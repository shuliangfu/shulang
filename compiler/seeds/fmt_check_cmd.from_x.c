/* R2 thin + Cap residual pure 深迁（续 path_bss rest C leaf）：
 * PREFER hybrid thin 由 src/driver/fmt_check_cmd_thin.x（lit/entry + pure 真体）；
 * rest XLANG_L2_FMT_CHECK_THIN_FROM_X：无 thin 公共体；pure-duplicate _impl 剔除
 * （含 set_current_file / print / cwd_fallback / try_walk / path_resolve_abs /
 *  append_repo_lib_roots / missing_diag / invoke/dep_clear /
 *  collect_mode is_check / user_passed_L_get / init_user_lib_flags /
 *  file_list_n / user_ignore_count / lib_bufs_n / user_ignore_at /
 *  parse_ignore_opt / try_append_lib_root / argv_append /
 *  fmt_file_list_store / file_list_clear / fmt_file_list_at /
 *  driver_run_compiler_check / driver_run_fmt / check_one_file body /
 *  fmt_path_stat_kind / walk_dir_collect / fmt_check_path_bss_slot / …）；
 * Cap residual pure done：ALWAYS residual 0 + path_bss pure（hybrid rest T=0）。
 * 冷启动无宏：全 C 体（含 pure _impl + public 门闩 + path_bss C static）。
 * Regen thin surface: xlang -E src/driver/fmt_check_cmd_thin.x → thin_surface.
 */
#include "win32_compat.h"
#include "driver/fmt_check_cmd.h"
#include "diag.h"
#include "lsp/lsp_diag.h"
#include "runtime_driver_abi.h"
#include "runtime_io_abi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: fmt_check path/walk format → Cap snprintf */
/* G.7: Cap before Win32 opendir pattern snprintf and all later path joins. */
#undef snprintf
#define snprintf xlang_snprintf
#include <sys/stat.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#include <xlang_io_cap.h>
#include "xlang_weak.h"
/*
 * Stage 12.0.5 pure-asm hybrid residual (G.7 有则补全 — single exported authority):
 *
 * pure-asm of fmt_check_cmd_thin.x leaves U xlang_fmt_{opendir,closedir,access,
 * readdir_name}. Host-cc prologue (rt_prefer_try_x_to_o / g05_ensure) only injects
 * static inline bodies (local `t` — not exported). Hybrid rest is raw seed under
 * XLANG_L2_FMT_CHECK_THIN_FROM_X without that prologue → historically no global
 * def → Darwin pure-ld UNDEF (mac residual; Ubuntu often fell through -E).
 *
 * Always export XLANG_WEAK bodies here for both cold monofile and FROM_X rest so
 * pure-asm thin+rest partial-merge / final pure-ld resolve inside the fmt leaf
 * (and any peer pure-asm that U's the same face while this leaf is on the bag).
 *
 * Cap residual 9.1.10: opendir/readdir/closedir via xlang_dir_cap.h (G.7).
 * PLATFORM: SHARED — header is the single authority (Linux Cap / POSIX libc /
 * WINDOWS MinGW _findfirst). Do not keep a second _findfirst / void closedir_win
 * copy in this seed. access still unistd shim on MinGW. Weak globals for
 * pure-asm thin U faces.
 */
#include <xlang_dir_cap.h>

XLANG_WEAK uint8_t *xlang_fmt_opendir(uint8_t *name) {
    if (!name) {
        return (uint8_t *)0;
    }
    /* Cap residual 9.1.10: no libc opendir on Linux; MinGW _findfirst in header. */
    return (uint8_t *)xlang_dir_open((const char *)(void *)name);
}

XLANG_WEAK int32_t xlang_fmt_closedir(uint8_t *dirp) {
    if (!dirp) {
        return (int32_t)-1;
    }
    return (int32_t)xlang_dir_close((void *)dirp);
}

XLANG_WEAK int32_t xlang_fmt_access(uint8_t *path, int32_t mode) {
    if (!path) {
        return (int32_t)-1;
    }
    return (int32_t)access((const char *)(void *)path, (int)mode);
}

XLANG_WEAK uint8_t *xlang_fmt_readdir_name(uint8_t *dirp) {
    if (!dirp) {
        return (uint8_t *)0;
    }
    {
        char *n = xlang_dir_readdir_name((void *)dirp);
        return (uint8_t *)(void *)n;
    }
}

/* wave234 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — cold seed residual uses same face as thin.x / full.x. */
extern char *link_abi_getenv(const char *name);
#ifdef XLANG_L2_FMT_CHECK_THIN_FROM_X
int32_t driver_check_quiet_ok_get(void);
int fmt_walk_skip_dot_name(const char *name);
int check_one_need_fallback_diag(int rc, int nd, int nd_errors, int nd_warnings, int nd_infos, int direct_diag);
int xlang_path_is_absolute(const char *path);
int check_one_finalize_rc(int rc, int warn_count);
const char *driver_collect_error_kind(void);
const char *driver_collect_missing_path_code(void);
int32_t driver_collect_mode_is_check(void);
void driver_collect_mode_set(int32_t v);
int32_t check_user_passed_L_get(void);
void check_user_passed_L_set(int32_t v);
int fmt_user_ignore_count(void);
void fmt_user_ignore_count_set(int32_t v);
int fmt_path_ends_with_dot_x(const char *path);
int fmt_file_list_n(void);
void fmt_file_list_n_set(int32_t v);
const char *fmt_file_list_at(int i);
int fmt_file_list_store(const char *abs_path);
int fmt_check_lib_bufs_n(void);
void fmt_check_lib_bufs_n_set(int32_t v);
void fmt_check_lib_bufs_reset(void);
const char *fmt_check_lib_buf_at(int i);
int fmt_check_lib_buf_store(int i, const char *path);
int check_lint_fail_on_warnings(void);
int fmt_check_invoke_compile(int argc, char **check_argv);
void fmt_check_dep_clear(void);
int fmt_path_stat_kind(const char *path);
void check_try_append_lib_root(char **check_argv, int *n, const char *dir);
void check_init_user_lib_flags(int argc, char **argv, int path_start);
void driver_check_set_current_file(const char *path);
int driver_check_print_collected_diagnostics(const char *path);
int check_one_file(const char *path, int argc, char **argv);
int path_should_ignore(const char *path);
int file_list_push(const char *path);
void walk_dir_collect_process_child(const char *child, int is_dir, int is_reg);
void walk_dir_collect(const char *dir);
void parse_ignore_opt(const char *arg);
void file_list_clear(void);
int fmt_try_walk_if_product_subdir(const char *sub);
void check_collect_default_product_dirs(void);
void collect_paths_from_arg(const char *arg);
void check_append_repo_lib_roots(const char *path, char **check_argv, int *n);
void check_argv_append_default_libs_for_path(const char *path, char **check_argv, int *n);
const char *fmt_builtin_ignore_at(int i);
const char *fmt_default_product_sub_at(int i);
const char *driver_fmt_check_lit_check_error(void);
const char *driver_fmt_check_lit_fmt_error(void);
const char *driver_fmt_check_lit_chk002(void);
const char *driver_fmt_check_lit_fmt001(void);
#endif

extern int driver_fmt_one_file(const uint8_t *path, int path_len);
extern int run_compiler_c(int argc, char **argv);
#ifdef XLANG_USE_X_PIPELINE
extern int driver_run_compiler_full(int argc, char **argv);
extern void driver_dep_seeded_clear_all(void);
#endif

/* 【Why 根源】Windows 绝对路径格式 C:/... 或 C:\...（驱动器盘符+冒号）不被 POSIX
 * path[0]=='/' 判断识别，导致 file_list_push/collect_paths_from_arg 把 Windows
 * 绝对路径当相对路径拼接到 getcwd，产生 C:\cwd/C:/abs/path 双重前缀。
 * 【Invariant】path 非空时返回 1 表示绝对路径（POSIX / 或 Windows 盘符）。
 * 【Asm/Perf】纯 ASCII 比较，零运行时开销。 */
/* G-02f-118/351：逻辑源 .x；hybrid 时 pure 由 fmt_check_cmd_thin */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int xlang_path_is_absolute(const char *path) {
    if (!path || !path[0])
        return 0;
    if (path[0] == '/')
        return 1;
#ifdef _WIN32
    if (((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z'))
        && path[1] == ':')
        return 1;
#endif
    return 0;
}
#endif





/** 单目录遍历时最多收集的 .x 路径数。 */
#define DRIVER_FMT_MAX_FILES 8192
/** 忽略规则条数（CLI --ignore + 内置）。 */
#define DRIVER_FMT_MAX_IGNORE 32

/* 冷启动 set_current_file / print 用；hybrid 时 thin.x g_check_current_file 权威 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char s_check_current_file[512];
#endif

/* 冷启动 pure _impl / public 用；hybrid 时 thin.x 字节表权威 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static const char *s_builtin_ignore[] = {
    "/.git/", "/build_asm/", "/build/", "/node_modules/", "/.cursor/", "/compiler/build_asm/",
    "/compiler/build/", "/compiler/tests/",
    /* Repo-root tests/: intentional negative fixtures; bare check is product-only. */
    "/tests/", NULL};
#endif

/**
 * 供 runtime.c 查询：check 子命令是否抑制逐文件 check OK 行。
 * pure 权威：thin.x driver_check_quiet_ok_get（恒 1）；冷启动同语义。
 * Cap residual pure：run_check 冷体用 s_check_quiet_ok；hybrid 无此 static。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
/** check 全部成功时不打印 check OK（deno check 静默成功）。 */
static int s_check_quiet_ok = 1;

int32_t driver_check_quiet_ok_get(void) {
  return 1;
}
#endif


/* 冷启动 run_fmt_impl 用；hybrid pure orch 按文件 note，无此表 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char s_unformatted_paths[DRIVER_FMT_MAX_FILES][512];
static int s_unformatted_count;
#endif

/* Cap residual pure：hybrid thin owns s_n_ignore + s_ignore_paths slots
 * (g_fmt_user_ignore_paths 32×256 flat); cold keeps statics. */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char s_ignore_paths[DRIVER_FMT_MAX_IGNORE][256];
static int s_n_ignore;
#endif

/* rest C leaf closed：hybrid thin owns g_fmt_check_path_bss (2×512) + pure slot.
 * Cold start keeps C static + accessor. PLATFORM: SHARED. */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char s_fmt_check_path_bss[2][512];

char *fmt_check_path_bss_slot(int which) {
    if (which < 0 || which > 1)
        return s_fmt_check_path_bss[0];
    return s_fmt_check_path_bss[which];
}
#endif /* XLANG_L2_FMT_CHECK_THIN_FROM_X */

/* Cap residual pure：hybrid thin owns s_n_files + path slots (8192×512 flat);
 * cold keeps static n + pointer table + strdup/free. */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char *s_file_list[DRIVER_FMT_MAX_FILES];
static int s_n_files;
#endif

/** check 默认 -L：cwd；用户未传 -L 时按路径追加（见 check_argv_append_default_libs_for_path）。 */
/* Cap residual pure：hybrid thin owns s_n_check_lib_bufs + s_check_lib_bufs slots
 * (g_fmt_check_lib_bufs 8×512 flat); cold keeps statics. */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static char s_check_lib_bufs[8][512];
static int s_n_check_lib_bufs;
#endif

/* Cap residual pure：hybrid thin owns s_user_passed_L / s_collect_mode; cold keeps statics. */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
static int s_user_passed_L;

typedef enum DriverCollectMode {
    DRIVER_COLLECT_MODE_FMT = 1,
    DRIVER_COLLECT_MODE_CHECK = 2,
} DriverCollectMode;

static DriverCollectMode s_collect_mode = DRIVER_COLLECT_MODE_FMT;
#else
/* Hybrid: thin owns mode/user_passed_L; rest still needs enum constants for mode_set. */
enum {
    DRIVER_COLLECT_MODE_FMT = 1,
    DRIVER_COLLECT_MODE_CHECK = 2
};
#endif

/* pure 权威：thin.x fmt_check_lib_bufs_n / n_set / reset / buf_at / buf_store；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup（H↓）。
 * Cap residual pure：hybrid thin owns path slots；cold keeps s_check_lib_bufs[].
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_check_lib_bufs_n_impl(void) {
    return s_n_check_lib_bufs;
}

int fmt_check_lib_bufs_n(void) {
    return fmt_check_lib_bufs_n_impl();
}

void fmt_check_lib_bufs_n_set(int32_t v) {
    s_n_check_lib_bufs = v < 0 ? 0 : (int)v;
}

void fmt_check_lib_bufs_reset(void) {
    fmt_check_lib_bufs_n_set(0);
}

const char *fmt_check_lib_buf_at(int i) {
    if (i < 0 || i >= 8)
        return NULL;
    return s_check_lib_bufs[i];
}

int fmt_check_lib_buf_store(int i, const char *path) {
    if (i < 0 || i >= 8 || !path)
        return 0;
    snprintf(s_check_lib_bufs[i], sizeof s_check_lib_bufs[0], "%s", path);
    return 1;
}
#endif

/* pure 权威：thin.x driver_collect_mode_is_check / driver_collect_mode_set；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int32_t driver_collect_mode_is_check_impl(void) {
    return s_collect_mode == DRIVER_COLLECT_MODE_CHECK ? 1 : 0;
}

int32_t driver_collect_mode_is_check(void) {
    return driver_collect_mode_is_check_impl();
}

void driver_collect_mode_set(int32_t v) {
    s_collect_mode = (DriverCollectMode)v;
}
#endif

#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
const char *driver_fmt_check_lit_check_error(void) { return "check error"; }
const char *driver_fmt_check_lit_fmt_error(void) { return "fmt error"; }
const char *driver_fmt_check_lit_chk002(void) { return "CHK002"; }
const char *driver_fmt_check_lit_fmt001(void) { return "FMT001"; }
#endif

/* G-02f-247/351：逻辑源 .x（mode→lit）；hybrid 时由 thin 门闩 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
const char *driver_collect_error_kind(void) {
    if (driver_collect_mode_is_check())
        return driver_fmt_check_lit_check_error();
    return driver_fmt_check_lit_fmt_error();
}

const char *driver_collect_missing_path_code(void) {
    if (driver_collect_mode_is_check())
        return driver_fmt_check_lit_chk002();
    return driver_fmt_check_lit_fmt001();
}
#endif

/* G-02f-247：ignore 槽访问（.x path_should_ignore pure） */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
const char *fmt_builtin_ignore_at(int i) {
    int n = 0;
    while (s_builtin_ignore[n])
        n++;
    if (i < 0 || i >= n)
        return NULL;
    return s_builtin_ignore[i];
}
#endif

/* pure 权威：thin.x fmt_user_ignore_count / count_set / at / parse_ignore_opt；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 * Hybrid thin owns ignore path slots (32×256); cold keeps s_ignore_paths[][].
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_user_ignore_count_impl(void) {
    return s_n_ignore;
}

int fmt_user_ignore_count(void) {
    return fmt_user_ignore_count_impl();
}

void fmt_user_ignore_count_set(int32_t v) {
    s_n_ignore = v < 0 ? 0 : (int)v;
}

const char *fmt_user_ignore_at_impl(int i) {
    if (i < 0 || i >= fmt_user_ignore_count())
        return NULL;
    return s_ignore_paths[i];
}

const char *fmt_user_ignore_at(int i) {
    return fmt_user_ignore_at_impl(i);
}
#endif




/* pure 权威：thin.x check_user_passed_L_get / check_user_passed_L_set；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int32_t check_user_passed_L_get_impl(void) {
    return s_user_passed_L ? 1 : 0;
}

int32_t check_user_passed_L_get(void) {
    return check_user_passed_L_get_impl();
}

void check_user_passed_L_set(int32_t v) {
    s_user_passed_L = v ? 1 : 0;
}
#endif

/**
 * 若 dir 下同时存在 core/ 与 std/ 子目录，则作为仓库 lib 根注入 -L（去重）。
 * pure 权威：thin.x check_try_append_lib_root（path_stat public + pure lib path slots +
 *   xlang_ptr_slot_set）；冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void check_try_append_lib_root_impl(char **check_argv, int *n, const char *dir) {
    char core_path[560];
    char std_path[560];
    struct stat st;
    int i;
    int nb;

    if (!check_argv || !n || !dir || !dir[0])
        return;
    /* public get：hybrid thin pure BSS / 冷 seed static */
    if (check_user_passed_L_get() || *n >= 58)
        return;
    snprintf(core_path, sizeof core_path, "%s/core", dir);
    snprintf(std_path, sizeof std_path, "%s/std", dir);
    if (stat(core_path, &st) != 0 || !S_ISDIR(st.st_mode))
        return;
    if (stat(std_path, &st) != 0 || !S_ISDIR(st.st_mode))
        return;
    /* public n + at/store：冷 seed path slots */
    nb = fmt_check_lib_bufs_n();
    for (i = 0; i < nb; i++) {
        const char *slot = fmt_check_lib_buf_at(i);
        if (slot && strcmp(slot, dir) == 0)
            return;
    }
    if (nb >= 8)
        return;
    if (!fmt_check_lib_buf_store(nb, dir))
        return;
    check_argv[(*n)++] = "-L";
    check_argv[(*n)++] = (char *)fmt_check_lib_buf_at(nb);
    fmt_check_lib_bufs_n_set(nb + 1);
}

void check_try_append_lib_root(char **check_argv, int *n, const char *dir) {
    if (!check_argv || !n || !dir)
        return;
    if (!dir[0])
        return;
    if (check_user_passed_L_get())
        return;
    if (*n >= 58)
        return;
    check_try_append_lib_root_impl(check_argv, n, dir);
}
#endif




/**
 * 从 path 所在目录向上查找含 core/ + std/ 的仓库根并注入 -L。
 * pure 权威：thin.x check_append_repo_lib_roots（getcwd+字节拼+dirname 上溯+try_append）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void check_append_repo_lib_roots_impl(const char *path, char **check_argv, int *n) {
    char start[512];
    char cur[512];
    char parent[512];
    int depth;

    if (check_user_passed_L_get() || *n >= 58)
        return;
    if (!path || !path[0]) {
        if (getcwd(start, sizeof start))
            /* public：hybrid thin pure 早退 / 冷 seed public→_impl */
            check_try_append_lib_root(check_argv, n, start);
        return;
    }
    if (path[0] == '/') {
        snprintf(start, sizeof start, "%s", path);
    } else {
        if (!getcwd(start, sizeof start))
            return;
        size_t sl = strlen(start);
        snprintf(start + sl, sizeof start - sl, "/%s", path);
    }
    /* 取目录部分 */
    {
        char *slash = strrchr(start, '/');
        if (slash && slash != start)
            *slash = '\0';
        else if (slash == start)
            start[1] = '\0';
    }
    snprintf(cur, sizeof cur, "%s", start);
    for (depth = 0; depth < 8; depth++) {
        /* public：hybrid thin pure 早退 / 冷 seed public→_impl */
        check_try_append_lib_root(check_argv, n, cur);
        if (strcmp(cur, "/") == 0)
            break;
        snprintf(parent, sizeof parent, "%s", cur);
        {
            char *slash = strrchr(parent, '/');
            if (!slash)
                break;
            if (slash == parent)
                strcpy(cur, "/");
            else {
                *slash = '\0';
                snprintf(cur, sizeof cur, "%s", parent);
            }
        }
    }
}

void check_append_repo_lib_roots(const char *path, char **check_argv, int *n) {
  check_append_repo_lib_roots_impl(path, check_argv, n);
}
#endif




/**
 * 扫描 argv：用户是否已传 -L（有则不再注入默认库根）。
 * pure 权威：thin.x check_init_user_lib_flags（xlang_ptr_slot_get + user_passed_L BSS +
 *   fmt_check_lib_bufs_reset pure）；冷启动保留 _impl + public；FROM_X 剔除 pure-dup。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void check_init_user_lib_flags_impl(int argc, char **argv, int path_start) {
    int i;
    check_user_passed_L_set(0);
    fmt_check_lib_bufs_reset();
    for (i = path_start; i < argc; i++) {
        if (argv[i] && strcmp(argv[i], "-L") == 0) {
            check_user_passed_L_set(1);
            return;
        }
    }
}

void check_init_user_lib_flags(int argc, char **argv, int path_start) {
  check_init_user_lib_flags_impl(argc, argv, path_start);
}
#endif




/**
 * 按待检查文件路径注入默认 -L（在单文件路径之前）。
 * 始终注入仓库根；compiler/src 下文件再追加 compiler/src 库根（裸 import lexer/token）。
 * pure 权威：thin.x check_argv_append_default_libs_for_path（getcwd + try_append public +
 *   path_stat public + pure lib path slots + xlang_ptr_slot_set）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-408：冷启动 _impl；hybrid thin pure 全量 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void check_argv_append_default_libs_for_path_impl(const char *path, char **check_argv, int *n) {
    char cwd_buf[512];
    char cs[560];
    struct stat st;
    int nb;

    if (check_user_passed_L_get() || *n >= 58)
        return;
    check_append_repo_lib_roots(path, check_argv, n);
    if (!getcwd(cwd_buf, sizeof cwd_buf))
        return;
    /* public：hybrid thin pure try_append / 冷 seed public→_impl */
    check_try_append_lib_root(check_argv, n, cwd_buf);
    /* wave1222: accept both "compiler/src/" and bare "compiler" (the natural
     * `xlang check compiler` invocation). Previously only "compiler/src/"
     * triggered lib_root injection, leaving cross-subdir imports unresolved. */
    if (path && (strstr(path, "compiler/src/") || strstr(path, "compiler")) && *n < 56) {
        snprintf(cs, sizeof cs, "%s/compiler/src", cwd_buf);
        if (stat(cs, &st) == 0 && S_ISDIR(st.st_mode)) {
            /* public n + pure/hybrid path slots via at/store */
            nb = fmt_check_lib_bufs_n();
            if (nb < 8 && fmt_check_lib_buf_store(nb, cs)) {
                check_argv[(*n)++] = "-L";
                check_argv[(*n)++] = (char *)fmt_check_lib_buf_at(nb);
                fmt_check_lib_bufs_n_set(nb + 1);
            }
        }
        if (*n < 56) /* always inject compiler/src/asm when under compiler/ (platform.elf) */ {
            snprintf(cs, sizeof cs, "%s/compiler/src/asm", cwd_buf);
            if (stat(cs, &st) == 0 && S_ISDIR(st.st_mode)) {
                nb = fmt_check_lib_bufs_n();
                if (nb < 8 && fmt_check_lib_buf_store(nb, cs)) {
                    check_argv[(*n)++] = "-L";
                    check_argv[(*n)++] = (char *)fmt_check_lib_buf_at(nb);
                    fmt_check_lib_bufs_n_set(nb + 1);
                }
            }
        }
    }
}

void check_argv_append_default_libs_for_path(const char *path, char **check_argv, int *n) {
  check_argv_append_default_libs_for_path_impl(path, check_argv, n);
}
#endif




/**
 * XLANG_LINT_CI_FAIL_ON=warn 时 warning 层诊断亦令 check 非零退出。
 * wave234 G.7: env via link_abi_getenv (not raw getenv).
 */
/* pure 权威：thin.x check_lint_fail_on_warnings；冷启动保留 _impl + public */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int check_lint_fail_on_warnings_impl(void) {
  /* wave234 G.7: XLANG_LINT_CI_FAIL_ON via link_abi_getenv (not raw getenv). */
  const char *v = link_abi_getenv("XLANG_LINT_CI_FAIL_ON");
  return v && (strcmp(v, "warn") == 0 || strcmp(v, "warning") == 0);
}

int check_lint_fail_on_warnings(void) {
  return check_lint_fail_on_warnings_impl();
}
#endif



/**
 * 单文件 check：X pipeline 走 driver_run_compiler_full，xlang-c 走 run_compiler_c。
 * pure 分派权威：thin.x fmt_check_invoke_compile → driver_run_compiler_full；
 * 冷启动保留 _impl + public（#ifdef 双路径）；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_check_invoke_compile_impl(int argc, char **check_argv) {
#ifdef XLANG_USE_X_PIPELINE
    return driver_run_compiler_full(argc, check_argv);
#else
    return run_compiler_c(argc, check_argv);
#endif
}

int fmt_check_invoke_compile(int argc, char **check_argv) {
  return fmt_check_invoke_compile_impl(argc, check_argv);
}
#endif




/**
 * check 批次结束后清理 dep 槽（仅 X pipeline 需要）。
 * pure 分派权威：thin.x fmt_check_dep_clear → driver_dep_seeded_clear_all；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void fmt_check_dep_clear_impl(void) {
#ifdef XLANG_USE_X_PIPELINE
    driver_dep_seeded_clear_all();
#endif
}

void fmt_check_dep_clear(void) {
  fmt_check_dep_clear_impl();
}
#endif




/**
 * 记录当前 check 的源文件路径，供诊断前缀使用。
 * pure 权威：thin.x driver_check_set_current_file（512B BSS 字节拷贝）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void driver_check_set_current_file_impl(const char *path) {
    if (!path) {
        s_check_current_file[0] = '\0';
        return;
    }
    snprintf(s_check_current_file, sizeof s_check_current_file, "%s", path);
}

void driver_check_set_current_file(const char *path) {
  driver_check_set_current_file_impl(path);
}
#endif

/**
 * 将 lsp_diag 收集器中的条目打印为 deno 风格行；返回条数。
 * pure 权威：thin.x driver_check_print_collected_diagnostics → lsp_diag_print_stderr_human；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int driver_check_print_collected_diagnostics_impl(const char *path) {
    extern int lsp_diag_enabled;
    (void)lsp_diag_enabled;
    return lsp_diag_print_stderr_human(path ? path : s_check_current_file);
}

int driver_check_print_collected_diagnostics(const char *path) {
  return driver_check_print_collected_diagnostics_impl(path);
}
#endif

/**
 * 路径是否应忽略（内置 + --ignore 子串匹配）。
 * pure 权威：thin.x path_should_ignore；冷启动保留 _impl + public 门闩。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int path_should_ignore_impl(const char *path) {
    int i;
    int n;
    if (!path)
        return 1;
    for (i = 0;; i++) {
        const char *b = fmt_builtin_ignore_at(i);
        if (!b)
            break;
        if (strstr(path, b))
            return 1;
    }
    n = fmt_user_ignore_count();
    for (i = 0; i < n; i++) {
        const char *u = fmt_user_ignore_at_impl(i);
        if (u && u[0] && strstr(path, u))
            return 1;
    }
    return 0;
}

int path_should_ignore(const char *path) {
  return path_should_ignore_impl(path);
}
#endif




/* pure 权威：thin.x fmt_path_ends_with_dot_x；冷启动保留 _impl + public */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_path_ends_with_dot_x_impl(const char *path) {
    size_t len;
    if (!path)
        return 0;
    len = strlen(path);
    if (len < 2)
        return 0;
    return path[len - 2] == '.' && path[len - 1] == 'x';
}

int fmt_path_ends_with_dot_x(const char *path) {
    return fmt_path_ends_with_dot_x_impl(path);
}
#endif

/* pure 权威：thin.x fmt_file_list_n / n_set / at / store / clear；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup（H↓）。
 * Cap residual pure：hybrid thin owns 8192×512 path slots；cold keeps s_file_list[] + strdup.
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_file_list_n_impl(void) {
    return s_n_files;
}

int fmt_file_list_n(void) {
    return fmt_file_list_n_impl();
}

void fmt_file_list_n_set(int32_t v) {
    s_n_files = v < 0 ? 0 : (int)v;
}

const char *fmt_file_list_at(int i) {
    int n = fmt_file_list_n();
    if (i < 0 || i >= n)
        return NULL;
    return s_file_list[i];
}

/* Cold Cap residual path: strdup into s_file_list[]; hybrid pure uses flat BSS store. */
int fmt_file_list_store_impl(const char *abs_path) {
    int n = fmt_file_list_n();
    if (!abs_path || n >= DRIVER_FMT_MAX_FILES)
        return -1;
    s_file_list[n] = strdup(abs_path);
    if (!s_file_list[n])
        return -1;
    fmt_file_list_n_set(n + 1);
    return 0;
}

int fmt_file_list_store(const char *abs_path) {
    return fmt_file_list_store_impl(abs_path);
}
#endif

/* pure 权威：thin.x fmt_path_resolve_abs（getcwd+字节拼/拷贝；512B BSS）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）；
 * 返回静态缓冲指针（勿 free；与 thin g_resolve_abs_buf 同语义）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
const char *fmt_path_resolve_abs_impl(const char *path) {
    static char ab[512];
    if (!path)
        return NULL;
    if (!xlang_path_is_absolute(path)) {
        if (!getcwd(ab, sizeof ab))
            return NULL;
        size_t n = strlen(ab);
        if (n + 1 + strlen(path) >= sizeof ab)
            return NULL;
        ab[n] = '/';
        strcpy(ab + n + 1, path);
    } else {
        snprintf(ab, sizeof ab, "%s", path);
    }
    return ab;
}

const char *fmt_path_resolve_abs(const char *path) {
    return fmt_path_resolve_abs_impl(path);
}
#endif

/**
 * 将相对/绝对路径加入待处理列表（去重由调用方保证顺序）。
 * pure 编排权威：thin.x file_list_push；冷启动保留 _impl + public。
 * store：public fmt_file_list_store（hybrid thin pure / 冷 seed→strdup _impl）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int file_list_push_impl(const char *path) {
    const char *abs_path;
    if (!path)
        return -1;
    if (fmt_file_list_n() >= DRIVER_FMT_MAX_FILES)
        return -1;
    abs_path = fmt_path_resolve_abs_impl(path);
    if (!abs_path)
        return -1;
    if (path_should_ignore_impl(abs_path))
        return 0;
    if (!fmt_path_ends_with_dot_x(abs_path))
        return 0;
    return fmt_file_list_store(abs_path);
}

int file_list_push(const char *path) {
  return file_list_push_impl(path);
}
#endif




/* G-02f-249：逻辑源 .x（真迁 skip '.' 名）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_walk_skip_dot_name(const char *name) {
    if (!name || !name[0])
        return 1;
    if (name[0] == '.')
        return 1;
    return 0;
}
#endif


void walk_dir_collect(const char *dir);
void walk_dir_collect_impl(const char *dir);

/* pure 权威：thin.x walk_dir_collect_process_child；冷启动保留 _impl + public */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void walk_dir_collect_process_child_impl(const char *child, int is_dir, int is_reg) {
    if (!child)
        return;
    if (path_should_ignore_impl(child))
        return;
    if (is_dir) {
        walk_dir_collect_impl(child);
        return;
    }
    if (is_reg && fmt_path_ends_with_dot_x_impl(child))
        file_list_push_impl(child);
}

void walk_dir_collect_process_child(const char *child, int is_dir, int is_reg) {
  walk_dir_collect_process_child_impl(child, is_dir, is_reg);
}
#endif

/**
 * 递归遍历目录，收集 .x 文件。
 * pure 权威：thin.x walk_dir_collect（opendir + readdir_name + path_stat classify；
 *   无 struct dirent/stat 布局）；冷启动保留本 _impl + public；
 * FROM_X 下剔除 pure-dup（H↓；ALWAYS residual 1→0）。
 *
 * 【Why 根源】dir 可能指向 fmt_path_resolve_abs 的静态/小 BSS 缓冲
 * （collect_paths_from_arg → resolve_abs → walk_dir_collect 传入；hybrid thin
 * g_resolve_abs_buf / 冷 seed static ab[512]）。
 * 循环中 file_list_push → resolve_abs 会覆盖该缓冲，
 * 导致 dir 指针内容变为上一个 .x 文件路径，snprintf 拼接出
 * "compiler/foo.x/bar.x" 这样的错误路径。拷贝到本地 dir_buf 隔离别名。
 * 【Invariant】dir_buf 在本函数栈帧内，不受下游调用影响。
 * 【Asm/Perf】单次 snprintf 拷贝，零热路径影响（目录遍历非热路径）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void walk_dir_collect_impl(const char *dir) {
    void *d;
    char *name;
    char child[768];
    char dir_buf[512];
    if (!dir)
        return;
    snprintf(dir_buf, sizeof dir_buf, "%s", dir);
    /* Cap residual 9.1.10: cold twin also uses Cap (no libc opendir). */
    d = xlang_dir_open(dir_buf);
    if (!d)
        return;
    while ((name = xlang_dir_readdir_name(d)) != NULL) {
        int is_dir = 0;
        int is_reg = 0;
        if (fmt_walk_skip_dot_name(name))
            continue;
        snprintf(child, sizeof child, "%s/%s", dir_buf, name);
        {
            struct stat st;
            if (stat(child, &st) == 0 && S_ISDIR(st.st_mode))
                is_dir = 1;
            else if (stat(child, &st) == 0 && S_ISREG(st.st_mode))
                is_reg = 1;
        }
        /* 调 public：冷 seed public→_impl path；hybrid 不编此函数 */
        walk_dir_collect_process_child(child, is_dir, is_reg);
    }
    (void)xlang_dir_close(d);
}

/* G-02f-249：逻辑源 .x（门闩）；seed 保留同语义 C 供产品 cc */
/* G-02f-407：public PREFER 时 thin → existing impl */
void walk_dir_collect(const char *dir) {
    if (!dir)
        return;
    walk_dir_collect_impl(dir);
}
#endif




/* G-02f-250：逻辑源 .x（真迁 sub 表）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
const char *fmt_default_product_sub_at(int i) {
    static const char *subs[] = {"compiler/src", "core", "std", "examples", NULL};
    int n = 0;
    while (subs[n])
        n++;
    if (i < 0 || i >= n)
        return NULL;
    return subs[i];
}
#endif

/* pure 权威：thin.x fmt_try_walk_if_product_subdir（getcwd+字节拼+stat_kind+walk）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓）；
 * cold public 与 hybrid pure 同形语义（getcwd/stat/walk）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_try_walk_if_product_subdir_impl(const char *sub) {
    char cwd[512];
    char subp[560];
    struct stat st;
    if (!sub)
        return 0;
    if (!getcwd(cwd, sizeof cwd))
        return 0;
    snprintf(subp, sizeof subp, "%s/%s", cwd, sub);
    if (stat(subp, &st) == 0 && S_ISDIR(st.st_mode)) {
        walk_dir_collect(subp);
        return 1;
    }
    return 0;
}

int fmt_try_walk_if_product_subdir(const char *sub) {
  return fmt_try_walk_if_product_subdir_impl(sub);
}
#endif

/**
 * pure 权威：thin.x fmt_walk_cwd_fallback（getcwd + walk_dir_collect public）；
 * 冷启动保留 _impl；FROM_X 下剔除 pure-dup _impl（H↓）；
 * cold orch 与 hybrid pure orch 同形：调 public 语义（cold 时 _impl 即 public 体）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void fmt_walk_cwd_fallback_impl(void) {
    char cwd[512];
    if (!getcwd(cwd, sizeof cwd))
        return;
    walk_dir_collect(cwd);
}

void fmt_walk_cwd_fallback(void) {
    fmt_walk_cwd_fallback_impl();
}
#endif

/**
 * Bare `xlang check` (no path args): recursively collect all *.x under cwd.
 * Builtin path_should_ignore still skips .git/build/node_modules/compiler/tests
 * etc. Name kept for ABI stability (was product-subdir-only).
 * pure 编排权威：thin.x check_collect_default_product_dirs；
 * 冷启动保留 _impl + public；cwd walk 调 public fmt_walk_cwd_fallback。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void check_collect_default_product_dirs_impl(void) {
    fmt_walk_cwd_fallback();
}

void check_collect_default_product_dirs(void) {
  check_collect_default_product_dirs_impl();
}
#endif




/* G-02f-249：-1 不可访问；1 目录；0 文件/其它 */
/* pure 权威：thin.x fmt_path_stat_kind（opendir + access F_OK；无 struct stat 布局）；
 * 冷启动保留 libc stat + S_ISDIR；FROM_X 下剔除 pure-dup（H↓；ALWAYS residual 2→1）。 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int fmt_path_stat_kind_impl(const char *path) {
    struct stat st;
    if (!path)
        return -1;
    if (stat(path, &st) != 0)
        return -1;
    if (S_ISDIR(st.st_mode))
        return 1;
    return 0;
}

int fmt_path_stat_kind(const char *path) {
  return fmt_path_stat_kind_impl(path);
}
#endif

/* pure 权威：thin.x collect_paths_missing_diag_pure（字节拼 msg + diag_report_with_code）；
 * 冷启动保留 _impl（reportf）；FROM_X 下剔除 pure-dup _impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void collect_paths_missing_diag_impl(const char *path) {
    diag_reportf_with_code(path, 0, 0, driver_collect_error_kind(),
                           driver_collect_missing_path_code(), NULL,
                           "cannot access path '%s'", path);
}
#endif

/**
 * 解析路径参数：文件直接加入；目录递归收集。
 * pure 编排权威：thin.x collect_paths_from_arg；
 * 冷启动保留 _impl + public；stat/resolve/missing-diag 🔒 Cap residual。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void collect_paths_from_arg_impl(const char *arg) {
    int k;
    if (!arg)
        return;
    /* 调 public Cap 门闩：与 thin pure 同形 */
    k = fmt_path_stat_kind(arg);
    if (k < 0) {
        collect_paths_missing_diag_impl(arg);
        return;
    }
    if (k == 1) {
        const char *base = fmt_path_resolve_abs(arg);
        if (base)
            walk_dir_collect(base);
        return;
    }
    file_list_push(arg);
}

void collect_paths_from_arg(const char *arg) {
  collect_paths_from_arg_impl(arg);
}
#endif




/**
 * 解析 --ignore=a,b,c 写入 ignore path slots。
 * pure 权威：thin.x parse_ignore_opt（前缀 + token 写槽）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void parse_ignore_opt_impl(const char *arg) {
    char buf[512];
    char *p;
    char *tok;
    int n;
    if (!arg || strncmp(arg, "--ignore=", 9) != 0)
        return;
    snprintf(buf, sizeof buf, "%s", arg + 9);
    p = buf;
    n = fmt_user_ignore_count();
    while (p && *p && n < DRIVER_FMT_MAX_IGNORE) {
        tok = p;
        while (*p && *p != ',')
            p++;
        if (*p)
            *p++ = '\0';
        if (tok[0]) {
            snprintf(s_ignore_paths[n], sizeof s_ignore_paths[0], "%s", tok);
            n++;
            fmt_user_ignore_count_set(n);
        }
    }
}

void parse_ignore_opt(const char *arg) {
    if (!arg)
        return;
    if (strncmp(arg, "--ignore=", 9) != 0)
        return;
    parse_ignore_opt_impl(arg);
}
#endif




/**
 * Clear collected file list.
 * pure 权威：thin.x file_list_clear（n=0；hybrid flat slots 无 free）；
 * 冷启动 free s_file_list[] + n=0；FROM_X 下剔除 pure-dup clear_impl（H↓）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
void file_list_clear_impl(void) {
    int i;
    int n = fmt_file_list_n();
    for (i = 0; i < n; i++)
        free(s_file_list[i]);
    fmt_file_list_n_set(0);
}

void file_list_clear(void) {
  file_list_clear_impl();
}
#endif




/**
 * 运行 xlang fmt（deno fmt 语义）。
 * pure 权威：thin.x driver_run_fmt（full orch + public APIs）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓；ALWAYS residual 4→3）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int driver_run_fmt_impl(int argc, char **argv) {
    int i;
    int fail_fast = 0;
    int any_path_arg = 0;
    int failed = 0;
    int formatted = 0;
    int check_mode = 0;

    /* public n：hybrid thin pure BSS / 冷 seed static */
    fmt_user_ignore_count_set(0);
    s_unformatted_count = 0;
    /* public set：hybrid thin pure BSS / 冷 seed static */
    driver_collect_mode_set(DRIVER_COLLECT_MODE_FMT);
    /* public clear：hybrid thin pure n=0 / 冷 seed free+n=0 */
    file_list_clear();

    for (i = 1; i < argc; i++) {
        if (!argv[i])
            continue;
        if (strcmp(argv[i], "--check") == 0) {
            driver_fmt_check_only_set(1);
            check_mode = 1;
            continue;
        }
        if (strcmp(argv[i], "--fail-fast") == 0) {
            fail_fast = 1;
            continue;
        }
        if (strncmp(argv[i], "--ignore=", 9) == 0) {
            /* public：hybrid thin pure 前缀 / 冷 seed public→_impl */
            parse_ignore_opt(argv[i]);
            continue;
        }
        if (argv[i][0] == '-')
            continue;
        any_path_arg = 1;
        /* public：hybrid thin pure / 冷 seed public→_impl */
        collect_paths_from_arg(argv[i]);
    }

    if (!any_path_arg) {
        char cwd[512];
        if (getcwd(cwd, sizeof cwd))
            walk_dir_collect(cwd);
    }

    /* public n：hybrid thin pure BSS / 冷 seed static */
    if (fmt_file_list_n() == 0) {
        if (any_path_arg)
            diag_report_with_code(NULL, 0, 0, "fmt error", "FMT001",
                                  "no .x files found under given path(s)", NULL);
        else
            diag_report_with_code(NULL, 0, 0, "fmt error", "FMT001",
                                  "no .x files found in current directory", NULL);
        return 1;
    }

    for (i = 0; i < fmt_file_list_n(); i++) {
        /* public at：hybrid thin pure flat slots / 冷 seed s_file_list[] */
        const char *path = fmt_file_list_at(i);
        int plen;
        int rc;
        if (!path)
            continue;
        plen = (int)strlen(path);
        rc = driver_fmt_one_file((const uint8_t *)path, plen);
        if (rc != 0) {
            if (driver_fmt_check_only_get() && s_unformatted_count < DRIVER_FMT_MAX_FILES) {
                snprintf(s_unformatted_paths[s_unformatted_count], sizeof s_unformatted_paths[0], "%s", path);
                s_unformatted_count++;
            }
            failed = 1;
            if (fail_fast)
                break;
        } else if (!driver_fmt_check_only_get()) {
            formatted++;
        }
    }

    driver_fmt_check_only_set(0);
    file_list_clear();

    if (failed && check_mode) {
        int j;
        diag_reportf_with_code(NULL, 0, 0, "fmt error", "FMT001", NULL,
                               "found %d not formatted file%s",
                               s_unformatted_count, s_unformatted_count == 1 ? "" : "s");
        for (j = 0; j < s_unformatted_count; j++)
            diag_reportf(s_unformatted_paths[j], 0, 0, "note", NULL,
                         "needs formatting: %s", s_unformatted_paths[j]);
        diag_report(NULL, 0, 0, "note",
                    "run `xlang fmt` to format these files", NULL);
        return 1;
    }

    if (failed)
        return 1;

    /* wave234 G.7: XLANG_FMT_VERBOSE via link_abi_getenv (not raw getenv). */
    if (!check_mode && formatted > 0 && link_abi_getenv("XLANG_FMT_VERBOSE"))
        diag_reportf(NULL, 0, 0, "info", NULL,
                     "Formatted %d file%s", formatted, formatted == 1 ? "" : "s");

    return 0;
}
int driver_run_fmt(int argc, char **argv) {
    return driver_run_fmt_impl(argc, argv);
}
#endif

/* G-02f-250：逻辑源 .x（真迁 fallback/lint 判定）；seed 保留同语义 C 供产品 cc */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int check_one_need_fallback_diag(int rc, int nd, int nd_errors, int nd_warnings, int nd_infos,
                                int direct_diag) {
    if (rc == 0)
        return 0;
    if (direct_diag != 0)
        return 0;
    if (nd == 0)
        return 1;
    if (nd_errors == 0 && nd_warnings == 0 && nd_infos == 0)
        return 1;
    return 0;
}
#endif


/* pure 权威：thin.x check_one_finalize_rc；冷启动保留 public 体 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int check_one_finalize_rc(int rc, int warn_count) {
    if (rc != 0)
        return rc;
    if (check_lint_fail_on_warnings_impl() && warn_count > 0)
        return 1;
    return rc;
}
#endif


/**
 * 对单个 .x 运行 check；复用 driver_run_compiler_full。
 * pure 权威：thin.x check_one_file（full body + public APIs）；
 * 冷启动保留 body_impl + public；FROM_X 下剔除 pure-dup body_impl（H↓；ALWAYS residual 3→2）。
 * G-02f-250：冷路径主体 🔒；hybrid 结果判定与编排均 pure。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int check_one_file_body_impl(const char *path, int argc, char **argv) {
    char *check_argv[64];
    XlangRuntimeFileView diag_view = {0};
    int have_diag_view = 0;
    int n = 0;
    int i;
    int rc;

    if (runtime_read_file_view(path, &diag_view) == 0) {
        diag_set_file(path, (const char *)diag_view.data, diag_view.length);
        have_diag_view = 1;
    } else {
        diag_set_file(path, NULL, 0);
    }
    lsp_diag_collect_begin();
    driver_check_diag_emitted_reset();
    /* public：hybrid thin pure BSS / 冷 seed public→_impl */
    driver_check_set_current_file(path);

    /* 每个文件独立构建 check_argv；-L 缓冲须按文件重置，否则跨文件 dedup 会漏注入仓库根。
     * public reset：hybrid thin pure BSS / 冷 seed static。 */
    fmt_check_lib_bufs_reset();

    check_argv[n++] = argv[0];
#ifdef XLANG_USE_X_PIPELINE
    check_argv[n++] = "check";
#endif
    for (i = 2; i < argc && n < 60; i++) {
        if (!argv[i])
            continue;
        if (argv[i][0] == '-') {
            check_argv[n++] = argv[i];
            if ((strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "-I") == 0 || strcmp(argv[i], "-o") == 0
                 || strcmp(argv[i], "-backend") == 0 || strcmp(argv[i], "-O") == 0)
                && i + 1 < argc)
                check_argv[n++] = argv[++i];
        } else if (strcmp(argv[i], "--fail-fast") == 0) {
            check_argv[n++] = argv[i];
        }
    }
    check_argv_append_default_libs_for_path(path, check_argv, &n);
    check_argv[n++] = (char *)path;

    driver_check_only_set(1);
    /* public：hybrid thin pure 分派 / 冷 seed public→_impl */
    rc = fmt_check_invoke_compile(n, check_argv);
    driver_check_only_set(0);

    {
        DiagContextSnapshot diag_snapshot;
        int nd;
        int nd_errors;
        int nd_warnings;
        int nd_infos;
        int direct_diag_emitted;
        if (have_diag_view)
            diag_push_file(&diag_snapshot, path, (const char *)diag_view.data, diag_view.length);
        else
            diag_push_file(&diag_snapshot, path, NULL, 0);
        nd = lsp_diag_print_stderr_human(path);
        nd_errors = lsp_diag_count_severity(1);
        nd_warnings = lsp_diag_count_severity(2);
        nd_infos = lsp_diag_count_severity(3);
        direct_diag_emitted = driver_check_diag_emitted_get();
        diag_restore(&diag_snapshot);
        if (check_one_need_fallback_diag(rc, nd, nd_errors, nd_warnings, nd_infos, direct_diag_emitted))
            diag_reportf_with_code(path, 0, 0, "check error", "CHK001", NULL,
                                   "check failed: %s", path);
        /* 【Why 根源】recovery/typeck 错误经 lsp_diag 打印时 compile rc 可能仍为 0（假绿）。 */
        if (nd_errors > 0)
            rc = 1;
        rc = check_one_finalize_rc(rc, nd_warnings);
    }

    lsp_diag_collect_end();
    if (have_diag_view)
        runtime_release_file_view(&diag_view);
    /* public：hybrid thin pure 分派 / 冷 seed public→_impl */
    fmt_check_dep_clear();
    return rc;
}

/* pure 门闩权威：thin.x check_one_file full body；
 * 冷启动保留 pure-dup check_one_file_impl；FROM_X 下剔除（H↓）。 */
int check_one_file_impl(const char *path, int argc, char **argv) {
    if (!path || !argv || argc <= 0)
        return -1;
    return check_one_file_body_impl(path, argc, argv);
}

int check_one_file(const char *path, int argc, char **argv) {
  return check_one_file_impl(path, argc, argv);
}
#endif




/* Defined with spinner block below; cold _impl installs early for single-file too. */
void check_install_interrupt_handlers(void);

/**
 * 运行 xlang check（deno check 语义：多文件/目录，失败打印诊断）。
 * pure 权威：thin.x driver_run_compiler_check（full orch + public APIs）；
 * 冷启动保留 _impl + public；FROM_X 下剔除 pure-dup _impl（H↓；ALWAYS residual 5→4）。
 */
#ifndef XLANG_L2_FMT_CHECK_THIN_FROM_X
int driver_run_compiler_check_impl(int argc, char **argv) {
    int i;
    int fail_fast = 0;
    int any_path = 0;
    int failed = 0;
    int checked = 0;
    int path_start = 1;

    /* Ctrl+C / SIGTERM force-exit even when stuck in parse/typeck or join.
     * PLATFORM: SHARED — also installed from spin_start (multi-file). */
    check_install_interrupt_handlers();

    s_check_quiet_ok = 1;
    /* public set：hybrid thin pure BSS / 冷 seed static */
    driver_collect_mode_set(DRIVER_COLLECT_MODE_CHECK);
    /* public clear：hybrid thin pure n=0 / 冷 seed free+n=0 */
    file_list_clear();

    /* main.x 传入 argv[1]=check；xlang-c 已 drop 子命令时 argv[1] 为首个路径。 */
    if (argc >= 2 && argv[1] && strcmp(argv[1], "check") == 0)
        path_start = 2;

    /* public：hybrid thin pure init / 冷 seed public→_impl */
    check_init_user_lib_flags(argc, argv, path_start);

    for (i = path_start; i < argc; i++) {
        if (!argv[i])
            continue;
        if (strcmp(argv[i], "--fail-fast") == 0) {
            fail_fast = 1;
            continue;
        }
        if (strncmp(argv[i], "--ignore=", 9) == 0) {
            /* public：hybrid thin pure 前缀 / 冷 seed public→_impl */
            parse_ignore_opt(argv[i]);
            continue;
        }
        if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "-I") == 0 || strcmp(argv[i], "-o") == 0) {
            i++;
            continue;
        }
        if (strcmp(argv[i], "-backend") == 0 || strcmp(argv[i], "-O") == 0) {
            i++;
            continue;
        }
        if (argv[i][0] == '-')
            continue;
        any_path = 1;
        /* public：hybrid thin pure / 冷 seed public→_impl */
        collect_paths_from_arg(argv[i]);
    }

    /*
     * 无路径：仅 check 产品目录（compiler/src、core、std、examples），避免扫 tests 负例。
     * 有路径时仍由 collect_paths_from_arg 处理（可显式 xlang check tests/...）。
     */
    if (!any_path)
        check_collect_default_product_dirs();

    /* public n：hybrid thin pure BSS / 冷 seed static */
    if (fmt_file_list_n() == 0) {
        if (any_path)
            diag_report_with_code(NULL, 0, 0, "check error", "CHK002",
                                  "no .x files found under given path(s)", NULL);
        else
            diag_report_with_code(NULL, 0, 0, "check error", "CHK002",
                                  "no .x files found in current directory", NULL);
        return 1;
    }

    for (i = 0; i < fmt_file_list_n(); i++) {
        /* public at + one_file：hybrid thin pure at / 冷 seed s_file_list */
        const char *path = fmt_file_list_at(i);
        if (!path)
            continue;
        if (check_one_file(path, argc, argv) != 0) {
            failed = 1;
            if (fail_fast)
                break;
        }
        checked++;
    }

    file_list_clear();

    if (failed)
        return 1;

    if (!s_check_quiet_ok && checked > 0)
        diag_reportf(NULL, 0, 0, "info", NULL,
                     "check OK (%d file%s)", checked, checked == 1 ? "" : "s");

    return 0;
}

int driver_run_compiler_check(int argc, char **argv) {
    return driver_run_compiler_check_impl(argc, argv);
}
#endif

int fmt_check_cmd_slice_marker(void) {
    return 1;
}

/* ============================================================================
 * Multi-file check progress spinner (braille circle + relative path).
 * Called from thin.x check_progress_show/break/resume/finish.
 *
 * Frames: UTF-8 braille circle ⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏ (1 display column each).
 * Erase: CSI K after path so shorter paths never leave trail (no space pad).
 *
 * Animation backend:
 *  - Real pthread (macOS / -lc product): spinner thread + usleep.
 *  - Linux freestanding (bootstrap_nostdlib pthread stub is sync): fork child
 *    + MAP_SHARED run/pause flags. Parent never runs the infinite loop.
 *  - Windows / fork+mmap failure: single static frame.
 *
 * Ctrl+C / SIGTERM:
 *  - check_install_interrupt_handlers() installs async-signal-safe handlers
 *    that stop the spinner (no pthread_join) and _exit(128+sig).
 *  - Needed so multi-file check stuck in parse/typeck (or large-stack
 *    pthread_join) still dies immediately when the user hits Ctrl+C;
 *    spinner thread alone keeps animating and looks "unkillable" if the
 *    process does not exit.
 *  - Respects SIG_IGN (shell background job control).
 *
 * PLATFORM: SHARED UI; LINUX freestanding uses fork path; MACOS pthread.
 * ============================================================================ */
#ifndef _WIN32
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#endif
#ifdef _WIN32
#include <signal.h>
#endif

/*
 * When product links bootstrap_nostdlib_stubs, pthread_create runs the start
 * routine synchronously — an infinite spinner would hang forever. Strong
 * symbol there returns 1. Weak default here returns 0 for -lc/-lSystem builds
 * that do not link the nostdlib stubs object.
 * PLATFORM: SHARED.
 */
__attribute__((weak)) int bootstrap_nostdlib_pthread_is_stub(void) {
    return 0;
}

/*
 * Shared control for fork-mode spinner child.
 * path[] lives here so one long-lived child can animate every multi-file path
 * without re-forking after the parent heap has grown to multi-GB (COW fork of
 * a huge RSS was the Ubuntu hang root: waitpid stuck / shell process-group
 * wait on an orphan spinner after summary).
 * PLATFORM: LINUX freestanding (MAP_SHARED); MACOS uses pthread path.
 */
typedef struct {
    volatile int run;
    volatile int pause;
    volatile int frame;
    char path[512];
} ck_spin_sh;

static volatile int g_ck_spin_run = 0;
static volatile int g_ck_spin_pause = 0;
static char g_ck_spin_path[512];
static int g_ck_spin_shown = 0; /* 1 if a spinner line is active (needs \n) */
static int g_ck_spin_frame = 0;
static int g_ck_interrupt_installed = 0;
#ifndef _WIN32
static int g_ck_spin_have_tid = 0;
static pthread_t g_ck_spin_tid;
static pid_t g_ck_spin_pid = 0;
static ck_spin_sh *g_ck_spin_sh = NULL;
#endif

/*
 * Async-signal-safe interrupt path for `xlang check`.
 * PLATFORM: SHARED — POSIX signal(2)/sigaction; Windows uses signal().
 * Does not pthread_join/waitpid (not async-safe); kills fork spinner child if any.
 */
static void check_interrupt_handler(int sig) {
    const char msg[] = "\ncheck: interrupted\n";
    (void)xlang_io_write(2, msg, sizeof(msg) - 1);
    g_ck_spin_run = 0;
    g_ck_spin_pause = 0;
#ifndef _WIN32
    if (g_ck_spin_sh) {
        g_ck_spin_sh->run = 0;
        g_ck_spin_sh->pause = 0;
    }
    if (g_ck_spin_pid > 0) {
        (void)kill(g_ck_spin_pid, SIGKILL);
        /* Do not waitpid here (not async-signal-safe); parent is _exit-ing. */
        g_ck_spin_pid = 0;
    }
#endif
    if (g_ck_spin_shown) {
        (void)xlang_io_write(2, "\n", 1);
        g_ck_spin_shown = 0;
    }
    /* 128+sig is shell convention for death-by-signal (SIGINT → 130). */
    _exit(128 + (sig & 127));
}

/* Install SIGINT/SIGTERM handlers once per process for check.
 * Skip if currently SIG_IGN so shell background jobs keep job-control semantics.
 * PLATFORM: SHARED. */
void check_install_interrupt_handlers(void) {
    if (g_ck_interrupt_installed)
        return;
    g_ck_interrupt_installed = 1;
#ifndef _WIN32
    {
        struct sigaction sa;
        struct sigaction old;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = check_interrupt_handler;
        sigemptyset(&sa.sa_mask);
        /* No SA_RESTART: long syscalls should surface EINTR when possible. */
        sa.sa_flags = 0;
        if (sigaction(SIGINT, NULL, &old) == 0 && old.sa_handler != SIG_IGN)
            (void)sigaction(SIGINT, &sa, NULL);
        if (sigaction(SIGTERM, NULL, &old) == 0 && old.sa_handler != SIG_IGN)
            (void)sigaction(SIGTERM, &sa, NULL);
    }
#else
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        (void)signal(SIGINT, check_interrupt_handler);
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
        (void)signal(SIGTERM, check_interrupt_handler);
#endif
}

/* Braille circle spinner (UTF-8). 10 frames; each is 3 bytes, width 1 cell. */
static const char *const g_ck_spin_frames[10] = {
    "\xE2\xA0\x8B", /* ⠋ */
    "\xE2\xA0\x99", /* ⠙ */
    "\xE2\xA0\xB9", /* ⠹ */
    "\xE2\xA0\xB8", /* ⠸ */
    "\xE2\xA0\xBC", /* ⠼ */
    "\xE2\xA0\xB4", /* ⠴ */
    "\xE2\xA0\xA6", /* ⠦ */
    "\xE2\xA0\xA7", /* ⠧ */
    "\xE2\xA0\x87", /* ⠇ */
    "\xE2\xA0\x8F", /* ⠏ */
};

/* Copy path into parent-local buffer and (when present) shared path for child. */
static void check_progress_spin_set_path(const char *path) {
    int i;
    g_ck_spin_path[0] = 0;
    if (path) {
        for (i = 0; i < 511 && path[i]; i++)
            g_ck_spin_path[i] = path[i];
        g_ck_spin_path[i] = 0;
    }
#ifndef _WIN32
    if (g_ck_spin_sh) {
        for (i = 0; i < 511 && g_ck_spin_path[i]; i++)
            g_ck_spin_sh->path[i] = g_ck_spin_path[i];
        g_ck_spin_sh->path[i] = 0;
    }
#endif
}

static void check_progress_spin_write_frame(void) {
    const char *glyph;
    const char *path_src;
    char buf[640];
    int at = 0;
    int i;
    int gi;
    int frame;

#ifndef _WIN32
    if (g_ck_spin_sh)
        frame = g_ck_spin_sh->frame++;
    else
#endif
    {
        frame = g_ck_spin_frame++;
    }

    glyph = g_ck_spin_frames[frame % 10];

    buf[at++] = '\r';
    /* UTF-8 braille glyph (3 bytes) */
    for (gi = 0; glyph[gi] && at < 8; gi++)
        buf[at++] = glyph[gi];
    buf[at++] = ' ';

    /* Prefer shared path so long-lived fork child tracks parent path updates. */
    path_src = g_ck_spin_path;
#ifndef _WIN32
    if (g_ck_spin_sh)
        path_src = g_ck_spin_sh->path;
#endif
    for (i = 0; i < 511 && path_src[i]; i++) {
        if (at >= 620)
            break;
        buf[at++] = path_src[i];
    }
    /* Erase to end of line — works across fork (no shared width state). */
    if (at + 3 < 640) {
        buf[at++] = '\033';
        buf[at++] = '[';
        buf[at++] = 'K';
    }

    if (at > 0) {
        (void)xlang_io_write(2, buf, (size_t)at);
        g_ck_spin_shown = 1;
    }
}

#ifndef _WIN32
static int check_progress_spin_live_run(void) {
    if (g_ck_spin_sh)
        return g_ck_spin_sh->run != 0;
    return g_ck_spin_run != 0;
}

static int check_progress_spin_live_pause(void) {
    if (g_ck_spin_sh)
        return g_ck_spin_sh->pause != 0;
    return g_ck_spin_pause != 0;
}

static void *check_progress_spin_thread(void *arg) {
    (void)arg;
    while (check_progress_spin_live_run()) {
        if (!check_progress_spin_live_pause())
            check_progress_spin_write_frame();
        /* ~80ms per frame — readable without flooding stderr */
        (void)usleep(80000);
    }
    return NULL;
}

/* Linux freestanding: long-lived child animates until shared run==0, then _exit.
 * Reads path from MAP_SHARED so parent can advance files without re-fork.
 * Exits if parent dies (reparent → getppid()==1).
 * PLATFORM: LINUX freestanding (fork path); MACOS product uses pthread. */
static void check_progress_spin_fork_child(void) {
    while (check_progress_spin_live_run()) {
        if (getppid() <= 1)
            _exit(0);
        if (!check_progress_spin_live_pause())
            check_progress_spin_write_frame();
        (void)usleep(80000);
    }
    _exit(0);
}

static int check_progress_spin_ensure_shared(void) {
    void *p;
    if (g_ck_spin_sh)
        return 0;
    /* MAP_SHARED|MAP_ANONYMOUS — needed so parent stop/path updates reach child. */
    p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED || p == (void *)(intptr_t)-1)
        return -1;
    g_ck_spin_sh = (ck_spin_sh *)p;
    g_ck_spin_sh->run = 0;
    g_ck_spin_sh->pause = 0;
    g_ck_spin_sh->frame = 0;
    g_ck_spin_sh->path[0] = 0;
    return 0;
}

/*
 * Reap fork spinner: cooperative run=0 first, then SIGKILL + waitpid.
 * Must not leave a live child in the shell process group after summary
 * (interactive shell then appears hung even though parent returned).
 * PLATFORM: LINUX freestanding / POSIX waitpid+kill.
 */
static void check_progress_spin_reap_fork_child(pid_t pid) {
    int st = 0;
    pid_t w;
    int tries;
    if (pid <= 0)
        return;
    for (tries = 0; tries < 5; tries++) {
        w = waitpid(pid, &st, WNOHANG);
        if (w == pid)
            return;
        if (w < 0) {
            /* ECHILD: already reaped (or never a child). */
            return;
        }
        (void)usleep(20000); /* 20ms; child usleep is 80ms — ~100ms window */
    }
    (void)kill(pid, SIGKILL);
    for (;;) {
        w = waitpid(pid, &st, 0);
        if (w == pid || w < 0)
            return;
    }
}
#endif

/* Join spinner worker without committing a newline (next file overwrites via \r). */
static void check_progress_spin_join_only(void) {
#ifndef _WIN32
    if (g_ck_spin_have_tid) {
        if (g_ck_spin_sh)
            g_ck_spin_sh->run = 0;
        g_ck_spin_run = 0;
        (void)pthread_join(g_ck_spin_tid, NULL);
        g_ck_spin_have_tid = 0;
    } else if (g_ck_spin_pid > 0) {
        pid_t pid = g_ck_spin_pid;
        if (g_ck_spin_sh)
            g_ck_spin_sh->run = 0;
        g_ck_spin_run = 0;
        g_ck_spin_pid = 0;
        check_progress_spin_reap_fork_child(pid);
    } else {
        g_ck_spin_run = 0;
        if (g_ck_spin_sh)
            g_ck_spin_sh->run = 0;
    }
#else
    g_ck_spin_run = 0;
#endif
    g_ck_spin_pause = 0;
#ifndef _WIN32
    if (g_ck_spin_sh)
        g_ck_spin_sh->pause = 0;
#endif
}

void check_progress_spin_stop(void) {
    check_progress_spin_join_only();
    /* Commit spinner line so the summary/next output starts on a new line. */
    if (g_ck_spin_shown) {
        (void)xlang_io_write(2, "\n", 1);
        g_ck_spin_shown = 0;
    }
}

void check_progress_spin_start(const char *path) {
    /* Ensure Ctrl+C works even if thin.x forgot to install (defense in depth). */
    check_install_interrupt_handlers();

    check_progress_spin_set_path(path);
    g_ck_spin_pause = 0;
    g_ck_spin_run = 1;

#ifndef _WIN32
    /*
     * Long-lived worker: if a spinner child/thread is already alive, only update
     * the shared path (no join/re-fork). Re-forking after multi-GB heap COW was
     * the Ubuntu bare-check hang root.
     * PLATFORM: LINUX freestanding — one fork + MAP_SHARED path/control.
     * PLATFORM: MACOS / libc — real pthread (reuse if already running).
     */
    if (g_ck_spin_have_tid || g_ck_spin_pid > 0) {
        if (g_ck_spin_sh) {
            g_ck_spin_sh->run = 1;
            g_ck_spin_sh->pause = 0;
        }
        /* Parent paints immediately so path change is visible even mid-usleep. */
        check_progress_spin_write_frame();
        return;
    }

    if (bootstrap_nostdlib_pthread_is_stub() != 0) {
        if (check_progress_spin_ensure_shared() == 0) {
            /* Re-copy path now that shared page exists. */
            check_progress_spin_set_path(path);
            g_ck_spin_sh->run = 1;
            g_ck_spin_sh->pause = 0;
            g_ck_spin_sh->frame = 0;
            {
                pid_t child = fork();
                if (child == 0) {
                    /*
                     * Leave shell foreground process group so a stuck spinner
                     * cannot hold the interactive shell after parent exits.
                     * PLATFORM: LINUX — setsid freestanding stub or libc.
                     */
                    (void)setsid();
                    check_progress_spin_fork_child();
                    _exit(0);
                } else if (child > 0) {
                    g_ck_spin_pid = child;
                    check_progress_spin_write_frame();
                    return;
                }
            }
        }
        /* fork/mmap failed: single static frame (still better than hang). */
        g_ck_spin_run = 0;
        if (g_ck_spin_sh)
            g_ck_spin_sh->run = 0;
        check_progress_spin_write_frame();
    } else if (pthread_create(&g_ck_spin_tid, NULL, check_progress_spin_thread, NULL) == 0) {
        g_ck_spin_have_tid = 1;
        check_progress_spin_write_frame();
    } else {
        /* Real pthread create failed: single static frame. */
        g_ck_spin_run = 0;
        check_progress_spin_write_frame();
    }
#else
    g_ck_spin_run = 0;
    check_progress_spin_write_frame();
#endif
}

void check_progress_spin_pause(void) {
    g_ck_spin_pause = 1;
#ifndef _WIN32
    if (g_ck_spin_sh)
        g_ck_spin_sh->pause = 1;
#endif
    /* End the active spinner line so multi-line diagnostics are clean. */
    if (g_ck_spin_shown) {
        (void)xlang_io_write(2, "\n", 1);
        g_ck_spin_shown = 0;
    }
}

void check_progress_spin_resume(void) {
    int live = 0;
#ifndef _WIN32
    live = (g_ck_spin_have_tid || g_ck_spin_pid > 0) && check_progress_spin_live_run();
#else
    live = g_ck_spin_run != 0;
#endif
    if (!live) {
        /* Threadless/forkless fallback: redraw one frame. */
        check_progress_spin_write_frame();
        return;
    }
    g_ck_spin_pause = 0;
#ifndef _WIN32
    if (g_ck_spin_sh)
        g_ck_spin_sh->pause = 0;
#endif
}
