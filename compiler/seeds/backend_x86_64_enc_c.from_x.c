/* seeds/backend_x86_64_enc_c.from_x.c
 * G-02f-130 true .x pure helpers.
 * G-02f-129 true .x pure helpers.
 * G-02f-128 true .x pure helpers.
 * G-02f-124 true .x pure helpers.
 * G-02f-102 helper gates.
 * G-02f-101 x86 enc helper gates. — G-02f-15 product TU
 * Product object from this seed; logic still C until full .x port.
 */
/**
 * backend_x86_64_enc_c.c — x86_64 ELF 指令编码 C 体（覆盖 asm_full_link_stubs weak -1）
 *
 * M8 自举 USER_ASM_LINK 链仅 partial+stubs，未链 x86_64_enc.o；强符号在此提供，
 * 端口 arch/x86_64_enc.x。
 */
#include <stdint.h>
#include <string.h>

struct platform_elf_ElfCodegenCtx;

extern int32_t pipeline_elf_ctx_append_bytes(uint8_t *ctx_bytes, uint8_t *ptr, int32_t n);
extern int32_t pipeline_elf_ctx_emit_code_len(uint8_t *ctx_bytes);
extern int32_t pipeline_elf_ctx_ensure_label(uint8_t *ctx_bytes, uint8_t *name, int32_t name_len);
extern int32_t pipeline_elf_ctx_append_patch(uint8_t *ctx_bytes, int32_t rel32_offset, uint8_t *name, int32_t name_len,
                                              int32_t imm_bits);
extern int32_t pipeline_elf_ctx_append_reloc(uint8_t *ctx_bytes, int32_t offset, uint8_t *name, int32_t name_len);
extern int32_t pipeline_elf_ctx_add_label(uint8_t *ctx_bytes, uint8_t *name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_pad_code_to_4(uint8_t *ctx_bytes);
extern int32_t pipeline_elf_ctx_add_sym(uint8_t *ctx_bytes, uint8_t *name, int32_t name_len, int32_t offset);
extern int32_t pipeline_elf_ctx_macho_leading_underscore(uint8_t *ctx_bytes);

/* G-02f-441：thin+rest PREFER_X_O — common 函数由 .x -E 提供 thin .o；
 * rest .o 编译时定义 XLANG_BACKEND_X86_64_ENC_C_FROM_X 跳过 common 定义。 */
extern int32_t x86_enc_u8(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t b);
extern int32_t x86_enc_u32_le(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm);
extern int32_t x86_enc_bytes(struct platform_elf_ElfCodegenCtx *elf_ctx, const uint8_t *buf, int32_t n);
extern int32_t x86_enc_jcc_rel32(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t opcode2, uint8_t *label,
                                 int32_t label_len);
extern int32_t x86_enc_movq_from_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                         uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_lea_from_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                        uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_movl_from_rbp_neg32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                           uint8_t disp8_modrm, uint8_t disp32_modrm);
extern int32_t x86_enc_store_rax_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset);
extern int32_t x86_enc_store_r64_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg, int32_t offset);
extern int32_t x86_enc_alu_imm32_to_reg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm, uint8_t op_prefix,
                                        uint8_t reg_modrm);
extern int32_t x86_enc_store_rdx_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset);

/** 取 ElfCodegenCtx 字节视图。 */
static uint8_t *x86_enc_ctx_bytes(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  return (uint8_t *)elf_ctx;
}

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/** 追加 1 字节机器码。 */
/* G-02f-124：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_u8(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t b) {
  return pipeline_elf_ctx_append_bytes(x86_enc_ctx_bytes(elf_ctx), &b, 1);
}




/** 追加 imm32 小端。 */
/* G-02f-128：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_u32_le(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  uint8_t buf[4];
  buf[0] = (uint8_t)(imm & 255);
  buf[1] = (uint8_t)((imm >> 8) & 255);
  buf[2] = (uint8_t)((imm >> 16) & 255);
  buf[3] = (uint8_t)((imm >> 24) & 255);
  return pipeline_elf_ctx_append_bytes(x86_enc_ctx_bytes(elf_ctx), buf, 4);
}


/** 追加固定字节序列。 */
/* G-02f-124：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_bytes(struct platform_elf_ElfCodegenCtx *elf_ctx, const uint8_t *buf, int32_t n) {
  return pipeline_elf_ctx_append_bytes(x86_enc_ctx_bytes(elf_ctx), (uint8_t *)buf, n);
}


#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#define X86_ENC_FIXED(ctx, arr) x86_enc_bytes((ctx), (const uint8_t *)(arr), (int32_t)sizeof(arr))

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/** x86 rel32 条件跳转 + patch（与 x86_64_enc.x enc_jz/enc_jge 一致）。 */
/* G-02f-129：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_jcc_rel32(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t opcode2, uint8_t *label,
                                 int32_t label_len) {
  uint8_t buf[6];
  int32_t rel32_at;
  uint8_t *cb;
  if (!elf_ctx || !label || label_len <= 0)
    return -1;
  cb = x86_enc_ctx_bytes(elf_ctx);
  buf[0] = 0x0F;
  buf[1] = opcode2;
  buf[2] = buf[3] = buf[4] = buf[5] = 0;
  if (pipeline_elf_ctx_append_bytes(cb, buf, 6) != 0)
    return -1;
  rel32_at = pipeline_elf_ctx_emit_code_len(cb) - 4;
  if (pipeline_elf_ctx_ensure_label(cb, label, label_len) != 0)
    return -1;
  return pipeline_elf_ctx_append_patch(cb, rel32_at, label, label_len, 0);
}


/** movq -offset(%rbp), %reg：modrm_reg 为 disp8 第三字节（69=rax, 93=rbx 等）。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_movq_from_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                         uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp;
  uint8_t buf[7];
  disp = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    buf[0] = 72;
    buf[1] = 0x8B;
    buf[2] = disp8_modrm;
    buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[0] = 72;
  buf[1] = 0x8B;
  buf[2] = disp32_modrm;
  buf[3] = (uint8_t)(disp & 255);
  buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255);
  buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);

}


/** leaq -offset(%rbp), %reg。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_lea_from_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                        uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp;
  uint8_t buf[7];
  disp = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    buf[0] = 72;
    buf[1] = 0x8D;
    buf[2] = disp8_modrm;
    buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[0] = 72;
  buf[1] = 0x8D;
  buf[2] = disp32_modrm;
  buf[3] = (uint8_t)(disp & 255);
  buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255);
  buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);

}


/** movl -offset(%rbp), 32-bit reg（disp8 modrm 在 buf[2]）。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_movl_from_rbp_neg32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset,
                                           uint8_t disp8_modrm, uint8_t disp32_modrm) {
  int32_t disp;
  uint8_t buf[6];
  disp = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    buf[0] = 0x8B;
    buf[1] = disp8_modrm;
    buf[2] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  buf[0] = 0x8B;
  buf[1] = disp32_modrm;
  buf[2] = (uint8_t)(disp & 255);
  buf[3] = (uint8_t)((disp >> 8) & 255);
  buf[4] = (uint8_t)((disp >> 16) & 255);
  buf[5] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 6);

}


/** movq %rax, -offset(%rbp)。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_store_rax_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  int32_t disp;
  uint8_t buf[7];
  disp = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    buf[0] = 72;
    buf[1] = 0x89;
    buf[2] = 0x45;
    buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[0] = 72;
  buf[1] = 0x89;
  buf[2] = 0x85;
  buf[3] = (uint8_t)(disp & 255);
  buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255);
  buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);

}

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* movq %r64, -offset(%rbp). F7 dyn coerce vtable store. PLATFORM: LINUX x86_64. */
int32_t x86_enc_store_r64_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg,
                                     int32_t offset) {
  int32_t disp;
  uint8_t buf[8];
  int32_t lo;
  if (!elf_ctx || reg < 0 || reg > 15)
    return -1;
  disp = 0 - offset;
  lo = reg & 7;
  buf[0] = (reg >= 8) ? 76 : 72;
  buf[1] = 0x89;
  if (disp >= -128 && disp <= -1) {
    buf[2] = (uint8_t)(0x45 + lo * 8);
    buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[2] = (uint8_t)(0x85 + lo * 8);
  buf[3] = (uint8_t)(disp & 255);
  buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255);
  buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);
}
#endif

/** add/sub/imul imm32 到 32-bit reg 的通用模板。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_alu_imm32_to_reg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm, uint8_t op_prefix,
                                        uint8_t reg_modrm) {
  uint8_t buf[6];
  if (imm == 0)
    return 0;
  if (imm >= -128 && imm <= 127) {
    buf[0] = 0x83;
    buf[1] = reg_modrm;
    buf[2] = (uint8_t)imm;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  buf[0] = op_prefix;
  buf[1] = reg_modrm;
  buf[2] = (uint8_t)(imm & 255);
  buf[3] = (uint8_t)((imm >> 8) & 255);
  buf[4] = (uint8_t)((imm >> 16) & 255);
  buf[5] = (uint8_t)((imm >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 6);

}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_prologue */
/*
 * 【Why 根源】push/pop %rbx：body 用 rbx 作 array/const 基址却未保存，破坏 SysV 被调方保存；
 *   args_iter_count_c 覆写 next 保存在 rbx 的 it → run-env env_iter Ubuntu exit 1。
 * SysV 16B CALL align (same as backend_x86_64_enc_c.x): after push rbp+push rbx,
 *   RSP≡8; sub imm must be ≡8 mod 16 so body CALL sites have RSP≡0. Else glibc
 *   mktime/tzset/sscanf SEGV (run-time format_timezone). Locals rbp-relative.
 * PLATFORM: SHARED x86_64 SysV. Seed 与 arch/x86_64_enc.x 同语义。
 */
int32_t arch_x86_64_enc_enc_prologue(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t frame_size) {
  uint8_t mov[3] = {72, 137, 229};
  uint8_t sub[7] = {72, 129, 236, 0, 0, 0, 0};
  int32_t fs_i = frame_size;
  int32_t rem;
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 85) != 0) return -1; /* push rbp */
  if (X86_ENC_FIXED(elf_ctx, mov) != 0) return -1; /* mov rbp, rsp */
  if (x86_enc_u8(elf_ctx, 83) != 0) return -1; /* push rbx (callee-saved) */
  if (fs_i < 0) fs_i = 0;
  rem = fs_i % 16;
  if (rem != 8) {
    if (rem < 8) fs_i = fs_i + (8 - rem);
    else fs_i = fs_i + (16 - rem + 8);
  }
  sub[3] = (uint8_t)(fs_i & 255);
  sub[4] = (uint8_t)((fs_i >> 8) & 255);
  sub[5] = (uint8_t)((fs_i >> 16) & 255);
  sub[6] = (uint8_t)((fs_i >> 24) & 255);
  return X86_ENC_FIXED(elf_ctx, sub);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_epilogue */
int32_t arch_x86_64_enc_enc_epilogue(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  uint8_t lea[4] = {72, 141, 101, 248}; /* lea rsp, [rbp-8] */
  if (!elf_ctx) return -1;
  if (X86_ENC_FIXED(elf_ctx, lea) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 91) != 0) return -1; /* pop rbx */
  if (x86_enc_u8(elf_ctx, 93) != 0) return -1; /* pop rbp */
  return x86_enc_u8(elf_ctx, 195); /* ret */
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_label when FROM_X.
 * Ordering: pad_code_to_4 BEFORE emit_code_len (G.7 dual-authority with .x).
 * Hoist of emit_code_len before pad → multi-func SEGV (overload.x). */
int32_t arch_x86_64_enc_enc_label(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len, int32_t is_func) {
  uint8_t *cb;
  uint8_t mn[128];
  int32_t k;
  int32_t code_len;
  if (!elf_ctx || !name || name_len < 0) return -1;
  cb = x86_enc_ctx_bytes(elf_ctx);
  /* Block 1: pad only. */
  if (is_func != 0 && pipeline_elf_ctx_pad_code_to_4(cb) != 0) return -1;
  /* Block 2: capture after pad. */
  code_len = pipeline_elf_ctx_emit_code_len(cb);
  if (pipeline_elf_ctx_add_label(cb, name, name_len, code_len) != 0) return -1;
  if (is_func == 0) return 0;
  /* wave580 Cap: mn u8[128] holds '_' + up to 127 content (was 63).
   * PLATFORM: MACOS|DARWIN x86_64 Mach-O export; LINUX bare name. */
  if (pipeline_elf_ctx_macho_leading_underscore(cb) != 0 && name_len > 0 && name_len <= 127 && name[0] != 95) {
    mn[0] = 95;
    k = 0;
    while (k < name_len && k < 127) { mn[k + 1] = name[k]; k = k + 1; }
    return pipeline_elf_ctx_add_sym(cb, mn, name_len + 1, pipeline_elf_ctx_emit_code_len(cb));
  }
  return pipeline_elf_ctx_add_sym(cb, name, name_len, pipeline_elf_ctx_emit_code_len(cb));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_add_rax_rbx */
/* addl %ebx, %eax — 32-bit add (zero-extends to RAX).
 * Why: X language integer arithmetic defaults to 32-bit (i32/u32/u8/bool).
 *      A 32-bit ADD EAX,EBX zero-extends the result to RAX, giving correct
 *      wrapping semantics for u32 (0xFFFFFFFF + 1 = 0). The prior 64-bit
 *      ADD RAX,RBX (REX.W + 01 D8) did not wrap at 32 bits, breaking
 *      unsigned overflow.
 * Invariant: Must match .x authority x86_64_enc.x::enc_add_rax_rbx.
 *            i64/u64/ptr arithmetic uses enc_rax_plus_rbx_scale1 (64-bit) or
 *            ptr-arith scaled paths, NOT this function.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
int32_t arch_x86_64_enc_enc_add_rax_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {1, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_and_rbx_rax.
 * REX.W andq %rbx,%rax — 32-bit andl wiped usize/ptr high 32. */
int32_t arch_x86_64_enc_enc_and_rbx_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 33, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_or_rbx_rax.
 * REX.W orq %rbx,%rax — 32-bit orl truncated g02f_load_ptr_at (Ubuntu SIGSEGV).
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. Twin of ARM64 ELF orr x0,x0,x1. */
int32_t arch_x86_64_enc_enc_or_rbx_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 9, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_xor_rbx_rax.
 * REX.W xorq %rbx,%rax — same high-32 wipe as AND/OR. */
int32_t arch_x86_64_enc_enc_xor_rbx_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 49, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_mov_rax_to_rbx */
int32_t arch_x86_64_enc_enc_mov_rax_to_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 137, 195};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_mov_rbx_to_rax */
int32_t arch_x86_64_enc_enc_mov_rbx_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 137, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_mov_rbx_to_ecx */
int32_t arch_x86_64_enc_enc_mov_rbx_to_ecx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {137, 217};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_mov_edx_to_eax */
int32_t arch_x86_64_enc_enc_mov_edx_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {137, 208};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_not_eax */
int32_t arch_x86_64_enc_enc_not_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {247, 208};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_neg_eax */
int32_t arch_x86_64_enc_enc_neg_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {247, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_test_eax_eax */
int32_t arch_x86_64_enc_enc_test_eax_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {133, 192};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_test_rbx_rbx */
int32_t arch_x86_64_enc_enc_test_rbx_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {133, 219};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** test %edx,%edx — Result `?` 检查第二槽 err（双寄存器返回 ABI）。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_test_edx_edx */
int32_t arch_x86_64_enc_enc_test_edx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {0x85, 0xD2};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_cmp_rbx_rax */
int32_t arch_x86_64_enc_enc_cmp_rbx_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {57, 195};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_cmp_rax_rbx */
int32_t arch_x86_64_enc_enc_cmp_rax_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {57, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_cltd */
int32_t arch_x86_64_enc_enc_cltd(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {153};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_idiv_rbx */
int32_t arch_x86_64_enc_enc_idiv_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {247, 251};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_imul_rbx_rax */
/* imull %ebx, %eax — 32-bit imul (zero-extends to RAX).
 * Why: Must match .x authority x86_64_enc.x::enc_imul_rbx_rax.
 *      i64/u64/ptr arithmetic uses scaled paths, NOT this function.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
int32_t arch_x86_64_enc_enc_imul_rbx_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {15, 175, 195};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_push_rax */
int32_t arch_x86_64_enc_enc_push_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {80};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_push_rbx */
int32_t arch_x86_64_enc_enc_push_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {83};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_pop_rbx */
int32_t arch_x86_64_enc_enc_pop_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {91};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_pop_rax */
int32_t arch_x86_64_enc_enc_pop_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {88};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_shl_cl_eax */
int32_t arch_x86_64_enc_enc_shl_cl_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {211, 224};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_shr_cl_eax */
int32_t arch_x86_64_enc_enc_shr_cl_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {211, 232};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sar_cl_eax */
int32_t arch_x86_64_enc_enc_sar_cl_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {211, 248};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** shlq %cl, %rax — 64-bit 逻辑左移（REX.W=0x48 前缀）。i64/u64 移位须用 64-bit 指令。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_shl_cl_rax */
int32_t arch_x86_64_enc_enc_shl_cl_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 211, 224};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** shrq %cl, %rax — 64-bit 逻辑右移（REX.W=0x48 前缀）。u64/usize 逻辑右移保留高 32 位。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_shr_cl_rax */
int32_t arch_x86_64_enc_enc_shr_cl_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 211, 232};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** sarq %cl, %rax — 64-bit 算术右移（REX.W=0x48 前缀）。i64/isize 算术右移符号位扩展。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sar_cl_rax */
int32_t arch_x86_64_enc_enc_sar_cl_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 211, 248};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** xorl %edx, %edx — 32-bit 无符号除法前清零 edx（替代 cltd 符号扩展）。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_xor_edx_edx */
int32_t arch_x86_64_enc_enc_xor_edx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {49, 210};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** divl %ebx — 32-bit 无符号除法（被除数在 edx:eax，除数在 %ebx）。u32 除法必须用 divl。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_div_rbx */
int32_t arch_x86_64_enc_enc_div_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {247, 243};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_load_32_from_rax */
int32_t arch_x86_64_enc_enc_load_32_from_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {139, 0};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_load_64_from_rax */
int32_t arch_x86_64_enc_enc_load_64_from_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 139, 0};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_load_zext8_from_rax */
int32_t arch_x86_64_enc_enc_load_zext8_from_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {15, 182, 0};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_rax_plus_rbx_scale1 */
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale1(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 4, 24};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_rax_plus_rbx_scale4 */
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale4(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 4, 152};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_rax_plus_rbx_scale8 */
int32_t arch_x86_64_enc_enc_rax_plus_rbx_scale8(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 4, 216};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1 */
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 28, 11};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4 */
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 28, 139};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8 */
int32_t arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 141, 28, 203};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_add_ecx_edx */
int32_t arch_x86_64_enc_enc_add_ecx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {1, 209};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sub_ecx_edx */
int32_t arch_x86_64_enc_enc_sub_ecx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {41, 209};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_add_ebx_edx */
int32_t arch_x86_64_enc_enc_add_ebx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {1, 211};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sub_ebx_edx */
int32_t arch_x86_64_enc_enc_sub_ebx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {41, 211};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_imul_ecx_edx.
 * Wave184 root-fix: 0F AF /r IMUL ecx,edx (ModRM 0xCA). Was 0xD1 (IMUL edx,ecx).
 * PLATFORM: SHARED x86_64 SysV — index_scratch primary *= secondary. */
int32_t arch_x86_64_enc_enc_imul_ecx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {15, 175, 202};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_imul_ebx_edx.
 * Wave184 root-fix: 0F AF /r IMUL ebx,edx (ModRM 0xDA). Was 0xD3 (IMUL edx,ebx).
 * PLATFORM: SHARED x86_64 SysV — INDEX read path rbx *= secondary; scale uses rbx. */
int32_t arch_x86_64_enc_enc_imul_ebx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {15, 175, 218};
  if (!elf_ctx) return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sub_rbx_rax_then_mov */
int32_t arch_x86_64_enc_enc_sub_rbx_rax_then_mov(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t sub[] = {72, 41, 195};
  static const uint8_t mov[] = {72, 137, 216};
  if (!elf_ctx) return -1;
  if (x86_enc_bytes(elf_ctx, sub, 3) != 0) return -1;
  return x86_enc_bytes(elf_ctx, mov, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_rsub_ecx_edx */
int32_t arch_x86_64_enc_enc_rsub_ecx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t sub[] = {41, 202};
  static const uint8_t mov[] = {137, 209};
  if (!elf_ctx) return -1;
  if (x86_enc_bytes(elf_ctx, sub, 2) != 0) return -1;
  return x86_enc_bytes(elf_ctx, mov, 2);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_rsub_ebx_edx */
int32_t arch_x86_64_enc_enc_rsub_ebx_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t sub[] = {41, 218};
  static const uint8_t mov[] = {137, 211};
  if (!elf_ctx) return -1;
  if (x86_enc_bytes(elf_ctx, sub, 2) != 0) return -1;
  return x86_enc_bytes(elf_ctx, mov, 2);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_setz_movzbl_eax */
int32_t arch_x86_64_enc_enc_setz_movzbl_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t s[] = {15, 148, 192};
  static const uint8_t m[] = {15, 182, 192};
  if (!elf_ctx) return -1;
  if (x86_enc_bytes(elf_ctx, s, 3) != 0) return -1;
  return x86_enc_bytes(elf_ctx, m, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_cmp_setcc_movzbl */
int32_t arch_x86_64_enc_enc_cmp_setcc_movzbl(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t cc) {
  uint8_t op = 148;
  static const uint8_t m[] = {15, 182, 192};
  uint8_t s[3];
  if (!elf_ctx) return -1;
  if (cc == 1) op = 149;
  else if (cc == 2) op = 156;
  else if (cc == 3) op = 158;
  else if (cc == 4) op = 159;
  else if (cc == 5) op = 157;
  s[0] = 15; s[1] = op; s[2] = 192;
  if (x86_enc_bytes(elf_ctx, s, 3) != 0) return -1;
  return x86_enc_bytes(elf_ctx, m, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Stage 10 S3.1 slice 2 (10.1.1): syscall (0F 05). Twin of
 * arch_x86_64_enc_enc_syscall in backend_x86_64_enc_c.x.
 * PLATFORM: LINUX|x86_64 runtime effect; SHARED emit code. */
int32_t arch_x86_64_enc_enc_syscall(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  return x86_enc_u8(elf_ctx, 5);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: movl (%rax), %eax (8B 00). Twin of backend_x86_64_enc_c.x. */
int32_t arch_x86_64_enc_enc_movl_mem_rax_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 139) != 0) return -1;
  return x86_enc_u8(elf_ctx, 0);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: movl (%rcx), %eax (8B 01) — *expected while ptr lives elsewhere. */
int32_t arch_x86_64_enc_enc_movl_mem_rcx_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 139) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: xchg %edx, (%rax) (87 10). */
int32_t arch_x86_64_enc_enc_xchg_edx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 135) != 0) return -1;
  return x86_enc_u8(elf_ctx, 16);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: mov %rax, %rcx (48 89 C1). */
int32_t arch_x86_64_enc_enc_mov_rax_to_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 193);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: movl %eax, (%rcx) (89 01). */
int32_t arch_x86_64_enc_enc_movl_eax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: lock cmpxchg %edx, (%rax) (F0 0F B1 10) — kept for completeness. */
int32_t arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 240) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 177) != 0) return -1;
  return x86_enc_u8(elf_ctx, 16);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: lock cmpxchg %edx, (%rbx) (F0 0F B1 13) — ptr≠rax so eax keeps expected. */
int32_t arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 240) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 177) != 0) return -1;
  return x86_enc_u8(elf_ctx, 19);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: sete %al (0F 94 C0). */
int32_t arch_x86_64_enc_enc_sete_al(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 148) != 0) return -1;
  return x86_enc_u8(elf_ctx, 192);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: movzbl %al, %eax (0F B6 C0). */
int32_t arch_x86_64_enc_enc_movzbl_al_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 182) != 0) return -1;
  return x86_enc_u8(elf_ctx, 192);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice1: mov %eax, %edx (89 C2). */
int32_t arch_x86_64_enc_enc_mov_eax_to_edx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 194);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: movq (%rax), %rax (48 8B 00). */
int32_t arch_x86_64_enc_enc_movq_mem_rax_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 139) != 0) return -1;
  return x86_enc_u8(elf_ctx, 0);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: xchg %rdx, (%rax) (48 87 10). */
int32_t arch_x86_64_enc_enc_xchg_rdx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 135) != 0) return -1;
  return x86_enc_u8(elf_ctx, 16);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: mov %rax, %rdx (48 89 C2). */
int32_t arch_x86_64_enc_enc_mov_rax_to_rdx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 194);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: movq (%rcx), %rax (48 8B 01). */
int32_t arch_x86_64_enc_enc_movq_mem_rcx_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 139) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: movq %rax, (%rcx) (48 89 01). */
int32_t arch_x86_64_enc_enc_movq_rax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice2: lock cmpxchg %rdx, (%rbx) (F0 48 0F B1 13). */
int32_t arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 240) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 177) != 0) return -1;
  return x86_enc_u8(elf_ctx, 19);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.2: mfence (0F AE F0). */
int32_t arch_x86_64_enc_enc_mfence(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 174) != 0) return -1;
  return x86_enc_u8(elf_ctx, 240);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.2: lfence (0F AE E8). */
int32_t arch_x86_64_enc_enc_lfence(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 174) != 0) return -1;
  return x86_enc_u8(elf_ctx, 232);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.2: sfence (0F AE F8). */
int32_t arch_x86_64_enc_enc_sfence(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 174) != 0) return -1;
  return x86_enc_u8(elf_ctx, 248);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: movzwl (%rax), %eax (0F B7 00). */
int32_t arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 183) != 0) return -1;
  return x86_enc_u8(elf_ctx, 0);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: xchg %dx, (%rax) (66 87 10). */
int32_t arch_x86_64_enc_enc_xchg_dx_mem_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 102) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 135) != 0) return -1;
  return x86_enc_u8(elf_ctx, 16);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: mov %ax, %dx (66 89 C2). */
int32_t arch_x86_64_enc_enc_mov_ax_to_dx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 102) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 194);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: movzwl (%rcx), %eax (0F B7 01). */
int32_t arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 183) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: movw %ax, (%rcx) (66 89 01). */
int32_t arch_x86_64_enc_enc_movw_ax_to_mem_rcx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 102) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 1);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* 10.4.1 slice3: lock cmpxchg %dx, (%rbx) (F0 66 0F B1 13). */
int32_t arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 240) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 102) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 15) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 177) != 0) return -1;
  return x86_enc_u8(elf_ctx, 19);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Stage 10 S3.1 slice 2 (10.1.1): mov %rax, %r10 (49 89 C2). Twin of
 * arch_x86_64_enc_enc_mov_rax_to_r10 in backend_x86_64_enc_c.x. r10 has no
 * C-ABI mov_rax_to_arg_reg k slot (G.7; do not fork a second register map).
 * PLATFORM: LINUX|x86_64 runtime effect; SHARED emit code. */
int32_t arch_x86_64_enc_enc_mov_rax_to_r10(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 73) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 194);
}

/* Stage10 10.2.1 slice7: mov %r10, %rax (4C 89 D0). Twin of
 * arch_x86_64_enc_enc_mov_r10_to_rax in backend_x86_64_enc_c.x.
 * PLATFORM: LINUX|x86_64; SHARED emit. */
int32_t arch_x86_64_enc_enc_mov_r10_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 76) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 208);
}

/* Stage10 10.2.3: mov %rax, %r11 (49 89 C3). Twin of
 * arch_x86_64_enc_enc_mov_rax_to_r11 in backend_x86_64_enc_c.x.
 * PLATFORM: SHARED. */
int32_t arch_x86_64_enc_enc_mov_rax_to_r11(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 73) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 195);
}

/* Stage10 10.2.3: mov %r11, %rax (4C 89 D8). Twin of
 * arch_x86_64_enc_enc_mov_r11_to_rax in backend_x86_64_enc_c.x.
 * PLATFORM: SHARED. */
int32_t arch_x86_64_enc_enc_mov_r11_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 76) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 137) != 0) return -1;
  return x86_enc_u8(elf_ctx, 216);
}

/* Stage10 10.2.3: pause (F3 90). Twin of
 * arch_x86_64_enc_enc_pause in backend_x86_64_enc_c.x.
 * PLATFORM: SHARED. */
int32_t arch_x86_64_enc_enc_pause(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 243) != 0) return -1;
  return x86_enc_u8(elf_ctx, 144);
}

/* Stage10 10.2.3: int3 (CC). Twin of
 * arch_x86_64_enc_enc_int3 in backend_x86_64_enc_c.x.
 * PLATFORM: SHARED. */
int32_t arch_x86_64_enc_enc_int3(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  if (!elf_ctx) return -1;
  return x86_enc_u8(elf_ctx, 204);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_mov_imm32_to_rbx */
int32_t arch_x86_64_enc_enc_mov_imm32_to_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm32) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 187) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, imm32);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_ret_imm32 */
int32_t arch_x86_64_enc_enc_ret_imm32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm32) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 184) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, imm32);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_mov_imm64_to_rax */
int32_t arch_x86_64_enc_enc_mov_imm64_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t lo, int32_t hi) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 184) != 0) return -1;
  if (x86_enc_u32_le(elf_ctx, lo) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, hi);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_cmp_eax_imm32 */
int32_t arch_x86_64_enc_enc_cmp_eax_imm32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm32) {
  if (!elf_ctx) return -1;
  if (x86_enc_u8(elf_ctx, 61) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, imm32);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_add_imm_to_rax */
int32_t arch_x86_64_enc_enc_add_imm_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  if (imm == 0) return 0;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 5) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, imm);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_add_imm_to_rbx */
int32_t arch_x86_64_enc_enc_add_imm_to_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  if (imm == 0) return 0;
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 129) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 195) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, imm);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_store_rax_to_rbp */
int32_t arch_x86_64_enc_enc_store_rax_to_rbp(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_store_rax_to_rbp_neg(elf_ctx, offset);
}

/* F7: general r64 → [rbp-off]. Completes store_x_reg_to_rbp_arch on x86_64. */
int32_t arch_x86_64_enc_enc_store_r64_to_rbp(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t reg,
                                              int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_store_r64_to_rbp_neg(elf_ctx, reg, offset);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_rax */
int32_t arch_x86_64_enc_enc_load_rbp_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 69, 133);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_rbx */
int32_t arch_x86_64_enc_enc_load_rbp_to_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 93, 157);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_lea_rbp_to_rax */
int32_t arch_x86_64_enc_enc_lea_rbp_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 69, 133);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_lea_rbp_to_rbx */
int32_t arch_x86_64_enc_enc_lea_rbp_to_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 93, 157);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_pos_to_rax */
int32_t arch_x86_64_enc_enc_load_rbp_pos_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t off_pos) {
  int32_t disp;
  uint8_t buf[7];
  if (!elf_ctx) return -1;
  disp = off_pos;
  if (disp < 0) disp = 0;
  if (disp <= 127) {
    buf[0] = 72; buf[1] = 0x8B; buf[2] = 0x45; buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[0] = 72; buf[1] = 0x8B; buf[2] = 0x85;
  buf[3] = (uint8_t)(disp & 255); buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255); buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_eax32 */
int32_t arch_x86_64_enc_enc_load_rbp_to_eax32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 69, 133);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_ebx32 */
int32_t arch_x86_64_enc_enc_load_rbp_to_ebx32(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 93, 157);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_ecx */
int32_t arch_x86_64_enc_enc_load_rbp_to_ecx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 77, 141);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_edx */
int32_t arch_x86_64_enc_enc_load_rbp_to_edx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx) return -1;
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 85, 149);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_add_imm_to_ecx */
int32_t arch_x86_64_enc_enc_add_imm_to_ecx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 193);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_sub_imm_from_ecx */
int32_t arch_x86_64_enc_enc_sub_imm_from_ecx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 233);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_add_imm_to_ebx_index */
int32_t arch_x86_64_enc_enc_add_imm_to_ebx_index(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 195);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_sub_imm_from_ebx_index */
int32_t arch_x86_64_enc_enc_sub_imm_from_ebx_index(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  if (!elf_ctx) return -1;
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 235);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_imul_imm_to_ecx */
int32_t arch_x86_64_enc_enc_imul_imm_to_ecx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  uint8_t buf[6];
  if (!elf_ctx) return -1;
  if (imm <= 1) return 0;
  if (imm >= -128 && imm <= 127) {
    buf[0] = 0x6B; buf[1] = 201; buf[2] = (uint8_t)imm;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  buf[0] = 0x69; buf[1] = 201;
  buf[2] = (uint8_t)(imm & 255); buf[3] = (uint8_t)((imm >> 8) & 255);
  buf[4] = (uint8_t)((imm >> 16) & 255); buf[5] = (uint8_t)((imm >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 6);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_imul_imm_to_ebx */
int32_t arch_x86_64_enc_enc_imul_imm_to_ebx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t imm) {
  uint8_t buf[6];
  if (!elf_ctx) return -1;
  if (imm <= 1) return 0;
  if (imm >= -128 && imm <= 127) {
    buf[0] = 0x6B; buf[1] = 219; buf[2] = (uint8_t)imm;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  buf[0] = 0x69; buf[1] = 219;
  buf[2] = (uint8_t)(imm & 255); buf[3] = (uint8_t)((imm >> 8) & 255);
  buf[4] = (uint8_t)((imm >> 16) & 255); buf[5] = (uint8_t)((imm >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 6);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_mov_arg_reg_to_rax */
int32_t arch_x86_64_enc_enc_mov_arg_reg_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k) {
  static const uint8_t b0[] = {72,137,248};
  static const uint8_t b1[] = {72,137,240};
  static const uint8_t b2[] = {72,137,208};
  static const uint8_t b3[] = {72,137,200};
  static const uint8_t b4[] = {76,137,192};
  static const uint8_t b5[] = {76,137,200};
  int32_t idx;
  if (!elf_ctx) return -1;
  idx = k; if (idx < 0) idx = 0; if (idx > 5) idx = 5;
  if (idx == 0) return x86_enc_bytes(elf_ctx, b0, 3);
  if (idx == 1) return x86_enc_bytes(elf_ctx, b1, 3);
  if (idx == 2) return x86_enc_bytes(elf_ctx, b2, 3);
  if (idx == 3) return x86_enc_bytes(elf_ctx, b3, 3);
  if (idx == 4) return x86_enc_bytes(elf_ctx, b4, 3);
  return x86_enc_bytes(elf_ctx, b5, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_mov_rax_to_arg_reg */
int32_t arch_x86_64_enc_enc_mov_rax_to_arg_reg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k) {
  static const uint8_t b0[] = {72,137,199};
  static const uint8_t b1[] = {72,137,198};
  static const uint8_t b2[] = {72,137,194};
  static const uint8_t b3[] = {72,137,193};
  static const uint8_t b4[] = {73,137,192};
  static const uint8_t b5[] = {73,137,193};
  int32_t idx;
  if (!elf_ctx) return -1;
  idx = k; if (idx < 0) idx = 0; if (idx > 5) idx = 5;
  if (idx == 0) return x86_enc_bytes(elf_ctx, b0, 3);
  if (idx == 1) return x86_enc_bytes(elf_ctx, b1, 3);
  if (idx == 2) return x86_enc_bytes(elf_ctx, b2, 3);
  if (idx == 3) return x86_enc_bytes(elf_ctx, b3, 3);
  if (idx == 4) return x86_enc_bytes(elf_ctx, b4, 3);
  return x86_enc_bytes(elf_ctx, b5, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_jz */
int32_t arch_x86_64_enc_enc_jz(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *label, int32_t label_len) {
  if (!elf_ctx) return -1;
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_jeq */
int32_t arch_x86_64_enc_enc_jeq(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *label, int32_t label_len) {
  if (!elf_ctx) return -1;
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_jge */
int32_t arch_x86_64_enc_enc_jge(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *label, int32_t label_len) {
  if (!elf_ctx) return -1;
  return x86_enc_jcc_rel32(elf_ctx, 141, label, label_len);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_jnz */
int32_t arch_x86_64_enc_enc_jnz(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *label, int32_t label_len) {
  if (!elf_ctx) return -1;
  return x86_enc_jcc_rel32(elf_ctx, 133, label, label_len);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_jmp */
int32_t arch_x86_64_enc_enc_jmp(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *label, int32_t label_len) {
  int32_t rel32_at;
  uint8_t *cb;
  if (!elf_ctx || !label || label_len <= 0) return -1;
  cb = x86_enc_ctx_bytes(elf_ctx);
  if (x86_enc_u8(elf_ctx, 233) != 0) return -1;
  if (x86_enc_u32_le(elf_ctx, 0) != 0) return -1;
  rel32_at = pipeline_elf_ctx_emit_code_len(cb) - 4;
  if (pipeline_elf_ctx_ensure_label(cb, label, label_len) != 0) return -1;
  return pipeline_elf_ctx_append_patch(cb, rel32_at, label, label_len, 0);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_call */
int32_t arch_x86_64_enc_enc_call(struct platform_elf_ElfCodegenCtx *elf_ctx, uint8_t *name, int32_t name_len) {
  int32_t rel32_at;
  uint8_t *cb;
  uint8_t rn[128];
  int32_t k;
  if (!elf_ctx || !name || name_len <= 0) return -1;
  cb = x86_enc_ctx_bytes(elf_ctx);
  if (x86_enc_u8(elf_ctx, 232) != 0) return -1;
  if (x86_enc_u32_le(elf_ctx, 0) != 0) return -1;
  rel32_at = pipeline_elf_ctx_emit_code_len(cb) - 4;
  /* wave580 Cap: rn u8[128] holds '_' + up to 127 content (was 63).
   * PLATFORM: MACOS|DARWIN x86_64 call reloc.
   * Stage 12.0.5 ABI: always prepend '_' even when C name starts with '_'
   * (__error → ___error). Do not skip on name[0]=='_'. */
  if (pipeline_elf_ctx_macho_leading_underscore(cb) != 0 && name_len > 0 && name_len <= 127) {
    rn[0] = 95; k = 0;
    while (k < name_len && k < 127) { rn[k + 1] = name[k]; k = k + 1; }
    return pipeline_elf_ctx_append_reloc(cb, rel32_at, rn, name_len + 1);
  }
  return pipeline_elf_ctx_append_reloc(cb, rel32_at, name, name_len);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_add_rsp_imm */
int32_t arch_x86_64_enc_enc_add_rsp_imm(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t nbytes) {
  if (!elf_ctx) return -1;
  if (nbytes <= 0) return 0;
  if (nbytes <= 127) {
    if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
    if (x86_enc_u8(elf_ctx, 131) != 0) return -1;
    if (x86_enc_u8(elf_ctx, 196) != 0) return -1;
    return x86_enc_u8(elf_ctx, (uint8_t)nbytes);
  }
  if (x86_enc_u8(elf_ctx, 72) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 129) != 0) return -1;
  if (x86_enc_u8(elf_ctx, 196) != 0) return -1;
  return x86_enc_u32_le(elf_ctx, nbytes);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_store_rax_to_rbx_indirect */
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_indirect(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t elem_sz) {
  static const uint8_t b1[] = {136, 3};
  static const uint8_t b4[] = {137, 3};
  static const uint8_t b8[] = {72, 137, 3};
  if (!elf_ctx) return -1;
  if (elem_sz == 1) return x86_enc_bytes(elf_ctx, b1, 2);
  if (elem_sz == 4) return x86_enc_bytes(elf_ctx, b4, 2);
  return x86_enc_bytes(elf_ctx, b8, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_store_rax_to_rbx_offset */
int32_t arch_x86_64_enc_enc_store_rax_to_rbx_offset(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset, int32_t store_size) {
  uint8_t buf[7];
  if (!elf_ctx) return -1;
  if (store_size == 1) {
    buf[0] = 136; buf[1] = 131;
    buf[2] = (uint8_t)(offset & 255); buf[3] = (uint8_t)((offset >> 8) & 255);
    buf[4] = (uint8_t)((offset >> 16) & 255); buf[5] = (uint8_t)((offset >> 24) & 255);
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  if (store_size == 4) {
    buf[0] = 137; buf[1] = 131;
    buf[2] = (uint8_t)(offset & 255); buf[3] = (uint8_t)((offset >> 8) & 255);
    buf[4] = (uint8_t)((offset >> 16) & 255); buf[5] = (uint8_t)((offset >> 24) & 255);
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  buf[0] = 72; buf[1] = 137; buf[2] = 131;
  buf[3] = (uint8_t)(offset & 255); buf[4] = (uint8_t)((offset >> 8) & 255);
  buf[5] = (uint8_t)((offset >> 16) & 255); buf[6] = (uint8_t)((offset >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

/** subl %ebx, %eax — 32-bit sub (zero-extends to RAX). */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_sub_rax_rbx */
/* subl %ebx, %eax — 32-bit sub (zero-extends to RAX).
 * Why: Must match .x authority x86_64_enc.x::enc_sub_rax_rbx.
 *      i64/u64/ptr arithmetic uses scaled paths, NOT this function.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
int32_t arch_x86_64_enc_enc_sub_rax_rbx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {41, 216};
  if (!elf_ctx)
    return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** movq (%rbx), %rax — SysV 16B struct 返回低 8 字节。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_load_qword_from_rbx_to_rax */
int32_t arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 139, 3};
  if (!elf_ctx)
    return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** movq 8(%rbx), %rdx — SysV 16B struct 返回高 8 字节。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave1: .x provides arch_x86_64_enc_enc_load_qword_rbx8_to_rdx */
int32_t arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(struct platform_elf_ElfCodegenCtx *elf_ctx) {
  static const uint8_t ins[] = {72, 139, 83, 8};
  if (!elf_ctx)
    return -1;
  return x86_enc_bytes(elf_ctx, ins, (int32_t)sizeof(ins));
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/** movq %rdx, -offset(%rbp)。 */
/* G-02f-130：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t x86_enc_store_rdx_to_rbp_neg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  int32_t disp;
  uint8_t buf[7];
  disp = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    buf[0] = 72;
    buf[1] = 0x89;
    buf[2] = 0x55;
    buf[3] = (uint8_t)disp;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  buf[0] = 72;
  buf[1] = 0x89;
  buf[2] = 0x95;
  buf[3] = (uint8_t)(disp & 255);
  buf[4] = (uint8_t)((disp >> 8) & 255);
  buf[5] = (uint8_t)((disp >> 16) & 255);
  buf[6] = (uint8_t)((disp >> 24) & 255);
  return x86_enc_bytes(elf_ctx, buf, 7);

}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */


/** movq %rdx, -offset(%rbp)（16B struct 第二寄存器落栈）。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_store_rdx_to_rbp */
int32_t arch_x86_64_enc_enc_store_rdx_to_rbp(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx)
    return -1;
  return x86_enc_store_rdx_to_rbp_neg(elf_ctx, offset);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

/** movq -offset(%rbp), %rdx（16B struct 栈槽高 8 字节）。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_load_rbp_to_rdx */
int32_t arch_x86_64_enc_enc_load_rbp_to_rdx(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t offset) {
  if (!elf_ctx)
    return -1;
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 85, 149);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */

/** movq %rdx, arg_reg[k]（SysV 16B struct 第二 GPR 实参）。 */
#ifndef XLANG_BACKEND_X86_64_ENC_C_FROM_X
/* Cap residual pure R2 wave2: .x provides arch_x86_64_enc_enc_mov_rdx_to_arg_reg */
int32_t arch_x86_64_enc_enc_mov_rdx_to_arg_reg(struct platform_elf_ElfCodegenCtx *elf_ctx, int32_t k) {
  static const uint8_t b0[] = {72, 137, 215};
  static const uint8_t b1[] = {72, 137, 214};
  static const uint8_t b2[] = {72, 137, 210};
  static const uint8_t b3[] = {72, 137, 209};
  static const uint8_t b4[] = {73, 137, 208};
  static const uint8_t b5[] = {73, 137, 209};
  int32_t idx;
  if (!elf_ctx)
    return -1;
  idx = k;
  if (idx < 0)
    idx = 0;
  if (idx > 5)
    idx = 5;
  /** 与 enc_mov_rax_to_arg_reg 对称：目的=arg_reg[k]，源=rdx。 */
  if (idx == 0)
    return x86_enc_bytes(elf_ctx, b0, 3);
  if (idx == 1)
    return x86_enc_bytes(elf_ctx, b1, 3);
  if (idx == 2)
    return x86_enc_bytes(elf_ctx, b2, 3);
  if (idx == 3)
    return x86_enc_bytes(elf_ctx, b3, 3);
  if (idx == 4)
    return x86_enc_bytes(elf_ctx, b4, 3);
  return x86_enc_bytes(elf_ctx, b5, 3);
}
#endif /* !XLANG_BACKEND_X86_64_ENC_C_FROM_X */
