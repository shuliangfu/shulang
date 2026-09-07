/* seeds/target_cpu_pure_surface.from_x.c
 * G-02f target_cpu_pure R2 full surface — isomorphic with src/driver/target_cpu_pure.x
 * Product PREFER_X_O: g05_try_x_to_o(target_cpu_pure.x) + mega rest under FROM_X
 * Prove: full.x vs this seed -> nm IDENTICAL (12 public business funcs + BSS)
 * Cap residual: xlang_target_cpu_print (Cap io write, fd-handle face 9.7.2) + OS detect (sysctl / proc / #if) in mega rest
 * Regen: ./xlang -E ... src/driver/target_cpu_pure.x | filter DBG + polish prologue
 * NOTE: must use ./xlang (not xlang-x); xlang-x adds driver_ prefix to non-#[no_mangle] funcs.
 */
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
extern void driver_set_pending_target_cpu_features(uint32_t features);
extern uint32_t driver_get_pending_target_cpu_features(void);
extern uint8_t tcp_tolower(uint8_t c);
extern int32_t tcp_eq_at(uint8_t * name, size_t base, size_t n, uint8_t lit0, uint8_t lit1, uint8_t lit2, uint8_t lit3, uint8_t lit4, uint8_t lit5, uint8_t lit6, uint8_t lit7, uint8_t lit8);
extern void tcp_set_u32(uint32_t * out, uint32_t f);
extern int32_t tcp_parse_named(uint8_t * spec, size_t base, size_t end, uint32_t * out);
extern int32_t xlang_target_cpu_resolve(uint8_t * spec, size_t spec_len, uint32_t * out);
extern int32_t tcp_eq5(uint8_t * name, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4);
extern int32_t tcp_eq6(uint8_t * name, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5);
extern int32_t xlang_simd_is_vector_type_spelling(uint8_t * name, size_t name_len);
extern int32_t xlang_simd_vector_lanes_esz_from_spelling(uint8_t * name, size_t name_len, int32_t * out_lanes, int32_t * out_esz);
extern void append_feat_name(uint8_t * buf, size_t cap, size_t * pos, uint8_t * name);
extern int32_t flags_has_token(uint8_t * hay, uint8_t * token);
#undef g_driver_pending_target_cpu_features
static uint32_t g_driver_pending_target_cpu_features = 0;
static void init_globals(void) {
  g_driver_pending_target_cpu_features = 0;
}
extern uint32_t xlang_target_cpu_detect_host(void);
extern uint32_t xlang_target_cpu_generic_for_host(void);
void driver_set_pending_target_cpu_features(uint32_t features) {
  (void)((g_driver_pending_target_cpu_features = features));
}
uint32_t driver_get_pending_target_cpu_features(void) {
  return g_driver_pending_target_cpu_features;
}
uint8_t tcp_tolower(uint8_t c) {
  if (((c >=65) && (c <=90))) {
    return ((uint8_t)((c + 32)));
  }
  return c;
}
int32_t tcp_eq_at(uint8_t * name, size_t base, size_t n, uint8_t lit0, uint8_t lit1, uint8_t lit2, uint8_t lit3, uint8_t lit4, uint8_t lit5, uint8_t lit6, uint8_t lit7, uint8_t lit8) {
  size_t i = 0;
  uint8_t want = 0;
  while ((i < n)) {
    if ((i ==0)) {
      (void)((want = lit0));
    }
    if ((i ==1)) {
      (void)((want = lit1));
    }
    if ((i ==2)) {
      (void)((want = lit2));
    }
    if ((i ==3)) {
      (void)((want = lit3));
    }
    if ((i ==4)) {
      (void)((want = lit4));
    }
    if ((i ==5)) {
      (void)((want = lit5));
    }
    if ((i ==6)) {
      (void)((want = lit6));
    }
    if ((i ==7)) {
      (void)((want = lit7));
    }
    if ((i ==8)) {
      (void)((want = lit8));
    }
    if ((tcp_tolower((name)[(base + i)]) !=want)) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
void tcp_set_u32(uint32_t * out, uint32_t f) {
  (void)(((out)[0] = f));
}
int32_t tcp_parse_named(uint8_t * spec, size_t base, size_t end, uint32_t * out) {
  size_t n = 0;
  uint32_t f = 0;
  if ((end < base)) {
    return -1;
  }
  (void)((n = (end - base)));
  if (((n ==6) && (tcp_eq_at(spec, base, 6, 110, 97, 116, 105, 118, 101, 0, 0, 0) !=0))) {
    (void)((f = xlang_target_cpu_detect_host()));
    (void)(tcp_set_u32(out, f));
    return 0;
  }
  if (((n ==7) && (tcp_eq_at(spec, base, 7, 103, 101, 110, 101, 114, 105, 99, 0, 0) !=0))) {
    (void)((f = xlang_target_cpu_generic_for_host()));
    (void)(tcp_set_u32(out, f));
    return 0;
  }
  if (((n ==4) && (tcp_eq_at(spec, base, 4, 115, 115, 101, 50, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 1));
    return 0;
  }
  if (((n ==6) && ((tcp_eq_at(spec, base, 6, 115, 115, 101, 52, 46, 49, 0, 0, 0) !=0) || (tcp_eq_at(spec, base, 6, 115, 115, 101, 52, 95, 49, 0, 0, 0) !=0)))) {
    (void)(tcp_set_u32(out, 3));
    return 0;
  }
  if (((n ==3) && (tcp_eq_at(spec, base, 3, 97, 118, 120, 0, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 7));
    return 0;
  }
  if (((n ==4) && (tcp_eq_at(spec, base, 4, 97, 118, 120, 50, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 15));
    return 0;
  }
  if (((n ==6) && (tcp_eq_at(spec, base, 6, 97, 118, 120, 53, 49, 50, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 31));
    return 0;
  }
  if (((n ==7) && (tcp_eq_at(spec, base, 7, 97, 118, 120, 53, 49, 50, 102, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 31));
    return 0;
  }
  if (((n ==9) && (tcp_eq_at(spec, base, 9, 120, 56, 54, 45, 54, 52, 45, 118, 50) !=0))) {
    (void)(tcp_set_u32(out, 35));
    return 0;
  }
  if (((n ==9) && (tcp_eq_at(spec, base, 9, 120, 56, 54, 45, 54, 52, 45, 118, 51) !=0))) {
    (void)(tcp_set_u32(out, 111));
    return 0;
  }
  if (((n ==9) && (tcp_eq_at(spec, base, 9, 120, 56, 54, 45, 54, 52, 45, 118, 52) !=0))) {
    (void)(tcp_set_u32(out, 127));
    return 0;
  }
  if (((n ==4) && (tcp_eq_at(spec, base, 4, 110, 101, 111, 110, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 256));
    return 0;
  }
  if (((n ==3) && (tcp_eq_at(spec, base, 3, 115, 118, 101, 0, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 768));
    return 0;
  }
  if (((n ==3) && (tcp_eq_at(spec, base, 3, 114, 118, 118, 0, 0, 0, 0, 0, 0) !=0))) {
    (void)(tcp_set_u32(out, 65536));
    return 0;
  }
  return -1;
}
int32_t xlang_target_cpu_resolve(uint8_t * spec, size_t spec_len, uint32_t * out) {
  size_t start = 0;
  size_t end = 0;
  uint32_t f = 0;
  if ((out ==0)) {
    return -1;
  }
  if (((spec ==0) || (spec_len ==0))) {
    (void)((f = xlang_target_cpu_detect_host()));
    (void)(tcp_set_u32(out, f));
    return 0;
  }
  (void)((end = spec_len));
  while (((start < end) && (((spec)[start] ==32) || ((spec)[start] ==9)))) {
    (void)((start = (start + 1)));
  }
  while (((end > start) && (((spec)[(end - 1)] ==32) || ((spec)[(end - 1)] ==9)))) {
    (void)((end = (end - 1)));
  }
  if ((end <=start)) {
    (void)((f = xlang_target_cpu_detect_host()));
    (void)(tcp_set_u32(out, f));
    return 0;
  }
  return tcp_parse_named(spec, start, end, out);
}
int32_t tcp_eq5(uint8_t * name, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4) {
  return tcp_eq_at(name, 0, 5, a0, a1, a2, a3, a4, 0, 0, 0, 0);
}
int32_t tcp_eq6(uint8_t * name, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5) {
  return tcp_eq_at(name, 0, 6, a0, a1, a2, a3, a4, a5, 0, 0, 0);
}
int32_t xlang_simd_is_vector_type_spelling(uint8_t * name, size_t name_len) {
  if (((name ==0) || (name_len ==0))) {
    return 0;
  }
  if ((name_len ==5)) {
    if ((tcp_eq5(name, 105, 51, 50, 120, 52) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 105, 51, 50, 120, 56) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 117, 51, 50, 120, 52) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 117, 51, 50, 120, 56) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 102, 51, 50, 120, 52) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 118, 101, 99, 52, 102) !=0)) {
      return 1;
    }
    if ((tcp_eq5(name, 118, 101, 99, 56, 105) !=0)) {
      return 1;
    }
  }
  if ((name_len ==6)) {
    if ((tcp_eq6(name, 105, 51, 50, 120, 49, 54) !=0)) {
      return 1;
    }
    if ((tcp_eq6(name, 117, 51, 50, 120, 49, 54) !=0)) {
      return 1;
    }
  }
  return 0;
}
int32_t xlang_simd_vector_lanes_esz_from_spelling(uint8_t * name, size_t name_len, int32_t * out_lanes, int32_t * out_esz) {
  int32_t lanes = 4;
  int32_t esz = 4;
  if (((out_lanes ==0) || (out_esz ==0))) {
    return -1;
  }
  if ((xlang_simd_is_vector_type_spelling(name, name_len) ==0)) {
    return -1;
  }
  if (((name_len ==5) && ((name)[4] ==56))) {
    (void)((lanes = 8));
  }
  if ((((name_len ==6) && ((name)[4] ==49)) && ((name)[5] ==54))) {
    (void)((lanes = 16));
  }
  if (((name_len ==5) && (tcp_eq5(name, 118, 101, 99, 56, 105) !=0))) {
    (void)((lanes = 8));
  }
  (void)(((out_lanes)[0] = lanes));
  (void)(((out_esz)[0] = esz));
  return 0;
}
void append_feat_name(uint8_t * buf, size_t cap, size_t * pos, uint8_t * name) {
  if ((buf ==0)) {
    return;
  }
  if ((pos ==0)) {
    return;
  }
  if ((name ==0)) {
    return;
  }
  size_t p = (pos)[0];
  if ((p >=cap)) {
    return;
  }
  if ((p > 0)) {
    if (((p + 1) < cap)) {
      (void)(((buf)[((int32_t)(p))] = 44));
      (void)((p = (p + 1)));
    }
  }
  size_t nlen = 0;
  while ((nlen < 256)) {
    if (((name)[((int32_t)(nlen))] ==0)) {
      break;
    }
    (void)((nlen = (nlen + 1)));
  }
  if (((p + nlen) >=cap)) {
    return;
  }
  size_t i = 0;
  while ((i < nlen)) {
    (void)(((buf)[((int32_t)((p + i)))] = (name)[((int32_t)(i))]));
    (void)((i = (i + 1)));
  }
  (void)((p = (p + nlen)));
  (void)(((buf)[((int32_t)(p))] = 0));
  (void)(((pos)[0] = p));
}
int32_t flags_has_token(uint8_t * hay, uint8_t * token) {
  if ((hay ==0)) {
    return 0;
  }
  if ((token ==0)) {
    return 0;
  }
  int32_t tlen = 0;
  while ((tlen < 256)) {
    if (((token)[tlen] ==0)) {
      break;
    }
    (void)((tlen = (tlen + 1)));
  }
  if ((tlen <=0)) {
    return 0;
  }
  int32_t i = 0;
  while ((i < 65536)) {
    if (((hay)[i] ==0)) {
      break;
    }
    int32_t ok = 1;
    int32_t j = 0;
    while ((j < tlen)) {
      if (((hay)[(i + j)] !=(token)[j])) {
        (void)((ok = 0));
        break;
      }
      (void)((j = (j + 1)));
    }
    if ((ok !=0)) {
      int32_t b_ok = 0;
      if ((i ==0)) {
        (void)((b_ok = 1));
      } else {
        uint8_t before = (hay)[(i - 1)];
        if ((before ==32)) {
          (void)((b_ok = 1));
        }
        if ((before ==9)) {
          (void)((b_ok = 1));
        }
        if ((before ==44)) {
          (void)((b_ok = 1));
        }
      }
      uint8_t after = (hay)[(i + tlen)];
      int32_t a_ok = 0;
      if ((after ==0)) {
        (void)((a_ok = 1));
      }
      if ((after ==32)) {
        (void)((a_ok = 1));
      }
      if ((after ==9)) {
        (void)((a_ok = 1));
      }
      if ((after ==44)) {
        (void)((a_ok = 1));
      }
      if ((after ==10)) {
        (void)((a_ok = 1));
      }
      if ((b_ok !=0)) {
        if ((a_ok !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
