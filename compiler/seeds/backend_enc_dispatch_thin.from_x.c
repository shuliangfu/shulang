/* seeds/backend_enc_dispatch_thin.from_x.c
 * G-02f backend_enc_dispatch R2 thin full surface (legacy name) — isomorphic with src/asm/backend_enc_dispatch_thin.x
 * Product PREFER_X_O: g05_try_x_to_o(thin.x) + full seed rest (-DXLANG_L2_ENC_DISPATCH_THIN_FROM_X) ld -r
 * Cap residual: *_impl / enc C 尾 in seeds/backend_enc_dispatch.from_x.c rest
 * Regen: ./xlang -E ... src/asm/backend_enc_dispatch_thin.x | filter DBG + polish externs
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
extern int32_t backend_enc_arm64_add_sp_imm12_c(uint8_t * elf_ctx, int32_t imm);
extern int32_t backend_enc_arm64_sub_sp_imm12_c(uint8_t * elf_ctx, int32_t imm);
extern int32_t backend_enc_arm64_str_x0_sp_offset_c(uint8_t * elf_ctx, int32_t off_bytes);
extern int32_t arm64_enc_load_w0_from_rbp_c(uint8_t * elf_ctx, int32_t offset);
extern int32_t arm64_enc_load_w1_from_rbp_c(uint8_t * elf_ctx, int32_t offset);
extern int32_t arm64_enc_store_w0_to_rbp_c(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_arm64_enc_enc_add_sp_imm12(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_arm64_enc_enc_sub_sp_imm12(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_arm64_enc_enc_str_x0_sp_offset(uint8_t * elf_ctx, int32_t off_bytes);
extern int32_t arch_arm64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k);
extern int32_t backend_enc_push_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_push_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_pop_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_pop_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_epilogue_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_add_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_sub_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_imul_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_rax_to_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_not_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_and_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_or_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_xor_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_rbx_to_ecx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cltd_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_neg_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_test_eax_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_test_rbx_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_shl_cl_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_shr_cl_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_sar_cl_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_edx_to_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_setz_movzbl_eax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cmp_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_sub_rbx_rax_then_mov_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_shl_cl_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_shr_cl_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_sar_cl_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cmp_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_idiv_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_div_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_prologue_arch(uint8_t * elf_ctx, int32_t frame_sz, int32_t ta);
extern int32_t backend_enc_ret_imm32_arch(uint8_t * elf_ctx, int32_t imm32, int32_t ta);
extern int32_t backend_enc_mov_imm32_to_rbx_arch(uint8_t * elf_ctx, int32_t imm32, int32_t ta);
extern int32_t backend_enc_mov_imm64_to_rax_arch(uint8_t * elf_ctx, int32_t lo, int32_t hi, int32_t ta);
extern int32_t backend_enc_cmp_setcc_movzbl_arch(uint8_t * elf_ctx, int32_t cc, int32_t ta);
extern int32_t backend_enc_store_rax_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_load_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_lea_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_lea_rbp_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_rax_plus_rbx_scale1_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rax_plus_rbx_scale4_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rax_plus_rbx_scale8_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_load_zext8_from_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_add_imm_to_rax_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_add_imm_to_rbx_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_label_arch(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func, int32_t ta);
extern int32_t backend_enc_store_rax_to_rbx_indirect_arch(uint8_t * elf_ctx, int32_t elem_sz, int32_t ta);
extern int32_t backend_enc_load_32_from_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_load_i32_indirect_to_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_load_rbp_index_scratch_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_load_64_from_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_store_rax_to_rbx_offset_arch(uint8_t * elf_ctx, int32_t offset, int32_t store_size, int32_t ta);
extern int32_t backend_enc_mov_rbx_to_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_jz_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jeq_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jge_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jnz_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jne_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jmp_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_mov_rax_to_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta);
extern int32_t backend_enc_rem_mod_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rem_mod_unsigned_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_call_stack_cleanup_arch(uint8_t * elf_ctx, int32_t nbytes, int32_t ta);
extern int32_t backend_enc_call_stack_reserve_arch(uint8_t * elf_ctx, int32_t nbytes, int32_t ta);
extern int32_t backend_enc_store_x0_sp_offset_arch(uint8_t * elf_ctx, int32_t off_bytes, int32_t ta);
extern int32_t backend_enc_store_x_reg_to_rbp_arch(uint8_t * elf_ctx, int32_t reg, int32_t offset, int32_t ta);
extern int32_t backend_enc_load_qword_from_rbx_to_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_load_qword_rbx8_to_rdx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_store_rdx_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_index_scratch_add_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_index_scratch_sub_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_index_scratch_rsub_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rbx_index_rsub_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rbx_index_add_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rbx_index_sub_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_index_scratch_mul_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_rbx_index_mul_secondary_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_call_arch(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t ta);
extern int32_t backend_enc_load_rbp_to_rdx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_mov_rdx_to_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta);
extern int32_t backend_enc_mov_arg_reg_to_rax_arch(uint8_t * elf_ctx, int32_t k, int32_t ta);
extern int32_t backend_enc_load_rbp_pos_to_rax_arch(uint8_t * elf_ctx, int32_t off_pos, int32_t ta);
extern int32_t backend_enc_rbx_plus_index_scratch_scaled_arch(uint8_t * elf_ctx, int32_t esz, int32_t ta);
extern int32_t backend_enc_load_rbp_lane_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t esz, int32_t ta);
extern int32_t backend_enc_jle_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_jl_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_enc_load_x29_pos_to_rax_arch(uint8_t * elf_ctx, int32_t off_pos, int32_t ta);
extern int32_t backend_enc_add_imm_to_index_scratch_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_load_rbp_index_secondary_scratch_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_sub_imm_from_index_scratch_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_mul_imm_to_index_scratch_arch(uint8_t * elf_ctx, int32_t lit, int32_t ta);
extern int32_t backend_enc_mul_imm_to_rbx_arch(uint8_t * elf_ctx, int32_t lit, int32_t ta);
extern int32_t backend_enc_add_imm_to_rbx_index_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_sub_imm_from_rbx_index_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta);
extern int32_t backend_enc_load_rbp_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_load_rbp_lane_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t esz, int32_t ta);
extern int32_t backend_enc_addss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_mulss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_subss_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_subss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_divss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvttss2si_eax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvttsd2si_eax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvttss2si_rax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvttsd2si_rax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsd2ss_eax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2ss_eax_from_i32_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2ss_eax_from_i64_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2sd_rax_from_i32_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2sd_rax_from_i64_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2sd_rax_from_u64_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtsi2ss_eax_from_u64_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_cvtss2sd_rax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta);
extern int32_t backend_enc_mov_eax_to_xmm_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta);
extern int32_t backend_enc_mov_xmm_arg_reg_to_eax_arch(uint8_t * elf_ctx, int32_t k, int32_t ta);
extern int32_t backend_enc_store_eax_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta);
extern int32_t backend_enc_append_u32_le_c(uint8_t * elf_ctx, uint32_t word);
extern int32_t backend_enc_append_u8_c(uint8_t * elf_ctx, int32_t byte);
extern int32_t backend_enc_arm64_call_c(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t backend_enc_x86_jcc_rel32_c(uint8_t * elf_ctx, int32_t opcode2, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_cdqe_rax(uint8_t * elf_ctx);
extern int32_t backend_enc_append_u32_le_c_impl(uint8_t * elf_ctx, uint32_t word);
extern int32_t backend_enc_append_u8_c_impl(uint8_t * elf_ctx, int32_t byte);
extern int32_t arch_arm64_enc_enc_u32_le(uint8_t * elf_ctx, int32_t val);
extern int32_t backend_enc_arm64_call_c_impl(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_enc_enc_call_impl(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_enc_enc_mov_rax_to_arg_reg_impl(uint8_t * elf_ctx, int32_t k);
int32_t backend_enc_arm64_add_sp_imm12_c(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((imm <=0)) {
    return 0;
  }
  if ((imm > 4095)) {
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-1862269953 | (4095 * 1024)));
    }
    return (0 - 1);
  }
  {
    return backend_enc_append_u32_le_c_impl(elf_ctx, (-1862269953 | (((uint32_t)(imm)) * 1024)));
  }
  return (0 - 1);
}
int32_t backend_enc_arm64_sub_sp_imm12_c(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((imm <=0)) {
    return 0;
  }
  if ((imm > 4095)) {
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-788528129 | (4095 * 1024)));
    }
    return (0 - 1);
  }
  {
    return backend_enc_append_u32_le_c_impl(elf_ctx, (-788528129 | (((uint32_t)(imm)) * 1024)));
  }
  return (0 - 1);
}
int32_t backend_enc_arm64_str_x0_sp_offset_c(uint8_t * elf_ctx, int32_t off_bytes) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((off_bytes < 0)) {
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, -117439520);
    }
    return (0 - 1);
  }
  if (((off_bytes / 8) > 4095)) {
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-117439520 | (4095 * 1024)));
    }
    return (0 - 1);
  }
  {
    return backend_enc_append_u32_le_c_impl(elf_ctx, (-117439520 | (((uint32_t)((off_bytes / 8))) * 1024)));
  }
  return (0 - 1);
}
/* PLATFORM: MACOS|ARM64 — product-positive LDRSW x0,[x29,#off].
 * Twin of backend_enc_dispatch_thin.x (was LDUR w0,[x29,#-off]). */
int32_t arm64_enc_load_w0_from_rbp_c(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((offset < 0)) {
    return (0 - 1);
  }
  if (((offset % 4) != 0)) {
    return (0 - 1);
  }
  if (((offset / 4) > 4095)) {
    return (0 - 1);
  }
  {
    int32_t imm12 = (offset / 4);
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((3112173568 | (imm12 * 1024)) | 928)));
  }
  return (0 - 1);
}
/* PLATFORM: MACOS|ARM64 — LDRSW x1,[x29,#off] (Rt=1). */
int32_t arm64_enc_load_w1_from_rbp_c(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((offset < 0)) {
    return (0 - 1);
  }
  if (((offset % 4) != 0)) {
    return (0 - 1);
  }
  if (((offset / 4) > 4095)) {
    return (0 - 1);
  }
  {
    int32_t imm12 = (offset / 4);
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((3112173568 | (imm12 * 1024)) | 928) | 1)));
  }
  return (0 - 1);
}
int32_t arm64_enc_store_w0_to_rbp_c(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((offset < 0)) {
    return (0 - 1);
  }
  if ((offset > 256)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((-1207959552 | (256 * 4096)) | 928))));
    }
    return (0 - 1);
  }
  {
    int32_t u9 = ((0 - offset) & 511);
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((-1207959552 | (((uint32_t)(u9)) * 4096)) | 928))));
  }
  return (0 - 1);
}
int32_t arch_arm64_enc_enc_add_sp_imm12(uint8_t * elf_ctx, int32_t imm) {
  return backend_enc_arm64_add_sp_imm12_c(elf_ctx, imm);
}
int32_t arch_arm64_enc_enc_sub_sp_imm12(uint8_t * elf_ctx, int32_t imm) {
  return backend_enc_arm64_sub_sp_imm12_c(elf_ctx, imm);
}
int32_t arch_arm64_enc_enc_str_x0_sp_offset(uint8_t * elf_ctx, int32_t off_bytes) {
  return backend_enc_arm64_str_x0_sp_offset_c(elf_ctx, off_bytes);
}
int32_t arch_arm64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len) {
  {
    return backend_enc_arm64_call_c_impl(elf_ctx, name, name_len);
  }
  return (0 - 1);
}
int32_t arch_riscv64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len) {
  {
    return arch_riscv64_enc_enc_call_impl(elf_ctx, name, name_len);
  }
  return (0 - 1);
}
int32_t arch_riscv64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k) {
  {
    return arch_riscv64_enc_enc_mov_rax_to_arg_reg_impl(elf_ctx, k);
  }
  return (0 - 1);
}
extern int32_t arch_arm64_enc_enc_push_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_push_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_push_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_push_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_push_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_push_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_pop_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_pop_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_pop_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_pop_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_pop_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_pop_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_epilogue(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_epilogue(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_epilogue(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_add_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_add_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_sub_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_imul_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_imul_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_rbx_rax(uint8_t * elf_ctx);
int32_t backend_enc_push_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_push_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_push_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_push_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_push_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_push_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_push_rbx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_push_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_pop_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_pop_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_pop_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_pop_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_pop_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_pop_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_pop_rbx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_pop_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_epilogue_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_epilogue(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_epilogue(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_epilogue(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_add_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_add_rax_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_rax_rbx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_add_rax_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_sub_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_sub_rax_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_sub_rax_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_imul_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_imul_rbx_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_imul_rbx_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_imul_rbx_rax(elf_ctx);
  }
  return (0 - 1);
}
extern int32_t arch_arm64_enc_enc_mov_rax_to_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mov_rax_to_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_not_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_not_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_not_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_and_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_and_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_and_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_or_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_or_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_or_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_xor_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_xor_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_xor_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_rbx_to_ecx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mov_rbx_to_ecx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_cltd(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_cltd(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cltd(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_neg_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_neg_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_neg_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_test_eax_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_test_eax_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_test_eax_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_test_rbx_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_test_rbx_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_test_rbx_rbx(uint8_t * elf_ctx);
int32_t backend_enc_mov_rax_to_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_rax_to_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_rax_to_rbx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_rax_to_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_not_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_not_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_not_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_not_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_and_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_and_rbx_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_and_rbx_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_and_rbx_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_or_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_or_rbx_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_or_rbx_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_or_rbx_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_xor_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_xor_rbx_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_xor_rbx_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_xor_rbx_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_rbx_to_ecx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_rbx_to_ecx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_rbx_to_ecx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_rbx_to_ecx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_cltd_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_cltd(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_cltd(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_cltd(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_neg_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_neg_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_neg_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_neg_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_test_eax_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_test_eax_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_test_eax_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_test_eax_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_test_rbx_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_test_rbx_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_test_rbx_rbx(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_test_rbx_rbx(elf_ctx);
  }
  return (0 - 1);
}
extern int32_t arch_arm64_enc_enc_cmp_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_cmp_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_idiv_rbx(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_edx_to_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_sar_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_setz_movzbl_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_shl_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_shr_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_sub_rbx_rax_then_mov(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_cmp_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_idiv_rbx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mov_edx_to_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_sar_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_setz_movzbl_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_shl_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_shr_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_sub_rbx_rax_then_mov(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cmp_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cmp_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_div_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_idiv_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_edx_to_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sar_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sar_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_setz_movzbl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shl_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shl_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shr_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shr_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_xor_edx_edx(uint8_t * elf_ctx);
int32_t backend_enc_shl_cl_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_shl_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_shl_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_shl_cl_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_shr_cl_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_shr_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_shr_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_shr_cl_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_sar_cl_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_sar_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sar_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_sar_cl_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_edx_to_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_setz_movzbl_eax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_setz_movzbl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_setz_movzbl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_setz_movzbl_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_cmp_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_cmp_rbx_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_cmp_rbx_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_cmp_rbx_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_sub_rbx_rax_then_mov_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_shl_cl_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_shl_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_shl_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_shl_cl_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_shr_cl_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_shr_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_shr_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_shr_cl_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_sar_cl_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_sar_cl_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sar_cl_eax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_sar_cl_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_cmp_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_cmp_rax_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_cmp_rax_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_idiv_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_idiv_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_idiv_rbx(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_cltd(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_idiv_rbx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_div_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_idiv_rbx(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_idiv_rbx(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_xor_edx_edx(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_div_rbx(elf_ctx);
  }
  return (0 - 1);
}
extern int32_t arch_arm64_enc_enc_add_imm_to_rax(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_arm64_enc_enc_add_imm_to_rbx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_arm64_enc_enc_cmp_setcc_movzbl(uint8_t * elf_ctx, int32_t cc);
extern int32_t arch_arm64_enc_enc_label(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func);
extern int32_t arch_arm64_enc_enc_lea_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_arm64_enc_enc_lea_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_arm64_enc_enc_load_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_arm64_enc_enc_load_zext8_from_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_mov_imm32_to_rbx(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_arm64_enc_enc_mov_imm64_to_rax(uint8_t * elf_ctx, int32_t lo, int32_t hi);
extern int32_t arch_arm64_enc_enc_prologue(uint8_t * elf_ctx, int32_t frame_sz);
extern int32_t arch_arm64_enc_enc_rax_plus_rbx_scale1(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_rax_plus_rbx_scale4(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_rax_plus_rbx_scale8(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_ret_imm32(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_arm64_enc_enc_store_rax_to_rbp(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_add_imm_to_rax(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_riscv64_enc_enc_add_imm_to_rbx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_riscv64_enc_enc_cmp_setcc_movzbl(uint8_t * elf_ctx, int32_t cc);
extern int32_t arch_riscv64_enc_enc_label(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func);
extern int32_t arch_riscv64_enc_enc_lea_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_lea_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_load_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_load_zext8_from_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mov_imm32_to_rbx(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_riscv64_enc_enc_mov_imm64_to_rax(uint8_t * elf_ctx, int32_t lo, int32_t hi);
extern int32_t arch_riscv64_enc_enc_prologue(uint8_t * elf_ctx, int32_t frame_sz);
extern int32_t arch_riscv64_enc_enc_rax_plus_rbx_scale1(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rax_plus_rbx_scale4(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rax_plus_rbx_scale8(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_ret_imm32(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_riscv64_enc_enc_store_rax_to_rbp(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_add_imm_to_rax(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_add_imm_to_rbx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(uint8_t * elf_ctx, int32_t cc);
extern int32_t arch_x86_64_enc_enc_label(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func);
extern int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_lea_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_zext8_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(uint8_t * elf_ctx, int32_t lo, int32_t hi);
extern int32_t arch_x86_64_enc_enc_prologue(uint8_t * elf_ctx, int32_t frame_sz);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale1(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale8(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_ret_imm32(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbp(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_store_r64_to_rbp(uint8_t * elf_ctx, int32_t reg, int32_t offset);
int32_t backend_enc_prologue_arch(uint8_t * elf_ctx, int32_t frame_sz, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_prologue(elf_ctx, frame_sz);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_prologue(elf_ctx, frame_sz);
    }
  }
  {
    return arch_x86_64_enc_enc_prologue(elf_ctx, frame_sz);
  }
  return (0 - 1);
}
int32_t backend_enc_ret_imm32_arch(uint8_t * elf_ctx, int32_t imm32, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_ret_imm32(elf_ctx, imm32);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_ret_imm32(elf_ctx, imm32);
    }
  }
  {
    return arch_x86_64_enc_enc_ret_imm32(elf_ctx, imm32);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_imm32_to_rbx_arch(uint8_t * elf_ctx, int32_t imm32, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_imm64_to_rax_arch(uint8_t * elf_ctx, int32_t lo, int32_t hi, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
  }
  return (0 - 1);
}
int32_t backend_enc_cmp_setcc_movzbl_arch(uint8_t * elf_ctx, int32_t cc, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
    }
  }
  {
    return arch_x86_64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
  }
  return (0 - 1);
}
int32_t backend_enc_store_rax_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_lea_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_lea_rbp_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_rax_plus_rbx_scale1_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_rax_plus_rbx_scale1(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rax_plus_rbx_scale1(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_rax_plus_rbx_scale1(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rax_plus_rbx_scale4_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rax_plus_rbx_scale8_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_rax_plus_rbx_scale8(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rax_plus_rbx_scale8(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_rax_plus_rbx_scale8(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_load_zext8_from_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_zext8_from_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_zext8_from_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_load_zext8_from_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_add_imm_to_rax_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_add_imm_to_rax(elf_ctx, imm);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_imm_to_rax(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_add_imm_to_rax(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_add_imm_to_rbx_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_add_imm_to_rbx(elf_ctx, imm);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_imm_to_rbx(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_add_imm_to_rbx(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_label_arch(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_label(elf_ctx, name, name_len, is_func);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_label(elf_ctx, name, name_len, is_func);
    }
  }
  {
    return arch_x86_64_enc_enc_label(elf_ctx, name, name_len, is_func);
  }
  return (0 - 1);
}
extern int32_t arch_arm64_enc_enc_store_rax_to_rbx_indirect(uint8_t * elf_ctx, int32_t elem_sz);
extern int32_t arch_riscv64_enc_enc_store_rax_to_rbx_indirect(uint8_t * elf_ctx, int32_t elem_sz);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbx_indirect(uint8_t * elf_ctx, int32_t elem_sz);
extern int32_t arch_arm64_enc_enc_load_32_from_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_load_32_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_32_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cdqe_rax_impl(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_load_rbp_to_x2(uint8_t * elf_ctx, int32_t offset);
/* G.7 twin of arch_arm64_enc_enc_load_rbp_to_x2 with Rt=3 (x3 = INDEX secondary
 * scratch). Positive-offset LDR X3, [X29, #imm12] — must match primary loader's
 * positive-offset convention; old inline negated offset (LDUR [x29,-off]) loaded
 * garbage from below the frame for arr[i+j] right operand. */
extern int32_t arch_arm64_enc_enc_load_rbp_to_x3(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_load_rbp_to_a2(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_ecx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_arm64_enc_enc_load_64_from_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_load_64_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_64_from_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_store_rax_to_rbx_offset(uint8_t * elf_ctx, int32_t offset, int32_t store_size);
extern int32_t arch_riscv64_enc_enc_store_rax_to_rbx_offset(uint8_t * elf_ctx, int32_t offset, int32_t store_size);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(uint8_t * elf_ctx, int32_t offset, int32_t store_size);
extern int32_t arch_arm64_enc_enc_mov_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mov_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_jz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_enc_enc_jz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_jeq(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_enc_enc_jeq(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jeq(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_jge(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_enc_enc_jge(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jge(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_jnz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_enc_enc_jnz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jnz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_jne(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_jmp(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_enc_enc_jmp(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jmp(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_riscv64_enc_enc_add_sp_imm12(uint8_t * elf_ctx, int32_t nbytes);
extern int32_t arch_x86_64_enc_enc_add_rsp_imm(uint8_t * elf_ctx, int32_t nbytes);
extern int32_t arch_arm64_enc_enc_store_x_reg_to_rbp(uint8_t * elf_ctx, int32_t reg, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_store_rdx_to_rbp(uint8_t * elf_ctx, int32_t offset);
int32_t backend_enc_store_rax_to_rbx_indirect_arch(uint8_t * elf_ctx, int32_t elem_sz, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz);
    }
  }
  {
    return arch_x86_64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz);
  }
  return (0 - 1);
}
int32_t backend_enc_load_32_from_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_32_from_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_32_from_rax(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_load_32_from_rax(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_cdqe_rax_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_load_i32_indirect_to_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      /* LDRSW x0,[x0] 0xB9800000 — signed 32→64; twin of x86 CDQE.
       * ldr w0 zero-extends so INDEX vs 64-bit -5 fails. */
      return arch_arm64_enc_enc_u32_le(elf_ctx, (int32_t)0xB9800000u);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_32_from_rax(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_load_32_from_rax(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_cdqe_rax_impl(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_index_scratch_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_rbp_to_x2(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_a2(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_ecx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_load_64_from_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_64_from_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_64_from_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_load_64_from_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_store_rax_to_rbx_offset_arch(uint8_t * elf_ctx, int32_t offset, int32_t store_size, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
    }
  }
  {
    return arch_x86_64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_rbx_to_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_rbx_to_rax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_rbx_to_rax(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_rbx_to_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_jz_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jz(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jz(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jz(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jeq_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jeq(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jeq(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jeq(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jge_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jge(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jge(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jge(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jnz_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jnz(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jnz(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jnz(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jne_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jne(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jnz(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jnz(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jmp_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_jmp(elf_ctx, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_jmp(elf_ctx, label, label_len);
    }
  }
  {
    return arch_x86_64_enc_enc_jmp(elf_ctx, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_rax_to_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
    }
  }
  {
    return arch_x86_64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
  }
  return (0 - 1);
}
int32_t backend_enc_rem_mod_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      if ((arch_riscv64_enc_enc_cltd(elf_ctx) !=0)) {
        return (0 - 1);
      }
      if ((arch_riscv64_enc_enc_idiv_rbx(elf_ctx) !=0)) {
        return (0 - 1);
      }
      return arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_cltd(elf_ctx) !=0)) {
      return (0 - 1);
    }
    if ((arch_x86_64_enc_enc_idiv_rbx(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx);
  }
  return (0 - 1);
}
/* wave322: xor edx before div — mirror backend_enc_dispatch_thin.x (G.7). */
int32_t backend_enc_rem_mod_unsigned_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      if ((arch_riscv64_enc_enc_idiv_rbx(elf_ctx) !=0)) {
        return (0 - 1);
      }
      return arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx);
    }
  }
  {
    if ((arch_x86_64_enc_enc_xor_edx_edx(elf_ctx) !=0)) {
      return (0 - 1);
    }
    if ((arch_x86_64_enc_enc_div_rbx(elf_ctx) !=0)) {
      return (0 - 1);
    }
    return arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_call_stack_cleanup_arch(uint8_t * elf_ctx, int32_t nbytes, int32_t ta) {
  if ((nbytes <=0)) {
    return 0;
  }
  if ((ta ==1)) {
    if ((elf_ctx ==((uint8_t *)(0)))) {
      return (0 - 1);
    }
    if ((nbytes > 4095)) {
      {
        return backend_enc_append_u32_le_c_impl(elf_ctx, (-1862269953 | (4095 * 1024)));
      }
      return (0 - 1);
    }
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-1862269953 | (((uint32_t)(nbytes)) * 1024)));
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_sp_imm12(elf_ctx, nbytes);
    }
  }
  {
    return arch_x86_64_enc_enc_add_rsp_imm(elf_ctx, nbytes);
  }
  return (0 - 1);
}
int32_t backend_enc_call_stack_reserve_arch(uint8_t * elf_ctx, int32_t nbytes, int32_t ta) {
  if ((nbytes <=0)) {
    return 0;
  }
  if ((ta ==1)) {
    if ((elf_ctx ==((uint8_t *)(0)))) {
      return (0 - 1);
    }
    if ((nbytes > 4095)) {
      {
        return backend_enc_append_u32_le_c_impl(elf_ctx, (-788528129 | (4095 * 1024)));
      }
      return (0 - 1);
    }
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-788528129 | (((uint32_t)(nbytes)) * 1024)));
    }
    return (0 - 1);
  }
  return 0;
}
int32_t backend_enc_store_x0_sp_offset_arch(uint8_t * elf_ctx, int32_t off_bytes, int32_t ta) {
  if ((ta ==1)) {
    if ((elf_ctx ==((uint8_t *)(0)))) {
      return (0 - 1);
    }
    if ((off_bytes < 0)) {
      {
        return backend_enc_append_u32_le_c_impl(elf_ctx, -117439520);
      }
      return (0 - 1);
    }
    if (((off_bytes / 8) > 4095)) {
      {
        return backend_enc_append_u32_le_c_impl(elf_ctx, (-117439520 | (4095 * 1024)));
      }
      return (0 - 1);
    }
    {
      return backend_enc_append_u32_le_c_impl(elf_ctx, (-117439520 | (((uint32_t)((off_bytes / 8))) * 1024)));
    }
    return (0 - 1);
  }
  return (0 - 1);
}
int32_t backend_enc_store_x_reg_to_rbp_arch(uint8_t * elf_ctx, int32_t reg, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_store_x_reg_to_rbp(elf_ctx, reg, offset);
    }
  }
  if ((ta ==0)) {
    return arch_x86_64_enc_enc_store_r64_to_rbp(elf_ctx, reg, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_load_qword_from_rbx_to_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta == 1)) {
    /* ldr x0,[x1] — low 8. PLATFORM: MACOS|ARM64. G.7 twin of full. */
    return arch_arm64_enc_enc_u32_le(elf_ctx, (int32_t)0xF9400020u);
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_load_qword_rbx8_to_rdx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta == 1)) {
    /* ldr x1,[x1,#8] — high 8; rdx=x1. PLATFORM: MACOS|ARM64. */
    return arch_arm64_enc_enc_u32_le(elf_ctx, (int32_t)0xF9400421u);
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(elf_ctx);
  }
  return (0 - 1);
}
/* wave408: arm64 dual-GP length half → str x1,[x29,#off] via store_x_reg. */
extern int32_t arch_arm64_enc_enc_store_x_reg_to_rbp(uint8_t * elf_ctx, int32_t reg, int32_t offset);
int32_t backend_enc_store_rdx_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    return arch_arm64_enc_enc_store_x_reg_to_rbp(elf_ctx, 1, offset);
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_store_rdx_to_rbp(elf_ctx, offset);
  }
  return (0 - 1);
}
extern int32_t arch_riscv64_enc_enc_add_a2_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_sub_a2_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rsub_a2_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rsub_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rsub_rbx_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rsub_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_add_rbx_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_sub_rbx_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mul_a2_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_mul_rbx_a3(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rdx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_mov_rdx_to_arg_reg(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_x86_64_enc_enc_mov_arg_reg_to_rax(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_arm64_enc_enc_mov_arg_reg_to_rax(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_x86_64_enc_enc_load_rbp_pos_to_rax(uint8_t * elf_ctx, int32_t off_pos);
extern int32_t arch_arm64_enc_enc_rbx_plus_x2_scale1(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rbx_plus_a2_scale1(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_rbx_plus_x2_scale4(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rbx_plus_a2_scale4(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(uint8_t * elf_ctx);
extern int32_t arch_arm64_enc_enc_rbx_plus_x2_scale8(uint8_t * elf_ctx);
extern int32_t arch_riscv64_enc_enc_rbx_plus_a2_scale8(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_eax32(uint8_t * elf_ctx, int32_t offset);
extern int32_t backend_enc_x86_jcc_rel32_c_impl(uint8_t * elf_ctx, int32_t opcode2, uint8_t * label, int32_t label_len);
int32_t backend_enc_index_scratch_add_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 184746050);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_a2_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_add_ecx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_index_scratch_sub_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 1258487874);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sub_a2_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_sub_ecx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_index_scratch_rsub_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 1258422370);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rsub_a2_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_rsub_ecx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rbx_index_rsub_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 1258356833);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rsub_rbx_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_rsub_ebx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rbx_index_add_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 184746017);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_rbx_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_add_ebx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rbx_index_sub_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 1258487841);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sub_rbx_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_sub_ebx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_index_scratch_mul_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 453213250);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mul_a2_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_imul_ecx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_rbx_index_mul_secondary_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, 453213217);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mul_rbx_a3(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_imul_ebx_edx(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_call_arch(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return backend_enc_arm64_call_c_impl(elf_ctx, name, name_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_call(elf_ctx, name, name_len);
    }
  }
  {
    return arch_x86_64_enc_enc_call(elf_ctx, name, name_len);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_to_rdx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_rdx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_rdx_to_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return arch_x86_64_enc_enc_mov_rdx_to_arg_reg(elf_ctx, k);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_arg_reg_to_rax_arch(uint8_t * elf_ctx, int32_t k, int32_t ta) {
  if ((ta ==0)) {
    {
      return arch_x86_64_enc_enc_mov_arg_reg_to_rax(elf_ctx, k);
    }
  }
  /* Stage10 10.2.2 slice1: AAPCS arg → x0 for asm! lateout. */
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_mov_arg_reg_to_rax(elf_ctx, k);
    }
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_pos_to_rax_arch(uint8_t * elf_ctx, int32_t off_pos, int32_t ta) {
  if ((ta ==0)) {
    {
      return arch_x86_64_enc_enc_load_rbp_pos_to_rax(elf_ctx, off_pos);
    }
  }
  return (0 - 1);
}
int32_t backend_enc_rbx_plus_index_scratch_scaled_arch(uint8_t * elf_ctx, int32_t esz, int32_t ta) {
  if ((esz ==1)) {
    if ((ta ==1)) {
      {
        return arch_arm64_enc_enc_rbx_plus_x2_scale1(elf_ctx);
      }
    }
    if ((ta ==2)) {
      {
        return arch_riscv64_enc_enc_rbx_plus_a2_scale1(elf_ctx);
      }
    }
    {
      return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(elf_ctx);
    }
    return (0 - 1);
  }
  if ((esz ==4)) {
    if ((ta ==1)) {
      {
        return arch_arm64_enc_enc_rbx_plus_x2_scale4(elf_ctx);
      }
    }
    if ((ta ==2)) {
      {
        return arch_riscv64_enc_enc_rbx_plus_a2_scale4(elf_ctx);
      }
    }
    {
      return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(elf_ctx);
    }
    return (0 - 1);
  }
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_rbx_plus_x2_scale8(elf_ctx);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_rbx_plus_a2_scale8(elf_ctx);
    }
  }
  {
    return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(elf_ctx);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_lane_to_rax_arch(uint8_t * elf_ctx, int32_t offset, int32_t esz, int32_t ta) {
  if ((ta ==1)) {
    if ((esz ==4)) {
      return arm64_enc_load_w0_from_rbp_c(elf_ctx, offset);
    }
    {
      return arch_arm64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
    }
  }
  if ((esz ==4)) {
    {
      return arch_x86_64_enc_enc_load_rbp_to_eax32(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_jle_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return backend_enc_x86_jcc_rel32_c_impl(elf_ctx, 142, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_enc_jl_arch(uint8_t * elf_ctx, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  {
    return backend_enc_x86_jcc_rel32_c_impl(elf_ctx, 140, label, label_len);
  }
  return (0 - 1);
}
extern int32_t arch_riscv64_enc_enc_add_imm_to_a2(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_add_imm_to_ecx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_riscv64_enc_enc_load_rbp_to_a3(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_edx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_sub_imm_from_a2(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_sub_imm_from_ecx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_riscv64_enc_enc_mul_imm_to_a2(uint8_t * elf_ctx, int32_t lit);
extern int32_t arch_x86_64_enc_enc_imul_imm_to_ecx(uint8_t * elf_ctx, int32_t lit);
extern int32_t arch_riscv64_enc_enc_mul_imm_to_rbx(uint8_t * elf_ctx, int32_t lit);
extern int32_t arch_x86_64_enc_enc_imul_imm_to_ebx(uint8_t * elf_ctx, int32_t lit);
extern int32_t arch_x86_64_enc_enc_add_imm_to_ebx_index(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_riscv64_enc_enc_sub_imm_from_rbx_index(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_sub_imm_from_ebx_index(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_arm64_enc_enc_load_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_riscv64_enc_enc_load_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_ebx32(uint8_t * elf_ctx, int32_t offset);
int32_t backend_enc_load_x29_pos_to_rax_arch(uint8_t * elf_ctx, int32_t off_pos, int32_t ta) {
  if ((ta !=1)) {
    return (0 - 1);
  }
  if ((off_pos < 0)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(-113245280)));
    }
    return (0 - 1);
  }
  if (((off_pos / 8) > 4095)) {
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((-113245280 | (4095 * 1024)))));
    }
    return (0 - 1);
  }
  {
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((-113245280 | (((uint32_t)((off_pos / 8))) * 1024)))));
  }
  return (0 - 1);
}
int32_t backend_enc_add_imm_to_index_scratch_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    if ((imm ==0)) {
      return 0;
    }
    if ((imm > 4095)) {
      {
        return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((285213762 + ((4095 - 1) * 1024)))));
      }
      return (0 - 1);
    }
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((285213762 + ((imm - 1) * 1024)))));
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_imm_to_a2(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_add_imm_to_ecx(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_index_secondary_scratch_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  /* wave617: delegate to arch_arm64_enc_enc_load_rbp_to_x3 (positive-offset LDR
   * X3, [X29, #imm12]) — SAME convention as primary loader load_rbp_to_x2.
   * Root: old inline negated offset (LDUR W3, [x29,-off]) while primary used
   *   positive LDR X2, [x29,+off] → secondary loaded garbage below the frame
   *   for arr[i+j] right operand (i+j computed wrong, e.g. got 10 not 99).
   * Invariant: secondary loader offset convention MUST match primary loader. */
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_rbp_to_x3(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_a3(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_edx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_sub_imm_from_index_scratch_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    if ((imm ==0)) {
      return 0;
    }
    if ((imm > 4095)) {
      {
        return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((1358955586 + ((4095 - 1) * 1024)))));
      }
      return (0 - 1);
    }
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((1358955586 + ((imm - 1) * 1024)))));
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sub_imm_from_a2(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_sub_imm_from_ecx(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_mul_imm_to_index_scratch_arch(uint8_t * elf_ctx, int32_t lit, int32_t ta) {
  if ((lit <=1)) {
    return 0;
  }
  if ((lit > 65535)) {
    return (0 - 1);
  }
  if ((ta ==1)) {
    {
      if ((arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((1384120320 | (((uint32_t)(lit)) * 32)) | 3)))) !=0)) {
        return (0 - 1);
      }
      return arch_arm64_enc_enc_u32_le(elf_ctx, 453213250);
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mul_imm_to_a2(elf_ctx, lit);
    }
  }
  {
    return arch_x86_64_enc_enc_imul_imm_to_ecx(elf_ctx, lit);
  }
  return (0 - 1);
}
int32_t backend_enc_mul_imm_to_rbx_arch(uint8_t * elf_ctx, int32_t lit, int32_t ta) {
  if ((lit <=1)) {
    return 0;
  }
  if ((lit > 65535)) {
    return (0 - 1);
  }
  if ((ta ==1)) {
    {
      if ((arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((1384120320 | (((uint32_t)(lit)) * 32)) | 3)))) !=0)) {
        return (0 - 1);
      }
      return arch_arm64_enc_enc_u32_le(elf_ctx, 453213217);
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_mul_imm_to_rbx(elf_ctx, lit);
    }
  }
  {
    return arch_x86_64_enc_enc_imul_imm_to_ebx(elf_ctx, lit);
  }
  return (0 - 1);
}
int32_t backend_enc_add_imm_to_rbx_index_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((imm ==0)) {
    return 0;
  }
  if ((ta ==1)) {
    if ((imm > 4095)) {
      {
        return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((285213729 + ((4095 - 1) * 1024)))));
      }
      return (0 - 1);
    }
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((285213729 + ((imm - 1) * 1024)))));
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_add_imm_to_rbx(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_add_imm_to_ebx_index(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_sub_imm_from_rbx_index_arch(uint8_t * elf_ctx, int32_t imm, int32_t ta) {
  if ((imm ==0)) {
    return 0;
  }
  if ((ta ==1)) {
    if ((imm > 4095)) {
      {
        return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((1358955553 + ((4095 - 1) * 1024)))));
      }
      return (0 - 1);
    }
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)((1358955553 + ((imm - 1) * 1024)))));
    }
    return (0 - 1);
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_sub_imm_from_rbx_index(elf_ctx, imm);
    }
  }
  {
    return arch_x86_64_enc_enc_sub_imm_from_ebx_index(elf_ctx, imm);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_load_rbp_lane_to_rbx_arch(uint8_t * elf_ctx, int32_t offset, int32_t esz, int32_t ta) {
  if ((ta ==1)) {
    if ((esz ==4)) {
      return arm64_enc_load_w1_from_rbp_c(elf_ctx, offset);
    }
    {
      return arch_arm64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
    }
  }
  if ((esz ==4)) {
    {
      return arch_x86_64_enc_enc_load_rbp_to_ebx32(elf_ctx, offset);
    }
  }
  {
    return arch_x86_64_enc_enc_load_rbp_to_rbx(elf_ctx, offset);
  }
  return (0 - 1);
}
int32_t backend_enc_addss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1066528922) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -881979546) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1051193357) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
/* wave294: f32 MUL freestanding (mulss); thin twin of addss with F3 0F 59 C1. */
int32_t backend_enc_mulss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1066528922) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -881979546) !=0)) {
      return (0 - 1);
    }
    /* mulss F3 0F 59 C1 → u32 3243839475 → i32 -1051127821 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1051127821) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
/* wave298: f32 SUB freestanding (subss); left=rbx right=rax → eax. */
int32_t backend_enc_subss_rbx_rax_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* movd xmm0,ebx: 66 0f 6e c3 → i32 -1016197274 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1016197274) !=0)) {
      return (0 - 1);
    }
    /* movd xmm1,eax: 66 0f 6e c8 → i32 -932311194 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -932311194) !=0)) {
      return (0 - 1);
    }
    /* subss F3 0F 5C C1 → u32 3244036083 → i32 -1050931213 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1050931213) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
/* wave298: f32 SUB freestanding (subss); left=rax right=rbx → eax. */
int32_t backend_enc_subss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1066528922) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -881979546) !=0)) {
      return (0 - 1);
    }
    /* subss F3 0F 5C C1 → i32 -1050931213 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1050931213) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
/* wave298: f32 DIV freestanding (divss); left=rax right=rbx → eax. */
int32_t backend_enc_divss_rax_rbx_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1066528922) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -881979546) !=0)) {
      return (0 - 1);
    }
    /* divss F3 0F 5E C1 → u32 3244167155 → i32 -1050800141 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1050800141) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
int32_t backend_enc_cvttss2si_eax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1066528922) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1070854157);
  }
  return (0 - 1);
}
int32_t backend_enc_cvttsd2si_eax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 1846495334) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 192) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, 3224113138);
  }
  return (0 - 1);
}
/* wave303: f32→i64 freestanding cast (REX.W cvttss2si). */
int32_t backend_enc_cvttss2si_rax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* movd xmm0,eax: 66 0f 6e c0 → 3228438374 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 3228438374) !=0)) {
      return (0 - 1);
    }
    /* cvttss2si rax,xmm0: f3 48 0f 2c = 0x2c0f48f3 = 739199219u ; + c0 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 739199219) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, 192);
  }
  return (0 - 1);
}
/* wave303: f64→i64 freestanding cast (REX.W cvttsd2si). */
int32_t backend_enc_cvttsd2si_rax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 1846495334) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 192) !=0)) {
      return (0 - 1);
    }
    /* cvttsd2si rax,xmm0: f2 48 0f 2c = 0x2c0f48f2 = 739199218u ; + c0 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 739199218) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, 192);
  }
  return (0 - 1);
}
int32_t backend_enc_cvtsd2ss_eax_from_f64_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 1846495334) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 192) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1067839502) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
int32_t backend_enc_cvtsi2ss_eax_from_i32_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, -1070985229) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u32_le_c_impl(elf_ctx, -1065480346);
  }
  return (0 - 1);
}
/* wave299: i64/u64→f32 freestanding cast (REX.W cvtsi2ss). */
int32_t backend_enc_cvtsi2ss_eax_from_i64_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* f3 48 0f 2a = 0x2a0f48f3 = 705644787u ; + c0 → cvtsi2ss xmm0,rax */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 705644787) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 192) !=0)) {
      return (0 - 1);
    }
    /* movd eax,xmm0: 66 0f 7e c0 = 3229486950u */
    return backend_enc_append_u32_le_c_impl(elf_ctx, 3229486950);
  }
  return (0 - 1);
}
/* wave292: i32→f64 freestanding cast (cvtsi2sd). */
int32_t backend_enc_cvtsi2sd_rax_from_i32_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* f2 0f 2a c0 = 0xc02a0ff2 = 3223982066u */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 3223982066) !=0)) {
      return (0 - 1);
    }
    /* 66 48 0f 7e = 0x7e0f4866 = 2114930790u ; + c0 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 2114930790) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, 192);
  }
  return (0 - 1);
}
/* wave295: i64/u64→f64 freestanding cast (REX.W cvtsi2sd). */
int32_t backend_enc_cvtsi2sd_rax_from_i64_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* f2 48 0f 2a = 0x2a0f48f2 = 705644786u ; + c0 → cvtsi2sd xmm0,rax */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 705644786) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 192) !=0)) {
      return (0 - 1);
    }
    /* 66 48 0f 7e = 0x7e0f4866 = 2114930790u ; + c0 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 2114930790) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, 192);
  }
  return (0 - 1);
}
/* wave304: u64→f64 unsigned freestanding cast sequence. */
int32_t backend_enc_cvtsi2sd_rax_from_u64_arch(uint8_t * elf_ctx, int32_t ta) {
  static const uint8_t seq[43] = {
      0x48, 0x85, 0xc0, 0x79, 0x1c,
      0x48, 0x89, 0xc2, 0x48, 0xd1, 0xea, 0x83, 0xe0, 0x01, 0x48, 0x09, 0xc2,
      0xf2, 0x48, 0x0f, 0x2a, 0xc2, 0xf2, 0x0f, 0x58, 0xc0,
      0x66, 0x48, 0x0f, 0x7e, 0xc0, 0xeb, 0x0a,
      0xf2, 0x48, 0x0f, 0x2a, 0xc0, 0x66, 0x48, 0x0f, 0x7e, 0xc0
  };
  int32_t i;
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  for (i = 0; i < 43; i++) {
    if ((backend_enc_append_u8_c_impl(elf_ctx, (int32_t)seq[i]) !=0)) {
      return (0 - 1);
    }
  }
  return 0;
}
/* wave304: u64→f32 unsigned freestanding cast sequence. */
int32_t backend_enc_cvtsi2ss_eax_from_u64_arch(uint8_t * elf_ctx, int32_t ta) {
  static const uint8_t seq[41] = {
      0x48, 0x85, 0xc0, 0x79, 0x1b,
      0x48, 0x89, 0xc2, 0x48, 0xd1, 0xea, 0x83, 0xe0, 0x01, 0x48, 0x09, 0xc2,
      0xf3, 0x48, 0x0f, 0x2a, 0xc2, 0xf3, 0x0f, 0x58, 0xc0,
      0x66, 0x0f, 0x7e, 0xc0, 0xeb, 0x09,
      0xf3, 0x48, 0x0f, 0x2a, 0xc0, 0x66, 0x0f, 0x7e, 0xc0
  };
  int32_t i;
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  for (i = 0; i < 41; i++) {
    if ((backend_enc_append_u8_c_impl(elf_ctx, (int32_t)seq[i]) !=0)) {
      return (0 - 1);
    }
  }
  return 0;
}

/* wave293: f32→f64 freestanding cast (cvtss2sd). */
int32_t backend_enc_cvtss2sd_rax_from_f32_bits_arch(uint8_t * elf_ctx, int32_t ta) {
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    /* movd xmm0,eax: 66 0f 6e c0 = 0xc06e0f66 = 3228438374u */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 3228438374) !=0)) {
      return (0 - 1);
    }
    /* cvtss2sd xmm0,xmm0: f3 0f 5a c0 = 0xc05a0ff3 = 3227127795u
     * (cvtsd2ss is f2… = 3227127794; do not miscompute decimal). */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 3227127795) !=0)) {
      return (0 - 1);
    }
    /* movq rax,xmm0: 66 48 0f 7e + c0 */
    if ((backend_enc_append_u32_le_c_impl(elf_ctx, 2114930790) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, 192);
  }
  return (0 - 1);
}
int32_t backend_enc_mov_eax_to_xmm_arg_reg_arch(uint8_t * elf_ctx, int32_t k, int32_t ta) {
  /* PLATFORM: MACOS|ARM64 AAPCS64 — fmov sK, w0. Twin of full seed. */
  if (ta == 1) {
    if ((elf_ctx == ((uint8_t *)(0))) || (k < 0) || (k > 7)) {
      return (0 - 1);
    }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(0x1e270000u | (uint32_t)k)));
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((k < 0)) {
    return (0 - 1);
  }
  if ((k > 7)) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u8_c_impl(elf_ctx, 102) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 15) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 110) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, (192 + (k * 8)));
  }
  return (0 - 1);
}
int32_t backend_enc_mov_xmm_arg_reg_to_eax_arch(uint8_t * elf_ctx, int32_t k, int32_t ta) {
  /* PLATFORM: MACOS|ARM64 AAPCS64 — fmov w0, sK. Twin of full seed. */
  if (ta == 1) {
    if ((elf_ctx == ((uint8_t *)(0))) || (k < 0) || (k > 7)) {
      return (0 - 1);
    }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(0x1e260000u | ((uint32_t)k << 5))));
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if ((k < 0)) {
    return (0 - 1);
  }
  if ((k > 7)) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u8_c_impl(elf_ctx, 102) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 15) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 126) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, (192 + (k * 8)));
  }
  return (0 - 1);
}
int32_t backend_enc_store_eax_to_rbp_arch(uint8_t * elf_ctx, int32_t offset, int32_t ta) {
  if ((ta ==1)) {
    if ((elf_ctx ==((uint8_t *)(0)))) {
      return (0 - 1);
    }
    if ((offset < 0)) {
      return (0 - 1);
    }
    if ((offset > 256)) {
      {
        return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((-1207959552 | (256 * 4096)) | 928))));
      }
      return (0 - 1);
    }
    {
      return arch_arm64_enc_enc_u32_le(elf_ctx, ((int32_t)(((-1207959552 | (((uint32_t)(((0 - offset) & 511))) * 4096)) | 928))));
    }
    return (0 - 1);
  }
  if ((ta !=0)) {
    return (0 - 1);
  }
  if ((elf_ctx ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  {
    if ((backend_enc_append_u8_c_impl(elf_ctx, 137) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, 133) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, (((uint32_t)((0 - offset))) & 255)) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, ((((uint32_t)((0 - offset))) / 256) & 255)) !=0)) {
      return (0 - 1);
    }
    if ((backend_enc_append_u8_c_impl(elf_ctx, ((((uint32_t)((0 - offset))) / 65536) & 255)) !=0)) {
      return (0 - 1);
    }
    return backend_enc_append_u8_c_impl(elf_ctx, ((((uint32_t)((0 - offset))) / 16777216) & 255));
  }
  return (0 - 1);
}
int32_t backend_enc_append_u32_le_c(uint8_t * elf_ctx, uint32_t word) {
  {
    return backend_enc_append_u32_le_c_impl(elf_ctx, word);
  }
  return (0 - 1);
}
int32_t backend_enc_append_u8_c(uint8_t * elf_ctx, int32_t byte) {
  {
    return backend_enc_append_u8_c_impl(elf_ctx, byte);
  }
  return (0 - 1);
}
int32_t backend_enc_arm64_call_c(uint8_t * elf_ctx, uint8_t * name, int32_t name_len) {
  {
    return backend_enc_arm64_call_c_impl(elf_ctx, name, name_len);
  }
  return (0 - 1);
}
int32_t backend_enc_x86_jcc_rel32_c(uint8_t * elf_ctx, int32_t opcode2, uint8_t * label, int32_t label_len) {
  {
    return backend_enc_x86_jcc_rel32_c_impl(elf_ctx, opcode2, label, label_len);
  }
  return (0 - 1);
}
int32_t arch_x86_64_enc_enc_cdqe_rax(uint8_t * elf_ctx) {
  {
    return arch_x86_64_enc_enc_cdqe_rax_impl(elf_ctx);
  }
  return (0 - 1);
}
