/* seeds/labi_ondemand_list.from_x.c — G-02f-272 P2 link_abi L8b on_demand list pure → R2 full
 * Logic source: src/runtime/labi_ondemand_list.x
 * Hybrid: XLANG_LABI_ONDEMAND_LIST_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14 / wave118–123）：公共业务符号由 full .x 提供：
 *   simple/kv/arrow/time/queue + rel_* 纯表
 *   + labi_od_net_sym_{count,at} + link_abi_user_o_needs_std_net pure orch
 *   + labi_od_set_sym_{count,at} + link_abi_user_o_needs_std_set pure orch
 *   + labi_od_map_sym_{count,at} + link_abi_user_o_needs_std_map pure orch
 *   + labi_od_queue_api_sym_{count,at} + link_abi_user_o_needs_std_queue pure orch
 *   + labi_od_test_sym_{count,at} + link_abi_user_o_needs_std_test pure orch
 *   + labi_od_core_mem_sym_{count,at} + link_abi_user_o_needs_core_mem pure orch
 *   + labi_od_core_slice_sym_{count,at} + link_abi_user_o_needs_core_slice pure orch
 *   + labi_od_page_mmap_sym_{count,at} + link_abi_user_o_needs_std_heap_page_mmap pure orch
 *   + labi_od_sys_linux_sym_{count,at} + link_abi_user_o_needs_std_sys_linux pure orch
 *   + labi_od_sys_sym_{count,at} + link_abi_user_o_needs_std_sys pure orch
 *   + labi_od_heap_api_sym_{count,at} + link_abi_user_o_needs_std_heap_api pure orch
 *   + labi_od_heap_user_sym_{count,at} + link_abi_user_o_needs_heap_user_syms pure orch
 *   + labi_od_async_scheduler_sym_{count,at} + link_abi_user_o_needs_async_scheduler pure orch
 *   + wave131 compress family: zlib/zstd/brotli marker+undef tables + needs_compress_libs pure orch
 *   + wave132 labi_od_runtime_{time_os,random_fill,env_os}_sym_* + labi_user_needs_runtime_* pure orch
 *   + wave133 labi_od_runtime_process_argv_sym_* + labi_user_needs_runtime_process_argv pure orch
 *   + wave134 labi_od_std_task_sym_* + labi_user_needs_std_task pure orch
 *   + wave135 labi_fk0_rel/sym_* + labi_std_fk0_user_needs_rel pure orch
 *     (PRIMARY OS + TASK_SPECIAL; null/empty user_o → 1)
 *   + wave140 labi_od_provides_{core_mem,std_heap}_sym_* + link_abi_user_o_provides_* pure orch
 *     (defined T/t probes; Cap residual has_defined_sym; skip hard-link mem.o/heap.o)
 *   + wave145 link_abi_link_needs_{heap_user_c,std_heap_import} pure orch
 *     (aggregate user_o + argv .o scan via pure needs_* + ld_argv_entry_is_obj)
 *   + wave190 labi_std_fk_gate_sym_* + labi_std_fk_user_needs pure orch
 *     (fk 1–13 plan gates; Cap residual undef_sym; G.7 complete wave135 fk0 sibling)
 *   + wave197 xlang_asm_ld_append_on_demand_user_objs pure orch
 *     (product on_demand shell; Cap residual ensure/skip/path + freestanding_get + undef_sym)
 * Cap residual：ensure/skip/path Cap inside shell peers；
 *   wave210：has_undef_sym pure thin orch（null/empty）；_impl = UNDEF-cache substring 常驻 mega；
 *   wave211：exports_marker pure thin orch（null/empty）；_impl = all-names cache substring 常驻 mega；
 *   wave212：needs_undef_sym pure thin orch（null/empty）；_impl = UNDEF cache mmap 常驻 mega；
 *   wave213：has_defined_sym pure thin orch（null/empty）；_impl = T/t cache mmap 常驻 mega。
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 * Prove：seeds/labi_ondemand_list_surface.from_x.c（-E 同构）nm IDENTICAL。
 */
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: L8b standalone ondemand seed → Cap snprintf */
/* G.7: Cap when this TU is cc'd alone (try-labi-prefer L8b); mega include already redirects. */
#undef snprintf
#define snprintf xlang_snprintf
#include "runtime_link_abi.h"

/* Cap residual (wave212): UNDEF cache mmap; pure owns null/empty gates. */
int xlang_link_obj_needs_undef_sym_impl(const char *user_o, const char *sym);
/* Cap residual (wave213): T/t cache mmap; pure owns null/empty gates. */
int xlang_link_obj_has_defined_sym_impl(const char *o_path, const char *sym);
/* Cap residual (wave211): all-names cache substring; pure owns null/empty gates. */
int link_abi_obj_exports_marker_impl(const char *obj_o, const char *marker);
/* Cap residual (wave210): UNDEF cache substring; pure owns null/empty gates. */
int link_abi_obj_has_undef_sym_impl(const char *obj_o, const char *sym);
/* wave145 aggregate orch Cap: path pure suffix scan (authority labi_path_pure). */
int link_abi_ld_argv_entry_is_obj(const char *s);

/* Cap residual / peer pure for wave197 on_demand shell cold twin. */
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, int *flag_out);
/* bank opaque void* ≡ pure labi_path_pure / invoke_ld_list (G.7; L4 cold TU). */
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la, const char *p);
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank);
const char *asm_link_obj_skip_missing(const char *path);
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
const char *xlang_repo_root_from_argv0(const char *argv0);
int xlang_ensure_formal_std_make_o(const char *repo_root, const char *rel_from_repo, const char *make_target);
int driver_freestanding_get(void);
int xlang_ensure_runtime_thread_glue_o(const char *argv0);
const char *xlang_runtime_thread_glue_o_path(const char *argv0);
int xlang_ensure_runtime_http_glue_o(const char *argv0);
const char *xlang_runtime_http_glue_o_path(const char *argv0);
int xlang_ensure_runtime_atomic_glue_o(const char *argv0);
const char *xlang_runtime_atomic_glue_o_path(const char *argv0);
int xlang_ensure_runtime_net_udp_batch_o(const char *argv0);
const char *xlang_runtime_net_udp_batch_o_path(const char *argv0);
int xlang_ensure_runtime_net_workers_o(const char *argv0);
const char *xlang_runtime_net_workers_o_path(const char *argv0);
int xlang_ensure_runtime_test_fn_invoke_o(const char *argv0);
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0);
int xlang_ensure_runtime_heap_user_o(const char *argv0);
const char *xlang_runtime_heap_user_o_path(const char *argv0);
int xlang_ensure_runtime_process_argv_o(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
int xlang_ensure_runtime_time_os_o(const char *argv0);
const char *xlang_runtime_time_os_o_path(const char *argv0);
int xlang_ensure_runtime_crypto_inc_glue_o(const char *argv0);
const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0);
int xlang_ensure_runtime_ed25519_ref10_glue_o(const char *argv0);
const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0);
int xlang_ensure_runtime_queue_contention_o(const char *argv0);
const char *xlang_runtime_queue_contention_o_path(const char *argv0);
void labi_std_append_queue_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la, void *flags);
void labi_std_append_test_monofile_companions(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la);
const char *xlang_std_async_scheduler_o_path(const char *argv0);
const char *xlang_runtime_scheduler_glue_o_path(const char *argv0);
int xlang_ensure_runtime_scheduler_glue_o(const char *argv0);
const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0);
int xlang_ensure_runtime_kv_mmap_glue_o(const char *argv0);
const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0);
int xlang_ensure_runtime_arrow_simd_glue_o(const char *argv0);
void link_abi_asm_ld_push_glue_after_std(int have_std, int (*ensure_fn)(const char *), const char *glue_primary,
    const char *link_argv0, const char *glue_rel, const char **lib_roots, int n_lib_roots,
    ShuAsmLdPathBank *bank, const char **argv, int *la, int max_la);

#ifndef XLANG_LABI_ONDEMAND_LIST_FROM_X

/* wave212: needs_undef_sym pure orch cold twin (null/empty gates + Cap residual nm/ELF).
 * PLATFORM: SHARED orch; residual xlang_link_obj_needs_undef_sym_impl always mega. */
int xlang_link_obj_needs_undef_sym(const char *user_o, const char *sym) {
  if (!user_o || !user_o[0] || !sym || !sym[0])
    return 0;
  return xlang_link_obj_needs_undef_sym_impl(user_o, sym);
}

/* wave213: has_defined_sym pure orch cold twin (null/empty gates + Cap residual nm T/t).
 * PLATFORM: SHARED orch; residual xlang_link_obj_has_defined_sym_impl always mega. */
int xlang_link_obj_has_defined_sym(const char *o_path, const char *sym) {
  if (!o_path || !o_path[0] || !sym || !sym[0])
    return 0;
  return xlang_link_obj_has_defined_sym_impl(o_path, sym);
}

/* wave211: exports_marker pure orch cold twin (null/empty gates + Cap residual nm).
 * PLATFORM: SHARED orch; residual link_abi_obj_exports_marker_impl always mega. */
int link_abi_obj_exports_marker(const char *obj_o, const char *marker) {
  if (!obj_o || !obj_o[0] || !marker || !marker[0])
    return 0;
  return link_abi_obj_exports_marker_impl(obj_o, marker);
}

/* wave210: has_undef_sym pure orch cold twin (null/empty gates + Cap residual nm).
 * PLATFORM: SHARED orch; residual link_abi_obj_has_undef_sym_impl always mega. */
int link_abi_obj_has_undef_sym(const char *obj_o, const char *sym) {
  if (!obj_o || !obj_o[0] || !sym || !sym[0])
    return 0;
  return link_abi_obj_has_undef_sym_impl(obj_o, sym);
}

/* Simple groups: string=0 core_types=1 encoding=2 base64=3 csv=4 schema=5
 * core_option=6 core_result=7 core_debug=8 core_slice=9 core_builtin=10 std_ffi=11.
 * PLATFORM: SHARED — g1 rel is core/types/types.o (was wrongly base64.o).
 * types/option/result/debug/slice/builtin formal .o via formal_mod + ensure; no asm co-emit hang.
 * g9 rel is core/slice/mod.o (API); glue from_ptr/subslice remains core/slice/slice.o.
 * g10 core.builtin: pure-asm emits core_builtin_* (C-path G-01 still __builtin_*).
 * g11 std.ffi: pure-asm emits std_ffi_*; formal std/ffi/ffi.o (mod.x + ffi.x). */

int labi_od_simple_group_count(void) {
  /* PLATFORM: SHARED — ≡ pure labi_ondemand_list.x (g0..g23).
   * G.7: seed cold twin must match pure table; L4 product often falls back to
   * this host-cc seed when pure prefer times out. Was return 13 with g12=simd
   * (pure g12=test / g18=simd) → run-compress UNDEF after L4 wipe.
   * g21: core.str formal (cookbook core_str_index unique UNDEF).
   * g22: core.iterator formal (cookbook iter_slice_sum unique UNDEF).
   * g23: std.bytes formal (tests/std-bytes/arena_external unique UNDEF).
   * g24: core.fmt formal (CORE-010/011 direct import).
   * g25: core.cmp formal (CORE-005 direct import Ordering/cmp_*). */
  return 26;
}

int labi_od_simple_group_sym_count(int g) {
  if (g < 0)
    return 0;
  if (g == 0)
    return 13; /* std.string — +concat_arena/view_get/length_StrView cookbook unique UNDEF */
  /* PLATFORM: SHARED — full core/types/types.o export surface (CORE-013 i16/u16). */
  if (g == 1)
    return 27;
  if (g == 2)
    return 6;
  if (g == 3)
    return 4;
  if (g == 4)
    return 5;
  if (g == 5)
    return 3;
  if (g == 6)
    return 4;
  /* PLATFORM: SHARED — core.result short API + *_i32 aliases (mirror list.x; was 4). */
  if (g == 7)
    return 10;
  if (g == 8)
    return 6;
  /* PLATFORM: SHARED — full core/slice/mod.o export surface (CORE-004). */
  if (g == 9)
    return 28;
  if (g == 10)
    return 14;
  if (g == 11)
    return 8;
  if (g == 12)
    return 5; /* std.test */
  if (g == 13)
    return 6; /* core.assert */
  if (g == 14)
    return 9; /* std.fmt — +format_template cookbook sole UNDEF */
  if (g == 15)
    return 24; /* std.compress — +stream/format/mode + 9.2.2 zlib/gzip unique + Linux *_c */
  if (g == 16)
    return 4; /* std.io.driver */
  if (g == 17)
    return 3; /* std.debug */
  if (g == 18)
    return 23; /* std.simd VECTOR mid + binop/dot/fma + scalar faces + select_lane */
  if (g == 19)
    return 3; /* std.io ctx-timeout STD-091 */
  /* wave957: std.unicode formal (run-unicode residual). */
  if (g == 20)
    return 8;
  /* PLATFORM: SHARED — core.str formal (cookbook core_str_index unique UNDEF).
   * Matcher exact; bytes_view often inlined so index_of* / starts_with fire.
   * Count 12 = full core/str/mod.x export surface. G.7 one table. */
  if (g == 21)
    return 12;
  /* PLATFORM: SHARED — core.iterator formal (cookbook iter_slice_sum unique UNDEF).
   * Matcher exact; no prior group. Count 10 = full core/iterator/mod.x export
   * surface. G.7 one table. */
  if (g == 22)
    return 10;
  /* PLATFORM: SHARED — std.bytes formal (tests/std-bytes/arena_external unique UNDEF).
   * Matcher exact; no prior group. Count 29 = full std/bytes/mod.x export
   * surface. G.7 one table. */
  if (g == 23)
    return 29;
  /* PLATFORM: SHARED — core.fmt formal (CORE-010/011). Count 12. G.7 one table. */
  if (g == 24)
    return 12;
  /* PLATFORM: SHARED — core.cmp formal (CORE-005). Count 12. G.7 one table. */
  if (g == 25)
    return 12;
  return 0;
}

const char *labi_od_simple_group_sym_at(int g, int i) {
  if (g < 0)
    return NULL;
  if (i < 0)
    return NULL;
  if (g == 0) {
    if (i == 0)
      return "xlang_string_copy_c";
    if (i == 1)
      return "xlang_string_memcmp_c";
    if (i == 2)
      return "xlang_string_memchr_c";
    if (i == 3)
      return "xlang_string_memmem_c";
    if (i == 4)
      return "xlang_string_memrchr_c";
    if (i == 5)
      return "std_string_string_new";
    if (i == 6)
      return "std_string_string_from_slice";
    if (i == 7)
      return "std_string_string_view";
    if (i == 8)
      return "std_string_string_len";
    /*
     * wave958: std_string_string_view_case_fold for string_case_fold
     * cookbook. G.7: complete the single string probe table. PLATFORM: SHARED.
     */
    if (i == 9)
      return "std_string_string_view_case_fold";
    /*
     * zc_arena_concat unique UNDEF (Ubuntu gold): string.view is often
     * inlined so g0 never fired from string_view. Unique names
     * concat_arena / string_view_get / length_StrView then never ensure
     * string.o. Matcher is exact; string_len does not cover length_StrView.
     * G.7: complete this single string probe table. Do not add a second group.
     * PLATFORM: SHARED.
     */
    if (i == 10)
      return "std_string_string_view_concat_arena";
    if (i == 11)
      return "std_string_string_view_get";
    if (i == 12)
      return "std_string_length_StrView";
    return NULL;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/types/types.o (g==1).
   * CORE-013 unique: size_of/align_of i16/u16. Rest = full scalar size/align
   * surface so sole-call smokes also fire. G.7: one table (was only i32+placeholder).
   */
  if (g == 1) {
    if (i == 0)
      return "core_types_size_of_i16";
    if (i == 1)
      return "core_types_size_of_u16";
    if (i == 2)
      return "core_types_align_of_i16";
    if (i == 3)
      return "core_types_align_of_u16";
    if (i == 4)
      return "core_types_size_of_i32";
    if (i == 5)
      return "core_types_size_of_bool";
    if (i == 6)
      return "core_types_size_of_u8";
    if (i == 7)
      return "core_types_size_of_u32";
    if (i == 8)
      return "core_types_size_of_u64";
    if (i == 9)
      return "core_types_size_of_i64";
    if (i == 10)
      return "core_types_size_of_usize";
    if (i == 11)
      return "core_types_size_of_isize";
    if (i == 12)
      return "core_types_size_of_f32";
    if (i == 13)
      return "core_types_size_of_f64";
    if (i == 14)
      return "core_types_size_of_pointer";
    if (i == 15)
      return "core_types_align_of_i32";
    if (i == 16)
      return "core_types_align_of_bool";
    if (i == 17)
      return "core_types_align_of_u8";
    if (i == 18)
      return "core_types_align_of_u32";
    if (i == 19)
      return "core_types_align_of_u64";
    if (i == 20)
      return "core_types_align_of_i64";
    if (i == 21)
      return "core_types_align_of_usize";
    if (i == 22)
      return "core_types_align_of_isize";
    if (i == 23)
      return "core_types_align_of_f32";
    if (i == 24)
      return "core_types_align_of_f64";
    if (i == 25)
      return "core_types_align_of_pointer";
    if (i == 26)
      return "core_types_placeholder";
    return NULL;
  }
  if (g == 2) {
    if (i == 0)
      return "encoding_utf8_valid_c";
    if (i == 1)
      return "encoding_hex_encode_c";
    if (i == 2)
      return "encoding_ascii_is_alpha_c";
    if (i == 3)
      return "std_encoding_utf8_valid";
    if (i == 4)
      return "std_encoding_utf8_decode_rune";
    if (i == 5)
      return "std_encoding_ascii_is_alpha";
    return NULL;
  }
  if (g == 3) {
    if (i == 0)
      return "base64_encode_standard_c";
    if (i == 1)
      return "std_base64_encode_standard";
    if (i == 2)
      return "std_base64_decode_standard";
    if (i == 3)
      return "std_base64_encode_url";
    return NULL;
  }
  if (g == 4) {
    /* PLATFORM: SHARED — exact UNDEF needles for std/csv/csv.o (g==4).
     * next_field/escape do not cover parse_row/write_row (cookbook sole UNDEF). */
    if (i == 0)
      return "std_csv_next_field";
    if (i == 1)
      return "std_csv_escape";
    if (i == 2)
      return "std_csv_csv_test_quoted_first";
    if (i == 3)
      return "std_csv_parse_row";
    if (i == 4)
      return "std_csv_write_row";
    return NULL;
  }
  if (g == 5) {
    if (i == 0)
      return "schema_create_c";
    if (i == 1)
      return "schema_decode_json_c";
    if (i == 2)
      return "schema_smoke_c";
    return NULL;
  }
  if (g == 6) {
    if (i == 0)
      return "core_option_some_i32";
    if (i == 1)
      return "core_option_unwrap_or_i32";
    if (i == 2)
      return "core_option_none_i32";
    if (i == 3)
      return "core_option_is_some_i32";
    return NULL;
  }
  if (g == 7) {
    /* PLATFORM: SHARED — prefer short Result_i32 overloads (mirror list.x). */
    if (i == 0)
      return "core_result_ok_i32";
    if (i == 1)
      return "core_result_is_ok_i32";
    if (i == 2)
      return "core_result_err_i32";
    if (i == 3)
      return "core_result_ok";
    if (i == 4)
      return "core_result_err";
    if (i == 5)
      return "core_result_is_ok";
    if (i == 6)
      return "core_result_is_err";
    if (i == 7)
      return "core_result_unwrap_or";
    if (i == 8)
      return "core_result_unwrap_or_i32";
    if (i == 9)
      return "core_result_is_err_i32";
    return NULL;
  }
  /* PLATFORM: SHARED — core.debug formal surface (tests/sort assert_eq_*). */
  if (g == 8) {
    if (i == 0)
      return "core_debug_assert_eq_i32";
    if (i == 1)
      return "core_debug_assert_eq_u32";
    if (i == 2)
      return "core_debug_assert_eq_u64";
    if (i == 3)
      return "core_debug_assert_ne_i32";
    if (i == 4)
      return "core_debug_assert";
    if (i == 5)
      return "core_debug_debug_assert";
    return NULL;
  }
  /*
   * PLATFORM: SHARED — full core.slice formal API (mod.o) for CORE-004.
   * Glue from_ptr/subslice_*_c stays in core/slice/slice.o (labi_od_core_slice).
   * Prior g9 (13) covered len/get/subslice + u64 split/chunks only; sole UNDEF
   * for is_empty/first/last/split_at_i32|u8/chunks_len_i32|u8/chunk_* never
   * opened mod.o. Matcher is exact — complete one table (G.7); .x twin same
   * commit.
   */
  if (g == 9) {
    if (i == 0)
      return "core_slice_len_i32";
    if (i == 1)
      return "core_slice_get_i32";
    if (i == 2)
      return "core_slice_get_i32_unchecked";
    if (i == 3)
      return "core_slice_is_empty_i32";
    if (i == 4)
      return "core_slice_first_i32";
    if (i == 5)
      return "core_slice_last_i32";
    if (i == 6)
      return "core_slice_subslice_i32";
    if (i == 7)
      return "core_slice_split_at_i32";
    if (i == 8)
      return "core_slice_chunks_len_i32";
    if (i == 9)
      return "core_slice_chunk_i32";
    if (i == 10)
      return "core_slice_len_u8";
    if (i == 11)
      return "core_slice_get_u8";
    if (i == 12)
      return "core_slice_get_u8_unchecked";
    if (i == 13)
      return "core_slice_is_empty_u8";
    if (i == 14)
      return "core_slice_first_u8";
    if (i == 15)
      return "core_slice_subslice_u8";
    if (i == 16)
      return "core_slice_split_at_u8";
    if (i == 17)
      return "core_slice_chunks_len_u8";
    if (i == 18)
      return "core_slice_chunk_u8";
    if (i == 19)
      return "core_slice_len_u64";
    if (i == 20)
      return "core_slice_get_u64";
    if (i == 21)
      return "core_slice_is_empty_u64";
    if (i == 22)
      return "core_slice_first_u64";
    if (i == 23)
      return "core_slice_last_u64";
    if (i == 24)
      return "core_slice_subslice_u64";
    if (i == 25)
      return "core_slice_split_at_u64";
    if (i == 26)
      return "core_slice_chunks_len_u64";
    if (i == 27)
      return "core_slice_chunk_u64";
    return NULL;
  }
  /* PLATFORM: SHARED — core.builtin formal (tests/builtin pure-asm UNDEF residual). */
  if (g == 10) {
    if (i == 0)
      return "core_builtin_placeholder";
    if (i == 1)
      return "core_builtin_copy";
    if (i == 2)
      return "core_builtin_min_i32";
    if (i == 3)
      return "core_builtin_max_i32";
    if (i == 4)
      return "core_builtin_min_u32";
    if (i == 5)
      return "core_builtin_max_u32";
    if (i == 6)
      return "core_builtin_clz_u32";
    if (i == 7)
      return "core_builtin_ctz_u32";
    if (i == 8)
      return "core_builtin_popcount_u32";
    if (i == 9)
      return "core_builtin_bswap_u32";
    if (i == 10)
      return "core_builtin_rotl_u32";
    if (i == 11)
      return "core_builtin_rotr_u32";
    if (i == 12)
      return "core_builtin_unreachable";
    if (i == 13)
      return "core_builtin_abort";
    return NULL;
  }
  /* PLATFORM: SHARED — std.ffi formal (tests/ffi pure-asm UNDEF residual). */
  if (g == 11) {
    if (i == 0)
      return "std_ffi_cstr_len";
    if (i == 1)
      return "std_ffi_cstring_new";
    if (i == 2)
      return "std_ffi_cstring_free";
    if (i == 3)
      return "std_ffi_cstring_try_new";
    if (i == 4)
      return "std_ffi_cstring_destroy";
    if (i == 5)
      return "ffi_cstr_len_c";
    if (i == 6)
      return "ffi_cstring_new_c";
    if (i == 7)
      return "ffi_cstring_free_c";
    return NULL;
  }
  /* PLATFORM: SHARED — ≡ pure g12..g19 (test/assert/fmt/compress/driver/debug/simd/io). */
  if (g == 12) {
    if (i == 0)
      return "std_test_expect";
    if (i == 1)
      return "std_test_expect_eq_i32";
    if (i == 2)
      return "std_test_expect_ne_i32";
    if (i == 3)
      return "std_test_assert";
    if (i == 4)
      return "std_test_runner_case";
    return NULL;
  }
  if (g == 13) {
    if (i == 0)
      return "core_assert_assert";
    if (i == 1)
      return "core_assert_assert_eq_i32";
    if (i == 2)
      return "core_assert_assert_ne_i32";
    if (i == 3)
      return "core_assert_debug_assert";
    if (i == 4)
      return "core_assert_assert_eq_u32";
    if (i == 5)
      return "core_assert_assert_eq_bool";
    return NULL;
  }
  if (g == 14) {
    if (i == 0)
      return "std_fmt_format_i32";
    if (i == 1)
      return "std_fmt_to_buf_u8_ptr_i32_i32";
    if (i == 2)
      return "std_fmt_to_buf_u8_ptr_i32_u32";
    if (i == 3)
      return "std_fmt_to_buf_u8_ptr_i32_i64";
    if (i == 4)
      return "std_fmt_to_buf_u8_ptr_i32_u64";
    if (i == 5)
      return "std_fmt_hex_to_buf_u8_ptr_i32_u32";
    if (i == 6)
      return "std_fmt_append_to_buf_u8_ptr_i32_i32_i32";
    if (i == 7)
      return "std_fmt_format_u8_ptr_i32_i32_i32";
    if (i == 8)
      return "std_fmt_format_template";
    return NULL;
  }
  if (g == 15) {
    if (i == 0)
      return "std_compress_gzip_compress";
    if (i == 1)
      return "std_compress_gzip_decompress";
    if (i == 2)
      return "std_compress_brotli_compress";
    if (i == 3)
      return "std_compress_brotli_decompress";
    if (i == 4)
      return "std_compress_zstd_compress";
    if (i == 5)
      return "std_compress_zstd_decompress";
    if (i == 6)
      return "std_compress_compress_state_bytes_for";
    if (i == 7)
      return "std_compress_compress_init";
    if (i == 8)
      return "std_compress_compress_process";
    if (i == 9)
      return "std_compress_compress_end";
    if (i == 10)
      return "std_compress_format_brotli";
    if (i == 11)
      return "std_compress_format_zstd";
    if (i == 12)
      return "std_compress_mode_compress";
    if (i == 13)
      return "std_compress_mode_decompress";
    /* 9.2.2: submodule zlib/gzip unique UNDEF (exact; Darwin mangle). */
    if (i == 14)
      return "std_compress_zlib_deflate";
    if (i == 15)
      return "std_compress_zlib_inflate";
    if (i == 16)
      return "std_compress_gzip_gzip_compress";
    if (i == 17)
      return "std_compress_gzip_gzip_decompress";
    if (i == 18)
      return "std_compress_deflate";
    if (i == 19)
      return "std_compress_inflate";
    /* Linux product -o co-emits mod.x wrappers; UNDEF is bare *_c. */
    if (i == 20)
      return "compress_deflate_c";
    if (i == 21)
      return "compress_inflate_c";
    if (i == 22)
      return "compress_gzip_compress_c";
    if (i == 23)
      return "compress_gzip_decompress_c";
    return NULL;
  }
  if (g == 16) {
    if (i == 0)
      return "std_io_driver_register";
    if (i == 1)
      return "std_io_driver_submit_read";
    if (i == 2)
      return "std_io_driver_submit_write";
    if (i == 3)
      return "std_io_driver_submit_register_fixed_buffers_buf";
    return NULL;
  }
  if (g == 17) {
    if (i == 0)
      return "std_debug_assert";
    if (i == 1)
      return "std_debug_println_u8_ptr_i32";
    if (i == 2)
      return "std_debug_print_u8_ptr_i32";
    return NULL;
  }
  if (g == 18) {
    if (i == 0)
      return "std_simd_shuffle_f32x4_i32_a4";
    if (i == 1)
      return "std_simd_shuffle_i32x8_i32_a8";
    if (i == 2)
      return "std_simd_select_f32x4_f32x4_f32x4";
    if (i == 3)
      return "std_simd_select_i32x8_i32x8_i32x8";
    if (i == 4)
      return "std_simd_splat_i32";
    if (i == 5)
      return "std_simd_splat_f32";
    if (i == 6)
      return "std_simd_mul_f32x4_f32x4";
    if (i == 7)
      return "std_simd_mul_i32x8_i32x8";
    if (i == 8)
      return "std_simd_sub_i32x8_i32x8";
    if (i == 9)
      return "std_simd_sub_f32x4_f32x4";
    if (i == 10)
      return "std_simd_add_f32x4_f32x4";
    if (i == 11)
      return "std_simd_add_i32x8_i32x8";
    if (i == 12)
      return "std_simd_dot";
    if (i == 13)
      return "std_simd_madd";
    if (i == 14)
      return "std_simd_fma";
    if (i == 15)
      return "std_simd_hsum";
    if (i == 16)
      return "std_simd_placeholder";
    if (i == 17)
      return "std_simd_hw_available";
    if (i == 18)
      return "std_simd_recommend_path";
    if (i == 19)
      return "std_simd_SIMD_PATH_SCALAR";
    if (i == 20)
      return "std_simd_SIMD_PATH_HW";
    if (i == 21)
      return "std_simd_select_lane_i32_i32_i32";
    if (i == 22)
      return "std_simd_select_lane_f32_f32_f32";
    return NULL;
  }
  if (g == 19) {
    if (i == 0)
      return "std_io_timeout_from_ctx";
    if (i == 1)
      return "std_io_read_ctx";
    if (i == 2)
      return "std_io_write_ctx";
    return NULL;
  }
  /*
   * wave957: std.unicode formal product probes. Mirrors .x g==20.
   * G.7: single unicode probe authority. PLATFORM: SHARED.
   */
  if (g == 20) {
    if (i == 0)
      return "std_unicode_category";
    if (i == 1)
      return "std_unicode_to_lower";
    if (i == 2)
      return "std_unicode_to_upper";
    if (i == 3)
      return "std_unicode_is_whitespace";
    if (i == 4)
      return "std_unicode_is_ascii";
    if (i == 5)
      return "std_unicode_case_fold_rune";
    if (i == 6)
      return "std_unicode_is_supplementary";
    if (i == 7)
      return "std_unicode_rune_utf8_len";
    return NULL;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/str/mod.o (g==21).
   * Cookbook unique: index_of / index_of_byte / starts_with. Rest = remaining
   * mod.x exports (tests/str sole-call). G.7: one table, no second group.
   */
  if (g == 21) {
    if (i == 0)
      return "core_str_bytes_view";
    if (i == 1)
      return "core_str_bytes_view_from_slice";
    if (i == 2)
      return "core_str_bytes_view_len";
    if (i == 3)
      return "core_str_bytes_view_is_empty";
    if (i == 4)
      return "core_str_bytes_view_get";
    if (i == 5)
      return "core_str_bytes_view_subview";
    if (i == 6)
      return "core_str_bytes_view_eq";
    if (i == 7)
      return "core_str_bytes_view_eq_bytes";
    if (i == 8)
      return "core_str_bytes_view_index_of_byte";
    if (i == 9)
      return "core_str_bytes_view_index_of";
    if (i == 10)
      return "core_str_bytes_view_contains_byte";
    if (i == 11)
      return "core_str_bytes_view_starts_with";
    return NULL;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for core/iterator/mod.o (g==22).
   * Cookbook unique: iter_i32 / next_i32. Rest = remaining mod.x exports
   * (tests/iterator sole-call). G.7: one table, no second group.
   */
  if (g == 22) {
    if (i == 0)
      return "core_iterator_iter_i32";
    if (i == 1)
      return "core_iterator_iter_u8";
    if (i == 2)
      return "core_iterator_next_i32";
    if (i == 3)
      return "core_iterator_next_u8";
    if (i == 4)
      return "core_iterator_iter_remaining_i32";
    if (i == 5)
      return "core_iterator_iter_remaining_u8";
    if (i == 6)
      return "core_iterator_iterator_protocol_version";
    if (i == 7)
      return "core_iterator_iter_u64_from_buf";
    if (i == 8)
      return "core_iterator_next_u64";
    if (i == 9)
      return "core_iterator_iter_remaining_u64";
    return NULL;
  }
  /*
   * PLATFORM: SHARED — exact UNDEF needles for std/bytes/bytes.o (g==23).
   * Test unique: from_external / is_owned / recommend_bytes_alloc_arena /
   * extend / length / deinit. Rest = remaining mod.x exports
   * (tests/std-bytes/roundtrip sole-call). G.7: one table, no second group.
   */
  if (g == 23) {
    if (i == 0)
      return "std_bytes_from_external";
    if (i == 1)
      return "std_bytes_is_owned";
    if (i == 2)
      return "std_bytes_recommend_bytes_alloc_arena";
    if (i == 3)
      return "std_bytes_extend";
    if (i == 4)
      return "std_bytes_length";
    if (i == 5)
      return "std_bytes_deinit";
    if (i == 6)
      return "std_bytes_default_capacity";
    if (i == 7)
      return "std_bytes_new";
    if (i == 8)
      return "std_bytes_recommend_bytes_alloc";
    if (i == 9)
      return "std_bytes_with_capacity";
    if (i == 10)
      return "std_bytes_reserve_one";
    if (i == 11)
      return "std_bytes_reserve";
    if (i == 12)
      return "std_bytes_grow";
    if (i == 13)
      return "std_bytes_append_byte";
    if (i == 14)
      return "std_bytes_from_slice";
    if (i == 15)
      return "std_bytes_capacity";
    if (i == 16)
      return "std_bytes_clear";
    if (i == 17)
      return "std_bytes_as_view";
    if (i == 18)
      return "std_bytes_from_view";
    if (i == 19)
      return "std_bytes_as_buffer";
    if (i == 20)
      return "std_bytes_reader";
    if (i == 21)
      return "std_bytes_read";
    if (i == 22)
      return "std_bytes_remaining";
    if (i == 23)
      return "std_bytes_seek";
    if (i == 24)
      return "std_bytes_writer";
    if (i == 25)
      return "std_bytes_write";
    if (i == 26)
      return "std_bytes_remaining_cap";
    if (i == 27)
      return "std_bytes_eq";
    if (i == 28)
      return "std_bytes_bytes_module_anchor";
    return NULL;
  }
  /* PLATFORM: SHARED — exact UNDEF needles for core/fmt/mod.o (g==24). */
  if (g == 24) {
    if (i == 0)
      return "core_fmt_fmt_usize_to_buf";
    if (i == 1)
      return "core_fmt_fmt_isize_to_buf";
    if (i == 2)
      return "core_fmt_fmt_ptr_to_buf";
    if (i == 3)
      return "core_fmt_fmt_f64_to_buf";
    if (i == 4)
      return "core_fmt_fmt_f64_to_buf_prec";
    if (i == 5)
      return "core_fmt_fmt_i32_to_buf";
    if (i == 6)
      return "core_fmt_fmt_u32_to_buf";
    if (i == 7)
      return "core_fmt_fmt_u64_to_buf";
    if (i == 8)
      return "core_fmt_fmt_i64_to_buf";
    if (i == 9)
      return "core_fmt_fmt_bool_to_buf";
    if (i == 10)
      return "core_fmt_fmt_u64_hex_to_buf";
    if (i == 11)
      return "core_fmt_fmt_i32";
    return NULL;
  }
  /* PLATFORM: SHARED — exact UNDEF needles for core/cmp/mod.o (g==25).
   * CORE-005 unique fire: cmp_i32 / cmp_u8 / cmp_ptr / is_lt/eq/gt / then / reverse.
   * Rest = ordering_* constructors so sole-call smokes also fire. G.7: one table. */
  if (g == 25) {
    if (i == 0)
      return "core_cmp_cmp_i32";
    if (i == 1)
      return "core_cmp_cmp_u8";
    if (i == 2)
      return "core_cmp_cmp_ptr";
    if (i == 3)
      return "core_cmp_is_lt";
    if (i == 4)
      return "core_cmp_is_eq";
    if (i == 5)
      return "core_cmp_is_gt";
    if (i == 6)
      return "core_cmp_then";
    if (i == 7)
      return "core_cmp_reverse";
    if (i == 8)
      return "core_cmp_ordering_less";
    if (i == 9)
      return "core_cmp_ordering_equal";
    if (i == 10)
      return "core_cmp_ordering_greater";
    if (i == 11)
      return "core_cmp_ordering_from_i32";
    return NULL;
  }
  return NULL;
}

const char *labi_od_simple_group_rel(int g) {
  if (g < 0)
    return NULL;
  if (g == 0)
    return "std/string/string.o";
  if (g == 1)
    return "core/types/types.o";
  if (g == 2)
    return "std/encoding/encoding.o";
  if (g == 3)
    return "std/base64/base64.o";
  if (g == 4)
    return "std/csv/csv.o";
  if (g == 5)
    return "std/schema/schema.o";
  if (g == 6)
    return "core/option/option.o";
  if (g == 7)
    return "core/result/result.o";
  if (g == 8)
    return "core/debug/debug.o";
  if (g == 9)
    return "core/slice/mod.o";
  if (g == 10)
    return "core/builtin/builtin.o";
  if (g == 11)
    return "std/ffi/ffi.o";
  if (g == 12)
    return "std/test/test.o";
  if (g == 13)
    return "core/assert/assert.o";
  if (g == 14)
    return "std/fmt/fmt.o";
  if (g == 15)
    return "std/compress/compress.o";
  if (g == 16)
    return "std/io/driver.o";
  if (g == 17)
    return "std/debug/debug.o";
  if (g == 18)
    return "std/simd/simd.o";
  if (g == 19)
    return "std/io/io.o";
  /* wave957: std.unicode formal product .o (run-unicode residual). */
  if (g == 20)
    return "std/unicode/unicode.o";
  /* PLATFORM: SHARED — core.str formal product .o (cookbook core_str_index). */
  if (g == 21)
    return "core/str/mod.o";
  /* PLATFORM: SHARED — core.iterator formal product .o (cookbook iter_slice_sum). */
  if (g == 22)
    return "core/iterator/mod.o";
  /* PLATFORM: SHARED — std.bytes formal product .o (tests/std-bytes/arena_external). */
  if (g == 23)
    return "std/bytes/bytes.o";
  /* PLATFORM: SHARED — core.fmt formal product .o (CORE-010/011). */
  if (g == 24)
    return "core/fmt/mod.o";
  /* PLATFORM: SHARED — core.cmp formal product .o (CORE-005). */
  if (g == 25)
    return "core/cmp/mod.o";
  return NULL;
}

/* KV: multi-sym → kv.o + optional glue rel.
 * PLATFORM: SHARED — cookbook db_kv_arrow unique-first (mmap_available /
 * open / close / append_ts / get / wal_flush / compact / sst_level_count),
 * then remaining unique std.db.kv export faces, then legacy C ABI.
 * Matcher is exact; C ABI names never fire import METHOD std_db_kv_*. */
int labi_od_kv_sym_count(void) {
  return 14;
}

const char *labi_od_kv_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_db_kv_mmap_available";
  if (i == 1)
    return "std_db_kv_open";
  if (i == 2)
    return "std_db_kv_close";
  if (i == 3)
    return "std_db_kv_append_ts";
  if (i == 4)
    return "std_db_kv_get";
  if (i == 5)
    return "std_db_kv_wal_flush";
  if (i == 6)
    return "std_db_kv_compact";
  if (i == 7)
    return "std_db_kv_sst_level_count";
  if (i == 8)
    return "std_db_kv_sync";
  if (i == 9)
    return "std_db_kv_put";
  if (i == 10)
    return "std_db_kv_compact_generation";
  if (i == 11)
    return "std_db_kv_wal_bytes";
  if (i == 12)
    return "db_kv_open_c";
  if (i == 13)
    return "db_kv_get_c";
  return NULL;
}

const char *labi_od_kv_rel(void) {
  return "std/db/kv/kv.o";
}

const char *labi_od_kv_glue_rel(void) {
  return "compiler/runtime_kv_mmap_glue.o";
}

/* Arrow.
 * PLATFORM: SHARED — cookbook db_kv_arrow unique-first (adopt_f32_ptr_i32_i32 /
 * sum / dot / free_ArrowColumn), then remaining unique std.db.arrow export
 * faces, then legacy C ABI. Matcher is exact. */
int labi_od_arrow_sym_count(void) {
  return 29;
}

const char *labi_od_arrow_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_db_arrow_adopt_f32_ptr_i32_i32";
  if (i == 1)
    return "std_db_arrow_sum";
  if (i == 2)
    return "std_db_arrow_dot";
  if (i == 3)
    return "std_db_arrow_free_ArrowColumn";
  if (i == 4)
    return "std_db_arrow_new_i32";
  if (i == 5)
    return "std_db_arrow_new_f32";
  if (i == 6)
    return "std_db_arrow_new_f64";
  if (i == 7)
    return "std_db_arrow_adopt_i32_ptr_i32_i32";
  if (i == 8)
    return "std_db_arrow_length_ArrowColumn";
  if (i == 9)
    return "std_db_arrow_length_ArrowBatch";
  if (i == 10)
    return "std_db_arrow_owned";
  if (i == 11)
    return "std_db_arrow_null_bitmap";
  if (i == 12)
    return "std_db_arrow_valid";
  if (i == 13)
    return "std_db_arrow_data_i32";
  if (i == 14)
    return "std_db_arrow_data_f32";
  if (i == 15)
    return "std_db_arrow_data_f64";
  if (i == 16)
    return "std_db_arrow_append_ArrowColumn_i32";
  if (i == 17)
    return "std_db_arrow_append_ArrowColumn_f32";
  if (i == 18)
    return "std_db_arrow_append_ArrowColumn_f64";
  if (i == 19)
    return "std_db_arrow_append_null";
  if (i == 20)
    return "std_db_arrow_batch";
  if (i == 21)
    return "std_db_arrow_add";
  if (i == 22)
    return "std_db_arrow_get";
  if (i == 23)
    return "std_db_arrow_free_ArrowBatch";
  if (i == 24)
    return "std_db_arrow_sum_valid_i32";
  if (i == 25)
    return "std_db_arrow_sum_valid_f32";
  if (i == 26)
    return "std_db_arrow_simd_hw_available";
  if (i == 27)
    return "arrow_column_i32_create_c";
  if (i == 28)
    return "arrow_column_adopt_f32_c";
  return NULL;
}

const char *labi_od_arrow_rel(void) {
  return "std/db/arrow/arrow.o";
}

const char *labi_od_arrow_glue_rel(void) {
  return "compiler/runtime_arrow_simd_glue.o";
}

/* PLATFORM: SHARED — cookbook async_mod_import / drain_idle / scheduler_reset /
 * net_fs_async_smoke unique-first.
 * Distinct from labi_od_async_scheduler_sym_* (C ABI ×35 for scheduler.o
 * skip-missing; never unique import METHOD std_async_*). Matcher is exact.
 * Produce path is formal_mod c_face std/async/async.o (not host-cc of mod.x). */
int labi_od_async_sym_count(void) {
  return 4;
}

const char *labi_od_async_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_async_placeholder";
  if (i == 1)
    return "std_async_drain_idle";
  /* import("std.async").scheduler_reset → mangled unique METHOD. */
  if (i == 2)
    return "std_async_scheduler_reset";
  /* import("std.async").net_fs_async_smoke → mangled unique METHOD. */
  if (i == 3)
    return "std_async_net_fs_async_smoke";
  return NULL;
}

const char *labi_od_async_rel(void) {
  return "std/async/async.o";
}

/* Time */
int labi_od_time_sym_count(void) {
  return 4;
}

const char *labi_od_time_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_time_now_monotonic_ns";
  if (i == 1)
    return "std_time_sleep_ms";
  if (i == 2)
    return "std_time_timer_start";
  if (i == 3)
    return "time_now_monotonic_ns_c";
  return NULL;
}

const char *labi_od_time_rel(void) {
  return "std/time/time.o";
}

const char *labi_od_time_os_rel(void) {
  return "compiler/runtime_time_os.o";
}

/* Queue contention */
int labi_od_queue_sym_count(void) {
  return 3;
}

const char *labi_od_queue_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "sync_queue_contention_smoke_c";
  if (i == 1)
    return "queue_os_run_two_workers_c";
  if (i == 2)
    return "queue_contention_worker_push_c";
  return NULL;
}

const char *labi_od_queue_rel(void) {
  return "std/queue/queue.o";
}

const char *labi_od_queue_contention_rel(void) {
  return "compiler/runtime_queue_contention.o";
}

/* wave118: net UNDEF table + needs_std_net pure orch. PLATFORM: SHARED.
 * Count 34: +new/smoke/acquire/release unique tcp_pool wrappers + net_resolve_ipv4/ipv6_ex_c (9.1.7). */
int labi_od_net_sym_count(void) { return 34; }
const char *labi_od_net_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_net_listen";
  if (i == 1)
    return "std_net_connect";
  if (i == 2)
    return "std_net_udp_bind";
  if (i == 3)
    return "std_net_udp_recv_many_buf";
  if (i == 4)
    return "std_net_udp_send_many_buf";
  if (i == 5)
    return "std_net_addr_to_u32";
  if (i == 6)
    return "std_net_close_udp";
  if (i == 7)
    return "net_stream_write_batch_c";
  if (i == 8)
    return "net_tcp_connect_c";
  if (i == 9)
    return "net_tcp_listen_c";
  if (i == 10)
    return "net_udp_bind_c";
  if (i == 11)
    return "net_udp_recv_many_buf_c";
  if (i == 12)
    return "net_udp_send_many_buf_c";
  if (i == 13)
    return "net_close_socket_c";
  if (i == 14)
    return "net_udp_send_c";
  if (i == 15)
    return "net_dns_resolve_c";
  if (i == 16)
    return "net_sock_create_c";
  /*
   * wave956: std.net cookbook on_demand probes (resolve_ex / resolve_err_* /
   * close_stream / connect_blocking / write_batch / tcp_pool_*). Before
   * wave956: 4 cookbook examples hit BLD001 UNDEF because needs_std_net
   * probe table did not include these symbols. Probe shape: net.resolve_ex /
   * net.resolve_err_* / net.close_stream / net.connect_blocking /
   * net.write_batch / net.tcp_pool_* codegen to std_net_* mangled symbols
   * in net.o. Twin of labi_od_thread_sym_* (wave956) for std_thread_stats.
   * G.7: complete the single net probe table — no second path.
   * PLATFORM: SHARED.
   */
  if (i == 17)
    return "std_net_resolve_ex";
  if (i == 18)
    return "std_net_resolve_err_host_not_found";
  if (i == 19)
    return "std_net_resolve_err_no_data";
  if (i == 20)
    return "std_net_close_stream";
  if (i == 21)
    return "std_net_connect_blocking";
  if (i == 22)
    return "std_net_write_batch";
  if (i == 23)
    return "std_net_tcp_pool_connect_count";
  if (i == 24)
    return "std_net_tcp_pool_destroy";
  if (i == 25)
    return "std_net_tcp_pool_drain";
  if (i == 26)
    return "std_net_tcp_pool_idle_count";
  /* PLATFORM: SHARED — cookbook net_listen_bind unique close_listener.
   * listen already fires need_net; matcher is exact so close_listener-only
   * user.o would miss. G.7 complete the single net probe table. */
  if (i == 27)
    return "std_net_close_listener";
  /* PLATFORM: SHARED — tcp_pool unique wrappers (new/smoke/acquire/release).
   * Twin of labi_ondemand_list.x. Matcher is exact. */
  if (i == 28)
    return "std_net_tcp_pool_new";
  if (i == 29)
    return "std_net_tcp_pool_smoke";
  if (i == 30)
    return "std_net_tcp_pool_acquire";
  if (i == 31)
    return "std_net_tcp_pool_release";
  /* Cap residual 9.1.7: DNS raw resolve face. */
  if (i == 32)
    return "net_resolve_ipv4_ex_c";
  if (i == 33)
    return "net_resolve_ipv6_ex_c";
  return NULL;
}

/* Pure orch: table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_net(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_net_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_net_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/*
 * wave956: std.thread on_demand probe table + needs_std_thread pure orch.
 * Before wave956: asm on_demand only pushed thread.o inside need_net block;
 * user programs importing only std.thread never got thread.o. Twin of
 * labi_od_net_sym_* / link_abi_user_o_needs_std_net. PLATFORM: SHARED.
 */
int labi_od_thread_sym_count(void) { return 4; }
const char *labi_od_thread_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_thread_create";
  if (i == 1)
    return "std_thread_join";
  if (i == 2)
    return "std_thread_start";
  if (i == 3)
    return "std_thread_stats";
  return NULL;
}

int link_abi_user_o_needs_std_thread(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_thread_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_thread_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/*
 * wave958: std.vec on_demand probe table + needs_std_vec pure orch.
 * Twin of labi_od_thread_sym_* / link_abi_user_o_needs_std_thread.
 * PLATFORM: SHARED.
 */
int labi_od_vec_sym_count(void) { return 44; }
const char *labi_od_vec_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_vec_push_Vec_u16_ptr_u16";
  if (i == 1)
    return "std_vec_push_Vec_i32_ptr_i32";
  if (i == 2)
    return "std_vec_push_Vec_u8_ptr_u8";
  if (i == 3)
    return "std_vec_get_Vec_u16_i32";
  if (i == 4)
    return "std_vec_length_Vec_u16";
  if (i == 5)
    return "std_vec_deinit_Vec_u16_ptr";
  if (i == 6)
    return "std_vec_get_Vec_i32_i32";
  if (i == 7)
    return "std_vec_length_Vec_i32";
  if (i == 8)
    return "std_vec_deinit_Vec_i32_ptr";
  if (i == 9)
    return "std_vec_from_slice_u8_ptr_i32";
  if (i == 10)
    return "std_vec_capacity_Vec_u8";
  if (i == 11)
    return "std_vec_clear_Vec_u8_ptr";
  /* PLATFORM: SHARED — exact UNDEF needles for pop/extend/from_slice_u64/f64
   * (mirror list.x). from_slice_u8 does not cover sole from_slice_u64/f64. */
  if (i == 12)
    return "std_vec_pop_Vec_i32_ptr";
  if (i == 13)
    return "std_vec_pop_Vec_u8_ptr";
  if (i == 14)
    return "std_vec_extend_Vec_i32_ptr_i32_ptr_i32";
  if (i == 15)
    return "std_vec_extend_Vec_u8_ptr_u8_ptr_i32";
  if (i == 16)
    return "std_vec_extend_Vec_u64_ptr_u64_ptr_i32";
  if (i == 17)
    return "std_vec_extend_Vec_f64_ptr_f64_ptr_i32";
  if (i == 18)
    return "std_vec_from_slice_u64_ptr_i32";
  if (i == 19)
    return "std_vec_from_slice_f64_ptr_i32";
  /* PLATFORM: SHARED — exact UNDEF needles for push Vec_u64/f64
   * (mirror list.x). push_i32/u8/u16 do not cover sole push_u64/f64. */
  if (i == 20)
    return "std_vec_push_Vec_u64_ptr_u64";
  if (i == 21)
    return "std_vec_push_Vec_f64_ptr_f64";
  /* PLATFORM: SHARED — exact UNDEF needles for length/deinit/get Vec_u64/f64
   * (mirror list.x). u16/i32 length/deinit/get do not cover sole
   * new+length / new+deinit on Vec_u64/f64. */
  if (i == 22)
    return "std_vec_length_Vec_u64";
  if (i == 23)
    return "std_vec_deinit_Vec_u64_ptr";
  if (i == 24)
    return "std_vec_length_Vec_f64";
  if (i == 25)
    return "std_vec_deinit_Vec_f64_ptr";
  if (i == 26)
    return "std_vec_get_Vec_u64_i32";
  if (i == 27)
    return "std_vec_get_Vec_f64_i32";
  /* PLATFORM: SHARED — exact UNDEF needles for Vec3f SOA/AOS
   * (mirror list.x). Vec_* push/length/deinit do not cover unique
   * names vec3f_soa_push / vec3f_aos_deinit / reserve_one / sum_x. */
  if (i == 28)
    return "std_vec_vec3f_soa_push";
  if (i == 29)
    return "std_vec_vec3f_soa_deinit";
  if (i == 30)
    return "std_vec_vec3f_aos_push";
  if (i == 31)
    return "std_vec_vec3f_aos_deinit";
  if (i == 32)
    return "std_vec_vec3f_soa_sum_x";
  if (i == 33)
    return "std_vec_vec3f_soa_reserve_one";
  if (i == 34)
    return "std_vec_vec3f_soa_len";
  if (i == 35)
    return "std_vec_vec3f_soa_get_x";
  if (i == 36)
    return "std_vec_vec3f_soa_get_y";
  if (i == 37)
    return "std_vec_vec3f_soa_get_z";
  if (i == 38)
    return "std_vec_vec3f_soa_set";
  if (i == 39)
    return "std_vec_vec3f_soa_with_capacity";
  if (i == 40)
    return "std_vec_vec3f_aos_reserve_one";
  if (i == 41)
    return "std_vec_vec3f_aos_get_x";
  if (i == 42)
    return "std_vec_vec3f_aos_sum_x";
  if (i == 43)
    return "std_vec_vec3f_aos_with_capacity";
  return NULL;
}

int link_abi_user_o_needs_std_vec(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_vec_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_vec_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/*
 * wave958: std.http on_demand probe table + needs_std_http pure orch.
 * Twin of labi_od_thread_sym_* / link_abi_user_o_needs_std_thread.
 * PLATFORM: SHARED.
 */
int labi_od_http_sym_count(void) { return 5; }
const char *labi_od_http_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_http_parse_status_line";
  if (i == 1)
    return "std_http_decode_chunked_body";
  if (i == 2)
    return "std_http_has_chunked_encoding";
  if (i == 3)
    return "std_http_has_keep_alive";
  if (i == 4)
    return "std_http_headers_body_offset";
  return NULL;
}

int link_abi_user_o_needs_std_http(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_http_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_http_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave119: set UNDEF table + needs_std_set pure orch. PLATFORM: SHARED. */
int labi_od_set_sym_count(void) { return 20; }
const char *labi_od_set_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_set_new_i32_retSet_i32";
  if (i == 1)
    return "std_set_new_i32_retSet_u64";
  if (i == 2)
    return "std_set_with_capacity_Set_i32_ptr_i32";
  if (i == 3)
    return "std_set_insert_Set_i32_ptr_i32";
  if (i == 4)
    return "std_set_insert_Set_u64_ptr_u64";
  if (i == 5)
    return "std_set_contains_key_Set_i32_i32";
  if (i == 6)
    return "std_set_contains_key_Set_u64_u64";
  if (i == 7)
    return "std_set_remove_Set_i32_ptr_i32";
  if (i == 8)
    return "std_set_remove_Set_u64_ptr_u64";
  if (i == 9)
    return "std_set_length_Set_i32";
  if (i == 10)
    return "std_set_length_Set_u64";
  if (i == 11)
    return "std_set_deinit_Set_i32_ptr";
  if (i == 12)
    return "std_set_deinit_Set_u64_ptr";
  if (i == 13)
    return "std_set_str_new";
  if (i == 14)
    return "std_set_str_insert";
  /* Legacy / alternate mangles. */
  if (i == 15)
    return "std_set_set_i32_insert";
  if (i == 16)
    return "std_set_set_i32_contains";
  if (i == 17)
    return "std_set_set_i32_remove";
  if (i == 18)
    return "std_set_set_i32_len";
  if (i == 19)
    return "std_set_set_i32_deinit";
  return NULL;
}

/* Pure orch: table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_set(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_set_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_set_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave120: map UNDEF table + needs_std_map pure orch. PLATFORM: SHARED. */
int labi_od_map_sym_count(void) { return 15; }
const char *labi_od_map_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_map_empty_size";
  if (i == 1)
    return "std_map_new_Map_i32_i32";
  if (i == 2)
    return "std_map_with_capacity_Map_i32_i32_ptr_i32";
  if (i == 3)
    return "std_map_insert_Map_i32_i32_ptr_i32_i32";
  if (i == 4)
    return "std_map_get_Map_i32_i32_i32";
  if (i == 5)
    return "std_map_find_Map_i32_i32_i32";
  if (i == 6)
    return "std_map_deinit_Map_i32_i32_ptr";
  if (i == 7)
    return "std_map_str_new";
  if (i == 8)
    return "std_map_str_insert";
  /*
   * wave957: Map<u64, i32> on_demand probes. Before wave957: probe table only
   * had Map_i32_i32 + str variants; user programs using Map<u64, i32> hit
   * BLD001 UNDEF because needs_std_map probe never fired. G.7: complete the
   * single map probe table. PLATFORM: SHARED.
   */
  if (i == 9)
    return "std_map_new_u64";
  if (i == 10)
    return "std_map_with_capacity_Map_u64_i32_ptr_i32";
  if (i == 11)
    return "std_map_insert_Map_u64_i32_ptr_u64_i32";
  if (i == 12)
    return "std_map_get_Map_u64_i32_u64_i32";
  if (i == 13)
    return "std_map_remove_Map_u64_i32_ptr_u64";
  if (i == 14)
    return "std_map_deinit_Map_u64_i32_ptr";
  return NULL;
}

/* Pure orch: table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_map(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_map_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_map_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave121: product queue UNDEF table + needs_std_queue pure orch.
 * PLATFORM: SHARED — separate from contention labi_od_queue_sym_* (3 smoke/os symbols). */
int labi_od_queue_api_sym_count(void) { return 12; }
const char *labi_od_queue_api_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_queue_new_retQueue_i32";
  if (i == 1)
    return "std_queue_new_retQueue_u8";
  if (i == 2)
    return "std_queue_push_back_Queue_i32_ptr_i32";
  if (i == 3)
    return "std_queue_push_back_Queue_u8_ptr_u8";
  if (i == 4)
    return "std_queue_push_front";
  if (i == 5)
    return "std_queue_pop_front_Queue_i32_ptr";
  if (i == 6)
    return "std_queue_pop_back";
  if (i == 7)
    return "std_queue_get";
  if (i == 8)
    return "std_queue_length_Queue_i32";
  if (i == 9)
    return "std_queue_is_empty_Queue_i32";
  if (i == 10)
    return "std_queue_deinit_Queue_i32_ptr";
  if (i == 11)
    return "std_queue_with_capacity";
  return NULL;
}

/* Pure orch: product table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_queue(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_queue_api_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_queue_api_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave122: product test UNDEF/prefix table + needs_std_test pure orch.
 * PLATFORM: SHARED — prefixes (test_runner_ etc.) use Cap residual strstr in undef_sym. */
int labi_od_test_sym_count(void) { return 7; }
const char *labi_od_test_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "test_call_i32_void_c";
  if (i == 1)
    return "test_runner_";
  if (i == 2)
    return "test_expect_";
  if (i == 3)
    return "test_bench_";
  if (i == 4)
    return "test_f_test_";
  if (i == 5)
    return "test_io_";
  if (i == 6)
    return "test_fuzz_";
  return NULL;
}

/* Pure orch: test table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_test(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_test_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_test_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave123 + CORE-017: product core.mem exact UNDEF table + needs_core_mem pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes).
 * Was 7 (align/mem_* only): sole volatile/fence UNDEF never opened mem.o → BLD001.
 * Count 31 = full core/mem/mod.x export surface (G.7 one table; seed twin of .x). */
int labi_od_core_mem_sym_count(void) { return 31; }
const char *labi_od_core_mem_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "core_mem_align_up";
  if (i == 1)
    return "core_mem_align_down";
  if (i == 2)
    return "core_mem_mem_copy";
  if (i == 3)
    return "core_mem_mem_set";
  if (i == 4)
    return "core_mem_mem_zero";
  if (i == 5)
    return "core_mem_mem_move";
  if (i == 6)
    return "core_mem_mem_compare";
  if (i == 7)
    return "core_mem_mem_swap";
  if (i == 8)
    return "core_mem_is_alignment_power_of_two";
  if (i == 9)
    return "core_mem_placeholder";
  if (i == 10)
    return "core_mem_align_of_i32";
  if (i == 11)
    return "core_mem_align_of_bool";
  if (i == 12)
    return "core_mem_align_of_u8";
  if (i == 13)
    return "core_mem_align_of_u32";
  if (i == 14)
    return "core_mem_align_of_u64";
  if (i == 15)
    return "core_mem_align_of_i64";
  if (i == 16)
    return "core_mem_align_of_usize";
  if (i == 17)
    return "core_mem_align_of_isize";
  if (i == 18)
    return "core_mem_align_of_f32";
  if (i == 19)
    return "core_mem_align_of_f64";
  if (i == 20)
    return "core_mem_align_of_pointer";
  if (i == 21)
    return "core_mem_volatile_load_u8";
  if (i == 22)
    return "core_mem_volatile_store_u8";
  if (i == 23)
    return "core_mem_volatile_load_u16";
  if (i == 24)
    return "core_mem_volatile_store_u16";
  if (i == 25)
    return "core_mem_volatile_load_u32";
  if (i == 26)
    return "core_mem_volatile_store_u32";
  if (i == 27)
    return "core_mem_compiler_fence";
  if (i == 28)
    return "core_mem_fence_acquire";
  if (i == 29)
    return "core_mem_fence_release";
  if (i == 30)
    return "core_mem_fence_seq_cst";
  return NULL;
}

/* Pure orch: core_mem table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_core_mem(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_core_mem_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_core_mem_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave124: product core.slice exact UNDEF table + needs_core_slice pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_core_slice_sym_count(void) { return 9; }
const char *labi_od_core_slice_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "core_slice_i32_from_ptr_c";
  if (i == 1)
    return "core_subslice_i32_c";
  if (i == 2)
    return "core_slice_u8_from_ptr_c";
  if (i == 3)
    return "core_subslice_u8_c";
  if (i == 4)
    return "core_slice_u64_from_ptr_c";
  if (i == 5)
    return "core_subslice_u64_c";
  /*
   * wave957: core.slice X-facing u64 on_demand probes (chunks_len / split_at /
   * subslice). Before wave957: probe table only had C-bridge _c suffix symbols;
   * user programs calling slice.chunks_len / slice.split_at / slice.subslice
   * with u64 codegen to core_slice_*_u64 (X-facing, no _c) which didn't match.
   * G.7: complete the single core_slice probe table. PLATFORM: SHARED.
   */
  if (i == 6)
    return "core_slice_chunks_len_u64";
  if (i == 7)
    return "core_slice_split_at_u64";
  if (i == 8)
    return "core_slice_subslice_u64";
  return NULL;
}

/* Pure orch: core_slice table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_core_slice(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_core_slice_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_core_slice_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave125: product std.heap.page_mmap exact UNDEF table + needs_std_heap_page_mmap pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_page_mmap_sym_count(void) { return 5; }
const char *labi_od_page_mmap_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_heap_page_mmap_page_mmap_heap_available";
  if (i == 1)
    return "std_heap_page_mmap_page_mmap_heap_init";
  if (i == 2)
    return "std_heap_page_mmap_page_mmap_heap_alloc";
  if (i == 3)
    return "std_heap_page_mmap_page_mmap_heap_deinit";
  if (i == 4)
    return "std_heap_page_mmap_page_mmap_heap_free";
  return NULL;
}

/* Pure orch: page_mmap table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_heap_page_mmap(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_page_mmap_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_page_mmap_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* product sys_linux exact UNDEF table + needs pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_sys_linux_sym_count(void) { return 34; }
const char *labi_od_sys_linux_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_sys_linux_linux_syscall_nr_read_amd64";
  if (i == 1)
    return "std_sys_linux_linux_syscall_nr_write_amd64";
  if (i == 2)
    return "std_sys_linux_linux_syscall_nr_open_amd64";
  if (i == 3)
    return "std_sys_linux_linux_syscall_nr_close_amd64";
  if (i == 4)
    return "std_sys_linux_linux_syscall_nr_exit_amd64";
  if (i == 5)
    return "std_sys_linux_linux_syscall_nr_mmap_amd64";
  if (i == 6)
    return "std_sys_linux_linux_syscall_nr_read_arm64";
  if (i == 7)
    return "std_sys_linux_linux_syscall_nr_write_arm64";
  if (i == 8)
    return "std_sys_linux_linux_syscall_nr_openat_arm64";
  if (i == 9)
    return "std_sys_linux_linux_syscall_nr_close_arm64";
  if (i == 10)
    return "std_sys_linux_linux_syscall_nr_exit_arm64";
  if (i == 11)
    return "std_sys_linux_linux_syscall_nr_mmap_arm64";
  if (i == 12)
    return "std_sys_linux_linux_syscall_table_available";
  if (i == 13)
    return "std_sys_linux_linux_syscall_invoke_available";
  if (i == 14)
    return "std_sys_linux_linux_syscall_read";
  if (i == 15)
    return "std_sys_linux_linux_syscall_close";
  if (i == 16)
    return "std_sys_linux_linux_syscall_write";
  if (i == 17)
    return "std_sys_linux_linux_syscall_exit";
  if (i == 18)
    return "std_sys_linux_linux_syscall_openat";
  if (i == 19)
    return "std_sys_linux_linux_anonymous_mmap";
  if (i == 20)
    return "std_sys_linux_linux_syscall_munmap";
  if (i == 21)
    return "std_sys_linux_linux_read_file_openat";
  if (i == 22)
    return "std_sys_linux_linux_syscall_open";
  if (i == 23)
    return "std_sys_linux_linux_read_file_into";
  if (i == 24)
    return "std_sys_linux_linux_syscall_socket";
  if (i == 25)
    return "std_sys_linux_linux_syscall_connect";
  if (i == 26)
    return "std_sys_linux_linux_syscall_bind";
  if (i == 27)
    return "std_sys_linux_linux_syscall_listen";
  if (i == 28)
    return "std_sys_linux_linux_syscall_accept";
  if (i == 29)
    return "std_sys_linux_linux_mmap_rw";
  if (i == 30)
    return "std_sys_linux_linux_munmap";
  if (i == 31)
    return "std_sys_linux_linux_msync_sync";
  if (i == 32)
    return "std_sys_linux_linux_mmap_file_available";
  if (i == 33)
    return "std_sys_linux_linux_sys_module_anchor";
  return NULL;
}

int link_abi_user_o_needs_std_sys_linux(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_sys_linux_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_sys_linux_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* product sys_macos exact UNDEF table + needs pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_sys_macos_sym_count(void) { return 13; }
const char *labi_od_sys_macos_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_sys_macos_macos_exit";
  if (i == 1)
    return "std_sys_macos_macos_write_available";
  if (i == 2)
    return "std_sys_macos_macos_write";
  if (i == 3)
    return "std_sys_macos_macos_write_stdout";
  if (i == 4)
    return "std_sys_macos_macos_write_stderr";
  if (i == 5)
    return "std_sys_macos_macos_read";
  if (i == 6)
    return "std_sys_macos_macos_close";
  if (i == 7)
    return "std_sys_macos_macos_read_file_into";
  if (i == 8)
    return "std_sys_macos_macos_anonymous_mmap";
  if (i == 9)
    return "std_sys_macos_macos_munmap";
  if (i == 10)
    return "std_sys_macos_macos_mmap_available";
  if (i == 11)
    return "std_sys_macos_macos_mmap_rw";
  if (i == 12)
    return "std_sys_macos_macos_msync_sync";
  return NULL;
}

int link_abi_user_o_needs_std_sys_macos(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_sys_macos_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_sys_macos_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave127: product std.sys facade exact UNDEF table + needs_std_sys pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_sys_sym_count(void) { return 8; }
const char *labi_od_sys_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_sys_write_stdout";
  if (i == 1)
    return "std_sys_write_stderr";
  if (i == 2)
    return "std_sys_write";
  if (i == 3)
    return "std_sys_read";
  if (i == 4)
    return "std_sys_close";
  if (i == 5)
    return "std_sys_exit";
  if (i == 6)
    return "std_sys_freestanding_write_available";
  if (i == 7)
    return "std_sys_linux_syscall_table_available";
  return NULL;
}

/* Pure orch: sys table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_sys(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_sys_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_sys_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave128: product std.heap formal API exact UNDEF table + needs_std_heap_api pure orch.
 * PLATFORM: SHARED — exact symbols only (no prefix/strstr probes). */
int labi_od_heap_api_sym_count(void) { return 30; }
const char *labi_od_heap_api_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_heap_alloc_i32";
  if (i == 1)
    return "std_heap_alloc_u8";
  if (i == 2)
    return "std_heap_free_i32";
  if (i == 3)
    return "std_heap_free_u8";
  if (i == 4)
    return "std_heap_alloc_size_zero";
  if (i == 5)
    return "std_heap_alloc_usize";
  if (i == 6)
    return "std_heap_free_u8_ptr";
  if (i == 7)
    return "std_heap_default_alloc";
  if (i == 8)
    return "std_heap_kind_arena";
  if (i == 9)
    return "std_heap_alloc_Allocator_usize";
  if (i == 10)
    return "std_heap_realloc_Allocator_u8_ptr_usize";
  if (i == 11)
    return "std_heap_free_Allocator_u8_ptr";
  if (i == 12)
    return "std_heap_arena64_alloc";
  if (i == 13)
    return "std_heap_libc_heap_arena64_alloc_c";
  if (i == 14)
    return "std_heap_libc_heap_alloc_c";
  if (i == 15)
    return "std_heap_libc_heap_free_c";
  if (i == 16)
    return "std_heap_libc_heap_alloc_aligned_c";
  if (i == 17)
    return "std_heap_libc_heap_alloc_i32_c";
  if (i == 18)
    return "std_heap_libc_heap_alloc_u8_c";
  if (i == 19)
    return "std_heap_libc_heap_alloc_u64_c";
  if (i == 20)
    return "std_heap_libc_heap_free_i32_c";
  if (i == 21)
    return "std_heap_libc_heap_free_u8_c";
  if (i == 22)
    return "std_heap_libc_heap_free_u64_c";
  if (i == 23)
    return "std_heap_map_find";
  if (i == 24)
    return "std_heap_libc_heap_copy_u8_at_c";
  /*
   * wave957: std.heap trace on_demand probes (trace_on / trace_reset). Before
   * wave957: probe table had alloc/free/Allocator/libc surface but not trace
   * symbols; user programs calling heap.trace_on / heap.trace_reset hit
   * BLD001 UNDEF. G.7: complete the single heap probe table. PLATFORM: SHARED.
   */
  if (i == 25)
    return "std_heap_trace_on";
  if (i == 26)
    return "std_heap_trace_reset";
  /*
   * zc_arena_concat unique UNDEF: import METHOD arena64_empty / init / deinit.
   * Before this leaf: table had arena64_alloc (vec grow) but matcher is exact,
   * so empty/init/deinit never fired needs_std_heap_api. heap.o already
   * defines the three T names (mod.x). string.o is pulled by g0 view and
   * injects T libc arena64_*_c, so string cannot pull heap as a side effect.
   * G.7: complete this single heap probe table. Do not add a second group.
   * PLATFORM: SHARED.
   */
  if (i == 27)
    return "std_heap_arena64_empty";
  if (i == 28)
    return "std_heap_arena64_init";
  if (i == 29)
    return "std_heap_arena64_deinit";
  return NULL;
}

/* Pure orch: heap_api table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_std_heap_api(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_heap_api_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_heap_api_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave129: product runtime_heap_user exact UNDEF table + needs_heap_user_syms pure orch.
 * PLATFORM: SHARED — exact symbols only; product complete includes with_arena init/deinit. */
int labi_od_heap_user_sym_count(void) { return 7; }
const char *labi_od_heap_user_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "heap_alloc_c";
  if (i == 1)
    return "heap_free_c";
  if (i == 2)
    return "heap_realloc_c";
  if (i == 3)
    return "heap_arena64_alloc_c";
  if (i == 4)
    return "heap_arena_init_c";
  if (i == 5)
    return "heap_arena64_deinit_c";
  if (i == 6)
    return "heap_arena64_init_c";
  return NULL;
}

/* Pure orch: heap_user table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_heap_user_syms(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_heap_user_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_heap_user_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave130: product async scheduler exact UNDEF table + needs_async_scheduler pure orch.
 * PLATFORM: SHARED — exact symbols only; product complete coop/cps/frame/run/task/worker/io. */
int labi_od_async_scheduler_sym_count(void) { return 35; }
const char *labi_od_async_scheduler_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "xlang_async_coop_pingpong";
  if (i == 1)
    return "xlang_async_coop_pingpong_jmp";
  if (i == 2)
    return "xlang_async_cps_suspend";
  if (i == 3)
    return "xlang_async_asm_frame_phase_by_id";
  if (i == 4)
    return "xlang_async_asm_frame_store_from_ptr";
  if (i == 5)
    return "xlang_async_asm_frame_load_to_ptr";
  if (i == 6)
    return "xlang_async_asm_frame_reset_by_id";
  if (i == 7)
    return "xlang_async_cps_suspend_io";
  if (i == 8)
    return "xlang_async_run_i32";
  if (i == 9)
    return "xlang_async_task_submit";
  if (i == 10)
    return "xlang_async_task_submit_to";
  if (i == 11)
    return "xlang_async_scheduler_drain";
  if (i == 12)
    return "xlang_async_worker_drain";
  if (i == 13)
    return "xlang_async_worker_count";
  if (i == 14)
    return "xlang_async_worker_pending";
  if (i == 15)
    return "xlang_async_queue_reset";
  if (i == 16)
    return "xlang_async_scheduler_pending";
  if (i == 17)
    return "xlang_async_io_wake_all";
  if (i == 18)
    return "xlang_async_io_waiters_pending";
  if (i == 19)
    return "xlang_async_io_completions_ready";
  if (i == 20)
    return "xlang_async_run_seed_set_i32";
  if (i == 21)
    return "xlang_async_run_seed_reset";
  if (i == 22)
    return "xlang_async_run_seed_push_i32";
  if (i == 23)
    return "xlang_async_run_seed_push_u32";
  if (i == 24)
    return "xlang_async_run_seed_push_i64";
  if (i == 25)
    return "xlang_async_run_seed_valid";
  if (i == 26)
    return "xlang_async_run_seed_take_i32";
  if (i == 27)
    return "xlang_async_run_seed_take_u32";
  if (i == 28)
    return "xlang_async_run_seed_take_i64";
  if (i == 29)
    return "xlang_io_submit_read_async";
  if (i == 30)
    return "xlang_io_complete_read_async";
  if (i == 31)
    return "xlang_io_complete_read_async_slot";
  if (i == 32)
    return "xlang_io_submit_write_async";
  if (i == 33)
    return "xlang_io_complete_write_async";
  if (i == 34)
    return "xlang_io_complete_write_async_slot";
  return NULL;
}

/* Pure orch: async_scheduler table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_async_scheduler(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_async_scheduler_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_async_scheduler_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave131: product compress family marker + UNDEF/prefix tables + pure orch.
 * PLATFORM: SHARED — Cap residual exports_marker + has_undef_sym (popen/nm). */
int labi_od_zlib_undef_sym_count(void) { return 16; }
const char *labi_od_zlib_undef_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "_compress2";
  if (i == 1)
    return "_deflate";
  if (i == 2)
    return "_inflate";
  if (i == 3)
    return "_uncompress";
  /* PLATFORM: LINUX — ELF nm U compress2 (exact; Mach-O needles keep _prefix). */
  if (i == 4)
    return "compress2";
  if (i == 5)
    return "deflate";
  if (i == 6)
    return "inflate";
  if (i == 7)
    return "uncompress";
  /* gzip Init2 + Darwin product mangle: gzip-only import has no _compress2. */
  if (i == 8)
    return "_deflateInit2";
  if (i == 9)
    return "_inflateInit2";
  if (i == 10)
    return "_std_compress_gzip_gzip_compress";
  if (i == 11)
    return "_std_compress_gzip_gzip_decompress";
  if (i == 12)
    return "deflateInit2";
  if (i == 13)
    return "inflateInit2";
  if (i == 14)
    return "std_compress_gzip_gzip_compress";
  if (i == 15)
    return "std_compress_gzip_gzip_decompress";
  return NULL;
}
const char *labi_od_compress_zlib_marker(void) { return "xlang_compress_zlib_marker"; }

int labi_od_zstd_undef_sym_count(void) { return 2; }
const char *labi_od_zstd_undef_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "ZSTD_";
  if (i == 1)
    return "_ZSTD";
  return NULL;
}
const char *labi_od_compress_zstd_marker(void) { return "xlang_compress_zstd_marker"; }

int labi_od_brotli_undef_sym_count(void) { return 2; }
const char *labi_od_brotli_undef_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "BrotliEncoderCompress";
  if (i == 1)
    return "BrotliDecoderDecompress";
  return NULL;
}
const char *labi_od_compress_brotli_marker(void) { return "xlang_compress_brotli_marker"; }

/* Pure orch: zlib marker + exact UNDEF table + Cap residual. PLATFORM: SHARED. */
int link_abi_obj_needs_zlib(const char *obj_o) {
  int n;
  int i;
  const char *marker;
  if (!obj_o || !obj_o[0])
    return 0;
  marker = labi_od_compress_zlib_marker();
  if (marker && marker[0] && link_abi_obj_exports_marker(obj_o, marker) != 0)
    return 1;
  n = labi_od_zlib_undef_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_zlib_undef_sym_at(i);
    if (sym && sym[0] && link_abi_obj_has_undef_sym(obj_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* Pure orch: zstd marker + prefix needles + Cap residual. PLATFORM: SHARED. */
int link_abi_obj_needs_zstd(const char *obj_o) {
  int n;
  int i;
  const char *marker;
  if (!obj_o || !obj_o[0])
    return 0;
  marker = labi_od_compress_zstd_marker();
  if (marker && marker[0] && link_abi_obj_exports_marker(obj_o, marker) != 0)
    return 1;
  n = labi_od_zstd_undef_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_zstd_undef_sym_at(i);
    if (sym && sym[0] && link_abi_obj_has_undef_sym(obj_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* Pure orch: brotli marker + exact UNDEF table + Cap residual. PLATFORM: SHARED. */
int link_abi_obj_needs_brotli(const char *obj_o) {
  int n;
  int i;
  const char *marker;
  if (!obj_o || !obj_o[0])
    return 0;
  marker = labi_od_compress_brotli_marker();
  if (marker && marker[0] && link_abi_obj_exports_marker(obj_o, marker) != 0)
    return 1;
  n = labi_od_brotli_undef_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_brotli_undef_sym_at(i);
    if (sym && sym[0] && link_abi_obj_has_undef_sym(obj_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* Pure orch: OR of three compress leaves. PLATFORM: SHARED. */
int link_abi_user_o_needs_compress_libs(const char *user_o) {
  if (link_abi_obj_needs_zlib(user_o) != 0)
    return 1;
  if (link_abi_obj_needs_zstd(user_o) != 0)
    return 1;
  if (link_abi_obj_needs_brotli(user_o) != 0)
    return 1;
  return 0;
}

/* wave132–134: bulk PRIMARY OS + TASK_SPECIAL pure tables + orch.
 * PLATFORM: SHARED — exact symbols only; null/empty user_o → 1 legacy hard-link.
 * wave133: process_argv pure; wave134: std_task pure (single-leaf after capacity clip). */
int labi_od_runtime_time_os_sym_count(void) { return 10; }
const char *labi_od_runtime_time_os_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "time_now_monotonic_ns_c";
  if (i == 1)
    return "time_now_wall_ns_c";
  if (i == 2)
    return "time_sleep_ns_c";
  if (i == 3)
    return "time_format_wall_rfc3339_c";
  if (i == 4)
    return "time_wall_local_offset_min_c";
  if (i == 5)
    return "std_time_now_monotonic_ns";
  if (i == 6)
    return "std_time_now_wall_ns";
  if (i == 7)
    return "std_time_sleep_ms";
  if (i == 8)
    return "std_time_timer_start";
  if (i == 9)
    return "std_time_duration_ns";
  return NULL;
}
int labi_user_needs_runtime_time_os(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_od_runtime_time_os_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_runtime_time_os_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

int labi_od_runtime_random_fill_sym_count(void) { return 12; }
const char *labi_od_runtime_random_fill_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "random_fill_bytes_c";
  if (i == 1)
    return "std_random_fill_bytes";
  if (i == 2)
    return "std_random_fill";
  if (i == 3)
    return "std_random_next";
  if (i == 4)
    return "std_random_range_u32_u32";
  if (i == 5)
    return "std_random_gen";
  if (i == 6)
    return "std_random_flip";
  if (i == 7)
    return "std_random_rng_smoke";
  if (i == 8)
    return "std_random_seed";
  if (i == 9)
    return "random_u32_c";
  if (i == 10)
    return "random_u64_c";
  if (i == 11)
    return "random_rng_smoke_c";
  return NULL;
}
int labi_user_needs_runtime_random_fill(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_od_runtime_random_fill_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_runtime_random_fill_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

int labi_od_runtime_env_os_sym_count(void) { return 19; }
const char *labi_od_runtime_env_os_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "env_getenv_c";
  if (i == 1)
    return "env_getenv_exists_c";
  if (i == 2)
    return "env_getenv_z_c";
  if (i == 3)
    return "env_getenv_ptr_c";
  if (i == 4)
    return "env_setenv_c";
  if (i == 5)
    return "env_unsetenv_c";
  if (i == 6)
    return "env_temp_dir_c";
  if (i == 7)
    return "env_iter_count_c";
  if (i == 8)
    return "env_iter_at_c";
  if (i == 9)
    return "std_env_getenv";
  if (i == 10)
    return "std_env_getenv_exists";
  if (i == 11)
    return "std_env_getenv_z";
  if (i == 12)
    return "std_env_getenv_ptr";
  if (i == 13)
    return "std_env_setenv";
  if (i == 14)
    return "std_env_unsetenv";
  if (i == 15)
    return "std_env_temp_dir";
  if (i == 16)
    return "std_env_iter";
  if (i == 17)
    return "std_env_iter_count";
  if (i == 18)
    return "std_env_args_iter";
  return NULL;
}
int labi_user_needs_runtime_env_os(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_od_runtime_env_os_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_runtime_env_os_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave133: process_argv pure table + orch (5 needles).
 * PLATFORM: SHARED — product std_process_* is fk==1 → process.o (not process_argv).
 * Twin of labi_ondemand_list.x (G.7 seed/.x same commit). */
int labi_od_runtime_process_argv_sym_count(void) { return 5; }
const char *labi_od_runtime_process_argv_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "process_xlang_argc_get";
  if (i == 1)
    return "process_xlang_argv_get";
  if (i == 2)
    return "process_arg_c";
  if (i == 3)
    return "process_args_count_c";
  if (i == 4)
    return "std_env_args_iter";
  return NULL;
}
int labi_user_needs_runtime_process_argv(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_od_runtime_process_argv_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_runtime_process_argv_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave134: std_task pure table + orch (29 needles; TASK_SPECIAL). */
int labi_od_std_task_sym_count(void) { return 29; }
const char *labi_od_std_task_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_task_new";
  if (i == 1)
    return "std_task_free";
  if (i == 2)
    return "std_task_bind";
  if (i == 3)
    return "std_task_spawn";
  if (i == 4)
    return "std_task_join";
  if (i == 5)
    return "std_task_pending";
  if (i == 6)
    return "std_task_check_leak";
  if (i == 7)
    return "std_task_cancel";
  if (i == 8)
    return "std_task_total";
  if (i == 9)
    return "std_task_set_new";
  if (i == 10)
    return "std_task_set_free";
  if (i == 11)
    return "std_task_set_spawn";
  if (i == 12)
    return "std_task_set_join";
  if (i == 13)
    return "std_task_set_check_leak";
  if (i == 14)
    return "std_task_echo";
  if (i == 15)
    return "std_task_echo_ptr";
  if (i == 16)
    return "std_task_retry";
  if (i == 17)
    return "std_task_err_ok";
  if (i == 18)
    return "task_group_create_c";
  if (i == 19)
    return "task_group_spawn_c";
  if (i == 20)
    return "task_group_join_c";
  if (i == 21)
    return "task_group_free_c";
  if (i == 22)
    return "join_set_create_c";
  if (i == 23)
    return "join_set_spawn_c";
  if (i == 24)
    return "join_set_join_c";
  if (i == 25)
    return "task_smoke_c";
  if (i == 26)
    return "task_supervise_retry_c";
  if (i == 27)
    return "task_echo_fn_c";
  if (i == 28)
    return "task_echo_fn_ptr_c";
  return NULL;
}
int labi_user_needs_std_task(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_od_std_task_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_std_task_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}


/* wave135: labi_std_fk0_user_needs_rel pure cold twin (tables + orch).
 * PLATFORM: SHARED — must mirror labi_ondemand_heavy.x (G.7 single authority).
 * Product/cold both hit this TU when PREFER_X_O falls back or FROM_X off.
 * Was return 16 (fs last): ac064cc62/2d8b92871 pure+surface added tar/unicode/
 * runtime but cold twin lagged → Ubuntu product labi_fk0_rel_count still 0x10
 * → never open std/tar/tar.o gate → run-tar UNDEF std_tar_{read,write}_header
 * even when formal tar.o has T surface (soft first-red @bbb6646d0). */
int labi_fk0_rel_count(void) {
  /* PLATFORM: SHARED — was 25; +option +result (=heavy return 27). */
  return 27;
}
const char *labi_fk0_rel_at(int k) {

  if (k == 0)
    return "std/string/string.o";
  if (k == 1)
    return "std/encoding/encoding.o";
  if (k == 2)
    return "std/base64/base64.o";
  if (k == 3)
    return "std/http/http.o";
  if (k == 4)
    return "std/json/json.o";
  if (k == 5)
    return "std/csv/csv.o";
  if (k == 6)
    return "std/path/path.o";
  if (k == 7)
    return "std/hash/hash.o";
  if (k == 8)
    return "std/error/error.o";
  if (k == 9)
    return "std/context/context.o";
  if (k == 10)
    return "std/vec/vec.o";
  if (k == 11)
    return "std/sort/sort.o";
  if (k == 12)
    return "std/env/env.o";
  if (k == 13)
    return "std/random/random.o";
  if (k == 14)
    return "std/time/time.o";
  if (k == 15)
    return "std/fs/fs.o";
  /* PLATFORM: SHARED — mirror heavy k16–18 (pure-asm soft residual class). */
  if (k == 16)
    return "std/tar/tar.o";
  if (k == 17)
    return "std/unicode/unicode.o";
  if (k == 18)
    return "std/runtime/runtime.o";
  /* PLATFORM: SHARED — mirror heavy k19 (cookbook cli_subcommand). */
  if (k == 19)
    return "std/cli/cli.o";
  /* PLATFORM: SHARED — mirror heavy k20 (cookbook datetime_iana). */
  if (k == 20)
    return "std/datetime/datetime.o";
  /* PLATFORM: SHARED — mirror heavy k21 (STD-086 std_config_*). */
  if (k == 21)
    return "std/config/config.o";
  /* PLATFORM: SHARED — mirror heavy k22 (STD-087 std_cache_*). */
  if (k == 22)
    return "std/cache/cache.o";
  /* PLATFORM: SHARED — mirror heavy k23 (STD-076 std_url_*). */
  if (k == 23)
    return "std/url/url.o";
  /* PLATFORM: SHARED — mirror heavy k24 (STD-079 std_security_*). */
  if (k == 24)
    return "std/security/security.o";
  /* PLATFORM: SHARED — mirror heavy k25 (STD-080 std_option_*). */
  if (k == 25)
    return "std/option/option.o";
  /* PLATFORM: SHARED — mirror heavy k26 (STD-081 std_result_*). */
  if (k == 26)
    return "std/result/result.o";
  return NULL;
}

int labi_fk0_sym_count(int k) {

  if (k == 0)
    return 11;
  if (k == 1)
    return 2;
  if (k == 2)
    return 2;
  if (k == 3)
    return 3;
  /* PLATFORM: SHARED — json.o fk0 gate complete (mirror labi_ondemand_heavy.x).
   * Was: parse + dead stringify. Sole parse_null UNDEF never opened gate. */
  if (k == 4)
    return 6;
  if (k == 5)
    return 4;
  /* PLATFORM: SHARED — path.o fk0 complete (mirror labi_ondemand_heavy.x).
   * Was: join/dirname/empty_len/basename only. Sole sep/clean/extension UNDEF
   * never opened gate (run-path extension_stem_abs_clean). */
  if (k == 6)
    return 12;
  if (k == 7)
    return 7;
  /* PLATFORM: SHARED — error.o fk0 complete (mirror heavy.x; was 4).
   * EXC soft SKIP: sole code_invalid/io_err_generic/chain_* never opened gate.
   * G.7: every public std_error_* export ×57. */
  if (k == 8)
    return 57;
  if (k == 9)
    return 4;
  if (k == 10)
    return 42;
  if (k == 11)
    return 9;
  if (k == 12)
    return 11;
  if (k == 13)
    return 12;
  if (k == 14)
    return 15;
  /* PLATFORM: SHARED — fs fk0 complete (mirror heavy.x): +readv_buf/writev_buf +stat +dir_{open,read,close}. */
  if (k == 15)
    return 15;
  /* PLATFORM: SHARED — tar/unicode/runtime formal public surface (mirror heavy). */
  if (k == 16)
    return 7;
  if (k == 17)
    return 6;
  if (k == 18)
    return 5;
  /* PLATFORM: SHARED — cli formal public surface (mirror heavy). */
  if (k == 19)
    return 10;
  /* PLATFORM: SHARED — datetime formal public surface (mirror heavy). */
  if (k == 20)
    return 27;
  /* PLATFORM: SHARED — config formal public surface (mirror heavy). */
  if (k == 21)
    return 31;
  /* PLATFORM: SHARED — cache formal public surface (mirror heavy). */
  if (k == 22)
    return 20;
  /* PLATFORM: SHARED — url formal public surface (mirror heavy). */
  if (k == 23)
    return 10;
  /* PLATFORM: SHARED — security formal public surface (mirror heavy). */
  if (k == 24)
    return 16;
  /* PLATFORM: SHARED — option formal public surface (mirror heavy). */
  if (k == 25)
    return 11;
  /* PLATFORM: SHARED — result formal public surface (mirror heavy). */
  if (k == 26)
    return 11;
  return 0;
}

const char *labi_fk0_sym_at(int k, int i) {
  if (i < 0)
    return NULL;

  if (k == 0) {
    if (i == 0)
      return "std_string_string_empty";
    if (i == 1)
      return "std_string_new";
    if (i == 2)
      return "std_string_length_String";
    if (i == 3)
      return "std_string_length_StrView";
    if (i == 4)
      return "std_string_is_empty_String";
    if (i == 5)
      return "std_string_is_empty_StrView";
    if (i == 6)
      return "std_string_view";
    if (i == 7)
      return "std_string_string_from_slice";
    if (i == 8)
      return "std_string_string_eq";
    if (i == 9)
      return "xlang_string_memcmp_c";
    if (i == 10)
      return "xlang_string_memmem_c";
    return NULL;
  }
  if (k == 1) {
    if (i == 0)
      return "std_encoding_utf8_valid";
    if (i == 1)
      return "std_encoding_ascii_is_alpha";
    return NULL;
  }
  if (k == 2) {
    if (i == 0)
      return "std_base64_encode_standard";
    if (i == 1)
      return "std_base64_decode_standard";
    return NULL;
  }
  if (k == 3) {
    if (i == 0)
      return "std_http_get";
    if (i == 1)
      return "std_http_request";
    if (i == 2)
      return "std_http_client_new";
    return NULL;
  }
  /* PLATFORM: SHARED — exact UNDEF needles for std/json/json.o (k==4).
   * Exact match only; parse does not cover parse_null/number/string. */
  if (k == 4) {
    if (i == 0)
      return "std_json_parse";
    if (i == 1)
      return "std_json_parse_null";
    if (i == 2)
      return "std_json_parse_number";
    if (i == 3)
      return "std_json_parse_string";
    if (i == 4)
      return "std_json_parse_string_view";
    if (i == 5)
      return "std_json_skip_value";
    return NULL;
  }
  if (k == 5) {
    /* PLATFORM: SHARED — fk0 k==5 csv.o exact UNDEF (mirror labi_ondemand_heavy.x). */
    if (i == 0)
      return "std_csv_next_field";
    if (i == 1)
      return "std_csv_parse_line";
    if (i == 2)
      return "std_csv_parse_row";
    if (i == 3)
      return "std_csv_write_row";
    return NULL;
  }
  /* PLATFORM: SHARED — exact UNDEF needles for std/path/path.o (k==6).
   * Exact match only; join/basename do not cover clean/sep/extension/stem/resolve. */
  if (k == 6) {
    if (i == 0)
      return "std_path_join";
    if (i == 1)
      return "std_path_dirname";
    if (i == 2)
      return "std_path_empty_len";
    if (i == 3)
      return "std_path_basename";
    if (i == 4)
      return "std_path_sep";
    if (i == 5)
      return "std_path_is_absolute";
    if (i == 6)
      return "std_path_is_sep";
    if (i == 7)
      return "std_path_extension";
    if (i == 8)
      return "std_path_stem";
    if (i == 9)
      return "std_path_extension_and_stem";
    if (i == 10)
      return "std_path_clean";
    if (i == 11)
      return "std_path_resolve";
    return NULL;
  }
  if (k == 7) {
    if (i == 0)
      return "std_hash_sip_hash";
    if (i == 1)
      return "std_hash_fnv1a";
    if (i == 2)
      return "std_hash_start";
    if (i == 3)
      return "std_hash_bytes";
    if (i == 4)
      return "std_hash_finish";
    if (i == 5)
      return "std_hash_free";
    if (i == 6)
      return "std_hash_write_u8_ptr_u32";
    return NULL;
  }
  if (k == 8) {
    /* PLATFORM: SHARED — std/error/error.o exact UNDEF (mirror heavy.x).
     * Was 4 needles; sole code_invalid/io_err_generic/chain_* never opened gate
     * (EXC soft SKIP). G.7 complete: every public std_error_* export ×57. */
    if (i == 0)
      return "std_error_ok";
    if (i == 1)
      return "std_error_code_alloc_fail";
    if (i == 2)
      return "std_error_code_invalid";
    if (i == 3)
      return "std_error_code_not_found";
    if (i == 4)
      return "std_error_ok_value";
    if (i == 5)
      return "std_error_from_code";
    if (i == 6)
      return "std_error_code";
    if (i == 7)
      return "std_error_is_ok";
    if (i == 8)
      return "std_error_is_err";
    if (i == 9)
      return "std_error_base_io";
    if (i == 10)
      return "std_error_io_err_timeout";
    if (i == 11)
      return "std_error_io_err_cancelled";
    if (i == 12)
      return "std_error_io_err_generic";
    if (i == 13)
      return "std_error_base_net";
    if (i == 14)
      return "std_error_net_err_timeout";
    if (i == 15)
      return "std_error_net_err_cancelled";
    if (i == 16)
      return "std_error_net_err_generic";
    if (i == 17)
      return "std_error_base_async";
    if (i == 18)
      return "std_error_async_err_generic";
    if (i == 19)
      return "std_error_base_coll";
    if (i == 20)
      return "std_error_coll_err_generic";
    if (i == 21)
      return "std_error_base_fs";
    if (i == 22)
      return "std_error_fs_err_not_found";
    if (i == 23)
      return "std_error_mod_tag_io";
    if (i == 24)
      return "std_error_mod_tag_fs";
    if (i == 25)
      return "std_error_mod_tag_db";
    if (i == 26)
      return "std_error_sidecar_none";
    if (i == 27)
      return "std_error_sidecar_errno";
    if (i == 28)
      return "std_error_sidecar_db_struct";
    if (i == 29)
      return "std_error_code_to_module_base";
    if (i == 30)
      return "std_error_code_in_global_range";
    if (i == 31)
      return "std_error_code_in_module_span";
    if (i == 32)
      return "std_error_code_is_platform_errno";
    if (i == 33)
      return "std_error_mod_tag_from_base";
    if (i == 34)
      return "std_error_mod_base_from_tag";
    if (i == 35)
      return "std_error_module_sidecar_kind";
    if (i == 36)
      return "std_error_sem_none";
    if (i == 37)
      return "std_error_sem_timeout";
    if (i == 38)
      return "std_error_sem_cancelled";
    if (i == 39)
      return "std_error_sem_not_found";
    if (i == 40)
      return "std_error_http_err_timeout";
    if (i == 41)
      return "std_error_http_err_cancelled";
    if (i == 42)
      return "std_error_semantic_class";
    if (i == 43)
      return "std_error_is_timeout";
    if (i == 44)
      return "std_error_is_cancelled";
    if (i == 45)
      return "std_error_is_not_found";
    if (i == 46)
      return "std_error_recommend_retry";
    if (i == 47)
      return "std_error_chain_max_depth";
    if (i == 48)
      return "std_error_chain_empty";
    if (i == 49)
      return "std_error_chain_from_code";
    if (i == 50)
      return "std_error_chain_from_result";
    if (i == 51)
      return "std_error_chain_depth";
    if (i == 52)
      return "std_error_chain_root";
    if (i == 53)
      return "std_error_chain_code_at";
    if (i == 54)
      return "std_error_chain_leaf";
    if (i == 55)
      return "std_error_chain_wrap";
    if (i == 56)
      return "std_error_error_module_anchor";
    return NULL;
  }
  if (k == 9) {
    if (i == 0)
      return "std_context_background";
    if (i == 1)
      return "std_context_deadline_ns";
    if (i == 2)
      return "std_context_is_cancelled";
    if (i == 3)
      return "std_context_remaining_ns";
    return NULL;
  }
  if (k == 10) {
    /* PLATFORM: SHARED — fk0 k==10 std/vec/vec.o exact UNDEF (mirror heavy.x). */
    if (i == 0)
      return "std_vec_new_retVec_u8";
    if (i == 1)
      return "std_vec_new_retVec_i32";
    if (i == 2)
      return "std_vec_push_Vec_u8_ptr_u8";
    if (i == 3)
      return "std_vec_push_Vec_i32_ptr_i32";
    if (i == 4)
      return "std_vec_length_Vec_u8";
    if (i == 5)
      return "std_vec_length_Vec_i32";
    if (i == 6)
      return "std_vec_len_empty";
    if (i == 7)
      return "std_vec_vec_len_empty";
    if (i == 8)
      return "std_vec_new";
    if (i == 9)
      return "std_vec_push";
    if (i == 10)
      return "std_vec_pop_Vec_i32_ptr";
    if (i == 11)
      return "std_vec_pop_Vec_u8_ptr";
    if (i == 12)
      return "std_vec_extend_Vec_i32_ptr_i32_ptr_i32";
    if (i == 13)
      return "std_vec_extend_Vec_u8_ptr_u8_ptr_i32";
    if (i == 14)
      return "std_vec_extend_Vec_u64_ptr_u64_ptr_i32";
    if (i == 15)
      return "std_vec_extend_Vec_f64_ptr_f64_ptr_i32";
    if (i == 16)
      return "std_vec_from_slice_u64_ptr_i32";
    if (i == 17)
      return "std_vec_from_slice_f64_ptr_i32";
    if (i == 18)
      return "std_vec_push_Vec_u64_ptr_u64";
    if (i == 19)
      return "std_vec_push_Vec_f64_ptr_f64";
    /* PLATFORM: SHARED — fk0 k==10 +length/deinit/get u64/f64 (mirror heavy.x).
     * u8/i32 length do not cover sole new+length/deinit Vec_u64/f64. */
    if (i == 20)
      return "std_vec_length_Vec_u64";
    if (i == 21)
      return "std_vec_deinit_Vec_u64_ptr";
    if (i == 22)
      return "std_vec_length_Vec_f64";
    if (i == 23)
      return "std_vec_deinit_Vec_f64_ptr";
    if (i == 24)
      return "std_vec_get_Vec_u64_i32";
    if (i == 25)
      return "std_vec_get_Vec_f64_i32";
    /* PLATFORM: SHARED — fk0 k==10 +vec3f SOA/AOS (mirror heavy.x).
     * Vec_* push/length/deinit do not cover unique vec3f_* names. */
    if (i == 26)
      return "std_vec_vec3f_soa_push";
    if (i == 27)
      return "std_vec_vec3f_soa_deinit";
    if (i == 28)
      return "std_vec_vec3f_aos_push";
    if (i == 29)
      return "std_vec_vec3f_aos_deinit";
    if (i == 30)
      return "std_vec_vec3f_soa_sum_x";
    if (i == 31)
      return "std_vec_vec3f_soa_reserve_one";
    if (i == 32)
      return "std_vec_vec3f_soa_len";
    if (i == 33)
      return "std_vec_vec3f_soa_get_x";
    if (i == 34)
      return "std_vec_vec3f_soa_get_y";
    if (i == 35)
      return "std_vec_vec3f_soa_get_z";
    if (i == 36)
      return "std_vec_vec3f_soa_set";
    if (i == 37)
      return "std_vec_vec3f_soa_with_capacity";
    if (i == 38)
      return "std_vec_vec3f_aos_reserve_one";
    if (i == 39)
      return "std_vec_vec3f_aos_get_x";
    if (i == 40)
      return "std_vec_vec3f_aos_sum_x";
    if (i == 41)
      return "std_vec_vec3f_aos_with_capacity";
    return NULL;
  }
  if (k == 11) {
    if (i == 0)
      return "std_sort_sort_i32_ptr_i32";
    if (i == 1)
      return "std_sort_sort_u8_ptr_i32";
    if (i == 2)
      return "std_sort_stable_i32_ptr_i32";
    if (i == 3)
      return "std_sort_stable_u8_ptr_i32";
    if (i == 4)
      return "std_sort_stable_by_key";
    if (i == 5)
      return "std_sort_cmp";
    if (i == 6)
      return "std_sort_cmp_asc_fn";
    if (i == 7)
      return "std_sort_cmp_desc_fn";
    if (i == 8)
      return "std_sort_cmp_key_fn";
    return NULL;
  }
  if (k == 12) {
    if (i == 0)
      return "std_env_getenv";
    if (i == 1)
      return "std_env_getenv_exists";
    if (i == 2)
      return "std_env_getenv_z";
    if (i == 3)
      return "std_env_getenv_ptr";
    if (i == 4)
      return "std_env_setenv";
    if (i == 5)
      return "std_env_unsetenv";
    if (i == 6)
      return "std_env_temp_dir";
    if (i == 7)
      return "std_env_iter";
    if (i == 8)
      return "std_env_iter_count";
    if (i == 9)
      return "std_env_args_iter";
    if (i == 10)
      return "std_env_args_iter_count";
    return NULL;
  }
  if (k == 13) {
    if (i == 0)
      return "std_random_next";
    if (i == 1)
      return "std_random_fill_bytes";
    if (i == 2)
      return "std_random_fill";
    if (i == 3)
      return "std_random_range_u32_u32";
    if (i == 4)
      return "std_random_flip";
    if (i == 5)
      return "std_random_gen";
    if (i == 6)
      return "std_random_rng_smoke";
    if (i == 7)
      return "std_random_seed";
    if (i == 8)
      return "random_u32_c";
    if (i == 9)
      return "random_u64_c";
    if (i == 10)
      return "random_rng_smoke_c";
    if (i == 11)
      return "random_fill_bytes_c";
    return NULL;
  }
  if (k == 14) {
    if (i == 0)
      return "std_time_now_monotonic_ns";
    if (i == 1)
      return "std_time_now_monotonic_ms";
    if (i == 2)
      return "std_time_now_wall_ns";
    if (i == 3)
      return "std_time_sleep_ms";
    if (i == 4)
      return "std_time_sleep_ns";
    if (i == 5)
      return "std_time_duration_ns";
    if (i == 6)
      return "std_time_timer_start";
    if (i == 7)
      return "std_time_start";
    if (i == 8)
      return "std_time_elapsed_ns";
    if (i == 9)
      return "std_time_format_wall_rfc3339";
    if (i == 10)
      return "std_time_wall_local_offset_min";
    if (i == 11)
      return "std_time_format_timezone_smoke";
    if (i == 12)
      return "time_now_monotonic_ns_c";
    if (i == 13)
      return "time_sleep_ns_c";
    if (i == 14)
      return "time_now_wall_ns_c";
    return NULL;
  }
  if (k == 15) {
    if (i == 0)
      return "std_fs_invalid";
    if (i == 1)
      return "std_fs_open";
    if (i == 2)
      return "std_fs_create";
    if (i == 3)
      return "std_fs_close";
    if (i == 4)
      return "std_fs_read";
    if (i == 5)
      return "std_fs_write";
    if (i == 6)
      return "std_fs_chunk_size";
    if (i == 7)
      return "std_fs_mmap_ro";
    if (i == 8)
      return "std_fs_last_error";
    if (i == 9)
      return "std_fs_readv_buf";
    if (i == 10)
      return "std_fs_writev_buf";
    /* Cap residual 9.1.2: stat-only users must pull formal fs.o. */
    if (i == 11)
      return "std_fs_stat";
    /* Cap residual 9.1.10: dir-only users must pull formal fs.o. */
    if (i == 12)
      return "std_fs_dir_open";
    if (i == 13)
      return "std_fs_dir_read";
    if (i == 14)
      return "std_fs_dir_close";
    return NULL;
  }
  /* PLATFORM: SHARED — std/tar/tar.o exact UNDEF needles (fk0 k==16; mirror heavy). */
  if (k == 16) {
    if (i == 0)
      return "std_tar_read_header";
    if (i == 1)
      return "std_tar_write_header";
    if (i == 2)
      return "std_tar_append_entry";
    if (i == 3)
      return "std_tar_next_entry";
    if (i == 4)
      return "std_tar_read_entry_data";
    if (i == 5)
      return "std_tar_path_max";
    if (i == 6)
      return "tar_read_header_c";
    return NULL;
  }
  /* PLATFORM: SHARED — std/unicode/unicode.o exact UNDEF needles (fk0 k==17). */
  if (k == 17) {
    if (i == 0)
      return "std_unicode_category";
    if (i == 1)
      return "std_unicode_to_lower";
    if (i == 2)
      return "std_unicode_to_upper";
    if (i == 3)
      return "std_unicode_is_whitespace";
    if (i == 4)
      return "std_unicode_is_ascii";
    if (i == 5)
      return "std_unicode_case_fold_rune";
    /*
     * wave957: added is_supplementary + rune_utf8_len for unicode_nfc_smoke
     * cookbook. Before wave957: probe table missed these → BLD001 UNDEF.
     * G.7: complete the single unicode probe table. PLATFORM: SHARED.
     */
    if (i == 6)
      return "std_unicode_is_supplementary";
    if (i == 7)
      return "std_unicode_rune_utf8_len";
    return NULL;
  }
  /* PLATFORM: SHARED — std/runtime/runtime.o exact UNDEF needles (fk0 k==18). */
  if (k == 18) {
    if (i == 0)
      return "std_runtime_ready";
    if (i == 1)
      return "std_runtime_panic";
    if (i == 2)
      return "std_runtime_abort";
    if (i == 3)
      return "std_runtime_diag_enabled";
    if (i == 4)
      return "std_runtime_crash_evidence_collect";
    return NULL;
  }
  /* PLATFORM: SHARED — std/cli/cli.o exact UNDEF needles (fk0 k==19; mirror heavy). */
  if (k == 19) {
    if (i == 0)
      return "std_cli_err_ok";
    if (i == 1)
      return "std_cli_err_help";
    if (i == 2)
      return "std_cli_err_unknown";
    if (i == 3)
      return "std_cli_parse_from_iter";
    if (i == 4)
      return "std_cli_arg_len";
    if (i == 5)
      return "std_cli_is_help";
    if (i == 6)
      return "std_cli_is_version";
    if (i == 7)
      return "std_cli_match_long";
    if (i == 8)
      return "std_cli_match_short";
    if (i == 9)
      return "std_cli_write_usage";
    return NULL;
  }
  /* PLATFORM: SHARED — std/datetime/datetime.o exact UNDEF needles (fk0 k==20; mirror heavy). */
  if (k == 20) {
    if (i == 0)
      return "std_datetime_timezone_iana";
    if (i == 1)
      return "std_datetime_now_utc";
    if (i == 2)
      return "std_datetime_from_unix";
    if (i == 3)
      return "std_datetime_from_utc_fields";
    if (i == 4)
      return "std_datetime_to_utc_fields";
    if (i == 5)
      return "std_datetime_compare";
    if (i == 6)
      return "std_datetime_parse_rfc3339";
    if (i == 7)
      return "std_datetime_format_rfc3339";
    if (i == 8)
      return "std_datetime_format_rfc3339_nano";
    if (i == 9)
      return "std_datetime_local_offset_min";
    if (i == 10)
      return "std_datetime_to_local_fields";
    if (i == 11)
      return "std_datetime_duration_from_ns";
    if (i == 12)
      return "std_datetime_duration_from_sec";
    if (i == 13)
      return "std_datetime_duration_between";
    if (i == 14)
      return "std_datetime_add_duration";
    if (i == 15)
      return "std_datetime_duration_sleep";
    if (i == 16)
      return "std_datetime_duration_from_monotonic";
    if (i == 17)
      return "std_datetime_timezone_utc";
    if (i == 18)
      return "std_datetime_timezone_local";
    if (i == 19)
      return "std_datetime_timezone_fixed";
    if (i == 20)
      return "std_datetime_timezone_from_name";
    if (i == 21)
      return "std_datetime_timezone_offset_at";
    if (i == 22)
      return "std_datetime_parse_offset_min";
    if (i == 23)
      return "std_datetime_to_zoned_fields";
    if (i == 24)
      return "std_datetime_from_zoned_fields";
    if (i == 25)
      return "std_datetime_iana_dst_smoke";
    if (i == 26)
      return "std_datetime_timezone_smoke";
    return NULL;
  }
  /* PLATFORM: SHARED — std/config/config.o exact UNDEF needles (fk0 k==21; mirror heavy). */
  if (k == 21) {
    if (i == 0)
      return "std_config_err_ok";
    if (i == 1)
      return "std_config_err_null";
    if (i == 2)
      return "std_config_err_not_found";
    if (i == 3)
      return "std_config_err_invalid";
    if (i == 4)
      return "std_config_err_io";
    if (i == 5)
      return "std_config_err_full";
    if (i == 6)
      return "std_config_source_unknown";
    if (i == 7)
      return "std_config_source_toml";
    if (i == 8)
      return "std_config_source_yaml";
    if (i == 9)
      return "std_config_source_env";
    if (i == 10)
      return "std_config_source_set";
    if (i == 11)
      return "std_config_new";
    if (i == 12)
      return "std_config_free";
    if (i == 13)
      return "std_config_clear";
    if (i == 14)
      return "std_config_load_toml_buf";
    if (i == 15)
      return "std_config_load_toml_file";
    if (i == 16)
      return "std_config_load_env_prefix";
    if (i == 17)
      return "std_config_merge";
    if (i == 18)
      return "std_config_set_string";
    if (i == 19)
      return "std_config_get_string";
    if (i == 20)
      return "std_config_get_i32";
    if (i == 21)
      return "std_config_get_bool";
    if (i == 22)
      return "std_config_get_source";
    if (i == 23)
      return "std_config_get_i32_meta";
    if (i == 24)
      return "std_config_get_bool_meta";
    if (i == 25)
      return "std_config_get_string_meta";
    if (i == 26)
      return "std_config_backend_toml";
    if (i == 27)
      return "std_config_backend_yaml";
    if (i == 28)
      return "std_config_load_yaml_buf";
    if (i == 29)
      return "std_config_load_yaml_file";
    if (i == 30)
      return "std_config_yaml_smoke";
    return NULL;
  }
  /* PLATFORM: SHARED — std/cache/cache.o exact UNDEF needles (fk0 k==22; mirror heavy). */
  if (k == 22) {
    if (i == 0)
      return "std_cache_err_ok";
    if (i == 1)
      return "std_cache_err_null";
    if (i == 2)
      return "std_cache_err_not_found";
    if (i == 3)
      return "std_cache_err_full";
    if (i == 4)
      return "std_cache_err_invalid";
    if (i == 5)
      return "std_cache_new_lru";
    if (i == 6)
      return "std_cache_free_LruCache_ptr";
    if (i == 7)
      return "std_cache_get";
    if (i == 8)
      return "std_cache_put";
    if (i == 9)
      return "std_cache_remove";
    if (i == 10)
      return "std_cache_purge";
    if (i == 11)
      return "std_cache_stats_LruCache_ptr_CacheStats_ptr";
    if (i == 12)
      return "std_cache_new";
    if (i == 13)
      return "std_cache_free_ObjPool_ptr";
    if (i == 14)
      return "std_cache_add";
    if (i == 15)
      return "std_cache_acquire";
    if (i == 16)
      return "std_cache_release";
    if (i == 17)
      return "std_cache_mark_unhealthy";
    if (i == 18)
      return "std_cache_idle";
    if (i == 19)
      return "std_cache_stats_ObjPool_ptr_PoolStats_ptr";
    return NULL;
  }
  /* PLATFORM: SHARED — std/url/url.o exact UNDEF needles (fk0 k==23; mirror heavy). */
  if (k == 23) {
    if (i == 0)
      return "std_url_parse";
    if (i == 1)
      return "std_url_build";
    if (i == 2)
      return "std_url_stringify";
    if (i == 3)
      return "std_url_query_encode";
    if (i == 4)
      return "std_url_query_decode";
    if (i == 5)
      return "std_url_resolve";
    if (i == 6)
      return "std_url_host_to_ipv6";
    if (i == 7)
      return "std_url_format_ipv6_host";
    if (i == 8)
      return "std_url_host_is_ipv6";
    if (i == 9)
      return "std_url_ipv6_host_smoke";
    return NULL;
  }
  /* PLATFORM: SHARED — std/security/security.o exact UNDEF needles (fk0 k==24; mirror heavy). */
  if (k == 24) {
    if (i == 0)
      return "std_security_key_len";
    if (i == 1)
      return "std_security_salt_len_default";
    if (i == 2)
      return "std_security_min_secret_len";
    if (i == 3)
      return "std_security_err_ok";
    if (i == 4)
      return "std_security_err_invalid";
    if (i == 5)
      return "std_security_err_random";
    if (i == 6)
      return "std_security_err_buffer";
    if (i == 7)
      return "std_security_ct_compare";
    if (i == 8)
      return "std_security_random_key";
    if (i == 9)
      return "std_security_random_salt";
    if (i == 10)
      return "std_security_hkdf";
    if (i == 11)
      return "std_security_secure_zero";
    if (i == 12)
      return "std_security_sensitive_lock";
    if (i == 13)
      return "std_security_sensitive_unlock";
    if (i == 14)
      return "std_security_sensitive_buf_init";
    if (i == 15)
      return "std_security_sensitive_buf_wipe";
    return NULL;
  }
  /* PLATFORM: SHARED — std/option/option.o exact UNDEF needles (fk0 k==25; mirror heavy). */
  if (k == 25) {
    if (i == 0)
      return "std_option_none";
    if (i == 1)
      return "std_option_some";
    if (i == 2)
      return "std_option_unwrap_or";
    if (i == 3)
      return "std_option_is_some";
    if (i == 4)
      return "std_option_is_none";
    if (i == 5)
      return "std_option_map";
    if (i == 6)
      return "std_option_and_then";
    if (i == 7)
      return "std_option_or";
    if (i == 8)
      return "std_option_from_result_Result_i32";
    if (i == 9)
      return "std_option_from_result_Result_u8";
    if (i == 10)
      return "std_option_to_result";
    return NULL;
  }
  /* PLATFORM: SHARED — std/result/result.o exact UNDEF needles (fk0 k==26; mirror heavy). */
  if (k == 26) {
    if (i == 0)
      return "std_result_ok";
    if (i == 1)
      return "std_result_err";
    if (i == 2)
      return "std_result_is_ok";
    if (i == 3)
      return "std_result_is_err";
    if (i == 4)
      return "std_result_unwrap_or";
    if (i == 5)
      return "std_result_map";
    if (i == 6)
      return "std_result_and_then";
    if (i == 7)
      return "std_result_or_else";
    if (i == 8)
      return "std_result_from_error_code";
    if (i == 9)
      return "std_result_from_value";
    if (i == 10)
      return "std_result_err_code";
    return NULL;
  }
  return NULL;
}

int labi_std_fk0_user_needs_rel(const char *user_o, const char *rel) {
  int nk;
  int k;
  int kind;
  int n;
  int i;
  if (!rel || !rel[0])
    return 0;
  if (!user_o || !user_o[0])
    return 1;
  nk = labi_fk0_rel_count();
  kind = -1;
  for (k = 0; k < nk; k++) {
    const char *needle = labi_fk0_rel_at(k);
    if (needle && needle[0] && strstr(rel, needle) != NULL) {
      kind = k;
      break;
    }
  }
  if (kind < 0)
    return 0;
  n = labi_fk0_sym_count(kind);
  for (i = 0; i < n; i++) {
    const char *sym = labi_fk0_sym_at(kind, i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave190: labi_std_fk_user_needs pure cold twin (fk 1–13 gate tables + orch).
 * Cap residual: xlang_link_obj_needs_undef_sym. PLATFORM: SHARED. */
int labi_std_fk_gate_sym_count(int fk) {
  /* PLATFORM: SHARED — process product face complete (pure-asm std_process_*). */
  if (fk == 1) return 28;
  if (fk == 2) return 16; /* pool/name/affinity + create/join — twin labi_ondemand_heavy.x */
  if (fk == 3) return 5;
  if (fk == 4) return 3;
  if (fk == 5) return 5;
  /* PLATFORM: SHARED — std/atomic complete surface (10.4.1 widen i16/u16/i64/u64 support). */
  if (fk == 6) return 32;
  if (fk == 7) return 4;
  if (fk == 8) return 2;
  /* PLATFORM: SHARED — runtime_math_libm freestanding face gate completion
   * (9.2.4 Fix F). Was 29 needles; the 31 freestanding C-ABI faces
   * (math_acos_c .. math_special_near) were absent, so a user TU whose only
   * UNDEFs are e.g. math_fmin_c/math_fmax_c never opened the fk9 gate and
   * the std/math/math.o plan leaf stayed closed -> UNDEF at ld.
   * Twin of labi_ondemand_heavy.x labi_std_fk_gate_sym_count (fk9 = 60). */
  if (fk == 9) return 60;
  /* PLATFORM: SHARED — cookbook sqlite_available unique UNDEF (is_available).
   * Was 3 needles; matcher exact so prefix std_db_sqlite never fires.
   * Twin of labi_ondemand_heavy.x. 29 unique import faces + legacy 3 + db_open_c. */
  if (fk == 10) return 33;
  if (fk == 11) return 2;
  if (fk == 12) return 4;
  if (fk == 13) return 4;
  return 0;
}

const char *labi_std_fk_gate_sym_at(int fk, int i) {
  if (i < 0) return NULL;
  /* PLATFORM: SHARED — exact UNDEF needles for std/process/process.o (fk==1).
   * Twin of labi_ondemand_heavy.x labi_std_fk_gate_sym_at (G.7 seed/.x same commit). */
  if (fk == 1) {
    if (i == 0) return "process_xlang_argv_get";
    if (i == 1) return "process_arg_c";
    if (i == 2) return "process_args_count_c";
    if (i == 3) return "std_process_exit";
    if (i == 4) return "std_process_args_count";
    if (i == 5) return "std_process_arg";
    if (i == 6) return "std_process_getenv";
    if (i == 7) return "std_process_setenv";
    if (i == 8) return "std_process_unsetenv";
    if (i == 9) return "std_process_getpid";
    if (i == 10) return "std_process_getppid";
    if (i == 11) return "std_process_getcwd";
    if (i == 12) return "std_process_getcwd_ptr";
    if (i == 13) return "std_process_getcwd_cached_len";
    if (i == 14) return "std_process_chdir";
    if (i == 15) return "std_process_self_exe_path";
    if (i == 16) return "std_process_self_exe_path_ptr";
    if (i == 17) return "std_process_self_exe_path_cached_len";
    if (i == 18) return "std_process_spawn";
    if (i == 19) return "std_process_spawn_io";
    if (i == 20) return "std_process_spawn_simple";
    if (i == 21) return "std_process_exec";
    if (i == 22) return "std_process_exec_simple";
    if (i == 23) return "std_process_waitpid";
    if (i == 24) return "std_process_pipe";
    if (i == 25) return "process_getenv_c";
    if (i == 26) return "process_spawn_c";
    if (i == 27) return "process_waitpid_c";
    return NULL;
  }
  if (fk == 2) {
    /* PLATFORM: SHARED — twin of labi_ondemand_heavy.x fk==2 (pool co-emit UNDEFs glue). */
    if (i == 0) return "std_thread_spawn";
    if (i == 1) return "std_thread_join";
    if (i == 2) return "thread_create_c";
    if (i == 3) return "thread_join_c";
    if (i == 4) return "thread_pool_start_c";
    if (i == 5) return "thread_pool_submit_c";
    if (i == 6) return "thread_pool_drain_c";
    if (i == 7) return "thread_pool_stop_c";
    if (i == 8) return "thread_pool_pending_c";
    if (i == 9) return "thread_set_name_self_c";
    if (i == 10) return "thread_dummy_entry_ptr_c";
    if (i == 11) return "thread_create_with_stack_c";
    if (i == 12) return "thread_self_c";
    if (i == 13) return "thread_set_affinity_c";
    if (i == 14) return "thread_set_affinity_self_c";
    if (i == 15) return "thread_set_qos_class_self_c";
    return NULL;
  }
  if (fk == 3) {
    if (i == 0) return "std_sync_lock";
    if (i == 1) return "std_sync_new_mutex";
    if (i == 2) return "std_sync_try_lock";
    if (i == 3) return "std_sync_wait";
    if (i == 4) return "sync_mutex_lock_c";
    return NULL;
  }
  if (fk == 4) {
    if (i == 0) return "std_crypto_mem_eq";
    if (i == 1) return "crypto_mem_eq_c";
    if (i == 2) return "std_crypto_sha256";
    return NULL;
  }
  if (fk == 5) {
    if (i == 0) return "std_log_log";
    if (i == 1) return "std_log_level_info";
    if (i == 2) return "std_log_set_min_level";
    if (i == 3) return "log_write_c";
    if (i == 4) return "std_log_structured_kv";
    return NULL;
  }
  if (fk == 6) {
    if (i == 0) return "std_atomic_store_i32_ptr_i32";
    if (i == 1) return "std_atomic_load_i32_ptr";
    if (i == 2) return "std_atomic_fetch_add_i32_ptr_i32";
    if (i == 3) return "std_atomic_store_i64_ptr_i64";
    if (i == 4) return "atomic_store_i32_c";
    if (i == 5) return "std_atomic_store_i16_ptr_i16";
    if (i == 6) return "std_atomic_store_u16_ptr_u16";
    if (i == 7) return "std_atomic_store_u32_ptr_u32";
    if (i == 8) return "std_atomic_store_u64_ptr_u64";
    if (i == 9) return "std_atomic_load_i16_ptr";
    if (i == 10) return "std_atomic_load_u16_ptr";
    if (i == 11) return "std_atomic_load_u32_ptr";
    if (i == 12) return "std_atomic_load_i64_ptr";
    if (i == 13) return "std_atomic_load_u64_ptr";
    if (i == 14) return "std_atomic_fetch_add_i16_ptr_i16";
    if (i == 15) return "std_atomic_fetch_add_u16_ptr_u16";
    if (i == 16) return "std_atomic_fetch_add_u32_ptr_u32";
    if (i == 17) return "std_atomic_fetch_add_i64_ptr_i64";
    if (i == 18) return "std_atomic_fetch_add_u64_ptr_u64";
    if (i == 19) return "std_atomic_fetch_sub_i32_ptr_i32";
    if (i == 20) return "std_atomic_fetch_sub_i64_ptr_i64";
    if (i == 21) return "std_atomic_fetch_sub_u64_ptr_u64";
    if (i == 22) return "std_atomic_compare_exchange_i16_ptr_i16_ptr_i16";
    if (i == 23) return "std_atomic_compare_exchange_i32_ptr_i32_ptr_i32";
    if (i == 24) return "std_atomic_compare_exchange_i64_ptr_i64_ptr_i64";
    if (i == 25) return "std_atomic_compare_exchange_u16_ptr_u16_ptr_u16";
    if (i == 26) return "std_atomic_compare_exchange_u32_ptr_u32_ptr_u32";
    if (i == 27) return "std_atomic_compare_exchange_u64_ptr_u64_ptr_u64";
    if (i == 28) return "std_atomic_fence_acquire";
    if (i == 29) return "std_atomic_fence_release";
    if (i == 30) return "std_atomic_fence_seq_cst";
    if (i == 31) return "atomic_load_i32_c";
    return NULL;
  }
  if (fk == 7) {
    if (i == 0) return "std_channel_send";
    if (i == 1) return "std_channel_recv";
    if (i == 2) return "channel_send";
    if (i == 3) return "channel_recv";
    return NULL;
  }
  if (fk == 8) {
    if (i == 0) return "std_backtrace_capture";
    if (i == 1) return "backtrace_capture";
    return NULL;
  }
  if (fk == 9) {
    if (i == 0) return "std_math_sin";
    if (i == 1) return "std_math_cos";
    if (i == 2) return "std_math_tan";
    if (i == 3) return "std_math_pi";
    if (i == 4) return "std_math_e";
    if (i == 5) return "std_math_tau";
    if (i == 6) return "std_math_floor";
    if (i == 7) return "std_math_ceil";
    if (i == 8) return "std_math_trunc";
    if (i == 9) return "std_math_round";
    if (i == 10) return "std_math_sqrt";
    if (i == 11) return "std_math_cbrt";
    if (i == 12) return "std_math_pow";
    if (i == 13) return "std_math_exp";
    if (i == 14) return "std_math_log";
    if (i == 15) return "std_math_abs";
    if (i == 16) return "std_math_signum";
    if (i == 17) return "std_math_min";
    if (i == 18) return "std_math_max";
    if (i == 19) return "std_math_asin";
    if (i == 20) return "std_math_acos";
    if (i == 21) return "std_math_atan";
    if (i == 22) return "std_math_atan2";
    if (i == 23) return "math_sin";
    if (i == 24) return "math_cos";
    if (i == 25) return "math_sin_c";
    if (i == 26) return "math_cos_c";
    if (i == 27) return "math_floor_c";
    if (i == 28) return "math_pi_c";
    /* PLATFORM: SHARED — 9.2.4 Fix F gate completion: the 31 freestanding
     * runtime_math_libm C-ABI faces appended in the same order as the .x
     * authority (labi_ondemand_heavy.x labi_std_fk_gate_sym_at fk9 29..59),
     * so a user TU whose sole UNDEF is any one of these opens fk9 and the
     * std/math/math.o plan leaf links runtime_math_libm.o. Twin semantics. */
    if (i == 29) return "math_acos_c";
    if (i == 30) return "math_asin_c";
    if (i == 31) return "math_atan_c";
    if (i == 32) return "math_atan2_c";
    if (i == 33) return "math_cbrt_c";
    if (i == 34) return "math_ceil_c";
    if (i == 35) return "math_erf_c";
    if (i == 36) return "math_erfc_c";
    if (i == 37) return "math_exp_c";
    if (i == 38) return "math_expm1_c";
    if (i == 39) return "math_fabs_c";
    if (i == 40) return "math_fmax_c";
    if (i == 41) return "math_fmin_c";
    if (i == 42) return "math_log_c";
    if (i == 43) return "math_log1p_c";
    if (i == 44) return "math_pow_c";
    if (i == 45) return "math_round_c";
    if (i == 46) return "math_signum_c";
    if (i == 47) return "math_sqrt_c";
    if (i == 48) return "math_tan_c";
    if (i == 49) return "math_trunc_c";
    if (i == 50) return "math_fenv_available_c";
    if (i == 51) return "math_fenv_capability_smoke_c";
    if (i == 52) return "math_fenv_clear_c";
    if (i == 53) return "math_fenv_emit_cap_report";
    if (i == 54) return "math_fenv_fe_to_mask";
    if (i == 55) return "math_fenv_mask_to_fe";
    if (i == 56) return "math_fenv_raise_c";
    if (i == 57) return "math_fenv_smoke_c";
    if (i == 58) return "math_fenv_test_c";
    if (i == 59) return "math_special_near";
    return NULL;
  }
  if (fk == 10) {
    /* PLATFORM: SHARED — unique-first cookbook sqlite_available, then remaining
     * unique std.db.sqlite export faces in mod.x source order, then legacy 3. */
    if (i == 0) return "std_db_sqlite_is_available";
    if (i == 1) return "std_db_sqlite_open";
    if (i == 2) return "std_db_sqlite_close";
    if (i == 3) return "std_db_sqlite_exec";
    if (i == 4) return "std_db_sqlite_rows";
    if (i == 5) return "std_db_sqlite_begin";
    if (i == 6) return "std_db_sqlite_next_row";
    if (i == 7) return "std_db_sqlite_col";
    if (i == 8) return "std_db_sqlite_col_text";
    if (i == 9) return "std_db_sqlite_col_blob";
    if (i == 10) return "std_db_sqlite_col_blob_len";
    if (i == 11) return "std_db_sqlite_col_blob_read";
    if (i == 12) return "std_db_sqlite_end";
    if (i == 13) return "std_db_sqlite_begin_tx";
    if (i == 14) return "std_db_sqlite_commit";
    if (i == 15) return "std_db_sqlite_rollback";
    if (i == 16) return "std_db_sqlite_last_error";
    if (i == 17) return "std_db_sqlite_backend_name";
    if (i == 18) return "std_db_sqlite_changes";
    if (i == 19) return "std_db_sqlite_prepare";
    if (i == 20) return "std_db_sqlite_prepare_cached";
    if (i == 21) return "std_db_sqlite_bind";
    if (i == 22) return "std_db_sqlite_step";
    if (i == 23) return "std_db_sqlite_reset";
    if (i == 24) return "std_db_sqlite_finalize";
    if (i == 25) return "std_db_sqlite_cache_clear";
    if (i == 26) return "std_db_sqlite_acquire";
    if (i == 27) return "std_db_sqlite_release";
    if (i == 28) return "std_db_sqlite_idle";
    if (i == 29) return "std_db_sqlite";
    if (i == 30) return "sqlite3_open";
    if (i == 31) return "db_sqlite_open";
    /* Product -o co-emitting mod.x wrappers UNDEFs bare db_*_c. Exact matcher. */
    if (i == 32) return "db_open_c";
    return NULL;
  }
  if (fk == 11) {
    if (i == 0) return "std_elf_parse";
    if (i == 1) return "elf_parse";
    return NULL;
  }
  if (fk == 12) {
    if (i == 0) return "std_dynlib_open";
    if (i == 1) return "std_dynlib_sym";
    if (i == 2) return "dynlib_open_c";
    if (i == 3) return "dynlib_open";
    return NULL;
  }
  if (fk == 13) {
    if (i == 0) return "std_http_get";
    if (i == 1) return "std_http_request";
    if (i == 2) return "std_http_client_new";
    if (i == 3) return "std_http_request_timeout_ms_for_ctx";
    return NULL;
  }
  return NULL;
}

int labi_std_fk_user_needs(const char *user_o, int fk) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 1;
  n = labi_std_fk_gate_sym_count(fk);
  if (n <= 0)
    return 1;
  for (i = 0; i < n; i++) {
    const char *sym = labi_std_fk_gate_sym_at(fk, i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave140: user.o provides_core_mem/std_heap defined-sym tables + pure orch.
 * Cap residual: xlang_link_obj_has_defined_sym (popen/nm). PLATFORM: SHARED. */
int labi_od_provides_core_mem_sym_count(void) { return 2; }
const char *labi_od_provides_core_mem_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "core_mem_mem_copy";
  if (i == 1)
    return "core_mem_placeholder";
  return NULL;
}

int link_abi_user_o_provides_core_mem(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_provides_core_mem_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_provides_core_mem_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_has_defined_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

int labi_od_provides_std_heap_sym_count(void) { return 2; }
const char *labi_od_provides_std_heap_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_heap_libc_heap_alloc_c";
  if (i == 1)
    return "std_heap_alloc_usize";
  return NULL;
}

int link_abi_user_o_provides_std_heap(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_od_provides_std_heap_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_od_provides_std_heap_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_has_defined_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave145: aggregate link_needs_heap_user_c / std_heap_import pure orch.
 * user_o probe + argv .o scan; Cap residual: none new (reuses needs_* + is_obj).
 * PLATFORM: SHARED. */
int link_abi_link_needs_heap_user_c(const char *user_o, const char **argv, int la) {
  int i;
  if (user_o && user_o[0] && link_abi_user_o_needs_heap_user_syms(user_o))
    return 1;
  if (!argv || la <= 0)
    return 0;
  for (i = 0; i < la && argv[i]; i++) {
    if (!link_abi_ld_argv_entry_is_obj(argv[i]))
      continue;
    if (link_abi_user_o_needs_heap_user_syms(argv[i]))
      return 1;
  }
  return 0;
}

int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la) {
  int i;
  if (user_o && user_o[0] && link_abi_user_o_needs_std_heap_api(user_o))
    return 1;
  if (!argv || la <= 0)
    return 0;
  for (i = 0; i < la && argv[i]; i++) {
    if (!link_abi_ld_argv_entry_is_obj(argv[i]))
      continue;
    if (link_abi_user_o_needs_std_heap_api(argv[i]))
      return 1;
  }
  return 0;
}

/* Pure rel constants for needs_* driven branches (early on_demand). */
const char *labi_od_rel_net(void) { return "std/net/net.o"; }
/* PLATFORM: SHARED — net.o transitive U std_error_* / std_context_*; ≡ pure .x. */
const char *labi_od_rel_error(void) { return "std/error/error.o"; }
const char *labi_od_rel_context(void) { return "std/context/context.o"; }
const char *labi_od_rel_atomic_glue(void) { return "compiler/runtime_atomic_glue.o"; }
const char *labi_od_rel_thread(void) { return "std/thread/thread.o"; }
/* wave958: std.vec / std.http on_demand rel constants. PLATFORM: SHARED. */
const char *labi_od_rel_vec(void) { return "std/vec/vec.o"; }
const char *labi_od_rel_http(void) { return "std/http/http.o"; }
const char *labi_od_rel_heap(void) { return "std/heap/heap.o"; }
const char *labi_od_rel_set(void) { return "std/set/set.o"; }
const char *labi_od_rel_map(void) { return "std/map/map.o"; }
const char *labi_od_rel_async_scheduler(void) { return "std/async/scheduler.o"; }
const char *labi_od_rel_core_mem(void) { return "core/mem/mem.o"; }
const char *labi_od_rel_sys_linux(void) { return "std/sys/linux.o"; }
const char *labi_od_rel_sys_macos(void) { return "std/sys/macos.o"; }
const char *labi_od_rel_page_mmap(void) { return "std/heap/page_mmap.o"; }
const char *labi_od_rel_sys(void) { return "std/sys/sys.o"; }
const char *labi_od_rel_core_slice(void) { return "core/slice/slice.o"; }
const char *labi_od_rel_test(void) { return "std/test/test.o"; }
const char *labi_od_rel_heap_user(void) { return "compiler/runtime_heap_user.o"; }
const char *labi_od_rel_scheduler_glue(void) { return "compiler/runtime_scheduler_glue.o"; }
const char *labi_od_rel_thread_glue(void) { return "compiler/runtime_thread_glue.o"; }
/* wave958: http glue companion .o path for std.http on_demand ensure. */
const char *labi_od_rel_http_glue(void) { return "compiler/runtime_http_glue.o"; }
const char *labi_od_rel_net_udp_batch(void) { return "compiler/runtime_net_udp_batch.o"; }
const char *labi_od_rel_net_workers(void) { return "compiler/runtime_net_workers.o"; }
const char *labi_od_rel_test_fn_invoke(void) { return "compiler/runtime_test_fn_invoke.o"; }

/* wave197: on_demand product shell cold twin (≡ mega pre-wave197 / pure .x). */
/* local helper: any of pure-table syms undefined in user_o (nm). */
static int labi_od_user_needs_any_sym_table(const char *user_o, int n, const char *(*sym_at)(int)) {
    int i;
    if (!user_o || !user_o[0] || n <= 0 || !sym_at)
        return 0;
    for (i = 0; i < n; i++) {
        const char *s = sym_at(i);
        if (s && s[0] && xlang_link_obj_needs_undef_sym(user_o, s))
            return 1;
    }
    return 0;
}

static int labi_od_user_needs_simple_group(const char *user_o, int g) {
    int n = labi_od_simple_group_sym_count(g);
    int i;
    if (!user_o || !user_o[0] || n <= 0)
        return 0;
    for (i = 0; i < n; i++) {
        const char *s = labi_od_simple_group_sym_at(g, i);
        if (s && s[0] && xlang_link_obj_needs_undef_sym(user_o, s))
            return 1;
    }
    return 0;
}

/* G-02f-165：逻辑源 .x（批折叠）；seed 保留同语义 C 供产品 cc */
/* G-02f-272：on_demand 列表纯表 + 本函数 IO 解释 */
void xlang_asm_ld_append_on_demand_user_objs(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags) {
#if defined(__linux__) || defined(__APPLE__)
    const char *p;
    int sg;
    if (!user_o || !user_o[0] || !la || *la >= max_la - 1)
        return;
    if (link_abi_user_o_needs_std_net(user_o)) {
        int have_net = 0;
        /* PLATFORM: SHARED — L4 wipe deletes net.o; push_obj skip-missing is
         * not enough (≡ need_sys). Cookbook net_listen_bind UNDEF std_net_listen
         * / close_listener while needles already fire. Produce path is existing
         * net_merge via compiler-make try-heat (not formal_mod). G.7: complete
         * existing need_net path with ensure; do not add a second simple-group
         * or convert net_merge into formal_mod. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0])
                (void)xlang_ensure_formal_std_make_o(include_root, "std/net/net.o",
                                                    "../std/net/net.o");
        }
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_net(), lib_roots, n_lib_roots, bank, argv, la, max_la, &have_net);
        if (have_net) {
            if (flags)
                flags->have_net = 1;
            /* PLATFORM: SHARED — net.o U error/context; user needles miss. ≡ C need_context.
             * G.7 companions: error formal + context formal + atomic_glue + time_os. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0]) {
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/error/error.o",
                                                        "../std/error/error.o");
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/context/context.o",
                                                        "../std/context/context.o");
                }
                link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_error(), lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_context(), lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_atomic_glue_o,
                    xlang_runtime_atomic_glue_o_path(link_argv0), link_argv0,
                    labi_od_rel_atomic_glue(), lib_roots, n_lib_roots, bank, argv, la, max_la);
                link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_time_os_o,
                    xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                    labi_od_time_os_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la);
            }
            /* workers.x / net_run_accept_workers_c U thread_create_c (thread_glue).
             * PLATFORM: SHARED — L4 wipe deletes thread.o; skip-missing never
             * pushes glue. Darwin -dead_strip hid unused workers T; Ubuntu gold
             * exposes UNDEF. G.7 complete existing need_net thread companion
             * with formal ensure (≡ error/context); do not add a second table. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0])
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/thread/thread.o",
                                                        "../std/thread/thread.o");
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_thread(), lib_roots, n_lib_roots, bank, argv, la, max_la,
                flags ? &flags->have_thread : NULL);
            if (flags && flags->have_thread) {
                link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_thread_glue_o,
                    xlang_runtime_thread_glue_o_path(link_argv0), link_argv0,
                    labi_od_rel_thread_glue(), lib_roots, n_lib_roots, bank, argv, la, max_la);
            }
            link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_net_udp_batch_o,
                xlang_runtime_net_udp_batch_o_path(link_argv0), link_argv0,
                labi_od_rel_net_udp_batch(), lib_roots, n_lib_roots, bank, argv, la, max_la);
            link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_net_workers_o,
                xlang_runtime_net_workers_o_path(link_argv0), link_argv0,
                labi_od_rel_net_workers(), lib_roots, n_lib_roots, bank, argv, la, max_la);
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
     * path). Skip if need_net already pushed thread.o (flags->have_thread).
     * PLATFORM: SHARED. G.7: single thread ensure path (table + this block).
     */
    if (link_abi_user_o_needs_std_thread(user_o)) {
        int already_th = (flags && flags->have_thread);
        if (!already_th) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_thread(), lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, flags ? &flags->have_thread : NULL);
            if (flags && flags->have_thread) {
                link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_thread_glue_o,
                    xlang_runtime_thread_glue_o_path(link_argv0), link_argv0,
                    labi_od_rel_thread_glue(), lib_roots, n_lib_roots, bank, argv, la, max_la);
            }
        }
    }
    /*
     * wave958: standalone std.vec on_demand. PLATFORM: SHARED.
     * Probe: link_abi_user_o_needs_std_vec scans labi_od_vec_sym_*.
     * When hit, ensure std/vec/vec.o then push it onto the link line.
     * G.7: single vec ensure path (table + this block).
     */
    if (link_abi_user_o_needs_std_vec(user_o)) {
        const char *root_vec = xlang_repo_root_from_argv0(link_argv0);
        if (root_vec && root_vec[0])
            xlang_ensure_formal_std_make_o(root_vec, "std/vec/vec.o", "../std/vec/vec.o");
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_vec(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    }
    /*
     * wave958: standalone std.http on_demand. PLATFORM: SHARED.
     * Probe: link_abi_user_o_needs_std_http scans labi_od_http_sym_*.
     * When hit, ensure std/http/http.o then push it onto the link line.
     * G.7: single http ensure path (table + this block).
     */
    if (link_abi_user_o_needs_std_http(user_o)) {
        const char *root_http = xlang_repo_root_from_argv0(link_argv0);
        if (root_http && root_http[0])
            xlang_ensure_formal_std_make_o(root_http, "std/http/http.o", "../std/http/http.o");
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_http(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        /*
         * wave958: http.o has UNDEF _http_*_c symbols defined in
         * compiler/runtime_http_glue.o. Ensure + push glue companion.
         * PLATFORM: SHARED.
         */
        link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_http_glue_o,
            xlang_runtime_http_glue_o_path(link_argv0), link_argv0,
            labi_od_rel_http_glue(), lib_roots, n_lib_roots, bank, argv, la, max_la);
    }
    if (link_abi_link_needs_std_heap_import(user_o, argv, la ? *la : 0)) {
        /* L4 wipe deletes heap.o; push_obj skip-missing is not enough. Ensure
         * first (≡ set/map). PLATFORM: SHARED — Darwin hard UNDEF if absent. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0]) {
                (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o",
                                                    "../std/heap/heap.o");
                (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o",
                                                    "../core/mem/mem.o");
            }
        }
        /* heap.o → core.mem：user 已 co-emit 提供 T 时勿链 mem/heap（duplicate）。 */
        if (!link_abi_user_o_provides_core_mem(user_o)) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (!link_abi_user_o_provides_std_heap(user_o)) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_heap(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    /*
     * PLATFORM: SHARED — set/map product asm: formal .o + heap/core_mem/(hash for set).
     * Align companions with C invoke_cc need_set/need_map (G.7 complete, no second path).
     * L4 wipe: ensure formal .o via Makefile before push.
     */
    if (link_abi_user_o_needs_std_set(user_o)) {
        const char *include_root = xlang_repo_root_from_argv0(link_argv0);
        if (include_root && include_root[0]) {
            (void)xlang_ensure_formal_std_make_o(include_root, "std/set/set.o", "../std/set/set.o");
            (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
            (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
            (void)xlang_ensure_formal_std_make_o(include_root, "std/hash/hash.o", "../std/hash/hash.o");
        }
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_set(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_heap(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        /* set.o → U std_hash_bytes; fk0 hash gate is user-only and misses set.o. */
        link_abi_asm_ld_push_obj(NULL, link_argv0, "std/hash/hash.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    }
    if (link_abi_user_o_needs_std_map(user_o)) {
        const char *include_root = xlang_repo_root_from_argv0(link_argv0);
        if (include_root && include_root[0]) {
            (void)xlang_ensure_formal_std_make_o(include_root, "std/map/map.o", "../std/map/map.o");
            (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
            (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
        }
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_map(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        /* map.o U: typed libc heap + map_find; user may only U empty_size. */
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_heap(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    }
    if (link_abi_user_o_needs_async_scheduler(user_o)) {
        p = asm_link_obj_skip_missing(xlang_std_async_scheduler_o_path(link_argv0));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_rel_async_scheduler(), lib_roots, n_lib_roots, bank);
        if (p && *la < max_la - 1)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
        if (p && *la < max_la - 1) {
            const char *rsg = asm_link_obj_skip_missing(xlang_runtime_scheduler_glue_o_path(link_argv0));
            if (!rsg && bank)
                rsg = xlang_asm_ld_try_under_lib_roots(labi_od_rel_scheduler_glue(), lib_roots, n_lib_roots, bank);
            if (rsg)
                link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, rsg);
        }
    }
    if (link_abi_user_o_needs_core_mem(user_o)) {
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, labi_od_rel_core_mem()));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank);
        if (p)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
    }
    /*
     * F-no-libc NL-03：freestanding mmap bump 堆按需链入。
     * 【Why 根源】page_mmap.x 固定 import std.sys.linux + core.mem，故链 page_mmap.o 须同时
     * 链 linux.o + core_mem.o；sys.o 传递依赖 linux.o。--gc-sections 移除未引用的 hosted 函数。
     * 【Invariant】顺序：linux.o → core_mem.o → page_mmap.o / sys.o（被依赖者先入链）。
     *
     * G-03 freestanding co-emit 守卫：freestanding 模式下 dep 模块经 co-emit 已 emit 到 user.o
     * （#[cfg(not(freestanding))] 剪枝 hosted 函数，仅留 syscall 桩/const）。预编译 std/sys/linux.o
     * 等是 hosted 编译产物（含 linux_mmap_rw → libc open/lseek/ftruncate），链入会泄漏 undefined
     * 引用；且 consts（syscall_nr_write）与 co-emit 重复定义。故 freestanding 模式跳过整块，
     * 完全依赖 co-emit 提供的 freestanding-safe 子集。
     */
    if (!driver_freestanding_get()) {
        int need_page_mmap = link_abi_user_o_needs_std_heap_page_mmap(user_o);
        int need_sys_linux = link_abi_user_o_needs_std_sys_linux(user_o);
        int need_sys_macos = link_abi_user_o_needs_std_sys_macos(user_o);
        int need_sys = link_abi_user_o_needs_std_sys(user_o);
        int ai;
        /*
         * PLATFORM: SHARED / LINUX gold — formal heap.o carries U page_mmap_* even when
         * user.o only has std_string_* / std_heap_* API UNDEFs. Scan already-pushed argv
         * (heap.o from on_demand above) so string/wa chain gets page_mmap.o.
         * G.7: extend existing page_mmap probe authority (no second path).
         */
        if (argv && la) {
            for (ai = 0; ai < *la && argv[ai]; ai++) {
                if (!link_abi_ld_argv_entry_is_obj(argv[ai]))
                    continue;
                if (link_abi_user_o_needs_std_heap_page_mmap(argv[ai]))
                    need_page_mmap = 1;
                if (link_abi_user_o_needs_std_sys_linux(argv[ai]))
                    need_sys_linux = 1;
                if (link_abi_user_o_needs_std_sys_macos(argv[ai]))
                    need_sys_macos = 1;
                if (link_abi_user_o_needs_std_sys(argv[ai]))
                    need_sys = 1;
            }
        }
        if (need_sys_linux || need_page_mmap || need_sys) {
            /* PLATFORM: SHARED — L4 wipe deletes linux.o; nested leaf sys_linux
             * is authority for std_sys_linux_linux_*. Twin of need_sys ensure. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0])
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/sys/linux.o",
                                                        "../std/sys/linux.o");
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_sys_linux(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_sys_macos) {
            /* PLATFORM: SHARED — Darwin cfg import macos_write_*; ensure+push. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0])
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/sys/macos.o",
                                                        "../std/sys/macos.o");
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_sys_macos(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_page_mmap || need_sys) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_page_mmap) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_page_mmap(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_sys) {
            /* PLATFORM: SHARED — L4 wipe deletes sys.o; push_obj skip-missing is
             * not enough (≡ heap/vec/http). Cookbook sys_write_stdout UNDEF
             * std_sys_write_stdout while needles already fire. G.7: complete
             * existing need_sys path with formal ensure; do not add a second
             * simple-group table. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0])
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/sys/sys.o",
                                                        "../std/sys/sys.o");
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_sys(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    if (link_abi_user_o_needs_core_slice(user_o)) {
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, labi_od_rel_core_slice()));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_rel_core_slice(), lib_roots, n_lib_roots, bank);
        if (p)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
        /*
         * wave957: X-facing core_slice u64 symbols (chunks_len / split_at /
         * subslice) are in core/slice/mod.o (API), not slice.o (glue). Push
         * mod.o too when needs_core_slice fires. G.7: complete the single
         * core_slice ensure path. PLATFORM: SHARED.
         */
        {
            const char *csmod_rel = "core/slice/mod.o";
            const char *p_csmod = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, csmod_rel));
            if (!p_csmod && bank)
                p_csmod = xlang_asm_ld_try_under_lib_roots(csmod_rel, lib_roots, n_lib_roots, bank);
            if (p_csmod)
                link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p_csmod);
        }
    }
    if (labi_od_user_needs_any_sym_table(user_o, labi_od_kv_sym_count(), labi_od_kv_sym_at)) {
        /* PLATFORM: SHARED — L4 wipe deletes kv.o; push skip-missing is not
         * enough (≡ need_sys / need_net). Produce path is formal_mod
         * mod.x+kv.x (was std_x auto-soft kv.x only → T db_kv_*). G.7 complete
         * existing kv table with formal ensure + glue ensure. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0])
                (void)xlang_ensure_formal_std_make_o(include_root, "std/db/kv/kv.o",
                                                    "../std/db/kv/kv.o");
        }
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, labi_od_kv_rel()));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_kv_rel(), lib_roots, n_lib_roots, bank);
        if (p)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
        if (p)
            link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_kv_mmap_glue_o,
                xlang_runtime_kv_mmap_glue_o_path(link_argv0), link_argv0,
                labi_od_kv_glue_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la);
    }
    if (labi_od_user_needs_any_sym_table(user_o, labi_od_arrow_sym_count(), labi_od_arrow_sym_at)) {
        /* PLATFORM: SHARED — L4 wipe deletes arrow.o; skip-missing never
         * ensure (≡ kv). Produce path is formal_mod mod.x+arrow.x.
         * arrow.o U arrow_column_f32_*_c (simd glue) and simd_hw_available_c
         * (simd c_face C ABI). Darwin -dead_strip hid unused simd T; Ubuntu
         * gold exposes UNDEF. G.7 complete existing arrow table. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0]) {
                (void)xlang_ensure_formal_std_make_o(include_root, "std/db/arrow/arrow.o",
                                                    "../std/db/arrow/arrow.o");
                (void)xlang_ensure_formal_std_make_o(include_root, "std/simd/simd.o",
                                                    "../std/simd/simd.o");
            }
        }
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, labi_od_arrow_rel()));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_arrow_rel(), lib_roots, n_lib_roots, bank);
        if (p)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
        if (p) {
            link_abi_asm_ld_push_obj(NULL, link_argv0, "std/simd/simd.o", lib_roots, n_lib_roots,
                                     bank, argv, la, max_la, NULL);
            link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_arrow_simd_glue_o,
                xlang_runtime_arrow_simd_glue_o_path(link_argv0), link_argv0,
                labi_od_arrow_glue_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la);
        }
    }
    if (labi_od_user_needs_any_sym_table(user_o, labi_od_async_sym_count(), labi_od_async_sym_at)) {
        /* PLATFORM: SHARED — leftover unique UNDEF std_async_placeholder /
         * std_async_drain_idle / std_async_scheduler_reset /
         * std_async_net_fs_async_smoke. No async.o existed; scheduler C ABI
         * table never fires unique import METHOD. Produce path is formal_mod
         * c_face. drain_idle / scheduler_reset / net_fs U xlang_async_* →
         * scheduler glue ensure (async_net_fs #include). G.7 complete unique
         * table; do not dump unique names into labi_od_async_scheduler_sym_*. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0])
                (void)xlang_ensure_formal_std_make_o(include_root, "std/async/async.o",
                                                    "../std/async/async.o");
        }
        p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, labi_od_async_rel()));
        if (!p && bank)
            p = xlang_asm_ld_try_under_lib_roots(labi_od_async_rel(), lib_roots, n_lib_roots, bank);
        if (p)
            link_abi_asm_ld_argv_push_stable(bank, argv, la, max_la, p);
        if (p)
            link_abi_asm_ld_push_glue_after_std(1, xlang_ensure_runtime_scheduler_glue_o,
                xlang_runtime_scheduler_glue_o_path(link_argv0), link_argv0,
                labi_od_rel_scheduler_glue(), lib_roots, n_lib_roots, bank, argv, la, max_la);
    }
    if (link_abi_user_o_needs_std_test(user_o)) {
        /* PLATFORM: SHARED — Darwin -backend asm run-stdtest. Cold L4 leaves L8c
         * unused, so this full L8b seed is the on_demand body. Do not gate
         * companions on have_test (g12 may already have test.o). G.7 ≡ queue:
         * always push test.o then labi_std_append_test_monofile_companions. */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0])
                (void)xlang_ensure_formal_std_make_o(include_root, "std/test/test.o",
                                                    "../std/test/test.o");
        }
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_test(), lib_roots, n_lib_roots,
                                 bank, argv, la, max_la, NULL);
        labi_std_append_test_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la);
    }
    /*
     * PLATFORM: LINUX freestanding / SHARED gate —
     * runtime_heap_user.o wraps libc malloc/free/realloc. Under -freestanding
     * (-nostdlib) that yields U malloc. Zero-libc product heap is page_mmap
     * (co-emit or formal); never push heap_user on freestanding links.
     * G.7: complete existing heap_user on_demand authority (no second path).
     */
    if (!driver_freestanding_get() && link_abi_link_needs_heap_user_c(user_o, argv, la ? *la : 0)) {
        if (xlang_ensure_runtime_heap_user_o(link_argv0) != 0)
            return;
        link_abi_asm_ld_push_obj(xlang_runtime_heap_user_o_path(link_argv0), link_argv0, labi_od_rel_heap_user(),
                                 lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        if (flags)
            flags->have_libc_heap = 1;
    }
    /* Simple multi-sym groups → single rel (pure table). Formal ensure for core/*.o. */
    {
        int pushed_core_formal = 0;
        for (sg = 0; sg < labi_od_simple_group_count(); sg++) {
            const char *rel = labi_od_simple_group_rel(sg);
            if (!rel || !rel[0])
                continue;
            if (!labi_od_user_needs_simple_group(user_o, sg))
                continue;
            /* PLATFORM: SHARED — L4 wipe drops gitignored formal std/core .o.
             * G.7: ensure by rel for every simple-group hit (≡ pure heavy generic
             * ensure). Covers g12..g19 (test/assert/fmt/compress/driver/debug/simd/io)
             * and legacy core/* + encoding. Do not leave seed-only subset. */
            {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                char make_tgt[PATH_MAX];
                if (include_root && include_root[0] &&
                    (size_t)snprintf(make_tgt, sizeof make_tgt, "../%s", rel) < sizeof make_tgt)
                    (void)xlang_ensure_formal_std_make_o(include_root, rel, make_tgt);
                if (strstr(rel, "core/"))
                    pushed_core_formal = 1;
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, rel, lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
            /* PLATFORM: SHARED — 9.2.2: facade compress.o is c_face stub (return -1).
             * Real zlib/gzip live in submodule formal .o (mod+libz). Companion ≡
             * encoding.o → string/base64. Glue provides deflateInit2/inflateInit2. */
            if (strstr(rel, "std/compress/compress.o")) {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0]) {
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/compress/zlib/zlib.o",
                                                        "../std/compress/zlib/zlib.o");
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/compress/gzip/gzip.o",
                                                        "../std/compress/gzip/gzip.o");
                }
                link_abi_asm_ld_push_obj(NULL, link_argv0, "std/compress/zlib/zlib.o", lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                link_abi_asm_ld_push_obj(NULL, link_argv0, "std/compress/gzip/gzip.o", lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                /* Glue + -lz stay in asm_ld_append_compress_libs (needs_zlib).
                 * Do not push runtime_compress_zlib_glue.o here (duplicate T). */
            }
            /* PLATFORM: SHARED — g12 std/test/test.o monofile C dual (≡ need_test). */
            if (strstr(rel, "std/test/test.o"))
                labi_std_append_test_monofile_companions(link_argv0, lib_roots, n_lib_roots,
                                                       bank, argv, la, max_la);
            /* PLATFORM: SHARED — encoding.o U std_base64_* + std_string_string_* helpers.
             * User.o only U encoding_*; g0/g3 alone miss. Companion ≡ g9 slice glue. */
            if (strstr(rel, "std/encoding/encoding.o")) {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0]) {
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/string/string.o",
                                                        "../std/string/string.o");
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/base64/base64.o",
                                                        "../std/base64/base64.o");
                }
                link_abi_asm_ld_push_obj(NULL, link_argv0, "std/string/string.o", lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                link_abi_asm_ld_push_obj(NULL, link_argv0, "std/base64/base64.o", lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
            }
            /* PLATFORM: SHARED — bytes.o U heap.alloc/realloc/copy/free (mod.x grow/extend).
             * User.o for roundtrip only U std_bytes_* so heap_api needles miss.
             * Companion ≡ encoding.o → string/base64. Also co-push string.o for as_view.
             */
            if (strstr(rel, "std/bytes/bytes.o")) {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0]) {
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o",
                                                        "../std/heap/heap.o");
                    (void)xlang_ensure_formal_std_make_o(include_root, "std/string/string.o",
                                                        "../std/string/string.o");
                }
                link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_heap(), lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
                link_abi_asm_ld_push_obj(NULL, link_argv0, "std/string/string.o", lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
            }
            /* PLATFORM: SHARED — formal mod.o U from_ptr/subslice → always co-push glue slice.o.
             * User.o for length.x has no U core_slice_*_from_ptr_c, so needs_core_slice alone misses glue. */
            if (strstr(rel, "core/slice/mod.o")) {
                const char *include_root = xlang_repo_root_from_argv0(link_argv0);
                if (include_root && include_root[0])
                    (void)xlang_ensure_formal_std_make_o(include_root, "core/slice/slice.o",
                                                        "../core/slice/slice.o");
                link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_slice(), lib_roots, n_lib_roots,
                                         bank, argv, la, max_la, NULL);
            }
        }
        /*
         * Formal core/*.o from xlang_compile_std_module carry preamble weak process_arg*_c
         * → U process_xlang_*. Same complement as sync/atomic: push process_argv (not process.o).
         * PLATFORM: SHARED — Ubuntu asm si residual after ELF UNDEF scan.
         */
        if (pushed_core_formal) {
            (void)xlang_ensure_runtime_process_argv_o(link_argv0);
            link_abi_asm_ld_push_obj(xlang_runtime_process_argv_o_path(link_argv0), link_argv0,
                "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    /*
     * PLATFORM: SHARED — string/heap/vec/mem formal .o carry preamble weak process_arg*_c
     * → U process_xlang_*. fk0 string push does not set have_math/sync flags, so the std_objs
     * process_argv complement never fired (Ubuntu string_asm residual).
     * G.7: complete existing process_argv complement by scanning argv after on_demand.
     */
    if (argv && la) {
        int need_pav = 0;
        int ai;
        int have_process_o = 0;
        for (ai = 0; ai < *la && argv[ai]; ai++) {
            const char *e = argv[ai];
            if (!link_abi_ld_argv_entry_is_obj(e))
                continue;
            if (strstr(e, "process.o") && !strstr(e, "process_argv"))
                have_process_o = 1;
            if (xlang_link_obj_needs_undef_sym(e, "process_xlang_argc_get")
                || xlang_link_obj_needs_undef_sym(e, "process_xlang_argv_get"))
                need_pav = 1;
        }
        if (need_pav && !have_process_o) {
            (void)xlang_ensure_runtime_process_argv_o(link_argv0);
            link_abi_asm_ld_push_obj(xlang_runtime_process_argv_o_path(link_argv0), link_argv0,
                "compiler/runtime_process_argv.o", lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    /*
     * PLATFORM: SHARED — std/cache/cache.o (fk0) U time_now_monotonic_ns_c after
     * push; user.o only has std_cache_* so time-table / need_time_os never fire.
     * G.7: mirror process_argv complement — scan argv objs for the C face UNDEF,
     * then ensure + push runtime_time_os.o (STD-087 lru_pool_smoke).
     */
    if (argv && la) {
        int need_tos = 0;
        int have_tos = 0;
        int ti;
        for (ti = 0; ti < *la && argv[ti]; ti++) {
            const char *e = argv[ti];
            if (!link_abi_ld_argv_entry_is_obj(e))
                continue;
            if (strstr(e, "runtime_time_os.o"))
                have_tos = 1;
            if (xlang_link_obj_needs_undef_sym(e, "time_now_monotonic_ns_c"))
                need_tos = 1;
        }
        if (need_tos && !have_tos) {
            if (xlang_ensure_runtime_time_os_o(link_argv0) == 0)
                link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                    labi_od_time_os_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    /*
     * PLATFORM: SHARED — std/security/security.o (fk0) U std_crypto_mem_eq /
     * crypto_hmac_sha256_c / std_random_fill_bytes after push; user.o only has
     * std_security_* so fk4 crypto / random gates never fire. G.7: mirror
     * process_argv / time_os complement (STD-079 roundtrip).
     */
    if (argv && la) {
        int need_crypto = 0;
        int need_hmac = 0;
        int need_rand = 0;
        int have_crypto = 0;
        int have_hmac = 0;
        int have_rand = 0;
        int ci;
        for (ci = 0; ci < *la && argv[ci]; ci++) {
            const char *e = argv[ci];
            if (!link_abi_ld_argv_entry_is_obj(e))
                continue;
            if (strstr(e, "std/crypto/crypto.o"))
                have_crypto = 1;
            if (strstr(e, "runtime_crypto_inc_glue.o"))
                have_hmac = 1;
            if (strstr(e, "std/random/random.o"))
                have_rand = 1;
            if (xlang_link_obj_needs_undef_sym(e, "std_crypto_mem_eq")
                || xlang_link_obj_needs_undef_sym(e, "crypto_mem_eq_c"))
                need_crypto = 1;
            if (xlang_link_obj_needs_undef_sym(e, "crypto_hmac_sha256_c"))
                need_hmac = 1;
            if (xlang_link_obj_needs_undef_sym(e, "std_random_fill_bytes"))
                need_rand = 1;
        }
        if (need_crypto && !have_crypto) {
            const char *root_c = xlang_repo_root_from_argv0(link_argv0);
            if (root_c && root_c[0])
                (void)xlang_ensure_formal_std_make_o(root_c, "std/crypto/crypto.o",
                                                    "../std/crypto/crypto.o");
            link_abi_asm_ld_push_obj(NULL, link_argv0, "std/crypto/crypto.o",
                lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_hmac && !have_hmac) {
            /* CRYPTO_PAIR: ed25519_ref10 (sha512) + crypto_inc (hmac_sha256_c). */
            (void)xlang_ensure_runtime_ed25519_ref10_glue_o(link_argv0);
            link_abi_asm_ld_push_obj(xlang_runtime_ed25519_ref10_glue_o_path(link_argv0),
                link_argv0, "compiler/runtime_ed25519_ref10_glue.o",
                lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
            (void)xlang_ensure_runtime_crypto_inc_glue_o(link_argv0);
            link_abi_asm_ld_push_obj(xlang_runtime_crypto_inc_glue_o_path(link_argv0),
                link_argv0, "compiler/runtime_crypto_inc_glue.o",
                lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
        if (need_rand && !have_rand) {
            const char *root_r = xlang_repo_root_from_argv0(link_argv0);
            if (root_r && root_r[0])
                (void)xlang_ensure_formal_std_make_o(root_r, "std/random/random.o",
                                                    "../std/random/random.o");
            link_abi_asm_ld_push_obj(NULL, link_argv0, "std/random/random.o",
                lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    /*
     * PLATFORM: SHARED — std/result/result.o (fk0) U std_error_ok after push;
     * user.o may only have std_result_* so fk0 k8 error gate never fires.
     * G.7: mirror security→crypto (STD-080/081 roundtrip).
     */
    if (argv && la) {
        int need_err = 0;
        int have_err = 0;
        int ei;
        for (ei = 0; ei < *la && argv[ei]; ei++) {
            const char *e = argv[ei];
            if (!link_abi_ld_argv_entry_is_obj(e))
                continue;
            if (strstr(e, "std/error/error.o"))
                have_err = 1;
            if (xlang_link_obj_needs_undef_sym(e, "std_error_ok"))
                need_err = 1;
        }
        if (need_err && !have_err) {
            const char *root_e = xlang_repo_root_from_argv0(link_argv0);
            if (root_e && root_e[0])
                (void)xlang_ensure_formal_std_make_o(root_e, "std/error/error.o",
                                                    "../std/error/error.o");
            link_abi_asm_ld_push_obj(NULL, link_argv0, "std/error/error.o",
                lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        }
    }
    if (labi_od_user_needs_any_sym_table(user_o, labi_od_time_sym_count(), labi_od_time_sym_at)) {
        /* PLATFORM: SHARED — L4 wipe drops formal time.o; push_obj skip_missing alone
         * leaves U std_time_*. G.7: ensure formal before push (same as plan STD block). */
        {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0])
                (void)xlang_ensure_formal_std_make_o(include_root, "std/time/time.o",
                                                    "../std/time/time.o");
        }
        if (xlang_ensure_runtime_time_os_o(link_argv0) == 0)
            link_abi_asm_ld_push_obj(xlang_runtime_time_os_o_path(link_argv0), link_argv0,
                                     labi_od_time_os_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
        link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_time_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
    }
    /*
     * PLATFORM: SHARED — product queue (std_queue_*) + monofile companions.
     * G.7: single helper labi_std_append_queue_monofile_companions.
     */
    {
        int need_q_product = link_abi_user_o_needs_std_queue(user_o);
        int need_q_contention = labi_od_user_needs_any_sym_table(user_o, labi_od_queue_sym_count(), labi_od_queue_sym_at);
        if (need_q_product || need_q_contention) {
            const char *include_root = xlang_repo_root_from_argv0(link_argv0);
            if (include_root && include_root[0]) {
                (void)xlang_ensure_formal_std_make_o(include_root, "std/queue/queue.o", "../std/queue/queue.o");
                (void)xlang_ensure_formal_std_make_o(include_root, "std/heap/heap.o", "../std/heap/heap.o");
                (void)xlang_ensure_formal_std_make_o(include_root, "core/mem/mem.o", "../core/mem/mem.o");
            }
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_queue_rel(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_heap(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
            link_abi_asm_ld_push_obj(NULL, link_argv0, labi_od_rel_core_mem(), lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
            labi_std_append_queue_monofile_companions(link_argv0, lib_roots, n_lib_roots, bank, argv, la, max_la, flags);
        }
    }
#else
    (void)link_argv0;
    (void)user_o;
    (void)lib_roots;
    (void)n_lib_roots;
    (void)bank;
    (void)argv;
    (void)la;
    (void)max_la;
    (void)flags;
#endif
}

#else
int labi_od_simple_group_count(void);
int labi_od_simple_group_sym_count(int g);
const char *labi_od_simple_group_sym_at(int g, int i);
const char *labi_od_simple_group_rel(int g);
int labi_od_kv_sym_count(void);
const char *labi_od_kv_sym_at(int i);
const char *labi_od_kv_rel(void);
const char *labi_od_kv_glue_rel(void);
int labi_od_arrow_sym_count(void);
const char *labi_od_arrow_sym_at(int i);
const char *labi_od_arrow_rel(void);
const char *labi_od_arrow_glue_rel(void);
int labi_od_async_sym_count(void);
const char *labi_od_async_sym_at(int i);
const char *labi_od_async_rel(void);
int labi_od_time_sym_count(void);
const char *labi_od_time_sym_at(int i);
const char *labi_od_time_rel(void);
const char *labi_od_time_os_rel(void);
int labi_od_queue_sym_count(void);
const char *labi_od_queue_sym_at(int i);
const char *labi_od_queue_rel(void);
const char *labi_od_queue_contention_rel(void);
int labi_od_net_sym_count(void);
const char *labi_od_net_sym_at(int i);
int link_abi_user_o_needs_std_net(const char *user_o);
int labi_od_set_sym_count(void);
const char *labi_od_set_sym_at(int i);
int link_abi_user_o_needs_std_set(const char *user_o);
int labi_od_map_sym_count(void);
const char *labi_od_map_sym_at(int i);
int link_abi_user_o_needs_std_map(const char *user_o);
int labi_od_queue_api_sym_count(void);
const char *labi_od_queue_api_sym_at(int i);
int link_abi_user_o_needs_std_queue(const char *user_o);
int labi_od_test_sym_count(void);
const char *labi_od_test_sym_at(int i);
int link_abi_user_o_needs_std_test(const char *user_o);
int labi_od_core_mem_sym_count(void);
const char *labi_od_core_mem_sym_at(int i);
int link_abi_user_o_needs_core_mem(const char *user_o);
int labi_od_core_slice_sym_count(void);
const char *labi_od_core_slice_sym_at(int i);
int link_abi_user_o_needs_core_slice(const char *user_o);
int labi_od_page_mmap_sym_count(void);
const char *labi_od_page_mmap_sym_at(int i);
int link_abi_user_o_needs_std_heap_page_mmap(const char *user_o);
int labi_od_sys_linux_sym_count(void);
const char *labi_od_sys_linux_sym_at(int i);
int link_abi_user_o_needs_std_sys_linux(const char *user_o);
int labi_od_sys_macos_sym_count(void);
const char *labi_od_sys_macos_sym_at(int i);
int link_abi_user_o_needs_std_sys_macos(const char *user_o);
int labi_od_sys_sym_count(void);
const char *labi_od_sys_sym_at(int i);
int link_abi_user_o_needs_std_sys(const char *user_o);
int labi_od_heap_api_sym_count(void);
const char *labi_od_heap_api_sym_at(int i);
int link_abi_user_o_needs_std_heap_api(const char *user_o);
int labi_od_heap_user_sym_count(void);
const char *labi_od_heap_user_sym_at(int i);
int link_abi_user_o_needs_heap_user_syms(const char *user_o);
int labi_od_async_scheduler_sym_count(void);
const char *labi_od_async_scheduler_sym_at(int i);
int link_abi_user_o_needs_async_scheduler(const char *user_o);
int labi_od_zlib_undef_sym_count(void);
const char *labi_od_zlib_undef_sym_at(int i);
const char *labi_od_compress_zlib_marker(void);
int labi_od_zstd_undef_sym_count(void);
const char *labi_od_zstd_undef_sym_at(int i);
const char *labi_od_compress_zstd_marker(void);
int labi_od_brotli_undef_sym_count(void);
const char *labi_od_brotli_undef_sym_at(int i);
const char *labi_od_compress_brotli_marker(void);
int link_abi_obj_needs_zlib(const char *obj_o);
int link_abi_obj_needs_zstd(const char *obj_o);
int link_abi_obj_needs_brotli(const char *obj_o);
int link_abi_user_o_needs_compress_libs(const char *user_o);
int labi_od_runtime_time_os_sym_count(void);
const char *labi_od_runtime_time_os_sym_at(int i);
int labi_user_needs_runtime_time_os(const char *user_o);
int labi_od_runtime_random_fill_sym_count(void);
const char *labi_od_runtime_random_fill_sym_at(int i);
int labi_user_needs_runtime_random_fill(const char *user_o);
int labi_od_runtime_env_os_sym_count(void);
const char *labi_od_runtime_env_os_sym_at(int i);
int labi_user_needs_runtime_env_os(const char *user_o);
int labi_od_runtime_process_argv_sym_count(void);
const char *labi_od_runtime_process_argv_sym_at(int i);
int labi_user_needs_runtime_process_argv(const char *user_o);
int labi_od_std_task_sym_count(void);
const char *labi_od_std_task_sym_at(int i);
int labi_user_needs_std_task(const char *user_o);
int labi_fk0_rel_count(void);
const char *labi_fk0_rel_at(int k);
int labi_fk0_sym_count(int k);
const char *labi_fk0_sym_at(int k, int i);
int labi_std_fk0_user_needs_rel(const char *user_o, const char *rel);
int labi_std_fk_gate_sym_count(int fk);
const char *labi_std_fk_gate_sym_at(int fk, int i);
int labi_std_fk_user_needs(const char *user_o, int fk);
int labi_od_provides_core_mem_sym_count(void);
const char *labi_od_provides_core_mem_sym_at(int i);
int link_abi_user_o_provides_core_mem(const char *user_o);
int labi_od_provides_std_heap_sym_count(void);
const char *labi_od_provides_std_heap_sym_at(int i);
int link_abi_user_o_provides_std_heap(const char *user_o);
int link_abi_link_needs_heap_user_c(const char *user_o, const char **argv, int la);
int link_abi_link_needs_std_heap_import(const char *user_o, const char **argv, int la);
const char *labi_od_rel_net(void);
const char *labi_od_rel_thread(void);
const char *labi_od_rel_vec(void);
const char *labi_od_rel_http(void);
const char *labi_od_rel_heap(void);
const char *labi_od_rel_set(void);
const char *labi_od_rel_map(void);
const char *labi_od_rel_async_scheduler(void);
const char *labi_od_rel_core_mem(void);
const char *labi_od_rel_sys_linux(void);
const char *labi_od_rel_sys_macos(void);
const char *labi_od_rel_page_mmap(void);
const char *labi_od_rel_sys(void);
const char *labi_od_rel_core_slice(void);
const char *labi_od_rel_test(void);
const char *labi_od_rel_heap_user(void);
const char *labi_od_rel_scheduler_glue(void);
const char *labi_od_rel_thread_glue(void);
const char *labi_od_rel_http_glue(void);
const char *labi_od_rel_net_udp_batch(void);
const char *labi_od_rel_net_workers(void);
const char *labi_od_rel_test_fn_invoke(void);
/* wave197: product on_demand shell pure orch (L8b). */
void xlang_asm_ld_append_on_demand_user_objs(const char *link_argv0, const char *user_o,
    const char **lib_roots, int n_lib_roots, ShuAsmLdPathBank *bank,
    const char **argv, int *la, int max_la, ShuAsmLdStdLinkFlags *flags);
#endif

int labi_ondemand_list_slice_marker(void) {
  return 1;
}