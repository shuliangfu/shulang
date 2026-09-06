/* seeds/runtime_process_import_alias.from_x.c — pure-asm product std_process_* face
 *
 * PLATFORM: SHARED — ld -r into std/process/process.o (process_merge authority).
 *
 * Why (G.7 complete process_merge): pure-asm import METHOD mangles
 *   import("std.process").args_count → std_process_args_count (etc.).
 * process_merge historically only carried bare ABI process_*_c (args thin +
 * argv + os_glue). C-path product co-emitted mod.x for the namespaced face;
 * pure-asm skips that co-emit and links prebuilt process.o → UNDEF std_process_*.
 *
 * Authority: thin 1:1 wrappers over process_*_c already T in process.o after
 * merge (same signatures as std/process/mod.x export surface). Do not invent a
 * second process OS body — only import-binding names. Mirror net tls_stub
 * import_alias + path std_path_* product face in the hybrid leaf.
 *
 * exit: mod.x stub returns 0; product tests need real terminate.
 * Cap residual 9.1.4: Linux exit_group via xlang_process_cap (no libc _exit).
 */
#include <stdint.h>
#include <unistd.h>
#include <xlang_process_cap.h>

extern int32_t process_args_count_c(void);
extern uint8_t *process_arg_c(int32_t i);
extern uint8_t *process_getenv_c(uint8_t *name);
extern int32_t process_setenv_c(uint8_t *name, uint8_t *value, int32_t overwrite);
extern int32_t process_unsetenv_c(uint8_t *name);
extern int32_t process_getpid_c(void);
extern int32_t process_getppid_c(void);
extern int32_t process_getcwd_c(uint8_t *buf, int32_t buf_size);
extern uint8_t *process_getcwd_ptr_c(void);
extern int32_t process_getcwd_cached_len_c(void);
extern int32_t process_chdir_c(uint8_t *path);
extern int32_t process_self_exe_path_c(uint8_t *buf, int32_t buf_size);
extern uint8_t *process_self_exe_path_ptr_c(void);
extern int32_t process_self_exe_path_cached_len_c(void);
extern int32_t process_spawn_c(uint8_t *program, uint8_t *argv);
extern int32_t process_spawn_io_c(uint8_t *program, uint8_t *argv, void *io);
extern int32_t process_exec_c(uint8_t *program, uint8_t *argv);
extern int32_t process_waitpid_c(int32_t pid);
extern int32_t process_spawn_simple_c(uint8_t *program);
extern int32_t process_exec_simple_c(uint8_t *program);
extern int32_t process_pipe_c(int32_t *read_fd, int32_t *write_fd);

/**
 * Product std.process.exit — terminate with code.
 * Cap residual 9.1.4: Linux/Darwin raw syscall via xlang_proc_exit (no libc _exit).
 * @param code process exit status
 * @return never returns (0 unreachable)
 * PLATFORM: SHARED Cap residual.
 */
int32_t std_process_exit(int32_t code) {
    xlang_proc_exit((int)code);
    return 0;
}

int32_t std_process_args_count(void) { return process_args_count_c(); }

uint8_t *std_process_arg(int32_t i) { return process_arg_c(i); }

uint8_t *std_process_getenv(uint8_t *name) { return process_getenv_c(name); }

int32_t std_process_setenv(uint8_t *name, uint8_t *value, int32_t overwrite) {
    return process_setenv_c(name, value, overwrite);
}

int32_t std_process_unsetenv(uint8_t *name) { return process_unsetenv_c(name); }

int32_t std_process_getpid(void) { return process_getpid_c(); }

int32_t std_process_getppid(void) { return process_getppid_c(); }

int32_t std_process_getcwd(uint8_t *buf, int32_t buf_size) {
    return process_getcwd_c(buf, buf_size);
}

uint8_t *std_process_getcwd_ptr(void) { return process_getcwd_ptr_c(); }

int32_t std_process_getcwd_cached_len(void) { return process_getcwd_cached_len_c(); }

int32_t std_process_chdir(uint8_t *path) { return process_chdir_c(path); }

int32_t std_process_self_exe_path(uint8_t *buf, int32_t buf_size) {
    return process_self_exe_path_c(buf, buf_size);
}

uint8_t *std_process_self_exe_path_ptr(void) { return process_self_exe_path_ptr_c(); }

int32_t std_process_self_exe_path_cached_len(void) {
    return process_self_exe_path_cached_len_c();
}

int32_t std_process_spawn(uint8_t *program, uint8_t *argv) {
    return process_spawn_c(program, argv);
}

int32_t std_process_spawn_io(uint8_t *program, uint8_t *argv, void *io) {
    return process_spawn_io_c(program, argv, io);
}

int32_t std_process_exec(uint8_t *program, uint8_t *argv) {
    return process_exec_c(program, argv);
}

int32_t std_process_waitpid(int32_t pid) { return process_waitpid_c(pid); }

int32_t std_process_spawn_simple(uint8_t *program) {
    return process_spawn_simple_c(program);
}

int32_t std_process_exec_simple(uint8_t *program) {
    return process_exec_simple_c(program);
}

int32_t std_process_pipe(int32_t *read_fd, int32_t *write_fd) {
    return process_pipe_c(read_fd, write_fd);
}
