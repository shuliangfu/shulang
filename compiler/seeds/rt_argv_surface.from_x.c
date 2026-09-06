/* seeds/rt_argv_surface.from_x.c
 * G-02f rt_argv R2 full surface — isomorphic with src/runtime/rt_argv.x
 * Product PREFER_X_O: g05_try_x_to_o(rt_argv.x) + rest seed empty under FROM_X
 * Prove: full.x vs this seed → nm IDENTICAL (15 public drv_eq_* / path / target helpers)
 * Regen: ./xlang -E ... src/runtime/rt_argv.x | filter DBG + polish prologue
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int32_t drv_eq_minus_o(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] !=45) || ((buf)[1] !=111))) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_L(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] !=45) || ((buf)[1] !=76))) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_O(uint8_t * buf, int32_t len) {
  if ((len !=2)) {
    return 0;
  }
  if ((((buf)[0] !=45) || ((buf)[1] !=79))) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_flto(uint8_t * buf, int32_t len) {
  if ((len !=5)) {
    return 0;
  }
  if (((((((buf)[0] !=45) || ((buf)[1] !=102)) || ((buf)[2] !=108)) || ((buf)[3] !=116)) || ((buf)[4] !=111))) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_freestanding(uint8_t * buf, int32_t len) {
  if ((len !=13)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=102)) {
    return 0;
  }
  if (((buf)[2] !=114)) {
    return 0;
  }
  if (((buf)[3] !=101)) {
    return 0;
  }
  if (((buf)[4] !=101)) {
    return 0;
  }
  if (((buf)[5] !=115)) {
    return 0;
  }
  if (((buf)[6] !=116)) {
    return 0;
  }
  if (((buf)[7] !=97)) {
    return 0;
  }
  if (((buf)[8] !=110)) {
    return 0;
  }
  if (((buf)[9] !=100)) {
    return 0;
  }
  if (((buf)[10] !=105)) {
    return 0;
  }
  if (((buf)[11] !=110)) {
    return 0;
  }
  if (((buf)[12] !=103)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_legacy_f32_abi(uint8_t * buf, int32_t len) {
  if ((len !=15)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=108)) {
    return 0;
  }
  if (((buf)[2] !=101)) {
    return 0;
  }
  if (((buf)[3] !=103)) {
    return 0;
  }
  if (((buf)[4] !=97)) {
    return 0;
  }
  if (((buf)[5] !=99)) {
    return 0;
  }
  if (((buf)[6] !=121)) {
    return 0;
  }
  if (((buf)[7] !=45)) {
    return 0;
  }
  if (((buf)[8] !=102)) {
    return 0;
  }
  if (((buf)[9] !=51)) {
    return 0;
  }
  if (((buf)[10] !=50)) {
    return 0;
  }
  if (((buf)[11] !=45)) {
    return 0;
  }
  if (((buf)[12] !=97)) {
    return 0;
  }
  if (((buf)[13] !=98)) {
    return 0;
  }
  if (((buf)[14] !=105)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_fsanitize_address(uint8_t * buf, int32_t len) {
  if ((len !=18)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=102)) {
    return 0;
  }
  if (((buf)[2] !=115)) {
    return 0;
  }
  if (((buf)[3] !=97)) {
    return 0;
  }
  if (((buf)[4] !=110)) {
    return 0;
  }
  if (((buf)[5] !=105)) {
    return 0;
  }
  if (((buf)[6] !=116)) {
    return 0;
  }
  if (((buf)[7] !=105)) {
    return 0;
  }
  if (((buf)[8] !=122)) {
    return 0;
  }
  if (((buf)[9] !=101)) {
    return 0;
  }
  if (((buf)[10] !=61)) {
    return 0;
  }
  if (((buf)[11] !=97)) {
    return 0;
  }
  if (((buf)[12] !=100)) {
    return 0;
  }
  if (((buf)[13] !=100)) {
    return 0;
  }
  if (((buf)[14] !=114)) {
    return 0;
  }
  if (((buf)[15] !=101)) {
    return 0;
  }
  if (((buf)[16] !=115)) {
    return 0;
  }
  if (((buf)[17] !=115)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_backend(uint8_t * buf, int32_t len) {
  if ((len !=8)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=98)) {
    return 0;
  }
  if (((buf)[2] !=97)) {
    return 0;
  }
  if (((buf)[3] !=99)) {
    return 0;
  }
  if (((buf)[4] !=107)) {
    return 0;
  }
  if (((buf)[5] !=101)) {
    return 0;
  }
  if (((buf)[6] !=110)) {
    return 0;
  }
  if (((buf)[7] !=100)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_target(uint8_t * buf, int32_t len) {
  if ((len != 7)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=116)) {
    return 0;
  }
  if (((buf)[2] !=97)) {
    return 0;
  }
  if (((buf)[3] !=114)) {
    return 0;
  }
  if (((buf)[4] !=103)) {
    return 0;
  }
  if (((buf)[5] !=101)) {
    return 0;
  }
  if (((buf)[6] !=116)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_minus_target_cpu(uint8_t * buf, int32_t len) {
  if ((len != 11)) {
    return 0;
  }
  if (((buf)[0] !=45)) {
    return 0;
  }
  if (((buf)[1] !=116)) {
    return 0;
  }
  if (((buf)[2] !=97)) {
    return 0;
  }
  if (((buf)[3] !=114)) {
    return 0;
  }
  if (((buf)[4] !=103)) {
    return 0;
  }
  if (((buf)[5] !=101)) {
    return 0;
  }
  if (((buf)[6] !=116)) {
    return 0;
  }
  if (((buf)[7] !=45)) {
    return 0;
  }
  if (((buf)[8] !=99)) {
    return 0;
  }
  if (((buf)[9] !=112)) {
    return 0;
  }
  if (((buf)[10] !=117)) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_print_target_cpu(uint8_t * buf, int32_t len) {
  if ((len ==18)) {
    if (((buf)[0] !=45)) {
      return 0;
    }
    if (((buf)[1] !=45)) {
      return 0;
    }
    if (((buf)[2] !=112)) {
      return 0;
    }
    if (((buf)[3] !=114)) {
      return 0;
    }
    if (((buf)[4] !=105)) {
      return 0;
    }
    if (((buf)[5] !=110)) {
      return 0;
    }
    if (((buf)[6] !=116)) {
      return 0;
    }
    if (((buf)[7] !=45)) {
      return 0;
    }
    if (((buf)[8] !=116)) {
      return 0;
    }
    if (((buf)[9] !=97)) {
      return 0;
    }
    if (((buf)[10] !=114)) {
      return 0;
    }
    if (((buf)[11] !=103)) {
      return 0;
    }
    if (((buf)[12] !=101)) {
      return 0;
    }
    if (((buf)[13] !=116)) {
      return 0;
    }
    if (((buf)[14] !=45)) {
      return 0;
    }
    if (((buf)[15] !=99)) {
      return 0;
    }
    if (((buf)[16] !=112)) {
      return 0;
    }
    if (((buf)[17] !=117)) {
      return 0;
    }
    return 1;
  }
  if ((len ==17)) {
    if (((buf)[0] !=45)) {
      return 0;
    }
    if (((buf)[1] !=112)) {
      return 0;
    }
    if (((buf)[2] !=114)) {
      return 0;
    }
    if (((buf)[3] !=105)) {
      return 0;
    }
    if (((buf)[4] !=110)) {
      return 0;
    }
    if (((buf)[5] !=116)) {
      return 0;
    }
    if (((buf)[6] !=45)) {
      return 0;
    }
    if (((buf)[7] !=116)) {
      return 0;
    }
    if (((buf)[8] !=97)) {
      return 0;
    }
    if (((buf)[9] !=114)) {
      return 0;
    }
    if (((buf)[10] !=103)) {
      return 0;
    }
    if (((buf)[11] !=101)) {
      return 0;
    }
    if (((buf)[12] !=116)) {
      return 0;
    }
    if (((buf)[13] !=45)) {
      return 0;
    }
    if (((buf)[14] !=99)) {
      return 0;
    }
    if (((buf)[15] !=112)) {
      return 0;
    }
    if (((buf)[16] !=117)) {
      return 0;
    }
    return 1;
  }
  return 0;
}
int32_t drv_eq_asm_word(uint8_t * buf, int32_t len) {
  if ((len !=3)) {
    return 0;
  }
  if (((((buf)[0] !=97) || ((buf)[1] !=115)) || ((buf)[2] !=109))) {
    return 0;
  }
  return 1;
}
int32_t drv_eq_c_word(uint8_t * buf, int32_t len) {
  if ((len !=1)) {
    return 0;
  }
  if (((buf)[0] !=99)) {
    return 0;
  }
  return 1;
}
int32_t drv_path_ends_x(uint8_t * buf, int32_t len) {
  if ((((len >=2) && ((buf)[((size_t)((len - 2)))] ==46)) && ((buf)[((size_t)((len - 1)))] ==120))) {
    return 1;
  }
  if (((((len >=3) && ((buf)[((size_t)((len - 3)))] ==46)) && ((buf)[((size_t)((len - 2)))] ==115)) && ((buf)[((size_t)((len - 1)))] ==117))) {
    return 1;
  }
  return 0;
}
int32_t drv_target_has_arm(uint8_t * buf, int32_t len) {
  int32_t start = 0;
  while (((start + 5) <=len)) {
    if (((((((buf)[((size_t)(start))] ==97) && ((buf)[((size_t)((start + 1)))] ==114)) && ((buf)[((size_t)((start + 2)))] ==109)) && ((buf)[((size_t)((start + 3)))] ==54)) && ((buf)[((size_t)((start + 4)))] ==52))) {
      return 1;
    }
    (void)((start = (start + 1)));
  }
  return 0;
}
