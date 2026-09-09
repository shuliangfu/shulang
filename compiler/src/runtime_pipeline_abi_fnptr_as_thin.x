// Thin pure override: Cap-fn-ptr EXPR_AS (same-module fn as *u8 / TYPE_FN).
// G.7: bodies MUST match pipeline_asm_emit_as_elf_impl / _c in runtime_pipeline_abi.x.
// Cap-fn-ptr LEA spell is pipe_modlet_lea_fn_sym_to_rax (mega authority);
// this thin must not keep a second Mach-O '_' / ELF bare copy.
// ensure injects via first-wins ld -r so product need not full mega -E
// (Darwin mega -E hang-prone / memory).
// PLATFORM: SHARED freestanding cast emit · LINUX gold · MACOS underscore.

export extern function glue_expr_is_await_at_c(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_asm_emit_await_sync_elf_impl(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32;
export extern function pipeline_expr_as_operand_ref_at(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_as_target_type_ref_at(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_type_kind_ord_at(arena: *u8, type_ref: i32): i32;
export extern function pipeline_expr_kind_ord_at(arena: *u8, expr_ref: i32): i32;
export extern function glue_emit_float_lit_to_rax_elf_c(arena: *u8, elf_ctx: *u8, op: i32, ta: i32, tgt: i32, widen: i32): i32;
export extern function pipeline_expr_resolved_type_ref(arena: *u8, expr_ref: i32): i32;
export extern function glue_binop_operand_is_scalar_f64_elf_c(arena: *u8, ctx: *u8, op: i32): i32;
export extern function pipeline_asm_emit_expr_elf_c(arena: *u8, elf_ctx: *u8, op: i32, ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvttss2si_eax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvttsd2si_eax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvttss2si_rax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvttsd2si_rax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2ss_eax_from_i32_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2ss_eax_from_i64_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2ss_eax_from_u64_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsd2ss_eax_from_f64_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2sd_rax_from_u64_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2sd_rax_from_i64_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtsi2sd_rax_from_i32_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_cvtss2sd_rax_from_f32_bits_arch(elf_ctx: *u8, ta: i32): i32;
export extern function pipeline_elf_ctx_append_bytes(elf_ctx: *u8, ptr: *u8, n: i32): i32;
export extern function glue_var_expr_stack_off_elf_c(arena: *u8, ctx: *u8, var_expr_ref: i32): i32;
export extern function pipeline_expr_var_name_len(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_var_name_into(arena: *u8, expr_ref: i32, out64: *u8): void;
export extern function glue_emit_module_from_ctx(ctx: *u8): *u8;
export extern function glue_module_func_index_by_name_c(mod: *u8, name: *u8, name_len: i32): i32;
export extern function pipe_modlet_lea_fn_sym_to_rax(elf_ctx: *u8, name: *u8, name_len: i32, ta: i32): i32;

/**
 * Product-mega freestanding EXPR_AS ELF face (int/float cast family).
 * Routes await via sync stub; float-lit f32 force_ty; float↔int / int↔float / f32↔f64.
 * @param arena *u8 - ASTArena*
 * @param elf_ctx *u8 - ElfCodegenCtx*
 * @param expr_ref i32 - AS or await expr
 * @param ctx *u8 - AsmFuncCtx*
 * @param ta i32 - target arch
 * @return i32 - 0 ok; -1 failure
 * wave138 pure: G.7 authority (was pipeline_asm_emit_as_elf_impl).
 * Cap residual: emit_expr_elf_c + cast encoders + f32/f64 classifiers +
 *   float_lit face + elf append (u32 zext mov eax,eax).
 * Cap-fn-ptr (10.3.2 / 10.3.1): bare fn as *u8 or TYPE_FN → LEA link
 *   symbol into rax/x0 via pipe_modlet_lea_fn_sym_to_rax (any same-module
 *   fn; locals win over same-named funcs). No second spell in this thin.
 * PLATFORM: SHARED freestanding cast emit · LINUX gold · MACOS underscore.
 */
#[no_mangle]
export function pipeline_asm_emit_as_elf_impl(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32 {
  let op: i32 = 0;
  let tgt: i32 = 0;
  let tgt_kind: i32 = 0;
  let src_tr: i32 = 0;
  let src_kind: i32 = 0;
  let op_ko: i32 = 0;
  let src_is_f32: i32 = 0;
  let src_is_f64: i32 = 0;
  let rc: i32 = 0;
  let mov_eax: u8[2] = [];
  // Cap-fn-ptr scratch; kept at top for .x let discipline.
  // 9.4.2: the Mach-O '_' / ELF bare spell lives in pipe_modlet_lea_fn_sym_to_rax.
  let fnptr_off: i32 = 0;
  let fnptr_vlen: i32 = 0;
  let fnptr_fi: i32 = 0;
  let fnptr_mod: *u8 = 0 as *u8;
  let fnptr_vname: u8[128] = [];
  if (glue_expr_is_await_at_c(arena, expr_ref) != 0) {
    return pipeline_asm_emit_await_sync_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  unsafe {
    op = pipeline_expr_as_operand_ref_at(arena, expr_ref);
  }
  if (op == 0) {
    return 0 - 1;
  }
  unsafe {
    tgt = pipeline_expr_as_target_type_ref_at(arena, expr_ref);
  }
  if (tgt > 0) {
    unsafe {
      tgt_kind = pipeline_type_kind_ord_at(arena, tgt);
      op_ko = pipeline_expr_kind_ord_at(arena, op);
    }
    // f32 target + FLOAT_LIT force_ty
    if (tgt_kind == 14 && op_ko == 1) {
      return glue_emit_float_lit_to_rax_elf_c(arena, elf_ctx, op, ta, tgt, 0);
    }
  }
  // float → integer truncate
  if (tgt > 0) {
    unsafe {
      tgt_kind = pipeline_type_kind_ord_at(arena, tgt);
      src_tr = pipeline_expr_resolved_type_ref(arena, op);
    }
    if (src_tr > 0) {
      unsafe {
        src_kind = pipeline_type_kind_ord_at(arena, src_tr);
      }
    } else {
      src_kind = 0 - 1;
    }
    unsafe {
      op_ko = pipeline_expr_kind_ord_at(arena, op);
    }
    src_is_f32 = 0;
    src_is_f64 = 0;
    if (src_kind == 14) {
      src_is_f32 = 1;
    }
    if (src_kind == 15 || (src_kind <= 0 && op_ko == 1)) {
      src_is_f64 = 1;
    }
    if (src_is_f64 == 0) {
      unsafe {
        if (glue_binop_operand_is_scalar_f64_elf_c(arena, ctx, op) != 0) {
          src_is_f64 = 1;
        }
      }
    }
    if (src_is_f32 != 0 || src_is_f64 != 0) {
      if (tgt_kind == 0 || tgt_kind == 3) {
        unsafe {
          rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (src_is_f32 != 0) {
          unsafe {
            rc = backend_enc_cvttss2si_eax_from_f32_bits_arch(elf_ctx, ta);
          }
          return rc;
        }
        unsafe {
          rc = backend_enc_cvttsd2si_eax_from_f64_bits_arch(elf_ctx, ta);
        }
        return rc;
      }
      if (tgt_kind == 4 || tgt_kind == 5 || tgt_kind == 6 || tgt_kind == 7) {
        unsafe {
          rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (src_is_f32 != 0) {
          unsafe {
            rc = backend_enc_cvttss2si_rax_from_f32_bits_arch(elf_ctx, ta);
          }
          return rc;
        }
        unsafe {
          rc = backend_enc_cvttsd2si_rax_from_f64_bits_arch(elf_ctx, ta);
        }
        return rc;
      }
    }
  }
  // integer → f32
  if (tgt > 0) {
    unsafe {
      tgt_kind = pipeline_type_kind_ord_at(arena, tgt);
    }
    if (tgt_kind == 14) {
      unsafe {
        src_tr = pipeline_expr_resolved_type_ref(arena, op);
      }
      if (src_tr > 0) {
        unsafe {
          src_kind = pipeline_type_kind_ord_at(arena, src_tr);
        }
        if (src_kind == 0 || src_kind == 2 || src_kind == 8) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2ss_eax_from_i32_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 3) {
          mov_eax[0] = 137 as u8; // 0x89
          mov_eax[1] = 192 as u8; // 0xc0
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = pipeline_elf_ctx_append_bytes(elf_ctx, &mov_eax[0], 2);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2ss_eax_from_i64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 4 || src_kind == 6) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2ss_eax_from_u64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 5 || src_kind == 7) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2ss_eax_from_i64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 15) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsd2ss_eax_from_f64_bits_arch(elf_ctx, ta);
          }
          return rc;
        }
        unsafe {
          if (glue_binop_operand_is_scalar_f64_elf_c(arena, ctx, op) != 0) {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
            if (rc != 0) {
              return 0 - 1;
            }
            rc = backend_enc_cvtsd2ss_eax_from_f64_bits_arch(elf_ctx, ta);
            return rc;
          }
        }
      }
    }
  }
  // integer → f64
  if (tgt > 0) {
    unsafe {
      tgt_kind = pipeline_type_kind_ord_at(arena, tgt);
    }
    if (tgt_kind == 15) {
      unsafe {
        src_tr = pipeline_expr_resolved_type_ref(arena, op);
      }
      if (src_tr > 0) {
        unsafe {
          src_kind = pipeline_type_kind_ord_at(arena, src_tr);
        }
        if (src_kind == 4 || src_kind == 6) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2sd_rax_from_u64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 5 || src_kind == 7) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2sd_rax_from_i64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 3) {
          mov_eax[0] = 137 as u8;
          mov_eax[1] = 192 as u8;
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = pipeline_elf_ctx_append_bytes(elf_ctx, &mov_eax[0], 2);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2sd_rax_from_i64_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 0 || src_kind == 2 || src_kind == 8) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtsi2sd_rax_from_i32_arch(elf_ctx, ta);
          }
          return rc;
        }
        if (src_kind == 14) {
          unsafe {
            rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_cvtss2sd_rax_from_f32_bits_arch(elf_ctx, ta);
          }
          return rc;
        }
      }
    }
  }
  // Cap-fn-ptr: (same_module_fn as *u8|TYPE_FN) → LEA of link symbol (rax/x0).
  // Complements wave100 typeck Cap-fn-ptr + C codegen_try_emit_fn_as_value.
  // Locals (stack slot) win over same-named funcs.
  // PLATFORM: SHARED · MACOS Mach-O leading '_' · LINUX ELF bare name
  // (spell is pipe_modlet_lea_fn_sym_to_rax; this thin does not copy it).
  if (tgt > 0) {
    unsafe {
      tgt_kind = pipeline_type_kind_ord_at(arena, tgt);
      op_ko = pipeline_expr_kind_ord_at(arena, op);
    }
    // TYPE_PTR=9 · TYPE_FN=18 · EXPR_VAR=3
    if ((tgt_kind == 9 || tgt_kind == 18) && op_ko == 3) {
      unsafe {
        fnptr_off = glue_var_expr_stack_off_elf_c(arena, ctx, op);
      }
      if (fnptr_off < 0) {
        unsafe {
          fnptr_vlen = pipeline_expr_var_name_len(arena, op);
        }
        if (fnptr_vlen > 0 && fnptr_vlen < 128) {
          unsafe {
            pipeline_expr_var_name_into(arena, op, &fnptr_vname[0]);
            fnptr_mod = glue_emit_module_from_ctx(ctx);
          }
          if (fnptr_mod != (0 as *u8)) {
            unsafe {
              fnptr_fi = glue_module_func_index_by_name_c(fnptr_mod, &fnptr_vname[0], fnptr_vlen);
            }
            if (fnptr_fi >= 0) {
              // Cap-fn-ptr: load effective address of any same-module function into rax/x0.
              // 9.4.2: symbol spell (Mach-O '_' / ELF bare) is the
              // pipe_modlet_lea_fn_sym_to_rax authority.
              unsafe {
                rc = pipe_modlet_lea_fn_sym_to_rax(elf_ctx, &fnptr_vname[0], fnptr_vlen, ta);
              }
              return rc;
            }
          }
        }
      }
    }
  }
  unsafe {
    rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, op, ctx, ta);
  }
  return rc;
}

/**
 * Public EXPR_AS ELF face (thin delegate to as_elf_impl).
 * @param arena *u8 - ASTArena*
 * @param elf_ctx *u8 - ElfCodegenCtx*
 * @param expr_ref i32 - AS expr
 * @param ctx *u8 - AsmFuncCtx*
 * @param ta i32 - target arch
 * @return i32 - 0 ok; -1 failure
 * wave138 pure: G.7 authority (was pipeline_asm_emit_as_elf_c).
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function pipeline_asm_emit_as_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32 {
  return pipeline_asm_emit_as_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
}
