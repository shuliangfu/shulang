/* seeds/runtime_process_os_glue.from_x.c — G-02f-18 product TU
 * G-02f-103 helper gates.
 * Product: runtime_process_os_glue.o; logic still C until full .x port.
 *
 * wave252 G.7: process_getenv via public face link_abi_getenv (not raw getenv).
 * wave253: face body in runtime_link_abi_user_env.o (declaration only here).
 * Weak user-domain twin; strong may come from runtime_panic C seed (wave251).
 * PLATFORM: SHARED — user/STD_AND_PANIC residual face; never g05 host bag.
 */
/**
 * runtime_process_os_glue.c — 进程 OS 胶层（F-ZC：自 std/process/process_os_glue.c 迁入）
 *
 * 【文件职责】
 * getenv/setenv、getpid/getppid、getcwd/chdir、self_exe_path、spawn/exec/waitpid/pipe。
 * argc/argv 全局与 args 薄封装见 runtime_process_argv.c + process.x。
 *
 * 【所属模块/组件】
 * 标准库 std.process；与 std/process/mod.x 同目录，mod.x 为对外 API 层。
 *
 * 【与其它文件的关系】
 * - 被依赖：ld -r 合并为 process.o 后由 runtime 链入用户 exe。
 * - 依赖：runtime_process_argv.o 提供 xlang_process_argc/argv（codegen 写入）。
 *
 * 【重要约定与说明】
 * - 所有 *name、*path、*program 等指针均要求 NUL 结尾的 C 字符串；buf 与 buf_size 由调用方保证不越界。
 * - spawn/exec 的 argv 在 C 侧为 char**，以 NULL 结尾；spawn_simple/exec_simple 内部构造 [program, NULL]。
 * - Windows 上 getppid 返回 -1；exec/exec_simple 返回 -1（不实现替换当前进程）。
 * - 与 analysis/std开发时序分析.md、std/process/README.md 中 std.process 约定一致。
 *
 * 【性能与压榨】
 * - 热路径（args_count_c、arg_c、getenv_c、getpid_c、getppid_c）：仅读全局或单次 syscall，零分配；
 *   用户以 -O2/-O3 且 -flto 链接时，编译器可跨 TU 内联，消除调用开销。
 * - getcwd_c：首次或 chdir 后走 syscall 并写入静态缓存；后续调用仅 memcpy 从缓存到用户 buf，避免重复 getcwd/GetCurrentDirectory。
 *   chdir_c 调用时使缓存失效（process_cwd_cache_len=0）。
 * - self_exe_path_c：可执行路径在进程生命周期内不变，首次 syscall 后写入静态缓存，后续仅 memcpy，避免重复 readlink/GetModuleFileName/_NSGetExecutablePath。
 * - 零拷贝：getcwd_ptr_c/self_exe_path_ptr_c 直接返回指向内部缓存的只读指针，无 memcpy；调用方只读、勿写。
 *   getcwd 指针在下次 chdir 或 getcwd 前有效；self_exe_path 指针在进程生命周期内有效。配套 *_cached_len_c 返回长度。
 * - 缓存拷贝均用 memcpy，便于编译器向量化；缓存大小 4K，满足常见路径长度。
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/* wave253: declaration only — face body in runtime_link_abi_user_env.o (weak; panic C strong wins). */
#include <xlang_user_link_abi_getenv.h>
/* Cap residual 9.1.1: POSIX setenv/unsetenv via environ mutate (no libc). */
#include <xlang_environ_cap.h>
/* Cap residual 9.1.4: Linux fork/execve/wait4/pipe without libc. */
#include <xlang_process_cap.h>
/* wave252 G.7: single face — XLANG_GETENV routes through link_abi_getenv. */
#define XLANG_GETENV(name) link_abi_getenv((const char *)(name))

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#else
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif
#include <errno.h>
#include <fcntl.h>
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#else
extern char **environ;
#endif
#endif

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
void process_nop_sigchld(int32_t sig);
int32_t process_dup_stdio_posix(int32_t fd, int32_t slot);

/* Forward declarations of thin public API functions (provided by .x in R2 mode).
 * Needed by smoke tests and noinline C functions that call back into public API. */
uint8_t *process_getenv_c(uint8_t *name);
int32_t process_setenv_c(uint8_t *name, uint8_t *value, int32_t overwrite);
int32_t process_unsetenv_c(uint8_t *name);
int32_t process_getpid_c(void);
int32_t process_getppid_c(void);
int32_t process_getcwd_c(uint8_t *buf, int32_t buf_size);
uint8_t *process_getcwd_ptr_c(void);
int32_t process_getcwd_cached_len_c(void);
int32_t process_chdir_c(uint8_t *path);
int32_t process_self_exe_path_c(uint8_t *buf, int32_t buf_size);
uint8_t *process_self_exe_path_ptr_c(void);
int32_t process_self_exe_path_cached_len_c(void);
int32_t process_spawn_c(uint8_t *program, uint8_t *argv_ptr);
int32_t process_exec_c(uint8_t *program, uint8_t *argv_ptr);
int32_t process_waitpid_c(int32_t pid);
int32_t process_spawn_simple_c(uint8_t *program);
int32_t process_spawn_io_c(uint8_t *program, uint8_t *argv_ptr, void *io);
int32_t process_exec_simple_c(uint8_t *program);
int32_t process_pipe_c(int32_t *read_fd, int32_t *write_fd);

/** Get environment variable value. */
uint8_t *process_getenv_impl(uint8_t *name) {
    if (name == NULL) return NULL;
    const char *v = XLANG_GETENV(name);
    return v ? (uint8_t *)v : NULL;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
uint8_t *process_getenv_c(uint8_t *name) {
    return process_getenv_impl(name);
}
#endif

/**
 * Set environment variable name=value; overwrite != 0 replaces existing.
 * Cap residual 9.1.1: xlang_environ_setenv (POSIX walk / Win32 dual block).
 * @return 0 success, -1 failure.
 * PLATFORM: SHARED Cap (9.1.1).
 */
int32_t process_setenv_impl(uint8_t *name, uint8_t *value, int32_t overwrite) {
    if (name == NULL) return -1;
    return xlang_environ_setenv((const char *)name, value ? (const char *)value : "",
                                overwrite ? 1 : 0);
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_setenv_c(uint8_t *name, uint8_t *value, int32_t overwrite) {
    return process_setenv_impl(name, value, overwrite);
}
#endif

/**
 * Delete environment variable name.
 * Cap residual 9.1.1: xlang_environ_unsetenv (POSIX walk / Win32 dual block).
 * @return 0 success, -1 failure.
 * PLATFORM: SHARED Cap (9.1.1).
 */
int32_t process_unsetenv_impl(uint8_t *name) {
    if (name == NULL) return -1;
    return xlang_environ_unsetenv((const char *)name);
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_unsetenv_c(uint8_t *name) {
    return process_unsetenv_impl(name);
}
#endif

/** Cap residual 9.1.3: process_getpid_impl via Cap xlang_proc_getpid (no libc getpid).
 * Linux: raw syscall (nr 39/172); Darwin: raw syscall (nr 0x2000014/20); Windows: GetCurrentProcessId.
 * PLATFORM: SHARED Cap (9.1.3).
 */
int32_t process_getpid_impl(void) {
    return (int32_t)xlang_proc_getpid();
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_getpid_c(void) {
    return process_getpid_impl();
}
#endif

/** Cap residual 9.1.3: process_getppid_impl via Cap xlang_proc_getppid (no libc getppid).
 * Linux: raw syscall (nr 110/173); Darwin: raw syscall (nr 0x2000027/39); Windows: -1.
 * PLATFORM: SHARED Cap (9.1.3).
 */
int32_t process_getppid_impl(void) {
    return (int32_t)xlang_proc_getppid();
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_getppid_c(void) {
    return process_getppid_impl();
}
#endif

/* getcwd 缓存：进程内多次 getcwd 且未 chdir 时避免重复 syscall；chdir 时失效。最大路径 4K。 */
#define PROCESS_CWD_CACHE_SIZE 4096
static char process_cwd_cache[PROCESS_CWD_CACHE_SIZE];
static int32_t process_cwd_cache_len = 0; /* 0 表示未缓存或已失效 */

/**
 * Write cwd into buf (NUL-terminated), at most buf_size bytes including NUL.
 * Returns bytes written excluding NUL, or -1 on failure.
 * Cache: first call / after chdir hits syscall; later calls memcpy only.
 * Cap residual 9.1.3: uses Cap xlang_proc_getcwd (no libc getcwd).
 * PLATFORM: SHARED Cap (9.1.3).
 */
int32_t process_getcwd_impl(uint8_t *buf, int32_t buf_size) {
    if (buf == NULL || buf_size <= 0) return -1;
    if (process_cwd_cache_len > 0) {
        if ((int32_t)process_cwd_cache_len >= buf_size) return -1;
        memcpy(buf, process_cwd_cache, (size_t)process_cwd_cache_len + 1u);
        return process_cwd_cache_len;
    }
    long n = xlang_proc_getcwd(process_cwd_cache, sizeof(process_cwd_cache));
    if (n <= 1) return -1;
    process_cwd_cache_len = (int32_t)n - 1;
    if (process_cwd_cache_len >= buf_size) return -1;
    memcpy(buf, process_cwd_cache, (size_t)process_cwd_cache_len + 1u);
    return process_cwd_cache_len;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_getcwd_c(uint8_t *buf, int32_t buf_size) {
    return process_getcwd_impl(buf, buf_size);
}
#endif

/**
 * Zero-copy: pointer to internal cwd cache (NUL-terminated).
 * Fills cache on miss. Caller must not write; valid until next chdir/getcwd fill.
 * Cap residual 9.1.3: uses Cap xlang_proc_getcwd (no libc getcwd).
 * PLATFORM: SHARED Cap (9.1.3).
 */
uint8_t *process_getcwd_ptr_impl(void) {
    if (process_cwd_cache_len > 0)
        return (uint8_t *)process_cwd_cache;
    long n = xlang_proc_getcwd(process_cwd_cache, sizeof(process_cwd_cache));
    if (n <= 1)
        return NULL;
    process_cwd_cache_len = (int32_t)n - 1;
    return (uint8_t *)process_cwd_cache;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
uint8_t *process_getcwd_ptr_c(void) {
    return process_getcwd_ptr_impl();
}
#endif

/** 返回当前 getcwd 缓存长度（不含 NUL）；未缓存或已失效为 0。与 process_getcwd_ptr_c 配套使用。 */
int32_t process_getcwd_cached_len_impl(void) {
    return process_cwd_cache_len;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_getcwd_cached_len_c(void) {
    return process_getcwd_cached_len_impl();
}
#endif

/** Change cwd to path (NUL-terminated). Returns 0 ok, -1 fail. Invalidates getcwd cache.
 * Cap residual 9.1.3: uses Cap xlang_proc_chdir (no libc chdir).
 * Linux: raw syscall (nr 80/49); Darwin: raw syscall (nr 0x200000c/12); Windows: SetCurrentDirectoryA.
 * PLATFORM: SHARED Cap (9.1.3).
 */
int32_t process_chdir_impl(uint8_t *path) {
    if (path == NULL) return -1;
    process_cwd_cache_len = 0;
    return xlang_proc_chdir((const char *)path);
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_chdir_c(uint8_t *path) {
    return process_chdir_impl(path);
}
#endif

/* self_exe_path 缓存：可执行路径在进程生命周期内不变，首次 syscall 后缓存，后续仅 memcpy。 */
#define PROCESS_EXE_CACHE_SIZE 4096
static char process_exe_cache[PROCESS_EXE_CACHE_SIZE];
static int32_t process_exe_cache_len = 0; /* 0 表示未缓存 */

/**
 * 将当前可执行文件路径写入 buf（NUL 结尾），最多写 buf_size 字节（含 NUL）。
 * 返回写入的字节数（不含 NUL），失败返回 -1。
 * 性能：首次调用走 readlink/GetModuleFileName/_NSGetExecutablePath 并缓存；后续仅 memcpy，避免重复 syscall。
 */
int32_t process_self_exe_path_impl(uint8_t *buf, int32_t buf_size) {
    if (buf == NULL || buf_size <= 0) return -1;
    if (process_exe_cache_len > 0) {
        if (process_exe_cache_len >= buf_size) return -1;
        memcpy(buf, process_exe_cache, (size_t)process_exe_cache_len + 1u);
        return process_exe_cache_len;
    }
#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD n = GetModuleFileNameA(NULL, process_exe_cache, (DWORD)sizeof(process_exe_cache));
        if (n == 0 || n >= (DWORD)sizeof(process_exe_cache)) return -1;
        process_exe_cache[n] = '\0';
        process_exe_cache_len = (int32_t)n;
        if ((int32_t)n >= buf_size) return -1;
        memcpy(buf, process_exe_cache, (size_t)n + 1u);
        return (int32_t)n;
    }
#elif defined(__APPLE__)
    {
        uint32_t size = (uint32_t)sizeof(process_exe_cache);
        if (_NSGetExecutablePath(process_exe_cache, &size) != 0) return -1;
        size_t n = strlen(process_exe_cache);
        process_exe_cache_len = (int32_t)n;
        if ((int32_t)n >= buf_size) return -1;
        memcpy(buf, process_exe_cache, n + 1u);
        return (int32_t)n;
    }
#else
    {
        ssize_t n = readlink("/proc/self/exe", process_exe_cache, sizeof(process_exe_cache) - 1);
        if (n <= 0 || n >= (ssize_t)(sizeof(process_exe_cache) - 1)) return -1;
        process_exe_cache[n] = '\0';
        process_exe_cache_len = (int32_t)n;
        if ((int32_t)n >= buf_size) return -1;
        memcpy(buf, process_exe_cache, (size_t)n + 1u);
        return (int32_t)n;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_self_exe_path_c(uint8_t *buf, int32_t buf_size) {
    return process_self_exe_path_impl(buf, buf_size);
}
#endif

/**
 * 零拷贝：返回指向内部缓存的可执行路径（NUL 结尾）。若未缓存则先填充；失败返回 NULL。
 * 调用方只读，不得修改；指针在进程生命周期内有效。
 */
uint8_t *process_self_exe_path_ptr_impl(void) {
    if (process_exe_cache_len > 0)
        return (uint8_t *)process_exe_cache;
#if defined(_WIN32) || defined(_WIN64)
    {
        DWORD n = GetModuleFileNameA(NULL, process_exe_cache, (DWORD)sizeof(process_exe_cache));
        if (n == 0 || n >= (DWORD)sizeof(process_exe_cache)) return NULL;
        process_exe_cache[n] = '\0';
        process_exe_cache_len = (int32_t)n;
        return (uint8_t *)process_exe_cache;
    }
#elif defined(__APPLE__)
    {
        uint32_t size = (uint32_t)sizeof(process_exe_cache);
        if (_NSGetExecutablePath(process_exe_cache, &size) != 0) return NULL;
        process_exe_cache_len = (int32_t)strlen(process_exe_cache);
        return (uint8_t *)process_exe_cache;
    }
#else
    {
        ssize_t n = readlink("/proc/self/exe", process_exe_cache, sizeof(process_exe_cache) - 1);
        if (n <= 0 || n >= (ssize_t)(sizeof(process_exe_cache) - 1)) return NULL;
        process_exe_cache[n] = '\0';
        process_exe_cache_len = (int32_t)n;
        return (uint8_t *)process_exe_cache;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
uint8_t *process_self_exe_path_ptr_c(void) {
    return process_self_exe_path_ptr_impl();
}
#endif

/** 返回当前 self_exe_path 缓存长度（不含 NUL）；未缓存为 0。与 process_self_exe_path_ptr_c 配套使用。 */
int32_t process_self_exe_path_cached_len_impl(void) {
    return process_exe_cache_len;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_self_exe_path_cached_len_c(void) {
    return process_self_exe_path_cached_len_impl();
}
#endif

#if !defined(_WIN32) && !defined(_WIN64)
void process_nop_sigchld_impl(int32_t sig) { (void)sig; }

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
void process_nop_sigchld(int32_t sig) {
    process_nop_sigchld_impl(sig);
}
#endif

#else
void process_nop_sigchld_impl(int32_t sig) { (void)sig; }
#endif

/**
 * Spawn child running program with argv (NULL-terminated char* array).
 * Cap residual 9.1.4: Linux fork+execve via xlang_process_cap (no libc fork/execve).
 * Windows: CreateProcess. Other POSIX: libc fork/execve.
 * @return child pid (>0) or -1
 * PLATFORM: LINUX Cap residual; WIN32 CreateProcess; else POSIX.
 */
int32_t process_spawn_impl(uint8_t *program, uint8_t *argv_ptr) {
    if (program == NULL || argv_ptr == NULL) return -1;
    char **argv = (char **)(void *)argv_ptr;
#if defined(_WIN32) || defined(_WIN64)
    {
        char cmdline[32768];
        size_t off = 0;
        for (int i = 0; argv[i] != NULL && off < sizeof(cmdline) - 4; i++) {
            if (i > 0) { cmdline[off++] = ' '; }
            const char *a = argv[i];
            int quote = (strchr(a, ' ') != NULL || strchr(a, '\t') != NULL);
            if (quote) cmdline[off++] = '"';
            while (*a && off < sizeof(cmdline) - 2) {
                if (*a == '"') { cmdline[off++] = '\\'; cmdline[off++] = '"'; a++; continue; }
                cmdline[off++] = *a++;
            }
            if (quote) cmdline[off++] = '"';
        }
        cmdline[off] = '\0';
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));
        if (!CreateProcessA((const char *)program, cmdline, NULL, NULL, 0, 0, NULL, NULL, &si, &pi)) {
            return -1;
        }
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return (int32_t)(intptr_t)pi.dwProcessId;
    }
#else
    {
        void (*saved_sigchld)(int) = signal(SIGCHLD, process_nop_sigchld);
        if (saved_sigchld == SIG_ERR) saved_sigchld = SIG_DFL;
        long pid = xlang_proc_fork();
        if (pid < 0) {
            signal(SIGCHLD, saved_sigchld);
            return -1;
        }
        if (pid == 0) {
            signal(SIGCHLD, saved_sigchld);
            (void)xlang_proc_execve((const char *)program, (char *const *)argv, environ);
            xlang_proc_exit(127);
        }
        signal(SIGCHLD, saved_sigchld);
        return (int32_t)pid;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_spawn_c(uint8_t *program, uint8_t *argv_ptr) {
    return process_spawn_impl(program, argv_ptr);
}
#endif

/**
 * Replace current process with program (does not return on success).
 * Cap residual 9.1.4: Linux/Darwin raw execve via xlang_process_cap (no libc execve).
 * Windows: unsupported (-1).
 * @return -1 on failure
 * PLATFORM: SHARED Cap residual; WIN32 -1.
 */
int32_t process_exec_impl(uint8_t *program, uint8_t *argv_ptr) {
    if (program == NULL || argv_ptr == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    (void)program;
    (void)argv_ptr;
    return -1;
#else
    char **argv = (char **)(void *)argv_ptr;
    (void)xlang_proc_execve((const char *)program, (char *const *)argv, environ);
    return -1;
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_exec_c(uint8_t *program, uint8_t *argv_ptr) {
    return process_exec_impl(program, argv_ptr);
}
#endif

/**
 * Wait for child pid; return exit code (low 8 bits) or -1.
 * Cap residual 9.1.4: Linux/Darwin wait4 via xlang_process_cap (no libc waitpid).
 * Windows: OpenProcess + WaitForSingleObject.
 * PLATFORM: SHARED Cap residual; WIN32.
 */
int32_t process_waitpid_impl(int32_t pid) {
    if (pid <= 0) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE, FALSE, (DWORD)(uint32_t)pid);
        if (h == NULL) return -1;
        if (WaitForSingleObject(h, INFINITE) != WAIT_OBJECT_0) {
            CloseHandle(h);
            return -1;
        }
        DWORD code = 0;
        if (!GetExitCodeProcess(h, &code)) {
            CloseHandle(h);
            return -1;
        }
        CloseHandle(h);
        return (int32_t)(uint32_t)code;
    }
#else
    {
        int status = 0;
        long w = xlang_proc_waitpid((long)pid, &status, 0);
        if (w != (long)pid) return -1;
        if (WIFEXITED(status)) return (int32_t)(uint8_t)WEXITSTATUS(status);
        return -1;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_waitpid_c(int32_t pid) {
    return process_waitpid_impl(pid);
}
#endif

/**
 * 简化 spawn：argv = [program, NULL]。返回 pid 或 -1。
 */
int32_t process_spawn_simple_impl(uint8_t *program) {
    if (program == NULL) return -1;
    char *argv[] = { (char *)program, NULL };
    return process_spawn_impl(program, (uint8_t *)(void *)argv);
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_spawn_simple_c(uint8_t *program) {
    return process_spawn_simple_impl(program);
}
#endif

/** spawn_io 与 mod.x SpawnIo 布局一致（三 i32 fd）。 */
typedef struct {
    int32_t stdin_fd;
    int32_t stdout_fd;
    int32_t stderr_fd;
} process_spawn_io_t;

#if !defined(_WIN32) && !defined(_WIN64)
/**
 * dup2 fd → slot for spawn_io stdio redirect.
 * Cap residual 9.1.4: Linux/Darwin raw syscall via xlang_proc_dup2 (no libc dup2).
 * @return 0 ok, -1 fail
 * PLATFORM: SHARED Cap residual.
 */
int32_t process_dup_stdio_posix_impl(int32_t fd, int32_t slot) {
    if (fd < 0) return 0;
    if (xlang_proc_dup2(fd, slot) < 0) return -1;
    return 0;
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_dup_stdio_posix(int32_t fd, int32_t slot) {
    return process_dup_stdio_posix_impl(fd, slot);
}
#endif

#else
int32_t process_dup_stdio_posix_impl(int32_t fd, int32_t slot) { (void)fd; (void)slot; return -1; }
#endif

/**
 * 创建子进程并应用 stdio 重定向；fd < 0 表示继承。
 * POSIX: fork + dup2 + execve；Windows: CreateProcess + STARTF_USESTDHANDLES。
 */
int32_t process_spawn_io_impl(uint8_t *program, uint8_t *argv_ptr, void *io_void) {
    if (program == NULL || argv_ptr == NULL) return -1;
    process_spawn_io_t *io = (process_spawn_io_t *)io_void;
    int32_t in_fd = io ? io->stdin_fd : -1;
    int32_t out_fd = io ? io->stdout_fd : -1;
    int32_t err_fd = io ? io->stderr_fd : -1;
    char **argv = (char **)(void *)argv_ptr;
#if defined(_WIN32) || defined(_WIN64)
    {
        char cmdline[32768];
        size_t off = 0;
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE h_err = GetStdHandle(STD_ERROR_HANDLE);
        for (int i = 0; argv[i] != NULL && off < sizeof(cmdline) - 4; i++) {
            if (i > 0) cmdline[off++] = ' ';
            const char *a = argv[i];
            int quote = (strchr(a, ' ') != NULL || strchr(a, '\t') != NULL);
            if (quote) cmdline[off++] = '"';
            while (*a && off < sizeof(cmdline) - 2) {
                if (*a == '"') {
                    cmdline[off++] = '\\';
                    cmdline[off++] = '"';
                    a++;
                    continue;
                }
                cmdline[off++] = *a++;
            }
            if (quote) cmdline[off++] = '"';
        }
        cmdline[off] = '\0';
        if (in_fd >= 0) h_in = (HANDLE)_get_osfhandle(in_fd);
        if (out_fd >= 0) h_out = (HANDLE)_get_osfhandle(out_fd);
        if (err_fd >= 0) h_err = (HANDLE)_get_osfhandle(err_fd);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdInput = h_in;
        si.hStdOutput = h_out;
        si.hStdError = h_err;
        memset(&pi, 0, sizeof(pi));
        if (!CreateProcessA((const char *)program, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
            return -1;
        }
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return (int32_t)(intptr_t)pi.dwProcessId;
    }
#else
    {
        void (*saved_sigchld)(int) = signal(SIGCHLD, process_nop_sigchld);
        if (saved_sigchld == SIG_ERR) saved_sigchld = SIG_DFL;
        long pid = xlang_proc_fork();
        if (pid < 0) {
            signal(SIGCHLD, saved_sigchld);
            return -1;
        }
        if (pid == 0) {
            signal(SIGCHLD, saved_sigchld);
            if (in_fd >= 0 && process_dup_stdio_posix(in_fd, STDIN_FILENO) != 0) xlang_proc_exit(127);
            if (out_fd >= 0 && process_dup_stdio_posix(out_fd, STDOUT_FILENO) != 0) xlang_proc_exit(127);
            if (err_fd >= 0 && process_dup_stdio_posix(err_fd, STDERR_FILENO) != 0) xlang_proc_exit(127);
            (void)xlang_proc_execve((const char *)program, (char *const *)argv, environ);
            xlang_proc_exit(127);
        }
        signal(SIGCHLD, saved_sigchld);
        return (int32_t)pid;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_spawn_io_c(uint8_t *program, uint8_t *argv_ptr, void *io) {
    return process_spawn_io_impl(program, argv_ptr, io);
}
#endif

/**
 * 简化 exec：argv = [program, NULL]。成功不返回；失败返回 -1。
 */
int32_t process_exec_simple_impl(uint8_t *program) {
    if (program == NULL) return -1;
    char *argv[] = { (char *)program, NULL };
    return process_exec_impl(program, (uint8_t *)(void *)argv);
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_exec_simple_c(uint8_t *program) {
    return process_exec_simple_impl(program);
}
#endif

/**
 * Create a pipe; on success *read_fd readable, *write_fd writable.
 * Cap residual 9.1.4: Linux/Darwin raw syscall via xlang_process_cap (no libc pipe).
 * Windows: CreatePipe. Other POSIX: libc pipe.
 * @return 0 ok, -1 fail
 * PLATFORM: SHARED Cap residual; WIN32.
 */
int32_t process_pipe_impl(int32_t *read_fd, int32_t *write_fd) {
    if (read_fd == NULL || write_fd == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        SECURITY_ATTRIBUTES sa;
        HANDLE r = NULL;
        HANDLE w = NULL;
        memset(&sa, 0, sizeof(sa));
        sa.nLength = sizeof(sa);
        sa.bInheritHandle = TRUE;
        if (!CreatePipe(&r, &w, &sa, 0)) return -1;
        SetHandleInformation(r, HANDLE_FLAG_INHERIT, 0);
        *read_fd = (int32_t)_open_osfhandle((intptr_t)r, _O_RDONLY);
        *write_fd = (int32_t)_open_osfhandle((intptr_t)w, _O_WRONLY);
        if (*read_fd < 0 || *write_fd < 0) return -1;
        return 0;
    }
#else
    {
        int fd[2];
        if (xlang_proc_pipe(fd) != 0) return -1;
        *read_fd = (int32_t)fd[0];
        *write_fd = (int32_t)fd[1];
        return 0;
    }
#endif
}

#ifndef XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X
int32_t process_pipe_c(int32_t *read_fd, int32_t *write_fd) {
    return process_pipe_impl(read_fd, write_fd);
}
#endif
