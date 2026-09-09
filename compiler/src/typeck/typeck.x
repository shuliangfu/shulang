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
// See implementation.
// See implementation.
// See implementation.
//
// Cap-T001 / LANG-007 S0 (M1→M2 typeck): functions that call export-extern
// pipeline_* / glue use whole-body unsafe FFI gates. Does not weaken user-code
// unsafe checks inside typeck. PLATFORM: SHARED — product still pins typeck seed until M2.
// See implementation.

const ast = import("ast");

/**
* See implementation.
* See implementation.
*/
export extern function typeck_float64_bits_lo(d: f64): i32;
export extern function typeck_float64_bits_hi(d: f64): i32;
/*
 * F2 TYPE_DYN(17) dyn-coerce impl-lookup authority (single G.7 source — body lives
 * in seeds/parser_asm/parser_asm_skip_tl_slice.inc as the twin of
 * xlang_skip_impl_self_matches_for_c; typeck must NOT iterate
 * g_xlang_skip_impl_* globals directly).
 *
 * Returns 1 iff some registered `impl Trait for T` block has trait_name == trait_nm
 * AND for-type matches concrete_ty_ref. Called from the assign + let-init dyn-coerce
 * gates (search for `xlang_skip_impl_concrete_implements_trait_c` call sites).
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_impl_concrete_implements_trait_c(arena: *void,
        concrete_ty_ref: i32, trait_nm: *u8, trait_nlen: i32): i32;
/*
 * F3 TYPE_DYN(17) vtable-dispatch authority — G.7 accessors over the
 * trait registry `g_xlang_skip_trait_reg[]`. Method declaration order in the
 * trait body defines the vtable slot index (slot 0 = first declared method).
 *
 * `xlang_skip_trait_method_slot_c` resolves a method name to its vtable slot
 * (used by typeck dyn-dispatch branch to stamp call_resolved_func_index=slot,
 * call_resolved_dep_index=DYN_DISPATCH_DEP_SENTINEL=-2). The count + name
 * accessors are used by codegen to enumerate trait methods when building the
 * per-impl function-pointer array at the concrete->dyn coerce site.
 *
 * Bodies live in seeds/parser_asm/parser_asm_skip_tl_slice.inc (twins of
 * xlang_skip_impl_self_matches_for_c). typeck must NOT iterate
 * g_xlang_skip_trait_reg_* globals directly.
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_slot_c(trait_nm: *u8, trait_nlen: i32,
        method_nm: *u8, method_nlen: i32): i32;
export extern function xlang_skip_trait_method_count_c(trait_nm: *u8, trait_nlen: i32): i32;
export extern function xlang_skip_trait_method_name_into_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, out64: *u8): i32;
export extern function xlang_skip_trait_method_ret_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * Return-element TypeKind at trait-method slot. -1 if missing.
 * G.7: completes the skip-trait accessor family next to ret_kind
 * (registry already stores method_ret_elem_kinds). Dyn dispatch
 * reconstructs `[]T` / `[N]T` return type_refs (func_ix is the slot).
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_elem_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * Outer N of a trait-method `[N]T` return. -1 if missing / `[]T`.
 * G.7: completes the skip-trait accessor family next to ret_elem_kind.
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_array_size_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * ndims of a trait-method `[K][N]…T` return. -1 if missing.
 * G.7: completes the skip-trait accessor family next to ret_array_size
 * (registry already stores method_ret_array_ndims). Dyn ret reconstructs
 * `[K][N]T` by wrapping leaf → inner N → outer K (func_ix is the slot).
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @return i32 — ndims (>=1), or 0 / -1 if unset / invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_array_ndims_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * One dim of a trait-method `[K][N]…T` return. dim_ix 0 = outer K.
 * G.7: completes the skip-trait accessor family next to ret_array_ndims
 * (registry already stores method_ret_array_dims). Cap 8.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param dim_ix i32 — dimension index (0 = outer)
 * @return i32 — N > 0, or -1 if invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_array_dim_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, dim_ix: i32): i32;
/**
 * Leaf TypeKind of a trait-method return's ARRAY/SLICE elem (`*[N]T`).
 * G.7: completes the skip-trait accessor family next to ret_elem_kind
 * (registry already stores method_ret_elem_elem_kinds). Dyn ret
 * reconstructs `*[2]i32` via this + ret_elem_array ndims/dims
 * (func_ix is the slot). Twin of param_elem_elem_kind.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @return i32 — TypeKind ord (>=0), or -1 if unset / invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_elem_elem_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * ndims of a trait-method return's ARRAY elem (`*[K][N]T`).
 * G.7: completes the skip-trait accessor family next to ret_elem_elem_kind
 * (registry already stores method_ret_elem_array_ndims; not the
 * top-level ret_array_ndims used by `[K][N]T` ret).
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @return i32 — ndims (>=1), or 0 / -1 if unset / invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_elem_array_ndims_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32): i32;
/**
 * One dim of a trait-method return's ARRAY elem (`*[K][N]T`).
 * dim_ix 0 = outer K of the ARRAY elem. Cap 8.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param dim_ix i32 — dimension index (0 = outer of the ARRAY elem)
 * @return i32 — N > 0, or -1 if invalid. When ndims>0, dim_ix==ndims
 * is dest extras dest-RET extra empty `[]` wrap COUNT for ARRAY/PTR
 * elem (`*[2][]T` / `**[2][]T` = 1; `*[2][][]T` = 2; 0 / missing
 * means no extra wrap = `*[2]i32`) OR extra STAR wrap COUNT for
 * SLICE elem (`*[][2]*T` = 1). dim_ix==ndims+1 is dest extras
 * dest-RET extra STAR wrap COUNT for ARRAY/PTR elem (`*[2]*T` /
 * `**[2]*T` = 1; `*[2][]*T` / `**[2][]*T` = 1 with extra SLICE
 * also in dims[ndims]; 0 / missing means no extra PTR = `*[2]i32`
 * / `**[2]i32` / `*[2][]T` / `**[2][]T`) OR extra empty `[]`
 * wrap COUNT for SLICE elem (`*[][2][]T` = 1; `*[][2][][]T` = 2;
 * 0 / missing means no extra wrap = `*[][2]i32` / `*[][2]*T`).
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_elem_array_dim_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, dim_ix: i32): i32;
/**
 * Copy the TYPE_NAMED spelling of a trait-method return into out64.
 * G.7: completes the skip-trait accessor family next to ret_kind
 * (registry already stores method_ret_names). Dyn dispatch
 * reconstructs a `Pair` return type_ref and the NAMED leaf of
 * `*Pair` / `[]Pair` / `[N]Pair` (func_ix is the slot).
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param out64 *u8 — destination of at least 64 bytes; non-null
 * @return i32 — name length (>0), or 0 if missing
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_ret_name_into_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, out64: *u8): i32;
/**
 * Formal TypeKind at trait-method param_ix (0 = self). -1 if missing.
 * G.7: completes the skip-trait accessor family; body in parser_asm_skip_tl_slice.inc.
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32): i32;
/**
 * Formal element TypeKind at trait-method param_ix (0 = self). -1 if missing.
 * G.7: completes the skip-trait accessor family next to param_kind
 * (registry already stores method_param_elem_kinds). Used so dyn extras
 * can dest-stamp ARRAY_LIT as []T without a module-func type_ref.
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_elem_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32): i32;
/**
 * Copy the TYPE_NAMED spelling of one trait-method formal into out64.
 * G.7: completes the skip-trait accessor family next to param_elem_kind
 * (registry already stores method_param_names for a bare `Pair` formal).
 * Dyn extras cannot look up a module-func formal type_ref (func_ix is
 * the vtable slot), so STRUCT_LIT dest-stamp reconstructs via this +
 * find_or_alloc_named + typeck_coerce_init_struct_lit_to_decl.
 * Extra i of a METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm *u8 — trait name bytes; must be non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot (0..num_methods-1)
 * @param param_ix i32 — formal index including self (0 = self)
 * @param out64 *u8 — destination buffer; caller owns; capacity >= 64
 * @return i32 — name length (>0 on success), 0 if invalid or unset
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_name_into_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32, out64: *u8): i32;
/**
 * ndims of a trait-method `[K][N]…T` formal. -1 if missing.
 * G.7: completes the skip-trait accessor family next to param_name
 * (registry already stores method_param_array_ndims). Dyn extras
 * reconstruct dest-ARRAY (`[2]Pair`) by wrapping leaf → inner N →
 * outer K (func_ix is the slot). Extra i → param_ix = i+1.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param param_ix i32 — formal index including self (0 = self)
 * @return i32 — ndims (>=1), or 0 / -1 if unset / invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_array_ndims_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32): i32;
/**
 * One dim of a trait-method `[K][N]…T` formal. dim_ix 0 = outer K.
 * G.7: completes the skip-trait accessor family next to param_array_ndims
 * (registry already stores method_param_array_dims). Cap 8.
 * Extra i of a METHOD_CALL maps to param_ix = i+1 (param 0 is self).
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param param_ix i32 — formal index including self (0 = self)
 * @param dim_ix i32 — dimension index (0 = outer)
 * @return i32 — N > 0, or -1 if invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_array_dim_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32, dim_ix: i32): i32;
/**
 * Leaf TypeKind of a trait-method formal's ARRAY/SLICE elem (`[][N]T`).
 * G.7: completes the skip-trait accessor family next to param_elem_kind
 * (registry already stores method_param_elem_elem_kinds). Dyn dest-SLICE
 * extras reconstruct `[][2]i32` via this + elem_array ndims/dims
 * (func_ix is the slot). Extra i → param_ix = i+1.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param param_ix i32 — formal index including self (0 = self)
 * @return i32 — TypeKind ord (>=0), or -1 if unset / invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_elem_elem_kind_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32): i32;
/**
 * ndims of a trait-method formal's ARRAY elem (`[][K][N]T`).
 * G.7: completes the skip-trait accessor family next to elem_elem_kind
 * (registry already stores method_param_elem_array_ndims; not the
 * top-level param_array_ndims used by dest-ARRAY extras). Extra i →
 * param_ix = i+1.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param param_ix i32 — formal index including self (0 = self)
 * @return i32 — ndims (>=1 ARRAY pointee), 0 scalar, -2 extra SLICE wrap (`[]*[]T` / `[]*[][]T` / `[][][]T` / `[][][][]T`), or -1 invalid
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_elem_array_ndims_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32): i32;
/**
 * One dim of a trait-method formal's ARRAY elem (`[][K][N]T`).
 * dim_ix 0 = outer K of the ARRAY elem. Cap 8. Extra i → param_ix = i+1.
 * @param trait_nm *u8 — trait name bytes; non-null
 * @param trait_nlen i32 — trait name length; must be > 0
 * @param slot i32 — vtable slot
 * @param param_ix i32 — formal index including self (0 = self)
 * @param dim_ix i32 — dimension index (0 = outer of the ARRAY elem)
 * @return i32 — N > 0, or -1 if invalid. When ndims==-2, dim_ix 0 is
 * the extra SLICE wrap count (`[]*[]T` / `[][][]T` / `[2][][]T` = 1,
 * `[]*[][]T` / `[][][][]T` / `[2][][][]T` = 2; 0 stored means 1).
 * dest extras dest-SLICE-of-PTR, dest-SLICE-of-SLICE,
 * dest-ARRAY-of-PTR, and dest-ARRAY-of-SLICE all read this for
 * ndims==-2. When ndims==0, dim_ix 0 is dest extras
 * dest-ARRAY-of-SLICE extra PTR wrap count (`[2][]*T` = 1) and
 * dest extras dest-SLICE-of-SLICE extra PTR wrap count
 * (`[][]*T` = 1; 0 / missing means no extra PTR). When ndims>0,
 * dim_ix==ndims is dest extras dest-SLICE-of-ARRAY extra SLICE
 * wrap count (`[][2][]T` = 1; `[][2][][]T` = 2; 0 / missing
 * means no extra wrap) AND dest extras dest-ARRAY-of-SLICE extra
 * PTR wrap count (`[2][][2]*T` = 1; 0 / missing means no extra
 * PTR = `[2][][2]T`) AND dest extras dest-SLICE-of-SLICE extra
 * PTR wrap count (`[][][2]*T` = 1; 0 / missing means no extra
 * PTR = `[][][2]T`; discriminant vs extra SLICE is elem_kind
 * SLICE vs ARRAY; discriminant ARRAY vs SLICE outer is param
 * kind). dim_ix==ndims+1 is extra PTR wrap count
 * (`[][2]*T` = 1; `[][2][]*T` = 1 with extra SLICE also in
 * dims[ndims]; `[]*[2]*T` = 1; `[]*[2][]*T` = 1 with extra
 * SLICE also in dims[ndims]; `[2]*[2]*T` = 1;
 * `[2]*[2][]*T` = 1 with extra SLICE also in dims[ndims];
 * `*[2]*T` = 1; `*[2][]*T` = 1 with extra SLICE also in
 * dims[ndims]; 0 / missing means no extra PTR)
 * AND dest extras dest-ARRAY-of-SLICE extra wrap `[2][][2][]T`
 * extra SLICE wrap count (`[2][][2][]T` = 1;
 * `[2][][2][][]T` = 2; extra PTR of `[2][][2]*T` stays
 * dims[ndims] — do not reopen; 0 / missing means no extra
 * wrap = `[2][][2]T`) AND dest extras dest-SLICE-of-SLICE
 * extra wrap `[][][2][]T` extra SLICE wrap count
 * (`[][][2][]T` = 1; `[][][2][][]T` = 2; extra PTR of
 * `[][][2]*T` stays dims[ndims] — do not reopen; 0 /
 * missing means no extra wrap = `[][][2]T`). Discriminant
 * dest extras dest-SLICE of ARRAY extra `[][2]*T` vs dest
 * extras dest-SLICE of PTR extra `[]*[2]*T` vs dest extras
 * dest-ARRAY of PTR extra `[2]*[2]*T` vs PTR-outer
 * `*[2]*T` vs dest extras dest-ARRAY of SLICE extra wrap
 * `[2][][2][]T` vs dest extras dest-SLICE of SLICE extra
 * wrap `[][][2][]T` is elem_kind ARRAY vs PTR vs SLICE
 * (ARRAY vs SLICE vs PTR outer). Both unused slots may
 * be set (`[][2][]*T` / `[]*[2][]*T` / `[2]*[2][]*T` /
 * `[2][][2][]*T` / `[][][2][]*T` / `*[2][]*T`).
 * PLATFORM: SHARED.
 */
export extern function xlang_skip_trait_method_param_elem_array_dim_c(trait_nm: *u8, trait_nlen: i32,
        slot: i32, param_ix: i32, dim_ix: i32): i32;
/* See implementation. */
export extern function driver_diagnostic_typeck_func_fail(func_idx: i32, name: *u8, name_len: i32,
kind: i32): void;
/* See implementation. */
/* wave259 pure-owned leave: Cap face body at EOF (#[no_mangle]); same-TU forward. */
export extern function pipeline_typeck_loop_depth_set_c(ctx: *PipelineDepCtx, depth: i32): void;
/* See implementation. */
export extern function pipeline_dep_ctx_ndep(ctx: *PipelineDepCtx): i32;
export extern function pipeline_dep_ctx_module_at(ctx: *PipelineDepCtx, idx: i32): *Module;
export extern function pipeline_dep_ctx_import_path_len(ctx: *PipelineDepCtx, idx: i32): i32;
export extern function pipeline_dep_ctx_import_path_copy64(ctx: *PipelineDepCtx, idx: i32, dst: *u8): void;
export extern function parser_get_module_num_imports(module: *Module): i32;
export extern function pipeline_dep_ctx_arena_at(ctx: *PipelineDepCtx, idx: i32): *ASTArena;
/* See implementation. */
export extern function pipeline_dep_ctx_set_current_func_index(ctx: *PipelineDepCtx, ix: i32): void;
/* See implementation. */
export extern function pipeline_typeck_check_expr_impl_c(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/* See implementation. */
export extern function pipeline_typeck_check_expr_impl_mega_c(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * Cap residual face for EXPR_METHOD_CALL (wave253 pure leave; wave260 pure-owned leave).
 * Body at EOF (#[no_mangle]); product authority hops to typeck_check_expr_method_call.
 * export extern = same-TU forward for early call sites. Dual-export ban vs pipeline_x.
 * PLATFORM: SHARED freestanding typeck method_call Cap leave.
 */
export extern function pipeline_typeck_check_expr_method_call_c(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * wave260 pure-owned leave: write CALL resolve slots Cap face (thin → apply_call_resolve).
 * Body at EOF (#[no_mangle]). PLATFORM: SHARED freestanding typeck.
 */
export extern function pipeline_typeck_expr_apply_call_resolve_c(arena: *ASTArena, call_expr_ref: i32,
dep_ix: i32, func_ix: i32): void;
/**
 * wave260 pure-owned leave: import path segment Cap face (thin → typeck_import_segment_at).
 * Body at EOF (#[no_mangle]); bool pure → i32 Cap. PLATFORM: SHARED freestanding typeck.
 */
export extern function pipeline_typeck_import_segment_at_c(module: *Module, imp_ix: i32, want_seg: i32,
ostr: *i32, olen: *i32): i32;
/**
 * wave260 pure-owned leave: entry import → dep ctx slot Cap face.
 * Body at EOF (#[no_mangle]). PLATFORM: SHARED freestanding typeck.
 */
export extern function pipeline_typeck_resolve_dep_index_for_import_c(module: *Module, ctx: *PipelineDepCtx,
imp_ix: i32): i32;
/**
 * wave260 pure-owned leave: qualified whole-import CALL return type Cap face.
 * Body at EOF (#[no_mangle]). PLATFORM: SHARED freestanding typeck.
 */
export extern function pipeline_typeck_resolve_whole_import_call_ret_c(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, ctx: *PipelineDepCtx, dep_index_out: *i32, func_index_out: *i32): i32;
/**
 * Stamp CALL/METHOD_CALL resolve slots to empty before method resolve.
 * PLATFORM: SHARED — product residual accessor face (ast expr).
 */
export extern function pipeline_expr_init_call_resolve_at_ref(arena: *ASTArena, expr_ref: i32): void;
/**
 * W-heap-overload pick for CALL/METHOD_CALL by name.
 * wave303 G.7 8.3.6 leave: STRONG on typeck_x.o (was seed strict_minimal residual).
 * Early surface: monofile single-pass; body #[no_mangle] near other Cap faces.
 * is_method reserved (scoring uses EXPR_METHOD_CALL=49 via arg accessor authority).
 * PLATFORM: SHARED — sole import.method overload pick; dual-export ban vs seed.
 */
export extern function pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(
  mod: *Module, caller_arena: *ASTArena, name: *u8, name_len: i32, from_dep_index: i32,
  want_arity: i32, call_expr_ref: i32, is_method: i32, ctx: *PipelineDepCtx,
  func_index_out: *i32): i32;
/**
 * wave231: try_propagate / match live authority is typeck.x; residual C faces
 * thin-wrap these. Keep historical extern names only for cold seed paths that
 * still call the pipeline_*_c symbols (thin → typeck).
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_check_expr_try_propagate_c(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_expr_match_c(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * Match subject BSS faces (Cap residual check_expr; wave703 field-bind).
 * typeck_check_expr_match sets subject before arm typeck so bare VAR field
 * binds resolve via typeck_match_subject_field_type (wave234 pure leave).
 * set/clear/get remain residual BSS (pure pipeline_abi mega deferred).
 * @param module *Module — subject module (must match later field_type module)
 * @param ty i32 — matched expr resolved_type_ref (0 clears useful subject)
 * @return i32 — always 0 (C ABI face)
 * PLATFORM: SHARED freestanding typeck
 */
export extern function pipeline_typeck_match_set_subject_c(module: *Module, ty: i32): i32;
/**
 * Clear match subject field-bind context (nested match restore uses set+get).
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_match_clear_subject_c(): void;
/**
 * Read current match subject type_ref (for nested match save/restore).
 * @return i32 — subject type_ref or 0
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_match_subject_ty_get_c(): i32;
/**
 * Read current match subject module pointer (nested match save/restore).
 * @return *Module — subject module or null
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_match_subject_mod_get_c(): *Module;
/**
 * wave234 G.7: layout helpers for repr(compatible) / match field-bind pure leave.
 * Live in runtime_pipeline_abi.x (*u8 module/arena ABI).
 * PLATFORM: SHARED
 */
export extern function typeck_type_is_named_struct_c(m: *u8, a: *u8, ty_ref: i32): i32;
export extern function typeck_layout_index_for_named_type_c(m: *u8, a: *u8, ty_ref: i32): i32;
export extern function typeck_struct_layouts_same_shape_c(m: *u8, a: *u8, la: i32, lb: i32): i32;
export extern function pipeline_module_struct_layout_repr_compatible_at(module: *Module, idx: i32): i32;
export extern function glue_module_func_index_by_name_c(mod: *u8, name: *u8, name_len: i32): i32;
export extern function typeck_get_allow_legacy_extern_calls(): i32;
export extern function driver_diagnostic_typeck_extern_call_outside_unsafe(line: i32, col: i32): void;
/**
 * ERR-01 try-propagate diagnostic when operand is not Result_* or enclosing
 * function return type does not match Result.
 * @param line i32 — source line
 * @param col i32 — source column
 * PLATFORM: SHARED
 */
export extern function driver_diagnostic_typeck_try_propagate_bad_enclosing(line: i32, col: i32): void;
/**
 * Product check_expr boundary (try_propagate / impl_c). Used by field_access
 * orchestrator to typecheck the base expression with reverse-inferred expected.
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_check_expr_c(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * Generic struct layout type-param registry (used by mono field substitution).
 * PLATFORM: SHARED — defined in ast_pool_struct_layout.c
 */
export extern function pipeline_module_struct_layout_num_type_params_at(module: *Module, li: i32): i32;
export extern function pipeline_module_struct_layout_type_param_name_len(module: *Module, li: i32,
j: i32): i32;
export extern function pipeline_module_struct_layout_type_param_name_into(module: *Module, li: i32,
j: i32, out: *u8): void;
/**
 * Typeck diagnostic report (unknown field gate). Same surface as
 * runtime_driver_diagnostic.x / C field residual.
 * PLATFORM: SHARED
 */
export extern function lsp_diag_report_typeck(line: i32, col: i32, msg: *u8): void;
/* R2 (8.3.3): field_access/soa authority in typeck.x; host-cc thin C leaves retired
 * (pipeline_typeck_field_access.c / pipeline_typeck_soa.c deleted). Product callers
 * use typeck_* / typeck_soa_* / typeck_reject_bare_import_const directly.
 * Residual pipeline_*_c link faces: see EOF thin exports (strict_minimal).
 * PLATFORM: SHARED — BC host-cc leave for these two residual files.
 */
/* Module enum table accessors (dep enum type hop for import_binding). */
export extern function pipeline_module_enum_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_enum_name_byte_at(module: *Module, idx: i32, off: i32): u8;
/* See implementation. */
export extern function driver_diagnostic_typeck_ptr_field(bt_kind: i32, inner_kind: i32, inner_nlen: i32,
base_resolved_ref: i32, num_struct_layouts: i32): void;
/* See implementation. */
export extern function pipeline_type_named_name_into(arena: *ASTArena, type_ref: i32, out: *u8): i32;
/* See implementation. */
export extern function pipeline_type_kind_ord_at(arena: *ASTArena, type_ref: i32): i32;
/* See implementation. */
export extern function pipeline_type_array_size_at(arena: *ASTArena, type_ref: i32): i32;
export extern function pipeline_type_elem_ref_at(arena: *ASTArena, type_ref: i32): i32;
/* wave686: NAMED type-pos args (Wrap<T>) for free-param tree walk / pattern match. */
export extern function pipeline_type_type_arg_ref_at(arena: *ASTArena, type_ref: i32, idx: i32): i32;
/**
 * wave251: append one type-pos arg to TYPE_NAMED (sidecar; never collides bare name).
 * @param arena *ASTArena
 * @param type_ref i32 — TYPE_NAMED slot
 * @param arg_ref i32 — type_ref of type-position arg
 * @return i32 — 0 success, -1 failure
 * PLATFORM: SHARED type pool face (ast_pool_expr_sidecar).
 */
export extern function pipeline_type_append_type_arg(arena: *ASTArena, type_ref: i32, arg_ref: i32): i32;
/**
 * wave251: stamp TYPE_NAMED mono meta after append_type_arg (elem_type_ref + array_size).
 * Avoids pure .x writing Type struct fields (G.7 type-pool authority).
 * @param arena *ASTArena
 * @param type_ref i32 — TYPE_NAMED slot
 * @param elem_ref i32 — first type-arg (slot0 mirror)
 * @param array_size i32 — n type-args
 * @return i32 — 1 success, 0 failure
 * PLATFORM: SHARED type pool face.
 */
export extern function pipeline_type_set_elem_array_size_at(arena: *ASTArena, type_ref: i32,
elem_ref: i32, array_size: i32): i32;
/**
 * wave258 pure-owned leave: type_refs_equal Cap face → typeck.x EOF (#[no_mangle]).
 * typeck.x call sites use historical pipeline_*_c ABI (i32); body thins to
 * type_refs_equal (bool). export extern = same-TU forward; body at EOF.
 * PLATFORM: SHARED freestanding typeck coerce Cap leave.
 */
export extern function pipeline_typeck_type_refs_equal_c(arena: *ASTArena, a: i32, b: i32): i32;
/** Forward: defined near mono/pattern-unify leave (LANG-009 named-inst equality). */
export extern function typeck_named_num_type_args(arena: *ASTArena, ty: i32): i32;
/**
 * wave234: call_arg_repr_compatible residual face retired → typeck authority.
 * Keep historical pipeline_*_c name only as Cap residual thin (check_expr).
 * Product callers use typeck_call_arg_repr_compatible_ok (no wrap cycle).
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_call_arg_repr_compatible_ok_c(module: *Module, arena: *ASTArena,
param_ref: i32, arg_ref: i32): i32;
/**
 * wave234: extern-call unsafe boundary residual face retired → typeck authority.
 * Cap residual thins; product CALL path uses typeck_check_extern_call_unsafe_boundary.
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_check_extern_call_unsafe_boundary_c(module: *Module,
arena: *ASTArena, expr_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * wave234: match subject field_type residual face retired → typeck authority.
 * Cap residual thins; product VAR path uses typeck_match_subject_field_type.
 * PLATFORM: SHARED
 */
export extern function pipeline_typeck_match_subject_field_type_c(module: *Module, arena: *ASTArena,
name: *u8, name_len: i32): i32;
/* wave233 pure leave: resolve_type_alias_ref is typeck authority (active_module
 * peel + local walk). Residual C face thins to typeck_resolve_type_alias_ref.
 * Do NOT reintroduce pipeline_typeck_resolve_type_alias_ref_c wrap here (cycle). */
export extern function pipeline_typeck_active_module_c(): *Module;
export extern function pipeline_module_num_type_aliases_at(module: *Module): i32;
export extern function pipeline_module_type_alias_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_type_alias_name_byte_at(module: *Module, idx: i32, off: i32): u8;
export extern function pipeline_module_type_alias_target_ref(module: *Module, idx: i32): i32;
/* wave259 pure-owned leave: Cap face body at EOF (#[no_mangle]); same-TU forward. */
export extern function pipeline_typeck_func_body_has_implicit_return_tail_c(arena: *ASTArena, body_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_binop_left_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_binop_right_ref_at(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function driver_diagnostic_typeck_block_enter(func_idx: i32, block_ref: i32, n_const: i32,
n_let: i32, n_loop: i32, n_for: i32, n_expr: i32, final_ref: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_fn_enter(func_idx: i32, name: *u8, name_len: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_ret_fail(stage: i32, op_expr_ref: i32, expect_ty_ref: i32,
got_ty_ref: i32): void;
export extern function driver_diagnostic_typeck_binop_operands(expr_ref: i32, left_ref: i32, right_ref: i32,
left_kind: i32, right_kind: i32, left_block_ref: i32, right_block_ref: i32, left_ty_ref: i32, right_ty_ref: i32,
left_ty: *u8, left_ty_len: i32, right_ty: *u8, right_ty_len: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_return_mismatch(line: i32, col: i32,
expect_buf: *u8, expect_len: i32, found_buf: *u8, found_len: i32): void;
export extern function driver_diagnostic_typeck_return_unresolved(line: i32, col: i32,
expr_buf: *u8, expr_len: i32): void;
export extern function driver_diagnostic_typeck_return_subexpr(line: i32, col: i32,
expr_buf: *u8, expr_len: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_assign_mismatch(is_compound: i32, line: i32, col: i32,
expect_buf: *u8, expect_len: i32, found_buf: *u8, found_len: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_import_const_must_be_qualified(line: i32, col: i32,
name: *u8, name_len: i32, binding: *u8, binding_len: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_subscript_base(line: i32, col: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_break_continue_outside(line: i32, col: i32,
is_break: i32): void;
/**
 * Report illegal pointer arithmetic at a binary operator (wave285 Cap residual).
 * @param line i32 — 1-based source line of the binop
 * @param col i32 — 1-based source column of the binop
 * @return void
 * PLATFORM: SHARED — closes soft residual that formerly passed typeck then failed host-cc as BLD001.
 */
export extern function driver_diagnostic_typeck_invalid_ptr_binop(line: i32, col: i32): void;
/**
 * Report illegal float bitwise/mod/shift at a binary operator (wave286 Cap residual).
 * @param line i32 — 1-based source line of the binop
 * @param col i32 — 1-based source column of the binop
 * @return void
 * PLATFORM: SHARED — closes soft residual that formerly passed typeck then failed host-cc as BLD001.
 */
export extern function driver_diagnostic_typeck_invalid_float_binop(line: i32, col: i32): void;
/**
 * Report illegal aggregate ==/!=/relational (wave657 Cap residual).
 * @param line i32 — 1-based source line of the binop
 * @param col i32 — 1-based source column of the binop
 * @return void
 * PLATFORM: SHARED — closes soft residual: typeck stamped bool then host-cc BLD001 (struct/slice)
 * or silent pointer-identity false green (fixed array decay).
 */
export extern function driver_diagnostic_typeck_invalid_aggregate_cmp(line: i32, col: i32): void;
/**
 * Report illegal `as` cast (wave659 Cap residual).
 * @param line i32 — 1-based source line of the cast expr
 * @param col i32 — 1-based source column of the cast expr
 * @return void
 * PLATFORM: SHARED — closes soft residual: typeck stamped target then host-cc BLD001
 * (float→ptr) or silent false green (struct/array as scalar).
 */
export extern function driver_diagnostic_typeck_invalid_as_cast(line: i32, col: i32): void;
/**
 * Report free-function call arity mismatch (wave660 Cap residual).
 * @param line i32 — 1-based source line of the CALL expr
 * @param col i32 — 1-based source column of the CALL expr
 * @return void
 * PLATFORM: SHARED — closes soft residual: typeck bound first same-name func
 * ignoring arity → host-cc BLD001 (too few / too many arguments).
 */
export extern function driver_diagnostic_typeck_call_arity_mismatch(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_call_arg_type_mismatch(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_call_unresolved(line: i32, col: i32): void;
/* wave250 pure leave: generic type-args gate diags (Cap residual faces). */
export extern function driver_diagnostic_typeck_call_not_generic(line: i32, col: i32, name: *u8,
name_len: i32): void;
export extern function driver_diagnostic_typeck_call_requires_type_args(line: i32, col: i32,
name: *u8, name_len: i32): void;
export extern function driver_diagnostic_typeck_call_wrong_num_type_args(line: i32, col: i32,
name: *u8, name_len: i32, expect_n: i32, got_n: i32): void;
/**
 * skip_tl trait-bound check on inferred turbofish slots (wave449/wave250).
 * type_args is contiguous row-major u8[n][128] (first-row pointer).
 * @param fn_name *u8 — callee spelling
 * @param fn_name_len i32
 * @param type_args *u8 — concrete type-name rows (stride 128)
 * @param type_arg_lens *i32 — per-slot name lengths
 * @param nargs i32 — slot count
 * @param line i32
 * @param col i32
 * @return i32 — 0 ok, non-zero bound fail
 * PLATFORM: SHARED freestanding typeck / skip_tl.
 */
export extern function xlang_generic_bound_check_type_args_c(fn_name: *u8, fn_name_len: i32,
type_args: *u8, type_arg_lens: *i32, nargs: i32, line: i32, col: i32): i32;
export extern function pipeline_expr_call_num_type_args_at(arena: *ASTArena, expr_ref: i32): i32;
/**
 * Report non-integer array/slice/pointer subscript index (wave664 Cap residual).
 * @param line i32 — 1-based source line of the INDEX expr
 * @param col i32 — 1-based source column of the INDEX expr
 * @return void
 * PLATFORM: SHARED — closes soft residual: typeck accepted ptr/float/struct/bool
 * indices → host-cc BLD001 ("array subscript is not an integer") or freestanding
 * silent false green using pointer bits as index.
 */
export extern function driver_diagnostic_typeck_subscript_index(line: i32, col: i32): void;
/**
 * Report non-bool operand of LOGAND/LOGOR/LOGNOT (wave665 Cap residual).
 * @param line i32 — 1-based source line of the logical expr
 * @param col i32 — 1-based source column of the logical expr
 * @return void
 * PLATFORM: SHARED — docs/04: logical ops require bool; no implicit int-to-bool.
 * Closes soft residual: `i32 && i32` / `!i32` / `f32 && f32` passed typeck then
 * freestanding/host false green via C truthiness.
 */
export extern function driver_diagnostic_typeck_logical_operand_not_bool(line: i32, col: i32): void;
/**
 * Report incompatible comparison operand types (wave666 Cap residual).
 * @param line i32 — 1-based source line of the ==/!=/</>/<=/>= expr
 * @param col i32 — 1-based source column of the comparison expr
 * @return void
 * PLATFORM: SHARED — closes soft residual: typeck stamped bool for mixed
 * i32/f32/i64/bool/ptr-pointee pairs then freestanding/host false green.
 */
export extern function driver_diagnostic_typeck_comparison_type_mismatch(line: i32, col: i32): void;
/**
 * Report void used as arithmetic/unary operand (wave667 Cap residual).
 * @param line i32 — 1-based source line of the binop or unary expr
 * @param col i32 — 1-based source column of the op
 * @return void
 * PLATFORM: SHARED — closes soft residual: void call result in + - * / % bitops
 * or unary -/~ typeck OK then host-cc BLD001 invalid operands / argument type.
 */
export extern function driver_diagnostic_typeck_invalid_void_binop(line: i32, col: i32): void;
/**
 * Report bool used as arithmetic/bitop/shift/unary -/~ operand (wave677 Cap residual).
 * @param line i32 — 1-based source line of the op
 * @param col i32 — 1-based source column of the op
 * @return void
 * PLATFORM: SHARED — closes soft residual: binop bool→i32 promotion + unary -true
 * freestanding/host false green. LANG-006 let/const scalar bool→int retained.
 */
export extern function driver_diagnostic_typeck_invalid_bool_binop(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_assign_to_const(line: i32, col: i32): void;
/**
 * Report same-block let/const redecl or function-body param clash (wave680 Cap residual).
 * @param line i32 — 1-based source line of the second declaration
 * @param col i32 — 1-based source column of the second declaration
 * @return void
 * PLATFORM: SHARED — closes soft residual: host-C BLD001 redefinition of local.
 */
export extern function driver_diagnostic_typeck_duplicate_local(line: i32, col: i32): void;
export extern function pipeline_block_name_binding_kind(arena: *ASTArena, block_ref: i32, vname: *u8,
vlen: i32): i32;
export extern function pipeline_module_top_level_name_is_const(module: *Module, vname: *u8, vlen: i32): i32;
/**
 * wave680: 1 if name conflicts with another same-block let/const or function-body param.
 * @param arena *ASTArena
 * @param block_ref i32
 * @param vname *u8
 * @param vlen i32
 * @param kind i32 — 0=let at idx, 1=const at idx
 * @param idx i32
 * @param module *Module
 * @param func_index i32 — -1 skips param scan
 * @return i32 — 1 conflict, 0 ok
 * PLATFORM: SHARED — G.7 authority in runtime_pipeline_abi (ast_pool.c left wave309).
 */
export extern function pipeline_block_local_name_redecl_c(arena: *ASTArena, block_ref: i32, vname: *u8,
vlen: i32, kind: i32, idx: i32, module: *Module, func_index: i32): i32;
export extern function pipeline_block_let_name_len(arena: *ASTArena, br: i32, li: i32): i32;
export extern function pipeline_block_let_name_copy64(arena: *ASTArena, br: i32, li: i32, dst: *u8): void;
export extern function pipeline_block_let_init_ref(arena: *ASTArena, br: i32, li: i32): i32;
export extern function pipeline_block_const_name_len(arena: *ASTArena, br: i32, ci: i32): i32;
export extern function pipeline_block_const_name_copy64(arena: *ASTArena, br: i32, ci: i32, dst: *u8): void;
export extern function typeck_driver_diagnostic_pipe_marker(id: i32): void;
export extern function driver_diagnostic_typeck_if_condition_not_bool(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_while_condition_not_bool(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_for_condition_not_bool(line: i32, col: i32): void;
export extern function driver_typeck_diag_scratch_expect(): *u8;
export extern function driver_typeck_diag_scratch_found(): *u8;
/* See implementation. */
export extern function typeck_scratch64_slot(slot: i32): *u8;
/* See implementation. */
export extern function typeck_layout_metrics_sz_slot(): *i32;
export extern function typeck_layout_metrics_al_slot(): *i32;
export extern function typeck_layout_metrics_sz_slot_depth(depth: i32): *i32;
export extern function typeck_layout_metrics_al_slot_depth(depth: i32): *i32;
/* See implementation. */
export extern function typeck_i32_ptr_store(p: *i32, v: i32): void;
/* See implementation. */
export extern function typeck_i32_ptr_read(p: *i32): i32;
/* See implementation. */
export extern function typeck_call_resolve_dep_idx_slot(): *i32;
export extern function typeck_call_resolve_func_idx_slot(): *i32;
/** Expected return type for overload pick (let/assign/return context). 0 = none. PLATFORM: SHARED. */
export extern function typeck_overload_expected_ret_slot(): *i32;
export extern function typeck_overload_expected_ret_peek(): i32;
/* See implementation. */
export extern function typeck_call_resolve_dep_idx_peek(): i32;
export extern function typeck_call_resolve_func_idx_peek(): i32;
/* See implementation. */
export extern function typeck_binop_arith_infer_type_c(arena: *ASTArena, expr_ref: i32, bop_l: i32,
bop_r: i32, expr_kind: i32): void;
/* See implementation. */
export extern function pipeline_patch_block_parent_links(arena: *ASTArena, block_ref: i32, parent_ref: i32): void;
/* See implementation. */
export extern function typeck_layout_metrics_init_depth(depth: i32): void;
export extern function typeck_layout_metrics_al_read_depth(depth: i32): i32;
export extern function typeck_layout_metrics_sz_read_depth(depth: i32): i32;
export extern function typeck_layout_metrics_init_slot(): void;
/* See implementation. */
export extern function typeck_x_type_align_from_layout_glue(module: *Module, arena: *ASTArena, li: i32,
depth: i32): i32;
export extern function typeck_x_type_size_from_layout_glue(module: *Module, arena: *ASTArena, li: i32,
  depth: i32): i32;
/* R2 (8.3.3): typeck_soa_col_base / find_layout_* / field_soa_index /
 * fill_field_access_for_asm_emit migrated to .x authority below.
 * pipeline_typeck_soa.c keeps thin public surface + extern decls. */
/* WPO dep pipe for SoA layout cross-module lookup (emit context). */
export extern function pipeline_asm_emit_dep_pipe_c(): *PipelineDepCtx;
/* Current asm-emit function index (-1 unbound); VAR param fallback for SoA. */
export extern function pipeline_asm_emit_func_index_c(): i32;
/* Bind current emit func index (fill_soa func walk sets this for param fallback). */
export extern function pipeline_asm_emit_set_func_index(func_index: i32): void;
/* Stamp SoA column stride on FIELD_ACCESS (emit reads via field_access_soa_stride). */
export extern function pipeline_expr_set_field_access_soa_stride(arena: *ASTArena, expr_ref: i32,
stride: i32): void;
/* Read SoA stride stamped on FIELD_ACCESS; >0 means SoA path already filled. */
export extern function pipeline_expr_field_access_soa_stride(arena: *ASTArena, expr_ref: i32): i32;
/* Optional debug walk of named func bodies (XLANG_ASM_DEBUG / trace paths). */
export extern function pipeline_debug_trace_named_func_bodies(phase: *u8, module: *Module,
arena: *ASTArena): void;
/* Host-cc layout sync + skip-typeck var type backfill (link surfaces for fill_soa). */
export extern function glue_sync_struct_layout_field_offsets_c(module: *Module, arena: *ASTArena): void;
/* Layout field offset by name: prefer stored, else compute with the given arena. */
export extern function glue_struct_layout_field_offset_by_name_c(module: *Module, arena: *ASTArena,
li: i32, field_name: *u8, flen: i32): i32;
export extern function glue_fill_var_types_from_lets_in_block(arena: *ASTArena, block_ref: i32): void;
export extern function glue_fill_var_types_from_params_for_func(module: *Module, arena: *ASTArena,
func_index: i32): void;
export extern function glue_field_layout_offset_for_base_field(arena: *ASTArena, module: *Module,
base_ref: i32, field_name: *u8, flen: i32): i32;
/* See implementation. */
export extern function pipeline_get_dep_arena_slot(ix: i32): *ASTArena;
/* See implementation. */
export extern function pipeline_module_func_param_type_ref_for_name(module: *Module, func_index: i32,
vname: *u8, vname_len: i32): i32;
/* See implementation. */
export extern function pipeline_module_num_funcs(module: *Module): i32;
/* See implementation. */
export extern function pipeline_module_main_func_index(module: *Module): i32;
export extern function pipeline_module_func_is_extern_at(module: *Module, fi: i32): i32;
export extern function pipeline_module_func_body_ref_at(module: *Module, fi: i32): i32;
export extern function pipeline_module_func_body_expr_ref_at(module: *Module, fi: i32): i32;
export extern function pipeline_module_func_return_type_at(module: *Module, fi: i32): i32;
export extern function pipeline_module_func_name_len_at(module: *Module, fi: i32): i32;
export extern function pipeline_module_func_name_copy64(module: *Module, fi: i32, dst: *u8): void;
export extern function pipeline_module_func_name_byte_at(module: *Module, fi: i32, i: i32): u8;
export extern function pipeline_module_func_name_equal_at(module: *Module, fi: i32, name: *u8,
                                                         name_len: i32): i32;
export extern function pipeline_module_func_set_is_used(module: *Module, fi: i32, is_used: i32): void;
/* See implementation. */
export extern function pipeline_module_struct_layout_reset_slot(module: *Module, idx: i32): void;
export extern function pipeline_module_struct_layout_set_name(module: *Module, idx: i32, bytes: *u8,
len: i32): void;
export extern function pipeline_module_struct_layout_set_field(module: *Module, layout_idx: i32, j: i32,
fname: *u8, fname_len: i32, ftype_ref: i32, foff: i32): void;
/* See implementation. */
export extern function pipeline_struct_layout_next_field_offset(module: *Module, arena: *ASTArena,
layout_idx: i32, new_field_type_ref: i32): i32;
/* See implementation. */
export extern function pipeline_module_struct_layout_field_name_into(module: *Module, layout_idx: i32,
j: i32, out: *u8): void;
export extern function pipeline_module_struct_layout_field_name_len(module: *Module, layout_idx: i32,
j: i32): i32;
export extern function pipeline_module_struct_layout_name_into(module: *Module, idx: i32, out: *u8): void;
export extern function pipeline_module_struct_layout_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_struct_layout_num_fields(module: *Module, layout_idx: i32): i32;
export extern function pipeline_module_struct_layout_set_num_fields(module: *Module, layout_idx: i32,
nf: i32): void;
/* See implementation. */
export extern function pipeline_expr_struct_lit_num_fields(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_struct_lit_type_name_len(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_struct_lit_type_name_into(arena: *ASTArena, expr_ref: i32,
out: *u8): void;
/* Backfill struct_lit_struct_name on an anonymous struct literal from the
 * contextual return type (see runtime_pipeline_abi.x pipeline_expr_struct_lit_type_name_set;
 * pipeline_glue.c left wave309).
 * PLATFORM: SHARED. */
export extern function pipeline_expr_struct_lit_type_name_set(arena: *ASTArena, expr_ref: i32,
name: *u8, name_len: i32): void;
export extern function pipeline_expr_struct_lit_field_name_len(arena: *ASTArena, expr_ref: i32,
j: i32): i32;
export extern function pipeline_expr_struct_lit_field_name_into(arena: *ASTArena, expr_ref: i32, j: i32,
out: *u8): void;
export extern function pipeline_expr_struct_lit_init_ref(arena: *ASTArena, expr_ref: i32, j: i32): i32;
export extern function pipeline_expr_resolved_type_ref(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_set_resolved_type_ref(arena: *ASTArena, expr_ref: i32,
type_ref: i32): void;
/* See implementation. */
export extern function pipeline_expr_typeck_set_float_bits_from_val(arena: *ASTArena, expr_ref: i32): void;
/* See implementation. */
export extern function pipeline_expr_line_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_col_at(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_dep_ctx_typeck_loop_depth_at(ctx: *PipelineDepCtx): i32;
/* See implementation. */
export extern function pipeline_dep_ctx_current_block_ref_at(ctx: *PipelineDepCtx): i32;
export extern function pipeline_dep_ctx_current_func_index(ctx: *PipelineDepCtx): i32;
/* See implementation. */
/* wave259 pure-owned leave: Cap faces body at EOF (#[no_mangle]); same-TU forward. */
export extern function pipeline_dep_ctx_typeck_unsafe_depth_at(ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_block_impl_bind_ctx_c(ctx: *PipelineDepCtx, block_ref: i32): i32;
export extern function pipeline_typeck_block_impl_restore_ctx_c(ctx: *PipelineDepCtx, saved_block_ref: i32): void;
export extern function pipeline_typeck_block_impl_touch_ctx_block_c(ctx: *PipelineDepCtx, block_ref: i32): void;
/* See implementation. */
export extern function pipeline_expr_int_val_at(arena: *ASTArena, expr_ref: i32): i32;
/** Full i64 EXPR_LIT bits (wave307: u64/usize coerce must not use i32 truncation). */
export extern function pipeline_expr_int64_val_at(arena: *ASTArena, expr_ref: i32): i64;
export extern function pipeline_expr_field_access_is_enum_variant(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_set_field_access_enum_variant(arena: *ASTArena, expr_ref: i32,
tag: i32): void;
export extern function pipeline_expr_method_call_arg_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
export extern function pipeline_expr_match_arm_result_ref(arena: *ASTArena, expr_ref: i32, i: i32): i32;
export extern function pipeline_expr_match_arm_is_enum_variant(arena: *ASTArena, expr_ref: i32,
i: i32): i32;
export extern function pipeline_expr_match_arm_variant_index(arena: *ASTArena, expr_ref: i32, i: i32): i32;
/** wave700: optional match-arm guard expr (`pat if cond =>`); 0 = none. */
export extern function pipeline_expr_match_arm_guard_ref(arena: *ASTArena, expr_ref: i32, i: i32): i32;
/* See implementation. */
export extern function pipeline_expr_match_matched_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_match_num_arms_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_module_enum_variant_tag_for_names(m: *Module, enum_name: *u8,
enum_len: i32, variant_name: *u8, variant_len: i32): i32;
export extern function pipeline_expr_array_lit_num_elems_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_array_lit_elem_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
export extern function driver_diagnostic_typeck_enum_no_variant(line: i32, col: i32): void;
export extern function driver_diagnostic_typeck_var_resolution(expr_ref: i32, name: *u8, name_len: i32,
func_idx: i32, block_ref: i32, source: i32, type_ref: i32): void;
/* See implementation. */
export extern function pipeline_arena_type_alloc(arena: *ASTArena): i32;
/* See implementation. */
export extern function pipeline_type_init_primitive_kind_at(arena: *ASTArena, ref: i32, kind_ord: i32): i32;
/* See implementation. */
export extern function pipeline_type_init_named_at(arena: *ASTArena, ref: i32, name: *u8, name_len: i32): i32;
/* See implementation. */
export extern function pipeline_type_init_compound_kind_at(arena: *ASTArena, ref: i32, kind_ord: i32,
elem_ref: i32, array_size: i32): i32;
export extern function pipeline_type_ensure_by_kind_ord(arena: *ASTArena, kind_ord: i32): i32;
export extern function pipeline_type_find_or_alloc_named(arena: *ASTArena, name: *u8, name_len: i32): i32;
export extern function pipeline_type_find_or_alloc_compound(arena: *ASTArena, kind_ord: i32, elem_ref: i32,
array_size: i32): i32;
/* See implementation. */
export extern function pipeline_type_region_label_into(arena: *ASTArena, ref: i32, out64: *u8): i32;
export extern function pipeline_type_region_label_len_at(arena: *ASTArena, ref: i32): i32;
export extern function pipeline_type_set_region_label_at(arena: *ASTArena, ref: i32, label: *u8,
label_len: i32): i32;
export extern function pipeline_type_find_or_alloc_slice(arena: *ASTArena, elem_ref: i32, reg_label: *u8,
reg_label_len: i32): i32;
/**
 * Type-pool face (wave245): find/alloc *elem with optional region label.
 * region_len==0 → unlabelled *T; "stack_local"/11 → WPO-S3 stack-local *Struct.
 * PLATFORM: SHARED — Cap residual ast_pool_type authority.
 */
export extern function pipeline_type_find_or_alloc_ptr(arena: *ASTArena, elem_ref: i32, reg_label: *u8,
reg_label_len: i32): i32;
/**
 * wave257 pure-owned leave: Cap residual region_assign thin faces → typeck.x EOF
 * (#[no_mangle]). Product paths use typeck_check_slice_region_assign /
 * typeck_check_return_slice_region. export extern = same-TU forward for early
 * call sites; bodies at EOF are the single pipeline_*_c authority.
 * PLATFORM: SHARED freestanding typeck region Cap leave.
 */
export extern function pipeline_typeck_check_slice_region_assign_c(arena: *ASTArena, site_expr_ref: i32,
expect_ref: i32, src_ref: i32): i32;
export extern function pipeline_typeck_check_return_slice_region_c(arena: *ASTArena, ret_site_ref: i32,
op_ref: i32, func_return_ref: i32): i32;
/**
 * wave246 pure leave: M-3 return unbound T[] inside active region scope.
 * → typeck.x EOF (#[no_mangle]). Cap residual deletes second body (G.7 dual-export ban).
 * export extern below = same-TU forward for early call sites (check_expr_return /
 * scan_expr); body at EOF is the single authority.
 * PLATFORM: SHARED freestanding typeck region escape on return.
 */
export extern function pipeline_typeck_check_return_slice_region_in_scope_c(arena: *ASTArena,
site_expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * wave156 pure: assign-like expr kind (ASSIGN + compound assigns).
 * Used by typeck_expr_diag_line_col for line=0 fallback on assign sites.
 * PLATFORM: SHARED freestanding
 */
export extern function glue_expr_kind_is_assign_like_ord(ko: i32): i32;
/* See implementation. */
/* See implementation. */
export extern function pipeline_typeck_check_extern_call_unsafe_boundary_c(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx): i32;
/* See implementation. */
export extern function driver_diagnostic_typeck_deref_outside_unsafe(line: i32, col: i32): void;
/**
 * wave257 pure-owned leave: CALL slice region Cap face → typeck.x EOF (#[no_mangle]).
 * Product CALL path uses typeck_check_call_slice_region. export extern = same-TU
 * forward; body at EOF is single pipeline_*_c authority.
 * PLATFORM: SHARED freestanding typeck region Cap leave.
 */
export extern function pipeline_typeck_check_call_slice_region_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * wave248 pure leave: CALL→func_ix for emit/WPO (overload-aware).
 * Cap residual face → typeck.x EOF (#[no_mangle]); residual deletes second
 * scoring body (G.7 dual-export ban + single score authority:
 * typeck_overload_arg_param_score via find_func_return_type_in_module_by_name_overload).
 * export extern = same-TU forward for early call sites; body at EOF.
 * PLATFORM: SHARED freestanding typeck overload resolve.
 */
export extern function pipeline_typeck_resolve_call_func_index_for_emit_c(m: *u8, a: *u8,
call_expr_ref: i32): i32;
/**
 * wave248 pure leave: WPO/typeck overload pick Cap residual face.
 * → typeck.x EOF (#[no_mangle]); residual thin/extern only.
 * PLATFORM: SHARED freestanding typeck overload pick.
 */
export extern function pipeline_typeck_pick_overload_func_index_for_call_c(m: *Module, a: *ASTArena,
call_expr_ref: i32): i32;
/**
 * Env lookup via pure link_abi (not raw getenv). Used by call_slice stack-escape skip.
 * PLATFORM: SHARED freestanding
 */
export extern function link_abi_getenv(name: *u8): *u8;
/**
 * wave250 pure leave: generic type-args / infer / bounds Cap residual face.
 * → typeck.x EOF (#[no_mangle]); residual dual-export ban (body deleted).
 * export extern below = same-TU forward for early call sites (check_expr_call);
 * body at EOF is the single pipeline_*_c authority.
 * PLATFORM: SHARED freestanding typeck generic call type-args gate.
 */
export extern function pipeline_typeck_check_call_generic_type_args_c(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32;
/**
 * wave252 pure leave: generic CALL mono fixup Cap residual face.
 * → typeck.x EOF (#[no_mangle]); residual dual-export ban (body deleted).
 * export extern below = same-TU forward for early call sites (check_expr_call);
 * body at EOF is the single glue_*_c authority.
 * PLATFORM: SHARED freestanding typeck generic CALL fixup.
 */
export extern function glue_generic_call_fixup_resolved_type_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32;
/**
 * wave252 pure leave: generic method_call UFCS Cap residual face.
 * → typeck.x EOF (#[no_mangle]); residual dual-export ban (body deleted).
 * export extern = same-TU forward for residual method_call_c / strict_minimal.
 * PLATFORM: SHARED freestanding typeck generic method UFCS.
 */
export extern function pipeline_typeck_method_call_generic_ufcs_c(module: *Module, arena: *ASTArena,
expr_ref: i32, base_ty: i32, method_nm: *u8, method_nlen: i32, num_args: i32): i32;
/** Stamp CALL/METHOD_CALL resolve slots (dep_ix, func_ix). PLATFORM: SHARED. */
export extern function pipeline_expr_apply_call_resolve(arena: *ASTArena, call_expr_ref: i32,
dep_ix: i32, func_ix: i32): void;
/** Turbofish type-arg type_ref at call site. PLATFORM: SHARED. */
export extern function pipeline_expr_call_type_arg_ref_at(arena: *ASTArena, expr_ref: i32,
idx: i32): i32;
/**
 * Bound-scan registry: type-param name → declaration-order index for generic fn.
 * PLATFORM: SHARED (parser skip_tl registry).
 */
export extern function xlang_generic_func_type_param_index_c(fn_name: *u8, fn_name_len: i32,
tp_name: *u8, tp_name_len: i32): i32;
/**
 * skip_tl: does enclosing `fn<T: Trait>` grant `method` on type-param T?
 * @param fn_name *u8 — generic function spelling
 * @param fn_name_len i32
 * @param tp_name *u8 — receiver type-param name
 * @param tp_name_len i32
 * @param method_name *u8 — method spelling
 * @param method_name_len i32
 * @param num_args i32 — METHOD extras (self not counted)
 * @param out_ret_kind *i32 — TypeKind ord or -1
 * @param out_ret_name *u8 — 64-byte NAMED spelling
 * @param out_ret_name_len *i32
 * @return i32 — 1 granted, 0 no
 * PLATFORM: SHARED parser skip_tl registry.
 */
export extern function xlang_generic_bound_method_on_param_c(fn_name: *u8, fn_name_len: i32,
tp_name: *u8, tp_name_len: i32, method_name: *u8, method_name_len: i32, num_args: i32,
out_ret_kind: *i32, out_ret_name: *u8, out_ret_name_len: *i32): i32;
/**
 * wave247 pure leave: CALL callee return-type resolve Cap residual face.
 * → typeck.x EOF (#[no_mangle] thin → resolve_call_callee_return_type).
 * Cap residual method_call deletes second body (G.7 dual-export ban).
 * export extern below = same-TU forward for early call sites (check_expr_call);
 * body at EOF is the single pipeline_*_c authority.
 * PLATFORM: SHARED freestanding typeck call-target resolve.
 */
export extern function pipeline_typeck_resolve_call_callee_return_type_c(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, call_expr_ref: i32, ctx: *PipelineDepCtx): i32;
/**
 * wave243 pure leave: M-3 stamp_let + M-5 read_ptr faces → typeck.x EOF
 * (#[no_mangle]). Cap residual deletes second bodies (G.7 dual-export ban).
 * export extern below = same-TU forward for early call sites (check_expr /
 * check_block); bodies at EOF are the single authority.
 * PLATFORM: SHARED freestanding typeck region stamp / read_ptr bind.
 */
export extern function pipeline_type_stamp_block_let_region_c(arena: *ASTArena, block_ref: i32, let_idx: i32,
ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_is_read_ptr_slice_callee_c(name: *u8, name_len: i32): i32;
export extern function pipeline_typeck_read_ptr_slice_return_ref_c(arena: *ASTArena): i32;
export extern function pipeline_typeck_is_simd_comptime_callee_c(name: *u8, name_len: i32): i32;
export extern function pipeline_block_let_type_ref(arena: *ASTArena, br: i32, li: i32): i32;
export extern function pipeline_block_set_let_type_ref(arena: *ASTArena, br: i32, li: i32, type_ref: i32): i32;
/**
 * wave244 pure leave: M-3 check_block_one_region + WPO-S3 call_struct_stack_escape
 * → typeck.x EOF (#[no_mangle]). Cap residual deletes second bodies (G.7 dual-export ban).
 * export extern below = same-TU forward for early call sites (check_block / scan);
 * bodies at EOF are the single authority.
 * PLATFORM: SHARED freestanding typeck region dispatch / CALL stack-escape.
 */
export extern function pipeline_typeck_check_block_one_region_c(module: *Module, arena: *ASTArena,
block_ref: i32, region_idx: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_call_struct_stack_escape_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_block_region_is_unsafe(arena: *ASTArena, br: i32, ri: i32): i32;
/**
 * wave242 G.7 pure leave scan tree deps (Cap residual / block pool faces).
 * PLATFORM: SHARED — post-typeck stack-escape walker.
 */
export extern function pipeline_block_region_with_arena_cap_ref(arena: *ASTArena, br: i32, ri: i32): i32;
export extern function pipeline_block_region_label_len(arena: *ASTArena, br: i32, ri: i32): i32;
export extern function pipeline_block_region_label_copy64(arena: *ASTArena, br: i32, ri: i32, dst: *u8): void;
/* wave259 pure-owned leave: Cap faces body at EOF (#[no_mangle]); same-TU forward. */
export extern function pipeline_typeck_unsafe_depth_push_c(ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_unsafe_depth_pop_c(ctx: *PipelineDepCtx, saved: i32): void;
export extern function pipeline_module_func_num_generic_params_at(module: *Module, fi: i32): i32;
export extern function pipeline_typeck_linear_reset_c(): void;
export extern function pipeline_typeck_linear_use_var_c(arena: *ASTArena, type_ref: i32, expr_ref: i32,
name: *u8, name_len: i32): i32;
export extern function pipeline_typeck_linear_accepts_init_c(arena: *ASTArena, decl_ref: i32, init_ref: i32): i32;
export extern function pipeline_typeck_reject_addr_of_linear_c(arena: *ASTArena, op_ref: i32,
addr_expr_ref: i32, module: *Module, ctx: *PipelineDepCtx): i32;
/** M-4 linear ADDR_OF reject diagnostic (product driver face). */
export extern function driver_diagnostic_typeck_linear_addr_of(line: i32, col: i32): void;
/**
 * wave245 pure leave: WPO-S3 &local named-struct → stack_local *T type_ref.
 * → typeck.x EOF (#[no_mangle]). Cap residual deletes second body (G.7 dual-export ban).
 * export extern below = same-TU forward for early call sites (check_expr_addr_of);
 * body at EOF is the single authority.
 * PLATFORM: SHARED freestanding typeck stack-local pointer stamp.
 */
export extern function pipeline_typeck_ptr_for_addr_of_operand_c(arena: *ASTArena, op_ref: i32,
elem_ty: i32, module: *Module, ctx: *PipelineDepCtx): i32;
/**
 * wave257 pure-owned leave: stack-escape / scope-borrow / allocator Cap faces →
 * typeck.x EOF (#[no_mangle]). Product paths use typeck_check_struct_stack_escape_assign /
 * typeck_check_scope_borrow_* / typeck_check_allocator_region_*. export extern =
 * same-TU forward for residual check_expr / scan; bodies at EOF are single authority.
 * PLATFORM: SHARED freestanding typeck region Cap leave.
 */
export extern function pipeline_typeck_check_struct_stack_escape_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_scope_borrow_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_scope_borrow_return_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, op_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_allocator_region_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, ctx: *PipelineDepCtx): i32;
export extern function pipeline_typeck_check_allocator_region_return_c(arena: *ASTArena, site_expr_ref: i32,
return_type_ref: i32): i32;
/**
 * MEM-C1 with_arena nest BSS faces (wave240 pure leave → typeck.x EOF):
 * pure leave allocator gates read nest depth + current body block; residual
 * scan / one_region call pure push/pop/reset (G.7 dual-export ban).
 * Bodies: pipeline_typeck_with_arena_scope_* at file EOF (#[no_mangle]).
 * PLATFORM: SHARED freestanding typeck nest cells.
 */
/* export bodies at EOF — dual-export ban (no residual BSS second cell). */
/**
 * Pure block-pool faces used by wave236 scope-borrow ancestor / decl lookup.
 * PLATFORM: SHARED
 */
export extern function pipeline_block_parent_block_ref_at(arena: *ASTArena, block_ref: i32): i32;
export extern function pipeline_block_find_var_decl_block_ref(arena: *ASTArena, block_ref: i32, vname: *u8,
vlen: i32): i32;
/**
 * wave148 pure: is expr_ref the func_idx formal at param_ix?
 * PLATFORM: SHARED freestanding (runtime_pipeline_abi)
 */
export extern function glue_expr_is_func_param_at_c(arena: *ASTArena, mod: *Module, func_idx: i32,
expr_ref: i32, param_ix: i32): i32;
export extern function pipeline_module_func_param_type_ref_at(module: *Module, fi: i32, pi: i32): i32;
export extern function pipeline_module_func_num_params_at(module: *Module, fi: i32): i32;
/**
 * Cap 10.7.1: 1 when func has trailing `...` (named params only in num_params).
 * PLATFORM: SHARED — used by typeck call arity / overload pick.
 */
export extern function pipeline_module_func_is_variadic_at(module: *Module, fi: i32): i32;
export extern function pipeline_expr_call_resolved_func_index_at(arena: *ASTArena, expr_ref: i32): i32;
/**
 * Resolved dep module index for a CALL (-1 = local / entry module).
 * PLATFORM: SHARED — wave660 call arity gate needs dep module for num_params.
 */
export extern function pipeline_expr_call_resolved_dep_index_at(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_kind_ord_at(arena: *ASTArena, expr_ref: i32): i32;
/**
 * wave255 host-cc leave: historical pipeline_typeck_*_c CTFE Cap faces live as
 * #[no_mangle] thin exports at EOF (wave255 block) → typeck_* authority.
 * pipeline_typeck_ctfe.c deleted (present 56→55). Dual-export ban on residual C.
 * PLATFORM: SHARED freestanding typeck
 */
/**
 * wave423: stamp block const type_ref after inference from init.
 * @param arena *ASTArena
 * @param br i32 — block ref
 * @param ci i32 — const index in block
 * @param type_ref i32 — inferred type
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED typeck/AST.
 */
export extern function pipeline_block_set_const_type_ref(arena: *ASTArena, br: i32, ci: i32,
type_ref: i32): i32;
export extern function pipeline_module_top_level_let_set_type_ref(module: *Module, idx: i32,
type_ref: i32): void;
export extern function pipeline_module_top_level_let_init_ref(module: *Module, idx: i32): i32;

/**
 * wave238 G.7 pure leave: CTFE producer (LANG-006). Live body is hand-synced in
 * typeck_gen.c (typeck_fold_* / typeck_block_const_init_is_const /
 * typeck_const_init_not_constant / typeck_expr_is_c_static_const_init).
 * wave255: Cap residual pipeline_typeck_ctfe.c retired; historical pipeline_* faces
 * are thin on typeck_x.o only (EOF). Full .x body lands when typeck -E recovers.
 * @param arena *ASTArena
 * @param expr_ref i32
 * PLATFORM: SHARED freestanding typeck — single CTFE producer path.
 */
export extern function typeck_fold_expr(arena: *ASTArena, expr_ref: i32): void;
/**
 * Fold block const init at const_idx with prior consts in scope (wave238 pure leave).
 * @param arena *ASTArena
 * @param block_ref i32
 * @param const_idx i32
 * PLATFORM: SHARED freestanding typeck
 */
export extern function typeck_fold_block_const_init(arena: *ASTArena, block_ref: i32, const_idx: i32): void;
/**
 * Fold expr with all block consts as env (wave238 pure leave).
 * @param arena *ASTArena
 * @param block_ref i32
 * @param expr_ref i32
 * PLATFORM: SHARED freestanding typeck
 */
export extern function typeck_fold_expr_in_block(arena: *ASTArena, block_ref: i32, expr_ref: i32): void;
/**
 * Whitelist: block const init is a const expression (wave238 pure leave).
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck
 */
export extern function typeck_block_const_init_is_const(arena: *ASTArena, block_ref: i32, const_idx: i32): i32;
/**
 * Diag: const init must be constant expression (wave238 pure leave).
 * PLATFORM: SHARED freestanding typeck
 */
export extern function typeck_const_init_not_constant(line: i32, col: i32): void;
/**
 * Pure-lit tree legal as C static initializer (wave238 pure leave; codegen gate).
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck
 */
export extern function typeck_expr_is_c_static_const_init(arena: *ASTArena, expr_ref: i32): i32;
/**
 * Same const-expr whitelist as typeck_block_const_init_is_const, with
 * const_names != NULL so module top-level const VAR / import FIELD pass.
 * Residual body: typeck_cap_residual.from_x.c (same TU after -E).
 * @param arena *ASTArena — expr arena
 * @param expr_ref i32 — init expr
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck. G.7: not a second checker.
 */
export extern function typeck_expr_is_const_with_module_consts(arena: *ASTArena, expr_ref: i32): i32;


/* See implementation. */
export extern function pipeline_expr_if_cond_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_if_then_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_if_else_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_block_ref_at(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_asm_block_final_expr_ref_at(arena: *ASTArena, block_ref: i32): i32;
export extern function pipeline_block_expr_stmt_ref(arena: *ASTArena, block_ref: i32, ei: i32): i32;
/** See implementation for details. */
export extern function pipeline_block_set_parent_if_zero(arena: *ASTArena, block_ref: i32, parent_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_unary_operand_ref_at(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_expr_call_callee_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_call_num_args_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_call_arg_ref(arena: *ASTArena, expr_ref: i32, idx: i32): i32;
/* See implementation. */
export extern function pipeline_expr_index_base_ref(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_index_index_ref(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_set_index_base_is_slice(arena: *ASTArena, expr_ref: i32,
v: i32): void;
export extern function pipeline_expr_set_index_proven_in_bounds(arena: *ASTArena, expr_ref: i32,
v: i32): void;
/* See implementation. */
export extern function pipeline_expr_as_operand_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_as_target_type_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_name_into(arena: *ASTArena, expr_ref: i32,
out: *u8): void;
export extern function pipeline_expr_field_access_name_len(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_base_ref(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_set_field_access_offset(arena: *ASTArena, expr_ref: i32, offset: i32): void;
export extern function pipeline_expr_var_name_into(arena: *ASTArena, expr_ref: i32, out: *u8): void;
export extern function pipeline_expr_var_name_len(arena: *ASTArena, expr_ref: i32): i32;
/* See implementation. */
export extern function pipeline_block_resolve_var_type_ref(arena: *ASTArena, block_ref: i32, vname: *u8,
vlen: i32): i32;
export extern function pipeline_expr_method_call_base_ref_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_method_call_num_args_at(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_method_call_name_len(arena: *ASTArena, expr_ref: i32): i32;
export extern function pipeline_expr_method_call_name_into(arena: *ASTArena, expr_ref: i32, out64: *u8): void;
/* See implementation. */
export extern function asm_qual_sym_layer_reset(): void;
export extern function asm_qual_sym_layer_push(bytes: *u8, len: i32): i32;
export extern function asm_qual_sym_layer_count(): i32;
export extern function asm_qual_sym_layer_len(i: i32): i32;
export extern function asm_qual_sym_layer_copy(i: i32, dst: *u8, cap: i32): void;
/* See implementation. */
export extern function driver_diagnostic_typeck_struct_padding_before(sname: *u8, sname_len: i32, gap: i32,
fname: *u8, fname_len: i32): void;
export extern function driver_diagnostic_typeck_struct_padding_trailing(sname: *u8, sname_len: i32,
gap: i32): void;
export extern function driver_diagnostic_typeck_struct_field_bad_size(sname: *u8, sname_len: i32,
fname: *u8, fname_len: i32): void;
/* See implementation. */
export extern function pipeline_module_num_struct_layouts_at(module: *Module): i32;
export extern function pipeline_module_struct_layout_alloc(module: *Module): i32;
export extern function pipeline_module_struct_layout_field_type_ref(module: *Module, layout_idx: i32,
j: i32): i32;
export extern function pipeline_module_struct_layout_field_offset_at(module: *Module, li: i32,
j: i32): i32;
export extern function pipeline_module_struct_layout_field_align_at(module: *Module, li: i32, j: i32): i32;
export extern function pipeline_module_struct_layout_set_field_align(module: *Module, li: i32, j: i32, al: i32): void;
export extern function pipeline_struct_layout_next_field_offset_ex(module: *Module, arena: *ASTArena, layout_idx: i32,
new_field_type_ref: i32, field_align_req: i32): i32;
/* See implementation. */
export extern function pipeline_typeck_pad_fields_warn_layout(module: *Module, arena: *ASTArena, li: i32): void;
/* See implementation. */
export extern function pipeline_typeck_hot_reorder_warn_layout(module: *Module, arena: *ASTArena, li: i32): void;
/**
 * L6 unused-binding hints (XLANG_UNUSED_HINT=1). Info only; never fails typeck.
 * @param module *Module
 * @param arena *ASTArena
 * @return i32 — hint count
 * PLATFORM: SHARED — authority pipeline_typeck_unused_binding_hints.
 */
export extern function pipeline_typeck_unused_binding_hints(module: *Module, arena: *ASTArena): i32;
/**
 * WPO-S1 callgraph dump (XLANG_WPO_DUMP_CALLGRAPH=path|"-"). Info only; never fails typeck.
 * @param module *Module
 * @param arena *ASTArena
 * @param ctx *PipelineDepCtx — reserved (v1 single-module)
 * @return i32 — 1 dumped, 0 skipped
 * PLATFORM: SHARED — authority pipeline_typeck_wpo_dump_callgraph.
 */
export extern function pipeline_typeck_wpo_dump_callgraph(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx): i32;
export extern function pipeline_module_struct_layout_name_byte_at(module: *Module, idx: i32, off: i32): u8;
export extern function pipeline_module_struct_layout_allow_padding_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_struct_layout_set_allow_padding(module: *Module, idx: i32,
  v: i32): void;
export extern function pipeline_module_struct_layout_packed_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_struct_layout_soa_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_struct_layout_set_soa(module: *Module, idx: i32, v: i32): void;
export extern function pipeline_module_import_path_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_path_byte_at(module: *Module, idx: i32, off: i32): u8;
export extern function pipeline_module_import_kind_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_binding_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_binding_name_byte_at(module: *Module, idx: i32,
off: i32): u8;
export extern function pipeline_module_import_select_count_at(module: *Module, idx: i32): i32;
export extern function pipeline_module_import_select_name_len(module: *Module, idx: i32, sel: i32): i32;
export extern function pipeline_module_import_select_name_byte_at(module: *Module, idx: i32, sel: i32,
off: i32): u8;
export extern function pipeline_module_top_level_let_name_len(module: *Module, idx: i32): i32;
export extern function pipeline_module_top_level_let_name_byte_at(module: *Module, idx: i32, off: i32): u8;
export extern function pipeline_module_top_level_let_type_ref(module: *Module, idx: i32): i32;
export extern function pipeline_module_top_level_let_is_const(module: *Module, idx: i32): i32;

/** Exported function `type_kind_ordinal`.
 * Implements `type_kind_ordinal`.
 * @param k TypeKind
 * @return i32
 */
export function type_kind_ordinal(k: TypeKind): i32 {
  let o: i32 = k as i32;
  let lo: i32 = TypeKind.TYPE_I32 as i32;
  let hi: i32 = TypeKind.TYPE_FN as i32;
  if (o < lo) {
    return - 1;
  }
  if (o > hi) {
    return - 1;
  }
  return o;
}

/** Exported function `name_equal`.
 * Implements `name_equal`.
 * @param a *u8
 * @param a_len i32
 * @param b *u8
 * @param b_len i32
 * @return bool
 */
export function name_equal(a: *u8, a_len: i32, b: *u8, b_len: i32): bool {
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

/** Exported function `typeck_resolve_type_alias_ref_local`.
 * Implements `typeck_resolve_type_alias_ref_local`.
 * @param module *Module
 * @param arena *ASTArena
 * @param type_ref i32
 * @param depth i32
 * @return i32
 */
export function typeck_resolve_type_alias_ref_local(module: *Module, arena: *ASTArena, type_ref: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let type_name: u8[128] = [];
    let alias_count: i32 = 0;
    let alias_i: i32 = 0;
    let type_name_len: i32 = 0;
    let alias_name_len: i32 = 0;
    let alias_off: i32 = 0;
    let ord_named: i32 = 8;
    let alias_target_ref: i32 = 0;
    let max_depth: i32 = 32;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ast.ref_is_null(type_ref) || depth > max_depth) {
      return type_ref;
    }
    if (pipeline_type_kind_ord_at(arena, type_ref) != ord_named) {
      return type_ref;
    }
    type_name_len = pipeline_type_named_name_into(arena, type_ref, &type_name[0]);
    if (type_name_len <= 0) {
      return type_ref;
    }
    alias_count = pipeline_module_num_type_aliases_at(module);
    while (alias_i < alias_count) {
      alias_name_len = pipeline_module_type_alias_name_len(module, alias_i);
      /* wave582 Cap residual: alias names may be up to 127 (TypeAliasEntry.name[128]). */
      if (alias_name_len == type_name_len && alias_name_len > 0 && alias_name_len <= 127) {
        alias_off = 0;
        while (alias_off < alias_name_len) {
          if (pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off) != type_name[alias_off]) {
            break;
          }
          alias_off = alias_off + 1;
        }
        if (alias_off == alias_name_len) {
          alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i);
          if (ast.ref_is_null(alias_target_ref)) {
            return type_ref;
          }
          return typeck_resolve_type_alias_ref_local(module, arena, alias_target_ref, depth + 1);
        }
      }
      alias_i = alias_i + 1;
    }
    return type_ref;
  }
}

/**
 * Resolve type aliases using the process-wide active typeck module (wave233).
 * Thin product face for residual C and type_refs_equal peel: load
 * pipeline_typeck_active_module_c BSS, then walk aliases via
 * typeck_resolve_type_alias_ref_local (depth 0).
 * @param arena *ASTArena — type pool for NAMED names
 * @param type_ref i32 — type_ref to peel (null/non-NAMED returned unchanged)
 * @return i32 — resolved target type_ref, or type_ref if no alias match
 * PLATFORM: SHARED — freestanding typeck_x.o; residual C face thins here.
 */
export function typeck_resolve_type_alias_ref(arena: *ASTArena, type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let mod: *Module = pipeline_typeck_active_module_c();
    let peeled: i32 = typeck_resolve_type_alias_ref_local(mod, arena, type_ref, 0);
    /* CORE-016: Name&lt;Args&gt; → existing mangled family (Result_i32) when present. */
    return typeck_canonicalize_named_inst_if_present(arena, peeled);
  }
}

/**
 * CORE-016 / LANG-009: rewrite `Name&lt;Args&gt;` to the mangled family spelling
 * (`Result_i32`, `Option_i32`, …) via find_or_alloc. Layout still resolves by
 * name across modules (family structs / any-module named_layout). Prefer an
 * already-present bare or `module.Family` type_ref when the arena has one.
 * @param arena *ASTArena
 * @param ty i32 — candidate type_ref
 * @return i32 — family type_ref, or ty unchanged when mangle fails
 * PLATFORM: SHARED — sole named-inst → family layout canonicalize.
 */
export function typeck_canonicalize_named_inst_if_present(arena: *ASTArena, ty: i32): i32 {
  // PLATFORM: SHARED — Result&lt;T,i32&gt;/Option&lt;T&gt; family layout rewrite.
  unsafe {
    let mangled: u8[128] = [];
    let ml: i32 = 0;
    let k: i32 = 0;
    let ko: i32 = 0;
    let exist_len: i32 = 0;
    let nm_scr: *u8 = typeck_scratch64_slot(13);
    let uq: i32 = 0;
    let ul: i32 = 0;
    let i: i32 = 0;
    let ord_named: i32 = 8;
    let fam: i32 = 0;
    if (arena == 0 as *ASTArena || ty <= 0) {
      return ty;
    }
    if (pipeline_type_kind_ord_at(arena, ty) != ord_named) {
      return ty;
    }
    if (typeck_named_num_type_args(arena, ty) <= 0) {
      return ty;
    }
    ml = typeck_named_inst_mangle_into(arena, ty, &mangled[0], 128);
    if (ml <= 0) {
      return ty;
    }
    k = 1;
    while (k <= arena.num_types) {
      ko = pipeline_type_kind_ord_at(arena, k);
      if (ko == ord_named && typeck_named_num_type_args(arena, k) == 0) {
        exist_len = pipeline_type_named_name_into(arena, k, nm_scr);
        if (exist_len == ml && name_equal(nm_scr, exist_len, &mangled[0], ml)) {
          return k;
        }
        uq = typeck_named_unqual_start(nm_scr, exist_len);
        ul = exist_len - uq;
        if (ul == ml && ul > 0) {
          i = 0;
          while (i < ml) {
            if (nm_scr[uq + i] != mangled[i]) {
              break;
            }
            i = i + 1;
          }
          if (i == ml) {
            return k;
          }
        }
      }
      k = k + 1;
    }
    fam = find_or_alloc_named_type_ref(arena, &mangled[0], ml);
    if (fam > 0) {
      return fam;
    }
    return ty;
  }
}

/** Function `typeck_named_type_matches_name_or_alias`.
 * Purpose: implements `typeck_named_type_matches_name_or_alias`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
export function typeck_named_type_matches_name_or_alias(module: *Module, arena: *ASTArena, decl_ty_ref: i32,
lit_name: *u8, lit_name_len: i32, depth: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let decl_name: u8[128] = [];
    let alias_name: u8[128] = [];
    let resolved_decl: i32 = 0;
    let decl_name_len: i32 = 0;
    let alias_count: i32 = 0;
    let alias_i: i32 = 0;
    let alias_name_len: i32 = 0;
    let alias_off: i32 = 0;
    let alias_target_ref: i32 = 0;
    let ord_named: i32 = 8;
    let max_depth: i32 = 32;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ast.ref_is_null(decl_ty_ref)
    || lit_name == 0 as *u8 || lit_name_len <= 0 || depth > max_depth) {
      return false;
    }
    resolved_decl = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0);
    if (!ast.ref_is_null(resolved_decl) && pipeline_type_kind_ord_at(arena, resolved_decl) == ord_named) {
      decl_name_len = pipeline_type_named_name_into(arena, resolved_decl, &decl_name[0]);
      if (name_equal(&decl_name[0], decl_name_len, lit_name, lit_name_len)) {
        return true;
      }
    }
    if (pipeline_type_kind_ord_at(arena, decl_ty_ref) != ord_named) {
      return false;
    }
    decl_name_len = pipeline_type_named_name_into(arena, decl_ty_ref, &decl_name[0]);
    if (name_equal(&decl_name[0], decl_name_len, lit_name, lit_name_len)) {
      return true;
    }
    alias_count = pipeline_module_num_type_aliases_at(module);
    while (alias_i < alias_count) {
      alias_name_len = pipeline_module_type_alias_name_len(module, alias_i);
      /* wave582 Cap residual: alias names may be up to 127 (match resolve_type_alias). */
      if (alias_name_len == decl_name_len && alias_name_len > 0 && alias_name_len <= 127) {
        alias_off = 0;
        while (alias_off < alias_name_len) {
          alias_name[alias_off] = pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off);
          alias_off = alias_off + 1;
        }
        if (name_equal(&alias_name[0], alias_name_len, &decl_name[0], decl_name_len)) {
          alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i);
          return typeck_named_type_matches_name_or_alias(module, arena, alias_target_ref, lit_name,
          lit_name_len, depth + 1);
        }
      }
      alias_i = alias_i + 1;
    }
    return false;
  }
}

/** Exported function `typeck_layout_name_equal`.
 * Implements `typeck_layout_name_equal`.
 * @param module *Module
 * @param k i32
 * @param nm *u8
 * @param nlen i32
 * @return bool
 */
export function typeck_layout_name_equal(module: *Module, k: i32, nm: *u8, nlen: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let buf: *u8 = typeck_scratch64_slot(0);
    let slen: i32 = pipeline_module_struct_layout_name_len(module, k);
    if (slen != nlen || nlen <= 0) {
      return false;
    }
    pipeline_module_struct_layout_name_into(module, k, buf);
    return name_equal(buf, slen, nm, nlen);
  }
}

/** Exported function `typeck_layout_field_name_equal`.
 * Implements `typeck_layout_field_name_equal`.
 * @param module *Module
 * @param k i32
 * @param j i32
 * @param nm *u8
 * @param nlen i32
 * @return bool
 */
export function typeck_layout_field_name_equal(module: *Module, k: i32, j: i32, nm: *u8, nlen: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let buf: *u8 = typeck_scratch64_slot(1);
    let fl: i32 = pipeline_module_struct_layout_field_name_len(module, k, j);
    if (fl != nlen || nlen <= 0) {
      return false;
    }
    pipeline_module_struct_layout_field_name_into(module, k, j, buf);
    return name_equal(buf, fl, nm, nlen);
  }
}

/** Exported function `typeck_layout_name_into`.
 * Implements `typeck_layout_name_into`.
 * @param module *Module
 * @param k i32
 * @param buf *u8
 * @return i32
 */
export function typeck_layout_name_into(module: *Module, k: i32, buf: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    pipeline_module_struct_layout_name_into(module, k, buf);
    return pipeline_module_struct_layout_name_len(module, k);
  }
}

/** Exported function `typeck_layout_field_name_into`.
 * Implements `typeck_layout_field_name_into`.
 * @param module *Module
 * @param k i32
 * @param j i32
 * @param buf *u8
 * @return i32
 */
export function typeck_layout_field_name_into(module: *Module, k: i32, j: i32, buf: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    pipeline_module_struct_layout_field_name_into(module, k, j, buf);
    return pipeline_module_struct_layout_field_name_len(module, k, j);
  }
}

/* See implementation. */
export function typeck_import_path_slice_equal(module: *Module, imp_ix: i32, off: i32, seg_len: i32,
nm: *u8, nm_len: i32): bool {
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

/* See implementation. */
export function typeck_import_binding_name_equal(module: *Module, imp_ix: i32, nm: *u8,
nm_len: i32): bool {
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

/** Exported function `typeck_module_num_imports`.
 * Implements `typeck_module_num_imports`.
 * @param module *Module
 * @return i32
 */
export function typeck_module_num_imports(module: *Module): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (module == 0 as *Module) {
      return 0;
    }
    let n_imp: i32 = parser_get_module_num_imports(module);
    if (n_imp > 0) {
      return n_imp;
    }
    return module.num_imports;
  }
}

/** Exported function `typeck_var_is_import_visible_name`.
 * Implements `typeck_var_is_import_visible_name`.
 * @param module *Module
 * @param nm *u8
 * @param nlen i32
 * @return bool
 */
export function typeck_var_is_import_visible_name(module: *Module, nm: *u8, nlen: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ii: i32 = 0;
    let import_kind: i32 = 0;
    let seg_rel: i32 = 0;
    let seg_len: i32 = 0;
    if (module == 0 as *Module || nm == 0 as *u8 || nlen <= 0) {
      return false;
    }
    let n_imp: i32 = typeck_module_num_imports(module);
    while (ii < n_imp) {
      import_kind = pipeline_module_import_kind_at(module, ii);
      if (import_kind == 1 && typeck_import_binding_name_equal(module, ii, nm, nlen)) {
        return true;
      }
      if (typeck_import_segment_at(module, ii, 0, &seg_rel, &seg_len) &&
          typeck_import_path_slice_equal(module, ii, seg_rel, seg_len, nm, nlen)) {
        return true;
      }
      ii = ii + 1;
    }
    return false;
  }
}

/* See implementation. */
export function typeck_import_select_name_equal(module: *Module, imp_ix: i32, sel: i32, nm: *u8,
nm_len: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let sl: i32 = pipeline_module_import_select_name_len(module, imp_ix, sel);
    if (sl != nm_len || nm_len <= 0) {
      return false;
    }
    let i: i32 = 0;
    while (i < nm_len) {
      if (pipeline_module_import_select_name_byte_at(module, imp_ix, sel, i) != nm[i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/** Exported function `typeck_top_level_let_name_equal`.
 * Implements `typeck_top_level_let_name_equal`.
 * @param module *Module
 * @param tl_ix i32
 * @param nm *u8
 * @param nm_len i32
 * @return bool
 */
export function typeck_top_level_let_name_equal(module: *Module, tl_ix: i32, nm: *u8, nm_len: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let tll: i32 = pipeline_module_top_level_let_name_len(module, tl_ix);
    if (tll != nm_len || nm_len <= 0) {
      return false;
    }
    let i: i32 = 0;
    while (i < nm_len) {
      if (pipeline_module_top_level_let_name_byte_at(module, tl_ix, i) != nm[i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/** Exported function `typeck_dep_module_const_idx_named`.
 * Implements `typeck_dep_module_const_idx_named`.
 * @param module *Module
 * @param nm *u8
 * @param nlen i32
 * @param tl_ix i32
 * @return i32
 */
export function typeck_dep_module_const_idx_named(module: *Module, nm: *u8, nlen: i32, tl_ix: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (module == 0 as *Module || nm == 0 as *u8 || nlen <= 0) {
      return -1;
    }
    if (tl_ix >= module.num_top_level_lets) {
      return -1;
    }
    if (pipeline_module_top_level_let_is_const(module, tl_ix) != 0
    && typeck_top_level_let_name_equal(module, tl_ix, nm, nlen)) {
      return tl_ix;
    }
    return typeck_dep_module_const_idx_named(module, nm, nlen, tl_ix + 1);
  }
}

/* See implementation. */
export function typeck_find_import_const_dep_index(module: *Module, ctx: *PipelineDepCtx, nm: *u8, nlen: i32,
dep_ix: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dm: *Module = 0 as *Module;
    if (module == 0 as *Module || ctx == 0 as *PipelineDepCtx || nm == 0 as *u8 || nlen <= 0) {
      return -1;
    }
    if (dep_ix >= typeck_module_num_imports(module)) {
      return -1;
    }
    dm = pipeline_dep_ctx_module_at(ctx, dep_ix);
    if (dm != 0 as *Module && typeck_dep_module_const_idx_named(dm, nm, nlen, 0) >= 0) {
      return dep_ix;
    }
    return typeck_find_import_const_dep_index(module, ctx, nm, nlen, dep_ix + 1);
  }
}

/** Exported function `typeck_import_last_segment_into`.
 * Implements `typeck_import_last_segment_into`.
 * @param module *Module
 * @param imp_ix i32
 * @param out *u8
 * @return i32
 */
export function typeck_import_last_segment_into(module: *Module, imp_ix: i32, out: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let pl: i32 = 0;
    let start: i32 = 0;
    let i: i32 = 0;
    let seg_len: i32 = 0;
    if (module == 0 as *Module || out == 0 as *u8 || imp_ix < 0 || imp_ix >= typeck_module_num_imports(module)) {
      return 0;
    }
    pl = pipeline_module_import_path_len(module, imp_ix);
    if (pl <= 0 || pl > 127) {
      return 0;
    }
    while (i < pl) {
      if (pipeline_module_import_path_byte_at(module, imp_ix, i) == 46) {
        start = i + 1;
      }
      i = i + 1;
    }
    seg_len = pl - start;
    if (seg_len <= 0 || seg_len > 127) {
      return 0;
    }
    i = 0;
    while (i < seg_len) {
      out[i] = pipeline_module_import_path_byte_at(module, imp_ix, start + i);
      i = i + 1;
    }
    return seg_len;
  }
}

/** Exported function `typeck_resolve_dep_index_for_import`.
 * Implements `typeck_resolve_dep_index_for_import`.
 * @param module *Module
 * @param ctx *PipelineDepCtx
 * @param imp_ix i32
 * @return i32
 */
export function typeck_resolve_dep_index_for_import(module: *Module, ctx: *PipelineDepCtx, imp_ix: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let plen: i32 = 0;
    let dep_i: i32 = 0;
    let nd: i32 = 0;
    let path_buf: u8[128] = [];
    if (module == 0 as *Module || ctx == 0 as *PipelineDepCtx || imp_ix < 0 || imp_ix >= typeck_module_num_imports(module)) {
      return -1;
    }
    plen = pipeline_module_import_path_len(module, imp_ix);
    if (plen <= 0 || plen > 127) {
      return -1;
    }
    while (dep_i < plen) {
      path_buf[dep_i] = pipeline_module_import_path_byte_at(module, imp_ix, dep_i);
      dep_i = dep_i + 1;
    }
    nd = pipeline_dep_ctx_ndep(ctx);
    dep_i = 0;
    while (dep_i < nd) {
      let dep_plen: i32 = pipeline_dep_ctx_import_path_len(ctx, dep_i);
      if (dep_plen == plen) {
        let dep_buf: u8[128] = [];
        let eq: bool = true;
        let k: i32 = 0;
        pipeline_dep_ctx_import_path_copy64(ctx, dep_i, &dep_buf[0]);
        while (k < plen) {
          if (dep_buf[k] != path_buf[k]) {
            eq = false;
            break;
          }
          k = k + 1;
        }
        if (eq) {
          return dep_i;
        }
      }
      dep_i = dep_i + 1;
    }
    return -1;
  }
}

/** Exported function `typeck_import_const_binding_hint_at`.
 * Implements `typeck_import_const_binding_hint_at`.
 * @param module *Module
 * @param dep_ix i32
 * @param out *u8
 * @return i32
 */
export function typeck_import_const_binding_hint_at(module: *Module, dep_ix: i32, out: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let import_kind: i32 = 0;
    let bl: i32 = 0;
    let i: i32 = 0;
    if (module == 0 as *Module || out == 0 as *u8 || dep_ix < 0 || dep_ix >= typeck_module_num_imports(module)) {
      return 0;
    }
    import_kind = pipeline_module_import_kind_at(module, dep_ix);
    if (import_kind == 1) {
      bl = pipeline_module_import_binding_name_len(module, dep_ix);
      /* wave584 Cap residual: binding hint content ≤127 (binding_name[128]). */
      if (bl > 0 && bl <= 127) {
        while (i < bl) {
          out[i] = pipeline_module_import_binding_name_byte_at(module, dep_ix, i);
          i = i + 1;
        }
        return bl;
      }
    }
    return typeck_import_last_segment_into(module, dep_ix, out);
  }
}

/**
 * Reject bare VAR access to a dependency top-level const (must be binding.CONST).
 *
 * G.7 single authority for C VAR path (`pipeline_typeck_reject_bare_import_const_c`)
 * and `typeck_check_expr_var`. Reuses `typeck_find_import_const_dep_index` +
 * `typeck_import_const_binding_hint_at` +
 * `driver_diagnostic_typeck_import_const_must_be_qualified` — no second diag path.
 *
 * @param module *Module — entry module (import table for hint)
 * @param arena *ASTArena — for expr line/col
 * @param expr_ref i32 — VAR expr being resolved
 * @param ctx *PipelineDepCtx — loaded dependency modules
 * @param vbuf *u8 — bare identifier bytes
 * @param vnlen i32 — identifier length; must be > 0
 * @return i32 — 1 rejected (diag emitted), 0 not a bare import const
 * PLATFORM: SHARED
 */
export function typeck_reject_bare_import_const(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, vbuf: *u8, vnlen: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let const_dep_ix: i32 = -1;
    let hint_buf: u8[128] = [];
    let hint_len: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || vbuf == 0 as *u8 || vnlen <= 0 || expr_ref <= 0) {
      return 0;
    }
    const_dep_ix = typeck_find_import_const_dep_index(module, ctx, vbuf, vnlen, 0);
    if (const_dep_ix < 0) {
      return 0;
    }
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    hint_len = typeck_import_const_binding_hint_at(module, const_dep_ix, &hint_buf[0]);
    driver_diagnostic_typeck_import_const_must_be_qualified(line, col, vbuf, vnlen,
    &hint_buf[0], hint_len);
    return 1;
  }
}

/**
* See implementation.
*/
export function typeck_find_layout_idx_by_type_name(module: *Module, nm: *u8, nlen: i32): i32 {
  let k: i32 = 0;
  while (k < module.num_struct_layouts) {
    if (typeck_layout_name_equal(module, k, nm, nlen)) {
      return k;
    }
    k = k + 1;
  }
  return - 1;
}

/** Exported function `typeck_x_named_builtin_align`.
 * Implements `typeck_x_named_builtin_align`.
 * @param nm *u8
 * @param nlen i32
 * @return i32
 */
export function typeck_x_named_builtin_align(nm: *u8, nlen: i32): i32 {
  if (nm == 0 as *u8 || nlen <= 0) {
    return 0;
  }
  if (nlen == 3 && nm[0] == 105 && nm[1] == 51 && nm[2] == 50) { return 4; }
  if (nlen == 3 && nm[0] == 117 && nm[1] == 51 && nm[2] == 50) { return 4; }
  if (nlen == 4 && nm[0] == 98 && nm[1] == 111 && nm[2] == 111 && nm[3] == 108) { return 4; }
  if (nlen == 2 && nm[0] == 117 && nm[1] == 56) { return 1; }
  if (nlen == 3 && nm[0] == 105 && nm[1] == 54 && nm[2] == 52) { return 8; }
  if (nlen == 3 && nm[0] == 117 && nm[1] == 54 && nm[2] == 52) { return 8; }
  if (nlen == 5 && nm[0] == 117 && nm[1] == 115 && nm[2] == 105 && nm[3] == 122 && nm[4] == 101) { 
  return 8; }
  if (nlen == 5 && nm[0] == 105 && nm[1] == 115 && nm[2] == 105 && nm[3] == 122 && nm[4] == 101) { 
  return 8; }
  if (nlen == 3 && nm[0] == 102 && nm[1] == 51 && nm[2] == 50) { return 4; }
  if (nlen == 3 && nm[0] == 102 && nm[1] == 54 && nm[2] == 52) { return 8; }
  return 0;
}

/** Exported function `typeck_x_named_builtin_size`.
 * Implements `typeck_x_named_builtin_size`.
 * @param nm *u8
 * @param nlen i32
 * @return i32
 */
export function typeck_x_named_builtin_size(nm: *u8, nlen: i32): i32 {
  let a: i32 = typeck_x_named_builtin_align(nm, nlen);
  if (a == 1 && nlen == 2 && nm[0] == 117 && nm[1] == 56) { return 1; }
  if (a == 4) { return 4; }
  if (a == 8) { return 8; }
  return 0;
}

/** Exported function `typeck_x_type_align`.
 * Implements `typeck_x_type_align`.
 * @param module *Module
 * @param arena *ASTArena
 * @param ty_ref i32
 * @param depth i32
 * @return i32
 */
export function typeck_x_type_align(module: *Module, arena: *ASTArena, ty_ref: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ko: i32 = 0;
    let er: i32 = 0;
    let nm_len: i32 = 0;
    let li: i32 = 0;
    let ba: i32 = 0;
    let nm_buf: *u8 = typeck_scratch64_slot(4);
    if (ast.ref_is_null(ty_ref) || ty_ref <= 0 || ty_ref > arena.num_types || depth > 64) {
      return 1;
    }
    ko = pipeline_type_kind_ord_at(arena, ty_ref);
    if (ko == 2) {
      return 1;
    }
    if (ko == 0 || ko == 3 || ko == 1 || ko == 14) {
      return 4;
    }
    if (ko == 5 || ko == 4 || ko == 6 || ko == 7 || ko == 15 || ko == 9
        || ko == TypeKind.TYPE_FN as i32) {
      return 8;
    }
    if (ko == 11) {
      return 8;
    }
    /* See implementation. */
    if (ko == 10 || ko == 12 || ko == 13) {
      er = pipeline_type_elem_ref_at(arena, ty_ref);
      if (ast.ref_is_null(er)) {
        return 1;
      }
      return typeck_x_type_align(module, arena, er, depth + 1);
    }
    if (ko == 8) {
      /* See implementation. */
      nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf);
      li = typeck_find_layout_idx_by_type_name(module, nm_buf, nm_len);
      if (li >= 0) {
        return typeck_x_type_align_from_layout_glue(module, arena, li, depth + 1);
      }
      ba = typeck_x_named_builtin_align(nm_buf, nm_len);
      if (ba > 0) {
        return ba;
      }
      return 4;
    }
    return 1;
  }
}

/**
 * Return 1 when ty_ref is a TYPE_NAMED ZST layout: zero fields, or every field is
 * itself an empty struct (empty-of-empty nest). Host C sizeof Empty / NestEmpty is 0.
 * Layout metrics accept fsize==0 only when this returns 1; unknown types still fail.
 * @param module *Module — owning module for struct_layouts
 * @param arena *ASTArena — type pool for kind/name
 * @param ty_ref i32 — field or local type ref
 * @param depth i32 — recursion depth; >64 → 0 (cycle / absurd nest guard)
 * @return i32 — 1 empty named ZST layout, 0 otherwise
 * PLATFORM: SHARED — matches GCC empty-struct size 0 / A{e:Empty} nest ZST
 */
export function typeck_type_is_empty_struct(module: *Module, arena: *ASTArena, ty_ref: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ko: i32 = 0;
    let nm_len: i32 = 0;
    let li: i32 = 0;
    let nf: i32 = 0;
    let j: i32 = 0;
    let ftr: i32 = 0;
    let nm: *u8 = typeck_scratch64_slot(4);
    if (module == 0 as *Module || arena == 0 as *ASTArena || ty_ref <= 0) {
      return 0;
    }
    if (ty_ref > arena.num_types || depth > 64) {
      return 0;
    }
    ko = pipeline_type_kind_ord_at(arena, ty_ref);
    /* TYPE_NAMED ord == 8 */
    if (ko != 8) {
      return 0;
    }
    nm_len = pipeline_type_named_name_into(arena, ty_ref, nm);
    if (nm_len <= 0) {
      return 0;
    }
    li = typeck_find_layout_idx_by_type_name(module, nm, nm_len);
    if (li < 0) {
      return 0;
    }
    nf = pipeline_module_struct_layout_num_fields(module, li);
    /* wave366: nf==0 bare empty struct. */
    if (nf == 0) {
      return 1;
    }
    /* wave368: all fields empty ZSTs → nested empty-of-empty is also ZST. */
    j = 0;
    while (j < nf) {
      ftr = pipeline_module_struct_layout_field_type_ref(module, li, j);
      if (typeck_type_is_empty_struct(module, arena, ftr, depth + 1) == 0) {
        return 0;
      }
      j = j + 1;
    }
    return 1;
  }
}

/** Exported function `typeck_x_type_size`.
 * Implements `typeck_x_type_size`.
 * @param module *Module
 * @param arena *ASTArena
 * @param ty_ref i32
 * @param depth i32
 * @return i32
 */
export function typeck_x_type_size(module: *Module, arena: *ASTArena, ty_ref: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ko: i32 = 0;
    let er: i32 = 0;
    let asz: i32 = 0;
    let es: i32 = 0;
    let nm_len: i32 = 0;
    let li2: i32 = 0;
    let bsz: i32 = 0;
    let nm_buf_sz: *u8 = typeck_scratch64_slot(4);
    if (ast.ref_is_null(ty_ref) || ty_ref <= 0 || ty_ref > arena.num_types || depth > 64) {
      return 0;
    }
    ko = pipeline_type_kind_ord_at(arena, ty_ref);
    if (ko == 16) {
      return 0;
    }
    if (ko == 2) {
      return 1;
    }
    if (ko == 0 || ko == 3 || ko == 1 || ko == 14) {
      return 4;
    }
    if (ko == 5 || ko == 4 || ko == 6 || ko == 7 || ko == 15 || ko == 9
        || ko == TypeKind.TYPE_FN as i32) {
      return 8;
    }
    if (ko == 11) {
      return 16;
    }
    /* See implementation. */
    if (ko == 12) {
      er = pipeline_type_elem_ref_at(arena, ty_ref);
      if (ast.ref_is_null(er)) {
        return 0;
      }
      return typeck_x_type_size(module, arena, er, depth + 1);
    }
    if (ko == 10 || ko == 13) {
      er = pipeline_type_elem_ref_at(arena, ty_ref);
      asz = pipeline_type_array_size_at(arena, ty_ref);
      if (ast.ref_is_null(er) || asz <= 0) {
        return 0;
      }
      let soa_sz: i32 = typeck_soa_array_storage_size_glue(module, arena, er, asz, depth + 1);
      if (soa_sz > 0) {
        return soa_sz;
      }
      es = typeck_x_type_size(module, arena, er, depth + 1);
      if (es <= 0) {
        return 0;
      }
      return asz * es;
    }
    if (ko == 8) {
      nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf_sz);
      li2 = typeck_find_layout_idx_by_type_name(module, nm_buf_sz, nm_len);
      if (li2 >= 0) {
        return typeck_x_type_size_from_layout_glue(module, arena, li2, depth + 1);
      }
      bsz = typeck_x_named_builtin_size(nm_buf_sz, nm_len);
      if (bsz > 0) {
        return bsz;
      }
      return 4;
    }
    return 0;
  }
}

/**
 * R2 (8.3.3): SoA layout 按名查索引 — migrated from C bypass (pipeline_typeck_soa.c)
 * to .x authority. 按名比对 module 的 struct_layouts，命中返回 idx，未命中 -1。
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_find_layout_idx_by_name(module: *Module, name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    let j: i32 = 0;
    let ln: i32 = 0;
    let eq: i32 = 0;
    if (module == 0 as *Module || name == 0 as *u8 || name_len <= 0 || name_len > 127) {
      return -1;
    }
    k = 0;
    while (k < pipeline_module_num_struct_layouts_at(module)) {
      ln = pipeline_module_struct_layout_name_len(module, k);
      if (ln == name_len) {
        j = 0;
        eq = 1;
        while (j < name_len) {
          if (pipeline_module_struct_layout_name_byte_at(module, k, j) != name[j]) {
            eq = 0;
            break;
          }
          j = j + 1;
        }
        if (eq != 0) {
          return k;
        }
      }
      k = k + 1;
    }
    return -1;
  }
}

/**
 * R2 (8.3.3): Find SoA struct layout by name in the current module or the
 * WPO dep pool; on hit write the owning module into *out_layout_mod.
 *
 * Migrated from C static helper (pipeline_typeck_soa.c) to .x authority.
 * First probes the local module via typeck_soa_find_layout_idx_by_name; if
 * miss, walks pipeline_asm_emit_dep_pipe_c() deps with the same name probe.
 *
 * @param module *Module — primary module (also default *out_layout_mod)
 * @param name *u8 — layout / TYPE_NAMED bytes (not required to be NUL-terminated)
 * @param name_len i32 — byte count; must be > 0 (caller caps typically <= 127)
 * @param out_layout_mod **Module — optional out: module that owns the hit layout
 * @return i32 — layout index >= 0 on hit; -1 when not found / bad input
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_find_layout_module_and_idx(module: *Module, name: *u8, name_len: i32,
  out_layout_mod: **Module): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let li: i32 = 0;
    let pipe: *PipelineDepCtx = 0 as *PipelineDepCtx;
    let nd: i32 = 0;
    let di: i32 = 0;
    let dm: *Module = 0 as *Module;
    let om_bytes: *u8 = out_layout_mod as *u8;
    /* Default out owner to primary module when out pointer is non-null. */
    if (om_bytes != 0 as *u8) {
      out_layout_mod[0] = module;
    }
    if (module == 0 as *Module || name == 0 as *u8 || name_len <= 0) {
      return -1;
    }
    li = typeck_soa_find_layout_idx_by_name(module, name, name_len);
    if (li >= 0) {
      return li;
    }
    pipe = pipeline_asm_emit_dep_pipe_c();
    if (pipe == 0 as *PipelineDepCtx) {
      return -1;
    }
    nd = pipeline_dep_ctx_ndep(pipe);
    di = 0;
    while (di < nd) {
      dm = pipeline_dep_ctx_module_at(pipe, di);
      if (dm != 0 as *Module) {
        li = typeck_soa_find_layout_idx_by_name(dm, name, name_len);
        if (li >= 0) {
          if (om_bytes != 0 as *u8) {
            out_layout_mod[0] = dm;
          }
          return li;
        }
      }
      di = di + 1;
    }
    return -1;
  }
}

/**
 * R2 (8.3.3): SoA column base for field fi — columns before fi occupy
 * N * sizeof(field) with per-column align padding.
 *
 * Migrated from C bypass (pipeline_typeck_soa.c) to .x authority.
 * Uses typeck_x_type_align / typeck_x_type_size (G.7 twins) instead of
 * C glue_type_align_simple / glue_type_size_simple so SoA sizing no longer
 * depends on host-cc glue residual for field stride math.
 *
 * @param module *Module — layout owner module
 * @param arena *ASTArena — type arena
 * @param li i32 — struct_layouts index
 * @param field_idx i32 — exclusive end field index (0..num_fields)
 * @param array_len i32 — SoA array length N
 * @param depth i32 — recursion depth (cap 64; forwarded to type size/align)
 * @return i32 — byte offset of column base for field_idx (0 on bad input)
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_col_base_for_field(module: *Module, arena: *ASTArena, li: i32,
  field_idx: i32, array_len: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let col: i32 = 0;
    let j: i32 = 0;
    let nf: i32 = 0;
    let ftr: i32 = 0;
    let A: i32 = 0;
    let fsize: i32 = 0;
    let rem: i32 = 0;
    let gap: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || li < 0 || field_idx < 0 || array_len <= 0 || depth > 64) {
      return 0;
    }
    col = 0;
    nf = pipeline_module_struct_layout_num_fields(module, li);
    j = 0;
    while (j < nf && j < field_idx) {
      ftr = pipeline_module_struct_layout_field_type_ref(module, li, j);
      if (ftr > 0) {
        A = typeck_x_type_align(module, arena, ftr, depth);
        fsize = typeck_x_type_size(module, arena, ftr, depth);
        if (A <= 0) {
          A = 1;
        }
        if (fsize <= 0) {
          fsize = 4;
        }
        rem = col % A;
        gap = A - rem;
        gap = gap % A;
        col = col + gap + array_len * fsize;
      }
      j = j + 1;
    }
    return col;
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS with INDEX base — SoA `arr[i].field` stamps
 * col_base + stride on the field-access node.
 *
 * Migrated from C `pipeline_typeck_field_soa_index_c` (pipeline_typeck_soa.c)
 * to .x authority. Stride uses typeck_x_type_size (G.7 twin) instead of
 * host-cc glue_type_size_simple so column math no longer depends on glue residual.
 *
 * Contract:
 *  - Returns 1 when this is a SoA path and col_base/stride/type were written.
 *  - Returns 0 when not SoA / incomplete types / layout miss (caller falls back).
 *  - Skip-typeck VAR bases without resolved_type fall back to emit-func params
 *    then a full-module param scan (matches prior C behavior).
 *
 * @param module *Module — primary module (layouts may resolve via WPO deps)
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — field base; must be INDEX (kind ord 47) for SoA path
 * @return i32 — 1 handled SoA, 0 not handled
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_field_soa_index(module: *Module, arena: *ASTArena, expr_ref: i32,
  base_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ix_base_ref: i32 = 0;
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let elem_ty: i32 = 0;
    let array_sz: i32 = 0;
    let elem_nm: u8[128] = [];
    let elem_nlen: i32 = 0;
    let li: i32 = 0;
    let fl: i32 = 0;
    let fn_buf: u8[128] = [];
    let j: i32 = 0;
    let fnlen: i32 = 0;
    let ftr: i32 = 0;
    let col_base: i32 = 0;
    let stride: i32 = 0;
    let layout_mod: *Module = module;
    let fi: i32 = 0;
    let vname: u8[128] = [];
    let vlen: i32 = 0;
    let nfuncs: i32 = 0;
    let feq: i32 = 0;
    let bi: i32 = 0;
    let fb: u8[128] = [];
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 || base_ref <= 0) {
      return 0;
    }
    /* INDEX kind ord == 47 */
    if (pipeline_expr_kind_ord_at(arena, base_ref) != 47) {
      return 0;
    }
    ix_base_ref = pipeline_expr_index_base_ref(arena, base_ref);
    if (ix_base_ref <= 0) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, ix_base_ref);
    /* Skip-.x typeck: param VAR often lacks resolved_type; recover from emit func
     * formal table, then scan all module funcs (same as prior C path). */
    if (base_ty <= 0 && pipeline_expr_kind_ord_at(arena, ix_base_ref) == 3) {
      vlen = pipeline_expr_var_name_len(arena, ix_base_ref);
      if (vlen > 0 && vlen <= 127) {
        pipeline_expr_var_name_into(arena, ix_base_ref, &vname[0]);
        nfuncs = pipeline_module_num_funcs(module);
        fi = pipeline_asm_emit_func_index_c();
        if (fi >= 0 && fi < nfuncs) {
          base_ty = pipeline_module_func_param_type_ref_for_name(module, fi, &vname[0], vlen);
        }
        if (base_ty <= 0) {
          fi = 0;
          while (fi < nfuncs) {
            base_ty = pipeline_module_func_param_type_ref_for_name(module, fi, &vname[0], vlen);
            if (base_ty > 0) {
              break;
            }
            fi = fi + 1;
          }
        }
        if (base_ty > 0) {
          pipeline_expr_set_resolved_type_ref(arena, ix_base_ref, base_ty);
        }
      }
    }
    if (base_ty <= 0 || base_ty > arena.num_types) {
      return 0;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    /* TYPE_ARRAY=10, TYPE_ARRAY_SLICE-like storage=13 (product uses both). */
    if (bt_kind != 10 && bt_kind != 13) {
      return 0;
    }
    elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
    array_sz = pipeline_type_array_size_at(arena, base_ty);
    if (elem_ty <= 0 || array_sz <= 0) {
      return 0;
    }
    /* TYPE_NAMED ord == 8 */
    if (pipeline_type_kind_ord_at(arena, elem_ty) != 8) {
      return 0;
    }
    elem_nlen = pipeline_type_named_name_into(arena, elem_ty, &elem_nm[0]);
    if (elem_nlen <= 0 || elem_nlen > 127) {
      return 0;
    }
    li = typeck_soa_find_layout_module_and_idx(module, &elem_nm[0], elem_nlen, &layout_mod);
    if (li < 0 || layout_mod == 0 as *Module || pipeline_module_struct_layout_soa_at(layout_mod, li) == 0) {
      return 0;
    }
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    ftr = 0;
    stride = 0;
    col_base = 0;
    j = 0;
    while (j < pipeline_module_struct_layout_num_fields(layout_mod, li)) {
      fnlen = pipeline_module_struct_layout_field_name_len(layout_mod, li, j);
      if (fnlen == fl) {
        pipeline_module_struct_layout_field_name_into(layout_mod, li, j, &fb[0]);
        feq = 1;
        bi = 0;
        while (bi < fnlen) {
          if (fb[bi] != fn_buf[bi]) {
            feq = 0;
            break;
          }
          bi = bi + 1;
        }
        if (feq != 0) {
          ftr = pipeline_module_struct_layout_field_type_ref(layout_mod, li, j);
          /* G.7: stride from typeck_x_type_size authority (not glue_type_size_simple). */
          stride = typeck_x_type_size(layout_mod, arena, ftr, 0);
          if (stride <= 0) {
            stride = 4;
          }
          col_base = typeck_soa_col_base_for_field(layout_mod, arena, li, j, array_sz, 0);
          break;
        }
      }
      j = j + 1;
    }
    if (ftr <= 0) {
      return 0;
    }
    pipeline_expr_set_field_access_offset(arena, expr_ref, col_base);
    pipeline_expr_set_field_access_soa_stride(arena, expr_ref, stride);
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, ftr);
    return 1;
  }
}

/**
 * DOD-S1: SoAStruct[N] column-major total byte size; returns 0 when elem is
 * not SoA or layout not found.
 *
 * wave1219: migrated from C bypass (pipeline_typeck_soa.c) to .x authority.
 * Calls typeck_soa_find_layout_idx_by_name / typeck_soa_col_base_for_field
 * (.x authority after 8.3.3 R2). Uses typeck_x_type_align for the max-field-align
 * tail loop (G.7 twin, same semantics).
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param elem_type_ref i32 — candidate SoA struct element type_ref
 * @param array_len i32 — SoA array length N
 * @param depth i32 — recursion depth (cap 64)
 * @return i32 — column-major total bytes, or 0 if not SoA / not found
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_array_storage_size_glue(module: *Module, arena: *ASTArena, elem_type_ref: i32,
  array_len: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    let li: i32 = 0;
    let nf: i32 = 0;
    let col: i32 = 0;
    let max_al: i32 = 0;
    let j: i32 = 0;
    let ftr: i32 = 0;
    let A: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || elem_type_ref <= 0 || array_len <= 0 || depth > 64) {
      return 0;
    }
    /* TYPE_NAMED ord == 8 */
    if (pipeline_type_kind_ord_at(arena, elem_type_ref) != 8) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, elem_type_ref, &nm[0]);
    if (nlen <= 0 || nlen > 127) {
      return 0;
    }
    li = typeck_soa_find_layout_idx_by_name(module, &nm[0], nlen);
    if (li < 0 || pipeline_module_struct_layout_soa_at(module, li) == 0) {
      return 0;
    }
    /* Only when elem is a SoA struct: column-major size; non-SoA falls back to AoS. */
    nf = pipeline_module_struct_layout_num_fields(module, li);
    col = typeck_soa_col_base_for_field(module, arena, li, nf, array_len, depth + 1);
    max_al = 1;
    j = 0;
    while (j < nf) {
      ftr = pipeline_module_struct_layout_field_type_ref(module, li, j);
      if (ftr > 0) {
        A = typeck_x_type_align(module, arena, ftr, depth + 1);
        if (A > max_al) {
          max_al = A;
        }
      }
      j = j + 1;
    }
    if (max_al > 1 && (col % max_al) != 0) {
      col = col + (max_al - (col % max_al));
    }
    if (col > 0) {
      return col;
    }
    return 0;
  }
}

/**
* See implementation.
* See implementation.
*/
export function typeck_struct_layout_metrics(module: *Module, arena: *ASTArena, li: i32, depth: i32,
check_pad: i32, out_sz: *i32, out_al: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    /* See implementation. */
    let nf: i32 = 0;
    let allow: i32 = 0;
    let layout_nlen: i32 = 0;
    let current: i32 = 0;
    let max_align: i32 = 1;
    let j: i32 = 0;
    let ftr: i32 = 0;
    let flen: i32 = 0;
    let A: i32 = 0;
    let rem: i32 = 0;
    let gap: i32 = 0;
    let fsize: i32 = 0;
    let end_pad: i32 = 0;
    let fa: i32 = 0;
    /* See implementation. */
    let layout_nm: *u8 = typeck_scratch64_slot(2);
    let field_nm: *u8 = typeck_scratch64_slot(3);
    if (module == 0 as *Module || arena == 0 as *ASTArena || out_sz == 0 as *i32 || out_al == 0 as 
    *i32) {
      return - 1;
    }
    if (li < 0 || li >= pipeline_module_num_struct_layouts_at(module) || depth > 64) {
      return - 1;
    }
    nf = pipeline_module_struct_layout_num_fields(module, li);
    allow = pipeline_module_struct_layout_allow_padding_at(module, li);
    typeck_layout_name_into(module, li, layout_nm);
    layout_nlen = pipeline_module_struct_layout_name_len(module, li);
    current = 0;
    max_align = 1;
    /* See implementation. */
    if (pipeline_module_struct_layout_packed_at(module, li) != 0) {
      j = 0;
      while (j < nf) {
        ftr = pipeline_module_struct_layout_field_type_ref(module, li, j);
        fsize = typeck_x_type_size(module, arena, ftr, depth);
        /* wave366/368: fsize==0 OK for empty / empty-of-empty named ZST fields. */
        if (fsize < 0 || (fsize == 0 && typeck_type_is_empty_struct(module, arena, ftr, depth) == 0)) {
          /* See implementation. */
          if (check_pad != 0) {
            typeck_layout_field_name_into(module, li, j, field_nm);
            flen = pipeline_module_struct_layout_field_name_len(module, li, j);
            driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen);
          }
          return - 1;
        }
        current = current + fsize;
        j = j + 1;
      }
      typeck_i32_ptr_store(out_sz, current);
      typeck_i32_ptr_store(out_al, 1);
      return 0;
    }
    j = 0;
    while (j < nf) {
      ftr = pipeline_module_struct_layout_field_type_ref(module, li, j);
      typeck_layout_field_name_into(module, li, j, field_nm);
      flen = pipeline_module_struct_layout_field_name_len(module, li, j);
      fa = pipeline_module_struct_layout_field_align_at(module, li, j);
      A = typeck_x_type_align(module, arena, ftr, depth);
      if (A <= 0) {
        A = 1;
      }
      if (fa > A) {
        A = fa;
      }
      rem = current % A;
      gap = A - rem;
      gap = gap % A;
      if (check_pad != 0 && gap > 0 && allow == 0) {
        driver_diagnostic_typeck_struct_padding_before(layout_nm, layout_nlen, gap, field_nm, flen);
        return - 1;
      }
      current = current + gap;
      fsize = typeck_x_type_size(module, arena, ftr, depth);
      /* wave366/368: allow fsize==0 for empty / empty-of-empty named ZST fields. */
      if (fsize < 0 || (fsize == 0 && typeck_type_is_empty_struct(module, arena, ftr, depth) == 0)) {
        if (check_pad != 0) {
          driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen);
        }
        return - 1;
      }
      current = current + fsize;
      if (A > max_align) {
        max_align = A;
      }
      j = j + 1;
    }
    if (max_align > 0 && (current % max_align) != 0) {
      end_pad = max_align - (current % max_align);
      if (check_pad != 0 && end_pad > 0 && allow == 0) {
        driver_diagnostic_typeck_struct_padding_trailing(layout_nm, layout_nlen, end_pad);
        return - 1;
      }
      current = current + end_pad;
    }
    typeck_i32_ptr_store(out_sz, current);
    typeck_i32_ptr_store(out_al, max_align);
    return 0;
  }
}

/** Exported function `typeck_validate_struct_layouts_zero_padding`.
 * Implements `typeck_validate_struct_layouts_zero_padding`.
 * @param module *Module
 * @param arena *ASTArena
 * @return i32
 */
export function typeck_validate_struct_layouts_zero_padding(module: *Module, arena: *ASTArena): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let li: i32 = 0;
    let nsl: i32 = pipeline_module_num_struct_layouts_at(module);
    /* See implementation. */
    let sz_out: *i32 = typeck_layout_metrics_sz_slot();
    let al_out: *i32 = typeck_layout_metrics_al_slot();
    while (li < nsl) {
      typeck_layout_metrics_init_slot();
      if (typeck_struct_layout_metrics(module, arena, li, 0, 1, sz_out, al_out) != 0) {
        return - 1;
      }
      /* See implementation. */
      pipeline_typeck_pad_fields_warn_layout(module, arena, li);
      /* See implementation. */
      pipeline_typeck_hot_reorder_warn_layout(module, arena, li);
      li = li + 1;
    }
    return 0;
  }
}

/**
 * Stored layout field offset by type name + field name.
 * j==0 with stored 0 is a real first-field offset. j>0 with stored 0 is an
 * unsynced import-merge miss (gzip ZStream.zalloc) — return -1 so deps can
 * compute against the defining module+arena.
 * @param module *Module — layout table owner
 * @param type_name *u8 — struct type name bytes
 * @param type_name_len i32 — name length
 * @param field_name *u8 — field name bytes
 * @param field_name_len i32 — field name length
 * @return i32 — byte offset, or -1 on miss
 * PLATFORM: SHARED — Ubuntu gold gzip Init2; Darwin AAPCS64 uses the same table.
 */
export function get_field_offset_from_layout(module: *Module, type_name: *u8, type_name_len: i32,
field_name: *u8, field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    while (k < module.num_struct_layouts) {
      if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
        let j: i32 = 0;
        while (j < pipeline_module_struct_layout_num_fields(module, k)) {
          if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
            let stored: i32 = pipeline_module_struct_layout_field_offset_at(module, k, j);
            if (stored != 0) {
              return stored;
            }
            if (j == 0) {
              return 0;
            }
            return - 1;
          }
          j = j + 1;
        }
      }
      k = k + 1;
    }
    return - 1;
  }
}

/* See implementation. */
export function get_field_type_ref_from_layout(module: *Module, type_name: *u8, type_name_len: i32,
field_name: *u8, field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    while (k < module.num_struct_layouts) {
      if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
        let j: i32 = 0;
        while (j < pipeline_module_struct_layout_num_fields(module, k)) {
          if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
            return pipeline_module_struct_layout_field_type_ref(module, k, j);
          }
          j = j + 1;
        }
      }
      k = k + 1;
    }
    return 0;
  }
}

/**
 * Field offset: caller stored table, then each dep stored table, then
 * compute with the dep's own arena (field type_refs are dep-arena indices).
 * @param module *Module — caller / emit module
 * @param ctx *PipelineDepCtx — dep pipe; null skips dep walk
 * @param type_name *u8 — struct type name bytes
 * @param type_name_len i32 — name length
 * @param field_name *u8 — field name bytes
 * @param field_name_len i32 — field name length
 * @return i32 — byte offset, or -1 on miss
 * PLATFORM: SHARED — product import co-emit of gzip ZStream.
 */
export function get_field_offset_from_layout_deps(module: *Module, ctx: *PipelineDepCtx, type_name: *u8,
type_name_len: i32, field_name: *u8, field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let r: i32 = get_field_offset_from_layout(module, type_name, type_name_len, field_name,
    field_name_len);
    if (r >= 0) {
      return r;
    }
    if (ctx == 0 as *PipelineDepCtx) {
      return - 1;
    }
    let nd: i32 = pipeline_dep_ctx_ndep(ctx);
    let di: i32 = 0;
    while (di < nd) {
      let dm: *Module = pipeline_dep_ctx_module_at(ctx, di);
      if (dm != 0 as *Module) {
        r = get_field_offset_from_layout(dm, type_name, type_name_len, field_name, field_name_len);
        if (r >= 0) {
          return r;
        }
        /* Defining-module compute: skip-typeck / import merge leaves stored 0. */
        let darena: *ASTArena = pipeline_dep_ctx_arena_at(ctx, di);
        if (darena != 0 as *ASTArena) {
          let k: i32 = 0;
          let nsl: i32 = pipeline_module_num_struct_layouts_at(dm);
          while (k < nsl) {
            if (typeck_layout_name_equal(dm, k, type_name, type_name_len)) {
              r = glue_struct_layout_field_offset_by_name_c(dm, darena, k, field_name,
              field_name_len);
              if (r >= 0) {
                return r;
              }
            }
            k = k + 1;
          }
        }
      }
      di = di + 1;
    }
    return - 1;
  }
}

/**
 * Ensure module.struct_layouts has an entry for STRUCT_LIT expr_ref's type name.
 * Parser usually registered the layout already; this backfills missing fields when
 * parser only recorded a placeholder head. Called from typeck and from asm fill_cl
 * (skip-typeck STRUCT_LIT merge).
 *
 * wave369 Cap residual pure (PLATFORM: SHARED freestanding · LINUX gold):
 *   Prior append path always pushed STRUCT_LIT fields when name lookup missed.
 *   Mid/last nested Nest lit (`Box { a, n: Nest{e:Empty{}}, b }`) left Box layout
 *   scrambled (nf=4 names n/b/b/a, ftr mostly 0) → metrics fail, invent sz=24,
 *   field loads garbage. Root: (1) do not append when layout already has >= lit
 *   field count (parser complete); (2) re-read field name after expr_type_ref /
 *   next_field_offset — shared typeck_scratch64 slots can clobber field_nm.
 *   G.7: single authority ensure_struct_layout_from_struct_lit; seed typeck_gen
 *   same commit when regen.
 *
 * @param module *Module — owning struct_layouts table
 * @param arena *ASTArena — STRUCT_LIT expr pool
 * @param expr_ref i32 — EXPR_STRUCT_LIT ref; empty nf==0 is no-op (wave366 ZST)
 * @return i32 — 0 ok, -1 alloc failure
 */
export function ensure_struct_layout_from_struct_lit(module: *Module, arena: *ASTArena,
expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_fields: i32 = 0;
    let name_len: i32 = 0;
    let k: i32 = 0;
    let found_idx: i32 = -1;
    let idx_m: i32 = 0;
    let jm: i32 = 0;
    let fnlen_m: i32 = 0;
    let exists_m: i32 = 0;
    let tm: i32 = 0;
    let nf_layout: i32 = 0;
    let flen_tm: i32 = 0;
    let nf_m: i32 = 0;
    let ftr_m: i32 = 0;
    let init_rm: i32 = 0;
    let fr_m: i32 = 0;
    let idx: i32 = 0;
    let j: i32 = 0;
    let fnlen_j: i32 = 0;
    let ftr: i32 = 0;
    let init_r: i32 = 0;
    let fr: i32 = 0;
    let foff_m: i32 = 0;
    let foff_j: i32 = 0;
    let nsl: i32 = 0;
    let sname_len: i32 = 0;
    let lit_nm: *u8 = typeck_scratch64_slot(4);
    let layout_nm: *u8 = typeck_scratch64_slot(5);
    let field_nm: *u8 = typeck_scratch64_slot(6);
    let exist_nm: *u8 = typeck_scratch64_slot(7);
    if (expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref);
    /* wave366: Empty {} nf==0 — no fields to merge. */
    if (num_fields <= 0 || num_fields > 8) {
      return 0;
    }
    name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref);
    if (name_len <= 0 || name_len > 127) {
      return 0;
    }
    pipeline_expr_struct_lit_type_name_into(arena, expr_ref, lit_nm);
    nsl = pipeline_module_num_struct_layouts_at(module);
    k = 0;
    found_idx = -1;
    while (k < nsl) {
      pipeline_module_struct_layout_name_into(module, k, layout_nm);
      sname_len = pipeline_module_struct_layout_name_len(module, k);
      if (name_equal(layout_nm, sname_len, lit_nm, name_len)) {
        found_idx = k;
        break;
      }
      k = k + 1;
    }
    if (found_idx >= 0) {
      idx_m = found_idx;
      jm = 0;
      while (jm < num_fields) {
        pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm);
        fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm);
        exists_m = 0;
        tm = 0;
        nf_layout = pipeline_module_struct_layout_num_fields(module, idx_m);
        /*
         * wave369: parser already registered a full field set (nf >= lit fields).
         * Do not append — mid Nest STRUCT_LIT merge previously grew Box to nf=4
         * with scrambled names. Name-match update of type_ref is enough.
         */
        if (nf_layout >= num_fields) {
          return 0;
        }
        while (tm < nf_layout) {
          pipeline_module_struct_layout_field_name_into(module, idx_m, tm, exist_nm);
          flen_tm = pipeline_module_struct_layout_field_name_len(module, idx_m, tm);
          if (name_equal(exist_nm, flen_tm, field_nm, fnlen_m)) {
            exists_m = 1;
          }
          tm = tm + 1;
        }
        if (exists_m == 0) {
          nf_m = nf_layout;
          ftr_m = 0;
          init_rm = pipeline_expr_struct_lit_init_ref(arena, expr_ref, jm);
          if (!ast.ref_is_null(init_rm) && init_rm > 0 && init_rm <= arena.num_exprs) {
            fr_m = expr_type_ref(arena, init_rm);
            if (!ast.ref_is_null(fr_m)) {
              ftr_m = fr_m;
            }
          }
          foff_m = pipeline_struct_layout_next_field_offset(module, arena, idx_m, ftr_m);
          /* Re-read field name after helpers that reuse typeck_scratch64 slots. */
          pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm);
          fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm);
          pipeline_module_struct_layout_set_field(module, idx_m, nf_m, field_nm, fnlen_m, ftr_m,
          foff_m);
          pipeline_module_struct_layout_set_num_fields(module, idx_m, nf_m + 1);
        }
        jm = jm + 1;
      }
      return 0;
    }
    idx = pipeline_module_struct_layout_alloc(module);
    if (idx < 0) {
      return - 1;
    }
    pipeline_module_struct_layout_reset_slot(module, idx);
    pipeline_module_struct_layout_set_name(module, idx, lit_nm, name_len);
    pipeline_module_struct_layout_set_num_fields(module, idx, num_fields);
    j = 0;
    while (j < num_fields) {
      pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_nm);
      fnlen_j = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j);
      ftr = 0;
      init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j);
      if (!ast.ref_is_null(init_r) && init_r > 0 && init_r <= arena.num_exprs) {
        fr = expr_type_ref(arena, init_r);
        if (!ast.ref_is_null(fr)) {
          ftr = fr;
        }
      }
      foff_j = pipeline_struct_layout_next_field_offset(module, arena, idx, ftr);
      /* Re-read name after type/offset helpers (scratch slot safety). */
      pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_nm);
      fnlen_j = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j);
      pipeline_module_struct_layout_set_field(module, idx, j, field_nm, fnlen_j, ftr, foff_j);
      j = j + 1;
    }
    return 0;
  }
}

/**
 * R2 (8.3.3): Before asm emit, fill SoA col_base+stride and AoS layout
 * offsets for FIELD_ACCESS when C/X typeck was skipped or incomplete.
 *
 * Migrated from C `pipeline_fill_soa_field_access_for_asm_emit`
 * (pipeline_typeck_soa.c) to .x authority. Public surface name stays on a
 * thin C forwarder so runtime_pipeline_abi empty export / weak stubs do not
 * collide with a second no_mangle body.
 *
 * Steps (same as prior C):
 *  1. Merge STRUCT_LIT fields into module.struct_layouts
 *     (ensure_struct_layout_from_struct_lit authority).
 *  2. DOD-CL: inherit field_align from prior field when next is 0 and prior
 *     align >= 64 (align(N) column inheritance).
 *  3. Sync layout field offsets (glue_sync_struct_layout_field_offsets_c).
 *  4. Per non-extern func: bind emit func index, backfill VAR types from
 *     lets/params (skip-typeck INDEX base types).
 *  5. Per FIELD_ACCESS: SoA INDEX base → typeck_soa_field_soa_index; else
 *     stamp AoS layout offset unless soa_stride already set.
 *
 * @param module *Module — primary module (layouts + funcs)
 * @param arena *ASTArena — expr pool
 * @return void — no-op on null module/arena
 * PLATFORM: SHARED — G.7 single authority; .x -> typeck_gen.c -> typeck_x.o.
 */
export function typeck_soa_fill_field_access_for_asm_emit(module: *Module, arena: *ASTArena): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fi: i32 = 0;
    let ei: i32 = 0;
    let saved_fi: i32 = 0;
    let li: i32 = 0;
    let nf2: i32 = 0;
    let j: i32 = 0;
    let fa0: i32 = 0;
    let br: i32 = 0;
    let base_ref: i32 = 0;
    let flen: i32 = 0;
    let fname: u8[128] = [];
    let layout_off: i32 = 0;
    let nfuncs: i32 = 0;
    let nlayouts: i32 = 0;
    let nexprs: i32 = 0;
    let ens_rc: i32 = 0;
    let soa_rc: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena) {
      return;
    }
    pipeline_debug_trace_named_func_bodies("fill_cl_pre", module, arena);
    /* skip typeck: merge STRUCT_LIT fields into module.struct_layouts. */
    nexprs = arena.num_exprs;
    ei = 1;
    while (ei <= nexprs) {
      /* EXPR_STRUCT_LIT kind ord == 45 */
      if (pipeline_expr_kind_ord_at(arena, ei) == 45) {
        /* Discard return: merge failure is soft for skip-typeck emit path. */
        ens_rc = ensure_struct_layout_from_struct_lit(module, arena, ei);
        if (ens_rc != 0) {
          /* keep walking other STRUCT_LIT nodes */
        }
      }
      ei = ei + 1;
    }
    /* DOD-CL: inherit align(N) from field j onto j+1 when next align is 0. */
    nlayouts = pipeline_module_num_struct_layouts_at(module);
    li = 0;
    while (li < nlayouts) {
      nf2 = pipeline_module_struct_layout_num_fields(module, li);
      j = 0;
      while (j + 1 < nf2) {
        fa0 = pipeline_module_struct_layout_field_align_at(module, li, j);
        if (fa0 >= 64 && pipeline_module_struct_layout_field_align_at(module, li, j + 1) == 0) {
          pipeline_module_struct_layout_set_field_align(module, li, j + 1, fa0);
        }
        j = j + 1;
      }
      li = li + 1;
    }
    /* DOD-CL-S1: recompute field offsets from field_align, then fill FA. */
    glue_sync_struct_layout_field_offsets_c(module, arena);
    saved_fi = pipeline_asm_emit_func_index_c();
    nfuncs = pipeline_module_num_funcs(module);
    fi = 0;
    while (fi < nfuncs) {
      /* EMIT_HEAVY extern slots have no body/params; fill would SIGSEGV. */
      if (pipeline_module_func_is_extern_at(module, fi) != 0) {
        fi = fi + 1;
        continue;
      }
      br = pipeline_module_func_body_ref_at(module, fi);
      if (br <= 0) {
        fi = fi + 1;
        continue;
      }
      pipeline_asm_emit_set_func_index(fi);
      glue_fill_var_types_from_lets_in_block(arena, br);
      glue_fill_var_types_from_params_for_func(module, arena, fi);
      fi = fi + 1;
    }
    ei = 1;
    while (ei <= nexprs) {
      /* EXPR_FIELD_ACCESS kind ord == 44 */
      if (pipeline_expr_kind_ord_at(arena, ei) != 44) {
        ei = ei + 1;
        continue;
      }
      base_ref = pipeline_expr_field_access_base_ref(arena, ei);
      if (base_ref <= 0) {
        ei = ei + 1;
        continue;
      }
      /* INDEX kind ord == 47 → SoA arr[i].field */
      if (pipeline_expr_kind_ord_at(arena, base_ref) == 47) {
        /* Discard return: 0 means not-SoA; AoS offset path still runs below. */
        soa_rc = typeck_soa_field_soa_index(module, arena, ei, base_ref);
        if (soa_rc != 0) {
          /* SoA stamps already written */
        }
      }
      flen = pipeline_expr_field_access_name_len(arena, ei);
      if (flen <= 0 || flen > 127) {
        ei = ei + 1;
        continue;
      }
      pipeline_expr_field_access_name_into(arena, ei, &fname[0]);
      /* SoA path already wrote col_base+stride; do not overwrite with AoS off. */
      if (pipeline_expr_field_access_soa_stride(arena, ei) > 0) {
        ei = ei + 1;
        continue;
      }
      layout_off = glue_field_layout_offset_for_base_field(arena, module, base_ref, &fname[0], flen);
      if (layout_off >= 0) {
        pipeline_expr_set_field_access_offset(arena, ei, layout_off);
      }
      ei = ei + 1;
    }
    pipeline_asm_emit_set_func_index(saved_fi);
    pipeline_debug_trace_named_func_bodies("fill_cl_post", module, arena);
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS prebind for untyped VAR bases.
 *
 * Migrated from C `pipeline_typeck_field_prebind_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_prebind_c` remains a thin C forwarder for
 * field_access orchestration.
 *
 * When FIELD_ACCESS base is EXPR_VAR with null resolved_type_ref, and the name
 * is not a current-function formal, allocate/find a TYPE_NAMED with the same
 * spelling and stamp it on the base. This lets layout_named / known_ptr see a
 * type before full var resolution (self-host Lexer/Parser pattern: bare type
 * name used as temporary base).
 *
 * @param module *Module — param table for formal-name skip
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param ctx *PipelineDepCtx — current_func_index (null → skip formal check)
 * @return void
 * PLATFORM: SHARED — G.7; first knife in field_access orchestration order.
 */
export function typeck_field_prebind(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ref: i32 = 0;
    let vnlen: i32 = 0;
    let vbuf: u8[128] = [];
    let param_pre: i32 = 0;
    let nt_pre: i32 = 0;
    let fi: i32 = 0;
    if (arena == 0 as *ASTArena || module == 0 as *Module) {
      return;
    }
    base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref);
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return;
    }
    /* EXPR_VAR = 3 */
    if (pipeline_expr_kind_ord_at(arena, base_ref) != 3) {
      return;
    }
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
      return;
    }
    vnlen = pipeline_expr_var_name_len(arena, base_ref);
    if (vnlen <= 0 || vnlen > 127) {
      return;
    }
    pipeline_expr_var_name_into(arena, base_ref, &vbuf[0]);
    /* Skip prebind when name matches a formal (param already owns the type). */
    if (ctx != 0 as *PipelineDepCtx) {
      fi = pipeline_dep_ctx_current_func_index(ctx);
      if (fi >= 0 && fi < module.num_funcs) {
        param_pre = pipeline_module_func_param_type_ref_for_name(module, fi, &vbuf[0], vnlen);
        if (!ast.ref_is_null(param_pre)) {
          return;
        }
      }
    }
    nt_pre = find_or_alloc_named_type_ref(arena, &vbuf[0], vnlen);
    if (nt_pre != 0) {
      pipeline_expr_set_resolved_type_ref(arena, base_ref, nt_pre);
    }
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS hard-coded fields on *ASTArena / *Module.
 *
 * Migrated from C `pipeline_typeck_field_known_ptr_types_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_known_ptr_types_c` remains a thin C forwarder for
 * field_access orchestration.
 *
 * When the field base type is TYPE_PTR to a TYPE_NAMED "ASTArena" or "Module",
 * stamp resolved_type_ref (and for ASTArena, hard-coded byte offsets matching
 * the self-host arena / module layouts) for known SoA pool fields:
 *   ASTArena: types/num_types, exprs/num_exprs, blocks/num_blocks, funcs/num_funcs
 *   Module:   funcs, struct_layouts, num_funcs, num_struct_layouts
 * Offsets and array bounds are product ABI constants used by the compiler when
 * typechecking its own ASTArena/Module field access (self-host path).
 *
 * @param module *Module — reserved for ABI parity with C surface (unused body)
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — field base expr (must be *Named with resolved type)
 * @param num_struct_layouts i32 — diagnostic only (driver_diagnostic_typeck_ptr_field)
 * @return i32 — 1 = matched and stamped; 0 = not a known ptr field (continue)
 * PLATFORM: SHARED — G.7; layout offsets are ABI constants, not platform forks.
 */
export function typeck_field_known_ptr(module: *Module, arena: *ASTArena, expr_ref: i32,
base_ref: i32, num_struct_layouts: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let elem_ty: i32 = 0;
    let inner_nm_buf: u8[128] = [];
    let inner_nm_len: i32 = 0;
    let inner_ord: i32 = 0;
    let fl: i32 = 0;
    let fn_buf: u8[128] = [];
    /* "ASTArena" */
    let nm_astarena: u8[8] = [65, 83, 84, 65, 114, 101, 110, 97];
    /* "types" / "num_types" / "exprs" / "num_exprs" / "blocks" / "num_blocks" / "funcs" / "num_funcs" */
    let nm_types: u8[5] = [116, 121, 112, 101, 115];
    let nm_num_types: u8[9] = [110, 117, 109, 95, 116, 121, 112, 101, 115];
    let nm_exprs: u8[5] = [101, 120, 112, 114, 115];
    let nm_num_exprs: u8[9] = [110, 117, 109, 95, 101, 120, 112, 114, 115];
    let nm_blocks: u8[6] = [98, 108, 111, 99, 107, 115];
    let nm_num_blocks: u8[10] = [110, 117, 109, 95, 98, 108, 111, 99, 107, 115];
    let nm_funcs: u8[5] = [102, 117, 110, 99, 115];
    let nm_num_funcs: u8[9] = [110, 117, 109, 95, 102, 117, 110, 99, 115];
    /* array elem names: "Type" / "Expr" / "Block" / "Func" */
    let nm_ty: u8[4] = [84, 121, 112, 101];
    let nm_ex: u8[4] = [69, 120, 112, 114];
    let nm_bl: u8[5] = [66, 108, 111, 99, 107];
    let nm_fu: u8[4] = [70, 117, 110, 99];
    /* "Module" */
    let nm_module: u8[6] = [77, 111, 100, 117, 108, 101];
    /* Module fields reuse funcs/num_funcs; plus struct_layouts / num_struct_layouts */
    let nm_struct_layouts_m: u8[14] = [115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115];
    /* "num_struct_layouts" (18) */
    let nm_num_struct_layouts_m: u8[18] = [110, 117, 109, 95, 115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115];
    /* "StructLayout" */
    let nm_sl_m: u8[12] = [83, 116, 114, 117, 99, 116, 76, 97, 121, 111, 117, 116];
    let i32r_at: i32 = 0;
    let i32r_mod: i32 = 0;
    let matched: i32 = 0;
    let arr_ty: i32 = 0;
    /* `module` is ABI-only (C surface parity); body never dereferences it. */
    if (arena == 0 as *ASTArena) {
      return 0;
    }
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (ast.ref_is_null(base_ty) || base_ty <= 0 || base_ty > arena.num_types) {
      return 0;
    }
    /* TYPE_PTR = 9 */
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    if (bt_kind != 9) {
      return 0;
    }
    elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
    if (ast.ref_is_null(elem_ty)) {
      return 0;
    }
    inner_nm_len = pipeline_type_named_name_into(arena, elem_ty, &inner_nm_buf[0]);
    inner_ord = pipeline_type_kind_ord_at(arena, elem_ty);
    driver_diagnostic_typeck_ptr_field(9, inner_ord, inner_nm_len, base_ty, num_struct_layouts);
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    i32r_at = ensure_i32_type_ref(arena);
    i32r_mod = ensure_i32_type_ref(arena);
    matched = 0;
    /* TYPE_NAMED = 8; *ASTArena fields (hard-coded offsets). */
    if (inner_ord == 8 && inner_nm_len == 8 &&
    name_equal(&inner_nm_buf[0], inner_nm_len, &nm_astarena[0], 8)) {
      if (fl == 5 && name_equal(&fn_buf[0], fl, &nm_types[0], 5)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 0);
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_ty[0], 4, 512);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 9 && name_equal(&fn_buf[0], fl, &nm_num_types[0], 9)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 40960);
        if (i32r_at != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 5 && name_equal(&fn_buf[0], fl, &nm_exprs[0], 5)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 40968);
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_ex[0], 4, 32768);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 9 && name_equal(&fn_buf[0], fl, &nm_num_exprs[0], 9)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 6234120);
        if (i32r_at != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 6 && name_equal(&fn_buf[0], fl, &nm_blocks[0], 6)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 6234124);
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_bl[0], 5, 8192);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 10 && name_equal(&fn_buf[0], fl, &nm_num_blocks[0], 10)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 17184780);
        if (i32r_at != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 5 && name_equal(&fn_buf[0], fl, &nm_funcs[0], 5)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 17184784);
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_fu[0], 4, 256);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 9 && name_equal(&fn_buf[0], fl, &nm_num_funcs[0], 9)) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, 17371152);
        if (i32r_at != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at);
          matched = 1;
        }
      }
      if (matched != 0) {
        return 1;
      }
    }
    /* *Module fields (type only; offsets left for layout path). */
    if (inner_ord == 8 && inner_nm_len == 6 &&
    name_equal(&inner_nm_buf[0], inner_nm_len, &nm_module[0], 6)) {
      matched = 0;
      if (fl == 5 && name_equal(&fn_buf[0], fl, &nm_funcs[0], 5)) {
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_fu[0], 4, 256);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 14 && name_equal(&fn_buf[0], fl, &nm_struct_layouts_m[0], 14)) {
        arr_ty = ensure_array_type_ref_named_elem(arena, &nm_sl_m[0], 12, 32);
        if (arr_ty != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 9 && name_equal(&fn_buf[0], fl, &nm_num_funcs[0], 9)) {
        if (i32r_mod != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_mod);
          matched = 1;
        }
      }
      if (matched == 0 && fl == 18 && name_equal(&fn_buf[0], fl, &nm_num_struct_layouts_m[0], 18)) {
        if (i32r_mod != 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_mod);
          matched = 1;
        }
      }
    }
    if (matched != 0) {
      return 1;
    }
    return 0;
  }
}

/**
 * Match a top-level `const` in a dep module by name; write its type_ref.
 *
 * When the const has no `: Type` annotation (type_ref == 0), still match and
 * write 0 so the caller can stamp i32 from the *caller* arena (cross-module
 * type refs are not portable). Shared by import_binding resolve and bare
 * import-const diagnostics (G.7 single gate).
 *
 * @param dep_mod *Module — dependency module to scan
 * @param name *u8 — const identifier bytes
 * @param name_len i32 — byte length; must be > 0
 * @param out_type_ref *i32 — written on hit (may be 0 for untyped const)
 * @return i32 — 1 hit, 0 miss
 * PLATFORM: SHARED
 */
export function typeck_dep_top_level_const_match(dep_mod: *Module, name: *u8, name_len: i32,
out_type_ref: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let tl: i32 = 0;
    let ntl: i32 = 0;
    let tr: i32 = 0;
    if (dep_mod == 0 as *Module || name == 0 as *u8 || name_len <= 0 || out_type_ref == 0 as *i32) {
      return 0;
    }
    ntl = dep_mod.num_top_level_lets;
    while (tl < ntl) {
      if (pipeline_module_top_level_let_is_const(dep_mod, tl) != 0) {
        if (typeck_top_level_let_name_equal(dep_mod, tl, name, name_len)) {
          tr = pipeline_module_top_level_let_type_ref(dep_mod, tl);
          /* Allow tr==0: caller fills default (i32) in its arena. */
          *out_type_ref = tr;
          return 1;
        }
      }
      tl = tl + 1;
    }
    return 0;
  }
}

/**
 * Stamp import.Enum as TYPE_NAMED(enum) when field_name matches a dep enum.
 *
 * Single authority for both import-list and const-import sugar hops (G.7).
 * Also stamps base as TYPE_NAMED(base_name) when base is still untyped so the
 * outer `binding.Enum.Variant` hop can peel via layout_named.
 *
 * @param dep_mod *Module — dependency with module enum table
 * @param arena *ASTArena — caller arena for named type alloc
 * @param expr_ref i32 — FIELD_ACCESS expr to stamp
 * @param base_ref i32 — binding/base VAR expr
 * @param base_name *u8 — binding name bytes (for base TYPE_NAMED)
 * @param base_name_len i32 — binding name length
 * @param field_name *u8 — field spelling (enum type name)
 * @param field_name_len i32 — field name length
 * @return i32 — 1 hit, 0 miss
 * PLATFORM: SHARED
 */
export function typeck_field_import_try_dep_enum_type(dep_mod: *Module, arena: *ASTArena,
expr_ref: i32, base_ref: i32, base_name: *u8, base_name_len: i32, field_name: *u8,
field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ne: i32 = 0;
    let ek: i32 = 0;
    let el: i32 = 0;
    let bi: i32 = 0;
    let enum_ty: i32 = 0;
    let nt: i32 = 0;
    if (dep_mod == 0 as *Module || arena == 0 as *ASTArena || field_name == 0 as *u8 ||
    field_name_len <= 0) {
      return 0;
    }
    ne = dep_mod.num_module_enums;
    while (ek < ne) {
      el = pipeline_module_enum_name_len(dep_mod, ek);
      if (el == field_name_len && el > 0) {
        bi = 0;
        while (bi < el) {
          if (pipeline_module_enum_name_byte_at(dep_mod, ek, bi) != field_name[bi]) {
            break;
          }
          bi = bi + 1;
        }
        if (bi == el) {
          enum_ty = find_or_alloc_named_type_ref(arena, field_name, field_name_len);
          if (enum_ty != 0) {
            pipeline_expr_set_resolved_type_ref(arena, expr_ref, enum_ty);
          }
          if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
            if (base_name != 0 as *u8 && base_name_len > 0) {
              nt = find_or_alloc_named_type_ref(arena, base_name, base_name_len);
              if (nt != 0) {
                pipeline_expr_set_resolved_type_ref(arena, base_ref, nt);
              }
            }
          }
          return 1;
        }
      }
      ek = ek + 1;
    }
    return 0;
  }
}

/* Forward: remap a dep type_ref into the caller arena (body later). */
export extern function get_dep_return_type_in_caller_arena(from_dep_index: i32, dep_return_type_ref: i32,
caller_arena: *ASTArena, ctx: *PipelineDepCtx): i32;

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS import binding resolve.
 *
 * Migrated from C `pipeline_typeck_field_import_binding_resolve_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_import_binding_resolve_c` remains a thin C forwarder
 * for field_access orchestration (runs before base check_expr).
 *
 * When base is EXPR_VAR matching a whole-module import binding (e.g. `token`,
 * `backend`), resolve field against the dep module export surface:
 *  1) function → field expr type = function return type
 *  2) top-level const → field expr type = const type (or i32 if untyped)
 *  3) enum type name → TYPE_NAMED(enum) so `token.TokenKind.TOKEN_RETURN`
 *     can finish via layout_named + enum_variant_tag_for_names(deps)
 *
 * Wave702 residual: also match `const async_mod = import("std.async")` style
 * bindings (top-level const name equals base; scan all deps) for const + enum.
 *
 * @param module *Module — entry module (import list + top-level const sugar)
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — field base (must be EXPR_VAR)
 * @param ctx *PipelineDepCtx — dep modules aligned with import indices
 * @return i32 — 1 hit (resolved_type_ref stamped); 0 miss (continue field typeck)
 * PLATFORM: SHARED — G.7 single import-binding field gate.
 */
export function typeck_field_import_binding(module: *Module, arena: *ASTArena, expr_ref: i32,
base_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_name: u8[128] = [];
    let base_name_len: i32 = 0;
    let field_name: u8[128] = [];
    let field_name_len: i32 = 0;
    let i: i32 = 0;
    let n_imp: i32 = 0;
    let dep_mod: *Module = 0 as *Module;
    let j: i32 = 0;
    let nf: i32 = 0;
    let nd: i32 = 0;
    let ret_ty: i32 = 0;
    let const_ty: i32 = 0;
    let nt: i32 = 0;
    let ntl: i32 = 0;
    let tl: i32 = 0;
    let di: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || base_ref <= 0 ||
    ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    /* base must be EXPR_VAR (= 3) */
    if (pipeline_expr_kind_ord_at(arena, base_ref) != 3) {
      return 0;
    }
    base_name_len = pipeline_expr_var_name_len(arena, base_ref);
    if (base_name_len <= 0 || base_name_len > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, base_ref, &base_name[0]);
    field_name_len = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (field_name_len <= 0 || field_name_len > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &field_name[0]);
    /* Path A: import binding list — dep slot aligned with import index. */
    n_imp = module.num_imports;
    while (i < n_imp) {
      if (typeck_import_binding_name_equal(module, i, &base_name[0], base_name_len)) {
        dep_mod = 0 as *Module;
        nd = pipeline_dep_ctx_ndep(ctx);
        if (i < nd) {
          dep_mod = pipeline_dep_ctx_module_at(ctx, i);
        }
        if (dep_mod != 0 as *Module) {
          /* (1) dep function */
          nf = pipeline_module_num_funcs(dep_mod);
          j = 0;
          while (j < nf) {
            if (pipeline_module_func_name_equal_at(dep_mod, j, &field_name[0], field_name_len) != 0) {
              ret_ty = pipeline_module_func_return_type_at(dep_mod, j);
              if (ret_ty > 0) {
                pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty);
              }
              if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
                nt = find_or_alloc_named_type_ref(arena, &base_name[0], base_name_len);
                if (nt != 0) {
                  pipeline_expr_set_resolved_type_ref(arena, base_ref, nt);
                }
              }
              return 1;
            }
            j = j + 1;
          }
          /* (2) dep top-level const */
          const_ty = 0;
          if (typeck_dep_top_level_const_match(dep_mod, &field_name[0], field_name_len, &const_ty) != 0) {
            /* Cross-module type refs are not portable (see
             * typeck_dep_top_level_const_match). Untyped → i32 in the
             * caller arena; typed → remap via the existing dep-return
             * mapper (ARRAY/SLICE/named). Do not stamp a dep-arena
             * type_ref into the caller expr. */
            if (const_ty <= 0) {
              const_ty = ensure_i32_type_ref(arena);
            } else {
              const_ty = get_dep_return_type_in_caller_arena(i, const_ty, arena, ctx);
            }
            if (const_ty > 0) {
              pipeline_expr_set_resolved_type_ref(arena, expr_ref, const_ty);
            }
            if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
              nt = find_or_alloc_named_type_ref(arena, &base_name[0], base_name_len);
              if (nt != 0) {
                pipeline_expr_set_resolved_type_ref(arena, base_ref, nt);
              }
            }
            return 1;
          }
          /* (3) dep enum type as value namespace */
          if (typeck_field_import_try_dep_enum_type(dep_mod, arena, expr_ref, base_ref,
          &base_name[0], base_name_len, &field_name[0], field_name_len) != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    /*
     * Path B (wave702): const-import sugar `const m = import("path")`.
     * Top-level const name equals base; scan all deps for field const / enum
     * (import list may not register binding_name for this sugar).
     */
    ntl = module.num_top_level_lets;
    tl = 0;
    while (tl < ntl) {
      if (pipeline_module_top_level_let_is_const(module, tl) != 0) {
        if (typeck_top_level_let_name_equal(module, tl, &base_name[0], base_name_len)) {
          nd = pipeline_dep_ctx_ndep(ctx);
          di = 0;
          while (di < nd) {
            dep_mod = pipeline_dep_ctx_module_at(ctx, di);
            if (dep_mod != 0 as *Module) {
              const_ty = 0;
              if (typeck_dep_top_level_const_match(dep_mod, &field_name[0], field_name_len,
              &const_ty) != 0) {
                /* Same as Path A: remap typed dep const into caller arena. */
                if (const_ty <= 0) {
                  const_ty = ensure_i32_type_ref(arena);
                } else {
                  const_ty = get_dep_return_type_in_caller_arena(di, const_ty, arena, ctx);
                }
                if (const_ty > 0) {
                  pipeline_expr_set_resolved_type_ref(arena, expr_ref, const_ty);
                }
                if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
                  nt = find_or_alloc_named_type_ref(arena, &base_name[0], base_name_len);
                  if (nt != 0) {
                    pipeline_expr_set_resolved_type_ref(arena, base_ref, nt);
                  }
                }
                return 1;
              }
              if (typeck_field_import_try_dep_enum_type(dep_mod, arena, expr_ref, base_ref,
              &base_name[0], base_name_len, &field_name[0], field_name_len) != 0) {
                return 1;
              }
            }
            di = di + 1;
          }
        }
      }
      tl = tl + 1;
    }
    return 0;
  }
}

/**
 * True when FIELD is `binding.CONST` and CONST is a dep-module top-level const.
 *
 * Const-expr whitelist runs before check_expr, so it cannot wait for
 * typeck_field_import_binding to stamp. This predicate reuses that function's
 * Path A (import-list binding) and Path B (const-import sugar) walks, but
 * only the const match — dep functions and enum type names stay rejected
 * (they are not const-expr values). No resolved_type_ref stamp.
 *
 * @param module *Module — entry module (import list + top-level const sugar)
 * @param arena *ASTArena — expr arena (names only)
 * @param expr_ref i32 — EXPR_FIELD_ACCESS
 * @param ctx *PipelineDepCtx — dep modules; null → 0
 * @return i32 — 1 import-module const field, 0 otherwise
 * PLATFORM: SHARED — G.7 complete the existing const path of typeck_field_import_binding.
 */
export function typeck_field_import_const_is_const(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ref: i32 = 0;
    let base_name: u8[128] = [];
    let base_name_len: i32 = 0;
    let field_name: u8[128] = [];
    let field_name_len: i32 = 0;
    let i: i32 = 0;
    let n_imp: i32 = 0;
    let dep_mod: *Module = 0 as *Module;
    let nd: i32 = 0;
    let const_ty: i32 = 0;
    let ntl: i32 = 0;
    let tl: i32 = 0;
    let di: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 ||
    ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref);
    if (base_ref <= 0) {
      return 0;
    }
    /* base must be EXPR_VAR (= 3) */
    if (pipeline_expr_kind_ord_at(arena, base_ref) != 3) {
      return 0;
    }
    base_name_len = pipeline_expr_var_name_len(arena, base_ref);
    if (base_name_len <= 0 || base_name_len > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, base_ref, &base_name[0]);
    field_name_len = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (field_name_len <= 0 || field_name_len > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &field_name[0]);
    /* Path A: import binding list — dep slot aligned with import index. */
    n_imp = module.num_imports;
    while (i < n_imp) {
      if (typeck_import_binding_name_equal(module, i, &base_name[0], base_name_len)) {
        nd = pipeline_dep_ctx_ndep(ctx);
        dep_mod = 0 as *Module;
        if (i < nd) {
          dep_mod = pipeline_dep_ctx_module_at(ctx, i);
        }
        if (dep_mod != 0 as *Module) {
          const_ty = 0;
          if (typeck_dep_top_level_const_match(dep_mod, &field_name[0], field_name_len,
          &const_ty) != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    /*
     * Path B: const-import sugar `const m = import("path")`.
     * Top-level const name equals base; scan deps for field const only.
     */
    ntl = module.num_top_level_lets;
    tl = 0;
    while (tl < ntl) {
      if (pipeline_module_top_level_let_is_const(module, tl) != 0) {
        if (typeck_top_level_let_name_equal(module, tl, &base_name[0], base_name_len)) {
          nd = pipeline_dep_ctx_ndep(ctx);
          di = 0;
          while (di < nd) {
            dep_mod = pipeline_dep_ctx_module_at(ctx, di);
            if (dep_mod != 0 as *Module) {
              const_ty = 0;
              if (typeck_dep_top_level_const_match(dep_mod, &field_name[0], field_name_len,
              &const_ty) != 0) {
                return 1;
              }
            }
            di = di + 1;
          }
        }
      }
      tl = tl + 1;
    }
    return 0;
  }
}

/**
 * R2 (8.3.3): reverse-infer owner struct type of FIELD_ACCESS from field name.
 *
 * Migrated from C `pipeline_typeck_field_reverse_infer_base_type_c`
 * (pipeline_typeck_field_access.c) to .x authority. Used only by the field_access
 * orchestrator for CALL/METHOD_CALL bases.
 *
 * Why: ambient expected of `base.field` is the *field result* type (e.g. i32 for
 * `.v`), not the base type. Passing that into base typeck made bare ret-only
 * generic inference pin T=i32 for `return mk_default().v`, so CALL typed as i32
 * and `.v` became `?`.
 *
 * When exactly one module struct owns field `name`, return the named type_ref
 * for that struct so a bare generic CALL base can use it as expected_ret
 * (`mk_default()` → A). Zero or multiple hits → 0 (fail-closed).
 * outer_expected is reserved (parity with C; currently unused).
 *
 * @param module *Module — module with struct layouts
 * @param arena *ASTArena — type/name pool
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param outer_expected i32 — ambient expected of field result (reserved)
 * @return i32 — unique owner TYPE_NAMED ref, or 0
 * PLATFORM: SHARED — G.7 reverse-infer single authority.
 */
export function typeck_field_reverse_infer_base_type(module: *Module, arena: *ASTArena,
expr_ref: i32, outer_expected: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fn_buf: u8[128] = [];
    let fl: i32 = 0;
    let nsl: i32 = 0;
    let k: i32 = 0;
    let hits: i32 = 0;
    let unique_ty: i32 = 0;
    let nf: i32 = 0;
    let j: i32 = 0;
    let fjl: i32 = 0;
    let fjn: u8[128] = [];
    let bi: i32 = 0;
    let match_f: i32 = 0;
    let lnm: u8[128] = [];
    let lnl: i32 = 0;
    let nty: i32 = 0;
    /* outer_expected reserved (parity with prior C; currently unused — no (void) cast in X). */
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    nsl = pipeline_module_num_struct_layouts_at(module);
    if (nsl <= 0) {
      return 0;
    }
    hits = 0;
    unique_ty = 0;
    k = 0;
    while (k < nsl) {
      nf = pipeline_module_struct_layout_num_fields(module, k);
      j = 0;
      while (j < nf) {
        fjl = pipeline_module_struct_layout_field_name_len(module, k, j);
        if (fjl == fl) {
          pipeline_module_struct_layout_field_name_into(module, k, j, &fjn[0]);
          match_f = 1;
          bi = 0;
          while (bi < fl) {
            if (fjn[bi] != fn_buf[bi]) {
              match_f = 0;
              break;
            }
            bi = bi + 1;
          }
          if (match_f != 0) {
            lnl = pipeline_module_struct_layout_name_len(module, k);
            if (lnl > 0 && lnl <= 127) {
              pipeline_module_struct_layout_name_into(module, k, &lnm[0]);
              nty = find_or_alloc_named_type_ref(arena, &lnm[0], lnl);
              if (nty > 0) {
                /* Dedup same owner type (multiple fields same name should not happen). */
                if (!(hits == 1 && unique_ty == nty)) {
                  hits = hits + 1;
                  unique_ty = nty;
                  if (hits > 1) {
                    return 0; /* ambiguous owner — leave bare CALL unconstrained */
                  }
                }
              }
            }
          }
        }
        j = j + 1;
      }
      k = k + 1;
    }
    if (hits == 1) {
      return unique_ty;
    }
    return 0;
  }
}

/**
 * Byte offset of the last '.' segment in a TYPE_NAMED / layout spelling.
 * @param name *u8 — bytes; not required to be NUL-terminated
 * @param name_len i32 — byte count; <=0 → 0
 * @return i32 — 0 if no '.', else index after the last '.'
 * PLATFORM: SHARED — same last-dot strip as typeck_field_layout_named.
 */
function typeck_named_last_segment_off(name: *u8, name_len: i32): i32 {
  let i: i32 = 0;
  let off: i32 = 0;
  if (name == 0 as *u8 || name_len <= 0) {
    return 0;
  }
  while (i < name_len) {
    if (name[i] == 46 as u8) {
      off = i + 1;
    }
    i = i + 1;
  }
  return off;
}

/**
 * True if two type-name spellings are the same struct/enum.
 * Exact match, or last '.' segment (`heap.Allocator` vs layout `Allocator`).
 * @param a *u8 — TYPE_NAMED or layout bytes
 * @param a_len i32 — byte count of a
 * @param b *u8 — TYPE_NAMED or layout bytes
 * @param b_len i32 — byte count of b
 * @return i32 — 1 match, 0 no
 * PLATFORM: SHARED — G.7 helper for typeck_named_is_module_concrete only.
 */
function typeck_named_spelling_eq(a: *u8, a_len: i32, b: *u8, b_len: i32): i32 {
  let ao: i32 = 0;
  let bo: i32 = 0;
  let n: i32 = 0;
  let i: i32 = 0;
  if (a == 0 as *u8 || b == 0 as *u8 || a_len <= 0 || b_len <= 0) {
    return 0;
  }
  if (name_equal(a, a_len, b, b_len)) {
    return 1;
  }
  ao = typeck_named_last_segment_off(a, a_len);
  bo = typeck_named_last_segment_off(b, b_len);
  n = a_len - ao;
  if (n <= 0 || n != (b_len - bo)) {
    return 0;
  }
  while (i < n) {
    if (a[ao + i] != b[bo + i]) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}

/**
 * R2 (8.3.3): TYPE_NAMED name is a module (or dep) concrete struct/enum.
 *
 * Migrated from C `pipeline_typeck_named_is_module_concrete_c`
 * (pipeline_typeck_field_access.c). Public C surface remains a thin forwarder
 * for strict_minimal weak twin and any residual callers.
 *
 * wave465: free type-param vs concrete; wave1220 P4 walks dep modules so
 * TokenKind/Lexer etc. are not mistaken for free type params by ambient fill.
 * Import-qualified field types (`heap.Allocator`) must also count as concrete:
 * layout tables store the bare struct name (`Allocator`). Exact-only compare
 * treated `heap.Allocator` as a free type-param → apply_ambient stamped the
 * CALL return (`*u8`) onto `v.al` → heap.alloc scored -1 → first_idx
 * `alloc(i32):*u64`. Same last-dot strip as typeck_field_layout_named.
 * G.7 single probe — mono field path + ambient both use this.
 *
 * @param module *Module — entry module layouts/enums
 * @param ctx *PipelineDepCtx — optional deps (NULL/0 = local only; mono uses null)
 * @param name *u8 — TYPE_NAMED spelling (bare or import-qualified)
 * @param name_len i32 — name length (1..127)
 * @return i32 — 1 concrete, 0 free/unknown
 * PLATFORM: SHARED
 */
export function typeck_named_is_module_concrete(module: *Module, ctx: *PipelineDepCtx,
name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    let nsl: i32 = 0;
    let ne: i32 = 0;
    let sl: i32 = 0;
    let el: i32 = 0;
    let bi: i32 = 0;
    let snm: u8[128] = [];
    let nd: i32 = 0;
    let di: i32 = 0;
    let dm: *Module = 0 as *Module;
    if (module == 0 as *Module || name == 0 as *u8 || name_len <= 0 || name_len > 127) {
      return 0;
    }
    nsl = pipeline_module_num_struct_layouts_at(module);
    k = 0;
    while (k < nsl) {
      sl = pipeline_module_struct_layout_name_len(module, k);
      if (sl > 0 && sl <= 127) {
        pipeline_module_struct_layout_name_into(module, k, &snm[0]);
        if (typeck_named_spelling_eq(name, name_len, &snm[0], sl) != 0) {
          return 1;
        }
      }
      k = k + 1;
    }
    ne = module.num_module_enums;
    k = 0;
    while (k < ne) {
      el = pipeline_module_enum_name_len(module, k);
      if (el > 0 && el <= 127) {
        bi = 0;
        while (bi < el) {
          snm[bi] = pipeline_module_enum_name_byte_at(module, k, bi);
          bi = bi + 1;
        }
        if (typeck_named_spelling_eq(name, name_len, &snm[0], el) != 0) {
          return 1;
        }
      }
      k = k + 1;
    }
    /* wave1220 P4: dep modules for cross-module TokenKind / Lexer / Allocator. */
    if (ctx != 0 as *PipelineDepCtx) {
      nd = pipeline_dep_ctx_ndep(ctx);
      di = 0;
      while (di < nd) {
        dm = pipeline_dep_ctx_module_at(ctx, di);
        if (dm != 0 as *Module && dm != module) {
          nsl = pipeline_module_num_struct_layouts_at(dm);
          k = 0;
          while (k < nsl) {
            sl = pipeline_module_struct_layout_name_len(dm, k);
            if (sl > 0 && sl <= 127) {
              pipeline_module_struct_layout_name_into(dm, k, &snm[0]);
              if (typeck_named_spelling_eq(name, name_len, &snm[0], sl) != 0) {
                return 1;
              }
            }
            k = k + 1;
          }
          ne = dm.num_module_enums;
          k = 0;
          while (k < ne) {
            el = pipeline_module_enum_name_len(dm, k);
            if (el > 0 && el <= 127) {
              bi = 0;
              while (bi < el) {
                snm[bi] = pipeline_module_enum_name_byte_at(dm, k, bi);
                bi = bi + 1;
              }
              if (typeck_named_spelling_eq(name, name_len, &snm[0], el) != 0) {
                return 1;
              }
            }
            k = k + 1;
          }
        }
        di = di + 1;
      }
    }
    return 0;
  }
}

/**
 * R2 (8.3.3): mono free type-param field type against monomorphized base.
 *
 * Migrated from C `pipeline_typeck_mono_field_type_from_base_c`
 * (pipeline_typeck_field_access.c). G.7 single authority for field-access
 * apply_mono and STRUCT_LIT field-init coerce (wave466/467/682).
 *
 * When base is TYPE_NAMED with type-position args (`Wrap<i32>` / `Pair<A,B>`)
 * and field type is unconstrained TYPE_NAMED type-param (`v: T` / `b: U`),
 * map field name → layout type-param slot → type_arg[slot] (or elem_type_ref
 * for slot0 when no type-param registry).
 *
 * @param module *Module — layout type-param registry
 * @param arena *ASTArena — type / type-arg sidecar
 * @param field_ty i32 — layout field type_ref (often free TYPE_NAMED T/U)
 * @param base_ty i32 — monomorphized base (`Wrap<i32>`, `*Wrap<i32>`)
 * @return i32 — mono concrete type_ref, or 0 if no substitution
 * PLATFORM: SHARED
 */
export function typeck_mono_field_type_from_base(module: *Module, arena: *ASTArena,
field_ty: i32, base_ty: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let mono_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let gnm: u8[128] = [];
    let gnl: i32 = 0;
    let bnm: u8[128] = [];
    let bnl: i32 = 0;
    let sk: i32 = 0;
    let tp_slot: i32 = 0;
    let elem: i32 = 0;
    let nsl: i32 = 0;
    let sl: i32 = 0;
    let snm: u8[128] = [];
    let bi: i32 = 0;
    let match_b: i32 = 0;
    let ntp: i32 = 0;
    let tj: i32 = 0;
    let tpl: i32 = 0;
    let tpn: u8[128] = [];
    let pi: i32 = 0;
    let peq: i32 = 0;
    /* TYPE_PTR=9 TYPE_NAMED=8 */
    let ord_type_ptr: i32 = 9;
    let ord_type_named: i32 = 8;
    if (module == 0 as *Module || arena == 0 as *ASTArena) {
      return 0;
    }
    if (field_ty <= 0 || field_ty > arena.num_types) {
      return 0;
    }
    if (base_ty <= 0 || base_ty > arena.num_types) {
      return 0;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    if (bt_kind == ord_type_ptr) {
      elem = pipeline_type_elem_ref_at(arena, base_ty);
      if (elem > 0 && elem <= arena.num_types
      && pipeline_type_kind_ord_at(arena, elem) == ord_type_named) {
        base_ty = elem;
      } else {
        return 0;
      }
    } else if (bt_kind != ord_type_named) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, field_ty) != ord_type_named) {
      return 0;
    }
    gnl = pipeline_type_named_name_into(arena, field_ty, &gnm[0]);
    if (gnl <= 0 || gnl > 127) {
      return 0;
    }
    /* Local-only concrete check (ctx null) — mono does not walk deps. */
    if (typeck_named_is_module_concrete(module, 0 as *PipelineDepCtx, &gnm[0], gnl) != 0) {
      return 0;
    }
    bnl = pipeline_type_named_name_into(arena, base_ty, &bnm[0]);
    tp_slot = 0;
    if (bnl > 0) {
      nsl = pipeline_module_num_struct_layouts_at(module);
      sk = 0;
      while (sk < nsl) {
        sl = pipeline_module_struct_layout_name_len(module, sk);
        if (sl == bnl) {
          pipeline_module_struct_layout_name_into(module, sk, &snm[0]);
          match_b = 1;
          bi = 0;
          while (bi < bnl) {
            if (snm[bi] != bnm[bi]) {
              match_b = 0;
              break;
            }
            bi = bi + 1;
          }
          if (match_b != 0) {
            ntp = pipeline_module_struct_layout_num_type_params_at(module, sk);
            if (ntp > 0) {
              tp_slot = -1;
              tj = 0;
              while (tj < ntp) {
                tpl = pipeline_module_struct_layout_type_param_name_len(module, sk, tj);
                if (tpl == gnl) {
                  pipeline_module_struct_layout_type_param_name_into(module, sk, tj, &tpn[0]);
                  peq = 1;
                  pi = 0;
                  while (pi < gnl) {
                    if (tpn[pi] != gnm[pi]) {
                      peq = 0;
                      break;
                    }
                    pi = pi + 1;
                  }
                  if (peq != 0) {
                    tp_slot = tj;
                    break;
                  }
                }
                tj = tj + 1;
              }
              if (tp_slot < 0) {
                return 0;
              }
            }
            break;
          }
        }
        sk = sk + 1;
      }
    }
    mono_ty = pipeline_type_type_arg_ref_at(arena, base_ty, tp_slot);
    if (mono_ty <= 0 && tp_slot == 0) {
      mono_ty = pipeline_type_elem_ref_at(arena, base_ty);
    }
    if (mono_ty <= 0 || mono_ty > arena.num_types) {
      return 0;
    }
    return mono_ty;
  }
}

/**
 * R2 (8.3.3): hard-fail unknown field when base type is known field-bearing.
 *
 * Migrated from C `pipeline_typeck_field_unknown_hard_fail_c`
 * (pipeline_typeck_field_access.c). G.7 single gate — heavy field_access and
 * strict_minimal weak twin both call the C thin surface which forwards here.
 *
 * Soft residual: base type unknown (return 0). Resolved field type → already OK.
 * Hard-fail: slice/array/vector non-builtin fields; concrete/free TYPE_NAMED
 * miss; enum-only → enum has no variant; scalars → unknown field.
 * wave702: peel type aliases so `type P = Point` is concrete for the gate.
 *
 * @param module *Module — entry module layouts/enums
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_FIELD_ACCESS
 * @param base_ref i32 — field base expr
 * @param ctx *PipelineDepCtx — optional dep modules for cross-module layouts
 * @return i32 — 0 ok (resolved or soft-skip), -1 unknown field (diag emitted)
 * PLATFORM: SHARED
 */
export function typeck_field_unknown_hard_fail(module: *Module, arena: *ASTArena,
expr_ref: i32, base_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got_ty: i32 = 0;
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let check_ty: i32 = 0;
    let elem_ty: i32 = 0;
    let line_f: i32 = 0;
    let col_f: i32 = 0;
    let nlen: i32 = 0;
    let nbuf: u8[128] = [];
    let has_struct: i32 = 0;
    let has_enum: i32 = 0;
    let di: i32 = 0;
    let nd: i32 = 0;
    let dm: *Module = 0 as *Module;
    let k: i32 = 0;
    let nsl: i32 = 0;
    let ne: i32 = 0;
    let sl: i32 = 0;
    let el: i32 = 0;
    let bi: i32 = 0;
    let snm: u8[128] = [];
    let peeled: i32 = 0;
    let peeled_e: i32 = 0;
    /* TypeKind ord: NAMED=8 PTR=9 ARRAY=10 SLICE=11 VECTOR=13 (ast.x) */
    let ord_type_ptr: i32 = 9;
    let ord_type_named: i32 = 8;
    let ord_type_array: i32 = 10;
    let ord_type_slice: i32 = 11;
    let ord_type_vector: i32 = 13;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 || base_ref <= 0) {
      return 0;
    }
    got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    /* Resolved field type → already known member / enum variant / slice .length/.data. */
    if (!ast.ref_is_null(got_ty) && got_ty > 0 && got_ty <= arena.num_types) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (ast.ref_is_null(base_ty) || base_ty <= 0 || base_ty > arena.num_types) {
      return 0; /* soft: unknown base type */
    }
    /* wave702: peel type aliases so `type P = Point` is concrete for gate. */
    peeled = typeck_resolve_type_alias_ref_local(module, arena, base_ty, 0);
    if (!ast.ref_is_null(peeled) && peeled > 0 && peeled <= arena.num_types) {
      base_ty = peeled;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    check_ty = base_ty;
    /* Peel *S → S for layout/enum concrete check. */
    if (bt_kind == ord_type_ptr) {
      elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
      if (ast.ref_is_null(elem_ty) || elem_ty <= 0 || elem_ty > arena.num_types) {
        line_f = pipeline_expr_line_at(arena, expr_ref);
        col_f = pipeline_expr_col_at(arena, expr_ref);
        lsp_diag_report_typeck(line_f, col_f, "unknown field on this type");
        return -1;
      }
      peeled_e = typeck_resolve_type_alias_ref_local(module, arena, elem_ty, 0);
      if (!ast.ref_is_null(peeled_e) && peeled_e > 0 && peeled_e <= arena.num_types) {
        elem_ty = peeled_e;
      }
      check_ty = elem_ty;
      bt_kind = pipeline_type_kind_ord_at(arena, check_ty);
    }
    /* Slice / fixed array / vector: only .length / .data (slice) resolve above. */
    if (bt_kind == ord_type_slice || bt_kind == ord_type_array || bt_kind == ord_type_vector) {
      line_f = pipeline_expr_line_at(arena, expr_ref);
      col_f = pipeline_expr_col_at(arena, expr_ref);
      lsp_diag_report_typeck(line_f, col_f, "unknown field on this type");
      return -1;
    }
    if (bt_kind == ord_type_named) {
      nlen = pipeline_type_named_name_into(arena, check_ty, &nbuf[0]);
      if (nlen <= 0 || nlen > 127) {
        return 0;
      }
      has_struct = 0;
      has_enum = 0;
      nsl = pipeline_module_num_struct_layouts_at(module);
      ne = module.num_module_enums;
      k = 0;
      while (k < nsl) {
        sl = pipeline_module_struct_layout_name_len(module, k);
        if (sl == nlen) {
          pipeline_module_struct_layout_name_into(module, k, &snm[0]);
          bi = 0;
          while (bi < sl) {
            if (snm[bi] != nbuf[bi]) {
              break;
            }
            bi = bi + 1;
          }
          if (bi == sl) {
            has_struct = 1;
            break;
          }
        }
        k = k + 1;
      }
      k = 0;
      while (k < ne) {
        el = pipeline_module_enum_name_len(module, k);
        if (el == nlen) {
          bi = 0;
          while (bi < el) {
            if (pipeline_module_enum_name_byte_at(module, k, bi) != nbuf[bi]) {
              break;
            }
            bi = bi + 1;
          }
          if (bi == el) {
            has_enum = 1;
            break;
          }
        }
        k = k + 1;
      }
      /* Dep modules (import structs/enums). */
      if ((has_struct == 0 || has_enum == 0) && ctx != 0 as *PipelineDepCtx) {
        nd = pipeline_dep_ctx_ndep(ctx);
        di = 0;
        while (di < nd) {
          dm = pipeline_dep_ctx_module_at(ctx, di);
          if (dm != 0 as *Module) {
            if (has_struct == 0) {
              nsl = pipeline_module_num_struct_layouts_at(dm);
              k = 0;
              while (k < nsl) {
                sl = pipeline_module_struct_layout_name_len(dm, k);
                if (sl == nlen) {
                  pipeline_module_struct_layout_name_into(dm, k, &snm[0]);
                  bi = 0;
                  while (bi < sl) {
                    if (snm[bi] != nbuf[bi]) {
                      break;
                    }
                    bi = bi + 1;
                  }
                  if (bi == sl) {
                    has_struct = 1;
                    break;
                  }
                }
                k = k + 1;
              }
            }
            if (has_enum == 0) {
              ne = dm.num_module_enums;
              k = 0;
              while (k < ne) {
                el = pipeline_module_enum_name_len(dm, k);
                if (el == nlen) {
                  bi = 0;
                  while (bi < el) {
                    if (pipeline_module_enum_name_byte_at(dm, k, bi) != nbuf[bi]) {
                      break;
                    }
                    bi = bi + 1;
                  }
                  if (bi == el) {
                    has_enum = 1;
                    break;
                  }
                }
                k = k + 1;
              }
            }
            if (has_struct != 0 && has_enum != 0) {
              break;
            }
          }
          di = di + 1;
        }
      }
      /*
       * wave684: free type-param / incomplete TYPE_NAMED with no layout also
       * hard-fails (no fields). PLATFORM: SHARED.
       */
      if (has_struct == 0 && has_enum == 0) {
        line_f = pipeline_expr_line_at(arena, expr_ref);
        col_f = pipeline_expr_col_at(arena, expr_ref);
        lsp_diag_report_typeck(line_f, col_f, "unknown field on this type");
        return -1;
      }
      line_f = pipeline_expr_line_at(arena, expr_ref);
      col_f = pipeline_expr_col_at(arena, expr_ref);
      if (has_enum != 0 && has_struct == 0) {
        driver_diagnostic_typeck_enum_no_variant(line_f, col_f);
        return -1;
      }
      lsp_diag_report_typeck(line_f, col_f, "unknown field on this type");
      return -1;
    }
    /* Scalar / other first-class types: no fields. */
    line_f = pipeline_expr_line_at(arena, expr_ref);
    col_f = pipeline_expr_col_at(arena, expr_ref);
    lsp_diag_report_typeck(line_f, col_f, "unknown field on this type");
    return -1;
  }
}

/**
 * R2 (8.3.3): after layout/fallback, mono free type-param field result against
 * monomorphized base (`Wrap<i32>.v` → i32).
 *
 * Migrated from C `pipeline_typeck_field_apply_mono_type_arg_c`. Mono substitution
 * authority is `typeck_mono_field_type_from_base` (shared with STRUCT_LIT coerce —
 * G.7 single mono map).
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ty i32 — resolved base type (may be *Named or Named)
 * @return void
 * PLATFORM: SHARED
 */
export function typeck_field_apply_mono_type_arg(module: *Module, arena: *ASTArena,
expr_ref: i32, base_ty: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got_ty: i32 = 0;
    let mono_ty: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return;
    }
    got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    if (ast.ref_is_null(got_ty) || got_ty <= 0 || got_ty > arena.num_types) {
      return;
    }
    mono_ty = typeck_mono_field_type_from_base(module, arena, got_ty, base_ty);
    if (mono_ty <= 0 || mono_ty == got_ty) {
      return;
    }
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, mono_ty);
  }
}

/**
 * R2 (8.3.3): stamp ambient expected onto free type-param field results.
 *
 * Migrated from C `pipeline_typeck_field_apply_ambient_for_type_param_c`.
 * Only stamps when field type is TYPE_NAMED whose name is NOT a module/dep
 * concrete struct/enum (via `typeck_named_is_module_concrete`) and NOT a
 * builtin SIMD spelling (`typeck_vector_lanes_of_type` > 0).
 * Null/unknown field types are left unresolved (wave472: never invent ambient).
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param ambient_ty i32 — outer expected type of the field expression
 * @param ctx *PipelineDepCtx — dep modules for concrete-name check
 * @return void
 * PLATFORM: SHARED
 */
export function typeck_field_apply_ambient_for_type_param(module: *Module, arena: *ASTArena,
expr_ref: i32, ambient_ty: i32, ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got_ty: i32 = 0;
    let use_ambient: i32 = 0;
    let gnm: u8[128] = [];
    let gnl: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return;
    }
    if (ambient_ty <= 0 || ambient_ty > arena.num_types) {
      return;
    }
    got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    /* wave472: null/unknown field type → leave unresolved; never invent ambient. */
    if (ast.ref_is_null(got_ty) || got_ty <= 0 || got_ty > arena.num_types) {
      return;
    }
    /* Builtin SIMD named (i32x4 / f32x4 / Vec4f / …) is concrete, not a
     * free type-param. named_is_module_concrete only walks struct/enum
     * layouts, so i32x4 returned 0 and this helper stamped the outer
     * ambient (i32 from `return h.v[1]` / `let x: i32 = h.v`) over the
     * field type. INDEX then saw an i32 base → T001; `return h.v` as
     * i32 was a false green (lane0).
     * G.7: typeck_vector_lanes_of_type is the SIMD classifier.
     * Do not overwrite a SIMD field with a scalar ambient.
     * PLATFORM: SHARED — Ubuntu gold; Darwin ARM64 is the live fail. */
    if (typeck_vector_lanes_of_type(arena, got_ty) > 0) {
      return;
    }
    /* TYPE_NAMED = 8 */
    if (pipeline_type_kind_ord_at(arena, got_ty) == 8) {
      gnl = pipeline_type_named_name_into(arena, got_ty, &gnm[0]);
      /* wave587: TYPE_NAMED content ≤127; prior gnl<=63 skipped long concrete names. */
      if (gnl > 0 && gnl <= 127) {
        if (typeck_named_is_module_concrete(module, ctx, &gnm[0], gnl) == 0) {
          use_ambient = 1;
        }
      }
    }
    if (use_ambient != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ambient_ty);
    }
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS named-type layout / enum / TypeKind / TokenKind.
 *
 * Migrated from C `pipeline_typeck_field_layout_named_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_layout_named_c` remains a thin C forwarder for
 * field_access orchestration and strict_glue / seed call sites.
 *
 * Semantics (G.7 single authority):
 *  - Peel type aliases on base (and PTR pointee) before layout name lookup.
 *  - TYPE_PTR(*Named) or TYPE_NAMED → layout type name.
 *  - User enum variant: stamp enum_variant tag + resolved TYPE_NAMED(enum); return 2
 *    so the orchestrator short-circuits further fallbacks.
 *  - TypeKind.TYPE_* builtin variants: stamp tag + i32 type; skip struct layout.
 *  - Strip last `mod.` prefix on qualified type names so dep layouts match bare names.
 *  - Layout field offset + field type via get_field_*_from_layout_deps.
 *  - TokenKind.TOKEN_EOF residual special-case when layout miss.
 *
 * @param module *Module — entry + dep enum / layout tables
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — field base expr (resolved type required)
 * @param ctx *PipelineDepCtx — dep walk for cross-module layouts (null-safe)
 * @return i32 — 2 = user enum done (caller returns 0); 0 = continue field fallbacks
 * PLATFORM: SHARED — G.7; import-qualified type name strip at this single gate.
 */
export function typeck_field_layout_named(module: *Module, arena: *ASTArena, expr_ref: i32,
base_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let layout_named_ref: i32 = 0;
    let layout_nm_buf: u8[128] = [];
    let layout_nm_len: i32 = 0;
    let fn_buf: u8[128] = [];
    let fl2: i32 = 0;
    let user_ev_tag: i32 = 0;
    /* "TypeKind" */
    let nm_type_kind_ty: u8[8] = [84, 121, 112, 101, 75, 105, 110, 100];
    let skip_layout_for_type_kind: i32 = 0;
    let vv: i32 = 0;
    let off: i32 = 0;
    let ftr: i32 = 0;
    let i32r_tk: i32 = 0;
    let i32r_eof: i32 = 0;
    /* "TokenKind" */
    let nm_tok_kind_ty: u8[9] = [84, 111, 107, 101, 110, 75, 105, 110, 100];
    /* "TOKEN_EOF" */
    let nm_eof_variant: u8[9] = [84, 79, 75, 69, 78, 95, 69, 79, 70];
    let elem_ty: i32 = 0;
    let peeled: i32 = 0;
    let peeled_e: i32 = 0;
    let dot_pos: i32 = 0;
    let si: i32 = 0;
    let suffix_len: i32 = 0;
    /* TypeKind variant spellings */
    let s_i32: u8[8] = [84, 121, 112, 101, 95, 73, 51, 50];
    let s_bool: u8[9] = [84, 121, 112, 101, 95, 66, 79, 79, 76];
    let s_u8: u8[7] = [84, 121, 112, 101, 95, 85, 56];
    let s_u32: u8[8] = [84, 121, 112, 101, 95, 85, 51, 50];
    let s_u64: u8[8] = [84, 121, 112, 101, 95, 85, 54, 52];
    let s_i64: u8[8] = [84, 121, 112, 101, 95, 73, 54, 52];
    let s_usize: u8[10] = [84, 121, 112, 101, 95, 85, 83, 73, 90, 69];
    let s_isize: u8[10] = [84, 121, 112, 101, 95, 73, 83, 73, 90, 69];
    let s_named: u8[10] = [84, 121, 112, 101, 95, 78, 65, 77, 69, 68];
    let s_ptr: u8[8] = [84, 121, 112, 101, 95, 80, 84, 82];
    let s_arr: u8[10] = [84, 121, 112, 101, 95, 65, 82, 82, 65, 89];
    let s_sli: u8[10] = [84, 121, 112, 101, 95, 83, 76, 73, 67, 69];
    let s_vec: u8[11] = [84, 121, 112, 101, 95, 86, 69, 67, 84, 79, 82];
    let s_f32: u8[8] = [84, 121, 112, 101, 95, 70, 51, 50];
    let s_f64: u8[8] = [84, 121, 112, 101, 95, 70, 54, 52];
    let s_void: u8[9] = [84, 121, 112, 101, 95, 86, 79, 73, 68];

    if (arena == 0 as *ASTArena || module == 0 as *Module) {
      return 0;
    }
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (ast.ref_is_null(base_ty) || base_ty <= 0 || base_ty > arena.num_types) {
      return 0;
    }
    /* Peel type aliases so `type P = Point; p.x` uses Point layout. */
    peeled = typeck_resolve_type_alias_ref_local(module, arena, base_ty, 0);
    if (!ast.ref_is_null(peeled) && peeled > 0 && peeled <= arena.num_types) {
      base_ty = peeled;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    layout_named_ref = 0;
    /* TYPE_PTR = 9: peel pointee; TYPE_NAMED = 8. */
    if (bt_kind == 9) {
      elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
      if (!ast.ref_is_null(elem_ty) && elem_ty > 0) {
        peeled_e = typeck_resolve_type_alias_ref_local(module, arena, elem_ty, 0);
        if (!ast.ref_is_null(peeled_e) && peeled_e > 0 && peeled_e <= arena.num_types) {
          elem_ty = peeled_e;
        }
      }
      if (!ast.ref_is_null(elem_ty) && pipeline_type_kind_ord_at(arena, elem_ty) == 8) {
        layout_named_ref = elem_ty;
      }
    } else if (bt_kind == 8) {
      layout_named_ref = base_ty;
    }
    if (layout_named_ref == 0) {
      return 0;
    }
    layout_nm_len = pipeline_type_named_name_into(arena, layout_named_ref, &layout_nm_buf[0]);
    if (layout_nm_len <= 0 || pipeline_type_kind_ord_at(arena, layout_named_ref) != 8) {
      return 0;
    }
    fl2 = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl2 <= 0 || fl2 > 127) {
      return 0;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    user_ev_tag = pipeline_module_enum_variant_tag_for_names(module, &layout_nm_buf[0],
    layout_nm_len, &fn_buf[0], fl2);
    if (user_ev_tag >= 0) {
      /* User enum variant: resolved TYPE_NAMED(enum); codegen uses tag for discriminant. */
      pipeline_expr_set_field_access_enum_variant(arena, expr_ref, user_ev_tag);
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, layout_named_ref);
      return 2;
    }
    vv = -1;
    skip_layout_for_type_kind = 0;
    if (layout_nm_len == 8 && name_equal(&layout_nm_buf[0], layout_nm_len, &nm_type_kind_ty[0], 8)) {
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_i32[0], 8)) {
        vv = 0;
      }
      if (vv < 0 && fl2 == 9 && name_equal(&fn_buf[0], fl2, &s_bool[0], 9)) {
        vv = 1;
      }
      if (vv < 0 && fl2 == 7 && name_equal(&fn_buf[0], fl2, &s_u8[0], 7)) {
        vv = 2;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_u32[0], 8)) {
        vv = 3;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_u64[0], 8)) {
        vv = 4;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_i64[0], 8)) {
        vv = 5;
      }
      if (vv < 0 && fl2 == 10 && name_equal(&fn_buf[0], fl2, &s_usize[0], 10)) {
        vv = 6;
      }
      if (vv < 0 && fl2 == 10 && name_equal(&fn_buf[0], fl2, &s_isize[0], 10)) {
        vv = 7;
      }
      if (vv < 0 && fl2 == 10 && name_equal(&fn_buf[0], fl2, &s_named[0], 10)) {
        vv = 8;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_ptr[0], 8)) {
        vv = 9;
      }
      if (vv < 0 && fl2 == 10 && name_equal(&fn_buf[0], fl2, &s_arr[0], 10)) {
        vv = 10;
      }
      if (vv < 0 && fl2 == 10 && name_equal(&fn_buf[0], fl2, &s_sli[0], 10)) {
        vv = 11;
      }
      if (vv < 0 && fl2 == 11 && name_equal(&fn_buf[0], fl2, &s_vec[0], 11)) {
        vv = 12;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_f32[0], 8)) {
        vv = 13;
      }
      if (vv < 0 && fl2 == 8 && name_equal(&fn_buf[0], fl2, &s_f64[0], 8)) {
        vv = 14;
      }
      if (vv < 0 && fl2 == 9 && name_equal(&fn_buf[0], fl2, &s_void[0], 9)) {
        vv = 15;
      }
      if (vv >= 0) {
        i32r_tk = ensure_i32_type_ref(arena);
        if (i32r_tk != 0) {
          pipeline_expr_set_field_access_enum_variant(arena, expr_ref, vv);
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_tk);
        }
        skip_layout_for_type_kind = 1;
      }
    }
    off = -1;
    ftr = 0;
    if (skip_layout_for_type_kind == 0) {
      /*
       * Strip import-binding qualification: "lexer.Lexer" → "Lexer" so layout
       * tables registered under bare struct names match. Last '.' only.
       */
      dot_pos = -1;
      si = 0;
      while (si < layout_nm_len) {
        if (layout_nm_buf[si] == 46) {
          /* '.' */
          dot_pos = si;
        }
        si = si + 1;
      }
      if (dot_pos >= 0 && dot_pos + 1 < layout_nm_len) {
        suffix_len = layout_nm_len - (dot_pos + 1);
        si = 0;
        while (si < suffix_len) {
          layout_nm_buf[si] = layout_nm_buf[dot_pos + 1 + si];
          si = si + 1;
        }
        layout_nm_buf[suffix_len] = 0;
        layout_nm_len = suffix_len;
      }
      off = get_field_offset_from_layout_deps(module, ctx, &layout_nm_buf[0], layout_nm_len,
      &fn_buf[0], fl2);
      if (off >= 0) {
        pipeline_expr_set_field_access_offset(arena, expr_ref, off);
      }
      ftr = get_field_type_ref_from_layout_deps(module, arena, ctx, &layout_nm_buf[0],
      layout_nm_len, &fn_buf[0], fl2);
      if (ftr != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ftr);
      }
    }
    if (off < 0 && ftr == 0 && layout_nm_len == 9 &&
    name_equal(&layout_nm_buf[0], layout_nm_len, &nm_tok_kind_ty[0], 9) && fl2 == 9 &&
    name_equal(&fn_buf[0], fl2, &nm_eof_variant[0], 9)) {
      i32r_eof = ensure_i32_type_ref(arena);
      if (i32r_eof != 0) {
        pipeline_expr_set_field_access_enum_variant(arena, expr_ref, 0);
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_eof);
      }
    }
    return 0;
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS built-in field typing for slices / fixed arrays /
 * SIMD vectors.
 *
 * Migrated from C `pipeline_typeck_field_slice_c` (pipeline_typeck_field_access.c)
 * to .x authority. Public surface `pipeline_typeck_field_slice_c` remains a thin
 * C forwarder so EMIT_HEAVY field_access orchestration keeps the same call name.
 *
 * Semantics (G.7 single authority; match asm emit fat layout):
 *  - TYPE_ARRAY / TYPE_VECTOR `.length` → usize when array_size > 0; no offset
 *    stamp (compile-time N; emit must not load from stack).
 *  - TYPE_SLICE `.length` → usize + field_access_offset = 8 (fat second word).
 *  - TYPE_SLICE `.data` → *elem + field_access_offset = 0.
 *
 * @param arena *ASTArena — expr/type arena (null → no-op)
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — field base expr (must have resolved_type_ref)
 * @return void
 * PLATFORM: SHARED — G.7; data@0 length@8 fat layout shared with asm emit.
 */
export function typeck_field_slice(arena: *ASTArena, expr_ref: i32, base_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ty: i32 = 0;
    let elem_ty: i32 = 0;
    let fl: i32 = 0;
    let bt_kind: i32 = 0;
    let fn_buf: u8[128] = [];
    /* "length" / "data" as byte arrays (no string lit dependence). */
    let len_nm: u8[6] = [108, 101, 110, 103, 116, 104];
    let dat_nm: u8[4] = [100, 97, 116, 97];
    let ut: i32 = 0;
    let ptr_ref: i32 = 0;
    if (arena == 0 as *ASTArena || base_ref <= 0 || base_ref > arena.num_exprs) {
      return;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (base_ty <= 0 || base_ty > arena.num_types) {
      return;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    /* TYPE_ARRAY=10, TYPE_VECTOR=13: fixed T[N] / SIMD lanes — .length is N. */
    if ((bt_kind == 10 || bt_kind == 13) && fl == 6 && name_equal(&fn_buf[0], fl, &len_nm[0], 6)) {
      if (pipeline_type_array_size_at(arena, base_ty) <= 0) {
        return;
      }
      ut = ensure_usize_type_ref(arena);
      if (ut != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ut);
      }
      return;
    }
    /* TYPE_SLICE=11 */
    if (bt_kind != 11) {
      return;
    }
    elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
    if (elem_ty <= 0) {
      return;
    }
    if (fl == 6 && name_equal(&fn_buf[0], fl, &len_nm[0], 6)) {
      ut = ensure_usize_type_ref(arena);
      if (ut != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ut);
      }
      /* G.7: fat pointer second word at +8 (layout half, not rbp-distance). */
      pipeline_expr_set_field_access_offset(arena, expr_ref, 8);
      return;
    }
    if (fl == 4 && name_equal(&fn_buf[0], fl, &dat_nm[0], 4)) {
      /* G.7: .data is *elem for every slice element kind. */
      pipeline_expr_set_field_access_offset(arena, expr_ref, 0);
      ptr_ref = find_or_alloc_ptr_type_ref(arena, elem_ty);
      if (ptr_ref != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_ref);
      }
    }
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS name fallback when layout / known_ptr / slice miss.
 *
 * Migrated from C `pipeline_typeck_field_name_fallback_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_name_fallback_c` remains a thin C forwarder for
 * EMIT_HEAVY field_access orchestration.
 *
 * Order (no dual authority with layout path — only runs when field type still null):
 *  1. CodegenOutBuf.data → u8[8388608] (self-host CodegenOutBuf buffer field).
 *  2. Inline u8[64] field names (name / var_name / …).
 *  3. Inline i32[16] field names (call_arg_refs / match_arm_* / …).
 *  4. Scalar field-name heuristic (`expr_field_access_fallback_scalar_type_ref`).
 *
 * @param arena *ASTArena — expr/type arena (null → no-op)
 * @param expr_ref i32 — FIELD_ACCESS expr (must still have null resolved_type)
 * @param base_ref i32 — field base expr (used only for CodegenOutBuf.data path)
 * @return void
 * PLATFORM: SHARED — G.7 single authority; self-host + product field resolve.
 */
export function typeck_field_name_fallback(arena: *ASTArena, expr_ref: i32, base_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fl: i32 = 0;
    let fn_buf: u8[128] = [];
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let named_ref: i32 = 0;
    let cob_nm: u8[128] = [];
    let cob_len: i32 = 0;
    let nm_dat: u8[4] = [100, 97, 116, 97];
    /* "CodegenOutBuf" */
    let nm_cob: u8[13] = [67, 111, 100, 101, 103, 101, 110, 79, 117, 116, 66, 117, 102];
    let u8r_cob: i32 = 0;
    let arr_cob: i32 = 0;
    let u8_fb: i32 = 0;
    let arr_fb: i32 = 0;
    let scalar_fb: i32 = 0;
    let elem_r: i32 = 0;
    if (arena == 0 as *ASTArena) {
      return;
    }
    /* Already stamped by layout / slice / known_ptr — do not overwrite. */
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return;
    }
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    /* CodegenOutBuf.data → large u8 array (self-host outbuf buffer). */
    if (fl == 4 && !ast.ref_is_null(base_ref) && base_ref > 0 && base_ref <= arena.num_exprs) {
      base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
      if (!ast.ref_is_null(base_ty) && base_ty > 0 && base_ty <= arena.num_types) {
        bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
        named_ref = 0;
        /* TYPE_PTR=9: peel to pointee TYPE_NAMED; TYPE_NAMED=8: use base. */
        if (bt_kind == 9) {
          elem_r = pipeline_type_elem_ref_at(arena, base_ty);
          if (!ast.ref_is_null(elem_r) && pipeline_type_kind_ord_at(arena, elem_r) == 8) {
            named_ref = elem_r;
          }
        } else if (bt_kind == 8) {
          named_ref = base_ty;
        }
        if (named_ref != 0 && name_equal(&fn_buf[0], fl, &nm_dat[0], 4)) {
          cob_len = pipeline_type_named_name_into(arena, named_ref, &cob_nm[0]);
          if (cob_len == 13 && name_equal(&cob_nm[0], cob_len, &nm_cob[0], 13)) {
            u8r_cob = ensure_u8_type_ref(arena);
            if (u8r_cob != 0) {
              arr_cob = find_or_alloc_array_type_ref(arena, u8r_cob, 8388608);
              if (arr_cob != 0) {
                pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_cob);
                return;
              }
            }
          }
        }
      }
    }
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return;
    }
    u8_fb = typeck_inline_u8_64_array_field_type_ref(arena, &fn_buf[0], fl);
    if (u8_fb != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, u8_fb);
      return;
    }
    arr_fb = typeck_expr_inline_array_field_type_ref(arena, &fn_buf[0], fl);
    if (arr_fb != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_fb);
      return;
    }
    scalar_fb = expr_field_access_fallback_scalar_type_ref(arena, &fn_buf[0], fl);
    if (scalar_fb != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, scalar_fb);
    }
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS lexer-wrapper / param-type field fallback.
 *
 * Migrated from C `pipeline_typeck_field_lexer_fallback_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public surface
 * `pipeline_typeck_field_lexer_fallback_c` remains a thin C forwarder.
 *
 * Uses existing authority `typeck_field_access_lexer_wrapper_fallback` for
 * Lexer / LexerResult / Parse*Result field names. Additional hop: when base is
 * EXPR_VAR and still untyped after resolved_type attempts, look up the current
 * function formal type by name and retry the same wrapper table.
 *
 * @param module *Module — current module (param table)
 * @param arena *ASTArena — expr/type arena
 * @param expr_ref i32 — FIELD_ACCESS expr (must still have null resolved_type)
 * @param base_ref i32 — field base expr
 * @param ctx *PipelineDepCtx — current_func_index for param lookup
 * @return void
 * PLATFORM: SHARED — G.7; self-host lexer.x / parser result field resolve.
 */
export function typeck_field_lexer_fallback(module: *Module, arena: *ASTArena, expr_ref: i32,
base_ref: i32, ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ty: i32 = 0;
    let elem_ty: i32 = 0;
    let fl: i32 = 0;
    let fn_buf: u8[128] = [];
    let vbuf: u8[128] = [];
    let vnlen: i32 = 0;
    let pr_fb: i32 = 0;
    let lx_fb: i32 = 0;
    let fi: i32 = 0;
    if (arena == 0 as *ASTArena || module == 0 as *Module) {
      return;
    }
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return;
    }
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return;
    }
    fl = pipeline_expr_field_access_name_len(arena, expr_ref);
    if (fl <= 0 || fl > 127) {
      return;
    }
    pipeline_expr_field_access_name_into(arena, expr_ref, &fn_buf[0]);
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (!ast.ref_is_null(base_ty) && base_ty > 0 && base_ty <= arena.num_types) {
      lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, base_ty, &fn_buf[0], fl);
      if (lx_fb != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb);
        return;
      }
      /* TYPE_PTR=9: peel and retry on pointee (e.g. *LexerResult). */
      if (pipeline_type_kind_ord_at(arena, base_ty) == 9) {
        elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
        if (!ast.ref_is_null(elem_ty)) {
          lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, elem_ty, &fn_buf[0], fl);
          if (lx_fb != 0) {
            pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb);
            return;
          }
        }
      }
    }
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return;
    }
    /* EXPR_VAR=3: formal-type hop when base resolved_type still missing. */
    if (pipeline_expr_kind_ord_at(arena, base_ref) != 3) {
      return;
    }
    vnlen = pipeline_expr_var_name_len(arena, base_ref);
    if (vnlen <= 0 || vnlen > 127) {
      return;
    }
    if (ctx == 0 as *PipelineDepCtx) {
      return;
    }
    fi = pipeline_dep_ctx_current_func_index(ctx);
    if (fi < 0 || fi >= module.num_funcs) {
      return;
    }
    pipeline_expr_var_name_into(arena, base_ref, &vbuf[0]);
    pr_fb = pipeline_module_func_param_type_ref_for_name(module, fi, &vbuf[0], vnlen);
    if (ast.ref_is_null(pr_fb)) {
      return;
    }
    lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, pr_fb, &fn_buf[0], fl);
    if (lx_fb != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb);
    }
  }
}

/** See implementation for details. */
export function expr_var_name_equal_func(arena: *ASTArena, callee_expr_ref: i32, mod: *Module,
func_index: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let vbuf: *u8 = typeck_scratch64_slot(8);
    let b_len: i32 = 0;
    let a_len: i32 = 0;
    let i: i32 = 0;
    if (callee_expr_ref <= 0 || callee_expr_ref > arena.num_exprs) {
      return false;
    }
    if (pipeline_expr_kind_ord_at(arena, callee_expr_ref) != 3) {
      return false;
    }
    b_len = pipeline_expr_var_name_len(arena, callee_expr_ref);
    if (func_index < 0 || func_index >= mod.num_funcs) {
      return false;
    }
    a_len = pipeline_module_func_name_len_at(mod, func_index);
    if (a_len != b_len || a_len <= 0 || a_len > 127) {
      return false;
    }
    pipeline_expr_var_name_into(arena, callee_expr_ref, vbuf);
    while (i < a_len) {
      if (pipeline_module_func_name_byte_at(mod, func_index, i) != vbuf[i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/** Exported function `find_or_alloc_named_type_ref`.
 * Memory management helper `find_or_alloc_named_type_ref`.
 * @param arena *ASTArena
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
export function find_or_alloc_named_type_ref(arena: *ASTArena, name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    let ko: i32 = 0;
    let exist_len: i32 = 0;
    let ord_named: i32 = 8;
    /* See implementation. */
    let nm_scr: *u8 = typeck_scratch64_slot(12);
    if (arena == 0 as *ASTArena || name == 0 as *u8 || name_len <= 0 || name_len > 127) {
      return 0;
    }
    k = 1;
    while (k <= arena.num_types) {
      ko = pipeline_type_kind_ord_at(arena, k);
      if (ko == ord_named) {
        exist_len = pipeline_type_named_name_into(arena, k, nm_scr);
        if (exist_len == name_len && name_equal(nm_scr, exist_len, name, name_len)) {
          return k;
        }
      }
      k = k + 1;
    }
    k = pipeline_arena_type_alloc(arena);
    if (k <= 0) {
      return 0;
    }
    if (pipeline_type_init_named_at(arena, k, name, name_len) == 0) {
      return 0;
    }
    return k;
  }
}

/**
* See implementation.
* See implementation.
* See implementation.
*/
export function typeck_field_access_lexer_wrapper_fallback(arena: *ASTArena, base_type_ref: i32,
field_name: *u8, field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (ast.ref_is_null(base_type_ref) || base_type_ref <= 0 || base_type_ref > arena.num_types) {
      return 0;
    }
    /* See implementation. */
    let bn: u8[128] = [];
    let bn_len: i32 = pipeline_type_named_name_into(arena, base_type_ref, &bn[0]);
    if (bn_len <= 0 || bn_len > 127) {
      return 0;
    }
    let nm_lexer: u8[5] = [76, 101, 120, 101, 114];
    let nm_next_lex: u8[8] = [110, 101, 120, 95, 108, 101, 120];
    let nm_token_start: u8[11] = [116, 111, 107, 101, 110, 95, 115, 116, 97, 114, 116];
    let nm_lex: u8[3] = [108, 101, 120];
    let nm_pos: u8[3] = [112, 111, 115];
    let nm_line: u8[4] = [108, 105, 110, 101];
    let nm_col: u8[3] = [99, 111, 108];
    let nm_lres: u8[11] = [76, 101, 120, 101, 114, 82, 101, 115, 117, 108, 116];
    let nm_cir: u8[21] = [67, 111, 108, 108, 101, 99, 116, 73, 109, 112, 111, 114, 116, 115, 82, 101,
    115, 117, 108, 116];
    let nm_tsar: u8[18] = [84, 114, 121, 83, 107, 105, 112, 65, 108, 108, 111, 119, 82, 101, 115, 117,
    108, 116];
    let nm_lpr: u8[19] = [76, 105, 98, 114, 97, 114, 121, 80, 97, 114, 115, 101, 82, 101, 115, 117,
    108, 116];
    let nm_per: u8[15] = [80, 97, 114, 115, 101, 69, 120, 112, 114, 82, 101, 115, 117, 108, 116];
    let nm_pbr: u8[16] = [80, 97, 114, 115, 101, 66, 108, 111, 99, 107, 82, 101, 115, 117, 108, 116];
    let nm_tlr: u8[17] = [84, 111, 112, 76, 101, 118, 101, 108, 76, 101, 116, 82, 101, 115, 117, 108,
    116];
    let lex_tr: i32 = find_or_alloc_named_type_ref(arena, &nm_lexer[0], 5);
    if (lex_tr == 0) {
      return 0;
    }
    if (field_name_len == 8 && name_equal(field_name, field_name_len, &nm_next_lex[0], 8)) {
      if (bn_len == 11 && name_equal(&bn[0], bn_len, &nm_lres[0], 11)) {
        return lex_tr;
      }
      if (bn_len == 19 && name_equal(&bn[0], bn_len, &nm_lpr[0], 19)) {
        return lex_tr;
      }
      if (bn_len == 15 && name_equal(&bn[0], bn_len, &nm_per[0], 15)) {
        return lex_tr;
      }
      if (bn_len == 16 && name_equal(&bn[0], bn_len, &nm_pbr[0], 16)) {
        return lex_tr;
      }
      if (bn_len == 17 && name_equal(&bn[0], bn_len, &nm_tlr[0], 17)) {
        return lex_tr;
      }
    }
    if (field_name_len == 11 && name_equal(field_name, field_name_len, &nm_token_start[0], 11)) {
      if (bn_len == 11 && name_equal(&bn[0], bn_len, &nm_lres[0], 11)) {
        return ensure_usize_type_ref(arena);
      }
    }
    if (field_name_len == 3 && name_equal(field_name, field_name_len, &nm_lex[0], 3)) {
      if (bn_len == 21 && name_equal(&bn[0], bn_len, &nm_cir[0], 21)) {
        return lex_tr;
      }
      if (bn_len == 18 && name_equal(&bn[0], bn_len, &nm_tsar[0], 18)) {
        return lex_tr;
      }
    }
    if (bn_len == 5 && name_equal(&bn[0], bn_len, &nm_lexer[0], 5)) {
      if (field_name_len == 3 && name_equal(field_name, field_name_len, &nm_pos[0], 3)) {
        return ensure_usize_type_ref(arena);
      }
      if (field_name_len == 4 && name_equal(field_name, field_name_len, &nm_line[0], 4)) {
        return ensure_i32_type_ref(arena);
      }
      if (field_name_len == 3 && name_equal(field_name, field_name_len, &nm_col[0], 3)) {
        return ensure_i32_type_ref(arena);
      }
    }
    return 0;
  }
}

/*
 * Stage12.0.5 typeck wall slim — primitive kind O(1) cache keyed by arena.
 * Sample exclusive CPU on mega pure-asm was dominated by pipe_load_* inside
 * O(num_types) ensure_primitive / find_or_alloc_compound scans. Cache hits
 * avoid re-walking the type pool for i32/bool/u8/… on every stamp.
 * PLATFORM: SHARED — BSS process-local; invalidate when arena pointer changes.
 */
let g_typeck_prim_arena: *u8 = 0 as *u8;
/* [18]: slots 0..17 — TYPE_DYN (17) accepted since the TYPE_DYN foundation
 * wave widened the kind_ord gate; keeps the BSS cache in range (no OOB). */
let g_typeck_prim_ref: i32[18] = [];

/**
 * Ensure a primitive type slot exists for kind_ord in arena; return its ref.
 * Stage12.0.5 wall slim: BSS cache per arena + scan without named_name_into
 * (primitives never carry names; prior scan paid name_into on every kind hit).
 * @param arena *ASTArena — type pool
 * @param kind_ord i32 — TypeKind ordinal in [0,17] (i32=0 … dyn=17)
 * @return i32 — type_ref > 0, or 0 on null/alloc/init failure
 * PLATFORM: SHARED freestanding typeck type-pool.
 */
export function typeck_ensure_primitive_by_kind_ord(arena: *ASTArena, kind_ord: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    let ko: i32 = 0;
    let er: i32 = 0;
    let asz: i32 = 0;
    let a_u8: *u8 = 0 as *u8;
    let ci: i32 = 0;
    if (arena == 0 as *ASTArena || kind_ord < 0 || kind_ord > 17) {
      return 0;
    }
    a_u8 = arena as *u8;
    // Invalidate cache when the type pool instance changes.
    if (g_typeck_prim_arena != a_u8) {
      g_typeck_prim_arena = a_u8;
      ci = 0;
      while (ci <= 17) {
        g_typeck_prim_ref[ci] = 0;
        ci = ci + 1;
      }
    }
    if (g_typeck_prim_ref[kind_ord] > 0) {
      return g_typeck_prim_ref[kind_ord];
    }
    k = 1;
    while (k <= arena.num_types) {
      ko = pipeline_type_kind_ord_at(arena, k);
      // Bare primitive: matching kind, no pointee, no array size (no name load).
      if (ko == kind_ord) {
        er = pipeline_type_elem_ref_at(arena, k);
        asz = pipeline_type_array_size_at(arena, k);
        if (er == 0 && asz == 0) {
          g_typeck_prim_ref[kind_ord] = k;
          return k;
        }
      }
      k = k + 1;
    }
    k = pipeline_arena_type_alloc(arena);
    if (k <= 0) {
      return 0;
    }
    if (pipeline_type_init_primitive_kind_at(arena, k, kind_ord) == 0) {
      return 0;
    }
    g_typeck_prim_ref[kind_ord] = k;
    return k;
  }
}

/** Exported function `ensure_i32_type_ref`.
 * Implements `ensure_i32_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_i32_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 0);
}

/** Exported function `ensure_u8_type_ref`.
 * Implements `ensure_u8_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_u8_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 2);
}

/** Exported function `ensure_bool_type_ref`.
 * Implements `ensure_bool_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_bool_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 1);
}

/** Exported function `ensure_f32_type_ref`.
 * Implements `ensure_f32_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_f32_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 14);
}

/** Exported function `ensure_f64_type_ref`.
 * Implements `ensure_f64_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_f64_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 15);
}

/** Exported function `ensure_usize_type_ref`.
 * Implements `ensure_usize_type_ref`.
 * @param arena *ASTArena
 * @return i32
 */
export function ensure_usize_type_ref(arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(arena, 6);
}

/** Exported function `ensure_void_type_ref`.
 * Implements `ensure_void_type_ref`.
 * @param a *ASTArena
 * @return i32
 */
export function ensure_void_type_ref(a: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(a, 16);
}

/*
 * wave254 pure leave: entry-module BSS for dep return TYPE_NAMED binding prefix.
 * Cap residual / strict_minimal second BSS cells retired (G.7 dual-export ban).
 * Setter/getter Cap faces at EOF: pipeline_typeck_set_entry_module_for_dep_map_c /
 * pipeline_typeck_get_dep_return_type_in_caller_arena_c.
 * PLATFORM: SHARED freestanding typeck dep map.
 */
let g_typeck_entry_module_for_dep_map: *Module = 0 as *Module;

/**
 * Map a dep-side TYPE_NAMED bare name into the caller arena, qualified with the
 * entry import binding prefix when the import slot is IMPORT_BINDING
 * (e.g. vec.Vec_u8). Falls back to bare find_or_alloc_named.
 * @param entry_mod *Module — entry module import table; null → bare named
 * @param dep_ix i32 — import / dep slot index into entry_mod.imports
 * @param caller_arena *ASTArena — destination type pool
 * @param nm *u8 — bare type name bytes from dep arena
 * @param nlen i32 — name length; must be > 0
 * @return i32 — caller-arena type_ref, or 0 on failure
 * PLATFORM: SHARED freestanding typeck dep map (wave254 pure leave).
 */
export function typeck_map_import_binding_named_to_caller(entry_mod: *Module, dep_ix: i32,
caller_arena: *ASTArena, nm: *u8, nlen: i32): i32 {
  // PLATFORM: SHARED — binding-qualified TYPE_NAMED map for cross-module ret.
  unsafe {
    let bl: i32 = 0;
    let qlen: i32 = 0;
    let i: i32 = 0;
    let qnm: *u8 = typeck_scratch64_slot(15);
    if (caller_arena == 0 as *ASTArena || nm == 0 as *u8 || nlen <= 0) {
      return 0;
    }
    if (entry_mod == 0 as *Module || dep_ix < 0 || dep_ix >= entry_mod.num_imports) {
      return find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    if (pipeline_module_import_kind_at(entry_mod, dep_ix) != 1) {
      return find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    bl = pipeline_module_import_binding_name_len(entry_mod, dep_ix);
    if (bl <= 0 || bl + 1 + nlen > 127) {
      return find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    while (i < bl) {
      qnm[i] = pipeline_module_import_binding_name_byte_at(entry_mod, dep_ix, i);
      i = i + 1;
    }
    qnm[bl] = 46;
    i = 0;
    while (i < nlen) {
      qnm[bl + 1 + i] = nm[i];
      i = i + 1;
    }
    qlen = bl + 1 + nlen;
    return find_or_alloc_named_type_ref(caller_arena, qnm, qlen);
  }
}

/**
 * Resolve a dep module return type_ref into the caller's arena.
 * For TYPE_NAMED with entry module set, applies import-binding prefix so
 * `let v: vec.Vec_u8` matches dep `Vec_u8`. Otherwise delegates to
 * dep_return_type_to_caller_arena (recursive compound map).
 * @param from_dep_index i32 — dep slot; <0 → 0
 * @param dep_return_type_ref i32 — type_ref valid in dep arena
 * @param caller_arena *ASTArena — destination type pool
 * @param ctx *PipelineDepCtx — dep arenas / modules
 * @return i32 — caller-arena type_ref, or 0
 * wave254 pure leave: was residual pipeline_typeck_get_dep_return_type_in_caller_arena_c.
 * PLATFORM: SHARED freestanding typeck dep map.
 */
export function get_dep_return_type_in_caller_arena(from_dep_index: i32, dep_return_type_ref: i32,
caller_arena: *ASTArena, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dep_arena: *ASTArena = 0 as *ASTArena;
    let kind: i32 = 0;
    let nlen: i32 = 0;
    let nm_buf: *u8 = typeck_scratch64_slot(0);
    let ord_named: i32 = 8;
    if (from_dep_index < 0 || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    dep_arena = pipeline_dep_ctx_arena_at(ctx, from_dep_index);
    if (dep_arena == 0 as *ASTArena) {
      dep_arena = pipeline_get_dep_arena_slot(from_dep_index);
      if (dep_arena == 0 as *ASTArena) {
        return 0;
      }
    }
    // Bootstrap: dep_index may be >= ndep when slot is still bound.
    if (from_dep_index >= pipeline_dep_ctx_ndep(ctx)) {
      if (pipeline_dep_ctx_module_at(ctx, from_dep_index) == 0 as *Module) {
        return 0;
      }
    }
    if (g_typeck_entry_module_for_dep_map != 0 as *Module && dep_return_type_ref > 0) {
      if (dep_return_type_ref <= dep_arena.num_types) {
        kind = pipeline_type_kind_ord_at(dep_arena, dep_return_type_ref);
        if (kind == ord_named) {
          nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf);
          if (nlen > 0) {
            return typeck_map_import_binding_named_to_caller(g_typeck_entry_module_for_dep_map,
              from_dep_index, caller_arena, nm_buf, nlen);
          }
        }
      }
    }
    return dep_return_type_to_caller_arena(dep_arena, dep_return_type_ref, caller_arena);
  }
}

/** Exported function `ensure_i64_type_ref`.
 * Implements `ensure_i64_type_ref`.
 * @param caller_arena *ASTArena
 * @return i32
 */
export function ensure_i64_type_ref(caller_arena: *ASTArena): i32 {
  return typeck_ensure_primitive_by_kind_ord(caller_arena, 5);
}

/**
 * See implementation.
 * See implementation.
 */
/**
 * Find or allocate a compound type (*T / T[N] / linear / vector) in the arena.
 *
 * G.7 single authority: thin → pipeline_type_find_or_alloc_compound (direct
 * field loads on Type slots). Prior typeck twin rescanned every type via
 * pipeline_type_named_name_into + region_label_len — O(num_types × heavy
 * sidecar loads). Stage12.0.5 mega pure-asm sample: exclusive top frames were
 * pipe_load_ptr_slot / pipe_load_i32_le under this scan.
 *
 * @param a *ASTArena — type pool
 * @param kind_ord i32 — TypeKind ordinal (PTR=9, ARRAY=10, LINEAR=12, VECTOR=13)
 * @param elem_ref i32 — pointee / element type_ref (0 only when kind allows)
 * @param array_size i32 — fixed size for ARRAY/VECTOR; 0 for PTR/LINEAR
 * @return i32 — type_ref > 0, or 0 on failure
 * PLATFORM: SHARED freestanding typeck type-pool.
 */
export function typeck_find_or_alloc_compound_type_ref(a: *ASTArena, kind_ord: i32, elem_ref: i32,
array_size: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (a == 0 as *ASTArena || kind_ord < 0 || kind_ord > 15) {
      return 0;
    }
    // G.7: one find/alloc path — pipeline_abi pure leave (wave270).
    return pipeline_type_find_or_alloc_compound(a, kind_ord, elem_ref, array_size);
  }
}

/**
* See implementation.
*/
export function find_or_alloc_array_type_ref(a: *ASTArena, elem_ref: i32, array_size: i32): i32 {
  if (elem_ref == 0) {
    return 0;
  }
  return typeck_find_or_alloc_compound_type_ref(a, 10, elem_ref, array_size);
}

/**
* See implementation.
*/
export function ensure_array_type_ref_named_elem(a: *ASTArena, elem_nm: *u8, elem_nm_len: i32,
array_size: i32): i32 {
  let elem_ref: i32 = find_or_alloc_named_type_ref(a, elem_nm, elem_nm_len);
  if (elem_ref == 0) {
    return 0;
  }
  return find_or_alloc_array_type_ref(a, elem_ref, array_size);
}

/**
* See implementation.
* See implementation.
*/
export function ensure_kind_only_type_ref(w: *ASTArena, kind: TypeKind): i32 {
  /* See implementation. */
  return typeck_ensure_primitive_by_kind_ord(w, kind as i32);
}

/** Exported function `find_or_alloc_ptr_type_ref`.
 * Memory management helper `find_or_alloc_ptr_type_ref`.
 * @param w *ASTArena
 * @param elem_ref i32
 * @return i32
 */
export function find_or_alloc_ptr_type_ref(w: *ASTArena, elem_ref: i32): i32 {
  return typeck_find_or_alloc_compound_type_ref(w, 9, elem_ref, 0);
}

/** Exported function `find_or_alloc_slice_type_ref`.
 * Memory management helper `find_or_alloc_slice_type_ref`.
 * @param w *ASTArena
 * @param elem_ref i32
 * @return i32
 */
export function find_or_alloc_slice_type_ref(w: *ASTArena, elem_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    return pipeline_type_find_or_alloc_slice(w, elem_ref, 0 as *u8, 0);
  }
}

/** Exported function `find_or_alloc_linear_type_ref`.
 * Memory management helper `find_or_alloc_linear_type_ref`.
 * @param w *ASTArena
 * @param elem_ref i32
 * @return i32
 */
export function find_or_alloc_linear_type_ref(w: *ASTArena, elem_ref: i32): i32 {
  return typeck_find_or_alloc_compound_type_ref(w, 12, elem_ref, 0);
}

/** Exported function `find_or_alloc_vector_type_ref`.
 * Memory management helper `find_or_alloc_vector_type_ref`.
 * @param w *ASTArena
 * @param elem_ref i32
 * @param array_size i32
 * @return i32
 */
export function find_or_alloc_vector_type_ref(w: *ASTArena, elem_ref: i32, array_size: i32): i32 {
  return typeck_find_or_alloc_compound_type_ref(w, 13, elem_ref, array_size);
}

/**
* See implementation.
* See implementation.
*/
export function dep_return_type_to_caller_arena(dep_arena: *ASTArena, dep_return_type_ref: i32,
caller_arena: *ASTArena): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let kind: i32 = 0;
    let inner_mapped: i32 = 0;
    let elem_ref: i32 = 0;
    let array_size: i32 = 0;
    let nlen: i32 = 0;
    let nm_buf: *u8 = typeck_scratch64_slot(0);
    let ord_i32: i32 = 0;
    let ord_bool: i32 = 1;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_linear: i32 = 12;
    let ord_vector: i32 = 13;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_usize: i32 = 6;
    let ord_void: i32 = 16;
    if (dep_return_type_ref <= 0) {
      return 0;
    }
    kind = pipeline_type_kind_ord_at(dep_arena, dep_return_type_ref);
    if (kind < 0) {
      return 0;
    }
    if (kind == ord_i32 || kind == ord_i64 || kind == ord_bool || kind == ord_f64 || kind == ord_u8 
    || kind == ord_u32
    || kind == ord_u64 || kind == ord_isize || kind == ord_f32 || kind == ord_usize || kind == 
    ord_void) {
      return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
    }
    if (kind == ord_named) {
      nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf);
      if (nlen <= 0) {
        return 0;
      }
      return find_or_alloc_named_type_ref(caller_arena, nm_buf, nlen);
    }
    elem_ref = pipeline_type_elem_ref_at(dep_arena, dep_return_type_ref);
    inner_mapped = 0;
    if (!ast.ref_is_null(elem_ref)) {
      inner_mapped = dep_return_type_to_caller_arena(dep_arena, elem_ref, caller_arena);
      if (inner_mapped == 0) {
        return 0;
      }
    }
    array_size = pipeline_type_array_size_at(dep_arena, dep_return_type_ref);
    if (kind == ord_slice) {
      let rlen: i32 = pipeline_type_region_label_len_at(dep_arena, dep_return_type_ref);
      let rbuf: *u8 = typeck_scratch64_slot(14);
      if (rlen > 0) {
        pipeline_type_region_label_into(dep_arena, dep_return_type_ref, rbuf);
      }
      return pipeline_type_find_or_alloc_slice(caller_arena, inner_mapped, rbuf, rlen);
    }
    if (kind == ord_ptr) {
      return find_or_alloc_ptr_type_ref(caller_arena, inner_mapped);
    }
    if (kind == ord_linear) {
      return find_or_alloc_linear_type_ref(caller_arena, inner_mapped);
    }
    if (kind == ord_vector) {
      return find_or_alloc_vector_type_ref(caller_arena, inner_mapped, array_size);
    }
    if (kind == ord_array) {
      if (ast.ref_is_null(elem_ref) || array_size <= 0) {
        return 0;
      }
      return find_or_alloc_array_type_ref(caller_arena, inner_mapped, array_size);
    }
    if (!ast.ref_is_null(elem_ref) || array_size != 0) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf);
    if (nlen != 0) {
      return 0;
    }
    return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
  }
}

/**
* See implementation.
*/
export function expr_field_access_fallback_scalar_type_ref(arena: *ASTArena, field_name: *u8,
field_name_len: i32): i32 {
  /* See implementation. */
  if (field_name_len >= 4) {
    let br: i32 = field_name_len - 4;
    if (field_name[br] == 95 && field_name[br + 1] == 114 && field_name[br + 2] == 101 && 
    field_name[br + 3] == 102) {
      return ensure_i32_type_ref(arena);
    }
  }
  /* See implementation. */
  let nm_match_num_arms: u8[14] = [109, 97, 116, 99, 104, 95, 110, 117, 109, 95, 97, 114, 109, 115];
  let nm_field_access_is_enum_variant: u8[28] = [
  102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 105, 115, 95, 101, 110, 117, 109, 95,
  118, 97, 114, 105, 97, 110, 116
  ];
  let nm_field_access_field_len: u8[22] = [
  102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 108, 101,
  110
  ];
  let nm_field_access_offset: u8[19] = [102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95,
  111, 102, 102, 115, 101, 116];
  let nm_index_base_is_slice: u8[19] = [105, 110, 100, 101, 120, 95, 98, 97, 115, 101, 95, 105, 115,
  95, 115, 108, 105, 99, 101];
  let nm_call_num_args: u8[13] = [99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115];
  let nm_method_call_name_len: u8[20] = [
  109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101, 95, 108, 101, 110
  ];
  let nm_method_call_num_args: u8[20] = [
  109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115
  ];
  let nm_const_folded_val: u8[16] = [99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95,
  118, 97, 108];
  let nm_const_folded_valid: u8[18] = [99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95,
  118, 97, 108, 105, 100];
  let nm_index_proven_in_bounds: u8[22] = [
  105, 110, 100, 101, 120, 95, 112, 114, 111, 118, 101, 110, 95, 105, 110, 95, 98, 111, 117, 110,
  100, 115
  ];
  /* See implementation. */
  let nm_call_resolved_func_index: u8[24] = [
  99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 102, 117, 110, 99, 95, 105, 110,
  100, 101, 120
  ];
  let nm_call_resolved_dep_index: u8[22] = [
  99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 100, 101, 112, 95, 105, 110,
  100, 101, 120
  ];
  let nm_enum_variant_tag: u8[16] = [
  101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 116, 97, 103
  ];
  if (field_name_len == 14 && name_equal(field_name, field_name_len, &nm_match_num_arms[0], 14)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 28 && name_equal(field_name, field_name_len,
  &nm_field_access_is_enum_variant[0], 28)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 22 && name_equal(field_name, field_name_len, &nm_field_access_field_len[0],
  22)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 19 && name_equal(field_name, field_name_len, &nm_field_access_offset[0],
  19)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 19 && name_equal(field_name, field_name_len, &nm_index_base_is_slice[0],
  19)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 13 && name_equal(field_name, field_name_len, &nm_call_num_args[0], 13)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 20 && name_equal(field_name, field_name_len, &nm_method_call_name_len[0],
  20)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 20 && name_equal(field_name, field_name_len, &nm_method_call_num_args[0],
  20)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 16 && name_equal(field_name, field_name_len, &nm_const_folded_val[0], 16)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 18 && name_equal(field_name, field_name_len, &nm_const_folded_valid[0],
  18)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 22 && name_equal(field_name, field_name_len, &nm_index_proven_in_bounds[0],
  22)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 24 && name_equal(field_name, field_name_len,
  &nm_call_resolved_func_index[0], 24)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 22 && name_equal(field_name, field_name_len, &nm_call_resolved_dep_index[0],
  22)) {
    return ensure_i32_type_ref(arena);
  }
  if (field_name_len == 16 && name_equal(field_name, field_name_len, &nm_enum_variant_tag[0], 16)) {
    return ensure_i32_type_ref(arena);
  }
  return 0;
}

/* See implementation. */
export function get_field_type_ref_from_layout_deps(module: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx, type_name: *u8, type_name_len: i32, field_name: *u8,
field_name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    /**
    * See implementation.
    * See implementation.
    */
    let nm_funcs_pool: u8[5] = [102, 117, 110, 99, 115];
    let nm_func_elem: u8[4] = [70, 117, 110, 99];
    if (field_name_len == 5 && name_equal(field_name, field_name_len, &nm_funcs_pool[0], 5)) {
      let arr_funcs_pool: i32 = ensure_array_type_ref_named_elem(arena, &nm_func_elem[0], 4, 256);
      if (arr_funcs_pool != 0) {
        return arr_funcs_pool;
      }
    }
    let nm_struct_layouts_pool: u8[14] = [115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117,
    116, 115];
    let nm_sl_elem: u8[12] = [83, 116, 114, 117, 99, 116, 76, 97, 121, 111, 117, 116];
    if (field_name_len == 14 && name_equal(field_name, field_name_len, &nm_struct_layouts_pool[0],
    14)) {
      let arr_sl_pool: i32 = ensure_array_type_ref_named_elem(arena, &nm_sl_elem[0], 12, 32);
      if (arr_sl_pool != 0) {
        return arr_sl_pool;
      }
    }
    let nm_num_struct_layouts_pool: u8[18] = [110, 117, 109, 95, 115, 116, 114, 117, 99, 116, 95, 108,
    97, 121, 111, 117, 116, 115];
    if (field_name_len == 18 && name_equal(field_name, field_name_len, &nm_num_struct_layouts_pool[0],
    18)) {
      return ensure_i32_type_ref(arena);
    }
    let u8_inline: i32 = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
    if (u8_inline != 0) {
      return u8_inline;
    }
    let i32_arr_inline: i32 = typeck_expr_inline_array_field_type_ref(arena, field_name,
    field_name_len);
    if (i32_arr_inline != 0) {
      return i32_arr_inline;
    }
    let r: i32 = get_field_type_ref_from_layout(module, type_name, type_name_len, field_name,
    field_name_len);
    if (r != 0) {
      return r;
    }
    if (ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    /* See implementation. */
    let nd2: i32 = pipeline_dep_ctx_ndep(ctx);
    let di: i32 = 0;
    while (di < nd2) {
      let dm: *Module = pipeline_dep_ctx_module_at(ctx, di);
      if (dm != 0 as *Module) {
        r = get_field_type_ref_from_layout(dm, type_name, type_name_len, field_name, field_name_len);
        if (r != 0) {
          let da: *ASTArena = pipeline_dep_ctx_arena_at(ctx, di);
          if (da != 0 as *ASTArena) {
            return dep_return_type_to_caller_arena(da, r, arena);
          }
          return r;
        }
      }
      di = di + 1;
    }
    /* See implementation. */
    if (type_name_len == 4 && type_name[0] == 69 && type_name[1] == 120 && type_name[2] == 112 && 
    type_name[3] == 114) {
      let u8_fb: i32 = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      if (u8_fb != 0) {
        return u8_fb;
      }
      let arr_fb: i32 = typeck_expr_inline_array_field_type_ref(arena, field_name, field_name_len);
      if (arr_fb != 0) {
        return arr_fb;
      }
      let fb: i32 = expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
      if (fb != 0) {
        return fb;
      }
    }
    /* See implementation. */
    if (type_name_len == 4 && type_name[0] == 84 && type_name[1] == 121 && type_name[2] == 112 && 
    type_name[3] == 101) {
      let u8_ty: i32 = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      if (u8_ty != 0) {
        return u8_ty;
      }
    }
    /* See implementation. */
    if (type_name_len == 4 && type_name[0] == 70 && type_name[1] == 117 && type_name[2] == 110 && 
    type_name[3] == 99) {
      let u8_fn: i32 = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      if (u8_fn != 0) {
        return u8_fn;
      }
      let nm_params: u8[6] = [112, 97, 114, 97, 109, 115];
      let nm_pa: u8[5] = [80, 97, 114, 97, 109];
      if (field_name_len == 6 && name_equal(field_name, field_name_len, &nm_params[0], 6)) {
        return ensure_array_type_ref_named_elem(arena, &nm_pa[0], 5, 16);
      }
      let fb_fn: i32 = expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
      if (fb_fn != 0) {
        return fb_fn;
      }
    }
    /* See implementation. */
    if (type_name_len == 5 && type_name[0] == 80 && type_name[1] == 97 && type_name[2] == 114 && 
    type_name[3] == 97 && type_name[4] == 109) {
      let nm_pname: u8[4] = [110, 97, 109, 101];
      if (field_name_len == 4 && name_equal(field_name, field_name_len, &nm_pname[0], 4)) {
        let u8r_p: i32 = ensure_u8_type_ref(arena);
        if (u8r_p != 0) {
          return find_or_alloc_array_type_ref(arena, u8r_p, 32);
        }
      }
    }
    /* See implementation. */
    if (type_name_len == 12 && type_name[0] == 83 && type_name[1] == 116 && type_name[2] == 114 && 
    type_name[3] == 117
    && type_name[4] == 99 && type_name[5] == 116 && type_name[6] == 76 && type_name[7] == 97
    && type_name[8] == 121 && type_name[9] == 111 && type_name[10] == 117 && type_name[11] == 116) {
      let u8r_sl: i32 = ensure_u8_type_ref(arena);
      let i32r_sl: i32 = ensure_i32_type_ref(arena);
      let nm_sl_name: u8[4] = [110, 97, 109, 101];
      let nm_sl_field_names: u8[11] = [102, 105, 101, 108, 100, 95, 110, 97, 109, 101, 115];
      let nm_sl_field_lens: u8[11] = [102, 105, 101, 108, 100, 95, 108, 101, 110, 115];
      let nm_sl_field_offsets: u8[13] = [102, 105, 101, 108, 100, 95, 111, 102, 102, 115, 101, 116,
      115];
      let nm_sl_field_type_refs: u8[15] = [102, 105, 101, 108, 100, 95, 116, 121, 112, 101, 95, 114,
      101, 102, 115];
      let nm_sl_num_fields: u8[10] = [110, 117, 109, 95, 102, 105, 101, 108, 100, 115];
      let nm_sl_allow_padding: u8[14] = [97, 108, 108, 111, 119, 95, 112, 97, 100, 100, 105, 110,
      103];
      if (field_name_len == 4 && name_equal(field_name, field_name_len, &nm_sl_name[0],
      4) && u8r_sl != 0) {
        return find_or_alloc_array_type_ref(arena, u8r_sl, 64);
      }
      if (field_name_len == 11 && name_equal(field_name, field_name_len, &nm_sl_field_names[0],
      11) && u8r_sl != 0) {
        let row_u8: i32 = find_or_alloc_array_type_ref(arena, u8r_sl, 64);
        if (row_u8 != 0) {
          return find_or_alloc_array_type_ref(arena, row_u8, 64);
        }
      }
      if (field_name_len == 11 && name_equal(field_name, field_name_len, &nm_sl_field_lens[0],
      11) && i32r_sl != 0) {
        return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if (field_name_len == 13 && name_equal(field_name, field_name_len, &nm_sl_field_offsets[0],
      13) && i32r_sl != 0) {
        return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if (field_name_len == 15 && name_equal(field_name, field_name_len, &nm_sl_field_type_refs[0],
      15) && i32r_sl != 0) {
        return find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if (field_name_len == 10 && name_equal(field_name, field_name_len, &nm_sl_num_fields[0], 10)) {
        return i32r_sl;
      }
      if (field_name_len == 14 && name_equal(field_name, field_name_len, &nm_sl_allow_padding[0],
      14)) {
        return i32r_sl;
      }
      if (field_name_len == 8 && field_name[0] == 110 && field_name[1] == 97 && field_name[2] == 109 
      && field_name[3] == 101
      && field_name[4] == 95 && field_name[5] == 108 && field_name[6] == 101 && field_name[7] == 110) 
      {
        return i32r_sl;
      }
    }
    return 0;
  }
}

/**
* See implementation.
* See implementation.
*/
export function typeck_inline_u8_64_array_field_type_ref(arena: *ASTArena, field_name: *u8,
field_name_len: i32): i32 {
  let u8r: i32 = ensure_u8_type_ref(arena);
  if (u8r == 0) {
    return 0;
  }
  let nm_name: u8[4] = [110, 97, 109, 101];
  let nm_var_name: u8[8] = [118, 97, 114, 95, 110, 97, 109, 101];
  let nm_field_access_field_name: u8[22] = [
  102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 110, 97,
  109, 101
  ];
  let nm_method_call_name: u8[16] = [
  109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101
  ];
  let nm_struct_lit_struct_name: u8[22] = [
  115, 116, 114, 117, 99, 116, 95, 108, 105, 116, 95, 115, 116, 114, 117, 99, 116, 95, 110, 97, 109,
  101
  ];
  if (field_name_len == 4 && name_equal(field_name, field_name_len, &nm_name[0], 4)) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (field_name_len == 8 && name_equal(field_name, field_name_len, &nm_var_name[0], 8)) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (field_name_len == 22 && name_equal(field_name, field_name_len, &nm_field_access_field_name[0],
  22)) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (field_name_len == 16 && name_equal(field_name, field_name_len, &nm_method_call_name[0], 16)) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (field_name_len == 22 && name_equal(field_name, field_name_len, &nm_struct_lit_struct_name[0],
  22)) {
    return find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  return 0;
}

/* See implementation. */
export function typeck_expr_inline_array_field_type_ref(arena: *ASTArena, field_name: *u8,
field_name_len: i32): i32 {
  let i32r: i32 = ensure_i32_type_ref(arena);
  if (i32r == 0) {
    return 0;
  }
  let nm_call_arg_refs: u8[13] = [99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115];
  let nm_method_call_arg_refs: u8[20] = [
  109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115
  ];
  let nm_match_arm_result_refs: u8[21] = [
  109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 114, 101, 115, 117, 108, 116, 95, 114, 101, 102, 115
  ];
  let nm_array_lit_elem_refs: u8[19] = [
  97, 114, 114, 97, 121, 95, 108, 105, 116, 95, 101, 108, 101, 109, 95, 114, 101, 102, 115
  ];
  /* See implementation. */
  let nm_match_arm_is_wildcard: u8[21] = [
  109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 119, 105, 108, 100, 99, 97, 114, 100
  ];
  let nm_match_arm_lit_val: u8[17] = [
  109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 108, 105, 116, 95, 118, 97, 108
  ];
  let nm_match_arm_is_enum_variant: u8[25] = [
  109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 101, 110, 117, 109, 95, 118, 97, 114,
  105, 97, 110, 116
  ];
  let nm_match_arm_variant_index: u8[23] = [
  109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 105, 110, 100,
  101, 120
  ];
  if (field_name_len == 13 && name_equal(field_name, field_name_len, &nm_call_arg_refs[0], 13)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 20 && name_equal(field_name, field_name_len, &nm_method_call_arg_refs[0],
  20)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 21 && name_equal(field_name, field_name_len, &nm_match_arm_result_refs[0],
  21)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 19 && name_equal(field_name, field_name_len, &nm_array_lit_elem_refs[0],
  19)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 21 && name_equal(field_name, field_name_len, &nm_match_arm_is_wildcard[0],
  21)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 17 && name_equal(field_name, field_name_len, &nm_match_arm_lit_val[0],
  17)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 25 && name_equal(field_name, field_name_len,
  &nm_match_arm_is_enum_variant[0], 25)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (field_name_len == 23 && name_equal(field_name, field_name_len, &nm_match_arm_variant_index[0],
  23)) {
    return find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  return 0;
}

/** Exported function `entry_module_find_struct_layout_index`.
 * Implements `entry_module_find_struct_layout_index`.
 * @param mod *Module
 * @param nm *u8
 * @param nlen i32
 * @return i32
 */
export function entry_module_find_struct_layout_index(mod: *Module, nm: *u8, nlen: i32): i32 {
  return typeck_find_layout_idx_by_type_name(mod, nm, nlen);
}

/**
* See implementation.
*/
export function typeck_merge_dep_struct_layouts_into_entry(mod: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    /* See implementation. */
    let nd_merge: i32 = 0;
    let di: i32 = 0;
    let dm: *Module = 0 as *Module;
    let darena: *ASTArena = 0 as *ASTArena;
    let k: i32 = 0;
    let nl: i32 = 0;
    let nf_dep: i32 = 0;
    let ex: i32 = 0;
    let need: i32 = 0;
    let weak_entry: bool = false;
    let is_expr_nm: bool = false;
    let ni: i32 = 0;
    let j: i32 = 0;
    let raw_fr: i32 = 0;
    let mapped: i32 = 0;
    let fnlen: i32 = 0;
    let foff: i32 = 0;
    let ndm_sl: i32 = 0;
    /* See implementation. */
    let dep_nm_buf: *u8 = typeck_scratch64_slot(9);
    let fn_buf: *u8 = typeck_scratch64_slot(10);
    if (ctx == 0 as *PipelineDepCtx) {
      return;
    }
    nd_merge = pipeline_dep_ctx_ndep(ctx);
    di = 0;
    while (di < nd_merge) {
      dm = pipeline_dep_ctx_module_at(ctx, di);
      darena = pipeline_dep_ctx_arena_at(ctx, di);
      if (dm == 0 as *Module || darena == 0 as *ASTArena) {
        di = di + 1;
        continue;
      }
      /* PLATFORM: SHARED — dep co-emit calls the merge for every module,
       * including each dep itself (backend entry). Self-merge would
       * reset_slot the dep's own layout then "copy" from the already-reset
       * slot, wiping field type_refs and offsets to 0 (std.set abort 134 /
       * std.string exit 3 three-face layout divergence). Skip the self COPY
       * but still sync: parse-only deps carry stale parse-time offsets and
       * the dep's own emit runs before the entry merge syncs it. */
      if (dm == mod) {
        glue_sync_struct_layout_field_offsets_c(dm, darena);
        di = di + 1;
        continue;
      }
      /* Sync dep offsets against the dep arena BEFORE copy. Skip-typeck
       * import leaves field_offset=0; caller-arena recompute then misses
       * remapped type_refs (gzip ZStream zalloc → next_in).
       * PLATFORM: SHARED. */
      glue_sync_struct_layout_field_offsets_c(dm, darena);
      ndm_sl = pipeline_module_num_struct_layouts_at(dm);
      k = 0;
      while (k < ndm_sl) {
        nl = pipeline_module_struct_layout_name_len(dm, k);
        /* wave583 Cap residual: merge layout names ≤127 (scratch64 slots are 128 bytes). */
        if (nl > 0 && nl <= 127) {
          nf_dep = pipeline_module_struct_layout_num_fields(dm, k);
          if (nf_dep > 64) {
            nf_dep = 64;
          }
          pipeline_module_struct_layout_name_into(dm, k, dep_nm_buf);
          ex = entry_module_find_struct_layout_index(mod, dep_nm_buf, nl);
          need = 0;
          if (ex < 0) {
            need = 1;
          } else {
            weak_entry = false;
            /* See implementation. */
            if (pipeline_module_struct_layout_num_fields(mod,
            ex) >= 2 && pipeline_module_struct_layout_field_type_ref(mod, ex, 1) == 0) {
              weak_entry = true;
            }
            /* See implementation. */
            is_expr_nm = false;
            if (nl == 4) {
              if (pipeline_module_struct_layout_name_byte_at(dm, k,
              0) == 69 && pipeline_module_struct_layout_name_byte_at(dm, k, 1) == 120
              && pipeline_module_struct_layout_name_byte_at(dm, k, 2) == 112
              && pipeline_module_struct_layout_name_byte_at(dm, k, 3) == 114) {
                is_expr_nm = true;
              }
            }
            if (nf_dep > pipeline_module_struct_layout_num_fields(mod,
            ex) || weak_entry || is_expr_nm) {
              need = 1;
            }
            // wave1220 P5: also re-copy when field counts match but types may differ.
            // Root cause: typeck_ensure_struct_layout_from_struct_lit creates layouts
            // from struct literal init expressions (e.g. token_start: 0 → I32 instead
            // of USIZE). When the dep module's authoritative layout has the same field
            // count, the old `>` condition skipped the re-copy, leaving wrong field
            // types. Using `>=` ensures dep authority always overwrites struct-lit
            // guesses. PLATFORM: SHARED — typeck only, no runtime impact.
            if (nf_dep > 0 && nf_dep >= pipeline_module_struct_layout_num_fields(mod,
            ex) && pipeline_module_struct_layout_num_fields(mod, ex) > 0) {
              need = 1;
            }
            /* See implementation. */
            if (pipeline_module_struct_layout_soa_at(dm, k) != 0
            && pipeline_module_struct_layout_soa_at(mod, ex) == 0) {
              need = 1;
            }
          }
          if (need != 0) {
            ni = ex;
            if (ex < 0) {
              ni = pipeline_module_struct_layout_alloc(mod);
              if (ni < 0) {
                k = k + 1;
                continue;
              }
            }
            pipeline_module_struct_layout_reset_slot(mod, ni);
            pipeline_module_struct_layout_set_name(mod, ni, dep_nm_buf, nl);
            j = 0;
            while (j < nf_dep) {
              raw_fr = pipeline_module_struct_layout_field_type_ref(dm, k, j);
              mapped = 0;
              if (raw_fr != 0) {
                mapped = dep_return_type_to_caller_arena(darena, raw_fr, arena);
              }
              fnlen = pipeline_module_struct_layout_field_name_len(dm, k, j);
              pipeline_module_struct_layout_field_name_into(dm, k, j, fn_buf);
              foff = pipeline_module_struct_layout_field_offset_at(dm, k, j);
              pipeline_module_struct_layout_set_field(mod, ni, j, fn_buf, fnlen, mapped, foff);
              pipeline_module_struct_layout_set_field_align(mod, ni, j,
              pipeline_module_struct_layout_field_align_at(dm, k, j));
              j = j + 1;
            }
            pipeline_module_struct_layout_set_num_fields(mod, ni, nf_dep);
            /* See implementation. */
            pipeline_module_struct_layout_set_allow_padding(mod, ni,
            pipeline_module_struct_layout_allow_padding_at(dm, k));
            pipeline_module_struct_layout_set_soa(mod, ni,
            pipeline_module_struct_layout_soa_at(dm, k));
            pipeline_module_struct_layout_set_packed(mod, ni,
            pipeline_module_struct_layout_packed_at(dm, k));
          }
        }
        k = k + 1;
      }
      di = di + 1;
    }
  }
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 */
export function typeck_wpo_unify_soa_layouts(entry: *Module, ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let nd: i32 = 0;
    let mi: i32 = 0;
    let dm: *Module = 0 as *Module;
    let nsl: i32 = 0;
    let k: i32 = 0;
    let nl: i32 = 0;
    let any_soa: i32 = 0;
    let mj: i32 = 0;
    let dm2: *Module = 0 as *Module;
    let nsl2: i32 = 0;
    let k2: i32 = 0;
    let nl2: i32 = 0;
    let li: i32 = 0;
    let nm_buf: *u8 = typeck_scratch64_slot(11);
    let nm2: *u8 = typeck_scratch64_slot(12);
    if (entry == 0 as *Module || ctx == 0 as *PipelineDepCtx) {
      return;
    }
    nd = pipeline_dep_ctx_ndep(ctx);
    mi = -1;
    while (mi < nd) {
      dm = entry;
      if (mi >= 0) {
        dm = pipeline_dep_ctx_module_at(ctx, mi);
      }
      if (dm == 0 as *Module) {
        mi = mi + 1;
        continue;
      }
      nsl = pipeline_module_num_struct_layouts_at(dm);
      k = 0;
      while (k < nsl) {
        nl = pipeline_module_struct_layout_name_len(dm, k);
        /* wave583 Cap residual: WPO SoA unify layout names ≤127. */
        if (nl > 0 && nl <= 127) {
          pipeline_module_struct_layout_name_into(dm, k, nm_buf);
          any_soa = pipeline_module_struct_layout_soa_at(dm, k);
          mj = -1;
          while (mj < nd && any_soa == 0) {
            dm2 = entry;
            if (mj >= 0) {
              dm2 = pipeline_dep_ctx_module_at(ctx, mj);
            }
            if (dm2 != 0 as *Module) {
              nsl2 = pipeline_module_num_struct_layouts_at(dm2);
              k2 = 0;
              while (k2 < nsl2 && any_soa == 0) {
                nl2 = pipeline_module_struct_layout_name_len(dm2, k2);
                if (nl2 == nl) {
                  pipeline_module_struct_layout_name_into(dm2, k2, nm2);
                  if (name_equal(nm_buf, nl, nm2, nl2)
                  && pipeline_module_struct_layout_soa_at(dm2, k2) != 0) {
                    any_soa = 1;
                  }
                }
                k2 = k2 + 1;
              }
            }
            mj = mj + 1;
          }
          if (any_soa != 0) {
            mj = -1;
            while (mj < nd) {
              dm2 = entry;
              if (mj >= 0) {
                dm2 = pipeline_dep_ctx_module_at(ctx, mj);
              }
              if (dm2 != 0 as *Module) {
                li = typeck_find_layout_idx_by_type_name(dm2, nm_buf, nl);
                if (li >= 0 && pipeline_module_struct_layout_soa_at(dm2, li) == 0) {
                  pipeline_module_struct_layout_set_soa(dm2, li, 1);
                }
              }
              mj = mj + 1;
            }
          }
        }
        k = k + 1;
      }
      mi = mi + 1;
    }
  }
}

/**
* See implementation.
*/
export function typeck_resolve_scan_dep_with_apply(module: *Module, arena: *ASTArena, callee_expr_ref: i32,
callee_ord: i32, call_expr_ref: i32, ctx: *PipelineDepCtx, dep_i: i32, imax: i32,
want_apply: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dm: *Module = 0 as *Module;
    let ret: i32 = 0;
    let fn_slot: *i32 = typeck_call_resolve_func_idx_slot();
    if (dep_i >= imax) {
      return 0;
    }
    dm = pipeline_dep_ctx_module_at(ctx, dep_i);
    if (dm != 0 as *Module) {
      typeck_i32_ptr_store(fn_slot, 0);
      ret = find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx,
      fn_slot);
      if (ret != 0) {
        if (want_apply != 0) {
          ast.ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek());
        }
        return ret;
      }
      if (dep_i < typeck_module_num_imports(module)) {
        ret = resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord,
        dep_i, ctx, fn_slot);
        if (ret != 0) {
          if (want_apply != 0) {
            ast.ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek());
          }
          return ret;
        }
      }
    }
    return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord,
    call_expr_ref, ctx, dep_i + 1, imax, want_apply);
  }
}

/* See implementation. */
export function find_func_return_type_in_module(mod: *Module, mod_arena: *ASTArena,
caller_arena: *ASTArena, callee_arena: *ASTArena, callee_expr_ref: i32, from_dep_index: i32,
ctx: *PipelineDepCtx, func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let j: i32 = 0;
    while (j < mod.num_funcs) {
      if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
        if (func_index_out != 0 as *i32) {
          func_index_out[0] = j;
        }
        let ret_dep: i32 = pipeline_module_func_return_type_at(mod, j);
        if (from_dep_index < 0) {
          return ret_dep;
        }
        return get_dep_return_type_in_caller_arena(from_dep_index, ret_dep, caller_arena, ctx);
      }
      j = j + 1;
    }
    return 0;
  }
}

/* See implementation. */
export extern function pipeline_visibility_allow_func(mod: *Module, fi: i32, cross_module: i32): i32;

/**
 * Find a function return type in a module by name; map dep ret into caller arena.
 * wave254: bootstrap fallback when get_dep returns 0 but dep arena is bound
 * (parity with retired Cap residual find_func_return_type_in_module_by_name_c).
 * @param mod *Module — function table owner
 * @param caller_arena *ASTArena — destination type pool
 * @param name *u8 — function name bytes
 * @param name_len i32 — length in [1,127]
 * @param from_dep_index i32 — <0 same-module raw ret; >=0 map via get_dep
 * @param ctx *PipelineDepCtx — dep arenas (required when from_dep_index >= 0)
 * @param func_index_out *i32 — optional out func index
 * @return i32 — caller-arena (or same-mod) type_ref; 0 not found / denied
 * PLATFORM: SHARED freestanding typeck.
 */
export function find_func_return_type_in_module_by_name(mod: *Module, caller_arena: *ASTArena, name: *u8,
name_len: i32, from_dep_index: i32, ctx: *PipelineDepCtx, func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (name_len <= 0 || name_len > 127) {
      return 0;
    }
    let j: i32 = 0;
    while (j < mod.num_funcs) {
      if (pipeline_module_func_name_equal_at(mod, j, name, name_len) != 0) {
        if (from_dep_index >= 0 && pipeline_visibility_allow_func(mod, j, 1) == 0) {
          j = j + 1;
          continue;
        }
        if (func_index_out != 0 as *i32) {
          func_index_out[0] = j;
        }
        let rtr: i32 = pipeline_module_func_return_type_at(mod, j);
        if (from_dep_index < 0) {
          return rtr;
        }
        let mapped: i32 = get_dep_return_type_in_caller_arena(from_dep_index, rtr, caller_arena, ctx);
        if (mapped != 0) {
          return mapped;
        }
        // Bootstrap fallback: direct dep-arena primitive/compound map.
        let da: *ASTArena = pipeline_dep_ctx_arena_at(ctx, from_dep_index);
        if (da != 0 as *ASTArena && rtr != 0) {
          return dep_return_type_to_caller_arena(da, rtr, caller_arena);
        }
        return 0;
      }
      j = j + 1;
    }
    return 0;
  }
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 */
export function typeck_overload_arg_param_score(caller_arena: *ASTArena, call_expr_ref: i32, arg_i: i32,
param_ty_raw: i32, from_dep_index: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let arg_ref: i32 = 0;
    let arg_ty: i32 = 0;
    let param_ty: i32 = 0;
    let ord_as: i32 = 54;
    let ord_method_call: i32 = 49;
    let as_tgt: i32 = 0;
    let call_kind: i32 = 0;
    if (caller_arena == 0 as *ASTArena || call_expr_ref <= 0 || arg_i < 0) {
      return -1;
    }
    /* wave303 G.7: METHOD_CALL args live on method_call_arg_ref (import.method leave).
     * CALL (48) keeps call_arg_ref. Single score authority — no seed dual scorer. */
    call_kind = pipeline_expr_kind_ord_at(caller_arena, call_expr_ref);
    if (call_kind == ord_method_call) {
      arg_ref = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, arg_i);
    } else {
      arg_ref = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, arg_i);
    }
    if (arg_ref <= 0) {
      return -1;
    }
    param_ty = param_ty_raw;
    if (from_dep_index >= 0) {
      param_ty = get_dep_return_type_in_caller_arena(from_dep_index, param_ty_raw, caller_arena, ctx);
      if (param_ty == 0) {
        return -1;
      }
    }
    if (param_ty <= 0) {
      return -1;
    }
    arg_ty = pipeline_expr_resolved_type_ref(caller_arena, arg_ref);
    if (arg_ty > 0 && pipeline_typeck_type_refs_equal_c(caller_arena, arg_ty, param_ty) != 0) {
      return 1000;
    }
    if (pipeline_expr_kind_ord_at(caller_arena, arg_ref) == ord_as) {
      as_tgt = pipeline_expr_as_target_type_ref_at(caller_arena, arg_ref);
      if (as_tgt > 0 && pipeline_typeck_type_refs_equal_c(caller_arena, as_tgt, param_ty) != 0) {
        return 1000;
      }
    }
    /*
     * PLATFORM: SHARED — string lit is *u8 by default (C interop) but also matches
     * u8[] (TYPE_SLICE of u8) for product single-arg print/println("…") and any
     * other u8[] param. Score 1000 so 1-arg slice overload wins over no-match.
     */
    if (pipeline_expr_kind_ord_at(caller_arena, arg_ref) == 59) {
      let pk_sl: i32 = pipeline_type_kind_ord_at(caller_arena, param_ty);
      let pe_sl: i32 = 0;
      let u8_ord: i32 = 2;
      if (pk_sl == 9 || pk_sl == 11) {
        pe_sl = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if (pe_sl > 0 && pipeline_type_kind_ord_at(caller_arena, pe_sl) == u8_ord) {
          return 1000;
        }
      }
    }
    /*
     * See implementation.
     * See implementation.
     * See implementation.
     */
    if (pipeline_expr_kind_ord_at(caller_arena, arg_ref) == 0) {
      let pk_lit: i32 = pipeline_type_kind_ord_at(caller_arena, param_ty);
      /*
       * wave670 Cap residual: keyword `null` only scores for TYPE_PTR formals.
       * Bare INT 0 still weak-matches integers + ptr. G.7 single score path.
       * PLATFORM: SHARED — keep strict_minimal arg score aligned.
       */
      if (typeck_expr_is_null_keyword(caller_arena, arg_ref) != 0) {
        if (pk_lit == 9) {
          return 100;
        }
        return -1;
      }
      if (pk_lit == 0 || pk_lit == 2 || pk_lit == 3 || pk_lit == 4 || pk_lit == 5 || pk_lit == 6
          || pk_lit == 7) {
        return 100;
      }
      /*
       * wave668 Cap residual: bare EXPR_LIT 0 weak-matches TYPE_PTR formals —
       * same contract as let/return/cmp 0→*T coerce. Score 100 < exact 1000.
       * Non-zero lit to *T stays -1.
       */
      if (pk_lit == 9 && pipeline_expr_int_val_at(caller_arena, arg_ref) == 0) {
        return 100;
      }
    }
    /*
     * Bare FLOAT_LIT (kind 1) / NEG(FLOAT_LIT) weak-match f32/f64 formals.
     * Root (intrinsic_binop_dot): simd.splat(0.0) vs splat(i32)/splat(f32) —
     * both overloads scored -1 (lit defaults f64; no FLOAT_LIT clause) → first_idx
     * splat(i32) → emit U/sret SEGV. Score 100 < exact 1000; i32 stays -1.
     * G.7 complete this score authority (≡ INT_LIT vs integer formals).
     * PLATFORM: SHARED — typeck pick; emit consumes r_func (do not first-wins re-score).
     */
    let arg_ko_fl: i32 = pipeline_expr_kind_ord_at(caller_arena, arg_ref);
    let fl_inner: i32 = arg_ref;
    if (arg_ko_fl == 22) {
      fl_inner = pipeline_expr_unary_operand_ref_at(caller_arena, arg_ref);
      if (fl_inner > 0) {
        arg_ko_fl = pipeline_expr_kind_ord_at(caller_arena, fl_inner);
      }
    }
    if (arg_ko_fl == 1) {
      let pk_fl: i32 = pipeline_type_kind_ord_at(caller_arena, param_ty);
      if (pk_fl == 14 || pk_fl == 15) {
        return 100;
      }
      return 0 - 1;
    }
    /* See implementation. */
    if (arg_ty > 0) {
      let ak: i32 = pipeline_type_kind_ord_at(caller_arena, arg_ty);
      let pk: i32 = pipeline_type_kind_ord_at(caller_arena, param_ty);
      /*
       * Integer widen (typeck_integer_widen_ok_refs): first-class + NAMED i8/i16/u16.
       * i32→usize for heap.alloc(al, capacity) so 2-arg Allocator+usize is not eliminated.
       * Score 100 < exact 1000; expected-return is a separate tie-break (not in arg score).
       * PLATFORM: SHARED — keep strict_minimal arg score aligned (wave313).
       */
      if (typeck_integer_widen_ok_refs(caller_arena, param_ty, arg_ty)) {
        return 100;
      }
      /* wave314: f32→f64 IEEE promotion scores as widen (not exact). */
      if (typeck_float_widen_ok(pk, ak)) {
        return 100;
      }
      /*
       * 10.3.3: opaque Cap-fn-ptr ABI — TYPE_FN ↔ Cap *u8 (cross-kind only).
       * Same gate as let/assign (`typeck_fnptr_surface_compat`). Do not steal
       * Cap↔Cap / TYPE_FN↔TYPE_FN same-kind paths (exact / PTR / ak==pk).
       * Score 100 < exact 1000. TYPE_FN↔TYPE_FN mismatch → -1 via type_refs_equal.
       * Cap↔TYPE_FN soft at score (no arg expr here). PLATFORM: SHARED.
       */
      if (ak != pk
          && typeck_is_fnptr_surface(caller_arena, param_ty) != 0
          && typeck_is_fnptr_surface(caller_arena, arg_ty) != 0) {
        return 100;
      }
      /* See implementation. */
      if (ak == 10 && pk == 9) {
        let ae: i32 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        let pe: i32 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if (ae > 0 && pe > 0 && pipeline_typeck_type_refs_equal_c(caller_arena, ae, pe) != 0) {
          return 1000;
        }
      }
      /*
       * See implementation.
       * See implementation.
       */
      if (ak == 9 && pk == 9) {
        let ae2: i32 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        let pe2: i32 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if (ae2 > 0 && pe2 > 0 && pipeline_typeck_type_refs_equal_c(caller_arena, ae2, pe2) != 0) {
          return 1000;
        }
        return -1;
      }
      /*
       * wave672 Cap residual: TYPE_ARRAY (10) / TYPE_SLICE (11) same-kind weak score
       * must require matching element types. Prior: `ak==pk` returned 1 for bool[2]
       * vs i32[2] → free-fn call `f([true,false])` false-green after resolve.
       * G.7: complete this score authority (PTR already checks pointee above).
       * PLATFORM: SHARED — keep strict_minimal arg score aligned.
       */
      if (ak == 10 && pk == 10) {
        let ae_a: i32 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        let pe_a: i32 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        let asz: i32 = pipeline_type_array_size_at(caller_arena, arg_ty);
        let psz: i32 = pipeline_type_array_size_at(caller_arena, param_ty);
        if (ae_a > 0 && pe_a > 0
        && pipeline_typeck_type_refs_equal_c(caller_arena, ae_a, pe_a) != 0
        && (asz <= 0 || psz <= 0 || asz == psz)) {
          return 1000;
        }
        return -1;
      }
      if (ak == 11 && pk == 11) {
        let ae_s: i32 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        let pe_s: i32 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if (ae_s > 0 && pe_s > 0
        && pipeline_typeck_type_refs_equal_c(caller_arena, ae_s, pe_s) != 0) {
          return 1000;
        }
        return -1;
      }
      /*
       * 4.2.10: [N]T arg → []T formal (`take(W.xs)` / `take(a)`).
       * Score only — do not stamp resolved_type_ref. emit_call_arg_slice_abi
       * keys off TYPE_ARRAY to materialize `{.data,.length}`. Stamping SLICE
       * made host-C emit `&(w.xs)` (array, not fat) and asm STRUCT_LIT.field SEGV.
       * G.7: complete this score authority (no second matcher). PLATFORM: SHARED.
       */
      if (ak == 10 && pk == 11) {
        let ae_as: i32 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        let pe_as: i32 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if (ae_as > 0 && pe_as > 0
        && pipeline_typeck_type_refs_equal_c(caller_arena, ae_as, pe_as) != 0) {
          return 100;
        }
        return -1;
      }
      if (ak == pk && ak != 0) {
        return 1;
      }
      return -1;
    }
    return -1;
  }
}

/**
 * See implementation.
 * See implementation.
 * When args do not disambiguate (zero-arg new/Vec_i32 vs Vec_u8), also prefer expected
 * return type from typeck_overload_expected_ret_peek as a *tie-break only* (let/assign).
 * Never fold a huge bonus into arg score (polluted outer main i32 → wrong get overload).
 * PLATFORM: SHARED — authority: this function; keep strict_minimal pick in sync.
 */
export function find_func_return_type_in_module_by_name_overload(mod: *Module, caller_arena: *ASTArena,
name: *u8, name_len: i32, call_expr_ref: i32, from_dep_index: i32, ctx: *PipelineDepCtx,
func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let j: i32 = 0;
    let num_args: i32 = 0;
    let best_idx: i32 = -1;
    let best_score: i32 = -1;
    /* expected_ret is tie-break only — must not override exact arg scores (vec_u16 get BLD001). */
    let best_expect_match: i32 = -1;
    let best_ret: i32 = 0;
    let first_idx: i32 = -1;
    let first_ret: i32 = 0;
    let expect_ty: i32 = 0;
    if (name_len <= 0 || name_len > 127 || mod == 0 as *Module) {
      return 0;
    }
    if (call_expr_ref <= 0 || caller_arena == 0 as *ASTArena ||
    call_expr_ref > caller_arena.num_exprs) {
      return find_func_return_type_in_module_by_name(mod, caller_arena, name, name_len, from_dep_index,
      ctx, func_index_out);
    }
    /* wave303 G.7: METHOD_CALL=49 num_args via method accessor (seed is_method path). */
    if (pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) == 49) {
      num_args = pipeline_expr_method_call_num_args_at(caller_arena, call_expr_ref);
    } else {
      num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref);
    }
    expect_ty = typeck_overload_expected_ret_peek();
    while (j < mod.num_funcs) {
      if (pipeline_module_func_name_equal_at(mod, j, name, name_len) != 0) {
        let rtr: i32 = pipeline_module_func_return_type_at(mod, j);
        if (first_idx < 0) {
          first_idx = j;
          first_ret = rtr;
        }
        let nparams: i32 = pipeline_module_func_num_params_at(mod, j);
        /* Cap 10.7.1 slice8: exact or variadic (score named formals only). */
        if (typeck_call_arity_compatible(mod, j, num_args) != 0) {
          let ai: i32 = 0;
          let score: i32 = 0;
          let matched: i32 = 1;
          let expect_match: i32 = 0;
          while (ai < nparams) {
            let param_raw: i32 = pipeline_module_func_param_type_ref_at(mod, j, ai);
            let pty: i32 = param_raw;
            let aref: i32 = 0;
            /*
             * ARRAY_LIT extras were check_expr'd against METHOD/CALL ambient
             * (often the return type, not this formal). Stamp SIMD/array/slice
             * formals before score — same coerce as typeck_check_call_arg_types.
             * Map dep formals into the caller arena (import.binding METHOD).
             * PLATFORM: SHARED.
             */
            if (from_dep_index >= 0) {
              pty = get_dep_return_type_in_caller_arena(from_dep_index, param_raw, caller_arena, ctx);
            }
            if (pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) == 49) {
              aref = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, ai);
            } else {
              aref = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, ai);
            }
            if (aref > 0 && pty > 0) {
              typeck_coerce_init_array_vector_lit_to_decl(mod, caller_arena, aref, pty,
              pipeline_type_kind_ord_at(caller_arena, pty),
              pipeline_expr_kind_ord_at(caller_arena, aref));
            }
            let sc: i32 = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw,
            from_dep_index, ctx);
            if (sc < 0) {
              matched = 0;
              break;
            }
            score = score + sc;
            ai = ai + 1;
          }
          /*
           * Zero-arg / arg-tie only: prefer overload whose return matches expected
           * (e.g. let v: Vec_u8 = vec.new()). Do NOT add a huge bonus into score —
           * outer main i32 threaded through if/binop polluted get→Vec_i32 (BLD001).
           * Maps dep return via get_dep_return so vec.Vec_u8 equals bare Vec_u8.
           * wave303: last-segment NAMED tie-break (G.7 from seed strict_minimal leave).
           * PLATFORM: SHARED — single pick authority on typeck_x.
           */
          if (matched != 0 && expect_ty > 0 && rtr > 0) {
            let mapped_ret: i32 = rtr;
            if (from_dep_index >= 0) {
              mapped_ret = get_dep_return_type_in_caller_arena(from_dep_index, rtr, caller_arena, ctx);
            }
            if (mapped_ret > 0) {
              if (pipeline_typeck_type_refs_equal_c(caller_arena, mapped_ret, expect_ty) != 0) {
                expect_match = 1;
              } else {
                /* Last-segment NAMED: bare Vec_u8 vs vec.Vec_u8 (exact equal may miss). */
                let na: u8[128] = [];
                let nb: u8[128] = [];
                let la: i32 = pipeline_type_named_name_into(caller_arena, mapped_ret, &na[0]);
                let lb: i32 = pipeline_type_named_name_into(caller_arena, expect_ty, &nb[0]);
                if (la > 0 && lb > 0) {
                  let sa: i32 = 0;
                  let sb: i32 = 0;
                  let ii: i32 = 0;
                  while (ii < la) {
                    if (na[ii] == 46 as u8) {
                      sa = ii + 1;
                    }
                    ii = ii + 1;
                  }
                  ii = 0;
                  while (ii < lb) {
                    if (nb[ii] == 46 as u8) {
                      sb = ii + 1;
                    }
                    ii = ii + 1;
                  }
                  if ((la - sa) == (lb - sb) && (la - sa) > 0) {
                    let eq: i32 = 1;
                    ii = 0;
                    while (ii < (la - sa)) {
                      if (na[sa + ii] != nb[sb + ii]) {
                        eq = 0;
                        break;
                      }
                      ii = ii + 1;
                    }
                    if (eq != 0) {
                      expect_match = 1;
                    }
                  }
                }
              }
            }
          }
          if (matched != 0 && (score > best_score
              || (score == best_score && expect_match > best_expect_match))) {
            best_score = score;
            best_expect_match = expect_match;
            best_idx = j;
            best_ret = rtr;
          }
        }
      }
      j = j + 1;
    }
    if (best_idx >= 0) {
      if (func_index_out != 0 as *i32) {
        func_index_out[0] = best_idx;
      }
      if (from_dep_index < 0) {
        return best_ret;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, best_ret, caller_arena, ctx);
    }
    /*
     * wave660 Cap residual: do NOT bind first same-name func when no candidate has
     * matching arity (host-cc BLD001 too few/many args). first_idx fallback remains
     * only when some same-name func has nparams==num_args but arg type scores failed
     * (type-mismatch soft residual; not this wave).
     * PLATFORM: SHARED — G.7 single authority with module_overload twin below.
     */
    if (first_idx >= 0) {
      let any_arity: i32 = 0;
      let j2: i32 = 0;
      while (j2 < mod.num_funcs) {
        if (pipeline_module_func_name_equal_at(mod, j2, name, name_len) != 0) {
          /* Cap 10.7.1 slice8: exact or variadic compatible. */
          if (typeck_call_arity_compatible(mod, j2, num_args) != 0) {
            any_arity = 1;
            break;
          }
        }
        j2 = j2 + 1;
      }
      if (any_arity == 0) {
        return 0;
      }
      if (func_index_out != 0 as *i32) {
        func_index_out[0] = first_idx;
      }
      if (from_dep_index < 0) {
        return first_ret;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, first_ret, caller_arena, ctx);
    }
    return 0;
  }
}

/**
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 * See implementation.
 * Also scores expected return (typeck_overload_expected_ret_peek) for zero-arg / arg-tie cases.
 * See implementation.
 * PLATFORM: SHARED — keep typeck_gen seed + glue strict_minimal pick aligned.
 */
export function find_func_return_type_in_module_overload(mod: *Module, mod_arena: *ASTArena,
caller_arena: *ASTArena, callee_arena: *ASTArena, callee_expr_ref: i32,
call_expr_ref: i32, from_dep_index: i32, ctx: *PipelineDepCtx, func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let j: i32 = 0;
    let first_idx: i32 = -1;
    let first_ret: i32 = 0;
    let num_args: i32 = 0;
    let has_call_info: i32 = 0;
    let best_idx: i32 = -1;
    let best_score: i32 = -1;
    let best_ret: i32 = 0;
    let expect_ty: i32 = 0;
    /* See implementation. */
    if (call_expr_ref > 0 && call_expr_ref <= caller_arena.num_exprs) {
      if (pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) == 49) {
        num_args = pipeline_expr_method_call_num_args_at(caller_arena, call_expr_ref);
      } else {
        num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref);
      }
      has_call_info = 1;
    }
    expect_ty = typeck_overload_expected_ret_peek();
    let best_expect_match2: i32 = -1;
    while (j < mod.num_funcs) {
      if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
        if (first_idx < 0) {
          first_idx = j;
          first_ret = pipeline_module_func_return_type_at(mod, j);
        }
        if (has_call_info != 0) {
          let nparams: i32 = pipeline_module_func_num_params_at(mod, j);
          /* Cap 10.7.1 slice8: exact or variadic (score named formals only). */
          if (typeck_call_arity_compatible(mod, j, num_args) != 0) {
            let ai: i32 = 0;
            let score: i32 = 0;
            let matched: i32 = 1;
            let expect_match2: i32 = 0;
            let rtr_cand: i32 = pipeline_module_func_return_type_at(mod, j);
            while (ai < nparams) {
              let param_raw: i32 = pipeline_module_func_param_type_ref_at(mod, j, ai);
              let pty2: i32 = param_raw;
              let aref2: i32 = 0;
              /* G.7 twin of by_name_overload: coerce ARRAY_LIT before score. */
              if (from_dep_index >= 0) {
                pty2 = get_dep_return_type_in_caller_arena(from_dep_index, param_raw, caller_arena, ctx);
              }
              if (pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) == 49) {
                aref2 = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, ai);
              } else {
                aref2 = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, ai);
              }
              if (aref2 > 0 && pty2 > 0) {
                typeck_coerce_init_array_vector_lit_to_decl(mod, caller_arena, aref2, pty2,
                pipeline_type_kind_ord_at(caller_arena, pty2),
                pipeline_expr_kind_ord_at(caller_arena, aref2));
              }
              let sc: i32 = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw,
              from_dep_index, ctx);
              if (sc < 0) {
                matched = 0;
                break;
              }
              score = score + sc;
              ai = ai + 1;
            }
            /* expected_ret: secondary key only (see by_name_overload; G.7 align strict_minimal). */
            if (matched != 0 && expect_ty > 0 && rtr_cand > 0) {
              let mapped_ret2: i32 = rtr_cand;
              if (from_dep_index >= 0) {
                mapped_ret2 =
                    get_dep_return_type_in_caller_arena(from_dep_index, rtr_cand, caller_arena, ctx);
              }
              if (mapped_ret2 > 0
                  && pipeline_typeck_type_refs_equal_c(caller_arena, mapped_ret2, expect_ty) != 0) {
                expect_match2 = 1;
              }
            }
            if (matched != 0 && (score > best_score
                || (score == best_score && expect_match2 > best_expect_match2))) {
              best_score = score;
              best_expect_match2 = expect_match2;
              best_idx = j;
              best_ret = rtr_cand;
            }
          }
        }
      }
      j = j + 1;
    }
    if (best_idx >= 0) {
      if (func_index_out != 0 as *i32) {
        func_index_out[0] = best_idx;
      }
      if (from_dep_index < 0) {
        return best_ret;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, best_ret, caller_arena, ctx);
    }
    /*
     * wave660 Cap residual: pure arity miss → return 0 (no first_idx bind).
     * first_idx only when has_call_info and some same-name nparams==num_args
     * (type-score soft residual). Without call info, keep legacy first_idx.
     * PLATFORM: SHARED — G.7 twin of by_name_overload.
     */
    if (first_idx >= 0) {
      if (has_call_info != 0) {
        let any_arity2: i32 = 0;
        let j3: i32 = 0;
        while (j3 < mod.num_funcs) {
          if (expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j3)) {
            /* Cap 10.7.1 slice8: exact or variadic compatible. */
            if (typeck_call_arity_compatible(mod, j3, num_args) != 0) {
              any_arity2 = 1;
              break;
            }
          }
          j3 = j3 + 1;
        }
        if (any_arity2 == 0) {
          return 0;
        }
      }
      if (func_index_out != 0 as *i32) {
        func_index_out[0] = first_idx;
      }
      if (from_dep_index < 0) {
        return first_ret;
      }
      return get_dep_return_type_in_caller_arena(from_dep_index, first_ret, caller_arena, ctx);
    }
    return 0;
  }
}

/** Exported function `typeck_import_path_segment_count`.
 * Implements `typeck_import_path_segment_count`.
 * @param path *u8
 * @param path_len i32
 * @return i32
 */
export function typeck_import_path_segment_count(path: *u8, path_len: i32): i32 {
  if (path_len <= 0 || path == 0 as *u8) {
    return 0;
  }
  let n: i32 = 1;
  let ii: i32 = 0;
  while (ii < path_len) {
    let ch_u8: u8 = path[ii];
    if (ch_u8 == 46) {
      /** '.' */
      n = n + 1;
    }
    ii = ii + 1;
  }
  return n;
}

/* See implementation. */
export function typeck_import_segment_at(module: *Module, imp_ix: i32, want_seg: i32,
ostr: *i32, olen: *i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (module == 0 as *Module || imp_ix < 0 || imp_ix >= typeck_module_num_imports(module)) {
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

/** See implementation for details. */
export function resolve_whole_import_qualified_call_return_type(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, ctx: *PipelineDepCtx, dep_index_out: *i32, func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_field: i32 = 44;
    let ord_var: i32 = 3;
    if (ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    if (callee_expr_ref <= 0 || callee_expr_ref > arena.num_exprs || module == 0 as *Module) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, callee_expr_ref) != ord_field) {
      return 0;
    }
    /* See implementation. */
    let layer_buf: u8[128] = [];
    asm_qual_sym_layer_reset();
    let nstack: i32 = 0;
    let cur_ref: i32 = callee_expr_ref;
    while (true) {
      if (cur_ref <= 0 || cur_ref > arena.num_exprs) {
        return 0;
      }
      let falen: i32 = pipeline_expr_field_access_name_len(arena, cur_ref);
      if (pipeline_expr_kind_ord_at(arena, cur_ref) != ord_field || falen <= 0 || falen > 127) {
        break;
      }
      pipeline_expr_field_access_name_into(arena, cur_ref, &layer_buf[0]);
      if (asm_qual_sym_layer_push(&layer_buf[0], falen) < 0) {
        return 0;
      }
      nstack = nstack + 1;
      cur_ref = pipeline_expr_field_access_base_ref(arena, cur_ref);
    }
    nstack = asm_qual_sym_layer_count();
    if (cur_ref <= 0 || cur_ref > arena.num_exprs) {
      return 0;
    }
    let vnlen: i32 = pipeline_expr_var_name_len(arena, cur_ref);
    if (pipeline_expr_kind_ord_at(arena, cur_ref) != ord_var || vnlen <= 0 || vnlen > 127) {
      return 0;
    }
    let vname_buf: u8[128] = [];
    pipeline_expr_var_name_into(arena, cur_ref, &vname_buf[0]);
    /**
    * See implementation.
    * See implementation.
    */
    let dep_j: i32 = 0;
    /* See implementation. */
    let n_imp: i32 = typeck_module_num_imports(module);
    while (dep_j < n_imp) {
      let plen: i32 = pipeline_module_import_path_len(module, dep_j);
      if (plen <= 0 || plen > 127) {
        dep_j = dep_j + 1;
        continue;
      }
      let path_cnt_buf: u8[128] = [];
      let pci: i32 = 0;
      /* wave584 Cap residual: copy full path content ≤127 (was pci < 64 truncate). */
      while (pci < plen && pci < 127) {
        path_cnt_buf[pci] = pipeline_module_import_path_byte_at(module, dep_j, pci);
        pci = pci + 1;
      }
      let Pseg: i32 = typeck_import_path_segment_count(&path_cnt_buf[0], plen);
      if (Pseg <= 0 || nstack != Pseg) {
        dep_j = dep_j + 1;
        continue;
      }
      let s0_rel: i32 = 0;
      let s0_ln: i32 = 0;
      if (!typeck_import_segment_at(module, dep_j, 0, &s0_rel, &s0_ln)) {
        dep_j = dep_j + 1;
        continue;
      }
      if (!typeck_import_path_slice_equal(module, dep_j, s0_rel, s0_ln, &vname_buf[0], vnlen)) {
        dep_j = dep_j + 1;
        continue;
      }
      let bad_mid: bool = false;
      let sm: i32 = 1;
      while (sm <= Pseg - 1) {
        let srv: i32 = 0;
        let slv: i32 = 0;
        if (!typeck_import_segment_at(module, dep_j, sm, &srv, &slv)) {
          bad_mid = true;
        } else {
          let lay_ix: i32 = Pseg - sm;
          asm_qual_sym_layer_copy(lay_ix, &layer_buf[0], 64);
          if (!typeck_import_path_slice_equal(module, dep_j, srv, slv, &layer_buf[0],
          asm_qual_sym_layer_len(lay_ix))) {
            bad_mid = true;
          }
        }
        if (bad_mid) {
          break;
        }
        sm = sm + 1;
      }
      if (bad_mid) {
        dep_j = dep_j + 1;
        continue;
      }
      let dep_slot: i32 = typeck_resolve_dep_index_for_import(module, ctx, dep_j);
      let dm: *Module = 0 as *Module;
      if (dep_slot < 0) {
        dep_j = dep_j + 1;
        continue;
      }
      dm = pipeline_dep_ctx_module_at(ctx, dep_slot);
      if (dm == 0 as *Module) {
        dep_j = dep_j + 1;
        continue;
      }
      asm_qual_sym_layer_copy(0, &layer_buf[0], 64);
      let ret_fn: i32 = find_func_return_type_in_module_by_name(dm, arena, &layer_buf[0],
      asm_qual_sym_layer_len(0), dep_slot, ctx, func_index_out);
      if (ret_fn != 0) {
        if (dep_index_out != 0 as *i32) {
          typeck_i32_ptr_store(dep_index_out, dep_slot);
        }
      }
      return ret_fn;
    }
    return 0;
  }
}

/**
* See implementation.
* See implementation.
* See implementation.
*/
export function resolve_call_binding_import_return_type(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, call_expr_ref: i32, ctx: *PipelineDepCtx, dep_index_out: *i32,
func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_field: i32 = 44;
    let ord_var: i32 = 3;
    let ord_import_binding: i32 = 1;
    let base_bind_ref: i32 = 0;
    let base_bind_len: i32 = 0;
    let field_len: i32 = 0;
    let ii: i32 = 0;
    let ret_b: i32 = 0;
    let dm: *Module = 0 as *Module;
    let import_kind: i32 = 0;
    let base_bind_nm: u8[128] = [];
    let field_nm: u8[128] = [];
    if (callee_expr_ref <= 0 || callee_expr_ref > arena.num_exprs || module == 0 as *Module || ctx == 
    0 as *PipelineDepCtx) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, callee_expr_ref) != ord_field) {
      return 0;
    }
    base_bind_ref = pipeline_expr_field_access_base_ref(arena, callee_expr_ref);
    if (base_bind_ref <= 0 || base_bind_ref > arena.num_exprs) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, base_bind_ref) != ord_var) {
      return 0;
    }
    base_bind_len = pipeline_expr_var_name_len(arena, base_bind_ref);
    if (base_bind_len <= 0 || base_bind_len > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, base_bind_ref, &base_bind_nm[0]);
    field_len = pipeline_expr_field_access_name_len(arena, callee_expr_ref);
    pipeline_expr_field_access_name_into(arena, callee_expr_ref, &field_nm[0]);
    ii = 0;
    let n_imp: i32 = typeck_module_num_imports(module);
    while (ii < n_imp) {
      import_kind = pipeline_module_import_kind_at(module, ii);
      if (import_kind == ord_import_binding && typeck_import_binding_name_equal(module, ii,
      &base_bind_nm[0], base_bind_len)) {
        let dep_slot: i32 = typeck_resolve_dep_index_for_import(module, ctx, ii);
        if (dep_slot < 0) {
          break;
        }
        dm = pipeline_dep_ctx_module_at(ctx, dep_slot);
        if (dm != 0 as *Module) {
          ret_b = find_func_return_type_in_module_by_name_overload(dm, arena, &field_nm[0], field_len,
          call_expr_ref, dep_slot, ctx, func_index_out);
          if (ret_b != 0) {
            if (dep_index_out != 0 as *i32) {
              typeck_i32_ptr_store(dep_index_out, dep_slot);
            }
            return ret_b;
          }
        }
        break;
      }
      ii = ii + 1;
    }
    return 0;
  }
}

/* See implementation. */
export function resolve_method_call_binding_import_return_type(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, dep_index_out: *i32, func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_var: i32 = 3;
    let ord_import_binding: i32 = 1;
    let base_ref: i32 = 0;
    let base_len: i32 = 0;
    let method_len: i32 = 0;
    let ii: i32 = 0;
    let ret_b: i32 = 0;
    let dm: *Module = 0 as *Module;
    let import_kind: i32 = 0;
    let base_nm: u8[128] = [];
    let method_nm: u8[128] = [];
    if (expr_ref <= 0 || expr_ref > arena.num_exprs || module == 0 as *Module || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref);
    if (base_ref <= 0 || base_ref > arena.num_exprs) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, base_ref) != ord_var) {
      return 0;
    }
    base_len = pipeline_expr_var_name_len(arena, base_ref);
    method_len = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (base_len <= 0 || base_len > 127 || method_len <= 0 || method_len > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, base_ref, &base_nm[0]);
    pipeline_expr_method_call_name_into(arena, expr_ref, &method_nm[0]);
    let n_imp: i32 = typeck_module_num_imports(module);
    while (ii < n_imp) {
      import_kind = pipeline_module_import_kind_at(module, ii);
      if (import_kind == ord_import_binding && typeck_import_binding_name_equal(module, ii, &base_nm[0], base_len)) {
        let dep_slot: i32 = typeck_resolve_dep_index_for_import(module, ctx, ii);
        if (dep_slot < 0) {
          break;
        }
        dm = pipeline_dep_ctx_module_at(ctx, dep_slot);
        if (dm != 0 as *Module) {
          ret_b = find_func_return_type_in_module_by_name(dm, arena, &method_nm[0], method_len, dep_slot, ctx,
            func_index_out);
          if (ret_b != 0) {
            if (dep_index_out != 0 as *i32) {
              typeck_i32_ptr_store(dep_index_out, dep_slot);
            }
            return ret_b;
          }
        }
        break;
      }
      ii = ii + 1;
    }
    return 0;
  }
}

/**
* See implementation.
* See implementation.
*/
export function resolve_call_select_import_return_type(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, callee_ord: i32, dep_ix: i32, ctx: *PipelineDepCtx,
func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_var: i32 = 3;
    let ord_import_select: i32 = 2;
    let cv_len: i32 = 0;
    let k: i32 = 0;
    let sel_cnt: i32 = 0;
    let import_kind: i32 = 0;
    let dm: *Module = 0 as *Module;
    let cv_nm: u8[128] = [];
    if (module == 0 as *Module || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    if (dep_ix < 0 || dep_ix >= typeck_module_num_imports(module) || callee_ord != ord_var) {
      return 0;
    }
    import_kind = pipeline_module_import_kind_at(module, dep_ix);
    if (import_kind != ord_import_select) {
      return 0;
    }
    cv_len = pipeline_expr_var_name_len(arena, callee_expr_ref);
    if (cv_len <= 0) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, callee_expr_ref, &cv_nm[0]);
    let dep_slot: i32 = typeck_resolve_dep_index_for_import(module, ctx, dep_ix);
    if (dep_slot < 0) {
      return 0;
    }
    dm = pipeline_dep_ctx_module_at(ctx, dep_slot);
    if (dm == 0 as *Module) {
      return 0;
    }
    sel_cnt = pipeline_module_import_select_count_at(module, dep_ix);
    k = 0;
    while (k < sel_cnt) {
      if (typeck_import_select_name_equal(module, dep_ix, k, &cv_nm[0], cv_len)) {
        return find_func_return_type_in_module_by_name(dm, arena, &cv_nm[0], cv_len, dep_slot, ctx,
        func_index_out);
      }
      k = k + 1;
    }
    return 0;
  }
}

/**
* See implementation.
*/
export function resolve_call_callee_try_whole_import(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, ctx: *PipelineDepCtx, callee_ord: i32): i32 {
  let ord_field: i32 = 44;
  let null_po: *i32 = 0 as *i32;
  if (callee_ord != ord_field) {
    return 0;
  }
  return resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx,
  null_po, null_po);
}

/**
* See implementation.
* See implementation.
*/
export function resolve_call_callee_try_binding_import(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, call_expr_ref: i32, ctx: *PipelineDepCtx, callee_ord: i32): i32 {
  let ord_field: i32 = 44;
  let null_po: *i32 = 0 as *i32;
  if (callee_ord != ord_field) {
    return 0;
  }
  return resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx,
  null_po, null_po);
}

/**
* See implementation.
*/
export function resolve_call_callee_local_module(module: *Module, arena: *ASTArena, callee_expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  /* See implementation. */
  let minus_one: i32 = -1;
  return find_func_return_type_in_module(module, arena, arena, arena, callee_expr_ref, minus_one,
  ctx, 0 as *i32);
}

/**
* See implementation.
*/
export function resolve_call_callee_scan_dep(module: *Module, arena: *ASTArena, callee_expr_ref: i32,
callee_ord: i32, ctx: *PipelineDepCtx, dep_i: i32, imax: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dm: *Module = 0 as *Module;
    let ret: i32 = 0;
    let null_po: *i32 = 0 as *i32;
    if (dep_i >= imax) {
      return 0;
    }
    dm = pipeline_dep_ctx_module_at(ctx, dep_i);
    if (dm != 0 as *Module) {
      ret = find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx,
      null_po);
      if (ret != 0) {
        return ret;
      }
      if (dep_i < typeck_module_num_imports(module)) {
        ret = resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord,
        dep_i, ctx, null_po);
        if (ret != 0) {
          return ret;
        }
      }
    }
    return resolve_call_callee_scan_dep(module, arena, callee_expr_ref, callee_ord, ctx, dep_i + 1,
    imax);
  }
}

/** See implementation for details. */
export function resolve_call_callee_return_type(module: *Module, arena: *ASTArena, callee_expr_ref: i32,
call_expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let want_apply: i32 = 0;
    let callee_ord: i32 = 0;
    let ret: i32 = 0;
    let imax: i32 = 0;
    let nd_scan: i32 = 0;
    if (callee_expr_ref <= 0 || callee_expr_ref > arena.num_exprs) {
      return 0;
    }
    if (call_expr_ref > 0 && call_expr_ref <= arena.num_exprs) {
      want_apply = 1;
    }
    callee_ord = pipeline_expr_kind_ord_at(arena, callee_expr_ref);
    ret = resolve_call_callee_try_whole_import(module, arena, callee_expr_ref, ctx, callee_ord);
    if (ret != 0) {
      if (want_apply != 0) {
        /* See implementation. */
        typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0);
        typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0);
        resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx,
        typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot());
        ast.ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(),
        typeck_call_resolve_func_idx_peek());
      }
      return ret;
    }
    ret = resolve_call_callee_try_binding_import(module, arena, callee_expr_ref, call_expr_ref, ctx,
    callee_ord);
    if (ret != 0) {
      if (want_apply != 0) {
        /* See implementation. */
        typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0);
        typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0);
        ret = resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx,
        typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot());
        ast.ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(),
        typeck_call_resolve_func_idx_peek());
      }
      return ret;
    }
    ret = resolve_call_callee_local_module(module, arena, callee_expr_ref, ctx);
    if (ret != 0) {
      if (want_apply != 0) {
        /* See implementation. */
        let minus_one_lm: i32 = -1;
        typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0);
        ret = find_func_return_type_in_module_overload(module, arena, arena, arena, callee_expr_ref,
        call_expr_ref, minus_one_lm, ctx, typeck_call_resolve_func_idx_slot());
        ast.ast_expr_apply_call_resolve(arena, call_expr_ref, minus_one_lm,
        typeck_call_resolve_func_idx_peek());
      }
      return ret;
    }
    imax = typeck_module_num_imports(module);
    nd_scan = pipeline_dep_ctx_ndep(ctx);
    if (nd_scan > imax) {
      imax = nd_scan;
    }
    return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord,
    call_expr_ref, ctx, 0, imax, want_apply);
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function expr_type_ref(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (ast.ref_is_null(expr_ref)) {
      return 0;
    }
    if (expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    return pipeline_expr_resolved_type_ref(arena, expr_ref);
  }
}

/** Exported function `type_ref_is_bool_impl`.
 * Implements `type_ref_is_bool_impl`.
 * @param arena *ASTArena
 * @param type_ref i32
 * @return bool
 */
export function type_ref_is_bool_impl(arena: *ASTArena, type_ref: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    /* See implementation. */
    let ord_bool: i32 = 1;
    return pipeline_type_kind_ord_at(arena, type_ref) == ord_bool;
  }
}

/** Exported function `type_ref_is_bool`.
 * Implements `type_ref_is_bool`.
 * @param arena *ASTArena
 * @param type_ref i32
 * @return bool
 */
export function type_ref_is_bool(arena: *ASTArena, type_ref: i32): bool {
  if (ast.ref_is_null(type_ref)) {
    return false;
  }
  if (type_ref <= 0 || type_ref > arena.num_types) {
    return false;
  }
  return type_ref_is_bool_impl(arena, type_ref);
}

/**
* See implementation.
* See implementation.
*/
export function typeck_named_unqual_start(buf: *u8, len: i32): i32 {
  let i: i32 = len - 1;
  while (i > 0) {
    if (buf[i] == 46) {
      return i + 1;
    }
    i = i - 1;
  }
  return 0;
}

/**
* See implementation.
* See implementation.
*/
/**
 * Map one type_ref to a C-safe mangle suffix (LANG-009 / CORE-016).
 * Mirrors codegen_type_ref_to_suffix / parser_asm_type_ref_mangle_suffix_c.
 * @param arena *ASTArena
 * @param type_ref i32
 * @param buf *u8
 * @param buf_cap i32
 * @return i32 — bytes written, or 0
 * PLATFORM: SHARED — typeck-local copy; no parser/codegen link edge.
 */
function typeck_type_ref_mangle_suffix(arena: *ASTArena, type_ref: i32, buf: *u8, buf_cap: i32): i32 {
  // PLATFORM: SHARED — STRUCT_LIT / named-inst equality suffix.
  unsafe {
    let tk: i32 = 0;
    let n: i32 = 0;
    let elem: i32 = 0;
    if (arena == 0 as *ASTArena || type_ref <= 0 || buf == 0 as *u8 || buf_cap <= 0) {
      return 0;
    }
    tk = pipeline_type_kind_ord_at(arena, type_ref);
    if (tk == 9) {
      /* TYPE_PTR → elem + "_ptr" */
      elem = pipeline_type_elem_ref_at(arena, type_ref);
      n = typeck_type_ref_mangle_suffix(arena, elem, buf, buf_cap);
      if (n > 0 && n + 4 < buf_cap) {
        buf[n] = 95;
        buf[n + 1] = 112;
        buf[n + 2] = 116;
        buf[n + 3] = 114;
        return n + 4;
      }
      return n;
    }
    if (tk == 8) {
      n = pipeline_type_named_name_into(arena, type_ref, buf);
      if (n <= 0 || n >= buf_cap) {
        return 0;
      }
      return n;
    }
    if (tk == 0) {
      if (buf_cap < 3) { return 0; }
      buf[0] = 105; buf[1] = 51; buf[2] = 50; return 3;
    }
    if (tk == 5) {
      if (buf_cap < 3) { return 0; }
      buf[0] = 105; buf[1] = 54; buf[2] = 52; return 3;
    }
    if (tk == 2) {
      if (buf_cap < 2) { return 0; }
      buf[0] = 117; buf[1] = 56; return 2;
    }
    if (tk == 3) {
      if (buf_cap < 3) { return 0; }
      buf[0] = 117; buf[1] = 51; buf[2] = 50; return 3;
    }
    if (tk == 4) {
      if (buf_cap < 3) { return 0; }
      buf[0] = 117; buf[1] = 54; buf[2] = 52; return 3;
    }
    if (tk == 1) {
      if (buf_cap < 4) { return 0; }
      buf[0] = 98; buf[1] = 111; buf[2] = 111; buf[3] = 108; return 4;
    }
    if (tk == 6) {
      if (buf_cap < 5) { return 0; }
      buf[0] = 117; buf[1] = 115; buf[2] = 105; buf[3] = 122; buf[4] = 101; return 5;
    }
    if (tk == 7) {
      if (buf_cap < 5) { return 0; }
      buf[0] = 105; buf[1] = 115; buf[2] = 105; buf[3] = 122; buf[4] = 101; return 5;
    }
    return 0;
  }
}

/**
 * LANG-009 / CORE-016: `Name` + type-pos args → `Name_suf0[_suf1…]`.
 * Result&lt;T,i32&gt; compresses to Result_T (drop E=i32).
 * @return i32 — mangled length, or 0
 * PLATFORM: SHARED — sole typeck named-inst spelling for equality.
 */
function typeck_named_inst_mangle_into(arena: *ASTArena, ty: i32, out: *u8, out_cap: i32): i32 {
  // PLATFORM: SHARED — Option<i32>≡Option_i32 / Result compress equality.
  unsafe {
    let base: u8[128] = [];
    let base_len: i32 = 0;
    let n_args: i32 = 0;
    let pos: i32 = 0;
    let ai: i32 = 0;
    let is_result: i32 = 0;
    let e_is_i32: i32 = 0;
    let arg: i32 = 0;
    let suf: u8[64] = [];
    let sl: i32 = 0;
    let sj: i32 = 0;
    if (arena == 0 as *ASTArena || ty <= 0 || out == 0 as *u8 || out_cap <= 0) {
      return 0;
    }
    n_args = typeck_named_num_type_args(arena, ty);
    if (n_args <= 0) {
      return 0;
    }
    base_len = pipeline_type_named_name_into(arena, ty, &base[0]);
    if (base_len <= 0 || base_len >= out_cap) {
      return 0;
    }
    pos = 0;
    while (pos < base_len) {
      out[pos] = base[pos];
      pos = pos + 1;
    }
    if (base_len == 6 && base[0] == 82 && base[1] == 101 && base[2] == 115 && base[3] == 117
        && base[4] == 108 && base[5] == 116) {
      is_result = 1;
    }
    if (is_result != 0 && n_args >= 2) {
      arg = pipeline_type_type_arg_ref_at(arena, ty, 1);
      if (arg > 0 && pipeline_type_kind_ord_at(arena, arg) == 0) {
        e_is_i32 = 1;
      }
    }
    ai = 0;
    while (ai < n_args && ai < 8) {
      if (is_result != 0 && e_is_i32 != 0 && ai == 1) {
        ai = ai + 1;
      } else {
        arg = pipeline_type_type_arg_ref_at(arena, ty, ai);
        if (arg <= 0) {
          return 0;
        }
        sl = typeck_type_ref_mangle_suffix(arena, arg, &suf[0], 64);
        if (sl <= 0 || pos + 1 + sl >= out_cap) {
          return 0;
        }
        out[pos] = 95;
        pos = pos + 1;
        sj = 0;
        while (sj < sl) {
          out[pos] = suf[sj];
          pos = pos + 1;
          sj = sj + 1;
        }
        ai = ai + 1;
      }
    }
    if (pos <= base_len) {
      return 0;
    }
    return pos;
  }
}

/**
 * TYPE_NAMED equality: bare names, unqualified tails, or LANG-009 inst mangle
 * (`Option&lt;i32&gt;` ≡ `Option_i32`; CORE-016 Result compress).
 */
export function type_refs_equal_named(arena: *ASTArena, a: i32, b: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let buf_a: *u8 = typeck_scratch64_slot(0);
    let buf_b: *u8 = typeck_scratch64_slot(1);
    let na: i32 = pipeline_type_named_name_into(arena, a, buf_a);
    let nb: i32 = pipeline_type_named_name_into(arena, b, buf_b);
    let i: i32 = 0;
    let ta: i32 = 0;
    let tb: i32 = 0;
    let ua: i32 = 0;
    let ub: i32 = 0;
    let mangled: u8[128] = [];
    let ml: i32 = 0;
    let na_args: i32 = 0;
    let nb_args: i32 = 0;
    if (na <= 0 || nb <= 0) {
      return false;
    }
    /* See implementation. */
    if (na == nb) {
      i = 0;
      while (i < na) {
        if (buf_a[i] != buf_b[i]) {
          break;
        }
        i = i + 1;
      }
      if (i == na) {
        /* Same base spelling: if both have type-args, pairwise-equal them. */
        na_args = typeck_named_num_type_args(arena, a);
        nb_args = typeck_named_num_type_args(arena, b);
        if (na_args == 0 && nb_args == 0) {
          return true;
        }
        if (na_args > 0 && nb_args > 0 && na_args == nb_args) {
          i = 0;
          while (i < na_args) {
            if (!type_refs_equal(arena, pipeline_type_type_arg_ref_at(arena, a, i),
                pipeline_type_type_arg_ref_at(arena, b, i))) {
              return false;
            }
            i = i + 1;
          }
          return true;
        }
        /* One side bare Name, other Name&lt;…&gt; — fall through to inst mangle. */
      }
    }
    /* LANG-009 / CORE-016: Name&lt;Args&gt; ≡ Name_Args mangled spelling.
     * Also match module-qualified bare names (option.Option_i32 ≡ Option&lt;i32&gt;).
     * PLATFORM: SHARED — sole named-inst ↔ family equality path. */
    na_args = typeck_named_num_type_args(arena, a);
    nb_args = typeck_named_num_type_args(arena, b);
    if (na_args > 0 && nb_args == 0) {
      ml = typeck_named_inst_mangle_into(arena, a, &mangled[0], 128);
      if (ml > 0) {
        if (ml == nb) {
          i = 0;
          while (i < ml) {
            if (mangled[i] != buf_b[i]) {
              break;
            }
            i = i + 1;
          }
          if (i == ml) {
            return true;
          }
        }
        tb = typeck_named_unqual_start(buf_b, nb);
        ub = nb - tb;
        if (ml == ub && ub > 0) {
          i = 0;
          while (i < ml) {
            if (mangled[i] != buf_b[tb + i]) {
              break;
            }
            i = i + 1;
          }
          if (i == ml) {
            return true;
          }
        }
      }
    }
    if (nb_args > 0 && na_args == 0) {
      ml = typeck_named_inst_mangle_into(arena, b, &mangled[0], 128);
      if (ml > 0) {
        if (ml == na) {
          i = 0;
          while (i < ml) {
            if (mangled[i] != buf_a[i]) {
              break;
            }
            i = i + 1;
          }
          if (i == ml) {
            return true;
          }
        }
        ta = typeck_named_unqual_start(buf_a, na);
        ua = na - ta;
        if (ml == ua && ua > 0) {
          i = 0;
          while (i < ml) {
            if (mangled[i] != buf_a[ta + i]) {
              break;
            }
            i = i + 1;
          }
          if (i == ml) {
            return true;
          }
        }
      }
    }
    /* See implementation. */
    ta = typeck_named_unqual_start(buf_a, na);
    tb = typeck_named_unqual_start(buf_b, nb);
    ua = na - ta;
    ub = nb - tb;
    if (ua != ub || ua <= 0) {
      return false;
    }
    i = 0;
    while (i < ua) {
      if (buf_a[ta + i] != buf_b[tb + i]) {
        return false;
      }
      i = i + 1;
    }
    return true;
  }
}

/**
* See implementation.
* See implementation.
*/
export function type_refs_equal_same_kind(arena: *ASTArena, a: i32, b: i32, kind_ord: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ea: i32 = 0;
    let eb: i32 = 0;
    /* See implementation. */
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_linear: i32 = 12;
    let ord_vector: i32 = 13;
    let ord_fn: i32 = TypeKind.TYPE_FN as i32;
    if (kind_ord == ord_named) {
      return type_refs_equal_named(arena, a, b);
    }
    if (kind_ord == ord_ptr || kind_ord == ord_slice || kind_ord == ord_linear) {
      ea = pipeline_type_elem_ref_at(arena, a);
      eb = pipeline_type_elem_ref_at(arena, b);
      return type_refs_equal(arena, ea, eb);
    }
    if (kind_ord == ord_array || kind_ord == ord_vector) {
      if (pipeline_type_array_size_at(arena, a) != pipeline_type_array_size_at(arena, b)) {
        return false;
      }
      ea = pipeline_type_elem_ref_at(arena, a);
      eb = pipeline_type_elem_ref_at(arena, b);
      return type_refs_equal(arena, ea, eb);
    }
    /* 10.3.1: TYPE_FN structural sig (arity + params + ret). Prior fallthrough
     * returned true for any same-kind TYPE_FN → arity/ret false-green. */
    if (kind_ord == ord_fn) {
      return typeck_fn_type_sig_equal(arena, a, b) != 0;
    }
    return true;
  }
}

/**
* See implementation.
* See implementation.
*/
export function type_refs_equal_impl(arena: *ASTArena, a: i32, b: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ka: i32 = pipeline_type_kind_ord_at(arena, a);
    let kb: i32 = pipeline_type_kind_ord_at(arena, b);
    if (ka != kb) {
      return false;
    }
    return type_refs_equal_same_kind(arena, a, b, ka);
  }
}

/**
 * Structural type_ref equality with type-alias peel (G.7 single authority).
 * wave230 pure leave: do NOT wrap residual pipeline_typeck_type_refs_equal_c
 * (that face thins back to this export — C wrap would recurse).
 * wave233: alias peel is typeck_resolve_type_alias_ref (active_module + local);
 * residual resolve_alias_c thins to that export — must not wrap residual C.
 * Then type_refs_equal_impl (named / PTR / ARRAY / VECTOR compound walk).
 * @param arena *ASTArena — type pool
 * @param a i32 — left type_ref (0/null vs null → a==b)
 * @param b i32 — right type_ref
 * @return bool — true when equal after alias resolve
 * PLATFORM: SHARED — freestanding typeck_x.o; product residual C face thins here.
 */
export function type_refs_equal(arena: *ASTArena, a: i32, b: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (ast.ref_is_null(a) || ast.ref_is_null(b)) {
      return a == b;
    }
    /* wave233 pure leave: alias peel via typeck authority (not residual C). */
    a = typeck_resolve_type_alias_ref(arena, a);
    b = typeck_resolve_type_alias_ref(arena, b);
    if (a == b) {
      return true;
    }
    return type_refs_equal_impl(arena, a, b);
  }
}

/**
* See implementation.
* See implementation.
*/
/**
 * Integer implicit widen gate for first-class TypeKind ordinals only
 * (let-init, assign, call arg, return when both sides are non-NAMED ints).
 * @param dest_kind i32 — TypeKind ordinal of the expected/declared type
 * @param src_kind i32 — TypeKind ordinal of the found/rhs type
 * @return bool — true if same integer kind or a documented widen is allowed
 * wave309 Cap residual: add TYPE_ISIZE identity + i32→isize (symmetric with
 * i32→usize; matches pipeline_typeck_integer_widen_ok_c — G.7 dual-authority).
 * Prior omit left `let a:isize = -1` / `a = -1` as found i32 (EXPR_NEG/binop).
 * wave311 Cap residual: i32→u64 (true widen; prior hole vs i32→usize on LP64)
 * and i32→u8 (narrow store of low 8 bits — var init/assign/return path verified
 * green wave712; lit coerce already green). Call single-candidate was lax.
 * wave312 Cap residual: complete first-class integer family —
 *   u8→i64/isize; u32→i64/usize/isize (plus prior u32→u64);
 *   isize↔i64 and usize↔u64 (LP64 same-width store / true widen on ILP32).
 * wave313: NAMED i8/i16/u16 use typeck_integer_widen_ok_refs (name-based).
 * PLATFORM: SHARED — seed typeck_gen + empty_surface + glue + strict_minimal same commit.
 */
export function typeck_integer_widen_ok(dest_kind: i32, src_kind: i32): bool {
  let ord_i32: i32 = 0;
  let ord_u8: i32 = 2;
  let ord_u32: i32 = 3;
  let ord_u64: i32 = 4;
  let ord_i64: i32 = 5;
  let ord_usize: i32 = 6;
  let ord_isize: i32 = 7;
  if (dest_kind == src_kind) {
    if (dest_kind == ord_i32 || dest_kind == ord_i64 || dest_kind == ord_u8 ||
    dest_kind == ord_u32 || dest_kind == ord_u64 || dest_kind == ord_usize ||
    dest_kind == ord_isize) {
      return true;
    }
    return false;
  }
  if (src_kind == ord_u8) {
    /* u8 → all wider first-class integers (wave312: +i64 +isize). */
    if (dest_kind == ord_u32 || dest_kind == ord_u64 || dest_kind == ord_usize ||
    dest_kind == ord_i32 || dest_kind == ord_i64 || dest_kind == ord_isize) {
      return true;
    }
    return false;
  }
  if (src_kind == ord_i32) {
    /* i32→isize/u64: pointer-width / fixed 64-bit; i32→u8: low-byte narrow store. */
    if (dest_kind == ord_i64 || dest_kind == ord_u32 || dest_kind == ord_u64 ||
    dest_kind == ord_usize || dest_kind == ord_isize || dest_kind == ord_u8) {
      return true;
    }
    return false;
  }
  if (src_kind == ord_u32) {
    /* wave312: u32→u64 (prior) + u32→i64/usize/isize true widen. */
    if (dest_kind == ord_u64 || dest_kind == ord_i64 || dest_kind == ord_usize ||
    dest_kind == ord_isize) {
      return true;
    }
    return false;
  }
  /* wave312: LP64 pointer-width ↔ fixed 64-bit (same bits; ILP32 true widen). */
  if (src_kind == ord_usize && dest_kind == ord_u64) {
    return true;
  }
  if (src_kind == ord_u64 && dest_kind == ord_usize) {
    return true;
  }
  if (src_kind == ord_isize && dest_kind == ord_i64) {
    return true;
  }
  if (src_kind == ord_i64 && dest_kind == ord_isize) {
    return true;
  }
  return false;
}

/**
 * Map a type_ref to an integer family tag for widen decisions.
 * @param arena *ASTArena — type pool
 * @param type_ref i32 — type ref (first-class int or TYPE_NAMED i8/i16/u16)
 * @return i32 — family id: TypeKind ord for first-class ints (0/2/3/4/5/6/7);
 *   10=i8, 11=i16, 12=u16 for TYPE_NAMED spellings; -1 if not an integer
 * wave313 Cap residual: i8/i16/u16 have no TypeKind — name-based path only.
 * PLATFORM: SHARED — seed/glue/empty_surface same commit.
 */
export function typeck_int_family_id(arena: *ASTArena, type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let k: i32 = 0;
    let nlen: i32 = 0;
    let buf: *u8 = typeck_scratch64_slot(15);
    if (ast.ref_is_null(type_ref) || type_ref <= 0) {
      return -1;
    }
    k = pipeline_type_kind_ord_at(arena, type_ref);
    /* First-class integer TypeKinds (match typeck_integer_widen_ok). */
    if (k == 0 || k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7) {
      return k;
    }
    /* TYPE_NAMED=8: only i8 / i16 / u16 participate in integer widen. */
    if (k != 8) {
      return -1;
    }
    nlen = pipeline_type_named_name_into(arena, type_ref, buf);
    /* "i8" */
    if (nlen == 2 && buf[0] == 105 && buf[1] == 56) {
      return 10;
    }
    /* "i16" */
    if (nlen == 3 && buf[0] == 105 && buf[1] == 49 && buf[2] == 54) {
      return 11;
    }
    /* "u16" */
    if (nlen == 3 && buf[0] == 117 && buf[1] == 49 && buf[2] == 54) {
      return 12;
    }
    return -1;
  }
}

/**
 * Integer widen gate with TYPE_NAMED i8/i16/u16 (wave313).
 * Prefer this over typeck_integer_widen_ok whenever both type_refs are available.
 * @param arena *ASTArena — type pool
 * @param dest_ref i32 — expected/declared type ref
 * @param src_ref i32 — found/rhs type ref
 * @return bool — true if same integer family or documented widen/narrow store
 * Rules (G.7 single authority; mirrors first-class matrix + NAMED leaf):
 *   - first-class pairs via typeck_integer_widen_ok
 *   - i8 → i16/u16/u8/i32/u32/i64/u64/usize/isize
 *   - i16 → u16/u8/i32/u32/i64/u64/usize/isize
 *   - u16 → u8/i32/u32/i64/u64/usize/isize
 *   - u8/i32 → i8/i16/u16 (narrow store, same spirit as i32→u8)
 *   - u32 → i16/u16 (narrow store residual)
 * PLATFORM: SHARED — seed typeck_gen + empty_surface + glue + strict_minimal same commit.
 */
export function typeck_integer_widen_ok_refs(arena: *ASTArena, dest_ref: i32, src_ref: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dest_f: i32 = 0;
    let src_f: i32 = 0;
    if (ast.ref_is_null(dest_ref) || ast.ref_is_null(src_ref)) {
      return false;
    }
    dest_f = typeck_int_family_id(arena, dest_ref);
    src_f = typeck_int_family_id(arena, src_ref);
    if (dest_f < 0 || src_f < 0) {
      return false;
    }
    /* Same family (includes NAMED i8/i16/u16 identity across distinct type_refs). */
    if (dest_f == src_f) {
      return true;
    }
    /* First-class TypeKind matrix (tags 0/2/3/4/5/6/7 only). */
    if (dest_f <= 7 && src_f <= 7) {
      if (typeck_integer_widen_ok(dest_f, src_f)) {
        return true;
      }
    }
    /* NAMED src → wider first-class / peer NAMED. */
    if (src_f == 10) {
      /* i8 → i16/u16/u8 + all wider first-class ints. */
      if (dest_f == 11 || dest_f == 12 || dest_f == 2 || dest_f == 0 || dest_f == 3 ||
      dest_f == 4 || dest_f == 5 || dest_f == 6 || dest_f == 7) {
        return true;
      }
      return false;
    }
    if (src_f == 11) {
      /* i16 → u16/u8 + wider first-class. */
      if (dest_f == 12 || dest_f == 2 || dest_f == 0 || dest_f == 3 || dest_f == 4 ||
      dest_f == 5 || dest_f == 6 || dest_f == 7) {
        return true;
      }
      return false;
    }
    if (src_f == 12) {
      /* u16 → u8 + wider first-class (u8 is low-byte narrow like i32→u8). */
      if (dest_f == 2 || dest_f == 0 || dest_f == 3 || dest_f == 4 || dest_f == 5 ||
      dest_f == 6 || dest_f == 7) {
        return true;
      }
      return false;
    }
    /* First-class src → NAMED dest (narrow / peer store). */
    if (dest_f == 10) {
      /* → i8 from u8/i32/i16/u16 (low-byte / narrow). */
      if (src_f == 2 || src_f == 0 || src_f == 11 || src_f == 12) {
        return true;
      }
      return false;
    }
    if (dest_f == 11) {
      /* → i16 from u8/i32/u16/u32. */
      if (src_f == 2 || src_f == 0 || src_f == 12 || src_f == 3) {
        return true;
      }
      return false;
    }
    if (dest_f == 12) {
      /* → u16 from u8/i32/i16/u32. */
      if (src_f == 2 || src_f == 0 || src_f == 11 || src_f == 3) {
        return true;
      }
      return false;
    }
    return false;
  }
}

/**
 * Float widen gate (wave314 Cap residual pure).
 * @param dest_kind i32 — TypeKind ordinal of expected/declared type
 * @param src_kind i32 — TypeKind ordinal of found/rhs type
 * @return bool — true if same float kind or f32→f64 IEEE promotion
 * Only true widen f32→f64 is implicit. Narrow f64→f32 requires explicit `as`.
 * TypeKind: TYPE_F32=14, TYPE_F64=15 (ast.x enum order).
 * PLATFORM: SHARED — seed typeck_gen + empty_surface + glue same commit.
 */
export function typeck_float_widen_ok(dest_kind: i32, src_kind: i32): bool {
  let ord_f32: i32 = 14;
  let ord_f64: i32 = 15;
  if (dest_kind == src_kind) {
    if (dest_kind == ord_f32 || dest_kind == ord_f64) {
      return true;
    }
    return false;
  }
  /* IEEE true widen only (host C promotes float→double the same way). */
  if (src_kind == ord_f32 && dest_kind == ord_f64) {
    return true;
  }
  return false;
}

/**
 * True when type_ref is a Cap-fn-ptr surface: TYPE_FN (18) or Cap *u8 (PTR→U8).
 * 10.3.1/10.3.2: TYPE_FN lets/params share the opaque fn-pointer ABI with Cap *u8
 * (asm Cap blr path). Signature compare is typeck_fnptr_surface_compat.
 * PLATFORM: SHARED.
 * @param arena *ASTArena — type pool
 * @param type_ref i32 — candidate type
 * @return i32 — 1 if Cap/TYPE_FN surface; else 0
 */
export function typeck_is_fnptr_surface(arena: *ASTArena, type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ko: i32 = 0;
    let er: i32 = 0;
    let eko: i32 = 0;
    if (arena == 0 as *ASTArena || type_ref <= 0) {
      return 0;
    }
    ko = pipeline_type_kind_ord_at(arena, type_ref);
    if (ko == TypeKind.TYPE_FN as i32) {
      return 1;
    }
    if (ko == 9) {
      er = pipeline_type_elem_ref_at(arena, type_ref);
      if (er > 0) {
        eko = pipeline_type_kind_ord_at(arena, er);
        if (eko == 2) {
          return 1;
        }
      }
    }
    return 0;
  }
}

/**
 * Structural TYPE_FN signature equality: arity (array_size) + params (type_args)
 * + return (elem_type_ref). Both refs must already be TYPE_FN (18).
 * G.7 single authority for TYPE_FN↔TYPE_FN (also used by type_refs_equal_same_kind).
 * @param arena *ASTArena — type pool
 * @param a i32 — left TYPE_FN type_ref
 * @param b i32 — right TYPE_FN type_ref
 * @return i32 — 1 equal, 0 mismatch/null
 * PLATFORM: SHARED — 10.3.1 signature slice.
 */
export function typeck_fn_type_sig_equal(arena: *ASTArena, a: i32, b: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let na: i32 = 0;
    let nb: i32 = 0;
    let i: i32 = 0;
    let ra: i32 = 0;
    let rb: i32 = 0;
    let pa: i32 = 0;
    let pb: i32 = 0;
    if (arena == 0 as *ASTArena || a <= 0 || b <= 0) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, a) != TypeKind.TYPE_FN as i32
        || pipeline_type_kind_ord_at(arena, b) != TypeKind.TYPE_FN as i32) {
      return 0;
    }
    na = pipeline_type_array_size_at(arena, a);
    nb = pipeline_type_array_size_at(arena, b);
    if (na != nb || na < 0) {
      return 0;
    }
    ra = pipeline_type_elem_ref_at(arena, a);
    rb = pipeline_type_elem_ref_at(arena, b);
    if (!type_refs_equal(arena, ra, rb)) {
      return 0;
    }
    i = 0;
    while (i < na) {
      pa = pipeline_type_type_arg_ref_at(arena, a, i);
      pb = pipeline_type_type_arg_ref_at(arena, b, i);
      if (pa <= 0 || pb <= 0 || !type_refs_equal(arena, pa, pb)) {
        return 0;
      }
      i = i + 1;
    }
    return 1;
  }
}

/**
 * Compare a same-module function (by index) to a TYPE_FN expect type.
 * Uses num_params / param_type_ref_at / return_type_at vs TYPE_FN array_size /
 * type_args / elem. PLATFORM: SHARED.
 * @param module *Module — owning module of fi
 * @param arena *ASTArena — type pool (expect + param types)
 * @param fi i32 — function index
 * @param expect_fn i32 — TYPE_FN type_ref
 * @return i32 — 1 match, 0 mismatch
 */
export function typeck_module_func_matches_type_fn(module: *Module, arena: *ASTArena, fi: i32,
expect_fn: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let np: i32 = 0;
    let n_expect: i32 = 0;
    let i: i32 = 0;
    let pret: i32 = 0;
    let eret: i32 = 0;
    let ppar: i32 = 0;
    let epar: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || fi < 0 || expect_fn <= 0) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, expect_fn) != TypeKind.TYPE_FN as i32) {
      return 0;
    }
    np = pipeline_module_func_num_params_at(module, fi);
    n_expect = pipeline_type_array_size_at(arena, expect_fn);
    if (np != n_expect || np < 0) {
      return 0;
    }
    pret = pipeline_module_func_return_type_at(module, fi);
    eret = pipeline_type_elem_ref_at(arena, expect_fn);
    if (!type_refs_equal(arena, pret, eret)) {
      return 0;
    }
    i = 0;
    while (i < np) {
      ppar = pipeline_module_func_param_type_ref_at(module, fi, i);
      epar = pipeline_type_type_arg_ref_at(arena, expect_fn, i);
      if (ppar <= 0 || epar <= 0 || !type_refs_equal(arena, ppar, epar)) {
        return 0;
      }
      i = i + 1;
    }
    return 1;
  }
}

/**
 * Same-block let init for a Cap local name (10.3.1 opaque Cap provenance).
 * @param arena *ASTArena
 * @param block_ref i32 — active typeck block
 * @param name *u8 — VAR name bytes
 * @param name_len i32
 * @return i32 — init expr_ref, or 0 if not found
 * PLATFORM: SHARED.
 */
export function typeck_block_let_init_by_name(arena: *ASTArena, block_ref: i32, name: *u8,
name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let nl: i32 = 0;
    let i: i32 = 0;
    let ln: i32 = 0;
    let nbuf: u8[128] = [];
    let j: i32 = 0;
    let eq: i32 = 0;
    if (arena == 0 as *ASTArena || block_ref <= 0 || name == 0 as *u8 || name_len <= 0
        || name_len > 127) {
      return 0;
    }
    nl = ast.ast_block_num_lets(arena, block_ref);
    i = 0;
    while (i < nl) {
      ln = pipeline_block_let_name_len(arena, block_ref, i);
      if (ln == name_len) {
        pipeline_block_let_name_copy64(arena, block_ref, i, &nbuf[0]);
        eq = 1;
        j = 0;
        while (j < name_len) {
          if (nbuf[j] != name[j]) {
            eq = 0;
            break;
          }
          j = j + 1;
        }
        if (eq != 0) {
          return pipeline_block_let_init_ref(arena, block_ref, i);
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Recover a same-module function index from Cap / AS provenance.
 *
 * Peel EXPR_AS (54) and Cap locals whose init is `bare as *u8` (or nested AS)
 * so TYPE_FN←Cap can hard-check signatures when the underlying fn is known.
 * True opaque Cap (FFI call, null Cap, unknown) returns -1 → hard reject at
 * coerce unless caller passes allow_opaque (explicit `as function`).
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr i32 — Cap-side expr
 * @param depth i32 — recurse cap (max 8)
 * @return i32 — func index ≥0, or -1
 * PLATFORM: SHARED — 10.3.1 Cap provenance slice.
 */
export function typeck_recover_fn_fi_from_cap_expr(module: *Module, arena: *ASTArena, expr: i32,
depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ko: i32 = 0;
    let ord_var: i32 = 3;
    let ord_as: i32 = 54;
    let vnlen: i32 = 0;
    let vbuf: u8[128] = [];
    let fi: i32 = 0;
    let nfuncs: i32 = 0;
    let op: i32 = 0;
    let init_r: i32 = 0;
    let ctx: *PipelineDepCtx = 0 as *PipelineDepCtx;
    let br: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr <= 0 || depth > 8) {
      return 0 - 1;
    }
    ko = pipeline_expr_kind_ord_at(arena, expr);
    if (ko == ord_as) {
      op = pipeline_expr_as_operand_ref_at(arena, expr);
      return typeck_recover_fn_fi_from_cap_expr(module, arena, op, depth + 1);
    }
    if (ko == ord_var) {
      vnlen = pipeline_expr_var_name_len(arena, expr);
      if (vnlen > 0 && vnlen <= 127) {
        pipeline_expr_var_name_into(arena, expr, &vbuf[0]);
        nfuncs = module.num_funcs;
        fi = 0;
        while (fi < nfuncs) {
          if (pipeline_module_func_name_equal_at(module, fi, &vbuf[0], vnlen) != 0) {
            return fi;
          }
          fi = fi + 1;
        }
        /* Cap local: peel its let init when active typeck block is known. */
        ctx = pipeline_typeck_active_ctx_c();
        if (ctx != 0 as *PipelineDepCtx) {
          br = pipeline_dep_ctx_current_block_ref_at(ctx);
          if (br > 0) {
            init_r = typeck_block_let_init_by_name(arena, br, &vbuf[0], vnlen);
            if (init_r > 0) {
              return typeck_recover_fn_fi_from_cap_expr(module, arena, init_r, depth + 1);
            }
          }
        }
      }
    }
    return 0 - 1;
  }
}

/**
 * Cap/TYPE_FN surface assign / coerce / as / return gate with signature when
 * checkable. G.7 single authority for all soft surface sites.
 *
 * Rules:
 * - Both TYPE_FN → typeck_fn_type_sig_equal
 * - Expect TYPE_FN + got Cap *u8 + recoverable same-module fn (bare VAR, `as *u8`,
 *   Cap local init peel) → typeck_module_func_matches_type_fn
 * - TYPE_FN←true opaque Cap: reject unless allow_opaque≠0 (explicit `as function`)
 * - Cap↔Cap / Expect Cap *u8 + got TYPE_FN → allow
 *
 * @param module *Module — may be 0 → pipeline_typeck_active_module_c()
 * @param arena *ASTArena
 * @param expect_ty i32 — destination / cast target / return expect
 * @param got_ty i32 — source / operand type
 * @param got_expr i32 — source expr (0 if unavailable; skips recover)
 * @param allow_opaque i32 — 1: opaque Cap→TYPE_FN ok (as reinterpret); 0: hard reject
 * @return i32 — 1 compatible, 0 reject
 * PLATFORM: SHARED — 10.3.1 signature / Cap provenance / opaque hard gate.
 */
export function typeck_fnptr_surface_compat(module: *Module, arena: *ASTArena, expect_ty: i32,
got_ty: i32, got_expr: i32, allow_opaque: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ek: i32 = 0;
    let gk: i32 = 0;
    let mod: *Module = module;
    let vnlen: i32 = 0;
    let vbuf: u8[128] = [];
    let fi: i32 = 0;
    let nfuncs: i32 = 0;
    let ord_var: i32 = 3;
    let recovered: i32 = 0;
    if (arena == 0 as *ASTArena || expect_ty <= 0 || got_ty <= 0) {
      return 0;
    }
    if (typeck_is_fnptr_surface(arena, expect_ty) == 0
        || typeck_is_fnptr_surface(arena, got_ty) == 0) {
      return 0;
    }
    ek = pipeline_type_kind_ord_at(arena, expect_ty);
    gk = pipeline_type_kind_ord_at(arena, got_ty);
    /* TYPE_FN ↔ TYPE_FN: hard structural signature. */
    if (ek == TypeKind.TYPE_FN as i32 && gk == TypeKind.TYPE_FN as i32) {
      return typeck_fn_type_sig_equal(arena, expect_ty, got_ty);
    }
    /* Expect TYPE_FN ← Cap *u8: recover same-module fn when checkable. */
    if (ek == TypeKind.TYPE_FN as i32 && gk == 9) {
      if (mod == 0 as *Module) {
        mod = pipeline_typeck_active_module_c();
      }
      if (mod != 0 as *Module && got_expr > 0) {
        /* Fast path: bare function VAR name. */
        if (pipeline_expr_kind_ord_at(arena, got_expr) == ord_var) {
          vnlen = pipeline_expr_var_name_len(arena, got_expr);
          if (vnlen > 0 && vnlen <= 127) {
            pipeline_expr_var_name_into(arena, got_expr, &vbuf[0]);
            nfuncs = mod.num_funcs;
            fi = 0;
            while (fi < nfuncs) {
              if (pipeline_module_func_name_equal_at(mod, fi, &vbuf[0], vnlen) != 0) {
                return typeck_module_func_matches_type_fn(mod, arena, fi, expect_ty);
              }
              fi = fi + 1;
            }
          }
        }
        /*
         * Cap provenance: peel `bare as *u8` / Cap local init → hard sig check.
         * Unrecoverable Cap: only `as function(...)` (allow_opaque) may coerce.
         * PLATFORM: SHARED — 10.3.1 slice16 opaque hard gate.
         */
        recovered = typeck_recover_fn_fi_from_cap_expr(mod, arena, got_expr, 0);
        if (recovered >= 0) {
          return typeck_module_func_matches_type_fn(mod, arena, recovered, expect_ty);
        }
      }
      /* True opaque Cap → TYPE_FN: hard reject unless explicit as. */
      if (allow_opaque != 0) {
        return 1;
      }
      return 0;
    }
    /* Cap ← TYPE_FN / Cap ← Cap: opaque ABI accept. */
    return 1;
  }
}

/**
 * If METHOD_CALL name matches a Cap/TYPE_FN field on the receiver, return that
 * field type_ref; else 0.
 *
 * 10.3.3 slice3: `h.f(args)` parses as EXPR_METHOD_CALL (not CALL+FIELD_ACCESS).
 * When `f` is an opaque fn-ptr field, accept as Cap-style call (not LANG-004).
 * Peels one TYPE_PTR so `*Holder` receivers work. PLATFORM: SHARED.
 *
 * @param module *Module — layout table
 * @param arena *ASTArena — type pool
 * @param ctx *PipelineDepCtx — dep layouts
 * @param base_ty i32 — receiver resolved type
 * @param method_nm *u8 — method / field name bytes
 * @param method_nlen i32 — name length
 * @return i32 — field type_ref if Cap/TYPE_FN surface; else 0
 */
export function typeck_method_call_field_fnptr_ty(module: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx, base_ty: i32, method_nm: *u8, method_nlen: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ty: i32 = 0;
    let ko: i32 = 0;
    let er: i32 = 0;
    let nlen: i32 = 0;
    let ftr: i32 = 0;
    let nm: u8[128] = [];
    if (module == 0 as *Module || arena == 0 as *ASTArena || base_ty <= 0
        || method_nm == 0 as *u8 || method_nlen <= 0 || method_nlen > 127) {
      return 0;
    }
    ty = base_ty;
    ko = pipeline_type_kind_ord_at(arena, ty);
    /* Peel one pointer so `(*h).f` / typed `*Holder` receivers still match. */
    if (ko == 9) {
      er = pipeline_type_elem_ref_at(arena, ty);
      if (er <= 0) {
        return 0;
      }
      ty = er;
      ko = pipeline_type_kind_ord_at(arena, ty);
    }
    if (ko != 8) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, ty, &nm[0]);
    if (nlen <= 0 || nlen > 127) {
      return 0;
    }
    ftr = get_field_type_ref_from_layout_deps(module, arena, ctx, &nm[0], nlen, method_nm,
        method_nlen);
    if (ftr <= 0) {
      return 0;
    }
    if (typeck_is_fnptr_surface(arena, ftr) != 0) {
      return ftr;
    }
    return 0;
  }
}

/*
 * F2 TYPE_DYN(17) dyn-coerce null-sentinel predicate.
 *
 * `let x: dyn Trait = 0` (literal INT_LIT 0) and the equivalent `null` form
 * represent the null fat-ptr (data=NULL, vtable=NULL) — not a real concrete
 * value needing a vtable. The dyn-coerce gate in typeck_check_expr (assign
 * path) and typeck_check_block_one_let (let-init path) calls this predicate
 * to bypass impl-lookup for the null form, mirroring the F1 path that
 * accepted `0` onto any dyn LHS.
 *
 * Returns 1 iff expr_ref is a bare INT_LIT with value 0 (the canonical null
 * representation for a fat pointer); 0 otherwise. Mirrors the existing
 * `kop == ord_lit && pipeline_expr_int_val_at(...) == 0` pattern at L7622
 * (single G.7 rule, both sites). PLATFORM: SHARED.
 *
 * @param arena *ASTArena — expr pool
 * @param rhs_type_ref i32 — resolved type_ref of RHS (reserved for future
 *        TYPE_PTR-null forms; current implementation is expr-driven)
 * @param rhs_expr_ref i32 — RHS expr_ref (the value being assigned)
 * @return i32 — 1 if null sentinel; 0 otherwise
 */
export function typeck_dyn_rhs_is_null_sentinel(arena: *ASTArena, rhs_type_ref: i32,
        rhs_expr_ref: i32): i32 {
  unsafe {
  let ord_lit: i32 = 0;
  if (ast.ref_is_null(rhs_expr_ref)) {
    return 0;
  }
  if (pipeline_expr_kind_ord_at(arena, rhs_expr_ref) != ord_lit) {
    return 0;
  }
  if (pipeline_expr_int_val_at(arena, rhs_expr_ref) != 0) {
    return 0;
  }
  return 1;
  }
}

/**
 * True when src is T[N] and dest is T[] with equal element types.
 * Let coerce stamps after this check; return / assign / call-arg score
 * must not stamp — emit wrap keys off TYPE_ARRAY to build {.data,.length}.
 * G.7: one predicate for let coerce, return match, and assign match.
 * @param arena *ASTArena — type pool
 * @param src_ty i32 — operand / RHS type ref (must be TYPE_ARRAY)
 * @param dest_ty i32 — return / LHS type ref (must be TYPE_SLICE)
 * @return i32 — 1 when array→slice with equal elems, else 0
 * PLATFORM: SHARED
 */
export function typeck_array_to_slice_ok(arena: *ASTArena, src_ty: i32, dest_ty: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let se: i32 = 0;
    let de: i32 = 0;
    if (ast.ref_is_null(src_ty) || ast.ref_is_null(dest_ty)) {
      return 0;
    }
    if (src_ty <= 0 || dest_ty <= 0) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, dest_ty) != 11) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, src_ty) != 10) {
      return 0;
    }
    se = pipeline_type_elem_ref_at(arena, src_ty);
    de = pipeline_type_elem_ref_at(arena, dest_ty);
    if (ast.ref_is_null(se) || ast.ref_is_null(de)) {
      return 0;
    }
    if (!type_refs_equal(arena, se, de)) {
      return 0;
    }
    return 1;
  }
}

/**
 * Whether a return operand type matches the function's declared return type.
 * Accepts equal types, integer widen (wave313), f32→f64 (wave314), linear unwrap,
 * and bare INT 0 → pointer (nullish lit). Does not widen bool to integer.
 * wave671 Cap residual: prior path accepted EXPR_BOOL_LIT / EXPR_LOGNOT when
 * expect was TYPE_I32 (`return true` / `return !x` false-green while
 * `return (1==1)` / `return bool_var` already mismatched). Align with wave666
 * no int↔bool and with EQ/LOGAND return mismatch. Explicit `as i32` still works
 * (EXPR_AS stamps target before match). LANG-006 bool→int on let/const init is
 * typeck_coerce_init_bool_to_int_decl only — not return.
 * [N]T → []T (equal elems) is accepted without stamping: emit wrap keys off
 * TYPE_ARRAY to materialize the fat (same contract as 4.2.10 call-arg score).
 * TYPE_FN return of a same-module Cap *u8 (bare `return foo`) reuses
 * typeck_fnptr_surface_compat with the live module — do not pass 0 and hope
 * pipeline_typeck_active_module_c() is set (leftover-PE BSS can be NULL).
 * @param module *Module — live typeck module; 0 → active_module fallback
 * @param arena *ASTArena — type/expr arena
 * @param op_ref i32 — return operand expr
 * @param expect_ref i32 — declared function return type
 * @return bool — true when operand may return as expect
 * PLATFORM: SHARED — G.7 single return match authority (typeck.x + seed twins).
 */
export function typeck_return_operand_matches(module: *Module, arena: *ASTArena, op_ref: i32, expect_ref: i32): bool {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got: i32 = expr_type_ref(arena, op_ref);
    let expect_kind: i32 = 0;
    let got_kind: i32 = 0;
    if (ast.ref_is_null(op_ref) || ast.ref_is_null(expect_ref)) {
      return true;
    }
    if (ast.ref_is_null(got)) {
      let ord_lit: i32 = 0;
      let ord_ptr: i32 = 9;
      let kop: i32 = pipeline_expr_kind_ord_at(arena, op_ref);
      expect_kind = pipeline_type_kind_ord_at(arena, expect_ref);
      if (kop == ord_lit && expect_kind == ord_ptr && pipeline_expr_int_val_at(arena, op_ref) == 0) {
        pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref);
        return true;
      }
      return false;
    }
    if (type_refs_equal(arena, got, expect_ref)) {
      return true;
    }
    expect_kind = pipeline_type_kind_ord_at(arena, expect_ref);
    got_kind = pipeline_type_kind_ord_at(arena, got);
    /* wave313: name-based refs so NAMED i8/i16/u16 widen participates on return. */
    if (typeck_integer_widen_ok_refs(arena, expect_ref, got)) {
      return true;
    }
    /* wave314: f32→f64 float widen on return. */
    if (typeck_float_widen_ok(expect_kind, got_kind)) {
      return true;
    }
    /*
     * [N]T → []T: accept, do not stamp. emit_return / asm Path B0 wrap the
     * still-TYPE_ARRAY operand into a fat pair. Stamping SLICE made host-C
     * emit a raw array and asm skip the wrap (4.2.10 lesson).
     * G.7: same predicate as let coerce / assign. PLATFORM: SHARED.
     */
    if (typeck_array_to_slice_ok(arena, got, expect_ref) != 0) {
      return true;
    }
    /*
     * 10.3.3 / 10.3.1: Cap/TYPE_FN opaque ABI on return — surface gate + signature
     * when TYPE_FN↔TYPE_FN or bare fn recoverable. G.7 typeck_fnptr_surface_compat.
     * PLATFORM: SHARED.
     */
    if (typeck_fnptr_surface_compat(module, arena, expect_ref, got, op_ref, 0) != 0) {
      return true;
    }
    let ord_linear: i32 = 12;
    if (pipeline_type_kind_ord_at(arena, got) == ord_linear) {
      let elem: i32 = pipeline_type_elem_ref_at(arena, got);
      if (!ast.ref_is_null(elem) && type_refs_equal(arena, elem, expect_ref)) {
        return true;
      }
    }
    /*
     * wave671 Cap residual: hard-fail bool → non-bool return (no BOOL_LIT/LOGNOT
     * → i32 exception). Same mismatch path as EQ/LOGAND/bool VAR return.
     */
    return false;
  }
}

/**
* See implementation.
* See implementation.
*/
/**
 * True when expr is keyword `null` (wave668 EXPR_LIT 0 tagged var_name="null").
 * Bare INT_LIT 0 has var_name_len=0 (arena alloc zero). No new ExprKind.
 * @param arena *ASTArena — expr pool
 * @param expr_ref i32 — candidate lit ref
 * @return i32 — 1 if null keyword, 0 otherwise
 * PLATFORM: SHARED — wave670 Cap residual.
 * G.7: delegates to pipeline_expr_is_null_keyword_c (var_name_len is VAR-only).
 */
export extern function pipeline_expr_is_null_keyword_c(arena: *ASTArena, expr_ref: i32): i32;

export function typeck_expr_is_null_keyword(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    return pipeline_expr_is_null_keyword_c(arena, expr_ref);
  }
}

/**
 * Coerce bare EXPR_LIT into a declared let/const type.
 * @param arena *ASTArena — type/expr arena
 * @param init_ref i32 — initializer EXPR_LIT ref
 * @param decl_ty_ref i32 — declared type ref to stamp onto the lit
 * @param decl_kind i32 — TypeKind ordinal of the declaration
 * @param init_kind i32 — ExprKind ordinal of the initializer
 * @return i32 — 1 if retyped, 0 if no coerce
 * PLATFORM: SHARED — wave307 Cap residual: use full i64 lit bits via
 * pipeline_expr_int64_val_at. Prior i32 truncation made u64max (stored as -1)
 * and i64max (low32 all-ones) fail `int_val >= 0` for u64/usize.
 * Unsuffixed lits in 2^63..2^64-1 wrap to negative i64 two's-complement but
 * remain valid u64/usize bit patterns; accept any EXPR_LIT for u64/usize
 * (mirrors u32 full-bit accept). Unary `-N` is EXPR_NEG, not bare LIT.
 * wave670: keyword `null` only coerces to TYPE_PTR (not i32/f32/array/…).
 */
export function typeck_coerce_init_lit_to_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let int_val: i64 = 0;
    let ord_expr_lit: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_vector: i32 = 13;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    if (init_kind != ord_expr_lit) {
      return 0;
    }
    /* Full i64: u64max/i64max must not pass through i32 truncation. */
    int_val = pipeline_expr_int64_val_at(arena, init_ref);
    /*
     * wave670 Cap residual: keyword `null` is pointer-context only.
     * Bare INT 0 still coerces to integers/floats/ptr (docs/06).
     * G.7: single coerce authority; reject non-ptr early before f32/array zero.
     */
    if (typeck_expr_is_null_keyword(arena, init_ref) != 0) {
      if (decl_kind == ord_ptr) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
      return 0;
    }
    if (decl_kind == ord_ptr && int_val == 0) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (decl_kind == ord_array && int_val == 0) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (decl_kind == ord_u8 && int_val >= 0 && int_val <= 255) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (decl_kind == ord_i64) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (decl_kind == ord_isize) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    /* u32: accept full bit pattern of the i64-stored lit (low 32 used at emit). */
    if (decl_kind == ord_u32) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    /*
     * wave307: u64/usize accept any bare EXPR_LIT bit pattern.
     * Decimal/hex digits past i64max wrap in lexer to negative i64 (two's
     * complement) but are valid unsigned values (e.g. u64max → -1 bits).
     */
    if (decl_kind == ord_usize || decl_kind == ord_u64) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (decl_kind == ord_named) {
      let nm16: u8[128] = [];
      let nlen16: i32 = pipeline_type_named_name_into(arena, decl_ty_ref, &nm16[0]);
      if (nlen16 == 3 && nm16[0] == 117 && nm16[1] == 49 && nm16[2] == 54
          && int_val >= 0 && int_val <= 65535) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
      if (nlen16 == 3 && nm16[0] == 105 && nm16[1] == 49 && nm16[2] == 54
          && int_val + 32768 >= 0 && int_val <= 32767) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
    }
    /* Integer literal → f32/f64 (incl. non-zero): product gate run-float init_non_zero_int.
     * Zero-only would reject `let x: f32 = 1` after strict typeck stamps lit as i32. */
    if (decl_kind == ord_f32 || decl_kind == ord_f64) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    if (int_val == 0 && (decl_kind == ord_named || decl_kind == ord_vector)) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    return 0;
  }
}

/**
 * Coerce bare float literal (or unary `-` of a float literal) to a float decl type.
 * @param arena *ASTArena — expression pool
 * @param init_ref i32 — init/RHS/return operand expr ref
 * @param decl_ty_ref i32 — destination type ref (f32 or f64)
 * @param decl_kind i32 — TypeKind ordinal of decl_ty_ref
 * @param init_kind i32 — ExprKind ordinal of init_ref
 * @return i32 — 1 if stamped, 0 if not applicable
 * wave316 Cap residual: bare FLOAT_LIT already coerced on let-init; assign/return
 * and unary `-6.0` (EXPR_NEG of FLOAT_LIT) still resolved as default f64 → type mismatch
 * on f32. G.7 single authority — peel NEG once, stamp both NEG and operand.
 * PLATFORM: SHARED — seed typeck_gen + empty_surface + pipeline_glue twin.
 */
export function typeck_coerce_init_float_lit_to_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_expr_float: i32 = 1;
    let ord_neg: i32 = 22;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let op_ref: i32 = 0;
    if (decl_kind != ord_f32 && decl_kind != ord_f64) {
      return 0;
    }
    if (init_kind == ord_expr_float) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    /* wave316: `let a: f32 = -6.0` / `return -6.0` / `a = -6.0` — EXPR_NEG of FLOAT_LIT. */
    if (init_kind == ord_neg) {
      op_ref = pipeline_expr_unary_operand_ref_at(arena, init_ref);
      if (!ast.ref_is_null(op_ref) && op_ref > 0 && op_ref <= arena.num_exprs) {
        if (pipeline_expr_kind_ord_at(arena, op_ref) == ord_expr_float) {
          pipeline_expr_set_resolved_type_ref(arena, op_ref, decl_ty_ref);
          pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
          return 1;
        }
      }
    }
    return 0;
  }
}

/**
 * After CALL / METHOD resolve: stamp FLOAT_LIT / `-float` args to formal f32/f64.
 * Args are check_expr'd against the call ambient (e.g. let Vec4f) before resolve,
 * so `simd.splat(1.0)` / `fill4(1.0)` stay default f64. G.7 reuse
 * typeck_coerce_init_float_lit_to_decl — this is only the post-resolve loop.
 * Dep formals live in the dep arena: read kind there, then
 * pipeline_type_ensure_by_kind_ord in the caller arena (same map as overload
 * score's primitive path). CALL arg i → param i; UFCS arg i → param i+1 (self).
 * @param arena *ASTArena — caller expr/type arena (must own arg refs)
 * @param expr_ref i32 — EXPR_CALL (48) or EXPR_METHOD_CALL (49)
 * @param callee_mod *Module — resolved callee module (dep or same-module)
 * @param func_ix i32 — resolved func index in callee_mod
 * @param dep_ix i32 — dep slot (>=0) or -1 same-module
 * @param ctx *PipelineDepCtx — dep arenas; nullable when dep_ix < 0
 * @param param_base i32 — 0 CALL/import-method; 1 same-module UFCS (skip self)
 * @return void
 * PLATFORM: SHARED — seed typeck_gen twin same commit.
 */
export function typeck_stamp_resolved_args_float_lit(arena: *ASTArena, expr_ref: i32,
callee_mod: *Module, func_ix: i32, dep_ix: i32, ctx: *PipelineDepCtx, param_base: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_method: i32 = 49;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let call_kind: i32 = 0;
    let i: i32 = 0;
    let n: i32 = 0;
    let arg_ref: i32 = 0;
    let param_raw: i32 = 0;
    let arg_kind: i32 = 0;
    let pk: i32 = 0;
    let caller_ty: i32 = 0;
    let da: *ASTArena = 0 as *ASTArena;
    if (arena == 0 as *ASTArena || callee_mod == 0 as *Module || expr_ref <= 0 || func_ix < 0) {
      return;
    }
    if (param_base < 0) {
      param_base = 0;
    }
    call_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (call_kind == ord_method) {
      n = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    } else {
      n = pipeline_expr_call_num_args_at(arena, expr_ref);
    }
    if (dep_ix >= 0 && ctx != 0 as *PipelineDepCtx) {
      da = pipeline_dep_ctx_arena_at(ctx, dep_ix);
      if (da == 0 as *ASTArena) {
        da = pipeline_get_dep_arena_slot(dep_ix);
      }
    }
    while (i < n) {
      if (call_kind == ord_method) {
        arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i);
      } else {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      }
      param_raw = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i + param_base);
      pk = 0;
      if (param_raw > 0) {
        if (da != 0 as *ASTArena) {
          pk = pipeline_type_kind_ord_at(da, param_raw);
        } else {
          pk = pipeline_type_kind_ord_at(arena, param_raw);
        }
      }
      if (arg_ref > 0 && (pk == ord_f32 || pk == ord_f64)) {
        caller_ty = pipeline_type_ensure_by_kind_ord(arena, pk);
        if (caller_ty > 0) {
          arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref);
          typeck_coerce_init_float_lit_to_decl(arena, arg_ref, caller_ty, pk, arg_kind);
        }
      }
      i = i + 1;
    }
  }
}

/**
* See implementation.
* See implementation.
*/
export function typeck_coerce_init_enum_field_to_decl(module: *Module, arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ix: i32 = 0;
    let ord_named: i32 = 8;
    let ord_expr_var: i32 = 3;
    let ord_field_access: i32 = 44;
    if (decl_kind != ord_named || init_kind != ord_field_access) {
      return 0;
    }
    base_ix = pipeline_expr_field_access_base_ref(arena, init_ref);
    if (!ast.ref_is_null(base_ix) && base_ix > 0 && base_ix <= arena.num_exprs) {
      let decl_buf: *u8 = typeck_scratch64_slot(0);
      let vbuf: *u8 = typeck_scratch64_slot(1);
      let field_buf: *u8 = typeck_scratch64_slot(2);
      let decl_nlen: i32 = pipeline_type_named_name_into(arena, decl_ty_ref, decl_buf);
      let vnlen: i32 = pipeline_expr_var_name_len(arena, base_ix);
      let i_nm: i32 = 0;
      let eq_nm: bool = true;
      if (pipeline_expr_kind_ord_at(arena,
      base_ix) == ord_expr_var && decl_nlen == vnlen && decl_nlen > 0) {
        pipeline_expr_var_name_into(arena, base_ix, vbuf);
        while (i_nm < decl_nlen) {
          if (decl_buf[i_nm] != vbuf[i_nm]) {
            eq_nm = false;
          }
          i_nm = i_nm + 1;
        }
        if (eq_nm) {
          let field_nlen: i32 = pipeline_expr_field_access_name_len(arena, init_ref);
          pipeline_expr_field_access_name_into(arena, init_ref, field_buf);
          let ev_tag: i32 = pipeline_module_enum_variant_tag_for_names(module, decl_buf, decl_nlen,
          field_buf, field_nlen);
          if (ev_tag >= 0) {
            pipeline_expr_set_field_access_enum_variant(arena, init_ref, ev_tag);
            pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
            return 1;
          }
        }
      }
    }
    if (pipeline_expr_field_access_is_enum_variant(arena, init_ref) != 0) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    return 0;
  }
}

/* See implementation. */
export function typeck_coerce_init_named_call_to_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_type_named: i32 = 8;
    let ord_expr_call: i32 = 48;
    if (decl_kind == ord_type_named && init_kind == ord_expr_call
    && ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, init_ref))) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    return 0;
  }
}

/* See implementation. */
export function typeck_coerce_init_resolved_alias_to_decl(module: *Module, arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_type_named: i32 = 8;
    let init_resolved: i32 = 0;
    let decl_resolved: i32 = 0;
    if (decl_kind != ord_type_named) {
      return 0;
    }
    init_resolved = pipeline_expr_resolved_type_ref(arena, init_ref);
    if (ast.ref_is_null(init_resolved)) {
      return 0;
    }
    decl_resolved = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0);
    if (ast.ref_is_null(decl_resolved)) {
      return 0;
    }
    if (!type_refs_equal(arena, decl_resolved, init_resolved)) {
      return 0;
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Coerce ARRAY_LIT elements to the element type of a fixed array or slice decl.
 * Stamps the literal's resolved_type_ref to decl_ty_ref (TYPE_ARRAY or TYPE_SLICE)
 * only when every known element matches (or widens into) the element decl type.
 * @param arena *ASTArena — expression/type pool
 * @param init_ref i32 — EXPR_ARRAY_LIT ref
 * @param decl_ty_ref i32 — TYPE_ARRAY (T[N]) or TYPE_SLICE (T[]) declaration type
 * @return i32 — 1 if handled, 0 if not applicable, -1 on nested failure or elem mismatch
 * PLATFORM: SHARED — wave328: TYPE_SLICE so host emit uses slice compound, not uint8_t[] fallback.
 *
 * wave617 Cap residual pure: also stamp bare FLOAT_LIT / `-float` elems to f32/f64.
 * Root: only typeck_coerce_init_lit_to_decl (integer EXPR_LIT) ran per elem; FLOAT_LIT
 * stayed default f64. Freestanding ARRAY_LIT store uses esz=4 for f32 but emit still
 * movabs full f64 bits → store low-32 of many finite doubles is 0 → INDEX cast run=0
 * (host-C braces hide; `as f32` cast elems already green via EXPR_AS force_ty).
 * G.7: reuse typeck_coerce_init_float_lit_to_decl (wave316 let/assign/return) — no second
 * float-coerce authority. PLATFORM: SHARED typeck · LINUX pure-asm gold.
 *
 * wave672 Cap residual: prior path stamped the outer ARRAY_LIT as decl even when an
 * element stayed bool/f32/struct after lit/float coerce → let/assign/call false-green
 * (`let a:i32[2]=[true,false]` run=1). Hard-fail known elem mismatch; do not stamp outer
 * on failure. Soft-skip still-unknown elem_ty (incomplete resolve). LANG-006 bool→int
 * is scalar let/const only — not array elems.
 *
 * 4.2.3 deep lit: recurse when the element decl is TYPE_SLICE as well as
 * TYPE_ARRAY. Prior peel only matched TYPE_ARRAY, so `let x: [][]i32 = [[1,2]]`
 * compared wave611's inferred `[2]i32` to `[]i32` (expected []i32 found [2]i32).
 * Same-layer: already-typed TYPE_ARRAY elems (`let a:[2]i32=…; [a]` → `[][]i32`)
 * reuse typeck_coerce_init_slice_from_array (no second peel). PLATFORM: SHARED.
 *
 * 10.3.1 slice12: ARRAY_LIT elems that are Cap *u8 (bare same-module fn name)
 * into TYPE_FN element decls must reuse typeck_fnptr_surface_compat (let/assign
 * authority). Prior: only type_refs_equal → `expected function, found *u8`.
 * Recoverable bare/as Cap hard-checks arity; true opaque Cap rejected on
 * coerce (allow_opaque=0); explicit `as function` may allow.
 * TYPE_FN recover uses the live module — do not pass 0 and hope
 * pipeline_typeck_active_module_c() is set (leftover-PE BSS can be NULL).
 * @param module *Module — live typeck module; 0 → active_module fallback
 * @param arena *ASTArena — expr/type pool
 * @param init_ref i32 — EXPR_ARRAY_LIT
 * @param decl_ty_ref i32 — TYPE_ARRAY / TYPE_SLICE dest
 * @return i32 — 1 stamped, 0 skip, -1 known elem mismatch
 * PLATFORM: SHARED.
 */
export function typeck_coerce_array_lit_elem_types_to_decl(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_type_array: i32 = 10;
    let ord_type_slice: i32 = 11;
    let ord_expr_array_lit: i32 = 46;
    let decl_kind_here: i32 = 0;
    let elem_decl_ref: i32 = 0;
    let elem_decl_kind: i32 = 0;
    let num_elems: i32 = 0;
    let i: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    let err_line: i32 = 0;
    let err_col: i32 = 0;
    if (ast.ref_is_null(init_ref) || ast.ref_is_null(decl_ty_ref)) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, init_ref) != ord_expr_array_lit) {
      return 0;
    }
    decl_kind_here = pipeline_type_kind_ord_at(arena, decl_ty_ref);
    /* wave328 Cap residual: accept TYPE_SLICE (i32[] = [1,2,3]) as well as TYPE_ARRAY.
     * Prior: only TYPE_ARRAY → slice array-lit never stamped → host C (uint8_t[]){…}. */
    if (decl_kind_here != ord_type_array && decl_kind_here != ord_type_slice) {
      return 0;
    }
    elem_decl_ref = pipeline_type_elem_ref_at(arena, decl_ty_ref);
    if (ast.ref_is_null(elem_decl_ref)) {
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      return 1;
    }
    elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl_ref);
    num_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref);
    while (i < num_elems) {
      let elem_ref: i32 = pipeline_expr_array_lit_elem_ref(arena, init_ref, i);
      let elem_kind: i32 = 0;
      let elem_ty: i32 = 0;
      let got_kind: i32 = 0;
      if (ast.ref_is_null(elem_ref)) {
        i = i + 1;
        continue;
      }
      elem_kind = pipeline_expr_kind_ord_at(arena, elem_ref);
      /*
       * Nested ARRAY_LIT must peel both TYPE_ARRAY (`[N][M]T`) and TYPE_SLICE
       * (`[][]T` / `[N][]T`). Recurse on the same authority so 3+ layers
       * (`[][][]T = [[[1]]]`) stamp inward; do not stop at one ARRAY peel.
       * PLATFORM: SHARED.
       */
      if (elem_kind == ord_expr_array_lit
      && (elem_decl_kind == ord_type_array || elem_decl_kind == ord_type_slice)) {
        if (typeck_coerce_array_lit_elem_types_to_decl(module, arena, elem_ref, elem_decl_ref) < 0) {
          return - 1;
        }
      } else {
        typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl_ref, elem_decl_kind, elem_kind);
        /* wave617: f32/f64 ARRAY_LIT elems — same stamp as scalar let f32 = 10.0. */
        typeck_coerce_init_float_lit_to_decl(arena, elem_ref, elem_decl_ref, elem_decl_kind, elem_kind);
        /* Already-typed [N]T elem → T[] dest: same helper as let `x: T[] = arr`. */
        typeck_coerce_init_slice_from_array(arena, elem_ref, elem_decl_ref, elem_decl_kind);
        elem_ty = expr_type_ref(arena, elem_ref);
        if (!ast.ref_is_null(elem_ty) && elem_ty > 0) {
          got_kind = pipeline_type_kind_ord_at(arena, elem_ty);
          /*
           * 10.3.1 slice12: TYPE_FN elem decl ← Cap *u8 / TYPE_FN via G.7
           * typeck_fnptr_surface_compat with the live module (same as let/assign/
           * return). Do not pass 0. PLATFORM: SHARED.
           */
          if (type_refs_equal(arena, elem_ty, elem_decl_ref)
          || typeck_integer_widen_ok_refs(arena, elem_decl_ref, elem_ty)
          || typeck_float_widen_ok(elem_decl_kind, got_kind)
          || typeck_fnptr_surface_compat(module, arena, elem_decl_ref, elem_ty, elem_ref, 0) != 0) {
            pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl_ref);
          } else {
            /*
             * wave672: known elem type does not match array/slice element decl.
             * Do not stamp outer ARRAY_LIT as decl (that was the false-green).
             */
            eb = driver_typeck_diag_scratch_expect();
            gb = driver_typeck_diag_scratch_found();
            el = typeck_diag_fmt_type_into(arena, elem_decl_ref, eb, 96);
            gl = typeck_diag_fmt_type_into(arena, elem_ty, gb, 96);
            err_line = pipeline_expr_line_at(arena, elem_ref);
            err_col = pipeline_expr_col_at(arena, elem_ref);
            driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl);
            return -1;
          }
        }
      }
      i = i + 1;
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Lane count of a SIMD/VECTOR type, or 0 if the type is not a vector.
 * TYPE_VECTOR uses array_size. TYPE_NAMED matches i32x4 / f32x4 / … ('x'+4/8/16)
 * and product aliases Vec4f (4) / Vec8i (8) — twin of typeck_vector_elem_type_ref.
 * @param arena *ASTArena — type pool
 * @param type_ref i32 — type to classify; <=0 → 0
 * @return i32 — 4 / 8 / 16 or TYPE_VECTOR array_size; 0 if not SIMD
 * PLATFORM: SHARED — coerce / wave705 / free-T gate all use this.
 */
export function typeck_vector_lanes_of_type(arena: *ASTArena, type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_type_vector: i32 = 13;
    let ord_type_named: i32 = 8;
    let tk: i32 = 0;
    let asz: i32 = 0;
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    let i: i32 = 0;
    let lanes: i32 = 0;
    if (ast.ref_is_null(type_ref) || type_ref <= 0) {
      return 0;
    }
    tk = pipeline_type_kind_ord_at(arena, type_ref);
    if (tk == ord_type_vector) {
      asz = pipeline_type_array_size_at(arena, type_ref);
      if (asz > 0) {
        return asz;
      }
      return 0;
    }
    if (tk != ord_type_named) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, type_ref, &nm[0]);
    /* See implementation. */
    i = 0;
    while (i < nlen) {
      if (nm[i] == 120) {
        i = i + 1;
        lanes = 0;
        while (i < nlen && nm[i] >= 48 && nm[i] <= 57) {
          lanes = lanes * 10 + (nm[i] as i32 - 48);
          i = i + 1;
        }
        if (lanes == 4 || lanes == 8 || lanes == 16) {
          return lanes;
        }
        return 0;
      }
      i = i + 1;
    }
    /*
     * Product aliases have no 'x'+digit spelling. Twin of
     * typeck_vector_elem_type_ref (Vec4f→f32 / Vec8i→i32). Without this,
     * coerce/wave705 treat NAMED Vec4f as 0 lanes so import METHOD extras
     * stay TYPE_ARRAY and first_idx-bind the wrong add overload.
     * PLATFORM: SHARED.
     */
    if (nlen == 5 && nm[0] == 86 && nm[1] == 101 && nm[2] == 99 && nm[3] == 52 && nm[4] == 102) {
      return 4;
    }
    if (nlen == 5 && nm[0] == 86 && nm[1] == 101 && nm[2] == 99 && nm[3] == 56 && nm[4] == 105) {
      return 8;
    }
    return 0;
  }
}

/**
 * Coerce ARRAY_LIT init to array / slice / vector declaration type.
 * @param module *Module — live typeck module; 0 → active_module fallback
 * @param arena *ASTArena — pool
 * @param init_ref i32 — init expression
 * @param decl_ty_ref i32 — declaration type
 * @param decl_kind i32 — type kind ordinal of decl
 * @param init_kind i32 — expr kind ordinal of init
 * @return i32 — 1 if coerced, 0 otherwise
 * PLATFORM: SHARED — wave328: TYPE_SLICE + ARRAY_LIT (same elem coerce as fixed array).
 */
export function typeck_coerce_init_array_vector_lit_to_decl(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_type_array: i32 = 10;
    let ord_type_slice: i32 = 11;
    let ord_type_vector: i32 = 13;
    let ord_expr_array_lit: i32 = 46;
    let lanes: i32 = 0;
    let n_elems: i32 = 0;
    let elem_decl: i32 = 0;
    let elem_decl_kind: i32 = 0;
    let i: i32 = 0;
    let elem_ref: i32 = 0;
    let ek: i32 = 0;
    let elem_ty: i32 = 0;
    let got_kind: i32 = 0;
    /* Fixed array T[N] or open slice T[] ← [e0, e1, …] */
    if ((decl_kind == ord_type_array || decl_kind == ord_type_slice)
    && init_kind == ord_expr_array_lit) {
      return typeck_coerce_array_lit_elem_types_to_decl(module, arena, init_ref, decl_ty_ref);
    }
    if (init_kind == ord_expr_array_lit) {
      n_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref);
      lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref);
      if (lanes <= 0 && decl_kind == ord_type_vector) {
        lanes = pipeline_type_array_size_at(arena, decl_ty_ref);
      }
      if (lanes > 0 && n_elems == lanes) {
        /*
         * Stage12 soft residual (2026-08-13): prior path only stamped the outer
         * ARRAY_LIT as the vector type; FLOAT_LIT elems stayed default f64.
         * Freestanding vector let-init then movabs f64 bits and store low-32
         * (many finite doubles → 0.0f) → pure-asm Vec4f[i] / simd shuffle red.
         * G.7: reuse typeck_coerce_init_float_lit_to_decl / lit coerce (wave316 /
         * wave617 array authority) on each lane elem + stamp outer.
         * PLATFORM: SHARED typeck · LINUX pure-asm gold.
         */
        elem_decl = typeck_vector_elem_type_ref(arena, decl_ty_ref);
        if (!ast.ref_is_null(elem_decl) && elem_decl > 0) {
          elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl);
          i = 0;
          while (i < n_elems) {
            elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, i);
            if (!ast.ref_is_null(elem_ref) && elem_ref > 0) {
              ek = pipeline_expr_kind_ord_at(arena, elem_ref);
              typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek);
              typeck_coerce_init_float_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek);
              /*
               * Known elem must match the SIMD lane type (≡ array/slice
               * wave672). Refuse the outer stamp so CALL score still T001
               * on `[true,…]` → i32x4 and let/assign compare the inferred
               * TYPE_ARRAY. Do not emit assign_mismatch here — CALL would
               * get the wrong diagnostic.
               * PLATFORM: SHARED.
               */
              elem_ty = expr_type_ref(arena, elem_ref);
              if (!ast.ref_is_null(elem_ty) && elem_ty > 0) {
                got_kind = pipeline_type_kind_ord_at(arena, elem_ty);
                if (type_refs_equal(arena, elem_ty, elem_decl)
                || typeck_integer_widen_ok_refs(arena, elem_decl, elem_ty)
                || typeck_float_widen_ok(elem_decl_kind, got_kind)) {
                  pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl);
                } else {
                  return 0;
                }
              }
            }
            i = i + 1;
          }
        }
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
    }
    return 0;
  }
}

/* See implementation. */
export function typeck_coerce_init_vector_binop_to_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let lref_c: i32 = 0;
    let rref_c: i32 = 0;
    /* See implementation. */
    let ord_type_vector: i32 = 13;
    let ord_add: i32 = 4;
    let ord_sub: i32 = 5;
    let ord_mul: i32 = 6;
    let ord_div: i32 = 7;
    let ord_expr_array_lit: i32 = 46;
    let lanes: i32 = 0;
    lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref);
    if (lanes <= 0 && decl_kind != ord_type_vector) {
      return 0;
    }
    if (lanes <= 0) {
      lanes = pipeline_type_array_size_at(arena, decl_ty_ref);
    }
    if (lanes <= 0) {
      return 0;
    }
    if (init_kind != ord_add && init_kind != ord_sub && init_kind != ord_mul && init_kind != ord_div) 
    {
      return 0;
    }
    lref_c = pipeline_expr_binop_left_ref_at(arena, init_ref);
    rref_c = pipeline_expr_binop_right_ref_at(arena, init_ref);
    if (!ast.ref_is_null(lref_c) && !ast.ref_is_null(rref_c)) {
      let lt_c: i32 = expr_type_ref(arena, lref_c);
      let rt_c: i32 = expr_type_ref(arena, rref_c);
      let lk_e: i32 = pipeline_expr_kind_ord_at(arena, lref_c);
      let rk_e: i32 = pipeline_expr_kind_ord_at(arena, rref_c);
      /* See implementation. */
      if (lk_e == ord_expr_array_lit && rk_e == ord_expr_array_lit
      && pipeline_expr_array_lit_num_elems_at(arena, lref_c) == lanes
      && pipeline_expr_array_lit_num_elems_at(arena, rref_c) == lanes) {
        pipeline_expr_set_resolved_type_ref(arena, lref_c, decl_ty_ref);
        pipeline_expr_set_resolved_type_ref(arena, rref_c, decl_ty_ref);
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
      if (!ast.ref_is_null(lt_c) && !ast.ref_is_null(rt_c)
      && typeck_vector_lanes_of_type(arena, lt_c) == lanes
      && typeck_vector_lanes_of_type(arena, rt_c) == lanes
      && type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_c),
      pipeline_type_elem_ref_at(arena, rt_c))) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
        return 1;
      }
    }
    return 0;
  }
}

/**
 * Coerce arithmetic / EXPR_NEG init into a scalar int or f32/f64 declaration.
 *
 * Purpose: let/assign/return of `a + b`, `a - b`, unary `-N` (and NAMED i8/i16/u16)
 * must stamp resolved_type_ref to the declared type so freestanding emit loads
 * the right width / IEEE bits (not default i32). wave319: f32/f64 + EXPR_NEG of
 * bare int lit also stamps the unary operand.
 *
 * @param arena *ASTArena — expr/type pool
 * @param init_ref i32 — init expression ref (ADD/SUB/MUL/DIV/NEG)
 * @param decl_ty_ref i32 — declared type_ref to stamp
 * @param decl_kind i32 — TypeKind ordinal of decl (I32/I64/U-star/F-star/NAMED i8/i16/u16)
 * @param init_kind i32 — ExprKind ordinal of init
 * @return i32 — 1 if stamped, 0 if not applicable
 * wave233 pure leave: body was residual int_binop_c; residual face thins here.
 * PLATFORM: SHARED — freestanding typeck_x.o.
 */
export function typeck_coerce_init_int_binop_to_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_add: i32 = 4;
    let ord_sub: i32 = 5;
    let ord_mul: i32 = 6;
    let ord_div: i32 = 7;
    let ord_neg: i32 = 22;
    let ord_lit: i32 = 0;
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    let op_ref: i32 = 0;
    if (arena == 0 as *ASTArena || init_ref <= 0 || init_ref > arena.num_exprs) {
      return 0;
    }
    /* i8/i16 live as TYPE_NAMED; u16 same. Bare int lit still via lit coerce. */
    if (decl_kind != ord_i32 && decl_kind != ord_i64 && decl_kind != ord_u8 &&
        decl_kind != ord_u32 && decl_kind != ord_u64 && decl_kind != ord_usize &&
        decl_kind != ord_isize && decl_kind != ord_f32 && decl_kind != ord_f64 &&
        decl_kind != ord_named) {
      return 0;
    }
    if (decl_kind == ord_named) {
      nlen = pipeline_type_named_name_into(arena, decl_ty_ref, &nm[0]);
      /* "i8" / "i16" / "u16" only */
      if (!((nlen == 2 && nm[0] == 105 && nm[1] == 56) ||
            (nlen == 3 && nm[0] == 105 && nm[1] == 49 && nm[2] == 54) ||
            (nlen == 3 && nm[0] == 117 && nm[1] == 49 && nm[2] == 54))) {
        return 0;
      }
    }
    if (init_kind != ord_add && init_kind != ord_sub && init_kind != ord_mul &&
        init_kind != ord_div && init_kind != ord_neg) {
      return 0;
    }
    /*
     * wave319: f32/f64 + EXPR_NEG of bare int lit — stamp operand too so
     * freestanding emit_neg loads IEEE bits (not two's-complement int).
     */
    if ((decl_kind == ord_f32 || decl_kind == ord_f64) && init_kind == ord_neg) {
      op_ref = pipeline_expr_unary_operand_ref_at(arena, init_ref);
      if (!ast.ref_is_null(op_ref) && op_ref > 0 && op_ref <= arena.num_exprs &&
          pipeline_expr_kind_ord_at(arena, op_ref) == ord_lit) {
        pipeline_expr_set_resolved_type_ref(arena, op_ref, decl_ty_ref);
      }
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Coerce bool-typed const/let init into an integer declaration type.
 *
 * Purpose: LOGAND/LOGOR/EQ..GE/LOGNOT resolve to TYPE_BOOL, while product
 * code often writes `const V: i32 = (a && b) || c` (LANG-006 c_logical).
 * CTFE already folds those trees to 0/1 in const_folded_*; this only rewrites
 * resolved_type_ref so type_refs_equal accepts the declared integer.
 *
 * Parameters: init_ref must already be type-checked; decl_ty_ref is the
 * annotated const/let type; decl_kind is pipeline_type_kind_ord_at(decl).
 * Returns 1 if coercion applied, 0 if not applicable.
 * PLATFORM: SHARED — language coerce rule; verify with lang-const c_logical.
 */
export function typeck_coerce_init_bool_to_int_decl(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-006 bool→integer init coerce (not emit-side fold).
  unsafe {
    let ord_bool: i32 = 1;
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let init_res: i32 = 0;
    let init_tk: i32 = 0;
    if (decl_kind != ord_i32 && decl_kind != ord_u8 && decl_kind != ord_u32 &&
        decl_kind != ord_u64 && decl_kind != ord_i64 && decl_kind != ord_usize &&
        decl_kind != ord_isize) {
      return 0;
    }
    init_res = pipeline_expr_resolved_type_ref(arena, init_ref);
    if (ast.ref_is_null(init_res)) {
      return 0;
    }
    init_tk = pipeline_type_kind_ord_at(arena, init_res);
    if (init_tk != ord_bool) {
      return 0;
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Coerce ARRAY_LIT const/let init into a scalar integer declaration (C5-array-len).
 *
 * Purpose: LANG-006 documents `const N: i32 = [1, 2, 3, 4]` as folding to the
 * element count. check_expr types the lit as an array, so type_refs_equal
 * rejects array≠i32 before typeck_fold_block_const_init can stamp
 * const_folded_val=num_elems. This coerce only rewrites resolved_type_ref to
 * the declared scalar so the subsequent equality check passes; the fold
 * producer (typeck_fold_block_const_init / ARRAY_LIT fold arm) still owns the
 * length stamp.
 *
 * @param arena *ASTArena — type/expr pool
 * @param init_ref i32 — already type-checked init (must be EXPR_ARRAY_LIT)
 * @param decl_ty_ref i32 — annotated const/let scalar integer type
 * @param decl_kind i32 — pipeline_type_kind_ord_at(decl)
 * @param init_kind i32 — pipeline_expr_kind_ord_at(init)
 * @return i32 — 1 if coercion applied, 0 if not this shape
 * PLATFORM: SHARED — LANG-006 C5; verify with tests/lang-const/c_array_len.x.
 */
export function typeck_coerce_init_array_lit_to_len_int_decl(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-006 C5-array-len let/const coerce (fold stamps length).
  unsafe {
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_expr_array_lit: i32 = 46;
    if (init_kind != ord_expr_array_lit) {
      return 0;
    }
    if (decl_kind != ord_i32 && decl_kind != ord_u8 && decl_kind != ord_u32 &&
        decl_kind != ord_u64 && decl_kind != ord_i64 && decl_kind != ord_usize &&
        decl_kind != ord_isize) {
      return 0;
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Let/const: coerce already-typed T[N] init to declared T[].
 * Stamps resolved_type_ref so the dest let type is TYPE_SLICE (emit looks at
 * the dest + source var, not this stamp). Return/assign must not call this
 * stamp path — they use typeck_array_to_slice_ok only.
 * @param arena *ASTArena — type/expr pool
 * @param init_ref i32 — already type-checked init expr
 * @param decl_ty_ref i32 — declared TYPE_SLICE
 * @param decl_kind i32 — TypeKind of decl_ty_ref
 * @return i32 — 1 stamped, 0 not this shape
 * PLATFORM: SHARED
 */
export function typeck_coerce_init_slice_from_array(arena: *ASTArena, init_ref: i32, decl_ty_ref: i32,
decl_kind: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let init_res: i32 = 0;
    if (decl_kind != 11) {
      return 0;
    }
    init_res = pipeline_expr_resolved_type_ref(arena, init_ref);
    if (typeck_array_to_slice_ok(arena, init_res, decl_ty_ref) == 0) {
      return 0;
    }
    pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
    return 1;
  }
}

/**
 * Stamp STRUCT_LIT elems of an ARRAY_LIT from the ARRAY/SLICE dest elem type.
 * Let `let r: [1]Wrap = [{ h: { v: a } }]` dest-stamps at
 * typeck_coerce_init_expr_to_decl. STRUCT_LIT field
 * `{ one: [{ h: { v: a } }] }` dest-stamps at
 * typeck_coerce_struct_lit_field_inits_to_layout / nest recurse.
 * Field inits are check_expr'd with expected=0; without this the inner
 * `{ v: a }` has no Holder dest and emit stores 8B (Darwin leftover 12/13).
 * Recurse ARRAY_LIT elems whose dest is ARRAY/SLICE (`{ rows: [[{ … }]] }`).
 * @param module *Module — ensure_struct_layout for nested lits (may be null)
 * @param arena *ASTArena — type/expr pool
 * @param init_ref i32 — ARRAY_LIT (46); other kinds no-op
 * @param decl_ty_ref i32 — TYPE_ARRAY (10) / TYPE_SLICE (11) dest
 * @return i32 — 1 walked elems, 0 not this shape
 * PLATFORM: SHARED — G.7 complete ARRAY_LIT dest stamp (let + STRUCT_LIT field).
 */
export function typeck_coerce_array_lit_struct_elems_to_decl(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let dk: i32 = 0;
    let ik: i32 = 0;
    let ed: i32 = 0;
    let n: i32 = 0;
    let k: i32 = 0;
    let er: i32 = 0;
    let ek: i32 = 0;
    if (arena == 0 as *ASTArena || init_ref <= 0 || init_ref > arena.num_exprs ||
    decl_ty_ref <= 0 || decl_ty_ref > arena.num_types) {
      return 0;
    }
    ik = pipeline_expr_kind_ord_at(arena, init_ref);
    dk = pipeline_type_kind_ord_at(arena, decl_ty_ref);
    if (ik != 46) {
      return 0;
    }
    if (dk != 10) {
      if (dk != 11) {
        return 0;
      }
    }
    ed = pipeline_type_elem_ref_at(arena, decl_ty_ref);
    if (ed <= 0) {
      return 0;
    }
    n = pipeline_expr_array_lit_num_elems_at(arena, init_ref);
    k = 0;
    while (k < n) {
      er = pipeline_expr_array_lit_elem_ref(arena, init_ref, k);
      if (er > 0 && er <= arena.num_exprs) {
        ek = pipeline_expr_kind_ord_at(arena, er);
        if (ek == 45) {
          typeck_coerce_init_struct_lit_to_decl(module, arena, er, ed);
        }
        if (ek == 46) {
          typeck_coerce_array_lit_struct_elems_to_decl(module, arena, er, ed);
        }
      }
      k = k + 1;
    }
    return 1;
  }
}

/**
* See implementation.
* See implementation.
*/
export function typeck_coerce_init_expr_to_decl(module: *Module, arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let decl_kind: i32 = 0;
    let init_kind: i32 = 0;
    if (ast.ref_is_null(init_ref) || ast.ref_is_null(decl_ty_ref)) {
      return 0;
    }
    if (init_ref <= 0 || init_ref > arena.num_exprs || decl_ty_ref <= 0 || decl_ty_ref > 
    arena.num_types) {
      return 0;
    }
    decl_kind = pipeline_type_kind_ord_at(arena, decl_ty_ref);
    init_kind = pipeline_expr_kind_ord_at(arena, init_ref);
    if (typeck_coerce_init_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_float_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind,
    init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_enum_field_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind,
    init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_named_call_to_decl(arena, init_ref, decl_ty_ref, decl_kind,
    init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_resolved_alias_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind) != 0) {
      return 1;
    }
    /*
     * wave672: array-lit coerce returns -1 on known elem mismatch — propagate so
     * let/const do not soft-skip unstamped init_ty and false-green.
     */
    {
      let arr_c: i32 = typeck_coerce_init_array_vector_lit_to_decl(module, arena, init_ref, decl_ty_ref,
      decl_kind, init_kind);
      if (arr_c < 0) {
        return -1;
      }
      if (arr_c != 0) {
        /*
         * Let-init `let r: [1]Wrap = [{ h: { v: a } }]` check_expr's the
         * ARRAY_LIT with expected=0; dest arrives only here. Stamp STRUCT_LIT
         * elems with the same coerce as nest `{ h: { v: a } }`.
         * PLATFORM: SHARED — G.7 complete array-elem dest.
         */
        typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_ref, decl_ty_ref);
        return 1;
      }
    }
    if (typeck_coerce_init_vector_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind,
    init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_int_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_bool_to_int_decl(arena, init_ref, decl_ty_ref, decl_kind) != 0) {
      return 1;
    }
    /* LANG-006 C5: `const N: i32 = [1,2,3,4]` — array lit → scalar len type stamp. */
    if (typeck_coerce_init_array_lit_to_len_int_decl(arena, init_ref, decl_ty_ref, decl_kind,
        init_kind) != 0) {
      return 1;
    }
    if (typeck_coerce_init_slice_from_array(arena, init_ref, decl_ty_ref, decl_kind) != 0) {
      return 1;
    }
    /* wave231: anonymous struct lit `{ fd, ... }` backfill from named decl. */
    if (typeck_coerce_init_struct_lit_to_decl(module, arena, init_ref, decl_ty_ref) != 0) {
      return 1;
    }
    return 0;
  }
}

/**
 * Coerce anonymous struct literal `{ fields… }` to a named decl type (e.g.
 * PollFd): backfill struct_lit name from TYPE_NAMED decl, ensure layout, stamp
 * resolved_type_ref. Nested `{ h: { v: a } }` field inits are also STRUCT_LIT
 * and check_expr walks them with expected=0, so they never get the field dest
 * type. Recurse the same coerce onto each nested STRUCT_LIT using the layout
 * field type (Holder for `h`). Emit `field_type_ref_at` / `field_store_sz`
 * key off the inner lit name — without this, inner `v: i32x4` sizes 8 and
 * Darwin leftover is lane2 (isolate 12 / official 108).
 * Already-named lits (check_expr dest backfill) still recurse field nests.
 *
 * @param module *Module — for ensure_struct_layout_from_struct_lit (may be null → skip layout)
 * @param arena *ASTArena
 * @param init_ref i32 — EXPR_STRUCT_LIT init
 * @param decl_ty_ref i32 — TYPE_NAMED expected type
 * @return i32 — 1 if coerced or already named and field nests walked, 0 if not applicable / fail
 * PLATFORM: SHARED freestanding typeck
 */
export function typeck_coerce_init_struct_lit_to_decl(module: *Module, arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let decl_kind: i32 = 0;
    let init_kind: i32 = 0;
    let name_len: i32 = 0;
    let decl_nm: u8[128] = [];
    let decl_nlen: i32 = 0;
    let ord_named: i32 = 8;
    let ord_struct_lit: i32 = 45;
    let num_fields: i32 = 0;
    let j: i32 = 0;
    let flen: i32 = 0;
    let init_r: i32 = 0;
    let ftr: i32 = 0;
    let field_buf: u8[128] = [];
    if (arena == 0 as *ASTArena || init_ref <= 0 || init_ref > arena.num_exprs ||
    decl_ty_ref <= 0 || decl_ty_ref > arena.num_types) {
      return 0;
    }
    decl_kind = pipeline_type_kind_ord_at(arena, decl_ty_ref);
    init_kind = pipeline_expr_kind_ord_at(arena, init_ref);
    if (decl_kind != ord_named || init_kind != ord_struct_lit) {
      return 0;
    }
    name_len = pipeline_expr_struct_lit_type_name_len(arena, init_ref);
    if (name_len <= 0) {
      decl_nlen = pipeline_type_named_name_into(arena, decl_ty_ref, &decl_nm[0]);
      if (decl_nlen <= 0 || decl_nlen > 127) {
        return 0;
      }
      pipeline_expr_struct_lit_type_name_set(arena, init_ref, &decl_nm[0], decl_nlen);
      if (module != 0 as *Module) {
        if (ensure_struct_layout_from_struct_lit(module, arena, init_ref) != 0) {
          return 0;
        }
      }
      pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref);
      name_len = decl_nlen;
      pipeline_expr_struct_lit_type_name_into(arena, init_ref, &decl_nm[0]);
    } else {
      if (name_len > 127) {
        return 0;
      }
      pipeline_expr_struct_lit_type_name_into(arena, init_ref, &decl_nm[0]);
    }
    /* Nested `{ field: { ... } }` and `{ one: [{ h: { v: a } }] }`:
     * stamp each STRUCT_LIT / ARRAY_LIT-of-STRUCT_LIT init from the dest
     * field type. check_expr of field inits uses expected=0.
     * PLATFORM: SHARED — dest-in-rbx / frame dest nest. */
    if (module != 0 as *Module && name_len > 0) {
      num_fields = pipeline_expr_struct_lit_num_fields(arena, init_ref);
      j = 0;
      while (j < num_fields) {
        flen = pipeline_expr_struct_lit_field_name_len(arena, init_ref, j);
        init_r = pipeline_expr_struct_lit_init_ref(arena, init_ref, j);
        if (flen > 0 && flen <= 127 && init_r > 0 && init_r <= arena.num_exprs) {
          pipeline_expr_struct_lit_field_name_into(arena, init_ref, j, &field_buf[0]);
          ftr = get_field_type_ref_from_layout(module, &decl_nm[0], name_len, &field_buf[0], flen);
          if (ftr > 0) {
            if (pipeline_expr_kind_ord_at(arena, init_r) == ord_struct_lit) {
              typeck_coerce_init_struct_lit_to_decl(module, arena, init_r, ftr);
            }
            if (pipeline_expr_kind_ord_at(arena, init_r) == 46) {
              typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_r, ftr);
            }
          }
        }
        j = j + 1;
      }
    }
    return 1;
  }
}

/** Exported function `typeck_diag_append_lit`.
 * Implements `typeck_diag_append_lit`.
 * @param out *u8
 * @param pos i32
 * @param cap i32
 * @param lit *u8
 * @param lit_len i32
 * @return i32
 */
export function typeck_diag_append_lit(out: *u8, pos: i32, cap: i32, lit: *u8, lit_len: i32): i32 {
  let p: i32 = pos;
  let i: i32 = 0;
  while (i < lit_len && p >= 0 && p < cap) {
    out[p] = lit[i];
    p = p + 1;
    i = i + 1;
  }
  return p;
}

/** Exported function `typeck_diag_append_u32_dec`.
 * Implements `typeck_diag_append_u32_dec`.
 * @param out *u8
 * @param pos i32
 * @param cap i32
 * @param v i32
 * @return i32
 */
export function typeck_diag_append_u32_dec(out: *u8, pos: i32, cap: i32, v: i32): i32 {
  let p: i32 = pos;
  if (v < 0 || p < 0 || p >= cap) {
    return p;
  }
  if (v == 0) {
    let zd: u8[1] = [48];
    return typeck_diag_append_lit(out, p, cap, &zd[0], 1);
  }
  /* See implementation. */
  let cnt: i32 = 0;
  let tc: i32 = v;
  while (tc > 0) {
    cnt = cnt + 1;
    tc = tc / 10;
  }
  let k: i32 = cnt - 1;
  let tm: i32 = v;
  while (tm > 0) {
    let d: i32 = tm % 10;
    tm = tm / 10;
    if ((pos + k) < 0 || (pos + k) >= cap) {
      return p;
    }
    out[pos + k] = ((d + 48) as u8);
    k = k - 1;
  }
  return pos + cnt;
}

/** Exported function `typeck_diag_fmt_type_at`.
 * Implements `typeck_diag_fmt_type_at`.
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @param cur i32
 * @param cap i32
 * @return i32
 */
export function typeck_diag_fmt_type_at(arena: *ASTArena, ref: i32, out: *u8, cur: i32, cap: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let qmk: u8[1] = [63];
    let lit_i32: u8[3] = [105, 51, 50];
    let lit_bool: u8[4] = [98, 111, 111, 108];
    let lit_u8: u8[2] = [117, 56];
    let lit_u32: u8[3] = [117, 51, 50];
    let lit_u64: u8[3] = [117, 54, 52];
    let lit_i64: u8[3] = [105, 54, 52];
    let lit_usize: u8[5] = [117, 115, 105, 122, 101];
    let lit_isize: u8[5] = [105, 115, 105, 122, 101];
    let lit_f32: u8[3] = [102, 51, 50];
    let lit_f64: u8[3] = [102, 54, 52];
    /* wave663: format TYPE_VOID as "void" (was bare "?"). */
    let lit_void: u8[4] = [118, 111, 105, 100];
    /* 10.3.1: format TYPE_FN as "function" (was bare "?"). Full
     * function(...): Ret pretty-print can land with resolve/codegen. */
    let lit_fn: u8[8] = [102, 117, 110, 99, 116, 105, 111, 110];
    let star: u8[1] = [42];
    let lbk: u8[1] = [91];
    let rbk: u8[1] = [93];
    let slo: u8[2] = [91, 93];
    let kind: i32 = 0;
    let nlen: i32 = 0;
    let elem_ref: i32 = 0;
    let asz: i32 = 0;
    let ord_i32: i32 = 0;
    let ord_bool: i32 = 1;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_linear: i32 = 12;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_void: i32 = 16;
    let ord_fn: i32 = 18;
    let nm_buf: *u8 = typeck_scratch64_slot(0);
    if (cur < 0 || cap <= 0 || cur >= cap) {
      return cur;
    }
    if (ast.ref_is_null(ref) || ref <= 0 || ref > arena.num_types) {
      return typeck_diag_append_lit(out, cur, cap, &qmk[0], 1);
    }
    kind = pipeline_type_kind_ord_at(arena, ref);
    if (kind == ord_named) {
      nlen = pipeline_type_named_name_into(arena, ref, nm_buf);
      if (nlen > 0) {
        return typeck_diag_append_lit(out, cur, cap, nm_buf, nlen);
      }
    }
    if (kind == ord_i32) {
      return typeck_diag_append_lit(out, cur, cap, &lit_i32[0], 3);
    }
    if (kind == ord_bool) {
      return typeck_diag_append_lit(out, cur, cap, &lit_bool[0], 4);
    }
    if (kind == ord_u8) {
      return typeck_diag_append_lit(out, cur, cap, &lit_u8[0], 2);
    }
    if (kind == ord_u32) {
      return typeck_diag_append_lit(out, cur, cap, &lit_u32[0], 3);
    }
    if (kind == ord_u64) {
      return typeck_diag_append_lit(out, cur, cap, &lit_u64[0], 3);
    }
    if (kind == ord_i64) {
      return typeck_diag_append_lit(out, cur, cap, &lit_i64[0], 3);
    }
    if (kind == ord_usize) {
      return typeck_diag_append_lit(out, cur, cap, &lit_usize[0], 5);
    }
    if (kind == ord_isize) {
      return typeck_diag_append_lit(out, cur, cap, &lit_isize[0], 5);
    }
    if (kind == ord_f32) {
      return typeck_diag_append_lit(out, cur, cap, &lit_f32[0], 3);
    }
    if (kind == ord_f64) {
      return typeck_diag_append_lit(out, cur, cap, &lit_f64[0], 3);
    }
    if (kind == ord_void) {
      return typeck_diag_append_lit(out, cur, cap, &lit_void[0], 4);
    }
    if (kind == ord_fn) {
      return typeck_diag_append_lit(out, cur, cap, &lit_fn[0], 8);
    }
    if (kind == ord_ptr) {
      elem_ref = pipeline_type_elem_ref_at(arena, ref);
      let nex: i32 = typeck_diag_append_lit(out, cur, cap, &star[0], 1);
      return typeck_diag_fmt_type_at(arena, elem_ref, out, nex, cap);
    }
    if (kind == ord_slice) {
      let lt_ch: u8[1] = [60];
      let gt_ch: u8[1] = [62];
      let rlen: i32 = 0;
      let rbuf: *u8 = typeck_scratch64_slot(15);
      elem_ref = pipeline_type_elem_ref_at(arena, ref);
      let nex2: i32 = typeck_diag_append_lit(out, cur, cap, &slo[0], 2);
      nex2 = typeck_diag_fmt_type_at(arena, elem_ref, out, nex2, cap);
      rlen = pipeline_type_region_label_len_at(arena, ref);
      if (rlen > 0 && pipeline_type_region_label_into(arena, ref, rbuf) == rlen) {
        let p0: i32 = typeck_diag_append_lit(out, nex2, cap, &lt_ch[0], 1);
        let p1: i32 = typeck_diag_append_lit(out, p0, cap, rbuf, rlen);
        return typeck_diag_append_lit(out, p1, cap, &gt_ch[0], 1);
      }
      return nex2;
    }
    if (kind == ord_linear) {
      let lpar: u8[7] = [76, 105, 110, 101, 97, 114, 40];
      let rpar: u8[1] = [41];
      elem_ref = pipeline_type_elem_ref_at(arena, ref);
      let p0: i32 = typeck_diag_append_lit(out, cur, cap, &lpar[0], 7);
      let p1: i32 = typeck_diag_fmt_type_at(arena, elem_ref, out, p0, cap);
      return typeck_diag_append_lit(out, p1, cap, &rpar[0], 1);
    }
    if (kind == ord_array) {
      elem_ref = pipeline_type_elem_ref_at(arena, ref);
      asz = pipeline_type_array_size_at(arena, ref);
      if (!ast.ref_is_null(elem_ref) && asz > 0) {
        let p0: i32 = typeck_diag_append_lit(out, cur, cap, &lbk[0], 1);
        let p1: i32 = typeck_diag_append_u32_dec(out, p0, cap, asz);
        let p2: i32 = typeck_diag_append_lit(out, p1, cap, &rbk[0], 1);
        return typeck_diag_fmt_type_at(arena, elem_ref, out, p2, cap);
      }
    }
    return typeck_diag_append_lit(out, cur, cap, &qmk[0], 1);
  }
}

/** Exported function `typeck_diag_fmt_type_into`.
 * Implements `typeck_diag_fmt_type_into`.
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @param cap i32
 * @return i32
 */
export function typeck_diag_fmt_type_into(arena: *ASTArena, ref: i32, out: *u8, cap: i32): i32 {
  return typeck_diag_fmt_type_at(arena, ref, out, 0, cap);
}

/** Exported function `typeck_diag_fmt_type_or_question`.
 * Implements `typeck_diag_fmt_type_or_question`.
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @return i32
 */
export function typeck_diag_fmt_type_or_question(arena: *ASTArena, ref: i32, out: *u8): i32 {
  let qmk: u8[1] = [63];
  if (ast.ref_is_null(ref) || ref <= 0 || ref > arena.num_types) {
    return typeck_diag_append_lit(out, 0, 96, &qmk[0], 1);
  }
  return typeck_diag_fmt_type_into(arena, ref, out, 96);
}

/**
* See implementation.
* See implementation.
*/
export function typeck_ret_coerce_integral_to_expect_i32(arena: *ASTArena, op_ref: i32,
expect_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_usize: i32 = 6;
    if (ast.ref_is_null(op_ref) || op_ref <= 0 || op_ref > arena.num_exprs || ast.ref_is_null(expect_ref)) {
      return;
    }
    if (expect_ref <= 0 || expect_ref > arena.num_types) {
      return;
    }
    /* See implementation. */
    if (pipeline_type_kind_ord_at(arena, expect_ref) != ord_i32) {
      return;
    }
    let got_ref: i32 = expr_type_ref(arena, op_ref);
    if (ast.ref_is_null(got_ref) || got_ref <= 0 || got_ref > arena.num_types) {
      return;
    }
    let got_kind: i32 = pipeline_type_kind_ord_at(arena, got_ref);
    /* See implementation. */
    if (got_kind != ord_u8 && got_kind != ord_usize) {
      return;
    }
    pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref);
  }
}

/**
* See implementation.
* See implementation.
*/
export function typeck_ret_coerce_integral_widen(arena: *ASTArena, op_ref: i32, expect_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got_ref: i32 = 0;
    let expect_kind: i32 = 0;
    let got_kind: i32 = 0;
    if (ast.ref_is_null(op_ref) || op_ref <= 0 || op_ref > arena.num_exprs || ast.ref_is_null(expect_ref)) {
      return;
    }
    if (expect_ref <= 0 || expect_ref > arena.num_types) {
      return;
    }
    got_ref = expr_type_ref(arena, op_ref);
    if (ast.ref_is_null(got_ref) || got_ref <= 0 || got_ref > arena.num_types) {
      return;
    }
    expect_kind = pipeline_type_kind_ord_at(arena, expect_ref);
    got_kind = pipeline_type_kind_ord_at(arena, got_ref);
    /* wave313: refs path covers NAMED i8/i16/u16 as well as first-class. */
    if (typeck_integer_widen_ok_refs(arena, expect_ref, got_ref)) {
      pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref);
      return;
    }
    /* wave314: f32-to-f64 return is accepted by return_operand_matches; do not stamp
     * (freestanding emit promotes with SSE convert using true float32 bits).
     * wave1218: avoid digit+letter glues in comments before (void) casts;
     * lparen rewind probes can land mid-comment and sticky-L009 the parse. */
    /* wave1219: removed (void)expect_kind / (void)got_kind — C-style cast not
     * supported in X (parsed as call to unresolved `void` function). Variables
     * are assigned-but-unused; safe to drop the cast-to-void suppression. */
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function typeck_ret_coerce_null_lit_to_expect(arena: *ASTArena, op_ref: i32, expect_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_lit: i32 = 0;
    let ord_ptr: i32 = 9;
    let op_kind: i32 = 0;
    let expect_kind: i32 = 0;
    let int_val: i32 = 0;
    if (arena == 0 as *ASTArena || ast.ref_is_null(op_ref) || ast.ref_is_null(expect_ref)) {
      return;
    }
    op_kind = pipeline_expr_kind_ord_at(arena, op_ref);
    if (op_kind != ord_lit) {
      return;
    }
    expect_kind = pipeline_type_kind_ord_at(arena, expect_ref);
    int_val = pipeline_expr_int_val_at(arena, op_ref);
    if (expect_kind == ord_ptr && int_val == 0) {
      pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref);
    }
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function typeck_ret_fixup_unresolved_call(module: *Module, arena: *ASTArena, op_ref: i32,
ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_call: i32 = 48;
    let op_kind: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ast.ref_is_null(op_ref)) {
      return;
    }
    if (!ast.ref_is_null(expr_type_ref(arena, op_ref))) {
      return;
    }
    op_kind = pipeline_expr_kind_ord_at(arena, op_ref);
    if (op_kind != ord_call) {
      return;
    }
    typeck_check_expr_call_resolve(module, arena, op_ref, ctx);
  }
}

/**
 * See implementation.
 */
export function typeck_return_breadcrumb_into(arena: *ASTArena, expr_ref: i32, out: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_var: i32 = 3;
    let ord_field: i32 = 44;
    let ord_call: i32 = 48;
    let ord_method_call: i32 = 49;
    let kind: i32 = 0;
    let base_ref: i32 = 0;
    let callee_ref: i32 = 0;
    let base_len: i32 = 0;
    let field_len: i32 = 0;
    let callee_len: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (kind == ord_var) {
      base_len = pipeline_expr_var_name_len(arena, expr_ref);
      if (base_len <= 0 || base_len > 60) {
        return 0;
      }
      pipeline_expr_var_name_into(arena, expr_ref, out);
      out[base_len] = 0;
      return base_len;
    }
    if (kind == ord_field) {
      base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref);
      if (base_ref <= 0 || base_ref > arena.num_exprs) {
        return 0;
      }
      base_len = typeck_return_breadcrumb_into(arena, base_ref, out);
      field_len = pipeline_expr_field_access_name_len(arena, expr_ref);
      if (base_len <= 0 || field_len <= 0 || base_len + 1 + field_len > 60) {
        return 0;
      }
      out[base_len] = 46;
      pipeline_expr_field_access_name_into(arena, expr_ref, &out[base_len + 1]);
      out[base_len + 1 + field_len] = 0;
      return base_len + 1 + field_len;
    }
    if (kind == ord_call) {
      callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      callee_len = typeck_return_breadcrumb_into(arena, callee_ref, out);
      if (callee_len <= 0 || callee_len + 2 > 60) {
        return 0;
      }
      out[callee_len] = 40;
      out[callee_len + 1] = 41;
      out[callee_len + 2] = 0;
      return callee_len + 2;
    }
    if (kind == ord_method_call) {
      base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref);
      base_len = typeck_return_breadcrumb_into(arena, base_ref, out);
      field_len = pipeline_expr_method_call_name_len(arena, expr_ref);
      if (base_len <= 0 || field_len <= 0 || base_len + 3 + field_len > 60) {
        return 0;
      }
      out[base_len] = 46;
      pipeline_expr_method_call_name_into(arena, expr_ref, &out[base_len + 1]);
      out[base_len + 1 + field_len] = 40;
      out[base_len + 2 + field_len] = 41;
      out[base_len + 3 + field_len] = 0;
      return base_len + 3 + field_len;
    }
    return 0;
  }
}

/** Function `typeck_emit_return_subexpr_breadcrumb`.
 * Purpose: implements `typeck_emit_return_subexpr_breadcrumb`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
export function typeck_emit_return_subexpr_breadcrumb(arena: *ASTArena, expr_ref: i32, line: i32,
col: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let buf: *u8 = typeck_scratch64_slot(2);
    let bl: i32 = typeck_return_breadcrumb_into(arena, expr_ref, buf);
    if (bl > 0) {
      driver_diagnostic_typeck_return_subexpr(line, col, buf, bl);
    }
  }
}

/** Function `typeck_emit_return_unresolved_breadcrumb`.
 * Purpose: implements `typeck_emit_return_unresolved_breadcrumb`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
export function typeck_emit_return_unresolved_breadcrumb(arena: *ASTArena, expr_ref: i32, line: i32,
col: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let buf: *u8 = typeck_scratch64_slot(2);
    let bl: i32 = typeck_return_breadcrumb_into(arena, expr_ref, buf);
    if (bl > 0) {
      driver_diagnostic_typeck_return_unresolved(line, col, buf, bl);
    }
  }
}

/** Exported function `typeck_check_expr_float_lit`.
 * Implements `typeck_check_expr_float_lit`.
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32
 */
export function typeck_check_expr_float_lit(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    pipeline_expr_typeck_set_float_bits_from_val(arena, expr_ref);
    let ft: i32 = ensure_f64_type_ref(arena);
    if (ft != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ft);
    }
    return 0;
  }
}

/**
 * Default-type EXPR_LIT: i32 when |v| fits int32, else i64.
 * wave670: keyword `null` (int_val=0 + var_name="null") is not stamped —
 * only TYPE_PTR coerce may retype it.
 * @param arena *ASTArena — expr pool
 * @param expr_ref i32 — EXPR_LIT ref
 * @param return_type_ref i32 — optional expect for null→ptr coerce (0 = skip)
 * @return i32 — always 0 (side-effect stamp only)
 * wave233 pure leave: body was residual int_lit_c; residual face thins here
 * with return_type_ref=0. PLATFORM: SHARED freestanding typeck_x.o.
 */
export function typeck_check_expr_int_lit(arena: *ASTArena, expr_ref: i32, return_type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let v: i64 = 0;
    let ty: i32 = 0;
    let vlen: i32 = 0;
    let vname: u8[8] = [];
    let i32_max: i64 = 2147483647;
    let i32_min: i64 = -2147483648;
    let ord_i32: i32 = 0;
    let ord_i64: i32 = 5;
    typeck_ret_coerce_null_lit_to_expect(arena, expr_ref, return_type_ref);
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    /* Already resolved — no-op (matches residual int_lit_c). */
    if (!ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return 0;
    }
    /*
     * wave670 Cap residual: keyword `null` is EXPR_LIT 0 tagged var_name="null".
     * Do not default-stamp as i32 — only TYPE_PTR coerce may retype it.
     */
    v = pipeline_expr_int64_val_at(arena, expr_ref);
    vlen = pipeline_expr_var_name_len(arena, expr_ref);
    if (v == 0 && vlen == 4) {
      pipeline_expr_var_name_into(arena, expr_ref, &vname[0]);
      if (vname[0] == 110 && vname[1] == 117 && vname[2] == 108 && vname[3] == 108) {
        return 0;
      }
    }
    if (v > i32_max || v < i32_min) {
      ty = pipeline_type_ensure_by_kind_ord(arena, ord_i64);
    } else {
      ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32);
    }
    if (ty != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty);
    }
    return 0;
  }
}

/** Exported function `typeck_check_expr_bool_lit`.
 * Implements `typeck_check_expr_bool_lit`.
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32
 */
export function typeck_check_expr_bool_lit(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let bt: i32 = ensure_bool_type_ref(arena);
    if (bt != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt);
    }
    return 0;
  }
}

/** Exported function `typeck_check_expr_string_lit`.
 * Implements `typeck_check_expr_string_lit`.
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32
 */
export function typeck_check_expr_string_lit(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let u8r: i32 = ensure_u8_type_ref(arena);
    let ptr_u8: i32 = 0;
    if (ast.ref_is_null(u8r)) {
      return -1;
    }
    ptr_u8 = find_or_alloc_ptr_type_ref(arena, u8r);
    if (!ast.ref_is_null(ptr_u8)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_u8);
    }
    return 0;
  }
}

/**
 * Type-check `asm!("template"[, in("reg") expr])` (stage10 10.2.1).
 * Stamps TYPE_VOID. Requires unsafe nest (g_typeck_unsafe_depth > 0);
 * reuses extern-call-outside-unsafe diagnostic until a dedicated asm! diag exists.
 * Slice1: typeck each call_arg operand via pipeline_typeck_check_expr_impl_c.
 * Slice6: skip discard place VAR "_" (clobber; not a binding).
 * @param module *Module — for operand recursion
 * @param arena *ASTArena — expr arena
 * @param expr_ref i32 — EXPR_ASM (60)
 * @param return_type_ref i32 — forwarded to operand check
 * @param ctx *PipelineDepCtx — unsafe depth + operand ctx
 * @return i32 — 0 ok, -1 outside unsafe / operand fail
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_check_expr_asm(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — inline asm requires unsafe (docs/10 K1a).
  unsafe {
    let vt: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let nargs: i32 = 0;
    let i: i32 = 0;
    let arg_ref: i32 = 0;
    let arc: i32 = 0;
    let ako: i32 = 0;
    let alen: i32 = 0;
    let aname: u8[8] = [];
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    if (pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) <= 0) {
      line = pipeline_expr_line_at(arena, expr_ref);
      col = pipeline_expr_col_at(arena, expr_ref);
      driver_diagnostic_typeck_extern_call_outside_unsafe(line, col);
      return 0 - 1;
    }
    nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
    i = 0;
    while (i < nargs) {
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      if (arg_ref > 0) {
        /* Discard `_` is not a local — do not resolve as unbound VAR. */
        ako = pipeline_expr_kind_ord_at(arena, arg_ref);
        if (ako == 3) {
          alen = pipeline_expr_var_name_len(arena, arg_ref);
          if (alen == 1) {
            pipeline_expr_var_name_into(arena, arg_ref, &aname[0]);
            if (aname[0] == (95 as u8)) {
              i = i + 1;
              continue;
            }
          }
        }
        arc = pipeline_typeck_check_expr_impl_c(module, arena, arg_ref, return_type_ref, ctx);
        if (arc != 0) {
          return arc;
        }
      }
      i = i + 1;
    }
    vt = ensure_void_type_ref(arena);
    if (!ast.ref_is_null(vt)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, vt);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_break_continue(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_break: i32 = 39;
    let ord_continue: i32 = 40;
    let line: i32 = 0;
    let col: i32 = 0;
    let kind: i32 = 0;
    let is_break: i32 = 1;
    if (pipeline_dep_ctx_typeck_loop_depth_at(ctx) > 0) {
      return 0;
    }
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (kind == ord_continue) {
      is_break = 0;
    }
    driver_diagnostic_typeck_break_continue_outside(line, col, is_break);
    return - 1;
  }
}

/** Exported function `typeck_check_expr_enum_variant`.
 * Implements `typeck_check_expr_enum_variant`.
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32
 */
export function typeck_check_expr_enum_variant(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let it: i32 = ensure_i32_type_ref(arena);
    if (it != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, it);
    }
    return 0;
  }
}

/* See implementation. */
export function typeck_check_expr_if_ternary(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_ternary: i32 = 27;
    let ord_named: i32 = 8;
    let ord_lit: i32 = 0;
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let expr_kind: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let cond_ref: i32 = pipeline_expr_if_cond_ref_at(arena, expr_ref);
    let then_ref: i32 = pipeline_expr_if_then_ref_at(arena, expr_ref);
    let else_ref: i32 = pipeline_expr_if_else_ref_at(arena, expr_ref);
    let ty_t: i32 = 0;
    let ty_e: i32 = 0;
    let t_named: bool = false;
    let e_named: bool = false;
    let resolved: i32 = 0;
    let cond_ty: i32 = 0;
    let expect_kind: i32 = 0;
    let got_kind: i32 = 0;
    let then_k: i32 = 0;
    let else_k: i32 = 0;
    let tv: i32 = 0;
    let ev: i32 = 0;
    /*
     * wave704: if/ternary condition ambient must be 0 (bool), not fn return type.
     * `if (count <= 0)` in `*i32` fn ambient-stamped lit 0 as *i32 → T001.
     * PLATFORM: SHARED.
     */
    if (check_expr(module, arena, cond_ref, 0, ctx) != 0) {
      return - 1;
    }
    if (!ast.ref_is_null(cond_ref)) {
      cond_ty = expr_type_ref(arena, cond_ref);
      if (!type_ref_is_bool(arena, cond_ty)) {
        return - 1;
      }
    }
    if (check_expr(module, arena, then_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (!ast.ref_is_null(else_ref)) {
      if (check_expr(module, arena, else_ref, return_type_ref, ctx) != 0) {
        return - 1;
      }
    }
    ty_t = expr_type_ref(arena, then_ref);
    ty_e = expr_type_ref(arena, else_ref);
    if (!ast.ref_is_null(ty_t) && ty_t > 0) {
      t_named = (pipeline_type_kind_ord_at(arena, ty_t) == ord_named);
    }
    if (!ast.ref_is_null(ty_e) && ty_e > 0) {
      e_named = (pipeline_type_kind_ord_at(arena, ty_e) == ord_named);
    }
    if (expr_kind == ord_ternary) {
      if (ast.ref_is_null(ty_t)) {
        return - 1;
      }
      if (ast.ref_is_null(ty_e)) {
        return - 1;
      }
      if (!type_refs_equal(arena, ty_t, ty_e)) {
        return - 1;
      }
      resolved = ty_t;
      if (!ast.ref_is_null(return_type_ref) && return_type_ref > 0 && return_type_ref <= arena.num_types) {
        expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
        got_kind = pipeline_type_kind_ord_at(arena, ty_t);
        if (typeck_integer_widen_ok_refs(arena, return_type_ref, ty_t)) {
          resolved = return_type_ref;
        } else if (typeck_float_widen_ok(expect_kind, got_kind)) {
          /* wave314: ternary arms f32 under f64 expect. */
          resolved = return_type_ref;
        } else if (expect_kind == ord_u8 && got_kind == ord_i32) {
          /* See implementation. */
          then_k = pipeline_expr_kind_ord_at(arena, then_ref);
          else_k = pipeline_expr_kind_ord_at(arena, else_ref);
          if (then_k == ord_lit && else_k == ord_lit) {
            tv = pipeline_expr_int_val_at(arena, then_ref);
            ev = pipeline_expr_int_val_at(arena, else_ref);
            if (tv >= 0 && tv <= 255 && ev >= 0 && ev <= 255) {
              resolved = return_type_ref;
              pipeline_expr_set_resolved_type_ref(arena, then_ref, return_type_ref);
              pipeline_expr_set_resolved_type_ref(arena, else_ref, return_type_ref);
            }
          }
        }
      }
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved);
      return 0;
    }
    if (!ast.ref_is_null(ty_t) && !ast.ref_is_null(ty_e) && t_named && e_named) {
      if (!type_refs_equal(arena, ty_t, ty_e)) {
        return - 1;
      }
    }
    if (!ast.ref_is_null(ty_t) && !ast.ref_is_null(ty_e)) {
      if (e_named && !t_named) {
        resolved = ty_e;
      } else {
        resolved = ty_t;
      }
    } else if (!ast.ref_is_null(ty_t)) {
      resolved = ty_t;
    } else if (!ast.ref_is_null(ty_e)) {
      resolved = ty_e;
    }
    if (ast.ref_is_null(resolved) && !ast.ref_is_null(return_type_ref)
        && return_type_ref > 0 && return_type_ref <= arena.num_types) {
      /* dest-in-rbx IF of STRUCT_LIT both arms (`*p = if (c) { { h: { v: a } } }
       * else { { h: { v: b } } }`). Each arm is a BLOCK whose final
       * STRUCT_LIT dest-stamps, but the BLOCK expr type stayed `?` so
       * assign saw expected Wrap, found ?. Dest already checked both
       * arms. G.7: IF result is the dest type.
       * PLATFORM: SHARED dest-in-rbx IF STRUCT_LIT. */
      expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
      if (expect_kind == ord_named) {
        resolved = return_type_ref;
      }
    }
    if (!ast.ref_is_null(resolved)) {
      /* See implementation. */
      if (!ast.ref_is_null(return_type_ref) && return_type_ref > 0 && return_type_ref <= arena.num_types) {
        expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
        got_kind = pipeline_type_kind_ord_at(arena, resolved);
        if (typeck_integer_widen_ok_refs(arena, return_type_ref, resolved)) {
          resolved = return_type_ref;
        } else if (typeck_float_widen_ok(expect_kind, got_kind)) {
          /* wave314: if-expr result f32 under f64 expect. */
          resolved = return_type_ref;
        }
      }
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved);
    }
    return 0;
  }
}

/** Exported function `typeck_block_expr_value_ref`.
 * Implements `typeck_block_expr_value_ref`.
 * @param arena *ASTArena
 * @param block_ref i32
 * @return i32
 */
export function typeck_block_expr_value_ref(arena: *ASTArena, block_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let stmt_order_kind_region_c_parser: u8 = 5 as u8;
    let stmt_order_kind_region_x_parser: u8 = 6 as u8;
    let fin_ref: i32 = 0;
    let nso: i32 = 0;
    let last_k: u8 = 0 as u8;
    let ridx: i32 = 0;
    let nreg: i32 = 0;
    let inner_ref: i32 = 0;
    if (ast.ref_is_null(block_ref) || block_ref <= 0 || block_ref > arena.num_blocks) {
      return 0;
    }
    fin_ref = ast.ast_block_final_expr_ref(arena, block_ref);
    if (!ast.ref_is_null(fin_ref)) {
      return fin_ref;
    }
    nso = ast.ast_block_num_stmt_order(arena, block_ref);
    if (nso <= 0) {
      return 0;
    }
    last_k = ast.ast_block_stmt_order_kind(arena, block_ref, nso - 1);
    if (last_k != stmt_order_kind_region_c_parser && last_k != stmt_order_kind_region_x_parser) {
      return 0;
    }
    ridx = ast.ast_block_stmt_order_idx(arena, block_ref, nso - 1);
    nreg = ast.ast_block_num_regions(arena, block_ref);
    if (ridx < 0 || ridx >= nreg) {
      return 0;
    }
    if (pipeline_block_region_is_unsafe(arena, block_ref, ridx) == 0) {
      return 0;
    }
    inner_ref = ast.ast_block_region_body_ref(arena, block_ref, ridx);
    return typeck_block_expr_value_ref(arena, inner_ref);
  }
}

/** Function `typeck_check_expr_block`.
 * Purpose: implements `typeck_check_expr_block`; params/returns as declared (may be multi-line).
 * Contracts: null/cap/PLATFORM as enforced in the body.
 */
export function typeck_check_expr_block(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_assign: i32 = 28;
    let block_ref: i32 = pipeline_expr_block_ref_at(arena, expr_ref);
    let fin_blk: i32 = 0;
    let ty_fin: i32 = 0;
    let nes: i32 = 0;
    let fst_es: i32 = 0;
    let st_kind: i32 = 0;
    let rhs_ref: i32 = 0;
    let ty_rhs: i32 = 0;
    if (check_block(module, arena, block_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (ast.ref_is_null(block_ref) || block_ref <= 0) {
      return 0;
    }
    fin_blk = typeck_block_expr_value_ref(arena, block_ref);
    if (!ast.ref_is_null(fin_blk)) {
      ty_fin = expr_type_ref(arena, fin_blk);
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_fin);
      return 0;
    }
    nes = ast.ast_block_num_expr_stmts(arena, block_ref);
    if (nes != 1) {
      return 0;
    }
    fst_es = pipeline_block_expr_stmt_ref(arena, block_ref, 0);
    if (fst_es <= 0) {
      return 0;
    }
    st_kind = pipeline_expr_kind_ord_at(arena, fst_es);
    if (st_kind != ord_assign && (st_kind < 29 || st_kind > 39)) {
      return 0;
    }
    rhs_ref = pipeline_expr_binop_right_ref_at(arena, fst_es);
    if (ast.ref_is_null(rhs_ref)) {
      return 0;
    }
    ty_rhs = expr_type_ref(arena, rhs_ref);
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_rhs);
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_assign(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_assign: i32 = 28;
    let ord_add_assign: i32 = 29;
    let ord_sub_assign: i32 = 30;
    let ord_lit: i32 = 0;
    let ord_var: i32 = 3;
    let ord_ternary: i32 = 27;
    let ord_add: i32 = 4;
    let ord_sub: i32 = 5;
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_type_array: i32 = 10;
    let ord_field: i32 = 44;
    let ord_index: i32 = 47;
    let ord_call: i32 = 48;
    let ord_expr_array_lit: i32 = 46;
    let ord_string_lit: i32 = 59;
    let expr_kind: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let left_ref: i32 = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    let right_ref: i32 = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    let line: i32 = pipeline_expr_line_at(arena, expr_ref);
    let col: i32 = pipeline_expr_col_at(arena, expr_ref);
    /* wave236–237 pure leave: stack-escape + scope-borrow + allocator region. */
    if (typeck_check_struct_stack_escape_assign(module, arena, expr_ref, left_ref, right_ref, ctx) != 0) {
      return - 1;
    }
    if (typeck_check_scope_borrow_assign(module, arena, expr_ref, left_ref, right_ref, ctx) != 0) {
      return - 1;
    }
    let lt: i32 = 0;
    let rt: i32 = 0;
    let rt_after: i32 = 0;
    let rhs_ctx: i32 = 0;
    let compound_flag: i32 = 1;
    let lt_kind: i32 = 0;
    let rhs_kind: i32 = 0;
    let lhs_kind: i32 = 0;
    let int_val: i32 = 0;
    let ev: i32 = 0;
    let then_r: i32 = 0;
    let else_r: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    /*
     * F1 TYPE_DYN(17): dyn LHS accepts any concrete RHS. Foundation-wave
     * dyn is shape-only (concrete->dyn coerce + vtable are F2+), so the
     * equal-ref gate must not fire for `x: dyn T = 0` style stores. Set in
     * the final gate block; skips mismatch + slice-region checks like the
     * wave643 compound-offset exemption. Same semantic authority as the
     * let-init gate in typeck_check_block_one_let (single G.7 rule).
     * PLATFORM: SHARED.
     */
    let dyn_assign_ok: i32 = 0;
    /*
     * wave643: 1 when compound *T +=/-= integer offset is accepted (C-like ≡ p = p ± n).
     * Do not stamp RHS to *T (emit wave642 scales integer offset by sizeof(*p)).
     */
    let ptr_compound_offset_ok: i32 = 0;
    if (expr_kind == ord_assign) {
      compound_flag = 0;
    }
    /*
     * Assign LHS must not inherit the *function* return ambient.
     * wave465 stamps unconstrained field results with ambient; when LHS is
     * FIELD_ACCESS (`out.method = m` / `s.c = c`), feeding return_type_ref
     * rewrote the field type to the function return (or void→`?`) and caused
     * "expected S/?, found Color|Method" on enum field stores that already
     * type as R-values. G.7: check left with expected 0; then use resolved
     * lt as RHS expected (below). PLATFORM: SHARED.
     */
    if (check_expr(module, arena, left_ref, 0, ctx) != 0) {
      return - 1;
    }
    /*
     * AL-04 assign after LHS is typed so resolved/let type is visible.
     * Before check_expr(left) the decl type scan was a miss and the
     * conservative unknown-type reject fired on scalar `k = 1`.
     * G.7: same authority, just after the stamp. PLATFORM: SHARED.
     */
    if (typeck_check_allocator_region_assign(module, arena, expr_ref, left_ref, ctx) != 0) {
      return - 1;
    }
    /*
     * wave678 Cap residual: const is immutable (docs/06). VAR LHS only;
     * block parent chain then top-level const. G.7 twin of product
     * pipeline_typeck_check_expr_assign_c. PLATFORM: SHARED.
     */
    {
      let lhs_kind_c: i32 = pipeline_expr_kind_ord_at(arena, left_ref);
      if (lhs_kind_c == ord_var) {
        let vbuf_c: u8[128] = [];
        let vnlen_c: i32 = pipeline_expr_var_name_len(arena, left_ref);
        let bind_kind: i32 = -1;
        let br_c: i32 = 0;
        let bi: i32 = 0;
        if (vnlen_c > 0 && vnlen_c < 128) {
          pipeline_expr_var_name_into(arena, left_ref, &vbuf_c[0]);
          if (ctx != 0 as *PipelineDepCtx) {
            br_c = pipeline_dep_ctx_current_block_ref_at(ctx);
            if (br_c > 0) {
              bind_kind = pipeline_block_name_binding_kind(arena, br_c, &vbuf_c[0], vnlen_c);
            }
          }
          if (bind_kind < 0) {
            bi = pipeline_module_top_level_name_is_const(module, &vbuf_c[0], vnlen_c);
            if (bi != 0) {
              bind_kind = 1;
            }
          }
          if (bind_kind == 1) {
            driver_diagnostic_typeck_assign_to_const(line, col);
            return -1;
          }
        }
      }
    }
    lt = expr_type_ref(arena, left_ref);
    rhs_ctx = return_type_ref;
    if (!ast.ref_is_null(lt)) {
      rhs_ctx = lt;
    }
    /*
     * wave643 Cap residual: compound `p += n` / `p -= n` is C-like pointer
     * arithmetic (≡ `p = p ± n`). The compound RHS is an *integer offset*, not
     * *T. Prior path set rhs_ctx = lt (*T) then required type_refs_equal →
     * "expected *i32, found i32" while `p = p + 1` already greened (wave285
     * binop + wave642 freestanding scale). G.7: complete same assign authority
     * (no second compound-ptr path); offset kinds match wave285 (i32/usize/isize
     * plus common integer widths for typed offset vars). PLATFORM: SHARED —
     * seed typeck_gen same commit.
     */
    if (compound_flag != 0 && !ast.ref_is_null(lt)
    && (expr_kind == ord_add_assign || expr_kind == ord_sub_assign)) {
      lt_kind = pipeline_type_kind_ord_at(arena, lt);
      if (lt_kind == ord_ptr) {
        rhs_ctx = 0;
      }
    }
    if (check_expr(module, arena, right_ref, rhs_ctx, ctx) != 0) {
      return - 1;
    }
    if (ast.ref_is_null(left_ref) || ast.ref_is_null(right_ref)) {
      return 0;
    }
    if (ast.ref_is_null(lt)) {
      lt = expr_type_ref(arena, left_ref);
    }
    rt_after = expr_type_ref(arena, right_ref);
    if (!ast.ref_is_null(lt) && lt > 0) {
      rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref);
      lt_kind = pipeline_type_kind_ord_at(arena, lt);
      /*
       * wave331: assign ARRAY_LIT → TYPE_ARRAY or TYPE_SLICE (G.7 reuse
       * typeck_coerce_array_lit_elem_types_to_decl; let-init wave328 already accepted
       * TYPE_SLICE — assign previously only TYPE_ARRAY → `a:i32[] = []` found `?`).
       */
      {
        let ord_type_slice: i32 = 11;
        if (rhs_kind == ord_expr_array_lit
        && (lt_kind == ord_type_array || lt_kind == ord_type_slice)) {
          if (typeck_coerce_array_lit_elem_types_to_decl(module, arena, right_ref, lt) < 0) {
            return - 1;
          }
          rt_after = expr_type_ref(arena, right_ref);
        }
      }
      /*
       * wave308: assign RHS bare EXPR_LIT — reuse typeck_coerce_init_lit_to_decl
       * (G.7 single authority; same full-i64 path as let-init / wave307).
       * Prior hand path used pipeline_expr_int_val_at (i32 truncate) +
       * `int_val >= 0` for u64/usize, so `a = u64max` / `a = i64max` failed.
       * wave310: assign RHS EXPR_NEG / int binop — reuse typeck_coerce_init_int_binop_to_decl
       * (closes `a:u8=-1` / `a:u16=-1` / `a:u64=-1` assign + `1-2`; let-init already had int_binop).
       * wave316: assign/compound RHS FLOAT_LIT / `-float` — reuse typeck_coerce_init_float_lit_to_decl
       * (closes `a:f32 = 6.0` / `a += 2.0` / `a = -6.0`; let-init already had float lit).
       * PLATFORM: SHARED — typeck lit/binop/float/array-lit assign coerce.
       */
      if (!type_refs_equal(arena, lt, rt_after)) {
        if (rhs_kind == ord_lit) {
          typeck_coerce_init_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind);
        } else {
          typeck_coerce_init_float_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind);
          typeck_coerce_init_int_binop_to_decl(arena, right_ref, lt, lt_kind, rhs_kind);
        }
      }
      /*
       * wave670: keyword `null` only for TYPE_PTR assign RHS. Unstamped null
       * would soft-skip the lt/rt equal check below.
       */
      if (typeck_expr_is_null_keyword(arena, right_ref) != 0 && lt_kind != ord_ptr) {
        eb = driver_typeck_diag_scratch_expect();
        gb = driver_typeck_diag_scratch_found();
        el = typeck_diag_fmt_type_into(arena, lt, eb, 96);
        gl = typeck_diag_append_lit(gb, 0, 96, "null", 4);
        driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl);
        return -1;
      }
    }
    rt = expr_type_ref(arena, right_ref);
    if (!ast.ref_is_null(lt) && !ast.ref_is_null(rt) && !type_refs_equal(arena, lt, rt)) {
      lt_kind = pipeline_type_kind_ord_at(arena, lt);
      let rt_kind_assign: i32 = pipeline_type_kind_ord_at(arena, rt);
      /* wave313: refs path so NAMED i8/i16/u16 assign widen is accepted. */
      if (typeck_integer_widen_ok_refs(arena, lt, rt)) {
        pipeline_expr_set_resolved_type_ref(arena, right_ref, lt);
        rt = lt;
      } else if (typeck_float_widen_ok(lt_kind, rt_kind_assign)) {
        /* wave314: f32→f64 assign accepted; do not stamp RHS (emit needs cvtss2sd). */
        /* leave rt as f32 so store path can promote. */
      }
    }
    if (!ast.ref_is_null(lt) && !ast.ref_is_null(rt) && !type_refs_equal(arena, lt, rt)) {
      rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref);
      if (rhs_kind == ord_ternary) {
        lt_kind = pipeline_type_kind_ord_at(arena, lt);
        if (lt_kind == ord_u8) {
          then_r = pipeline_expr_if_then_ref_at(arena, right_ref);
          else_r = pipeline_expr_if_else_ref_at(arena, right_ref);
          if (pipeline_expr_kind_ord_at(arena, then_r) == ord_lit &&
          pipeline_expr_kind_ord_at(arena, else_r) == ord_lit) {
            int_val = pipeline_expr_int_val_at(arena, then_r);
            ev = pipeline_expr_int_val_at(arena, else_r);
            if (int_val >= 0 && int_val <= 255 && ev >= 0 && ev <= 255) {
              pipeline_expr_set_resolved_type_ref(arena, then_r, lt);
              pipeline_expr_set_resolved_type_ref(arena, else_r, lt);
              pipeline_expr_set_resolved_type_ref(arena, right_ref, lt);
              rt = lt;
            }
          }
        }
      }
    }
    if (!ast.ref_is_null(lt) && ast.ref_is_null(rt)) {
      rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref);
      if (rhs_kind == ord_call) {
        pipeline_expr_set_resolved_type_ref(arena, right_ref, lt);
        rt = lt;
      }
/** See implementation for details. */
      if (rhs_kind == ord_string_lit) {
        pipeline_expr_set_resolved_type_ref(arena, right_ref, lt);
        rt = lt;
      }
/** See implementation for details. */
      if (rhs_kind == ord_field) {
        lt_kind = pipeline_type_kind_ord_at(arena, lt);
        if (typeck_coerce_init_enum_field_to_decl(module, arena, right_ref, lt, lt_kind, rhs_kind) != 0) {
          rt = expr_type_ref(arena, right_ref);
        }
      }
    }
    if (ast.ref_is_null(lt) && !ast.ref_is_null(rt)) {
      lhs_kind = pipeline_expr_kind_ord_at(arena, left_ref);
      if (lhs_kind == ord_var || lhs_kind == ord_field || lhs_kind == ord_index) {
        pipeline_expr_set_resolved_type_ref(arena, left_ref, rt);
        lt = rt;
      }
    }
    /*
     * wave643: *T +=/-= integer offset — accept without requiring lt==rt and
     * without stamping RHS to *T. Reject *T += *U (would type_refs_equal if
     * rhs_ctx stayed *T) and *T += float/struct etc. G.7 ≡ wave285 ptr±int.
     */
    if (compound_flag != 0 && !ast.ref_is_null(lt) && !ast.ref_is_null(rt)
    && (expr_kind == ord_add_assign || expr_kind == ord_sub_assign)) {
      lt_kind = pipeline_type_kind_ord_at(arena, lt);
      if (lt_kind == ord_ptr) {
        let rt_kind_pca: i32 = pipeline_type_kind_ord_at(arena, rt);
        if (rt_kind_pca == ord_i32 || rt_kind_pca == ord_usize || rt_kind_pca == ord_isize
        || rt_kind_pca == ord_u8 || rt_kind_pca == ord_u32 || rt_kind_pca == ord_u64
        || rt_kind_pca == ord_i64) {
          ptr_compound_offset_ok = 1;
        } else {
          eb = driver_typeck_diag_scratch_expect();
          gb = driver_typeck_diag_scratch_found();
          el = typeck_diag_fmt_type_into(arena, lt, eb, 96);
          gl = typeck_diag_fmt_type_into(arena, rt, gb, 96);
          driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl);
          return - 1;
        }
      }
    }
    if (!ast.ref_is_null(lt) && !ast.ref_is_null(rt)) {
      /*
       * F2 TYPE_DYN(17): dyn LHS accepts a concrete RHS only when either
       * (a) the RHS is the null-dyn sentinel (literal INT_LIT 0 — null
       * fat-ptr representation, no vtable needed) OR (b) a registered
       * `impl Trait for RHS_type` block exists in the impl table. Concrete
       * RHS without impl leaves dyn_assign_ok = 0 so the downstream
       * type_refs_equal mismatch gate fires with the standard
       * "expected dyn Trait, found T" diagnostic.
       *
       * F1 history: blanket `dyn_assign_ok = 1` accepted any RHS (dyn was
       * shape-only). F2 closes that hole with real impl-lookup; null-dyn
       * sentinel preserves the F1 path for `let x: dyn Trait = 0`.
       * Mirrors the let-init gate in typeck_check_block_one_let (single
       * G.7 rule; same semantic authority, both sides). PLATFORM: SHARED.
       */
      if (pipeline_type_kind_ord_at(arena, lt) == TypeKind.TYPE_DYN as i32) {
        if (typeck_dyn_rhs_is_null_sentinel(arena, rt, right_ref) != 0) {
          dyn_assign_ok = 1;
        } else {
          let trait_nm_asg: u8[64] = [];
          let tnl_asg: i32 = pipeline_type_named_name_into(arena, lt, &trait_nm_asg[0]);
          if (tnl_asg > 0 && xlang_skip_impl_concrete_implements_trait_c(
                  arena as *void, rt, &trait_nm_asg[0], tnl_asg) != 0) {
            dyn_assign_ok = 1;
          }
        }
      }
      /*
       * 10.3.1: TYPE_FN LHS accepts Cap *u8 / TYPE_FN RHS with signature when
       * checkable (G.7 typeck_fnptr_surface_compat). PLATFORM: SHARED.
       */
      if (typeck_fnptr_surface_compat(module, arena, lt, rt, right_ref, 0) != 0) {
        dyn_assign_ok = 1;
      }
      if (!type_refs_equal(arena, lt, rt) && ptr_compound_offset_ok == 0 && dyn_assign_ok == 0) {
        lt_kind = pipeline_type_kind_ord_at(arena, lt);
        let rt_kind_mis: i32 = pipeline_type_kind_ord_at(arena, rt);
        /* wave314: f32→f64 is not a mismatch (emit promotes with cvtss2sd). */
        /* [N]T → []T: accept without stamping (emit assign wrap keys off ARRAY). */
        if (!typeck_float_widen_ok(lt_kind, rt_kind_mis)
        && typeck_array_to_slice_ok(arena, rt, lt) == 0) {
          eb = driver_typeck_diag_scratch_expect();
          gb = driver_typeck_diag_scratch_found();
          el = typeck_diag_fmt_type_into(arena, lt, eb, 96);
          gl = typeck_diag_fmt_type_into(arena, rt, gb, 96);
          driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl);
          return - 1;
        }
      }
      /* See implementation. */
      if (ptr_compound_offset_ok == 0 && dyn_assign_ok == 0
      && typeck_check_slice_region_assign(arena, expr_ref, lt, rt) != 0) {
        return - 1;
      }
    }
    if (!ast.ref_is_null(lt) && ast.ref_is_null(rt)) {
      rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref);
      if (rhs_kind == ord_sub || rhs_kind == ord_add) {
        lt_kind = pipeline_type_kind_ord_at(arena, lt);
        if (lt_kind == ord_usize) {
          pipeline_expr_set_resolved_type_ref(arena, right_ref, lt);
          rt = lt;
        }
      }
    }
    eb = driver_typeck_diag_scratch_expect();
    gb = driver_typeck_diag_scratch_found();
    if (ast.ref_is_null(lt) && !ast.ref_is_null(rt)) {
      el = typeck_diag_fmt_type_or_question(arena, lt, eb);
      gl = typeck_diag_fmt_type_or_question(arena, rt, gb);
      driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl);
      return - 1;
    }
    if (!ast.ref_is_null(lt) && ast.ref_is_null(rt)) {
      el = typeck_diag_fmt_type_or_question(arena, lt, eb);
      gl = typeck_diag_fmt_type_or_question(arena, rt, gb);
      driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl);
      return - 1;
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_return(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_void: i32 = 16;
    let ord_lit: i32 = 0;
    let ord_as: i32 = 54;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_ptr: i32 = 9;
    let op_ref: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let rt_kind: i32 = 0;
    let op_kind: i32 = 0;
    let int_val: i32 = 0;
    let as_tgt: i32 = 0;
    let got: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    if (ast.ref_is_null(op_ref)) {
      if (!ast.ref_is_null(return_type_ref)) {
        rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
        if (rt_kind != ord_void) {
          driver_diagnostic_typeck_ret_fail(1, expr_ref, return_type_ref, 0);
          return - 1;
        }
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
      }
      return 0;
    }
    if (!ast.ref_is_null(return_type_ref)) {
      rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
      if (rt_kind == ord_void) {
        got = expr_type_ref(arena, op_ref);
        driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got);
        return - 1;
      }
    }
    /* See implementation. */
    typeck_ret_fixup_unresolved_call(module, arena, op_ref, ctx);
    if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
      if (ast.ref_is_null(expr_type_ref(arena, op_ref))) {
        typeck_emit_return_unresolved_breadcrumb(arena, op_ref, line, col);
      } else {
        typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col);
      }
      driver_diagnostic_typeck_ret_fail(1, op_ref, return_type_ref, 0);
      return - 1;
    }
    typeck_ret_coerce_null_lit_to_expect(arena, op_ref, return_type_ref);
    /* See implementation. */
    if (!ast.ref_is_null(op_ref) && !ast.ref_is_null(return_type_ref)) {
      let rk_ret: i32 = pipeline_type_kind_ord_at(arena, return_type_ref);
      let ok_ret: i32 = pipeline_expr_kind_ord_at(arena, op_ref);
      /*
       * wave318: return bare int lit → f32/f64 (and other lit targets).
       * let/assign already call typeck_coerce_init_lit_to_decl; return only had
       * float_lit (wave316) + a partial hand-written i64/u32/u64/ptr0 path →
       * `function f(): f32 { return 6; }` reported expected f32 found i32.
       * wave319: return EXPR_NEG / int binop → f32/f64 — G.7 reuse
       * typeck_coerce_init_int_binop_to_decl (let/assign already call it).
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + pipeline_glue twin.
       */
      typeck_coerce_init_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret);
      /* wave316: return float lit / `-float` to f32/f64 (G.7 reuse float_lit coerce). */
      typeck_coerce_init_float_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret);
      /* wave319: return `-6` / `1-7` int tree to f32/f64 (G.7 reuse int_binop). */
      typeck_coerce_init_int_binop_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret);
      if (typeck_coerce_init_enum_field_to_decl(module, arena, op_ref, return_type_ref, rk_ret, ok_ret) != 0) {
        /* stamped */
      }
      /*
       * wave670: keyword `null` only valid when function returns TYPE_PTR.
       * Bare INT 0 still widens to i64/u32/u64 below.
       */
      if (typeck_expr_is_null_keyword(arena, op_ref) != 0 && rk_ret != 9) {
        got = expr_type_ref(arena, op_ref);
        driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got);
        return -1;
      }
    }
    if (!ast.ref_is_null(op_ref) && !ast.ref_is_null(return_type_ref)) {
      op_kind = pipeline_expr_kind_ord_at(arena, op_ref);
      if (op_kind == ord_lit) {
        rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
        /* wave670: never widen keyword null via i64/unsigned lit path. */
        if (typeck_expr_is_null_keyword(arena, op_ref) == 0) {
          if (rt_kind == ord_i64) {
            pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref);
          } else {
            int_val = pipeline_expr_int_val_at(arena, op_ref);
            if (int_val == 0 && rt_kind == ord_ptr) {
              pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref);
            } else if (int_val >= 0) {
              if (rt_kind == ord_usize || rt_kind == ord_u32 || rt_kind == ord_u64) {
                pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref);
              }
            }
          }
        } else if (rt_kind == ord_ptr) {
          pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref);
        }
      }
    }
    if (!ast.ref_is_null(op_ref) && !ast.ref_is_null(return_type_ref)) {
      /*
       * wave333 Cap residual pure: return ARRAY_LIT → TYPE_SLICE / TYPE_ARRAY / VECTOR.
       * Prior: only TYPE_ARRAY + hand-written VECTOR lanes; `return [1,2,3]: i32[]`
       * found ?. G.7: reuse typeck_coerce_init_array_vector_lit_to_decl (let wave328 /
       * assign wave331). PLATFORM: SHARED — seed typeck_gen + glue return_c twin.
       */
      let crc_arr: i32 = 0;
      op_kind = pipeline_expr_kind_ord_at(arena, op_ref);
      rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
      crc_arr = typeck_coerce_init_array_vector_lit_to_decl(module, arena, op_ref, return_type_ref, rt_kind,
      op_kind);
      if (crc_arr < 0) {
        return - 1;
      }
    }
    if (!ast.ref_is_null(op_ref) && !ast.ref_is_null(return_type_ref)) {
      op_kind = pipeline_expr_kind_ord_at(arena, op_ref);
      if (op_kind == ord_as) {
        as_tgt = pipeline_expr_as_target_type_ref_at(arena, op_ref);
        if (!ast.ref_is_null(as_tgt) && type_refs_equal(arena, as_tgt, return_type_ref)) {
          pipeline_expr_set_resolved_type_ref(arena, op_ref, as_tgt);
        }
      }
    }
    if (!ast.ref_is_null(return_type_ref) && !ast.ref_is_null(op_ref)) {
      let expect_kind: i32 = 0;
      let got_kind: i32 = 0;
      /* wave236–237 pure leave: scope borrow + allocator region before slice gates. */
      if (typeck_check_scope_borrow_return(module, arena, expr_ref, op_ref, return_type_ref, ctx) != 0) {
        return - 1;
      }
      if (typeck_check_allocator_region_return(arena, expr_ref, return_type_ref) != 0) {
        return - 1;
      }
      /* See implementation. */
      if (pipeline_typeck_check_return_slice_region_in_scope_c(arena, expr_ref, return_type_ref, ctx) != 0) {
        return - 1;
      }
      typeck_ret_coerce_integral_to_expect_i32(arena, op_ref, return_type_ref);
      typeck_ret_coerce_integral_widen(arena, op_ref, return_type_ref);
      got = expr_type_ref(arena, op_ref);
      if (!typeck_return_operand_matches(module, arena, op_ref, return_type_ref)) {
        /* See implementation. */
        if (!ast.ref_is_null(got) && got > 0 && !ast.ref_is_null(return_type_ref)) {
          expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
          got_kind = pipeline_type_kind_ord_at(arena, got);
          if (typeck_integer_widen_ok_refs(arena, return_type_ref, got) ||
              typeck_float_widen_ok(expect_kind, got_kind)) {
            pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref);
            if (typeck_check_return_slice_region(arena, expr_ref, op_ref, return_type_ref) != 0) {
              return - 1;
            }
            return 0;
          }
        }
        eb = driver_typeck_diag_scratch_expect();
        gb = driver_typeck_diag_scratch_found();
        el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb);
        gl = typeck_diag_fmt_type_or_question(arena, got, gb);
        driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl);
        typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col);
        driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got);
        return - 1;
      }
      /* wave235 pure leave: return slice region authority in typeck.x. */
      if (typeck_check_return_slice_region(arena, expr_ref, op_ref, return_type_ref) != 0) {
        return - 1;
      }
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_panic(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let op_ref: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (!ast.ref_is_null(return_type_ref)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
    }
    return 0;
  }
}

/**
 * Type-check one match arm (enum variant index + optional guard + result).
 * Recursive over arm_i for cold/seed paths; product match uses iterative
 * typeck_check_expr_match (wave231) to set subject BSS and avoid deep X stack.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_MATCH
 * @param return_type_ref i32 — ambient return / result type for arm bodies
 * @param ctx *PipelineDepCtx
 * @param arm_i i32 — current arm index
 * @param num_arms i32 — arm count
 * @param line i32 — match expr line (diagnostics)
 * @param col i32 — match expr col
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED
 */
export function typeck_check_expr_match_arm(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, arm_i: i32, num_arms: i32, line: i32, col: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let is_enum: i32 = 0;
    let var_ix: i32 = 0;
    let arm_res: i32 = 0;
    let guard_ref: i32 = 0;
    let bool_ty: i32 = 0;
    if (arm_i >= num_arms) {
      return 0;
    }
    is_enum = pipeline_expr_match_arm_is_enum_variant(arena, expr_ref, arm_i);
    if (is_enum != 0) {
      var_ix = pipeline_expr_match_arm_variant_index(arena, expr_ref, arm_i);
      if (var_ix < 0) {
        driver_diagnostic_typeck_enum_no_variant(line, col);
        return - 1;
      }
    }
    /* wave700: typecheck optional guard as bool ambient. */
    guard_ref = pipeline_expr_match_arm_guard_ref(arena, expr_ref, arm_i);
    if (!ast.ref_is_null(guard_ref) && guard_ref > 0) {
      bool_ty = ensure_bool_type_ref(arena);
      if (check_expr(module, arena, guard_ref, bool_ty, ctx) != 0) {
        return - 1;
      }
    }
    arm_res = pipeline_expr_match_arm_result_ref(arena, expr_ref, arm_i);
    if (check_expr(module, arena, arm_res, return_type_ref, ctx) != 0) {
      return - 1;
    }
    return typeck_check_expr_match_arm(module, arena, expr_ref, return_type_ref, ctx, arm_i + 1,
    num_arms, line, col);
  }
}

/**
 * Type-check EXPR_MATCH: matched expr, then each arm under subject field-bind
 * context (wave703). Product authority (wave231 pure leave) — residual
 * pipeline_typeck_check_expr_match_c is a thin face.
 *
 * Nested match: save/restore subject ty+mod so outer arm field binds stay
 * valid after inner match returns. Iterative arm loop avoids X recursion SEGV.
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_MATCH
 * @param return_type_ref i32 — ambient type for arm results / match result stamp
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck
 */
export function typeck_check_expr_match(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let matched_ref: i32 = 0;
    let num_arms: i32 = 0;
    let arm_i: i32 = 0;
    let is_enum: i32 = 0;
    let var_ix: i32 = 0;
    let arm_res: i32 = 0;
    let guard_ref: i32 = 0;
    let bool_ty: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let matched_ty: i32 = 0;
    let saved_subj_ty: i32 = 0;
    let saved_subj_mod: *Module = 0 as *Module;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    matched_ref = pipeline_expr_match_matched_ref_at(arena, expr_ref);
    num_arms = pipeline_expr_match_num_arms_at(arena, expr_ref);
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    if (check_expr(module, arena, matched_ref, return_type_ref, ctx) != 0) {
      return -1;
    }
    matched_ty = pipeline_expr_resolved_type_ref(arena, matched_ref);
    /* Nested match: save outer subject, install this match's subject for VAR hop. */
    saved_subj_ty = pipeline_typeck_match_subject_ty_get_c();
    saved_subj_mod = pipeline_typeck_match_subject_mod_get_c();
    pipeline_typeck_match_set_subject_c(module, matched_ty);
    arm_i = 0;
    while (arm_i < num_arms) {
      is_enum = pipeline_expr_match_arm_is_enum_variant(arena, expr_ref, arm_i);
      if (is_enum != 0) {
        var_ix = pipeline_expr_match_arm_variant_index(arena, expr_ref, arm_i);
        if (var_ix < 0) {
          pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty);
          driver_diagnostic_typeck_enum_no_variant(line, col);
          return -1;
        }
      }
      /* wave700: optional guard under subject field binds. */
      guard_ref = pipeline_expr_match_arm_guard_ref(arena, expr_ref, arm_i);
      if (!ast.ref_is_null(guard_ref) && guard_ref > 0) {
        bool_ty = ensure_bool_type_ref(arena);
        if (check_expr(module, arena, guard_ref, bool_ty, ctx) != 0) {
          pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty);
          return -1;
        }
      }
      arm_res = pipeline_expr_match_arm_result_ref(arena, expr_ref, arm_i);
      if (check_expr(module, arena, arm_res, return_type_ref, ctx) != 0) {
        pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty);
        return -1;
      }
      arm_i = arm_i + 1;
    }
    pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty);
    if (!ast.ref_is_null(return_type_ref)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
    }
    return 0;
  }
}

/**
 * ERR-01: Result `?` propagation — operand must be Result_* NAMED type;
 * enclosing function return type must match; expression type is Ok payload
 * (Result_i32→i32, Result_u8→u8). wave231 pure leave: live authority in
 * typeck.x; residual pipeline_typeck_check_expr_try_propagate_c is thin.
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_TRY_PROPAGATE
 * @param return_type_ref i32 — ambient return (overridden by current_func)
 * @param ctx *PipelineDepCtx — current_func_index for enclosing return type
 * @return i32 — 0 ok (expr stamped to payload), -1 fail
 * PLATFORM: SHARED freestanding typeck
 */
export function typeck_check_expr_try_propagate(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let op_ref: i32 = 0;
    let op_ty: i32 = 0;
    let enclosing_return_type_ref: i32 = 0;
    let func_ix: i32 = 0;
    let func_ret: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let payload_ty: i32 = 0;
    let rname: u8[128] = [];
    let rlen: i32 = 0;
    let si: i32 = 0;
    /* TypeKind: TYPE_I32=0, TYPE_U8=2, TYPE_NAMED=8 (ast.x enum order). */
    let ord_named: i32 = 8;
    let ord_i32: i32 = 0;
    let ord_u8: i32 = 2;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
      return -1;
    }
    /* wave314 G.7: use typeck.x authority names (not C seed typeck_ mangle). */
    op_ty = expr_type_ref(arena, op_ref);
    enclosing_return_type_ref = return_type_ref;
    func_ret = 0;
    func_ix = -1;
    if (ctx != 0 as *PipelineDepCtx) {
      func_ix = pipeline_dep_ctx_current_func_index(ctx);
    }
    if (module != 0 as *Module && ctx != 0 as *PipelineDepCtx && func_ix >= 0 &&
    func_ix < pipeline_module_num_funcs(module)) {
      func_ret = pipeline_module_func_return_type_at(module, func_ix);
      if (!ast.ref_is_null(func_ret)) {
        enclosing_return_type_ref = func_ret;
      }
    }
    if (ast.ref_is_null(op_ty) || pipeline_type_kind_ord_at(arena, op_ty) != ord_named) {
      driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col);
      return -1;
    }
    rlen = pipeline_type_named_name_into(arena, op_ty, &rname[0]);
    /* Require prefix "Result_" (7 bytes). */
    if (rlen < 7 || rname[0] != 82 || rname[1] != 101 || rname[2] != 115 || rname[3] != 117 ||
    rname[4] != 108 || rname[5] != 116 || rname[6] != 95) {
      driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col);
      return -1;
    }
    /* wave314: type_refs_equal is the live authority (bool); not typeck_type_refs_equal. */
    if (ast.ref_is_null(enclosing_return_type_ref) ||
    type_refs_equal(arena, enclosing_return_type_ref, op_ty) == false) {
      driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col);
      return -1;
    }
    payload_ty = 0;
    /* Result_i32 / Result_u8 exact suffixes; also scan suffix for embedded i32/u8. */
    if (rlen == 10 && rname[7] == 105 && rname[8] == 51 && rname[9] == 50) {
      payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32);
    } else if (rlen == 9 && rname[7] == 117 && rname[8] == 56) {
      payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_u8);
    } else {
      si = 7;
      while (si + 1 < rlen && si + 1 < 64) {
        if (rname[si] == 105 && rname[si + 1] == 51 && si + 2 < rlen && rname[si + 2] == 50) {
          payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32);
          break;
        }
        if (rname[si] == 117 && rname[si + 1] == 56) {
          payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_u8);
          break;
        }
        si = si + 1;
      }
    }
    if (payload_ty != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, payload_ty);
    } else if (!ast.ref_is_null(op_ty)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, op_ty);
    }
    return 0;
  }
}

/**
* See implementation.
*/
export function typeck_check_expr_call_arg(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, arg_i: i32, num_args: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let arg_ref: i32 = 0;
    if (arg_i >= num_args) {
      return 0;
    }
    arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, arg_i);
    if (check_expr(module, arena, arg_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    return typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, arg_i + 1,
    num_args);
  }
}

/**
* See implementation.
*/
export function typeck_check_expr_call_resolve(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_addr_of: i32 = 51;
    /* EXPR_DEREF — Cap-fn-ptr (*f)() peels to VAR f (*u8); ≡ f() for Cap. */
    let ord_deref: i32 = 52;
    let ord_var: i32 = 3;
    /* EXPR_INDEX / EXPR_FIELD — Cap/TYPE_FN surface callees (10.3.1 slice14). */
    let ord_index: i32 = 47;
    let ord_field: i32 = 44;
    /* EXPR_CALL / EXPR_METHOD_CALL — TYPE_FN CALL-of-CALL `getf()()`. */
    let ord_call: i32 = 48;
    let ord_method: i32 = 49;
    /* See implementation. */
    let minus_one: i32 = -1;
    let callee_ref: i32 = 0;
    let callee_eff: i32 = 0;
    let inner_c: i32 = 0;
    let ret_ty: i32 = 0;
    let cnml: i32 = 0;
    let cnm: u8[128] = [];
    let peel_ko: i32 = 0;
    callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    if (ast.ref_is_null(callee_ref)) {
      return 0;
    }
    callee_eff = callee_ref;
    /*
     * Peel ADDR_OF / DEREF once so Cap *u8 VAR is visible.
     * (*f)() → DEREF(VAR); Cap treats as call-through (no u8 load).
     * PLATFORM: SHARED — pairs with asm Cap peel (10.3.2 slice3).
     */
    peel_ko = pipeline_expr_kind_ord_at(arena, callee_eff);
    if (peel_ko == ord_addr_of || peel_ko == ord_deref) {
      inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff);
      if (!ast.ref_is_null(inner_c)) {
        callee_eff = inner_c;
      }
    }
    /* See implementation. */
    cnml = 0;
    if (pipeline_expr_kind_ord_at(arena, callee_eff) == ord_var) {
      cnml = pipeline_expr_var_name_len(arena, callee_eff);
      if (cnml > 0) {
        pipeline_expr_var_name_into(arena, callee_eff, &cnm[0]);
      }
    }
    ret_ty = resolve_call_callee_return_type(module, arena, callee_eff, expr_ref, ctx);
    if (ret_ty == 0 && cnml > 0) {
      typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0);
      ret_ty = find_func_return_type_in_module_by_name(module, arena, &cnm[0], cnml, minus_one, ctx,
      typeck_call_resolve_func_idx_slot());
      if (ret_ty != 0) {
        ast.ast_expr_apply_call_resolve(arena, expr_ref, minus_one, typeck_call_resolve_func_idx_peek());
      }
    }
    /* See implementation. */
    if (cnml > 0 && pipeline_typeck_is_read_ptr_slice_callee_c(&cnm[0], cnml) != 0) {
      ret_ty = pipeline_typeck_read_ptr_slice_return_ref_c(arena);
    }
    /*
     * Stage12 @shuffle/@select: parser lowers to bare CALL simd_shuffle /
     * simd_select (codegen inlines pshufd / blend). No module fi — stamp ret
     * from vector operand (arg0 shuffle, arg1 select) after args typecked.
     * G.7: pipeline_typeck_is_simd_comptime_callee_c authority.
     * PLATFORM: SHARED.
     */
    if (ret_ty == 0 && cnml > 0 && pipeline_typeck_is_simd_comptime_callee_c(&cnm[0], cnml) != 0) {
      let arg_i: i32 = 0;
      let arg_ref: i32 = 0;
      if (cnml == 11) {
        /* simd_select(mask, a, b) → type of a */
        arg_i = 1;
      }
      if (pipeline_expr_call_num_args_at(arena, expr_ref) > arg_i) {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, arg_i);
        if (!ast.ref_is_null(arg_ref)) {
          ret_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
        }
      }
    }
    /*
     * Cap-fn-ptr (10.3.2 slice1) / TYPE_FN (10.3.1): call through *u8 or TYPE_FN.
     * Type the callee; Cap *u8 stamps ret from expected or i32; TYPE_FN
     * stamps ret from elem (return type).
     * 10.3.1 slice14: also INDEX (`fs[0](x)`) and FIELD Cap surfaces —
     * prior VAR-only left CALL ret `?` (return mismatch).
     * CALL-of-CALL `getf()()`: callee is EXPR_CALL whose resolved type is
     * TYPE_FN — same stamp; prior VAR/INDEX/FIELD-only left outer ret `?`.
     * METHOD_CALL callee (`P.getf()()`) is the same surface.
     * Asm Cap emit already loads any Cap-typed expr then blr.
     * PLATFORM: SHARED.
     */
    if (ret_ty == 0) {
      let ckind: i32 = pipeline_expr_kind_ord_at(arena, callee_eff);
      if (ckind == ord_var || ckind == ord_index || ckind == ord_field
          || ckind == ord_call || ckind == ord_method) {
      if (check_expr(module, arena, callee_eff, 0, ctx) == 0) {
        let ctr: i32 = pipeline_expr_resolved_type_ref(arena, callee_eff);
        let cko: i32 = 0;
        let eer: i32 = 0;
        let eko: i32 = 0;
        let expect: i32 = 0;
        if (ctr > 0) {
          cko = pipeline_type_kind_ord_at(arena, ctr);
          if (cko == TypeKind.TYPE_FN as i32) {
            eer = pipeline_type_elem_ref_at(arena, ctr);
            if (eer > 0) {
              ret_ty = eer;
            } else {
              expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot());
              if (expect > 0) {
                ret_ty = expect;
              } else {
                ret_ty = ensure_i32_type_ref(arena);
              }
            }
          } else if (cko == 9) {
            eer = pipeline_type_elem_ref_at(arena, ctr);
            if (eer > 0) {
              eko = pipeline_type_kind_ord_at(arena, eer);
              if (eko == 2) {
                expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot());
                if (expect > 0) {
                  ret_ty = expect;
                } else {
                  ret_ty = ensure_i32_type_ref(arena);
                }
              }
            }
          }
        }
      }
      }
    }
    if (ret_ty != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty);
    }
    return 0;
  }
}

/**
 * Cap 10.7.1 slice8: call-site arity vs named formals.
 * Exact match, or variadic with num_args >= named param count (C `...`).
 * Too few args always fails (even on variadic).
 * @param module *Module — func owner (local or dep)
 * @param fi i32 — function index
 * @param num_args i32 — call-site argument count
 * @return i32 — 1 compatible, 0 not
 * PLATFORM: SHARED — G.7 single predicate for arity gate + overload pick.
 */
export function typeck_call_arity_compatible(module: *Module, fi: i32, num_args: i32): i32 {
  // PLATFORM: SHARED — Cap variadic call arity.
  unsafe {
    let np: i32 = 0;
    if (module == 0 as *Module || fi < 0) {
      return 0;
    }
    np = pipeline_module_func_num_params_at(module, fi);
    if (np == num_args) {
      return 1;
    }
    if (pipeline_module_func_is_variadic_at(module, fi) != 0 && num_args >= np) {
      return 1;
    }
    return 0;
  }
}

/**
 * Hard-fail free-function CALL when argument count ≠ resolved (or name-matched) arity,
 * or when a bare VAR callee name resolves to no function at all.
 * wave660 Cap residual: overload pick used to bind first same-name func ignoring arity
 * → typeck OK then host-cc BLD001. Also covers pure miss after first_idx gate.
 * wave675 Cap residual: unresolved bare VAR callee (name_hits==0) was soft-skipped →
 * host BLD001 undeclared function (typos, silent parse-drop of bad formals + call).
 * Cap 10.7.1 slice8: variadic callees accept num_args >= named arity.
 * Soft-skip: non-VAR callee (fn ptr / method path), special read_ptr_slice intrinsics.
 * @param module *Module — entry / local module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_CALL
 * @param ctx *PipelineDepCtx — for dep module when resolved_dep_index ≥ 0
 * @return i32 — 0 ok, -1 arity mismatch or unresolved (diagnostic emitted)
 * PLATFORM: SHARED — G.7 single gate; product path also invoked from
 * pipeline_typeck_check_expr_call_c after resolve (seed typeck_check_expr_call delegates).
 */
export function typeck_check_call_arity(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_args: i32 = 0;
    let fi: i32 = 0;
    let dep: i32 = 0;
    let mod: *Module = 0 as *Module;
    let dm: *Module = 0 as *Module;
    let line_a: i32 = 0;
    let col_a: i32 = 0;
    let callee_ref: i32 = 0;
    let callee_eff: i32 = 0;
    let ord_addr_of: i32 = 51;
    let ord_deref: i32 = 52;
    let ord_var: i32 = 3;
    let inner_c: i32 = 0;
    let peel_ko: i32 = 0;
    let cnml: i32 = 0;
    let cnm: u8[128] = [];
    let j: i32 = 0;
    let name_hits: i32 = 0;
    let arity_hits: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    num_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
    if (fi >= 0) {
      mod = module;
      if (dep >= 0 && ctx != 0 as *PipelineDepCtx) {
        dm = pipeline_dep_ctx_module_at(ctx, dep);
        if (dm != 0 as *Module) {
          mod = dm;
        }
      }
      /* Cap 10.7.1 slice8: exact or variadic (num_args >= named). */
      if (typeck_call_arity_compatible(mod, fi, num_args) == 0) {
        line_a = pipeline_expr_line_at(arena, expr_ref);
        col_a = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a);
        return -1;
      }
      return 0;
    }
    /*
     * Unresolved CALL (fi < 0 after resolve):
     * - name exists locally but no nparams==num_args → arity T001 (wave660)
     * - bare VAR name has zero local hits → unresolved T001 (wave675)
     * Special read_ptr_slice callees stamp ret without fi → soft-skip.
     * Non-VAR callee (fn pointer / complex) → soft (not this hard leaf).
     * Dep-resolved calls set fi ≥ 0 above; import-only names without import stay red.
     */
    callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    if (ast.ref_is_null(callee_ref)) {
      return 0;
    }
    callee_eff = callee_ref;
    /* Cap (*f)(): peel DEREF/ADDR_OF to VAR before Cap *u8 soft-skip. */
    peel_ko = pipeline_expr_kind_ord_at(arena, callee_eff);
    if (peel_ko == ord_addr_of || peel_ko == ord_deref) {
      inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff);
      if (!ast.ref_is_null(inner_c)) {
        callee_eff = inner_c;
      }
    }
    /*
     * Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): callee VAR typed *u8 or TYPE_FN
     * is an opaque function pointer. Soft-skip name lookup — no module fi.
     * 10.3.1 slice14: INDEX/FIELD Cap surfaces also soft (no local name).
     * PLATFORM: SHARED — pairs with asm Cap-fnptr blr / call *reg.
     */
    {
      let ckind: i32 = pipeline_expr_kind_ord_at(arena, callee_eff);
      let ord_index: i32 = 47;
      let ord_field: i32 = 44;
      if (ckind == ord_index || ckind == ord_field) {
        if (check_expr(module, arena, callee_eff, 0, ctx) != 0) {
          return -1;
        }
        {
          let ctr: i32 = pipeline_expr_resolved_type_ref(arena, callee_eff);
          if (ctr > 0 && typeck_is_fnptr_surface(arena, ctr) != 0) {
            return 0;
          }
        }
        /* Non-Cap INDEX/FIELD callee: soft (not unresolved-name leaf). */
        return 0;
      }
    }
    if (pipeline_expr_kind_ord_at(arena, callee_eff) != ord_var) {
      return 0;
    }
    cnml = pipeline_expr_var_name_len(arena, callee_eff);
    if (cnml <= 0 || cnml > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, callee_eff, &cnm[0]);
    /* PLATFORM: SHARED — product intrinsics that type without module fi. */
    if (pipeline_typeck_is_read_ptr_slice_callee_c(&cnm[0], cnml) != 0) {
      return 0;
    }
    /* @shuffle/@select → simd_shuffle/simd_select (codegen-inline; no fi). */
    if (pipeline_typeck_is_simd_comptime_callee_c(&cnm[0], cnml) != 0) {
      return 0;
    }
    /*
     * Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): callee VAR typed *u8 or TYPE_FN
     * is an opaque function pointer. Soft-skip name lookup — no module fi.
     * PLATFORM: SHARED — pairs with asm Cap-fnptr blr / call *reg.
     */
    if (check_expr(module, arena, callee_eff, 0, ctx) != 0) {
      return -1;
    }
    {
      let ctr: i32 = pipeline_expr_resolved_type_ref(arena, callee_eff);
      if (ctr > 0 && typeck_is_fnptr_surface(arena, ctr) != 0) {
        return 0;
      }
    }
    name_hits = 0;
    arity_hits = 0;
    j = 0;
    while (j < module.num_funcs) {
      if (pipeline_module_func_name_equal_at(module, j, &cnm[0], cnml) != 0) {
        name_hits = name_hits + 1;
        /* Cap 10.7.1 slice8: exact or variadic compatible. */
        if (typeck_call_arity_compatible(module, j, num_args) != 0) {
          arity_hits = arity_hits + 1;
        }
      }
      j = j + 1;
    }
    if (name_hits > 0 && arity_hits == 0) {
      line_a = pipeline_expr_line_at(arena, expr_ref);
      col_a = pipeline_expr_col_at(arena, expr_ref);
      driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a);
      return -1;
    }
    /* wave675: completely unknown bare name → hard-fail (was BLD001 undeclared). */
    if (name_hits == 0) {
      line_a = pipeline_expr_line_at(arena, expr_ref);
      col_a = pipeline_expr_col_at(arena, expr_ref);
      driver_diagnostic_typeck_call_unresolved(line_a, col_a);
      return -1;
    }
    return 0;
  }
}

/**
 * wave249 pure leave: TYPE_NAMED name is a module struct layout or type alias
 * (concrete type), as opposed to a free type-param. Cap residual mono/UFCS/
 * fixup authority face: pipeline_typeck_named_is_module_type_c.
 * G.7 有则补全 — sole name→concrete probe for free-param vs module type
 * (distinct from typeck_named_is_module_concrete which also walks enums/deps).
 * @param module *Module — layouts / type aliases owner (null → 0)
 * @param arena *ASTArena — unused (ABI parity with Cap residual; may be null)
 * @param name *u8 — TYPE_NAMED spelling
 * @param name_len i32 — byte count; <=0 → 0
 * @return i32 — 1 concrete module type, 0 free/unknown
 * PLATFORM: SHARED freestanding typeck mono foundation.
 */
export function typeck_named_is_module_type(module: *Module, arena: *ASTArena, name: *u8,
name_len: i32): i32 {
  // PLATFORM: SHARED — free-param vs module type probe (structs + aliases only).
  unsafe {
    let si: i32 = 0;
    let nsl: i32 = 0;
    let snlen: i32 = 0;
    let snm: u8[128] = [];
    let n_alias: i32 = 0;
    let ai: i32 = 0;
    let alen: i32 = 0;
    let bi: i32 = 0;
    let same: i32 = 0;
    if (module == 0 as *Module || name == 0 as *u8 || name_len <= 0) {
      return 0;
    }
    // arena unused: Cap residual (void)arena; name compare only.
    if (arena == 0 as *ASTArena) {
      // keep null-tolerant ABI; no load from arena.
    }
    nsl = pipeline_module_num_struct_layouts_at(module);
    si = 0;
    while (si < nsl) {
      snlen = pipeline_module_struct_layout_name_len(module, si);
      if (snlen == name_len && snlen > 0) {
        pipeline_module_struct_layout_name_into(module, si, &snm[0]);
        if (name_equal(&snm[0], snlen, name, name_len)) {
          return 1;
        }
      }
      si = si + 1;
    }
    n_alias = pipeline_module_num_type_aliases_at(module);
    ai = 0;
    while (ai < n_alias) {
      alen = pipeline_module_type_alias_name_len(module, ai);
      if (alen == name_len && alen > 0) {
        same = 1;
        bi = 0;
        while (bi < alen) {
          if (pipeline_module_type_alias_name_byte_at(module, ai, bi) != name[bi]) {
            same = 0;
            break;
          }
          bi = bi + 1;
        }
        if (same != 0) {
          return 1;
        }
      }
      ai = ai + 1;
    }
    return 0;
  }
}

/**
 * Return 1 when TYPE_NAMED ty is a free type-param (name is not a module
 * struct layout or type alias). wave249 G.7: inverted typeck_named_is_module_type
 * (no second name scan). Used by call arg gate so formals `x: T` on generics
 * accept concrete args.
 * NAMED SIMD spellings (i32x4 / f32x4 / …) are concrete — typeck_vector_lanes_of_type
 * > 0 — not free T. Else generic UFCS binds `[1,2,3].take0()` to take0(self: i32x4).
 * @param module *Module — callee module (layouts / aliases)
 * @param arena *ASTArena
 * @param ty_ref i32 — candidate formal type_ref
 * @return i32 — 1 free type-param, 0 concrete/unknown/non-named
 * PLATFORM: SHARED typeck helper.
 */
export function typeck_type_is_free_type_param(module: *Module, arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ty_ref <= 0) {
      return 0;
    }
    /*
     * Concrete SIMD (TYPE_VECTOR or NAMED i32x4 / f32x4 / …) is not free T.
     * PLATFORM: SHARED.
     */
    if (typeck_vector_lanes_of_type(arena, ty_ref) > 0) {
      return 0;
    }
    /* TYPE_NAMED ord == 8 */
    if (pipeline_type_kind_ord_at(arena, ty_ref) != 8) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, ty_ref, &nm[0]);
    if (nlen <= 0 || nlen > 127) {
      return 0;
    }
    // G.7: sole name→concrete probe is typeck_named_is_module_type.
    if (typeck_named_is_module_type(module, arena, &nm[0], nlen) != 0) {
      return 0;
    }
    return 1;
  }
}

/**
 * Return 1 when the type tree contains a free type-param (TYPE_NAMED not a
 * module struct/alias), walking PTR/SLICE/ARRAY/VECTOR elems and NAMED type-args.
 * Mirrors glue `glue_typeck_type_tree_has_free_param_c` for typeck.x pre-score.
 * @param module *Module
 * @param arena *ASTArena
 * @param ty_ref i32 — formal type tree root
 * @param depth i32 — recursion depth (cap 12)
 * @return i32 — 1 if free type-param found, else 0
 * PLATFORM: SHARED typeck helper (wave686).
 */
export function typeck_type_tree_has_free_type_param(module: *Module, arena: *ASTArena, ty_ref: i32,
depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let kind: i32 = 0;
    let elem: i32 = 0;
    let n_ta: i32 = 0;
    let i: i32 = 0;
    let ta: i32 = 0;
    let asz: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ty_ref <= 0 || depth > 12) {
      return 0;
    }
    if (typeck_type_is_free_type_param(module, arena, ty_ref) != 0) {
      return 1;
    }
    kind = pipeline_type_kind_ord_at(arena, ty_ref);
    /* TYPE_PTR=9, TYPE_ARRAY=10, TYPE_SLICE=11, TYPE_VECTOR=13 */
    if (kind == 9 || kind == 10 || kind == 11 || kind == 13) {
      elem = pipeline_type_elem_ref_at(arena, ty_ref);
      if (elem > 0) {
        return typeck_type_tree_has_free_type_param(module, arena, elem, depth + 1);
      }
      return 0;
    }
    /* TYPE_NAMED=8 module type — walk type-pos args if present. */
    if (kind == 8) {
      asz = pipeline_type_array_size_at(arena, ty_ref);
      if (asz > 0 && asz <= 8) {
        n_ta = asz;
      } else {
        n_ta = 0;
        i = 0;
        while (i < 8) {
          ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i);
          if (ta <= 0) {
            break;
          }
          n_ta = i + 1;
          i = i + 1;
        }
      }
      i = 0;
      while (i < n_ta) {
        ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i);
        if (ta <= 0 && i == 0) {
          ta = pipeline_type_elem_ref_at(arena, ty_ref);
        }
        if (ta > 0 && typeck_type_tree_has_free_type_param(module, arena, ta, depth + 1) != 0) {
          return 1;
        }
        i = i + 1;
      }
    }
    return 0;
  }
}

/**
 * wave686 Cap residual: structural match of a generic formal type against a
 * concrete arg type for call_arg pre-score accept.
 * Bare free type-param T matches any arg_ty. Compound formals *T / []T / T[N]
 * (and nested) match same-kind arg with recursive elem match; free leaf accepts
 * any concrete elem; ARRAY sizes must agree when both known.
 * Shape mirrors glue `glue_typeck_pattern_unify_bind_c` without building a map —
 * call_arg gate only needs accept/reject; mono bind stays in try_infer / fixup.
 * @param module *Module — callee module (free-param vs layout names)
 * @param arena *ASTArena — formal and arg types share caller arena for product calls
 * @param formal_ty i32 — formal type_ref (may contain free T)
 * @param arg_ty i32 — concrete arg resolved type_ref
 * @param depth i32 — recursion depth (cap 12)
 * @return i32 — 1 match, 0 no match
 * PLATFORM: SHARED typeck helper.
 */
export function typeck_generic_formal_matches_arg_type(module: *Module, arena: *ASTArena,
formal_ty: i32, arg_ty: i32, depth: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fk: i32 = 0;
    let ak: i32 = 0;
    let felem: i32 = 0;
    let aelem: i32 = 0;
    let fsz: i32 = 0;
    let asz: i32 = 0;
    let fnm: u8[128] = [];
    let anm: u8[128] = [];
    let fnlen: i32 = 0;
    let anlen: i32 = 0;
    let n_fta: i32 = 0;
    let n_ata: i32 = 0;
    let i: i32 = 0;
    let fta: i32 = 0;
    let ata: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || formal_ty <= 0 || arg_ty <= 0
    || depth > 12) {
      return 0;
    }
    /* Free type-param leaf: accepts any concrete arg type. */
    if (typeck_type_is_free_type_param(module, arena, formal_ty) != 0) {
      return 1;
    }
    if (pipeline_typeck_type_refs_equal_c(arena, formal_ty, arg_ty) != 0) {
      return 1;
    }
    fk = pipeline_type_kind_ord_at(arena, formal_ty);
    ak = pipeline_type_kind_ord_at(arena, arg_ty);
    if (fk < 0 || ak < 0) {
      return 0;
    }
    /* Module TYPE_NAMED: same name + pairwise type-args (Wrap<T> vs Wrap<i32>). */
    if (fk == 8) {
      if (ak != 8) {
        return 0;
      }
      fnlen = pipeline_type_named_name_into(arena, formal_ty, &fnm[0]);
      anlen = pipeline_type_named_name_into(arena, arg_ty, &anm[0]);
      if (fnlen <= 0 || anlen <= 0 || !name_equal(&fnm[0], fnlen, &anm[0], anlen)) {
        return 0;
      }
      asz = pipeline_type_array_size_at(arena, formal_ty);
      if (asz > 0 && asz <= 8) {
        n_fta = asz;
      } else {
        n_fta = 0;
        i = 0;
        while (i < 8) {
          if (pipeline_type_type_arg_ref_at(arena, formal_ty, i) <= 0) {
            break;
          }
          n_fta = i + 1;
          i = i + 1;
        }
      }
      if (n_fta <= 0) {
        return 1;
      }
      asz = pipeline_type_array_size_at(arena, arg_ty);
      if (asz > 0 && asz <= 8) {
        n_ata = asz;
      } else {
        n_ata = 0;
        i = 0;
        while (i < 8) {
          if (pipeline_type_type_arg_ref_at(arena, arg_ty, i) <= 0) {
            break;
          }
          n_ata = i + 1;
          i = i + 1;
        }
      }
      if (n_ata <= 0) {
        aelem = pipeline_type_elem_ref_at(arena, arg_ty);
        if (aelem > 0) {
          n_ata = 1;
        }
      }
      if (n_ata < n_fta) {
        return 0;
      }
      i = 0;
      while (i < n_fta) {
        fta = pipeline_type_type_arg_ref_at(arena, formal_ty, i);
        if (fta <= 0 && i == 0) {
          fta = pipeline_type_elem_ref_at(arena, formal_ty);
        }
        ata = pipeline_type_type_arg_ref_at(arena, arg_ty, i);
        if (ata <= 0 && i == 0) {
          ata = pipeline_type_elem_ref_at(arena, arg_ty);
        }
        if (fta <= 0 || ata <= 0) {
          return 0;
        }
        if (typeck_generic_formal_matches_arg_type(module, arena, fta, ata, depth + 1) == 0) {
          return 0;
        }
        i = i + 1;
      }
      return 1;
    }
    /* Compound: PTR / ARRAY / SLICE / VECTOR — same kind + elem recurse. */
    if (fk == 9 || fk == 10 || fk == 11 || fk == 13) {
      if (ak != fk) {
        return 0;
      }
      felem = pipeline_type_elem_ref_at(arena, formal_ty);
      aelem = pipeline_type_elem_ref_at(arena, arg_ty);
      if (felem <= 0 || aelem <= 0) {
        return 0;
      }
      if (fk == 10 || fk == 13) {
        fsz = pipeline_type_array_size_at(arena, formal_ty);
        asz = pipeline_type_array_size_at(arena, arg_ty);
        if (fsz > 0 && asz > 0 && fsz != asz) {
          return 0;
        }
      }
      return typeck_generic_formal_matches_arg_type(module, arena, felem, aelem, depth + 1);
    }
    /* Builtin formal without free tree: kinds must agree. */
    if (fk == ak) {
      return 1;
    }
    return 0;
  }
}

/**
 * Hard-fail free-function CALL when an arg does not match the formal param.
 * wave661 Cap residual: after resolve+arity, typeck never scored arg vs param → host-cc
 * BLD001 (*u8/struct→i32) or silent C conversion false-green (f32/bool→i32).
 * wave673 Cap residual: score&lt;0 with unknown arg_ty (arg_ty&lt;=0) was soft-skipped →
 * host BLD001 false-green (e.g. f(s.nope), f(g(1)) when g unresolved). Hard-fail any
 * score miss when the formal is known; soft-skip only untyped formals (param_raw&lt;=0).
 * wave685 Cap residual: free type-param formals (`x: T` on `id&lt;T&gt;`) score as
 * TYPE_NAMED vs scalar/lit → -1 false-red (`id(42)` / `id&lt;i32&gt;(42)` / `id(n:i32)`).
 * Same-kind NAMED already weak-scored 1 (struct→T greens). Accept free type-param
 * formals for any present arg; same-name unify stays in try_infer (same(1,true) red).
 * wave686 Cap residual: compound free formals `*T` / `[]T` / `T[N]` still score-reject
 * concrete `*i32` / `i32[]` / `i32[N]` (elem equal fails on free T). Pre-score accept via
 * `typeck_generic_formal_matches_arg_type` when formal tree has free type-param (G.7 twin
 * of glue pattern-unify shape; not a second score matcher).
 * Authority score: typeck_overload_arg_param_score (exact / int-lit / string-lit / widen /
 * null→*T); free-T is a pre-score accept, not a second matcher.
 * ARRAY_LIT → SIMD/VECTOR formals (i32x4 / f32x4 / Vec4f / …): args are check_expr'd
 * before resolve, so wave611 infers TYPE_ARRAY [N]T and score would T001. G.7: reuse
 * typeck_coerce_init_array_vector_lit_to_decl (let/assign/return/slice-region) BEFORE
 * score — same stamp as `let a: i32x4 = [1,2,3,4]`.
 * 4.2.10 already-typed [N]T (VAR/FIELD) → []T formal: score array→slice (ak=10,pk=11)
 * with equal elems. Do not stamp — emit_call_arg_slice_abi keys off TYPE_ARRAY.
 * METHOD_CALL=49 (import.binding extras): same accessors as score; formal[ai]
 * aligns with extra[ai] (param_base=0). UFCS self is not an extra — do not
 * call this on same-module UFCS (nparams==nargs+1).
 * @param module *Module — entry / local module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_CALL or EXPR_METHOD_CALL after apply_call_resolve
 * @param ctx *PipelineDepCtx — dep module when resolved_dep_index ≥ 0
 * @return i32 — 0 ok, -1 type mismatch (diagnostic emitted)
 * PLATFORM: SHARED — G.7 single gate; product path also from pipeline_typeck_check_expr_call_c.
 */

/**
 * True when a resolved 1-arg call is std.fmt / std.debug `print` / `println`.
 * Product contract (std.fmt README): composite args that miss scalar overloads are
 * accepted as compiler JSON "print any" specialization (not T001).
 * Detects by func name + dep import path (`std.fmt` / `std.debug`).
 * @param mod *Module — resolved callee module (often the dep module)
 * @param fi i32 — resolved function index in mod
 * @param dep i32 — resolved dep index (−1 = local; then not fmt/debug import)
 * @param ctx *PipelineDepCtx — dep import paths
 * @param num_args i32 — call arity (must be 1)
 * @return i32 — 1 when fmt/debug print/println 1-arg; else 0
 * PLATFORM: SHARED — G.7 single gate with asm glue_asm_prefix_is_fmt_or_debug.
 */
export function typeck_call_is_fmt_debug_print_any(mod: *Module, fi: i32, dep: i32,
ctx: *PipelineDepCtx, num_args: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let nlen: i32 = 0;
    let plen: i32 = 0;
    let print_nm: u8[8] = [];
    let println_nm: u8[8] = [];
    if (num_args != 1) {
      return 0;
    }
    if (mod == 0 as *Module || fi < 0) {
      return 0;
    }
    if (dep < 0 || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    nlen = pipeline_module_func_name_len_at(mod, fi);
    if (nlen != 5 && nlen != 7) {
      return 0;
    }
    /* Avoid copy64 into undersized locals — use name_equal (G.7 existing face). */
    print_nm[0] = 112; print_nm[1] = 114; print_nm[2] = 105; print_nm[3] = 110; print_nm[4] = 116;
    println_nm[0] = 112; println_nm[1] = 114; println_nm[2] = 105; println_nm[3] = 110;
    println_nm[4] = 116; println_nm[5] = 108; println_nm[6] = 110;
    if (nlen == 5) {
      if (pipeline_module_func_name_equal_at(mod, fi, &print_nm[0], 5) == 0) {
        return 0;
      }
    } else {
      if (pipeline_module_func_name_equal_at(mod, fi, &println_nm[0], 7) == 0) {
        return 0;
      }
    }
    plen = pipeline_dep_ctx_import_path_len(ctx, dep);
    if (plen != 7 && plen != 9) {
      return 0;
    }
    /*
     * copy64 APIs actually memset/write 128 bytes (wave577 AST name[128]).
     * Never use a smaller local — prior u8[64] → __stack_chk_fail.
     */
    {
      let pb: u8[128] = [];
      pipeline_dep_ctx_import_path_copy64(ctx, dep, &pb[0]);
      if (plen == 7) {
        if (pb[0] == 115 && pb[1] == 116 && pb[2] == 100 && pb[3] == 46
            && pb[4] == 102 && pb[5] == 109 && pb[6] == 116) {
          return 1;
        }
        return 0;
      }
      if (pb[0] == 115 && pb[1] == 116 && pb[2] == 100 && pb[3] == 46
          && pb[4] == 100 && pb[5] == 101 && pb[6] == 98 && pb[7] == 117
          && pb[8] == 103) {
        return 1;
      }
    }
    return 0;
  }
  return 0;
}

export function typeck_check_call_arg_types(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_args: i32 = 0;
    let fi: i32 = 0;
    let dep: i32 = 0;
    let mod: *Module = 0 as *Module;
    let dm: *Module = 0 as *Module;
    let ai: i32 = 0;
    let param_raw: i32 = 0;
    let sc: i32 = 0;
    let arg_ref: i32 = 0;
    let line_a: i32 = 0;
    let col_a: i32 = 0;
    let n_gp: i32 = 0;
    let arg_ty: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    if (fi < 0) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, expr_ref) == 49) {
      num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    } else {
      num_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    }
    dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
    mod = module;
    if (dep >= 0 && ctx != 0 as *PipelineDepCtx) {
      dm = pipeline_dep_ctx_module_at(ctx, dep);
      if (dm != 0 as *Module) {
        mod = dm;
      }
    }
    n_gp = pipeline_module_func_num_generic_params_at(mod, fi);
    ai = 0;
    while (ai < num_args) {
      param_raw = pipeline_module_func_param_type_ref_at(mod, fi, ai);
      /*
       * Soft-skip untyped / missing formal (param_raw<=0): score would return -1 and
       * false-red; leave soft residual (not this hard leaf).
       */
      if (param_raw > 0) {
        if (pipeline_expr_kind_ord_at(arena, expr_ref) == 49) {
          arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, ai);
        } else {
          arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, ai);
        }
        /*
         * wave670: hard-fail keyword `null`→non-ptr BEFORE score.
         * Root: ambient check_expr may stamp lit as i32; score then returns 1000
         * exact match and never hits the lit/is_null branch → call false green.
         * G.7: same gate as let/assign; only TYPE_PTR formals accept null.
         * Free type-param formals are not TYPE_PTR — null still hard-fails here
         * (mono may later bind T=*U only with a typed non-null arg).
         */
        if (arg_ref > 0 && typeck_expr_is_null_keyword(arena, arg_ref) != 0
        && pipeline_type_kind_ord_at(arena, param_raw) != 9) {
          line_a = pipeline_expr_line_at(arena, expr_ref);
          col_a = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a);
          return -1;
        }
        /*
         * wave685: free type-param formal on a generic callee (`x: T`) accepts any
         * present arg. Score treats T as TYPE_NAMED and rejects i32/bool/lit
         * (only same-kind NAMED weak-matches). Do not open a second score path —
         * pre-score accept only; concrete formals still use score below.
         * Requires n_gp>0 so a user type named like a param is not mis-accepted
         * on non-generic callees.
         */
        if (n_gp > 0 && typeck_type_is_free_type_param(mod, arena, param_raw) != 0) {
          if (arg_ref <= 0) {
            line_a = pipeline_expr_line_at(arena, expr_ref);
            col_a = pipeline_expr_col_at(arena, expr_ref);
            driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a);
            return -1;
          }
          ai = ai + 1;
          continue;
        }
        /*
         * wave686: compound free formals (*T / []T / T[N] / Wrap<T>) on generic
         * callees. Score requires elem type_refs_equal → free T vs i32 fails.
         * Pre-score structural match when formal tree has free type-param and arg
         * has a resolved type (lit alone cannot pin *T). Requires n_gp>0.
         */
        if (n_gp > 0 && arg_ref > 0) {
          arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
          if (arg_ty > 0
          && typeck_type_tree_has_free_type_param(mod, arena, param_raw, 0) != 0
          && typeck_generic_formal_matches_arg_type(mod, arena, param_raw, arg_ty, 0) != 0) {
            ai = ai + 1;
            continue;
          }
        }
        /*
         * ARRAY_LIT args were check_expr'd against the CALL ambient (not the
         * formal). Stamp SIMD/VECTOR / array / slice formals here so score
         * sees the same type as let-init. G.7: one coerce authority.
         * PLATFORM: SHARED.
         */
        if (arg_ref > 0) {
          let pty_c: i32 = param_raw;
          if (dep >= 0) {
            let mapped_c: i32 = get_dep_return_type_in_caller_arena(dep, param_raw, arena, ctx);
            if (mapped_c > 0) {
              pty_c = mapped_c;
            }
          }
          typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref, pty_c,
          pipeline_type_kind_ord_at(arena, pty_c),
          pipeline_expr_kind_ord_at(arena, arg_ref));
          /* Anonymous `{ fields }` call-arg: same dest backfill as let.
           * Named `Type { fields }` is also accepted (LANG-009); coerce is no-op
           * when already named. PLATFORM: SHARED — classify({ x: 0, y: 0 }). */
          typeck_coerce_init_struct_lit_to_decl(module, arena, arg_ref, pty_c);
          /*
           * ARRAY_LIT extras of NAMED elems (`[{a:2,b:3},{a:4,b:4}]` →
           * `[2]Pair` / `[]Pair`): array_vector stamps the outer ARRAY/
           * SLICE dest so host-C emits `struct Pair[]` / dest-SLICE wrap,
           * but STRUCT_LIT elems stay nameless → `(struct )` and asm
           * stores only the first field. G.7: same struct-elem dest as
           * typeck_coerce_init_expr_to_decl (let dest already green).
           * PLATFORM: SHARED extras dest-stamp.
           */
          typeck_coerce_array_lit_struct_elems_to_decl(module, arena, arg_ref, pty_c);
        }
        /*
         * Score covers known arg_ty + lit paths (int/string/null→*T) without requiring
         * a stamped type. wave673: any sc<0 is hard-fail when formal is known — do not
         * soft-skip unknown arg_ty (that left f(s.missing)/f(unresolved_call()) as BLD001).
         * Soft residual remains only param_raw<=0 (untyped formals) above.
         */
        sc = typeck_overload_arg_param_score(arena, expr_ref, ai, param_raw, dep, ctx);
        if (sc < 0) {
          /*
           * wave703 / wave234: #[repr(compatible)] *PairA → *PairB when same
           * field shape. Score treats distinct TYPE_NAMED pointees as mismatch.
           * G.7: typeck_call_arg_repr_compatible_ok (single layout gate).
           * PLATFORM: SHARED.
           */
          if (arg_ref > 0 && typeck_call_arg_repr_compatible_ok(mod, arena, param_raw, arg_ref) != 0) {
            ai = ai + 1;
            continue;
          }
          /*
           * std.fmt / std.debug print/println(composite): product JSON "print any".
           * first_idx may bind a scalar overload; score fails — do not T001.
           * Emit (asm try_emit_fmt_any / host-C) specializes; G.7 complete this gate.
           * PLATFORM: SHARED — closes print_any.x arg-type T001.
           */
          if (typeck_call_is_fmt_debug_print_any(mod, fi, dep, ctx, num_args) != 0) {
            ai = ai + 1;
            continue;
          }
          line_a = pipeline_expr_line_at(arena, expr_ref);
          col_a = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a);
          return -1;
        }
      }
      ai = ai + 1;
    }
    return 0;
  }
}

/**
 * Resolve unbound VAR as a field of the active match subject struct type.
 * wave234 G.7 pure leave: was Cap residual pipeline_typeck_match_subject_field_type_c.
 * Subject cells live in runtime_pipeline_abi pure BSS (set/get).
 * @param module *Module — current module (must equal subject module pointer)
 * @param arena *ASTArena — type pool for TYPE_NAMED name + field type_ref
 * @param name *u8 — VAR identifier bytes (not necessarily NUL-terminated)
 * @param name_len i32 — byte length; must be > 0
 * @return i32 — field type_ref (>0) on hit; 0 if no active subject or no field
 * PLATFORM: SHARED freestanding typeck — G.7 single subject-field authority.
 */
export function typeck_match_subject_field_type(module: *Module, arena: *ASTArena, name: *u8,
name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ty: i32 = 0;
    let subj_mod: *Module = 0 as *Module;
    let tnm: u8[128] = [];
    let tnl: i32 = 0;
    let nsl: i32 = 0;
    let k: i32 = 0;
    let fl: i32 = 0;
    let nf: i32 = 0;
    let fi: i32 = 0;
    let fnl: i32 = 0;
    let j: i32 = 0;
    let bi: i32 = 0;
    /* name_eq: not `match` — `match` is a reserved keyword (match expr). */
    let name_eq: i32 = 0;
    let fnm: u8[128] = [];
    if (module == 0 as *Module || arena == 0 as *ASTArena || name == 0 as *u8 || name_len <= 0) {
      return 0;
    }
    ty = pipeline_typeck_match_subject_ty_get_c();
    subj_mod = pipeline_typeck_match_subject_mod_get_c();
    if (ty <= 0 || subj_mod != module) {
      return 0;
    }
    /* TYPE_NAMED ord == 8 */
    if (pipeline_type_kind_ord_at(arena, ty) != 8) {
      return 0;
    }
    tnl = pipeline_type_named_name_into(arena, ty, &tnm[0]);
    if (tnl <= 0) {
      return 0;
    }
    nsl = pipeline_module_num_struct_layouts_at(module);
    k = 0;
    while (k < nsl) {
      fl = pipeline_module_struct_layout_name_len(module, k);
      if (fl == tnl) {
        name_eq = 1;
        bi = 0;
        while (bi < fl && name_eq != 0) {
          if (pipeline_module_struct_layout_name_byte_at(module, k, bi) != tnm[bi]) {
            name_eq = 0;
          }
          bi = bi + 1;
        }
        if (name_eq != 0) {
          nf = pipeline_module_struct_layout_num_fields(module, k);
          fi = 0;
          while (fi < nf) {
            fnl = pipeline_module_struct_layout_field_name_len(module, k, fi);
            if (fnl == name_len) {
              j = 0;
              while (j < 128) {
                fnm[j] = 0;
                j = j + 1;
              }
              pipeline_module_struct_layout_field_name_into(module, k, fi, &fnm[0]);
              name_eq = 1;
              j = 0;
              while (j < fnl && name_eq != 0) {
                if (fnm[j] != name[j]) {
                  name_eq = 0;
                }
                j = j + 1;
              }
              if (name_eq != 0) {
                return pipeline_module_struct_layout_field_type_ref(module, k, fi);
              }
            }
            fi = fi + 1;
          }
        }
      }
      k = k + 1;
    }
    return 0;
  }
}

/**
 * MOD-02: 1 if *StructA vs *StructB (or &StructB) may coerce under
 * #[repr(compatible)] + same field shape. 0 if not applicable or not ok.
 * wave234 G.7 pure leave: was Cap residual pipeline_typeck_call_arg_repr_compatible_ok_c.
 * @param module *Module — layout table owner
 * @param arena *ASTArena — type + expr arena
 * @param param_ref i32 — formal type_ref (must be TYPE_PTR to named struct)
 * @param arg_ref i32 — call argument expr_ref
 * @return i32 — 1 ok coerce, 0 not applicable / reject
 * PLATFORM: SHARED freestanding typeck — G.7 single layout gate.
 */
export function typeck_call_arg_repr_compatible_ok(module: *Module, arena: *ASTArena, param_ref: i32,
arg_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let param_elem: i32 = 0;
    let arg_elem: i32 = 0;
    let arg_ty: i32 = 0;
    let arg_kind: i32 = 0;
    let op: i32 = 0;
    let la: i32 = 0;
    let lb: i32 = 0;
    let m_u8: *u8 = 0 as *u8;
    let a_u8: *u8 = 0 as *u8;
    if (module == 0 as *Module || arena == 0 as *ASTArena || param_ref <= 0 || arg_ref <= 0) {
      return 0;
    }
    /* TYPE_PTR ord == 9 */
    if (pipeline_type_kind_ord_at(arena, param_ref) != 9) {
      return 0;
    }
    param_elem = pipeline_type_elem_ref_at(arena, param_ref);
    m_u8 = module as *u8;
    a_u8 = arena as *u8;
    if (param_elem <= 0 || typeck_type_is_named_struct_c(m_u8, a_u8, param_elem) == 0) {
      return 0;
    }
    arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
    arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref);
    /* EXPR_ADDR_OF ord == 51 — peel unary operand when arg still untyped */
    if (arg_ty <= 0 && arg_kind == 51) {
      op = pipeline_expr_unary_operand_ref_at(arena, arg_ref);
      if (op > 0) {
        arg_ty = pipeline_expr_resolved_type_ref(arena, op);
      }
    }
    if (arg_ty <= 0) {
      return 0;
    }
    /* TYPE_NAMED=8, TYPE_PTR=9 */
    if (pipeline_type_kind_ord_at(arena, arg_ty) == 8) {
      arg_elem = arg_ty;
    } else if (pipeline_type_kind_ord_at(arena, arg_ty) == 9) {
      arg_elem = pipeline_type_elem_ref_at(arena, arg_ty);
    } else {
      return 0;
    }
    if (arg_elem <= 0 || typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) == 0) {
      return 0;
    }
    param_elem = typeck_resolve_type_alias_ref(arena, param_elem);
    arg_elem = typeck_resolve_type_alias_ref(arena, arg_elem);
    if (param_elem == arg_elem) {
      return 1;
    }
    la = typeck_layout_index_for_named_type_c(m_u8, a_u8, param_elem);
    lb = typeck_layout_index_for_named_type_c(m_u8, a_u8, arg_elem);
    if (la < 0 || lb < 0) {
      return 0;
    }
    if (la == lb) {
      return 1;
    }
    if (typeck_struct_layouts_same_shape_c(m_u8, a_u8, la, lb) != 0
    && pipeline_module_struct_layout_repr_compatible_at(module, la) != 0
    && pipeline_module_struct_layout_repr_compatible_at(module, lb) != 0) {
      return 1;
    }
    return 0;
  }
}

/**
 * Cap 10.7.1 slice10+14: language Cap va_* faces (codegen → xlang_va_* macros).
 * Not libc FFI — export-extern is only a typeck shape; calls need no unsafe.
 * slice14: also `va_arg` (typed turbofish va_arg<T>(ap)).
 * @param name *u8 — bare callee spelling
 * @param name_len i32 — byte length
 * @return i32 — 1 Cap va builtin, 0 otherwise
 * PLATFORM: SHARED — pairs with codegen_try_emit_va_cap_call.
 */
export function typeck_is_cap_va_builtin_name(name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — Cap va language builtin name table.
  if (name == 0 as *u8 || name_len <= 0) {
    return 0;
  }
  if (name_len == 8 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 115 && name[4] == 116 && name[5] == 97
      && name[6] == 114 && name[7] == 116) {
    return 1;
  }
  if (name_len == 6 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 101 && name[4] == 110 && name[5] == 100) {
    return 1;
  }
  /* Cap 10.7.1 slice14: typed va_arg<T>(ap) — turbofish, not libc FFI. */
  if (name_len == 6 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 97 && name[4] == 114 && name[5] == 103) {
    return 1;
  }
  if (name_len == 7 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 99 && name[4] == 111 && name[5] == 112
      && name[6] == 121) {
    return 1;
  }
  if (name_len == 10 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 97 && name[4] == 114 && name[5] == 103
      && name[6] == 95 && name[7] == 105 && name[8] == 51
      && name[9] == 50) {
    return 1;
  }
  if (name_len == 10 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 97 && name[4] == 114 && name[5] == 103
      && name[6] == 95 && name[7] == 105 && name[8] == 54
      && name[9] == 52) {
    return 1;
  }
  if (name_len == 10 && name[0] == 118 && name[1] == 97 && name[2] == 95
      && name[3] == 97 && name[4] == 114 && name[5] == 103
      && name[6] == 95 && name[7] == 112 && name[8] == 116
      && name[9] == 114) {
    return 1;
  }
  return 0;
}

/**
 * LANG-007 v2 S0: extern calls must be inside unsafe { }.
 * wave234 G.7 pure leave: was Cap residual pipeline_typeck_check_extern_call_unsafe_boundary_c.
 * Cap 10.7.1 slice10: Cap va_* language builtins exempt (macro rewrite, not FFI).
 * @param module *Module — function table for is_extern
 * @param arena *ASTArena — call expr arena
 * @param expr_ref i32 — EXPR_CALL site
 * @param ctx *PipelineDepCtx — unsafe depth cell
 * @return i32 — 0 ok / skipped; -1 diagnostic emitted (outside unsafe)
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_check_extern_call_unsafe_boundary(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let callee_ref: i32 = 0;
    let callee_kind: i32 = 0;
    let name_len: i32 = 0;
    let name: u8[128] = [];
    let fi: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let m_u8: *u8 = 0 as *u8;
    /* -E seed regen / allow_legacy: typeck_gen preamble getter; default 0 keeps S0. */
    if (typeck_get_allow_legacy_extern_calls() != 0) {
      return 0;
    }
    if (pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) > 0) {
      return 0;
    }
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
    if (callee_ref <= 0) {
      return 0;
    }
    callee_kind = pipeline_expr_kind_ord_at(arena, callee_ref);
    /* EXPR_VAR ord == 3 */
    if (callee_kind != 3) {
      return 0;
    }
    name_len = pipeline_expr_var_name_len(arena, callee_ref);
    if (name_len <= 0 || name_len > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, callee_ref, &name[0]);
    /* Cap 10.7.1 slice10: va_* Cap faces → xlang_va_* (not libc FFI). */
    if (typeck_is_cap_va_builtin_name(&name[0], name_len) != 0) {
      return 0;
    }
    m_u8 = module as *u8;
    fi = glue_module_func_index_by_name_c(m_u8, &name[0], name_len);
    if (fi < 0 || pipeline_module_func_is_extern_at(module, fi) == 0) {
      return 0;
    }
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    driver_diagnostic_typeck_extern_call_outside_unsafe(line, col);
    return 0 - 1;
  }
}

/**
 * Resolve line/col for typeck diagnostics when site expr line is 0.
 * Assign-like: walk left then right. Unary (ADDR_OF/RETURN/NEG/LOGNOT):
 * walk operand. Mirrors Cap residual pipeline_typeck_expr_diag_line_col_c.
 * @param arena *ASTArena — expression arena
 * @param expr_ref i32 — site expression
 * @param line_out *i32 — written line (0 if unresolved)
 * @param col_out *i32 — written column
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_expr_diag_line_col(arena: *ASTArena, expr_ref: i32, line_out: *i32, col_out: *i32): void {
  // PLATFORM: SHARED — recursive line/col walk for region diags.
  unsafe {
    let k: i32 = 0;
    let l: i32 = 0;
    let c: i32 = 0;
    let child: i32 = 0;
    if (line_out == 0 as *i32 || col_out == 0 as *i32) {
      return;
    }
    if (arena == 0 as *ASTArena || expr_ref <= 0) {
      *line_out = 0;
      *col_out = 0;
      return;
    }
    l = pipeline_expr_line_at(arena, expr_ref);
    c = pipeline_expr_col_at(arena, expr_ref);
    *line_out = l;
    *col_out = c;
    if (l > 0) {
      return;
    }
    k = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (glue_expr_kind_is_assign_like_ord(k) != 0) {
      child = pipeline_expr_binop_left_ref_at(arena, expr_ref);
      typeck_expr_diag_line_col(arena, child, line_out, col_out);
      if (*line_out > 0) {
        return;
      }
      child = pipeline_expr_binop_right_ref_at(arena, expr_ref);
      typeck_expr_diag_line_col(arena, child, line_out, col_out);
      return;
    }
    /* EXPR_ADDR_OF=51, EXPR_RETURN=41, EXPR_NEG=22, EXPR_LOGNOT=24 */
    if (k == 51 || k == 41 || k == 22 || k == 24) {
      child = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
      typeck_expr_diag_line_col(arena, child, line_out, col_out);
    }
  }
}

/**
 * M-3 helper: 1 if src is region-bound slice and expect is unbound T[].
 * wave235 G.7 pure leave from residual pipeline_typeck_slice_region_escape_c.
 * @param arena *ASTArena — type pool
 * @param expect_ref i32 — destination type_ref
 * @param src_ref i32 — source type_ref
 * @return i32 — 1 escape, 0 ok / not applicable
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_slice_region_escape(arena: *ASTArena, expect_ref: i32, src_ref: i32): i32 {
  // PLATFORM: SHARED — TYPE_SLICE region escape predicate.
  unsafe {
    if (arena == 0 as *ASTArena || expect_ref <= 0 || src_ref <= 0) {
      return 0;
    }
    /* TYPE_SLICE ord == 11 */
    if (pipeline_type_kind_ord_at(arena, expect_ref) != 11) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, src_ref) != 11) {
      return 0;
    }
    if (pipeline_type_region_label_len_at(arena, src_ref) > 0
    && pipeline_type_region_label_len_at(arena, expect_ref) <= 0) {
      return 1;
    }
    return 0;
  }
}

/**
 * M-3 helper: 1 if both slices carry labels and labels differ.
 * wave235 G.7 pure leave from residual pipeline_typeck_slice_region_conflict_c.
 * @param arena *ASTArena — type pool
 * @param expect_ref i32 — destination type_ref
 * @param src_ref i32 — source type_ref
 * @return i32 — 1 mismatch, 0 ok / not applicable
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_slice_region_conflict(arena: *ASTArena, expect_ref: i32, src_ref: i32): i32 {
  // PLATFORM: SHARED — TYPE_SLICE region label conflict predicate.
  unsafe {
    let ek: i32 = 0;
    let sk: i32 = 0;
    let eb: u8[128] = [];
    let sb: u8[128] = [];
    if (arena == 0 as *ASTArena || expect_ref <= 0 || src_ref <= 0) {
      return 0;
    }
    /* TYPE_SLICE ord == 11 */
    if (pipeline_type_kind_ord_at(arena, expect_ref) != 11) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, src_ref) != 11) {
      return 0;
    }
    ek = pipeline_type_region_label_len_at(arena, expect_ref);
    sk = pipeline_type_region_label_len_at(arena, src_ref);
    if (ek <= 0 || sk <= 0) {
      return 0;
    }
    if (pipeline_type_region_label_into(arena, expect_ref, &eb[0]) != ek) {
      return 0;
    }
    if (pipeline_type_region_label_into(arena, src_ref, &sb[0]) != sk) {
      return 0;
    }
    if (name_equal(&eb[0], ek, &sb[0], sk)) {
      return 0;
    }
    return 1;
  }
}

/**
 * M-3 slice region assign/let/arg gate: escape or label mismatch → typeck error.
 * wave235 G.7 pure leave: was Cap residual pipeline_typeck_check_slice_region_assign_c.
 * Builds diagnostic text with typeck_diag_append_lit (lsp face is msg-only).
 * @param arena *ASTArena — type + expr arena
 * @param site_expr_ref i32 — site for line/col (assign/let/arg)
 * @param expect_ref i32 — formal / LHS type_ref
 * @param src_ref i32 — RHS / arg resolved type_ref
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single slice-region assign authority.
 */
export function typeck_check_slice_region_assign(arena: *ASTArena, site_expr_ref: i32,
expect_ref: i32, src_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let sb: u8[128] = [];
    let eb: u8[128] = [];
    let slen: i32 = 0;
    let elen: i32 = 0;
    let msg: u8[256] = [];
    let p: i32 = 0;
    let z: i32 = 0;
    if (arena == 0 as *ASTArena || expect_ref <= 0 || src_ref <= 0) {
      return 0;
    }
    /* TYPE_SLICE ord == 11 */
    if (pipeline_type_kind_ord_at(arena, expect_ref) != 11) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, src_ref) != 11) {
      return 0;
    }
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    if (typeck_slice_region_escape(arena, expect_ref, src_ref) != 0) {
      slen = pipeline_type_region_label_into(arena, src_ref, &sb[0]);
      if (slen < 0) {
        slen = 0;
      }
      if (slen > 64) {
        slen = 64;
      }
      z = 0;
      while (z < 256) {
        msg[z] = 0;
        z = z + 1;
      }
      /* "slice region escape: cannot assign <" + label + "> slice to unbound T[]" */
      p = typeck_diag_append_lit(&msg[0], 0, 255, "slice region escape: cannot assign <", 36);
      p = typeck_diag_append_lit(&msg[0], p, 255, &sb[0], slen);
      p = typeck_diag_append_lit(&msg[0], p, 255, "> slice to unbound T[]", 22);
      msg[p] = 0;
      lsp_diag_report_typeck(line, col, &msg[0]);
      return 0 - 1;
    }
    if (typeck_slice_region_conflict(arena, expect_ref, src_ref) != 0) {
      elen = pipeline_type_region_label_into(arena, expect_ref, &eb[0]);
      slen = pipeline_type_region_label_into(arena, src_ref, &sb[0]);
      if (elen < 0) {
        elen = 0;
      }
      if (slen < 0) {
        slen = 0;
      }
      if (elen > 64) {
        elen = 64;
      }
      if (slen > 64) {
        slen = 64;
      }
      z = 0;
      while (z < 256) {
        msg[z] = 0;
        z = z + 1;
      }
      /* "slice region mismatch: expected <" + e + ">, found <" + s + ">" */
      p = typeck_diag_append_lit(&msg[0], 0, 255, "slice region mismatch: expected <", 33);
      p = typeck_diag_append_lit(&msg[0], p, 255, &eb[0], elen);
      p = typeck_diag_append_lit(&msg[0], p, 255, ">, found <", 10);
      p = typeck_diag_append_lit(&msg[0], p, 255, &sb[0], slen);
      p = typeck_diag_append_lit(&msg[0], p, 255, ">", 1);
      msg[p] = 0;
      lsp_diag_report_typeck(line, col, &msg[0]);
      return 0 - 1;
    }
    return 0;
  }
}

/**
 * M-3 return-path slice region escape / mismatch gate.
 * wave235 G.7 pure leave: was Cap residual pipeline_typeck_check_return_slice_region_c.
 * @param arena *ASTArena — type + expr arena
 * @param ret_site_ref i32 — return expr for line/col
 * @param op_ref i32 — return operand expr
 * @param func_return_ref i32 — function return type_ref
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single return-slice-region authority.
 */
export function typeck_check_return_slice_region(arena: *ASTArena, ret_site_ref: i32,
op_ref: i32, func_return_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let got_ref: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let sb: u8[128] = [];
    let eb: u8[128] = [];
    let slen: i32 = 0;
    let elen: i32 = 0;
    let msg: u8[256] = [];
    let p: i32 = 0;
    let z: i32 = 0;
    if (arena == 0 as *ASTArena || op_ref <= 0 || func_return_ref <= 0) {
      return 0;
    }
    /* TYPE_SLICE ord == 11 */
    if (pipeline_type_kind_ord_at(arena, func_return_ref) != 11) {
      return 0;
    }
    got_ref = pipeline_expr_resolved_type_ref(arena, op_ref);
    if (got_ref <= 0 || pipeline_type_kind_ord_at(arena, got_ref) != 11) {
      return 0;
    }
    line = 0;
    col = 0;
    if (ret_site_ref > 0) {
      line = pipeline_expr_line_at(arena, ret_site_ref);
      col = pipeline_expr_col_at(arena, ret_site_ref);
    }
    if (typeck_slice_region_escape(arena, func_return_ref, got_ref) != 0) {
      slen = pipeline_type_region_label_into(arena, got_ref, &sb[0]);
      if (slen < 0) {
        slen = 0;
      }
      if (slen > 64) {
        slen = 64;
      }
      z = 0;
      while (z < 256) {
        msg[z] = 0;
        z = z + 1;
      }
      /* "slice region escape: cannot return <" + label + "> slice as unbound T[]" */
      p = typeck_diag_append_lit(&msg[0], 0, 255, "slice region escape: cannot return <", 36);
      p = typeck_diag_append_lit(&msg[0], p, 255, &sb[0], slen);
      p = typeck_diag_append_lit(&msg[0], p, 255, "> slice as unbound T[]", 22);
      msg[p] = 0;
      lsp_diag_report_typeck(line, col, &msg[0]);
      return 0 - 1;
    }
    if (typeck_slice_region_conflict(arena, func_return_ref, got_ref) != 0) {
      elen = pipeline_type_region_label_into(arena, func_return_ref, &eb[0]);
      slen = pipeline_type_region_label_into(arena, got_ref, &sb[0]);
      if (elen < 0) {
        elen = 0;
      }
      if (slen < 0) {
        slen = 0;
      }
      if (elen > 64) {
        elen = 64;
      }
      if (slen > 64) {
        slen = 64;
      }
      z = 0;
      while (z < 256) {
        msg[z] = 0;
        z = z + 1;
      }
      /* "slice region mismatch in return: expected <" + e + ">, found <" + s + ">" */
      p = typeck_diag_append_lit(&msg[0], 0, 255, "slice region mismatch in return: expected <", 43);
      p = typeck_diag_append_lit(&msg[0], p, 255, &eb[0], elen);
      p = typeck_diag_append_lit(&msg[0], p, 255, ">, found <", 10);
      p = typeck_diag_append_lit(&msg[0], p, 255, &sb[0], slen);
      p = typeck_diag_append_lit(&msg[0], p, 255, ">", 1);
      msg[p] = 0;
      lsp_diag_report_typeck(line, col, &msg[0]);
      return 0 - 1;
    }
    return 0;
  }
}

/**
 * WPO-S3 helper: 1 if ty_ref is TYPE_PTR stamped with "stack_local" region label.
 * wave236 G.7 pure leave from residual typeck_ptr_has_stack_local_label_c.
 * @param arena *ASTArena — type pool
 * @param ty_ref i32 — candidate pointer type_ref
 * @return i32 — 1 stack-local PTR, 0 otherwise
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_ptr_has_stack_local_label(arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — TYPE_PTR region label "stack_local" (len 11).
  // out buffer must be >= 64: pipeline_type_region_label_into may write label
  // slot (historical full-64 memcpy fixed at produce site; keep 64 for safety).
  unsafe {
    let lbl: u8[64] = [];
    let n: i32 = 0;
    if (arena == 0 as *ASTArena || ty_ref <= 0) {
      return 0;
    }
    /* TYPE_PTR ord == 9 */
    if (pipeline_type_kind_ord_at(arena, ty_ref) != 9) {
      return 0;
    }
    n = pipeline_type_region_label_len_at(arena, ty_ref);
    if (n != 11) {
      return 0;
    }
    if (pipeline_type_region_label_into(arena, ty_ref, &lbl[0]) != 11) {
      return 0;
    }
    /* "stack_local" */
    if (lbl[0] != 115 || lbl[1] != 116 || lbl[2] != 97 || lbl[3] != 99 || lbl[4] != 107) {
      return 0;
    }
    if (lbl[5] != 95 || lbl[6] != 108 || lbl[7] != 111 || lbl[8] != 99 || lbl[9] != 97 || lbl[10] != 108) {
      return 0;
    }
    return 1;
  }
}

/**
 * WPO-S3 helper: 1 if a let/const named vname exists anywhere in the block
 * subtree (while/for/if-then/else/region bodies). Residual fidelity for
 * post-scan paths where current_block_ref may not be pushed.
 * wave244 G.7: pure leave of residual typeck_block_tree_has_var_c (有则补全).
 * @param arena *ASTArena — block pool
 * @param block_ref i32 — root block to search
 * @param vname *u8 — variable name bytes
 * @param vlen i32 — name length
 * @return i32 — 1 found, 0 otherwise
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_block_tree_has_var(arena: *ASTArena, block_ref: i32, vname: *u8, vlen: i32): i32 {
  // PLATFORM: SHARED — recursive block-tree let/const lookup.
  unsafe {
    let nso: i32 = 0;
    let i: i32 = 0;
    let sk: i32 = 0;
    let idx: i32 = 0;
    let br: i32 = 0;
    let tr: i32 = 0;
    let er: i32 = 0;
    if (arena == 0 as *ASTArena || block_ref <= 0 || vname == 0 as *u8 || vlen <= 0) {
      return 0;
    }
    if (pipeline_block_resolve_var_type_ref(arena, block_ref, vname, vlen) > 0) {
      return 1;
    }
    nso = ast.ast_block_num_stmt_order(arena, block_ref);
    i = 0;
    while (i < nso) {
      sk = ast.ast_block_stmt_order_kind(arena, block_ref, i) as i32;
      idx = ast.ast_block_stmt_order_idx(arena, block_ref, i);
      br = 0;
      if (sk == 3 && idx >= 0 && idx < ast.ast_block_num_loops(arena, block_ref)) {
        br = ast.ast_block_while_body_ref(arena, block_ref, idx);
      } else if (sk == 4 && idx >= 0 && idx < ast.ast_block_num_for_loops(arena, block_ref)) {
        br = ast.ast_block_for_body_ref(arena, block_ref, idx);
      } else if (sk == 5 && idx >= 0 && idx < ast.ast_block_num_if_stmts(arena, block_ref)) {
        tr = ast.ast_block_if_then_body_ref(arena, block_ref, idx);
        er = ast.ast_block_if_else_body_ref(arena, block_ref, idx);
        if (tr > 0 && typeck_block_tree_has_var(arena, tr, vname, vlen) != 0) {
          return 1;
        }
        if (er > 0 && typeck_block_tree_has_var(arena, er, vname, vlen) != 0) {
          return 1;
        }
        i = i + 1;
        continue;
      } else if (sk == 6 && idx >= 0 && idx < ast.ast_block_num_regions(arena, block_ref)) {
        br = ast.ast_block_region_body_ref(arena, block_ref, idx);
      }
      if (br > 0 && typeck_block_tree_has_var(arena, br, vname, vlen) != 0) {
        return 1;
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * WPO-S3 helper: 1 if expr_ref is a VAR that is a block-local let/const (not a formal).
 * Product typeck path: current_block_ref resolve first; fallback full function-body
 * block-tree walk (wave244 residual fidelity — nested while/for/if/region lets).
 * @param module *Module — param name exclusion
 * @param arena *ASTArena — expr + block pool
 * @param ctx *PipelineDepCtx — current_func_index / current_block_ref
 * @param expr_ref i32 — candidate VAR expr
 * @return i32 — 1 block-local, 0 otherwise
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_var_is_block_local(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx,
expr_ref: i32): i32 {
  // PLATFORM: SHARED — local let vs formal discrimination for escape analysis.
  unsafe {
    let vlen: i32 = 0;
    let vbuf: u8[128] = [];
    let func_ix: i32 = 0;
    let body_ref: i32 = 0;
    let br: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || expr_ref <= 0) {
      return 0;
    }
    /* EXPR_VAR ord == 3 */
    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 3) {
      return 0;
    }
    vlen = pipeline_expr_var_name_len(arena, expr_ref);
    if (vlen <= 0 || vlen > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, expr_ref, &vbuf[0]);
    func_ix = pipeline_dep_ctx_current_func_index(ctx);
    if (func_ix >= 0 && pipeline_module_func_param_type_ref_for_name(module, func_ix, &vbuf[0], vlen) > 0) {
      return 0;
    }
    br = pipeline_dep_ctx_current_block_ref_at(ctx);
    if (br > 0 && pipeline_block_resolve_var_type_ref(arena, br, &vbuf[0], vlen) > 0) {
      return 1;
    }
    if (func_ix >= 0) {
      body_ref = pipeline_module_func_body_ref_at(module, func_ix);
      // wave244: residual fidelity — full block-tree walk (not root-only resolve).
      if (body_ref > 0 && typeck_block_tree_has_var(arena, body_ref, &vbuf[0], vlen) != 0) {
        return 1;
      }
    }
    return 0;
  }
}

/**
 * WPO-S3 helper: 1 if expr is &block_local or already carries stack_local PTR label.
 * wave236 G.7 pure leave from residual typeck_expr_is_addr_of_block_local_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param ctx *PipelineDepCtx
 * @param expr_ref i32 — candidate address expr
 * @return i32 — 1 stack-local address, 0 otherwise
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_expr_is_addr_of_block_local(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx,
expr_ref: i32): i32 {
  // PLATFORM: SHARED — &local / stack_local PTR predicate.
  unsafe {
    let op_ref: i32 = 0;
    let ty: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || expr_ref <= 0) {
      return 0;
    }
    ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    if (typeck_ptr_has_stack_local_label(arena, ty) != 0) {
      return 1;
    }
    /* EXPR_ADDR_OF ord == 51 */
    if (pipeline_expr_kind_ord_at(arena, expr_ref) != 51) {
      return 0;
    }
    op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    if (op_ref > 0 && typeck_var_is_block_local(module, arena, ctx, op_ref) != 0) {
      return 1;
    }
    return 0;
  }
}

/**
 * WPO-S3 helper: left is FIELD_ACCESS into *T formal dst_pi (or chain root).
 * wave236 G.7 pure leave from residual typeck_lval_is_param_ptr_field_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param func_ix i32 — enclosing function index
 * @param left_ref i32 — lvalue expr
 * @param dst_pi i32 — formal param index
 * @return i32 — 1 match, 0 otherwise
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_lval_is_param_ptr_field(module: *Module, arena: *ASTArena, func_ix: i32, left_ref: i32,
dst_pi: i32): i32 {
  // PLATFORM: SHARED — param *T field lvalue recognition.
  unsafe {
    let base_ref: i32 = 0;
    let param_ty: i32 = 0;
    let np: i32 = 0;
    let pi: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || left_ref <= 0 || func_ix < 0 || dst_pi < 0) {
      return 0;
    }
    /* EXPR_FIELD_ACCESS ord == 44 */
    if (pipeline_expr_kind_ord_at(arena, left_ref) != 44) {
      return 0;
    }
    base_ref = pipeline_expr_field_access_base_ref(arena, left_ref);
    if (glue_expr_is_func_param_at_c(arena, module, func_ix, base_ref, dst_pi) != 0) {
      param_ty = pipeline_module_func_param_type_ref_at(module, func_ix, dst_pi);
      if (param_ty > 0 && pipeline_type_kind_ord_at(arena, param_ty) == 9) {
        return 1;
      }
      return 0;
    }
    np = pipeline_module_func_num_params_at(module, func_ix);
    pi = 0;
    while (pi < np) {
      if (glue_expr_is_func_param_at_c(arena, module, func_ix, base_ref, pi) != 0) {
        param_ty = pipeline_module_func_param_type_ref_at(module, func_ix, pi);
        if (param_ty > 0 && pipeline_type_kind_ord_at(arena, param_ty) == 9) {
          if (pi == dst_pi) {
            return 1;
          }
          return 0;
        }
      }
      pi = pi + 1;
    }
    return 0;
  }
}

/**
 * MEM-A3 helper: 1 if ancestor is a strict outer parent of descendant (parent chain).
 * wave236 G.7 pure leave from residual typeck_block_is_strict_ancestor_c.
 * @param arena *ASTArena
 * @param ancestor i32 — outer block ref
 * @param descendant i32 — inner block ref
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_block_is_strict_ancestor(arena: *ASTArena, ancestor: i32, descendant: i32): i32 {
  // PLATFORM: SHARED — parent_block_ref walk (via block-pool face).
  unsafe {
    let cur: i32 = 0;
    let depth: i32 = 0;
    let p: i32 = 0;
    if (arena == 0 as *ASTArena || ancestor <= 0 || descendant <= 0 || ancestor == descendant) {
      return 0;
    }
    cur = descendant;
    depth = 0;
    while (cur > 0 && cur <= arena.num_blocks && depth < 128) {
      p = pipeline_block_parent_block_ref_at(arena, cur);
      if (p == ancestor) {
        return 1;
      }
      cur = p;
      depth = depth + 1;
    }
    return 0;
  }
}

/**
 * MEM-A3 helper: peel FIELD/INDEX chain to root VAR name bytes.
 * wave236 G.7 pure leave from residual typeck_expr_lval_root_var_c.
 * @param arena *ASTArena
 * @param expr_ref i32 — lvalue root
 * @param out *u8 — name buffer (>=128)
 * @param out_len *i32 — written name length
 * @return i32 — 1 ok, 0 fail
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_expr_lval_root_var(arena: *ASTArena, expr_ref: i32, out: *u8, out_len: *i32): i32 {
  // PLATFORM: SHARED — lvalue root VAR peel.
  unsafe {
    let cur: i32 = 0;
    let k: i32 = 0;
    let n: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || out == 0 as *u8 || out_len == 0 as *i32) {
      return 0;
    }
    cur = expr_ref;
    while (1 == 1) {
      k = pipeline_expr_kind_ord_at(arena, cur);
      /* EXPR_VAR == 3 */
      if (k == 3) {
        n = pipeline_expr_var_name_len(arena, cur);
        if (n <= 0 || n > 127) {
          return 0;
        }
        pipeline_expr_var_name_into(arena, cur, out);
        *out_len = n;
        return 1;
      }
      /* EXPR_FIELD_ACCESS == 44 */
      if (k == 44) {
        cur = pipeline_expr_field_access_base_ref(arena, cur);
      } else {
        /* EXPR_INDEX == 47 */
        if (k == 47) {
          cur = pipeline_expr_index_base_ref(arena, cur);
        } else {
          return 0;
        }
      }
      if (cur <= 0) {
        return 0;
      }
    }
    return 0;
  }
}

/**
 * WPO-S3 assign gate: forbid storing &local_struct into *T param field (outer escape).
 * Cap-T001: whole-body unsafe (typeck_unsafe_depth>0) skips. Not LANG-007 off.
 * wave236 G.7 pure leave: was Cap residual pipeline_typeck_check_struct_stack_escape_assign_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32 — site for line/col
 * @param left_ref i32 — assign LHS
 * @param right_ref i32 — assign RHS
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single stack-escape assign authority.
 */
export function typeck_check_struct_stack_escape_assign(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let func_ix: i32 = 0;
    let np: i32 = 0;
    let pi: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[80] = [];
    let p: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || left_ref <= 0 || right_ref <= 0) {
      return 0;
    }
    if (pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) > 0) {
      return 0;
    }
    if (typeck_expr_is_addr_of_block_local(module, arena, ctx, right_ref) == 0) {
      return 0;
    }
    func_ix = pipeline_dep_ctx_current_func_index(ctx);
    if (func_ix < 0) {
      return 0;
    }
    np = pipeline_module_func_num_params_at(module, func_ix);
    pi = 0;
    while (pi < np) {
      if (typeck_lval_is_param_ptr_field(module, arena, func_ix, left_ref, pi) != 0) {
        line = 0;
        col = 0;
        if (site_expr_ref > 0 && site_expr_ref <= arena.num_exprs) {
          line = pipeline_expr_line_at(arena, site_expr_ref);
          col = pipeline_expr_col_at(arena, site_expr_ref);
        }
        /* "struct stack escape: cannot store address of local struct in outer lifetime" len 73 */
        p = typeck_diag_append_lit(&msg[0], 0, 79,
        "struct stack escape: cannot store address of local struct in outer lifetime", 73);
        msg[p] = 0;
        lsp_diag_report_typeck(line, col, &msg[0]);
        return 0 - 1;
      }
      pi = pi + 1;
    }
    return 0;
  }
}

/**
 * MEM-A3 assign gate: forbid writing inner-block local address into outer-block var.
 * wave236 G.7 pure leave: was Cap residual pipeline_typeck_check_scope_borrow_assign_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32 — site for line/col
 * @param left_ref i32 — assign LHS
 * @param right_ref i32 — assign RHS (&inner)
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single scope-borrow assign authority.
 */
export function typeck_check_scope_borrow_assign(module: *Module, arena: *ASTArena, site_expr_ref: i32,
left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let lname: u8[128] = [];
    let rname: u8[128] = [];
    let llen: i32 = 0;
    let rlen: i32 = 0;
    let op_ref: i32 = 0;
    let site_block: i32 = 0;
    let lblock: i32 = 0;
    let rblock: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[24] = [];
    let p: i32 = 0;
    let cfi: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || left_ref <= 0 || right_ref <= 0) {
      return 0;
    }
    if (typeck_expr_is_addr_of_block_local(module, arena, ctx, right_ref) == 0) {
      return 0;
    }
    if (typeck_expr_lval_root_var(arena, left_ref, &lname[0], &llen) == 0) {
      return 0;
    }
    /* EXPR_ADDR_OF == 51 */
    if (pipeline_expr_kind_ord_at(arena, right_ref) != 51) {
      return 0;
    }
    op_ref = pipeline_expr_unary_operand_ref_at(arena, right_ref);
    /* EXPR_VAR == 3 */
    if (op_ref <= 0 || pipeline_expr_kind_ord_at(arena, op_ref) != 3) {
      return 0;
    }
    rlen = pipeline_expr_var_name_len(arena, op_ref);
    if (rlen <= 0 || rlen > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, op_ref, &rname[0]);
    site_block = pipeline_dep_ctx_current_block_ref_at(ctx);
    if (site_block <= 0) {
      cfi = pipeline_dep_ctx_current_func_index(ctx);
      if (cfi >= 0) {
        site_block = pipeline_module_func_body_ref_at(module, cfi);
      }
    }
    if (site_block <= 0) {
      return 0;
    }
    lblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &lname[0], llen);
    rblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &rname[0], rlen);
    if (lblock <= 0 || rblock <= 0 || lblock == rblock) {
      return 0;
    }
    if (typeck_block_is_strict_ancestor(arena, lblock, rblock) == 0) {
      return 0;
    }
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    /* "scope borrow escape" len 19 */
    p = typeck_diag_append_lit(&msg[0], 0, 23, "scope borrow escape", 19);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * MEM-A3 return gate: forbid returning address of block-local via *T return type.
 * wave236 G.7 pure leave: was Cap residual pipeline_typeck_check_scope_borrow_return_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32 — return expr site
 * @param op_ref i32 — return operand
 * @param return_type_ref i32 — function return type
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single scope-borrow return authority.
 */
export function typeck_check_scope_borrow_return(module: *Module, arena: *ASTArena, site_expr_ref: i32,
op_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[24] = [];
    let p: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || site_expr_ref <= 0 || op_ref <= 0) {
      return 0;
    }
    if (return_type_ref <= 0 || pipeline_type_kind_ord_at(arena, return_type_ref) != 9) {
      return 0;
    }
    if (typeck_expr_is_addr_of_block_local(module, arena, ctx, op_ref) == 0) {
      return 0;
    }
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    p = typeck_diag_append_lit(&msg[0], 0, 23, "scope borrow escape", 19);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * MEM-C1 helper: 1 if ty_ref is TYPE_NAMED "Allocator".
 * wave237 pure leave from residual typeck_type_is_allocator_struct_c.
 * @param arena *ASTArena
 * @param ty_ref i32 — type ref to test
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck
 */
function typeck_type_is_allocator_struct(arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — TYPE_NAMED bare "Allocator" or qualified "heap.Allocator".
  unsafe {
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    let off: i32 = 0;
    if (arena == 0 as *ASTArena || ty_ref <= 0) {
      return 0;
    }
    /* TYPE_NAMED == 8 */
    if (pipeline_type_kind_ord_at(arena, ty_ref) != 8) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, ty_ref, &nm[0]);
    /* Bare "Allocator" (len 9) — historical residual exact match. */
    if (name_equal(&nm[0], nlen, "Allocator" as *u8, 9)) {
      return 1;
    }
    /*
     * Import-qualified TYPE_NAMED (e.g. heap.Allocator): accept when the
     * suffix after the last '.' is exactly "Allocator". Residual only matched
     * bare name; product return-escape probes use heap.Allocator — complete
     * the authority (G.7 有则补全), do not open a second gate.
     */
    if (nlen > 10) {
      off = nlen - 9;
      /* preceding byte must be '.' */
      if (nm[off - 1] == 46) {
        if (name_equal(&nm[off], 9, "Allocator" as *u8, 9)) {
          return 1;
        }
      }
    }
    return 0;
  }
}

/**
 * MEM-C1 AL-04 assign gate: forbid writing Allocator-typed values into outer
 * vars while inside with_arena (allocator region escape).
 * Scalar outer writes (`k = 1` dest extra-arm / function-body) are not
 * allocator-region values — same cut as the return gate, which only rejects
 * TYPE_NAMED Allocator. Unknown / missing decl type stays conservative.
 * wave237 G.7 pure leave: was Cap residual pipeline_typeck_check_allocator_region_assign_c.
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32 — site for line/col
 * @param left_ref i32 — assign LHS
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single allocator-region assign authority.
 */
export function typeck_check_allocator_region_assign(module: *Module, arena: *ASTArena, site_expr_ref: i32,
left_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let lname: u8[128] = [];
    let llen: i32 = 0;
    let wa_body: i32 = 0;
    let site_block: i32 = 0;
    let lblock: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[28] = [];
    let p: i32 = 0;
    let i: i32 = 0;
    let nl: i32 = 0;
    let nlen: i32 = 0;
    let lhs_ty: i32 = 0;
    let right_ref: i32 = 0;
    let rhs_kind: i32 = 0;
    let nm: u8[64] = [];
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || left_ref <= 0) {
      return 0;
    }
    /* Outside any with_arena nest → no allocator region gate. */
    if (pipeline_typeck_with_arena_scope_n_at() <= 0) {
      return 0;
    }
    if (typeck_expr_lval_root_var(arena, left_ref, &lname[0], &llen) == 0) {
      return 0;
    }
    wa_body = pipeline_typeck_with_arena_current_body_ref_c();
    if (wa_body <= 0) {
      return 0;
    }
    site_block = pipeline_dep_ctx_current_block_ref_at(ctx);
    if (site_block <= 0) {
      site_block = wa_body;
    }
    lblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &lname[0], llen);
    if (lblock <= 0) {
      return 0;
    }
    /* LHS declared inside with_arena body (or nested under it) → ok. */
    if (lblock == wa_body || typeck_block_is_strict_ancestor(arena, wa_body, lblock) != 0) {
      return 0;
    }
    /* LHS must be an outer ancestor of the with_arena body to count as escape. */
    if (typeck_block_is_strict_ancestor(arena, lblock, wa_body) == 0) {
      return 0;
    }
    /*
     * AL-04 assign = Allocator-typed outer write only (G.7 complete;
     * same as typeck_check_allocator_region_return). An integer /
     * bool literal RHS cannot be an Allocator value — dest extra-arm
     * `k = 1` and function-body `k = 1` take this arm. EXPR_LIT=0.
     * Then prefer the LHS resolved type; scan decl-block lets if
     * empty. Known non-Allocator → allow. Missing type keeps the
     * historical reject (conservative).
     * PLATFORM: SHARED — with_arena assign; dest extra-arm k=1.
     */
    right_ref = pipeline_expr_binop_right_ref_at(arena, site_expr_ref);
    if (right_ref > 0) {
      rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref);
      if (rhs_kind == 0) {
        return 0;
      }
    }
    lhs_ty = pipeline_expr_resolved_type_ref(arena, left_ref);
    if (lhs_ty <= 0) {
      nl = ast.ast_block_num_lets(arena, lblock);
      i = 0;
      while (i < nl) {
        nlen = pipeline_block_let_name_len(arena, lblock, i);
        if (nlen == llen && nlen > 0 && nlen < 64) {
          pipeline_block_let_name_copy64(arena, lblock, i, &nm[0]);
          if (name_equal(&nm[0], nlen, &lname[0], llen)) {
            lhs_ty = pipeline_block_let_type_ref(arena, lblock, i);
            i = nl;
          }
        }
        i = i + 1;
      }
    }
    if (lhs_ty > 0 && typeck_type_is_allocator_struct(arena, lhs_ty) == 0) {
      return 0;
    }
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    /* "allocator region escape" len 24 */
    p = typeck_diag_append_lit(&msg[0], 0, 27, "allocator region escape", 24);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * MEM-C1 AL-04 return gate: forbid returning named Allocator while inside with_arena.
 * wave237 G.7 pure leave: was Cap residual pipeline_typeck_check_allocator_region_return_c.
 * @param arena *ASTArena
 * @param site_expr_ref i32 — return expr site
 * @param return_type_ref i32 — function return type
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single allocator-region return authority.
 */
export function typeck_check_allocator_region_return(arena: *ASTArena, site_expr_ref: i32,
return_type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[28] = [];
    let p: i32 = 0;
    if (arena == 0 as *ASTArena || site_expr_ref <= 0) {
      return 0;
    }
    if (pipeline_typeck_with_arena_scope_n_at() <= 0) {
      return 0;
    }
    if (typeck_type_is_allocator_struct(arena, return_type_ref) == 0) {
      return 0;
    }
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    p = typeck_diag_append_lit(&msg[0], 0, 27, "allocator region escape", 24);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * MOD-02 sub-check: *Struct formal vs call arg (incl. &local) compatibility.
 * wave239 G.7 pure leave: was Cap residual static typeck_check_call_ptr_struct_compat_c
 * (method_call.c). Used only from typeck_check_call_slice_region.
 * @param module *Module
 * @param arena *ASTArena
 * @param call_expr_ref i32 — CALL site for line/col
 * @param param_ref i32 — formal type_ref
 * @param arg_ref i32 — argument expr_ref
 * @return i32 — 0 ok / not applicable; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single *Struct call-arg gate.
 */
function typeck_check_call_ptr_struct_compat(module: *Module, arena: *ASTArena, call_expr_ref: i32,
param_ref: i32, arg_ref: i32): i32 {
  // PLATFORM: SHARED — *Struct formal vs arg shape + repr gate.
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let param_elem: i32 = 0;
    let arg_ty: i32 = 0;
    let arg_kind: i32 = 0;
    let arg_elem: i32 = 0;
    let op: i32 = 0;
    let m_u8: *u8 = 0 as *u8;
    let a_u8: *u8 = 0 as *u8;
    let msg: u8[64] = [];
    let p: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || param_ref <= 0 || arg_ref <= 0) {
      return 0;
    }
    /* TYPE_PTR ord == 9 */
    if (pipeline_type_kind_ord_at(arena, param_ref) != 9) {
      return 0;
    }
    param_elem = pipeline_type_elem_ref_at(arena, param_ref);
    m_u8 = module as *u8;
    a_u8 = arena as *u8;
    if (param_elem <= 0 || typeck_type_is_named_struct_c(m_u8, a_u8, param_elem) == 0) {
      return 0;
    }
    arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
    arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref);
    /* EXPR_ADDR_OF ord == 51 — peel operand when arg still untyped */
    if (arg_ty <= 0 && arg_kind == 51) {
      op = pipeline_expr_unary_operand_ref_at(arena, arg_ref);
      if (op > 0) {
        arg_ty = pipeline_expr_resolved_type_ref(arena, op);
      }
    }
    if (arg_ty <= 0) {
      return 0;
    }
    /* TYPE_NAMED=8, TYPE_PTR=9 */
    if (pipeline_type_kind_ord_at(arena, arg_ty) == 8) {
      arg_elem = arg_ty;
    } else if (pipeline_type_kind_ord_at(arena, arg_ty) == 9) {
      arg_elem = pipeline_type_elem_ref_at(arena, arg_ty);
    } else {
      return 0;
    }
    if (arg_elem <= 0 || typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) == 0) {
      return 0;
    }
    /* Positive path shared with call_arg_types / score (wave234 pure leave). */
    if (typeck_call_arg_repr_compatible_ok(module, arena, param_ref, arg_ref) != 0) {
      return 0;
    }
    line = pipeline_expr_line_at(arena, call_expr_ref);
    col = pipeline_expr_col_at(arena, call_expr_ref);
    /* "no matching overload (incompatible struct pointer argument)" len 56 */
    p = typeck_diag_append_lit(&msg[0], 0, 63,
    "no matching overload (incompatible struct pointer argument)", 56);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * M-3 CALL post-resolve: per-arg slice region + array_lit stamp + *Struct compat
 * + WPO-S3 &local struct with outer *Struct sibling reject.
 * wave239 G.7 pure leave: was Cap residual pipeline_typeck_check_call_slice_region_c.
 * @param module *Module — entry / caller module
 * @param arena *ASTArena — call expr arena
 * @param call_expr_ref i32 — EXPR_CALL
 * @param ctx *PipelineDepCtx — dep modules + unsafe depth (nullable belt)
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck — G.7 single call_slice_region authority.
 */
export function typeck_check_call_slice_region(module: *Module, arena: *ASTArena, call_expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — post-resolve CALL arg region / stack-escape gate.
  unsafe {
    let func_ix: i32 = 0;
    let dep_ix: i32 = 0;
    let num_args: i32 = 0;
    let np: i32 = 0;
    let i: i32 = 0;
    let arg_ref: i32 = 0;
    let param_ref: i32 = 0;
    let arg_ty: i32 = 0;
    let arg_kind: i32 = 0;
    let param_kind: i32 = 0;
    let callee_mod: *Module = 0 as *Module;
    let dm: *Module = 0 as *Module;
    let m_u8: *u8 = 0 as *u8;
    let a_u8: *u8 = 0 as *u8;
    let skip_env: *u8 = 0 as *u8;
    let src_i: i32 = 0;
    let dst_j: i32 = 0;
    let stack_arg: i32 = 0;
    let stack_arg_ty: i32 = 0;
    let stack_arg_elem: i32 = 0;
    let param_ref2: i32 = 0;
    let elem_ref: i32 = 0;
    let other_arg: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let msg: u8[96] = [];
    let p: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || call_expr_ref <= 0) {
      return 0;
    }
    /* LANG-007 belt: legacy typeck_gen call path may skip pure call body S0. */
    if (typeck_check_extern_call_unsafe_boundary(module, arena, call_expr_ref, ctx) != 0) {
      return 0 - 1;
    }
    func_ix = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref);
    dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
    if (func_ix < 0) {
      m_u8 = module as *u8;
      a_u8 = arena as *u8;
      func_ix = pipeline_typeck_resolve_call_func_index_for_emit_c(m_u8, a_u8, call_expr_ref);
    }
    if (func_ix < 0) {
      return 0;
    }
    callee_mod = module;
    if (dep_ix >= 0 && ctx != 0 as *PipelineDepCtx) {
      dm = pipeline_dep_ctx_module_at(ctx, dep_ix);
      if (dm != 0 as *Module) {
        callee_mod = dm;
      }
    }
    num_args = pipeline_expr_call_num_args_at(arena, call_expr_ref);
    np = pipeline_module_func_num_params_at(callee_mod, func_ix);
    if (num_args != np) {
      return 0;
    }
    /*
     * FLOAT_LIT args were check_expr'd against call ambient (not the formal).
     * G.7: reuse typeck_stamp_resolved_args_float_lit → coerce_init_float_lit.
     */
    typeck_stamp_resolved_args_float_lit(arena, call_expr_ref, callee_mod, func_ix, dep_ix, ctx, 0);
    i = 0;
    while (i < num_args) {
      arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, i);
      param_ref = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i);
      /*
       * wave332: bare ARRAY_LIT args check_expr'd before resolve → no param type
       * then; stamp here so host emit_call_arg_slice_abi sees slice shape.
       * G.7: reuse typeck_coerce_init_array_vector_lit_to_decl (let/assign authority).
       */
      if (arg_ref > 0 && param_ref > 0) {
        arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref);
        param_kind = pipeline_type_kind_ord_at(arena, param_ref);
        typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref, param_ref, param_kind, arg_kind);
      }
      arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
      if (typeck_check_slice_region_assign(arena, arg_ref, param_ref, arg_ty) != 0) {
        return 0 - 1;
      }
      if (typeck_check_call_ptr_struct_compat(module, arena, call_expr_ref, param_ref, arg_ref) != 0) {
        return 0 - 1;
      }
      i = i + 1;
    }
    /*
     * WPO-S3: &local struct + outer *Struct formal sibling → reject.
     * Cap-T001: skip inside unsafe { } (same gate as call_struct_stack_escape).
     */
    if (ctx != 0 as *PipelineDepCtx && num_args >= 2) {
      skip_env = link_abi_getenv("XLANG_SKIP_STACK_ESCAPE" as *u8);
      if (skip_env == 0 as *u8 && pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) <= 0) {
        src_i = 0;
        while (src_i < num_args) {
          stack_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, src_i);
          if (typeck_expr_is_addr_of_block_local(module, arena, ctx, stack_arg) != 0) {
            stack_arg_ty = pipeline_expr_resolved_type_ref(arena, stack_arg);
            if (stack_arg_ty > 0 && pipeline_type_kind_ord_at(arena, stack_arg_ty) == 9) {
              stack_arg_elem = pipeline_type_elem_ref_at(arena, stack_arg_ty);
              m_u8 = module as *u8;
              a_u8 = arena as *u8;
              if (stack_arg_elem > 0 && typeck_type_is_named_struct_c(m_u8, a_u8, stack_arg_elem) != 0) {
                dst_j = 0;
                while (dst_j < num_args) {
                  if (dst_j != src_i) {
                    param_ref2 = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, dst_j);
                    if (param_ref2 > 0 && pipeline_type_kind_ord_at(arena, param_ref2) == 9) {
                      elem_ref = pipeline_type_elem_ref_at(arena, param_ref2);
                      if (elem_ref > 0 && typeck_type_is_named_struct_c(m_u8, a_u8, elem_ref) != 0) {
                        other_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, dst_j);
                        /* same-frame &local sibling is not outer */
                        if (typeck_expr_is_addr_of_block_local(module, arena, ctx, other_arg) == 0) {
                          line = pipeline_expr_line_at(arena, call_expr_ref);
                          col = pipeline_expr_col_at(arena, call_expr_ref);
                          /* "struct stack escape: cannot pass address of local struct with outer struct pointer" len 78 */
                          p = typeck_diag_append_lit(&msg[0], 0, 95,
                          "struct stack escape: cannot pass address of local struct with outer struct pointer", 78);
                          msg[p] = 0;
                          lsp_diag_report_typeck(line, col, &msg[0]);
                          return 0 - 1;
                        }
                      }
                    }
                  }
                  dst_j = dst_j + 1;
                }
              }
            }
          }
          src_i = src_i + 1;
        }
      }
    }
    return 0;
  }
}

/**
 * Type-check EXPR_CALL: unsafe boundary, args, resolve, arity (wave660),
 * arg types (wave661), generic type-args gate, slice region, return resolve
 * + generic mono fixup (wave232 pure leave parity with former call_c).
 * Installs expected return (return_type_ref from let/assign/return) for
 * zero-arg overload pick and holds it through generic infer/fixup (wave453).
 * Cap residual pipeline_typeck_check_expr_call_c thins here — do NOT re-open
 * a second CALL body in residual C (dual-export ban).
 * @param module *Module — entry module
 * @param arena *ASTArena — expression arena
 * @param expr_ref i32 — EXPR_CALL
 * @param return_type_ref i32 — ambient expected return (let/assign/return); 0 if none
 * @param ctx *PipelineDepCtx — dep modules + unsafe depth
 * @return i32 — 0 success, -1 typeck fail
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_check_expr_call(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_args: i32 = 0;
    let expect_store: i32 = 0;
    let callee_ref: i32 = 0;
    let ret_ty: i32 = 0;
    /* LANG-007 S0: extern calls require unsafe { }. wave234 pure leave. */
    if (typeck_check_extern_call_unsafe_boundary(module, arena, expr_ref, ctx) != 0) {
      return -1;
    }
    num_args = pipeline_expr_call_num_args_at(arena, expr_ref);
    expect_store = 0;
    if (!ast.ref_is_null(return_type_ref) && return_type_ref > 0) {
      expect_store = return_type_ref;
    }
    /* Hold expected_ret through generic gate + fixup (wave453 / wave232). */
    typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), expect_store);
    if (typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, 0, num_args) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    if (typeck_check_expr_call_resolve(module, arena, expr_ref, ctx) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    /* wave660: hard-fail arity before generic / slice region / codegen. */
    if (typeck_check_call_arity(module, arena, expr_ref, ctx) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    /* wave661: hard-fail arg type vs formal after resolve+arity. */
    if (typeck_check_call_arg_types(module, arena, expr_ref, ctx) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    /* wave232: generic type-args / infer gate (was only in call_c residual). */
    if (pipeline_typeck_check_call_generic_type_args_c(module, arena, expr_ref, ctx, expect_store) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    /* wave239: call_slice pure leave — direct authority (not residual *_c hop). */
    if (typeck_check_call_slice_region(module, arena, expr_ref, ctx) != 0) {
      typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
      return -1;
    }
    /* Stamp callee return when resolve left resolved_type_ref empty.
     * wave247: pure resolve_call_callee_return_type (not residual *_c hop). */
    if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref);
      ret_ty = resolve_call_callee_return_type(module, arena, callee_ref, expr_ref, ctx);
      if (ret_ty != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty);
      }
    }
    /* Mono fixup: free type-param return trees → concrete from args / expected_ret. */
    glue_generic_call_fixup_resolved_type_c(module, arena, expr_ref, ctx, expect_store);
    typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);
    return 0;
  }
}

/**
 * Return 1 if ty cannot be an operand of scalar comparison or non-vector arithmetic.
 * Aggregates: TYPE_ARRAY/SLICE/LINEAR/VECTOR (host-C invalid; array cmp decay pointer-identity
 * false green; struct/array arith host-cc BLD001), and TYPE_NAMED that matches a struct layout
 * (enum/alias scalars still allowed for cmp; VECTOR same-size arith is allowed by caller).
 * @param module *Module — current module (struct layout table)
 * @param arena *ASTArena — type arena
 * @param ty_ref i32 — resolved type ref of a binop operand
 * @return i32 — 1 aggregate / non-scalar-binop, 0 scalar/ptr/enum/alias-ok or null/unknown
 * PLATFORM: SHARED — wave657 cmp + wave658 arith + wave662 unary; G.7 single helper.
 */
export function typeck_type_is_aggregate_cmp_operand(module: *Module, arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_named: i32 = 8;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_linear: i32 = 12;
    let ord_vector: i32 = 13;
    let ko: i32 = 0;
    let rty: i32 = 0;
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    let nlayouts: i32 = 0;
    let k: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ast.ref_is_null(ty_ref)) {
      return 0;
    }
    /* Peel type aliases so `type MyI32 = i32` stays scalar-comparable. */
    rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
    if (ast.ref_is_null(rty)) {
      rty = ty_ref;
    }
    ko = pipeline_type_kind_ord_at(arena, rty);
    if (ko == ord_array || ko == ord_slice || ko == ord_linear || ko == ord_vector) {
      return 1;
    }
    if (ko != ord_named) {
      return 0;
    }
    /* TYPE_NAMED: reject only when it is a product struct layout (enum tags stay ok). */
    nlen = pipeline_type_named_name_into(arena, rty, &nm[0]);
    if (nlen <= 0 || nlen > 127) {
      return 0;
    }
    nlayouts = pipeline_module_num_struct_layouts_at(module);
    k = 0;
    while (k < nlayouts) {
      if (typeck_layout_name_equal(module, k, &nm[0], nlen)) {
        return 1;
      }
      k = k + 1;
    }
    return 0;
  }
}

/**
 * C integer promotions for compare operands (Defect D / 9.6.1 residual).
 * Sub-int families (u8 / NAMED i8,i16,u16) that true-widen to i32 are
 * stamped to i32 so `u8 == i32` is not mixed-type T001.
 * Does NOT apply usual arithmetic conversions: i32 vs i64 / u32 vs i32
 * stay mismatch (wave666).
 * @param arena *ASTArena — type/expr pool
 * @param expr_ref i32 — operand expr to stamp when promoted
 * @param ty_ref i32 — current resolved type of expr_ref
 * @return i32 — 1 if stamped to i32; 0 if already i32 / not a sub-int / cannot widen
 * PLATFORM: SHARED — typeck_gen pin + empty_surface same commit.
 */
function typeck_cmp_promote_subint_to_i32(arena: *ASTArena, expr_ref: i32, ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fam: i32 = 0;
    let i32t: i32 = 0;
    if (ast.ref_is_null(ty_ref) || ty_ref <= 0 || expr_ref <= 0) {
      return 0;
    }
    fam = typeck_int_family_id(arena, ty_ref);
    /* Already i32 (family 0) or not an integer. */
    if (fam == 0 || fam < 0) {
      return 0;
    }
    i32t = ensure_i32_type_ref(arena);
    if (i32t <= 0) {
      return 0;
    }
    /* G.7: reuse dest-directed true-widen-to-i32 (u8/i8/i16/u16 → i32).
     * i32→u8 narrow-store is dest=u8, not used here. */
    if (typeck_integer_widen_ok_refs(arena, i32t, ty_ref)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32t);
      return 1;
    }
    return 0;
  }
}

/**
 * Type-check comparison binops (== != < <= > >=). Stamps result as bool.
 * wave317: f32 peer + bare FLOAT_LIT coerce. wave657: hard-fail aggregate operands.
 * wave665: LOGAND/LOGOR require bool. wave666: mixed operand types hard-fail
 * except Defect D C integer promotions (sub-int → i32) inside the equal gate.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EQ/NE/LT/LE/GT/GE expr
 * @param return_type_ref i32 — ambient return type for subexpr
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 hard fail
 * PLATFORM: SHARED — seed typeck_gen + empty_surface same commit.
 */
export function typeck_check_expr_binop_cmp(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let bop_l: i32 = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    let bop_r: i32 = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    let bt: i32 = 0;
    let lt_cmp: i32 = 0;
    let rt_cmp: i32 = 0;
    let lko_cmp: i32 = 0;
    let rko_cmp: i32 = 0;
    let lk_cmp: i32 = 0;
    let rk_cmp: i32 = 0;
    let ord_lit: i32 = 0;
    let ord_f32: i32 = 14;
    let ord_logand: i32 = 20;
    let ord_logor: i32 = 21;
    let expr_kind_cmp: i32 = 0;
    let line_ac: i32 = 0;
    let col_ac: i32 = 0;
    let is_logical: i32 = 0;
    if (check_expr(module, arena, bop_l, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (check_expr(module, arena, bop_r, return_type_ref, ctx) != 0) {
      return - 1;
    }
    /*
     * wave670 Cap residual: keyword `null` only compares with pointers (or null).
     * Runs immediately after operand check_expr — before LOGAND/typed gates —
     * so untyped null (type_ref 0) still hard-fails against non-ptr peers.
     * `null == null` both keyword → green; `null == p` / `p == null` peer ptr.
     * PLATFORM: SHARED — seed typeck_gen same commit.
     */
    if (typeck_expr_is_null_keyword(arena, bop_l) != 0
    && typeck_expr_is_null_keyword(arena, bop_r) == 0) {
      rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r);
      rko_cmp = 0;
      if (rt_cmp > 0) {
        rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp);
      }
      if (rt_cmp > 0 && rko_cmp != 9) {
        line_ac = pipeline_expr_line_at(arena, expr_ref);
        col_ac = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac);
        return -1;
      }
    } else if (typeck_expr_is_null_keyword(arena, bop_r) != 0
    && typeck_expr_is_null_keyword(arena, bop_l) == 0) {
      lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l);
      lko_cmp = 0;
      if (lt_cmp > 0) {
        lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp);
      }
      if (lt_cmp > 0 && lko_cmp != 9) {
        line_ac = pipeline_expr_line_at(arena, expr_ref);
        col_ac = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac);
        return -1;
      }
    }
    expr_kind_cmp = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (expr_kind_cmp == ord_logand || expr_kind_cmp == ord_logor) {
      is_logical = 1;
    }
    lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l);
    rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r);
    /*
     * wave665 Cap residual: LOGAND/LOGOR operands must be TYPE_BOOL (docs/04).
     * Root cause: binop_cmp stamped bool for any operands → `i32 && i32` / `f32 && f32`
     * typeck OK then freestanding/host C truthiness false green; if/while/for already
     * require bool, but nested `a && b` bypassed that gate.
     * Soft: unknown/null operand type (incomplete resolve) is not a hard leaf.
     * G.7: reuse type_ref_is_bool; diag logical_operand_not_bool.
     * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
     */
    if (is_logical != 0) {
      if (!ast.ref_is_null(lt_cmp) && lt_cmp > 0 && lt_cmp <= arena.num_types) {
        if (!type_ref_is_bool(arena, lt_cmp)) {
          line_ac = pipeline_expr_line_at(arena, expr_ref);
          col_ac = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac);
          return -1;
        }
      }
      if (!ast.ref_is_null(rt_cmp) && rt_cmp > 0 && rt_cmp <= arena.num_types) {
        if (!type_ref_is_bool(arena, rt_cmp)) {
          line_ac = pipeline_expr_line_at(arena, expr_ref);
          col_ac = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac);
          return -1;
        }
      }
      bt = ensure_bool_type_ref(arena);
      if (bt != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt);
      }
      return 0;
    }
    /* wave317: f32 peer + bare FLOAT_LIT / `-float` in cmp — G.7 reuse float_lit coerce
     * (same as binop_arith). Else `a:f32 < 6.0` keeps lit as f64 and freestanding/host
     * may mis-compare (Ubuntu while a<6.0 never entered). True f32 vs f64 vars unchanged. */
    if (!ast.ref_is_null(lt_cmp) && !ast.ref_is_null(rt_cmp)) {
      lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp);
      rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp);
      lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l);
      rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r);
      if (lko_cmp == ord_f32) {
        typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_cmp, ord_f32, rk_cmp);
      } else if (rko_cmp == ord_f32) {
        typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_cmp, ord_f32, lk_cmp);
      }
      /*
       * wave657 Cap residual: hard-fail aggregate ==/!=/relational at typeck.
       * Root cause: binop_cmp always stamped bool without checking operand kinds →
       * struct/slice `a == b` host-cc BLD001 (invalid C); fixed array `a == b` silent
       * pointer-identity false green (always unequal for distinct stack arrays).
       * Allowed: scalar ints/floats/bool, TYPE_PTR, TYPE_NAMED enum/alias-of-scalar.
       * Rejected: TYPE_ARRAY/SLICE/LINEAR/VECTOR; TYPE_NAMED matching a struct layout.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
       */
      if (typeck_type_is_aggregate_cmp_operand(module, arena, lt_cmp) != 0
      || typeck_type_is_aggregate_cmp_operand(module, arena, rt_cmp) != 0) {
        line_ac = pipeline_expr_line_at(arena, expr_ref);
        col_ac = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_aggregate_cmp(line_ac, col_ac);
        return -1;
      }
      /*
       * wave666 Cap residual: hard-fail mixed-type comparison at typeck.
       * Root cause: after aggregate gate, binop_cmp still stamped bool for any
       * remaining operands → `i32 == f32` / `i32 == i64` / `i32 == bool` /
       * `*i32 == *u8` typeck OK then freestanding/host C promotion false green
       * (or host warning-only for distinct pointer types).
       * Policy (strict, Cap residual): operands must be equal after peer lit coerce
       * (G.7 reuse typeck_coerce_init_lit_to_decl for bare INT_LIT / 0→ptr; float lit
       * already coerced above). No float widen, no int↔bool, no i32 vs i64 usual
       * arithmetic conversions (those were the wave666 false greens).
       * Defect D / 9.6.1 residual: C integer promotions ARE applied — sub-int
       * families (u8 / NAMED i8,i16,u16) stamp to i32 so `u8 == i32` is not T001.
       * Soft: unknown/null operand type (incomplete resolve) is not a hard leaf.
       * G.7: type_refs_equal; diag comparison_type_mismatch.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
       */
      lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l);
      rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r);
      if (!ast.ref_is_null(lt_cmp) && !ast.ref_is_null(rt_cmp)) {
        lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp);
        rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp);
        lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l);
        rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r);
        /* Peer integer/0-null lit coerce so `a:i32 == 1` and `p:*T == 0` stay green. */
        if (rk_cmp == ord_lit && typeck_coerce_init_lit_to_decl(arena, bop_r, lt_cmp, lko_cmp, rk_cmp) != 0) {
          rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r);
        } else if (lk_cmp == ord_lit
        && typeck_coerce_init_lit_to_decl(arena, bop_l, rt_cmp, rko_cmp, lk_cmp) != 0) {
          lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l);
        }
        if (lt_cmp > 0 && rt_cmp > 0 && lt_cmp <= arena.num_types && rt_cmp <= arena.num_types) {
          if (!type_refs_equal(arena, lt_cmp, rt_cmp)) {
            /* Defect D: promote sub-int operands to i32, then re-check equal. */
            if (typeck_cmp_promote_subint_to_i32(arena, bop_l, lt_cmp) != 0) {
              lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l);
            }
            if (typeck_cmp_promote_subint_to_i32(arena, bop_r, rt_cmp) != 0) {
              rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r);
            }
          }
          if (!type_refs_equal(arena, lt_cmp, rt_cmp)) {
            line_ac = pipeline_expr_line_at(arena, expr_ref);
            col_ac = pipeline_expr_col_at(arena, expr_ref);
            driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac);
            return -1;
          }
        }
      }
    }
    bt = ensure_bool_type_ref(arena);
    if (bt != 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_binop_arith(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_lit: i32 = 0;
    let bop_l: i32 = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    let bop_r: i32 = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    let expr_kind: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let lk_expr: i32 = 0;
    let rk_expr: i32 = 0;
    let lt_ar: i32 = 0;
    let rt_ar: i32 = 0;
    let lko: i32 = 0;
    let rko: i32 = 0;
    let out_ar: i32 = 0;
    let allow_i32_fallback: i32 = 0;
    let dbg_left: *u8 = 0 as *u8;
    let dbg_right: *u8 = 0 as *u8;
    let dbg_left_len: i32 = 0;
    let dbg_right_len: i32 = 0;
    let ord_type_vector: i32 = 13;
    let ord_i64: i32 = 5;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_void: i32 = 16;
    let ord_bool: i32 = 1;
    let ord_i32: i32 = 0;
    let ord_ptr: i32 = 9;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_add: i32 = 4;
    let ord_sub: i32 = 5;
    let ord_mod: i32 = 8;
    let ord_shl: i32 = 9;
    let ord_shr: i32 = 10;
    let ord_bitand: i32 = 11;
    let ord_bitor: i32 = 12;
    let ord_bitxor: i32 = 13;
    if (check_expr(module, arena, bop_l, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (check_expr(module, arena, bop_r, return_type_ref, ctx) != 0) {
      return - 1;
    }
    lt_ar = pipeline_expr_resolved_type_ref(arena, bop_l);
    rt_ar = pipeline_expr_resolved_type_ref(arena, bop_r);
    if (!ast.ref_is_null(lt_ar) && !ast.ref_is_null(rt_ar)) {
      lk_expr = pipeline_expr_kind_ord_at(arena, bop_l);
      rk_expr = pipeline_expr_kind_ord_at(arena, bop_r);
      dbg_left = driver_typeck_diag_scratch_expect();
      dbg_right = driver_typeck_diag_scratch_found();
      dbg_left_len = typeck_diag_fmt_type_or_question(arena, lt_ar, dbg_left);
      dbg_right_len = typeck_diag_fmt_type_or_question(arena, rt_ar, dbg_right);
      driver_diagnostic_typeck_binop_operands(expr_ref, bop_l, bop_r, lk_expr, rk_expr,
      pipeline_expr_block_ref_at(arena, bop_l), pipeline_expr_block_ref_at(arena, bop_r), lt_ar, rt_ar,
      dbg_left, dbg_left_len, dbg_right, dbg_right_len);
      lko = pipeline_type_kind_ord_at(arena, lt_ar);
      rko = pipeline_type_kind_ord_at(arena, rt_ar);
      /*
       * wave667 Cap residual: hard-fail void arithmetic at typeck.
       * Root cause: type_refs_equal / left-type / i32-fallback fallthrough stamped a
       * result type when either operand was TYPE_VOID (void call result + int, etc.)
       * → typeck OK then host-cc BLD001 `invalid operands to binary expression
       * ('void' and 'int')`. Soft residual after wave663 void-return gate.
       * Reject any + - * / % << >> & | ^ with a void operand. Soft: null/unknown
       * types (incomplete resolve) not hard-failed here.
       * G.7: driver_diagnostic_typeck_invalid_void_binop; unary -/~ void same diag.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
       */
      if (lko == ord_void || rko == ord_void) {
        let line_vb: i32 = pipeline_expr_line_at(arena, expr_ref);
        let col_vb: i32 = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_void_binop(line_vb, col_vb);
        return -1;
      }
      /*
       * wave677 Cap residual: hard-fail bool arithmetic / bitops / shifts at typeck.
       * Root cause: allow_i32_fallback rewrote bool operands to i32 (`true+false`,
       * `x<<true`, `true&false`) → freestanding/host false green; contradicts
       * wave671 (return bool→i32 hard) and LANG-006 scope (let/const only).
       * Soft: null/unknown types not hard-failed. G.7: invalid_bool_binop;
       * remove bool→i32 promotion block below.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
       */
      if (lko == ord_bool || rko == ord_bool) {
        let line_bb: i32 = pipeline_expr_line_at(arena, expr_ref);
        let col_bb: i32 = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_bool_binop(line_bb, col_bb);
        return -1;
      }
      /* Pointer ± integer is the only legal pointer arithmetic (C-like). */
      if (expr_kind == ord_add || expr_kind == ord_sub) {
        if (lko == ord_ptr && (rko == ord_i32 || rko == ord_usize || rko == ord_isize)) {
          out_ar = lt_ar;
        } else if (expr_kind == ord_add && rko == ord_ptr
        && (lko == ord_i32 || lko == ord_usize || lko == ord_isize)) {
          out_ar = rt_ar;
        }
      }
      /*
       * wave285 Cap residual: hard-fail illegal pointer arithmetic at typeck.
       * Root cause: type_refs_equal fallthrough accepted ptr+ptr / ptr*ptr / … and
       * codegen emitted invalid C → soft residual BLD001 (host-cc).
       * Allowed: ptr+int / int+ptr (ADD→ptr), ptr-int (SUB→ptr), ptr-ptr (SUB→isize).
       * Rejected: ptr+ptr (runtime *u8 string concat leave-off; use std.string or
       * adjacent string lits wave282), mul/div/mod/bitops with ptr, int-ptr, etc.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + ast_pool infer twin same commit.
       */
      if (lko == ord_ptr || rko == ord_ptr) {
        let line_pb: i32 = pipeline_expr_line_at(arena, expr_ref);
        let col_pb: i32 = pipeline_expr_col_at(arena, expr_ref);
        if (expr_kind == ord_add) {
          if (!ast.ref_is_null(out_ar)) {
            pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar);
            return 0;
          }
          driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb);
          return -1;
        }
        if (expr_kind == ord_sub) {
          if (lko == ord_ptr && rko == ord_ptr) {
            /* Pointer difference yields isize (not a pointer). */
            out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_isize);
            pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar);
            return 0;
          }
          if (!ast.ref_is_null(out_ar)) {
            pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar);
            return 0;
          }
          driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb);
          return -1;
        }
        driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb);
        return -1;
      }
      /*
       * wave286 Cap residual: hard-fail illegal float bitwise / mod / shift at typeck.
       * Root cause: f32/f64 promotion applied to ANY binop (incl. & | ^ << >> %) and
       * codegen emitted invalid C (`double a & b`) → soft residual BLD001 (host-cc).
       * Allowed on float: + - * / only (ADD/SUB/MUL/DIV). Rejected: MOD, SHL, SHR,
       * BITAND, BITOR, BITXOR with either operand f32/f64 (incl. float << int).
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + ast_pool infer twin same commit.
       */
      if (lko == ord_f32 || lko == ord_f64 || rko == ord_f32 || rko == ord_f64) {
        if (expr_kind == ord_mod || expr_kind == ord_shl || expr_kind == ord_shr
        || expr_kind == ord_bitand || expr_kind == ord_bitor || expr_kind == ord_bitxor) {
          let line_fb: i32 = pipeline_expr_line_at(arena, expr_ref);
          let col_fb: i32 = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_invalid_float_binop(line_fb, col_fb);
          return -1;
        }
      }
      /*
       * wave658 Cap residual: hard-fail aggregate + - * / % bitops/shifts at typeck.
       * Root cause: type_refs_equal fallthrough stamped out_ar = lt for struct/array/slice
       * → host-cc BLD001 (`invalid operands to binary expression`).
       * G.7 reuse typeck_type_is_aggregate_cmp_operand (wave657). VECTOR same-size pair
       * still allowed below (SIMD-style path). enum/alias/scalar/ptr paths unchanged.
       * PLATFORM: SHARED — seed typeck_gen + empty_surface + ast_pool twin same commit.
       */
      if ((typeck_type_is_aggregate_cmp_operand(module, arena, lt_ar) != 0
      || typeck_type_is_aggregate_cmp_operand(module, arena, rt_ar) != 0)
      && !(lko == ord_type_vector && rko == ord_type_vector)) {
        let line_aa: i32 = pipeline_expr_line_at(arena, expr_ref);
        let col_aa: i32 = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_aggregate_cmp(line_aa, col_aa);
        return -1;
      }
      if (ast.ref_is_null(out_ar)) {
        if ((lko == ord_i32 || lko == ord_u8 || lko == ord_u32 || lko == ord_u64 || lko == ord_i64
        || lko == ord_usize || lko == ord_isize)
        && (rko == ord_i32 || rko == ord_u8 || rko == ord_u32 || rko == ord_u64 || rko == ord_i64
        || rko == ord_usize || rko == ord_isize)) {
          if (expr_kind == ord_shl || expr_kind == ord_shr) {
            out_ar = lt_ar;
          } else if (expr_kind == ord_bitand || expr_kind == ord_bitor || expr_kind == ord_bitxor
          || expr_kind == ord_mod) {
            if (rk_expr == ord_lit && typeck_coerce_init_lit_to_decl(arena, bop_r, lt_ar, lko, rk_expr) != 0) {
              out_ar = lt_ar;
            } else if (lk_expr == ord_lit
            && typeck_coerce_init_lit_to_decl(arena, bop_l, rt_ar, rko, lk_expr) != 0) {
              out_ar = rt_ar;
            }
          }
        }
      }
      if (ast.ref_is_null(out_ar)) {
        if (lko == ord_type_vector && rko == ord_type_vector
        && pipeline_type_array_size_at(arena, lt_ar) == pipeline_type_array_size_at(arena, rt_ar)
        && type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_ar),
        pipeline_type_elem_ref_at(arena, rt_ar))) {
          out_ar = lt_ar;
        } else if (lko == ord_i64 || rko == ord_i64) {
          out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i64);
        } else if (lko == ord_f32
        && typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_ar, ord_f32, rk_expr) != 0) {
          /* wave317 Cap residual pure: f32 + bare FLOAT_LIT / `-float` stays f32.
           * Root: FLOAT_LIT defaults to f64 (typeck_check_expr_float_lit); wave296
           * usual-arith then widens f32+1.0 → f64 → assign/let `expected f32, found f64`.
           * G.7 reuse typeck_coerce_init_float_lit_to_decl (wave316 let/assign/return).
           * Must run before f64-before-f32 widen. True f32*f64 vars still widen below.
           * PLATFORM: SHARED — seed typeck_gen + empty_surface + ast_pool twin same commit. */
          out_ar = lt_ar;
        } else if (rko == ord_f32
        && typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_ar, ord_f32, lk_expr) != 0) {
          out_ar = rt_ar;
        } else if (lko == ord_f64 || rko == ord_f64) {
          /* wave296: usual arithmetic conversion — any f64 operand widens the binop to f64
           * (f32*f64 / f64*f32 must not resolve as f32; freestanding cast/mul need mulsd bits).
           * PLATFORM: SHARED — seed typeck_gen + empty_surface + ast_pool twin same commit. */
          out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f64);
        } else if (lko == ord_f32 || rko == ord_f32) {
          out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f32);
        } else if (type_refs_equal(arena, lt_ar, rt_ar)) {
          out_ar = lt_ar;
        } else if (typeck_integer_widen_ok_refs(arena, lt_ar, rt_ar)) {
          out_ar = lt_ar;
        } else if (typeck_integer_widen_ok_refs(arena, rt_ar, lt_ar)) {
          out_ar = rt_ar;
        } else if (lk_expr == ord_lit && rk_expr != ord_lit) {
          out_ar = rt_ar;
        } else if (rk_expr == ord_lit && lk_expr != ord_lit) {
          out_ar = lt_ar;
        } else if (!ast.ref_is_null(lt_ar)) {
          out_ar = lt_ar;
        } else if (!ast.ref_is_null(rt_ar)) {
          out_ar = rt_ar;
        }
      }
      if (expr_kind >= 4 && expr_kind <= 13) {
        allow_i32_fallback = 1;
      }
      if (ast.ref_is_null(out_ar) && lko != ord_type_vector && rko != ord_type_vector && allow_i32_fallback != 0) {
        out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i32);
      }
      /* wave677: bool→i32 arith promotion removed (hard-fail above). LANG-006 let/const only. */
      if (!ast.ref_is_null(out_ar)) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar);
      }
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_binop(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_eq: i32 = 14;
    let ord_ne: i32 = 15;
    let ord_lt: i32 = 16;
    let ord_le: i32 = 17;
    let ord_gt: i32 = 18;
    let ord_ge: i32 = 19;
    let ord_logand: i32 = 20;
    let ord_logor: i32 = 21;
    let expr_kind: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (expr_kind == ord_eq || expr_kind == ord_ne || expr_kind == ord_lt || expr_kind == ord_le
    || expr_kind == ord_gt || expr_kind == ord_ge || expr_kind == ord_logand || expr_kind == ord_logor) {
      return typeck_check_expr_binop_cmp(module, arena, expr_ref, return_type_ref, ctx);
    }
    return typeck_check_expr_binop_arith(module, arena, expr_ref, return_type_ref, ctx);
  }
}

/**
 * R2 (8.3.3): EXPR_FIELD_ACCESS typeck orchestrator.
 *
 * Migrated from C `pipeline_typeck_check_expr_field_access_c`
 * (pipeline_typeck_field_access.c) to .x authority. Public C surface
 * `pipeline_typeck_check_expr_field_access_c` remains a thin forwarder for
 * strict_glue / seed / OMIT_X_DUP product link order.
 *
 * Order (G.7 single orchestration path — do not open a parallel field typeck):
 *  1) prebind untyped VAR bases to TYPE_NAMED(name)
 *  2) import binding resolve (dep func / const / enum) — short-circuit on hit
 *  3) reverse-infer base expected for CALL/METHOD_CALL from unique field owner
 *  4) check_expr(base) — never pass field-result ambient as base expected
 *  5) SoA INDEX base path (arr[i].field)
 *  6) known_ptr (*ASTArena/*Module hard fields) + layout_named + slice
 *  7) name_fallback + lexer_fallback
 *  8) mono type-arg stamp + ambient free type-param fill
 *  9) unknown_hard_fail G.7 gate (typeck.x; C thin for strict_minimal)
 *
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param return_type_ref i32 — ambient expected of field result (0 if none)
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 hard fail
 * PLATFORM: SHARED — product field typeck authority.
 */
export function typeck_check_expr_field_access(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let base_ref: i32 = 0;
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let elem_ty: i32 = 0;
    let layout_rc: i32 = 0;
    let base_expected: i32 = 0;
    let base_kind: i32 = 0;
    /* EXPR_CALL=48 EXPR_METHOD_CALL=49 TYPE_PTR=9 */
    let ord_call: i32 = 48;
    let ord_method_call: i32 = 49;
    let ord_type_ptr: i32 = 9;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return -1;
    }
    base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref);
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return -1;
    }
    typeck_field_prebind(module, arena, expr_ref, ctx);
    /* Import binding special-case: backend.foo → dep func/const/enum. */
    if (typeck_field_import_binding(module, arena, expr_ref, base_ref, ctx) != 0) {
      return 0;
    }
    /*
     * wave454: do NOT pass field-result ambient (return_type_ref) into base.
     * For CALL/METHOD_CALL bases, reverse-infer unique owner struct from field
     * name so bare ret-only generics get the right expected.
     * STRUCT_LIT join (pin-seed array→slice lit path): anonymous
     * `{ xs: [10,32] }.xs` has no type name; reverse-infer unique layout so
     * base stamps TYPE_NAMED and field type is [N]T for array_to_slice_ok.
     * EXPR_STRUCT_LIT ord = 45. PLATFORM: SHARED.
     */
    base_expected = 0;
    base_kind = pipeline_expr_kind_ord_at(arena, base_ref);
    if (base_kind == ord_call || base_kind == ord_method_call || base_kind == 45) {
      base_expected = typeck_field_reverse_infer_base_type(module, arena, expr_ref,
      return_type_ref);
    }
    if (pipeline_typeck_check_expr_c(module, arena, base_ref, base_expected, ctx) != 0) {
      return -1;
    }
    /* DOD-S1: INDEX base SoA field access before AoS layout fallback. */
    if (typeck_soa_field_soa_index(module, arena, expr_ref, base_ref) != 0) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (!ast.ref_is_null(base_ty) && base_ty > 0 && base_ty <= arena.num_types) {
      bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
      if (bt_kind == ord_type_ptr) {
        elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
        if (!ast.ref_is_null(elem_ty)) {
          typeck_field_known_ptr(module, arena, expr_ref, base_ref,
          pipeline_module_num_struct_layouts_at(module));
        }
      }
      layout_rc = typeck_field_layout_named(module, arena, expr_ref, base_ref, ctx);
      if (layout_rc == 2) {
        /*
         * User enum variant (Method.GET): resolved to enum TYPE_NAMED.
         * wave472: do not mono/ambient — concrete, not type-param.
         */
        return 0;
      }
      typeck_field_slice(arena, expr_ref, base_ref);
    }
    typeck_field_name_fallback(arena, expr_ref, base_ref);
    typeck_field_lexer_fallback(module, arena, expr_ref, base_ref, ctx);
    typeck_field_apply_mono_type_arg(module, arena, expr_ref, base_ty);
    typeck_field_apply_ambient_for_type_param(module, arena, expr_ref, return_type_ref, ctx);
    /* wave674: hard-fail unresolved field on known base (G.7 single gate). */
    if (typeck_field_unknown_hard_fail(module, arena, expr_ref, base_ref, ctx) != 0) {
      return -1;
    }
    return 0;
  }
}

/**
 * Type-check unary NEG / BITNOT / LOGNOT.
 * @param module *Module — module under check
 * @param arena *ASTArena — AST arena
 * @param expr_ref i32 — unary expr ref
 * @param return_type_ref i32 — enclosing function return type (passed to operand)
 * @param ctx *PipelineDepCtx — dep/typeck context
 * @return i32 — 0 ok, -1 hard fail
 * wave289 Cap residual: hard-fail illegal unary ~ on float/ptr and unary - on ptr.
 * wave662 Cap residual: hard-fail unary -/~/! on aggregates (struct/array/slice).
 * wave665 Cap residual: hard-fail LOGNOT on non-bool (docs/04: logical requires bool).
 * wave667 Cap residual: hard-fail unary -/~ on void (void call result).
 * wave677 Cap residual: hard-fail unary -/~ on bool (no implicit bool→int).
 * Root cause (wave289): copied operand type without host-cc validity → BLD001 on
 * `~double`, `~uint8_t*`, `-uint8_t*`.
 * Root cause (wave662): LOGNOT always stamped bool; NEG/BITNOT stamped aggregate
 * type → host-cc BLD001 (`-struct`, `~struct`, `!slice`) without T001.
 * Root cause (wave665): LOGNOT still stamped bool for any non-aggregate scalar
 * (`!i32`, `!f32`) → C truthiness false green; if/while already require bool.
 * Root cause (wave677): unary -true stamped bool then host/fs treated as int
 * false green; ~true fell to return mismatch. G.7: invalid_bool_binop.
 * Allowed: ~int, -int, -float, !bool (LOGNOT→bool). Rejected: ~f32/f64, ~ptr,
 * -ptr, -bool, ~bool, aggregate -/~/!, and non-bool LOGNOT operands.
 * PLATFORM: SHARED — seed typeck_gen + empty_surface same commit (G.7).
 */
export function typeck_check_expr_unary(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_neg: i32 = 22;
    let ord_bitnot: i32 = 23;
    let ord_lognot: i32 = 24;
    let ord_ptr: i32 = 9;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let op_ref: i32 = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    let expr_kind: i32 = pipeline_expr_kind_ord_at(arena, expr_ref);
    let op_tr: i32 = 0;
    let bt: i32 = 0;
    let op_ko: i32 = 0;
    let line_u: i32 = 0;
    let col_u: i32 = 0;
    if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    op_tr = expr_type_ref(arena, op_ref);
    /*
     * wave662 Cap residual: hard-fail unary -/~/! on aggregates at typeck.
     * LOGNOT previously stamped bool for any operand (including struct/slice) → BLD001;
     * NEG/BITNOT stamped the aggregate type → BLD001 on host-C. G.7: reuse aggregate
     * helper from wave657/658; diag invalid_aggregate_cmp (message covers unary).
     */
    if (!ast.ref_is_null(op_tr) && op_tr > 0 && op_tr <= arena.num_types) {
      if (typeck_type_is_aggregate_cmp_operand(module, arena, op_tr) != 0) {
        line_u = pipeline_expr_line_at(arena, expr_ref);
        col_u = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_aggregate_cmp(line_u, col_u);
        return -1;
      }
    }
    if (expr_kind == ord_lognot) {
      /*
       * wave665 Cap residual: LOGNOT operand must be TYPE_BOOL (docs/04).
       * Soft: unknown/null op type not hard-failed. G.7: type_ref_is_bool +
       * driver_diagnostic_typeck_logical_operand_not_bool.
       */
      if (!ast.ref_is_null(op_tr) && op_tr > 0 && op_tr <= arena.num_types) {
        if (!type_ref_is_bool(arena, op_tr)) {
          line_u = pipeline_expr_line_at(arena, expr_ref);
          col_u = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_logical_operand_not_bool(line_u, col_u);
          return -1;
        }
      }
      bt = ensure_bool_type_ref(arena);
      if (bt != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt);
      }
      return 0;
    }
    if (!ast.ref_is_null(op_tr) && op_tr > 0 && op_tr <= arena.num_types) {
      op_ko = pipeline_type_kind_ord_at(arena, op_tr);
      /*
       * wave667 Cap residual: hard-fail unary -/~ on void at typeck.
       * Root cause: stamped op type for void call result → host-cc BLD001
       * `invalid argument type 'void' to unary expression`. LOGNOT already
       * rejected via wave665 non-bool. G.7: invalid_void_binop (same as arith).
       * PLATFORM: SHARED — seed typeck_gen + empty_surface same commit.
       */
      if ((expr_kind == ord_neg || expr_kind == ord_bitnot) && op_ko == 16) {
        line_u = pipeline_expr_line_at(arena, expr_ref);
        col_u = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_void_binop(line_u, col_u);
        return -1;
      }
      /*
       * wave677 Cap residual: hard-fail unary -/~ on bool at typeck.
       * Soft residual: -true / ~true typeck OK (stamp bool) → host/fs int false green
       * or late return mismatch. G.7: invalid_bool_binop (same as arith).
       * PLATFORM: SHARED — seed typeck_gen + empty_surface same commit.
       */
      if ((expr_kind == ord_neg || expr_kind == ord_bitnot) && op_ko == 1) {
        line_u = pipeline_expr_line_at(arena, expr_ref);
        col_u = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_bool_binop(line_u, col_u);
        return -1;
      }
      /* wave289: reject ~float, ~ptr, -ptr at typeck (reuse wave285/286 diags — G.7). */
      if (expr_kind == ord_bitnot) {
        if (op_ko == ord_f32 || op_ko == ord_f64) {
          line_u = pipeline_expr_line_at(arena, expr_ref);
          col_u = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_invalid_float_binop(line_u, col_u);
          return -1;
        }
        if (op_ko == ord_ptr) {
          line_u = pipeline_expr_line_at(arena, expr_ref);
          col_u = pipeline_expr_col_at(arena, expr_ref);
          driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u);
          return -1;
        }
      }
      if (expr_kind == ord_neg && op_ko == ord_ptr) {
        line_u = pipeline_expr_line_at(arena, expr_ref);
        col_u = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u);
        return -1;
      }
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, op_tr);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_addr_of(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let op_ref: i32 = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    let op_ty: i32 = 0;
    let pt: i32 = 0;
    /* See implementation. */
    if (!ast.ref_is_null(op_ref)) {
      if (pipeline_typeck_reject_addr_of_linear_c(arena, op_ref, expr_ref, module, ctx) != 0) {
        return - 1;
      }
      if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
        return - 1;
      }
    }
    op_ty = expr_type_ref(arena, op_ref);
    if (ast.ref_is_null(op_ty) || op_ty <= 0 || op_ty > arena.num_types) {
      return - 1;
    }
    /* See implementation. */
    pt = pipeline_typeck_ptr_for_addr_of_operand_c(arena, op_ref, op_ty, module, ctx);
    if (pt == 0) {
      pt = find_or_alloc_ptr_type_ref(arena, op_ty);
    }
    if (pt == 0) {
      return - 1;
    }
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, pt);
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_deref(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
/** See implementation for details. */
    if (pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) <= 0) {
      let line: i32 = pipeline_expr_line_at(arena, expr_ref);
      let col: i32 = pipeline_expr_col_at(arena, expr_ref);
      driver_diagnostic_typeck_deref_outside_unsafe(line, col);
      return -1;
    }
    let ord_ptr: i32 = 9;
    let op_ref: i32 = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    let op_ptr: i32 = 0;
    let elem_ty: i32 = 0;
    if (!ast.ref_is_null(op_ref)) {
      if (check_expr(module, arena, op_ref, return_type_ref, ctx) != 0) {
        return - 1;
      }
    }
    op_ptr = expr_type_ref(arena, op_ref);
    if (ast.ref_is_null(op_ptr) || op_ptr <= 0 || op_ptr > arena.num_types) {
      return - 1;
    }
    if (pipeline_type_kind_ord_at(arena, op_ptr) != ord_ptr) {
      return - 1;
    }
    elem_ty = pipeline_type_elem_ref_at(arena, op_ptr);
    if (ast.ref_is_null(elem_ty)) {
      return - 1;
    }
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty);
    return 0;
  }
}

/**
 * See implementation.
 * See implementation.
 */
export function typeck_check_expr_var_top_level(module: *Module, arena: *ASTArena, expr_ref: i32,
vbuf: *u8, vnlen: i32, tl: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let tl_tr: i32 = 0;
    if (tl >= module.num_top_level_lets) {
      return 0;
    }
    if (typeck_top_level_let_name_equal(module, tl, vbuf, vnlen)) {
      tl_tr = pipeline_module_top_level_let_type_ref(module, tl);
      if (!ast.ref_is_null(tl_tr)) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, tl_tr);
        return 1;
      }
    }
    return typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, tl + 1);
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_var(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let vnlen: i32 = 0;
    let vbuf: *u8 = typeck_scratch64_slot(0);
    let vd_tr: i32 = 0;
    let block_ref: i32 = 0;
    let func_ix: i32 = 0;
    let pr: i32 = 0;
    let tk_tr: i32 = 0;
    let tg_tr: i32 = 0;
    let nm_tok_kind: u8[9] = [84, 111, 107, 101, 110, 75, 105, 110, 100];
    let nm_typ_kind: u8[8] = [84, 121, 112, 101, 75, 105, 110, 100];
    if (arena == 0 as *ASTArena || module == 0 as *Module || ctx == 0 as *PipelineDepCtx
    || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    vnlen = pipeline_expr_var_name_len(arena, expr_ref);
    if (vnlen <= 0 || vnlen > 127) {
      return - 1;
    }
    pipeline_expr_var_name_into(arena, expr_ref, vbuf);
    block_ref = pipeline_dep_ctx_current_block_ref_at(ctx);
    driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx),
    block_ref, 99, pipeline_expr_resolved_type_ref(arena, expr_ref));
    if (block_ref != 0 && block_ref <= arena.num_blocks) {
      vd_tr = pipeline_block_resolve_var_type_ref(arena, block_ref, vbuf, vnlen);
      if (vd_tr != 0) {
        driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx),
        block_ref, 1, vd_tr);
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, vd_tr);
        if (pipeline_typeck_linear_use_var_c(arena, vd_tr, expr_ref, vbuf, vnlen) != 0) {
          return - 1;
        }
        return 0;
      }
    }
/** See implementation for details. */
    func_ix = pipeline_dep_ctx_current_func_index(ctx);
    if (func_ix >= 0 && func_ix < module.num_funcs) {
      pr = pipeline_module_func_param_type_ref_for_name(module, func_ix, vbuf, vnlen);
      if (pr != 0) {
        driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 2, pr);
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, pr);
        if (pipeline_typeck_linear_use_var_c(arena, pr, expr_ref, vbuf, vnlen) != 0) {
          return - 1;
        }
        return 0;
      }
    }
    driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx),
    block_ref, 100, pipeline_expr_resolved_type_ref(arena, expr_ref));
    if (module.num_top_level_lets > 0) {
      if (typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, 0) != 0) {
        driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx),
        block_ref, 101, pipeline_expr_resolved_type_ref(arena, expr_ref));
        return 0;
      }
    }
    driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx),
    block_ref, 102, pipeline_expr_resolved_type_ref(arena, expr_ref));
    driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 104,
    pipeline_expr_resolved_type_ref(arena, expr_ref));
    /* wave100 language residual: same-module function name as Cap-fn-ptr *u8.
     * PLATFORM: SHARED — product large-stack surfaces need bare fn as *u8
     * (g05 formerly held (uint8_t*)(void*)fn; .x could not form fn-pointer constants).
     * Locals/params/top-level lets already resolved above. CALL does not typecheck
     * the callee via this path (name-based resolve), so call sites stay unchanged.
     * First matching overload wins (C product surfaces are #[no_mangle] unique).
     * Cap-fn-ptr (10.3.2): mark is_used so asm WPO emit-order keeps the body
     * (address-taken has no call edge; same pattern as F7 vtable impl mark). */
    {
      let fi: i32 = 0;
      let nfuncs: i32 = module.num_funcs;
      while (fi < nfuncs) {
        if (pipeline_module_func_name_equal_at(module, fi, vbuf, vnlen) != 0) {
          let u8r: i32 = ensure_u8_type_ref(arena);
          let ptr_u8: i32 = 0;
          if (ast.ref_is_null(u8r)) {
            return -1;
          }
          ptr_u8 = find_or_alloc_ptr_type_ref(arena, u8r);
          if (ast.ref_is_null(ptr_u8) || ptr_u8 == 0) {
            return -1;
          }
          pipeline_module_func_set_is_used(module, fi, 1);
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_u8);
          driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 105, ptr_u8);
          return 0;
        }
        fi = fi + 1;
      }
    }
    if (vnlen == 9 && name_equal(vbuf, vnlen, &nm_tok_kind[0], 9)) {
      tk_tr = find_or_alloc_named_type_ref(arena, &nm_tok_kind[0], 9);
      if (tk_tr != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, tk_tr);
        return 0;
      }
    }
    if (vnlen == 8 && name_equal(vbuf, vnlen, &nm_typ_kind[0], 8)) {
      tg_tr = find_or_alloc_named_type_ref(arena, &nm_typ_kind[0], 8);
      if (tg_tr != 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, tg_tr);
        return 0;
      }
    }
    if (typeck_var_is_import_visible_name(module, vbuf, vnlen)) {
      return 0;
    }
    /* G.7: bare import-const reject — shared with C VAR path thin. */
    if (typeck_reject_bare_import_const(module, arena, expr_ref, ctx, vbuf, vnlen) != 0) {
      return -1;
    }
    /*
     * wave703 / match_struct_destructure: struct match field binds
     * (`Point { x, y } => x + y`) store patterns as wildcards; arm bodies
     * refer to field names as bare VARs. wave231/wave234: typeck_check_expr_match
     * sets match subject BSS before arms; product VAR hops subject field
     * types here via typeck_match_subject_field_type (pure leave).
     * PLATFORM: SHARED — G.7 single subject-field authority.
     */
    if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      let ft: i32 = typeck_match_subject_field_type(module, arena, vbuf, vnlen);
      if (ft > 0) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, ft);
        driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 106, ft);
        return 0;
      }
    }
    if (ast.ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return - 1;
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_method_call_arg(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, arg_i: i32, num_args: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let arg_ref: i32 = 0;
    if (arg_i >= num_args) {
      return 0;
    }
    arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i);
    if (check_expr(module, arena, arg_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    return typeck_check_expr_method_call_arg(module, arena, expr_ref, return_type_ref, ctx,
    arg_i + 1, num_args);
  }
}

/**
 * Resolve `x.method(...)` when `x` is a free type-param T and the enclosing
 * function declared `T: Trait` with Trait listing that method.
 *
 * Call-site `foo<A>` already hard-checks the impl (scan+check). The generic
 * body still saw T as a nameless TYPE_NAMED and LANG-004'd. G.7: consume the
 * skip_tl bound+trait tables via xlang_generic_bound_method_on_param_c.
 *
 * Return type: builtin kind → ensure_by_kind; NAMED Self or the type-param
 * name → receiver type_ref; other NAMED → find_or_alloc_named. Compound
 * PTR/SLICE/ARRAY ret is not formed this wave (leave resolved 0).
 * Resolve slots stay dep=-1 / func=-1 so mono C6 (not a random impl) picks
 * the concrete method.
 *
 * @param module *Module — current module (func name + free-T test)
 * @param arena *ASTArena
 * @param expr_ref i32 — METHOD_CALL
 * @param ctx *PipelineDepCtx — current_func_index
 * @param base_ty i32 — resolved receiver type
 * @param method_nm *u8 — method spelling
 * @param method_nlen i32
 * @param num_args i32 — extras
 * @return i32 — 1 resolved and stamped, 0 not this case
 * PLATFORM: SHARED typeck method_call bound step.
 */
export function typeck_method_call_resolve_generic_bound(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, base_ty: i32, method_nm: *u8, method_nlen: i32,
num_args: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let cfi: i32 = 0 - 1;
    let fn_len: i32 = 0;
    let tp_len: i32 = 0;
    let ret_kind: i32 = 0 - 1;
    let ret_nlen: i32 = 0;
    let ret_ty: i32 = 0;
    let hit: i32 = 0;
    let i: i32 = 0;
    let same: i32 = 0;
    let fn_nm: u8[128] = [];
    let tp_nm: u8[128] = [];
    let ret_nm: u8[64] = [];
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
        || expr_ref <= 0 || base_ty <= 0 || method_nm == 0 as *u8 || method_nlen <= 0) {
      return 0;
    }
    if (typeck_type_is_free_type_param(module, arena, base_ty) == 0) {
      return 0;
    }
    cfi = pipeline_dep_ctx_current_func_index(ctx);
    if (cfi < 0) {
      return 0;
    }
    if (pipeline_module_func_num_generic_params_at(module, cfi) <= 0) {
      return 0;
    }
    fn_len = pipeline_module_func_name_len_at(module, cfi);
    if (fn_len <= 0 || fn_len > 127) {
      return 0;
    }
    pipeline_module_func_name_copy64(module, cfi, &fn_nm[0]);
    tp_len = pipeline_type_named_name_into(arena, base_ty, &tp_nm[0]);
    if (tp_len <= 0 || tp_len > 127) {
      return 0;
    }
    ret_kind = 0 - 1;
    ret_nlen = 0;
    hit = xlang_generic_bound_method_on_param_c(&fn_nm[0], fn_len, &tp_nm[0], tp_len, method_nm,
    method_nlen, num_args, &ret_kind, &ret_nm[0], &ret_nlen);
    if (hit == 0) {
      return 0;
    }
    /* NAMED Self or the type-param name means "same as receiver". */
    if (ret_kind == 8 && ret_nlen > 0) {
      same = 0;
      if (ret_nlen == 4 && ret_nm[0] == 83 && ret_nm[1] == 101 && ret_nm[2] == 108
          && ret_nm[3] == 102) {
        same = 1;
      }
      if (same == 0 && ret_nlen == tp_len) {
        same = 1;
        i = 0;
        while (i < tp_len) {
          if (ret_nm[i] != tp_nm[i]) {
            same = 0;
            i = tp_len;
          } else {
            i = i + 1;
          }
        }
      }
      if (same != 0) {
        ret_ty = base_ty;
      } else {
        ret_ty = pipeline_type_find_or_alloc_named(arena, &ret_nm[0], ret_nlen);
      }
    } else if (ret_kind >= 0 && ret_kind != 8 && ret_kind != 9 && ret_kind != 10
        && ret_kind != 11 && ret_kind != 13) {
      ret_ty = pipeline_type_ensure_by_kind_ord(arena, ret_kind);
    } else {
      ret_ty = 0;
    }
    pipeline_expr_apply_call_resolve(arena, expr_ref, 0 - 1, 0 - 1);
    if (ret_ty > 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty);
    }
    return 1;
  }
}

/**
 * EXPR_METHOD_CALL typeck authority (wave253 pure leave).
 *
 * Order (must match product strict_minimal seed — G.7 single path):
 * 1) typecheck base + all method args
 * 2) import.binding.method via path-matched dep slot + W-heap overload (call_strict_minimal)
 *    with multi-dep fallback when path slot is empty. Overload pick coerces
 *    ARRAY_LIT extras to SIMD formals before score (Vec4f/Vec8i/i32x4). After
 *    resolve, typeck_check_call_arg_types (METHOD extras) T001s coerce/score miss
 *    — first_idx type-mismatch bind must not stay soft-green.
 * 3) generic method UFCS (pattern-unify self) BEFORE non-generic UFCS.
 *    Only n_gp>0; NAMED SIMD (i32x4) is not free T.
 * 4) same-module free-fn UFCS (exact / auto-ref *T / weak integer self).
 *    ARRAY_LIT receiver / extra args coerce to SIMD/VECTOR formals via
 *    typeck_coerce_init_array_vector_lit_to_decl before type_refs_equal
 *    (same stamp as CALL-arg / let `a: i32x4 = [1,2,3,4]`).
 *    ARRAY_LIT extras of NAMED elems (`[2]Pair` / `[]Pair`) also dest-stamp
 *    STRUCT_LIT elems via typeck_coerce_array_lit_struct_elems_to_decl;
 *    nameless `{ fields }` extras dest-stamp via
 *    typeck_coerce_init_struct_lit_to_decl (twin typeck_check_call_arg_types).
 *    Coerce 0 on ARRAY_LIT + SIMD formal (n_elems != lanes or elem type)
 *    refuses that candidate — same hard miss as CALL score T001, not
 *    LANG-004 "no impl" and not type_refs_equal fallback.
 * 5) generic-body bound method: receiver is free T, enclosing `fn<T: Trait>`
 *    lists Trait.method — stamp ret (Self / T → receiver type) and accept.
 *    func_ix stays -1; codegen C6 re-resolves the impl on the concrete type.
 * 6) associated Type.method(): VAR base is a struct-layout name, not a value
 *    (`P.mk()` / `P.id(7)` / `P.get(p)`). Same-module func with
 *    nparams == num_args (no implicit self). Instance `p.get()` stays step 4.
 * 7) bootstrap i32.double() when impl blocks skipped
 * 8) no-impl LANG-004 diagnostic
 *
 * Cap residual / strict_minimal faces thin → this function (dual-export ban).
 *
 * @param module *Module — entry module (imports + same-module free fns)
 * @param arena *ASTArena — caller expr/type arena
 * @param expr_ref i32 — METHOD_CALL expr
 * @param return_type_ref i32 — ambient expected return (overload tie-break; 0 if none)
 * @param ctx *PipelineDepCtx — dep modules for import.method
 * @return i32 — 0 ok, -1 typeck fail
 * PLATFORM: SHARED freestanding typeck method_call pure leave.
 */
export function typeck_check_expr_method_call(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_var: i32 = 3;
    let ord_i32: i32 = 0;
    let ord_ptr: i32 = 9;
    let ord_dyn: i32 = 17;
    let ord_import_binding: i32 = 1;
    let base_ref: i32 = 0;
    let base_rc: i32 = 0;
    let base_ty: i32 = 0;
    let base_kind: i32 = 0;
    let method_nlen: i32 = 0;
    let num_args: i32 = 0;
    let arg_i: i32 = 0;
    let ret_ty: i32 = 0;
    let dep_ix: i32 = 0 - 1;
    let dep_slot: i32 = 0 - 1;
    let func_ix: i32 = 0 - 1;
    let import_ret_ty: i32 = 0;
    let ii: i32 = 0;
    let n_imp: i32 = 0;
    let base_nlen: i32 = 0;
    let expect_store: i32 = 0;
    let method_nm: u8[128] = [];
    let base_nm: u8[128] = [];
    let dm: *Module = 0 as *Module;
    let msg: u8[256] = [];
    let p: i32 = 0;
    let z: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;

    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    pipeline_expr_init_call_resolve_at_ref(arena, expr_ref);
    base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref);
    base_rc = check_expr(module, arena, base_ref, 0, ctx);
    base_kind = pipeline_expr_kind_ord_at(arena, base_ref);
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    method_nlen = pipeline_expr_method_call_name_len(arena, expr_ref);
    if (method_nlen <= 0 || method_nlen > 127) {
      return 0 - 1;
    }
    pipeline_expr_method_call_name_into(arena, expr_ref, &method_nm[0]);

    /* Bootstrap: i32.double() when impl blocks are skipped. */
    ret_ty = 0;
    if (base_ty > 0 && pipeline_type_kind_ord_at(arena, base_ty) == ord_i32 && method_nlen == 6
        && method_nm[0] == 100 && method_nm[1] == 111 && method_nm[2] == 117
        && method_nm[3] == 98 && method_nm[4] == 108 && method_nm[5] == 101) {
      ret_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32);
    }

    /*
     * F3 TYPE_DYN(17) vtable dispatch: when the receiver is a `dyn Trait`
     * fat-ptr, resolve the method name to a vtable slot (trait declaration
     * order) and stamp the call as dyn-dispatch via the sentinel
     * call_resolved_dep_index = -2 (DYN_DISPATCH_DEP_SENTINEL) with
     * call_resolved_func_index = slot. Codegen reads this sentinel and emits
     * an indirect call through ((void**)recv.vtable)[slot].
     *
     * Return type is resolved from the trait registry's method_ret_kinds[slot]
     * so codegen can emit a typed function-pointer cast. Builtin return kinds
     * (i32/bool/u8/.../void) map directly via pipeline_type_ensure_by_kind_ord.
     * TYPE_ARRAY / TYPE_SLICE (`[N]T` / `[]T`) reconstruct via ret_elem_kind
     * + find_or_alloc_array/slice. TYPE_NAMED (`Pair`) reconstructs via
     * ret_name + find_or_alloc_named. TYPE_PTR-to-scalar (`*i32`) reconstructs
     * via ret_elem_kind + find_or_alloc_ptr. NAMED leaf of `*T` / `[]T` /
     * `[N]T` (`*Pair` / `[]Pair` / `[2]Pair`) reuses ret_name +
     * find_or_alloc_named then wrap ptr/slice/array. Sit-red host-C void-cast
     * (`struct Pair *p = (void)call` / `struct xlang_slice_Pair = (void)call`).
     * VECTOR kind 13 still falls back (leftover). `[K][N]T` ret wraps
     * leaf → inner dims → outer K via ret_array_ndims / ret_array_dim.
     *
     * Extras: visit with check_expr, then stamp FLOAT_LIT / `-float` to the
     * trait formal (f32=14 / f64=15), ARRAY_LIT extras to dest-SLICE
     * (`[]T`, kind=11) including NAMED leaf (`[]Pair`), ARRAY_LIT extras
     * to dest-ARRAY (`[N]T`, kind=10) including NAMED leaf (`[2]Pair`),
     * and STRUCT_LIT extras to dest-NAMED (`Pair`, kind=8). func_ix is
     * the vtable slot — must not call typeck_stamp_resolved_args_float_lit
     * (that looks up module-func params). Formal kinds come from
     * xlang_skip_trait_method_param_kind_c (registry already stored them
     * at parse). Extra i → param i+1 (self=0).
     * G.7 reuse typeck_coerce_init_float_lit_to_decl,
     * typeck_coerce_init_slice_from_array,
     * typeck_coerce_init_expr_to_decl (dest-SLICE-of-NAMED / dest-ARRAY),
     * and typeck_coerce_init_struct_lit_to_decl (no second stamp).
     * PLATFORM: SHARED — mirrors seeds/typeck_gen.linux.x86_64.c.
     */
    if (base_ty > 0 && pipeline_type_kind_ord_at(arena, base_ty) == ord_dyn) {
      let dyn_trait_nm: u8[64] = [];
      let dyn_trait_nlen: i32 = pipeline_type_named_name_into(arena, base_ty, &dyn_trait_nm[0]);
      if (dyn_trait_nlen > 0) {
        let dyn_slot: i32 = xlang_skip_trait_method_slot_c(&dyn_trait_nm[0], dyn_trait_nlen,
                &method_nm[0], method_nlen);
        if (dyn_slot < 0) {
          /* Method not declared in the trait -> typeck reject (compile fail). */
          return 0 - 1;
        }
        pipeline_expr_apply_call_resolve(arena, expr_ref, 0 - 2, dyn_slot);
        let dyn_ret_kind: i32 = xlang_skip_trait_method_ret_kind_c(&dyn_trait_nm[0],
                dyn_trait_nlen, dyn_slot);
        let dyn_ret_ty: i32 = 0;
        if (dyn_ret_kind >= 0 && dyn_ret_kind != 8 && dyn_ret_kind != 9
            && dyn_ret_kind != 10 && dyn_ret_kind != 11 && dyn_ret_kind != 13) {
          dyn_ret_ty = pipeline_type_ensure_by_kind_ord(arena, dyn_ret_kind);
        }
        /*
         * ARRAY/SLICE ret: F3 left dyn_ret_ty=0 so emit_type_kind(10/11)
         * failed (host-C XP003). Reconstruct with registry elem + existing
         * find_or_alloc_* (G.7 complete this block; no second resolve).
         * Scalar elem plus NAMED leaf (`[]Pair` / `[2]Pair`) plus
         * `[K][N]T` ndims. Remaining leftover: PTR/ARRAY/SLICE/VECTOR
         * elem of compounds.
         * PLATFORM: SHARED.
         */
        if (dyn_ret_ty == 0 && dyn_ret_kind == 11) {
          let dyn_rek: i32 = xlang_skip_trait_method_ret_elem_kind_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot);
          if (dyn_rek >= 0 && dyn_rek != 8 && dyn_rek != 9 && dyn_rek != 10
              && dyn_rek != 11 && dyn_rek != 13) {
            let dyn_ety: i32 = pipeline_type_ensure_by_kind_ord(arena, dyn_rek);
            if (dyn_ety > 0) {
              dyn_ret_ty = find_or_alloc_slice_type_ref(arena, dyn_ety);
            }
          }
          /*
           * SLICE-of-NAMED (`[]Pair`): registry ret_elem_kind=8 and
           * ret_name holds the leaf. Reconstruct named then wrap slice.
           * Sit-red host-C `struct xlang_slice_Pair = (void)call`.
           * G.7 complete this block; no second resolve. PLATFORM: SHARED.
           */
          if (dyn_ret_ty == 0 && dyn_rek == 8) {
            let dyn_sname: u8[64] = [];
            let dyn_slen: i32 = xlang_skip_trait_method_ret_name_into_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, &dyn_sname[0]);
            if (dyn_slen > 0) {
              let dyn_snty: i32 = find_or_alloc_named_type_ref(arena, &dyn_sname[0], dyn_slen);
              if (dyn_snty > 0) {
                dyn_ret_ty = find_or_alloc_slice_type_ref(arena, dyn_snty);
              }
            }
          }
        }
        if (dyn_ret_ty == 0 && dyn_ret_kind == 10) {
          let dyn_rek2: i32 = xlang_skip_trait_method_ret_elem_kind_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot);
          let dyn_rsz: i32 = xlang_skip_trait_method_ret_array_size_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot);
          let dyn_rnd: i32 = xlang_skip_trait_method_ret_array_ndims_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot);
          let dyn_leaf: i32 = 0;
          if (dyn_rek2 >= 0 && dyn_rek2 != 8 && dyn_rek2 != 9
              && dyn_rek2 != 10 && dyn_rek2 != 11 && dyn_rek2 != 13) {
            dyn_leaf = pipeline_type_ensure_by_kind_ord(arena, dyn_rek2);
          }
          /*
           * ARRAY-of-NAMED (`[2]Pair`): registry ret_elem_kind=8 and
           * ret_name holds the leaf. Reconstruct named then wrap array.
           * Sit-red host-C memcpy of `(void)call`. PLATFORM: SHARED.
           */
          if (dyn_leaf == 0 && dyn_rek2 == 8) {
            let dyn_aname: u8[64] = [];
            let dyn_alen: i32 = xlang_skip_trait_method_ret_name_into_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, &dyn_aname[0]);
            if (dyn_alen > 0) {
              dyn_leaf = find_or_alloc_named_type_ref(arena, &dyn_aname[0], dyn_alen);
            }
          }
          if (dyn_leaf > 0) {
            /*
             * `[K][N]T` ret: scanner stores ndims>=2 + dims[0]=outer K.
             * Sit-red XT001 expected [2][2]i32 found [2]i32 (outer-only).
             * Wrap innermost dim first. G.7 complete this block; no
             * second resolve. PLATFORM: SHARED.
             */
            if (dyn_rnd >= 2) {
              let dyn_di: i32 = dyn_rnd - 1;
              let dyn_cur: i32 = dyn_leaf;
              while (dyn_di >= 0 && dyn_cur > 0) {
                let dyn_dsz: i32 = xlang_skip_trait_method_ret_array_dim_c(&dyn_trait_nm[0],
                        dyn_trait_nlen, dyn_slot, dyn_di);
                if (dyn_dsz > 0) {
                  dyn_cur = find_or_alloc_array_type_ref(arena, dyn_cur, dyn_dsz);
                } else {
                  dyn_cur = 0;
                }
                dyn_di = dyn_di - 1;
              }
              dyn_ret_ty = dyn_cur;
            } else if (dyn_rsz > 0) {
              dyn_ret_ty = find_or_alloc_array_type_ref(arena, dyn_leaf, dyn_rsz);
            }
          }
        }
        /*
         * NAMED ret (`Pair`): F3 left dyn_ret_ty=0 so the call-site cast
         * was void (host-C `struct Pair r = (void)call`). Reconstruct with
         * registry ret name + existing find_or_alloc_named (G.7 complete
         * this block; no second resolve). PLATFORM: SHARED.
         */
        if (dyn_ret_ty == 0 && dyn_ret_kind == 8) {
          let dyn_rnm: u8[64] = [];
          let dyn_rnl: i32 = xlang_skip_trait_method_ret_name_into_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot, &dyn_rnm[0]);
          if (dyn_rnl > 0) {
            dyn_ret_ty = find_or_alloc_named_type_ref(arena, &dyn_rnm[0], dyn_rnl);
          }
        }
        /*
         * PTR-to-scalar ret (`*i32`): same void-cast leftover. Reconstruct
         * with ret_elem_kind + find_or_alloc_ptr. PTR-to-NAMED (`*Pair`)
         * uses ret_name + find_or_alloc_named then wrap ptr. PTR-to-ARRAY
         * (`*[2]i32`) reconstructs via ret_elem_elem_kind + elem_array
         * wrap then wrap ptr. Remaining leftover: PTR-to-PTR / SLICE /
         * VECTOR elem.
         * PLATFORM: SHARED.
         */
        if (dyn_ret_ty == 0 && dyn_ret_kind == 9) {
          let dyn_rek3: i32 = xlang_skip_trait_method_ret_elem_kind_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot);
          if (dyn_rek3 >= 0 && dyn_rek3 != 8 && dyn_rek3 != 9 && dyn_rek3 != 10
              && dyn_rek3 != 11 && dyn_rek3 != 13) {
            let dyn_ety3: i32 = pipeline_type_ensure_by_kind_ord(arena, dyn_rek3);
            if (dyn_ety3 > 0) {
              dyn_ret_ty = find_or_alloc_ptr_type_ref(arena, dyn_ety3);
            }
          }
          /*
           * PTR-to-NAMED (`*Pair`): registry ret_elem_kind=8; ret_name is
           * the leaf. Sit-red host-C `struct Pair *p = (void)call`.
           * G.7 complete this block; no second resolve. PLATFORM: SHARED.
           */
          if (dyn_ret_ty == 0 && dyn_rek3 == 8) {
            let dyn_pname: u8[64] = [];
            let dyn_plen: i32 = xlang_skip_trait_method_ret_name_into_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, &dyn_pname[0]);
            if (dyn_plen > 0) {
              let dyn_pnty: i32 = find_or_alloc_named_type_ref(arena, &dyn_pname[0], dyn_plen);
              if (dyn_pnty > 0) {
                dyn_ret_ty = find_or_alloc_ptr_type_ref(arena, dyn_pnty);
              }
            }
          }
          /*
           * PTR-to-ARRAY ret (`*[2]i32`): scalar PTR skips elem kind 10 so
           * the call-site cast was void (host-C `int32_t (*p)[2] =
           * (void)call`). Registry ret_elem_elem_kind + ret_elem_array
           * ndims/dims already hold the ARRAY leaf (`[2]i32`). G.7: wrap
           * ARRAY inner-first then wrap ptr (no second resolve). emit_type
           * peels PTR-to-ARRAY to first-element `E *` before a function
           * name; dest let still uses `E (*name)[N]`. NAMED leaf of
           * `*[N]Pair` is handled below via ret_name. PLATFORM: SHARED.
           */
          if (dyn_ret_ty == 0 && dyn_rek3 == 10) {
            let dyn_reek: i32 = xlang_skip_trait_method_ret_elem_elem_kind_c(
                    &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
            let dyn_ralf: i32 = 0;
            if (dyn_reek >= 0 && dyn_reek != 8 && dyn_reek != 9 && dyn_reek != 10
                && dyn_reek != 11 && dyn_reek != 13) {
              dyn_ralf = pipeline_type_ensure_by_kind_ord(arena, dyn_reek);
            }
            /*
             * dest ret PTR-to-ARRAY NAMED leaf (`*[2]Pair`): scalar
             * PTR-to-ARRAY skips elem_elem kind 8 so dyn_ret_ty stays 0
             * and the call-site is `(void(*)(void*))`. Ubuntu gcc then
             * rejects dest-cast of a void expression; mac clang
             * false-greens run=7. Registry ret_name already holds the
             * leaf (`Pair`) + ret_elem_array ndims/dims. G.7: wrap named
             * into dyn_ralf then the existing ARRAY wrap + wrap ptr (no
             * second dest-ret resolve). PLATFORM: SHARED.
             */
            if (dyn_ralf == 0 && dyn_reek == 8) {
              let dyn_ranm: u8[64] = [];
              let dyn_ranl: i32 = xlang_skip_trait_method_ret_name_into_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, &dyn_ranm[0]);
              if (dyn_ranl > 0) {
                dyn_ralf = find_or_alloc_named_type_ref(arena, &dyn_ranm[0], dyn_ranl);
              }
            }
            if (dyn_ralf > 0) {
              let dyn_rend: i32 = xlang_skip_trait_method_ret_elem_array_ndims_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
              let dyn_rew: i32 = dyn_ralf;
              if (dyn_rend >= 1) {
                /*
                 * dest extras dest-RET PTR-to-ARRAY extra empty `[]`
                 * `*[2][]T` AND dest extras dest-RET extra STAR
                 * `*[2]*T`: unused slot dims[ndims] extra SLICE wrap
                 * COUNT (1 = `*[2][]T`; 2 = `*[2][][]T`; 0 = no extra
                 * wrap = `*[2]i32`). Unused slot dims[ndims+1] extra
                 * PTR wrap COUNT (1 = `*[2]*T` / `*[2][]*T`; 0 = no
                 * extra PTR = `*[2]i32` / `*[2][]T`; `*[2][]*T` has
                 * both slots set). Wrap extra PTR of leaf extra times
                 * then extra SLICE then ARRAY inner-first then wrap
                 * ptr. Sit-red dest extras dest-RET wrap-once dest-
                 * stamps `*[2]i32` (typed let of `*[2]*i32` /
                 * `*[2][]i32` T001; INDEX of a live identity 139).
                 * `*[2]i32` (rpx/rex<=0) stays wrap-once. Twin of
                 * dest extras dest-ARRAY of PTR extra PTR-then-SLICE
                 * wraps. Do not invent -3. PLATFORM: SHARED. G.7:
                 * complete this wrap.
                 */
                let dyn_rpx: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_rend + 1);
                if (dyn_rpx > 0) {
                  let dyn_rpi: i32 = 0;
                  while (dyn_rpi < dyn_rpx && dyn_rew > 0) {
                    dyn_rew = find_or_alloc_ptr_type_ref(arena, dyn_rew);
                    dyn_rpi = dyn_rpi + 1;
                  }
                }
                let dyn_rex: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_rend);
                if (dyn_rex > 0) {
                  let dyn_rxi: i32 = 0;
                  while (dyn_rxi < dyn_rex && dyn_rew > 0) {
                    dyn_rew = find_or_alloc_slice_type_ref(arena, dyn_rew);
                    dyn_rxi = dyn_rxi + 1;
                  }
                }
                let dyn_rei: i32 = dyn_rend - 1;
                while (dyn_rei >= 0 && dyn_rew > 0) {
                  let dyn_red: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_rei);
                  if (dyn_red > 0) {
                    dyn_rew = find_or_alloc_array_type_ref(arena, dyn_rew, dyn_red);
                  } else {
                    dyn_rew = 0;
                  }
                  dyn_rei = dyn_rei - 1;
                }
              } else {
                dyn_rew = 0;
              }
              if (dyn_rew > 0) {
                dyn_ret_ty = find_or_alloc_ptr_type_ref(arena, dyn_rew);
              }
            }
          }
          /*
           * dest extras dest-RET extra STAR PTR-elem `**[2]*T` /
           * dest extras dest-RET of `**i32` / dest extras dest-RET
           * extra STAR PTR-elem ndims=0 `***T` / dest extras dest-RET
           * extra empty `[]` PTR-elem ndims=0 `**[]T`: scalar PTR
           * skips elem kind 9 so dyn_ret_ty stays 0 (typed let
           * `**[2]*i32` / `***i32` / `**[]i32` T001; Darwin dest-
           * stamp via the local = false green). Registry
           * ret_elem_elem_kind + ret_elem_array ndims/dims already
           * hold the PTR-elem leaf (`[2]*i32` extras / extra PTR of
           * `***T` / extra SLICE of `**[]T`). Unused slot dims[ndims]
           * extra SLICE wrap COUNT (1 = `**[2][]T`; 0 = no extra
           * wrap = `**[2]i32`). Unused slot dims[ndims+1] extra PTR
           * wrap COUNT (1 = `**[2]*T` / `**[2][]*T`; 0 = no extra
           * PTR = `**[2]i32` / `**[2][]T`; `**[2][]*T` has both
           * slots set). Unused slot dims[1] extra PTR wrap COUNT
           * when ndims=0 (1 = `***T`; 2 = `****T`; 0 = no extra PTR
           * = `**T`). Unused slot dims[0] extra SLICE wrap COUNT
           * when ndims=0 (1 = `**[]T`; 2 = `**[][]T`; 0 = no extra
           * SLICE = `**T` / `***T`; extra PTR stays dims[1]; both
           * slots = `**[]*T`). Wrap extra PTR of leaf extra times
           * then extra SLICE then ARRAY inner-first then wrap PTR
           * (elem) then wrap outer ptr. dest extras dest-RET extra
           * STAR PTR-elem ndims=0 wraps extra PTR of leaf extra
           * times then wrap PTR then wrap outer ptr (wrap rek3==9
           * previously skipped extra PTR when ndims=0 so dest-
           * stamped `**i32` — typed let `***i32` T001). dest extras
           * dest-RET extra empty `[]` PTR-elem ndims=0 wraps extra
           * PTR of leaf extra times then extra SLICE then wrap PTR
           * then wrap outer ptr (wrap rek3==9 previously skipped
           * extra SLICE when ndims=0 so dest-stamped `**i32` —
           * typed let `**[]i32` T001; dest-stamp via the local of
           * typed dest = false green even Ubuntu). `**i32` (ndims=0
           * extra PTR=0 extra SLICE=0) wraps PTR of leaf then wrap
           * outer ptr. Twin of dest extras dest-RET extra STAR
           * SLICE-elem ndims=0 wrap (wrap extra PTR then wrap SLICE
           * then wrap outer ptr; this wrap extra PTR then extra
           * SLICE then wrap PTR then wrap outer ptr). Discriminant
           * vs dest extras dest-RET extra STAR ARRAY-elem `*[2]*T`
           * is PTR vs ARRAY elem. Do not invent -3. PLATFORM:
           * SHARED. G.7: complete this wrap.
           */
          if (dyn_ret_ty == 0 && dyn_rek3 == 9) {
            let dyn_preek: i32 = xlang_skip_trait_method_ret_elem_elem_kind_c(
                    &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
            let dyn_pralf: i32 = 0;
            if (dyn_preek >= 0 && dyn_preek != 8 && dyn_preek != 9 && dyn_preek != 10
                && dyn_preek != 11 && dyn_preek != 13) {
              dyn_pralf = pipeline_type_ensure_by_kind_ord(arena, dyn_preek);
            }
            if (dyn_pralf == 0 && dyn_preek == 8) {
              let dyn_pranm: u8[64] = [];
              let dyn_pranl: i32 = xlang_skip_trait_method_ret_name_into_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, &dyn_pranm[0]);
              if (dyn_pranl > 0) {
                dyn_pralf = find_or_alloc_named_type_ref(arena, &dyn_pranm[0], dyn_pranl);
              }
            }
            if (dyn_pralf > 0) {
              let dyn_prend: i32 = xlang_skip_trait_method_ret_elem_array_ndims_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
              let dyn_prew: i32 = dyn_pralf;
              if (dyn_prend >= 1) {
                let dyn_prpx: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_prend + 1);
                if (dyn_prpx > 0) {
                  let dyn_prpi: i32 = 0;
                  while (dyn_prpi < dyn_prpx && dyn_prew > 0) {
                    dyn_prew = find_or_alloc_ptr_type_ref(arena, dyn_prew);
                    dyn_prpi = dyn_prpi + 1;
                  }
                }
                let dyn_prex: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_prend);
                if (dyn_prex > 0) {
                  let dyn_prxi: i32 = 0;
                  while (dyn_prxi < dyn_prex && dyn_prew > 0) {
                    dyn_prew = find_or_alloc_slice_type_ref(arena, dyn_prew);
                    dyn_prxi = dyn_prxi + 1;
                  }
                }
                let dyn_prei: i32 = dyn_prend - 1;
                while (dyn_prei >= 0 && dyn_prew > 0) {
                  let dyn_pred: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_prei);
                  if (dyn_pred > 0) {
                    dyn_prew = find_or_alloc_array_type_ref(arena, dyn_prew, dyn_pred);
                  } else {
                    dyn_prew = 0;
                  }
                  dyn_prei = dyn_prei - 1;
                }
              } else if (dyn_prend == 0) {
                /*
                 * dest extras dest-RET extra STAR PTR-elem ndims=0
                 * `***T` AND dest extras dest-RET extra empty `[]`
                 * PTR-elem ndims=0 `**[]T`: unused slot dims[1]
                 * extra PTR wrap COUNT (1 = `***T`; 2 = `****T`;
                 * 0 = no extra PTR = `**T`). Unused slot dims[0]
                 * extra SLICE wrap COUNT (1 = `**[]T`; 2 =
                 * `**[][]T`; 0 = no extra SLICE = `**T` / `***T`;
                 * both slots = `**[]*T`). Wrap extra PTR of leaf
                 * extra times then extra SLICE then wrap PTR then
                 * wrap outer ptr. Wrap rek3==9 previously skipped
                 * extra PTR/SLICE when ndims=0 so dest-stamped
                 * `**i32`. Twin of dest extras dest-RET extra STAR
                 * SLICE-elem ndims=0 wrap. Do not invent -3.
                 * PLATFORM: SHARED. G.7: complete this wrap.
                 */
                let dyn_prpx0: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, 1);
                if (dyn_prpx0 > 0) {
                  let dyn_prpi0: i32 = 0;
                  while (dyn_prpi0 < dyn_prpx0 && dyn_prew > 0) {
                    dyn_prew = find_or_alloc_ptr_type_ref(arena, dyn_prew);
                    dyn_prpi0 = dyn_prpi0 + 1;
                  }
                }
                let dyn_prex0: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, 0);
                if (dyn_prex0 > 0) {
                  let dyn_prxi0: i32 = 0;
                  while (dyn_prxi0 < dyn_prex0 && dyn_prew > 0) {
                    dyn_prew = find_or_alloc_slice_type_ref(arena, dyn_prew);
                    dyn_prxi0 = dyn_prxi0 + 1;
                  }
                }
              }
              if (dyn_prew > 0) {
                dyn_prew = find_or_alloc_ptr_type_ref(arena, dyn_prew);
              }
              if (dyn_prew > 0) {
                dyn_ret_ty = find_or_alloc_ptr_type_ref(arena, dyn_prew);
              }
            }
          }
          /*
           * dest extras dest-RET extra empty `[]` SLICE-elem
           * `*[][2][]T` / dest extras dest-RET of `*[]T`: scalar PTR
           * skips elem kind 11 so dyn_ret_ty stays 0 (typed let
           * dest-stamps via the local = false green; leftover skip
           * eek=-1 so impl `*[][2]i32` vs trait `*[][2][]i32`
           * compile=0). Registry ret_elem_elem_kind + ret_elem_array
           * ndims/dims already hold the SLICE-elem leaf (`[2][]i32`
           * extras). Unused slot dims[ndims] extra PTR wrap COUNT
           * (1 = `*[][2]*T`; 0 = no extra PTR = `*[][2]i32` /
           * `*[][2][]T`). Unused slot dims[ndims+1] extra SLICE wrap
           * COUNT (1 = `*[][2][]T` / `*[][2][]*T`; 0 = no extra wrap
           * = `*[][2]i32` / `*[][2]*T`; `*[][2][]*T` has both slots
           * set). Wrap extra PTR of leaf extra times then extra SLICE
           * then ARRAY inner-first then wrap SLICE (elem) then wrap
           * outer ptr. dest extras dest-RET extra STAR SLICE-elem
           * ndims=0 `*[]*T`: unused slot dims[0] extra PTR wrap COUNT
           * (1 = `*[]*T`; 2 = `*[]**T`; 0 = no extra PTR = `*[]i32`).
           * Wrap extra PTR of leaf extra times then wrap SLICE then
           * wrap outer ptr (wrap rek3==11 previously skipped extra
           * PTR when ndims=0 so dest-stamped `*[]i32` — typed let
           * `*[]*i32` T001; dest-stamp via the local of typed dest =
           * false green even Ubuntu). dest extras dest-RET extra STAR
           * SLICE-elem ndims=-2 `*[][]*T`: unused slot dims[1] extra
           * PTR wrap COUNT (1 = `*[][]*T`; 2 = `*[][]**T`; 0 = no
           * extra PTR = `*[][]T`). Extra SLICE wrap COUNT is dims[0]
           * (0 means 1 = `*[][]T`; 2 = `*[][][]T`). Wrap extra PTR
           * of leaf extra times then extra SLICE then wrap SLICE then
           * wrap outer ptr (wrap rek3==11 previously skipped extra
           * PTR/SLICE when ndims=-2 so dest-stamped `*[]i32` — typed
           * let `*[][]*i32` T001). `*[]T` (ndims=0 extra PTR=0)
           * wraps SLICE of leaf then wrap outer ptr. Twin of dest
           * extras dest-RET extra STAR PTR-elem wrap (wrap PTR of
           * elem then wrap outer ptr; this wrap SLICE of elem then
           * wrap outer ptr) and param extra STAR ndims=0 leftover
           * eand==0 extra PTR peels (`*[]*T` param already closed).
           * Discriminant vs dest extras dest-RET extra empty `[]`
           * ARRAY-elem `*[2][]T` / PTR-elem `**[2][]T` is SLICE vs
           * ARRAY vs PTR elem. Do not invent -3. PLATFORM: SHARED.
           * G.7: complete this wrap.
           */
          if (dyn_ret_ty == 0 && dyn_rek3 == 11) {
            let dyn_sreek: i32 = xlang_skip_trait_method_ret_elem_elem_kind_c(
                    &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
            let dyn_sralf: i32 = 0;
            if (dyn_sreek >= 0 && dyn_sreek != 8 && dyn_sreek != 9 && dyn_sreek != 10
                && dyn_sreek != 11 && dyn_sreek != 13) {
              dyn_sralf = pipeline_type_ensure_by_kind_ord(arena, dyn_sreek);
            }
            if (dyn_sralf == 0 && dyn_sreek == 8) {
              let dyn_sranm: u8[64] = [];
              let dyn_sranl: i32 = xlang_skip_trait_method_ret_name_into_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, &dyn_sranm[0]);
              if (dyn_sranl > 0) {
                dyn_sralf = find_or_alloc_named_type_ref(arena, &dyn_sranm[0], dyn_sranl);
              }
            }
            if (dyn_sralf > 0) {
              let dyn_srend: i32 = xlang_skip_trait_method_ret_elem_array_ndims_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot);
              let dyn_srew: i32 = dyn_sralf;
              if (dyn_srend == -2) {
                /*
                 * dest extras dest-RET extra STAR SLICE-elem
                 * ndims=-2 `*[][]*T`: unused slot dims[1] extra PTR
                 * wrap COUNT (1 = `*[][]*T`; 2 = `*[][]**T`; 0 =
                 * no extra PTR = `*[][]T`). Extra SLICE wrap COUNT
                 * is dims[0] (0 means 1 = `*[][]T`; 2 = `*[][][]T`).
                 * Wrap extra PTR of leaf extra times then extra
                 * SLICE then wrap SLICE then wrap outer ptr. Twin of
                 * param extra STAR `*[][]*T` wrap (param already
                 * closed). Wrap rek3==11 previously skipped extra
                 * PTR/SLICE when ndims=-2 so dest-stamped `*[]i32`.
                 * Do not invent -3. PLATFORM: SHARED. G.7: complete
                 * this wrap.
                 */
                let dyn_srpxm2: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, 1);
                if (dyn_srpxm2 > 0) {
                  let dyn_srpim2: i32 = 0;
                  while (dyn_srpim2 < dyn_srpxm2 && dyn_srew > 0) {
                    dyn_srew = find_or_alloc_ptr_type_ref(arena, dyn_srew);
                    dyn_srpim2 = dyn_srpim2 + 1;
                  }
                }
                let dyn_srexm2: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, 0);
                if (dyn_srexm2 < 1) {
                  dyn_srexm2 = 1;
                }
                let dyn_srxim2: i32 = 0;
                while (dyn_srxim2 < dyn_srexm2 && dyn_srew > 0) {
                  dyn_srew = find_or_alloc_slice_type_ref(arena, dyn_srew);
                  dyn_srxim2 = dyn_srxim2 + 1;
                }
              } else if (dyn_srend == 0) {
                let dyn_srpx0: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, 0);
                if (dyn_srpx0 > 0) {
                  let dyn_srpi0: i32 = 0;
                  while (dyn_srpi0 < dyn_srpx0 && dyn_srew > 0) {
                    dyn_srew = find_or_alloc_ptr_type_ref(arena, dyn_srew);
                    dyn_srpi0 = dyn_srpi0 + 1;
                  }
                }
              } else if (dyn_srend >= 1) {
                let dyn_srpx: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_srend);
                if (dyn_srpx > 0) {
                  let dyn_srpi: i32 = 0;
                  while (dyn_srpi < dyn_srpx && dyn_srew > 0) {
                    dyn_srew = find_or_alloc_ptr_type_ref(arena, dyn_srew);
                    dyn_srpi = dyn_srpi + 1;
                  }
                }
                let dyn_srex: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_srend + 1);
                if (dyn_srex > 0) {
                  let dyn_srxi: i32 = 0;
                  while (dyn_srxi < dyn_srex && dyn_srew > 0) {
                    dyn_srew = find_or_alloc_slice_type_ref(arena, dyn_srew);
                    dyn_srxi = dyn_srxi + 1;
                  }
                }
                let dyn_srei: i32 = dyn_srend - 1;
                while (dyn_srei >= 0 && dyn_srew > 0) {
                  let dyn_sred: i32 = xlang_skip_trait_method_ret_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, dyn_srei);
                  if (dyn_sred > 0) {
                    dyn_srew = find_or_alloc_array_type_ref(arena, dyn_srew, dyn_sred);
                  } else {
                    dyn_srew = 0;
                  }
                  dyn_srei = dyn_srei - 1;
                }
              }
              if (dyn_srew > 0) {
                dyn_srew = find_or_alloc_slice_type_ref(arena, dyn_srew);
              }
              if (dyn_srew > 0) {
                dyn_ret_ty = find_or_alloc_ptr_type_ref(arena, dyn_srew);
              }
            }
          }
        }
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, dyn_ret_ty);
        num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
        arg_i = 0;
        while (arg_i < num_args) {
          let dyn_arg: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i);
          if (check_expr(module, arena, dyn_arg, return_type_ref, ctx) != 0) {
            return 0 - 1;
          }
          /* Extra i maps to formal i+1 (param 0 is self). */
          let dyn_pk: i32 = xlang_skip_trait_method_param_kind_c(&dyn_trait_nm[0],
                  dyn_trait_nlen, dyn_slot, arg_i + 1);
          if (dyn_arg > 0 && (dyn_pk == 14 || dyn_pk == 15)) {
            let dyn_fty: i32 = pipeline_type_ensure_by_kind_ord(arena, dyn_pk);
            if (dyn_fty > 0) {
              let dyn_ak: i32 = pipeline_expr_kind_ord_at(arena, dyn_arg);
              typeck_coerce_init_float_lit_to_decl(arena, dyn_arg, dyn_fty, dyn_pk, dyn_ak);
            }
          }
          /*
           * dest-SLICE extra (`p: []i32`): ARRAY_LIT `[2, 4]` stays TYPE_ARRAY
           * after check_expr. Host-C emit_call_arg_slice_abi and asm
           * emit_expr_elf_for_call_args only wrap fat when resolved is
           * TYPE_SLICE (UFCS already stamps via the module-func formal).
           * Sit-red: dyn x.sums([2,4]) asm=1 / host-C=139; named local=7.
           * G.7: reuse typeck_coerce_init_slice_from_array. Scalar elem plus
           * NAMED leaf (`[]Pair`) plus ARRAY elem (`[][2]i32`) plus PTR
           * elem (`[]*i32`) plus PTR-to-ARRAY elem (`[]*[N]T`) plus SLICE
           * elem (`[][]i32`) plus PTR-to-SLICE elem (`[]*[]T`). Remaining
           * leftover: VECTOR / dest-SLICE of SLICE-of-SLICE (`[][][]T`).
           * PLATFORM: SHARED.
           */
          if (dyn_arg > 0 && dyn_pk == 11) {
            let dyn_eek: i32 = xlang_skip_trait_method_param_elem_kind_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, arg_i + 1);
            if (dyn_eek >= 0 && dyn_eek != 8 && dyn_eek != 9 && dyn_eek != 10
                && dyn_eek != 11 && dyn_eek != 13) {
              let dyn_ety: i32 = pipeline_type_ensure_by_kind_ord(arena, dyn_eek);
              if (dyn_ety > 0) {
                let dyn_sty: i32 = find_or_alloc_slice_type_ref(arena, dyn_ety);
                if (dyn_sty > 0) {
                  typeck_coerce_init_slice_from_array(arena, dyn_arg, dyn_sty, 11);
                }
              }
            }
            /*
             * dest-SLICE-of-NAMED extra (`p: []Pair`): ARRAY_LIT
             * `[{a:2,b:4}]` stays TYPE_ARRAY of nameless STRUCT_LIT.
             * Scalar dest-SLICE skips elem kind 8. Sit-red asm=139 /
             * host-C `(uint8_t[]){(struct )}`. Named local extra already 7.
             * Registry param_name already holds the leaf (`Pair`).
             * G.7: reconstruct via param_name + find_or_alloc_named then
             * wrap slice; reuse typeck_coerce_init_expr_to_decl so
             * dest-SLICE + STRUCT_LIT elems stamp together (no second
             * dest-SLICE / ARRAY_LIT / STRUCT_LIT stamp). PLATFORM: SHARED.
             */
            if (dyn_eek == 8) {
              let dyn_snm: u8[64] = [];
              let dyn_snl: i32 = xlang_skip_trait_method_param_name_into_c(&dyn_trait_nm[0],
                      dyn_trait_nlen, dyn_slot, arg_i + 1, &dyn_snm[0]);
              if (dyn_snl > 0) {
                let dyn_snty: i32 = find_or_alloc_named_type_ref(arena, &dyn_snm[0], dyn_snl);
                if (dyn_snty > 0) {
                  let dyn_ssty: i32 = find_or_alloc_slice_type_ref(arena, dyn_snty);
                  if (dyn_ssty > 0) {
                    typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_ssty);
                  }
                }
              }
            }
            /*
             * dest-SLICE-of-ARRAY extra (`p: [][2]i32` / `[][2][]i32` /
             * `[][2]*i32`): ARRAY_LIT `[[2, 4]]` / `[[[2], [4]]]` /
             * `[[&n, &m]]` stays TYPE_ARRAY of ARRAY or PTR. Scalar
             * dest-SLICE skips elem kind 10. Sit-red `[][2]i32` was
             * asm=1 / host-C=139. Sit-red `[][2][]i32` nested
             * ARRAY_LIT is 139 because wrap-once dest-stamps
             * `[][2]i32`. Sit-red `[][2]*i32` is T001 because extra
             * STAR after ARRAY never stored (eek unset; leftover PTR
             * vs eeek=-1). Named / UFCS / module-func of `[][2][]T`
             * already dest-stamp via the formal (6); named / UFCS of
             * `[][2]*T` share the T001 until store + extra PTR peel.
             * Skip-trait stores elem=ARRAY + eek=leaf + ndims=[N]
             * after `[]` then `[N]`; extra inner SLICE uses unused
             * dim slot dims[ndims] (1 = `[][2][]T`); extra inner PTR
             * uses unused slot dims[ndims+1] (1 = `[][2]*T`; ban -3).
             * G.7: wrap PTR of leaf extra times then extra SLICE
             * wraps then ARRAY wrap inner-first then wrap slice;
             * reuse typeck_coerce_init_expr_to_decl (no second
             * dest-SLICE stamp). NAMED leaf of `[][N]Pair` is handled
             * below via param_name. PLATFORM: SHARED.
             */
            if (dyn_eek == 10) {
              let dyn_saek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_salf: i32 = 0;
              if (dyn_saek >= 0 && dyn_saek != 8 && dyn_saek != 9 && dyn_saek != 10
                  && dyn_saek != 11 && dyn_saek != 13) {
                dyn_salf = pipeline_type_ensure_by_kind_ord(arena, dyn_saek);
              }
              /*
               * dest-SLICE-of-ARRAY NAMED leaf (`p: [][2]Pair`):
               * ARRAY_LIT `[[{a:2,b:4}]]` stays TYPE_ARRAY of nameless
               * STRUCT_LIT. Scalar dest-SLICE-of-ARRAY skips elem_elem
               * kind 8. Sit-red dyn extra asm=139 / host-C `(struct )`;
               * named local / UFCS already dest-stamp (asm 7). Registry
               * param_name already holds the leaf (`Pair`). G.7: wrap
               * named into dyn_salf then the existing ARRAY wrap + wrap
               * slice; reuse typeck_coerce_init_expr_to_decl (no second
               * dest-SLICE / ARRAY_LIT / STRUCT_LIT stamp). Host-C
               * BLD001 of `struct Pair (*data)[2]` before `struct Pair`
               * is a different produce (layout emit order).
               * PLATFORM: SHARED.
               */
              if (dyn_salf == 0 && dyn_saek == 8) {
                let dyn_sanm: u8[64] = [];
                let dyn_sanl: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_sanm[0]);
                if (dyn_sanl > 0) {
                  dyn_salf = find_or_alloc_named_type_ref(arena, &dyn_sanm[0], dyn_sanl);
                }
              }
              if (dyn_salf > 0) {
                let dyn_sand: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                let dyn_saw: i32 = dyn_salf;
                if (dyn_sand >= 1) {
                  /*
                   * dest extras dest-SLICE-of-ARRAY extra wraps
                   * (`[][2]*T` / `[][2][]T` / `[][2][][]T` /
                   * `[][2][]*T`): dim accessor returns extra PTR wrap
                   * count at dim_ix==ndims+1 and extra SLICE wrap
                   * count at dim_ix==ndims when unused slots >0. Wrap
                   * PTR of leaf extra times then extra SLICE wraps
                   * then ARRAY wrap then outer SLICE (`[][2][]*T` is
                   * wrap-both). `[][2]i32` (sapx/saex<=0) stays
                   * wrap-once. Do not invent -3. PLATFORM: SHARED.
                   */
                  let dyn_sapx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_sand + 1);
                  if (dyn_sapx > 0) {
                    let dyn_sapi: i32 = 0;
                    while (dyn_sapi < dyn_sapx && dyn_saw > 0) {
                      dyn_saw = find_or_alloc_ptr_type_ref(arena, dyn_saw);
                      dyn_sapi = dyn_sapi + 1;
                    }
                  }
                  let dyn_saex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_sand);
                  if (dyn_saex > 0) {
                    let dyn_saxi: i32 = 0;
                    while (dyn_saxi < dyn_saex && dyn_saw > 0) {
                      dyn_saw = find_or_alloc_slice_type_ref(arena, dyn_saw);
                      dyn_saxi = dyn_saxi + 1;
                    }
                  }
                  let dyn_sai: i32 = dyn_sand - 1;
                  while (dyn_sai >= 0 && dyn_saw > 0) {
                    let dyn_sad: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, dyn_sai);
                    if (dyn_sad > 0) {
                      dyn_saw = find_or_alloc_array_type_ref(arena, dyn_saw, dyn_sad);
                    } else {
                      dyn_saw = 0;
                    }
                    dyn_sai = dyn_sai - 1;
                  }
                } else {
                  dyn_saw = 0;
                }
                if (dyn_saw > 0) {
                  let dyn_sasty: i32 = find_or_alloc_slice_type_ref(arena, dyn_saw);
                  if (dyn_sasty > 0) {
                    typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_sasty);
                  }
                }
              }
            }
            /*
             * dest-SLICE-of-PTR extra (`p: []*i32`): ARRAY_LIT `[&n, &m]`
             * stays TYPE_ARRAY of PTR. Scalar dest-SLICE skips elem kind 9.
             * Sit-red host-C run=133 (`(int32_t *[]){&n,&m}` into a fat
             * slice*); UFCS / named local already dest-stamp (host-C 7).
             * Skip-trait now stores elem_kind=PTR + elem_elem_kind=leaf
             * after `[]` then STAR. G.7: wrap ptr of leaf then wrap slice;
             * reuse typeck_coerce_init_expr_to_decl (no second dest-SLICE
             * stamp). NAMED leaf of `[]*Pair` is handled below via
             * param_name. dest-ARRAY extra `[2]*Pair` already dest-stamps
             * via ADDR_OF elems (host-C/asm 7 without kind-9 reconstruct).
             * PLATFORM: SHARED.
             */
            if (dyn_eek == 9) {
              let dyn_spek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_splf: i32 = 0;
              if (dyn_spek >= 0 && dyn_spek != 8 && dyn_spek != 9 && dyn_spek != 10
                  && dyn_spek != 11 && dyn_spek != 13) {
                dyn_splf = pipeline_type_ensure_by_kind_ord(arena, dyn_spek);
              }
              /*
               * dest-SLICE-of-PTR NAMED leaf (`p: []*Pair`): ARRAY_LIT
               * `[&n]` stays TYPE_ARRAY of PTR (no dest-SLICE stamp).
               * Scalar dest-SLICE-of-PTR skips elem_elem kind 8. Sit-red
               * dyn extra asm=139 / host-C `(struct Pair *[]){&n}` into
               * wrapper `struct xlang_slice_Pair_p *` (panic: 0). Named
               * local / UFCS already dest-stamp (7). Registry param_name
               * already holds the leaf (`Pair`). G.7: wrap named into
               * dyn_splf then the existing wrap ptr + wrap slice; reuse
               * typeck_coerce_init_expr_to_decl (no second dest-SLICE /
               * PTR stamp). PLATFORM: SHARED.
               */
              if (dyn_splf == 0 && dyn_spek == 8) {
                let dyn_spnm: u8[64] = [];
                let dyn_spnl: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_spnm[0]);
                if (dyn_spnl > 0) {
                  dyn_splf = find_or_alloc_named_type_ref(arena, &dyn_spnm[0], dyn_spnl);
                }
              }
              /*
               * dest-SLICE-of-PTR ARRAY leaf (`p: []*[2]i32` /
               * `[]*[2][]i32`): skip-trait after `[]*` then `[` stores
               * eek=leaf + elem_array_ndims (elem_kind stays PTR).
               * Scalar dest-SLICE-of-PTR wrapped ptr-of-leaf so dest
               * was `[]*i32` (typeck expected *i32, found *[2]i32).
               * Extra empty `[]` after `[]*[N]` used to set
               * elem_kind=-1 (dest extras skipped → ADDR_OF of
               * `[2][]i32` run=1 panic). Extra SLICE wrap COUNT lives
               * in unused slot dims[ndims] (1 = `[]*[2][]T`; 0 = no
               * extra wrap = `[]*[2]i32`; ban -3). Extra PTR wrap
               * COUNT lives in unused slot dims[ndims+1]
               * (1 = `[]*[2]*T` / `[]*[2][]*T`; 0 = no extra PTR =
               * `[]*[2]i32` / `[]*[2][]T`). Extra STAR after
               * `[]*[N]` used to want_param_ty=0 then wave434 lift
               * kind=ARRAY (named / extra T001 leftover SLICE vs
               * ARRAY). Named extra dest-stamps via the formal once
               * store keeps PTR; host-C BLD001 of `int32_t *` /
               * `xlang_arr2_int32_t` is the emit twin (layout +
               * ARRAY_LIT). G.7: wrap extra PTR of leaf extra times
               * then extra SLICE of leaf then ARRAY via
               * elem_array_ndims then the existing wrap ptr + wrap
               * slice (no second dest-SLICE stamp). ndims==0 keeps
               * ptr-of-leaf (`[]*i32`).
               * dest-SLICE-of-PTR SLICE leaf (`p: []*[]i32` /
               * `[]*[][]i32`): skip-trait after `[]*` then `[` then `]`
               * used to set elem_kind=-1 (wave434 3-layer defer). Scanner
               * now keeps elem=PTR + eek=leaf + ndims=-2 (SLICE pointee;
               * extra wrap count in dims[0]: 0 means 1 = `[]*[]T`; 2 =
               * `[]*[][]T`). Named / UFCS already dest-stamp via the
               * formal (7); dyn `[]*[][]T` sit-red run=1 (panic: 0) when
               * dest extras wrapped SLICE of leaf once. G.7: wrap SLICE
               * extra times then the existing wrap ptr + wrap slice (no
               * second dest-SLICE stamp; do not invent -3).
               * PLATFORM: SHARED.
               */
              if (dyn_splf > 0) {
                let dyn_spand: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                let dyn_spaw: i32 = dyn_splf;
                if (dyn_spand == -2) {
                  let dyn_spex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                  if (dyn_spex < 1) {
                    dyn_spex = 1;
                  }
                  let dyn_spi: i32 = 0;
                  while (dyn_spi < dyn_spex && dyn_spaw > 0) {
                    dyn_spaw = find_or_alloc_slice_type_ref(arena, dyn_spaw);
                    dyn_spi = dyn_spi + 1;
                  }
                } else if (dyn_spand >= 1) {
                  /*
                   * dest extras dest-SLICE-of-PTR extra wraps
                   * (`[]*[2][]T` / `[]*[2][][]T` / `[]*[2]*T` /
                   * `[]*[2][]*T`): dim accessor returns extra PTR
                   * wrap count at dim_ix==ndims+1 and extra SLICE
                   * wrap count at dim_ix==ndims when unused slots
                   * >0. Wrap PTR of leaf extra times then extra
                   * SLICE wraps THEN ARRAY wrap then wrap PTR then
                   * outer SLICE (`[]*[2][]*T` is wrap-both).
                   * `[]*[2]i32` (sppx/spex<=0) stays wrap-once.
                   * Discriminant vs dest extras dest-SLICE-of-ARRAY
                   * extra `[][2]*T` / `[][2][]T` is elem_kind
                   * (PTR vs ARRAY); same unused slots. Do not
                   * invent -3. PLATFORM: SHARED.
                   */
                  let dyn_sppx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_spand + 1);
                  if (dyn_sppx > 0) {
                    let dyn_sppi: i32 = 0;
                    while (dyn_sppi < dyn_sppx && dyn_spaw > 0) {
                      dyn_spaw = find_or_alloc_ptr_type_ref(arena, dyn_spaw);
                      dyn_sppi = dyn_sppi + 1;
                    }
                  }
                  let dyn_spex2: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_spand);
                  if (dyn_spex2 > 0) {
                    let dyn_spi2: i32 = 0;
                    while (dyn_spi2 < dyn_spex2 && dyn_spaw > 0) {
                      dyn_spaw = find_or_alloc_slice_type_ref(arena, dyn_spaw);
                      dyn_spi2 = dyn_spi2 + 1;
                    }
                  }
                  let dyn_spai: i32 = dyn_spand - 1;
                  while (dyn_spai >= 0 && dyn_spaw > 0) {
                    let dyn_spad: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_spai);
                    if (dyn_spad > 0) {
                      dyn_spaw = find_or_alloc_array_type_ref(arena, dyn_spaw, dyn_spad);
                    } else {
                      dyn_spaw = 0;
                    }
                    dyn_spai = dyn_spai - 1;
                  }
                }
                if (dyn_spaw > 0) {
                  let dyn_spty: i32 = find_or_alloc_ptr_type_ref(arena, dyn_spaw);
                  if (dyn_spty > 0) {
                    let dyn_spsty: i32 = find_or_alloc_slice_type_ref(arena, dyn_spty);
                    if (dyn_spsty > 0) {
                      typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_spsty);
                    }
                  }
                }
              }
            }
            /*
             * dest-SLICE-of-SLICE extra (`p: [][]i32` / `[][][]i32` /
             * `[][][][]i32` / `[][]*i32` / `[][][]*i32` /
             * `[][][2][]i32`): ARRAY_LIT stays TYPE_ARRAY of ARRAY.
             * Scalar dest-SLICE skips elem kind 11. Sit-red 4-layer
             * dyn/named T001 (impl-match extra peel once while
             * pipeline still has a SLICE); 3-layer dyn extra was
             * INDEX 139. Sit-red `[][]*i32` nested ARRAY_LIT
             * `[[&n, &m]]` is 139 because wrap-once dest-stamps
             * `[][]i32` not `[][]*i32`. Sit-red `[][][]*i32` nested
             * `[[[&n, &m]]]` is 139 because extra STAR after
             * `[][][]` set elem_kind=-1 (dest extras skipped; named /
             * UFCS dest-stamp via the formal 7; store-only capturing
             * leaf is T001 leftover PTR vs eeek=leaf). Sit-red
             * `[][][2][]i32` nested ARRAY_LIT `[[[[2], [4]]]]` is
             * compile=0 run=1 (panic: 0) because extra empty `[]`
             * after `[][][M]` set elem_kind=-1 so dest extras skipped
             * (extra stayed `int32_t[][1][2][1]`; named / UFCS dest-
             * stamp via the formal 7). Extra SLICE wrap when
             * ndims>=1 lives in unused slot dims[ndims+1] (1 =
             * `[][][2][]T`; 2 = `[][][2][][]T`; 0 = no extra wrap =
             * `[][][2]T`; extra PTR of `[][][2]*T` stays
             * dims[ndims] — do not reopen). Skip-trait stores
             * elem_kind=SLICE + elem_elem_kind=leaf after `[]`
             * then `[]`; extra inner SLICE uses ndims=-2 with wrap
             * count in dims[0] (0 means 1 = 3-layer; 2 = 4-layer);
             * extra inner PTR uses unused slot dims[0] with ndims
             * staying 0 (1 = `[][]*T`) or unused slot dims[1] when
             * ndims==-2 (1 = `[][][]*T`; 0 = no extra PTR =
             * `[][][]T`; ban -3). G.7: wrap PTR of leaf extra times
             * then extra SLICE wraps at dim_ix==ndims+1 then wrap
             * ARRAY inner-first then wrap slice of that then wrap
             * slice; ndims==-2 wraps extra times; reuse
             * typeck_coerce_init_expr_to_decl (no second dest-SLICE
             * stamp). NAMED leaf of `[][]Pair` is handled below via
             * param_name. dest-SLICE-of-PTR ARRAY / SLICE leaf
             * (`[]*[N]T` / `[]*[]T` / `[]*[][]T`) are handled above
             * via elem_array_ndims (eek is the leaf, not 10 / 11).
             * Do not invent -3. PLATFORM: SHARED.
             */
            if (dyn_eek == 11) {
              let dyn_ssek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_sslf: i32 = 0;
              if (dyn_ssek >= 0 && dyn_ssek != 8 && dyn_ssek != 9 && dyn_ssek != 10
                  && dyn_ssek != 11 && dyn_ssek != 13) {
                dyn_sslf = pipeline_type_ensure_by_kind_ord(arena, dyn_ssek);
              }
              /*
               * dest-SLICE-of-SLICE NAMED leaf (`p: [][]Pair`): ARRAY_LIT
               * `[[{a:2,b:4}]]` stays TYPE_ARRAY of nameless STRUCT_LIT.
               * Scalar dest-SLICE-of-SLICE skips elem_elem kind 8. Sit-red
               * dyn extra asm=139 / host-C `(uint8_t[]){(uint8_t[]){(struct )}}`.
               * Registry param_name already holds the leaf (`Pair`). G.7:
               * wrap named into dyn_sslf then the existing wrap slice +
               * wrap slice; reuse typeck_coerce_init_expr_to_decl (no
               * second dest-SLICE / STRUCT_LIT stamp). PLATFORM: SHARED.
               */
              if (dyn_sslf == 0 && dyn_ssek == 8) {
                let dyn_ssnm: u8[64] = [];
                let dyn_ssnl: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_ssnm[0]);
                if (dyn_ssnl > 0) {
                  dyn_sslf = find_or_alloc_named_type_ref(arena, &dyn_ssnm[0], dyn_ssnl);
                }
              }
              if (dyn_sslf > 0) {
                let dyn_ssaw: i32 = dyn_sslf;
                let dyn_ssand: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                /*
                 * dest extras dest-SLICE-of-SLICE extra PTR wraps
                 * (`[][]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix=0 when ndims==0. Wrap PTR of leaf
                 * extra times then wrap SLICE twice. `[][]i32`
                 * (sspx<=0) stays wrap-once. Twin of dest extras
                 * dest-ARRAY-of-SLICE extra PTR wraps. Do not invent
                 * -3. PLATFORM: SHARED.
                 */
                if (dyn_ssand == 0) {
                  let dyn_sspx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                  if (dyn_sspx > 0) {
                    let dyn_sspi: i32 = 0;
                    while (dyn_sspi < dyn_sspx && dyn_ssaw > 0) {
                      dyn_ssaw = find_or_alloc_ptr_type_ref(arena, dyn_ssaw);
                      dyn_sspi = dyn_sspi + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-SLICE-of-SLICE extra PTR wraps
                 * (`[][][]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix=1 when ndims==-2 (dims[0] is extra
                 * SLICE). Wrap PTR of leaf extra times then wrap
                 * SLICE twice then extra SLICE wraps. `[][][]i32`
                 * (sspx<=0) stays extra-SLICE-only. Outer SLICE so
                 * `[2][][]*T` stays deferred. Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_ssand == -2) {
                  let dyn_sspx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 1);
                  if (dyn_sspx > 0) {
                    let dyn_sspi: i32 = 0;
                    while (dyn_sspi < dyn_sspx && dyn_ssaw > 0) {
                      dyn_ssaw = find_or_alloc_ptr_type_ref(arena, dyn_ssaw);
                      dyn_sspi = dyn_sspi + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-SLICE-of-SLICE extra PTR wraps
                 * (`[][][2]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix==ndims when ndims>=1 (unused slot
                 * after inner ARRAY dims). Wrap PTR of leaf extra
                 * times then wrap ARRAY inner-first then wrap SLICE
                 * twice. `[][][2]i32` (sspx3<=0) stays extra-ARRAY-
                 * only. Twin of dest extras dest-ARRAY-of-SLICE extra
                 * PTR wraps (`[2][][2]*T`; same unused-slot encoding;
                 * discriminant is SLICE vs ARRAY outer). Store extra
                 * STAR ARRAY-or-SLICE already complete. Impl-match
                 * leftover PTR vs eeek=leaf after extra ARRAY peels
                 * is T001 until extra PTR peels. Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_ssand >= 1) {
                  let dyn_sspx3: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_ssand);
                  if (dyn_sspx3 > 0) {
                    let dyn_sspi3: i32 = 0;
                    while (dyn_sspi3 < dyn_sspx3 && dyn_ssaw > 0) {
                      dyn_ssaw = find_or_alloc_ptr_type_ref(arena, dyn_ssaw);
                      dyn_sspi3 = dyn_sspi3 + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-SLICE-of-SLICE extra wrap
                 * (`[][][2][]T` / `[][][2][][]T`): dim accessor
                 * returns extra SLICE wrap count at dim_ix==ndims+1
                 * when ndims>=1 (unused slot after extra PTR at
                 * dims[ndims]). Wrap extra SLICE of leaf extra
                 * times then wrap ARRAY inner-first then wrap
                 * SLICE twice. `[][][2]i32` (ssex3<=0) stays extra-
                 * ARRAY-only. Twin of dest extras dest-ARRAY-of-
                 * SLICE extra wrap (`[2][][2][]T`; extra SLICE
                 * there is also dims[ndims+1]; discriminant is
                 * SLICE vs ARRAY outer). Extra PTR of `[][][2]*T`
                 * stays dims[ndims] — do not reopen. Named / UFCS
                 * dest-stamp via the formal 7; extra compile=0
                 * run=1 (panic) is dest extras skipped. Store-
                 * only without impl-match extra SLICE peels is
                 * T001 leftover SLICE vs eeek=leaf after extra
                 * ARRAY peels. Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_ssand >= 1) {
                  let dyn_ssex3: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_ssand + 1);
                  if (dyn_ssex3 > 0) {
                    let dyn_ssxi3: i32 = 0;
                    while (dyn_ssxi3 < dyn_ssex3 && dyn_ssaw > 0) {
                      dyn_ssaw = find_or_alloc_slice_type_ref(arena, dyn_ssaw);
                      dyn_ssxi3 = dyn_ssxi3 + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-SLICE-of-SLICE extra ARRAY wraps
                 * (`[][][2]T`): dim accessor returns inner ARRAY
                 * dims at 0..ndims-1 when ndims>=1 (wave437 store
                 * after `[][]` then `[M]`). Wrap ARRAY of leaf
                 * inner-first then wrap SLICE twice. `[][]i32`
                 * (ndims==0) stays wrap-once. Twin of dest extras
                 * dest-ARRAY-of-SLICE extra ARRAY wraps. Store
                 * already has ndims>=1 (named / UFCS dest-stamp
                 * via the formal 7). Impl-match leftover ARRAY
                 * vs eeek=leaf is T001 until extra ARRAY peels.
                 * Do not invent -3. PLATFORM: SHARED.
                 */
                if (dyn_ssand >= 1) {
                  let dyn_ssai: i32 = dyn_ssand - 1;
                  while (dyn_ssai >= 0 && dyn_ssaw > 0) {
                    let dyn_ssad: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_ssai);
                    if (dyn_ssad > 0) {
                      dyn_ssaw = find_or_alloc_array_type_ref(arena, dyn_ssaw, dyn_ssad);
                    } else {
                      dyn_ssaw = 0;
                    }
                    dyn_ssai = dyn_ssai - 1;
                  }
                }
                let dyn_ssity: i32 = find_or_alloc_slice_type_ref(arena, dyn_ssaw);
                if (dyn_ssity > 0) {
                  let dyn_ssoty: i32 = find_or_alloc_slice_type_ref(arena, dyn_ssity);
                  if (dyn_ssoty > 0) {
                    /*
                     * dest-SLICE extra `[][][]T` / `[][][][]T`: skip-trait
                     * after `[][]` then `[` then `]` used to set
                     * elem_kind=-1 (wave434 3-layer defer). Scanner now
                     * keeps elem=SLICE + eek=leaf + ndims=-2 (extra inner
                     * SLICE; same sentinel as `[]*[]T` — discriminant is
                     * elem_kind). Extra wrap count is dims[0] (0 means 1
                     * = 3-layer; 2 = 4-layer). Two wraps dest-stamp
                     * `[][]T`; ndims==-2 wraps extra times. Named /
                     * UFCS dest-stamp via the formal once impl-match
                     * walks extra peels. Do not invent -3. G.7: complete
                     * dest-SLICE-of-SLICE reconstruct (no second
                     * dest-SLICE stamp). PLATFORM: SHARED.
                     */
                    let dyn_ssdest: i32 = dyn_ssoty;
                    if (dyn_ssand == -2) {
                      let dyn_ssex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                              &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                      if (dyn_ssex < 1) {
                        dyn_ssex = 1;
                      }
                      let dyn_ssi: i32 = 0;
                      while (dyn_ssi < dyn_ssex && dyn_ssdest > 0) {
                        dyn_ssdest = find_or_alloc_slice_type_ref(arena, dyn_ssdest);
                        dyn_ssi = dyn_ssi + 1;
                      }
                    }
                    if (dyn_ssdest > 0) {
                      typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_ssdest);
                    }
                  }
                }
              }
            }
          }
          /*
           * dest-NAMED extra (`p: Pair`): anonymous STRUCT_LIT `{a:2,b:4}`
           * stays nameless after check_expr. Host-C STRUCT_LIT emit uses
           * struct_lit_struct_name → `(struct ){…}` (compile fail). Asm
           * field stores miss the dest layout (sit-red run=162). Named
           * local extra already 7; UFCS stamps via the module-func formal.
           * G.7: reconstruct via param_name + find_or_alloc_named, then
           * reuse typeck_coerce_init_struct_lit_to_decl (no second stamp).
           * PLATFORM: SHARED.
           */
          if (dyn_arg > 0 && dyn_pk == 8) {
            let dyn_pnm: u8[64] = [];
            let dyn_pnl: i32 = xlang_skip_trait_method_param_name_into_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, arg_i + 1, &dyn_pnm[0]);
            if (dyn_pnl > 0) {
              let dyn_nty: i32 = find_or_alloc_named_type_ref(arena, &dyn_pnm[0], dyn_pnl);
              if (dyn_nty > 0) {
                typeck_coerce_init_struct_lit_to_decl(module, arena, dyn_arg, dyn_nty);
              }
            }
          }
          /*
           * dest extras dest-PTR stamp (`p: *[2][]i32` / `*[2]i32` /
           * `*[2]*T` / `*[2][]*T`): nested extra lit `&[[2],[4]]` is
           * ADDR_OF of ARRAY_LIT. Scalar PTR skips elem kind 10 so
           * check_expr leaves the ARRAY_LIT wrap-once as `[2][1]i32`
           * (host-C) and asm ADDR_OF of ARRAY_LIT is CG002 until emit
           * completes. Named ADDR_OF of a typed `[2][]i32` local already
           * dest-stamps via the formal (dyn_add_ptr_arr_slice.x = 7).
           * Registry param_elem_kind / param_elem_elem_kind /
           * param_elem_array ndims/dims already hold the ARRAY pointee
           * (`[2][]T` extras / wrap-once `[2]i32` / extra STAR). Unused
           * slot dims[ndims] extra SLICE wrap COUNT (1 = `*[2][]T`; 2 =
           * `*[2][][]T`; 0 = no extra wrap = `*[2]i32`). Unused slot
           * dims[ndims+1] extra PTR wrap COUNT (1 = `*[2]*T` /
           * `*[2][]*T`; 0 = no extra PTR = `*[2]i32` / `*[2][]T`;
           * `*[2][]*T` has both slots set). Wrap extra PTR of leaf
           * extra times then extra SLICE then ARRAY inner-first then
           * wrap ptr. Peel ADDR_OF (kind 51): dest-stamp the operand
           * ARRAY_LIT as the PTR elem via typeck_coerce_init_expr_to_decl,
           * then stamp ADDR_OF as the reconstructed PTR dest. Do not
           * change typeck_coerce_init_expr_to_decl to peel ADDR_OF
           * globally (would mix typed-dest ADDR_OF of ARRAY_LIT
           * leftover). Twin of dest extras dest-RET PTR-to-ARRAY extra
           * empty `[]` `*[2][]T`. Discriminant vs dest extras dest-
           * ARRAY of SLICE extra `[2][]i32` (no ADDR_OF) is PTR wrap.
           * Do not invent -3 / a second dest-PTR stamp table. Do not
           * mix dest extras dest-PTR of SLICE extra `*[]T` / dest
           * extras dest-PTR of PTR extra `**T` (RET twins; PARAM first
           * leaf is PTR-to-ARRAY). PLATFORM: SHARED. G.7: complete
           * this wrap.
           */
          if (dyn_arg > 0 && dyn_pk == 9) {
            let dyn_pek: i32 = xlang_skip_trait_method_param_elem_kind_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, arg_i + 1);
            /*
             * PTR-to-ARRAY formal (`*[2]i32` / `*[2][]T` / `*[2]*T`):
             * scalar PTR skips elem kind 10. Twin of dest extras
             * dest-RET PTR-to-ARRAY. PLATFORM: SHARED.
             */
            if (dyn_pek == 10) {
              let dyn_peek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_plf: i32 = 0;
              if (dyn_peek >= 0 && dyn_peek != 8 && dyn_peek != 9 && dyn_peek != 10
                  && dyn_peek != 11 && dyn_peek != 13) {
                dyn_plf = pipeline_type_ensure_by_kind_ord(arena, dyn_peek);
              }
              /*
               * PTR-to-ARRAY NAMED leaf (`*[2]Pair`): registry
               * param_elem_elem_kind=8; param_name is the leaf.
               * G.7: wrap named into dyn_plf then ARRAY + wrap ptr.
               * PLATFORM: SHARED.
               */
              if (dyn_plf == 0 && dyn_peek == 8) {
                let dyn_pnm2: u8[64] = [];
                let dyn_pnl2: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_pnm2[0]);
                if (dyn_pnl2 > 0) {
                  dyn_plf = find_or_alloc_named_type_ref(arena, &dyn_pnm2[0], dyn_pnl2);
                }
              }
              if (dyn_plf > 0) {
                let dyn_pend: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                let dyn_pew: i32 = dyn_plf;
                if (dyn_pend >= 1) {
                  let dyn_ppx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_pend + 1);
                  if (dyn_ppx > 0) {
                    let dyn_ppi: i32 = 0;
                    while (dyn_ppi < dyn_ppx && dyn_pew > 0) {
                      dyn_pew = find_or_alloc_ptr_type_ref(arena, dyn_pew);
                      dyn_ppi = dyn_ppi + 1;
                    }
                  }
                  let dyn_pex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_pend);
                  if (dyn_pex > 0) {
                    let dyn_pxi: i32 = 0;
                    while (dyn_pxi < dyn_pex && dyn_pew > 0) {
                      dyn_pew = find_or_alloc_slice_type_ref(arena, dyn_pew);
                      dyn_pxi = dyn_pxi + 1;
                    }
                  }
                  let dyn_pei: i32 = dyn_pend - 1;
                  while (dyn_pei >= 0 && dyn_pew > 0) {
                    let dyn_ped: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_pei);
                    if (dyn_ped > 0) {
                      dyn_pew = find_or_alloc_array_type_ref(arena, dyn_pew, dyn_ped);
                    } else {
                      dyn_pew = 0;
                    }
                    dyn_pei = dyn_pei - 1;
                  }
                } else {
                  dyn_pew = 0;
                }
                if (dyn_pew > 0) {
                  let dyn_pty: i32 = find_or_alloc_ptr_type_ref(arena, dyn_pew);
                  if (dyn_pty > 0) {
                    /*
                     * Peel ADDR_OF then dest-stamp operand as PTR elem;
                     * stamp ADDR_OF as reconstructed PTR. Non-ADDR_OF
                     * extras reuse coerce on the arg itself.
                     * PLATFORM: SHARED.
                     */
                    let dyn_ak9: i32 = pipeline_expr_kind_ord_at(arena, dyn_arg);
                    if (dyn_ak9 == 51) {
                      let dyn_op9: i32 = pipeline_expr_unary_operand_ref_at(arena, dyn_arg);
                      if (dyn_op9 > 0) {
                        typeck_coerce_init_expr_to_decl(module, arena, dyn_op9, dyn_pew);
                      }
                      pipeline_expr_set_resolved_type_ref(arena, dyn_arg, dyn_pty);
                    } else {
                      typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_pty);
                    }
                  }
                }
              }
            }
          }
          /*
           * dest-ARRAY extra (`p: [2]i32` / `[2]Pair`): ARRAY_LIT stays
           * TYPE_ARRAY of unstamped elems after check_expr. Scalar
           * `[2]i32` already works (INT_LIT elems). NAMED leaf (`[2]Pair`)
           * leaves nameless STRUCT_LIT so host-C emits
           * `(uint8_t[]){(struct )}`. Sit-red dyn host-C compile fail;
           * named local extra already 7; asm dyn already 7 (field stores
           * by name). Registry param_elem_kind / param_name /
           * param_array_ndims+dims already hold the dest. G.7: reconstruct
           * via elem_kind / param_name + find_or_alloc_* then wrap ARRAY
           * (ndims inner-first, twin of dyn ret ARRAY); reuse
           * typeck_coerce_init_expr_to_decl so dest-ARRAY + STRUCT_LIT
           * elems stamp together (no second ARRAY_LIT / STRUCT_LIT stamp).
           * Remaining leftover: PTR/VECTOR elem of dest-ARRAY (SLICE
           * elem `[2][]i32` closed with scanner + this reconstruct).
           * UFCS extras dest-stamp STRUCT_LIT elems in the same-module
           * extras loop (twin typeck_check_call_arg_types). PLATFORM: SHARED.
           */
          if (dyn_arg > 0 && dyn_pk == 10) {
            let dyn_aek: i32 = xlang_skip_trait_method_param_elem_kind_c(&dyn_trait_nm[0],
                    dyn_trait_nlen, dyn_slot, arg_i + 1);
            let dyn_alf: i32 = 0;
            if (dyn_aek >= 0 && dyn_aek != 8 && dyn_aek != 9 && dyn_aek != 10
                && dyn_aek != 11 && dyn_aek != 13) {
              dyn_alf = pipeline_type_ensure_by_kind_ord(arena, dyn_aek);
            }
            if (dyn_alf == 0 && dyn_aek == 8) {
              let dyn_apnm: u8[64] = [];
              let dyn_apnl: i32 = xlang_skip_trait_method_param_name_into_c(&dyn_trait_nm[0],
                      dyn_trait_nlen, dyn_slot, arg_i + 1, &dyn_apnm[0]);
              if (dyn_apnl > 0) {
                dyn_alf = find_or_alloc_named_type_ref(arena, &dyn_apnm[0], dyn_apnl);
              }
            }
            /*
             * dest-ARRAY-of-SLICE extra (`p: [2][]i32` / `[2][][]i32` /
             * `[2][]*i32` / `[2][][2]i32` / `[2][][]*i32` /
             * `[2][][2]*i32` / `[2][][2][]i32`): ARRAY_LIT `[[2, 3], [1, 4]]` stays
             * TYPE_ARRAY of ARRAY. Scalar dest-ARRAY skips elem kind
             * 11. Sit-red `[2][]i32` was asm=139 / host-C=133
             * (`(int32_t[][2])` into a slice* wrapper). Sit-red
             * `[2][][]i32` nested ARRAY_LIT `[[[2, 4]], [[3, 5]]]`
             * is 139 (`(int32_t[][1][2])`) because wrap-once dest-
             * stamps `[2][]i32`. Sit-red `[2][]*i32` nested ARRAY_LIT
             * `[[&n, &n], [&m, &m]]` is 139 because wrap-once dest-
             * stamps `[2][]i32` not `[2][]*i32` (impl-match already
             * matches at SLICE; named / UFCS / typed lets dest-stamp
             * via the formal 6/7). Sit-red `[2][][2]i32` nested
             * ARRAY_LIT `[[[2, 3]], [[1, 4]]]` is 139 because wrap-
             * once dest-stamps `[2][]i32` not `[2][][2]i32` (skip-
             * trait after `[N][]` then `[M]` already stores ndims>=1
             * via the wave437 pending LBRACKET dim collector; named
             * / UFCS / asg / typed lets already 7; impl-match leftover
             * SLICE vs eek=SLICE is not T001). Sit-red `[2][][2]*i32`
             * nested ARRAY_LIT `[[[&n, &n]], [[&m, &m]]]` is 139
             * because extra STAR after `[N][][M]` set elem_kind=-1 so
             * dest extras never extra-wraps PTR after extra ARRAY
             * wraps (dest-stamps `[2][][2]i32` not `[2][][2]*i32`;
             * named / UFCS / typed lets dest-stamp via the formal
             * 6/7; ARRAY leftover SLICE vs eek=SLICE is not T001).
             * Skip-trait stores elem_kind=SLICE + eek=leaf after
             * `[N][]`; extra inner SLICE uses ndims=-2 with wrap
             * count in dims[0] (0 means 1 = `[2][][]T`; 2 =
             * `[2][][][]T`); extra inner PTR uses unused slot
             * dims[0] with ndims staying 0 (1 = `[2][]*T`; 0 = no
             * extra PTR = `[2][]i32`); extra inner ARRAY uses
             * ndims>=1 dims[0..ndims-1] (`[2][][2]T`); extra PTR
             * when ndims==-2 lives in unused slot dims[1]
             * (1 = `[2][][]*T`; 0 = no extra PTR = `[2][][]T`); extra
             * PTR when ndims>=1 lives in unused slot dims[ndims]
             * (1 = `[2][][2]*T`; 0 = no extra PTR = `[2][][2]T`;
             * ban -3). Extra SLICE wrap when ndims>=1 lives in
             * unused slot dims[ndims+1] (1 = `[2][][2][]T`; 2 =
             * `[2][][2][][]T`; 0 = no extra wrap = `[2][][2]T`;
             * extra PTR stays dims[ndims] — do not reopen). Sit-red
             * `[2][][2][]i32` nested ARRAY_LIT
             * `[[[[2], [3]]], [[[1], [4]]]]` is 139 because extra
             * empty `[]` after `[N][][M]` set elem_kind=-1 so dest
             * extras skipped (named / UFCS dest-stamp via the
             * formal 7). G.7: wrap PTR of leaf extra times then extra
             * SLICE wraps at dim_ix==ndims+1 then wrap ARRAY of leaf
             * inner-first when ndims>=1 then wrap slice into dyn_alf
             * then extra SLICE wraps when ndims==-2 then the existing
             * ARRAY wrap below (no second dest-ARRAY stamp; do not
             * invent -3; do not add impl-match extra ARRAY / extra
             * PTR / extra SLICE peels). Twin of dest extras dest-
             * SLICE-of-ARRAY extra PTR wraps. NAMED leaf of
             * `[N][]Pair` is handled below via param_name. dest extras
             * dest-SLICE-of-SLICE extra PTR (`[][]*T`) is handled in
             * the dest-SLICE path (same dims[0] extra PTR encoding;
             * discriminant is SLICE outer vs ARRAY outer). dest extras
             * dest-SLICE-of-SLICE extra ARRAY extra PTR (`[][][2]*T`)
             * and dest extras dest-SLICE-of-SLICE extra wrap
             * `[][][2][]T` are handled in the dest-SLICE path
             * (same unused-slot encoding; discriminant is SLICE
             * outer vs ARRAY outer).
             * PLATFORM: SHARED.
             */
            if (dyn_alf == 0 && dyn_aek == 11) {
              let dyn_aseek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_aslf: i32 = 0;
              if (dyn_aseek >= 0 && dyn_aseek != 8 && dyn_aseek != 9 && dyn_aseek != 10
                  && dyn_aseek != 11 && dyn_aseek != 13) {
                dyn_aslf = pipeline_type_ensure_by_kind_ord(arena, dyn_aseek);
              }
              /*
               * dest-ARRAY-of-SLICE NAMED leaf (`p: [2][]Pair`):
               * ARRAY_LIT `[[{a:2,b:3}],[{a:4,b:4}]]` stays TYPE_ARRAY
               * of nameless STRUCT_LIT. Scalar dest-ARRAY-of-SLICE
               * skips elem_elem kind 8. Sit-red dyn extra asm/host-C=139
               * (`(uint8_t[]){(struct )}`); named local / UFCS already 7.
               * Registry param_name already holds the leaf (`Pair`).
               * G.7: wrap named then wrap slice into dyn_alf; reuse
               * typeck_coerce_init_expr_to_decl (no second dest-ARRAY
               * / dest-SLICE / STRUCT_LIT stamp). PLATFORM: SHARED.
               */
              if (dyn_aslf == 0 && dyn_aseek == 8) {
                let dyn_asnm: u8[64] = [];
                let dyn_asnl: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_asnm[0]);
                if (dyn_asnl > 0) {
                  dyn_aslf = find_or_alloc_named_type_ref(arena, &dyn_asnm[0], dyn_asnl);
                }
              }
              if (dyn_aslf > 0) {
                let dyn_asaw: i32 = dyn_aslf;
                let dyn_asand: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                /*
                 * dest extras dest-ARRAY-of-SLICE extra PTR wraps
                 * (`[2][]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix=0 when ndims==0. Wrap PTR of leaf
                 * extra times then wrap SLICE. `[2][]i32`
                 * (aspx<=0) stays wrap-once. Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_asand == 0) {
                  let dyn_aspx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                  if (dyn_aspx > 0) {
                    let dyn_aspi: i32 = 0;
                    while (dyn_aspi < dyn_aspx && dyn_asaw > 0) {
                      dyn_asaw = find_or_alloc_ptr_type_ref(arena, dyn_asaw);
                      dyn_aspi = dyn_aspi + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-ARRAY-of-SLICE extra PTR wraps
                 * (`[2][][]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix=1 when ndims==-2 (dims[0] is extra
                 * SLICE). Wrap PTR of leaf extra times then wrap
                 * SLICE then extra SLICE wraps. `[2][][]i32`
                 * (aspx2<=0) stays extra-SLICE-only. Twin of dest
                 * extras dest-SLICE-of-SLICE extra PTR wraps
                 * (`[][][]*T`; same unused-slot encoding;
                 * discriminant is ARRAY vs SLICE outer). ARRAY
                 * leftover impl-match matches at leftover SLICE
                 * (not T001). Do not invent -3. PLATFORM: SHARED.
                 */
                if (dyn_asand == -2) {
                  let dyn_aspx2: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 1);
                  if (dyn_aspx2 > 0) {
                    let dyn_aspi2: i32 = 0;
                    while (dyn_aspi2 < dyn_aspx2 && dyn_asaw > 0) {
                      dyn_asaw = find_or_alloc_ptr_type_ref(arena, dyn_asaw);
                      dyn_aspi2 = dyn_aspi2 + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-ARRAY-of-SLICE extra PTR wraps
                 * (`[2][][2]*T`): dim accessor returns extra PTR wrap
                 * count at dim_ix==ndims when ndims>=1 (unused slot
                 * after inner ARRAY dims). Wrap PTR of leaf extra
                 * times then wrap ARRAY inner-first then wrap SLICE.
                 * `[2][][2]i32` (aspx3<=0) stays extra-ARRAY-only.
                 * Twin of dest extras dest-SLICE-of-ARRAY extra PTR
                 * wraps (`[][2]*T`; discriminant is ARRAY vs SLICE
                 * elem). ARRAY leftover impl-match matches at leftover
                 * SLICE (not T001). dest extras dest-SLICE-of-SLICE
                 * extra ARRAY extra PTR (`[][][2]*T`) is handled in
                 * the dest-SLICE path (same dims[ndims] extra PTR
                 * encoding; discriminant is SLICE outer vs ARRAY
                 * outer). Do not invent -3. PLATFORM: SHARED.
                 */
                if (dyn_asand >= 1) {
                  let dyn_aspx3: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_asand);
                  if (dyn_aspx3 > 0) {
                    let dyn_aspi3: i32 = 0;
                    while (dyn_aspi3 < dyn_aspx3 && dyn_asaw > 0) {
                      dyn_asaw = find_or_alloc_ptr_type_ref(arena, dyn_asaw);
                      dyn_aspi3 = dyn_aspi3 + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-ARRAY-of-SLICE extra wrap
                 * (`[2][][2][]T` / `[2][][2][][]T`): dim accessor
                 * returns extra SLICE wrap count at dim_ix==ndims+1
                 * when ndims>=1 (unused slot after extra PTR at
                 * dims[ndims]). Wrap extra SLICE of leaf extra
                 * times then wrap ARRAY inner-first then wrap
                 * SLICE. `[2][][2]i32` (asex3<=0) stays extra-
                 * ARRAY-only. Twin of dest extras dest-SLICE-of-
                 * ARRAY extra SLICE wraps (`[][2][]T`; extra SLICE
                 * there is dims[ndims]; discriminant is ARRAY vs
                 * SLICE elem / SLICE vs ARRAY outer). Extra PTR
                 * of `[2][][2]*T` stays dims[ndims] — do not
                 * reopen. ARRAY leftover impl-match leftover
                 * SLICE vs eek=SLICE is not T001 (do not add
                 * extra SLICE peels). Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_asand >= 1) {
                  let dyn_asex3: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                          &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                          dyn_asand + 1);
                  if (dyn_asex3 > 0) {
                    let dyn_asxi3: i32 = 0;
                    while (dyn_asxi3 < dyn_asex3 && dyn_asaw > 0) {
                      dyn_asaw = find_or_alloc_slice_type_ref(arena, dyn_asaw);
                      dyn_asxi3 = dyn_asxi3 + 1;
                    }
                  }
                }
                /*
                 * dest extras dest-ARRAY-of-SLICE extra ARRAY wraps
                 * (`[2][][2]T`): dim accessor returns inner ARRAY
                 * dims at 0..ndims-1 when ndims>=1 (wave437 store
                 * after `[N][]` then `[M]`). Wrap ARRAY of leaf
                 * inner-first then wrap SLICE. `[2][]i32`
                 * (ndims==0) stays wrap-once. Twin of dest extras
                 * dest-SLICE-of-ARRAY ARRAY wrap. Do not invent
                 * -3. PLATFORM: SHARED.
                 */
                if (dyn_asand >= 1) {
                  let dyn_asai: i32 = dyn_asand - 1;
                  while (dyn_asai >= 0 && dyn_asaw > 0) {
                    let dyn_asad: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_asai);
                    if (dyn_asad > 0) {
                      dyn_asaw = find_or_alloc_array_type_ref(arena, dyn_asaw, dyn_asad);
                    } else {
                      dyn_asaw = 0;
                    }
                    dyn_asai = dyn_asai - 1;
                  }
                }
                dyn_alf = find_or_alloc_slice_type_ref(arena, dyn_asaw);
                /*
                 * dest extras dest-ARRAY-of-SLICE extra wraps
                 * (`[2][][]T` / `[2][][][]T`): dim accessor returns
                 * extra wrap count at dim_ix=0 when ndims==-2.
                 * One wrap dest-stamps `[2][]i32`; wrap extra times
                 * then the existing ARRAY wrap. Do not invent -3.
                 * PLATFORM: SHARED.
                 */
                if (dyn_alf > 0) {
                  if (dyn_asand == -2) {
                    let dyn_asex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                    if (dyn_asex < 1) {
                      dyn_asex = 1;
                    }
                    let dyn_asi: i32 = 0;
                    while (dyn_asi < dyn_asex && dyn_alf > 0) {
                      dyn_alf = find_or_alloc_slice_type_ref(arena, dyn_alf);
                      dyn_asi = dyn_asi + 1;
                    }
                  }
                }
              }
            }
            /*
             * dest-ARRAY-of-PTR extra (`p: [2]*[2]i32` / `[2]*[]i32` /
             * `[2]*[][]i32` / `[2]*[2]*i32`): ARRAY_LIT `[&r0, &r1]`
             * stays TYPE_ARRAY of PTR. Scalar dest-ARRAY skips elem
             * kind 9. Sit-red `[2]*[2]i32` was T001 (inner ARRAY dim
             * lost); `[2]*[][]T` sit-red T001 because ARRAY+PTR
             * impl-match peeled ndims=-2 once (pelem still SLICE vs
             * eeek=leaf) and dest extras wrapped SLICE of leaf once
             * (dest would be `[2]*[]i32`). `[2]*[2]*T` sit-red T001
             * because extra STAR after `[K]*[N]` required SLICE outer
             * so ARRAY outer never stored extra PTR (leaf T never
             * committed) and dest extras wrap-once dest-stamps
             * `[2]*[2]i32`. Extra PTR wrap COUNT lives in unused slot
             * dims[ndims+1] (1 = `[2]*[2]*T`; 0 = no extra PTR =
             * `[2]*[2]i32`; extra SLICE stays dims[ndims];
             * `[2]*[2][]*T` has both slots set). Skip-trait stores
             * elem_kind=PTR + eek=leaf + elem_array_ndims/dims after
             * `[N]*` then `[` (ndims=-2 extra wrap count in dims[0]:
             * 0 means 1 = `[2]*[]T`; 2 = `[2]*[][]T`). Named / UFCS
             * dest-stamp via the formal once store keeps PTR.
             * G.7: wrap extra PTR of leaf extra times then extra
             * SLICE wraps then ARRAY via elem_array_ndims then wrap
             * ptr into dyn_alf; the existing ARRAY wrap below handles
             * the outer [N]. No second dest-ARRAY stamp; do not invent
             * -3. ndims==0 keeps ptr-of-leaf (`[2]*i32` / `[2]*Pair`
             * already 7 via ADDR_OF elems). Twin of dest-SLICE-of-PTR
             * extra wraps. Discriminant vs dest extras dest-SLICE of
             * PTR extra `[]*[2]*T` (same unused slot) is ARRAY vs
             * SLICE outer. PLATFORM: SHARED.
             */
            if (dyn_alf == 0 && dyn_aek == 9) {
              let dyn_aeek: i32 = xlang_skip_trait_method_param_elem_elem_kind_c(
                      &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_aplf: i32 = 0;
              if (dyn_aeek >= 0 && dyn_aeek != 8 && dyn_aeek != 9 && dyn_aeek != 10
                  && dyn_aeek != 11 && dyn_aeek != 13) {
                dyn_aplf = pipeline_type_ensure_by_kind_ord(arena, dyn_aeek);
              }
              if (dyn_aplf == 0 && dyn_aeek == 8) {
                let dyn_apnm: u8[64] = [];
                let dyn_apnl: i32 = xlang_skip_trait_method_param_name_into_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                        &dyn_apnm[0]);
                if (dyn_apnl > 0) {
                  dyn_aplf = find_or_alloc_named_type_ref(arena, &dyn_apnm[0], dyn_apnl);
                }
              }
              if (dyn_aplf > 0) {
                let dyn_aand: i32 = xlang_skip_trait_method_param_elem_array_ndims_c(
                        &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1);
                if (dyn_aand != 0) {
                  let dyn_apaw: i32 = dyn_aplf;
                  if (dyn_aand == -2) {
                    /*
                     * dest extras dest-ARRAY-of-PTR extra wraps
                     * (`[2]*[]T` / `[2]*[][]T`): dim accessor returns
                     * extra wrap count at dim_ix=0 when ndims==-2.
                     * Wrap SLICE extra times then wrap ptr. Do not
                     * invent -3. PLATFORM: SHARED.
                     */
                    let dyn_apex: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                    if (dyn_apex < 1) {
                      dyn_apex = 1;
                    }
                    let dyn_api: i32 = 0;
                    while (dyn_api < dyn_apex && dyn_apaw > 0) {
                      dyn_apaw = find_or_alloc_slice_type_ref(arena, dyn_apaw);
                      dyn_api = dyn_api + 1;
                    }
                  } else if (dyn_aand >= 1) {
                    /*
                     * dest extras dest-ARRAY-of-PTR extra wraps
                     * (`[2]*[2][]T` / `[2]*[2][][]T` / `[2]*[2]*T` /
                     * `[2]*[2][]*T`): dim accessor returns extra PTR
                     * wrap count at dim_ix==ndims+1 and extra SLICE
                     * wrap count at dim_ix==ndims when unused slots
                     * >0. Wrap PTR of leaf extra times then extra
                     * SLICE wraps THEN ARRAY wrap then wrap PTR then
                     * outer ARRAY (`[2]*[2][]*T` is wrap-both).
                     * `[2]*[2]i32` (appx/apex<=0) stays wrap-once.
                     * Discriminant vs dest extras dest-SLICE-of-PTR
                     * extra `[]*[2]*T` / `[]*[2][]T` is ARRAY vs
                     * SLICE outer; same unused slots. Do not invent
                     * -3. PLATFORM: SHARED.
                     */
                    let dyn_appx: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_aand + 1);
                    if (dyn_appx > 0) {
                      let dyn_appi: i32 = 0;
                      while (dyn_appi < dyn_appx && dyn_apaw > 0) {
                        dyn_apaw = find_or_alloc_ptr_type_ref(arena, dyn_apaw);
                        dyn_appi = dyn_appi + 1;
                      }
                    }
                    let dyn_apex2: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                            &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                            dyn_aand);
                    if (dyn_apex2 > 0) {
                      let dyn_api2: i32 = 0;
                      while (dyn_api2 < dyn_apex2 && dyn_apaw > 0) {
                        dyn_apaw = find_or_alloc_slice_type_ref(arena, dyn_apaw);
                        dyn_api2 = dyn_api2 + 1;
                      }
                    }
                    let dyn_apai: i32 = dyn_aand - 1;
                    while (dyn_apai >= 0 && dyn_apaw > 0) {
                      let dyn_apad: i32 = xlang_skip_trait_method_param_elem_array_dim_c(
                              &dyn_trait_nm[0], dyn_trait_nlen, dyn_slot, arg_i + 1,
                              dyn_apai);
                      if (dyn_apad > 0) {
                        dyn_apaw = find_or_alloc_array_type_ref(arena, dyn_apaw, dyn_apad);
                      } else {
                        dyn_apaw = 0;
                      }
                      dyn_apai = dyn_apai - 1;
                    }
                  }
                  if (dyn_apaw > 0) {
                    dyn_alf = find_or_alloc_ptr_type_ref(arena, dyn_apaw);
                  }
                }
              }
            }
            if (dyn_alf > 0) {
              let dyn_and: i32 = xlang_skip_trait_method_param_array_ndims_c(&dyn_trait_nm[0],
                      dyn_trait_nlen, dyn_slot, arg_i + 1);
              let dyn_aty: i32 = 0;
              if (dyn_and >= 2) {
                let dyn_ai: i32 = dyn_and - 1;
                let dyn_aw: i32 = dyn_alf;
                while (dyn_ai >= 0 && dyn_aw > 0) {
                  let dyn_ad: i32 = xlang_skip_trait_method_param_array_dim_c(&dyn_trait_nm[0],
                          dyn_trait_nlen, dyn_slot, arg_i + 1, dyn_ai);
                  if (dyn_ad > 0) {
                    dyn_aw = find_or_alloc_array_type_ref(arena, dyn_aw, dyn_ad);
                  } else {
                    dyn_aw = 0;
                  }
                  dyn_ai = dyn_ai - 1;
                }
                dyn_aty = dyn_aw;
              } else {
                let dyn_ad1: i32 = xlang_skip_trait_method_param_array_dim_c(&dyn_trait_nm[0],
                        dyn_trait_nlen, dyn_slot, arg_i + 1, 0);
                if (dyn_ad1 > 0) {
                  dyn_aty = find_or_alloc_array_type_ref(arena, dyn_alf, dyn_ad1);
                }
              }
              if (dyn_aty > 0) {
                typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_aty);
              }
            }
          }
          arg_i = arg_i + 1;
        }
        return 0;
      }
    }

    num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref);
    arg_i = 0;
    while (arg_i < num_args) {
      let arg_ref: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i);
      if (check_expr(module, arena, arg_ref, return_type_ref, ctx) != 0) {
        return 0 - 1;
      }
      arg_i = arg_i + 1;
    }

    /*
     * 10.3.3 slice3: `h.f(args)` METHOD_CALL when `f` is Cap/TYPE_FN field.
     * Before import/UFCS/LANG-004 — field-fnptr is not an impl method.
     * Stamp ret like Cap CALL (TYPE_FN elem / ambient / i32). PLATFORM: SHARED.
     */
    if (base_ty > 0 && method_nlen > 0) {
      let ff_ty: i32 = typeck_method_call_field_fnptr_ty(module, arena, ctx, base_ty, &method_nm[0],
          method_nlen);
      if (ff_ty > 0) {
        let ff_ret: i32 = 0;
        let ff_ko: i32 = pipeline_type_kind_ord_at(arena, ff_ty);
        let ff_er: i32 = 0;
        let ff_expect: i32 = 0;
        if (ff_ko == TypeKind.TYPE_FN as i32) {
          ff_er = pipeline_type_elem_ref_at(arena, ff_ty);
          if (ff_er > 0) {
            ff_ret = ff_er;
          }
        }
        if (ff_ret <= 0) {
          ff_expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot());
          if (ff_expect <= 0 && return_type_ref > 0) {
            ff_expect = return_type_ref;
          }
          if (ff_expect > 0) {
            ff_ret = ff_expect;
          } else {
            ff_ret = ensure_i32_type_ref(arena);
          }
        }
        if (ff_ret > 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, ff_ret);
          return 0;
        }
      }
    }

    /* Hold expected_ret for zero-arg / tie-break overload pick. */
    expect_store = 0;
    if (return_type_ref > 0) {
      expect_store = return_type_ref;
    }
    typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), expect_store);

    dep_ix = 0 - 1;
    func_ix = 0 - 1;
    import_ret_ty = 0;
    if (ctx != 0 as *PipelineDepCtx && base_kind == ord_var) {
      base_nlen = pipeline_expr_var_name_len(arena, base_ref);
      if (base_nlen > 0 && base_nlen <= 127) {
        pipeline_expr_var_name_into(arena, base_ref, &base_nm[0]);
        n_imp = typeck_module_num_imports(module);
        ii = 0;
        while (ii < n_imp) {
          /* wave314: typeck_import_binding_name_equal returns bool (not i32). */
          if (pipeline_module_import_kind_at(module, ii) == ord_import_binding
              && typeck_import_binding_name_equal(module, ii, &base_nm[0], base_nlen)) {
            dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii);
            func_ix = 0 - 1;
            if (dep_slot >= 0) {
              dm = pipeline_dep_ctx_module_at(ctx, dep_slot);
              if (dm != 0 as *Module && pipeline_module_num_funcs(dm) > 0) {
                import_ret_ty = pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(
                  dm, arena, &method_nm[0], method_nlen, dep_slot, num_args, expr_ref, 1, ctx, &func_ix);
                if (import_ret_ty > 0) {
                  dep_ix = dep_slot;
                }
              }
            }
            /* Path slot empty or miss: scan all dep modules (same as strict seed). */
            if (import_ret_ty <= 0) {
              let try_di: i32 = 0;
              let nd: i32 = pipeline_dep_ctx_ndep(ctx);
              while (try_di < nd && import_ret_ty <= 0) {
                let try_dm: *Module = 0 as *Module;
                let try_fn: i32 = 0 - 1;
                let try_ret: i32 = 0;
                if (try_di != dep_slot) {
                  try_dm = pipeline_dep_ctx_module_at(ctx, try_di);
                  if (try_dm != 0 as *Module && pipeline_module_num_funcs(try_dm) > 0) {
                    try_ret = pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(
                      try_dm, arena, &method_nm[0], method_nlen, try_di, num_args, expr_ref, 1, ctx,
                      &try_fn);
                    if (try_ret > 0) {
                      import_ret_ty = try_ret;
                      dep_ix = try_di;
                      func_ix = try_fn;
                    }
                  }
                }
                try_di = try_di + 1;
              }
            }
            break;
          }
          ii = ii + 1;
        }
      }
    }
    typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0);

    if (import_ret_ty > 0) {
      let cm: *Module = module;
      if (dep_ix >= 0 && ctx != 0 as *PipelineDepCtx) {
        dm = pipeline_dep_ctx_module_at(ctx, dep_ix);
        if (dm != 0 as *Module) {
          cm = dm;
        }
      }
      pipeline_expr_apply_call_resolve(arena, expr_ref, dep_ix, func_ix);
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, import_ret_ty);
      /* G.7: stamp FLOAT_LIT args to formal f32/f64 (ambient was call return). */
      typeck_stamp_resolved_args_float_lit(arena, expr_ref, cm, func_ix, dep_ix, ctx, 0);
      /*
       * Post-resolve extras: same T001 gate as CALL. first_idx fallback can
       * bind a same-arity func after all scores failed (3-lane hsum).
       * PLATFORM: SHARED.
       */
      if (typeck_check_call_arg_types(module, arena, expr_ref, ctx) != 0) {
        return 0 - 1;
      }
      return 0;
    }

    /*
     * Generic method UFCS first (wave494/wave252): non-generic type_refs_equal
     * fails on Wrap<i32> vs Wrap<T>; weak integer match would stamp free T.
     */
    if (base_ty > 0 && method_nlen > 0) {
      if (typeck_method_call_generic_ufcs(module, arena, expr_ref, base_ty, &method_nm[0], method_nlen,
          num_args) != 0) {
        return 0;
      }
    }

    /* Same-module free-fn UFCS: method(self, args...) / auto-ref *T self. */
    if (base_ty > 0 && method_nlen > 0) {
      let uj: i32 = 0;
      let uf_best: i32 = 0 - 1;
      let uf_best_score: i32 = 0 - 1;
      let saw_simd_mismatch: i32 = 0;
      let nf: i32 = pipeline_module_num_funcs(module);
      while (uj < nf) {
        let nparams: i32 = 0;
        let score: i32 = 0;
        let matched: i32 = 1;
        let p0: i32 = 0;
        let sc0: i32 = 0 - 1;
        let ai: i32 = 0;
        let simd_recv_refuse: i32 = 0;
        if (pipeline_module_func_name_equal_at(module, uj, &method_nm[0], method_nlen) != 0) {
          nparams = pipeline_module_func_num_params_at(module, uj);
          if (nparams == num_args + 1) {
            p0 = pipeline_module_func_param_type_ref_at(module, uj, 0);
            sc0 = 0 - 1;
            simd_recv_refuse = 0;
            /*
             * ARRAY_LIT receiver was check_expr'd with ambient 0 → wave611
             * TYPE_ARRAY [N]T. Self formal is TYPE_VECTOR / NAMED i32x4.
             * G.7: reuse typeck_coerce_init_array_vector_lit_to_decl (CALL-arg /
             * let authority) so type_refs_equal sees the stamped SIMD type.
             * Coerce 0 + ARRAY_LIT + SIMD lanes: n_elems != lanes or elem
             * type — refuse this candidate (≡ CALL score T001). Do not
             * fall through to type_refs_equal / auto-ref / weak integer.
             * PLATFORM: SHARED.
             */
            if (p0 > 0 && base_ref > 0) {
              let crc0: i32 = typeck_coerce_init_array_vector_lit_to_decl(module, arena, base_ref, p0,
              pipeline_type_kind_ord_at(arena, p0),
              pipeline_expr_kind_ord_at(arena, base_ref));
              let bk0: i32 = pipeline_expr_kind_ord_at(arena, base_ref);
              if (crc0 == 0 && bk0 == 46 && typeck_vector_lanes_of_type(arena, p0) > 0) {
                simd_recv_refuse = 1;
                saw_simd_mismatch = 1;
              } else {
                base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
              }
            }
            if (simd_recv_refuse == 0 && p0 > 0
                && pipeline_typeck_type_refs_equal_c(arena, base_ty, p0) != 0) {
              sc0 = 1000;
            }
            /* auto-ref: value T.method when formal is *T */
            if (simd_recv_refuse == 0 && sc0 < 0 && p0 > 0
                && pipeline_type_kind_ord_at(arena, p0) == ord_ptr) {
              let pe: i32 = pipeline_type_elem_ref_at(arena, p0);
              if (pe > 0 && pipeline_typeck_type_refs_equal_c(arena, base_ty, pe) != 0) {
                sc0 = 900;
              }
            }
            /* Weak integer family match on self (strict seed parity). */
            if (simd_recv_refuse == 0 && sc0 < 0 && p0 > 0) {
              let ak: i32 = pipeline_type_kind_ord_at(arena, base_ty);
              let pk: i32 = pipeline_type_kind_ord_at(arena, p0);
              if ((pk == 0 || pk == 2 || pk == 3 || pk == 4 || pk == 5 || pk == 6 || pk == 7)
                  && (ak == 0 || ak == 2 || ak == 3 || ak == 4 || ak == 5 || ak == 6 || ak == 7)) {
                if (pk == ak || (ak == 0 && (pk == 5 || pk == 6 || pk == 7))
                    || (ak == 2 && (pk == 0 || pk == 3 || pk == 4 || pk == 6))) {
                  sc0 = 100;
                }
              }
            }
            if (sc0 >= 0) {
              score = sc0;
              matched = 1;
              ai = 0;
              while (ai < num_args) {
                let param_raw: i32 = pipeline_module_func_param_type_ref_at(module, uj, ai + 1);
                let arg_ref2: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, ai);
                let arg_ty: i32 = 0;
                let crc_a: i32 = 0;
                if (arg_ref2 > 0 && param_raw > 0) {
                  crc_a = typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref2, param_raw,
                  pipeline_type_kind_ord_at(arena, param_raw),
                  pipeline_expr_kind_ord_at(arena, arg_ref2));
                  /*
                   * Extra ARRAY_LIT → SIMD formal: same refuse as self
                   * (e.g. recv.add4([1,2,3]) vs other: i32x4).
                   * PLATFORM: SHARED.
                   */
                  if (crc_a == 0
                      && pipeline_expr_kind_ord_at(arena, arg_ref2) == 46
                      && typeck_vector_lanes_of_type(arena, param_raw) > 0) {
                    saw_simd_mismatch = 1;
                    matched = 0;
                    break;
                  }
                  /*
                   * UFCS extras dest-stamp: ARRAY dest already stamped so
                   * host-C emits `struct Pair[]` / dest-SLICE wrap, but
                   * STRUCT_LIT elems stayed nameless (`(struct )`; asm
                   * run=3 first field only). Nameless `{a:2,b:4}` extras
                   * also need dest-NAMED or type_refs_equal fails T001.
                   * G.7: reuse typeck_check_call_arg_types dest helpers
                   * (no second STRUCT_LIT stamp). PLATFORM: SHARED.
                   */
                  typeck_coerce_array_lit_struct_elems_to_decl(module, arena, arg_ref2, param_raw);
                  typeck_coerce_init_struct_lit_to_decl(module, arena, arg_ref2, param_raw);
                }
                if (arg_ref2 > 0) {
                  arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref2);
                }
                if (param_raw <= 0 || arg_ty <= 0
                    || pipeline_typeck_type_refs_equal_c(arena, arg_ty, param_raw) == 0) {
                  matched = 0;
                  break;
                }
                score = score + 1000;
                ai = ai + 1;
              }
              if (matched != 0 && score > uf_best_score) {
                uf_best_score = score;
                uf_best = uj;
              }
            }
          }
        }
        uj = uj + 1;
      }
      if (uf_best >= 0) {
        let uf_ret: i32 = pipeline_module_func_return_type_at(module, uf_best);
        if (uf_ret > 0) {
          pipeline_expr_apply_call_resolve(arena, expr_ref, 0 - 1, uf_best);
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, uf_ret);
          /* UFCS: arg i maps to param i+1 (param 0 is self). */
          typeck_stamp_resolved_args_float_lit(arena, expr_ref, module, uf_best, 0 - 1, ctx, 1);
          return 0;
        }
      }
      /*
       * Same-name SIMD UFCS existed but ARRAY_LIT lanes/elem refused coerce.
       * G.7: same T001 as typeck_check_call_arg_types (not LANG-004).
       * PLATFORM: SHARED.
       */
      if (saw_simd_mismatch != 0) {
        line = pipeline_expr_line_at(arena, expr_ref);
        col = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_call_arg_type_mismatch(line, col);
        return 0 - 1;
      }
    }

    /*
     * Generic body: T: Trait grants Trait.method on a free type-param receiver.
     * Must run after UFCS (concrete impls / SIMD) and before LANG-004.
     * PLATFORM: SHARED.
     */
    if (base_ty > 0 && method_nlen > 0) {
      if (typeck_method_call_resolve_generic_bound(module, arena, expr_ref, ctx, base_ty,
          &method_nm[0], method_nlen, num_args) != 0) {
        return 0;
      }
    }

    if (ret_ty > 0) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty);
      return 0;
    }
    /*
     * Associated Type.method(): receiver is a type name. check_expr(VAR) fails
     * because the name is not a value (not local/param). `P.mk()` / `P.id(7)` /
     * `P.get(p)` resolve to a same-module func with nparams == num_args
     * (self is an explicit extra when present). Instance `p.get()` already
     * matched UFCS nparams == num_args+1 above. Prefer a constructor whose
     * return TYPE_NAMED spelling matches the layout name.
     * Hoisted impl methods and free fns of the same arity both match (P.mk()
     * ≡ mk() when mk is unique). PLATFORM: SHARED — G.7 complete
     * typeck_check_expr_method_call; pin twin typeck_gen.linux.x86_64.c.
     */
    if (base_kind == ord_var && method_nlen > 0 && base_rc != 0) {
      let assoc_nlen: i32 = pipeline_expr_var_name_len(arena, base_ref);
      if (assoc_nlen > 0 && assoc_nlen <= 127) {
        pipeline_expr_var_name_into(arena, base_ref, &base_nm[0]);
        if (typeck_soa_find_layout_idx_by_name(module, &base_nm[0], assoc_nlen) >= 0) {
          let assoc_uj: i32 = 0;
          let assoc_best: i32 = 0 - 1;
          let assoc_best_score: i32 = 0 - 1;
          let assoc_nf: i32 = pipeline_module_num_funcs(module);
          while (assoc_uj < assoc_nf) {
            let assoc_np: i32 = 0;
            if (pipeline_module_func_name_equal_at(module, assoc_uj, &method_nm[0], method_nlen) != 0) {
              assoc_np = pipeline_module_func_num_params_at(module, assoc_uj);
              if (assoc_np == num_args) {
                let assoc_matched: i32 = 1;
                let assoc_score: i32 = 1;
                let assoc_ai: i32 = 0;
                let assoc_ret: i32 = 0;
                let assoc_rnlen: i32 = 0;
                let assoc_rnm: u8[128] = [];
                while (assoc_ai < num_args) {
                  let assoc_param: i32 = pipeline_module_func_param_type_ref_at(module, assoc_uj, assoc_ai);
                  let assoc_arg: i32 = pipeline_expr_method_call_arg_ref(arena, expr_ref, assoc_ai);
                  let assoc_arg_ty: i32 = 0;
                  if (assoc_arg > 0 && assoc_param > 0) {
                    typeck_coerce_init_array_vector_lit_to_decl(module, arena, assoc_arg, assoc_param,
                    pipeline_type_kind_ord_at(arena, assoc_param),
                    pipeline_expr_kind_ord_at(arena, assoc_arg));
                    typeck_coerce_array_lit_struct_elems_to_decl(module, arena, assoc_arg, assoc_param);
                    typeck_coerce_init_struct_lit_to_decl(module, arena, assoc_arg, assoc_param);
                    assoc_arg_ty = pipeline_expr_resolved_type_ref(arena, assoc_arg);
                  }
                  if (assoc_param <= 0 || assoc_arg_ty <= 0
                      || pipeline_typeck_type_refs_equal_c(arena, assoc_arg_ty, assoc_param) == 0) {
                    assoc_matched = 0;
                    assoc_ai = num_args;
                  } else {
                    assoc_score = assoc_score + 1000;
                    assoc_ai = assoc_ai + 1;
                  }
                }
                if (assoc_matched != 0) {
                  assoc_ret = pipeline_module_func_return_type_at(module, assoc_uj);
                  if (assoc_ret > 0 && pipeline_type_kind_ord_at(arena, assoc_ret) == 8) {
                    assoc_rnlen = pipeline_type_named_name_into(arena, assoc_ret, &assoc_rnm[0]);
                    if (assoc_rnlen == assoc_nlen && assoc_rnlen > 0) {
                      let assoc_eq: i32 = 1;
                      let assoc_bi: i32 = 0;
                      while (assoc_bi < assoc_rnlen) {
                        if (assoc_rnm[assoc_bi] != base_nm[assoc_bi]) {
                          assoc_eq = 0;
                          assoc_bi = assoc_rnlen;
                        } else {
                          assoc_bi = assoc_bi + 1;
                        }
                      }
                      if (assoc_eq != 0) {
                        assoc_score = assoc_score + 100;
                      }
                    }
                  }
                  if (assoc_score > assoc_best_score) {
                    assoc_best_score = assoc_score;
                    assoc_best = assoc_uj;
                  }
                }
              }
            }
            assoc_uj = assoc_uj + 1;
          }
          if (assoc_best >= 0) {
            let assoc_ok_ret: i32 = pipeline_module_func_return_type_at(module, assoc_best);
            if (assoc_ok_ret > 0) {
              pipeline_expr_apply_call_resolve(arena, expr_ref, 0 - 1, assoc_best);
              pipeline_expr_set_resolved_type_ref(arena, expr_ref, assoc_ok_ret);
              /* is_method=0: extra i maps to param i (no implicit self). */
              typeck_stamp_resolved_args_float_lit(arena, expr_ref, module, assoc_best, 0 - 1, ctx, 0);
              return 0;
            }
          }
        }
      }
    }
    if (base_rc != 0) {
      return 0 - 1;
    }

    /* LANG-004: no impl for type with method */
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    z = 0;
    while (z < 256) {
      msg[z] = 0;
      z = z + 1;
    }
    p = typeck_diag_append_lit(&msg[0], 0, 255, "no impl for type with method ", 29);
    p = typeck_diag_append_lit(&msg[0], p, 255, &method_nm[0], method_nlen);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

/**
 * Return 1 when ty_ref is a cast-eligible class for `expr as T` (wave659).
 * Eligible: first-class integers/bool, floats, pointers, TYPE_FN (opaque Cap-fn-ptr),
 * NAMED integer spellings (i8/i16/u16 via int_family), and TYPE_NAMED enum/alias-of-scalar
 * (non-struct).
 * Ineligible: ARRAY/SLICE/LINEAR/VECTOR/struct layouts (via aggregate helper).
 * @param module *Module — struct layout table for named aggregate detection
 * @param arena *ASTArena — type arena
 * @param ty_ref i32 — source or target type of an `as` cast
 * @return i32 — 1 ok class, 0 ineligible or null/unknown
 * PLATFORM: SHARED — G.7 helper for typeck_as_cast_allowed only.
 */
export function typeck_as_cast_type_class_ok(module: *Module, arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_bool: i32 = 1;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_void: i32 = 16;
    let ko: i32 = 0;
    let rty: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ast.ref_is_null(ty_ref)) {
      return 0;
    }
    /* Aggregate (struct/array/slice/vector/linear) never participates in `as`. */
    if (typeck_type_is_aggregate_cmp_operand(module, arena, ty_ref) != 0) {
      return 0;
    }
    rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
    if (ast.ref_is_null(rty)) {
      rty = ty_ref;
    }
    ko = pipeline_type_kind_ord_at(arena, rty);
    if (ko == ord_void) {
      return 0;
    }
    /* First-class ints / bool / float / ptr / TYPE_FN (opaque Cap-fn-ptr ABI). */
    if (ko == ord_bool || ko == ord_ptr || ko == ord_f32 || ko == ord_f64
        || ko == TypeKind.TYPE_FN as i32) {
      return 1;
    }
    if (typeck_int_family_id(arena, rty) >= 0) {
      return 1;
    }
    /* TYPE_NAMED non-struct (enum tags / non-layout names) stay castable like C enums. */
    if (ko == ord_named) {
      return 1;
    }
    return 0;
  }
}

/**
 * Return 1 when `src as tgt` is a legal cast (wave659 Cap residual).
 * Allowed: same type; numeric↔numeric (int/bool/float family); int↔ptr; ptr↔ptr;
 * Cap/TYPE_FN opaque fn-ptr surface ↔ Cap/TYPE_FN (`as function(...)` / `as *u8`);
 * enum-like NAMED↔integer; `[N]T as []T` (equal elems, reuse typeck_array_to_slice_ok);
 * same-type ARRAY/SLICE ascription. Rejected: other aggregates; float↔ptr; void;
 * int↔TYPE_FN (not Cap surface).
 * @param module *Module
 * @param arena *ASTArena
 * @param src_ty i32 — resolved type of cast operand
 * @param tgt_ty i32 — cast target type ref
 * @return i32 — 1 allowed, 0 illegal
 * PLATFORM: SHARED — single authority for typeck_check_expr_as.
 */
export function typeck_as_cast_allowed(module: *Module, arena: *ASTArena, src_ty: i32,
tgt_ty: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_bool: i32 = 1;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let sk: i32 = 0;
    let tk: i32 = 0;
    let s_int: i32 = 0;
    let t_int: i32 = 0;
    let s_float: i32 = 0;
    let t_float: i32 = 0;
    let s_num: i32 = 0;
    let t_num: i32 = 0;
    let src_r: i32 = 0;
    let tgt_r: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena) {
      return 0;
    }
    if (ast.ref_is_null(src_ty) || ast.ref_is_null(tgt_ty)) {
      return 0;
    }
    /*
     * `[N]T as []T` / same-type ARRAY|SLICE ascription.
     * wave659 class_ok rejects every aggregate to stop `arr as i32` false-green.
     * `[10,32] as []i32` is the existing array→slice coerce, not a numeric cast.
     * Check these first. G.7: reuse typeck_array_to_slice_ok + type_refs_equal.
     * Do not stamp the operand (emit wrap keys off TYPE_ARRAY), same as return.
     * PLATFORM: SHARED typeck.
     */
    if (typeck_array_to_slice_ok(arena, src_ty, tgt_ty) != 0) {
      return 1;
    }
    if (type_refs_equal(arena, src_ty, tgt_ty)) {
      let sk0: i32 = pipeline_type_kind_ord_at(arena, src_ty);
      if (sk0 == 10 || sk0 == 11) {
        return 1;
      }
    }
    /*
     * 10.3.1: Cap *u8 / TYPE_FN opaque fn-ptr surface ↔ surface (`as function(...)`).
     * Both TYPE_FN → structural sig. Cap↔TYPE_FN soft here; bare-fn recover in
     * typeck_check_expr_as via typeck_fnptr_surface_compat. PLATFORM: SHARED.
     */
    if (typeck_is_fnptr_surface(arena, src_ty) != 0
        && typeck_is_fnptr_surface(arena, tgt_ty) != 0) {
      let sk_fn: i32 = pipeline_type_kind_ord_at(arena, src_ty);
      let tk_fn: i32 = pipeline_type_kind_ord_at(arena, tgt_ty);
      if (sk_fn == TypeKind.TYPE_FN as i32 && tk_fn == TypeKind.TYPE_FN as i32) {
        return typeck_fn_type_sig_equal(arena, src_ty, tgt_ty);
      }
      return 1;
    }
    if (typeck_as_cast_type_class_ok(module, arena, src_ty) == 0
    || typeck_as_cast_type_class_ok(module, arena, tgt_ty) == 0) {
      return 0;
    }
    src_r = typeck_resolve_type_alias_ref_local(module, arena, src_ty, 0);
    if (ast.ref_is_null(src_r)) {
      src_r = src_ty;
    }
    tgt_r = typeck_resolve_type_alias_ref_local(module, arena, tgt_ty, 0);
    if (ast.ref_is_null(tgt_r)) {
      tgt_r = tgt_ty;
    }
    if (type_refs_equal(arena, src_r, tgt_r)) {
      return 1;
    }
    sk = pipeline_type_kind_ord_at(arena, src_r);
    tk = pipeline_type_kind_ord_at(arena, tgt_r);
    s_int = 0;
    t_int = 0;
    if (typeck_int_family_id(arena, src_r) >= 0 || sk == ord_bool || sk == ord_named) {
      s_int = 1;
    }
    if (typeck_int_family_id(arena, tgt_r) >= 0 || tk == ord_bool || tk == ord_named) {
      t_int = 1;
    }
    s_float = 0;
    t_float = 0;
    if (sk == ord_f32 || sk == ord_f64) {
      s_float = 1;
    }
    if (tk == ord_f32 || tk == ord_f64) {
      t_float = 1;
    }
    /* float ↔ pointer is illegal in C and here (host-cc BLD001 soft residual). */
    if ((s_float != 0 && tk == ord_ptr) || (t_float != 0 && sk == ord_ptr)) {
      return 0;
    }
    s_num = 0;
    t_num = 0;
    if (s_int != 0 || s_float != 0) {
      s_num = 1;
    }
    if (t_int != 0 || t_float != 0) {
      t_num = 1;
    }
    /* numeric ↔ numeric (int/bool/float/enum-like). */
    if (s_num != 0 && t_num != 0) {
      return 1;
    }
    /* integer ↔ pointer (kernel MMIO / address casts). */
    if ((s_int != 0 && tk == ord_ptr) || (t_int != 0 && sk == ord_ptr)) {
      return 1;
    }
    /* pointer ↔ pointer (reinterpret pointee). */
    if (sk == ord_ptr && tk == ord_ptr) {
      return 1;
    }
    return 0;
  }
}

/**
 * Type-check `operand as TargetType`. Stamps resolved type to target on success.
 * wave659: hard-fail illegal casts (aggregate-to-scalar / float↔ptr / void)
 * instead of stamping target and leaving host-cc BLD001 or silent false green.
 * `[N]T as []T` / same-type ARRAY|SLICE ascription is allowed (reuse
 * typeck_array_to_slice_ok); operand stays TYPE_ARRAY so emit can wrap.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_AS
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 hard fail
 * PLATFORM: SHARED — seed typeck_gen + empty_surface same commit.
 */
export function typeck_check_expr_as(module: *Module, arena: *ASTArena, expr_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let op_ref: i32 = pipeline_expr_as_operand_ref_at(arena, expr_ref);
    let tgt: i32 = pipeline_expr_as_target_type_ref_at(arena, expr_ref);
    let src_ty: i32 = 0;
    let line_as: i32 = 0;
    let col_as: i32 = 0;
    if (!ast.ref_is_null(op_ref) && check_expr(module, arena, op_ref, 0, ctx) != 0) {
      return - 1;
    }
    /*
     * wave659 Cap residual: hard-fail illegal `as` at typeck.
     * Root cause: typeck_check_expr_as only checked the operand then stamped tgt →
     * struct/array `as i32` false green; float→ptr host-cc BLD001.
     * G.7: typeck_as_cast_allowed + typeck_type_is_aggregate_cmp_operand (wave657).
     * Legal: numeric↔numeric, int↔ptr, ptr↔ptr, enum-like NAMED↔int (docs MMIO).
     * PLATFORM: SHARED — seed typeck_gen + empty_surface + diagnostic twin same commit.
     */
    if (!ast.ref_is_null(op_ref) && !ast.ref_is_null(tgt)) {
      src_ty = pipeline_expr_resolved_type_ref(arena, op_ref);
      if (!ast.ref_is_null(src_ty) && typeck_as_cast_allowed(module, arena, src_ty, tgt) == 0) {
        line_as = pipeline_expr_line_at(arena, expr_ref);
        col_as = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_as_cast(line_as, col_as);
        return -1;
      }
      /*
       * 10.3.1 signature: Cap bare fn `as function(...)` — recoverable Cap hard
       * sig check; true opaque Cap allowed only here (allow_opaque=1).
       * G.7 typeck_fnptr_surface_compat. PLATFORM: SHARED.
       */
      if (!ast.ref_is_null(src_ty)
          && typeck_is_fnptr_surface(arena, src_ty) != 0
          && typeck_is_fnptr_surface(arena, tgt) != 0
          && typeck_fnptr_surface_compat(module, arena, tgt, src_ty, op_ref, 1) == 0) {
        line_as = pipeline_expr_line_at(arena, expr_ref);
        col_as = pipeline_expr_col_at(arena, expr_ref);
        driver_diagnostic_typeck_invalid_as_cast(line_as, col_as);
        return -1;
      }
      /*
       * ARRAY_LIT as []T: stamp the lit SLICE so emit_expr(ARRAY_LIT) takes
       * the existing durable-fat path (let `x: []T = [lit]`). VAR/FIELD stay
       * TYPE_ARRAY — return/assign wrap keys off that (do not stamp).
       * G.7: reuse typeck_coerce_init_slice_from_array. PLATFORM: SHARED.
       */
      if (pipeline_expr_kind_ord_at(arena, op_ref) == 46
          && typeck_array_to_slice_ok(arena, src_ty, tgt) != 0) {
        typeck_coerce_init_slice_from_array(arena, op_ref, tgt, 11);
      }
    }
    if (!ast.ref_is_null(tgt)) {
      pipeline_expr_set_resolved_type_ref(arena, expr_ref, tgt);
    }
    return 0;
  }
}

/**
 * EXPR_STRUCT_LIT field init check (recursive step; avoid while+check_expr EMIT_HEAVY SIGSEGV).
 * PLATFORM: SHARED — field inits must NOT inherit the outer function/return expected type.
 * Passing the callee return (e.g. Vec_i32) into heap.default_alloc() as expected ret polluted
 * overload pick (METHOD_CALL expected_ret slot) → soft XT001 on freestanding co-emit new().
 * Check with expected=0; layout coerce stamps field types after ensure_struct_layout.
 * return_type_ref param kept for call-site API stability; unused for field init expected.
 */
export function typeck_check_expr_struct_lit_field(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, field_i: i32, num_fields: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let init_sl: i32 = 0;
    let no_expected: i32 = 0;
    if (field_i >= num_fields) {
      return 0;
    }
    init_sl = pipeline_expr_struct_lit_init_ref(arena, expr_ref, field_i);
    /* expected=0: do not pass outer function return type into field METHOD_CALL/CALL. */
    if (!ast.ref_is_null(init_sl) && check_expr(module, arena, init_sl, no_expected, ctx) != 0) {
      return - 1;
    }
    return typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx,
    field_i + 1, num_fields);
  }
}

/**
 * Coerce STRUCT_LIT field inits to layout field types and hard-fail mismatches.
 * wave672 Cap residual: prior path called typeck_coerce_init_expr_to_decl (incl.
 * LANG-006 bool→int) and never checked field types → `S { v: true }` / `v: 1.0 as f32`
 * for `v: i32` false-green. G.7: reuse lit/float/enum/array/int_binop/slice coerces
 * only — **not** bool→int (LANG-006 is scalar let/const only). Then require equal /
 * integer_widen / float_widen; emit assign_mismatch on known mismatch.
 * wave682 Cap residual: layout field types may be free type-params (`v: T`). When
 * expected/base is monomorphized (`Wrap<i32>`), substitute via
 * typeck_mono_field_type_from_base before coerce (was expected T, found i32).
 * @param module *Module — layout table
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_STRUCT_LIT
 * @param base_ty i32 — expected/mono base type (let/return `Wrap<i32>`), or 0
 * @return i32 — 0 ok, -1 field type mismatch (diagnostic emitted)
 * PLATFORM: SHARED typeck
 */
export function typeck_coerce_struct_lit_field_inits_to_layout(module: *Module, arena: *ASTArena,
expr_ref: i32, base_ty: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_fields: i32 = 0;
    let name_len: i32 = 0;
    let j: i32 = 0;
    let flen: i32 = 0;
    let init_r: i32 = 0;
    let ftr: i32 = 0;
    let ftr_mono: i32 = 0;
    let ftr_kind: i32 = 0;
    let init_kind: i32 = 0;
    let init_ty: i32 = 0;
    let got_kind: i32 = 0;
    let crc: i32 = 0;
    let mono_base: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    let err_line: i32 = 0;
    let err_col: i32 = 0;
    let name_buf: *u8 = typeck_scratch64_slot(4);
    let field_buf: *u8 = typeck_scratch64_slot(5);
    if (expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref);
    name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref);
    if (num_fields <= 0 || name_len <= 0 || name_len > 127) {
      return 0;
    }
    pipeline_expr_struct_lit_type_name_into(arena, expr_ref, name_buf);
    /*
     * wave682: mono base from expected let/return type when it names the same
     * generic struct (Wrap / Pair). PTR peel is inside mono helper.
     */
    mono_base = 0;
    if (!ast.ref_is_null(base_ty) && base_ty > 0 && base_ty <= arena.num_types) {
      if (typeck_named_type_matches_name_or_alias(module, arena, base_ty, name_buf, name_len, 0)) {
        mono_base = base_ty;
      } else {
        let peel: i32 = pipeline_type_elem_ref_at(arena, base_ty);
        if (!ast.ref_is_null(peel) && peel > 0
        && typeck_named_type_matches_name_or_alias(module, arena, peel, name_buf, name_len, 0)) {
          mono_base = peel;
        }
      }
    }
    while (j < num_fields) {
      flen = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j);
      /* wave583 Cap residual: struct-lit field name content ≤127. */
      if (flen > 0 && flen <= 127) {
        pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_buf);
        ftr = get_field_type_ref_from_layout(module, name_buf, name_len, field_buf, flen);
        init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j);
        if (!ast.ref_is_null(init_r) && init_r > 0 && init_r <= arena.num_exprs
        && !ast.ref_is_null(ftr) && ftr > 0) {
          /*
           * wave682: substitute free type-param field types (T/U) from mono base.
           * Layout stores `v: T`; expected Wrap<i32> → ftr becomes i32.
           */
          if (mono_base > 0) {
            ftr_mono = typeck_mono_field_type_from_base(module, arena, ftr, mono_base);
            if (ftr_mono > 0) {
              ftr = ftr_mono;
            }
          }
          /*
           * wave672: field-level coerce without LANG-006 bool→int (scalar let/const only).
           * Reuse G.7 authorities per case; array-lit return -1 propagates.
           */
          ftr_kind = pipeline_type_kind_ord_at(arena, ftr);
          init_kind = pipeline_expr_kind_ord_at(arena, init_r);
          typeck_coerce_init_lit_to_decl(arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_float_lit_to_decl(arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_enum_field_to_decl(module, arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_named_call_to_decl(arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_resolved_alias_to_decl(module, arena, init_r, ftr, ftr_kind);
          crc = typeck_coerce_init_array_vector_lit_to_decl(module, arena, init_r, ftr, ftr_kind, init_kind);
          if (crc < 0) {
            return -1;
          }
          /* STRUCT_LIT field ARRAY_LIT `{ one: [{ h: { v: a } }] }`:
           * array coerce stamps the ARRAY_LIT dest type but used to skip
           * STRUCT_LIT elems. Let dest / dest-in-rbx / sret all emit 8B
           * (Darwin leftover 12/13). G.7: same dest-stamp as let
           * `let r: [1]Wrap = [{ … }]`.
           * PLATFORM: SHARED — STRUCT_LIT field ARRAY_LIT of nest. */
          if (init_kind == 46) {
            typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_r, ftr);
          }
          typeck_coerce_init_vector_binop_to_decl(arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_int_binop_to_decl(arena, init_r, ftr, ftr_kind, init_kind);
          typeck_coerce_init_slice_from_array(arena, init_r, ftr, ftr_kind);
          /* Nested STRUCT_LIT field `{ h: { v: a } }`: same dest backfill
           * as let / call-arg. Prior list omitted struct_lit_to_decl so
           * the inner lit had no name and emit stored 8B (Darwin 12/108).
           * Coerce stamps ftr; skip the type_refs_equal gate (layout vs
           * decl Holder can be distinct pool refs).
           * PLATFORM: SHARED — G.7 complete field dest coerce. */
          crc = typeck_coerce_init_struct_lit_to_decl(module, arena, init_r, ftr);
          init_ty = expr_type_ref(arena, init_r);
          if (crc != 0) {
            pipeline_expr_set_resolved_type_ref(arena, init_r, ftr);
          } else if (!ast.ref_is_null(init_ty) && init_ty > 0) {
            got_kind = pipeline_type_kind_ord_at(arena, init_ty);
            if (type_refs_equal(arena, ftr, init_ty)
            || typeck_integer_widen_ok_refs(arena, ftr, init_ty)
            || typeck_float_widen_ok(ftr_kind, got_kind)
            || typeck_fnptr_surface_compat(module, arena, ftr, init_ty, init_r, 0) != 0) {
              pipeline_expr_set_resolved_type_ref(arena, init_r, ftr);
            } else {
              eb = driver_typeck_diag_scratch_expect();
              gb = driver_typeck_diag_scratch_found();
              el = typeck_diag_fmt_type_into(arena, ftr, eb, 96);
              gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96);
              err_line = pipeline_expr_line_at(arena, init_r);
              err_col = pipeline_expr_col_at(arena, init_r);
              driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl);
              return -1;
            }
          }
        }
      }
      j = j + 1;
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_expr_struct_lit(
  module: *Module, 
  arena: *ASTArena, 
  expr_ref: i32,
  return_type_ref: i32, 
  ctx: *PipelineDepCtx): i32 
{
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_fields: i32 = pipeline_expr_struct_lit_num_fields(arena, expr_ref);
    let name_len: i32 = 0;
    let name_buf: u8[128] = [];
    let tr: i32 = 0;
    let ord_named: i32 = 8;
    name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref);
    /**
     * LANG-009: named `Type { fields }` / `Type<Args> { fields }` (parse-mangled
     * to Type_Args) are values again. Anonymous `{ fields }` with dest type still
     * preferred for AI-facing lets; both forms must typeck.
     * Prior ban soft-dropped LANG-009/010 goldens (expected "{ fields }", found Name).
     * PLATFORM: SHARED — G.7 restore named path below (ensure layout + resolve).
     */
    if (typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx, 0,
    num_fields) != 0) {
      return - 1;
    }
    if (name_len <= 0) {
      /* Anonymous struct literal `{ field: expr, ... }`: backfill struct_lit_struct_name
       * from contextual return_type_ref so codegen emits `(struct <module>_Pair){...}`
       * instead of `(struct <module>_){...}` (incomplete type cc error). Resolve type
       * alias to reach the underlying NAMED struct type. PLATFORM: SHARED. */
      if (!ast.ref_is_null(return_type_ref)
      && pipeline_type_kind_ord_at(arena, return_type_ref) == ord_named) {
        let resolved_ref: i32 = typeck_resolve_type_alias_ref_local(module, arena, return_type_ref, 0);
        if (!ast.ref_is_null(resolved_ref)
        && pipeline_type_kind_ord_at(arena, resolved_ref) == ord_named) {
          let backfill_name: u8[128] = [];
          let backfill_len: i32 = pipeline_type_named_name_into(arena, resolved_ref, &backfill_name[0]);
          /* wave583 Cap residual: anonymous struct-lit type name backfill ≤127. */
          if (backfill_len > 0 && backfill_len <= 127) {
            /* Why setter (not get_copy/set_copy): avoids returning the ~400-byte ast.Expr
             * by value across the X-ABI boundary (sret mismatch → SIGBUS on arm64). */
            pipeline_expr_struct_lit_type_name_set(arena, expr_ref, &backfill_name[0], backfill_len);
          }
        }
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
      }
      /* After dest-name backfill the lit is named. Named path already
       * runs ensure + field_inits_to_layout (nested STRUCT_LIT dest).
       * Anonymous used to return here so `{ h: { v: a } }` never stamped
       * the inner Holder lit. Assign `*p = { h: { v: a } }` only
       * check_expr's the RHS — no later coerce_init_expr_to_decl.
       * PLATFORM: SHARED — same field_inits authority as named path. */
      name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref);
      if (name_len > 0) {
        if (ensure_struct_layout_from_struct_lit(module, arena, expr_ref) != 0) {
          return 0 - 1;
        }
        if (typeck_coerce_struct_lit_field_inits_to_layout(module, arena, expr_ref, return_type_ref) != 0) {
          return 0 - 1;
        }
      }
      return 0;
    }
    if (ensure_struct_layout_from_struct_lit(module, arena, expr_ref) != 0) {
      return - 1;
    }
    /* wave672/682: field coerce + mono type-param fields + hard-fail mismatch. */
    if (typeck_coerce_struct_lit_field_inits_to_layout(module, arena, expr_ref, return_type_ref) != 0) {
      return -1;
    }
    if (name_len > 127) {
      return 0;
    }
    pipeline_expr_struct_lit_type_name_into(arena, expr_ref, &name_buf[0]);
    tr = find_or_alloc_named_type_ref(arena, &name_buf[0], name_len);
    if (tr != 0) {
      if (!ast.ref_is_null(return_type_ref)
      && pipeline_type_kind_ord_at(arena, return_type_ref) == ord_named
      && typeck_named_type_matches_name_or_alias(module, arena, return_type_ref, &name_buf[0], name_len, 0)) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
      } else {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, tr);
      }
    }
    return 0;
  }
}

/**
 * Resolve element type of a SIMD vector type for INDEX `v[i]`.
 * TYPE_VECTOR uses elem_type_ref; TYPE_NAMED spellings (i32x4/u32x8/f32x4/…)
 * often have empty elem_ref — map prefix to a primitive via ensure_*.
 * Returns 0 if not a vector-like type.
 * PLATFORM: SHARED — pairs with typeck_vector_lanes_of_type (NAMED residual).
 */
export function typeck_vector_elem_type_ref(arena: *ASTArena, type_ref: i32): i32 {
  // PLATFORM: SHARED — vector lane element for INDEX / CTFE.
  unsafe {
    let ord_type_vector: i32 = 13;
    let ord_type_named: i32 = 8;
    let tk: i32 = 0;
    let er: i32 = 0;
    let nm: u8[128] = [];
    let nlen: i32 = 0;
    if (ast.ref_is_null(type_ref) || type_ref <= 0) {
      return 0;
    }
    if (typeck_vector_lanes_of_type(arena, type_ref) <= 0) {
      return 0;
    }
    tk = pipeline_type_kind_ord_at(arena, type_ref);
    er = pipeline_type_elem_ref_at(arena, type_ref);
    if (!ast.ref_is_null(er) && er > 0 && er <= arena.num_types) {
      return er;
    }
    if (tk == ord_type_vector) {
      /* No elem stamp: default i32 lane (i32xN product default). */
      return ensure_i32_type_ref(arena);
    }
    if (tk != ord_type_named) {
      return 0;
    }
    nlen = pipeline_type_named_name_into(arena, type_ref, &nm[0]);
    if (nlen <= 0) {
      return ensure_i32_type_ref(arena);
    }
    /* f32x* / f64x* first (overlap with *32 / *64 digit patterns). */
    if (nlen >= 3 && nm[0] == 102 && nm[1] == 51 && nm[2] == 50) {
      return ensure_f32_type_ref(arena);
    }
    if (nlen >= 3 && nm[0] == 102 && nm[1] == 54 && nm[2] == 52) {
      return ensure_f64_type_ref(arena);
    }
    /* Product aliases: Vec4f → f32 (≡ glue_vector_elem_is_f32_c). */
    if (nlen == 5 && nm[0] == 86 && nm[1] == 101 && nm[2] == 99 && nm[3] == 52 && nm[4] == 102) {
      return ensure_f32_type_ref(arena);
    }
    if (nlen >= 3 && nm[0] == 105 && nm[1] == 54 && nm[2] == 52) {
      return ensure_i64_type_ref(arena);
    }
    if (nlen >= 3 && nm[0] == 117 && nm[1] == 54 && nm[2] == 52) {
      return typeck_ensure_primitive_by_kind_ord(arena, 4); /* TYPE_U64 */
    }
    if (nlen >= 3 && nm[0] == 117 && nm[1] == 51 && nm[2] == 50) {
      return typeck_ensure_primitive_by_kind_ord(arena, 3); /* TYPE_U32 */
    }
    if (nlen >= 2 && nm[0] == 117 && nm[1] == 56) {
      return ensure_u8_type_ref(arena);
    }
    /* i32x* / Vec8i / residual → i32 */
    return ensure_i32_type_ref(arena);
  }
}

/**
 * True when ty_ref is a legal INDEX subscript (integer-like).
 * First-class ints (i32/u8/u32/u64/i64/usize/isize) and non-struct TYPE_NAMED
 * (i8/i16/u16 aliases, enum tags) are ok. Rejects bool/ptr/float/aggregate/void.
 * Soft: unknown/null ty_ref returns 1 so incomplete resolve is not a hard leaf.
 * @param module *Module — for struct-layout NAMED check (via aggregate helper)
 * @param arena *ASTArena — type pool
 * @param ty_ref i32 — resolved type of the index expression
 * @return i32 — 1 allowed (or soft-unknown), 0 hard-reject
 * PLATFORM: SHARED — wave664 Cap residual; G.7 single helper for INDEX index gate.
 */
export function typeck_type_is_valid_subscript_index(module: *Module, arena: *ASTArena, ty_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_i32: i32 = 0;
    let ord_bool: i32 = 1;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_named: i32 = 8;
    let rty: i32 = 0;
    let ko: i32 = 0;
    if (arena == 0 as *ASTArena || ast.ref_is_null(ty_ref) || ty_ref <= 0) {
      return 1;
    }
    /* Peel aliases so `type Idx = i32` stays integer-like. */
    rty = ty_ref;
    if (module != 0 as *Module) {
      rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0);
      if (ast.ref_is_null(rty) || rty <= 0) {
        rty = ty_ref;
      }
    }
    ko = pipeline_type_kind_ord_at(arena, rty);
    if (ko == ord_i32 || ko == ord_u8 || ko == ord_u32 || ko == ord_u64 || ko == ord_i64
    || ko == ord_usize || ko == ord_isize) {
      return 1;
    }
    if (ko == ord_named) {
      /* Enum / i8/i16/u16 aliases: allow. Product struct layouts: reject. */
      if (typeck_type_is_aggregate_cmp_operand(module, arena, rty) != 0) {
        return 0;
      }
      return 1;
    }
    /* bool, ptr, float, array/slice/vector/linear, void, other: hard reject. */
    if (ko == ord_bool) {
      return 0;
    }
    return 0;
  }
}

/**
 * Type-check EXPR_INDEX: base must be array/slice/ptr/vector; index must be integer-like.
 * Accepts TYPE_ARRAY / SLICE / PTR / VECTOR and TYPE_NAMED SIMD spellings (i32x4…).
 * wave664 Cap residual: hard-fail non-integer index (ptr/float/struct/bool) that
 * formerly passed typeck then host-cc BLD001 or freestanding silent false green.
 * wave699: index ambient is i32, NOT outer return_type_ref. Outer *T (e.g. let p: *u8 =
 * &buf[0]) must not contextual-type the lit index as pointer — that false-T001
 * red'd ptr_arith_i32 and all &arr[lit] under L4 cold product.
 * @param module *Module — current module
 * @param arena *ASTArena — expr/type pool
 * @param expr_ref i32 — EXPR_INDEX
 * @param return_type_ref i32 — ambient for base only (INDEX result type is elem)
 * @param ctx *PipelineDepCtx — typeck context
 * @return i32 — 0 ok, -1 hard fail
 * PLATFORM: SHARED — product INDEX path for vector lane extract (WPO-S2 lane0).
 */
export function typeck_check_expr_index(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_lit: i32 = 0;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_vector: i32 = 13;
    let base_ref: i32 = pipeline_expr_index_base_ref(arena, expr_ref);
    let index_ref: i32 = pipeline_expr_index_index_ref(arena, expr_ref);
    let line: i32 = pipeline_expr_line_at(arena, expr_ref);
    let col: i32 = pipeline_expr_col_at(arena, expr_ref);
    let base_ty: i32 = 0;
    let bt_kind: i32 = 0;
    let elem_ty: i32 = 0;
    let array_sz: i32 = 0;
    let vec_lanes: i32 = 0;
    let is_vec_base: i32 = 0;
    let index_ty: i32 = 0;
    // Index ambient: always integer-like (i32). Do not pass outer return_type_ref.
    let idx_ambient: i32 = ensure_i32_type_ref(arena);
    if (check_expr(module, arena, base_ref, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (check_expr(module, arena, index_ref, idx_ambient, ctx) != 0) {
      return - 1;
    }
    if (ast.ref_is_null(base_ref) || base_ref <= 0 || base_ref > arena.num_exprs) {
      return 0;
    }
    base_ty = pipeline_expr_resolved_type_ref(arena, base_ref);
    if (ast.ref_is_null(base_ty) || base_ty <= 0 || base_ty > arena.num_types) {
      driver_diagnostic_typeck_subscript_base(line, col);
      return - 1;
    }
    bt_kind = pipeline_type_kind_ord_at(arena, base_ty);
    vec_lanes = typeck_vector_lanes_of_type(arena, base_ty);
    is_vec_base = 0;
    if (bt_kind == ord_vector || vec_lanes > 0) {
      is_vec_base = 1;
    }
    if (bt_kind != ord_array && bt_kind != ord_slice && bt_kind != ord_ptr && is_vec_base == 0) {
      driver_diagnostic_typeck_subscript_base(line, col);
      return - 1;
    }
    /*
     * wave664: hard-fail non-integer index after index expr is type-checked.
     * Soft-skip unknown index_ty (<=0) inside helper; known bad kinds → T001.
     */
    if (!ast.ref_is_null(index_ref) && index_ref > 0 && index_ref <= arena.num_exprs) {
      index_ty = pipeline_expr_resolved_type_ref(arena, index_ref);
      if (typeck_type_is_valid_subscript_index(module, arena, index_ty) == 0) {
        driver_diagnostic_typeck_subscript_index(line, col);
        return - 1;
      }
    }
    if (is_vec_base != 0) {
      elem_ty = typeck_vector_elem_type_ref(arena, base_ty);
    } else {
      elem_ty = pipeline_type_elem_ref_at(arena, base_ty);
    }
    if (ast.ref_is_null(elem_ty) || elem_ty <= 0) {
      driver_diagnostic_typeck_subscript_base(line, col);
      return - 1;
    }
    pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty);
    if (bt_kind == ord_slice) {
      pipeline_expr_set_index_base_is_slice(arena, expr_ref, 1);
    } else {
      pipeline_expr_set_index_base_is_slice(arena, expr_ref, 0);
    }
    if (!ast.ref_is_null(index_ref) && index_ref > 0 && index_ref <= arena.num_exprs) {
      if (pipeline_expr_kind_ord_at(arena, index_ref) == ord_lit &&
      pipeline_expr_int_val_at(arena, index_ref) == 0 && (bt_kind == ord_array || is_vec_base != 0)) {
        array_sz = pipeline_type_array_size_at(arena, base_ty);
        if (array_sz < 1 && vec_lanes > 0) {
          array_sz = vec_lanes;
        }
        if (array_sz >= 1) {
          pipeline_expr_set_index_proven_in_bounds(arena, expr_ref, 1);
        }
      }
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_expr_is_any_assign_kind(kind_ord: i32): bool {
  let ord_assign: i32 = 28;
  let ord_add_assign: i32 = 29;
  let ord_shr_assign: i32 = 38;
  if (kind_ord == ord_assign) {
    return true;
  }
  if (kind_ord >= ord_add_assign && kind_ord <= ord_shr_assign) {
    return true;
  }
  return false;
}

/**
 * Recursively type-check every element of an ARRAY_LIT.
 * Prior: check_expr fell through for kind=46 without visiting children, so nested
 * INDEX never ran typeck_check_expr_index → index_base_is_slice stayed 0 and host-C
 * emitted `(slice_var)[i]` (invalid for by-value fat) instead of `.data[i]`.
 * wave611: when the literal still has no resolved type after elems (no let/return
 * ambient), infer TYPE_ARRAY from homogeneous element types so rvalues like
 * `[10, 32][1]` pass typeck_check_expr_index. Let/return still overwrite via
 * typeck_coerce_array_lit_elem_types_to_decl (wave328/333).
 * @param module *Module — current module
 * @param arena *ASTArena — expr/type pool
 * @param expr_ref i32 — EXPR_ARRAY_LIT (kind 46); other kinds return 0
 * @param return_type_ref i32 — ambient dest; ARRAY/SLICE peel elem dest for
 *   nested check_expr (STRUCT_LIT elems `{ h: { v: a } }`); SIMD stamps outer only
 * @param ctx *PipelineDepCtx — typeck context
 * @return i32 — 0 on success, -1 if any element fails typeck
 * PLATFORM: SHARED — wave407 Cap residual pure; wave611 untyped ARRAY_LIT infer
 */
export function typeck_check_expr_array_lit(module: *Module, arena: *ASTArena, expr_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_expr_array_lit: i32 = 46;
    let num_elems: i32 = 0;
    let i: i32 = 0;
    let elem_ref: i32 = 0;
    let already: i32 = 0;
    let elem_ty: i32 = 0;
    let ok_inf: i32 = 1;
    let j: i32 = 0;
    let er: i32 = 0;
    let et: i32 = 0;
    let arr_ty: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, expr_ref) != ord_expr_array_lit) {
      return 0;
    }
    num_elems = pipeline_expr_array_lit_num_elems_at(arena, expr_ref);
    /*
     * wave705: ambient SIMD/VECTOR stamps the array lit; elems use ambient 0.
     * PLATFORM: SHARED — unblocks `let c: i32x4 = [1,2,3,4] + [10,…]`.
     */
    if (return_type_ref > 0 && num_elems > 0) {
      let amb_lanes: i32 = typeck_vector_lanes_of_type(arena, return_type_ref);
      let amb_kind: i32 = pipeline_type_kind_ord_at(arena, return_type_ref);
      if (amb_lanes <= 0 && amb_kind == 13) {
        amb_lanes = pipeline_type_array_size_at(arena, return_type_ref);
      }
      if (amb_lanes > 0 && amb_lanes == num_elems) {
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref);
      }
    }
    /*
     * ARRAY/SLICE dest (`return [{ h: { v: a } }]` / `*p = [{ … }]`): peel
     * the element dest and pass it into check_expr. Nested STRUCT_LIT elems
     * used expected=0 so inner `{ v: a }` never got Holder dest (Darwin 12).
     * SIMD ambient stays 0 on elems (lane stamp is coerce, not this peel).
     * PLATFORM: SHARED — G.7 complete check_expr_array_lit dest.
     */
    {
      let elem_expected: i32 = 0;
      let amb_tk: i32 = 0;
      if (return_type_ref > 0) {
        amb_tk = pipeline_type_kind_ord_at(arena, return_type_ref);
        if (amb_tk == 10 || amb_tk == 11) {
          elem_expected = pipeline_type_elem_ref_at(arena, return_type_ref);
        }
      }
      while (i < num_elems) {
        elem_ref = pipeline_expr_array_lit_elem_ref(arena, expr_ref, i);
        if (!ast.ref_is_null(elem_ref) && elem_ref > 0) {
          if (check_expr(module, arena, elem_ref, elem_expected, ctx) != 0) {
            return -1;
          }
        }
        i = i + 1;
      }
    }
    /*
     * wave611 / PLATFORM: SHARED — untyped ARRAY_LIT rvalue type inference.
     * G.7: complete this authority (no second INDEX-only path). Empty lit leaves
     * type unset (no size-0 array stamp). Coerce paths may still overwrite.
     */
    already = pipeline_expr_resolved_type_ref(arena, expr_ref);
    if ((ast.ref_is_null(already) || already <= 0) && num_elems > 0) {
      elem_ref = pipeline_expr_array_lit_elem_ref(arena, expr_ref, 0);
      elem_ty = 0;
      ok_inf = 1;
      if (!ast.ref_is_null(elem_ref) && elem_ref > 0) {
        elem_ty = pipeline_expr_resolved_type_ref(arena, elem_ref);
      }
      if (ast.ref_is_null(elem_ty) || elem_ty <= 0) {
        ok_inf = 0;
      }
      j = 1;
      while (ok_inf != 0 && j < num_elems) {
        er = pipeline_expr_array_lit_elem_ref(arena, expr_ref, j);
        et = 0;
        if (!ast.ref_is_null(er) && er > 0) {
          et = pipeline_expr_resolved_type_ref(arena, er);
        }
        if (ast.ref_is_null(et) || et <= 0) {
          ok_inf = 0;
        } else if (!type_refs_equal(arena, et, elem_ty)
        && !typeck_integer_widen_ok_refs(arena, elem_ty, et)
        && !typeck_integer_widen_ok_refs(arena, et, elem_ty)) {
          ok_inf = 0;
        } else if (!type_refs_equal(arena, et, elem_ty)
        && typeck_integer_widen_ok_refs(arena, et, elem_ty)) {
          /* wider element type wins (e.g. i32 then i64 → i64[N]). */
          elem_ty = et;
        }
        j = j + 1;
      }
      if (ok_inf != 0) {
        arr_ty = find_or_alloc_array_type_ref(arena, elem_ty, num_elems);
        if (!ast.ref_is_null(arr_ty) && arr_ty > 0) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty);
        }
      }
    }
    return 0;
  }
}

/**
 * Dispatch non-primary expression kinds for typeck (method/call/index/binop/…).
 * wave407: ARRAY_LIT (46) routes to typeck_check_expr_array_lit so nested INDEX/CALL
 * get full typeck (see that helper).
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32
 * @param return_type_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED
 */
export function check_expr_impl_mega(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_return: i32 = 41;
    let ord_panic: i32 = 42;
    let ord_match: i32 = 43;
    let ord_field: i32 = 44;
    let ord_struct_lit: i32 = 45;
    let ord_array_lit: i32 = 46;
    let ord_index: i32 = 47;
    let ord_call: i32 = 48;
    let ord_method_call: i32 = 49;
    let ord_add: i32 = 4;
    let ord_logor: i32 = 21;
    let ord_neg: i32 = 22;
    let ord_bitnot: i32 = 23;
    let ord_lognot: i32 = 24;
    let ord_addr_of: i32 = 51;
    let ord_deref: i32 = 52;
    let ord_var: i32 = 3;
    let ord_as: i32 = 54;
    /* See implementation. */
    let ord_try_propagate: i32 = ExprKind.EXPR_TRY_PROPAGATE as i32;
    let kind: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    /* See implementation. */
    if (typeck_expr_is_any_assign_kind(kind)) {
      return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_return) {
      return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_panic) {
      return typeck_check_expr_panic(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_match) {
      /* wave231: match authority in typeck.x (subject BSS + iterative arms). */
      return typeck_check_expr_match(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_field) {
      return typeck_check_expr_field_access(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_array_lit) {
      return typeck_check_expr_array_lit(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_index) {
      return typeck_check_expr_index(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_call) {
      return typeck_check_expr_call(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_method_call) {
      return typeck_check_expr_method_call(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind >= ord_add && kind <= ord_logor) {
      return typeck_check_expr_binop(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_neg || kind == ord_bitnot || kind == ord_lognot) {
      return typeck_check_expr_unary(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_addr_of) {
      return typeck_check_expr_addr_of(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_deref) {
      return typeck_check_expr_deref(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_var) {
      return typeck_check_expr_var(module, arena, expr_ref, ctx);
    }
    if (kind == ord_as) {
      return typeck_check_expr_as(module, arena, expr_ref, ctx);
    }
    if (kind == ord_struct_lit) {
      return typeck_check_expr_struct_lit(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_try_propagate) {
      /* wave231: try_propagate authority in typeck.x (Result_? payload). */
      return typeck_check_expr_try_propagate(module, arena, expr_ref, return_type_ref, ctx);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function check_expr_impl(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ord_lit: i32 = 0;
    let ord_float: i32 = 1;
    let ord_bool: i32 = 2;
    let ord_string_lit: i32 = 59;
    let ord_asm: i32 = 60;
    let ord_if: i32 = 25;
    let ord_block: i32 = 26;
    let ord_ternary: i32 = 27;
    let ord_break: i32 = 39;
    let ord_continue: i32 = 40;
    let ord_enum_var: i32 = 50;
    let kind: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (kind == ord_float) {
      return typeck_check_expr_float_lit(arena, expr_ref);
    }
    if (kind == ord_lit) {
      return typeck_check_expr_int_lit(arena, expr_ref, return_type_ref);
    }
    if (kind == ord_bool) {
      return typeck_check_expr_bool_lit(arena, expr_ref);
    }
    if (kind == ord_string_lit) {
      return typeck_check_expr_string_lit(arena, expr_ref);
    }
    if (kind == ord_asm) {
      return typeck_check_expr_asm(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_break || kind == ord_continue) {
      return typeck_check_expr_break_continue(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_enum_var) {
      return typeck_check_expr_enum_variant(arena, expr_ref);
    }
    if (kind == ord_if || kind == ord_ternary) {
      return typeck_check_expr_if_ternary(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (kind == ord_block) {
      return typeck_check_expr_block(module, arena, expr_ref, return_type_ref, ctx);
    }
    return check_expr_impl_mega(module, arena, expr_ref, return_type_ref, ctx);
  }
}

/**
 * See implementation.
 */
export function check_expr(module: *Module, arena: *ASTArena, expr_ref: i32, return_type_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — post-check CTFE write of const_folded_* (not emit fold).
  let rc: i32 = 0;
  if (ast.ref_is_null(expr_ref)) {
    return 0;
  }
  if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
    return 0;
  }
  rc = check_expr_impl(module, arena, expr_ref, return_type_ref, ctx);
  if (rc == 0) {
    unsafe {
      typeck_fold_expr(arena, expr_ref);
    }
  }
  return rc;
}

/**
* See implementation.
*
* See implementation.
* See implementation.
* See implementation.
* See implementation.
* See implementation.
* See implementation.
*/
export function func_body_tail_expr_ref_for_implicit_rule(arena: *ASTArena, body_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let stmt_order_kind_expr_stmt: u8 = (2 as u8);
    let stmt_order_kind_region_c_parser: u8 = (5 as u8);
    let stmt_order_kind_region_x_parser: u8 = (6 as u8);
    let ord_break: i32 = 39;
    let ord_continue: i32 = 40;
    let ord_return: i32 = 41;
    let ord_panic: i32 = 42;
    let fin_ref: i32 = ast.ast_block_final_expr_ref(arena, body_ref);
    let fin_kind: i32 = 0;
    let nso: i32 = ast.ast_block_num_stmt_order(arena, body_ref);
    if (!ast.ref_is_null(fin_ref)) {
      fin_kind = pipeline_expr_kind_ord_at(arena, fin_ref);
      if (fin_kind == ord_return || fin_kind == ord_panic || fin_kind == ord_break ||
          fin_kind == ord_continue) {
        return fin_ref;
      }
    }
    if (nso > 0) {
      let last_k: u8 = ast.ast_block_stmt_order_kind(arena, body_ref, nso - 1);
      if (last_k == stmt_order_kind_region_c_parser || last_k == stmt_order_kind_region_x_parser) {
        let ridx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, nso - 1);
        let nreg: i32 = ast.ast_block_num_regions(arena, body_ref);
        if (ridx >= 0 && ridx < nreg) {
          let unsafe_region: i32 = pipeline_block_region_is_unsafe(arena, body_ref, ridx);
          if (unsafe_region != 0) {
            let inner_ref: i32 = ast.ast_block_region_body_ref(arena, body_ref, ridx);
            if (!ast.ref_is_null(inner_ref)) {
              return func_body_tail_expr_ref_for_implicit_rule(arena, inner_ref);
            }
          }
        }
      }
    }
    if (!ast.ref_is_null(fin_ref)) {
      return fin_ref;
    }
    if (nso > 0) {
      let last_k2: u8 = ast.ast_block_stmt_order_kind(arena, body_ref, nso - 1);
      if (last_k2 == stmt_order_kind_expr_stmt) {
        let idx: i32 = ast.ast_block_stmt_order_idx(arena, body_ref, nso - 1);
        let nes: i32 = ast.ast_block_num_expr_stmts(arena, body_ref);
        if (idx >= 0 && idx < nes) {
          return ast.ast_block_expr_stmt_ref(arena, body_ref, idx);
        }
      }
      return 0;
    }
    let nes2: i32 = ast.ast_block_num_expr_stmts(arena, body_ref);
    if (nes2 > 0) {
      return ast.ast_block_expr_stmt_ref(arena, body_ref, nes2 - 1);
    }
    return 0;
  }
}

/**
* See implementation.
* See implementation.
*/
export function func_body_has_implicit_return_tail(arena: *ASTArena, body_ref: i32): bool {
  // wave259 pure-owned leave: full authority here (was Cap residual C twin).
  // G-02f-477: EXPR_BLOCK (ord=26) recurses into inner block for explicit return
  // (unsafe { return ...; } parsed as EXPR_BLOCK not region).
  // PLATFORM: SHARED freestanding typeck.
  unsafe {
    let tail_ref: i32 = 0;
    let tail_kind: i32 = 0;
    let dbg: *u8 = 0 as *u8;
    if (ast.ref_is_null(body_ref) || body_ref <= 0 || arena == 0 as *ASTArena ||
        body_ref > arena.num_blocks) {
      return false;
    }
    tail_ref = func_body_tail_expr_ref_for_implicit_rule(arena, body_ref);
    if (ast.ref_is_null(tail_ref)) {
      return false;
    }
    tail_kind = pipeline_expr_kind_ord_at(arena, tail_ref);
    dbg = link_abi_getenv("XLANG_DEBUG_PIPE" as *u8);
    if (dbg != 0 as *u8) {
      // Debug only; residual used fprintf — keep gate, omit host I/O in pure.
    }
    if (ast.ast_expr_disallows_implicit_tail(arena, tail_ref)) {
      return false;
    }
    if (tail_kind == 26) {
      let inner_block: i32 = pipeline_expr_block_ref_at(arena, tail_ref);
      if (!ast.ref_is_null(inner_block)) {
        return func_body_has_implicit_return_tail(arena, inner_block);
      }
    }
    return true;
  }
}

/**
 * See implementation.
 */
export function typeck_loop_depth_push(ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let saved: i32 = pipeline_dep_ctx_typeck_loop_depth_at(ctx);
    pipeline_typeck_loop_depth_set_c(ctx, saved + 1);
    return saved;
  }
}

/**
 * See implementation.
 */
export function typeck_loop_depth_pop(ctx: *PipelineDepCtx, saved: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    pipeline_typeck_loop_depth_set_c(ctx, saved);
  }
}

/**
 * See implementation.
 */
export function check_block_as_loop_body(module: *Module, arena: *ASTArena, body_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  let saved_ld: i32 = 0;
  let rc: i32 = 0;
  if (ctx == 0 as *PipelineDepCtx) {
    return -1;
  }
  saved_ld = typeck_loop_depth_push(ctx);
  rc = check_block(module, arena, body_ref, return_type_ref, ctx);
  typeck_loop_depth_pop(ctx, saved_ld);
  return rc;
}

/**
 * See implementation.
 */
export function typeck_check_block_one_const(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let cd_ir: i32 = ast.ast_block_const_init_ref(arena, block_ref, idx);
    let cd_tr: i32 = ast.ast_block_const_type_ref(arena, block_ref, idx);
    let init_ty: i32 = 0;
    let init_ctx: i32 = 0;
    let cname_buf: u8[128];
    let cname_len: i32 = 0;
    let func_ix: i32 = 0;
    /*
     * wave680 Cap residual: same-block const redecl / clash with let / body-param.
     * Host-C BLD001 redefinition soft residual. Nested shadow OK.
     * G.7: pipeline_block_local_name_redecl_c + diag duplicate_local.
     *
     * Discard binding `const _` (parser TOKEN_UNDERSCORE → name "_", len=1):
     * multiple discards in one block are intentional and must not T001.
     * Aligns with parser is_discard_name and L6 unused-hint skip of `_`.
     * Mega pipeline_abi redecl helper is hard-banned this wave; complete the
     * typeck gate here (sole emit site of duplicate_local for consts).
     * PLATFORM: SHARED typeck.
     */
    cname_len = pipeline_block_const_name_len(arena, block_ref, idx);
    if (cname_len > 0 && cname_len < 128) {
      pipeline_block_const_name_copy64(arena, block_ref, idx, &cname_buf[0]);
      /* Exact discard `_` only — `_foo` still participates in redecl. */
      if (!(cname_len == 1 && cname_buf[0] == 95)) {
        func_ix = pipeline_dep_ctx_current_func_index(ctx);
        if (pipeline_block_local_name_redecl_c(arena, block_ref, &cname_buf[0], cname_len, 1, idx, module,
            func_ix) != 0) {
          let err_line: i32 = 0;
          let err_col: i32 = 0;
          if (!ast.ref_is_null(cd_ir)) {
            err_line = pipeline_expr_line_at(arena, cd_ir);
            err_col = pipeline_expr_col_at(arena, cd_ir);
          }
          driver_diagnostic_typeck_duplicate_local(err_line, err_col);
          return -1;
        }
      }
    }
    /* See implementation. */
    if (!ast.ref_is_null(cd_ir)) {
      if (typeck_block_const_init_is_const(arena, block_ref, idx) == 0) {
        let err_line: i32 = pipeline_expr_line_at(arena, cd_ir);
        let err_col: i32 = pipeline_expr_col_at(arena, cd_ir);
        typeck_const_init_not_constant(err_line, err_col);
        return - 1;
      }
    }
    /*
     * wave423 Cap residual pure: const type inference.
     * Untyped `const name = init` (parser left type_ref null): check init with no
     * expected type, then stamp decl type from init via pipeline_block_set_const_type_ref.
     * Typed const still uses decl type as expected context + coerce.
     * G.7: typeck_check_block_one_const; twin typeck_gen + set_const_type_ref.
     * PLATFORM: SHARED typeck. return_type_ref unused for untyped path (kept in signature).
     */
    if (!ast.ref_is_null(cd_tr)) {
      init_ctx = cd_tr;
    } else {
      init_ctx = 0;
    }
    if (check_expr(module, arena, cd_ir, init_ctx, ctx) != 0) {
      return - 1;
    }
    if (!ast.ref_is_null(cd_ir) && ast.ref_is_null(cd_tr)) {
      init_ty = expr_type_ref(arena, cd_ir);
      if (ast.ref_is_null(init_ty)) {
        return - 1;
      }
      if (pipeline_block_set_const_type_ref(arena, block_ref, idx, init_ty) != 0) {
        return - 1;
      }
    } else if (!ast.ref_is_null(cd_ir) && !ast.ref_is_null(cd_tr)) {
      /* wave672: coerce may hard-fail ARRAY_LIT elem mismatch (-1). */
      if (typeck_coerce_init_expr_to_decl(module, arena, cd_ir, cd_tr) < 0) {
        return -1;
      }
      init_ty = expr_type_ref(arena, cd_ir);
      if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, cd_tr, init_ty)) {
        return - 1;
      }
    }
    /** CTFE: fold const init with prior block consts (A=3; B=A+2). */
    if (!ast.ref_is_null(cd_ir)) {
      typeck_fold_block_const_init(arena, block_ref, idx);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_block_one_let(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ld_ir: i32 = ast.ast_block_let_init_ref(arena, block_ref, idx);
    let ld_tr: i32 = ast.ast_block_let_type_ref(arena, block_ref, idx);
    let init_ty: i32 = 0;
    let init_ctx: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    let lname_buf: u8[128];
    let lname_len: i32 = 0;
    let func_ix_l: i32 = 0;
    let canon_tr: i32 = 0;
    /*
     * CORE-016: stamp Name&lt;Args&gt; let types to mangled family (Result_i32)
     * so slot layout matches core family ABI (not hollow generic-inst size).
     * PLATFORM: SHARED — sole let-decl family canonicalize write-back.
     */
    if (!ast.ref_is_null(ld_tr)) {
      canon_tr = typeck_resolve_type_alias_ref(arena, ld_tr);
      if (canon_tr > 0 && canon_tr != ld_tr) {
        if (pipeline_block_set_let_type_ref(arena, block_ref, idx, canon_tr) == 0) {
          ld_tr = canon_tr;
        }
      }
    }
    /*
     * wave680 Cap residual: same-block let redecl / clash with const / body-param.
     * Host-C BLD001 redefinition soft residual. Nested shadow OK.
     * G.7: pipeline_block_local_name_redecl_c + diag duplicate_local.
     *
     * Discard binding `let _` (parser TOKEN_UNDERSCORE → name "_", len=1):
     * multiple discards in one block are intentional (side-effect inits kept;
     * name never read). Must not T001 — closes view_lifecycle / print_any.
     * Aligns with parser is_discard_name and L6 unused-hint skip of `_`.
     * Mega pipeline_abi redecl helper is hard-banned this wave; complete the
     * typeck gate here (sole emit site of duplicate_local for lets).
     * PLATFORM: SHARED typeck.
     */
    lname_len = pipeline_block_let_name_len(arena, block_ref, idx);
    if (lname_len > 0 && lname_len < 128) {
      pipeline_block_let_name_copy64(arena, block_ref, idx, &lname_buf[0]);
      /* Exact discard `_` only — `_foo` still participates in redecl. */
      if (!(lname_len == 1 && lname_buf[0] == 95)) {
        func_ix_l = pipeline_dep_ctx_current_func_index(ctx);
        if (pipeline_block_local_name_redecl_c(arena, block_ref, &lname_buf[0], lname_len, 0, idx, module,
            func_ix_l) != 0) {
          let err_line: i32 = 0;
          let err_col: i32 = 0;
          if (!ast.ref_is_null(ld_ir)) {
            err_line = pipeline_expr_line_at(arena, ld_ir);
            err_col = pipeline_expr_col_at(arena, ld_ir);
          }
          driver_diagnostic_typeck_duplicate_local(err_line, err_col);
          return -1;
        }
      }
    }
    /* See implementation. */
    if (!ast.ref_is_null(ld_ir)) {
      init_ctx = return_type_ref;
      if (!ast.ref_is_null(ld_tr)) {
        init_ctx = ld_tr;
      }
      /*
       * wave314: do not pass f64 expected when checking a bare f32 VAR init.
       * check_expr with expected f64 stamps VAR resolved as f64 → freestanding
       * load looks like f64 and skips cvtss2sd. Check with no expected type; let
       * widen gate below accepts f32→f64 without stamping.
       */
      if (!ast.ref_is_null(ld_tr) && pipeline_expr_kind_ord_at(arena, ld_ir) == 3) {
        let decl_k0: i32 = pipeline_type_kind_ord_at(arena, ld_tr);
        if (decl_k0 == 15) {
          init_ctx = 0;
        }
      }
      if (check_expr(module, arena, ld_ir, init_ctx, ctx) != 0) {
        return - 1;
      }
    }
    /* See implementation. */
    pipeline_type_stamp_block_let_region_c(arena, block_ref, idx, ctx);
    /* See implementation. */
    ld_tr = ast.ast_block_let_type_ref(arena, block_ref, idx);
    if (!ast.ref_is_null(ld_ir) && !ast.ref_is_null(ld_tr)) {
      /* wave672: coerce may hard-fail ARRAY_LIT elem mismatch (-1). */
      if (typeck_coerce_init_expr_to_decl(module, arena, ld_ir, ld_tr) < 0) {
        return -1;
      }
      init_ty = expr_type_ref(arena, ld_ir);
      /*
       * wave670 Cap residual: keyword `null` only for TYPE_PTR let-init.
       * Coerce leaves untyped null when decl is non-ptr → must hard-fail (init_ty=0
       * would soft-skip the equal check below). Bare INT 0 still coerces.
       */
      if (typeck_expr_is_null_keyword(arena, ld_ir) != 0
      && pipeline_type_kind_ord_at(arena, ld_tr) != 9) {
        eb = driver_typeck_diag_scratch_expect();
        gb = driver_typeck_diag_scratch_found();
        el = typeck_diag_fmt_type_into(arena, ld_tr, eb, 96);
        gl = typeck_diag_append_lit(gb, 0, 96, "null", 4);
        {
          let err_line: i32 = pipeline_expr_line_at(arena, ld_ir);
          let err_col: i32 = pipeline_expr_col_at(arena, ld_ir);
          driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl);
        }
        return -1;
      }
      /* See implementation. */
      if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, ld_tr, init_ty)) {
        /* wave313: refs path closes NAMED i8/i16/u16 let-init widen (e.g. i16→i32). */
        if (typeck_integer_widen_ok_refs(arena, ld_tr, init_ty)) {
          pipeline_expr_set_resolved_type_ref(arena, ld_ir, ld_tr);
          init_ty = ld_tr;
        }
        /* wave314: f32→f64 accepted without stamping resolved type.
         * Freestanding emit needs true f32 bits then cvtss2sd; stamping VAR as f64
         * zero-extends IEEE f32 bits and yields run=0 (Ubuntu gold). */
      }
      if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, ld_tr, init_ty)
          && pipeline_typeck_linear_accepts_init_c(arena, ld_tr, init_ty) == 0) {
        let decl_k2: i32 = pipeline_type_kind_ord_at(arena, ld_tr);
        let init_k2: i32 = pipeline_type_kind_ord_at(arena, init_ty);
        /*
         * F2 TYPE_DYN(17): dyn decl accepts a concrete init only when either
         * (a) the init is the null-dyn sentinel (literal INT_LIT 0 — null
         * fat-ptr representation, no vtable) OR (b) a registered
         * `impl Trait for init_ty` block exists. Concrete init without impl
         * rejects here with the standard mismatch diagnostic.
         *
         * F1 history: blanket skip when decl_k2 == TYPE_DYN accepted any
         * init (dyn was shape-only). F2 closes that hole with real
         * impl-lookup; null-dyn sentinel preserves the F1 path for
         * `let x: dyn Trait = 0`. Mirrors the assign-path dyn_assign_ok
         * rule (single G.7 rule; both sides live in this commit).
         * PLATFORM: SHARED.
         */
        let dyn_init_reject: i32 = 0;
        let fn_init_ok: i32 = 0;
        if (decl_k2 == TypeKind.TYPE_DYN as i32) {
          if (typeck_dyn_rhs_is_null_sentinel(arena, init_ty, ld_ir) == 0) {
            let trait_nm_let: u8[64] = [];
            let tnl_let: i32 = pipeline_type_named_name_into(arena, ld_tr, &trait_nm_let[0]);
            if (tnl_let == 0 || xlang_skip_impl_concrete_implements_trait_c(
                    arena as *void, init_ty, &trait_nm_let[0], tnl_let) == 0) {
              dyn_init_reject = 1;
            }
          }
        }
        /*
         * 10.3.1: `let f: function(...): T = bare_fn` — bare_fn is Cap *u8
         * (wave100); accept Cap/TYPE_FN onto TYPE_FN with signature when
         * checkable (G.7 typeck_fnptr_surface_compat). PLATFORM: SHARED.
         */
        if (typeck_fnptr_surface_compat(module, arena, ld_tr, init_ty, ld_ir, 0) != 0) {
          fn_init_ok = 1;
        }
        if (dyn_init_reject != 0
            || (decl_k2 != TypeKind.TYPE_DYN as i32 && fn_init_ok == 0
                && !typeck_float_widen_ok(decl_k2, init_k2))) {
          eb = driver_typeck_diag_scratch_expect();
          gb = driver_typeck_diag_scratch_found();
          el = typeck_diag_fmt_type_into(arena, ld_tr, eb, 96);
          gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96);
          let err_line: i32 = pipeline_expr_line_at(arena, ld_ir);
          let err_col: i32 = pipeline_expr_col_at(arena, ld_ir);
          driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl);
          return - 1;
        }
        /* match via f32→f64; leave init_ty as f32 for freestanding cvtss2sd. */
      }
      /* See implementation. */
      if (!ast.ref_is_null(init_ty) && typeck_check_slice_region_assign(arena, ld_ir, ld_tr, init_ty) != 0) {
        return - 1;
      }
    }
    /** CTFE: re-fold let init with block const env (e.g. let x = B * 2). */
    if (!ast.ref_is_null(ld_ir)) {
      typeck_fold_expr_in_block(arena, block_ref, ld_ir);
    }
    return 0;
  }
}

/**
 * See implementation.
 */
export function typeck_check_block_one_while(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let wc: i32 = ast.ast_block_while_cond_ref(arena, block_ref, idx);
    let wb: i32 = ast.ast_block_while_body_ref(arena, block_ref, idx);
    if (!ast.ref_is_null(wc)) {
      /* wave704: while cond ambient = 0 (bool). */
      if (check_expr(module, arena, wc, 0, ctx) != 0) {
        return - 1;
      }
      if (!type_ref_is_bool(arena, expr_type_ref(arena, wc))) {
        driver_diagnostic_typeck_while_condition_not_bool(pipeline_expr_line_at(arena, wc),
        pipeline_expr_col_at(arena, wc));
        return - 1;
      }
    }
    return check_block_as_loop_body(module, arena, wb, return_type_ref, ctx);
  }
}

/**
 * See implementation.
 */
export function typeck_check_block_one_for(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let fi_ir: i32 = ast.ast_block_for_init_ref(arena, block_ref, idx);
    let fc_cr: i32 = ast.ast_block_for_cond_ref(arena, block_ref, idx);
    let fs_sr: i32 = ast.ast_block_for_step_ref(arena, block_ref, idx);
    let fb_br: i32 = ast.ast_block_for_body_ref(arena, block_ref, idx);
    if (check_expr(module, arena, fi_ir, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (!ast.ref_is_null(fc_cr)) {
      /* wave704: for cond ambient = 0 (bool). */
      if (check_expr(module, arena, fc_cr, 0, ctx) != 0) {
        return - 1;
      }
      if (!type_ref_is_bool(arena, expr_type_ref(arena, fc_cr))) {
        driver_diagnostic_typeck_for_condition_not_bool(pipeline_expr_line_at(arena, fc_cr),
        pipeline_expr_col_at(arena, fc_cr));
        return - 1;
      }
    }
    if (check_expr(module, arena, fs_sr, return_type_ref, ctx) != 0) {
      return - 1;
    }
    return check_block_as_loop_body(module, arena, fb_br, return_type_ref, ctx);
  }
}

/**
 * See implementation.
 */
export function typeck_check_block_one_if(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ic_cr: i32 = ast.ast_block_if_cond_ref(arena, block_ref, idx);
    let ib_tr: i32 = ast.ast_block_if_then_body_ref(arena, block_ref, idx);
    let ib_er: i32 = 0;
    if (!ast.ref_is_null(ic_cr)) {
      /* wave704: block-if cond ambient = 0 (bool). */
      if (check_expr(module, arena, ic_cr, 0, ctx) != 0) {
        return - 1;
      }
      if (!type_ref_is_bool(arena, expr_type_ref(arena, ic_cr))) {
        typeck_driver_diagnostic_pipe_marker(pipeline_expr_kind_ord_at(arena, ic_cr));
        typeck_driver_diagnostic_pipe_marker(pipeline_type_kind_ord_at(arena, expr_type_ref(arena, ic_cr)));
        driver_diagnostic_typeck_if_condition_not_bool(pipeline_expr_line_at(arena, ic_cr),
        pipeline_expr_col_at(arena, ic_cr));
        return - 1;
      }
    }
    if (check_block(module, arena, ib_tr, return_type_ref, ctx) != 0) {
      return - 1;
    }
    ib_er = ast.ast_block_if_else_body_ref(arena, block_ref, idx);
    if (!ast.ref_is_null(ib_er)) {
      return check_block(module, arena, ib_er, return_type_ref, ctx);
    }
    return 0;
  }
}

/**
 * wave663 Cap residual: hard-fail a value-producing expression used as a statement
 * or final_expr inside a void function.
 *
 * Parser often lowers `return e` / bare `e` in void functions to a non-RETURN
 * expr_stmt or final_expr; host-C then emits `(void)(e)` without typeck error.
 * Allow statement-like kinds: bare RETURN, CALL, METHOD_CALL, ASSIGN*,
 * BREAK, CONTINUE, PANIC, IF, BLOCK, MATCH.
 *
 * wave1227 root fix: if the expression already resolved to TYPE_VOID, it is not a
 * value-producing rvalue — accept it. Prior allowlist missed EXPR_IF/EXPR_BLOCK/
 * EXPR_MATCH as statements, which produced the false positive
 * "return expression type mismatch: expected void, found void" (same type ref on
 * both sides; e.g. `driver_parsed_work_cleanup` with nested `if` expr_stmts).
 *
 * @param arena *ASTArena — holds expr_ref and return_type_ref
 * @param expr_ref i32 — candidate expression (final or expr_stmt)
 * @param return_type_ref i32 — enclosing function return type
 * @return i32 — 0 ok (not void, or statement-like / void-typed), -1 void value rejected
 * PLATFORM: SHARED — typeck.x + typeck_gen + empty_surface same commit.
 */
export function typeck_void_reject_value_expr(arena: *ASTArena, expr_ref: i32,
return_type_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let void_ord: i32 = 16;
    let rt_k: i32 = 0;
    let ek: i32 = 0;
    let void_stmt_ok: i32 = 0;
    let got: i32 = 0;
    let got_k: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    if (arena == 0 as *ASTArena || expr_ref <= 0 || ast.ref_is_null(return_type_ref)) {
      return 0;
    }
    rt_k = pipeline_type_kind_ord_at(arena, return_type_ref);
    if (rt_k != void_ord) {
      return 0;
    }
    ek = pipeline_expr_kind_ord_at(arena, expr_ref);
    /* ExprKind ordinals: IF=25 BLOCK=26 ASSIGN..=28..38 BREAK=39 CONTINUE=40
     * RETURN=41 PANIC=42 MATCH=43 CALL=48 METHOD_CALL=49. */
    if (ek == 41) {
      if (ast.ref_is_null(pipeline_expr_unary_operand_ref_at(arena, expr_ref))) {
        void_stmt_ok = 1;
      }
    } else if (ek == 48 || ek == 49 || ek == 39 || ek == 40 || ek == 42 || ek == 60) {
      void_stmt_ok = 1;
    } else if (ek >= 28 && ek <= 38) {
      void_stmt_ok = 1;
    } else if (ek == 25 || ek == 26 || ek == 43) {
      void_stmt_ok = 1;
    }
    if (void_stmt_ok != 0) {
      return 0;
    }
    got = expr_type_ref(arena, expr_ref);
    /*
     * wave1227: void-typed expression is statement-shaped, not a value rvalue.
     * Closes expected-void/found-void FP when kind allowlist lags (if/block/match).
     */
    if (!ast.ref_is_null(got)) {
      got_k = pipeline_type_kind_ord_at(arena, got);
      if (got_k == void_ord) {
        return 0;
      }
    }
    eb = driver_typeck_diag_scratch_expect();
    gb = driver_typeck_diag_scratch_found();
    el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb);
    gl = typeck_diag_fmt_type_or_question(arena, got, gb);
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl);
    typeck_emit_return_subexpr_breadcrumb(arena, expr_ref, line, col);
    driver_diagnostic_typeck_ret_fail(2, expr_ref, return_type_ref, got);
    return - 1;
  }
}

/**
 * Type-check a block's final expression against the enclosing function return type.
 * @param module *Module — current module (unused except via check_expr callees)
 * @param arena *ASTArena — expression/type arena; must hold fin0
 * @param block_ref i32 — block owning the final (diagnostics / parent links)
 * @param return_type_ref i32 — function return type; 0 skips match
 * @param ctx *PipelineDepCtx — typeck context (unsafe depth, current func)
 * @param fin0 i32 — final_expr ref; null → no-op
 * @return i32 — 0 ok, -1 type error
 * wave663: also rejects void value finals via typeck_void_reject_value_expr.
 * PLATFORM: SHARED — typeck.x + typeck_gen + empty_surface same commit.
 */
export function typeck_check_block_final(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, fin0: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let skip_tail_ty_cmp: bool = false;
    let fin_k_tail: i32 = 0;
    let got: i32 = 0;
    let fin_op: i32 = 0;
    let fin_k_ret: i32 = 0;
    let eb_fin: *u8 = 0 as *u8;
    let gb_fin: *u8 = 0 as *u8;
    let el_fin: i32 = 0;
    let gl_fin: i32 = 0;
    if (ast.ref_is_null(fin0)) {
      return 0;
    }
    if (check_expr(module, arena, fin0, return_type_ref, ctx) != 0) {
      return - 1;
    }
    if (typeck_void_reject_value_expr(arena, fin0, return_type_ref) != 0) {
      return - 1;
    }
    fin_k_tail = pipeline_expr_kind_ord_at(arena, fin0);
/** See implementation for details. */
    if (fin_k_tail != 41) {
      skip_tail_ty_cmp = true;
    } else if (ast.ref_is_null(pipeline_expr_unary_operand_ref_at(arena, fin0))) {
      skip_tail_ty_cmp = true;
    }
    if (ast.ref_is_null(return_type_ref) || skip_tail_ty_cmp) {
      return 0;
    }
    got = expr_type_ref(arena, fin0);
    fin_op = fin0;
    fin_k_ret = pipeline_expr_kind_ord_at(arena, fin0);
    if (fin_k_ret == 41) {
      fin_op = pipeline_expr_unary_operand_ref_at(arena, fin0);
    }
    /* See implementation. */
    if (!ast.ref_is_null(fin_op) && fin_op > 0 && !ast.ref_is_null(return_type_ref)) {
      typeck_ret_coerce_integral_to_expect_i32(arena, fin_op, return_type_ref);
      typeck_ret_coerce_integral_widen(arena, fin_op, return_type_ref);
    }
    if (typeck_return_operand_matches(module, arena, fin_op, return_type_ref)) {
      return 0;
    }
    /* See implementation. */
    if (!ast.ref_is_null(fin_op) && fin_op > 0 && !ast.ref_is_null(return_type_ref)) {
      let fin_got: i32 = expr_type_ref(arena, fin_op);
      let ek_fin: i32 = 0;
      let gk_fin: i32 = 0;
      if (!ast.ref_is_null(fin_got) && fin_got > 0) {
        ek_fin = pipeline_type_kind_ord_at(arena, return_type_ref);
        gk_fin = pipeline_type_kind_ord_at(arena, fin_got);
        if (typeck_integer_widen_ok_refs(arena, return_type_ref, fin_got) ||
            typeck_float_widen_ok(ek_fin, gk_fin)) {
          pipeline_expr_set_resolved_type_ref(arena, fin_op, return_type_ref);
          return 0;
        }
      }
    }
    eb_fin = driver_typeck_diag_scratch_expect();
    gb_fin = driver_typeck_diag_scratch_found();
    el_fin = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb_fin);
    gl_fin = typeck_diag_fmt_type_or_question(arena, got, gb_fin);
    let err_line: i32 = pipeline_expr_line_at(arena, fin0);
    let err_col: i32 = pipeline_expr_col_at(arena, fin0);
    driver_diagnostic_typeck_return_mismatch(err_line, err_col, eb_fin, el_fin, gb_fin, gl_fin);
    typeck_emit_return_subexpr_breadcrumb(arena, fin0, err_line, err_col);
    return - 1;
  }
}

/**
 * See implementation.
 */
export function typeck_check_block_one_region(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    return pipeline_typeck_check_block_one_region_c(module, arena, block_ref, idx, return_type_ref, ctx);
  }
}

/**
 * Typecheck stmt_order[si .. nso) for one block (const/let/expr/while/for/if/region).
 *
 * Iterative walk (while), not tail recursion. Historical form recursed on
 * si+1 — deep blocks (mega pipeline_abi bodies) stacked dozens of frames
 * (Stage12.0.5 sample: typeck_check_block_stmt_order_one self-chain). The
 * leftover `i < 96` cap was stack insurance for that recursion. The walk
 * is iterative now; keeping 96 dropped late lets in a large main() so
 * anonymous STRUCT_LIT never dest-stamped (`(struct )` on dest7+).
 * Walk every stmt_order entry. Fail-fast -1; void expr_stmt reject (wave663).
 * PLATFORM: SHARED — large-main late-let dest-name.
 *
 * @param module *Module — entry / current module
 * @param arena *ASTArena — type/expr pool
 * @param block_ref i32 — block under check
 * @param return_type_ref i32 — enclosing function return type
 * @param ctx *PipelineDepCtx — current_block / current_func
 * @param si i32 — start stmt_order index (callers pass 0)
 * @param nso i32 — stmt_order length
 * @param nc i32 — num consts (bounds for kind 0)
 * @param nl i32 — num lets
 * @param nes i32 — num expr_stmts
 * @param nlp i32 — num while loops
 * @param nfp i32 — num for loops
 * @param nif i32 — num ifs
 * @param nreg i32 — num regions
 * @return i32 — 0 ok; -1 typeck fail
 * PLATFORM: SHARED freestanding typeck block walk.
 */
export function typeck_check_block_stmt_order_one(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, si: i32, nso: i32, nc: i32, nl: i32, nes: i32,
nlp: i32, nfp: i32, nif: i32, nreg: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let i: i32 = 0;
    let sk: u8 = (0 as u8);
    let idx: i32 = 0;
    let es_ref: i32 = 0;
    i = si;
    // Constant stack: walk stmt_order[i] then i+1 (≡ historical tail recursion).
    // Do not recap at 96: that leftover recursive bound skipped dest-stamp
    // of late lets (official vfir dest7+ emitted `(struct )`).
    while (i < nso) {
      pipeline_typeck_block_impl_touch_ctx_block_c(ctx, block_ref);
      sk = ast.ast_block_stmt_order_kind(arena, block_ref, i);
      idx = ast.ast_block_stmt_order_idx(arena, block_ref, i);
      if (sk == (0 as u8)) {
        if (idx >= 0 && idx < nc && idx < 128) {
          if (typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      } else if (sk == (1 as u8)) {
        if (idx >= 0 && idx < nl && idx < 128) {
          if (typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      } else if (sk == (2 as u8)) {
        if (idx >= 0 && idx < nes) {
          es_ref = ast.ast_block_expr_stmt_ref(arena, block_ref, idx);
          if (check_expr(module, arena, es_ref, return_type_ref, ctx) != 0) {
            return -1;
          }
          /* wave663: void function expr_stmt value (return e lowered to e). */
          if (typeck_void_reject_value_expr(arena, es_ref, return_type_ref) != 0) {
            return -1;
          }
        }
      } else if (sk == (3 as u8)) {
        if (idx >= 0 && idx < nlp) {
          if (typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      } else if (sk == (4 as u8)) {
        if (idx >= 0 && idx < nfp) {
          if (typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      } else if (sk == (5 as u8)) {
        if (idx >= 0 && idx < nif) {
          if (typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      } else if (sk == (6 as u8)) {
        if (idx >= 0 && idx < nreg) {
          if (typeck_check_block_one_region(module, arena, block_ref, return_type_ref, ctx, idx) != 0) {
            return -1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/* See implementation. */
export function typeck_check_block_legacy_consts(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nc: i32): i32 {
  if (i >= nc) {
    return 0;
  }
  if (typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, i) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, i + 1, nc);
}

/* See implementation. */
export function typeck_check_block_legacy_lets(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nl: i32): i32 {
  if (i >= nl) {
    return 0;
  }
  if (typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, i) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, i + 1, nl);
}

/* See implementation. */
export function typeck_check_block_legacy_whiles(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nlp: i32): i32 {
  if (i >= nlp) {
    return 0;
  }
  if (typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, i) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, i + 1, nlp);
}

/* See implementation. */
export function typeck_check_block_legacy_fors(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nfp: i32): i32 {
  if (i >= nfp) {
    return 0;
  }
  if (typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, i) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, i + 1, nfp);
}

/* See implementation. */
export function typeck_check_block_legacy_ifs(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nif: i32): i32 {
  if (i >= nif) {
    return 0;
  }
  if (typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, i) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, i + 1, nif);
}

/* See implementation. */
export function typeck_check_block_legacy_expr_stmts(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx, i: i32, nes: i32): i32 {
  let es_ref: i32 = 0;
  if (i >= nes || i >= 32) {
    return 0;
  }
  es_ref = ast.ast_block_expr_stmt_ref(arena, block_ref, i);
  if (check_expr(module, arena, es_ref, return_type_ref, ctx) != 0) {
    return - 1;
  }
  /* wave663: void function expr_stmt value (return e lowered to e). */
  if (typeck_void_reject_value_expr(arena, es_ref, return_type_ref) != 0) {
    return - 1;
  }
  return typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, i + 1, nes);
}

/**
 * See implementation.
 */
export function check_block_impl(module: *Module, arena: *ASTArena, block_ref: i32, return_type_ref: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let saved_block_ref: i32 = 0;
    let nc: i32 = 0;
    let nl: i32 = 0;
    let nlp: i32 = 0;
    let nfp: i32 = 0;
    let nif: i32 = 0;
    let nreg: i32 = 0;
    let nes: i32 = 0;
    let nso: i32 = 0;
    let fin0: i32 = 0;
    let func_ix: i32 = 0;
    if (arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || block_ref <= 0) {
      return - 1;
    }
    saved_block_ref = pipeline_typeck_block_impl_bind_ctx_c(ctx, block_ref);
    /* parent_block_ref: pipeline_patch_block_parent_links covers while/for/if/region bodies,
       but not block-expr cases (blocks tied via pipeline_expr_block_ref_at).
       saved_block_ref is current_block_ref before entering this block = direct parent. */
    pipeline_block_set_parent_if_zero(arena, block_ref, saved_block_ref);
    nc = ast.ast_block_num_consts(arena, block_ref);
    nl = ast.ast_block_num_lets(arena, block_ref);
    nlp = ast.ast_block_num_loops(arena, block_ref);
    nfp = ast.ast_block_num_for_loops(arena, block_ref);
    nif = ast.ast_block_num_if_stmts(arena, block_ref);
    nreg = ast.ast_block_num_regions(arena, block_ref);
    nes = ast.ast_block_num_expr_stmts(arena, block_ref);
    nso = ast.ast_block_num_stmt_order(arena, block_ref);
    fin0 = ast.ast_block_final_expr_ref(arena, block_ref);
    func_ix = pipeline_dep_ctx_current_func_index(ctx);
    driver_diagnostic_typeck_block_enter(func_ix, block_ref, nc, nl, nlp, nfp, nes, fin0);
    if (nso > 0) {
      if (typeck_check_block_stmt_order_one(module, arena, block_ref, return_type_ref, ctx, 0, nso, nc, nl,
      nes, nlp, nfp, nif, nreg) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
    } else {
      if (typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, 0, nc) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
      if (typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, 0, nl) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
      if (typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, 0, nlp) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
      if (typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, 0, nfp) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
      if (typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, 0, nif) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
      if (typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, 0, nes) != 0) {
        pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
        return - 1;
      }
    }
    if (typeck_check_block_final(module, arena, block_ref, return_type_ref, ctx, fin0) != 0) {
      pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
      return - 1;
    }
    pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref);
    return 0;
  }
}

/**
 * See implementation.
 */
export function check_block(module: *Module, arena: *ASTArena, block_ref: i32, return_type_ref: i32,
ctx: *PipelineDepCtx): i32 {
  if (ast.ref_is_null(block_ref)) {
    return 0;
  }
  if (arena == 0 as *ASTArena || block_ref <= 0 || block_ref > arena.num_blocks) {
    return 0;
  }
  return check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}

/**
 * See implementation.
 */
export function typeck_x_ast_check_one_func(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx, func_idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let body_ref: i32 = 0;
    let ret_ty_ref: i32 = 0;
    let fn_name_len: i32 = 0;
    let num_generic_params: i32 = 0;
    let ord_void: i32 = 16;
    let rt_kind: i32 = 0;
    let err_check_block: i32 = 5;
    let err_implicit_tail: i32 = 6;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    fn_name_len = pipeline_module_func_name_len_at(module, func_idx);
    pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0));
    driver_diagnostic_typeck_fn_enter(func_idx, typeck_scratch64_slot(0), fn_name_len);
    pipeline_typeck_linear_reset_c();
    /* wave684 Cap residual: typecheck generic function bodies too.
     * Prior skip (num_generic_params > 0 → return 0) left free-T / Wrap<T>
     * bodies unchecked: unknown fields, concrete S.nope, and other typeck
     * errors soft-greened until (if ever) monomorphized. Free type-params
     * stay TYPE_NAMED without layout; field gate hard-fails them (wave684).
     * Keep checking: id/geta/return of T, Wrap.val mono, concrete layouts. */
    num_generic_params = pipeline_module_func_num_generic_params_at(module, func_idx);
    /* wave1219: removed (void)num_generic_params — C-style cast unsupported in X. */
    body_ref = pipeline_module_func_body_ref_at(module, func_idx);
    if (ast.ref_is_null(body_ref) || pipeline_module_func_is_extern_at(module, func_idx) != 0) {
      return 0;
    }
    ret_ty_ref = pipeline_module_func_return_type_at(module, func_idx);
    if (check_block(module, arena, body_ref, ret_ty_ref, ctx) != 0) {
      fn_name_len = pipeline_module_func_name_len_at(module, func_idx);
      pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0));
      /* See implementation. */
      let fail_kind_cb: i32 = -5;
      driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb);
      return fail_kind_cb;
    }
    if (!ast.ref_is_null(ret_ty_ref)) {
      rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref);
      if (rt_kind != ord_void && func_body_has_implicit_return_tail(arena, body_ref)) {
        fn_name_len = pipeline_module_func_name_len_at(module, func_idx);
        pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0));
        let fail_kind_tail: i32 = -6;
        driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail);
        return fail_kind_tail;
      }
    }
    return 0;
  }
}

/**
 * Typecheck every function body in [func_i, num_funcs) on the entry module.
 *
 * Iterative walk (while), not recursion. Historical Cap residual used
 * tail-style recursion (func_i+1); mega modules (~2k funcs, e.g.
 * runtime_pipeline_abi.x) forced O(n) stack frames and multi-minute wall
 * under product pure-asm / -E (Stage12.0.5 hang map: 180s timeout mid-typeck
 * with empty OUT — false hang). Same semantics as the recursive form:
 * check_block + implicit-return tail; fail-fast -5/-6; entry-module set once
 * when starting at func_i==0.
 *
 * @param module *Module — entry module after parse
 * @param arena *ASTArena — type/arena storage for check_block
 * @param ctx *PipelineDepCtx — current_func_index + dep map
 * @param func_i i32 — start index (callers pass 0; resume offset kept for API)
 * @param num_funcs i32 — exclusive end (pipeline_module_num_funcs)
 * @return i32 — 0 ok; -5 check_block fail; -6 non-void implicit tail
 * PLATFORM: SHARED — G.7 sole all-funcs typeck walker; seed twin aligned.
 */
export function typeck_x_ast_check_all_funcs_loop(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx,
func_i: i32, num_funcs: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let i: i32 = 0;
    let body_ref: i32 = 0;
    let ret_ty_ref: i32 = 0;
    let fn_name_len: i32 = 0;
    let num_generic_params: i32 = 0;
    let ord_void: i32 = 16;
    let rt_kind: i32 = 0;
    let no_func_ix: i32 = -1;
    let fail_kind_cb: i32 = -5;
    let fail_kind_tail: i32 = -6;
    i = func_i;
    if (i >= num_funcs) {
      pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
      return 0;
    }
    // Entry-module dep map once when the walk starts at the first function.
    if (i == 0) {
      pipeline_typeck_set_entry_module_for_dep_map_c(module);
    }
    // Iterative per-func typeck — constant stack (mega-safe). Same body as
    // historical recursive step; matches typeck_patch_all_body_parent_links.
    while (i < num_funcs) {
      pipeline_dep_ctx_set_current_func_index(ctx, i);
      fn_name_len = pipeline_module_func_name_len_at(module, i);
      pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0));
      driver_diagnostic_typeck_fn_enter(i, typeck_scratch64_slot(0), fn_name_len);
      // wave684: do not skip generic bodies (see typeck_x_ast_check_one_func).
      num_generic_params = pipeline_module_func_num_generic_params_at(module, i);
      body_ref = pipeline_module_func_body_ref_at(module, i);
      if (!ast.ref_is_null(body_ref) && pipeline_module_func_is_extern_at(module, i) == 0) {
        ret_ty_ref = pipeline_module_func_return_type_at(module, i);
        if (check_block(module, arena, body_ref, ret_ty_ref, ctx) != 0) {
          fn_name_len = pipeline_module_func_name_len_at(module, i);
          pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0));
          driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb);
          pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
          return fail_kind_cb;
        }
        if (!ast.ref_is_null(ret_ty_ref)) {
          rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref);
          if (rt_kind != ord_void && func_body_has_implicit_return_tail(arena, body_ref)) {
            fn_name_len = pipeline_module_func_name_len_at(module, i);
            pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0));
            driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail);
            pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
            return fail_kind_tail;
          }
        }
      }
      pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
      i = i + 1;
    }
    pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
    return 0;
  }
}

/**
 * See implementation.
 */
/* Rest-lane C walker: stamp anonymous return-position STRUCT_LITs with the
 * declared return type name (parse-only dep prerun backfill). PLATFORM: SHARED. */
export extern function glue_stamp_return_lits_in_block_c(arena: *ASTArena, block_ref: i32, rty: i32): void;
/* Rest-lane C walker: stamp block_ref on nested VAR exprs (parse-only dep
 * prerun backfill; feeds the emit-phase var type backfill climb). SHARED. */
export extern function glue_fill_var_block_refs_c(arena: *ASTArena, block_ref: i32): void;

export function typeck_patch_all_body_parent_links(module: *Module, arena: *ASTArena): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let i: i32 = 0;
    let num: i32 = 0;
    let br: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena) {
      return;
    }
    num = pipeline_module_num_funcs(module);
    while (i < num) {
      br = pipeline_module_func_body_ref_at(module, i);
      if (!ast.ref_is_null(br)) {
        pipeline_patch_block_parent_links(arena, br, 0);
        // PLATFORM: SHARED — parse-only dep prerun backfill: anonymous
        // STRUCT_LIT in return position is unstamped without typeck; stamp
        // the declared return type name so emit-side field offsets / store
        // sizes / return classification stop inferring per-field (std.string
        // new() `data: []` mis-sized as a 16B slice). Rest-lane C walker.
        let rty_pl: i32 = pipeline_module_func_return_type_at(module, i);
        if (rty_pl > 0) {
          glue_stamp_return_lits_in_block_c(arena, br, rty_pl);
        }
        // PLATFORM: SHARED — parser only stamps block-level stmt exprs;
        // stamp nested VAR block_refs so the emit-phase param/let type
        // backfill climb (glue_fill_var_types_from_params_for_func) works
        // on parse-only deps (field load widths else default to 8 bytes).
        glue_fill_var_block_refs_c(arena, br);
      }
      i = i + 1;
    }
  }
}

/**
 * See implementation.
 */
/**
 * wave421: product-path trait completeness (skip_tl registry filled at parse).
 * @param module *Module — entry module after parse_into
 * @return i32 — 0 ok; -1 missing method (diagnostic emitted)
 * PLATFORM: SHARED typeck
 */
export extern function xlang_trait_check_impls_complete_c(module: *Module): i32;

/**
 * Typecheck one module top-level let/const initializer.
 *
 * Function-scope lets go through typeck_check_block_one_const / one_let.
 * typeck_x_ast historically walked only function bodies, so
 * `const x: i32 = [1, 2]` / `const x: i32 = foo()` at module scope skipped
 * T001. This is G.7 complete of the same check_expr + coerce + const-expr
 * whitelist (not a second checker).
 *
 * After lit/array coerce and integer widen, a remaining TYPE_FN decl vs
 * Cap *u8 (bare same-module fn name) or TYPE_FN↔TYPE_FN mismatch is
 * accepted only via typeck_fnptr_surface_compat — same authority as
 * typeck_check_block_one_let / assign. Arity/ret/opaque Cap stay T001.
 *
 * @param module *Module — entry or library module after parse
 * @param arena *ASTArena — expr/type arena
 * @param ctx *PipelineDepCtx — current_func_index / current_block_ref
 * @param tl i32 — top-level let index; must be in range
 * @return i32 — 0 ok, -1 typeck fail (diagnostic already emitted)
 * PLATFORM: SHARED typeck. Do not fold module const / import FIELD as i32.
 */
export function typeck_x_ast_check_one_top_level_let(module: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx, tl: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let init_ref: i32 = 0;
    let decl_ty: i32 = 0;
    let is_const: i32 = 0;
    let init_ty: i32 = 0;
    let init_ctx: i32 = 0;
    let eb: *u8 = 0 as *u8;
    let gb: *u8 = 0 as *u8;
    let el: i32 = 0;
    let gl: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return -1;
    }
    if (tl < 0 || tl >= module.num_top_level_lets) {
      return -1;
    }
    init_ref = pipeline_module_top_level_let_init_ref(module, tl);
    decl_ty = pipeline_module_top_level_let_type_ref(module, tl);
    is_const = pipeline_module_top_level_let_is_const(module, tl);
    if (ast.ref_is_null(init_ref)) {
      return 0;
    }
    if (is_const != 0) {
      if (typeck_expr_is_const_with_module_consts(arena, init_ref) == 0) {
        typeck_const_init_not_constant(pipeline_expr_line_at(arena, init_ref),
            pipeline_expr_col_at(arena, init_ref));
        return -1;
      }
    }
    init_ctx = 0;
    if (!ast.ref_is_null(decl_ty)) {
      init_ctx = decl_ty;
    }
    if (check_expr(module, arena, init_ref, init_ctx, ctx) != 0) {
      return -1;
    }
    if (ast.ref_is_null(decl_ty)) {
      init_ty = expr_type_ref(arena, init_ref);
      if (ast.ref_is_null(init_ty)) {
        return -1;
      }
      pipeline_module_top_level_let_set_type_ref(module, tl, init_ty);
      return 0;
    }
    if (typeck_coerce_init_expr_to_decl(module, arena, init_ref, decl_ty) < 0) {
      return -1;
    }
    init_ty = expr_type_ref(arena, init_ref);
    if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, decl_ty, init_ty)) {
      if (typeck_integer_widen_ok_refs(arena, decl_ty, init_ty)) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty);
        init_ty = decl_ty;
      }
    }
    /*
     * p3 family: `let f: function(i32): i32 = inc` at module scope.
     * Bare fn VAR is Cap *u8 (wave100); function-scope let/assign already
     * accept via typeck_fnptr_surface_compat. The top-level equal-ref gate
     * used to T001 "expected function, found *u8". Stamp decl when the
     * existing surface gate says yes (allow_opaque=0 — true opaque Cap
     * without recoverable same-module fn stays mismatch).
     * G.7: do not invent a second fnptr checker. PLATFORM: SHARED.
     */
    if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, decl_ty, init_ty)) {
      if (typeck_fnptr_surface_compat(module, arena, decl_ty, init_ty, init_ref, 0) != 0) {
        pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty);
        init_ty = decl_ty;
      }
    }
    if (!ast.ref_is_null(init_ty) && !type_refs_equal(arena, decl_ty, init_ty)) {
      eb = driver_typeck_diag_scratch_expect();
      gb = driver_typeck_diag_scratch_found();
      el = typeck_diag_fmt_type_into(arena, decl_ty, eb, 96);
      gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96);
      driver_diagnostic_typeck_assign_mismatch(0, pipeline_expr_line_at(arena, init_ref),
          pipeline_expr_col_at(arena, init_ref), eb, el, gb, gl);
      return -1;
    }
    return 0;
  }
}

/**
 * Typecheck every module top-level let/const initializer before function bodies.
 *
 * Iterative walk (while), not recursion — same mega-safe discipline as
 * typeck_x_ast_check_all_funcs_loop. Sets current_func_index=-1 and
 * current_block_ref=0 so VAR resolve uses the module table, not a stale block.
 *
 * @param module *Module — entry or library module after parse
 * @param arena *ASTArena — expr/type arena
 * @param ctx *PipelineDepCtx — mutated current_func_index / current_block_ref
 * @return i32 — 0 ok, -1 typeck fail
 * PLATFORM: SHARED typeck. G.7: sole module-let typeck walker.
 */
export function typeck_x_ast_check_top_level_lets(module: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let i: i32 = 0;
    let n: i32 = 0;
    let no_func_ix: i32 = -1;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return -1;
    }
    pipeline_typeck_set_entry_module_for_dep_map_c(module);
    pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix);
    ctx.current_block_ref = 0;
    n = module.num_top_level_lets;
    while (i < n) {
      if (typeck_x_ast_check_one_top_level_let(module, arena, ctx, i) != 0) {
        return -1;
      }
      i = i + 1;
    }
    return 0;
  }
}

export function typeck_x_ast_impl(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let mi: i32 = 0;
    let ret_kind: i32 = 0;
    let ord_i32: i32 = 0;
    let ord_i64: i32 = 5;
    let ord_void: i32 = 16;
    let main_num_generic_params: i32 = 0;
    let body_ref: i32 = 0;
    let body_expr_ref: i32 = 0;
    let ret_ty: i32 = 0;
    let num_funcs: i32 = 0;
    let pipe_marker_ret_ty_ready: i32 = 301;
    let pipe_marker_main_generic_checked: i32 = 302;
    let pipe_marker_layout_validated: i32 = 303;
    let pipe_marker_parent_links_patched: i32 = 304;
    let pipe_marker_main_generic_base: i32 = 320;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return -2;
    }
    /* wave421 Cap residual pure — missing method before per-func check_block.
     * Root: incomplete impl Trait for T was false-green (only free-fn hoist).
     * G.7: xlang_trait_check_impls_complete_c (skip_tl registry). Soft: bounds/dyn. */
    if (xlang_trait_check_impls_complete_c(module) != 0) {
      return -1;
    }
    mi = pipeline_module_main_func_index(module);
    if (pipeline_module_func_is_extern_at(module, mi) != 0
    && ast.ref_is_null(pipeline_module_func_body_ref_at(module, mi))) {
      return -1;
    }
    body_ref = pipeline_module_func_body_ref_at(module, mi);
    body_expr_ref = pipeline_module_func_body_expr_ref_at(module, mi);
    if (ast.ref_is_null(body_ref) && ast.ref_is_null(body_expr_ref)) {
      return -2;
    }
    ret_ty = pipeline_module_func_return_type_at(module, mi);
    if (ast.ref_is_null(ret_ty)) {
      return -3;
    }
    typeck_driver_diagnostic_pipe_marker(pipe_marker_ret_ty_ready);
    main_num_generic_params = pipeline_module_func_num_generic_params_at(module, mi);
    typeck_driver_diagnostic_pipe_marker(pipe_marker_main_generic_base + main_num_generic_params);
    if (main_num_generic_params > 0) {
      return -12;
    }
    typeck_driver_diagnostic_pipe_marker(pipe_marker_main_generic_checked);
    /* PLATFORM: SHARED — process entry may be i32/i64 (exit code) or void (Zig-like
     * implicit exit 0). Codegen maps void main → C int32_t main + return 0. */
    ret_kind = pipeline_type_kind_ord_at(arena, ret_ty);
    if (ret_kind != ord_i32 && ret_kind != ord_i64 && ret_kind != ord_void) {
      return -4;
    }
    if (typeck_validate_struct_layouts_zero_padding(module, arena) != 0) {
      return -7;
    }
    typeck_driver_diagnostic_pipe_marker(pipe_marker_layout_validated);
    typeck_patch_all_body_parent_links(module, arena);
    typeck_driver_diagnostic_pipe_marker(pipe_marker_parent_links_patched);
    if (typeck_x_ast_check_top_level_lets(module, arena, ctx) != 0) {
      return -5;
    }
    num_funcs = pipeline_module_num_funcs(module);
    let rc_funcs: i32 = typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
    // L6 unused-binding hints + WPO_DUMP_CALLGRAPH after successful entry typeck.
    if (rc_funcs == 0) {
      pipeline_typeck_unused_binding_hints(module, arena);
      pipeline_typeck_wpo_dump_callgraph(module, arena, ctx);
    }
    return rc_funcs;
  }
}

/**
 * See implementation.
 */
export function typeck_x_ast_library(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let num_funcs: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return -5;
    }
    if (typeck_validate_struct_layouts_zero_padding(module, arena) != 0) {
      return -7;
    }
    typeck_patch_all_body_parent_links(module, arena);
    if (typeck_x_ast_check_top_level_lets(module, arena, ctx) != 0) {
      return -5;
    }
    num_funcs = pipeline_module_num_funcs(module);
    let rc_lib: i32 = typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
    // L6 unused-binding hints + WPO_DUMP_CALLGRAPH after successful library typeck.
    if (rc_lib == 0) {
      pipeline_typeck_unused_binding_hints(module, arena);
      pipeline_typeck_wpo_dump_callgraph(module, arena, ctx);
    }
    return rc_lib;
  }
}

/**
 * See implementation.
 */
export function typeck_x_ast(module: *Module, arena: *ASTArena, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let mi: i32 = 0;
    let num_funcs: i32 = 0;
    if (module == 0 as *Module) {
      return -10;
    }
    mi = pipeline_module_main_func_index(module);
    num_funcs = pipeline_module_num_funcs(module);
    if (mi < 0) {
      return -10;
    }
    if (mi >= num_funcs) {
      return -11;
    }
    return typeck_x_ast_impl(module, arena, ctx);
  }
}


/* ============================================================================
 * 8.3.3 host-cc leave: historical pipeline_*_c thin link faces for
 * pipeline_glue_strict_minimal (zero business logic → typeck_* authority).
 * PLATFORM: SHARED — typeck_x.o only; not pipeline_x host-cc mega-TU.
 * ============================================================================ */

/**
 * Thin link face: historical C name → typeck_field_import_binding.
 * @param module *Module — entry module
 * @param arena *ASTArena — expression arena
 * @param expr_ref i32 — FIELD_ACCESS expr
 * @param base_ref i32 — base expr
 * @param ctx *PipelineDepCtx — dep pool (may be null)
 * @return i32 — 1 handled, 0 continue
 * PLATFORM: SHARED — strict_minimal residual only
 */
#[no_mangle]
export function pipeline_typeck_field_import_binding_resolve_c(module: *Module, arena: *ASTArena, expr_ref: i32, base_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_field_import_binding(module, arena, expr_ref, base_ref, ctx);
}

/**
 * Thin link face: historical C name → typeck_field_layout_named.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32
 * @param base_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 2 enum done, 0 continue
 * PLATFORM: SHARED — strict_minimal residual only
 */
#[no_mangle]
export function pipeline_typeck_field_layout_named_c(module: *Module, arena: *ASTArena, expr_ref: i32, base_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_field_layout_named(module, arena, expr_ref, base_ref, ctx);
}

/**
 * Thin link face: historical C name → typeck_field_unknown_hard_fail.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32
 * @param base_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — non-zero hard-fail
 * PLATFORM: SHARED — strict_minimal residual only
 */
#[no_mangle]
export function pipeline_typeck_field_unknown_hard_fail_c(module: *Module, arena: *ASTArena, expr_ref: i32, base_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_field_unknown_hard_fail(module, arena, expr_ref, base_ref, ctx);
}

/**
 * Thin link face: historical C name → typeck_named_is_module_concrete.
 * @param module *Module
 * @param ctx *PipelineDepCtx
 * @param name *u8
 * @param name_len i32
 * @return i32 — 1 concrete, 0 not
 * PLATFORM: SHARED — strict_minimal residual only
 */
#[no_mangle]
export function pipeline_typeck_named_is_module_concrete_c(module: *Module, ctx: *PipelineDepCtx, name: *u8, name_len: i32): i32 {
  return typeck_named_is_module_concrete(module, ctx, name, name_len);
}

// ===========================================================================
// wave240: typeck with_arena nest BSS pure leave
// (was Cap residual pipeline_typeck_region_assign.c static body stack +
//  scope_n + push/pop + wave237 residual n_at/current_body_ref faces)
// G.7 product authority (typeck_x.o; typeck_gen hand-sync when -E SEGV):
//   pipeline_typeck_with_arena_scope_n_at
//   pipeline_typeck_with_arena_current_body_ref_c
//   pipeline_typeck_with_arena_scope_push_c
//   pipeline_typeck_with_arena_scope_pop_c
//   pipeline_typeck_with_arena_scope_reset_c
// Residual scan tree / check_block_one_region write pure push/pop/reset only.
// wave241: region-label scope stack also pure (below).
// PLATFORM: SHARED freestanding — nest body refs are platform-agnostic.
// ===========================================================================

let g_typeck_with_arena_body_stack: i32[8] = [];
let g_typeck_with_arena_scope_n: i32 = 0;

/**
 * MEM-C1: current with_arena nest depth (0 = outside any with_arena).
 * @return i32 — nest count; 0 when empty
 * wave240 pure: G.7 authority (was Cap residual region_assign BSS face).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_with_arena_scope_n_at(): i32 {
  return g_typeck_with_arena_scope_n;
}

/**
 * MEM-C1: current with_arena body block_ref (stack top); 0 if none.
 * @return i32 — body block_ref or 0
 * wave240 pure: G.7 authority (was Cap residual region_assign BSS face).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_with_arena_current_body_ref_c(): i32 {
  if (g_typeck_with_arena_scope_n > 0) {
    return g_typeck_with_arena_body_stack[g_typeck_with_arena_scope_n - 1];
  }
  return 0;
}

/**
 * MEM-C1: push with_arena body block_ref before scanning/typeck of the body.
 * Contract: body_ref <= 0 or nest full (>= 8) → no-op.
 * @param body_ref i32 — with_arena body block_ref (>0)
 * @return void
 * wave240 pure: G.7 authority (was Cap residual static push).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_with_arena_scope_push_c(body_ref: i32): void {
  if (body_ref <= 0) {
    return;
  }
  if (g_typeck_with_arena_scope_n >= 8) {
    return;
  }
  g_typeck_with_arena_body_stack[g_typeck_with_arena_scope_n] = body_ref;
  g_typeck_with_arena_scope_n = g_typeck_with_arena_scope_n + 1;
}

/**
 * MEM-C1: pop with_arena nest after body scan/typeck.
 * Contract: empty stack → no-op.
 * @return void
 * wave240 pure: G.7 authority (was Cap residual static pop).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_with_arena_scope_pop_c(): void {
  if (g_typeck_with_arena_scope_n > 0) {
    g_typeck_with_arena_scope_n = g_typeck_with_arena_scope_n - 1;
  }
}

/**
 * MEM-C1: clear with_arena nest before module-level post-typeck scan.
 * @return void
 * wave240 pure: G.7 authority (was Cap residual direct scope_n = 0 write).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_with_arena_scope_reset_c(): void {
  g_typeck_with_arena_scope_n = 0;
}

// end wave240 pure-owned leave

// ===========================================================================
// wave241: typeck region-label scope BSS pure leave
// (was Cap residual pipeline_typeck_region_assign.c:
//  g_typeck_region_saved_len / saved_label / scope_n +
//  pipeline_dep_ctx_scope_region_{push,pop,len_at}_c)
// G.7 product authority (typeck_x.o; typeck_gen hand-sync when -E SEGV):
//   pipeline_dep_ctx_scope_region_push_c
//   pipeline_dep_ctx_scope_region_pop_c
//   pipeline_dep_ctx_scope_region_len_at
//   pipeline_typeck_region_scope_reset_c
// Residual scan tree / check_block_one_region / stamp_let only call pure faces.
// Saved labels are flattened u8[8*128] (slot * 128 + i) — no nested array BSS.
// Preserve residual C quirks: push saves prior label only when prev_len <= 63;
// pop restores when saved_len <= 127 (exact leave fidelity).
// PLATFORM: SHARED freestanding — region labels are platform-agnostic bytes.
// ===========================================================================

let g_typeck_region_saved_len: i32[8] = [];
let g_typeck_region_saved_label: u8[1024] = [];
let g_typeck_region_scope_n: i32 = 0;

/**
 * M-3: save current ctx region label and set new domain label for nesting.
 * Used by region block scan/typeck so inner lets inherit tagged T[] labels.
 * Contract: null ctx/label or label_len outside [1,127] → -1.
 *           Nest full (>= 8) → -1.
 * @param ctx *PipelineDepCtx — typeck dep context (mutates scope region fields)
 * @param label *u8 — new region label bytes (not required to be NUL-terminated)
 * @param label_len i32 — byte count in [1,127]
 * @return i32 — 0 success, -1 failure
 * wave241 pure: G.7 authority (was Cap residual region_assign BSS body).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_dep_ctx_scope_region_push_c(ctx: *PipelineDepCtx, label: *u8,
                                                     label_len: i32): i32 {
  if (ctx == 0 as *PipelineDepCtx || label == 0 as *u8) {
    return -1;
  }
  if (label_len <= 0 || label_len > 127) {
    return -1;
  }
  if (g_typeck_region_scope_n >= 8) {
    return -1;
  }
  let slot: i32 = g_typeck_region_scope_n;
  let prev_len: i32 = ctx.typeck_scope_region_len;
  g_typeck_region_saved_len[slot] = prev_len;
  // Residual fidelity: only snapshot prior label when prev_len in (0, 63].
  if (prev_len > 0 && prev_len <= 63) {
    let base: i32 = slot * 128;
    let i: i32 = 0;
    while (i < 128) {
      g_typeck_region_saved_label[base + i] = ctx.typeck_scope_region_label[i];
      i = i + 1;
    }
  }
  // Clear then write new label into ctx (128-byte fixed field).
  let j: i32 = 0;
  while (j < 128) {
    ctx.typeck_scope_region_label[j] = 0;
    j = j + 1;
  }
  let k: i32 = 0;
  while (k < label_len) {
    ctx.typeck_scope_region_label[k] = label[k];
    k = k + 1;
  }
  ctx.typeck_scope_region_len = label_len;
  g_typeck_region_scope_n = g_typeck_region_scope_n + 1;
  return 0;
}

/**
 * M-3: restore region domain label saved by matching push.
 * Contract: null ctx or empty stack → no-op.
 * @param ctx *PipelineDepCtx — typeck dep context (mutates scope region fields)
 * @return void
 * wave241 pure: G.7 authority (was Cap residual region_assign BSS body).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_dep_ctx_scope_region_pop_c(ctx: *PipelineDepCtx): void {
  if (ctx == 0 as *PipelineDepCtx) {
    return;
  }
  if (g_typeck_region_scope_n <= 0) {
    return;
  }
  g_typeck_region_scope_n = g_typeck_region_scope_n - 1;
  let slot: i32 = g_typeck_region_scope_n;
  let saved_len: i32 = g_typeck_region_saved_len[slot];
  ctx.typeck_scope_region_len = saved_len;
  let j: i32 = 0;
  while (j < 128) {
    ctx.typeck_scope_region_label[j] = 0;
    j = j + 1;
  }
  // Residual fidelity: restore bytes only when saved_len in (0, 127].
  if (saved_len > 0 && saved_len <= 127) {
    let base: i32 = slot * 128;
    let i: i32 = 0;
    while (i < 128) {
      ctx.typeck_scope_region_label[i] = g_typeck_region_saved_label[base + i];
      i = i + 1;
    }
  }
}

/**
 * M-3: current ctx region domain label length; 0 means outside a region block.
 * @param ctx *PipelineDepCtx — typeck dep context
 * @return i32 — scope region label length, or 0 if null/empty
 * wave241 pure: G.7 authority (was Cap residual region_assign face).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_dep_ctx_scope_region_len_at(ctx: *PipelineDepCtx): i32 {
  if (ctx == 0 as *PipelineDepCtx) {
    return 0;
  }
  if (ctx.typeck_scope_region_len > 0) {
    return ctx.typeck_scope_region_len;
  }
  return 0;
}

/**
 * M-3: clear region-label nest depth before module-level post-typeck scan.
 * Does not clear ctx fields — caller still zeros typeck_scope_region_*.
 * @return void
 * wave241 pure: G.7 authority (was Cap residual direct scope_n = 0 write).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_region_scope_reset_c(): void {
  g_typeck_region_scope_n = 0;
}

// end wave241 pure-owned leave

// ---------------------------------------------------------------------------
// wave242: typeck post-scan stack-escape tree pure leave
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   typeck_scan_expr_stack_escape_c
//   typeck_scan_block_stack_escape_c
//   pipeline_typeck_scan_module_struct_stack_escape_c  (product ABI)
// Cap residual region_assign deletes static scan bodies (dual-export ban).
// Residual fidelity: nested while/for/if fail paths may leave current_block_ref
// unrestored (same as former host-cc residual).
// PLATFORM: SHARED freestanding typeck WPO-S3 / M-3 post-scan.
// ---------------------------------------------------------------------------

/**
 * WPO-S3: single-expr assign/call/return stack-escape scan (post-typeck).
 * Dispatches assign-like / RETURN / CALL through pure check faces; CALL also
 * uses pure pipeline_typeck_check_call_struct_stack_escape_c (wave244;
 * helpers still Cap residual).
 * @param m *Module — entry module under scan
 * @param a *ASTArena — arena for expr/type refs
 * @param ctx *PipelineDepCtx — mutates current_func_index / current_block_ref
 * @param func_ix i32 — enclosing function index (>=0)
 * @param expr_ref i32 — expression to scan (>0)
 * @return i32 — 0 OK; -1 escape (diag already printed)
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function typeck_scan_expr_stack_escape_c(m: *Module, a: *ASTArena, ctx: *PipelineDepCtx,
func_ix: i32, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let k: i32 = 0;
    let saved_ix: i32 = 0;
    let saved_br: i32 = 0;
    let l: i32 = 0;
    let r: i32 = 0;
    let op: i32 = 0;
    let func_ret: i32 = 0;
    if (m == 0 as *Module || a == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || expr_ref <= 0
    || func_ix < 0) {
      return 0;
    }
    saved_ix = ctx.current_func_index;
    saved_br = ctx.current_block_ref;
    ctx.current_func_index = func_ix;
    k = pipeline_expr_kind_ord_at(a, expr_ref);
    if (glue_expr_kind_is_assign_like_ord(k) != 0) {
      l = pipeline_expr_binop_left_ref_at(a, expr_ref);
      r = pipeline_expr_binop_right_ref_at(a, expr_ref);
      if (typeck_check_struct_stack_escape_assign(m, a, expr_ref, l, r, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
      if (typeck_check_scope_borrow_assign(m, a, expr_ref, l, r, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
      if (typeck_check_allocator_region_assign(m, a, expr_ref, l, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
    } else if (k == 41) {
      // EXPR_RETURN = 41
      op = pipeline_expr_unary_operand_ref_at(a, expr_ref);
      func_ret = pipeline_module_func_return_type_at(m, func_ix);
      if (typeck_check_scope_borrow_return(m, a, expr_ref, op, func_ret, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
      if (typeck_check_allocator_region_return(a, expr_ref, func_ret) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
      if (pipeline_typeck_check_return_slice_region_in_scope_c(a, expr_ref, func_ret, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
      if (typeck_check_return_slice_region(a, expr_ref, op, func_ret) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
    } else if (k == 48) {
      // EXPR_CALL = 48
      if (pipeline_typeck_check_call_struct_stack_escape_c(m, a, expr_ref, ctx) != 0) {
        ctx.current_func_index = saved_ix;
        ctx.current_block_ref = saved_br;
        return -1;
      }
    }
    ctx.current_func_index = saved_ix;
    ctx.current_block_ref = saved_br;
    return 0;
  }
}

/**
 * WPO-S3: recursive block scan — expr_stmts + final_expr + stmt_order
 * (expr / while / for / if / region). Region path mirrors check_block_one_region
 * (with_arena / labeled region / unsafe depth).
 * @param m *Module — entry module
 * @param a *ASTArena — arena
 * @param ctx *PipelineDepCtx — mutates current_block_ref + region/with_arena nests
 * @param func_ix i32 — enclosing function index
 * @param block_ref i32 — block to walk
 * @return i32 — 0 OK; -1 escape detected
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function typeck_scan_block_stack_escape_c(m: *Module, a: *ASTArena, ctx: *PipelineDepCtx,
func_ix: i32, block_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let nes: i32 = 0;
    let ei: i32 = 0;
    let fin: i32 = 0;
    let nso: i32 = 0;
    let i: i32 = 0;
    let saved_br: i32 = 0;
    let k: i32 = 0;
    let idx: i32 = 0;
    let er: i32 = 0;
    let br: i32 = 0;
    let tr: i32 = 0;
    let wa_cap: i32 = 0;
    let is_unsafe: i32 = 0;
    let saved_ud: i32 = 0;
    let llen: i32 = 0;
    let lbl: u8[128] = [];
    if (m == 0 as *Module || a == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || block_ref <= 0
    || func_ix < 0) {
      return 0;
    }
    saved_br = ctx.current_block_ref;
    ctx.current_block_ref = block_ref;
    nes = ast.ast_block_num_expr_stmts(a, block_ref);
    ei = 0;
    while (ei < nes) {
      er = ast.ast_block_expr_stmt_ref(a, block_ref, ei);
      if (er > 0 && typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, er) != 0) {
        ctx.current_block_ref = saved_br;
        return -1;
      }
      ei = ei + 1;
    }
    fin = ast.ast_block_final_expr_ref(a, block_ref);
    if (fin > 0 && typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, fin) != 0) {
      ctx.current_block_ref = saved_br;
      return -1;
    }
    nso = ast.ast_block_num_stmt_order(a, block_ref);
    i = 0;
    while (i < nso) {
      k = ast.ast_block_stmt_order_kind(a, block_ref, i) as i32;
      idx = ast.ast_block_stmt_order_idx(a, block_ref, i);
      if (k == 2 && idx >= 0 && idx < ast.ast_block_num_expr_stmts(a, block_ref)) {
        er = ast.ast_block_expr_stmt_ref(a, block_ref, idx);
        if (er > 0 && typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, er) != 0) {
          ctx.current_block_ref = saved_br;
          return -1;
        }
      } else if (k == 3 && idx >= 0 && idx < ast.ast_block_num_loops(a, block_ref)) {
        br = ast.ast_block_while_body_ref(a, block_ref, idx);
        // Residual fidelity: fail path does not restore saved_br.
        if (br > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) != 0) {
          return -1;
        }
      } else if (k == 4 && idx >= 0 && idx < ast.ast_block_num_for_loops(a, block_ref)) {
        br = ast.ast_block_for_body_ref(a, block_ref, idx);
        if (br > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) != 0) {
          return -1;
        }
      } else if (k == 5 && idx >= 0 && idx < ast.ast_block_num_if_stmts(a, block_ref)) {
        tr = ast.ast_block_if_then_body_ref(a, block_ref, idx);
        er = ast.ast_block_if_else_body_ref(a, block_ref, idx);
        if (tr > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, tr) != 0) {
          return -1;
        }
        if (er > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, er) != 0) {
          return -1;
        }
      } else if (k == 6 && idx >= 0 && idx < ast.ast_block_num_regions(a, block_ref)) {
        wa_cap = pipeline_block_region_with_arena_cap_ref(a, block_ref, idx);
        br = ast.ast_block_region_body_ref(a, block_ref, idx);
        is_unsafe = pipeline_block_region_is_unsafe(a, block_ref, idx);
        saved_ud = 0;
        if (is_unsafe != 0) {
          saved_ud = pipeline_typeck_unsafe_depth_push_c(ctx);
        }
        if (wa_cap > 0) {
          pipeline_typeck_with_arena_scope_push_c(br);
          if (br > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) != 0) {
            pipeline_typeck_with_arena_scope_pop_c();
            if (is_unsafe != 0) {
              pipeline_typeck_unsafe_depth_pop_c(ctx, saved_ud);
            }
            ctx.current_block_ref = saved_br;
            return -1;
          }
          pipeline_typeck_with_arena_scope_pop_c();
        } else {
          llen = pipeline_block_region_label_len(a, block_ref, idx);
          if (llen > 0) {
            pipeline_block_region_label_copy64(a, block_ref, idx, &lbl[0]);
            if (pipeline_dep_ctx_scope_region_push_c(ctx, &lbl[0], llen) != 0) {
              if (is_unsafe != 0) {
                pipeline_typeck_unsafe_depth_pop_c(ctx, saved_ud);
              }
              ctx.current_block_ref = saved_br;
              return -1;
            }
          }
          if (br > 0 && typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) != 0) {
            if (llen > 0) {
              pipeline_dep_ctx_scope_region_pop_c(ctx);
            }
            if (is_unsafe != 0) {
              pipeline_typeck_unsafe_depth_pop_c(ctx, saved_ud);
            }
            ctx.current_block_ref = saved_br;
            return -1;
          }
          if (llen > 0) {
            pipeline_dep_ctx_scope_region_pop_c(ctx);
          }
        }
        if (is_unsafe != 0) {
          pipeline_typeck_unsafe_depth_pop_c(ctx, saved_ud);
        }
      }
      i = i + 1;
    }
    ctx.current_block_ref = saved_br;
    return 0;
  }
}

/**
 * Module-level post-typeck scan for struct stack-pointer escape.
 * Iterates non-extern non-generic funcs; resets with_arena + region nests first.
 * Product ABI face (runtime_pipeline_abi / parse_orch / after_parse_ok).
 * @param module *Module — module under scan
 * @param arena *ASTArena — arena
 * @param ctx *PipelineDepCtx — dep context (scope region fields zeroed)
 * @return i32 — 0 OK / skip; -1 escape
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_scan_module_struct_stack_escape_c(module: *Module, arena: *ASTArena,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let i: i32 = 0;
    let nf: i32 = 0;
    let body: i32 = 0;
    let num_generic_params: i32 = 0;
    let j: i32 = 0;
    let skip_env: *u8 = 0 as *u8;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx) {
      return 0;
    }
    skip_env = link_abi_getenv("XLANG_SKIP_STACK_ESCAPE" as *u8);
    if (skip_env != 0 as *u8) {
      return 0;
    }
    pipeline_typeck_with_arena_scope_reset_c();
    pipeline_typeck_region_scope_reset_c();
    ctx.typeck_scope_region_len = 0;
    j = 0;
    while (j < 128) {
      ctx.typeck_scope_region_label[j] = 0;
      j = j + 1;
    }
    nf = pipeline_module_num_funcs(module);
    i = 0;
    while (i < nf) {
      if (pipeline_module_func_is_extern_at(module, i) != 0) {
        i = i + 1;
        continue;
      }
      num_generic_params = pipeline_module_func_num_generic_params_at(module, i);
      if (num_generic_params > 0) {
        i = i + 1;
        continue;
      }
      body = pipeline_module_func_body_ref_at(module, i);
      if (body <= 0) {
        i = i + 1;
        continue;
      }
      if (typeck_scan_block_stack_escape_c(module, arena, ctx, i, body) != 0) {
        return -1;
      }
      i = i + 1;
    }
    return 0;
  }
}

// end wave242 pure-owned leave

// ---------------------------------------------------------------------------
// wave243: typeck stamp_let + read_ptr cluster pure leave
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_is_read_ptr_slice_callee_c
//   pipeline_typeck_read_ptr_slice_return_ref_c
//   pipeline_type_stamp_block_let_region_c
// Cap residual region_assign deletes second bodies (dual-export ban).
// PLATFORM: SHARED freestanding typeck M-3 stamp / M-5 read_ptr.
// ---------------------------------------------------------------------------

/**
 * M-5: return 1 if callee name is a read_ptr slice producer (auto-binds
 * io_read_ptr region on the return type).
 * Names: read_ptr_slice / xlang_io_read_ptr_slice / driver_read_ptr_slice /
 * io_read_ptr_slice.
 * @param name *u8 — callee name bytes (not required NUL-terminated)
 * @param name_len i32 — byte count; <=0 or null → 0
 * @return i32 — 1 match; 0 no match / invalid
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_is_read_ptr_slice_callee_c(name: *u8, name_len: i32): i32 {
  if (name == 0 as *u8 || name_len <= 0) {
    return 0;
  }
  // Residual fidelity: host-cc used name_len gates 14/19/18/16 with memcmp of
  // that many bytes (not full C-string strlen for xlang_/driver_ prefixes).
  if (name_len == 14 && name_equal(name, name_len, "read_ptr_slice" as *u8, 14)) {
    return 1;
  }
  if (name_len == 19 && name_equal(name, name_len, "xlang_io_read_ptr_slice" as *u8, 19)) {
    return 1;
  }
  if (name_len == 18 && name_equal(name, name_len, "driver_read_ptr_slice" as *u8, 18)) {
    return 1;
  }
  if (name_len == 16 && name_equal(name, name_len, "io_read_ptr_slice" as *u8, 16)) {
    return 1;
  }
  return 0;
}

/**
 * Return 1 if callee is a SIMD comptime builtin lowered from @shuffle / @select.
 * Names: simd_shuffle (12) / simd_select (11). Codegen inlines; no module fi.
 * @param name *u8 — callee name bytes (not required NUL-terminated)
 * @param name_len i32 — byte count; <=0 or null → 0
 * @return i32 — 1 match; 0 no match / invalid
 * PLATFORM: SHARED freestanding typeck. G.7 single gate for @ simd CALL names.
 */
#[no_mangle]
export function pipeline_typeck_is_simd_comptime_callee_c(name: *u8, name_len: i32): i32 {
  if (name == 0 as *u8 || name_len <= 0) {
    return 0;
  }
  if (name_len == 12 && name_equal(name, name_len, "simd_shuffle" as *u8, 12)) {
    return 1;
  }
  if (name_len == 11 && name_equal(name, name_len, "simd_select" as *u8, 11)) {
    return 1;
  }
  return 0;
}

/**
 * M-5: allocate or find u8[]<io_read_ptr> type pool ref for read_ptr return.
 * @param arena *ASTArena — type arena; null → 0
 * @return i32 — type_ref (>0) or 0 on failure
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_read_ptr_slice_return_ref_c(arena: *ASTArena): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let u8_ref: i32 = 0;
    if (arena == 0 as *ASTArena) {
      return 0;
    }
    // kind_ord 2 = TYPE_U8 (same as Cap residual host-cc face).
    u8_ref = pipeline_type_ensure_by_kind_ord(arena, 2);
    if (u8_ref <= 0) {
      return 0;
    }
    return pipeline_type_find_or_alloc_slice(arena, u8_ref, "io_read_ptr" as *u8, 11);
  }
}

/**
 * M-3: stamp a block-let's T[] type with the current ctx region label.
 * In-place mutation of shared type nodes is forbidden; find_or_alloc a new
 * T[]<label> and write it back via pipeline_block_set_let_type_ref.
 * @param arena *ASTArena — type/block arena
 * @param block_ref i32 — block holding the let (>0)
 * @param let_idx i32 — let index within block (>=0)
 * @param ctx *PipelineDepCtx — active region scope (label + len)
 * @return i32 — 0 no-op/success; -1 find_or_alloc failure
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_type_stamp_block_let_region_c(arena: *ASTArena, block_ref: i32, let_idx: i32,
ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let ty_ref: i32 = 0;
    let rlen: i32 = 0;
    let elem: i32 = 0;
    let stamped: i32 = 0;
    if (arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || block_ref <= 0 || let_idx < 0) {
      return 0;
    }
    rlen = pipeline_dep_ctx_scope_region_len_at(ctx);
    if (rlen <= 0) {
      return 0;
    }
    ty_ref = pipeline_block_let_type_ref(arena, block_ref, let_idx);
    // TYPE_SLICE ord == 11
    if (ty_ref <= 0 || pipeline_type_kind_ord_at(arena, ty_ref) != 11) {
      return 0;
    }
    if (pipeline_type_region_label_len_at(arena, ty_ref) > 0) {
      return 0;
    }
    elem = pipeline_type_elem_ref_at(arena, ty_ref);
    if (elem <= 0) {
      return 0;
    }
    stamped = pipeline_type_find_or_alloc_slice(arena, elem, &ctx.typeck_scope_region_label[0], rlen);
    if (stamped <= 0) {
      return -1;
    }
    if (stamped == ty_ref) {
      return 0;
    }
    return pipeline_block_set_let_type_ref(arena, block_ref, let_idx, stamped);
  }
}

// end wave243 pure-owned leave

// ---------------------------------------------------------------------------
// wave244: typeck one_region + call_struct_stack_escape pure leave
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_check_block_one_region_c
//   pipeline_typeck_check_call_struct_stack_escape_c
// Cap residual region_assign deletes second bodies (dual-export ban).
// PLATFORM: SHARED freestanding typeck M-3 region dispatch / WPO-S3 CALL escape.
// ---------------------------------------------------------------------------

/**
 * M-3 / MEM-C1: typeck a single region or with_arena block.
 * Dispatches unsafe depth push/pop, with_arena nest scope, or labeled
 * region scope around check_block on the region body.
 * with_arena has no domain label; empty label must not skip body typeck
 * (historical AL-04 leak when label_len<=0 returned early).
 * @param module *Module — enclosing module
 * @param arena *ASTArena — block/expr pool
 * @param block_ref i32 — parent block holding the region (>0)
 * @param region_idx i32 — region index within block (>=0)
 * @param return_type_ref i32 — enclosing function return type for body check
 * @param ctx *PipelineDepCtx — unsafe depth + region scope BSS
 * @return i32 — 0 ok / no-op; -1 region push failure or body typeck fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_block_one_region_c(module: *Module, arena: *ASTArena,
block_ref: i32, region_idx: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — region / with_arena / unsafe body typeck dispatch.
  unsafe {
    let label: u8[128] = [];
    let label_len: i32 = 0;
    let body_ref: i32 = 0;
    let wa_cap: i32 = 0;
    let rc: i32 = 0;
    let saved_ud: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || block_ref <= 0 || region_idx < 0) {
      return 0;
    }
    body_ref = ast.ast_block_region_body_ref(arena, block_ref, region_idx);
    if (body_ref <= 0) {
      return 0;
    }
    if (pipeline_block_region_is_unsafe(arena, block_ref, region_idx) != 0) {
      saved_ud = pipeline_typeck_unsafe_depth_push_c(ctx);
      // Module export name is check_block (C symbol typeck_check_block).
      rc = check_block(module, arena, body_ref, return_type_ref, ctx);
      pipeline_typeck_unsafe_depth_pop_c(ctx, saved_ud);
      return rc;
    }
    wa_cap = pipeline_block_region_with_arena_cap_ref(arena, block_ref, region_idx);
    if (wa_cap > 0) {
      // MEM-C1: push with_arena so check_expr / post-scan can report allocator escape.
      pipeline_typeck_with_arena_scope_push_c(body_ref);
      rc = check_block(module, arena, body_ref, return_type_ref, ctx);
      pipeline_typeck_with_arena_scope_pop_c();
      return rc;
    }
    label_len = pipeline_block_region_label_len(arena, block_ref, region_idx);
    if (label_len <= 0) {
      return 0;
    }
    pipeline_block_region_label_copy64(arena, block_ref, region_idx, &label[0]);
    if (pipeline_dep_ctx_scope_region_push_c(ctx, &label[0], label_len) != 0) {
      return -1;
    }
    rc = check_block(module, arena, body_ref, return_type_ref, ctx);
    pipeline_dep_ctx_scope_region_pop_c(ctx);
    return rc;
  }
}

/**
 * WPO-S3 CALL path: reject when &local named-struct pointer is passed alongside
 * an outer *Struct formal (callee may write into longer-lived slot).
 * Cap-T001: skip inside unsafe { }; XLANG_SKIP_STACK_ESCAPE env bypass.
 * Same-frame &local sibling pairs are allowed (not outer).
 * @param module *Module — entry module for resolve + named-struct checks
 * @param arena *ASTArena — call expr / type pool
 * @param call_expr_ref i32 — CALL expr ref
 * @param ctx *PipelineDepCtx — unsafe depth + block-local lookup context
 * @return i32 — 0 ok; -1 escape diagnostic reported
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_call_struct_stack_escape_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — CALL-site stack-local *Struct vs outer *Struct gate.
  unsafe {
    let func_ix: i32 = 0;
    let num_args: i32 = 0;
    let np: i32 = 0;
    let src_i: i32 = 0;
    let dst_j: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let arg_ref: i32 = 0;
    let arg_ty: i32 = 0;
    let arg_elem: i32 = 0;
    let param_ref: i32 = 0;
    let elem_ref: i32 = 0;
    let other_arg: i32 = 0;
    let skip_env: *u8 = 0 as *u8;
    let m_u8: *u8 = 0 as *u8;
    let a_u8: *u8 = 0 as *u8;
    let msg: u8[96] = [];
    let p: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx
    || call_expr_ref <= 0) {
      return 0;
    }
    // Cap-T001: mega parser/typeck/codegen whole-body unsafe may pass &local with *Struct outer.
    if (pipeline_dep_ctx_typeck_unsafe_depth_at(ctx) > 0) {
      return 0;
    }
    m_u8 = module as *u8;
    a_u8 = arena as *u8;
    func_ix = pipeline_typeck_resolve_call_func_index_for_emit_c(m_u8, a_u8, call_expr_ref);
    if (func_ix < 0) {
      return 0;
    }
    num_args = pipeline_expr_call_num_args_at(arena, call_expr_ref);
    np = pipeline_module_func_num_params_at(module, func_ix);
    if (num_args != np || num_args < 2) {
      return 0;
    }
    skip_env = link_abi_getenv("XLANG_SKIP_STACK_ESCAPE" as *u8);
    if (skip_env != 0 as *u8) {
      return 0;
    }
    src_i = 0;
    while (src_i < num_args) {
      arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, src_i);
      if (typeck_expr_is_addr_of_block_local(module, arena, ctx, arg_ref) != 0) {
        // Only *Struct &local triggers (not &local_i32).
        arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
        if (arg_ty > 0 && pipeline_type_kind_ord_at(arena, arg_ty) == 9) {
          arg_elem = pipeline_type_elem_ref_at(arena, arg_ty);
          if (arg_elem > 0 && typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) != 0) {
            dst_j = 0;
            while (dst_j < num_args) {
              if (dst_j != src_i) {
                param_ref = pipeline_module_func_param_type_ref_at(module, func_ix, dst_j);
                if (param_ref > 0 && pipeline_type_kind_ord_at(arena, param_ref) == 9) {
                  elem_ref = pipeline_type_elem_ref_at(arena, param_ref);
                  if (elem_ref > 0 && typeck_type_is_named_struct_c(m_u8, a_u8, elem_ref) != 0) {
                    other_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, dst_j);
                    // Same-frame &local sibling is not outer.
                    if (typeck_expr_is_addr_of_block_local(module, arena, ctx, other_arg) == 0) {
                      line = pipeline_expr_line_at(arena, call_expr_ref);
                      col = pipeline_expr_col_at(arena, call_expr_ref);
                      // Residual msg len 78 (no trailing NUL in lit count).
                      p = typeck_diag_append_lit(&msg[0], 0, 95,
                      "struct stack escape: cannot pass address of local struct with outer struct pointer", 78);
                      msg[p] = 0;
                      lsp_diag_report_typeck(line, col, &msg[0]);
                      return -1;
                    }
                  }
                }
              }
              dst_j = dst_j + 1;
            }
          }
        }
      }
      src_i = src_i + 1;
    }
    return 0;
  }
}

// end wave244 pure-owned leave

// ---------------------------------------------------------------------------
// wave245: typeck ptr_for_addr_of (+ stack_local *T) pure leave
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_ptr_for_addr_of_operand_c
// Type-pool authority for labelled *T: pipeline_type_find_or_alloc_ptr
//   (ast_pool_type.c — G.7 有则补全, mirrors find_or_alloc_slice).
// Cap residual region_assign deletes stack_local helpers + second body
// (dual-export ban) + dead store-scan cluster.
// PLATFORM: SHARED freestanding typeck WPO-S3 stack-local stamp.
// ---------------------------------------------------------------------------

/**
 * WPO-S3: when operand is a block-local VAR of named struct type, return a
 * stack_local *T type_ref; otherwise 0 (caller falls back to ordinary *T via
 * find_or_alloc_ptr_type_ref).
 * @param arena *ASTArena — type pool
 * @param op_ref i32 — & operand expr (must be block-local VAR)
 * @param elem_ty i32 — named struct type of the operand
 * @param module *Module — param exclusion / named-struct check
 * @param ctx *PipelineDepCtx — current_func / current_block for local lookup
 * @return i32 — stack_local *T type_ref (>0) or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_ptr_for_addr_of_operand_c(arena: *ASTArena, op_ref: i32, elem_ty: i32,
module: *Module, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — &local named-struct → *T with region label "stack_local".
  unsafe {
    let m_u8: *u8 = 0 as *u8;
    let a_u8: *u8 = 0 as *u8;
    if (arena == 0 as *ASTArena || module == 0 as *Module || ctx == 0 as *PipelineDepCtx
    || op_ref <= 0 || elem_ty <= 0) {
      return 0;
    }
    if (typeck_var_is_block_local(module, arena, ctx, op_ref) == 0) {
      return 0;
    }
    m_u8 = module as *u8;
    a_u8 = arena as *u8;
    if (typeck_type_is_named_struct_c(m_u8, a_u8, elem_ty) == 0) {
      return 0;
    }
    // Residual fidelity: label "stack_local" (len 11); type-pool face is authority.
    return pipeline_type_find_or_alloc_ptr(arena, elem_ty, "stack_local" as *u8, 11);
  }
}

// end wave245 pure-owned leave

// ---------------------------------------------------------------------------
// wave246: typeck return_slice_region_in_scope pure leave
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_check_return_slice_region_in_scope_c
// Cap residual region_assign deletes second body + expr_diag_line_col static
// (dual-export ban); pure uses typeck_expr_diag_line_col + built msg (no printf).
// PLATFORM: SHARED freestanding typeck M-3 region escape on return.
// ---------------------------------------------------------------------------

/**
 * M-3 AL-06: return of unbound T[] while inside an active region scope is escape.
 * Does not require operand stamp — only func return type is TYPE_SLICE with empty
 * region label, and ctx scope region label is non-empty.
 * @param arena *ASTArena — type + expr arena
 * @param site_expr_ref i32 — return expr for line/col
 * @param return_type_ref i32 — function return type_ref
 * @param ctx *PipelineDepCtx — active region scope label/len
 * @return i32 — 0 ok; -1 diagnostic emitted
 * wave246 G.7 pure leave: was Cap residual pipeline_typeck_check_return_slice_region_in_scope_c.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_return_slice_region_in_scope_c(arena: *ASTArena,
site_expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — region-scope unbound T[] return escape gate.
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let rlen: i32 = 0;
    let msg: u8[256] = [];
    let p: i32 = 0;
    let z: i32 = 0;
    if (arena == 0 as *ASTArena || ctx == 0 as *PipelineDepCtx || site_expr_ref <= 0
    || return_type_ref <= 0) {
      return 0;
    }
    if (pipeline_dep_ctx_scope_region_len_at(ctx) <= 0) {
      return 0;
    }
    /* TYPE_SLICE ord == 11 */
    if (pipeline_type_kind_ord_at(arena, return_type_ref) != 11) {
      return 0;
    }
    if (pipeline_type_region_label_len_at(arena, return_type_ref) > 0) {
      return 0;
    }
    line = 0;
    col = 0;
    typeck_expr_diag_line_col(arena, site_expr_ref, &line, &col);
    rlen = pipeline_dep_ctx_scope_region_len_at(ctx);
    if (rlen < 0) {
      rlen = 0;
    }
    if (rlen > 64) {
      rlen = 64;
    }
    z = 0;
    while (z < 256) {
      msg[z] = 0;
      z = z + 1;
    }
    /* "slice region escape: cannot return <" + label + "> slice as unbound T[]" */
    p = typeck_diag_append_lit(&msg[0], 0, 255, "slice region escape: cannot return <", 36);
    p = typeck_diag_append_lit(&msg[0], p, 255, &ctx.typeck_scope_region_label[0], rlen);
    p = typeck_diag_append_lit(&msg[0], p, 255, "> slice as unbound T[]", 22);
    msg[p] = 0;
    lsp_diag_report_typeck(line, col, &msg[0]);
    return 0 - 1;
  }
}

// end wave246 pure-owned leave

// ---------------------------------------------------------------------------
// wave247: typeck call-resolve domain pure leave (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_resolve_call_callee_return_type_c  (#[no_mangle] thin)
// Live body: resolve_call_callee_return_type + import/binding/select pure faces
// Cap residual method_call: delete second resolve_callee body; thin import faces
//   (import_segment_at / resolve_dep_index / whole_import_call_ret) → typeck_*.
// PLATFORM: SHARED freestanding typeck CALL target resolve.
// ---------------------------------------------------------------------------

/**
 * Cap residual face for CALL callee return-type resolve (wave247 pure leave).
 * Thin → resolve_call_callee_return_type (G.7 single authority; dual-export ban).
 * @param module *Module — entry module (local funcs + imports)
 * @param arena *ASTArena — caller expr/type arena
 * @param callee_expr_ref i32 — CALL callee expr ref (VAR / FIELD_ACCESS chain)
 * @param call_expr_ref i32 — full CALL expr; >0 applies call_resolve dep/func idx
 * @param ctx *PipelineDepCtx — dep modules for import binding / select scan
 * @return i32 — >0 return type_ref; 0 unresolved
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_resolve_call_callee_return_type_c(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, call_expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure resolve authority.
  return resolve_call_callee_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx);
}

// end wave247 pure-owned leave

// ---------------------------------------------------------------------------
// wave248: typeck overload pick/resolve pure leave (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_pick_overload_func_index_for_call_c  (#[no_mangle])
//   pipeline_typeck_resolve_call_func_index_for_emit_c   (#[no_mangle])
// Live bodies: typeck_module_func_overload_count + typeck_pick_overload_func_index_for_call
//   + typeck_resolve_call_func_index_for_emit
// Score authority: typeck_overload_arg_param_score via
//   find_func_return_type_in_module_by_name_overload (G.7 有则补全 — no second score).
// Cap residual method_call: delete static overload cluster (count / assignable /
//   match_score / expect_match / pick / resolve); Cap faces extern-only (dual-export ban).
// PLATFORM: SHARED freestanding typeck CALL overload resolve for emit/WPO.
// ---------------------------------------------------------------------------

/**
 * Count non-extern module funcs whose name equals (name, name_len).
 * Used as overload-worthiness gate before scoring (count > 1 → pick path).
 * @param m *Module — function table owner (null → 0)
 * @param name *u8 — callee name bytes
 * @param name_len i32 — byte count; <=0 → 0
 * @return i32 — non-extern same-name count
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_module_func_overload_count(m: *Module, name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — overload gate; skips extern decls (import binding path).
  unsafe {
    let i: i32 = 0;
    let c: i32 = 0;
    if (m == 0 as *Module || name == 0 as *u8 || name_len <= 0) {
      return 0;
    }
    while (i < m.num_funcs) {
      if (pipeline_module_func_is_extern_at(m, i) == 0) {
        if (pipeline_module_func_name_equal_at(m, i, name, name_len) != 0) {
          c = c + 1;
        }
      }
      i = i + 1;
    }
    return c;
  }
}

/**
 * Pick unique best overload func index for a CALL by arg score + expected-ret tiebreak.
 * Reuses find_func_return_type_in_module_by_name_overload (single score authority).
 * Returns -1 when name is not overloaded (count <= 1), callee is not VAR, or no match.
 * @param m *Module — entry module funcs[]
 * @param a *ASTArena — CALL expr arena
 * @param call_expr_ref i32 — CALL expr ref
 * @return i32 — funcs[] index or -1
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_pick_overload_func_index_for_call(m: *Module, a: *ASTArena,
call_expr_ref: i32): i32 {
  // PLATFORM: SHARED — WPO/typeck overload pick; score = typeck_overload_arg_param_score.
  unsafe {
    let callee_ref: i32 = 0;
    let ord_var: i32 = 3;
    let nlen: i32 = 0;
    let nm: u8[128] = [];
    let count: i32 = 0;
    let fx_out: i32 = 0 - 1;
    let ret: i32 = 0;
    let minus_one: i32 = 0 - 1;
    if (m == 0 as *Module || a == 0 as *ASTArena || call_expr_ref <= 0) {
      return minus_one;
    }
    callee_ref = pipeline_expr_call_callee_ref_at(a, call_expr_ref);
    if (callee_ref <= 0) {
      return minus_one;
    }
    if (pipeline_expr_kind_ord_at(a, callee_ref) != ord_var) {
      return minus_one;
    }
    nlen = pipeline_expr_var_name_len(a, callee_ref);
    if (nlen <= 0 || nlen > 127) {
      return minus_one;
    }
    pipeline_expr_var_name_into(a, callee_ref, &nm[0]);
    count = typeck_module_func_overload_count(m, &nm[0], nlen);
    if (count <= 1) {
      return minus_one;
    }
    fx_out = minus_one;
    ret = find_func_return_type_in_module_by_name_overload(m, a, &nm[0], nlen, call_expr_ref,
    minus_one, 0 as *PipelineDepCtx, &fx_out);
    if (fx_out >= 0) {
      return fx_out;
    }
    // Soft residual: overload scorer returned type but no func_ix — treat as miss.
    if (ret > 0 && fx_out >= 0) {
      return fx_out;
    }
    return minus_one;
  }
}

/**
 * Resolve CALL target func index (overload-aware) for asm emit + stack-escape scan.
 * When callee name is overloaded (count > 1), pick via pure score authority and stamp
 * apply_call_resolve(-1, picked). Else use cached resolved_func_index, then name-only scan.
 * @param m *Module — entry module
 * @param a *ASTArena — CALL arena
 * @param call_expr_ref i32 — CALL expr
 * @return i32 — funcs[] index or -1
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_resolve_call_func_index_for_emit(m: *Module, a: *ASTArena,
call_expr_ref: i32): i32 {
  // PLATFORM: SHARED — emit/WPO CALL→func_ix; single overload authority with pick above.
  unsafe {
    let callee_ref: i32 = 0;
    let ord_var: i32 = 3;
    let nlen: i32 = 0;
    let nm: u8[128] = [];
    let picked: i32 = 0;
    let fx: i32 = 0;
    let i: i32 = 0;
    let minus_one: i32 = 0 - 1;
    if (m == 0 as *Module || a == 0 as *ASTArena || call_expr_ref <= 0) {
      return minus_one;
    }
    callee_ref = pipeline_expr_call_callee_ref_at(a, call_expr_ref);
    if (callee_ref > 0 && pipeline_expr_kind_ord_at(a, callee_ref) == ord_var) {
      nlen = pipeline_expr_var_name_len(a, callee_ref);
      if (nlen > 0 && nlen <= 127) {
        pipeline_expr_var_name_into(a, callee_ref, &nm[0]);
        if (typeck_module_func_overload_count(m, &nm[0], nlen) > 1) {
          picked = typeck_pick_overload_func_index_for_call(m, a, call_expr_ref);
          if (picked >= 0) {
            ast.ast_expr_apply_call_resolve(a, call_expr_ref, minus_one, picked);
            return picked;
          }
        }
      }
    }
    fx = pipeline_expr_call_resolved_func_index_at(a, call_expr_ref);
    if (fx >= 0) {
      return fx;
    }
    if (callee_ref <= 0) {
      return minus_one;
    }
    if (pipeline_expr_kind_ord_at(a, callee_ref) != ord_var) {
      return minus_one;
    }
    nlen = pipeline_expr_var_name_len(a, callee_ref);
    if (nlen <= 0 || nlen > 127) {
      return minus_one;
    }
    pipeline_expr_var_name_into(a, callee_ref, &nm[0]);
    i = 0;
    while (i < m.num_funcs) {
      if (pipeline_module_func_name_equal_at(m, i, &nm[0], nlen) != 0) {
        return i;
      }
      i = i + 1;
    }
    return minus_one;
  }
}

/**
 * Cap residual face: pick overload func index for CALL (wave248 pure leave).
 * Thin → typeck_pick_overload_func_index_for_call (G.7 dual-export ban).
 * @param m *Module — entry module
 * @param a *ASTArena — CALL arena
 * @param call_expr_ref i32 — CALL expr
 * @return i32 — funcs[] index or -1
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_pick_overload_func_index_for_call_c(m: *Module, a: *ASTArena,
call_expr_ref: i32): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure pick authority.
  return typeck_pick_overload_func_index_for_call(m, a, call_expr_ref);
}

/**
 * Cap residual face: resolve CALL func index for emit (wave248 pure leave).
 * Thin → typeck_resolve_call_func_index_for_emit (G.7 dual-export ban).
 * ABI keeps *u8 slots for early typeck_gen / cast call sites.
 * @param m *u8 — Module* bitcast
 * @param a *u8 — ASTArena* bitcast
 * @param call_expr_ref i32 — CALL expr
 * @return i32 — funcs[] index or -1
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_resolve_call_func_index_for_emit_c(m: *u8, a: *u8,
call_expr_ref: i32): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure resolve authority.
  return typeck_resolve_call_func_index_for_emit(m as *Module, a as *ASTArena, call_expr_ref);
}

// end wave248 pure-owned leave

// ---------------------------------------------------------------------------
// wave249: typeck mono foundation pure leave (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_named_is_module_type_c       (#[no_mangle])
//   pipeline_typeck_call_arg_effective_type_c    (#[no_mangle])
//   glue_typeck_type_tree_has_free_param_c       (#[no_mangle])
// Live bodies: typeck_named_is_module_type + typeck_call_arg_effective_type
//   + typeck_type_tree_has_free_type_param (pre-existing; Cap face only)
// G.7: free-param probe = inverted named_is_module_type (no second name scan).
// Cap residual method_call: delete static named_is_module_type body +
//   type_tree_has_free_param body + call_arg_effective_type body (dual-export ban).
// PLATFORM: SHARED freestanding typeck generic mono foundation for UFCS/fixup.
// ---------------------------------------------------------------------------

/**
 * Effective mono type_ref for a call arg, falling back to lit-kind defaults.
 * Bare INT/BOOL/FLOAT/STRING lits often lack resolved_type_ref until stamp;
 * try_infer needs each arg to pin a mono type for free-T unification.
 * @param arena *ASTArena — arg expr arena (null → 0)
 * @param arg_ref i32 — call arg expr ref
 * @return i32 — type_ref >0 if pinable; 0 if null arena / invalid / bare null keyword
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_call_arg_effective_type(arena: *ASTArena, arg_ref: i32): i32 {
  // PLATFORM: SHARED — mono pin for generic inference (lit fallback).
  unsafe {
    let arg_ty: i32 = 0;
    let ek: i32 = 0;
    let u8t: i32 = 0;
    if (arena == 0 as *ASTArena || arg_ref <= 0) {
      return 0;
    }
    arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
    if (arg_ty > 0) {
      return arg_ty;
    }
    ek = pipeline_expr_kind_ord_at(arena, arg_ref);
    // EXPR_LIT=0: bare int lit (not keyword null) → i32 for mono pin.
    if (ek == 0) {
      if (typeck_expr_is_null_keyword(arena, arg_ref) != 0) {
        return 0;
      }
      return pipeline_type_ensure_by_kind_ord(arena, TypeKind.TYPE_I32 as i32);
    }
    // EXPR_FLOAT_LIT=1 → f64.
    if (ek == 1) {
      return pipeline_type_ensure_by_kind_ord(arena, TypeKind.TYPE_F64 as i32);
    }
    // EXPR_BOOL_LIT=2 → bool.
    if (ek == 2) {
      return pipeline_type_ensure_by_kind_ord(arena, TypeKind.TYPE_BOOL as i32);
    }
    // EXPR_STRING_LIT=59 → *u8 (C interop default).
    if (ek == 59) {
      u8t = pipeline_type_ensure_by_kind_ord(arena, TypeKind.TYPE_U8 as i32);
      if (u8t <= 0) {
        return 0;
      }
      return pipeline_type_find_or_alloc_compound(arena, TypeKind.TYPE_PTR as i32, u8t, 0);
    }
    return 0;
  }
}

/**
 * Cap residual face: named is module type (wave249 pure leave).
 * Thin → typeck_named_is_module_type (G.7 dual-export ban).
 * @param m *Module — layouts / aliases owner
 * @param a *ASTArena — unused ABI slot
 * @param nm *u8 — TYPE_NAMED spelling
 * @param nlen i32 — name length
 * @return i32 — 1 concrete, 0 free/unknown
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_named_is_module_type_c(m: *Module, a: *ASTArena, nm: *u8,
nlen: i32): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure named_is_module_type.
  return typeck_named_is_module_type(m, a, nm, nlen);
}

/**
 * Cap residual face: call-arg effective mono type (wave249 pure leave).
 * Thin → typeck_call_arg_effective_type (G.7 dual-export ban).
 * @param a *ASTArena — arg arena
 * @param arg_ref i32 — call arg expr
 * @return i32 — type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_call_arg_effective_type_c(a: *ASTArena, arg_ref: i32): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure call_arg_effective_type.
  return typeck_call_arg_effective_type(a, arg_ref);
}

/**
 * Cap residual face: type tree has free type-param (wave249 pure leave).
 * Thin → typeck_type_tree_has_free_type_param (G.7 dual-export ban;
 * residual glue body deleted; historical C name preserved for UFCS/fixup).
 * @param mod *Module — layouts / aliases owner
 * @param arena *ASTArena — type tree arena
 * @param ty i32 — type_ref root
 * @param depth i32 — recursion depth (cap 12)
 * @return i32 — 1 if free type-param found, else 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function glue_typeck_type_tree_has_free_param_c(mod: *Module, arena: *ASTArena, ty: i32,
depth: i32): i32 {
  // PLATFORM: SHARED — Cap residual historical glue name; body = pure free-param walk.
  return typeck_type_tree_has_free_type_param(mod, arena, ty, depth);
}

// end wave249 pure-owned leave

// ---------------------------------------------------------------------------
// wave250: typeck generic type-args / try_infer / bounds pure leave
// (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Symbols:
//   pipeline_typeck_check_call_generic_type_args_c  (#[no_mangle] Cap face)
// Live bodies: typeck_try_infer_generic_call_from_args +
//   typeck_check_inferred_generic_bounds + typeck_check_call_generic_type_args
// G.7: sole generic type-args / infer / post-infer bounds gate for EXPR_CALL.
// Cap residual method_call: delete residual try_infer + bounds + check_call
//   generic_type_args bodies (dual-export ban).
// PLATFORM: SHARED freestanding typeck generic call type-args gate.
// ---------------------------------------------------------------------------

/**
 * Infer bare generic CALL (no turbofish) from value args or ambient expected ret.
 * Value path: every formal has effective mono arg type (wave249 Cap face) and
 * same-named free type-params unify (same(1,true) red). Ret-only path: ret is
 * free type-param and expected_ret is fully concrete (no free type-param tree) —
 * module TYPE_NAMED **or** primitive/compound (i32, i64, bool, []T, …).
 * wave 4.2.4: prim ambient (`let a: i32 = mk_default()`) was hard-rejected
 * because expected was forced to module TYPE_NAMED only; fixup then left
 * `found T`. G.7: sole authority typeck_try_infer_generic_call_from_args.
 * Pure phantom: ret and all formals free of free type-params (`unit_t<T>():i32`
 * bare) — allowed; codegen wave450 bare-link mono. `mk_default<T>():T` without
 * ambient still requires expected or turbofish.
 * @param callee_mod *Module — resolved callee module (entry or dep)
 * @param arena *ASTArena — call expr arena
 * @param expr_ref i32 — EXPR_CALL
 * @param func_ix i32 — resolved func index in callee_mod
 * @param expected_ret i32 — ambient expected return type_ref (0 if none)
 * @return i32 — 0 infer ok, -1 fail-closed (requires turbofish)
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_try_infer_generic_call_from_args(callee_mod: *Module, arena: *ASTArena,
expr_ref: i32, func_ix: i32, expected_ret: i32): i32 {
  // PLATFORM: SHARED — bare generic CALL mono pin (value args / ret-only).
  unsafe {
    let np: i32 = 0;
    let nargs: i32 = 0;
    let i: i32 = 0;
    let j: i32 = 0;
    let k: i32 = 0;
    let ord_named: i32 = 8;
    let n_gp: i32 = 0;
    let ret_ty: i32 = 0;
    let ret_nm: u8[128] = [];
    let ret_nlen: i32 = 0;
    let value_ok: i32 = 1;
    let arg_ref: i32 = 0;
    let arg_ty: i32 = 0;
    let pi_ty: i32 = 0;
    let pi_nm: u8[128] = [];
    let pi_nlen: i32 = 0;
    let ai_ty: i32 = 0;
    let pj_ty: i32 = 0;
    let pj_nm: u8[128] = [];
    let pj_nlen: i32 = 0;
    let aj_ty: i32 = 0;
    let same_name: i32 = 0;
    if (callee_mod == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 || func_ix < 0) {
      return -1;
    }
    np = pipeline_module_func_num_params_at(callee_mod, func_ix);
    nargs = pipeline_expr_call_num_args_at(arena, expr_ref);
    // Value-arg path: formals present + each arg pinable + same-name unify.
    if (np > 0 && nargs >= np) {
      value_ok = 1;
      i = 0;
      while (i < np) {
        arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
        if (arg_ref <= 0) {
          value_ok = 0;
          break;
        }
        arg_ty = typeck_call_arg_effective_type(arena, arg_ref);
        if (arg_ty <= 0) {
          value_ok = 0;
          break;
        }
        i = i + 1;
      }
      if (value_ok != 0) {
        i = 0;
        while (i < np) {
          pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i);
          if (pi_ty <= 0 || pipeline_type_kind_ord_at(arena, pi_ty) != ord_named) {
            i = i + 1;
            continue;
          }
          // Only free type-params participate (not module Wrap).
          pi_nlen = pipeline_type_named_name_into(arena, pi_ty, &pi_nm[0]);
          if (pi_nlen <= 0) {
            i = i + 1;
            continue;
          }
          if (typeck_named_is_module_type(callee_mod, arena, &pi_nm[0], pi_nlen) != 0) {
            i = i + 1;
            continue;
          }
          ai_ty = typeck_call_arg_effective_type(arena,
            pipeline_expr_call_arg_ref(arena, expr_ref, i));
          if (ai_ty <= 0) {
            return -1;
          }
          j = i + 1;
          while (j < np) {
            pj_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, j);
            if (pj_ty <= 0 || pipeline_type_kind_ord_at(arena, pj_ty) != ord_named) {
              j = j + 1;
              continue;
            }
            pj_nlen = pipeline_type_named_name_into(arena, pj_ty, &pj_nm[0]);
            if (pj_nlen != pi_nlen) {
              j = j + 1;
              continue;
            }
            same_name = 1;
            k = 0;
            while (k < pi_nlen) {
              if (pi_nm[k] != pj_nm[k]) {
                same_name = 0;
                break;
              }
              k = k + 1;
            }
            if (same_name == 0) {
              j = j + 1;
              continue;
            }
            aj_ty = typeck_call_arg_effective_type(arena,
              pipeline_expr_call_arg_ref(arena, expr_ref, j));
            if (aj_ty <= 0 || pipeline_typeck_type_refs_equal_c(arena, ai_ty, aj_ty) == 0) {
              return -1;
            }
            j = j + 1;
          }
          i = i + 1;
        }
        return 0;
      }
    }
    // Ret-only path: free type-param ret + fully concrete ambient expected_ret.
    // PLATFORM: SHARED — prim (i32/…) and module NAMED both pin; free-T expected fail-closed.
    n_gp = pipeline_module_func_num_generic_params_at(callee_mod, func_ix);
    if (n_gp < 1) {
      return -1;
    }
    if (expected_ret > 0
    && typeck_type_tree_has_free_type_param(callee_mod, arena, expected_ret, 0) == 0) {
      ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix);
      if (ret_ty > 0 && pipeline_type_kind_ord_at(arena, ret_ty) == ord_named) {
        ret_nlen = pipeline_type_named_name_into(arena, ret_ty, &ret_nm[0]);
        if (ret_nlen > 0
        && typeck_named_is_module_type(callee_mod, arena, &ret_nm[0], ret_nlen) == 0) {
          return 0;
        }
      }
    }
    /*
     * Phantom path (wave 4.2.4 close): all type params unconstrained at this
     * call — return type has no free type-param tree, and no value formal
     * carries a free type-param. Example: `unit_t<T>(): i32` / `forty_two<T>()`
     * bare. Codegen wave450 already emits one bare-link mono for zero-param
     * phantom. Soft: `mk_default<T>():T` without ambient still fail-closed
     * (ret free T). Trait bounds on phantom-only T are enforced by
     * typeck_check_inferred_generic_bounds → xlang_generic_bound_check_type_args_c
     * with n_tp==0 (fail closed; require turbofish).
     * PLATFORM: SHARED freestanding typeck.
     */
    ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix);
    if (ret_ty <= 0) {
      return -1;
    }
    if (typeck_type_tree_has_free_type_param(callee_mod, arena, ret_ty, 0) != 0) {
      return -1;
    }
    i = 0;
    while (i < np) {
      pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i);
      if (pi_ty > 0
      && typeck_type_tree_has_free_type_param(callee_mod, arena, pi_ty, 0) != 0) {
        return -1;
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * After bare-call inference, check trait bounds via skip_tl authority.
 * Slots = first-appearance free TYPE_NAMED formals among value params; ret-only
 * free param appends a slot from expected_ret when not already present.
 * type_args rows are contiguous stride-128 (ABI match xlang_generic_bound).
 * When n_tp==0 (pure phantom / no free-T formals or ret pin), still call the
 * bound authority with nargs=0 so `T: Trait` decls fail closed (need turbofish).
 * @param callee_mod *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_CALL
 * @param func_ix i32
 * @param fn_name *u8 — callee name bytes
 * @param fn_name_len i32
 * @param line i32
 * @param col i32
 * @param expected_ret i32 — ambient ret (ret-only slot)
 * @return i32 — 0 ok / no bounds; non-zero bound fail
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_check_inferred_generic_bounds(callee_mod: *Module, arena: *ASTArena,
expr_ref: i32, func_ix: i32, fn_name: *u8, fn_name_len: i32, line: i32, col: i32,
expected_ret: i32): i32 {
  // PLATFORM: SHARED — post-infer trait bounds (G.7 skip_tl authority).
  unsafe {
    let max_targs: i32 = 4;
    let stride: i32 = 128;
    let type_args_flat: u8[512] = [];
    let type_arg_lens: i32[4] = [];
    let formal_names_flat: u8[512] = [];
    let formal_name_lens: i32[4] = [];
    let n_tp: i32 = 0;
    let np: i32 = 0;
    let i: i32 = 0;
    let k: i32 = 0;
    let ord_named: i32 = 8;
    let ret_ty: i32 = 0;
    let ret_nm: u8[128] = [];
    let ret_nlen: i32 = 0;
    let pi_ty: i32 = 0;
    let pi_nm: u8[128] = [];
    let pi_nlen: i32 = 0;
    let arg_ref: i32 = 0;
    let arg_ty: i32 = 0;
    let found: i32 = 0;
    let slot: i32 = 0;
    let conc_len: i32 = 0;
    let base: i32 = 0;
    let bi: i32 = 0;
    let found_r: i32 = 0;
    if (callee_mod == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 || func_ix < 0
    || fn_name == 0 as *u8 || fn_name_len <= 0) {
      return 0;
    }
    np = pipeline_module_func_num_params_at(callee_mod, func_ix);
    n_tp = 0;
    i = 0;
    while (i < np && n_tp < max_targs) {
      pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i);
      if (pi_ty <= 0 || pipeline_type_kind_ord_at(arena, pi_ty) != ord_named) {
        i = i + 1;
        continue;
      }
      pi_nlen = pipeline_type_named_name_into(arena, pi_ty, &pi_nm[0]);
      if (pi_nlen <= 0) {
        i = i + 1;
        continue;
      }
      if (typeck_named_is_module_type(callee_mod, arena, &pi_nm[0], pi_nlen) != 0) {
        i = i + 1;
        continue;
      }
      found = -1;
      k = 0;
      while (k < n_tp) {
        if (formal_name_lens[k] == pi_nlen) {
          base = k * stride;
          bi = 0;
          while (bi < pi_nlen) {
            if (formal_names_flat[base + bi] != pi_nm[bi]) {
              break;
            }
            bi = bi + 1;
          }
          if (bi == pi_nlen) {
            found = k;
            break;
          }
        }
        k = k + 1;
      }
      if (found >= 0) {
        i = i + 1;
        continue;
      }
      slot = n_tp;
      base = slot * stride;
      bi = 0;
      while (bi < pi_nlen) {
        formal_names_flat[base + bi] = pi_nm[bi];
        bi = bi + 1;
      }
      formal_name_lens[slot] = pi_nlen;
      arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i);
      arg_ty = 0;
      if (arg_ref > 0) {
        arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref);
      }
      conc_len = 0;
      if (arg_ty > 0 && pipeline_type_kind_ord_at(arena, arg_ty) == ord_named) {
        conc_len = pipeline_type_named_name_into(arena, arg_ty, &type_args_flat[base]);
        if (conc_len < 0) {
          conc_len = 0;
        }
        if (conc_len > 127) {
          conc_len = 63;
        }
      }
      type_arg_lens[slot] = conc_len;
      n_tp = n_tp + 1;
      i = i + 1;
    }
    // Ret-only free type-param not already in formal slots.
    ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix);
    if (ret_ty > 0 && pipeline_type_kind_ord_at(arena, ret_ty) == ord_named && n_tp < max_targs) {
      ret_nlen = pipeline_type_named_name_into(arena, ret_ty, &ret_nm[0]);
      if (ret_nlen > 0
      && typeck_named_is_module_type(callee_mod, arena, &ret_nm[0], ret_nlen) == 0) {
        found_r = -1;
        k = 0;
        while (k < n_tp) {
          if (formal_name_lens[k] == ret_nlen) {
            base = k * stride;
            bi = 0;
            while (bi < ret_nlen) {
              if (formal_names_flat[base + bi] != ret_nm[bi]) {
                break;
              }
              bi = bi + 1;
            }
            if (bi == ret_nlen) {
              found_r = k;
              break;
            }
          }
          k = k + 1;
        }
        if (found_r < 0 && expected_ret > 0
        && pipeline_type_kind_ord_at(arena, expected_ret) == ord_named) {
          slot = n_tp;
          base = slot * stride;
          bi = 0;
          while (bi < ret_nlen) {
            formal_names_flat[base + bi] = ret_nm[bi];
            bi = bi + 1;
          }
          formal_name_lens[slot] = ret_nlen;
          conc_len = pipeline_type_named_name_into(arena, expected_ret, &type_args_flat[base]);
          if (conc_len < 0) {
            conc_len = 0;
          }
          if (conc_len > 127) {
            conc_len = 63;
          }
          type_arg_lens[slot] = conc_len;
          n_tp = n_tp + 1;
        }
      }
    }
    /* n_tp==0 still invokes bound authority (nargs=0): pure-phantom bare with
     * T: Trait must fail closed. No-bound unit_t<T>() stays 0. */
    return xlang_generic_bound_check_type_args_c(fn_name, fn_name_len, &type_args_flat[0],
      &type_arg_lens[0], n_tp, line, col);
  }
}

/**
 * Validate generic CALL type-args count; infer bare calls; check bounds.
 * G.7 sole gate for turbofish arity + bare infer + post-infer trait bounds.
 * @param module *Module — entry module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_CALL (resolved func index already stamped)
 * @param ctx *PipelineDepCtx — dep modules when resolved_dep_index ≥ 0
 * @param expected_ret i32 — ambient expected return (ret-only infer)
 * @return i32 — 0 ok; -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_check_call_generic_type_args(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32 {
  // PLATFORM: SHARED — generic type-args / infer / bounds gate.
  unsafe {
    let callee_mod: *Module = 0 as *Module;
    let func_ix: i32 = 0;
    let dep_ix: i32 = 0;
    let num_generic_params: i32 = 0;
    let num_type_args: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let name: u8[128] = [];
    let name_len: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0) {
      return 0;
    }
    func_ix = pipeline_expr_call_resolved_func_index_at(arena, expr_ref);
    if (func_ix < 0) {
      return 0;
    }
    dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref);
    callee_mod = module;
    if (dep_ix >= 0) {
      callee_mod = pipeline_dep_ctx_module_at(ctx, dep_ix);
      if (callee_mod == 0 as *Module) {
        return 0;
      }
    }
    num_generic_params = pipeline_module_func_num_generic_params_at(callee_mod, func_ix);
    num_type_args = pipeline_expr_call_num_type_args_at(arena, expr_ref);
    if (num_generic_params == 0 && num_type_args == 0) {
      return 0;
    }
    line = pipeline_expr_line_at(arena, expr_ref);
    col = pipeline_expr_col_at(arena, expr_ref);
    name_len = pipeline_module_func_name_len_at(callee_mod, func_ix);
    if (name_len > 127) {
      name_len = 63;
    }
    if (name_len > 0) {
      pipeline_module_func_name_copy64(callee_mod, func_ix, &name[0]);
    }
    if (num_type_args > 0 && num_generic_params == 0) {
      driver_diagnostic_typeck_call_not_generic(line, col, &name[0], name_len);
      return -1;
    }
    if (num_generic_params > 0 && num_type_args == 0) {
      // Bare call: infer from value args or expected ret; then bounds.
      if (typeck_try_infer_generic_call_from_args(callee_mod, arena, expr_ref, func_ix,
      expected_ret) == 0) {
        if (typeck_check_inferred_generic_bounds(callee_mod, arena, expr_ref, func_ix, &name[0],
        name_len, line, col, expected_ret) != 0) {
          return -1;
        }
        return 0;
      }
      driver_diagnostic_typeck_call_requires_type_args(line, col, &name[0], name_len);
      return -1;
    }
    if (num_generic_params != num_type_args) {
      driver_diagnostic_typeck_call_wrong_num_type_args(line, col, &name[0], name_len,
        num_generic_params, num_type_args);
      return -1;
    }
    return 0;
  }
}

/**
 * Cap residual face: generic CALL type-args gate (wave250 pure leave).
 * Thin → typeck_check_call_generic_type_args (G.7 dual-export ban).
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32 — EXPR_CALL
 * @param ctx *PipelineDepCtx
 * @param expected_ret i32
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_call_generic_type_args_c(module: *Module, arena: *ASTArena,
expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32 {
  // PLATFORM: SHARED — Cap residual face name; body = pure check_call_generic.
  return typeck_check_call_generic_type_args(module, arena, expr_ref, ctx, expected_ret);
}

// end wave250 pure-owned leave

// ---------------------------------------------------------------------------
// wave251: typeck mono-map / pattern-unify / subst pure leave
// (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Cap faces (#[no_mangle], flat mono-map ABI stride-128):
//   glue_typeck_pattern_unify_bind_c
//   glue_typeck_subst_type_ref_c
//   glue_typeck_build_value_formal_mono_map_c
// Live helpers: mono_map lookup/bind + named_num_type_args + alloc_named_with
//   type_args + pattern_unify + build_value_formal_mono_map + subst_type_ref
// Flat ABI: names_flat *u8 (n_map rows × 128), lens *i32, conc *i32, n_map *i32
//   Residual C multi-dim [8][128] is byte-identical; pass (uint8_t *)names.
// G.7: sole mono map / pattern-unify / subst path for generic UFCS + CALL fixup.
// Cap residual method_call: delete residual mono engine bodies (dual-export ban).
// PLATFORM: SHARED freestanding typeck generic mono map engine.
// ---------------------------------------------------------------------------

/**
 * Lookup free type-param name in flat mono map.
 * @param names_flat *u8 — row-major name bytes (stride 128)
 * @param lens *i32 — per-slot name lengths
 * @param conc *i32 — concrete type_ref per slot (caller arena)
 * @param n_map i32 — live slot count
 * @param nm *u8 — free-param name bytes
 * @param nlen i32 — name length
 * @return i32 — concrete type_ref or 0 miss
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_mono_map_lookup(names_flat: *u8, lens: *i32, conc: *i32, n_map: i32,
nm: *u8, nlen: i32): i32 {
  // PLATFORM: SHARED — free-param → concrete map lookup (stride-128 rows).
  unsafe {
    let i: i32 = 0;
    let k: i32 = 0;
    let base: i32 = 0;
    let stride: i32 = 128;
    if (names_flat == 0 as *u8 || lens == 0 as *i32 || conc == 0 as *i32 || nm == 0 as *u8
    || nlen <= 0 || n_map <= 0) {
      return 0;
    }
    i = 0;
    while (i < n_map) {
      if (lens[i] == nlen) {
        base = i * stride;
        k = 0;
        while (k < nlen) {
          if (names_flat[base + k] != nm[k]) {
            break;
          }
          k = k + 1;
        }
        if (k == nlen) {
          return conc[i];
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Bind free type-param name → concrete type_ref. Fail-closed on conflict rebind.
 * @param names_flat *u8 — flat map rows
 * @param lens *i32
 * @param conc *i32
 * @param n_map *i32 — in/out live count
 * @param max_map i32 — capacity (8)
 * @param nm *u8
 * @param nlen i32
 * @param concrete_ty i32 — caller-arena type_ref
 * @param caller_arena *ASTArena — for equal check on rebind
 * @return i32 — 0 ok, -1 conflict/full/invalid
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_mono_map_bind(names_flat: *u8, lens: *i32, conc: *i32, n_map: *i32,
max_map: i32, nm: *u8, nlen: i32, concrete_ty: i32, caller_arena: *ASTArena): i32 {
  // PLATFORM: SHARED — identity / pattern-unify free-param bind.
  unsafe {
    let prev: i32 = 0;
    let n: i32 = 0;
    let base: i32 = 0;
    let k: i32 = 0;
    let stride: i32 = 128;
    if (names_flat == 0 as *u8 || lens == 0 as *i32 || conc == 0 as *i32 || n_map == 0 as *i32
    || nm == 0 as *u8 || nlen <= 0 || nlen > 127 || concrete_ty <= 0 || max_map <= 0) {
      return -1;
    }
    n = typeck_i32_ptr_read(n_map);
    prev = typeck_mono_map_lookup(names_flat, lens, conc, n, nm, nlen);
    if (prev > 0) {
      if (caller_arena != 0 as *ASTArena
      && pipeline_typeck_type_refs_equal_c(caller_arena, prev, concrete_ty) == 0) {
        return -1;
      }
      return 0;
    }
    if (n >= max_map) {
      return -1;
    }
    base = n * stride;
    // Clear first 64 name bytes (residual memset 64).
    k = 0;
    while (k < 64) {
      names_flat[base + k] = 0;
      k = k + 1;
    }
    k = 0;
    while (k < nlen) {
      names_flat[base + k] = nm[k];
      k = k + 1;
    }
    lens[n] = nlen;
    conc[n] = concrete_ty;
    typeck_i32_ptr_store(n_map, n + 1);
    return 0;
  }
}

/**
 * Count type-position args on TYPE_NAMED (array_size preferred; sidecar walk fallback).
 * @param arena *ASTArena
 * @param ty i32 — TYPE_NAMED type_ref
 * @return i32 — n type-args in 0..8
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_named_num_type_args(arena: *ASTArena, ty: i32): i32 {
  // PLATFORM: SHARED — NAMED type-arg arity for mono unify/subst.
  unsafe {
    let n: i32 = 0;
    let asz: i32 = 0;
    let i: i32 = 0;
    let max_targs: i32 = 8;
    if (arena == 0 as *ASTArena || ty <= 0) {
      return 0;
    }
    asz = pipeline_type_array_size_at(arena, ty);
    if (asz > 0 && asz <= max_targs) {
      return asz;
    }
    n = 0;
    i = 0;
    while (i < max_targs) {
      if (pipeline_type_type_arg_ref_at(arena, ty, i) <= 0) {
        break;
      }
      n = i + 1;
      i = i + 1;
    }
    return n;
  }
}

/**
 * Allocate fresh TYPE_NAMED with type-pos args (never find_or_alloc_named).
 * @param arena *ASTArena
 * @param name *u8
 * @param name_len i32
 * @param arg0..arg7 i32 — type_ref slots; only first n_args used
 * @param n_args i32
 * @return i32 — new type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 *
 * Note: X has no *i32 arg_refs array param multi-value; Cap residual and pure
 * subst pass args via local stack then call this with fixed slots, or pure
 * subst inlines alloc. Here we take up to 8 explicit args for Cap thin path.
 * Live pure subst uses typeck_alloc_named_with_type_args_flat (*i32 arg_refs).
 */
export function typeck_alloc_named_with_type_args_flat(arena: *ASTArena, name: *u8, name_len: i32,
arg_refs: *i32, n_args: i32): i32 {
  // PLATFORM: SHARED — fresh mono NAMED node (sidecar type-args + meta stamp).
  unsafe {
    let tr: i32 = 0;
    let i: i32 = 0;
    let ar: i32 = 0;
    let max_targs: i32 = 8;
    if (arena == 0 as *ASTArena || name == 0 as *u8 || name_len <= 0 || name_len > 127) {
      return 0;
    }
    if (n_args < 0 || n_args > max_targs || arg_refs == 0 as *i32) {
      return 0;
    }
    tr = pipeline_arena_type_alloc(arena);
    if (tr <= 0) {
      return 0;
    }
    if (pipeline_type_init_named_at(arena, tr, name, name_len) == 0) {
      return 0;
    }
    i = 0;
    while (i < n_args) {
      ar = arg_refs[i];
      if (ar <= 0) {
        return 0;
      }
      if (pipeline_type_append_type_arg(arena, tr, ar) != 0) {
        return 0;
      }
      i = i + 1;
    }
    if (n_args > 0) {
      if (pipeline_type_set_elem_array_size_at(arena, tr, arg_refs[0], n_args) == 0) {
        return 0;
      }
    }
    return tr;
  }
}

/**
 * Recursively pattern-unify formal type with concrete arg; bind free params.
 * Free TYPE_NAMED formals bind; module TYPE_NAMED with type-args unify pairwise;
 * PTR/SLICE/ARRAY/VECTOR strip and unify elems.
 * @return i32 — 0 ok, -1 hard conflict
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_pattern_unify_bind(mod: *Module, formal_arena: *ASTArena, formal_ty: i32,
arg_arena: *ASTArena, arg_ty: i32, names_flat: *u8, lens: *i32, conc: *i32, n_map: *i32,
max_map: i32, depth: i32): i32 {
  // PLATFORM: SHARED — formal↔arg pattern unify (generic UFCS / mono map).
  unsafe {
    let fk: i32 = 0;
    let ak: i32 = 0;
    let fnlen: i32 = 0;
    let fnm: u8[128] = [];
    let anlen: i32 = 0;
    let anm: u8[128] = [];
    let n_fta: i32 = 0;
    let n_ata: i32 = 0;
    let i: i32 = 0;
    let fta: i32 = 0;
    let ata: i32 = 0;
    let felem: i32 = 0;
    let aelem: i32 = 0;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_vector: i32 = 13;
    let max_depth: i32 = 12;
    if (mod == 0 as *Module || formal_arena == 0 as *ASTArena || arg_arena == 0 as *ASTArena
    || names_flat == 0 as *u8 || lens == 0 as *i32 || conc == 0 as *i32 || n_map == 0 as *i32
    || formal_ty <= 0 || arg_ty <= 0) {
      return -1;
    }
    if (depth > max_depth) {
      return -1;
    }
    fk = pipeline_type_kind_ord_at(formal_arena, formal_ty);
    ak = pipeline_type_kind_ord_at(arg_arena, arg_ty);
    if (fk < 0 || ak < 0) {
      return -1;
    }
    // Free type-param formal (TYPE_NAMED not a module struct/alias).
    if (fk == ord_named) {
      fnlen = pipeline_type_named_name_into(formal_arena, formal_ty, &fnm[0]);
      if (fnlen <= 0) {
        return -1;
      }
      if (typeck_named_is_module_type(mod, formal_arena, &fnm[0], fnlen) == 0) {
        return typeck_mono_map_bind(names_flat, lens, conc, n_map, max_map, &fnm[0], fnlen, arg_ty,
          arg_arena);
      }
      // Module named formal: require arg same name + unify type-pos args.
      if (ak != ord_named) {
        return -1;
      }
      anlen = pipeline_type_named_name_into(arg_arena, arg_ty, &anm[0]);
      if (anlen <= 0 || !name_equal(&fnm[0], fnlen, &anm[0], anlen)) {
        return -1;
      }
      n_fta = typeck_named_num_type_args(formal_arena, formal_ty);
      if (n_fta <= 0) {
        return 0;
      }
      n_ata = typeck_named_num_type_args(arg_arena, arg_ty);
      if (n_ata <= 0) {
        aelem = pipeline_type_elem_ref_at(arg_arena, arg_ty);
        if (aelem > 0) {
          n_ata = 1;
        }
      }
      if (n_ata < n_fta) {
        return -1;
      }
      i = 0;
      while (i < n_fta) {
        fta = pipeline_type_type_arg_ref_at(formal_arena, formal_ty, i);
        if (fta <= 0 && i == 0) {
          fta = pipeline_type_elem_ref_at(formal_arena, formal_ty);
        }
        ata = pipeline_type_type_arg_ref_at(arg_arena, arg_ty, i);
        if (ata <= 0 && i == 0) {
          ata = pipeline_type_elem_ref_at(arg_arena, arg_ty);
        }
        if (fta <= 0 || ata <= 0) {
          return -1;
        }
        if (typeck_pattern_unify_bind(mod, formal_arena, fta, arg_arena, ata, names_flat, lens, conc,
        n_map, max_map, depth + 1) != 0) {
          return -1;
        }
        i = i + 1;
      }
      return 0;
    }
    // Compound: ptr/slice/array/vector — strip and unify elems when both match.
    if (fk == ord_ptr || fk == ord_slice || fk == ord_array || fk == ord_vector) {
      if (ak != fk) {
        return -1;
      }
      felem = pipeline_type_elem_ref_at(formal_arena, formal_ty);
      aelem = pipeline_type_elem_ref_at(arg_arena, arg_ty);
      if (felem <= 0 || aelem <= 0) {
        return -1;
      }
      if (fk == ord_array || fk == ord_vector) {
        if (pipeline_type_array_size_at(formal_arena, formal_ty)
        != pipeline_type_array_size_at(arg_arena, arg_ty)) {
          return -1;
        }
      }
      return typeck_pattern_unify_bind(mod, formal_arena, felem, arg_arena, aelem, names_flat, lens,
        conc, n_map, max_map, depth + 1);
    }
    // Builtin formal: kinds must agree.
    if (fk == ak) {
      return 0;
    }
    return -1;
  }
}

/**
 * Build free-type-param mono map from value formals + call args.
 * @return i32 — n_map (>=0); 0 if nothing bound or conflict fail-closed
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_build_value_formal_mono_map(search_mod: *Module, search_arena: *ASTArena,
caller_arena: *ASTArena, call_expr_ref: i32, func_idx: i32, names_flat: *u8, lens: *i32,
conc: *i32, max_map: i32): i32 {
  // PLATFORM: SHARED — formal/arg mono map for CALL fixup / subst ret.
  unsafe {
    let n_map_local: i32 = 0;
    let n_map_ptr: *i32 = 0 as *i32;
    let num_params: i32 = 0;
    let pi: i32 = 0;
    let param_ty: i32 = 0;
    let arg_i: i32 = 0;
    let arg_ty: i32 = 0;
    let ord_named: i32 = 8;
    let param_nm: u8[128] = [];
    let param_nlen: i32 = 0;
    let gi: i32 = 0;
    let dup: i32 = 0;
    let base: i32 = 0;
    let k: i32 = 0;
    let stride: i32 = 128;
    if (search_mod == 0 as *Module || search_arena == 0 as *ASTArena || caller_arena == 0 as *ASTArena
    || call_expr_ref <= 0 || func_idx < 0 || names_flat == 0 as *u8 || lens == 0 as *i32
    || conc == 0 as *i32 || max_map <= 0) {
      return 0;
    }
    n_map_local = 0;
    n_map_ptr = &n_map_local;
    num_params = pipeline_module_func_num_params_at(search_mod, func_idx);
    pi = 0;
    while (pi < num_params && n_map_local < max_map) {
      param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi);
      if (param_ty <= 0) {
        pi = pi + 1;
        continue;
      }
      arg_i = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, pi);
      if (arg_i <= 0) {
        pi = pi + 1;
        continue;
      }
      arg_ty = pipeline_expr_resolved_type_ref(caller_arena, arg_i);
      if (arg_ty <= 0) {
        pi = pi + 1;
        continue;
      }
      // Fast path: bare free TYPE_NAMED formal.
      if (pipeline_type_kind_ord_at(search_arena, param_ty) == ord_named) {
        param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &param_nm[0]);
        if (param_nlen > 0
        && typeck_named_is_module_type(search_mod, search_arena, &param_nm[0], param_nlen) == 0) {
          dup = 0;
          gi = 0;
          while (gi < n_map_local) {
            if (lens[gi] == param_nlen) {
              base = gi * stride;
              k = 0;
              while (k < param_nlen) {
                if (names_flat[base + k] != param_nm[k]) {
                  break;
                }
                k = k + 1;
              }
              if (k == param_nlen) {
                dup = 1;
                break;
              }
            }
            gi = gi + 1;
          }
          if (dup == 0) {
            if (typeck_mono_map_bind(names_flat, lens, conc, n_map_ptr, max_map, &param_nm[0],
            param_nlen, arg_ty, caller_arena) != 0) {
              return 0;
            }
            n_map_local = typeck_i32_ptr_read(n_map_ptr);
          }
          pi = pi + 1;
          continue;
        }
      }
      // Pattern-unify module formals with free type-arg trees.
      if (typeck_type_tree_has_free_type_param(search_mod, search_arena, param_ty, 0) != 0) {
        if (typeck_pattern_unify_bind(search_mod, search_arena, param_ty, caller_arena, arg_ty,
        names_flat, lens, conc, n_map_ptr, max_map, 0) != 0) {
          // Soft: skip this formal; other formals may still bind.
          pi = pi + 1;
          continue;
        }
        n_map_local = typeck_i32_ptr_read(n_map_ptr);
      }
      pi = pi + 1;
    }
    return n_map_local;
  }
}

/**
 * Recursively substitute free type-params in ty into dst_arena using mono map.
 * @return i32 — concrete type_ref in dst_arena, or 0 on failure
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_subst_type_ref(mod: *Module, src_arena: *ASTArena, dst_arena: *ASTArena,
ty: i32, names_flat: *u8, lens: *i32, conc: *i32, n_map: i32, depth: i32): i32 {
  // PLATFORM: SHARED — mono subst free params / module NAMED trees.
  unsafe {
    let kind: i32 = 0;
    let nlen: i32 = 0;
    let nm: u8[128] = [];
    let n_ta: i32 = 0;
    let i: i32 = 0;
    let ta: i32 = 0;
    let sa: i32 = 0;
    let args: i32[8] = [];
    let elem: i32 = 0;
    let mapped_elem: i32 = 0;
    let asz: i32 = 0;
    let looked: i32 = 0;
    let max_depth: i32 = 12;
    let ord_named: i32 = 8;
    let ord_ptr: i32 = 9;
    let ord_array: i32 = 10;
    let ord_slice: i32 = 11;
    let ord_vector: i32 = 13;
    // Primitive ords (LINEAR-inclusive TypeKind).
    let ord_i32: i32 = 0;
    let ord_bool: i32 = 1;
    let ord_u8: i32 = 2;
    let ord_u32: i32 = 3;
    let ord_u64: i32 = 4;
    let ord_i64: i32 = 5;
    let ord_usize: i32 = 6;
    let ord_isize: i32 = 7;
    let ord_f32: i32 = 14;
    let ord_f64: i32 = 15;
    let ord_void: i32 = 16;
    if (mod == 0 as *Module || src_arena == 0 as *ASTArena || dst_arena == 0 as *ASTArena
    || ty <= 0 || depth > max_depth) {
      return 0;
    }
    kind = pipeline_type_kind_ord_at(src_arena, ty);
    if (kind < 0) {
      return 0;
    }
    if (kind == ord_i32 || kind == ord_i64 || kind == ord_bool || kind == ord_f64 || kind == ord_u8
    || kind == ord_u32 || kind == ord_u64 || kind == ord_isize || kind == ord_f32 || kind == ord_usize
    || kind == ord_void) {
      return pipeline_type_ensure_by_kind_ord(dst_arena, kind);
    }
    if (kind == ord_named) {
      nlen = pipeline_type_named_name_into(src_arena, ty, &nm[0]);
      if (nlen <= 0) {
        return 0;
      }
      if (typeck_named_is_module_type(mod, src_arena, &nm[0], nlen) == 0) {
        looked = typeck_mono_map_lookup(names_flat, lens, conc, n_map, &nm[0], nlen);
        if (looked > 0) {
          return looked;
        }
        return 0;
      }
      n_ta = typeck_named_num_type_args(src_arena, ty);
      if (n_ta <= 0) {
        return pipeline_type_find_or_alloc_named(dst_arena, &nm[0], nlen);
      }
      i = 0;
      while (i < n_ta) {
        ta = pipeline_type_type_arg_ref_at(src_arena, ty, i);
        if (ta <= 0) {
          return 0;
        }
        sa = typeck_subst_type_ref(mod, src_arena, dst_arena, ta, names_flat, lens, conc, n_map,
          depth + 1);
        if (sa <= 0) {
          return 0;
        }
        args[i] = sa;
        i = i + 1;
      }
      return typeck_alloc_named_with_type_args_flat(dst_arena, &nm[0], nlen, &args[0], n_ta);
    }
    elem = pipeline_type_elem_ref_at(src_arena, ty);
    mapped_elem = 0;
    if (elem > 0) {
      mapped_elem = typeck_subst_type_ref(mod, src_arena, dst_arena, elem, names_flat, lens, conc,
        n_map, depth + 1);
      if (mapped_elem <= 0) {
        return 0;
      }
    }
    asz = pipeline_type_array_size_at(src_arena, ty);
    if (kind == ord_ptr) {
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_ptr, mapped_elem, 0);
    }
    if (kind == ord_vector) {
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_vector, mapped_elem, asz);
    }
    if (kind == ord_array) {
      if (mapped_elem <= 0 || asz <= 0) {
        return 0;
      }
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_array, mapped_elem, asz);
    }
    if (kind == ord_slice) {
      return pipeline_type_find_or_alloc_slice(dst_arena, mapped_elem, 0 as *u8, 0);
    }
    return 0;
  }
}

/**
 * Cap residual face: pattern-unify formal with arg; bind free params (flat map).
 * Thin → typeck_pattern_unify_bind (G.7 dual-export ban).
 * @return i32 — 0 ok, -1 conflict
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function glue_typeck_pattern_unify_bind_c(mod: *Module, formal_arena: *ASTArena,
formal_ty: i32, arg_arena: *ASTArena, arg_ty: i32, names_flat: *u8, lens: *i32, conc: *i32,
n_map: *i32, max_map: i32, depth: i32): i32 {
  // PLATFORM: SHARED — Cap residual face; body = pure pattern_unify.
  return typeck_pattern_unify_bind(mod, formal_arena, formal_ty, arg_arena, arg_ty, names_flat, lens,
    conc, n_map, max_map, depth);
}

/**
 * Cap residual face: substitute free type-params (flat map).
 * Thin → typeck_subst_type_ref (G.7 dual-export ban).
 * @return i32 — mono type_ref in dst_arena or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function glue_typeck_subst_type_ref_c(mod: *Module, src_arena: *ASTArena,
dst_arena: *ASTArena, ty: i32, names_flat: *u8, lens: *i32, conc: *i32, n_map: i32,
depth: i32): i32 {
  // PLATFORM: SHARED — Cap residual face; body = pure subst.
  return typeck_subst_type_ref(mod, src_arena, dst_arena, ty, names_flat, lens, conc, n_map, depth);
}

/**
 * Cap residual face: build formal free-param mono map from call value args.
 * Thin → typeck_build_value_formal_mono_map (G.7 dual-export ban).
 * @return i32 — n_map
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function glue_typeck_build_value_formal_mono_map_c(search_mod: *Module,
search_arena: *ASTArena, caller_arena: *ASTArena, call_expr_ref: i32, func_idx: i32,
names_flat: *u8, lens: *i32, conc: *i32, max_map: i32): i32 {
  // PLATFORM: SHARED — Cap residual face; body = pure build_value_formal_mono_map.
  return typeck_build_value_formal_mono_map(search_mod, search_arena, caller_arena, call_expr_ref,
    func_idx, names_flat, lens, conc, max_map);
}

// end wave251 pure-owned leave

// ---------------------------------------------------------------------------
// wave252: typeck generic method UFCS + CALL mono fixup pure leave
// (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync).
// Cap faces (#[no_mangle]):
//   pipeline_typeck_method_call_generic_ufcs_c
//   glue_generic_call_fixup_resolved_type_c
// Live helpers: subst_ret_from_formal_map + method_call_generic_ufcs +
//   generic_call_fixup_resolved_type
// Flat mono-map ABI: names_flat *u8 stride-128 (same wave251).
// G.7: sole generic UFCS + CALL fixup path (residual dual-export ban).
// Cap residual method_call: delete residual UFCS / fixup / subst helper bodies.
// PLATFORM: SHARED freestanding typeck generic UFCS + CALL fixup.
// ---------------------------------------------------------------------------

/**
 * Build formal free-param mono map; subst ret tree when ret is free type-param
 * or module NAMED with free type-arg tree.
 * @return i32 — mono type_ref in caller_arena, or 0 if not applicable
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_generic_call_subst_ret_from_formal_map(search_mod: *Module,
search_arena: *ASTArena, caller_arena: *ASTArena, call_expr_ref: i32, func_idx: i32,
ret_ty: i32): i32 {
  // PLATFORM: SHARED — formal-map subst for free / module ret trees.
  unsafe {
    let ord_named: i32 = 8;
    let n_map: i32 = 0;
    let names_flat: u8[1024] = [];
    let lens: i32[8] = [];
    let conc: i32[8] = [];
    let ret_nm: u8[128] = [];
    let ret_nlen: i32 = 0;
    let mono_ret: i32 = 0;
    let max_map: i32 = 8;
    if (search_mod == 0 as *Module || search_arena == 0 as *ASTArena || caller_arena == 0 as *ASTArena
    || call_expr_ref <= 0 || func_idx < 0 || ret_ty <= 0) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(search_arena, ret_ty) != ord_named) {
      return 0;
    }
    ret_nlen = pipeline_type_named_name_into(search_arena, ret_ty, &ret_nm[0]);
    if (ret_nlen <= 0) {
      return 0;
    }
    n_map = typeck_build_value_formal_mono_map(search_mod, search_arena, caller_arena, call_expr_ref,
      func_idx, &names_flat[0], &lens[0], &conc[0], max_map);
    if (n_map <= 0) {
      return 0;
    }
    // Free type-param ret: subst free NAMED leaf = map lookup.
    if (typeck_named_is_module_type(search_mod, search_arena, &ret_nm[0], ret_nlen) == 0) {
      mono_ret = typeck_subst_type_ref(search_mod, search_arena, caller_arena, ret_ty, &names_flat[0],
        &lens[0], &conc[0], n_map, 0);
      if (mono_ret > 0) {
        return mono_ret;
      }
      return 0;
    }
    // Module ret with free tree — fail-closed if mono still free.
    if (typeck_type_tree_has_free_type_param(search_mod, search_arena, ret_ty, 0) == 0) {
      return 0;
    }
    mono_ret = typeck_subst_type_ref(search_mod, search_arena, caller_arena, ret_ty, &names_flat[0],
      &lens[0], &conc[0], n_map, 0);
    if (mono_ret <= 0) {
      return 0;
    }
    if (typeck_type_tree_has_free_type_param(search_mod, caller_arena, mono_ret, 0) != 0) {
      return 0;
    }
    return mono_ret;
  }
}

/**
 * Generic method_call UFCS: pattern-unify formal self with concrete receiver,
 * verify non-self args (after subst), stamp mono return + call_resolve.
 * Only functions with n_gp>0 enter (non-generic take0(self: i32x4) is not T).
 * @return i32 — 1 success (stamped), 0 no match
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_method_call_generic_ufcs(module: *Module, arena: *ASTArena, expr_ref: i32,
base_ty: i32, method_nm: *u8, method_nlen: i32, num_args: i32): i32 {
  // PLATFORM: SHARED — sole generic method UFCS authority (wave494 / wave252).
  unsafe {
    let nf: i32 = 0;
    let fi: i32 = 0;
    let nparams: i32 = 0;
    let p0: i32 = 0;
    let g_ret: i32 = 0;
    let g_ai: i32 = 0;
    let g_matched: i32 = 0;
    let names_flat: u8[1024] = [];
    let lens: i32[8] = [];
    let conc: i32[8] = [];
    let g_nmap: i32 = 0;
    let g_param: i32 = 0;
    let g_arg_ref: i32 = 0;
    let g_arg_ty: i32 = 0;
    let g_sub: i32 = 0;
    let g_mono: i32 = 0;
    let max_map: i32 = 8;
    if (module == 0 as *Module || arena == 0 as *ASTArena || expr_ref <= 0 || base_ty <= 0
    || method_nm == 0 as *u8 || method_nlen <= 0) {
      return 0;
    }
    nf = pipeline_module_num_funcs(module);
    fi = 0;
    while (fi < nf) {
      if (pipeline_module_func_name_equal_at(module, fi, method_nm, method_nlen) == 0) {
        fi = fi + 1;
        continue;
      }
      nparams = pipeline_module_func_num_params_at(module, fi);
      if (nparams != num_args + 1) {
        fi = fi + 1;
        continue;
      }
      /*
       * Non-generic fn (n_gp==0): i32x4 NAMED is not a free T. Leave to
       * same-module UFCS + coerce refuse / T001.
       * PLATFORM: SHARED.
       */
      if (pipeline_module_func_num_generic_params_at(module, fi) <= 0) {
        fi = fi + 1;
        continue;
      }
      p0 = pipeline_module_func_param_type_ref_at(module, fi, 0);
      if (p0 <= 0) {
        fi = fi + 1;
        continue;
      }
      // Only enter generic path when self param has a free type-param.
      if (typeck_type_tree_has_free_type_param(module, arena, p0, 0) == 0) {
        fi = fi + 1;
        continue;
      }
      g_nmap = 0;
      // Pattern-unify formal self with concrete receiver → free-name map.
      if (typeck_pattern_unify_bind(module, arena, p0, arena, base_ty, &names_flat[0], &lens[0],
      &conc[0], &g_nmap, max_map, 0) != 0 || g_nmap <= 0) {
        fi = fi + 1;
        continue;
      }
      // Verify non-self args (exact or after subst for generic formals).
      g_matched = 1;
      g_ai = 0;
      while (g_ai < num_args) {
        g_param = pipeline_module_func_param_type_ref_at(module, fi, g_ai + 1);
        g_arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, g_ai);
        if (g_arg_ref > 0) {
          g_arg_ty = pipeline_expr_resolved_type_ref(arena, g_arg_ref);
        } else {
          g_arg_ty = 0;
        }
        if (g_param <= 0 || g_arg_ty <= 0) {
          g_matched = 0;
          break;
        }
        if (pipeline_typeck_type_refs_equal_c(arena, g_arg_ty, g_param) != 0) {
          g_ai = g_ai + 1;
          continue;
        }
        g_sub = typeck_subst_type_ref(module, arena, arena, g_param, &names_flat[0], &lens[0],
          &conc[0], g_nmap, 0);
        if (g_sub <= 0 || pipeline_typeck_type_refs_equal_c(arena, g_arg_ty, g_sub) == 0) {
          g_matched = 0;
          break;
        }
        g_ai = g_ai + 1;
      }
      if (g_matched == 0) {
        fi = fi + 1;
        continue;
      }
      g_ret = pipeline_module_func_return_type_at(module, fi);
      if (g_ret <= 0) {
        fi = fi + 1;
        continue;
      }
      g_mono = typeck_subst_type_ref(module, arena, arena, g_ret, &names_flat[0], &lens[0], &conc[0],
        g_nmap, 0);
      if (g_mono > 0 && typeck_type_tree_has_free_type_param(module, arena, g_mono, 0) == 0) {
        pipeline_expr_apply_call_resolve(arena, expr_ref, 0 - 1, fi);
        pipeline_expr_set_resolved_type_ref(arena, expr_ref, g_mono);
        return 1;
      }
      fi = fi + 1;
    }
    return 0;
  }
}

/**
 * Stamp monomorphized resolved_type_ref on generic CALL (free *T / module ret /
 * identity formal / turbofish type-arg). Returns 0 always (in-place stamp).
 * @return i32 — always 0 (contract matches residual fixup)
 * PLATFORM: SHARED freestanding typeck.
 */
export function typeck_generic_call_fixup_resolved_type(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32 {
  // PLATFORM: SHARED — sole generic CALL mono fixup (wave1096 / wave252).
  unsafe {
    let ord_var: i32 = 3;
    let ord_field: i32 = 44;
    let ord_named: i32 = 8;
    let callee_ref: i32 = 0;
    let callee_eff: i32 = 0;
    let callee_kind: i32 = 0;
    let func_idx: i32 = 0;
    let ret_ty: i32 = 0;
    let param_ty: i32 = 0;
    let ret_nm: u8[128] = [];
    let param_nm: u8[128] = [];
    let ret_nlen: i32 = 0;
    let param_nlen: i32 = 0;
    let arg_i: i32 = 0;
    let arg_ty: i32 = 0;
    let num_params: i32 = 0;
    let pi: i32 = 0;
    let cnm: u8[128] = [];
    let cnml: i32 = 0;
    let j: i32 = 0;
    let dep_ix: i32 = 0;
    let search_mod: *Module = 0 as *Module;
    let search_arena: *ASTArena = 0 as *ASTArena;
    let cur: i32 = 0;
    let dm: *Module = 0 as *Module;
    let da: *ASTArena = 0 as *ASTArena;
    let nd: i32 = 0;
    let di: i32 = 0;
    let n_map_c: i32 = 0;
    let map_names_c: u8[1024] = [];
    let map_lens_c: i32[8] = [];
    let map_conc_c: i32[8] = [];
    let mono_ret_c: i32 = 0;
    let mono_ret: i32 = 0;
    let n_gp: i32 = 0;
    let n_ta: i32 = 0;
    let ta_ty: i32 = 0;
    let ret_is_module_type: i32 = 0;
    let gnames_n: i32 = 0;
    let gnames: u8[1024] = [];
    let glens: i32[8] = [];
    let gidx: i32 = 0;
    let found_gi: i32 = 0;
    let is_mod: i32 = 0;
    let max_map: i32 = 8;
    let stride: i32 = 128;
    let base: i32 = 0;
    let k: i32 = 0;
    let ci: i32 = 0;
    if (module == 0 as *Module || arena == 0 as *ASTArena || call_expr_ref <= 0) {
      return 0;
    }
    // Already fully concrete — nothing to fix.
    cur = pipeline_expr_resolved_type_ref(arena, call_expr_ref);
    if (cur > 0 && typeck_type_tree_has_free_type_param(module, arena, cur, 0) == 0) {
      return 0;
    }
    callee_ref = pipeline_expr_call_callee_ref_at(arena, call_expr_ref);
    callee_eff = callee_ref;
    callee_kind = pipeline_expr_kind_ord_at(arena, callee_eff);
    cnml = 0;
    search_mod = module;
    search_arena = arena;
    dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref);
    func_idx = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref);
    if (callee_kind == ord_var) {
      cnml = pipeline_expr_var_name_len(arena, callee_eff);
      if (cnml <= 0 || cnml > 127) {
        return 0;
      }
      pipeline_expr_var_name_into(arena, callee_eff, &cnm[0]);
    } else {
      if (callee_kind == ord_field) {
        cnml = pipeline_expr_field_access_name_len(arena, callee_eff);
        if (cnml <= 0 || cnml > 127) {
          return 0;
        }
        pipeline_expr_field_access_name_into(arena, callee_eff, &cnm[0]);
      } else {
        return 0;
      }
    }
    if (dep_ix >= 0 && ctx != 0 as *PipelineDepCtx && dep_ix < pipeline_dep_ctx_ndep(ctx)) {
      dm = pipeline_dep_ctx_module_at(ctx, dep_ix);
      da = pipeline_dep_ctx_arena_at(ctx, dep_ix);
      if (dm != 0 as *Module) {
        search_mod = dm;
        if (da != 0 as *ASTArena) {
          search_arena = da;
        }
      }
    }
    if (func_idx < 0) {
      j = 0;
      while (j < pipeline_module_num_funcs(search_mod)) {
        if (pipeline_module_func_name_equal_at(search_mod, j, &cnm[0], cnml) != 0) {
          func_idx = j;
          break;
        }
        j = j + 1;
      }
    }
    // Local miss: scan deps (bare id via whole/select or binding mis-resolve).
    if (func_idx < 0 && ctx != 0 as *PipelineDepCtx) {
      nd = pipeline_dep_ctx_ndep(ctx);
      di = 0;
      while (di < nd && func_idx < 0) {
        dm = pipeline_dep_ctx_module_at(ctx, di);
        if (dm == 0 as *Module) {
          di = di + 1;
          continue;
        }
        j = 0;
        while (j < pipeline_module_num_funcs(dm)) {
          if (pipeline_module_func_name_equal_at(dm, j, &cnm[0], cnml) != 0) {
            func_idx = j;
            search_mod = dm;
            da = pipeline_dep_ctx_arena_at(ctx, di);
            if (da != 0 as *ASTArena) {
              search_arena = da;
            }
            break;
          }
          j = j + 1;
        }
        di = di + 1;
      }
    }
    if (func_idx < 0) {
      return 0;
    }
    ret_ty = pipeline_module_func_return_type_at(search_mod, func_idx);
    if (ret_ty <= 0) {
      return 0;
    }
    // Non-NAMED return with free type-params (*T, []T, T[N]).
    if (pipeline_type_kind_ord_at(search_arena, ret_ty) != ord_named) {
      if (typeck_type_tree_has_free_type_param(search_mod, search_arena, ret_ty, 0) == 0) {
        return 0;
      }
      n_map_c = typeck_build_value_formal_mono_map(search_mod, search_arena, arena, call_expr_ref,
        func_idx, &map_names_c[0], &map_lens_c[0], &map_conc_c[0], max_map);
      if (n_map_c <= 0) {
        return 0;
      }
      mono_ret_c = typeck_subst_type_ref(search_mod, search_arena, arena, ret_ty, &map_names_c[0],
        &map_lens_c[0], &map_conc_c[0], n_map_c, 0);
      if (mono_ret_c <= 0) {
        return 0;
      }
      if (typeck_type_tree_has_free_type_param(search_mod, arena, mono_ret_c, 0) != 0) {
        return 0;
      }
      pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, mono_ret_c);
      return 0;
    }
    ret_nlen = pipeline_type_named_name_into(search_arena, ret_ty, &ret_nm[0]);
    if (ret_nlen <= 0) {
      return 0;
    }
    num_params = pipeline_module_func_num_params_at(search_mod, func_idx);
    // Identity formal: any formal TYPE_NAMED whose name equals ret name → arg type.
    pi = 0;
    while (pi < num_params) {
      param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi);
      if (param_ty <= 0 || pipeline_type_kind_ord_at(search_arena, param_ty) != ord_named) {
        pi = pi + 1;
        continue;
      }
      param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &param_nm[0]);
      if (param_nlen <= 0 || !name_equal(&ret_nm[0], ret_nlen, &param_nm[0], param_nlen)) {
        pi = pi + 1;
        continue;
      }
      arg_i = pipeline_expr_call_arg_ref(arena, call_expr_ref, pi);
      if (arg_i <= 0) {
        pi = pi + 1;
        continue;
      }
      arg_ty = pipeline_expr_resolved_type_ref(arena, arg_i);
      if (arg_ty <= 0) {
        pi = pi + 1;
        continue;
      }
      pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, arg_ty);
      return 0;
    }
    // Formal-map path: free type-param ret or module ret with free tree.
    mono_ret = typeck_generic_call_subst_ret_from_formal_map(search_mod, search_arena, arena,
      call_expr_ref, func_idx, ret_ty);
    if (mono_ret > 0) {
      pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, mono_ret);
      return 0;
    }
    // Turbofish / ambient expected for type-param ret not on value formals.
    n_gp = pipeline_module_func_num_generic_params_at(search_mod, func_idx);
    n_ta = pipeline_expr_call_num_type_args_at(arena, call_expr_ref);
    ret_is_module_type = typeck_named_is_module_type(search_mod, search_arena, &ret_nm[0], ret_nlen);
    if (ret_is_module_type != 0) {
      return 0;
    }
    /*
     * Bare call + ambient expected (wave 4.2.4): free type-param ret not on
     * value formals (mk_default<T>():T / as_t<T>(i32):T). Stamp any fully
     * concrete expected — prim i32/i64/bool/… or module TYPE_NAMED — so
     * assign/return typeck and codegen mono (resolved_type_ref) agree.
     * Prior gate required module TYPE_NAMED only → `let a: i32 = mk()` left
     * found T. Soft: expected with free T still fail-closed (no stamp).
     * PLATFORM: SHARED freestanding typeck fixup.
     */
    if (n_gp > 0 && n_ta == 0 && expected_ret > 0
    && typeck_type_tree_has_free_type_param(search_mod, arena, expected_ret, 0) == 0) {
      pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, expected_ret);
      return 0;
    }
    if (n_gp <= 0 || n_ta <= 0 || n_ta != n_gp) {
      return 0;
    }
    // Primary: declaration-order index from bound-scan registry.
    found_gi = xlang_generic_func_type_param_index_c(&cnm[0], cnml, &ret_nm[0], ret_nlen);
    if (found_gi >= 0 && found_gi < n_ta) {
      ta_ty = pipeline_expr_call_type_arg_ref_at(arena, call_expr_ref, found_gi);
      if (ta_ty > 0) {
        pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, ta_ty);
        return 0;
      }
    }
    // Fallback: collect type-param names from formals + ret (wave452).
    gnames_n = 0;
    pi = 0;
    while (pi < num_params && gnames_n < 8) {
      param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi);
      if (param_ty <= 0 || pipeline_type_kind_ord_at(search_arena, param_ty) != ord_named) {
        pi = pi + 1;
        continue;
      }
      param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &param_nm[0]);
      if (param_nlen <= 0) {
        pi = pi + 1;
        continue;
      }
      is_mod = typeck_named_is_module_type(search_mod, search_arena, &param_nm[0], param_nlen);
      if (is_mod != 0) {
        pi = pi + 1;
        continue;
      }
      found_gi = 0 - 1;
      gidx = 0;
      while (gidx < gnames_n) {
        if (glens[gidx] == param_nlen) {
          base = gidx * stride;
          k = 0;
          while (k < param_nlen) {
            if (gnames[base + k] != param_nm[k]) {
              break;
            }
            k = k + 1;
          }
          if (k == param_nlen) {
            found_gi = gidx;
            break;
          }
        }
        gidx = gidx + 1;
      }
      if (found_gi >= 0) {
        pi = pi + 1;
        continue;
      }
      base = gnames_n * stride;
      k = 0;
      while (k < 64) {
        gnames[base + k] = 0;
        k = k + 1;
      }
      ci = 0;
      while (ci < param_nlen && ci < 63) {
        gnames[base + ci] = param_nm[ci];
        ci = ci + 1;
      }
      glens[gnames_n] = param_nlen;
      gnames_n = gnames_n + 1;
      pi = pi + 1;
    }
    found_gi = 0 - 1;
    gidx = 0;
    while (gidx < gnames_n) {
      if (glens[gidx] == ret_nlen) {
        base = gidx * stride;
        k = 0;
        while (k < ret_nlen) {
          if (gnames[base + k] != ret_nm[k]) {
            break;
          }
          k = k + 1;
        }
        if (k == ret_nlen) {
          found_gi = gidx;
          break;
        }
      }
      gidx = gidx + 1;
    }
    if (found_gi < 0 && gnames_n < 8) {
      base = gnames_n * stride;
      k = 0;
      while (k < 64) {
        gnames[base + k] = 0;
        k = k + 1;
      }
      ci = 0;
      while (ci < ret_nlen && ci < 63) {
        gnames[base + ci] = ret_nm[ci];
        ci = ci + 1;
      }
      glens[gnames_n] = ret_nlen;
      found_gi = gnames_n;
      gnames_n = gnames_n + 1;
    }
    if (found_gi < 0) {
      return 0;
    }
    // n_gp==1 always uses slot 0 when ret is type param.
    if (n_gp == 1) {
      found_gi = 0;
    } else {
      if (n_gp > 1 && gnames_n != n_gp) {
        return 0;
      }
    }
    ta_ty = pipeline_expr_call_type_arg_ref_at(arena, call_expr_ref, found_gi);
    if (ta_ty <= 0) {
      return 0;
    }
    pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, ta_ty);
    return 0;
  }
}

/**
 * Cap residual face: generic method_call UFCS (thin → pure).
 * G.7 dual-export ban — residual body deleted.
 * @return i32 — 1 success, 0 no match
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_method_call_generic_ufcs_c(module: *Module, arena: *ASTArena,
expr_ref: i32, base_ty: i32, method_nm: *u8, method_nlen: i32, num_args: i32): i32 {
  // PLATFORM: SHARED — Cap residual face; body = pure method_call_generic_ufcs.
  return typeck_method_call_generic_ufcs(module, arena, expr_ref, base_ty, method_nm, method_nlen,
    num_args);
}

/**
 * Cap residual face: generic CALL mono fixup (thin → pure).
 * G.7 dual-export ban — residual body deleted.
 * @return i32 — always 0 (in-place stamp)
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function glue_generic_call_fixup_resolved_type_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx, expected_ret: i32): i32 {
  // PLATFORM: SHARED — Cap residual face; body = pure generic_call_fixup.
  return typeck_generic_call_fixup_resolved_type(module, arena, call_expr_ref, ctx, expected_ret);
}

// end wave252 pure-owned leave

// ---------------------------------------------------------------------------
// wave254: typeck dep map + find_func pure leave (method_call residual subdomain)
// Authority: typeck_x.o (this file + typeck_gen hand-sync / migrate).
// Symbols (#[no_mangle] Cap faces):
//   pipeline_typeck_set_entry_module_for_dep_map_c
//   pipeline_typeck_get_dep_return_type_in_caller_arena_c
//   pipeline_typeck_dep_return_type_to_caller_arena_c
//   pipeline_typeck_expr_var_name_equal_func_c
//   pipeline_typeck_find_func_return_type_in_module_by_name_c
//   pipeline_typeck_find_func_return_type_in_module_c
// Live bodies: g_typeck_entry_module_for_dep_map + typeck_map_import_binding_named_to_caller
//   + get_dep_return_type_in_caller_arena + dep_return_type_to_caller_arena
//   + expr_var_name_equal_func + find_func_return_type_in_module(_by_name)
// Cap residual method_call: delete second bodies (static map/impl + public faces);
//   dual-export ban — residual extern-only / thin import faces kept.
// strict_minimal: set_entry / get_dep thin → typeck Cap faces (no second BSS).
// PLATFORM: SHARED freestanding typeck dep map / find_func.
// ---------------------------------------------------------------------------

/**
 * Set entry module for dep return TYPE_NAMED binding-prefix mapping.
 * @param module *Module — entry module; null clears
 * @return void
 * wave254 pure leave — G.7 authority (was Cap residual + strict_minimal BSS).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_set_entry_module_for_dep_map_c(module: *Module): void {
  g_typeck_entry_module_for_dep_map = module;
}

/**
 * Cap residual face: get dep return type in caller arena (thin → pure get_dep).
 * @param from_dep_index i32 — dep slot
 * @param dep_return_type_ref i32 — type_ref in dep arena
 * @param caller_arena *ASTArena — destination
 * @param ctx *PipelineDepCtx — dep pool
 * @return i32 — caller type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_get_dep_return_type_in_caller_arena_c(from_dep_index: i32,
dep_return_type_ref: i32, caller_arena: *ASTArena, ctx: *PipelineDepCtx): i32 {
  return get_dep_return_type_in_caller_arena(from_dep_index, dep_return_type_ref, caller_arena, ctx);
}

/**
 * Cap residual face: recursive dep→caller type_ref map (thin → pure).
 * @param dep_arena *ASTArena — source type pool
 * @param dep_return_type_ref i32 — source type_ref
 * @param caller_arena *ASTArena — destination
 * @return i32 — caller type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_dep_return_type_to_caller_arena_c(dep_arena: *ASTArena,
dep_return_type_ref: i32, caller_arena: *ASTArena): i32 {
  return dep_return_type_to_caller_arena(dep_arena, dep_return_type_ref, caller_arena);
}

/**
 * Cap residual face: VAR callee name equals module.funcs[func_index] (i32 0/1).
 * @param arena *ASTArena — callee expr arena
 * @param callee_expr_ref i32 — VAR expr
 * @param mod *Module — function table
 * @param func_index i32 — candidate func index
 * @return i32 — 1 match, 0 no
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_expr_var_name_equal_func_c(arena: *ASTArena, callee_expr_ref: i32,
mod: *Module, func_index: i32): i32 {
  if (expr_var_name_equal_func(arena, callee_expr_ref, mod, func_index)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: find func return type by name (thin → pure).
 * @return i32 — type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_find_func_return_type_in_module_by_name_c(mod: *Module,
caller_arena: *ASTArena, name: *u8, name_len: i32, from_dep_index: i32, ctx: *PipelineDepCtx,
func_index_out: *i32): i32 {
  return find_func_return_type_in_module_by_name(mod, caller_arena, name, name_len, from_dep_index,
    ctx, func_index_out);
}

/**
 * wave303 G.7 8.3.6 leave: W-heap-overload pick for CALL/METHOD_CALL by name.
 * Product STRONG on typeck_x.o (link before strict_minimal WEAK suffix).
 * Score authority: typeck_overload_arg_param_score + by_name_overload (METHOD_CALL args).
 * call_expr_ref<=0: arity-only (want_arity) via index pick + visibility + dep map.
 * is_method: historical seed flag; scoring uses expr kind METHOD_CALL=49.
 * dual-export ban: seed body deleted same commit.
 * @return i32 — caller-mapped return type_ref; 0 not found / visibility denied
 * PLATFORM: SHARED freestanding typeck 8.3.6 leave.
 */
#[no_mangle]
export function pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(
  mod: *Module, caller_arena: *ASTArena, name: *u8, name_len: i32, from_dep_index: i32,
  want_arity: i32, call_expr_ref: i32, is_method: i32, ctx: *PipelineDepCtx,
  func_index_out: *i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    let ret: i32 = 0;
    let fi: i32 = 0 - 1;
    let _im: i32 = is_method;
    if (_im < 0) {
      _im = 0;
    }
    if (mod == 0 as *Module || name == 0 as *u8 || name_len <= 0) {
      return 0;
    }
    if (call_expr_ref > 0 && caller_arena != 0 as *ASTArena) {
      ret = find_func_return_type_in_module_by_name_overload(
        mod, caller_arena, name, name_len, call_expr_ref, from_dep_index, ctx, func_index_out);
      if (ret > 0 && from_dep_index >= 0 && func_index_out != 0 as *i32) {
        fi = func_index_out[0];
        if (fi >= 0 && pipeline_visibility_allow_func(mod, fi, 1) == 0) {
          return 0;
        }
      }
      return ret;
    }
    /* Arity-only: first same-name with want_arity (seed pick when no call_expr). */
    fi = 0 - 1;
    {
      let j: i32 = 0;
      let first_match: i32 = 0 - 1;
      let n: i32 = pipeline_module_num_funcs(mod);
      while (j < n) {
        if (pipeline_module_func_name_equal_at(mod, j, name, name_len) != 0) {
          if (first_match < 0) {
            first_match = j;
          }
          if (want_arity >= 0) {
            if (pipeline_module_func_num_params_at(mod, j) == want_arity) {
              fi = j;
              break;
            }
          }
        }
        j = j + 1;
      }
      if (fi < 0) {
        fi = first_match;
      }
    }
    if (fi < 0) {
      return 0;
    }
    if (from_dep_index >= 0 && pipeline_visibility_allow_func(mod, fi, 1) == 0) {
      return 0;
    }
    if (func_index_out != 0 as *i32) {
      func_index_out[0] = fi;
    }
    ret = pipeline_module_func_return_type_at(mod, fi);
    if (from_dep_index < 0) {
      return ret;
    }
    return get_dep_return_type_in_caller_arena(from_dep_index, ret, caller_arena, ctx);
  }
  return 0;
}

/**
 * wave303 G.7 8.3.6 leave: arity-only wrapper (no call-site scoring).
 * dual-export ban vs seed strict_minimal residual.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_find_func_return_type_in_module_by_name_strict_minimal(
  mod: *Module, caller_arena: *ASTArena, name: *u8, name_len: i32, from_dep_index: i32,
  want_arity: i32, ctx: *PipelineDepCtx, func_index_out: *i32): i32 {
  return pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(
    mod, caller_arena, name, name_len, from_dep_index, want_arity, 0, 0, ctx, func_index_out);
}

/**
 * Cap residual face: find func return type by callee VAR expr (thin → pure).
 * @return i32 — type_ref or 0
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_find_func_return_type_in_module_c(mod: *Module, mod_arena: *ASTArena,
caller_arena: *ASTArena, callee_arena: *ASTArena, callee_expr_ref: i32, from_dep_index: i32,
ctx: *PipelineDepCtx, func_index_out: *i32): i32 {
  return find_func_return_type_in_module(mod, mod_arena, caller_arena, callee_arena, callee_expr_ref,
    from_dep_index, ctx, func_index_out);
}

// end wave254 pure-owned leave

// ---------------------------------------------------------------------------
// wave255: typeck CTFE Cap residual pure-owned leave (host-cc present 56→55)
// Delete pipeline_typeck_ctfe.c from pipeline_x mega-TU.
// Historical pipeline_* / pipeline_typeck_*_c CTFE faces → typeck_* pure authority
//   (typeck_fold_* / typeck_block_const_init_is_const / typeck_const_init_not_constant /
//    typeck_expr_is_c_static_const_init; bodies in typeck_gen product twin).
// Cap residual: dual-export ban — no second thin body on pipeline_x.
// strict_minimal: XLANG_WEAK const_init faces remain bootstrap fallback only.
// PLATFORM: SHARED freestanding typeck CTFE Cap leave.
// ---------------------------------------------------------------------------

/**
 * Cap residual face: block const init is constant expression (thin → pure).
 * @param arena *ASTArena — block arena
 * @param block_ref i32 — block ref
 * @param const_idx i32 — const index in block
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_block_const_init_is_const_c(arena: *ASTArena, block_ref: i32,
const_idx: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  // Callee is export-extern (seed / pure twin); monofile -E requires unsafe.
  unsafe {
    return typeck_block_const_init_is_const(arena, block_ref, const_idx);
  }
}

/**
 * Cap residual face: diag const init must be constant (thin → pure).
 * @param line i32 — source line
 * @param col i32 — source column
 * @return void
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_const_init_not_constant_c(line: i32, col: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    typeck_const_init_not_constant(line, col);
  }
}

/**
 * Cap residual face: fold expr CTFE (thin → pure typeck_fold_expr).
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return void
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_fold_expr_c(arena: *ASTArena, expr_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    typeck_fold_expr(arena, expr_ref);
  }
}

/**
 * Cap residual face: fold block const init (thin → pure).
 * @param arena *ASTArena
 * @param block_ref i32
 * @param const_idx i32
 * @return void
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_fold_block_const_init_c(arena: *ASTArena, block_ref: i32,
const_idx: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    typeck_fold_block_const_init(arena, block_ref, const_idx);
  }
}

/**
 * Cap residual face: fold expr with block const env (thin → pure).
 * @param arena *ASTArena
 * @param block_ref i32
 * @param expr_ref i32
 * @return void
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_fold_expr_in_block_c(arena: *ASTArena, block_ref: i32,
expr_ref: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    typeck_fold_expr_in_block(arena, block_ref, expr_ref);
  }
}

/**
 * Cap residual face: pure-lit tree legal as C static init (codegen gate).
 * Historical name pipeline_expr_is_c_static_const_init (no _c suffix).
 * @param arena *ASTArena
 * @param expr_ref i32
 * @return i32 — 1 yes, 0 no
 * PLATFORM: SHARED freestanding typeck / codegen static-init gate.
 */
#[no_mangle]
export function pipeline_expr_is_c_static_const_init(arena: *ASTArena, expr_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    return typeck_expr_is_c_static_const_init(arena, expr_ref);
  }
}

// end wave255 pure-owned leave

// ---------------------------------------------------------------------------
// wave256: typeck assign Cap residual pure-owned leave (host-cc present 55→54)
// Delete pipeline_typeck_assign.c from pipeline_x mega-TU.
// Historical pipeline_typeck_*_c assign + diag-fmt faces → typeck_* pure authority
//   (typeck_check_expr_assign + typeck_diag_*). Active-module stamp stays on
//   runtime_pipeline_abi (pipeline_typeck_active_module_set_c) before assign body.
// Cap residual: dual-export ban — no second thin body on pipeline_x.
// Same-TU static pipeline_typeck_module_num_imports_c retired (dead; callers use
//   typeck_module_num_imports / parser face).
// PLATFORM: SHARED freestanding typeck assign Cap leave.
// ---------------------------------------------------------------------------

/** Cap residual face: set pure BSS active module (wave224 runtime_pipeline_abi). */
export extern function pipeline_typeck_active_module_set_c(m: *Module): void;

/**
 * Cap residual face: EXPR_ASSIGN / compound assign check (thin → pure).
 * Stamps active-module cell then delegates to typeck_check_expr_assign.
 * @param module *Module
 * @param arena *ASTArena
 * @param expr_ref i32
 * @param return_type_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_expr_assign_c(module: *Module, arena: *ASTArena,
expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — Cap thin: bounds + active-module stamp + pure assign.
  unsafe {
    if (arena == 0 as *ASTArena || expr_ref <= 0 || expr_ref > arena.num_exprs) {
      return 0;
    }
    pipeline_typeck_active_module_set_c(module);
    return typeck_check_expr_assign(module, arena, expr_ref, return_type_ref, ctx);
  }
}

/**
 * Cap residual face: append literal bytes into diag buffer (thin → pure).
 * @param out *u8
 * @param pos i32
 * @param cap i32
 * @param lit *u8
 * @param lit_len i32
 * @return i32 — new write pos
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_diag_append_lit_c(out: *u8, pos: i32, cap: i32, lit: *u8,
lit_len: i32): i32 {
  return typeck_diag_append_lit(out, pos, cap, lit, lit_len);
}

/**
 * Cap residual face: append u32 decimal into diag buffer (thin → pure).
 * @param out *u8
 * @param pos i32
 * @param cap i32
 * @param v i32
 * @return i32 — new write pos
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_diag_append_u32_dec_c(out: *u8, pos: i32, cap: i32, v: i32): i32 {
  return typeck_diag_append_u32_dec(out, pos, cap, v);
}

/**
 * Cap residual face: format type ref into diag buffer at cursor (thin → pure).
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @param cur i32
 * @param cap i32
 * @return i32 — new write pos
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_diag_fmt_type_at_c(arena: *ASTArena, ref: i32, out: *u8, cur: i32,
cap: i32): i32 {
  return typeck_diag_fmt_type_at(arena, ref, out, cur, cap);
}

/**
 * Cap residual face: format type ref into fresh diag buffer (thin → pure).
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @param cap i32
 * @return i32 — written length
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_diag_fmt_type_into_c(arena: *ASTArena, ref: i32, out: *u8,
cap: i32): i32 {
  return typeck_diag_fmt_type_into(arena, ref, out, cap);
}

/**
 * Cap residual face: format type or "?" when unresolved (thin → pure).
 * @param arena *ASTArena
 * @param ref i32
 * @param out *u8
 * @return i32 — written length
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_diag_fmt_type_or_question_c(arena: *ASTArena, ref: i32,
out: *u8): i32 {
  return typeck_diag_fmt_type_or_question(arena, ref, out);
}

// end wave256 pure-owned leave

// ---------------------------------------------------------------------------
// wave257: typeck region_assign Cap residual pure-owned leave (host-cc present 54→53)
// Delete pipeline_typeck_region_assign.c from pipeline_x mega-TU.
// Historical pipeline_typeck_*_c region/escape faces → typeck_* pure authority
//   (slice_region / return_slice / struct_stack_escape / scope_borrow /
//    allocator_region / call_slice_region). All pure bodies already live in
//   typeck.x (wave235–239); this wave only lifts residual thin Cap faces.
// Cap residual: dual-export ban — no second thin body on pipeline_x.
// PLATFORM: SHARED freestanding typeck region_assign Cap leave.
// ---------------------------------------------------------------------------

/**
 * Cap residual face: M-3 slice region assign/let/arg (thin → pure).
 * @param arena *ASTArena
 * @param site_expr_ref i32 — site for line/col
 * @param expect_ref i32 — expected type ref
 * @param src_ref i32 — source type ref
 * @return i32 — 0 ok, -1 fail (diag already reported)
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_slice_region_assign_c(arena: *ASTArena, site_expr_ref: i32,
expect_ref: i32, src_ref: i32): i32 {
  return typeck_check_slice_region_assign(arena, site_expr_ref, expect_ref, src_ref);
}

/**
 * Cap residual face: WPO-S3 stack-escape assign (thin → pure).
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32
 * @param left_ref i32
 * @param right_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_struct_stack_escape_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_struct_stack_escape_assign(module, arena, site_expr_ref, left_ref, right_ref, ctx);
}

/**
 * Cap residual face: MEM-A3 scope-borrow assign (thin → pure).
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32
 * @param left_ref i32
 * @param right_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_scope_borrow_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, right_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_scope_borrow_assign(module, arena, site_expr_ref, left_ref, right_ref, ctx);
}

/**
 * Cap residual face: MEM-A3 scope-borrow return (thin → pure).
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32
 * @param op_ref i32
 * @param return_type_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_scope_borrow_return_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, op_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_scope_borrow_return(module, arena, site_expr_ref, op_ref, return_type_ref, ctx);
}

/**
 * Cap residual face: MEM-C1 allocator region assign (thin → pure).
 * @param module *Module
 * @param arena *ASTArena
 * @param site_expr_ref i32
 * @param left_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_allocator_region_assign_c(module: *Module, arena: *ASTArena,
site_expr_ref: i32, left_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_allocator_region_assign(module, arena, site_expr_ref, left_ref, ctx);
}

/**
 * Cap residual face: MEM-C1 allocator region return (thin → pure).
 * @param arena *ASTArena
 * @param site_expr_ref i32
 * @param return_type_ref i32
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_allocator_region_return_c(arena: *ASTArena, site_expr_ref: i32,
return_type_ref: i32): i32 {
  return typeck_check_allocator_region_return(arena, site_expr_ref, return_type_ref);
}

/**
 * Cap residual face: M-3 return slice region (thin → pure).
 * @param arena *ASTArena
 * @param ret_site_ref i32
 * @param op_ref i32
 * @param func_return_ref i32
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_return_slice_region_c(arena: *ASTArena, ret_site_ref: i32,
op_ref: i32, func_return_ref: i32): i32 {
  return typeck_check_return_slice_region(arena, ret_site_ref, op_ref, func_return_ref);
}

/**
 * Cap residual face: M-3 CALL slice region (thin → pure).
 * @param module *Module
 * @param arena *ASTArena
 * @param call_expr_ref i32
 * @param ctx *PipelineDepCtx
 * @return i32 — 0 ok, -1 fail
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_call_slice_region_c(module: *Module, arena: *ASTArena,
call_expr_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_call_slice_region(module, arena, call_expr_ref, ctx);
}

// end wave257 pure-owned leave

// ---------------------------------------------------------------------------
// wave258: typeck coerce_init Cap residual pure-owned leave (host-cc present 53→52)
// Delete pipeline_typeck_coerce_init.c from pipeline_x mega-TU.
// Historical pipeline_typeck_*_c coerce/type_refs/widen/ret_coerce/int_lit/
//   expr_is_any_assign faces → typeck_* pure authority (wave227–233).
// float_bits residual moved to ast_pool_arena.c (glue_arena_expr_at_ref home).
// Cap residual: dual-export ban — no second thin body on pipeline_x.
// PLATFORM: SHARED freestanding typeck coerce_init Cap leave.
// ---------------------------------------------------------------------------

/**
 * Cap residual face: integer-literal init coerce (thin → pure).
 * @param arena *ASTArena
 * @param init_ref i32
 * @param decl_ty_ref i32
 * @param decl_kind i32
 * @param init_kind i32
 * @return i32 — non-zero when coerce applied
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_lit_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: float-lit / -float init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_float_lit_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_float_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: enum field-access init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_enum_field_to_decl_c(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_enum_field_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: named-call init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_named_call_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_named_call_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: array/vector lit init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_array_vector_lit_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  /* C ABI unchanged: no module param. Pass 0 → active_module fallback. */
  return typeck_coerce_init_array_vector_lit_to_decl(0 as *Module, arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: vector binop init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_vector_binop_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_vector_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: int binop / EXPR_NEG init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_int_binop_to_decl_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32, init_kind: i32): i32 {
  return typeck_coerce_init_int_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}

/**
 * Cap residual face: struct_lit init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_struct_lit_to_decl_c(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32): i32 {
  return typeck_coerce_init_struct_lit_to_decl(module, arena, init_ref, decl_ty_ref);
}

/**
 * Cap residual face: array→slice init coerce (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_slice_from_array_c(arena: *ASTArena, init_ref: i32,
decl_ty_ref: i32, decl_kind: i32): i32 {
  return typeck_coerce_init_slice_from_array(arena, init_ref, decl_ty_ref, decl_kind);
}

/**
 * Cap residual face: let/const init coerce dispatcher (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_coerce_init_expr_to_decl_c(module: *Module, arena: *ASTArena,
init_ref: i32, decl_ty_ref: i32): i32 {
  return typeck_coerce_init_expr_to_decl(module, arena, init_ref, decl_ty_ref);
}

/**
 * Cap residual face: f32→f64 float widen gate (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_float_widen_ok_c(dest_kind: i32, src_kind: i32): i32 {
  if (typeck_float_widen_ok(dest_kind, src_kind)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: first-class integer widen matrix (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_integer_widen_ok_c(dest_kind: i32, src_kind: i32): i32 {
  if (typeck_integer_widen_ok(dest_kind, src_kind)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: refs-based integer widen (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_integer_widen_ok_refs_c(arena: *ASTArena, dest_ref: i32, src_ref: i32): i32 {
  if (typeck_integer_widen_ok_refs(arena, dest_ref, src_ref)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: NAMED type_refs_equal (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_refs_equal_named_c(arena: *ASTArena, a: i32, b: i32): i32 {
  if (type_refs_equal_named(arena, a, b)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: resolve_type_alias_ref public C name (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_resolve_type_alias_ref_c(arena: *ASTArena, type_ref: i32): i32 {
  return typeck_resolve_type_alias_ref(arena, type_ref);
}

/**
 * Cap residual face: type_refs_equal_impl (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_refs_equal_impl_c(arena: *ASTArena, a: i32, b: i32): i32 {
  if (type_refs_equal_impl(arena, a, b)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: type_refs_equal public C ABI (thin → pure; bool as i32).
 * typeck.x call sites use this historical name; pure body is type_refs_equal.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_refs_equal_c(arena: *ASTArena, a: i32, b: i32): i32 {
  if (type_refs_equal(arena, a, b)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: type_refs_equal_same_kind (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_refs_equal_same_kind_c(arena: *ASTArena, a: i32, b: i32,
kind_ord: i32): i32 {
  if (type_refs_equal_same_kind(arena, a, b, kind_ord)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: type_ref_is_bool_impl (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_ref_is_bool_impl_c(arena: *ASTArena, type_ref: i32): i32 {
  if (type_ref_is_bool_impl(arena, type_ref)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: type_ref_is_bool (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_type_ref_is_bool_c(arena: *ASTArena, type_ref: i32): i32 {
  if (type_ref_is_bool(arena, type_ref)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: expr_type_ref_impl (thin → pure; same as expr_type_ref).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_expr_type_ref_impl_c(arena: *ASTArena, expr_ref: i32): i32 {
  return expr_type_ref(arena, expr_ref);
}

/**
 * Cap residual face: expr_type_ref public C name (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_expr_type_ref_c(arena: *ASTArena, expr_ref: i32): i32 {
  return expr_type_ref(arena, expr_ref);
}

/**
 * Cap residual face: return operand matches (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_return_operand_matches_c(arena: *ASTArena, op_ref: i32,
expect_ref: i32): i32 {
  if (typeck_return_operand_matches(0 as *Module, arena, op_ref, expect_ref)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: u8/usize → i32 return stamp (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_ret_coerce_integral_to_expect_i32_c(arena: *ASTArena, op_ref: i32,
expect_ref: i32): void {
  typeck_ret_coerce_integral_to_expect_i32(arena, op_ref, expect_ref);
}

/**
 * Cap residual face: integer widen stamp on return operand (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_ret_coerce_integral_widen_c(arena: *ASTArena, op_ref: i32,
expect_ref: i32): void {
  typeck_ret_coerce_integral_widen(arena, op_ref, expect_ref);
}

/**
 * Cap residual face: EXPR_LIT default i32/i64 stamp (thin → pure; return_type_ref=0).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_expr_int_lit_c(arena: *ASTArena, expr_ref: i32): i32 {
  return typeck_check_expr_int_lit(arena, expr_ref, 0);
}

/**
 * Cap residual face: assign-kind classifier for residual mega dispatch (thin → pure).
 * @param kind_ord i32 — ExprKind ordinal
 * @return i32 — 1 if plain/compound assign, 0 otherwise
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_expr_is_any_assign_kind_c(kind_ord: i32): i32 {
  if (typeck_expr_is_any_assign_kind(kind_ord)) {
    return 1;
  }
  return 0;
}

// end wave258 pure-owned leave

// ---------------------------------------------------------------------------
// wave259: typeck check_block Cap residual pure-owned leave (host-cc present 52→51)
// Delete pipeline_typeck_check_block.c from pipeline_x mega-TU.
// Historical pipeline_typeck_*_c check_block / ctx / depth / linear / has_implicit
//   faces → typeck_x.o sole authority (#[no_mangle] Cap + pure BSS cells).
// XLANG_WEAK check_block_impl / patch_all_body_parent_links residual cold
//   fallbacks retired — product pure already owns strong faces.
// Cap residual: dual-export ban — no second thin body on pipeline_x.
// PLATFORM: SHARED freestanding typeck check_block Cap leave.
// ---------------------------------------------------------------------------

// LANG-007 v2: unsafe { } nest depth sidecar (no PipelineDepCtx ABI growth).
let g_typeck_unsafe_depth: i32 = 0;

// M-4: linear type use-once move tracking (per-func reset). Cap 128 names x 128 bytes.
let g_typeck_linear_moved_n: i32 = 0;
let g_typeck_linear_moved_names: u8[16384] = [];
let g_typeck_linear_moved_lens: i32[128] = [];

// WPO-S3: active typeck ctx for call-slice C glue without ctx param (write-only cell).
let g_typeck_active_ctx: *PipelineDepCtx = 0 as *PipelineDepCtx;

/**
 * Cap residual face: bind ctx.current_block_ref, return saved.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_block_impl_bind_ctx_c(ctx: *PipelineDepCtx, block_ref: i32): i32 {
  let saved: i32 = 0;
  if (ctx == 0 as *PipelineDepCtx) {
    return 0;
  }
  saved = ctx.current_block_ref;
  ctx.current_block_ref = block_ref;
  return saved;
}

/**
 * Cap residual face: restore ctx.current_block_ref.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_block_impl_restore_ctx_c(ctx: *PipelineDepCtx, saved_block_ref: i32): void {
  if (ctx == 0 as *PipelineDepCtx) {
    return;
  }
  ctx.current_block_ref = saved_block_ref;
}

/**
 * Cap residual face: keep current_block_ref aligned with the block under check.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_block_impl_touch_ctx_block_c(ctx: *PipelineDepCtx, block_ref: i32): void {
  if (ctx == 0 as *PipelineDepCtx) {
    return;
  }
  ctx.current_block_ref = block_ref;
}

/**
 * Cap residual face: typeck_loop_depth++ , return prior depth.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_loop_depth_push_c(ctx: *PipelineDepCtx): i32 {
  let saved: i32 = 0;
  if (ctx == 0 as *PipelineDepCtx) {
    return 0;
  }
  saved = ctx.typeck_loop_depth;
  ctx.typeck_loop_depth = saved + 1;
  return saved;
}

/**
 * Cap residual face: restore typeck_loop_depth.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_loop_depth_pop_c(ctx: *PipelineDepCtx, saved_loop_depth: i32): void {
  if (ctx == 0 as *PipelineDepCtx) {
    return;
  }
  ctx.typeck_loop_depth = saved_loop_depth;
}

/**
 * Cap residual face: read process-local unsafe nest depth (ctx unused).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_dep_ctx_typeck_unsafe_depth_at(ctx: *PipelineDepCtx): i32 {
  if (ctx == 0 as *PipelineDepCtx) {
    // residual ignored ctx; keep same regardless of null
  }
  return g_typeck_unsafe_depth;
}

/**
 * Cap residual face: unsafe depth++ , return prior.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_unsafe_depth_push_c(ctx: *PipelineDepCtx): i32 {
  let saved: i32 = 0;
  if (ctx == 0 as *PipelineDepCtx) {
    // unused
  }
  saved = g_typeck_unsafe_depth;
  g_typeck_unsafe_depth = saved + 1;
  return saved;
}

/**
 * Cap residual face: restore unsafe nest depth.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_unsafe_depth_pop_c(ctx: *PipelineDepCtx, saved_unsafe_depth: i32): void {
  if (ctx == 0 as *PipelineDepCtx) {
    // unused
  }
  g_typeck_unsafe_depth = saved_unsafe_depth;
}

/**
 * Cap residual face: write ctx.typeck_loop_depth (used by pure push/pop).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_loop_depth_set_c(ctx: *PipelineDepCtx, depth: i32): void {
  if (ctx == 0 as *PipelineDepCtx) {
    return;
  }
  ctx.typeck_loop_depth = depth;
}

/**
 * Cap residual face: product-mega check_block_impl → pure walker.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_block_impl_c(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  return check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}

/**
 * Cap residual face: bounds then pure check_block walker.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_block_c(module: *Module, arena: *ASTArena, block_ref: i32,
return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  if (ast.ref_is_null(block_ref)) {
    return 0;
  }
  if (block_ref <= 0 || arena == 0 as *ASTArena || block_ref > arena.num_blocks) {
    return 0;
  }
  return check_block(module, arena, block_ref, return_type_ref, ctx);
}

/**
 * Cap residual face: as_loop_body thin → pure (loop_depth push/pop inside).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_check_block_as_loop_body_c(module: *Module, arena: *ASTArena,
body_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  return check_block_as_loop_body(module, arena, body_ref, return_type_ref, ctx);
}

/**
 * Cap residual face: set active module + process-local ctx cell.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_set_active_ctx_c(module: *Module, ctx: *PipelineDepCtx): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    pipeline_typeck_active_module_set_c(module);
    g_typeck_active_ctx = ctx;
  }
}

/**
 * Process-local PipelineDepCtx written by pipeline_typeck_set_active_ctx_c.
 * Null outside typeck_parsed_module. The const-expr whitelist (residual C)
 * reads this so `import.CONST` FIELD can reuse typeck_field_import_const_is_const
 * without growing the whitelist helper's signature.
 * @return *PipelineDepCtx — active ctx, or null
 * PLATFORM: SHARED — G.7 complete the existing setter cell.
 */
#[no_mangle]
export function pipeline_typeck_active_ctx_c(): *PipelineDepCtx {
  return g_typeck_active_ctx;
}

/**
 * Cap residual face: clear linear moved set (per-function).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_linear_reset_c(): void {
  g_typeck_linear_moved_n = 0;
}

/**
 * Linear move-set name equality (exact len + bytes). Returns 1 if match.
 * PLATFORM: SHARED freestanding typeck.
 */
function typeck_linear_name_already_moved(name: *u8, name_len: i32): i32 {
  let i: i32 = 0;
  let j: i32 = 0;
  let base: i32 = 0;
  if (name == 0 as *u8 || name_len <= 0) {
    return 0;
  }
  while (i < g_typeck_linear_moved_n) {
    if (g_typeck_linear_moved_lens[i] == name_len) {
      base = i * 128;
      j = 0;
      while (j < name_len) {
        if (g_typeck_linear_moved_names[base + j] != name[j]) {
          j = name_len + 1;
        } else {
          j = j + 1;
        }
      }
      if (j == name_len) {
        return 1;
      }
    }
    i = i + 1;
  }
  return 0;
}

/**
 * Cap residual face: VAR read of Linear(T) double-move gate; mark moved on success.
 * @return i32 — 0 ok, -1 already moved (diag emitted)
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_linear_use_var_c(arena: *ASTArena, type_ref: i32, expr_ref: i32,
name: *u8, name_len: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let line: i32 = 0;
    let col: i32 = 0;
    let i: i32 = 0;
    let base: i32 = 0;
    // TYPE_LINEAR ord = 12 (TypeKind enum)
    let ord_linear: i32 = 12;
    if (arena == 0 as *ASTArena || name_len <= 0 || name_len > 127 || name == 0 as *u8) {
      return 0;
    }
    if (type_ref <= 0 || pipeline_type_kind_ord_at(arena, type_ref) != ord_linear) {
      return 0;
    }
    if (typeck_linear_name_already_moved(name, name_len) != 0) {
      line = 0;
      col = 0;
      if (expr_ref > 0 && expr_ref <= arena.num_exprs) {
        line = pipeline_expr_line_at(arena, expr_ref);
        col = pipeline_expr_col_at(arena, expr_ref);
      }
      lsp_diag_report_typeck(line, col, "linear value used after move" as *u8);
      return 0 - 1;
    }
    if (g_typeck_linear_moved_n < 128) {
      base = g_typeck_linear_moved_n * 128;
      i = 0;
      while (i < name_len) {
        g_typeck_linear_moved_names[base + i] = name[i];
        i = i + 1;
      }
      g_typeck_linear_moved_lens[g_typeck_linear_moved_n] = name_len;
      g_typeck_linear_moved_n = g_typeck_linear_moved_n + 1;
    }
    return 0;
  }
}

/**
 * Cap residual face: Linear(T) let accepts Linear(T) or inner T init.
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_linear_accepts_init_c(arena: *ASTArena, decl_ref: i32,
init_ref: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let ord_linear: i32 = 12;
    if (arena == 0 as *ASTArena || decl_ref <= 0 || init_ref <= 0) {
      return 0;
    }
    if (pipeline_type_kind_ord_at(arena, decl_ref) != ord_linear) {
      return 0;
    }
    if (type_refs_equal(arena, decl_ref, init_ref)) {
      return 1;
    }
    if (type_refs_equal(arena, pipeline_type_elem_ref_at(arena, decl_ref), init_ref)) {
      return 1;
    }
    return 0;
  }
}

/**
 * Cap residual face: reject ADDR_OF on Linear var (before linear_use_var).
 * @return i32 — 0 continue, -1 diagnostic emitted
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_reject_addr_of_linear_c(arena: *ASTArena, op_ref: i32,
addr_expr_ref: i32, module: *Module, ctx: *PipelineDepCtx): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    let vnlen: i32 = 0;
    let block_ref: i32 = 0;
    let vd_tr: i32 = 0;
    let func_ix: i32 = 0;
    let pr: i32 = 0;
    let line: i32 = 0;
    let col: i32 = 0;
    let vbuf: u8[128] = [];
    let ord_linear: i32 = 12;
    let ord_var: i32 = 3;
    let i: i32 = 0;
    if (arena == 0 as *ASTArena || module == 0 as *Module || ctx == 0 as *PipelineDepCtx ||
        op_ref <= 0 || op_ref > arena.num_exprs) {
      return 0;
    }
    if (pipeline_expr_kind_ord_at(arena, op_ref) != ord_var) {
      return 0;
    }
    vnlen = pipeline_expr_var_name_len(arena, op_ref);
    if (vnlen <= 0 || vnlen > 127) {
      return 0;
    }
    pipeline_expr_var_name_into(arena, op_ref, &vbuf[0]);
    block_ref = ctx.current_block_ref;
    if (block_ref > 0 && block_ref <= arena.num_blocks) {
      vd_tr = pipeline_block_resolve_var_type_ref(arena, block_ref, &vbuf[0], vnlen);
      if (vd_tr > 0 && pipeline_type_kind_ord_at(arena, vd_tr) == ord_linear) {
        line = 0;
        col = 0;
        if (addr_expr_ref > 0 && addr_expr_ref <= arena.num_exprs) {
          line = pipeline_expr_line_at(arena, addr_expr_ref);
          col = pipeline_expr_col_at(arena, addr_expr_ref);
        }
        driver_diagnostic_typeck_linear_addr_of(line, col);
        return 0 - 1;
      }
    }
    func_ix = ctx.current_func_index;
    if (func_ix >= 0 && func_ix < module.num_funcs) {
      pr = pipeline_module_func_param_type_ref_for_name(module, func_ix, &vbuf[0], vnlen);
      if (pr > 0 && pipeline_type_kind_ord_at(arena, pr) == ord_linear) {
        line = 0;
        col = 0;
        if (addr_expr_ref > 0 && addr_expr_ref <= arena.num_exprs) {
          line = pipeline_expr_line_at(arena, addr_expr_ref);
          col = pipeline_expr_col_at(arena, addr_expr_ref);
        }
        driver_diagnostic_typeck_linear_addr_of(line, col);
        return 0 - 1;
      }
    }
    return 0;
  }
}

/**
 * Cap residual face: tail expr ref for implicit-return rule (thin → pure).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_func_body_tail_expr_ref_for_implicit_rule_c(arena: *ASTArena,
body_ref: i32): i32 {
  return func_body_tail_expr_ref_for_implicit_rule(arena, body_ref);
}

/**
 * Cap residual face: has_implicit_return_tail (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_func_body_has_implicit_return_tail_c(arena: *ASTArena,
body_ref: i32): i32 {
  if (func_body_has_implicit_return_tail(arena, body_ref)) {
    return 1;
  }
  return 0;
}

// end wave259 pure-owned leave

// ---------------------------------------------------------------------------
// wave260: typeck method_call Cap residual pure-owned leave (host-cc present 51→50)
// Delete pipeline_typeck_method_call.c from pipeline_x mega-TU.
// Cap faces sole on typeck_x.o (#[no_mangle]):
//   method_call_c / expr_apply_call_resolve_c / import_segment_at_c /
//   resolve_dep_index_for_import_c / resolve_whole_import_call_ret_c
// Call-resolve + METHOD_CALL field accessors completed in ast_pool_expr_sidecar
//   (G.7 有则补全; same-TU via ast_pool). Dead statics retired with residual:
//   debug_try_propagate_report_glue_c / bootstrap_expr_fixup_c (no live callers).
// Dual-export ban: no second Cap body on pipeline_x.
// PLATFORM: SHARED freestanding typeck method_call Cap leave.
// ---------------------------------------------------------------------------

/**
 * Cap residual face: EXPR_METHOD_CALL typeck (thin → pure authority).
 * PLATFORM: SHARED freestanding typeck method_call Cap leave.
 */
#[no_mangle]
export function pipeline_typeck_check_expr_method_call_c(module: *Module, arena: *ASTArena,
expr_ref: i32, return_type_ref: i32, ctx: *PipelineDepCtx): i32 {
  return typeck_check_expr_method_call(module, arena, expr_ref, return_type_ref, ctx);
}

/**
 * Cap residual face: write CALL resolve slots (thin → pipeline_expr_apply_call_resolve).
 * PLATFORM: SHARED freestanding typeck.
 */
#[no_mangle]
export function pipeline_typeck_expr_apply_call_resolve_c(arena: *ASTArena, call_expr_ref: i32,
dep_ix: i32, func_ix: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate (wave314).
  unsafe {
    pipeline_expr_apply_call_resolve(arena, call_expr_ref, dep_ix, func_ix);
  }
}

/**
 * Cap residual face: import path segment at want_seg (thin → pure; bool as i32).
 * PLATFORM: SHARED freestanding typeck import resolve.
 */
#[no_mangle]
export function pipeline_typeck_import_segment_at_c(module: *Module, imp_ix: i32, want_seg: i32,
ostr: *i32, olen: *i32): i32 {
  if (typeck_import_segment_at(module, imp_ix, want_seg, ostr, olen)) {
    return 1;
  }
  return 0;
}

/**
 * Cap residual face: entry import slot → dep ctx slot (thin → pure).
 * PLATFORM: SHARED freestanding typeck import resolve.
 */
#[no_mangle]
export function pipeline_typeck_resolve_dep_index_for_import_c(module: *Module, ctx: *PipelineDepCtx,
imp_ix: i32): i32 {
  return typeck_resolve_dep_index_for_import(module, ctx, imp_ix);
}

/**
 * Cap residual face: qualified whole-import CALL return type (thin → pure).
 * PLATFORM: SHARED freestanding typeck import resolve.
 */
#[no_mangle]
export function pipeline_typeck_resolve_whole_import_call_ret_c(module: *Module, arena: *ASTArena,
callee_expr_ref: i32, ctx: *PipelineDepCtx, dep_index_out: *i32, func_index_out: *i32): i32 {
  return resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx,
  dep_index_out, func_index_out);
}

// end wave260 pure-owned leave
