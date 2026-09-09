// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// link_abi L8b on_demand early pure tables; G.9 English; body authoritative.
// wave263: late heavy pure (std_task/fk0/fk_gate/provides/link_needs/on_demand shell)
// lives in labi_ondemand_heavy.x (L8c) — full-module -E silent-parse-skip capacity cliff.
// Hybrid: L8b+L8c PREFER_X_O under XLANG_LABI_ONDEMAND_LIST_FROM_X (rest H=0 marker).
//
// R2 full: simple/kv/arrow/time/queue + rel_* pure tables +
//   wave118 labi_od_net_sym_* + link_abi_user_o_needs_std_net pure orch +
//   wave119 labi_od_set_sym_* + link_abi_user_o_needs_std_set pure orch +
//   wave120 labi_od_map_sym_* + link_abi_user_o_needs_std_map pure orch +
//   wave121 labi_od_queue_api_sym_* + link_abi_user_o_needs_std_queue pure orch
//     (product API; separate from contention labi_od_queue_sym_*) +
//   wave122 labi_od_test_sym_* + link_abi_user_o_needs_std_test pure orch +
//   wave123 labi_od_core_mem_sym_* + link_abi_user_o_needs_core_mem pure orch +
//   wave124 labi_od_core_slice_sym_* + link_abi_user_o_needs_core_slice pure orch +
//   wave125 labi_od_page_mmap_sym_* + link_abi_user_o_needs_std_heap_page_mmap pure orch +
//   wave126 labi_od_sys_linux_sym_* + link_abi_user_o_needs_std_sys_linux pure orch +
//   wave127 labi_od_sys_sym_* + link_abi_user_o_needs_std_sys pure orch +
//   wave128 labi_od_heap_api_sym_* + link_abi_user_o_needs_std_heap_api pure orch +
//   wave129 labi_od_heap_user_sym_* + link_abi_user_o_needs_heap_user_syms pure orch +
//   wave130 labi_od_async_scheduler_sym_* + link_abi_user_o_needs_async_scheduler pure orch +
//   wave131 link_abi_obj_needs_{zlib,zstd,brotli} + link_abi_user_o_needs_compress_libs pure orch
//     (marker + UNDEF/prefix tables; Cap residual exports_marker + has_undef_sym) +
//   wave132 labi_user_needs_runtime_{time_os,random_fill,env_os} pure orch
//     (PRIMARY OS bulk gates; null/empty user_o → 1 legacy hard-link) +
//   wave133 labi_user_needs_runtime_process_argv pure orch (9 needles; single-leaf) +
//   wave134 labi_user_needs_std_task pure orch (29 needles; TASK_SPECIAL bulk gate).
//   wave135 labi_std_fk0_user_needs_rel pure orch (16 rel × 106 exact UNDEF; Cap strstr).
//   wave140 labi_od_provides_{core_mem,std_heap}_sym_* + link_abi_user_o_provides_* pure orch
//     (defined-sym tables; Cap residual has_defined_sym; skip hard-link mem.o/heap.o).
//   wave145 link_abi_link_needs_{heap_user_c,std_heap_import} pure orch
//     (aggregate: user_o + ld argv .o scan via pure needs_* + ld_argv_entry_is_obj;
//      Cap residual: none new — reuses pure path_pure is_obj + L8b needs tables).
//   wave190 labi_std_fk_gate_sym_* + labi_std_fk_user_needs pure orch
//     (fk 1–13 plan gates; Cap residual undef_sym; G.7 complete wave135 fk0 sibling).
//   wave197 xlang_asm_ld_append_on_demand_user_objs pure orch
//     (product on_demand shell: pure needs/provides + pure push/path peers;
//      Cap residual ensure/skip/path + freestanding_get + undef_sym).
//   wave210 link_abi_obj_has_undef_sym pure thin orch
//     (null/empty gates; Cap residual link_abi_obj_has_undef_sym_impl =
//      UNDEF-cache substring, sibling of needs_undef mmap).
//   wave211 link_abi_obj_exports_marker pure thin orch
//     (null/empty gates; Cap residual link_abi_obj_exports_marker_impl =
//      all-names cache substring; markers are d/s/b, not T/t).
//   wave212 xlang_link_obj_needs_undef_sym pure thin orch
//     (null/empty gates; Cap residual xlang_link_obj_needs_undef_sym_impl = nm/popen + ELF).
//   wave213 xlang_link_obj_has_defined_sym pure thin orch
//     (null/empty gates; Cap residual xlang_link_obj_has_defined_sym_impl =
//      Mach-O/ELF T/t scan or one nm; per-path cache sibling of UNDEF).
// Cap residual: ensure/skip/path Cap inside shell peers; needs_undef_impl /
//   has_undef_impl / exports_marker_impl / has_defined_impl Cap
//   (wave210–213: one-slot UNDEF + T/t + all-names mmap; no per-probe nm).
// PLATFORM: SHARED — no asm co-emit of option/result/debug (Ubuntu hang); link formal .o only.
// Simple groups: string=0 core_types=1 encoding=2 base64=3 csv=4 schema=5
// core_option=6 core_result=7 core_debug=8 core_slice=9 core_builtin=10 std_ffi=11.
// Formal core/*/*.o; g1 rel is core/types/types.o; g9 rel is core/slice/mod.o (API, not glue).
// g9: length.x needs core_slice_len_i32/get_* from mod.x; glue remains core/slice/slice.o.
// g11: pure-asm import METHOD mangle → std_ffi_*; formal std/ffi/ffi.o (mod.x + ffi.x).

/**
 * Cap residual (wave212): exact UNDEF probe body (one-slot cache + in-process scan).
 * Pure orch owns null/empty gates; _impl is always mega.
 * @param user_o *u8 — path to .o (caller already rejected null/empty)
 * @param sym *u8 — exact bare symbol name, no leading underscore (caller rejected null/empty)
 * @return i32 — 1 if user.o has UNDEF for sym, else 0
 * PLATFORM: SHARED orch residual; LINUX ELF / DARWIN Mach-O in-process; nm -u once fallback
 */
export extern "C" function xlang_link_obj_needs_undef_sym_impl(user_o: *u8, sym: *u8): i32;

/**
 * Return 1 iff user.o needs (UNDEF) the given exact symbol; null/empty → 0 without residual.
 * @param user_o *u8 — path to user .o; null/empty rejected at pure gate
 * @param sym *u8 — exact bare symbol name; null/empty rejected at pure gate
 * @return i32 — 1 if UNDEF hit, else 0
 * Pure orch: ≡ mega null/empty gates before Cap residual UNDEF cache lookup.
 * Cap residual: xlang_link_obj_needs_undef_sym_impl (Mach-O/ELF scan or one nm -u;
 * strip optional U/_). Per-path cache: on_demand walks hundreds of probes against
 * the same user.o — do not popen nm per symbol (P2 Darwin -o).
 * Why (wave212): hybrid still had needs_undef_sym body always mega C (gates+nm+ELF).
 * Used by all L8b pure needs_* orch tables (net/set/map/queue/fk/… on_demand gates).
 * PLATFORM: SHARED orch; residual scan/nm is host (POSIX; Windows hybrid via tools).
 * Track-L: #[no_mangle] keeps surface short name matching Cap residual callers.
 */
#[no_mangle]
export function xlang_link_obj_needs_undef_sym(user_o: *u8, sym: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  if (sym == 0 as *u8) {
    return 0;
  }
  if (sym[0] == 0) {
    return 0;
  }
  unsafe {
    return xlang_link_obj_needs_undef_sym_impl(user_o, sym);
  }
  return 0;
}

/**
 * Cap residual path pure: whether ld argv entry looks like .o/.obj (suffix scan).
 * Used by wave145 aggregate link_needs_* orch when scanning already-pushed objs.
 * @param s *u8 — argv entry path; null/empty → 0
 * @return i32 — 1 if ends with .o or .obj
 * PLATFORM: SHARED — authority labi_path_pure; dual-end prove IDENTICAL
 */
export extern "C" function link_abi_ld_argv_entry_is_obj(s: *u8): i32;

/**
 * Cap residual (wave213): exact defined (T/t) probe body (one-slot cache + in-process scan).
 * Pure orch owns null/empty gates; _impl is always mega.
 * @param o_path *u8 — path to .o (caller already rejected null/empty)
 * @param sym *u8 — exact bare symbol name, no leading underscore (caller rejected null/empty)
 * @return i32 — 1 if the object defines sym as text (T/t), else 0
 * PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O in-process; nm once fallback
 */
export extern "C" function xlang_link_obj_has_defined_sym_impl(o_path: *u8, sym: *u8): i32;

/**
 * Return 1 iff .o defines (T/t) the given exact symbol; null/empty → 0 without residual.
 * @param o_path *u8 — path to .o; null/empty rejected at pure gate
 * @param sym *u8 — exact bare symbol name; null/empty rejected at pure gate
 * @return i32 — 1 if defined hit, else 0
 * Pure orch: ≡ mega null/empty gates before Cap residual T/t cache lookup.
 * Cap residual: xlang_link_obj_has_defined_sym_impl (Mach-O/ELF T/t scan or one nm;
 * strip optional _). Per-path cache shares the UNDEF mmap: on_demand also probes
 * defined-sym tables against the same user.o — do not popen nm per symbol
 * (P2 Darwin -o sibling). Compress substring probes share this mmap too.
 * Why (wave213): hybrid still had has_defined_sym body always mega C (gates+nm).
 * Used by wave140 user_o_provides_* orch and wave170 heap_user ensure stub reject.
 * PLATFORM: SHARED orch; residual scan/nm is host (POSIX; Windows hybrid via tools).
 * Track-L: #[no_mangle] keeps surface short name matching Cap residual callers.
 */
#[no_mangle]
export function xlang_link_obj_has_defined_sym(o_path: *u8, sym: *u8): i32 {
  if (o_path == 0 as *u8) {
    return 0;
  }
  if (o_path[0] == 0) {
    return 0;
  }
  if (sym == 0 as *u8) {
    return 0;
  }
  if (sym[0] == 0) {
    return 0;
  }
  unsafe {
    return xlang_link_obj_has_defined_sym_impl(o_path, sym);
  }
  return 0;
}

/**
 * Cap residual (wave211): export-marker substring probe body (all-names cache).
 * Pure orch owns null/empty gates; _impl is always mega.
 * @param obj_o *u8 — path to .o (caller already rejected null/empty)
 * @param marker *u8 — marker substring (caller already rejected null/empty)
 * @return i32 — 1 if any symbol name contains marker
 * PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O in-process; nm once fallback
 */
export extern "C" function link_abi_obj_exports_marker_impl(obj_o: *u8, marker: *u8): i32;

/**
 * Return 1 iff .o exports a symbol whose name contains marker; null/empty → 0 without residual.
 * @param obj_o *u8 — path to .o; null/empty rejected at pure gate
 * @param marker *u8 — marker substring; null/empty rejected at pure gate
 * @return i32 — 1 if any symbol name contains marker, else 0
 * Pure orch: ≡ mega null/empty gates before Cap residual all-names lookup.
 * Cap residual: link_abi_obj_exports_marker_impl (Mach-O/ELF all-names scan or one nm;
 * strstr on stripped names; Darwin reconstructs one leading '_'). Markers live in
 * data (d/s/b), not T/t — do not reuse the defined blob. Per-path cache shares the
 * UNDEF mmap (P2 Darwin -o compress sibling; hello still spawned 11 full-nm after
 * UNDEF + T/t caches).
 * Why (wave211): hybrid still had exports_marker body always mega C (gates+nm).
 * Used by compress pure orch (zlib/zstd/brotli package markers) and net TLS ensure.
 * PLATFORM: SHARED orch; residual scan/nm is host (POSIX; Windows hybrid via tools).
 * Track-L: #[no_mangle] keeps surface short name matching Cap residual callers.
 */
#[no_mangle]
export function link_abi_obj_exports_marker(obj_o: *u8, marker: *u8): i32 {
  if (obj_o == 0 as *u8) {
    return 0;
  }
  if (obj_o[0] == 0) {
    return 0;
  }
  if (marker == 0 as *u8) {
    return 0;
  }
  if (marker[0] == 0) {
    return 0;
  }
  unsafe {
    return link_abi_obj_exports_marker_impl(obj_o, marker);
  }
  return 0;
}

/**
 * Cap residual (wave210): UNDEF substring probe body (one-slot cache).
 * Pure orch owns null/empty gates; _impl is always mega.
 * @param obj_o *u8 — path to .o (caller already rejected null/empty)
 * @param sym *u8 — symbol name or prefix needle (caller already rejected null/empty)
 * @return i32 — 1 if any UNDEF name contains needle
 * PLATFORM: SHARED residual; LINUX ELF / DARWIN Mach-O in-process; nm once fallback
 */
export extern "C" function link_abi_obj_has_undef_sym_impl(obj_o: *u8, sym: *u8): i32;

/**
 * Return 1 iff .o has an UNDEF name containing sym; null/empty → 0 without residual.
 * @param obj_o *u8 — path to .o; null/empty rejected at pure gate
 * @param sym *u8 — symbol name or prefix needle; null/empty rejected at pure gate
 * @return i32 — 1 if UNDEF substring hits, else 0
 * Pure orch: ≡ mega null/empty gates before Cap residual UNDEF-cache substring.
 * Cap residual: link_abi_obj_has_undef_sym_impl (Mach-O/ELF UNDEF scan or one nm;
 * strstr on stripped names; Darwin reconstructs one leading '_' so `_ZSTD` /
 * `_compress2` still hit). Per-path cache shares the needs_undef mmap
 * (P2 Darwin -o compress sibling; 8 of hello's 11 leftover full-nm).
 * Why (wave210): hybrid still had has_undef_sym body always mega C (gates+nm).
 * Used by compress pure orch (exact lib symbols and zstd prefix needles).
 * PLATFORM: SHARED orch; residual scan/nm is host (POSIX; Windows hybrid via tools).
 * Track-L: #[no_mangle] keeps surface short name matching Cap residual callers.
 */
#[no_mangle]
export function link_abi_obj_has_undef_sym(obj_o: *u8, sym: *u8): i32 {
  if (obj_o == 0 as *u8) {
    return 0;
  }
  if (obj_o[0] == 0) {
    return 0;
  }
  if (sym == 0 as *u8) {
    return 0;
  }
  if (sym[0] == 0) {
    return 0;
  }
  unsafe {
    return link_abi_obj_has_undef_sym_impl(obj_o, sym);
  }
  return 0;
}

/* ===== wave197 Cap residual / peer pure for on_demand product shell ===== */
export extern "C" function link_abi_asm_ld_push_obj(primary: *u8, link_argv0: *u8, rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8, argv: **u8, la: *i32, max_la: i32, flag_out: *i32): i32;
export extern "C" function link_abi_asm_ld_argv_push_stable(bank: *u8, argv: **u8, la: *i32, max_la: i32, p: *u8): void;
export extern "C" function xlang_asm_ld_try_under_lib_roots(rel: *u8, lib_roots: **u8, n_lib_roots: i32, bank: *u8): *u8;
export extern "C" function asm_link_obj_skip_missing(path: *u8): *u8;
export extern "C" function xlang_rel_o_path_from_argv0(argv0: *u8, rel: *u8): *u8;
export extern "C" function xlang_repo_root_from_argv0(argv0: *u8): *u8;
export extern "C" function xlang_ensure_formal_std_make_o(repo_root: *u8, rel_from_repo: *u8, make_target: *u8): i32;
export extern "C" function driver_freestanding_get(): i32;
export extern "C" function xlang_ensure_runtime_thread_glue_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_thread_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_net_udp_batch_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_net_udp_batch_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_net_workers_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_net_workers_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_test_fn_invoke_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_test_fn_invoke_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_heap_user_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_heap_user_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_process_argv_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_process_argv_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_time_os_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_time_os_o_path(argv0: *u8): *u8;
export extern "C" function xlang_ensure_runtime_queue_contention_o(argv0: *u8): i32;
export extern "C" function xlang_runtime_queue_contention_o_path(argv0: *u8): *u8;
export extern "C" function xlang_std_async_scheduler_o_path(argv0: *u8): *u8;
export extern "C" function xlang_runtime_scheduler_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_runtime_kv_mmap_glue_o_path(argv0: *u8): *u8;
export extern "C" function xlang_runtime_arrow_simd_glue_o_path(argv0: *u8): *u8;

/**
 * Return simple on_demand group count (must match seed labi_ondemand_list.from_x.c).
 * Groups: 0 string · 1 types · 2 encoding · 3 base64 · 4 csv · 5 schema ·
 * 6 option · 7 result · 8 debug · 9 slice · 10 builtin · 11 ffi.
 * @return i32 — 26 (was 25; +g25 core.cmp formal faces, CORE-005 direct import)
 * PLATFORM: SHARED — pure-asm product UNDEF gates for formal core/std .o
 */
#[no_mangle]
export function labi_od_simple_group_count(): i32 {
  return 26;
}

/**
 * Return symbol probe count for simple group g.
 * @param g i32 — group index in [0, labi_od_simple_group_count())
 * @return i32 — exact UNDEF needle count for that group; 0 if out of range
 * PLATFORM: SHARED — must match formal export surface for each rel .o
 */
#[no_mangle]
export function labi_od_simple_group_sym_count(g: i32): i32 {
  if (g < 0) {
    return 0;
  }
  if (g == 0) {
    return 13;
  }
  if (g == 1) {
    /* PLATFORM: SHARED — full core/types/types.o export surface (CORE-013 i16/u16). */
    return 27;
  }
  if (g == 2) {
    return 6;
  }
  if (g == 3) {
    return 4;
  }
  if (g == 4) {
    return 5;
  }
  if (g == 5) {
    return 3;
  }
  if (g == 6) {
    return 4;
  }
  // PLATFORM: SHARED — core.result short API (is_ok/is_err/unwrap_or/err/ok) + *_i32 aliases.
  // Was 4 (ok_i32/is_ok_i32/err_i32/ok): sole is_err/unwrap_or/err never opened gate → BLD001.
  // G.7: prefer suffix-free overloads; keep *_i32 needles for legacy callers.
  if (g == 7) {
    return 10;
  }
  if (g == 8) {
    return 6;
  }
  /* PLATFORM: SHARED — full core/slice/mod.o export surface (CORE-004; was 13). */
  if (g == 9) {
    return 28;
  }
  // PLATFORM: SHARED — core.builtin formal (tests/builtin/main.x pure-asm UNDEF residual).
  // G-01: C-path still never hard-links builtin.o (bitops → __builtin_*); pure-asm emits
  // external core_builtin_* and needs formal core/builtin/builtin.o via this group.
  if (g == 10) {
    return 14;
  }
  // PLATFORM: SHARED — std.ffi formal (tests/ffi/main.x pure-asm UNDEF residual).
  // Pure-asm import METHOD → std_ffi_*; also probe leaf ffi_*_c faces from ffi.x.
  if (g == 11) {
    return 8;
  }
  // PLATFORM: SHARED — std.test formal (tests/stdtest pure-asm residual).
  // need_test special path can miss when monofile dual lags; simple-group is
  // the same authority path as g10/g11 (ensure formal + push).
  if (g == 12) {
    return 5;
  }
  // PLATFORM: SHARED — core.assert formal (run-debug core-assert residual).
  // Distinct from g8 core.debug (core_debug_*); pure-asm mangles core.assert → core_assert_*.
  if (g == 13) {
    return 6;
  }
  // PLATFORM: SHARED — std.fmt formal (run-fmt / run-fmt-std residual).
  // Not on default OP_STD plan; simple-group is sole pure-asm push path.
  // Count 8→9: cookbook fmt_template_i32 sole UNDEF std_fmt_format_template.
  if (g == 14) {
    return 9;
  }
  // PLATFORM: SHARED — std.compress formal facade (run-compress residual).
  // Product path previously retired compress.o for C co-emit; pure-asm needs formal T.
  // Count 6→14: cookbook compress_stream_br_zs unique UNDEF stream/format/mode.
  // Count 14→24 (9.2.2): submodule zlib/gzip unique UNDEFs + Linux co-emit
  // bare compress_*_c (exact matcher; facade std_compress_gzip_compress does
  // not fire for std_compress_zlib_deflate / std_compress_gzip_gzip_compress).
  if (g == 15) {
    /* PLATFORM: SHARED — 28: +4 stream needles the co-emitted std.compress
   * module leaves U (glue in std/compress/*.o; run-compress BLD001 root). */
  return 28;
  }
  // PLATFORM: SHARED — std.io.driver formal (run-io-driver residual).
  if (g == 16) {
    return 4;
  }
  // PLATFORM: SHARED — std.debug formal (run-debug std-debug residual).
  if (g == 17) {
    return 3;
  }
  // PLATFORM: SHARED — std.simd formal (run-perf-simd + STD-SIMD-INTRINSIC).
  // VECTOR mid faces: shuffle/select/splat + add/sub/mul/hsum/dot/fma/madd
  // + scalar placeholder/hw_available/recommend_path/SIMD_PATH_* (s2/autovec)
  // + select_lane i32/f32 (product helper; sole-call UNDEF without these needles).
  if (g == 18) {
    return 23;
  }
  // PLATFORM: SHARED — std.io context-timeout formal (run-std-io-context residual).
  // timeout_from_ctx / read_ctx / write_ctx (mod.x; monofile skip std.io emit).
  if (g == 19) {
    return 3;
  }
  /*
   * wave957: std.unicode formal product probe (run-unicode residual).
   * Before wave957: .x source had no unicode simple_group; C seed had k==17
   * but PREFER path used .x → unicode symbols never probed → BLD001 UNDEF.
   * Added as g==20 to avoid disrupting existing g0-g19 assignments.
   * PLATFORM: SHARED.
   */
  if (g == 20) {
    return 8;
  }
  /*
   * PLATFORM: SHARED — core.str formal (cookbook core_str_index unique UNDEF).
   * Matcher is exact; bytes_view itself is often inlined (STRUCT_LIT return) so
   * index_of / index_of_byte / starts_with are the fire points. Count 12 = full
   * export surface in core/str/mod.x (G.7 complete one table; no second group).
   */
  if (g == 21) {
    return 12;
  }
  /*
   * PLATFORM: SHARED — core.iterator formal (cookbook iter_slice_sum unique UNDEF).
   * Matcher is exact; no prior group. Count 10 = full export surface in
   * core/iterator/mod.x (G.7 complete one table; no second group).
   */
  if (g == 22) {
    return 10;
  }
  /*
   * PLATFORM: SHARED — std.bytes formal (tests/std-bytes/arena_external unique UNDEF).
   * Matcher is exact; no prior group. Count 29 = full export surface in
   * std/bytes/mod.x (G.7 complete one table; no second group). Unique fire
   * points: from_external / is_owned / recommend_bytes_alloc_arena / extend /
   * length / deinit.
   */
  if (g == 23) {
    return 29;
  }
  /*
   * PLATFORM: SHARED — core.fmt formal (CORE-010/011 direct import("core.fmt")).
   * Matcher exact; widths/f64_special unique fire: usize/isize/ptr + f64*_to_buf.
   * Count 12 = CORE-010/011 fire points + common *_to_buf exports (G.7 one table).
   */
  if (g == 24) {
    return 12;
  }
  /*
   * PLATFORM: SHARED — core.cmp formal (CORE-005 direct import("core.cmp")).
   * Matcher exact; Ordering smoke unique fire: cmp_i32/u8/ptr + is_lt/eq/gt + then/reverse.
   * Count 12 = full core/cmp/mod.x export surface (G.7 one table).
   */
  if (g == 25) {
    return 12;
  }
  return 0;
}

/** Exported function `labi_od_simple_group_sym_at`.
 * Implements `labi_od_simple_group_sym_at`.
 * @param g i32
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_od_simple_group_sym_at(g: i32, i: i32): *u8 {
  if (g < 0) {
    return 0 as *u8;
  }
  if (i < 0) {
    return 0 as *u8;
  }
  if (g == 0) {
    if (i == 0) {
      let p: *u8 = "xlang_string_copy_c";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "xlang_string_memcmp_c";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "xlang_string_memchr_c";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "xlang_string_memmem_c";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "xlang_string_memrchr_c";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_string_string_new";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "std_string_string_from_slice";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_string_string_view";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "std_string_string_len";
      return p;
    }
    /*
     * wave958: std_string_string_view_case_fold for string_case_fold
     * cookbook. Before wave958: g==0 table missed this → BLD001 UNDEF.
     * G.7: complete the single string probe table. PLATFORM: SHARED.
     */
    if (i == 9) {
      let p: *u8 = "std_string_string_view_case_fold";
      return p;
    }
    /*
     * zc_arena_concat unique UNDEF (Ubuntu gold): string.view is often
     * inlined so g0 never fired from string_view. Unique names
     * concat_arena / string_view_get / length_StrView then never ensure
     * string.o. Matcher is exact; string_len does not cover length_StrView.
     * G.7: complete this single string probe table. Do not add a second group.
     * PLATFORM: SHARED.
     */
    if (i == 10) {
      let p: *u8 = "std_string_string_view_concat_arena";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "std_string_string_view_get";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "std_string_length_StrView";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/types/types.o (g==1).
   * CORE-013 unique: size_of/align_of i16/u16. Rest = full scalar size/align
   * surface so sole-call smokes also fire. G.7: one table (was only i32+placeholder).
   */
  if (g == 1) {
    if (i == 0) {
      let p: *u8 = "core_types_size_of_i16";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_types_size_of_u16";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_types_align_of_i16";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_types_align_of_u16";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_types_size_of_i32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_types_size_of_bool";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_types_size_of_u8";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_types_size_of_u32";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_types_size_of_u64";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_types_size_of_i64";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_types_size_of_usize";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_types_size_of_isize";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "core_types_size_of_f32";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "core_types_size_of_f64";
      return p;
    }
    if (i == 14) {
      let p: *u8 = "core_types_size_of_pointer";
      return p;
    }
    if (i == 15) {
      let p: *u8 = "core_types_align_of_i32";
      return p;
    }
    if (i == 16) {
      let p: *u8 = "core_types_align_of_bool";
      return p;
    }
    if (i == 17) {
      let p: *u8 = "core_types_align_of_u8";
      return p;
    }
    if (i == 18) {
      let p: *u8 = "core_types_align_of_u32";
      return p;
    }
    if (i == 19) {
      let p: *u8 = "core_types_align_of_u64";
      return p;
    }
    if (i == 20) {
      let p: *u8 = "core_types_align_of_i64";
      return p;
    }
    if (i == 21) {
      let p: *u8 = "core_types_align_of_usize";
      return p;
    }
    if (i == 22) {
      let p: *u8 = "core_types_align_of_isize";
      return p;
    }
    if (i == 23) {
      let p: *u8 = "core_types_align_of_f32";
      return p;
    }
    if (i == 24) {
      let p: *u8 = "core_types_align_of_f64";
      return p;
    }
    if (i == 25) {
      let p: *u8 = "core_types_align_of_pointer";
      return p;
    }
    if (i == 26) {
      let p: *u8 = "core_types_placeholder";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 2) {
    if (i == 0) {
      let p: *u8 = "encoding_utf8_valid_c";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "encoding_hex_encode_c";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "encoding_ascii_is_alpha_c";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_encoding_utf8_valid";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_encoding_utf8_decode_rune";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_encoding_ascii_is_alpha";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 3) {
    if (i == 0) {
      let p: *u8 = "base64_encode_standard_c";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_base64_encode_standard";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_base64_decode_standard";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_base64_encode_url";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 4) {
    // PLATFORM: SHARED — exact UNDEF needles for std/csv/csv.o (g==4).
    // Matcher is exact; next_field/escape do not cover parse_row/write_row
    // (cookbook csv_write_row and tests/csv/row_roundtrip sole UNDEFs).
    if (i == 0) {
      let p: *u8 = "std_csv_next_field";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_csv_escape";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_csv_csv_test_quoted_first";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_csv_parse_row";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_csv_write_row";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 5) {
    if (i == 0) {
      let p: *u8 = "schema_create_c";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "schema_decode_json_c";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "schema_smoke_c";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 6) {
    if (i == 0) {
      let p: *u8 = "core_option_some_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_option_unwrap_or_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_option_none_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_option_is_some_i32";
      return p;
    }
    return 0 as *u8;
  }
  if (g == 7) {
    // PLATFORM: SHARED — prefer short Result_i32 overloads (is_ok/is_err/unwrap_or/ok/err).
    if (i == 0) {
      let p: *u8 = "core_result_ok_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_result_is_ok_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_result_err_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_result_ok";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_result_err";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_result_is_ok";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_result_is_err";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_result_unwrap_or";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_result_unwrap_or_i32";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_result_is_err_i32";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — core.debug formal surface (tests/sort assert_eq_*).
  if (g == 8) {
    if (i == 0) {
      let p: *u8 = "core_debug_assert_eq_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_debug_assert_eq_u32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_debug_assert_eq_u64";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_debug_assert_ne_i32";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_debug_assert";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_debug_debug_assert";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — full core.slice formal API (mod.o) for CORE-004.
   * Glue from_ptr/subslice_*_c stays in core/slice/slice.o (labi_od_core_slice).
   * Prior g9 (13) covered len/get/subslice + u64 split/chunks only; sole UNDEF
   * for is_empty/first/last/split_at_i32|u8/chunks_len_i32|u8/chunk_* never
   * opened mod.o. Matcher is exact — complete one table (G.7); seed twin same
   * commit.
   */
  if (g == 9) {
    if (i == 0) {
      let p: *u8 = "core_slice_len_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_slice_get_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_slice_get_i32_unchecked";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_slice_is_empty_i32";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_slice_first_i32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_slice_last_i32";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_slice_subslice_i32";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_slice_split_at_i32";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_slice_chunks_len_i32";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_slice_chunk_i32";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_slice_len_u8";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_slice_get_u8";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "core_slice_get_u8_unchecked";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "core_slice_is_empty_u8";
      return p;
    }
    if (i == 14) {
      let p: *u8 = "core_slice_first_u8";
      return p;
    }
    if (i == 15) {
      let p: *u8 = "core_slice_subslice_u8";
      return p;
    }
    if (i == 16) {
      let p: *u8 = "core_slice_split_at_u8";
      return p;
    }
    if (i == 17) {
      let p: *u8 = "core_slice_chunks_len_u8";
      return p;
    }
    if (i == 18) {
      let p: *u8 = "core_slice_chunk_u8";
      return p;
    }
    if (i == 19) {
      let p: *u8 = "core_slice_len_u64";
      return p;
    }
    if (i == 20) {
      let p: *u8 = "core_slice_get_u64";
      return p;
    }
    if (i == 21) {
      let p: *u8 = "core_slice_is_empty_u64";
      return p;
    }
    if (i == 22) {
      let p: *u8 = "core_slice_first_u64";
      return p;
    }
    if (i == 23) {
      let p: *u8 = "core_slice_last_u64";
      return p;
    }
    if (i == 24) {
      let p: *u8 = "core_slice_subslice_u64";
      return p;
    }
    if (i == 25) {
      let p: *u8 = "core_slice_split_at_u64";
      return p;
    }
    if (i == 26) {
      let p: *u8 = "core_slice_chunks_len_u64";
      return p;
    }
    if (i == 27) {
      let p: *u8 = "core_slice_chunk_u64";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — core.builtin formal export surface (core/builtin/mod.x).
  // Pure-asm import METHOD/CALL mangle → core_builtin_<name>; must match formal_mod.
  if (g == 10) {
    if (i == 0) {
      let p: *u8 = "core_builtin_placeholder";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_builtin_copy";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_builtin_min_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_builtin_max_i32";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_builtin_min_u32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_builtin_max_u32";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_builtin_clz_u32";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_builtin_ctz_u32";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_builtin_popcount_u32";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_builtin_bswap_u32";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_builtin_rotl_u32";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_builtin_rotr_u32";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "core_builtin_unreachable";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "core_builtin_abort";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.ffi formal export surface (std/ffi/mod.x + ffi.x).
  // Pure-asm import METHOD/CALL mangle → std_ffi_<name>; leaf faces ffi_*_c.
  if (g == 11) {
    if (i == 0) {
      let p: *u8 = "std_ffi_cstr_len";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_ffi_cstring_new";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_ffi_cstring_free";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_ffi_cstring_try_new";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_ffi_cstring_destroy";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "ffi_cstr_len_c";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "ffi_cstring_new_c";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "ffi_cstring_free_c";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.test formal export surface (std/test/mod.x + test.x).
  if (g == 12) {
    if (i == 0) {
      let p: *u8 = "std_test_expect";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_test_expect_eq_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_test_expect_ne_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_test_assert";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_test_runner_case";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — core.assert formal export surface (core/assert/mod.x).
  if (g == 13) {
    if (i == 0) {
      let p: *u8 = "core_assert_assert";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_assert_assert_eq_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_assert_assert_ne_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_assert_debug_assert";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_assert_assert_eq_u32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_assert_assert_eq_bool";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.fmt formal export surface (std/fmt/mod.x + c_face).
  // Exact needles cover sole-caller faces used by tests/fmt/main.x and
  // cookbook fmt_template_i32 (std_fmt_format_template is unique-name, no suffix).
  if (g == 14) {
    if (i == 0) {
      let p: *u8 = "std_fmt_format_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_fmt_to_buf_u8_ptr_i32_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_fmt_to_buf_u8_ptr_i32_u32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_fmt_to_buf_u8_ptr_i32_i64";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_fmt_to_buf_u8_ptr_i32_u64";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_fmt_hex_to_buf_u8_ptr_i32_u32";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "std_fmt_append_to_buf_u8_ptr_i32_i32_i32";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_fmt_format_u8_ptr_i32_i32_i32";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "std_fmt_format_template";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.compress formal facade (std/compress/mod.x + c_face).
  // One-shot gzip/brotli/zstd plus stream unique names used by
  // cookbook compress_stream_br_zs (no type suffix; matcher is exact).
  if (g == 15) {
    if (i == 0) {
      let p: *u8 = "std_compress_gzip_compress";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_compress_gzip_decompress";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_compress_brotli_compress";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_compress_brotli_decompress";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_compress_zstd_compress";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_compress_zstd_decompress";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "std_compress_compress_state_bytes_for";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_compress_compress_init";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "std_compress_compress_process";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "std_compress_compress_end";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "std_compress_format_brotli";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "std_compress_format_zstd";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "std_compress_mode_compress";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "std_compress_mode_decompress";
      return p;
    }
    // 9.2.2: direct import std.compress.zlib / std.compress.gzip (Darwin mangle).
    if (i == 14) {
      let p: *u8 = "std_compress_zlib_deflate";
      return p;
    }
    if (i == 15) {
      let p: *u8 = "std_compress_zlib_inflate";
      return p;
    }
    if (i == 16) {
      let p: *u8 = "std_compress_gzip_gzip_compress";
      return p;
    }
    if (i == 17) {
      let p: *u8 = "std_compress_gzip_gzip_decompress";
      return p;
    }
    // Facade one-shot zlib (std.compress.deflate / inflate).
    if (i == 18) {
      let p: *u8 = "std_compress_deflate";
      return p;
    }
    if (i == 19) {
      let p: *u8 = "std_compress_inflate";
      return p;
    }
    // Linux product -o co-emits mod.x wrappers; UNDEF is bare *_c (exact).
    if (i == 20) {
      let p: *u8 = "compress_deflate_c";
      return p;
    }
    if (i == 21) {
      let p: *u8 = "compress_inflate_c";
      return p;
    }
    if (i == 22) {
      let p: *u8 = "compress_gzip_compress_c";
      return p;
    }
    if (i == 23) {
      let p: *u8 = "compress_gzip_decompress_c";
      return p;
    }

    /* PLATFORM: SHARED — stream needles (see g15 count note). */
    if (i == 24) {
      let p: *u8 = "std_compress_gzip_stream_state_bytes";
      return p;
    }
    if (i == 25) {
      let p: *u8 = "std_compress_brotli_stream_state_bytes";
      return p;
    }
    if (i == 26) {
      let p: *u8 = "std_compress_zstd_stream_state_bytes";
      return p;
    }
    if (i == 27) {
      let p: *u8 = "std_compress_brotli_lib_compress_brotli_stream_init_decompress_";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.io.driver formal (std/io/driver.x).
  if (g == 16) {
    if (i == 0) {
      let p: *u8 = "std_io_driver_register";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_io_driver_submit_read";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_io_driver_submit_write";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_io_driver_submit_register_fixed_buffers_buf";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.debug formal (std/debug formal_surface).
  if (g == 17) {
    if (i == 0) {
      let p: *u8 = "std_debug_assert";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_debug_println_u8_ptr_i32";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_debug_print_u8_ptr_i32";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.simd formal (shuffle/select/splat + binop/dot/fma + scalar faces).
  if (g == 18) {
    if (i == 0) {
      let p: *u8 = "std_simd_shuffle_f32x4_i32_a4";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_simd_shuffle_i32x8_i32_a8";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_simd_select_f32x4_f32x4_f32x4";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_simd_select_i32x8_i32x8_i32x8";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_simd_splat_i32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_simd_splat_f32";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "std_simd_mul_f32x4_f32x4";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_simd_mul_i32x8_i32x8";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "std_simd_sub_i32x8_i32x8";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "std_simd_sub_f32x4_f32x4";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "std_simd_add_f32x4_f32x4";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "std_simd_add_i32x8_i32x8";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "std_simd_dot";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "std_simd_madd";
      return p;
    }
    if (i == 14) {
      let p: *u8 = "std_simd_fma";
      return p;
    }
    if (i == 15) {
      let p: *u8 = "std_simd_hsum";
      return p;
    }
    if (i == 16) {
      let p: *u8 = "std_simd_placeholder";
      return p;
    }
    if (i == 17) {
      let p: *u8 = "std_simd_hw_available";
      return p;
    }
    if (i == 18) {
      let p: *u8 = "std_simd_recommend_path";
      return p;
    }
    if (i == 19) {
      let p: *u8 = "std_simd_SIMD_PATH_SCALAR";
      return p;
    }
    if (i == 20) {
      let p: *u8 = "std_simd_SIMD_PATH_HW";
      return p;
    }
    if (i == 21) {
      let p: *u8 = "std_simd_select_lane_i32_i32_i32";
      return p;
    }
    if (i == 22) {
      let p: *u8 = "std_simd_select_lane_f32_f32_f32";
      return p;
    }
    return 0 as *u8;
  }
  // PLATFORM: SHARED — std.io context-timeout formal (formal_surface STD-091).
  if (g == 19) {
    if (i == 0) {
      let p: *u8 = "std_io_timeout_from_ctx";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_io_read_ctx";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_io_write_ctx";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * wave957: std.unicode formal product probes. Mirrors C seed k==17 unicode
   * group + 2 new entries (is_supplementary, rune_utf8_len) needed by
   * unicode_nfc_smoke cookbook. G.7: single unicode probe authority.
   * PLATFORM: SHARED.
   */
  if (g == 20) {
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
    if (i == 6) {
      let p: *u8 = "std_unicode_is_supplementary";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_unicode_rune_utf8_len";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/str/mod.o (g==21).
   * Cookbook core_str_index unique names: index_of / index_of_byte / starts_with
   * (bytes_view is inlined). Rest of the table = remaining mod.x exports so
   * tests/str/bytes_view and find_split sole-call UNDEFs also fire. G.7: one table.
   */
  if (g == 21) {
    if (i == 0) {
      let p: *u8 = "core_str_bytes_view";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_str_bytes_view_from_slice";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_str_bytes_view_len";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_str_bytes_view_is_empty";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_str_bytes_view_get";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_str_bytes_view_subview";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_str_bytes_view_eq";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_str_bytes_view_eq_bytes";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_str_bytes_view_index_of_byte";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_str_bytes_view_index_of";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_str_bytes_view_contains_byte";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_str_bytes_view_starts_with";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/iterator/mod.o (g==22).
   * Cookbook iter_slice_sum unique names: iter_i32 / next_i32. Rest of the
   * table = remaining mod.x exports so tests/iterator/main and u64_roundtrip
   * sole-call UNDEFs also fire. G.7: one table.
   */
  if (g == 22) {
    if (i == 0) {
      let p: *u8 = "core_iterator_iter_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_iterator_iter_u8";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_iterator_next_i32";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_iterator_next_u8";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_iterator_iter_remaining_i32";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_iterator_iter_remaining_u8";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_iterator_iterator_protocol_version";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_iterator_iter_u64_from_buf";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_iterator_next_u64";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_iterator_iter_remaining_u64";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for std/bytes/bytes.o (g==23).
   * Test unique: from_external / is_owned / recommend_bytes_alloc_arena /
   * extend / length / deinit. Rest = remaining mod.x exports so
   * tests/std-bytes/roundtrip sole-call UNDEFs also fire. G.7: one table.
   */
  if (g == 23) {
    if (i == 0) {
      let p: *u8 = "std_bytes_from_external";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "std_bytes_is_owned";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "std_bytes_recommend_bytes_alloc_arena";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "std_bytes_extend";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "std_bytes_length";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "std_bytes_deinit";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "std_bytes_default_capacity";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "std_bytes_new";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "std_bytes_recommend_bytes_alloc";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "std_bytes_with_capacity";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "std_bytes_reserve_one";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "std_bytes_reserve";
      return p;
    }
    if (i == 12) {
      let p: *u8 = "std_bytes_grow";
      return p;
    }
    if (i == 13) {
      let p: *u8 = "std_bytes_append_byte";
      return p;
    }
    if (i == 14) {
      let p: *u8 = "std_bytes_from_slice";
      return p;
    }
    if (i == 15) {
      let p: *u8 = "std_bytes_capacity";
      return p;
    }
    if (i == 16) {
      let p: *u8 = "std_bytes_clear";
      return p;
    }
    if (i == 17) {
      let p: *u8 = "std_bytes_as_view";
      return p;
    }
    if (i == 18) {
      let p: *u8 = "std_bytes_from_view";
      return p;
    }
    if (i == 19) {
      let p: *u8 = "std_bytes_as_buffer";
      return p;
    }
    if (i == 20) {
      let p: *u8 = "std_bytes_reader";
      return p;
    }
    if (i == 21) {
      let p: *u8 = "std_bytes_read";
      return p;
    }
    if (i == 22) {
      let p: *u8 = "std_bytes_remaining";
      return p;
    }
    if (i == 23) {
      let p: *u8 = "std_bytes_seek";
      return p;
    }
    if (i == 24) {
      let p: *u8 = "std_bytes_writer";
      return p;
    }
    if (i == 25) {
      let p: *u8 = "std_bytes_write";
      return p;
    }
    if (i == 26) {
      let p: *u8 = "std_bytes_remaining_cap";
      return p;
    }
    if (i == 27) {
      let p: *u8 = "std_bytes_eq";
      return p;
    }
    if (i == 28) {
      let p: *u8 = "std_bytes_bytes_module_anchor";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/fmt/mod.o (g==24).
   * CORE-010 unique: fmt_usize/isize/ptr_to_buf. CORE-011 unique: fmt_f64*_to_buf.
   * Rest = common decimal/hex *_to_buf so sole-call smokes also fire. G.7: one table.
   */
  if (g == 24) {
    if (i == 0) {
      let p: *u8 = "core_fmt_fmt_usize_to_buf";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_fmt_fmt_isize_to_buf";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_fmt_fmt_ptr_to_buf";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_fmt_fmt_f64_to_buf";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_fmt_fmt_f64_to_buf_prec";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_fmt_fmt_i32_to_buf";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_fmt_fmt_u32_to_buf";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_fmt_fmt_u64_to_buf";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_fmt_fmt_i64_to_buf";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_fmt_fmt_bool_to_buf";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_fmt_fmt_u64_hex_to_buf";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_fmt_fmt_i32";
      return p;
    }
    return 0 as *u8;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/cmp/mod.o (g==25).
   * CORE-005 unique: cmp_i32/u8/ptr + is_lt/eq/gt + then/reverse.
   * Rest = ordering_* constructors so sole-call smokes also fire. G.7: one table.
   */
  if (g == 25) {
    if (i == 0) {
      let p: *u8 = "core_cmp_cmp_i32";
      return p;
    }
    if (i == 1) {
      let p: *u8 = "core_cmp_cmp_u8";
      return p;
    }
    if (i == 2) {
      let p: *u8 = "core_cmp_cmp_ptr";
      return p;
    }
    if (i == 3) {
      let p: *u8 = "core_cmp_is_lt";
      return p;
    }
    if (i == 4) {
      let p: *u8 = "core_cmp_is_eq";
      return p;
    }
    if (i == 5) {
      let p: *u8 = "core_cmp_is_gt";
      return p;
    }
    if (i == 6) {
      let p: *u8 = "core_cmp_then";
      return p;
    }
    if (i == 7) {
      let p: *u8 = "core_cmp_reverse";
      return p;
    }
    if (i == 8) {
      let p: *u8 = "core_cmp_ordering_less";
      return p;
    }
    if (i == 9) {
      let p: *u8 = "core_cmp_ordering_equal";
      return p;
    }
    if (i == 10) {
      let p: *u8 = "core_cmp_ordering_greater";
      return p;
    }
    if (i == 11) {
      let p: *u8 = "core_cmp_ordering_from_i32";
      return p;
    }
    return 0 as *u8;
  }
  return 0 as *u8;
}

/**
 * Return relative .o path for simple group g (repo-relative).
 * @param g i32 — group index in [0, labi_od_simple_group_count())
 * @return *u8 — static path string, or null if out of range
 * PLATFORM: SHARED — ensure via xlang_ensure_formal_std_make_o before push
 */
#[no_mangle]
export function labi_od_simple_group_rel(g: i32): *u8 {
  if (g < 0) {
    return 0 as *u8;
  }
  if (g == 0) {
    let p: *u8 = "std/string/string.o";
    return p;
  }
  if (g == 1) {
    let p: *u8 = "core/types/types.o";
    return p;
  }
  if (g == 2) {
    let p: *u8 = "std/encoding/encoding.o";
    return p;
  }
  if (g == 3) {
    let p: *u8 = "std/base64/base64.o";
    return p;
  }
  if (g == 4) {
    let p: *u8 = "std/csv/csv.o";
    return p;
  }
  if (g == 5) {
    let p: *u8 = "std/schema/schema.o";
    return p;
  }
  if (g == 6) {
    let p: *u8 = "core/option/option.o";
    return p;
  }
  if (g == 7) {
    let p: *u8 = "core/result/result.o";
    return p;
  }
  if (g == 8) {
    let p: *u8 = "core/debug/debug.o";
    return p;
  }
  if (g == 9) {
    let p: *u8 = "core/slice/mod.o";
    return p;
  }
  // PLATFORM: SHARED — core.builtin formal product .o (G-01 pure-asm only; C stays __builtin_*).
  if (g == 10) {
    let p: *u8 = "core/builtin/builtin.o";
    return p;
  }
  // PLATFORM: SHARED — std.ffi formal product .o (pure-asm run-ffi residual).
  if (g == 11) {
    let p: *u8 = "std/ffi/ffi.o";
    return p;
  }
  // PLATFORM: SHARED — std.test formal product .o (pure-asm run-stdtest residual).
  if (g == 12) {
    let p: *u8 = "std/test/test.o";
    return p;
  }
  // PLATFORM: SHARED — core.assert formal product .o (run-debug core-assert residual).
  if (g == 13) {
    let p: *u8 = "core/assert/assert.o";
    return p;
  }
  // PLATFORM: SHARED — std.fmt formal product .o (run-fmt residual).
  if (g == 14) {
    let p: *u8 = "std/fmt/fmt.o";
    return p;
  }
  // PLATFORM: SHARED — std.compress formal product .o (run-compress residual).
  if (g == 15) {
    let p: *u8 = "std/compress/compress.o";
    return p;
  }
  // PLATFORM: SHARED — std.io.driver formal product .o (run-io-driver residual).
  if (g == 16) {
    let p: *u8 = "std/io/driver.o";
    return p;
  }
  // PLATFORM: SHARED — std.debug formal product .o (run-debug residual).
  if (g == 17) {
    let p: *u8 = "std/debug/debug.o";
    return p;
  }
  // PLATFORM: SHARED — std.simd formal product .o (run-perf-simd residual).
  if (g == 18) {
    let p: *u8 = "std/simd/simd.o";
    return p;
  }
  // PLATFORM: SHARED — std.io context-timeout formal product .o (STD-091 residual).
  if (g == 19) {
    let p: *u8 = "std/io/io.o";
    return p;
  }
  // wave957: std.unicode formal product .o (run-unicode residual).
  if (g == 20) {
    let p: *u8 = "std/unicode/unicode.o";
    return p;
  }
  // PLATFORM: SHARED — core.str formal product .o (cookbook core_str_index).
  if (g == 21) {
    let p: *u8 = "core/str/mod.o";
    return p;
  }
  // PLATFORM: SHARED — core.iterator formal product .o (cookbook iter_slice_sum).
  if (g == 22) {
    let p: *u8 = "core/iterator/mod.o";
    return p;
  }
  // PLATFORM: SHARED — std.bytes formal product .o (tests/std-bytes/arena_external).
  if (g == 23) {
    let p: *u8 = "std/bytes/bytes.o";
    return p;
  }
  // PLATFORM: SHARED — core.fmt formal product .o (CORE-010/011 direct import).
  if (g == 24) {
    let p: *u8 = "core/fmt/mod.o";
    return p;
  }
  // PLATFORM: SHARED — core.cmp formal product .o (CORE-005 direct import).
  if (g == 25) {
    let p: *u8 = "core/cmp/mod.o";
    return p;
  }
  return 0 as *u8;
}

/* KV: multi-sym → kv.o + optional glue rel.
 * PLATFORM: SHARED — cookbook db_kv_arrow unique-first, then remaining unique
 * std.db.kv export faces, then legacy C ABI. Twin of L8b seed. */
#[no_mangle]
export function labi_od_kv_sym_count(): i32 {
  return 14;
}

/**
 * Exact UNDEF needle at index i for std.db.kv on-demand (user .o).
 * @param i i32 — 0..count-1; unique-first cookbook names, then remaining unique, then C ABI
 * @return *u8 — NUL-terminated symbol; null if i out of range
 * PLATFORM: SHARED — matcher is exact; import METHOD is std_db_kv_*.
 */
#[no_mangle]
export function labi_od_kv_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_db_kv_mmap_available";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_db_kv_open";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_db_kv_close";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_db_kv_append_ts";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_db_kv_get";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_db_kv_wal_flush";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_db_kv_compact";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_db_kv_sst_level_count";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_db_kv_sync";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_db_kv_put";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_db_kv_compact_generation";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_db_kv_wal_bytes";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "db_kv_open_c";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "db_kv_get_c";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_od_kv_rel`.
 * Implements `labi_od_kv_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_kv_rel(): *u8 {
  let p: *u8 = "std/db/kv/kv.o";
  return p;
}

/** Exported function `labi_od_kv_glue_rel`.
 * Implements `labi_od_kv_glue_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_kv_glue_rel(): *u8 {
  let p: *u8 = "compiler/runtime_kv_mmap_glue.o";
  return p;
}

/* Arrow.
 * PLATFORM: SHARED — cookbook db_kv_arrow unique-first, then remaining unique
 * std.db.arrow export faces, then legacy C ABI. Twin of L8b seed. */
#[no_mangle]
export function labi_od_arrow_sym_count(): i32 {
  return 29;
}

/**
 * Exact UNDEF needle at index i for std.db.arrow on-demand (user .o).
 * @param i i32 — 0..count-1; unique-first cookbook names, then remaining unique, then C ABI
 * @return *u8 — NUL-terminated symbol; null if i out of range
 * PLATFORM: SHARED — matcher is exact; import METHOD is std_db_arrow_*.
 */
#[no_mangle]
export function labi_od_arrow_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_db_arrow_adopt_f32_ptr_i32_i32";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_db_arrow_sum";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_db_arrow_dot";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_db_arrow_free_ArrowColumn";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_db_arrow_new_i32";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_db_arrow_new_f32";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_db_arrow_new_f64";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_db_arrow_adopt_i32_ptr_i32_i32";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_db_arrow_length_ArrowColumn";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_db_arrow_length_ArrowBatch";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_db_arrow_owned";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_db_arrow_null_bitmap";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_db_arrow_valid";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_db_arrow_data_i32";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_db_arrow_data_f32";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_db_arrow_data_f64";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_db_arrow_append_ArrowColumn_i32";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_db_arrow_append_ArrowColumn_f32";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_db_arrow_append_ArrowColumn_f64";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_db_arrow_append_null";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "std_db_arrow_batch";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_db_arrow_add";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "std_db_arrow_get";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "std_db_arrow_free_ArrowBatch";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "std_db_arrow_sum_valid_i32";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "std_db_arrow_sum_valid_f32";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "std_db_arrow_simd_hw_available";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "arrow_column_i32_create_c";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "arrow_column_adopt_f32_c";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_od_arrow_rel`.
 * Implements `labi_od_arrow_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_arrow_rel(): *u8 {
  let p: *u8 = "std/db/arrow/arrow.o";
  return p;
}

/** Exported function `labi_od_arrow_glue_rel`.
 * Implements `labi_od_arrow_glue_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_arrow_glue_rel(): *u8 {
  let p: *u8 = "compiler/runtime_arrow_simd_glue.o";
  return p;
}

/* PLATFORM: SHARED — cookbook async_mod_import / drain_idle / scheduler_reset /
 * net_fs_async_smoke unique-first.
 * Distinct from labi_od_async_scheduler_sym_* (C ABI ×35 for scheduler.o
 * skip-missing; never unique import METHOD std_async_*). Twin of L8b seed.
 * Produce path is formal_mod c_face std/async/async.o. */
#[no_mangle]
export function labi_od_async_sym_count(): i32 {
  return 4;
}

/**
 * Exact UNDEF needle at index i for std.async leftover unique on-demand (user .o).
 * @param i i32 — 0..count-1; unique-first cookbook names only
 * @return *u8 — NUL-terminated symbol; null if i out of range
 * PLATFORM: SHARED — matcher is exact; import METHOD is std_async_*.
 */
#[no_mangle]
export function labi_od_async_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_async_placeholder";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_async_drain_idle";
    return p;
  }
  // import("std.async").scheduler_reset → mangled unique METHOD.
  if (i == 2) {
    let p: *u8 = "std_async_scheduler_reset";
    return p;
  }
  // import("std.async").net_fs_async_smoke → mangled unique METHOD (cookbook async_net_fs).
  if (i == 3) {
    let p: *u8 = "std_async_net_fs_async_smoke";
    return p;
  }
  return 0 as *u8;
}

/**
 * Rel path of the formal_mod c_face vehicle for leftover unique std.async names.
 * @return *u8 — "std/async/async.o"
 * PLATFORM: SHARED — distinct from scheduler.o / future.o std_x auto-soft.
 */
#[no_mangle]
export function labi_od_async_rel(): *u8 {
  let p: *u8 = "std/async/async.o";
  return p;
}

/* Time */
#[no_mangle]
export function labi_od_time_sym_count(): i32 {
  return 4;
}

/** Exported function `labi_od_time_sym_at`.
 * Implements `labi_od_time_sym_at`.
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_od_time_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_time_now_monotonic_ns";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_time_sleep_ms";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_time_timer_start";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "time_now_monotonic_ns_c";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_od_time_rel`.
 * Implements `labi_od_time_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_time_rel(): *u8 {
  let p: *u8 = "std/time/time.o";
  return p;
}

/** Exported function `labi_od_time_os_rel`.
 * Implements `labi_od_time_os_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_time_os_rel(): *u8 {
  let p: *u8 = "compiler/runtime_time_os.o";
  return p;
}

/* Queue contention */
#[no_mangle]
export function labi_od_queue_sym_count(): i32 {
  return 3;
}

/** Exported function `labi_od_queue_sym_at`.
 * Implements `labi_od_queue_sym_at`.
 * @param i i32
 * @return *u8
 */
#[no_mangle]
export function labi_od_queue_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "sync_queue_contention_smoke_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "queue_os_run_two_workers_c";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "queue_contention_worker_push_c";
    return p;
  }
  return 0 as *u8;
}

/** Exported function `labi_od_queue_rel`.
 * Implements `labi_od_queue_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_queue_rel(): *u8 {
  let p: *u8 = "std/queue/queue.o";
  return p;
}

/** Exported function `labi_od_queue_contention_rel`.
 * Implements `labi_od_queue_contention_rel`.
 * @return *u8
 */
#[no_mangle]
export function labi_od_queue_contention_rel(): *u8 {
  let p: *u8 = "compiler/runtime_queue_contention.o";
  return p;
}

/**
 * Count of UNDEF symbols that pull std/net/net.o on product asm on_demand.
 * @return i32 — 34 (std_net_* + net_*_c surface + wave956 std_net_resolve_*
 *                + std_net_close_stream/connect_blocking/write_batch/tcp_pool_*
 *                + unique close_listener + Cap 9.1.7 net_resolve_ipv4/ipv6_ex_c)
 * PLATFORM: SHARED — must match formal net.o export / C glue mangles
 */
#[no_mangle]
export function labi_od_net_sym_count(): i32 {
  return 34;
}

/**
 * Net on_demand UNDEF symbol at index (product probe table for needs_std_net).
 * @param i i32 — index in [0, 32)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_net_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_net_listen";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_net_connect";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_net_udp_bind";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_net_udp_recv_many_buf";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_net_udp_send_many_buf";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_net_addr_to_u32";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_net_close_udp";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "net_stream_write_batch_c";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "net_tcp_connect_c";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "net_tcp_listen_c";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "net_udp_bind_c";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "net_udp_recv_many_buf_c";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "net_udp_send_many_buf_c";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "net_close_socket_c";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "net_udp_send_c";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "net_dns_resolve_c";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "net_sock_create_c";
    return p;
  }
  /*
   * wave956: std.net cookbook on_demand probes (resolve_ex / resolve_err_* /
   * close_stream / connect_blocking / write_batch / tcp_pool_*). Before
   * wave956: 4 cookbook examples (net_resolve_invalid / net_stream_write /
   * net_tcp_pool / thread_pool_stats — thread goes via labi_od_thread_sym_*)
   * hit BLD001 UNDEF because needs_std_net probe table did not include
   * these symbols. Probe shape: net.resolve_ex / net.resolve_err_* /
   * net.close_stream / net.connect_blocking / net.write_batch /
   * net.tcp_pool_* codegen to std_net_* mangled symbols in net.o. Twin of
   * labi_od_thread_sym_* (wave956) for std_thread_stats. G.7: complete the
   * single net probe table — no second path. PLATFORM: SHARED.
   */
  if (i == 17) {
    let p: *u8 = "std_net_resolve_ex";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_net_resolve_err_host_not_found";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_net_resolve_err_no_data";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "std_net_close_stream";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_net_connect_blocking";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "std_net_write_batch";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "std_net_tcp_pool_connect_count";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "std_net_tcp_pool_destroy";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "std_net_tcp_pool_drain";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "std_net_tcp_pool_idle_count";
    return p;
  }
  /*
   * PLATFORM: SHARED — cookbook net_listen_bind unique close_listener.
   * listen already fires need_net; matcher is exact so close_listener-only
   * user.o would miss. G.7 complete the single net probe table.
   */
  if (i == 27) {
    let p: *u8 = "std_net_close_listener";
    return p;
  }
  /*
   * PLATFORM: SHARED — tcp_pool unique wrappers (new/smoke/acquire/release).
   * connect_count/destroy/drain/idle_count already in the table; sole
   * tcp_pool_new / tcp_pool_smoke user.o still missed need_net. Matcher is
   * exact. G.7 complete this single net probe table (net_merge carries real
   * tcp_pool.o bodies). Do not add a second group.
   */
  if (i == 28) {
    let p: *u8 = "std_net_tcp_pool_new";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "std_net_tcp_pool_smoke";
    return p;
  }
  if (i == 30) {
    let p: *u8 = "std_net_tcp_pool_acquire";
    return p;
  }
  if (i == 31) {
    let p: *u8 = "std_net_tcp_pool_release";
    return p;
  }
  /* Cap residual 9.1.7: DNS raw resolve face. */
  if (i == 32) {
    let p: *u8 = "net_resolve_ipv4_ex_c";
    return p;
  }
  if (i == 33) {
    let p: *u8 = "net_resolve_ipv6_ex_c";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.net / net_*_c (on-demand chain net.o).
 * Pure orch: fixed net UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave118): hybrid still had needs_std_net body always mega C with hard-coded strings.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_net(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_net_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_net_sym_at(i);
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

/**
 * Count of UNDEF symbols that pull std/thread/thread.o on product asm on_demand.
 * @return i32 — 4 (wave956: std_thread_create / join / start / stats)
 * PLATFORM: SHARED — must match formal thread.o export / C glue mangles
 */
#[no_mangle]
export function labi_od_thread_sym_count(): i32 {
  return 4;
}

/**
 * Thread on_demand UNDEF symbol at index (product probe table for needs_std_thread).
 * @param i i32 — index in [0, 4)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 single thread probe table (no second path)
 */
#[no_mangle]
export function labi_od_thread_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  /*
   * wave956: std.thread cookbook on_demand probes (create / join / start /
   * stats). Before wave956: thread_pool_stats.x hit BLD001 UNDEF
   * std_thread_stats because asm on_demand only pushed thread.o inside the
   * need_net block (L2568 labi_ondemand_heavy.x); user programs importing
   * only std.thread (no std.net) never triggered thread.o ensure. Probe
   * shape: thread.create / thread.join / thread.start / thread.stats
   * codegen to std_thread_* mangled symbols in thread.o. G.7: single
   * thread probe table (mirrors labi_od_net_sym_*). PLATFORM: SHARED.
   */
  if (i == 0) {
    let p: *u8 = "std_thread_create";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_thread_join";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_thread_start";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_thread_stats";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.thread / std_thread_* (on-demand chain thread.o).
 * Pure orch: fixed thread UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave956): before this, asm on_demand only pushed thread.o inside
 * need_net block; user programs importing only std.thread never got
 * thread.o. Twin of link_abi_user_o_needs_std_net. PLATFORM: SHARED.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_thread(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_thread_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_thread_sym_at(i);
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

/*
 * wave958: std.vec on_demand probe table. Before wave958: no vec probe table
 * existed; user programs using Vec<u16/i32/u8/u64/f64> hit BLD001 UNDEF
 * because needs_std_vec never fired. Probe covers common ops (push/get/
 * length/deinit/from_slice/capacity/clear) plus pop/extend (exact UNDEF;
 * matcher is exact — push/from_slice_u8 do not cover pop, Vec_u64/f64
 * extend, sole from_slice_u64/f64, sole push_u64/f64, sole
 * length/get/deinit u64/f64, or sole vec3f SOA/AOS push/deinit/
 * reserve/sum). G.7: single vec probe authority.
 * PLATFORM: SHARED.
 */
#[no_mangle]
export function labi_od_vec_sym_count(): i32 {
  return 44;
}

/**
 * Vec on_demand UNDEF symbol at index (product probe table for needs_std_vec).
 * @param i i32 — index in [0, 44)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_vec authority (no second table)
 */
#[no_mangle]
export function labi_od_vec_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_vec_push_Vec_u16_ptr_u16";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_vec_push_Vec_i32_ptr_i32";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_vec_push_Vec_u8_ptr_u8";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_vec_get_Vec_u16_i32";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_vec_length_Vec_u16";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_vec_deinit_Vec_u16_ptr";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_vec_get_Vec_i32_i32";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_vec_length_Vec_i32";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_vec_deinit_Vec_i32_ptr";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_vec_from_slice_u8_ptr_i32";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_vec_capacity_Vec_u8";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_vec_clear_Vec_u8_ptr";
    return p;
  }
  // PLATFORM: SHARED — exact UNDEF needles for pop/extend/from_slice_u64/f64.
  // Matcher is exact; from_slice_u8 does not cover sole from_slice_u64/f64
  // (length/get/deinit u64/f64 also miss until vec.o is pulled).
  if (i == 12) {
    let p: *u8 = "std_vec_pop_Vec_i32_ptr";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_vec_pop_Vec_u8_ptr";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_vec_extend_Vec_i32_ptr_i32_ptr_i32";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_vec_extend_Vec_u8_ptr_u8_ptr_i32";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_vec_extend_Vec_u64_ptr_u64_ptr_i32";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_vec_extend_Vec_f64_ptr_f64_ptr_i32";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_vec_from_slice_u64_ptr_i32";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_vec_from_slice_f64_ptr_i32";
    return p;
  }
  // PLATFORM: SHARED — exact UNDEF needles for push Vec_u64/f64.
  // Matcher is exact; push_i32/u8/u16 do not cover sole push_u64/f64.
  if (i == 20) {
    let p: *u8 = "std_vec_push_Vec_u64_ptr_u64";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_vec_push_Vec_f64_ptr_f64";
    return p;
  }
  // PLATFORM: SHARED — exact UNDEF needles for length/deinit/get Vec_u64/f64.
  // Matcher is exact; u16/i32 length/deinit/get do not cover sole
  // new+length / new+deinit / get on Vec_u64/f64 (push/from_slice already
  // pull vec.o when those UNDEFs exist).
  if (i == 22) {
    let p: *u8 = "std_vec_length_Vec_u64";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "std_vec_deinit_Vec_u64_ptr";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "std_vec_length_Vec_f64";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "std_vec_deinit_Vec_f64_ptr";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "std_vec_get_Vec_u64_i32";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "std_vec_get_Vec_f64_i32";
    return p;
  }
  // PLATFORM: SHARED — exact UNDEF needles for Vec3f SOA/AOS.
  // Matcher is exact; length/push/deinit Vec_* do not cover unique
  // names vec3f_soa_push / vec3f_aos_deinit / reserve_one / sum_x.
  // new() is a const STRUCT_LIT and inlines; needles cover the
  // public unique names that can appear as the sole user UNDEF.
  if (i == 28) {
    let p: *u8 = "std_vec_vec3f_soa_push";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "std_vec_vec3f_soa_deinit";
    return p;
  }
  if (i == 30) {
    let p: *u8 = "std_vec_vec3f_aos_push";
    return p;
  }
  if (i == 31) {
    let p: *u8 = "std_vec_vec3f_aos_deinit";
    return p;
  }
  if (i == 32) {
    let p: *u8 = "std_vec_vec3f_soa_sum_x";
    return p;
  }
  if (i == 33) {
    let p: *u8 = "std_vec_vec3f_soa_reserve_one";
    return p;
  }
  if (i == 34) {
    let p: *u8 = "std_vec_vec3f_soa_len";
    return p;
  }
  if (i == 35) {
    let p: *u8 = "std_vec_vec3f_soa_get_x";
    return p;
  }
  if (i == 36) {
    let p: *u8 = "std_vec_vec3f_soa_get_y";
    return p;
  }
  if (i == 37) {
    let p: *u8 = "std_vec_vec3f_soa_get_z";
    return p;
  }
  if (i == 38) {
    let p: *u8 = "std_vec_vec3f_soa_set";
    return p;
  }
  if (i == 39) {
    let p: *u8 = "std_vec_vec3f_soa_with_capacity";
    return p;
  }
  if (i == 40) {
    let p: *u8 = "std_vec_vec3f_aos_reserve_one";
    return p;
  }
  if (i == 41) {
    let p: *u8 = "std_vec_vec3f_aos_get_x";
    return p;
  }
  if (i == 42) {
    let p: *u8 = "std_vec_vec3f_aos_sum_x";
    return p;
  }
  if (i == 43) {
    let p: *u8 = "std_vec_vec3f_aos_with_capacity";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.vec API (on-demand chain std/vec/vec.o).
 * Pure orch: fixed vec UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * PLATFORM: SHARED — G.7 single vec probe authority.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_vec(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_vec_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_vec_sym_at(i);
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

/**
 * Return relative .o path for std.vec (repo-relative).
 * @return *u8 — static "std/vec/vec.o"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_rel_vec(): *u8 {
  let p: *u8 = "std/vec/vec.o";
  return p;
}

/*
 * wave958: std.http on_demand probe table. Before wave958: no http probe
 * table existed; user programs using http.parse_status_line / decode_chunked
 * / has_chunked_encoding / has_keep_alive / headers_body_offset hit BLD001
 * UNDEF. All 5 symbols are in std/http/http.o. G.7: single http probe
 * authority. PLATFORM: SHARED.
 */
#[no_mangle]
export function labi_od_http_sym_count(): i32 {
  return 5;
}

/**
 * Http on_demand UNDEF symbol at index (product probe table for needs_std_http).
 * @param i i32 — index in [0, 5)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_http authority (no second table)
 */
#[no_mangle]
export function labi_od_http_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_http_parse_status_line";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_http_decode_chunked_body";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_http_has_chunked_encoding";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_http_has_keep_alive";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_http_headers_body_offset";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.http API (on-demand chain std/http/http.o).
 * Pure orch: fixed http UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * PLATFORM: SHARED — G.7 single http probe authority.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_http(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_http_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_http_sym_at(i);
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

/**
 * Return relative .o path for std.http (repo-relative).
 * @return *u8 — static "std/http/http.o"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_rel_http(): *u8 {
  let p: *u8 = "std/http/http.o";
  return p;
}

/**
 * Count of UNDEF symbols that pull std/set/set.o on product asm on_demand.
 * @return i32 — 20 (formal overload mangles + legacy std_set_set_i32_*)
 * PLATFORM: SHARED — must match formal set.o export / historical user.o
 */
#[no_mangle]
export function labi_od_set_sym_count(): i32 {
  return 20;
}

/**
 * Set on_demand UNDEF symbol at index (product probe table for needs_std_set).
 * @param i i32 — index in [0, 20)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete existing needs_std_set authority (no second table)
 */
#[no_mangle]
export function labi_od_set_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_set_new_i32_retSet_i32";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_set_new_i32_retSet_u64";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_set_with_capacity_Set_i32_ptr_i32";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_set_insert_Set_i32_ptr_i32";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_set_insert_Set_u64_ptr_u64";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_set_contains_key_Set_i32_i32";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_set_contains_key_Set_u64_u64";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_set_remove_Set_i32_ptr_i32";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_set_remove_Set_u64_ptr_u64";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_set_length_Set_i32";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_set_length_Set_u64";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_set_deinit_Set_i32_ptr";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_set_deinit_Set_u64_ptr";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_set_str_new";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_set_str_insert";
    return p;
  }
  /* Legacy / alternate mangles: old user.o still pulls set.o. */
  if (i == 15) {
    let p: *u8 = "std_set_set_i32_insert";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_set_set_i32_contains";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_set_set_i32_remove";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_set_set_i32_len";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_set_set_i32_deinit";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.set API (on-demand chain set.o + heap/hash deps).
 * Pure orch: fixed set UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave119): hybrid still had needs_std_set body always mega C with hard-coded strings.
 * Stale names alone never appear as U on product asm → set.o never pushed → BLD001 (Ubuntu).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_set(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_set_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_set_sym_at(i);
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

/**
 * Count of UNDEF symbols that pull std/map/map.o on product asm on_demand.
 * @return i32 — 15 (empty_size smoke + Map_i32_i32 surface + str map + wave957 Map_u64_i32 surface)
 * PLATFORM: SHARED — must match formal map.o export mangles
 */
#[no_mangle]
export function labi_od_map_sym_count(): i32 {
  return 15;
}

/**
 * Map on_demand UNDEF symbol at index (product probe table for needs_std_map).
 * @param i i32 — index in [0, 15)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete existing needs_std_map authority (no second table)
 */
#[no_mangle]
export function labi_od_map_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_map_empty_size";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_map_new_Map_i32_i32";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_map_with_capacity_Map_i32_i32_ptr_i32";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_map_insert_Map_i32_i32_ptr_i32_i32";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_map_get_Map_i32_i32_i32";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_map_find_Map_i32_i32_i32";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_map_deinit_Map_i32_i32_ptr";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_map_str_new";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_map_str_insert";
    return p;
  }
  /*
   * wave957: Map<u64, i32> on_demand probes. Before wave957: probe table only
   * had Map_i32_i32 + str variants; user programs using Map<u64, i32> hit
   * BLD001 UNDEF because needs_std_map probe never fired. Probe shape:
   * map.new/get/insert/remove/deinit/with_capacity codegen to std_map_*_Map_u64_i32_*
   * mangled symbols in map.o. G.7: complete the single map probe table.
   * PLATFORM: SHARED.
   */
  if (i == 9) {
    let p: *u8 = "std_map_new_u64";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_map_with_capacity_Map_u64_i32_ptr_i32";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_map_insert_Map_u64_i32_ptr_u64_i32";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_map_get_Map_u64_i32_u64_i32";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_map_remove_Map_u64_i32_ptr_u64";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_map_deinit_Map_u64_i32_ptr";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.map API (on-demand chain map.o + heap companions).
 * Pure orch: fixed map UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave120): hybrid still had needs_std_map body always mega C with hard-coded strings.
 * Complete authority was empty_size + full Map_i32/str surface; keep single table+orch in L8b.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_map(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_map_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_map_sym_at(i);
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

/**
 * Count of product std.queue UNDEF symbols (tests/queue surface; not contention).
 * Complements labi_od_queue_sym_* (contention smoke only).
 * @return i32 — 12
 * PLATFORM: SHARED — must match formal queue.o export mangles
 */
#[no_mangle]
export function labi_od_queue_api_sym_count(): i32 {
  return 12;
}

/**
 * Product queue on_demand UNDEF symbol at index (needs_std_queue probe table).
 * @param i i32 — index in [0, 12)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete product needs_std_queue authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_queue_api_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_queue_new_retQueue_i32";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_queue_new_retQueue_u8";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_queue_push_back_Queue_i32_ptr_i32";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_queue_push_back_Queue_u8_ptr_u8";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_queue_push_front";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_queue_pop_front_Queue_i32_ptr";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_queue_pop_back";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_queue_get";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_queue_length_Queue_i32";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_queue_is_empty_Queue_i32";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_queue_deinit_Queue_i32_ptr";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_queue_with_capacity";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references product std.queue API (on-demand chain queue.o).
 * Pure orch: fixed product queue UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * Contention path stays labi_od_queue_sym_* + labi_od_user_needs_any_sym_table in mega.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave121): hybrid still had needs_std_queue body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; do not merge with contention table (different objs).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_queue(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_queue_api_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_queue_api_sym_at(i);
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

/**
 * Count of std.test on_demand UNDEF probes (product test.o gate).
 * Matcher is exact `xlang_undef_cache_has` (rest==len). Prefix rows never fire.
 * @return i32 — 28
 * PLATFORM: SHARED — leftover L8b is the live table; keep seed/.x/.surface twins
 */
#[no_mangle]
export function labi_od_test_sym_count(): i32 {
  // PLATFORM: SHARED — 7 historical prefix/bare + 5 std_test_* + 16 mod.x inner *_c.
  return 28;
}

/**
 * Product test on_demand UNDEF symbol at index (needs_std_test probe table).
 * @param i i32 — index in [0, labi_od_test_sym_count())
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_test authority (no second hard-coded list)
 *
 * Product asm -o co-emits imported mod.x wrappers as T (`std_test_expect` etc.),
 * so exact needles on those public faces never open the gate. Live UNDEF is the
 * inner `test_*_c` face (mod.x extern → test.x T in formal test.o). Complete the
 * existing table: keep historical prefixes + std_test_* faces, add every mod.x
 * inner `*_c` so leftover exact-match fires and leftover PUSH pushes test.o.
 */
#[no_mangle]
export function labi_od_test_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "test_call_i32_void_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "test_runner_";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "test_expect_";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "test_bench_";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "test_f_test_";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "test_io_";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "test_fuzz_";
    return p;
  }
  // PLATFORM: SHARED — public std_test_* faces (T under product -o co-emit).
  if (i == 7) {
    let p: *u8 = "std_test_expect";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_test_expect_eq_i32";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_test_expect_ne_i32";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_test_assert";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_test_runner_case";
    return p;
  }
  // PLATFORM: SHARED — mod.x inner *_c (live UNDEF after wrapper co-emit as T).
  if (i == 12) {
    let p: *u8 = "test_expect_c";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "test_expect_eq_i32_c";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "test_expect_eq_u32_c";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "test_expect_ne_i32_c";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "test_run_c";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "test_bench_run_c";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "test_bench_report_c";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "test_fuzz_seed_c";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "test_fuzz_next_c";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "test_fuzz_run_c";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "test_bench_run_noop_c";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "test_fuzz_run_noop_c";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "test_runner_reset_c";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "test_runner_report_case_c";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "test_runner_report_skip_c";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "test_runner_finish_c";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.test API (on-demand chain test.o).
 * Pure orch: fixed test UNDEF table; Cap residual xlang_link_obj_needs_undef_sym
 * (exact cache; prefixes in the table never fire).
 * Avoids unconditional test.o on hello-class minimal links (ld duplicate risk).
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave122): hybrid still had needs_std_test body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b. Live needles = inner test_*_c (product -o
 * co-emits std_test_* wrappers as T).
 * PLATFORM: SHARED — hybrid L8b leftover is live; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_test(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_test_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_test_sym_at(i);
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

/**
 * Count of core.mem on_demand UNDEF probes (product core/mem/mem.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 31 (was 7; +volatile/fence + align_of_* + mem_swap/placeholder/is_alignment)
 * PLATFORM: SHARED — must match formal core/mem/mod.x export surface (CORE-017)
 */
#[no_mangle]
export function labi_od_core_mem_sym_count(): i32 {
  /* PLATFORM: SHARED — full core/mem/mem.o export surface (CORE-017 volatile/fence). */
  return 31;
}

/**
 * Product core.mem on_demand UNDEF symbol at index (needs_core_mem probe table).
 * @param i i32 — index in [0, 31)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_core_mem authority (no second hard-coded list).
 * Was 7 (align/mem_* only): sole volatile/fence UNDEF never opened mem.o → BLD001.
 */
#[no_mangle]
export function labi_od_core_mem_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "core_mem_align_up";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "core_mem_align_down";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "core_mem_mem_copy";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "core_mem_mem_set";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "core_mem_mem_zero";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "core_mem_mem_move";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "core_mem_mem_compare";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "core_mem_mem_swap";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "core_mem_is_alignment_power_of_two";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "core_mem_placeholder";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "core_mem_align_of_i32";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "core_mem_align_of_bool";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "core_mem_align_of_u8";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "core_mem_align_of_u32";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "core_mem_align_of_u64";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "core_mem_align_of_i64";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "core_mem_align_of_usize";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "core_mem_align_of_isize";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "core_mem_align_of_f32";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "core_mem_align_of_f64";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "core_mem_align_of_pointer";
    return p;
  }
  /* CORE-017 fire points: volatile load/store + fences. */
  if (i == 21) {
    let p: *u8 = "core_mem_volatile_load_u8";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "core_mem_volatile_store_u8";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "core_mem_volatile_load_u16";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "core_mem_volatile_store_u16";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "core_mem_volatile_load_u32";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "core_mem_volatile_store_u32";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "core_mem_compiler_fence";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "core_mem_fence_acquire";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "core_mem_fence_release";
    return p;
  }
  if (i == 30) {
    let p: *u8 = "core_mem_fence_seq_cst";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references core.mem API (on-demand chain core/mem/mem.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave123): hybrid still had needs_core_mem body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_core_mem(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_core_mem_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_core_mem_sym_at(i);
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

/**
 * Count of core.slice on_demand UNDEF probes (product core/slice glue gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 6
 * PLATFORM: SHARED — must match formal core/slice export surface used by needs_core_slice
 */
#[no_mangle]
export function labi_od_core_slice_sym_count(): i32 {
  return 9;
}

/**
 * Product core.slice on_demand UNDEF symbol at index (needs_core_slice probe table).
 * @param i i32 — index in [0, 9)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_core_slice authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_core_slice_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "core_slice_i32_from_ptr_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "core_subslice_i32_c";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "core_slice_u8_from_ptr_c";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "core_subslice_u8_c";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "core_slice_u64_from_ptr_c";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "core_subslice_u64_c";
    return p;
  }
  /*
   * wave957: core.slice X-facing u64 on_demand probes (chunks_len / split_at /
   * subslice). Before wave957: probe table only had C-bridge _c suffix symbols;
   * user programs calling slice.chunks_len / slice.split_at / slice.subslice
   * with u64 codegen to core_slice_*_u64 (X-facing, no _c) which didn't match
   * any probe entry → BLD001 UNDEF. G.7: complete the single core_slice probe
   * table. PLATFORM: SHARED.
   */
  if (i == 6) {
    let p: *u8 = "core_slice_chunks_len_u64";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "core_slice_split_at_u64";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "core_slice_subslice_u64";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references core.slice glue API (on-demand chain core/slice/slice.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave124): hybrid still had needs_core_slice body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_core_slice(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_core_slice_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_core_slice_sym_at(i);
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

/**
 * Count of std.heap.page_mmap on_demand UNDEF probes (product page_mmap.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 5
 * PLATFORM: SHARED — must match formal std/heap/page_mmap export surface
 */
#[no_mangle]
export function labi_od_page_mmap_sym_count(): i32 {
  return 5;
}

/**
 * Product std.heap.page_mmap on_demand UNDEF symbol at index (needs_std_heap_page_mmap probe table).
 * @param i i32 — index in [0, 5)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_heap_page_mmap authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_page_mmap_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_heap_page_mmap_page_mmap_heap_available";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_heap_page_mmap_page_mmap_heap_init";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_heap_page_mmap_page_mmap_heap_alloc";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_heap_page_mmap_page_mmap_heap_deinit";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_heap_page_mmap_page_mmap_heap_free";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.heap.page_mmap API (on-demand chain std/heap/page_mmap.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * Freestanding mmap bump heap gate; transitive linux.o + core_mem.o covered by later on_demand.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave125): hybrid still had needs_std_heap_page_mmap body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_heap_page_mmap(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_page_mmap_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_page_mmap_sym_at(i);
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

/**
 * Count of sys_linux on_demand UNDEF probes (product formal .o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 34
 * PLATFORM: SHARED — must match formal std/sys/linux export surface (nested leaf sys_linux)
 */
#[no_mangle]
export function labi_od_sys_linux_sym_count(): i32 {
  // 38 since 2026-09-09: +4 xlang_sys_* FFI externs the co-emitted
  // std.sys.linux module leaves U (glue = std/sys/linux.o +
  // compiler/src/asm/freestanding_io_x86_64.o; run-process BLD001 root).
  return 38;
}

/**
 * Product sys_linux on_demand UNDEF symbol at index.
 * @param i i32 — index in [0, 34)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_sys_linux authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_sys_linux_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_read_amd64";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_write_amd64";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_open_amd64";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_close_amd64";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_exit_amd64";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_mmap_amd64";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_read_arm64";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_write_arm64";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_openat_arm64";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_close_arm64";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_exit_arm64";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_sys_linux_linux_syscall_nr_mmap_arm64";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_sys_linux_linux_syscall_table_available";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_sys_linux_linux_syscall_invoke_available";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_sys_linux_linux_syscall_read";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_sys_linux_linux_syscall_close";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_sys_linux_linux_syscall_write";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_sys_linux_linux_syscall_exit";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_sys_linux_linux_syscall_openat";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_sys_linux_linux_anonymous_mmap";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "std_sys_linux_linux_syscall_munmap";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_sys_linux_linux_read_file_openat";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "std_sys_linux_linux_syscall_open";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "std_sys_linux_linux_read_file_into";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "std_sys_linux_linux_syscall_socket";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "std_sys_linux_linux_syscall_connect";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "std_sys_linux_linux_syscall_bind";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "std_sys_linux_linux_syscall_listen";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "std_sys_linux_linux_syscall_accept";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "std_sys_linux_linux_mmap_rw";
    return p;
  }
  if (i == 30) {
    let p: *u8 = "std_sys_linux_linux_munmap";
    return p;
  }
  if (i == 31) {
    let p: *u8 = "std_sys_linux_linux_msync_sync";
    return p;
  }
  if (i == 32) {
    let p: *u8 = "std_sys_linux_linux_mmap_file_available";
    return p;
  }
  if (i == 33) {
    let p: *u8 = "std_sys_linux_linux_sys_module_anchor";
    return p;
  }
  /* PLATFORM: SHARED — xlang_sys_* FFI externs (see sym_count note). */
  if (i == 34) {
    let p: *u8 = "xlang_sys_close";
    return p;
  }
  if (i == 35) {
    let p: *u8 = "xlang_sys_openat";
    return p;
  }
  if (i == 36) {
    let p: *u8 = "xlang_sys_exit";
    return p;
  }
  if (i == 37) {
    let p: *u8 = "xlang_sys_connect";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.sys.linux API (on-demand chain std/sys/linux.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_sys_linux(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_sys_linux_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_sys_linux_sym_at(i);
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

/**
 * Count of sys_macos on_demand UNDEF probes (product formal .o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 13
 * PLATFORM: SHARED — must match formal std/sys/macos export surface (nested leaf sys_macos)
 */
#[no_mangle]
export function labi_od_sys_macos_sym_count(): i32 {
  return 13;
}

/**
 * Product sys_macos on_demand UNDEF symbol at index.
 * @param i i32 — index in [0, 13)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_sys_macos authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_sys_macos_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_sys_macos_macos_exit";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_sys_macos_macos_write_available";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_sys_macos_macos_write";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_sys_macos_macos_write_stdout";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_sys_macos_macos_write_stderr";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_sys_macos_macos_read";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_sys_macos_macos_close";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_sys_macos_macos_read_file_into";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_sys_macos_macos_anonymous_mmap";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_sys_macos_macos_munmap";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_sys_macos_macos_mmap_available";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_sys_macos_macos_mmap_rw";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_sys_macos_macos_msync_sync";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.sys.macos API (on-demand chain std/sys/macos.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * PLATFORM: SHARED — Darwin cfg import / macos_write_*; LINUX no-op unless needles fire.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_sys_macos(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_sys_macos_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_sys_macos_sym_at(i);
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

/**
 * Count of std.sys facade on_demand UNDEF probes (product sys.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 8
 * PLATFORM: SHARED — must match formal std/sys export surface
 */
#[no_mangle]
export function labi_od_sys_sym_count(): i32 {
  return 8;
}

/**
 * Product std.sys on_demand UNDEF symbol at index (needs_std_sys probe table).
 * @param i i32 — index in [0, 8)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_sys authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_sys_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_sys_write_stdout";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_sys_write_stderr";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_sys_write";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_sys_read";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_sys_close";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_sys_exit";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_sys_freestanding_write_available";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_sys_linux_syscall_table_available";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.sys facade API (on-demand chain std/sys/sys.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * F-no-libc: write_stdout/read/close/exit + freestanding availability probes.
 * On Linux, sys.o may transitively pull linux.o via cfg target_os.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave127): hybrid still had needs_std_sys body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_sys(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_sys_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_sys_sym_at(i);
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

/**
 * Count of std.heap formal API on_demand UNDEF probes (product heap.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * @return i32 — 32
 * PLATFORM: SHARED — must match formal std/heap export surface (incl. Allocator/libc family)
 */
#[no_mangle]
export function labi_od_heap_api_sym_count(): i32 {
  return 32;
}

/**
 * Product std.heap on_demand UNDEF symbol at index (needs_std_heap_api probe table).
 * @param i i32 — index in [0, 32)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_std_heap_api authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_heap_api_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "std_heap_alloc_i32";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "std_heap_alloc_u8";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "std_heap_free_i32";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "std_heap_free_u8";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_heap_alloc_size_zero";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_heap_alloc_usize";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_heap_free_u8_ptr";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_heap_default_alloc";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_heap_kind_arena";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_heap_alloc_Allocator_usize";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_heap_realloc_Allocator_u8_ptr_usize";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_heap_free_Allocator_u8_ptr";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_heap_arena64_alloc";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_heap_libc_heap_arena64_alloc_c";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_heap_libc_heap_alloc_c";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_heap_libc_heap_free_c";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_heap_libc_heap_alloc_aligned_c";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_heap_libc_heap_alloc_i32_c";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_heap_libc_heap_alloc_u8_c";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_heap_libc_heap_alloc_u64_c";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "std_heap_libc_heap_free_i32_c";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_heap_libc_heap_free_u8_c";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "std_heap_libc_heap_free_u64_c";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "std_heap_map_find";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "std_heap_libc_heap_copy_u8_at_c";
    return p;
  }
  /*
   * wave957: std.heap trace on_demand probes (trace_on / trace_reset). Before
   * wave957: probe table had alloc/free/Allocator/libc surface but not trace
   * symbols; user programs calling heap.trace_on / heap.trace_reset hit
   * BLD001 UNDEF because needs_std_heap_api probe never fired. G.7: complete
   * the single heap probe table. PLATFORM: SHARED.
   */
  if (i == 25) {
    let p: *u8 = "std_heap_trace_on";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "std_heap_trace_reset";
    return p;
  }
  /*
   * zc_arena_concat unique UNDEF: import METHOD arena64_empty / init / deinit.
   * Before this leaf: table had arena64_alloc (vec grow) but matcher is exact,
   * so empty/init/deinit never fired needs_std_heap_api. heap.o already
   * defines the three T names (mod.x). string.o is pulled by g0 view and
   * injects T libc arena64_*_c, so string cannot pull heap as a side effect.
   * G.7: complete this single heap probe table. Do not add a second group.
   * PLATFORM: SHARED.
   */
  if (i == 27) {
    let p: *u8 = "std_heap_arena64_empty";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "std_heap_arena64_init";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "std_heap_arena64_deinit";
    return p;
  }
  /*
   * heap ops wrappers (mod.x mem_set / mem_compare). Matcher is exact: table
   * had map_find / libc copy but never mem_set, so user.o U std_heap_mem_set
   * never fired needs_std_heap_api → heap.o not pushed (run-heap / run-set).
   * heap.o catalog already compiles mod.x+ops.x (T mem_set + heap_mem_set_c).
   * G.7: complete this single heap probe table. Do not add a second group.
   * PLATFORM: SHARED.
   */
  if (i == 30) {
    let p: *u8 = "std_heap_mem_set";
    return p;
  }
  if (i == 31) {
    let p: *u8 = "std_heap_mem_compare";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references std.heap formal API (on-demand chain std/heap/heap.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * Covers typed alloc/free, Allocator/default/kind, arena64, and libc heap surface
 * used by formal set/map/queue/vec .o after import_alias C stubs were removed.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave128): hybrid still had needs_std_heap_api body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_std_heap_api(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_heap_api_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_heap_api_sym_at(i);
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

/**
 * Count of runtime_heap_user on_demand UNDEF probes (compiler/runtime_heap_user.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * Product complete set (G.7): seed authority includes with_arena init/deinit
 * (not the incomplete 4-sym residual formerly left in mega runtime_link_abi.x).
 * @return i32 — 7
 * PLATFORM: SHARED — must match heap_user export surface used by with_arena asm emit
 */
#[no_mangle]
export function labi_od_heap_user_sym_count(): i32 {
  return 7;
}

/**
 * Product runtime_heap_user on_demand UNDEF symbol at index (needs_heap_user_syms probe table).
 * @param i i32 — index in [0, 7)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_heap_user_syms authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_heap_user_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "heap_alloc_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "heap_free_c";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "heap_realloc_c";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "heap_arena64_alloc_c";
    return p;
  }
  // with_arena asm emit (pipeline_glue) — complete product probes (G.7).
  if (i == 4) {
    let p: *u8 = "heap_arena_init_c";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "heap_arena64_deinit_c";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "heap_arena64_init_c";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references runtime_heap_user symbols (on-demand chain runtime_heap_user.o).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * Covers heap_alloc/free/realloc, arena64_alloc, and with_arena init/deinit surface.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave129): hybrid still had needs_heap_user_syms body always mega C with hard-coded strings;
 *   and residual mega runtime_link_abi.x table was incomplete (4 of 7 product symbols).
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_heap_user_syms(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_heap_user_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_heap_user_sym_at(i);
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

/**
 * Count of std.async.scheduler on_demand UNDEF probes (std/async/scheduler.o gate).
 * Exact symbol names only (no prefix/strstr probes).
 * Product complete set (G.7): seed authority coop/cps/frame/run/task/worker/io + seed I/O complete surface.
 * @return i32 — 35
 * PLATFORM: SHARED — must match async scheduler + async IO export surface used by product on_demand
 */
#[no_mangle]
export function labi_od_async_scheduler_sym_count(): i32 {
  return 35;
}

/**
 * Product async scheduler on_demand UNDEF symbol at index (needs_async_scheduler probe table).
 * @param i i32 — index in [0, 35)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete needs_async_scheduler authority (no second hard-coded list)
 */
#[no_mangle]
export function labi_od_async_scheduler_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "xlang_async_coop_pingpong";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "xlang_async_coop_pingpong_jmp";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "xlang_async_cps_suspend";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "xlang_async_asm_frame_phase_by_id";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "xlang_async_asm_frame_store_from_ptr";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "xlang_async_asm_frame_load_to_ptr";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "xlang_async_asm_frame_reset_by_id";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "xlang_async_cps_suspend_io";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "xlang_async_run_i32";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "xlang_async_task_submit";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "xlang_async_task_submit_to";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "xlang_async_scheduler_drain";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "xlang_async_worker_drain";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "xlang_async_worker_count";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "xlang_async_worker_pending";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "xlang_async_queue_reset";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "xlang_async_scheduler_pending";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "xlang_async_io_wake_all";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "xlang_async_io_waiters_pending";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "xlang_async_io_completions_ready";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "xlang_async_run_seed_set_i32";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "xlang_async_run_seed_reset";
    return p;
  }
  if (i == 22) {
    let p: *u8 = "xlang_async_run_seed_push_i32";
    return p;
  }
  if (i == 23) {
    let p: *u8 = "xlang_async_run_seed_push_u32";
    return p;
  }
  if (i == 24) {
    let p: *u8 = "xlang_async_run_seed_push_i64";
    return p;
  }
  if (i == 25) {
    let p: *u8 = "xlang_async_run_seed_valid";
    return p;
  }
  if (i == 26) {
    let p: *u8 = "xlang_async_run_seed_take_i32";
    return p;
  }
  if (i == 27) {
    let p: *u8 = "xlang_async_run_seed_take_u32";
    return p;
  }
  if (i == 28) {
    let p: *u8 = "xlang_async_run_seed_take_i64";
    return p;
  }
  if (i == 29) {
    let p: *u8 = "xlang_io_submit_read_async";
    return p;
  }
  if (i == 30) {
    let p: *u8 = "xlang_io_complete_read_async";
    return p;
  }
  if (i == 31) {
    let p: *u8 = "xlang_io_complete_read_async_slot";
    return p;
  }
  if (i == 32) {
    let p: *u8 = "xlang_io_submit_write_async";
    return p;
  }
  if (i == 33) {
    let p: *u8 = "xlang_io_complete_write_async";
    return p;
  }
  if (i == 34) {
    let p: *u8 = "xlang_io_complete_write_async_slot";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o references async scheduler / async IO symbols (on-demand chain scheduler.o + glue).
 * Pure orch: fixed exact UNDEF table; Cap residual xlang_link_obj_needs_undef_sym.
 * Covers coop/cps/frame/run/task/worker/io waiters and async read/write complete surface.
 * @param user_o *u8 — path to user .o; null/empty → 0
 * @return i32 — 1 if any UNDEF hits, else 0
 * Why (wave130): hybrid still had needs_async_scheduler body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; exact symbols only (no prefix table).
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_async_scheduler(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 0;
  }
  if (user_o[0] == 0) {
    return 0;
  }
  let n: i32 = labi_od_async_scheduler_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_async_scheduler_sym_at(i);
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

/**
 * Count of zlib UNDEF needles for link_abi_obj_needs_zlib (exact libz symbols).
 * Product complete set (G.7): one-shot compress2/uncompress plus gzip Init2
 * and Darwin/ELF gzip product mangles.
 * @return i32 — 22
 * PLATFORM: SHARED — Darwin gzip-only import must pull glue/-lz.
 * 16..19: facade names (`std_compress_gzip_compress`) so `xlang build`
 * user.o UNDEF fires needs_zlib while asm ld passes compress_o=NULL.
 * 20..21: stream facade (`std_compress_compress_init`) so cookbook
 * compress_stream_br_zs fires -lz (c_face dispatch U gzip stream T).
 */
#[no_mangle]
export function labi_od_zlib_undef_sym_count(): i32 {
  return 22;
}

/**
 * zlib UNDEF needle at index (needs_zlib probe table; exact symbols).
 * @param i i32 — index in [0, 22)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete zlib undef authority
 * 0..3 Mach-O one-shot; 4..7 ELF one-shot; 8..11 Mach-O Init2 + gzip
 * product mangle; 12..15 ELF Init2 + gzip product mangle;
 * 16..19 Mach-O/ELF facade (`std_compress_gzip_compress`) for `xlang build`
 * user.o (asm ld compress_o is NULL; tail libs scan user.o only).
 * 20..21 Mach-O/ELF stream facade (`std_compress_compress_init`).
 * gzip-only import has UNDEF _std_compress_gzip_gzip_compress (no
 * _compress2); without those needles Darwin -dead_strip omits glue/-lz.
 */
#[no_mangle]
export function labi_od_zlib_undef_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "_compress2";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "_deflate";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "_inflate";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "_uncompress";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "compress2";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "deflate";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "inflate";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "uncompress";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "_deflateInit2";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "_inflateInit2";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "_std_compress_gzip_gzip_compress";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "_std_compress_gzip_gzip_decompress";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "deflateInit2";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "inflateInit2";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_compress_gzip_gzip_compress";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_compress_gzip_gzip_decompress";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "_std_compress_gzip_compress";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "_std_compress_gzip_decompress";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_compress_gzip_compress";
    return p;
  }
  if (i == 19) {
    let p: *u8 = "std_compress_gzip_decompress";
    return p;
  }
  if (i == 20) {
    let p: *u8 = "_std_compress_compress_init";
    return p;
  }
  if (i == 21) {
    let p: *u8 = "std_compress_compress_init";
    return p;
  }
  return 0 as *u8;
}

/**
 * xlang_compress_zlib_marker export name for package marker gate.
 * @return *u8 — static C string "xlang_compress_zlib_marker"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_compress_zlib_marker(): *u8 {
  let p: *u8 = "xlang_compress_zlib_marker";
  return p;
}

/**
 * Count of zstd UNDEF/prefix needles for link_abi_obj_needs_zstd.
 * Product complete set (G.7): seed authority prefix needles ZSTD_ and _ZSTD
 * (Cap residual has_undef_sym does substring match on UNDEF lines) plus
 * facade / submodule mangles so `xlang build` user.o fires needs_zstd while
 * asm ld passes compress_o=NULL.
 * @return i32 — 12
 * PLATFORM: SHARED — must match zstd C API surface used by product compress gate
 */
#[no_mangle]
export function labi_od_zstd_undef_sym_count(): i32 {
  return 12;
}

/**
 * zstd UNDEF/prefix needle at index (needs_zstd probe table).
 * @param i i32 — index in [0, 12)
 * @return *u8 — static C string needle, or null if out of range
 * PLATFORM: SHARED — G.7 complete zstd undef/prefix authority
 * 0..1 C API prefix; 2..5 Mach-O/ELF facade (`std_compress_zstd_compress`);
 * 6..9 Mach-O/ELF submodule (`std_compress_zstd_zstd_compress`);
 * 10..11 Mach-O/ELF stream facade (`std_compress_compress_init`).
 */
#[no_mangle]
export function labi_od_zstd_undef_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "ZSTD_";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "_ZSTD";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "_std_compress_zstd_compress";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "_std_compress_zstd_decompress";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_compress_zstd_compress";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_compress_zstd_decompress";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "_std_compress_zstd_zstd_compress";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "_std_compress_zstd_zstd_decompress";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_compress_zstd_zstd_compress";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_compress_zstd_zstd_decompress";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "_std_compress_compress_init";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_compress_compress_init";
    return p;
  }
  return 0 as *u8;
}

/**
 * xlang_compress_zstd_marker export name for package marker gate.
 * @return *u8 — static C string "xlang_compress_zstd_marker"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_compress_zstd_marker(): *u8 {
  let p: *u8 = "xlang_compress_zstd_marker";
  return p;
}

/**
 * Count of brotli UNDEF needles for link_abi_obj_needs_brotli (exact libbrotli symbols).
 * Product complete set (G.7): seed authority BrotliEncoderCompress + BrotliDecoderDecompress
 * plus facade / submodule mangles so `xlang build` user.o fires needs_brotli while
 * asm ld passes compress_o=NULL.
 * @return i32 — 12
 * PLATFORM: SHARED — must match brotli C API surface used by product compress gate
 */
#[no_mangle]
export function labi_od_brotli_undef_sym_count(): i32 {
  return 12;
}

/**
 * brotli UNDEF needle at index (needs_brotli probe table; exact symbols).
 * @param i i32 — index in [0, 12)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — G.7 complete brotli undef authority
 * 0..1 C API; 2..5 Mach-O/ELF facade (`std_compress_brotli_compress`);
 * 6..9 Mach-O/ELF submodule (`std_compress_brotli_brotli_compress`);
 * 10..11 Mach-O/ELF stream facade (`std_compress_compress_init`).
 */
#[no_mangle]
export function labi_od_brotli_undef_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "BrotliEncoderCompress";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "BrotliDecoderDecompress";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "_std_compress_brotli_compress";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "_std_compress_brotli_decompress";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_compress_brotli_compress";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_compress_brotli_decompress";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "_std_compress_brotli_brotli_compress";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "_std_compress_brotli_brotli_decompress";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_compress_brotli_brotli_compress";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_compress_brotli_brotli_decompress";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "_std_compress_compress_init";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_compress_compress_init";
    return p;
  }
  return 0 as *u8;
}

/**
 * xlang_compress_brotli_marker export name for package marker gate.
 * @return *u8 — static C string "xlang_compress_brotli_marker"
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_compress_brotli_marker(): *u8 {
  let p: *u8 = "xlang_compress_brotli_marker";
  return p;
}

/**
 * Whether .o depends on libz (package marker or zlib UNDEF symbols).
 * Pure orch: marker Cap residual + fixed exact UNDEF table + Cap residual has_undef_sym.
 * @param obj_o *u8 — path to any .o (user or compress); null/empty → 0
 * @return i32 — 1 if marker or any zlib UNDEF hits, else 0
 * Why (wave131): hybrid still had needs_zlib body always mega C with hard-coded strings.
 * Keep single product table+orch in L8b; Cap residual marker/has_undef stay mega.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_obj_needs_zlib(obj_o: *u8): i32 {
  if (obj_o == 0 as *u8) {
    return 0;
  }
  if (obj_o[0] == 0) {
    return 0;
  }
  let marker: *u8 = labi_od_compress_zlib_marker();
  if (marker != 0 as *u8) {
    if (marker[0] != 0) {
      let mhit: i32 = 0;
      unsafe {
        mhit = link_abi_obj_exports_marker(obj_o, marker);
      }
      if (mhit != 0) {
        return 1;
      }
    }
  }
  let n: i32 = labi_od_zlib_undef_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_zlib_undef_sym_at(i);
    if (sym != 0 as *u8) {
      if (sym[0] != 0) {
        let hit: i32 = 0;
        unsafe {
          hit = link_abi_obj_has_undef_sym(obj_o, sym);
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

/**
 * Whether .o depends on libzstd (package marker or zstd UNDEF/prefix needles).
 * Pure orch: marker Cap residual + fixed prefix-needle table + Cap residual has_undef_sym.
 * Prefix needles ZSTD_ / _ZSTD match product seed authority (substring on UNDEF lines).
 * @param obj_o *u8 — path to any .o; null/empty → 0
 * @return i32 — 1 if marker or any zstd needle hits, else 0
 * Why (wave131): hybrid still had needs_zstd body always mega C with hard-coded strings.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_obj_needs_zstd(obj_o: *u8): i32 {
  if (obj_o == 0 as *u8) {
    return 0;
  }
  if (obj_o[0] == 0) {
    return 0;
  }
  let marker: *u8 = labi_od_compress_zstd_marker();
  if (marker != 0 as *u8) {
    if (marker[0] != 0) {
      let mhit: i32 = 0;
      unsafe {
        mhit = link_abi_obj_exports_marker(obj_o, marker);
      }
      if (mhit != 0) {
        return 1;
      }
    }
  }
  let n: i32 = labi_od_zstd_undef_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_zstd_undef_sym_at(i);
    if (sym != 0 as *u8) {
      if (sym[0] != 0) {
        let hit: i32 = 0;
        unsafe {
          hit = link_abi_obj_has_undef_sym(obj_o, sym);
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

/**
 * Whether .o depends on libbrotli (package marker or brotli UNDEF symbols).
 * Pure orch: marker Cap residual + fixed exact UNDEF table + Cap residual has_undef_sym.
 * @param obj_o *u8 — path to any .o; null/empty → 0
 * @return i32 — 1 if marker or any brotli UNDEF hits, else 0
 * Why (wave131): hybrid still had needs_brotli body always mega C with hard-coded strings.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_obj_needs_brotli(obj_o: *u8): i32 {
  if (obj_o == 0 as *u8) {
    return 0;
  }
  if (obj_o[0] == 0) {
    return 0;
  }
  let marker: *u8 = labi_od_compress_brotli_marker();
  if (marker != 0 as *u8) {
    if (marker[0] != 0) {
      let mhit: i32 = 0;
      unsafe {
        mhit = link_abi_obj_exports_marker(obj_o, marker);
      }
      if (mhit != 0) {
        return 1;
      }
    }
  }
  let n: i32 = labi_od_brotli_undef_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_brotli_undef_sym_at(i);
    if (sym != 0 as *u8) {
      if (sym[0] != 0) {
        let hit: i32 = 0;
        unsafe {
          hit = link_abi_obj_has_undef_sym(obj_o, sym);
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

/**
 * Whether user .o references any compress library (zlib/zstd/brotli).
 * Pure orch: OR of three leaf pure orchs (G.7 single product compress gate).
 * @param user_o *u8 — path to user .o; null/empty → 0 via leaf null guards
 * @return i32 — 1 if any leaf needs hits, else 0
 * Why (wave131): hybrid still had needs_compress_libs body always mega C chaining hard-coded leaves.
 * Keep single product orch in L8b; leaf pure + Cap residual marker/has_undef.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function link_abi_user_o_needs_compress_libs(user_o: *u8): i32 {
  if (link_abi_obj_needs_zlib(user_o) != 0) {
    return 1;
  }
  if (link_abi_obj_needs_zstd(user_o) != 0) {
    return 1;
  }
  if (link_abi_obj_needs_brotli(user_o) != 0) {
    return 1;
  }
  return 0;
}

/* wave132–133: bulk PRIMARY OS pure tables + orch.
 * wave132: time_os / random_fill / env_os.
 * wave133: process_argv (9 needles; single-leaf to stay under module codegen capacity).
 * Semantics: null/empty user_o → 1 (legacy hard-link for old call sites without user_o).
 * std_task stays mega until capacity raise or L8b split.
 * Cap residual: xlang_link_obj_needs_undef_sym. PLATFORM: SHARED. */

/**
 * Count of runtime time_os UNDEF needles for labi_user_needs_runtime_time_os.
 * Product complete (G.7): time_*_c OS glue + std_time_* formal API.
 * @return i32 — 10
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_time_os_sym_count(): i32 {
  return 10;
}

/**
 * runtime time_os UNDEF needle at index (exact symbols only).
 * @param i i32 — index in [0, 10)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_time_os_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "time_now_monotonic_ns_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "time_now_wall_ns_c";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "time_sleep_ns_c";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "time_format_wall_rfc3339_c";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "time_wall_local_offset_min_c";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_time_now_monotonic_ns";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_time_now_wall_ns";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_time_sleep_ms";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_time_timer_start";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_time_duration_ns";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o needs runtime time_os companion (PRIMARY_TIME_OS bulk gate).
 * Pure orch: fixed exact UNDEF table; Cap residual undef_sym.
 * null/empty user_o → 1 (legacy hard-link when call site has no user_o).
 * @param user_o *u8 — path to user .o
 * @return i32 — 1 if gate open (push/ensure time_os), else 0
 * Why (wave132): hybrid still had labi_user_needs_runtime_time_os body always mega C.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function labi_user_needs_runtime_time_os(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 1;
  }
  if (user_o[0] == 0) {
    return 1;
  }
  let n: i32 = labi_od_runtime_time_os_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_runtime_time_os_sym_at(i);
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

/**
 * Count of runtime random_fill UNDEF needles for labi_user_needs_runtime_random_fill.
 * Product complete (G.7): random_*_c OS glue + std_random_* formal API.
 * @return i32 — 12
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_random_fill_sym_count(): i32 {
  return 12;
}

/**
 * runtime random_fill UNDEF needle at index (exact symbols only).
 * @param i i32 — index in [0, 12)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_random_fill_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "random_fill_bytes_c";
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
    let p: *u8 = "std_random_next";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_random_range_u32_u32";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "std_random_gen";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "std_random_flip";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "std_random_rng_smoke";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "std_random_seed";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "random_u32_c";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "random_u64_c";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "random_rng_smoke_c";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o needs runtime random_fill companion (PRIMARY_RANDOM_FILL bulk gate).
 * Pure orch: fixed exact UNDEF table; Cap residual undef_sym.
 * null/empty user_o → 1 (legacy hard-link).
 * @param user_o *u8 — path to user .o
 * @return i32 — 1 if gate open, else 0
 * Why (wave132): hybrid still had labi_user_needs_runtime_random_fill body always mega C.
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_user_needs_runtime_random_fill(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 1;
  }
  if (user_o[0] == 0) {
    return 1;
  }
  let n: i32 = labi_od_runtime_random_fill_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_runtime_random_fill_sym_at(i);
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

/**
 * Count of runtime env_os UNDEF needles for labi_user_needs_runtime_env_os.
 * Product complete (G.7): env_*_c OS glue + std_env_* formal API (incl args_iter).
 * @return i32 — 19
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_env_os_sym_count(): i32 {
  return 19;
}

/**
 * runtime env_os UNDEF needle at index (exact symbols only).
 * @param i i32 — index in [0, 19)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_env_os_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "env_getenv_c";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "env_getenv_exists_c";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "env_getenv_z_c";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "env_getenv_ptr_c";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "env_setenv_c";
    return p;
  }
  if (i == 5) {
    let p: *u8 = "env_unsetenv_c";
    return p;
  }
  if (i == 6) {
    let p: *u8 = "env_temp_dir_c";
    return p;
  }
  if (i == 7) {
    let p: *u8 = "env_iter_count_c";
    return p;
  }
  if (i == 8) {
    let p: *u8 = "env_iter_at_c";
    return p;
  }
  if (i == 9) {
    let p: *u8 = "std_env_getenv";
    return p;
  }
  if (i == 10) {
    let p: *u8 = "std_env_getenv_exists";
    return p;
  }
  if (i == 11) {
    let p: *u8 = "std_env_getenv_z";
    return p;
  }
  if (i == 12) {
    let p: *u8 = "std_env_getenv_ptr";
    return p;
  }
  if (i == 13) {
    let p: *u8 = "std_env_setenv";
    return p;
  }
  if (i == 14) {
    let p: *u8 = "std_env_unsetenv";
    return p;
  }
  if (i == 15) {
    let p: *u8 = "std_env_temp_dir";
    return p;
  }
  if (i == 16) {
    let p: *u8 = "std_env_iter";
    return p;
  }
  if (i == 17) {
    let p: *u8 = "std_env_iter_count";
    return p;
  }
  if (i == 18) {
    let p: *u8 = "std_env_args_iter";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o needs runtime env_os companion (PRIMARY_ENV_OS bulk gate).
 * Pure orch: fixed exact UNDEF table; Cap residual undef_sym.
 * null/empty user_o → 1 (legacy hard-link).
 * @param user_o *u8 — path to user .o
 * @return i32 — 1 if gate open, else 0
 * Why (wave132): hybrid still had labi_user_needs_runtime_env_os body always mega C.
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_user_needs_runtime_env_os(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 1;
  }
  if (user_o[0] == 0) {
    return 1;
  }
  let n: i32 = labi_od_runtime_env_os_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_runtime_env_os_sym_at(i);
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

/**
 * Count of runtime process_argv UNDEF needles for labi_user_needs_runtime_process_argv.
 * G.7: process_argv only for bare argv glue + env args_iter (not product std_process_*).
 * Product import METHOD std_process_* opens std/process/process.o via fk==1 (OP_STD).
 * Pushing process_argv for std_process_* dual-linked with process.o (multidef args_c).
 * @return i32 — 5
 * PLATFORM: SHARED
 */
#[no_mangle]
export function labi_od_runtime_process_argv_sym_count(): i32 {
  return 5;
}

/**
 * runtime process_argv UNDEF needle at index (exact symbols only).
 * @param i i32 — index in [0, 5)
 * @return *u8 — static C string symbol, or null if out of range
 * PLATFORM: SHARED — exact match (Darwin nm -u has no type letter U)
 */
#[no_mangle]
export function labi_od_runtime_process_argv_sym_at(i: i32): *u8 {
  if (i < 0) {
    return 0 as *u8;
  }
  if (i == 0) {
    let p: *u8 = "process_xlang_argc_get";
    return p;
  }
  if (i == 1) {
    let p: *u8 = "process_xlang_argv_get";
    return p;
  }
  if (i == 2) {
    let p: *u8 = "process_arg_c";
    return p;
  }
  if (i == 3) {
    let p: *u8 = "process_args_count_c";
    return p;
  }
  if (i == 4) {
    let p: *u8 = "std_env_args_iter";
    return p;
  }
  return 0 as *u8;
}

/**
 * Whether user .o needs runtime process_argv companion (PRIMARY process argv bulk gate).
 * Pure orch: fixed exact UNDEF table; Cap residual undef_sym.
 * null/empty user_o → 1 (legacy hard-link when call site has no user_o).
 * @param user_o *u8 — path to user .o
 * @return i32 — 1 if gate open (push/ensure process_argv path), else 0
 * Why (wave133): hybrid still had labi_user_needs_runtime_process_argv body always mega C;
 * single-leaf migrate after wave132 capacity clip blocked process_argv+std_task together.
 * PLATFORM: SHARED — hybrid L8b pure; mega cold twin under #ifndef ONDEMAND_LIST_FROM_X.
 */
#[no_mangle]
export function labi_user_needs_runtime_process_argv(user_o: *u8): i32 {
  if (user_o == 0 as *u8) {
    return 1;
  }
  if (user_o[0] == 0) {
    return 1;
  }
  let n: i32 = labi_od_runtime_process_argv_sym_count();
  let i: i32 = 0;
  while (i < n) {
    let sym: *u8 = labi_od_runtime_process_argv_sym_at(i);
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
