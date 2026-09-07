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
// backend.x — asm backend: AST traversal, lowering dispatch, arch dispatch.
//
// Responsibility: CodegenOutBuf + AsmFuncCtx usage; dispatch AST nodes to
// arch-specific emit (x86_64/arm64); entry point asm_codegen_ast.
// Dependencies: ast (Module/ASTArena/Func, PipelineDepCtx), codegen
// (CodegenOutBuf), types, x86_64, arm64, elf, arch.x86_64_enc (.o paths).
// Future (7.3): simple register allocation to reduce fixed rax/rbx push/pop;
// peephole to merge adjacent mov/arith.


const ast = import("ast");
const codegen_outbuf_abi = import("codegen_outbuf_abi");
const types = import("asm.types");
const x86_64 = import("arch.x86_64");
const arm64 = import("arch.arm64");
const riscv64 = import("arch.riscv64");
const elf = import("platform.elf");
const backend_enc_dispatch = import("backend_enc_dispatch");

// See implementation.
// See implementation.
export extern "C" function enc_dispatch_backend_enc_add_imm_to_rax_arch(elf_ctx: *u8, imm: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_add_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_and_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_call_arch(elf_ctx: *u8, name: *u8, name_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cltd_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cmp_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cmp_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cmp_setcc_movzbl_arch(elf_ctx: *u8, cc: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cmp_w0_imm12_arch(elf_ctx: *u8, imm12: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_cset_w0_from_cc_arch(elf_ctx: *u8, cc: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_div_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_epilogue_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_idiv_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_imul_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_jeq_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_jge_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_jmp_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_jnz_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_jz_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_label_arch(elf_ctx: *u8, name: *u8, name_len: i32, is_func: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_lea_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_load_32_from_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_load_64_from_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_load_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_load_rbp_to_rbx_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_load_zext8_from_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_edx_to_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_imm32_to_rbx_arch(elf_ctx: *u8, imm32: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_imm64_to_rax_arch(elf_ctx: *u8, lo: i32, hi: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_rax_to_arg_reg_arch(elf_ctx: *u8, k: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_rax_to_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_rbx_to_ecx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_mov_rbx_to_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_neg_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_not_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_or_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_pop_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_pop_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_prologue_arch(elf_ctx: *u8, frame_sz: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_push_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_rax_plus_rbx_scale1_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_rax_plus_rbx_scale4_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_rax_plus_rbx_scale8_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_rem_mod_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_rem_mod_unsigned_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_ret_imm32_arch(elf_ctx: *u8, imm32: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_sar_cl_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_sar_cl_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_setz_movzbl_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_shl_cl_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_shl_cl_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_shr_cl_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_shr_cl_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_store_rax_to_rbp_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_store_rax_to_rbx_indirect_arch(elf_ctx: *u8, elem_sz: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_store_rax_to_rbx_offset_arch(elf_ctx: *u8, offset: i32, store_size: i32, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_sub_rax_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_sub_rbx_rax_then_mov_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_test_eax_eax_arch(elf_ctx: *u8, ta: i32): i32;
export extern "C" function enc_dispatch_backend_enc_xor_rbx_rax_arch(elf_ctx: *u8, ta: i32): i32;

/** Diagnostic: print unsupported ExprKind from runtime (helps locate rc=-6). */
export extern function driver_diagnostic_asm_unsupported_expr(kind: i32): void;
/** C stub: move imm32 into w0/eax/a0 without emitting epilogue
 * (avoids early ret vs enc_ret_imm32 on arm64).
 */
export extern function backend_enc_mov_imm32_to_w0_arch(elf_ctx: *ElfCodegenCtx, imm32: i32, ta: i32): i32;
/** Diagnostic before return -1; loc 1=section_text 2=globl 3=label 4=prologue 5=block_body 6=block_inits 7=emit_expr 8=epilogue 9=tail_join_label. */
export extern function driver_diagnostic_asm_fail_at(loc: i32): void;
/** Diagnostic: record ExprKind ordinal currently being emitted (printed by fail_at). */
export extern function driver_diagnostic_asm_set_last_expr_kind(k: i32): void;
/** Diagnostic: EXPR_VAR not found; first_slot/first_len = ctx first slot name (pass asm_ctx_local first when num_locals>0). */
export extern function driver_diagnostic_asm_var_not_found(name: *u8, name_len: i32, num_locals: i32, first_slot: *u8, first_len: i32): void;
/** Diagnostic: set current function name before each function codegen (for var_not_found). */
export extern function driver_diagnostic_asm_set_current_func(name: *u8, name_len: i32): void;
/* See implementation. */
export extern function driver_freestanding_get(): i32;
/** build_xlang_asm: heavy-module emit gate (runtime_pipeline_abi; call asm_skip_heavy_set_pipeline_ctx first). Historical ast_pool.c left wave309. */
export extern function asm_skip_heavy_module_func_body(module: *Module, arena: *ASTArena, func_index: i32): i32;
/** XLANG_ASM_START_FUNC: skip emit for the first N functions of the module (debug). */
export extern function asm_diag_start_func_skip(): i32;
/** parser_gen / C ABI: write cur_mod import i logical path into out_buf (max 64 bytes, NUL-terminated). */
export extern function parser_get_module_import_path(mod: *Module, i: i32, out_buf: u8[128]): void;
export extern function codegen_import_path_to_c_prefix_into(path: *u8, buf: *u8, buf_cap: i32): void;
/** codegen: some std/c shim calls in AST disagree with real C prototype arity; codegen.x corrects. */
export extern function codegen_call_num_args_override(prefix: *u8, prefix_len: i32, name: *u8, name_len: i32, num_args: i32): i32;
/** Module import path/binding sidecar (runtime_pipeline_abi). Historical ast_pool.c left wave309. */
export extern function pipeline_module_import_path_len(module: *Module, idx: i32): i32;
/**
 * Hoist module top-level let/const into main as block lets for asm stack init.
 * Equivalent to C codegen static+init_globals; call before asm_codegen_ast*.
 * G.7: runtime_pipeline_abi (historical ast_pool.c left wave309).
 */
export extern function pipeline_module_hoist_top_level_lets_into_main(module: *Module, arena: *ASTArena): void;

/** Exported function `asm_hoist_top_level_lets_for_codegen`.
 * Implements `asm_hoist_top_level_lets_for_codegen`.
 * @param module *Module
 * @param arena *ASTArena
 * @return void
 */
export function asm_hoist_top_level_lets_for_codegen(module: *Module, arena: *ASTArena): void {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    pipeline_module_hoist_top_level_lets_into_main(module, arena);
  }
}
export extern function pipeline_module_import_path_byte_at(module: *Module, idx: i32, off: i32): u8;
export extern function pipeline_module_import_kind_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_binding_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_binding_name_byte_at(module: *Module, idx: i32, off: i32): u8;
/** Expr call/match/struct_lit/array_lit sidecar (runtime_pipeline_abi). Historical ast_pool.c left wave309. */
export extern function pipeline_expr_call_arg_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
export extern function pipeline_expr_call_num_args_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_call_callee_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_method_call_arg_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
export extern function pipeline_expr_match_arm_result_ref(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_match_num_arms_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_match_matched_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_match_arm_is_wildcard(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_match_arm_is_enum_variant(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_match_arm_lit_val(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_match_arm_variant_index(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_struct_lit_init_ref(arena: *ASTArena, expr_ref: i32, j: i32): i32;
export extern function pipeline_expr_struct_lit_num_fields(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_array_lit_elem_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
export extern function pipeline_expr_array_lit_num_elems_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_asm_init_is_empty_array_lit_c(arena: *ASTArena, init_ref: i32): i32;
export extern function pipeline_asm_enc_local_slot_ptr_or_addr_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, stack_off: i32, ta: i32, ctx: *u8): i32;
export extern function pipeline_asm_arch_emit_local_slot_ptr_or_addr_text_c(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, stack_off: i32, ta: i32, ctx: *u8): i32;
export extern function pipeline_asm_build_import_binding_call_sym_c(pre: *u8, pre_len: i32, field_name: *u8, field_len: i32, out_name: *u8): i32;
export extern function pipeline_expr_field_access_name_len(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_name_into(arena: *ASTArena, expr_ref: i32, out: *u8): void;
export extern function pipeline_expr_field_access_base_ref(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_var_name_len(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_var_name_into(arena: *ASTArena, expr_ref: i32, out: *u8): void;
export extern function pipeline_asm_index_elem_byte_sz(arena: *ASTArena, index_expr_ref: i32): i32;
export extern function pipeline_asm_array_lit_elem_byte_sz_c(arena: *ASTArena, array_lit_ref: i32): i32;
export extern function pipeline_asm_array_lit_reserve_stack_bytes_c(arena: *ASTArena, init_ref: i32): i32;
export extern function pipeline_asm_struct_lit_reserve_stack_bytes_c(arena: *ASTArena, init_ref: i32): i32;
export extern function pipeline_type_kind_ord_at(arena: *ASTArena, type_ref: i32): i32;
export extern "C" function pipeline_type_named_name_into(arena: *u8, tr: i32, out64: *u8): i32;
export extern function pipeline_expr_kind_ord_at(arena: *ASTArena, expr_ref: i32): i32;
/** Read binop child expr refs; do not use ast_arena_expr_get then e.binop_* (self-host asm field tear; 1+2 would become 1). */
export extern function pipeline_expr_binop_left_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_binop_right_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_unary_operand_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_int_val_at(arena: *ASTArena, expr_ref: i32): i32;
/** C-synced block-body stmt_order emit (runtime_pipeline_abi / backend seed; do not scan stmt_order in X while). Historical pipeline_glue.c left wave309. */
export extern function backend_emit_block_body_sync_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
/* See implementation. */
export extern function pipeline_asm_compute_frame_size_c(num_params: i32, arena: *ASTArena, block_ref: i32, mod: *Module, func_index: i32): i32;
export extern function pipeline_asm_fill_param_slots(ctx: *AsmFuncCtx, mod: *Module, func_index: i32): void;
/* See implementation. */
export extern function pipeline_asm_emit_param_home_elf_c(elf_ctx: *ElfCodegenCtx, ctx: *AsmFuncCtx, mod: *Module, func_index: i32, ta: i32): i32;
export extern function pipeline_asm_emit_set_arena(arena: *ASTArena): void;
export extern function pipeline_asm_emit_set_call_param_type_ref(type_ref: i32): void;
export extern function pipeline_asm_emit_async_cps_entry_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, ctx: *AsmFuncCtx, mod: *Module, func_index: i32, ta: i32): i32;
export extern function pipeline_asm_emit_async_cps_end_func_elf_c(): void;
export extern function pipeline_asm_fill_local_slots(ctx: *AsmFuncCtx, arena: *ASTArena, block_ref: i32): void;
export extern function pipeline_asm_emit_block_inits_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, ctx: *AsmFuncCtx, ta: i32, slot_base: i32): i32;
export extern function pipeline_asm_emit_block_inits_c(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32, slot_base: i32): i32;
export extern function pipeline_asm_emit_block_body_c(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_while_loop_c(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, loop_idx: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_for_loop_c(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, for_idx: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_if_then_block_body_text_c(arena: *ASTArena, out: *CodegenOutBuf, then_block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_expr_c(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_expr_call_c(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_expr_method_call_c(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_next_label_c(ctx: *AsmFuncCtx, buf: *u8, buf_size: i32): i32;
export extern function pipeline_asm_format_label_id_c(buf: *u8, buf_size: i32, id: i32): i32;
export extern function pipeline_asm_emit_if_then_block_body_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, then_block_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_while_loop_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, loop_idx: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_for_loop_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, for_idx: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_loop_body_content_c(arena: *ASTArena, out: *CodegenOutBuf, body_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32;
export extern function pipeline_asm_emit_loop_body_content_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, body_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_expr_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_call_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_method_call_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_call_args_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32, nargs: i32): i32;
/* See implementation. */
export extern function pipeline_asm_emit_skip_heavy_or_thin_stub_elf_c(elf_ctx: *ElfCodegenCtx, ta: i32, module: *Module, func_index: i32): i32;
/* See implementation. */
export extern function pipeline_asm_emit_set_func_index(func_index: i32): void;
/* See implementation. */
export extern function pipeline_asm_emit_set_dep_pipe(pipeline_ctx: *PipelineDepCtx): void;
export extern function pipeline_asm_emit_set_module(module: *Module): void;
export extern function pipeline_debug_trace_body_x_mega_pre_reset(module: *Module, arena: *ASTArena): void;
export extern function pipeline_debug_trace_body_x_mega_post_reset(module: *Module, arena: *ASTArena): void;
export extern function pipeline_debug_trace_body_x_mega_post_params(module: *Module, arena: *ASTArena): void;
export extern function pipeline_debug_trace_body_x_mega_post_frame(module: *Module, arena: *ASTArena): void;
export extern function pipeline_debug_trace_body_x_mega_post_locals(module: *Module, arena: *ASTArena): void;
export extern function pipeline_debug_trace_body_x_mega_pre_emit(module: *Module, arena: *ASTArena): void;
/* See implementation. */
export extern function pipeline_asm_wpo_should_emit_func(module: *Module, func_index: i32): i32;
export extern function pipeline_asm_wpo_pgo_is_hot_func(module: *Module, func_index: i32): i32;
export extern function pipeline_elf_ctx_set_emit_hot(ctx: *u8, hot: i32): void;
export extern function pipeline_asm_wpo_pgo_emit_order_prepare(module: *Module): void;
export extern function pipeline_asm_wpo_pgo_emit_order_count(module: *Module): i32;
export extern function pipeline_asm_wpo_pgo_emit_order_at(module: *Module, order_index: i32): i32;
/* See implementation. */
export extern function pipeline_asm_emit_func_param_is_ptr_by_name_c(arena: *ASTArena, mod: *Module, vname: *u8, vlen: i32): i32;
/* See implementation. */
export extern function pipeline_asm_emit_index_eff_addr_text_c(arena: *ASTArena, out: *CodegenOutBuf, ix_ref: i32, ctx: *AsmFuncCtx, ta: i32, elem_sz: i32): i32;
export extern function pipeline_asm_emit_index_eff_addr_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, ix_ref: i32, ctx: *AsmFuncCtx, ta: i32, elem_sz: i32): i32;
export extern function pipeline_asm_emit_lvalue_eff_addr_text_c(arena: *ASTArena, ob: *CodegenOutBuf, lval_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_lvalue_eff_addr_elf_c(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, lval_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32;
export extern function pipeline_asm_emit_call_args_text_c(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32, nargs: i32): i32;
export extern function pipeline_asm_local_offset_c(ctx: *AsmFuncCtx, name: *u8, name_len: i32): i32;
/* See implementation. */
export extern function pipeline_asm_emit_skip_heavy_stub_elf_c(elf_ctx: *ElfCodegenCtx, ta: i32): i32;
/* See implementation. */
export extern function pipeline_backend_asm_codegen_ast_c(module: *Module, arena: *ASTArena, out: *CodegenOutBuf, pipeline_ctx: *PipelineDepCtx): i32;
export extern function pipeline_backend_asm_codegen_ast_to_elf_c(module: *Module, arena: *ASTArena, elf_ctx: *ElfCodegenCtx, pipeline_ctx: *PipelineDepCtx): i32;
/* See implementation. */
export extern function pipeline_asm_resolve_whole_import_qualified_symbol_c(arena: *ASTArena, cur_mod: *Module, callee_expr_ref: i32, sym_flat: *u8, out_match_imp_j: *i32): i32;
/** Block sidecar fields via C readers; avoid ast_arena_block_get tearing num_stmt_order / final_expr_ref. */
export extern function pipeline_asm_block_num_stmt_order_at(arena: *ASTArena, block_ref: i32): i32;
export extern function pipeline_asm_block_final_expr_ref_at(arena: *ASTArena, block_ref: i32): i32;
export extern function pipeline_asm_block_stmt_order_has_return(arena: *ASTArena, block_ref: i32): i32;
/** Binary left/right child expr refs (emit_expr* reads uniformly via glue). */
export function asm_expr_binop_left(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_expr_binop_left_ref_at(arena, expr_ref);
  }
}
/** Exported function `asm_expr_binop_right`.
 * Implements `asm_expr_binop_right`.
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32
 */
export function asm_expr_binop_right(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_expr_binop_right_ref_at(arena, expr_ref);
  }
}
/** Block sidecar (ast.x thin wrappers + pipeline_block_*). */
export extern function pipeline_block_const_name_copy64(arena: *ASTArena, br: i32, ci: i32, dst: *u8): void;
export extern function pipeline_block_const_name_len(arena: *ASTArena, br: i32, ci: i32): i32;
export extern function pipeline_block_const_init_ref(arena: *ASTArena, br: i32, ci: i32): i32;
export extern function pipeline_block_let_name_copy64(arena: *ASTArena, br: i32, li: i32, dst: *u8): void;
export extern function pipeline_block_let_name_len(arena: *ASTArena, br: i32, li: i32): i32;
export extern function pipeline_block_let_init_ref(arena: *ASTArena, br: i32, li: i32): i32;
/** Asm main-loop Func pool readers (runtime_pipeline_abi forwarders; avoid codegen_ prefix). Historical pipeline_glue.c left wave309. */
export extern function pipeline_asm_module_func_is_extern_at(mod: *Module, func_index: i32): i32;
export extern function pipeline_asm_module_func_body_ref_at(mod: *Module, func_index: i32): i32;
export extern function pipeline_asm_module_func_name_len_at(mod: *Module, func_index: i32): i32;
export extern function pipeline_asm_module_func_name_copy64(module: *Module, fi: i32, dst: *u8): void;
export extern function pipeline_asm_module_func_num_params_at(mod: *Module, func_index: i32): i32;
export extern function pipeline_asm_module_func_param_name_len_at(mod: *Module, func_index: i32, param_index: i32): i32;
export extern function pipeline_asm_module_func_param_name_copy32(mod: *Module, func_index: i32, param_index: i32, dst: *u8): void;
export extern function pipeline_asm_get_return_expr_ref_at(arena: *ASTArena, module: *Module, func_index: i32): i32;
/* Declared in backend_call_dispatch.x; used by the implicit-tail f64 return
 * conversion (AAPCS64 boundary wave). Same authority, extern re-declaration. */
export extern function pipeline_module_func_return_type_at(m: *u8, fi: i32): i32;
/* fmov dK, x0 dispatcher; defined alongside the other backend_enc_*_arch
 * dispatchers (backend_enc_dispatch seed object). Single authority — no new
 * encoder body here. */
export extern function backend_enc_mov_rax_to_xmm_arg_reg_arch(elf: *u8, k: i32, ta: i32): i32;
/** Import-qualified symbol field-layer scratch (runtime_pipeline_abi; shared with typeck.x). Historical ast_pool.c left wave309. */
export extern function asm_qual_sym_layer_reset(): void;
export extern function asm_qual_sym_layer_push(bytes: *u8, len: i32): i32;
export extern function asm_qual_sym_layer_count(): i32;
export extern function asm_qual_sym_layer_len(i: i32): i32;
export extern function asm_qual_sym_layer_copy(i: i32, dst: *u8, cap: i32): void;
/** AsmFuncCtx local-slot sidecar (runtime_pipeline_abi; key = ctx pointer). Historical ast_pool.c left wave309. */
export extern function asm_ctx_local_reset(ctx: *u8): void;
export extern function asm_ctx_local_count(ctx: *u8): i32;
export extern function asm_ctx_local_append(ctx: *u8, name: *u8, name_len: i32, offset: i32): i32;
export extern function asm_ctx_local_name_len(ctx: *u8, idx: i32): i32;
export extern function asm_ctx_local_name_byte_at(ctx: *u8, idx: i32, off: i32): u8;
export extern function asm_ctx_local_name_copy64(ctx: *u8, idx: i32, dst: *u8): void;
export extern function asm_ctx_local_offset_at(ctx: *u8, idx: i32): i32;
export extern function pipeline_module_struct_layout_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_struct_layout_name_byte_at(module: *Module, idx: i32, off: i32): u8;

/** Map ExprKind to ordinal (0..60) for diagnostics; typeck lacks enum-as-i32, so branch-map explicitly. */
export function expr_kind_ordinal(k: ExprKind): i32 {
  let o: i32 = k as i32;
  let lo: i32 = ExprKind.EXPR_LIT as i32;
  let hi: i32 = ExprKind.EXPR_TRY_PROPAGATE as i32;
  if (o < lo || o > hi) {
    return -1;
  }
  return o;
}

/**
 * True when init is empty array literal [] (zero elements).
 * For `let buf: T[N] = []`, skip emit/store; stack-slot address is buf base (INDEX uses VAR+LEA).
 */
/**
 * When left is in rax and immediate right is in rbx, enc_cmp_setcc uses cmp w1,w0;
 * swap lt/le/gt/ge condition codes for left OP right (eq/ne unchanged).
 */
export function asm_cmp_cc_when_rhs_imm_in_rbx(cc: i32): i32 {
  if (cc == 2) { return 4; }
  if (cc == 3) { return 5; }
  if (cc == 4) { return 2; }
  if (cc == 5) { return 3; }
  return cc;
}

/** Exported function `asm_init_is_empty_array_lit`.
 * Implements `asm_init_is_empty_array_lit`.
 * @param arena *ASTArena
 * @param init_ref i32
 * @return i32
 */
export function asm_init_is_empty_array_lit(arena: *ASTArena, init_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_init_is_empty_array_lit_c(arena, init_ref);
  }
}

/** Exported function `enc_label_arch`.
 * Implements `enc_label_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param name u8[128]
 * @param name_len i32
 * @param is_func i32
 * @param ta i32
 * @return i32
 */
export function enc_label_arch(elf_ctx: *ElfCodegenCtx, name: u8[128], name_len: i32, is_func: i32, ta: i32): i32 {
  let use_len: i32 = name_len;
  let use_ptr: *u8 = &name[0];
  /* See implementation. */
  return backend_enc_dispatch.backend_enc_label_arch(elf_ctx as *u8, use_ptr, use_len, is_func, ta);
}
/** Exported function `enc_prologue_arch`.
 * Implements `enc_prologue_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param frame_sz i32
 * @param ta i32
 * @return i32
 */
export function enc_prologue_arch(elf_ctx: *ElfCodegenCtx, frame_sz: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_prologue_arch(elf_ctx as *u8, frame_sz, ta);
  }
}
/** Exported function `enc_epilogue_arch`.
 * Implements `enc_epilogue_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_epilogue_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_epilogue_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_ret_imm32_arch`.
 * Implements `enc_ret_imm32_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param imm32 i32
 * @param ta i32
 * @return i32
 */
export function enc_ret_imm32_arch(elf_ctx: *ElfCodegenCtx, imm32: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_ret_imm32_arch(elf_ctx as *u8, imm32, ta);
  }
}

/** Exported function `enc_mov_imm32_to_rbx_arch`.
 * Implements `enc_mov_imm32_to_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param imm32 i32
 * @param ta i32
 * @return i32
 */
export function enc_mov_imm32_to_rbx_arch(elf_ctx: *ElfCodegenCtx, imm32: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_imm32_to_rbx_arch(elf_ctx as *u8, imm32, ta);
  }
}
/** Move 64-bit immediate into rax/x0; used by EXPR_FLOAT_LIT (double bit pattern). */
export function enc_mov_imm64_to_rax_arch(elf_ctx: *ElfCodegenCtx, lo: i32, hi: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_imm64_to_rax_arch(elf_ctx as *u8, lo, hi, ta);
  }
}
/** Exported function `enc_push_rax_arch`.
 * Implements `enc_push_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_push_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_push_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_pop_rax_arch`.
 * Implements `enc_pop_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_pop_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_pop_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_pop_rbx_arch`.
 * Implements `enc_pop_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_pop_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_pop_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_add_rax_rbx_arch`.
 * Implements `enc_add_rax_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_add_rax_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_add_rax_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** w0/eax = w0 - w1 (left in w0, right/imm in w1); arm64 has enc_sub_rax_rbx, x86/rv via C glue. */
export function enc_sub_rax_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_sub_rax_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_sub_rbx_rax_then_mov_arch`.
 * Implements `enc_sub_rbx_rax_then_mov_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_sub_rbx_rax_then_mov_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_sub_rbx_rax_then_mov_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_imul_rbx_rax_arch`.
 * Implements `enc_imul_rbx_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_imul_rbx_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_imul_rbx_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_mov_rax_to_rbx_arch`.
 * Implements `enc_mov_rax_to_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_mov_rax_to_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_rax_to_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_not_eax_arch`.
 * Implements `enc_not_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_not_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_not_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_and_rbx_rax_arch`.
 * Implements `enc_and_rbx_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_and_rbx_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_and_rbx_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_or_rbx_rax_arch`.
 * Implements `enc_or_rbx_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_or_rbx_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_or_rbx_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_xor_rbx_rax_arch`.
 * Implements `enc_xor_rbx_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_xor_rbx_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_xor_rbx_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_mov_rbx_to_ecx_arch`.
 * Implements `enc_mov_rbx_to_ecx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_mov_rbx_to_ecx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_rbx_to_ecx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_shl_cl_eax_arch`.
 * Implements `enc_shl_cl_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_shl_cl_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_shl_cl_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_shr_cl_eax_arch`.
 * Implements `enc_shr_cl_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_shr_cl_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_shr_cl_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_sar_cl_eax_arch`.
 * Implements `enc_sar_cl_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_sar_cl_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_sar_cl_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_cltd_arch`.
 * Implements `enc_cltd_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_cltd_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cltd_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_idiv_rbx_arch`.
 * Implements `enc_idiv_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_idiv_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_idiv_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_mov_edx_to_eax_arch`.
 * Implements `enc_mov_edx_to_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_mov_edx_to_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_edx_to_eax_arch(elf_ctx as *u8, ta);
  }
}
/** MOD: arm64 uses sdiv+msub (do not let idiv clobber dividend); x86 is cltd+idiv+edx->eax. */
export function enc_rem_mod_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_rem_mod_arch(elf_ctx as *u8, ta);
  }
}
/** shlq %cl, %rax (64-bit logical left shift for i64/u64/usize/isize). */
export function enc_shl_cl_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_shl_cl_rax_arch(elf_ctx as *u8, ta);
  }
}
/** shrq %cl, %rax (64-bit logical right shift). */
export function enc_shr_cl_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_shr_cl_rax_arch(elf_ctx as *u8, ta);
  }
}
/** sarq %cl, %rax (64-bit arithmetic right shift). */
export function enc_sar_cl_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_sar_cl_rax_arch(elf_ctx as *u8, ta);
  }
}
/** divl %ebx (32-bit unsigned division; x86_64 emits xor_edx_edx then divl). */
export function enc_div_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_div_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Unsigned MOD (x86_64: xor_edx_edx+divl+edx->eax; arm64 fallback). */
export function enc_rem_mod_unsigned_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_rem_mod_unsigned_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_neg_eax_arch`.
 * Implements `enc_neg_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_neg_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_neg_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_test_eax_eax_arch`.
 * Implements `enc_test_eax_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_test_eax_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_test_eax_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_setz_movzbl_eax_arch`.
 * Implements `enc_setz_movzbl_eax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_setz_movzbl_eax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_setz_movzbl_eax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_cmp_rbx_rax_arch`.
 * Comparison/utility `enc_cmp_rbx_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_cmp_rbx_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cmp_rbx_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_cmp_rax_rbx_arch`.
 * Comparison/utility `enc_cmp_rax_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_cmp_rax_rbx_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cmp_rax_rbx_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_cmp_w0_imm12_arch`.
 * Comparison/utility `enc_cmp_w0_imm12_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param imm12 i32
 * @param ta i32
 * @return i32
 */
export function enc_cmp_w0_imm12_arch(elf_ctx: *ElfCodegenCtx, imm12: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cmp_w0_imm12_arch(elf_ctx as *u8, imm12, ta);
  }
}
/** Only cset into w0 (cmp must already have run). */
export function enc_cset_w0_from_cc_arch(elf_ctx: *ElfCodegenCtx, cc: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cset_w0_from_cc_arch(elf_ctx as *u8, cc, ta);
  }
}
/** Exported function `enc_cmp_setcc_movzbl_arch`.
 * Comparison/utility `enc_cmp_setcc_movzbl_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param cc i32
 * @param ta i32
 * @return i32
 */
export function enc_cmp_setcc_movzbl_arch(elf_ctx: *ElfCodegenCtx, cc: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_cmp_setcc_movzbl_arch(elf_ctx as *u8, cc, ta);
  }
}
/** Exported function `enc_store_rax_to_rbp_arch`.
 * Implements `enc_store_rax_to_rbp_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param offset i32
 * @param ta i32
 * @return i32
 */
export function enc_store_rax_to_rbp_arch(elf_ctx: *ElfCodegenCtx, offset: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_store_rax_to_rbp_arch(elf_ctx as *u8, offset, ta);
  }
}
/** Exported function `enc_load_rbp_to_rax_arch`.
 * Implements `enc_load_rbp_to_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param offset i32
 * @param ta i32
 * @return i32
 */
export function enc_load_rbp_to_rax_arch(elf_ctx: *ElfCodegenCtx, offset: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_load_rbp_to_rax_arch(elf_ctx as *u8, offset, ta);
  }
}
/** Exported function `enc_load_rbp_to_rbx_arch`.
 * Implements `enc_load_rbp_to_rbx_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param offset i32
 * @param ta i32
 * @return i32
 */
export function enc_load_rbp_to_rbx_arch(elf_ctx: *ElfCodegenCtx, offset: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_load_rbp_to_rbx_arch(elf_ctx as *u8, offset, ta);
  }
}
/** Exported function `enc_lea_rbp_to_rax_arch`.
 * Implements `enc_lea_rbp_to_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param offset i32
 * @param ta i32
 * @return i32
 */
export function enc_lea_rbp_to_rax_arch(elf_ctx: *ElfCodegenCtx, offset: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_lea_rbp_to_rax_arch(elf_ctx as *u8, offset, ta);
  }
}
/**
 * Whether a local slot is an 8-byte pointer to a temp-area object (ARRAY_LIT / STRUCT_LIT init).
 * INDEX / FIELD_ACCESS with VAR base must load that pointer; do not lea the slot address.
 */
export function asm_local_var_slot_holds_indirect_ptr(arena: *ASTArena, base_var: Expr, mod: *Module): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let rtbv: i32 = base_var.resolved_type_ref;
    let kind: i32 = 0;
    if (rtbv <= 0) {
      /* See implementation. */
      if (mod != 0 as *Module && base_var.kind == ExprKind.EXPR_VAR && base_var.var_name_len > 0
          && pipeline_asm_emit_func_param_is_ptr_by_name_c(arena, mod, &base_var.var_name[0], base_var.var_name_len) != 0) {
        return 1;
      }
      return 0;
    }
    kind = pipeline_type_kind_ord_at(arena, rtbv);
    /* See implementation. Compare i32 ordinals (pipeline returns ord, not enum). */
    if (kind == TypeKind.TYPE_PTR as i32) {
      return 1;
    }
    if (kind == TypeKind.TYPE_NAMED as i32 && mod != 0 as *Module) {
      let type_name: u8[128] = [];
      let type_name_len: i32 = pipeline_type_named_name_into(arena as *u8, rtbv, &type_name[0]);
      if (type_name_len > 0 && asm_module_named_type_has_struct_layout(mod, &type_name[0], type_name_len)) {
        return 1;
      }
    }
    return 0;
  }
}

/**
 * ELF: when local VAR is a pointer, load (slot holds object address); else lea (slot is object/array base).
 * Matches text path arch_emit_local_slot_ptr_or_addr.
 */
 */
export function enc_local_slot_ptr_or_addr_arch(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, base_ref: i32, stack_off: i32, ta: i32, ctx: *AsmFuncCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_enc_local_slot_ptr_or_addr_elf_c(arena, elf_ctx, base_ref, stack_off, ta, ctx as *u8);
  }
}
/** Exported function `enc_rax_plus_rbx_scale4_arch`.
 * Implements `enc_rax_plus_rbx_scale4_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_rax_plus_rbx_scale4_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_rax_plus_rbx_scale4_arch(elf_ctx as *u8, ta);
  }
}
/** INDEX scale: rbx*1 (u8). */
export function enc_rax_plus_rbx_scale1_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_rax_plus_rbx_scale1_arch(elf_ctx as *u8, ta);
  }
}
/** INDEX scale: rbx*8 (pointer / wide int). */
export function enc_rax_plus_rbx_scale8_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_rax_plus_rbx_scale8_arch(elf_ctx as *u8, ta);
  }
}
/** Store rax to [rbx]; width elem_sz in {1,4,8} (INDEX assign). */
export function enc_store_rax_to_rbx_indirect_arch(elf_ctx: *ElfCodegenCtx, elem_sz: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_store_rax_to_rbx_indirect_arch(elf_ctx as *u8, elem_sz, ta);
  }
}
/** Exported function `enc_load_32_from_rax_arch`.
 * Implements `enc_load_32_from_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_load_32_from_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_load_32_from_rax_arch(elf_ctx as *u8, ta);
  }
}
/** u8 INDEX load: movzbl/ldrb/lbu (zero-extend into destination register). */
export function enc_load_zext8_from_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_load_zext8_from_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_add_imm_to_rax_arch`.
 * Implements `enc_add_imm_to_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param imm i32
 * @param ta i32
 * @return i32
 */
export function enc_add_imm_to_rax_arch(elf_ctx: *ElfCodegenCtx, imm: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_add_imm_to_rax_arch(elf_ctx as *u8, imm, ta);
  }
}
/** Exported function `enc_load_64_from_rax_arch`.
 * Implements `enc_load_64_from_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_load_64_from_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_load_64_from_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_store_rax_to_rbx_offset_arch`.
 * Implements `enc_store_rax_to_rbx_offset_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param offset i32
 * @param store_size i32
 * @param ta i32
 * @return i32
 */
export function enc_store_rax_to_rbx_offset_arch(elf_ctx: *ElfCodegenCtx, offset: i32, store_size: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_store_rax_to_rbx_offset_arch(elf_ctx as *u8, offset, store_size, ta);
  }
}
/** Exported function `enc_mov_rbx_to_rax_arch`.
 * Implements `enc_mov_rbx_to_rax_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param ta i32
 * @return i32
 */
export function enc_mov_rbx_to_rax_arch(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_rbx_to_rax_arch(elf_ctx as *u8, ta);
  }
}
/** Exported function `enc_jz_arch`.
 * Implements `enc_jz_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param label u8[128]
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
export function enc_jz_arch(elf_ctx: *ElfCodegenCtx, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_jz_arch(elf_ctx as *u8, &label[0], label_len, ta);
  }
}
/** After cmp, branch on equal (match arm); arm64 beq, x86 je. */
export function enc_jeq_arch(elf_ctx: *ElfCodegenCtx, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_jeq_arch(elf_ctx as *u8, &label[0], label_len, ta);
  }
}
/** After cmp, branch when i>=n (counted-while opt); arm64 b.ge / x86 jge / riscv bge a0,a1. */
export function enc_jge_arch(elf_ctx: *ElfCodegenCtx, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_jge_arch(elf_ctx as *u8, &label[0], label_len, ta);
  }
}
/** Exported function `enc_jnz_arch`.
 * Implements `enc_jnz_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param label u8[128]
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
export function enc_jnz_arch(elf_ctx: *ElfCodegenCtx, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_jnz_arch(elf_ctx as *u8, &label[0], label_len, ta);
  }
}
/** Exported function `enc_jmp_arch`.
 * Implements `enc_jmp_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param label u8[128]
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
export function enc_jmp_arch(elf_ctx: *ElfCodegenCtx, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_jmp_arch(elf_ctx as *u8, &label[0], label_len, ta);
  }
}
/** Exported function `enc_mov_rax_to_arg_reg_arch`.
 * Implements `enc_mov_rax_to_arg_reg_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param k i32
 * @param ta i32
 * @return i32
 */
export function enc_mov_rax_to_arg_reg_arch(elf_ctx: *ElfCodegenCtx, k: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_mov_rax_to_arg_reg_arch(elf_ctx as *u8, k, ta);
  }
}
/** Exported function `enc_call_arch`.
 * Implements `enc_call_arch`.
 * @param elf_ctx *ElfCodegenCtx
 * @param name u8[128]
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
export function enc_call_arch(elf_ctx: *ElfCodegenCtx, name: u8[128], name_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_enc_dispatch.backend_enc_call_arch(elf_ctx as *u8, &name[0], name_len, ta);
  }
}

/** Current function context: frame size, local table (sidecar), label counter;
 * loop break/continue target stacks; trailing padding OK when aligning new fields with C/driver (typeck padding gate).
 */
allow(padding) struct AsmFuncCtx {
  frame_size: i32;
  next_offset: i32;
  num_locals: i32;
  label_counter: i32;
  /** Module under codegen; FIELD_ACCESS uses it to tell aggregate struct_layout fields from plain enums. Null → legacy 64-bit load. */
  module_ref: *Module;
  /** Nested-loop break label stack: 8 levels × 64 bytes = 512 bytes. */
  loop_break_label_stack: u8[512];
  loop_break_len_stack: i32[8];
  /** Nested-loop continue label stack: 8 levels × 64 bytes = 512 bytes. */
  loop_continue_label_stack: u8[512];
  loop_continue_len_stack: i32[8];
  /** Active break/continue labels (stack top); fast path for EXPR_BREAK/EXPR_CONTINUE. */
  break_label: u8[128];
  break_len: i32;
  continue_label: u8[128];
  continue_len: i32;
  /** Loop-label stack depth; push fails when d>=8. */
  loop_label_depth: i32;
  /** Pipeline deps (dep_paths / ndep); bind import calls `mod.fn` with the same symbol spelling as codegen. */
  dep_pipe: *PipelineDepCtx;
  /** Function tail-join label (from emit_next_label): bare `return;` jmps here, then joins tail return expr + epilogue. */
  tail_join_label: u8[128];
  tail_join_label_len: i32;
}

/** Cast AsmFuncCtx pointer to asm_ctx_local_* sidecar key (*u8). */
export function asm_ctx_key(ctx: *AsmFuncCtx): *u8 {
  return ctx as *u8;
}

/** Return 1 when prefix is ASCII "build_" (6 bytes) and name already contains it; mirrors codegen_c_prefix_redundant_with_name. */
export function asm_c_prefix_redundant_with_name(prefix: *u8, prefix_len: i32, name: *u8, name_len: i32): i32 {
  if (prefix == 0 as *u8 || name == 0 as *u8) {
    return 0;
  }
  if (prefix_len != 6) {
    return 0;
  }
  if (prefix[0] != 98 || prefix[1] != 117 || prefix[2] != 105 || prefix[3] != 108 || prefix[4] != 100 || prefix[5] != 95) {
    return 0;
  }
  if (name_len < prefix_len) {
    return 0;
  }
  let i: i32 = 0;
  while (i < prefix_len) {
    if (name[i] != prefix[i]) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}

/** Concat C prefix bytes + field name into out_name (max 63); return length 1..63 on success, -1 on failure. */
export function asm_build_import_binding_call_sym(pre: *u8, pre_len: i32, field_name: *u8, field_len: i32, out_name: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_build_import_binding_call_sym_c(pre, pre_len, field_name, field_len, out_name);
  }
}

/** Number of "." segments in import path buffer (matches typeck_import_path_segment_count). */
export function asm_import_path_segment_count_local(path: *u8, path_len: i32): i32 {
  if (path_len <= 0 || path == 0 as *u8) {
    return 0;
  }
  let n: i32 = 1;
  let ii: i32 = 0;
  while (ii < path_len) {
    if (path[ii] == 46) {
      n = n + 1;
    }
    ii = ii + 1;
  }
  return n;
}

/** Compare module import imp_ix path slice [off..off+seg_len) to an external byte sequence. */
export function asm_import_path_slice_equal(module: *Module, imp_ix: i32, off: i32, seg_len: i32, nm: *u8, nm_len: i32): bool {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (seg_len != nm_len || seg_len <= 0) {
      return false;
    }
    let i: i32 = 0;
    while (i < seg_len) {
      if (pipeline_module_import_path_byte_at(module, imp_ix, off + i) != nm[i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/** Compare import binding name to an external byte sequence. */
export function asm_import_binding_name_equal(module: *Module, imp_ix: i32, nm: *u8, nm_len: i32): bool {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let bl: i32 = pipeline_module_import_binding_name_len(module, imp_ix);
    if (bl != nm_len || nm_len <= 0) {
      return false;
    }
    let i: i32 = 0;
    while (i < nm_len) {
      if (pipeline_module_import_binding_name_byte_at(module, imp_ix, i) != nm[i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/** Start offset and length of the want_seg-th segment in pipeline_module_import_path (aligned with typeck_import_segment_at). */
export function asm_import_segment_at_local(module: *Module, imp_ix: i32, want_seg: i32,
  ostr: *i32, olen: *i32): bool {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (module == 0 as *Module || imp_ix < 0 || imp_ix >= module.num_imports) {
      return false;
    }
    let pl: i32 = pipeline_module_import_path_len(module, imp_ix);
    if (pl <= 0 || pl > 127) {
      return false;
    }
    let ci: i32 = 0;
    let ss: i32 = 0;
    let k: i32 = 0;
    while (k <= pl) {
      let at_end_p: bool = k == pl;
      let dot_p: bool = false;
      if (!at_end_p && k < pl) {
        dot_p = pipeline_module_import_path_byte_at(module, imp_ix, k) == 46;
      }
      if (at_end_p || dot_p) {
        let seg_len_here: i32 = k - ss;
        if (seg_len_here <= 0) {
          return false;
        }
        if (ci == want_seg) {
          ostr[0] = ss;
          olen[0] = seg_len_here;
          return true;
        }
        if (dot_p) {
          ss = k + 1;
        }
        ci = ci + 1;
      }
      k = k + 1;
    }
    return false;
  }
}

/** Convert cur_mod import[imp_ix] logical path to a C ABI prefix into pre_buf.
 * @return i32 — prefix byte length on success; -1 if path/prefix empty.
 */
export function asm_fill_c_prefix_from_module_import(cur_mod: *Module, imp_ix: i32, pre_buf: *u8): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let path_bytes: u8[128] = [];
    parser_get_module_import_path(cur_mod, imp_ix, path_bytes);
    if (path_bytes[0] == 0) {
      return -1;
    }
    codegen_import_path_to_c_prefix_into(&path_bytes[0], pre_buf, 128);
    let pre_len: i32 = 0;
    while (pre_len < 128 && pre_buf[pre_len] != 0) {
      pre_len = pre_len + 1;
    }
    if (pre_len <= 0) {
      return -1;
    }
    return pre_len;
  }
}

/** Resolve `import a.b…` + `a.b….method(args)` into a codegen-aligned C ABI symbol in sym_flat.
 * @param sym_flat *u8 — out buffer; returns byte length, or -1 on miss.
 * On success also writes the matching module import slot index to *out_match_imp_j.
 * `pipe` is retained for ABI capacity: prefix always comes from cur_mod import path
 * (PipelineDepCtx.ndep is often the entry direct-dep count under codegen dep modules and
 * need not match cur_mod.num_imports — do not use dep_j < pipe.ndep as a miss filter).
 * On miss leave *out unchanged.
 */
export function asm_resolve_whole_import_qualified_symbol(
  arena: *ASTArena, cur_mod: *Module, pipe: *PipelineDepCtx, callee_expr_ref: i32, sym_flat: *u8,
  out_match_imp_j: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    /* See implementation. */
    return pipeline_asm_resolve_whole_import_qualified_symbol_c(arena, cur_mod, callee_expr_ref, sym_flat, out_match_imp_j);
  }
}

/** Exported function `asm_emit_call_args_text`.
 * Implements `asm_emit_call_args_text`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param expr_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @param nargs i32
 * @return i32
 */
export function asm_emit_call_args_text(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32, nargs: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_call_args_text_c(arena, out, expr_ref, ctx, target_arch, nargs);
  }
}

/** Exported function `asm_emit_call_args_elf`.
 * Implements `asm_emit_call_args_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param e Expr
 * @param expr_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @param nargs i32
 * @return i32
 */
export function asm_emit_call_args_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, e: Expr, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32, nargs: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, nargs);
  }
}


/** Compare two identifier byte sequences for equality (same role as typeck.name_equal; used by asm struct_layout lookup). */
export function asm_names_equal(a: *u8, a_len: i32, b: *u8, b_len: i32): bool {
  if (a_len != b_len || a_len <= 0) {
    return false;
  }
  let i: i32 = 0;
  while (i < a_len) {
    if (a[i] != b[i]) {
      return false;
    }
    i = i + 1;
  }
  return true;
}
/** Exported function `asm_module_named_type_has_struct_layout`.
 * Implements `asm_module_named_type_has_struct_layout`.
 * @param module *Module
 * @param name *u8
 * @param name_len i32
 * @return bool
 */
export function asm_module_named_type_has_struct_layout(module: *Module, name: *u8, name_len: i32): bool {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (module == 0 as *Module || name_len <= 0) {
      return false;
    }
    let k: i32 = 0;
    while (k < module.num_struct_layouts) {
      let nlen: i32 = pipeline_module_struct_layout_name_len(module, k);
      if (nlen == name_len && nlen > 0) {
        let eq: bool = true;
        let j: i32 = 0;
        while (j < name_len && eq) {
          if (pipeline_module_struct_layout_name_byte_at(module, k, j) != name[j]) {
            eq = false;
          }
          j = j + 1;
        }
        if (eq) {
          return true;
        }
      }
      k = k + 1;
    }
    return false;
  }
}

/**
 * Byte width to load at FIELD_ACCESS effective address [rax/x0]+offset.
 * When module_ref is null, fall back to 8 bytes to preserve historical behavior.
 */
export function asm_field_access_load_byte_sz(arena: *ASTArena, field_expr_ref: i32, module: *Module): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let kind: i32 = 0;
    if (field_expr_ref <= 0) {
      return 8;
    }
    let fx: Expr = ast.ast_arena_expr_get(arena, field_expr_ref);
    if (fx.resolved_type_ref <= 0) {
      return 8;
    }
    kind = pipeline_type_kind_ord_at(arena, fx.resolved_type_ref);
    if (kind == TypeKind.TYPE_U8 as i32) {
      return 1;
    }
    /* 10.3.3: TYPE_FN shares Cap-fn-ptr opaque ABI — 8-byte field load. */
    if (kind == TypeKind.TYPE_PTR as i32 || kind == TypeKind.TYPE_FN as i32
        || kind == TypeKind.TYPE_I64 as i32 || kind == TypeKind.TYPE_U64 as i32
        || kind == TypeKind.TYPE_USIZE as i32 || kind == TypeKind.TYPE_ISIZE as i32
        || kind == TypeKind.TYPE_F64 as i32) {
      return 8;
    }
    if (kind == TypeKind.TYPE_NAMED as i32 && module != 0 as *Module) {
      let type_name: u8[128] = [];
      let type_name_len: i32 = pipeline_type_named_name_into(arena as *u8, fx.resolved_type_ref, &type_name[0]);
      if (type_name_len > 0 && asm_module_named_type_has_struct_layout(module, &type_name[0], type_name_len)) {
        return 8;
      }
    }
    return 4;
  }
}

/** Reset per-function asm context for a new function. Records mod into module_ref for emit_expr FIELD_ACCESS etc. */
/** Exported function `ctx_reset`.
 * Implements `ctx_reset`.
 * @param ctx *AsmFuncCtx
 * @param mod *Module
 * @return void
 */
export function ctx_reset(ctx: *AsmFuncCtx, mod: *Module): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    ctx.frame_size = 0;
    ctx.next_offset = 0;
    ctx.num_locals = 0;
    ctx.module_ref = mod;
    ctx.break_len = 0;
    ctx.continue_len = 0;
    ctx.loop_label_depth = 0;
    ctx.dep_pipe = 0 as *PipelineDepCtx;
    ctx.tail_join_label_len = 0;
    asm_ctx_local_reset(asm_ctx_key(ctx));
  }
}

/** Compute stack frame size from params + block const/let count (8 bytes/slot, round up to 16), reserving 64-byte temp for STRUCT_LIT/ARRAY_LIT. */
/** Exported function `compute_frame_size`.
 * Implements `compute_frame_size`.
 * @param num_params i32
 * @param arena *ASTArena
 * @param block_ref i32
 * @param mod *Module
 * @param func_index i32
 * @return i32
 */
export function compute_frame_size(num_params: i32, arena: *ASTArena, block_ref: i32, mod: *Module, func_index: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_compute_frame_size_c(num_params, arena, block_ref, mod, func_index);
  }
}


/** Fill function params into ctx local sidecar (offsets 8, 16, 24, …). Must run before fill_local_slots. */
/** Exported function `fill_param_slots`.
 * Implements `fill_param_slots`.
 * @param ctx *AsmFuncCtx
 * @param mod *Module
 * @param func_index i32
 * @return void
 */
export function fill_param_slots(ctx: *AsmFuncCtx, mod: *Module, func_index: i32): void {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    pipeline_asm_fill_param_slots(ctx, mod, func_index);
  }
}


/** Fill block const/let into ctx local sidecar starting at ctx.next_offset (after fill_param_slots). */
/** Exported function `fill_local_slots`.
 * Implements `fill_local_slots`.
 * @param ctx *AsmFuncCtx
 * @param arena *ASTArena
 * @param block_ref i32
 * @return void
 */
export function fill_local_slots(ctx: *AsmFuncCtx, arena: *ASTArena, block_ref: i32): void {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    pipeline_asm_fill_local_slots(ctx, arena, block_ref);
  }
}


/**
 * If-stmt then-block may hold independent const/let; they must be entered into ctx.locals
 * before EXPR_VAR resolution. Same pattern as EXPR_BLOCK: temporarily grow the slot table,
 * then restore num_locals/next_offset so nested branch stack offsets can be reused.
 */
/** Exported function `emit_if_then_block_body_text`.
 * Implements `emit_if_then_block_body_text`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param then_block_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_if_then_block_body_text(arena: *ASTArena, out: *CodegenOutBuf, then_block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_if_then_block_body_text_c(arena, out, then_block_ref, ctx, target_arch);
  }
}


/** ELF path: machine counterpart of `emit_if_then_block_body_text`. ta is target-arch index. */
/* See implementation. */
export function emit_if_then_block_body_elf(
  arena: *ASTArena,
  elf_ctx: *ElfCodegenCtx,
  then_block_ref: i32,
  ctx: *AsmFuncCtx,
  ta: i32
): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_if_then_block_body_elf_c(arena, elf_ctx, then_block_ref, ctx, ta);
  }
}


/** Look up name in ctx local sidecar; return stack offset, or -1 if not found. */
/** Exported function `local_offset`.
 * Implements `local_offset`.
 * @param ctx *AsmFuncCtx
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
export function local_offset(ctx: *AsmFuncCtx, name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_local_offset_c(ctx, name, name_len);
  }
}

/** Exported function `arch_emit_ret_imm32`.
 * Implements `arch_emit_ret_imm32`.
 * @param out *CodegenOutBuf
 * @param imm i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_ret_imm32(out: *CodegenOutBuf, imm: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_ret_imm32(out, imm); }
    if (ta == 2) { return riscv64.emit_ret_imm32(out, imm); }
    return x86_64.emit_ret_imm32(out, imm);
  }
}
/** Move a 64-bit immediate (lo/hi = low/high 32 bits) into rax/x0. Used for EXPR_FLOAT_LIT double bit patterns. */
export function arch_emit_mov_imm64_to_rax(out: *CodegenOutBuf, lo: i32, hi: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_mov_imm64_to_rax(out, lo, hi); }
    if (ta == 2) { return riscv64.emit_mov_imm64_to_rax(out, lo, hi); }
    return x86_64.emit_mov_imm64_to_rax(out, lo, hi);
  }
}
/** 7.3: immediate into rbx/w1; avoids push/pop when ADD left operand is a literal. */
export function arch_emit_mov_imm32_to_rbx(out: *CodegenOutBuf, imm: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_mov_imm32_to_rbx(out, imm); }
    if (ta == 2) { return riscv64.emit_mov_imm32_to_rbx(out, imm); }
    return x86_64.emit_mov_imm32_to_rbx(out, imm);
  }
}
/** Exported function `arch_emit_neg_eax`.
 * Implements `arch_emit_neg_eax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_neg_eax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_neg_eax(out); }
    if (ta == 2) { return riscv64.emit_neg_eax(out); }
    return x86_64.emit_neg_eax(out);
  }
}
/** Exported function `arch_emit_test_setz`.
 * Implements `arch_emit_test_setz`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_test_setz(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) {
      if (arm64.emit_test_eax_eax(out) != 0) { return -1; }
      return arm64.emit_setz_movzbl_eax(out);
    }
    if (ta == 2) {
      if (riscv64.emit_test_eax_eax(out) != 0) { return -1; }
      return riscv64.emit_setz_movzbl_eax(out);
    }
    if (x86_64.emit_test_eax_eax(out) != 0) { return -1; }
    return x86_64.emit_setz_movzbl_eax(out);
  }
}

/** Compare rbx vs rax (set flags/result for jz). Used by match-arm equality. */
export function arch_emit_cmp_rbx_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_cmp_rbx_rax(out); }
    if (ta == 2) { return riscv64.emit_cmp_rbx_rax(out); }
    return x86_64.emit_cmp_rbx_rax(out);
  }
}

/** Compare: left already in rbx, right in rax; set result 0/1 from cc. cc: 0=eq,1=ne,2=lt,3=le,4=gt,5=ge. */
export function arch_emit_cmp_setcc(out: *CodegenOutBuf, cc: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) {
      return arm64.emit_cmp_setcc(out, cc);
    }
    if (ta == 2) { return riscv64.emit_cmp_setcc(out, cc); }
    return x86_64.emit_cmp_setcc(out, cc);
  }
}

/** Exported function `arch_emit_push_rax`.
 * Implements `arch_emit_push_rax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_push_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_push_rax(out); }
    if (ta == 2) { return riscv64.emit_push_rax(out); }
    return x86_64.emit_push_rax(out);
  }
}
/** Exported function `arch_emit_pop_rbx`.
 * Implements `arch_emit_pop_rbx`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_pop_rbx(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_pop_rbx(out); }
    if (ta == 2) { return riscv64.emit_pop_rbx(out); }
    return x86_64.emit_pop_rbx(out);
  }
}
/** Exported function `arch_emit_pop_rax`.
 * Implements `arch_emit_pop_rax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_pop_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_pop_rax(out); }
    if (ta == 2) { return riscv64.emit_pop_rax(out); }
    return x86_64.emit_pop_rax(out);
  }
}
/** Exported function `arch_emit_add_rax_rbx`.
 * Implements `arch_emit_add_rax_rbx`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_add_rax_rbx(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_add_rax_rbx(out); }
    if (ta == 2) { return riscv64.emit_add_rax_rbx(out); }
    return x86_64.emit_add_rax_rbx(out);
  }
}
/** Exported function `arch_emit_sub_rbx_rax_then_mov`.
 * Implements `arch_emit_sub_rbx_rax_then_mov`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_sub_rbx_rax_then_mov(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_sub_rbx_rax_then_mov(out); }
    if (ta == 2) { return riscv64.emit_sub_rbx_rax_then_mov(out); }
    return x86_64.emit_sub_rbx_rax_then_mov(out);
  }
}
/** Exported function `arch_emit_imul_rbx_rax`.
 * Implements `arch_emit_imul_rbx_rax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_imul_rbx_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_imul_rbx_rax(out); }
    if (ta == 2) { return riscv64.emit_imul_rbx_rax(out); }
    return x86_64.emit_imul_rbx_rax(out);
  }
}
/** Exported function `arch_emit_mov_rax_to_rbx`.
 * Implements `arch_emit_mov_rax_to_rbx`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_mov_rax_to_rbx(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_mov_rax_to_rbx(out); }
    if (ta == 2) { return riscv64.emit_mov_rax_to_rbx(out); }
    return x86_64.emit_mov_rax_to_rbx(out);
  }
}
/** Exported function `arch_emit_idiv_rbx`.
 * Implements `arch_emit_idiv_rbx`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_idiv_rbx(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_idiv_rbx(out); }
    if (ta == 2) { return riscv64.emit_idiv_rbx(out); }
    if (x86_64.emit_cltd(out) != 0) { return -1; }
    return x86_64.emit_idiv_rbx(out);
  }
}
/** Exported function `arch_emit_rem_mod`.
 * Implements `arch_emit_rem_mod`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_rem_mod(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_rem_w0_w1(out); }
    if (ta == 2) { return riscv64.emit_rem_w0_w1(out); }
    if (x86_64.emit_cltd(out) != 0) { return -1; }
    if (x86_64.emit_idiv_rbx(out) != 0) { return -1; }
    return x86_64.emit_mov_edx_to_eax(out);
  }
}
/** Exported function `arch_emit_load_rbp_to_rax`.
 * Implements `arch_emit_load_rbp_to_rax`.
 * @param out *CodegenOutBuf
 * @param off i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_load_rbp_to_rax(out: *CodegenOutBuf, off: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_load_rbp_to_rax(out, off); }
    if (ta == 2) { return riscv64.emit_load_rbp_to_rax(out, off); }
    return x86_64.emit_load_rbp_to_rax(out, off);
  }
}
/** Exported function `arch_emit_store_rax_to_rbp`.
 * Implements `arch_emit_store_rax_to_rbp`.
 * @param out *CodegenOutBuf
 * @param off i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_store_rax_to_rbp(out: *CodegenOutBuf, off: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_store_rax_to_rbp(out, off); }
    if (ta == 2) { return riscv64.emit_store_rax_to_rbp(out, off); }
    return x86_64.emit_store_rax_to_rbp(out, off);
  }
}
/** LEA local-variable address into rax (x86/arm64). For EXPR_INDEX base=VAR and STRUCT_LIT/ARRAY_LIT temp. */
export function arch_emit_lea_rbp_to_rax(out: *CodegenOutBuf, off: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_lea_rbp_to_rax(out, off); }
    if (ta == 2) { return riscv64.emit_lea_rbp_to_rax(out, off); }
    return x86_64.emit_lea_rbp_to_rax(out, off);
  }
}
/**
 * Text path: if local VAR is a pointer, load pointer from stack slot into rax;
 * otherwise rax = stack-slot address (in-place struct/array).
 * In codegen.x, `fn(..., out: *CodegenOutBuf)` style `out.field` must load — never lea the slot.
 */
export function arch_emit_local_slot_ptr_or_addr(arena: *ASTArena, out: *CodegenOutBuf, base_ref: i32, stack_off: i32, ta: i32, ctx: *AsmFuncCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_arch_emit_local_slot_ptr_or_addr_text_c(arena, out, base_ref, stack_off, ta, ctx as *u8);
  }
}
/** rax/x0 = rax/x0 + rbx/x1*4. For EXPR_INDEX with element size 4. */
export function arch_emit_rax_plus_rbx_scale4(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_rax_plus_rbx_scale4(out); }
    if (ta == 2) { return riscv64.emit_rax_plus_rbx_scale4(out); }
    return x86_64.emit_rax_plus_rbx_scale4(out);
  }
}
/** Add rbx×1 to address (u8 arrays). */
export function arch_emit_rax_plus_rbx_scale1(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_rax_plus_rbx_scale1(out); }
    if (ta == 2) { return riscv64.emit_rax_plus_rbx_scale1(out); }
    return x86_64.emit_rax_plus_rbx_scale1(out);
  }
}
/** rbx×8 (pointer slices, etc.). */
export function arch_emit_rax_plus_rbx_scale8(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_rax_plus_rbx_scale8(out); }
    if (ta == 2) { return riscv64.emit_rax_plus_rbx_scale8(out); }
    return x86_64.emit_rax_plus_rbx_scale8(out);
  }
}
/** INDEX store: write to [rbx]. */
export function arch_emit_store_rax_to_rbx_indirect(out: *CodegenOutBuf, elem_sz: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_store_rax_to_rbx_indirect(out, elem_sz); }
    if (ta == 2) { return riscv64.emit_store_rax_to_rbx_indirect(out, elem_sz); }
    return x86_64.emit_store_rax_to_rbx_indirect(out, elem_sz);
  }
}
/** Load 4 bytes from [rax]/[x0] into rax/w0. For EXPR_INDEX element reads. */
export function arch_emit_load_32_from_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_load_32_from_rax(out); }
    if (ta == 2) { return riscv64.emit_load_32_from_rax(out); }
    return x86_64.emit_load_32_from_rax(out);
  }
}
/** Load u8 element and zero-extend into the return register. */
export function arch_emit_load_zext8_from_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_load_zext8_from_rax(out); }
    if (ta == 2) { return riscv64.emit_load_zext8_from_rax(out); }
    return x86_64.emit_load_zext8_from_rax(out);
  }
}
/** rax/x0 += ç«å³æ°ãç¨äº EXPR_FIELD_ACCESS å­æ®µåç§»ã */
export function arch_emit_add_imm_to_rax(out: *CodegenOutBuf, imm: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_add_imm_to_rax(out, imm); }
    if (ta == 2) { return riscv64.emit_add_imm_to_rax(out, imm); }
    return x86_64.emit_add_imm_to_rax(out, imm);
  }
}
/** Load 8 bytes from [rax]/[x0] into rax/x0. For EXPR_FIELD_ACCESS. */
export function arch_emit_load_64_from_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_load_64_from_rax(out); }
    if (ta == 2) { return riscv64.emit_load_64_from_rax(out); }
    return x86_64.emit_load_64_from_rax(out);
  }
}
/** Store rax to [rbx+offset]. store_size 4=ARRAY_LIT element, 8=STRUCT_LIT field. For STRUCT_LIT/ARRAY_LIT temp. */
export function arch_emit_store_rax_to_rbx_offset(out: *CodegenOutBuf, offset: i32, store_size: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_store_rax_to_rbx_offset(out, offset, store_size); }
    if (ta == 2) { return riscv64.emit_store_rax_to_rbx_offset(out, offset, store_size); }
    return x86_64.emit_store_rax_to_rbx_offset(out, offset, store_size);
  }
}
/** Copy rbx to rax (base/value). For STRUCT_LIT/ARRAY_LIT returning temp base. */
export function arch_emit_mov_rbx_to_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_mov_rbx_to_rax(out); }
    if (ta == 2) { return riscv64.emit_mov_rbx_to_rax(out); }
    return x86_64.emit_mov_rbx_to_rax(out);
  }
}
/** Copy current rax into arg register k (System V: 0=rdi..5=r9). arm64 multi-arg uses stack slots + later load; x86 mov here. */
export function arch_emit_mov_rax_to_arg_reg(out: *CodegenOutBuf, k: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return 0; }
    if (ta == 2) { return riscv64.emit_mov_rax_to_arg_reg(out, k); }
    return x86_64.emit_mov_rax_to_arg_reg(out, k);
  }
}

/** arm64: load [sp + i*16] into wi before multi-arg calls. Not used on x86. */
export function arch_emit_ldr_sp_offset_to_wi(out: *CodegenOutBuf, i: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta != 1) { return 0; }
    return arm64.emit_ldr_sp_offset_to_wi(out, i);
  }
}

/** arm64: add sp, sp, #n — reclaim stack after multi-arg call. Not used on x86. */
export function arch_emit_add_sp_imm(out: *CodegenOutBuf, n: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta != 1) { return 0; }
    return arm64.emit_add_sp_imm(out, n);
  }
}

/** Handle EXPR_CALL alone: support import-bound FIELD_ACCESS callee (align with codegen); otherwise require EXPR_VAR. */
/** Exported function `emit_expr_call`.
 * Implements `emit_expr_call`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param expr_ref i32
 * @param e Expr
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_expr_call(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, e: Expr, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_expr_call_c(arena, out, expr_ref, ctx, target_arch);
  }
}


/** EXPR_METHOD_CALL: receiver as arg0, then method args arg1..argN, then call method_call_name. */
/** Exported function `emit_expr_method_call`.
 * Implements `emit_expr_method_call`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param expr_ref i32
 * @param e Expr
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_expr_method_call(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, e: Expr, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_expr_method_call_c(arena, out, expr_ref, ctx, target_arch);
  }
}


/** ELF EXPR_METHOD_CALL: receiver as arg0, then arg1..argN, enc_call(method_name). */
/** Exported function `emit_expr_elf_method_call`.
 * Implements `emit_expr_elf_method_call`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param expr_ref i32
 * @param e Expr
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_expr_elf_method_call(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, e: Expr, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_method_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
  }
}


/** Look up function index in this module by name; -1 if missing. */
export function asm_module_func_index_by_name(mod: *Module, name: *u8, name_len: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (mod == 0 as *Module || name_len <= 0 || name_len > 127) { return -1; }
    let fi: i32 = 0;
    while (fi < mod.num_funcs) {
      let flen: i32 = pipeline_asm_module_func_name_len_at(mod, fi);
      if (flen == name_len) {
        let fb: u8[128] = [];
        pipeline_asm_module_func_name_copy64(mod, fi, &fb[0]);
        let same: i32 = 1;
        let k: i32 = 0;
        while (k < name_len) {
          if (fb[k] != name[k]) { same = 0; }
          k = k + 1;
        }
        if (same != 0) { return fi; }
      }
      fi = fi + 1;
    }
    return -1;
  }
}

/** Whether expr_ref is a VAR naming func_idx's parameter 0. */
export function fold_expr_is_func_param0(arena: *ASTArena, mod: *Module, func_idx: i32, expr_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 3) { return 0; }
    if (pipeline_asm_module_func_num_params_at(mod, func_idx) != 1) { return 0; }
    let plen: i32 = pipeline_asm_module_func_param_name_len_at(mod, func_idx, 0);
    let vlen: i32 = pipeline_expr_var_name_len(arena, expr_ref);
    if (plen <= 0 || plen != vlen) { return 0; }
    let pbuf: u8[128] = [];
    let vbuf: u8[128] = [];
    pipeline_asm_module_func_param_name_copy32(mod, func_idx, 0, &pbuf[0]);
    pipeline_expr_var_name_into(arena, expr_ref, &vbuf[0]);
    let k: i32 = 0;
    while (k < plen) {
      if (pbuf[k] != vbuf[k]) { return 0; }
      k = k + 1;
    }
    return 1;
  }
}

/** Read the operand ref of a function body's single return (including explicit `return expr;`); 0 on failure. */
export function fold_func_return_operand_ref(arena: *ASTArena, mod: *Module, func_idx: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let body_ref: i32 = pipeline_asm_module_func_body_ref_at(mod, func_idx);
    if (body_ref <= 0) { return 0; }
    /*
     * PLATFORM: SHARED — unique-return only (seed twin seed_link_compat).
     * Historic final_expr short-circuit ignored earlier RETURNs → multi-return
     * helpers (e.g. chain_leaf) falsely matched single-field inline.
     */
    let nes: i32 = ast.ast_block_num_expr_stmts(arena, body_ref);
    let found: i32 = 0;
    let op_ref: i32 = 0;
    let ei: i32 = 0;
    while (ei < nes) {
      let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, ei);
      if (er > 0 && pipeline_expr_kind_ord_at(arena, er) == 41) {
        let op_e: i32 = pipeline_expr_unary_operand_ref_at(arena, er);
        if (op_e != 0) {
          found = found + 1;
          op_ref = op_e;
        }
      }
      ei = ei + 1;
    }
    let fin: i32 = pipeline_asm_block_final_expr_ref_at(arena, body_ref);
    if (fin != 0) {
      if (pipeline_expr_kind_ord_at(arena, fin) == 41) {
        let op_f: i32 = pipeline_expr_unary_operand_ref_at(arena, fin);
        if (op_f != 0) {
          if (found == 0) {
            found = 1;
            op_ref = op_f;
          } else {
            return 0;
          }
        }
      } else if (found == 0) {
        return fin;
      } else {
        return 0;
      }
    }
    if (found == 1) { return op_ref; }
    return 0;
  }
}

/** Whether expression is ADD (including EXPR_BINOP placeholder). */
export function fold_expr_is_add_kind(arena: *ASTArena, expr_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    // PLATFORM: SHARED — EXPR_ADD=4; EXPR_BINOP=53 (generic binop that is ADD).
    // Historic bug: k==51 matched EXPR_ADDR_OF, not add.
    let k: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (k == 4 || k == 53) { return 1; }
    return 0;
  }
}

/**
 * If function body is `return param0 + k` or `return callee(param0) + k` (same-module unary chain),
 * return accumulated constant k; return -1 when not linkable. depth caps recursion.
 */
export function fold_func_x_plus_k_chain(arena: *ASTArena, mod: *Module, func_idx: i32, depth: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (depth > 12) { return -1; }
    if (mod == 0 as *Module || func_idx < 0) { return -1; }
    if (pipeline_asm_module_func_is_extern_at(mod, func_idx) != 0) { return -1; }
    if (pipeline_asm_module_func_num_params_at(mod, func_idx) != 1) { return -1; }
    let ret_ref: i32 = fold_func_return_operand_ref(arena, mod, func_idx);
    if (ret_ref <= 0) { return -1; }
    if (fold_expr_is_add_kind(arena, ret_ref) == 0) { return -1; }
    let addend: i32 = 0;
    let right_ref: i32 = asm_expr_binop_right(arena, ret_ref);
    if (pipeline_expr_kind_ord_at(arena, right_ref) != 0) { return -1; }
    addend = pipeline_expr_int_val_at(arena, right_ref);
    let left_ref: i32 = asm_expr_binop_left(arena, ret_ref);
    if (fold_expr_is_func_param0(arena, mod, func_idx, left_ref) != 0) {
      return addend;
    }
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 48) { return -1; }
    if (pipeline_expr_call_num_args_at(arena, left_ref) != 1) { return -1; }
    let arg0: i32 = pipeline_expr_call_arg_ref(arena, left_ref, 0);
    if (fold_expr_is_func_param0(arena, mod, func_idx, arg0) == 0) { return -1; }
    let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, left_ref);
    if (callee_ref <= 0) { return -1; }
    if (pipeline_expr_kind_ord_at(arena, callee_ref) != 3) { return -1; }
    let cname: u8[128] = [];
    pipeline_expr_var_name_into(arena, callee_ref, &cname[0]);
    let inner_fi: i32 = asm_module_func_index_by_name(mod, &cname[0], pipeline_expr_var_name_len(arena, callee_ref));
    if (inner_fi < 0) { return -1; }
    let inner_k: i32 = fold_func_x_plus_k_chain(arena, mod, inner_fi, depth + 1);
    if (inner_k < 0) { return -1; }
    return inner_k + addend;
  }
}

/**
 * ELF CALL fold: when same-module `f(arg0)` and f is `return p.f0 + p.f1` (param0 two i32 fields),
 * emit field loads + add and skip call/ret (also helps const struct cases).
 * @return 1=folded, 0=no match, -1=error.
 */
export function try_inline_param0_field_sum_call_elf(
  arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, e: Expr,
  ctx: *AsmFuncCtx, ta: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let mod_ref: *Module = ctx.module_ref;
    if (mod_ref == 0 as *Module) { return 0; }
    let callee: Expr = ast.ast_arena_expr_get(arena, e.call_callee_ref);
    if (callee.kind != ExprKind.EXPR_VAR) { return 0; }
    if (pipeline_expr_call_num_args_at(arena, expr_ref) != 1) { return 0; }
    let fi: i32 = asm_module_func_index_by_name(mod_ref, callee.var_name, callee.var_name_len);
    if (fi < 0) { return 0; }
    if (fold_func_returns_param0_field_sum(arena, mod_ref, fi) == 0) { return 0; }
    let ret_ref: i32 = fold_func_return_operand_ref(arena, mod_ref, fi);
    if (ret_ref <= 0) { return 0; }
    let al: i32 = asm_expr_binop_left(arena, ret_ref);
    let ar: i32 = asm_expr_binop_right(arena, ret_ref);
    let fa: Expr = ast.ast_arena_expr_get(arena, al);
    let fb: Expr = ast.ast_arena_expr_get(arena, ar);
    let off_a: i32 = fa.field_access_offset;
    let off_b: i32 = fb.field_access_offset;
    let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
    if (arg_ref <= 0) { return -1; }
    let arg_e: Expr = ast.ast_arena_expr_get(arena, arg_ref);
    if (arg_e.kind != ExprKind.EXPR_VAR) { return 0; }
    let slot_off: i32 = local_offset(ctx, arg_e.var_name, arg_e.var_name_len);
    if (slot_off < 0) { return 0; }
    if (enc_local_slot_ptr_or_addr_arch(arena, elf_ctx, arg_ref, slot_off, ta, ctx) != 0) { return -1; }
    if (enc_push_rax_arch(elf_ctx, ta) != 0) { return -1; }
    if (enc_add_imm_to_rax_arch(elf_ctx, off_a, ta) != 0) { return -1; }
    if (enc_load_32_from_rax_arch(elf_ctx, ta) != 0) { return -1; }
    if (enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return -1; }
    if (enc_pop_rax_arch(elf_ctx, ta) != 0) { return -1; }
    if (enc_add_imm_to_rax_arch(elf_ctx, off_b, ta) != 0) { return -1; }
    if (enc_load_32_from_rax_arch(elf_ctx, ta) != 0) { return -1; }
    if (enc_add_rax_rbx_arch(elf_ctx, ta) != 0) { return -1; }
    return 1;
  }
}

/**
 * ELF CALL simple fold: when same-module `f(x)` and f is an x+K chain, emit arg then add K; skip call/ret.
 * @return 1=folded, 0=no match, -1=error.
 */
export function try_inline_x_plus_k_call_elf(
  arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, e: Expr,
  ctx: *AsmFuncCtx, ta: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let mod_ref: *Module = ctx.module_ref;
    if (mod_ref == 0 as *Module) { return 0; }
    let callee: Expr = ast.ast_arena_expr_get(arena, e.call_callee_ref);
    if (callee.kind != ExprKind.EXPR_VAR) { return 0; }
    let nargs: i32 = pipeline_expr_call_num_args_at(arena, expr_ref);
    if (nargs != 1) { return 0; }
    let fi: i32 = asm_module_func_index_by_name(mod_ref, callee.var_name, callee.var_name_len);
    if (fi < 0) { return 0; }
    let k: i32 = fold_func_x_plus_k_chain(arena, mod_ref, fi, 0);
    if (k < 0) { return 0; }
    let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
    if (arg_ref <= 0) { return -1; }
    if (emit_expr_elf(arena, elf_ctx, arg_ref, ctx, ta) != 0) { return -1; }
    if (k != 0) {
      if (enc_add_imm_to_rax_arch(elf_ctx, k, ta) != 0) { return -1; }
    }
    return 1;
  }
}

/** ELF EXPR_CALL: support import-bound FIELD_ACCESS callee. */
/** Exported function `emit_expr_elf_call`.
 * Implements `emit_expr_elf_call`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param expr_ref i32
 * @param e Expr
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_expr_elf_call(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, e: Expr, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
  }
}


/** Exported function `arch_emit_call`.
 * Implements `arch_emit_call`.
 * @param out *CodegenOutBuf
 * @param name u8[128]
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_call(out: *CodegenOutBuf, name: u8[128], name_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_call(out, name, name_len); }
    if (ta == 2) { return riscv64.emit_call(out, name, name_len); }
    return x86_64.emit_call(out, name, name_len);
  }
}
/** Exported function `arch_emit_jz`.
 * Implements `arch_emit_jz`.
 * @param out *CodegenOutBuf
 * @param label u8[128]
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_jz(out: *CodegenOutBuf, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_jz(out, label, label_len); }
    if (ta == 2) { return riscv64.emit_jz(out, label, label_len); }
    return x86_64.emit_jz(out, label, label_len);
  }
}
/** Match-arm equal branch (beq/je after cmp). */
export function arch_emit_jeq(out: *CodegenOutBuf, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_jeq(out, label, label_len); }
    if (ta == 2) { return riscv64.emit_jeq(out, label, label_len); }
    return x86_64.emit_jeq(out, label, label_len);
  }
}
/** Exported function `arch_emit_jmp`.
 * Implements `arch_emit_jmp`.
 * @param out *CodegenOutBuf
 * @param label u8[128]
 * @param label_len i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_jmp(out: *CodegenOutBuf, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_jmp(out, label, label_len); }
    if (ta == 2) { return riscv64.emit_jmp(out, label, label_len); }
    return x86_64.emit_jmp(out, label, label_len);
  }
}

/** Conditional jump: branch if rax != 0 (LOGOR short-circuit). */
export function arch_emit_jnz(out: *CodegenOutBuf, label: u8[128], label_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_jnz(out, label, label_len); }
    if (ta == 2) { return riscv64.emit_jnz(out, label, label_len); }
    return x86_64.emit_jnz(out, label, label_len);
  }
}

/** Bitwise not/mvn; unary operand in rax. */
export function arch_emit_not_eax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_not_eax(out); }
    if (ta == 2) { return riscv64.emit_not_eax(out); }
    return x86_64.emit_not_eax(out);
  }
}

/** Bitwise and/or/xor: left in rbx, right in rax, result in rax. */
export function arch_emit_and_rbx_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_and_rbx_rax(out); }
    if (ta == 2) { return riscv64.emit_and_rbx_rax(out); }
    return x86_64.emit_and_rbx_rax(out);
  }
}
/** Exported function `arch_emit_or_rbx_rax`.
 * Implements `arch_emit_or_rbx_rax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_or_rbx_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_or_rbx_rax(out); }
    if (ta == 2) { return riscv64.emit_or_rbx_rax(out); }
    return x86_64.emit_or_rbx_rax(out);
  }
}
/** Exported function `arch_emit_xor_rbx_rax`.
 * Implements `arch_emit_xor_rbx_rax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_xor_rbx_rax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_xor_rbx_rax(out); }
    if (ta == 2) { return riscv64.emit_xor_rbx_rax(out); }
    return x86_64.emit_xor_rbx_rax(out);
  }
}

/** Copy rbx to ecx (x86 shift count); unnecessary on arm64. */
export function arch_emit_mov_rbx_to_ecx(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return 0; }
    if (ta == 2) { return riscv64.emit_mov_rbx_to_ecx(out); }
    return x86_64.emit_mov_rbx_to_ecx(out);
  }
}

/** Left / logical-right / arithmetic-right shift: value in rax, count already in rbx (x86 may mov rbx→ecx). */
export function arch_emit_shl_cl_eax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_shl_cl_eax(out); }
    if (ta == 2) { return riscv64.emit_shl_cl_eax(out); }
    return x86_64.emit_shl_cl_eax(out);
  }
}
/** Exported function `arch_emit_shr_cl_eax`.
 * Implements `arch_emit_shr_cl_eax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_shr_cl_eax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_shr_cl_eax(out); }
    if (ta == 2) { return riscv64.emit_shr_cl_eax(out); }
    return x86_64.emit_shr_cl_eax(out);
  }
}
/** Exported function `arch_emit_sar_cl_eax`.
 * Implements `arch_emit_sar_cl_eax`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_sar_cl_eax(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_sar_cl_eax(out); }
    if (ta == 2) { return riscv64.emit_sar_cl_eax(out); }
    return x86_64.emit_sar_cl_eax(out);
  }
}

/** Exported function `arch_emit_label`.
 * Implements `arch_emit_label`.
 * @param out *CodegenOutBuf
 * @param name u8[128]
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_label(out: *CodegenOutBuf, name: u8[128], name_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_label(out, name, name_len); }
    if (ta == 2) { return riscv64.emit_label(out, name, name_len); }
    return x86_64.emit_label(out, name, name_len);
  }
}
/** Exported function `arch_emit_section_text`.
 * Implements `arch_emit_section_text`.
 * @param out *CodegenOutBuf
 * @param ta i32
 * @return i32
 */
export function arch_emit_section_text(out: *CodegenOutBuf, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_section_text(out); }
    if (ta == 2) { return riscv64.emit_section_text(out); }
    return x86_64.emit_section_text(out);
  }
}
/** Exported function `arch_emit_globl`.
 * Implements `arch_emit_globl`.
 * @param out *CodegenOutBuf
 * @param name u8[128]
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_globl(out: *CodegenOutBuf, name: u8[128], name_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_globl(out, name, name_len); }
    if (ta == 2) { return riscv64.emit_globl(out, name, name_len); }
    return x86_64.emit_globl(out, name, name_len);
  }
}
/** Exported function `arch_emit_prologue`.
 * Implements `arch_emit_prologue`.
 * @param out *CodegenOutBuf
 * @param frame_sz i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_prologue(out: *CodegenOutBuf, frame_sz: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_prologue(out, frame_sz); }
    if (ta == 2) { return riscv64.emit_prologue(out, frame_sz); }
    return x86_64.emit_prologue(out, frame_sz);
  }
}
/** Exported function `arch_emit_epilogue`.
 * Implements `arch_emit_epilogue`.
 * @param out *CodegenOutBuf
 * @param frame_sz i32
 * @param ta i32
 * @return i32
 */
export function arch_emit_epilogue(out: *CodegenOutBuf, frame_sz: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ta == 1) { return arm64.emit_epilogue(out, frame_sz); }
    if (ta == 2) { return riscv64.emit_epilogue(out, frame_sz); }
    return x86_64.emit_epilogue(out);
  }
}

/** Read stack offset of local sidecar slot slot_idx. */
export function asm_ctx_slot_offset(ctx: *AsmFuncCtx, slot_idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return asm_ctx_local_offset_at(asm_ctx_key(ctx), slot_idx);
  }
}

/** Stack store width in bytes for a scalar/element type. */
export function asm_scalar_type_byte_sz(arena: *ASTArena, type_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let kind: i32 = 0;
    if (type_ref <= 0) { return 4; }
    kind = pipeline_type_kind_ord_at(arena, type_ref);
    if (kind == TypeKind.TYPE_U8 as i32) { return 1; }
    if (kind == TypeKind.TYPE_PTR as i32 || kind == TypeKind.TYPE_I64 as i32 || kind == TypeKind.TYPE_U64 as i32
        || kind == TypeKind.TYPE_USIZE as i32 || kind == TypeKind.TYPE_ISIZE as i32 || kind == TypeKind.TYPE_F64 as i32) {
      return 8;
    }
    return 4;
  }
}

/** INDEX result element byte width from typeck resolved_type_ref on the INDEX node; default 4. */
export function asm_index_elem_byte_sz(arena: *ASTArena, index_expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_index_elem_byte_sz(arena, index_expr_ref);
  }
}

/** Exported function `asm_array_lit_elem_byte_sz`.
 * Implements `asm_array_lit_elem_byte_sz`.
 * @param arena *ASTArena
 * @param array_lit_ref i32
 * @return i32
 */
export function asm_array_lit_elem_byte_sz(arena: *ASTArena, array_lit_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_array_lit_elem_byte_sz_c(arena, array_lit_ref);
  }
}

/** Exported function `asm_align_up8`.
 * Implements `asm_align_up8`.
 * @param n i32
 * @return i32
 */
export function asm_align_up8(n: i32): i32 {
  let r: i32 = n;
  let m: i32 = n % 8;
  if (m != 0) {
    r = n + (8 - m);
  }
  return r;
}

/**
 * See implementation.
 * See implementation.
 */
export function asm_array_lit_reserve_stack_bytes(arena: *ASTArena, init_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_array_lit_reserve_stack_bytes_c(arena, init_ref);
  }
}

/** Exported function `asm_struct_lit_reserve_stack_bytes`.
 * Implements `asm_struct_lit_reserve_stack_bytes`.
 * @param arena *ASTArena
 * @param init_ref i32
 * @return i32
 */
export function asm_struct_lit_reserve_stack_bytes(arena: *ASTArena, init_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_struct_lit_reserve_stack_bytes_c(arena, init_ref);
  }
}

/** Exported function `asm_init_expr_reserve_stack_bytes`.
 * Implements `asm_init_expr_reserve_stack_bytes`.
 * @param arena *ASTArena
 * @param init_ref i32
 * @return i32
 */
export function asm_init_expr_reserve_stack_bytes(arena: *ASTArena, init_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let n: i32 = asm_array_lit_reserve_stack_bytes(arena, init_ref);
    if (n > 0) {
      return n;
    }
    return asm_struct_lit_reserve_stack_bytes(arena, init_ref);
  }
}

/** Exported function `emit_index_eff_addr_text`.
 * Implements `emit_index_eff_addr_text`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param ix_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @param elem_sz i32
 * @return i32
 */
export function emit_index_eff_addr_text(arena: *ASTArena, out: *CodegenOutBuf, ix_ref: i32, ctx: *AsmFuncCtx, ta: i32, elem_sz: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_index_eff_addr_text_c(arena, out, ix_ref, ctx, ta, elem_sz);
  }
}

/** Exported function `emit_lvalue_eff_addr_text`.
 * Implements `emit_lvalue_eff_addr_text`.
 * @param arena *ASTArena
 * @param ob *CodegenOutBuf
 * @param lval_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_lvalue_eff_addr_text(arena: *ASTArena, ob: *CodegenOutBuf, lval_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_lvalue_eff_addr_text_c(arena, ob, lval_ref, ctx, ta);
  }
}

/** Exported function `emit_expr`.
 * Implements `emit_expr`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param expr_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_expr(arena: *ASTArena, out: *CodegenOutBuf, expr_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_expr_c(arena, out, expr_ref, ctx, target_arch);
  }
}


/**
 * ELF machine-code counterpart of emit_expr: result in %rax/w0, write via enc_* into elf_ctx.code;
 * ta 0=x86_64, 1=arm64.
 */
/** Exported function `emit_expr_elf`.
 * Implements `emit_expr_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param expr_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_expr_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, expr_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_expr_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
  }
}


/** ELF è·¯å¾ INDEX ææå°åè£
å
/** ELF INDEX effective address into rax/x0 (no load). Must be defined after emit_expr_elf for mutual calls. */
/** Exported function `emit_index_eff_addr_elf`.
 * Implements `emit_index_eff_addr_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param ix_ref i32
 * @param ctx *AsmFuncCtx
 * @param elf_ta i32
 * @param elem_sz i32
 * @return i32
 */
export function emit_index_eff_addr_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, ix_ref: i32, ctx: *AsmFuncCtx, elf_ta: i32, elem_sz: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_index_eff_addr_elf_c(arena, elf_ctx, ix_ref, ctx, elf_ta, elem_sz);
  }
}

/** Exported function `emit_lvalue_eff_addr_elf`.
 * Implements `emit_lvalue_eff_addr_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param lval_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_lvalue_eff_addr_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, lval_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, lval_ref, ctx, ta);
  }
}

/** Exported function `emit_block_inits_elf`.
 * Implements `emit_block_inits_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param block_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @param slot_base i32
 * @return i32
 */
export function emit_block_inits_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, ctx: *AsmFuncCtx, ta: i32, slot_base: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_block_inits_elf_c(arena, elf_ctx, block_ref, ctx, ta, slot_base);
  }
}


/** Whether two EXPR_VAR nodes share a name (via pipeline name readers; avoid AST field tear). */
export function fold_expr_var_refs_same(arena: *ASTArena, a_ref: i32, b_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, a_ref) != 3) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, b_ref) != 3) { return 0; }
    let alen: i32 = pipeline_expr_var_name_len(arena, a_ref);
    let blen: i32 = pipeline_expr_var_name_len(arena, b_ref);
    if (alen <= 0 || alen != blen) { return 0; }
    let abuf: u8[128] = [];
    let bbuf: u8[128] = [];
    pipeline_expr_var_name_into(arena, a_ref, &abuf[0]);
    pipeline_expr_var_name_into(arena, b_ref, &bbuf[0]);
    let k: i32 = 0;
    while (k < alen) {
      if (abuf[k] != bbuf[k]) { return 0; }
      k = k + 1;
    }
    return 1;
  }
}

/**
 * Whether `target = target + addend` with addend an EXPR_LIT immediate.
 * On success write addend into *out_addend; target_ref is the LHS VAR expr ref.
 */
export function fold_is_assign_var_add_lit(arena: *ASTArena, expr_ref: i32, target_ref: i32, out_addend: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, expr_ref);
    let right_ref: i32 = asm_expr_binop_right(arena, expr_ref);
    if (left_ref <= 0 || right_ref <= 0) { return 0; }
    if (fold_expr_var_refs_same(arena, left_ref, target_ref) == 0) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, right_ref) != 4) { return 0; }
    let add_l: i32 = asm_expr_binop_left(arena, right_ref);
    let add_r: i32 = asm_expr_binop_right(arena, right_ref);
    if (fold_expr_var_refs_same(arena, add_l, target_ref) == 0) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, add_r) != 0) { return 0; }
    if (out_addend != 0 as *i32) {
      out_addend[0] = pipeline_expr_int_val_at(arena, add_r);
    }
    return 1;
  }
}

/** Whether block stmt_order contains call / nested loop (blocks constant fold). */
export function fold_body_has_call_or_nested_loop(arena: *ASTArena, body_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let nso: i32 = ast.ast_block_num_stmt_order(arena, body_ref);
    let i: i32 = 0;
    while (i < nso) {
      let item_kind: u8 = ast.ast_block_stmt_order_kind(arena, body_ref, i);
      if (item_kind == 3 || item_kind == 4) { return 1; }
      if (item_kind == 2) {
        let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, i);
        if (idx >= 0 && idx < ast.ast_block_num_expr_stmts(arena, body_ref)) {
          let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
          if (er > 0) {
            let ek: i32 = pipeline_expr_kind_ord_at(arena, er);
            if (ek == 48 || ek == 49) { return 1; }
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Parse `while (i < n)`: left VAR i; right VAR n or LIT n.
 * On success write *out_i_ref, *out_n_is_lit, and *out_n_lit (literal) or *out_n_ref (var).
 */
export function fold_parse_while_lt_i_n(
  arena: *ASTArena, cond_ref: i32,
  out_i_ref: *i32, out_n_is_lit: *i32, out_n_lit: *i32, out_n_ref: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, cond_ref) != 16) { return 0; }
    let i_ref: i32 = asm_expr_binop_left(arena, cond_ref);
    let n_side: i32 = asm_expr_binop_right(arena, cond_ref);
    if (pipeline_expr_kind_ord_at(arena, i_ref) != 3) { return 0; }
    if (out_i_ref != 0 as *i32) {
      out_i_ref[0] = i_ref;
    }
    if (pipeline_expr_kind_ord_at(arena, n_side) == 0) {
      if (out_n_is_lit != 0 as *i32) { out_n_is_lit[0] = 1; }
      if (out_n_lit != 0 as *i32) { out_n_lit[0] = pipeline_expr_int_val_at(arena, n_side); }
      if (out_n_ref != 0 as *i32) { out_n_ref[0] = 0; }
      return 1;
    }
    if (pipeline_expr_kind_ord_at(arena, n_side) == 3) {
      if (out_n_is_lit != 0 as *i32) { out_n_is_lit[0] = 0; }
      if (out_n_lit != 0 as *i32) { out_n_lit[0] = 0; }
      if (out_n_ref != 0 as *i32) { out_n_ref[0] = n_side; }
      return 1;
    }
    return 0;
  }
}

/**
 * Whether `s = s + (i + K)` or `s = s + f(i)` (f is x+K chain); on success write out_s_ref, out_k.
 */
export function fold_affine_i_plus_k_expr(arena: *ASTArena, mod: *Module, expr_ref: i32, i_ref: i32, out_k: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let rk: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (rk == 48) {
      if (pipeline_expr_call_num_args_at(arena, expr_ref) != 1) { return 0; }
      let arg0: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
      if (fold_expr_var_refs_same(arena, arg0, i_ref) == 0) { return 0; }
      let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      if (callee_ref <= 0 || pipeline_expr_kind_ord_at(arena, callee_ref) != 3) { return 0; }
      let cname: u8[128] = [];
      pipeline_expr_var_name_into(arena, callee_ref, &cname[0]);
      let fi: i32 = asm_module_func_index_by_name(mod, &cname[0], pipeline_expr_var_name_len(arena, callee_ref));
      if (fi < 0) { return 0; }
      let kk: i32 = fold_func_x_plus_k_chain(arena, mod, fi, 0);
      if (kk < 0) { return 0; }
      if (out_k != 0 as *i32) { out_k[0] = kk; }
      return 1;
    }
    if (fold_expr_is_add_kind(arena, expr_ref) == 0) { return 0; }
    let al: i32 = asm_expr_binop_left(arena, expr_ref);
    let ar: i32 = asm_expr_binop_right(arena, expr_ref);
    let k_lit: i32 = 0;
    if (fold_expr_var_refs_same(arena, al, i_ref) != 0 && pipeline_expr_kind_ord_at(arena, ar) == 0) {
      k_lit = pipeline_expr_int_val_at(arena, ar);
    } else if (fold_expr_var_refs_same(arena, ar, i_ref) != 0 && pipeline_expr_kind_ord_at(arena, al) == 0) {
      k_lit = pipeline_expr_int_val_at(arena, al);
    } else {
      return 0;
    }
    if (out_k != 0 as *i32) { out_k[0] = k_lit; }
    return 1;
  }
}

/** Function `fold_is_assign_s_plus_affine_i`.
 * Purpose: implements `fold_is_assign_s_plus_affine_i`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
export function fold_is_assign_s_plus_affine_i(
  arena: *ASTArena, mod: *Module, expr_ref: i32, i_ref: i32, out_s_ref: *i32, out_k: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, expr_ref);
    let right_ref: i32 = asm_expr_binop_right(arena, expr_ref);
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 3) { return 0; }
    let inner: i32 = right_ref;
    if (fold_expr_is_add_kind(arena, right_ref) != 0) {
      let add_l: i32 = asm_expr_binop_left(arena, right_ref);
      if (fold_expr_var_refs_same(arena, add_l, left_ref) == 0) { return 0; }
      inner = asm_expr_binop_right(arena, right_ref);
    }
    let kk: i32 = 0;
    if (fold_affine_i_plus_k_expr(arena, mod, inner, i_ref, &kk) == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = left_ref; }
    if (out_k != 0 as *i32) { out_k[0] = kk; }
    return 1;
  }
}

/** Parse `s += (i+K); i++` two-statement loop body (call_boundary etc.). */
export function fold_parse_affine_sum_body(
  arena: *ASTArena, mod: *Module, body_ref: i32, i_ref: i32, out_s_ref: *i32, out_k: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let nso: i32 = ast.ast_block_num_stmt_order(arena, body_ref);
    if (nso != 2) { return 0; }
    let found_s: i32 = 0;
    let found_i: i32 = 0;
    let s_ref: i32 = 0;
    let k_v: i32 = 0;
    let j: i32 = 0;
    while (j < nso) {
      if (ast.ast_block_stmt_order_kind(arena, body_ref, j) != 2) { return 0; }
      let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, j);
      if (idx < 0 || idx >= ast.ast_block_num_expr_stmts(arena, body_ref)) { return 0; }
      let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
      if (er <= 0) { return 0; }
      let addend: i32 = 0;
      if (fold_is_assign_var_add_lit(arena, er, i_ref, &addend) != 0 && addend == 1) {
        found_i = 1;
      } else {
        let kk: i32 = 0;
        let sr: i32 = 0;
        if (fold_is_assign_s_plus_affine_i(arena, mod, er, i_ref, &sr, &kk) != 0) {
          if (found_s != 0) { return 0; }
          found_s = 1;
          s_ref = sr;
          k_v = kk;
        } else {
          return 0;
        }
      }
      j = j + 1;
    }
    if (found_s == 0 || found_i == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = s_ref; }
    if (out_k != 0 as *i32) { out_k[0] = k_v; }
    return 1;
  }
}

/** Whether expression is a field access on func's parameter 0 (`p.a` etc.). */
export function fold_expr_is_param0_field_access(arena: *ASTArena, mod: *Module, func_idx: i32, expr_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 44) { return 0; }
    let base_ref: i32 = pipeline_expr_field_access_base_ref(arena, expr_ref);
    return fold_expr_is_func_param0(arena, mod, func_idx, base_ref);
  }
}

/** Whether function body is `return p.f0 + p.f1` (both fields from param0). */
export function fold_func_returns_param0_field_sum(arena: *ASTArena, mod: *Module, func_idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let ret_ref: i32 = fold_func_return_operand_ref(arena, mod, func_idx);
    if (ret_ref <= 0) { return 0; }
    if (fold_expr_is_add_kind(arena, ret_ref) == 0) { return 0; }
    let al: i32 = asm_expr_binop_left(arena, ret_ref);
    let ar: i32 = asm_expr_binop_right(arena, ret_ref);
    if (fold_expr_is_param0_field_access(arena, mod, func_idx, al) == 0) { return 0; }
    if (fold_expr_is_param0_field_access(arena, mod, func_idx, ar) == 0) { return 0; }
    return 1;
  }
}

/** Exported function `fold_func_returns_param0_single_field`.
 * Implements `fold_func_returns_param0_single_field`.
 * @param arena *ASTArena
 * @param mod *Module
 * @param func_idx i32
 * @return i32
 */
export function fold_func_returns_param0_single_field(arena: *ASTArena, mod: *Module, func_idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let ret_ref: i32 = fold_func_return_operand_ref(arena, mod, func_idx);
    if (ret_ref <= 0) { return 0; }
    return fold_expr_is_param0_field_access(arena, mod, func_idx, ret_ref);
  }
}

/**
 * If var is a same-block let whose init is STRUCT_LIT, sum all i32 literal fields into *out_sum.
 * Used for `let p = Pair { a: 1, b: 2 }` → 3.
 */
export function fold_block_let_struct_lit_i32_sum(arena: *ASTArena, block_ref: i32, var_ref: i32, out_sum: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, var_ref) != 3) { return 0; }
    let vlen: i32 = pipeline_expr_var_name_len(arena, var_ref);
    if (vlen <= 0 || vlen > 127) { return 0; }
    let vbuf: u8[128] = [];
    pipeline_expr_var_name_into(arena, var_ref, &vbuf[0]);
    let nlet: i32 = ast.ast_block_num_lets(arena, block_ref);
    let li: i32 = 0;
    while (li < nlet) {
      let llen: i32 = pipeline_block_let_name_len(arena, block_ref, li);
      if (llen == vlen) {
        let is_match: i32 = 1;
        let lb: u8[128] = [];
        pipeline_block_let_name_copy64(arena, block_ref, li, &lb[0]);
        let kk: i32 = 0;
        while (kk < vlen) {
          if (lb[kk] != vbuf[kk]) { is_match = 0; }
          kk = kk + 1;
        }
        if (is_match != 0) {
          let init_ref: i32 = pipeline_block_let_init_ref(arena, block_ref, li);
          if (init_ref <= 0 || pipeline_expr_kind_ord_at(arena, init_ref) != 45) { return 0; }
          let nf: i32 = pipeline_expr_struct_lit_num_fields(arena, init_ref);
          if (nf <= 0) { return 0; }
          let sum_v: i32 = 0;
          let fj: i32 = 0;
          while (fj < nf) {
            let fv: i32 = pipeline_expr_struct_lit_init_ref(arena, init_ref, fj);
            if (fv <= 0 || pipeline_expr_kind_ord_at(arena, fv) != 0) { return 0; }
            sum_v = sum_v + pipeline_expr_int_val_at(arena, fv);
            fj = fj + 1;
          }
          if (out_sum != 0 as *i32) { out_sum[0] = sum_v; }
          return 1;
        }
      }
      li = li + 1;
    }
    return 0;
  }
}

/** Exported function `fold_field_assign_pair_base_ref`.
 * Implements `fold_field_assign_pair_base_ref`.
 * @param arena *ASTArena
 * @param er i32
 * @return i32
 */
export function fold_field_assign_pair_base_ref(arena: *ASTArena, er: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, er) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, er);
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 44) { return 0; }
    return pipeline_expr_field_access_base_ref(arena, left_ref);
  }
}

/* See implementation. */
export function fold_is_field_assign_from_var(
  arena: *ASTArena, er: i32, pair_ref: i32, field_ch: u8, src_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, er) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, er);
    let right_ref: i32 = asm_expr_binop_right(arena, er);
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 44) { return 0; }
    if (fold_expr_var_refs_same(arena, pipeline_expr_field_access_base_ref(arena, left_ref), pair_ref) == 0) {
      return 0;
    }
    if (pipeline_expr_field_access_name_len(arena, left_ref) != 1) { return 0; }
    let fn: u8[128] = [];
    pipeline_expr_field_access_name_into(arena, left_ref, &fn[0]);
    if (fn[0] != field_ch) { return 0; }
    return fold_expr_var_refs_same(arena, right_ref, src_ref);
  }
}

/** Exported function `fold_is_field_assign_i_plus_one`.
 * Implements `fold_is_field_assign_i_plus_one`.
 * @param arena *ASTArena
 * @param er i32
 * @param pair_ref i32
 * @param i_ref i32
 * @return i32
 */
export function fold_is_field_assign_i_plus_one(arena: *ASTArena, er: i32, pair_ref: i32, i_ref: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, er) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, er);
    let right_ref: i32 = asm_expr_binop_right(arena, er);
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 44) { return 0; }
    if (fold_expr_var_refs_same(arena, pipeline_expr_field_access_base_ref(arena, left_ref), pair_ref) == 0) {
      return 0;
    }
    if (pipeline_expr_field_access_name_len(arena, left_ref) != 1) { return 0; }
    let fn: u8[128] = [];
    pipeline_expr_field_access_name_into(arena, left_ref, &fn[0]);
    if (fn[0] != 98 as u8) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, right_ref) != 4) { return 0; }
    let add_l: i32 = asm_expr_binop_left(arena, right_ref);
    let add_r: i32 = asm_expr_binop_right(arena, right_ref);
    if (fold_expr_var_refs_same(arena, add_l, i_ref) == 0) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, add_r) != 0) { return 0; }
    if (pipeline_expr_int_val_at(arena, add_r) != 1) { return 0; }
    return 1;
  }
}

/* See implementation. */
export function fold_is_assign_s_plus_pair_field_sum_call(
  arena: *ASTArena, mod: *Module, er: i32, pair_ref: i32, out_s_ref: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, er) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, er);
    let right_ref: i32 = asm_expr_binop_right(arena, er);
    if (fold_expr_is_add_kind(arena, right_ref) == 0) { return 0; }
    let add_l: i32 = asm_expr_binop_left(arena, right_ref);
    let inner: i32 = asm_expr_binop_right(arena, right_ref);
    if (fold_expr_var_refs_same(arena, add_l, left_ref) == 0) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, inner) != 48) { return 0; }
    if (pipeline_expr_call_num_args_at(arena, inner) != 1) { return 0; }
    let arg0: i32 = pipeline_expr_call_arg_ref(arena, inner, 0);
    if (fold_expr_var_refs_same(arena, arg0, pair_ref) == 0) { return 0; }
    let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, inner);
    if (callee_ref <= 0 || pipeline_expr_kind_ord_at(arena, callee_ref) != 3) { return 0; }
    let cname: u8[128] = [];
    pipeline_expr_var_name_into(arena, callee_ref, &cname[0]);
    let fi: i32 = asm_module_func_index_by_name(mod, &cname[0], pipeline_expr_var_name_len(arena, callee_ref));
    if (fi < 0) { return 0; }
    if (fold_func_returns_param0_field_sum(arena, mod, fi) == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = left_ref; }
    return 1;
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function fold_parse_struct_pair_n2_body(
  arena: *ASTArena, mod: *Module, body_ref: i32, i_ref: i32, out_s_ref: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (ast.ast_block_num_stmt_order(arena, body_ref) != 4) { return 0; }
    let pair_ref: i32 = 0;
    let s_ref: i32 = 0;
    let found_a: i32 = 0;
    let found_b: i32 = 0;
    let found_call: i32 = 0;
    let found_i: i32 = 0;
    let si: i32 = 0;
    while (si < 4) {
      if (ast.ast_block_stmt_order_kind(arena, body_ref, si) != 2) { return 0; }
      let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, si);
      if (idx < 0 || idx >= ast.ast_block_num_expr_stmts(arena, body_ref)) { return 0; }
      let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
      if (er <= 0) { return 0; }
      let addend: i32 = 0;
      if (fold_is_assign_var_add_lit(arena, er, i_ref, &addend) != 0 && addend == 1) {
        found_i = 1;
      } else {
        if (pair_ref == 0) {
          pair_ref = fold_field_assign_pair_base_ref(arena, er);
        }
        if (pair_ref > 0 && fold_is_field_assign_from_var(arena, er, pair_ref, 97 as u8, i_ref) != 0) {
          found_a = 1;
        } else if (pair_ref > 0 && fold_is_field_assign_i_plus_one(arena, er, pair_ref, i_ref) != 0) {
          found_b = 1;
        } else if (pair_ref > 0 && fold_is_assign_s_plus_pair_field_sum_call(arena, mod, er, pair_ref, &s_ref) != 0) {
          found_call = 1;
        } else {
          return 0;
        }
      }
      si = si + 1;
    }
    if (found_a == 0 || found_b == 0 || found_call == 0 || found_i == 0 || s_ref <= 0 || pair_ref <= 0) {
      return 0;
    }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = s_ref; }
    return 1;
  }
}

/**
 * Whether `s = s + add_pair(p)` with add_pair = param0 field-sum and p a const struct lit.
 * On success write out_s_ref, out_step (per-iteration constant delta).
 */
export function fold_is_assign_s_plus_const_field_call(
  arena: *ASTArena, mod: *Module, block_ref: i32, expr_ref: i32, out_s_ref: *i32, out_step: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 28) { return 0; }
    let left_ref: i32 = asm_expr_binop_left(arena, expr_ref);
    let right_ref: i32 = asm_expr_binop_right(arena, expr_ref);
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 3) { return 0; }
    let inner: i32 = right_ref;
    if (fold_expr_is_add_kind(arena, right_ref) != 0) {
      let add_l: i32 = asm_expr_binop_left(arena, right_ref);
      if (fold_expr_var_refs_same(arena, add_l, left_ref) == 0) { return 0; }
      inner = asm_expr_binop_right(arena, right_ref);
    }
    if (pipeline_expr_kind_ord_at(arena, inner) != 48) { return 0; }
    if (pipeline_expr_call_num_args_at(arena, inner) != 1) { return 0; }
    let arg0: i32 = pipeline_expr_call_arg_ref(arena, inner, 0);
    if (pipeline_expr_kind_ord_at(arena, arg0) != 3) { return 0; }
    let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, inner);
    if (callee_ref <= 0 || pipeline_expr_kind_ord_at(arena, callee_ref) != 3) { return 0; }
    let cname: u8[128] = [];
    pipeline_expr_var_name_into(arena, callee_ref, &cname[0]);
    let fi: i32 = asm_module_func_index_by_name(mod, &cname[0], pipeline_expr_var_name_len(arena, callee_ref));
    if (fi < 0) { return 0; }
    if (fold_func_returns_param0_field_sum(arena, mod, fi) == 0) { return 0; }
    let step_v: i32 = 0;
    if (fold_block_let_struct_lit_i32_sum(arena, block_ref, arg0, &step_v) == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = left_ref; }
    if (out_step != 0 as *i32) { out_step[0] = step_v; }
    return 1;
  }
}

/** Parse `s += add_pair(const p); i++` (struct_param etc.). */
export function fold_parse_count_up_const_field_call_body(
  arena: *ASTArena, mod: *Module, block_ref: i32, body_ref: i32, i_ref: i32,
  out_s_ref: *i32, out_step: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let nso: i32 = ast.ast_block_num_stmt_order(arena, body_ref);
    if (nso != 2) { return 0; }
    let found_s: i32 = 0;
    let found_i: i32 = 0;
    let s_ref: i32 = 0;
    let step_v: i32 = 0;
    let j: i32 = 0;
    while (j < nso) {
      if (ast.ast_block_stmt_order_kind(arena, body_ref, j) != 2) { return 0; }
      let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, j);
      if (idx < 0 || idx >= ast.ast_block_num_expr_stmts(arena, body_ref)) { return 0; }
      let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
      if (er <= 0) { return 0; }
      let addend: i32 = 0;
      if (fold_is_assign_var_add_lit(arena, er, i_ref, &addend) != 0 && addend == 1) {
        found_i = 1;
      } else {
        let st: i32 = 0;
        let sr: i32 = 0;
        if (fold_is_assign_s_plus_const_field_call(arena, mod, block_ref, er, &sr, &st) != 0) {
          if (found_s != 0) { return 0; }
          found_s = 1;
          s_ref = sr;
          step_v = st;
        } else {
          return 0;
        }
      }
      j = j + 1;
    }
    if (found_s == 0 || found_i == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = s_ref; }
    if (out_step != 0 as *i32) { out_step[0] = step_v; }
    return 1;
  }
}

/** Parse count-up loop body: the two assigns `s = s + step` and `i = i + 1` (order irrelevant). */
export function fold_parse_count_up_body(
  arena: *ASTArena, body_ref: i32, i_ref: i32, out_s_ref: *i32, out_step: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let nso: i32 = ast.ast_block_num_stmt_order(arena, body_ref);
    if (nso != 2) { return 0; }
    let found_s: i32 = 0;
    let found_i: i32 = 0;
    let s_ref: i32 = 0;
    let step_v: i32 = 0;
    let j: i32 = 0;
    while (j < nso) {
      if (ast.ast_block_stmt_order_kind(arena, body_ref, j) != 2) { return 0; }
      let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, j);
      if (idx < 0 || idx >= ast.ast_block_num_expr_stmts(arena, body_ref)) { return 0; }
      let er: i32 = ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
      if (er <= 0) { return 0; }
      let addend: i32 = 0;
      if (fold_is_assign_var_add_lit(arena, er, i_ref, &addend) != 0 && addend == 1) {
        found_i = 1;
      } else {
        let addend_s: i32 = 0;
        let left_ref: i32 = asm_expr_binop_left(arena, er);
        if (fold_is_assign_var_add_lit(arena, er, left_ref, &addend_s) != 0) {
          if (found_s != 0) { return 0; }
          found_s = 1;
          s_ref = left_ref;
          step_v = addend_s;
        } else {
          return 0;
        }
      }
      j = j + 1;
    }
    if (found_s == 0 || found_i == 0) { return 0; }
    if (out_s_ref != 0 as *i32) { out_s_ref[0] = s_ref; }
    if (out_step != 0 as *i32) { out_step[0] = step_v; }
    return 1;
  }
}

/**
 * If var_ref is a same-block let bound to an integer literal, write *out_lit and return 1.
 * Used for const-prop of `let n: i32 = 1000000000; while (i < n)`.
 */
export function fold_block_let_init_lit(arena: *ASTArena, block_ref: i32, var_ref: i32, out_lit: *i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (pipeline_expr_kind_ord_at(arena, var_ref) != 3) { return 0; }
    let vlen: i32 = pipeline_expr_var_name_len(arena, var_ref);
    if (vlen <= 0 || vlen > 127) { return 0; }
    let vbuf: u8[128] = [];
    pipeline_expr_var_name_into(arena, var_ref, &vbuf[0]);
    let nlet: i32 = ast.ast_block_num_lets(arena, block_ref);
    let li: i32 = 0;
    while (li < nlet) {
      let llen: i32 = pipeline_block_let_name_len(arena, block_ref, li);
      if (llen == vlen) {
        let is_match: i32 = 1;
        let lb: u8[128] = [];
        pipeline_block_let_name_copy64(arena, block_ref, li, &lb[0]);
        let kk: i32 = 0;
        while (kk < vlen) {
          if (lb[kk] != vbuf[kk]) { is_match = 0; }
          kk = kk + 1;
        }
        if (is_match != 0) {
          let init_ref: i32 = pipeline_block_let_init_ref(arena, block_ref, li);
          if (init_ref > 0 && pipeline_expr_kind_ord_at(arena, init_ref) == 0) {
            if (out_lit != 0 as *i32) {
              out_lit[0] = pipeline_expr_int_val_at(arena, init_ref);
            }
            return 1;
          }
          return 0;
        }
      }
      li = li + 1;
    }
    return 0;
  }
}

/** Emit `i >= n` branch to exit (must follow cmp); use imm cmp when n is literal. */
export function fold_emit_i_ge_n_branch_exit_elf(
  elf_ctx: *ElfCodegenCtx, off_i: i32, off_n: i32, n_is_lit: i32, n_lit: i32,
  exit_buf: u8[128], exit_len: i32, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (n_is_lit != 0) {
      if (enc_load_rbp_to_rax_arch(elf_ctx, off_i, ta) != 0) { return -1; }
      if (enc_cmp_w0_imm12_arch(elf_ctx, n_lit, ta) != 0) { return -1; }
    } else {
      /* See implementation. */
      if (enc_load_rbp_to_rax_arch(elf_ctx, off_i, ta) != 0) { return -1; }
      if (enc_load_rbp_to_rbx_arch(elf_ctx, off_n, ta) != 0) { return -1; }
      if (enc_cmp_rax_rbx_arch(elf_ctx, ta) != 0) { return -1; }
    }
    return enc_jge_arch(elf_ctx, exit_buf, exit_len, ta);
  }
}

/**
 * ELF: try optimize `while (i < n) { s += step; i += 1; }`.
 * 1) If n is a compile-time constant and body has no call → write n*step into s directly;
 * 2) Else if condition is i<n → replace cset condition with cmp+jge, then emit original body.
 * @return 1=folded, 0=no match, -1=error.
 */
export function try_fold_count_up_while_elf(
  arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, loop_idx: i32,
  ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let cond_ref: i32 = ast.ast_block_while_cond_ref(arena, block_ref, loop_idx);
    let body_ref: i32 = ast.ast_block_while_body_ref(arena, block_ref, loop_idx);
    if (cond_ref <= 0 || body_ref <= 0) { return 0; }
    let i_ref: i32 = 0;
    let n_is_lit: i32 = 0;
    let n_lit: i32 = 0;
    let n_var_ref: i32 = 0;
    if (fold_parse_while_lt_i_n(arena, cond_ref, &i_ref, &n_is_lit, &n_lit, &n_var_ref) == 0) {
      return 0;
    }
    let i_e: Expr = ast.ast_arena_expr_get(arena, i_ref);
    let off_i: i32 = local_offset(ctx, i_e.var_name, i_e.var_name_len);
    if (off_i < 0) { return 0; }
    let off_n: i32 = -1;
    let n_e: Expr = ast.ast_arena_expr_get(arena, n_var_ref);
    if (n_is_lit == 0) {
      off_n = local_offset(ctx, n_e.var_name, n_e.var_name_len);
      if (off_n < 0) { return 0; }
    }
    let s_ref: i32 = 0;
    let step_v: i32 = 0;
    let simple_body: i32 = fold_parse_count_up_body(arena, body_ref, i_ref, &s_ref, &step_v);
    let has_call: i32 = fold_body_has_call_or_nested_loop(arena, body_ref);
    let n_const: i32 = n_lit;
    let n_const_ok: i32 = n_is_lit;
    let n_from_let: i32 = 0;
    if (n_const_ok == 0 && n_var_ref > 0) {
      if (fold_block_let_init_lit(arena, block_ref, n_var_ref, &n_from_let) != 0) {
        n_const = n_from_let;
        n_const_ok = 1;
      }
    }
    /** Const n + `s += (i+K); i++`: ∑(i+K)=n(n-1)/2+Kn (call_boundary etc.). */
    let affine_s: i32 = 0;
    let affine_k: i32 = 0;
    let s_ea: Expr = ast.ast_arena_expr_get(arena, affine_s);
    let off_sa: i32 = -1;
    let nm1: i32 = 0;
    let sum_i: i32 = 0;
    let sum_k: i32 = 0;
    let total: i32 = 0;
    if (n_const_ok != 0 && ctx.module_ref != 0 as *Module
        && fold_parse_affine_sum_body(arena, ctx.module_ref, body_ref, i_ref, &affine_s, &affine_k) != 0) {
      off_sa = local_offset(ctx, s_ea.var_name, s_ea.var_name_len);
      if (off_sa < 0) { return 0; }
      nm1 = n_const - 1;
      sum_i = nm1 * n_const / 2;
      sum_k = affine_k * n_const;
      total = sum_i + sum_k;
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, total, ta) != 0) { return -1; }
      if (enc_store_rax_to_rbp_arch(elf_ctx, off_sa, ta) != 0) { return -1; }
      return 1;
    }
    /* See implementation. */
    let struct_n2_s: i32 = 0;
    let s_e2: Expr = ast.ast_arena_expr_get(arena, 0);
    let off_s2: i32 = -1;
    let prod_n2: i32 = 0;
    if (0 != 0) {
      if (n_const_ok != 0 && ctx.module_ref != 0 as *Module
          && fold_parse_struct_pair_n2_body(arena, ctx.module_ref, body_ref, i_ref, &struct_n2_s) != 0) {
        s_e2 = ast.ast_arena_expr_get(arena, struct_n2_s);
        off_s2 = local_offset(ctx, s_e2.var_name, s_e2.var_name_len);
        if (off_s2 < 0) { return 0; }
        prod_n2 = n_const * n_const;
        if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, prod_n2, ta) != 0) { return -1; }
        if (enc_store_rax_to_rbp_arch(elf_ctx, off_s2, ta) != 0) { return -1; }
        return 1;
      }
    }
    /** Const n + `s += add_pair(const p); i++`: s = n * ∑fields (struct_param etc.). */
    let struct_s: i32 = 0;
    let struct_step: i32 = 0;
    let s_es: Expr = ast.ast_arena_expr_get(arena, 0);
    let off_ss: i32 = -1;
    let prod_s: i32 = 0;
    if (n_const_ok != 0 && ctx.module_ref != 0 as *Module
        && fold_parse_count_up_const_field_call_body(arena, ctx.module_ref, block_ref, body_ref, i_ref, &struct_s, &struct_step) != 0) {
      s_es = ast.ast_arena_expr_get(arena, struct_s);
      off_ss = local_offset(ctx, s_es.var_name, s_es.var_name_len);
      if (off_ss < 0) { return 0; }
      prod_s = n_const * struct_step;
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, prod_s, ta) != 0) { return -1; }
      if (enc_store_rax_to_rbp_arch(elf_ctx, off_ss, ta) != 0) { return -1; }
      return 1;
    }
    /** Const n + pure increment body: fold to s = n * step (loop_i32 etc.). */
    let s_e: Expr = ast.ast_arena_expr_get(arena, s_ref);
    let off_s: i32 = -1;
    let prod: i32 = 0;
    if (simple_body != 0 && has_call == 0 && n_const_ok != 0) {
      off_s = local_offset(ctx, s_e.var_name, s_e.var_name_len);
      if (off_s < 0) { return 0; }
      prod = n_const * step_v;
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, prod, ta) != 0) { return -1; }
      if (enc_store_rax_to_rbp_arch(elf_ctx, off_s, ta) != 0) { return -1; }
      return 1;
    }
    /** Const n + `s += (i+K); i++`: ∑(i+K)=n(n-1)/2+Kn (call_boundary etc.). */
    let loop_buf: u8[128] = [];
    let exit_buf: u8[128] = [];
    let loop_len: i32 = emit_next_label(ctx, loop_buf, 20);
    let exit_len: i32 = emit_next_label(ctx, exit_buf, 20);
    if (enc_label_arch(elf_ctx, loop_buf, loop_len, 0, ta) != 0) { return -1; }
    /* See implementation. */
    if (fold_emit_i_ge_n_branch_exit_elf(elf_ctx, off_i, off_n, n_const_ok, n_const, exit_buf, exit_len, ta) != 0) {
      return -1;
    }
    if (ctx_push_loop_labels(ctx, exit_buf, exit_len, loop_buf, loop_len) != 0) { return -1; }
    if (emit_loop_body_content_elf(arena, elf_ctx, body_ref, ctx, ta) != 0) {
      ctx_pop_loop_labels(ctx);
      return -1;
    }
    if (enc_jmp_arch(elf_ctx, loop_buf, loop_len, ta) != 0) { ctx_pop_loop_labels(ctx); return -1; }
    if (enc_label_arch(elf_ctx, exit_buf, exit_len, 0, ta) != 0) { ctx_pop_loop_labels(ctx); return -1; }
    ctx_pop_loop_labels(ctx);
    return 1;

  }
}

/** ELF path: while loop. ta 0=x86_64, 1=arm64. */
/** Exported function `emit_while_loop_elf`.
 * Implements `emit_while_loop_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param block_ref i32
 * @param loop_idx i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_while_loop_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, loop_idx: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_while_loop_elf_c(arena, elf_ctx, block_ref, loop_idx, ctx, ta);
  }
}


/** ELF path: for loop. ta 0=x86_64, 1=arm64. */
/** Exported function `emit_for_loop_elf`.
 * Implements `emit_for_loop_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param block_ref i32
 * @param for_idx i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_for_loop_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, for_idx: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_for_loop_elf_c(arena, elf_ctx, block_ref, for_idx, ctx, ta);
  }
}


/**
 * ELF path: emit block body by stmt_order via backend_emit_block_body_sync_elf
 * (runtime_pipeline_abi / backend seed; historical pipeline_glue.c C for-loop
 * left wave309). X while(i<nso) under selfhost xlang-c -E may run only one
 * iteration and drop the return 1+2 left operand — prefer the C sync path.
 */
export function emit_block_body_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, block_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return backend_emit_block_body_sync_elf(arena, elf_ctx, block_ref, ctx, ta);
  }
}

/**
 * Emit block const/let initializers; slot_base is this block's start index in ctx local sidecar.
 * Nested blocks under EXPR_BLOCK call fill_local_slots then this function; slot_base is
 * ctx.num_locals before the fill.
 */
/** Exported function `emit_block_inits`.
 * Implements `emit_block_inits`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param block_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @param slot_base i32
 * @return i32
 */
export function emit_block_inits(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32, slot_base: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_block_inits_c(arena, out, block_ref, ctx, target_arch, slot_base);
  }
}


/** Generate a unique local label into buf; return length. Format ".L_" + digits. */
/** Exported function `emit_next_label`.
 * Implements `emit_next_label`.
 * @param ctx *AsmFuncCtx
 * @param buf *u8
 * @param buf_size i32
 * @return i32
 */
export function emit_next_label(ctx: *AsmFuncCtx, buf: *u8, buf_size: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_next_label_c(ctx, buf, buf_size);
  }
}


/** Format label ordinal id as ".L_<id>" into buf; return length (does not advance ctx.label_counter). For match multi-arm labels. */
/** Exported function `format_label_id`.
 * Implements `format_label_id`.
 * @param buf *u8
 * @param buf_size i32
 * @param id i32
 * @return i32
 */
export function format_label_id(buf: *u8, buf_size: i32, id: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_format_label_id_c(buf, buf_size, id);
  }
}


/** Push break/continue labels onto the 8-deep stack and make them current; return -1 if d>=8. */
export function ctx_push_loop_labels(ctx: *AsmFuncCtx, exit_buf: *u8, exit_len: i32, loop_buf: *u8, loop_len: i32): i32 {
  let d: i32 = ctx.loop_label_depth;
  if (d >= 8) {
    return -1;
  }
  let base_off: i32 = d * 64;
  let k: i32 = 0;
  while (k < exit_len && k < 64) {
    ctx.loop_break_label_stack[base_off + k] = exit_buf[k];
    k = k + 1;
  }
  ctx.loop_break_len_stack[d] = exit_len;
  k = 0;
  while (k < loop_len && k < 64) {
    ctx.loop_continue_label_stack[base_off + k] = loop_buf[k];
    k = k + 1;
  }
  ctx.loop_continue_len_stack[d] = loop_len;
  ctx.loop_label_depth = d + 1;
  k = 0;
  while (k < exit_len && k < 64) {
    ctx.break_label[k] = exit_buf[k];
    k = k + 1;
  }
  ctx.break_len = exit_len;
  k = 0;
  while (k < loop_len && k < 64) {
    ctx.continue_label[k] = loop_buf[k];
    k = k + 1;
  }
  ctx.continue_len = loop_len;
  return 0;
}

/** Pop loop-label stack top; restore outer break/continue or clear to empty. */
export function ctx_pop_loop_labels(ctx: *AsmFuncCtx): void {
  if (ctx.loop_label_depth <= 0) {
    ctx.break_len = 0;
    ctx.continue_len = 0;
    return;
  }
  ctx.loop_label_depth = ctx.loop_label_depth - 1;
  let d: i32 = ctx.loop_label_depth;
  if (d <= 0) {
    ctx.break_len = 0;
    ctx.continue_len = 0;
    return;
  }
  let prev: i32 = d - 1;
  let base_off: i32 = prev * 64;
  let bl: i32 = ctx.loop_break_len_stack[prev];
  let cl: i32 = ctx.loop_continue_len_stack[prev];
  let k: i32 = 0;
  while (k < bl && k < 64) {
    ctx.break_label[k] = ctx.loop_break_label_stack[base_off + k];
    k = k + 1;
  }
  ctx.break_len = bl;
  k = 0;
  while (k < cl && k < 64) {
    ctx.continue_label[k] = ctx.loop_continue_label_stack[base_off + k];
    k = k + 1;
  }
  ctx.continue_len = cl;
}

/** Exported function `emit_loop_body_content_elf`.
 * Implements `emit_loop_body_content_elf`.
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param body_ref i32
 * @param ctx *AsmFuncCtx
 * @param ta i32
 * @return i32
 */
export function emit_loop_body_content_elf(arena: *ASTArena, elf_ctx: *ElfCodegenCtx, body_ref: i32, ctx: *AsmFuncCtx, ta: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_loop_body_content_elf_c(arena, elf_ctx, body_ref, ctx, ta);
  }
}

/** Exported function `emit_loop_body_content`.
 * Implements `emit_loop_body_content`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param body_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_loop_body_content(arena: *ASTArena, out: *CodegenOutBuf, body_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_loop_body_content_c(arena, out, body_ref, ctx, target_arch);
  }
}

/** Exported function `emit_while_loop`.
 * Implements `emit_while_loop`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param block_ref i32
 * @param loop_idx i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_while_loop(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, loop_idx: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_while_loop_c(arena, out, block_ref, loop_idx, ctx, target_arch);
  }
}


/** Emit for-loop; set break/continue and emit loop body. */
/** Exported function `emit_for_loop`.
 * Implements `emit_for_loop`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param block_ref i32
 * @param for_idx i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_for_loop(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, for_idx: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_for_loop_c(arena, out, block_ref, for_idx, ctx, target_arch);
  }
}


/** Emit block body in stmt_order; target_arch dispatches emit_expr / store / while / for. */
/** Exported function `emit_block_body`.
 * Implements `emit_block_body`.
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param block_ref i32
 * @param ctx *AsmFuncCtx
 * @param target_arch i32
 * @return i32
 */
export function emit_block_body(arena: *ASTArena, out: *CodegenOutBuf, block_ref: i32, ctx: *AsmFuncCtx, target_arch: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_asm_emit_block_body_c(arena, out, block_ref, ctx, target_arch);
  }
}


/** Exported function `asm_codegen_ast`.
 * Implements `asm_codegen_ast`.
 * @param module *Module
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param pipeline_ctx *PipelineDepCtx
 * @return i32
 */
export function asm_codegen_ast(module: *Module, arena: *ASTArena, out: *CodegenOutBuf, pipeline_ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_backend_asm_codegen_ast_c(module, arena, out, pipeline_ctx);
  }
}

/**
 * build_xlang_asm SKIP_TYPECK stub: only mov w0/x0/eax,#0 + epilogue; do not fill/emit_block
 * (large-module host stack would SIGSEGV).
 */
export function emit_skip_heavy_stub_elf(elf_ctx: *ElfCodegenCtx, ta: i32): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    /* See implementation. */
    return pipeline_asm_emit_skip_heavy_stub_elf_c(elf_ctx, ta);
  }
}

/** Exported function `asm_codegen_ast_to_elf`.
 * Implements `asm_codegen_ast_to_elf`.
 * @param module *Module
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param pipeline_ctx *PipelineDepCtx
 * @return i32
 */
export function asm_codegen_ast_to_elf(module: *Module, arena: *ASTArena, elf_ctx: *ElfCodegenCtx, pipeline_ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    return pipeline_backend_asm_codegen_ast_to_elf_c(module, arena, elf_ctx, pipeline_ctx);
  }
}

/** Exported function `asm_codegen_ast_seed_mega`.
 * Implements `asm_codegen_ast_seed_mega`.
 * @param module *Module
 * @param arena *ASTArena
 * @param out *CodegenOutBuf
 * @param pipeline_ctx *PipelineDepCtx
 * @return i32
 */
export function asm_codegen_ast_seed_mega(module: *Module, arena: *ASTArena, out: *CodegenOutBuf, pipeline_ctx: *PipelineDepCtx): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    asm_hoist_top_level_lets_for_codegen(module, arena);
    let ta: i32 = pipeline_ctx.target_arch;
    let br_stk: u8[512] = [];
    let co_stk: u8[512] = [];
    let br_lens: i32[8] = [];
    let co_lens: i32[8] = [];
    let lbl: u8[128] = [];
    let ctx: AsmFuncCtx = {
      frame_size: 0, next_offset: 0, num_locals: 0, label_counter: 0,
      module_ref: 0 as *Module,
      loop_break_label_stack: br_stk, loop_break_len_stack: br_lens,
      loop_continue_label_stack: co_stk, loop_continue_len_stack: co_lens,
      break_label: lbl, break_len: 0, continue_label: lbl, continue_len: 0,
      loop_label_depth: 0, dep_pipe: 0 as *PipelineDepCtx,
      tail_join_label: lbl, tail_join_label_len: 0
    };
    let fname_buf: u8[128] = [];
    pipeline_asm_emit_set_dep_pipe(pipeline_ctx);
    pipeline_asm_emit_set_module(module);
    pipeline_asm_emit_set_arena(arena);
    let i: i32 = 0;
    while (i < module.num_funcs) {
      if (i == 0) {
        if (arch_emit_section_text(out, ta) != 0) {
          driver_diagnostic_asm_fail_at(1);
          return -1;
        }
      }
      if (pipeline_asm_module_func_is_extern_at(module, i) != 0) {
        i = i + 1;
        continue;
      }
      /* See implementation. */
      if (pipeline_asm_wpo_should_emit_func(module, i) == 0) {
        i = i + 1;
        continue;
      }
      pipeline_asm_module_func_name_copy64(module, i, &fname_buf[0]);
      let fname_len: i32 = pipeline_asm_module_func_name_len_at(module, i);
      driver_diagnostic_asm_set_current_func(&fname_buf[0], fname_len);
      pipeline_asm_emit_set_func_index(i);
      ctx_reset(&ctx, module);
      ctx.dep_pipe = pipeline_ctx;
      fill_param_slots(&ctx, module, i);
      if (arch_emit_globl(out, fname_buf, fname_len, ta) != 0) {
        driver_diagnostic_asm_fail_at(2);
        return -1;
      }
      if (arch_emit_label(out, fname_buf, fname_len, ta) != 0) {
        driver_diagnostic_asm_fail_at(3);
        return -1;
      }
      let body_ref: i32 = pipeline_asm_module_func_body_ref_at(module, i);
      let frame_sz: i32 = 0;
      if (body_ref != 0) {
        frame_sz = compute_frame_size(pipeline_asm_module_func_num_params_at(module, i), arena, body_ref, module, i);
        fill_local_slots(&ctx, arena, body_ref);
      }
      if (arch_emit_prologue(out, frame_sz, ta) != 0) {
        driver_diagnostic_asm_fail_at(4);
        return -1;
      }
      if (body_ref != 0) {
        ctx.tail_join_label_len = emit_next_label(&ctx, &ctx.tail_join_label[0], 64);
        if (pipeline_asm_block_num_stmt_order_at(arena, body_ref) > 0) {
          if (emit_block_body(arena, out, body_ref, &ctx, ta) != 0) {
            driver_diagnostic_asm_fail_at(5);
            return -1;
          }
          /* See implementation. */
        } else {
          let slot_base: i32 = ctx.num_locals - ast.ast_block_num_consts(arena, body_ref) - ast.ast_block_num_lets(arena, body_ref);
          if (slot_base < 0) { driver_diagnostic_asm_fail_at(6); return -1; }
          if (emit_block_inits(arena, out, body_ref, &ctx, ta, slot_base) != 0) {
            driver_diagnostic_asm_fail_at(6);
            return -1;
          }
        }
        if (arch_emit_label(out, ctx.tail_join_label, ctx.tail_join_label_len, ta) != 0) {
          driver_diagnostic_asm_fail_at(9);
          return -1;
        }
      }
      let result_ref: i32 = 0;
      if (body_ref == 0 || pipeline_asm_block_num_stmt_order_at(arena, body_ref) == 0) {
        result_ref = pipeline_asm_get_return_expr_ref_at(arena, module, i);
      }
      if (result_ref != 0) {
        if (emit_expr(arena, out, result_ref, &ctx, ta) != 0) {
          driver_diagnostic_asm_fail_at(7);
          return -1;
        }
      }
      if (arch_emit_epilogue(out, frame_sz, ta) != 0) {
        driver_diagnostic_asm_fail_at(8);
        return -1;
      }
      i = i + 1;
    }
    return 0;
  }
}

/** Exported function `asm_codegen_ast_to_elf_seed_mega`.
 * Implements `asm_codegen_ast_to_elf_seed_mega`.
 * @param module *Module
 * @param arena *ASTArena
 * @param elf_ctx *ElfCodegenCtx
 * @param pipeline_ctx *PipelineDepCtx
 * @return i32
 */
export function asm_codegen_ast_to_elf_seed_mega(module: *Module, arena: *ASTArena, elf_ctx: *ElfCodegenCtx, pipeline_ctx: *PipelineDepCtx): i32 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    asm_hoist_top_level_lets_for_codegen(module, arena);
    let ta: i32 = pipeline_ctx.target_arch;
    if (ta == 1) {
      elf_ctx.e_machine = 183;
      elf_ctx.reloc_type_r_pc32 = 283;
    } else if (ta == 2) {
      elf_ctx.e_machine = 243;
      elf_ctx.reloc_type_r_pc32 = 32;
    } else {
      elf_ctx.e_machine = 62;
      elf_ctx.reloc_type_r_pc32 = 2;
    }
    let br_stk2: u8[512] = [];
    let co_stk2: u8[512] = [];
    let br_lens2: i32[8] = [];
    let co_lens2: i32[8] = [];
    let lbl2: u8[128] = [];
    let ctx: AsmFuncCtx = {
      frame_size: 0, next_offset: 0, num_locals: 0, label_counter: 0,
      module_ref: 0 as *Module,
      loop_break_label_stack: br_stk2, loop_break_len_stack: br_lens2,
      loop_continue_label_stack: co_stk2, loop_continue_len_stack: co_lens2,
      break_label: lbl2, break_len: 0, continue_label: lbl2, continue_len: 0,
      loop_label_depth: 0, dep_pipe: 0 as *PipelineDepCtx,
      tail_join_label: lbl2, tail_join_label_len: 0
    };
    let fname_buf2: u8[128] = [];
    pipeline_asm_emit_set_dep_pipe(pipeline_ctx);
    pipeline_asm_emit_set_module(module);
    pipeline_asm_emit_set_arena(arena);
    pipeline_asm_wpo_pgo_emit_order_prepare(module);
    let start_skip: i32 = asm_diag_start_func_skip();
    let emit_n: i32 = pipeline_asm_wpo_pgo_emit_order_count(module);
    let k: i32 = 0;
    while (k < emit_n) {
      let i: i32 = pipeline_asm_wpo_pgo_emit_order_at(module, k);
      if (i < 0) {
        k = k + 1;
        continue;
      }
      if (i < start_skip) {
        k = k + 1;
        continue;
      }
      // PLATFORM: SHARED — extern must stay U (text-asm path already skips).
      // Defense in depth if emit_order ever leaks an extern index (OOB/stale).
      if (pipeline_asm_module_func_is_extern_at(module, i) != 0) {
        k = k + 1;
        continue;
      }
      pipeline_elf_ctx_set_emit_hot(elf_ctx as *u8, pipeline_asm_wpo_pgo_is_hot_func(module, i));
      pipeline_asm_module_func_name_copy64(module, i, &fname_buf2[0]);
      let fname_len2: i32 = pipeline_asm_module_func_name_len_at(module, i);
      driver_diagnostic_asm_set_current_func(&fname_buf2[0], fname_len2);
      pipeline_asm_emit_set_func_index(i);
      pipeline_debug_trace_body_x_mega_pre_reset(module, arena);
      ctx_reset(&ctx, module);
      pipeline_debug_trace_body_x_mega_post_reset(module, arena);
      ctx.dep_pipe = pipeline_ctx;
      fill_param_slots(&ctx, module, i);
      pipeline_debug_trace_body_x_mega_post_params(module, arena);
      if (enc_label_arch(elf_ctx, fname_buf2, fname_len2, 1, ta) != 0) { return -1; }
      /* See implementation. */
      if (asm_skip_heavy_module_func_body(module, arena, i) != 0) {
        if (enc_prologue_arch(elf_ctx, 0, ta) != 0) { return -1; }
        if (pipeline_asm_emit_skip_heavy_or_thin_stub_elf_c(elf_ctx, ta, module, i) != 0) { return -1; }
        k = k + 1;
        continue;
      }
      let body_ref: i32 = pipeline_asm_module_func_body_ref_at(module, i);
      let frame_sz: i32 = 0;
      if (body_ref != 0) {
        frame_sz = compute_frame_size(pipeline_asm_module_func_num_params_at(module, i), arena, body_ref, module, i);
        pipeline_debug_trace_body_x_mega_post_frame(module, arena);
        if (pipeline_asm_block_num_stmt_order_at(arena, body_ref) == 0) {
          fill_local_slots(&ctx, arena, body_ref);
        }
        pipeline_debug_trace_body_x_mega_post_locals(module, arena);
      }
      if (enc_prologue_arch(elf_ctx, frame_sz, ta) != 0) { return -1; }
      if (pipeline_asm_emit_param_home_elf_c(elf_ctx, &ctx, module, i, ta) != 0) { return -1; }
      if (pipeline_asm_emit_async_cps_entry_elf_c(arena, elf_ctx, &ctx, module, i, ta) != 0) { return -1; }
      if (body_ref != 0) {
        ctx.tail_join_label_len = emit_next_label(&ctx, &ctx.tail_join_label[0], 64);
        if (pipeline_asm_block_num_stmt_order_at(arena, body_ref) > 0) {
          pipeline_debug_trace_body_x_mega_pre_emit(module, arena);
          if (emit_block_body_elf(arena, elf_ctx, body_ref, &ctx, ta) != 0) { return -1; }
          /* See implementation. */
        } else {
          let slot_base: i32 = ctx.num_locals - ast.ast_block_num_consts(arena, body_ref) - ast.ast_block_num_lets(arena, body_ref);
          if (slot_base < 0) { return -1; }
          if (emit_block_inits_elf(arena, elf_ctx, body_ref, &ctx, ta, slot_base) != 0) { return -1; }
        }
        if (enc_label_arch(elf_ctx, ctx.tail_join_label, ctx.tail_join_label_len, 0, ta) != 0) { return -1; }
      }
      let result_ref: i32 = 0;
      if (body_ref == 0 || pipeline_asm_block_num_stmt_order_at(arena, body_ref) == 0) {
        result_ref = pipeline_asm_get_return_expr_ref_at(arena, module, i);
      }
      if (result_ref != 0) {
        if (emit_expr_elf(arena, elf_ctx, result_ref, &ctx, ta) != 0) { return -1; }
      }
      /* AAPCS64 f64 boundary: implicit-tail exit (single-expression body or
       * empty body with a return expr). The value leaves in d0 to match the
       * explicit-return common tail in pipeline_asm_emit_return_elf_impl.
       * f64 cannot be sret, so no sret guard; ta==0 needs no conversion.
       * PLATFORM: MACOS|ARM64 AAPCS64. */
      if (ta == 1 && result_ref != 0) {
        let rty_tail: i32 = pipeline_module_func_return_type_at(module as *u8, i);
        if (rty_tail > 0) {
          unsafe {
            if (pipeline_type_kind_ord_at(arena, rty_tail) == 15) {
              unsafe {
                if (backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx as *u8, 0, ta) != 0) { return -1; }
              }
            }
          }
        }
      }
      if (enc_epilogue_arch(elf_ctx, ta) != 0) { return -1; }
      pipeline_asm_emit_async_cps_end_func_elf_c();
      k = k + 1;
    }
    return 0;
  }
}
