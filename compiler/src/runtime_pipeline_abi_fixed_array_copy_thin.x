// Thin pure override: dest-ARRAY-of-ARRAY / return Path B0 memcpy size
// plus dest extras dest-ARRAY of ARRAY extra `[K][N][]T` flatten.
// G.7: bodies MUST match glue_struct_lit_store_fixed_array_field_elf_c,
// pipeline_asm_emit_return_elf_impl, and pipeline_asm_emit_array_lit_flat_elf_c
// in runtime_pipeline_abi.x (same symbols).
// Peel-then-measure via glue_index_elem_byte_sz(elem) copied only the first
// row of [K][N]T (asm run=3). This leaf uses glue_array_lit_force_esz_from_elem_type
// (TYPE_ARRAY → glue_fixed_array_total_bytes). Twin of 4.2.7 nested SLICE esz.
// ensure injects via first-wins ld -r so product need not full mega -E.
// PLATFORM: SHARED freestanding · LINUX gold · MACOS|ARM64 co-path.


export extern function glue_align_next_offset(ctx: *u8): void;
export extern function glue_array_lit_force_esz_from_elem_type_c(arena: *u8, et: i32): i32;
export extern function glue_asm_emit_array_lit_durable_ptr_rax_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, force_esz: i32, ta: i32, ctx: *u8, dest_elem_ty: i32): i32;
export extern function glue_asm_lea_rax_common_adrp_arm64(elf_ctx: *u8, name: *u8, name_len: i32): i32;
export extern function glue_asm_lea_rax_common_rip_x86(elf_ctx: *u8, name: *u8, name_len: i32): i32;
export extern function glue_async_cps_emit_phase_reset(elf_ctx: *u8, ta: i32): i32;
export extern function glue_emit_bulk_mem_copy_spills_elf_c(elf_ctx: *u8, src_spill: i32, dst_spill: i32, esz: i32, ta: i32): i32;
export extern function glue_emit_index_eff_addr_scaled_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, base_ref: i32, idx_ref: i32, ctx: *u8, ta: i32, esz: i32): i32;
export extern function glue_emit_sret_memcpy_rbx_to_home_elf_c(elf_ctx: *u8, nbytes: i32, ta: i32): i32;
export extern function glue_emit_sret_return_from_var_elf_c(arena: *u8, elf_ctx: *u8, var_ref: i32, ctx: *u8, ta: i32): i32;
export extern function glue_enc_local_slot_ptr_or_addr_elf_c(arena: *u8, elf_ctx: *u8, var_ref: i32, off: i32, ctx: *u8, ta: i32): i32;
export extern function glue_field_access_effective_offset_c(arena: *u8, mod: *u8, fa_ref: i32): i32;
export extern function glue_fixed_array_total_bytes_c(arena: *u8, ty_ref: i32, depth: i32): i32;
export extern function glue_float_promote_src_ty_ref_c(arena: *u8, expr_ref: i32): i32;
export extern function glue_index_elem_byte_sz_from_type_ref_c(arena: *u8, tr: i32): i32;
export extern function glue_index_scratch_spills_cleanup_all_elf_c(elf_ctx: *u8, ta: i32): i32;
export extern function glue_maybe_promote_f32_to_f64_rax_elf_c(arena: *u8, elf_ctx: *u8, rty: i32, sty: i32, ta: i32): i32;
export extern function glue_peel_as_array_slice_ascription_c(arena: *u8, expr_ref: i32): i32;
export extern function glue_pipeline_asm_al_nc_seq_take_c(): i32;
export extern function glue_struct_field_frame_mag_c(base_off: i32, foff: i32, ta: i32): i32;
export extern function glue_try_index_var_or_field_base_to_rax_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32;
export extern function glue_try_return_slice_escape_from_fixed_array_elf_c(arena: *u8, elf_ctx: *u8, ret_op: i32, ctx: *u8, ta: i32): i32;
export extern function glue_var_expr_stack_off_elf_c(arena: *u8, ctx: *u8, var_ref: i32): i32;
export extern function pipe_asm_ctx_off_next_offset(): i32;
export extern function pipe_load_i32_le(base: *u8, off: i32): i32;
export extern function pipe_store_i32_le(base: *u8, off: i32, v: i32): void;
export extern function pipeline_asm_bump_next_offset_for_array_lit(arena: *u8, expr_ref: i32, ctx: *u8): void;
export extern function pipeline_asm_ctx_layout(ctx: *u8): *u8;
export extern function pipeline_asm_emit_array_lit_force_esz_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32, force_esz: i32): i32;
export extern function pipeline_asm_emit_ctx_sret_active_get(): i32;
export extern function pipeline_asm_emit_ctx_sret_home_off_get(): i32;
export extern function pipeline_asm_emit_ctx_sret_ret_sz_get(): i32;
export extern function pipeline_asm_emit_expr_elf_c(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32;
export extern function pipeline_asm_emit_func_index_c(): i32;
export extern function pipeline_asm_emit_module_ref_c(): *u8;
export extern function pipeline_asm_emit_vector_let_init_elf_c(arena: *u8, elf_ctx: *u8, init_ref: i32, ctx: *u8, ta: i32, stack_slot_off: i32): i32;
export extern function pipeline_elf_ctx_add_common_sym(ctx_bytes: *u8, name: *u8, name_len: i32, sym_size: i32, sym_align: i32): i32;
export extern function pipeline_expr_array_lit_elem_ref(arena: *u8, expr_ref: i32, idx: i32): i32;
export extern function pipeline_expr_array_lit_num_elems_at(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_base_ref(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_is_enum_variant(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_index_base_ref(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_index_index_ref(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_int64_val_at(arena: *u8, expr_ref: i32): i64;
export extern function pipeline_expr_kind_ord_at(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_resolved_type_ref(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_unary_operand_ref_at(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_module_func_return_type_at(mod: *u8, fi: i32): i32;
export extern function pipeline_type_array_size_at(arena: *u8, type_ref: i32): i32;
export extern function pipeline_type_elem_ref_at(arena: *u8, type_ref: i32): i32;
export extern function pipeline_type_kind_ord_at(arena: *u8, type_ref: i32): i32;
export extern function backend_enc_add_imm_to_rax_arch(elf_ctx: *u8, imm: i32, ta: i32): i32;
export extern function backend_enc_jmp_arch(elf_ctx: *u8, label: *u8, label_len: i32, ta: i32): i32;
export extern function backend_enc_lea_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern function backend_enc_load_64_from_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_load_i32_indirect_to_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_load_rbp_to_rax_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern function backend_enc_load_rbp_to_rbx_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern function backend_enc_load_zext8_from_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_mov_imm64_to_rax_arch(elf_ctx: *u8, lo: i32, hi: i32, ta: i32): i32;
export extern function backend_enc_mov_rax_to_arg_reg_arch(elf_ctx: *u8, k: i32, ta: i32): i32;
export extern function backend_enc_mov_rax_to_rbx_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_pop_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_push_rax_arch(elf_ctx: *u8, ta: i32): i32;
export extern function backend_enc_store_rax_to_rbp_arch(elf_ctx: *u8, offset: i32, ta: i32): i32;
export extern function backend_enc_store_rax_to_rbx_offset_arch(elf_ctx: *u8, off: i32, load_sz: i32, ta: i32): i32;
export extern function pipeline_asm_array_lit_elem_type_ref(arena: *u8, array_lit_expr_ref: i32): i32;
export extern function glue_emit_fixed_array_type_let_init_elf_c(arena: *u8, elf_ctx: *u8, init_ref: i32, ctx: *u8, ta: i32, type_ref: i32, stack_slot_off: i32): i32;
export extern function glue_emit_struct_type_let_init_elf_c(arena: *u8, elf_ctx: *u8, init_ref: i32, ctx: *u8, ta: i32, let_ty_ref: i32, stack_slot_off: i32): i32;
export extern function glue_emit_slice_from_array_let_init_elf_c(arena: *u8, elf_ctx: *u8, block_ref: i32, let_idx: i32, init_ref: i32, let_type_ref: i32, ctx: *u8, ta: i32, slice_slot_off: i32): i32;
export extern function glue_array_lit_emit_scalar_elem_to_rax_elf_c(arena: *u8, elf_ctx: *u8, array_lit_ref: i32, elem_ref: i32, ctx: *u8, ta: i32, force_esz: i32): i32;
export extern function glue_expr_emit_may_clobber_rbx_elf_c(arena: *u8, expr_ref: i32): i32;
export extern function glue_type_size_simple(mod: *u8, arena: *u8, ty_ref: i32, depth: i32): i32;
export extern function glue_type_named_layout_size_any_module_elf_c(arena: *u8, ty_ref: i32): i32;
export extern function glue_call_arg_resolve_var_stack_off_elf_c(arena: *u8, ctx: *u8, var_ref: i32): i32;
export extern function asm_local_var_slot_holds_indirect_ptr(arena: *u8, var_ref: i32, mod: *u8, ctx: *u8): i32;
export extern function pipeline_expr_var_name_len(arena: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_var_name_into(arena: *u8, expr_ref: i32, dst: *u8): void;
export extern function pipeline_module_num_funcs(mod: *u8): i32;
export extern function pipeline_module_func_param_type_ref_for_name(mod: *u8, fi: i32, name: *u8, nlen: i32): i32;
export extern function asm_ctx_scope_block_ref_at(ctx: *u8): i32;
export extern function pipeline_block_resolve_var_type_ref(arena: *u8, br: i32, name: *u8, nlen: i32): i32;
export extern function glue_type_ref_is_named_struct_layout_elf_c(arena: *u8, mod: *u8, ty_ref: i32): i32;
export extern function glue_type_is_fixed_array(arena: *u8, ty_ref: i32): i32;
export extern function glue_emit_func_param_is_indirect_array_slot_c(arena: *u8, mod: *u8, var_ref: i32): i32;

/**
 * CALL-arg VAR: lea stack payload only for MEMORY >16B named structs / T[N].
 * INTEGER-class ≤16B (including unknown size_simple=0 → 8B) must load bits.
 * G.7: first-wins twin of runtime_pipeline_abi.x wave190.
 * PLATFORM: LINUX+MACOS x86_64 SysV INTEGER load; MACOS|ARM64 x0 bits.
 * @param arena *u8 — ASTArena*; null → 0
 * @param expr_ref i32 — EXPR_VAR ref
 * @param ctx *u8 — AsmFuncCtx*
 * @return i32 — 1 use lea; 0 use load / unknown
 */
#[no_mangle]
export function glue_call_arg_var_use_lea_not_load_elf_c(arena: *u8, expr_ref: i32, ctx: *u8): i32 {
  let mod: *u8 = 0 as *u8;
  let holds: i32 = 0;
  let ko: i32 = 0;
  let vname: u8[128] = [];
  let vlen: i32 = 0;
  let fi: i32 = 0;
  let nf: i32 = 0;
  let pty: i32 = 0;
  let tk: i32 = 0;
  let scope_br: i32 = 0;
  let decl_ty: i32 = 0;
  let sz: i32 = 0;
  if (arena == (0 as *u8) || ctx == (0 as *u8) || expr_ref <= 0) {
    return 0;
  }
  mod = pipeline_asm_emit_module_ref_c();
  unsafe {
    holds = asm_local_var_slot_holds_indirect_ptr(arena, expr_ref, mod, ctx);
  }
  if (holds != 0) {
    return 0;
  }
  unsafe {
    ko = pipeline_expr_kind_ord_at(arena, expr_ref);
  }
  if (ko != 3) {
    return 0;
  }
  unsafe {
    vlen = pipeline_expr_var_name_len(arena, expr_ref);
  }
  if (vlen <= 0 || vlen > 127) {
    return 0;
  }
  unsafe {
    pipeline_expr_var_name_into(arena, expr_ref, &vname[0]);
  }
  fi = pipeline_asm_emit_func_index_c();
  if (mod != (0 as *u8) && fi >= 0) {
    unsafe {
      nf = pipeline_module_num_funcs(mod);
    }
    if (fi < nf) {
      unsafe {
        pty = pipeline_module_func_param_type_ref_for_name(mod, fi, &vname[0], vlen);
      }
      if (pty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, pty);
        }
        if (tk == 9) {
          return 0;
        }
      }
    }
  }
  unsafe {
    scope_br = asm_ctx_scope_block_ref_at(ctx);
  }
  decl_ty = 0;
  if (scope_br > 0) {
    unsafe {
      decl_ty = pipeline_block_resolve_var_type_ref(arena, scope_br, &vname[0], vlen);
    }
  }
  if (decl_ty <= 0) {
    unsafe {
      decl_ty = pipeline_expr_resolved_type_ref(arena, expr_ref);
    }
  }
  if (decl_ty <= 0) {
    return 0;
  }
  if (glue_type_ref_is_named_struct_layout_elf_c(arena, mod, decl_ty) != 0) {
    sz = glue_type_size_simple(mod, arena, decl_ty, 0);
    if (sz <= 0) {
      sz = glue_type_named_layout_size_any_module_elf_c(arena, decl_ty);
    }
    if (sz > 16) {
      return 1;
    }
    return 0;
  }
  if (glue_type_is_fixed_array(arena, decl_ty) != 0) {
    if (mod != (0 as *u8) && fi >= 0) {
      if (glue_emit_func_param_is_indirect_array_slot_c(arena, mod, expr_ref) != 0) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

/**
 * EXPR_RETURN ELF emit impl (sret / slice escape / ARRAY_LIT dual-GP / float / tail_join).
 * Path B0 also durables VAR/FIELD/INDEX [N]T → dest []T (fat) or dest T[N] (E*).
 * @param arena *u8 — AST arena
 * @param elf_ctx *u8 — ELF codegen ctx
 * @param expr_ref i32 — EXPR_RETURN
 * @param ctx *u8 — asm func ctx
 * @param ta i32 — 0 x86_64 SysV / 1 arm64 AAPCS64
 * @return i32 — 0 ok; -1 fail
 * wave144 pure: G.7 authority (was static pipeline_asm_emit_return_elf_impl).
 * Public for expr_rec residual callsite. Operand emit uses public emit_expr_elf_c.
 * PLATFORM: SHARED freestanding · LINUX gold · MACOS|ARM64.
 */
#[no_mangle]
export function pipeline_asm_emit_return_elf_impl(arena: *u8, elf_ctx: *u8, expr_ref: i32, ctx: *u8, ta: i32): i32 {
  let ly: *u8 = 0 as *u8;
  let ret_op: i32 = 0;
  let sret_act: i32 = 0;
  let sret_sz: i32 = 0;
  let ko: i32 = 0;
  let esc: i32 = 0;
  let mod: *u8 = 0 as *u8;
  let fi: i32 = 0;
  let rty: i32 = 0;
  let sty: i32 = 0;
  let tk: i32 = 0;
  let slice_ty: i32 = 0;
  let n_arr: i32 = 0;
  let force_esz: i32 = 0;
  let durable: i32 = 0;
  let len_arg: i32 = 0;
  let rc: i32 = 0;
  let tj_len: i32 = 0;
  let tj_lbl: u8[128] = [];
  let ti: i32 = 0;
  let handled: i32 = 0;
  let ret_off: i32 = 0;
  let ret_named_sz: i32 = 0;
  let rar_elem: i32 = 0;
  let rar_src: i32 = 0;
  let rar_dst: i32 = 0;
  let rar_noff: i32 = 0;
  let rar_seq: i32 = 0;
  let rar_llen: i32 = 0;
  let rar_nd: i32 = 0;
  let rar_di: i32 = 0;
  let rar_v: i32 = 0;
  let rar_lbl: u8[24] = [];
  let rar_digs: u8[8] = [];
  ly = pipeline_asm_ctx_layout(ctx);
  unsafe {
    ret_op = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
  }
  if (ret_op != 0) {
    // Identity ascription: `return [10,32] as []i32` must hit Path C ARRAY_LIT.
    ret_op = glue_peel_as_array_slice_ascription_c(arena, ret_op);
    handled = 0;
    unsafe {
      sret_act = pipeline_asm_emit_ctx_sret_active_get();
      sret_sz = pipeline_asm_emit_ctx_sret_ret_sz_get();
      ko = pipeline_expr_kind_ord_at(arena, ret_op);
      mod = pipeline_asm_emit_module_ref_c();
      fi = pipeline_asm_emit_func_index_c();
    }
    /* Path A0: INTEGER-class ≤8B named struct `return local`. Load the 8
     * bits into rax/x0. STRUCT_LIT / emit_expr used to lea the slot when
     * value_bytes sized 0, so Ubuntu SysV returned a callee-local pointer
     * and `free()` aborted on ArrowColumn. AAPCS64 8B already in x0 bits
     * (mac false-green). Do not sret (that path is >16B MEMORY).
     * G.7: must match runtime_pipeline_abi.x (this thin is first-wins inject).
     * PLATFORM: LINUX+MACOS x86_64 SysV INTEGER rax; MACOS|ARM64 x0. */
    if (handled == 0 && ko == 3 && (ta == 0 || ta == 1) && mod != (0 as *u8) && fi >= 0) {
      unsafe {
        rty = pipeline_module_func_return_type_at(mod, fi);
      }
      if (rty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, rty);
        }
        if (tk == 8) {
          ret_named_sz = glue_type_size_simple(mod, arena, rty, 0);
          force_esz = glue_type_named_layout_size_any_module_elf_c(arena, rty);
          if (force_esz > ret_named_sz) {
            ret_named_sz = force_esz;
          }
          if (ret_named_sz <= 8) {
            ret_off = glue_call_arg_resolve_var_stack_off_elf_c(arena, ctx, ret_op);
            if (ret_off < 0) {
              unsafe {
                ret_off = glue_var_expr_stack_off_elf_c(arena, ctx, ret_op);
              }
            }
            if (ret_off >= 0) {
              unsafe {
                rc = backend_enc_load_rbp_to_rax_arch(elf_ctx, ret_off, ta);
              }
              if (rc != 0) {
                return 0 - 1;
              }
              handled = 1;
            }
          }
        }
      }
    }
    // Path A: sret return local VAR of large struct
    if (handled == 0 && sret_act != 0 && sret_sz > 16 && (ta == 0 || ta == 1) && ko == 3) {
      if (glue_emit_sret_return_from_var_elf_c(arena, elf_ctx, ret_op, ctx, ta) != 0) {
        return 0 - 1;
      }
      handled = 1;
    }
    // Path A2: sret return INDEX of large struct. emit_index esz>16 leaves
    // the element address in rax — same pointer as VAR slot lea. Reuse
    // glue_emit_sret_memcpy_rbx_to_home (rbx = src). Do not memcpy inside
    // emit_index and do not widen the frozen CALL-only classifier.
    // PLATFORM: SHARED freestanding · LINUX+MACOS SysV · MACOS|ARM64 AAPCS64.
    if (handled == 0 && sret_act != 0 && sret_sz > 16 && (ta == 0 || ta == 1) && ko == 47) {
      unsafe {
        rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, ret_op, ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (glue_emit_sret_memcpy_rbx_to_home_elf_c(elf_ctx, sret_sz, ta) != 0) {
        return 0 - 1;
      }
      handled = 1;
    }
    // Path B0: already-typed [N]T VAR/FIELD/INDEX → []T (fat) or T[N] (E*).
    // Durable COMMON copy then either dual-GP (dest SLICE) or rax=E*
    // (dest TYPE_ARRAY). Stack view / lea-local dangles after return
    // (wave342 / 4.2.17 `return s` of S24[2] SEGV). Do not stamp.
    // INDEX (`return a[0]` of [K][N]T): return/assign do not stamp, so
    // N+elem-esz come from the INDEX TYPE_ARRAY; lea scale is the row
    // total (glue_fixed_array_total_bytes). Do not emit_index (esz>8
    // leaves a raw addr and never packs dest-SLICE length).
    // Keep esz>8 (wave632 NAMED); only weird mid widths 3/5/6/7 → 4.
    // G.7: reuse lea helpers + bulk_mem_copy + Path C dual-GP pack.
    // PLATFORM: SHARED freestanding · LINUX+MACOS SysV · MACOS|ARM64.
    if (handled == 0 && arena != (0 as *u8) && ctx != (0 as *u8) && elf_ctx != (0 as *u8)
    && (ta == 0 || ta == 1) && (ko == 3 || ko == 44 || ko == 47) && mod != (0 as *u8) && fi >= 0) {
      unsafe {
        rty = pipeline_module_func_return_type_at(mod, fi);
        sty = pipeline_expr_resolved_type_ref(arena, ret_op);
      }
      slice_ty = 0;
      if (rty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, rty);
        }
        // dest SLICE=11 (fat) or dest TYPE_ARRAY=10 (E*). slice_ty holds dest.
        if (tk == 11 || tk == 10) {
          slice_ty = rty;
        }
      }
      n_arr = 0;
      force_esz = 0;
      if (slice_ty > 0 && sty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, sty);
        }
        if (tk == 10) {
          unsafe {
            n_arr = pipeline_type_array_size_at(arena, sty);
            rar_elem = pipeline_type_elem_ref_at(arena, sty);
          }
          if (rar_elem > 0) {
            unsafe {
              /* Same peel-then-measure as dest-ARRAY memcpy: rar_elem of
               * [K][N]T is TYPE_ARRAY and index-esz peels to leaf 4B.
               * Durable COMMON then holds one row; dest copy run=3.
               * G.7: glue_array_lit_force_esz_from_elem_type (sizeof row).
               * PLATFORM: SHARED freestanding return Path B0. */
              force_esz = glue_array_lit_force_esz_from_elem_type_c(arena, rar_elem);
            }
          }
          if (force_esz <= 0) {
            force_esz = 4;
          }
          // wave632: keep esz>8 large NAMED; weird mid widths 3/5/6/7 → 4.
          if (force_esz != 1 && force_esz != 2 && force_esz != 4 && force_esz != 8 && force_esz <= 8) {
            force_esz = 4;
          }
        }
      }
      // Scalar face 4KiB; large NAMED up to 64KiB (wave632).
      if (n_arr > 0 && n_arr <= 1024 && force_esz > 0) {
        if (force_esz > 8) {
          if (n_arr > (65536 / force_esz)) {
            n_arr = 0;
          }
        } else {
          if (n_arr > (4096 / force_esz)) {
            n_arr = 0;
          }
        }
      } else {
        n_arr = 0;
      }
      if (n_arr > 0) {
        if (ko == 3) {
          unsafe {
            rar_src = glue_var_expr_stack_off_elf_c(arena, ctx, ret_op);
          }
          if (rar_src < 0) {
            n_arr = 0;
          } else {
            unsafe {
              rc = glue_enc_local_slot_ptr_or_addr_elf_c(arena, elf_ctx, ret_op, rar_src, ctx, ta);
            }
            if (rc != 0) {
              return 0 - 1;
            }
          }
        } else if (ko == 47) {
          // INDEX row: lea scale = sizeof([N]T), not dest-SLICE 16.
          // rar_src/dst hold base/index refs only until the spill slots below.
          unsafe {
            rar_src = pipeline_expr_index_base_ref(arena, ret_op);
            rar_dst = pipeline_expr_index_index_ref(arena, ret_op);
            rar_noff = glue_fixed_array_total_bytes_c(arena, sty, 0);
          }
          if (rar_src <= 0 || rar_dst <= 0 || rar_noff <= 0) {
            n_arr = 0;
          } else {
            unsafe {
              rc = glue_emit_index_eff_addr_scaled_elf_c(arena, elf_ctx, ret_op, rar_src, rar_dst, ctx, ta, rar_noff);
            }
            if (rc != 0) {
              return 0 - 1;
            }
          }
        } else {
          unsafe {
            rc = glue_try_index_var_or_field_base_to_rax_elf_c(arena, elf_ctx, ret_op, ctx, ta);
          }
          if (rc == (0 - 1)) {
            return 0 - 1;
          }
          if (rc != 0) {
            n_arr = 0;
          }
        }
      } else {
        n_arr = 0;
      }
      if (n_arr > 0) {
        rar_noff = pipe_load_i32_le(ctx, pipe_asm_ctx_off_next_offset());
        if (rar_noff + 48 < rar_noff) {
          return 0 - 1;
        }
        rar_noff = rar_noff + 16;
        rar_src = rar_noff;
        rar_noff = rar_noff + 16;
        rar_dst = rar_noff;
        pipe_store_i32_le(ctx, pipe_asm_ctx_off_next_offset(), rar_noff + 16);
        glue_align_next_offset(ctx);
        unsafe {
          rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, rar_src, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rar_seq = glue_pipeline_asm_al_nc_seq_take_c();
        }
        if (rar_seq < 0 || rar_seq > 999999) {
          rar_seq = 0;
        }
        // "Lxlang_rar_"
        rar_lbl[0] = 76 as u8; rar_lbl[1] = 120 as u8; rar_lbl[2] = 108 as u8;
        rar_lbl[3] = 97 as u8; rar_lbl[4] = 110 as u8; rar_lbl[5] = 103 as u8;
        rar_lbl[6] = 95 as u8; rar_lbl[7] = 114 as u8; rar_lbl[8] = 97 as u8;
        rar_lbl[9] = 114 as u8; rar_lbl[10] = 95 as u8;
        rar_llen = 11;
        rar_v = rar_seq;
        rar_nd = 0;
        if (rar_v == 0) {
          rar_digs[0] = 48 as u8;
          rar_nd = 1;
        } else {
          while (rar_v > 0 && rar_nd < 8) {
            rar_digs[rar_nd] = (48 + (rar_v % 10)) as u8;
            rar_nd = rar_nd + 1;
            rar_v = rar_v / 10;
          }
        }
        rar_di = rar_nd - 1;
        while (rar_di >= 0 && rar_llen < 23) {
          rar_lbl[rar_llen] = rar_digs[rar_di];
          rar_llen = rar_llen + 1;
          rar_di = rar_di - 1;
        }
        unsafe {
          rc = pipeline_elf_ctx_add_common_sym(elf_ctx, &rar_lbl[0], rar_llen, n_arr * force_esz, force_esz);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (ta == 1) {
          unsafe {
            rc = glue_asm_lea_rax_common_adrp_arm64(elf_ctx, &rar_lbl[0], rar_llen);
          }
        } else {
          unsafe {
            rc = glue_asm_lea_rax_common_rip_x86(elf_ctx, &rar_lbl[0], rar_llen);
          }
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, rar_dst, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = glue_emit_bulk_mem_copy_spills_elf_c(elf_ctx, rar_src, rar_dst, n_arr * force_esz, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (ta == 1) {
          unsafe {
            rc = glue_asm_lea_rax_common_adrp_arm64(elf_ctx, &rar_lbl[0], rar_llen);
          }
        } else {
          unsafe {
            rc = glue_asm_lea_rax_common_rip_x86(elf_ctx, &rar_lbl[0], rar_llen);
          }
        }
        if (rc != 0) {
          return 0 - 1;
        }
        // dest SLICE: pack length (dual-GP). dest TYPE_ARRAY: rax is already E*.
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, slice_ty);
        }
        if (tk == 11) {
          unsafe {
            rc = backend_enc_push_rax_arch(elf_ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_mov_imm64_to_rax_arch(elf_ctx, n_arr, 0, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          if (ta == 1) {
            len_arg = 1;
          } else {
            len_arg = 2;
          }
          unsafe {
            rc = backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, len_arg, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
          unsafe {
            rc = backend_enc_pop_rax_arch(elf_ctx, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
        }
        handled = 1;
      }
    }
    // Path B: VAR + module — slice escape or emit+float promote
    if (handled == 0 && arena != (0 as *u8) && ctx != (0 as *u8) && elf_ctx != (0 as *u8) && (ta == 0 || ta == 1) && ko == 3 && mod != (0 as *u8) && fi >= 0) {
      esc = glue_try_return_slice_escape_from_fixed_array_elf_c(arena, elf_ctx, ret_op, ctx, ta);
      if (esc < 0) {
        return 0 - 1;
      }
      if (esc == 0) {
        unsafe {
          rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, ret_op, ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rty = pipeline_module_func_return_type_at(mod, fi);
        }
        sty = glue_float_promote_src_ty_ref_c(arena, ret_op);
        if (glue_maybe_promote_f32_to_f64_rax_elf_c(arena, elf_ctx, rty, sty, ta) != 0) {
          return 0 - 1;
        }
      }
      handled = 1;
    }
    // Path C: ARRAY_LIT + module — durable TYPE_ARRAY / dual-GP TYPE_SLICE
    if (handled == 0 && arena != (0 as *u8) && ctx != (0 as *u8) && elf_ctx != (0 as *u8) && (ta == 0 || ta == 1) && ko == 46 && mod != (0 as *u8) && fi >= 0) {
      unsafe {
        rty = pipeline_module_func_return_type_at(mod, fi);
        sty = pipeline_expr_resolved_type_ref(arena, ret_op);
      }
      slice_ty = 0;
      if (rty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, rty);
        }
        if (tk == 11) {
          slice_ty = rty;
        }
      }
      if (slice_ty == 0 && sty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, sty);
        }
        if (tk == 11) {
          slice_ty = sty;
        }
      }
      if (slice_ty == 0 && rty > 0) {
        unsafe {
          tk = pipeline_type_kind_ord_at(arena, rty);
        }
        if (tk == 10) {
          unsafe {
            n_arr = pipeline_expr_array_lit_num_elems_at(arena, ret_op);
            force_esz = glue_array_lit_force_esz_from_elem_type_c(arena, pipeline_type_elem_ref_at(arena, rty));
          }
          if (n_arr < 0 || n_arr > 1024) {
            return 0 - 1;
          }
          unsafe {
            rc = glue_asm_emit_array_lit_durable_ptr_rax_elf_c(arena, elf_ctx, ret_op, force_esz, ta, ctx, pipeline_type_elem_ref_at(arena, rty));
          }
          if (rc != 0) {
            unsafe {
              rc = pipeline_asm_emit_array_lit_force_esz_elf_c(arena, elf_ctx, ret_op, ctx, ta, force_esz);
            }
            if (rc != 0) {
              return 0 - 1;
            }
            if (n_arr > 0) {
              unsafe {
                pipeline_asm_bump_next_offset_for_array_lit(arena, ret_op, ctx);
              }
            }
          }
          handled = 1;
        }
      }
      if (handled == 0 && slice_ty > 0) {
        unsafe {
          n_arr = pipeline_expr_array_lit_num_elems_at(arena, ret_op);
          force_esz = glue_array_lit_force_esz_from_elem_type_c(arena, pipeline_type_elem_ref_at(arena, slice_ty));
        }
        if (n_arr < 0 || n_arr > 1024) {
          return 0 - 1;
        }
        durable = 0;
        unsafe {
          rc = glue_asm_emit_array_lit_durable_ptr_rax_elf_c(arena, elf_ctx, ret_op, force_esz, ta, ctx, pipeline_type_elem_ref_at(arena, slice_ty));
        }
        if (rc == 0) {
          durable = 1;
        } else {
          unsafe {
            rc = pipeline_asm_emit_array_lit_force_esz_elf_c(arena, elf_ctx, ret_op, ctx, ta, force_esz);
          }
          if (rc != 0) {
            return 0 - 1;
          }
        }
        unsafe {
          rc = backend_enc_push_rax_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_mov_imm64_to_rax_arch(elf_ctx, n_arr, 0, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (ta == 1) {
          len_arg = 1;
        } else {
          len_arg = 2;
        }
        unsafe {
          rc = backend_enc_mov_rax_to_arg_reg_arch(elf_ctx, len_arg, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_pop_rax_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (durable == 0 && n_arr > 0) {
          unsafe {
            pipeline_asm_bump_next_offset_for_array_lit(arena, ret_op, ctx);
          }
        }
        handled = 1;
      }
      if (handled == 0) {
        unsafe {
          rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, ret_op, ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rty = pipeline_module_func_return_type_at(mod, fi);
        }
        sty = glue_float_promote_src_ty_ref_c(arena, ret_op);
        if (glue_maybe_promote_f32_to_f64_rax_elf_c(arena, elf_ctx, rty, sty, ta) != 0) {
          return 0 - 1;
        }
        handled = 1;
      }
    }
    // Path D: general operand emit + float promote
    if (handled == 0) {
      unsafe {
        rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, ret_op, ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (mod != (0 as *u8) && fi >= 0) {
        unsafe {
          rty = pipeline_module_func_return_type_at(mod, fi);
        }
        sty = glue_float_promote_src_ty_ref_c(arena, ret_op);
        if (glue_maybe_promote_f32_to_f64_rax_elf_c(arena, elf_ctx, rty, sty, ta) != 0) {
          return 0 - 1;
        }
      }
    }
  }
  unsafe {
    rc = glue_index_scratch_spills_cleanup_all_elf_c(elf_ctx, ta);
  }
  if (rc != 0) {
    return 0 - 1;
  }
  rc = glue_async_cps_emit_phase_reset(elf_ctx, ta);
  if (rc != 0) {
    return 0 - 1;
  }
  if (ly == (0 as *u8)) {
    return 0 - 1;
  }
  tj_len = pipe_load_i32_le(ly, 1520);
  if (tj_len <= 0) {
    return 0 - 1;
  }
  ti = 0;
  while (ti < tj_len && ti < 128) {
    unsafe {
      tj_lbl[ti] = ly[1392 + ti];
    }
    ti = ti + 1;
  }
  unsafe {
    return backend_enc_jmp_arch(elf_ctx, &tj_lbl[0], tj_len, ta);
  }
}

/**
 * STRUCT_LIT fixed TYPE_ARRAY field store / fixed-array let element-wise authority.
 * Handles ARRAY_LIT, zero LIT, VAR/FIELD, CALL/METHOD/INDEX (E* + bulk esz>8).
 * @param arena *u8 - ASTArena*
 * @param elf_ctx *u8 - ElfCodegenCtx*
 * @param init_ref i32 - field/let init expr ref
 * @param ctx *u8 - AsmFuncCtx*
 * @param ta i32 - target arch
 * @param sret_direct i32 - 0=frame mag dest; non-0=sret true address + foff
 * @param base_off i32 - Outer byte0 frame magnitude (or unused when sret)
 * @param foff i32 - field byte offset from Outer byte0
 * @param fty i32 - fixed TYPE_ARRAY type ref
 * @return i32 - 0 handled; -1 error; -2 unsupported init
 * wave146 pure: G.7 authority (was static glue_struct_lit_store_fixed_array_field_elf_c).
 * PLATFORM: SHARED freestanding · LINUX gold · MACOS|ARM64 co-path.
 */
#[no_mangle]
export function glue_struct_lit_store_fixed_array_field_elf_c(arena: *u8, elf_ctx: *u8, init_ref: i32, ctx: *u8, ta: i32, sret_direct: i32, base_off: i32, foff: i32, fty: i32): i32 {
  let iko: i32 = 0;
  let n_arr: i32 = 0;
  let esz: i32 = 0;
  let ai: i32 = 0;
  let elem_tr: i32 = 0;
  let src_off: i32 = 0;
  let field_mag: i32 = 0;
  let elem_ref: i32 = 0;
  let lit_v: i64 = 0;
  let var_base: i32 = 0;
  let var_off: i32 = 0;
  let field_off: i32 = 0;
  let is_enum: i32 = 0;
  let ko_base: i32 = 0;
  let ly: *u8 = 0 as *u8;
  let spill_off: i32 = 0;
  let emit_rc: i32 = 0;
  let next_off: i32 = 0;
  let src_spill: i32 = 0;
  let dst_spill: i32 = 0;
  let total: i32 = 0;
  let sret_home: i32 = 0;
  let mod: *u8 = 0 as *u8;
  let rc: i32 = 0;
  let store_off: i32 = 0;
  let empty_array_zero: i32 = 0;
  let lit_n: i32 = 0;
  let src: i32 = 0;
  if (arena == (0 as *u8) || elf_ctx == (0 as *u8) || ctx == (0 as *u8) || init_ref <= 0 || fty <= 0) {
    return 0 - 1;
  }
  src = glue_peel_as_array_slice_ascription_c(arena, init_ref);
  if (src <= 0) {
    src = init_ref;
  }
  unsafe {
    iko = pipeline_expr_kind_ord_at(arena, src);
    n_arr = pipeline_type_array_size_at(arena, fty);
  }
  if (n_arr <= 0 && iko == 46) {
    unsafe {
      n_arr = pipeline_expr_array_lit_num_elems_at(arena, src);
    }
  }
  // Empty ARRAY_LIT `[]` has 0 elems; type size still supplies n_arr for zero-fill.
  // Per-elem paths still cap at 1024; empty / zero-fill may be larger (skip body if huge).
  if (n_arr <= 0) {
    return 0 - 1;
  }
  unsafe {
    elem_tr = pipeline_type_elem_ref_at(arena, fty);
    /* Outer stride of dest TYPE_ARRAY = sizeof(elem). Peel-then-measure
     * via glue_index_elem_byte_sz(elem) is wrong for [K][N]T: elem is
     * TYPE_ARRAY and index-esz peels again to sizeof(leaf) (4 for i32),
     * so VAR/CALL dest memcpy copies only the first row (asm run=3;
     * named-local `let r = t` same). G.7: reuse
     * glue_array_lit_force_esz_from_elem_type (TYPE_ARRAY →
     * glue_fixed_array_total_bytes). Twin of 4.2.7 nested SLICE esz
     * (pass the compound, do not peel then measure).
     * PLATFORM: SHARED freestanding dest-ARRAY memcpy · LINUX gold. */
    esz = glue_array_lit_force_esz_from_elem_type_c(arena, elem_tr);
  }
  if (esz <= 0) {
    unsafe {
      esz = glue_index_elem_byte_sz_from_type_ref_c(arena, fty);
    }
  }
  if (esz <= 0) {
    esz = 4;
  }
  field_mag = 0;
  if (sret_direct == 0) {
    field_mag = glue_struct_field_frame_mag_c(base_off, foff, ta);
    if (field_mag < 0) {
      return 0 - 1;
    }
  }

  // EXPR_ARRAY_LIT = 46.
  // Empty `[]` ≡ product zero-init (host-C `{0}`) — fall through to wave363 zero path.
  // Non-empty still uses vector_let_init (caps at 1024 elems).
  // PLATFORM: SHARED freestanding — Stage 12.2.7 CG002 root (struct field `data: []`).
  if (iko == 46) {
    unsafe {
      lit_n = pipeline_expr_array_lit_num_elems_at(arena, src);
    }
    if (lit_n == 0) {
      empty_array_zero = 1;
    } else if (n_arr > 1024) {
      return 0 - 1;
    } else if (sret_direct == 0) {
      return pipeline_asm_emit_vector_let_init_elf_c(arena, elf_ctx, src, ctx, ta, field_mag);
    } else {
      unsafe {
        sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
      }
      ai = 0;
      while (ai < n_arr) {
        unsafe {
          elem_ref = pipeline_expr_array_lit_elem_ref(arena, src, ai);
        }
        if (elem_ref == 0) {
          ai = ai + 1;
          continue;
        }
        unsafe {
          rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, elem_ref, ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_push_rax_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_load_rbp_to_rbx_arch(elf_ctx, sret_home, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_pop_rax_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, foff + ai * esz, esz, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        ai = ai + 1;
      }
      return 0;
    }
  }

  // wave363: let a: T[N] = 0 zero-fill (+ empty ARRAY_LIT `[]` via empty_array_zero).
  // n_arr > 1024: accept without per-elem stores (avoids multi-MiB instruction blast;
  // product multi-MiB buffers use heap ensure / uninit+assign, not STRUCT_LIT zero).
  if (iko == 0 || empty_array_zero != 0) {
    if (empty_array_zero == 0) {
      unsafe {
        lit_v = pipeline_expr_int64_val_at(arena, init_ref);
      }
      if (lit_v != (0 as i64)) {
        return 0 - 2;
      }
    }
    if (n_arr > 1024) {
      return 0;
    }
    if (sret_direct == 0) {
      unsafe {
        rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, field_mag, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_mov_imm64_to_rax_arch(elf_ctx, 0, 0, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      ai = 0;
      while (ai < n_arr) {
        unsafe {
          rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, ai * esz, esz, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        ai = ai + 1;
      }
      return 0;
    }
    unsafe {
      sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
    }
    unsafe {
      rc = backend_enc_mov_imm64_to_rax_arch(elf_ctx, 0, 0, ta);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    ai = 0;
    while (ai < n_arr) {
      unsafe {
        rc = backend_enc_push_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_load_rbp_to_rbx_arch(elf_ctx, sret_home, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_pop_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, foff + ai * esz, esz, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      ai = ai + 1;
    }
    return 0;
  }

  src_off = 0 - 1;
  if (iko == 3) {
    unsafe {
      src_off = glue_var_expr_stack_off_elf_c(arena, ctx, src);
    }
  } else if (iko == 44) {
    unsafe {
      is_enum = pipeline_expr_field_access_is_enum_variant(arena, src);
    }
    if (is_enum != 0) {
      return 0 - 2;
    }
    unsafe {
      var_base = pipeline_expr_field_access_base_ref(arena, src);
    }
    if (var_base <= 0) {
      return 0 - 2;
    }
    unsafe {
      ko_base = pipeline_expr_kind_ord_at(arena, var_base);
    }
    if (ko_base != 3) {
      return 0 - 2;
    }
    unsafe {
      var_off = glue_var_expr_stack_off_elf_c(arena, ctx, var_base);
    }
    if (var_off < 0) {
      return 0 - 1;
    }
    mod = pipeline_asm_emit_module_ref_c();
    unsafe {
      field_off = glue_field_access_effective_offset_c(arena, mod, src);
    }
    if (field_off < 0) {
      field_off = 0;
    }
    src_off = glue_struct_field_frame_mag_c(var_off, field_off, ta);
    if (src_off < 0) {
      return 0 - 1;
    }
  } else if (iko == 48 || iko == 49 || iko == 47 || iko == 52) {
    /* CALL=48 / METHOD=49 / INDEX=47 / DEREF=52: emit leaves E* (TYPE_ARRAY
     * return / subrow / emit_deref trk==10 leave-ptr). Same payload copy.
     * `unsafe { let y: [N]T = *p }` used to fall through to -2 → CG002.
     * PLATFORM: SHARED freestanding · LINUX gold · MACOS|ARM64 co-path. */
    ly = pipeline_asm_ctx_layout(ctx);
    if (ly == (0 as *u8)) {
      return 0 - 1;
    }
    next_off = pipe_load_i32_le(ly, pipe_asm_ctx_off_next_offset());
    if (next_off + 16 < next_off) {
      return 0 - 1;
    }
    next_off = next_off + 16;
    pipe_store_i32_le(ly, pipe_asm_ctx_off_next_offset(), next_off);
    spill_off = next_off;
    unsafe {
      emit_rc = pipeline_asm_emit_expr_elf_c(arena, elf_ctx, src, ctx, ta);
    }
    if (emit_rc != 0) {
      return 0 - 1;
    }
    unsafe {
      rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, spill_off, ta);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    if (esz > 8) {
      if (esz > 4096) {
        return 0 - 1;
      }
      total = n_arr * esz;
      if (total <= 0 || total > 4096) {
        return 0 - 1;
      }
      next_off = pipe_load_i32_le(ly, pipe_asm_ctx_off_next_offset());
      if (next_off + 32 < next_off) {
        return 0 - 1;
      }
      next_off = next_off + 16;
      src_spill = next_off;
      next_off = next_off + 16;
      dst_spill = next_off;
      pipe_store_i32_le(ly, pipe_asm_ctx_off_next_offset(), next_off);
      unsafe {
        rc = backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, src_spill, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        unsafe {
          rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, field_mag, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      } else {
        unsafe {
      sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
    }
        unsafe {
          rc = backend_enc_load_rbp_to_rax_arch(elf_ctx, sret_home, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (foff != 0) {
          unsafe {
            rc = backend_enc_add_imm_to_rax_arch(elf_ctx, foff, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
        }
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, dst_spill, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = glue_emit_bulk_mem_copy_spills_elf_c(elf_ctx, src_spill, dst_spill, total, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      return 0;
    }
    unsafe {
      sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
    }
    ai = 0;
    while (ai < n_arr) {
      unsafe {
        rc = backend_enc_load_rbp_to_rax_arch(elf_ctx, spill_off, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (ai * esz != 0) {
        unsafe {
          rc = backend_enc_add_imm_to_rax_arch(elf_ctx, ai * esz, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      }
      if (esz == 1) {
        unsafe {
          rc = backend_enc_load_zext8_from_rax_arch(elf_ctx, ta);
        }
      } else if (esz == 8) {
        unsafe {
          rc = backend_enc_load_64_from_rax_arch(elf_ctx, ta);
        }
      } else {
        unsafe {
          rc = backend_enc_load_i32_indirect_to_rax_arch(elf_ctx, ta);
        }
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_push_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        unsafe {
          rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, field_mag, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      } else {
        unsafe {
          rc = backend_enc_load_rbp_to_rbx_arch(elf_ctx, sret_home, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      }
      unsafe {
        rc = backend_enc_pop_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        store_off = ai * esz;
      } else {
        store_off = foff + ai * esz;
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, store_off, esz, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      ai = ai + 1;
    }
    return 0;
  }

  if (src_off >= 0) {
    if (esz > 8) {
      ly = pipeline_asm_ctx_layout(ctx);
      if (ly == (0 as *u8)) {
        return 0 - 1;
      }
      if (esz > 4096) {
        return 0 - 1;
      }
      total = n_arr * esz;
      if (total <= 0 || total > 4096) {
        return 0 - 1;
      }
      next_off = pipe_load_i32_le(ly, pipe_asm_ctx_off_next_offset());
      if (next_off + 32 < next_off) {
        return 0 - 1;
      }
      next_off = next_off + 16;
      src_spill = next_off;
      next_off = next_off + 16;
      dst_spill = next_off;
      pipe_store_i32_le(ly, pipe_asm_ctx_off_next_offset(), next_off);
      unsafe {
        rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, src_off, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, src_spill, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        unsafe {
          rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, field_mag, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      } else {
        unsafe {
      sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
    }
        unsafe {
          rc = backend_enc_load_rbp_to_rax_arch(elf_ctx, sret_home, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        if (foff != 0) {
          unsafe {
            rc = backend_enc_add_imm_to_rax_arch(elf_ctx, foff, ta);
          }
          if (rc != 0) {
            return 0 - 1;
          }
        }
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbp_arch(elf_ctx, dst_spill, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = glue_emit_bulk_mem_copy_spills_elf_c(elf_ctx, src_spill, dst_spill, total, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      return 0;
    }
    unsafe {
      sret_home = pipeline_asm_emit_ctx_sret_home_off_get();
    }
    ai = 0;
    while (ai < n_arr) {
      unsafe {
        rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, src_off, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (ai * esz != 0) {
        unsafe {
          rc = backend_enc_add_imm_to_rax_arch(elf_ctx, ai * esz, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      }
      if (esz == 1) {
        unsafe {
          rc = backend_enc_load_zext8_from_rax_arch(elf_ctx, ta);
        }
      } else if (esz == 8) {
        unsafe {
          rc = backend_enc_load_64_from_rax_arch(elf_ctx, ta);
        }
      } else {
        unsafe {
          rc = backend_enc_load_i32_indirect_to_rax_arch(elf_ctx, ta);
        }
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_push_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        unsafe {
          rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, field_mag, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
        unsafe {
          rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      } else {
        unsafe {
          rc = backend_enc_load_rbp_to_rbx_arch(elf_ctx, sret_home, ta);
        }
        if (rc != 0) {
          return 0 - 1;
        }
      }
      unsafe {
        rc = backend_enc_pop_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      if (sret_direct == 0) {
        store_off = ai * esz;
      } else {
        store_off = foff + ai * esz;
      }
      unsafe {
        rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, store_off, esz, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      ai = ai + 1;
    }
    return 0;
  }

  return 0 - 2;
}

/**
 * Flatten nested ARRAY_LIT to row-major scalar/struct stores at base+flat_i*leaf_esz.
 * dest extras dest-ARRAY of ARRAY extra `[K][N][]T`: dest elem is TYPE_ARRAY
 * of SLICE. Flatten used to write i32 leaves (asg run=1 / extra SIGSEGV 139).
 * Direct elem TYPE_SLICE → per-cell glue_emit_slice_from_array_let_init
 * (same writer as dest-ARRAY extra `[2][]i32`). `[K][N]i32` dest elem is
 * ARRAY of scalar — keep flatten. Do not invent -3.
 * G.7: body MUST match pipeline_asm_emit_array_lit_flat_elf_c in
 * runtime_pipeline_abi.x (first-wins ld -r).
 * @param arena *u8 — ASTArena*
 * @param elf_ctx *u8 — ElfCodegenCtx*
 * @param init_ref i32 — ARRAY_LIT expr ref
 * @param ctx *u8 — AsmFuncCtx*
 * @param ta i32 — 0=x86 high-end, 1=arm64 low-end
 * @param stack_slot_off i32 — array base frame magnitude
 * @param leaf_esz i32 — scalar/leaf element byte size
 * @param flat_i *i32 — running flat index (in/out)
 * @return i32 — 0 ok; -1 error
 * PLATFORM: SHARED freestanding multi-dim · LINUX|x86 · MACOS|ARM64.
 */
#[no_mangle]
export function pipeline_asm_emit_array_lit_flat_elf_c(arena: *u8, elf_ctx: *u8, init_ref: i32, ctx: *u8, ta: i32, stack_slot_off: i32, leaf_esz: i32, flat_i: *i32): i32 {
  let n_arr: i32 = 0;
  let ai: i32 = 0;
  let elem_ref: i32 = 0;
  let store_sz: i32 = 0;
  let ko: i32 = 0;
  let elem_home: i32 = 0;
  let st: i32 = 0;
  let may_clobber: i32 = 0;
  let rc: i32 = 0;
  let fi: i32 = 0;
  let dest_elem: i32 = 0;
  let dest_ek: i32 = 0;
  let inner: i32 = 0;
  let inner_k: i32 = 0;
  let row_esz: i32 = 0;
  let row_home: i32 = 0;
  let cell_home: i32 = 0;
  let n_inner: i32 = 0;
  let ji: i32 = 0;
  let cell_ref: i32 = 0;
  let row_st: i32 = 0;
  if (arena == (0 as *u8) || elf_ctx == (0 as *u8) || ctx == (0 as *u8) || flat_i == (0 as *i32) || init_ref <= 0 || leaf_esz <= 0) {
    return 0 - 1;
  }
  unsafe {
    ko = pipeline_expr_kind_ord_at(arena, init_ref);
  }
  if (ko != 46) {
    return 0 - 1;
  }
  unsafe {
    n_arr = pipeline_expr_array_lit_num_elems_at(arena, init_ref);
  }
  if (n_arr < 0 || n_arr > 1024) {
    return 0 - 1;
  }
  dest_elem = pipeline_asm_array_lit_elem_type_ref(arena, init_ref);
  if (dest_elem > 0) {
    unsafe {
      dest_ek = pipeline_type_kind_ord_at(arena, dest_elem);
    }
    if (dest_ek == 10) {
      unsafe {
        inner = pipeline_type_elem_ref_at(arena, dest_elem);
      }
      if (inner > 0) {
        unsafe {
          inner_k = pipeline_type_kind_ord_at(arena, inner);
        }
      }
      if (inner_k == 11) {
        row_esz = glue_array_lit_force_esz_from_elem_type_c(arena, dest_elem);
        if (row_esz <= 0) {
          return 0 - 1;
        }
        ai = 0;
        while (ai < n_arr && ai < 1024) {
          unsafe {
            elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, ai);
            ko = pipeline_expr_kind_ord_at(arena, elem_ref);
          }
          if (elem_ref > 0) {
            if (ta == 1) {
              row_home = stack_slot_off + ai * row_esz;
            } else {
              row_home = stack_slot_off - ai * row_esz;
            }
            if (row_home < 0) {
              return 0 - 1;
            }
            if (ko == 46) {
              unsafe {
                n_inner = pipeline_expr_array_lit_num_elems_at(arena, elem_ref);
              }
              ji = 0;
              while (ji < n_inner && ji < 1024) {
                unsafe {
                  cell_ref = pipeline_expr_array_lit_elem_ref(arena, elem_ref, ji);
                }
                if (cell_ref > 0) {
                  if (ta == 1) {
                    cell_home = row_home + ji * 16;
                  } else {
                    cell_home = row_home - ji * 16;
                  }
                  if (cell_home < 0) {
                    return 0 - 1;
                  }
                  row_st = glue_emit_slice_from_array_let_init_elf_c(
                      arena, elf_ctx, 0, 0, cell_ref, inner, ctx, ta, cell_home);
                  if (row_st != 1) {
                    return 0 - 1;
                  }
                }
                ji = ji + 1;
              }
            } else {
              unsafe {
                row_st = glue_emit_fixed_array_type_let_init_elf_c(
                    arena, elf_ctx, elem_ref, ctx, ta, dest_elem, row_home);
              }
              if (row_st != 0) {
                return 0 - 1;
              }
            }
          }
          ai = ai + 1;
        }
        unsafe {
          fi = flat_i[0];
          flat_i[0] = fi + n_arr;
        }
        return 0;
      }
    }
  }
  store_sz = leaf_esz;
  if (store_sz != 1 && store_sz != 2 && store_sz != 4 && store_sz != 8) {
    store_sz = 4;
  }
  ai = 0;
  while (ai < n_arr && ai < 1024) {
    unsafe {
      elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, ai);
    }
    if (elem_ref == 0) {
      ai = ai + 1;
      continue;
    }
    unsafe {
      ko = pipeline_expr_kind_ord_at(arena, elem_ref);
    }
    if (ko == 46) {
      rc = pipeline_asm_emit_array_lit_flat_elf_c(arena, elf_ctx, elem_ref, ctx, ta, stack_slot_off, leaf_esz, flat_i);
      if (rc != 0) {
        return 0 - 1;
      }
      ai = ai + 1;
      continue;
    }
    if (leaf_esz > 8 || ko == 45) {
      unsafe {
        fi = flat_i[0];
      }
      if (ta == 1) {
        elem_home = stack_slot_off + fi * leaf_esz;
      } else {
        elem_home = stack_slot_off - fi * leaf_esz;
      }
      if (elem_home < 0) {
        return 0 - 1;
      }
      st = glue_emit_struct_type_let_init_elf_c(arena, elf_ctx, elem_ref, ctx, ta, 0, elem_home);
      if (st == 0) {
        unsafe {
          fi = flat_i[0];
          flat_i[0] = fi + 1;
        }
        ai = ai + 1;
        continue;
      }
      if (st == 0 - 1) {
        return 0 - 1;
      }
    }
    unsafe {
      rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, stack_slot_off, ta);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    unsafe {
      rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    unsafe {
      may_clobber = glue_expr_emit_may_clobber_rbx_elf_c(arena, elem_ref);
      rc = glue_array_lit_emit_scalar_elem_to_rax_elf_c(arena, elf_ctx, init_ref, elem_ref, ctx, ta, leaf_esz);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    if (may_clobber != 0) {
      unsafe {
        rc = backend_enc_push_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_lea_rbp_to_rax_arch(elf_ctx, stack_slot_off, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_mov_rax_to_rbx_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
      unsafe {
        rc = backend_enc_pop_rax_arch(elf_ctx, ta);
      }
      if (rc != 0) {
        return 0 - 1;
      }
    }
    unsafe {
      fi = flat_i[0];
      rc = backend_enc_store_rax_to_rbx_offset_arch(elf_ctx, fi * leaf_esz, store_sz, ta);
    }
    if (rc != 0) {
      return 0 - 1;
    }
    unsafe {
      fi = flat_i[0];
      flat_i[0] = fi + 1;
    }
    ai = ai + 1;
  }
  return 0;
}
