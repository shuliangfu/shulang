// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// link_abi L6 invoke_ld pure tables + orch (G.9 English; body is authoritative).
// Product: PREFER_X_O → g05_try_x_to_o; cold-start seeds/labi_invoke_ld_list.from_x.c.
// Hybrid macro XLANG_LABI_INVOKE_LD_LIST_FROM_X (FROM_X rest business H=0, marker only).
//
// R2 full: .x owns brew/compress/tail/driver/entry pure tables + wave152 brew orch
// + wave153 asm compress-libs orch + wave154 invoke_cc compress-ld orch
// + wave156 mach tail_libs_impl pure orch + wave157 unix gcc tail + wave158 net_tls
// + wave179 invoke_cc_argv_push_existing pure orch
// + wave187 ensure_std_net_o_auto_tls pure orch
// + wave188 xlang_ensure_formal_std_make_o pure orch
// + wave191 labi_std_append_formal_ensure_for_rel pure orch
// + wave192 labi_std_append_glue_for_op pure orch
// + wave193 labi_std_append_primary_for_op + process_argv_if pure orch
// + wave194 labi_std_append_task_special pure orch
// + wave195 labi_std_append_op_std pure orch
// + wave196 xlang_asm_ld_append_std_objs_for_user plan loop shell pure orch:
//   - labi_ld_brew_lib_path_{count,at} + labi_ld_flag_* / drivers / common_tail
//   - ld_append_brew_lib_paths (wave152; pure table scan; Cap residual host_is_apple)
//   - asm_ld_append_compress_libs (wave153; pure orch; Cap residual needs+ensure+path)
//   - invoke_cc_append_compress_ld (wave154; pure orch; Cap residual needs+ensure+path
//     + pure push_existing for glue realpath/skip/dedup)
//   - xlang_asm_ld_append_mach_tail_libs_impl (wave156; pure orch over flags i32 layout
//     + pure flag_* + peer compress orch + peer needs_compress)
//   - xlang_asm_ld_append_unix_gcc_tail_libs_impl (wave157; pure orch; peer host_is_linux
//     + host_is_apple for -ldl / else -lc gates)
//   - invoke_cc_append_net_tls_ld (wave158; pure orch; Cap residual exports_marker +
//     realpath_cap + rel_o_path + pure push_existing + host_is_apple for brew -L)
//   - invoke_cc_argv_push_existing (wave179; pure gates/dedup/append; Cap residual resolve pool)
//   - invoke_cc_argv_resolve_existing_path (wave215/255; pure null/empty + skip_missing;
//     Cap residual resolve_existing_path_impl = multi-slot realpath pool only)
//   - ensure_std_net_o_auto_tls (wave187; pure mode/path orch; Cap residual
//     link_abi_getenv+link_abi_system+realpath_cap+exports_marker; wave222/224 pure faces)
//   - xlang_ensure_formal_std_make_o (wave188; pure path/XLANG/make-cmd orch; Cap residual
//     link_abi_getenv+path_executable+realpath_cap+link_abi_system+skip_missing;
//     wave221 X_OK / wave222 getenv / wave224 system pure faces)
//   - labi_std_append_formal_ensure_for_rel (wave191; pure formal ensure+companions orch for
//     append_std OP_STD; Cap residual repo_root + ensure_runtime_* + peer push_obj)
//   - labi_std_append_glue_for_op (wave192; pure OP_GLUE_* ensure+path+push orch for
//     append_std plan glue leaves; Cap residual ensure_runtime_*_glue + peer path + push_obj)
//   - labi_std_append_primary_for_op (wave193; pure IO_STUBS/PRIMARY_* path+gate+ensure+push
//     for append_std plan primary leaves; Cap residual needs_* + ensure/path + push_obj)
//   - labi_std_append_process_argv_if (wave193; pure process_argv complement when
//     heavy std on argv without process.o; Cap residual ensure+path + push_obj)
//   - labi_std_append_task_special (wave194; pure TASK_SPECIAL orch: needs_std_task gate +
//     formal ensure task.o + push task/scheduler/scheduler_glue; Cap residual skip/path/bank)
//   - labi_std_append_op_std (wave195; pure OP_STD orch: fk→flag_out map + fk0/fk1–13 gate +
//     formal ensure + push_obj; Cap residual undef_sym inside fk gate peers)
//   - xlang_asm_ld_append_std_objs_for_user (wave196; pure plan shell: flags/local_have init +
//     plan_count/step_at loop + dispatch to wave190–195 leaf pure + process_argv complement;
//     Cap residual stays inside leaf peers / plan table L8)
// Cap residual (mega): link_abi_host_is_apple; obj_needs_* Cap (marker/has_undef);
//   ensure/path for zlib glue; invoke_cc_argv_resolve_existing_path_impl (realpath pool only;
//   wave215/255 pure owns null/empty + skip_missing);
//   exports_marker / realpath_cap / xlang_rel_o_path_from_argv0;
//   spawn/ld/cc IO; contains_substr / undef_sym / path_io / wait / strerror / ld_debug_argv;
//   link_abi_getenv / link_abi_system / path_executable for ensure_std_net + formal_std_make
//     (wave187/188 Cap; wave221 X_OK pure; wave222 getenv pure; wave224 system pure);
//   runtime ensure/path peers for wave191 formal companions + wave192 glue leaves;
//   needs + primary ensure/path + process_argv for wave193 primary/complement;
//   task/scheduler path peers + bank_push for wave194 TASK_SPECIAL;
//   fk gate peers (wave135/190) for wave195 OP_STD;
//   plan table accessors (labi_std_list L8) for wave196 plan shell.
// PLATFORM: SHARED orch / MACOS brew+mach / LINUX unix gcc tail -l*.

// Cap residual: compile-time #if __APPLE__ (all arch: aarch64 + x86_64).
// Not the same as xlang_host_is_apple_aarch64 (host_lit L2; arm64 only).
export extern "C" function link_abi_host_is_apple(): i32;

// Peer pure (host_lit L2 thin → Cap residual _impl #if __linux__).
// Used by wave157 unix gcc tail for -ldl and (with host_is_apple) else-branch -lc.
export extern "C" function xlang_host_is_linux(): i32;

// Cap residual / peer pure (ondemand L8b): .o depends on zlib/zstd/brotli.
export extern "C" function link_abi_obj_needs_zlib(obj_o: *u8): i32;
export extern "C" function link_abi_obj_needs_zstd(obj_o: *u8): i32;
export extern "C" function link_abi_obj_needs_brotli(obj_o: *u8): i32;

// Peer pure (ondemand L8b): user.o needs any compress lib (zlib|zstd|brotli aggregate).
export extern "C" function link_abi_user_o_needs_compress_libs(user_o: *u8): i32;
// Peer pure (ondemand L8b): exact UNDEF probe (nm -u; strip optional U/_).
export extern "C" function xlang_link_obj_needs_undef_sym(user_o: *u8, sym: *u8): i32;

// Cap residual: ensure zlib macro-wrapper glue .o + resolve its path for ld argv.
export extern "C" function xlang_ensure_runtime_compress_zlib_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_compress_zlib_glue_o_path(argv0: *u8): *u8;

// Peer pure (labi_path_io L3): regular-file existence gate before resolve pool residual.
// Declared early so wave255 resolve pure orch can call it above other ensure peers.
export extern "C" function asm_link_obj_skip_missing(path: *u8): *u8;

// Cap residual (wave179 / wave215 / wave255): multi-slot POSIX realpath pool body only.
// Pure orch owns null/empty + skip_missing; _impl is always mega (static pool + host realpath).
// PLATFORM: SHARED residual; Windows skips realpath (returns validated path as-is).
export extern "C" function invoke_cc_argv_resolve_existing_path_impl(path: *u8): *u8;

// Peer pure (labi_path_pure L0): realpath-equal argv scan. G.7 single dedup authority
// for CLI extra .o vs auto-pushed companions (relative vs compiler-dir absolute).
export extern "C" function link_abi_asm_ld_argv_has_obj(argv: **u8, la: i32, path: *u8): i32;

/**
 * Resolve an existing .o path for invoke_cc argv: skip missing + durable realpath pool.
 * null/empty → null without residual. Product push_existing and compress/net_tls pure
 * call this public face (G.7 single authority).
 * @param path *u8 — candidate path; null/empty rejected at pure gate
 * @return *u8 — durable path pointer (pool slot or skip_missing path), or null if missing
 * Pure orch (wave215/255): null/empty gates + peer pure asm_link_obj_skip_missing
 *   before Cap residual multi-slot realpath pool.
 * Cap residual: invoke_cc_argv_resolve_existing_path_impl (pool + host realpath only;
 *   wave255 moved skip_missing out of _impl into pure).
 * Why (wave215): hybrid still had resolve_existing body always mega C (gates+skip+pool).
 * Why (wave255): soft residual skip_missing still lived inside always-mega _impl.
 * PLATFORM: SHARED orch; residual realpath pool is host (POSIX; Windows no realpath).
 * Track-L: #[no_mangle] keeps surface short name matching Cap residual callers.
 */
#[no_mangle]
export function invoke_cc_argv_resolve_existing_path(path: *u8): *u8 {
  let use: *u8 = 0 as *u8;
  if (path == 0 as *u8) {
    return 0 as *u8;
  }
  if (path[0] == 0) {
    return 0 as *u8;
  }
  // Peer pure (labi_path_io L3): skip missing / non-regular before pool residual.
  // export extern "C" peer requires unsafe (same as ensure formal short-circuit).
  unsafe {
    use = asm_link_obj_skip_missing(path);
  }
  if (use == 0 as *u8) {
    return 0 as *u8;
  }
  unsafe {
    return invoke_cc_argv_resolve_existing_path_impl(use);
  }
  return 0 as *u8;
}

// Cap residual (wave158): nm/marker probe for TLS backend objects (openssl/mbedtls).
export extern "C" function link_abi_obj_exports_marker(obj_o: *u8, marker: *u8): i32;

// Cap residual (wave146/158): POSIX realpath into caller buffer; Windows/fail → null.
export extern "C" function link_abi_realpath_cap(path: *u8, out: *u8): *u8;

// Cap residual (wave158): resolve rel path under argv0/repo_root (tls_openssl.o etc.).
export extern "C" function xlang_rel_o_path_from_argv0(argv0: *u8, rel: *u8): *u8;

// Cap residual (wave187/188 ensure shell make): host shell make / skip_missing.
// PLATFORM: SHARED — XLANG_NET_TLS net-o-* + formal std make (XLANG_FORMAL_STD_ENSURE reentrancy).
// wave222: env lookup is public pure thin link_abi_getenv (labi_diag_pure L1 hybrid);
// Cap residual host getenv stays mega as link_abi_getenv_impl.
// wave224: shell make is public pure thin link_abi_system (labi_diag_pure L1 hybrid);
// Cap residual host system stays mega as link_abi_system_impl.
export extern "C" function link_abi_getenv(name: *u8): *u8;
export extern "C" function link_abi_system(cmd: *u8): i32;
export extern "C" function strcmp(a: *u8, b: *u8): i32;
// wave221: product host binary X_OK probe is public pure thin link_abi_path_executable
// (labi_path_io L3 hybrid); Cap residual access X_OK stays mega as _impl.
export extern "C" function link_abi_path_executable(path: *u8): i32;
// asm_link_obj_skip_missing declared above resolve pure (wave255); ensure leaves reuse it.

// Peer pure (path_pure L0 wave162): repo root from argv0 (strip compiler-dir / process.o walk).
// wave191 formal ensure orch uses this to pass repo_root into xlang_ensure_formal_std_make_o.
export extern "C" function xlang_repo_root_from_argv0(argv0: *u8): *u8;

// Cap residual / peer pure (ensure_list L4): runtime companion ensure + path for formal
// env.o / random.o / time.o (mirrors mega append_std OP_STD companions).
// PLATFORM: SHARED — product path symbols; hybrid may be pure L0/L4 path ladders.
export extern "C" function xlang_ensure_runtime_env_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_env_os_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_random_fill_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_random_fill_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_time_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_time_os_o_path(argv0: *u8): *u8;

// Peer pure (path_pure L0 wave148): push one .o onto asm ld argv (resolve+bank+dedup).
// wave191 companions + wave192 glue leaves call this after ensure.
// Note: single-line signature (multi-line export decls can drop the symbol).
export extern "C" function link_abi_asm_ld_push_obj(primary: *u8, link_argv0: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flag_out: *i32): i32;
// Peer pure (ondemand L8b): formal .o UNDEF table for std.heap API (heap.o gate).
// wave191 companions probe the just-ensured rel, not only user.o / vec-set-map whitelist.
export extern "C" function link_abi_user_o_needs_std_heap_api(user_o: *u8): i32;

// Cap residual / peer pure (ensure_list L4 + path_pure L0): OP_GLUE_* runtime glue
// ensure + path for append_std plan leaves (wave192).
// PLATFORM: SHARED — product symbols; hybrid may resolve via pure L0/L4 path ladders.
// G.7: compose ensure+path+push_obj (≡ push_glue_after_std without C fnptr); no second gate.
export extern "C" function xlang_ensure_runtime_thread_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_thread_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_sync_lock_diag_tls_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_sync_lock_diag_tls_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_sync_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_sync_os_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_ed25519_ref10_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_ed25519_ref10_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_crypto_inc_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_crypto_inc_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_log_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_log_os_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_atomic_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_atomic_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_channel_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_channel_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_backtrace_platform_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_backtrace_platform_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_math_libm_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_math_libm_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_sqlite_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_sqlite_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_dynlib_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_dynlib_os_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_http_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_http_glue_o_path(argv0: *u8): *u8;

// Peer pure (ondemand L8b wave132–133): bulk PRIMARY OS gates for append_std plan.
// null/empty user_o → 1 (always need; matches mega hard-link when no user filter).
// PLATFORM: SHARED — product UNDEF probe tables; Cap residual undef_sym inside orch.
export extern "C" function labi_user_needs_runtime_time_os(user_o: *u8): i32;
export extern "C" function labi_user_needs_runtime_random_fill(user_o: *u8): i32;
export extern "C" function labi_user_needs_runtime_env_os(user_o: *u8): i32;

// Peer pure (path_pure L0): primary runtime path ladders for IO_STUBS / PANIC leaves.
// PLATFORM: SHARED — product path symbols used by append_std PRIMARY plan steps.
export extern "C" function xlang_runtime_asm_io_stubs_o_path(argv0: *u8): *u8;
export extern "C" function xlang_runtime_panic_o_path(argv0: *u8): *u8;
export extern "C" function xlang_runtime_link_abi_user_env_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_link_abi_user_env_o(argv0: *u8): i32;

// Cap residual / peer pure: process_argv ensure+path for wave193 complement.
// PLATFORM: SHARED — constructor-bound argc/argv glue; never dual-link with process.o.
export extern "C" function xlang_ensure_runtime_process_argv_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_process_argv_o_path(argv0: *u8): *u8;
// Queue monofile U sync_queue_contention_smoke_c (formal_ensure + on_demand).
export extern "C" function xlang_ensure_runtime_queue_contention_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_queue_contention_o_path(argv0: *u8): *u8;
// Test monofile U test_call_i32_void_c / env_getenv_c / time_now_monotonic_ns_c.
// Body is labi_std_append_test_monofile_companions in this TU (≡ queue helper).
// Do not extern labi_od_push_test_monofile_companions (L8c): seed-phase1 links
// runtime_link_abi.o without L8c → UNDEF (c02468dbf Darwin bootstrap).
export extern "C" function xlang_ensure_runtime_test_fn_invoke_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_test_fn_invoke_o_path(argv0: *u8): *u8;

// Peer pure / Cap residual for wave194 TASK_SPECIAL (task.o + scheduler.o + scheduler_glue).
// PLATFORM: SHARED — append_std plan leaf 30; gate + formal ensure + path ladder + push.
// G.7: compose existing needs/path/ensure/push peers; no second task plan table.
export extern "C" function labi_user_needs_std_task(user_o: *u8): i32;
export extern "C" function scheduler_o_for_task_link(task_o: *u8, explicit_scheduler: *u8): *u8;
export extern "C" function xlang_std_async_scheduler_o_path(argv0: *u8): *u8;
export extern "C" function xlang_asm_ld_try_under_lib_roots(rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8): *u8;
export extern "C" function link_abi_asm_ld_argv_push_stable(bank: *u8, argv: **u8, la: *i32, max_la: i32, p: *u8): void;
export extern "C" function xlang_ensure_runtime_scheduler_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_scheduler_glue_o_path(argv0: *u8): *u8;

// Peer pure (ondemand L8b wave135/190): OP_STD plan gates for fk0 (rel×sym) and fk 1–13.
// Cap residual undef_sym / strstr stays inside those orchs; pure OP_STD only composes.
// PLATFORM: SHARED — product UNDEF gate tables; G.7 single gate authority.
export extern "C" function labi_std_fk0_user_needs_rel(user_o: *u8, rel: *u8): i32;
export extern "C" function labi_std_fk_user_needs(user_o: *u8, fk: i32): i32;

// Peer pure (labi_std_list L8): default std link plan table for wave196 plan shell.
// PLATFORM: SHARED — plan table authority; shell only iterates + dispatches leaves.
export extern "C" function labi_std_plan_count(): i32;
export extern "C" function labi_std_plan_step_at(i: i32, op_out: *i32, rel_out: *usize, flag_kind_out: *i32): i32;

/**
 * Push an existing .o path onto invoke_cc argv when the file is present.
 * Pure orch: null/capacity gates + Cap residual resolve (public pure skip + pool residual)
 * + pure cstr-eq dedup over argv[0..*ia) + pure append of the durable path pointer.
 * @param argv **u8 — cc linker argv table (char**); null → 0
 * @param ia *i32 — in/out argv length; null → 0
 * @param max_ia i32 — argv capacity; need *ia < max_ia - 1 (room for NUL terminator)
 * @param path *u8 — candidate .o path; null/empty → 0
 * @return i32 — 1 if appended, 0 if skipped (missing / capacity / duplicate)
 * Cap residual: invoke_cc_argv_resolve_existing_path public → _impl (wave215/255 pure
 *   null/empty + skip_missing; residual multi-slot realpath pool stays mega always).
 * Why (wave179): hybrid still had always-mega C body for push_existing (pool + dedup + append).
 * Dedup: link_abi_asm_ld_argv_has_obj (string + realpath-equal). strcmp-only on
 * `use` missed CLI extra `compiler/runtime_atomic_glue.o` vs auto-pushed
 * `{compiler_dir}/runtime_atomic_glue.o` — Darwin ld duplicate-symbol (Ubuntu
 * GNU ld hid the same .o twice). G.7 complete of the existing has_obj authority.
 * Note: null-check argv via cast to *u8 (do not write argv == 0 as **u8).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED — hybrid L6 pure; mega cold twin under #ifndef INVOKE_LD_LIST_FROM_X.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function invoke_cc_argv_push_existing(argv: **u8, ia: *i32, max_ia: i32, path: *u8): i32 {
  // Guard argv null via *u8 cast (wave147/151–158: avoid **u8 null compare codegen drop).
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return 0;
  }
  if (ia == 0 as *i32) {
    return 0;
  }
  if (path == 0 as *u8) {
    return 0;
  }
  if (path[0] == 0) {
    return 0;
  }
  // Capacity: leave one slot for argv NULL terminator (≡ mega *ia >= max_ia - 1).
  let cur: i32 = ia[0];
  if (cur >= max_ia - 1) {
    return 0;
  }
  // Public resolve: pure skip_missing + Cap residual multi-slot realpath pool (wave215/255).
  let use: *u8 = 0 as *u8;
  unsafe {
    use = invoke_cc_argv_resolve_existing_path(path);
  }
  if (use == 0 as *u8) {
    return 0;
  }
  // G.7: reuse L0 has_obj (string + realpath). Check resolved `use` and the
  // original `path` so CLI relative extra .o matches an already-absolute companion.
  let hit: i32 = 0;
  unsafe {
    hit = link_abi_asm_ld_argv_has_obj(argv, cur, use);
  }
  if (hit != 0) {
    return 0;
  }
  unsafe {
    hit = link_abi_asm_ld_argv_has_obj(argv, cur, path);
  }
  if (hit != 0) {
    return 0;
  }
  // Append durable path pointer (no copy; pool / skip path lifetime covers spawn).
  argv[cur] = use;
  ia[0] = cur + 1;
  return 1;
}

/**
 * Homebrew /usr/local -L path table size (fixed catalog).
 * @return i32 — always 2 (homebrew + /usr/local)
 * PLATFORM: SHARED table; consumers gate with host_is_apple.
 */
#[no_mangle]
export function labi_ld_brew_lib_path_count(): i32 {
  return 2;
}

/** Exported function `labi_ld_brew_lib_path_at`.
 * Implements `labi_ld_brew_lib_path_at`.
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_ld_brew_lib_path_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "-L/opt/homebrew/lib";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "-L/usr/local/lib";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_ld_flag_lz`.
 * Implements `labi_ld_flag_lz`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lz(): *u8 {
  let p: *u8 = "-lz";
  return p;
}

/** Exported function `labi_ld_flag_lzstd`.
 * Implements `labi_ld_flag_lzstd`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lzstd(): *u8 {
  let p: *u8 = "-lzstd";
  return p;
}

/** Exported function `labi_ld_flag_lbrotlienc`.
 * Implements `labi_ld_flag_lbrotlienc`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lbrotlienc(): *u8 {
  let p: *u8 = "-lbrotlienc";
  return p;
}

/** Exported function `labi_ld_flag_lbrotlidec`.
 * Implements `labi_ld_flag_lbrotlidec`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lbrotlidec(): *u8 {
  let p: *u8 = "-lbrotlidec";
  return p;
}

/** Exported function `labi_ld_compress_flag_count`.
 * Implements `labi_ld_compress_flag_count`.
 * @return i32
 */
#[no_mangle]
export function labi_ld_compress_flag_count(): i32 {
  return 4;
}

/** Exported function `labi_ld_compress_flag_at`.
 * Implements `labi_ld_compress_flag_at`.
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_ld_compress_flag_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "-lz";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "-lzstd";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "-lbrotlienc";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "-lbrotlidec";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_ld_flag_lm`.
 * Implements `labi_ld_flag_lm`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lm(): *u8 {
  let p: *u8 = "-lm";
  return p;
}

/**
 * ld flag that pulls libsqlite3.
 * PLATFORM: LINUX — Ubuntu gold ships libsqlite3-0 (SONAME .so.0) without
 * libsqlite3-dev, so raw `ld -lsqlite3` fails (`libsqlite3.so` missing).
 * `-l:libsqlite3.so.0` is the exact filename in the default search dir.
 * PLATFORM: MACOS|DARWIN / WINDOWS — `-lsqlite3` (SDK / MinGW name).
 * @return *u8 — static flag string; never null
 */
#[no_mangle]
export function labi_ld_flag_lsqlite3(): *u8 {
  let linux: i32 = 0;
  unsafe {
    linux = xlang_host_is_linux();
  }
  if (linux != 0) {
    let p: *u8 = "-l:libsqlite3.so.0";
    return p;
  }
  let p: *u8 = "-lsqlite3";
  return p;
}

/** Exported function `labi_ld_flag_pthread`.
 * Read path helper `labi_ld_flag_pthread`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_pthread(): *u8 {
  let p: *u8 = "-pthread";
  return p;
}

/** Exported function `labi_ld_flag_lpthread`.
 * Read path helper `labi_ld_flag_lpthread`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lpthread(): *u8 {
  let p: *u8 = "-lpthread";
  return p;
}

/** Exported function `labi_ld_flag_ldl`.
 * Implements `labi_ld_flag_ldl`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_ldl(): *u8 {
  let p: *u8 = "-ldl";
  return p;
}

/** Exported function `labi_ld_flag_lc`.
 * Implements `labi_ld_flag_lc`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lc(): *u8 {
  let p: *u8 = "-lc";
  return p;
}

/** Exported function `labi_ld_flag_lSystem`.
 * Implements `labi_ld_flag_lSystem`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lSystem(): *u8 {
  let p: *u8 = "-lSystem";
  return p;
}

/** Exported function `labi_ld_flag_lws2_32`.
 * Implements `labi_ld_flag_lws2_32`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lws2_32(): *u8 {
  let p: *u8 = "-lws2_32";
  return p;
}

/** Exported function `labi_ld_flag_lbcrypt`.
 * Implements `labi_ld_flag_lbcrypt`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_lbcrypt(): *u8 {
  let p: *u8 = "-lbcrypt";
  return p;
}

/**
 * Homebrew OpenSSL libdir -L flag (wave158 net_tls pure catalog).
 * @return *u8 — always "-L/opt/homebrew/opt/openssl/lib"
 * PLATFORM: SHARED string; consumers gate with link_abi_host_is_apple (≡ mega #if __APPLE__).
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_L_hb_openssl(): *u8 {
  let p: *u8 = "-L/opt/homebrew/opt/openssl/lib";
  return p;
}

/**
 * Homebrew mbedTLS libdir -L flag (wave158 net_tls pure catalog).
 * @return *u8 — always "-L/opt/homebrew/opt/mbedtls/lib"
 * PLATFORM: SHARED string; consumers gate with link_abi_host_is_apple.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_L_hb_mbedtls(): *u8 {
  let p: *u8 = "-L/opt/homebrew/opt/mbedtls/lib";
  return p;
}

/**
 * OpenSSL link flag -lssl (wave158 net_tls pure catalog).
 * @return *u8 — always "-lssl"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_lssl(): *u8 {
  let p: *u8 = "-lssl";
  return p;
}

/**
 * OpenSSL link flag -lcrypto (wave158 net_tls pure catalog).
 * @return *u8 — always "-lcrypto"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_lcrypto(): *u8 {
  let p: *u8 = "-lcrypto";
  return p;
}

/**
 * mbedTLS link flag -lmbedtls (wave158 net_tls pure catalog).
 * @return *u8 — always "-lmbedtls"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_lmbedtls(): *u8 {
  let p: *u8 = "-lmbedtls";
  return p;
}

/**
 * mbedTLS link flag -lmbedx509 (wave158 net_tls pure catalog).
 * @return *u8 — always "-lmbedx509"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_lmbedx509(): *u8 {
  let p: *u8 = "-lmbedx509";
  return p;
}

/**
 * mbedTLS link flag -lmbedcrypto (wave158 net_tls pure catalog).
 * @return *u8 — always "-lmbedcrypto"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_ld_flag_lmbedcrypto(): *u8 {
  let p: *u8 = "-lmbedcrypto";
  return p;
}

/**
 * TLS OpenSSL backend marker symbol name (wave158; Cap residual exports_marker needle).
 * @return *u8 — always "xlang_net_tls_openssl_marker"
 * PLATFORM: SHARED — F-04 v8 marker in std/net/tls_openssl.o (not net.o).
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_net_tls_openssl_marker(): *u8 {
  let p: *u8 = "xlang_net_tls_openssl_marker";
  return p;
}

/**
 * TLS mbedTLS backend marker symbol name (wave158; Cap residual exports_marker needle).
 * @return *u8 — always "xlang_net_tls_mbedtls_marker"
 * PLATFORM: SHARED — F-04 v9 marker in std/net/tls_mbedtls.o (not net.o).
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_net_tls_mbedtls_marker(): *u8 {
  let p: *u8 = "xlang_net_tls_mbedtls_marker";
  return p;
}

/**
 * Relative path for OpenSSL TLS .o under repo root (wave158 pure catalog).
 * @return *u8 — always "std/net/tls_openssl.o"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_rel_tls_openssl_o(): *u8 {
  let p: *u8 = "std/net/tls_openssl.o";
  return p;
}

/**
 * Relative path for mbedTLS TLS .o under repo root (wave158 pure catalog).
 * @return *u8 — always "std/net/tls_mbedtls.o"
 * PLATFORM: SHARED
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_rel_tls_mbedtls_o(): *u8 {
  let p: *u8 = "std/net/tls_mbedtls.o";
  return p;
}

/**
 * Append OpenSSL -L (Apple homebrew only) + -lssl -lcrypto onto cc/ld argv.
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param i *i32 — in/out argv length; null → no-op
 * @param argv_cap i32 — capacity; leave one slot for NULL terminator
 * @return void — appends zero or more flags when capacity remains
 * Pure orch: pure flag_* + Cap residual link_abi_host_is_apple for -L gate (≡ mega #if __APPLE__).
 * Why (wave158): share openssl lib append between net_o and tls_openssl.o branches (G.7).
 * PLATFORM: SHARED orch / MACOS -L path only when host_is_apple.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_append_openssl_ld_flags(argv: **u8, i: *i32, argv_cap: i32): void {
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (i == 0 as *i32) {
    return;
  }
  let is_apple: i32 = 0;
  unsafe {
    is_apple = link_abi_host_is_apple();
  }
  if (is_apple != 0) {
    let cur: i32 = i[0];
    if (cur < argv_cap - 1) {
      let fl: *u8 = labi_ld_flag_L_hb_openssl();
      argv[cur] = fl;
      i[0] = cur + 1;
    }
  }
  let cur2: i32 = i[0];
  if (cur2 < argv_cap - 1) {
    let fssl: *u8 = labi_ld_flag_lssl();
    argv[cur2] = fssl;
    i[0] = cur2 + 1;
  }
  let cur3: i32 = i[0];
  if (cur3 < argv_cap - 1) {
    let fcr: *u8 = labi_ld_flag_lcrypto();
    argv[cur3] = fcr;
    i[0] = cur3 + 1;
  }
}

/**
 * Append mbedTLS -L (Apple homebrew only) + -lmbedtls -lmbedx509 -lmbedcrypto onto cc/ld argv.
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param i *i32 — in/out argv length; null → no-op
 * @param argv_cap i32 — capacity; leave one slot for NULL terminator
 * @return void — appends zero or more flags when capacity remains
 * Pure orch: pure flag_* + Cap residual link_abi_host_is_apple for -L gate (≡ mega #if __APPLE__).
 * Why (wave158): share mbedtls lib append between net_o and tls_mbedtls.o branches (G.7).
 * PLATFORM: SHARED orch / MACOS -L path only when host_is_apple.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function labi_append_mbedtls_ld_flags(argv: **u8, i: *i32, argv_cap: i32): void {
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (i == 0 as *i32) {
    return;
  }
  let is_apple: i32 = 0;
  unsafe {
    is_apple = link_abi_host_is_apple();
  }
  if (is_apple != 0) {
    let cur: i32 = i[0];
    if (cur < argv_cap - 1) {
      let fl: *u8 = labi_ld_flag_L_hb_mbedtls();
      argv[cur] = fl;
      i[0] = cur + 1;
    }
  }
  let cur2: i32 = i[0];
  if (cur2 < argv_cap - 1) {
    let fmb: *u8 = labi_ld_flag_lmbedtls();
    argv[cur2] = fmb;
    i[0] = cur2 + 1;
  }
  let cur3: i32 = i[0];
  if (cur3 < argv_cap - 1) {
    let fx: *u8 = labi_ld_flag_lmbedx509();
    argv[cur3] = fx;
    i[0] = cur3 + 1;
  }
  let cur4: i32 = i[0];
  if (cur4 < argv_cap - 1) {
    let fc: *u8 = labi_ld_flag_lmbedcrypto();
    argv[cur4] = fc;
    i[0] = cur4 + 1;
  }
}

/** Exported function `labi_ld_driver_clang`.
 * Implements `labi_ld_driver_clang`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_driver_clang(): *u8 {
  let p: *u8 = "clang";
  return p;
}

/** Exported function `labi_ld_driver_ld`.
 * Implements `labi_ld_driver_ld`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_driver_ld(): *u8 {
  let p: *u8 = "ld";
  return p;
}

/** Exported function `labi_ld_driver_gcc`.
 * Implements `labi_ld_driver_gcc`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_driver_gcc(): *u8 {
  let p: *u8 = "gcc";
  return p;
}

/** Exported function `labi_ld_driver_cc`.
 * Implements `labi_ld_driver_cc`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_driver_cc(): *u8 {
  let p: *u8 = "cc";
  return p;
}

/** Exported function `labi_ld_mach_entry_main`.
 * Implements `labi_ld_mach_entry_main`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_mach_entry_main(): *u8 {
  let p: *u8 = "_main";
  return p;
}

/** Exported function `labi_ld_flag_e`.
 * Implements `labi_ld_flag_e`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_e(): *u8 {
  let p: *u8 = "-e";
  return p;
}

/** Exported function `labi_ld_flag_o`.
 * Implements `labi_ld_flag_o`.
 * @return *u8
 */
#[no_mangle]
export function labi_ld_flag_o(): *u8 {
  let p: *u8 = "-o";
  return p;
}

/** Exported function `labi_ld_common_tail_flag_count`.
 * Implements `labi_ld_common_tail_flag_count`.
 * @return i32
 */
#[no_mangle]
export function labi_ld_common_tail_flag_count(): i32 {
  return 7;
}

/** Exported function `labi_ld_common_tail_flag_at`.
 * Implements `labi_ld_common_tail_flag_at`.
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_ld_common_tail_flag_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "-lm";
    return p;
  }
  if (i == 1) {
    return labi_ld_flag_lsqlite3();
  }
  if (i == 2) {
    let p: *u8 = "-pthread";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "-lpthread";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "-ldl";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "-lc";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "-lSystem";
    return p;
  }
  return 0 as *u8;
}

/**
 * Append Homebrew /usr/local -L paths onto an ld/cc argv (Apple hosts only).
 * Enables -lz / -lzstd / -lbrotli* resolution under brew prefixes without hardcoding
 * at each compress-lib append site.
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param la *i32 — in/out argv length; null → no-op
 * @param max_la i32 — argv capacity; need *la < max_la - 1 (room for NUL terminator)
 * @return void — no-op on non-Apple; skips null/empty table entries; stops when capacity full
 * Pure orch: Cap residual link_abi_host_is_apple + pure brew table count/at + append loop.
 * Cap residual: link_abi_host_is_apple (#if __APPLE__; all arch — not aarch64-only host_lit).
 * Why (wave152): hybrid still had always-mega C body for brew -L append (#if APPLE loop).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch / MACOS consumers (Linux/Windows host_is_apple → 0 no-op).
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function ld_append_brew_lib_paths(argv: **u8, la: *i32, max_la: i32): void {
  // Cap residual: only Apple hosts append -L brew paths (≡ mega #if defined(__APPLE__)).
  let apple: i32 = 0;
  unsafe {
    apple = link_abi_host_is_apple();
  }
  if (apple == 0) {
    return;
  }
  // Guard argv null via *u8 cast (wave147/151: avoid **u8 null compare codegen drop).
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  let n: i32 = labi_ld_brew_lib_path_count();
  let k: i32 = 0;
  while (k < n) {
    // Capacity guard: leave one slot for argv NULL terminator (≡ mega max_la - 1).
    let cur: i32 = la[0];
    if (cur >= max_la - 1) {
      break;
    }
    let p: *u8 = labi_ld_brew_lib_path_at(k);
    k = k + 1;
    if (p == 0 as *u8) {
      continue;
    }
    if (p[0] == 0) {
      continue;
    }
    // Store table pointer (static string lifetime; no copy).
    argv[cur] = p;
    la[0] = cur + 1;
  }
}

/**
 * ASM ld: append -lz / -lzstd / -lbrotli* (and zlib glue .o) when compress_o or user_o needs them.
 * Gates each format via Cap residual / peer pure link_abi_obj_needs_*; brew -L via pure peer
 * ld_append_brew_lib_paths; flag strings via pure labi_ld_flag_*; zlib glue via Cap residual
 * ensure + path then direct argv append (asm path does not use invoke_cc_argv_push_existing).
 * @param compress_o *u8 — path to std/compress .o (nullable/empty → ignored by needs_*)
 * @param user_o *u8 — path to user main .o (nullable/empty → ignored by needs_*)
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param la *i32 — in/out argv length; null → no-op
 * @param max_la i32 — argv capacity; leave one slot for NULL terminator (max_la - 1)
 * @return void — appends only when a needs_* hits and capacity remains
 * Pure orch: needs_* Cap/peer + brew pure + flag pure + ensure/path Cap residual.
 * Cap residual: xlang_ensure_runtime_compress_zlib_glue_o + xlang_runtime_compress_zlib_glue_o_path;
 *   needs_* Cap (marker/has_undef) live under ondemand hybrid pure.
 * Why (wave153): hybrid still had always-mega C body for asm compress -l* append.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * Sibling invoke_cc_append_compress_ld: wave154 pure orch (push_existing Cap residual for glue).
 * PLATFORM: SHARED — verify mac + Ubuntu compress neighborhood + prove IDENTICAL.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function asm_ld_append_compress_libs(compress_o: *u8, user_o: *u8, argv: **u8, la: *i32, max_la: i32): void {
  // Guard argv null via *u8 cast (wave147/151/152: avoid **u8 null compare codegen drop).
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  let need_z: i32 = 0;
  let need_zs: i32 = 0;
  let need_br: i32 = 0;
  unsafe {
    need_z = link_abi_obj_needs_zlib(compress_o);
    if (need_z == 0) {
      need_z = link_abi_obj_needs_zlib(user_o);
    }
    need_zs = link_abi_obj_needs_zstd(compress_o);
    if (need_zs == 0) {
      need_zs = link_abi_obj_needs_zstd(user_o);
    }
    need_br = link_abi_obj_needs_brotli(compress_o);
    if (need_br == 0) {
      need_br = link_abi_obj_needs_brotli(user_o);
    }
  }
  if (need_z != 0) {
    // brew -L then -lz; ensure zlib macro-wrapper glue .o and append its path.
    ld_append_brew_lib_paths(argv, la, max_la);
    let cur: i32 = la[0];
    if (cur < max_la - 1) {
      let fl: *u8 = labi_ld_flag_lz();
      argv[cur] = fl;
      la[0] = cur + 1;
    }
    // Cap residual: build/ensure glue then resolve path (argv0 null ≡ mega NULL).
    unsafe {
      let _e: i32 = xlang_ensure_runtime_compress_zlib_glue_o(0 as *u8);
    }
    let glue: *u8 = 0 as *u8;
    unsafe {
      glue = xlang_runtime_compress_zlib_glue_o_path(0 as *u8);
    }
    if (glue != 0 as *u8) {
      if (glue[0] != 0) {
        let cur2: i32 = la[0];
        if (cur2 < max_la - 1) {
          argv[cur2] = glue;
          la[0] = cur2 + 1;
        }
      }
    }
  }
  if (need_zs != 0) {
    ld_append_brew_lib_paths(argv, la, max_la);
    let curz: i32 = la[0];
    if (curz < max_la - 1) {
      let flz: *u8 = labi_ld_flag_lzstd();
      argv[curz] = flz;
      la[0] = curz + 1;
    }
  }
  if (need_br != 0) {
    ld_append_brew_lib_paths(argv, la, max_la);
    let curb: i32 = la[0];
    if (curb < max_la - 1) {
      let fle: *u8 = labi_ld_flag_lbrotlienc();
      argv[curb] = fle;
      la[0] = curb + 1;
    }
    let curb2: i32 = la[0];
    if (curb2 < max_la - 1) {
      let fld: *u8 = labi_ld_flag_lbrotlidec();
      argv[curb2] = fld;
      la[0] = curb2 + 1;
    }
  }
}

/**
 * invoke_cc link: append -lz / -lzstd / -lbrotli* (and zlib glue .o) when compress_o or user_o needs them.
 * Same needs/brew/flag structure as asm_ld_append_compress_libs, but glue goes through Cap residual
 * invoke_cc_argv_push_existing (skip missing, realpath on POSIX, dedup) rather than direct argv store.
 * @param argv **u8 — cc linker argv table (char**); null → no-op
 * @param i *i32 — in/out argv length; null → no-op
 * @param argv_cap i32 — argv capacity; early exit if *i >= argv_cap - 1 (room for NUL terminator)
 * @param compress_o *u8 — path to std/compress .o (nullable/empty → ignored by needs_*)
 * @param user_o *u8 — path to user main .o (nullable/empty → ignored by needs_*)
 * @return void — appends only when a needs_* hits and capacity remains
 * Pure orch: needs_* Cap/peer + brew pure + flag pure + ensure/path Cap + pure push_existing.
 * Cap residual: push_existing resolve pool (wave179 Cap); ensure + path for glue;
 *   needs_* Cap (marker/has_undef) live under ondemand hybrid pure.
 * Why (wave154): hybrid still had always-mega C body for invoke_cc compress -l* append.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED — verify mac + Ubuntu compress neighborhood + prove IDENTICAL.
 * Track-L: #[no_mangle] keeps surface short name.
 */
#[no_mangle]
export function invoke_cc_append_compress_ld(argv: **u8, i: *i32, argv_cap: i32, compress_o: *u8, user_o: *u8): void {
  // Guard argv null via *u8 cast (wave147/151–153: avoid **u8 null compare codegen drop).
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (i == 0 as *i32) {
    return;
  }
  // Early capacity guard (≡ mega *i >= argv_cap - 1 at entry).
  if (i[0] >= argv_cap - 1) {
    return;
  }
  let need_z: i32 = 0;
  let need_zs: i32 = 0;
  let need_br: i32 = 0;
  unsafe {
    need_z = link_abi_obj_needs_zlib(compress_o);
    if (need_z == 0) {
      need_z = link_abi_obj_needs_zlib(user_o);
    }
    need_zs = link_abi_obj_needs_zstd(compress_o);
    if (need_zs == 0) {
      need_zs = link_abi_obj_needs_zstd(user_o);
    }
    need_br = link_abi_obj_needs_brotli(compress_o);
    if (need_br == 0) {
      need_br = link_abi_obj_needs_brotli(user_o);
    }
  }
  if (need_z != 0) {
    // brew -L then -lz; ensure zlib glue .o and push via pure push_existing (wave179).
    ld_append_brew_lib_paths(argv, i, argv_cap);
    let cur: i32 = i[0];
    if (cur < argv_cap - 1) {
      let fl: *u8 = labi_ld_flag_lz();
      argv[cur] = fl;
      i[0] = cur + 1;
    }
    // Cap residual: build/ensure glue then push path (argv0 null ≡ mega NULL).
    unsafe {
      let _e: i32 = xlang_ensure_runtime_compress_zlib_glue_o(0 as *u8);
    }
    let glue: *u8 = 0 as *u8;
    unsafe {
      glue = xlang_runtime_compress_zlib_glue_o_path(0 as *u8);
    }
    // Pure peer wave179: skip-missing / realpath / dedup (asm path stores path bytes directly).
    let _p: i32 = invoke_cc_argv_push_existing(argv, i, argv_cap, glue);
  }
  if (need_zs != 0) {
    ld_append_brew_lib_paths(argv, i, argv_cap);
    let curz: i32 = i[0];
    if (curz < argv_cap - 1) {
      let flz: *u8 = labi_ld_flag_lzstd();
      argv[curz] = flz;
      i[0] = curz + 1;
    }
  }
  if (need_br != 0) {
    ld_append_brew_lib_paths(argv, i, argv_cap);
    let curb: i32 = i[0];
    if (curb < argv_cap - 1) {
      let fle: *u8 = labi_ld_flag_lbrotlienc();
      argv[curb] = fle;
      i[0] = curb + 1;
    }
    let curb2: i32 = i[0];
    if (curb2 < argv_cap - 1) {
      let fld: *u8 = labi_ld_flag_lbrotlidec();
      argv[curb2] = fld;
      i[0] = curb2 + 1;
    }
  }
}

/**
 * macOS asm ld/clang: append tail -l* from ShuAsmLdStdLinkFlags (math/compress/sqlite/pthread/System).
 * Pure orch over LP64 i32 flag layout + pure labi_ld_flag_* + peer asm_ld_append_compress_libs
 * + peer link_abi_user_o_needs_compress_libs. Gate xlang_asm_ld_append_mach_tail_libs stays L9 thin.
 * @param compress_o *u8 — path to std/compress .o (nullable/empty → ignored by needs_*)
 * @param user_o *u8 — path to user main .o (nullable/empty → ignored by needs_*)
 * @param flags *u8 — ShuAsmLdStdLinkFlags* as opaque bytes; null → no-op
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param la *i32 — in/out argv length; null → no-op; *la < 0 → no-op
 * @param max_la i32 — argv capacity; leave one slot for NULL terminator (max_la - 1)
 * @param append_lsystem i32 — non-zero → also append -lSystem (clang driver path often skips)
 * @return void — appends zero or more tail flags; compress may expand multi -l* via peer orch
 * Flag layout (PLATFORM: SHARED LP64 int fields, declaration order ≡ runtime_link_abi.h):
 *   0=have_io 1=have_net 2=have_thread 3=have_sync 4=have_channel
 *   5=have_math 6=have_compress 7=have_dynlib 8=have_sqlite
 *   9=have_elf 10=have_libc_heap 11=have_fs
 * need_pt = have_thread || have_sync || have_channel (≡ mega).
 * Why (wave156): hybrid still had always-mega C body for mach tail -l* over pure flag tables.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * Callers: pure gate xlang_asm_ld_append_mach_tail_libs (labi_gates) + product asm ld paths.
 * PLATFORM: SHARED orch / MACOS consumers (flags semantics shared; -lSystem is Darwin).
 * Track-L: #[no_mangle] keeps surface short name matching mega / gates Cap residual extern.
 */
#[no_mangle]
export function xlang_asm_ld_append_mach_tail_libs_impl(compress_o: *u8, user_o: *u8, flags: *u8, argv: **u8, la: *i32, max_la: i32, append_lsystem: i32): void {
  // Guard nulls via *u8 cast (wave147/151–155: avoid **u8 null compare codegen drop).
  if (flags == 0 as *u8) {
    return;
  }
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  if (la[0] < 0) {
    return;
  }
  // LP64 shared: flags is contiguous i32 fields (ShuAsmLdStdLinkFlags).
  let f: *i32 = flags as *i32;
  let have_thread: i32 = f[2];
  let have_sync: i32 = f[3];
  let have_channel: i32 = f[4];
  let have_math: i32 = f[5];
  let have_compress: i32 = f[6];
  let have_sqlite: i32 = f[8];
  // need_pt ≡ mega: thread | sync | channel.
  let need_pt: i32 = 0;
  if (have_thread != 0) {
    need_pt = 1;
  }
  if (have_sync != 0) {
    need_pt = 1;
  }
  if (have_channel != 0) {
    need_pt = 1;
  }
  // -lm when math std linked.
  if (have_math != 0) {
    let cur: i32 = la[0];
    if (cur < max_la - 1) {
      let fl: *u8 = labi_ld_flag_lm();
      argv[cur] = fl;
      la[0] = cur + 1;
    }
  }
  // compress -l* when flag set or user.o UNDEF needs compress (peer pure aggregate).
  let need_comp: i32 = have_compress;
  if (need_comp == 0) {
    unsafe {
      need_comp = link_abi_user_o_needs_compress_libs(user_o);
    }
  }
  if (need_comp != 0) {
    asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la);
  }
  // -lsqlite3 only when glue.o actually U sqlite3_open (real libsqlite3 TU).
  // Stub glue (no sqlite3.h) defines xlang_sqlite3_*_c without that U; adding
  // -lsqlite3 then fails Ubuntu gold `ld: cannot find -lsqlite3`.
  // PLATFORM: SHARED — G.7 complete have_sqlite tail; glue already OP 18.
  if (have_sqlite != 0) {
    let gp: *u8 = 0 as *u8;
    let need_lib: i32 = 1;
    unsafe {
      gp = asm_link_obj_skip_missing("compiler/runtime_sqlite_glue.o");
    }
    if (gp == 0 as *u8) {
      unsafe {
        gp = asm_link_obj_skip_missing("runtime_sqlite_glue.o");
      }
    }
    if (gp != 0 as *u8) {
      unsafe {
        need_lib = xlang_link_obj_needs_undef_sym(gp, "sqlite3_open");
      }
    }
    if (need_lib != 0) {
      let curs: i32 = la[0];
      if (curs < max_la - 1) {
        let fs: *u8 = labi_ld_flag_lsqlite3();
        argv[curs] = fs;
        la[0] = curs + 1;
      }
    }
  }
  // -lpthread when thread/sync/channel.
  // PLATFORM: MACOS — bare /usr/bin/ld (used by asm -o exe path) does not
  // recognize the -pthread driver flag (it is a cc/clang driver option).
  // Use -lpthread instead so the library is resolved via libSystem on
  // Darwin and via libpthread on Linux. This matches the unix_gcc twin
  // (labi_invoke_ld_list.x !have_io && need_pt branch) which already uses
  // labi_ld_flag_lpthread(). Before wave955: mach tail unconditionally used
  // labi_ld_flag_pthread() = "-pthread" → macOS ld: "unknown options:
  // -pthread" → BLD001 for any user program importing std.net/thread/sync/
  // channel (e.g. examples/cookbook/net_listen_bind.x). G.7: fix at the
  // single authority (mach tail libs) — no second path. G.8: SHARED, both
  // .x and from_x.c twin updated in same commit.
  if (need_pt != 0) {
    let curp: i32 = la[0];
    if (curp < max_la - 1) {
      let fp: *u8 = labi_ld_flag_lpthread();
      argv[curp] = fp;
      la[0] = curp + 1;
    }
  }
  // -lSystem optional (clang as driver often pulls System; bare ld may need it).
  if (append_lsystem != 0) {
    let curl: i32 = la[0];
    if (curl < max_la - 1) {
      let fsys: *u8 = labi_ld_flag_lSystem();
      argv[curl] = fsys;
      la[0] = curl + 1;
    }
  }
}

/**
 * Linux/Unix gcc or bare ld: append tail -l* from ShuAsmLdStdLinkFlags + need_pt.
 * Pure orch over LP64 i32 flag layout + pure labi_ld_flag_* + peer compress orch
 * + peer needs_compress + peer xlang_host_is_linux + Cap residual host_is_apple.
 * Gate xlang_asm_ld_append_unix_gcc_tail_libs stays L9 thin.
 * @param compress_o *u8 — path to std/compress .o (nullable/empty → ignored by needs_*)
 * @param user_o *u8 — path to user main .o (nullable/empty → ignored by needs_*)
 * @param flags *u8 — ShuAsmLdStdLinkFlags* as opaque bytes; null → no-op
 * @param need_pt i32 — non-zero when thread|sync|channel (caller-derived; ≡ mega)
 * @param argv **u8 — linker argv table (char**); null → no-op
 * @param la *i32 — in/out argv length; null → no-op; *la < 0 → no-op
 * @param max_la i32 — argv capacity; leave one slot for NULL terminator (max_la - 1)
 * @return void — appends zero or more tail flags; compress may expand multi -l*
 * Flag layout (PLATFORM: SHARED LP64 int fields ≡ runtime_link_abi.h):
 *   0=have_io 1=have_net 2=have_thread 3=have_sync 4=have_channel
 *   5=have_math 6=have_compress 7=have_dynlib 8=have_sqlite
 *   9=have_elf 10=have_libc_heap 11=have_fs
 * pthread selection (≡ mega branches):
 *   have_io && need_pt → -pthread; !have_io && need_pt → -lpthread; else no pthread flag
 * -ldl only when host linux && have_dynlib (mega #if __linux__).
 * -lc always when have_io || have_net || need_pt; else only on linux|apple when any of
 *   heap|fs|math|compress|sqlite|dynlib (mega #if linux||apple in final else).
 * Why (wave157): hybrid still had always-mega C body for unix gcc tail -l* over pure tables.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * Callers: pure gate xlang_asm_ld_append_unix_gcc_tail_libs (labi_gates) + product asm ld paths.
 * PLATFORM: SHARED orch / LINUX primary consumers (Unix gcc/ld; -ldl Linux-only).
 * Track-L: #[no_mangle] keeps surface short name matching mega / gates Cap residual extern.
 */
#[no_mangle]
export function xlang_asm_ld_append_unix_gcc_tail_libs_impl(compress_o: *u8, user_o: *u8, flags: *u8, need_pt: i32, argv: **u8, la: *i32, max_la: i32): void {
  // Guard nulls via *u8 cast (wave147/151–156: avoid **u8 null compare codegen drop).
  if (flags == 0 as *u8) {
    return;
  }
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  if (la[0] < 0) {
    return;
  }
  // LP64 shared: flags is contiguous i32 fields (ShuAsmLdStdLinkFlags).
  let f: *i32 = flags as *i32;
  let have_io: i32 = f[0];
  let have_net: i32 = f[1];
  let have_math: i32 = f[5];
  let have_compress: i32 = f[6];
  let have_dynlib: i32 = f[7];
  let have_sqlite: i32 = f[8];
  let have_libc_heap: i32 = f[10];
  let have_fs: i32 = f[11];
  // pthread: have_io uses -pthread; net/need_pt alone uses -lpthread (≡ mega).
  if (have_io != 0) {
    if (need_pt != 0) {
      let cur0: i32 = la[0];
      if (cur0 < max_la - 1) {
        let fp0: *u8 = labi_ld_flag_pthread();
        argv[cur0] = fp0;
        la[0] = cur0 + 1;
      }
    }
  } else {
    if (need_pt != 0) {
      let cur1: i32 = la[0];
      if (cur1 < max_la - 1) {
        let fp1: *u8 = labi_ld_flag_lpthread();
        argv[cur1] = fp1;
        la[0] = cur1 + 1;
      }
    }
  }
  // -lm when math std linked (all branches).
  if (have_math != 0) {
    let curm: i32 = la[0];
    if (curm < max_la - 1) {
      let fm: *u8 = labi_ld_flag_lm();
      argv[curm] = fm;
      la[0] = curm + 1;
    }
  }
  // compress -l* when flag set or user.o UNDEF needs compress (peer pure aggregate).
  let need_comp: i32 = have_compress;
  if (need_comp == 0) {
    unsafe {
      need_comp = link_abi_user_o_needs_compress_libs(user_o);
    }
  }
  if (need_comp != 0) {
    asm_ld_append_compress_libs(compress_o, user_o, argv, la, max_la);
  }
  // -lsqlite3 only when glue.o actually U sqlite3_open (real libsqlite3 TU).
  // Stub glue (no sqlite3.h) must not pull -lsqlite3 (Ubuntu gold).
  // PLATFORM: SHARED — G.7 complete have_sqlite tail; ≡ mach twin.
  if (have_sqlite != 0) {
    let gp: *u8 = 0 as *u8;
    let need_lib: i32 = 1;
    unsafe {
      gp = asm_link_obj_skip_missing("compiler/runtime_sqlite_glue.o");
    }
    if (gp == 0 as *u8) {
      unsafe {
        gp = asm_link_obj_skip_missing("runtime_sqlite_glue.o");
      }
    }
    if (gp != 0 as *u8) {
      unsafe {
        need_lib = xlang_link_obj_needs_undef_sym(gp, "sqlite3_open");
      }
    }
    if (need_lib != 0) {
      let curs: i32 = la[0];
      if (curs < max_la - 1) {
        let fs: *u8 = labi_ld_flag_lsqlite3();
        argv[curs] = fs;
        la[0] = curs + 1;
      }
    }
  }
  // -ldl only on Linux when dynlib (mega #if __linux__; peer pure host_is_linux).
  if (have_dynlib != 0) {
    let is_linux: i32 = 0;
    unsafe {
      is_linux = xlang_host_is_linux();
    }
    if (is_linux != 0) {
      let curd: i32 = la[0];
      if (curd < max_la - 1) {
        let fd: *u8 = labi_ld_flag_ldl();
        argv[curd] = fd;
        la[0] = curd + 1;
      }
    }
  }
  // -lc: always when io/net/need_pt (mega branches 1–4); else conditional (branch 5).
  let always_lc: i32 = 0;
  if (have_io != 0) {
    always_lc = 1;
  }
  if (have_net != 0) {
    always_lc = 1;
  }
  if (need_pt != 0) {
    always_lc = 1;
  }
  if (always_lc != 0) {
    let curc: i32 = la[0];
    if (curc < max_la - 1) {
      let fc: *u8 = labi_ld_flag_lc();
      argv[curc] = fc;
      la[0] = curc + 1;
    }
  } else {
    // Final else: -lc only on linux|apple when any of heap/fs/math/compress/sqlite/dynlib.
    let want_lc: i32 = 0;
    if (have_libc_heap != 0) {
      want_lc = 1;
    }
    if (have_fs != 0) {
      want_lc = 1;
    }
    if (have_math != 0) {
      want_lc = 1;
    }
    if (have_compress != 0) {
      want_lc = 1;
    }
    if (have_sqlite != 0) {
      want_lc = 1;
    }
    if (have_dynlib != 0) {
      want_lc = 1;
    }
    if (want_lc != 0) {
      let is_linux2: i32 = 0;
      let is_apple: i32 = 0;
      unsafe {
        is_linux2 = xlang_host_is_linux();
        is_apple = link_abi_host_is_apple();
      }
      if (is_linux2 != 0 || is_apple != 0) {
        let curc2: i32 = la[0];
        if (curc2 < max_la - 1) {
          let fc2: *u8 = labi_ld_flag_lc();
          argv[curc2] = fc2;
          la[0] = curc2 + 1;
        }
      }
    }
  }
}

/**
 * invoke_cc link: append OpenSSL or mbedTLS -L/-l when net.o or std/net/tls_*.o exports TLS markers.
 * F-04 v8/v9: markers live in tls_openssl.o / tls_mbedtls.o (not compiled into net.o).
 * @param argv **u8 — cc linker argv table (char**); null → return 0
 * @param i *i32 — in/out argv length; null → return 0
 * @param argv_cap i32 — capacity; early exit if *i >= argv_cap - 1
 * @param net_o *u8 — path to std/net .o (nullable/empty → skip net_o marker phase)
 * @param repo_root *u8 — repo root for rel resolve of tls_*.o (nullable/empty → skip phase 2)
 * @return i32 — 1 if TLS libs were appended, 0 otherwise
 * Pure orch: pure marker/rel/flag catalogs + peer labi_append_{openssl,mbedtls}_ld_flags.
 * Cap residual: link_abi_obj_exports_marker; link_abi_realpath_cap (POSIX; Windows null ≡ mega);
 *   xlang_rel_o_path_from_argv0; invoke_cc_argv_push_existing (tls_*.o only, not net_o).
 * Why (wave158): hybrid still had always-mega C body for net_tls -L/-l append.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * Sibling ensure_std_net_o_auto_tls pure at wave187 (Cap residual getenv+system still).
 * PLATFORM: SHARED orch / MACOS brew -L gated by host_is_apple inside append_* helpers.
 * Track-L: #[no_mangle] keeps surface short name matching mega / thin callers.
 */
#[no_mangle]
export function invoke_cc_append_net_tls_ld(argv: **u8, i: *i32, argv_cap: i32, net_o: *u8, repo_root: *u8): i32 {
  // Guard argv null via *u8 cast (wave147/151–157: avoid **u8 null compare codegen drop).
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return 0;
  }
  if (i == 0 as *i32) {
    return 0;
  }
  // Early capacity guard (≡ mega *i >= argv_cap - 1 at entry).
  if (i[0] >= argv_cap - 1) {
    return 0;
  }
  let mk_ssl: *u8 = labi_net_tls_openssl_marker();
  let mk_mb: *u8 = labi_net_tls_mbedtls_marker();
  // Phase 1: probe net_o for legacy co-located markers (rare post F-04 v8).
  if (net_o != 0 as *u8) {
    if (net_o[0] != 0) {
      let use: *u8 = net_o;
      // Cap residual realpath; on fail keep original path (≡ mega #if !WIN32 realpath).
      let abs_n: u8[4096] = [];
      let rn: *u8 = 0 as *u8;
      unsafe {
        rn = link_abi_realpath_cap(net_o, &abs_n[0]);
      }
      if (rn != 0 as *u8) {
        use = rn;
      }
      let hit_ssl: i32 = 0;
      unsafe {
        hit_ssl = link_abi_obj_exports_marker(use, mk_ssl);
      }
      if (hit_ssl != 0) {
        labi_append_openssl_ld_flags(argv, i, argv_cap);
        return 1;
      }
      let hit_mb: i32 = 0;
      unsafe {
        hit_mb = link_abi_obj_exports_marker(use, mk_mb);
      }
      if (hit_mb != 0) {
        labi_append_mbedtls_ld_flags(argv, i, argv_cap);
        return 1;
      }
    }
  }
  // Phase 2: resolve std/net/tls_*.o under repo_root and push .o + libs on marker.
  if (repo_root == 0 as *u8) {
    return 0;
  }
  if (repo_root[0] == 0) {
    return 0;
  }
  let rel_ssl: *u8 = labi_rel_tls_openssl_o();
  let tls_ssl: *u8 = 0 as *u8;
  unsafe {
    tls_ssl = xlang_rel_o_path_from_argv0(repo_root, rel_ssl);
  }
  if (tls_ssl != 0 as *u8) {
    if (tls_ssl[0] != 0) {
      let use2: *u8 = tls_ssl;
      let abs_s: u8[4096] = [];
      let rs: *u8 = 0 as *u8;
      unsafe {
        rs = link_abi_realpath_cap(tls_ssl, &abs_s[0]);
      }
      if (rs != 0 as *u8) {
        use2 = rs;
      }
      let hit2: i32 = 0;
      unsafe {
        hit2 = link_abi_obj_exports_marker(use2, mk_ssl);
      }
      if (hit2 != 0) {
        // Pure peer wave179: skip-missing / realpath / dedup for the .o path itself.
        let _p: i32 = invoke_cc_argv_push_existing(argv, i, argv_cap, tls_ssl);
        labi_append_openssl_ld_flags(argv, i, argv_cap);
        return 1;
      }
    }
  }
  let rel_mb: *u8 = labi_rel_tls_mbedtls_o();
  let tls_mb: *u8 = 0 as *u8;
  unsafe {
    tls_mb = xlang_rel_o_path_from_argv0(repo_root, rel_mb);
  }
  if (tls_mb != 0 as *u8) {
    if (tls_mb[0] != 0) {
      let use3: *u8 = tls_mb;
      let abs_m: u8[4096] = [];
      let rm: *u8 = 0 as *u8;
      unsafe {
        rm = link_abi_realpath_cap(tls_mb, &abs_m[0]);
      }
      if (rm != 0 as *u8) {
        use3 = rm;
      }
      let hit3: i32 = 0;
      unsafe {
        hit3 = link_abi_obj_exports_marker(use3, mk_mb);
      }
      if (hit3 != 0) {
        // Pure peer wave179: skip-missing / realpath / dedup for the .o path itself.
        let _p2: i32 = invoke_cc_argv_push_existing(argv, i, argv_cap, tls_mb);
        labi_append_mbedtls_ld_flags(argv, i, argv_cap);
        return 1;
      }
    }
  }
  return 0;
}

/**
 * Append bytes of `src` onto `dst` starting at `pos` (NUL-terminated result).
 * Pure helper for ensure_std_net_o_auto_tls shell/path buffers (wave187).
 * @param dst *u8 — destination buffer
 * @param cap i32 — capacity including trailing NUL
 * @param pos i32 — current write index (0..cap-1)
 * @param src *u8 — source C string; null treated as empty
 * @return i32 — new pos after append, or -1 if capacity would overflow
 * Track-L: #[no_mangle] keeps surface short name for prove IDENTICAL.
 */
#[no_mangle]
export function labi_net_tls_buf_append(dst: *u8, cap: i32, pos: i32, src: *u8): i32 {
  if (dst == 0 as *u8) {
    return 0 - 1;
  }
  if (pos < 0) {
    return 0 - 1;
  }
  if (pos >= cap) {
    return 0 - 1;
  }
  let i: i32 = 0;
  if (src == 0 as *u8) {
    dst[pos as usize] = 0;
    return pos;
  }
  while (1 == 1) {
    let c: u8 = src[i as usize];
    if (c == 0) {
      break;
    }
    if (pos + 1 >= cap) {
      dst[pos as usize] = 0;
      return 0 - 1;
    }
    dst[pos as usize] = c;
    pos = pos + 1;
    i = i + 1;
  }
  dst[pos as usize] = 0;
  return pos;
}

/**
 * Build net-tls ensure shell command into `cmd` (cap 640).
 * wave944 0-make:
 *   bash '<repo>/tests/lib/compiler-make.sh' <target> >/dev/null 2>&1
 * Historical: `make -C '<repo>/compiler' <target> >/dev/null 2>&1` (Makefile deleted).
 * @param cmd *u8 — destination shell buffer
 * @param cap i32 — capacity (use 640 ≡ mega)
 * @param repo_root *u8 — absolute repo root (already non-empty)
 * @param target *u8 — leaf target (e.g. net-o-openssl)
 * @return i32 — 1 on success, 0 on overflow
 * PLATFORM: SHARED — G.7 hub = tests/lib/compiler-make.sh
 * Track-L: #[no_mangle] keeps surface short name for prove IDENTICAL.
 */
#[no_mangle]
export function labi_net_tls_build_make_cmd(cmd: *u8, cap: i32, repo_root: *u8, target: *u8): i32 {
  let pos: i32 = 0;
  // wave944: bash '<repo>/tests/lib/compiler-make.sh' <target> >/dev/null 2>&1
  pos = labi_net_tls_buf_append(cmd, cap, pos, "bash '");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root);
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, "/tests/lib/compiler-make.sh' ");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, target);
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, " >/dev/null 2>&1");
  if (pos < 0) {
    return 0;
  }
  return 1;
}

/**
 * Join repo_root + '/' + rel into path_buf (pure byte join; no realpath).
 * @param path_buf *u8 — destination
 * @param cap i32 — capacity
 * @param repo_root *u8 — absolute root
 * @param rel *u8 — relative under root (e.g. std/net/tls_openssl.o)
 * @return i32 — 1 success, 0 overflow/null
 * Track-L: #[no_mangle] keeps surface short name for prove IDENTICAL.
 */
#[no_mangle]
export function labi_net_tls_join_repo_rel(path_buf: *u8, cap: i32, repo_root: *u8, rel: *u8): i32 {
  let pos: i32 = 0;
  pos = labi_net_tls_buf_append(path_buf, cap, pos, repo_root);
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(path_buf, cap, pos, "/");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(path_buf, cap, pos, rel);
  if (pos < 0) {
    return 0;
  }
  return 1;
}

/**
 * If XLANG_NET_TLS is set and net/tls objects still lack real TLS markers, run
 * `make -C <repo>/compiler net-o-{stub,openssl,mbedtls}` (system shell Cap residual).
 * F-04 v8: OpenSSL/mbedTLS markers live in std/net/tls_*.o (not compiled into net.o).
 * Modes: stub | openssl | mbedtls | auto (default when mode string is "auto").
 * Empty/unset XLANG_NET_TLS → no-op (≡ mega).
 * @param repo_root *u8 — absolute repository root; null/empty → no-op
 * @return void — best-effort make; marker short-circuit when already built
 * Pure orch: mode strcmp + pure path join + pure make-cmd join.
 * Cap residual: link_abi_getenv (XLANG_NET_TLS pure thin → _impl; wave222);
 *   link_abi_system (make shell pure thin → _impl; wave224); link_abi_realpath_cap;
 *   link_abi_obj_exports_marker (nm/marker probe).
 * Why (wave187): hybrid still had always-mega C body for auto TLS ensure orch
 *   (getenv + marker probe + system make). Soft residual after wave158 net_tls ld append.
 * wave222: raw getenv closed — public pure thin link_abi_getenv owns env lookup.
 * wave224: raw system closed — public pure thin link_abi_system owns shell make.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — system/make is host shell (LINUX/MACOS product hosts).
 * Track-L: #[no_mangle] keeps surface short name for invoke_cc_impl call sites.
 */
#[no_mangle]
export function ensure_std_net_o_auto_tls(repo_root: *u8): void {
  if (repo_root == 0 as *u8) {
    return;
  }
  if (repo_root[0] == 0) {
    return;
  }
  // wave222: mode from env via public pure thin getenv (not raw libc getenv).
  let mode: *u8 = 0 as *u8;
  unsafe {
    mode = link_abi_getenv("XLANG_NET_TLS");
  }
  if (mode == 0 as *u8) {
    return;
  }
  if (mode[0] == 0) {
    return;
  }
  let cmd: u8[640] = [];
  let path_buf: u8[4096] = [];
  let resolved: u8[4096] = [];
  let mk_ssl: *u8 = labi_net_tls_openssl_marker();
  let mk_mb: *u8 = labi_net_tls_mbedtls_marker();
  // stub: always force make net-o-stub (≡ mega).
  let eq_stub: i32 = 0;
  unsafe {
    eq_stub = strcmp(mode, "stub");
  }
  if (eq_stub == 0) {
    let ok: i32 = labi_net_tls_build_make_cmd(&cmd[0], 640, repo_root, "net-o-stub");
    if (ok != 0) {
      unsafe {
        // wave224 G.7: public pure thin link_abi_system (not raw libc system).
        let _s: i32 = link_abi_system(&cmd[0]);
      }
    }
    return;
  }
  // Already have OpenSSL marker object under repo? short-circuit.
  let j1: i32 = labi_net_tls_join_repo_rel(&path_buf[0], 4096, repo_root, "std/net/tls_openssl.o");
  if (j1 != 0) {
    let rp1: *u8 = 0 as *u8;
    unsafe {
      rp1 = link_abi_realpath_cap(&path_buf[0], &resolved[0]);
    }
    if (rp1 != 0 as *u8) {
      let hit1: i32 = 0;
      unsafe {
        hit1 = link_abi_obj_exports_marker(rp1, mk_ssl);
      }
      if (hit1 != 0) {
        return;
      }
    }
  }
  // Already have mbedTLS marker object?
  let j2: i32 = labi_net_tls_join_repo_rel(&path_buf[0], 4096, repo_root, "std/net/tls_mbedtls.o");
  if (j2 != 0) {
    let rp2: *u8 = 0 as *u8;
    unsafe {
      rp2 = link_abi_realpath_cap(&path_buf[0], &resolved[0]);
    }
    if (rp2 != 0 as *u8) {
      let hit2: i32 = 0;
      unsafe {
        hit2 = link_abi_obj_exports_marker(rp2, mk_mb);
      }
      if (hit2 != 0) {
        return;
      }
    }
  }
  // Legacy: markers co-located in net.o (pre F-04 v8 rare path).
  // Try repo/std/net/net.o then cwd std/net/net.o (≡ mega realpath pair).
  resolved[0] = 0;
  let j3: i32 = labi_net_tls_join_repo_rel(&path_buf[0], 4096, repo_root, "std/net/net.o");
  if (j3 != 0) {
    let rp3: *u8 = 0 as *u8;
    unsafe {
      rp3 = link_abi_realpath_cap(&path_buf[0], &resolved[0]);
    }
    if (rp3 == 0 as *u8) {
      // Fallback: cwd-relative std/net/net.o
      unsafe {
        rp3 = link_abi_realpath_cap("std/net/net.o", &resolved[0]);
      }
    }
    if (rp3 != 0 as *u8) {
      let hit_s: i32 = 0;
      let hit_m: i32 = 0;
      unsafe {
        hit_s = link_abi_obj_exports_marker(rp3, mk_ssl);
        hit_m = link_abi_obj_exports_marker(rp3, mk_mb);
      }
      if (hit_s != 0) {
        return;
      }
      if (hit_m != 0) {
        return;
      }
    }
  }
  // Mode openssl: only openssl make.
  let eq_ssl: i32 = 0;
  unsafe {
    eq_ssl = strcmp(mode, "openssl");
  }
  if (eq_ssl == 0) {
    let ok2: i32 = labi_net_tls_build_make_cmd(&cmd[0], 640, repo_root, "net-o-openssl");
    if (ok2 != 0) {
      unsafe {
        // wave224 G.7: public pure thin link_abi_system (not raw libc system).
        let _s2: i32 = link_abi_system(&cmd[0]);
      }
    }
    return;
  }
  // Mode mbedtls: only mbedtls make.
  let eq_mb: i32 = 0;
  unsafe {
    eq_mb = strcmp(mode, "mbedtls");
  }
  if (eq_mb == 0) {
    let ok3: i32 = labi_net_tls_build_make_cmd(&cmd[0], 640, repo_root, "net-o-mbedtls");
    if (ok3 != 0) {
      unsafe {
        // wave224 G.7: public pure thin link_abi_system (not raw libc system).
        let _s3: i32 = link_abi_system(&cmd[0]);
      }
    }
    return;
  }
  // auto: try openssl then mbedtls on failure (≡ mega system != 0).
  let eq_auto: i32 = 0;
  unsafe {
    eq_auto = strcmp(mode, "auto");
  }
  if (eq_auto != 0) {
    return;
  }
  let ok4: i32 = labi_net_tls_build_make_cmd(&cmd[0], 640, repo_root, "net-o-openssl");
  if (ok4 != 0) {
    let rc: i32 = 0;
    unsafe {
      // wave224 G.7: public pure thin link_abi_system (not raw libc system).
      rc = link_abi_system(&cmd[0]);
    }
    if (rc != 0) {
      let ok5: i32 = labi_net_tls_build_make_cmd(&cmd[0], 640, repo_root, "net-o-mbedtls");
      if (ok5 != 0) {
        unsafe {
          // wave224 G.7: public pure thin link_abi_system (not raw libc system).
          let _s5: i32 = link_abi_system(&cmd[0]);
        }
      }
    }
  }
}

/**
 * Build formal-std ensure shell command into `cmd` (cap 768 ≡ mega).
 * Format (wave944 post-delete 0-make):
 *   XLANG_FORMAL_STD_ENSURE=1 XLANG='{bin}' bash '{repo}/tests/lib/compiler-make.sh' '{target}'
 * Historical (pre-wave944): `make -C '{repo}/compiler' '{target}'` — Makefile gone (MG).
 * Pure byte join (G.7 reuses labi_net_tls_buf_append).
 * @param cmd *u8 — destination shell buffer
 * @param cap i32 — capacity including trailing NUL (use 768 ≡ mega)
 * @param xlang_bin *u8 — absolute (or fallback) product host path for XLANG=
 * @param repo_root *u8 — absolute repository root
 * @param make_target *u8 — leaf target relative to compiler/ (e.g. ../std/vec/vec.o)
 * @return i32 — 1 on success, 0 on overflow/null
 * PLATFORM: SHARED — shell hub is tests/lib/compiler-make.sh (G.7 single ensure body).
 * Track-L: #[no_mangle] keeps surface short name for prove IDENTICAL.
 */
#[no_mangle]
export function labi_formal_std_build_make_cmd(cmd: *u8, cap: i32, xlang_bin: *u8, repo_root: *u8, make_target: *u8): i32 {
  let pos: i32 = 0;
  pos = labi_net_tls_buf_append(cmd, cap, pos, "XLANG_FORMAL_STD_ENSURE=1 XLANG='");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, xlang_bin);
  if (pos < 0) {
    return 0;
  }
  // wave944: 0-make hub (G.7). Do not reintroduce make -C after MG delete.
  pos = labi_net_tls_buf_append(cmd, cap, pos, "' bash '");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, repo_root);
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, "/tests/lib/compiler-make.sh' '");
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, make_target);
  if (pos < 0) {
    return 0;
  }
  pos = labi_net_tls_buf_append(cmd, cap, pos, "'");
  if (pos < 0) {
    return 0;
  }
  return 1;
}

/**
 * Ensure a formal std|core .o exists under the repo (gitignored after L4 wipe).
 * If `repo_root/rel_from_repo` is missing, run (wave944 0-make):
 *   XLANG_FORMAL_STD_ENSURE=1 XLANG='{bin}' bash '{repo}/tests/lib/compiler-make.sh' '{make_target}'
 * Historical pre-wave944 used `make -C '{repo}/compiler' '{make_target}'` (Makefile deleted).
 * Reentrancy: nested ensure while compiling formal .o sees XLANG_FORMAL_STD_ENSURE set
 * and only re-checks existence (no second ensure / no fork-bomb).
 * Product host binary: getenv("XLANG") if X_OK, else first of
 *   {repo}/compiler/{xlang_asm,xlang,xlang-c} that is X_OK; realpath preferred.
 * @param repo_root *u8 — absolute repository root; null/empty → 0
 * @param rel_from_repo *u8 — path under repo (e.g. std/vec/vec.o); null/empty → 0
 * @param make_target *u8 — leaf target under compiler/ (e.g. ../std/vec/vec.o); null/empty → 0
 * @return i32 — 1 if object exists after ensure, 0 otherwise
 * Pure orch: path join + XLANG discovery loop + ensure-cmd join (G.7 labi_net_tls_* helpers).
 * Cap residual: link_abi_getenv (pure thin → _impl; wave222); link_abi_path_executable
 *   (X_OK pure thin → _impl; wave221); link_abi_realpath_cap;
 *   link_abi_system (shell ensure pure thin → _impl; wave224);
 *   asm_link_obj_skip_missing (stat existence).
 * Why (wave188): hybrid still had always-mega C body for formal_std_make (getenv+access+
 *   realpath+system make orch). Soft residual sibling of wave187 ensure_std_net.
 * wave221: raw access(X_OK) closed — public pure thin path_executable owns X_OK probe.
 * wave222: raw getenv closed — public pure thin link_abi_getenv owns env lookup.
 * wave224: raw system closed — public pure thin link_abi_system owns shell ensure.
 * wave944: cmd authority = tests/lib/compiler-make.sh (0-make; G.7 with tests hub).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — system/bash is host shell (LINUX/MACOS product hosts).
 * Track-L: #[no_mangle] keeps surface short name for invoke_cc / on_demand call sites.
 */
#[no_mangle]
export function xlang_ensure_formal_std_make_o(repo_root: *u8, rel_from_repo: *u8, make_target: *u8): i32 {
  if (repo_root == 0 as *u8) {
    return 0;
  }
  if (repo_root[0] == 0) {
    return 0;
  }
  if (rel_from_repo == 0 as *u8) {
    return 0;
  }
  if (rel_from_repo[0] == 0) {
    return 0;
  }
  if (make_target == 0 as *u8) {
    return 0;
  }
  if (make_target[0] == 0) {
    return 0;
  }
  // abs = repo_root + '/' + rel_from_repo (pure join; cap 4096 ≡ PATH_MAX product hosts).
  let abs: u8[4096] = [];
  let j0: i32 = labi_net_tls_join_repo_rel(&abs[0], 4096, repo_root, rel_from_repo);
  if (j0 == 0) {
    return 0;
  }
  // Already present? short-circuit (≡ mega asm_link_obj_skip_missing).
  let have0: *u8 = 0 as *u8;
  unsafe {
    have0 = asm_link_obj_skip_missing(&abs[0]);
  }
  if (have0 != 0 as *u8) {
    return 1;
  }
  // Nested ensure while compiling formal .o: do not system(make) again.
  let ensuring: *u8 = 0 as *u8;
  unsafe {
    ensuring = link_abi_getenv("XLANG_FORMAL_STD_ENSURE");
  }
  if (ensuring != 0 as *u8) {
    if (ensuring[0] != 0) {
      if (ensuring[0] != 48) {
        // '0' == 48: only digit zero allows a nested make; any other non-empty → stop.
        return 0;
      }
    }
  }
  // Resolve product host binary into xlang_bin (realpath preferred; copy on fail).
  let xlang_bin: u8[4096] = [];
  xlang_bin[0] = 0;
  let env_xlang: *u8 = 0 as *u8;
  unsafe {
    env_xlang = link_abi_getenv("XLANG");
  }
  // wave221: X_OK via public pure thin path_executable (not raw access mode).
  let found: i32 = 0;
  if (env_xlang != 0 as *u8) {
    if (env_xlang[0] != 0) {
      let ax: i32 = 0;
      unsafe {
        ax = link_abi_path_executable(env_xlang);
      }
      if (ax != 0) {
        let rp: *u8 = 0 as *u8;
        unsafe {
          rp = link_abi_realpath_cap(env_xlang, &xlang_bin[0]);
        }
        if (rp == 0 as *u8) {
          // realpath fail → copy raw XLANG path (≡ mega snprintf).
          let cp: i32 = labi_net_tls_buf_append(&xlang_bin[0], 4096, 0, env_xlang);
          if (cp < 0) {
            return 0;
          }
        }
        found = 1;
      }
    }
  }
  if (found == 0) {
    // Fallback: {repo}/compiler/{xlang_asm,xlang,xlang-c} first X_OK hit.
    let cand: u8[4096] = [];
    let i: i32 = 0;
    while (i < 3) {
      let name: *u8 = 0 as *u8;
      if (i == 0) {
        name = "xlang_asm";
      }
      if (i == 1) {
        name = "xlang";
      }
      if (i == 2) {
        name = "xlang-c";
      }
      // cand = repo_root + "/compiler/" + name
      let pos: i32 = 0;
      pos = labi_net_tls_buf_append(&cand[0], 4096, pos, repo_root);
      if (pos < 0) {
        i = i + 1;
        continue;
      }
      pos = labi_net_tls_buf_append(&cand[0], 4096, pos, "/compiler/");
      if (pos < 0) {
        i = i + 1;
        continue;
      }
      pos = labi_net_tls_buf_append(&cand[0], 4096, pos, name);
      if (pos < 0) {
        i = i + 1;
        continue;
      }
      let ax2: i32 = 0;
      unsafe {
        ax2 = link_abi_path_executable(&cand[0]);
      }
      if (ax2 != 0) {
        let rp2: *u8 = 0 as *u8;
        unsafe {
          rp2 = link_abi_realpath_cap(&cand[0], &xlang_bin[0]);
        }
        if (rp2 == 0 as *u8) {
          let cp2: i32 = labi_net_tls_buf_append(&xlang_bin[0], 4096, 0, &cand[0]);
          if (cp2 < 0) {
            return 0;
          }
        }
        found = 1;
        break;
      }
      i = i + 1;
    }
  }
  if (found == 0) {
    return 0;
  }
  if (xlang_bin[0] == 0) {
    return 0;
  }
  // freestanding host system residual = fork+execvp sh -c; PATH fixed in invoke_cc child too.
  // wave224 G.7: public pure thin link_abi_system (not raw libc system).
  let cmd: u8[768] = [];
  let ok: i32 = labi_formal_std_build_make_cmd(&cmd[0], 768, &xlang_bin[0], repo_root, make_target);
  if (ok == 0) {
    return 0;
  }
  unsafe {
    let _s: i32 = link_abi_system(&cmd[0]);
  }
  let have1: *u8 = 0 as *u8;
  unsafe {
    have1 = asm_link_obj_skip_missing(&abs[0]);
  }
  if (have1 != 0 as *u8) {
    return 1;
  }
  return 0;
}

/**
 * Return 1 iff `rel` is under formal std/ or core/ (plan OP_STD ensure target).
 * Pure prefix check: "std/" (4) or "core/" (5). Null/empty → 0.
 * @param rel *u8 — plan step rel path (e.g. std/vec/vec.o)
 * @return i32 — 1 if formal ensure applies, else 0
 * PLATFORM: SHARED — pure; used by wave191 formal ensure orch.
 */
#[no_mangle]
export function labi_std_rel_is_std_or_core(rel: *u8): i32 {
  if (rel == 0 as *u8) {
    return 0;
  }
  if (rel[0] == 0) {
    return 0;
  }
  // "std/"
  if (rel[0] == 115) {
    if (rel[1] == 116) {
      if (rel[2] == 100) {
        if (rel[3] == 47) {
          return 1;
        }
      }
    }
  }
  // "core/"
  if (rel[0] == 99) {
    if (rel[1] == 111) {
      if (rel[2] == 114) {
        if (rel[3] == 101) {
          if (rel[4] == 47) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

/**
 * Push monofile companions for std/queue/queue.o (sync/atomic/contention/process_argv + glue).
 * Formal queue.o co-defines SyncQueue locals that U std_sync_* / std_atomic_* /
 * sync_queue_contention_smoke_c / process_xlang_*. User.o only U std_queue_* so
 * fk3/fk6 miss. G.7 single body: formal_ensure (exact rel) and on_demand (need_qp)
 * both call this — do not copy the push list a second time.
 * Always push_obj the rel even if ensure != 0 (skip-missing); do not gate on
 * ensure==0 (existing .o after L4 sibling tests must still enter argv).
 * @param link_argv0 *u8 — compiler argv0 / link root; null → no-op
 * @param lib_roots **u8 — -L roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*; may be null
 * @param argv **u8 — ld argv table; null → no-op
 * @param la *i32 — in/out argv length; null → no-op
 * @param max_la i32 — argv capacity
 * @param flags *u8 — ShuAsmLdStdLinkFlags*; may be null; have_sync written if sync.o pushed
 * @return void
 * PLATFORM: SHARED — Darwin ld hard UNDEF; Linux ELF may look green without these.
 * Track-L: #[no_mangle] product short name (on_demand + formal_ensure).
 */
#[no_mangle]
export function labi_std_append_queue_monofile_companions(link_argv0: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flags: *u8): void {
  if (link_argv0 == 0 as *u8) {
    return;
  }
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  let include_root: *u8 = 0 as *u8;
  unsafe {
    include_root = xlang_repo_root_from_argv0(link_argv0);
  }
  if (include_root != 0 as *u8) {
    if (include_root[0] != 0) {
      unsafe {
        let _qs: i32 = xlang_ensure_formal_std_make_o(include_root, "std/sync/sync.o", "../std/sync/sync.o");
        let _qa: i32 = xlang_ensure_formal_std_make_o(include_root, "std/atomic/atomic.o", "../std/atomic/atomic.o");
      }
    }
  }
  let have_sq: i32 = 0;
  unsafe {
    let _ps: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/sync/sync.o", lib_roots, n_lib_roots, bank, argv, la, max_la, &have_sq);
    let _pa: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/atomic/atomic.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    let _eqc: i32 = xlang_ensure_runtime_queue_contention_o(link_argv0);
    let _pqc: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_queue_contention.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    let _epv: i32 = xlang_ensure_runtime_process_argv_o(link_argv0);
    let _ppv: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
  }
  if (have_sq != 0) {
    if (flags != 0 as *u8) {
      let fsq: *i32 = flags as *i32;
      fsq[3] = 1;
    }
    unsafe {
      let _esd: i32 = xlang_ensure_runtime_sync_lock_diag_tls_o(link_argv0);
      let _psd: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_sync_lock_diag_tls.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
      let _eso: i32 = xlang_ensure_runtime_sync_os_o(link_argv0);
      let _pso: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_sync_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    }
  }
  unsafe {
    let _eag: i32 = xlang_ensure_runtime_atomic_glue_o(link_argv0);
    let _pag: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
  }
}

/**
 * Push std.test monofile C-dual companions onto the ld argv.
 * Formal test.o UNDEFs test_call_i32_void_c / env_getenv_c / time_now_monotonic_ns_c
 * even when user.o only names std_test_expect* (≡ queue monofile class).
 * Authority lives in this TU so seed-phase1 mega runtime_link_abi.o (includes
 * this file) defines the symbol. L8c labi_od_push_test_monofile_companions is
 * a zero-logic trampoline to this helper.
 * Always push_obj after ensure (queue contract); skip_missing no-ops a miss.
 * @param link_argv0 *u8 — compiler argv0 / link root; null → no-op
 * @param lib_roots **u8 — -L roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*; may be null
 * @param argv **u8 — ld argv table; null → no-op
 * @param la *i32 — in/out argv length; null → no-op
 * @param max_la i32 — argv capacity
 * @return void
 * PLATFORM: SHARED — Darwin ld hard UNDEF; Linux ELF may look green without these.
 * Track-L: #[no_mangle] product short name (on_demand + formal_ensure).
 */
#[no_mangle]
export function labi_std_append_test_monofile_companions(link_argv0: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (link_argv0 == 0 as *u8) {
    return;
  }
  let ab: *u8 = argv as *u8;
  if (ab == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  unsafe {
    let _et: i32 = xlang_ensure_runtime_test_fn_invoke_o(link_argv0);
    let _pt: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_test_fn_invoke.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    let _ee: i32 = xlang_ensure_runtime_env_os_o(link_argv0);
    let _pe: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_env_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
    let _eto: i32 = xlang_ensure_runtime_time_os_o(link_argv0);
    let _pto: i32 = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
  }
}

/**
 * After OP_STD gate opens and user_o is set: ensure formal std|core .o exists
 * (L4 wipe restores via Makefile) and push companion .o when rel needs them.
 * Pure orch:
 *   1) reject null/non-std-core rel
 *   2) Cap residual xlang_repo_root_from_argv0 → pure make_tgt="../"+rel
 *   3) peer pure xlang_ensure_formal_std_make_o(root, rel, make_tgt)
 *   4) companions (exact rel match ≡ mega strstr on plan exact paths):
 *        vec/set/map OR just-ensured rel U std_heap_* → ensure+push heap.o + core/mem/mem.o
 *        env.o → ensure+push runtime_env_os.o
 *        random.o → ensure+push runtime_random_fill.o
 *        time.o → ensure+push runtime_time_os.o
 *        test.o → labi_std_append_test_monofile_companions (fn_invoke / env_os / time_os)
 * Does NOT push `rel` itself (caller still does link_abi_asm_ld_push_obj for the plan step).
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param rel *u8 — plan OP_STD rel (std/... or core/...)
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank* (opaque; path bank for durable argv strings)
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * Cap residual: xlang_repo_root_from_argv0; ensure_runtime_{env_os,random_fill,time_os}_o
 *   + *_o_path; peer pure formal_std_make + link_abi_asm_ld_push_obj.
 * Why (wave191): hybrid still had formal ensure+companions always-mega inline in
 *   append_std_objs_for_user OP_STD (soft residual after wave188 formal_std_make pure
 *   and wave190 fk gates pure).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2; shell make inside formal_std_make Cap residual.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_formal_ensure_for_rel(link_argv0: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (link_argv0 == 0 as *u8) {
    return;
  }
  if (rel == 0 as *u8) {
    return;
  }
  if (rel[0] == 0) {
    return;
  }
  let is_sc: i32 = labi_std_rel_is_std_or_core(rel);
  if (is_sc == 0) {
    return;
  }
  let include_root: *u8 = 0 as *u8;
  unsafe {
    include_root = xlang_repo_root_from_argv0(link_argv0);
  }
  if (include_root == 0 as *u8) {
    return;
  }
  if (include_root[0] == 0) {
    return;
  }
  // make_tgt = "../" + rel (≡ mega snprintf ../%s); cap 4096 ≡ PATH_MAX product hosts.
  let make_tgt: u8[4096] = [];
  let pos: i32 = 0;
  pos = labi_net_tls_buf_append(&make_tgt[0], 4096, pos, "../");
  if (pos < 0) {
    return;
  }
  pos = labi_net_tls_buf_append(&make_tgt[0], 4096, pos, rel);
  if (pos < 0) {
    return;
  }
  // Ensure the formal .o for this plan step (L4 wipe recovery).
  let _ens: i32 = 0;
  unsafe {
    _ens = xlang_ensure_formal_std_make_o(include_root, rel, &make_tgt[0]);
  }
  // Guard lib_roots / argv null via *u8 cast (wave147+ style).
  let ab: *u8 = argv as *u8;
  let lb: *u8 = lib_roots as *u8;
  // Companion: formal vec/set/map .o carry U std_heap_* / core_mem_*.
  // Exact path match (plan rels are exact; mega used strstr on those exact strings).
  // Also probe the just-ensured formal .o: http.o (and any later std) U
  // std_heap_alloc_usize / std_heap_free_u8_ptr while user.o only U std_http_*.
  // On-demand heap scan of user.o therefore misses; Darwin ld is hard UNDEF
  // (Linux ELF may look green without heap.o). G.7 complete the existing
  // needs_std_heap_api consumer — do not grow a second http-only heap path.
  // PLATFORM: SHARED — L4 wipe + mac run-http residual.
  let need_heap_mem: i32 = 0;
  let eq_vec: i32 = 0;
  let eq_set: i32 = 0;
  let eq_map: i32 = 0;
  unsafe {
    eq_vec = strcmp(rel, "std/vec/vec.o");
    eq_set = strcmp(rel, "std/set/set.o");
    eq_map = strcmp(rel, "std/map/map.o");
  }
  if (eq_vec == 0) {
    need_heap_mem = 1;
  }
  if (eq_set == 0) {
    need_heap_mem = 1;
  }
  if (eq_map == 0) {
    need_heap_mem = 1;
  }
  if (need_heap_mem == 0) {
    let abs_rel: u8[4096] = [];
    let joined: i32 = labi_net_tls_join_repo_rel(&abs_rel[0], 4096, include_root, rel);
    if (joined != 0) {
      let need_rel_heap: i32 = 0;
      unsafe {
        need_rel_heap = link_abi_user_o_needs_std_heap_api(&abs_rel[0]);
      }
      if (need_rel_heap != 0) {
        need_heap_mem = 1;
      }
    }
  }
  if (need_heap_mem != 0) {
    let _h: i32 = 0;
    let _m: i32 = 0;
    unsafe {
      _h = xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
      _m = xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
    }
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _ph: i32 = 0;
        let _pm: i32 = 0;
        unsafe {
          _ph = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/heap/heap.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          _pm = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "core/mem/mem.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
  }
  // Companion: formal env.o U env_*_c lives in runtime_env_os.o.
  let eq_env: i32 = 0;
  unsafe {
    eq_env = strcmp(rel, "std/env/env.o");
  }
  if (eq_env == 0) {
    let er: i32 = 0;
    unsafe {
      er = xlang_ensure_runtime_env_os_o(link_argv0);
    }
    if (er == 0) {
      if (ab != 0 as *u8) {
        if (la != 0 as *i32) {
          let env_p: *u8 = 0 as *u8;
          unsafe {
            env_p = xlang_runtime_env_os_o_path(link_argv0);
          }
          let _pe: i32 = 0;
          unsafe {
            _pe = link_abi_asm_ld_push_obj(env_p, link_argv0, "compiler/runtime_env_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // Companion: formal random.o U random_fill_bytes_c.
  let eq_rnd: i32 = 0;
  unsafe {
    eq_rnd = strcmp(rel, "std/random/random.o");
  }
  if (eq_rnd == 0) {
    let rr: i32 = 0;
    unsafe {
      rr = xlang_ensure_runtime_random_fill_o(link_argv0);
    }
    if (rr == 0) {
      if (ab != 0 as *u8) {
        if (la != 0 as *i32) {
          let rnd_p: *u8 = 0 as *u8;
          unsafe {
            rnd_p = xlang_runtime_random_fill_o_path(link_argv0);
          }
          let _pr: i32 = 0;
          unsafe {
            _pr = link_abi_asm_ld_push_obj(rnd_p, link_argv0, "compiler/runtime_random_fill.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // Companion: formal time.o U time_*_c (mirrors on_demand pair).
  let eq_tm: i32 = 0;
  unsafe {
    eq_tm = strcmp(rel, "std/time/time.o");
  }
  if (eq_tm == 0) {
    let tr: i32 = 0;
    unsafe {
      tr = xlang_ensure_runtime_time_os_o(link_argv0);
    }
    if (tr == 0) {
      if (ab != 0 as *u8) {
        if (la != 0 as *i32) {
          let tm_p: *u8 = 0 as *u8;
          unsafe {
            tm_p = xlang_runtime_time_os_o_path(link_argv0);
          }
          let _pt: i32 = 0;
          unsafe {
            _pt = link_abi_asm_ld_push_obj(tm_p, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // PLATFORM: SHARED — formal datetime.o U time_now_wall_*_c / time_wall_local_offset_min_c
  // (datetime.x now_utc / local_offset) and std_time_sleep_ns / duration_ns (mod.x).
  // User.o for datetime_iana only U std_datetime_timezone_iana so fk0 time needles miss.
  // Companion ≡ time.o → time_os. G.7 complete ensure_for_rel; no second group.
  let eq_dt: i32 = 0;
  unsafe {
    eq_dt = strcmp(rel, "std/datetime/datetime.o");
  }
  if (eq_dt == 0) {
    let _ftm: i32 = 0;
    unsafe {
      _ftm = xlang_ensure_formal_std_make_o(include_root, "std/time/time.o", "../std/time/time.o");
    }
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _ptm: i32 = 0;
        unsafe {
          _ptm = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/time/time.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        let trdt: i32 = 0;
        unsafe {
          trdt = xlang_ensure_runtime_time_os_o(link_argv0);
        }
        if (trdt == 0) {
          let tm_pdt: *u8 = 0 as *u8;
          unsafe {
            tm_pdt = xlang_runtime_time_os_o_path(link_argv0);
          }
          let _ptdt: i32 = 0;
          unsafe {
            _ptdt = link_abi_asm_ld_push_obj(tm_pdt, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // Companion: formal fs.o carries U std_error_* / std_context_* (timeout/ctx IO).
  // User.o typically only U std_fs_* so fk0 error/context user needles miss.
  // context.o then U atomic_*_i32_c + time_now_monotonic_ns_c.
  // G.7 complete authority ≡ net have_net companions + C need_context + vec/heap pattern.
  // PLATFORM: SHARED — pure-asm run-fs residual; dual-end L2.
  // Same companion class for http.o (run-http UNDEF std_error_http_err_* /
  // std_context_*): monofile co-compiles timeout/ctx faces; user only U std_http_*.
  let eq_fs: i32 = 0;
  let eq_http: i32 = 0;
  unsafe {
    eq_fs = strcmp(rel, "std/fs/fs.o");
    eq_http = strcmp(rel, "std/http/http.o");
  }
  if (eq_fs == 0) {
    let _fe: i32 = 0;
    let _fc: i32 = 0;
    unsafe {
      _fe = xlang_ensure_formal_std_make_o(include_root, "std/error/error.o", "../std/error/error.o");
      _fc = xlang_ensure_formal_std_make_o(include_root, "std/context/context.o", "../std/context/context.o");
    }
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _pe: i32 = 0;
        let _pc: i32 = 0;
        unsafe {
          _pe = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/error/error.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          _pc = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/context/context.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        let er_ag: i32 = 0;
        let agp: *u8 = 0 as *u8;
        unsafe {
          er_ag = xlang_ensure_runtime_atomic_glue_o(link_argv0);
          agp = xlang_runtime_atomic_glue_o_path(link_argv0);
        }
        if (er_ag == 0) {
          let _pag: i32 = 0;
          unsafe {
            _pag = link_abi_asm_ld_push_obj(agp, link_argv0, "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
        let er_to: i32 = 0;
        let top: *u8 = 0 as *u8;
        unsafe {
          er_to = xlang_ensure_runtime_time_os_o(link_argv0);
          top = xlang_runtime_time_os_o_path(link_argv0);
        }
        if (er_to == 0) {
          let _pto: i32 = 0;
          unsafe {
            _pto = link_abi_asm_ld_push_obj(top, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  if (eq_http == 0) {
    // PLATFORM: SHARED — pure-asm run-http residual (≡ fs/net error/context companions).
    let _fe_h: i32 = 0;
    let _fc_h: i32 = 0;
    unsafe {
      _fe_h = xlang_ensure_formal_std_make_o(include_root, "std/error/error.o", "../std/error/error.o");
      _fc_h = xlang_ensure_formal_std_make_o(include_root, "std/context/context.o", "../std/context/context.o");
    }
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _pe_h: i32 = 0;
        let _pc_h: i32 = 0;
        unsafe {
          _pe_h = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/error/error.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          _pc_h = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, "std/context/context.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
        let er_ag_h: i32 = 0;
        let agp_h: *u8 = 0 as *u8;
        unsafe {
          er_ag_h = xlang_ensure_runtime_atomic_glue_o(link_argv0);
          agp_h = xlang_runtime_atomic_glue_o_path(link_argv0);
        }
        if (er_ag_h == 0) {
          let _pag_h: i32 = 0;
          unsafe {
            _pag_h = link_abi_asm_ld_push_obj(agp_h, link_argv0, "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
        let er_to_h: i32 = 0;
        let top_h: *u8 = 0 as *u8;
        unsafe {
          er_to_h = xlang_ensure_runtime_time_os_o(link_argv0);
          top_h = xlang_runtime_time_os_o_path(link_argv0);
        }
        if (er_to_h == 0) {
          let _pto_h: i32 = 0;
          unsafe {
            _pto_h = link_abi_asm_ld_push_obj(top_h, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // PLATFORM: SHARED — queue.o monofile companions (G.7 single helper).
  let eq_queue: i32 = 0;
  unsafe {
    eq_queue = strcmp(rel, "std/queue/queue.o");
  }
  if (eq_queue == 0) {
    labi_std_append_queue_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *u8);
  }
  // PLATFORM: SHARED — test.o monofile companions (G.7 single helper in this TU).
  // User.o only U std_test_*; formal test.o U test_call / env_getenv / time_now.
  // C path need_test used to skip companions when test.o was already on argv.
  let eq_test: i32 = 0;
  unsafe {
    eq_test = strcmp(rel, "std/test/test.o");
  }
  if (eq_test == 0) {
    labi_std_append_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
  }
  // PLATFORM: SHARED — direct OP_STD context.o (user U std_context_* / STD-091).
  // context.o U atomic_*_i32_c + time_now_monotonic_ns_c. C path need_context already
  // pairs them; pure-asm plan only pushed context.o until companions added here.
  // G.7 complete authority ≡ invoke_cc need_context companions (atomic_glue + time_os).
  let eq_ctx: i32 = 0;
  unsafe {
    eq_ctx = strcmp(rel, "std/context/context.o");
  }
  if (eq_ctx == 0) {
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let er_ag_c: i32 = 0;
        let agp_c: *u8 = 0 as *u8;
        unsafe {
          er_ag_c = xlang_ensure_runtime_atomic_glue_o(link_argv0);
          agp_c = xlang_runtime_atomic_glue_o_path(link_argv0);
        }
        if (er_ag_c == 0) {
          let _pag_c: i32 = 0;
          unsafe {
            _pag_c = link_abi_asm_ld_push_obj(agp_c, link_argv0, "compiler/runtime_atomic_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
        let er_to_c: i32 = 0;
        let top_c: *u8 = 0 as *u8;
        unsafe {
          er_to_c = xlang_ensure_runtime_time_os_o(link_argv0);
          top_c = xlang_runtime_time_os_o_path(link_argv0);
        }
        if (er_to_c == 0) {
          let _pto_c: i32 = 0;
          unsafe {
            _pto_c = link_abi_asm_ld_push_obj(top_c, link_argv0, "compiler/runtime_time_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
          }
        }
      }
    }
  }
  // keep Cap residual peer args live for typeck (bank/lib_roots used only via push_obj).
  if (lb == 0 as *u8) {
    if (_ens != 0) {
      return;
    }
  }
}

/**
 * Helper: if have!=0 and ensure returns 0, push glue_rel via primary path.
 * Mirrors link_abi_asm_ld_push_glue_after_std without a C function-pointer ensure_fn
 * (G.7: same gate semantics — have gate + ensure success + peer push_obj).
 * @param have i32 — non-zero when owning formal std .o is already on ld argv
 * @param er i32 — ensure_* return (0 success; non-zero skip push)
 * @param primary *u8 — preferred glue .o path (may be null; push_obj resolves via rel)
 * @param link_argv0 *u8 — compiler argv0
 * @param glue_rel *u8 — relative glue path under project/lib roots
 * @param lib_roots **u8 — -L style roots
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * PLATFORM: SHARED — pure thin; used only by labi_std_append_glue_for_op.
 * Track-L: #[no_mangle] keeps short surface name (wave262; not module_prefix double name).
 */
#[no_mangle]
function labi_std_glue_push_if(have: i32, er: i32, primary: *u8, link_argv0: *u8, glue_rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (have == 0) {
    return;
  }
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

/**
 * Append_std plan OP_GLUE_* leaf: when `have` is set, ensure runtime glue .o and push
 * onto ld argv. Pure orch over plan op codes (≡ mega LABI_STD_OP_GLUE_*):
 *   10 THREAD, 11 SYNC_PAIR, 12 CRYPTO_PAIR, 13 LOG, 14 ATOMIC, 15 CHANNEL,
 *   16 BACKTRACE, 17 MATH, 18 SQLITE, 19 DYNLIB, 20 HTTP.
 * Pairs (sync/crypto): two glue pushes when have (lock_diag+sync_os / ed25519+crypto_inc).
 * Single leaves: use plan `rel` when non-null/non-empty else default compiler/runtime_*.o.
 * @param op i32 — LABI_STD_OP_GLUE_* (10..20); other → no-op
 * @param have i32 — flag set by prior OP_STD step (local or ShuAsmLdStdLinkFlags)
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param rel *u8 — plan step rel (may be null; singles fall back to default path)
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * Cap residual: ensure_runtime_*_glue / *_os / math_libm + peer path pure + push_obj.
 * Why (wave192): hybrid still had all OP_GLUE_* cases always-mega inline after wave191
 *   formal ensure pure (soft residual append_std plan glue/flag).
 * G.7: compose existing ensure+path+push (same semantics as push_glue_after_std); no
 *   second gate table; no C ensure_fn pointer from .x.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_glue_for_op(op: i32, have: i32, link_argv0: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (link_argv0 == 0 as *u8) {
    return;
  }
  // Resolve effective rel for single-glue leaves (mega: rel ? rel : default).
  let use_rel: *u8 = rel;
  let rel_ok: i32 = 0;
  if (rel != 0 as *u8) {
    if (rel[0] != 0) {
      rel_ok = 1;
    }
  }
  // ≡ push_glue_after_std: have gate before any ensure (do not build unused glue).
  if (have == 0) {
    return;
  }
  // op 10: THREAD glue
  if (op == 10) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_thread_glue.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_thread_glue_o(link_argv0);
      p = xlang_runtime_thread_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 11: SYNC_PAIR — lock_diag_tls + sync_os (mega hardcodes both rels)
  if (op == 11) {
    let er1: i32 = 0;
    let p1: *u8 = 0 as *u8;
    let er2: i32 = 0;
    let p2: *u8 = 0 as *u8;
    unsafe {
      er1 = xlang_ensure_runtime_sync_lock_diag_tls_o(link_argv0);
      p1 = xlang_runtime_sync_lock_diag_tls_o_path(link_argv0);
      er2 = xlang_ensure_runtime_sync_os_o(link_argv0);
      p2 = xlang_runtime_sync_os_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er1, p1, link_argv0, "compiler/runtime_sync_lock_diag_tls.o", lib_roots, n_lib_roots, bank, argv, la, max_la);
    labi_std_glue_push_if(1, er2, p2, link_argv0, "compiler/runtime_sync_os.o", lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 12: CRYPTO_PAIR — ed25519_ref10 + crypto_inc
  if (op == 12) {
    let er1: i32 = 0;
    let p1: *u8 = 0 as *u8;
    let er2: i32 = 0;
    let p2: *u8 = 0 as *u8;
    unsafe {
      er1 = xlang_ensure_runtime_ed25519_ref10_glue_o(link_argv0);
      p1 = xlang_runtime_ed25519_ref10_glue_o_path(link_argv0);
      er2 = xlang_ensure_runtime_crypto_inc_glue_o(link_argv0);
      p2 = xlang_runtime_crypto_inc_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er1, p1, link_argv0, "compiler/runtime_ed25519_ref10_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la);
    labi_std_glue_push_if(1, er2, p2, link_argv0, "compiler/runtime_crypto_inc_glue.o", lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 13: LOG
  if (op == 13) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_log_os.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_log_os_o(link_argv0);
      p = xlang_runtime_log_os_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 14: ATOMIC
  if (op == 14) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_atomic_glue.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_atomic_glue_o(link_argv0);
      p = xlang_runtime_atomic_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 15: CHANNEL
  if (op == 15) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_channel_glue.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_channel_glue_o(link_argv0);
      p = xlang_runtime_channel_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 16: BACKTRACE
  if (op == 16) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_backtrace_platform.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_backtrace_platform_o(link_argv0);
      p = xlang_runtime_backtrace_platform_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 17: MATH
  if (op == 17) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_math_libm.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_math_libm_o(link_argv0);
      p = xlang_runtime_math_libm_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 18: SQLITE
  if (op == 18) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_sqlite_glue.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_sqlite_glue_o(link_argv0);
      p = xlang_runtime_sqlite_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 19: DYNLIB
  if (op == 19) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_dynlib_os.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_dynlib_os_o(link_argv0);
      p = xlang_runtime_dynlib_os_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
  // op 20: HTTP
  if (op == 20) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_http_glue.o";
    }
    let er: i32 = 0;
    let p: *u8 = 0 as *u8;
    unsafe {
      er = xlang_ensure_runtime_http_glue_o(link_argv0);
      p = xlang_runtime_http_glue_o_path(link_argv0);
    }
    labi_std_glue_push_if(1, er, p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
    return;
  }
}

/**
 * Append_std plan primary leaf: IO_STUBS / PRIMARY_PANIC / TIME_OS / RANDOM_FILL / ENV_OS.
 * Pure orch over plan op codes (≡ mega LABI_STD_OP_*):
 *   2 IO_STUBS — push runtime_asm_io_stubs.o (no gate; always on plan)
 *   3 PRIMARY_PANIC — push runtime_panic.o (no gate)
 *   4 PRIMARY_TIME_OS — gate labi_user_needs_runtime_time_os then ensure+push time_os
 *   5 PRIMARY_RANDOM_FILL — gate needs_random_fill then ensure+push random_fill
 *   6 PRIMARY_ENV_OS — gate needs_env_os then ensure+push env_os
 * Gated leaves ignore ensure return (≡ mega `(void)ensure` then always push_obj).
 * @param op i32 — 2..6; other → no-op
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param user_o *u8 — user .o for needs gates; null/empty → needs returns 1
 * @param rel *u8 — plan step rel (may be null; fall back to default compiler/runtime_*.o)
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * Cap residual: labi_user_needs_runtime_* (undef_sym tables) + ensure_runtime_* + path + push_obj.
 * Why (wave193): hybrid still had IO_STUBS + PRIMARY_* cases always-mega inline after wave192 glue.
 * G.7: compose existing needs+ensure+path+push; no second gate table.
 * wave253: PRIMARY_PANIC also ensure+push runtime_link_abi_user_env.o companion face.
 * wave259: surface re-pin PRIMARY_PANIC user_env companion (≡ this .x / cold; close lag).
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_primary_for_op(op: i32, link_argv0: *u8, user_o: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (link_argv0 == 0 as *u8) {
    return;
  }
  let use_rel: *u8 = rel;
  let rel_ok: i32 = 0;
  if (rel != 0 as *u8) {
    if (rel[0] != 0) {
      rel_ok = 1;
    }
  }
  // op 2: IO_STUBS — always push (plan first leaf; nostdlib/minimal also uses same path)
  if (op == 2) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_asm_io_stubs.o";
    }
    let p: *u8 = 0 as *u8;
    unsafe {
      p = xlang_runtime_asm_io_stubs_o_path(link_argv0);
    }
    let ab: *u8 = argv as *u8;
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _p: i32 = 0;
        unsafe {
          _p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    return;
  }
  // op 3: PRIMARY_PANIC — always push (no ensure in plan leaf; prepare may ensure earlier)
  if (op == 3) {
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_panic.o";
    }
    let p: *u8 = 0 as *u8;
    unsafe {
      p = xlang_runtime_panic_o_path(link_argv0);
    }
    let ab: *u8 = argv as *u8;
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _p: i32 = 0;
        unsafe {
          _p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    // wave253: companion user-domain face for residual declare-only / Linux .s panic.
    unsafe {
      let _e: i32 = 0;
      _e = xlang_ensure_runtime_link_abi_user_env_o(link_argv0);
    }
    let ue_p: *u8 = 0 as *u8;
    unsafe {
      ue_p = xlang_runtime_link_abi_user_env_o_path(link_argv0);
    }
    let ab2: *u8 = argv as *u8;
    if (ab2 != 0 as *u8) {
      if (la != 0 as *i32) {
        let _ue: i32 = 0;
        unsafe {
          _ue = link_abi_asm_ld_push_obj(ue_p, link_argv0, "compiler/runtime_link_abi_user_env.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    return;
  }
  // op 4: PRIMARY_TIME_OS — gate + ensure + push
  if (op == 4) {
    let need: i32 = 0;
    unsafe {
      need = labi_user_needs_runtime_time_os(user_o);
    }
    if (need == 0) {
      return;
    }
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_time_os.o";
    }
    let p: *u8 = 0 as *u8;
    let _e: i32 = 0;
    unsafe {
      _e = xlang_ensure_runtime_time_os_o(link_argv0);
      p = xlang_runtime_time_os_o_path(link_argv0);
    }
    let ab: *u8 = argv as *u8;
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _p: i32 = 0;
        unsafe {
          _p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    return;
  }
  // op 5: PRIMARY_RANDOM_FILL
  if (op == 5) {
    let need: i32 = 0;
    unsafe {
      need = labi_user_needs_runtime_random_fill(user_o);
    }
    if (need == 0) {
      return;
    }
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_random_fill.o";
    }
    let p: *u8 = 0 as *u8;
    let _e: i32 = 0;
    unsafe {
      _e = xlang_ensure_runtime_random_fill_o(link_argv0);
      p = xlang_runtime_random_fill_o_path(link_argv0);
    }
    let ab: *u8 = argv as *u8;
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _p: i32 = 0;
        unsafe {
          _p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    return;
  }
  // op 6: PRIMARY_ENV_OS
  if (op == 6) {
    let need: i32 = 0;
    unsafe {
      need = labi_user_needs_runtime_env_os(user_o);
    }
    if (need == 0) {
      return;
    }
    if (rel_ok == 0) {
      use_rel = "compiler/runtime_env_os.o";
    }
    let p: *u8 = 0 as *u8;
    let _e: i32 = 0;
    unsafe {
      _e = xlang_ensure_runtime_env_os_o(link_argv0);
      p = xlang_runtime_env_os_o_path(link_argv0);
    }
    let ab: *u8 = argv as *u8;
    if (ab != 0 as *u8) {
      if (la != 0 as *i32) {
        let _p: i32 = 0;
        unsafe {
          _p = link_abi_asm_ld_push_obj(p, link_argv0, use_rel, lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
        }
      }
    }
    return;
  }
}

/**
 * When heavy std/runtime leaves already on ld argv but process.o was not pushed,
 * ensure+push runtime_process_argv.o so weak process_arg*_c resolve to process_xlang_*.
 * Pure orch: need gate → Cap residual ensure → path → peer push_obj.
 * Caller computes need as (have_atomic|have_log|…|flags.have_*) && !have_process
 * (must NOT dual-link with process.o — have_process=1 suppresses this).
 * @param need i32 — non-zero to run complement; 0 → no-op
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * Cap residual: xlang_ensure_runtime_process_argv_o + peer path + push_obj.
 * Why (wave193): hybrid still had process_argv complement always-mega inline after plan loop.
 * G.7: complete existing C-backend process_argv path; no second plan table.
 * Note: export signature must stay single-line.
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_process_argv_if(need: i32, link_argv0: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  if (need == 0) {
    return;
  }
  if (link_argv0 == 0 as *u8) {
    return;
  }
  let p: *u8 = 0 as *u8;
  let _e: i32 = 0;
  unsafe {
    _e = xlang_ensure_runtime_process_argv_o(link_argv0);
    p = xlang_runtime_process_argv_o_path(link_argv0);
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
    _p = link_abi_asm_ld_push_obj(p, link_argv0, "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, 0 as *i32);
  }
  if (_p == 0) {
    return;
  }
}

/**
 * Append_std plan TASK_SPECIAL leaf (op 30): when user needs std.task, ensure+push
 * task.o + async scheduler.o + runtime_scheduler_glue.o onto ld argv.
 * Pure orch (≡ mega LABI_STD_OP_TASK_SPECIAL):
 *   1) gate labi_user_needs_std_task when user_o non-empty (null/empty → always open)
 *   2) task_rel = plan rel if non-null/non-empty else "std/task/task.o"
 *   3) when user_o set: Cap residual repo_root + peer formal_std_make (L4 wipe recovery)
 *   4) resolve task path: Cap residual skip_missing(rel_o_path) → peer try_under_lib_roots
 *   5) peer pure argv_push_stable(task)
 *   6) peer pure scheduler_o_for_task_link(task) with fallbacks:
 *        skip_missing(std_async_scheduler_o_path) → try_under "std/async/scheduler.o"
 *   7) push_stable(scheduler) then Cap residual ensure_scheduler_glue + resolve + push_stable
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param user_o *u8 — user .o for needs gate; null/empty → skip gate (hard-link style)
 * @param rel *u8 — plan step rel (may be null; default std/task/task.o)
 * @param lib_roots **u8 — -L style roots for try_under / path bank
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * Cap residual: xlang_repo_root_from_argv0 + formal_std_make + skip_missing + rel_o_path +
 *   ensure_runtime_scheduler_glue_o + path peers; peer pure scheduler rewrite / push_stable /
 *   try_under / needs_std_task.
 * Why (wave194): hybrid still had TASK_SPECIAL always-mega inline after wave193 primary.
 * G.7: compose existing needs/path/ensure/push peers; no second task link table.
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_task_special(link_argv0: *u8, user_o: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32): void {
  // Gate: only when user_o is a real path (≡ mega if user_o && user_o[0] && !needs break).
  if (user_o != 0 as *u8) {
    if (user_o[0] != 0) {
      let need: i32 = 0;
      unsafe {
        need = labi_user_needs_std_task(user_o);
      }
      if (need == 0) {
        return;
      }
    }
  }
  if (link_argv0 == 0 as *u8) {
    return;
  }
  if (la == 0 as *i32) {
    return;
  }
  // Capacity gate (≡ mega if (p && la && *la < max_la - 1) before any push).
  if (la[0] >= max_la - 1) {
    return;
  }
  // task_rel = rel ? rel : "std/task/task.o"
  let task_rel: *u8 = rel;
  let rel_ok: i32 = 0;
  if (rel != 0 as *u8) {
    if (rel[0] != 0) {
      rel_ok = 1;
    }
  }
  if (rel_ok == 0) {
    task_rel = "std/task/task.o";
  }
  // L4 wipe: formal ensure when user actually needs task (G.7 complete ensure authority).
  if (user_o != 0 as *u8) {
    if (user_o[0] != 0) {
      let include_root: *u8 = 0 as *u8;
      unsafe {
        include_root = xlang_repo_root_from_argv0(link_argv0);
      }
      if (include_root != 0 as *u8) {
        if (include_root[0] != 0) {
          let make_tgt: u8[4096] = [];
          let pos: i32 = 0;
          pos = labi_net_tls_buf_append(&make_tgt[0], 4096, pos, "../");
          if (pos >= 0) {
            pos = labi_net_tls_buf_append(&make_tgt[0], 4096, pos, task_rel);
          }
          if (pos >= 0) {
            let _ens: i32 = 0;
            unsafe {
              _ens = xlang_ensure_formal_std_make_o(include_root, task_rel, &make_tgt[0]);
            }
            if (_ens == 0) {
              // keep ensure result live for typeck; failure still falls through to resolve.
            }
          }
        }
      }
    }
  }
  // Resolve task.o: Cap residual skip(rel_o_path) → peer try_under when bank present.
  let p: *u8 = 0 as *u8;
  let relp: *u8 = 0 as *u8;
  unsafe {
    relp = xlang_rel_o_path_from_argv0(link_argv0, task_rel);
  }
  if (relp != 0 as *u8) {
    unsafe {
      p = asm_link_obj_skip_missing(relp);
    }
  }
  if (p == 0 as *u8) {
    if (bank != 0 as *u8) {
      unsafe {
        p = xlang_asm_ld_try_under_lib_roots(task_rel, lib_roots, n_lib_roots, bank);
      }
    }
  }
  if (p == 0 as *u8) {
    return;
  }
  // Push task.o (bank + dedup + append; soft-keep on bank_push fail ≡ mega).
  unsafe {
    link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
  }
  // Derive scheduler.o from task path; fallbacks ≡ mega ladder.
  let sched: *u8 = 0 as *u8;
  unsafe {
    sched = scheduler_o_for_task_link(p, 0 as *u8);
  }
  if (sched == 0 as *u8) {
    let sp: *u8 = 0 as *u8;
    unsafe {
      sp = xlang_std_async_scheduler_o_path(link_argv0);
    }
    if (sp != 0 as *u8) {
      unsafe {
        sched = asm_link_obj_skip_missing(sp);
      }
    }
  }
  if (sched == 0 as *u8) {
    if (bank != 0 as *u8) {
      unsafe {
        sched = xlang_asm_ld_try_under_lib_roots("std/async/scheduler.o", lib_roots, n_lib_roots, bank);
      }
    }
  }
  if (sched == 0 as *u8) {
    return;
  }
  unsafe {
    link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, sched);
  }
  // runtime_scheduler_glue.o (only when scheduler was resolved; ≡ mega nested under sched).
  let _eg: i32 = 0;
  unsafe {
    _eg = xlang_ensure_runtime_scheduler_glue_o(link_argv0);
  }
  let rsg: *u8 = 0 as *u8;
  let gp: *u8 = 0 as *u8;
  unsafe {
    gp = xlang_runtime_scheduler_glue_o_path(link_argv0);
  }
  if (gp != 0 as *u8) {
    unsafe {
      rsg = asm_link_obj_skip_missing(gp);
    }
  }
  if (rsg == 0 as *u8) {
    if (bank != 0 as *u8) {
      unsafe {
        rsg = xlang_asm_ld_try_under_lib_roots("compiler/runtime_scheduler_glue.o", lib_roots, n_lib_roots, bank);
      }
    }
  }
  if (rsg != 0 as *u8) {
    unsafe {
      link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, rsg);
    }
  }
  // keep Cap residual peer args live for typeck (lib_roots used via try_under only).
  if (_eg != 0) {
    return;
  }
}

/**
 * Resolve OP_STD flag_out slot for plan flag_kind `fk`.
 * Maps fk → either a field of ShuAsmLdStdLinkFlags (LP64 i32 layout) or a slot in
 * caller-owned `local_have[6]` (locals that are not in the public flags struct).
 * @param fk i32 — plan flag_kind (0..13); 0 and unknown → null
 * @param flags *u8 — ShuAsmLdStdLinkFlags* as opaque bytes; null skips flags slots
 * @param local_have *i32 — array of 6 ints: [0]process [1]crypto [2]log [3]atomic
 *   [4]backtrace [5]http; null skips local slots
 * @return *i32 — pointer written by push_obj on success; null when no flag to set
 * Flag layout (PLATFORM: SHARED LP64; ≡ runtime_link_abi.h ShuAsmLdStdLinkFlags):
 *   0=have_io 1=have_net 2=have_thread 3=have_sync 4=have_channel
 *   5=have_math 6=have_compress 7=have_dynlib 8=have_sqlite
 *   9=have_elf 10=have_libc_heap 11=have_fs
 * Map (≡ mega OP_STD flag_out if/else):
 *   fk1→local[0] process; fk2→flags[2] thread; fk3→flags[3] sync;
 *   fk4→local[1] crypto; fk5→local[2] log; fk6→local[3] atomic;
 *   fk7→flags[4] channel; fk8→local[4] backtrace; fk9→flags[5] math;
 *   fk10→flags[8] sqlite; fk11→flags[9] elf; fk12→flags[7] dynlib;
 *   fk13→local[5] http.
 * Why (wave195): hybrid still had fk→flag_out pointer map always-mega inline.
 * PLATFORM: SHARED pure; dual-end L2.
 * Track-L: not exported (internal helper for labi_std_append_op_std only).
 * Track-L: #[no_mangle] keeps short surface name (wave262; not module_prefix double name).
 */
#[no_mangle]
function labi_std_op_std_flag_out(fk: i32, flags: *u8, local_have: *i32): *i32 {
  // Locals bank (process/crypto/log/atomic/backtrace/http).
  if (local_have != 0 as *i32) {
    if (fk == 1) {
      return &local_have[0];
    }
    if (fk == 4) {
      return &local_have[1];
    }
    if (fk == 5) {
      return &local_have[2];
    }
    if (fk == 6) {
      return &local_have[3];
    }
    if (fk == 8) {
      return &local_have[4];
    }
    if (fk == 13) {
      return &local_have[5];
    }
  }
  // ShuAsmLdStdLinkFlags fields used by glue + tail -l*.
  if (flags != 0 as *u8) {
    let f: *i32 = flags as *i32;
    if (fk == 2) {
      return &f[2];
    }
    if (fk == 3) {
      return &f[3];
    }
    if (fk == 7) {
      return &f[4];
    }
    if (fk == 9) {
      return &f[5];
    }
    if (fk == 10) {
      return &f[8];
    }
    if (fk == 11) {
      return &f[9];
    }
    if (fk == 12) {
      return &f[7];
    }
  }
  return 0 as *i32;
}

/**
 * append_std plan OP_STD leaf: gate by fk + formal ensure + push rel with flag_out.
 * Pure orch composes existing peers (G.7 no second gate/ensure/push path):
 *   1) pure fk→flag_out map (labi_std_op_std_flag_out)
 *   2) peer pure labi_std_fk0_user_needs_rel (fk==0) / labi_std_fk_user_needs (fk 1–13)
 *   3) peer pure labi_std_append_formal_ensure_for_rel when user_o set
 *   4) peer pure link_abi_asm_ld_push_obj(NULL, …, flag_out)
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param user_o *u8 — user main .o path; null/empty → hard-link style (fk≥1 always; fk0 still gates)
 * @param rel *u8 — plan OP_STD rel (std/... or core/...); null/empty → no-op
 * @param fk i32 — plan flag_kind 0..13
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * @param flags *u8 — ShuAsmLdStdLinkFlags* (opaque); may be null
 * @param local_have *i32 — caller array of 6 have_* locals (see labi_std_op_std_flag_out)
 * Cap residual: undef_sym inside fk gate peers; formal ensure shell make Cap residual.
 * Why (wave195): hybrid still had OP_STD flag map + gate + ensure + push always-mega inline
 *   after wave191 formal ensure pure and wave190 fk gates pure (soft residual "flag 映射").
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] keeps surface short name for append_std call sites.
 */
#[no_mangle]
export function labi_std_append_op_std(link_argv0: *u8, user_o: *u8, rel: *u8, fk: i32, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flags: *u8, local_have: *i32): void {
  // Resolve flag_out before gate (≡ mega: map then maybe break; push only when rel ok).
  let flag_out: *i32 = labi_std_op_std_flag_out(fk, flags, local_have);
  // Gate: when user_o is a real path, fk0 uses rel×sym; fk 1–13 use gate table.
  let user_ok: i32 = 0;
  if (user_o != 0 as *u8) {
    if (user_o[0] != 0) {
      user_ok = 1;
    }
  }
  let rel_ok: i32 = 0;
  if (rel != 0 as *u8) {
    if (rel[0] != 0) {
      rel_ok = 1;
    }
  }
  if (rel_ok != 0) {
    if (user_ok != 0) {
      if (fk == 0) {
        let need0: i32 = 0;
        unsafe {
          need0 = labi_std_fk0_user_needs_rel(user_o, rel);
        }
        if (need0 == 0) {
          return;
        }
      }
      if (fk >= 1) {
        if (fk <= 13) {
          let needk: i32 = 0;
          unsafe {
            needk = labi_std_fk_user_needs(user_o, fk);
          }
          if (needk == 0) {
            return;
          }
        }
      }
    } else {
      // No user filter: fk0 still probes (null user → needs_rel authority; ≡ mega else-if).
      if (fk == 0) {
        let need0b: i32 = 0;
        unsafe {
          need0b = labi_std_fk0_user_needs_rel(user_o, rel);
        }
        if (need0b == 0) {
          return;
        }
      }
    }
  } else {
    // Empty rel: nothing to push (≡ mega if (rel && rel[0]) body skipped).
    return;
  }
  // L4 wipe: formal ensure + companions only when user actually needs this rel.
  if (user_ok != 0) {
    labi_std_append_formal_ensure_for_rel(link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
  }
  // Push plan rel; flag_out set to 1 on successful new argv slot (peer pure push_obj).
  let _push: i32 = 0;
  unsafe {
    _push = link_abi_asm_ld_push_obj(0 as *u8, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la, flag_out);
  }
  if (_push != 0) {
    return;
  }
}

/**
 * Resolve OP_GLUE_* have bit from flags / local_have (≡ mega case LABI_STD_OP_GLUE_*).
 * @param op i32 — LABI_STD_OP_GLUE_* 10..20; other → 0
 * @param flags *u8 — ShuAsmLdStdLinkFlags* opaque; null → flags slots 0
 * @param local_have *i32 — [0]process [1]crypto [2]log [3]atomic [4]backtrace [5]http
 * @return i32 — non-zero when glue leaf should ensure+push
 * Map: 10 thread→f[2]; 11 sync→f[3]; 12 crypto→local[1]; 13 log→local[2];
 *   14 atomic→local[3]; 15 channel→f[4]; 16 backtrace→local[4]; 17 math→f[5];
 *   18 sqlite→f[8]; 19 dynlib→f[7]; 20 http→local[5].
 * PLATFORM: SHARED pure; dual-end L2.
 * Track-L: not exported (internal helper for plan shell only).
 * Track-L: #[no_mangle] keeps short surface name (wave262; not module_prefix double name).
 */
#[no_mangle]
function labi_std_glue_have_for_op(op: i32, flags: *u8, local_have: *i32): i32 {
  if (local_have != 0 as *i32) {
    if (op == 12) {
      return local_have[1];
    }
    if (op == 13) {
      return local_have[2];
    }
    if (op == 14) {
      return local_have[3];
    }
    if (op == 16) {
      return local_have[4];
    }
    if (op == 20) {
      return local_have[5];
    }
  }
  if (flags != 0 as *u8) {
    let f: *i32 = flags as *i32;
    if (op == 10) {
      return f[2];
    }
    if (op == 11) {
      return f[3];
    }
    if (op == 15) {
      return f[4];
    }
    if (op == 17) {
      return f[5];
    }
    if (op == 18) {
      return f[8];
    }
    if (op == 19) {
      return f[7];
    }
  }
  return 0;
}

/**
 * Compute process_argv complement need after plan loop (≡ mega need_pav).
 * True when heavy std is on argv (atomic/log/backtrace locals or flags
 * sync/thread/dynlib/channel/math/elf/sqlite) and process.o was not pushed.
 * @param flags *u8 — ShuAsmLdStdLinkFlags* opaque; null skips flags terms
 * @param local_have *i32 — must be non-null bank of 6 ints (see wave195)
 * @return i32 — 1 when process_argv should be ensured+pushed
 * PLATFORM: SHARED pure; dual-end L2.
 * Track-L: not exported (internal helper for plan shell only).
 * Track-L: #[no_mangle] keeps short surface name (wave262; not module_prefix double name).
 */
#[no_mangle]
function labi_std_need_process_argv(flags: *u8, local_have: *i32): i32 {
  if (local_have == 0 as *i32) {
    return 0;
  }
  // Already have process.o → never dual-link process_argv.
  if (local_have[0] != 0) {
    return 0;
  }
  let heavy: i32 = 0;
  if (local_have[3] != 0) {
    heavy = 1;
  }
  if (local_have[2] != 0) {
    heavy = 1;
  }
  if (local_have[4] != 0) {
    heavy = 1;
  }
  if (flags != 0 as *u8) {
    let f: *i32 = flags as *i32;
    if (f[3] != 0) {
      heavy = 1;
    }
    if (f[2] != 0) {
      heavy = 1;
    }
    if (f[7] != 0) {
      heavy = 1;
    }
    if (f[4] != 0) {
      heavy = 1;
    }
    if (f[5] != 0) {
      heavy = 1;
    }
    if (f[9] != 0) {
      heavy = 1;
    }
    if (f[8] != 0) {
      heavy = 1;
    }
  }
  return heavy;
}

/**
 * Product append_std plan shell: init flags/local_have, walk plan table, dispatch
 * leaf pure orchs (wave190–195), then process_argv complement.
 * Pure orch composes existing peers (G.7 no second plan/gate/ensure path):
 *   1) zero flags + set have_io=1 have_fs=1 (≡ mega memset + defaults)
 *   2) zero local_have[6] bank (process/crypto/log/atomic/backtrace/http)
 *   3) peer pure labi_std_plan_count / labi_std_plan_step_at (L8 table)
 *   4) dispatch op → primary / OP_STD / OP_GLUE_* / TASK_SPECIAL pure leaves
 *   5) peer pure labi_std_append_process_argv_if when heavy without process
 * @param link_argv0 *u8 — effective compiler argv0 / link root
 * @param user_o *u8 — user main .o; null → hard-link style (no user UNDEF filter)
 * @param lib_roots **u8 — -L style roots for push_obj
 * @param n_lib_roots i32 — root count
 * @param bank *u8 — ShuAsmLdPathBank*
 * @param argv **u8 — ld argv table
 * @param la *i32 — in/out argv length
 * @param max_la i32 — argv capacity
 * @param flags *u8 — ShuAsmLdStdLinkFlags* opaque; may be null
 * Cap residual: inside leaf peers (undef_sym / ensure shell make / resolve / path).
 * Why (wave196): hybrid still had plan loop shell always-mega inline after wave190–195
 *   leaf pure (soft residual "plan 循环壳").
 * Note: export signature must stay single-line (multi-line export drops the function).
 * PLATFORM: SHARED orch — dual-end L2.
 * Track-L: #[no_mangle] product short name (mega call sites / old wrapper).
 */
#[no_mangle]
export function xlang_asm_ld_append_std_objs_for_user(link_argv0: *u8, user_o: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flags: *u8): void {
  // local_have bank: [0]process [1]crypto [2]log [3]atomic [4]backtrace [5]http.
  let local_have: i32[6] = [];
  local_have[0] = 0;
  local_have[1] = 0;
  local_have[2] = 0;
  local_have[3] = 0;
  local_have[4] = 0;
  local_have[5] = 0;
  // Flags: zero all 12 LP64 i32 fields then set have_io + have_fs (≡ mega).
  if (flags != 0 as *u8) {
    let f: *i32 = flags as *i32;
    let zi: i32 = 0;
    while (zi < 12) {
      f[zi] = 0;
      zi = zi + 1;
    }
    f[0] = 1;
    f[11] = 1;
  }
  let n_steps: i32 = 0;
  unsafe {
    n_steps = labi_std_plan_count();
  }
  let si: i32 = 0;
  while (si < n_steps) {
    let op: i32 = 0;
    let rel_u: usize = 0;
    let fk: i32 = 0;
    let ok: i32 = 0;
    unsafe {
      ok = labi_std_plan_step_at(si, &op, &rel_u, &fk);
    }
    if (ok != 0) {
      let rel: *u8 = rel_u as *u8;
      // IO_STUBS=2 PRIMARY_PANIC=3 TIME_OS=4 RANDOM_FILL=5 ENV_OS=6 → primary pure.
      if (op == 2) {
        labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
      if (op == 3) {
        labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
      if (op == 4) {
        labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
      if (op == 5) {
        labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
      if (op == 6) {
        labi_std_append_primary_for_op(op, link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
      // OP_STD=1 → wave195 pure leaf.
      if (op == 1) {
        labi_std_append_op_std(link_argv0, user_o, rel, fk, lib_roots, n_lib_roots, bank, argv, la, max_la, flags, &local_have[0]);
      }
      // OP_GLUE_*=10..20 → wave192 pure leaf with have from flags/local.
      if (op >= 10) {
        if (op <= 20) {
          let have: i32 = labi_std_glue_have_for_op(op, flags, &local_have[0]);
          labi_std_append_glue_for_op(op, have, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
        }
      }
      // TASK_SPECIAL=30 → wave194 pure leaf.
      if (op == 30) {
        labi_std_append_task_special(link_argv0, user_o, rel, lib_roots, n_lib_roots, bank, argv, la, max_la);
      }
    }
    si = si + 1;
  }
  // Complement: heavy std without process.o → process_argv (wave193 pure).
  let need_pav: i32 = labi_std_need_process_argv(flags, &local_have[0]);
  labi_std_append_process_argv_if(need_pav, link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
}
