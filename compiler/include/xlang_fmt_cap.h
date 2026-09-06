/*
 * xlang_fmt_cap.h — Cap residual 10.7.2 slice0: freestanding vsnprintf without libc.
 *
 * G.7: single authority for Cap format faces. Lifted from
 * bootstrap_nostdlib_stubs.from_x.c vsnprintf / bootstrap_format_double_impl;
 * nostdlib stubs become thin wrappers over this header.
 *
 * Uses xlang_va_cap.h (10.7.1) — no <stdarg.h>. No <string.h> (local strlen).
 *
 * Specs: %% %c %s %d %u %ld %lu %x %p %f/%F/%g/%G/%e/%E plus width / .* precision.
 *
 * PLATFORM: SHARED (GCC/Clang builtins via Cap va).
 */

#ifndef XLANG_FMT_CAP_H
#define XLANG_FMT_CAP_H

#include <stddef.h>
#include <stdint.h>

#include <xlang_va_cap.h>

/**
 * Cap strlen (no libc).
 * @return byte count before NUL; 0 if s is NULL
 * PLATFORM: SHARED
 */
static inline size_t xlang_fmt_strlen(const char *s) {
  size_t n = 0;
  if (s == 0) {
    return 0;
  }
  while (s[n] != 0) {
    n++;
  }
  return n;
}

/**
 * Cap fixed decimal for float specs (nostdlib-grade; not glibc %.17g).
 * @param x value
 * @param out destination
 * @param cap capacity
 * @return bytes written (not including NUL); may equal cap without NUL
 * PLATFORM: SHARED
 */
static inline int xlang_format_double(double x, char *out, size_t cap) {
  size_t n = 0;
  long ipart;
  unsigned frac6;
  int scale;
  if (cap == 0 || out == 0) {
    return 0;
  }
  if (x < 0.0) {
    if (n < cap) {
      out[n++] = '-';
    }
    x = -x;
  }
  ipart = (long)x;
  frac6 = (unsigned)((x - (double)ipart) * 1000000.0 + 0.5);
  if (frac6 >= 1000000u) {
    ipart++;
    frac6 = 0;
  }
  if (ipart == 0) {
    if (n < cap) {
      out[n++] = '0';
    }
  } else {
    char ib[32];
    int in = 0;
    long v = ipart;
    while (v > 0) {
      ib[in++] = (char)('0' + (v % 10));
      v /= 10;
    }
    while (in > 0 && n < cap) {
      out[n++] = ib[--in];
    }
  }
  if (n < cap) {
    out[n++] = '.';
  }
  for (scale = 100000; scale >= 1; scale /= 10) {
    if (n < cap) {
      out[n++] = (char)('0' + ((frac6 / (unsigned)scale) % 10u));
    }
  }
  return (int)n;
}

/**
 * Cap vsnprintf — freestanding format into buf.
 * @return would-be length (may be >= size); NUL-terminates when size > 0
 * PLATFORM: SHARED
 */
static inline int xlang_vsnprintf(char *buf, size_t size, const char *fmt,
                                  xlang_va_list ap) {
  size_t pos = 0;
  if (buf == 0 || size == 0) {
    return fmt ? (int)xlang_fmt_strlen(fmt) : 0;
  }
  if (fmt == 0) {
    buf[0] = '\0';
    return 0;
  }
  while (*fmt) {
    if (*fmt != '%') {
      if (pos + 1 < size) {
        buf[pos] = *fmt;
      }
      pos++;
      fmt++;
      continue;
    }
    fmt++;
    if (*fmt == '%') {
      if (pos + 1 < size) {
        buf[pos] = '%';
      }
      pos++;
      fmt++;
      continue;
    }
    {
      char tmp[64];
      int tn = 0;
      int width = 0;
      int pad_zero = 0;
      int prec = -1;
      int longmod = 0;
      if (*fmt == '0') {
        pad_zero = 1;
        fmt++;
      }
      if (*fmt == '*') {
        width = xlang_va_arg(ap, int);
        fmt++;
      } else {
        while (*fmt >= '0' && *fmt <= '9') {
          width = width * 10 + (*fmt - '0');
          fmt++;
        }
      }
      if (*fmt == '.') {
        fmt++;
        if (*fmt == '*') {
          prec = xlang_va_arg(ap, int);
          fmt++;
        } else {
          prec = 0;
          while (*fmt >= '0' && *fmt <= '9') {
            prec = prec * 10 + (*fmt - '0');
            fmt++;
          }
        }
      }
      if (*fmt == 'l') {
        longmod = 1;
        fmt++;
      }
      (void)width;
      switch (*fmt) {
      case 'c': {
        char c = (char)xlang_va_arg(ap, int);
        tmp[tn++] = c;
        break;
      }
      case 's': {
        const char *s = xlang_va_arg(ap, const char *);
        int si = 0;
        if (s == 0) {
          s = "(null)";
        }
        while (s[si] && (prec < 0 || si < prec)) {
          if (pos + 1 < size) {
            buf[pos] = s[si];
          }
          pos++;
          si++;
        }
        fmt++;
        continue;
      }
      case 'd': {
        long v = longmod ? xlang_va_arg(ap, long) : xlang_va_arg(ap, int);
        char ib[32];
        int in = 0;
        int neg = 0;
        if (v < 0) {
          neg = 1;
          v = -v;
        }
        if (v == 0) {
          ib[in++] = '0';
        }
        while (v > 0) {
          ib[in++] = (char)('0' + (v % 10));
          v /= 10;
        }
        if (pad_zero) {
          int target = neg ? (width - 1) : width;
          while (in < target && in < (int)sizeof(ib) - 1) {
            ib[in++] = '0';
          }
        }
        if (neg && in < (int)sizeof(ib)) {
          ib[in++] = '-';
        }
        while (in > 0 && tn < (int)sizeof(tmp) - 1) {
          tmp[tn++] = ib[--in];
        }
        break;
      }
      case 'u': {
        unsigned long v =
            longmod ? xlang_va_arg(ap, unsigned long) : xlang_va_arg(ap, unsigned int);
        char ib[32];
        int in = 0;
        if (v == 0) {
          ib[in++] = '0';
        }
        while (v > 0) {
          ib[in++] = (char)('0' + (v % 10));
          v /= 10;
        }
        if (pad_zero) {
          while (in < width && in < (int)sizeof(ib) - 1) {
            ib[in++] = '0';
          }
        }
        while (in > 0 && tn < (int)sizeof(tmp) - 1) {
          tmp[tn++] = ib[--in];
        }
        break;
      }
      case 'x': {
        unsigned long v =
            longmod ? xlang_va_arg(ap, unsigned long) : xlang_va_arg(ap, unsigned int);
        char ib[32];
        int in = 0;
        if (v == 0) {
          ib[in++] = '0';
        }
        while (v > 0) {
          ib[in++] = "0123456789abcdef"[v & 15];
          v >>= 4;
        }
        while (in > 0 && tn < (int)sizeof(tmp) - 1) {
          tmp[tn++] = ib[--in];
        }
        break;
      }
      case 'p': {
        void *p = xlang_va_arg(ap, void *);
        tmp[tn++] = '0';
        tmp[tn++] = 'x';
        {
          uintptr_t v = (uintptr_t)p;
          char ib[2 * sizeof(uintptr_t) + 1];
          int in = 0;
          if (v == 0) {
            ib[in++] = '0';
          }
          while (v > 0) {
            ib[in++] = "0123456789abcdef"[v & 15];
            v >>= 4;
          }
          while (in > 0 && tn < (int)sizeof(tmp) - 1) {
            tmp[tn++] = ib[--in];
          }
        }
        break;
      }
      case 'f':
      case 'F':
      case 'g':
      case 'G':
      case 'e':
      case 'E': {
        double dv = xlang_va_arg(ap, double);
        char fb[32];
        int fn = xlang_format_double(dv, fb, sizeof(fb));
        int fi = 0;
        if (fn < 0) {
          fn = 0;
        }
        while (fi < fn && tn < (int)sizeof(tmp) - 1) {
          tmp[tn++] = fb[fi++];
        }
        break;
      }
      default:
        tmp[tn++] = *fmt;
        break;
      }
      fmt++;
      {
        int ti;
        for (ti = 0; ti < tn; ti++) {
          if (pos + 1 < size) {
            buf[pos] = tmp[ti];
          }
          pos++;
        }
      }
    }
  }
  if (size > 0) {
    buf[pos < size ? pos : size - 1] = '\0';
  }
  return (int)pos;
}

/**
 * Cap snprintf — Cap va_start + xlang_vsnprintf.
 * PLATFORM: SHARED
 */
static inline int xlang_snprintf(char *buf, size_t size, const char *fmt, ...) {
  xlang_va_list ap;
  int n;
  xlang_va_start(ap, fmt);
  n = xlang_vsnprintf(buf, size, fmt, ap);
  xlang_va_end(ap);
  return n;
}

#endif /* XLANG_FMT_CAP_H */
