/* seeds/runtime_panic_arm64.from_x.c — G-02f-22 product TU
 * G-02f-107 helper gates.
 * Logic still C until full .x port.
 *
 * wave251 G.7: user-product face strategy for STD_AND_PANIC bag —
 * CRASH_EVIDENCE env via public pure thin link_abi_getenv (wave222 → _impl
 * host getenv); not raw libc getenv. This TU is user-linkable (runtime_panic.o
 * on product -o lines), NOT part of the g05 xlang/xlang_asm host link.
 * Product host authority remains labi_diag_pure.x + mega link_abi_getenv_impl.
 * User-domain cold twin of the same face ABI (≡ wave222 pure thin + host getenv).
 * Never dual-def with product host g05. PLATFORM: MACOS|ARM64 primary product
 * panic TU on Darwin; SHARED face contract with runtime_panic.from_x.c.
 */
/* runtime_panic_arm64.c — ARM64/macOS 用最小 panic 实现。提供 xlang_panic_ 符号供链接。 */
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <xlang_weak.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: crash evidence path → Cap snprintf */
/* G.7: Cap after stdio for user-link panic residual (Darwin/arm64). */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_environ_cap.h>

/* wave251: user-domain cold twin of product link_abi_getenv face (≡ pure thin + _impl).
 * PLATFORM: SHARED — user/STD_AND_PANIC only; never dual-def with g05 labi. */

/**
 * Cap residual host getenv for user-linked runtime_panic.o (≡ product _impl).
 * Cap residual 9.1.1: unified xlang_environ_getenv (POSIX walk / Win32).
 * @param name NUL-terminated environment key; may be null
 * @return value pointer from process env block, or NULL
 * PLATFORM: SHARED Cap (9.1.1).
 */
const char *link_abi_getenv_impl(const char *name) {
  return xlang_environ_getenv(name);
}

/**
 * Public face twin: null/empty gate then host residual (≡ product pure thin).
 * @param name NUL-terminated environment key
 * @return NULL on null/empty; else link_abi_getenv_impl value
 */
const char *link_abi_getenv(const char *name) {
  if (!name || !name[0])
    return NULL;
  return link_abi_getenv_impl(name);
}

/** 无 backtrace.o 时的最小证据包（XLANG_CRASH_EVIDENCE=1）。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-22 thin+rest：_impl 实现；thin（src/asm/runtime_panic_arm64.x）提供 public wrapper */
/* wave251 G.7: env via public face link_abi_getenv (not raw libc getenv). */
void xlang_crash_evidence_minimal_impl(int has_msg, int msg_val) {
  const char *en = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  if (!en || en[0] != '1') {
    return;
  }
  int pid = (int)getpid();
  fprintf(stderr, "note: crash evidence: panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val,
          pid);
  const char *dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
  if (dir && dir[0]) {
    char path[1024];
    (void)snprintf(path, sizeof(path), "%s/xlang-crash-%d.txt", dir, pid);
    FILE *f = fopen(path, "w");
    if (f) {
      fprintf(f, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, pid);
      fclose(f);
      fprintf(stderr, "note: crash evidence: bundle=%s\n", path);
    }
  }
}

#ifndef XLANG_RUNTIME_PANIC_ARM64_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
void xlang_crash_evidence_minimal(int has_msg, int msg_val) {
  xlang_crash_evidence_minimal_impl(has_msg, msg_val);
}
#endif




XLANG_WEAK void xlang_crash_evidence_collect_c(int has_msg, int msg_val) {
  xlang_crash_evidence_minimal_impl(has_msg, msg_val);
}

/**
 * Product panic entry (wave386): full-width payload; print cstr when has_msg==2.
 * @param has_msg 0=bare, 1=integer msg_val, 2=NUL cstr pointer in msg_val
 * @param msg_val integer evidence or cstr pointer (LP64 full width)
 * PLATFORM: LINUX|ARM64 / MACOS twin of runtime_panic.from_x.c face.
 */
__attribute__((noreturn)) void xlang_panic_(int has_msg, intptr_t msg_val) {
  if (has_msg == 2) {
    const char *s = (const char *)(uintptr_t)msg_val;
    if (s != NULL && s[0] != '\0') {
      fputs("panic: ", stderr);
      fputs(s, stderr);
      fputc('\n', stderr);
    } else {
      fputs("panic\n", stderr);
    }
  } else if (has_msg == 1) {
    fprintf(stderr, "panic: %ld\n", (long)msg_val);
  }
  xlang_crash_evidence_collect_c(has_msg, (int)msg_val);
  _exit(1);
}
