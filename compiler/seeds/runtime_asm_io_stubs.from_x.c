/* seeds/runtime_asm_io_stubs.from_x.c — G-02f-20 product TU
 * G-02f-100 seed io syscall/write gates.
 * Product: runtime_asm_io_stubs.o; logic still C until full .x port.
 */
/**
 * runtime_asm_io_stubs.c — seed asm 用户程序链接桩
 *
 * std.io 族 .x 模块在 pipeline/asm_codegen_elf_o 中跳过机器码生成；
 * 本 TU 提供 print_* / write_* / read_ptr 等 C ABI 符号，与 ../std/io/io.o 一并链入用户可执行文件。
 */
#if defined(__linux__)
#define _GNU_SOURCE
#endif
#include <xlang_weak.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#if defined(__unix__) || defined(__APPLE__)
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#endif
#include <xlang_io_cap.h>
#include <xlang_proc_cap.h>

/**
 * Cap residual 9.1.8: seed_io_syscall_* → xlang_io_cap.h (G.7 single authority).
 * F-03 无 std/io/io.o 时供 nostdlib / gcc 链；timeout 在 seed 桩 v1 忽略。
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS | POSIX).
 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_asm_io_stubs.x）提供 public wrapper */
long seed_io_syscall_write_impl(int fd, const void *buf, unsigned long count) {
  return xlang_io_write(fd, buf, (size_t)count);
}

/** Cap residual 9.1.8: read via xlang_io_cap.h. G-02f-100 gate. */
long seed_io_syscall_read_impl(int fd, void *buf, unsigned long count) {
  return xlang_io_read(fd, buf, (size_t)count);
}

#ifndef XLANG_RUNTIME_ASM_IO_STUBS_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供
 * Cap residual 9.1.8: emit wrappers on all platforms. */
long seed_io_syscall_write(int fd, const void *buf, unsigned long count) {
  return seed_io_syscall_write_impl(fd, buf, count);
}
long seed_io_syscall_read(int fd, void *buf, unsigned long count) {
  return seed_io_syscall_read_impl(fd, buf, count);
}
#endif

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
long seed_io_syscall_write(int fd, const void *buf, unsigned long count);
long seed_io_syscall_read(int fd, void *buf, unsigned long count);
int32_t seed_io_write_fd1(uint8_t *ptr, size_t len, uint32_t timeout_ms);

/*
 * Cap residual 9.1.8: complete xlang_sys_write/read/writev for -backend asm
 * std.io / std.fs (preamble static inline does not export into those .o).
 * Weak so freestanding_io.o strong twin wins when both are linked.
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS | POSIX).
 */
XLANG_WEAK ssize_t xlang_sys_write(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_write((int)fd, (const void *)buf, count);
}
XLANG_WEAK ssize_t xlang_sys_read(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_read((int)fd, (void *)buf, count);
}
XLANG_WEAK ssize_t xlang_sys_writev(int32_t fd, uint8_t *iov, int32_t iovcnt) {
  return (ssize_t)xlang_io_writev((int)fd, (const void *)iov, (int)iovcnt);
}

#if !defined(_WIN32) && !defined(_WIN64)

/*
 * Cap residual 9.1.11: weak backtrace_capture_c for -backend asm probes.
 * Strong twin in runtime_backtrace_platform.o wins on full product link.
 * PLATFORM: LINUX|DARWIN
 */
#if (defined(__linux__) || defined(__APPLE__)) && (defined(__x86_64__) || defined(__aarch64__))
#include <xlang_backtrace_cap.h>
#include <string.h>

/** Weak probe/product stub: frame walk into buf (void* slots). */
__attribute__((weak)) int32_t backtrace_capture_c(uint8_t *buf, int32_t max_frames) {
  void *arr[256];
  int cap;
  int n;
  int i;
  if (!buf || max_frames <= 0)
    return 0;
  cap = max_frames > 256 ? 256 : (int)max_frames;
  n = xlang_bt_backtrace(arr, cap);
  if (n <= 0)
    return 0;
  for (i = 0; i < n; i++)
    memcpy(buf + (size_t)i * sizeof(void *), &arr[i], sizeof(void *));
  return (int32_t)n;
}

#if defined(__linux__)

#define XLANG_BT_STUB_SYM_NAME_LEN 128

/** Write "0x" + hex digits for addr into out (Cap probe stub hex fallback). */
static void xlang_bt_stub_hex_addr(uint8_t *out, int32_t cap, void *addr) {
  static const char hx[] = "0123456789abcdef";
  uintptr_t v = (uintptr_t)addr;
  int32_t pos = 2;
  int32_t i;
  int32_t ncopy;
  if (!out || cap <= 0)
    return;
  out[0] = '0';
  out[1] = 'x';
  for (i = (int32_t)sizeof(void *) - 1; i >= 0; i--) {
    uint8_t b = (uint8_t)((v >> (i * 8)) & 0xffu);
    out[pos++] = (uint8_t)hx[(b >> 4) & 0x0fu];
    out[pos++] = (uint8_t)hx[b & 0x0fu];
  }
  ncopy = pos;
  if (ncopy >= cap)
    ncopy = cap - 1;
  out[ncopy] = '\0';
}

/**
 * Weak probe stub: Cap dladdr symbolicate (strong twin in platform.o).
 * PLATFORM: LINUX
 */
__attribute__((weak)) int32_t backtrace_symbolicate_c(const uint8_t *buf, int32_t len,
                                                      uint8_t *out_ptrs, uint8_t *out_names,
                                                      int32_t max) {
  int32_t ok = 0;
  int32_t n;
  int32_t i;
  if (!buf || len <= 0 || !out_names || max <= 0)
    return 0;
  n = len < max ? len : max;
  for (i = 0; i < n; i++) {
    void *addr;
    uint8_t *name_slot = out_names + (size_t)i * XLANG_BT_STUB_SYM_NAME_LEN;
    XlangBtDlInfo info;
    memcpy(&addr, buf + (size_t)i * sizeof(void *), sizeof(void *));
    if (out_ptrs)
      memcpy(out_ptrs + (size_t)i * sizeof(void *), &addr, sizeof(void *));
    memset(&info, 0, sizeof(info));
    if (xlang_bt_dladdr(addr, &info) && info.dli_sname && info.dli_sname[0]) {
      size_t k = 0;
      while (info.dli_sname[k] && k + 1 < (size_t)XLANG_BT_STUB_SYM_NAME_LEN) {
        name_slot[k] = (uint8_t)info.dli_sname[k];
        k++;
      }
      name_slot[k] = '\0';
      ok++;
    } else {
      xlang_bt_stub_hex_addr(name_slot, XLANG_BT_STUB_SYM_NAME_LEN, addr);
    }
  }
  return ok;
}

#elif defined(__APPLE__)

#define XLANG_BT_STUB_SYM_NAME_LEN 128

/** Write "0x" + hex digits for addr into out (Cap probe stub hex fallback). */
static void xlang_bt_stub_hex_addr(uint8_t *out, int32_t cap, void *addr) {
  static const char hx[] = "0123456789abcdef";
  uintptr_t v = (uintptr_t)addr;
  int32_t pos = 2;
  int32_t i;
  int32_t ncopy;
  if (!out || cap <= 0)
    return;
  out[0] = '0';
  out[1] = 'x';
  for (i = (int32_t)sizeof(void *) - 1; i >= 0; i--) {
    uint8_t b = (uint8_t)((v >> (i * 8)) & 0xffu);
    out[pos++] = (uint8_t)hx[(b >> 4) & 0x0fu];
    out[pos++] = (uint8_t)hx[b & 0x0fu];
  }
  ncopy = pos;
  if (ncopy >= cap)
    ncopy = cap - 1;
  out[ncopy] = '\0';
}

/**
 * Weak probe stub: Cap dladdr symbolicate on Darwin (strong twin in platform.o).
 * PLATFORM: MACOS|DARWIN
 */
__attribute__((weak)) int32_t backtrace_symbolicate_c(const uint8_t *buf, int32_t len,
                                                      uint8_t *out_ptrs, uint8_t *out_names,
                                                      int32_t max) {
  int32_t ok = 0;
  int32_t n;
  int32_t i;
  if (!buf || len <= 0 || !out_names || max <= 0)
    return 0;
  n = len < max ? len : max;
  for (i = 0; i < n; i++) {
    void *addr;
    uint8_t *name_slot = out_names + (size_t)i * XLANG_BT_STUB_SYM_NAME_LEN;
    XlangBtDlInfo info;
    memcpy(&addr, buf + (size_t)i * sizeof(void *), sizeof(void *));
    if (out_ptrs)
      memcpy(out_ptrs + (size_t)i * sizeof(void *), &addr, sizeof(void *));
    memset(&info, 0, sizeof(info));
    if (xlang_bt_dladdr(addr, &info) && info.dli_sname && info.dli_sname[0]) {
      size_t k = 0;
      while (info.dli_sname[k] && k + 1 < (size_t)XLANG_BT_STUB_SYM_NAME_LEN) {
        name_slot[k] = (uint8_t)info.dli_sname[k];
        k++;
      }
      name_slot[k] = '\0';
      ok++;
    } else {
      xlang_bt_stub_hex_addr(name_slot, XLANG_BT_STUB_SYM_NAME_LEN, addr);
    }
  }
  return ok;
}

#endif /* __linux__ | __APPLE__ symbolicate stubs */

#endif /* LINUX|DARWIN backtrace capture stub */
#endif /* !_WIN32 */

/*
 * Cap residual 9.1.12: weak xlang_target_cpu_detect_host for probes and runtime.
 * Strong twin in src/driver/target_cpu.o wins on full product link.
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS).
 */
__attribute__((weak)) uint32_t xlang_target_cpu_detect_host(void) {
#if defined(__linux__)
  char buf[8192];
  char *line;
  char *next;
  long n;
#if defined(__x86_64__)
  uint32_t f = 0;
  n = xlang_proc_read_file("/proc/cpuinfo", buf, sizeof(buf));
  if (n <= 0)
    return 1u; /* XLANG_CPU_FEAT_SSE2 macro fallback minimum */
  line = buf;
  while (line) {
    next = xlang_proc_next_line(line);
    if (strncmp(line, "flags", 5) == 0) {
      if (strstr(line, " sse2") || strstr(line, "\tsse2"))
        f |= 1u;
      if (strstr(line, " avx2"))
        f |= 8u;
      break;
    }
    line = next;
  }
  return f != 0 ? f : 1u;
#elif defined(__aarch64__)
  uint32_t f = 256u; /* XLANG_CPU_FEAT_NEON */
  n = xlang_proc_read_file("/proc/cpuinfo", buf, sizeof(buf));
  if (n <= 0)
    return f;
  line = buf;
  while (line) {
    next = xlang_proc_next_line(line);
    if (strncmp(line, "Features", 8) == 0) {
      if (strstr(line, " sve"))
        f |= 512u;
      break;
    }
    line = next;
  }
  return f;
#else
  return 0;
#endif

#elif defined(__APPLE__)
#if defined(__aarch64__)
  return 256u; /* XLANG_CPU_FEAT_NEON */
#elif defined(__x86_64__)
  return 1u | 2u; /* XLANG_CPU_FEAT_SSE2 | XLANG_CPU_FEAT_SSE41 */
#else
  return 0;
#endif

#elif defined(_WIN32) || defined(_WIN64)
#if defined(__x86_64__) || defined(_M_X64)
  return 1u; /* XLANG_CPU_FEAT_SSE2 */
#elif defined(__aarch64__) || defined(_M_ARM64)
  return 256u; /* XLANG_CPU_FEAT_NEON */
#else
  return 0;
#endif

#else
  return 0;
#endif
}

/** F-03：sync.x 机器码不在 io.o；本 TU 提供 io_write/io_read 同步 ABI。 */
ptrdiff_t io_write(int fd, const uint8_t *buf, size_t count, unsigned timeout_ms) {
  (void)timeout_ms;
  if (!buf && count > 0)
    return (ptrdiff_t)-1;
  return (ptrdiff_t)seed_io_syscall_write(fd, buf, (unsigned long)count);
}

/** 同步读；hello 等仅写 stdout 时 read 路径可为空实现。 */
ptrdiff_t io_read(int fd, uint8_t *buf, size_t count, unsigned timeout_ms) {
  (void)timeout_ms;
  if (!buf && count > 0)
    return (ptrdiff_t)-1;
  return (ptrdiff_t)seed_io_syscall_read(fd, buf, (unsigned long)count);
}

/** 与 io_read_ptr 配套的 TLS 缓冲（F-03 seed 桩：单线程单缓冲）。 */
static uint8_t g_io_read_ptr_buf[4096];
static int32_t g_io_read_ptr_len = 0;
/* Match std/io/read_ptr.x generation + backend cells (G.7 single buffer).
 * backend stays 0 in this TU — no mmap/io_uring here. */
static uint64_t g_io_read_ptr_gen = 0;
static int32_t g_io_read_ptr_backend = 0;

/** Zero-copy read into g_io_read_ptr_buf; EOF/error returns NULL.
 * PLATFORM: SHARED — handle is a POSIX fd (std.io from_fd is identity).
 * Historic restriction handle!=0 (stdin-only) dropped: cookbooks/tests
 * call io.read_ptr(from_fd(fd)) on a regular file. Length cell is the
 * same g_io_read_ptr_len used by std_io_ptr_len (G.7 single buffer).
 * Generation bumps on every call (read_ptr.x); backend forced 0. */
uint8_t *io_read_ptr(unsigned handle, unsigned timeout_ms) {
  ptrdiff_t r;
  (void)timeout_ms;
  g_io_read_ptr_gen = g_io_read_ptr_gen + 1;
  g_io_read_ptr_backend = 0;
  g_io_read_ptr_len = 0;
  r = io_read((int)handle, g_io_read_ptr_buf, sizeof g_io_read_ptr_buf, 0);
  if (r <= 0)
    return NULL;
  g_io_read_ptr_len = (int32_t)r;
  return g_io_read_ptr_buf;
}

/** Length of the last io_read_ptr fill (g_io_read_ptr_len).
 * Historic body always returned 0 (length stub), so ptr_len() never
 * observed a successful read. Complete the existing face (G.7).
 * PLATFORM: SHARED. */
int32_t io_read_ptr_len(void) {
  return g_io_read_ptr_len;
}

/** std.io.core 注册单缓冲桩。 */
int32_t io_register_buffer(uint8_t *ptr, size_t len) {
  (void)ptr;
  (void)len;
  return 0;
}

/** std.io.core 三参注册。
 * PLATFORM: SHARED — weak so that std/io/core.x export (strong T) wins when
 * user imports std.io.core; fallback when asm/standalone link omits core.x.
 * G.7 single authority: core.x is the strong impl; this stub is fallback only. */
XLANG_WEAK int32_t xlang_io_register(uint8_t *ptr, size_t len, size_t handle) {
  (void)handle;
  return io_register_buffer(ptr, len);
}

/** driver 侧 Buffer 描述符注册。 */
typedef struct { uint8_t *ptr; size_t length; size_t handle; } xlang_buffer_abi_t;
int32_t xlang_io_register_buf(intptr_t buf) {
  const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf;
  if (!b)
    return -1;
  return xlang_io_register(b->ptr, b->length, b->handle);
}

/** std.io.core submit_read 桩。
 * PLATFORM: SHARED — weak so that std/io/core.x export (strong T) wins when
 * user imports std.io.core; fallback when asm/standalone link omits core.x.
 * G.7 single authority: core.x is the strong impl; this stub is fallback only. */
XLANG_WEAK int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_ms) {
  (void)ptr;
  (void)len;
  (void)handle;
  (void)timeout_ms;
  return 0;
}

/** std.io.core submit_write 桩。
 * PLATFORM: SHARED — weak so that std/io/core.x export (strong T) wins when
 * user imports std.io.core; fallback when asm/standalone link omits core.x.
 * G.7 single authority: core.x is the strong impl; this stub is fallback only. */
XLANG_WEAK int32_t xlang_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_ms) {
  (void)ptr;
  (void)len;
  (void)handle;
  (void)timeout_ms;
  return 0;
}

size_t std_io_handle_stdin(void) {
  return 0;
}

size_t std_io_handle_stdout(void) {
  return 1;
}

size_t std_io_handle_stderr(void) {
  return 2;
}

/**
 * PLATFORM: SHARED — pure-asm import METHOD io.stdin()/stdout() mangle to bare
 * std_io_stdin / std_io_stdout (mod.x export surface). handle_* are historical
 * co-emit names; complete both faces here (G.7 stub authority).
 */
size_t std_io_stdin(void) {
  return std_io_handle_stdin();
}

size_t std_io_stdout(void) {
  return std_io_handle_stdout();
}

size_t std_io_stderr(void) {
  return std_io_handle_stderr();
}

int32_t std_io_write(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  ptrdiff_t r = io_write((int)handle, (const uint8_t *)ptr, len, timeout_ms);
  if (r < 0)
    return -1;
  return (int32_t)r;
}

int32_t std_io_read(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  ptrdiff_t r = io_read((int)handle, ptr, len, timeout_ms);
  if (r < 0)
    return -1;
  return (int32_t)r;
}

/* Unique std.io names (cookbook io_fallback_read / io_mmap_read).
 * Always-linked with std_io_read / std_io_write / std_io_ptr_len so we
 * complete this TU instead of a second buffer in io.o c_face (G.7).
 * from_fd ≡ (size_t)fd as in std/io/mod.x. read_fd/write_fd timeout=0.
 * PLATFORM: SHARED — product import mangle std_io_*. */
size_t std_io_from_fd(int32_t fd, int32_t unused) {
  (void)unused;
  return (size_t)fd;
}

int32_t std_io_read_fd(int32_t fd, uint8_t *ptr, size_t len) {
  return std_io_read((size_t)fd, ptr, len, 0);
}

int32_t std_io_write_fd(int32_t fd, uint8_t *ptr, size_t len) {
  return std_io_write((size_t)fd, ptr, len, 0);
}

/** stdout 写：供 std_io_write_stdout / write_with_timeout 桩使用。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-20 thin+rest：_impl 实现；thin（src/asm/runtime_asm_io_stubs.x）提供 public wrapper */
int32_t seed_io_write_fd1_impl(uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  ptrdiff_t r;
  if (!ptr && len > 0)
    return -1;
  r = io_write(1, (const uint8_t *)ptr, len, timeout_ms);
  if (r < 0)
    return -1;
  return (int32_t)r;
}

#ifndef XLANG_RUNTIME_ASM_IO_STUBS_FROM_X
/* 完整模式（未定义 thin 宏）：public wrapper 由 seed 提供 */
int32_t seed_io_write_fd1(uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  return seed_io_write_fd1_impl(ptr, len, timeout_ms);
}
#endif



int32_t std_io_print_i32(int32_t x) {
  (void)printf("%d\n", (int)x);
  return 0;
}

int32_t std_io_print_u32(uint32_t x) {
  (void)printf("%u\n", (unsigned)x);
  return 0;
}

int32_t std_io_print_i64(int64_t x) {
  (void)printf("%lld\n", (long long)x);
  return 0;
}

XLANG_WEAK int32_t std_io_write_stdout(uint8_t *ptr, size_t len) {
  return seed_io_write_fd1(ptr, len, 0);
}

XLANG_WEAK int32_t std_io_write_with_timeout(uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  return seed_io_write_fd1(ptr, len, timeout_ms);
}

/**
 * PLATFORM: SHARED — pure-asm overload mid for io.write(ptr,len,timeout):
 * std_io_write_u8_ptr_usize_u32 (tests/io/write_with_timeout.x). Forwards to
 * stdout write-with-timeout (3-arg product face). G.7 complete stub surface.
 */
int32_t std_io_write_u8_ptr_usize_u32(uint8_t *ptr, size_t len, uint32_t timeout_ms) {
  return seed_io_write_fd1(ptr, len, timeout_ms);
}

/** std.io.print(ptr,len) C ABI：mangled std_io_print_u8_ptr_usize。 */
XLANG_WEAK int32_t std_io_print_u8_ptr_usize(uint8_t *ptr, size_t len) {
  int32_t r = std_io_write_stdout(ptr, len);
  return (r >= 0) ? 0 : -1;
}

/** 兼容旧链接名 std_io_print_str。 */
XLANG_WEAK int32_t std_io_print_str(uint8_t *ptr, size_t len) {
  return std_io_print_u8_ptr_usize(ptr, len);
}

/** std.fmt.print(ptr,len): asm CALL surface when fmt is not co-emitted.
 * PLATFORM: SHARED — println without trailing newline; string-lit special path uses bare.
 * Authority: this TU only (G.7); LABI_STD_OP_IO_STUBS / ensure runtime_asm_io_stubs.o. */
int32_t std_fmt_print(uint8_t *ptr, size_t len) {
  int32_t r = std_io_print_str(ptr, len);
  return (r >= 0) ? 0 : -1;
}

/** Overload mid for print(*u8, i32) — import-binding mangle when fmt has many print overloads.
 * PLATFORM: SHARED — hello.x calls fmt.print(msg,12); pairs with bare std_fmt_print.
 * CALL may hit this symbol directly if redirect is skipped; G.7 complete stub surface. */
int32_t std_fmt_print_u8_ptr_i32(uint8_t *ptr, int32_t len) {
  if (len < 0)
    return -1;
  return std_fmt_print(ptr, (size_t)len);
}

/** std.fmt.println(ptr,len): print + single \\n; asm CALL surface (no fmt co-emit).
 * PLATFORM: SHARED — pairs with std_fmt_print; do not invent a second stub path. */
int32_t std_fmt_println(uint8_t *ptr, size_t len) {
  int32_t r = std_io_write_stdout(ptr, len);
  if (r < 0)
    return -1;
  uint8_t nl = 10;
  int32_t rn = std_io_write_stdout(&nl, 1);
  return (rn >= 0) ? 0 : -1;
}

/** Overload mid for println(*u8, i32) — same mangle contract as std_fmt_print_u8_ptr_i32. */
int32_t std_fmt_println_u8_ptr_i32(uint8_t *ptr, int32_t len) {
  if (len < 0)
    return -1;
  return std_fmt_println(ptr, (size_t)len);
}

/** M-5：u8[] slice ABI（与 mod.x / read_ptr.x XlangSliceU8 一致）。
 * Hoisted above fmt println_u8_slc so the overload mid can use the typedef.
 * PLATFORM: SHARED.
 */
typedef struct XlangSliceU8 {
  uint8_t *data;
  size_t length;
} XlangSliceU8;

/**
 * PLATFORM: SHARED — pure-asm scalar fmt.print/println when std.fmt is not co-emitted.
 * Call sites mangle to std_fmt_println_i32 / std_fmt_print_u32 / … (codegen + glue mid;
 * wave687 slice fix: no false println_i32_reti32). Authority: this TU only (G.7 complete
 * stub surface with string-lit print/println); do not invent a second path or formal
 * monofile co-emit of std.io for fmt.o. Matches tests/run-io.sh (i32/u32/i64).
 * Return 0 on success (printf write path); align std_io_print_i32.
 */
int32_t std_fmt_print_i32(int32_t x) {
  (void)printf("%d", (int)x);
  return 0;
}

int32_t std_fmt_println_i32(int32_t x) {
  (void)printf("%d\n", (int)x);
  return 0;
}

int32_t std_fmt_print_u32(uint32_t x) {
  (void)printf("%u", (unsigned)x);
  return 0;
}

int32_t std_fmt_println_u32(uint32_t x) {
  (void)printf("%u\n", (unsigned)x);
  return 0;
}

int32_t std_fmt_print_i64(int64_t x) {
  (void)printf("%lld", (long long)x);
  return 0;
}

int32_t std_fmt_println_i64(int64_t x) {
  (void)printf("%lld\n", (long long)x);
  return 0;
}

int32_t std_fmt_print_u64(uint64_t x) {
  (void)printf("%llu", (unsigned long long)x);
  return 0;
}

int32_t std_fmt_println_u64(uint64_t x) {
  (void)printf("%llu\n", (unsigned long long)x);
  return 0;
}

/**
 * PLATFORM: SHARED — pure-asm fmt.println(u8[]) / print(u8[]) overload mid.
 * Call sites mangle to std_fmt_println_u8_slc (glue_asm_type_ref_to_suffix_c TYPE_SLICE).
 *
 * ABI (G.7 single authority with host-C codegen + asm call_arg):
 *   TYPE_SLICE formals lower as `struct xlang_slice_* *` / fat-pointer address
 *   (call_arg packs SLICE→8; locals stay by-value). Stub MUST take a pointer —
 *   by-value XlangSliceU8 here made asm pass &fat into x0 while C expected
 *   {data,length} in x0/x1 → empty/err print (u8_slc by-value soft residual).
 */
int32_t std_fmt_print_u8_slc(const XlangSliceU8 *s) {
  if (s == NULL)
    return -1;
  return std_fmt_print(s->data, s->length);
}

int32_t std_fmt_println_u8_slc(const XlangSliceU8 *s) {
  if (s == NULL)
    return -1;
  return std_fmt_println(s->data, s->length);
}

/* ---- std.fmt / std.debug JSON "print any" (schema interpreter) ----
 * Schema (ASCII, NUL-terminated), offsets decimal relative to base:
 *   i@OFF          i32 at base+OFF
 *   b@OFF          bool (uint8) at base+OFF → true/false
 *   u@OFF,LEN      u8[LEN] as JSON string
 *   a@OFF,LEN      i32[LEN] as JSON array (inline / fixed T[N])
 *   A@OFF          i32[] fat at base+OFF ({data,len} 16B) → JSON array via data
 *   ?SOFF:VAL      if *(uint8*)(base+SOFF)==0 → null; else VAL
 *   {k:VAL,k:VAL}  JSON object (keys are identifiers)
 * Asm emit builds schema from type layout; G.7 single interpreter authority.
 * PLATFORM: SHARED — pairs with glue_asm_try_emit_fmt_any_import_call_elf_c.
 * u8[] (TYPE_SLICE of u8) stays mid std_fmt_*_u8_slc (raw bytes, not JSON).
 */

static void fmt_json_escape_byte(unsigned char c) {
  if (c == '\\' || c == '"') {
    putchar('\\');
    putchar((int)c);
  } else if (c == '\n') {
    fputs("\\n", stdout);
  } else if (c == '\r') {
    fputs("\\r", stdout);
  } else if (c == '\t') {
    fputs("\\t", stdout);
  } else if (c < 32) {
    printf("\\x%02x", (unsigned)c);
  } else {
    putchar((int)c);
  }
}

static const char *fmt_json_parse_dec(const char *p, int32_t *out) {
  int32_t v = 0;
  int neg = 0;
  if (p == NULL || out == NULL)
    return p;
  if (*p == '-') {
    neg = 1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    v = v * 10 + (int32_t)(*p - '0');
    p++;
  }
  *out = neg ? -v : v;
  return p;
}

static const char *fmt_json_emit_val(const uint8_t *base, const char *sch);

static const char *fmt_json_emit_val(const uint8_t *base, const char *sch) {
  int32_t off = 0;
  int32_t len = 0;
  int32_t i;
  if (sch == NULL)
    return sch;
  if (*sch == 'i' && sch[1] == '@') {
    sch = fmt_json_parse_dec(sch + 2, &off);
    if (base)
      printf("%d", (int)(*(const int32_t *)(base + off)));
    else
      fputs("0", stdout);
    return sch;
  }
  if (*sch == 'b' && sch[1] == '@') {
    sch = fmt_json_parse_dec(sch + 2, &off);
    if (base && base[off])
      fputs("true", stdout);
    else
      fputs("false", stdout);
    return sch;
  }
  if (*sch == 'u' && sch[1] == '@') {
    sch = fmt_json_parse_dec(sch + 2, &off);
    if (*sch == ',')
      sch++;
    sch = fmt_json_parse_dec(sch, &len);
    putchar('"');
    if (base && len > 0) {
      for (i = 0; i < len; i++)
        fmt_json_escape_byte(base[off + i]);
    }
    putchar('"');
    return sch;
  }
  if (*sch == 'a' && sch[1] == '@') {
    sch = fmt_json_parse_dec(sch + 2, &off);
    if (*sch == ',')
      sch++;
    sch = fmt_json_parse_dec(sch, &len);
    putchar('[');
    if (base && len > 0) {
      const int32_t *arr = (const int32_t *)(base + off);
      for (i = 0; i < len; i++) {
        if (i)
          putchar(',');
        printf("%d", (int)arr[i]);
      }
    }
    putchar(']');
    return sch;
  }
  /* A@OFF — TYPE_SLICE of i32: fat {data,len} at base+OFF (PLATFORM: SHARED ABI). */
  if (*sch == 'A' && sch[1] == '@') {
    const uint8_t *fat;
    const int32_t *arr;
    uint64_t n64;
    sch = fmt_json_parse_dec(sch + 2, &off);
    putchar('[');
    if (base) {
      fat = base + off;
      arr = *(const int32_t *const *)fat;
      n64 = *(const uint64_t *)(fat + 8);
      if (arr != NULL && n64 > 0 && n64 <= 1000000u) {
        len = (int32_t)n64;
        for (i = 0; i < len; i++) {
          if (i)
            putchar(',');
          printf("%d", (int)arr[i]);
        }
      }
    }
    putchar(']');
    return sch;
  }
  if (*sch == '?') {
    sch = fmt_json_parse_dec(sch + 1, &off);
    if (*sch == ':')
      sch++;
    if (base == NULL || base[off] == 0) {
      fputs("null", stdout);
      /* Skip VAL without emitting: walk nested braces / atoms. */
      if (*sch == '{') {
        int depth = 0;
        do {
          if (*sch == '{')
            depth++;
          else if (*sch == '}')
            depth--;
          sch++;
        } while (*sch && depth > 0);
        return sch;
      }
      if (*sch == 'i' || *sch == 'b' || *sch == 'u' || *sch == 'a' || *sch == 'A') {
        /* Re-enter skip by emitting into a discarded path — parse only. */
        const char *save = sch;
        /* Use a throwaway: parse structure without printing via recurse on null base for atoms. */
        (void)save;
        if (*sch == 'i' && sch[1] == '@') {
          sch = fmt_json_parse_dec(sch + 2, &off);
          return sch;
        }
        if (*sch == 'b' && sch[1] == '@') {
          sch = fmt_json_parse_dec(sch + 2, &off);
          return sch;
        }
        if (*sch == 'A' && sch[1] == '@') {
          sch = fmt_json_parse_dec(sch + 2, &off);
          return sch;
        }
        if ((*sch == 'u' || *sch == 'a') && sch[1] == '@') {
          sch = fmt_json_parse_dec(sch + 2, &off);
          if (*sch == ',')
            sch++;
          sch = fmt_json_parse_dec(sch, &len);
          return sch;
        }
      }
      return sch;
    }
    return fmt_json_emit_val(base, sch);
  }
  if (*sch == '{') {
    sch++;
    putchar('{');
    int first = 1;
    while (*sch && *sch != '}') {
      if (*sch == ',') {
        sch++;
        continue;
      }
      /* key until ':' */
      char key[64];
      int ki = 0;
      while (*sch && *sch != ':' && *sch != '}' && *sch != ',' && ki < 63) {
        key[ki++] = *sch++;
      }
      key[ki] = 0;
      if (*sch == ':')
        sch++;
      if (!first)
        putchar(',');
      first = 0;
      putchar('"');
      fputs(key, stdout);
      putchar('"');
      putchar(':');
      sch = fmt_json_emit_val(base, sch);
    }
    if (*sch == '}')
      sch++;
    putchar('}');
    return sch;
  }
  return sch;
}

/**
 * Print JSON for `base` per `schema`, then newline. Returns 0.
 * @param base value address (struct / array storage)
 * @param schema NUL-terminated schema (see above)
 * PLATFORM: SHARED — print_any / fmt-any product path.
 */
int32_t std_fmt_json_println_schema(const uint8_t *base, const char *schema) {
  if (schema == NULL)
    schema = "null";
  (void)fmt_json_emit_val(base, schema);
  putchar('\n');
  return 0;
}

/** Same without trailing newline (fmt.print). */
int32_t std_fmt_json_print_schema(const uint8_t *base, const char *schema) {
  if (schema == NULL)
    schema = "null";
  (void)fmt_json_emit_val(base, schema);
  return 0;
}

/** 兜底：未走 redirect 的 call 仍可直接链到 print_str。 */
int32_t print_str(uint8_t *ptr, size_t len) {
  return std_io_print_str(ptr, len);
}

uint8_t *std_io_read_stdin_ptr(void) {
  return io_read_ptr(0, 0);
}

int32_t std_io_ptr_len(void) {
  return io_read_ptr_len();
}

/** 兼容旧链接名。 */
int32_t std_io_read_ptr_len(void) {
  return std_io_ptr_len();
}

/* preamble / co-emit 使用 xlang_io_read_ptr*；与 io_read_ptr* 同实现（无 io.o 时）。 */
int32_t xlang_io_read_ptr_len(void) {
  return io_read_ptr_len();
}
uint8_t *xlang_io_read_ptr(size_t handle, unsigned timeout_ms) {
  return io_read_ptr((unsigned)handle, timeout_ms);
}

/**
 * Product import METHOD io.read_ptr → std_io_read_ptr.
 * Same cell as std_io_ptr_len / xlang_io_read_ptr (G.7; no c_face copy).
 * PLATFORM: SHARED.
 */
uint8_t *std_io_read_ptr(size_t handle, uint32_t timeout_ms) {
  return io_read_ptr((unsigned)handle, timeout_ms);
}

/**
 * Product import METHOD io.ptr_gen / ptr_valid / ptr_backend → std_io_ptr_*.
 * Unique UNDEF class for tests/io/read_ptr_mmap_smoke (G.7 complete this
 * always-linked TU; do not add labi needles or a c_face second buffer).
 * Semantics match std/io/read_ptr.x: gen is the last io_read_ptr bump;
 * valid is equality with that cell; backend is always 0.
 * mmap_smoke wants backend 1 or 2 and will return 9 — do not fake mmap.
 * PLATFORM: SHARED.
 */
uint64_t std_io_ptr_gen(void) {
  return g_io_read_ptr_gen;
}

int32_t std_io_ptr_valid(uint64_t saved) {
  return saved == g_io_read_ptr_gen ? 1 : 0;
}

int32_t std_io_ptr_backend(void) {
  return g_io_read_ptr_backend;
}

/**
 * Product import METHOD io.ptr_view / ptr_view_valid / stdin_ptr_view.
 * Unique UNDEF class for examples/cookbook/zc_read_ptr_slice (G.7 complete
 * this always-linked TU; do not add labi needles or a c_face second buffer).
 * Layout matches std/io/mod.x ReadPtrView {ptr, length, gen} with padding
 * after length (24B on 64-bit). Semantics: pack last read_ptr/len/gen;
 * valid is non-null ptr AND gen equals the gen cell.
 * PLATFORM: SHARED.
 */
typedef struct std_io_ReadPtrView {
  uint8_t *ptr;
  int32_t length;
  uint64_t gen;
} std_io_ReadPtrView;

std_io_ReadPtrView std_io_ptr_view(size_t handle, uint32_t timeout_ms) {
  std_io_ReadPtrView v;
  v.ptr = io_read_ptr((unsigned)handle, timeout_ms);
  v.length = io_read_ptr_len();
  v.gen = g_io_read_ptr_gen;
  return v;
}

int32_t std_io_ptr_view_valid(std_io_ReadPtrView v) {
  if (v.ptr == 0)
    return 0;
  return std_io_ptr_valid(v.gen);
}

std_io_ReadPtrView std_io_stdin_ptr_view(void) {
  return std_io_ptr_view(std_io_stdin(), 0);
}

/**
 * Product import METHOD io.register_provided / unregister_provided.
 * Unique UNDEF class for examples/cookbook/zc_provided_buffers (G.7 complete
 * this always-linked TU; do not add labi needles or a c_face second buffer).
 * Semantics match std/io/stubs.x: register always returns 0 (no io_uring
 * provided-buffer ring on this TU); unregister is a no-op.
 * Cookbook treats rc==1 as registered-then-unregister; stub path still
 * returns 0 from main. Do not fake a real buffer ring.
 * PLATFORM: SHARED.
 */
int32_t std_io_register_provided(uint32_t nr, uint32_t bufsz) {
  (void)nr;
  (void)bufsz;
  return 0;
}

void std_io_unregister_provided(void) {
}

/* XlangSliceU8 typedef: see above (hoisted for std_fmt_*_u8_slc). */

/** 零拷贝读 stdin slice；转发 io_read_ptr(0,0) 打包为 slice。 */
XlangSliceU8 std_io_read_stdin_ptr_slice(void) {
  XlangSliceU8 s;
  s.data = io_read_ptr(0, 0);
  s.length = s.data ? (size_t)g_io_read_ptr_len : 0;
  return s;
}

/**
 * PLATFORM: SHARED — pure-asm import METHOD io.stdin_slice() → std_io_stdin_slice.
 * Same body as std_io_read_stdin_ptr_slice (historical co-emit name). G.7 stub surface.
 * Used by tests/io/read_ptr*.x (run-io).
 */
XlangSliceU8 std_io_stdin_slice(void) {
  return std_io_read_stdin_ptr_slice();
}

/** 零拷贝读 slice；handle 0=stdin。 */
XlangSliceU8 std_io_read_ptr_slice(size_t handle, uint32_t timeout_ms) {
  XlangSliceU8 s;
  s.data = io_read_ptr((unsigned)handle, timeout_ms);
  s.length = s.data ? (size_t)g_io_read_ptr_len : 0;
  return s;
}

/**
 * 批量读桩：net/tcp 等链 net.o 时解析 io_read_batch；seed 路径退化为首段 io_read。
 * 参数 p1..p3 在桩 v1 中忽略，与 bootstrap_seed_io_stubs.c 行为一致。
 */
ptrdiff_t io_read_batch(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2,
                        size_t l2, uint8_t *p3, size_t l3, int32_t n, unsigned timeout_ms) {
  (void)p1;
  (void)l1;
  (void)p2;
  (void)l2;
  (void)p3;
  (void)l3;
  (void)n;
  return io_read(fd, p0, l0, timeout_ms);
}

/**
 * 批量写桩：net/tcp 等链 net.o 时解析 io_write_batch；seed 路径退化为首段 io_write。
 */
ptrdiff_t io_write_batch(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2,
                         size_t l2, uint8_t *p3, size_t l3, int32_t n, unsigned timeout_ms) {
  (void)p1;
  (void)l1;
  (void)p2;
  (void)l2;
  (void)p3;
  (void)l3;
  (void)n;
  return io_write(fd, p0, l0, timeout_ms);
}

/** driver.Buffer 批读写：与 std/io/sync.x 的 IoBatchBuf 布局一致（ptr+len 对）。 */
typedef struct XlangIoBatchBuf {
  uint8_t *ptr;
  size_t length;
} XlangIoBatchBuf;

/** 批量读 buf 桩：逐段 io_read 累加；timeout_ms 在桩 v1 中仅传给首段。 */
ptrdiff_t io_read_batch_buf(int32_t fd, const XlangIoBatchBuf *bufs, int32_t n, unsigned timeout_ms) {
  ptrdiff_t total = 0;
  int32_t i;
  if (!bufs || n <= 0)
    return (ptrdiff_t)-1;
  for (i = 0; i < n; i++) {
    ptrdiff_t r = io_read(fd, bufs[i].ptr, bufs[i].length, i == 0 ? timeout_ms : 0);
    if (r < 0)
      return r;
    total += r;
    if ((size_t)r < bufs[i].length)
      break;
  }
  return total;
}

/**
 * io_read_batch_provided 弱桩：io_batch.x 链 net.o 时解析；seed 路径返回 -1（无 io_uring provided）。
 */
XLANG_WEAK int32_t io_read_batch_provided(int32_t fd, int32_t n, uint32_t timeout_ms, uint32_t *out_bids,
                                                     uint32_t *out_lens) {
  (void)fd;
  (void)n;
  (void)timeout_ms;
  (void)out_bids;
  (void)out_lens;
  return -1;
}

/**
 * tcp.x Linux cfg 引用 io_uring_*；std.io 尚无独立 io.o 时由弱桩满足 net.o 合并后的 U 符号。
 * 真 io_uring 实现链入后覆盖弱符号。
 */
XLANG_WEAK int32_t io_uring_connect(uint32_t addr_u32, uint32_t port_u32, uint32_t timeout_ms) {
  (void)addr_u32;
  (void)port_u32;
  (void)timeout_ms;
  return -1;
}

XLANG_WEAK int32_t io_uring_accept(int32_t listener_fd, uint32_t timeout_ms) {
  (void)listener_fd;
  (void)timeout_ms;
  return -1;
}

XLANG_WEAK int32_t io_uring_accept_many(int32_t listener_fd, int32_t *out_fds, int32_t n, uint32_t timeout_ms) {
  (void)listener_fd;
  (void)out_fds;
  (void)n;
  (void)timeout_ms;
  return -1;
}

XLANG_WEAK int32_t io_uring_connect_many(uint32_t addr_u32, uint32_t port_u32, int32_t *out_fds, int32_t n,
                                                    uint32_t timeout_ms) {
  (void)addr_u32;
  (void)port_u32;
  (void)out_fds;
  (void)n;
  (void)timeout_ms;
  return -1;
}

XLANG_WEAK int32_t io_uring_prefetch_fd(int32_t fd) {
  (void)fd;
  return 0;
}

/** 批量写 buf 桩：逐段 io_write 累加。 */
ptrdiff_t io_write_batch_buf(int32_t fd, const XlangIoBatchBuf *bufs, int32_t n, unsigned timeout_ms) {
  ptrdiff_t total = 0;
  int32_t i;
  if (!bufs || n <= 0)
    return (ptrdiff_t)-1;
  for (i = 0; i < n; i++) {
    ptrdiff_t r = io_write(fd, bufs[i].ptr, bufs[i].length, i == 0 ? timeout_ms : 0);
    if (r < 0)
      return r;
    total += r;
    if ((size_t)r < bufs[i].length)
      break;
  }
  return total;
}

/*
 * F-03 无 io.o：co-emit 跳过 core 部分函数体，preamble 仅 extern 声明。
 * weak 桩补齐 hello 等 C 路径 -o 链接；真实实现由 co-emit / 强符号覆盖。
 * 【Why 根源】codegen_should_skip_emit_std_io_core_io_dup 假定 io.o 提供
 * xlang_io_read_fixed 等，但 Makefile 注释已标明「无 io.o」，导致 U 符号。
 */
XLANG_WEAK int32_t xlang_io_read_ptr_backend(void) { return g_io_read_ptr_backend; }
XLANG_WEAK int32_t xlang_io_read_fixed(size_t handle, uint32_t buf_index, size_t offset,
                                                 size_t len, uint32_t timeout_ms) {
  (void)handle; (void)buf_index; (void)offset; (void)len; (void)timeout_ms;
  return -1;
}
XLANG_WEAK int32_t xlang_io_write_fixed(size_t handle, uint32_t buf_index, size_t offset,
                                                  size_t len, uint32_t timeout_ms) {
  (void)handle; (void)buf_index; (void)offset; (void)len; (void)timeout_ms;
  return -1;
}
XLANG_WEAK int32_t xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle) {
  (void)ptr; (void)len; (void)handle;
  return -1;
}
XLANG_WEAK int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1,
                                                uint8_t *p2, size_t l2, uint8_t *p3, size_t l3,
                                                unsigned nr) {
  (void)p0; (void)l0; (void)p1; (void)l1; (void)p2; (void)l2; (void)p3; (void)l3; (void)nr;
  return -1;
}
XLANG_WEAK void io_unregister_buffers(void) {}
XLANG_WEAK int io_wait_readable(int32_t *fds, int n, unsigned timeout_ms) {
  (void)fds; (void)n; (void)timeout_ms;
  return 0;
}
/* driver 层 batch/submit：co-emit 可能仅声明；弱桩避免 hello 无条件链全量 std 时 U */
XLANG_WEAK int32_t std_io_driver_submit_read_batch(void *buffers, int32_t n,
                                                              uint32_t timeout_ms) {
  (void)buffers; (void)n; (void)timeout_ms;
  return -1;
}
XLANG_WEAK int32_t std_io_driver_submit_write_batch(void *buffers, int32_t n,
                                                               uint32_t timeout_ms) {
  (void)buffers; (void)n; (void)timeout_ms;
  return -1;
}
XLANG_WEAK int32_t std_io_driver_submit_read_batch_buf(size_t handle, void *bufs,
                                                                 int32_t n, uint32_t timeout_ms) {
  (void)handle; (void)bufs; (void)n; (void)timeout_ms;
  return -1;
}
XLANG_WEAK int32_t std_io_driver_submit_write_batch_buf(size_t handle, void *bufs,
                                                                  int32_t n, uint32_t timeout_ms) {
  (void)handle; (void)bufs; (void)n; (void)timeout_ms;
  return -1;
}
XLANG_WEAK uint64_t std_io_driver_driver_read_ptr_gen(void) { return g_io_read_ptr_gen; }
XLANG_WEAK int32_t std_io_driver_driver_read_ptr_backend(void) { return g_io_read_ptr_backend; }
/* sync 层：backend co-emit 转发到 std_io_sync_*；无定义时弱回退 */
XLANG_WEAK ptrdiff_t std_io_sync_io_read_fixed(int32_t fd, uint32_t buf_index, size_t offset,
                                                          size_t len, uint32_t timeout_ms) {
  (void)fd; (void)buf_index; (void)offset; (void)len; (void)timeout_ms;
  return (ptrdiff_t)-1;
}
XLANG_WEAK ptrdiff_t std_io_sync_io_write_fixed(int32_t fd, uint32_t buf_index, size_t offset,
                                                           size_t len, uint32_t timeout_ms) {
  (void)fd; (void)buf_index; (void)offset; (void)len; (void)timeout_ms;
  return (ptrdiff_t)-1;
}
XLANG_WEAK int32_t std_io_backend_io_read_ptr_backend(void) { return g_io_read_ptr_backend; }

/* page_mmap / freestanding heap 引用 xlang_sys_mmap；std/sys 未绿时 weak 回退到 libc mmap */
#if defined(__unix__) || defined(__APPLE__)
#ifndef _WIN32
#include <sys/mman.h>
XLANG_WEAK void *xlang_sys_mmap(void *addr, size_t length, int prot, int flags, int fd,
                                          int64_t offset) {
  return mmap(addr, length, prot, flags, fd, (off_t)offset);
}
XLANG_WEAK int xlang_sys_munmap(void *addr, size_t length) {
  return munmap(addr, length);
}
#endif
#endif

#if defined(__linux__) && defined(__GLIBC__)
#define XLANG_NET_UDP_GLUE_WEAK XLANG_WEAK
/* G-02f-259：.c 已 seed 化为 runtime_net_udp_batch.from_x.c（同目录 #include） */
#include "runtime_net_udp_batch.from_x.c"
#undef XLANG_NET_UDP_GLUE_WEAK
#endif
