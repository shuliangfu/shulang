/*
 * thread_cap_win_smoke.c — Stage 10 (10.6.2) Cap residual probe (Windows).
 *
 * Host-cc smoke for xlang_thread_cap.h Windows CreateThread Cap spawn/join.
 * PLATFORM: WINDOWS gold when MSYS/Win host available; non-Win gate skip=1.
 *
 * Build (gate): cc -O0 -Icompiler/include -o /tmp/... tests/sys/thread_cap_win_smoke.c
 * Exit: 0 ok; 1..5 step failure.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xlang_thread_cap.h>

#if !defined(_WIN32) && !defined(_WIN64)
int main(void) {
  fprintf(stderr, "thread_cap_win_smoke: Windows only\n");
  return 0;
}
#else

static volatile int g_child_marker = 0;

/**
 * Cap child: set marker then return.
 * @param arg unused
 * @return NULL
 * PLATFORM: WINDOWS
 */
static void *thread_cap_win_child(void *arg) {
  (void)arg;
  g_child_marker = 42;
  return 0;
}

/**
 * Cap residual 10.6.2 probe entry (CreateThread spawn/join).
 * @return 0 ok; nonzero step id on failure
 * PLATFORM: WINDOWS
 */
int main(void) {
  struct xlang_thread_join join;

  g_child_marker = 0;
  memset(&join, 0, sizeof(join));
  if (xlang_thread_spawn(thread_cap_win_child, 0, &join, 65536u) != 0) {
    fprintf(stderr, "spawn failed errno=%d\n", errno);
    return 1;
  }
  if (xlang_thread_join(&join) != 0) {
    fprintf(stderr, "join failed errno=%d\n", errno);
    return 2;
  }
  if (g_child_marker != 42) {
    fprintf(stderr, "g_child_marker=%d want 42\n", g_child_marker);
    return 3;
  }

  /* Null join / null fn reject. */
  if (xlang_thread_spawn(0, 0, &join, 65536u) == 0) {
    fprintf(stderr, "spawn null fn unexpectedly ok\n");
    return 4;
  }
  if (xlang_thread_join(0) == 0) {
    fprintf(stderr, "join null unexpectedly ok\n");
    return 5;
  }

  /* Step 6: Cap residual 9.4.6 — Affinity & QoS */
  if (xlang_thread_set_affinity_self(0) != 0) {
    fprintf(stderr, "affinity self(0) failed errno=%d\n", errno);
    return 6;
  }
  if (xlang_thread_set_affinity_self(-1) == 0) {
    fprintf(stderr, "affinity self(-1) unexpectedly ok\n");
    return 7;
  }
  if (xlang_thread_set_qos_self(0) == 0 || errno != ENOSYS) {
    fprintf(stderr, "qos self(0) want ENOSYS\n");
    return 8;
  }

  return 0;
}

#endif /* WINDOWS */
