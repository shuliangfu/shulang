// Thin pure override: FIELD_ACCESS load width (CORE-016 generic mono).
// G.7: body MUST match pipeline_expr_field_access_load_byte_sz in
// runtime_pipeline_abi.x (same exported symbol). Prefer typeck-resolved
// scalar (mono stamp) before generic-layout free TYPE_NAMED T/U so
// Option<i32>.value / Wrap<i32>.v emit ldr w not ldr x0 with garbage
// high bits (multi-let / multi-mono compare false-red).
// ensure injects via pipeline_abi_inject_field_load_sz_thin (first-wins
// ld -r; avoids Darwin mega -E 22-40GB RSS).
// PLATFORM: SHARED freestanding field load · LINUX gold · MACOS co-path.

export extern function pipeline_expr_field_access_base_ref(a: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_name_len(a: *u8, expr_ref: i32): i32;
export extern function pipeline_expr_field_access_name_into(a: *u8, expr_ref: i32, out: *u8): void;
export extern function pipeline_expr_resolved_type_ref(a: *u8, expr_ref: i32): i32;
export extern function pipeline_type_kind_ord_at(a: *u8, ty_ref: i32): i32;
export extern function pipeline_type_elem_ref_at(a: *u8, ref: i32): i32;
export extern function pipeline_type_named_name_into(a: *u8, ty_ref: i32, out: *u8): i32;
export extern function pipeline_module_num_struct_layouts_at(m: *u8): i32;
export extern function pipeline_module_struct_layout_name_len(m: *u8, k: i32): i32;
export extern function pipeline_module_struct_layout_name_byte_at(m: *u8, k: i32, j: i32): i32;
export extern function pipeline_module_struct_layout_num_fields(m: *u8, k: i32): i32;
export extern function pipeline_module_struct_layout_field_name_len(m: *u8, k: i32, j: i32): i32;
export extern function pipeline_module_struct_layout_field_name_into(m: *u8, k: i32, j: i32, out: *u8): void;
export extern function pipeline_module_struct_layout_field_type_ref(m: *u8, k: i32, j: i32): i32;
export extern function glue_field_access_load_bytes_for_type_ref(a: *u8, ty_ref: i32): i32;

/**
 * Compare n bytes at a and b; 1 if equal, else 0.
 * @param a *u8 — left bytes
 * @param b *u8 — right bytes
 * @param n i32 — length; n<=0 → 1
 * @return i32 — 1 equal, 0 mismatch
 * PLATFORM: SHARED — thin-local twin of wave151_bytes_eq (no mega link).
 */
function field_load_sz_bytes_eq(a: *u8, b: *u8, n: i32): i32 {
  let i: i32 = 0;
  if (n <= 0) {
    return 1;
  }
  if (a == (0 as *u8) || b == (0 as *u8)) {
    return 0;
  }
  while (i < n) {
    if (a[i] != b[i]) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}

/**
 * FIELD_ACCESS load width (base-layout / resolved / is_some|is_none heuristic).
 *
 * Order (G.7 typed-first — do not scan all layouts by bare field name):
 *  1. Field expr resolved scalar type width (typeck mono stamp). CORE-016.
 *  2. Base TYPE_NAMED layout match then field type width; skip free TYPE_NAMED.
 *  3. is_some / is_none name → 1.
 *  4. Default 8.
 *
 * @param a *u8 - ASTArena*
 * @param m *u8 - Module*
 * @param expr_ref i32 - FIELD_ACCESS expr ref
 * @return i32 - load byte size
 * PLATFORM: SHARED — G.7 thin twin of runtime_pipeline_abi.x authority.
 */
#[no_mangle]
export function pipeline_expr_field_access_load_byte_sz(a: *u8, m: *u8, expr_ref: i32): i32 {
  let tr: i32 = 0;
  let base_tr: i32 = 0;
  let base_ref: i32 = 0;
  let struct_name: u8[128] = [];
  let nlen: i32 = 0;
  let flen: i32 = 0;
  let field_name: u8[128] = [];
  let k: i32 = 0;
  let j: i32 = 0;
  let ftr: i32 = 0;
  let kind_ord: i32 = 0;
  let ftr_kind: i32 = 0;
  let nsl: i32 = 0;
  let nf: i32 = 0;
  let fnlen: i32 = 0;
  let feq: i32 = 0;
  let fi: i32 = 0;
  let fb: u8[128] = [];
  let ln: i32 = 0;
  let eq: i32 = 0;
  let nm_is_some: u8[7] = [105, 115, 95, 115, 111, 109, 101];
  let nm_is_none: u8[7] = [105, 115, 95, 110, 111, 110, 101];
  if (a == (0 as *u8) || expr_ref <= 0) {
    return 8;
  }
  unsafe {
    base_ref = pipeline_expr_field_access_base_ref(a, expr_ref);
    flen = pipeline_expr_field_access_name_len(a, expr_ref);
  }
  if (base_ref <= 0 || flen <= 0 || flen > 127) {
    return 8;
  }
  unsafe {
    pipeline_expr_field_access_name_into(a, expr_ref, &field_name[0]);
  }
  /* CORE-016: prefer typeck mono scalar stamp before generic layout T/U → 8. */
  unsafe {
    tr = pipeline_expr_resolved_type_ref(a, expr_ref);
  }
  if (tr > 0) {
    unsafe {
      kind_ord = pipeline_type_kind_ord_at(a, tr);
    }
    if (kind_ord != 8 && kind_ord != 10 && kind_ord != 11 && kind_ord != 12) {
      return glue_field_access_load_bytes_for_type_ref(a, tr);
    }
  }
  unsafe {
    base_tr = pipeline_expr_resolved_type_ref(a, base_ref);
  }
  if (base_tr > 0) {
    unsafe {
      kind_ord = pipeline_type_kind_ord_at(a, base_tr);
    }
    /* PLATFORM: SHARED — dep parse-only bases are POINTER params (`s: *S`,
     * stamped by the block_ref backfill); peel TYPE_PTR (9) to the element
     * so the layout match runs (else i32 field loads fall to the 8-byte
     * default and drag padding garbage into address math — std.string
     * append_char SEGV). Must match the runtime_pipeline_abi.x twin. */
    if (kind_ord == 9) {
      unsafe {
        let elem_tr_lbs: i32 = pipeline_type_elem_ref_at(a, base_tr);
        if (elem_tr_lbs > 0) {
          base_tr = elem_tr_lbs;
          kind_ord = pipeline_type_kind_ord_at(a, base_tr);
        }
      }
    }
    if (kind_ord == 8) {
      unsafe {
        nlen = pipeline_type_named_name_into(a, base_tr, &struct_name[0]);
      }
      if (nlen > 0 && nlen <= 63 && m != (0 as *u8)) {
        unsafe {
          nsl = pipeline_module_num_struct_layouts_at(m);
        }
        k = 0;
        while (k < nsl) {
          unsafe {
            ln = pipeline_module_struct_layout_name_len(m, k);
          }
          eq = 1;
          if (ln != nlen) {
            eq = 0;
          } else {
            j = 0;
            while (j < nlen) {
              unsafe {
                if (pipeline_module_struct_layout_name_byte_at(m, k, j) != (struct_name[j] as i32)) {
                  eq = 0;
                  break;
                }
              }
              j = j + 1;
            }
          }
          if (eq != 0) {
            unsafe {
              nf = pipeline_module_struct_layout_num_fields(m, k);
            }
            j = 0;
            while (j < nf) {
              unsafe {
                fnlen = pipeline_module_struct_layout_field_name_len(m, k, j);
              }
              feq = 1;
              if (fnlen != flen) {
                feq = 0;
              } else {
                unsafe {
                  pipeline_module_struct_layout_field_name_into(m, k, j, &fb[0]);
                }
                fi = 0;
                while (fi < fnlen) {
                  if (fb[fi] != field_name[fi]) {
                    feq = 0;
                    break;
                  }
                  fi = fi + 1;
                }
              }
              if (feq != 0) {
                unsafe {
                  ftr = pipeline_module_struct_layout_field_type_ref(m, k, j);
                  ftr_kind = pipeline_type_kind_ord_at(a, ftr);
                }
                if (ftr_kind != 8) {
                  return glue_field_access_load_bytes_for_type_ref(a, ftr);
                }
              }
              j = j + 1;
            }
          }
          k = k + 1;
        }
      }
    }
  }
  if (flen == 7 && field_load_sz_bytes_eq(&field_name[0], &nm_is_some[0], 7) != 0) {
    return 1;
  }
  if (flen == 7 && field_load_sz_bytes_eq(&field_name[0], &nm_is_none[0], 7) != 0) {
    return 1;
  }
  return 8;
}
