/**
 * tests/sys/random_cap_raw_smoke.c — Linux raw syscall random Cap probe (9.1.6).
 *
 * Verifies xlang_random_fill_bytes without libc getrandom / errno on Linux:
 * 1. Single chunk random fill (32 bytes) returns 32, not all-zero
 * 2. Second fill produces different bytes (CSPRNG sanity)
 * 3. Zero length returns 0
 * 4. NULL buffer returns -1
 * 5. Negative length returns -1
 * 6. Multi-chunk fill (>256 bytes, e.g. 500 bytes) succeeds and is not all-zero
 *
 * PLATFORM: LINUX raw syscall Cap (9.1.6).
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "compiler/include/xlang_random_cap.h"

int main(void) {
  uint8_t b1[32];
  uint8_t b2[32];
  uint8_t b_large[500];
  int i;
  int all_zero;

  /* Step 1: 32 bytes random fill */
  memset(b1, 0, sizeof(b1));
  if (xlang_random_fill_bytes(b1, (int32_t)sizeof(b1)) != (int32_t)sizeof(b1)) {
    return 1;
  }
  all_zero = 1;
  for (i = 0; i < (int)sizeof(b1); i++) {
    if (b1[i] != 0) {
      all_zero = 0;
      break;
    }
  }
  if (all_zero) return 2;

  /* Step 2: second 32 bytes fill, verify randomness */
  memset(b2, 0, sizeof(b2));
  if (xlang_random_fill_bytes(b2, (int32_t)sizeof(b2)) != (int32_t)sizeof(b2)) {
    return 3;
  }
  if (memcmp(b1, b2, sizeof(b1)) == 0) return 4;

  /* Step 3: zero length */
  if (xlang_random_fill_bytes(b1, 0) != 0) return 5;

  /* Step 4: NULL buffer */
  if (xlang_random_fill_bytes(NULL, 16) != -1) return 6;

  /* Step 5: Negative length */
  if (xlang_random_fill_bytes(b1, -1) != -1) return 7;

  /* Step 6: Multi-chunk fill (>256 bytes) */
  memset(b_large, 0, sizeof(b_large));
  if (xlang_random_fill_bytes(b_large, (int32_t)sizeof(b_large)) != (int32_t)sizeof(b_large)) {
    return 8;
  }
  all_zero = 1;
  for (i = 0; i < (int)sizeof(b_large); i++) {
    if (b_large[i] != 0) {
      all_zero = 0;
      break;
    }
  }
  if (all_zero) return 9;

  return 0;
}
