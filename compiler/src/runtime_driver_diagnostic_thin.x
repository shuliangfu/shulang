// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// G-02f-339..341/409/416 + Cap residual pure deep-migrate
// (parse_fail / codegen_fail / typeck residual + skip/commit_fail/warn/hint/generic/param/import
//  + binop + commit_shape wave3 + after_entry_module + emit_func_fail wave4):
// runtime_driver_diagnostic R2 thin.
// Product PREFER_X_O: g05_try_x_to_o -> thin.o + seeds/runtime_driver_diagnostic.from_x.c rest
//   (-DXLANG_L2_RDD_THIN_FROM_X) ld -r -> src/runtime_driver_diagnostic.o
// Pure bodies: fixed-msg typeck + pipe orch + assemble pure + append_* + env pure
//   + parse_fail (XP001) + codegen_fail note + typeck_func_fail (XT001)
//   + typeck_ptr_field / typeck_ret_fail debug notes (getenv gate + append+note)
//   + parse_skip / parse_commit_fail (XP002) / parse_func_generic / parser_onefunc_param_ref
//   + typeck_import_const_must_be_qualified / warn_pad / warn_hot / hint_unused (append; no va_list)
//   + typeck_binop_operands / parse_commit_shape / parser_diagnostic_parse_commit_shape (wave3)
//   + parse_commit_pre/post gather→shape (wave302; left strict_minimal dual-export)
//   + after_entry_parse_module / codegen_emit_func_fail (wave4; pipeline API + append; no va_list).
//   + asm BSS store/set/trace/print/var/fail_at (wave5; module BSS + append+note; no va_list).
//   + wave6: slice_marker pure; lsp_diag_get_enabled is G.7 extern (runtime_lsp_glue owner);
//     FROM_X rest drops dead va_list report_x (pure XP001/XP002 cover callers) → rest T=0.
// This TU: thin gates + pure bodies (f-339..341 + f-387 env + f-409 pipe + wave5 + wave6)

/* wave228 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl. */
export extern "C" function link_abi_getenv(name: *u8): *u8;

// Authority for driver_env_flag_truthy is runtime_driver_abi_thin.x (G.7 single implementation).
// Extern declaration only here to avoid duplicate global symbols across .o files.
extern function driver_env_flag_truthy(name: *u8): i32;

// Pipeline module read APIs (authoritative in pipeline_glue / ast_pool — G.7; not reimplemented here).
// Used by pure after_entry_parse_module + codegen_emit_func_fail (wave4).
export extern "C" function pipeline_module_num_funcs(module: *u8): i32;
export extern "C" function pipeline_module_func_is_extern_at(module: *u8, fi: i32): i32;
export extern "C" function pipeline_module_func_name_len_at(module: *u8, fi: i32): i32;
export extern "C" function pipeline_module_func_name_byte_at(module: *u8, fi: i32, bi: i32): u8;

// wave302 G.7: parse_commit_pre/post pool+block metric faces — Cap on pipeline/ast_pool
// (not reimplemented here). Thin only gathers counts then calls commit_shape.
// PLATFORM: SHARED freestanding parse-commit gather.
export extern "C" function pipeline_onefunc_num_consts(pool: *u8): i32;
export extern "C" function pipeline_onefunc_num_lets(pool: *u8): i32;
export extern "C" function pipeline_onefunc_num_if_stmts(pool: *u8): i32;
export extern "C" function pipeline_onefunc_num_regions(pool: *u8): i32;
export extern "C" function pipeline_onefunc_num_src_stmt_order(pool: *u8): i32;
export extern "C" function ast_ast_block_num_consts(arena: *u8, block_ref: i32): i32;
export extern "C" function ast_ast_block_num_lets(arena: *u8, block_ref: i32): i32;
export extern "C" function ast_ast_block_num_if_stmts(arena: *u8, block_ref: i32): i32;
export extern "C" function ast_ast_block_num_regions(arena: *u8, block_ref: i32): i32;
export extern "C" function ast_ast_block_num_stmt_order(arena: *u8, block_ref: i32): i32;
export extern "C" function ast_ast_block_final_expr_ref(arena: *u8, block_ref: i32): i32;

// pure bodies for parse_fail / skip / commit_fail / warn / hint / generic / param / import /
// binop / commit_shape / after_entry_module / emit_func_fail / asm BSS are after append_* helpers.

// pure: typeck_block/fn/var debug below (getenv gate + append+note); thin gate removed.
// pure: typeck_binop_operands / parse_commit_shape / parser_diagnostic_parse_commit_shape (wave3).
// pure: after_entry_parse_module / codegen_emit_func_fail (wave4).
// pure: asm BSS + print/var/fail_at/trace (wave5).
// pure: slice_marker (wave6); lsp_diag_get_enabled is extern C (G.7 glue owner).

// pure:driver_diagnostic_codegen_fail defined after append_* helpers.

// G.7: flag + getter live in runtime_lsp_glue / lsp_diag_stubs_no_c (not this residual rest).
export extern "C" function lsp_diag_get_enabled(): i32;

// ---- Wave5 Cap residual pure: asm backend diagnostic BSS (PLATFORM: SHARED) ----
// Authority lives in this thin TU under PREFER hybrid; cold seed keeps C static BSS.
// last_expr_kind starts at -1 (unset), matching cold seed semantics.
let g_asm_last_expr_kind: i32 = -1;
// Current function name buffer for fail_at / var_not_found / print notes (cap 64 usable).
let g_asm_current_func: u8[72] = [];
let g_asm_current_func_len: i32 = 0;

// pure: debug_log / parser_diag_* / warn / hint below (append+note; thin gate removed).

// ---- G-02f-340 pure full bodies ----
export extern "C" function driver_check_only_get(): i32;
export extern "C" function driver_check_diag_emitted_get(): i32;

/** Exported function `driver_diagnostic_entry_already`.
 * Read path helper `driver_diagnostic_entry_already`.
 * @param v i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_entry_already(v: i32): void {
}

/** Exported function `driver_diagnostic_after_dep_codegen`.
 * Implements `driver_diagnostic_after_dep_codegen`.
 * @param j i32
 * @param out_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_after_dep_codegen(j: i32, out_len: i32): void {
}

/** Exported function `driver_diagnostic_typeck_fail`.
 * Implements `driver_diagnostic_typeck_fail`.
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_fail(): void {
  unsafe {
    let _a: i32 = driver_check_only_get();
    let _b: i32 = driver_check_diag_emitted_get();
  }
}

// Wave5 pure asm BSS consumers are defined after append_* + driver_diag_note (below).

/** Exported function `driver_diag_append_cstr`.
 * Implements `driver_diag_append_cstr`.
 * @param dst *u8
 * @param cap i32
 * @param at i32
 * @param src *u8
 * @return i32
 */
#[no_mangle]
export function driver_diag_append_cstr(dst: *u8, cap: i32, at: i32, src: *u8): i32 {
  if (dst == 0) { return at; }
  if (src == 0) { return at; }
  let j: i32 = at;
  let i: i32 = 0;
  while (j + 1 < cap) {
    let c: u8 = src[i];
    if (c == 0) { break; }
    dst[j] = c;
    j = j + 1;
    i = i + 1;
  }
  dst[j] = 0;
  return j;
}

/** Exported function `driver_diag_append_name`.
 * Implements `driver_diag_append_name`.
 * @param dst *u8
 * @param cap i32
 * @param at i32
 * @param name *u8
 * @param name_len i32
 * @return i32
 */
#[no_mangle]
export function driver_diag_append_name(dst: *u8, cap: i32, at: i32, name: *u8, name_len: i32): i32 {
  if (name == 0) { return at; }
  if (name_len <= 0) { return at; }
  let n: i32 = 0;
  while (n < name_len) {
    if (at + 1 >= cap) { break; }
    dst[at] = name[n];
    at = at + 1;
    n = n + 1;
  }
  dst[at] = 0;
  return at;
}

/** Exported function `driver_diag_append_i32`.
 * Implements `driver_diag_append_i32`.
 * @param dst *u8
 * @param cap i32
 * @param at i32
 * @param val i32
 * @return i32
 */
#[no_mangle]
export function driver_diag_append_i32(dst: *u8, cap: i32, at: i32, val: i32): i32 {
  if (dst == 0) { return at; }
  if (at + 1 >= cap) { return at; }
  let v: i32 = val;
  if (v < 0) {
    dst[at] = 45;
    at = at + 1;
    v = 0 - v;
  }
  let d0: i32 = 0;
  let d1: i32 = 0;
  let d2: i32 = 0;
  let d3: i32 = 0;
  let d4: i32 = 0;
  let d5: i32 = 0;
  let d6: i32 = 0;
  let d7: i32 = 0;
  let d8: i32 = 0;
  let d9: i32 = 0;
  let dn: i32 = 0;
  if (v == 0) {
    d0 = 0;
    dn = 1;
  } else {
    let t: i32 = v;
    while (t > 0) {
      if (dn >= 10) { break; }
      let dig: i32 = t % 10;
      if (dn == 0) { d0 = dig; }
      if (dn == 1) { d1 = dig; }
      if (dn == 2) { d2 = dig; }
      if (dn == 3) { d3 = dig; }
      if (dn == 4) { d4 = dig; }
      if (dn == 5) { d5 = dig; }
      if (dn == 6) { d6 = dig; }
      if (dn == 7) { d7 = dig; }
      if (dn == 8) { d8 = dig; }
      if (dn == 9) { d9 = dig; }
      t = t / 10;
      dn = dn + 1;
    }
  }
  let i: i32 = dn - 1;
  while (i >= 0) {
    if (at + 1 >= cap) { break; }
    let dig: i32 = 0;
    if (i == 0) { dig = d0; }
    if (i == 1) { dig = d1; }
    if (i == 2) { dig = d2; }
    if (i == 3) { dig = d3; }
    if (i == 4) { dig = d4; }
    if (i == 5) { dig = d5; }
    if (i == 6) { dig = d6; }
    if (i == 7) { dig = d7; }
    if (i == 8) { dig = d8; }
    if (i == 9) { dig = d9; }
    dst[at] = (dig + 48) as u8;
    at = at + 1;
    i = i - 1;
  }
  dst[at] = 0;
  return at;
}




/** Exported function `driver_diag_copy_bytes`.
 * Implements `driver_diag_copy_bytes`.
 * @param dst *u8
 * @param dst_size i64
 * @param src *u8
 * @param src_len i32
 * @return i32
 */
#[no_mangle]
export function driver_diag_copy_bytes(dst: *u8, dst_size: i64, src: *u8, src_len: i32): i32 {
  if (dst == 0) { return 0; }
  if (dst_size == 0) { return 0; }
  let n: i32 = 0;
  if (src != 0) {
    if (src_len > 0) {
      while (n < src_len) {
        if ((n as i64) + 1 >= dst_size) { break; }
        dst[n] = src[n];
        n = n + 1;
      }
    }
  }
  dst[n] = 0;
  return n;
}

// ---- Cap residual pure deep-migrate: fixed-msg typeck + pipe orch (body; FROM_X no pure-dup _impl) ----
export extern "C" function lsp_diag_report_typeck(line: i32, col: i32, msg: *u8): void;
// pure: XLANG_DEBUG_PIPE truthy (getenv non-empty and != '0'); FROM_X no pure-dup _impl

/** Exported function `driver_diag_env_debug_pipe`.
 * Implements `driver_diag_env_debug_pipe`.
 * @return i32
 */
#[no_mangle]
export function driver_diag_env_debug_pipe(): i32 {
  // PLATFORM: SHARED - LANG-007 S0: is_extern calls require unsafe (align tests/unsafe U4).
  unsafe {
    return driver_env_flag_truthy("XLANG_DEBUG_PIPE");
  }
}

/** Exported function `driver_diagnostic_before_codegen`.
 * Implements `driver_diagnostic_before_codegen`.
 * @param num_funcs i32
 * @param out_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_before_codegen(num_funcs: i32, out_len: i32): void {
  unsafe {
    if (driver_diag_env_debug_pipe() != 0) {
      driver_diag_pipe_note(0, num_funcs, out_len);
    }
  }
}

/** Exported function `driver_diagnostic_source_len`.
 * Query helper `driver_diagnostic_source_len`.
 * @param len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_source_len(len: i32): void {
  unsafe {
    if (driver_diag_env_debug_pipe() != 0) {
      driver_diag_pipe_note(1, len, 0);
    }
  }
}

/** Exported function `driver_diagnostic_after_entry_parse`.
 * Implements `driver_diagnostic_after_entry_parse`.
 * @param num_funcs i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_after_entry_parse(num_funcs: i32): void {
  unsafe {
    if (driver_diag_env_debug_pipe() != 0) {
      driver_diag_pipe_note(2, num_funcs, 0);
    }
  }
}

/** Exported function `driver_diagnostic_pipe_marker`.
 * Implements `driver_diagnostic_pipe_marker`.
 * @param id i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_pipe_marker(id: i32): void {
  unsafe {
    if (driver_diag_env_debug_pipe() != 0) {
      driver_diag_pipe_note(3, id, 0);
    }
  }
}

/** Exported function `driver_diagnostic_typeck_if_condition_not_bool`.
 * Implements `driver_diagnostic_typeck_if_condition_not_bool`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_if_condition_not_bool(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "if condition must be bool (no implicit int-to-bool)");
  }
}

/** Exported function `driver_diagnostic_typeck_while_condition_not_bool`.
 * Implements `driver_diagnostic_typeck_while_condition_not_bool`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_while_condition_not_bool(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "while condition must be bool (no implicit int-to-bool)");
  }
}

/** Exported function `driver_diagnostic_typeck_for_condition_not_bool`.
 * Implements `driver_diagnostic_typeck_for_condition_not_bool`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_for_condition_not_bool(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "for condition must be bool (no implicit int-to-bool)");
  }
}

/** Exported function `driver_diagnostic_typeck_deref_outside_unsafe`.
 * Implements `driver_diagnostic_typeck_deref_outside_unsafe`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_deref_outside_unsafe(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "pointer dereference requires unsafe block");
  }
}

/** Exported function `driver_diagnostic_typeck_extern_call_outside_unsafe`.
 * Implements `driver_diagnostic_typeck_extern_call_outside_unsafe`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_extern_call_outside_unsafe(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "extern call requires unsafe block");
  }
}

/** Exported function `driver_diagnostic_typeck_linear_addr_of`.
 * Implements `driver_diagnostic_typeck_linear_addr_of`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_linear_addr_of(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "cannot take address of linear value");
  }
}

/** Exported function `driver_diagnostic_typeck_subscript_base`.
 * Implements `driver_diagnostic_typeck_subscript_base`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_subscript_base(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "subscript base must be array, slice or pointer");
  }
}

/** Exported function `driver_diagnostic_typeck_enum_no_variant`.
 * Implements `driver_diagnostic_typeck_enum_no_variant`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_enum_no_variant(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "enum has no variant");
  }
}

/** Exported function `driver_diagnostic_typeck_try_propagate_bad_enclosing`.
 * Implements `driver_diagnostic_typeck_try_propagate_bad_enclosing`.
 * @param line i32
 * @param col i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_try_propagate_bad_enclosing(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
                           "`?` requires the enclosing function to return the same Result type");
  }
}

/** Exported function `driver_diagnostic_typeck_break_continue_outside`.
 * Implements `driver_diagnostic_typeck_break_continue_outside`.
 * @param line i32
 * @param col i32
 * @param is_break i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_break_continue_outside(line: i32, col: i32, is_break: i32): void {
  unsafe {
    if (is_break != 0) {
      lsp_diag_report_typeck(line, col, "break only allowed inside a loop");
    } else {
      lsp_diag_report_typeck(line, col, "continue only allowed inside a loop");
    }
  }
}

/**
 * Report illegal pointer arithmetic (wave285 Cap residual pure leaf).
 * Closes soft residual: typeck accepted ptr+ptr / ptr*ptr via type_refs_equal, then
 * host-cc failed as BLD001. Product path hard-fails at typeck with a clear message.
 * @param line i32 — 1-based source line of the binop
 * @param col i32 — 1-based source column of the binop
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_ptr_binop(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col, "invalid pointer arithmetic (ptr+ptr / non-offset ops)");
  }
}

/**
 * Report illegal float bitwise/mod/shift/unary~ (wave286 + wave289 Cap residual pure leaf).
 * Closes soft residual: typeck promoted f32/f64 for & | ^ << >> % / ~ then host-cc BLD001.
 * @param line i32 — 1-based source line of the op
 * @param col i32 — 1-based source column of the op
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_float_binop(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "invalid float op (no bitwise/mod/shift/unary ~ on f32/f64; use + - * / and unary -)");
  }
}

/**
 * Report illegal aggregate binop (wave657 cmp + wave658 arith Cap residual).
 * Closes soft residual: typeck stamped bool/result for struct/slice/array cmp or arith
 * → host-cc BLD001 or silent array pointer-identity false green.
 * @param line i32 — 1-based source line of the binop
 * @param col i32 — 1-based source column of the binop
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_aggregate_cmp(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "invalid aggregate operation (cmp/arith/unary -/~/! not allowed on array/slice/struct; use scalars or fields)");
  }
}

/**
 * Report illegal `as` cast (wave659 Cap residual pure leaf).
 * Closes soft residual: typeck stamped cast target for aggregate/float↔ptr false green/BLD001.
 * @param line i32 — 1-based source line of the cast
 * @param col i32 — 1-based source column of the cast
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_as_cast(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "invalid cast (as not allowed for aggregate or float<->pointer; use numeric/ptr casts or fields)");
  }
}

/**
 * Report free-function call arity mismatch (wave660 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the CALL
 * @param col i32 — 1-based source column of the CALL
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_arity_mismatch(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "wrong number of arguments in function call (arity mismatch)");
  }
}

/**
 * Report free-function call argument type mismatch (wave661 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the CALL
 * @param col i32 — 1-based source column of the CALL
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_arg_type_mismatch(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "argument type mismatch in function call");
  }
}

/**
 * Report unresolved free-function CALL (wave675 Cap residual pure leaf).
 * Closes soft residual: bare VAR callee with no module name hit left typeck OK → host BLD001
 * undeclared function (also covers silent parse-drop of bad formals + call).
 * @param line i32 — 1-based source line of the CALL
 * @param col i32 — 1-based source column of the CALL
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_unresolved(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "unresolved function call (no matching function)");
  }
}

/**
 * Report non-integer array/slice/pointer subscript index (wave664 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the INDEX
 * @param col i32 — 1-based source column of the INDEX
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_subscript_index(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "subscript index must be an integer type");
  }
}

/**
 * Report non-bool operand of && / || / ! (wave665 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the logical expr
 * @param col i32 — 1-based source column of the logical expr
 * @return void
 * PLATFORM: SHARED — seed cold twin under #ifndef XLANG_L2_RDD_THIN_FROM_X same commit.
 */
#[no_mangle]
export function driver_diagnostic_typeck_logical_operand_not_bool(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "logical operand must be bool (no implicit int-to-bool)");
  }
}

/**
 * Report incompatible comparison operand types (wave666 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the comparison
 * @param col i32 — 1-based source column of the comparison
 * @return void
 * PLATFORM: SHARED — G.7 ≡ runtime_driver_diagnostic.x.
 */
#[no_mangle]
export function driver_diagnostic_typeck_comparison_type_mismatch(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "comparison operands have incompatible types");
  }
}

/**
 * Report void used in arithmetic or unary -/~ (wave667 Cap residual pure leaf).
 * @param line i32 — 1-based source line of the op
 * @param col i32 — 1-based source column of the op
 * @return void
 * PLATFORM: SHARED — G.7 ≡ runtime_driver_diagnostic.x.
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_void_binop(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "invalid void operation (void cannot be used in arithmetic or unary -/~)");
  }
}

/**
 * Report bool used in arithmetic / bitops / shifts or unary -/~ (wave677 Cap residual).
 * @param line i32 — 1-based source line of the op
 * @param col i32 — 1-based source column of the op
 * @return void
 * PLATFORM: SHARED — G.7 ≡ runtime_driver_diagnostic.x.
 * LANG-006 scalar let/const bool→int remains allowed; this rejects bool as an
 * arithmetic/bit operand (true+false, x<<true, -true, ~true, true&false).
 */
#[no_mangle]
export function driver_diagnostic_typeck_invalid_bool_binop(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "invalid bool operation (bool cannot be used in arithmetic, bitops, shifts, or unary -/~; use logical ops or `as`)");
  }
}

/**
 * Report assignment / compound-assign to a const binding (wave678 Cap residual).
 * @param line i32 — 1-based source line of the assign
 * @param col i32 — 1-based source column of the assign
 * @return void
 * PLATFORM: SHARED — G.7 ≡ runtime_driver_diagnostic.x.
 * docs/06: const bindings are immutable; let remains reassignable (mut is spelling only).
 */
#[no_mangle]
export function driver_diagnostic_typeck_assign_to_const(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "cannot assign to const binding (const is immutable; use let for a mutable variable)");
  }
}

/**
 * Report same-block let/const redecl or function-body param name clash (wave680 Cap residual).
 * @param line i32 — 1-based source line of the second declaration
 * @param col i32 — 1-based source column of the second declaration
 * @return void
 * PLATFORM: SHARED — G.7 ≡ runtime_driver_diagnostic.x.
 * Nested-block shadowing remains allowed; only same block / param+body local conflict.
 */
#[no_mangle]
export function driver_diagnostic_typeck_duplicate_local(line: i32, col: i32): void {
  unsafe {
    lsp_diag_report_typeck(line, col,
      "duplicate let/const binding (same-block local, parameter clash, or module-scope redecl)");
  }
}

// ---- G-02f-341 pure helpers / remaining gates ----

/** Exported function `parser_is_ident_allow`.
 * Implements `parser_is_ident_allow`.
 * @param ident *u8
 * @param len i32
 * @return i32
 */
#[no_mangle]
export function parser_is_ident_allow(ident: *u8, len: i32): i32 {
  if (ident == 0) { return 0; }
  if (len != 5) { return 0; }
  if (ident[0] == 97 && ident[1] == 108 && ident[2] == 108 && ident[3] == 111 && ident[4] == 119) {
    return 1;
  }
  return 0;
}

// ---- Cap residual pure deep-migrate: assemble pure (return/assign/call/struct/asm note + fill/build) ----
// Same authority as full.x G-02f-175..179; append_* pure; scratch expect/found small BSS pure
// pure: XLANG_PARSE_STRICT truthy + report_prefixed + pipe_note; FROM_X no pure-dup _impl
// pure (prior): parse_fail XP001 / codegen_fail note / typeck_func_fail XT001 /
//   typeck_ptr_field + typeck_ret_fail debug notes (no va_list / snprintf)
// pure (this wave): parse_skip / parse_commit_fail XP002 / parse_func_generic /
//   parser_onefunc_param_ref / typeck_import_const / warn_pad / warn_hot / hint_unused
export extern "C" function diag_report(file: *u8, line: i32, col: i32, kind: *u8, msg: *u8, detail: *u8): void;
export extern "C" function diag_report_with_code(file: *u8, line: i32, col: i32, kind: *u8, code: *u8, msg: *u8, detail: *u8): void;
export extern "C" function lsp_diag_add(line: i32, col: i32, severity: i32, msg: *u8): void;
export extern "C" function lsp_diag_add_code(line: i32, col: i32, severity: i32, code: *u8, msg: *u8): void;
export extern "C" function driver_check_diag_emitted_note(): void;

/** Emit XP001 when .x parse fails: assemble fixed message via append_cstr/append_i32
 * (no va_list / snprintf). Params: main_idx, num_funcs, arena_num_types for diagnostics.
 * Side effects: lsp_diag_add_code when LSP collect enabled; else check-only note +
 * diag_report_with_code("pipeline error","XP001",msg). Message text must match cold seed.
 * PLATFORM: SHARED — pure authority in thin.x; rest drops pure-dup _impl under FROM_X. */
#[no_mangle]
export function driver_diagnostic_parse_fail(main_idx: i32, num_funcs: i32, arena_num_types: i32): void {
  unsafe {
    let msg: u8[256] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 256, 0, ".x parse failed (main_idx=");
    at = driver_diag_append_i32(&msg[0], 256, at, main_idx);
    at = driver_diag_append_cstr(&msg[0], 256, at, ", num_funcs=");
    at = driver_diag_append_i32(&msg[0], 256, at, num_funcs);
    at = driver_diag_append_cstr(&msg[0], 256, at, ", arena_num_types=");
    at = driver_diag_append_i32(&msg[0], 256, at, arena_num_types);
    at = driver_diag_append_cstr(&msg[0], 256, at, ")");
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add_code(1, 1, 1, "XP001", &msg[0]);
      return;
    }
    if (driver_check_only_get() != 0) {
      driver_check_diag_emitted_note();
    }
    diag_report_with_code(0 as *u8, 0, 0, "pipeline error", "XP001", &msg[0], 0 as *u8);
  }
}

/** Emit a codegen-fail note: which dep (is_dep!=0 → dependency emission) or entry module
 * (is_dep==0), plus dep_index. Assembles via append_cstr/append_i32 then driver_diag_note;
 * no va_list diag_reportf. PLATFORM: SHARED — pure in thin; cold seed keeps C body. */
#[no_mangle]
export function driver_diagnostic_codegen_fail(dep_index: i32, is_dep: i32): void {
  let msg: u8[160] = [];
  let at: i32 = 0;
  if (is_dep != 0) {
    at = driver_diag_append_cstr(&msg[0], 160, 0, "codegen failed at dependency emission (dep_index=");
  } else {
    at = driver_diag_append_cstr(&msg[0], 160, 0, "codegen failed at entry module emission (dep_index=");
  }
  at = driver_diag_append_i32(&msg[0], 160, at, dep_index);
  at = driver_diag_append_cstr(&msg[0], 160, at, ")");
  driver_diag_note(&msg[0]);
}

/** Soft-suppress flag set by pipeline_typeck_dep_prerun_module_c during exploratory full typeck. */
export extern "C" function pipeline_typeck_diag_soft_suppress_get(): i32;

/** Emit XT001 when typeck fails in a function. Params: func_idx; name[0..name_len) capped
 * at 64 bytes (or "(unknown)"); kind==-6 → "implicit tail return", else "check_block failed".
 * Path: append assemble → lsp_diag_add_code if LSP; else check note + diag_report_with_code
 * ("typeck error","XT001") and optional prefixed hint for kind -6. No va_list reportf.
 * PLATFORM: SHARED — pure authority in thin.x; FROM_X rest no pure-dup _impl.
 * Soft-suppress: dep prerun full typeck may fail then light-fallback; do not spam XT001. */
#[no_mangle]
export function driver_diagnostic_typeck_func_fail(func_idx: i32, name: *u8, name_len: i32, kind: i32): void {
  unsafe {
    if (pipeline_typeck_diag_soft_suppress_get() != 0) {
      return;
    }
    let msg: u8[240] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, ".x type check failed in function #");
    at = driver_diag_append_i32(&msg[0], 240, at, func_idx);
    at = driver_diag_append_cstr(&msg[0], 240, at, " ");
    if (name != 0 as *u8 && name_len > 0) {
      let nl: i32 = name_len;
      if (nl > 64) {
        nl = 64;
      }
      at = driver_diag_append_name(&msg[0], 240, at, name, nl);
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "(unknown)");
    }
    at = driver_diag_append_cstr(&msg[0], 240, at, " (");
    if (kind == 0 - 6) {
      at = driver_diag_append_cstr(&msg[0], 240, at, "implicit tail return");
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "check_block failed");
    }
    at = driver_diag_append_cstr(&msg[0], 240, at, ")");
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add_code(1, 1, 1, "XT001", &msg[0]);
      return;
    }
    driver_check_diag_emitted_note();
    diag_report_with_code(0 as *u8, 0, 0, "typeck error", "XT001", &msg[0], 0 as *u8);
    if (kind == 0 - 6) {
      driver_diag_report_prefixed(0, 0,
        "typeck error: return value must use explicit return statement (e.g. return 0;)");
    }
  }
}

/** Optional FIELD_ACCESS debug note when link_abi_getenv("XLANG_TYPECK_PTR") is set. Prints bt_kind,
 * inner_kind, inner_nlen, base_resolved_ref, num_struct_layouts via append+driver_diag_note.
 * No-op if env unset. No va_list. PLATFORM: SHARED — pure in thin; cold seed keeps C body. */
#[no_mangle]
export function driver_diagnostic_typeck_ptr_field(bt_kind: i32, inner_kind: i32, inner_nlen: i32, base_resolved_ref: i32, num_struct_layouts: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_PTR") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "typeck ptr debug: FIELD_ACCESS bt_kind=");
  at = driver_diag_append_i32(&msg[0], 240, at, bt_kind);
  at = driver_diag_append_cstr(&msg[0], 240, at, " inner_kind=");
  at = driver_diag_append_i32(&msg[0], 240, at, inner_kind);
  at = driver_diag_append_cstr(&msg[0], 240, at, " inner_nlen=");
  at = driver_diag_append_i32(&msg[0], 240, at, inner_nlen);
  at = driver_diag_append_cstr(&msg[0], 240, at, " base_resolved_ref=");
  at = driver_diag_append_i32(&msg[0], 240, at, base_resolved_ref);
  at = driver_diag_append_cstr(&msg[0], 240, at, " num_struct_layouts=");
  at = driver_diag_append_i32(&msg[0], 240, at, num_struct_layouts);
  driver_diag_note(&msg[0]);
}

/** Optional EXPR_RETURN debug note when link_abi_getenv("XLANG_TYPECK_RET") is set. Prints stage,
 * op_expr_ref, expect_ty_ref, got_ty_ref via append+driver_diag_note. No-op if env unset.
 * stage 1 = operand check fail; 2 = got vs expect mismatch. No va_list.
 * PLATFORM: SHARED — pure in thin; cold seed keeps C body. */
#[no_mangle]
export function driver_diagnostic_typeck_ret_fail(stage: i32, op_expr_ref: i32, expect_ty_ref: i32, got_ty_ref: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_RET") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[200] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 200, 0, "typeck return debug: stage=");
  at = driver_diag_append_i32(&msg[0], 200, at, stage);
  at = driver_diag_append_cstr(&msg[0], 200, at, " op_expr_ref=");
  at = driver_diag_append_i32(&msg[0], 200, at, op_expr_ref);
  at = driver_diag_append_cstr(&msg[0], 200, at, " expect_ty_ref=");
  at = driver_diag_append_i32(&msg[0], 200, at, expect_ty_ref);
  at = driver_diag_append_cstr(&msg[0], 200, at, " got_ty_ref=");
  at = driver_diag_append_i32(&msg[0], 200, at, got_ty_ref);
  driver_diag_note(&msg[0]);
}

// pure: assignment-diag dual scratch buffers (96B; seed width; single-thread pipeline)
let g_type_diag_scratch_expect: u8[96] = [];
let g_type_diag_scratch_found: u8[96] = [];

/**
 * Whether parse_into_buf must hard-fail (and emit skip diags) instead of
 * silently soft-skipping a failed top-level function / unexpected token.
 *
 * True when:
 * - `XLANG_PARSE_STRICT` is truthy, or
 * - `driver_check_only_get()` is set (`xlang check` path).
 *
 * Why check_only is included (2026-08-05 root fix): without this, parse_into_buf
 * soft-skipped bad `function` bodies, returned empty-module success (pr.ok=0),
 * recovery found nothing, and `xlang check` exited 0 on obvious syntax errors
 * while typeck errors still worked. Header contract already said PARSE_STRICT
 * returns -2 on single-function failure; check is the product syntax gate and
 * must imply the same strictness.
 *
 * @return i32 — 1 strict, 0 soft-skip allowed (compile path default)
 * PLATFORM: SHARED — dual-host check matrix after change.
 */
#[no_mangle]
export function driver_parse_strict_enabled(): i32 {
  // PLATFORM: SHARED — check_only OR env; see analysis / check false-green.
  unsafe {
    if (driver_check_only_get() != 0) {
      return 1;
    }
    return driver_env_flag_truthy("XLANG_PARSE_STRICT");
  }
}

// pure: after assemble, emit via diag_report note (no va_list reportf)
/** Exported function `driver_diag_note`.
 * Implements `driver_diag_note`.
 * @param msg *u8
 * @return void
 */
#[no_mangle]
export function driver_diag_note(msg: *u8): void {
  unsafe {
    let m: *u8 = msg;
    if (m == 0) { m = ""; }
    diag_report(0 as *u8, 0, 0, "note", m, 0 as *u8);
  }
}

// ---- Wave5 Cap residual pure: asm BSS consumers (append/note available) ----

/** Record last ExprKind ordinal seen by asm backend (for fail_at notes).
 * PLATFORM: SHARED — pure module BSS in thin; cold seed keeps C static. */
#[no_mangle]
export function driver_diagnostic_asm_last_expr_kind_set(k: i32): void {
  g_asm_last_expr_kind = k;
}

/** Alias of last_expr_kind_set (historical dual surface; zero-logic, G.7 single store). */
#[no_mangle]
export function driver_diagnostic_asm_set_last_expr_kind(k: i32): void {
  g_asm_last_expr_kind = k;
}

/** Store current asm codegen function name into module BSS for later notes.
 * Caps usable length to 64 (buffer size 72). Null or empty name clears length.
 * PLATFORM: SHARED — pure in thin; FROM_X rest has no BSS _impl. */
#[no_mangle]
export function driver_diagnostic_asm_current_func_store(name: *u8, len: i32): void {
  let n: i32 = 0;
  if (len > 0) {
    if (len <= 64) {
      n = len;
    }
  }
  g_asm_current_func_len = n;
  if (name != 0 as *u8) {
    if (n > 0) {
      let i: i32 = 0;
      while (i < n) {
        g_asm_current_func[i] = name[i];
        i = i + 1;
      }
    }
  }
}

/** If XLANG_ASM_FUNC_TRACE is truthy and a current func name is stored, emit a note.
 * Uses driver_env_flag_truthy (G.7 abi authority) + append+note (no va_list reportf).
 * PLATFORM: SHARED — pure in thin. */
#[no_mangle]
export function driver_diagnostic_asm_current_func_maybe_trace(): void {
  // PLATFORM: SHARED — LANG-007 S0: extern driver_env_flag_truthy requires unsafe.
  unsafe {
    if (driver_env_flag_truthy("XLANG_ASM_FUNC_TRACE") == 0) {
      return;
    }
  }
  if (g_asm_current_func_len <= 0) {
    return;
  }
  let msg: u8[160] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 160, 0, "asm trace: ");
  at = driver_diag_append_name(&msg[0], 160, at, &g_asm_current_func[0], g_asm_current_func_len);
  driver_diag_note(&msg[0]);
}

/** Store name then maybe_trace (historical set_current_func surface; composes pure authorities). */
#[no_mangle]
export function driver_diagnostic_asm_set_current_func(name: *u8, len: i32): void {
  driver_diagnostic_asm_current_func_store(name, len);
  driver_diagnostic_asm_current_func_maybe_trace();
}

/** Note which function failed during asm codegen (XLANG_ASM_DEBUG paths).
 * Assembles fixed prefix + stored name via append; no va_list. PLATFORM: SHARED. */
#[no_mangle]
export function driver_diagnostic_asm_print_current_func(): void {
  let msg: u8[200] = [];
  let at: i32 = 0;
  if (g_asm_current_func_len > 0) {
    at = driver_diag_append_cstr(&msg[0], 200, 0, "asm codegen failed in func=");
    at = driver_diag_append_name(&msg[0], 200, at, &g_asm_current_func[0], g_asm_current_func_len);
  } else {
    at = driver_diag_append_cstr(&msg[0], 200, 0, "asm codegen failed (func unknown)");
  }
  driver_diag_note(&msg[0]);
}

/** EXPR_VAR not found in asm local_offset map. Optional first_slot helps compare tables.
 * Assembles via append_cstr/name/i32 + note (no va_list). PLATFORM: SHARED. */
#[no_mangle]
export function driver_diagnostic_asm_var_not_found(name: *u8, len: i32, num_locals: i32, first_slot: *u8, first_len: i32): void {
  let namebuf: u8[65] = [];
  let firstbuf: u8[65] = [];
  let _n: i32 = driver_diag_copy_bytes(&namebuf[0], 65, name, len);
  let _f: i32 = driver_diag_copy_bytes(&firstbuf[0], 65, first_slot, first_len);
  let msg: u8[320] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 320, 0, "asm codegen EXPR_VAR not in ctx: \"");
  at = driver_diag_append_cstr(&msg[0], 320, at, &namebuf[0]);
  at = driver_diag_append_cstr(&msg[0], 320, at, "\" (func: ");
  if (g_asm_current_func_len > 0) {
    at = driver_diag_append_name(&msg[0], 320, at, &g_asm_current_func[0], g_asm_current_func_len);
  } else {
    at = driver_diag_append_cstr(&msg[0], 320, at, "?");
  }
  at = driver_diag_append_cstr(&msg[0], 320, at, ", num_locals=");
  at = driver_diag_append_i32(&msg[0], 320, at, num_locals);
  if (num_locals > 0) {
    if (first_slot != 0 as *u8) {
      if (first_len > 0) {
        if (first_len <= 64) {
          at = driver_diag_append_cstr(&msg[0], 320, at, ", first_slot=\"");
          at = driver_diag_append_cstr(&msg[0], 320, at, &firstbuf[0]);
          at = driver_diag_append_cstr(&msg[0], 320, at, "\" len=");
          at = driver_diag_append_i32(&msg[0], 320, at, first_len);
        }
      }
    }
  }
  at = driver_diag_append_cstr(&msg[0], 320, at, ")");
  driver_diag_note(&msg[0]);
}

/** Asm backend fail site note before returning -1. loc encodes stage (1=text..8=epilogue).
 * Includes last_expr_kind and optional current func name. PLATFORM: SHARED — pure thin. */
#[no_mangle]
export function driver_diagnostic_asm_fail_at(loc: i32): void {
  let msg: u8[240] = [];
  let at: i32 = 0;
  if (g_asm_current_func_len > 0) {
    at = driver_diag_append_cstr(&msg[0], 240, 0, "asm codegen func=");
    at = driver_diag_append_name(&msg[0], 240, at, &g_asm_current_func[0], g_asm_current_func_len);
    at = driver_diag_append_cstr(&msg[0], 240, at, " fail_at=");
    at = driver_diag_append_i32(&msg[0], 240, at, loc);
    at = driver_diag_append_cstr(&msg[0], 240, at, " (last_expr_kind=");
    at = driver_diag_append_i32(&msg[0], 240, at, g_asm_last_expr_kind);
    at = driver_diag_append_cstr(&msg[0], 240, at, ")");
  } else {
    at = driver_diag_append_cstr(&msg[0], 240, 0, "asm codegen fail_at=");
    at = driver_diag_append_i32(&msg[0], 240, at, loc);
    at = driver_diag_append_cstr(&msg[0], 240, at, " (last_expr_kind=");
    at = driver_diag_append_i32(&msg[0], 240, at, g_asm_last_expr_kind);
    at = driver_diag_append_cstr(&msg[0], 240, at, ")");
  }
  driver_diag_note(&msg[0]);
}

// pure: LSP collect or check-only mark then diag_report (same full.x G-02f-163; no snprintf)
/** Exported function `driver_diag_report_prefixed`.
 * Implements `driver_diag_report_prefixed`.
 * @param line i32
 * @param col i32
 * @param msg *u8
 * @return void
 */
#[no_mangle]
export function driver_diag_report_prefixed(line: i32, col: i32, msg: *u8): void {
  unsafe {
    if (lsp_diag_get_enabled() != 0) {
      let ln: i32 = line;
      let cl: i32 = col;
      if (ln <= 0) { ln = 1; }
      if (cl <= 0) { cl = 1; }
      let m: *u8 = msg;
      if (m == 0 as *u8) { m = ""; }
      lsp_diag_add(ln, cl, 1, m);
      return;
    }
    if (driver_check_only_get() != 0) {
      driver_check_diag_emitted_note();
    }
    let m2: *u8 = msg;
    if (m2 == 0 as *u8) { m2 = ""; }
    diag_report(0 as *u8, line, col, 0 as *u8, m2, m2);
  }
}

// pure: pipe debug note (append_cstr/i32 + note; no va_list diag_reportf)
// kind:0=before_codegen 1=source_len 2=after_entry 3=pipe_marker
/** Exported function `driver_diag_pipe_note`.
 * Implements `driver_diag_pipe_note`.
 * @param kind i32
 * @param a i32
 * @param b i32
 * @return void
 */
#[no_mangle]
export function driver_diag_pipe_note(kind: i32, a: i32, b: i32): void {
  let msg: u8[128] = [];
  if (kind == 0) {
    let at: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "pipeline debug: before_codegen num_funcs=");
    at = driver_diag_append_i32(&msg[0], 128, at, a);
    at = driver_diag_append_cstr(&msg[0], 128, at, " out_len=");
    at = driver_diag_append_i32(&msg[0], 128, at, b);
    driver_diag_note(&msg[0]);
    return;
  }
  if (kind == 1) {
    let at1: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "pipeline debug: entry_source_len=");
    at1 = driver_diag_append_i32(&msg[0], 128, at1, a);
    driver_diag_note(&msg[0]);
    return;
  }
  if (kind == 2) {
    let at2: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "pipeline debug: after_entry_parse num_funcs=");
    at2 = driver_diag_append_i32(&msg[0], 128, at2, a);
    driver_diag_note(&msg[0]);
    return;
  }
  if (kind == 3) {
    let at3: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "pipeline debug: pipe_marker=");
    at3 = driver_diag_append_i32(&msg[0], 128, at3, a);
    driver_diag_note(&msg[0]);
    return;
  }
}

// pure: same shape as seed Cap residual - link_abi_getenv("XLANG_DEBUG_PARSE") non-null or parse_strict.
// (C: !getenv && !parse_strict -> return; any non-NULL getenv enables, including "0".)
/** Internal function `driver_diag_parse_debug_enabled`.
 * Implements `driver_diag_parse_debug_enabled`.
 * @return i32
 */
function driver_diag_parse_debug_enabled(): i32 {
  unsafe {
    if (link_abi_getenv("XLANG_DEBUG_PARSE") != 0 as *u8) {
      return 1;
    }
  }
  return driver_parse_strict_enabled();
}

// pure: parse debug step note (append+note; no va_list reportf)
/** Exported function `driver_debug_log`.
 * Implements `driver_debug_log`.
 * @param step i32
 * @return void
 */
#[no_mangle]
export function driver_debug_log(step: i32): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  let msg: u8[128] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "parse debug: step=");
  at = driver_diag_append_i32(&msg[0], 128, at, step);
  driver_diag_note(&msg[0]);
}

// pure:tok.kind note
/** Exported function `parser_diag_tok_kind`.
 * Implements `parser_diag_tok_kind`.
 * @param k i32
 * @return void
 */
#[no_mangle]
export function parser_diag_tok_kind(k: i32): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  let msg: u8[128] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "parse debug: r.tok.kind=");
  at = driver_diag_append_i32(&msg[0], 128, at, k);
  driver_diag_note(&msg[0]);
}

// pure:first ident_len note
/** Exported function `parser_diag_ident_len`.
 * Query helper `parser_diag_ident_len`.
 * @param len i32
 * @return void
 */
#[no_mangle]
export function parser_diag_ident_len(len: i32): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  let msg: u8[128] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "parse debug: first ident_len=");
  at = driver_diag_append_i32(&msg[0], 128, at, len);
  driver_diag_note(&msg[0]);
}

// pure:library scan fail note
/** Exported function `parser_diag_scan_fail`.
 * Implements `parser_diag_scan_fail`.
 * @param step i32
 * @return void
 */
#[no_mangle]
export function parser_diag_scan_fail(step: i32): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  let msg: u8[128] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 128, 0, "library scan failed at step=");
  at = driver_diag_append_i32(&msg[0], 128, at, step);
  driver_diag_note(&msg[0]);
}

// pure: XLANG_TYPECK_BLOCK set -> block count note (append+note, no va_list)
/** Exported function `driver_diagnostic_typeck_block_enter`.
 * Implements `driver_diagnostic_typeck_block_enter`.
 * @param func_idx i32
 * @param block_ref i32
 * @param n_const i32
 * @param n_let i32
 * @param n_loop i32
 * @param n_for i32
 * @param n_expr i32
 * @param final_ref i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_block_enter(func_idx: i32, block_ref: i32, n_const: i32, n_let: i32, n_loop: i32, n_for: i32, n_expr: i32, final_ref: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_BLOCK") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "typeck block debug: func_idx=");
  at = driver_diag_append_i32(&msg[0], 240, at, func_idx);
  at = driver_diag_append_cstr(&msg[0], 240, at, " block_ref=");
  at = driver_diag_append_i32(&msg[0], 240, at, block_ref);
  at = driver_diag_append_cstr(&msg[0], 240, at, " const=");
  at = driver_diag_append_i32(&msg[0], 240, at, n_const);
  at = driver_diag_append_cstr(&msg[0], 240, at, " let=");
  at = driver_diag_append_i32(&msg[0], 240, at, n_let);
  at = driver_diag_append_cstr(&msg[0], 240, at, " while=");
  at = driver_diag_append_i32(&msg[0], 240, at, n_loop);
  at = driver_diag_append_cstr(&msg[0], 240, at, " for=");
  at = driver_diag_append_i32(&msg[0], 240, at, n_for);
  at = driver_diag_append_cstr(&msg[0], 240, at, " expr_stmt=");
  at = driver_diag_append_i32(&msg[0], 240, at, n_expr);
  at = driver_diag_append_cstr(&msg[0], 240, at, " final_expr=");
  at = driver_diag_append_i32(&msg[0], 240, at, final_ref);
  driver_diag_note(&msg[0]);
}

// pure: XLANG_TYPECK_FN set -> function-enter note
/** Exported function `driver_diagnostic_typeck_fn_enter`.
 * Implements `driver_diagnostic_typeck_fn_enter`.
 * @param func_idx i32
 * @param name *u8
 * @param name_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_fn_enter(func_idx: i32, name: *u8, name_len: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_FN") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[160] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 160, 0, "typeck function debug: func_idx=");
  at = driver_diag_append_i32(&msg[0], 160, at, func_idx);
  at = driver_diag_append_cstr(&msg[0], 160, at, " name=");
  if (name != 0 as *u8 && name_len > 0) {
    at = driver_diag_append_name(&msg[0], 160, at, name, name_len);
  } else {
    at = driver_diag_append_cstr(&msg[0], 160, at, "(unknown)");
  }
  driver_diag_note(&msg[0]);
}

// pure: XLANG_TYPECK_VAR set -> VAR resolution source note
/** Exported function `driver_diagnostic_typeck_var_resolution`.
 * Implements `driver_diagnostic_typeck_var_resolution`.
 * @param expr_ref i32
 * @param name *u8
 * @param name_len i32
 * @param func_idx i32
 * @param block_ref i32
 * @param source i32
 * @param type_ref i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_var_resolution(expr_ref: i32, name: *u8, name_len: i32, func_idx: i32, block_ref: i32, source: i32, type_ref: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_VAR") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[200] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 200, 0, "typeck var debug: expr=");
  at = driver_diag_append_i32(&msg[0], 200, at, expr_ref);
  at = driver_diag_append_cstr(&msg[0], 200, at, " name=");
  if (name != 0 as *u8 && name_len > 0) {
    at = driver_diag_append_name(&msg[0], 200, at, name, name_len);
  } else {
    at = driver_diag_append_cstr(&msg[0], 200, at, "?");
  }
  at = driver_diag_append_cstr(&msg[0], 200, at, " func=");
  at = driver_diag_append_i32(&msg[0], 200, at, func_idx);
  at = driver_diag_append_cstr(&msg[0], 200, at, " block=");
  at = driver_diag_append_i32(&msg[0], 200, at, block_ref);
  at = driver_diag_append_cstr(&msg[0], 200, at, " source=");
  at = driver_diag_append_i32(&msg[0], 200, at, source);
  at = driver_diag_append_cstr(&msg[0], 200, at, " type_ref=");
  at = driver_diag_append_i32(&msg[0], 200, at, type_ref);
  driver_diag_note(&msg[0]);
}

// pure: scratch BSS pointers (expect/found 96B each)
/** Exported function `driver_typeck_diag_scratch_expect`.
 * Implements `driver_typeck_diag_scratch_expect`.
 * @return *u8
 */
#[no_mangle]
export function driver_typeck_diag_scratch_expect(): *u8 {
  return &g_type_diag_scratch_expect[0];
}

/** Exported function `driver_typeck_diag_scratch_found`.
 * Implements `driver_typeck_diag_scratch_found`.
 * @return *u8
 */
#[no_mangle]
export function driver_typeck_diag_scratch_found(): *u8 {
  return &g_type_diag_scratch_found[0];
}

// pure: fill expr fragment (? fallback; no memcpy/snprintf)
/** Exported function `driver_diag_fill_expr_part`.
 * Implements `driver_diag_fill_expr_part`.
 * @param dst *u8
 * @param cap i32
 * @param expr_buf *u8
 * @param expr_len i32
 * @return void
 */
#[no_mangle]
export function driver_diag_fill_expr_part(dst: *u8, cap: i32, expr_buf: *u8, expr_len: i32): void {
  if (dst == 0) { return; }
  if (cap <= 0) { return; }
  let el: i32 = 0;
  if (expr_buf != 0) {
    if (expr_len > 0) { el = expr_len; }
  }
  if (el > 0) {
    if (el < cap) {
      let n: i32 = driver_diag_copy_bytes(dst, cap as i64, expr_buf, el);
      return;
    }
  }
  dst[0] = 63;
  if (cap > 1) { dst[1] = 0; }
}

// pure:pref + epart + ", found " + fpart
/** Exported function `driver_diag_build_expected_found`.
 * Implements `driver_diag_build_expected_found`.
 * @param msg *u8
 * @param msg_cap i32
 * @param pref *u8
 * @param epart *u8
 * @param fpart *u8
 * @return void
 */
#[no_mangle]
export function driver_diag_build_expected_found(msg: *u8, msg_cap: i32, pref: *u8, epart: *u8, fpart: *u8): void {
  let mid: *u8 = ", found ";
  let at: i32 = driver_diag_append_cstr(msg, msg_cap, 0, pref);
  at = driver_diag_append_cstr(msg, msg_cap, at, epart);
  at = driver_diag_append_cstr(msg, msg_cap, at, mid);
  at = driver_diag_append_cstr(msg, msg_cap, at, fpart);
}

/** Exported function `driver_diagnostic_typeck_return_unresolved`.
 * Implements `driver_diagnostic_typeck_return_unresolved`.
 * @param line i32
 * @param col i32
 * @param expr_buf *u8
 * @param expr_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_return_unresolved(line: i32, col: i32, expr_buf: *u8, expr_len: i32): void {
  let expr_part: u8[128] = [];
  let msg: u8[240] = [];
  driver_diag_fill_expr_part(&expr_part[0], 128, expr_buf, expr_len);
  let pref: *u8 = "typeck error: cannot resolve return subexpression: ";
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, pref);
  at = driver_diag_append_cstr(&msg[0], 240, at, &expr_part[0]);
  driver_diag_report_prefixed(line, col, &msg[0]);
}

/** Exported function `driver_diagnostic_typeck_return_subexpr`.
 * Implements `driver_diagnostic_typeck_return_subexpr`.
 * @param line i32
 * @param col i32
 * @param expr_buf *u8
 * @param expr_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_return_subexpr(line: i32, col: i32, expr_buf: *u8, expr_len: i32): void {
  let expr_part: u8[128] = [];
  let msg: u8[240] = [];
  driver_diag_fill_expr_part(&expr_part[0], 128, expr_buf, expr_len);
  let pref: *u8 = "typeck note: return subexpression: ";
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, pref);
  at = driver_diag_append_cstr(&msg[0], 240, at, &expr_part[0]);
  driver_diag_report_prefixed(line, col, &msg[0]);
}

/** Exported function `driver_diagnostic_typeck_return_mismatch`.
 * Implements `driver_diagnostic_typeck_return_mismatch`.
 * @param line i32
 * @param col i32
 * @param expect_buf *u8
 * @param expect_len i32
 * @param found_buf *u8
 * @param found_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_return_mismatch(line: i32, col: i32, expect_buf: *u8, expect_len: i32, found_buf: *u8, found_len: i32): void {
  let epart: u8[112] = [];
  let fpart: u8[112] = [];
  let msg: u8[240] = [];
  driver_diag_fill_expr_part(&epart[0], 112, expect_buf, expect_len);
  driver_diag_fill_expr_part(&fpart[0], 112, found_buf, found_len);
  let pref: *u8 = "typeck error: return expression type mismatch: expected ";
  driver_diag_build_expected_found(&msg[0], 240, pref, &epart[0], &fpart[0]);
  driver_diag_report_prefixed(line, col, &msg[0]);
}

/** Exported function `driver_diagnostic_typeck_assign_mismatch`.
 * Implements `driver_diagnostic_typeck_assign_mismatch`.
 * @param is_compound i32
 * @param line i32
 * @param col i32
 * @param expect_buf *u8
 * @param expect_len i32
 * @param found_buf *u8
 * @param found_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_assign_mismatch(is_compound: i32, line: i32, col: i32, expect_buf: *u8, expect_len: i32, found_buf: *u8, found_len: i32): void {
  let epart: u8[112] = [];
  let fpart: u8[112] = [];
  let msg: u8[240] = [];
  driver_diag_fill_expr_part(&epart[0], 112, expect_buf, expect_len);
  driver_diag_fill_expr_part(&fpart[0], 112, found_buf, found_len);
  let pref: *u8 = "typeck error: assignment type mismatch: expected ";
  if (is_compound != 0) {
    pref = "typeck error: compound assignment type mismatch: expected ";
  }
  driver_diag_build_expected_found(&msg[0], 240, pref, &epart[0], &fpart[0]);
  driver_diag_report_prefixed(line, col, &msg[0]);
}

/** Exported function `driver_diagnostic_typeck_call_not_generic`.
 * Implements `driver_diagnostic_typeck_call_not_generic`.
 * @param line i32
 * @param col i32
 * @param name *u8
 * @param name_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_not_generic(line: i32, col: i32, name: *u8, name_len: i32): void {
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "function '");
  at = driver_diag_append_name(&msg[0], 240, at, name, name_len);
  at = driver_diag_append_cstr(&msg[0], 240, at, "' is not generic but type arguments were provided");
  unsafe {
    lsp_diag_report_typeck(line, col, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_typeck_call_wrong_num_type_args`.
 * Implements `driver_diagnostic_typeck_call_wrong_num_type_args`.
 * @param line i32
 * @param col i32
 * @param name *u8
 * @param name_len i32
 * @param expect_n i32
 * @param got_n i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_wrong_num_type_args(line: i32, col: i32, name: *u8, name_len: i32, expect_n: i32, got_n: i32): void {
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "generic function '");
  at = driver_diag_append_name(&msg[0], 240, at, name, name_len);
  at = driver_diag_append_cstr(&msg[0], 240, at, "' expects ");
  at = driver_diag_append_i32(&msg[0], 240, at, expect_n);
  at = driver_diag_append_cstr(&msg[0], 240, at, " type arguments, got ");
  at = driver_diag_append_i32(&msg[0], 240, at, got_n);
  unsafe {
    lsp_diag_report_typeck(line, col, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_typeck_call_requires_type_args`.
 * Implements `driver_diagnostic_typeck_call_requires_type_args`.
 * @param line i32
 * @param col i32
 * @param name *u8
 * @param name_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_call_requires_type_args(line: i32, col: i32, name: *u8, name_len: i32): void {
  let msg: u8[280] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 280, 0, "generic function '");
  at = driver_diag_append_name(&msg[0], 280, at, name, name_len);
  at = driver_diag_append_cstr(&msg[0], 280, at, "' requires type arguments (e.g. ");
  at = driver_diag_append_name(&msg[0], 280, at, name, name_len);
  at = driver_diag_append_cstr(&msg[0], 280, at, "<Type>(...))");
  unsafe {
    lsp_diag_report_typeck(line, col, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_typeck_struct_padding_before`.
 * Implements `driver_diagnostic_typeck_struct_padding_before`.
 * @param sname *u8
 * @param sname_len i32
 * @param gap i32
 * @param fname *u8
 * @param fname_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_struct_padding_before(sname: *u8, sname_len: i32, gap: i32, fname: *u8, fname_len: i32): void {
  let msg: u8[320] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 320, 0, "struct '");
  at = driver_diag_append_name(&msg[0], 320, at, sname, sname_len);
  at = driver_diag_append_cstr(&msg[0], 320, at, "' has ");
  at = driver_diag_append_i32(&msg[0], 320, at, gap);
  at = driver_diag_append_cstr(&msg[0], 320, at, " byte(s) implicit padding before field '");
  at = driver_diag_append_name(&msg[0], 320, at, fname, fname_len);
  at = driver_diag_append_cstr(&msg[0], 320, at, "'; add explicit padding field or allow(padding)");
  unsafe {
    lsp_diag_report_typeck(0, 0, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_typeck_struct_padding_trailing`.
 * Implements `driver_diagnostic_typeck_struct_padding_trailing`.
 * @param sname *u8
 * @param sname_len i32
 * @param gap i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_struct_padding_trailing(sname: *u8, sname_len: i32, gap: i32): void {
  let msg: u8[320] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 320, 0, "struct '");
  at = driver_diag_append_name(&msg[0], 320, at, sname, sname_len);
  at = driver_diag_append_cstr(&msg[0], 320, at, "' has ");
  at = driver_diag_append_i32(&msg[0], 320, at, gap);
  at = driver_diag_append_cstr(&msg[0], 320, at, " byte(s) implicit trailing padding; add explicit padding field or allow(padding)");
  unsafe {
    lsp_diag_report_typeck(0, 0, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_typeck_struct_field_bad_size`.
 * Implements `driver_diagnostic_typeck_struct_field_bad_size`.
 * @param sname *u8
 * @param sname_len i32
 * @param fname *u8
 * @param fname_len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_typeck_struct_field_bad_size(sname: *u8, sname_len: i32, fname: *u8, fname_len: i32): void {
  let msg: u8[280] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 280, 0, "struct '");
  at = driver_diag_append_name(&msg[0], 280, at, sname, sname_len);
  at = driver_diag_append_cstr(&msg[0], 280, at, "' field '");
  at = driver_diag_append_name(&msg[0], 280, at, fname, fname_len);
  at = driver_diag_append_cstr(&msg[0], 280, at, "' has unknown or invalid type size");
  unsafe {
    lsp_diag_report_typeck(0, 0, &msg[0]);
  }
}

/** Exported function `driver_diagnostic_asm_unsupported_expr`.
 * Implements `driver_diagnostic_asm_unsupported_expr`.
 * @param kind i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_asm_unsupported_expr(kind: i32): void {
  let msg: u8[96] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 96, 0, "asm codegen unsupported ExprKind=");
  at = driver_diag_append_i32(&msg[0], 96, at, kind);
  driver_diag_note(&msg[0]);
}

/** Exported function `driver_diagnostic_asm_elf_unresolved_patch`.
 * Implements `driver_diagnostic_asm_elf_unresolved_patch`.
 * @param name *u8
 * @param len i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_asm_elf_unresolved_patch(name: *u8, len: i32): void {
  let namebuf: u8[65] = [];
  driver_diag_fill_expr_part(&namebuf[0], 65, name, len);
  let msg: u8[160] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 160, 0, "elf unresolved patch label name_len=");
  at = driver_diag_append_i32(&msg[0], 160, at, len);
  at = driver_diag_append_cstr(&msg[0], 160, at, " name='");
  at = driver_diag_append_cstr(&msg[0], 160, at, &namebuf[0]);
  at = driver_diag_append_cstr(&msg[0], 160, at, "'");
  driver_diag_note(&msg[0]);
}

/** Exported function `driver_diagnostic_asm_macho_empty_reloc`.
 * Implements `driver_diagnostic_asm_macho_empty_reloc`.
 * @param reloc_idx i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_asm_macho_empty_reloc(reloc_idx: i32): void {
  let msg: u8[96] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 96, 0, "macho empty reloc symbol at idx=");
  at = driver_diag_append_i32(&msg[0], 96, at, reloc_idx);
  driver_diag_note(&msg[0]);
}

/** Exported function `driver_diagnostic_asm_macho_missing_und_reloc`.
 * Implements `driver_diagnostic_asm_macho_missing_und_reloc`.
 * @param reloc_idx i32
 * @return void
 */
#[no_mangle]
export function driver_diagnostic_asm_macho_missing_und_reloc(reloc_idx: i32): void {
  let msg: u8[96] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 96, 0, "macho undef reloc not in und pool at idx=");
  at = driver_diag_append_i32(&msg[0], 96, at, reloc_idx);
  driver_diag_note(&msg[0]);
}

// ---- Cap residual pure deep-migrate: skip / commit_fail / generic / param / import / warn / hint (wave2) ----

/** Parse skip note when a function cannot be committed. Gate: XLANG_DEBUG_PARSE non-NULL
 * or XLANG_PARSE_STRICT truthy (same as driver_diag_parse_debug_enabled).
 * Tag: "debug" if link_abi_getenv(XLANG_DEBUG_PARSE) non-NULL else "strict" (cold seed ternary).
 * LSP path: "parse skip at byte N (num_funcs=M) name=X [tag]"; note path uses mode=tag.
 * Assembles via append_cstr/append_i32/append_name; no va_list reportf/snprintf.
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_parse_skip_function(byte_pos: i32, num_funcs_so_far: i32, name_len: i32, name: *u8): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  unsafe {
    // Inline mode tag (avoid *u8-returning helper — -E may omit its body).
    let tag: *u8 = "strict";
    if (link_abi_getenv("XLANG_DEBUG_PARSE") != 0 as *u8) {
      tag = "debug";
    }
    let msg: u8[240] = [];
    let at: i32 = 0;
    if (lsp_diag_get_enabled() != 0) {
      at = driver_diag_append_cstr(&msg[0], 240, 0, "parse skip at byte ");
      at = driver_diag_append_i32(&msg[0], 240, at, byte_pos);
      at = driver_diag_append_cstr(&msg[0], 240, at, " (num_funcs=");
      at = driver_diag_append_i32(&msg[0], 240, at, num_funcs_so_far);
      at = driver_diag_append_cstr(&msg[0], 240, at, ") name=");
      if (name != 0 as *u8) {
        if (name_len > 0) {
          at = driver_diag_append_name(&msg[0], 240, at, name, name_len);
        } else {
          at = driver_diag_append_cstr(&msg[0], 240, at, "?");
        }
      } else {
        at = driver_diag_append_cstr(&msg[0], 240, at, "?");
      }
      at = driver_diag_append_cstr(&msg[0], 240, at, " [");
      at = driver_diag_append_cstr(&msg[0], 240, at, tag);
      at = driver_diag_append_cstr(&msg[0], 240, at, "]");
      lsp_diag_add(1, 1, 1, &msg[0]);
      return;
    }
    at = driver_diag_append_cstr(&msg[0], 240, 0, "parse skip at byte ");
    at = driver_diag_append_i32(&msg[0], 240, at, byte_pos);
    at = driver_diag_append_cstr(&msg[0], 240, at, " (num_funcs=");
    at = driver_diag_append_i32(&msg[0], 240, at, num_funcs_so_far);
    at = driver_diag_append_cstr(&msg[0], 240, at, ", name=");
    if (name != 0 as *u8) {
      if (name_len > 0) {
        at = driver_diag_append_name(&msg[0], 240, at, name, name_len);
      } else {
        at = driver_diag_append_cstr(&msg[0], 240, at, "?");
      }
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "?");
    }
    at = driver_diag_append_cstr(&msg[0], 240, at, ", mode=");
    at = driver_diag_append_cstr(&msg[0], 240, at, tag);
    at = driver_diag_append_cstr(&msg[0], 240, at, ")");
    driver_diag_note(&msg[0]);
  }
}

/** Emit XP002 when parse commit fails (arena/sidecar full). Same gate as parse_skip.
 * Message: ".x parse commit failed at byte N (num_funcs=M, name=X, mode=tag)".
 * Path: append assemble → lsp_diag_add_code if LSP; else check note + diag_report_with_code
 * ("pipeline error","XP002"). No va_list report_x_pipeline_code.
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_parse_commit_fail(byte_pos: i32, num_funcs_so_far: i32, name_len: i32, name: *u8): void {
  if (driver_diag_parse_debug_enabled() == 0) {
    return;
  }
  unsafe {
    let tag: *u8 = "strict";
    if (link_abi_getenv("XLANG_DEBUG_PARSE") != 0 as *u8) {
      tag = "debug";
    }
    let msg: u8[256] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 256, 0, ".x parse commit failed at byte ");
    at = driver_diag_append_i32(&msg[0], 256, at, byte_pos);
    at = driver_diag_append_cstr(&msg[0], 256, at, " (num_funcs=");
    at = driver_diag_append_i32(&msg[0], 256, at, num_funcs_so_far);
    at = driver_diag_append_cstr(&msg[0], 256, at, ", name=");
    if (name != 0 as *u8) {
      if (name_len > 0) {
        if (name_len < 64) {
          at = driver_diag_append_name(&msg[0], 256, at, name, name_len);
        } else {
          at = driver_diag_append_cstr(&msg[0], 256, at, "?");
        }
      } else {
        at = driver_diag_append_cstr(&msg[0], 256, at, "?");
      }
    } else {
      at = driver_diag_append_cstr(&msg[0], 256, at, "?");
    }
    at = driver_diag_append_cstr(&msg[0], 256, at, ", mode=");
    at = driver_diag_append_cstr(&msg[0], 256, at, tag);
    at = driver_diag_append_cstr(&msg[0], 256, at, ")");
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add_code(1, 1, 1, "XP002", &msg[0]);
      return;
    }
    if (driver_check_only_get() != 0) {
      driver_check_diag_emitted_note();
    }
    diag_report_with_code(0 as *u8, 0, 0, "pipeline error", "XP002", &msg[0], 0 as *u8);
  }
}

/** Generic-param debug note for parse_into commit path. Gate: XLANG_DEBUG_PARSE_GENERIC
 * non-NULL (any value). Message: "parse generic debug: byte=N num_funcs=M generic=G is_main=I name=X".
 * PLATFORM: SHARED — pure in thin; cold C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_parse_func_generic(byte_pos: i32, num_funcs_so_far: i32, name: *u8, name_len: i32, num_generic_params: i32, is_main: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_DEBUG_PARSE_GENERIC") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "parse generic debug: byte=");
  at = driver_diag_append_i32(&msg[0], 240, at, byte_pos);
  at = driver_diag_append_cstr(&msg[0], 240, at, " num_funcs=");
  at = driver_diag_append_i32(&msg[0], 240, at, num_funcs_so_far);
  at = driver_diag_append_cstr(&msg[0], 240, at, " generic=");
  at = driver_diag_append_i32(&msg[0], 240, at, num_generic_params);
  at = driver_diag_append_cstr(&msg[0], 240, at, " is_main=");
  at = driver_diag_append_i32(&msg[0], 240, at, is_main);
  at = driver_diag_append_cstr(&msg[0], 240, at, " name=");
  if (name != 0 as *u8) {
    if (name_len > 0) {
      at = driver_diag_append_name(&msg[0], 240, at, name, name_len);
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "?");
    }
  } else {
    at = driver_diag_append_cstr(&msg[0], 240, at, "?");
  }
  driver_diag_note(&msg[0]);
}

/** OneFunc param type_ref debug. Gate: XLANG_PARSE_PARAM non-NULL.
 * Message: "parser param debug: func=F stage=S param_idx=I param=P type_ref=T".
 * PLATFORM: SHARED — pure in thin; cold C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_parser_onefunc_param_ref(func_name: *u8, func_name_len: i32, param_name: *u8, param_name_len: i32, stage: i32, param_idx: i32, type_ref: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_PARSE_PARAM") == 0 as *u8) {
      return;
    }
  }
  let msg: u8[240] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 240, 0, "parser param debug: func=");
  if (func_name != 0 as *u8) {
    if (func_name_len > 0) {
      at = driver_diag_append_name(&msg[0], 240, at, func_name, func_name_len);
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "?");
    }
  } else {
    at = driver_diag_append_cstr(&msg[0], 240, at, "?");
  }
  at = driver_diag_append_cstr(&msg[0], 240, at, " stage=");
  at = driver_diag_append_i32(&msg[0], 240, at, stage);
  at = driver_diag_append_cstr(&msg[0], 240, at, " param_idx=");
  at = driver_diag_append_i32(&msg[0], 240, at, param_idx);
  at = driver_diag_append_cstr(&msg[0], 240, at, " param=");
  if (param_name != 0 as *u8) {
    if (param_name_len > 0) {
      at = driver_diag_append_name(&msg[0], 240, at, param_name, param_name_len);
    } else {
      at = driver_diag_append_cstr(&msg[0], 240, at, "?");
    }
  } else {
    at = driver_diag_append_cstr(&msg[0], 240, at, "?");
  }
  at = driver_diag_append_cstr(&msg[0], 240, at, " type_ref=");
  at = driver_diag_append_i32(&msg[0], 240, at, type_ref);
  driver_diag_note(&msg[0]);
}

/** Import top-level const bare-name access must be qualified. Assembles fixed message then
 * lsp_diag_report_typeck (3-arg; no format varargs). With a binding: use binding.name form;
 * if binding is null: must be qualified as binding.name. PLATFORM: SHARED — pure in thin. */
#[no_mangle]
export function driver_diagnostic_typeck_import_const_must_be_qualified(line: i32, col: i32, name: *u8, name_len: i32, binding: *u8, binding_len: i32): void {
  let msg: u8[280] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 280, 0, "import constant '");
  at = driver_diag_append_name(&msg[0], 280, at, name, name_len);
  if (binding != 0 as *u8) {
    if (binding_len > 0) {
      at = driver_diag_append_cstr(&msg[0], 280, at, "' must be qualified; use ");
      at = driver_diag_append_name(&msg[0], 280, at, binding, binding_len);
      at = driver_diag_append_cstr(&msg[0], 280, at, ".");
      at = driver_diag_append_name(&msg[0], 280, at, name, name_len);
      unsafe {
        lsp_diag_report_typeck(line, col, &msg[0]);
      }
      return;
    }
  }
  at = driver_diag_append_cstr(&msg[0], 280, at, "' must be qualified as binding.");
  at = driver_diag_append_name(&msg[0], 280, at, name, name_len);
  unsafe {
    lsp_diag_report_typeck(line, col, &msg[0]);
  }
}

/** DOD-CL -pad-fields warning: two fields share a 64-byte cache line. Severity 2 (warning)
 * for LSP collect; else diag_report kind "warning". No snprintf. PLATFORM: SHARED. */
#[no_mangle]
export function driver_diagnostic_warn_pad_fields_same_cache_line(sname: *u8, sname_len: i32, f0: *u8, f0_len: i32, f1: *u8, f1_len: i32): void {
  let msg: u8[384] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 384, 0, "-pad-fields: struct '");
  at = driver_diag_append_name(&msg[0], 384, at, sname, sname_len);
  at = driver_diag_append_cstr(&msg[0], 384, at, "' fields '");
  at = driver_diag_append_name(&msg[0], 384, at, f0, f0_len);
  at = driver_diag_append_cstr(&msg[0], 384, at, "' and '");
  at = driver_diag_append_name(&msg[0], 384, at, f1, f1_len);
  // Split long cstr: product codegen string-lit cap ~127 bytes (G.9 / no silent truncate).
  at = driver_diag_append_cstr(&msg[0], 384, at, "' share a 64-byte cache line; ");
  at = driver_diag_append_cstr(&msg[0], 384, at, "consider align(64) to avoid false sharing");
  unsafe {
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add(1, 1, 2, &msg[0]);
      return;
    }
    diag_report(0 as *u8, 0, 0, "warning", &msg[0], 0 as *u8);
  }
}

/** DOD-CL-S2 -hot-reorder warning: move hot field before cold. Severity 2 for LSP; else
 * diag_report "warning". PLATFORM: SHARED — pure in thin; cold C body; FROM_X no pure-dup. */
#[no_mangle]
export function driver_diagnostic_warn_hot_reorder_field(sname: *u8, sname_len: i32, hot: *u8, hot_len: i32, cold: *u8, cold_len: i32): void {
  let msg: u8[256] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 256, 0, "-hot-reorder: struct '");
  at = driver_diag_append_name(&msg[0], 256, at, sname, sname_len);
  at = driver_diag_append_cstr(&msg[0], 256, at, "': consider moving hot field '");
  at = driver_diag_append_name(&msg[0], 256, at, hot, hot_len);
  at = driver_diag_append_cstr(&msg[0], 256, at, "' before '");
  at = driver_diag_append_name(&msg[0], 256, at, cold, cold_len);
  at = driver_diag_append_cstr(&msg[0], 256, at, "'");
  unsafe {
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add(1, 1, 2, &msg[0]);
      return;
    }
    diag_report(0 as *u8, 0, 0, "warning", &msg[0], 0 as *u8);
  }
}

/** L6 unused-binding hint (info). Message: "unused binding 'name'". LSP severity 3; else
 * diag_report kind "info" at line/col (clamped to >=1 for LSP). PLATFORM: SHARED. */
#[no_mangle]
export function driver_diagnostic_hint_unused_binding(line: i32, col: i32, name: *u8, name_len: i32): void {
  let msg: u8[160] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 160, 0, "unused binding '");
  at = driver_diag_append_name(&msg[0], 160, at, name, name_len);
  at = driver_diag_append_cstr(&msg[0], 160, at, "'");
  unsafe {
    let ln: i32 = line;
    let cl: i32 = col;
    if (ln <= 0) { ln = 1; }
    if (cl <= 0) { cl = 1; }
    if (lsp_diag_get_enabled() != 0) {
      lsp_diag_add(ln, cl, 3, &msg[0]);
      return;
    }
    diag_report(0 as *u8, ln, cl, "info", &msg[0], 0 as *u8);
  }
}

// ---- Cap residual pure deep-migrate wave3: binop operands + parse_commit_shape ----

/** Optional binop operand debug note when link_abi_getenv("XLANG_TYPECK_BINOP") is set.
 * Assembles left/right refs, kinds, block refs, type refs, and type name fragments via
 * fill_expr_part (? fallback) + append_cstr/append_i32 + driver_diag_note. No va_list reportf.
 * Message text must match cold seed reportf format (field order fixed).
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_typeck_binop_operands(expr_ref: i32, left_ref: i32, right_ref: i32, left_kind: i32, right_kind: i32, left_block_ref: i32, right_block_ref: i32, left_ty_ref: i32, right_ty_ref: i32, left_ty: *u8, left_ty_len: i32, right_ty: *u8, right_ty_len: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_TYPECK_BINOP") == 0 as *u8) {
      return;
    }
  }
  let left_buf: u8[112] = [];
  let right_buf: u8[112] = [];
  // Match cold seed: empty / missing type name -> "?".
  driver_diag_fill_expr_part(&left_buf[0], 112, left_ty, left_ty_len);
  driver_diag_fill_expr_part(&right_buf[0], 112, right_ty, right_ty_len);
  let msg: u8[384] = [];
  // Split long cstrs: product codegen string-lit cap ~127 bytes.
  let at: i32 = driver_diag_append_cstr(&msg[0], 384, 0, "typeck binop debug: expr=");
  at = driver_diag_append_i32(&msg[0], 384, at, expr_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " left_ref=");
  at = driver_diag_append_i32(&msg[0], 384, at, left_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " left_kind=");
  at = driver_diag_append_i32(&msg[0], 384, at, left_kind);
  at = driver_diag_append_cstr(&msg[0], 384, at, " left_block=");
  at = driver_diag_append_i32(&msg[0], 384, at, left_block_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " left_ty_ref=");
  at = driver_diag_append_i32(&msg[0], 384, at, left_ty_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " left_ty=");
  at = driver_diag_append_cstr(&msg[0], 384, at, &left_buf[0]);
  at = driver_diag_append_cstr(&msg[0], 384, at, " right_ref=");
  at = driver_diag_append_i32(&msg[0], 384, at, right_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " right_kind=");
  at = driver_diag_append_i32(&msg[0], 384, at, right_kind);
  at = driver_diag_append_cstr(&msg[0], 384, at, " right_block=");
  at = driver_diag_append_i32(&msg[0], 384, at, right_block_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " right_ty_ref=");
  at = driver_diag_append_i32(&msg[0], 384, at, right_ty_ref);
  at = driver_diag_append_cstr(&msg[0], 384, at, " right_ty=");
  at = driver_diag_append_cstr(&msg[0], 384, at, &right_buf[0]);
  driver_diag_note(&msg[0]);
}

/** Optional parse-commit shape debug when link_abi_getenv("XLANG_DEBUG_PARSE_COMMIT") is set.
 * phase: 0=pre_fill, 1=post_block, else unknown. Prints pool vs block counts and final_expr_ref.
 * Assembles via fill_expr_part for name (? fallback) + append_* + driver_diag_note. No va_list.
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_parse_commit_shape(byte_pos: i32, num_funcs_so_far: i32, name: *u8, name_len: i32, phase: i32, block_ref: i32, pool_num_consts: i32, pool_num_lets: i32, pool_num_ifs: i32, pool_num_regions: i32, pool_num_stmt_order: i32, block_num_consts: i32, block_num_lets: i32, block_num_ifs: i32, block_num_regions: i32, block_num_stmt_order: i32, final_expr_ref: i32): void {
  unsafe {
    if (link_abi_getenv("XLANG_DEBUG_PARSE_COMMIT") == 0 as *u8) {
      return;
    }
  }
  let namebuf: u8[72] = [];
  driver_diag_fill_expr_part(&namebuf[0], 72, name, name_len);
  // Inline phase tag (avoid *u8-returning helper — -E may omit its body).
  let phase_name: *u8 = "unknown";
  if (phase == 0) {
    phase_name = "pre_fill";
  } else {
    if (phase == 1) {
      phase_name = "post_block";
    }
  }
  let msg: u8[512] = [];
  let at: i32 = driver_diag_append_cstr(&msg[0], 512, 0, "parse commit debug: byte=");
  at = driver_diag_append_i32(&msg[0], 512, at, byte_pos);
  at = driver_diag_append_cstr(&msg[0], 512, at, " num_funcs=");
  at = driver_diag_append_i32(&msg[0], 512, at, num_funcs_so_far);
  at = driver_diag_append_cstr(&msg[0], 512, at, " phase=");
  at = driver_diag_append_cstr(&msg[0], 512, at, phase_name);
  at = driver_diag_append_cstr(&msg[0], 512, at, " block=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_ref);
  at = driver_diag_append_cstr(&msg[0], 512, at, " pool(c=");
  at = driver_diag_append_i32(&msg[0], 512, at, pool_num_consts);
  at = driver_diag_append_cstr(&msg[0], 512, at, " l=");
  at = driver_diag_append_i32(&msg[0], 512, at, pool_num_lets);
  at = driver_diag_append_cstr(&msg[0], 512, at, " if=");
  at = driver_diag_append_i32(&msg[0], 512, at, pool_num_ifs);
  at = driver_diag_append_cstr(&msg[0], 512, at, " reg=");
  at = driver_diag_append_i32(&msg[0], 512, at, pool_num_regions);
  at = driver_diag_append_cstr(&msg[0], 512, at, " so=");
  at = driver_diag_append_i32(&msg[0], 512, at, pool_num_stmt_order);
  at = driver_diag_append_cstr(&msg[0], 512, at, ") block(c=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_num_consts);
  at = driver_diag_append_cstr(&msg[0], 512, at, " l=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_num_lets);
  at = driver_diag_append_cstr(&msg[0], 512, at, " if=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_num_ifs);
  at = driver_diag_append_cstr(&msg[0], 512, at, " reg=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_num_regions);
  at = driver_diag_append_cstr(&msg[0], 512, at, " so=");
  at = driver_diag_append_i32(&msg[0], 512, at, block_num_stmt_order);
  at = driver_diag_append_cstr(&msg[0], 512, at, " fin=");
  at = driver_diag_append_i32(&msg[0], 512, at, final_expr_ref);
  at = driver_diag_append_cstr(&msg[0], 512, at, ") name=");
  at = driver_diag_append_cstr(&msg[0], 512, at, &namebuf[0]);
  driver_diag_note(&msg[0]);
}

/** Parser-facing alias of driver_diagnostic_parse_commit_shape (same args / same body path).
 * G.7: zero business logic — single authority is driver_diagnostic_parse_commit_shape.
 * PLATFORM: SHARED — pure thin public; cold seed forwards; FROM_X no pure-dup _impl. */
#[no_mangle]
export function parser_diagnostic_parse_commit_shape(byte_pos: i32, num_funcs_so_far: i32, name: *u8, name_len: i32, phase: i32, block_ref: i32, pool_num_consts: i32, pool_num_lets: i32, pool_num_ifs: i32, pool_num_regions: i32, pool_num_stmt_order: i32, block_num_consts: i32, block_num_lets: i32, block_num_ifs: i32, block_num_regions: i32, block_num_stmt_order: i32, final_expr_ref: i32): void {
  driver_diagnostic_parse_commit_shape(byte_pos, num_funcs_so_far, name, name_len, phase, block_ref, pool_num_consts, pool_num_lets, pool_num_ifs, pool_num_regions, pool_num_stmt_order, block_num_consts, block_num_lets, block_num_ifs, block_num_regions, block_num_stmt_order, final_expr_ref);
}

/**
 * Parser parse-commit pre hook (phase 0): gather onefunc pool metrics, then
 * driver_diagnostic_parse_commit_shape. Called from parser.x at function commit.
 * @param arena *u8 — ASTArena* (unused at pre; kept for ABI symmetry with post)
 * @param name *u8 — function name bytes
 * @param name_len i32 — name length
 * @param block_ref i32 — block ref being filled
 * @param pool *u8 — onefunc result pool; null → zeros
 * @param final_expr_ref i32 — final expr ref at pre fill
 * @return void
 * wave302 G.7: authority moved here from pipeline_glue_strict_minimal seed twin
 * (product U from parser_x; dual-export ban — strict_minimal body deleted).
 * PLATFORM: SHARED freestanding parse-commit gather → shape.
 */
#[no_mangle]
export function parser_diagnostic_parse_commit_pre(arena: *u8, name: *u8, name_len: i32, block_ref: i32, pool: *u8, final_expr_ref: i32): void {
  let pool_nc: i32 = 0;
  let pool_nl: i32 = 0;
  let pool_nif: i32 = 0;
  let pool_nreg: i32 = 0;
  let pool_nso: i32 = 0;
  let _a: *u8 = arena;
  if (_a == 0 as *u8) {
    // keep seed (void)arena semantics — pre does not read block metrics
  }
  if (pool != 0 as *u8) {
    pool_nc = pipeline_onefunc_num_consts(pool);
    pool_nl = pipeline_onefunc_num_lets(pool);
    pool_nif = pipeline_onefunc_num_if_stmts(pool);
    pool_nreg = pipeline_onefunc_num_regions(pool);
    pool_nso = pipeline_onefunc_num_src_stmt_order(pool);
  }
  driver_diagnostic_parse_commit_shape(
    0, 0, name, name_len, 0, block_ref,
    pool_nc, pool_nl, pool_nif, pool_nreg, pool_nso,
    0, 0, 0, 0, 0, final_expr_ref
  );
}

/**
 * Parser parse-commit post hook (phase 1): gather onefunc pool + block metrics,
 * then driver_diagnostic_parse_commit_shape.
 * @param arena *u8 — ASTArena*; null → block metrics zero
 * @param name *u8 — function name bytes
 * @param name_len i32 — name length
 * @param block_ref i32 — committed block ref
 * @param pool *u8 — onefunc result pool; null → pool metrics zero
 * @return void
 * wave302 G.7: authority moved here from pipeline_glue_strict_minimal seed twin
 * (product U from parser_x; dual-export ban — strict_minimal body deleted).
 * PLATFORM: SHARED freestanding parse-commit gather → shape.
 */
#[no_mangle]
export function parser_diagnostic_parse_commit_post(arena: *u8, name: *u8, name_len: i32, block_ref: i32, pool: *u8): void {
  let pool_nc: i32 = 0;
  let pool_nl: i32 = 0;
  let pool_nif: i32 = 0;
  let pool_nreg: i32 = 0;
  let pool_nso: i32 = 0;
  let blk_nc: i32 = 0;
  let blk_nl: i32 = 0;
  let blk_nif: i32 = 0;
  let blk_nreg: i32 = 0;
  let blk_nso: i32 = 0;
  let final_er: i32 = 0;
  if (pool != 0 as *u8) {
    pool_nc = pipeline_onefunc_num_consts(pool);
    pool_nl = pipeline_onefunc_num_lets(pool);
    pool_nif = pipeline_onefunc_num_if_stmts(pool);
    pool_nreg = pipeline_onefunc_num_regions(pool);
    pool_nso = pipeline_onefunc_num_src_stmt_order(pool);
  }
  if (arena != 0 as *u8) {
    blk_nc = ast_ast_block_num_consts(arena, block_ref);
    blk_nl = ast_ast_block_num_lets(arena, block_ref);
    blk_nif = ast_ast_block_num_if_stmts(arena, block_ref);
    blk_nreg = ast_ast_block_num_regions(arena, block_ref);
    blk_nso = ast_ast_block_num_stmt_order(arena, block_ref);
    final_er = ast_ast_block_final_expr_ref(arena, block_ref);
  }
  driver_diagnostic_parse_commit_shape(
    0, 0, name, name_len, 1, block_ref,
    pool_nc, pool_nl, pool_nif, pool_nreg, pool_nso,
    blk_nc, blk_nl, blk_nif, blk_nreg, blk_nso, final_er
  );
}

// ---- Cap residual pure deep-migrate wave4: after_entry_parse_module + codegen_emit_func_fail ----

/** Optional pipeline debug after entry parse when link_abi_getenv("XLANG_DEBUG_PIPE") is set (any value;
 * match cold seed: non-NULL env enables, including "0"). Counts num_funcs / defined / extern via
 * pipeline_module_* APIs (G.7: do not reimplement module walk). Reads num_top_level_lets from
 * shared ast_Module layout offset 12 (i32 field index 3: after num_funcs/main/imports) — same
 * thin cast the cold seed uses; not a second layout authority.
 * Assembles notes via append_cstr/append_i32 + driver_diag_note. No va_list reportf.
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_after_entry_parse_module(module: *u8): void {
  unsafe {
    if (link_abi_getenv("XLANG_DEBUG_PIPE") == 0 as *u8) {
      return;
    }
    if (module == 0 as *u8) {
      return;
    }
    let nf: i32 = pipeline_module_num_funcs(module);
    let ndef: i32 = 0;
    let next: i32 = 0;
    let i: i32 = 0;
    while (i < nf) {
      if (pipeline_module_func_is_extern_at(module, i) != 0) {
        next = next + 1;
      } else {
        ndef = ndef + 1;
      }
      i = i + 1;
    }
    let msg: u8[200] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 200, 0, "pipeline debug: after_entry_parse num_funcs=");
    at = driver_diag_append_i32(&msg[0], 200, at, nf);
    at = driver_diag_append_cstr(&msg[0], 200, at, " num_defined=");
    at = driver_diag_append_i32(&msg[0], 200, at, ndef);
    at = driver_diag_append_cstr(&msg[0], 200, at, " num_extern=");
    at = driver_diag_append_i32(&msg[0], 200, at, next);
    driver_diag_note(&msg[0]);
    // ast_Module shared prefix: [num_funcs, main_func_index, num_imports, num_top_level_lets]
    // PLATFORM: SHARED — LE i32 at byte offset 12; keep in sync with C struct layout.
    let m: *u8 = module;
    let ntl: i32 = (m[12] as i32)
      | ((m[13] as i32) << 8)
      | ((m[14] as i32) << 16)
      | ((m[15] as i32) << 24);
    let msg2: u8[120] = [];
    let at2: i32 = driver_diag_append_cstr(&msg2[0], 120, 0, "pipeline debug: after_entry_parse num_top_level_lets=");
    at2 = driver_diag_append_i32(&msg2[0], 120, at2, ntl);
    driver_diag_note(&msg2[0]);
  }
}

/** CG003 when codegen fails to emit one function. Reads name via pipeline_module_func_name_*
 * (G.7 authority; not a second name path). Assembles
 * "failed to emit function 'NAME' (idx=N)" with append; empty name -> "?".
 * Path: check-only note + diag_report_with_code("codegen error","CG003",msg). No va_list reportf.
 * PLATFORM: SHARED — pure authority in thin.x; cold seed keeps C body; FROM_X no pure-dup _impl. */
#[no_mangle]
export function driver_diagnostic_codegen_emit_func_fail(module: *u8, func_index: i32): void {
  unsafe {
    if (module == 0 as *u8) {
      return;
    }
    if (func_index < 0) {
      return;
    }
    let nl: i32 = pipeline_module_func_name_len_at(module, func_index);
    let namebuf: u8[80] = [];
    let out_i: i32 = 0;
    let k: i32 = 0;
    while (k < nl && k < 72) {
      namebuf[out_i] = pipeline_module_func_name_byte_at(module, func_index, k);
      out_i = out_i + 1;
      k = k + 1;
    }
    namebuf[out_i] = 0;
    let msg: u8[200] = [];
    let at: i32 = driver_diag_append_cstr(&msg[0], 200, 0, "failed to emit function '");
    if (out_i > 0) {
      at = driver_diag_append_cstr(&msg[0], 200, at, &namebuf[0]);
    } else {
      at = driver_diag_append_cstr(&msg[0], 200, at, "?");
    }
    at = driver_diag_append_cstr(&msg[0], 200, at, "' (idx=");
    at = driver_diag_append_i32(&msg[0], 200, at, func_index);
    at = driver_diag_append_cstr(&msg[0], 200, at, ")");
    if (driver_check_only_get() != 0) {
      driver_check_diag_emitted_note();
    }
    diag_report_with_code(0 as *u8, 0, 0, "codegen error", "CG003", &msg[0], 0 as *u8);
  }
}

// wave6: lsp_diag_get_enabled is export-extern at file head (G.7 glue authority).
// No local definition — avoids dual authority with runtime_lsp_glue.

/** Hybrid ld -r slice marker (return 1). Pure authority under PREFER; cold seed keeps C.
 * PLATFORM: SHARED — FROM_X rest has no pure-dup marker. */
#[no_mangle]
export function runtime_driver_diagnostic_slice_marker(): i32 {
  return 1;
}
