/* PLATFORM: SHARED — pure-asm formal vehicle for std/compress (class-batch 2).
 *
 * Why C face: .x monofile co-emits bare deflate/inflate that conflict with zlib
 * C API types in the same TU. Product body stays in submodule formal .o
 * (std/compress/gzip/gzip.o, zlib/zlib.o). This vehicle exports the facade
 * std_compress_* names the user import mangles to.
 *
 * G.7: complete existing c_face — gzip/zstd/brotli one-shot AND stream faces
 * trampoline to the submodule mangle
 * (std_compress_{gzip_gzip,zstd_zstd,brotli_brotli}_*), not return -1.
 * Returning -1 made `xlang build` skip-green (tests/compress/main.x treats
 * n<=0 as skip; cookbook compress_stream_br_zs treats init!=0 as success 0)
 * while submodule .o was never on the ld argv.
 *
 * G.7: single formal vehicle for pure-asm product link (catalog key
 * std/compress/compress.o). formal_mod kind=c_face.
 */
#include <stdint.h>

/* PLATFORM: SHARED — product gzip lives in gzip.o (mod.x + libz.x). */
extern int32_t std_compress_gzip_gzip_compress(uint8_t *in, int32_t in_len, uint8_t *out,
                                               int32_t out_cap);
extern int32_t std_compress_gzip_gzip_decompress(uint8_t *in, int32_t in_len, uint8_t *out,
                                                 int32_t out_cap);

int32_t std_compress_gzip_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_gzip_gzip_compress(in, in_len, out, out_cap);
}

int32_t std_compress_gzip_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_gzip_gzip_decompress(in, in_len, out, out_cap);
}

/* PLATFORM: SHARED — product brotli lives in brotli.o (mod.x + lib.x). */
extern int32_t std_compress_brotli_brotli_compress(uint8_t *in, int32_t in_len, uint8_t *out,
                                                   int32_t out_cap);
extern int32_t std_compress_brotli_brotli_decompress(uint8_t *in, int32_t in_len, uint8_t *out,
                                                     int32_t out_cap);

int32_t std_compress_brotli_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_brotli_brotli_compress(in, in_len, out, out_cap);
}

int32_t std_compress_brotli_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_brotli_brotli_decompress(in, in_len, out, out_cap);
}

/* PLATFORM: SHARED — product zstd lives in zstd.o (mod.x + lib.x). */
extern int32_t std_compress_zstd_zstd_compress(uint8_t *in, int32_t in_len, uint8_t *out,
                                               int32_t out_cap);
extern int32_t std_compress_zstd_zstd_decompress(uint8_t *in, int32_t in_len, uint8_t *out,
                                                 int32_t out_cap);

int32_t std_compress_zstd_compress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_zstd_zstd_compress(in, in_len, out, out_cap);
}

int32_t std_compress_zstd_decompress(uint8_t *in, int32_t in_len, uint8_t *out, int32_t out_cap) {
  return std_compress_zstd_zstd_decompress(in, in_len, out, out_cap);
}

/* Stream surface (cookbook compress_stream_br_zs unique UNDEF).
 * format/mode match std/compress/mod.x constants. state_bytes_for returns
 * the real gzip/brotli/zstd caps (128/32/32) so the cookbook passes the
 * 1..512 gate. init/process/end trampoline to submodule stream T — same
 * contract as the one-shot faces.
 * PLATFORM: SHARED — c_face T only; product body remains gzip/zstd/brotli .o. */
typedef struct std_compress_StreamCompress {
  int32_t format;
  int32_t mode;
  uint8_t *state;
  int32_t state_cap;
} std_compress_StreamCompress;

/* PLATFORM: SHARED — product stream lives in gzip.o / brotli.o / zstd.o. */
extern int32_t std_compress_gzip_gzip_stream_init_compress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_gzip_gzip_stream_init_decompress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_gzip_gzip_stream_compress(uint8_t *state, int32_t state_cap,
                                                      uint8_t *inp, int32_t in_len, uint8_t *out,
                                                      int32_t out_cap, int32_t is_last,
                                                      int32_t *in_consumed);
extern int32_t std_compress_gzip_gzip_stream_decompress(uint8_t *state, int32_t state_cap,
                                                        uint8_t *inp, int32_t in_len, uint8_t *out,
                                                        int32_t out_cap, int32_t *in_consumed);
extern int32_t std_compress_gzip_gzip_stream_end(uint8_t *state, int32_t state_cap);

extern int32_t std_compress_brotli_brotli_stream_init_compress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_brotli_brotli_stream_init_decompress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_brotli_brotli_stream_compress(uint8_t *state, int32_t state_cap,
                                                          uint8_t *inp, int32_t in_len, uint8_t *out,
                                                          int32_t out_cap, int32_t is_last,
                                                          int32_t *in_consumed);
extern int32_t std_compress_brotli_brotli_stream_decompress(uint8_t *state, int32_t state_cap,
                                                            uint8_t *inp, int32_t in_len,
                                                            uint8_t *out, int32_t out_cap,
                                                            int32_t *in_consumed);
extern int32_t std_compress_brotli_brotli_stream_end(uint8_t *state, int32_t state_cap);

extern int32_t std_compress_zstd_zstd_stream_init_compress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_zstd_zstd_stream_init_decompress(uint8_t *state, int32_t state_cap);
extern int32_t std_compress_zstd_zstd_stream_compress(uint8_t *state, int32_t state_cap,
                                                      uint8_t *inp, int32_t in_len, uint8_t *out,
                                                      int32_t out_cap, int32_t is_last,
                                                      int32_t *in_consumed);
extern int32_t std_compress_zstd_zstd_stream_decompress(uint8_t *state, int32_t state_cap,
                                                        uint8_t *inp, int32_t in_len, uint8_t *out,
                                                        int32_t out_cap, int32_t *in_consumed);
extern int32_t std_compress_zstd_zstd_stream_end(uint8_t *state, int32_t state_cap);

extern int32_t std_compress_brotli_lib_compress_brotli_stream_init_decompress_c(uint8_t *state,
                                                                               int32_t state_cap);

int32_t std_compress_format_gzip(void) {
  return 0;
}

int32_t std_compress_format_brotli(void) {
  return 1;
}

int32_t std_compress_format_zstd(void) {
  return 2;
}

int32_t std_compress_mode_compress(void) {
  return 0;
}

int32_t std_compress_mode_decompress(void) {
  return 1;
}

int32_t std_compress_compress_state_bytes_for(int32_t format) {
  if (format == 0) {
    return 128;
  }
  if (format == 1) {
    return 32;
  }
  if (format == 2) {
    return 32;
  }
  return -1;
}

/* PLATFORM: SHARED — mod.x max(gzip=128, brotli=32, zstd=32). Needed when
 * link_only skips co-emit of compress_state_bytes (unified_stream_roundtrip). */
int32_t std_compress_compress_state_bytes(void) {
  return 128;
}

int32_t std_compress_compress_init(std_compress_StreamCompress *sc, uint8_t *state,
                                   int32_t state_cap, int32_t format, int32_t mode) {
  if (sc == 0) {
    return -1;
  }
  sc->format = format;
  sc->mode = mode;
  sc->state = state;
  sc->state_cap = state_cap;
  if (format == 0) {
    if (mode == 0) {
      return std_compress_gzip_gzip_stream_init_compress(state, state_cap);
    }
    if (mode == 1) {
      return std_compress_gzip_gzip_stream_init_decompress(state, state_cap);
    }
    return -2;
  }
  if (format == 1) {
    if (mode == 0) {
      return std_compress_brotli_brotli_stream_init_compress(state, state_cap);
    }
    if (mode == 1) {
      return std_compress_brotli_brotli_stream_init_decompress(state, state_cap);
    }
    return -2;
  }
  if (format == 2) {
    if (mode == 0) {
      return std_compress_zstd_zstd_stream_init_compress(state, state_cap);
    }
    if (mode == 1) {
      return std_compress_zstd_zstd_stream_init_decompress(state, state_cap);
    }
    return -2;
  }
  return -9;
}

int32_t std_compress_compress_process(std_compress_StreamCompress sc, uint8_t *inp,
                                      int32_t in_len, uint8_t *out, int32_t out_cap,
                                      int32_t is_last, int32_t *in_consumed) {
  if (sc.format == 0) {
    if (sc.mode == 0) {
      return std_compress_gzip_gzip_stream_compress(sc.state, sc.state_cap, inp, in_len, out,
                                                    out_cap, is_last, in_consumed);
    }
    if (sc.mode == 1) {
      return std_compress_gzip_gzip_stream_decompress(sc.state, sc.state_cap, inp, in_len, out,
                                                      out_cap, in_consumed);
    }
    return -9;
  }
  if (sc.format == 1) {
    if (sc.mode == 0) {
      return std_compress_brotli_brotli_stream_compress(sc.state, sc.state_cap, inp, in_len, out,
                                                        out_cap, is_last, in_consumed);
    }
    if (sc.mode == 1) {
      return std_compress_brotli_brotli_stream_decompress(sc.state, sc.state_cap, inp, in_len, out,
                                                          out_cap, in_consumed);
    }
    return -9;
  }
  if (sc.format == 2) {
    if (sc.mode == 0) {
      return std_compress_zstd_zstd_stream_compress(sc.state, sc.state_cap, inp, in_len, out,
                                                    out_cap, is_last, in_consumed);
    }
    if (sc.mode == 1) {
      return std_compress_zstd_zstd_stream_decompress(sc.state, sc.state_cap, inp, in_len, out,
                                                      out_cap, in_consumed);
    }
    return -9;
  }
  return -9;
}

int32_t std_compress_compress_end(std_compress_StreamCompress sc) {
  if (sc.format == 0) {
    return std_compress_gzip_gzip_stream_end(sc.state, sc.state_cap);
  }
  if (sc.format == 1) {
    return std_compress_brotli_brotli_stream_end(sc.state, sc.state_cap);
  }
  if (sc.format == 2) {
    return std_compress_zstd_zstd_stream_end(sc.state, sc.state_cap);
  }
  return -9;
}

/* PLATFORM: SHARED — g15 needles 24→28 (run-compress BLD001). gzip/brotli/zstd
 * lib.x co-emit calls these facade names (and one brotli-lib init) as U;
 * c_face is the compress.o product vehicle so it must export the T.
 * Caps match compress_state_bytes_for (128/32/32). Stream init/process/end
 * trampoline to submodule T (do not keep the constant-cap faces as -1). */
int32_t std_compress_gzip_stream_state_bytes(void) {
  return 128;
}

int32_t std_compress_brotli_stream_state_bytes(void) {
  return 32;
}

int32_t std_compress_zstd_stream_state_bytes(void) {
  return 32;
}

int32_t std_compress_gzip_stream_init_compress(uint8_t *state, int32_t state_cap) {
  return std_compress_gzip_gzip_stream_init_compress(state, state_cap);
}

int32_t std_compress_gzip_stream_init_decompress(uint8_t *state, int32_t state_cap) {
  return std_compress_gzip_gzip_stream_init_decompress(state, state_cap);
}

int32_t std_compress_gzip_stream_compress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                          int32_t in_len, uint8_t *out, int32_t out_cap,
                                          int32_t is_last, int32_t *in_consumed) {
  return std_compress_gzip_gzip_stream_compress(state, state_cap, inp, in_len, out, out_cap,
                                                is_last, in_consumed);
}

int32_t std_compress_gzip_stream_decompress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                            int32_t in_len, uint8_t *out, int32_t out_cap,
                                            int32_t *in_consumed) {
  return std_compress_gzip_gzip_stream_decompress(state, state_cap, inp, in_len, out, out_cap,
                                                  in_consumed);
}

int32_t std_compress_gzip_stream_end(uint8_t *state, int32_t state_cap) {
  return std_compress_gzip_gzip_stream_end(state, state_cap);
}

int32_t std_compress_brotli_stream_init_compress(uint8_t *state, int32_t state_cap) {
  return std_compress_brotli_brotli_stream_init_compress(state, state_cap);
}

int32_t std_compress_brotli_stream_init_decompress(uint8_t *state, int32_t state_cap) {
  return std_compress_brotli_brotli_stream_init_decompress(state, state_cap);
}

int32_t std_compress_brotli_stream_compress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                            int32_t in_len, uint8_t *out, int32_t out_cap,
                                            int32_t is_last, int32_t *in_consumed) {
  return std_compress_brotli_brotli_stream_compress(state, state_cap, inp, in_len, out, out_cap,
                                                    is_last, in_consumed);
}

int32_t std_compress_brotli_stream_decompress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                              int32_t in_len, uint8_t *out, int32_t out_cap,
                                              int32_t *in_consumed) {
  return std_compress_brotli_brotli_stream_decompress(state, state_cap, inp, in_len, out, out_cap,
                                                      in_consumed);
}

int32_t std_compress_brotli_stream_end(uint8_t *state, int32_t state_cap) {
  return std_compress_brotli_brotli_stream_end(state, state_cap);
}

int32_t std_compress_zstd_stream_init_compress(uint8_t *state, int32_t state_cap) {
  return std_compress_zstd_zstd_stream_init_compress(state, state_cap);
}

int32_t std_compress_zstd_stream_init_decompress(uint8_t *state, int32_t state_cap) {
  return std_compress_zstd_zstd_stream_init_decompress(state, state_cap);
}

int32_t std_compress_zstd_stream_compress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                          int32_t in_len, uint8_t *out, int32_t out_cap,
                                          int32_t is_last, int32_t *in_consumed) {
  return std_compress_zstd_zstd_stream_compress(state, state_cap, inp, in_len, out, out_cap,
                                                is_last, in_consumed);
}

int32_t std_compress_zstd_stream_decompress(uint8_t *state, int32_t state_cap, uint8_t *inp,
                                            int32_t in_len, uint8_t *out, int32_t out_cap,
                                            int32_t *in_consumed) {
  return std_compress_zstd_zstd_stream_decompress(state, state_cap, inp, in_len, out, out_cap,
                                                  in_consumed);
}

int32_t std_compress_zstd_stream_end(uint8_t *state, int32_t state_cap) {
  return std_compress_zstd_zstd_stream_end(state, state_cap);
}

int32_t std_compress_brotli_lib_compress_brotli_stream_init_decompress_(uint8_t *state,
                                                                        int32_t state_cap) {
  return std_compress_brotli_lib_compress_brotli_stream_init_decompress_c(state, state_cap);
}
