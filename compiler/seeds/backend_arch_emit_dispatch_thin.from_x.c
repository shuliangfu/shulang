/* seeds/backend_arch_emit_dispatch_thin.from_x.c
 * G-02f backend_arch_emit_dispatch R2 thin full surface (legacy name) — isomorphic with src/asm/backend_arch_emit_dispatch_thin.x
 * Product PREFER_X_O: g05_try_x_to_o(thin.x) + full seed rest (-DXLANG_L2_ARCH_EMIT_THIN_FROM_X) ld -r
 * Cap residual: arch_*_emit_* C 尾 outside thin (asm_backend_partial / cold full seed shells)
 * Regen: ./xlang -E ... src/asm/backend_arch_emit_dispatch_thin.x | filter DBG + polish externs
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
extern int32_t backend_arch_emit_ret_imm32(uint8_t * out, int32_t imm, int32_t ta);
extern int32_t backend_arch_emit_mov_imm64_to_rax(uint8_t * out, int32_t lo, int32_t hi, int32_t ta);
extern int32_t backend_arch_emit_mov_imm32_to_rbx(uint8_t * out, int32_t imm, int32_t ta);
extern int32_t backend_arch_emit_neg_eax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_cmp_rbx_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_cmp_setcc(uint8_t * out, int32_t cc, int32_t ta);
extern int32_t backend_arch_emit_push_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_pop_rbx(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_pop_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_add_rax_rbx(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_sub_rbx_rax_then_mov(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_imul_rbx_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_mov_rax_to_rbx(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_load_rbp_to_rax(uint8_t * out, int32_t off, int32_t ta);
extern int32_t backend_arch_emit_store_rax_to_rbp(uint8_t * out, int32_t off, int32_t ta);
extern int32_t backend_arch_emit_lea_rbp_to_rax(uint8_t * out, int32_t off, int32_t ta);
extern int32_t backend_arch_emit_rax_plus_rbx_scale4(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_rax_plus_rbx_scale1(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_rax_plus_rbx_scale8(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_store_rax_to_rbx_indirect(uint8_t * out, int32_t elem_sz, int32_t ta);
extern int32_t backend_arch_emit_load_32_from_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_load_zext8_from_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_add_imm_to_rax(uint8_t * out, int32_t imm, int32_t ta);
extern int32_t backend_arch_emit_load_64_from_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_store_rax_to_rbx_offset(uint8_t * out, int32_t offset, int32_t store_size, int32_t ta);
extern int32_t backend_arch_emit_mov_rbx_to_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_mov_rax_to_arg_reg(uint8_t * out, int32_t k, int32_t ta);
extern int32_t backend_arch_emit_ldr_sp_offset_to_wi(uint8_t * out, int32_t i, int32_t ta);
extern int32_t backend_arch_emit_add_sp_imm(uint8_t * out, int32_t n, int32_t ta);
extern int32_t backend_arch_emit_call(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta);
extern int32_t backend_arch_emit_jz(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_arch_emit_jeq(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_arch_emit_jmp(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_arch_emit_jnz(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta);
extern int32_t backend_arch_emit_not_eax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_and_rbx_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_or_rbx_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_xor_rbx_rax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_mov_rbx_to_ecx(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_shl_cl_eax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_shr_cl_eax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_sar_cl_eax(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_label(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta);
extern int32_t backend_arch_emit_section_text(uint8_t * out, int32_t ta);
extern int32_t backend_arch_emit_globl(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta);
extern int32_t backend_arch_emit_prologue(uint8_t * out, int32_t frame_sz, int32_t ta);
extern int32_t backend_arch_emit_epilogue(uint8_t * out, int32_t frame_sz, int32_t ta);
extern int32_t arch_arm64_emit_add_imm_to_rax(uint8_t * out, int32_t imm);
extern int32_t arch_arm64_emit_add_rax_rbx(uint8_t * out);
extern int32_t arch_arm64_emit_add_sp_imm(uint8_t * out, int32_t n);
extern int32_t arch_arm64_emit_and_rbx_rax(uint8_t * out);
extern int32_t arch_arm64_emit_call(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_arm64_emit_cmp_rbx_rax(uint8_t * out);
extern int32_t arch_arm64_emit_cmp_setcc(uint8_t * out, int32_t cc);
extern int32_t arch_arm64_emit_epilogue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_arm64_emit_globl(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_arm64_emit_imul_rbx_rax(uint8_t * out);
extern int32_t arch_arm64_emit_jeq(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_emit_jmp(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_emit_jnz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_emit_jz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_arm64_emit_label(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_arm64_emit_ldr_sp_offset_to_wi(uint8_t * out, int32_t i);
extern int32_t arch_arm64_emit_lea_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_arm64_emit_load_32_from_rax(uint8_t * out);
extern int32_t arch_arm64_emit_load_64_from_rax(uint8_t * out);
extern int32_t arch_arm64_emit_load_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_arm64_emit_load_zext8_from_rax(uint8_t * out);
extern int32_t arch_arm64_emit_mov_imm32_to_rbx(uint8_t * out, int32_t imm);
extern int32_t arch_arm64_emit_mov_imm64_to_rax(uint8_t * out, int32_t lo, int32_t hi);
extern int32_t arch_arm64_emit_mov_rax_to_rbx(uint8_t * out);
extern int32_t arch_arm64_emit_mov_rbx_to_rax(uint8_t * out);
extern int32_t arch_arm64_emit_neg_eax(uint8_t * out);
extern int32_t arch_arm64_emit_not_eax(uint8_t * out);
extern int32_t arch_arm64_emit_or_rbx_rax(uint8_t * out);
extern int32_t arch_arm64_emit_pop_rax(uint8_t * out);
extern int32_t arch_arm64_emit_pop_rbx(uint8_t * out);
extern int32_t arch_arm64_emit_prologue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_arm64_emit_push_rax(uint8_t * out);
extern int32_t arch_arm64_emit_rax_plus_rbx_scale1(uint8_t * out);
extern int32_t arch_arm64_emit_rax_plus_rbx_scale4(uint8_t * out);
extern int32_t arch_arm64_emit_rax_plus_rbx_scale8(uint8_t * out);
extern int32_t arch_arm64_emit_ret_imm32(uint8_t * out, int32_t imm);
extern int32_t arch_arm64_emit_sar_cl_eax(uint8_t * out);
extern int32_t arch_arm64_emit_section_text(uint8_t * out);
extern int32_t arch_arm64_emit_shl_cl_eax(uint8_t * out);
extern int32_t arch_arm64_emit_shr_cl_eax(uint8_t * out);
extern int32_t arch_arm64_emit_store_rax_to_rbp(uint8_t * out, int32_t off);
extern int32_t arch_arm64_emit_store_rax_to_rbx_indirect(uint8_t * out, int32_t elem_sz);
extern int32_t arch_arm64_emit_store_rax_to_rbx_offset(uint8_t * out, int32_t offset, int32_t store_size);
extern int32_t arch_arm64_emit_sub_rbx_rax_then_mov(uint8_t * out);
extern int32_t arch_arm64_emit_xor_rbx_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_add_imm_to_rax(uint8_t * out, int32_t imm);
extern int32_t arch_riscv64_emit_add_rax_rbx(uint8_t * out);
extern int32_t arch_riscv64_emit_and_rbx_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_call(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_emit_cmp_rbx_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_cmp_setcc(uint8_t * out, int32_t cc);
extern int32_t arch_riscv64_emit_epilogue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_riscv64_emit_globl(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_emit_imul_rbx_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_jeq(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_emit_jmp(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_emit_jnz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_emit_jz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_riscv64_emit_label(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_riscv64_emit_lea_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_riscv64_emit_load_32_from_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_load_64_from_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_load_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_riscv64_emit_load_zext8_from_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_mov_imm32_to_rbx(uint8_t * out, int32_t imm);
extern int32_t arch_riscv64_emit_mov_imm64_to_rax(uint8_t * out, int32_t lo, int32_t hi);
extern int32_t arch_riscv64_emit_mov_rax_to_arg_reg(uint8_t * out, int32_t k);
extern int32_t arch_riscv64_emit_mov_rax_to_rbx(uint8_t * out);
extern int32_t arch_riscv64_emit_mov_rbx_to_ecx(uint8_t * out);
extern int32_t arch_riscv64_emit_mov_rbx_to_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_neg_eax(uint8_t * out);
extern int32_t arch_riscv64_emit_not_eax(uint8_t * out);
extern int32_t arch_riscv64_emit_or_rbx_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_pop_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_pop_rbx(uint8_t * out);
extern int32_t arch_riscv64_emit_prologue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_riscv64_emit_push_rax(uint8_t * out);
extern int32_t arch_riscv64_emit_rax_plus_rbx_scale1(uint8_t * out);
extern int32_t arch_riscv64_emit_rax_plus_rbx_scale4(uint8_t * out);
extern int32_t arch_riscv64_emit_rax_plus_rbx_scale8(uint8_t * out);
extern int32_t arch_riscv64_emit_ret_imm32(uint8_t * out, int32_t imm);
extern int32_t arch_riscv64_emit_sar_cl_eax(uint8_t * out);
extern int32_t arch_riscv64_emit_section_text(uint8_t * out);
extern int32_t arch_riscv64_emit_shl_cl_eax(uint8_t * out);
extern int32_t arch_riscv64_emit_shr_cl_eax(uint8_t * out);
extern int32_t arch_riscv64_emit_store_rax_to_rbp(uint8_t * out, int32_t off);
extern int32_t arch_riscv64_emit_store_rax_to_rbx_indirect(uint8_t * out, int32_t elem_sz);
extern int32_t arch_riscv64_emit_store_rax_to_rbx_offset(uint8_t * out, int32_t offset, int32_t store_size);
extern int32_t arch_riscv64_emit_sub_rbx_rax_then_mov(uint8_t * out);
extern int32_t arch_riscv64_emit_xor_rbx_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_add_imm_to_rax(uint8_t * out, int32_t imm);
extern int32_t arch_x86_64_emit_add_rax_rbx(uint8_t * out);
extern int32_t arch_x86_64_emit_and_rbx_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_call(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_x86_64_emit_cmp_rbx_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_cmp_setcc(uint8_t * out, int32_t cc);
extern int32_t arch_x86_64_emit_epilogue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_x86_64_emit_globl(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_x86_64_emit_imul_rbx_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_jeq(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_emit_jmp(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_emit_jnz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_emit_jz(uint8_t * out, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_emit_label(uint8_t * out, uint8_t * name, int32_t name_len);
extern int32_t arch_x86_64_emit_lea_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_x86_64_emit_load_32_from_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_load_64_from_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_load_rbp_to_rax(uint8_t * out, int32_t off);
extern int32_t arch_x86_64_emit_load_zext8_from_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_mov_imm32_to_rbx(uint8_t * out, int32_t imm);
extern int32_t arch_x86_64_emit_mov_imm64_to_rax(uint8_t * out, int32_t lo, int32_t hi);
extern int32_t arch_x86_64_emit_mov_rax_to_arg_reg(uint8_t * out, int32_t k);
extern int32_t arch_x86_64_emit_mov_rax_to_rbx(uint8_t * out);
extern int32_t arch_x86_64_emit_mov_rbx_to_ecx(uint8_t * out);
extern int32_t arch_x86_64_emit_mov_rbx_to_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_neg_eax(uint8_t * out);
extern int32_t arch_x86_64_emit_not_eax(uint8_t * out);
extern int32_t arch_x86_64_emit_or_rbx_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_pop_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_pop_rbx(uint8_t * out);
extern int32_t arch_x86_64_emit_prologue(uint8_t * out, int32_t frame_sz);
extern int32_t arch_x86_64_emit_push_rax(uint8_t * out);
extern int32_t arch_x86_64_emit_rax_plus_rbx_scale1(uint8_t * out);
extern int32_t arch_x86_64_emit_rax_plus_rbx_scale4(uint8_t * out);
extern int32_t arch_x86_64_emit_rax_plus_rbx_scale8(uint8_t * out);
extern int32_t arch_x86_64_emit_ret_imm32(uint8_t * out, int32_t imm);
extern int32_t arch_x86_64_emit_sar_cl_eax(uint8_t * out);
extern int32_t arch_x86_64_emit_section_text(uint8_t * out);
extern int32_t arch_x86_64_emit_shl_cl_eax(uint8_t * out);
extern int32_t arch_x86_64_emit_shr_cl_eax(uint8_t * out);
extern int32_t arch_x86_64_emit_store_rax_to_rbp(uint8_t * out, int32_t off);
extern int32_t arch_x86_64_emit_store_rax_to_rbx_indirect(uint8_t * out, int32_t elem_sz);
extern int32_t arch_x86_64_emit_store_rax_to_rbx_offset(uint8_t * out, int32_t offset, int32_t store_size);
extern int32_t arch_x86_64_emit_sub_rbx_rax_then_mov(uint8_t * out);
extern int32_t arch_x86_64_emit_xor_rbx_rax(uint8_t * out);
int32_t backend_arch_emit_ret_imm32(uint8_t * out, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_ret_imm32(out, imm);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_ret_imm32(out, imm);
    }
  }
  {
    return arch_x86_64_emit_ret_imm32(out, imm);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_imm64_to_rax(uint8_t * out, int32_t lo, int32_t hi, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_mov_imm64_to_rax(out, lo, hi);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_imm64_to_rax(out, lo, hi);
    }
  }
  {
    return arch_x86_64_emit_mov_imm64_to_rax(out, lo, hi);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_imm32_to_rbx(uint8_t * out, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_mov_imm32_to_rbx(out, imm);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_imm32_to_rbx(out, imm);
    }
  }
  {
    return arch_x86_64_emit_mov_imm32_to_rbx(out, imm);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_neg_eax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_neg_eax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_neg_eax(out);
    }
  }
  {
    return arch_x86_64_emit_neg_eax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_cmp_rbx_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_cmp_rbx_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_cmp_rbx_rax(out);
    }
  }
  {
    return arch_x86_64_emit_cmp_rbx_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_cmp_setcc(uint8_t * out, int32_t cc, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_cmp_setcc(out, cc);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_cmp_setcc(out, cc);
    }
  }
  {
    return arch_x86_64_emit_cmp_setcc(out, cc);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_push_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_push_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_push_rax(out);
    }
  }
  {
    return arch_x86_64_emit_push_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_pop_rbx(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_pop_rbx(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_pop_rbx(out);
    }
  }
  {
    return arch_x86_64_emit_pop_rbx(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_pop_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_pop_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_pop_rax(out);
    }
  }
  {
    return arch_x86_64_emit_pop_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_add_rax_rbx(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_add_rax_rbx(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_add_rax_rbx(out);
    }
  }
  {
    return arch_x86_64_emit_add_rax_rbx(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_sub_rbx_rax_then_mov(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_sub_rbx_rax_then_mov(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_sub_rbx_rax_then_mov(out);
    }
  }
  {
    return arch_x86_64_emit_sub_rbx_rax_then_mov(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_imul_rbx_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_imul_rbx_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_imul_rbx_rax(out);
    }
  }
  {
    return arch_x86_64_emit_imul_rbx_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_rax_to_rbx(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_mov_rax_to_rbx(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_rax_to_rbx(out);
    }
  }
  {
    return arch_x86_64_emit_mov_rax_to_rbx(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_load_rbp_to_rax(uint8_t * out, int32_t off, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_load_rbp_to_rax(out, off);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_load_rbp_to_rax(out, off);
    }
  }
  {
    return arch_x86_64_emit_load_rbp_to_rax(out, off);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_store_rax_to_rbp(uint8_t * out, int32_t off, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_store_rax_to_rbp(out, off);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_store_rax_to_rbp(out, off);
    }
  }
  {
    return arch_x86_64_emit_store_rax_to_rbp(out, off);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_lea_rbp_to_rax(uint8_t * out, int32_t off, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_lea_rbp_to_rax(out, off);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_lea_rbp_to_rax(out, off);
    }
  }
  {
    return arch_x86_64_emit_lea_rbp_to_rax(out, off);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_rax_plus_rbx_scale4(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_rax_plus_rbx_scale4(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_rax_plus_rbx_scale4(out);
    }
  }
  {
    return arch_x86_64_emit_rax_plus_rbx_scale4(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_rax_plus_rbx_scale1(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_rax_plus_rbx_scale1(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_rax_plus_rbx_scale1(out);
    }
  }
  {
    return arch_x86_64_emit_rax_plus_rbx_scale1(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_rax_plus_rbx_scale8(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_rax_plus_rbx_scale8(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_rax_plus_rbx_scale8(out);
    }
  }
  {
    return arch_x86_64_emit_rax_plus_rbx_scale8(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_store_rax_to_rbx_indirect(uint8_t * out, int32_t elem_sz, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_store_rax_to_rbx_indirect(out, elem_sz);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_store_rax_to_rbx_indirect(out, elem_sz);
    }
  }
  {
    return arch_x86_64_emit_store_rax_to_rbx_indirect(out, elem_sz);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_load_32_from_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_load_32_from_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_load_32_from_rax(out);
    }
  }
  {
    return arch_x86_64_emit_load_32_from_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_load_zext8_from_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_load_zext8_from_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_load_zext8_from_rax(out);
    }
  }
  {
    return arch_x86_64_emit_load_zext8_from_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_add_imm_to_rax(uint8_t * out, int32_t imm, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_add_imm_to_rax(out, imm);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_add_imm_to_rax(out, imm);
    }
  }
  {
    return arch_x86_64_emit_add_imm_to_rax(out, imm);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_load_64_from_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_load_64_from_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_load_64_from_rax(out);
    }
  }
  {
    return arch_x86_64_emit_load_64_from_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_store_rax_to_rbx_offset(uint8_t * out, int32_t offset, int32_t store_size, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_store_rax_to_rbx_offset(out, offset, store_size);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_store_rax_to_rbx_offset(out, offset, store_size);
    }
  }
  {
    return arch_x86_64_emit_store_rax_to_rbx_offset(out, offset, store_size);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_rbx_to_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_mov_rbx_to_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_rbx_to_rax(out);
    }
  }
  {
    return arch_x86_64_emit_mov_rbx_to_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_rax_to_arg_reg(uint8_t * out, int32_t k, int32_t ta) {
  if ((ta ==1)) {
    return 0;
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_rax_to_arg_reg(out, k);
    }
  }
  {
    return arch_x86_64_emit_mov_rax_to_arg_reg(out, k);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_ldr_sp_offset_to_wi(uint8_t * out, int32_t i, int32_t ta) {
  if ((ta !=1)) {
    return 0;
  }
  {
    return arch_arm64_emit_ldr_sp_offset_to_wi(out, i);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_add_sp_imm(uint8_t * out, int32_t n, int32_t ta) {
  if ((ta !=1)) {
    return 0;
  }
  {
    return arch_arm64_emit_add_sp_imm(out, n);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_call(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_call(out, name, name_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_call(out, name, name_len);
    }
  }
  {
    return arch_x86_64_emit_call(out, name, name_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_jz(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_jz(out, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_jz(out, label, label_len);
    }
  }
  {
    return arch_x86_64_emit_jz(out, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_jeq(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_jeq(out, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_jeq(out, label, label_len);
    }
  }
  {
    return arch_x86_64_emit_jeq(out, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_jmp(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_jmp(out, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_jmp(out, label, label_len);
    }
  }
  {
    return arch_x86_64_emit_jmp(out, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_jnz(uint8_t * out, uint8_t * label, int32_t label_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_jnz(out, label, label_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_jnz(out, label, label_len);
    }
  }
  {
    return arch_x86_64_emit_jnz(out, label, label_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_not_eax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_not_eax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_not_eax(out);
    }
  }
  {
    return arch_x86_64_emit_not_eax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_and_rbx_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_and_rbx_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_and_rbx_rax(out);
    }
  }
  {
    return arch_x86_64_emit_and_rbx_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_or_rbx_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_or_rbx_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_or_rbx_rax(out);
    }
  }
  {
    return arch_x86_64_emit_or_rbx_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_xor_rbx_rax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_xor_rbx_rax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_xor_rbx_rax(out);
    }
  }
  {
    return arch_x86_64_emit_xor_rbx_rax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_mov_rbx_to_ecx(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    return 0;
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_mov_rbx_to_ecx(out);
    }
  }
  {
    return arch_x86_64_emit_mov_rbx_to_ecx(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_shl_cl_eax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_shl_cl_eax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_shl_cl_eax(out);
    }
  }
  {
    return arch_x86_64_emit_shl_cl_eax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_shr_cl_eax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_shr_cl_eax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_shr_cl_eax(out);
    }
  }
  {
    return arch_x86_64_emit_shr_cl_eax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_sar_cl_eax(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_sar_cl_eax(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_sar_cl_eax(out);
    }
  }
  {
    return arch_x86_64_emit_sar_cl_eax(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_label(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_label(out, name, name_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_label(out, name, name_len);
    }
  }
  {
    return arch_x86_64_emit_label(out, name, name_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_section_text(uint8_t * out, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_section_text(out);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_section_text(out);
    }
  }
  {
    return arch_x86_64_emit_section_text(out);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_globl(uint8_t * out, uint8_t * name, int32_t name_len, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_globl(out, name, name_len);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_globl(out, name, name_len);
    }
  }
  {
    return arch_x86_64_emit_globl(out, name, name_len);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_prologue(uint8_t * out, int32_t frame_sz, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_prologue(out, frame_sz);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_prologue(out, frame_sz);
    }
  }
  {
    return arch_x86_64_emit_prologue(out, frame_sz);
  }
  return (0 - 1);
}
int32_t backend_arch_emit_epilogue(uint8_t * out, int32_t frame_sz, int32_t ta) {
  if ((ta ==1)) {
    {
      return arch_arm64_emit_epilogue(out, frame_sz);
    }
  }
  if ((ta ==2)) {
    {
      return arch_riscv64_emit_epilogue(out, frame_sz);
    }
  }
  {
    return arch_x86_64_emit_epilogue(out, frame_sz);
  }
  return (0 - 1);
}
