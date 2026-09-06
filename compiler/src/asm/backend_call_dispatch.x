// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// See implementation.
// See implementation.
// See implementation.
// See implementation.


/* Forward decls: monofile typeck is single-pass by function order; callees defined later need early surface. PLATFORM: SHARED. */
export extern function glue_try_std_heap_redirect_sym_local(name: *u8, nlen: i32, out: *u8, cap: i32): i32;
export extern function glue_asm_build_import_binding_call_sym(pre: *u8, plen: i32, field: *u8, flen: i32, out: *u8): i32;
export extern function glue_asm_build_func_export_sym_c(m: *u8, a: *u8, func_ix: i32, out: *u8, out_cap: i32): i32;
export extern function glue_codegen_import_path_to_c_prefix_into(path: *u8, buf: *u8, buf_cap: i32): void;
// PLATFORM: SHARED — all export extern "C" hoisted before first use so -E emits
// short-name prototypes matching call sites (late mid-file externs caused type-mangle
// decls vs short calls → undeclared + cc fail). Product ABI = short pipeline_* names.
/* wave231 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED — product hybrid full.x path owns f32 xmm / WPO fold env gates. */
export extern function link_abi_getenv(name: *u8): *u8;
export extern function pipeline_expr_var_name_into(arena: *u8, er: i32, out: *u8): void;
export extern function pipeline_expr_kind_ord_at(arena: *u8, er: i32): i32;
export extern function pipeline_expr_var_name_len_for_string_lit_c(arena: *u8, er: i32): i32;
export extern function pipeline_asm_call_param_type_ref_at_c(arena: *u8, call: i32, pix: i32): i32;
export extern function pipeline_type_kind_ord_at(arena: *u8, type_ref: i32): i32;
export extern function parser_get_module_import_path(mod: *u8, ix: i32, path_bytes: *u8): void;
export extern function pipeline_module_num_funcs(m: *u8): i32;
export extern function pipeline_asm_module_func_is_extern_at(m: *u8, i: i32): i32;
export extern function pipeline_module_func_name_equal_at(m: *u8, i: i32, name: *u8, nlen: i32): i32;
export extern function parser_get_module_num_imports(mod: *u8): i32;
export extern function pipeline_module_import_path_len(mod: *u8, idx: i32): i32;
export extern function pipeline_module_import_path_byte_at(mod: *u8, idx: i32, k: i32): u8;
export extern function pipeline_elf_ctx_append_bytes(ctx: *u8, ptr: *u8, n: i32): i32;
export extern function pipeline_asm_redirect_std_c_wrapper_sym(name: *u8, nlen: i32, out: *u8, cap: i32): i32;
export extern function backend_enc_call_arch(elf: *u8, name: *u8, nlen: i32, ta: i32): i32;
export extern function backend_enc_call_stack_cleanup_arch(elf: *u8, nbytes: i32, ta: i32): i32;
/**
 * Call-return kind ordinal for harvest (I32=0, BOOL/U8, U32, f32/f64).
 * Authority: pipeline_asm_call_return_type_kind_ord_c (pipeline_abi).
 * PLATFORM: SHARED.
 */
export extern function pipeline_asm_call_return_type_kind_ord_c(arena: *u8, call_expr_ref: i32): i32;
/**
 * Sign-extend i32 call result in w0/x0 after CALL (AAPCS mov w0,imm zero-extends).
 * PLATFORM: SHARED — pure-asm cmp of full x0 vs -2 requires this.
 */
export extern function glue_enc_sxt_i32_result_to_rax_elf_c(elf_ctx: *u8, ta: i32): i32;
/** Zero-extend u32 call result in w0/x0 after CALL. PLATFORM: SHARED. */
export extern function glue_enc_zxt_u32_result_to_rax_elf_c(elf_ctx: *u8, ta: i32): i32;
/** Zero-extend u8/bool call result in w0/x0 after CALL. PLATFORM: SHARED. */
export extern function glue_enc_zxt_u8_result_to_rax_elf_c(elf_ctx: *u8, ta: i32): i32;
/** x86_64 only: move xmm0 f32 bits into eax after CALL. PLATFORM: LINUX|MACOS x86_64. */
export extern function backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx: *u8, k: i32, ta: i32): i32;
/** x86_64 only: move xmm0 f64 bits into rax after CALL. PLATFORM: LINUX|MACOS x86_64. */
export extern function backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx: *u8, k: i32, ta: i32): i32;
export extern function pipeline_asm_emit_call_sret_reg_shift_c(): i32;
export extern function backend_enc_store_x0_sp_offset_arch(elf: *u8, off_bytes: i32, ta: i32): i32;
export extern function pipeline_asm_emit_set_call_param_type_ref(tr: i32): void;
export extern function pipeline_asm_emit_call_arg_begin_c(): void;
export extern function pipeline_asm_emit_call_arg_end_c(): void;
/**
 * Returns 1 if the ELF codegen ctx targets Mach-O (Darwin) so symbol names need
 * a leading underscore prefix; 0 otherwise. Authority: pipeline_elf_ctx_macho_leading_underscore
 * in runtime_pipeline_abi.x. Used by vtable static emit to decide whether to prepend
 * `_` to wrapper/vtable symbol names. PLATFORM: SHARED.
 */
export extern function pipeline_elf_ctx_macho_leading_underscore(ctx: *u8): i32;
export extern function pipeline_asm_emit_expr_elf_for_call_args(arena: *u8, elf: *u8, ar: i32, ctx: *u8, ta: i32): i32;
export extern function pipeline_asm_call_struct16_ret_needs_rax_deref_c(arena: *u8, call: i32): i32;
export extern function pipeline_asm_deref_struct16_rax_ptr_elf_c(elf: *u8, ta: i32): i32;
export extern function pipeline_expr_call_num_args_at(arena: *u8, er: i32): i32;
export extern function pipeline_expr_call_arg_ref(arena: *u8, er: i32, i: i32): i32;
export extern function pipeline_expr_call_num_type_args_at(arena: *u8, er: i32): i32;
/* stage10 10.2.1 slice9: mark block emit diverged after options(noreturn). */
export extern function glue_asm_block_diverged_set(v: i32): void;
export extern function pipeline_expr_call_type_arg_ref_at(arena: *u8, er: i32, idx: i32): i32;
export extern function glue_type_size_simple(m: *u8, a: *u8, ty_ref: i32, depth: i32): i32;
export extern function glue_type_align_simple(m: *u8, a: *u8, ty_ref: i32, depth: i32): i32;
export extern function backend_enc_mov_imm32_to_w0_arch(elf: *u8, imm: i32, ta: i32): i32;
export extern function backend_enc_mov_imm32_to_rbx_arch(elf: *u8, imm: i32, ta: i32): i32;
export extern function backend_enc_mov_rax_to_arg_reg_arch(elf: *u8, k: i32, ta: i32): i32;
/* stage10 10.2.1 slice5: out/lateout from SysV GP → rax before store. */
export extern function backend_enc_mov_arg_reg_to_rax_arch(elf: *u8, k: i32, ta: i32): i32;
/* stage10 S3.1 slice2 (10.1.1): raw syscall byte-level encoders (x86_64).
 * bodies in backend_x86_64_enc_c.x — same family as the enc externs above. */
export extern "C" function arch_x86_64_enc_enc_syscall(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx: *u8): i32;
/* stage10 10.2.1 slice7: lateout/out("r10") → rax. */
export extern "C" function arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx: *u8): i32;
/* stage10 10.2.3: Windows x64 volatile scratch r11 in/lateout, pause and int3. */
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_r11(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_r11_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_pause(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_int3(elf_ctx: *u8): i32;
/* 10.4.1 slice1: atomic_load/store/cas i32 encoders (backend_x86_64_enc_c.x). */
export extern "C" function arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movl_mem_rcx_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_xchg_edx_mem_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movl_eax_to_mem_rcx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sete_al(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx: *u8): i32;
/* Cap 10.7.1 slice12: bump VaList cursor (addq $imm,%rax). */
export extern function backend_enc_add_imm_to_rax_arch(elf: *u8, imm: i32, ta: i32): i32;
/* Cap 10.7.1 slice18: mixed overflow select (cmp class_cursor vs class_end). */
export extern function backend_enc_cmp_rbx_rax_arch(elf: *u8, ta: i32): i32;
export extern function backend_enc_cmp_setcc_movzbl_arch(elf: *u8, cc: i32, ta: i32): i32;
export extern function backend_enc_test_eax_eax_arch(elf: *u8, ta: i32): i32;
export extern function backend_enc_jz_arch(elf: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern function backend_enc_jmp_arch(elf: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern function backend_enc_label_arch(elf: *u8, name: *u8, name_len: i32, is_func: i32, ta: i32): i32;
export extern function pipeline_asm_emit_next_label_c(ctx: *u8, buf: *u8, buf_size: i32): i32;
/* Cap 10.7.1 slice12: current emit func index for named-param gp skip. */
export extern function pipeline_asm_emit_func_index_c(): i32;
/* 10.4.1 slice2: i64 atomic encoders. */
export extern "C" function arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_xchg_rdx_mem_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(elf_ctx: *u8): i32;
/* 10.4.2: memory fences. */
export extern "C" function arch_x86_64_enc_enc_mfence(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lfence(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_sfence(elf_ctx: *u8): i32;
/* 10.4.1 slice3: i16 atomic encoders. */
export extern "C" function arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_xchg_dx_mem_rax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_movw_ax_to_mem_rcx(elf_ctx: *u8): i32;
export extern "C" function arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(elf_ctx: *u8): i32;
/* stage10 S3.1 10.1.2: Linux aarch64 svc #0 + nr home x8.
 * bodies in seeds/backend_arm64_enc_c.from_x.c (G.7 mov_xn_xm family). */
export extern "C" function arch_arm64_enc_enc_svc(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx: *u8): i32;
/* stage10 10.2.1 slice10: lateout/out("x8") → x0. */
export extern "C" function arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx: *u8): i32;
/* 10.4.1–2 arm64: fence + i32 atomic encoders (seed LIVE + arm64_enc.x twin). */
export extern "C" function arch_arm64_enc_enc_dmb_ish(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_dmb_ishld(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_dmb_ishst(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldar_w0_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_stlr_w1_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldr_w0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_str_w0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_w0_to_w4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_casal_w0_w1_x2(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cmp_w0_w4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cset_eq_w0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldar_x0_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_stlr_x1_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldr_x0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_str_x0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_mov_x0_to_x4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_casal_x0_x1_x2(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_cmp_x0_x4(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldarh_w0_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_stlrh_w1_x0(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_ldrh_w0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_strh_w0_x3(elf_ctx: *u8): i32;
export extern "C" function arch_arm64_enc_enc_casalh_w0_w1_x2(elf_ctx: *u8): i32;
/* 10.5.1 slice0: Vec4f SSE addps/mulps via simd_enc (reuse HW vector binop encoders). */
export extern "C" function simd_enc_try_hw_vector_fadd_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32): i32;
export extern "C" function simd_enc_try_hw_vector_fmul_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32): i32;
export extern "C" function simd_enc_try_hw_vector_fsub_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32): i32;
/* 10.5.1 slice7: f32x4 lang fma (a + b*c); x86 SSE/FMA3 via existing fma_rbp. */
export extern "C" function simd_enc_try_hw_vector_fma_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, off_c: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32): i32;
/* 10.5.1 slice8: f32x4 lang hsum/dot → scalar f32 in xmm0 then eax. */
export extern "C" function simd_enc_try_hw_vector_hsum_f32x4_rbp(elf_ctx: *u8, off_v: i32, ta: i32, feats: u32): i32;
export extern "C" function simd_enc_try_hw_vector_dot_f32x4_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, ta: i32, feats: u32): i32;
/* 10.5.1 slice1: i32x8 lang builtins (VAR stack homes + sret let slot). */
export extern "C" function simd_enc_try_hw_vector_iadd_isub_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32, is_sub: i32): i32;
export extern "C" function simd_enc_try_hw_vector_imul_rbp(elf_ctx: *u8, off_a: i32, off_b: i32, dst_off: i32, lanes: i32, esz: i32, ta: i32, feats: u32): i32;
export extern function glue_asm_local_var_stack_off_scoped(arena: *u8, ctx: *u8, var_expr_ref: i32): i32;
export extern function pipeline_asm_emit_ctx_sret_home_off_get(): i32;
export extern "C" function glue_simd_emit_cpu_features_c(): u32;
export extern "C" function xlang_target_cpu_detect_host(): u32;
/** wave359: freestanding i32.double → x*2 (mov+add self). */
export extern function backend_enc_mov_rax_to_rbx_arch(elf: *u8, ta: i32): i32;
export extern function backend_enc_mov_rbx_to_rax_arch(elf: *u8, ta: i32): i32;
export extern function pipeline_module_num_struct_layouts_at(m: *u8): i32;
export extern function pipeline_module_struct_layout_name_len(m: *u8, idx: i32): i32;
export extern function pipeline_module_struct_layout_name_into(m: *u8, idx: i32, out: *u8): void;
export extern function pipeline_module_struct_layout_num_fields(m: *u8, li: i32): i32;
export extern function pipeline_module_struct_layout_field_name_len(m: *u8, li: i32, j: i32): i32;
export extern function pipeline_module_struct_layout_field_name_into(m: *u8, li: i32, j: i32, out: *u8): void;
export extern function pipeline_module_struct_layout_field_type_ref(m: *u8, li: i32, j: i32): i32;
export extern function pipeline_module_struct_layout_field_offset_at(m: *u8, li: i32, j: i32): i32;
export extern function backend_enc_add_rax_rbx_arch(elf: *u8, ta: i32): i32;
export extern function pipeline_expr_call_resolved_func_index_at(arena: *u8, er: i32): i32;
export extern function driver_get_current_dep_path_for_codegen(): *u8;
export extern function pipeline_asm_module_func_name_len_at(m: *u8, fi: i32): i32;
export extern function pipeline_asm_module_func_name_copy64(m: *u8, fi: i32, dst: *u8): void;
export extern function pipeline_module_func_num_params_at(m: *u8, fi: i32): i32;
export extern function pipeline_module_func_param_type_ref_at(m: *u8, fi: i32, pi: i32): i32;
export extern function pipeline_type_elem_ref_at(a: *u8, tr: i32): i32;
/** TYPE_ARRAY size (N in T[N]) for mid suffix `_aN`. PLATFORM: SHARED. */
export extern function pipeline_type_array_size_at(a: *u8, tr: i32): i32;
/** wave360: UFCS auto-ref helpers (type equal + lvalue lea). */
export extern function pipeline_typeck_type_refs_equal_c(a: *u8, x: i32, y: i32): i32;
export extern function pipeline_type_kind_ord_at(a: *u8, tr: i32): i32;
export extern function pipeline_expr_resolved_type_ref(a: *u8, er: i32): i32;
export extern function pipeline_asm_emit_lvalue_eff_addr_elf_c(a: *u8, elf: *u8, lr: i32, ctx: *u8, ta: i32): i32;
/**
 * SysV x86_64 MEMORY by-value push (multi-qword reverse). Used by import METHOD
 * for host-C large POD (String ~260B) on LINUX|x86 — matches gcc stack formals.
 * PLATFORM: LINUX+MACOS x86_64 SysV (ta==0); returns -1 on other arches.
 */
export extern function pipeline_asm_push_sysv_memory_by_value_elf_c(
  arena: *u8, elf: *u8, ctx: *u8, arg_ref: i32, sz: i32, ta: i32): i32;
/**
 * AAPCS64 MEMORY by-value store to [sp+off] (multi-qword low-end).
 * Twin of push_sysv_memory. Seed wave603/606 authority.
 * PLATFORM: MACOS|ARM64 AAPCS64 (ta==1); returns -1 on other arches.
 */
export extern function pipeline_asm_store_memory_by_value_to_sp_elf_c(
  arena: *u8, elf: *u8, ctx: *u8, arg_ref: i32, sz: i32, ta: i32, sp_off: i32): i32;
export extern function pipeline_asm_type_ref_byte_size_c(arena: *u8, pty: i32): i32;
export extern function backend_enc_store_rax_to_rbp_arch(elf: *u8, off: i32, ta: i32): i32;
export extern function backend_enc_store_rdx_to_rbp_arch(elf: *u8, off: i32, ta: i32): i32;
/** AAPCS64 dual-GP high half spill (x1 @ home+8). PLATFORM: MACOS|ARM64. */
export extern function backend_enc_store_x_reg_to_rbp_arch(elf: *u8, reg: i32, off: i32, ta: i32): i32;
export extern function backend_enc_load_rbp_to_rax_arch(elf: *u8, off: i32, ta: i32): i32;
/**
 * Load [rbp+#off_pos] into rax (incoming stack formals). x86 only.
 * PLATFORM: LINUX+MACOS x86_64 SysV — param_home / dyn wrapper stack extras.
 */
export extern function backend_enc_load_rbp_pos_to_rax_arch(elf: *u8, off_pos: i32, ta: i32): i32;
/**
 * Load [x29,#off_pos] into x0 (incoming stack formals). ARM64 only.
 * PLATFORM: MACOS|ARM64 AAPCS64 — param_home / dyn wrapper stack extras.
 */
export extern function backend_enc_load_x29_pos_to_rax_arch(elf: *u8, off_pos: i32, ta: i32): i32;
export extern function backend_enc_lea_rbp_to_rax_arch(elf: *u8, off: i32, ta: i32): i32;
/**
 * F7: materialize a symbol address into a GP register (adrp+add / movabs).
 * PLATFORM: SHARED — vtable static address for dyn coerce store.
 */
export extern function backend_enc_lea_sym_to_reg_arch(elf: *u8, reg: i32, name: *u8, name_len: i32, ta: i32): i32;
export extern function backend_enc_blr_arch(elf: *u8, reg: i32, ta: i32): i32;
export extern function backend_enc_ldr_xreg_xreg_imm_arch(elf: *u8, dst: i32, base: i32, off: i32, ta: i32): i32;
export extern function pipeline_asm_emit_expr_elf_c(arena: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function pipeline_expr_unary_operand_ref_at(arena: *u8, er: i32): i32;
export extern function pipeline_block_let_type_ref(arena: *u8, block_ref: i32, idx: i32): i32;
export extern function pipeline_typeck_resolve_type_alias_ref_c(arena: *u8, tr: i32): i32;
export extern function pipeline_asm_emit_expr_elf_rec(arena: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function backend_asm_ctx_slot_offset(ctx: *u8, slot: i32): i32;
export extern function pipeline_expr_int_val_at(arena: *u8, er: i32): i32;
/** Resolve local VAR frame offset by name (scoped). PLATFORM: SHARED. */
export extern "C" function asm_ctx_local_find_offset_scoped(ctx: *u8, arena: *u8, name: *u8, nlen: i32): i32;
export extern function pipeline_module_func_set_is_used(module: *u8, fi: i32, is_used: i32): void;
export extern function backend_enc_call_stack_reserve_arch(elf: *u8, nbytes: i32, ta: i32): i32;
export extern function backend_enc_push_rax_arch(elf: *u8, ta: i32): i32;
export extern function backend_enc_mov_eax_to_xmm_arg_reg_arch(elf: *u8, k: i32, ta: i32): i32;
export extern function backend_enc_mov_rax_to_xmm_arg_reg_arch(elf: *u8, k: i32, ta: i32): i32;
/** wave195 pure authority — call-arg value byte size (VAR/layout preferred). */
export extern function pipeline_asm_call_arg_value_byte_size_c(arena: *u8, ctx: *u8, arg_ref: i32, pty: i32): i32;
/**
 * Nested CALL/METHOD return byte size (resolve callee → return type).
 * Used when call_arg_value_byte_size floors to 8 for non-VAR MEMORY args.
 * PLATFORM: SHARED — wave194 pure leave.
 */
export extern function glue_call_return_byte_size_c(arena: *u8, call_expr_ref: i32): i32;
/**
 * Cross-module named layout size (ErrorChain 20B when size_simple is soft).
 * PLATFORM: SHARED — wave191 pure leave.
 */
export extern function glue_type_named_layout_size_any_module_elf_c(arena: *u8, ty_ref: i32): i32;
/** AAPCS64: mov x8, x0 (set Indirect Result Location). PLATFORM: MACOS|ARM64. */
export extern function glue_arm64_mov_x0_to_x8_elf_c(elf: *u8): i32;
/** AAPCS64: mov x0, x8 (save incoming sret dest). PLATFORM: MACOS|ARM64. */
export extern function glue_arm64_mov_x8_to_x0_elf_c(elf: *u8): i32;
export extern function pipeline_expr_var_name_len(arena: *u8, er: i32): i32;
export extern function pipeline_expr_call_resolved_dep_index_at(arena: *u8, call: i32): i32;
/** Process-local AsmFuncCtx dep_pipe (set by pipeline_asm_emit_set_dep_pipe). PLATFORM: SHARED. */
export extern function pipeline_asm_emit_dep_pipe_c(): *u8;
export extern function pipeline_dep_ctx_ndep(dep: *u8): i32;
export extern function pipeline_dep_ctx_module_at(dep: *u8, j: i32): *u8;
export extern function pipeline_dep_ctx_import_path_copy64(dep: *u8, j: i32, path: *u8): void;
export extern function pipeline_dep_ctx_import_path_len(dep: *u8, j: i32): i32;
export extern function pipeline_dep_ctx_arena_at(dep: *u8, j: i32): *u8;
/** NAMED type name into out (for overload mid e.g. String / StrView). PLATFORM: SHARED. */
export extern function pipeline_type_named_name_into(a: *u8, tr: i32, out: *u8): i32;
export extern function pipeline_module_func_return_type_at(m: *u8, fi: i32): i32;
/**
 * G.7 import-binding CALL/METHOD_CALL mangle (pre+mid with overload suffixes).
 * Defined later in this TU; METHOD/CALL sites must not bare-concat pre+name.
 * PLATFORM: SHARED — pure-asm mangles this surface (…_u8_ptr_…_reti32). Body must
 * NOT use #[no_mangle]: short def + mangled call → pure-ld U on Ubuntu PREFER
 * thin+rest (seed-only path keeps static short name; dual authority same commit).
 */
export extern function glue_asm_mangle_import_binding_call_sym_c(
  arena: *u8, ctx: *u8, expr_ref: i32, mod_ref: *u8, imp_j: i32,
  pre_buf: *u8, pre_len: i32, field_name: *u8, field_len: i32,
  is_method: i32, sym_flat: *u8
): i32;
export extern function pipeline_module_func_is_extern_at(m: *u8, fi: i32): i32;
export extern function pipeline_typeck_resolve_call_func_index_for_emit_c(m: *u8, a: *u8, call: i32): i32;
export extern function pipeline_typeck_call_arg_effective_type_c(a: *u8, arg_ref: i32): i32;
export extern function pipeline_dep_ctx_current_func_index(dep: *u8): i32;
export extern function pipeline_module_func_param_name_len_at(m: *u8, fi: i32, pi: i32): i32;
export extern function pipeline_module_func_param_name_copy32(m: *u8, fi: i32, pi: i32, dst: *u8): void;
export extern function asm_qual_sym_layer_reset(): void;
export extern function asm_qual_sym_layer_push(bytes: *u8, len: i32): i32;
export extern function asm_qual_sym_layer_count(): i32;
export extern function asm_qual_sym_layer_len(i: i32): i32;
export extern function asm_qual_sym_layer_copy(i: i32, dst: *u8, cap: i32): void;
export extern function pipeline_expr_field_access_name_len(arena: *u8, er: i32): i32;
export extern function pipeline_expr_field_access_name_into(arena: *u8, er: i32, out: *u8): void;
export extern function pipeline_expr_field_access_base_ref(arena: *u8, er: i32): i32;
export extern function pipeline_expr_call_callee_ref_at(arena: *u8, er: i32): i32;
export extern function pipeline_module_import_kind_at(m: *u8, j: i32): i32;
export extern function pipeline_codegen_call_num_args_override(pre: *u8, plen: i32, field: *u8, flen: i32, nargs: i32): i32;
export extern function try_inline_param0_single_field_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_inline_param0_field_sum_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_inline_x_plus_k_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_call_wpo_mono_symbol_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_call_wpo_mono_vector_lane_of_binop_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_inline_wpo_const_vector_lane_of_binop_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function try_inline_wpo_const_scalar_binop_call_elf(a: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function pipeline_expr_method_call_base_ref_at(a: *u8, er: i32): i32;
export extern function pipeline_expr_method_call_num_args_at(a: *u8, er: i32): i32;
export extern function pipeline_expr_method_call_name_len(a: *u8, er: i32): i32;
export extern function pipeline_expr_method_call_name_into(a: *u8, er: i32, out: *u8): void;
export extern function pipeline_expr_method_call_arg_ref(a: *u8, er: i32, idx: i32): i32;
export extern function pipeline_asm_emit_expr_c(arena: *u8, out: *u8, er: i32, ctx: *u8, ta: i32): i32;
export extern function backend_arch_emit_mov_rax_to_arg_reg(out: *u8, i: i32, ta: i32): i32;
export extern function backend_arch_emit_push_rax(out: *u8, ta: i32): i32;
export extern function backend_arch_emit_ldr_sp_offset_to_wi(out: *u8, i: i32, ta: i32): i32;
export extern function backend_arch_emit_add_sp_imm(out: *u8, imm: i32, ta: i32): i32;
export extern function pipeline_module_import_binding_name_len(mod: *u8, ix: i32): i32;
export extern function pipeline_module_import_binding_name_byte_at(mod: *u8, ix: i32, i: i32): u8;

/** Exported function `backend_call_dispatch_x_doc_anchor`.
 * Implements `backend_call_dispatch_x_doc_anchor`.
 * @return i32
 */
export function backend_call_dispatch_x_doc_anchor(): i32 {
  return 0;
}


// See implementation.
let g_pipeline_asm_emit_call_f32_xmm: i32 = 0;

/** Exported function `pipeline_asm_abi_f32_xmm_enabled_c`.
 * Default-on f32 XMM ABI gate: returns 0 only when XLANG_ABI_F32_XMM is exactly "0".
 * wave231 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED — host residual only link_abi_getenv_impl.
 * @return i32 1 = f32 xmm enabled; 0 = legacy f64 widen
 */
#[no_mangle]
export function pipeline_asm_abi_f32_xmm_enabled_c(): i32 {
  unsafe {
    // wave231 G.7: XLANG_ABI_F32_XMM via link_abi_getenv.
    let env: *u8 = link_abi_getenv("XLANG_ABI_F32_XMM");
    if (env != 0) {
      // "0"
      if (env[0] == 48) {
        if (env[1] == 0) { return 0; }
      }
    }
  }
  return 1;
}

/** Exported function `pipeline_asm_emit_set_call_f32_xmm`.
 * Implements `pipeline_asm_emit_set_call_f32_xmm`.
 * @param on i32
 * @return void
 */
#[no_mangle]
export function pipeline_asm_emit_set_call_f32_xmm(on: i32): void {
  if (on != 0) {
    g_pipeline_asm_emit_call_f32_xmm = 1;
  } else {
    g_pipeline_asm_emit_call_f32_xmm = 0;
  }
}

/** Exported function `pipeline_asm_emit_get_call_f32_xmm_c`.
 * Implements `pipeline_asm_emit_get_call_f32_xmm_c`.
 * @return i32
 */
#[no_mangle]
export function pipeline_asm_emit_get_call_f32_xmm_c(): i32 {
  return g_pipeline_asm_emit_call_f32_xmm;
}


// See implementation.
// See implementation.
// See implementation.


/* ---- G-02f-108 / G-02f-139: backend call dispatch helpers ---- */

// glue_asm_string_lit_into: see function docblock below.
/** Exported function `glue_asm_string_lit_into`.
 * Implements `glue_asm_string_lit_into`.
 * @param arena *u8
 * @param er i32
 * @param out64 *u8
 * @return void
 */
#[no_mangle]
export function glue_asm_string_lit_into(arena: *u8, er: i32, out64: *u8): void {
  if (out64 == 0) { return; }
  let zi: i32 = 0;
  while (zi < 64) {
    out64[zi] = 0;
    zi = zi + 1;
  }
  if (arena == 0 as *u8) { return; }
  unsafe {
    if (glue_asm_string_lit_len(arena, er) <= 0) { return; }
    pipeline_expr_var_name_into(arena, er, out64);
  }
}

// glue_codegen_import_path_to_c_prefix_into: see function docblock below.
/** Exported function `glue_codegen_import_path_to_c_prefix_into`.
 * Implements `glue_codegen_import_path_to_c_prefix_into`.
 * @param path *u8
 * @param buf *u8
 * @param buf_cap i32
 * @return void
 */
#[no_mangle]
export function glue_codegen_import_path_to_c_prefix_into(path: *u8, buf: *u8, buf_cap: i32): void {
  if (buf == 0 as *u8) { return; }
  if (buf_cap <= 0) { return; }
  let off: i32 = 0;
  let pi: i32 = 0;
  if (path != 0 as *u8) {
    while (1 == 1) {
      let ch: u8 = path[pi];
      if (ch == 0) { break; }
      if (off + 2 >= buf_cap) { break; }
      // '.'=46 → '_'=95
      if (ch == 46) {
        buf[off] = 95;
      } else {
        buf[off] = ch;
      }
      off = off + 1;
      pi = pi + 1;
    }
  }
  if (off + 1 < buf_cap) {
    buf[off] = 95;
    off = off + 1;
  }
  if (off < buf_cap) {
    buf[off] = 0;
  }
}







// See implementation.


/* ---- G-02f-109 / G-02f-133 / G-02f-134: call_dispatch more helpers ---- */

// glue_module_func_overload_count_c: see function docblock below.
/** Exported function `glue_module_func_overload_count_c`.
 * Implements `glue_module_func_overload_count_c`.
 * @param m *u8
 * @param name *u8
 * @param nlen i32
 * @return i32
 */
#[no_mangle]
export function glue_module_func_overload_count_c(m: *u8, name: *u8, nlen: i32): i32 {
  if (m == 0) { return 0; }
  if (name == 0 as *u8) { return 0; }
  if (nlen <= 0) { return 0; }
  unsafe {
    let c: i32 = 0;
    let n: i32 = pipeline_module_num_funcs(m);
    let i: i32 = 0;
    while (i < n) {
      if (pipeline_asm_module_func_is_extern_at(m, i) == 0) {
        if (pipeline_module_func_name_equal_at(m, i, name, nlen) != 0) {
          c = c + 1;
        }
      }
      i = i + 1;
    }
    return c;
  }
  return 0;
}

// glue_asm_import_segment_at: see function docblock below.
/** Exported function `glue_asm_import_segment_at`.
 * Implements `glue_asm_import_segment_at`.
 * @param mod *u8
 * @param ix i32
 * @param want_seg i32
 * @param ostr *i32
 * @param olen *i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_import_segment_at(mod: *u8, ix: i32, want_seg: i32, ostr: *i32, olen: *i32): i32 {
  if (mod == 0 as *u8) { return 0; }
  if (ix < 0) { return 0; }
  if (ostr == 0) { return 0; }
  if (olen == 0) { return 0; }
  unsafe {
    if (ix >= parser_get_module_num_imports(mod)) { return 0; }
    let pl: i32 = pipeline_module_import_path_len(mod, ix);
    if (pl <= 0) { return 0; }
    if (pl > 127) { return 0; }
    let ci: i32 = 0;
    let ss: i32 = 0;
    let k: i32 = 0;
    while (k <= pl) {
      let at_end: i32 = 0;
      if (k == pl) { at_end = 1; }
      let dot: i32 = 0;
      if (at_end == 0) {
        if (k < pl) {
          if (pipeline_module_import_path_byte_at(mod, ix, k) == 46) { dot = 1; }
        }
      }
      if (at_end != 0 || dot != 0) {
        let seg_len_here: i32 = k - ss;
        if (seg_len_here <= 0) { return 0; }
        if (ci == want_seg) {
          ostr[0] = ss;
          olen[0] = seg_len_here;
          return 1;
        }
        if (dot != 0) { ss = k + 1; }
        ci = ci + 1;
      }
      k = k + 1;
    }
  }
  return 0;
}

// glue_asm_fill_c_prefix_from_module_import: see function docblock below.
/** Exported function `glue_asm_fill_c_prefix_from_module_import`.
 * Implements `glue_asm_fill_c_prefix_from_module_import`.
 * @param mod *u8
 * @param ix i32
 * @param pre *u8
 * @return i32
 */
#[no_mangle]
export function glue_asm_fill_c_prefix_from_module_import(mod: *u8, ix: i32, pre: *u8): i32 {
  if (mod == 0 as *u8) { return 0 - 1; }
  if (pre == 0) { return 0 - 1; }
  let path_bytes: u8[128] = [];
  unsafe {
    parser_get_module_import_path(mod, ix, &path_bytes[0]);
    if (path_bytes[0] == 0) { return 0 - 1; }
    glue_codegen_import_path_to_c_prefix_into(&path_bytes[0], pre, 128);
  }
  let pre_len: i32 = 0;
  while (pre_len < 128) {
    if (pre[pre_len] == 0) { break; }
    pre_len = pre_len + 1;
  }
  if (pre_len > 0) { return pre_len; }
  return 0 - 1;
}





// See implementation.

// See implementation.
/* ---- G-02f-110 / G-02f-141 / G-02f-142 / G-02f-145: call_dispatch emit helpers ---- */

// LE i32 load/store（AsmFuncCtx.next_offset @4）
/** Load little-endian i32 from p[off..off+4). Null p → 0.
 * Used for AsmFuncCtx.next_offset @4 among call-arg emit helpers.
 * Track-L: no_mangle keeps surface short name call_dispatch_load_i32_le.
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function call_dispatch_load_i32_le(p: *u8, off: i32): i32 {
  if (p == 0) { return 0; }
  let m: i32 = 256;
  let a: i32 = p[off] as i32;
  a = a + (p[off + 1] as i32) * m;
  a = a + (p[off + 2] as i32) * (m * m);
  a = a + (p[off + 3] as i32) * (m * m * m);
  return a;
}

/** Store little-endian i32 v into p[off..off+4). Null p is a no-op.
 * Track-L: no_mangle keeps surface short name call_dispatch_store_i32_le.
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function call_dispatch_store_i32_le(p: *u8, off: i32, v: i32): void {
  if (p == 0) { return; }
  let u: u32 = v as u32;
  p[off] = (u & 255) as u8;
  p[off + 1] = ((u / 256) & 255) as u8;
  p[off + 2] = ((u / 65536) & 255) as u8;
  p[off + 3] = ((u / 16777216) & 255) as u8;
}

// See implementation.
/** Load little-endian pointer from p[off..off+8). Null p → null.
 * Used for AsmFuncCtx module_ref @16 and dep_pipe @1384 (64-bit LE).
 * LP64 layout authority: pipeline_abi glue_block_body_bind_module_dep_from_ctx
 * (module_ref@16 / dep_pipe@1384; was stale 1256 mid continue_label → bare call UNDEF).
 * Track-L: no_mangle keeps surface short name call_dispatch_load_ptr_le.
 * PLATFORM: SHARED — link-name contract; dual-host prove. */
#[no_mangle]
export function call_dispatch_load_ptr_le(p: *u8, off: i32): *u8 {
  if (p == 0) { return 0 as *u8; }
  let m: usize = 256;
  let m2: usize = m * m;
  let m4: usize = m2 * m2;
  let a: usize = p[off] as usize;
  a = a + (p[off + 1] as usize) * m;
  a = a + (p[off + 2] as usize) * m2;
  a = a + (p[off + 3] as usize) * (m2 * m);
  a = a + (p[off + 4] as usize) * m4;
  a = a + (p[off + 5] as usize) * (m4 * m);
  a = a + (p[off + 6] as usize) * (m4 * m2);
  a = a + (p[off + 7] as usize) * (m4 * m2 * m);
  return a as *u8;
}

// glue_asm_call_reg_max: see function docblock below.
/** Exported function `glue_asm_call_reg_max`.
 * Implements `glue_asm_call_reg_max`.
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_call_reg_max(ta: i32): i32 {
  if (ta == 0) { return 6; }
  return 8;
}

// G-02f-143 / wave108: x86_64 jmp+lea and aarch64 B+ADR string embed
// glue_asm_emit_jmp_skip_string_then_lea: see function docblock below.
/**
 * Embed a short string in the text stream and load its address into a GP reg.
 * @param ctx_bytes *u8 — platform_elf_ElfCodegenCtx bytes
 * @param ta i32 — 0=x86_64, 1=aarch64; other → -1
 * @param reg_k i32 — x86: 0→rdi, 1→rax; aarch64: both map to x0
 * @param sbuf *u8 — string bytes (not required NUL-terminated)
 * @param slen i32 — length 0..126 (0 = empty ""; max fits x86 short-jmp + NUL)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED emit shape / x86_64+aarch64 encodings (wave108 Darwin pure-asm).
 * Stage 12.2.5: empty string lit is valid (*u8 to NUL); slen==0 must not CG002.
 */
#[no_mangle]
export function glue_asm_emit_jmp_skip_string_then_lea(ctx_bytes: *u8, ta: i32, reg_k: i32, sbuf: *u8, slen: i32): i32 {
  if (ctx_bytes == 0) { return 0 - 1; }
  if (sbuf == 0) { return 0 - 1; }
  if (slen < 0) { return 0 - 1; }
  if (slen > 126) { return 0 - 1; }
  if (ta != 0) {
    if (ta != 1) { return 0 - 1; }
  }
  unsafe {
    // PLATFORM: aarch64 — B over 4-aligned bytes + ADR x0 (wave108).
    if (ta == 1) {
      let raw: i32 = slen + 1;
      let pad: i32 = (4 - (raw & 3)) & 3;
      let skip: i32 = raw + pad;
      let imm26: i32 = 1 + (skip / 4);
      if (imm26 <= 0) { return 0 - 1; }
      if (imm26 >= 33554432) { return 0 - 1; }
      let b_inst: u32 = 335544320 as u32 | ((imm26 as u32) & 67108863 as u32); // 0x14000000 | imm26
      let b4: u8[4] = [];
      b4[0] = (b_inst & 255) as u8;
      b4[1] = ((b_inst / 256) & 255) as u8;
      b4[2] = ((b_inst / 65536) & 255) as u8;
      b4[3] = ((b_inst / 16777216) & 255) as u8;
      if (pipeline_elf_ctx_append_bytes(ctx_bytes, &b4[0], 4) != 0) { return 0 - 1; }
      if (pipeline_elf_ctx_append_bytes(ctx_bytes, sbuf, slen) != 0) { return 0 - 1; }
      let z: u8 = 0;
      if (pipeline_elf_ctx_append_bytes(ctx_bytes, &z, 1) != 0) { return 0 - 1; }
      let pi: i32 = 0;
      while (pi < pad) {
        if (pipeline_elf_ctx_append_bytes(ctx_bytes, &z, 1) != 0) { return 0 - 1; }
        pi = pi + 1;
      }
      // ADR x0, string: imm = -skip (Rd=0 for both reg_k).
      let imm: i32 = 0 - skip;
      let imm_bits: u32 = (imm as u32) & 2097151 as u32; // 0x1FFFFF
      let immlo: u32 = imm_bits & (3 as u32);
      let immhi: u32 = (imm_bits / (4 as u32)) & 524287 as u32; // 0x7FFFF
      let adr_inst: u32 = 268435456 as u32 | (immlo * (536870912 as u32)) | (immhi * (32 as u32)); // 0x10000000 | ...
      let adr4: u8[4] = [];
      adr4[0] = (adr_inst & 255) as u8;
      adr4[1] = ((adr_inst / 256) & 255) as u8;
      adr4[2] = ((adr_inst / 65536) & 255) as u8;
      adr4[3] = ((adr_inst / 16777216) & 255) as u8;
      if (reg_k == 0) { /* x0 */ }
      return pipeline_elf_ctx_append_bytes(ctx_bytes, &adr4[0], 4);
    }
    // PLATFORM: x86_64 — short jmp + lea [rip].
    if (slen + 1 > 127) { return 0 - 1; }
    let jmp2: u8[2] = [];
    jmp2[0] = 235; // 0xeb
    jmp2[1] = (slen + 1) as u8;
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, &jmp2[0], 2) != 0) { return 0 - 1; }
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, sbuf, slen) != 0) { return 0 - 1; }
    let z0: u8 = 0;
    if (pipeline_elf_ctx_append_bytes(ctx_bytes, &z0, 1) != 0) { return 0 - 1; }
    let d: i32 = 0 - slen - 8;
    let u: u32 = d as u32;
    let lea7: u8[7] = [];
    lea7[0] = 72; // 0x48
    lea7[1] = 141; // 0x8d
    if (reg_k == 0) {
      lea7[2] = 61; // 0x3d rdi
    } else {
      lea7[2] = 5; // 0x05 rax
    }
    lea7[3] = (u & 255) as u8;
    lea7[4] = ((u / 256) & 255) as u8;
    lea7[5] = ((u / 65536) & 255) as u8;
    lea7[6] = ((u / 16777216) & 255) as u8;
    return pipeline_elf_ctx_append_bytes(ctx_bytes, &lea7[0], 7);
  }
  return 0 - 1;
}

/**
 * PLATFORM: LINUX+MACOS x86_64 SysV — how many integer arg registers a value of size sz needs.
 * 9–16B POD → 2; >16B MEMORY → 0 GP; else 1.
 * wave214 fix: pure surface previously always used 1 unit → dual-GP struct clobbered later args.
 */
function glue_sysv_arg_gp_units_from_size_c(sz: i32): i32 {
  if (sz > 16) { return 0; }
  if (sz > 8) {
    if (sz <= 16) { return 2; }
  }
  return 1;
}

/** SysV MEMORY by-value: aggregate size >16 (not a pointer in a GP). */
function glue_sysv_arg_is_memory_by_value_c(sz: i32): i32 {
  if (sz > 16) { return 1; }
  return 0;
}

/** Stack words for one SysV arg: MEMORY → ceil(sz/8); integer stack excess → units. */
function glue_sysv_arg_stack_words_c(sz: i32, gp_units: i32): i32 {
  if (sz > 16) { return (sz + 7) / 8; }
  if (gp_units < 1) { return 1; }
  return gp_units;
}

/**
 * Byte size of a call/method arg for SysV packing.
 * Take max of call_arg_value / formal / resolved / nested CALL return size.
 * Root (ErrorChain nested CALL-as-MEMORY Cap): call_arg_value floors to 8 for
 * non-VAR args and early-return blocked formal ErrorChain (20B) → is_mem≠2 → SEGV.
 * Root (bare CALL formal size): x86 slot/n_stack classifiers pass ctx=NULL, so
 * call_arg cannot recover VAR decl; soft sz=8 → lea→rdi while callee expects
 * SysV stack MEMORY. Widen non-CALL soft sizes only when formal/resolved
 * named_layout (or type_ref size) is true MEMORY (>16). Do NOT max ≤16 layouts
 * (SLICE fat=16 would undo E* pack → slice_oob).
 * G.7: one packer; max() not first-wins. PLATFORM: SHARED freestanding dual-GP.
 */
function glue_sysv_arg_byte_size_c(arena: *u8, ctx: *u8, pty: i32, arg_ref: i32): i32 {
  let sz: i32 = 0;
  let alt: i32 = 0;
  let ko: i32 = 0;
  let tr: i32 = 0;
  if (arena != 0 as *u8) {
    sz = pipeline_asm_call_arg_value_byte_size_c(arena, ctx, arg_ref, pty);
  }
  // Preserve call_arg SLICE/ARRAY→8 pointer packing for VAR/FIELD/etc.
  // Widen nested CALL/METHOD when soft (≤16): formal/resolved named layout +
  // callee return (ErrorChain 20B). Widen non-CALL soft only to MEMORY (>16).
  // PLATFORM: SHARED freestanding · MACOS|ARM64 host-indirect · LINUX SysV.
  if (arg_ref > 0) {
    if (arena != 0 as *u8) {
      ko = pipeline_expr_kind_ord_at(arena, arg_ref);
      if (ko == 48 || ko == 49) {
        if (sz <= 16) {
          if (pty > 0) {
            alt = pipeline_asm_type_ref_byte_size_c(arena, pty);
            if (alt > sz) { sz = alt; }
            alt = glue_type_named_layout_size_any_module_elf_c(arena, pty);
            if (alt > sz) { sz = alt; }
          }
          tr = pipeline_expr_resolved_type_ref(arena, arg_ref);
          if (tr > 0) {
            alt = pipeline_asm_type_ref_byte_size_c(arena, tr);
            if (alt > sz) { sz = alt; }
            alt = glue_type_named_layout_size_any_module_elf_c(arena, tr);
            if (alt > sz) { sz = alt; }
          }
          alt = glue_call_return_byte_size_c(arena, arg_ref);
          if (alt > sz) { sz = alt; }
        }
      } else {
        // Non-CALL VAR/FIELD/…: MEMORY-class widen when soft (ctx may be null).
        // Only TYPE_NAMED named_layout >16 (ErrorChain 20B). Do NOT use
        // type_ref_byte_size — ARRAY payload (e.g. [2]Wide=40) would undo E*
        // pack (ret_idx(a) / slice_oob). PLATFORM: SHARED · LINUX SysV gold.
        if (sz <= 16) {
          if (pty > 0) {
            if (pipeline_type_kind_ord_at(arena, pty) == 8) {
              alt = glue_type_named_layout_size_any_module_elf_c(arena, pty);
              if (alt > 16) {
                if (alt > sz) { sz = alt; }
              }
            }
          }
          tr = pipeline_expr_resolved_type_ref(arena, arg_ref);
          if (tr > 0) {
            if (pipeline_type_kind_ord_at(arena, tr) == 8) {
              alt = glue_type_named_layout_size_any_module_elf_c(arena, tr);
              if (alt > 16) {
                if (alt > sz) { sz = alt; }
              }
            }
          }
        }
      }
    }
  } else if (sz <= 0) {
    if (pty > 0) {
      if (arena != 0 as *u8) {
        sz = pipeline_asm_type_ref_byte_size_c(arena, pty);
      }
    }
  }
  if (sz <= 0) { return 8; }
  return sz;
}

/**
 * PLATFORM: MACOS|ARM64 — address of host-indirect MEMORY arg into rax/x0.
 * VAR: lea. Nested CALL/METHOD: sret into frame temp (save/restore outer x8), then lea.
 * Root (ErrorChain nested chain_wrap SEGV): bare lvalue_eff_addr on CALL fails;
 * outer let sret in x8 must survive inner materialize (≡ store_memory_by_value).
 * G.7: one materialize for import METHOD is_mem=2. @return 0 ok; -1 fail.
 */
function glue_emit_arm64_host_mem_arg_addr_to_rax_c(
    arena: *u8, elf_ctx: *u8, ctx: *u8, arg_ref: i32, sz: i32, ta: i32): i32 {
  let ko: i32 = 0;
  let nbytes: i32 = 0;
  let off: i32 = 0;
  let save_off: i32 = 0;
  let cur: i32 = 0;
  let sum: i32 = 0;
  let ret_sz: i32 = 0;
  if (arena == 0 as *u8 || elf_ctx == 0 as *u8 || ctx == 0 as *u8 || arg_ref <= 0 || sz <= 16 || ta != 1) {
    return 0 - 1;
  }
  ko = pipeline_expr_kind_ord_at(arena, arg_ref);
  // EXPR_VAR = 3
  if (ko == 3) {
    return pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, arg_ref, ctx, ta);
  }
  // Nested CALL/METHOD (48/49) or other non-lvalue: materialize then lea.
  nbytes = (sz + 7) & (0 - 8);
  cur = call_dispatch_load_i32_le(ctx, 4);
  off = cur;
  if (off < 16) { off = 16; }
  save_off = off + nbytes;
  sum = save_off + 8;
  if (sum < off) { return 0 - 1; }
  call_dispatch_store_i32_le(ctx, 4, sum);
  // Save incoming x8 (outer let/call sret dest) before inner IRLR overwrite.
  if (glue_arm64_mov_x8_to_x0_elf_c(elf_ctx) != 0) { return 0 - 1; }
  if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off, ta) != 0) { return 0 - 1; }
  if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta) != 0) { return 0 - 1; }
  if (glue_arm64_mov_x0_to_x8_elf_c(elf_ctx) != 0) { return 0 - 1; }
  if (ko == 48 || ko == 49) {
    ret_sz = glue_call_return_byte_size_c(arena, arg_ref);
    if (ret_sz <= 16) { ret_sz = sz; }
  } else {
    ret_sz = sz;
  }
  if (ret_sz <= 16) { return 0 - 1; }
  if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
    return 0 - 1;
  }
  // Restore outer x8, then lea temp for host-indirect arg pointer.
  if (backend_enc_load_rbp_to_rax_arch(elf_ctx, save_off, ta) != 0) { return 0 - 1; }
  if (glue_arm64_mov_x0_to_x8_elf_c(elf_ctx) != 0) { return 0 - 1; }
  return backend_enc_lea_rbp_to_rax_arch(elf_ctx, off, ta);
}

/**
 * Spill rax (+ rdx / x1 for 9–16B) to a fresh frame slot; advance AsmFuncCtx.next_offset @4.
 * PLATFORM: LINUX+MACOS x86_64 SysV — multi-arg packing must materialize all values to memory
 * before loading GPs so dual-load (uses rdx) does not clobber already-placed higher arg regs.
 * PLATFORM: MACOS|ARM64 AAPCS64 — dual high half @ home+8 via x1 (wave600 seed twin).
 * @return i32 — spill offset (low half), or -1
 */
function glue_sysv_spill_rax_rdx_to_frame_c(elf: *u8, ctx: *u8, ta: i32, gp_units: i32): i32 {
  if (elf == 0 as *u8) { return 0 - 1; }
  if (ctx == 0 as *u8) { return 0 - 1; }
  if (ta != 0) {
    if (ta != 1) { return 0 - 1; }
  }
  // AsmFuncCtx.next_offset is the second i32 (offset 4).
  let cur: i32 = call_dispatch_load_i32_le(ctx, 4);
  let off: i32 = cur + 16;
  if (off < 16) { off = 16; }
  if (backend_enc_store_rax_to_rbp_arch(elf, off, ta) != 0) { return 0 - 1; }
  if (gp_units >= 2) {
    if (ta == 0) {
      // SysV high-end: high half @ home-8 (rdx).
      if (backend_enc_store_rdx_to_rbp_arch(elf, off - 8, ta) != 0) { return 0 - 1; }
    } else {
      // AAPCS64 low-end: high half @ home+8 (x1).
      if (backend_enc_store_x_reg_to_rbp_arch(elf, 1, off + 8, ta) != 0) { return 0 - 1; }
    }
  }
  call_dispatch_store_i32_le(ctx, 4, off + 16);
  return off;
}

/**
 * Load spilled arg from frame into integer arg regs starting at gp.
 * PLATFORM: LINUX+MACOS x86_64 SysV (high@spill-8).
 * When gp==0 and dual-GP, load high half first then low (avoid overwriting low in rax).
 */
function glue_sysv_load_spill_to_arg_regs_elf_c(elf: *u8, ta: i32, spill_off: i32, gp: i32, gp_units: i32): i32 {
  if (elf == 0 as *u8) { return 0 - 1; }
  if (spill_off < 0) { return 0 - 1; }
  if (gp < 0) { return 0 - 1; }
  if (gp_units >= 2) {
    if (gp == 0) {
      let half2: i32 = spill_off - 8;
      if (ta == 1) { half2 = spill_off + 8; }
      if (backend_enc_load_rbp_to_rax_arch(elf, half2, ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_arg_reg_arch(elf, 1, ta) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf, spill_off, ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_arg_reg_arch(elf, 0, ta) != 0) { return 0 - 1; }
      return 0;
    }
  }
  if (backend_enc_load_rbp_to_rax_arch(elf, spill_off, ta) != 0) { return 0 - 1; }
  if (backend_enc_mov_rax_to_arg_reg_arch(elf, gp, ta) != 0) { return 0 - 1; }
  if (gp_units >= 2) {
    let half2b: i32 = spill_off - 8;
    if (ta == 1) { half2b = spill_off + 8; }
    if (backend_enc_load_rbp_to_rax_arch(elf, half2b, ta) != 0) { return 0 - 1; }
    if (backend_enc_mov_rax_to_arg_reg_arch(elf, gp + 1, ta) != 0) { return 0 - 1; }
  }
  return 0;
}

/**
 * SysV x86_64: classify arg_index into GP / XMM / stack, with dual-GP unit accounting.
 * @param out_kind *i32 — 0=gp 1=xmm 2=stack
 * @param out_reg_k *i32 — GP or XMM index when kind is 0/1
 * @param out_stack_k *i32 — stack word index when kind is 2
 * PLATFORM: LINUX+MACOS x86_64 SysV — 9–16B INTEGER aggregates consume 2 GP slots.
 */
#[no_mangle]
export function glue_sysv_x86_call_arg_slot_c(
  arena: *u8, call_expr_ref: i32, nargs: i32, arg_index: i32, out_kind: *i32, out_reg_k: *i32, out_stack_k: *i32
): void {
  if (out_kind == 0) { return; }
  if (out_reg_k == 0) { return; }
  if (out_stack_k == 0) { return; }
  let gp: i32 = 0;
  let xmm: i32 = 0;
  let stk: i32 = 0;
  let j: i32 = 0;
  while (j <= arg_index) {
    if (j >= nargs) { break; }
    let pty: i32 = glue_call_param_type_ref_at(arena, call_expr_ref, j);
    let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, call_expr_ref, j);
    let sz: i32 = glue_sysv_arg_byte_size_c(arena, 0 as *u8, pty, arg_ref);
    let units: i32 = glue_sysv_arg_gp_units_from_size_c(sz);
    let words: i32 = glue_sysv_arg_stack_words_c(sz, units);
    if (j == arg_index) {
      if (glue_call_param_is_f32_c(arena, pty) != 0) {
        if (xmm < 8) {
          out_kind[0] = 1;
          out_reg_k[0] = xmm;
        } else {
          out_kind[0] = 2;
          out_stack_k[0] = stk;
        }
      } else {
        if (glue_sysv_arg_is_memory_by_value_c(sz) != 0) {
          out_kind[0] = 2;
          out_stack_k[0] = stk;
        } else {
          if (units > 0) {
            if (gp + units <= 6) {
              out_kind[0] = 0;
              out_reg_k[0] = gp;
            } else {
              out_kind[0] = 2;
              out_stack_k[0] = stk;
            }
          } else {
            out_kind[0] = 2;
            out_stack_k[0] = stk;
          }
        }
      }
      return;
    }
    if (glue_call_param_is_f32_c(arena, pty) != 0) {
      if (xmm < 8) { xmm = xmm + 1; }
      else { stk = stk + 1; }
    } else {
      if (glue_sysv_arg_is_memory_by_value_c(sz) != 0) {
        stk = stk + words;
      } else {
        if (units > 0) {
          if (gp + units <= 6) { gp = gp + units; }
          else { stk = stk + words; }
        } else {
          stk = stk + words;
        }
      }
    }
    j = j + 1;
  }
  out_kind[0] = 2;
  out_reg_k[0] = 0;
  out_stack_k[0] = 0;
}

/**
 * Historical name: spill 9–16B call-arg to stack then lea.
 * PLATFORM: LINUX+MACOS x86_64 SysV — INTEGER-class 9–16B aggregates pass by value in
 * rax+rdx / two consecutive GPs. Nested CALL already leaves that form; converting to a
 * pointer mismatches formal C (std_string_length_StrView rdi+rsi). No-op; placement uses
 * mov_rax/mov_rdx_to_arg_reg. Authority aligned with pipeline_glue call-arg dual load.
 */
#[no_mangle]
export function glue_spill_struct16_call_arg_to_lea_elf_c(arena: *u8, elf: *u8, ctx: *u8, pty: i32, ta: i32): i32 {
  // Keep signature for G.7 single symbol; body is intentionally a no-op (SysV by-value).
  if (arena == 0 as *u8) { return 0; }
  if (elf == 0 as *u8) { return 0; }
  if (ctx == 0 as *u8) { return 0; }
  if (pty < 0) { return 0; }
  if (ta < 0) { return 0; }
  return 0;
}

// See implementation.
// GLUE_ASM_MAX_CALL_ARGS=96
/** Exported function `glue_emit_call_args_elf_sysv_f32_xmm_c`.
 * Implements `glue_emit_call_args_elf_sysv_f32_xmm_c`.
 * @param arena *u8
 * @param elf *u8
 * @param er i32
 * @param ctx *u8
 * @param ta i32
 * @param nargs i32
 * @return i32
 */
#[no_mangle]
export function glue_emit_call_args_elf_sysv_f32_xmm_c(arena: *u8, elf: *u8, er: i32, ctx: *u8, ta: i32, nargs: i32): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (elf == 0 as *u8) { return 0 - 1; }
  if (ctx == 0 as *u8) { return 0 - 1; }
  if (nargs < 0) { return 0 - 1; }
  if (nargs > 96) { return 0 - 1; }
  unsafe {
    let n_stack: i32 = glue_sysv_x86_call_n_stack_c(arena, er, nargs);
    let stack_reserve: i32 = 0;
    if (n_stack > 0) {
      stack_reserve = n_stack * 8;
      if ((n_stack & 1) != 0) {
        stack_reserve = stack_reserve + 8;
      }
    }
    if (backend_enc_call_stack_reserve_arch(elf, stack_reserve, ta) != 0) { return 0 - 1; }
    let stk_push: i32[96] = [];
    let n_stk_push: i32 = 0;
    let i: i32 = 0;
    while (i < nargs) {
      let kind: i32 = 0;
      let reg_k: i32 = 0;
      let stack_k: i32 = 0;
      glue_sysv_x86_call_arg_slot_c(arena, er, nargs, i, &kind, &reg_k, &stack_k);
      if (kind == 2) {
        if (n_stk_push < 96) {
          stk_push[n_stk_push] = i;
          n_stk_push = n_stk_push + 1;
        }
      }
      i = i + 1;
    }
    if (n_stack > 0) {
      if ((n_stack & 1) != 0) {
        if (backend_enc_mov_imm32_to_w0_arch(elf, 0, ta) != 0) { return 0 - 1; }
        if (backend_enc_push_rax_arch(elf, ta) != 0) { return 0 - 1; }
      }
    }
    let si: i32 = n_stk_push - 1;
    while (si >= 0) {
      i = stk_push[si];
      let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, er, i);
      if (arg_ref != 0) {
        /*
         * G.7: f32-xmm is the default CALL packer (XLANG_ABI_F32_XMM
         * unset → on). Stack-class >16B must multi-qword push — the
         * old emit+push rax left INDEX leave-addr as the first 8B
         * (take_w(a[1]) on Wide → .e = 0). Same helper as seed
         * wave601 / non-f32 emit_call_args / METHOD UFCS.
         * PLATFORM: LINUX+MACOS x86_64 SysV.
         */
        let pty_s: i32 = glue_call_param_type_ref_at(arena, er, i);
        let sz_s: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_s, arg_ref);
        if (glue_sysv_arg_is_memory_by_value_c(sz_s) != 0) {
          let pushed_s: i32 = pipeline_asm_push_sysv_memory_by_value_elf_c(
            arena, elf, ctx, arg_ref, sz_s, ta);
          if (pushed_s < 0) { return 0 - 1; }
        } else if (glue_emit_one_call_arg_elf_c(arena, elf, er, arg_ref, i, ctx, ta) != 0) {
          return 0 - 1;
        } else if (backend_enc_push_rax_arch(elf, ta) != 0) {
          return 0 - 1;
        }
      }
      si = si - 1;
    }
    pipeline_asm_emit_set_call_f32_xmm(1);
    // wave214: spill-then-load for register args (dual-GP units; same as non-f32 path).
    // Direct place by kind/reg_k alone missed the second half of 9–16B structs.
    let gp_start_f: i32[96] = [];
    let gp_units_f: i32[96] = [];
    let spill_off_f: i32[96] = [];
    let is_sse_f: i32[96] = [];
    let gp_cur_f: i32 = 0;
    let xmm_cur_f: i32 = 0;
    i = 0;
    while (i < nargs) {
      let ar_f: i32 = pipeline_expr_call_arg_ref(arena, er, i);
      let pty_f: i32 = glue_call_param_type_ref_at(arena, er, i);
      is_sse_f[i] = glue_call_param_is_f32_c(arena, pty_f);
      spill_off_f[i] = 0 - 1;
      if (is_sse_f[i] != 0) {
        if (xmm_cur_f < 8) {
          gp_start_f[i] = xmm_cur_f;
          gp_units_f[i] = 1;
          xmm_cur_f = xmm_cur_f + 1;
        } else {
          gp_start_f[i] = 0 - 1;
          gp_units_f[i] = 0;
        }
      } else {
        let sz_f: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_f, ar_f);
        if (glue_sysv_arg_is_memory_by_value_c(sz_f) != 0) {
          gp_start_f[i] = 0 - 1;
          gp_units_f[i] = 0;
        } else {
          let u_f: i32 = glue_sysv_arg_gp_units_from_size_c(sz_f);
          gp_start_f[i] = gp_cur_f;
          gp_units_f[i] = u_f;
          if (u_f > 0) {
            if (gp_cur_f + u_f <= 6) {
              gp_cur_f = gp_cur_f + u_f;
            } else {
              gp_start_f[i] = 0 - 1;
            }
          } else {
            gp_start_f[i] = 0 - 1;
          }
        }
      }
      i = i + 1;
    }
    i = 0;
    while (i < nargs) {
      if (gp_start_f[i] >= 0) {
        let arg_ref_f: i32 = pipeline_expr_call_arg_ref(arena, er, i);
        if (arg_ref_f != 0) {
          if (glue_emit_one_call_arg_elf_c(arena, elf, er, arg_ref_f, i, ctx, ta) != 0) {
            pipeline_asm_emit_set_call_f32_xmm(0);
            return 0 - 1;
          }
          let so_f: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf, ctx, ta, gp_units_f[i]);
          if (so_f < 0) {
            pipeline_asm_emit_set_call_f32_xmm(0);
            return 0 - 1;
          }
          spill_off_f[i] = so_f;
        }
      }
      i = i + 1;
    }
    i = 0;
    while (i < nargs) {
      if (spill_off_f[i] >= 0) {
        if (is_sse_f[i] != 0) {
          if (backend_enc_load_rbp_to_rax_arch(elf, spill_off_f[i], ta) != 0) {
            pipeline_asm_emit_set_call_f32_xmm(0);
            return 0 - 1;
          }
          if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf, gp_start_f[i], ta) != 0) {
            pipeline_asm_emit_set_call_f32_xmm(0);
            return 0 - 1;
          }
        } else {
          if (glue_sysv_load_spill_to_arg_regs_elf_c(elf, ta, spill_off_f[i], gp_start_f[i], gp_units_f[i]) != 0) {
            pipeline_asm_emit_set_call_f32_xmm(0);
            return 0 - 1;
          }
        }
      }
      i = i + 1;
    }
    pipeline_asm_emit_set_call_f32_xmm(0);
    pipeline_asm_emit_set_call_param_type_ref(0);
    return 0;
  }
  return 0 - 1;
}

// See implementation.
/** Function `glue_emit_one_call_arg_elf_c`.
 * Purpose: implements `glue_emit_one_call_arg_elf_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function glue_emit_one_call_arg_elf_c(
  arena: *u8, elf_ctx: *u8, call_expr_ref: i32, arg_ref: i32, arg_index: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8) { return 0; }
  if (elf_ctx == 0) { return 0; }
  if (ctx == 0 as *u8) { return 0; }
  if (arg_ref == 0) { return 0; }
  unsafe {
    let pty0: i32 = glue_call_param_type_ref_at(arena, call_expr_ref, arg_index);
    pipeline_asm_emit_set_call_param_type_ref(pty0);
    pipeline_asm_emit_call_arg_begin_c();
    if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
      pipeline_asm_emit_call_arg_end_c();
      pipeline_asm_emit_set_call_param_type_ref(0);
      return 0 - 1;
    }
    let pty: i32 = glue_call_param_type_ref_at(arena, call_expr_ref, arg_index);
    // CALL=48
    if (pipeline_expr_kind_ord_at(arena, arg_ref) == 48) {
      if (pipeline_asm_call_struct16_ret_needs_rax_deref_c(arena, arg_ref) != 0) {
        if (pipeline_asm_deref_struct16_rax_ptr_elf_c(elf_ctx, ta) != 0) {
          pipeline_asm_emit_call_arg_end_c();
          pipeline_asm_emit_set_call_param_type_ref(0);
          return 0 - 1;
        }
      }
      if (glue_spill_struct16_call_arg_to_lea_elf_c(arena, elf_ctx, ctx, pty, ta) != 0) {
        pipeline_asm_emit_call_arg_end_c();
        pipeline_asm_emit_set_call_param_type_ref(0);
        return 0 - 1;
      }
    }
    pipeline_asm_emit_call_arg_end_c();
    pipeline_asm_emit_set_call_param_type_ref(0);
    return 0;
  }
  return 0;
}

// See implementation.
/** Function `glue_asm_build_call_export_sym_c`.
 * Build link symbol for EXPR_CALL with VAR callee (same-module + dep co-emit).
 * Dep-pool hits must score overload mid (mul Vec4f → mul_f32x4_f32x4), not bare
 * prefix+cname (STD-SIMD-INTRINSIC std_simd_mul UNDEF on Ubuntu pure .x path).
 * G.7 twin of seeds/backend_call_dispatch.from_x.c glue_asm_build_call_export_sym_c_impl.
 * @param arena *u8 — call-site AST arena
 * @param call_expr_ref i32 — EXPR_CALL expr ref
 * @param callee_ref i32 — EXPR_VAR callee ref
 * @param mod *u8 — emitting module (may equal dep_mod for co-emit bodies)
 * @param dep_pipe *u8 — PipelineDepCtx for dep_ix lookup
 * @param out *u8 — destination symbol buffer
 * @param out_cap i32 — capacity; must be > 0
 * @return i32 — symbol length, or -1 on failure
 * PLATFORM: SHARED — mac C _impl + Ubuntu pure .x must agree.
 */
#[no_mangle]
export function glue_asm_build_call_export_sym_c(
  arena: *u8, call_expr_ref: i32, callee_ref: i32, mod: *u8, dep_pipe: *u8, out: *u8, out_cap: i32
): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (callee_ref <= 0) { return 0 - 1; }
  if (out == 0 as *u8) { return 0 - 1; }
  if (out_cap <= 0) { return 0 - 1; }
  unsafe {
    let clen: i32 = pipeline_expr_var_name_len(arena, callee_ref);
    if (clen <= 0) { return 0 - 1; }
    if (clen > 127) { return 0 - 1; }
    let cname: u8[128] = [];
    pipeline_expr_var_name_into(arena, callee_ref, &cname[0]);
    /* Heap redirect: skip for std.heap.libc FFI and when a local body exists. */
    {
      let dep_path: *u8 = driver_get_current_dep_path_for_codegen();
      let skip_heap_redirect: i32 = 0;
      let has_local: i32 = 0;
      if (dep_path != 0 as *u8) {
        if (dep_path[0] != 0) {
          let p0: i32 = 0;
          while (p0 < 120) {
            if (dep_path[p0] == 0) { break; }
            if (dep_path[p0] == 104 && dep_path[p0 + 1] == 101 && dep_path[p0 + 2] == 97
                && dep_path[p0 + 3] == 112) {
              if (dep_path[p0 + 4] == 46 || dep_path[p0 + 4] == 47) {
                skip_heap_redirect = 1;
                break;
              }
            }
            p0 = p0 + 1;
          }
        }
      }
      if (mod != 0 as *u8) {
        let efi: i32 = 0;
        while (efi < pipeline_module_num_funcs(mod)) {
          if (pipeline_module_func_name_equal_at(mod, efi, &cname[0], clen) != 0) {
            if (pipeline_module_func_is_extern_at(mod, efi) != 0) {
              if (clen > 0) {
                if (clen < out_cap) {
                  let ci_e: i32 = 0;
                  while (ci_e < clen) {
                    out[ci_e] = cname[ci_e];
                    ci_e = ci_e + 1;
                  }
                  return clen;
                }
              }
              return 0 - 1;
            }
            has_local = 1;
          }
          efi = efi + 1;
        }
      }
      if (skip_heap_redirect == 0) {
        if (has_local == 0) {
          let rlen: i32 = glue_try_std_heap_redirect_sym_local(&cname[0], clen, out, out_cap);
          if (rlen > 0) { return rlen; }
        }
      }
    }
    let dep_ix: i32 = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
    if (dep_ix < 0) {
      if (dep_pipe != 0 as *u8) {
        let nd: i32 = pipeline_dep_ctx_ndep(dep_pipe);
        let j: i32 = 0;
        while (j < nd) {
          let dm: *u8 = pipeline_dep_ctx_module_at(dep_pipe, j);
          if (dm != 0 as *u8) {
            let nfunc: i32 = pipeline_module_num_funcs(dm);
            let fi: i32 = 0;
            while (fi < nfunc) {
              if (pipeline_module_func_name_equal_at(dm, fi, &cname[0], clen) != 0) {
                dep_ix = j;
                break;
              }
              fi = fi + 1;
            }
          }
          if (dep_ix >= 0) { break; }
          j = j + 1;
        }
      }
    }
    if (dep_ix >= 0) {
      if (dep_pipe != 0 as *u8) {
        let dep_mod: *u8 = pipeline_dep_ctx_module_at(dep_pipe, dep_ix);
        let dep_arena: *u8 = pipeline_dep_ctx_arena_at(dep_pipe, dep_ix);
        if (dep_mod != 0) {
          let saw_non_extern: i32 = 0;
          let fi2: i32 = 0;
          while (fi2 < pipeline_module_num_funcs(dep_mod)) {
            if (pipeline_module_func_name_equal_at(dep_mod, fi2, &cname[0], clen) != 0) {
              if (pipeline_module_func_is_extern_at(dep_mod, fi2) == 0) {
                saw_non_extern = 1;
                break;
              }
            }
            fi2 = fi2 + 1;
          }
          if (saw_non_extern == 0) {
            fi2 = 0;
            while (fi2 < pipeline_module_num_funcs(dep_mod)) {
              if (pipeline_module_func_name_equal_at(dep_mod, fi2, &cname[0], clen) != 0) {
                if (pipeline_module_func_is_extern_at(dep_mod, fi2) != 0) {
                  if (clen > 0) {
                    if (clen < out_cap) {
                      let ci_x: i32 = 0;
                      while (ci_x < clen) {
                        out[ci_x] = cname[ci_x];
                        ci_x = ci_x + 1;
                      }
                      return clen;
                    }
                  }
                  return 0 - 1;
                }
              }
              fi2 = fi2 + 1;
            }
          }
        }
        let path: u8[128] = [];
        let zi: i32 = 0;
        while (zi < 64) {
          path[zi] = 0;
          zi = zi + 1;
        }
        pipeline_dep_ctx_import_path_copy64(dep_pipe, dep_ix, &path[0]);
        if (path[0] != 0) {
          if (dep_mod != 0) {
            let want_np: i32 = pipeline_expr_call_num_args_at(arena, call_expr_ref);
            let use_fi: i32 = 0 - 1;
            let r_func: i32 = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref);
            let r_dep: i32 = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
            let mid: u8[128] = [];
            let mid_len: i32 = 0 - 1;
            let da: *u8 = dep_arena;
            if (da == 0 as *u8) { da = arena; }
            // CALL expr + resolved_func_index live in the caller arena.
            // Passing dep_arena here reads a different expr at the same ref
            // (STD-091: io_err_cancelled() emitted as std_error_base_fs).
            // PLATFORM: SHARED — typeck stamp/name scan; Ubuntu gold -o.
            use_fi = pipeline_typeck_resolve_call_func_index_for_emit_c(dep_mod, arena, call_expr_ref);
            if (use_fi >= 0) {
              if (use_fi >= pipeline_module_num_funcs(dep_mod)) {
                use_fi = 0 - 1;
              } else {
                if (pipeline_module_func_is_extern_at(dep_mod, use_fi) != 0) {
                  use_fi = 0 - 1;
                } else {
                  if (pipeline_module_func_name_equal_at(dep_mod, use_fi, &cname[0], clen) == 0) {
                    use_fi = 0 - 1;
                  } else {
                    if (pipeline_module_func_num_params_at(dep_mod, use_fi) != want_np) {
                      use_fi = 0 - 1;
                    }
                  }
                }
              }
            }
            if (use_fi < 0) {
              if (r_dep == dep_ix) {
                if (r_func >= 0) {
                  if (r_func < pipeline_module_num_funcs(dep_mod)) {
                    if (pipeline_module_func_is_extern_at(dep_mod, r_func) == 0) {
                      if (pipeline_module_func_name_equal_at(dep_mod, r_func, &cname[0], clen) != 0) {
                        if (pipeline_module_func_num_params_at(dep_mod, r_func) == want_np) {
                          use_fi = r_func;
                        }
                      }
                    }
                  }
                }
              }
            }
            if (use_fi < 0) {
              use_fi = glue_asm_score_import_binding_func_ix_c(
                arena, call_expr_ref, dep_mod, da, &cname[0], clen, want_np, 0, 0 as *i32
              );
            }
            let prefix: u8[128] = [];
            glue_codegen_import_path_to_c_prefix_into(&path[0], &prefix[0], 128);
            let plen: i32 = 0;
            while (plen < 127) {
              if (prefix[plen] == 0) { break; }
              plen = plen + 1;
            }
            if (plen > 0) {
              if (use_fi >= 0) {
                mid_len = glue_asm_build_func_overload_mid_c(dep_mod, da, use_fi, &mid[0], 64);
                if (mid_len > 0) {
                  return glue_asm_build_import_binding_call_sym(&prefix[0], plen, &mid[0], mid_len, out);
                }
              }
              return glue_asm_build_import_binding_call_sym(&prefix[0], plen, &cname[0], clen, out);
            }
          }
        }
      }
    }
    if (mod != 0 as *u8) {
      let want_np2: i32 = pipeline_expr_call_num_args_at(arena, call_expr_ref);
      let func_ix: i32 = pipeline_typeck_resolve_call_func_index_for_emit_c(mod, arena, call_expr_ref);
      if (func_ix < 0) {
        func_ix = glue_asm_score_import_binding_func_ix_c(
          arena, call_expr_ref, mod, arena, &cname[0], clen, want_np2, 0, 0 as *i32
        );
      }
      if (func_ix >= 0) {
        if (pipeline_module_func_is_extern_at(mod, func_ix) != 0) {
          if (clen > 0) {
            if (clen < out_cap) {
              let ci2: i32 = 0;
              while (ci2 < clen) {
                out[ci2] = cname[ci2];
                ci2 = ci2 + 1;
              }
              return clen;
            }
          }
          return 0 - 1;
        }
        return glue_asm_build_func_export_sym_c(mod, arena, func_ix, out, out_cap);
      }
    }
    if (clen > 0) {
      if (clen < out_cap) {
        let ci3: i32 = 0;
        while (ci3 < clen) {
          out[ci3] = cname[ci3];
          ci3 = ci3 + 1;
        }
        return clen;
      }
    }
  }
  return 0 - 1;
}

// glue_asm_build_dep_export_sym_c: see function docblock below.
/** Exported function `glue_asm_build_dep_export_sym_c`.
 * Implements `glue_asm_build_dep_export_sym_c`.
 * @param name *u8
 * @param name_len i32
 * @param out *u8
 * @param out_cap i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_build_dep_export_sym_c(name: *u8, name_len: i32, out: *u8, out_cap: i32): i32 {
  if (name == 0 as *u8) { return 0 - 1; }
  if (name_len <= 0) { return 0 - 1; }
  if (out == 0 as *u8) { return 0 - 1; }
  if (out_cap <= 0) { return 0 - 1; }
  unsafe {
    let dep_path: *u8 = driver_get_current_dep_path_for_codegen();
    let pos: i32 = 0;
    if (dep_path != 0) {
      if (dep_path[0] != 0) {
        let prefix: u8[128] = [];
        glue_codegen_import_path_to_c_prefix_into(dep_path, &prefix[0], 128);
        let plen: i32 = 0;
        while (plen < 127) {
          if (prefix[plen] == 0) { break; }
          plen = plen + 1;
        }
        if (plen > 0) {
          if (glue_asm_c_prefix_redundant_with_name(&prefix[0], plen, name, name_len) == 0) {
            let i: i32 = 0;
            while (i < plen) {
              if (pos >= out_cap - 1) { break; }
              out[pos] = prefix[i];
              pos = pos + 1;
              i = i + 1;
            }
          }
        }
      }
    }
    let j: i32 = 0;
    while (j < name_len) {
      if (pos >= out_cap - 1) { break; }
      out[pos] = name[j];
      pos = pos + 1;
      j = j + 1;
    }
    if (pos > 0) { return pos; }
  }
  return 0 - 1;
}

// glue_asm_build_func_export_sym_c: see function docblock below.
/** Exported function `glue_asm_build_func_export_sym_c`.
 * Build dep-prefixed export link symbol for func_ix (def emit + same-module CALL).
 * Unique names stay bare; overloads append param suffixes via glue_asm_type_ref_to_suffix_c
 * (VECTOR → f32x4 / i32x8, not glue_type_kind_to_suffix scalar fallback).
 * Same param-sig siblings append `_ret_<T>` (align seed glue_asm_build_func_export_sym_c_impl).
 * Why: dot(Vec4f){ mul(a,b) } must call std_simd_mul_f32x4_f32x4, not bare std_simd_mul
 * (STD-SIMD-INTRINSIC BLD001 on Ubuntu when .x used glue_type_kind_to_suffix for TYPE_VECTOR).
 * @param m *u8 — owning Module
 * @param a *u8 — arena for param/return type_refs
 * @param func_ix i32 — function index in m
 * @param out *u8 — destination symbol buffer
 * @param out_cap i32 — capacity; must be > 0
 * @return i32 — symbol length, or -1 on failure
 * PLATFORM: SHARED — G.7 twin of seeds/backend_call_dispatch.from_x.c impl authority.
 */
#[no_mangle]
export function glue_asm_build_func_export_sym_c(m: *u8, a: *u8, func_ix: i32, out: *u8, out_cap: i32): i32 {
  if (m == 0) { return 0 - 1; }
  if (a == 0) { return 0 - 1; }
  if (func_ix < 0) { return 0 - 1; }
  if (out == 0 as *u8) { return 0 - 1; }
  if (out_cap <= 0) { return 0 - 1; }
  unsafe {
    let fname_len: i32 = pipeline_asm_module_func_name_len_at(m, func_ix);
    if (fname_len <= 0) { return 0 - 1; }
    if (fname_len > 127) { return 0 - 1; }
    let fname: u8[128] = [];
    pipeline_asm_module_func_name_copy64(m, func_ix, &fname[0]);
    if (glue_module_func_overload_count_c(m, &fname[0], fname_len) <= 1) {
      let pos0: i32 = glue_asm_build_dep_export_sym_c(&fname[0], fname_len, out, out_cap);
      if (pos0 <= 0) { return 0 - 1; }
      if (glue_asm_std_c_wrapper_fname_needs_export_c_suffix(&fname[0], fname_len) != 0) {
        pos0 = glue_asm_append_export_c_suffix(out, pos0, out_cap);
      }
      if (pos0 > 0) { return pos0; }
      return 0 - 1;
    }
    let pos: i32 = glue_asm_build_dep_export_sym_c(&fname[0], fname_len, out, out_cap);
    if (pos <= 0) { return 0 - 1; }
    let np: i32 = pipeline_module_func_num_params_at(m, func_ix);
    let pi: i32 = 0;
    while (pi < np) {
      if (pos >= out_cap - 2) { break; }
      let pty: i32 = pipeline_module_func_param_type_ref_at(m, func_ix, pi);
      if (pty > 0) {
        let suf: u8[64] = [];
        let sl: i32 = glue_asm_type_ref_to_suffix_c(a, pty, &suf[0], 64);
        if (sl <= 0) {
          pi = pi + 1;
          continue;
        }
        if (pos >= out_cap - 1) { break; }
        out[pos] = 95;
        pos = pos + 1;
        if (pos + sl >= out_cap) { return 0 - 1; }
        let si: i32 = 0;
        while (si < sl) {
          out[pos] = suf[si];
          pos = pos + 1;
          si = si + 1;
        }
      }
      pi = pi + 1;
    }
    /* Same param-sig overloads: append _ret_<T> (e.g. vec.new → new_i32_retVec_u8). */
    let sig_count: i32 = glue_asm_overload_param_sig_count_c(a, m, func_ix);
    if (sig_count > 1) {
      let ret_ref: i32 = pipeline_module_func_return_type_at(m, func_ix);
      let rsuf: u8[64] = [];
      let rsl: i32 = glue_asm_type_ref_to_suffix_c(a, ret_ref, &rsuf[0], 64);
      if (rsl > 0) {
        if (pos + 4 + rsl >= out_cap) { return 0 - 1; }
        out[pos] = 95;
        out[pos + 1] = 114;
        out[pos + 2] = 101;
        out[pos + 3] = 116;
        pos = pos + 4;
        let ri: i32 = 0;
        while (ri < rsl) {
          out[pos] = rsuf[ri];
          pos = pos + 1;
          ri = ri + 1;
        }
      }
    }
    if (glue_asm_std_c_wrapper_fname_needs_export_c_suffix(&fname[0], fname_len) != 0) {
      pos = glue_asm_append_export_c_suffix(out, pos, out_cap);
    }
    if (pos > 0) { return pos; }
  }
  return 0 - 1;
}

// See implementation.
// See implementation.
/** Function `glue_asm_try_emit_fmt_string_lit_import_call_elf_c`.
 * Purpose: implements `glue_asm_try_emit_fmt_string_lit_import_call_elf_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
/**
 * Embed STRING_LIT + call std_fmt_print/println(ptr,len) for fmt/debug binding.
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — platform_elf_ElfCodegenCtx bytes
 * @param call_expr_ref i32 — EXPR_CALL or EXPR_METHOD_CALL (hello fmt.println is METHOD_CALL)
 * @param ctx *u8 — AsmFuncCtx
 * @param ta i32 — 0=x86_64, 1=aarch64; other → skip (return 0)
 * @param pre_buf *u8 — C prefix e.g. std_fmt_
 * @param pre_len i32 — prefix length
 * @param field_name *u8 — print or println
 * @param field_len i32 — 5 or 7
 * @return i32 — 1 emitted, 0 not applicable, -1 hard fail
 * PLATFORM: SHARED — METHOD_CALL + CALL; wave108 opens aarch64 (ADR x0 + mov len w1).
 */
#[no_mangle]
export function glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
  arena: *u8, elf_ctx: *u8, call_expr_ref: i32, ctx: *u8, ta: i32,
  pre_buf: *u8, pre_len: i32, field_name: *u8, field_len: i32
): i32 {
  if (arena == 0 as *u8) { return 0; }
  if (elf_ctx == 0) { return 0; }
  if (ctx == 0 as *u8) { return 0; }
  if (call_expr_ref <= 0) { return 0; }
  if (ta != 0) {
    if (ta != 1) { return 0; }
  }
  unsafe {
    if (glue_asm_prefix_is_fmt_or_debug(pre_buf, pre_len) == 0) { return 0; }
    let is_ln: i32 = 0;
    if (field_len == 7) {
      // println
      if (field_name[0]==112&&field_name[1]==114&&field_name[2]==105&&field_name[3]==110
          &&field_name[4]==116&&field_name[5]==108&&field_name[6]==110) {
        is_ln = 1;
      } else {
        return 0;
      }
    } else {
      if (field_len == 5) {
        // print
        if (field_name[0]==112&&field_name[1]==114&&field_name[2]==105&&field_name[3]==110&&field_name[4]==116) {
          is_ln = 0;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    }
    // PLATFORM: SHARED — METHOD_CALL (49) vs CALL (48) arg accessors.
    let expr_ko: i32 = pipeline_expr_kind_ord_at(arena, call_expr_ref);
    let nargs: i32 = 0;
    let arg_ref: i32 = 0;
    if (expr_ko == 49) {
      nargs = pipeline_expr_method_call_num_args_at(arena, call_expr_ref);
      if (nargs == 1) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, call_expr_ref, 0);
      }
    } else {
      nargs = pipeline_expr_call_num_args_at(arena, call_expr_ref);
      if (nargs == 1) {
        arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, 0);
      }
    }
    if (nargs != 1) { return 0; }
    if (arg_ref <= 0) { return 0; }
    if (pipeline_expr_kind_ord_at(arena, arg_ref) != 59) { return 0; }
    let slen: i32 = glue_asm_string_lit_len(arena, arg_ref);
    // Stage 12.2.5: empty OK; long string lit up to 126.
    if (slen < 0) { return 0 - 1; }
    if (slen > 126) { return 0 - 1; }
    let sbuf: u8[128] = [];
    glue_asm_string_lit_into(arena, arg_ref, &sbuf[0]);
    let sym_flat: u8[128] = [];
    // Bare std_fmt_println — not overload mid println_i32_reti32.
    let sym_len: i32 = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, field_name, field_len, &sym_flat[0]);
    if (sym_len <= 0) { return 0 - 1; }
    if (is_ln == 0) { /* print */ }
    if (glue_asm_emit_jmp_skip_string_then_lea(elf_ctx, ta, 0, &sbuf[0], slen) != 0) {
      return 0 - 1;
    }
    // aarch64: len → w1 via rbx alias (do not clobber ptr in x0 with mov w0).
    if (ta == 1) {
      if (backend_enc_mov_imm32_to_rbx_arch(elf_ctx, slen, ta) != 0) { return 0 - 1; }
    } else {
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, slen, ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0) { return 0 - 1; }
    }
    if (glue_asm_enc_call_redirected(elf_ctx, &sym_flat[0], sym_len, ta) != 0) { return 0 - 1; }
    return 1;
  }
  return 0;
}

/**
 * Append decimal digits of v (>=0) into out[pos..). Returns new pos, or -1 on overflow.
 * PLATFORM: SHARED — fmt-any schema builder helper.
 */
function glue_asm_fmt_any_append_dec(out: *u8, cap: i32, pos: i32, v: i32): i32 {
  let digs: u8[12] = [];
  let nd: i32 = 0;
  let x: i32 = v;
  let i: i32 = 0;
  if (out == 0 as *u8 || cap <= 0 || pos < 0) { return 0 - 1; }
  if (x < 0) { return 0 - 1; }
  if (x == 0) {
    if (pos >= cap) { return 0 - 1; }
    out[pos] = 48;
    return pos + 1;
  }
  while (x > 0) {
    if (nd >= 11) { return 0 - 1; }
    digs[nd] = ((x % 10) + 48) as u8;
    nd = nd + 1;
    x = x / 10;
  }
  i = nd;
  while (i > 0) {
    i = i - 1;
    if (pos >= cap) { return 0 - 1; }
    out[pos] = digs[i];
    pos = pos + 1;
  }
  return pos;
}

/**
 * Find struct layout index by type name in module. Returns -1 if missing.
 * PLATFORM: SHARED — G.7 twin of typeck_find_layout_idx_by_type_name (pipeline face).
 */
function glue_asm_fmt_any_find_layout(m: *u8, nm: *u8, nlen: i32): i32 {
  let n: i32 = 0;
  let k: i32 = 0;
  let ln: i32 = 0;
  let buf: u8[128] = [];
  let i: i32 = 0;
  if (m == 0 as *u8 || nm == 0 as *u8 || nlen <= 0) { return 0 - 1; }
  n = pipeline_module_num_struct_layouts_at(m);
  while (k < n) {
    ln = pipeline_module_struct_layout_name_len(m, k);
    if (ln == nlen && ln > 0 && ln <= 127) {
      pipeline_module_struct_layout_name_into(m, k, &buf[0]);
      i = 0;
      while (i < nlen) {
        if (buf[i] != nm[i]) { break; }
        i = i + 1;
      }
      if (i == nlen) { return k; }
    }
    k = k + 1;
  }
  return 0 - 1;
}

/**
 * Build JSON schema for type_ref into out (no trailing NUL). Returns length, or -1.
 * Offsets are absolute from the value base (base_off added for nested structs).
 * Supports i32/bool fields, nested NAMED, i32[N], u8[N], i32[] (fat A@OFF),
 * Option_* {is_some,value}. u8[] returns -1 so emit falls through to u8_slc mid.
 * PLATFORM: SHARED — print_any product shapes; schema max fits jmp_skip 126.
 */
function glue_asm_fmt_any_build_schema(m: *u8, arena: *u8, ty: i32, out: *u8, cap: i32,
base_off: i32, depth: i32): i32 {
  let tk: i32 = 0;
  let pos: i32 = 0;
  let elem: i32 = 0;
  let asz: i32 = 0;
  let etk: i32 = 0;
  let nm: u8[128] = [];
  let nlen: i32 = 0;
  let li: i32 = 0;
  let nf: i32 = 0;
  let j: i32 = 0;
  let fnm: u8[64] = [];
  let fnl: i32 = 0;
  let fty: i32 = 0;
  let foff: i32 = 0;
  let ftk: i32 = 0;
  let is_some_j: i32 = 0 - 1;
  let value_j: i32 = 0 - 1;
  let sub: i32 = 0;
  let is_opt: i32 = 0;
  if (m == 0 as *u8 || arena == 0 as *u8 || out == 0 as *u8 || ty <= 0 || cap <= 0) {
    return 0 - 1;
  }
  if (depth > 4) { return 0 - 1; }
  tk = pipeline_type_kind_ord_at(arena, ty);
  /* TYPE_I32=0 */
  if (tk == 0) {
    if (pos + 2 >= cap) { return 0 - 1; }
    out[pos] = 105; /* i */
    out[pos + 1] = 64; /* @ */
    pos = pos + 2;
    return glue_asm_fmt_any_append_dec(out, cap, pos, base_off);
  }
  /* TYPE_BOOL=1 */
  if (tk == 1) {
    if (pos + 2 >= cap) { return 0 - 1; }
    out[pos] = 98; /* b */
    out[pos + 1] = 64;
    pos = pos + 2;
    return glue_asm_fmt_any_append_dec(out, cap, pos, base_off);
  }
  /* TYPE_ARRAY=10 */
  if (tk == 10) {
    elem = pipeline_type_elem_ref_at(arena, ty);
    asz = pipeline_type_array_size_at(arena, ty);
    if (elem <= 0 || asz <= 0) { return 0 - 1; }
    etk = pipeline_type_kind_ord_at(arena, elem);
    /* u8=2 → u@off,len */
    if (etk == 2) {
      if (pos + 2 >= cap) { return 0 - 1; }
      out[pos] = 117;
      out[pos + 1] = 64;
      pos = pos + 2;
      pos = glue_asm_fmt_any_append_dec(out, cap, pos, base_off);
      if (pos < 0) { return 0 - 1; }
      if (pos >= cap) { return 0 - 1; }
      out[pos] = 44; /* , */
      pos = pos + 1;
      return glue_asm_fmt_any_append_dec(out, cap, pos, asz);
    }
    /* i32=0 → a@off,len */
    if (etk == 0) {
      if (pos + 2 >= cap) { return 0 - 1; }
      out[pos] = 97;
      out[pos + 1] = 64;
      pos = pos + 2;
      pos = glue_asm_fmt_any_append_dec(out, cap, pos, base_off);
      if (pos < 0) { return 0 - 1; }
      if (pos >= cap) { return 0 - 1; }
      out[pos] = 44;
      pos = pos + 1;
      return glue_asm_fmt_any_append_dec(out, cap, pos, asz);
    }
    return 0 - 1;
  }
  /* TYPE_SLICE=11 — i32[] → A@off (fat {data,len}); u8[] → -1 (u8_slc mid). */
  if (tk == 11) {
    elem = pipeline_type_elem_ref_at(arena, ty);
    if (elem <= 0) { return 0 - 1; }
    etk = pipeline_type_kind_ord_at(arena, elem);
    /* u8=2: keep product mid std_fmt_*_u8_slc (raw bytes). */
    if (etk == 2) { return 0 - 1; }
    /* i32=0 → A@off */
    if (etk == 0) {
      if (pos + 2 >= cap) { return 0 - 1; }
      out[pos] = 65; /* A */
      out[pos + 1] = 64; /* @ */
      pos = pos + 2;
      return glue_asm_fmt_any_append_dec(out, cap, pos, base_off);
    }
    return 0 - 1;
  }
  /* TYPE_NAMED=8 */
  if (tk != 8) { return 0 - 1; }
  nlen = pipeline_type_named_name_into(arena, ty, &nm[0]);
  if (nlen <= 0 || nlen > 127) { return 0 - 1; }
  li = glue_asm_fmt_any_find_layout(m, &nm[0], nlen);
  if (li < 0) { return 0 - 1; }
  nf = pipeline_module_struct_layout_num_fields(m, li);
  if (nf <= 0) { return 0 - 1; }
  /* Option_* with is_some + value → ?soff:val_schema */
  if (nlen >= 7) {
    if (nm[0] == 79 && nm[1] == 112 && nm[2] == 116 && nm[3] == 105
        && nm[4] == 111 && nm[5] == 110 && nm[6] == 95) {
      is_opt = 1;
    }
  }
  if (is_opt != 0) {
    j = 0;
    while (j < nf) {
      fnl = pipeline_module_struct_layout_field_name_len(m, li, j);
      if (fnl > 0 && fnl <= 63) {
        pipeline_module_struct_layout_field_name_into(m, li, j, &fnm[0]);
        if (fnl == 7 && fnm[0] == 105 && fnm[1] == 115 && fnm[2] == 95
            && fnm[3] == 115 && fnm[4] == 111 && fnm[5] == 109 && fnm[6] == 101) {
          is_some_j = j;
        }
        if (fnl == 5 && fnm[0] == 118 && fnm[1] == 97 && fnm[2] == 108
            && fnm[3] == 117 && fnm[4] == 101) {
          value_j = j;
        }
      }
      j = j + 1;
    }
    if (is_some_j >= 0 && value_j >= 0) {
      foff = pipeline_module_struct_layout_field_offset_at(m, li, is_some_j);
      if (pos >= cap) { return 0 - 1; }
      out[pos] = 63; /* ? */
      pos = pos + 1;
      pos = glue_asm_fmt_any_append_dec(out, cap, pos, base_off + foff);
      if (pos < 0) { return 0 - 1; }
      if (pos >= cap) { return 0 - 1; }
      out[pos] = 58; /* : */
      pos = pos + 1;
      fty = pipeline_module_struct_layout_field_type_ref(m, li, value_j);
      foff = pipeline_module_struct_layout_field_offset_at(m, li, value_j);
      {
        let scratch: u8[128] = [];
        let si: i32 = 0;
        sub = glue_asm_fmt_any_build_schema(m, arena, fty, &scratch[0], 128,
          base_off + foff, depth + 1);
        if (sub < 0) { return 0 - 1; }
        if (pos + sub > cap) { return 0 - 1; }
        while (si < sub) {
          out[pos] = scratch[si];
          pos = pos + 1;
          si = si + 1;
        }
        return pos;
      }
    }
  }
  /* Generic struct object */
  if (pos >= cap) { return 0 - 1; }
  out[pos] = 123; /* { */
  pos = pos + 1;
  j = 0;
  while (j < nf) {
    if (j > 0) {
      if (pos >= cap) { return 0 - 1; }
      out[pos] = 44;
      pos = pos + 1;
    }
    fnl = pipeline_module_struct_layout_field_name_len(m, li, j);
    if (fnl <= 0 || fnl > 63) { return 0 - 1; }
    pipeline_module_struct_layout_field_name_into(m, li, j, &fnm[0]);
    if (pos + fnl + 1 >= cap) { return 0 - 1; }
    let ci: i32 = 0;
    while (ci < fnl) {
      out[pos] = fnm[ci];
      pos = pos + 1;
      ci = ci + 1;
    }
    out[pos] = 58;
    pos = pos + 1;
    fty = pipeline_module_struct_layout_field_type_ref(m, li, j);
    foff = pipeline_module_struct_layout_field_offset_at(m, li, j);
    ftk = pipeline_type_kind_ord_at(arena, fty);
    if (ftk == 0 || ftk == 1 || ftk == 8 || ftk == 10 || ftk == 11) {
      let scratch2: u8[128] = [];
      let sj: i32 = 0;
      sub = glue_asm_fmt_any_build_schema(m, arena, fty, &scratch2[0], 128,
        base_off + foff, depth + 1);
      if (sub < 0) { return 0 - 1; }
      if (pos + sub > cap) { return 0 - 1; }
      while (sj < sub) {
        out[pos] = scratch2[sj];
        pos = pos + 1;
        sj = sj + 1;
      }
    } else {
      return 0 - 1;
    }
    j = j + 1;
  }
  if (pos >= cap) { return 0 - 1; }
  out[pos] = 125; /* } */
  pos = pos + 1;
  return pos;
}

/**
 * Emit std.fmt/std.debug print/println(composite) as JSON via schema stub.
 * Sibling of glue_asm_try_emit_fmt_string_lit_import_call_elf_c.
 * @return i32 — 1 emitted, 0 not applicable, -1 hard fail
 * PLATFORM: SHARED — print_any; calls std_fmt_json_println_schema / _print_schema.
 */
#[no_mangle]
export function glue_asm_try_emit_fmt_any_import_call_elf_c(
  arena: *u8, elf_ctx: *u8, call_expr_ref: i32, ctx: *u8, ta: i32,
  pre_buf: *u8, pre_len: i32, field_name: *u8, field_len: i32
): i32 {
  if (arena == 0 as *u8) { return 0; }
  if (elf_ctx == 0) { return 0; }
  if (ctx == 0 as *u8) { return 0; }
  if (call_expr_ref <= 0) { return 0; }
  if (ta != 0) {
    if (ta != 1) { return 0; }
  }
  unsafe {
    if (glue_asm_prefix_is_fmt_or_debug(pre_buf, pre_len) == 0) { return 0; }
    let is_ln: i32 = 0;
    if (field_len == 7) {
      if (field_name[0]==112&&field_name[1]==114&&field_name[2]==105&&field_name[3]==110
          &&field_name[4]==116&&field_name[5]==108&&field_name[6]==110) {
        is_ln = 1;
      } else {
        return 0;
      }
    } else {
      if (field_len == 5) {
        if (field_name[0]==112&&field_name[1]==114&&field_name[2]==105&&field_name[3]==110&&field_name[4]==116) {
          is_ln = 0;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    }
    let expr_ko: i32 = pipeline_expr_kind_ord_at(arena, call_expr_ref);
    let nargs: i32 = 0;
    let arg_ref: i32 = 0;
    if (expr_ko == 49) {
      nargs = pipeline_expr_method_call_num_args_at(arena, call_expr_ref);
      if (nargs == 1) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, call_expr_ref, 0);
      }
    } else {
      nargs = pipeline_expr_call_num_args_at(arena, call_expr_ref);
      if (nargs == 1) {
        arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, 0);
      }
    }
    if (nargs != 1) { return 0; }
    if (arg_ref <= 0) { return 0; }
    /* String lit → sibling path. */
    if (pipeline_expr_kind_ord_at(arena, arg_ref) == 59) { return 0; }
    let arg_ty: i32 = pipeline_expr_resolved_type_ref(arena, arg_ref);
    if (arg_ty <= 0) { return 0; }
    let atk: i32 = pipeline_type_kind_ord_at(arena, arg_ty);
    /* Scalars → normal overload. NAMED/ARRAY/SLICE(non-u8) → schema; u8[] mid. */
    if (atk != 8 && atk != 10 && atk != 11) { return 0; }
    /* u8[N]/NAMED/i32[N]/i32[] via schema. u8[] build_schema -1 → u8_slc mid. */
    /* Only VAR lvalues for address (print_any shapes). */
    if (pipeline_expr_kind_ord_at(arena, arg_ref) != 3) { return 0; }
    let mod_ref: *u8 = call_dispatch_load_ptr_le(ctx, 16);
    if (mod_ref == 0 as *u8) { return 0; }
    let sch: u8[128] = [];
    let slen: i32 = glue_asm_fmt_any_build_schema(mod_ref, arena, arg_ty, &sch[0], 126, 0, 0);
    if (slen <= 0) { return 0; }
    if (slen > 126) { return 0; }
    /*
     * Spill base to frame (SHARED): aarch64 mov_rax_to_rbx also writes x1;
     * mov_rax_to_arg_reg(1) clobbers x1; mov_rbx_to_rax reads x1 not x19.
     */
    let spill: i32 = call_dispatch_load_i32_le(ctx, 4);
    if (spill < 16) { spill = 16; }
    call_dispatch_store_i32_le(ctx, 4, spill + 8);
    if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
      return 0 - 1;
    }
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, spill, ta) != 0) { return 0 - 1; }
    if (glue_asm_emit_jmp_skip_string_then_lea(elf_ctx, ta, 1, &sch[0], slen) != 0) {
      return 0 - 1;
    }
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0) { return 0 - 1; }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill, ta) != 0) { return 0 - 1; }
    if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
    let sym: u8[40] = [];
    let sn: i32 = 0;
    /* std_fmt_json_println_schema / std_fmt_json_print_schema */
    let pfx: u8[16] = [];
    pfx[0]=115;pfx[1]=116;pfx[2]=100;pfx[3]=95;pfx[4]=102;pfx[5]=109;pfx[6]=116;pfx[7]=95;
    pfx[8]=106;pfx[9]=115;pfx[10]=111;pfx[11]=110;pfx[12]=95;
    sn = 0;
    while (sn < 13) {
      sym[sn] = pfx[sn];
      sn = sn + 1;
    }
    if (is_ln != 0) {
      /* println_schema */
      let t1: u8[16] = [];
      t1[0]=112;t1[1]=114;t1[2]=105;t1[3]=110;t1[4]=116;t1[5]=108;t1[6]=110;
      t1[7]=95;t1[8]=115;t1[9]=99;t1[10]=104;t1[11]=101;t1[12]=109;t1[13]=97;
      let ti: i32 = 0;
      while (ti < 14) {
        sym[sn] = t1[ti];
        sn = sn + 1;
        ti = ti + 1;
      }
    } else {
      /* print_schema */
      let t0: u8[16] = [];
      t0[0]=112;t0[1]=114;t0[2]=105;t0[3]=110;t0[4]=116;t0[5]=95;
      t0[6]=115;t0[7]=99;t0[8]=104;t0[9]=101;t0[10]=109;t0[11]=97;
      let tj: i32 = 0;
      while (tj < 12) {
        sym[sn] = t0[tj];
        sn = sn + 1;
        tj = tj + 1;
      }
    }
    if (glue_asm_enc_call_redirected(elf_ctx, &sym[0], sn, ta) != 0) { return 0 - 1; }
    return 1;
  }
  return 0;
}

// glue_asm_enc_call_redirected: see function docblock below.
/** Exported function `glue_asm_enc_call_redirected`.
 * Implements `glue_asm_enc_call_redirected`.
 * @param elf_ctx *u8
 * @param name *u8
 * @param name_len i32
 * @param ta i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_enc_call_redirected(elf_ctx: *u8, name: *u8, name_len: i32, ta: i32): i32 {
  if (name == 0 as *u8) { return 0 - 1; }
  if (name_len <= 0) { return 0 - 1; }
  unsafe {
    let redir: u8[128] = [];
    let rlen: i32 = glue_try_std_heap_redirect_sym_local(name, name_len, &redir[0], 64);
    if (rlen <= 0) {
      rlen = glue_try_std_string_xlang_redirect_sym_local(name, name_len, &redir[0], 64);
    }
    if (rlen <= 0) {
      rlen = glue_try_std_encoding_redirect_sym_local(name, name_len, &redir[0], 64);
    }
    if (rlen <= 0) {
      rlen = pipeline_asm_redirect_std_c_wrapper_sym(name, name_len, &redir[0], 64);
    }
    if (rlen > 0) {
      return backend_enc_call_arch(elf_ctx, &redir[0], rlen, ta);
    }
    return backend_enc_call_arch(elf_ctx, name, name_len, ta);
  }
  return 0 - 1;
}

// GLUE_ASM_MAX_CALL_ARGS=96
/**
 * Emit freestanding CALL args into SysV/AAPCS register/stack homes.
 * wave214 root fix (G.7 有则补全): x86 path must spill-then-load with dual-GP
 * unit accounting. Prior pure surface placed by arg *index* into GP *index*, so
 * `set_in(WithArr, i, v)` put v in rdx then struct dual-load clobbered it →
 * Ubuntu assign_index_struct_field panic 134 (i became 15).
 * Stage 12.0.5: AAPCS64 spill-then-load + stack-before-GP-reload (seed twin).
 * Root: high-to-low direct place then stack emit→x0 clobbered arg0 (rt_eq6 c=0x3e).
 * Authority matches seeds/backend_call_dispatch.from_x.c (wave392/600/601 + 12.0.5).
 * PLATFORM: SHARED — LINUX+MACOS x86_64 SysV dual-GP; MACOS|ARM64 AAPCS64 spill.
 */
#[no_mangle]
export function pipeline_asm_emit_call_args_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32, nargs: i32
): i32 {
  if (nargs < 0) { return 0 - 1; }
  if (nargs > 96) { return 0 - 1; }
  unsafe {
    let reg_max: i32 = glue_asm_call_reg_max(ta);
    // Prefer f32-xmm classifier when enabled and no sret shift (sret not implemented there).
    if (ta == 0) {
      if (pipeline_asm_abi_f32_xmm_enabled_c() != 0) {
        if (pipeline_asm_emit_call_sret_reg_shift_c() == 0) {
          return glue_emit_call_args_elf_sysv_f32_xmm_c(arena, elf_ctx, expr_ref, ctx, ta, nargs);
        }
      }
    }
    let sret_sh: i32 = 0;
    if (ta == 0) {
      sret_sh = pipeline_asm_emit_call_sret_reg_shift_c();
    }
    let eff_reg_max: i32 = reg_max - sret_sh;
    if (ta == 2) { return 0 - 1; }

    // Stack reserve: x86 uses dual-GP-aware n_stack (wave601), not nargs-reg_max alone.
    let stack_reserve: i32 = 0;
    if (ta == 0) {
      if (arena != 0 as *u8) {
        if (expr_ref > 0) {
          let nw: i32 = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
          stack_reserve = nw * 8;
          if (nw > 0) {
            if ((nw & 1) != 0) { stack_reserve = stack_reserve + 8; }
          }
        }
      }
    } else if (ta == 1) {
      /* wave603: AAPCS64 stack words include MEMORY multi-word (≡ x86 wave601),
       * not nargs-reg_max alone. Align 16 for arm64 SP.
       * PLATFORM: MACOS|ARM64 AAPCS64. */
      let nw_a: i32 = 0;
      let gp_tmp: i32 = 0;
      let j_a: i32 = 0;
      while (j_a < nargs) {
        let ar_j: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, j_a);
        let pty_j: i32 = glue_call_param_type_ref_at(arena, expr_ref, j_a);
        let sz_j: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_j, ar_j);
        let u_j: i32 = glue_sysv_arg_gp_units_from_size_c(sz_j);
        let w_j: i32 = glue_sysv_arg_stack_words_c(sz_j, u_j);
        if (glue_sysv_arg_is_memory_by_value_c(sz_j) != 0) {
          nw_a = nw_a + w_j;
        } else if (u_j > 0 && gp_tmp + u_j <= reg_max) {
          gp_tmp = gp_tmp + u_j;
        } else {
          if (w_j > 0) {
            nw_a = nw_a + w_j;
          } else {
            nw_a = nw_a + 1;
          }
        }
        j_a = j_a + 1;
      }
      stack_reserve = nw_a * 8;
      if (stack_reserve > 0) {
        stack_reserve = (stack_reserve + 15) & (0 - 16);
      }
    } else {
      stack_reserve = glue_asm_call_stack_cleanup_bytes(ta, nargs);
    }
    if (stack_reserve < 0) { return 0 - 1; }
    if (backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve, ta) != 0) { return 0 - 1; }

    // x86: push stack-class args right-to-left (kind==2).
    if (ta == 0) {
      let nw2: i32 = glue_sysv_x86_call_n_stack_c(arena, expr_ref, nargs);
      if (nw2 > 0) {
        if ((nw2 & 1) != 0) {
          if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
        }
      }
      let i0: i32 = nargs - 1;
      while (i0 >= 0) {
        let kind_i: i32 = 0;
        let reg_k_i: i32 = 0;
        let stack_k_i: i32 = 0;
        let arg_ref0: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i0);
        if (arg_ref0 != 0) {
          glue_sysv_x86_call_arg_slot_c(arena, expr_ref, nargs, i0, &kind_i, &reg_k_i, &stack_k_i);
          if (kind_i == 2) {
            /*
             * G.7: >16B MEMORY by-value must multi-qword push (seed wave601).
             * emit+push rax left INDEX/FIELD leave-addr as the first 8B
             * (take_w(a[1]) on Wide → .e miss). Reuse
             * pipeline_asm_push_sysv_memory_by_value_elf_c (INDEX now
             * shares the FIELD lvalue loop). Do not invent a second copy.
             * PLATFORM: LINUX+MACOS x86_64 SysV.
             */
            let pty0: i32 = glue_call_param_type_ref_at(arena, expr_ref, i0);
            let sz0: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty0, arg_ref0);
            if (glue_sysv_arg_is_memory_by_value_c(sz0) != 0) {
              let pushed0: i32 = pipeline_asm_push_sysv_memory_by_value_elf_c(
                arena, elf_ctx, ctx, arg_ref0, sz0, ta);
              if (pushed0 < 0) { return 0 - 1; }
            } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref0, i0, ctx, ta) != 0) {
              return 0 - 1;
            } else if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) {
              return 0 - 1;
            }
          }
        }
        i0 = i0 - 1;
      }
    }

    /*
     * AAPCS64: spill-then-load (wave392/600) + stack-before-GP-reload (Stage 12.0.5).
     * Order: classify → emit+spill GP → place stack (x0 temp OK) → load GPs high→low.
     * PLATFORM: MACOS|ARM64 AAPCS64 · SHARED freestanding multi-arg.
     */
    if (ta == 1) {
      let gp_start: i32[96] = [];
      let gp_units: i32[96] = [];
      let spill_off: i32[96] = [];
      let arg_sz_a: i32[96] = [];
      let is_mem_a: i32[96] = [];
      let gp_cur: i32 = 0;
      let i: i32 = 0;
      while (i < nargs) {
        let ar_i: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        let pty_i: i32 = glue_call_param_type_ref_at(arena, expr_ref, i);
        let sz_i: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, ar_i);
        spill_off[i] = 0 - 1;
        arg_sz_a[i] = sz_i;
        is_mem_a[i] = glue_sysv_arg_is_memory_by_value_c(sz_i);
        if (is_mem_a[i] != 0) {
          gp_start[i] = 0 - 1;
          gp_units[i] = 0;
        } else {
          let u: i32 = glue_sysv_arg_gp_units_from_size_c(sz_i);
          if (u < 1) { u = 1; }
          if (u > 2) { u = 2; }
          gp_start[i] = gp_cur;
          gp_units[i] = u;
          if (gp_cur + u <= reg_max) {
            gp_cur = gp_cur + u;
          } else {
            gp_start[i] = 0 - 1;
          }
        }
        i = i + 1;
      }
      // Emit + spill register-class args.
      i = 0;
      while (i < nargs) {
        if (gp_start[i] >= 0) {
          let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
          if (arg_ref != 0) {
            if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0) {
              return 0 - 1;
            }
            let so: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units[i]);
            if (so < 0) { return 0 - 1; }
            spill_off[i] = so;
          }
        }
        i = i + 1;
      }
      // Stack / MEMORY: materialize *before* final GP load (do not clobber x0).
      // wave603: MEMORY multi-word via store_to_sp (INDEX/FIELD lvalue copy).
      // PLATFORM: MACOS|ARM64 AAPCS64.
      let stk_slot: i32 = 0;
      i = 0;
      while (i < nargs) {
        if (gp_start[i] < 0) {
          let arg_ref2: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
          if (arg_ref2 != 0) {
            if (is_mem_a[i] != 0) {
              let stored: i32 = pipeline_asm_store_memory_by_value_to_sp_elf_c(
                arena, elf_ctx, ctx, arg_ref2, arg_sz_a[i], ta, stk_slot * 8);
              if (stored < 0) { return 0 - 1; }
              let words: i32 = stored / 8;
              if (words < 1) { words = 1; }
              stk_slot = stk_slot + words;
            } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref2, i, ctx, ta) != 0) {
              return 0 - 1;
            } else if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0) {
              return 0 - 1;
            } else {
              stk_slot = stk_slot + 1;
            }
          }
        }
        i = i + 1;
      }
      // Load spills high→low so x0 temp does not wipe lower final GPs.
      i = nargs - 1;
      while (i >= 0) {
        if (spill_off[i] >= 0) {
          if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], gp_start[i], gp_units[i]) != 0) {
            return 0 - 1;
          }
        }
        i = i - 1;
      }
      pipeline_asm_emit_set_call_param_type_ref(0);
      return 0;
    }

    // x86 register args: classify GP units, spill-then-load (SysV dual-GP safety).
    if (ta == 0) {
      let gp_start: i32[96] = [];
      let gp_units: i32[96] = [];
      let spill_off: i32[96] = [];
      let is_sse: i32[96] = [];
      let gp_cur: i32 = sret_sh;
      let xmm_cur: i32 = 0;
      let i: i32 = 0;
      while (i < nargs) {
        let ar_i: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        let pty_i: i32 = glue_call_param_type_ref_at(arena, expr_ref, i);
        is_sse[i] = glue_call_param_is_f32_c(arena, pty_i);
        spill_off[i] = 0 - 1;
        if (is_sse[i] != 0) {
          if (xmm_cur < 8) {
            gp_start[i] = xmm_cur;
            gp_units[i] = 1;
            xmm_cur = xmm_cur + 1;
          } else {
            gp_start[i] = 0 - 1;
            gp_units[i] = 0;
          }
        } else {
          let sz_i: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_i, ar_i);
          if (glue_sysv_arg_is_memory_by_value_c(sz_i) != 0) {
            gp_start[i] = 0 - 1;
            gp_units[i] = 0;
          } else {
            let u: i32 = glue_sysv_arg_gp_units_from_size_c(sz_i);
            gp_start[i] = gp_cur;
            gp_units[i] = u;
            if (u > 0) {
              if (gp_cur + u <= reg_max) {
                gp_cur = gp_cur + u;
              } else {
                gp_start[i] = 0 - 1;
              }
            } else {
              gp_start[i] = 0 - 1;
            }
          }
        }
        i = i + 1;
      }
      // Emit + spill every register-class arg (order free: values go to frame).
      i = 0;
      while (i < nargs) {
        if (gp_start[i] >= 0) {
          let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
          if (arg_ref != 0) {
            if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref, i, ctx, ta) != 0) {
              return 0 - 1;
            }
            let so: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units[i]);
            if (so < 0) { return 0 - 1; }
            spill_off[i] = so;
          }
        }
        i = i + 1;
      }
      // Load spills into final arg regs (low→high by arg index; dual-GP atomic relative to later).
      i = 0;
      while (i < nargs) {
        if (spill_off[i] >= 0) {
          if (is_sse[i] != 0) {
            if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off[i], ta) != 0) { return 0 - 1; }
            if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, gp_start[i], ta) != 0) {
              return 0 - 1;
            }
          } else {
            if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off[i], gp_start[i], gp_units[i]) != 0) {
              return 0 - 1;
            }
          }
        }
        i = i + 1;
      }
      pipeline_asm_emit_set_call_param_type_ref(0);
      return 0;
    }

    pipeline_asm_emit_set_call_param_type_ref(0);
    return 0;
  }
  return 0 - 1;
}

// glue_asm_emit_string_lit_ptr_rax_elf_c: see function docblock below.
/**
 * Emit STRING_LIT as *u8 pointer in result reg (x86 rax / aarch64 x0).
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — codegen ctx bytes
 * @param str_expr_ref i32 — EXPR_STRING_LIT
 * @param ta i32 — 0=x86_64, 1=aarch64
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED — delegates to glue_asm_emit_jmp_skip_string_then_lea (wave108).
 */
#[no_mangle]
export function glue_asm_emit_string_lit_ptr_rax_elf_c(arena: *u8, elf_ctx: *u8, str_expr_ref: i32, ta: i32): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  if (str_expr_ref <= 0) { return 0 - 1; }
  if (ta != 0) {
    if (ta != 1) { return 0 - 1; }
  }
  unsafe {
    if (pipeline_expr_kind_ord_at(arena, str_expr_ref) != 59) { return 0 - 1; }
    let slen: i32 = glue_asm_string_lit_len(arena, str_expr_ref);
    // Stage 12.2.5: empty "" OK; long diag strings up to 126.
    if (slen < 0) { return 0 - 1; }
    if (slen > 126) { return 0 - 1; }
    let sbuf: u8[128] = [];
    glue_asm_string_lit_into(arena, str_expr_ref, &sbuf[0]);
    return glue_asm_emit_jmp_skip_string_then_lea(elf_ctx, ta, 1, &sbuf[0], slen);
  }
  return 0 - 1;
}

/**
 * After CALL, canonicalize the return value into GPR x0/rax for pure-asm consumers.
 * Type-driven only (G.7; mirrors seed glue_asm_harvest_sse_call_ret_to_gpr_c):
 *   · kind 14=f32 / 15=f64 → xmm0 harvest (x86_64 only; ta==0)
 *   · kind 0=I32 → sxtw/cdqe (AAPCS64 `mov w0,imm` zero-extends; pure-asm
 *     full-x0 cmp vs sign-ext -2 fails without this — hybrid ONLY=rt_run_compiler_parsed
 *     try_c returned shell rc=254)
 *   · kind 3=U32 → zxt; kind 1=BOOL / 2=U8 → zxt8
 * Unknown kind / null → no-op success (0).
 * @param arena *u8 — AST arena for call_expr_ref type resolution
 * @param elf_ctx *u8 — ElfCodegenCtx* receiving encode bytes
 * @param call_expr_ref i32 — EXPR_CALL node (not ASSIGN wrapper)
 * @param ta i32 — target arch (0=x86_64, 1=arm64)
 * @return i32 — 0 ok; non-zero encode failure
 * PLATFORM: SHARED (GP sxt/zxt) / LINUX+MACOS x86_64 (SSE harvest).
 */
#[no_mangle]
export function glue_asm_harvest_call_ret_to_gpr_c(
  arena: *u8, elf_ctx: *u8, call_expr_ref: i32, ta: i32
): i32 {
  let kind: i32 = 0;
  if (arena == 0 as *u8) {
    return 0;
  }
  if (elf_ctx == 0 as *u8) {
    return 0;
  }
  if (call_expr_ref <= 0) {
    return 0;
  }
  unsafe {
    kind = pipeline_asm_call_return_type_kind_ord_c(arena, call_expr_ref);
  }
  // SSE harvest remains x86-only (xmm).
  if (ta == 0) {
    if (kind == 14) {
      unsafe {
        return backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta);
      }
    }
    if (kind == 15) {
      unsafe {
        return backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta);
      }
    }
  }
  // Integer GP ret: both x86_64 and arm64 (sxtw / cdqe / uxt).
  if (kind == 0) {
    unsafe {
      return glue_enc_sxt_i32_result_to_rax_elf_c(elf_ctx, ta);
    }
  }
  if (kind == 3) {
    unsafe {
      return glue_enc_zxt_u32_result_to_rax_elf_c(elf_ctx, ta);
    }
  }
  if (kind == 1) {
    unsafe {
      return glue_enc_zxt_u8_result_to_rax_elf_c(elf_ctx, ta);
    }
  }
  if (kind == 2) {
    unsafe {
      return glue_enc_zxt_u8_result_to_rax_elf_c(elf_ctx, ta);
    }
  }
  return 0;
}

// G-02f-141: emit args + call + stack cleanup + call-ret harvest (G.7 complete)
/**
 * Emit CALL arguments, the call site, outgoing-stack cleanup, then harvest
 * the return value into GPR (i32 sxtw / u32 zxt / f32 xmm).
 * Completes pure .x authority to match seed glue_asm_emit_call_with_cleanup_impl
 * harvest (was missing → pure-asm try_c `rc == -2` false → hello -o rc=254).
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — ElfCodegenCtx*
 * @param expr_ref i32 — EXPR_CALL node
 * @param ctx *u8 — AsmFuncCtx*
 * @param ta i32 — target arch
 * @param nargs i32 — argument count
 * @param cname *u8 — callee symbol bytes
 * @param clen i32 — symbol length
 * @return i32 — 0 ok; -1 emit failure
 * PLATFORM: SHARED — pure-asm product path for freestanding .x→.o.
 */
#[no_mangle]
export function glue_asm_emit_call_with_cleanup(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32, nargs: i32, cname: *u8, clen: i32
): i32 {
  let cleanup: i32 = 0;
  let hr: i32 = 0;
  unsafe {
    if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, nargs) != 0) {
      return 0 - 1;
    }
    if (glue_asm_enc_call_redirected(elf_ctx, cname, clen, ta) != 0) {
      return 0 - 1;
    }
    cleanup = glue_asm_call_stack_cleanup_bytes(ta, nargs);
    if (cleanup < 0) {
      return 0 - 1;
    }
    if (backend_enc_call_stack_cleanup_arch(elf_ctx, cleanup, ta) != 0) {
      return 0 - 1;
    }
    // G.7 complete: seed impl always harvests after cleanup; pure .x must too.
    hr = glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta);
    if (hr != 0) {
      return 0 - 1;
    }
    return 0;
  }
  return 0 - 1;
}

/** Exported function `glue_asm_call_stack_cleanup_bytes`.
 * Implements `glue_asm_call_stack_cleanup_bytes`.
 * @param ta i32
 * @param nargs i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_call_stack_cleanup_bytes(ta: i32, nargs: i32): i32 {
  if (nargs <= 0) {
    return 0;
  }
  let reg_max: i32 = glue_asm_call_reg_max(ta);
  let n_stack: i32 = nargs - reg_max;
  if (n_stack <= 0) {
    return 0;
  }
  if (ta == 0) {
    let bytes: i32 = n_stack * 8;
    if ((n_stack & 1) != 0) {
      bytes = bytes + 8;
    }
    return bytes;
  }
  if (ta == 2) {
    return -1;
  }
  return (n_stack * 8 + 15) & -16;
}

// See implementation.

// See implementation.
/** Function `pipeline_asm_resolve_whole_import_qualified_symbol_c`.
 * Purpose: implements `pipeline_asm_resolve_whole_import_qualified_symbol_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function pipeline_asm_resolve_whole_import_qualified_symbol_c(
  arena: *u8, cur_mod: *u8, callee_expr_ref: i32, sym_flat: *u8, out_match_imp_j: *i32
): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (cur_mod == 0) { return 0 - 1; }
  if (sym_flat == 0) { return 0 - 1; }
  if (callee_expr_ref <= 0) { return 0 - 1; }
  unsafe {
    if (pipeline_expr_kind_ord_at(arena, callee_expr_ref) != 44) { return 0 - 1; }
    asm_qual_sym_layer_reset();
    let cur_ref: i32 = callee_expr_ref;
    while (1 == 1) {
      if (cur_ref <= 0) { return 0 - 1; }
      let falen: i32 = pipeline_expr_field_access_name_len(arena, cur_ref);
      if (pipeline_expr_kind_ord_at(arena, cur_ref) != 44) { break; }
      if (falen <= 0) { break; }
      if (falen > 127) { break; }
      let layer_buf: u8[128] = [];
      pipeline_expr_field_access_name_into(arena, cur_ref, &layer_buf[0]);
      if (asm_qual_sym_layer_push(&layer_buf[0], falen) < 0) { return 0 - 1; }
      cur_ref = pipeline_expr_field_access_base_ref(arena, cur_ref);
    }
    let nstack: i32 = asm_qual_sym_layer_count();
    if (cur_ref <= 0) { return 0 - 1; }
    let vnlen: i32 = pipeline_expr_var_name_len(arena, cur_ref);
    if (pipeline_expr_kind_ord_at(arena, cur_ref) != 3) { return 0 - 1; }
    if (vnlen <= 0) { return 0 - 1; }
    if (vnlen > 127) { return 0 - 1; }
    let vname_buf: u8[128] = [];
    pipeline_expr_var_name_into(arena, cur_ref, &vname_buf[0]);
    let dep_j: i32 = 0;
    let nimp: i32 = parser_get_module_num_imports(cur_mod);
    while (dep_j < nimp) {
      let plen: i32 = pipeline_module_import_path_len(cur_mod, dep_j);
      if (plen <= 0) {
        dep_j = dep_j + 1;
        continue;
      }
      if (plen > 127) {
        dep_j = dep_j + 1;
        continue;
      }
      let path_cnt_buf: u8[128] = [];
      let pci: i32 = 0;
      while (pci < plen) {
        if (pci >= 64) { break; }
        path_cnt_buf[pci] = pipeline_module_import_path_byte_at(cur_mod, dep_j, pci);
        pci = pci + 1;
      }
      let pseg: i32 = glue_asm_import_path_segment_count(&path_cnt_buf[0], plen);
      if (pseg <= 0) {
        dep_j = dep_j + 1;
        continue;
      }
      if (nstack != pseg) {
        dep_j = dep_j + 1;
        continue;
      }
      let s0_rel: i32 = 0;
      let s0_ln: i32 = 0;
      if (glue_asm_import_segment_at(cur_mod, dep_j, 0, &s0_rel, &s0_ln) == 0) {
        dep_j = dep_j + 1;
        continue;
      }
      if (glue_asm_import_path_slice_equal(cur_mod, dep_j, s0_rel, s0_ln, &vname_buf[0], vnlen) == 0) {
        dep_j = dep_j + 1;
        continue;
      }
      let bad_mid: i32 = 0;
      let sm: i32 = 1;
      while (sm <= pseg - 1) {
        let srv: i32 = 0;
        let slv: i32 = 0;
        if (glue_asm_import_segment_at(cur_mod, dep_j, sm, &srv, &slv) == 0) {
          bad_mid = 1;
          break;
        }
        let lay_ix: i32 = pseg - sm;
        let layer_mid: u8[128] = [];
        asm_qual_sym_layer_copy(lay_ix, &layer_mid[0], 64);
        if (glue_asm_import_path_slice_equal(cur_mod, dep_j, srv, slv, &layer_mid[0], asm_qual_sym_layer_len(lay_ix)) == 0) {
          bad_mid = 1;
          break;
        }
        sm = sm + 1;
      }
      if (bad_mid != 0) {
        dep_j = dep_j + 1;
        continue;
      }
      let pre_buf: u8[128] = [];
      let pre_len: i32 = glue_asm_fill_c_prefix_from_module_import(cur_mod, dep_j, &pre_buf[0]);
      if (pre_len <= 0) {
        dep_j = dep_j + 1;
        continue;
      }
      let layer0: u8[128] = [];
      asm_qual_sym_layer_copy(0, &layer0[0], 64);
      let blt: i32 = glue_asm_build_import_binding_call_sym(&pre_buf[0], pre_len, &layer0[0], asm_qual_sym_layer_len(0), sym_flat);
      if (out_match_imp_j != 0) {
        out_match_imp_j[0] = dep_j;
      }
      return blt;
    }
  }
  return 0 - 1;
}

// See implementation.
/** Function `pipeline_asm_emit_call_args_text_c`.
 * Purpose: implements `pipeline_asm_emit_call_args_text_c`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
#[no_mangle]
export function pipeline_asm_emit_call_args_text_c(
  arena: *u8, out: *u8, expr_ref: i32, ctx: *u8, target_arch: i32, nargs: i32
): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (out == 0 as *u8) { return 0 - 1; }
  if (ctx == 0 as *u8) { return 0 - 1; }
  if (expr_ref <= 0) { return 0 - 1; }
  if (nargs < 0) { return 0 - 1; }
  if (nargs > 6) { return 0 - 1; }
  if (nargs <= 0) { return 0; }
  unsafe {
    let i: i32 = 0;
    while (i < nargs) {
      let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      if (arg_ref != 0) {
        if (pipeline_asm_emit_expr_c(arena, out, arg_ref, ctx, target_arch) != 0) { return 0 - 1; }
        if (target_arch == 0) {
          if (backend_arch_emit_mov_rax_to_arg_reg(out, i, target_arch) != 0) { return 0 - 1; }
        } else {
          if (target_arch == 2) {
            if (backend_arch_emit_mov_rax_to_arg_reg(out, i, target_arch) != 0) { return 0 - 1; }
          } else {
            if (backend_arch_emit_push_rax(out, target_arch) != 0) { return 0 - 1; }
          }
        }
      }
      i = i + 1;
    }
    if (target_arch == 1) {
      i = 0;
      while (i < nargs) {
        if (backend_arch_emit_ldr_sp_offset_to_wi(out, i, target_arch) != 0) { return 0 - 1; }
        i = i + 1;
      }
      if (backend_arch_emit_add_sp_imm(out, nargs * 16, target_arch) != 0) { return 0 - 1; }
    }
    return 0;
  }
  return 0 - 1;
}

// G-02f-147: EXPR_METHOD_CALL ELF; module_ref@16 LE; IMPORT_BINDING=1 VAR=3
/**
 * Freestanding METHOD_CALL ELF emit (import.method + UFCS free + bootstrap i32.double).
 * wave359: when typeck did not resolve a same-module free fn, `x.double()` with 0 args
 * expands to `2*x` (mov rax→rbx; add rax,rbx) — mirrors host `(x * 2)` so Ubuntu no longer
 * UNDEF `double`. UFCS free methods named `double` keep call_resolved_func_index >= 0 and
 * fall through to the normal call path.
 * wave360: UFCS auto-ref — free fn `method(self: *T, ...)` with value receiver emits lea
 * of receiver as arg0 (not by-value load).
 * UFCS leave (after import-binding + folds): places are [receiver, extra0..] with
 * formal types 0..n_place-1. Receiver goes through glue_emit_one_call_arg (pty=self)
 * so ARRAY_LIT `[7,8,9,10].take0()` packs i32x4 as 16B INTEGER dual-GP — the old
 * 1-GP `for_call_args` + `mov rax→rdi` dropped rdx. Same classify/spill/load as
 * import METHOD (wave214) and seed wave602. Export-sym mangle ≡ seed wave683.
 * f32/f64 extras: x86 SysV xmm0–7 (seed _impl already; .x was GP-only).
 * F7 dyn (dep_idx==-2): extras after data in GP0.
 * Integer extras → GP 1..(reg_max-1). Overflow → stack (SysV push /
 * AAPCS64 [sp+slot]). x86 SysV f32/f64 extras → xmm0–7 then stack.
 * ARM64 local callee stays GP-in (do not copy import METHOD s0).
 * Wrapper rdi/x0=data is unchanged (trampoline only touches self;
 * stack extras are copied in pipeline_asm_emit_vtable_wrapper_def).
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — ELF codegen context
 * @param expr_ref i32 — METHOD_CALL expr ref
 * @param ctx *u8 — AsmFuncCtx (module_ref at +16)
 * @param ta i32 — target arch (0=x86_64, 1=arm64, …)
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED — mac + Ubuntu freestanding · LINUX gold dual-GP
 */
#[no_mangle]
export function pipeline_asm_emit_method_call_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  if (ctx == 0 as *u8) { return 0 - 1; }
  unsafe {
    let mod_ref: *u8 = call_dispatch_load_ptr_le(ctx, 16);
    let nargs: i32 = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    /** Product parses core.xlang_io_submit_*_batch as METHOD_CALL with >5 args; seed _impl is authority. */
    if (nargs < 0) { return 0 - 1; }
    if (nargs > 96) { return 0 - 1; }
    let base_ref: i32 = pipeline_expr_method_call_base_ref_at(arena, expr_ref);
    let name_len: i32 = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (name_len <= 0) { return 0 - 1; }
    if (name_len > 127) { return 0 - 1; }
    let name: u8[128] = [];
    pipeline_expr_method_call_name_into(arena, expr_ref, &name[0]);
    /* stage10 S3.1 slice2 (10.1.1): dot-call raw_syscall0..6 shape
     * (linux.raw_syscall3(...) parses here; before dyn/UFCS/try_inline). */
    {
      let rs_mc: i32 = try_emit_raw_syscall_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (rs_mc < 0) { return 0 - 1; }
      if (rs_mc > 0) { return 0; }
    }
    /* Cap 10.7.1 slice12: va_* Cap METHOD_CALL (x86_64). */
    {
      let va_mc: i32 = try_emit_va_cap_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (va_mc < 0) { return 0 - 1; }
      if (va_mc > 0) { return 0; }
    }
    /* 10.4.1 slice1: atomic_load/store/cas_i32 METHOD_CALL (x86_64 only). */
    {
      let at_mc: i32 = try_emit_atomic_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (at_mc < 0) { return 0 - 1; }
      if (at_mc > 0) { return 0; }
    }
    /* 10.5.1 slice0: add_f32x4 / mul_f32x4 language SIMD builtins (x86 SSE). */
    {
      let sd_mc: i32 = try_emit_simd_lang_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (sd_mc < 0) { return 0 - 1; }
      if (sd_mc > 0) { return 0; }
    }
    /*
     * 10.3.3 slice3: METHOD_CALL `h.f(args)` when `f` is Cap/TYPE_FN field.
     * typeck stamps ret; emit loads field into rax/x0 then Cap blr (no self arg).
     * G.7: reuse spill / emit_expr_for_call_args / mov_rax_to_arg_reg / blr.
     * PLATFORM: SHARED · LINUX x86_64 call *r · MACOS|ARM64 blr.
     */
    {
      let ff_base_ty: i32 = 0;
      let ff_ty: i32 = 0;
      let ff_ko: i32 = 0;
      let ff_er: i32 = 0;
      let ff_eko: i32 = 0;
      let ff_ok: i32 = 0;
      let ff_nlen: i32 = 0;
      let ff_li: i32 = 0;
      let ff_nf: i32 = 0;
      let ff_j: i32 = 0;
      let ff_fnl: i32 = 0;
      let ff_foff: i32 = 0;
      let ff_hit: i32 = 0;
      let ff_eq: i32 = 0;
      let ff_k: i32 = 0;
      let ff_nlays: i32 = 0;
      let ff_fi: i32 = 0;
      let ff_spill: i32 = 0;
      let ff_reg_max: i32 = 0;
      let ff_nm: u8[128] = [];
      let ff_fnm: u8[128] = [];
      let ff_lnm: u8[128] = [];
      ff_base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
      if (ff_base_ty > 0) {
        ff_ty = ff_base_ty;
        ff_ko = pipeline_type_kind_ord_at(arena, ff_ty);
        if (ff_ko == 9) {
          ff_er = pipeline_type_elem_ref_at(arena, ff_ty);
          if (ff_er > 0) {
            ff_ty = ff_er;
            ff_ko = pipeline_type_kind_ord_at(arena, ff_ty);
          }
        }
        if (ff_ko == 8 && mod_ref != 0 as *u8) {
          ff_nlen = pipeline_type_named_name_into(arena, ff_ty, &ff_nm[0]);
          if (ff_nlen > 0 && ff_nlen <= 127) {
            ff_nlays = pipeline_module_num_struct_layouts_at(mod_ref);
            ff_li = 0;
            while (ff_li < ff_nlays && ff_hit == 0) {
              let ln: i32 = pipeline_module_struct_layout_name_len(mod_ref, ff_li);
              ff_eq = 1;
              if (ln != ff_nlen) {
                ff_eq = 0;
              } else {
                pipeline_module_struct_layout_name_into(mod_ref, ff_li, &ff_lnm[0]);
                ff_k = 0;
                while (ff_k < ff_nlen) {
                  if (ff_lnm[ff_k] != ff_nm[ff_k]) {
                    ff_eq = 0;
                  }
                  ff_k = ff_k + 1;
                }
              }
              if (ff_eq != 0) {
                ff_nf = pipeline_module_struct_layout_num_fields(mod_ref, ff_li);
                ff_j = 0;
                while (ff_j < ff_nf && ff_hit == 0) {
                  ff_fnl = pipeline_module_struct_layout_field_name_len(mod_ref, ff_li, ff_j);
                  if (ff_fnl == name_len && ff_fnl > 0 && ff_fnl <= 127) {
                    pipeline_module_struct_layout_field_name_into(mod_ref, ff_li, ff_j, &ff_fnm[0]);
                    ff_eq = 1;
                    ff_k = 0;
                    while (ff_k < ff_fnl) {
                      if (ff_fnm[ff_k] != name[ff_k]) {
                        ff_eq = 0;
                      }
                      ff_k = ff_k + 1;
                    }
                    if (ff_eq != 0) {
                      ff_er = pipeline_module_struct_layout_field_type_ref(mod_ref, ff_li, ff_j);
                      ff_foff = pipeline_module_struct_layout_field_offset_at(mod_ref, ff_li, ff_j);
                      ff_hit = 1;
                    }
                  }
                  ff_j = ff_j + 1;
                }
              }
              ff_li = ff_li + 1;
            }
          }
        }
        if (ff_hit != 0 && ff_er > 0) {
          ff_ko = pipeline_type_kind_ord_at(arena, ff_er);
          if (ff_ko == 18) {
            ff_ok = 1;
          } else if (ff_ko == 9) {
            let ff_pointee: i32 = pipeline_type_elem_ref_at(arena, ff_er);
            if (ff_pointee > 0) {
              ff_eko = pipeline_type_kind_ord_at(arena, ff_pointee);
              if (ff_eko == 2) {
                ff_ok = 1;
              }
            }
          }
        }
        if (ff_ok != 0) {
          /* rax = &receiver; load field qword at offset. */
          if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, ff_foff, ta) != 0) {
            return 0 - 1;
          }
          if (nargs == 0) {
            if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
            return 0;
          }
          ff_reg_max = glue_asm_call_reg_max(ta);
          if (ff_reg_max < 1) { ff_reg_max = 6; }
          if (nargs > ff_reg_max) {
            /* Stack-arg Cap via METHOD_CALL residual — keep UFCS fallthrough. */
            ff_ok = 0;
          }
        }
        if (ff_ok != 0 && nargs > 0) {
          ff_spill = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
          if (ff_spill < 0) { return 0 - 1; }
          ff_fi = 0;
          while (ff_fi < nargs) {
            let ff_ar: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, ff_fi);
            if (ff_ar <= 0) { return 0 - 1; }
            if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, ff_ar, ctx, ta) != 0) {
              return 0 - 1;
            }
            if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, ff_fi, ta) != 0) {
              return 0 - 1;
            }
            ff_fi = ff_fi + 1;
          }
          if (backend_enc_load_rbp_to_rax_arch(elf_ctx, ff_spill, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
          return 0;
        }
      }
    }
    // wave359: bootstrap i32.double → 2*x when not UFCS-resolved free fn.
    let r_fn: i32 = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    /*
     * F7: dyn Trait dispatch via vtable indirect call.
     * typeck sets call_resolved_dep_index = DYN_DISPATCH_DEP_SENTINEL (-2) when
     * the receiver is TYPE_DYN (kind=17), and stores the trait method slot
     * index in call_resolved_func_index (r_fn here). The dyn_obj layout is
     * { void* data; void* vtable; } (16 bytes), so:
     *   1. receiver addr in x0 (base_ref expression emit)
     *   2. ldr x1, [x0, #8]      — x1 = dyn_obj.vtable
     *   3. ldr x2, [x1, #slot*8] — x2 = vtable[slot] (wrapper fn ptr)
     *   4. ldr x0, [x0, #0]      — x0 = dyn_obj.data (self arg to wrapper)
     *   5. extras: GP 1..(reg_max-1) and/or xmm0–7 (x86 SysV); overflow
     *      extras go on the stack (UFCS/CALL same SysV/AAPCS words)
     *   6. blr x2 (or scratch)   — indirect call through wrapper fn ptr
     * Extra args must be packed after data: `x.add(3)` is wrapper(data, 3);
     * `x.add(3.0)` f64 is wrapper(data) + xmm0 (SysV). Do NOT use
     * glue_emit_one_call_arg here — resolved_func_index is the vtable slot,
     * not an impl func, so formal lookup would alias func[slot].
     * G.7: emit_expr_elf_for_call_args + glue_arg_ref_is_sse_float_c
     * (same classifier as UFCS leave; xmm only when ta==0 — local callee)
     * + glue_asm_call_reg_max for the GP file (not a hardcoded 5).
     * Without this branch, dyn calls fall into try_inline_param0_single_field_call_elf
     * which reads dyn_obj.data low 4 bytes as a value → SIGBUS on later blr.
     */
    let dep_idx: i32 = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
    if (dep_idx == -2) {
      let slot: i32 = r_fn;
      if (slot < 0) { return 0 - 1; }
      /*
       * Emit extras first (x0 not live yet), spill each to the frame.
       * Classify SSE from the extra expr (FLOAT_LIT / resolved f32/f64).
       * Cannot look up impl formals: r_fn is the vtable slot.
       * GP file after self: 1..reg_max-1 (x86=5, ARM64=7). Overflow → stack.
       * PLATFORM: LINUX x86_64 SysV xmm · MACOS ARM64 extras stay GP.
       */
      let extra_off: i32[96] = [];
      let is_sse_e: i32[96] = [];
      let is_f64_e: i32[96] = [];
      let place_e: i32[96] = [];
      let on_stk_e: i32[96] = [];
      let xmm_cur: i32 = 0;
      let gp_cur: i32 = 1;
      let n_stk: i32 = 0;
      let reg_max_e: i32 = glue_asm_call_reg_max(ta);
      if (reg_max_e < 2) { reg_max_e = 6; }
      let ei: i32 = 0;
      while (ei < nargs) {
        extra_off[ei] = 0 - 1;
        is_sse_e[ei] = 0;
        is_f64_e[ei] = 0;
        place_e[ei] = 0;
        on_stk_e[ei] = 0;
        let arg_ex: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, ei);
        if (arg_ex == 0) { return 0 - 1; }
        /* PLATFORM: LINUX|x86_64 SysV — f32/f64 extras go xmm0–7 then stack.
         * PLATFORM: MACOS|ARM64 — local impl homes GP (do not copy import METHOD). */
        if (ta == 0) {
          is_sse_e[ei] = glue_arg_ref_is_sse_float_c(arena, arg_ex, 0);
          is_f64_e[ei] = glue_arg_ref_is_f64_width_c(arena, arg_ex, 0);
        }
        if (is_sse_e[ei] != 0) {
          if (xmm_cur < 8) {
            place_e[ei] = xmm_cur;
            xmm_cur = xmm_cur + 1;
          } else {
            on_stk_e[ei] = 1;
            place_e[ei] = n_stk;
            n_stk = n_stk + 1;
          }
        } else {
          if (gp_cur < reg_max_e) {
            place_e[ei] = gp_cur;
            gp_cur = gp_cur + 1;
          } else {
            on_stk_e[ei] = 1;
            place_e[ei] = n_stk;
            n_stk = n_stk + 1;
          }
        }
        if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ex, ctx, ta) != 0) {
          return 0 - 1;
        }
        let so_ex: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
        if (so_ex < 0) { return 0 - 1; }
        extra_off[ei] = so_ex;
        ei = ei + 1;
      }
      /* F7: x0 must be &dyn_obj, not the loaded .data word. VAR/lvalue
       * receivers use the existing lvalue-LEA authority (G.7). emit_expr
       * would load the first 8 bytes (data ptr) and [x0,#8] would then
       * read past the concrete payload — SIGSEGV / exit=112 false-green. */
      if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      /* x0 = &dyn_obj; load vtable ptr from dyn_obj+8 into x1. */
      if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 1, 0, 8, ta) != 0) { return 0 - 1; }
      /* x1 = vtable; load method slot fn ptr from vtable+slot*8 into x2. */
      if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 2, 1, slot * 8, ta) != 0) { return 0 - 1; }
      /* x2 = wrapper fn ptr; load data ptr from dyn_obj+0 into x0 (self arg). */
      if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, 0, ta) != 0) { return 0 - 1; }
      /* SysV first arg is rdi, not rax. ARM64 x0 is already arg0. Do not change. */
      if (ta == 0) {
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
      }
      if (nargs <= 0) {
        if (backend_enc_blr_arch(elf_ctx, 2, ta) != 0) { return 0 - 1; }
        return 0;
      }
      /* Spill data (rax/x0 still holds the pointer). Extra loads go through rax. */
      let data_off: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
      if (data_off < 0) { return 0 - 1; }
      /* nargs>=2 extras occupy rdx/x2; park the fn ptr first. */
      let fn_off: i32 = 0 - 1;
      if (nargs >= 2) {
        let cur_fn: i32 = call_dispatch_load_i32_le(ctx, 4);
        fn_off = cur_fn + 16;
        if (fn_off < 16) { fn_off = 16; }
        if (backend_enc_store_x_reg_to_rbp_arch(elf_ctx, 2, fn_off, ta) != 0) {
          return 0 - 1;
        }
        call_dispatch_store_i32_le(ctx, 4, fn_off + 16);
      }
      /*
       * Stack extras from spills. x86: pad then push right-to-left (UFCS).
       * ARM64: reserve + store [sp+slot] before GP reload.
       * PLATFORM: LINUX x86_64 SysV push · MACOS|ARM64 AAPCS64 [sp].
       */
      let stk_bytes: i32 = 0;
      if (n_stk > 0) {
        if (ta == 0) {
          if ((n_stk & 1) != 0) {
            if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
            if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
            stk_bytes = stk_bytes + 8;
          }
          ei = nargs - 1;
          while (ei >= 0) {
            if (on_stk_e[ei] != 0) {
              if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0) {
                return 0 - 1;
              }
              if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
              stk_bytes = stk_bytes + 8;
            }
            ei = ei - 1;
          }
        } else {
          stk_bytes = n_stk * 8;
          stk_bytes = (stk_bytes + 15) & (0 - 16);
          if (backend_enc_call_stack_reserve_arch(elf_ctx, stk_bytes, ta) != 0) {
            return 0 - 1;
          }
          let stk_slot: i32 = 0;
          ei = 0;
          while (ei < nargs) {
            if (on_stk_e[ei] != 0) {
              if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0) {
                return 0 - 1;
              }
              if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot * 8, ta) != 0) {
                return 0 - 1;
              }
              stk_slot = stk_slot + 1;
            }
            ei = ei + 1;
          }
        }
      }
      ei = 0;
      while (ei < nargs) {
        if (on_stk_e[ei] == 0) {
          if (is_sse_e[ei] != 0) {
            /* Reload bits then movd/movq into xmm[k] (≡ UFCS leave / seed _impl). */
            if (backend_enc_load_rbp_to_rax_arch(elf_ctx, extra_off[ei], ta) != 0) {
              return 0 - 1;
            }
            if (is_f64_e[ei] != 0) {
              if (backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, place_e[ei], ta) != 0) {
                return 0 - 1;
              }
            } else if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, place_e[ei], ta) != 0) {
              return 0 - 1;
            }
          } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, extra_off[ei], place_e[ei], 1) != 0) {
            return 0 - 1;
          }
        }
        ei = ei + 1;
      }
      if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, data_off, 0, 1) != 0) {
        return 0 - 1;
      }
      if (nargs >= 2) {
        /* Non-arg scratch: x86 r11 (hw 11) / ARM64 x9. PLATFORM: LINUX x86 · MACOS ARM64. */
        if (ta == 0) {
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 11, 5, 0 - fn_off, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_blr_arch(elf_ctx, 11, ta) != 0) { return 0 - 1; }
        } else {
          if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 9, 29, fn_off, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_blr_arch(elf_ctx, 9, ta) != 0) { return 0 - 1; }
        }
      } else {
        /* nargs==1: extra in rsi/x1; fn still in rdx/x2. */
        if (backend_enc_blr_arch(elf_ctx, 2, ta) != 0) { return 0 - 1; }
      }
      if (stk_bytes > 0) {
        if (backend_enc_call_stack_cleanup_arch(elf_ctx, stk_bytes, ta) != 0) {
          return 0 - 1;
        }
      }
      return 0;
    }
    if (r_fn < 0) {
      if (nargs == 0) {
        if (name_len == 6) {
          if (base_ref != 0) {
            if (name[0] == 100) {
              if (name[1] == 111) {
                if (name[2] == 117) {
                  if (name[3] == 98) {
                    if (name[4] == 108) {
                      if (name[5] == 101) {
                        if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, base_ref, ctx, ta) != 0) {
                          return 0 - 1;
                        }
                        if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
                        if (backend_enc_add_rax_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
                        return 0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (mod_ref != 0) {
      if (base_ref > 0) {
        if (pipeline_expr_kind_ord_at(arena, base_ref) == 3) {
          let base_len: i32 = pipeline_expr_var_name_len(arena, base_ref);
          if (base_len > 0) {
            // wave580 Cap: import binding name content cap 127.
            if (base_len <= 127) {
              let base_name: u8[128] = [];
              pipeline_expr_var_name_into(arena, base_ref, &base_name[0]);
              let j: i32 = 0;
              let nimp: i32 = parser_get_module_num_imports(mod_ref);
              while (j < nimp) {
                if (pipeline_module_import_kind_at(mod_ref, j) == 1) {
                  if (glue_asm_import_binding_name_equal(mod_ref, j, &base_name[0], base_len) != 0) {
                    let pre_buf: u8[128] = [];
                    let pre_len: i32 = glue_asm_fill_c_prefix_from_module_import(mod_ref, j, &pre_buf[0]);
                    if (pre_len <= 0) { return 0 - 1; }
                    // PLATFORM: SHARED — fmt.println string lit (METHOD_CALL). G.7 seed _impl same leaf.
                    let fmt_lit: i32 = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
                      arena, elf_ctx, expr_ref, ctx, ta, &pre_buf[0], pre_len, &name[0], name_len);
                    if (fmt_lit < 0) { return 0 - 1; }
                    if (fmt_lit > 0) { return 0; }
                    /* PLATFORM: SHARED — fmt.println(composite) JSON any (print_any). */
                    let fmt_any: i32 = glue_asm_try_emit_fmt_any_import_call_elf_c(
                      arena, elf_ctx, expr_ref, ctx, ta, &pre_buf[0], pre_len, &name[0], name_len);
                    if (fmt_any < 0) { return 0 - 1; }
                    if (fmt_any > 0) { return 0; }
                    let sym_flat: u8[128] = [];
                    /*
                     * PLATFORM: SHARED — import METHOD mangle (G.7 ≡ seed).
                     * Bare pre+name → U std_string_length / std_string_is_empty while
                     * string.o exports length_String / is_empty_String. Seed
                     * glue_asm_mangle_import_binding_call_sym_c is authority; pure PREFER
                     * must call the same surface (not bare build).
                     */
                    let sym_len: i32 = glue_asm_mangle_import_binding_call_sym_c(
                      arena, ctx, expr_ref, mod_ref, j, &pre_buf[0], pre_len, &name[0], name_len, 1, &sym_flat[0]
                    );
                    if (sym_len <= 0) { return 0 - 1; }
                    let n_ov: i32 = pipeline_codegen_call_num_args_override(&pre_buf[0], pre_len, &name[0], name_len, nargs);
                    /*
                     * PLATFORM: SHARED freestanding multi-arg · MACOS|ARM64 AAPCS64 + LINUX x86 SysV.
                     * Root (mac option residual): import-binding METHOD_CALL must spill-then-load
                     * (same as pipeline_asm_emit_call_args_elf_c / seed wave602). Direct place via
                     * x0 temp after nested CALL clobbers Option in x0 (unwrap_or(some(42),0)→0).
                     * Root (run-result 173 residual): pure import METHOD path hard-coded gp_units=1
                     * and used arg index as GP index → Result_i32 (16B INTEGER dual-GP) only packed
                     * lows into x0/x1; host core_result_or_i32 expects x0:x1 + x2:x3 → return -3.
                     * Free CALL already uses size→units + gp_start; import METHOD must match.
                     * Root (run-slice subslice_split_chunks SEGV): pure import METHOD started
                     * gp_cur at 0 while let-init sret had already placed hidden dest in rdi and
                     * set call_sret_reg_shift=1. Args overwrote rdi with arg0 → callee
                     * core_slice_split_at_i32 (sret, slice*, at) read at-as-pointer → SEGV.
                     * Seed twin already starts gp_cur at sret_sh; pure .x must match.
                     * G.7: one discipline for free CALL and import METHOD_CALL (dual-GP + sret).
                     */
                    {
                      let spill_off_m: i32[96] = [];
                      let gp_start_m: i32[96] = [];
                      let gp_units_m: i32[96] = [];
                      // is_mem_m: 0=reg/int, 1=x86 SysV MEMORY stack, 2=arm64 host-indirect lea.
                      let is_mem_m: i32[96] = [];
                      let is_sse_m: i32[96] = [];
                      let is_f64_m: i32[96] = [];
                      let arg_sz_m: i32[96] = [];
                      let i_m: i32 = 0;
                      let mem_stack_m: i32 = 0;
                      let xmm_cur_m: i32 = 0;
                      // PLATFORM: SHARED — SysV 6 (rdi..r9) / AAPCS64 8 (x0–x7).
                      // Seed twin pipeline_asm_emit_method_call_elf_c_impl must call this
                      // (not hardcode 6): Darwin product L2 is the seed; csv.parse_row's
                      // 7th GP is x6. Free CALL / UFCS already use glue_asm_call_reg_max.
                      let reg_max_m: i32 = glue_asm_call_reg_max(ta);
                      // SysV hidden sret consumes rdi (GP0); shift formals by sret_sh.
                      // PLATFORM: SHARED — LINUX+MACOS x86_64 SysV; AAPCS64 uses x8 (sret_sh=0).
                      let sret_sh_m: i32 = 0;
                      if (ta == 0) {
                        sret_sh_m = pipeline_asm_emit_call_sret_reg_shift_c();
                      }
                      let gp_cur_m: i32 = sret_sh_m;
                      if (reg_max_m < 1) { reg_max_m = 6; }
                      /*
                       * Classify large POD for import METHOD → host-C std .o (string.o):
                       * - PLATFORM: LINUX|x86_64 SysV — MEMORY by-value on stack (gcc formals
                       *   at [rbp+0x10..]; run-string length(String) residual when lea→rdi).
                       * - PLATFORM: MACOS|ARM64 AAPCS64 — large composite as pointer in GP
                       *   (lea; host-C std_string_length_String takes x0=&String).
                       * Pure→pure UFCS still uses MEMORY stack on its own path (wave602).
                       * G.7: one authority with seed is_mem=1 (x86) / is_mem=2 (arm64).
                       */
                      while (i_m < nargs) {
                        let ar_m: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_m);
                        let pty_m: i32 = glue_call_param_type_ref_at(arena, expr_ref, i_m);
                        let sz_m: i32 = glue_sysv_arg_byte_size_c(arena, ctx, pty_m, ar_m);
                        let u_m: i32 = glue_sysv_arg_gp_units_from_size_c(sz_m);
                        spill_off_m[i_m] = 0 - 1;
                        is_mem_m[i_m] = 0;
                        is_sse_m[i_m] = 0;
                        is_f64_m[i_m] = 0;
                        arg_sz_m[i_m] = sz_m;
                        gp_start_m[i_m] = 0 - 1;
                        gp_units_m[i_m] = 0;
                        // PLATFORM: LINUX+MACOS x86_64 SysV — f32/f64 extras go xmm0–7.
                        // PLATFORM: MACOS|ARM64 AAPCS64 — same extras go s0–s7 / d0–d7
                        // (host-C gcc reads FP regs). Encoder now has fmov sK,w0.
                        // Do NOT open UFCS leave / CALL packer / param home (those
                        // stay GP on arm64 — local xlang callee homes x0).
                        if (ta == 0 || ta == 1) {
                          is_sse_m[i_m] = glue_arg_ref_is_sse_float_c(arena, ar_m, pty_m);
                          is_f64_m[i_m] = glue_arg_ref_is_f64_width_c(arena, ar_m, pty_m);
                        }
                        if (is_sse_m[i_m] != 0) {
                          if (xmm_cur_m >= 8) { return 0 - 1; }
                          gp_start_m[i_m] = xmm_cur_m;
                          gp_units_m[i_m] = 1;
                          xmm_cur_m = xmm_cur_m + 1;
                        } else {
                          if (u_m < 1) { u_m = 1; }
                          if (u_m > 2) { u_m = 2; }
                          if (glue_sysv_arg_is_memory_by_value_c(sz_m) != 0) {
                            if (ta == 0) {
                              // x86 SysV MEMORY: stack only (not lea into GP).
                              is_mem_m[i_m] = 1;
                              gp_start_m[i_m] = 0 - 1;
                              gp_units_m[i_m] = 0;
                            } else {
                              // arm64 large composite: 1 GP + lea at emit.
                              is_mem_m[i_m] = 2;
                              if (gp_cur_m + 1 <= reg_max_m) {
                                gp_start_m[i_m] = gp_cur_m;
                                gp_units_m[i_m] = 1;
                                gp_cur_m = gp_cur_m + 1;
                              } else {
                                gp_start_m[i_m] = 0 - 1;
                                gp_units_m[i_m] = 1;
                              }
                            }
                          } else if (gp_cur_m + u_m <= reg_max_m) {
                            gp_start_m[i_m] = gp_cur_m;
                            gp_units_m[i_m] = u_m;
                            gp_cur_m = gp_cur_m + u_m;
                          } else {
                            gp_start_m[i_m] = 0 - 1;
                            gp_units_m[i_m] = u_m;
                          }
                        }
                        i_m = i_m + 1;
                      }
                      // x86: MEMORY multi-word + excess integer stack (high→low) before reg load.
                      // PLATFORM: LINUX+MACOS x86_64 SysV — pad first for 16-align (seed twin).
                      if (ta == 0) {
                        let raw_mem: i32 = 0;
                        let pushed_total: i32 = 0;
                        i_m = 0;
                        while (i_m < nargs) {
                          if (is_mem_m[i_m] == 1) {
                            raw_mem = raw_mem + ((arg_sz_m[i_m] + 7) & (0 - 8));
                          } else if (gp_start_m[i_m] < 0) {
                            raw_mem = raw_mem + 8;
                          }
                          i_m = i_m + 1;
                        }
                        while (((raw_mem + pushed_total) & 15) != 0) {
                          if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
                          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
                          pushed_total = pushed_total + 8;
                        }
                        i_m = nargs - 1;
                        while (i_m >= 0) {
                          if (is_mem_m[i_m] == 1) {
                            let arg_mem: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_m);
                            let pushed: i32 = 0;
                            if (arg_mem == 0) { return 0 - 1; }
                            pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(
                              arena, elf_ctx, ctx, arg_mem, arg_sz_m[i_m], ta);
                            if (pushed < 0) { return 0 - 1; }
                            pushed_total = pushed_total + pushed;
                          } else if (gp_start_m[i_m] < 0) {
                            let arg_stk: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_m);
                            if (arg_stk != 0) {
                              if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_stk, i_m, ctx, ta) != 0) {
                                return 0 - 1;
                              }
                              if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
                              pushed_total = pushed_total + 8;
                            }
                          }
                          i_m = i_m - 1;
                        }
                        mem_stack_m = pushed_total;
                      }
                      // Emit + spill register-class args (dual-GP; arm64 >16B → lea).
                      i_m = 0;
                      while (i_m < nargs) {
                        if (gp_start_m[i_m] >= 0) {
                          let arg_ref_m: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_m);
                          if (arg_ref_m != 0) {
                            if (is_mem_m[i_m] == 2) {
                              // PLATFORM: MACOS|ARM64 — host-C large POD addr into GP
                              // (VAR lea / nested CALL sret→temp+lea; save outer x8).
                              if (glue_emit_arm64_host_mem_arg_addr_to_rax_c(
                                    arena, elf_ctx, ctx, arg_ref_m, arg_sz_m[i_m], ta) != 0) {
                                return 0 - 1;
                              }
                            } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_ref_m, i_m, ctx, ta) != 0) {
                              return 0 - 1;
                            }
                            let so_m: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units_m[i_m]);
                            if (so_m < 0) { return 0 - 1; }
                            spill_off_m[i_m] = so_m;
                          }
                        }
                        i_m = i_m + 1;
                      }
                      // arm64 excess: place on [sp] via x0 *before* final GP load (do not clobber GPs).
                      // Skip is_mem==2 (already in GP); only true excess integer stack.
                      if (ta == 1) {
                        let stk_slot_m: i32 = 0;
                        i_m = 0;
                        while (i_m < nargs) {
                          if (gp_start_m[i_m] < 0) {
                            if (is_mem_m[i_m] != 2) {
                              let arg_stk_a: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_m);
                              if (arg_stk_a != 0) {
                                if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_stk_a, i_m, ctx, ta) != 0) {
                                  return 0 - 1;
                                }
                                if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot_m * 8, ta) != 0) {
                                  return 0 - 1;
                                }
                                stk_slot_m = stk_slot_m + 1;
                              }
                            }
                          }
                          i_m = i_m + 1;
                        }
                      }
                      // Load high→low so x0/rax temp does not wipe lower final GPs.
                      // Dual-GP: load into gp_start_m and gp_start_m+1 (not bare arg index).
                      // SSE: reload bits then movd/movq into xmm[k] (≡ seed _impl).
                      i_m = nargs - 1;
                      while (i_m >= 0) {
                        if (spill_off_m[i_m] >= 0) {
                          if (is_sse_m[i_m] != 0) {
                            if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off_m[i_m], ta) != 0) {
                              return 0 - 1;
                            }
                            if (is_f64_m[i_m] != 0) {
                              if (backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, gp_start_m[i_m], ta) != 0) {
                                return 0 - 1;
                              }
                            } else if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, gp_start_m[i_m], ta) != 0) {
                              return 0 - 1;
                            }
                          } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off_m[i_m], gp_start_m[i_m], gp_units_m[i_m]) != 0) {
                            return 0 - 1;
                          }
                        }
                        i_m = i_m - 1;
                      }
                      if (glue_asm_enc_call_redirected(elf_ctx, &sym_flat[0], sym_len, ta) != 0) { return 0 - 1; }
                      // Cleanup: MEMORY multi-word bytes when tracked; else nargs-based.
                      {
                        let cln_m: i32 = mem_stack_m;
                        if (cln_m <= 0) {
                          cln_m = glue_asm_call_stack_cleanup_bytes(ta, n_ov);
                        }
                        if (cln_m < 0) { return 0 - 1; }
                        if (cln_m > 0) {
                          if (backend_enc_call_stack_cleanup_arch(elf_ctx, cln_m, ta) != 0) { return 0 - 1; }
                        }
                      }
                    }
                    /*
                     * PLATFORM: SHARED freestanding — after import METHOD_CALL, harvest
                     * ret into full GPR (i32 sxtw / u32 zxt / f32 xmm). G.7 complete:
                     * seed _impl always harvests here; pure .x previously returned after
                     * cleanup only → AAPCS64 `ldr w0` zero-extends -1 to 0xFFFFFFFF,
                     * then full-x0 signed cmp (`call() >= 0`) is true (run-mem exit 8).
                     * Free CALL already harvests via glue_asm_emit_call_with_cleanup;
                     * import METHOD must match (same authority glue_asm_harvest_call_ret_to_gpr_c).
                     */
                    if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0) {
                      return 0 - 1;
                    }
                    // PLATFORM: MACOS|ARM64 AAPCS64 — host-C returns f32/f64 in s0/d0.
                    // Shared harvest is x86-only so local xlang f32 CALL stays GP-in/GP-out.
                    // Import METHOD callee is gcc: move s0/d0 → w0/x0 after the no-op harvest.
                    if (ta == 1) {
                      let rk_m: i32 = pipeline_asm_call_return_type_kind_ord_c(arena, expr_ref);
                      if (rk_m == 14) {
                        if (backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta) != 0) {
                          return 0 - 1;
                        }
                      } else if (rk_m == 15) {
                        if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, 0, ta) != 0) {
                          return 0 - 1;
                        }
                      }
                    }
                    return 0;
                  }
                }
                j = j + 1;
              }
            }
          }
        }
      }
    }
    // G.7: same param0.field / field-sum / x+K / wpo_mono-symbol / wpo_mono-vector_lane
    // / wpo_const-scalar / vector_lane folds as CALL emit
    // (recv.first() ≡ take_a(recv); recv.pair_sum() ≡ field_sum(recv);
    //  recv.plus_one() ≡ add_one(recv); recv.fold_add(K) ≡ fold_add_call(recv, K);
    //  XLANG_WPO_MONO: recv.fold_add(K) ≡ fold_add_call(recv, K) via zero-arg thunk;
    //  XLANG_WPO_MONO: recv.lane0() ≡ lane0_call(recv) via zero-arg thunk
    //  when recv is const vec_binop;
    //  recv.lane0() ≡ lane0_call(recv) when recv is const vec_binop).
    // After import-binding: import methods must not enter lookup/fold (option/si SEGV).
    // extra mismatch / fold miss / PTR → 0, fall through to UFCS CALL.
    {
      let inline_sf: i32 = try_inline_param0_single_field_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
      if (inline_sf != 0) {
        if (inline_sf < 0) { return 0 - 1; }
        return 0;
      }
    }
    {
      let inline_fs: i32 = try_inline_param0_field_sum_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
      if (inline_fs != 0) {
        if (inline_fs < 0) { return 0 - 1; }
        return 0;
      }
    }
    {
      let inline_xk: i32 = try_inline_x_plus_k_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
      if (inline_xk != 0) {
        if (inline_xk < 0) { return 0 - 1; }
        return 0;
      }
    }
    // Same order as CALL emit: mono symbol then vector_lane mono
    // (both self-gate on XLANG_WPO_MONO) then const fold only when
    // neither mono nor no-fold env is set.
    {
      let inline_ms: i32 = try_call_wpo_mono_symbol_elf(arena, elf_ctx, expr_ref, ctx, ta);
      if (inline_ms != 0) {
        if (inline_ms < 0) { return 0 - 1; }
        return 0;
      }
    }
    {
      let inline_mv: i32 = try_call_wpo_mono_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
      if (inline_mv != 0) {
        if (inline_mv < 0) { return 0 - 1; }
        return 0;
      }
    }
    // Same env gate as CALL emit: XLANG_WPO_MONO / XLANG_WPO_NO_FOLD skip const fold.
    // Order matches CALL emit: vector_lane then scalar.
    if (link_abi_getenv("XLANG_WPO_MONO") == 0) {
      if (link_abi_getenv("XLANG_WPO_NO_FOLD") == 0) {
        let inline_vl: i32 = try_inline_wpo_const_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
        if (inline_vl != 0) {
          if (inline_vl < 0) { return 0 - 1; }
          return 0;
        }
        let inline_wc: i32 = try_inline_wpo_const_scalar_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
        if (inline_wc != 0) {
          if (inline_wc < 0) { return 0 - 1; }
          return 0;
        }
      }
    }
    // wave360 + ARRAY_LIT SIMD self: UFCS places [receiver, extra0..] (seed wave602).
    // PLATFORM: SHARED — LINUX+MACOS x86_64 SysV dual-GP; MACOS|ARM64 AAPCS64 spill.
    {
      let has_recv: i32 = 0;
      let n_place: i32 = 0;
      let need_aref: i32 = 0;
      let spill_off_u: i32[96] = [];
      let gp_start_u: i32[96] = [];
      let gp_units_u: i32[96] = [];
      let is_mem_u: i32[96] = [];
      let is_sse_u: i32[96] = [];
      let is_f64_u: i32[96] = [];
      let arg_sz_u: i32[96] = [];
      let i_u: i32 = 0;
      let mem_stack_u: i32 = 0;
      let xmm_cur_u: i32 = 0;
      let reg_max_u: i32 = glue_asm_call_reg_max(ta);
      let sret_sh_u: i32 = 0;
      let gp_cur_u: i32 = 0;
      if (base_ref != 0) { has_recv = 1; }
      /*
       * Associated Type.method(): resolved callee nparams == nargs (no implicit
       * self). `P.mk()` / `P.id(7)` / `P.get(p)` — type-name receiver is not
       * an argument. Instance `p.get()` keeps nparams == nargs+1 so has_recv
       * stays 1. PLATFORM: SHARED — G.7 complete UFCS leave; seed twin
       * seeds/backend_call_dispatch.from_x.c.
       */
      if (has_recv != 0) {
        let assoc_fn: i32 = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
        let assoc_dep: i32 = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
        if (assoc_fn >= 0) {
          if (assoc_dep < 0) {
            if (mod_ref != 0 as *u8) {
              let assoc_np: i32 = pipeline_module_func_num_params_at(mod_ref, assoc_fn);
              if (assoc_np == nargs) {
                has_recv = 0;
              }
            }
          }
        }
      }
      n_place = has_recv + nargs;
      if (n_place < 0) { return 0 - 1; }
      if (n_place > 96) { return 0 - 1; }
      if (has_recv != 0) {
        let r_fn2: i32 = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
        let r_dep2: i32 = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
        if (r_fn2 >= 0) {
          if (r_dep2 < 0) {
            if (mod_ref != 0) {
              let p0: i32 = pipeline_module_func_param_type_ref_at(mod_ref, r_fn2, 0);
              let bty: i32 = pipeline_expr_resolved_type_ref(arena, base_ref);
              if (p0 > 0) {
                if (bty > 0) {
                  // TYPE_PTR kind ord = 9
                  if (pipeline_type_kind_ord_at(arena, p0) == 9) {
                    if (pipeline_typeck_type_refs_equal_c(arena, bty, p0) == 0) {
                      let pe: i32 = pipeline_type_elem_ref_at(arena, p0);
                      if (pe > 0) {
                        if (pipeline_typeck_type_refs_equal_c(arena, bty, pe) != 0) {
                          need_aref = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (ta == 0) {
        sret_sh_u = pipeline_asm_emit_call_sret_reg_shift_c();
      }
      gp_cur_u = sret_sh_u;
      if (reg_max_u < 1) { reg_max_u = 6; }
      while (i_u < n_place) {
        let ar_u: i32 = 0;
        let pty_u: i32 = glue_call_param_type_ref_at(arena, expr_ref, i_u);
        let sz_u: i32 = 0;
        let u_u: i32 = 0;
        if (has_recv != 0) {
          if (i_u == 0) {
            ar_u = base_ref;
          } else {
            ar_u = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u - has_recv);
          }
        } else {
          ar_u = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u);
        }
        if (has_recv != 0) {
          if (i_u == 0) {
            if (need_aref != 0) {
              sz_u = 8;
            } else {
              sz_u = glue_sysv_arg_byte_size_c(arena, ctx, pty_u, ar_u);
            }
          } else {
            sz_u = glue_sysv_arg_byte_size_c(arena, ctx, pty_u, ar_u);
          }
        } else {
          sz_u = glue_sysv_arg_byte_size_c(arena, ctx, pty_u, ar_u);
        }
        u_u = glue_sysv_arg_gp_units_from_size_c(sz_u);
        spill_off_u[i_u] = 0 - 1;
        is_mem_u[i_u] = 0;
        is_sse_u[i_u] = 0;
        is_f64_u[i_u] = 0;
        arg_sz_u[i_u] = sz_u;
        gp_start_u[i_u] = 0 - 1;
        gp_units_u[i_u] = 0;
        // Same-layer twin of import METHOD SSE classify (G.7 有则补全).
        if (ta == 0) {
          is_sse_u[i_u] = glue_arg_ref_is_sse_float_c(arena, ar_u, pty_u);
          is_f64_u[i_u] = glue_arg_ref_is_f64_width_c(arena, ar_u, pty_u);
        }
        if (is_sse_u[i_u] != 0) {
          if (xmm_cur_u >= 8) { return 0 - 1; }
          gp_start_u[i_u] = xmm_cur_u;
          gp_units_u[i_u] = 1;
          xmm_cur_u = xmm_cur_u + 1;
        } else {
          if (u_u < 1) { u_u = 1; }
          if (u_u > 2) { u_u = 2; }
          if (glue_sysv_arg_is_memory_by_value_c(sz_u) != 0) {
            /* wave606: X-to-X MEMORY is stack-only on SysV and AAPCS64.
             * Do not lea into GP (callee param_home reads stack words).
             * Import METHOD keeps is_mem=2 (host-C AAPCS64 pointer).
             * PLATFORM: LINUX+MACOS x86_64 SysV · MACOS|ARM64 AAPCS64. */
            is_mem_u[i_u] = 1;
            gp_start_u[i_u] = 0 - 1;
            gp_units_u[i_u] = 0;
          } else if (gp_cur_u + u_u <= reg_max_u) {
            gp_start_u[i_u] = gp_cur_u;
            gp_units_u[i_u] = u_u;
            gp_cur_u = gp_cur_u + u_u;
          } else {
            gp_start_u[i_u] = 0 - 1;
            gp_units_u[i_u] = u_u;
          }
        }
        i_u = i_u + 1;
      }
      // x86: MEMORY multi-word + excess integer stack (high→low) before reg load.
      if (ta == 0) {
        let raw_mem: i32 = 0;
        let pushed_total: i32 = 0;
        i_u = 0;
        while (i_u < n_place) {
          if (is_mem_u[i_u] == 1) {
            raw_mem = raw_mem + ((arg_sz_u[i_u] + 7) & (0 - 8));
          } else if (gp_start_u[i_u] < 0) {
            raw_mem = raw_mem + 8;
          }
          i_u = i_u + 1;
        }
        while (((raw_mem + pushed_total) & 15) != 0) {
          if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
          pushed_total = pushed_total + 8;
        }
        i_u = n_place - 1;
        while (i_u >= 0) {
          let arg_pl: i32 = 0;
          if (has_recv != 0) {
            if (i_u == 0) {
              arg_pl = base_ref;
            } else {
              arg_pl = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u - has_recv);
            }
          } else {
            arg_pl = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u);
          }
          if (is_mem_u[i_u] == 1) {
            let pushed: i32 = 0;
            if (arg_pl == 0) { return 0 - 1; }
            pushed = pipeline_asm_push_sysv_memory_by_value_elf_c(
              arena, elf_ctx, ctx, arg_pl, arg_sz_u[i_u], ta);
            if (pushed < 0) { return 0 - 1; }
            pushed_total = pushed_total + pushed;
          } else if (gp_start_u[i_u] < 0) {
            if (arg_pl != 0) {
              if (has_recv != 0) {
                if (i_u == 0) {
                  if (need_aref != 0) {
                    if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
                      return 0 - 1;
                    }
                  } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
                    return 0 - 1;
                  }
                } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_pl, i_u, ctx, ta) != 0) {
                  return 0 - 1;
                }
              } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_pl, i_u, ctx, ta) != 0) {
                return 0 - 1;
              }
              if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
              pushed_total = pushed_total + 8;
            }
          }
          i_u = i_u - 1;
        }
        mem_stack_u = pushed_total;
      }
      if (ta == 1) {
        let nw_u: i32 = 0;
        let stack_reserve_u: i32 = 0;
        i_u = 0;
        while (i_u < n_place) {
          if (is_mem_u[i_u] == 1) {
            nw_u = nw_u + glue_sysv_arg_stack_words_c(arg_sz_u[i_u], 0);
          } else if (gp_start_u[i_u] < 0) {
            if (is_mem_u[i_u] != 2) {
              nw_u = nw_u + 1;
            }
          }
          i_u = i_u + 1;
        }
        stack_reserve_u = nw_u * 8;
        if (stack_reserve_u > 0) {
          stack_reserve_u = (stack_reserve_u + 15) & (0 - 16);
        }
        mem_stack_u = stack_reserve_u;
        if (backend_enc_call_stack_reserve_arch(elf_ctx, stack_reserve_u, ta) != 0) { return 0 - 1; }
      }
      // Emit + spill register-class places (receiver uses pty=formal0 via glue_emit_one_call_arg).
      i_u = 0;
      while (i_u < n_place) {
        if (gp_start_u[i_u] >= 0) {
          let arg_rg: i32 = 0;
          if (has_recv != 0) {
            if (i_u == 0) {
              arg_rg = base_ref;
            } else {
              arg_rg = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u - has_recv);
            }
          } else {
            arg_rg = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u);
          }
          if (arg_rg != 0) {
            if (is_mem_u[i_u] == 2) {
              // PLATFORM: MACOS|ARM64 — host-indirect (nested CALL safe).
              if (glue_emit_arm64_host_mem_arg_addr_to_rax_c(
                    arena, elf_ctx, ctx, arg_rg, arg_sz_u[i_u], ta) != 0) {
                return 0 - 1;
              }
            } else if (has_recv != 0) {
              if (i_u == 0) {
                if (need_aref != 0) {
                  if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
                    return 0 - 1;
                  }
                } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
                  return 0 - 1;
                }
              } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_rg, i_u, ctx, ta) != 0) {
                return 0 - 1;
              }
            } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_rg, i_u, ctx, ta) != 0) {
              return 0 - 1;
            }
            let so_u: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, gp_units_u[i_u]);
            if (so_u < 0) { return 0 - 1; }
            spill_off_u[i_u] = so_u;
          }
        }
        i_u = i_u + 1;
      }
      // arm64 MEMORY / excess integer stack *before* final GP load.
      // wave606: MEMORY multi-word via store_to_sp (≡ free CALL wave603).
      // PLATFORM: MACOS|ARM64 AAPCS64.
      if (ta == 1) {
        let stk_slot_u: i32 = 0;
        i_u = 0;
        while (i_u < n_place) {
          if (gp_start_u[i_u] < 0) {
            let arg_sk: i32 = 0;
            if (has_recv != 0) {
              if (i_u == 0) {
                arg_sk = base_ref;
              } else {
                arg_sk = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u - has_recv);
              }
            } else {
              arg_sk = pipeline_expr_method_call_arg_ref(arena, expr_ref, i_u);
            }
            if (is_mem_u[i_u] == 1) {
              if (arg_sk == 0) { return 0 - 1; }
              let stored_u: i32 = pipeline_asm_store_memory_by_value_to_sp_elf_c(
                arena, elf_ctx, ctx, arg_sk, arg_sz_u[i_u], ta, stk_slot_u * 8);
              if (stored_u < 0) { return 0 - 1; }
              let words_u: i32 = stored_u / 8;
              if (words_u < 1) { words_u = 1; }
              stk_slot_u = stk_slot_u + words_u;
            } else if (is_mem_u[i_u] != 2) {
              if (arg_sk != 0) {
                if (has_recv != 0) {
                  if (i_u == 0) {
                    if (need_aref != 0) {
                      if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, base_ref, ctx, ta) != 0) {
                        return 0 - 1;
                      }
                    } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, base_ref, 0, ctx, ta) != 0) {
                      return 0 - 1;
                    }
                  } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_sk, i_u, ctx, ta) != 0) {
                    return 0 - 1;
                  }
                } else if (glue_emit_one_call_arg_elf_c(arena, elf_ctx, expr_ref, arg_sk, i_u, ctx, ta) != 0) {
                  return 0 - 1;
                }
                if (backend_enc_store_x0_sp_offset_arch(elf_ctx, stk_slot_u * 8, ta) != 0) {
                  return 0 - 1;
                }
                stk_slot_u = stk_slot_u + 1;
              }
            }
          }
          i_u = i_u + 1;
        }
      }
      // Load high→low so rax/x0 temp does not wipe lower GPs. Dual-GP uses gp_start+units.
      // SSE: reload bits then movd/movq into xmm[k] (≡ import METHOD / seed _impl).
      i_u = n_place - 1;
      while (i_u >= 0) {
        if (spill_off_u[i_u] >= 0) {
          if (is_sse_u[i_u] != 0) {
            if (backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off_u[i_u], ta) != 0) {
              return 0 - 1;
            }
            if (is_f64_u[i_u] != 0) {
              if (backend_enc_mov_rax_to_xmm_arg_reg_arch(elf_ctx, gp_start_u[i_u], ta) != 0) {
                return 0 - 1;
              }
            } else if (backend_enc_mov_eax_to_xmm_arg_reg_arch(elf_ctx, gp_start_u[i_u], ta) != 0) {
              return 0 - 1;
            }
          } else if (glue_sysv_load_spill_to_arg_regs_elf_c(elf_ctx, ta, spill_off_u[i_u], gp_start_u[i_u], gp_units_u[i_u]) != 0) {
            return 0 - 1;
          }
        }
        i_u = i_u - 1;
      }
      // wave683: overload-safe export-sym (get_S / take0) — bare name UNDEF on Ubuntu.
      {
        let r_fn_call: i32 = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
        let r_dep_call: i32 = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
        let call_sym: u8[128] = [];
        let call_sym_len: i32 = 0 - 1;
        if (r_fn_call >= 0) {
          if (r_dep_call < 0) {
            if (mod_ref != 0) {
              call_sym_len = glue_asm_build_func_export_sym_c(mod_ref, arena, r_fn_call, &call_sym[0], 128);
            }
          } else {
            let dep_pipe_u: *u8 = pipeline_asm_emit_dep_pipe_c();
            if (dep_pipe_u != 0 as *u8) {
              let dm_u: *u8 = pipeline_dep_ctx_module_at(dep_pipe_u, r_dep_call);
              let da_u: *u8 = pipeline_dep_ctx_arena_at(dep_pipe_u, r_dep_call);
              if (dm_u != 0 as *u8) {
                if (da_u == 0 as *u8) { da_u = arena; }
                call_sym_len = glue_asm_build_func_export_sym_c(dm_u, da_u, r_fn_call, &call_sym[0], 128);
              }
            }
          }
        }
        if (call_sym_len > 0) {
          if (glue_asm_enc_call_redirected(elf_ctx, &call_sym[0], call_sym_len, ta) != 0) { return 0 - 1; }
        } else if (glue_asm_enc_call_redirected(elf_ctx, &name[0], name_len, ta) != 0) {
          return 0 - 1;
        }
      }
      if (mem_stack_u > 0) {
        if (backend_enc_call_stack_cleanup_arch(elf_ctx, mem_stack_u, ta) != 0) { return 0 - 1; }
      }
      if (glue_asm_harvest_call_ret_to_gpr_c(arena, elf_ctx, expr_ref, ta) != 0) { return 0 - 1; }
      return 0;
    }
  }
  return 0 - 1;
}

// pipeline_asm_emit_call_elf_c: see function docblock below.
/** Exported function `pipeline_asm_emit_call_elf_c`.
 * Implements `pipeline_asm_emit_call_elf_c`.
 * @param arena *u8
 * @param elf_ctx *u8
 * @param expr_ref i32
 * @param ctx *u8
 * @param ta i32
 * @return i32
 */
/**
 * CORE-001 asm twin of codegen_try_emit_size_align_of_call (host-C sizeof/_Alignof).
 * Fold `size_of<T>()` / `align_of<T>()` (free or import-qualified) to imm in w0/eax.
 * Without this, zero-arg generics skip mono → bare `core_types_size_of` → BLD001 UNDEF.
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — ELF/Mach-O codegen ctx
 * @param expr_ref i32 — EXPR_CALL site
 * @param mod_ref *u8 — caller module (named-struct layouts)
 * @param ta i32 — target arch
 * @return i32 — 1 folded, 0 not applicable, -1 emit error
 * PLATFORM: SHARED — layout via glue_type_size_simple / glue_type_align_simple
 */
function try_fold_size_align_of_call_elf(arena: *u8, elf_ctx: *u8, expr_ref: i32, mod_ref: *u8, ta: i32): i32 {
  unsafe {
    let callee_ref: i32 = 0;
    let callee_ko: i32 = 0;
    let n_ta: i32 = 0;
    let ty_ref: i32 = 0;
    let is_size: i32 = 0;
    let is_align: i32 = 0;
    let nlen: i32 = 0;
    let val: i32 = 0;
    let name: u8[128] = [];
    let i: i32 = 0;
    if (arena == 0 as *u8 || elf_ctx == 0 as *u8 || expr_ref <= 0) {
      return 0;
    }
    if (pipeline_expr_call_num_args_at(arena, expr_ref) != 0) {
      return 0;
    }
    n_ta = pipeline_expr_call_num_type_args_at(arena, expr_ref);
    if (n_ta < 1) {
      return 0;
    }
    callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    if (callee_ref <= 0) {
      return 0;
    }
    callee_ko = pipeline_expr_kind_ord_at(arena, callee_ref);
    i = 0;
    while (i < 128) {
      name[i] = 0;
      i = i + 1;
    }
    if (callee_ko == 44) {
      nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
      if (nlen <= 0) { return 0; }
      if (nlen > 127) { return 0; }
      pipeline_expr_field_access_name_into(arena, callee_ref, &name[0]);
    } else if (callee_ko == 3) {
      nlen = pipeline_expr_var_name_len(arena, callee_ref);
      if (nlen <= 0) { return 0; }
      if (nlen > 127) { return 0; }
      pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
    } else {
      return 0;
    }
    /* Exact bare name: size_of (7) / align_of (8). */
    if (nlen == 7 && name[0] == 115 && name[1] == 105 && name[2] == 122 && name[3] == 101
        && name[4] == 95 && name[5] == 111 && name[6] == 102) {
      is_size = 1;
    } else if (nlen == 8 && name[0] == 97 && name[1] == 108 && name[2] == 105 && name[3] == 103
        && name[4] == 110 && name[5] == 95 && name[6] == 111 && name[7] == 102) {
      is_align = 1;
    } else {
      return 0;
    }
    ty_ref = pipeline_expr_call_type_arg_ref_at(arena, expr_ref, 0);
    if (ty_ref <= 0) {
      return 0;
    }
    if (is_size != 0) {
      val = glue_type_size_simple(mod_ref, arena, ty_ref, 0);
    } else if (is_align != 0) {
      val = glue_type_align_simple(mod_ref, arena, ty_ref, 0);
    } else {
      return 0;
    }
    if (val < 0) {
      return 0 - 1;
    }
    if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, val, ta) != 0) {
      return 0 - 1;
    }
    return 1;
  }
}

/**
 * Stage 10 S3.1 slice 2 (10.1.1): raw_syscall0..6 — ELF direct-encode lowering.
 *
 * Matches the same builtin surface as the C-backend intercept
 * (codegen_try_emit_raw_syscall_call) on BOTH parse shapes: dot calls parse as
 * METHOD_CALL (49, fmt.println default), bare/alt calls as EXPR_CALL (48) with
 * FIELD_ACCESS/VAR callee. Arity digit is the callee-name suffix; arg count
 * must equal arity+1 (arg 0 is the syscall nr).
 *
 * Lowering:
 *   1. emit each arg expr (pipeline_asm_emit_expr_elf_for_call_args → rax) and
 *      spill rax to a frame slot, bumping the AsmFuncCtx.next_offset cursor
 *      exactly like glue_sysv_spill_rax_rdx_to_frame_c (G.7 same discipline;
 *      arg emissions may clobber rax so nothing lives in registers mid-loop)
 *   2a. Linux x86_64 (ta==0): reload a1→rdi(k0) a2→rsi(k1) a3→rdx(k2)
 *       a4→r10(raw; no C-ABI k slot) a5→r8(k4) a6→r9(k5); nr LAST → rax;
 *       enc syscall (0F 05). Return in rax; clobbers rcx/r11 (dead here).
 *   2b. Linux ELF aarch64 (ta==1 && !macho): a2..a6 → x1..x5; nr → x8;
 *       a1 LAST → x0 (so mov-to-x8 does not clobber a1); enc svc #0.
 *       Return in x0. Darwin Mach-O (ta==1 && macho) returns 0 — Darwin
 *       syscalls use x16 + svc #0x80, not the Linux ABI (honest panic body).
 *
 * @param arena *u8 — ASTArena*
 * @param elf_ctx *u8 — ElfCodegenCtx*
 * @param expr_ref i32 — CALL/METHOD_CALL expr ref
 * @param ctx *u8 — AsmFuncCtx* (frame cursor at byte 4)
 * @param ta i32 — target arch (0 x86_64, 1 aarch64)
 * @return i32 — 1 emitted; 0 not applicable (fall through to normal call);
 *               -1 emit error
 * PLATFORM: LINUX x86_64 or LINUX aarch64 ELF runtime; SHARED emit code.
 */
function try_emit_raw_syscall_call_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 || ctx == 0 as *u8 || expr_ref <= 0) {
    return 0;
  }
  unsafe {
    /* x86_64, or Linux ELF aarch64. Darwin Mach-O (x16 + svc #0x80) falls
     * through to the panic body — linux.raw_syscall is the Linux ABI. */
    if (ta != 0) {
      if (ta != 1) { return 0; }
      if (pipeline_elf_ctx_macho_leading_underscore(elf_ctx) != 0) { return 0; }
    }
    let ko: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let name: u8[128] = [];
    let nlen: i32 = 0;
    let n_args: i32 = 0;
    let is_method: i32 = 0;
    let arity: i32 = 0 - 1;
    let pfx: u8[11] = [114, 97, 119, 95, 115, 121, 115, 99, 97, 108, 108];
    let i: i32 = 0;
    let cur: i32 = 0;
    let off: i32[8] = [];
    let arg_ref: i32 = 0;
    let j: i32 = 0;
    let k: i32 = 0;
    /* Shape match: METHOD_CALL(49) reads method_call_name; CALL(48) reads the
     * callee FIELD_ACCESS(44)/VAR(3) name. Exact raw_syscall<digit>, len 12. */
    if (ko == 49) {
      nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
      if (nlen != 12) { return 0; }
      pipeline_expr_method_call_name_into(arena, expr_ref, &name[0]);
      n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
      is_method = 1;
    } else if (ko == 48) {
      let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      let cko: i32 = 0;
      if (callee_ref <= 0) { return 0; }
      cko = pipeline_expr_kind_ord_at(arena, callee_ref);
      if (cko == 44) {
        nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
        if (nlen != 12) { return 0; }
        pipeline_expr_field_access_name_into(arena, callee_ref, &name[0]);
      } else if (cko == 3) {
        nlen = pipeline_expr_var_name_len(arena, callee_ref);
        if (nlen != 12) { return 0; }
        pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
      } else {
        return 0;
      }
      n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    } else {
      return 0;
    }
    i = 0;
    while (i < 11) {
      if (name[i] != pfx[i]) { return 0; }
      i = i + 1;
    }
    arity = name[11] as i32 - 48;
    if (arity < 0 || arity > 6) { return 0; }
    if (n_args != arity + 1) { return 0; }
    /* Emit + spill each arg to its own frame slot (cursor discipline twin of
     * glue_sysv_spill_rax_rdx_to_frame_c: off = max(cur+16,16), 16 stride). */
    cur = call_dispatch_load_i32_le(ctx, 4);
    i = 0;
    while (i < n_args) {
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off[i] = cur + 16;
      if (off[i] < 16) { off[i] = 16; }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, off[i], ta) != 0) { return 0 - 1; }
      cur = off[i];
      i = i + 1;
    }
    call_dispatch_store_i32_le(ctx, 4, cur + 16);
    if (ta == 0) {
      /* Reload into syscall homes: a1..a6 first (rdi/rsi/rdx/r10/r8/r9), then
       * nr LAST so rax ends holding the syscall number. */
      j = 1;
      while (j < n_args) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[j], ta) != 0) { return 0 - 1; }
        if (j == 1) { k = 0; }
        else if (j == 2) { k = 1; }
        else if (j == 3) { k = 2; }
        else if (j == 4) { k = 0 - 1; }
        else if (j == 5) { k = 4; }
        else { k = 5; }
        if (k == 0 - 1) {
          /* a4 → r10 (49 89 C2); r10 has no C-ABI mov_rax_to_arg_reg slot. */
          if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0) { return 0 - 1; }
        } else {
          if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, k, ta) != 0) { return 0 - 1; }
        }
        j = j + 1;
      }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_syscall(elf_ctx) != 0) { return 0 - 1; }
    } else {
      /* LINUX ELF aarch64: a2..a6 → x1..x5 (C-ABI k=1..5), nr → x8,
       * then a1 LAST → x0 so the x8 move does not clobber a1. */
      j = 2;
      while (j < n_args) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[j], ta) != 0) { return 0 - 1; }
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, j - 1, ta) != 0) { return 0 - 1; }
        j = j + 1;
      }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0) { return 0 - 1; }
      if (n_args > 1) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      }
      if (arch_arm64_enc_enc_svc(elf_ctx) != 0) { return 0 - 1; }
    }
    return 1;
  }
}

/**
 * Cap 10.7.1 slice18: after class_cursor is in rax and class_cell in rcx/x3,
 * compare against class_end and — if past the register file — switch to the
 * shared overflow cursor (header[16]).
 *
 * Preconditions: header parked in r10 (x86) / x8 (aarch64); rax = class_cursor;
 * rcx/x3 = class_cell. Post: rax = slot pointer; rcx/x3 = writeback cell
 * (class_cell or ov_cell). Unique labels via pipeline_asm_emit_next_label_c.
 *
 * class_end = header_addr - (24 + gp_n*8 [+ fp_n*8 if FP]). rbp-negative
 * layout means a cursor address <= class_end is past the save (overflow).
 * Signed LE (cc=3) is valid: both pointers live in the same user stack.
 *
 * @param elf_ctx *u8 — ELF codegen ctx
 * @param ctx *u8 — AsmFuncCtx (label counter)
 * @param ta i32 — 0 = x86_64; 1 = aarch64
 * @param is_fp i32 — 0 GP class, 1 FP class
 * @param gp_n i32 — 6 SysV / 8 AAPCS
 * @return i32 — 0 ok; -1 emit error
 * PLATFORM: SHARED emit · LINUX|x86_64 · LINUX|aarch64 cross-emit.
 */
function try_emit_va_cap_ov_select_elf_c(
  elf_ctx: *u8, ctx: *u8, ta: i32, is_fp: i32, gp_n: i32
): i32 {
  unsafe {
    let end_delta: i32 = 0;
    let lbl_sv: u8[64] = [];
    let lbl_dn: u8[64] = [];
    let n_sv: i32 = 0;
    let n_dn: i32 = 0;
    if (elf_ctx == 0 as *u8 || ctx == 0 as *u8) { return 0 - 1; }
    if (gp_n < 6) { gp_n = 6; }
    /* header(24) + GP save; FP class_end is past FP save too. */
    end_delta = 24 + gp_n * 8;
    if (is_fp != 0) { end_delta = end_delta + 64; }
    n_sv = pipeline_asm_emit_next_label_c(ctx, &lbl_sv[0], 64);
    n_dn = pipeline_asm_emit_next_label_c(ctx, &lbl_dn[0], 64);
    if (n_sv <= 0 || n_dn <= 0) { return 0 - 1; }
    /* rbx = class_cursor (mov does not clobber flags we have not set yet). */
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    /* rax = header (parked r10 / x8). */
    if (ta == 1) {
      if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0) { return 0 - 1; }
    } else {
      if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) { return 0 - 1; }
    }
    if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - end_delta, ta) != 0) {
      return 0 - 1;
    }
    /* rax = class_end, rbx = class_cursor. cmp cursor, end. */
    if (backend_enc_cmp_rbx_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    /* cc=3 LE: overflow = (cursor <= class_end). */
    if (backend_enc_cmp_setcc_movzbl_arch(elf_ctx, 3, ta) != 0) { return 0 - 1; }
    if (backend_enc_test_eax_eax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    if (backend_enc_jz_arch(elf_ctx, &lbl_sv[0], n_sv, ta) != 0) { return 0 - 1; }
    /* overflow: ov_cell = header - 16; load *ov_cell as slot. */
    if (ta == 1) {
      if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0) { return 0 - 1; }
    } else {
      if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) { return 0 - 1; }
    }
    if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - 16, ta) != 0) { return 0 - 1; }
    if (ta == 1) {
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0) { return 0 - 1; }
    } else {
      if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0) { return 0 - 1; }
    }
    if (backend_enc_jmp_arch(elf_ctx, &lbl_dn[0], n_dn, ta) != 0) { return 0 - 1; }
    if (backend_enc_label_arch(elf_ctx, &lbl_sv[0], n_sv, 0, ta) != 0) { return 0 - 1; }
    /* in-save: slot = class_cursor (rbx); writeback stays class_cell. */
    if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    if (backend_enc_label_arch(elf_ctx, &lbl_dn[0], n_dn, 0, ta) != 0) { return 0 - 1; }
    return 0;
  }
}

/**
 * Cap 10.7.1 slice12–18: language va_start / va_end / va_arg_{i32,i64,ptr} /
 * typed va_arg<T>(ap) including f32/f64 + stack extras → asm Cap.
 *
 * Host-C uses xlang_va_* macros (SysV / AAPCS; C promotes unnamed f32→double).
 * Asm Cap is Cap-private: at va_start, spill GP + FP arg regs into call-spill
 * scratch (regs still hold entry values because this intercept runs before
 * call-arg packing). VaList local holds a pointer to a 24-byte header:
 *   header[0] = GP cursor, header[8] (pointer-8) = FP cursor,
 *   header[16] (pointer-16) = shared overflow cursor.
 * Layout: header (24) / GP[gp_n] / FP[fp_n] / OV[8].
 * gp_n = 6 SysV (rdi..r9) or 8 AAPCS (x0..x7). fp_n = 8 (xmm0..7 / v0..v7).
 * Named params consume GP or FP slots independently (glue_call_param_is_f32_c).
 * slice17–18: incoming stack extras are copied once into OV. va_arg walks the
 * class save with -8 until class_end, then both GP and FP consume the shared
 * OV cursor (SysV / AAPCS mixed overflow). x86 first extra at [rbp+16];
 * aarch64 at [x29,#frame+16] (prologue x19 pad; matches param_home). Named
 * stack formals skip that many words in the copy source. MSVC residual.
 * va_arg loads *slot as a full 8-byte slot (i32/f32 live in the low 32);
 * both streams bump -8 (rising rbp-offsets = falling addresses). va_end is a no-op.
 * slice14: va_arg<T>(ap) classifies T via type-arg sidecar.
 * slice16: TYPE_F32=14 / TYPE_F64=15 walk the FP cursor (G.7 complete).
 *
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — ELF codegen ctx
 * @param expr_ref i32 — CALL or METHOD_CALL expr
 * @param ctx *u8 — AsmFuncCtx (next_offset@4, module@16)
 * @param ta i32 — 0 = x86_64; 1 = aarch64; other → 0 fallthrough
 * @return i32 — 1 emitted; 0 not Cap va; -1 emit error
 * PLATFORM: SHARED emit · LINUX|x86_64 runtime · LINUX|aarch64 cross-emit.
 */
function try_emit_va_cap_builtin_call_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 || ctx == 0 as *u8 || expr_ref <= 0) {
    return 0;
  }
  if (ta != 0 && ta != 1) {
    return 0;
  }
  unsafe {
    let ko: i32 = 0;
    let name: u8[128] = [];
    let nlen: i32 = 0;
    let n_args: i32 = 0;
    let is_method: i32 = 0;
    let which: i32 = 0;
    let i: i32 = 0;
    let nm_start: u8[8] = [118, 97, 95, 115, 116, 97, 114, 116]; /* va_start */
    let nm_end: u8[6] = [118, 97, 95, 101, 110, 100]; /* va_end */
    let nm_argi32_full: u8[10] = [118, 97, 95, 97, 114, 103, 95, 105, 51, 50]; /* va_arg_i32 */
    let nm_argi64_full: u8[10] = [118, 97, 95, 97, 114, 103, 95, 105, 54, 52]; /* va_arg_i64 */
    let nm_argptr_full: u8[10] = [118, 97, 95, 97, 114, 103, 95, 112, 116, 114]; /* va_arg_ptr */
    let nm_arg_typed: u8[6] = [118, 97, 95, 97, 114, 103]; /* va_arg */
    let ty_ref: i32 = 0;
    let tk: i32 = 0;
    let tsz: i32 = 0;
    let ap_ref: i32 = 0;
    let ap_off: i32 = 0;
    let cur: i32 = 0;
    let save_off: i32 = 0;
    let mod: *u8 = 0 as *u8;
    let fi: i32 = 0;
    let np: i32 = 0;
    let k: i32 = 0;
    let gp_n: i32 = 6;
    let fp_n: i32 = 8;
    let np_gp: i32 = 0;
    let np_fp: i32 = 0;
    let gp_save: i32 = 0;
    let fp_save: i32 = 0;
    let ov: i32 = 0;
    let ov_n: i32 = 8;
    let named_stk: i32 = 0;
    let stk_pos: i32 = 0;
    let pty: i32 = 0;
    let is_fp: i32 = 0;

    ko = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (ko == 49) {
      nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
      if (nlen <= 0 || nlen > 127) { return 0; }
      pipeline_expr_method_call_name_into(arena, expr_ref, &name[0]);
      n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
      is_method = 1;
    } else if (ko == 48) {
      let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      let cko: i32 = 0;
      if (callee_ref <= 0) { return 0; }
      cko = pipeline_expr_kind_ord_at(arena, callee_ref);
      if (cko == 44) {
        nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
        if (nlen <= 0 || nlen > 127) { return 0; }
        pipeline_expr_field_access_name_into(arena, callee_ref, &name[0]);
      } else if (cko == 3) {
        nlen = pipeline_expr_var_name_len(arena, callee_ref);
        if (nlen <= 0 || nlen > 127) { return 0; }
        pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
      } else {
        return 0;
      }
      n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    } else {
      return 0;
    }

    which = 0;
    if (nlen == 8) {
      i = 0;
      while (i < 8) {
        if (name[i] != nm_start[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 8) { which = 1; }
    }
    if (which == 0 && nlen == 6) {
      i = 0;
      while (i < 6) {
        if (name[i] != nm_end[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 6) { which = 2; }
      if (which == 0) {
        i = 0;
        while (i < 6) {
          if (name[i] != nm_arg_typed[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 6) { which = 6; }
      }
    }
    if (which == 0 && nlen == 10) {
      i = 0;
      while (i < 10) {
        if (name[i] != nm_argi32_full[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 10) { which = 3; }
      if (which == 0) {
        i = 0;
        while (i < 10) {
          if (name[i] != nm_argi64_full[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 10) { which = 4; }
      }
      if (which == 0) {
        i = 0;
        while (i < 10) {
          if (name[i] != nm_argptr_full[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 10) { which = 5; }
      }
    }
    if (which == 0) { return 0; }

    /* va_end(ap): Cap no-op (do not emit call). */
    if (which == 2) {
      if (n_args != 1) { return 0; }
      return 1;
    }

    if (which == 1) {
      /* va_start(ap, last): need ap as local VAR. */
      if (n_args != 2) { return 0; }
      if (is_method != 0) {
        ap_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
      } else {
        ap_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
      }
      if (ap_ref <= 0) { return 0 - 1; }
      if (pipeline_expr_kind_ord_at(arena, ap_ref) != 3) { return 0; }
      ap_off = glue_asm_local_var_stack_off_scoped(arena, ctx, ap_ref);
      if (ap_off < 16) { return 0 - 1; }

      mod = call_dispatch_load_ptr_le(ctx, 16);
      fi = pipeline_asm_emit_func_index_c();
      np = 0;
      if (mod != 0 as *u8 && fi >= 0) {
        np = pipeline_module_func_num_params_at(mod, fi);
      }
      if (np < 0) { np = 0; }
      gp_n = 6;
      if (ta == 1) { gp_n = 8; }
      fp_n = 8;
      /* Named params consume GP or XMM/NEON independently (SysV / AAPCS). */
      np_gp = 0;
      np_fp = 0;
      k = 0;
      while (k < np) {
        pty = 0;
        if (mod != 0 as *u8 && fi >= 0) {
          pty = pipeline_module_func_param_type_ref_at(mod, fi, k);
        }
        if (glue_call_param_is_f32_c(arena, pty) != 0) {
          np_fp = np_fp + 1;
        } else {
          np_gp = np_gp + 1;
        }
        k = k + 1;
      }
      /* Named stack formals sit at the front of the incoming overflow area. */
      named_stk = 0;
      if (np_gp > gp_n) { named_stk = named_stk + (np_gp - gp_n); }
      if (np_fp > fp_n) { named_stk = named_stk + (np_fp - fp_n); }
      if (np_gp > gp_n) { np_gp = gp_n; }
      if (np_fp > fp_n) { np_fp = fp_n; }

      /* Reserve header(24) + GP save + FP save + shared OV in call-spill
       * scratch (frame already ≥512). ov_n=8 extra 8-byte slots, one copy.
       * PLATFORM: LINUX|x86_64 SysV · LINUX|aarch64 AAPCS (cross-emit). */
      cur = call_dispatch_load_i32_le(ctx, 4);
      save_off = cur + 16;
      if (save_off < 16) { save_off = 16; }
      gp_save = save_off + 24;
      ov_n = 8;
      fp_save = gp_save + gp_n * 8;
      ov = fp_save + fp_n * 8;
      call_dispatch_store_i32_le(ctx, 4, ov + ov_n * 8);

      /* Spill GP arg regs while entry values still live. */
      k = 0;
      while (k < gp_n) {
        if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, k, ta) != 0) { return 0 - 1; }
        if (backend_enc_store_rax_to_rbp_arch(elf_ctx, gp_save + k * 8, ta) != 0) {
          return 0 - 1;
        }
        k = k + 1;
      }
      /* Spill FP arg regs (xmmK / vK) as 8-byte slots. G.7 existing encoders. */
      k = 0;
      while (k < fp_n) {
        if (backend_enc_mov_xmm_arg_reg_to_rax_arch(elf_ctx, k, ta) != 0) { return 0 - 1; }
        if (backend_enc_store_rax_to_rbp_arch(elf_ctx, fp_save + k * 8, ta) != 0) {
          return 0 - 1;
        }
        k = k + 1;
      }

      /* Copy incoming stack extras once into shared OV. G.7 existing
       * load_rbp_pos / load_x29_pos (param_home twins). rax/x0 is free: GP
       * and FP files already spilled. */
      stk_pos = 16;
      if (ta == 1) {
        /* PLATFORM: LINUX|aarch64 — prologue grows frame by 16 (x19). */
        cur = call_dispatch_load_i32_le(ctx, 0);
        if (cur > 16) { stk_pos = cur; }
        stk_pos = stk_pos + 16;
      }
      stk_pos = stk_pos + named_stk * 8;
      k = 0;
      while (k < ov_n) {
        if (ta == 1) {
          if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, stk_pos + k * 8, ta) != 0) {
            return 0 - 1;
          }
        } else {
          if (backend_enc_load_rbp_pos_to_rax_arch(elf_ctx, stk_pos + k * 8, ta) != 0) {
            return 0 - 1;
          }
        }
        if (backend_enc_store_rax_to_rbp_arch(elf_ctx, ov + k * 8, ta) != 0) {
          return 0 - 1;
        }
        k = k + 1;
      }

      /* header[0] = &GP[np_gp] (first trailing GP). */
      if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, gp_save + np_gp * 8, ta) != 0) {
        return 0 - 1;
      }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off, ta) != 0) { return 0 - 1; }
      /* header[8] = &FP[np_fp] (first trailing FP). */
      if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, fp_save + np_fp * 8, ta) != 0) {
        return 0 - 1;
      }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off + 8, ta) != 0) { return 0 - 1; }
      /* header[16] = &OV[0] (shared overflow; named_stk already skipped in copy). */
      if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ov, ta) != 0) {
        return 0 - 1;
      }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, save_off + 16, ta) != 0) { return 0 - 1; }
      /* *ap = &header. */
      if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, save_off, ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ap_off, ta) != 0) { return 0 - 1; }
      if (ta == 1) {
        /* x3 = &ap; x0 = header; str x0, [x3]. G.7 existing encoders. */
        if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }

    /* which == 6: typed va_arg<T>(ap) → classify T into 3/4/5/7/8. */
    if (which == 6) {
      if (n_args != 1) { return 0; }
      if (pipeline_expr_call_num_type_args_at(arena, expr_ref) < 1) { return 0; }
      ty_ref = pipeline_expr_call_type_arg_ref_at(arena, expr_ref, 0);
      if (ty_ref <= 0) { return 0; }
      tk = pipeline_type_kind_ord_at(arena, ty_ref);
      /* TYPE_F32=14 / TYPE_F64=15: FP cursor (slice16). */
      if (tk == 14) {
        which = 7;
      } else if (tk == 15) {
        which = 8;
      } else {
        mod = call_dispatch_load_ptr_le(ctx, 16);
        tsz = glue_type_size_simple(mod, arena, ty_ref, 0);
        if (tk == 9) {
          which = 5;
        } else if (tsz >= 8) {
          which = 4;
        } else {
          which = 3;
        }
      }
    }
    /* 3=i32 4=i64 5=ptr (GP) · 7=f32 8=f64 (FP). */
    if (which < 3 || which == 6 || which > 8) { return 0; }
    is_fp = 0;
    if (which >= 7) { is_fp = 1; }
    if (n_args != 1) { return 0; }
    if (is_method != 0) {
      ap_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
    } else {
      ap_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
    }
    if (ap_ref <= 0) { return 0 - 1; }
    if (pipeline_expr_kind_ord_at(arena, ap_ref) != 3) { return 0; }
    ap_off = glue_asm_local_var_stack_off_scoped(arena, ctx, ap_ref);
    if (ap_off < 16) { return 0 - 1; }

    /* *ap = header; GP cursor at header[0], FP at header[8], OV at header[16].
     * Park header, load class cursor, then slice18 shared-OV select. */
    gp_n = 6;
    if (ta == 1) { gp_n = 8; }
    if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, ap_off, ta) != 0) { return 0 - 1; }
    if (ta == 1) {
      /* x3=&ap; x0=header; park x8; optional +8; x3=&cursor_cell; ldr cursor. */
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0) { return 0 - 1; }
      if (is_fp != 0) {
        /* header+8 rbp-off = lower addr = pointer-8 (same -8 as slot walk). */
        if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - 8, ta) != 0) { return 0 - 1; }
      }
      if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0) { return 0 - 1; }
      if (try_emit_va_cap_ov_select_elf_c(elf_ctx, ctx, ta, is_fp, gp_n) != 0) {
        return 0 - 1;
      }
      if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 1, 0, ta) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_mov_x0_to_x4(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - 8, ta) != 0) { return 0 - 1; }
      if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, 4, ta) != 0) { return 0 - 1; }
      return 1;
    }
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0) { return 0 - 1; }
    if (is_fp != 0) {
      /* header+8 rbp-off = lower addr = pointer-8 (same -8 as slot walk). */
      if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - 8, ta) != 0) { return 0 - 1; }
    }
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0) { return 0 - 1; }
    if (try_emit_va_cap_ov_select_elf_c(elf_ctx, ctx, ta, is_fp, gp_n) != 0) {
      return 0 - 1;
    }
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    if (which == 3 || which == 7) {
      /* i32/f32: eax = *(i32*)cursor; park in edx across bump. */
      if (arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0) { return 0 - 1; }
    } else {
      /* i64 / ptr / f64: rax = *cursor; park in r10 across bump. */
      if (arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0) { return 0 - 1; }
    }
    if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    /* Spill layout: save+k*8 is rbp-(save_off+k*8); next slot is lower addr → -8. */
    if (backend_enc_add_imm_to_rax_arch(elf_ctx, 0 - 8, ta) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0) { return 0 - 1; }
    if (which == 3 || which == 7) {
      if (arch_x86_64_enc_enc_mov_edx_to_eax(elf_ctx) != 0) { return 0 - 1; }
    } else {
      if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) { return 0 - 1; }
    }
    return 1;
  }
}

/**
 * Stage 10 (10.4.1) slice1–3 + (10.4.2) fences + arm64 i32/fence:
 * atomic load/store/cas i16/i32/i64 (x86) and i32 (aarch64 LSE),
 * fence_seq_cst/acquire/release on both.
 * Match CALL/METHOD_CALL by exact name; spill args; emit lock/xchg/cmpxchg
 * (ta==0) or ldar/stlr/casal/dmb (ta==1). Other arches → 0 fallthrough.
 * PLATFORM: SHARED emit · LINUX|x86_64 / aarch64 runtime (Darwin aarch64 OK for
 * atomics/fences — CPU ops, not syscall ABI).
 * @return i32 — 1 emitted; 0 not applicable; -1 emit error
 */
function try_emit_atomic_builtin_call_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 || ctx == 0 as *u8 || expr_ref <= 0) {
    return 0;
  }
  unsafe {
    let ko: i32 = 0;
    let name: u8[128] = [];
    let nlen: i32 = 0;
    let n_args: i32 = 0;
    let is_method: i32 = 0;
    let which: i32 = 0;
    let i: i32 = 0;
    let cur: i32 = 0;
    let off: i32[4] = [];
    let arg_ref: i32 = 0;
    /* 1=load32 2=store32 3=cas32 4=load64 5=store64 6=cas64
     * 7=fence_seq_cst 8=fence_acquire 9=fence_release
     * 10=load16 11=store16 12=cas16 */
    let nm_fseq: u8[20] = [97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 115, 101, 113, 95, 99, 115, 116];
    let nm_facq: u8[20] = [97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 97, 99, 113, 117, 105, 114, 101];
    let nm_frel: u8[20] = [97, 116, 111, 109, 105, 99, 95, 102, 101, 110, 99, 101, 95, 114, 101, 108, 101, 97, 115, 101];
    let nm_load32: u8[15] = [97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 51, 50];
    let nm_store32: u8[16] = [97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 51, 50];
    let nm_cas32: u8[14] = [97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 51, 50];
    let nm_load64: u8[15] = [97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 54, 52];
    let nm_store64: u8[16] = [97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 54, 52];
    let nm_cas64: u8[14] = [97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 54, 52];
    let nm_load16: u8[15] = [97, 116, 111, 109, 105, 99, 95, 108, 111, 97, 100, 95, 105, 49, 54];
    let nm_store16: u8[16] = [97, 116, 111, 109, 105, 99, 95, 115, 116, 111, 114, 101, 95, 105, 49, 54];
    let nm_cas16: u8[14] = [97, 116, 111, 109, 105, 99, 95, 99, 97, 115, 95, 105, 49, 54];
    if (ta != 0 && ta != 1) {
      return 0;
    }
    ko = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (ko == 49) {
      nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
      if (nlen <= 0 || nlen > 127) { return 0; }
      pipeline_expr_method_call_name_into(arena, expr_ref, &name[0]);
      n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
      is_method = 1;
    } else if (ko == 48) {
      let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      let cko: i32 = 0;
      if (callee_ref <= 0) { return 0; }
      cko = pipeline_expr_kind_ord_at(arena, callee_ref);
      if (cko == 44) {
        nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
        if (nlen <= 0 || nlen > 127) { return 0; }
        pipeline_expr_field_access_name_into(arena, callee_ref, &name[0]);
      } else if (cko == 3) {
        nlen = pipeline_expr_var_name_len(arena, callee_ref);
        if (nlen <= 0 || nlen > 127) { return 0; }
        pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
      } else {
        return 0;
      }
      n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    } else {
      return 0;
    }
    which = 0;
    if (nlen == 15) {
      i = 0;
      while (i < 15) {
        if (name[i] != nm_load32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 15) { which = 1; }
      if (which == 0) {
        i = 0;
        while (i < 15) {
          if (name[i] != nm_load64[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 15) { which = 4; }
      }
      if (which == 0) {
        i = 0;
        while (i < 15) {
          if (name[i] != nm_load16[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 15) { which = 10; }
      }
    }
    if (which == 0 && nlen == 16) {
      i = 0;
      while (i < 16) {
        if (name[i] != nm_store32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 16) { which = 2; }
      if (which == 0) {
        i = 0;
        while (i < 16) {
          if (name[i] != nm_store64[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 16) { which = 5; }
      }
      if (which == 0) {
        i = 0;
        while (i < 16) {
          if (name[i] != nm_store16[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 16) { which = 11; }
      }
    }
    if (which == 0 && nlen == 14) {
      i = 0;
      while (i < 14) {
        if (name[i] != nm_cas32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 14) { which = 3; }
      if (which == 0) {
        i = 0;
        while (i < 14) {
          if (name[i] != nm_cas64[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 14) { which = 6; }
      }
      if (which == 0) {
        i = 0;
        while (i < 14) {
          if (name[i] != nm_cas16[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 14) { which = 12; }
      }
    }
    if (which == 0 && nlen == 20) {
      i = 0;
      while (i < 20) {
        if (name[i] != nm_fseq[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 20) { which = 7; }
      if (which == 0) {
        i = 0;
        while (i < 20) {
          if (name[i] != nm_facq[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 20) { which = 8; }
      }
      if (which == 0) {
        i = 0;
        while (i < 20) {
          if (name[i] != nm_frel[i]) { i = 99; }
          else { i = i + 1; }
        }
        if (i == 20) { which = 9; }
      }
    }
    if (which == 0) { return 0; }
    if ((which == 1 || which == 4 || which == 10) && n_args != 1) { return 0; }
    if ((which == 2 || which == 5 || which == 11) && n_args != 2) { return 0; }
    if ((which == 3 || which == 6 || which == 12) && n_args != 3) { return 0; }
    if ((which == 7 || which == 8 || which == 9) && n_args != 0) { return 0; }
    cur = call_dispatch_load_i32_le(ctx, 4);
    i = 0;
    while (i < n_args) {
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_for_call_args(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off[i] = cur + 16;
      if (off[i] < 16) { off[i] = 16; }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, off[i], ta) != 0) { return 0 - 1; }
      cur = off[i];
      i = i + 1;
    }
    call_dispatch_store_i32_le(ctx, 4, cur + 16);
    /* aarch64: i16/i32/i64 load/store/cas + fences. */
    if (ta == 1) {
      if (which == 1) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldar_w0_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 4) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldar_x0_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 10) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldarh_w0_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 2) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_stlr_w1_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 5) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_stlr_x1_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 11) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_stlrh_w1_x0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 3) {
        /* desired→x1; expected*→x3; ptr→x2; *expected→w0; save w4; casal; str; cmp; cset */
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldr_w0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_w0_to_w4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_casal_w0_w1_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_str_w0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cmp_w0_w4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 6) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldr_x0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_casal_x0_x1_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_str_x0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cmp_x0_x4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 12) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x1(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x3(elf_ctx) != 0) { return 0 - 1; }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_x0_to_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_ldrh_w0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_mov_w0_to_w4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_casalh_w0_w1_x2(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_strh_w0_x3(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cmp_w0_w4(elf_ctx) != 0) { return 0 - 1; }
        if (arch_arm64_enc_enc_cset_eq_w0(elf_ctx) != 0) { return 0 - 1; }
        return 1;
      }
      if (which == 7 || which == 8 || which == 9) {
        if (which == 7) {
          if (arch_arm64_enc_enc_dmb_ish(elf_ctx) != 0) { return 0 - 1; }
        } else if (which == 8) {
          if (arch_arm64_enc_enc_dmb_ishld(elf_ctx) != 0) { return 0 - 1; }
        } else {
          if (arch_arm64_enc_enc_dmb_ishst(elf_ctx) != 0) { return 0 - 1; }
        }
        if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
        return 1;
      }
      return 0;
    }
    if (which == 1) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movl_mem_rax_to_eax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 4) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movq_mem_rax_to_rax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 10) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movzwl_mem_rax_to_eax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 2) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_xchg_edx_mem_rax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 5) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_xchg_rdx_mem_rax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 11) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_xchg_dx_mem_rax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 3) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_eax_to_edx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movl_mem_rcx_to_eax(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_lock_cmpxchg_edx_mem_rbx(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movl_eax_to_mem_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 12) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_ax_to_dx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
      if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movzwl_mem_rcx_to_eax(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_lock_cmpxchg_dx_mem_rbx(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movw_ax_to_mem_rcx(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) { return 0 - 1; }
      if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) { return 0 - 1; }
      return 1;
    }
    if (which == 7 || which == 8 || which == 9) {
      /* 10.4.2 fences: 0-arg; emit barrier then imm 0 in eax. */
      if (which == 7) {
        if (arch_x86_64_enc_enc_mfence(elf_ctx) != 0) { return 0 - 1; }
      } else if (which == 8) {
        if (arch_x86_64_enc_enc_lfence(elf_ctx) != 0) { return 0 - 1; }
      } else {
        if (arch_x86_64_enc_enc_sfence(elf_ctx) != 0) { return 0 - 1; }
      }
      if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
      return 1;
    }
    /* cas i64: desired→rdx; expected_ptr→rcx; ptr→rbx; *expected→rax LAST */
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[2], ta) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) { return 0 - 1; }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[1], ta) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_mov_rax_to_rcx(elf_ctx) != 0) { return 0 - 1; }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, off[0], ta) != 0) { return 0 - 1; }
    if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movq_mem_rcx_to_rax(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_lock_cmpxchg_rdx_mem_rbx(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movq_rax_to_mem_rcx(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_sete_al(elf_ctx) != 0) { return 0 - 1; }
    if (arch_x86_64_enc_enc_movzbl_al_eax(elf_ctx) != 0) { return 0 - 1; }
    return 1;
  }
}

/**
 * Resolve SIMD HW feature bits for language-builtin emit (ta-aware).
 * x86: glue pending or host SSE2 detect. aarch64: OR in NEON (mandatory on
 * ARM64; x86 gold cross-emit may leave host SSE in pending).
 * @param ta i32 — 0=x86_64 1=aarch64
 * @param feats_in u32 — glue_simd_emit_cpu_features_c() raw value
 * @return u32 — feature mask for simd_enc try_hw_* calls
 * PLATFORM: SHARED · LINUX cross-emit gold on x86_64 host.
 */
function try_emit_simd_lang_resolve_feats_c(ta: i32, feats_in: u32): u32 {
  let feats: u32 = feats_in;
  if (ta == 1) {
    if ((feats & 256) == 0) {
      feats = feats | 256;
    }
    return feats;
  }
  if (feats == 0) {
    feats = xlang_target_cpu_detect_host();
  }
  return feats;
}

/**
 * Stage 10 (10.5.1) slice0–9: language SIMD builtins add/mul/sub/fma/hsum/dot.
 *
 * Matches CALL/METHOD_CALL by exact export name (std.simd.builtin surface).
 * f32x4 add/mul/sub: spill each Vec4f arg (16B dual-GP), x86 SSE or aarch64 NEON,
 *   reload dual-GP (x86 rdx/rax · aarch64 x1/x0).
 * f32x4 fma (slice7/9): 3-arg spill; x86 FMA3/mulps+addps · aarch64 NEON fmul+fadd.
 * f32x4 hsum/dot (slice8/9): spill; x86 SSE or aarch64 faddp → xmm0/s0 → eax/w0.
 * i32x8/f32x8: VAR stack homes + sret let slot; x86 AVX2/SSE or aarch64 NEON dual-half.
 *
 * @return i32 — 1 emitted; 0 not applicable or HW unavailable (fallthrough);
 *               -1 emit error
 * PLATFORM: LINUX|x86_64 (ta==0) · MACOS|ARM64|LINUX aarch64 (ta==1); SHARED name match.
 */
function try_emit_simd_lang_builtin_call_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 || ctx == 0 as *u8 || expr_ref <= 0) {
    return 0;
  }
  /* slice5: x86_64 SSE/AVX + aarch64 NEON f32x4; i32x8/f32x8 remain x86-only for now. */
  if (ta != 0 && ta != 1) {
    return 0;
  }
  unsafe {
    let ko: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let name: u8[128] = [];
    let nlen: i32 = 0;
    let n_args: i32 = 0;
    let is_method: i32 = 0;
    let which: i32 = 0;
    let i: i32 = 0;
    let arg_ref: i32 = 0;
    let off_a: i32 = 0;
    let off_b: i32 = 0;
    let off_c: i32 = 0;
    let dst_off: i32 = 0;
    let cur: i32 = 0;
    let feats: u32 = 0;
    let hw: i32 = 0;
    let ko_a: i32 = 0;
    let ko_b: i32 = 0;
    let sret_sh: i32 = 0;
    let ar0: i32 = 0;
    let ar1: i32 = 0;
    /* add_f32x4 (9) */
    let nm_add_f32: u8[9] = [97, 100, 100, 95, 102, 51, 50, 120, 52];
    /* mul_f32x4 (9) */
    let nm_mul_f32: u8[9] = [109, 117, 108, 95, 102, 51, 50, 120, 52];
    /* add_i32x8 (9) */
    let nm_add_i32: u8[9] = [97, 100, 100, 95, 105, 51, 50, 120, 56];
    /* mul_i32x8 (9) */
    let nm_mul_i32: u8[9] = [109, 117, 108, 95, 105, 51, 50, 120, 56];
    /* sub_f32x4 (9) */
    let nm_sub_f32: u8[9] = [115, 117, 98, 95, 102, 51, 50, 120, 52];
    /* sub_i32x8 (9) */
    let nm_sub_i32: u8[9] = [115, 117, 98, 95, 105, 51, 50, 120, 56];
    /* add_f32x8 (9) */
    let nm_add_f32x8: u8[9] = [97, 100, 100, 95, 102, 51, 50, 120, 56];
    /* mul_f32x8 (9) */
    let nm_mul_f32x8: u8[9] = [109, 117, 108, 95, 102, 51, 50, 120, 56];
    /* sub_f32x8 (9) */
    let nm_sub_f32x8: u8[9] = [115, 117, 98, 95, 102, 51, 50, 120, 56];
    /* fma_f32x4 (9) — slice7 */
    let nm_fma_f32: u8[9] = [102, 109, 97, 95, 102, 51, 50, 120, 52];
    /* dot_f32x4 (9) — slice8 */
    let nm_dot_f32: u8[9] = [100, 111, 116, 95, 102, 51, 50, 120, 52];
    /* hsum_f32x4 (10) — slice8 */
    let nm_hsum_f32: u8[10] = [104, 115, 117, 109, 95, 102, 51, 50, 120, 52];
    if (ko == 49) {
      nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
      if (nlen != 9 && nlen != 10) { return 0; }
      pipeline_expr_method_call_name_into(arena, expr_ref, &name[0]);
      n_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
      is_method = 1;
    } else if (ko == 48) {
      let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      let cko: i32 = 0;
      if (callee_ref <= 0) { return 0; }
      cko = pipeline_expr_kind_ord_at(arena, callee_ref);
      if (cko == 44) {
        nlen = pipeline_expr_field_access_name_len(arena, callee_ref);
        if (nlen != 9 && nlen != 10) { return 0; }
        pipeline_expr_field_access_name_into(arena, callee_ref, &name[0]);
      } else if (cko == 3) {
        nlen = pipeline_expr_var_name_len(arena, callee_ref);
        if (nlen != 9 && nlen != 10) { return 0; }
        pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
      } else {
        return 0;
      }
      n_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    } else {
      return 0;
    }
    /* Arity checked after name match: binops need 2; fma_f32x4 needs 3. */
    which = 0;
    i = 0;
    while (i < 9) {
      if (name[i] != nm_add_f32[i]) { i = 99; }
      else { i = i + 1; }
    }
    if (i == 9) { which = 1; }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_mul_f32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 2; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_add_i32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 3; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_mul_i32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 4; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_sub_f32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 5; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_sub_i32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 6; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_add_f32x8[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 7; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_mul_f32x8[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 8; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_sub_f32x8[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 9; }
    }
    if (which == 0) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_fma_f32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 10; }
    }
    if (which == 0 && nlen == 9) {
      i = 0;
      while (i < 9) {
        if (name[i] != nm_dot_f32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 9) { which = 11; }
    }
    if (which == 0 && nlen == 10) {
      i = 0;
      while (i < 10) {
        if (name[i] != nm_hsum_f32[i]) { i = 99; }
        else { i = i + 1; }
      }
      if (i == 10) { which = 12; }
    }
    if (which == 0) { return 0; }
    /* slice7/9: fma_f32x4 — 3× dual-GP spill; x86 FMA/SSE or aarch64 NEON; reload. */
    if (which == 10) {
      if (n_args != 3) { return 0; }
      if (ta != 0 && ta != 1) { return 0; }
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off_a = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
      if (off_a < 0) { return 0 - 1; }
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 1);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 1);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off_b = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
      if (off_b < 0) { return 0 - 1; }
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 2);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 2);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off_c = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
      if (off_c < 0) { return 0 - 1; }
      cur = call_dispatch_load_i32_le(ctx, 4);
      dst_off = cur + 16;
      if (dst_off < 16) { dst_off = 16; }
      call_dispatch_store_i32_le(ctx, 4, dst_off + 16);
      feats = try_emit_simd_lang_resolve_feats_c(ta, glue_simd_emit_cpu_features_c());
      if (ta == 0) {
        if ((feats & 1) == 0) {
          return 0;
        }
      } else {
        if ((feats & 256) == 0) {
          return 0;
        }
      }
      hw = simd_enc_try_hw_vector_fma_rbp(elf_ctx, off_a, off_b, off_c, dst_off, 4, 4, ta, feats);
      if (hw != 0) {
        return 0;
      }
      if (ta == 1) {
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off + 8, ta) != 0) {
          return 0 - 1;
        }
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0) {
          return 0 - 1;
        }
        if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off, ta) != 0) {
          return 0 - 1;
        }
        return 1;
      }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off - 8, ta) != 0) {
        return 0 - 1;
      }
      if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) {
        return 0 - 1;
      }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off, ta) != 0) {
        return 0 - 1;
      }
      return 1;
    }
    /* slice8/9: hsum_f32x4 / dot_f32x4 — spill; SSE/NEON reduce → xmm0/s0 → eax/w0. */
    if (which == 11 || which == 12) {
      if (ta != 0 && ta != 1) { return 0; }
      if (which == 12) {
        if (n_args != 1) { return 0; }
      } else {
        if (n_args != 2) { return 0; }
      }
      if (is_method != 0) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
      }
      if (arg_ref == 0) { return 0 - 1; }
      if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
      off_a = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
      if (off_a < 0) { return 0 - 1; }
      if (which == 11) {
        if (is_method != 0) {
          arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 1);
        } else {
          arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 1);
        }
        if (arg_ref == 0) { return 0 - 1; }
        if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
          return 0 - 1;
        }
        off_b = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
        if (off_b < 0) { return 0 - 1; }
      }
      feats = try_emit_simd_lang_resolve_feats_c(ta, glue_simd_emit_cpu_features_c());
      if (ta == 0) {
        if ((feats & 1) == 0) {
          return 0;
        }
      } else {
        if ((feats & 256) == 0) {
          return 0;
        }
      }
      if (which == 12) {
        hw = simd_enc_try_hw_vector_hsum_f32x4_rbp(elf_ctx, off_a, ta, feats);
      } else {
        hw = simd_enc_try_hw_vector_dot_f32x4_rbp(elf_ctx, off_a, off_b, ta, feats);
      }
      if (hw != 0) {
        return 0;
      }
      /* Pure-asm CALL consumers expect f32 bits in eax/w0 (same as harvest). */
      if (backend_enc_mov_xmm_arg_reg_to_eax_arch(elf_ctx, 0, ta) != 0) {
        return 0 - 1;
      }
      return 1;
    }
    if (n_args != 2) { return 0; }
    /* slice1–6: i32x8 / f32x8 — VAR + sret; x86 SSE/AVX · aarch64 NEON dual-half. */
    if ((ta == 0 || ta == 1) && (which == 3 || which == 4 || which == 6 || which == 7 || which == 8 || which == 9)) {
      if (is_method != 0) {
        ar0 = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
        ar1 = pipeline_expr_method_call_arg_ref(arena, expr_ref, 1);
      } else {
        ar0 = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
        ar1 = pipeline_expr_call_arg_ref(arena, expr_ref, 1);
      }
      if (ar0 == 0 || ar1 == 0) { return 0 - 1; }
      ko_a = pipeline_expr_kind_ord_at(arena, ar0);
      ko_b = pipeline_expr_kind_ord_at(arena, ar1);
      if (ko_a != 3 || ko_b != 3) {
        return 0;
      }
      off_a = glue_asm_local_var_stack_off_scoped(arena, ctx, ar0);
      off_b = glue_asm_local_var_stack_off_scoped(arena, ctx, ar1);
      if (off_a < 0 || off_b < 0) { return 0 - 1; }
      sret_sh = pipeline_asm_emit_call_sret_reg_shift_c();
      if (sret_sh != 0) {
        dst_off = pipeline_asm_emit_ctx_sret_home_off_get();
      } else {
        cur = call_dispatch_load_i32_le(ctx, 4);
        dst_off = cur + 16;
        if (dst_off < 16) { dst_off = 16; }
        call_dispatch_store_i32_le(ctx, 4, dst_off + 32);
      }
      if (dst_off < 0) { return 0; }
      feats = try_emit_simd_lang_resolve_feats_c(ta, glue_simd_emit_cpu_features_c());
      if (ta == 0) {
        if ((feats & 1) == 0) {
          return 0;
        }
      } else {
        if ((feats & 256) == 0) {
          return 0;
        }
      }
      if (which == 3) {
        hw = simd_enc_try_hw_vector_iadd_isub_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats, 0);
      } else if (which == 4) {
        hw = simd_enc_try_hw_vector_imul_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats);
      } else if (which == 6) {
        hw = simd_enc_try_hw_vector_iadd_isub_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats, 1);
      } else if (which == 7) {
        hw = simd_enc_try_hw_vector_fadd_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats);
      } else if (which == 8) {
        hw = simd_enc_try_hw_vector_fmul_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats);
      } else {
        hw = simd_enc_try_hw_vector_fsub_rbp(elf_ctx, off_a, off_b, dst_off, 8, 4, ta, feats);
      }
      if (hw != 0) {
        return 0;
      }
      /* Callee wrote into sret dest (rdi / let slot); no rax/rdx reload. */
      return 1;
    }
    /* slice0: f32x4 — spill dual-GP args, SSE, reload 16B pair into rdx/rax. */
    if (is_method != 0) {
      arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 0);
    } else {
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 0);
    }
    if (arg_ref == 0) { return 0 - 1; }
    if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
      return 0 - 1;
    }
    off_a = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
    if (off_a < 0) { return 0 - 1; }
    if (is_method != 0) {
      arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, 1);
    } else {
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, 1);
    }
    if (arg_ref == 0) { return 0 - 1; }
    if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, arg_ref, ctx, ta) != 0) {
      return 0 - 1;
    }
    off_b = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 2);
    if (off_b < 0) { return 0 - 1; }
    cur = call_dispatch_load_i32_le(ctx, 4);
    dst_off = cur + 16;
    if (dst_off < 16) { dst_off = 16; }
    call_dispatch_store_i32_le(ctx, 4, dst_off + 16);
    feats = try_emit_simd_lang_resolve_feats_c(ta, glue_simd_emit_cpu_features_c());
    if (ta == 0) {
      if ((feats & 1) == 0) {
        return 0;
      }
    }
    if (which == 1) {
      hw = simd_enc_try_hw_vector_fadd_rbp(elf_ctx, off_a, off_b, dst_off, 4, 4, ta, feats);
    } else if (which == 2) {
      hw = simd_enc_try_hw_vector_fmul_rbp(elf_ctx, off_a, off_b, dst_off, 4, 4, ta, feats);
    } else {
      hw = simd_enc_try_hw_vector_fsub_rbp(elf_ctx, off_a, off_b, dst_off, 4, 4, ta, feats);
    }
    if (hw != 0) {
      return 0;
    }
    /* Reload 16B dual-GP result into arg regs (x86 rdx/rax · aarch64 x1/x0). */
    if (ta == 1) {
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off + 8, ta) != 0) {
        return 0 - 1;
      }
      if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 1, ta) != 0) {
        return 0 - 1;
      }
      if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off, ta) != 0) {
        return 0 - 1;
      }
      return 1;
    }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off - 8, ta) != 0) {
      return 0 - 1;
    }
    if (arch_x86_64_enc_enc_mov_rax_to_rdx(elf_ctx) != 0) {
      return 0 - 1;
    }
    if (backend_enc_load_rbp_to_rax_arch(elf_ctx, dst_off, ta) != 0) {
      return 0 - 1;
    }
    return 1;
  }
}

/**
 * Stage10 10.2.1 slice2 / 10.2.3: map in-reg spelling to post-emit move from rax/x0.
 * @param reg *u8 Null-terminated register name string.
 * @param ta i32 Target architecture (0 = x86_64, 1 = arm64).
 * @return i32 — 0 = already in rax/x0 (no mov); 1..6 = SysV/AAPCS arg index
 *   for backend_enc_mov_rax_to_arg_reg_arch (0=rdi/x0…); 100 = rbx;
 *   101 = r10; 102 = x8; 103 = r11 (Windows x64 / SysV volatile scratch);
 *   -1 = unsupported spelling.
 * PLATFORM: SHARED · LINUX|x86_64 (rax/rdi/…) · aarch64 (x0..x7) · WINDOWS x64 (rcx/rdx/r8/r9/r10/r11).
 */
function pipeline_asm_inline_in_reg_mov_kind(reg: *u8, ta: i32): i32 {
  unsafe {
    if (reg == 0 as *u8) {
      return 0 - 1;
    }
    if (ta == 0) {
      /* rax / eax — value already in rax */
      if (reg[0] == (114 as u8) && reg[1] == (97 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 0;
      }
      if (reg[0] == (101 as u8) && reg[1] == (97 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 0;
      }
      /* rdi / edi → arg 0 */
      if (reg[0] == (114 as u8) && reg[1] == (100 as u8) && reg[2] == (105 as u8)
          && reg[3] == (0 as u8)) {
        return 1;
      }
      if (reg[0] == (101 as u8) && reg[1] == (100 as u8) && reg[2] == (105 as u8)
          && reg[3] == (0 as u8)) {
        return 1;
      }
      /* rsi / esi → arg 1 */
      if (reg[0] == (114 as u8) && reg[1] == (115 as u8) && reg[2] == (105 as u8)
          && reg[3] == (0 as u8)) {
        return 2;
      }
      if (reg[0] == (101 as u8) && reg[1] == (115 as u8) && reg[2] == (105 as u8)
          && reg[3] == (0 as u8)) {
        return 2;
      }
      /* rdx / edx → arg 2 */
      if (reg[0] == (114 as u8) && reg[1] == (100 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 3;
      }
      if (reg[0] == (101 as u8) && reg[1] == (100 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 3;
      }
      /* rcx / ecx → arg 3 */
      if (reg[0] == (114 as u8) && reg[1] == (99 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 4;
      }
      if (reg[0] == (101 as u8) && reg[1] == (99 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 4;
      }
      /* r8 / r8d → arg 4 */
      if (reg[0] == (114 as u8) && reg[1] == (56 as u8) && reg[2] == (0 as u8)) {
        return 5;
      }
      if (reg[0] == (114 as u8) && reg[1] == (56 as u8) && reg[2] == (100 as u8)
          && reg[3] == (0 as u8)) {
        return 5;
      }
      /* r9 / r9d → arg 5 */
      if (reg[0] == (114 as u8) && reg[1] == (57 as u8) && reg[2] == (0 as u8)) {
        return 6;
      }
      if (reg[0] == (114 as u8) && reg[1] == (57 as u8) && reg[2] == (100 as u8)
          && reg[3] == (0 as u8)) {
        return 6;
      }
      /* r10 / r10d — Linux syscall arg4 home (not C-ABI k). */
      if (reg[0] == (114 as u8) && reg[1] == (49 as u8) && reg[2] == (48 as u8)
          && reg[3] == (0 as u8)) {
        return 101;
      }
      if (reg[0] == (114 as u8) && reg[1] == (49 as u8) && reg[2] == (48 as u8)
          && reg[3] == (100 as u8) && reg[4] == (0 as u8)) {
        return 101;
      }
      /* r11 / r11d — Windows x64 / SysV volatile scratch (stage10 10.2.3). */
      if (reg[0] == (114 as u8) && reg[1] == (49 as u8) && reg[2] == (49 as u8)
          && reg[3] == (0 as u8)) {
        return 103;
      }
      if (reg[0] == (114 as u8) && reg[1] == (49 as u8) && reg[2] == (49 as u8)
          && reg[3] == (100 as u8) && reg[4] == (0 as u8)) {
        return 103;
      }
      /* rbx / ebx */
      if (reg[0] == (114 as u8) && reg[1] == (98 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 100;
      }
      if (reg[0] == (101 as u8) && reg[1] == (98 as u8) && reg[2] == (120 as u8)
          && reg[3] == (0 as u8)) {
        return 100;
      }
      return 0 - 1;
    }
    if (ta == 1) {
      /* x0 already; x1..x7 → mk 2..8 (k=mk-1); x8 → syscall nr (102). */
      if (reg[0] == (120 as u8) && reg[1] == (48 as u8) && reg[2] == (0 as u8)) {
        return 0;
      }
      if (reg[0] == (120 as u8) && reg[1] == (49 as u8) && reg[2] == (0 as u8)) {
        return 2;
      }
      if (reg[0] == (120 as u8) && reg[1] == (50 as u8) && reg[2] == (0 as u8)) {
        return 3;
      }
      if (reg[0] == (120 as u8) && reg[1] == (51 as u8) && reg[2] == (0 as u8)) {
        return 4;
      }
      if (reg[0] == (120 as u8) && reg[1] == (52 as u8) && reg[2] == (0 as u8)) {
        return 5;
      }
      if (reg[0] == (120 as u8) && reg[1] == (53 as u8) && reg[2] == (0 as u8)) {
        return 6;
      }
      /* Slice2: x6/x7 AAPCS arg homes (mk 7/8 → k 6/7). */
      if (reg[0] == (120 as u8) && reg[1] == (54 as u8) && reg[2] == (0 as u8)) {
        return 7;
      }
      if (reg[0] == (120 as u8) && reg[1] == (55 as u8) && reg[2] == (0 as u8)) {
        return 8;
      }
      if (reg[0] == (120 as u8) && reg[1] == (56 as u8) && reg[2] == (0 as u8)) {
        return 102;
      }
      return 0 - 1;
    }
    return 0 - 1;
  }
}

/**
 * Copy the idx-th comma-separated field from pack into out (NUL-terminated).
 * @return i32 — 0 ok; -1 missing field / overflow
 * PLATFORM: SHARED.
 */
function pipeline_asm_inline_regpack_field(pack: *u8, idx: i32, out: *u8, out_cap: i32): i32 {
  unsafe {
    let i: i32 = 0;
    let field: i32 = 0;
    let o: i32 = 0;
    let c: u8 = 0;
    if (pack == 0 as *u8 || out == 0 as *u8 || out_cap < 2 || idx < 0) {
      return 0 - 1;
    }
    while (1 == 1) {
      c = pack[i];
      if (field == idx) {
        if (c == (0 as u8) || c == (44 as u8)) {
          if (o >= out_cap) {
            return 0 - 1;
          }
          out[o] = 0 as u8;
          return 0;
        }
        if (o + 1 >= out_cap) {
          return 0 - 1;
        }
        out[o] = c;
        o = o + 1;
        i = i + 1;
      } else {
        if (c == (0 as u8)) {
          return 0 - 1;
        }
        if (c == (44 as u8)) {
          field = field + 1;
          i = i + 1;
        } else {
          i = i + 1;
        }
      }
    }
    return 0 - 1;
  }
}

/**
 * Stage10 10.2.1 / 10.2.3: emit EXPR_ASM (kind 60) from template in var_name.
 * Templates: "nop" · "syscall" (x86 0F05 / aarch64 svc) · "pause" (x86 F390 / aarch64 yield)
 *   · "int3" (x86 CC / aarch64 brk #0).
 * Operands: up to 6; int_val = num_in; call_args[0..num_in) = in,
 *   call_args[num_in..) = out/lateout places (VAR only).
 * Out homes: mk==0 (rax/x0) · mk 1..6 SysV GP · mk 2..8 AAPCS x1..x7
 *   · mk==100 rbx · mk==101 r10 (x86) · mk==102 x8 (aarch64, slice10)
 *   · mk==103 r11 (x86, 10.2.3).
 * Place `_` (VAR name "_"): clobber discard — no store (slice6).
 * Options bits in call_num_type_args; noreturn(32) → x86 ud2 after (slice8).
 * Slice9: after noreturn ud2, glue_asm_block_diverged_set(1) so block emit
 * skips trailing stmt_order / final_expr (no fallthrough return).
 * Slice12: preserves_flags(2) → x86 pushfq before template / popfq after
 *   (net RFLAGS restore; aarch64 accept-only no-op).
 * Slice13: nostack(1) → skip preserves_flags wrap (pushfq uses stack);
 *   nostack alone still accept-only for the template itself.
 * Slice14: nomem(4) → hard-fail if any out/lateout stores to a local VAR
 *   (`_` clobber discard still OK; no memory write).
 * Slice15: readonly(8) → same local-out store forbid as nomem.
 * Slice16: pure(16) → same store forbid; pure+noreturn(32) hard-fail
 *   (noreturn is a side effect beyond writing outputs).
 * 10.2.2 slice1: lateout AAPCS GP via backend_enc_mov_arg_reg_to_rax_arch(ta==1).
 * 10.2.2 slice2: open x6/x7 (mk 7/8) — AAPCS arg homes complete x0..x7.
 * 10.2.3: Windows x64 volatile scratch r11 (mk 103), pause, and int3 templates.
 * Extra in-homes: r10 (x86) · x8 (aarch64 nr) · r11 (x86).
 * @param arena *u8 AST arena pointer.
 * @param elf_ctx *u8 Codegen context pointer.
 * @param expr_ref i32 Expression reference.
 * @param ctx *u8 Function context pointer.
 * @param ta i32 Target architecture (0 = x86_64, 1 = arm64).
 * @return i32 — 0 ok; -1 error / unsupported
 * PLATFORM: SHARED emit · LINUX|x86_64 gold · WINDOWS x64 · aarch64 encode.
 */
#[no_mangle]
export function pipeline_asm_try_emit_inline_asm_expr_elf_c(
  arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32
): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 || expr_ref <= 0) {
    return 0 - 1;
  }
  unsafe {
    let ko: i32 = 0;
    let tmpl: u8[128] = [];
    let nop1: u8 = 144 as u8;
    let a64: u8[4] = [];
    let nargs: i32 = 0;
    let num_in: i32 = 0;
    let arg_ref: i32 = 0;
    let pack: u8[128] = [];
    let reg: u8[32] = [];
    let vname: u8[128] = [];
    let i: i32 = 0;
    let mk: i32 = 0;
    let erc: i32 = 0;
    let is_nop: i32 = 0;
    let is_sys: i32 = 0;
    let is_pause: i32 = 0;
    let is_int3: i32 = 0;
    let pko: i32 = 0;
    let vlen: i32 = 0;
    let voff: i32 = 0;
    let opt_bits: i32 = 0;
    let ud2: u8[2] = [];
    let pfq: u8 = 0 as u8;
    ko = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (ko != 60) {
      return 0 - 1;
    }
    pipeline_expr_var_name_into(arena, expr_ref, &tmpl[0]);
    if (tmpl[0] == (110 as u8) && tmpl[1] == (111 as u8) && tmpl[2] == (112 as u8)
        && tmpl[3] == (0 as u8)) {
      is_nop = 1;
    }
    if (tmpl[0] == (115 as u8) && tmpl[1] == (121 as u8) && tmpl[2] == (115 as u8)
        && tmpl[3] == (99 as u8) && tmpl[4] == (97 as u8) && tmpl[5] == (108 as u8)
        && tmpl[6] == (108 as u8) && tmpl[7] == (0 as u8)) {
      is_sys = 1;
    }
    if (tmpl[0] == (112 as u8) && tmpl[1] == (97 as u8) && tmpl[2] == (117 as u8)
        && tmpl[3] == (115 as u8) && tmpl[4] == (101 as u8) && tmpl[5] == (0 as u8)) {
      is_pause = 1;
    }
    if (tmpl[0] == (105 as u8) && tmpl[1] == (110 as u8) && tmpl[2] == (116 as u8)
        && tmpl[3] == (51 as u8) && tmpl[4] == (0 as u8)) {
      is_int3 = 1;
    }
    if (is_nop == 0 && is_sys == 0 && is_pause == 0 && is_int3 == 0) {
      return 0 - 1;
    }
    nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
    if (nargs < 0 || nargs > 6) {
      return 0 - 1;
    }
    num_in = pipeline_expr_int_val_at(arena, expr_ref);
    if (num_in < 0 || num_in > nargs) {
      return 0 - 1;
    }
    /* Options bitfield once (slice8–16 options family). */
    opt_bits = pipeline_expr_call_num_type_args_at(arena, expr_ref);
    /* Slice16: pure + noreturn conflict (side effect beyond outputs). */
    if ((opt_bits & 16) != 0 && (opt_bits & 32) != 0) {
      return 0 - 1;
    }
    if (nargs > 0) {
      if (ctx == 0 as *u8) {
        return 0 - 1;
      }
      pipeline_expr_method_call_name_into(arena, expr_ref, &pack[0]);
      /* ---- in operands ---- */
      i = 0;
      while (i < num_in) {
        if (pipeline_asm_inline_regpack_field(&pack[0], i, &reg[0], 32) != 0) {
          return 0 - 1;
        }
        mk = pipeline_asm_inline_in_reg_mov_kind(&reg[0], ta);
        if (mk < 0) {
          return 0 - 1;
        }
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref <= 0) {
          return 0 - 1;
        }
        erc = pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, arg_ref, ctx, ta);
        if (erc != 0) {
          return 0 - 1;
        }
        if (mk >= 1 && mk <= 8) {
          if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, mk - 1, ta) != 0) {
            return 0 - 1;
          }
        }
        if (mk == 100) {
          if (backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta) != 0) {
            return 0 - 1;
          }
        }
        if (mk == 101) {
          if (ta != 0) {
            return 0 - 1;
          }
          if (arch_x86_64_enc_enc_mov_rax_to_r10(elf_ctx) != 0) {
            return 0 - 1;
          }
        }
        if (mk == 102) {
          if (ta != 1) {
            return 0 - 1;
          }
          if (arch_arm64_enc_enc_mov_rax_to_x8(elf_ctx) != 0) {
            return 0 - 1;
          }
        }
        /* Stage10 10.2.3: r11 Windows x64 / SysV volatile scratch in-reg */
        if (mk == 103) {
          if (ta != 0) {
            return 0 - 1;
          }
          if (arch_x86_64_enc_enc_mov_rax_to_r11(elf_ctx) != 0) {
            return 0 - 1;
          }
        }
        i = i + 1;
      }
      /* Slice14–16: nomem/readonly/pure forbid out/lateout stores to locals. */
      if ((opt_bits & 28) != 0) {
        i = num_in;
        while (i < nargs) {
          arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
          if (arg_ref <= 0) {
            return 0 - 1;
          }
          pko = pipeline_expr_kind_ord_at(arena, arg_ref);
          if (pko != 3) {
            return 0 - 1;
          }
          vlen = pipeline_expr_var_name_len(arena, arg_ref);
          if (vlen <= 0 || vlen > 127) {
            return 0 - 1;
          }
          pipeline_expr_var_name_into(arena, arg_ref, &vname[0]);
          /* `_` clobber discard does not store — allowed. */
          if (!(vlen == 1 && vname[0] == (95 as u8))) {
            return 0 - 1;
          }
          i = i + 1;
        }
      }
    }
    /* Slice12/13: preserves_flags wrap unless nostack (pushfq uses stack). */
    if ((opt_bits & 2) != 0 && (opt_bits & 1) == 0 && ta == 0) {
      pfq = 156 as u8; /* 0x9C pushfq */
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &pfq, 1) != 0) {
        return 0 - 1;
      }
    }
    /* ---- template ---- */
    if (is_nop != 0) {
      if (ta == 0) {
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &nop1, 1) != 0) {
          return 0 - 1;
        }
      } else if (ta == 1) {
        a64[0] = 31 as u8;
        a64[1] = 32 as u8;
        a64[2] = 3 as u8;
        a64[3] = 213 as u8;
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &a64[0], 4) != 0) {
          return 0 - 1;
        }
      } else {
        return 0 - 1;
      }
    } else if (is_pause != 0) {
      if (ta == 0) {
        if (arch_x86_64_enc_enc_pause(elf_ctx) != 0) {
          return 0 - 1;
        }
      } else if (ta == 1) {
        /* aarch64 yield: 0xd503203f */
        a64[0] = 63 as u8;
        a64[1] = 32 as u8;
        a64[2] = 3 as u8;
        a64[3] = 213 as u8;
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &a64[0], 4) != 0) {
          return 0 - 1;
        }
      } else {
        return 0 - 1;
      }
    } else if (is_int3 != 0) {
      if (ta == 0) {
        if (arch_x86_64_enc_enc_int3(elf_ctx) != 0) {
          return 0 - 1;
        }
      } else if (ta == 1) {
        /* aarch64 brk #0: 0xd4200000 */
        a64[0] = 0 as u8;
        a64[1] = 0 as u8;
        a64[2] = 32 as u8;
        a64[3] = 212 as u8;
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &a64[0], 4) != 0) {
          return 0 - 1;
        }
      } else {
        return 0 - 1;
      }
    } else {
      if (ta == 0) {
        if (arch_x86_64_enc_enc_syscall(elf_ctx) != 0) {
          return 0 - 1;
        }
      } else if (ta == 1) {
        if (arch_arm64_enc_enc_svc(elf_ctx) != 0) {
          return 0 - 1;
        }
      } else {
        return 0 - 1;
      }
    }
    /* Slice12/13: popfq after template unless nostack. */
    if ((opt_bits & 2) != 0 && (opt_bits & 1) == 0 && ta == 0) {
      pfq = 157 as u8; /* 0x9D popfq */
      if (pipeline_elf_ctx_append_bytes(elf_ctx, &pfq, 1) != 0) {
        return 0 - 1;
      }
    }
    /* ---- out / lateout: VAR store, or `_` clobber discard (slice6) ---- */
    i = num_in;
    while (i < nargs) {
      if (ctx == 0 as *u8) {
        return 0 - 1;
      }
      if (pipeline_asm_inline_regpack_field(&pack[0], i, &reg[0], 32) != 0) {
        return 0 - 1;
      }
      mk = pipeline_asm_inline_in_reg_mov_kind(&reg[0], ta);
      if (mk < 0) {
        return 0 - 1;
      }
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      if (arg_ref <= 0) {
        return 0 - 1;
      }
      pko = pipeline_expr_kind_ord_at(arena, arg_ref);
      if (pko != 3) {
        return 0 - 1;
      }
      vlen = pipeline_expr_var_name_len(arena, arg_ref);
      if (vlen <= 0 || vlen > 127) {
        return 0 - 1;
      }
      pipeline_expr_var_name_into(arena, arg_ref, &vname[0]);
      /* Slice6: VAR "_" = clobber discard — validate reg, no store. */
      if (vlen == 1 && vname[0] == (95 as u8)) {
        i = i + 1;
        continue;
      }
      voff = asm_ctx_local_find_offset_scoped(ctx, arena, &vname[0], vlen);
      if (voff < 0) {
        return 0 - 1;
      }
      /* mk==0: value already in rax/x0. */
      if (mk >= 1 && mk <= 8) {
        /* G.7: SysV mk1..6 / AAPCS mk2..8 (x1..x7) → rax/x0 (10.2.2 slice1–2). */
        if (backend_enc_mov_arg_reg_to_rax_arch(elf_ctx, mk - 1, ta) != 0) {
          return 0 - 1;
        }
      }
      if (mk == 100) {
        if (backend_enc_mov_rbx_to_rax_arch(elf_ctx, ta) != 0) {
          return 0 - 1;
        }
      }
      if (mk == 101) {
        if (ta != 0) {
          return 0 - 1;
        }
        if (arch_x86_64_enc_enc_mov_r10_to_rax(elf_ctx) != 0) {
          return 0 - 1;
        }
      }
      /* Slice10: lateout/out("x8") → x0 before store (mirror r10). */
      if (mk == 102) {
        if (ta != 1) {
          return 0 - 1;
        }
        if (arch_arm64_enc_enc_mov_x8_to_rax(elf_ctx) != 0) {
          return 0 - 1;
        }
      }
      /* Stage10 10.2.3: lateout/out("r11") → rax before store */
      if (mk == 103) {
        if (ta != 0) {
          return 0 - 1;
        }
        if (arch_x86_64_enc_enc_mov_r11_to_rax(elf_ctx) != 0) {
          return 0 - 1;
        }
      }
      if (backend_enc_store_rax_to_rbp_arch(elf_ctx, voff, ta) != 0) {
        return 0 - 1;
      }
      i = i + 1;
    }
    /* Slice8: options(noreturn) → ud2 after asm (trap if template returns). */
    /* Slice9: stamp diverged so parent block skips unreachable stmts/final_expr. */
    if ((opt_bits & 32) != 0) {
      if (ta == 0) {
        ud2[0] = 15 as u8;
        ud2[1] = 11 as u8;
        if (pipeline_elf_ctx_append_bytes(elf_ctx, &ud2[0], 2) != 0) {
          return 0 - 1;
        }
        glue_asm_block_diverged_set(1);
      } else {
        return 0 - 1;
      }
    }
    return 0;
  }
}

#[no_mangle]
export function pipeline_asm_emit_call_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (elf_ctx == 0) { return 0 - 1; }
  if (ctx == 0 as *u8) { return 0 - 1; }
  unsafe {
    let callee_ref: i32 = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    if (callee_ref <= 0) { return 0 - 1; }
    let mod_ref: *u8 = call_dispatch_load_ptr_le(ctx, 16);
    // PLATFORM: SHARED LP64 — dep_pipe@1384 (pipeline_abi authority; not 1256).
    // Fallback: process-local set by pipeline_asm_emit_set_dep_pipe (try_inline twin).
    let dep_pipe: *u8 = call_dispatch_load_ptr_le(ctx, 1384);
    if (dep_pipe == 0 as *u8) {
      dep_pipe = pipeline_asm_emit_dep_pipe_c();
    }
    let callee_ko: i32 = pipeline_expr_kind_ord_at(arena, callee_ref);
    /* CORE-001: size_of<T>/align_of<T> → imm (before import mangle → core_types_size_of). */
    {
      let sa_rc: i32 = try_fold_size_align_of_call_elf(arena, elf_ctx, expr_ref, mod_ref, ta);
      if (sa_rc < 0) { return 0 - 1; }
      if (sa_rc > 0) { return 0; }
    }
    /* stage10 S3.1 slice2 (10.1.1): raw_syscall0..6 → direct syscall
     * (before import mangle; same slot as the size_of fold). */
    {
      let rs_rc: i32 = try_emit_raw_syscall_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (rs_rc < 0) { return 0 - 1; }
      if (rs_rc > 0) { return 0; }
    }
    /* Cap 10.7.1 slice12–16: va_start/end/va_arg_{i32,i64,ptr}/va_arg<T> Cap (GP+FP). */
    {
      let va_rc: i32 = try_emit_va_cap_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (va_rc < 0) { return 0 - 1; }
      if (va_rc > 0) { return 0; }
    }
    /* 10.4.1 slice1: atomic_load/store/cas_i32 CALL (x86_64 only). */
    {
      let at_rc: i32 = try_emit_atomic_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (at_rc < 0) { return 0 - 1; }
      if (at_rc > 0) { return 0; }
    }
    /* 10.5.1 slice0: add_f32x4 / mul_f32x4 language SIMD builtins (x86 SSE). */
    {
      let sd_rc: i32 = try_emit_simd_lang_builtin_call_elf_c(arena, elf_ctx, expr_ref, ctx, ta);
      if (sd_rc < 0) { return 0 - 1; }
      if (sd_rc > 0) { return 0; }
    }
    /*
     * Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): CALL through *u8 or TYPE_FN.
     * typeck stamps Cap as TYPE_PTR(u8) or TYPE_FN(18). Emit callee → rax/x0,
     * then blr / call *reg (G.7 reuse backend_enc_blr_arch; same as F7 dyn).
     * slice1: 0-arg. slice2: GP args via spill fn + pipeline_asm_emit_call_args_elf_c
     * then reload fn (args would otherwise clobber rax before blr).
     * PLATFORM: SHARED · LINUX x86_64 call *r · MACOS|ARM64 blr xN.
     */
    {
      let cap_tr: i32 = 0;
      let cap_ko: i32 = 0;
      let cap_er: i32 = 0;
      let cap_eko: i32 = 0;
      let cap_nargs: i32 = 0;
      let cap_eff: i32 = callee_ref;
      let cap_fn_off: i32 = 0;
      let cap_ok: i32 = 0;
      if (callee_ko == 51 || callee_ko == 52) {
        /* EXPR_ADDR_OF / EXPR_DEREF — peel so Cap *u8 / TYPE_FN VAR is visible.
         * (*f)() → DEREF(VAR); Cap ≡ f() (emit pointer value, not u8 load). */
        let inn: i32 = pipeline_expr_unary_operand_ref_at(arena, callee_ref);
        if (inn > 0) { cap_eff = inn; }
      }
      cap_tr = pipeline_expr_resolved_type_ref(arena, cap_eff);
      if (cap_tr > 0) {
        cap_ko = pipeline_type_kind_ord_at(arena, cap_tr);
        /* TYPE_FN (18) shares Cap opaque fn-ptr ABI with *u8. */
        if (cap_ko == 18) {
          cap_ok = 1;
        } else if (cap_ko == 9) {
          cap_er = pipeline_type_elem_ref_at(arena, cap_tr);
          if (cap_er > 0) {
            cap_eko = pipeline_type_kind_ord_at(arena, cap_er);
            if (cap_eko == 2) {
              cap_ok = 1;
            }
          }
        }
        if (cap_ok != 0) {
              cap_nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
              if (cap_nargs < 0) { return 0 - 1; }
              /*
               * Cap opaque *u8 / TYPE_FN: reuse pipeline_asm_emit_call_args_elf_c
               * for GP regs + stack spill (SysV 6 / AAPCS64 8). slice2 was
               * reg-only; slice4 lifts the reg_max hard-fail (G.7 same packer
               * as direct CALL). PLATFORM: SHARED.
               */
              if (pipeline_asm_emit_expr_elf_c(arena, elf_ctx, cap_eff, ctx, ta) != 0) {
                return 0 - 1;
              }
              if (cap_nargs == 0) {
                /* rax/x0 = Cap-fn-ptr; indirect call. */
                if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
                return 0;
              }
              /* Spill fn, pack args into ABI regs, reload fn, blr. */
              cap_fn_off = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
              if (cap_fn_off < 0) { return 0 - 1; }
              if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, cap_nargs) != 0) {
                return 0 - 1;
              }
              if (backend_enc_load_rbp_to_rax_arch(elf_ctx, cap_fn_off, ta) != 0) {
                return 0 - 1;
              }
              if (backend_enc_blr_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
              return 0;
        }
      }
    }
    // See implementation.
    if (callee_ko == 44) {
      let pre_fmt: u8[16] = [];
      pre_fmt[0] = 115; pre_fmt[1] = 116; pre_fmt[2] = 100; pre_fmt[3] = 95;
      pre_fmt[4] = 102; pre_fmt[5] = 109; pre_fmt[6] = 116; pre_fmt[7] = 95;
      let fn_println: u8[16] = [];
      fn_println[0] = 112; fn_println[1] = 114; fn_println[2] = 105; fn_println[3] = 110;
      fn_println[4] = 116; fn_println[5] = 108; fn_println[6] = 110;
      let fa_lit: i32 = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
        arena, elf_ctx, expr_ref, ctx, ta, &pre_fmt[0], 8, &fn_println[0], 7
      );
      if (fa_lit < 0) { return 0 - 1; }
      if (fa_lit > 0) { return 0; }
      let fn_print: u8[16] = [];
      fn_print[0] = 112; fn_print[1] = 114; fn_print[2] = 105; fn_print[3] = 110; fn_print[4] = 116;
      fa_lit = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
        arena, elf_ctx, expr_ref, ctx, ta, &pre_fmt[0], 8, &fn_print[0], 5
      );
      if (fa_lit < 0) { return 0 - 1; }
      if (fa_lit > 0) { return 0; }
    }
    // import binding + binding.field(args)
    if (mod_ref != 0) {
      if (callee_ko == 44) {
        let base_ref: i32 = pipeline_expr_field_access_base_ref(arena, callee_ref);
        if (base_ref > 0) {
          if (pipeline_expr_kind_ord_at(arena, base_ref) == 3) {
            let base_len: i32 = pipeline_expr_var_name_len(arena, base_ref);
            if (base_len > 0) {
              // wave580 Cap: binding/field name content cap 127 (AST u8[128]).
              if (base_len <= 127) {
                let base_name: u8[128] = [];
                pipeline_expr_var_name_into(arena, base_ref, &base_name[0]);
                let field_len: i32 = pipeline_expr_field_access_name_len(arena, callee_ref);
                if (field_len > 0) {
                  if (field_len <= 127) {
                    let field_name: u8[128] = [];
                    pipeline_expr_field_access_name_into(arena, callee_ref, &field_name[0]);
                    let j: i32 = 0;
                    let nimp: i32 = parser_get_module_num_imports(mod_ref);
                    while (j < nimp) {
                      if (pipeline_module_import_kind_at(mod_ref, j) == 1) {
                        if (glue_asm_import_binding_name_equal(mod_ref, j, &base_name[0], base_len) != 0) {
                          let pre_buf: u8[128] = [];
                          let pre_len: i32 = glue_asm_fill_c_prefix_from_module_import(mod_ref, j, &pre_buf[0]);
                          if (pre_len <= 0) { return 0 - 1; }
                          let sym_flat: u8[128] = [];
                          /* PLATFORM: SHARED — G.7 import-binding CALL mangle (same as METHOD). */
                          let sym_len: i32 = glue_asm_mangle_import_binding_call_sym_c(
                            arena, ctx, expr_ref, mod_ref, j, &pre_buf[0], pre_len,
                            &field_name[0], field_len, 0, &sym_flat[0]
                          );
                          if (sym_len <= 0) { return 0 - 1; }
                          let fmt_lit: i32 = glue_asm_try_emit_fmt_string_lit_import_call_elf_c(
                            arena, elf_ctx, expr_ref, ctx, ta, &pre_buf[0], pre_len, &field_name[0], field_len
                          );
                          if (fmt_lit < 0) { return 0 - 1; }
                          if (fmt_lit > 0) { return 0; }
                          let fmt_any_c: i32 = glue_asm_try_emit_fmt_any_import_call_elf_c(
                            arena, elf_ctx, expr_ref, ctx, ta, &pre_buf[0], pre_len, &field_name[0], field_len
                          );
                          if (fmt_any_c < 0) { return 0 - 1; }
                          if (fmt_any_c > 0) { return 0; }
                          let call_nargs: i32 = pipeline_expr_call_num_args_at(arena, expr_ref);
                          let n_ov: i32 = pipeline_codegen_call_num_args_override(
                            &pre_buf[0], pre_len, &field_name[0], field_len, call_nargs
                          );
                          if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, n_ov) != 0) {
                            return 0 - 1;
                          }
                          if (glue_asm_enc_call_redirected(elf_ctx, &sym_flat[0], sym_len, ta) != 0) {
                            return 0 - 1;
                          }
                          let cln: i32 = glue_asm_call_stack_cleanup_bytes(ta, n_ov);
                          if (cln < 0) { return 0 - 1; }
                          if (backend_enc_call_stack_cleanup_arch(elf_ctx, cln, ta) != 0) { return 0 - 1; }
                          return 0;
                        }
                      }
                      j = j + 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    // See implementation.
    if (mod_ref != 0) {
      if (callee_ko == 44) {
        let imp_elt: i32 = 0;
        let sym_eh: u8[128] = [];
        let elen: i32 = pipeline_asm_resolve_whole_import_qualified_symbol_c(
          arena, mod_ref, callee_ref, &sym_eh[0], &imp_elt
        );
        if (elen > 0) {
          if (imp_elt >= 0) {
            if (imp_elt < parser_get_module_num_imports(mod_ref)) {
              let field_len2: i32 = pipeline_expr_field_access_name_len(arena, callee_ref);
              if (field_len2 <= 0) { return 0 - 1; }
              if (field_len2 > 127) { return 0 - 1; }
              let field_name2: u8[128] = [];
              pipeline_expr_field_access_name_into(arena, callee_ref, &field_name2[0]);
              let pre_eb: u8[128] = [];
              let pre_el: i32 = glue_asm_fill_c_prefix_from_module_import(mod_ref, imp_elt, &pre_eb[0]);
              if (pre_el <= 0) { return 0 - 1; }
              let call_nargs2: i32 = pipeline_expr_call_num_args_at(arena, expr_ref);
              let n_wo_elf: i32 = pipeline_codegen_call_num_args_override(
                &pre_eb[0], pre_el, &field_name2[0], field_len2, call_nargs2
              );
              if (pipeline_asm_emit_call_args_elf_c(arena, elf_ctx, expr_ref, ctx, ta, n_wo_elf) != 0) {
                return 0 - 1;
              }
              if (glue_asm_enc_call_redirected(elf_ctx, &sym_eh[0], elen, ta) != 0) { return 0 - 1; }
              let cln2: i32 = glue_asm_call_stack_cleanup_bytes(ta, n_wo_elf);
              if (cln2 < 0) { return 0 - 1; }
              if (backend_enc_call_stack_cleanup_arch(elf_ctx, cln2, ta) != 0) { return 0 - 1; }
              return 0;
            }
          }
        }
      }
    }
    // See implementation.
    if (callee_ko != 3) { return 0 - 1; }
    let nargs: i32 = pipeline_expr_call_num_args_at(arena, expr_ref);
    if (nargs < 0) { return 0 - 1; }
    if (nargs > 96) { return 0 - 1; }
    let inline_rc: i32 = try_inline_param0_single_field_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0) {
      if (inline_rc < 0) { return 0 - 1; }
      return 0;
    }
    inline_rc = try_inline_param0_field_sum_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0) {
      if (inline_rc < 0) { return 0 - 1; }
      return 0;
    }
    inline_rc = try_inline_x_plus_k_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0) {
      if (inline_rc < 0) { return 0 - 1; }
      return 0;
    }
    inline_rc = try_call_wpo_mono_symbol_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0) {
      if (inline_rc < 0) { return 0 - 1; }
      return 0;
    }
    inline_rc = try_call_wpo_mono_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
    if (inline_rc != 0) {
      if (inline_rc < 0) { return 0 - 1; }
      return 0;
    }
    // See implementation.
    let kmono: u8[16] = [];
    kmono[0] = 83; kmono[1] = 72; kmono[2] = 85; kmono[3] = 88; kmono[4] = 95;
    kmono[5] = 87; kmono[6] = 80; kmono[7] = 79; kmono[8] = 95;
    kmono[9] = 77; kmono[10] = 79; kmono[11] = 78; kmono[12] = 79; kmono[13] = 0;
    let knofold: u8[20] = [];
    knofold[0] = 83; knofold[1] = 72; knofold[2] = 85; knofold[3] = 88; knofold[4] = 95;
    knofold[5] = 87; knofold[6] = 80; knofold[7] = 79; knofold[8] = 95;
    knofold[9] = 78; knofold[10] = 79; knofold[11] = 95;
    knofold[12] = 70; knofold[13] = 79; knofold[14] = 76; knofold[15] = 68; knofold[16] = 0;
    // wave231 G.7: XLANG_WPO_MONO / XLANG_WPO_NO_FOLD via link_abi_getenv (not raw getenv).
    // Const fold only when neither mono nor no-fold env is set.
    if (link_abi_getenv(&kmono[0]) == 0) {
      if (link_abi_getenv(&knofold[0]) == 0) {
        inline_rc = try_inline_wpo_const_vector_lane_of_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
        if (inline_rc != 0) {
          if (inline_rc < 0) { return 0 - 1; }
          return 0;
        }
        inline_rc = try_inline_wpo_const_scalar_binop_call_elf(arena, elf_ctx, expr_ref, ctx, ta);
        if (inline_rc != 0) {
          if (inline_rc < 0) { return 0 - 1; }
          return 0;
        }
      }
    }
    let clen0: i32 = pipeline_expr_var_name_len(arena, callee_ref);
    if (clen0 <= 0) { return 0 - 1; }
    if (clen0 > 127) { return 0 - 1; }
    let cname: u8[128] = [];
    // wave580 Cap residual: out_cap must match cname[128] / AST name content cap 127.
    let clen: i32 = glue_asm_build_call_export_sym_c(arena, expr_ref, callee_ref, mod_ref, dep_pipe, &cname[0], 128);
    if (clen <= 0) { return 0 - 1; }
    return glue_asm_emit_call_with_cleanup(arena, elf_ctx, expr_ref, ctx, ta, nargs, &cname[0], clen);
  }
  return 0 - 1;
}

// glue_asm_prefix_is_fmt_or_debug: see function docblock below.

/** Exported function `glue_asm_prefix_is_fmt_or_debug`.
 * Implements `glue_asm_prefix_is_fmt_or_debug`.
 * @param pre *u8
 * @param pre_len i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_prefix_is_fmt_or_debug(pre: *u8, pre_len: i32): i32 {
  if (pre == 0) { return 0; }
  if (pre_len < 8) { return 0; }
  // "std_fmt_"
  if (pre_len >= 8) {
    if (pre[0] == 115 && pre[1] == 116 && pre[2] == 100 && pre[3] == 95
        && pre[4] == 102 && pre[5] == 109 && pre[6] == 116 && pre[7] == 95) {
      return 1;
    }
  }
  // "std_debug_"
  if (pre_len >= 10) {
    if (pre[0] == 115 && pre[1] == 116 && pre[2] == 100 && pre[3] == 95
        && pre[4] == 100 && pre[5] == 101 && pre[6] == 98 && pre[7] == 117
        && pre[8] == 103 && pre[9] == 95) {
      return 1;
    }
  }
  return 0;
}

// See implementation.
// See implementation.

/** SysV SSE float slot: f32 (14) or f64 (15). Name is historical; G.7 completes f64.
 * PLATFORM: SHARED kind / LINUX+MACOS x86_64 SysV xmm class. */
#[no_mangle]
export function glue_call_param_is_f32_c(arena: *u8, tr: i32): i32 {
  if (arena == 0 as *u8) { return 0; }
  if (tr <= 0) { return 0; }
  unsafe {
    let k: i32 = pipeline_type_kind_ord_at(arena, tr);
    // TYPE_F32=14, TYPE_F64=15
    if (k == 14) { return 1; }
    if (k == 15) { return 1; }
  }
  return 0;
}

/**
 * True if this arg should use SysV xmm (formal f32/f64, FLOAT_LIT, or resolved float).
 * Twin of seed `glue_arg_ref_is_sse_float_c` (static in rest). Completes import
 * METHOD extras when dep formal mapping is missing: FLOAT_LIT still goes xmm.
 * @param arena *u8 — AST arena
 * @param arg_ref i32 — extra / place expr; 0 is ok when pty is already float
 * @param pty i32 — formal type_ref (may be 0)
 * @return i32 — 1 = SSE class, 0 = integer / MEMORY
 * PLATFORM: SHARED classification / LINUX+MACOS x86_64 SysV placement.
 */
function glue_arg_ref_is_sse_float_c(arena: *u8, arg_ref: i32, pty: i32): i32 {
  if (glue_call_param_is_f32_c(arena, pty) != 0) { return 1; }
  if (arena == 0 as *u8) { return 0; }
  if (arg_ref <= 0) { return 0; }
  unsafe {
    let ko: i32 = pipeline_expr_kind_ord_at(arena, arg_ref);
    let atr: i32 = 0;
    let ak: i32 = 0;
    // FLOAT_LIT kind_ord = 1 — default f64 bits / SysV xmm.
    if (ko == 1) { return 1; }
    atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
    if (atr <= 0) { return 0; }
    ak = pipeline_type_kind_ord_at(arena, atr);
    if (ak == 14) { return 1; }
    if (ak == 15) { return 1; }
  }
  return 0;
}

/**
 * f64 width for movq vs movd when placing into xmm.
 * Twin of seed `glue_arg_ref_is_f64_width_c`. Formal TYPE_F64=15 wins;
 * unstamped FLOAT_LIT defaults to f64 (typeck stamp to f32 clears this).
 * @param arena *u8 — AST arena
 * @param arg_ref i32 — extra / place expr
 * @param pty i32 — formal type_ref
 * @return i32 — 1 = 64-bit xmm move, 0 = 32-bit
 * PLATFORM: SHARED kind / LINUX+MACOS x86_64 SysV.
 */
function glue_arg_ref_is_f64_width_c(arena: *u8, arg_ref: i32, pty: i32): i32 {
  if (arena != 0 as *u8) {
    if (pty > 0) {
      unsafe {
        let pk: i32 = pipeline_type_kind_ord_at(arena, pty);
        if (pk == 15) { return 1; }
        // Formal f32 wins over unstamped FLOAT_LIT default-f64
        // (else arm64 emits fmov dK,x0 for select_lane(1.0) extras).
        if (pk == 14) { return 0; }
      }
    }
  }
  if (arena == 0 as *u8) { return 0; }
  if (arg_ref <= 0) { return 0; }
  unsafe {
    let atr: i32 = 0;
    let ak: i32 = 0;
    // FLOAT_LIT: honor typeck stamp (f32=14 / f64=15). Unstamped default f64.
    // Dyn extras pass pty=0 (slot ≠ func) so formal-kind cannot win above.
    if (pipeline_expr_kind_ord_at(arena, arg_ref) == 1) {
      atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
      if (atr > 0) {
        ak = pipeline_type_kind_ord_at(arena, atr);
        if (ak == 15) { return 1; }
        if (ak == 14) { return 0; }
      }
      return 1;
    }
    atr = pipeline_expr_resolved_type_ref(arena, arg_ref);
    if (atr <= 0) { return 0; }
    ak = pipeline_type_kind_ord_at(arena, atr);
    if (ak == 15) { return 1; }
  }
  return 0;
}

/** Exported function `glue_asm_std_c_wrapper_fname_needs_export_c_suffix`.
 * Implements `glue_asm_std_c_wrapper_fname_needs_export_c_suffix`.
 * @param fname *u8
 * @param nlen i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_std_c_wrapper_fname_needs_export_c_suffix(fname: *u8, nlen: i32): i32 {
  if (fname == 0) { return 0; }
  if (nlen <= 0) { return 0; }
  if (nlen >= 2) {
    if (fname[nlen - 2] == 95) { // '_'
      if (fname[nlen - 1] == 99) { // 'c'
        return 0;
      }
    }
  }
  if (nlen >= 4) {
    if (fname[0]==110 && fname[1]==101 && fname[2]==116 && fname[3]==95) { return 1; } // net_
  }
  if (nlen >= 3) {
    if (fname[0]==102 && fname[1]==115 && fname[2]==95) { return 1; } // fs_
  }
  return 0;
}

/** Exported function `glue_asm_append_export_c_suffix`.
 * Implements `glue_asm_append_export_c_suffix`.
 * @param sym *u8
 * @param slen i32
 * @param cap i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_append_export_c_suffix(sym: *u8, slen: i32, cap: i32): i32 {
  if (sym == 0) { return slen; }
  if (slen <= 0) { return slen; }
  if (slen + 2 >= cap) { return slen; }
  sym[slen] = 95; // '_'
  sym[slen + 1] = 99; // 'c'
  return slen + 2;
}

/** Exported function `glue_asm_import_path_segment_count`.
 * Implements `glue_asm_import_path_segment_count`.
 * @param path *u8
 * @param plen i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_import_path_segment_count(path: *u8, plen: i32): i32 {
  if (path == 0 as *u8) { return 0; }
  if (plen <= 0) { return 0; }
  let n: i32 = 1;
  let ii: i32 = 0;
  while (ii < plen) {
    if (path[ii] == 46) { n = n + 1; } // '.'
    ii = ii + 1;
  }
  return n;
}

// See implementation.

// glue_call_param_type_ref_at / glue_call_param_is_f32_c already in this TU or linked

/** Exported function `glue_asm_c_prefix_redundant_with_name`.
 * Implements `glue_asm_c_prefix_redundant_with_name`.
 * @param pre *u8
 * @param plen i32
 * @param name *u8
 * @param nlen i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_c_prefix_redundant_with_name(pre: *u8, plen: i32, name: *u8, nlen: i32): i32 {
  // prefix must be "build_" (6 chars) and name starts with it
  if (pre == 0) { return 0; }
  if (name == 0 as *u8) { return 0; }
  if (plen != 6) { return 0; }
  if (nlen < plen) { return 0; }
  // build_
  if (pre[0] != 98) { return 0; }
  if (pre[1] != 117) { return 0; }
  if (pre[2] != 105) { return 0; }
  if (pre[3] != 108) { return 0; }
  if (pre[4] != 100) { return 0; }
  if (pre[5] != 95) { return 0; }
  let i: i32 = 0;
  while (i < plen) {
    if (name[i] != pre[i]) { return 0; }
    i = i + 1;
  }
  return 1;
}

/** Exported function `glue_type_kind_to_suffix_c`.
 * Implements `glue_type_kind_to_suffix_c`.
 * @param kind i32
 * @param out *u8
 * @param cap i32
 * @return i32
 */
/**
 * Map a scalar TypeKind ordinal to an overload mid suffix.
 * @param kind i32 — TypeKind ord (TYPE_I32=0 …); compound kinds return 0
 * @param out *u8 — destination buffer
 * @param cap i32 — capacity
 * @return i32 — written length, or 0 for unknown/compound kinds
 * PLATFORM: SHARED — TYPE_I32 is explicit (not silent default). Unknown kinds
 * (SLICE/ARRAY/…) return 0 so glue_asm_type_ref_to_suffix_c can use compound
 * paths; never map u8[] → "i32" (run-io false println_i32_reti32 collision).
 * Aligns codegen_type_ref_to_suffix scalars.
 */
#[no_mangle]
export function glue_type_kind_to_suffix_c(kind: i32, out: *u8, cap: i32): i32 {
  if (out == 0 as *u8) { return 0; }
  if (cap <= 0) { return 0; }
  let s0: u8 = 0; let s1: u8 = 0; let s2: u8 = 0; let s3: u8 = 0; let s4: u8 = 0;
  let slen: i32 = 0;
  if (kind == 0) { // TYPE_I32 — explicit, not default
    s0 = 105; s1 = 51; s2 = 50; slen = 3;
  } else if (kind == 5) { // i64
    s0 = 105; s1 = 54; s2 = 52; slen = 3;
  } else if (kind == 2) { // u8
    s0 = 117; s1 = 56; slen = 2;
  } else if (kind == 3) { // u32
    s0 = 117; s1 = 51; s2 = 50; slen = 3;
  } else if (kind == 4) { // u64
    s0 = 117; s1 = 54; s2 = 52; slen = 3;
  } else if (kind == 6) { // usize
    s0 = 117; s1 = 115; s2 = 105; s3 = 122; s4 = 101; slen = 5;
  } else if (kind == 7) { // isize
    s0 = 105; s1 = 115; s2 = 105; s3 = 122; s4 = 101; slen = 5;
  } else if (kind == 14) { // f32
    s0 = 102; s1 = 51; s2 = 50; slen = 3;
  } else if (kind == 15) { // f64
    s0 = 102; s1 = 54; s2 = 52; slen = 3;
  } else if (kind == 1) { // bool
    s0 = 98; s1 = 111; s2 = 111; s3 = 108; slen = 4;
  } else {
    return 0;
  }
  let i: i32 = 0;
  while (i < slen) {
    if (i >= cap - 1) { break; }
    if (i == 0) { out[i] = s0; }
    if (i == 1) { out[i] = s1; }
    if (i == 2) { out[i] = s2; }
    if (i == 3) { out[i] = s3; }
    if (i == 4) { out[i] = s4; }
    i = i + 1;
  }
  return slen;
}

/**
 * Map a type_ref to an overload-mangle suffix (align seed + codegen_type_ref_to_suffix).
 * PTR → elem + "_ptr"; SLICE → elem + "_slc" (u8[] → u8_slc); ARRAY → elem + "_aN";
 * NAMED → type name ('.' → '_'); else scalar kind suffix.
 * @param a *u8 — AST arena owning type_ref
 * @param type_ref i32 — type pool ref; <=0 → 0
 * @param out *u8 — destination buffer
 * @param out_cap i32 — capacity; must be > 0
 * @return i32 — written length, or 0 on failure
 * PLATFORM: SHARED — must match host std .o mid (println_i32 vs println_u8_slc;
 * free_u8_ptr). G.7 single authority with codegen_type_ref_to_suffix.
 */
#[no_mangle]
export function glue_asm_type_ref_to_suffix_c(a: *u8, type_ref: i32, out: *u8, out_cap: i32): i32 {
  if (a == 0 as *u8) { return 0; }
  if (type_ref <= 0) { return 0; }
  if (out == 0 as *u8) { return 0; }
  if (out_cap <= 0) { return 0; }
  unsafe {
    let tk: i32 = pipeline_type_kind_ord_at(a, type_ref);
    // TYPE_PTR = 9
    if (tk == 9) {
      let elem: i32 = pipeline_type_elem_ref_at(a, type_ref);
      let n: i32 = glue_asm_type_ref_to_suffix_c(a, elem, out, out_cap);
      if (n > 0) {
        if (n + 4 < out_cap) {
          out[n] = 95; // _
          out[n + 1] = 112; // p
          out[n + 2] = 116; // t
          out[n + 3] = 114; // r
          return n + 4;
        }
      }
      return n;
    }
    // TYPE_SLICE = 11 → <elem>_slc (std_fmt_println_u8_slc; wave687 C twin).
    if (tk == 11) {
      let elem_s: i32 = pipeline_type_elem_ref_at(a, type_ref);
      let ns: i32 = glue_asm_type_ref_to_suffix_c(a, elem_s, out, out_cap);
      if (ns > 0) {
        if (ns + 4 < out_cap) {
          out[ns] = 95; // _
          out[ns + 1] = 115; // s
          out[ns + 2] = 108; // l
          out[ns + 3] = 99; // c
          return ns + 4;
        }
      }
      return 0;
    }
    // TYPE_ARRAY = 10 → <elem>_aN (align codegen wave687).
    if (tk == 10) {
      let elem_a: i32 = pipeline_type_elem_ref_at(a, type_ref);
      let asz: i32 = pipeline_type_array_size_at(a, type_ref);
      let na: i32 = glue_asm_type_ref_to_suffix_c(a, elem_a, out, out_cap);
      if (na <= 0) { return 0; }
      if (asz <= 0) { return 0; }
      if (na + 2 >= out_cap) { return 0; }
      out[na] = 95; // _
      out[na + 1] = 97; // a
      na = na + 2;
      let digs: u8[8] = [];
      let nd: i32 = 0;
      let v: i32 = asz;
      while (v > 0) {
        if (nd >= 6) { break; }
        digs[nd] = ((v % 10) + 48) as u8;
        nd = nd + 1;
        v = v / 10;
      }
      if (nd <= 0) { return 0; }
      if (na + nd >= out_cap) { return 0; }
      let di: i32 = nd - 1;
      while (di >= 0) {
        out[na] = digs[di];
        na = na + 1;
        di = di - 1;
      }
      return na;
    }
    // TYPE_VECTOR = 13 → <elem>x<lanes> (f32x4 / i32x8). G.7 ≡ codegen_type_ref_to_suffix.
    // Root (run-perf-simd-xlangffle-select): without this, import METHOD mid skips the
    // vector param → U std_simd_shuffle_i32_a4 while host-C formal exports
    // std_simd_shuffle_f32x4_i32_a4 (BLD001). PLATFORM: SHARED pure-asm product.
    if (tk == 13) {
      let elem_v: i32 = pipeline_type_elem_ref_at(a, type_ref);
      let lanes: i32 = pipeline_type_array_size_at(a, type_ref);
      let ek: i32 = 0;
      let pos: i32 = 0;
      if (elem_v <= 0) { return 0; }
      if (lanes <= 0) { return 0; }
      ek = pipeline_type_kind_ord_at(a, elem_v);
      // TYPE_I32=0 → i32; TYPE_U32=3 → u32; TYPE_F32=14 → f32
      if (ek == 0) {
        if (out_cap < 4) { return 0; }
        out[0] = 105; out[1] = 51; out[2] = 50; pos = 3;
      } else if (ek == 3) {
        if (out_cap < 4) { return 0; }
        out[0] = 117; out[1] = 51; out[2] = 50; pos = 3;
      } else if (ek == 14) {
        if (out_cap < 4) { return 0; }
        out[0] = 102; out[1] = 51; out[2] = 50; pos = 3;
      } else {
        return 0;
      }
      if (pos >= out_cap) { return 0; }
      out[pos] = 120; // 'x'
      pos = pos + 1;
      if (lanes == 4) {
        if (pos >= out_cap) { return 0; }
        out[pos] = 52; // '4'
        return pos + 1;
      }
      if (lanes == 8) {
        if (pos >= out_cap) { return 0; }
        out[pos] = 56; // '8'
        return pos + 1;
      }
      if (lanes == 16) {
        if (pos + 1 >= out_cap) { return 0; }
        out[pos] = 49; // '1'
        out[pos + 1] = 54; // '6'
        return pos + 2;
      }
      return 0;
    }
    // NAMED / user types: prefer type name (String, StrView, Vec_u8, …).
    let n2: i32 = pipeline_type_named_name_into(a, type_ref, out);
    if (n2 > 0) {
      if (n2 < out_cap) {
        let si: i32 = 0;
        while (si < n2) {
          if (out[si] == 46) { // '.'
            out[si] = 95;
          }
          si = si + 1;
        }
        return n2;
      }
    }
    return glue_type_kind_to_suffix_c(tk, out, out_cap);
  }
  return 0;
}

/**
 * Count overloads that share the same param-type suffix signature as func_ix.
 * Used to decide whether import-binding / export mid must append `_ret_<T>`
 * (return-only overloads: set.new(i32)->Set_i32 vs Set_u64, vec.new, …).
 * @param a *u8 — arena for param type_refs (same module as m)
 * @param m *u8 — owning Module
 * @param func_ix i32 — function index in m
 * @return i32 — count of same name+param-sig siblings; 0 on bad input
 * PLATFORM: SHARED — G.7 twin of seed glue_asm_overload_param_sig_count_c.
 * Why: pure mid lacked this gate → stop at name_t1… without _ret_ → user.o
 * U std_set_new_i32 while formal T std_set_new_i32_retSet_i32 (run-set BLD001).
 */
#[no_mangle]
export function glue_asm_overload_param_sig_count_c(a: *u8, m: *u8, func_ix: i32): i32 {
  if (a == 0 as *u8) { return 0; }
  if (m == 0 as *u8) { return 0; }
  if (func_ix < 0) { return 0; }
  unsafe {
    let fname_len: i32 = pipeline_asm_module_func_name_len_at(m, func_ix);
    if (fname_len <= 0) { return 0; }
    if (fname_len > 127) { return 0; }
    let fname: u8[128] = [];
    pipeline_asm_module_func_name_copy64(m, func_ix, &fname[0]);
    let np0: i32 = pipeline_module_func_num_params_at(m, func_ix);
    let c: i32 = 0;
    let nfunc: i32 = pipeline_module_num_funcs(m);
    let i: i32 = 0;
    while (i < nfunc) {
      if (pipeline_asm_module_func_is_extern_at(m, i) == 0) {
        if (pipeline_module_func_name_equal_at(m, i, &fname[0], fname_len) != 0) {
          let npi: i32 = pipeline_module_func_num_params_at(m, i);
          if (npi == np0) {
            let same: i32 = 1;
            let pi: i32 = 0;
            while (pi < np0) {
              let sa: u8[64] = [];
              let sb: u8[64] = [];
              let na: i32 = glue_asm_type_ref_to_suffix_c(
                a, pipeline_module_func_param_type_ref_at(m, func_ix, pi), &sa[0], 64
              );
              let nb: i32 = glue_asm_type_ref_to_suffix_c(
                a, pipeline_module_func_param_type_ref_at(m, i, pi), &sb[0], 64
              );
              if (na != nb) {
                same = 0;
                break;
              }
              let k: i32 = 0;
              while (k < na) {
                if (sa[k] != sb[k]) {
                  same = 0;
                  break;
                }
                k = k + 1;
              }
              if (same == 0) { break; }
              pi = pi + 1;
            }
            if (same != 0) {
              c = c + 1;
            }
          }
        }
      }
      i = i + 1;
    }
    return c;
  }
  return 0;
}

/**
 * Build overload mid name for func_ix: bare when unique; else name_t1_t2[_ret_T].
 * Aligns seed glue_asm_build_func_overload_mid_c (import-binding mid, no dep path).
 * Same param-sig overloads append `_ret_<T>` so call site matches formal export
 * (codegen_emit_func_link_name / seed export: set.new → new_i32_retSet_i32).
 * @param m *u8 — owning Module
 * @param a *u8 — arena for param type_refs
 * @param func_ix i32 — function index in m
 * @param out *u8 — destination
 * @param out_cap i32 — capacity
 * @return i32 — mid length, or -1 on failure
 * PLATFORM: SHARED — G.7 complete pure twin of seed mid (was param-only incomplete).
 */
#[no_mangle]
export function glue_asm_build_func_overload_mid_c(m: *u8, a: *u8, func_ix: i32, out: *u8, out_cap: i32): i32 {
  if (m == 0 as *u8) { return 0 - 1; }
  if (a == 0 as *u8) { return 0 - 1; }
  if (func_ix < 0) { return 0 - 1; }
  if (out == 0 as *u8) { return 0 - 1; }
  if (out_cap <= 0) { return 0 - 1; }
  unsafe {
    let fname_len: i32 = pipeline_asm_module_func_name_len_at(m, func_ix);
    if (fname_len <= 0) { return 0 - 1; }
    if (fname_len >= out_cap) { return 0 - 1; }
    if (fname_len > 127) { return 0 - 1; }
    let fname: u8[128] = [];
    pipeline_asm_module_func_name_copy64(m, func_ix, &fname[0]);
    let pos: i32 = 0;
    while (pos < fname_len) {
      out[pos] = fname[pos];
      pos = pos + 1;
    }
    if (glue_module_func_overload_count_c(m, &fname[0], fname_len) <= 1) {
      return pos;
    }
    let np: i32 = pipeline_module_func_num_params_at(m, func_ix);
    let pi: i32 = 0;
    while (pi < np) {
      if (pos >= out_cap - 2) { break; }
      let pty: i32 = pipeline_module_func_param_type_ref_at(m, func_ix, pi);
      if (pty > 0) {
        let suf: u8[64] = [];
        let sl: i32 = glue_asm_type_ref_to_suffix_c(a, pty, &suf[0], 64);
        if (sl > 0) {
          if (pos + 1 + sl >= out_cap) { return 0 - 1; }
          out[pos] = 95;
          pos = pos + 1;
          let si: i32 = 0;
          while (si < sl) {
            out[pos] = suf[si];
            pos = pos + 1;
            si = si + 1;
          }
        }
      }
      pi = pi + 1;
    }
    // PLATFORM: SHARED — same param-sig overloads need _ret_<T> (seed mid authority).
    // Without this, pure product emits std_set_new_i32 while formal exports
    // std_set_new_i32_retSet_i32 → BLD001 even when set.o is on the link line.
    let sig_count: i32 = glue_asm_overload_param_sig_count_c(a, m, func_ix);
    if (sig_count > 1) {
      let ret_ref: i32 = pipeline_module_func_return_type_at(m, func_ix);
      if (ret_ref > 0) {
        let rsuf: u8[64] = [];
        let rsl: i32 = glue_asm_type_ref_to_suffix_c(a, ret_ref, &rsuf[0], 64);
        if (rsl > 0) {
          if (pos + 4 + rsl >= out_cap) { return 0 - 1; }
          out[pos] = 95; // '_'
          pos = pos + 1;
          out[pos] = 114; // 'r'
          pos = pos + 1;
          out[pos] = 101; // 'e'
          pos = pos + 1;
          out[pos] = 116; // 't'
          pos = pos + 1;
          let ri: i32 = 0;
          while (ri < rsl) {
            out[pos] = rsuf[ri];
            pos = pos + 1;
            ri = ri + 1;
          }
        }
      }
    }
    if (pos > 0) { return pos; }
  }
  return 0 - 1;
}

/**
 * Score field_name candidates in res_mod (arity + arg-type mid match).
 * ARRAY T vs *T counts as a suffix hit (same decay as typeck_overload_arg_param_score
 * ak==10 && pk==9). Without it, from_slice(u64[4], n) stays name+arity first-wins
 * from_slice_i32 (score==1; mangle override requires sc_best>=11).
 * @param arena *u8 — call-site arena
 * @param expr_ref i32 — CALL or METHOD_CALL
 * @param res_mod *u8 — dep module to scan
 * @param res_arena *u8 — arena for res_mod types (may equal arena)
 * @param field_name *u8 — method/field name bytes
 * @param field_len i32 — name length
 * @param want_np i32 — expected param count (= call nargs)
 * @param is_method i32 — 1 → METHOD_CALL arg refs; 0 → CALL arg refs
 * @param out_best_score *i32 — optional; written best suffix-score (1 arity / +10 match)
 * @return i32 — best func_ix or -1
 * PLATFORM: SHARED — product -o mangle; seed twin must match.
 */
#[no_mangle]
export function glue_asm_score_import_binding_func_ix_c(
  arena: *u8, expr_ref: i32, res_mod: *u8, res_arena: *u8,
  field_name: *u8, field_len: i32, want_np: i32, is_method: i32, out_best_score: *i32
): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (res_mod == 0 as *u8) { return 0 - 1; }
  if (field_name == 0 as *u8) { return 0 - 1; }
  if (field_len <= 0) { return 0 - 1; }
  if (res_arena == 0 as *u8) { res_arena = arena; }
  unsafe {
    let best: i32 = 0 - 1;
    let best_score: i32 = 0 - 1;
    let nfunc: i32 = pipeline_module_num_funcs(res_mod);
    let fi: i32 = 0;
    while (fi < nfunc) {
      if (pipeline_asm_module_func_is_extern_at(res_mod, fi) == 0) {
        if (pipeline_module_func_name_equal_at(res_mod, fi, field_name, field_len) != 0) {
          let np: i32 = pipeline_module_func_num_params_at(res_mod, fi);
          if (np == want_np) {
            let score: i32 = 1;
            let pi: i32 = 0;
            while (pi < np) {
              if (pi >= 8) { break; }
              let arg_ref: i32 = 0;
              if (is_method != 0) {
                arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, pi);
              } else {
                arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, pi);
              }
              let arg_ty: i32 = 0;
              if (arg_ref > 0) {
                arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
                if (arg_ty <= 0) {
                  arg_ty = pipeline_typeck_call_arg_effective_type_c(arena, arg_ref);
                }
                /* Co-emit dep bodies: mul(a,b) inside dot may lack resolved_type_ref on
                 * param VARs — match enclosing current_func_index formals (Vec4f not Vec8i).
                 * PLATFORM: SHARED — STD-SIMD-INTRINSIC dot→mul_f32x4 on Ubuntu pure .x. */
                if (arg_ty <= 0) {
                  if (pipeline_expr_kind_ord_at(arena, arg_ref) == 3) {
                    let vn_len: i32 = pipeline_expr_var_name_len(arena, arg_ref);
                    if (vn_len > 0) {
                      if (vn_len <= 127) {
                        let vn: u8[128] = [];
                        pipeline_expr_var_name_into(arena, arg_ref, &vn[0]);
                        let dp_sc: *u8 = pipeline_asm_emit_dep_pipe_c();
                        if (dp_sc != 0 as *u8) {
                          let cur_fi: i32 = pipeline_dep_ctx_current_func_index(dp_sc);
                          if (cur_fi >= 0) {
                            let np_cur: i32 = pipeline_module_func_num_params_at(res_mod, cur_fi);
                            let pj: i32 = 0;
                            while (pj < np_cur) {
                              let plen: i32 = pipeline_module_func_param_name_len_at(res_mod, cur_fi, pj);
                              if (plen == vn_len) {
                                if (plen > 0) {
                                  let pn: u8[128] = [];
                                  pipeline_module_func_param_name_copy32(res_mod, cur_fi, pj, &pn[0]);
                                  let eqn: i32 = 1;
                                  let vk: i32 = 0;
                                  while (vk < plen) {
                                    if (pn[vk] != vn[vk]) { eqn = 0; break; }
                                    vk = vk + 1;
                                  }
                                  if (eqn != 0) {
                                    arg_ty = pipeline_module_func_param_type_ref_at(res_mod, cur_fi, pj);
                                    pj = np_cur;
                                  }
                                }
                              }
                              pj = pj + 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              let pty: i32 = pipeline_module_func_param_type_ref_at(res_mod, fi, pi);
              if (arg_ty > 0) {
                if (pty > 0) {
                  let sa: u8[64] = [];
                  let sb: u8[64] = [];
                  let na: i32 = glue_asm_type_ref_to_suffix_c(arena, arg_ty, &sa[0], 64);
                  let nb: i32 = glue_asm_type_ref_to_suffix_c(res_arena, pty, &sb[0], 64);
                  let hit: i32 = 0;
                  if (na > 0) {
                    if (na == nb) {
                      let eq: i32 = 1;
                      let k: i32 = 0;
                      while (k < na) {
                        if (sa[k] != sb[k]) { eq = 0; break; }
                        k = k + 1;
                      }
                      if (eq != 0) { hit = 1; }
                    }
                  }
                  /* PLATFORM: SHARED — ARRAY T → *T decay ≡ typeck ak==10 pk==9.
                   * FLOAT_LIT splat stays score==1 (not ARRAY); gate sc_best>=11 unchanged. */
                  if (hit == 0) {
                    let ak: i32 = pipeline_type_kind_ord_at(arena, arg_ty);
                    let pk: i32 = pipeline_type_kind_ord_at(res_arena, pty);
                    if (ak == 10) {
                      if (pk == 9) {
                        let ae: i32 = pipeline_type_elem_ref_at(arena, arg_ty);
                        let pe: i32 = pipeline_type_elem_ref_at(res_arena, pty);
                        if (ae > 0) {
                          if (pe > 0) {
                            let sea: u8[64] = [];
                            let seb: u8[64] = [];
                            let nea: i32 = glue_asm_type_ref_to_suffix_c(arena, ae, &sea[0], 64);
                            let neb: i32 = glue_asm_type_ref_to_suffix_c(res_arena, pe, &seb[0], 64);
                            if (nea > 0) {
                              if (nea == neb) {
                                let eqe: i32 = 1;
                                let ke: i32 = 0;
                                while (ke < nea) {
                                  if (sea[ke] != seb[ke]) { eqe = 0; break; }
                                  ke = ke + 1;
                                }
                                if (eqe != 0) { hit = 1; }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  if (hit != 0) { score = score + 10; }
                }
              }
              pi = pi + 1;
            }
            if (score > best_score) {
              best_score = score;
              best = fi;
            }
          }
        }
      }
      fi = fi + 1;
    }
    if (out_best_score != (0 as *i32)) {
      out_best_score[0] = best_score;
    }
    return best;
  }
  return 0 - 1;
}

/**
 * Resolve dep Module for import-binding j: prefer typeck r_dep, else path match.
 * @param dp *u8 — PipelineDepCtx (nullable)
 * @param user_mod *u8 — user module with import table
 * @param imp_j i32 — import index
 * @param r_dep i32 — typeck resolved dep index (-1 if unknown)
 * @param out_arena *u8 — out: dep arena (written when non-null out pointer used via return only)
 * @return *u8 — dep Module or null; arena recovered via pipeline_dep_ctx_arena_at by caller
 * PLATFORM: SHARED
 */
#[no_mangle]
export function glue_asm_res_mod_for_import_binding_c(
  dp: *u8, user_mod: *u8, imp_j: i32, r_dep: i32
): *u8 {
  if (dp == 0 as *u8) { return 0 as *u8; }
  unsafe {
    let nd: i32 = pipeline_dep_ctx_ndep(dp);
    if (r_dep >= 0) {
      if (r_dep < nd) {
        return pipeline_dep_ctx_module_at(dp, r_dep);
      }
    }
    if (user_mod == 0 as *u8) { return 0 as *u8; }
    if (imp_j < 0) { return 0 as *u8; }
    let iplen: i32 = pipeline_module_import_path_len(user_mod, imp_j);
    if (iplen <= 0) { return 0 as *u8; }
    if (iplen > 63) { return 0 as *u8; }
    let di: i32 = 0;
    while (di < nd) {
      let dplen: i32 = pipeline_dep_ctx_import_path_len(dp, di);
      if (dplen == iplen) {
        let dpath: u8[128] = [];
        pipeline_dep_ctx_import_path_copy64(dp, di, &dpath[0]);
        let eq: i32 = 1;
        let k: i32 = 0;
        while (k < iplen) {
          if (dpath[k] != pipeline_module_import_path_byte_at(user_mod, imp_j, k)) {
            eq = 0;
            break;
          }
          k = k + 1;
        }
        if (eq != 0) {
          return pipeline_dep_ctx_module_at(dp, di);
        }
      }
      di = di + 1;
    }
  }
  return 0 as *u8;
}

/**
 * G.7 single authority for import-binding CALL / METHOD_CALL symbol mangle.
 * Builds pre+mid into sym_flat. is_method selects METHOD vs CALL arg accessors.
 * Formal path: resolve dep Module + func_ix → overload mid; unique names stay bare.
 * Fallback: bare pre+field when formal mid unavailable.
 * Root residual: pure METHOD used bare pre+name → U std_string_length while string.o
 * exports length_String / is_empty_String (seed already mangled; pure PREFER incomplete).
 * @param arena *u8 — call-site AST arena
 * @param ctx *u8 — AsmFuncCtx (unused; reserved for arg-type scope recovery)
 * @param expr_ref i32 — CALL or METHOD_CALL expr
 * @param mod_ref *u8 — user module
 * @param imp_j i32 — matching import index
 * @param pre_buf *u8 — C prefix (e.g. std_string_)
 * @param pre_len i32 — prefix length
 * @param field_name *u8 — method / field name
 * @param field_len i32 — name length
 * @param is_method i32 — 1 METHOD_CALL, 0 CALL
 * @param sym_flat *u8 — out symbol buffer (cap 128)
 * @return i32 — symbol length, or -1 on failure
 * PLATFORM: SHARED — mac + Ubuntu pure-asm product. No #[no_mangle]: must match
 * pure-asm mangled call sites from the forward export extern (see comment above).
 * Seed mirror is static short name (seed-only fallback); PREFER .x uses mangled T.
 */
export function glue_asm_mangle_import_binding_call_sym_c(
  arena: *u8, ctx: *u8, expr_ref: i32, mod_ref: *u8, imp_j: i32,
  pre_buf: *u8, pre_len: i32, field_name: *u8, field_len: i32,
  is_method: i32, sym_flat: *u8
): i32 {
  if (arena == 0 as *u8) { return 0 - 1; }
  if (mod_ref == 0 as *u8) { return 0 - 1; }
  if (pre_buf == 0 as *u8) { return 0 - 1; }
  if (pre_len <= 0) { return 0 - 1; }
  if (field_name == 0 as *u8) { return 0 - 1; }
  if (field_len <= 0) { return 0 - 1; }
  if (sym_flat == 0 as *u8) { return 0 - 1; }
  let _ctx_keep: *u8 = ctx; // reserved (scope recovery); silence unused
  if (_ctx_keep == 0 as *u8) { /* ok */ }
  unsafe {
    let r_func: i32 = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    let r_dep: i32 = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
    let dp: *u8 = pipeline_asm_emit_dep_pipe_c();
    let want_np: i32 = 0;
    if (is_method != 0) {
      want_np = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    } else {
      want_np = pipeline_expr_call_num_args_at(arena, expr_ref);
    }
    let mid: u8[128] = [];
    let mid_len: i32 = 0 - 1;
    let sym_len: i32 = 0 - 1;
    let use_fi: i32 = 0 - 1;
    let res_mod: *u8 = 0 as *u8;
    let res_arena: *u8 = arena;
    if (dp != 0 as *u8) {
      // attempt 0: typeck r_dep; attempt 1: path match ignoring bad r_dep
      let attempt: i32 = 0;
      while (attempt < 2) {
        if (use_fi >= 0) { break; }
        let try_dep: i32 = r_dep;
        if (attempt == 1) { try_dep = 0 - 1; }
        res_mod = glue_asm_res_mod_for_import_binding_c(dp, mod_ref, imp_j, try_dep);
        if (res_mod != 0 as *u8) {
          // Prefer arena of matched dep when r_dep valid
          if (try_dep >= 0) {
            let ra: *u8 = pipeline_dep_ctx_arena_at(dp, try_dep);
            if (ra != 0 as *u8) { res_arena = ra; }
          } else {
            // path match: scan for same module pointer to get arena
            let nd: i32 = pipeline_dep_ctx_ndep(dp);
            let di: i32 = 0;
            while (di < nd) {
              if (pipeline_dep_ctx_module_at(dp, di) == res_mod) {
                let ra2: *u8 = pipeline_dep_ctx_arena_at(dp, di);
                if (ra2 != 0 as *u8) { res_arena = ra2; }
                break;
              }
              di = di + 1;
            }
          }
          use_fi = r_func;
          if (use_fi >= 0) {
            if (use_fi < pipeline_module_num_funcs(res_mod)) {
              let ok: i32 = 1;
              if (pipeline_module_func_num_params_at(res_mod, use_fi) != want_np) { ok = 0; }
              if (pipeline_module_func_name_equal_at(res_mod, use_fi, field_name, field_len) == 0) { ok = 0; }
              if (ok == 0) { use_fi = 0 - 1; }
            } else {
              use_fi = 0 - 1;
            }
          }
          if (use_fi < 0) {
            use_fi = glue_asm_score_import_binding_func_ix_c(
              arena, expr_ref, res_mod, res_arena, field_name, field_len, want_np, is_method, 0 as *i32
            );
          }
          /* Overloaded: re-score only when suffix evidence exists (score>=11).
           * Seed already gated sc_best>=11; pure .x used to always overwrite →
           * FLOAT_LIT splat(0.0) first-wins splat_i32 (score==1). G.7 ≡ seed.
           * PLATFORM: SHARED — typeck r_func is the pick authority. */
          if (use_fi >= 0) {
            if (glue_module_func_overload_count_c(res_mod, field_name, field_len) > 1) {
              let sc_best: i32 = 0 - 1;
              let scored: i32 = glue_asm_score_import_binding_func_ix_c(
                arena, expr_ref, res_mod, res_arena, field_name, field_len, want_np, is_method, &sc_best
              );
              if (scored >= 0) {
                if (sc_best >= 11) {
                  use_fi = scored;
                }
              }
            }
          }
        }
        attempt = attempt + 1;
      }
      // attempt 2: scan all deps for unique name+arity hit
      if (use_fi < 0) {
        let nd2: i32 = pipeline_dep_ctx_ndep(dp);
        let di2: i32 = 0;
        while (di2 < nd2) {
          let rm: *u8 = pipeline_dep_ctx_module_at(dp, di2);
          if (rm != 0 as *u8) {
            let ra3: *u8 = pipeline_dep_ctx_arena_at(dp, di2);
            if (ra3 == 0 as *u8) { ra3 = arena; }
            let cand: i32 = glue_asm_score_import_binding_func_ix_c(
              arena, expr_ref, rm, ra3, field_name, field_len, want_np, is_method, 0 as *i32
            );
            if (cand >= 0) {
              res_mod = rm;
              res_arena = ra3;
              use_fi = cand;
              break;
            }
          }
          di2 = di2 + 1;
        }
      }
      if (res_mod != 0 as *u8) {
        if (use_fi >= 0) {
          if (use_fi < pipeline_module_num_funcs(res_mod)) {
            mid_len = glue_asm_build_func_overload_mid_c(res_mod, res_arena, use_fi, &mid[0], 64);
            if (mid_len > 0) {
              sym_len = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, &mid[0], mid_len, sym_flat);
              if (sym_len <= 0) { mid_len = 0 - 1; }
            }
          }
        }
      }
    }
    // Caller-arg mid only when formal failed AND name is overloaded on a known res_mod.
    if (sym_len <= 0) {
      if (res_mod != 0 as *u8) {
        if (glue_module_func_overload_count_c(res_mod, field_name, field_len) > 1) {
          let alen: i32 = 0;
          if (field_len < 64) {
            let ci: i32 = 0;
            while (ci < field_len) {
              mid[ci] = field_name[ci];
              ci = ci + 1;
            }
            alen = field_len;
          }
          let pi: i32 = 0;
          while (pi < want_np) {
            if (alen >= 60) { break; }
            let arg_ref: i32 = 0;
            if (is_method != 0) {
              arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, pi);
            } else {
              arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, pi);
            }
            let arg_ty: i32 = 0;
            if (arg_ref > 0) {
              arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
            }
            if (arg_ty > 0) {
              let suf: u8[64] = [];
              let sl: i32 = glue_asm_type_ref_to_suffix_c(arena, arg_ty, &suf[0], 64);
              if (sl > 0) {
                if (alen + 1 + sl < 64) {
                  mid[alen] = 95;
                  alen = alen + 1;
                  let si: i32 = 0;
                  while (si < sl) {
                    mid[alen] = suf[si];
                    alen = alen + 1;
                    si = si + 1;
                  }
                }
              }
            }
            pi = pi + 1;
          }
          if (alen > field_len) {
            let pos: i32 = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, &mid[0], alen, sym_flat);
            if (pos > 0) { sym_len = pos; }
          }
        }
      }
    }
    if (sym_len <= 0) {
      sym_len = glue_asm_build_import_binding_call_sym(pre_buf, pre_len, field_name, field_len, sym_flat);
    }
    return sym_len;
  }
  return 0 - 1;
}

/** Exported function `glue_asm_import_path_slice_equal`.
 * Implements `glue_asm_import_path_slice_equal`.
 * @param mod *u8
 * @param ix i32
 * @param off i32
 * @param slen i32
 * @param nm *u8
 * @param nm_len i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_import_path_slice_equal(mod: *u8, ix: i32, off: i32, slen: i32, nm: *u8, nm_len: i32): i32 {
  if (slen != nm_len) { return 0; }
  if (slen <= 0) { return 0; }
  if (nm == 0) { return 0; }
  let i: i32 = 0;
  while (i < slen) {
    unsafe {
      let b: u8 = pipeline_module_import_path_byte_at(mod, ix, off + i);
      if (b != nm[i]) { return 0; }
    }
    i = i + 1;
  }
  return 1;
}

/** Exported function `glue_asm_import_binding_name_equal`.
 * Implements `glue_asm_import_binding_name_equal`.
 * @param mod *u8
 * @param ix i32
 * @param nm *u8
 * @param nlen i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_import_binding_name_equal(mod: *u8, ix: i32, nm: *u8, nlen: i32): i32 {
  if (nm == 0) { return 0; }
  if (nlen <= 0) { return 0; }
  unsafe {
    let bl: i32 = pipeline_module_import_binding_name_len(mod, ix);
    if (bl != nlen) { return 0; }
    let i: i32 = 0;
    while (i < nlen) {
      let b: u8 = pipeline_module_import_binding_name_byte_at(mod, ix, i);
      if (b != nm[i]) { return 0; }
      i = i + 1;
    }
  }
  return 1;
}

/**
 * Count stack words for SysV x86 call args (after GP/XMM registers are full).
 * wave214: dual-GP units + MEMORY multi-word (wave601). Prior pure always used 1 unit.
 * @param arena *u8 — AST arena
 * @param call i32 — CALL expr ref
 * @param nargs i32 — argument count
 * @return i32 — stack word count
 * PLATFORM: LINUX+MACOS x86_64 SysV.
 */
#[no_mangle]
export function glue_sysv_x86_call_n_stack_c(arena: *u8, call: i32, nargs: i32): i32 {
  let gp: i32 = 0;
  let xmm: i32 = 0;
  let stk: i32 = 0;
  let j: i32 = 0;
  while (j < nargs) {
    let pty: i32 = glue_call_param_type_ref_at(arena, call, j);
    let arg_ref: i32 = pipeline_expr_call_arg_ref(arena, call, j);
    let sz: i32 = glue_sysv_arg_byte_size_c(arena, 0 as *u8, pty, arg_ref);
    let units: i32 = glue_sysv_arg_gp_units_from_size_c(sz);
    let words: i32 = glue_sysv_arg_stack_words_c(sz, units);
    if (glue_call_param_is_f32_c(arena, pty) != 0) {
      if (xmm < 8) { xmm = xmm + 1; }
      else { stk = stk + 1; }
    } else {
      if (glue_sysv_arg_is_memory_by_value_c(sz) != 0) {
        stk = stk + words;
      } else {
        if (units > 0) {
          if (gp + units <= 6) { gp = gp + units; }
          else { stk = stk + words; }
        } else {
          stk = stk + words;
        }
      }
    }
    j = j + 1;
  }
  return stk;
}

// See implementation.
// glue_asm_string_lit_len: see function docblock below.

/** Exported function `glue_asm_string_lit_len`.
 * Query helper `glue_asm_string_lit_len`.
 * @param arena *u8
 * @param er i32
 * @return i32
 */
#[no_mangle]
export function glue_asm_string_lit_len(arena: *u8, er: i32): i32 {
  if (arena == 0 as *u8) { return 0; }
  if (er <= 0) { return 0; }
  unsafe {
    let k: i32 = pipeline_expr_kind_ord_at(arena, er);
    // GLUE_EXPR_STRING_LIT_ORD = 59
    if (k != 59) { return 0; }
    return pipeline_expr_var_name_len_for_string_lit_c(arena, er);
  }
  return 0;
}

/** Exported function `glue_asm_build_import_binding_call_sym`.
 * Implements `glue_asm_build_import_binding_call_sym`.
 * @param pre *u8
 * @param plen i32
 * @param field *u8
 * @param flen i32
 * @param out *u8
 * @return i32
 */
#[no_mangle]
export function glue_asm_build_import_binding_call_sym(pre: *u8, plen: i32, field: *u8, flen: i32, out: *u8): i32 {
  if (out == 0 as *u8) { return 0 - 1; }
  let pos: i32 = 0;
  let skip_pre: i32 = 0;
  if (plen > 0) {
    if (glue_asm_c_prefix_redundant_with_name(pre, plen, field, flen) != 0) {
      skip_pre = 1;
    }
  }
  if (skip_pre == 0) {
    if (plen > 0) {
      let pi: i32 = 0;
      while (pi < plen) {
        if (pos >= 63) { break; }
        out[pos] = pre[pi];
        pos = pos + 1;
        pi = pi + 1;
      }
    }
  }
  let pi2: i32 = 0;
  while (pi2 < flen) {
    if (pos >= 63) { break; }
    out[pos] = field[pi2];
    pos = pos + 1;
    pi2 = pi2 + 1;
  }
  if (pos > 0) { return pos; }
  return 0 - 1;
}

/** Exported function `glue_call_param_type_ref_at`.
 * Implements `glue_call_param_type_ref_at`.
 * @param arena *u8
 * @param call i32
 * @param pix i32
 * @return i32
 */
#[no_mangle]
export function glue_call_param_type_ref_at(arena: *u8, call: i32, pix: i32): i32 {
  unsafe {
    return pipeline_asm_call_param_type_ref_at_c(arena, call, pix);
  }
  return 0;
}

// glue_try_std_string_xlang_redirect_sym_local: see function docblock below.

/** Exported function `glue_try_std_string_xlang_redirect_sym_local`.
 * Implements `glue_try_std_string_xlang_redirect_sym_local`.
 * @param name *u8
 * @param nlen i32
 * @param out *u8
 * @param cap i32
 * @return i32
 */
#[no_mangle]
export function glue_try_std_string_xlang_redirect_sym_local(name: *u8, nlen: i32, out: *u8, cap: i32): i32 {
  if (name == 0 as *u8) { return 0; }
  if (nlen <= 11) { return 0; }
  if (out == 0 as *u8) { return 0; }
  if (cap <= 0) { return 0; }
  // "std_string_"
  if (name[0]!=115||name[1]!=116||name[2]!=100||name[3]!=95||name[4]!=115||name[5]!=116
      ||name[6]!=114||name[7]!=105||name[8]!=110||name[9]!=103||name[10]!=95) {
    return 0;
  }
  let suffix_len: i32 = nlen - 11;
  if (suffix_len < 12) { return 0; }
  // "xlang_string_"
  if (name[11]!=115||name[12]!=104||name[13]!=117||name[14]!=120||name[15]!=95
      ||name[16]!=115||name[17]!=116||name[18]!=114||name[19]!=105||name[20]!=110
      ||name[21]!=103||name[22]!=95) {
    return 0;
  }
  if (suffix_len + 1 > cap) { return 0; }
  let i: i32 = 0;
  while (i < suffix_len) {
    out[i] = name[11 + i];
    i = i + 1;
  }
  return suffix_len;
}

/** Exported function `glue_try_std_encoding_redirect_sym_local`.
 * Implements `glue_try_std_encoding_redirect_sym_local`.
 * @param name *u8
 * @param nlen i32
 * @param out *u8
 * @param cap i32
 * @return i32
 */
#[no_mangle]
export function glue_try_std_encoding_redirect_sym_local(name: *u8, nlen: i32, out: *u8, cap: i32): i32 {
  if (name == 0 as *u8) { return 0; }
  if (out == 0 as *u8) { return 0; }
  if (cap <= 0) { return 0; }
  let prefix_len: i32 = 13; // "std_encoding_"
  if (nlen <= prefix_len) { return 0; }
  // std_encoding_
  if (name[0]!=115||name[1]!=116||name[2]!=100||name[3]!=95||name[4]!=101||name[5]!=110
      ||name[6]!=99||name[7]!=111||name[8]!=100||name[9]!=105||name[10]!=110||name[11]!=103
      ||name[12]!=95) {
    return 0;
  }
  let suffix_len: i32 = nlen - prefix_len;
  if (suffix_len <= 0) { return 0; }
  let out_len: i32 = 9 + suffix_len + 2; // encoding_ + suffix + _c
  if (out_len >= cap) { return 0; }
  // encoding_
  out[0]=101; out[1]=110; out[2]=99; out[3]=111; out[4]=100; out[5]=105; out[6]=110; out[7]=103; out[8]=95;
  let i: i32 = 0;
  while (i < suffix_len) {
    out[9 + i] = name[prefix_len + i];
    i = i + 1;
  }
  out[9 + suffix_len] = 95;
  out[9 + suffix_len + 1] = 99;
  return out_len;
}

// glue_try_std_heap_redirect_sym_local: see function docblock below.

/** Exported function `glue_try_std_heap_redirect_sym_local`.
 * Implements `glue_try_std_heap_redirect_sym_local`.
 * @param name *u8
 * @param nlen i32
 * @param out *u8
 * @param cap i32
 * @return i32
 */
#[no_mangle]
export function glue_try_std_heap_redirect_sym_local(name: *u8, nlen: i32, out: *u8, cap: i32): i32 {
  if (name == 0 as *u8) { return 0; }
  if (nlen <= 0) { return 0; }
  if (out == 0 as *u8) { return 0; }
  if (cap <= 0) { return 0; }
  if (nlen == 5) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99) {
      if (12 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 99;
      return 12;
    }
  }
  /* bare realloc (7) / free (4) removed: collide with libc FFI in heap.libc co-emit.
   * PLATFORM: SHARED — typed free_*/realloc_* rows below; seed table same (G.7). */
  if (nlen == 9) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 105;
      out[12] = 51;
      out[13] = 50;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 21) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50 && name[9]==95 && name[10]==114 && name[11]==101 && name[12]==116 && name[13]==95 && name[14]==105 && name[15]==51 && name[16]==50 && name[17]==95 && name[18]==112 && name[19]==116 && name[20]==114) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 105;
      out[12] = 51;
      out[13] = 50;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 20) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50 && name[9]==95 && name[10]==114 && name[11]==101 && name[12]==116 && name[13]==95 && name[14]==117 && name[15]==56 && name[16]==95 && name[17]==112 && name[18]==116 && name[19]==114) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 117;
      out[12] = 56;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 21) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50 && name[9]==95 && name[10]==114 && name[11]==101 && name[12]==116 && name[13]==95 && name[14]==117 && name[15]==54 && name[16]==52 && name[17]==95 && name[18]==112 && name[19]==116 && name[20]==114) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 117;
      out[12] = 54;
      out[13] = 52;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 21) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50 && name[9]==95 && name[10]==114 && name[11]==101 && name[12]==116 && name[13]==95 && name[14]==102 && name[15]==54 && name[16]==52 && name[17]==95 && name[18]==112 && name[19]==116 && name[20]==114) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 102;
      out[12] = 54;
      out[13] = 52;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 21) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==105 && name[7]==51 && name[8]==50 && name[9]==95 && name[10]==114 && name[11]==101 && name[12]==116 && name[13]==95 && name[14]==102 && name[15]==51 && name[16]==50 && name[17]==95 && name[18]==112 && name[19]==116 && name[20]==114) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 102;
      out[12] = 51;
      out[13] = 50;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 11) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==105 && name[9]==51 && name[10]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 105;
      out[14] = 51;
      out[15] = 50;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 23) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==105 && name[9]==51 && name[10]==50 && name[11]==95 && name[12]==114 && name[13]==101 && name[14]==116 && name[15]==95 && name[16]==105 && name[17]==51 && name[18]==50 && name[19]==95 && name[20]==112 && name[21]==116 && name[22]==114) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 105;
      out[14] = 51;
      out[15] = 50;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 23) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==117 && name[9]==54 && name[10]==52 && name[11]==95 && name[12]==114 && name[13]==101 && name[14]==116 && name[15]==95 && name[16]==117 && name[17]==54 && name[18]==52 && name[19]==95 && name[20]==112 && name[21]==116 && name[22]==114) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 117;
      out[14] = 54;
      out[15] = 52;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 23) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==102 && name[9]==54 && name[10]==52 && name[11]==95 && name[12]==114 && name[13]==101 && name[14]==116 && name[15]==95 && name[16]==102 && name[17]==54 && name[18]==52 && name[19]==95 && name[20]==112 && name[21]==116 && name[22]==114) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 102;
      out[14] = 54;
      out[15] = 52;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 23) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==102 && name[9]==51 && name[10]==50 && name[11]==95 && name[12]==114 && name[13]==101 && name[14]==116 && name[15]==95 && name[16]==102 && name[17]==51 && name[18]==50 && name[19]==95 && name[20]==112 && name[21]==116 && name[22]==114) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 102;
      out[14] = 51;
      out[15] = 50;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 21) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==117 && name[9]==56 && name[10]==95 && name[11]==114 && name[12]==101 && name[13]==116 && name[14]==95 && name[15]==117 && name[16]==56 && name[17]==95 && name[18]==112 && name[19]==116 && name[20]==114) {
      if (17 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 117;
      out[14] = 56;
      out[15] = 95;
      out[16] = 99;
      return 17;
    }
  }
  if (nlen == 8) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==105 && name[6]==51 && name[7]==50) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 105;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 12) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==105 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 105;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 12) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==117 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 117;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 12) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==102 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 102;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 12) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==102 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 102;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 8) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==117 && name[7]==56) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 117;
      out[12] = 56;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 10) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==117 && name[9]==56) {
      if (17 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 117;
      out[14] = 56;
      out[15] = 95;
      out[16] = 99;
      return 17;
    }
  }
  if (nlen == 7) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==117 && name[6]==56) {
      if (14 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 117;
      out[11] = 56;
      out[12] = 95;
      out[13] = 99;
      return 14;
    }
  }
  if (nlen == 9) {
    if (name[0]==97 && name[1]==108 && name[2]==108 && name[3]==111 && name[4]==99 && name[5]==95 && name[6]==102 && name[7]==51 && name[8]==50) {
      if (16 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 108;
      out[7] = 108;
      out[8] = 111;
      out[9] = 99;
      out[10] = 95;
      out[11] = 102;
      out[12] = 51;
      out[13] = 50;
      out[14] = 95;
      out[15] = 99;
      return 16;
    }
  }
  if (nlen == 11) {
    if (name[0]==114 && name[1]==101 && name[2]==97 && name[3]==108 && name[4]==108 && name[5]==111 && name[6]==99 && name[7]==95 && name[8]==102 && name[9]==51 && name[10]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 114;
      out[6] = 101;
      out[7] = 97;
      out[8] = 108;
      out[9] = 108;
      out[10] = 111;
      out[11] = 99;
      out[12] = 95;
      out[13] = 102;
      out[14] = 51;
      out[15] = 50;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 8) {
    if (name[0]==102 && name[1]==114 && name[2]==101 && name[3]==101 && name[4]==95 && name[5]==102 && name[6]==51 && name[7]==50) {
      if (15 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 102;
      out[6] = 114;
      out[7] = 101;
      out[8] = 101;
      out[9] = 95;
      out[10] = 102;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 99;
      return 15;
    }
  }
  if (nlen == 11) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==105 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==97 && name[10]==116) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 105;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 10) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==117 && name[6]==56 && name[7]==95 && name[8]==97 && name[9]==116) {
      if (17 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 117;
      out[11] = 56;
      out[12] = 95;
      out[13] = 97;
      out[14] = 116;
      out[15] = 95;
      out[16] = 99;
      return 17;
    }
  }
  if (nlen == 11) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==102 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==97 && name[10]==116) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 102;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 11) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==117 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==97 && name[10]==116) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 117;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 11) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==102 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==97 && name[10]==116) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 102;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 28) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==105 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114 && name[12]==95 && name[13]==105 && name[14]==51 && name[15]==50 && name[16]==95 && name[17]==105 && name[18]==51 && name[19]==50 && name[20]==95 && name[21]==112 && name[22]==116 && name[23]==114 && name[24]==95 && name[25]==105 && name[26]==51 && name[27]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 105;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 26) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==117 && name[6]==56 && name[7]==95 && name[8]==112 && name[9]==116 && name[10]==114 && name[11]==95 && name[12]==105 && name[13]==51 && name[14]==50 && name[15]==95 && name[16]==117 && name[17]==56 && name[18]==95 && name[19]==112 && name[20]==116 && name[21]==114 && name[22]==95 && name[23]==105 && name[24]==51 && name[25]==50) {
      if (17 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 117;
      out[11] = 56;
      out[12] = 95;
      out[13] = 97;
      out[14] = 116;
      out[15] = 95;
      out[16] = 99;
      return 17;
    }
  }
  if (nlen == 28) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==102 && name[6]==51 && name[7]==50 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114 && name[12]==95 && name[13]==105 && name[14]==51 && name[15]==50 && name[16]==95 && name[17]==102 && name[18]==51 && name[19]==50 && name[20]==95 && name[21]==112 && name[22]==116 && name[23]==114 && name[24]==95 && name[25]==105 && name[26]==51 && name[27]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 102;
      out[11] = 51;
      out[12] = 50;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 28) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==117 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114 && name[12]==95 && name[13]==105 && name[14]==51 && name[15]==50 && name[16]==95 && name[17]==117 && name[18]==54 && name[19]==52 && name[20]==95 && name[21]==112 && name[22]==116 && name[23]==114 && name[24]==95 && name[25]==105 && name[26]==51 && name[27]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 117;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 28) {
    if (name[0]==99 && name[1]==111 && name[2]==112 && name[3]==121 && name[4]==95 && name[5]==102 && name[6]==54 && name[7]==52 && name[8]==95 && name[9]==112 && name[10]==116 && name[11]==114 && name[12]==95 && name[13]==105 && name[14]==51 && name[15]==50 && name[16]==95 && name[17]==102 && name[18]==54 && name[19]==52 && name[20]==95 && name[21]==112 && name[22]==116 && name[23]==114 && name[24]==95 && name[25]==105 && name[26]==51 && name[27]==50) {
      if (18 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 99;
      out[6] = 111;
      out[7] = 112;
      out[8] = 121;
      out[9] = 95;
      out[10] = 102;
      out[11] = 54;
      out[12] = 52;
      out[13] = 95;
      out[14] = 97;
      out[15] = 116;
      out[16] = 95;
      out[17] = 99;
      return 18;
    }
  }
  if (nlen == 12) {
    if (name[0]==97 && name[1]==114 && name[2]==101 && name[3]==110 && name[4]==97 && name[5]==54 && name[6]==52 && name[7]==95 && name[8]==105 && name[9]==110 && name[10]==105 && name[11]==116) {
      if (19 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 114;
      out[7] = 101;
      out[8] = 110;
      out[9] = 97;
      out[10] = 54;
      out[11] = 52;
      out[12] = 95;
      out[13] = 105;
      out[14] = 110;
      out[15] = 105;
      out[16] = 116;
      out[17] = 95;
      out[18] = 99;
      return 19;
    }
  }
  if (nlen == 13) {
    if (name[0]==97 && name[1]==114 && name[2]==101 && name[3]==110 && name[4]==97 && name[5]==54 && name[6]==52 && name[7]==95 && name[8]==97 && name[9]==108 && name[10]==108 && name[11]==111 && name[12]==99) {
      if (20 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 114;
      out[7] = 101;
      out[8] = 110;
      out[9] = 97;
      out[10] = 54;
      out[11] = 52;
      out[12] = 95;
      out[13] = 97;
      out[14] = 108;
      out[15] = 108;
      out[16] = 111;
      out[17] = 99;
      out[18] = 95;
      out[19] = 99;
      return 20;
    }
  }
  if (nlen == 14) {
    if (name[0]==97 && name[1]==114 && name[2]==101 && name[3]==110 && name[4]==97 && name[5]==54 && name[6]==52 && name[7]==95 && name[8]==100 && name[9]==101 && name[10]==105 && name[11]==110 && name[12]==105 && name[13]==116) {
      if (21 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 97;
      out[6] = 114;
      out[7] = 101;
      out[8] = 110;
      out[9] = 97;
      out[10] = 54;
      out[11] = 52;
      out[12] = 95;
      out[13] = 100;
      out[14] = 101;
      out[15] = 105;
      out[16] = 110;
      out[17] = 105;
      out[18] = 116;
      out[19] = 95;
      out[20] = 99;
      return 21;
    }
  }
  if (nlen == 7) {
    if (name[0]==112 && name[1]==116 && name[2]==114 && name[3]==95 && name[4]==109 && name[5]==111 && name[6]==100) {
      if (14 + 1 > cap) { return 0; }
      out[0] = 104;
      out[1] = 101;
      out[2] = 97;
      out[3] = 112;
      out[4] = 95;
      out[5] = 112;
      out[6] = 116;
      out[7] = 114;
      out[8] = 95;
      out[9] = 109;
      out[10] = 111;
      out[11] = 100;
      out[12] = 95;
      out[13] = 99;
      return 14;
    }
  }
  return 0;
}

// ===========================================================================
// F7: asm backend native vtable statics + wrapper function emission.
// Moved from backend_vtable_emit.x (merged here to reuse existing seed/build).
// PLATFORM: SHARED — mirrors codegen.x vtable naming (G.7 single authority).
// ===========================================================================

export extern function xlang_skip_impl_seen_count_c(): i32;
export extern function xlang_skip_impl_trait_name_into_c(si: i32, out64: *u8): i32;
export extern function xlang_skip_impl_for_type_into_c(si: i32, out_kind: *i32,
        out_is_ptr: *i32, out_name64: *u8, out_nlen_ptr: *i32): i32;
export extern function xlang_skip_trait_method_count_c(trait_nm: *u8, trait_nlen: i32): i32;
export extern function xlang_skip_trait_method_name_into_c(trait_nm: *u8, trait_nlen: i32,
        slot_i: i32, out: *u8): i32;
export extern function codegen_find_impl_method_for_type(module: *u8, arena: *u8,
        method_name: *u8, method_name_len: i32, receiver_type_ref: i32): i32;
export extern function codegen_builtin_type_name_into(kind_ord: i32, out: *u8): i32;
export extern function pipeline_type_find_or_alloc_named(arena: *u8, name: *u8, nlen: i32): i32;
export extern function pipeline_type_find_or_alloc_compound(arena: *u8, kind_ord: i32,
        elem_ref: i32, asz: i32): i32;
export extern function pipeline_elf_ctx_add_label(ctx: *u8, name: *u8, name_len: i32, offset: i32): i32;
export extern function pipeline_elf_ctx_add_sym(ctx: *u8, name: *u8, name_len: i32, offset: i32): i32;
export extern function pipeline_elf_ctx_append_reloc(ctx: *u8, offset: i32, name: *u8, name_len: i32): i32;
export extern function pipeline_elf_ctx_append_reloc_absolute64(ctx: *u8, offset: i32, name: *u8, name_len: i32): i32;
export extern function pipeline_elf_ctx_emit_code_len(ctx: *u8): i32;
/* F7: data section helpers for vtable static data (__DATA,__const). */
export extern function pipeline_elf_ctx_emit_data_len(ctx: *u8): i32;
export extern function pipeline_elf_ctx_append_data_u32_le(ctx: *u8, word: u32): i32;
export extern function pipeline_elf_ctx_set_shndx_override(ctx: *u8, shndx: i32): void;
export extern function backend_enc_prologue_arch(elf_ctx: *u8, frame_sz: i32, ta: i32): i32;
export extern function backend_enc_epilogue_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_append_u32_le_c(elf_ctx: *u8, word: u32): i32;

/**
 * Build the canonical vtable static name `xlang_vtable_<Trait>_for_[Ptr_]<Type>`.
 * G.7 single authority — byte sequence MUST match codegen_emit_vtable_static_name.
 * PLATFORM: SHARED — G.7 naming authority twin.
 */
#[no_mangle]
export function pipeline_asm_emit_vtable_static_name_into(trait_nm: *u8, trait_nlen: i32,
        for_nm: *u8, for_nlen: i32, is_ptr: i32, out: *u8): i32 {
  if (trait_nm == 0 as *u8 || for_nm == 0 as *u8 || out == 0 as *u8) { return 0 - 1; }
  if (trait_nlen <= 0 || for_nlen <= 0) { return 0 - 1; }
  if (trait_nlen > 64 || for_nlen > 64) { return 0 - 1; }
  unsafe {
    let w: i32 = 0;
    let stem: u8[13] = [120, 108, 97, 110, 103, 95, 118, 116, 97, 98, 108, 101, 95];
    let k: i32 = 0;
    while (k < 13) { out[w] = stem[k]; w = w + 1; k = k + 1; }
    let ti: i32 = 0;
    while (ti < trait_nlen) {
      let b: u8 = trait_nm[ti];
      if (b == 95) { out[w] = b; }
      else if (b >= 48 && b <= 57) { out[w] = b; }
      else if (b >= 65 && b <= 90) { out[w] = b; }
      else if (b >= 97 && b <= 122) { out[w] = b; }
      else { out[w] = 95; }
      w = w + 1; ti = ti + 1;
    }
    let fk: u8[5] = [95, 102, 111, 114, 95];
    k = 0;
    while (k < 5) { out[w] = fk[k]; w = w + 1; k = k + 1; }
    if (is_ptr != 0) {
      let pk: u8[4] = [80, 116, 114, 95];
      k = 0;
      while (k < 4) { out[w] = pk[k]; w = w + 1; k = k + 1; }
    }
    let fi: i32 = 0;
    while (fi < for_nlen) {
      let b: u8 = for_nm[fi];
      if (b == 95) { out[w] = b; }
      else if (b >= 48 && b <= 57) { out[w] = b; }
      else if (b >= 65 && b <= 90) { out[w] = b; }
      else if (b >= 97 && b <= 122) { out[w] = b; }
      else { out[w] = 95; }
      w = w + 1; fi = fi + 1;
    }
    return w;
  }
}

/**
 * Build the canonical wrapper name `xlang_vtable_wrap_<Trait>_for_[Ptr_]<Type>_<slot>`.
 * G.7 single authority — byte sequence MUST match codegen_emit_vtable_wrapper_name.
 * PLATFORM: SHARED — G.7 naming authority twin.
 */
#[no_mangle]
export function pipeline_asm_emit_vtable_wrapper_name_into(trait_nm: *u8, trait_nlen: i32,
        for_nm: *u8, for_nlen: i32, is_ptr: i32, slot_i: i32, out: *u8): i32 {
  if (trait_nm == 0 as *u8 || for_nm == 0 as *u8 || out == 0 as *u8) { return 0 - 1; }
  if (trait_nlen <= 0 || for_nlen <= 0) { return 0 - 1; }
  if (trait_nlen > 64 || for_nlen > 64) { return 0 - 1; }
  if (slot_i < 0) { return 0 - 1; }
  unsafe {
    let w: i32 = 0;
    let stem: u8[18] = [120, 108, 97, 110, 103, 95, 118, 116, 97, 98, 108, 101, 95, 119, 114, 97, 112, 95];
    let k: i32 = 0;
    while (k < 18) { out[w] = stem[k]; w = w + 1; k = k + 1; }
    let ti: i32 = 0;
    while (ti < trait_nlen) {
      let b: u8 = trait_nm[ti];
      if (b == 95) { out[w] = b; }
      else if (b >= 48 && b <= 57) { out[w] = b; }
      else if (b >= 65 && b <= 90) { out[w] = b; }
      else if (b >= 97 && b <= 122) { out[w] = b; }
      else { out[w] = 95; }
      w = w + 1; ti = ti + 1;
    }
    let fk: u8[5] = [95, 102, 111, 114, 95];
    k = 0;
    while (k < 5) { out[w] = fk[k]; w = w + 1; k = k + 1; }
    if (is_ptr != 0) {
      let pk: u8[4] = [80, 116, 114, 95];
      k = 0;
      while (k < 4) { out[w] = pk[k]; w = w + 1; k = k + 1; }
    }
    let fi: i32 = 0;
    while (fi < for_nlen) {
      let b: u8 = for_nm[fi];
      if (b == 95) { out[w] = b; }
      else if (b >= 48 && b <= 57) { out[w] = b; }
      else if (b >= 65 && b <= 90) { out[w] = b; }
      else if (b >= 97 && b <= 122) { out[w] = b; }
      else { out[w] = 95; }
      w = w + 1; fi = fi + 1;
    }
    out[w] = 95; w = w + 1;
    if (slot_i == 0) {
      out[w] = 48; w = w + 1;
    } else {
      let tmp: u8[10] = [];
      let n: i32 = 0;
      let v: i32 = slot_i;
      while (v > 0 && n < 10) {
        tmp[n] = (48 as u8) + ((v % 10) as u8);
        v = v / 10;
        n = n + 1;
      }
      let j: i32 = n - 1;
      while (j >= 0) { out[w] = tmp[j]; w = w + 1; j = j - 1; }
    }
    return w;
  }
}

/**
 * Emit a single wrapper function for (impl Trait for Type, method slot).
 * Wrapper body: prologue(16) + optional ldr x0,[x0] (by-value deref)
 * + copy incoming stack extras onto the impl outgoing stack + bl <impl> + epilogue.
 * First incoming arg stays data (rdi/x0). Stack extras do not pass through a
 * nested `call` unless copied (prologue+ret shift [rbp+16]).
 * ARM64 leftover: load_x29_pos writes x0 (rax and arg0). Save remapped self
 * at [x29,#24] (prologue(16) pad after x19 at #16) before the copy, restore
 * after. x86 rdi is not rax — no save. Do not use mov_rax_to_rbx (also
 * writes x1 = extra a).
 * PLATFORM: SHARED — G.7 twin of codegen_emit_vtable_wrapper_def.
 */
#[no_mangle]
export function pipeline_asm_emit_vtable_wrapper_def(elf_ctx: *u8, ta: i32, module: *u8,
        arena: *u8, trait_nm: *u8, trait_nlen: i32, for_nm: *u8, for_nlen: i32,
        for_ptr: i32, slot_i: i32, recv_rt: i32): i32 {
  if (elf_ctx == 0 as *u8 || module == 0 as *u8 || arena == 0 as *u8) { return 0 - 1; }
  if (trait_nm == 0 as *u8 || for_nm == 0 as *u8) { return 0 - 1; }
  if (trait_nlen <= 0 || for_nlen <= 0 || slot_i < 0) { return 0 - 1; }
  unsafe {
    let meth_nm: u8[64] = [];
    let meth_nlen: i32 = xlang_skip_trait_method_name_into_c(trait_nm, trait_nlen,
            slot_i, &meth_nm[0]);
    if (meth_nlen <= 0) { return 0; }
    let impl_fi: i32 = codegen_find_impl_method_for_type(module, arena,
            &meth_nm[0], meth_nlen, recv_rt);
    if (impl_fi < 0) { return 0; }
    /* Keep the impl in WPO emit-order: dyn wrappers are not call-graph edges. */
    pipeline_module_func_set_is_used(module, impl_fi, 1);
    /* Link name (overload suffix clone_A / clone_B), not the source name. */
    let impl_nm: u8[128] = [];
    let impl_nlen: i32 = glue_asm_build_func_export_sym_c(module, arena, impl_fi, &impl_nm[0], 128);
    if (impl_nlen <= 0) { return 0 - 1; }
    let wrap_nm: u8[168] = [];
    let wrap_nlen: i32 = pipeline_asm_emit_vtable_wrapper_name_into(trait_nm, trait_nlen,
            for_nm, for_nlen, for_ptr, slot_i, &wrap_nm[0]);
    if (wrap_nlen <= 0) { return 0 - 1; }
    let macho: i32 = pipeline_elf_ctx_macho_leading_underscore(elf_ctx);
    let sym_nm: u8[170] = [];
    let sym_nlen: i32 = wrap_nlen;
    if (macho != 0) {
      sym_nm[0] = 95;
      let k: i32 = 0;
      while (k < wrap_nlen && k < 168) { sym_nm[k + 1] = wrap_nm[k]; k = k + 1; }
      sym_nlen = wrap_nlen + 1;
    } else {
      let k: i32 = 0;
      while (k < wrap_nlen && k < 169) { sym_nm[k] = wrap_nm[k]; k = k + 1; }
    }
    let entry_off: i32 = pipeline_elf_ctx_emit_code_len(elf_ctx);
    if (entry_off < 0) { return 0 - 1; }
    if (pipeline_elf_ctx_add_label(elf_ctx, &sym_nm[0], sym_nlen, entry_off) != 0) {
      return 0 - 1;
    }
    if (pipeline_elf_ctx_add_sym(elf_ctx, &sym_nm[0], sym_nlen, entry_off) != 0) {
      return 0 - 1;
    }
    if (backend_enc_prologue_arch(elf_ctx, 16, ta) != 0) { return 0 - 1; }
    if (for_ptr == 0) {
      if (backend_enc_ldr_xreg_xreg_imm_arch(elf_ctx, 0, 0, 0, ta) != 0) {
        return 0 - 1;
      }
      /* By-value deref left the payload in rax; SysV impl expects rdi. */
      if (ta == 0) {
        if (backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
      }
    }
    /*
     * Copy incoming stack extras to the impl outgoing stack.
     * nparams includes self (already remapped in rdi/x0). GP file is
     * glue_asm_call_reg_max: overflow extras live at [rbp+16] (x86) or
     * [x29,#32] after prologue(16) on ARM64 (align 16 + x19 slot).
     * PLATFORM: LINUX x86_64 SysV · MACOS|ARM64 AAPCS64.
     */
    let nparams_w: i32 = pipeline_module_func_num_params_at(module, impl_fi);
    let reg_max_w: i32 = glue_asm_call_reg_max(ta);
    if (reg_max_w < 2) { reg_max_w = 6; }
    let n_stk_w: i32 = 0;
    if (nparams_w > reg_max_w) { n_stk_w = nparams_w - reg_max_w; }
    let stk_bytes_w: i32 = 0;
    if (n_stk_w > 0) {
      if (ta == 0) {
        if ((n_stk_w & 1) != 0) {
          if (backend_enc_mov_imm32_to_w0_arch(elf_ctx, 0, ta) != 0) { return 0 - 1; }
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
          stk_bytes_w = stk_bytes_w + 8;
        }
        let si_w: i32 = n_stk_w - 1;
        while (si_w >= 0) {
          if (backend_enc_load_rbp_pos_to_rax_arch(elf_ctx, 16 + si_w * 8, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_push_rax_arch(elf_ctx, ta) != 0) { return 0 - 1; }
          stk_bytes_w = stk_bytes_w + 8;
          si_w = si_w - 1;
        }
      } else {
        /*
         * PLATFORM: MACOS|ARM64 — x0 is both the load temp and impl arg0.
         * store [sp,#24] before reserve (sp==x29); restore via [x29,#24]
         * after copy. Slot 24 is the unused half of the x19 16B pad.
         * G.7: complete this wrapper (no second dispatcher / no x1 scratch).
         */
        if (backend_enc_store_x0_sp_offset_arch(elf_ctx, 24, ta) != 0) {
          return 0 - 1;
        }
        stk_bytes_w = n_stk_w * 8;
        stk_bytes_w = (stk_bytes_w + 15) & (0 - 16);
        if (backend_enc_call_stack_reserve_arch(elf_ctx, stk_bytes_w, ta) != 0) {
          return 0 - 1;
        }
        let si_a: i32 = 0;
        while (si_a < n_stk_w) {
          /* prologue(16) → frame 32 (aligned request + x19). */
          if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, 32 + si_a * 8, ta) != 0) {
            return 0 - 1;
          }
          if (backend_enc_store_x0_sp_offset_arch(elf_ctx, si_a * 8, ta) != 0) {
            return 0 - 1;
          }
          si_a = si_a + 1;
        }
        if (backend_enc_load_x29_pos_to_rax_arch(elf_ctx, 24, ta) != 0) {
          return 0 - 1;
        }
      }
    }
    if (backend_enc_call_arch(elf_ctx, &impl_nm[0], impl_nlen, ta) != 0) {
      return 0 - 1;
    }
    if (stk_bytes_w > 0) {
      if (backend_enc_call_stack_cleanup_arch(elf_ctx, stk_bytes_w, ta) != 0) {
        return 0 - 1;
      }
    }
    if (backend_enc_epilogue_arch(elf_ctx, ta) != 0) { return 0 - 1; }
    return 1;
  }
}

/**
 * Emit all vtable statics + wrapper functions for the current module.
 * Called from asm_compile module entry after dep SoA merge, before funcs.
 * PLATFORM: SHARED — G.7 twin of codegen_emit_module_vtable_statics.
 */
#[no_mangle]
export function pipeline_asm_emit_module_vtable_statics(elf_ctx: *u8, ta: i32, module: *u8,
        arena: *u8): i32 {
  if (elf_ctx == 0 as *u8 || module == 0 as *u8 || arena == 0 as *u8) { return 0 - 1; }
  unsafe {
    let n_impl: i32 = xlang_skip_impl_seen_count_c();
    if (n_impl <= 0) { return 0; }
    let NAMED_KIND: i32 = 8;
    let PTR_KIND: i32 = 9;
    let si: i32 = 0;
    while (si < n_impl) {
      let trait_nm: u8[64] = [];
      let trait_nlen: i32 = xlang_skip_impl_trait_name_into_c(si, &trait_nm[0]);
      if (trait_nlen <= 0) { si = si + 1; continue; }
      let for_k: i32 = 0;
      let for_ptr: i32 = 0;
      let for_nm: u8[64] = [];
      let for_nlen: i32 = 0;
      if (xlang_skip_impl_for_type_into_c(si, &for_k, &for_ptr, &for_nm[0], &for_nlen) == 0) {
        si = si + 1; continue;
      }
      let is_builtin: i32 = 0;
      if (for_nlen <= 0) {
        let blen: i32 = codegen_builtin_type_name_into(for_k, &for_nm[0]);
        if (blen <= 0) { si = si + 1; continue; }
        for_nlen = blen;
        is_builtin = 1;
      }
      let recv_rt: i32 = 0;
      if (is_builtin != 0) {
        recv_rt = pipeline_type_find_or_alloc_compound(arena, for_k, 0, 0);
      } else {
        recv_rt = pipeline_type_find_or_alloc_named(arena, &for_nm[0], for_nlen);
      }
      if (recv_rt <= 0) { si = si + 1; continue; }
      if (for_ptr != 0) {
        recv_rt = pipeline_type_find_or_alloc_compound(arena, PTR_KIND, recv_rt, 0);
        if (recv_rt <= 0) { si = si + 1; continue; }
      }
      let meth_count: i32 = xlang_skip_trait_method_count_c(&trait_nm[0], trait_nlen);
      if (meth_count <= 0) { si = si + 1; continue; }
      let has_impl: i32[64] = [];
      let wi: i32 = 0;
      while (wi < meth_count && wi < 64) {
        let rc: i32 = pipeline_asm_emit_vtable_wrapper_def(elf_ctx, ta, module, arena,
                &trait_nm[0], trait_nlen, &for_nm[0], for_nlen, for_ptr, wi, recv_rt);
        if (rc < 0) { return 0 - 1; }
        has_impl[wi] = rc;
        wi = wi + 1;
      }
      let vt_nm: u8[150] = [];
      let vt_nlen: i32 = pipeline_asm_emit_vtable_static_name_into(&trait_nm[0],
              trait_nlen, &for_nm[0], for_nlen, for_ptr, &vt_nm[0]);
      if (vt_nlen <= 0) { si = si + 1; continue; }
      let macho: i32 = pipeline_elf_ctx_macho_leading_underscore(elf_ctx);
      let vt_sym: u8[152] = [];
      let vt_sym_nlen: i32 = vt_nlen;
      if (macho != 0) {
        vt_sym[0] = 95;
        let k: i32 = 0;
        while (k < vt_nlen && k < 150) { vt_sym[k + 1] = vt_nm[k]; k = k + 1; }
        vt_sym_nlen = vt_nlen + 1;
      } else {
        let k: i32 = 0;
        while (k < vt_nlen && k < 151) { vt_sym[k] = vt_nm[k]; k = k + 1; }
      }
      /* F7: vtable static data goes to __DATA,__const section (separate from
       * __TEXT,__text which rejects absolute pointer relocations). Override the
       * current shndx so all new labels/syms/relocs are tagged as data section.
       * Single-threaded compile; restore to 0 before returning. */
      pipeline_elf_ctx_set_shndx_override(elf_ctx, 4);
      let vt_off: i32 = pipeline_elf_ctx_emit_data_len(elf_ctx);
      if (vt_off < 0) {
        pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
        return 0 - 1;
      }
      if (pipeline_elf_ctx_add_label(elf_ctx, &vt_sym[0], vt_sym_nlen, vt_off) != 0) {
        pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
        return 0 - 1;
      }
      if (pipeline_elf_ctx_add_sym(elf_ctx, &vt_sym[0], vt_sym_nlen, vt_off) != 0) {
        pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
        return 0 - 1;
      }
      let slot_i: i32 = 0;
      while (slot_i < meth_count && slot_i < 64) {
        let slot_off: i32 = pipeline_elf_ctx_emit_data_len(elf_ctx);
        if (slot_off < 0) {
          pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
          return 0 - 1;
        }
        if (pipeline_elf_ctx_append_data_u32_le(elf_ctx, (0 as u32)) != 0) {
          pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
          return 0 - 1;
        }
        if (pipeline_elf_ctx_append_data_u32_le(elf_ctx, (0 as u32)) != 0) {
          pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
          return 0 - 1;
        }
        if (has_impl[slot_i] != 0) {
          let wrap_nm: u8[168] = [];
          let wrap_nlen: i32 = pipeline_asm_emit_vtable_wrapper_name_into(&trait_nm[0],
                  trait_nlen, &for_nm[0], for_nlen, for_ptr, slot_i, &wrap_nm[0]);
          if (wrap_nlen <= 0) {
            pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
            return 0 - 1;
          }
          let wrap_sym: u8[170] = [];
          let wrap_sym_nlen: i32 = wrap_nlen;
          if (macho != 0) {
            wrap_sym[0] = 95;
            let k: i32 = 0;
            while (k < wrap_nlen && k < 168) { wrap_sym[k + 1] = wrap_nm[k]; k = k + 1; }
            wrap_sym_nlen = wrap_nlen + 1;
          } else {
            let k: i32 = 0;
            while (k < wrap_nlen && k < 169) { wrap_sym[k] = wrap_nm[k]; k = k + 1; }
          }
          if (pipeline_elf_ctx_append_reloc_absolute64(elf_ctx, slot_off,
                  &wrap_sym[0], wrap_sym_nlen) != 0) {
            pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
            return 0 - 1;
          }
        }
        slot_i = slot_i + 1;
      }
      /* F7: restore shndx override to 0 (text section) after vtable static emit. */
      pipeline_elf_ctx_set_shndx_override(elf_ctx, 0);
      si = si + 1;
    }
    return 0;
  }
}

/**
 * F7: materialize a TYPE_DYN let-init coerce as a 16-byte fat pointer.
 *   [rbp+slot]   = data  (RHS value if RHS is TYPE_PTR; else &RHS)
 *   [rbp+slot+8] = &xlang_vtable_<Trait>_for_[Ptr_]<Type>
 * Called from glue_block_body_emit_let_init when the let type is TYPE_DYN.
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — emit context
 * @param block_ref i32 — enclosing block
 * @param idx i32 — let index in the block
 * @param init_ref i32 — RHS expr
 * @param slot_off i32 — rbp-relative home of the dyn local
 * @param ctx *u8 — AsmFuncCtx
 * @param ta i32 — target arch
 * @return i32 — 1 handled, 0 not a dyn coerce (caller continues), -1 fail
 * PLATFORM: SHARED — G.7 twin of codegen_emit_dyn_vtable_close store shape.
 */
#[no_mangle]
export function pipeline_asm_try_emit_dyn_coerce_let(arena: *u8, elf_ctx: *u8,
        block_ref: i32, idx: i32, init_ref: i32, slot_off: i32, ctx: *u8, ta: i32): i32 {
  if (arena == 0 as *u8 || elf_ctx == 0 as *u8 || ctx == 0 as *u8) { return 0 - 1; }
  if (block_ref <= 0 || idx < 0 || init_ref <= 0) { return 0; }
  unsafe {
    let let_ty: i32 = pipeline_block_let_type_ref(arena, block_ref, idx);
    if (let_ty <= 0) { return 0; }
    let lt_dyn: i32 = pipeline_typeck_resolve_type_alias_ref_c(arena, let_ty);
    if (lt_dyn <= 0) { return 0; }
    if (pipeline_type_kind_ord_at(arena, lt_dyn) != 17) { return 0; }
    /* F1 null-dyn sentinel: `let x: dyn T = 0` — no vtable, keep default store. */
    if (pipeline_expr_kind_ord_at(arena, init_ref) == 0) {
      if (pipeline_expr_int_val_at(arena, init_ref) == 0) { return 0; }
    }
    let rhs_rt: i32 = pipeline_expr_resolved_type_ref(arena, init_ref);
    if (rhs_rt <= 0) { return 0 - 1; }
    let recv_kind: i32 = pipeline_type_kind_ord_at(arena, rhs_rt);
    let is_ptr: i32 = 0;
    let name_rt: i32 = rhs_rt;
    if (recv_kind == 9) {
      let elem_rt: i32 = pipeline_type_elem_ref_at(arena, rhs_rt);
      if (elem_rt > 0 && pipeline_type_kind_ord_at(arena, elem_rt) == 8) {
        is_ptr = 1;
        name_rt = elem_rt;
      }
    }
    let trait_nm: u8[64] = [];
    let trait_nlen: i32 = pipeline_type_named_name_into(arena, lt_dyn, &trait_nm[0]);
    if (trait_nlen <= 0) { return 0 - 1; }
    let for_nm: u8[64] = [];
    let for_nlen: i32 = pipeline_type_named_name_into(arena, name_rt, &for_nm[0]);
    /* F7 neighborhood / F6 twin: impl Trait for builtin (i32/i64/f32/…).
     * The impl registry keeps an empty for-type name (kind ordinal only).
     * Synthesize the canonical X name via the G.7 authority
     * codegen_builtin_type_name_into so this coerce LEAs the same static
     * that pipeline_asm_emit_module_vtable_statics already emits.
     * Do not open a second kind→name map. PLATFORM: SHARED. */
    let is_builtin: i32 = 0;
    if (for_nlen <= 0) {
      let bk: i32 = pipeline_type_kind_ord_at(arena, name_rt);
      for_nlen = codegen_builtin_type_name_into(bk, &for_nm[0]);
      if (for_nlen <= 0) { return 0 - 1; }
      is_builtin = 1;
    }
    /* Emit data pointer into rax.
     * PTR RHS: the value IS the data pointer (impl for *T).
     * NAMED by-value: LEA the local (existing F7).
     * Builtin by-value: VAR is an lvalue — LEA it. Rvalue (INT_LIT 7 in
     * dyn_builtin.x) has no address — emit to rax, spill to a fresh frame
     * slot (G.7 reuse glue_sysv_spill_rax_rdx_to_frame_c), then LEA that
     * slot. Wrapper first arg stays rdi/x0 = data; do not change that ABI.
     * EXPR_VAR ordinal is 3 (ast.x ExprKind). PLATFORM: SHARED. */
    if (is_ptr != 0) {
      if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, init_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
    } else if (is_builtin != 0) {
      let ek: i32 = pipeline_expr_kind_ord_at(arena, init_ref);
      if (ek == 3) {
        if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, init_ref, ctx, ta) != 0) {
          return 0 - 1;
        }
      } else {
        if (pipeline_asm_emit_expr_elf_rec(arena, elf_ctx, init_ref, ctx, ta) != 0) {
          return 0 - 1;
        }
        let spill: i32 = glue_sysv_spill_rax_rdx_to_frame_c(elf_ctx, ctx, ta, 1);
        if (spill < 0) { return 0 - 1; }
        if (backend_enc_lea_rbp_to_rax_arch(elf_ctx, spill, ta) != 0) {
          return 0 - 1;
        }
      }
    } else {
      if (pipeline_asm_emit_lvalue_eff_addr_elf_c(arena, elf_ctx, init_ref, ctx, ta) != 0) {
        return 0 - 1;
      }
    }
    if (backend_enc_store_rax_to_rbp_arch(elf_ctx, slot_off, ta) != 0) {
      return 0 - 1;
    }
    let vt_nm: u8[160] = [];
    let vt_nlen: i32 = pipeline_asm_emit_vtable_static_name_into(&trait_nm[0],
            trait_nlen, &for_nm[0], for_nlen, is_ptr, &vt_nm[0]);
    if (vt_nlen <= 0) { return 0 - 1; }
    let macho: i32 = pipeline_elf_ctx_macho_leading_underscore(elf_ctx);
    let vt_sym: u8[162] = [];
    let vt_sym_nlen: i32 = vt_nlen;
    if (macho != 0) {
      vt_sym[0] = 95;
      let k: i32 = 0;
      while (k < vt_nlen && k < 160) { vt_sym[k + 1] = vt_nm[k]; k = k + 1; }
      vt_sym_nlen = vt_nlen + 1;
    } else {
      let k: i32 = 0;
      while (k < vt_nlen && k < 161) { vt_sym[k] = vt_nm[k]; k = k + 1; }
    }
    if (backend_enc_lea_sym_to_reg_arch(elf_ctx, 1, &vt_sym[0], vt_sym_nlen, ta) != 0) {
      return 0 - 1;
    }
    /* Fat is {data @ slot_off, vtable @ +8 in address space}.
     * ARM64 product stores [x29, #+off] so +8 is a higher address.
     * x86 stores [rbp, #-off] so a larger off is a LOWER address; the
     * +8 field is therefore slot_off-8. Dispatch loads [fat+8].
     * PLATFORM: LINUX x86_64 rbp-down · MACOS|ARM64 x29-up. */
    let vt_home: i32 = slot_off + 8;
    if (ta == 0) {
      if (slot_off <= 8) { return 0 - 1; }
      vt_home = slot_off - 8;
    }
    if (backend_enc_store_x_reg_to_rbp_arch(elf_ctx, 1, vt_home, ta) != 0) {
      return 0 - 1;
    }
    return 1;
  }
}
