/* seeds/bootstrap_nostdlib_stubs.from_x.c — G-02f-80 product cold-start TU
 * G-02f-114 true .x pure helpers.
 * G-02f-104 helper gates.
 * G-02f-103 helper gates.
 * Promoted from compiler/src/asm/bootstrap_nostdlib_stubs.inc (stub/bridge; retired .inc).
 * Compile: cc -c / cc_inc_tu seeds/bootstrap_nostdlib_stubs.from_x.c
 */
/**
 * bootstrap_nostdlib_stubs.c — NL-07 v2：编译器 bootstrap crt0 链 nostdlib 最小 libc 桩
 *
 * 【职责】
 * 当 XLANG_BOOTSTRAP_NOSTDLIB=1 时，与 crt0_x86_64.o + freestanding_io_x86_64.o 一并链入，
 * 替代 -lc/-lm，供 build_xlang_asm.sh crt0 路径尝试无 libc.so 静态链。
 *
 * 【范围】
 * 覆盖 bootstrap 链常见未定义符号：string/mem、stdio 最小格式化
 * （NL-07 L2 fflush；NL-07 L6 fileno/isatty/puts/strerror/fread/ferror/stdin/remove/__ctype_b_loc）、
 * getenv、libm（freestanding soft math，禁 __builtin_* 自递归）、fenv 空实现、posix_memalign、POSIX open/read/close/fstat/waitpid、
 * readlink/realpath/getcwd/opendir（NL-07 v5 runtime_link_abi / fmt_check 路径）、
 * getppid/kill/sigemptyset/sigaction（fmt_check spinner parent-death + Ctrl+C interrupt handlers；
 *   wave bare-check rebuild: Linux pure-ld nostdlib has no -lc, so these must live here）。
 * L1–L5 companions 后 residual 应仅为本 libc 面；失败时 build_xlang_asm 回退 -lc/-lm。
 *
 * 【依赖】
 * freestanding_io_x86_64.s 提供 xlang_sys_write / xlang_sys_mmap / xlang_sys_exit。
 */

#include <stddef.h>
#include <stdint.h>
#include <xlang_fmt_cap.h> /* also Cap va via xlang_va_cap (10.7.1) */ /* Cap residual 10.7.2: freestanding vsnprintf authority */
#include <xlang_fdprint_cap.h> /* Cap residual 9.5.4: format-to-fd write authority */
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif
#include <sys/time.h>
#ifndef _WIN32
#include <sys/resource.h>
#endif
#ifndef _WIN32
#include <sys/utsname.h>
#endif
#include <pthread.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#include <signal.h>
/** bootstrap opendir 用最小 dirent（勿链 libc libdl）。
 * 必须与 glibc <dirent.h> 的 struct dirent 布局一致（d_name 在 offset 19），
 * 否则 xlang_fmt_readdir_name（prelude #include <dirent.h>）的 ent->d_name 偏移错误。
 * wave1241: 修复 Ubuntu check 命令截断 19 字符 bug。PLATFORM: Linux x86_64。 */
struct dirent {
    uint64_t d_ino;
    int64_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[256];
};

/** 不透明目录流；见 opendir/readdir/closedir。 */
typedef struct bootstrap_dir DIR;

/** FILE 最小占位；bootstrap 区分 stdin/stdout/stderr（fd 0/1/2）。 */
struct _bootstrap_file {
    int fd;
};
typedef struct _bootstrap_file FILE;

static FILE bootstrap_stdin_file = { 0 };
static FILE bootstrap_stdout_file = { 1 };
static FILE bootstrap_stderr_file = { 2 };

FILE *stdin = &bootstrap_stdin_file;
FILE *stdout = &bootstrap_stdout_file;
FILE *stderr = &bootstrap_stderr_file;

/** 线程局部 errno 占位。 */
static int bootstrap_errno;

/** nostdlib crt0 无 libc _start：由 bootstrap_init_environ 从 argv 后填充。 */
char **environ;

/** 返回 errno 指针；满足链接对 __errno_location 的引用。 */
int *__errno_location(void) {
    return &bootstrap_errno;
}

/** freestanding syscall 门面（见 freestanding_io_x86_64.s）。 */
extern long xlang_sys_write(int fd, const void *buf, unsigned long len);
extern long xlang_sys_read(int fd, void *buf, unsigned long len);
extern long xlang_sys_close(int fd);
extern void *xlang_sys_mmap(void *addr, unsigned long len, int prot, int flags, int fd, long off);
extern long xlang_sys_munmap(void *addr, unsigned long len);
extern void xlang_sys_exit(int code) __attribute__((noreturn));

#ifndef ARCH_SET_FS
#define ARCH_SET_FS 0x1002
#endif
#ifndef SYS_arch_prctl
#define SYS_arch_prctl 158
#endif

/**
 * NL-07 v5 / 2026-09-05 complete: nostdlib static has no glibc TLS.
 * x86-64 SysV: FS = TCB; PT_TLS lives at [FS - p_memsz, FS); canary at FS+0x28.
 *
 * The original 48-byte block only covered the canary. gcc initial-exec
 * __thread stores (parser binop-peek PT_TLS memsz=0x70) use negative FS
 * offsets and wrote into BSS, zeroing `environ`. Then execve(..., NULL)
 * made gcc 15 posix_spawnp("cc1") ENOENT after L4 wipe (ensure rebuilds
 * runtime_link_abi_user_env.o via cc).
 *
 * G.7: complete this function; do not add a second TLS init.
 * PLATFORM: LINUX x86_64 nostdlib (crt0_x86_64.s calls this before main).
 */
#if defined(__linux__) && defined(__x86_64__)
#ifndef PT_TLS
#define PT_TLS 7
#endif
/* Storage cap: PT_TLS p_memsz + TCB. Today p_memsz=0x70; mmap if larger. */
#define BOOTSTRAP_TLS_IMG_CAP 4096u
#define BOOTSTRAP_TCB_LEN 64u

static unsigned char bootstrap_tls_area[BOOTSTRAP_TLS_IMG_CAP + BOOTSTRAP_TCB_LEN]
    __attribute__((aligned(16)));

struct bootstrap_elf64_ehdr {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

struct bootstrap_elf64_phdr {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
};

extern char __executable_start[] __attribute__((weak));

static unsigned long bootstrap_read_pt_tls_memsz(void) {
    const struct bootstrap_elf64_ehdr *eh;
    const struct bootstrap_elf64_phdr *ph;
    unsigned int i;
    unsigned int n;
    if (!__executable_start)
        return 0;
    eh = (const struct bootstrap_elf64_ehdr *)(const void *)__executable_start;
    if (eh->e_ident[0] != 0x7f || eh->e_ident[1] != 'E' ||
        eh->e_ident[2] != 'L' || eh->e_ident[3] != 'F')
        return 0;
    if (eh->e_phentsize != (uint16_t)sizeof(struct bootstrap_elf64_phdr))
        return 0;
    ph = (const struct bootstrap_elf64_phdr *)(const void *)((const char *)eh + eh->e_phoff);
    n = eh->e_phnum;
    for (i = 0; i < n; i++) {
        if (ph[i].p_type == (uint32_t)PT_TLS)
            return (unsigned long)ph[i].p_memsz;
    }
    return 0;
}

void bootstrap_init_static_tls(void) {
    unsigned long tls_len;
    unsigned long fs;
    unsigned long *guard;
    unsigned char *img;
    long ret;

    tls_len = bootstrap_read_pt_tls_memsz();
    if (tls_len == 0)
        tls_len = 256;
    tls_len = (tls_len + 15ul) & ~15ul;
    img = bootstrap_tls_area;
    if (tls_len > BOOTSTRAP_TLS_IMG_CAP) {
        /* PROT_READ|PROT_WRITE=3, MAP_PRIVATE|MAP_ANONYMOUS=0x22 */
        img = (unsigned char *)xlang_sys_mmap((void *)0, tls_len + BOOTSTRAP_TCB_LEN,
                                              3, 0x22, -1, 0);
        if (!img || img == (unsigned char *)(long)-1) {
            tls_len = BOOTSTRAP_TLS_IMG_CAP;
            img = bootstrap_tls_area;
        }
    }
    /* FS = TCB; __thread slots are at FS - tls_len .. FS-1. */
    fs = (unsigned long)(img + tls_len);
    guard = (unsigned long *)(fs + 0x28);
    *guard = 0xdeadbeefdeadbeefUL ^ fs;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(158L), "D"(0x1002L), "S"(fs) : "rcx", "r11", "memory");
    (void)ret;
}
#else
struct bootstrap_tls_block {
    char pad[0x28];
    unsigned long stack_guard;
};

static struct bootstrap_tls_block bootstrap_tls;

void bootstrap_init_static_tls(void) {
    long ret;
    unsigned long tls_base = (unsigned long)&bootstrap_tls;
    bootstrap_tls.stack_guard =
        (unsigned long)0xdeadbeefdeadbeefUL ^ tls_base;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(158L), "D"(0x1002L), "S"(tls_base) : "rcx", "r11", "memory");
    (void)ret;
}
#endif

/**
 * NL-07 v5：自定义 crt0 不链 libc _start，须从栈布局 argv[argc+1]… 初始化 environ。
 * 由 crt0_x86_64.s _start 在 main_entry 前调用（rdi=argc, rsi=argv）。
 */
void bootstrap_init_environ(int argc, char **argv) {
    if (!argv || argc < 0) {
        environ = NULL;
        return;
    }
    environ = &argv[argc + 1];
}

/** 返回 1：driver_run_thread_on_large_stack 须在当前线程执行（pthread 桩不同步分配栈）。 */
int bootstrap_nostdlib_pthread_is_stub(void) {
    return 1;
}

/** 内存拷贝；bootstrap 链常见 libgcc/libc 引用。 */
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    size_t i;
    if (!dest || !src)
        return dest;
    for (i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

/** 内存移动；重叠区从后向前复制。 */
void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    size_t i;
    if (!dest || !src)
        return dest;
    if (d == s || n == 0)
        return dest;
    if (d < s) {
        for (i = 0; i < n; i++)
            d[i] = s[i];
    } else {
        for (i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }
    return dest;
}

/** 内存填充。 */
void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    unsigned char b = (unsigned char)c;
    size_t i;
    if (!s)
        return s;
    for (i = 0; i < n; i++)
        p[i] = b;
    return s;
}

/** 内存比较；相等返回 0。 */
int memcmp(const void *a, const void *b, size_t n) {
    const unsigned char *p = (const unsigned char *)a;
    const unsigned char *q = (const unsigned char *)b;
    size_t i;
    for (i = 0; i < n; i++) {
        if (p[i] != q[i])
            return (int)p[i] - (int)q[i];
    }
    return 0;
}

/** C 字符串长度。 */
size_t strlen(const char *s) {
    size_t n = 0;
    if (!s)
        return 0;
    while (s[n])
        n++;
    return n;
}

/** 返回 s 中首个落在 reject 集内的字符偏移；未命中则返回 strlen(s)。 */
size_t strcspn(const char *s, const char *reject) {
    size_t i;
    size_t j;
    if (!s)
        return 0;
    if (!reject || !reject[0])
        return strlen(s);
    for (i = 0; s[i]; i++) {
        for (j = 0; reject[j]; j++) {
            if (s[i] == reject[j])
                return i;
        }
    }
    return i;
}

/** POSIX write；转 xlang_sys_write。 */
long write(int fd, const void *buf, unsigned long count) {
    return xlang_sys_write(fd, buf, count);
}

/** 栈保护失败；直接退出（bootstrap 烟测路径）。 */
void __stack_chk_fail(void) {
    xlang_sys_exit(127);
}

/** abort 等价；bootstrap 无 stderr 格式化。 */
void abort(void) {
    xlang_sys_exit(134);
}

/** 简单 mmap bump 分配器（MAP_PRIVATE | ANONYMOUS = 0x22 on Linux x86_64）。 */
static unsigned char *bootstrap_heap_base;
static unsigned char *bootstrap_heap_end;
static unsigned char *bootstrap_heap_limit;

/* thin+rest：thin 函数在 rest 模式下由 .x 提供，前向声明供 rest 函数调用 */
size_t bootstrap_align16(size_t n);
int bootstrap_heap_grow(size_t need);
int bootstrap_format_double(double x, char *out, size_t cap);
int bootstrap_vfprintf_fd(int fd, const char *fmt, xlang_va_list ap);
#if defined(__linux__) && defined(__x86_64__)
long bootstrap_syscall3(long nr, long a0, long a1, long a2);
long bootstrap_syscall4(long nr, long a0, long a1, long a2, long a3);
#endif

/** 对齐到 16 字节边界。 */
#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-114：逻辑源 .x（真迁）；DIRECT 模式，rest 模式下 seed 不提供 */
size_t bootstrap_align16(size_t n) {
  return (n + 15u) & ~(size_t)15u;
}
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */



/** 扩展 bump 区；失败返回 NULL。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int bootstrap_heap_grow_impl(size_t need) {
    unsigned long chunk = 1024UL * 1024UL;
    void *p;
    if (need > chunk)
        chunk = (unsigned long)((need + 65535UL) & ~65535UL);
    p = xlang_sys_mmap(0, chunk, 3 /* PROT_READ|PROT_WRITE */, 0x22 /* MAP_PRIVATE|MAP_ANONYMOUS */, -1, 0);
    if (!p || p == (void *)(intptr_t)-1)
        return -1;
    bootstrap_heap_base = (unsigned char *)p;
    bootstrap_heap_end = bootstrap_heap_base;
    bootstrap_heap_limit = bootstrap_heap_base + chunk;
    return 0;
}

#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/bootstrap_nostdlib_stubs.x）提供 wrapper 调用 _impl */
int bootstrap_heap_grow(size_t need) { return bootstrap_heap_grow_impl(need); }
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */




/*
 * PLATFORM: SHARED — freestanding bump heap for XLANG_BOOTSTRAP_NOSTDLIB / static xlang_asm.
 *
 * Layout of every live block:
 *   [HeapHdr size (16 B, 16-aligned)][user payload ...]
 * malloc/calloc return the payload pointer; free is still a no-op (bump).
 *
 * Why the header: realloc must copy min(old_user_size, new_size). The previous
 * "memcpy(n, ptr, size)" used the *new* size while the old payload was only
 * old_size bytes. On grow (e.g. GrowVec 256→4352 × sizeof(ast_Expr)), that
 * read past the old block into unmapped pages → intermittent Ubuntu SIGSEGV
 * under ASLR (~50% on large -E; setarch -R 0%; small files OK). GDB often
 * hid it via different layout.
 *
 * Authority: this seed TU only (G.7). .x thin does not reimplement malloc.
 */
/* 大块阈值：>1MB 的分配单独 mmap，header.flags 记 mmap_size 以便 free/realloc munmap 回收。
 * Why: bump realloc 对大块 malloc+copy+不释放旧块，反复 grow 累积致 SIGKILL
 *      (check 处理 codegen.x 时 buffer grow 600MB ×17 ≈ 10GB)。
 *      macOS libc realloc 用 mremap 原地扩展无此问题；nostdlib 需大块独立回收。
 * Invariant: 大块 header.flags>0 且 ==mmap_size；小块 header.flags==0。
 * Asm/Perf: 大块单独 mmap 对齐 64K；realloc 大块需 copy（无 mREMAP），但不累积。 */
#define BOOTSTRAP_BIG_THRESHOLD (1024UL * 1024UL)
typedef struct {
  size_t user_size; /* exact size requested by the last malloc/realloc for this block */
  size_t flags;     /* 0=small(bump pool); >0=big(standalone mmap, value=mmap_size) */
} BootstrapHeapHdr;

/** malloc: 大块(>1MB)单独 mmap 可回收；小块 bump pool。 */
void *malloc(size_t size) {
    size_t need;
    size_t payload;
    unsigned char *raw;
    BootstrapHeapHdr *hdr;
    if (size == 0)
        return NULL;
    if (size > BOOTSTRAP_BIG_THRESHOLD) {
        size_t big_mmap_size;
        void *bp;
        payload = bootstrap_align16(size);
        need = sizeof(BootstrapHeapHdr) + payload;
        big_mmap_size = (need + 65535UL) & ~65535UL;
        bp = xlang_sys_mmap(0, big_mmap_size, 3, 0x22, -1, 0);
        if (!bp || (uintptr_t)bp >= (uintptr_t)-4095)
            return NULL;
        hdr = (BootstrapHeapHdr *)bp;
        hdr->user_size = size;
        hdr->flags = big_mmap_size;
        return (void *)((unsigned char *)bp + sizeof(BootstrapHeapHdr));
    }
    payload = bootstrap_align16(size);
    need = sizeof(BootstrapHeapHdr) + payload;
    if (!bootstrap_heap_end || bootstrap_heap_end + need > bootstrap_heap_limit) {
        if (bootstrap_heap_grow(need) != 0)
            return NULL;
    }
    raw = bootstrap_heap_end;
    bootstrap_heap_end += need;
    hdr = (BootstrapHeapHdr *)(void *)raw;
    hdr->user_size = size;
    hdr->flags = 0;
    return (void *)(raw + sizeof(BootstrapHeapHdr));
}

/** free: 大块 munmap 回收；小块 bump no-op。 */
void free(void *ptr) {
    BootstrapHeapHdr *hdr;
    if (!ptr)
        return;
    hdr = (BootstrapHeapHdr *)(void *)((unsigned char *)ptr - sizeof(BootstrapHeapHdr));
    if (hdr->flags > 0)
        xlang_sys_munmap(hdr, (unsigned long)hdr->flags);
    /* 小块：bump no-op */
}

/** calloc minimal: malloc then zero user_size bytes. */
void *calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void *p = malloc(total);
    if (p)
        memset(p, 0, total);
    return p;
}

/** realloc: allocate new block; copy min(old_user_size, size); 旧大块 munmap 回收。
 * PLATFORM: SHARED — must not memcpy with `size` when growing (OOB read).
 * Why: 旧大块若不 munmap，反复 realloc grow 累积致 SIGKILL（bump no-op free）。 */
void *realloc(void *ptr, size_t size) {
    BootstrapHeapHdr *old_hdr;
    size_t old_size;
    size_t ncopy;
    void *n;
    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    old_hdr = (BootstrapHeapHdr *)(void *)((unsigned char *)ptr - sizeof(BootstrapHeapHdr));
    old_size = old_hdr->user_size;
    n = malloc(size);
    if (!n)
        return NULL;
    ncopy = old_size < size ? old_size : size;
    if (ncopy > 0)
        memcpy(n, ptr, ncopy);
    if (old_hdr->flags > 0)
        xlang_sys_munmap(old_hdr, (unsigned long)old_hdr->flags);
    return n;
}

/** C 字符串比较；相等返回 0。 */
int strcmp(const char *a, const char *b) {
    size_t i = 0;
    if (!a || !b)
        return (a == b) ? 0 : (a ? 1 : -1);
    while (a[i] && a[i] == b[i])
        i++;
    return (unsigned char)a[i] - (unsigned char)b[i];
}

/** 限定长度字符串比较。 */
int strncmp(const char *a, const char *b, size_t n) {
    size_t i;
    if (!a || !b)
        return (a == b) ? 0 : (a ? 1 : -1);
    for (i = 0; i < n; i++) {
        if (a[i] != b[i] || a[i] == '\0')
            return (unsigned char)a[i] - (unsigned char)b[i];
    }
    return 0;
}

/** 字符串拷贝；返回 dest。 */
char *strcpy(char *dest, const char *src) {
  char *d = dest;
  if (!dest || !src)
    return dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

/** 字符串拼接；dest 须有足够空间。 */
char *strcat(char *dest, const char *src) {
  size_t dlen;
  if (!dest || !src)
    return dest;
  dlen = strlen(dest);
  strcpy(dest + dlen, src);
  return dest;
}

/** strtol 最小实现：支持 base 0/10/16 与正负号。 */
long strtol(const char *nptr, char **endptr, int base) {
  const char *p = nptr;
  long sign = 1;
  long val = 0;
  if (!nptr) {
    if (endptr)
      *endptr = (char *)nptr;
    return 0;
  }
  while (*p == ' ' || *p == '\t' || *p == '\n')
    p++;
  if (*p == '-') {
    sign = -1;
    p++;
  } else if (*p == '+') {
    p++;
  }
  if (base == 0) {
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
      base = 16;
      p += 2;
    } else if (p[0] == '0') {
      base = 8;
      p++;
    } else {
      base = 10;
    }
  } else if (base == 16 && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
    p += 2;
  }
  while (*p) {
    int digit = -1;
    if (*p >= '0' && *p <= '9')
      digit = *p - '0';
    else if (*p >= 'a' && *p <= 'z')
      digit = 10 + (*p - 'a');
    else if (*p >= 'A' && *p <= 'Z')
      digit = 10 + (*p - 'A');
    if (digit < 0 || digit >= base)
      break;
    val = val * base + digit;
    p++;
  }
  if (endptr)
    *endptr = (char *)p;
  return sign * val;
}

/** strtoul 最小实现：委托 strtol，负值钳制为 0（XLANG_STACK_LIMIT_MB 等环境变量解析）。 */
unsigned long strtoul(const char *nptr, char **endptr, int base) {
  long v = strtol(nptr, endptr, base);
  if (v < 0)
    return 0UL;
  return (unsigned long)v;
}

/** glibc 2.38+ 可能把 strto* 重写到 __isoc23_*；nostdlib 链直接回落到本地最小实现。 */
long __isoc23_strtol(const char *nptr, char **endptr, int base) {
  return strtol(nptr, endptr, base);
}

/** 兼容 glibc 新符号名，避免 runtime_driver_abi / pipeline_x 在 nostdlib 链丢失解析符号。 */
unsigned long __isoc23_strtoul(const char *nptr, char **endptr, int base) {
  return strtoul(nptr, endptr, base);
}

/** mmap 最小包装：将裸 syscall 的负 errno 返回归一化为 MAP_FAILED。 */
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off) {
  uintptr_t raw = (uintptr_t)xlang_sys_mmap(addr, (unsigned long)len, prot, flags, fd, (long)off);
  if (raw >= (uintptr_t)-4095) {
    bootstrap_errno = -(int)(intptr_t)raw;
    return (void *)-1;
  }
  return (void *)raw;
}

/** munmap 最小包装：将裸 syscall 的负 errno 返回归一化为 -1。 */
int munmap(void *addr, size_t len) {
  long rc = xlang_sys_munmap(addr, (unsigned long)len);
  if (rc < 0) {
    bootstrap_errno = (int)(-rc);
    return -1;
  }
  return 0;
}

/** 限定长度拷贝；保证 dest 以 NUL 结尾。 */
char *strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    if (!dest || !src)
        return dest;
    for (i = 0; i < n && src[i]; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

/** 堆上复制字符串；失败返回 NULL。 */
char *strdup(const char *s) {
    size_t n;
    char *p;
    if (!s)
        return NULL;
    n = strlen(s) + 1;
    p = (char *)malloc(n);
    if (p)
        memcpy(p, s, n);
    return p;
}

void bootstrap_flush_stdio_and_exit(int code);

/** 进程退出；先 flush stdio（与 crt0 同源），再 sys_exit。 */
void exit(int code) {
    bootstrap_flush_stdio_and_exit(code);
}

/**
 * getenv：遍历 bootstrap_init_environ 设置的 environ（与 Linux 进程 envp 布局一致）。
 */
char *getenv(const char *name) {
    char **ep;
    size_t nlen;
    if (!name || !environ)
        return NULL;
    nlen = strlen(name);
    for (ep = environ; *ep; ep++) {
        if (strncmp(*ep, name, nlen) == 0 && (*ep)[nlen] == '=')
            return *ep + nlen + 1;
    }
    return NULL;
}

/** 对齐分配；用 bump malloc + 手动对齐。 */
int posix_memalign(void **memptr, size_t alignment, size_t size) {
    uintptr_t raw;
    uintptr_t aligned;
    size_t total;
    void *block;
    if (!memptr || alignment < sizeof(void *) || (alignment & (alignment - 1)) != 0)
        return 22; /* EINVAL */
    if (size == 0) {
        *memptr = NULL;
        return 0;
    }
    total = size + alignment + sizeof(void *);
    block = malloc(total);
    if (!block)
        return 12; /* ENOMEM */
    raw = (uintptr_t)block + sizeof(void *);
    aligned = (raw + alignment - 1) & ~(uintptr_t)(alignment - 1);
    ((void **)aligned)[-1] = block;
    *memptr = (void *)aligned;
    return 0;
}

/** Cap residual 10.7.2: float decimal — thin wrap over xlang_format_double (G.7).
 * PLATFORM: SHARED — nostdlib TU; logic lives in xlang_fmt_cap.h. */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
int bootstrap_format_double_impl(double x, char *out, size_t cap) {
    return xlang_format_double(x, out, cap);
}

#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/bootstrap_nostdlib_stubs.x）提供 wrapper 调用 _impl */
int bootstrap_format_double(double x, char *out, size_t cap) { return bootstrap_format_double_impl(x, out, cap); }
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */




/**
 * Minimal vsnprintf — Cap residual 10.7.2 thin wrap (G.7: body in xlang_fmt_cap.h).
 *
 * PLATFORM: SHARED — nostdlib freestanding face; symbol name remains libc-compatible.
 *
 * NL-07 L4: Cap honors %.*s / * width so product diagnostics stay va-aligned.
 */
int vsnprintf(char *buf, size_t size, const char *fmt, xlang_va_list ap) {
    return xlang_vsnprintf(buf, size, fmt, ap);
}

/** snprintf — Cap residual 10.7.2 thin wrap over xlang_vsnprintf. */
int snprintf(char *buf, size_t size, const char *fmt, ...) {
    xlang_va_list ap;
    int n;
    xlang_va_start(ap, fmt);
    n = xlang_vsnprintf(buf, size, fmt, ap);
    xlang_va_end(ap);
    return n;
}

/** 向 fd 格式化输出；返回写入字节数。 */
/* Cap residual 9.5.4: "vsnprintf + write" combo — thin wrap over xlang_vfdprintf
 * (G.7: body in xlang_fdprint_cap.h). Bounded 512-byte face (no heap): the
 * nostdlib chain prints short diagnostic lines (spinner, per-line check
 * summary, usage), so the old malloc heap-grow path is retired. */
int bootstrap_vfprintf_fd_impl(int fd, const char *fmt, xlang_va_list ap) {
    return xlang_vfdprintf(fd, fmt, ap);
}

#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/bootstrap_nostdlib_stubs.x）提供 wrapper 调用 _impl
 * 类型擦除：.x 侧 ap 参数为 *u8，seed 前向声明用 xlang_va_list，C 链接器不看类型，ABI 兼容 */
int bootstrap_vfprintf_fd(int fd, const char *fmt, xlang_va_list ap) { return bootstrap_vfprintf_fd_impl(fd, fmt, ap); }
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */




/** fprintf 最小实现；仅 stdout/stderr fd 路径。 */
int fprintf(FILE *stream, const char *fmt, ...) {
    xlang_va_list ap;
    int n;
    int fd = 1;
    if (stream == stderr)
        fd = 2;
    xlang_va_start(ap, fmt);
    n = bootstrap_vfprintf_fd(fd, fmt, ap);
    xlang_va_end(ap);
    return n;
}

/** vfprintf 最小实现；供 _FORTIFY_SOURCE 重定向桩使用。 */
int vfprintf(FILE *stream, const char *fmt, xlang_va_list ap) {
    int fd = 1;
    if (stream == stderr)
        fd = 2;
    else if (stream != stdout)
        return -1;
    return bootstrap_vfprintf_fd(fd, fmt, ap);
}

/** glibc _FORTIFY_SOURCE：nostdlib 链 fmt_check_cmd_driver.o 需要。 */
int __fprintf_chk(FILE *stream, int flag, const char *fmt, ...) {
    xlang_va_list ap;
    int n;
    (void)flag;
    xlang_va_start(ap, fmt);
    n = vfprintf(stream, fmt, ap);
    xlang_va_end(ap);
    return n;
}

/** glibc _FORTIFY_SOURCE：nostdlib 链 snprintf 重定向。 */
int __snprintf_chk(char *s, size_t maxlen, int flag, size_t slen, const char *fmt, ...) {
    xlang_va_list ap;
    int n;
    (void)flag;
    (void)slen;
    if (!s || maxlen == 0)
        return -1;
    xlang_va_start(ap, fmt);
    n = vsnprintf(s, maxlen, fmt, ap);
    xlang_va_end(ap);
    return n;
}

/** printf 最小实现。 */
int printf(const char *fmt, ...) {
    xlang_va_list ap;
    int n;
    xlang_va_start(ap, fmt);
    n = bootstrap_vfprintf_fd(1, fmt, ap);
    xlang_va_end(ap);
    return n;
}

/* ── freestanding soft libm（替代 -lm；禁 __builtin_* 同名自递归）──
 *
 * PLATFORM: SHARED soft-math semantics / LINUX+MACOS product nostdlib link face.
 * Authority (G.7): this TU only for freestanding pure-static libm symbols.
 * Hosted product std.math still uses runtime_math_libm.from_x.c + host -lm.
 *
 * Root cause of prior hang/warning: defining `double erfc(x){return __builtin_erfc(x);}`
 * (and sin/exp/floor/…) lowers to a call of the same symbol when the builtin is not a
 * hardware intrinsic → infinite recursion (Ubuntu -Winfinite-recursion; mac/Linux hang).
 * Fix: real soft implementations via static helpers with distinct names; public faces
 * only forward to helpers (never call public sin from inside soft_sin body).
 *
 * Quality: enough for std.math smoke (floor/ceil/sqrt/abs + STD-115 erf/erfc/log1p/expm1
 * at ~1e-6..1e-12 on gold samples). Not a full IEEE libm replacement.
 */

typedef union {
    double d;
    uint64_t u;
} xlang_soft_f64bits;

/** Absolute value via sign-bit clear (no libm). */
static double xlang_soft_fabs(double x) {
    xlang_soft_f64bits b;
    b.d = x;
    b.u &= 0x7fffffffffffffffull;
    return b.d;
}

/** True if IEEE-754 quiet/signaling NaN. */
static int xlang_soft_isnan(double x) {
    xlang_soft_f64bits b;
    b.d = x;
    return ((b.u & 0x7ff0000000000000ull) == 0x7ff0000000000000ull) &&
           ((b.u & 0x000fffffffffffffull) != 0ull);
}

/** True if ±Inf. */
static int xlang_soft_isinf(double x) {
    xlang_soft_f64bits b;
    b.d = x;
    return (b.u & 0x7fffffffffffffffull) == 0x7ff0000000000000ull;
}

/** Copy sign bit of s onto magnitude of m. */
static double xlang_soft_copysign(double m, double s) {
    xlang_soft_f64bits bm, bs;
    bm.d = m;
    bs.d = s;
    bm.u = (bm.u & 0x7fffffffffffffffull) | (bs.u & 0x8000000000000000ull);
    return bm.d;
}

/** Min; NaN policy: prefer non-NaN when one is NaN (simple freestanding). */
static double xlang_soft_fmin(double a, double b) {
    if (xlang_soft_isnan(a))
        return b;
    if (xlang_soft_isnan(b))
        return a;
    return a < b ? a : b;
}

/** Max; NaN policy: prefer non-NaN when one is NaN. */
static double xlang_soft_fmax(double a, double b) {
    if (xlang_soft_isnan(a))
        return b;
    if (xlang_soft_isnan(b))
        return a;
    return a > b ? a : b;
}

/** Truncate toward zero via integer cast when |x| < 2^53. */
static double xlang_soft_trunc(double x) {
    double y;
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x;
    if (x >= 0x1p53 || x <= -0x1p53)
        return x;
    y = (double)(long long)x;
    return y;
}

/** Floor toward −∞. */
static double xlang_soft_floor(double x) {
    double y;
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x;
    if (x >= 0x1p53 || x <= -0x1p53)
        return x;
    y = (double)(long long)x;
    if (x < 0.0 && y != x)
        y -= 1.0;
    return y;
}

/** Ceil toward +∞. */
static double xlang_soft_ceil(double x) {
    double y;
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x;
    if (x >= 0x1p53 || x <= -0x1p53)
        return x;
    y = (double)(long long)x;
    if (x > 0.0 && y != x)
        y += 1.0;
    return y;
}

/** Round half away from zero (common freestanding; matches smoke ints). */
static double xlang_soft_round(double x) {
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x;
    if (x >= 0.0)
        return xlang_soft_floor(x + 0.5);
    return xlang_soft_ceil(x - 0.5);
}

/** Square root: hardware when available, else Newton. */
static double xlang_soft_sqrt(double x) {
    double r;
    if (xlang_soft_isnan(x) || x == 0.0)
        return x;
    if (x < 0.0) {
        xlang_soft_f64bits n;
        n.u = 0x7ff8000000000000ull; /* qNaN */
        return n.d;
    }
    if (xlang_soft_isinf(x))
        return x;
#if defined(__x86_64__) || defined(_M_X64)
    __asm__ volatile("sqrtsd %1, %0" : "=x"(r) : "x"(x));
    return r;
#elif defined(__aarch64__)
    __asm__ volatile("fsqrt %d0, %d1" : "=w"(r) : "w"(x));
    return r;
#else
    {
        int i;
        r = x;
        if (r < 1.0)
            r = 1.0;
        for (i = 0; i < 16; i++)
            r = 0.5 * (r + x / r);
        return r;
    }
#endif
}

/* ---- transcendentals: range reduction + minimax / Taylor ---- */

#define XLANG_SOFT_PI 3.14159265358979323846
#define XLANG_SOFT_PI_2 1.57079632679489661923
#define XLANG_SOFT_PI_4 0.78539816339744830962
#define XLANG_SOFT_LN2 0.693147180559945309417
#define XLANG_SOFT_LOG2E 1.44269504088896340736
#define XLANG_SOFT_TWO54 0x1.0p54

/** exp(x) via 2^k * exp(r), |r| small; freestanding series. */
static double xlang_soft_exp(double x) {
    double r, z, p;
    int k;
    if (xlang_soft_isnan(x))
        return x;
    if (x > 709.0)
        return 0x1.0p1023 * 0x1.0p1023; /* +Inf overflow */
    if (x < -745.0)
        return 0.0;
    /* k = round(x / ln2) */
    k = (int)(x * XLANG_SOFT_LOG2E + (x >= 0.0 ? 0.5 : -0.5));
    r = x - (double)k * XLANG_SOFT_LN2;
    /* exp(r) ≈ 1 + r + r^2/2! + … + r^8/8! */
    z = r * r;
    p = 1.0 + r +
        z * (0.5 + r * (1.0 / 6.0 + r * (1.0 / 24.0 + r * (1.0 / 120.0 + r * (1.0 / 720.0 + r * (1.0 / 5040.0 + r * (1.0 / 40320.0)))))));
    /* scale by 2^k via exponent field */
    {
        xlang_soft_f64bits b;
        int e;
        b.d = p;
        e = (int)((b.u >> 52) & 0x7ffull);
        e += k;
        if (e <= 0)
            return 0.0;
        if (e >= 0x7ff)
            return 0x1.0p1023 * 0x1.0p1023;
        b.u = (b.u & 0x800fffffffffffffull) | ((uint64_t)e << 52);
        return b.d;
    }
}

/** frexp-like: x = m * 2^e, m in [0.5, 1). */
static double xlang_soft_frexp_mant(double x, int *exp_out) {
    xlang_soft_f64bits b;
    int e;
    b.d = x;
    e = (int)((b.u >> 52) & 0x7ffull);
    if (e == 0) {
        /* subnormal or zero */
        if ((b.u & 0x7fffffffffffffffull) == 0ull) {
            *exp_out = 0;
            return x;
        }
        /* normalize subnormal */
        b.d = x * XLANG_SOFT_TWO54;
        e = (int)((b.u >> 52) & 0x7ffull) - 54;
    } else if (e == 0x7ff) {
        *exp_out = 0;
        return x;
    } else {
        e -= 1022; /* bias so mant in [0.5,1) */
    }
    b.u = (b.u & 0x800fffffffffffffull) | (0x3feull << 52);
    *exp_out = e;
    return b.d;
}

/** log(x) natural log for x > 0. */
static double xlang_soft_log(double x) {
    double m, f, s, z, R;
    int e;
    if (xlang_soft_isnan(x))
        return x;
    if (x < 0.0) {
        xlang_soft_f64bits n;
        n.u = 0x7ff8000000000000ull;
        return n.d;
    }
    if (x == 0.0)
        return -0x1.0p1023 * 0x1.0p1023; /* -Inf */
    if (xlang_soft_isinf(x))
        return x;
    if (x == 1.0)
        return 0.0;
    m = xlang_soft_frexp_mant(x, &e);
    /* Bring mant into [sqrt(1/2), sqrt(2)] ≈ [0.707, 1.414] for better series. */
    if (m < 0.7071067811865476) {
        m *= 2.0;
        e -= 1;
    }
    /* log(m) for m near 1: f=(m-1)/(m+1) atanh series */
    f = (m - 1.0) / (m + 1.0);
    s = f * f;
    z = f + f * s * (1.0 / 3.0 + s * (1.0 / 5.0 + s * (1.0 / 7.0 + s * (1.0 / 9.0 + s * (1.0 / 11.0 + s * (1.0 / 13.0))))));
    R = 2.0 * z;
    return R + (double)e * XLANG_SOFT_LN2;
}

/** log1p(x) = log(1+x) numerically stable for small x. */
static double xlang_soft_log1p(double x) {
    double y, z;
    if (xlang_soft_isnan(x))
        return x;
    if (x == 0.0)
        return x;
    if (x <= -1.0) {
        if (x == -1.0)
            return -0x1.0p1023 * 0x1.0p1023;
        {
            xlang_soft_f64bits n;
            n.u = 0x7ff8000000000000ull;
            return n.d;
        }
    }
    y = 1.0 + x;
    z = y - 1.0;
    if (z == 0.0)
        return x;
    return xlang_soft_log(y) * (x / z);
}

/** expm1(x) = exp(x)-1 numerically stable for small x. */
static double xlang_soft_expm1(double x) {
    double a, e;
    if (xlang_soft_isnan(x))
        return x;
    if (xlang_soft_fabs(x) < 1.0e-8) {
        /* x + x^2/2 + x^3/6 */
        return x + x * x * (0.5 + x / 6.0);
    }
    e = xlang_soft_exp(x);
    if (e == 1.0)
        return x;
    a = e - 1.0;
    if (a == 0.0)
        return a;
    return a * x / xlang_soft_log(e);
}

/** pow(base, exp) via exp(exp*log|base|) with special cases. */
static double xlang_soft_pow(double base, double expn) {
    int neg = 0;
    double r;
    long long n;
    if (base == 0.0) {
        if (expn > 0.0)
            return 0.0;
        if (expn < 0.0)
            return 0x1.0p1023 * 0x1.0p1023;
        return 1.0;
    }
    if (xlang_soft_isnan(base) || xlang_soft_isnan(expn)) {
        xlang_soft_f64bits nb;
        nb.u = 0x7ff8000000000000ull;
        return nb.d;
    }
    if (expn == 0.0)
        return 1.0;
    if (base == 1.0)
        return 1.0;
    /* Small integer exponents: exact multiply ladder (avoids log/exp error on 2^3 etc.). */
    if (expn == xlang_soft_floor(expn) && expn >= -1022.0 && expn <= 1023.0) {
        n = (long long)expn;
        if (n < 0) {
            return 1.0 / xlang_soft_pow(base, (double)(-n));
        }
        r = 1.0;
        {
            double b = base;
            unsigned long long u = (unsigned long long)n;
            while (u) {
                if (u & 1ull)
                    r *= b;
                b *= b;
                u >>= 1;
            }
        }
        return r;
    }
    if (base < 0.0) {
        double ip;
        /* only integer exponents for negative bases in this soft face */
        ip = xlang_soft_floor(expn);
        if (ip != expn) {
            xlang_soft_f64bits nb;
            nb.u = 0x7ff8000000000000ull;
            return nb.d;
        }
        neg = ((long long)ip) & 1;
        base = -base;
    }
    r = xlang_soft_exp(expn * xlang_soft_log(base));
    return neg ? -r : r;
}

/** cbrt via Newton on y^3 - x = 0. */
static double xlang_soft_cbrt(double x) {
    double y;
    int i, sign = 0;
    if (xlang_soft_isnan(x) || x == 0.0 || xlang_soft_isinf(x))
        return x;
    if (x < 0.0) {
        sign = 1;
        x = -x;
    }
    y = xlang_soft_exp(xlang_soft_log(x) / 3.0);
    for (i = 0; i < 4; i++)
        y = (2.0 * y + x / (y * y)) / 3.0;
    return sign ? -y : y;
}

/** Kernel sin on [-pi/4, pi/4]. */
static double xlang_soft_sin_kernel(double x) {
    double z = x * x;
    /* sin = x + x^3*(-1/6 + z*(1/120 + z*(-1/5040 + z/362880))) */
    return x + x * z * (-1.0 / 6.0 + z * (1.0 / 120.0 + z * (-1.0 / 5040.0 + z * (1.0 / 362880.0))));
}

/** Kernel cos on [-pi/4, pi/4]. */
static double xlang_soft_cos_kernel(double x) {
    double z = x * x;
    return 1.0 + z * (-0.5 + z * (1.0 / 24.0 + z * (-1.0 / 720.0 + z * (1.0 / 40320.0))));
}

/** Reduce x to [-pi/4,pi/4] and quadrant; *q = 0..3. */
static double xlang_soft_rem_pio2(double x, int *q) {
    double y;
    long n;
    /* n ≈ x / (pi/2) */
    n = (long)(x * (1.0 / XLANG_SOFT_PI_2) + (x >= 0.0 ? 0.5 : -0.5));
    y = x - (double)n * XLANG_SOFT_PI_2;
    *q = (int)(n & 3);
    return y;
}

static double xlang_soft_sin(double x) {
    int q;
    double y;
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x - x; /* NaN */
    y = xlang_soft_rem_pio2(x, &q);
    switch (q) {
    case 0:
        return xlang_soft_sin_kernel(y);
    case 1:
        return xlang_soft_cos_kernel(y);
    case 2:
        return -xlang_soft_sin_kernel(y);
    default:
        return -xlang_soft_cos_kernel(y);
    }
}

static double xlang_soft_cos(double x) {
    int q;
    double y;
    if (xlang_soft_isnan(x) || xlang_soft_isinf(x))
        return x - x;
    y = xlang_soft_rem_pio2(x, &q);
    switch (q) {
    case 0:
        return xlang_soft_cos_kernel(y);
    case 1:
        return -xlang_soft_sin_kernel(y);
    case 2:
        return -xlang_soft_cos_kernel(y);
    default:
        return xlang_soft_sin_kernel(y);
    }
}

static double xlang_soft_tan(double x) {
    double s = xlang_soft_sin(x);
    double c = xlang_soft_cos(x);
    if (c == 0.0)
        return xlang_soft_copysign(0x1.0p1023 * 0x1.0p1023, s);
    return s / c;
}

/** atan via range reduction + rational approximation. */
static double xlang_soft_atan(double x) {
    double t, z;
    int inv = 0, sign = 0;
    if (xlang_soft_isnan(x))
        return x;
    if (x < 0.0) {
        sign = 1;
        x = -x;
    }
    if (x > 1.0) {
        inv = 1;
        x = 1.0 / x;
    }
    /* atan(x) for |x|<=1: polynomial in z=x^2 */
    z = x * x;
    t = x * (1.0 + z * (-0.3333333333333333 + z * (0.2 + z * (-0.14285714285714285 +
                                                                z * (0.1111111111111111 + z * (-0.09090909090909091 +
                                                                                              z * 0.07692307692307693))))));
    if (inv)
        t = XLANG_SOFT_PI_2 - t;
    return sign ? -t : t;
}

static double xlang_soft_atan2(double y, double x) {
    if (xlang_soft_isnan(x) || xlang_soft_isnan(y)) {
        xlang_soft_f64bits n;
        n.u = 0x7ff8000000000000ull;
        return n.d;
    }
    if (x > 0.0)
        return xlang_soft_atan(y / x);
    if (x < 0.0) {
        if (y >= 0.0)
            return xlang_soft_atan(y / x) + XLANG_SOFT_PI;
        return xlang_soft_atan(y / x) - XLANG_SOFT_PI;
    }
    /* x == 0 */
    if (y > 0.0)
        return XLANG_SOFT_PI_2;
    if (y < 0.0)
        return -XLANG_SOFT_PI_2;
    return 0.0;
}

/** asin via atan(x/sqrt(1-x^2)). */
static double xlang_soft_asin(double x) {
    if (xlang_soft_isnan(x))
        return x;
    if (x < -1.0 || x > 1.0) {
        xlang_soft_f64bits n;
        n.u = 0x7ff8000000000000ull;
        return n.d;
    }
    if (x == 1.0)
        return XLANG_SOFT_PI_2;
    if (x == -1.0)
        return -XLANG_SOFT_PI_2;
    return xlang_soft_atan(x / xlang_soft_sqrt(1.0 - x * x));
}

/** acos via pi/2 - asin. */
static double xlang_soft_acos(double x) {
    return XLANG_SOFT_PI_2 - xlang_soft_asin(x);
}

/** erf via A&S 7.1.26 (max err ~1.5e-7); enough for STD-115 1e-6 gold. */
static double xlang_soft_erf(double x) {
    double ax, t, y;
    const double a1 = 0.254829592;
    const double a2 = -0.284496736;
    const double a3 = 1.421413741;
    const double a4 = -1.453152027;
    const double a5 = 1.061405429;
    const double p = 0.3275911;
    /* 2/sqrt(pi) — linear small-x: erf(x) ≈ c*x */
    const double two_over_sqrt_pi = 1.1283791670955126;
    int sign = 0;
    if (xlang_soft_isnan(x))
        return x;
    if (x == 0.0)
        return x; /* preserve ±0 */
    if (x < 0.0) {
        sign = 1;
        x = -x;
    }
    ax = x;
    if (ax < 1.0e-8)
        return sign ? -two_over_sqrt_pi * ax : two_over_sqrt_pi * ax;
    t = 1.0 / (1.0 + p * ax);
    y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * xlang_soft_exp(-ax * ax);
    return sign ? -y : y;
}

/** erfc(x) = 1 - erf(x); for large |x| use complementary path to limit cancellation. */
static double xlang_soft_erfc(double x) {
    if (x >= 0.0 && x < 0.5)
        return 1.0 - xlang_soft_erf(x);
    if (x >= 0.5) {
        /* erfc(x) for x>=0.5: 1-erf still OK until ~6; beyond → 0 */
        if (x > 20.0)
            return 0.0;
        return 1.0 - xlang_soft_erf(x);
    }
    /* x < 0: erfc(x) = 1 + erf(-x) = 2 - erfc(-x) */
    return 2.0 - xlang_soft_erfc(-x);
}

/* ---- public libm face (forward only; no __builtin_*) ---- */

double fabs(double x) { return xlang_soft_fabs(x); }
double fmin(double a, double b) { return xlang_soft_fmin(a, b); }
double fmax(double a, double b) { return xlang_soft_fmax(a, b); }
double trunc(double x) { return xlang_soft_trunc(x); }
double floor(double x) { return xlang_soft_floor(x); }
double ceil(double x) { return xlang_soft_ceil(x); }
double round(double x) { return xlang_soft_round(x); }
double sqrt(double x) { return xlang_soft_sqrt(x); }
double cbrt(double x) { return xlang_soft_cbrt(x); }
double exp(double x) { return xlang_soft_exp(x); }
double log(double x) { return xlang_soft_log(x); }
double log1p(double x) { return xlang_soft_log1p(x); }
double expm1(double x) { return xlang_soft_expm1(x); }
double pow(double base, double expn) { return xlang_soft_pow(base, expn); }
double sin(double x) { return xlang_soft_sin(x); }
double cos(double x) { return xlang_soft_cos(x); }
double tan(double x) { return xlang_soft_tan(x); }
double asin(double x) { return xlang_soft_asin(x); }
double acos(double x) { return xlang_soft_acos(x); }
double atan(double x) { return xlang_soft_atan(x); }
double atan2(double y, double x) { return xlang_soft_atan2(y, x); }
double erf(double x) { return xlang_soft_erf(x); }
double erfc(double x) { return xlang_soft_erfc(x); }

/* ── fenv 空实现：runtime_math_libm.c 在 Linux 上可链入 ── */

#define FE_INVALID 0x01
#define FE_DIVBYZERO 0x02
#define FE_OVERFLOW 0x04
#define FE_UNDERFLOW 0x08
#define FE_INEXACT 0x10
#define FE_ALL_EXCEPT (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT)

/** 清除浮点异常标志；bootstrap 恒成功。 */
int feclearexcept(int excepts) {
    (void)excepts;
    return 0;
}

/** 测试浮点异常标志；bootstrap 恒无异常。 */
int fetestexcept(int excepts) {
    (void)excepts;
    return 0;
}

/** 触发浮点异常标志；bootstrap 恒成功。 */
int feraiseexcept(int excepts) {
    (void)excepts;
    return 0;
}

/* ── POSIX I/O / 进程：Linux x86_64 经 freestanding_io 或 syscall ── */

#if defined(__linux__) && defined(__x86_64__)

/** Linux x86_64 三参数 syscall 助手。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
long bootstrap_syscall3_impl(long nr, long a0, long a1, long a2) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(nr), "D"(a0), "S"(a1), "d"(a2) : "rcx", "r11", "memory");
    return ret;
}

#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/bootstrap_nostdlib_stubs.x）提供 wrapper 调用 _impl */
long bootstrap_syscall3(long nr, long a0, long a1, long a2) { return bootstrap_syscall3_impl(nr, a0, a1, a2); }
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */




/** Linux x86_64 四参数 syscall 助手（waitpid 等）。 */
/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
long bootstrap_syscall4_impl(long nr, long a0, long a1, long a2, long a3) {
    long ret;
    register long r10 asm("r10") = a3;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(nr), "D"(a0), "S"(a1), "d"(a2), "r"(r10) : "rcx", "r11", "memory");
    return ret;
}

#ifndef XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X
/* G-02f-20 thin+rest：IMPL 模式，thin（src/asm/bootstrap_nostdlib_stubs.x）提供 wrapper 调用 _impl */
long bootstrap_syscall4(long nr, long a0, long a1, long a2, long a3) { return bootstrap_syscall4_impl(nr, a0, a1, a2, a3); }
#endif /* XLANG_BOOTSTRAP_NOSTDLIB_STUBS_FROM_X */




#endif

/** read：转 xlang_sys_read。 */
ssize_t read(int fd, void *buf, size_t count) {
    return (ssize_t)xlang_sys_read(fd, buf, (unsigned long)count);
}

/** close：转 xlang_sys_close。 */
int close(int fd) {
    return (int)xlang_sys_close(fd);
}

/** open：O_CREAT 时取 mode；Linux 走 syscall 2。 */
int open(const char *path, int flags, ...) {
    mode_t mode = 0;
    if (flags & O_CREAT) {
        xlang_va_list ap;
        xlang_va_start(ap, flags);
        mode = (mode_t)xlang_va_arg(ap, int);
        xlang_va_end(ap);
    }
#if defined(__linux__) && defined(__x86_64__)
    return (int)bootstrap_syscall3(2L, (long)path, (long)flags, (long)mode);
#else
    (void)path;
    (void)flags;
    (void)mode;
    return -1;
#endif
}

/** fstat：Linux syscall 5。 */
int fstat(int fd, struct stat *st) {
#if defined(__linux__) && defined(__x86_64__)
    return (int)bootstrap_syscall3(5L, (long)fd, (long)st, 0L);
#else
    (void)fd;
    (void)st;
    return -1;
#endif
}

/**
 * lseek：Linux x86_64 syscall 8 (SYS_lseek).
 * Needed by runtime_io_abi pure Cap residual (file-view size without fstat layout in .x).
 * PLATFORM: LINUX x86_64 nostdlib product link; macOS uses host libc lseek.
 * G.7: single face next to open/read/close/fstat in this stub TU.
 */
off_t lseek(int fd, off_t offset, int whence) {
#if defined(__linux__) && defined(__x86_64__)
    return (off_t)bootstrap_syscall3(8L, (long)fd, (long)offset, (long)whence);
#else
    (void)fd;
    (void)offset;
    (void)whence;
    return (off_t)-1;
#endif
}

/**
 * ftruncate：Linux x86_64 syscall 77 (SYS_ftruncate).
 * Why: PREFER driver_x co-emits std_sys_linux_linux_mmap_rw (#[cfg(not(freestanding))])
 * which calls ftruncate; g05 nostdlib pure-ld drops -lc → U without this face.
 * PLATFORM: LINUX x86_64 nostdlib product link. G.7: same stub TU as open/lseek.
 */
int ftruncate(int fd, off_t length) {
#if defined(__linux__) && defined(__x86_64__)
    return (int)bootstrap_syscall3(77L, (long)fd, (long)length, 0L);
#else
    (void)fd;
    (void)length;
    return -1;
#endif
}

/**
 * msync：Linux x86_64 syscall 26 (SYS_msync).
 * Why: PREFER driver_x co-emits std_sys_linux_linux_msync_sync → msync; same nostdlib
 * pure-ld residual as ftruncate (Ubuntu L4 g05 after PREFER main.x).
 * PLATFORM: LINUX x86_64 nostdlib product link. G.7: same stub TU as mmap/munmap.
 */
int msync(void *addr, size_t length, int flags) {
#if defined(__linux__) && defined(__x86_64__)
    return (int)bootstrap_syscall3(26L, (long)addr, (long)length, (long)flags);
#else
    (void)addr;
    (void)length;
    (void)flags;
    return -1;
#endif
}

/** stat：Linux syscall 4。 */
int stat(const char *path, struct stat *st) {
#if defined(__linux__) && defined(__x86_64__)
    return (int)bootstrap_syscall3(4L, (long)path, (long)st, 0L);
#else
    (void)path;
    (void)st;
    return -1;
#endif
}

/** getpid：Linux syscall 39。 */
pid_t getpid(void) {
#if defined(__linux__) && defined(__x86_64__)
    return (pid_t)bootstrap_syscall3(39L, 0L, 0L, 0L);
#else
    return 1;
#endif
}

/**
 * getppid for freestanding Linux product pure-ld (no -lc).
 *
 * Why: fmt_check_cmd spinner child calls getppid() to exit when the check
 * parent dies (reparent to init → ppid==1). Linux g05 nostdlib drops -lc.
 *
 * Contract: Linux x86_64 SYS_getppid (110); other hosts return 1.
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 */
pid_t getppid(void) {
#if defined(__linux__) && defined(__x86_64__)
    return (pid_t)bootstrap_syscall3(110L, 0L, 0L, 0L);
#else
    return 1;
#endif
}

/**
 * kill for freestanding Linux product pure-ld (no -lc).
 *
 * Why: check_interrupt_handler kills the fork spinner child on SIGINT/SIGTERM.
 * Contract: Linux x86_64 SYS_kill (62); negative kernel errno → -1 + bootstrap_errno.
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 */
int kill(pid_t pid, int sig) {
#if defined(__linux__) && defined(__x86_64__)
    long ret = bootstrap_syscall3(62L, (long)pid, (long)sig, 0L);
    if (ret < 0) {
        bootstrap_errno = (int)(-ret);
        return -1;
    }
    return 0;
#else
    (void)pid;
    (void)sig;
    return -1;
#endif
}

/**
 * sigemptyset for freestanding pure-ld (userspace only).
 *
 * Why: check_install_interrupt_handlers zeros sa_mask before sigaction.
 * Contract: clear all bits in *set; set==NULL → -1.
 * PLATFORM: SHARED symbol; no syscall.
 */
int sigemptyset(sigset_t *set) {
    if (!set)
        return -1;
    memset(set, 0, sizeof(*set));
    return 0;
}

#if defined(__linux__) && defined(__x86_64__)
/* Kernel ABI for SYS_rt_sigaction (13) — not glibc struct sigaction layout.
 * Field names intentionally avoid sa_handler/sa_mask (glibc macros).
 * PLATFORM: LINUX x86_64 nostdlib only. */
struct bootstrap_k_sigaction {
    void (*handler)(int);
    unsigned long flags;
    void (*restorer)(void);
    unsigned long mask;
};

#ifndef SA_RESTORER
#define SA_RESTORER 0x04000000
#endif

/* SA_RESTORER trampoline: SYS_rt_sigreturn (15). Async-signal path only. */
static void bootstrap_rt_sigreturn(void) {
    __asm__ volatile(
        "mov $15, %%rax\n"
        "syscall\n"
        :
        :
        : "rax", "rcx", "r11", "memory");
}
#endif

/**
 * sigaction for freestanding Linux product pure-ld (no -lc).
 *
 * Why: check_install_interrupt_handlers installs SIGINT/SIGTERM handlers so
 * Ctrl+C stops multi-file check cleanly (and kills spinner child).
 *
 * Contract:
 *  - Translates glibc struct sigaction → kernel k_sigaction + SA_RESTORER.
 *  - Linux x86_64 SYS_rt_sigaction (13) with sigsetsize=8.
 *  - Other hosts: -1 (real libc provides when this object is not linked).
 *
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 * Authority: G.7 this freestanding face only — do not open a second signal
 * installer for check; product path uses this + fmt_check_cmd handler.
 */
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
#if defined(__linux__) && defined(__x86_64__)
    struct bootstrap_k_sigaction kact;
    struct bootstrap_k_sigaction kold;
    long ret;
    memset(&kact, 0, sizeof(kact));
    memset(&kold, 0, sizeof(kold));
    if (act) {
        kact.handler = act->sa_handler;
        kact.flags = (unsigned long)act->sa_flags | (unsigned long)SA_RESTORER;
        kact.restorer = bootstrap_rt_sigreturn;
        /* Kernel mask width on x86_64 is 8 bytes (first word of glibc sigset_t). */
        memcpy(&kact.mask, &act->sa_mask, sizeof(kact.mask));
    }
    ret = bootstrap_syscall4(
        13L,
        (long)signum,
        act ? (long)(uintptr_t)&kact : 0L,
        oldact ? (long)(uintptr_t)&kold : 0L,
        8L);
    if (ret < 0) {
        bootstrap_errno = (int)(-ret);
        return -1;
    }
    if (oldact) {
        memset(oldact, 0, sizeof(*oldact));
        oldact->sa_handler = kold.handler;
        oldact->sa_flags = (int)(kold.flags & ~(unsigned long)SA_RESTORER);
        memcpy(&oldact->sa_mask, &kold.mask, sizeof(kold.mask));
    }
    return 0;
#else
    (void)signum;
    (void)act;
    (void)oldact;
    return -1;
#endif
}

/**
 * waitpid for freestanding Linux product pure-ld (no -lc).
 *
 * Contract:
 *  - Linux x86_64 SYS_wait4 (61) with rusage=NULL (POSIX waitpid face).
 *  - Negative kernel errno → -1 + bootstrap_errno (EINTR/ECHILD callers need this).
 *  - Prior raw-negative return broke check spinner reap (treated as success, orphan
 *    child left in shell process group → "check finished but process never exits").
 *
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 */
pid_t waitpid(pid_t pid, int *status, int options) {
#if defined(__linux__) && defined(__x86_64__)
    long ret = bootstrap_syscall4(61L, (long)pid, (long)status, (long)options, 0L);
    if (ret < 0) {
        bootstrap_errno = (int)(-ret);
        return (pid_t)-1;
    }
    return (pid_t)ret;
#else
    (void)pid;
    (void)status;
    (void)options;
    return -1;
#endif
}

/**
 * setsid for freestanding Linux product pure-ld (no -lc).
 *
 * Why: check spinner child must leave the shell foreground process group so a
 * unreaped (or slow-to-die) spinner cannot keep the interactive shell waiting
 * after the parent has printed the summary and returned.
 *
 * Contract: Linux x86_64 SYS_setsid (112); negative errno → -1.
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 */
pid_t setsid(void) {
#if defined(__linux__) && defined(__x86_64__)
    long ret = bootstrap_syscall3(112L, 0L, 0L, 0L);
    if (ret < 0) {
        bootstrap_errno = (int)(-ret);
        return (pid_t)-1;
    }
    return (pid_t)ret;
#else
    return (pid_t)-1;
#endif
}

/** perror：最小实现，输出 msg + errno 到 stderr。 */
void perror(const char *msg) {
    if (msg && msg[0])
        fprintf(stderr, "%s: ", msg);
    fprintf(stderr, "errno=%d\n", bootstrap_errno);
}

/** fopen 最小实现：仅支持 "w"/"r"；返回带 fd 的 FILE 占位。 */
FILE *fopen(const char *path, const char *mode) {
    static FILE bootstrap_file_w = { 1 };
    static FILE bootstrap_file_r = { 0 };
    int flags = 0;
    int fd;
    if (!path || !mode)
        return NULL;
    if (mode[0] == 'w')
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (mode[0] == 'r')
        flags = O_RDONLY;
    else
        return NULL;
    fd = open(path, flags, 0644);
    if (fd < 0)
        return NULL;
    if (mode[0] == 'w') {
        bootstrap_file_w.fd = fd;
        return &bootstrap_file_w;
    }
    bootstrap_file_r.fd = fd;
    return &bootstrap_file_r;
}

/** fclose：close 并返回 0。 */
int fclose(FILE *stream) {
    if (!stream)
        return -1;
    close(stream->fd);
    stream->fd = -1;
    return 0;
}

/** fwrite 最小实现。 */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t total;
    ssize_t n;
    if (!ptr || !stream || size == 0 || nmemb == 0)
        return 0;
    total = size * nmemb;
    n = write(stream->fd, ptr, (unsigned long)total);
    if (n < 0)
        return 0;
    return (size_t)n / size;
}

/** 查找字符首次出现位置。 */
char *strchr(const char *s, int c) {
  if (!s)
    return NULL;
  for (; *s; s++) {
    if ((unsigned char)*s == (unsigned char)c)
      return (char *)s;
  }
  if ((unsigned char)c == '\0')
    return (char *)s;
  return NULL;
}

/** 在内存块中查找字节；string.h 常用。 */
void *memchr(const void *s, int c, size_t n) {
  const unsigned char *p = (const unsigned char *)s;
  size_t i;
  if (!p)
    return NULL;
  for (i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c)
      return (void *)(p + i);
  }
  return NULL;
}

/** 写 C 字符串到流（不含换行）。 */
int fputs(const char *s, FILE *stream) {
  size_t n;
  if (!s || !stream)
    return -1;
  n = strlen(s);
  if (n > 0 && write(stream->fd, s, (unsigned long)n) != (ssize_t)n)
    return -1;
  return 1;
}

/** ASCII 大写化；driver_argv_collect_defines 路径用。 */
int toupper(int c) {
  if (c >= 'a' && c <= 'z')
    return c + ('A' - 'a');
  return c;
}

/** gettimeofday 最小实现；Linux 走 syscall 96。 */
int gettimeofday(struct timeval *tv, void *tz) {
  (void)tz;
  if (!tv)
    return -1;
#if defined(__linux__) && defined(__x86_64__)
  {
    long ret = bootstrap_syscall3(96L, (long)tv, 0L, 0L);
    return (int)ret;
  }
#else
  tv->tv_sec = 0;
  tv->tv_usec = 0;
  return 0;
#endif
}

/**
 * usleep for freestanding Linux product pure-ld (no -lc).
 *
 * Why: wave1227 multi-file check spinner calls usleep; Linux g05 nostdlib
 * drops -lc so the symbol must live in bootstrap_nostdlib_stubs.
 *
 * Contract:
 *  - usec is wall-clock microseconds (POSIX usleep).
 *  - Linux x86_64: SYS_nanosleep (35); retries on EINTR (-4).
 *  - Other hosts in this TU: no-op success (real libc provides usleep when
 *    this stub object is not linked).
 *
 * PLATFORM: LINUX freestanding (x86_64); SHARED symbol name.
 */
int usleep(unsigned int usec) {
#if defined(__linux__) && defined(__x86_64__)
  struct {
    long tv_sec;
    long tv_nsec;
  } req;
  long rem_usec;
  req.tv_sec = (long)(usec / 1000000u);
  rem_usec = (long)(usec % 1000000u);
  req.tv_nsec = rem_usec * 1000L;
  for (;;) {
    long ret = bootstrap_syscall3(35L, (long)&req, 0L, 0L);
    if (ret == 0)
      return 0;
    /* -EINTR */
    if (ret != -4L)
      return -1;
  }
#else
  (void)usec;
  return 0;
#endif
}

/** popen/pclose 最小桩；runtime_link_abi 仅需符号解析。 */
FILE *popen(const char *command, const char *type) {
  (void)command;
  (void)type;
  return NULL;
}

int pclose(FILE *stream) {
  (void)stream;
  return -1;
}

/** pthread 最小桩：bootstrap 单线程，create 同步执行 start_routine。 */
int pthread_attr_init(pthread_attr_t *attr) {
  if (!attr)
    return 22;
  memset(attr, 0, sizeof(*attr));
  return 0;
}

int pthread_attr_destroy(pthread_attr_t *attr) {
  (void)attr;
  return 0;
}

int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize) {
  (void)attr;
  (void)guardsize;
  return 0;
}

int pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize) {
  (void)attr;
  (void)stackaddr;
  (void)stacksize;
  return 0;
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) {
  (void)attr;
  (void)stacksize;
  return 0;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
  (void)attr;
  if (thread)
    *thread = 1;
  if (start_routine)
    (void)start_routine(arg);
  return 0;
}

int pthread_join(pthread_t thread, void **retval) {
  (void)thread;
  if (retval)
    *retval = NULL;
  return 0;
}

/** pthread 互斥/条件变量最小桩：bootstrap 单线程；满足 runtime 链符号，不链 libpthread。 */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
  (void)attr;
  if (!mutex)
    return 22;
  memset(mutex, 0, sizeof(*mutex));
  return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
  (void)mutex;
  return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
  (void)mutex;
  return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
  (void)mutex;
  return 0;
}

pthread_t pthread_self(void) {
  return (pthread_t)1;
}

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr) {
  (void)attr;
  if (!cond)
    return 22;
  memset(cond, 0, sizeof(*cond));
  return 0;
}

int pthread_cond_destroy(pthread_cond_t *cond) {
  (void)cond;
  return 0;
}

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
  (void)cond;
  (void)mutex;
  return 0;
}

int pthread_cond_signal(pthread_cond_t *cond) {
  (void)cond;
  return 0;
}

int pthread_cond_broadcast(pthread_cond_t *cond) {
  (void)cond;
  return 0;
}

int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize, const cpu_set_t *cpuset) {
  (void)thread;
  (void)cpusetsize;
  (void)cpuset;
  return 0;
}

/** 查找字符最后一次出现位置。 */
char *strrchr(const char *s, int c) {
    const char *last = NULL;
    if (!s)
        return NULL;
    for (; *s; s++) {
        if ((unsigned char)*s == (unsigned char)c)
            last = s;
    }
    if ((unsigned char)c == '\0')
        return (char *)s;
    return (char *)last;
}

/** 查找子串首次出现位置；needle 空串时返回 haystack。 */
char *strstr(const char *haystack, const char *needle) {
    size_t nlen;
    size_t i;
    if (!haystack || !needle)
        return NULL;
    if (!needle[0])
        return (char *)haystack;
    nlen = strlen(needle);
    for (i = 0; haystack[i]; i++) {
        if (strncmp(haystack + i, needle, nlen) == 0)
            return (char *)(haystack + i);
    }
    return NULL;
}

/** 小写化 ASCII 字母；bootstrap target_cpu 路径用。 */
int tolower(int c) {
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

#if defined(__linux__) && defined(__x86_64__)

/** readlink：Linux syscall 89。 */
ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
    long ret = bootstrap_syscall3(89L, (long)path, (long)buf, (long)bufsiz);
    if (ret < 0)
        return -1;
    return (ssize_t)ret;
}

/** getcwd：优先 /proc/self/cwd readlink。 */
char *getcwd(char *buf, size_t size) {
    ssize_t n;
    if (!buf || size == 0) {
        bootstrap_errno = 22; /* EINVAL */
        return NULL;
    }
    n = readlink("/proc/self/cwd", buf, size - 1);
    if (n < 0)
        return NULL;
    buf[n] = '\0';
    return buf;
}

/** 拼接 base + rel 到 out（out 容量 cap）；成功返回 out。 */
static char *bootstrap_path_join(char *out, size_t cap, const char *base, const char *rel) {
    size_t blen;
    size_t rlen;
    if (!out || cap == 0 || !base || !rel)
        return NULL;
    blen = strlen(base);
    rlen = strlen(rel);
    if (blen + 1 + rlen + 1 > cap)
        return NULL;
    memcpy(out, base, blen);
    if (blen > 0 && base[blen - 1] != '/') {
        out[blen] = '/';
        blen++;
    }
    memcpy(out + blen, rel, rlen + 1);
    return out;
}

/** realpath 最小实现：绝对路径拷贝；相对路径基于 getcwd 拼接（无 .. 规范化）。 */
char *realpath(const char *path, char *resolved) {
    static char bootstrap_realpath_pool[4096];
    char *out = resolved ? resolved : bootstrap_realpath_pool;
    size_t cap = resolved ? 4096u : sizeof(bootstrap_realpath_pool);
    char cwd[2048];
    if (!path)
        return NULL;
    if (path[0] == '/') {
        if (strlen(path) + 1 > cap)
            return NULL;
        strcpy(out, path);
        return out;
    }
    if (!getcwd(cwd, sizeof(cwd)))
        return NULL;
    return bootstrap_path_join(out, cap, cwd, path);
}

/** Linux getdents64 目录项（bootstrap opendir 用）。 */
struct bootstrap_linux_dirent64 {
    uint64_t d_ino;
    int64_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};

/** bootstrap opendir 状态。 */
struct bootstrap_dir {
    int fd;
    unsigned char *buf;
    size_t buf_cap;
    size_t buf_len;
    size_t buf_pos;
    struct dirent ent;
};

/** opendir：open + getdents64 缓冲。 */
DIR *opendir(const char *name) {
    struct bootstrap_dir *d;
    if (!name)
        return NULL;
    d = (struct bootstrap_dir *)calloc(1, sizeof(*d));
    if (!d)
        return NULL;
    d->fd = open(name, O_RDONLY | 0200000 /* O_DIRECTORY */, 0);
    if (d->fd < 0) {
        free(d);
        return NULL;
    }
    d->buf_cap = 8192;
    d->buf = (unsigned char *)malloc(d->buf_cap);
    if (!d->buf) {
        close(d->fd);
        free(d);
        return NULL;
    }
    return (DIR *)d;
}

/** readdir：从 getdents64 缓冲取下一条；失败或结束返回 NULL。 */
struct dirent *readdir(DIR *dirp) {
    struct bootstrap_dir *d = (struct bootstrap_dir *)dirp;
    struct bootstrap_linux_dirent64 *de;
    if (!d || d->fd < 0)
        return NULL;
    for (;;) {
        if (d->buf_pos >= d->buf_len) {
            long nr = bootstrap_syscall3(217L, (long)d->fd, (long)d->buf, (long)d->buf_cap);
            if (nr <= 0)
                return NULL;
            d->buf_len = (size_t)nr;
            d->buf_pos = 0;
        }
        if (d->buf_pos >= d->buf_len)
            return NULL;
        de = (struct bootstrap_linux_dirent64 *)(d->buf + d->buf_pos);
        d->buf_pos += de->d_reclen;
        if (de->d_name[0] == '\0')
            continue;
        /* wave1241: 填充 glibc 标准 struct dirent 全字段，使 d_name 偏移与
         * xlang_fmt_readdir_name（prelude #include <dirent.h>）一致。 */
        d->ent.d_ino = de->d_ino;
        d->ent.d_off = de->d_off;
        d->ent.d_reclen = de->d_reclen;
        d->ent.d_type = de->d_type;
        strncpy(d->ent.d_name, de->d_name, sizeof(d->ent.d_name) - 1);
        d->ent.d_name[sizeof(d->ent.d_name) - 1] = '\0';
        return &d->ent;
    }
}

/** closedir：释放 bootstrap_dir。 */
int closedir(DIR *dirp) {
    struct bootstrap_dir *d = (struct bootstrap_dir *)dirp;
    if (!d)
        return -1;
    if (d->fd >= 0)
        close(d->fd);
    free(d->buf);
    free(d);
    return 0;
}

#else

/** 非 Linux x86_64：路径 API 桩返回失败。 */
ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
    (void)path;
    (void)buf;
    (void)bufsiz;
    return -1;
}

char *getcwd(char *buf, size_t size) {
    (void)buf;
    (void)size;
    return NULL;
}

char *realpath(const char *path, char *resolved) {
    (void)path;
    (void)resolved;
    return NULL;
}

DIR *opendir(const char *name) {
    (void)name;
    return NULL;
}

struct dirent *readdir(DIR *dirp) {
    (void)dirp;
    return NULL;
}

int closedir(DIR *dirp) {
    (void)dirp;
    return -1;
}

#endif

/** fgets：从 FILE 读一行（含换行或 EOF）。 */
char *fgets(char *s, int size, FILE *stream) {
  int i;
  if (!s || size <= 0 || !stream)
    return NULL;
  for (i = 0; i < size - 1; i++) {
    unsigned char c;
    ssize_t n = read(stream->fd, &c, 1);
    if (n <= 0) {
      if (i == 0)
        return NULL;
      break;
    }
    s[i] = (char)c;
    if (c == '\n') {
      i++;
      break;
    }
  }
  s[i] = '\0';
  return s;
}

/** glibc FORTIFY：nostdlib 链 backend_call_dispatch / parser_asm 需要。 */
void *__memcpy_chk(void *dest, const void *src, size_t len, size_t destlen) {
  if (len > destlen)
    __stack_chk_fail();
  return memcpy(dest, src, len);
}

/**
 * Flush a stdio stream (POSIX fflush).
 *
 * PLATFORM: LINUX — this TU is linked **only** on XLANG_BOOTSTRAP_NOSTDLIB crt0
 * (build_xlang_asm bootstrap_link_tail_crt0 / driver). g05 dynamic product does
 * **not** link bootstrap_nostdlib_stubs.o, so glibc keeps fflush (historical
 * 24KiB -E truncate when a strong no-op covered glibc + unflushed fwrite).
 *
 * Authority (G.7 / NL-07 L2): single nostdlib FILE* stdio surface lives in this
 * seed — do **not** add a second fflush in freestanding_io_x86_64.s.
 *
 * Semantics: stub FILE* I/O is unbuffered write(fd) (see fwrite/fputs); there is
 * no user-space buffer to drain. Always return 0. fflush(NULL) is a no-op success
 * (no open buffered streams to walk).
 */
int fflush(FILE *stream) {
  (void)stream;
  return 0;
}

/**
 * Return the underlying fd of a stub FILE* (POSIX fileno).
 *
 * PLATFORM: LINUX — nostdlib-only (same link gate as fflush).
 * Authority (G.7 / NL-07 L6): this seed only; do not add fileno in freestanding_io.
 */
int fileno(FILE *stream) {
  if (!stream)
    return -1;
  return stream->fd;
}

/**
 * Report sticky error on stream (POSIX ferror).
 *
 * Stub FILE* has no error flag field; unbuffered read/write failures are reported
 * by return values only. Always 0 so seed paths like `fread==0 && ferror(stdin)`
 * treat EOF cleanly without a false hard error.
 *
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed.
 */
int ferror(FILE *stream) {
  (void)stream;
  return 0;
}

/**
 * Read size*nmemb bytes from stream into ptr (POSIX fread).
 *
 * Mirrors fwrite: single read() on stream->fd; returns complete elements only.
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed.
 */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t total;
  ssize_t n;
  if (!ptr || !stream || size == 0 || nmemb == 0)
    return 0;
  total = size * nmemb;
  n = read(stream->fd, ptr, (unsigned long)total);
  if (n <= 0)
    return 0;
  return (size_t)n / size;
}

/**
 * Write s plus a trailing newline to stdout (POSIX puts).
 *
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed.
 */
int puts(const char *s) {
  size_t n;
  char nl = '\n';
  if (!s)
    return -1;
  n = strlen(s);
  if (n > 0 && write(1, s, (unsigned long)n) != (long)n)
    return -1;
  if (write(1, &nl, 1) != 1)
    return -1;
  return 0;
}

/**
 * Test whether fd refers to a terminal (POSIX isatty).
 *
 * Bootstrap returns 0 always: nostdlib has no termios; diag color paths stay off.
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed.
 */
int isatty(int fd) {
  (void)fd;
  return 0;
}

/**
 * Map errno to a short static message (POSIX strerror).
 *
 * Not a full locale table — enough for rt_diag / link_abi error strings.
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed.
 */
char *strerror(int errnum) {
  static char buf[48];
  (void)snprintf(buf, sizeof(buf), "errno %d", errnum);
  return buf;
}

/**
 * glibc ctype class table locator for objects compiled against hosted headers.
 *
 * Seeds / gen C expand isalpha/isdigit via (*__ctype_b_loc())[c] with glibc
 * little-endian _ISbit layout. Provide a 384-entry ASCII table (index = c+128)
 * so -nostdlib links without libpthread/libc ctype.
 *
 * PLATFORM: LINUX — nostdlib-only. Authority: G.7 / NL-07 L6 this seed only
 * (do not duplicate in freestanding_io).
 */
#define BOOTSTRAP_ISBIT(bit) \
  ((unsigned short)(((bit) < 8) ? ((1u << (bit)) << 8) : ((1u << (bit)) >> 8)))
enum {
  B_ISupper = BOOTSTRAP_ISBIT(0),
  B_ISlower = BOOTSTRAP_ISBIT(1),
  B_ISalpha = BOOTSTRAP_ISBIT(2),
  B_ISdigit = BOOTSTRAP_ISBIT(3),
  B_ISxdigit = BOOTSTRAP_ISBIT(4),
  B_ISspace = BOOTSTRAP_ISBIT(5),
  B_ISprint = BOOTSTRAP_ISBIT(6),
  B_ISgraph = BOOTSTRAP_ISBIT(7),
  B_ISblank = BOOTSTRAP_ISBIT(8),
  B_IScntrl = BOOTSTRAP_ISBIT(9),
  B_ISpunct = BOOTSTRAP_ISBIT(10),
  B_ISalnum = BOOTSTRAP_ISBIT(11)
};

static unsigned short bootstrap_ctype_b_array[384];
static const unsigned short *bootstrap_ctype_b_ptr;
static int bootstrap_ctype_inited;

static void bootstrap_ctype_init(void) {
  int c;
  if (bootstrap_ctype_inited)
    return;
  for (c = 0; c < 256; c++) {
    unsigned short bits = 0;
    unsigned char u = (unsigned char)c;
    if (u < 32u || u == 127u)
      bits |= (unsigned short)B_IScntrl;
    if (u == ' ' || u == '\t')
      bits |= (unsigned short)(B_ISblank | B_ISspace);
    if (u == '\n' || u == '\r' || u == '\f' || u == '\v')
      bits |= (unsigned short)B_ISspace;
    if (u >= 0x21u && u <= 0x7eu)
      bits |= (unsigned short)(B_ISprint | B_ISgraph);
    if (u == ' ')
      bits |= (unsigned short)B_ISprint;
    if (u >= '0' && u <= '9')
      bits |= (unsigned short)(B_ISdigit | B_ISxdigit | B_ISalnum);
    if ((u >= 'A' && u <= 'F') || (u >= 'a' && u <= 'f'))
      bits |= (unsigned short)B_ISxdigit;
    if (u >= 'A' && u <= 'Z')
      bits |= (unsigned short)(B_ISupper | B_ISalpha | B_ISalnum);
    if (u >= 'a' && u <= 'z')
      bits |= (unsigned short)(B_ISlower | B_ISalpha | B_ISalnum);
    if ((bits & (unsigned short)B_ISgraph) &&
        !(bits & (unsigned short)(B_ISalnum | B_ISspace)))
      bits |= (unsigned short)B_ISpunct;
    bootstrap_ctype_b_array[c + 128] = bits;
  }
  /* EOF (-1) lands at index 127; leave 0. */
  bootstrap_ctype_b_ptr = &bootstrap_ctype_b_array[128];
  bootstrap_ctype_inited = 1;
}

const unsigned short **__ctype_b_loc(void) {
  bootstrap_ctype_init();
  return (const unsigned short **)&bootstrap_ctype_b_ptr;
}

/**
 * crt0 exit path after main_entry: flush stdio when safe, then sys_exit (never returns).
 *
 * PLATFORM: LINUX (freestanding + hosted hybrid) —
 * - Hosted/dynamic (g05 product): stubs not linked; crt0 weak ref is 0 → fflush@PLT
 *   on real glibc streams (keeps -E buffer tail).
 * - Freestanding / nostdlib crt0: this symbol is strong; call fflush (this TU) then
 *   xlang_sys_exit. Stub FILE* path is no-op success (unbuffered write).
 *
 * Authority: only this helper from crt0_x86_64.s for freestanding exit — do not
 * call fflush@PLT on raw stdout from asm (G.7 single exit-flush path).
 */
void bootstrap_flush_stdio_and_exit(int code) {
  /* fflush is defined in this TU for nostdlib; identity skip no longer required
   * for SIGSEGV safety, but still avoid work when pointers are null. */
  if (stdout)
    (void)fflush(stdout);
  if (stderr)
    (void)fflush(stderr);
  xlang_sys_exit(code);
}

/** 写单字符到流。 */
int fputc(int c, FILE *stream) {
  unsigned char ch = (unsigned char)c;
  if (!stream)
    return -1;
  if (write(stream->fd, &ch, 1) != 1)
    return -1;
  return (unsigned char)c;
}

/** 设置流缓冲；bootstrap no-op。 */
int setvbuf(FILE *stream, char *buf, int mode, size_t size) {
  (void)stream;
  (void)buf;
  (void)mode;
  (void)size;
  return 0;
}

/** 设置环境变量；bootstrap 无真实 environ，恒成功 no-op。 */
int setenv(const char *name, const char *value, int overwrite) {
  (void)name;
  (void)value;
  (void)overwrite;
  return 0;
}

/** 进程立即退出；不跑 atexit（Linux syscall 60）。 */
void _exit(int status) {
#if defined(__linux__) && defined(__x86_64__)
  bootstrap_syscall3(60L, (long)status, 0L, 0L);
  for (;;)
    ;
#else
  xlang_sys_exit(status);
#endif
}

#if defined(__linux__) && defined(__x86_64__)

/** fork：Linux syscall 57。 */
pid_t fork(void) {
  return (pid_t)bootstrap_syscall3(57L, 0L, 0L, 0L);
}

/* access is defined later in this #if block; needed for PATH search. */
int access(const char *path, int mode);

/**
 * execve-like helper: Linux syscall 59 with bootstrap environ.
 * PLATFORM: LINUX — nostdlib only (this #if block).
 * Must pass environ (not NULL): host gcc/collect2 need PATH and friends.
 */
static int bootstrap_execve(const char *path, char *const argv[]) {
  long ret = bootstrap_syscall3(59L, (long)path, (long)argv, (long)(uintptr_t)environ);
  if (ret < 0) {
    bootstrap_errno = (int)(-ret);
    return -1;
  }
  return (int)ret;
}

/**
 * POSIX execvp: search PATH when `file` has no '/'; otherwise exec absolute/relative path.
 *
 * Root cause (NL-07 L10 L4 expose): prior stub was bare execve(file) without PATH search.
 * After L4 wipe, ensure → xlang_cc_compile_sync_ex → execvp("cc") → ENOENT, BLD001 on
 * runtime_asm_io_stubs.o. L2/L3 with residual .o hid this (ensure skipped).
 *
 * Authority: G.7 this freestanding execvp only — do not fork second search in link_abi.
 * Fallback PATH when environ has no PATH (setenv is no-op here): /usr/local/bin:/usr/bin:/bin.
 * PLATFORM: LINUX x86_64 nostdlib.
 */
int execvp(const char *file, char *const argv[]) {
  const char *path_env;
  const char *p;
  char cand[4096];
  size_t flen;
  if (!file || !file[0]) {
    bootstrap_errno = 2; /* ENOENT */
    return -1;
  }
  /* Absolute or relative with slash: no PATH search (POSIX). */
  if (strchr(file, '/') != NULL)
    return bootstrap_execve(file, argv);

  flen = strlen(file);
  path_env = getenv("PATH");
  if (!path_env || !path_env[0])
    path_env = "/usr/local/bin:/usr/bin:/bin";

  p = path_env;
  for (;;) {
    const char *colon = strchr(p, ':');
    size_t dlen = colon ? (size_t)(colon - p) : strlen(p);
    /* Empty component means current directory (POSIX). */
    if (dlen == 0) {
      if (flen + 1 >= sizeof(cand)) {
        bootstrap_errno = 36; /* ENAMETOOLONG */
        return -1;
      }
      memcpy(cand, file, flen + 1);
    } else {
      if (dlen + 1 + flen + 1 >= sizeof(cand)) {
        /* Skip oversized component; try next. */
        if (!colon)
          break;
        p = colon + 1;
        continue;
      }
      memcpy(cand, p, dlen);
      cand[dlen] = '/';
      memcpy(cand + dlen + 1, file, flen + 1);
    }
    if (access(cand, X_OK) == 0) {
      (void)bootstrap_execve(cand, argv);
      /* exec failed: try next path component (e.g. not a real ELF). */
    }
    if (!colon)
      break;
    p = colon + 1;
  }
  bootstrap_errno = 2; /* ENOENT */
  return -1;
}

/** execv：absolute/relative path only; pass environ (gcc needs PATH even with abs path). */
int execv(const char *path, char *const argv[]) {
  if (!path)
    return -1;
  return bootstrap_execve(path, argv);
}

/** execlp：可变参数转 argv 后 execvp（签名与 unistd.h 一致）。 */
int execlp(const char *file, const char *arg, ...) {
  xlang_va_list ap;
  char *argv[256];
  int i = 0;
  argv[i++] = (char *)file;
  argv[i++] = (char *)arg;
  xlang_va_start(ap, arg);
  while (i < 255) {
    char *a = xlang_va_arg(ap, char *);
    argv[i++] = a;
    if (!a)
      break;
  }
  xlang_va_end(ap);
  return execvp(file, argv);
}

/** uname：Linux syscall 63。 */
int uname(struct utsname *buf) {
  if (!buf)
    return -1;
  memset(buf, 0, sizeof(*buf));
  strncpy(buf->sysname, "Linux", sizeof(buf->sysname) - 1);
  strncpy(buf->machine, "x86_64", sizeof(buf->machine) - 1);
  return 0;
}

/** getrlimit / setrlimit：Linux syscall 97 / 160。 */
int getrlimit(int resource, struct rlimit *rlim) {
  return (int)bootstrap_syscall3(97L, (long)resource, (long)rlim, 0L);
}

int setrlimit(int resource, const struct rlimit *rlim) {
  return (int)bootstrap_syscall3(160L, (long)resource, (long)rlim, 0L);
}

/** system 最小实现：fork + execvp + waitpid；失败返回 -1。 */
int system(const char *command) {
  pid_t pid;
  int status = 0;
  if (!command)
    return 1;
  pid = fork();
  if (pid < 0)
    return -1;
  if (pid == 0) {
    char *argv[] = { "/bin/sh", "-c", (char *)command, NULL };
    execvp("/bin/sh", argv);
    _exit(127);
  }
  if (waitpid(pid, &status, 0) < 0)
    return -1;
  if (WIFEXITED(status))
    return WEXITSTATUS(status);
  return -1;
}

/** unlink：Linux syscall 87。 */
int unlink(const char *path) {
  return (int)bootstrap_syscall3(87L, (long)path, 0L, 0L);
}

/**
 * Remove a file (POSIX remove → unlink for regular paths).
 *
 * PLATFORM: LINUX — nostdlib-only; wraps this TU's unlink (G.7 single path).
 * Authority: G.7 / NL-07 L6 this seed.
 */
int remove(const char *path) {
  return unlink(path);
}

/** rename：Linux syscall 82。 */
int rename(const char *oldpath, const char *newpath) {
  return (int)bootstrap_syscall3(82L, (long)oldpath, (long)newpath, 0L);
}

/** access：Linux syscall 21（mode 仅 F_OK 常用）。 */
int access(const char *path, int mode) {
  return (int)bootstrap_syscall3(21L, (long)path, (long)mode, 0L);
}

/** fdopen：将已打开 fd 包装为 FILE 占位。 */
FILE *fdopen(int fd, const char *mode) {
  static FILE bootstrap_fd_file = { -1 };
  (void)mode;
  if (fd < 0)
    return NULL;
  bootstrap_fd_file.fd = fd;
  return &bootstrap_fd_file;
}

/** mkstemp：/tmp/xlangXXXXXX 最小实现（pid+序号避免跨进程 O_EXCL 冲突）。 */
int mkstemp(char *template) {
  static int bootstrap_mkstemp_seq;
  char *p;
  int fd;
  int attempt;
  if (!template)
    return -1;
  p = strstr(template, "XXXXXX");
  if (!p)
    return -1;
  for (attempt = 0; attempt < 32; attempt++) {
    bootstrap_mkstemp_seq++;
    snprintf(p, 7, "%06d", (int)((getpid() * 997u + (unsigned)bootstrap_mkstemp_seq + (unsigned)attempt) % 1000000u));
    fd = open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd >= 0)
      return fd;
  }
  return -1;
}

#else

/** 非 Linux x86_64：进程 API 桩。 */
pid_t fork(void) {
  return -1;
}

int execvp(const char *file, char *const argv[]) {
  (void)file;
  (void)argv;
  return -1;
}

int system(const char *command) {
  (void)command;
  return -1;
}

#endif
