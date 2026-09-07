/**
 * target_cpu.h — SIMD-S1：目标 CPU feature 探测与 `-target-cpu` 解析。
 *
 * 供 driver/runtime 在编译期解析 `-target-cpu`（native/generic/具名特性），
 * 并将结果写入 PipelineDepCtx.target_cpu_features 供后续 SIMD pass 使用。
 */
#ifndef XLANG_TARGET_CPU_H
#define XLANG_TARGET_CPU_H

#include <stdint.h>
#include <stddef.h>

/** x86/x86_64 特性位（与 arm/riscv 分段，避免混用）。 */
#define XLANG_CPU_FEAT_SSE2     (1u << 0)
#define XLANG_CPU_FEAT_SSE41    (1u << 1)
#define XLANG_CPU_FEAT_AVX      (1u << 2)
#define XLANG_CPU_FEAT_AVX2     (1u << 3)
#define XLANG_CPU_FEAT_AVX512F  (1u << 4)
#define XLANG_CPU_FEAT_POPCNT   (1u << 5)
#define XLANG_CPU_FEAT_BMI2     (1u << 6)
/** x86 FMA3（vfmadd213ps / vfmadd231ps 等）。 */
#define XLANG_CPU_FEAT_FMA      (1u << 7)
/** AArch64：NEON（asimd）为 baseline；SVE 为可选扩展。 */
#define XLANG_CPU_FEAT_NEON     (1u << 8)
#define XLANG_CPU_FEAT_SVE      (1u << 9)
/** RISC-V：向量扩展（探测到 rv64 含 'v' 时置位）。 */
#define XLANG_CPU_FEAT_RVV      (1u << 16)

/**
 * 探测当前宿主机 CPU 特性（Linux /proc/cpuinfo、macOS sysctl、编译期宏兜底）。
 * 返回 feature 位掩码；探测失败时返回 0。
 */
uint32_t xlang_target_cpu_detect_host(void);

/**
 * 当前宿主架构下的 generic baseline（x86_64→SSE2，arm64→NEON，riscv64→0）。
 */
uint32_t xlang_target_cpu_generic_for_host(void);

/**
 * 解析 `-target-cpu` 规格字符串。
 * @param spec     如 "native"、"generic"、"avx2"、"x86-64-v3"（可为 NULL 表示 native）
 * @param spec_len 字节长度；0 表示 native
 * @param out      输出 feature 掩码
 * @return 0 成功，-1 未知规格
 */
int xlang_target_cpu_resolve(const char *spec, size_t spec_len, uint32_t *out);

/**
 * Print the feature mask as stable key=value lines (for `--print-target-cpu`
 * and gate greps).
 * @param out Opaque stdout handle (*u8, e.g. from driver_stdio_stdout());
 *            kept for face parity with the .x authority `out: *u8` — the
 *            Cap implementation always writes through raw fd 1 and ignores
 *            the handle value (NULL allowed).
 * Cap residual 9.7.2: face unified with .x authority — no libc FILE*.
 * PLATFORM: SHARED (LINUX | DARWIN | WINDOWS) — Cap io write, fd 1.
 */
void xlang_target_cpu_print(uint8_t *out, uint32_t features);

/** driver 分派前暂存已解析 feature（lib_key→state 不可直传 pctx 时用）。 */
void driver_set_pending_target_cpu_features(uint32_t features);

/** 读取 driver_set_pending_target_cpu_features 写入的值。 */
uint32_t driver_get_pending_target_cpu_features(void);

/**
 * SIMD-S2：判断 TYPE_NAMED 拼写是否为标准向量类型（i32x4、Vec4f、Vec8i 等）。
 * @return 1 是向量拼写，0 否
 */
int xlang_simd_is_vector_type_spelling(const char *name, size_t name_len);

/**
 * SIMD-S2：从向量类型拼写推断 lane 数与元素字节宽。
 * @return 0 成功，-1 非向量拼写
 */
int xlang_simd_vector_lanes_esz_from_spelling(const char *name, size_t name_len, int32_t *out_lanes,
                                            int32_t *out_esz);

#endif /* XLANG_TARGET_CPU_H */
