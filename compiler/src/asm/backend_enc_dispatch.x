// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// See implementation.
// backend_enc_dispatch_x_doc_anchor: see function docblock below.

/** Exported function `backend_enc_dispatch_x_doc_anchor`.
 * Implements `backend_enc_dispatch_x_doc_anchor`.
 * @return i32
 */
export function backend_enc_dispatch_x_doc_anchor(): i32 {
  return 0;
}

/* ---- G-02f-100 / G-02f-146：enc helpers ---- */
/* See implementation. */

// See implementation.







/* See implementation. */

// See implementation.
// See implementation.

export extern "C" function pipeline_elf_ctx_append_bytes(ctx: *u8, ptr: *u8, n: i32): i32;
export extern "C" function pipeline_elf_ctx_emit_code_len(ctx: *u8): i32;
export extern "C" function pipeline_elf_ctx_ensure_label(ctx: *u8, name: *u8, name_len: i32): i32;
export extern "C" function pipeline_elf_ctx_append_patch(ctx: *u8, rel32_offset: i32, name: *u8, name_len: i32, imm_bits: i32): i32;
export extern "C" function pipeline_elf_ctx_append_reloc(ctx: *u8, at: i32, name: *u8, name_len: i32): i32;
/**
 * Typed reloc append (PAGE21 / PAGEOFF12 / absolute64 sentinels).
 * Authority: pipeline_elf_ctx_append_reloc_typed in runtime_pipeline_abi.x.
 * PLATFORM: SHARED — F7 lea-of-symbol for vtable statics.
 */
export extern "C" function pipeline_elf_ctx_append_reloc_typed(ctx: *u8, at: i32, name: *u8, name_len: i32, r_type: i32, r_pcrel: i32): i32;
export extern "C" function pipeline_elf_ctx_append_reloc_absolute64(ctx: *u8, at: i32, name: *u8, name_len: i32): i32;
/**
 * Read ElfCodegenCtx.macho_leading_underscore via offsetof (ast_pool).
 * wave580 Cap: forbids hardcoding field offset (pre-Cap 598052 is stale after name[128]).
 * @param ctx *u8 — ElfCodegenCtx bytes
 * @return i32 — non-zero when Darwin leading '_' must be applied
 * PLATFORM: MACOS|DARWIN product pure-asm; 0 on LINUX/WINDOWS
 */
export extern "C" function pipeline_elf_ctx_macho_leading_underscore(ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_u32_le(elf_ctx: *u8, word: i32): i32;

// backend_enc_x86_jcc_rel32_c: see function docblock below.
/**
 * Emit x86_64 near jcc (`0F <opcode2> rel32`) and patch to `label`.
 *
 * Same ordering contract as `x86_enc_jcc_rel32`: append bytes in block 1, then
 * `emit_code_len()-4` + append_patch in block 2 so pass0 cannot hoist the
 * rel32 let before the jcc bytes (option/si instruction-stream corruption).
 *
 * @param elf_ctx opaque ElfCodegenCtx*
 * @param opcode2 second opcode byte
 * @param label patch target name
 * @param label_len name length; must be > 0
 * @return 0 on success, -1 on failure
 * PLATFORM: SHARED — x86_64 product asm encode path.
 */
#[no_mangle]
export function backend_enc_x86_jcc_rel32_c(elf_ctx: *u8, opcode2: u8, label: *u8, label_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (label == 0) { return 0 - 1; }
  if (label_len <= 0) { return 0 - 1; }
  let b0: u8 = 15;
  let b1: u8 = opcode2;
  let z: u8 = 0;
  // Block 1: append jcc skeleton only.
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b0, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b1, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &z, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &z, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &z, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &z, 1) != 0) { return 0 - 1; }
  }
  // Block 2: patch slot after appends (hoist-safe vs prior side effects).
  unsafe {
    let rel32_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
    if (pipeline_elf_ctx_ensure_label(elf_ctx, label, label_len) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_patch(elf_ctx, rel32_at, label, label_len, 32);
  }
  return 0 - 1;
}

/** Exported function `backend_enc_append_u32_le_c`.
 * Implements `backend_enc_append_u32_le_c`.
 * @param elf_ctx *u8
 * @param word u32
 * @return i32
 */
#[no_mangle]
export function backend_enc_append_u32_le_c(elf_ctx: *u8, word: u32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let b0: u8 = (word & 255) as u8;
  let b1: u8 = ((word / 256) & 255) as u8;
  let b2: u8 = ((word / 65536) & 255) as u8;
  let b3: u8 = ((word / 16777216) & 255) as u8;
  unsafe {
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b0, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b1, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b2, 1) != 0) { return 0 - 1; }
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b3, 1);
  }
  return 0 - 1;
}

// G-02f-146：ARM64 BL stub + reloc；macho_leading_underscore @ ElfCodegenCtx+598052 LE
/** Exported function `backend_enc_arm64_call_c`.
 * Implements `backend_enc_arm64_call_c`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_arm64_call_c(elf_ctx: *u8, name: *u8, name_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (name == 0) { return 0 - 1; }
  if (name_len <= 0) { return 0 - 1; }
  unsafe {
    // 0x94000000 BL imm26 placeholder
    if (backend_enc_append_u32_le_c(elf_ctx, (2483027968 as u32)) != 0) { return 0 - 1; }
    let at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
    if (at < 0) { return 0 - 1; }
    // wave580 Cap residual: G.7 API only — never hardcode ElfCodegenCtx offsets
    // (pre-Cap 598052 broke after name[64]→[128] table growth).
    // PLATFORM: MACOS|DARWIN arm64 BL reloc; LINUX flag 0.
    // Stage 12.0.5 ABI: always prepend '_' on Darwin for C link names.
    // Do NOT skip when name[0]=='_' — C reserved names like __error must become
    // ___error (host cc). Skipping left bare U __error → pure-ld fail / residual.
    let macho: i32 = pipeline_elf_ctx_macho_leading_underscore(elf_ctx);
    if (macho != 0 && name_len > 0 && name_len <= 127) {
      let reloc_name: u8[128] = [];
      reloc_name[0] = 95;
      let i: i32 = 0;
      while (i < name_len) {
        if (i >= 127) { break; }
        reloc_name[i + 1] = name[i];
        i = i + 1;
      }
      let reloc_len: i32 = name_len + 1;
      return pipeline_elf_ctx_append_reloc(elf_ctx, at, &reloc_name[0], reloc_len);
    }
    return pipeline_elf_ctx_append_reloc(elf_ctx, at, name, name_len);
  }
  return 0 - 1;
}

/**
 * Emit `blr xN` (branch with link to register) for ARM64 indirect call.
 * Used by F7 dyn Trait vtable dispatch to call through slot fn ptr.
 * @param elf_ctx *u8 — emit context (ElfCodegenCtx)
 * @param reg i32 — register number 0..30 (x0..x30); 31=x31/SP reserved
 * @return i32 — 0 success, -1 failure (null ctx or invalid reg)
 * PLATFORM: MACOS|ARM64 AAPCS64 — G.7 twin product seed.
 * Encoding: BLR xN = 0xD63F0000 | (N << 5); no reloc (reg encoded in insn).
 */
#[no_mangle]
export function backend_enc_arm64_blr_c(elf_ctx: *u8, reg: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (reg < 0) { return 0 - 1; }
  if (reg > 30) { return 0 - 1; }
  return backend_enc_append_u32_le_c(elf_ctx, (3595386880 as u32) | ((reg as u32) * 32));
}

/**
 * Emit `ldr xN, [xM, #off]` for ARM64 64-bit load (register base + unsigned imm12 offset).
 * Used by F7 dyn Trait vtable dispatch to load vtable ptr and slot fn ptr.
 * @param elf_ctx *u8 — emit context (ElfCodegenCtx)
 * @param dst_reg i32 — destination register 0..30
 * @param base_reg i32 — base register 0..30
 * @param offset i32 — byte offset; must be multiple of 8 in [0, 32760]
 * @return i32 — 0 success, -1 failure
 * PLATFORM: MACOS|ARM64 AAPCS64 — G.7 twin product seed.
 * Encoding: LDR (immediate, unsigned offset, 64-bit) =
 *   0xF9400000 | ((off/8)<<10) | (base<<5) | dst.
 */
#[no_mangle]
export function backend_enc_arm64_ldr_xreg_xreg_imm_c(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (dst_reg < 0) { return 0 - 1; }
  if (dst_reg > 30) { return 0 - 1; }
  if (base_reg < 0) { return 0 - 1; }
  if (base_reg > 30) { return 0 - 1; }
  if (offset < 0) { return 0 - 1; }
  if ((offset & 7) != 0) { return 0 - 1; }
  let imm12: i32 = offset / 8;
  if (imm12 > 4095) { imm12 = 4095; }
  return backend_enc_append_u32_le_c(
    elf_ctx,
    (4181721088 as u32) | ((imm12 as u32) * 1024) | ((base_reg as u32) * 32) | (dst_reg as u32)
  );
}

/**
 * Emit `call rN` for x86_64 indirect call (64-bit mode).
 * Used by F7 dyn Trait vtable dispatch on Linux/Ubuntu.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — register number 0..15 (rax..r15)
 * @return i32 — 0 success, -1 failure
 * PLATFORM: LINUX|UBUNTU x86_64 SysV — G.7 twin product seed.
 * Encoding: optional REX.B (0x41) for r8-r15; then FF /2 (ModRM=0xD0|(reg&7)).
 */
#[no_mangle]
export function backend_enc_x86_64_call_reg_c(elf_ctx: *u8, reg: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (reg < 0) { return 0 - 1; }
  if (reg > 15) { return 0 - 1; }
  unsafe {
    if (reg >= 8) {
      if (backend_enc_append_u8_c(elf_ctx, 65) != 0) { return 0 - 1; }
    }
    if (backend_enc_append_u8_c(elf_ctx, 255) != 0) { return 0 - 1; }
    return backend_enc_append_u8_c(elf_ctx, 208 | (reg & 7));
  }
  return 0 - 1;
}

/**
 * Emit `mov r64_dst, [r64_base + disp32]` for x86_64 64-bit load.
 * Used by F7 dyn Trait vtable dispatch on Linux/Ubuntu. Register numbers
 * are the hardware encoding (0=rax … 15=r15) so the arm64-style sequence
 * dst=1/base=0, dst=2/base=1, dst=0/base=0 maps to rcx/rax, rdx/rcx, rax/rax.
 * @param elf_ctx *u8 — emit context
 * @param dst_reg i32 — destination register 0..15
 * @param base_reg i32 — base register 0..15 (rsp/r12 get a SIB byte)
 * @param offset i32 — byte offset (disp32 form)
 * @return i32 — 0 success, -1 failure
 * PLATFORM: LINUX|UBUNTU x86_64 SysV — G.7 twin product seed.
 * Encoding: REX.W[+R][+B] + 8B /r (mod=10 disp32) [+SIB if base&7==4] + disp32.
 */
#[no_mangle]
export function backend_enc_x86_64_load_rax_rbx_disp32_c(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (dst_reg < 0 || dst_reg > 15) { return 0 - 1; }
  if (base_reg < 0 || base_reg > 15) { return 0 - 1; }
  unsafe {
    let rex: i32 = 72;
    if (dst_reg >= 8) { rex = rex + 4; }
    if (base_reg >= 8) { rex = rex + 1; }
    if (backend_enc_append_u8_c(elf_ctx, rex) != 0) { return 0 - 1; }
    if (backend_enc_append_u8_c(elf_ctx, 139) != 0) { return 0 - 1; }
    let modrm: i32 = 128 + ((dst_reg & 7) * 8) + (base_reg & 7);
    if (backend_enc_append_u8_c(elf_ctx, modrm) != 0) { return 0 - 1; }
    /* SIB required when r/m is rsp/r12 (encoding 4). */
    if ((base_reg & 7) == 4) {
      if (backend_enc_append_u8_c(elf_ctx, 36) != 0) { return 0 - 1; }
    }
    let b0: u8 = (offset & 255) as u8;
    let b1: u8 = ((offset / 256) & 255) as u8;
    let b2: u8 = ((offset / 65536) & 255) as u8;
    let b3: u8 = ((offset / 16777216) & 255) as u8;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b0, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b1, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b2, 1) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &b3, 1) != 0) { return 0 - 1; }
    return 0;
  }
  return 0 - 1;
}

/**
 * Emit `jalr x1, 0(xN)` for riscv64 indirect call (return addr in ra=x1).
 * Used by F7 dyn Trait vtable dispatch on riscv64 targets.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — register number 0..31 (x0..x31)
 * @return i32 — 0 success, -1 failure
 * PLATFORM: LINUX|UBUNTU riscv64 — G.7 twin product seed.
 * Encoding: jalr rd=1, rs1=N, imm=0, opcode=0x67 = (N<<15) | 0xE7.
 */
#[no_mangle]
export function backend_enc_riscv64_jalr_reg_c(elf_ctx: *u8, reg: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (reg < 0) { return 0 - 1; }
  if (reg > 31) { return 0 - 1; }
  return backend_enc_append_u32_le_c(elf_ctx, (231 as u32) | ((reg as u32) * 32768));
}

/**
 * Emit `ld rd, off(rs1)` for riscv64 64-bit load (register base + imm12 offset).
 * Used by F7 dyn Trait vtable dispatch on riscv64 targets.
 * @param elf_ctx *u8 — emit context
 * @param dst_reg i32 — destination register 0..31
 * @param base_reg i32 — base register 0..31
 * @param offset i32 — byte offset; must fit in signed imm12 [-2048, 2047]
 * @return i32 — 0 success, -1 failure
 * PLATFORM: LINUX|UBUNTU riscv64 — G.7 twin product seed.
 * Encoding: LD (rd, rs1, imm12) = (imm12<<20) | (rs1<<15) | (3<<12) | (rd<<7) | 3.
 */
#[no_mangle]
export function backend_enc_riscv64_ldr_xreg_xreg_imm_c(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (dst_reg < 0) { return 0 - 1; }
  if (dst_reg > 31) { return 0 - 1; }
  if (base_reg < 0) { return 0 - 1; }
  if (base_reg > 31) { return 0 - 1; }
  if (offset < 0) { return 0 - 1; }
  let imm12: i32 = offset & 4095;
  return backend_enc_append_u32_le_c(
    elf_ctx,
    ((imm12 as u32) * 1048576) | ((base_reg as u32) * 32768) | 12288 | ((dst_reg as u32) * 128) | 3
  );
}

// ADD X31, X31, #imm12 — 0x910003ff | (imm12<<10)
/** Exported function `backend_enc_arm64_add_sp_imm12_c`.
 * Implements `backend_enc_arm64_add_sp_imm12_c`.
 * @param elf_ctx *u8
 * @param imm i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_arm64_add_sp_imm12_c(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm <= 0) { return 0; }
  if (imm > 4095) {
    return backend_enc_append_u32_le_c(elf_ctx, (2432697343 as u32) | (4095 * 1024));
  }
  return backend_enc_append_u32_le_c(elf_ctx, (2432697343 as u32) | ((imm as u32) * 1024));
}

// SUB X31, X31, #imm12 — 0xd10003ff | (imm12<<10)
/** Exported function `backend_enc_arm64_sub_sp_imm12_c`.
 * Implements `backend_enc_arm64_sub_sp_imm12_c`.
 * @param elf_ctx *u8
 * @param imm i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_arm64_sub_sp_imm12_c(elf_ctx: *u8, imm: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (imm <= 0) { return 0; }
  if (imm > 4095) {
    return backend_enc_append_u32_le_c(elf_ctx, (3506439167 as u32) | (4095 * 1024));
  }
  return backend_enc_append_u32_le_c(elf_ctx, (3506439167 as u32) | ((imm as u32) * 1024));
}

// STR X0, [SP, #imm12*8] — 0xf90003e0 | (imm12<<10)
/** Exported function `backend_enc_arm64_str_x0_sp_offset_c`.
 * Implements `backend_enc_arm64_str_x0_sp_offset_c`.
 * @param elf_ctx *u8
 * @param off_bytes i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_arm64_str_x0_sp_offset_c(elf_ctx: *u8, off_bytes: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (off_bytes < 0) {
    return backend_enc_append_u32_le_c(elf_ctx, (4177527776 as u32));
  }
  if (off_bytes / 8 > 4095) {
    return backend_enc_append_u32_le_c(elf_ctx, (4177527776 as u32) | (4095 * 1024));
  }
  return backend_enc_append_u32_le_c(elf_ctx, (4177527776 as u32) | (((off_bytes / 8) as u32) * 1024));
}

/**
 * Load one 32-bit product-frame slot into x0 as a signed 64-bit value.
 * @param elf_ctx *u8 — emit context; null rejected
 * @param offset i32 — logical frame bytes; >=0, multiple of 4, /4 <= 4095
 * @return i32 — 0 ok, -1 bad ctx/offset
 * PLATFORM: MACOS|ARM64 — LDRSW x0,[x29,#off]
 *   0xB9800000 | ((off/4)<<10) | (29<<5) | Rt=0
 * Align thin: product frame is positive; prior LDUR [x29,#-off] is stale.
 */
#[no_mangle]
export function arm64_enc_load_w0_from_rbp_c(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (offset < 0) { return 0 - 1; }
  if ((offset % 4) != 0) { return 0 - 1; }
  if ((offset / 4) > 4095) { return 0 - 1; }
  unsafe {
    let imm12: i32 = offset / 4;
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((3112173568 as i32) | (imm12 * 1024) | 928));
  }
  return 0 - 1;
}

/**
 * Load one 32-bit product-frame slot into x1 as a signed 64-bit value.
 * @param elf_ctx *u8 — emit context; null rejected
 * @param offset i32 — logical frame bytes; >=0, multiple of 4, /4 <= 4095
 * @return i32 — 0 ok, -1 bad ctx/offset
 * PLATFORM: MACOS|ARM64 — LDRSW x1,[x29,#off] (Rt=1).
 */
#[no_mangle]
export function arm64_enc_load_w1_from_rbp_c(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (offset < 0) { return 0 - 1; }
  if ((offset % 4) != 0) { return 0 - 1; }
  if ((offset / 4) > 4095) { return 0 - 1; }
  unsafe {
    let imm12: i32 = offset / 4;
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((3112173568 as i32) | (imm12 * 1024) | 928 | 1));
  }
  return 0 - 1;
}

/**
 * Store w0 to product frame [x29, #offset] (32-bit STR, positive polarity).
 * @param elf_ctx *u8 — emit context
 * @param offset i32 — logical frame bytes; >=0, multiple of 4, /4 <= 4095
 * @return i32 — 0 ok, -1 failure
 * PLATFORM: MACOS|ARM64 — wave616: match product positive STR/LDR frame
 * (was STUR [x29,#-off] mismatched load_rbp_to_rax).
 */
#[no_mangle]
export function arm64_enc_store_w0_to_rbp_c(elf_ctx: *u8, offset: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (offset < 0) { return 0 - 1; }
  if ((offset % 4) != 0) { return 0 - 1; }
  if ((offset / 4) > 4095) { return 0 - 1; }
  unsafe {
    /* STR W0,[x29,#off]: 0xB9000000 | ((off/4)<<10) | (29<<5) */
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((3103785888 as u32) | (((offset / 4) as u32) * 1024)) as i32);
  }
  return 0 - 1;
}

/* ---- G-02f-206：backend_enc_*_arch ta-dispatch shells ---- */

export extern "C" function arch_arm64_enc_enc_add_imm_to_rax(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_arm64_enc_enc_add_imm_to_rbx(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_arm64_enc_enc_add_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_and_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cltd(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cmp_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cmp_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cmp_setcc_movzbl(elf_ctx: *u8, cc: i32): i32;
export extern "C" function pipeline_asm_arm64_cset_cond_enc_from_cc(cc: i32): i32;
export extern "C" function arch_arm64_enc_enc_epilogue(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_imul_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_jeq(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_jge(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_jmp(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_jnz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_jz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_label(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32): i32;
export extern "C" function arch_arm64_enc_enc_lea_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_lea_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_load_64_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_load_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_load_rbp_to_x2(elf_ctx: *u8, offset: i32): i32;
/* G.7 twin of arch_arm64_enc_enc_load_rbp_to_x2 with Rt=3 (x3 = INDEX secondary
 * scratch). Positive-offset LDR X3, [X29, #imm12] — must match primary loader's
 * positive-offset convention; old inline negated offset (LDUR [x29,-off]) loaded
 * garbage from below the frame for arr[i+j] right operand. */
export extern "C" function arch_arm64_enc_enc_load_rbp_to_x3(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_load_zext8_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_imm32_to_rbx(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_arm64_enc_enc_mov_imm64_to_rax(elf_ctx: *u8, lo: i32, hi: i32): i32;
export extern "C" function arch_arm64_enc_enc_mov_rax_to_arg_reg(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_arm64_enc_enc_mov_rax_to_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_rbx_to_ecx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_rbx_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_neg_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_not_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_or_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_pop_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_pop_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_prologue(elf_ctx: *u8, frame_sz: i32): i32;
export extern "C" function arch_arm64_enc_enc_push_rax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_push_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_rax_plus_rbx_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_rax_plus_rbx_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_rax_plus_rbx_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ret_imm32(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_arm64_enc_enc_sar_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_setz_movzbl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_shl_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_shr_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_store_rax_to_rbp(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_store_rax_to_rbx_indirect(elf_ctx: *u8, elem_sz: i32): i32;
export extern "C" function arch_arm64_enc_enc_store_rax_to_rbx_offset(elf_ctx: *u8, offset: i32, store_size: i32): i32;
export extern "C" function arch_arm64_enc_enc_sub_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_sub_rbx_rax_then_mov(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_test_eax_eax(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_test_rbx_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_xor_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_add_imm_to_rax(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_riscv64_enc_enc_add_imm_to_rbx(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_riscv64_enc_enc_add_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_and_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_call(elf_ctx: *u8, name: *u8, name_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_cltd(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_cmp_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_cmp_setcc_movzbl(elf_ctx: *u8, cc: i32): i32;
export extern "C" function arch_riscv64_enc_enc_epilogue(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_imul_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_jeq(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_jge(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_jmp(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_jnz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_jz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_riscv64_enc_enc_label(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32): i32;
export extern "C" function arch_riscv64_enc_enc_lea_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_lea_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_load_64_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_load_rbp_to_a2(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_load_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_load_zext8_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mov_imm32_to_rbx(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_riscv64_enc_enc_mov_imm64_to_rax(elf_ctx: *u8, lo: i32, hi: i32): i32;
export extern "C" function arch_riscv64_enc_enc_mov_rax_to_arg_reg(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_riscv64_enc_enc_mov_rax_to_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mov_rbx_to_ecx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mov_rbx_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_neg_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_not_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_or_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_pop_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_pop_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_prologue(elf_ctx: *u8, frame_sz: i32): i32;
export extern "C" function arch_riscv64_enc_enc_push_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_push_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rax_plus_rbx_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rax_plus_rbx_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rax_plus_rbx_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_ret_imm32(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_riscv64_enc_enc_sar_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_setz_movzbl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_shl_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_shr_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_store_rax_to_rbp(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_store_rax_to_rbx_indirect(elf_ctx: *u8, elem_sz: i32): i32;
export extern "C" function arch_riscv64_enc_enc_store_rax_to_rbx_offset(elf_ctx: *u8, offset: i32, store_size: i32): i32;
export extern "C" function arch_riscv64_enc_enc_sub_rbx_rax_then_mov(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_test_eax_eax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_test_rbx_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_xor_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_add_imm_to_rax(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_add_imm_to_rbx(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_add_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_and_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_call(elf_ctx: *u8, name: *u8, name_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_cltd(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_cmp_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_cmp_eax_imm32(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_x86_64_enc_enc_cmp_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_cmp_setcc_movzbl(elf_ctx: *u8, cc: i32): i32;
export extern "C" function arch_x86_64_enc_enc_epilogue(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_imul_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_jeq(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_jge(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_jmp(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_jnz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_jz(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_x86_64_enc_enc_label(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32): i32;
export extern "C" function arch_x86_64_enc_enc_lea_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_lea_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_64_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_ecx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_zext8_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_imm32_to_rbx(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_x86_64_enc_enc_mov_imm64_to_rax(elf_ctx: *u8, lo: i32, hi: i32): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_arg_reg(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rbx_to_ecx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rbx_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_neg_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_not_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_or_rbx_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_pop_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_pop_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_prologue(elf_ctx: *u8, frame_sz: i32): i32;
export extern "C" function arch_x86_64_enc_enc_push_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_push_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_rax_plus_rbx_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_rax_plus_rbx_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_rax_plus_rbx_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_ret_imm32(elf_ctx: *u8, imm32: i32): i32;
export extern "C" function arch_x86_64_enc_enc_sar_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sar_cl_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_setz_movzbl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_shl_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_shl_cl_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_shr_cl_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_shr_cl_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_store_rax_to_rbp(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_store_r64_to_rbp(elf_ctx: *u8, reg: i32, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_store_rax_to_rbx_indirect(elf_ctx: *u8, elem_sz: i32): i32;
export extern "C" function arch_x86_64_enc_enc_store_rax_to_rbx_offset(elf_ctx: *u8, offset: i32, store_size: i32): i32;
export extern "C" function arch_x86_64_enc_enc_sub_rax_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sub_rbx_rax_then_mov(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_test_eax_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_test_rbx_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_xor_rbx_rax(elf_ctx: *u8): i32;

// backend_enc_label_arch: see function docblock below.
/** Exported function `backend_enc_label_arch`.
 * Implements `backend_enc_label_arch`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @param is_func i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_label_arch(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_label(elf_ctx, name, name_len, is_func); }
  if (ta == 2) { return arch_riscv64_enc_enc_label(elf_ctx, name, name_len, is_func); }
  return arch_x86_64_enc_enc_label(elf_ctx, name, name_len, is_func);
  }
}

// backend_enc_prologue_arch: see function docblock below.
/** Exported function `backend_enc_prologue_arch`.
 * Implements `backend_enc_prologue_arch`.
 * @param elf_ctx *u8
 * @param frame_sz i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_prologue_arch(elf_ctx: *u8, frame_sz: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_prologue(elf_ctx, frame_sz); }
  if (ta == 2) { return arch_riscv64_enc_enc_prologue(elf_ctx, frame_sz); }
  return arch_x86_64_enc_enc_prologue(elf_ctx, frame_sz);
  }
}

// backend_enc_epilogue_arch: see function docblock below.
/** Exported function `backend_enc_epilogue_arch`.
 * Implements `backend_enc_epilogue_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_epilogue_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_epilogue(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_epilogue(elf_ctx); }
  return arch_x86_64_enc_enc_epilogue(elf_ctx);
  }
}

// backend_enc_ret_imm32_arch: see function docblock below.
/** Exported function `backend_enc_ret_imm32_arch`.
 * Implements `backend_enc_ret_imm32_arch`.
 * @param elf_ctx *u8
 * @param imm32 i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_ret_imm32_arch(elf_ctx: *u8, imm32: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_ret_imm32(elf_ctx, imm32); }
  if (ta == 2) { return arch_riscv64_enc_enc_ret_imm32(elf_ctx, imm32); }
  return arch_x86_64_enc_enc_ret_imm32(elf_ctx, imm32);
  }
}

// backend_enc_mov_imm32_to_rbx_arch: see function docblock below.
/** Exported function `backend_enc_mov_imm32_to_rbx_arch`.
 * Implements `backend_enc_mov_imm32_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param imm32 i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_imm32_to_rbx_arch(elf_ctx: *u8, imm32: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32); }
  return arch_x86_64_enc_enc_mov_imm32_to_rbx(elf_ctx, imm32);
  }
}

// backend_enc_mov_imm64_to_rax_arch: see function docblock below.
/** Exported function `backend_enc_mov_imm64_to_rax_arch`.
 * Implements `backend_enc_mov_imm64_to_rax_arch`.
 * @param elf_ctx *u8
 * @param lo i32
 * @param hi i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_imm64_to_rax_arch(elf_ctx: *u8, lo: i32, hi: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi); }
  return arch_x86_64_enc_enc_mov_imm64_to_rax(elf_ctx, lo, hi);
  }
}

// backend_enc_push_rax_arch: see function docblock below.
/** Exported function `backend_enc_push_rax_arch`.
 * Implements `backend_enc_push_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_push_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_push_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_push_rax(elf_ctx); }
  return arch_x86_64_enc_enc_push_rax(elf_ctx);
  }
}

// backend_enc_push_rbx_arch: see function docblock below.
/** Exported function `backend_enc_push_rbx_arch`.
 * Implements `backend_enc_push_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_push_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_push_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_push_rbx(elf_ctx); }
  return arch_x86_64_enc_enc_push_rbx(elf_ctx);
  }
}

// backend_enc_pop_rax_arch: see function docblock below.
/** Exported function `backend_enc_pop_rax_arch`.
 * Implements `backend_enc_pop_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_pop_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_pop_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_pop_rax(elf_ctx); }
  return arch_x86_64_enc_enc_pop_rax(elf_ctx);
  }
}

// backend_enc_pop_rbx_arch: see function docblock below.
/** Exported function `backend_enc_pop_rbx_arch`.
 * Implements `backend_enc_pop_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_pop_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_pop_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_pop_rbx(elf_ctx); }
  return arch_x86_64_enc_enc_pop_rbx(elf_ctx);
  }
}

// backend_enc_add_rax_rbx_arch: see function docblock below.
/** Exported function `backend_enc_add_rax_rbx_arch`.
 * Implements `backend_enc_add_rax_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_add_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_add_rax_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_rax_rbx(elf_ctx); }
  return arch_x86_64_enc_enc_add_rax_rbx(elf_ctx);
  }
}

// backend_enc_sub_rax_rbx_arch: see function docblock below.
/** Exported function `backend_enc_sub_rax_rbx_arch`.
 * Implements `backend_enc_sub_rax_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sub_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_sub_rax_rbx(elf_ctx); }
  if (ta == 2) { return -1; }
  return arch_x86_64_enc_enc_sub_rax_rbx(elf_ctx);
  }
}

// backend_enc_sub_rbx_rax_then_mov_arch: see function docblock below.
/** Exported function `backend_enc_sub_rbx_rax_then_mov_arch`.
 * Implements `backend_enc_sub_rbx_rax_then_mov_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sub_rbx_rax_then_mov_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_sub_rbx_rax_then_mov(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_sub_rbx_rax_then_mov(elf_ctx); }
  return arch_x86_64_enc_enc_sub_rbx_rax_then_mov(elf_ctx);
  }
}

// backend_enc_imul_rbx_rax_arch: see function docblock below.
/** Exported function `backend_enc_imul_rbx_rax_arch`.
 * Implements `backend_enc_imul_rbx_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_imul_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_imul_rbx_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_imul_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_imul_rbx_rax(elf_ctx);
  }
}

// backend_enc_mov_rax_to_rbx_arch: see function docblock below.
/** Exported function `backend_enc_mov_rax_to_rbx_arch`.
 * Implements `backend_enc_mov_rax_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_rax_to_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_rax_to_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_rax_to_rbx(elf_ctx); }
  return arch_x86_64_enc_enc_mov_rax_to_rbx(elf_ctx);
  }
}

// backend_enc_not_eax_arch: see function docblock below.
/** Exported function `backend_enc_not_eax_arch`.
 * Implements `backend_enc_not_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_not_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_not_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_not_eax(elf_ctx); }
  return arch_x86_64_enc_enc_not_eax(elf_ctx);
  }
}

// backend_enc_and_rbx_rax_arch: see function docblock below.
/** Exported function `backend_enc_and_rbx_rax_arch`.
 * Implements `backend_enc_and_rbx_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_and_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_and_rbx_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_and_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_and_rbx_rax(elf_ctx);
  }
}

// backend_enc_or_rbx_rax_arch: see function docblock below.
/** Exported function `backend_enc_or_rbx_rax_arch`.
 * Implements `backend_enc_or_rbx_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_or_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_or_rbx_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_or_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_or_rbx_rax(elf_ctx);
  }
}

// backend_enc_xor_rbx_rax_arch: see function docblock below.
/** Exported function `backend_enc_xor_rbx_rax_arch`.
 * Implements `backend_enc_xor_rbx_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_xor_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_xor_rbx_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_xor_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_xor_rbx_rax(elf_ctx);
  }
}

// backend_enc_mov_rbx_to_ecx_arch: see function docblock below.
/** Exported function `backend_enc_mov_rbx_to_ecx_arch`.
 * Implements `backend_enc_mov_rbx_to_ecx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_rbx_to_ecx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_rbx_to_ecx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_rbx_to_ecx(elf_ctx); }
  return arch_x86_64_enc_enc_mov_rbx_to_ecx(elf_ctx);
  }
}

// backend_enc_shl_cl_eax_arch: see function docblock below.
/** Exported function `backend_enc_shl_cl_eax_arch`.
 * Implements `backend_enc_shl_cl_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_shl_cl_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_shl_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_shl_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_shl_cl_eax(elf_ctx);
  }
}

// backend_enc_shr_cl_eax_arch: see function docblock below.
/** Exported function `backend_enc_shr_cl_eax_arch`.
 * Implements `backend_enc_shr_cl_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_shr_cl_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_shr_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_shr_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_shr_cl_eax(elf_ctx);
  }
}

// backend_enc_sar_cl_eax_arch: see function docblock below.
/** Exported function `backend_enc_sar_cl_eax_arch`.
 * Implements `backend_enc_sar_cl_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sar_cl_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_sar_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_sar_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_sar_cl_eax(elf_ctx);
  }
}

// backend_enc_shl_cl_rax_arch: see function docblock below.
/** Exported function `backend_enc_shl_cl_rax_arch`.
 * Implements `backend_enc_shl_cl_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_shl_cl_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_shl_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_shl_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_shl_cl_rax(elf_ctx);
  }
}

// backend_enc_shr_cl_rax_arch: see function docblock below.
/** Exported function `backend_enc_shr_cl_rax_arch`.
 * Implements `backend_enc_shr_cl_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_shr_cl_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_shr_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_shr_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_shr_cl_rax(elf_ctx);
  }
}

// backend_enc_sar_cl_rax_arch: see function docblock below.
/** Exported function `backend_enc_sar_cl_rax_arch`.
 * Implements `backend_enc_sar_cl_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sar_cl_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_sar_cl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_sar_cl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_sar_cl_rax(elf_ctx);
  }
}

// backend_enc_cltd_arch: see function docblock below.
/** Exported function `backend_enc_cltd_arch`.
 * Implements `backend_enc_cltd_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cltd_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_cltd(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_cltd(elf_ctx); }
  return arch_x86_64_enc_enc_cltd(elf_ctx);
  }
}

// backend_enc_mov_edx_to_eax_arch: see function docblock below.
/** Exported function `backend_enc_mov_edx_to_eax_arch`.
 * Implements `backend_enc_mov_edx_to_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_edx_to_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_edx_to_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_edx_to_eax(elf_ctx); }
  return arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx);
  }
}

// backend_enc_neg_eax_arch: see function docblock below.
/** Exported function `backend_enc_neg_eax_arch`.
 * Implements `backend_enc_neg_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_neg_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_neg_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_neg_eax(elf_ctx); }
  return arch_x86_64_enc_enc_neg_eax(elf_ctx);
  }
}

// backend_enc_test_eax_eax_arch: see function docblock below.
/** Exported function `backend_enc_test_eax_eax_arch`.
 * Implements `backend_enc_test_eax_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_test_eax_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_test_eax_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_test_eax_eax(elf_ctx); }
  return arch_x86_64_enc_enc_test_eax_eax(elf_ctx);
  }
}

// backend_enc_test_rbx_rbx_arch: see function docblock below.
/** Exported function `backend_enc_test_rbx_rbx_arch`.
 * Implements `backend_enc_test_rbx_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_test_rbx_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_test_rbx_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_test_rbx_rbx(elf_ctx); }
  return arch_x86_64_enc_enc_test_rbx_rbx(elf_ctx);
  }
}

// backend_enc_setz_movzbl_eax_arch: see function docblock below.
/** Exported function `backend_enc_setz_movzbl_eax_arch`.
 * Implements `backend_enc_setz_movzbl_eax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_setz_movzbl_eax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_setz_movzbl_eax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_setz_movzbl_eax(elf_ctx); }
  return arch_x86_64_enc_enc_setz_movzbl_eax(elf_ctx);
  }
}

// backend_enc_cmp_rbx_rax_arch: see function docblock below.
/** Exported function `backend_enc_cmp_rbx_rax_arch`.
 * Comparison/utility `backend_enc_cmp_rbx_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cmp_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_cmp_rbx_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_cmp_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_cmp_rbx_rax(elf_ctx);
  }
}

// backend_enc_cmp_rax_rbx_arch: see function docblock below.
/** Exported function `backend_enc_cmp_rax_rbx_arch`.
 * Comparison/utility `backend_enc_cmp_rax_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cmp_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_cmp_rax_rbx(elf_ctx); }
  if (ta == 2) { return -1; }
  return arch_x86_64_enc_enc_cmp_rax_rbx(elf_ctx);
  }
}

// backend_enc_cmp_setcc_movzbl_arch: see function docblock below.
/** Exported function `backend_enc_cmp_setcc_movzbl_arch`.
 * Comparison/utility `backend_enc_cmp_setcc_movzbl_arch`.
 * @param elf_ctx *u8
 * @param cc i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cmp_setcc_movzbl_arch(elf_ctx: *u8, cc: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc); }
  if (ta == 2) { return arch_riscv64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc); }
  return arch_x86_64_enc_enc_cmp_setcc_movzbl(elf_ctx, cc);
  }
}

/** Exported function `backend_enc_cmp_w0_imm12_arch`.
 * Comparison/utility `backend_enc_cmp_w0_imm12_arch`.
 * @param elf_ctx *u8
 * @param imm12 i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cmp_w0_imm12_arch(elf_ctx: *u8, imm12: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_cmp_w0_imm12(elf_ctx, imm12); }
  if (ta == 2) { return arch_riscv64_enc_enc_cmp_rbx_rax(elf_ctx); }
  return arch_x86_64_enc_enc_cmp_eax_imm32(elf_ctx, imm12);
  }
}

/** Exported function `backend_enc_cset_w0_from_cc_arch`.
 * Implements `backend_enc_cset_w0_from_cc_arch`.
 * @param elf_ctx *u8
 * @param cc i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cset_w0_from_cc_arch(elf_ctx: *u8, cc: i32, ta: i32): i32 {
  if (ta == 1) { return arch_arm64_enc_enc_cset_w0_from_cc(elf_ctx, cc); }
  return backend_enc_cmp_setcc_movzbl_arch(elf_ctx, cc, ta);
}

// backend_enc_store_rax_to_rbp_arch: see function docblock below.
/** Exported function `backend_enc_store_rax_to_rbp_arch`.
 * Implements `backend_enc_store_rax_to_rbp_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_store_rax_to_rbp_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_store_rax_to_rbp(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_store_rax_to_rbp(elf_ctx, offset); }
  return arch_x86_64_enc_enc_store_rax_to_rbp(elf_ctx, offset);
  }
}

// backend_enc_load_rbp_to_rax_arch: see function docblock below.
/** Exported function `backend_enc_load_rbp_to_rax_arch`.
 * Implements `backend_enc_load_rbp_to_rax_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_rbp_to_rax(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_rbp_to_rax(elf_ctx, offset); }
  return arch_x86_64_enc_enc_load_rbp_to_rax(elf_ctx, offset);
  }
}

// backend_enc_lea_rbp_to_rax_arch: see function docblock below.
/** Exported function `backend_enc_lea_rbp_to_rax_arch`.
 * Implements `backend_enc_lea_rbp_to_rax_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_lea_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_lea_rbp_to_rax(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_lea_rbp_to_rax(elf_ctx, offset); }
  return arch_x86_64_enc_enc_lea_rbp_to_rax(elf_ctx, offset);
  }
}

// backend_enc_lea_rbp_to_rbx_arch: see function docblock below.
/** Exported function `backend_enc_lea_rbp_to_rbx_arch`.
 * Implements `backend_enc_lea_rbp_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_lea_rbp_to_rbx_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset); }
  return arch_x86_64_enc_enc_lea_rbp_to_rbx(elf_ctx, offset);
  }
}

// backend_enc_rax_plus_rbx_scale4_arch: see function docblock below.
/** Exported function `backend_enc_rax_plus_rbx_scale4_arch`.
 * Implements `backend_enc_rax_plus_rbx_scale4_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rax_plus_rbx_scale4_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_rax_plus_rbx_scale4(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_rax_plus_rbx_scale4(elf_ctx); }
  return arch_x86_64_enc_enc_rax_plus_rbx_scale4(elf_ctx);
  }
}

// backend_enc_rax_plus_rbx_scale1_arch: see function docblock below.
/** Exported function `backend_enc_rax_plus_rbx_scale1_arch`.
 * Implements `backend_enc_rax_plus_rbx_scale1_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rax_plus_rbx_scale1_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_rax_plus_rbx_scale1(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_rax_plus_rbx_scale1(elf_ctx); }
  return arch_x86_64_enc_enc_rax_plus_rbx_scale1(elf_ctx);
  }
}

// backend_enc_rax_plus_rbx_scale8_arch: see function docblock below.
/** Exported function `backend_enc_rax_plus_rbx_scale8_arch`.
 * Implements `backend_enc_rax_plus_rbx_scale8_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rax_plus_rbx_scale8_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_rax_plus_rbx_scale8(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_rax_plus_rbx_scale8(elf_ctx); }
  return arch_x86_64_enc_enc_rax_plus_rbx_scale8(elf_ctx);
  }
}

// backend_enc_store_rax_to_rbx_indirect_arch: see function docblock below.
/** Exported function `backend_enc_store_rax_to_rbx_indirect_arch`.
 * Implements `backend_enc_store_rax_to_rbx_indirect_arch`.
 * @param elf_ctx *u8
 * @param elem_sz i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_store_rax_to_rbx_indirect_arch(elf_ctx: *u8, elem_sz: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz); }
  if (ta == 2) { return arch_riscv64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz); }
  return arch_x86_64_enc_enc_store_rax_to_rbx_indirect(elf_ctx, elem_sz);
  }
}

// backend_enc_load_zext8_from_rax_arch: see function docblock below.
/** Exported function `backend_enc_load_zext8_from_rax_arch`.
 * Implements `backend_enc_load_zext8_from_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_zext8_from_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_zext8_from_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_zext8_from_rax(elf_ctx); }
  return arch_x86_64_enc_enc_load_zext8_from_rax(elf_ctx);
  }
}

// backend_enc_add_imm_to_rax_arch: see function docblock below.
/** Exported function `backend_enc_add_imm_to_rax_arch`.
 * Implements `backend_enc_add_imm_to_rax_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_add_imm_to_rax_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_add_imm_to_rax(elf_ctx, imm); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_imm_to_rax(elf_ctx, imm); }
  return arch_x86_64_enc_enc_add_imm_to_rax(elf_ctx, imm);
  }
}

// backend_enc_add_imm_to_rbx_arch: see function docblock below.
/** Exported function `backend_enc_add_imm_to_rbx_arch`.
 * Implements `backend_enc_add_imm_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_add_imm_to_rbx_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_add_imm_to_rbx(elf_ctx, imm); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_imm_to_rbx(elf_ctx, imm); }
  return arch_x86_64_enc_enc_add_imm_to_rbx(elf_ctx, imm);
  }
}

// backend_enc_load_rbp_index_scratch_arch: see function docblock below.
/** Exported function `backend_enc_load_rbp_index_scratch_arch`.
 * Implements `backend_enc_load_rbp_index_scratch_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_index_scratch_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_rbp_to_x2(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_rbp_to_a2(elf_ctx, offset); }
  return arch_x86_64_enc_enc_load_rbp_to_ecx(elf_ctx, offset);
  }
}

// backend_enc_load_64_from_rax_arch: see function docblock below.
/** Exported function `backend_enc_load_64_from_rax_arch`.
 * Implements `backend_enc_load_64_from_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_64_from_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_64_from_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_64_from_rax(elf_ctx); }
  return arch_x86_64_enc_enc_load_64_from_rax(elf_ctx);
  }
}

// backend_enc_store_rax_to_rbx_offset_arch: see function docblock below.
/** Exported function `backend_enc_store_rax_to_rbx_offset_arch`.
 * Implements `backend_enc_store_rax_to_rbx_offset_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param store_size i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_store_rax_to_rbx_offset_arch(elf_ctx: *u8, offset: i32, store_size: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size); }
  if (ta == 2) { return arch_riscv64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size); }
  return arch_x86_64_enc_enc_store_rax_to_rbx_offset(elf_ctx, offset, store_size);
  }
}

// backend_enc_mov_rbx_to_rax_arch: see function docblock below.
/** Exported function `backend_enc_mov_rbx_to_rax_arch`.
 * Implements `backend_enc_mov_rbx_to_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_rbx_to_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_rbx_to_rax(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_rbx_to_rax(elf_ctx); }
  return arch_x86_64_enc_enc_mov_rbx_to_rax(elf_ctx);
  }
}

// backend_enc_jz_arch: see function docblock below.
/** Exported function `backend_enc_jz_arch`.
 * Implements `backend_enc_jz_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jz_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jz(elf_ctx, label, label_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_jz(elf_ctx, label, label_len); }
  return arch_x86_64_enc_enc_jz(elf_ctx, label, label_len);
  }
}

// backend_enc_jeq_arch: see function docblock below.
/** Exported function `backend_enc_jeq_arch`.
 * Implements `backend_enc_jeq_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jeq_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jeq(elf_ctx, label, label_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_jeq(elf_ctx, label, label_len); }
  return arch_x86_64_enc_enc_jeq(elf_ctx, label, label_len);
  }
}

// backend_enc_jge_arch: see function docblock below.
/** Exported function `backend_enc_jge_arch`.
 * Implements `backend_enc_jge_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jge_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jge(elf_ctx, label, label_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_jge(elf_ctx, label, label_len); }
  return arch_x86_64_enc_enc_jge(elf_ctx, label, label_len);
  }
}

// backend_enc_jnz_arch: see function docblock below.
/** Exported function `backend_enc_jnz_arch`.
 * Implements `backend_enc_jnz_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jnz_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jnz(elf_ctx, label, label_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_jnz(elf_ctx, label, label_len); }
  return arch_x86_64_enc_enc_jnz(elf_ctx, label, label_len);
  }
}

// backend_enc_jmp_arch: see function docblock below.
/** Exported function `backend_enc_jmp_arch`.
 * Implements `backend_enc_jmp_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jmp_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jmp(elf_ctx, label, label_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_jmp(elf_ctx, label, label_len); }
  return arch_x86_64_enc_enc_jmp(elf_ctx, label, label_len);
  }
}

// backend_enc_mov_rax_to_arg_reg_arch: see function docblock below.
/** Exported function `backend_enc_mov_rax_to_arg_reg_arch`.
 * Implements `backend_enc_mov_rax_to_arg_reg_arch`.
 * @param elf_ctx *u8
 * @param k i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_rax_to_arg_reg_arch(elf_ctx: *u8, k: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k); }
  if (ta == 2) { return arch_riscv64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k); }
  return arch_x86_64_enc_enc_mov_rax_to_arg_reg(elf_ctx, k);
  }
}

// backend_enc_call_arch: see function docblock below.
/** Exported function `backend_enc_call_arch`.
 * Implements `backend_enc_call_arch`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_call_arch(elf_ctx: *u8, name: *u8, name_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return backend_enc_arm64_call_c(elf_ctx, name, name_len); }
  if (ta == 2) { return arch_riscv64_enc_enc_call(elf_ctx, name, name_len); }
  return arch_x86_64_enc_enc_call(elf_ctx, name, name_len);
  }
}

/* See implementation. */
export extern "C" function arch_arm64_enc_enc_idiv_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_jne(elf_ctx: *u8, label: *u8, label_len: i32): i32;
export extern "C" function arch_arm64_enc_enc_store_x_reg_to_rbp(elf_ctx: *u8, reg: i32, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_add_a2_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_add_rbx_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_add_sp_imm12(elf_ctx: *u8, nbytes: i32): i32;
export extern "C" function arch_riscv64_enc_enc_idiv_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mul_a2_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_mul_rbx_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rsub_a2_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rsub_rbx_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_sub_a2_a3(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_sub_rbx_a3(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_add_ebx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_add_ecx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_add_rsp_imm(elf_ctx: *u8, nbytes: i32): i32;
export extern "C" function arch_x86_64_enc_enc_div_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_idiv_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_imul_ebx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_imul_ecx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_rsub_ebx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_rsub_ecx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sub_ebx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sub_ecx_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_xor_edx_edx(elf_ctx: *u8): i32;

// backend_enc_store_x_reg_to_rbp_arch: see function docblock below.
/** Exported function `backend_enc_store_x_reg_to_rbp_arch`.
 * Implements `backend_enc_store_x_reg_to_rbp_arch`.
 * @param elf_ctx *u8
 * @param reg i32
 * @param offset i32
 * @param ta i32
 * @return i32
 */
/**
 * Store GP `reg` to [rbp - offset] (product frame slot).
 * @param elf_ctx *u8 — ElfCodegenCtx
 * @param reg i32 — hardware register (arm64 xN / x86 0=rax..15=r15)
 * @param offset i32 — positive rbp-down slot
 * @param ta i32 — 0=x86_64, 1=arm64
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED — LINUX|x86_64 SysV movq %r64,-off(%rbp); MACOS|ARM64 stur.
 */
#[no_mangle]
export function backend_enc_store_x_reg_to_rbp_arch(elf_ctx: *u8, reg: i32, offset: i32, ta: i32): i32 {
  unsafe {
    if (ta == 1) { return arch_arm64_enc_enc_store_x_reg_to_rbp(elf_ctx, reg, offset); }
    if (ta == 0) { return arch_x86_64_enc_enc_store_r64_to_rbp(elf_ctx, reg, offset); }
    return 0 - 1;
  }
}

// backend_enc_jne_arch: see function docblock below.
/** Exported function `backend_enc_jne_arch`.
 * Implements `backend_enc_jne_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jne_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_jne(elf_ctx, label, label_len); }
  return backend_enc_jnz_arch(elf_ctx, label, label_len, ta);
  }
}

// backend_enc_call_stack_cleanup_arch: see function docblock below.
/** Exported function `backend_enc_call_stack_cleanup_arch`.
 * Implements `backend_enc_call_stack_cleanup_arch`.
 * @param elf_ctx *u8
 * @param nbytes i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_call_stack_cleanup_arch(elf_ctx: *u8, nbytes: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (nbytes <= 0) { return 0; }
  if (ta == 1) { return backend_enc_arm64_add_sp_imm12_c(elf_ctx, nbytes); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_sp_imm12(elf_ctx, nbytes); }
  return arch_x86_64_enc_enc_add_rsp_imm(elf_ctx, nbytes);
  }
}

// backend_enc_call_stack_reserve_arch: see function docblock below.
/** Exported function `backend_enc_call_stack_reserve_arch`.
 * Implements `backend_enc_call_stack_reserve_arch`.
 * @param elf_ctx *u8
 * @param nbytes i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_call_stack_reserve_arch(elf_ctx: *u8, nbytes: i32, ta: i32): i32 {
  if (nbytes <= 0) { return 0; }
  if (ta == 1) { return backend_enc_arm64_sub_sp_imm12_c(elf_ctx, nbytes); }
  return 0;
}

// backend_enc_store_x0_sp_offset_arch: see function docblock below.
/** Exported function `backend_enc_store_x0_sp_offset_arch`.
 * Implements `backend_enc_store_x0_sp_offset_arch`.
 * @param elf_ctx *u8
 * @param off_bytes i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_store_x0_sp_offset_arch(elf_ctx: *u8, off_bytes: i32, ta: i32): i32 {
  if (ta == 1) { return backend_enc_arm64_str_x0_sp_offset_c(elf_ctx, off_bytes); }
  return 0 - 1;
}

// backend_enc_index_scratch_add_secondary_arch: see function docblock below.
/** Exported function `backend_enc_index_scratch_add_secondary_arch`.
 * Implements `backend_enc_index_scratch_add_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_index_scratch_add_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (184746050 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_a2_a3(elf_ctx); }
  return arch_x86_64_enc_enc_add_ecx_edx(elf_ctx);
  }
}

// backend_enc_index_scratch_sub_secondary_arch: see function docblock below.
/** Exported function `backend_enc_index_scratch_sub_secondary_arch`.
 * Implements `backend_enc_index_scratch_sub_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_index_scratch_sub_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (1258487874 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_sub_a2_a3(elf_ctx); }
  return arch_x86_64_enc_enc_sub_ecx_edx(elf_ctx);
  }
}

// backend_enc_index_scratch_rsub_secondary_arch: see function docblock below.
/** Exported function `backend_enc_index_scratch_rsub_secondary_arch`.
 * Implements `backend_enc_index_scratch_rsub_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_index_scratch_rsub_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (1258422370 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_rsub_a2_a3(elf_ctx); }
  return arch_x86_64_enc_enc_rsub_ecx_edx(elf_ctx);
  }
}

// backend_enc_rbx_index_rsub_secondary_arch: see function docblock below.
/** Exported function `backend_enc_rbx_index_rsub_secondary_arch`.
 * Implements `backend_enc_rbx_index_rsub_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rbx_index_rsub_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (1258356833 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_rsub_rbx_a3(elf_ctx); }
  return arch_x86_64_enc_enc_rsub_ebx_edx(elf_ctx);
  }
}

// backend_enc_rbx_index_add_secondary_arch: see function docblock below.
/** Exported function `backend_enc_rbx_index_add_secondary_arch`.
 * Implements `backend_enc_rbx_index_add_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rbx_index_add_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (184746017 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_add_rbx_a3(elf_ctx); }
  return arch_x86_64_enc_enc_add_ebx_edx(elf_ctx);
  }
}

// backend_enc_rbx_index_sub_secondary_arch: see function docblock below.
/** Exported function `backend_enc_rbx_index_sub_secondary_arch`.
 * Implements `backend_enc_rbx_index_sub_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rbx_index_sub_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (1258487841 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_sub_rbx_a3(elf_ctx); }
  return arch_x86_64_enc_enc_sub_ebx_edx(elf_ctx);
  }
}

// backend_enc_index_scratch_mul_secondary_arch: see function docblock below.
/** Exported function `backend_enc_index_scratch_mul_secondary_arch`.
 * Implements `backend_enc_index_scratch_mul_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_index_scratch_mul_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (453213250 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_mul_a2_a3(elf_ctx); }
  return arch_x86_64_enc_enc_imul_ecx_edx(elf_ctx);
  }
}

// backend_enc_rbx_index_mul_secondary_arch: see function docblock below.
/** Exported function `backend_enc_rbx_index_mul_secondary_arch`.
 * Implements `backend_enc_rbx_index_mul_secondary_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rbx_index_mul_secondary_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_u32_le(elf_ctx, (453213217 as i32)); }
  if (ta == 2) { return arch_riscv64_enc_enc_mul_rbx_a3(elf_ctx); }
  return arch_x86_64_enc_enc_imul_ebx_edx(elf_ctx);
  }
}

// backend_enc_idiv_rbx_arch: see function docblock below.
/** Exported function `backend_enc_idiv_rbx_arch`.
 * Implements `backend_enc_idiv_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_idiv_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_idiv_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_idiv_rbx(elf_ctx); }
  if (arch_x86_64_enc_enc_cltd(elf_ctx) != 0) { return 0 - 1; }
  return arch_x86_64_enc_enc_idiv_rbx(elf_ctx);
  }
}

// backend_enc_div_rbx_arch: see function docblock below.
/** Exported function `backend_enc_div_rbx_arch`.
 * Implements `backend_enc_div_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_div_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_idiv_rbx(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_idiv_rbx(elf_ctx); }
  if (arch_x86_64_enc_enc_xor_edx_edx(elf_ctx) != 0) { return 0 - 1; }
  return arch_x86_64_enc_enc_div_rbx(elf_ctx);
  }
}

// backend_enc_rem_mod_arch: see function docblock below.
/** Exported function `backend_enc_rem_mod_arch`.
 * Implements `backend_enc_rem_mod_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rem_mod_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta == 1) { return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta); }
  if (backend_enc_cltd_arch(elf_ctx, ta) != 0) { return 0 - 1; }
  if (backend_enc_idiv_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
  return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta);
}

/**
 * Unsigned rem: routes through backend_enc_div_rbx_arch (xor edx + div) then mov remainder.
 * PLATFORM: SHARED — full-dispatch twin of thin wave322 fix (thin is product authority when L2).
 * @param elf_ctx *u8 — ElfCodegenCtx*
 * @param ta i32 — target arch
 * @return i32 — 0 success, -1 failure
 */
#[no_mangle]
export function backend_enc_rem_mod_unsigned_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta == 1) { return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta); }
  /* backend_enc_div_rbx_arch already emits xor_edx + divl %ebx (wave322 / G.7). */
  if (backend_enc_div_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
  return backend_enc_mov_edx_to_eax_arch(elf_ctx, ta);
}

/* See implementation. */

export extern "C" function arch_x86_64_enc_enc_store_rdx_to_rbp(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_rdx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rdx_to_arg_reg(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_x86_64_enc_enc_mov_arg_reg_to_rax(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_arm64_enc_enc_mov_arg_reg_to_rax(elf_ctx: *u8, k: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_pos_to_rax(elf_ctx: *u8, off_pos: i32): i32;
export extern "C" function arch_arm64_enc_enc_load_32_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_load_32_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_load_32_from_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_eax32(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_ebx32(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_load_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_load_rbp_to_rbx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_arm64_enc_enc_rbx_plus_x2_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_rbx_plus_x2_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_rbx_plus_x2_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rbx_plus_a2_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rbx_plus_a2_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_rbx_plus_a2_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(elf_ctx: *u8): i32;
export extern "C" function arch_riscv64_enc_enc_add_imm_to_a2(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_add_imm_to_ecx(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_riscv64_enc_enc_sub_imm_from_a2(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_sub_imm_from_ecx(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_add_imm_to_ebx_index(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_riscv64_enc_enc_sub_imm_from_rbx_index(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_x86_64_enc_enc_sub_imm_from_ebx_index(elf_ctx: *u8, imm: i32): i32;
export extern "C" function arch_riscv64_enc_enc_load_rbp_to_a3(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_x86_64_enc_enc_load_rbp_to_edx(elf_ctx: *u8, offset: i32): i32;
export extern "C" function arch_riscv64_enc_enc_mul_imm_to_a2(elf_ctx: *u8, lit: i32): i32;
export extern "C" function arch_x86_64_enc_enc_imul_imm_to_ecx(elf_ctx: *u8, lit: i32): i32;
export extern "C" function arch_riscv64_enc_enc_mul_imm_to_rbx(elf_ctx: *u8, lit: i32): i32;
export extern "C" function arch_x86_64_enc_enc_imul_imm_to_ebx(elf_ctx: *u8, lit: i32): i32;

/**
 * Store dual-GP second half (length / high 8B) to frame slot.
 * @param elf_ctx *u8 — ElfCodegenCtx
 * @param offset i32 — product frame offset of the length half
 * @param ta i32 — 0=x86_64 (rdx), 1=arm64 (x1 / AAPCS64 second GP)
 * @return i32 — 0 success, -1 unsupported arch / encode fail
 * PLATFORM: SHARED dual-GP contract · LINUX|x86_64 SysV rdx · MACOS|ARM64 x1
 * wave408: arm64 was hard -1 → TYPE_SLICE let-init/call-arg dropped length (panic).
 */
#[no_mangle]
export function backend_enc_store_rdx_to_rbp_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  unsafe {
  if (ta == 1) {
    /* x1 = SysV/AAPCS second integer return/arg; G.7 reuse store_x_reg. */
    return arch_arm64_enc_enc_store_x_reg_to_rbp(elf_ctx, 1, offset);
  }
  if (ta != 0) { return 0 - 1; }
  return arch_x86_64_enc_enc_store_rdx_to_rbp(elf_ctx, offset);
  }
}

/**
 * Load [rbx] → rax (low 8 of a 9–16B INTEGER-class aggregate).
 * Used by pipeline_asm_deref_struct16_rax_ptr_elf_c after mov rax→rbx
 * parked the address. FIELD-as-call-arg 16B (heap.Allocator / local POD)
 * goes through this face.
 * @param elf_ctx *u8 — ElfCodegenCtx*; encoder rejects null
 * @param ta i32 — 0=x86_64 SysV; 1=arm64 AAPCS64; else -1
 * @return i32 — 0 ok; -1 encoder / unsupported arch
 * PLATFORM: SHARED — LINUX|x86_64 mov rax,[rbx]; MACOS|ARM64 ldr x0,[x1]
 *   (rbx=x1, rax=x0). Same word as pipeline_asm_modlet_load_to_rax_elf_c.
 * G.7: complete the existing ta shell; do not add a second deref path.
 */
#[no_mangle]
export function backend_enc_load_qword_from_rbx_to_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  unsafe {
    if (ta == 1) {
      // ldr x0, [x1] = 0xF9400020
      return arch_arm64_enc_enc_u32_le(elf_ctx, (4181721120 as u32) as i32);
    }
    if (ta != 0) { return 0 - 1; }
    return arch_x86_64_enc_enc_load_qword_from_rbx_to_rax(elf_ctx);
  }
}

/**
 * Load [rbx+8] → rdx (high 8 of a 9–16B INTEGER-class aggregate).
 * After mov rax→rbx the address lives in rbx. On ARM64 rdx is x1
 * (wave408 store_rdx), so this is ldr x1,[x1,#8]: the base is sampled
 * before Rt is written — valid, and yields AAPCS64 x0+x1.
 * @param elf_ctx *u8 — ElfCodegenCtx*; encoder rejects null
 * @param ta i32 — 0=x86_64 SysV rdx; 1=arm64 AAPCS64 x1; else -1
 * @return i32 — 0 ok; -1 encoder / unsupported arch
 * PLATFORM: SHARED — LINUX|x86_64 mov rdx,[rbx+8]; MACOS|ARM64 ldr x1,[x1,#8]
 * G.7: same face as the x86 encoder; do not invent a second dual-GP load.
 */
#[no_mangle]
export function backend_enc_load_qword_rbx8_to_rdx_arch(elf_ctx: *u8, ta: i32): i32 {
  unsafe {
    if (ta == 1) {
      // ldr x1, [x1, #8] = 0xF9400421
      return arch_arm64_enc_enc_u32_le(elf_ctx, (4181722145 as u32) as i32);
    }
    if (ta != 0) { return 0 - 1; }
    return arch_x86_64_enc_enc_load_qword_rbx8_to_rdx(elf_ctx);
  }
}

/** Exported function `backend_enc_load_rbp_to_rdx_arch`.
 * Implements `backend_enc_load_rbp_to_rdx_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_to_rdx_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta != 0) { return 0 - 1; }
  return arch_x86_64_enc_enc_load_rbp_to_rdx(elf_ctx, offset);
  }
}

/** Exported function `backend_enc_mov_rdx_to_arg_reg_arch`.
 * Implements `backend_enc_mov_rdx_to_arg_reg_arch`.
 * @param elf_ctx *u8
 * @param k i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_rdx_to_arg_reg_arch(elf_ctx: *u8, k: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta != 0) { return 0 - 1; }
  return arch_x86_64_enc_enc_mov_rdx_to_arg_reg(elf_ctx, k);
  }
}

/** Exported function `backend_enc_mov_arg_reg_to_rax_arch`.
 * Implements `backend_enc_mov_arg_reg_to_rax_arch`.
 * @param elf_ctx *u8
 * @param k i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mov_arg_reg_to_rax_arch(elf_ctx: *u8, k: i32, ta: i32): i32 {
  // Stage10 10.2.2 slice1: ta==1 → arch_arm64_enc_enc_mov_arg_reg_to_rax (AAPCS lateout).
  unsafe {
  if (ta == 0) { return arch_x86_64_enc_enc_mov_arg_reg_to_rax(elf_ctx, k); }
  if (ta == 1) { return arch_arm64_enc_enc_mov_arg_reg_to_rax(elf_ctx, k); }
  return 0 - 1;
  }
}

/** Exported function `backend_enc_load_rbp_pos_to_rax_arch`.
 * Implements `backend_enc_load_rbp_pos_to_rax_arch`.
 * @param elf_ctx *u8
 * @param off_pos i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_pos_to_rax_arch(elf_ctx: *u8, off_pos: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 0) { return arch_x86_64_enc_enc_load_rbp_pos_to_rax(elf_ctx, off_pos); }
  return 0 - 1;
  }
}

/** Exported function `backend_enc_jle_arch`.
 * Implements `backend_enc_jle_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jle_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  return backend_enc_x86_jcc_rel32_c(elf_ctx, 142, label, label_len);
}

/** Exported function `backend_enc_jl_arch`.
 * Implements `backend_enc_jl_arch`.
 * @param elf_ctx *u8
 * @param label *u8
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_jl_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  return backend_enc_x86_jcc_rel32_c(elf_ctx, 140, label, label_len);
}

// G-02f-207：load 32 from [rax]
/** Exported function `backend_enc_load_32_from_rax_arch`.
 * Implements `backend_enc_load_32_from_rax_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_32_from_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) {
    if (arch_arm64_enc_enc_load_32_from_rax(elf_ctx) != 0) { return 0 - 1; }
    return 0;
  }
  if (ta == 2) {
    if (arch_riscv64_enc_enc_load_32_from_rax(elf_ctx) != 0) { return 0 - 1; }
    return 0;
  }
  if (arch_x86_64_enc_enc_load_32_from_rax(elf_ctx) != 0) { return 0 - 1; }
  return 0;
  }
}

/**
 * Signed i32 load from [rax/x0] into the full GP (rax/x0).
 * @param elf_ctx *u8 — emit context
 * @param ta i32 — 0=x86_64, 1=arm64, 2=riscv64
 * @return i32 — 0 ok, -1 encoder failure
 * PLATFORM: SHARED — x86 CDQE via load_32; MACOS|ARM64 LDRSW x0,[x0].
 * G.7 complete: emit_index esz==4 vs 64-bit `-5` needs sign-extend.
 * Do not change load_32_from_rax (f32 bits stay zero-ext). Product L2
 * uses thin; this full twin stays aligned.
 */
#[no_mangle]
export function backend_enc_load_i32_indirect_to_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta == 1) {
    unsafe { return arch_arm64_enc_enc_u32_le(elf_ctx, 3112173568 as i32); }
  }
  return backend_enc_load_32_from_rax_arch(elf_ctx, ta);
}

// backend_enc_load_rbp_to_rbx_arch: see function docblock below.
/** Exported function `backend_enc_load_rbp_to_rbx_arch`.
 * Implements `backend_enc_load_rbp_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_to_rbx_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_rbp_to_rbx(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_rbp_to_rbx(elf_ctx, offset); }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let disp: i32 = 0 - offset;
    let u: u32 = disp as u32;
    let b: u8[7] = [];
    if (disp >= 0 - 128) {
      if (disp <= 0 - 1) {
        b[0] = 72;
        b[1] = 139;
        b[2] = 93;
        b[3] = (u & 255) as u8;
        return pipeline_elf_ctx_append_bytes(elf_ctx, &b[0], 4);
      }
    }
    b[0] = 72;
    b[1] = 139;
    b[2] = 157;
    b[3] = (u & 255) as u8;
    b[4] = ((u / 256) & 255) as u8;
    b[5] = ((u / 65536) & 255) as u8;
    b[6] = ((u / 16777216) & 255) as u8;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b[0], 7);
  }
  return 0 - 1;
  }
}

// G-02f-207：store eax → rbp
/** Exported function `backend_enc_store_eax_to_rbp_arch`.
 * Implements `backend_enc_store_eax_to_rbp_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_store_eax_to_rbp_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  if (ta == 1) { return arm64_enc_store_w0_to_rbp_c(elf_ctx, offset); }
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let disp: i32 = 0 - offset;
    let u: u32 = disp as u32;
    let b: u8[7] = [];
    if (disp >= 0 - 128) {
      if (disp <= 0 - 1) {
        b[0] = 137;
        b[1] = 69;
        b[2] = (u & 255) as u8;
        return pipeline_elf_ctx_append_bytes(elf_ctx, &b[0], 3);
      }
    }
    b[0] = 137;
    b[1] = 133;
    b[2] = (u & 255) as u8;
    b[3] = ((u / 256) & 255) as u8;
    b[4] = ((u / 65536) & 255) as u8;
    b[5] = ((u / 16777216) & 255) as u8;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b[0], 6);
  }
  return 0 - 1;
}

// G-02f-207：lane load
/** Exported function `backend_enc_load_rbp_lane_to_rax_arch`.
 * Implements `backend_enc_load_rbp_lane_to_rax_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param esz i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_lane_to_rax_arch(elf_ctx: *u8, offset: i32, esz: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 0) {
    if (esz == 4) { return arch_x86_64_enc_enc_load_rbp_to_eax32(elf_ctx, offset); }
  }
  if (ta == 1) {
    if (esz == 4) { return arm64_enc_load_w0_from_rbp_c(elf_ctx, offset); }
  }
  return backend_enc_load_rbp_to_rax_arch(elf_ctx, offset, ta);
  }
}

/** Exported function `backend_enc_load_rbp_lane_to_rbx_arch`.
 * Implements `backend_enc_load_rbp_lane_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param esz i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_lane_to_rbx_arch(elf_ctx: *u8, offset: i32, esz: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 0) {
    if (esz == 4) { return arch_x86_64_enc_enc_load_rbp_to_ebx32(elf_ctx, offset); }
  }
  if (ta == 1) {
    if (esz == 4) { return arm64_enc_load_w1_from_rbp_c(elf_ctx, offset); }
  }
  return backend_enc_load_rbp_to_rbx_arch(elf_ctx, offset, ta);
  }
}

// G-02f-207：arm64 ldr x0,[x29,#pos] — 0xf9400000 | (imm12<<10) | (29<<5) ≈ (4181722016 as u32) base
/** Exported function `backend_enc_load_x29_pos_to_rax_arch`.
 * Implements `backend_enc_load_x29_pos_to_rax_arch`.
 * @param elf_ctx *u8
 * @param off_pos i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_x29_pos_to_rax_arch(elf_ctx: *u8, off_pos: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) {
    let off: i32 = off_pos;
    if (off < 0) { off = 0; }
    let imm12: i32 = off / 8;
    if (imm12 > 4095) { imm12 = 4095; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((4181722016 as u32) | ((imm12 as u32) * 1024)) as i32);
  }
  return 0 - 1;
  }
}

// G-02f-207：rbx + index_scratch * esz
/** Exported function `backend_enc_rbx_plus_index_scratch_scaled_arch`.
 * Implements `backend_enc_rbx_plus_index_scratch_scaled_arch`.
 * @param elf_ctx *u8
 * @param esz i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_rbx_plus_index_scratch_scaled_arch(elf_ctx: *u8, esz: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (esz == 1) {
    if (ta == 1) { return arch_arm64_enc_enc_rbx_plus_x2_scale1(elf_ctx); }
    if (ta == 2) { return arch_riscv64_enc_enc_rbx_plus_a2_scale1(elf_ctx); }
    return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale1(elf_ctx);
  }
  if (esz == 4) {
    if (ta == 1) { return arch_arm64_enc_enc_rbx_plus_x2_scale4(elf_ctx); }
    if (ta == 2) { return arch_riscv64_enc_enc_rbx_plus_a2_scale4(elf_ctx); }
    return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale4(elf_ctx);
  }
  if (ta == 1) { return arch_arm64_enc_enc_rbx_plus_x2_scale8(elf_ctx); }
  if (ta == 2) { return arch_riscv64_enc_enc_rbx_plus_a2_scale8(elf_ctx); }
  return arch_x86_64_enc_enc_lea_rbx_plus_rcx_scale8(elf_ctx);
  }
}

// G-02f-207：add imm → index_scratch
/** Exported function `backend_enc_add_imm_to_index_scratch_arch`.
 * Implements `backend_enc_add_imm_to_index_scratch_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_add_imm_to_index_scratch_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) {
    if (imm == 0) { return 0; }
    let imm12: i32 = imm;
    if (imm12 > 4095) { imm12 = 4095; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((285213762 as u32) + ((imm12 - 1) * 1024)) as i32);
  }
  if (ta == 2) { return arch_riscv64_enc_enc_add_imm_to_a2(elf_ctx, imm); }
  return arch_x86_64_enc_enc_add_imm_to_ecx(elf_ctx, imm);
  }
}

/** Exported function `backend_enc_sub_imm_from_index_scratch_arch`.
 * Implements `backend_enc_sub_imm_from_index_scratch_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sub_imm_from_index_scratch_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (ta == 1) {
    if (imm == 0) { return 0; }
    let imm12: i32 = imm;
    if (imm12 > 4095) { imm12 = 4095; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((1358955586 as u32) + ((imm12 - 1) * 1024)) as i32);
  }
  if (ta == 2) { return arch_riscv64_enc_enc_sub_imm_from_a2(elf_ctx, imm); }
  return arch_x86_64_enc_enc_sub_imm_from_ecx(elf_ctx, imm);
  }
}

/** Exported function `backend_enc_add_imm_to_rbx_index_arch`.
 * Implements `backend_enc_add_imm_to_rbx_index_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_add_imm_to_rbx_index_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (imm == 0) { return 0; }
  if (ta == 1) {
    let imm12: i32 = imm;
    if (imm12 > 4095) { imm12 = 4095; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((285213729 as u32) + ((imm12 - 1) * 1024)) as i32);
  }
  if (ta == 2) { return arch_riscv64_enc_enc_add_imm_to_rbx(elf_ctx, imm); }
  return arch_x86_64_enc_enc_add_imm_to_ebx_index(elf_ctx, imm);
  }
}

/** Exported function `backend_enc_sub_imm_from_rbx_index_arch`.
 * Implements `backend_enc_sub_imm_from_rbx_index_arch`.
 * @param elf_ctx *u8
 * @param imm i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_sub_imm_from_rbx_index_arch(elf_ctx: *u8, imm: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (imm == 0) { return 0; }
  if (ta == 1) {
    let imm12: i32 = imm;
    if (imm12 > 4095) { imm12 = 4095; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((1358955553 as u32) + ((imm12 - 1) * 1024)) as i32);
  }
  if (ta == 2) { return arch_riscv64_enc_enc_sub_imm_from_rbx_index(elf_ctx, imm); }
  return arch_x86_64_enc_enc_sub_imm_from_ebx_index(elf_ctx, imm);
  }
}

/** Exported function `backend_enc_load_rbp_index_secondary_scratch_arch`.
 * Implements `backend_enc_load_rbp_index_secondary_scratch_arch`.
 * @param elf_ctx *u8
 * @param offset i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_load_rbp_index_secondary_scratch_arch(elf_ctx: *u8, offset: i32, ta: i32): i32 {
  /* wave617: delegate to arch_arm64_enc_enc_load_rbp_to_x3 (positive-offset LDR
   * X3, [X29, #imm12]) — SAME convention as primary loader load_rbp_to_x2.
   * Root: old inline negated offset (LDUR W3, [x29,-off]) while primary used
   *   positive LDR X2, [x29,+off] → secondary loaded garbage below the frame
   *   for arr[i+j] right operand (i+j computed wrong, e.g. got 10 not 99).
   * Invariant: secondary loader offset convention MUST match primary loader. */
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_load_rbp_to_x3(elf_ctx, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_load_rbp_to_a3(elf_ctx, offset); }
  return arch_x86_64_enc_enc_load_rbp_to_edx(elf_ctx, offset);
  }
}

/** Exported function `backend_enc_mul_imm_to_index_scratch_arch`.
 * Implements `backend_enc_mul_imm_to_index_scratch_arch`.
 * @param elf_ctx *u8
 * @param lit i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mul_imm_to_index_scratch_arch(elf_ctx: *u8, lit: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (lit <= 1) { return 0; }
  if (lit > 65535) { return 0 - 1; }
  if (ta == 1) {
    if (arch_arm64_enc_enc_u32_le(elf_ctx, ((1384120320 as u32) | ((lit as u32) * 32) | 3) as i32) != 0) { return 0 - 1; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, (453213250 as i32));
  }
  if (ta == 2) { return arch_riscv64_enc_enc_mul_imm_to_a2(elf_ctx, lit); }
  return arch_x86_64_enc_enc_imul_imm_to_ecx(elf_ctx, lit);
  }
}

/** Exported function `backend_enc_mul_imm_to_rbx_arch`.
 * Implements `backend_enc_mul_imm_to_rbx_arch`.
 * @param elf_ctx *u8
 * @param lit i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_mul_imm_to_rbx_arch(elf_ctx: *u8, lit: i32, ta: i32): i32 {
  // See implementation.
  unsafe {
  if (lit <= 1) { return 0; }
  if (lit > 65535) { return 0 - 1; }
  if (ta == 1) {
    if (arch_arm64_enc_enc_u32_le(elf_ctx, ((1384120320 as u32) | ((lit as u32) * 32) | 3) as i32) != 0) { return 0 - 1; }
    return arch_arm64_enc_enc_u32_le(elf_ctx, (453213217 as i32));
  }
  if (ta == 2) { return arch_riscv64_enc_enc_mul_imm_to_rbx(elf_ctx, lit); }
  return arch_x86_64_enc_enc_imul_imm_to_ebx(elf_ctx, lit);
  }
}

/* See implementation. */

// G-02f-208：addss via xmm0/xmm1
/** Exported function `backend_enc_addss_rax_rbx_arch`.
 * Implements `backend_enc_addss_rax_rbx_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_addss_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 203;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 243; a[1] = 15; a[2] = 88; a[3] = 193;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Scalar f32 multiply: IEEE bits in eax/rbx low 32 → product bits in eax (mulss).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding f32 `*` (wave294 Cap residual pure).
 * G.7: complete authority next to addss / mulsd (not integer imul on float bits).
 */
#[no_mangle]
export function backend_enc_mulss_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    /* movd xmm0, eax — 66 0f 6e c0 */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd xmm1, ebx — 66 0f 6e cb */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 203;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* mulss xmm0, xmm1 — f3 0f 59 c1 */
    a[0] = 243; a[1] = 15; a[2] = 89; a[3] = 193;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd eax, xmm0 — 66 0f 7e c0 */
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Scalar f32 sub: left bits in ebx, right in eax → (left-right) bits in eax (subss).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding f32 `-` (wave298 Cap residual pure).
 * G.7: complete authority next to addss/mulss/subsd (not integer sub on float bits).
 */
#[no_mangle]
export function backend_enc_subss_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    /* movd xmm0, ebx — 66 0f 6e c3 */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 195;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd xmm1, eax — 66 0f 6e c8 */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 200;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* subss xmm0, xmm1 — f3 0f 5c c1 */
    a[0] = 243; a[1] = 15; a[2] = 92; a[3] = 193;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd eax, xmm0 — 66 0f 7e c0 */
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Scalar f32 sub: left bits in eax, right in ebx → (left-right) bits in eax (subss).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding f32 `-` (wave298 Cap residual pure).
 * G.7 twin of subss_rbx_rax (rax-rbx placement convention).
 */
#[no_mangle]
export function backend_enc_subss_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    /* movd xmm0, eax — 66 0f 6e c0 */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd xmm1, ebx — 66 0f 6e cb */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 203;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* subss xmm0, xmm1 — f3 0f 5c c1 */
    a[0] = 243; a[1] = 15; a[2] = 92; a[3] = 193;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd eax, xmm0 — 66 0f 7e c0 */
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Scalar f32 divide: left bits in eax, right in ebx → quotient bits in eax (divss).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding f32 `/` (wave298 Cap residual pure).
 * G.7: complete authority next to mulss/divsd (not integer idiv on float bits).
 * IEEE Inf/NaN on /0 (no integer div-zero panic).
 */
#[no_mangle]
export function backend_enc_divss_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    /* movd xmm0, eax — 66 0f 6e c0 */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd xmm1, ebx — 66 0f 6e cb */
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 203;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* divss xmm0, xmm1 — f3 0f 5e c1 */
    a[0] = 243; a[1] = 15; a[2] = 94; a[3] = 193;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movd eax, xmm0 — 66 0f 7e c0 */
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/** Exported function `backend_enc_cvttss2si_eax_from_f32_bits_arch`.
 * Implements `backend_enc_cvttss2si_eax_from_f32_bits_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cvttss2si_eax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 243; a[1] = 15; a[2] = 44; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Truncate f64 bits in rax to i32 in eax (cvttsd2si).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as i32` from f64 (wave291).
 */
#[no_mangle]
export function backend_enc_cvttsd2si_eax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* movq xmm0, rax — 66 48 0f 6e c0 (must include 66 + REX.W). */
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 110; q[4] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5) != 0) { return 0 - 1; }
    /* cvttsd2si eax, xmm0 — f2 0f 2c c0 */
    let a: u8[4] = [];
    a[0] = 242; a[1] = 15; a[2] = 44; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Truncate f32 bits in eax to i64 in rax (REX.W cvttss2si).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as i64/u64/usize/isize` from f32 (wave303).
 * Encoding: movd xmm0,eax (66 0F 6E C0) ; cvttss2si rax,xmm0 (F3 48 0F 2C C0).
 */
#[no_mangle]
export function backend_enc_cvttss2si_rax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* movd xmm0, eax — 66 0f 6e c0 */
    let m: u8[4] = [];
    m[0] = 102; m[1] = 15; m[2] = 110; m[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &m[0], 4) != 0) { return 0 - 1; }
    /* cvttss2si rax, xmm0 — f3 48 0f 2c c0 */
    let a: u8[5] = [];
    a[0] = 243; a[1] = 72; a[2] = 15; a[3] = 44; a[4] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 5);
  }
  return 0 - 1;
}

/**
 * Truncate f64 bits in rax to i64 in rax (REX.W cvttsd2si).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as i64/u64/usize/isize` from f64 (wave303).
 * Encoding: movq xmm0,rax (66 REX.W 0F 6E C0) ; cvttsd2si rax,xmm0 (F2 48 0F 2C C0).
 */
#[no_mangle]
export function backend_enc_cvttsd2si_rax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* movq xmm0, rax — 66 48 0f 6e c0 */
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 110; q[4] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5) != 0) { return 0 - 1; }
    /* cvttsd2si rax, xmm0 — f2 48 0f 2c c0 */
    let a: u8[5] = [];
    a[0] = 242; a[1] = 72; a[2] = 15; a[3] = 44; a[4] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 5);
  }
  return 0 - 1;
}

/** Exported function `backend_enc_cvtsd2ss_eax_from_f64_bits_arch`.
 * Implements `backend_enc_cvtsd2ss_eax_from_f64_bits_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cvtsd2ss_eax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta == 1) {
    if (elf_ctx == 0 as *u8) { return 0 - 1; }
    unsafe {
      // fmov d0, x0 — move f64 bits from x0 into d0 (0x9e670000).
      if (arch_arm64_enc_enc_u32_le(elf_ctx, 0 - 1637416960) != 0) { return 0 - 1; }
      // fcvt s0, d0 — double to single convert (0x1e624000).
      if (arch_arm64_enc_enc_u32_le(elf_ctx, 509755392) != 0) { return 0 - 1; }
      // fmov w0, s0 — move f32 bits from s0 into w0 (0x1e260000).
      return arch_arm64_enc_enc_u32_le(elf_ctx, 505806848);
    }
  }
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 110; q[4] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5) != 0) { return 0 - 1; }
    let a: u8[4] = [];
    a[0] = 242; a[1] = 15; a[2] = 90; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/** Exported function `backend_enc_cvtsi2ss_eax_from_i32_arch`.
 * Implements `backend_enc_cvtsi2ss_eax_from_i32_arch`.
 * @param elf_ctx *u8
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_cvtsi2ss_eax_from_i32_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let a: u8[4] = [];
    a[0] = 243; a[1] = 15; a[2] = 42; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    a[0] = 102; a[1] = 15; a[2] = 126; a[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4);
  }
  return 0 - 1;
}

/**
 * Convert i64/u64 (value in i64 range) in rax to f32 bits in eax (REX.W cvtsi2ss).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f32` from u64/i64 (wave299 Cap residual).
 * Encoding: cvtsi2ss xmm0,rax (F3 48 0F 2A C0) ; movd eax,xmm0 (66 0F 7E C0).
 * Note: signed convert; unsigned >2^63-1 uses backend_enc_cvtsi2ss_eax_from_u64_arch (wave304).
 */
#[no_mangle]
export function backend_enc_cvtsi2ss_eax_from_i64_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* cvtsi2ss xmm0, rax — f3 48 0f 2a c0 */
    let a: u8[5] = [];
    a[0] = 243; a[1] = 72; a[2] = 15; a[3] = 42; a[4] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 5) != 0) { return 0 - 1; }
    /* movd eax, xmm0 — 66 0f 7e c0 */
    let m: u8[4] = [];
    m[0] = 102; m[1] = 15; m[2] = 126; m[3] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &m[0], 4);
  }
  return 0 - 1;
}

/**
 * Convert i32 in eax to f64 bits in rax (cvtsi2sd).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f64` from i32 (wave292).
 */
#[no_mangle]
export function backend_enc_cvtsi2sd_rax_from_i32_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* cvtsi2sd xmm0, eax — f2 0f 2a c0 */
    let a: u8[4] = [];
    a[0] = 242; a[1] = 15; a[2] = 42; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movq rax, xmm0 — 66 48 0f 7e c0 (must include 66 + REX.W). */
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 126; q[4] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5);
  }
  return 0 - 1;
}

/**
 * Convert i64/u64 (value in i64 range) in rax to f64 bits in rax (REX.W cvtsi2sd).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f64` from u64/i64 (wave295 Cap residual).
 * Encoding: cvtsi2sd xmm0,rax (F2 48 0F 2A C0) ; movq rax,xmm0 (66 REX.W 0F 7E C0).
 * Note: signed convert; unsigned >2^63-1 uses backend_enc_cvtsi2sd_rax_from_u64_arch (wave304).
 */
#[no_mangle]
export function backend_enc_cvtsi2sd_rax_from_i64_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* cvtsi2sd xmm0, rax — f2 48 0f 2a c0 */
    let a: u8[5] = [];
    a[0] = 242; a[1] = 72; a[2] = 15; a[3] = 42; a[4] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 5) != 0) { return 0 - 1; }
    /* movq rax, xmm0 — 66 48 0f 7e c0 */
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 126; q[4] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5);
  }
  return 0 - 1;
}

/**
 * Convert full-range u64 in rax to f64 bits in rax (unsigned convert sequence).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f64` from u64/usize (wave304 Cap residual).
 * Root: signed REX.W cvtsi2sd makes values >2^63-1 negative → freestanding run=0.
 * Algorithm (gcc/clang): if high bit clear, signed convert; else (v>>1)|(v&1) convert + add.
 * Fixed rel8: jns +28, jmp +10. G.7 next to signed i64 form.
 */
#[no_mangle]
export function backend_enc_cvtsi2sd_rax_from_u64_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let s: u8[43] = [];
    /* test rax,rax */
    s[0] = 72; s[1] = 133; s[2] = 192;
    /* jns +28 */
    s[3] = 121; s[4] = 28;
    /* mov rdx,rax; shr rdx,1; and eax,1; or rdx,rax */
    s[5] = 72; s[6] = 137; s[7] = 194;
    s[8] = 72; s[9] = 209; s[10] = 234;
    s[11] = 131; s[12] = 224; s[13] = 1;
    s[14] = 72; s[15] = 9; s[16] = 194;
    /* cvtsi2sd xmm0,rdx; addsd xmm0,xmm0; movq rax,xmm0 */
    s[17] = 242; s[18] = 72; s[19] = 15; s[20] = 42; s[21] = 194;
    s[22] = 242; s[23] = 15; s[24] = 88; s[25] = 192;
    s[26] = 102; s[27] = 72; s[28] = 15; s[29] = 126; s[30] = 192;
    /* jmp +10 */
    s[31] = 235; s[32] = 10;
    /* fit: cvtsi2sd xmm0,rax; movq rax,xmm0 */
    s[33] = 242; s[34] = 72; s[35] = 15; s[36] = 42; s[37] = 192;
    s[38] = 102; s[39] = 72; s[40] = 15; s[41] = 126; s[42] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &s[0], 43);
  }
  return 0 - 1;
}

/**
 * Convert full-range u64 in rax to f32 bits in eax (unsigned convert sequence).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f32` from u64/usize (wave304 Cap residual).
 * Same algorithm as u64→f64 with cvtsi2ss/addss/movd. jns +27, jmp +9.
 * G.7 next to signed backend_enc_cvtsi2ss_eax_from_i64_arch.
 */
#[no_mangle]
export function backend_enc_cvtsi2ss_eax_from_u64_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let s: u8[41] = [];
    s[0] = 72; s[1] = 133; s[2] = 192;
    s[3] = 121; s[4] = 27;
    s[5] = 72; s[6] = 137; s[7] = 194;
    s[8] = 72; s[9] = 209; s[10] = 234;
    s[11] = 131; s[12] = 224; s[13] = 1;
    s[14] = 72; s[15] = 9; s[16] = 194;
    s[17] = 243; s[18] = 72; s[19] = 15; s[20] = 42; s[21] = 194;
    s[22] = 243; s[23] = 15; s[24] = 88; s[25] = 192;
    s[26] = 102; s[27] = 15; s[28] = 126; s[29] = 192;
    s[30] = 235; s[31] = 9;
    s[32] = 243; s[33] = 72; s[34] = 15; s[35] = 42; s[36] = 192;
    s[37] = 102; s[38] = 15; s[39] = 126; s[40] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &s[0], 41);
  }
  return 0 - 1;
}

/**
 * Convert f32 bits in eax to f64 bits in rax (cvtss2sd).
 * @param elf_ctx *u8 — ELF codegen context
 * @param ta i32 — target arch; 0 = x86_64 only
 * @return i32 — 0 ok, -1 unsupported arch / null ctx
 * PLATFORM: LINUX+MACOS x86_64 — freestanding `as f64` from f32 (wave293 Cap residual).
 */
#[no_mangle]
export function backend_enc_cvtss2sd_rax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32 {
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    /* movd xmm0, eax — 66 0f 6e c0 */
    let a: u8[4] = [];
    a[0] = 102; a[1] = 15; a[2] = 110; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* cvtss2sd xmm0, xmm0 — f3 0f 5a c0 */
    a[0] = 243; a[1] = 15; a[2] = 90; a[3] = 192;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &a[0], 4) != 0) { return 0 - 1; }
    /* movq rax, xmm0 — 66 48 0f 7e c0 */
    let q: u8[5] = [];
    q[0] = 102; q[1] = 72; q[2] = 15; q[3] = 126; q[4] = 192;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &q[0], 5);
  }
  return 0 - 1;
}

/**
 * Move IEEE f32 bits in eax/w0 into FP arg register k.
 * @param elf_ctx *u8 — ElfCodegenCtx*; null rejected
 * @param k i32 — xmmK (SysV) or sK (AAPCS64); 0..7
 * @param ta i32 — 0=x86_64 SysV movd; 1=AAPCS64 fmov sK,w0
 * @return i32 — 0 ok; -1 null/range/unsupported ta
 * PLATFORM: LINUX+MACOS x86_64 SysV · MACOS|ARM64 AAPCS64
 */
#[no_mangle]
export function backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx: *u8, k: i32, ta: i32): i32 {
  if (ta == 1) {
    if (elf_ctx == 0) { return 0 - 1; }
    if (k < 0) { return 0 - 1; }
    if (k > 7) { return 0 - 1; }
    // fmov sK, w0 — 0x1e270000 | K (≡ addss ta==1 first insn).
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((505872384 as u32) | (k as u32)) as i32);
  }
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  if (k < 0) { return 0 - 1; }
  if (k > 7) { return 0 - 1; }
  unsafe {
    let p: u8[3] = [];
    p[0] = 102; p[1] = 15; p[2] = 110;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &p[0], 3) != 0) { return 0 - 1; }
    let modrm: u8 = (192 | ((k * 8) & 255)) as u8;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &modrm, 1);
  }
  return 0 - 1;
}

/**
 * Harvest IEEE f32 bits from FP arg/return register k into eax/w0.
 * @param elf_ctx *u8 — ElfCodegenCtx*; null rejected
 * @param k i32 — xmmK (SysV) or sK (AAPCS64); 0..7
 * @param ta i32 — 0=x86_64 SysV movd; 1=AAPCS64 fmov w0,sK
 * @return i32 — 0 ok; -1 null/range/unsupported ta
 * PLATFORM: LINUX+MACOS x86_64 SysV · MACOS|ARM64 AAPCS64
 */
#[no_mangle]
export function backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx: *u8, k: i32, ta: i32): i32 {
  if (ta == 1) {
    if (elf_ctx == 0) { return 0 - 1; }
    if (k < 0) { return 0 - 1; }
    if (k > 7) { return 0 - 1; }
    // fmov w0, sK — 0x1e260000 | (K << 5).
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((505806848 as u32) | ((k as u32) * 32)) as i32);
  }
  if (ta != 0) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  if (k < 0) { return 0 - 1; }
  if (k > 7) { return 0 - 1; }
  unsafe {
    let p: u8[3] = [];
    p[0] = 102; p[1] = 15; p[2] = 126;
    if (pipeline_elf_ctx_append_bytes(elf_ctx, &p[0], 3) != 0) { return 0 - 1; }
    let modrm: u8 = (192 | ((k * 8) & 255)) as u8;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &modrm, 1);
  }
  return 0 - 1;
}

/* See implementation. */

// arch_arm64_enc_enc_cmp_w0_imm12: see function docblock below.
/** Exported function `arch_arm64_enc_enc_cmp_w0_imm12`.
 * Comparison/utility `arch_arm64_enc_enc_cmp_w0_imm12`.
 * @param elf_ctx *u8
 * @param imm12 i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_cmp_w0_imm12(elf_ctx: *u8, imm12: i32): i32 {
  // See implementation.
  unsafe {
  let imm: i32 = imm12 & 4095;
  return arch_arm64_enc_enc_u32_le(elf_ctx, ((1895825439 as u32) | (imm * 1024)) as i32);
  }
}

// arm64 cset w0,cond — 0x1a9f07e0 | (cond<<12)
/** Exported function `arch_arm64_enc_enc_cset_w0_from_cc`.
 * Implements `arch_arm64_enc_enc_cset_w0_from_cc`.
 * @param elf_ctx *u8
 * @param cc i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_cset_w0_from_cc(elf_ctx: *u8, cc: i32): i32 {
  unsafe {
    let c: i32 = pipeline_asm_arm64_cset_cond_enc_from_cc(cc);
    return arch_arm64_enc_enc_u32_le(elf_ctx, ((446629856 as u32) | (c * 4096)) as i32);
  }
  return 0 - 1;
}

// arch_arm64_enc_enc_add_sp_imm12: see function docblock below.
/** Exported function `arch_arm64_enc_enc_add_sp_imm12`.
 * Implements `arch_arm64_enc_enc_add_sp_imm12`.
 * @param elf_ctx *u8
 * @param imm i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_add_sp_imm12(elf_ctx: *u8, imm: i32): i32 {
  return backend_enc_arm64_add_sp_imm12_c(elf_ctx, imm);
}

/** Exported function `arch_arm64_enc_enc_sub_sp_imm12`.
 * Implements `arch_arm64_enc_enc_sub_sp_imm12`.
 * @param elf_ctx *u8
 * @param imm i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_sub_sp_imm12(elf_ctx: *u8, imm: i32): i32 {
  return backend_enc_arm64_sub_sp_imm12_c(elf_ctx, imm);
}

/** Exported function `arch_arm64_enc_enc_str_x0_sp_offset`.
 * Implements `arch_arm64_enc_enc_str_x0_sp_offset`.
 * @param elf_ctx *u8
 * @param off_bytes i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_str_x0_sp_offset(elf_ctx: *u8, off_bytes: i32): i32 {
  return backend_enc_arm64_str_x0_sp_offset_c(elf_ctx, off_bytes);
}

/** Exported function `arch_arm64_enc_enc_call`.
 * Implements `arch_arm64_enc_enc_call`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
#[no_mangle]
export function arch_arm64_enc_enc_call(elf_ctx: *u8, name: *u8, name_len: i32): i32 {
  return backend_enc_arm64_call_c(elf_ctx, name, name_len);
}

/**
 * Thin wrapper: arch_arm64_enc_enc_blr → backend_enc_arm64_blr_c.
 * F7 dyn Trait vtable dispatch — emit blr xN for indirect call.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — register number 0..30
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: MACOS|ARM64 AAPCS64 — G.7 twin product seed.
 */
#[no_mangle]
export function arch_arm64_enc_enc_blr(elf_ctx: *u8, reg: i32): i32 {
  return backend_enc_arm64_blr_c(elf_ctx, reg);
}

/**
 * Thin wrapper: arch_arm64_enc_enc_ldr_xreg_xreg_imm → backend_enc_arm64_ldr_xreg_xreg_imm_c.
 * F7 dyn Trait vtable dispatch — emit ldr xN, [xM, #off] for 64-bit load.
 * @param elf_ctx *u8 — emit context
 * @param dst_reg i32 — destination register 0..30
 * @param base_reg i32 — base register 0..30
 * @param offset i32 — byte offset, multiple of 8 in [0, 32760]
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: MACOS|ARM64 AAPCS64 — G.7 twin product seed.
 */
#[no_mangle]
export function arch_arm64_enc_enc_ldr_xreg_xreg_imm(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  return backend_enc_arm64_ldr_xreg_xreg_imm_c(elf_ctx, dst_reg, base_reg, offset);
}

/**
 * Thin wrapper: arch_x86_64_enc_enc_call_reg → backend_enc_x86_64_call_reg_c.
 * F7 dyn Trait vtable dispatch — emit call rN for indirect call.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — register number 0..15
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU x86_64 SysV — G.7 twin product seed.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_call_reg(elf_ctx: *u8, reg: i32): i32 {
  return backend_enc_x86_64_call_reg_c(elf_ctx, reg);
}

/**
 * Thin wrapper: arch_x86_64_enc_enc_load_rax_rbx_disp32 → backend_enc_x86_64_load_rax_rbx_disp32_c.
 * F7 dyn Trait vtable dispatch — emit mov rax, [rbx+disp32] for 64-bit load.
 * @param elf_ctx *u8 — emit context
 * @param dst_reg i32 — destination register (ignored, always rax)
 * @param base_reg i32 — base register (ignored, always rbx)
 * @param offset i32 — byte offset (disp32 form)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU x86_64 SysV — G.7 twin product seed.
 */
#[no_mangle]
export function arch_x86_64_enc_enc_load_rax_rbx_disp32(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  return backend_enc_x86_64_load_rax_rbx_disp32_c(elf_ctx, dst_reg, base_reg, offset);
}

/**
 * Thin wrapper: arch_riscv64_enc_enc_jalr_reg → backend_enc_riscv64_jalr_reg_c.
 * F7 dyn Trait vtable dispatch — emit jalr x1, 0(xN) for indirect call.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — register number 0..31
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU riscv64 — G.7 twin product seed.
 */
#[no_mangle]
export function arch_riscv64_enc_enc_jalr_reg(elf_ctx: *u8, reg: i32): i32 {
  return backend_enc_riscv64_jalr_reg_c(elf_ctx, reg);
}

/**
 * Thin wrapper: arch_riscv64_enc_enc_ldr_xreg_xreg_imm → backend_enc_riscv64_ldr_xreg_xreg_imm_c.
 * F7 dyn Trait vtable dispatch — emit ld rd, off(rs1) for 64-bit load.
 * @param elf_ctx *u8 — emit context
 * @param dst_reg i32 — destination register 0..31
 * @param base_reg i32 — base register 0..31
 * @param offset i32 — byte offset (imm12 form)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: LINUX|UBUNTU riscv64 — G.7 twin product seed.
 */
#[no_mangle]
export function arch_riscv64_enc_enc_ldr_xreg_xreg_imm(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32): i32 {
  return backend_enc_riscv64_ldr_xreg_xreg_imm_c(elf_ctx, dst_reg, base_reg, offset);
}

/**
 * Cross-arch indirect call via register: blr xN (arm64), call rN (x86_64), jalr (riscv64).
 * F7 dyn Trait vtable dispatch — call through slot fn ptr.
 * @param elf_ctx *u8 — emit context (ElfCodegenCtx)
 * @param reg i32 — register holding the function pointer
 * @param ta i32 — target arch: 0=x86_64, 1=arm64, 2=riscv64
 * @return i32 — 0 ok, -1 failure
 * PLATFORM: SHARED — dispatches to per-arch encoders.
 */
#[no_mangle]
export function backend_enc_blr_arch(elf_ctx: *u8, reg: i32, ta: i32): i32 {
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_blr(elf_ctx, reg); }
  if (ta == 2) { return arch_riscv64_enc_enc_jalr_reg(elf_ctx, reg); }
  return arch_x86_64_enc_enc_call_reg(elf_ctx, reg);
  }
}

/**
 * Cross-arch 64-bit load with register base + immediate offset:
 *   ldr xN, [xM, #off] (arm64), mov rax, [rbx+disp32] (x86_64), ld rd,off(rs1) (riscv64).
 * F7 dyn Trait vtable dispatch — load vtable ptr and slot fn ptr.
 * @param elf_ctx *u8 — emit context (ElfCodegenCtx)
 * @param dst_reg i32 — destination register
 * @param base_reg i32 — base register
 * @param offset i32 — byte offset
 * @param ta i32 — target arch: 0=x86_64, 1=arm64, 2=riscv64
 * @return i32 — 0 ok, -1 failure
 * PLATFORM: SHARED — dispatches to per-arch encoders.
 */
#[no_mangle]
export function backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx: *u8, dst_reg: i32, base_reg: i32, offset: i32, ta: i32): i32 {
  unsafe {
  if (ta == 1) { return arch_arm64_enc_enc_ldr_xreg_xreg_imm(elf_ctx, dst_reg, base_reg, offset); }
  if (ta == 2) { return arch_riscv64_enc_enc_ldr_xreg_xreg_imm(elf_ctx, dst_reg, base_reg, offset); }
  return arch_x86_64_enc_enc_load_rax_rbx_disp32(elf_ctx, dst_reg, base_reg, offset);
  }
}

/**
 * Materialize a symbol address into a GP register.
 * ARM64: `adrp xN, sym@PAGE` + `add xN, xN, sym@PAGEOFF` (PAGE21 + PAGEOFF12).
 * x86_64: `lea r64, [rip+disp32]` + untyped PC32 reloc (same contract as
 * `glue_asm_lea_rax_common_rip_x86`). Do NOT emit `movabs` + absolute64 in
 * .text — that is TEXTREL on PIE and the dyn vtable pointer stays unrelocated.
 * Used by F7 dyn coerce to store `.vtable = &xlang_vtable_<Trait>_for_<Type>`.
 * @param elf_ctx *u8 — emit context
 * @param reg i32 — destination register (arm64 0..30 / x86 0..15)
 * @param name *u8 — link symbol bytes (already Mach-O-underscored when needed)
 * @param name_len i32 — length of name
 * @param ta i32 — 0=x86_64, 1=arm64, 2=riscv64 (riscv unsupported → -1)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED — MACOS|ARM64 PAGE21/12 · LINUX x86_64 RIP-relative PC32.
 */
#[no_mangle]
export function backend_enc_lea_sym_to_reg_arch(elf_ctx: *u8, reg: i32, name: *u8, name_len: i32, ta: i32): i32 {
  if (elf_ctx == 0 as *u8 || name == 0 as *u8 || name_len <= 0) { return 0 - 1; }
  unsafe {
    if (ta == 1) {
      if (reg < 0 || reg > 30) { return 0 - 1; }
      /* adrp xN, #0 — reloc PAGE21 (r_type=3, pcrel=1) fills the page immediate. */
      if (backend_enc_append_u32_le_c(elf_ctx, (2415919104 as u32) | (reg as u32)) != 0) {
        return 0 - 1;
      }
      let adrp_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
      if (pipeline_elf_ctx_append_reloc_typed(elf_ctx, adrp_at, name, name_len, 3, 1) != 0) {
        return 0 - 1;
      }
      /* add xN, xN, #0 — reloc PAGEOFF12 (r_type=4, pcrel=0). */
      if (backend_enc_append_u32_le_c(elf_ctx, (2432696320 as u32) | ((reg as u32) * 32) | (reg as u32)) != 0) {
        return 0 - 1;
      }
      let add_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
      return pipeline_elf_ctx_append_reloc_typed(elf_ctx, add_at, name, name_len, 4, 0);
    }
    if (ta == 0) {
      if (reg < 0 || reg > 15) { return 0 - 1; }
      /* lea r64, [rip+disp32]: REX.W[+R] 8D ModRM(reg, r/m=101) disp32.
       * REX.R extends ModRM.reg (dest); r/m is RIP so REX.B stays 0.
       * Reloc is the same untyped PC32 as glue_asm_lea_rax_common_rip_x86. */
      let rex: u8 = 72;
      if (reg >= 8) { rex = 76; }
      if (backend_enc_append_u8_c(elf_ctx, rex) != 0) { return 0 - 1; }
      if (backend_enc_append_u8_c(elf_ctx, 141) != 0) { return 0 - 1; }
      let modrm: u8 = ((((reg & 7) * 8) + 5) as u8);
      if (backend_enc_append_u8_c(elf_ctx, modrm) != 0) { return 0 - 1; }
      let z: u8 = 0;
      let k: i32 = 0;
      while (k < 4) {
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &z, 1) != 0) { return 0 - 1; }
        k = k + 1;
      }
      let rel32_at: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx) - 4;
      return pipeline_elf_ctx_append_reloc(elf_ctx, rel32_at, name, name_len);
    }
  }
  return 0 - 1;
}

// arch_riscv64_enc_enc_call: see function docblock below.
/** Exported function `arch_riscv64_enc_enc_call`.
 * Implements `arch_riscv64_enc_enc_call`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
#[no_mangle]
export function arch_riscv64_enc_enc_call(elf_ctx: *u8, name: *u8, name_len: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (name == 0) { return 0 - 1; }
  if (name_len <= 0) { return 0 - 1; }
  return 0 - 1;
}

/** Exported function `arch_riscv64_enc_enc_mov_rax_to_arg_reg`.
 * Implements `arch_riscv64_enc_enc_mov_rax_to_arg_reg`.
 * @param elf_ctx *u8
 * @param k i32
 * @return i32
 */
#[no_mangle]
export function arch_riscv64_enc_enc_mov_rax_to_arg_reg(elf_ctx: *u8, k: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  if (k < 0) { return 0 - 1; }
  return 0 - 1;
}

// backend_enc_append_u8_c: see function docblock below.
/** Exported function `backend_enc_append_u8_c`.
 * Implements `backend_enc_append_u8_c`.
 * @param elf_ctx *u8
 * @param byte i32
 * @return i32
 */
#[no_mangle]
export function backend_enc_append_u8_c(elf_ctx: *u8, byte: i32): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  let b: u8 = (byte & 255) as u8;
  unsafe {
    return pipeline_elf_ctx_append_bytes(elf_ctx, &b, 1);
  }
  return 0 - 1;
}

// x86_64 cdqe：48 98
/** Exported function `arch_x86_64_enc_enc_cdqe_rax`.
 * Implements `arch_x86_64_enc_enc_cdqe_rax`.
 * @param elf_ctx *u8
 * @return i32
 */
#[no_mangle]
export function arch_x86_64_enc_enc_cdqe_rax(elf_ctx: *u8): i32 {
  if (elf_ctx == 0) { return 0 - 1; }
  unsafe {
    let cdqe: u8[2] = [];
    cdqe[0] = 72;
    cdqe[1] = 152;
    return pipeline_elf_ctx_append_bytes(elf_ctx, &cdqe[0], 2);
  }
  return 0 - 1;
}
