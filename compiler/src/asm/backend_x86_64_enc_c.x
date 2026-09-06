// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// backend_x86_64_enc_c_x_doc_anchor: see function docblock below.

/** Exported function `backend_x86_64_enc_c_x_doc_anchor`.
 * Implements `backend_x86_64_enc_c_x_doc_anchor`.
 * @return i32
 */
export function backend_x86_64_enc_c_x_doc_anchor(): i32 {
  return 0;
}

// See implementation.

export extern "C" function pipeline_elf_ctx_append_bytes(ctx: *u8, ptr: *u8, n: i32): i32;
export extern "C" function pipeline_elf_ctx_emit_code_len(ctx: *u8): i32;
export extern "C" function pipeline_elf_ctx_ensure_label(ctx: *u8, name: *u8, name_len: i32): i32;
export extern "C" function pipeline_elf_ctx_append_patch(ctx: *u8, rel32_offset: i32, name: *u8, name_len: i32, imm_bits: i32): i32;
export extern "C" function pipeline_elf_ctx_append_reloc(ctx: *u8, offset: i32, name: *u8, name_len: i32): i32;
export extern "C" function pipeline_elf_ctx_add_label(ctx: *u8, name: *u8, name_len: i32, offset: i32): i32;
export extern "C" function pipeline_elf_ctx_pad_code_to_4(ctx: *u8): i32;
export extern "C" function pipeline_elf_ctx_add_sym(ctx: *u8, name: *u8, name_len: i32, offset: i32): i32;
export extern "C" function pipeline_elf_ctx_macho_leading_underscore(ctx: *u8): i32;

/** Exported function `x86_enc_u8`.
 * Implements `x86_enc_u8`.
 * @param elf_ctx *u8
 * @param b u8
 * @return i32
 */
#[no_mangle]
export function x86_enc_u8(elf_ctx: *u8, b: u8): i32 {
  let bb: u8 = b;
  unsafe {
    return pipeline_elf_ctx_append_bytes(elf_ctx, &bb, 1);
  }
  return 0 - 1;
}

/** Exported function `x86_enc_bytes`.
 * Implements `x86_enc_bytes`.
 * @param elf_ctx *u8
 * @param buf *u8
 * @param n i32
 * @return i32
 */
#[no_mangle]
export function x86_enc_bytes(elf_ctx: *u8, buf: *u8, n: i32): i32 {
  unsafe {
    return pipeline_elf_ctx_append_bytes(elf_ctx, buf, n);
  }
  return 0 - 1;
}

/** Exported function `x86_enc_u32_le`.
 * Implements `x86_enc_u32_le`.
 * @param elf_ctx *u8
 * @param imm i32
 * @return i32
 */
#[no_mangle]
export function x86_enc_u32_le(elf_ctx: *u8, imm: i32): i32 {
  // See implementation.
  let w: u32 = imm as u32;
  let b0: u8 = (w & 255) as u8;
  let b1: u8 = ((w / 256) & 255) as u8;
  let b2: u8 = ((w / 65536) & 255) as u8;
  let b3: u8 = ((w / 16777216) & 255) as u8;
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b0, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b1, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b2, 1) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b3, 1);
  }
  return 0 - 1;
}

// x86_enc_jcc_rel32: see function docblock below.
/**
 * Emit x86_64 near jcc: `0F <opcode2> rel32` and register a patch to `label`.
 *
 * Encoding: 6 bytes (`0F` + opcode2 + 4 zero displ). Patch slot is the displ
 * at `emit_code_len() - 4` **after** the 6 bytes are appended.
 *
 * **Ordering contract (Stage12.0.5 product root):** pass0 may hoist
 * `let rel32_at = emit_code_len() - 4` (BINOP with nested CALL) to the top of
 * its enclosing block. If that let shares a block with the append side effects,
 * rel32_at is computed **before** the jcc bytes exist → patch overwrites the
 * prior insn stream (and/test/setz) → Ubuntu option SIGILL / stdlib-import SEGV.
 * Mitigation: append in one block, then compute rel32_at + patch in a **later**
 * block (same shape as `arch_x86_64_enc_enc_jmp` / `enc_call`). Do not merge.
 *
 * @param elf_ctx opaque ElfCodegenCtx*
 * @param opcode2 second opcode byte (e.g. 0x84 jz, 0x85 jnz)
 * @param label patch target name bytes
 * @param label_len name length; must be > 0
 * @return 0 on success, -1 on null/encode/patch failure
 * PLATFORM: SHARED — x86_64 SysV product asm (LINUX gold for jcc stream).
 */
#[no_mangle]
export function x86_enc_jcc_rel32(elf_ctx: *u8, opcode2: u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (label == 0) { return 0 - 1; }
  if (label_len <= 0) { return 0 - 1; }
  let b: u8[6] = [15, 0, 0, 0, 0, 0];
  b[1] = opcode2;
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b[0], 6) != 0) { return 0 - 1; }
    let rel32_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
    if (pipeline_elf_ctx_ensure_label(elf_ctx, label, label_len) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_patch(elf_ctx, rel32_at, label, label_len, 0);
  }
  return 0 - 1;
}

// G-02f-130：rbp/alu enc pure helpers

/** Exported function `x86_enc_append_i32_le`.
 * Implements `x86_enc_append_i32_le`.
 * @param elf_ctx *u8
 * @param v i32
 * @return i32
 */
export function x86_enc_append_i32_le(elf_ctx: *u8, v: i32): i32 {
  let w: u32 = v as u32;
  let b0: u8 = (w & 255) as u8;
  let b1: u8 = ((w / 256) & 255) as u8;
  let b2: u8 = ((w / 65536) & 255) as u8;
  let b3: u8 = ((w / 16777216) & 255) as u8;
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b0, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b1, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b2, 1) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b3, 1);
  }
  return 0 - 1;
}

/** Exported function `x86_enc_movq_from_rbp_neg`.
 * Implements `x86_enc_movq_from_rbp_neg`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param disp8_modrm u8
 * @param disp32_modrm u8
 * @return i32
 */
#[no_mangle]
export function x86_enc_movq_from_rbp_neg(elf_ctx: *u8, offset: i32, disp8_modrm: u8, disp32_modrm: u8): i32 {
  let disp: i32 = 0 - offset;
  let r64: u8 = 72;
  let op: u8 = 139; // 0x8B
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp8_modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp32_modrm, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/** Exported function `x86_enc_lea_from_rbp_neg`.
 * Implements `x86_enc_lea_from_rbp_neg`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param disp8_modrm u8
 * @param disp32_modrm u8
 * @return i32
 */
#[no_mangle]
export function x86_enc_lea_from_rbp_neg(elf_ctx: *u8, offset: i32, disp8_modrm: u8, disp32_modrm: u8): i32 {
  let disp: i32 = 0 - offset;
  let r64: u8 = 72;
  let op: u8 = 141; // 0x8D
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp8_modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp32_modrm, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/** Exported function `x86_enc_movl_from_rbp_neg32`.
 * Implements `x86_enc_movl_from_rbp_neg32`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param disp8_modrm u8
 * @param disp32_modrm u8
 * @return i32
 */
#[no_mangle]
export function x86_enc_movl_from_rbp_neg32(elf_ctx: *u8, offset: i32, disp8_modrm: u8, disp32_modrm: u8): i32 {
  let disp: i32 = 0 - offset;
  let op: u8 = 139; // 0x8B
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp8_modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &disp32_modrm, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/** Exported function `x86_enc_store_rax_to_rbp_neg`.
 * Implements `x86_enc_store_rax_to_rbp_neg`.
 * @param elf_ctx *u8
 * @param offset i32
 * @return i32
 */
#[no_mangle]
export function x86_enc_store_rax_to_rbp_neg(elf_ctx: *u8, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  let r64: u8 = 72;
  let op: u8 = 137; // 0x89
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let modrm: u8 = 69; // 0x45
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  let modrm32: u8 = 133; // 0x85
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm32, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/**
 * movq %r64, -offset(%rbp). REX.W[+R] + 89 /r, rbp base (rm=5).
 * @param elf_ctx *u8 — ElfCodegenCtx
 * @param reg i32 — 0..15
 * @param offset i32 — positive rbp-down slot (disp = -offset)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU x86_64 SysV — G.7 twin of store_rax/store_rdx helpers.
 */
#[no_mangle]
export function x86_enc_store_r64_to_rbp_neg(elf_ctx: *u8, reg: i32, offset: i32): i32 {
  if (elf_ctx == 0 as *u8) { return 0 - 1; }
  if (reg < 0 || reg > 15) { return 0 - 1; }
  let disp: i32 = 0 - offset;
  let rex: u8 = 72;
  if (reg >= 8) { rex = 76; }
  let op: u8 = 137;
  let lo: i32 = reg & 7;
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let modrm: u8 = (69 + lo * 8) as u8;
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &rex, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  let modrm32: u8 = (133 + lo * 8) as u8;
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &rex, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm32, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/** Exported function `x86_enc_store_rdx_to_rbp_neg`.
 * Implements `x86_enc_store_rdx_to_rbp_neg`.
 * @param elf_ctx *u8
 * @param offset i32
 * @return i32
 */
#[no_mangle]
export function x86_enc_store_rdx_to_rbp_neg(elf_ctx: *u8, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  let r64: u8 = 72;
  let op: u8 = 137; // 0x89
  if (disp >= 0 - 128 && disp <= 0 - 1) {
    let modrm: u8 = 85; // 0x55
    let d8: u8 = disp as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  let modrm32: u8 = 149; // 0x95
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &r64, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &modrm32, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, disp);
}

/** Exported function `x86_enc_alu_imm32_to_reg`.
 * Implements `x86_enc_alu_imm32_to_reg`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param op_prefix u8
 * @param reg_modrm u8
 * @return i32
 */
#[no_mangle]
export function x86_enc_alu_imm32_to_reg(elf_ctx: *u8, imm: i32, op_prefix: u8, reg_modrm: u8): i32 {
  if (imm == 0) { return 0; }
  if (imm >= 0 - 128 && imm <= 127) {
    let op83: u8 = 131; // 0x83
    let d8: u8 = imm as u8;
    unsafe {
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &op83, 1) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &reg_modrm, 1) != 0) { return 0 - 1; }
      return pipeline_elf_ctx_append_bytes(elf_ctx, &d8, 1);
    }
    return 0 - 1;
  }
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &op_prefix, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &reg_modrm, 1) != 0) { return 0 - 1; }
  }
  return x86_enc_append_i32_le(elf_ctx, imm);
}


// ---- Cap residual pure R2 wave1: arch_x86_64_enc fixed/multi insn (product C ABI) ----
// G.7: product authority for arch_x86_64_enc_* C symbols is this TU + seed FROM_X rest;
// arch/x86_64_enc.x is high-level import API (different names/types), not this link surface.

/** Emit x86_64 function prologue: push rbp; mov rbp,rsp; push rbx; sub rsp,frame.
 * Saves rbx (callee-saved) because body may use it as array/const base (SysV).
 *
 * SysV AMD64 stack alignment (G.7 authority for pure-asm CALL sites):
 *   At function entry RSP ≡ 8 (mod 16). After `push rbp` + `push rbx`, RSP ≡ 8.
 *   ABI requires RSP ≡ 0 (mod 16) immediately before every CALL. Therefore the
 *   `sub rsp, imm` amount must be ≡ 8 (mod 16). compute_frame_size rounds to a
 *   multiple of 16 (≡ 0), which alone leaves CALL sites misaligned and crashes
 *   glibc paths that use SSE/movaps (e.g. mktime/tzset → sscanf → SEGV in
 *   format_timezone / wall_local_offset_min). Locals stay rbp-relative; padding
 *   only grows the sub amount. Epilogue lea rsp,[rbp-8]; pop rbx; pop rbp is
 *   independent of the padded size.
 *
 * PLATFORM: SHARED — x86_64 SysV (LINUX gold + Darwin x86_64). Cap residual pure R2 wave1.
 * @param elf_ctx opaque ElfCodegenCtx*
 * @param frame_size stack frame bytes (LE encoded into sub imm32); padded to ≡8 mod 16
 * @return 0 on success, -1 on failure
 */
#[no_mangle]
export function arch_x86_64_enc_enc_prologue(elf_ctx: *u8, frame_size: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 85) != 0) { return 0 - 1; }
  let mov: u8[3] = [72, 137, 229];
  if (x86_enc_bytes(elf_ctx, mov, 3) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 83) != 0) { return 0 - 1; }
  // Pad frame so after push rbp+push rbx, RSP ≡ 0 before body CALLs (SysV 16B).
  let fs_i: i32 = frame_size;
  if (fs_i < 0) { fs_i = 0; }
  let rem: i32 = fs_i % 16;
  if (rem != 8) {
    // rem in 0..15; add (8-rem) mod 16, with positive remainder.
    if (rem < 8) {
      fs_i = fs_i + (8 - rem);
    } else {
      fs_i = fs_i + (16 - rem + 8);
    }
  }
  let sub: u8[7] = [72, 129, 236, 0, 0, 0, 0];
  let fs: u32 = fs_i as u32;
  sub[3] = (fs & 255) as u8;
  sub[4] = ((fs / 256) & 255) as u8;
  sub[5] = ((fs / 65536) & 255) as u8;
  sub[6] = ((fs / 16777216) & 255) as u8;
  return x86_enc_bytes(elf_ctx, sub, 7);
}

/** Emit x86_64 epilogue: lea rsp,[rbp-8]; pop rbx; pop rbp; ret.
 * Mirrors prologue push rbx. PLATFORM: SHARED — x86_64 SysV.
 * Cap residual pure R2 wave1.
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on failure
 */
#[no_mangle]
export function arch_x86_64_enc_enc_epilogue(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let lea: u8[4] = [72, 141, 101, 248];
  if (x86_enc_bytes(elf_ctx, lea, 4) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 91) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 93) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 195);
}

/** Emit fixed x86_64 insn `add_rax_rbx` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_add_rax_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 1, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit `andq %rbx, %rax` (REX.W 48 21 D8).
 * Prior 2-byte `andl %ebx, %eax` (21 D8) zero-extended EAX and wiped
 * the high 32 bits, truncating usize/ptr bitwise AND.
 * i32 AND of zero-extended operands is unchanged in the low 32.
 * Twin of ARM64 ELF `and x0, x0, x1` (64-bit).
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64 — SysV encode path.
 * @param elf_ctx *u8 — opaque ElfCodegenCtx*; null → -1
 * @return i32 — 0 success, -1 null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_and_rbx_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 33, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit `orq %rbx, %rax` (REX.W 48 09 D8).
 * Prior 2-byte `orl %ebx, %eax` (09 D8) zero-extended EAX after each OR,
 * so `g02f_load_ptr_at` usize `| (byte << n)` kept only the low 32 bits
 * (Ubuntu ELF: module 0x7ffff7ef9950 → 0xf7ef9950 SIGSEGV in
 * glue_module_func_index_by_name). SHL of usize was already 64-bit.
 * i32 OR of zero-extended operands is unchanged in the low 32.
 * Twin of ARM64 ELF `orr x0, x0, x1` (64-bit).
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64 — SysV encode path.
 * @param elf_ctx *u8 — opaque ElfCodegenCtx*; null → -1
 * @return i32 — 0 success, -1 null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_or_rbx_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 9, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit `xorq %rbx, %rax` (REX.W 48 31 D8).
 * Same REX.W as AND/OR: 32-bit `xorl` wiped high 32 of usize/ptr XOR.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64 — SysV encode path.
 * @param elf_ctx *u8 — opaque ElfCodegenCtx*; null → -1
 * @return i32 — 0 success, -1 null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_xor_rbx_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 49, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `mov_rax_to_rbx` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 137, 195];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `mov_rbx_to_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rbx_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 137, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `mov_rbx_to_ecx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rbx_to_ecx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [137, 217];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `mov_edx_to_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [137, 208];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `not_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_not_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [247, 208];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `neg_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_neg_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [247, 216];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `test_eax_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_test_eax_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [133, 192];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `test_rbx_rbx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_test_rbx_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [133, 219];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `test_edx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_test_edx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [133, 210];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `cmp_rbx_rax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_cmp_rbx_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [57, 195];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `cmp_rax_rbx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_cmp_rax_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [57, 216];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `cltd` (1 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_cltd(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[1] = [153];
  return x86_enc_bytes(elf_ctx, ins, 1);
}

/** Emit fixed x86_64 insn `idiv_rbx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_idiv_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [247, 251];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `imul_rbx_rax` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_imul_rbx_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 15, 175, 195];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `push_rax` (1 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_push_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[1] = [80];
  return x86_enc_bytes(elf_ctx, ins, 1);
}

/** Emit fixed x86_64 insn `push_rbx` (1 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_push_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[1] = [83];
  return x86_enc_bytes(elf_ctx, ins, 1);
}

/** Emit fixed x86_64 insn `pop_rbx` (1 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_pop_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[1] = [91];
  return x86_enc_bytes(elf_ctx, ins, 1);
}

/** Emit fixed x86_64 insn `pop_rax` (1 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_pop_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[1] = [88];
  return x86_enc_bytes(elf_ctx, ins, 1);
}

/** Emit fixed x86_64 insn `shl_cl_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_shl_cl_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [211, 224];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `shr_cl_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_shr_cl_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [211, 232];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `sar_cl_eax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sar_cl_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [211, 248];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `shl_cl_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_shl_cl_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 211, 224];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `shr_cl_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_shr_cl_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 211, 232];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `sar_cl_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sar_cl_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 211, 248];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `xor_edx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_xor_edx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [49, 210];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `div_rbx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_div_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [247, 243];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `load_32_from_rax` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_32_from_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [139, 0];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `load_64_from_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_64_from_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 139, 0];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `load_zext8_from_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_zext8_from_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [15, 182, 0];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `rax_plus_rbx_scale1` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_rax_plus_rbx_scale1(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 4, 24];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `rax_plus_rbx_scale4` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_rax_plus_rbx_scale4(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 4, 152];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `rax_plus_rbx_scale8` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_rax_plus_rbx_scale8(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 4, 216];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `lea_rbx_plus_rcx_scale1` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 28, 11];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `lea_rbx_plus_rcx_scale4` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 28, 139];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `lea_rbx_plus_rcx_scale8` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 141, 28, 203];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `add_ecx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_add_ecx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [1, 209];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `sub_ecx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_ecx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [41, 209];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `add_ebx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_add_ebx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [1, 211];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/** Emit fixed x86_64 insn `sub_ebx_edx` (2 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_ebx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[2] = [41, 211];
  return x86_enc_bytes(elf_ctx, ins, 2);
}

/**
 * Emit `imul %edx, %ecx` — index_scratch primary *= secondary (ecx = ecx * edx).
 * Opcode: 0F AF /r IMUL r32,r/m32; reg=ecx(001), rm=edx(010) → ModRM 0xCA.
 * Wave184 root-fix: was 0xD1 (IMUL edx,ecx) leaving product in edx; primary is ecx.
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_imul_ecx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [15, 175, 202];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/**
 * Emit `imul %edx, %ebx` — INDEX read path primary rbx *= secondary (ebx = ebx * edx).
 * Opcode: 0F AF /r IMUL r32,r/m32; reg=ebx(011), rm=edx(010) → ModRM 0xDA.
 * Wave184 root-fix: was 0xD3 (IMUL edx,ebx) leaving product in edx; scale uses rbx.
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_imul_ebx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [15, 175, 218];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `sub_rax_rbx` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_rax_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 41, 216];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `load_qword_from_rbx_to_rax` (3 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[3] = [72, 139, 3];
  return x86_enc_bytes(elf_ctx, ins, 3);
}

/** Emit fixed x86_64 insn `load_qword_rbx8_to_rdx` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins: u8[4] = [72, 139, 83, 8];
  return x86_enc_bytes(elf_ctx, ins, 4);
}

/** Emit fixed x86_64 insn `sub_rbx_rax_then_mov` (6 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_rbx_rax_then_mov(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins0: u8[3] = [72, 41, 195];
  if (x86_enc_bytes(elf_ctx, ins0, 3) != 0) { return 0 - 1; }
  let ins1: u8[3] = [72, 137, 216];
  return x86_enc_bytes(elf_ctx, ins1, 3);
}

/** Emit fixed x86_64 insn `rsub_ecx_edx` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_rsub_ecx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins0: u8[2] = [41, 202];
  if (x86_enc_bytes(elf_ctx, ins0, 2) != 0) { return 0 - 1; }
  let ins1: u8[2] = [137, 209];
  return x86_enc_bytes(elf_ctx, ins1, 2);
}

/** Emit fixed x86_64 insn `rsub_ebx_edx` (4 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_rsub_ebx_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins0: u8[2] = [41, 218];
  if (x86_enc_bytes(elf_ctx, ins0, 2) != 0) { return 0 - 1; }
  let ins1: u8[2] = [137, 211];
  return x86_enc_bytes(elf_ctx, ins1, 2);
}

/** Emit fixed x86_64 insn `setz_movzbl_eax` (6 bytes).
 * Cap residual pure R2 wave1: product C ABI bridge for backend_enc_dispatch.
 * PLATFORM: SHARED — x86_64 SysV encode path (Linux/macOS product asm).
 * @param elf_ctx opaque ElfCodegenCtx*
 * @return 0 on success, -1 on null/overflow
 */
#[no_mangle]
export function arch_x86_64_enc_enc_setz_movzbl_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let ins0: u8[3] = [15, 148, 192];
  if (x86_enc_bytes(elf_ctx, ins0, 3) != 0) { return 0 - 1; }
  let ins1: u8[3] = [15, 182, 192];
  return x86_enc_bytes(elf_ctx, ins1, 3);
}

// ---- Cap residual pure R2 wave2: label/imm/jcc/rbp/arg/call (product C ABI) ----
// G.7: same authority as wave1 — this TU + seed FROM_X rest.

/**
 * Define a code label; when is_func!=0, pad text to 4-byte alignment then
 * export the function symbol (Mach-O may add a leading underscore).
 *
 * **Ordering contract (Stage12 pure-asm product root):** pass0 may hoist
 * `let code_len = emit_code_len()` (and code_len2/3) to the top of their
 * enclosing block. If those lets share a block with `pad_code_to_4` side
 * effects, code_len is captured **before** padding zeros are appended →
 * exported sym/label points at the zero pad, not the real prologue →
 * multi-function pure-asm SEGV (Ubuntu `tests/types/overload.x`: pick_i64/main
 * start with `00 00 00` then `55 48 89 e5`). Mitigation: pad in one block,
 * then capture emit_code_len + add_label/add_sym in a **later** block
 * (same shape as `x86_enc_jcc_rel32` / enc_jmp / enc_call). Do not merge.
 *
 * @param elf_ctx opaque ElfCodegenCtx*
 * @param name label/symbol bytes (not necessarily NUL-terminated; use name_len)
 * @param name_len byte length of name; Mach-O underscore path requires 1..127
 * @param is_func non-zero: pad code to 4 and add exported symbol
 * @return 0 on success, -1 on failure
 * PLATFORM: SHARED — ELF/Mach-O product asm encode (LINUX gold for multi-func).
 */
#[no_mangle]
export function arch_x86_64_enc_enc_label(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (name == 0) { return 0 - 1; }
  if (name_len < 0) { return 0 - 1; }
  // Block 1: pad only. Must complete before any emit_code_len() let.
  if (is_func != 0) {
    unsafe {
      if (pipeline_elf_ctx_pad_code_to_4(elf_ctx) != 0) { return 0 - 1; }
    }
  }
  // Block 2: capture code_len after pad; register label + optional export sym.
  // Hoist of emit_code_len stays inside this block only (pad already done).
  unsafe {
    let code_len: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx);
    if (pipeline_elf_ctx_add_label(elf_ctx, name, name_len, code_len) != 0) { return 0 - 1; }
    if (is_func == 0) { return 0; }
    // Mach-O: export with leading underscore when host requests it.
    // wave580 Cap: mn u8[128] holds '_' + up to 127 content (was 63).
    if (pipeline_elf_ctx_macho_leading_underscore(elf_ctx) != 0 && name_len > 0 && name_len <= 127 && name[0] != 95) {
      let mn: u8[128] = [0];
      mn[0] = 95;
      let k: i32 = 0;
      while (k < name_len && k < 127) {
        mn[k + 1] = name[k];
        k = k + 1;
      }
      let code_len2: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx);
      return pipeline_elf_ctx_add_sym(elf_ctx, &mn[0], name_len + 1, code_len2);
    }
    let code_len3: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx);
    return pipeline_elf_ctx_add_sym(elf_ctx, name, name_len, code_len3);
  }
  return 0 - 1;
}

/** cmp + setcc + movzbl %al,%eax for condition code cc (0..5).
 * Cap residual pure R2 wave2. PLATFORM: SHARED — x86_64 SysV encode.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_cmp_setcc_movzbl(elf_ctx: *u8, cc: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let op: u8 = 148;
  if (cc == 1) { op = 149; }
  else if (cc == 2) { op = 156; }
  else if (cc == 3) { op = 158; }
  else if (cc == 4) { op = 159; }
  else if (cc == 5) { op = 157; }
  let s: u8[3] = [15, 0, 192];
  s[1] = op;
  if (x86_enc_bytes(elf_ctx, s, 3) != 0) { return 0 - 1; }
  let m: u8[3] = [15, 182, 192];
  return x86_enc_bytes(elf_ctx, m, 3);
}

/**
 * syscall instruction (0F 05) — stage 10 S3.1 slice 2 (10.1.1) raw syscall
 * builtin ELF lowering. Linux x86_64 kernel ABI: nr in rax, args in
 * rdi/rsi/rdx/r10/r8/r9, return rax; rcx/r11 clobbered by the instruction.
 * Consumed by try_emit_raw_syscall_call_elf_c (backend_call_dispatch.x).
 * PLATFORM: LINUX|x86_64 runtime effect; SHARED emit code.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_syscall(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 5);
}

/**
 * `movl (%rcx), %eax` (8B 01) — load *expected after expected_ptr lives in rcx.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movl_mem_rcx_to_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 139) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `lock cmpxchg %edx, (%rbx)` (F0 0F B1 13) — CAS with ptr in rbx so eax keeps
 * expected (eax is the low half of rax; ptr must not share rax).
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 240) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 177) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 19);
}

/**
 * `movl (%rax), %eax` (8B 00) — 10.4.1 atomic_load_i32 asm lowering.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 139) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 0);
}

/**
 * `xchg %edx, (%rax)` (87 10) — 10.4.1 atomic_store_i32 asm lowering.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_xchg_edx_mem_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 135) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 16);
}

/**
 * `mov %rax, %rcx` (48 89 C1) — scratch for atomic_cas expected-ptr update.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 193);
}

/**
 * `movl %eax, (%rcx)` (89 01) — write old CAS value to *expected.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movl_eax_to_mem_rcx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `lock cmpxchg %edx, (%rax)` (F0 0F B1 10) — 10.4.1 atomic_cas_i32.
 * Pre: eax=expected, edx=desired, rax=ptr. Post: eax=old; ZF=success.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 240) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 177) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 16);
}

/**
 * `sete %al` (0F 94 C0) — CAS success flag.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sete_al(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 148) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 192);
}

/**
 * `movzbl %al, %eax` (0F B6 C0) — zero-extend sete result.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 182) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 192);
}

/**
 * `mov %eax, %edx` (89 C2) — copy i32 desired/val into edx for xchg/cmpxchg.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 194);
}

/**
 * `movq (%rax), %rax` (48 8B 00) — 10.4.1 slice2 atomic_load_i64.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 139) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 0);
}

/**
 * `xchg %rdx, (%rax)` (48 87 10) — 10.4.1 slice2 atomic_store_i64.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_xchg_rdx_mem_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 135) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 16);
}

/**
 * `mov %rax, %rdx` (48 89 C2) — i64 desired/val into rdx for xchg/cmpxchg.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 194);
}

/**
 * `movq (%rcx), %rax` (48 8B 01) — load *expected (i64) with ptr parked in rbx.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 139) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `movq %rax, (%rcx)` (48 89 01) — write old CAS i64 value to *expected.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `lock cmpxchg %rdx, (%rbx)` (F0 48 0F B1 13) — 10.4.1 slice2 atomic_cas_i64.
 * Pre: rax=expected, rdx=desired, rbx=ptr. Post: rax=old; ZF=success.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 240) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 177) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 19);
}

/**
 * `mfence` (0F AE F0) — 10.4.2 atomic_fence_seq_cst.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mfence(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 174) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 240);
}

/**
 * `lfence` (0F AE E8) — 10.4.2 atomic_fence_acquire.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lfence(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 174) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 232);
}

/**
 * `sfence` (0F AE F8) — 10.4.2 atomic_fence_release.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_sfence(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 174) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 248);
}

/**
 * `movzwl (%rax), %eax` (0F B7 00) — 10.4.1 slice3 atomic_load_i16.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 183) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 0);
}

/**
 * `xchg %dx, (%rax)` (66 87 10) — 10.4.1 slice3 atomic_store_i16.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_xchg_dx_mem_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 102) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 135) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 16);
}

/**
 * `mov %ax, %dx` (66 89 C2) — i16 desired/val into dx.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 102) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 194);
}

/**
 * `movzwl (%rcx), %eax` (0F B7 01) — load *expected i16 with ptr in rbx.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 183) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `movw %ax, (%rcx)` (66 89 01) — write old CAS i16 to *expected.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_movw_ax_to_mem_rcx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 102) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 1);
}

/**
 * `lock cmpxchg %dx, (%rbx)` (F0 66 0F B1 13) — 10.4.1 slice3 atomic_cas_i16.
 * Pre: ax=expected, dx=desired, rbx=ptr. Post: ax=old; ZF=success.
 * PLATFORM: SHARED emit · x86_64 runtime.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 240) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 102) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 15) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 177) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 19);
}

/**
 * mov %rax, %r10 (49 89 C2) — stage 10 S3.1 slice 2 (10.1.1): syscall arg4
 * home. r10 has no slot in the C-ABI mov_rax_to_arg_reg k table, so this raw
 * form is the single r10 path (G.7; do not fork a second register map).
 * PLATFORM: LINUX|x86_64 runtime effect; SHARED emit code.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 73) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 194);
}

/**
 * mov %r10, %rax (4C 89 D0) — reverse of enc_mov_rax_to_r10.
 * Stage10 10.2.1 slice7: lateout/out("r10") → rax before store.
 * G.7: same r10 family as syscall arg4; do not invent a second map.
 * PLATFORM: LINUX|x86_64 runtime effect; SHARED emit code.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 76) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 208);
}

/**
 * mov %rax, %r11 (49 89 C3).
 * Stage10 10.2.3: Windows x64 / SysV volatile scratch r11 in-reg operand.
 * @param elf_ctx *u8 Pointer to ElfCodegenCtx.
 * @return i32 0 on success, -1 on null ctx or write failure.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_r11(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 73) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 195);
}

/**
 * mov %r11, %rax (4C 89 D8).
 * Stage10 10.2.3: Windows x64 / SysV volatile scratch r11 lateout/out operand.
 * @param elf_ctx *u8 Pointer to ElfCodegenCtx.
 * @return i32 0 on success, -1 on null ctx or write failure.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_r11_to_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 76) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 137) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 216);
}

/**
 * pause instruction (F3 90).
 * Stage10 10.2.3: Windows / x86 spinloop pause hint.
 * @param elf_ctx *u8 Pointer to ElfCodegenCtx.
 * @return i32 0 on success, -1 on null ctx or write failure.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_pause(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 243) != 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 144);
}

/**
 * int3 instruction (CC).
 * Stage10 10.2.3: Windows __debugbreak / breakpoint trap.
 * @param elf_ctx *u8 Pointer to ElfCodegenCtx.
 * @return i32 0 on success, -1 on null ctx or write failure.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_int3(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_u8(elf_ctx, 204);
}

/** mov imm32 to ebx (B8+reg form). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_imm32_to_rbx(elf_ctx: *u8, imm32: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 187) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, imm32);
}

/** mov imm32 to eax then return path (ret_imm32 surface). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_ret_imm32(elf_ctx: *u8, imm32: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 184) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, imm32);
}

/** movabs imm64 (lo,hi) to rax. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_imm64_to_rax(elf_ctx: *u8, lo: i32, hi: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 184) != 0) { return 0 - 1; }
  if (x86_enc_u32_le(elf_ctx, lo) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, hi);
}

/** cmp eax, imm32. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_cmp_eax_imm32(elf_ctx: *u8, imm32: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 61) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, imm32);
}

/** add imm32 to rax (REX.W add rax,imm32). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_add_imm_to_rax(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm == 0) { return 0; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 5) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, imm);
}

/** add imm32 to rbx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_add_imm_to_rbx(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm == 0) { return 0; }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 129) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 195) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, imm);
}

/** movq %rax, -offset(%rbp). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_store_rax_to_rbp(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_store_rax_to_rbp_neg(elf_ctx, offset);
}

/**
 * movq %r64, -offset(%rbp) for any GP 0..15 (rax..r15).
 * Completes backend_enc_store_x_reg_to_rbp_arch on Linux x86_64 (F7 dyn
 * coerce stores the vtable pointer from rcx=1). Same disp convention as
 * store_rax_to_rbp_neg: offset is the frame slot below %rbp.
 * @param elf_ctx *u8 — ElfCodegenCtx
 * @param reg i32 — hardware register 0..15
 * @param offset i32 — positive rbp-down slot
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU x86_64 SysV
 */
#[no_mangle]
export function arch_x86_64_enc_enc_store_r64_to_rbp(elf_ctx: *u8, reg: i32, offset: i32): i32 {
  if (elf_ctx == 0 as *u8) { return 0 - 1; }
  if (reg < 0 || reg > 15) { return 0 - 1; }
  return x86_enc_store_r64_to_rbp_neg(elf_ctx, reg, offset);
}

/** movq -offset(%rbp), %rax. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 69, 133);
}

/** movq -offset(%rbp), %rbx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 93, 157);
}

/** leaq -offset(%rbp), %rax. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_lea_rbp_to_rax(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 69, 133);
}

/** leaq -offset(%rbp), %rbx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_lea_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_lea_from_rbp_neg(elf_ctx, offset, 93, 157);
}

/** movq +off_pos(%rbp), %rax (positive frame offset). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_pos_to_rax(elf_ctx: *u8, off_pos: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let disp: i32 = off_pos;
  if (disp < 0) { disp = 0; }
  if (disp <= 127) {
    let buf: u8[4] = [72, 139, 69, 0];
    buf[3] = disp as u8;
    return x86_enc_bytes(elf_ctx, buf, 4);
  }
  let buf2: u8[7] = [72, 139, 133, 0, 0, 0, 0];
  let w: u32 = disp as u32;
  buf2[3] = (w & 255) as u8;
  buf2[4] = ((w / 256) & 255) as u8;
  buf2[5] = ((w / 65536) & 255) as u8;
  buf2[6] = ((w / 16777216) & 255) as u8;
  return x86_enc_bytes(elf_ctx, buf2, 7);
}

/** movl -offset(%rbp), %eax. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_eax32(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 69, 133);
}

/** movl -offset(%rbp), %ebx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_ebx32(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 93, 157);
}

/** movl -offset(%rbp), %ecx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_ecx(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 77, 141);
}

/** movl -offset(%rbp), %edx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_edx(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movl_from_rbp_neg32(elf_ctx, offset, 85, 149);
}

/** add imm to ecx (alu_imm32 template). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_add_imm_to_ecx(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 193);
}

/** sub imm from ecx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_imm_from_ecx(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 233);
}

/** add imm to ebx (index path). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_add_imm_to_ebx_index(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 195);
}

/** sub imm from ebx (index path). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_sub_imm_from_ebx_index(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_alu_imm32_to_reg(elf_ctx, imm, 129, 235);
}

/** imul ecx,ecx,imm (skip if imm<=1). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_imul_imm_to_ecx(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm <= 1) { return 0; }
  if (imm >= 0 - 128 && imm <= 127) {
    let buf: u8[3] = [107, 201, 0];
    buf[2] = imm as u8;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  let buf2: u8[6] = [105, 201, 0, 0, 0, 0];
  let w: u32 = imm as u32;
  buf2[2] = (w & 255) as u8;
  buf2[3] = ((w / 256) & 255) as u8;
  buf2[4] = ((w / 65536) & 255) as u8;
  buf2[5] = ((w / 16777216) & 255) as u8;
  return x86_enc_bytes(elf_ctx, buf2, 6);
}

/** imul ebx,ebx,imm (skip if imm<=1). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_imul_imm_to_ebx(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm <= 1) { return 0; }
  if (imm >= 0 - 128 && imm <= 127) {
    let buf: u8[3] = [107, 219, 0];
    buf[2] = imm as u8;
    return x86_enc_bytes(elf_ctx, buf, 3);
  }
  let buf2: u8[6] = [105, 219, 0, 0, 0, 0];
  let w: u32 = imm as u32;
  buf2[2] = (w & 255) as u8;
  buf2[3] = ((w / 256) & 255) as u8;
  buf2[4] = ((w / 65536) & 255) as u8;
  buf2[5] = ((w / 16777216) & 255) as u8;
  return x86_enc_bytes(elf_ctx, buf2, 6);
}

/** mov SysV arg_reg[k] -> rax (k clamped 0..5). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_arg_reg_to_rax(elf_ctx: *u8, k: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let idx: i32 = k;
  if (idx < 0) { idx = 0; }
  if (idx > 5) { idx = 5; }
  if (idx == 0) {
    let b0: u8[3] = [72, 137, 248];
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if (idx == 1) {
    let b1: u8[3] = [72, 137, 240];
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if (idx == 2) {
    let b2: u8[3] = [72, 137, 208];
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if (idx == 3) {
    let b3: u8[3] = [72, 137, 200];
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if (idx == 4) {
    let b4: u8[3] = [76, 137, 192];
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  let b5: u8[3] = [76, 137, 200];
  return x86_enc_bytes(elf_ctx, b5, 3);
}

/** mov rax -> SysV arg_reg[k] (k clamped 0..5). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rax_to_arg_reg(elf_ctx: *u8, k: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let idx: i32 = k;
  if (idx < 0) { idx = 0; }
  if (idx > 5) { idx = 5; }
  if (idx == 0) {
    let b0: u8[3] = [72, 137, 199];
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if (idx == 1) {
    let b1: u8[3] = [72, 137, 198];
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if (idx == 2) {
    let b2: u8[3] = [72, 137, 194];
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if (idx == 3) {
    let b3: u8[3] = [72, 137, 193];
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if (idx == 4) {
    let b4: u8[3] = [73, 137, 192];
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  let b5: u8[3] = [73, 137, 193];
  return x86_enc_bytes(elf_ctx, b5, 3);
}

/** jz rel32 label (0F 84). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_jz(elf_ctx: *u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}

/** jeq alias of jz. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_jeq(elf_ctx: *u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_jcc_rel32(elf_ctx, 132, label, label_len);
}

/** jge rel32 label (0F 8D). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_jge(elf_ctx: *u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_jcc_rel32(elf_ctx, 141, label, label_len);
}

/** jnz rel32 label (0F 85). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_jnz(elf_ctx: *u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_jcc_rel32(elf_ctx, 133, label, label_len);
}

/** jmp rel32 + patch. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_jmp(elf_ctx: *u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (label == 0) { return 0 - 1; }
  if (label_len <= 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 233) != 0) { return 0 - 1; }
  if (x86_enc_u32_le(elf_ctx, 0) != 0) { return 0 - 1; }
  unsafe {
    let rel32_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
    if (pipeline_elf_ctx_ensure_label(elf_ctx, label, label_len) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_patch(elf_ctx, rel32_at, label, label_len, 0);
  }
  return 0 - 1;
}

/** call rel32 + reloc (Mach-O leading underscore when required).
 * Cap residual pure R2 wave2. PLATFORM: SHARED — ELF/Mach-O product asm.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_call(elf_ctx: *u8, name: *u8, name_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (name == 0) { return 0 - 1; }
  if (name_len <= 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 232) != 0) { return 0 - 1; }
  if (x86_enc_u32_le(elf_ctx, 0) != 0) { return 0 - 1; }
  unsafe {
    let rel32_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
    // PLATFORM: MACOS|DARWIN — always prepend '_' for C call names (even if the
    // C name itself starts with '_', e.g. __error → ___error). Stage 12.0.5.
    if (pipeline_elf_ctx_macho_leading_underscore(elf_ctx) != 0 && name_len > 0 && name_len <= 127) {
      let rn: u8[128] = [0];
      rn[0] = 95;
      let k: i32 = 0;
      while (k < name_len && k < 127) {
        rn[k + 1] = name[k];
        k = k + 1;
      }
      return pipeline_elf_ctx_append_reloc(elf_ctx, rel32_at, &rn[0], name_len + 1);
    }
    return pipeline_elf_ctx_append_reloc(elf_ctx, rel32_at, name, name_len);
  }
  return 0 - 1;
}

/** add rsp, nbytes (imm8 or imm32). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_add_rsp_imm(elf_ctx: *u8, nbytes: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (nbytes <= 0) { return 0; }
  if (nbytes <= 127) {
    if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
    if (x86_enc_u8(elf_ctx, 131) != 0) { return 0 - 1; }
    if (x86_enc_u8(elf_ctx, 196) != 0) { return 0 - 1; }
    return x86_enc_u8(elf_ctx, nbytes as u8);
  }
  if (x86_enc_u8(elf_ctx, 72) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 129) != 0) { return 0 - 1; }
  if (x86_enc_u8(elf_ctx, 196) != 0) { return 0 - 1; }
  return x86_enc_u32_le(elf_ctx, nbytes);
}

/** store rax through (%rbx) by elem size 1/4/8. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_store_rax_to_rbx_indirect(elf_ctx: *u8, elem_sz: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (elem_sz == 1) {
    let b1: u8[2] = [136, 3];
    return x86_enc_bytes(elf_ctx, b1, 2);
  }
  if (elem_sz == 4) {
    let b4: u8[2] = [137, 3];
    return x86_enc_bytes(elf_ctx, b4, 2);
  }
  let b8: u8[3] = [72, 137, 3];
  return x86_enc_bytes(elf_ctx, b8, 3);
}

/** store rax to offset(%rbx) size 1/4/8. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_store_rax_to_rbx_offset(elf_ctx: *u8, offset: i32, store_size: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let w: u32 = offset as u32;
  let b0: u8 = (w & 255) as u8;
  let b1: u8 = ((w / 256) & 255) as u8;
  let b2: u8 = ((w / 65536) & 255) as u8;
  let b3: u8 = ((w / 16777216) & 255) as u8;
  if (store_size == 1) {
    let buf: u8[6] = [136, 131, 0, 0, 0, 0];
    buf[2] = b0; buf[3] = b1; buf[4] = b2; buf[5] = b3;
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  if (store_size == 4) {
    let buf: u8[6] = [137, 131, 0, 0, 0, 0];
    buf[2] = b0; buf[3] = b1; buf[4] = b2; buf[5] = b3;
    return x86_enc_bytes(elf_ctx, buf, 6);
  }
  let buf8: u8[7] = [72, 137, 131, 0, 0, 0, 0];
  buf8[3] = b0; buf8[4] = b1; buf8[5] = b2; buf8[6] = b3;
  return x86_enc_bytes(elf_ctx, buf8, 7);
}

/** movq %rdx, -offset(%rbp) (16B struct high half). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_store_rdx_to_rbp(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_store_rdx_to_rbp_neg(elf_ctx, offset);
}

/** movq -offset(%rbp), %rdx. Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rbp_to_rdx(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  return x86_enc_movq_from_rbp_neg(elf_ctx, offset, 85, 149);
}

/** movq %rdx, arg_reg[k] (SysV 16B struct second GPR). Cap residual pure R2 wave2. PLATFORM: SHARED */
#[no_mangle]
export function arch_x86_64_enc_enc_mov_rdx_to_arg_reg(elf_ctx: *u8, k: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let idx: i32 = k;
  if (idx < 0) { idx = 0; }
  if (idx > 5) { idx = 5; }
  if (idx == 0) {
    let b0: u8[3] = [72, 137, 215];
    return x86_enc_bytes(elf_ctx, b0, 3);
  }
  if (idx == 1) {
    let b1: u8[3] = [72, 137, 214];
    return x86_enc_bytes(elf_ctx, b1, 3);
  }
  if (idx == 2) {
    let b2: u8[3] = [72, 137, 210];
    return x86_enc_bytes(elf_ctx, b2, 3);
  }
  if (idx == 3) {
    let b3: u8[3] = [72, 137, 209];
    return x86_enc_bytes(elf_ctx, b3, 3);
  }
  if (idx == 4) {
    let b4: u8[3] = [73, 137, 208];
    return x86_enc_bytes(elf_ctx, b4, 3);
  }
  let b5: u8[3] = [73, 137, 209];
  return x86_enc_bytes(elf_ctx, b5, 3);
}
