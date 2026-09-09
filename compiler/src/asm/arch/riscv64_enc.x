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
// reloc、elf_add_sym、elf_to_u8）。

const elf = import("platform.elf");

/** Exported function `enc_u32_le`.
 * Implements `enc_u32_le`.
 * @param ctx *ElfCodegenCtx
 * @param val i64
 * @return i32
 */
export function enc_u32_le(ctx: *ElfCodegenCtx, val: i64): i32 {
  let buf: u8[4] = [];
  buf[0] = elf.elf_u32_byte_at(val, 0);
  buf[1] = elf.elf_u32_byte_at(val, 1);
  buf[2] = elf.elf_u32_byte_at(val, 2);
  buf[3] = elf.elf_u32_byte_at(val, 3);
  return elf.append_elf_bytes(ctx, buf, 4);
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
    return elf.elf_add_sym(ctx, name, name_len, elf.elf_section_code_len(ctx));
  }
  return 0;
}

/** Exported function `enc_prologue`.
 * Implements `enc_prologue`.
 * @param ctx *ElfCodegenCtx
 * @param frame_sz i32
 * @return i32
 */
export function enc_prologue(ctx: *ElfCodegenCtx, frame_sz: i32): i32 {
  let sz: i32 = frame_sz;
  if (sz < 16) { sz = 16; }
  if (frame_sz >= 16) { ctx.current_frame_size = sz | 4096; } else { ctx.current_frame_size = sz; }
  let imm12: i32 = 0 - sz;
  imm12 = imm12 & 4095;
  if (enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (imm12 << 20)) != 0) { return -1; }
  let off_ra: i32 = sz - 8;
  let imm_lo: i32 = off_ra & 31;
  let imm_hi: i32 = (off_ra >> 5) & 127;
  if (enc_u32_le(ctx, 35 | (imm_lo << 7) | (3 << 12) | (2 << 15) | (1 << 20) | (imm_hi << 25)) !=
  0) { return -1; }
  if (frame_sz < 16) { return 0; }
  let off_s0: i32 = sz - 16;
  imm_lo = off_s0 & 31;
  imm_hi = (off_s0 >> 5) & 127;
  if (enc_u32_le(ctx, 35 | (imm_lo << 7) | (3 << 12) | (2 << 15) | (8 << 20) | (imm_hi << 25)) !=
  0) { return -1; }
  imm12 = sz & 4095;
  return enc_u32_le(ctx, 19 | (8 << 7) | (0 << 12) | (2 << 15) | (imm12 << 20));
}

/** Exported function `enc_epilogue`.
 * Implements `enc_epilogue`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_epilogue(ctx: *ElfCodegenCtx): i32 {
  let saved_s0: i32 = (ctx.current_frame_size & 4096) >> 12;
  let frame_sz: i32 = ctx.current_frame_size & 4095;
  if (frame_sz == 0) { frame_sz = 16; }
  if (saved_s0 != 0) {
    let off_s0: i32 = frame_sz - 16;
    let imm12: i32 = off_s0 & 4095;
    if (enc_u32_le(ctx, 3 | (8 << 7) | (3 << 12) | (2 << 15) | (imm12 << 20)) != 0) { return -1; }
  }
  let off_ra: i32 = frame_sz - 8;
  let imm12: i32 = off_ra & 4095;
  if (enc_u32_le(ctx, 3 | (1 << 7) | (3 << 12) | (2 << 15) | (imm12 << 20)) != 0) { return -1; }
  imm12 = frame_sz & 4095;
  if (enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (imm12 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 103 | (0 << 7) | (0 << 12) | (1 << 15) | (0 << 20));
}

/** Exported function `enc_ret_imm32`.
 * Implements `enc_ret_imm32`.
 * @param ctx *ElfCodegenCtx
 * @param imm32 i32
 * @return i32
 */
export function enc_ret_imm32(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  let imm12: i32 = imm32 & 4095;
  if (imm32 >= 2048 && imm32 < 4096) { imm12 = imm32; }
  if (imm32 >= 0 && imm32 < 4096) {
    return enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (0 << 15) | (imm12 << 20));
  }
  let hi20: i32 = (imm32 >> 12) & 1048575;
  if ((imm32 & 2048) != 0) { hi20 = hi20 + 1; }
  if (enc_u32_le(ctx, 55 | (10 << 7) | (hi20 << 12)) != 0) { return -1; }
  imm12 = imm32 & 4095;
  return enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (10 << 15) | (imm12 << 20));
}

/** li a1, imm32。 */
export function enc_mov_imm32_to_rbx(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  let imm12: i32 = imm32 & 4095;
  if (imm32 >= 0 && imm32 < 4096) {
    return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (0 << 15) | (imm12 << 20));
  }
  let hi20: i32 = (imm32 >> 12) & 1048575;
  if ((imm32 & 2048) != 0) { hi20 = hi20 + 1; }
  if (enc_u32_le(ctx, 55 | (11 << 7) | (hi20 << 12)) != 0) { return -1; }
  imm12 = imm32 & 4095;
  return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (11 << 15) | (imm12 << 20));
}

/** Exported function `enc_mov_imm64_to_rax`.
 * Implements `enc_mov_imm64_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param lo i32
 * @param hi i32
 * @return i32
 */
export function enc_mov_imm64_to_rax(ctx: *ElfCodegenCtx, lo: i32, hi: i32): i32 {
  let imm12: i32 = lo & 4095;
  if (enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (0 << 15) | (imm12 << 20)) != 0) { return -1; }
  if (hi == 0) { return 0; }
  if (enc_u32_le(ctx, 19 | (10 << 7) | (1 << 12) | (10 << 15) | (32 << 20)) != 0) { return -1; }
  if (enc_u32_le(ctx, 19 | (10 << 7) | (5 << 12) | (10 << 15) | (32 << 20)) != 0) { return -1; }
  let hi20: i32 = (hi >> 12) & 1048575;
  if ((hi & 2048) != 0) { hi20 = hi20 + 1; }
  if (enc_u32_le(ctx, 55 | (5 << 7) | (hi20 << 12)) != 0) { return -1; }
  imm12 = hi & 4095;
  if (enc_u32_le(ctx, 19 | (5 << 7) | (0 << 12) | (5 << 15) | (imm12 << 20)) != 0) { return -1; }
  if (enc_u32_le(ctx, 19 | (5 << 7) | (1 << 12) | (5 << 15) | (32 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (5 << 20));
}

/** addi sp, sp, -16; sd a0, 0(sp)。 */
export function enc_push_rax(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (4080 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 35 | (0 << 7) | (3 << 12) | (2 << 15) | (10 << 20) | (0 << 25));
}

/** addi sp, sp, -16; sd a1, 0(sp)。 */
export function enc_push_rbx(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (4080 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 35 | (0 << 7) | (3 << 12) | (2 << 15) | (11 << 20) | (0 << 25));
}

/** ld a1, 0(sp); addi sp, sp, 16。 */
export function enc_pop_rbx(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 3 | (11 << 7) | (3 << 12) | (2 << 15) | (0 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (16 << 20));
}

/** ld a0, 0(sp); addi sp, sp, 16。 */
export function enc_pop_rax(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 3 | (10 << 7) | (3 << 12) | (2 << 15) | (0 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (16 << 20));
}

/** add a0, a0, a1。 */
export function enc_add_rax_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20));
}

/** Exported function `enc_sub_rbx_rax_then_mov`.
 * Implements `enc_sub_rbx_rax_then_mov`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_rbx_rax_then_mov(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (11 << 15) | (10 << 20) | (64 << 25));
}

/** Exported function `enc_sub_rax_rbx`.
 * Implements `enc_sub_rax_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_rax_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20) | (64 << 25));
}

/** mul a0, a0, a1。 */
export function enc_imul_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20) | (1 << 25));
}

/** mv a1, a0。addi a1, a0, 0。 */
export function enc_mov_rax_to_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (10 << 15) | (0 << 20));
}

/** not a0, a0。xori a0, a0, -1。 */
export function enc_not_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 19 | (10 << 7) | (4 << 12) | (10 << 15) | (4095 << 20));
}

/** and a0, a1, a0。 */
export function enc_and_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (7 << 12) | (11 << 15) | (10 << 20));
}

/** or a0, a1, a0。 */
export function enc_or_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (6 << 12) | (11 << 15) | (10 << 20));
}

/** xor a0, a1, a0。 */
export function enc_xor_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (4 << 12) | (11 << 15) | (10 << 20));
}

/** Exported function `enc_mov_rbx_to_ecx`.
 * Implements `enc_mov_rbx_to_ecx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_mov_rbx_to_ecx(ctx: *ElfCodegenCtx): i32 {
  return 0;
}

/** sll a0, a0, a1。 */
export function enc_shl_cl_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (1 << 12) | (10 << 15) | (11 << 20));
}

/** srl a0, a0, a1。 */
export function enc_shr_cl_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (5 << 12) | (10 << 15) | (11 << 20));
}

/** sra a0, a0, a1。 */
export function enc_sar_cl_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (5 << 12) | (10 << 15) | (11 << 20) | (64 << 25));
}

/** no-op。 */
export function enc_cltd(ctx: *ElfCodegenCtx): i32 {
  return 0;
}

/** div a0, a0, a1。 */
export function enc_idiv_rbx(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (4 << 12) | (10 << 15) | (11 << 20) | (1 << 25));
}

/** Exported function `enc_mov_edx_to_eax`.
 * Implements `enc_mov_edx_to_eax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_mov_edx_to_eax(ctx: *ElfCodegenCtx): i32 {
  return 0;
}

/** neg a0, a0。sub a0, x0, a0。 */
export function enc_neg_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (0 << 15) | (10 << 20) | (64 << 25));
}

/** Exported function `enc_test_eax_eax`.
 * Implements `enc_test_eax_eax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_test_eax_eax(ctx: *ElfCodegenCtx): i32 {
  return 0;
}

/** Exported function `enc_test_rbx_rbx`.
 * Implements `enc_test_rbx_rbx`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_test_rbx_rbx(ctx: *ElfCodegenCtx): i32 {
  return 0;
}

/** seqz a0, a0。sltiu a0, a0, 1。 */
export function enc_setz_movzbl_eax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 19 | (10 << 7) | (3 << 12) | (10 << 15) | (1 << 20));
}

/** Exported function `enc_cmp_rbx_rax`.
 * Comparison/utility `enc_cmp_rbx_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_cmp_rbx_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (11 << 15) | (10 << 20) | (64 << 25));
}

/** Exported function `enc_cmp_setcc_movzbl`.
 * Comparison/utility `enc_cmp_setcc_movzbl`.
 * @param ctx *ElfCodegenCtx
 * @param cc i32
 * @return i32
 */
export function enc_cmp_setcc_movzbl(ctx: *ElfCodegenCtx, cc: i32): i32 {
  let c: i32 = cc;
  if (c < 0) { c = 0; }
  if (c > 9) { c = 5; }
  if (c == 0) { return enc_u32_le(ctx, 19 | (10 << 7) | (3 << 12) | (10 << 15) | (1 << 20)); }
  if (c == 1) { return enc_u32_le(ctx, 51 | (10 << 7) | (3 << 12) | (0 << 15) | (10 << 20)); }
  if (c == 2) { return enc_u32_le(ctx, 51 | (10 << 7) | (2 << 12) | (11 << 15) | (10 << 20)); }
  if (c == 3) {
    if (enc_u32_le(ctx, 51 | (10 << 7) | (2 << 12) | (10 << 15) | (11 << 20)) != 0) { return -1; }
    return enc_u32_le(ctx, 19 | (10 << 7) | (4 << 12) | (10 << 15) | (1 << 20));
  }
  if (c == 4) { return enc_u32_le(ctx, 51 | (10 << 7) | (2 << 12) | (10 << 15) | (11 << 20)); }
  if (c == 5) {
    if (enc_u32_le(ctx, 51 | (10 << 7) | (2 << 12) | (11 << 15) | (10 << 20)) != 0) { return -1; }
    return enc_u32_le(ctx, 19 | (10 << 7) | (4 << 12) | (10 << 15) | (1 << 20));
  }
  // Unsigned 6..9: sltu (funct3=3) instead of slt (funct3=2).
  if (c == 6) { return enc_u32_le(ctx, 51 | (10 << 7) | (3 << 12) | (11 << 15) | (10 << 20)); }
  if (c == 7) {
    if (enc_u32_le(ctx, 51 | (10 << 7) | (3 << 12) | (10 << 15) | (11 << 20)) != 0) { return -1; }
    return enc_u32_le(ctx, 19 | (10 << 7) | (4 << 12) | (10 << 15) | (1 << 20));
  }
  if (c == 8) { return enc_u32_le(ctx, 51 | (10 << 7) | (3 << 12) | (10 << 15) | (11 << 20)); }
  if (enc_u32_le(ctx, 51 | (10 << 7) | (3 << 12) | (11 << 15) | (10 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 19 | (10 << 7) | (4 << 12) | (10 << 15) | (1 << 20));
}

/** sd a0, -offset(s0)。S-type imm = -offset。 */
export function enc_store_rax_to_rbp(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm: i32 = 0 - offset;
  imm = imm & 4095;
  let imm_lo: i32 = imm & 31;
  let imm_hi: i32 = (imm >> 5) & 127;
  return enc_u32_le(ctx, 35 | (imm_lo << 7) | (3 << 12) | (8 << 15) | (10 << 20) | (imm_hi << 25));
}

/** ld a0, -offset(s0)。 */
export function enc_load_rbp_to_rax(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm: i32 = 0 - offset;
  imm = imm & 4095;
  return enc_u32_le(ctx, 3 | (10 << 7) | (3 << 12) | (8 << 15) | (imm << 20));
}

/** Exported function `enc_load_rbp_to_rbx`.
 * Implements `enc_load_rbp_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_rbx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm: i32 = 0 - offset;
  imm = imm & 4095;
  return enc_u32_le(ctx, 3 | (11 << 7) | (3 << 12) | (8 << 15) | (imm << 20));
}

/** Exported function `enc_li_a2_imm32`.
 * Implements `enc_li_a2_imm32`.
 * @param ctx *ElfCodegenCtx
 * @param imm32 i32
 * @return i32
 */
export function enc_li_a2_imm32(ctx: *ElfCodegenCtx, imm32: i32): i32 {
  let imm12: i32 = imm32 & 4095;
  if (imm32 >= 0 && imm32 < 4096) {
    return enc_u32_le(ctx, 19 | (12 << 7) | (0 << 12) | (0 << 15) | (imm12 << 20));
  }
  let hi20: i32 = (imm32 >> 12) & 1048575;
  if ((imm32 & 2048) != 0) {
    hi20 = hi20 + 1;
  }
  if (enc_u32_le(ctx, 55 | (12 << 7) | (hi20 << 12)) != 0) {
    return -1;
  }
  imm12 = imm32 & 4095;
  return enc_u32_le(ctx, 19 | (12 << 7) | (0 << 12) | (12 << 15) | (imm12 << 20));
}

/**
* See implementation.
*/
export function enc_memset_rbp_zero(ctx: *ElfCodegenCtx, rbp_off: i32, nbytes: i32): i32 {
  if (nbytes <= 0) {
    return 0;
  }
  if (enc_lea_rbp_to_rax(ctx, rbp_off) != 0) {
    return -1;
  }
  if (enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (0 << 15) | (0 << 20)) != 0) {
    return -1;
  }
  if (enc_li_a2_imm32(ctx, nbytes) != 0) {
    return -1;
  }
  let memset_nm: u8[128] = [109, 101, 109, 115, 101, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  return enc_call(ctx, memset_nm, 6);
}

/** Exported function `enc_lea_rbp_to_rax`.
 * Implements `enc_lea_rbp_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_lea_rbp_to_rax(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm12: i32 = 0 - offset;
  imm12 = imm12 & 4095;
  return enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (8 << 15) | (imm12 << 20));
}

/** Exported function `enc_lea_rbp_to_rbx`.
 * Implements `enc_lea_rbp_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_lea_rbp_to_rbx(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm12: i32 = 0 - offset;
  imm12 = imm12 & 4095;
  return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (8 << 15) | (imm12 << 20));
}

/** Exported function `enc_rax_plus_rbx_scale1`.
 * Implements `enc_rax_plus_rbx_scale1`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale1(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20));
}

/** Exported function `enc_rax_plus_rbx_scale4`.
 * Implements `enc_rax_plus_rbx_scale4`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale4(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (11 << 7) | (1 << 12) | (11 << 15) | (2 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20));
}

/** Exported function `enc_rax_plus_rbx_scale8`.
 * Implements `enc_rax_plus_rbx_scale8`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rax_plus_rbx_scale8(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (11 << 7) | (1 << 12) | (11 << 15) | (3 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (10 << 7) | (0 << 12) | (10 << 15) | (11 << 20));
}

/** Exported function `enc_store_rax_to_rbx_indirect`.
 * Implements `enc_store_rax_to_rbx_indirect`.
 * @param ctx *ElfCodegenCtx
 * @param elem_sz i32
 * @return i32
 */
export function enc_store_rax_to_rbx_indirect(ctx: *ElfCodegenCtx, elem_sz: i32): i32 {
  let imm_lo: i32 = 0;
  let imm_hi: i32 = 0;
  if (elem_sz == 1) {
    return enc_u32_le(ctx, 35 | (imm_lo << 7) | (0 << 12) | (11 << 15) | (10 << 20) | (imm_hi <<
    25));
  }
  if (elem_sz == 4) {
    return enc_u32_le(ctx, 35 | (imm_lo << 7) | (2 << 12) | (11 << 15) | (10 << 20) | (imm_hi <<
    25));
  }
  return enc_u32_le(ctx, 35 | (imm_lo << 7) | (3 << 12) | (11 << 15) | (10 << 20) | (imm_hi << 25));
}

/** lw a0, 0(a0)。 */
export function enc_load_32_from_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 3 | (10 << 7) | (2 << 12) | (10 << 15) | (0 << 20));
}

/** Exported function `enc_load_zext8_from_rax`.
 * Implements `enc_load_zext8_from_rax`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_load_zext8_from_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 3 | (10 << 7) | (4 << 12) | (10 << 15) | (0 << 20));
}

/** Exported function `enc_add_imm_to_rax`.
 * Implements `enc_add_imm_to_rax`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_rax(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  let imm12: i32 = imm & 4095;
  return enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (10 << 15) | (imm12 << 20));
}

/** Exported function `enc_add_imm_to_rbx`.
 * Implements `enc_add_imm_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_rbx(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  let imm12: i32 = imm & 4095;
  return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (11 << 15) | (imm12 << 20));
}

/** Exported function `enc_load_rbp_to_a2`.
 * Implements `enc_load_rbp_to_a2`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_a2(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm: i32 = 0 - offset;
  imm = imm & 4095;
  return enc_u32_le(ctx, 3 | (12 << 7) | (2 << 12) | (8 << 15) | (imm << 20));
}

/** Exported function `enc_rbx_plus_a2_scale1`.
 * Implements `enc_rbx_plus_a2_scale1`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rbx_plus_a2_scale1(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (12 << 20));
}

/** Exported function `enc_rbx_plus_a2_scale4`.
 * Implements `enc_rbx_plus_a2_scale4`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rbx_plus_a2_scale4(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (12 << 7) | (1 << 12) | (12 << 15) | (2 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (12 << 20));
}

/** Exported function `enc_rbx_plus_a2_scale8`.
 * Implements `enc_rbx_plus_a2_scale8`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rbx_plus_a2_scale8(ctx: *ElfCodegenCtx): i32 {
  if (enc_u32_le(ctx, 19 | (12 << 7) | (1 << 12) | (12 << 15) | (3 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (12 << 20));
}

/** Exported function `enc_add_imm_to_a2`.
 * Implements `enc_add_imm_to_a2`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_add_imm_to_a2(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  let imm12: i32 = imm & 4095;
  return enc_u32_le(ctx, 19 | (12 << 7) | (0 << 12) | (12 << 15) | (imm12 << 20));
}

/** Exported function `enc_load_rbp_to_a3`.
 * Implements `enc_load_rbp_to_a3`.
 * @param ctx *ElfCodegenCtx
 * @param offset i32
 * @return i32
 */
export function enc_load_rbp_to_a3(ctx: *ElfCodegenCtx, offset: i32): i32 {
  let imm: i32 = 0 - offset;
  imm = imm & 4095;
  return enc_u32_le(ctx, 3 | (13 << 7) | (2 << 12) | (8 << 15) | (imm << 20));
}

/** Exported function `enc_add_a2_a3`.
 * Implements `enc_add_a2_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_add_a2_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (12 << 7) | (0 << 12) | (12 << 15) | (13 << 20));
}

/** Exported function `enc_sub_imm_from_a2`.
 * Implements `enc_sub_imm_from_a2`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_sub_imm_from_a2(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  let neg: i32 = 0 - imm;
  let imm12: i32 = neg & 4095;
  return enc_u32_le(ctx, 19 | (12 << 7) | (0 << 12) | (12 << 15) | (imm12 << 20));
}

/** Exported function `enc_sub_a2_a3`.
 * Implements `enc_sub_a2_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_a2_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (12 << 7) | (0 << 12) | (12 << 15) | (13 << 20) | (64 << 25));
}

/** sub a2, a3, a2（INDEX scratch = a3 - a2，i-(j+k)）。 */
export function enc_rsub_a2_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (12 << 7) | (0 << 12) | (13 << 15) | (12 << 20) | (64 << 25));
}

/** Exported function `enc_rsub_rbx_a3`.
 * Implements `enc_rsub_rbx_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_rsub_rbx_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (13 << 15) | (11 << 20) | (64 << 25));
}

/** Exported function `enc_mul_imm_to_a2`.
 * Implements `enc_mul_imm_to_a2`.
 * @param ctx *ElfCodegenCtx
 * @param lit i32
 * @return i32
 */
export function enc_mul_imm_to_a2(ctx: *ElfCodegenCtx, lit: i32): i32 {
  if (lit <= 1) { return 0; }
  let imm12: i32 = lit & 4095;
  if (enc_u32_le(ctx, 19 | (13 << 7) | (0 << 12) | (13 << 15) | (imm12 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (12 << 7) | (0 << 12) | (12 << 15) | (13 << 20) | (1 << 25));
}

/** Exported function `enc_mul_imm_to_rbx`.
 * Implements `enc_mul_imm_to_rbx`.
 * @param ctx *ElfCodegenCtx
 * @param lit i32
 * @return i32
 */
export function enc_mul_imm_to_rbx(ctx: *ElfCodegenCtx, lit: i32): i32 {
  if (lit <= 1) { return 0; }
  let imm12: i32 = lit & 4095;
  if (enc_u32_le(ctx, 19 | (13 << 7) | (0 << 12) | (13 << 15) | (imm12 << 20)) != 0) { return -1; }
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (13 << 20) | (1 << 25));
}

/** Exported function `enc_sub_imm_from_rbx_index`.
 * Implements `enc_sub_imm_from_rbx_index`.
 * @param ctx *ElfCodegenCtx
 * @param imm i32
 * @return i32
 */
export function enc_sub_imm_from_rbx_index(ctx: *ElfCodegenCtx, imm: i32): i32 {
  if (imm == 0) { return 0; }
  let neg: i32 = 0 - imm;
  let imm12: i32 = neg & 4095;
  return enc_u32_le(ctx, 19 | (11 << 7) | (0 << 12) | (11 << 15) | (imm12 << 20));
}

/** Exported function `enc_add_rbx_a3`.
 * Implements `enc_add_rbx_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_add_rbx_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (13 << 20));
}

/** Exported function `enc_sub_rbx_a3`.
 * Implements `enc_sub_rbx_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_sub_rbx_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (13 << 20) | (64 << 25));
}

/** Exported function `enc_mul_a2_a3`.
 * Implements `enc_mul_a2_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_mul_a2_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (12 << 7) | (0 << 12) | (12 << 15) | (13 << 20) | (1 << 25));
}

/** Exported function `enc_mul_rbx_a3`.
 * Implements `enc_mul_rbx_a3`.
 * @param ctx *ElfCodegenCtx
 * @return i32
 */
export function enc_mul_rbx_a3(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 51 | (11 << 7) | (0 << 12) | (11 << 15) | (13 << 20) | (1 << 25));
}

/** ld a0, 0(a0)。 */
export function enc_load_64_from_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 3 | (10 << 7) | (3 << 12) | (10 << 15) | (0 << 20));
}

/** sw/sd a0, offset(a1)。 */
export function enc_store_rax_to_rbx_offset(ctx: *ElfCodegenCtx, offset: i32, store_size: i32): i32 {
  let imm: i32 = offset & 4095;
  let imm_lo: i32 = imm & 31;
  let imm_hi: i32 = (imm >> 5) & 127;
  if (store_size == 4) {
    return enc_u32_le(ctx, 35 | (imm_lo << 7) | (2 << 12) | (11 << 15) | (10 << 20) | (imm_hi <<
    25));
  }
  return enc_u32_le(ctx, 35 | (imm_lo << 7) | (3 << 12) | (11 << 15) | (10 << 20) | (imm_hi << 25));
}

/** mv a0, a1。 */
export function enc_mov_rbx_to_rax(ctx: *ElfCodegenCtx): i32 {
  return enc_u32_le(ctx, 19 | (10 << 7) | (0 << 12) | (11 << 15) | (0 << 20));
}

/** Exported function `enc_jz`.
 * Implements `enc_jz`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jz(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  if (enc_u32_le(ctx, 99 | (0 << 12) | (10 << 15) | (0 << 20)) != 0) { return -1; }
  let at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch_with_bits(ctx, at, label, label_len, 13);
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
  if (enc_u32_le(ctx, 99 | (5 << 12) | (11 << 15) | (10 << 20)) != 0) { return -1; }
  let at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch_with_bits(ctx, at, label, label_len, 13);
}

/** Exported function `enc_jnz`.
 * Implements `enc_jnz`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jnz(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  if (enc_u32_le(ctx, 99 | (1 << 12) | (10 << 15) | (0 << 20)) != 0) { return -1; }
  let at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch_with_bits(ctx, at, label, label_len, 13);
}

/** Exported function `enc_jmp`.
 * Implements `enc_jmp`.
 * @param ctx *ElfCodegenCtx
 * @param label *u8
 * @param label_len i32
 * @return i32
 */
export function enc_jmp(ctx: *ElfCodegenCtx, label: *u8, label_len: i32): i32 {
  if (enc_u32_le(ctx, 111 | (0 << 7)) != 0) { return -1; }
  let at: i32 = ctx.code_len - 4;
  if (elf.elf_ensure_label_slot(ctx, label, label_len) != 0) { return -1; }
  return elf.elf_add_patch_with_bits(ctx, at, label, label_len, 21);
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
  if (idx > 7) { idx = 7; }
  if (idx == 0) { return 0; }
  let rd: i32 = 10 + idx;
  return enc_u32_le(ctx, 19 | (rd << 7) | (0 << 12) | (10 << 15) | (0 << 20));
}

/** Exported function `enc_add_sp_imm12`.
 * Implements `enc_add_sp_imm12`.
 * @param ctx *ElfCodegenCtx
 * @param nbytes i32
 * @return i32
 */
export function enc_add_sp_imm12(ctx: *ElfCodegenCtx, nbytes: i32): i32 {
  if (nbytes <= 0) {
    return 0;
  }
  let imm12: i32 = nbytes & 4095;
  return enc_u32_le(ctx, 19 | (2 << 7) | (0 << 12) | (2 << 15) | (imm12 << 20));
}

/** Exported function `enc_call`.
 * Implements `enc_call`.
 * @param ctx *ElfCodegenCtx
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
export function enc_call(ctx: *ElfCodegenCtx, name: *u8, name_len: i32): i32 {
  if (name_len <= 0) {
    return -1;
  }
  if (enc_u32_le(ctx, 111 | (1 << 7)) != 0) { return -1; }
  let at: i32 = ctx.code_len - 4;
  return elf.elf_add_reloc(ctx, at, &name[0], name_len);
}
