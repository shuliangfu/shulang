/* labi_ondemand_heavy.x — L8c ondemand heavy pure tables/orch (wave263)
 * PLATFORM: SHARED
 *
 * Capacity root (wave263): full labi_ondemand_list.x silent-parse-skips ~14 late
 * exports under XLANG_DEBUG_PARSE (codegen/product -E incomplete → PREFER L8b UNDEF).
 * Split: L8b keeps early pure tables; L8c holds std_task / fk0 / fk_gate / provides /
 * link_needs_* / on_demand shell (+ private helpers). Both PREFER_X_O → product L8b+L8c.
 *
 * G.7: one authority per symbol (bodies only here, not duplicated in L8b).
 * Cap residual: undef_sym / has_defined / push/ensure / nm host _impl (mega).
 * Prove surface: seeds/labi_ondemand_heavy_surface.from_x.c (or combined prove).
 */


/* wave263 L8c: Cap residual + L8b pure callees (G.7 extern-only; bodies elsewhere). */
/* PLATFORM: SHARED — resolve at product link (L8b .x.o + mega rest). */
export extern "C" function driver_freestanding_get(): i32;
export extern function asm_link_obj_skip_missing(path: *u8): *u8;
export extern function labi_od_arrow_glue_rel(): *u8;
export extern function labi_od_arrow_rel(): *u8;
export extern function labi_od_arrow_sym_at(i: i32): *u8;
export extern function labi_od_arrow_sym_count(): i32;
export extern function labi_od_kv_glue_rel(): *u8;
export extern function labi_od_kv_rel(): *u8;
export extern function labi_od_async_rel(): *u8;
export extern function labi_od_async_sym_at(i: i32): *u8;
export extern function labi_od_async_sym_count(): i32;
export extern function labi_od_kv_sym_at(i: i32): *u8;
export extern function labi_od_kv_sym_count(): i32;
export extern function labi_od_queue_contention_rel(): *u8;
export extern function labi_od_queue_rel(): *u8;
export extern function labi_od_queue_sym_at(i: i32): *u8;
export extern function labi_od_queue_sym_count(): i32;
export extern function labi_od_simple_group_count(): i32;
export extern function labi_od_simple_group_rel(g: i32): *u8;
export extern function labi_od_simple_group_sym_at(g: i32, i: i32): *u8;
export extern function labi_od_simple_group_sym_count(g: i32): i32;
export extern function labi_od_time_os_rel(): *u8;
export extern function labi_od_time_rel(): *u8;
export extern function labi_od_time_sym_at(i: i32): *u8;
export extern function labi_od_time_sym_count(): i32;
export extern function link_abi_asm_ld_argv_push_stable(bank: *u8, argv: **u8, la: *i32, max_la: i32, p: *u8): void;
export extern function link_abi_asm_ld_push_obj(primary: *u8, link_argv0: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flag_out: *i32): i32;
export extern function link_abi_ld_argv_entry_is_obj(s: *u8): i32;
export extern function link_abi_user_o_needs_async_scheduler(user_o: *u8): i32;
export extern function link_abi_user_o_needs_core_mem(user_o: *u8): i32;
export extern function link_abi_user_o_needs_core_slice(user_o: *u8): i32;
export extern function link_abi_user_o_needs_heap_user_syms(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_heap_api(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_heap_page_mmap(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_map(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_net(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_queue(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_set(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_sys(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_sys_linux(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_sys_macos(user_o: *u8): i32;
export extern function link_abi_user_o_needs_std_test(user_o: *u8): i32;
export extern function xlang_asm_ld_try_under_lib_roots(rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8): *u8;
export extern function xlang_ensure_formal_std_make_o(repo_root: *u8, rel_from_repo: *u8, make_target: *u8): i32;
export extern function labi_std_append_queue_monofile_companions(link_argv0: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flags: *u8): void;
export extern function labi_std_append_test_monofile_companions(link_argv0: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void;
export extern function xlang_ensure_runtime_heap_user_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_net_udp_batch_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_net_workers_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_process_argv_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_queue_contention_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_test_fn_invoke_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_env_os_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_thread_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_kv_mmap_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_arrow_simd_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_scheduler_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_http_glue_o(argv0: *u8): i32;
export extern function xlang_runtime_http_glue_o_path(argv0: *u8): *u8;
export extern function xlang_ensure_runtime_atomic_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_sync_os_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_sync_lock_diag_tls_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_time_os_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_crypto_inc_glue_o(argv0: *u8): i32;
export extern function xlang_ensure_runtime_ed25519_ref10_glue_o(argv0: *u8): i32;
export extern function xlang_link_obj_has_defined_sym(o_path: *u8, sym: *u8): i32;
export extern function xlang_link_obj_needs_undef_sym(user_o: *u8, sym: *u8): i32;
export extern function xlang_rel_o_path_from_argv0(argv0: *u8, rel: *u8): *u8;
export extern function xlang_repo_root_from_argv0(argv0: *u8): *u8;
export extern function xlang_runtime_arrow_simd_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_heap_user_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_kv_mmap_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_net_udp_batch_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_net_workers_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_process_argv_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_queue_contention_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_scheduler_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_test_fn_invoke_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_env_os_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_thread_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_atomic_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_sync_os_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_sync_lock_diag_tls_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_time_os_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_crypto_inc_glue_o_path(argv0: *u8): *u8;
export extern function xlang_runtime_ed25519_ref10_glue_o_path(argv0: *u8): *u8;
export extern function xlang_std_async_scheduler_o_path(argv0: *u8): *u8;

/* wave134: bulk TASK_SPECIAL pure table + orch (std_task / task.o gate).
 * Do NOT probe xlang_async_task_submit* here — pure async goes through on_demand
 * scheduler path without forcing task.o. null/empty user_o → 1 legacy hard-link.
 * PLATFORM: SHARED — exact symbols only; Cap residual undef_sym. */

/**
 * Count of std.task / task glue UNDEF needles for labi_user_needs_std_task.
 * Product complete (G.7): std_task_* formal API + task_group_* / join_set_* / task_*_c.
 * @return i32 — 29
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_std_task_sym_count(): i32 {
  return 29;
}

/**
 * std.task UNDEF needle at index (exact symbols only; no async submit* probes).
 * @param i i32 — index in [0, 29)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_std_task_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_task_new";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_task_free";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_task_bind";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_task_spawn";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_task_join";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_task_pending";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_task_check_leak";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_task_cancel";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_task_total";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_task_set_new";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_task_set_free";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_task_set_spawn";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_task_set_join";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_task_set_check_leak";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_task_echo";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_task_echo_ptr";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_task_retry";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_task_err_ok";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "task_group_create_c";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "task_group_spawn_c";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "task_group_join_c";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "task_group_free_c";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "join_set_create_c";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "join_set_spawn_c";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "join_set_join_c";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "task_smoke_c";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "task_supervise_retry_c";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "task_echo_fn_c";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "task_echo_fn_ptr_c";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o needs std.task / task.o bulk (TASK_SPECIAL gate).
 * Pure orch: fixed exact UNDEF table; Cap residual undef_sym.
 * null/empty user_o → 1 (legacy hard-link when call site has no user_o).
 * Does not probe xlang_async_task_submit* (scheduler on_demand path).
 * @param user_o *u8 — path to user .o
 * @return i32 — 1 if gate open (push/ensure task.o path), else 0
 * Why (wave134): hybrid still had labi_user_needs_std_task body always mega C;
 * single-leaf migrate after wave133 process_argv pure (capacity-safe one leaf).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function labi_user_needs_std_task(user_o: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (user_o == 0 as *u8) {
      return 1;
    }
    if (user_o[0] == 0) {
      return 1;
    }
    let n: i32 = labi_od_std_task_sym_count();
    let i: i32 = 0;
    while (i < n) {
      let sym: *u8 = labi_od_std_task_sym_at(i);
      if (sym != 0 as *u8) {
        if (sym[0] != 0) {
          let hit: i32 = 0;
          unsafe {
            hit = xlang_link_obj_needs_undef_sym(user_o, sym);
          }
          if (hit != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}



/* wave135: labi_std_fk0_user_needs_rel pure orch (fk==0 std plan gate).
 * Cap residual: undef_sym (mega) + libc strstr for rel path match.
 * null/empty user_o → 1 legacy hard-link; unknown rel → 0 (no hard-link poison).
 * PLATFORM: SHARED — complete product surface from mega authority (G.7). */

export extern "C" function strstr(hay: *u8, needle: *u8): *u8;

/**
 * Count of fk0 rel path needles (substring match order matches mega seed).
 * @return i32 — 27 (was 25; +option/+result STD-080/081 roundtrip residual 2026-08-26)
 * PLATFORM: SHARED — G.7 complete: every OP_STD flag_kind=0 formal rel that can
 * be the sole user UNDEF must appear here or the gate never opens (run-tar /
 * run-unicode / cli_subcommand / datetime_iana / std_config_* / std_cache_* /
 * std_url_* / std_security_* / std_option_* / std_result_* history: formal .o
 * existed or bare impl only, plan step present, fk0 table missed).
 */
#[no_mangle]
export function labi_fk0_rel_count(): i32 {
  // PLATFORM: SHARED — was 25 (+security); +k25 option +k26 result.
  return 27;
}

/**
 * fk0 rel path needle at index (substring of plan rel path).
 * @param k i32 — kind in [0, labi_fk0_rel_count())
 * @return *u8 — static C string path needle, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_fk0_rel_at(k: i32): *u8 {

  if (k == 0) {
    let p: *u8 = "std/string/string.o";
    return p;
  }
  if (k == 1) {
    let p: *u8 = "std/encoding/encoding.o";
    return p;
  }
  if (k == 2) {
    let p: *u8 = "std/base64/base64.o";
    return p;
  }
  if (k == 3) {
    let p: *u8 = "std/http/http.o";
    return p;
  }
  if (k == 4) {
    let p: *u8 = "std/json/json.o";
    return p;
  }
  if (k == 5) {
    let p: *u8 = "std/csv/csv.o";
    return p;
  }
  if (k == 6) {
    let p: *u8 = "std/path/path.o";
    return p;
  }
  if (k == 7) {
    let p: *u8 = "std/hash/hash.o";
    return p;
  }
  if (k == 8) {
    let p: *u8 = "std/error/error.o";
    return p;
  }
  if (k == 9) {
    let p: *u8 = "std/context/context.o";
    return p;
  }
  if (k == 10) {
    let p: *u8 = "std/vec/vec.o";
    return p;
  }
  if (k == 11) {
    let p: *u8 = "std/sort/sort.o";
    return p;
  }
  if (k == 12) {
    let p: *u8 = "std/env/env.o";
    return p;
  }
  if (k == 13) {
    let p: *u8 = "std/random/random.o";
    return p;
  }
  if (k == 14) {
    let p: *u8 = "std/time/time.o";
    return p;
  }
  if (k == 15) {
    let p: *u8 = "std/fs/fs.o";
    return p;
  }
  // PLATFORM: SHARED — std/tar/tar.o was OP_STD flag_kind=0 but missing from fk0
  // → labi_std_fk0_user_needs_rel always 0 → never push formal tar.o (run-tar UNDEF
  // std_tar_read_header / write_header even when formal rebuild produced T surface).
  if (k == 16) {
    let p: *u8 = "std/tar/tar.o";
    return p;
  }
  // PLATFORM: SHARED — std/unicode/unicode.o same class as tar (flag_kind=0, no fk0).
  if (k == 17) {
    let p: *u8 = "std/unicode/unicode.o";
    return p;
  }
  // PLATFORM: SHARED — std/runtime/runtime.o is OP_STD flag_kind=0 but was missing from
  // fk0 table → never push formal runtime.o; stale marker .o lacked std_runtime_ready
  // (run-runtime residual). G.7 complete: add rel×sym like tar/unicode.
  if (k == 18) {
    let p: *u8 = "std/runtime/runtime.o";
    return p;
  }
  // PLATFORM: SHARED — std/cli/cli.o is OP_STD flag_kind=0 but was missing from
  // fk0 table → never push formal cli.o even after formal_mod exported std_cli_*
  // (cookbook cli_subcommand UNDEF std_cli_err_* / parse_from_iter).
  if (k == 19) {
    let p: *u8 = "std/cli/cli.o";
    return p;
  }
  // PLATFORM: SHARED — std/datetime/datetime.o is OP_STD flag_kind=0 but was missing
  // from fk0 → never push formal datetime.o even after formal_mod exported
  // std_datetime_* (cookbook datetime_iana UNDEF timezone_iana).
  if (k == 20) {
    let p: *u8 = "std/datetime/datetime.o";
    return p;
  }
  // PLATFORM: SHARED — std/config/config.o is OP_STD flag_kind=0 but was missing
  // from fk0 → never push formal config.o even after formal_mod exported
  // std_config_* (STD-086 layer_smoke / yaml_smoke BLD001 UNDEF).
  if (k == 21) {
    let p: *u8 = "std/config/config.o";
    return p;
  }
  // PLATFORM: SHARED — std/cache/cache.o is OP_STD flag_kind=0 but was missing
  // from fk0 → never push formal cache.o even after formal_mod exported
  // std_cache_* (STD-087 lru_pool_smoke BLD001 UNDEF).
  if (k == 22) {
    let p: *u8 = "std/cache/cache.o";
    return p;
  }
  // PLATFORM: SHARED — std/url/url.o is OP_STD flag_kind=0 but was missing
  // from fk0 → never push formal url.o even after formal_mod exported
  // std_url_* (STD-076 roundtrip BLD001 UNDEF).
  if (k == 23) {
    let p: *u8 = "std/url/url.o";
    return p;
  }
  // PLATFORM: SHARED — std/security/security.o is OP_STD flag_kind=0 but was
  // missing from fk0 → never push formal security.o even after formal_mod
  // exported std_security_* (STD-079 roundtrip BLD001 UNDEF).
  if (k == 24) {
    let p: *u8 = "std/security/security.o";
    return p;
  }
  // PLATFORM: SHARED — std/option/option.o was missing from plan+fk0 →
  // never push formal option.o (STD-080 roundtrip BLD001 UNDEF std_option_*).
  if (k == 25) {
    let p: *u8 = "std/option/option.o";
    return p;
  }
  // PLATFORM: SHARED — std/result/result.o was missing from plan+fk0 →
  // never push formal result.o (STD-081 roundtrip BLD001 UNDEF std_result_*).
  if (k == 26) {
    let p: *u8 = "std/result/result.o";
    return p;
  }
  return 0 as *u8;
}


/**
 * Count of exact UNDEF needles for fk0 kind.
 * @param k i32 — rel kind
 * @return i32 — needle count; 0 if kind OOB
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_fk0_sym_count(k: i32): i32 {

  if (k == 0) {
    return 11;
  }
  if (k == 1) {
    return 2;
  }
  if (k == 2) {
    return 2;
  }
  if (k == 3) {
    return 4;
  }
  // PLATFORM: SHARED — json.o gate: std_json_parse* needles are not enough on
  // product asm -o. Co-emit of mod.x wrappers makes those T in user.o; the sole
  // remaining UNDEF is the extern "C" / --bare-impl json_*_c body in json.x
  // (run-json / boundary json_invalid: json_parse_null_c). Exact matcher.
  // G.7 complete parse/skip family including bare *_c so json.o is pushed.
  if (k == 4) {
    return 12;
  }
  if (k == 5) {
    return 4;
  }
  // PLATFORM: SHARED — path.o fk0 was incomplete (only join/dirname/empty_len/basename).
  // Sole callers of sep/extension/stem/clean/resolve/is_absolute never opened the gate
  // → UNDEF at ld (run-path extension_stem_abs_clean / resolve / extreme).
  // G.7 complete surface: every public std_path_* export that can be sole user UNDEF.
  if (k == 6) {
    return 12;
  }
  if (k == 7) {
    return 11;
  }
  // PLATFORM: SHARED — error.o fk0 complete (was 4: http/ok/io timeout/cancel).
  // EXC-006 sole code_invalid/io_err_generic/chain_* never opened gate → soft SKIP.
  // G.7: every public std_error_* export (mod.x ×57).
  if (k == 8) {
    return 57;
  }
  if (k == 9) {
    return 4;
  }
  if (k == 10) {
    return 42;
  }
  if (k == 11) {
    return 9;
  }
  if (k == 12) {
    // PLATFORM: SHARED — +args_iter_count_c / args_iter_at_c (env_iter leftover UNDEF).
    return 13;
  }
  if (k == 13) {
    return 12;
  }
  if (k == 14) {
    return 15;
  }
  // PLATFORM: SHARED — fs fk0 was incomplete (only invalid/open/…/last_error).
  // Sole callers of readv_buf/writev_buf never opened the gate → UNDEF at ld
  // (run-fs readv_writev_buf). G.7 complete surface: public readv/writev faces.
  // Cap residual 9.1.2: +std_fs_stat so stat-only users pull formal fs.o.
  // Cap residual 9.1.10: +std_fs_dir_{open,read,close} so dir-only users pull formal fs.o.
  if (k == 15) {
    return 15;
  }
  // PLATFORM: SHARED — tar formal public surface (std_tar_*).
  if (k == 16) {
    return 7;
  }
  // PLATFORM: SHARED — unicode formal public surface (std_unicode_*).
  if (k == 17) {
    return 6;
  }
  // PLATFORM: SHARED — runtime formal public surface (std_runtime_*).
  if (k == 18) {
    return 5;
  }
  // PLATFORM: SHARED — cli formal public surface (std_cli_*).
  if (k == 19) {
    return 10;
  }
  // PLATFORM: SHARED — datetime formal public surface (std_datetime_*).
  // Count 27 = full export surface in std/datetime/mod.x (G.7 complete one table).
  if (k == 20) {
    return 27;
  }
  // PLATFORM: SHARED — config formal public surface (std_config_*).
  // Count 31 = full export surface in std/config/mod.x (G.7 complete one table).
  if (k == 21) {
    return 31;
  }
  // PLATFORM: SHARED — cache formal public surface (std_cache_*).
  // Count 20 = full export surface in std/cache/mod.x (G.7 complete one table).
  if (k == 22) {
    return 20;
  }
  // PLATFORM: SHARED — url formal public surface (std_url_*).
  // Count 10 = full export surface in std/url/mod.x (G.7 complete one table).
  if (k == 23) {
    return 10;
  }
  // PLATFORM: SHARED — security formal public surface (std_security_*).
  // Count 16 = full export surface in std/security/mod.x (G.7 complete one table).
  if (k == 24) {
    return 16;
  }
  // PLATFORM: SHARED — option formal public surface (std_option_*).
  // Count 11 = full export surface in std/option/mod.x (incl. from_result overloads).
  if (k == 25) {
    return 11;
  }
  // PLATFORM: SHARED — result formal public surface (std_result_*).
  // Count 11 = full export surface in std/result/mod.x (G.7 complete one table).
  if (k == 26) {
    return 11;
  }
  return 0;
}


/**
 * Exact UNDEF needle for fk0 kind at index.
 * @param k i32 — rel kind
 * @param i i32 — index in [0, labi_fk0_sym_count(k))
 * @return *u8 — static C string symbol, or null if OOB
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_fk0_sym_at(k: i32, i: i32): *u8 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (i < 0) {
      return 0 as *u8;
    }

    if (k == 0) {
      if (i == 0) {
        let p: *u8 = "std_string_string_empty";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_string_new";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_string_length_String";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_string_length_StrView";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_string_is_empty_String";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_string_is_empty_StrView";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_string_view";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_string_string_from_slice";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_string_string_eq";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "xlang_string_memcmp_c";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "xlang_string_memmem_c";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 1) {
      if (i == 0) {
        let p: *u8 = "std_encoding_utf8_valid";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_encoding_ascii_is_alpha";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 2) {
      if (i == 0) {
        let p: *u8 = "std_base64_encode_standard";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_base64_decode_standard";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 3) {
      if (i == 0) {
        let p: *u8 = "std_http_get";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_http_request";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_http_client_new";
        return p;
      }
      // PLATFORM: SHARED — asm -o co-emits std_http_get as T; sole UNDEF is
      // extern "C" http_get_c (run-http). Exact matcher; G.7 complete.
      if (i == 3) {
        let p: *u8 = "http_get_c";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — fk0 k==4 std/json/json.o exact UNDEF needles.
    // Must list every public export that can appear as the sole UNDEF in user.o;
    // matcher is exact (rest==len), so std_json_parse does NOT cover parse_null
    // and does NOT cover json_parse_null_c after asm co-emit of the wrapper.
    if (k == 4) {
      if (i == 0) {
        let p: *u8 = "std_json_parse";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_json_parse_null";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_json_parse_number";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_json_parse_string";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_json_parse_string_view";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_json_skip_value";
        return p;
      }
      // PLATFORM: SHARED — bare --bare-impl / extern "C" parse family.
      // Product asm -o co-emits mod.x wrappers (T std_json_parse*); remaining
      // U is json_parse_*_c. Push json.o (ld --allow-multiple-definition).
      if (i == 6) {
        let p: *u8 = "json_parse_null_c";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "json_parse_number_c";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "json_parse_bool_c";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "json_parse_string_c";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "json_parse_string_view_c";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "json_skip_value_c";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — fk0 k==5 std/csv/csv.o exact UNDEF needles.
    // Matcher is exact; next_field/parse_line do not cover parse_row/write_row.
    if (k == 5) {
      if (i == 0) {
        let p: *u8 = "std_csv_next_field";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_csv_parse_line";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_csv_parse_row";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_csv_write_row";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — exact UNDEF needles for std/path/path.o (k==6).
    // Exact match only; join/basename do not cover clean/sep/extension/stem/resolve.
    if (k == 6) {
      if (i == 0) {
        let p: *u8 = "std_path_join";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_path_dirname";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_path_empty_len";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_path_basename";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_path_sep";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_path_is_absolute";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_path_is_sep";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_path_extension";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_path_stem";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_path_extension_and_stem";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_path_clean";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_path_resolve";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 7) {
      if (i == 0) {
        let p: *u8 = "std_hash_sip_hash";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_hash_fnv1a";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_hash_start";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_hash_bytes";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_hash_finish";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_hash_free";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_hash_write_u8_ptr_u32";
        return p;
      }
      // PLATFORM: SHARED — asm -o co-emits std_hash_* wrappers as T; sole UNDEF
      // is --bare-impl hash_sip_*_c / hash_xxhash64_*_c (run-hash / run-set).
      if (i == 7) {
        let p: *u8 = "hash_sip_bytes_c";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "hash_sip_free_c";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "hash_xxhash64_bytes_c";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "hash_xxhash64_seed_bytes_c";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 8) {
      // PLATFORM: SHARED — std/error/error.o exact UNDEF needles (fk0 k==8).
      // Was only http_err_timeout/ok/io_err_timeout/io_err_cancelled (4).
      // Sole callers of code_invalid/io_err_generic/chain_*/fs_err_* never
      // opened the gate → BLD001; EXC-006/002/003/004 soft SKIP falsified green.
      // G.7 complete surface: every public std_error_* export (mod.x ×57).
      if (i == 0) {
        let p: *u8 = "std_error_ok";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_error_code_alloc_fail";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_error_code_invalid";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_error_code_not_found";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_error_ok_value";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_error_from_code";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_error_code";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_error_is_ok";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_error_is_err";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_error_base_io";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_error_io_err_timeout";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_error_io_err_cancelled";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_error_io_err_generic";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_error_base_net";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_error_net_err_timeout";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_error_net_err_cancelled";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_error_net_err_generic";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_error_base_async";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_error_async_err_generic";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_error_base_coll";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_error_coll_err_generic";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_error_base_fs";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_error_fs_err_not_found";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_error_mod_tag_io";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_error_mod_tag_fs";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_error_mod_tag_db";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "std_error_sidecar_none";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "std_error_sidecar_errno";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "std_error_sidecar_db_struct";
        return p;
      }
      if (i == 29) {
        let p: *u8 = "std_error_code_to_module_base";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "std_error_code_in_global_range";
        return p;
      }
      if (i == 31) {
        let p: *u8 = "std_error_code_in_module_span";
        return p;
      }
      if (i == 32) {
        let p: *u8 = "std_error_code_is_platform_errno";
        return p;
      }
      if (i == 33) {
        let p: *u8 = "std_error_mod_tag_from_base";
        return p;
      }
      if (i == 34) {
        let p: *u8 = "std_error_mod_base_from_tag";
        return p;
      }
      if (i == 35) {
        let p: *u8 = "std_error_module_sidecar_kind";
        return p;
      }
      if (i == 36) {
        let p: *u8 = "std_error_sem_none";
        return p;
      }
      if (i == 37) {
        let p: *u8 = "std_error_sem_timeout";
        return p;
      }
      if (i == 38) {
        let p: *u8 = "std_error_sem_cancelled";
        return p;
      }
      if (i == 39) {
        let p: *u8 = "std_error_sem_not_found";
        return p;
      }
      if (i == 40) {
        let p: *u8 = "std_error_http_err_timeout";
        return p;
      }
      if (i == 41) {
        let p: *u8 = "std_error_http_err_cancelled";
        return p;
      }
      if (i == 42) {
        let p: *u8 = "std_error_semantic_class";
        return p;
      }
      if (i == 43) {
        let p: *u8 = "std_error_is_timeout";
        return p;
      }
      if (i == 44) {
        let p: *u8 = "std_error_is_cancelled";
        return p;
      }
      if (i == 45) {
        let p: *u8 = "std_error_is_not_found";
        return p;
      }
      if (i == 46) {
        let p: *u8 = "std_error_recommend_retry";
        return p;
      }
      if (i == 47) {
        let p: *u8 = "std_error_chain_max_depth";
        return p;
      }
      if (i == 48) {
        let p: *u8 = "std_error_chain_empty";
        return p;
      }
      if (i == 49) {
        let p: *u8 = "std_error_chain_from_code";
        return p;
      }
      if (i == 50) {
        let p: *u8 = "std_error_chain_from_result";
        return p;
      }
      if (i == 51) {
        let p: *u8 = "std_error_chain_depth";
        return p;
      }
      if (i == 52) {
        let p: *u8 = "std_error_chain_root";
        return p;
      }
      if (i == 53) {
        let p: *u8 = "std_error_chain_code_at";
        return p;
      }
      if (i == 54) {
        let p: *u8 = "std_error_chain_leaf";
        return p;
      }
      if (i == 55) {
        let p: *u8 = "std_error_chain_wrap";
        return p;
      }
      if (i == 56) {
        let p: *u8 = "std_error_error_module_anchor";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 9) {
      if (i == 0) {
        let p: *u8 = "std_context_background";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_context_deadline_ns";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_context_is_cancelled";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_context_remaining_ns";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 10) {
      // PLATFORM: SHARED — fk0 k==10 std/vec/vec.o exact UNDEF needles.
      // Matcher is exact; new/push_i32/length_u8/i32 do not cover pop,
      // Vec_u64/f64 extend, sole from_slice_u64/f64, sole push_u64/f64,
      // or sole length/get/deinit u64/f64.
      if (i == 0) {
        let p: *u8 = "std_vec_new_retVec_u8";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_vec_new_retVec_i32";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_vec_push_Vec_u8_ptr_u8";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_vec_push_Vec_i32_ptr_i32";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_vec_length_Vec_u8";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_vec_length_Vec_i32";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_vec_len_empty";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_vec_vec_len_empty";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_vec_new";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_vec_push";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_vec_pop_Vec_i32_ptr";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_vec_pop_Vec_u8_ptr";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_vec_extend_Vec_i32_ptr_i32_ptr_i32";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_vec_extend_Vec_u8_ptr_u8_ptr_i32";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_vec_extend_Vec_u64_ptr_u64_ptr_i32";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_vec_extend_Vec_f64_ptr_f64_ptr_i32";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_vec_from_slice_u64_ptr_i32";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_vec_from_slice_f64_ptr_i32";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_vec_push_Vec_u64_ptr_u64";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_vec_push_Vec_f64_ptr_f64";
        return p;
      }
      // PLATFORM: SHARED — exact UNDEF needles for length/deinit/get
      // Vec_u64/f64. u8/i32 length do not cover sole new+length/deinit.
      if (i == 20) {
        let p: *u8 = "std_vec_length_Vec_u64";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_vec_deinit_Vec_u64_ptr";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_vec_length_Vec_f64";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_vec_deinit_Vec_f64_ptr";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_vec_get_Vec_u64_i32";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_vec_get_Vec_f64_i32";
        return p;
      }
      // PLATFORM: SHARED — exact UNDEF needles for Vec3f SOA/AOS.
      // Matcher is exact; Vec_* push/length/deinit do not cover unique
      // names vec3f_soa_push / vec3f_aos_deinit / reserve_one / sum_x.
      if (i == 26) {
        let p: *u8 = "std_vec_vec3f_soa_push";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "std_vec_vec3f_soa_deinit";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "std_vec_vec3f_aos_push";
        return p;
      }
      if (i == 29) {
        let p: *u8 = "std_vec_vec3f_aos_deinit";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "std_vec_vec3f_soa_sum_x";
        return p;
      }
      if (i == 31) {
        let p: *u8 = "std_vec_vec3f_soa_reserve_one";
        return p;
      }
      if (i == 32) {
        let p: *u8 = "std_vec_vec3f_soa_len";
        return p;
      }
      if (i == 33) {
        let p: *u8 = "std_vec_vec3f_soa_get_x";
        return p;
      }
      if (i == 34) {
        let p: *u8 = "std_vec_vec3f_soa_get_y";
        return p;
      }
      if (i == 35) {
        let p: *u8 = "std_vec_vec3f_soa_get_z";
        return p;
      }
      if (i == 36) {
        let p: *u8 = "std_vec_vec3f_soa_set";
        return p;
      }
      if (i == 37) {
        let p: *u8 = "std_vec_vec3f_soa_with_capacity";
        return p;
      }
      if (i == 38) {
        let p: *u8 = "std_vec_vec3f_aos_reserve_one";
        return p;
      }
      if (i == 39) {
        let p: *u8 = "std_vec_vec3f_aos_get_x";
        return p;
      }
      if (i == 40) {
        let p: *u8 = "std_vec_vec3f_aos_sum_x";
        return p;
      }
      if (i == 41) {
        let p: *u8 = "std_vec_vec3f_aos_with_capacity";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 11) {
      if (i == 0) {
        let p: *u8 = "std_sort_sort_i32_ptr_i32";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_sort_sort_u8_ptr_i32";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_sort_stable_i32_ptr_i32";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_sort_stable_u8_ptr_i32";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_sort_stable_by_key";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_sort_cmp";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_sort_cmp_asc_fn";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_sort_cmp_desc_fn";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_sort_cmp_key_fn";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 12) {
      if (i == 0) {
        let p: *u8 = "std_env_getenv";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_env_getenv_exists";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_env_getenv_z";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_env_getenv_ptr";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_env_setenv";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_env_unsetenv";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_env_temp_dir";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_env_iter";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_env_iter_count";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_env_args_iter";
        return p;
      }
      // PLATFORM: SHARED — cookbook cli_subcommand sole-UNDEF of
      // std_env_args_iter_count (args_iter may be co-emitted; exact match).
      if (i == 10) {
        let p: *u8 = "std_env_args_iter_count";
        return p;
      }
      // PLATFORM: SHARED — leftover may emit std_env_args_iter_* as T (fk0 closed) while
      // leaving args_iter_*_c U (run-env env_iter Ubuntu UNDEF). Complete env fk0 surface.
      if (i == 11) {
        let p: *u8 = "args_iter_count_c";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "args_iter_at_c";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 13) {
      if (i == 0) {
        let p: *u8 = "std_random_next";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_random_fill_bytes";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_random_fill";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_random_range_u32_u32";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_random_flip";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_random_gen";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_random_rng_smoke";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_random_seed";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "random_u32_c";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "random_u64_c";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "random_rng_smoke_c";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "random_fill_bytes_c";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 14) {
      if (i == 0) {
        let p: *u8 = "std_time_now_monotonic_ns";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_time_now_monotonic_ms";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_time_now_wall_ns";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_time_sleep_ms";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_time_sleep_ns";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_time_duration_ns";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_time_timer_start";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_time_start";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_time_elapsed_ns";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_time_format_wall_rfc3339";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_time_wall_local_offset_min";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_time_format_timezone_smoke";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "time_now_monotonic_ns_c";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "time_sleep_ns_c";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "time_now_wall_ns_c";
        return p;
      }
      return 0 as *u8;
    }
    if (k == 15) {
      if (i == 0) {
        let p: *u8 = "std_fs_invalid";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_fs_open";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_fs_create";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_fs_close";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_fs_read";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_fs_write";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_fs_chunk_size";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_fs_mmap_ro";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_fs_last_error";
        return p;
      }
      // PLATFORM: SHARED — complete fk0: readv/writev product faces (run-fs residual).
      if (i == 9) {
        let p: *u8 = "std_fs_readv_buf";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_fs_writev_buf";
        return p;
      }
      // Cap residual 9.1.2: stat-only pure-asm must open fs.o gate.
      if (i == 11) {
        let p: *u8 = "std_fs_stat";
        return p;
      }
      // Cap residual 9.1.10: dir-only pure-asm must open fs.o gate.
      if (i == 12) {
        let p: *u8 = "std_fs_dir_open";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_fs_dir_read";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_fs_dir_close";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/tar/tar.o exact UNDEF needles (fk0 k==16).
    // Exact match only; sole callers of read_header/write_header never opened gate.
    if (k == 16) {
      if (i == 0) {
        let p: *u8 = "std_tar_read_header";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_tar_write_header";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_tar_append_entry";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_tar_next_entry";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_tar_read_entry_data";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_tar_path_max";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "tar_read_header_c";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/unicode/unicode.o exact UNDEF needles (fk0 k==17).
    // Pure-asm import METHOD → std_unicode_*; formal_mod must export same surface.
    if (k == 17) {
      if (i == 0) {
        let p: *u8 = "std_unicode_category";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_unicode_to_lower";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_unicode_to_upper";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_unicode_is_whitespace";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_unicode_is_ascii";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_unicode_case_fold_rune";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/runtime/runtime.o exact UNDEF needles (fk0 k==18).
    // Pure-asm import METHOD → std_runtime_ready (sole caller in tests/runtime/main.x).
    if (k == 18) {
      if (i == 0) {
        let p: *u8 = "std_runtime_ready";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_runtime_panic";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_runtime_abort";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_runtime_diag_enabled";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_runtime_crash_evidence_collect";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/cli/cli.o exact UNDEF needles (fk0 k==19).
    // Exact match only; err_ok/err_help/parse_from_iter are cookbook sole UNDEFs.
    if (k == 19) {
      if (i == 0) {
        let p: *u8 = "std_cli_err_ok";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_cli_err_help";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_cli_err_unknown";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_cli_parse_from_iter";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_cli_arg_len";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_cli_is_help";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_cli_is_version";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_cli_match_long";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_cli_match_short";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_cli_write_usage";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/datetime/datetime.o exact UNDEF needles (fk0 k==20).
    // Exact match only; timezone_iana is cookbook datetime_iana sole UNDEF.
    // Count 27 = full export surface in std/datetime/mod.x (G.7 complete one table).
    if (k == 20) {
      if (i == 0) {
        let p: *u8 = "std_datetime_timezone_iana";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_datetime_now_utc";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_datetime_from_unix";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_datetime_from_utc_fields";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_datetime_to_utc_fields";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_datetime_compare";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_datetime_parse_rfc3339";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_datetime_format_rfc3339";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_datetime_format_rfc3339_nano";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_datetime_local_offset_min";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_datetime_to_local_fields";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_datetime_duration_from_ns";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_datetime_duration_from_sec";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_datetime_duration_between";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_datetime_add_duration";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_datetime_duration_sleep";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_datetime_duration_from_monotonic";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_datetime_timezone_utc";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_datetime_timezone_local";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_datetime_timezone_fixed";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_datetime_timezone_from_name";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_datetime_timezone_offset_at";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_datetime_parse_offset_min";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_datetime_to_zoned_fields";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_datetime_from_zoned_fields";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_datetime_iana_dst_smoke";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "std_datetime_timezone_smoke";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/config/config.o exact UNDEF needles (fk0 k==21).
    // Exact match only; layer_smoke / yaml_smoke sole UNDEFs open the gate.
    // Count 31 = full export surface in std/config/mod.x (G.7 complete one table).
    if (k == 21) {
      if (i == 0) {
        let p: *u8 = "std_config_err_ok";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_config_err_null";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_config_err_not_found";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_config_err_invalid";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_config_err_io";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_config_err_full";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_config_source_unknown";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_config_source_toml";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_config_source_yaml";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_config_source_env";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_config_source_set";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_config_new";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_config_free";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_config_clear";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_config_load_toml_buf";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_config_load_toml_file";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_config_load_env_prefix";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_config_merge";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_config_set_string";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_config_get_string";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_config_get_i32";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_config_get_bool";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_config_get_source";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_config_get_i32_meta";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_config_get_bool_meta";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_config_get_string_meta";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "std_config_backend_toml";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "std_config_backend_yaml";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "std_config_load_yaml_buf";
        return p;
      }
      if (i == 29) {
        let p: *u8 = "std_config_load_yaml_file";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "std_config_yaml_smoke";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/cache/cache.o exact UNDEF needles (fk0 k==22).
    // Exact match only; lru_pool_smoke sole UNDEFs open the gate.
    // Count 20 = full export surface in std/cache/mod.x (G.7 complete one table).
    if (k == 22) {
      if (i == 0) {
        let p: *u8 = "std_cache_err_ok";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_cache_err_null";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_cache_err_not_found";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_cache_err_full";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_cache_err_invalid";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_cache_new_lru";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_cache_free_LruCache_ptr";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_cache_get";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_cache_put";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_cache_remove";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_cache_purge";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_cache_stats_LruCache_ptr_CacheStats_ptr";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_cache_new";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_cache_free_ObjPool_ptr";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_cache_add";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_cache_acquire";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_cache_release";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_cache_mark_unhealthy";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_cache_idle";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_cache_stats_ObjPool_ptr_PoolStats_ptr";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/url/url.o exact UNDEF needles (fk0 k==23).
    // Exact match only; roundtrip sole UNDEFs open the gate.
    // Count 10 = full export surface in std/url/mod.x (G.7 complete one table).
    if (k == 23) {
      if (i == 0) {
        let p: *u8 = "std_url_parse";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_url_build";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_url_stringify";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_url_query_encode";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_url_query_decode";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_url_resolve";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_url_host_to_ipv6";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_url_format_ipv6_host";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_url_host_is_ipv6";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_url_ipv6_host_smoke";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/security/security.o exact UNDEF needles (fk0 k==24).
    // Exact match only; roundtrip sole UNDEFs open the gate.
    // Count 16 = full export surface in std/security/mod.x (G.7 complete one table).
    // Product API names follow 标准库api命名规范 (hkdf / err_ok; not fossil hkdf_sha256).
    if (k == 24) {
      if (i == 0) {
        let p: *u8 = "std_security_key_len";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_security_salt_len_default";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_security_min_secret_len";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_security_err_ok";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_security_err_invalid";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_security_err_random";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_security_err_buffer";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_security_ct_compare";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_security_random_key";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_security_random_salt";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_security_hkdf";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_security_secure_zero";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_security_sensitive_lock";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_security_sensitive_unlock";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_security_sensitive_buf_init";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_security_sensitive_buf_wipe";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/option/option.o exact UNDEF needles (fk0 k==25).
    // Count 11 = full export surface (from_result overloads mangled).
    if (k == 25) {
      if (i == 0) {
        let p: *u8 = "std_option_none";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_option_some";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_option_unwrap_or";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_option_is_some";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_option_is_none";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_option_map";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_option_and_then";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_option_or";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_option_from_result_Result_i32";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_option_from_result_Result_u8";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_option_to_result";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — std/result/result.o exact UNDEF needles (fk0 k==26).
    // Count 11 = full export surface in std/result/mod.x.
    if (k == 26) {
      if (i == 0) {
        let p: *u8 = "std_result_ok";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_result_err";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_result_is_ok";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_result_is_err";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_result_unwrap_or";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_result_map";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_result_and_then";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_result_or_else";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_result_from_error_code";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_result_from_value";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_result_err_code";
        return p;
      }
      return 0 as *u8;
    }
    return 0 as *u8;
  }
}


/**
 * Whether user .o needs a fk==0 std plan rel (string/encoding/.../fs formal .o).
 * Pure orch: match rel via Cap strstr table, then scan exact UNDEF needles.
 * null/empty user_o → 1 (legacy hard-link when call site has no user_o).
 * null/empty or unknown rel → 0 (except user_o null path above).
 * @param user_o *u8 — path to user .o
 * @param rel *u8 — plan relative path (e.g. std/string/string.o)
 * @return i32 — 1 if gate open (push/ensure that rel), else 0
 * Why (wave135): hybrid still had labi_std_fk0_user_needs_rel body always mega C;
 * single-leaf migrate after wave134 std_task pure (G.7 complete surface).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function labi_std_fk0_user_needs_rel(user_o: *u8, rel: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (rel == 0 as *u8) {
      return 0;
    }
    if (rel[0] == 0) {
      return 0;
    }
    if (user_o == 0 as *u8) {
      return 1;
    }
    if (user_o[0] == 0) {
      return 1;
    }
    let nk: i32 = labi_fk0_rel_count();
    let k: i32 = 0;
    let kind: i32 = -1;
    while (k < nk) {
      let needle: *u8 = labi_fk0_rel_at(k);
      if (needle != 0 as *u8) {
        if (needle[0] != 0) {
          let hitp: *u8 = 0 as *u8;
          unsafe {
            hitp = strstr(rel, needle);
          }
          if (hitp != 0 as *u8) {
            kind = k;
            // first match wins (mega sequential if order)
            k = nk;
          }
        }
      }
      k = k + 1;
    }
    if (kind < 0) {
      return 0;
    }
    let n: i32 = labi_fk0_sym_count(kind);
    let i: i32 = 0;
    while (i < n) {
      let sym: *u8 = labi_fk0_sym_at(kind, i);
      if (sym != 0 as *u8) {
        if (sym[0] != 0) {
          let hit: i32 = 0;
          unsafe {
            hit = xlang_link_obj_needs_undef_sym(user_o, sym);
          }
          if (hit != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Count of exact UNDEF needles for std-plan flag_kind fk (1=process … 13=http).
 * fk 0 is gated by labi_std_fk0_user_needs_rel (rel×sym tables); unknown fk → 0.
 * @param fk i32 — plan flag_kind from labi_std_plan_step_at
 * @return i32 — needle count; 0 if no gate table (always push when called)
 * PLATFORM: SHARED — pure table; G.7 single authority for fk≥1 plan gates
 */
#[no_mangle]
export function labi_std_fk_gate_sym_count(fk: i32): i32 {
  // PLATFORM: SHARED — process product face complete (pure-asm std_process_*).
  // Exact match only (Darwin nm -u); cover full mod.x / import_alias surface.
  if (fk == 1) {
    return 28;
  }
  if (fk == 2) {
    // PLATFORM: SHARED — thread product face complete (pool/name/affinity + create/join).
    // Was only spawn/join + create/join_c; pool_roundtrip co-emits std_thread_* and
    // UNDEFs thread_pool_*_c / set_name_self_c → need_thread stayed 0 → glue never linked.
    return 16;
  }
  if (fk == 3) {
    return 5;
  }
  if (fk == 4) {
    return 3;
  }
  if (fk == 5) {
    return 5;
  }
  // PLATFORM: SHARED — std/atomic complete surface (10.4.1 widen i16/u16/i64/u64 support).
  if (fk == 6) {
    return 32;
  }
  // PLATFORM: SHARED — channel product face complete (pure-asm std_channel_*
  // + leftover channel_send/recv + every channel_i32_*_c wrapper body).
  // Ubuntu L8b leftover was count=4 (send/recv only); asm -o co-emits
  // std_channel_* as T so the sole UNDEF is channel_i32_free_c (run-channel).
  // Exact matcher; G.7 complete i32 faces so fk7 pushes channel.o + glue.
  if (fk == 7) {
    return 19;
  }
  if (fk == 8) {
    return 2;
  }
  // PLATFORM: SHARED — math gate complete (was 29: std_math_* + sin/cos/
  // sin_c/cos_c/floor_c/pi_c). +31 runtime_math_libm freestanding faces so a
  // sole fmin/fmax/fabs/ceil/... UNDEF opens the gate too (see table note).
  if (fk == 9) {
    return 60;
  }
  // PLATFORM: SHARED — cookbook sqlite_available unique UNDEF (is_available).
  // Was 3 needles std_db_sqlite / sqlite3_open / db_sqlite_open. Matcher exact
  // so prefix never fires for std_db_sqlite_is_available. G.7 complete: 29 unique
  // import faces + keep legacy 3 + db_open_c (user-TU wrapper UNDEF when
  // mod.x is compiled into the probe; Linux gold). Glue companion OP 18.
  if (fk == 10) {
    return 33;
  }
  if (fk == 11) {
    return 2;
  }
  if (fk == 12) {
    return 4;
  }
  if (fk == 13) {
    return 5;
  }
  return 0;
}

/**
 * Exact UNDEF needle at index i for std-plan flag_kind fk (fk 1–13).
 * Tables match historical mega append_std_objs_for_user inline probes (G.7 no second path).
 * @param fk i32 — plan flag_kind
 * @param i i32 — zero-based needle index
 * @return *u8 — static C string; null if out of range
 * PLATFORM: SHARED — pure table; seed cold twin must stay in sync
 */
#[no_mangle]
export function labi_std_fk_gate_sym_at(fk: i32, i: i32): *u8 {

  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (i < 0) {
      return 0 as *u8;
    }
    // PLATFORM: SHARED — exact UNDEF needles for std/process/process.o (fk==1).
    // Full std_process_* import surface + bare process_*_c (run-process sole callers).
    if (fk == 1) {
      if (i == 0) { let p: *u8 = "process_xlang_argv_get"; return p; }
      if (i == 1) { let p: *u8 = "process_arg_c"; return p; }
      if (i == 2) { let p: *u8 = "process_args_count_c"; return p; }
      if (i == 3) { let p: *u8 = "std_process_exit"; return p; }
      if (i == 4) { let p: *u8 = "std_process_args_count"; return p; }
      if (i == 5) { let p: *u8 = "std_process_arg"; return p; }
      if (i == 6) { let p: *u8 = "std_process_getenv"; return p; }
      if (i == 7) { let p: *u8 = "std_process_setenv"; return p; }
      if (i == 8) { let p: *u8 = "std_process_unsetenv"; return p; }
      if (i == 9) { let p: *u8 = "std_process_getpid"; return p; }
      if (i == 10) { let p: *u8 = "std_process_getppid"; return p; }
      if (i == 11) { let p: *u8 = "std_process_getcwd"; return p; }
      if (i == 12) { let p: *u8 = "std_process_getcwd_ptr"; return p; }
      if (i == 13) { let p: *u8 = "std_process_getcwd_cached_len"; return p; }
      if (i == 14) { let p: *u8 = "std_process_chdir"; return p; }
      if (i == 15) { let p: *u8 = "std_process_self_exe_path"; return p; }
      if (i == 16) { let p: *u8 = "std_process_self_exe_path_ptr"; return p; }
      if (i == 17) { let p: *u8 = "std_process_self_exe_path_cached_len"; return p; }
      if (i == 18) { let p: *u8 = "std_process_spawn"; return p; }
      if (i == 19) { let p: *u8 = "std_process_spawn_io"; return p; }
      if (i == 20) { let p: *u8 = "std_process_spawn_simple"; return p; }
      if (i == 21) { let p: *u8 = "std_process_exec"; return p; }
      if (i == 22) { let p: *u8 = "std_process_exec_simple"; return p; }
      if (i == 23) { let p: *u8 = "std_process_waitpid"; return p; }
      if (i == 24) { let p: *u8 = "std_process_pipe"; return p; }
      if (i == 25) { let p: *u8 = "process_getenv_c"; return p; }
      if (i == 26) { let p: *u8 = "process_spawn_c"; return p; }
      if (i == 27) { let p: *u8 = "process_waitpid_c"; return p; }
      return 0 as *u8;
    }
    if (fk == 2) {
      // PLATFORM: SHARED — exact UNDEF needles for std/thread + runtime_thread_glue.
      if (i == 0) { let p: *u8 = "std_thread_spawn"; return p; }
      if (i == 1) { let p: *u8 = "std_thread_join"; return p; }
      if (i == 2) { let p: *u8 = "thread_create_c"; return p; }
      if (i == 3) { let p: *u8 = "thread_join_c"; return p; }
      if (i == 4) { let p: *u8 = "thread_pool_start_c"; return p; }
      if (i == 5) { let p: *u8 = "thread_pool_submit_c"; return p; }
      if (i == 6) { let p: *u8 = "thread_pool_drain_c"; return p; }
      if (i == 7) { let p: *u8 = "thread_pool_stop_c"; return p; }
      if (i == 8) { let p: *u8 = "thread_pool_pending_c"; return p; }
      if (i == 9) { let p: *u8 = "thread_set_name_self_c"; return p; }
      if (i == 10) { let p: *u8 = "thread_dummy_entry_ptr_c"; return p; }
      if (i == 11) { let p: *u8 = "thread_create_with_stack_c"; return p; }
      if (i == 12) { let p: *u8 = "thread_self_c"; return p; }
      if (i == 13) { let p: *u8 = "thread_set_affinity_c"; return p; }
      if (i == 14) { let p: *u8 = "thread_set_affinity_self_c"; return p; }
      if (i == 15) { let p: *u8 = "thread_set_qos_class_self_c"; return p; }
      return 0 as *u8;
    }
    if (fk == 3) {
      if (i == 0) {
        let p: *u8 = "std_sync_lock";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_sync_new_mutex";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_sync_try_lock";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_sync_wait";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "sync_mutex_lock_c";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 4) {
      if (i == 0) {
        let p: *u8 = "std_crypto_mem_eq";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "crypto_mem_eq_c";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_crypto_sha256";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 5) {
      if (i == 0) {
        let p: *u8 = "std_log_log";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_log_level_info";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_log_set_min_level";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "log_write_c";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_log_structured_kv";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 6) {
      if (i == 0) {
        let p: *u8 = "std_atomic_store_i32_ptr_i32";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_atomic_load_i32_ptr";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_atomic_fetch_add_i32_ptr_i32";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_atomic_store_i64_ptr_i64";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "atomic_store_i32_c";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_atomic_store_i16_ptr_i16";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_atomic_store_u16_ptr_u16";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_atomic_store_u32_ptr_u32";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_atomic_store_u64_ptr_u64";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_atomic_load_i16_ptr";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_atomic_load_u16_ptr";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_atomic_load_u32_ptr";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_atomic_load_i64_ptr";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_atomic_load_u64_ptr";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_atomic_fetch_add_i16_ptr_i16";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_atomic_fetch_add_u16_ptr_u16";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_atomic_fetch_add_u32_ptr_u32";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_atomic_fetch_add_i64_ptr_i64";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_atomic_fetch_add_u64_ptr_u64";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_atomic_fetch_sub_i32_ptr_i32";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_atomic_fetch_sub_i64_ptr_i64";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_atomic_fetch_sub_u64_ptr_u64";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_atomic_compare_exchange_i16_ptr_i16_ptr_i16";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_atomic_compare_exchange_i32_ptr_i32_ptr_i32";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_atomic_compare_exchange_i64_ptr_i64_ptr_i64";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_atomic_compare_exchange_u16_ptr_u16_ptr_u16";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "std_atomic_compare_exchange_u32_ptr_u32_ptr_u32";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "std_atomic_compare_exchange_u64_ptr_u64_ptr_u64";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "std_atomic_fence_acquire";
        return p;
      }
      if (i == 29) {
        let p: *u8 = "std_atomic_fence_release";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "std_atomic_fence_seq_cst";
        return p;
      }
      if (i == 31) {
        let p: *u8 = "atomic_load_i32_c";
        return p;
      }
      return 0 as *u8;
    }
    // PLATFORM: SHARED — fk==7 std/channel complete surface (exact match).
    // Pure-asm import METHOD → std_channel_*; leftover C-path channel_send/recv;
    // glue provides channel_i32_*_c. Asm -o co-emits wrappers as T so the live
    // UNDEF is the bare *_c body (run-channel: channel_i32_free_c). G.7 complete
    // every i32 wrapper face in std/channel/mod.x (not the select companion).
    if (fk == 7) {
      if (i == 0) {
        let p: *u8 = "std_channel_send";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_channel_recv";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_channel_bounded";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_channel_close";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_channel_free";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_channel_try_send";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_channel_try_recv";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_channel_unbounded";
        return p;
      }
      // Leftover L8b unique C-path needles (keep; exact match).
      if (i == 8) {
        let p: *u8 = "channel_send";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "channel_recv";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "channel_i32_send_c";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "channel_i32_bounded_c";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "channel_i32_unbounded_c";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "channel_i32_recv_c";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "channel_i32_try_send_c";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "channel_i32_try_recv_c";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "channel_i32_close_c";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "channel_i32_free_c";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "channel_i32_is_closed_c";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 8) {
      if (i == 0) {
        let p: *u8 = "std_backtrace_capture";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "backtrace_capture";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 9) {
      if (i == 0) {
        let p: *u8 = "std_math_sin";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_math_cos";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_math_tan";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_math_pi";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_math_e";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_math_tau";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_math_floor";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_math_ceil";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_math_trunc";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_math_round";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_math_sqrt";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_math_cbrt";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_math_pow";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_math_exp";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_math_log";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_math_abs";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_math_signum";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_math_min";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_math_max";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_math_asin";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_math_acos";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_math_atan";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_math_atan2";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "math_sin";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "math_cos";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "math_sin_c";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "math_cos_c";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "math_floor_c";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "math_pi_c";
        return p;
      }
      // PLATFORM: SHARED — fk9 gate was incomplete (only sin/cos/sin_c/cos_c/
      // floor_c/pi_c freestanding faces). Sole callers of any other
      // runtime_math_libm export (fmin/fmax/fabs/ceil/... — exact7v linked only
      // because floor_c rode along) never opened the gate → std/math/math.o
      // plan leaf skipped → runtime_math_libm.o never pulled → UNDEF at ld.
      // G.7 complete surface: every runtime_math_libm.x export that can be the
      // sole user UNDEF (trig / rounding / exp-log / minmax / fenv Cap faces).
      if (i == 29) {
        let p: *u8 = "math_acos_c";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "math_asin_c";
        return p;
      }
      if (i == 31) {
        let p: *u8 = "math_atan_c";
        return p;
      }
      if (i == 32) {
        let p: *u8 = "math_atan2_c";
        return p;
      }
      if (i == 33) {
        let p: *u8 = "math_cbrt_c";
        return p;
      }
      if (i == 34) {
        let p: *u8 = "math_ceil_c";
        return p;
      }
      if (i == 35) {
        let p: *u8 = "math_erf_c";
        return p;
      }
      if (i == 36) {
        let p: *u8 = "math_erfc_c";
        return p;
      }
      if (i == 37) {
        let p: *u8 = "math_exp_c";
        return p;
      }
      if (i == 38) {
        let p: *u8 = "math_expm1_c";
        return p;
      }
      if (i == 39) {
        let p: *u8 = "math_fabs_c";
        return p;
      }
      if (i == 40) {
        let p: *u8 = "math_fmax_c";
        return p;
      }
      if (i == 41) {
        let p: *u8 = "math_fmin_c";
        return p;
      }
      if (i == 42) {
        let p: *u8 = "math_log_c";
        return p;
      }
      if (i == 43) {
        let p: *u8 = "math_log1p_c";
        return p;
      }
      if (i == 44) {
        let p: *u8 = "math_pow_c";
        return p;
      }
      if (i == 45) {
        let p: *u8 = "math_round_c";
        return p;
      }
      if (i == 46) {
        let p: *u8 = "math_signum_c";
        return p;
      }
      if (i == 47) {
        let p: *u8 = "math_sqrt_c";
        return p;
      }
      if (i == 48) {
        let p: *u8 = "math_tan_c";
        return p;
      }
      if (i == 49) {
        let p: *u8 = "math_trunc_c";
        return p;
      }
      if (i == 50) {
        let p: *u8 = "math_fenv_available_c";
        return p;
      }
      if (i == 51) {
        let p: *u8 = "math_fenv_capability_smoke_c";
        return p;
      }
      if (i == 52) {
        let p: *u8 = "math_fenv_clear_c";
        return p;
      }
      if (i == 53) {
        let p: *u8 = "math_fenv_emit_cap_report";
        return p;
      }
      if (i == 54) {
        let p: *u8 = "math_fenv_fe_to_mask";
        return p;
      }
      if (i == 55) {
        let p: *u8 = "math_fenv_mask_to_fe";
        return p;
      }
      if (i == 56) {
        let p: *u8 = "math_fenv_raise_c";
        return p;
      }
      if (i == 57) {
        let p: *u8 = "math_fenv_smoke_c";
        return p;
      }
      if (i == 58) {
        let p: *u8 = "math_fenv_test_c";
        return p;
      }
      if (i == 59) {
        let p: *u8 = "math_special_near";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 10) {
      // PLATFORM: SHARED — unique-first cookbook sqlite_available, then remaining
      // unique std.db.sqlite export faces in mod.x source order, then legacy 3.
      if (i == 0) {
        let p: *u8 = "std_db_sqlite_is_available";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_db_sqlite_open";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_db_sqlite_close";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_db_sqlite_exec";
        return p;
      }
      if (i == 4) {
        let p: *u8 = "std_db_sqlite_rows";
        return p;
      }
      if (i == 5) {
        let p: *u8 = "std_db_sqlite_begin";
        return p;
      }
      if (i == 6) {
        let p: *u8 = "std_db_sqlite_next_row";
        return p;
      }
      if (i == 7) {
        let p: *u8 = "std_db_sqlite_col";
        return p;
      }
      if (i == 8) {
        let p: *u8 = "std_db_sqlite_col_text";
        return p;
      }
      if (i == 9) {
        let p: *u8 = "std_db_sqlite_col_blob";
        return p;
      }
      if (i == 10) {
        let p: *u8 = "std_db_sqlite_col_blob_len";
        return p;
      }
      if (i == 11) {
        let p: *u8 = "std_db_sqlite_col_blob_read";
        return p;
      }
      if (i == 12) {
        let p: *u8 = "std_db_sqlite_end";
        return p;
      }
      if (i == 13) {
        let p: *u8 = "std_db_sqlite_begin_tx";
        return p;
      }
      if (i == 14) {
        let p: *u8 = "std_db_sqlite_commit";
        return p;
      }
      if (i == 15) {
        let p: *u8 = "std_db_sqlite_rollback";
        return p;
      }
      if (i == 16) {
        let p: *u8 = "std_db_sqlite_last_error";
        return p;
      }
      if (i == 17) {
        let p: *u8 = "std_db_sqlite_backend_name";
        return p;
      }
      if (i == 18) {
        let p: *u8 = "std_db_sqlite_changes";
        return p;
      }
      if (i == 19) {
        let p: *u8 = "std_db_sqlite_prepare";
        return p;
      }
      if (i == 20) {
        let p: *u8 = "std_db_sqlite_prepare_cached";
        return p;
      }
      if (i == 21) {
        let p: *u8 = "std_db_sqlite_bind";
        return p;
      }
      if (i == 22) {
        let p: *u8 = "std_db_sqlite_step";
        return p;
      }
      if (i == 23) {
        let p: *u8 = "std_db_sqlite_reset";
        return p;
      }
      if (i == 24) {
        let p: *u8 = "std_db_sqlite_finalize";
        return p;
      }
      if (i == 25) {
        let p: *u8 = "std_db_sqlite_cache_clear";
        return p;
      }
      if (i == 26) {
        let p: *u8 = "std_db_sqlite_acquire";
        return p;
      }
      if (i == 27) {
        let p: *u8 = "std_db_sqlite_release";
        return p;
      }
      if (i == 28) {
        let p: *u8 = "std_db_sqlite_idle";
        return p;
      }
      if (i == 29) {
        let p: *u8 = "std_db_sqlite";
        return p;
      }
      if (i == 30) {
        let p: *u8 = "sqlite3_open";
        return p;
      }
      if (i == 31) {
        let p: *u8 = "db_sqlite_open";
        return p;
      }
      // Product -o that co-emits mod.x wrappers into the user TU UNDEFs
      // bare db_*_c (not std_db_sqlite_*). Exact matcher; one hit opens fk10.
      // PLATFORM: SHARED — Ubuntu gold first observed this UNDEF set.
      if (i == 32) {
        let p: *u8 = "db_open_c";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 11) {
      if (i == 0) {
        let p: *u8 = "std_elf_parse";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "elf_parse";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 12) {
      if (i == 0) {
        let p: *u8 = "std_dynlib_open";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_dynlib_sym";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "dynlib_open_c";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "dynlib_open";
        return p;
      }
      return 0 as *u8;
    }
    if (fk == 13) {
      if (i == 0) {
        let p: *u8 = "std_http_get";
        return p;
      }
      if (i == 1) {
        let p: *u8 = "std_http_request";
        return p;
      }
      if (i == 2) {
        let p: *u8 = "std_http_client_new";
        return p;
      }
      if (i == 3) {
        let p: *u8 = "std_http_request_timeout_ms_for_ctx";
        return p;
      }
      // PLATFORM: SHARED — plan fk==13 is the live http gate (not fk0 k==3).
      // Asm co-emit T std_http_get; sole UNDEF http_get_c (run-http Ubuntu).
      if (i == 4) {
        let p: *u8 = "http_get_c";
        return p;
      }
      return 0 as *u8;
    }
    return 0 as *u8;
  }
}

/**
 * Whether user .o needs std plan OP_STD step with flag_kind fk (1–13).
 * Pure orch: scan pure gate needle table; Cap residual xlang_link_obj_needs_undef_sym.
 * null/empty user_o → 1 (legacy hard-link when call site has no user_o).
 * Unknown fk (no table / fk0) → 1 (no gate here; fk0 uses labi_std_fk0_user_needs_rel).
 * @param user_o *u8 — path to user .o
 * @param fk i32 — plan flag_kind (1=process … 13=http)
 * @return i32 — 1 if gate open (push/ensure that std .o), else 0
 * Why (wave190): hybrid still had fk 1–13 gate probes always-mega inline in
 *   append_std_objs_for_user (soft residual sibling of wave135 fk0 pure table).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_fk_user_needs(user_o: *u8, fk: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (user_o == 0 as *u8) {
      return 1;
    }
    if (user_o[0] == 0) {
      return 1;
    }
    let n: i32 = labi_std_fk_gate_sym_count(fk);
    if (n <= 0) {
      return 1;
    }
    let i: i32 = 0;
    while (i < n) {
      let sym: *u8 = labi_std_fk_gate_sym_at(fk, i);
      if (sym != 0 as *u8) {
        if (sym[0] != 0) {
          let hit: i32 = 0;
          unsafe {
            hit = xlang_link_obj_needs_undef_sym(user_o, sym);
          }
          if (hit != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/* Pure rel constants for needs_* driven branches (early on_demand). */
/**
 * Relative path of formal std/net/net.o for on_demand push.
 * @return *u8 — static C string "std/net/net.o"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_rel_net(): *u8 {
  let p: *u8 = "std/net/net.o";
  return p;
}

/**
 * Relative path of formal std/error/error.o (net.o transitive U std_error_*).
 * @return *u8 — static C string "std/error/error.o"
 * PLATFORM: SHARED — co-pushed with net; user.o often has no error needles.
 */
#[no_mangle]
export function labi_od_rel_error(): *u8 {
  let p: *u8 = "std/error/error.o";
  return p;
}

/**
 * Relative path of formal std/context/context.o (net.o transitive U std_context_*).
 * @return *u8 — static C string "std/context/context.o"
 * PLATFORM: SHARED — co-pushed with net; pairs with atomic_glue + time_os.
 */
#[no_mangle]
export function labi_od_rel_context(): *u8 {
  let p: *u8 = "std/context/context.o";
  return p;
}

/**
 * Relative path of runtime_atomic_glue.o (context.o U atomic_load/store_i32_c).
 * @return *u8 — static C string "compiler/runtime_atomic_glue.o"
 * PLATFORM: SHARED — ≡ C-path need_context companions (invoke_cc_list).
 */
#[no_mangle]
export function labi_od_rel_atomic_glue(): *u8 {
  let p: *u8 = "compiler/runtime_atomic_glue.o";
  return p;
}

/**
 * Relative path of formal std/sync/sync.o (queue.o monofile U std_sync_*).
 * @return *u8 — static C string "std/sync/sync.o"
 * PLATFORM: SHARED — co-pushed with queue; user.o often has no sync needles
 *   (SyncQueue lives inside formal queue.o, invisible to user-only fk scan).
 */
#[no_mangle]
export function labi_od_rel_sync(): *u8 {
  let p: *u8 = "std/sync/sync.o";
  return p;
}

/**
 * Relative path of formal std/atomic/atomic.o (queue SyncQueue U std_atomic_*).
 * @return *u8 — static C string "std/atomic/atomic.o"
 * PLATFORM: SHARED — co-pushed with queue monofile SyncQueue path.
 */
#[no_mangle]
export function labi_od_rel_atomic(): *u8 {
  let p: *u8 = "std/atomic/atomic.o";
  return p;
}

/**
 * Relative path of runtime_sync_os.o (sync.o U sync_mutex_*_c / condvar / rwlock).
 * @return *u8 — static C string "compiler/runtime_sync_os.o"
 * PLATFORM: SHARED — ≡ plan OP_GLUE SYNC_PAIR second half.
 */
#[no_mangle]
export function labi_od_rel_sync_os(): *u8 {
  let p: *u8 = "compiler/runtime_sync_os.o";
  return p;
}

/**
 * Relative path of runtime_sync_lock_diag_tls.o (sync.o U lock_diag_*_c).
 * @return *u8 — static C string "compiler/runtime_sync_lock_diag_tls.o"
 * PLATFORM: SHARED — ≡ plan OP_GLUE SYNC_PAIR first half.
 */
#[no_mangle]
export function labi_od_rel_sync_lock_diag(): *u8 {
  let p: *u8 = "compiler/runtime_sync_lock_diag_tls.o";
  return p;
}

/** Exported function `labi_od_rel_thread`.
 * Read path helper `labi_od_rel_thread`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_thread(): *u8 {
  let p: *u8 = "std/thread/thread.o";
  return p;
}

/** Exported function `labi_od_rel_heap`.
 * Implements `labi_od_rel_heap`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_heap(): *u8 {
  let p: *u8 = "std/heap/heap.o";
  return p;
}

/** Exported function `labi_od_rel_set`.
 * Implements `labi_od_rel_set`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_set(): *u8 {
  let p: *u8 = "std/set/set.o";
  return p;
}

/** Exported function `labi_od_rel_map`.
 * Implements `labi_od_rel_map`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_map(): *u8 {
  let p: *u8 = "std/map/map.o";
  return p;
}

/** Exported function `labi_od_rel_async_scheduler`.
 * Implements `labi_od_rel_async_scheduler`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_async_scheduler(): *u8 {
  let p: *u8 = "std/async/scheduler.o";
  return p;
}

/** Exported function `labi_od_rel_core_mem`.
 * Implements `labi_od_rel_core_mem`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_core_mem(): *u8 {
  let p: *u8 = "core/mem/mem.o";
  return p;
}

/**
 * Relative product path for formal std/sys/linux.o (on-demand push).
 * @return *u8 — static C string "std/sys/linux.o"
 * PLATFORM: SHARED — nested leaf sys_linux product face.
 */
#[no_mangle]
export function labi_od_rel_sys_linux(): *u8 {
  let p: *u8 = "std/sys/linux.o";
  return p;
}

/**
 * Relative product path for formal std/sys/macos.o (on-demand push).
 * @return *u8 — static C string "std/sys/macos.o"
 * PLATFORM: SHARED — nested leaf sys_macos product face (Darwin cfg import).
 */
#[no_mangle]
export function labi_od_rel_sys_macos(): *u8 {
  let p: *u8 = "std/sys/macos.o";
  return p;
}

/**
 * Relative product path for formal std/heap/page_mmap.o (on-demand push).
 * @return *u8 — static C string "std/heap/page_mmap.o"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_rel_page_mmap(): *u8 {
  let p: *u8 = "std/heap/page_mmap.o";
  return p;
}

/** Exported function `labi_od_rel_sys`.
 * Implements `labi_od_rel_sys`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_sys(): *u8 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let p: *u8 = "std/sys/sys.o";
    return p;
  }
}

/** Exported function `labi_od_rel_core_slice`.
 * Implements `labi_od_rel_core_slice`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_core_slice(): *u8 {
  let p: *u8 = "core/slice/slice.o";
  return p;
}

/** Exported function `labi_od_rel_test`.
 * Implements `labi_od_rel_test`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_test(): *u8 {
  let p: *u8 = "std/test/test.o";
  return p;
}

/** Exported function `labi_od_rel_heap_user`.
 * Implements `labi_od_rel_heap_user`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_heap_user(): *u8 {
  let p: *u8 = "compiler/runtime_heap_user.o";
  return p;
}

/** Exported function `labi_od_rel_scheduler_glue`.
 * Implements `labi_od_rel_scheduler_glue`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_scheduler_glue(): *u8 {
  let p: *u8 = "compiler/runtime_scheduler_glue.o";
  return p;
}

/** Exported function `labi_od_rel_thread_glue`.
 * Read path helper `labi_od_rel_thread_glue`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_thread_glue(): *u8 {
  let p: *u8 = "compiler/runtime_thread_glue.o";
  return p;
}

/** Exported function `labi_od_rel_http_glue`.
 * wave958: http glue companion .o path for std.http on_demand ensure.
 * @return *u8 — static "compiler/runtime_http_glue.o"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_rel_http_glue(): *u8 {
  let p: *u8 = "compiler/runtime_http_glue.o";
  return p;
}

/** Exported function `labi_od_rel_net_udp_batch`.
 * Implements `labi_od_rel_net_udp_batch`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_net_udp_batch(): *u8 {
  let p: *u8 = "compiler/runtime_net_udp_batch.o";
  return p;
}

/** Exported function `labi_od_rel_net_workers`.
 * Implements `labi_od_rel_net_workers`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_net_workers(): *u8 {
  let p: *u8 = "compiler/runtime_net_workers.o";
  return p;
}

/** Exported function `labi_od_rel_test_fn_invoke`.
 * Implements `labi_od_rel_test_fn_invoke`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_rel_test_fn_invoke(): *u8 {
  let p: *u8 = "compiler/runtime_test_fn_invoke.o";
  return p;
}

/**
 * Relative path for runtime_env_os.o (std.env OS face: env_getenv_c*).
 * @return *u8 — static C string "compiler/runtime_env_os.o"
 * PLATFORM: SHARED — monofile test.o C dual U env_getenv_c (fuzz_seed).
 */
#[no_mangle]
export function labi_od_rel_env_os(): *u8 {
  let p: *u8 = "compiler/runtime_env_os.o";
  return p;
}

/**
 * Count of defined-symbol probes for user.o co-emit core.mem strong defs.
 * Used to skip hard-linking core/mem/mem.o when user.o already defines mem API.
 * @return i32 — 2
 * PLATFORM: SHARED — must match mega historical provides_core_mem surface
 */
#[no_mangle]
export function labi_od_provides_core_mem_sym_count(): i32 {
  return 2;
}

/**
 * Defined-symbol probe at index for user.o provides_core_mem.
 * @param i i32 — index in [0, 2)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 single product table (no second hard-coded list in mega)
 */
#[no_mangle]
export function labi_od_provides_core_mem_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "core_mem_mem_copy";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "core_mem_placeholder";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o already co-emits core.mem strong definitions (T/t).
 * Pure orch: fixed exact defined-sym table; Cap residual has_defined_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any defined probe hits, else 0
 * Why (wave140): hybrid still had provides_core_mem body always mega C hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_provides_core_mem(user_o: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (user_o == 0 as *u8) {
      return 0;
    }
    if (user_o[0] == 0) {
      return 0;
    }
    let n: i32 = labi_od_provides_core_mem_sym_count();
    let i: i32 = 0;
    while (i < n) {
      let sym: *u8 = labi_od_provides_core_mem_sym_at(i);
      if (sym != 0 as *u8) {
        if (sym[0] != 0) {
          let hit: i32 = 0;
          unsafe {
            hit = xlang_link_obj_has_defined_sym(user_o, sym);
          }
          if (hit != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Count of defined-symbol probes for user.o co-emit std.heap strong defs.
 * Used to skip hard-linking heap.o when user.o already defines libc heap API.
 * @return i32 — 2
 * PLATFORM: SHARED — must match mega historical provides_std_heap surface
 */
#[no_mangle]
export function labi_od_provides_std_heap_sym_count(): i32 {
  return 2;
}

/**
 * Defined-symbol probe at index for user.o provides_std_heap.
 * @param i i32 — index in [0, 2)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 single product table
 */
#[no_mangle]
export function labi_od_provides_std_heap_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_heap_libc_heap_alloc_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_heap_alloc_usize";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o already co-emits std.heap strong definitions (T/t).
 * Pure orch: fixed exact defined-sym table; Cap residual has_defined_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any defined probe hits, else 0
 * Why (wave140): hybrid still had provides_std_heap body always mega C hard-coded strings.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_provides_std_heap(user_o: *u8): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (user_o == 0 as *u8) {
      return 0;
    }
    if (user_o[0] == 0) {
      return 0;
    }
    let n: i32 = labi_od_provides_std_heap_sym_count();
    let i: i32 = 0;
    while (i < n) {
      let sym: *u8 = labi_od_provides_std_heap_sym_at(i);
      if (sym != 0 as *u8) {
        if (sym[0] != 0) {
          let hit: i32 = 0;
          unsafe {
            hit = xlang_link_obj_has_defined_sym(user_o, sym);
          }
          if (hit != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Whether user main .o or any already-pushed ld argv .o still needs heap_*_c user glue.
 * Aggregate pure orch: probe user_o via needs_heap_user_syms, then scan argv for .o entries
 * and re-probe each. Stops early on null argv slot (≡ mega: i < la && argv[i]).
 * @param user_o *u8 — primary user object path; null/empty skipped (still scan argv)
 * @param argv **u8 — ld argv table (char**); null → only user_o path
 * @param la i32 — argv length; la <= 0 → no argv scan
 * @return i32 — 1 if any object needs heap user symbols, else 0
 * Why (wave145): hybrid still had aggregate body always mega C; leaf needs_* pure since wave129.
 * Cap residual: none new — reuses pure needs_heap_user_syms + path_pure ld_argv_entry_is_obj.
 * Note: null-check argv via cast to *u8 (do not write `argv == 0 as **u8`; -E may drop body).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_link_needs_heap_user_c(user_o: *u8, argv: **u8, la: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: extern FFI must be in unsafe.
  unsafe {
    if (user_o != 0 as *u8) {
      if (user_o[0] != 0) {
        let uh: i32 = link_abi_user_o_needs_heap_user_syms(user_o);
        if (uh != 0) {
          return 1;
        }
      }
    }
    // Null-check argv without `0 as **u8` (see rt_emit_state discipline; -E body drop risk).
    let ab: *u8 = argv as *u8;
    if (ab == 0 as *u8) {
      return 0;
    }
    if (la <= 0) {
      return 0;
    }
    let i: i32 = 0;
    while (i < la) {
      let e: *u8 = argv[i];
      if (e == 0 as *u8) {
        return 0;
      }
      let is_obj: i32 = link_abi_ld_argv_entry_is_obj(e);
      if (is_obj != 0) {
        let need: i32 = link_abi_user_o_needs_heap_user_syms(e);
        if (need != 0) {
          return 1;
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Whether user main .o or any already-pushed ld argv .o needs formal std.heap API.
 * Aggregate pure orch: probe user_o via needs_std_heap_api, then scan argv .o entries.
 * Stops early on null argv slot (≡ mega: i < la && argv[i]).
 * @param user_o *u8 — primary user object path; null/empty skipped (still scan argv)
 * @param argv **u8 — ld argv table (char**); null → only user_o path
 * @param la i32 — argv length; la <= 0 → no argv scan
 * @return i32 — 1 if any object needs std heap API, else 0
 * Why (wave145): hybrid still had aggregate body always mega C; leaf needs_* pure since wave128.
 * Cap residual: none new — reuses pure needs_std_heap_api + path_pure ld_argv_entry_is_obj.
 * Note: null-check argv via cast to *u8 (do not write `argv == 0 as **u8`; -E may drop body).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_link_needs_std_heap_import(user_o: *u8, argv: **u8, la: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (user_o != 0 as *u8) {
      if (user_o[0] != 0) {
        let uh: i32 = link_abi_user_o_needs_std_heap_api(user_o);
        if (uh != 0) {
          return 1;
        }
      }
    }
    let ab: *u8 = argv as *u8;
    if (ab == 0 as *u8) {
      return 0;
    }
    if (la <= 0) {
      return 0;
    }
    let i: i32 = 0;
    while (i < la) {
      let e: *u8 = argv[i];
      if (e == 0 as *u8) {
        return 0;
      }
      let is_obj: i32 = link_abi_ld_argv_entry_is_obj(e);
      if (is_obj != 0) {
        let need: i32 = link_abi_user_o_needs_std_heap_api(e);
        if (need != 0) {
          return 1;
        }
      }
      i = i + 1;
    }
    return 0;
  }
}


/**
 * Pure first-match substring scan (≡ libc strstr non-null).
 * @param hay *u8 — haystack NUL-terminated; null/empty → 0
 * @param needle *u8 — needle NUL-terminated; null/empty → 0
 * @return i32 — 1 if needle occurs in hay, else 0
 * PLATFORM: SHARED pure; dual-end L2.
 * Track-L: not exported (internal helper for on_demand shell only).
 */
function labi_od_cstr_contains(hay: *u8, needle: *u8): i32 {
  if (hay == 0 as *u8) {
    return 0;
  }
  if (needle == 0 as *u8) {
    return 0;
  }
  if (hay[0] == 0) {
    return 0;
  }
  if (needle[0] == 0) {
    return 0;
  }
  let nlen: i32 = 0;
  while (needle[nlen] != 0) {
    nlen = nlen + 1;
  }
  let hlen: i32 = 0;
  while (hay[hlen] != 0) {
    hlen = hlen + 1;
  }
  if (nlen > hlen) {
    return 0;
  }
  let i: i32 = 0;
  while (i + nlen <= hlen) {
    let j: i32 = 0;
    let ok: i32 = 1;
    while (j < nlen) {
      if (ok != 0) {
        if (hay[i + j] != needle[j]) {
          ok = 0;
        }
      }
      j = j + 1;
    }
    if (ok != 0) {
      return 1;
    }
    i = i + 1;
  }
  return 0;
}

/**
 * Whether user_o has any UNDEF from simple on_demand group g (table + Cap undef_sym).
 * Pure orch ≡ mega static labi_od_user_needs_simple_group.
 * @param user_o *u8 — user .o path; null/empty → 0
 * @param g i32 — simple group index 0..count-1
 * @return i32 — 1 if any group symbol is UNDEF in user_o
 * PLATFORM: SHARED pure; Cap residual undef_sym.
 * Track-L: not exported (internal shell helper).
 */
function labi_od_user_needs_simple_group(user_o: *u8, g: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (user_o == 0 as *u8) {
      return 0;
    }
    if (user_o[0] == 0) {
      return 0;
    }
    let n: i32 = labi_od_simple_group_sym_count(g);
    if (n <= 0) {
      return 0;
    }
    let i: i32 = 0;
    while (i < n) {
      let s: *u8 = labi_od_simple_group_sym_at(g, i);
      if (s != 0 as *u8) {
        if (s[0] != 0) {
          let u: i32 = xlang_link_obj_needs_undef_sym(user_o, s);
          if (u != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Whether user_o has any UNDEF from a pure table accessed by count/at pair.
 * Specializations below call this with concrete table accessors.
 * @param user_o *u8 — user .o; null/empty → 0
 * @param n i32 — symbol count
 * @param which i32 — 0=kv 1=arrow 2=time 3=queue_contention 4=async unique
 * @return i32 — 1 if any UNDEF hit
 * PLATFORM: SHARED pure; Cap residual undef_sym.
 */
function labi_od_user_needs_table_which(user_o: *u8, n: i32, which: i32): i32 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (user_o == 0 as *u8) {
      return 0;
    }
    if (user_o[0] == 0) {
      return 0;
    }
    if (n <= 0) {
      return 0;
    }
    let i: i32 = 0;
    while (i < n) {
      let s: *u8 = 0 as *u8;
      if (which == 0) {
        s = labi_od_kv_sym_at(i);
      }
      if (which == 1) {
        s = labi_od_arrow_sym_at(i);
      }
      if (which == 2) {
        s = labi_od_time_sym_at(i);
      }
      if (which == 3) {
        s = labi_od_queue_sym_at(i);
      }
      if (which == 4) {
        s = labi_od_async_sym_at(i);
      }
      if (s != 0 as *u8) {
        if (s[0] != 0) {
          let u: i32 = xlang_link_obj_needs_undef_sym(user_o, s);
          if (u != 0) {
            return 1;
          }
        }
      }
      i = i + 1;
    }
    return 0;
  }
}

/**
 * Helper: if er==0, push glue_rel via primary (≡ push_glue_after_std without fn-ptr).
 * @param er i32 — ensure return (0 = success)
 * @param primary *u8 — preferred glue path (may be null)
 * @param link_argv0 *u8 — argv0
 * @param glue_rel *u8 — relative glue path
 * PLATFORM: SHARED pure thin.
 */
function labi_od_glue_push_if(er: i32, primary: *u8, link_argv0: *u8, glue_rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (er != 0) {
      return;
    }
    let ab: *u8 = argv as *u8;
    if (ab == 0 as *u8) {
      return;
    }
    if (la == 0 as *i32) {
      return;
    }
    let _p: i32 = 0;
    unsafe {
      _p = link_abi_asm_ld_push_obj(primary, link_argv0, glue_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    }
    if (_p == 0) {
      return;
    }
  }
}

/**
 * Thin trampoline: push std.test monofile companions via the invoke_ld authority.
 * Body lives in labi_std_append_test_monofile_companions (L6 / seed-phase1 TU).
 * Call sites (need_test + g12) keep this name so mega-frame spill stays thin.
 * @param link_argv0 *u8 — product host argv0
 * @param lib_roots **u8 — -L roots
 * @param n_lib_roots i32
 * @param bank *u8 — path bank (may be null)
 * @param argv **u8 — ld argv
 * @param la *i32 — argv length
 * @param max_la i32
 * PLATFORM: SHARED — zero-logic wrapper; G.7 single companion body in invoke_ld.
 */
#[no_mangle]
export function labi_od_push_test_monofile_companions(
  link_argv0: *u8,
  lib_roots: **u8,
  n_lib_roots: i32,
  bank: *u8,
  argv: **u8,
  la: *i32,
  max_la: i32
): void {
  labi_std_append_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
}

/**
 * Formal-ensure + push std/time/time.o and runtime_time_os.o.
 *
 * Thin helper: mega append_on_demand large-frame pure-asm spill mis-loads the
 * `rel` argument to push_obj (trel stored at low slot, call setup reloads a high
 * garbage slot → rel=0x100000000 → SEGV in push_obj ldrb). Small frame keeps
 * spill correct. Callers gate on user time needles (labi_od_time_sym_*).
 *
 * @param link_argv0 *u8 — product host argv0
 * @param lib_roots **u8 — -L roots
 * @param n_lib_roots i32
 * @param bank *u8 — path bank (may be null)
 * @param argv **u8 — ld argv
 * @param la *i32 — argv length
 * @param max_la i32
 * PLATFORM: SHARED pure thin — pure-asm run-time residual class.
 */
#[no_mangle]
export function labi_od_push_time_formal_and_os(
  link_argv0: *u8,
  lib_roots: **u8,
  n_lib_roots: i32,
  bank: *u8,
  argv: **u8,
  la: *i32,
  max_la: i32
): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {
    if (la == 0 as *i32) {
      return;
    }
    let ab: *u8 = argv as *u8;
    if (ab == 0 as *u8) {
      return;
    }
    let rtt: *u8 = 0 as *u8;
    unsafe {
      rtt = xlang_repo_root_from_argv0(link_argv0);
    }
    if (rtt != 0 as *u8) {
      if (rtt[0] != 0) {
        unsafe {
          let _te: i32 = xlang_ensure_formal_std_make_o(rtt, "std/time/time.o", "../std/time/time.o");
        }
      }
    }
    let er_to: i32 = 0;
    let top: *u8 = 0 as *u8;
    let torel: *u8 = labi_od_time_os_rel();
    unsafe {
      er_to = xlang_ensure_runtime_time_os_o(link_argv0);
      top = xlang_runtime_time_os_o_path(link_argv0);
    }
    if (er_to == 0) {
      unsafe {
        let _to: i32 = link_abi_asm_ld_push_obj(top, link_argv0, torel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }
    let trel: *u8 = labi_od_time_rel();
    unsafe {
      let _tm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, trel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    }
  }
}

/**
 * Resolve path: skip_missing(primary) else try_under(rel).
 * @return *u8 — path or null
 */
function labi_od_resolve_or_try(primary: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8): *u8 {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    let p: *u8 = 0 as *u8;
    if (primary != 0 as *u8) {
      unsafe {
        p = asm_link_obj_skip_missing(primary);
      }
    }
    if (p == 0 as *u8) {
      if (bank != 0 as *u8) {
        if (rel != 0 as *u8) {
          unsafe {
            p = xlang_asm_ld_try_under_lib_roots(rel, lib_roots, n_lib_roots, bank);
          }
        }
      }
    }
    return p;
  }
}

/**
 * Product on_demand shell: push formal/runtime .o for UNDEFs in user_o.
 * Pure orch composes existing peers (G.7 no second needs/push/ensure path):
 *   net/thread/glue → heap import (provides skip) → set/map formal → async sched →
 *   core_mem → freestanding-gated page_mmap/sys → core_slice → kv/arrow →
 *   test glue → heap_user → simple groups (+ core formal ensure) →
 *   process_argv complement scan → time formal+os → queue product/contention.
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param user_o *u8 — user main .o; null/empty → no-op
 * @param lib_roots **u8 — -L style roots
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length; null or near-full → no-op
 * @param max_la i32 — argv capacity
 * @param flags *u8 — ShuAsmLdStdLinkFlags* opaque; may be null
 * Cap residual: ensure_* / skip_missing / freestanding_get / undef_sym (inside peers).
 * Why (wave197): hybrid still had full on_demand IO shell always-mega after wave118–145
 *   needs/provides pure (soft residual "on_demand body").
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2 (POSIX product; Windows hybrid not gold).
 * Track-L: #[no_mangle] product short name (mega call sites / old wrapper).
 */
#[no_mangle]
export function xlang_asm_ld_append_on_demand_user_objs(link_argv0: *u8, user_o: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flags: *u8): void {
  // PLATFORM: SHARED — LANG-007 S0: Cap-T001 whole-body unsafe FFI gate.
  unsafe {

    if (user_o == 0 as *u8) {
      return;
    }
    if (user_o[0] == 0) {
      return;
    }
    if (la == 0 as *i32) {
      return;
    }
    if (la[0] >= max_la - 1) {
      return;
    }
    let ab: *u8 = argv as *u8;
    if (ab == 0 as *u8) {
      return;
    }

    // --- net + thread companions ---
    // PLATFORM: SHARED — net.o carries U std_error_* / std_context_* (timeout/ctx IO).
    // User.o typically only U net_tcp_* so fk0 error/context user needles miss.
    // G.7 companions ≡ C-path need_context (error formal + context formal +
    // atomic_glue + time_os) plus existing thread/udp/workers glue.
    let need_net: i32 = link_abi_user_o_needs_std_net(user_o);
    if (need_net != 0) {
      let have_net: i32 = 0;
      let rel_net: *u8 = labi_od_rel_net();
      // PLATFORM: SHARED — L4 wipe deletes net.o; push_obj skip-missing is
      // not enough (≡ need_sys). Cookbook net_listen_bind UNDEF std_net_listen
      // / close_listener while needles already fire. Produce path is existing
      // net_merge via compiler-make try-heat (not formal_mod). G.7: complete
      // existing need_net path with ensure; do not add a second simple-group
      // or convert net_merge into formal_mod.
      let root_net_ensure: *u8 = 0 as *u8;
      unsafe {
        root_net_ensure = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_net_ensure != 0 as *u8) {
        if (root_net_ensure[0] != 0) {
          unsafe {
            let _enet: i32 = xlang_ensure_formal_std_make_o(root_net_ensure, "std/net/net.o", "../std/net/net.o");
          }
        }
      }
      unsafe {
        let _n: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel_net, lib_roots, n_lib_roots, bank, argv, la, max_la, &have_net);
      }
      if (have_net != 0) {
        if (flags != 0 as *u8) {
          let f: *i32 = flags as *i32;
          f[1] = 1;
        }
        // error.o + context.o formal ensure (L4 wipe drops gitignored .o) then push.
        let root_net: *u8 = 0 as *u8;
        unsafe {
          root_net = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_net != 0 as *u8) {
          if (root_net[0] != 0) {
            unsafe {
              let _fe_err: i32 = xlang_ensure_formal_std_make_o(root_net, "std/error/error.o", "../std/error/error.o");
              let _fe_ctx: i32 = xlang_ensure_formal_std_make_o(root_net, "std/context/context.o", "../std/context/context.o");
            }
          }
        }
        let rel_err: *u8 = labi_od_rel_error();
        let rel_ctx: *u8 = labi_od_rel_context();
        unsafe {
          let _pe: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel_err, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          let _pc: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel_ctx, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        // context.o U atomic_*_i32_c + time_now_monotonic_ns_c (≡ invoke_cc need_context).
        let er_ag: i32 = 0;
        let agp: *u8 = 0 as *u8;
        let agrel: *u8 = labi_od_rel_atomic_glue();
        unsafe {
          er_ag = xlang_ensure_runtime_atomic_glue_o(link_argv0);
          agp = xlang_runtime_atomic_glue_o_path(link_argv0);
        }
        labi_od_glue_push_if(er_ag, agp, link_argv0, agrel, lib_roots, n_lib_roots, bank, argv, la, max_la);
        let er_to: i32 = 0;
        let top: *u8 = 0 as *u8;
        let torel: *u8 = labi_od_time_os_rel();
        unsafe {
          er_to = xlang_ensure_runtime_time_os_o(link_argv0);
          top = xlang_runtime_time_os_o_path(link_argv0);
        }
        labi_od_glue_push_if(er_to, top, link_argv0, torel, lib_roots, n_lib_roots, bank, argv, la, max_la);
        let rel_th: *u8 = labi_od_rel_thread();
        let have_th: i32 = 0;
        // PLATFORM: SHARED — net.o T net_run_accept_workers_c U thread_create_c
        // (thread_glue). L4 wipe deletes thread.o; skip-missing never pushes
        // glue. Darwin -dead_strip hid unused workers T; Ubuntu gold exposes
        // UNDEF. G.7 complete existing need_net thread companion with formal
        // ensure (≡ error/context); do not add a second table.
        if (root_net_ensure != 0 as *u8) {
          if (root_net_ensure[0] != 0) {
            unsafe {
              let _eth: i32 = xlang_ensure_formal_std_make_o(root_net_ensure, "std/thread/thread.o", "../std/thread/thread.o");
            }
          }
        }
        unsafe {
          let _t: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel_th, lib_roots, n_lib_roots, bank, argv, la, max_la, &have_th);
        }
        if (have_th != 0) {
          if (flags != 0 as *u8) {
            let f2: *i32 = flags as *i32;
            f2[2] = 1;
          }
          let er: i32 = 0;
          let tp: *u8 = 0 as *u8;
          let trel: *u8 = labi_od_rel_thread_glue();
          unsafe {
            er = xlang_ensure_runtime_thread_glue_o(link_argv0);
            tp = xlang_runtime_thread_glue_o_path(link_argv0);
          }
          labi_od_glue_push_if(er, tp, link_argv0, trel, lib_roots, n_lib_roots, bank, argv, la, max_la);
        }
        // net udp batch + workers glue (always after have_net; ensure then push)
        let er_u: i32 = 0;
        let up: *u8 = 0 as *u8;
        let urel: *u8 = labi_od_rel_net_udp_batch();
        unsafe {
          er_u = xlang_ensure_runtime_net_udp_batch_o(link_argv0);
          up = xlang_runtime_net_udp_batch_o_path(link_argv0);
        }
        labi_od_glue_push_if(er_u, up, link_argv0, urel, lib_roots, n_lib_roots, bank, argv, la, max_la);
        let er_w: i32 = 0;
        let wp: *u8 = 0 as *u8;
        let wrel: *u8 = labi_od_rel_net_workers();
        unsafe {
          er_w = xlang_ensure_runtime_net_workers_o(link_argv0);
          wp = xlang_runtime_net_workers_o_path(link_argv0);
        }
        labi_od_glue_push_if(er_w, wp, link_argv0, wrel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
    }

    /*
     * wave956: standalone std.thread on_demand (independent of need_net).
     * Before wave956: thread.o + thread_glue.o were only pushed inside the
     * need_net block above; user programs importing only std.thread (no
     * std.net) never triggered thread.o ensure → BLD001 UNDEF std_thread_*.
     * Probe: link_abi_user_o_needs_std_thread scans labi_od_thread_sym_*
     * (std_thread_create / join / start / stats). When hit, push thread.o
     * then ensure + push thread_glue.o (same as the net-embedded thread
     * path). Skip if need_net already pushed thread.o (have_th flag f[2]).
     * PLATFORM: SHARED. G.7: single thread ensure path (table + this block).
     */
    let need_thread_alone: i32 = link_abi_user_o_needs_std_thread(user_o);
    if (need_thread_alone != 0) {
      let already_th: i32 = 0;
      if (flags != 0 as *u8) {
        let ff: *i32 = flags as *i32;
        already_th = ff[2];
      }
      if (already_th == 0) {
        let rel_th2: *u8 = labi_od_rel_thread();
        let have_th2: i32 = 0;
        unsafe {
          let _t2: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel_th2, lib_roots, n_lib_roots, bank, argv, la, max_la, &have_th2);
        }
        if (have_th2 != 0) {
          if (flags != 0 as *u8) {
            let f3: *i32 = flags as *i32;
            f3[2] = 1;
          }
          let er2: i32 = 0;
          let tp2: *u8 = 0 as *u8;
          let trel2: *u8 = labi_od_rel_thread_glue();
          unsafe {
            er2 = xlang_ensure_runtime_thread_glue_o(link_argv0);
            tp2 = xlang_runtime_thread_glue_o_path(link_argv0);
          }
          labi_od_glue_push_if(er2, tp2, link_argv0, trel2, lib_roots, n_lib_roots, bank, argv, la, max_la);
        }
      }
    }

    /*
     * wave958: standalone std.vec on_demand. Before wave958: no vec probe
     * table existed; user programs using Vec<u16/i32/u8> hit BLD001 UNDEF.
     * Probe: link_abi_user_o_needs_std_vec scans labi_od_vec_sym_* (push/
     * get/length/deinit/capacity/clear/from_slice plus pop/extend plus
     * from_slice_u64/f64 plus push_u64/f64 plus length/get/deinit u64/f64).
     * When hit, ensure + push std/vec/vec.o. PLATFORM: SHARED.
     */
    let need_vec: i32 = link_abi_user_o_needs_std_vec(user_o);
    if (need_vec != 0) {
      let root_vec: *u8 = 0 as *u8;
      unsafe {
        root_vec = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_vec != 0 as *u8) {
        if (root_vec[0] != 0) {
          unsafe {
            let _ev: i32 = xlang_ensure_formal_std_make_o(root_vec, "std/vec/vec.o", "../std/vec/vec.o");
          }
        }
      }
      let rv: *u8 = labi_od_rel_vec();
      unsafe {
        let _pv: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rv, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }

    /*
     * wave958: standalone std.http on_demand. Before wave958: no http probe
     * table existed; user programs using http.parse_status_line / decode_chunked
     * / has_chunked_encoding / has_keep_alive / headers_body_offset hit BLD001
     * UNDEF. Probe: link_abi_user_o_needs_std_http scans labi_od_http_sym_*.
     * When hit, ensure + push std/http/http.o + runtime_http_glue.o (http.o
     * has UNDEF _http_*_c symbols defined in compiler/runtime_http_glue.o).
     * PLATFORM: SHARED.
     */
    let need_http: i32 = link_abi_user_o_needs_std_http(user_o);
    if (need_http != 0) {
      let root_http: *u8 = 0 as *u8;
      unsafe {
        root_http = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_http != 0 as *u8) {
        if (root_http[0] != 0) {
          unsafe {
            let _eh2: i32 = xlang_ensure_formal_std_make_o(root_http, "std/http/http.o", "../std/http/http.o");
          }
        }
      }
      let rh2: *u8 = labi_od_rel_http();
      unsafe {
        let _ph2: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rh2, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
      let erh: i32 = 0;
      let tph: *u8 = 0 as *u8;
      let trelh: *u8 = labi_od_rel_http_glue();
      unsafe {
        erh = xlang_ensure_runtime_http_glue_o(link_argv0);
        tph = xlang_runtime_http_glue_o_path(link_argv0);
      }
      labi_od_glue_push_if(erh, tph, link_argv0, trelh, lib_roots, n_lib_roots, bank, argv, la, max_la);
    }

    // --- heap import (skip if user provides) ---
    // Aggregate already scans user_o + argv .o (append_std pushed http.o first).
    // L4 wipe deletes heap.o: push_obj skip-missing is not enough — ensure first
    // (≡ set/map companions). PLATFORM: SHARED — Darwin hard UNDEF if heap.o absent.
    let la_n: i32 = la[0];
    let need_hi: i32 = link_abi_link_needs_std_heap_import(user_o, argv, la_n);
    if (need_hi != 0) {
      let root_h: *u8 = 0 as *u8;
      unsafe {
        root_h = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_h != 0 as *u8) {
        if (root_h[0] != 0) {
          unsafe {
            let _eh: i32 = xlang_ensure_formal_std_make_o(root_h, "std/heap/heap.o", "../std/heap/heap.o");
            let _em: i32 = xlang_ensure_formal_std_make_o(root_h, "core/mem/mem.o", "../core/mem/mem.o");
          }
        }
      }
      let prov_m: i32 = link_abi_user_o_provides_core_mem(user_o);
      if (prov_m == 0) {
        let rm: *u8 = labi_od_rel_core_mem();
        unsafe {
          let _m: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
      // Always push heap.o when needs_std_heap_api fired.
      // Product asm -o co-emits libc/alloc wrappers as T (provides_std_heap
      // hits std_heap_libc_heap_alloc_c) while still U std_heap_mem_set
      // (core_mem_mem_zero call). Two-probe provides is too coarse.
      // Product ld --allow-multiple-definition (first-wins user T).
      // G.7: complete this single heap push. PLATFORM: SHARED.
      let rh: *u8 = labi_od_rel_heap();
      unsafe {
        let _h: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rh, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }

    // --- set formal + companions ---
    let need_set: i32 = link_abi_user_o_needs_std_set(user_o);
    if (need_set != 0) {
      let root: *u8 = 0 as *u8;
      unsafe {
        root = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root != 0 as *u8) {
        if (root[0] != 0) {
          unsafe {
            let _e1: i32 = xlang_ensure_formal_std_make_o(root, "std/set/set.o", "../std/set/set.o");
            let _e2: i32 = xlang_ensure_formal_std_make_o(root, "std/heap/heap.o", "../std/heap/heap.o");
            let _e3: i32 = xlang_ensure_formal_std_make_o(root, "core/mem/mem.o", "../core/mem/mem.o");
            let _e4: i32 = xlang_ensure_formal_std_make_o(root, "std/hash/hash.o", "../std/hash/hash.o");
          }
        }
      }
      let rs: *u8 = labi_od_rel_set();
      let rh2: *u8 = labi_od_rel_heap();
      let rm2: *u8 = labi_od_rel_core_mem();
      unsafe {
        let _s: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rs, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _sh: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rh2, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _sm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rm2, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _hh: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/hash/hash.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }

    // --- map formal + companions ---
    let need_map: i32 = link_abi_user_o_needs_std_map(user_o);
    if (need_map != 0) {
      let rootm: *u8 = 0 as *u8;
      unsafe {
        rootm = xlang_repo_root_from_argv0(link_argv0);
      }
      if (rootm != 0 as *u8) {
        if (rootm[0] != 0) {
          unsafe {
            let _m1: i32 = xlang_ensure_formal_std_make_o(rootm, "std/map/map.o", "../std/map/map.o");
            let _m2: i32 = xlang_ensure_formal_std_make_o(rootm, "std/heap/heap.o", "../std/heap/heap.o");
            let _m3: i32 = xlang_ensure_formal_std_make_o(rootm, "core/mem/mem.o", "../core/mem/mem.o");
          }
        }
      }
      let rmap: *u8 = labi_od_rel_map();
      let rhm: *u8 = labi_od_rel_heap();
      let rmm: *u8 = labi_od_rel_core_mem();
      unsafe {
        let _mp: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rmap, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _mph: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rhm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _mpm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rmm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }

    // --- async scheduler + glue ---
    let need_as: i32 = link_abi_user_o_needs_async_scheduler(user_o);
    if (need_as != 0) {
      let spath: *u8 = 0 as *u8;
      unsafe {
        spath = xlang_std_async_scheduler_o_path(link_argv0);
      }
      let p_as: *u8 = labi_od_resolve_or_try(spath, labi_od_rel_async_scheduler(), lib_roots, n_lib_roots, bank);
      if (p_as != 0 as *u8) {
        if (la[0] < max_la - 1) {
          unsafe {
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_as);
          }
        }
        if (la[0] < max_la - 1) {
          let gpath: *u8 = 0 as *u8;
          unsafe {
            gpath = xlang_runtime_scheduler_glue_o_path(link_argv0);
          }
          let p_sg: *u8 = labi_od_resolve_or_try(gpath, labi_od_rel_scheduler_glue(), lib_roots, n_lib_roots, bank);
          if (p_sg != 0 as *u8) {
            unsafe {
              link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_sg);
            }
          }
        }
      }
    }

    // --- core_mem (user needs) ---
    let need_cm: i32 = link_abi_user_o_needs_core_mem(user_o);
    if (need_cm != 0) {
      let crel: *u8 = labi_od_rel_core_mem();
      let cprim: *u8 = 0 as *u8;
      unsafe {
        cprim = xlang_rel_o_path_from_argv0(link_argv0, crel);
      }
      let p_cm: *u8 = labi_od_resolve_or_try(cprim, crel, lib_roots, n_lib_roots, bank);
      if (p_cm != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_cm);
        }
      }
    }

    // --- freestanding-gated page_mmap / sys / linux ---
    let fs: i32 = 0;
    unsafe {
      fs = driver_freestanding_get();
    }
    if (fs == 0) {
      let need_pm: i32 = link_abi_user_o_needs_std_heap_page_mmap(user_o);
      let need_sl: i32 = link_abi_user_o_needs_std_sys_linux(user_o);
      let need_sm: i32 = link_abi_user_o_needs_std_sys_macos(user_o);
      let need_sy: i32 = link_abi_user_o_needs_std_sys(user_o);
      // Scan already-pushed argv for formal heap → page_mmap needs
      let ai: i32 = 0;
      let la_now: i32 = la[0];
      while (ai < la_now) {
        let e: *u8 = argv[ai];
        if (e == 0 as *u8) {
          // stop like mega for-loop && argv[ai]
          ai = la_now;
        }
        if (e != 0 as *u8) {
          let is_obj: i32 = 0;
          unsafe {
            is_obj = link_abi_ld_argv_entry_is_obj(e);
          }
          if (is_obj != 0) {
            if (link_abi_user_o_needs_std_heap_page_mmap(e) != 0) {
              need_pm = 1;
            }
            if (link_abi_user_o_needs_std_sys_linux(e) != 0) {
              need_sl = 1;
            }
            if (link_abi_user_o_needs_std_sys_macos(e) != 0) {
              need_sm = 1;
            }
            if (link_abi_user_o_needs_std_sys(e) != 0) {
              need_sy = 1;
            }
          }
        }
        ai = ai + 1;
      }
      let need_any_sys: i32 = 0;
      if (need_sl != 0) {
        need_any_sys = 1;
      }
      if (need_pm != 0) {
        need_any_sys = 1;
      }
      if (need_sy != 0) {
        need_any_sys = 1;
      }
      if (need_any_sys != 0) {
        // PLATFORM: SHARED — L4 wipe deletes linux.o; twin of need_sys ensure.
        // Nested leaf rename makes linux.o the authority for std_sys_linux_linux_*.
        let root_sl: *u8 = 0 as *u8;
        unsafe {
          root_sl = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_sl != 0 as *u8) {
          if (root_sl[0] != 0) {
            unsafe {
              let _esl: i32 = xlang_ensure_formal_std_make_o(root_sl, "std/sys/linux.o", "../std/sys/linux.o");
            }
          }
        }
        let rsl: *u8 = labi_od_rel_sys_linux();
        unsafe {
          let _sl: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rsl, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        // PLATFORM: LINUX|x86_64 — linux.o itself only *calls* xlang_sys_*;
        // the raw syscall stubs live in compiler/src/asm/freestanding_io_x86_64.o
        // (product main-link object). Hosted user links that co-emit
        // std.sys.linux need it pushed too (run-process BLD001
        // xlang_sys_close/connect root). Mirrors the seed twin.
        unsafe {
          let _fio: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/src/asm/freestanding_io_x86_64.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
      if (need_sm != 0) {
        // PLATFORM: SHARED — Darwin cfg import macos_write_*; ensure+push macos.o.
        let root_sm: *u8 = 0 as *u8;
        unsafe {
          root_sm = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_sm != 0 as *u8) {
          if (root_sm[0] != 0) {
            unsafe {
              let _esm: i32 = xlang_ensure_formal_std_make_o(root_sm, "std/sys/macos.o", "../std/sys/macos.o");
            }
          }
        }
        let rsm: *u8 = labi_od_rel_sys_macos();
        unsafe {
          let _sm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rsm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
      // core_mem when page_mmap or sys
      let need_cm_sys: i32 = 0;
      if (need_pm != 0) {
        need_cm_sys = 1;
      }
      if (need_sy != 0) {
        need_cm_sys = 1;
      }
      if (need_cm_sys != 0) {
        let rcm: *u8 = labi_od_rel_core_mem();
        unsafe {
          let _cm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rcm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
      if (need_pm != 0) {
        let rpm: *u8 = labi_od_rel_page_mmap();
        unsafe {
          let _pm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rpm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
      if (need_sy != 0) {
        // PLATFORM: SHARED — L4 wipe deletes sys.o; skip-missing push is not
        // enough (≡ heap/vec/http). Needles already fire; cookbook
        // sys_write_stdout UNDEF std_sys_write_stdout until formal ensure.
        // G.7: complete existing need_sys path; no second simple-group table.
        let root_sy: *u8 = 0 as *u8;
        unsafe {
          root_sy = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_sy != 0 as *u8) {
          if (root_sy[0] != 0) {
            unsafe {
              let _esy: i32 = xlang_ensure_formal_std_make_o(root_sy, "std/sys/sys.o", "../std/sys/sys.o");
            }
          }
        }
        let rsy: *u8 = labi_od_rel_sys();
        unsafe {
          let _sy: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rsy, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }

    // --- core_slice ---
    let need_cs: i32 = link_abi_user_o_needs_core_slice(user_o);
    if (need_cs != 0) {
      // PLATFORM: SHARED — L4 wipe deletes core/slice/slice.o; the silent
      // resolve_or_try skip below then leaves core_subslice_*_c UNDEF
      // (subslice_split_chunks BLD001). Mirror the sys.o discipline: ensure
      // the formal make before resolving. G.7: same single ensure authority.
      let root_cs: *u8 = 0 as *u8;
      unsafe {
        root_cs = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_cs != 0 as *u8) {
        if (root_cs[0] != 0) {
          unsafe {
            let _ecs: i32 = xlang_ensure_formal_std_make_o(root_cs, "core/slice/slice.o", "../core/slice/slice.o");
          }
        }
      }
      let csrel: *u8 = labi_od_rel_core_slice();
      let csprim: *u8 = 0 as *u8;
      unsafe {
        csprim = xlang_rel_o_path_from_argv0(link_argv0, csrel);
      }
      let p_cs: *u8 = labi_od_resolve_or_try(csprim, csrel, lib_roots, n_lib_roots, bank);
      if (p_cs != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_cs);
        }
      }
      /*
       * wave957: X-facing core_slice u64 symbols (chunks_len / split_at /
       * subslice) are in core/slice/mod.o (API), not slice.o (glue). Push
       * mod.o too when needs_core_slice fires. Before wave957: only glue
       * was pushed → BLD001 UNDEF for user programs using slice.subslice_u64.
       * G.7: complete the single core_slice ensure path. PLATFORM: SHARED.
       */
      let csmod_rel: *u8 = "core/slice/mod.o";
      let csmod_prim: *u8 = 0 as *u8;
      unsafe {
        csmod_prim = xlang_rel_o_path_from_argv0(link_argv0, csmod_rel);
      }
      let p_csmod: *u8 = labi_od_resolve_or_try(csmod_prim, csmod_rel, lib_roots, n_lib_roots, bank);
      if (p_csmod != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_csmod);
        }
      }
    }

    // --- kv + glue ---
    let n_kv: i32 = labi_od_kv_sym_count();
    if (labi_od_user_needs_table_which(user_o, n_kv, 0) != 0) {
      // PLATFORM: SHARED — L4 wipe deletes kv.o; skip-missing never ensure
      // (≡ need_sys). Produce path is formal_mod mod.x+kv.x. Twin of L8b seed.
      let root_kv: *u8 = 0 as *u8;
      unsafe {
        root_kv = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_kv != 0 as *u8) {
        if (root_kv[0] != 0) {
          unsafe {
            let _ekv: i32 = xlang_ensure_formal_std_make_o(root_kv, "std/db/kv/kv.o", "../std/db/kv/kv.o");
          }
        }
      }
      let kvrel: *u8 = labi_od_kv_rel();
      let kvprim: *u8 = 0 as *u8;
      unsafe {
        kvprim = xlang_rel_o_path_from_argv0(link_argv0, kvrel);
      }
      let p_kv: *u8 = labi_od_resolve_or_try(kvprim, kvrel, lib_roots, n_lib_roots, bank);
      if (p_kv != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_kv);
        }
        unsafe {
          let _kg: i32 = xlang_ensure_runtime_kv_mmap_glue_o(link_argv0);
        }
        let kvp: *u8 = 0 as *u8;
        unsafe {
          kvp = xlang_runtime_kv_mmap_glue_o_path(link_argv0);
        }
        let p_kg: *u8 = labi_od_resolve_or_try(kvp, labi_od_kv_glue_rel(), lib_roots, n_lib_roots, bank);
        if (p_kg != 0 as *u8) {
          unsafe {
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_kg);
          }
        }
      }
    }

    // --- arrow + glue ---
    let n_ar: i32 = labi_od_arrow_sym_count();
    if (labi_od_user_needs_table_which(user_o, n_ar, 1) != 0) {
      // PLATFORM: SHARED — L4 wipe deletes arrow.o; skip-missing never ensure.
      // simd c_face companion for simd_hw_available_c. Twin of L8b seed.
      let root_ar: *u8 = 0 as *u8;
      unsafe {
        root_ar = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_ar != 0 as *u8) {
        if (root_ar[0] != 0) {
          unsafe {
            let _ear: i32 = xlang_ensure_formal_std_make_o(root_ar, "std/db/arrow/arrow.o", "../std/db/arrow/arrow.o");
            let _esi: i32 = xlang_ensure_formal_std_make_o(root_ar, "std/simd/simd.o", "../std/simd/simd.o");
          }
        }
      }
      let arrel: *u8 = labi_od_arrow_rel();
      let arprim: *u8 = 0 as *u8;
      unsafe {
        arprim = xlang_rel_o_path_from_argv0(link_argv0, arrel);
      }
      let p_ar: *u8 = labi_od_resolve_or_try(arprim, arrel, lib_roots, n_lib_roots, bank);
      if (p_ar != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_ar);
        }
        unsafe {
          let _si: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/simd/simd.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          let _ag: i32 = xlang_ensure_runtime_arrow_simd_glue_o(link_argv0);
        }
        let arp: *u8 = 0 as *u8;
        unsafe {
          arp = xlang_runtime_arrow_simd_glue_o_path(link_argv0);
        }
        let p_ag: *u8 = labi_od_resolve_or_try(arp, labi_od_arrow_glue_rel(), lib_roots, n_lib_roots, bank);
        if (p_ag != 0 as *u8) {
          unsafe {
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_ag);
          }
        }
      }
    }

    // --- async unique c_face + scheduler glue ---
    let n_as: i32 = labi_od_async_sym_count();
    if (labi_od_user_needs_table_which(user_o, n_as, 4) != 0) {
      // PLATFORM: SHARED — leftover unique UNDEF std_async_placeholder /
      // drain_idle / scheduler_reset / net_fs_async_smoke. No async.o existed;
      // scheduler C ABI table never fires unique import METHOD. Produce path is
      // formal_mod c_face (+ scheduler_glue for net_fs smoke body). Twin of L8b seed.
      let root_as: *u8 = 0 as *u8;
      unsafe {
        root_as = xlang_repo_root_from_argv0(link_argv0);
      }
      if (root_as != 0 as *u8) {
        if (root_as[0] != 0) {
          unsafe {
            let _eas: i32 = xlang_ensure_formal_std_make_o(root_as, "std/async/async.o", "../std/async/async.o");
          }
        }
      }
      let asrel: *u8 = labi_od_async_rel();
      let asprim: *u8 = 0 as *u8;
      unsafe {
        asprim = xlang_rel_o_path_from_argv0(link_argv0, asrel);
      }
      let p_as2: *u8 = labi_od_resolve_or_try(asprim, asrel, lib_roots, n_lib_roots, bank);
      if (p_as2 != 0 as *u8) {
        unsafe {
          link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_as2);
        }
        unsafe {
          let _sg: i32 = xlang_ensure_runtime_scheduler_glue_o(link_argv0);
        }
        let sgp: *u8 = 0 as *u8;
        unsafe {
          sgp = xlang_runtime_scheduler_glue_o_path(link_argv0);
        }
        let p_sg2: *u8 = labi_od_resolve_or_try(sgp, labi_od_rel_scheduler_glue(), lib_roots, n_lib_roots, bank);
        if (p_sg2 != 0 as *u8) {
          unsafe {
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_sg2);
          }
        }
      }
    }

    // --- test + monofile companions (fn_invoke / env_os / time_os) ---
    // PLATFORM: SHARED — pure-asm run-stdtest residual: always formal-ensure test.o
    // before push (L4 wipe / stale marker .o lack std_test_* T surface).
    // Monofile C dual U test_call_i32_void_c / env_getenv_c / time_now_monotonic_ns_c
    // even when user.o only names std_test_expect* (≡ queue/net companion class).
    // Companions always after need_test (not only have_test): mega-frame spill can
    // leave have_test=0 while g12 still lands test.o; thin helper is idempotent.
    let need_test: i32 = link_abi_user_o_needs_std_test(user_o);
    if (need_test != 0) {
      let rt_test: *u8 = 0 as *u8;
      unsafe {
        rt_test = xlang_repo_root_from_argv0(link_argv0);
      }
      if (rt_test != 0 as *u8) {
        if (rt_test[0] != 0) {
          unsafe {
            let _fe_t: i32 = xlang_ensure_formal_std_make_o(rt_test, "std/test/test.o", "../std/test/test.o");
          }
        }
      }
      let trel: *u8 = labi_od_rel_test();
      unsafe {
        let _tt: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, trel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
      unsafe {
        labi_od_push_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
    }

    // --- heap_user (not freestanding) ---
    if (fs == 0) {
      let la_hu: i32 = la[0];
      let need_hu: i32 = link_abi_link_needs_heap_user_c(user_o, argv, la_hu);
      if (need_hu != 0) {
        let er_hu: i32 = 0;
        unsafe {
          er_hu = xlang_ensure_runtime_heap_user_o(link_argv0);
        }
        if (er_hu != 0) {
          return;
        }
        let hup: *u8 = 0 as *u8;
        let hurel: *u8 = labi_od_rel_heap_user();
        unsafe {
          hup = xlang_runtime_heap_user_o_path(link_argv0);
          let _hu: i32 = link_abi_asm_ld_push_obj(hup, link_argv0, hurel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        if (flags != 0 as *u8) {
          let fh: *i32 = flags as *i32;
          fh[10] = 1;
        }
      }
    }

    // --- simple multi-sym groups ---
    let pushed_core_formal: i32 = 0;
    let gcount: i32 = labi_od_simple_group_count();
    let sg: i32 = 0;
    while (sg < gcount) {
      let rel: *u8 = labi_od_simple_group_rel(sg);
      if (rel != 0 as *u8) {
        if (rel[0] != 0) {
          if (labi_od_user_needs_simple_group(user_o, sg) != 0) {
            // Formal ensure for core/* groups by fixed group ids (≡ mega strstr).
            // g1 types, g6 option, g7 result, g8 debug, g9 slice/mod.
            if (sg == 1) {
              let rt: *u8 = 0 as *u8;
              unsafe {
                rt = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt != 0 as *u8) {
                if (rt[0] != 0) {
                  unsafe {
                    let _fe: i32 = xlang_ensure_formal_std_make_o(rt, "core/types/types.o", "../core/types/types.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            if (sg == 6) {
              let rt6: *u8 = 0 as *u8;
              unsafe {
                rt6 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt6 != 0 as *u8) {
                if (rt6[0] != 0) {
                  unsafe {
                    let _fe6: i32 = xlang_ensure_formal_std_make_o(rt6, "core/option/option.o", "../core/option/option.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            if (sg == 7) {
              let rt7: *u8 = 0 as *u8;
              unsafe {
                rt7 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt7 != 0 as *u8) {
                if (rt7[0] != 0) {
                  unsafe {
                    let _fe7: i32 = xlang_ensure_formal_std_make_o(rt7, "core/result/result.o", "../core/result/result.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            if (sg == 8) {
              let rt8: *u8 = 0 as *u8;
              unsafe {
                rt8 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt8 != 0 as *u8) {
                if (rt8[0] != 0) {
                  unsafe {
                    let _fe8: i32 = xlang_ensure_formal_std_make_o(rt8, "core/debug/debug.o", "../core/debug/debug.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            if (sg == 9) {
              let rt9: *u8 = 0 as *u8;
              unsafe {
                rt9 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt9 != 0 as *u8) {
                if (rt9[0] != 0) {
                  unsafe {
                    let _fe9: i32 = xlang_ensure_formal_std_make_o(rt9, "core/slice/mod.o", "../core/slice/mod.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            // PLATFORM: SHARED — g10 core.builtin formal (pure-asm run-builtin residual).
            // L4 wipe drops gitignored core/builtin/builtin.o; ensure via formal_mod catalog.
            if (sg == 10) {
              let rt10: *u8 = 0 as *u8;
              unsafe {
                rt10 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt10 != 0 as *u8) {
                if (rt10[0] != 0) {
                  unsafe {
                    let _fe10: i32 = xlang_ensure_formal_std_make_o(rt10, "core/builtin/builtin.o", "../core/builtin/builtin.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            // PLATFORM: SHARED — g11 std.ffi formal (pure-asm run-ffi residual).
            // L4 wipe drops gitignored std/ffi/ffi.o; ensure via formal_mod catalog.
            if (sg == 11) {
              let rt11: *u8 = 0 as *u8;
              unsafe {
                rt11 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt11 != 0 as *u8) {
                if (rt11[0] != 0) {
                  unsafe {
                    let _fe11: i32 = xlang_ensure_formal_std_make_o(rt11, "std/ffi/ffi.o", "../std/ffi/ffi.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g12 std.test formal (pure-asm run-stdtest residual).
            // Formal ensure here; companions after the shared push_obj below (≡ g2).
            if (sg == 12) {
              let rt12: *u8 = 0 as *u8;
              unsafe {
                rt12 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt12 != 0 as *u8) {
                if (rt12[0] != 0) {
                  unsafe {
                    let _fe12: i32 = xlang_ensure_formal_std_make_o(rt12, "std/test/test.o", "../std/test/test.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g13 core.assert formal (run-debug core-assert residual).
            if (sg == 13) {
              let rt13: *u8 = 0 as *u8;
              unsafe {
                rt13 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt13 != 0 as *u8) {
                if (rt13[0] != 0) {
                  unsafe {
                    let _fe13: i32 = xlang_ensure_formal_std_make_o(rt13, "core/assert/assert.o", "../core/assert/assert.o");
                  }
                  pushed_core_formal = 1;
                }
              }
            }
            // PLATFORM: SHARED — g14 std.fmt formal (run-fmt residual).
            if (sg == 14) {
              let rt14: *u8 = 0 as *u8;
              unsafe {
                rt14 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt14 != 0 as *u8) {
                if (rt14[0] != 0) {
                  unsafe {
                    let _fe14: i32 = xlang_ensure_formal_std_make_o(rt14, "std/fmt/fmt.o", "../std/fmt/fmt.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g15 std.compress formal (run-compress residual).
            // 9.2.2: facade compress.o is c_face stub; real zlib/gzip are submodule
            // formal .o (mod+libz) plus runtime_compress_zlib_glue (Init2 macros).
            if (sg == 15) {
              let rt15: *u8 = 0 as *u8;
              unsafe {
                rt15 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt15 != 0 as *u8) {
                if (rt15[0] != 0) {
                  unsafe {
                    let _fe15: i32 = xlang_ensure_formal_std_make_o(rt15, "std/compress/compress.o", "../std/compress/compress.o");
                    let _fez: i32 = xlang_ensure_formal_std_make_o(rt15, "std/compress/zlib/zlib.o", "../std/compress/zlib/zlib.o");
                    let _feg: i32 = xlang_ensure_formal_std_make_o(rt15, "std/compress/gzip/gzip.o", "../std/compress/gzip/gzip.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g16 std.io.driver formal (run-io-driver residual).
            if (sg == 16) {
              let rt16: *u8 = 0 as *u8;
              unsafe {
                rt16 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt16 != 0 as *u8) {
                if (rt16[0] != 0) {
                  unsafe {
                    let _fe16: i32 = xlang_ensure_formal_std_make_o(rt16, "std/io/driver.o", "../std/io/driver.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g17 std.debug formal (run-debug residual).
            if (sg == 17) {
              let rt17: *u8 = 0 as *u8;
              unsafe {
                rt17 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt17 != 0 as *u8) {
                if (rt17[0] != 0) {
                  unsafe {
                    let _fe17: i32 = xlang_ensure_formal_std_make_o(rt17, "std/debug/debug.o", "../std/debug/debug.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g18 std.simd formal (run-perf-simd residual).
            // VECTOR mid faces from formal_surface; L4 wipe drops gitignored simd.o.
            if (sg == 18) {
              let rt18: *u8 = 0 as *u8;
              unsafe {
                rt18 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt18 != 0 as *u8) {
                if (rt18[0] != 0) {
                  unsafe {
                    let _fe18: i32 = xlang_ensure_formal_std_make_o(rt18, "std/simd/simd.o", "../std/simd/simd.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g19 std.io context-timeout formal (STD-091 residual).
            // L4 wipe drops gitignored io.o; ensure via formal_mod catalog.
            if (sg == 19) {
              let rt19: *u8 = 0 as *u8;
              unsafe {
                rt19 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt19 != 0 as *u8) {
                if (rt19[0] != 0) {
                  unsafe {
                    let _fe19: i32 = xlang_ensure_formal_std_make_o(rt19, "std/io/io.o", "../std/io/io.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — g2 encoding formal may be gitignored after L4 wipe.
            // encode_hex/base64 wrappers U string + base64; ensure primary before push.
            if (sg == 2) {
              let rt2: *u8 = 0 as *u8;
              unsafe {
                rt2 = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt2 != 0 as *u8) {
                if (rt2[0] != 0) {
                  unsafe {
                    let _fe2: i32 = xlang_ensure_formal_std_make_o(rt2, "std/encoding/encoding.o", "../std/encoding/encoding.o");
                  }
                }
              }
            }
            // PLATFORM: SHARED — ensure formal by rel for every simple group (seed/pure
            // index skew: seed g12=simd while pure g12=test / g18=simd). G.7: one
            // ensure authority = formal_mod catalog key = rel path.
            {
              let rta: *u8 = 0 as *u8;
              unsafe {
                rta = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rta != 0 as *u8) {
                if (rta[0] != 0) {
                  // make_target = "../" + rel (compiler/ cwd convention).
                  let mt: u8[160] = [];
                  let mi: i32 = 0;
                  mt[0] = 46; mt[1] = 46; mt[2] = 47; // ../
                  mi = 3;
                  let ri: i32 = 0;
                  while (ri < 140) {
                    let c: u8 = rel[ri];
                    if (c == 0) { break; }
                    mt[mi] = c;
                    mi = mi + 1;
                    ri = ri + 1;
                  }
                  mt[mi] = 0;
                  unsafe {
                    let _fea: i32 = xlang_ensure_formal_std_make_o(rta, rel, &mt[0]);
                  }
                }
              }
            }
            unsafe {
              let _sg: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
            }
            // PLATFORM: SHARED — g12 std.test monofile C dual companions
            // (fn_invoke / env_os / time_os). ≡ need_test path; dedup-safe.
            if (sg == 12) {
              unsafe {
                labi_od_push_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
              }
            }
            // PLATFORM: SHARED — g2 encoding.o carries U std_base64_* + std_string_string_*
            // (encode_hex/base64/base32 helpers). User.o only U encoding_* so g0/g3 alone miss.
            // Companion co-push ≡ g9 slice glue pattern (transitive formal deps).
            if (sg == 2) {
              let rt2c: *u8 = 0 as *u8;
              unsafe {
                rt2c = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rt2c != 0 as *u8) {
                if (rt2c[0] != 0) {
                  unsafe {
                    let _fes: i32 = xlang_ensure_formal_std_make_o(rt2c, "std/string/string.o", "../std/string/string.o");
                    let _feb: i32 = xlang_ensure_formal_std_make_o(rt2c, "std/base64/base64.o", "../std/base64/base64.o");
                  }
                }
              }
              let srel: *u8 = labi_od_simple_group_rel(0);
              let brel: *u8 = labi_od_simple_group_rel(3);
              if (srel != 0 as *u8) {
                if (srel[0] != 0) {
                  unsafe {
                    let _ps: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, srel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
                  }
                }
              }
              if (brel != 0 as *u8) {
                if (brel[0] != 0) {
                  unsafe {
                    let _pb: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, brel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
                  }
                }
              }
            }
            /*
             * PLATFORM: SHARED — g23 std/bytes/bytes.o U heap.alloc/realloc/copy/free
             * (mod.x grow/extend). User.o for roundtrip only U std_bytes_* so heap_api
             * needles miss. Companion ≡ g2 encoding → string/base64. Also co-push
             * string.o for as_view. G.7: complete g23 ensure; no second group.
             */
            if (sg == 23) {
              let rtb: *u8 = 0 as *u8;
              unsafe {
                rtb = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rtb != 0 as *u8) {
                if (rtb[0] != 0) {
                  unsafe {
                    let _feh: i32 = xlang_ensure_formal_std_make_o(rtb, "std/heap/heap.o", "../std/heap/heap.o");
                    let _fes: i32 = xlang_ensure_formal_std_make_o(rtb, "std/string/string.o", "../std/string/string.o");
                  }
                }
              }
              let hrel: *u8 = labi_od_rel_heap();
              let srelb: *u8 = labi_od_simple_group_rel(0);
              if (hrel != 0 as *u8) {
                if (hrel[0] != 0) {
                  unsafe {
                    let _ph: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, hrel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
                  }
                }
              }
              if (srelb != 0 as *u8) {
                if (srelb[0] != 0) {
                  unsafe {
                    let _psb: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, srelb, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
                  }
                }
              }
            }
            // g9: co-push glue slice.o after formal mod.o
            if (sg == 9) {
              let rtg: *u8 = 0 as *u8;
              unsafe {
                rtg = xlang_repo_root_from_argv0(link_argv0);
              }
              if (rtg != 0 as *u8) {
                if (rtg[0] != 0) {
                  unsafe {
                    let _feg: i32 = xlang_ensure_formal_std_make_o(rtg, "core/slice/slice.o", "../core/slice/slice.o");
                  }
                }
              }
              let csgl: *u8 = labi_od_rel_core_slice();
              unsafe {
                let _csg: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, csgl, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
              }
            }
          }
        }
      }
      sg = sg + 1;
    }
    if (pushed_core_formal != 0) {
      let pav: *u8 = 0 as *u8;
      unsafe {
        let _ep: i32 = xlang_ensure_runtime_process_argv_o(link_argv0);
        pav = xlang_runtime_process_argv_o_path(link_argv0);
        let _pp: i32 = link_abi_asm_ld_push_obj(pav, link_argv0, "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      }
    }

    // --- process_argv complement scan after on_demand pushes ---
    let need_pav: i32 = 0;
    let have_process_o: i32 = 0;
    let bi: i32 = 0;
    let la_b: i32 = la[0];
    while (bi < la_b) {
      let e2: *u8 = argv[bi];
      if (e2 == 0 as *u8) {
        bi = la_b;
      }
      if (e2 != 0 as *u8) {
        let is_o: i32 = 0;
        unsafe {
          is_o = link_abi_ld_argv_entry_is_obj(e2);
        }
        if (is_o != 0) {
          let has_po: i32 = labi_od_cstr_contains(e2, "process.o");
          let has_pa: i32 = labi_od_cstr_contains(e2, "process_argv");
          if (has_po != 0) {
            if (has_pa == 0) {
              have_process_o = 1;
            }
          }
          let u1: i32 = 0;
          let u2: i32 = 0;
          unsafe {
            u1 = xlang_link_obj_needs_undef_sym(e2, "process_xlang_argc_get");
            u2 = xlang_link_obj_needs_undef_sym(e2, "process_xlang_argv_get");
          }
          if (u1 != 0) {
            need_pav = 1;
          }
          if (u2 != 0) {
            need_pav = 1;
          }
        }
      }
      bi = bi + 1;
    }
    if (need_pav != 0) {
      if (have_process_o == 0) {
        let pav2: *u8 = 0 as *u8;
        unsafe {
          let _ep2: i32 = xlang_ensure_runtime_process_argv_o(link_argv0);
          pav2 = xlang_runtime_process_argv_o_path(link_argv0);
          let _pp2: i32 = link_abi_asm_ld_push_obj(pav2, link_argv0, "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }

    // --- time_os complement scan after on_demand pushes ---
    // PLATFORM: SHARED — std/cache/cache.o (and similar formal monofiles) U
    // time_now_monotonic_ns_c after fk0 push; user.o only has std_cache_* so
    // labi_user_needs_runtime_time_os / time-table gate never fire. Mirror the
    // process_argv complement: scan argv objs for the C face UNDEF, then ensure
    // + push runtime_time_os.o. G.7 complete existing companion pattern (STD-087).
    let need_tos: i32 = 0;
    let have_tos: i32 = 0;
    let ti: i32 = 0;
    let la_t: i32 = la[0];
    while (ti < la_t) {
      let et: *u8 = argv[ti];
      if (et == 0 as *u8) {
        ti = la_t;
      }
      if (et != 0 as *u8) {
        let is_ot: i32 = 0;
        unsafe {
          is_ot = link_abi_ld_argv_entry_is_obj(et);
        }
        if (is_ot != 0) {
          let has_tos: i32 = labi_od_cstr_contains(et, "runtime_time_os.o");
          if (has_tos != 0) {
            have_tos = 1;
          }
          let ut: i32 = 0;
          unsafe {
            ut = xlang_link_obj_needs_undef_sym(et, "time_now_monotonic_ns_c");
          }
          if (ut != 0) {
            need_tos = 1;
          }
        }
      }
      ti = ti + 1;
    }
    if (need_tos != 0) {
      if (have_tos == 0) {
        let torel2: *u8 = labi_od_time_os_rel();
        let top2: *u8 = 0 as *u8;
        unsafe {
          let _et2: i32 = xlang_ensure_runtime_time_os_o(link_argv0);
          top2 = xlang_runtime_time_os_o_path(link_argv0);
          let _pt2: i32 = link_abi_asm_ld_push_obj(top2, link_argv0, torel2, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }

    // --- crypto/random complement scan after on_demand pushes ---
    // PLATFORM: SHARED — std/security/security.o (fk0) U std_crypto_mem_eq /
    // crypto_hmac_sha256_c / std_random_fill_bytes after push; user.o only has
    // std_security_* so fk4 crypto / random gates never fire. G.7: mirror
    // process_argv / time_os complement (STD-079 roundtrip).
    let need_crypto: i32 = 0;
    let need_hmac: i32 = 0;
    let need_rand: i32 = 0;
    let have_crypto: i32 = 0;
    let have_hmac: i32 = 0;
    let have_rand: i32 = 0;
    let ci: i32 = 0;
    let la_c: i32 = la[0];
    while (ci < la_c) {
      let ec: *u8 = argv[ci];
      if (ec == 0 as *u8) {
        ci = la_c;
      }
      if (ec != 0 as *u8) {
        let is_oc: i32 = 0;
        unsafe {
          is_oc = link_abi_ld_argv_entry_is_obj(ec);
        }
        if (is_oc != 0) {
          let has_c: i32 = labi_od_cstr_contains(ec, "std/crypto/crypto.o");
          let has_cg: i32 = labi_od_cstr_contains(ec, "runtime_crypto_inc_glue.o");
          let has_r: i32 = labi_od_cstr_contains(ec, "std/random/random.o");
          if (has_c != 0) {
            have_crypto = 1;
          }
          if (has_cg != 0) {
            have_hmac = 1;
          }
          if (has_r != 0) {
            have_rand = 1;
          }
          let u_c1: i32 = 0;
          let u_c2: i32 = 0;
          let u_h: i32 = 0;
          let u_r: i32 = 0;
          unsafe {
            u_c1 = xlang_link_obj_needs_undef_sym(ec, "std_crypto_mem_eq");
            u_c2 = xlang_link_obj_needs_undef_sym(ec, "crypto_mem_eq_c");
            u_h = xlang_link_obj_needs_undef_sym(ec, "crypto_hmac_sha256_c");
            u_r = xlang_link_obj_needs_undef_sym(ec, "std_random_fill_bytes");
          }
          if (u_c1 != 0) {
            need_crypto = 1;
          }
          if (u_c2 != 0) {
            need_crypto = 1;
          }
          if (u_h != 0) {
            need_hmac = 1;
          }
          if (u_r != 0) {
            need_rand = 1;
          }
        }
      }
      ci = ci + 1;
    }
    if (need_crypto != 0) {
      if (have_crypto == 0) {
        let root_c: *u8 = 0 as *u8;
        unsafe {
          root_c = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_c != 0 as *u8) {
          if (root_c[0] != 0) {
            unsafe {
              let _ecr: i32 = xlang_ensure_formal_std_make_o(root_c, "std/crypto/crypto.o", "../std/crypto/crypto.o");
            }
          }
        }
        unsafe {
          let _pcr: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/crypto/crypto.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    if (need_hmac != 0) {
      if (have_hmac == 0) {
        // CRYPTO_PAIR: ed25519_ref10 (sha512) + crypto_inc (hmac_sha256_c).
        let p_ed: *u8 = 0 as *u8;
        let p_ci: *u8 = 0 as *u8;
        unsafe {
          let _eed: i32 = xlang_ensure_runtime_ed25519_ref10_glue_o(link_argv0);
          p_ed = xlang_runtime_ed25519_ref10_glue_o_path(link_argv0);
          let _ped: i32 = link_abi_asm_ld_push_obj(p_ed, link_argv0, "compiler/runtime_ed25519_ref10_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          let _eci: i32 = xlang_ensure_runtime_crypto_inc_glue_o(link_argv0);
          p_ci = xlang_runtime_crypto_inc_glue_o_path(link_argv0);
          let _pci: i32 = link_abi_asm_ld_push_obj(p_ci, link_argv0, "compiler/runtime_crypto_inc_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    if (need_rand != 0) {
      if (have_rand == 0) {
        let root_r: *u8 = 0 as *u8;
        unsafe {
          root_r = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_r != 0 as *u8) {
          if (root_r[0] != 0) {
            unsafe {
              let _ernd: i32 = xlang_ensure_formal_std_make_o(root_r, "std/random/random.o", "../std/random/random.o");
            }
          }
        }
        unsafe {
          let _prnd: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/random/random.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }

    // --- error companion after result.o push ---
    // PLATFORM: SHARED — std/result/result.o (fk0) U std_error_ok after push;
    // user.o may only have std_result_* so fk0 k8 error gate never fires.
    // G.7: mirror security→crypto / cache→time_os (STD-080/081 roundtrip).
    let need_err: i32 = 0;
    let have_err: i32 = 0;
    let ei: i32 = 0;
    let la_e: i32 = la[0];
    while (ei < la_e) {
      let ee: *u8 = argv[ei];
      if (ee == 0 as *u8) {
        ei = la_e;
      }
      if (ee != 0 as *u8) {
        let is_oe: i32 = 0;
        unsafe {
          is_oe = link_abi_ld_argv_entry_is_obj(ee);
        }
        if (is_oe != 0) {
          let has_e: i32 = labi_od_cstr_contains(ee, "std/error/error.o");
          if (has_e != 0) {
            have_err = 1;
          }
          let u_e: i32 = 0;
          unsafe {
            u_e = xlang_link_obj_needs_undef_sym(ee, "std_error_ok");
          }
          if (u_e != 0) {
            need_err = 1;
          }
        }
      }
      ei = ei + 1;
    }
    if (need_err != 0) {
      if (have_err == 0) {
        let root_e: *u8 = 0 as *u8;
        unsafe {
          root_e = xlang_repo_root_from_argv0(link_argv0);
        }
        if (root_e != 0 as *u8) {
          if (root_e[0] != 0) {
            unsafe {
              let _eerr: i32 = xlang_ensure_formal_std_make_o(root_e, "std/error/error.o", "../std/error/error.o");
            }
          }
        }
        unsafe {
          let _perr: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/error/error.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }

    // --- time formal + time_os (thin helper: mega-frame spill SEGV residual) ---
    // PLATFORM: SHARED — pure-asm run-time: large-frame push_obj rel arg mis-load
    // → SEGV under ASLR. Gate stays here; body in labi_od_push_time_formal_and_os.
    let n_tm: i32 = labi_od_time_sym_count();
    if (labi_od_user_needs_table_which(user_o, n_tm, 2) != 0) {
      unsafe {
        labi_od_push_time_formal_and_os(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
    }

    // --- queue product + monofile companions (sync/atomic/contention) ---
    // G.7 root (pure-asm run-queue): formal queue.o monofile co-defines SyncQueue
    // locals (sync_new/push/try_pop/smoke) that U std_sync_* / std_atomic_* /
    // sync_queue_contention_smoke_c. User.o only has std_queue_* needles → fk3
    // sync / fk6 atomic never fire; need_qc only covers contention smoke symbols
    // on user.o (tests/queue/main.x never names them). Whole .o link (not archive)
    // pulls monofile U even for plain Queue_i32 API. Companions ≡ net→error/context
    // pattern + C-path SYNC_PAIR / ATOMIC glue when have_sync.
    let need_qp: i32 = link_abi_user_o_needs_std_queue(user_o);
    let n_qc: i32 = labi_od_queue_sym_count();
    let need_qc: i32 = labi_od_user_needs_table_which(user_o, n_qc, 3);
    if (need_qp != 0 || need_qc != 0) {
      let rq: *u8 = 0 as *u8;
      unsafe {
        rq = xlang_repo_root_from_argv0(link_argv0);
      }
      if (rq != 0 as *u8) {
        if (rq[0] != 0) {
          unsafe {
            let _q1: i32 = xlang_ensure_formal_std_make_o(rq, "std/queue/queue.o", "../std/queue/queue.o");
            let _q2: i32 = xlang_ensure_formal_std_make_o(rq, "std/heap/heap.o", "../std/heap/heap.o");
            let _q3: i32 = xlang_ensure_formal_std_make_o(rq, "core/mem/mem.o", "../core/mem/mem.o");
          }
        }
      }
      let qrel: *u8 = labi_od_queue_rel();
      let qh: *u8 = labi_od_rel_heap();
      let qm: *u8 = labi_od_rel_core_mem();
      unsafe {
        let _qq: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, qrel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _qh: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, qh, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        let _qm: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, qm, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        labi_std_append_queue_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la, flags);
      }
    }
  }
}
