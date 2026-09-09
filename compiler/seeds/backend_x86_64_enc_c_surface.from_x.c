/* seeds/backend_x86_64_enc_c_surface.from_x.c
 * G-02f backend_x86_64_enc_c R2 mixed surface - isomorphic with src/asm/backend_x86_64_enc_c.x
 * Product PREFER_X_O: xlang-c -E(.x) -> thin.o + ld -r with rest (seeds/backend_x86_64_enc_c.from_x.c)
 * Prove: full.x vs this surface -> nm IDENTICAL (104 symbols)
 * Mode: mixed - 104 DIRECT compute (no thin+rest _impl forwards); bridge calls to pipeline_elf_ctx_*
 * Cap residual: 9 pipeline_elf_ctx_* bridges (emit context providers, defined in pipeline rest C)
 * doc_anchor: backend_x86_64_enc_c_x_doc_anchor (defined here, returns 0).
 * Logic: 104 functions = 104 DIRECT compute
 *   (x86_enc_u8/bytes/u32_le/jcc_rel32/append_i32_le/movq/lea/movl/store_rax/store_rdx/alu_imm32
 *    + 92 arch_x86_64_enc_enc_* + backend_x86_64_enc_c_x_doc_anchor).
 *   Bridges: pipeline_elf_ctx_append_bytes, pipeline_elf_ctx_emit_code_len,
 *   pipeline_elf_ctx_ensure_label, pipeline_elf_ctx_append_patch,
 *   pipeline_elf_ctx_append_reloc, pipeline_elf_ctx_add_label,
 *   pipeline_elf_ctx_pad_code_to_4, pipeline_elf_ctx_add_sym,
 *   pipeline_elf_ctx_macho_leading_underscore.
 * Regen: xlang_asm -E src/asm/backend_x86_64_enc_c.x | filter DBG + polish prologue
 */
#include <stdint.h>
#include <stddef.h>
/* Forward declarations for all 104 surface functions (nm IDENTICAL targets). */
extern int32_t backend_x86_64_enc_c_x_doc_anchor(void);
extern int32_t x86_enc_u8(uint8_t * elf_ctx, uint8_t b);
extern int32_t x86_enc_bytes(uint8_t * elf_ctx, uint8_t * buf, int32_t n);
extern int32_t x86_enc_u32_le(uint8_t * elf_ctx, int32_t imm);
extern int32_t x86_enc_jcc_rel32(uint8_t * elf_ctx, uint8_t opcode2, uint8_t * label, int32_t label_len);
extern int32_t backend_x86_64_enc_c_x86_enc_append_i32_le(uint8_t * elf_ctx, int32_t v);
extern int32_t x86_enc_movq_from_rbp_neg(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_lea_from_rbp_neg(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_movl_from_rbp_neg32(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_store_rax_to_rbp_neg(uint8_t * elf_ctx, int32_t offset);
extern int32_t x86_enc_store_rdx_to_rbp_neg(uint8_t * elf_ctx, int32_t offset);
extern int32_t x86_enc_alu_imm32_to_reg(uint8_t * elf_ctx, int32_t imm, uint8_t op_prefix, uint8_t reg_modrm);
extern int32_t arch_x86_64_enc_enc_prologue(uint8_t * elf_ctx, int32_t frame_size);
extern int32_t arch_x86_64_enc_enc_epilogue(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_and_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_or_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_xor_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_mov_edx_to_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_not_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_neg_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_test_eax_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_test_rbx_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_test_edx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cmp_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cmp_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_cltd(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_idiv_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_rbx_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_push_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_push_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_pop_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_pop_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shl_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shr_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sar_cl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shl_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_shr_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sar_cl_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_xor_edx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_div_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_32_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_64_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_zext8_from_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale1(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale8(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_add_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_imul_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_rax_rbx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rsub_ecx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_rsub_ebx_edx(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_setz_movzbl_eax(uint8_t * elf_ctx);
extern int32_t arch_x86_64_enc_enc_label(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func);
extern int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(uint8_t * elf_ctx, int32_t cc);
extern int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_x86_64_enc_enc_ret_imm32(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(uint8_t * elf_ctx, int32_t lo, int32_t hi);
extern int32_t arch_x86_64_enc_enc_cmp_eax_imm32(uint8_t * elf_ctx, int32_t imm32);
extern int32_t arch_x86_64_enc_enc_add_imm_to_rax(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_add_imm_to_rbx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbp(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_lea_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_pos_to_rax(uint8_t * elf_ctx, int32_t off_pos);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_eax32(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_ebx32(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_ecx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_edx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_add_imm_to_ecx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_sub_imm_from_ecx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_add_imm_to_ebx_index(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_sub_imm_from_ebx_index(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_imul_imm_to_ecx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_imul_imm_to_ebx(uint8_t * elf_ctx, int32_t imm);
extern int32_t arch_x86_64_enc_enc_mov_arg_reg_to_rax(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k);
extern int32_t arch_x86_64_enc_enc_jz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jeq(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jge(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jnz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_jmp(uint8_t * elf_ctx, uint8_t * label, int32_t label_len);
extern int32_t arch_x86_64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len);
extern int32_t arch_x86_64_enc_enc_add_rsp_imm(uint8_t * elf_ctx, int32_t nbytes);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbx_indirect(uint8_t * elf_ctx, int32_t elem_sz);
extern int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(uint8_t * elf_ctx, int32_t offset, int32_t store_size);
extern int32_t arch_x86_64_enc_enc_store_rdx_to_rbp(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_load_rbp_to_rdx(uint8_t * elf_ctx, int32_t offset);
extern int32_t arch_x86_64_enc_enc_mov_rdx_to_arg_reg(uint8_t * elf_ctx, int32_t k);
/* Cap residual: 9 pipeline_elf_ctx_* bridges (emit context providers, defined in pipeline rest C). */
extern int32_t pipeline_elf_ctx_append_bytes(uint8_t * ctx, uint8_t * ptr, int32_t n);
extern int32_t pipeline_elf_ctx_emit_code_len(uint8_t * ctx);
extern int32_t pipeline_elf_ctx_ensure_label(uint8_t * ctx, uint8_t * name, int32_t name_len);
extern int32_t pipeline_elf_ctx_append_patch(uint8_t * ctx, int32_t rel32_offset, uint8_t * name, int32_t name_len, int32_t imm_bits);
extern int32_t pipeline_elf_ctx_append_reloc(uint8_t * ctx, int32_t offset, uint8_t * name, int32_t name_len);
extern int32_t pipeline_elf_ctx_add_label(uint8_t * ctx, uint8_t * name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_pad_code_to_4(uint8_t * ctx);
extern int32_t pipeline_elf_ctx_add_sym(uint8_t * ctx, uint8_t * name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_macho_leading_underscore(uint8_t * ctx);
int32_t backend_x86_64_enc_c_x_doc_anchor(void) {
  return 0;
}
int32_t x86_enc_u8(uint8_t * elf_ctx, uint8_t b) {
  uint8_t bb = b;
  return pipeline_elf_ctx_append_bytes(elf_ctx, &(bb), 1);
  return -1;
}
int32_t x86_enc_bytes(uint8_t * elf_ctx, uint8_t * buf, int32_t n) {
  return pipeline_elf_ctx_append_bytes(elf_ctx, buf, n);
  return -1;
}
int32_t x86_enc_u32_le(uint8_t * elf_ctx, int32_t imm) {
  uint32_t w = ((uint32_t)(imm));
  uint8_t b0 = ((uint8_t)((w & 255)));
  uint8_t b1 = ((uint8_t)(((w / 256) & 255)));
  uint8_t b2 = ((uint8_t)(((w / 65536) & 255)));
  uint8_t b3 = ((uint8_t)(((w / 16777216) & 255)));
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b0), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b1), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b2), 1) !=0)) {
    return -1;
  }
  return pipeline_elf_ctx_append_bytes(elf_ctx, &(b3), 1);
  return -1;
}
int32_t x86_enc_jcc_rel32(uint8_t * elf_ctx, uint8_t opcode2, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((label ==0)) {
    return -1;
  }
  if ((label_len <=0)) {
    return -1;
  }
  uint8_t b0 = 15;
  uint8_t b1 = opcode2;
  uint8_t z = 0;
  /* Dual-authority mirror of backend_x86_64_enc_c.x x86_enc_jcc_rel32:
   * append jcc skeleton first, then rel32_at = emit_code_len()-4.
   * Same-block let hoist of emit_code_len()-4 before appends corrupts prior
   * insns (Ubuntu option SIGILL / stdlib-import SEGV). PLATFORM: SHARED x86_64. */
  {
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b0), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b1), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(z), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(z), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(z), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(z), 1) !=0)) {
      return -1;
    }
  }
  {
    int32_t rel32_at = (pipeline_elf_ctx_emit_code_len(elf_ctx) - 4);
    if ((pipeline_elf_ctx_ensure_label(elf_ctx, label, label_len) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_patch(elf_ctx, rel32_at, label, label_len, 0);
  }
  return -1;
}
int32_t backend_x86_64_enc_c_x86_enc_append_i32_le(uint8_t * elf_ctx, int32_t v) {
  uint32_t w = ((uint32_t)(v));
  uint8_t b0 = ((uint8_t)((w & 255)));
  uint8_t b1 = ((uint8_t)(((w / 256) & 255)));
  uint8_t b2 = ((uint8_t)(((w / 65536) & 255)));
  uint8_t b3 = ((uint8_t)(((w / 16777216) & 255)));
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b0), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b1), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(b2), 1) !=0)) {
    return -1;
  }
  return pipeline_elf_ctx_append_bytes(elf_ctx, &(b3), 1);
  return -1;
}
int32_t x86_enc_movq_from_rbp_neg(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp = (0 - offset);
  uint8_t r64 = 72;
  uint8_t op = 139;
  if (((disp >=-128) && (disp <=-1))) {
    uint8_t d8 = ((uint8_t)(disp));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp8_modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp32_modrm), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, disp);
}
int32_t x86_enc_lea_from_rbp_neg(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp = (0 - offset);
  uint8_t r64 = 72;
  uint8_t op = 141;
  if (((disp >=-128) && (disp <=-1))) {
    uint8_t d8 = ((uint8_t)(disp));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp8_modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp32_modrm), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, disp);
}
int32_t x86_enc_movl_from_rbp_neg32(uint8_t * elf_ctx, int32_t offset, uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp = (0 - offset);
  uint8_t op = 139;
  if (((disp >=-128) && (disp <=-1))) {
    uint8_t d8 = ((uint8_t)(disp));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp8_modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(disp32_modrm), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, disp);
}
int32_t x86_enc_store_rax_to_rbp_neg(uint8_t * elf_ctx, int32_t offset) {
  int32_t disp = (0 - offset);
  uint8_t r64 = 72;
  uint8_t op = 137;
  if (((disp >=-128) && (disp <=-1))) {
    uint8_t modrm = 69;
    uint8_t d8 = ((uint8_t)(disp));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  uint8_t modrm32 = 133;
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(modrm32), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, disp);
}
int32_t x86_enc_store_rdx_to_rbp_neg(uint8_t * elf_ctx, int32_t offset) {
  int32_t disp = (0 - offset);
  uint8_t r64 = 72;
  uint8_t op = 137;
  if (((disp >=-128) && (disp <=-1))) {
    uint8_t modrm = 85;
    uint8_t d8 = ((uint8_t)(disp));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  uint8_t modrm32 = 149;
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(r64), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(modrm32), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, disp);
}
int32_t x86_enc_alu_imm32_to_reg(uint8_t * elf_ctx, int32_t imm, uint8_t op_prefix, uint8_t reg_modrm) {
  if ((imm ==0)) {
    return 0;
  }
  if (((imm >=-128) && (imm <=127))) {
    uint8_t op83 = 131;
    uint8_t d8 = ((uint8_t)(imm));
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op83), 1) !=0)) {
      return -1;
    }
    if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(reg_modrm), 1) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &(d8), 1);
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(op_prefix), 1) !=0)) {
    return -1;
  }
  if ((pipeline_elf_ctx_append_bytes(elf_ctx, &(reg_modrm), 1) !=0)) {
    return -1;
  }
  return backend_x86_64_enc_c_x86_enc_append_i32_le(elf_ctx, imm);
}
int32_t arch_x86_64_enc_enc_prologue(uint8_t * elf_ctx, int32_t frame_size) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 85) !=0)) {
    return -1;
  }
  uint8_t mov[3] = {72, 137, 229};
  if ((x86_enc_bytes(elf_ctx, mov, 3) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 83) !=0)) {
    return -1;
  }
  /* SysV 16B: after push rbp+rbx, pad sub imm to ≡8 mod 16 (see .x authority). */
  int32_t fs_i = frame_size;
  int32_t rem;
  if (fs_i < 0) fs_i = 0;
  rem = fs_i % 16;
  if (rem != 8) {
    if (rem < 8) fs_i = fs_i + (8 - rem);
    else fs_i = fs_i + (16 - rem + 8);
  }
  uint8_t sub[7] = {72, 129, 236, 0, 0, 0, 0};
  uint32_t fs = ((uint32_t)(fs_i));
  (void)(((sub)[3] = ((uint8_t)((fs & 255)))));
  (void)(((sub)[4] = ((uint8_t)(((fs / 256) & 255)))));
  (void)(((sub)[5] = ((uint8_t)(((fs / 65536) & 255)))));
  (void)(((sub)[6] = ((uint8_t)(((fs / 16777216) & 255)))));
  return x86_enc_bytes(elf_ctx, sub, 7);
}
int32_t arch_x86_64_enc_enc_epilogue(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t lea[4] = {72, 141, 101, 248};
  if ((x86_enc_bytes(elf_ctx, lea, 4) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 91) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 93) !=0)) {
    return -1;
  }
  return x86_enc_u8(elf_ctx, 195);
}
int32_t arch_x86_64_enc_enc_add_rax_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 1, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_and_rbx_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 33, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_or_rbx_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 9, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_xor_rbx_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 49, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 137, 195};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 137, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {137, 217};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_mov_edx_to_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {137, 208};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_not_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {247, 208};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_neg_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {247, 216};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_test_eax_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {133, 192};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_test_rbx_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {133, 219};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_test_edx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {133, 210};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_cmp_rbx_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {57, 195};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_cmp_rax_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {57, 216};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_cltd(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[1] = {153};
  return x86_enc_bytes(elf_ctx, ins, 1);
}
int32_t arch_x86_64_enc_enc_idiv_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {247, 251};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_imul_rbx_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 15, 175, 195};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_push_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[1] = {80};
  return x86_enc_bytes(elf_ctx, ins, 1);
}
int32_t arch_x86_64_enc_enc_push_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[1] = {83};
  return x86_enc_bytes(elf_ctx, ins, 1);
}
int32_t arch_x86_64_enc_enc_pop_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[1] = {91};
  return x86_enc_bytes(elf_ctx, ins, 1);
}
int32_t arch_x86_64_enc_enc_pop_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[1] = {88};
  return x86_enc_bytes(elf_ctx, ins, 1);
}
int32_t arch_x86_64_enc_enc_shl_cl_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {211, 224};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_shr_cl_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {211, 232};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_sar_cl_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {211, 248};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_shl_cl_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 211, 224};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_shr_cl_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 211, 232};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_sar_cl_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 211, 248};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_xor_edx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {49, 210};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_div_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {247, 243};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_load_32_from_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {139, 0};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_load_64_from_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 139, 0};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_load_zext8_from_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {15, 182, 0};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale1(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 4, 24};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 4, 152};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale8(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 4, 216};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 28, 11};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 28, 139};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 141, 28, 203};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_add_ecx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {1, 209};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_sub_ecx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {41, 209};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_add_ebx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {1, 211};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
int32_t arch_x86_64_enc_enc_sub_ebx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[2] = {41, 211};
  return x86_enc_bytes(elf_ctx, ins, 2);
}
/* Wave184: IMUL ecx,edx (0xCA) — primary *= secondary; was 0xD1 product-in-edx. */
int32_t arch_x86_64_enc_enc_imul_ecx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {15, 175, 202};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
/* Wave184: IMUL ebx,edx (0xDA) — rbx *= secondary; was 0xD3 product-in-edx. */
int32_t arch_x86_64_enc_enc_imul_ebx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {15, 175, 218};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_sub_rax_rbx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 41, 216};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[3] = {72, 139, 3};
  return x86_enc_bytes(elf_ctx, ins, 3);
}
int32_t arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins[4] = {72, 139, 83, 8};
  return x86_enc_bytes(elf_ctx, ins, 4);
}
int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins0[3] = {72, 41, 195};
  if ((x86_enc_bytes(elf_ctx, ins0, 3) !=0)) {
    return -1;
  }
  uint8_t ins1[3] = {72, 137, 216};
  return x86_enc_bytes(elf_ctx, ins1, 3);
}
int32_t arch_x86_64_enc_enc_rsub_ecx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins0[2] = {41, 202};
  if ((x86_enc_bytes(elf_ctx, ins0, 2) !=0)) {
    return -1;
  }
  uint8_t ins1[2] = {137, 209};
  return x86_enc_bytes(elf_ctx, ins1, 2);
}
int32_t arch_x86_64_enc_enc_rsub_ebx_edx(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins0[2] = {41, 218};
  if ((x86_enc_bytes(elf_ctx, ins0, 2) !=0)) {
    return -1;
  }
  uint8_t ins1[2] = {137, 211};
  return x86_enc_bytes(elf_ctx, ins1, 2);
}
int32_t arch_x86_64_enc_enc_setz_movzbl_eax(uint8_t * elf_ctx) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t ins0[3] = {15, 148, 192};
  if ((x86_enc_bytes(elf_ctx, ins0, 3) !=0)) {
    return -1;
  }
  uint8_t ins1[3] = {15, 182, 192};
  return x86_enc_bytes(elf_ctx, ins1, 3);
}
/* Ordering contract: pad_code_to_4 BEFORE emit_code_len (same as .x authority).
 * pass0 hoist of emit_code_len before pad → sym points at zero pad → multi-func SEGV.
 * PLATFORM: SHARED — dual-authority with backend_x86_64_enc_c.x arch_x86_64_enc_enc_label. */
int32_t arch_x86_64_enc_enc_label(uint8_t * elf_ctx, uint8_t * name, int32_t name_len, int32_t is_func) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((name ==0)) {
    return -1;
  }
  if ((name_len < 0)) {
    return -1;
  }
  /* Block 1: pad only. */
  if ((is_func !=0)) {
    if ((pipeline_elf_ctx_pad_code_to_4(elf_ctx) !=0)) {
      return -1;
    }
  }
  /* Block 2: capture code_len after pad; register label + optional export sym. */
  {
    int32_t code_len = pipeline_elf_ctx_emit_code_len(elf_ctx);
    if ((pipeline_elf_ctx_add_label(elf_ctx, name, name_len, code_len) !=0)) {
      return -1;
    }
    if ((is_func ==0)) {
      return 0;
    }
    /* wave580 Cap: mn u8[128] holds '_' + up to 127 content (was 63). PLATFORM: MACOS|DARWIN. */
    if (((((pipeline_elf_ctx_macho_leading_underscore(elf_ctx) !=0) && (name_len > 0)) && (name_len <=127)) && ((name)[0] !=95))) {
      uint8_t mn[128] = {0};
      (void)(((mn)[0] = 95));
      int32_t k = 0;
      while (((k < name_len) && (k < 127))) {
        (void)(((mn)[(k + 1)] = (name)[k]));
        (void)((k = (k + 1)));
      }
      int32_t code_len2 = pipeline_elf_ctx_emit_code_len(elf_ctx);
      return pipeline_elf_ctx_add_sym(elf_ctx, &((mn)[0]), (name_len + 1), code_len2);
    }
    int32_t code_len3 = pipeline_elf_ctx_emit_code_len(elf_ctx);
    return pipeline_elf_ctx_add_sym(elf_ctx, name, name_len, code_len3);
  }
  return -1;
}
int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(uint8_t * elf_ctx, int32_t cc) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint8_t op = 148;
  if ((cc ==1)) {
    (void)((op = 149));
  } else {
    if ((cc ==2)) {
      (void)((op = 156));
    } else {
      if ((cc ==3)) {
        (void)((op = 158));
      } else {
        if ((cc ==4)) {
          (void)((op = 159));
        } else {
          if ((cc ==5)) {
            (void)((op = 157));
          } else {
            if ((cc ==6)) {
              (void)((op = 146));
            } else {
              if ((cc ==7)) {
                (void)((op = 150));
              } else {
                if ((cc ==8)) {
                  (void)((op = 151));
                } else {
                  if ((cc ==9)) {
                    (void)((op = 147));
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uint8_t s[3] = {15, 0, 192};
  (void)(((s)[1] = op));
  if ((x86_enc_bytes(elf_ctx, s, 3) !=0)) {
    return -1;
  }
  uint8_t m[3] = {15, 182, 192};
  return x86_enc_bytes(elf_ctx, m, 3);
}
int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(uint8_t * elf_ctx, int32_t imm32) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 187) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, imm32);
}
int32_t arch_x86_64_enc_enc_ret_imm32(uint8_t * elf_ctx, int32_t imm32) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 184) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, imm32);
}
int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(uint8_t * elf_ctx, int32_t lo, int32_t hi) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 72) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 184) !=0)) {
    return -1;
  }
  if ((x86_enc_u32_le(elf_ctx, lo) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, hi);
}
int32_t arch_x86_64_enc_enc_cmp_eax_imm32(uint8_t * elf_ctx, int32_t imm32) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 61) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, imm32);
}
int32_t arch_x86_64_enc_enc_add_imm_to_rax(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((imm ==0)) {
    return 0;
  }
  if ((x86_enc_u8(elf_ctx, 72) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 5) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, imm);
}
int32_t arch_x86_64_enc_enc_add_imm_to_rbx(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((imm ==0)) {
    return 0;
  }
  if ((x86_enc_u8(elf_ctx, 72) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 129) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 195) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, imm);
}
int32_t arch_x86_64_enc_enc_store_rax_to_rbp(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_store_rax_to_rbp_neg(elf_ctx, offset);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_rax(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 69, 133);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 93, 157);
}
int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 69, 133);
}
int32_t arch_x86_64_enc_enc_lea_rbp_to_rbx(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 93, 157);
}
int32_t arch_x86_64_enc_enc_load_rbp_pos_to_rax(uint8_t * elf_ctx, int32_t off_pos) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  int32_t disp = off_pos;
  if ((disp < 0)) {
    (void)((disp = 0));
  }
  if ((disp <=127)) {
    uint8_t buf[4] = {72, 139, 69, 0};
    (void)(((buf)[3] = ((uint8_t)(disp))));
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  uint8_t buf2[7] = {72, 139, 133, 0, 0, 0, 0};
  uint32_t w = ((uint32_t)(disp));
  (void)(((buf2)[3] = ((uint8_t)((w & 255)))));
  (void)(((buf2)[4] = ((uint8_t)(((w / 256) & 255)))));
  (void)(((buf2)[5] = ((uint8_t)(((w / 65536) & 255)))));
  (void)(((buf2)[6] = ((uint8_t)(((w / 16777216) & 255)))));
  return x86_enc_bytes(elf_ctx, buf2, 7);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_eax32(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 69, 133);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_ebx32(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 93, 157);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_ecx(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 77, 141);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_edx(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 85, 149);
}
int32_t arch_x86_64_enc_enc_add_imm_to_ecx(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 193);
}
int32_t arch_x86_64_enc_enc_sub_imm_from_ecx(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 233);
}
int32_t arch_x86_64_enc_enc_add_imm_to_ebx_index(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 195);
}
int32_t arch_x86_64_enc_enc_sub_imm_from_ebx_index(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 235);
}
int32_t arch_x86_64_enc_enc_imul_imm_to_ecx(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((imm <=1)) {
    return 0;
  }
  if (((imm >=-128) && (imm <=127))) {
    uint8_t buf[3] = {107, 201, 0};
    (void)(((buf)[2] = ((uint8_t)(imm))));
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  uint8_t buf2[6] = {105, 201, 0, 0, 0, 0};
  uint32_t w = ((uint32_t)(imm));
  (void)(((buf2)[2] = ((uint8_t)((w & 255)))));
  (void)(((buf2)[3] = ((uint8_t)(((w / 256) & 255)))));
  (void)(((buf2)[4] = ((uint8_t)(((w / 65536) & 255)))));
  (void)(((buf2)[5] = ((uint8_t)(((w / 16777216) & 255)))));
  return x86_enc_bytes(elf_ctx, buf2, 6);
}
int32_t arch_x86_64_enc_enc_imul_imm_to_ebx(uint8_t * elf_ctx, int32_t imm) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((imm <=1)) {
    return 0;
  }
  if (((imm >=-128) && (imm <=127))) {
    uint8_t buf[3] = {107, 219, 0};
    (void)(((buf)[2] = ((uint8_t)(imm))));
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  uint8_t buf2[6] = {105, 219, 0, 0, 0, 0};
  uint32_t w = ((uint32_t)(imm));
  (void)(((buf2)[2] = ((uint8_t)((w & 255)))));
  (void)(((buf2)[3] = ((uint8_t)(((w / 256) & 255)))));
  (void)(((buf2)[4] = ((uint8_t)(((w / 65536) & 255)))));
  (void)(((buf2)[5] = ((uint8_t)(((w / 16777216) & 255)))));
  return x86_enc_bytes(elf_ctx, buf2, 6);
}
int32_t arch_x86_64_enc_enc_mov_arg_reg_to_rax(uint8_t * elf_ctx, int32_t k) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  int32_t idx = k;
  if ((idx < 0)) {
    (void)((idx = 0));
  }
  if ((idx > 5)) {
    (void)((idx = 5));
  }
  if ((idx ==0)) {
    uint8_t b0[3] = {72, 137, 248};
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if ((idx ==1)) {
    uint8_t b1[3] = {72, 137, 240};
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if ((idx ==2)) {
    uint8_t b2[3] = {72, 137, 208};
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if ((idx ==3)) {
    uint8_t b3[3] = {72, 137, 200};
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if ((idx ==4)) {
    uint8_t b4[3] = {76, 137, 192};
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  uint8_t b5[3] = {76, 137, 200};
  return x86_enc_bytes(elf_ctx, b5, 3);
}
int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(uint8_t * elf_ctx, int32_t k) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  int32_t idx = k;
  if ((idx < 0)) {
    (void)((idx = 0));
  }
  if ((idx > 5)) {
    (void)((idx = 5));
  }
  if ((idx ==0)) {
    uint8_t b0[3] = {72, 137, 199};
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if ((idx ==1)) {
    uint8_t b1[3] = {72, 137, 198};
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if ((idx ==2)) {
    uint8_t b2[3] = {72, 137, 194};
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if ((idx ==3)) {
    uint8_t b3[3] = {72, 137, 193};
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if ((idx ==4)) {
    uint8_t b4[3] = {73, 137, 192};
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  uint8_t b5[3] = {73, 137, 193};
  return x86_enc_bytes(elf_ctx, b5, 3);
}
int32_t arch_x86_64_enc_enc_jz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}
int32_t arch_x86_64_enc_enc_jeq(uint8_t * elf_ctx, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}
int32_t arch_x86_64_enc_enc_jge(uint8_t * elf_ctx, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_jcc_rel32(elf_ctx, 141, label, label_len);
}
int32_t arch_x86_64_enc_enc_jnz(uint8_t * elf_ctx, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_jcc_rel32(elf_ctx, 133, label, label_len);
}
int32_t arch_x86_64_enc_enc_jmp(uint8_t * elf_ctx, uint8_t * label, int32_t label_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((label ==0)) {
    return -1;
  }
  if ((label_len <=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 233) !=0)) {
    return -1;
  }
  if ((x86_enc_u32_le(elf_ctx, 0) !=0)) {
    return -1;
  }
  {
    int32_t rel32_at = (pipeline_elf_ctx_emit_code_len(elf_ctx) - 4);
    if ((pipeline_elf_ctx_ensure_label(elf_ctx, label, label_len) !=0)) {
      return -1;
    }
    return pipeline_elf_ctx_append_patch(elf_ctx, rel32_at, label, label_len, 0);
  }
  return -1;
}
int32_t arch_x86_64_enc_enc_call(uint8_t * elf_ctx, uint8_t * name, int32_t name_len) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((name ==0)) {
    return -1;
  }
  if ((name_len <=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 232) !=0)) {
    return -1;
  }
  if ((x86_enc_u32_le(elf_ctx, 0) !=0)) {
    return -1;
  }
  {
    int32_t rel32_at = (pipeline_elf_ctx_emit_code_len(elf_ctx) - 4);
    /* wave580 Cap: rn u8[128] holds '_' + up to 127 content (was 63). PLATFORM: MACOS|DARWIN.
     * Stage 12.0.5 ABI: always prepend '_' even when C name starts with '_'
     * (__error → ___error). Do not skip on name[0]=='_'. */
    if (((((pipeline_elf_ctx_macho_leading_underscore(elf_ctx) !=0) && (name_len > 0)) && (name_len <=127)))) {
      uint8_t rn[128] = {0};
      (void)(((rn)[0] = 95));
      int32_t k = 0;
      while (((k < name_len) && (k < 127))) {
        (void)(((rn)[(k + 1)] = (name)[k]));
        (void)((k = (k + 1)));
      }
      return pipeline_elf_ctx_append_reloc(elf_ctx, rel32_at, &((rn)[0]), (name_len + 1));
    }
    return pipeline_elf_ctx_append_reloc(elf_ctx, rel32_at, name, name_len);
  }
  return -1;
}
int32_t arch_x86_64_enc_enc_add_rsp_imm(uint8_t * elf_ctx, int32_t nbytes) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((nbytes <=0)) {
    return 0;
  }
  if ((nbytes <=127)) {
    if ((x86_enc_u8(elf_ctx, 72) !=0)) {
      return -1;
    }
    if ((x86_enc_u8(elf_ctx, 131) !=0)) {
      return -1;
    }
    if ((x86_enc_u8(elf_ctx, 196) !=0)) {
      return -1;
    }
    return x86_enc_u8(elf_ctx, ((uint8_t)(nbytes)));
  }
  if ((x86_enc_u8(elf_ctx, 72) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 129) !=0)) {
    return -1;
  }
  if ((x86_enc_u8(elf_ctx, 196) !=0)) {
    return -1;
  }
  return x86_enc_u32_le(elf_ctx, nbytes);
}
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_indirect(uint8_t * elf_ctx, int32_t elem_sz) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  if ((elem_sz ==1)) {
    uint8_t b1[2] = {136, 3};
    return x86_enc_bytes(elf_ctx, b1, 2);
  }
  if ((elem_sz ==4)) {
    uint8_t b4[2] = {137, 3};
    return x86_enc_bytes(elf_ctx, b4, 2);
  }
  uint8_t b8[3] = {72, 137, 3};
  return x86_enc_bytes(elf_ctx, b8, 3);
}
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(uint8_t * elf_ctx, int32_t offset, int32_t store_size) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  uint32_t w = ((uint32_t)(offset));
  uint8_t b0 = ((uint8_t)((w & 255)));
  uint8_t b1 = ((uint8_t)(((w / 256) & 255)));
  uint8_t b2 = ((uint8_t)(((w / 65536) & 255)));
  uint8_t b3 = ((uint8_t)(((w / 16777216) & 255)));
  if ((store_size ==1)) {
    uint8_t buf[6] = {136, 131, 0, 0, 0, 0};
    (void)(((buf)[2] = b0));
    (void)(((buf)[3] = b1));
    (void)(((buf)[4] = b2));
    (void)(((buf)[5] = b3));
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  if ((store_size ==4)) {
    uint8_t buf[6] = {137, 131, 0, 0, 0, 0};
    (void)(((buf)[2] = b0));
    (void)(((buf)[3] = b1));
    (void)(((buf)[4] = b2));
    (void)(((buf)[5] = b3));
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  uint8_t buf8[7] = {72, 137, 131, 0, 0, 0, 0};
  (void)(((buf8)[3] = b0));
  (void)(((buf8)[4] = b1));
  (void)(((buf8)[5] = b2));
  (void)(((buf8)[6] = b3));
  return x86_enc_bytes(elf_ctx, buf8, 7);
}
int32_t arch_x86_64_enc_enc_store_rdx_to_rbp(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_store_rdx_to_rbp_neg(elf_ctx, offset);
}
int32_t arch_x86_64_enc_enc_load_rbp_to_rdx(uint8_t * elf_ctx, int32_t offset) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 85, 149);
}
int32_t arch_x86_64_enc_enc_mov_rdx_to_arg_reg(uint8_t * elf_ctx, int32_t k) {
  if ((elf_ctx ==0)) {
    return -1;
  }
  int32_t idx = k;
  if ((idx < 0)) {
    (void)((idx = 0));
  }
  if ((idx > 5)) {
    (void)((idx = 5));
  }
  if ((idx ==0)) {
    uint8_t b0[3] = {72, 137, 215};
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if ((idx ==1)) {
    uint8_t b1[3] = {72, 137, 214};
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if ((idx ==2)) {
    uint8_t b2[3] = {72, 137, 210};
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if ((idx ==3)) {
    uint8_t b3[3] = {72, 137, 209};
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if ((idx ==4)) {
    uint8_t b4[3] = {73, 137, 208};
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  uint8_t b5[3] = {73, 137, 209};
  return x86_enc_bytes(elf_ctx, b5, 3);
}
