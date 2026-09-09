/* seeds/simd_enc_thin.from_x.c
 * G-02f simd_enc R2 thin full surface (legacy name) — isomorphic with src/asm/simd_enc_thin.x
 * Product PREFER_X_O: g05_try_x_to_o(thin.x) + full seed rest (-DXLANG_L2_SIMD_ENC_THIN_FROM_X) ld -r
 * Cap residual: *_impl / encode C 尾 in seeds/simd_enc.from_x.c rest
 * Regen: ./xlang -E ... src/asm/simd_enc_thin.x | filter DBG + polish externs
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
extern uint32_t simd_arm64_ins_v1_from_v0_s(int32_t dst_lane, int32_t src_lane);
extern int32_t simd_arm64_rbp_lea_off_128half(int32_t slot, int32_t half, int32_t esz);
extern int32_t simd_rbp_disp32(int32_t slot_off, int32_t lanes, int32_t esz);
extern int32_t simd_append(uint8_t * elf_ctx, uint8_t * bytes, int32_t n);
extern int32_t simd_append_disp32(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_addps_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_paddd_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_psubd_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vpsubd_ymm0_ymm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vpaddd_ymm0_ymm1(uint8_t * elf_ctx);
extern int32_t simd_x86_mulps_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_pmulld_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vpmulld_ymm0_ymm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vfmadd231ps_xmm0_xmm1_xmm2(uint8_t * elf_ctx);
extern int32_t simd_x86_pxor_xmm3_xmm3(uint8_t * elf_ctx);
extern int32_t simd_x86_pcmpgtd_xmm2_xmm3(uint8_t * elf_ctx);
extern int32_t simd_x86_pand_xmm0_xmm2(uint8_t * elf_ctx);
extern int32_t simd_x86_pandn_xmm2_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_por_xmm0_xmm2(uint8_t * elf_ctx);
extern int32_t simd_x86_xorps_xmm3_xmm3(uint8_t * elf_ctx);
extern int32_t simd_x86_cmpgtps_xmm2_xmm3(uint8_t * elf_ctx);
extern int32_t simd_x86_andps_xmm0_xmm2(uint8_t * elf_ctx);
extern int32_t simd_x86_andnps_xmm2_xmm1(uint8_t * elf_ctx);
extern int32_t simd_x86_orps_xmm0_xmm2(uint8_t * elf_ctx);
extern int32_t simd_x86_vpxor_ymm3_ymm3(uint8_t * elf_ctx);
extern int32_t simd_x86_vpcmpgtd_ymm2_ymm3(uint8_t * elf_ctx);
extern int32_t simd_x86_vpand_ymm0_ymm2(uint8_t * elf_ctx);
extern int32_t simd_x86_vpandn_ymm2_ymm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vpor_ymm0_ymm2(uint8_t * elf_ctx);
extern int32_t simd_x86_vxorps_ymm3_ymm3(uint8_t * elf_ctx);
extern int32_t simd_x86_vcmpgtps_ymm2_ymm3(uint8_t * elf_ctx);
extern int32_t simd_x86_vandps_ymm0_ymm2(uint8_t * elf_ctx);
extern int32_t simd_x86_vandnps_ymm2_ymm1(uint8_t * elf_ctx);
extern int32_t simd_x86_vorps_ymm0_ymm2(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm0_from_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm1_from_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm0_to_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_from_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm1_from_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_to_rbx_rax4(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm1_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm0_to_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm0_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm1_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm0_to_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm2_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm2_from_rbp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_x86_xorps_xmm0_zero(uint8_t * elf_ctx);
extern int32_t simd_enc_x86_movups_xmm1_rbp_disp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_x86_addps_xmm0_xmm1(uint8_t * elf_ctx);
extern int32_t simd_enc_try_hw_vector_iadd_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_isub_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_append_u32_le(uint8_t * elf_ctx, uint32_t word);
extern int32_t simd_x86_pshufd_xmm0_imm8(uint8_t * elf_ctx, int32_t imm8);
extern int32_t simd_x86_vpshufd_ymm0_imm8(uint8_t * elf_ctx, int32_t imm8);
extern int32_t simd_enc_emit_i32_select_xmm_seq(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_f32_select_xmm_seq(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_i32_select_ymm_seq(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_f32_select_ymm_seq(uint8_t * elf_ctx);
extern int32_t simd_x86_pshufd_xmm1_xmm0(uint8_t * elf_ctx, uint8_t imm);
extern int32_t simd_enc_x86_horizontal_addps_xmm0(uint8_t * elf_ctx);
extern int32_t simd_enc_x86_movss_xmm0_rbp_disp(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_f32_soa_col_movups_xmm1_at_idx(uint8_t * elf_ctx, int32_t off_col0, int32_t off_i, int32_t ta);
extern int32_t simd_enc_try_hw_vector_iadd_isub_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features, int32_t is_sub);
extern int32_t simd_enc_try_hw_vector_imul_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fadd_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fmul_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fma_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_c, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_binop_rbp_at_idx(uint8_t * elf_ctx, int32_t off_a, int32_t off_b, int32_t off_d, int32_t off_i, int32_t array_n, int32_t binop_ko, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_arm64_pshufd_imm8_128_rbp(uint8_t * elf_ctx, int32_t lea_src, int32_t lea_dst, int32_t imm8, int32_t ta);
extern int32_t simd_arm64_select_128_rbp(uint8_t * elf_ctx, int32_t lea_mask, int32_t lea_a, int32_t lea_b, int32_t lea_dst, int32_t is_f32, int32_t ta);
extern int32_t simd_enc_try_pshufd_rbp(uint8_t * elf_ctx, int32_t slot_off_src, int32_t slot_off_dst, int32_t imm8, int32_t lanes, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_select_rbp(uint8_t * elf_ctx, int32_t slot_off_mask, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t is_f32, int32_t ta, uint32_t cpu_features);
uint32_t simd_arm64_ins_v1_from_v0_s(int32_t dst_lane, int32_t src_lane) {
  int32_t d = (dst_lane & 3);
  int32_t s = (src_lane & 3);
  int32_t enc = (((1846018048 | (d <<19)) | (s <<13)) | 1025);
  return enc;
}
int32_t simd_arm64_rbp_lea_off_128half(int32_t slot, int32_t half, int32_t esz) {
  if ((slot < 0)) {
    return slot;
  }
  if ((esz <=0)) {
    return slot;
  }
  if ((half < 0)) {
    return slot;
  }
  /* PLATFORM: MACOS|ARM64 low-end home; half1 = slot+16. */
  return (slot + ((half * 4) * esz));
}
int32_t simd_rbp_disp32(int32_t slot_off, int32_t lanes, int32_t esz) {
  if ((slot_off < 0)) {
    return 0;
  }
  return (0 - slot_off);
}
extern int32_t simd_append_impl(uint8_t * elf_ctx, uint8_t * bytes, int32_t n);
extern int32_t simd_append_disp32_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_addps_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_paddd_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_psubd_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpsubd_ymm0_ymm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpaddd_ymm0_ymm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_mulps_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pmulld_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpmulld_ymm0_ymm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vfmadd231ps_xmm0_xmm1_xmm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pxor_xmm3_xmm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pcmpgtd_xmm2_xmm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pand_xmm0_xmm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pandn_xmm2_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_por_xmm0_xmm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_xorps_xmm3_xmm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_cmpgtps_xmm2_xmm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_andps_xmm0_xmm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_andnps_xmm2_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_orps_xmm0_xmm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpxor_ymm3_ymm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpcmpgtd_ymm2_ymm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpand_ymm0_ymm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpandn_ymm2_ymm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vpor_ymm0_ymm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vxorps_ymm3_ymm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vcmpgtps_ymm2_ymm3_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vandps_ymm0_ymm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vandnps_ymm2_ymm1_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vorps_ymm0_ymm2_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm0_from_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm1_from_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_vmovups_ymm0_to_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_from_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm1_from_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_to_rbx_rax4_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_movups_xmm0_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm1_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm0_to_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm0_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm1_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm0_to_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_movups_xmm2_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_x86_vmovups_ymm2_from_rbp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_x86_xorps_xmm0_zero_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_x86_movups_xmm1_rbp_disp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_x86_addps_xmm0_xmm1_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_try_hw_vector_iadd_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_isub_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_append_u32_le_impl(uint8_t * elf_ctx, uint32_t word);
extern int32_t simd_x86_pshufd_xmm0_imm8_impl(uint8_t * elf_ctx, int32_t imm8);
extern int32_t simd_x86_vpshufd_ymm0_imm8_impl(uint8_t * elf_ctx, int32_t imm8);
int32_t simd_append(uint8_t * elf_ctx, uint8_t * bytes, int32_t n) {
  {
    return simd_append_impl(elf_ctx, bytes, n);
  }
  return (0 - 1);
}
int32_t simd_append_disp32(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_append_disp32_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_addps_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_addps_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_paddd_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_paddd_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_psubd_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_psubd_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpsubd_ymm0_ymm1(uint8_t * elf_ctx) {
  {
    return simd_x86_vpsubd_ymm0_ymm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpaddd_ymm0_ymm1(uint8_t * elf_ctx) {
  {
    return simd_x86_vpaddd_ymm0_ymm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_mulps_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_mulps_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pmulld_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_pmulld_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpmulld_ymm0_ymm1(uint8_t * elf_ctx) {
  {
    return simd_x86_vpmulld_ymm0_ymm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vfmadd231ps_xmm0_xmm1_xmm2(uint8_t * elf_ctx) {
  {
    return simd_x86_vfmadd231ps_xmm0_xmm1_xmm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pxor_xmm3_xmm3(uint8_t * elf_ctx) {
  {
    return simd_x86_pxor_xmm3_xmm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pcmpgtd_xmm2_xmm3(uint8_t * elf_ctx) {
  {
    return simd_x86_pcmpgtd_xmm2_xmm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pand_xmm0_xmm2(uint8_t * elf_ctx) {
  {
    return simd_x86_pand_xmm0_xmm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pandn_xmm2_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_pandn_xmm2_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_por_xmm0_xmm2(uint8_t * elf_ctx) {
  {
    return simd_x86_por_xmm0_xmm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_xorps_xmm3_xmm3(uint8_t * elf_ctx) {
  {
    return simd_x86_xorps_xmm3_xmm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_cmpgtps_xmm2_xmm3(uint8_t * elf_ctx) {
  {
    return simd_x86_cmpgtps_xmm2_xmm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_andps_xmm0_xmm2(uint8_t * elf_ctx) {
  {
    return simd_x86_andps_xmm0_xmm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_andnps_xmm2_xmm1(uint8_t * elf_ctx) {
  {
    return simd_x86_andnps_xmm2_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_orps_xmm0_xmm2(uint8_t * elf_ctx) {
  {
    return simd_x86_orps_xmm0_xmm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpxor_ymm3_ymm3(uint8_t * elf_ctx) {
  {
    return simd_x86_vpxor_ymm3_ymm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpcmpgtd_ymm2_ymm3(uint8_t * elf_ctx) {
  {
    return simd_x86_vpcmpgtd_ymm2_ymm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpand_ymm0_ymm2(uint8_t * elf_ctx) {
  {
    return simd_x86_vpand_ymm0_ymm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpandn_ymm2_ymm1(uint8_t * elf_ctx) {
  {
    return simd_x86_vpandn_ymm2_ymm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vpor_ymm0_ymm2(uint8_t * elf_ctx) {
  {
    return simd_x86_vpor_ymm0_ymm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vxorps_ymm3_ymm3(uint8_t * elf_ctx) {
  {
    return simd_x86_vxorps_ymm3_ymm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vcmpgtps_ymm2_ymm3(uint8_t * elf_ctx) {
  {
    return simd_x86_vcmpgtps_ymm2_ymm3_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vandps_ymm0_ymm2(uint8_t * elf_ctx) {
  {
    return simd_x86_vandps_ymm0_ymm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vandnps_ymm2_ymm1(uint8_t * elf_ctx) {
  {
    return simd_x86_vandnps_ymm2_ymm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vorps_ymm0_ymm2(uint8_t * elf_ctx) {
  {
    return simd_x86_vorps_ymm0_ymm2_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm0_from_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_vmovups_ymm0_from_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm1_from_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_vmovups_ymm1_from_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm0_to_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_vmovups_ymm0_to_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm0_from_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_movups_xmm0_from_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm1_from_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_movups_xmm1_from_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm0_to_rbx_rax4(uint8_t * elf_ctx) {
  {
    return simd_x86_movups_xmm0_to_rbx_rax4_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm0_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_movups_xmm0_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm1_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_movups_xmm1_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm0_to_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_movups_xmm0_to_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm0_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_vmovups_ymm0_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm1_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_vmovups_ymm1_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm0_to_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_vmovups_ymm0_to_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_movups_xmm2_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_movups_xmm2_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_x86_vmovups_ymm2_from_rbp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_x86_vmovups_ymm2_from_rbp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_enc_x86_xorps_xmm0_zero(uint8_t * elf_ctx) {
  {
    return simd_enc_x86_xorps_xmm0_zero_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_x86_movups_xmm1_rbp_disp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_enc_x86_movups_xmm1_rbp_disp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_enc_x86_addps_xmm0_xmm1(uint8_t * elf_ctx) {
  {
    return simd_enc_x86_addps_xmm0_xmm1_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_iadd_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_iadd_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_isub_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_isub_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_append_u32_le(uint8_t * elf_ctx, uint32_t word) {
  {
    return simd_append_u32_le_impl(elf_ctx, word);
  }
  return (0 - 1);
}
int32_t simd_x86_pshufd_xmm0_imm8(uint8_t * elf_ctx, int32_t imm8) {
  {
    return simd_x86_pshufd_xmm0_imm8_impl(elf_ctx, imm8);
  }
  return (0 - 1);
}
int32_t simd_x86_vpshufd_ymm0_imm8(uint8_t * elf_ctx, int32_t imm8) {
  {
    return simd_x86_vpshufd_ymm0_imm8_impl(elf_ctx, imm8);
  }
  return (0 - 1);
}
extern int32_t simd_enc_emit_i32_select_xmm_seq_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_f32_select_xmm_seq_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_i32_select_ymm_seq_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_emit_f32_select_ymm_seq_impl(uint8_t * elf_ctx);
extern int32_t simd_x86_pshufd_xmm1_xmm0_impl(uint8_t * elf_ctx, uint8_t imm);
extern int32_t simd_enc_x86_horizontal_addps_xmm0_impl(uint8_t * elf_ctx);
extern int32_t simd_enc_x86_movss_xmm0_rbp_disp_impl(uint8_t * elf_ctx, int32_t disp);
extern int32_t simd_enc_f32_soa_col_movups_xmm1_at_idx_impl(uint8_t * elf_ctx, int32_t off_col0, int32_t off_i, int32_t ta);
int32_t simd_enc_emit_i32_select_xmm_seq(uint8_t * elf_ctx) {
  {
    return simd_enc_emit_i32_select_xmm_seq_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_emit_f32_select_xmm_seq(uint8_t * elf_ctx) {
  {
    return simd_enc_emit_f32_select_xmm_seq_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_emit_i32_select_ymm_seq(uint8_t * elf_ctx) {
  {
    return simd_enc_emit_i32_select_ymm_seq_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_emit_f32_select_ymm_seq(uint8_t * elf_ctx) {
  {
    return simd_enc_emit_f32_select_ymm_seq_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_x86_pshufd_xmm1_xmm0(uint8_t * elf_ctx, uint8_t imm) {
  {
    return simd_x86_pshufd_xmm1_xmm0_impl(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t simd_enc_x86_horizontal_addps_xmm0(uint8_t * elf_ctx) {
  {
    return simd_enc_x86_horizontal_addps_xmm0_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t simd_enc_x86_movss_xmm0_rbp_disp(uint8_t * elf_ctx, int32_t disp) {
  {
    return simd_enc_x86_movss_xmm0_rbp_disp_impl(elf_ctx, disp);
  }
  return (0 - 1);
}
int32_t simd_enc_f32_soa_col_movups_xmm1_at_idx(uint8_t * elf_ctx, int32_t off_col0, int32_t off_i, int32_t ta) {
  {
    return simd_enc_f32_soa_col_movups_xmm1_at_idx_impl(elf_ctx, off_col0, off_i, ta);
  }
  return (0 - 1);
}
extern int32_t simd_enc_try_hw_vector_iadd_isub_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features, int32_t is_sub);
extern int32_t simd_enc_try_hw_vector_imul_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fadd_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fmul_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_fma_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_c, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_binop_rbp_at_idx_impl(uint8_t * elf_ctx, int32_t off_a, int32_t off_b, int32_t off_d, int32_t off_i, int32_t array_n, int32_t binop_ko, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features);
extern int32_t simd_arm64_pshufd_imm8_128_rbp_impl(uint8_t * elf_ctx, int32_t lea_src, int32_t lea_dst, int32_t imm8, int32_t ta);
extern int32_t simd_arm64_select_128_rbp_impl(uint8_t * elf_ctx, int32_t lea_mask, int32_t lea_a, int32_t lea_b, int32_t lea_dst, int32_t is_f32, int32_t ta);
extern int32_t simd_enc_try_pshufd_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_src, int32_t slot_off_dst, int32_t imm8, int32_t lanes, int32_t ta, uint32_t cpu_features);
extern int32_t simd_enc_try_hw_vector_select_rbp_impl(uint8_t * elf_ctx, int32_t slot_off_mask, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t is_f32, int32_t ta, uint32_t cpu_features);
int32_t simd_enc_try_hw_vector_iadd_isub_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features, int32_t is_sub) {
  {
    return simd_enc_try_hw_vector_iadd_isub_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features, is_sub);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_imul_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_imul_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_fadd_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_fadd_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_fmul_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_fmul_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_fma_rbp(uint8_t * elf_ctx, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_c, int32_t slot_off_dst, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_fma_rbp_impl(elf_ctx, slot_off_a, slot_off_b, slot_off_c, slot_off_dst, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_binop_rbp_at_idx(uint8_t * elf_ctx, int32_t off_a, int32_t off_b, int32_t off_d, int32_t off_i, int32_t array_n, int32_t binop_ko, int32_t lanes, int32_t esz, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_binop_rbp_at_idx_impl(elf_ctx, off_a, off_b, off_d, off_i, array_n, binop_ko, lanes, esz, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_arm64_pshufd_imm8_128_rbp(uint8_t * elf_ctx, int32_t lea_src, int32_t lea_dst, int32_t imm8, int32_t ta) {
  {
    return simd_arm64_pshufd_imm8_128_rbp_impl(elf_ctx, lea_src, lea_dst, imm8, ta);
  }
  return (0 - 1);
}
int32_t simd_arm64_select_128_rbp(uint8_t * elf_ctx, int32_t lea_mask, int32_t lea_a, int32_t lea_b, int32_t lea_dst, int32_t is_f32, int32_t ta) {
  {
    return simd_arm64_select_128_rbp_impl(elf_ctx, lea_mask, lea_a, lea_b, lea_dst, is_f32, ta);
  }
  return (0 - 1);
}
int32_t simd_enc_try_pshufd_rbp(uint8_t * elf_ctx, int32_t slot_off_src, int32_t slot_off_dst, int32_t imm8, int32_t lanes, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_pshufd_rbp_impl(elf_ctx, slot_off_src, slot_off_dst, imm8, lanes, ta, cpu_features);
  }
  return (0 - 1);
}
int32_t simd_enc_try_hw_vector_select_rbp(uint8_t * elf_ctx, int32_t slot_off_mask, int32_t slot_off_a, int32_t slot_off_b, int32_t slot_off_dst, int32_t lanes, int32_t is_f32, int32_t ta, uint32_t cpu_features) {
  {
    return simd_enc_try_hw_vector_select_rbp_impl(elf_ctx, slot_off_mask, slot_off_a, slot_off_b, slot_off_dst, lanes, is_f32, ta, cpu_features);
  }
  return (0 - 1);
}
