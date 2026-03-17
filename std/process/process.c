/**
 * std/process/process.c — 进程控制、命令行参数、环境变量、工作目录、spawn/exec/waitpid
 *
 * 【文件职责】
 * 实现 std.process 模块的 C 侧逻辑：保存入口 main 的 argc/argv；提供环境变量（getenv/setenv/unsetenv）、
 * 进程 ID（getpid/getppid）、当前工作目录（getcwd/chdir）、可执行路径（self_exe_path）、
 * 子进程创建与等待（spawn/spawn_simple、exec/exec_simple、waitpid）。所有接口按 POSIX + Windows 双平台实现，
 * 供 std/process/mod.su 通过 extern 调用。
 *
 * 【所属模块/组件】
 * 标准库 std.process，依赖 core 无；与 std/process/mod.su 同目录，mod.su 为对外 API 层，本文件为平台实现层。
 *
 * 【与其它文件的关系】
 * - 被依赖：compiler 在用户使用「-o exe」且程序 import std.process 时，将本文件编译产出的 process.o 链入可执行文件。
 * - 依赖：无项目内头文件；依赖系统 C 库（stdlib、string、unistd/sys/wait 或 Windows API）。
 * - 与 codegen：codegen 对入口 main 生成「写 shulang_process_argc/argv」的代码，本文件定义该全局供 args_count_c/arg_c 读取。
 *
 * 【重要约定与说明】
 * - 全局变量 shulang_process_argc、shulang_process_argv 仅在入口 main 执行后有效；库模块的 main 不会写入。
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

#if defined(_WIN32) || defined(_WIN64)
#include <stdlib.h>
#include <string.h>
/* Windows: process & env & cwd */
#include <windows.h>
#define SHU_GETENV(name) getenv((const char *)(name))
#else
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
#define SHU_GETENV(name) getenv((const char *)(name))
extern char **environ;
#endif

/** 由 codegen 生成的 main(int argc, char **argv) 在入口处赋值；供 args_count_c / arg_c 读取。 */
int shulang_process_argc = 0;
char **shulang_process_argv = NULL;

/** 热路径：仅读全局，零分配；链接时 -flto 可跨 TU 内联以压榨调用开销。 */
int32_t process_args_count_c(void) {
    return (int32_t)shulang_process_argc;
}

/** 热路径：边界检查 + 指针解引用，零分配；-flto 可内联。 */
uint8_t *process_arg_c(int32_t i) {
    if (shulang_process_argv == NULL || i < 0 || (int)i >= shulang_process_argc)
        return NULL;
    return (uint8_t *)shulang_process_argv[i];
}

/** 热路径：单次 getenv，零分配；-flto 可内联。 */
uint8_t *process_getenv_c(uint8_t *name) {
    if (name == NULL) return NULL;
    const char *v = SHU_GETENV(name);
    return v ? (uint8_t *)v : NULL;
}

/**
 * 设置环境变量 name=value；overwrite 非 0 时覆盖已有值。
 * POSIX: setenv(name, value, overwrite)；Windows: _putenv("name=value")。
 * 返回 0 成功，-1 失败。
 */
int32_t process_setenv_c(uint8_t *name, uint8_t *value, int32_t overwrite) {
    if (name == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    (void)overwrite;
    {
        char buf[1024];
        size_t n = 0;
        while (n < sizeof(buf) - 2 && name[n]) { buf[n] = (char)name[n]; n++; }
        if (n >= sizeof(buf) - 2) return -1;
        buf[n++] = '=';
        if (value) {
            size_t j = 0;
            while (value[j] && n < sizeof(buf) - 1) { buf[n++] = (char)value[j++]; }
        }
        buf[n] = '\0';
        return _putenv(buf) == 0 ? 0 : -1;
    }
#else
    return setenv((const char *)name, value ? (const char *)value : "", overwrite ? 1 : 0) == 0 ? 0 : -1;
#endif
}

/** 删除环境变量 name。POSIX: unsetenv；Windows: _putenv("name=")。返回 0 成功，-1 失败。 */
int32_t process_unsetenv_c(uint8_t *name) {
    if (name == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    {
        char buf[512];
        size_t n = 0;
        while (n < sizeof(buf) - 2 && name[n]) { buf[n] = (char)name[n]; n++; }
        if (n >= sizeof(buf) - 2) return -1;
        buf[n++] = '=';
        buf[n] = '\0';
        return _putenv(buf) == 0 ? 0 : -1;
    }
#else
    return unsetenv((const char *)name) == 0 ? 0 : -1;
#endif
}

/** 热路径：单次 syscall；-flto 可内联。POSIX: getpid()；Windows: GetCurrentProcessId()。 */
int32_t process_getpid_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    return (int32_t)(intptr_t)GetCurrentProcessId();
#else
    return (int32_t)getpid();
#endif
}

/** 热路径：POSIX 单次 getppid()；Windows 返回 -1。-flto 可内联。 */
int32_t process_getppid_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    (void)0;
    return -1;
#else
    return (int32_t)getppid();
#endif
}

/* getcwd 缓存：进程内多次 getcwd 且未 chdir 时避免重复 syscall；chdir 时失效。最大路径 4K。 */
#define PROCESS_CWD_CACHE_SIZE 4096
static char process_cwd_cache[PROCESS_CWD_CACHE_SIZE];
static int32_t process_cwd_cache_len = 0; /* 0 表示未缓存或已失效 */

/**
 * 将当前工作目录写入 buf（NUL 结尾），最多写 buf_size 字节（含 NUL）。
 * 返回写入的字节数（不含 NUL），失败返回 -1。
 * 性能：首次调用或 chdir 后走 syscall 并缓存；后续调用仅内存拷贝，避免重复 getcwd/GetCurrentDirectory。
 */
int32_t process_getcwd_c(uint8_t *buf, int32_t buf_size) {
    if (buf == NULL || buf_size <= 0) return -1;
#if defined(_WIN32) || defined(_WIN64)
    if (process_cwd_cache_len > 0) {
        if ((int32_t)process_cwd_cache_len >= buf_size) return -1;
        size_t n = (size_t)process_cwd_cache_len + 1u;
        memcpy(buf, process_cwd_cache, n);
        return process_cwd_cache_len;
    }
    {
        DWORD n = GetCurrentDirectoryA((DWORD)buf_size, (char *)buf);
        if (n == 0 || n >= (DWORD)buf_size) return -1;
        process_cwd_cache_len = (int32_t)n;
        memcpy(process_cwd_cache, buf, (size_t)n + 1u);
        return (int32_t)n;
    }
#else
    if (process_cwd_cache_len > 0) {
        if (process_cwd_cache_len >= buf_size) return -1;
        memcpy(buf, process_cwd_cache, (size_t)process_cwd_cache_len + 1u);
        return process_cwd_cache_len;
    }
    {
        char *p = getcwd(process_cwd_cache, sizeof(process_cwd_cache));
        if (p == NULL) return -1;
        size_t n = strlen(process_cwd_cache);
        process_cwd_cache_len = (int32_t)n;
        if ((int32_t)n >= buf_size) return -1;
        memcpy(buf, process_cwd_cache, n + 1u);
        return (int32_t)n;
    }
#endif
}

/**
 * 零拷贝：返回指向内部缓存的当前工作目录字符串（NUL 结尾）。
 * 若缓存未填充则先填充；失败返回 NULL。调用方只读，不得修改；指针在下次 chdir 或 getcwd 前有效。
 */
uint8_t *process_getcwd_ptr_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    if (process_cwd_cache_len > 0)
        return (uint8_t *)process_cwd_cache;
    {
        DWORD n = GetCurrentDirectoryA((DWORD)sizeof(process_cwd_cache), process_cwd_cache);
        if (n == 0 || n >= (DWORD)sizeof(process_cwd_cache)) return NULL;
        process_cwd_cache[n] = '\0';
        process_cwd_cache_len = (int32_t)n;
        return (uint8_t *)process_cwd_cache;
    }
#else
    if (process_cwd_cache_len > 0)
        return (uint8_t *)process_cwd_cache;
    {
        char *p = getcwd(process_cwd_cache, sizeof(process_cwd_cache));
        if (p == NULL) return NULL;
        process_cwd_cache_len = (int32_t)strlen(process_cwd_cache);
        return (uint8_t *)process_cwd_cache;
    }
#endif
}

/** 返回当前 getcwd 缓存长度（不含 NUL）；未缓存或已失效为 0。与 process_getcwd_ptr_c 配套使用。 */
int32_t process_getcwd_cached_len_c(void) {
    return process_cwd_cache_len;
}

/** 切换当前工作目录到 path（NUL 结尾）。返回 0 成功，-1 失败。调用后使 getcwd 缓存失效。 */
int32_t process_chdir_c(uint8_t *path) {
    if (path == NULL) return -1;
    process_cwd_cache_len = 0;
#if defined(_WIN32) || defined(_WIN64)
    return SetCurrentDirectoryA((const char *)path) ? 0 : -1;
#else
    return chdir((const char *)path) == 0 ? 0 : -1;
#endif
}

/* self_exe_path 缓存：可执行路径在进程生命周期内不变，首次 syscall 后缓存，后续仅 memcpy。 */
#define PROCESS_EXE_CACHE_SIZE 4096
static char process_exe_cache[PROCESS_EXE_CACHE_SIZE];
static int32_t process_exe_cache_len = 0; /* 0 表示未缓存 */

/**
 * 将当前可执行文件路径写入 buf（NUL 结尾），最多写 buf_size 字节（含 NUL）。
 * 返回写入的字节数（不含 NUL），失败返回 -1。
 * 性能：首次调用走 readlink/GetModuleFileName/_NSGetExecutablePath 并缓存；后续仅 memcpy，避免重复 syscall。
 */
int32_t process_self_exe_path_c(uint8_t *buf, int32_t buf_size) {
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

/**
 * 零拷贝：返回指向内部缓存的可执行路径（NUL 结尾）。若未缓存则先填充；失败返回 NULL。
 * 调用方只读，不得修改；指针在进程生命周期内有效。
 */
uint8_t *process_self_exe_path_ptr_c(void) {
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

/** 返回当前 self_exe_path 缓存长度（不含 NUL）；未缓存为 0。与 process_self_exe_path_ptr_c 配套使用。 */
int32_t process_self_exe_path_cached_len_c(void) {
    return process_exe_cache_len;
}

#if !defined(_WIN32) && !defined(_WIN64)
/** 空 SIGCHLD handler，用于 spawn 前临时替换 SIG_IGN，使子进程可被 waitpid 回收（SIG_IGN 时系统会自动回收，waitpid 得 ECHILD）。 */
static void process_nop_sigchld(int sig) { (void)sig; }
#endif

/**
 * 创建子进程执行 program，参数为 argv（argv 为 char* 数组，以 NULL 结尾）。
 * 使用当前环境与当前工作目录。返回子进程 pid（>0），失败返回 -1。
 * POSIX: fork + execve；Windows: CreateProcess。
 */
int32_t process_spawn_c(uint8_t *program, uint8_t *argv_ptr) {
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
        /* 若当前为 SIG_IGN，子进程会被系统自动回收，waitpid 会得 ECHILD。临时改为空 handler，使子进程不被自动回收、可被 waitpid 回收；fork 后在父进程恢复。 */
        void (*saved_sigchld)(int) = signal(SIGCHLD, process_nop_sigchld);
        if (saved_sigchld == SIG_ERR) saved_sigchld = SIG_DFL;
        pid_t pid = fork();
        if (pid < 0) {
            signal(SIGCHLD, saved_sigchld);
            return -1;
        }
        if (pid == 0) {
            signal(SIGCHLD, saved_sigchld);
            execve((const char *)program, (char *const *)argv, environ);
            _exit(127);
        }
        signal(SIGCHLD, saved_sigchld);
        return (int32_t)pid;
    }
#endif
}

/**
 * 用 program 替换当前进程（不返回）。argv 为 char* 数组，以 NULL 结尾。
 * POSIX: execve；Windows 不支持，返回 -1。
 */
int32_t process_exec_c(uint8_t *program, uint8_t *argv_ptr) {
    if (program == NULL || argv_ptr == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    (void)program;
    (void)argv_ptr;
    return -1;
#else
    char **argv = (char **)(void *)argv_ptr;
    execve((const char *)program, (char *const *)argv, environ);
    return -1;
#endif
}

/**
 * 等待子进程 pid 结束，返回其退出码（低 8 位）；失败返回 -1。
 * POSIX: waitpid(pid, &status, 0)；Windows: OpenProcess + WaitForSingleObject + GetExitCodeProcess。
 */
int32_t process_waitpid_c(int32_t pid) {
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
        if (waitpid((pid_t)pid, &status, 0) != (pid_t)pid) return -1;
        if (WIFEXITED(status)) return (int32_t)(uint8_t)WEXITSTATUS(status);
        return -1;
    }
#endif
}

/**
 * 简化 spawn：argv = [program, NULL]。返回 pid 或 -1。
 */
int32_t process_spawn_simple_c(uint8_t *program) {
    if (program == NULL) return -1;
    char *argv[] = { (char *)program, NULL };
    return process_spawn_c(program, (uint8_t *)(void *)argv);
}

/**
 * 简化 exec：argv = [program, NULL]。成功不返回；失败返回 -1。
 */
int32_t process_exec_simple_c(uint8_t *program) {
    if (program == NULL) return -1;
    char *argv[] = { (char *)program, NULL };
    return process_exec_c(program, (uint8_t *)(void *)argv);
}

/**
 * 创建管道（P3 process 扩展）；成功时 *read_fd 可读、*write_fd 可写，返回 0；失败返回 -1。
 * POSIX: pipe(2)；Windows 暂不支持，返回 -1。
 */
int32_t process_pipe_c(int32_t *read_fd, int32_t *write_fd) {
    if (read_fd == NULL || write_fd == NULL) return -1;
#if defined(_WIN32) || defined(_WIN64)
    (void)read_fd;
    (void)write_fd;
    return -1;
#else
    int fd[2];
    if (pipe(fd) != 0) return -1;
    *read_fd = (int32_t)fd[0];
    *write_fd = (int32_t)fd[1];
    return 0;
#endif
}
