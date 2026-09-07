/* seeds/runtime_backtrace_platform.from_x.c — G-02f-19 product TU
 * Product: runtime_backtrace_platform.o; R2 full mode (wave506).
 *
 * R2 full mode: public API in src/asm/runtime_backtrace_platform.x (thin),
 * OS bridge _impl functions here (rest). Thin+rest linked via ld -r.
 * Platform-specific: Cap residual 9.1.11 (FP walk + ELF/Mach-O/PE) on
 * LINUX|DARWIN|WINDOWS; fallback execinfo/dladdr or CaptureStackBackTrace/
 * DbgHelp only when Cap is unavailable.
 *
 * wave252 G.7: CRASH_EVIDENCE env via public face link_abi_getenv (not raw libc getenv).
 * wave253: face body in runtime_link_abi_user_env.o (declaration only here).
 * PLATFORM: SHARED
 */

#if defined(__linux__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: crash evidence path → Cap snprintf */
/* G.7: Cap after stdio for backtrace crash-evidence residual. */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_io_cap.h>   /* Cap residual 9.5.3: xlang_io_write / xlang_io_open_write */
#include <xlang_proc_cap.h> /* Cap residual 9.5.3: xlang_proc_close_fd (single close authority) */
#include "diag.h"
#include <xlang_user_link_abi_getenv.h>
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif

#define BACKTRACE_SYM_NAME_LEN 128

static int32_t g_sym_capture_mode = 0;
static int32_t g_sym_capture_result = 0;

/* Forward declarations of thin public API functions (provided by .x in R2 mode).
 * Needed by smoke tests and noinline C functions that call back into public API. */
void *backtrace_read_frame_addr_c(const uint8_t *buf, int32_t i);
void backtrace_write_frame_addr_c(uint8_t *buf, int32_t i, void *addr);
int32_t backtrace_copy_sym_name_c(uint8_t *out, int32_t name_cap, const uint8_t *name);
void backtrace_format_hex_addr_c(uint8_t *out, int32_t cap, void *addr);
int32_t backtrace_name_has_gold_anchor_c(const uint8_t *name);
int32_t backtrace_capture_c(uint8_t *buf, int32_t max_frames);
int32_t backtrace_symbolicate_c(const uint8_t *buf, int32_t len, uint8_t *out_ptrs, uint8_t *out_names, int32_t max);
void *backtrace_gold_anchor_addr_c(void);
int32_t backtrace_capture_and_check_gold_c(void);
const uint8_t *backtrace_xplat_platform_name_c(void);
int32_t backtrace_xplat_quality_c(void);
void xlang_crash_evidence_collect_c(int has_msg, int msg_val);
void backtrace_u8_hex2(uint8_t b, uint8_t *out);

/* === Pure helper _impl functions === */

/** Read the i-th frame address from buffer. */
void *backtrace_read_frame_addr_impl(const uint8_t *buf, int32_t i) {
  void *p = NULL;
  const uint8_t *src;
  uint8_t *dst;
  size_t k;
  if (!buf || i < 0) return NULL;
  src = buf + (size_t)i * sizeof(void *);
  dst = (uint8_t *)&p;
  for (k = 0; k < sizeof(void *); k++) dst[k] = src[k];
  return p;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void *backtrace_read_frame_addr_c(const uint8_t *buf, int32_t i) {
  return backtrace_read_frame_addr_impl(buf, i);
}
#endif

/** Write frame address into buffer at position i. */
void backtrace_write_frame_addr_impl(uint8_t *buf, int32_t i, void *addr) {
  uint8_t *dst;
  const uint8_t *src;
  size_t k;
  if (!buf || i < 0) return;
  dst = buf + (size_t)i * sizeof(void *);
  src = (const uint8_t *)&addr;
  for (k = 0; k < sizeof(void *); k++) dst[k] = src[k];
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void backtrace_write_frame_addr_c(uint8_t *buf, int32_t i, void *addr) {
  backtrace_write_frame_addr_impl(buf, i, addr);
}
#endif

/** Convert single byte to two lowercase hex characters. */
void backtrace_u8_hex2_impl(uint8_t b, uint8_t *out) {
  uint8_t hi = (uint8_t)((b >> 4) & 0x0fu);
  uint8_t lo = (uint8_t)(b & 0x0fu);
  if (!out) return;
  out[0] = (uint8_t)(hi < 10 ? ('0' + hi) : ('a' + hi - 10));
  out[1] = (uint8_t)(lo < 10 ? ('0' + lo) : ('a' + lo - 10));
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void backtrace_u8_hex2(uint8_t b, uint8_t *out) {
  backtrace_u8_hex2_impl(b, out);
}
#endif

/** Copy symbol name into output buffer (max name_cap-1 bytes + NUL). */
void backtrace_copy_sym_name_impl(uint8_t *out, int32_t name_cap, const uint8_t *name) {
  int32_t n;
  if (!out || name_cap <= 0) return;
  if (!name) { out[0] = '\0'; return; }
  n = (int32_t)strlen((const char *)name);
  if (n >= name_cap) n = name_cap - 1;
  if (n > 0) memcpy(out, name, (size_t)n);
  out[n] = '\0';
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_copy_sym_name_c(uint8_t *out, int32_t name_cap, const uint8_t *name) {
  backtrace_copy_sym_name_impl(out, name_cap, name);
  return 0;
}
#endif

/** Format address as "0x" + hex digits into out[0..cap).
 * PLATFORM: SHARED — walk address bytes and call backtrace_u8_hex2_impl per
 * byte (two digits). Do NOT pass a nibble to u8_hex2: that writes two digits
 * per nibble and overruns a 18-byte scratch (Ubuntu stack-smash in
 * symbolicate fallback when dladdr misses). Scratch holds "0x" + 16 digits.
 */
void backtrace_format_hex_addr_impl(uint8_t *out, int32_t cap, void *addr) {
  uint8_t tmp[19];
  uintptr_t v = (uintptr_t)addr;
  int32_t i;
  int32_t pos = 2;
  int32_t ncopy;
  if (!out || cap <= 0) return;
  tmp[0] = '0';
  tmp[1] = 'x';
  /* sizeof(void*) bytes → 2*sizeof(void*) hex digits; 64-bit → pos ends at 18. */
  for (i = (int32_t)sizeof(void *) - 1; i >= 0; i--) {
    uint8_t b = (uint8_t)((v >> (i * 8)) & 0xffu);
    backtrace_u8_hex2_impl(b, &tmp[pos]);
    pos += 2;
  }
  ncopy = pos;
  if (ncopy >= cap) ncopy = cap - 1;
  if (ncopy > 0) memcpy(out, tmp, (size_t)ncopy);
  out[ncopy] = '\0';
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void backtrace_format_hex_addr_c(uint8_t *out, int32_t cap, void *addr) {
  backtrace_format_hex_addr_impl(out, cap, addr);
}
#endif

/** Check if symbol name contains gold_anchor substring. */
int32_t backtrace_name_has_gold_anchor_impl(const uint8_t *name) {
  if (!name) return 0;
  return strstr((const char *)name, "gold_anchor") != NULL ? 1 : 0;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_name_has_gold_anchor_c(const uint8_t *name) {
  return backtrace_name_has_gold_anchor_impl(name);
}
#endif

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t name_has_gold_anchor(const uint8_t *name) {
  return backtrace_name_has_gold_anchor_impl(name);
}
#endif

/* === Platform-specific _impl functions === */

/* Cap residual 9.1.11: stack capture + resolve without libc backtrace/dladdr
 * (Linux/Darwin) or CaptureStackBackTrace/DbgHelp (Windows). */
#if (defined(__linux__) || defined(__APPLE__) || defined(_WIN32) || defined(_WIN64)) && \
    (defined(__x86_64__) || defined(__aarch64__) || defined(_M_X64) || defined(_M_ARM64))
#include <xlang_backtrace_cap.h>
#define HAVE_XLANG_BT_CAPTURE_CAP 1
#define HAVE_XLANG_BT_CAP 1
#endif

/* PLATFORM: POSIX — stdio above pulls features.h on glibc so __GLIBC__ is set.
 * Musl/Alpine typically lack execinfo.h → leave HAVE_EXECINFO undefined.
 * Skip execinfo when Cap frame walk is active (Linux or Darwin). */
#if ((defined(__linux__) && defined(__GLIBC__)) || defined(__APPLE__)) && !defined(HAVE_XLANG_BT_CAPTURE_CAP)
#include <execinfo.h>
#define HAVE_EXECINFO 1
#endif

#if !defined(HAVE_XLANG_BT_CAP) && (defined(__linux__) || defined(__APPLE__))
#include <dlfcn.h>
#define HAVE_DLADDR 1
#endif

#if !defined(HAVE_XLANG_BT_CAP) && (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#ifdef _MSC_VER
#pragma comment(lib, "dbghelp.lib")
#endif
#include <dbghelp.h>
#endif

/** Capture current call stack into buffer. */
int32_t backtrace_capture_impl(uint8_t *buf, int32_t max_frames) {
  if (!buf || max_frames <= 0) return 0;
#if defined(HAVE_XLANG_BT_CAPTURE_CAP)
  {
    void *arr[256];
    int cap = max_frames > 256 ? 256 : (int)max_frames;
    int n = xlang_bt_backtrace(arr, cap);
    int i;
    if (n <= 0) return 0;
    for (i = 0; i < n; i++)
      backtrace_write_frame_addr_c(buf, i, arr[i]);
    return (int32_t)n;
  }
#elif defined(HAVE_EXECINFO)
  {
    void *arr[256];
    int n = backtrace(arr, max_frames > 256 ? 256 : (int)max_frames);
    int i;
    if (n <= 0) return 0;
    for (i = 0; i < n; i++)
      backtrace_write_frame_addr_c(buf, i, arr[i]);
    return (int32_t)n;
  }
#elif defined(_WIN32) || defined(_WIN64)
  {
    void *arr[256];
    uint32_t n = CaptureStackBackTrace(0, (uint32_t)(max_frames > 256 ? 256 : max_frames), arr, NULL);
    uint32_t i;
    if (n == 0) return 0;
    for (i = 0; i < n; i++)
      backtrace_write_frame_addr_c(buf, (int32_t)i, arr[i]);
    return (int32_t)n;
  }
#else
  (void)buf;
  (void)max_frames;
  return 0;
#endif
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_capture_c(uint8_t *buf, int32_t max_frames) {
  return backtrace_capture_impl(buf, max_frames);
}
#endif

/** Symbolicate captured buffer. */
int32_t backtrace_symbolicate_impl(const uint8_t *buf, int32_t len, uint8_t *out_ptrs, uint8_t *out_names, int32_t max) {
  int32_t ok = 0;
  int32_t n;
  int32_t i;
  if (!buf || len <= 0 || !out_names || max <= 0) return 0;
  n = len < max ? len : max;
  for (i = 0; i < n; i++) {
    void *addr = backtrace_read_frame_addr_c(buf, i);
    uint8_t *name_slot = out_names + (size_t)i * BACKTRACE_SYM_NAME_LEN;
    if (out_ptrs) backtrace_write_frame_addr_c(out_ptrs, i, addr);
#if defined(HAVE_XLANG_BT_CAP)
    {
      XlangBtDlInfo info;
      memset(&info, 0, sizeof(info));
      if (xlang_bt_dladdr(addr, &info) && info.dli_sname && info.dli_sname[0]) {
        backtrace_copy_sym_name_impl(name_slot, BACKTRACE_SYM_NAME_LEN, (const uint8_t *)info.dli_sname);
        ok++;
      } else {
        backtrace_format_hex_addr_impl(name_slot, BACKTRACE_SYM_NAME_LEN, addr);
      }
    }
#elif defined(HAVE_DLADDR)
    {
      Dl_info info;
      memset(&info, 0, sizeof(info));
      if (dladdr(addr, &info) && info.dli_sname && info.dli_sname[0]) {
        backtrace_copy_sym_name_impl(name_slot, BACKTRACE_SYM_NAME_LEN, (const uint8_t *)info.dli_sname);
        ok++;
      } else {
        backtrace_format_hex_addr_impl(name_slot, BACKTRACE_SYM_NAME_LEN, addr);
      }
    }
#elif defined(_WIN32) || defined(_WIN64)
    {
      static int sym_init = 0;
      uint8_t undec[BACKTRACE_SYM_NAME_LEN];
      DWORD64 disp = 0;
      SYMBOL_INFO_PACKAGE pkg;
      if (!sym_init) {
        SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
        SymInitialize(GetCurrentProcess(), NULL, TRUE);
        sym_init = 1;
      }
      memset(&pkg, 0, sizeof(pkg));
      pkg.si.SizeOfStruct = sizeof(SYMBOL_INFO);
      pkg.si.MaxNameLen = MAX_SYM_NAME;
      if (SymFromAddr(GetCurrentProcess(), (DWORD64)(uintptr_t)addr, &disp, &pkg.si)) {
        if (UnDecorateSymbolName(pkg.si.Name, (char *)undec, (DWORD)sizeof(undec), UNDNAME_COMPLETE)) {
          backtrace_copy_sym_name_impl(name_slot, BACKTRACE_SYM_NAME_LEN, undec);
        } else {
          backtrace_copy_sym_name_impl(name_slot, BACKTRACE_SYM_NAME_LEN, (const uint8_t *)pkg.si.Name);
        }
        ok++;
      } else {
        backtrace_format_hex_addr_impl(name_slot, BACKTRACE_SYM_NAME_LEN, addr);
      }
    }
#else
    backtrace_format_hex_addr_impl(name_slot, BACKTRACE_SYM_NAME_LEN, addr);
#endif
  }
  return ok;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_symbolicate_c(const uint8_t *buf, int32_t len, uint8_t *out_ptrs, uint8_t *out_names, int32_t max) {
  return backtrace_symbolicate_impl(buf, len, out_ptrs, out_names, max);
}
#endif

/** Get address of gold_anchor function. */
int32_t backtrace_gold_anchor_smoke_enter_c(void);
#if defined(_MSC_VER)
__declspec(noinline)
#else
__attribute__((noinline))
#endif
void backtrace_gold_anchor_c(void);

void *backtrace_gold_anchor_addr_impl(void) {
  return (void *)&backtrace_gold_anchor_c;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void *backtrace_gold_anchor_addr_c(void) {
  return backtrace_gold_anchor_addr_impl();
}
#endif

/** Capture and check for gold_anchor symbol. */
int32_t backtrace_capture_and_check_gold_c_impl(void) {
  uint8_t buf[512];
  uint8_t names[1024];
  int32_t n, sym_n, i;
  n = backtrace_capture_c(buf, 8);
  if (n <= 0) return 10;
  sym_n = backtrace_symbolicate_c(buf, n, buf, names, n);
  if (sym_n <= 0) return 11;
  for (i = 0; i < n; i++) {
    const uint8_t *slot = names + (size_t)i * BACKTRACE_SYM_NAME_LEN;
    if (backtrace_name_has_gold_anchor_c(slot)) return 0;
  }
  return 12;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_capture_and_check_gold_c(void) {
  return backtrace_capture_and_check_gold_c_impl();
}
#endif

/** Get current platform name. */
const uint8_t *backtrace_xplat_platform_name_impl(void) {
#if defined(__APPLE__)
  return (const uint8_t *)"Darwin";
#elif defined(_WIN32) || defined(_WIN64)
  return (const uint8_t *)"Windows";
#elif defined(__linux__)
  return (const uint8_t *)"Linux";
#else
  return (const uint8_t *)"Unknown";
#endif
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
const uint8_t *backtrace_xplat_platform_name_c(void) {
  return backtrace_xplat_platform_name_impl();
}
#endif

/** Cross-platform symbol quality probe. */
int32_t backtrace_xplat_quality_impl(void) {
  const uint8_t *plat = backtrace_xplat_platform_name_c();
  uint8_t buf[512];
  uint8_t names[32 * BACKTRACE_SYM_NAME_LEN];
  int32_t gold = 0;
  int32_t resolved = 0;
  int32_t total = 0;

  backtrace_write_frame_addr_c(buf, 0, backtrace_gold_anchor_addr_c());
  if (backtrace_symbolicate_c(buf, 1, buf, names, 1) > 0) {
    if (backtrace_name_has_gold_anchor_c(names)) gold = 1;
  }
  total = backtrace_capture_c(buf, 32);
  if (total > 0) resolved = backtrace_symbolicate_c(buf, total, buf, names, total);
  /* 9.5.3: diagnostic note via Cap IO (xlang_io_write); no libc fprintf. */
  {
    char note[256];
    int note_len = snprintf(note, sizeof(note),
                            "xlang: [XLANG_BT_XPLAT] backtrace xplat: platform=%s gold=%d "
                            "resolved=%d total=%d\n",
                            (const char *)plat, gold, resolved, total);
    if (note_len > 0)
      (void)xlang_io_write(2, note, (size_t)note_len);
  }
  if (gold < 1 || resolved < 1 || total < 1) return 1;
  return 0;
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
int32_t backtrace_xplat_quality_c(void) {
  return backtrace_xplat_quality_impl();
}
#endif

/** Collect crash evidence when XLANG_CRASH_EVIDENCE=1.
 * 9.5.3: stderr note + evidence bundle via Cap IO (xlang_io_write/open_write +
 * xlang_proc_close_fd); no libc fprintf/fopen/fclose. */
void xlang_crash_evidence_collect_impl(int has_msg, int msg_val) {
  const char *en = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  uint8_t buf[512];
  char note[256];
  int32_t n;
  int32_t pid = 0;
  if (!en || en[0] != '1') return;
  n = backtrace_capture_c(buf, 32);
#if defined(__unix__) || defined(__APPLE__)
  pid = (int32_t)getpid();
#elif defined(_WIN32) || defined(_WIN64)
  pid = (int32_t)GetCurrentProcessId();
#endif
  {
    int note_len = snprintf(note, sizeof(note),
                            "note: crash evidence: panic=%d msg=%d frames=%d pid=%d\n",
                            has_msg, msg_val, n, pid);
    if (note_len > 0)
      (void)xlang_io_write(2, note, (size_t)note_len);
  }
  {
    const char *dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (dir && dir[0]) {
      char path[1024];
      int32_t i;
      (void)snprintf(path, sizeof(path), "%s/xlang-crash-%d.txt", dir, pid);
      {
        int fd = xlang_io_open_write(path);
        if (fd >= 0) {
          char body[128];
          int body_len = snprintf(body, sizeof(body),
                                  "panic_has_msg=%d\npanic_msg=%d\nframes=%d\npid=%d\n",
                                  has_msg, msg_val, n, pid);
          if (body_len > 0)
            (void)xlang_io_write(fd, body, (size_t)body_len);
          for (i = 0; i < n; i++) {
            void *addr = backtrace_read_frame_addr_c(buf, i);
            int line_len = snprintf(body, sizeof(body), "frame%d=0x%zx\n", (int)i,
                                    (size_t)(uintptr_t)addr);
            if (line_len > 0)
              (void)xlang_io_write(fd, body, (size_t)line_len);
          }
          (void)xlang_proc_close_fd(fd);
          {
            int note_len = snprintf(note, sizeof(note), "note: crash evidence: bundle=%s\n", path);
            if (note_len > 0)
              (void)xlang_io_write(2, note, (size_t)note_len);
          }
        }
      }
    }
  }
}

#ifndef XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X
void xlang_crash_evidence_collect_c(int has_msg, int msg_val) {
  xlang_crash_evidence_collect_impl(has_msg, msg_val);
}
#endif

/* === Smoke tests + noinline functions (stay in C, no thin wrapper) === */

/** Smoke test mode: capture on stack entry. */
int32_t backtrace_gold_anchor_smoke_enter_c(void) {
  if (g_sym_capture_mode != 0) {
    g_sym_capture_result = backtrace_capture_and_check_gold_c_impl();
    g_sym_capture_mode = 0;
  }
  return 0;
}

/** noinline gold_anchor function for smoke tests. */
#if defined(_MSC_VER)
__declspec(noinline)
#else
__attribute__((noinline))
#endif
void backtrace_gold_anchor_c(void) {
  (void)backtrace_gold_anchor_smoke_enter_c();
}

/** STD-052 C smoke: symbolicate gold_anchor + capture path. */
int32_t backtrace_symbolicate_smoke_c(void) {
  uint8_t buf[128];
  uint8_t names[128];
  g_sym_capture_result = 12;
  backtrace_write_frame_addr_c(buf, 0, backtrace_gold_anchor_addr_c());
  if (backtrace_symbolicate_c(buf, 1, buf, names, 1) <= 0) return 1;
  if (!backtrace_name_has_gold_anchor_c(names)) return 2;
  g_sym_capture_mode = 1;
  backtrace_gold_anchor_c();
  return g_sym_capture_result;
}