/* seeds/labi_host_lit.from_x.c — G-02f-269/L P2 link_abi L2 host lit → R2 full
 * Logic source: src/runtime/labi_host_lit.x
 * Hybrid: XLANG_LABI_HOST_LIT_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14）：公共业务符号由 full .x 提供：
 *   xlang_host_is_linux + xlang_host_is_apple_aarch64 + labi_host_lit_count
 * Cap residual（mega rest 常驻）：
 *   xlang_host_is_linux_impl（#if __linux__）
 *   xlang_host_is_apple_aarch64_impl（#if __APPLE__ && __aarch64__）
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C thin 体（可与 mega _impl 并存）。
 *
 */

/* Host #if bodies provided by runtime_link_abi.from_x.c rest (always). */
int xlang_host_is_linux_impl(void);
int xlang_host_is_apple_aarch64_impl(void);

#ifndef XLANG_LABI_HOST_LIT_FROM_X

int xlang_host_is_linux(void) {
  return xlang_host_is_linux_impl();
}

int xlang_host_is_apple_aarch64(void) {
  return xlang_host_is_apple_aarch64_impl();
}

/* Pure audit: number of L2 host-lit thin gates in this slice. */
int labi_host_lit_count(void) {
  return 2;
}

#else
int xlang_host_is_linux(void);
int xlang_host_is_apple_aarch64(void);
int labi_host_lit_count(void);
#endif

int labi_host_lit_slice_marker(void) {
  return 1;
}
