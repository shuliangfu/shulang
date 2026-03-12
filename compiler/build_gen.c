/* generated from build */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static void shulang_panic_(int has_msg, int msg_val) {
  if (has_msg) (void)fprintf(stderr, "%d\n", msg_val);
  abort();
}
int32_t build_build_get_step_count();
int32_t build_build_get_step_at(int32_t i);
int32_t build_build_get_step_count() {
  return 7;
}
int32_t build_build_get_step_at(int32_t i) {
  (void)(({ int32_t __tmp = 0; if (i == 0) {   return 0;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 1) {   return 6;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 2) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 3) {   return 2;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 4) {   return 3;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 5) {   return 4;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (i == 6) {   return 5;
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
}
