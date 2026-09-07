/* seeds/rt_stack.from_x.c — G-02f-317 P2 runtime R8-lite (stack esc pthread gate)
 * Logic source: src/runtime/rt_stack.x
 * Hybrid: XLANG_RT_STACK_FROM_X + ld -r into runtime_driver_no_c.o
 *
 * R2 full：thread_fn + large_stack 由 .x 提供；FROM_X 下本文件仅前向声明 + slice marker
 * （产品 rest 业务 H=0）。冷启动/无 PREFER 时仍编译完整 C 体。
 * Cap-fn-ptr residual：.x 与冷启动 C 体一致，均经 wave37 编排
 * driver_run_stack_esc_gate_on_large_stack（driver_abi）绑定 thread_fn；
 * 9.7.6 前冷体曾直接传函数指针给 driver_run_thread_on_large_stack（已收敛）。
 */
#include <stddef.h>
#include <stdint.h>

/** xlang check 后 X 栈逃逸 gate 大栈线程参数。 */
typedef struct {
  uint8_t *src;
  int32_t src_len;
  int32_t result;
} DriverStackEscGateArgs;

extern int32_t pipeline_typeck_x_stack_escape_gate_from_src_c(uint8_t *src, int32_t src_len);
/* 9.7.6 G.7: cold body binds thread_fn only via the wave37 orch
 * (driver_abi: fn-ptr residual + G.7 driver_run_thread_on_large_stack). */
extern void driver_run_stack_esc_gate_on_large_stack(uint8_t *arg);

#ifndef XLANG_RT_STACK_FROM_X

/** pthread 入口：WPO-S3 post-scan gate；null arg 直接返回（同 .x 权威）。 */
void *driver_stack_esc_gate_thread_fn(void *arg) {
  DriverStackEscGateArgs *a = (DriverStackEscGateArgs *)arg;
  if (a == NULL)
    return NULL;
  a->result = pipeline_typeck_x_stack_escape_gate_from_src_c(a->src, a->src_len);
  return NULL;
}

/**
 * 在 256MiB 栈 pthread 上跑 X struct 栈逃逸 gate（check 路径；勿在主线程 parse）。
 * result 仍为 -99（线程未跑，如创建失败）→ 主线程回退直接跑 gate。
 */
int32_t driver_stack_esc_gate_large_stack(uint8_t *src, int32_t src_len) {
  DriverStackEscGateArgs args;
  args.src = src;
  args.src_len = src_len;
  args.result = -99;
  driver_run_stack_esc_gate_on_large_stack((uint8_t *)&args);
  if (args.result == -99)
    return pipeline_typeck_x_stack_escape_gate_from_src_c(src, src_len);
  return args.result;
}

#else
void *driver_stack_esc_gate_thread_fn(void *arg);
int32_t driver_stack_esc_gate_large_stack(uint8_t *src, int32_t src_len);
#endif

int labi_rt_stack_slice_marker(void) {
  return 1;
}
