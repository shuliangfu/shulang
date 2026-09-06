/* seeds/runtime_panic.from_x.c — G-02f-22 product TU
 * G-02f-106 helper gates.
 * Logic still C until full .x port.
 *
 * wave251 G.7: user-product face strategy for STD_AND_PANIC bag —
 * CRASH_EVIDENCE env via public pure thin link_abi_getenv (wave222 → _impl
 * host getenv); not raw libc getenv. This TU is user-linkable (runtime_panic.o
 * on product -o lines), NOT part of the g05 xlang/xlang_asm host link.
 * Product host authority remains labi_diag_pure.x (pure thin) + mega
 * link_abi_getenv_impl. This seed supplies a user-domain cold twin of the same
 * face ABI so panic residual can call link_abi_getenv without U in user
 * binaries and without dragging labi mega into the user link graph.
 * Semantics ≡ wave222 pure thin (null/empty → null) + host getenv residual.
 * Never dual-def with product host: this .o is only on user / STD_AND_PANIC
 * link lines (and test_c), never on g05 60/62-obj.
 * PLATFORM: SHARED — user-domain host residual twin of product face.
 * Follow-up leaves (backtrace/env_os/process_os/log_os/http_glue) may share
 * this twin when co-linked with panic, or extract a dedicated user_env.o.
 */
/* runtime_panic.c — 提供 xlang_panic_，链 libc 时调用 abort；供 -backend asm 链接用（Linux 可用 .s 不链 libc）。
 * Freestanding / 弱化 libc 路线见 compiler/docs/SELFHOST.md §6 与 src/asm/runtime_panic_x86_64.s（若存在）。
 * SAFE-007：弱符号证据收集，强符号由 runtime_backtrace_platform.o 提供。 */
#include <xlang_weak.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: crash evidence path → Cap snprintf */
/* G.7: Cap after stdio for user-link panic residual. */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_environ_cap.h>
#ifdef _WIN32
#include <process.h> /* MinGW getpid() 声明在此；unistd.h 不提供 */
#else
#include <unistd.h>
#endif

/** Linux ld：标记非可执行栈，消除 missing .note.GNU-stack 链接警告（macOS 勿用 %progbits 语法）。 */
#if defined(__GNUC__) && defined(__linux__)
__asm__(".section .note.GNU-stack,\"\",%progbits");
#endif

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

/** 无 backtrace 平台 runtime 时的最小证据包（XLANG_CRASH_EVIDENCE=1）；强符号链接 runtime_backtrace_platform.o 时覆盖。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-22 thin+rest：_impl 实现；thin（src/asm/runtime_panic.x）提供 public wrapper */
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

#ifndef XLANG_RUNTIME_PANIC_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
void xlang_crash_evidence_minimal(int has_msg, int msg_val) {
  xlang_crash_evidence_minimal_impl(has_msg, msg_val);
}
#endif




/**
 * 弱默认：无 runtime_backtrace_platform.o 时输出最小证据；有平台 runtime 时强符号覆盖。
 * PE/COFF（Windows/Cygwin）弱符号不可靠，须强符号默认实现以满足 std/runtime/runtime.o 链接。
 */
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
void xlang_crash_evidence_collect_c(int has_msg, int msg_val) {
  xlang_crash_evidence_minimal_impl(has_msg, msg_val);
}
#else
XLANG_WEAK void xlang_crash_evidence_collect_c(int has_msg, int msg_val) {
  xlang_crash_evidence_minimal_impl(has_msg, msg_val);
}
#endif

XLANG_WEAK int io_register_buffers_buf_c(const void *bufs, int nr) {
  (void)bufs;
  (void)nr;
  return -1;
}

/**
 * Product panic entry (wave386): full-width payload; print cstr when has_msg==2.
 * @param has_msg 0=bare, 1=integer msg_val, 2=NUL cstr pointer in msg_val
 * @param msg_val integer evidence or cstr pointer (LP64 full width)
 * PLATFORM: SHARED — host-C / libc path; Linux freestanding uses .s twin.
 */
void xlang_panic_(int has_msg, intptr_t msg_val) {
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
  /* Evidence path keeps historical int payload (truncated). */
  xlang_crash_evidence_collect_c(has_msg, (int)msg_val);
  abort();
}
