// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// See implementation.
//
// See implementation.
// See implementation.
//
// See implementation.
// f_add_sym）。
//

const elf = import("platform.elf");

/** Exported function `enc_u8`.
 * Implements `enc_u8`.
 * @param ctx *ElfCodegenCtx
 * @param b i32
 * @return i32
 */
export function enc_u8(ctx: *ElfCodegenCtx, b: i32): i32 {
  let buf: u8[1] = [0];
  buf[0] = elf.elf_to_u8(b);
  return elf.append_elf_bytes(ctx, buf, 1);
}

/** Exported function `enc_u32_le`.
 * Implements `enc_u32_le`.
 * @param ctx *ElfCodegenCtx
 * @param imm i64
 * @return i32
 */
export function enc_u32_le(ctx: *ElfCodegenCtx, imm: i64): i32 {
  let buf: u8[4] = [];
  buf[0] = elf.elf_u32_byte_at(imm, 0);
  buf[1] = elf.elf_u32_byte_at(imm, 1);
  buf[2] = elf.elf_u32_byte_at(imm, 2);
  buf[3] = elf.elf_u32_byte_at(imm, 3);
  return elf.append_elf_bytes(ctx, buf, 4);
}

/**
 * See implementation.
 *
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 * PLATFORM: SHARED — Linux/macOS x86_64 SysV.
 */
export function enc_prologue(ctx: *ElfCodegenCtx, frame_size: i32): i32 {
  if (enc_u8(ctx, 85) != 0) { return -1; }
  let mov: u8[3] = [72, 137, 229];
  if (elf.append_elf_bytes(ctx, mov, 3) != 0) { return -1; }
  /* pushq %rbx — callee-saved; body may use rbx as store base. */
  if (enc_u8(ctx, 83) != 0) { return -1; }
  /*
   * PLATFORM: SHARED x86_64 SysV.
   * push rbp + push rbx leave RSP ≡ 8 (mod 16) after entry (RSP ≡ 8).
   * Before CALL, ABI needs RSP ≡ 0 — so sub imm must be ≡ 8 (mod 16).
   * See arch_x86_64_enc_enc_prologue (product authority; same pad rule).
   */
  let fs_i: i32 = frame_size;
  if (fs_i < 0) { fs_i = 0; }
  let rem: i32 = fs_i % 16;
  if (rem != 8) {
    if (rem < 8) {
      fs_i = fs_i + (8 - rem);
    } else {
      fs_i = fs_i + (16 - rem + 8);
    }
  }
  let sub: u8[7] = [72, 129, 236, 0, 0, 0, 0];
  sub[3] = elf.elf_to_u8(fs_i);
  sub[4] = elf.elf_to_u8(fs_i >> 8);
  sub[5] = elf.elf_to_u8(fs_i >> 16);
  sub[6] = elf.elf_to_u8(fs_i >> 24);
  return elf.append_elf_bytes(ctx, sub, 7);
}

/**
 * See implementation.
 * See implementation.
 */
export function enc_epilogue(ctx: *ElfCodegenCtx): i32 {
  /* lea rsp, [rbp-8] → 48 8d 65 f8 */
  let lea: u8[4] = [72, 141, 101, 248];
  if (elf.append_elf_bytes(ctx, lea, 4) != 0) { return -1; }
  if (enc_u8(ctx, 91) != 0) { return -1; }
  if (enc_u8(ctx, 93) != 0) { return -1; }
  return enc_u8(ctx, 195);
}

/** movl $imm32, %eax。 */
export function enc_ret_imm32(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  if (enc_u8(ctx, 184) != 0) { return -1; }
  return enc_u32_le(ctx, imm32);
}

/** movl $imm32, %ebx。 */
export function enc_mov_imm32_to_rbx(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  if (enc_u8(ctx, 187) != 0) { return -1; }
  return enc_u32_le(ctx, imm32);
}

/** Exported function `enc_mov_imm64_to_rax`.
 * Implements `enc_mov_imm64_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param lo i32
 * @param hi i32
 * @return i32
 */
export function enc_mov_imm64_to_rax(ctx: *ElfCodegenCtx, lo: i32, hi: i32): i32 {
  if (enc_u8(ctx, 72) != 0) { return -1; }
  if (enc_u8(ctx, 184) != 0) { return -1; }
  if (enc_u32_le(ctx, lo) != 0) { return -1; }
  return enc_u32_le(ctx, hi);
}

/** pushq %rax。 */
export function enc_push_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u8(ctx, 80);
}

/** pushq %rbx。 */
export function enc_push_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u8(ctx, 83);
}

/** popq %rbx。 */
export function enc_pop_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u8(ctx, 91);
}

/** popq %rax。 */
export function enc_pop_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u8(ctx, 88);
}

/** addl %ebx, %eax — 32-bit add (zero-extends to RAX).
 * Why: X language integer arithmetic defaults to 32-bit (i32/u32/u8/bool).
 *      A 32-bit ADD EAX,EBX zero-extends the result to RAX, giving correct
 *      wrapping semantics for u32 (0xFFFFFFFF + 1 = 0). The prior 64-bit
 *      ADD RAX,RBX did not wrap at 32 bits, breaking unsigned overflow.
 * Invariant: Must match seed authority backend_x86_64_enc_c.from_x.c.
 *            i64/u64/ptr arithmetic uses enc_rax_plus_rbx_scale1 (64-bit) or
 *            ptr-arith scaled paths, NOT this function.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
export function enc_add_rax_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [1, 216];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** subq %rax, %rbx; movq %rbx, %rax。 */
export function enc_sub_rbx_rax_then_mov(ctx: *ElfCodegenCtx): i32 {
  let sub: u8[3] = [72, 41, 195];
  if (elf.append_elf_bytes(ctx, sub, 3) != 0) { return -1; }
  let mov: u8[3] = [72, 137, 216];
  return elf.append_elf_bytes(ctx, mov, 3);
}

/** Exported function `enc_sub_rax_rbx`.
 * Implements `enc_sub_rax_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
/** subl %ebx, %eax — 32-bit sub (zero-extends to RAX).
 * Why: Must match arm64_enc.x 32-bit sub. i64/u64/ptr use scaled paths.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
export function enc_sub_rax_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [41, 216];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** imull %ebx, %eax — 32-bit imul (zero-extends to RAX).
 * Why: Must match arm64_enc.x 32-bit mul. i64/u64/ptr use scaled paths.
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64. */
export function enc_imul_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [15, 175, 195];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** movq %rax, %rbx。 */
export function enc_mov_rax_to_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 137, 195];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** notl %eax。 */
export function enc_not_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [247, 208];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/**
 * andq %rbx, %rax (REX.W). 32-bit andl wiped usize/ptr high 32.
 * @param ctx *ElfCodegenCtx — ELF emit ctx; null handled by append
 * @return i32 — 0 success, -1 overflow
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64
 */
export function enc_and_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 33, 216];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/**
 * orq %rbx, %rax (REX.W). 32-bit orl truncated g02f_load_ptr_at usize reconstruct.
 * @param ctx *ElfCodegenCtx — ELF emit ctx; null handled by append
 * @return i32 — 0 success, -1 overflow
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64
 */
export function enc_or_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 9, 216];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/**
 * xorq %rbx, %rax (REX.W). Same high-32 wipe as AND/OR.
 * @param ctx *ElfCodegenCtx — ELF emit ctx; null handled by append
 * @return i32 — 0 success, -1 overflow
 * PLATFORM: LINUX|UBUNTU|WINDOWS|x86_64
 */
export function enc_xor_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 49, 216];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_mov_rbx_to_ecx`.
 * Implements `enc_mov_rbx_to_ecx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_mov_rbx_to_ecx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [137, 217];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** sall %cl, %eax。 */
export function enc_shl_cl_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [211, 224];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** shrl %cl, %eax。 */
export function enc_shr_cl_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [211, 232];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** sarl %cl, %eax。 */
export function enc_sar_cl_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [211, 248];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_shl_cl_rax`.
 * Implements `enc_shl_cl_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_shl_cl_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 211, 224];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_shr_cl_rax`.
 * Implements `enc_shr_cl_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_shr_cl_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 211, 232];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_sar_cl_rax`.
 * Implements `enc_sar_cl_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sar_cl_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 211, 248];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** cltd。 */
export function enc_cltd(ctx: *ElfCodegenCtx): i32 {
  return enc_u8(ctx, 153);
}

/** Exported function `enc_xor_edx_edx`.
 * Implements `enc_xor_edx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_xor_edx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [49, 210];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_div_rbx`.
 * Implements `enc_div_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_div_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [247, 243];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_idiv_rbx`.
 * Implements `enc_idiv_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_idiv_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [247, 251];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** movl %edx, %eax。 */
export function enc_mov_edx_to_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [137, 208];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** negl %eax。 */
export function enc_neg_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [247, 216];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** test %eax, %eax。 */
export function enc_test_eax_eax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [133, 192];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_test_rbx_rbx`.
 * Implements `enc_test_rbx_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_test_rbx_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [133, 219];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** setz %al; movzbl %al, %eax。 */
export function enc_setz_movzbl_eax(ctx: *ElfCodegenCtx): i32 {
  let s: u8[3] = [15, 148, 192];
  if (elf.append_elf_bytes(ctx, s, 3) != 0) { return -1; }
  let m: u8[3] = [15, 182, 192];
  return elf.append_elf_bytes(ctx, m, 3);
}

/** Exported function `enc_cmp_rbx_rax`.
 * Comparison/utility `enc_cmp_rbx_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_cmp_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [57, 195];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_cmp_rax_rbx`.
 * Comparison/utility `enc_cmp_rax_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_cmp_rax_rbx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [57, 216];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_cmp_eax_imm32`.
 * Comparison/utility `enc_cmp_eax_imm32`.
 * @param ctx *ElfCodegenCtx
 * @param imm32 i32
 * @return i32
 */
export function enc_cmp_eax_imm32(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  let b: u8[1] = [61];
  if (elf.append_elf_bytes(ctx, b, 1) != 0) { return -1; }
  return enc_u32_le(ctx, imm32);
}

/** Exported function `enc_cmp_setcc_movzbl`.
 * Comparison/utility `enc_cmp_setcc_movzbl`.
 * @param ctx *ElfCodegenCtx
 * @param cc i32
 * @return i32
 */
export function enc_cmp_setcc_movzbl(ctx: *ElfCodegenCtx, cc: i32): i32 {
  let op: i32 = 148;
  if (cc == 1) { op = 149; }
  if (cc == 2) { op = 156; }
  if (cc == 3) { op = 158; }
  if (cc == 4) { op = 159; }
  if (cc == 5) { op = 157; }
  // Unsigned 6..9: SETB/SETBE/SETA/SETAE (0x92/0x96/0x97/0x93).
  if (cc == 6) { op = 146; }
  if (cc == 7) { op = 150; }
  if (cc == 8) { op = 151; }
  if (cc == 9) { op = 147; }
  let s: u8[3] = [15, elf.elf_to_u8(op), 192];
  if (elf.append_elf_bytes(ctx, s, 3) != 0) { return -1; }
  let m: u8[3] = [15, 182, 192];
  return elf.append_elf_bytes(ctx, m, 3);
}

/** Exported function `enc_store_rax_to_rbp`.
 * Implements `enc_store_rax_to_rbp`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_store_rax_to_rbp(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[4] = [72, 137, 69, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  let buf: u8[7] = [72, 137, 133, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** Exported function `enc_mov_arg_reg_to_rax`.
 * Implements `enc_mov_arg_reg_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param k i32
 * @return i32
 */
export function enc_mov_arg_reg_to_rax(ctx: *ElfCodegenCtx, k: i32): i32 {
  let idx: i32 = k;
  if (idx < 0) { idx = 0; }
  if (idx > 5) { idx = 5; }
  /* See implementation. */
  if (idx == 0) {
    let b0: u8[3] = [72, 137, 248];
    return elf.append_elf_bytes(ctx, b0, 3);
  }
  if (idx == 1) {
    let b1: u8[3] = [72, 137, 240];
    return elf.append_elf_bytes(ctx, b1, 3);
  }
  if (idx == 2) {
    let b2: u8[3] = [72, 137, 208];
    return elf.append_elf_bytes(ctx, b2, 3);
  }
  if (idx == 3) {
    let b3: u8[3] = [72, 137, 200];
    return elf.append_elf_bytes(ctx, b3, 3);
  }
  if (idx == 4) {
    let b4: u8[3] = [76, 137, 192];
    return elf.append_elf_bytes(ctx, b4, 3);
  }
  let b5: u8[3] = [76, 137, 200];
  return elf.append_elf_bytes(ctx, b5, 3);
}

/** Exported function `enc_load_rbp_pos_to_rax`.
 * Implements `enc_load_rbp_pos_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param off_pos i32
 * @return i32
 */
export function enc_load_rbp_pos_to_rax(ctx: *ElfCodegenCtx, off_pos: i32): i32 {
  let disp: i32 = off_pos;
  if (disp < 0) { disp = 0; }
  if (disp <= 127) {
    let buf: u8[4] = [72, 139, 69, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  let buf: u8[7] = [72, 139, 133, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** movq -offset(%rbp), %rax。 */
export function enc_load_rbp_to_rax(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[4] = [72, 139, 69, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  let buf: u8[7] = [72, 139, 133, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** Exported function `enc_load_rbp_to_rbx`.
 * Implements `enc_load_rbp_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_rbx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[4] = [72, 139, 93, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  /* See implementation. */
  let buf: u8[7] = [72, 139, 157, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** Exported function `enc_lea_rbp_to_rax`.
 * Implements `enc_lea_rbp_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_lea_rbp_to_rax(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[4] = [72, 141, 69, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  let buf: u8[7] = [72, 141, 133, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** Exported function `enc_lea_rbp_to_rbx`.
 * Implements `enc_lea_rbp_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_lea_rbp_to_rbx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[4] = [72, 141, 93, 0];
    buf[3] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 4);
  }
  let buf: u8[7] = [72, 141, 157, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(disp);
  buf[4] = elf.elf_to_u8(disp >> 8);
  buf[5] = elf.elf_to_u8(disp >> 16);
  buf[6] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/**
* See implementation.
* memset（SysV）。
*/
export function enc_memset_rbp_zero(ctx: *ElfCodegenCtx, rbp_off: i32, nbytes: i32): i32 {
  if (nbytes <= 0) {
    return 0;
  }
  if (enc_lea_rbp_to_rax(ctx, rbp_off) != 0) {
    return -1;
  }
  if (enc_mov_rax_to_arg_reg(ctx, 0) != 0) {
    return -1;
  }
  let xor_esi: u8[2] = [49, 246];
  if (elf.append_elf_bytes(ctx, xor_esi, 2) != 0) {
    return -1;
  }
  if (enc_mov_imm32_to_rbx(ctx, nbytes) != 0) {
    return -1;
  }
  if (enc_mov_rbx_to_rax(ctx) != 0) {
    return -1;
  }
  if (enc_mov_rax_to_arg_reg(ctx, 2) != 0) {
    return -1;
  }
  let memset_nm: u8[128] = [109, 101, 109, 115, 101, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  return enc_call(ctx, memset_nm, 6);
}

/** Exported function `enc_rax_plus_rbx_scale1`.
 * Implements `enc_rax_plus_rbx_scale1`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale1(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 4, 24];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_rax_plus_rbx_scale4`.
 * Implements `enc_rax_plus_rbx_scale4`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale4(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 4, 152];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_rax_plus_rbx_scale8`.
 * Implements `enc_rax_plus_rbx_scale8`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale8(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 4, 216];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_store_rax_to_rbx_indirect`.
 * Implements `enc_store_rax_to_rbx_indirect`.
 * @param ctx *ElfCodegenCtx
 * @param elem_sz i32
 * @return i32
 */
export function enc_store_rax_to_rbx_indirect(ctx: *ElfCodegenCtx, elem_sz: i32): i32 {
  if (elem_sz == 1) {
    let buf: u8[2] = [136, 3];
    return elf.append_elf_bytes(ctx, buf, 2);
  }
  if (elem_sz == 4) {
    let buf: u8[2] = [137, 3];
    return elf.append_elf_bytes(ctx, buf, 2);
  }
  let buf: u8[3] = [72, 137, 3];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_load_32_from_rax`.
 * Implements `enc_load_32_from_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_load_32_from_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [139, 0];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_cdqe_rax`.
 * Implements `enc_cdqe_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_cdqe_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [72, 152];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_load_zext8_from_rax`.
 * Implements `enc_load_zext8_from_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_load_zext8_from_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [15, 182, 0];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_add_imm_to_rax`.
 * Implements `enc_add_imm_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_rax(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (enc_u8(ctx, 72) != 0) { return -1; }
  if (enc_u8(ctx, 5) != 0) { return -1; }
  return enc_u32_le(ctx, imm);
}

/** Exported function `enc_add_imm_to_rbx`.
 * Implements `enc_add_imm_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_rbx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (enc_u8(ctx, 72) != 0) { return -1; }
  if (enc_u8(ctx, 129) != 0) { return -1; }
  if (enc_u8(ctx, 195) != 0) { return -1; }
  return enc_u32_le(ctx, imm);
}

/** Exported function `enc_load_rbp_to_eax32`.
 * Implements `enc_load_rbp_to_eax32`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_eax32(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[3] = [139, 69, 0];
    buf[2] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [139, 133, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(disp);
  buf[3] = elf.elf_to_u8(disp >> 8);
  buf[4] = elf.elf_to_u8(disp >> 16);
  buf[5] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_load_rbp_to_ebx32`.
 * Implements `enc_load_rbp_to_ebx32`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_ebx32(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[3] = [139, 93, 0];
    buf[2] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [139, 155, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(disp);
  buf[3] = elf.elf_to_u8(disp >> 8);
  buf[4] = elf.elf_to_u8(disp >> 16);
  buf[5] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_load_rbp_to_ecx`.
 * Implements `enc_load_rbp_to_ecx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_ecx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[3] = [139, 77, 0];
    buf[2] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [139, 141, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(disp);
  buf[3] = elf.elf_to_u8(disp >> 8);
  buf[4] = elf.elf_to_u8(disp >> 16);
  buf[5] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_lea_rbx_plus_rcx_scale1`.
 * Implements `enc_lea_rbx_plus_rcx_scale1`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_lea_rbx_plus_rcx_scale1(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 28, 11];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_lea_rbx_plus_rcx_scale4`.
 * Implements `enc_lea_rbx_plus_rcx_scale4`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_lea_rbx_plus_rcx_scale4(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 28, 139];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_lea_rbx_plus_rcx_scale8`.
 * Implements `enc_lea_rbx_plus_rcx_scale8`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_lea_rbx_plus_rcx_scale8(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[4] = [72, 141, 28, 203];
  return elf.append_elf_bytes(ctx, buf, 4);
}

/** Exported function `enc_add_imm_to_ecx`.
 * Implements `enc_add_imm_to_ecx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_ecx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [131, 193, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [129, 193, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_load_rbp_to_edx`.
 * Implements `enc_load_rbp_to_edx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_edx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let disp: i32 = 0 - offset;
  if (disp >= -128 && disp <= -1) {
    let buf: u8[3] = [139, 85, 0];
    buf[2] = elf.elf_to_u8(disp);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [139, 149, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(disp);
  buf[3] = elf.elf_to_u8(disp >> 8);
  buf[4] = elf.elf_to_u8(disp >> 16);
  buf[5] = elf.elf_to_u8(disp >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_add_ecx_edx`.
 * Implements `enc_add_ecx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_add_ecx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [1, 209];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_sub_imm_from_ecx`.
 * Implements `enc_sub_imm_from_ecx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_sub_imm_from_ecx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [131, 233, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [129, 233, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_sub_ecx_edx`.
 * Implements `enc_sub_ecx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_ecx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [41, 209];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** subl %ecx, %edx + movl %edx, %ecx（scratch = secondary - scratch，i-(j+k)）。 */
export function enc_rsub_ecx_edx(ctx: *ElfCodegenCtx): i32 {
  let sub: u8[2] = [41, 202];
  if (elf.append_elf_bytes(ctx, sub, 2) != 0) { return -1; }
  let mov: u8[2] = [137, 209];
  return elf.append_elf_bytes(ctx, mov, 2);
}

/** Exported function `enc_rsub_ebx_edx`.
 * Implements `enc_rsub_ebx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rsub_ebx_edx(ctx: *ElfCodegenCtx): i32 {
  /* See implementation. */
  let sub: u8[2] = [41, 218];
  if (elf.append_elf_bytes(ctx, sub, 2) != 0) { return -1; }
  let mov: u8[2] = [137, 211];
  return elf.append_elf_bytes(ctx, mov, 2);
}

/** Exported function `enc_imul_imm_to_ecx`.
 * Implements `enc_imul_imm_to_ecx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_imul_imm_to_ecx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm <= 1) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [107, 201, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [105, 201, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_imul_imm_to_ebx`.
 * Implements `enc_imul_imm_to_ebx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_imul_imm_to_ebx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm <= 1) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [107, 219, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [105, 219, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_add_imm_to_ebx_index`.
 * Implements `enc_add_imm_to_ebx_index`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_ebx_index(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [131, 195, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [129, 195, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_sub_imm_from_ebx_index`.
 * Implements `enc_sub_imm_from_ebx_index`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_sub_imm_from_ebx_index(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  if (imm >= -128 && imm <= 127) {
    let buf: u8[3] = [131, 235, 0];
    buf[2] = elf.elf_to_u8(imm);
    return elf.append_elf_bytes(ctx, buf, 3);
  }
  let buf: u8[6] = [129, 235, 0, 0, 0, 0];
  buf[2] = elf.elf_to_u8(imm);
  buf[3] = elf.elf_to_u8(imm >> 8);
  buf[4] = elf.elf_to_u8(imm >> 16);
  buf[5] = elf.elf_to_u8(imm >> 24);
  return elf.append_elf_bytes(ctx, buf, 6);
}

/** Exported function `enc_add_ebx_edx`.
 * Implements `enc_add_ebx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_add_ebx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [1, 211];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/** Exported function `enc_sub_ebx_edx`.
 * Implements `enc_sub_ebx_edx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_ebx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[2] = [41, 211];
  return elf.append_elf_bytes(ctx, buf, 2);
}

/**
 * Emit IMUL ecx, edx (ecx = ecx * edx). Index-scratch primary *= secondary.
 * Wave184: ModRM 0xCA (was 0xD1 product-in-edx bug).
 * @param ctx *ElfCodegenCtx
 * @return i32
 * PLATFORM: SHARED x86_64 SysV.
 */
export function enc_imul_ecx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [15, 175, 202];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/**
 * Emit IMUL ebx, edx (ebx = ebx * edx). INDEX rvalue primary rbx *= secondary.
 * Wave184: ModRM 0xDA (was 0xD3 product-in-edx bug; scale uses rbx).
 * @param ctx *ElfCodegenCtx
 * @return i32
 * PLATFORM: SHARED x86_64 SysV.
 */
export function enc_imul_ebx_edx(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [15, 175, 218];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_load_64_from_rax`.
 * Implements `enc_load_64_from_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_load_64_from_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 139, 0];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_store_rax_to_rbx_offset`.
 * Implements `enc_store_rax_to_rbx_offset`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @param store_size i32
 * @return i32
 */
export function enc_store_rax_to_rbx_offset(ctx: *ElfCodegenCtx, offset: i32, store_size: i32): i32 {
  if (store_size == 1) {
    let buf: u8[6] = [136, 131, 0, 0, 0, 0];
    buf[2] = elf.elf_to_u8(offset);
    buf[3] = elf.elf_to_u8(offset >> 8);
    buf[4] = elf.elf_to_u8(offset >> 16);
    buf[5] = elf.elf_to_u8(offset >> 24);
    return elf.append_elf_bytes(ctx, buf, 6);
  }
  if (store_size == 4) {
    let buf: u8[6] = [137, 131, 0, 0, 0, 0];
    buf[2] = elf.elf_to_u8(offset);
    buf[3] = elf.elf_to_u8(offset >> 8);
    buf[4] = elf.elf_to_u8(offset >> 16);
    buf[5] = elf.elf_to_u8(offset >> 24);
    return elf.append_elf_bytes(ctx, buf, 6);
  }
  let buf: u8[7] = [72, 137, 131, 0, 0, 0, 0];
  buf[3] = elf.elf_to_u8(offset);
  buf[4] = elf.elf_to_u8(offset >> 8);
  buf[5] = elf.elf_to_u8(offset >> 16);
  buf[6] = elf.elf_to_u8(offset >> 24);
  return elf.append_elf_bytes(ctx, buf, 7);
}

/** movq %rbx, %rax。 */
export function enc_mov_rbx_to_rax(ctx: *ElfCodegenCtx): i32 {
  let buf: u8[3] = [72, 137, 216];
  return elf.append_elf_bytes(ctx, buf, 3);
}

/** Exported function `enc_jz`.
 * Implements `enc_jz`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jz(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  let buf: u8[6] = [15, 132, 0, 0, 0, 0];
  if (elf.append_elf_bytes(ctx, buf, 6) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_jeq`.
 * Implements `enc_jeq`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jeq(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  return enc_jz(ctx, label, label_len);
}

/** Exported function `enc_jge`.
 * Implements `enc_jge`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jge(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  let buf: u8[6] = [15, 141, 0, 0, 0, 0];
  if (elf.append_elf_bytes(ctx, buf, 6) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_jle`.
 * Implements `enc_jle`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jle(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  let buf: u8[6] = [15, 142, 0, 0, 0, 0];
  if (elf.append_elf_bytes(ctx, buf, 6) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_jl`.
 * Implements `enc_jl`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jl(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  let buf: u8[6] = [15, 140, 0, 0, 0, 0];
  if (elf.append_elf_bytes(ctx, buf, 6) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_jnz`.
 * Implements `enc_jnz`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jnz(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  let buf: u8[6] = [15, 133, 0, 0, 0, 0];
  if (elf.append_elf_bytes(ctx, buf, 6) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_jmp`.
 * Implements `enc_jmp`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jmp(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  if (enc_u8(ctx, 233) != 0) { return -1; }
  if (enc_u32_le(ctx, 0) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch(ctx, rel32_at, label, label_len);
}

/** Exported function `enc_mov_rax_to_arg_reg`.
 * Implements `enc_mov_rax_to_arg_reg`.
 * @param ctx *ElfCodegenCtx
 * @param k i32
 * @return i32
 */
export function enc_mov_rax_to_arg_reg(ctx: *ElfCodegenCtx, k: i32): i32 {
  let idx: i32 = k;
  if (idx < 0) { idx = 0; }
  if (idx > 5) { idx = 5; }
  /* See implementation. */
  if (idx == 0) {
    let b0: u8[3] = [72, 137, 199];
    return elf.append_elf_bytes(ctx, b0, 3);
  }
  if (idx == 1) {
    let b1: u8[3] = [72, 137, 198];
    return elf.append_elf_bytes(ctx, b1, 3);
  }
  if (idx == 2) {
    let b2: u8[3] = [72, 137, 194];
    return elf.append_elf_bytes(ctx, b2, 3);
  }
  if (idx == 3) {
    /* See implementation. */
    let b3: u8[3] = [72, 137, 193];
    return elf.append_elf_bytes(ctx, b3, 3);
  }
  if (idx == 4) {
    let b4: u8[3] = [73, 137, 192];
    return elf.append_elf_bytes(ctx, b4, 3);
  }
  let b5: u8[3] = [73, 137, 193];
  return elf.append_elf_bytes(ctx, b5, 3);
}

/** Exported function `enc_add_rsp_imm`.
 * Implements `enc_add_rsp_imm`.
 * @param ctx *ElfCodegenCtx
 * @param nbytes i32
 * @return i32
 */
export function enc_add_rsp_imm(ctx: *ElfCodegenCtx, nbytes: i32): i32 {
  if (nbytes <= 0) {
    return 0;
  }
  if (nbytes <= 127) {
    if (enc_u8(ctx, 72) != 0) { return -1; }
    if (enc_u8(ctx, 131) != 0) { return -1; }
    if (enc_u8(ctx, 196) != 0) { return -1; }
    return enc_u8(ctx, nbytes);
  }
  /** addq $imm32, %rsp → 48 81 C4 imm32 */
  if (enc_u8(ctx, 72) != 0) { return -1; }
  if (enc_u8(ctx, 129) != 0) { return -1; }
  if (enc_u8(ctx, 196) != 0) { return -1; }
  return enc_u32_le(ctx, nbytes);
}

/** Exported function `enc_call`.
 * Implements `enc_call`.
 * @param ctx *ElfCodegenCtx
 * @param name u8[128]
 * @param name_len i32
 * @return i32
 */
export function enc_call(ctx: *ElfCodegenCtx, name: u8[128], name_len: i32): i32 {
  /* See implementation. */
  if (name_len <= 0) {
    return -1;
  }
  if (enc_u8(ctx, 232) != 0) { return -1; }
  if (enc_u32_le(ctx, 0) != 0) { return -1; }
  let rel32_at: i32 = ctx.code_len - 4;
/** See implementation for details. */
  // PLATFORM: MACOS|DARWIN — always prepend '_' for C call names.
  // Must not skip when name[0]=='_' (__error → ___error). Stage 12.0.5 ABI.
  if (ctx.macho_leading_underscore != 0 && name_len > 0 && name_len <= 127) {
    let rn: u8[128] = [];
    rn[0] = 95;
    let k: i32 = 0;
    while (k < name_len && k < 127) {
      rn[k + 1] = name[k];
      k = k + 1;
    }
    return elf.elf_add_reloc(ctx, rel32_at, &rn[0], name_len + 1);
  }
  return elf.elf_add_reloc(ctx, rel32_at, &name[0], name_len);
}

/** Exported function `enc_label`.
 * Implements `enc_label`.
 * @param ctx *ElfCodegenCtx
 * @param name *u8
 * @param name_len i32
 * @param is_func i32
 * @return i32
 */
export function enc_label(ctx: *ElfCodegenCtx, name: *u8, name_len: i32, is_func: i32): i32 {
  if (is_func != 0) {
    if (elf.elf_pad_code_to_4(ctx) != 0) { return -1; }
  }
  if (elf.elf_add_label(ctx, name, name_len) != 0) { return -1; }
  if (is_func != 0) {
    if (ctx.macho_leading_underscore != 0) {
      let mn: u8[128] = [];
      mn[0] = 95;
      let k: i32 = 0;
      while (k < name_len && k < 63) {
        mn[k + 1] = name[k];
        k = k + 1;
      }
      return elf.elf_add_sym(ctx, mn, name_len + 1, elf.elf_section_code_len(ctx));
    }
    return elf.elf_add_sym(ctx, name, name_len, elf.elf_section_code_len(ctx));
  }
  return 0;
}
