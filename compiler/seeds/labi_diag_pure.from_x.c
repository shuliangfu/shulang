/* seeds/labi_diag_pure.from_x.c — G-02f-268/L P2 link_abi L1 → R2 full
 * Logic source: src/runtime/labi_diag_pure.x
 * Hybrid: XLANG_LABI_DIAG_PURE_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供：
 *   link_diag_code_for_kind + 7 report 消息体 + labi_diag_pure_count
 *   （栈拼装 + diag_report_with_code；无 va_list / reportf）
 * wave111：xlang_link_perror pure orch（prefix + paren split）
 * wave112：tool_status / obj_build_status pure orch（append_i32 + wait Cap residual）
 * wave113：link_diag_errno / _path pure orch（append + code_for_kind + report_with_code）
 * wave216：xlang_waitpid_retry pure thin（Cap residual waitpid+EINTR+strerror _impl）
 * wave217：strerror_current + wait_is_signaled + wait_code pure thin（_impl Cap residual）
 * wave219：xlang_spawn_sync pure thin（Cap residual fork/exec/wait 或 _spawnvp _impl）
 * wave220：invoke_cc_strip_out_x pure thin（Cap residual argv pack + spawn _impl）
 * wave222：link_abi_getenv pure thin（Cap residual host getenv _impl）
 * wave224：link_abi_system pure thin（Cap residual host system _impl）
 * Cap residual（mega rest 常驻）：
 *   link_diag_ld_debug_argv_impl（char** 🔒）
 *   link_diag_strerror_current_impl（errno + strerror 🔒；wave217）
 *   link_diag_wait_is_signaled_impl / link_diag_wait_code_impl（WIF* 🔒；wave217）
 *   xlang_waitpid_retry_impl（waitpid+EINTR+strerror 🔒；wave216）
 *   xlang_spawn_sync_impl（fork+execvp+wait / _spawnvp 🔒；wave219）
 *   invoke_cc_strip_out_x_impl（strip argv pack + spawn 🔒；wave220）
 *   link_abi_getenv_impl（host getenv 🔒；wave222）
 *   link_abi_system_impl（host system 🔒；wave224）
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega _impl 并存）。
 *
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "runtime_diag_codes.h"

extern void diag_report_with_code(const char *file, int line, int col, const char *kind, const char *code,
                                  const char *msg, const char *detail);
extern void link_diag_ld_debug_argv_impl(const char *label, const char *const *argv);
/* Cap residual (mega always _impl, wave217): errno + strerror. PLATFORM: SHARED. */
extern const char *link_diag_strerror_current_impl(void);
/* Cap residual (mega always _impl, wave217): POSIX wait decode. PLATFORM: POSIX. */
extern int link_diag_wait_is_signaled_impl(int status);
extern int link_diag_wait_code_impl(int status);
/* Cap residual (wave216): waitpid + EINTR + strerror. PLATFORM: POSIX.
 * Signature uses int64_t to match pure .x i64 / surface pin (pid_t on host). */
extern int xlang_waitpid_retry_impl(int64_t pid, int *status_out);
/* Cap residual (wave219): host spawn. PLATFORM: POSIX fork / WINDOWS _spawnvp.
 * argv is NULL-terminated; pure owns null/empty gates. */
extern int xlang_spawn_sync_impl(const char *prog, const char *const *argv);
/* Cap residual (wave220): strip -x argv pack + spawn. PLATFORM: POSIX spawn / WINDOWS _spawnvp.
 * Pure owns null/empty out_path gates. */
extern void invoke_cc_strip_out_x_impl(const char *out_path);
/* Cap residual (wave222): host getenv. PLATFORM: SHARED — process environment. */
extern const char *link_abi_getenv_impl(const char *name);
/* Cap residual (wave224): host system. PLATFORM: SHARED — shell / process boundary. */
extern int link_abi_system_impl(const char *cmd);
/* Public pure thin (defined later under cold #ifndef; used by errno/tool orch). */
const char *link_diag_strerror_current(void);
int link_diag_wait_is_signaled(int status);
int link_diag_wait_code(int status);

#ifndef XLANG_LABI_DIAG_PURE_FROM_X

static int labi_diag_append_c(char *dst, int cap, const char *src) {
  int i = 0;
  int j = 0;
  if (!dst || cap <= 0)
    return 0;
  while (i < cap && dst[i] != 0)
    i++;
  if (i >= cap) {
    dst[cap - 1] = 0;
    return cap - 1;
  }
  if (!src) {
    dst[i] = 0;
    return i;
  }
  j = 0;
  while (i + 1 < cap && src[j] != 0) {
    dst[i] = src[j];
    i++;
    j++;
  }
  dst[i] = 0;
  return i;
}

/* wave112 cold twin of pure labi_diag_append_i32. PLATFORM: SHARED. */
void labi_diag_append_i32(char *dst, int cap, int v) {
  char dig[16];
  int n = v;
  int i = 0;
  int j = 0;
  int neg = 0;
  char a;
  dig[0] = 0;
  if (n == 0) {
    dig[0] = '0';
    dig[1] = 0;
    labi_diag_append_c(dst, cap, dig);
    return;
  }
  if (n < 0) {
    neg = 1;
    n = -n;
  }
  while (n > 0) {
    if (i >= 15)
      break;
    dig[i] = (char)('0' + (n % 10));
    n = n / 10;
    i++;
  }
  if (neg != 0 && i < 15) {
    dig[i] = '-';
    i++;
  }
  j = 0;
  while (j < i / 2) {
    a = dig[j];
    dig[j] = dig[i - 1 - j];
    dig[i - 1 - j] = a;
    j++;
  }
  dig[i] = 0;
  labi_diag_append_c(dst, cap, dig);
}

const char *link_diag_code_for_kind(const char *kind) {
  if (!kind)
    return XLANG_DIAG_CODE_PROCESS_PRC001;
  if (strcmp(kind, "build error") == 0)
    return XLANG_DIAG_CODE_BUILD_BLD001;
  if (strcmp(kind, "process error") == 0)
    return XLANG_DIAG_CODE_PROCESS_PRC001;
  return NULL;
}

void link_diag_runtime_obj_resolve_fail(const char *obj_name, const char *hint) {
  char msg[320];
  const char *on = obj_name ? obj_name : "runtime object";
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), "cannot resolve compiler directory to build ");
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  if (hint && hint[0] != '\0') {
    labi_diag_append_c(msg, (int)sizeof(msg), " (");
    labi_diag_append_c(msg, (int)sizeof(msg), hint);
    labi_diag_append_c(msg, (int)sizeof(msg), ")");
  }
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_runtime_source_missing(const char *obj_name, const char *source_path) {
  char msg[320];
  const char *on = obj_name ? obj_name : "runtime object";
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  labi_diag_append_c(msg, (int)sizeof(msg), " source not found at ");
  labi_diag_append_c(msg, (int)sizeof(msg), source_path ? source_path : "?");
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_runtime_source_missing_under(const char *obj_name, const char *base_dir, const char *suffix) {
  char msg[384];
  const char *on = obj_name ? obj_name : "runtime object";
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  labi_diag_append_c(msg, (int)sizeof(msg), " source not found under ");
  labi_diag_append_c(msg, (int)sizeof(msg), base_dir ? base_dir : "?");
  labi_diag_append_c(msg, (int)sizeof(msg), suffix ? suffix : "");
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_runtime_obj_missing(const char *obj_name, const char *out_o) {
  char msg[320];
  const char *on = obj_name ? obj_name : "runtime object";
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  labi_diag_append_c(msg, (int)sizeof(msg), " missing after cc -c (expected near ");
  labi_diag_append_c(msg, (int)sizeof(msg), out_o ? out_o : "?");
  labi_diag_append_c(msg, (int)sizeof(msg), ")");
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_freestanding_missing(const char *obj_name, const char *symbol_name) {
  char msg[320];
  const char *on = obj_name ? obj_name : "runtime object";
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), "freestanding link missing ");
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  if (symbol_name && symbol_name[0] != '\0') {
    labi_diag_append_c(msg, (int)sizeof(msg), " (user references ");
    labi_diag_append_c(msg, (int)sizeof(msg), symbol_name);
    labi_diag_append_c(msg, (int)sizeof(msg), ")");
  }
  diag_report_with_code(NULL, 0, 0, "link error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_freestanding_unsupported(void) {
  char msg[192];
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), "-freestanding / XLANG_FREESTANDING is only supported for ");
  labi_diag_append_c(msg, (int)sizeof(msg), "Linux ELF x86_64 (-o prog, not .o/.obj on macOS/COFF)");
  diag_report_with_code(NULL, 0, 0, "link error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

void link_diag_ld_debug_push(const char *rel, const char *stage, const char *path) {
  char msg[320];
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), "ld debug: push ");
  labi_diag_append_c(msg, (int)sizeof(msg), rel ? rel : "(null)");
  labi_diag_append_c(msg, (int)sizeof(msg), " ");
  labi_diag_append_c(msg, (int)sizeof(msg), stage ? stage : "path");
  labi_diag_append_c(msg, (int)sizeof(msg), "=");
  labi_diag_append_c(msg, (int)sizeof(msg), path ? path : "(null)");
  diag_report_with_code(NULL, 0, 0, "note", NULL, msg, NULL);
}

void link_diag_ld_debug_argv(const char *label, const char *const *argv) {
  link_diag_ld_debug_argv_impl(label, argv);
}

/* wave113 cold twin of pure link_diag_errno. Cap residual strerror. PLATFORM: SHARED. */
void link_diag_errno(const char *kind, const char *op) {
  char msg[320];
  const char *k = kind ? kind : "process error";
  const char *o = (op && op[0]) ? op : "system call";
  const char *err = link_diag_strerror_current();
  const char *code;
  if (!err)
    err = "unknown error";
  code = link_diag_code_for_kind(k);
  msg[0] = 0;
  labi_diag_append_c(msg, 320, o);
  labi_diag_append_c(msg, 320, " failed: ");
  labi_diag_append_c(msg, 320, err);
  diag_report_with_code(NULL, 0, 0, k, code, msg, NULL);
}

/* wave113 cold twin of pure link_diag_errno_path. PLATFORM: SHARED. */
void link_diag_errno_path(const char *kind, const char *op, const char *path) {
  char msg[384];
  const char *k;
  const char *o;
  const char *err;
  const char *code;
  if (!path || !path[0]) {
    link_diag_errno(kind, op);
    return;
  }
  k = kind ? kind : "process error";
  o = (op && op[0]) ? op : "system call";
  err = link_diag_strerror_current();
  if (!err)
    err = "unknown error";
  code = link_diag_code_for_kind(k);
  msg[0] = 0;
  labi_diag_append_c(msg, 384, o);
  labi_diag_append_c(msg, 384, " failed for '");
  labi_diag_append_c(msg, 384, path);
  labi_diag_append_c(msg, 384, "': ");
  labi_diag_append_c(msg, 384, err);
  diag_report_with_code(NULL, 0, 0, k, code, msg, NULL);
}

/* wave112 cold twin of pure link_diag_tool_status. Cap residual wait decode. PLATFORM: SHARED. */
void link_diag_tool_status(const char *tool, int status) {
  char msg[320];
  const char *t = tool ? tool : "tool";
  int sig;
  int c;
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), t);
  sig = link_diag_wait_is_signaled(status);
  c = link_diag_wait_code(status);
  if (sig != 0)
    labi_diag_append_c(msg, (int)sizeof(msg), " failed (signal ");
  else
    labi_diag_append_c(msg, (int)sizeof(msg), " failed (exit ");
  labi_diag_append_i32(msg, (int)sizeof(msg), c);
  labi_diag_append_c(msg, (int)sizeof(msg), ")");
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

/* wave112 cold twin of pure link_diag_runtime_obj_build_status. PLATFORM: SHARED. */
void link_diag_runtime_obj_build_status(const char *obj_name, int status) {
  char msg[320];
  const char *on = obj_name ? obj_name : "runtime object";
  int sig;
  int c;
  msg[0] = 0;
  labi_diag_append_c(msg, (int)sizeof(msg), "failed to build ");
  labi_diag_append_c(msg, (int)sizeof(msg), on);
  sig = link_diag_wait_is_signaled(status);
  c = link_diag_wait_code(status);
  if (sig != 0)
    labi_diag_append_c(msg, (int)sizeof(msg), " (signal ");
  else
    labi_diag_append_c(msg, (int)sizeof(msg), " (exit ");
  labi_diag_append_i32(msg, (int)sizeof(msg), c);
  labi_diag_append_c(msg, (int)sizeof(msg), ")");
  diag_report_with_code(NULL, 0, 0, "build error", XLANG_DIAG_CODE_BUILD_BLD001, msg, NULL);
}

/* wave111 cold twin of pure xlang_link_perror (hybrid L1 owns body under FROM_X).
 * wave113: calls cold twin pure-style link_diag_errno/_path. PLATFORM: SHARED. */
void xlang_link_perror(const char *msg) {
  char op_buf[128];
  char path_buf[160];
  const char *text = msg;
  const char *lparen;
  const char *rparen;
  size_t op_len;
  size_t path_len;
  if (!text || !text[0]) {
    link_diag_errno("process error", "system call");
    return;
  }
  if (strncmp(text, "xlang: ", 6) == 0)
    text += 6;
  lparen = strrchr(text, '(');
  rparen = strrchr(text, ')');
  if (lparen && rparen && lparen < rparen && rparen[1] == '\0') {
    const char *op_end = lparen;
    while (op_end > text && op_end[-1] == ' ')
      op_end--;
    op_len = (size_t)(op_end - text);
    path_len = (size_t)(rparen - lparen - 1);
    if (op_len >= sizeof op_buf)
      op_len = sizeof op_buf - 1;
    if (path_len >= sizeof path_buf)
      path_len = sizeof path_buf - 1;
    memcpy(op_buf, text, op_len);
    op_buf[op_len] = '\0';
    memcpy(path_buf, lparen + 1, path_len);
    path_buf[path_len] = '\0';
    link_diag_errno_path("process error", op_buf, path_buf);
    return;
  }
  link_diag_errno("process error", text);
}

/* wave217 cold twins of pure strerror / wait decode (thin → Cap residual _impl).
 * PLATFORM: SHARED orch / POSIX wait residual / libc strerror residual. */
const char *link_diag_strerror_current(void) {
  return link_diag_strerror_current_impl();
}
int link_diag_wait_is_signaled(int status) {
  return link_diag_wait_is_signaled_impl(status);
}
int link_diag_wait_code(int status) {
  return link_diag_wait_code_impl(status);
}

/* wave216 cold twin of pure xlang_waitpid_retry (thin → Cap residual _impl).
 * PLATFORM: SHARED orch / POSIX wait residual. */
int xlang_waitpid_retry(int64_t pid, int *status_out) {
  return xlang_waitpid_retry_impl(pid, status_out);
}

/* wave219 cold twin of pure xlang_spawn_sync (null/empty gates + Cap residual spawn).
 * PLATFORM: SHARED orch / POSIX fork residual / WINDOWS _spawnvp residual. */
int xlang_spawn_sync(const char *prog, const char *const *argv) {
  if (prog == NULL)
    return -1;
  if (prog[0] == 0)
    return -1;
  if (argv == NULL)
    return -1;
  return xlang_spawn_sync_impl(prog, argv);
}

/* wave220 cold twin of pure invoke_cc_strip_out_x (null/empty gates + Cap residual strip).
 * PLATFORM: SHARED orch / POSIX strip spawn residual / WINDOWS _spawnvp residual. */
void invoke_cc_strip_out_x(const char *out_path) {
  if (out_path == NULL)
    return;
  if (out_path[0] == 0)
    return;
  invoke_cc_strip_out_x_impl(out_path);
}

/* wave222 cold twin of pure link_abi_getenv (null/empty gates + Cap residual getenv).
 * PLATFORM: SHARED orch / host libc getenv residual. */
const char *link_abi_getenv(const char *name) {
  if (name == NULL)
    return NULL;
  if (name[0] == 0)
    return NULL;
  return link_abi_getenv_impl(name);
}

/* wave224 cold twin of pure link_abi_system (null/empty gates + Cap residual system).
 * PLATFORM: SHARED orch / host libc system residual. */
int link_abi_system(const char *cmd) {
  if (cmd == NULL)
    return -1;
  if (cmd[0] == 0)
    return -1;
  return link_abi_system_impl(cmd);
}

int labi_diag_pure_count(void) {
  return 9;
}

#else
const char *link_diag_code_for_kind(const char *kind);
void labi_diag_append_i32(char *dst, int cap, int v);
void link_diag_runtime_obj_resolve_fail(const char *obj_name, const char *hint);
void link_diag_runtime_source_missing(const char *obj_name, const char *source_path);
void link_diag_runtime_source_missing_under(const char *obj_name, const char *base_dir, const char *suffix);
void link_diag_runtime_obj_missing(const char *obj_name, const char *out_o);
void link_diag_freestanding_missing(const char *obj_name, const char *symbol_name);
void link_diag_freestanding_unsupported(void);
void link_diag_ld_debug_push(const char *rel, const char *stage, const char *path);
void link_diag_ld_debug_argv(const char *label, const char *const *argv);
void link_diag_tool_status(const char *tool, int status);
void link_diag_runtime_obj_build_status(const char *obj_name, int status);
void link_diag_errno(const char *kind, const char *op);
void link_diag_errno_path(const char *kind, const char *op, const char *path);
void xlang_link_perror(const char *msg);
const char *link_diag_strerror_current(void);
int link_diag_wait_is_signaled(int status);
int link_diag_wait_code(int status);
int xlang_waitpid_retry(int64_t pid, int *status_out);
int xlang_spawn_sync(const char *prog, const char *const *argv);
void invoke_cc_strip_out_x(const char *out_path);
const char *link_abi_getenv(const char *name);
int link_abi_system(const char *cmd);
int labi_diag_pure_count(void);
#endif

int labi_diag_pure_slice_marker(void) {
  return 1;
}
