/*
 * thread_cap_raw_smoke.c — Stage 10 (10.6.1) Cap residual probe.
 *
 * Host-cc smoke for xlang_thread_cap.h:
 *   slice0: mmap stack + futex wake + timed wait
 *   slice1: clone3/clone spawn + join (no libpthread)
 *
 * PLATFORM: LINUX|x86_64|aarch64 gold.
 *
 * Build (gate): cc -O0 -Icompiler/include -o /tmp/... tests/sys/thread_cap_raw_smoke.c
 * Exit: 0 ok; 1..8 step failure.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_thread_cap.h>

#ifndef __linux__
int main(void) {
  fprintf(stderr, "thread_cap_raw_smoke: Linux only\n");
  return 0;
}
#else

/** Shared slot written by Cap-spawned child. */
static volatile int g_child_slot = 0;

/**
 * Cap spawn child: set shared slot to 42.
 * @param arg unused
 * @return NULL
 * PLATFORM: LINUX
 */
static void *thread_cap_child(void *arg) {
  (void)arg;
  g_child_slot = 42;
  return 0;
}

/**
 * Cap residual 10.6.1 probe entry (slice0 futex/mmap + slice1 spawn/join).
 * @return 0 ok; nonzero step id on failure
 * PLATFORM: LINUX
 */
int main(void) {
  const size_t stack_len = 65536u;
  void *stack = 0;
  volatile uint32_t word = 0;
  long wr = 0;
  long r = 0;
  struct xlang_thread_join join;

  /* Step1: mmap anonymous stack and touch. */
  stack = xlang_thread_mmap_stack(stack_len);
  if (stack == 0) {
    fprintf(stderr, "mmap_stack failed errno=%d\n", errno);
    return 1;
  }
  ((volatile unsigned char *)stack)[0] = 42;
  ((volatile unsigned char *)stack)[stack_len - 1u] = 7;
  if (xlang_thread_munmap_stack(stack, stack_len) != 0) {
    fprintf(stderr, "munmap_stack failed errno=%d\n", errno);
    return 2;
  }

  /* Step2: wake with zero waiters must succeed (returns 0). */
  word = 0;
  wr = xlang_futex_wake((uint32_t *)&word, 1);
  if (wr < 0) {
    fprintf(stderr, "futex_wake failed errno=%d\n", errno);
    return 3;
  }

  /* Step3: wait while word==0 with 1ms timeout → ETIMEDOUT. */
  word = 0;
  r = xlang_futex_wait_timeout_ns((uint32_t *)&word, 0, 1000000LL);
  if (r == 0) {
    fprintf(stderr, "futex_wait unexpectedly woke\n");
    return 4;
  }
  if (errno != ETIMEDOUT && errno != EAGAIN) {
    fprintf(stderr, "futex_wait errno=%d (want ETIMEDOUT/EAGAIN)\n", errno);
    return 5;
  }

  /* Step4: Cap spawn + join (clone3 / clone fallback). */
  memset(&join, 0, sizeof(join));
  g_child_slot = 0;
  if (xlang_thread_spawn(thread_cap_child, 0, &join, stack_len) != 0) {
    fprintf(stderr, "thread_spawn failed errno=%d\n", errno);
    return 6;
  }
  if (xlang_thread_join(&join) != 0) {
    fprintf(stderr, "thread_join failed errno=%d\n", errno);
    return 7;
  }
  if (g_child_slot != 42) {
    fprintf(stderr, "child slot=%d want 42\n", g_child_slot);
    return 8;
  }

  /* Step5: Cap residual 9.4.6 — Linux affinity and QoS */
  if (xlang_thread_set_affinity_self(0) != 0) {
    fprintf(stderr, "affinity self(0) failed errno=%d\n", errno);
    return 9;
  }
  if (xlang_thread_set_affinity_self(-1) == 0 || errno != EINVAL) {
    fprintf(stderr, "affinity self(-1) want EINVAL\n");
    return 10;
  }
  if (xlang_thread_set_qos_self(0) == 0 || errno != ENOSYS) {
    fprintf(stderr, "qos self(0) want ENOSYS\n");
    return 11;
  }

  return 0;
}

#endif /* __linux__ */
