/* seeds/labi_freestanding_list.from_x.c — G-02f-276 P2 link_abi L7 freestanding list pure → R2 full
 * Logic source: src/runtime/labi_freestanding_list.x
 * Hybrid: XLANG_LABI_FREESTANDING_LIST_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14 / wave117 / wave136）：公共业务符号由 full .x 提供：
 *   labi_fs_env_freestanding
 *   labi_fs_io_sym_{count,at} + labi_fs_panic_sym
 *   labi_fs_ensure_catalog_{count,step_at}
 *   labi_fs_ensure_{out_base,src_rel,stem}
 *   labi_fs_{crt0,io}_{out_base,src_rel}
 *   + labi_fs_heap_{c_needle,o_sym}_* + labi_fs_memcpy_face_sym_* (wave117 tables)
 *   + link_abi_{generated_c,user_o}_needs_libc_heap
 *   + link_abi_user_o_needs_freestanding_nostdlib_face
 *   + wave136 labi_fs_gen_{fs,random,time,runtime}_needle_* +
 *     link_abi_generated_c_needs_{fs,random,time,runtime} pure orch
 *   + wave137 labi_fs_gen_{zlib,zstd,brotli}_needle_* +
 *     link_abi_generated_c_needs_{zlib,zstd,brotli} pure orch
 *   + wave138 labi_fs_gen_{core_slice,db_kv,db_arrow}_needle_* +
 *     link_abi_generated_c_needs_{core_slice,db_kv,db_arrow} pure orch
 *   + wave139 labi_fs_gen_provides_{core_mem,std_heap}_needle_* +
 *     link_abi_generated_c_provides_{core_mem,std_heap} pure orch
 *   + wave141 labi_fs_gen_{win32,win32_wsa}_needle_* +
 *     link_abi_generated_c_needs_{win32,win32_wsa} pure orch
 *   + wave142 link_abi_generated_c_needs_{core_builtin,core_mem} pure stub0 orch
 *   + wave143 labi_fs_gen_async_scheduler_needle_* +
 *     xlang_generated_c_needs_async_scheduler pure orch
 *   + wave144 xlang_freestanding_user_o_needs_{io,panic} pure orch
 *     (io_sym / panic_sym tables + undef_sym Cap residual)
 *   + wave159 xlang_link_freestanding_enabled pure orch
 *     (peer host_is_linux + pure env name + Cap residual link_abi_getenv wave223)
 *   + wave167 xlang_ensure_crt0_user_o pure orch
 *     (peer freestanding_enabled + tables + Cap residual resolve/access/cc/stat)
 *   + wave168 xlang_ensure_freestanding_io_o pure orch
 *     (peer freestanding_enabled + io tables + Cap residual resolve/access/cc/stat)
 *   + wave175 link_abi_generated_c_contains_substr pure orch
 *     (pure null gates + Cap residual malloc/free + Cap residual buf_contains_substr)
 *   + wave176 link_abi_generated_c_contains_substr_use_line pure orch
 *     (pure null gates + Cap residual malloc/free + Cap residual buf use_line scan)
 *   + wave177 link_abi_generated_c_contains_any_substr_use_line pure orch
 *     (pure thin loop → pure contains_substr_use_line)
 *   + wave178 link_abi_generated_c_contains_any_substr pure orch
 *     (pure thin loop → pure contains_substr; raw multi-needle)
 * Cap residual：undef_sym；link_abi_getenv（wave223 G.7）；ensure 叶的 resolve/access/cc/stat（wave167/168）；
 *   file malloc/free + buf_contains_substr（wave175）；buf_contains_substr_use_line（wave176）。
 * FROM_X 下本文件仅前向声明 + slice marker。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* wave223 G.7: env lookup authority = public pure thin link_abi_getenv (labi_diag_pure). */
const char *link_abi_getenv(const char *name);

/* Cap residual (mega/runtime always): nm UNDEF probe used by pure needs orch. */
int xlang_link_obj_needs_undef_sym(const char *user_o, const char *sym);
/* Cap residual (wave175/176): whole-file malloc + buf / use_line scan (mega). */
char *runtime_read_file_malloc(const char *path, size_t *out_len);
int link_abi_buf_contains_substr(const char *data, size_t data_len, const char *needle);
int link_abi_buf_contains_substr_use_line(const char *data, size_t data_len, const char *needle);
/* Peer pure (host_lit) used by wave159 freestanding_enabled cold twin. */
int xlang_host_is_linux(void);
/* Cap residual (wave167/168 ensure cold twin; mega always provides). */
int xlang_resolve_compiler_dir(const char *argv0, char *out_dir, size_t out_dir_sz);
int link_abi_path_readable(const char *path);
int xlang_cc_compile_sync(const char *src, const char *out_o, const char *inc0, const char *inc1,
                         const char *inc2, int from_asm_s);
const char *asm_link_obj_skip_missing(const char *path);
/* Peer pure path ladder (path_pure L0 wave164/165; mega always provides). */
const char *xlang_crt0_user_o_path(const char *argv0);
const char *xlang_freestanding_io_o_path(const char *argv0);
/* Peer pure diags (diag_pure L1; mega always provides). */
void link_diag_runtime_obj_resolve_fail(const char *obj_name, const char *hint);
void link_diag_runtime_source_missing(const char *obj_name, const char *source_path);
void link_diag_runtime_obj_build_status(const char *obj_name, int status);
void link_diag_runtime_obj_missing(const char *obj_name, const char *out_o);

#ifndef XLANG_LABI_FREESTANDING_LIST_FROM_X

/* ---- env ---- */
const char *labi_fs_env_freestanding(void) {
  return "XLANG_FREESTANDING";
}

/* ---- freestanding_io probe symbols (any undef → needs io) ---- */
int labi_fs_io_sym_count(void) {
  return 16;
}

const char *labi_fs_io_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "xlang_sys_write";
  if (i == 1)
    return "xlang_sys_read";
  if (i == 2)
    return "xlang_sys_close";
  if (i == 3)
    return "xlang_sys_exit";
  if (i == 4)
    return "xlang_sys_open";
  if (i == 5)
    return "xlang_sys_openat";
  if (i == 6)
    return "xlang_sys_mmap";
  if (i == 7)
    return "xlang_sys_munmap";
  if (i == 8)
    return "xlang_sys_socket";
  if (i == 9)
    return "xlang_sys_connect";
  if (i == 10)
    return "xlang_sys_bind";
  if (i == 11)
    return "xlang_sys_listen";
  if (i == 12)
    return "xlang_sys_accept";
  if (i == 13)
    return "backtrace_capture_c";
  if (i == 14)
    return "backtrace_symbolicate_c";
  if (i == 15)
    return "xlang_target_cpu_detect_host";
  return NULL;
}

/* ---- freestanding panic probe ---- */
const char *labi_fs_panic_sym(void) {
  return "xlang_panic_";
}

/* ---- ensure catalog: out basename + asm source under compiler dir ---- */
int labi_fs_ensure_catalog_count(void) {
  return 2;
}

int labi_fs_ensure_catalog_step_at(int i, const char **stem_out, const char **out_base_out,
                                   const char **src_rel_out) {
  if (i < 0 || i >= 2)
    return 0;
  if (i == 0) {
    if (stem_out)
      *stem_out = "crt0_user";
    if (out_base_out)
      *out_base_out = "crt0_user.o";
    if (src_rel_out)
      *src_rel_out = "src/asm/crt0_user_x86_64.s";
    return 1;
  }
  if (i == 1) {
    if (stem_out)
      *stem_out = "freestanding_io";
    if (out_base_out)
      *out_base_out = "freestanding_io.o";
    if (src_rel_out)
      *src_rel_out = "src/asm/freestanding_io_x86_64.s";
    return 1;
  }
  return 0;
}

const char *labi_fs_ensure_out_base(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "crt0_user.o";
  if (i == 1)
    return "freestanding_io.o";
  return NULL;
}

const char *labi_fs_ensure_src_rel(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "src/asm/crt0_user_x86_64.s";
  if (i == 1)
    return "src/asm/freestanding_io_x86_64.s";
  return NULL;
}

const char *labi_fs_ensure_stem(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "crt0_user";
  if (i == 1)
    return "freestanding_io";
  return NULL;
}

/* convenience accessors matching historic names */
const char *labi_fs_crt0_out_base(void) { return "crt0_user.o"; }
const char *labi_fs_crt0_src_rel(void) { return "src/asm/crt0_user_x86_64.s"; }
const char *labi_fs_io_out_base(void) { return "freestanding_io.o"; }
const char *labi_fs_io_src_rel(void) { return "src/asm/freestanding_io_x86_64.s"; }

/* ---- wave117: heap / nostdlib face pure tables + orch ---- */
int labi_fs_heap_c_needle_count(void) { return 9; }
const char *labi_fs_heap_c_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "malloc";
  if (i == 1)
    return "calloc";
  if (i == 2)
    return "realloc";
  if (i == 3)
    return "posix_memalign";
  if (i == 4)
    return "heap_alloc_c";
  if (i == 5)
    return "heap_free_c";
  if (i == 6)
    return "heap_realloc_c";
  if (i == 7)
    return "heap_alloc_zeroed_c";
  if (i == 8)
    return "getenv";
  return NULL;
}
int labi_fs_heap_o_sym_count(void) { return 6; }
const char *labi_fs_heap_o_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "malloc";
  if (i == 1)
    return "calloc";
  if (i == 2)
    return "realloc";
  if (i == 3)
    return "free";
  if (i == 4)
    return "posix_memalign";
  if (i == 5)
    return "getenv";
  return NULL;
}
int labi_fs_memcpy_face_sym_count(void) { return 3; }
const char *labi_fs_memcpy_face_sym_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "memcpy";
  if (i == 1)
    return "memcmp";
  if (i == 2)
    return "memset";
  return NULL;
}

/* wave175: pure orch contains_substr (cold twin ≡ .x).
 * Cap residual: runtime_read_file_malloc + free + link_abi_buf_contains_substr.
 * Pure: null/empty gates + load/scan orch. PLATFORM: SHARED — not use_line.
 */
int link_abi_generated_c_contains_substr(const char *c_path, const char *needle) {
  size_t raw_len;
  char *data;
  int hit;
  if (!c_path || !c_path[0] || !needle || !needle[0])
    return 0;
  raw_len = 0;
  data = runtime_read_file_malloc(c_path, &raw_len);
  if (!data)
    return 0;
  hit = link_abi_buf_contains_substr(data, raw_len, needle);
  free(data);
  return hit;
}

/* wave176: pure orch contains_substr_use_line (cold twin ≡ .x).
 * Cap residual: runtime_read_file_malloc + free + link_abi_buf_contains_substr_use_line.
 * Pure: null/empty gates + load/scan orch. PLATFORM: SHARED — line filter in Cap residual.
 */
int link_abi_generated_c_contains_substr_use_line(const char *c_path, const char *needle) {
  size_t raw_len;
  char *data;
  int hit;
  if (!c_path || !c_path[0] || !needle || !needle[0])
    return 0;
  raw_len = 0;
  data = runtime_read_file_malloc(c_path, &raw_len);
  if (!data)
    return 0;
  hit = link_abi_buf_contains_substr_use_line(data, raw_len, needle);
  free(data);
  return hit;
}

/* wave177: pure orch any_substr_use_line (cold twin ≡ .x).
 * Thin loop over pure contains_substr_use_line. PLATFORM: SHARED.
 */
int link_abi_generated_c_contains_any_substr_use_line(const char *c_path, const char **needles,
                                                     int n_needles) {
  int i;
  if (!c_path || !needles || n_needles <= 0)
    return 0;
  for (i = 0; i < n_needles; i++) {
    if (needles[i] && needles[i][0] &&
        link_abi_generated_c_contains_substr_use_line(c_path, needles[i]))
      return 1;
  }
  return 0;
}

/* wave178: pure orch any_substr (cold twin ≡ .x).
 * Thin loop over pure contains_substr (raw multi-needle; no line filter).
 * Empty needles skipped (aligned with pure contains_substr). PLATFORM: SHARED.
 */
int link_abi_generated_c_contains_any_substr(const char *c_path, const char **needles,
                                            int n_needles) {
  int i;
  if (!c_path || !needles || n_needles <= 0)
    return 0;
  for (i = 0; i < n_needles; i++) {
    if (needles[i] && needles[i][0] &&
        link_abi_generated_c_contains_substr(c_path, needles[i]))
      return 1;
  }
  return 0;
}

/* Pure orch: table + peer pure contains_substr. PLATFORM: SHARED. */
int link_abi_generated_c_needs_libc_heap(const char *c_path) {
  int n;
  int i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_heap_c_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_heap_c_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* Pure orch: table + Cap residual undef_sym. PLATFORM: SHARED. */
int link_abi_user_o_needs_libc_heap(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_fs_heap_o_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_fs_heap_o_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* Pure orch: heap + mem* face. PLATFORM: LINUX freestanding face / SHARED tables. */
int link_abi_user_o_needs_freestanding_nostdlib_face(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  if (link_abi_user_o_needs_libc_heap(user_o) != 0)
    return 1;
  n = labi_fs_memcpy_face_sym_count();
  for (i = 0; i < n; i++) {
    const char *sym = labi_fs_memcpy_face_sym_at(i);
    if (sym && sym[0] && xlang_link_obj_needs_undef_sym(user_o, sym) != 0)
      return 1;
  }
  return 0;
}

/* wave136: generated-C string needs pure cold twin (tables + orch). */
int labi_fs_gen_fs_needle_count(void) {
  return 5;
}
const char *labi_fs_gen_fs_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "fs_open_read_c";
  if (i == 1)
    return "fs_last_error_c";
  if (i == 2)
    return "fs_close_c";
  if (i == 3)
    return "fs_read_c";
  if (i == 4)
    return "fs_write_c";
  return NULL;
}
int labi_fs_gen_random_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_random_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "random_rng_smoke_c";
  if (i == 1)
    return "random_fill_bytes_c";
  if (i == 2)
    return "random_u64_c";
  return NULL;
}
int labi_fs_gen_time_needle_count(void) {
  return 10;
}
const char *labi_fs_gen_time_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "std_time_now_monotonic_ns";
  if (i == 1)
    return "std_time_sleep_ms";
  if (i == 2)
    return "std_time_duration_ns";
  if (i == 3)
    return "std_time_now_wall_ns";
  if (i == 4)
    return "std_time_format_timezone_smoke";
  if (i == 5)
    return "time_now_monotonic_ns_c";
  if (i == 6)
    return "time_sleep_ms_c";
  if (i == 7)
    return "time_duration_ns_c";
  if (i == 8)
    return "time_now_wall_ns_c";
  if (i == 9)
    return "time_format_timezone_smoke_c";
  return NULL;
}
int labi_fs_gen_runtime_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_runtime_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "runtime_crash_evidence_collect_c";
  if (i == 1)
    return "runtime_panic";
  if (i == 2)
    return "runtime_abort";
  return NULL;
}
int link_abi_generated_c_needs_fs(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_fs_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_fs_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_random(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_random_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_random_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_time(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_time_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_time_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_runtime(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_runtime_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_runtime_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* wave137: compress lib generated_c needs pure (cold twin). */
int labi_fs_gen_zlib_needle_count(void) {
  return 7;
}
const char *labi_fs_gen_zlib_needle_at(int i) {
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
  if (i == 4)
    return "compress2";
  if (i == 5)
    return "deflateInit";
  if (i == 6)
    return "inflateInit";
  return NULL;
}
int labi_fs_gen_zstd_needle_count(void) {
  return 5;
}
const char *labi_fs_gen_zstd_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "ZSTD_compress";
  if (i == 1)
    return "ZSTD_decompress";
  if (i == 2)
    return "ZSTD_create";
  if (i == 3)
    return "ZSTD_free";
  if (i == 4)
    return "ZSTD_isError";
  return NULL;
}
int labi_fs_gen_brotli_needle_count(void) {
  return 2;
}
const char *labi_fs_gen_brotli_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "BrotliEncoder";
  if (i == 1)
    return "BrotliDecoder";
  return NULL;
}
int link_abi_generated_c_needs_zlib(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_zlib_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_zlib_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_zstd(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_zstd_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_zstd_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_brotli(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_brotli_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_brotli_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* wave138: core.slice / std.db.kv / std.db.arrow generated_c needs pure (cold twin). */
int labi_fs_gen_core_slice_needle_count(void) {
  return 6;
}
const char *labi_fs_gen_core_slice_needle_at(int i) {
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
  return NULL;
}
int labi_fs_gen_db_kv_needle_count(void) {
  return 7;
}
const char *labi_fs_gen_db_kv_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "db_kv_open_c";
  if (i == 1)
    return "db_kv_put_c";
  if (i == 2)
    return "db_kv_get_c";
  if (i == 3)
    return "db_kv_append_ts_c";
  if (i == 4)
    return "db_kv_wal_flush_c";
  if (i == 5)
    return "db_kv_compact_c";
  if (i == 6)
    return "db_kv_sst_level_count_c";
  return NULL;
}
int labi_fs_gen_db_arrow_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_db_arrow_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "arrow_column_";
  if (i == 1)
    return "arrow_batch_";
  if (i == 2)
    return "arrow_smoke_c";
  return NULL;
}
int link_abi_generated_c_needs_core_slice(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_core_slice_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_core_slice_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_db_kv(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_db_kv_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_db_kv_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_db_arrow(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_db_arrow_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_db_arrow_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
/* wave139: co-emit provides_* pure (skip hard-link when TU already defines). */
int labi_fs_gen_provides_core_mem_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_provides_core_mem_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "void core_mem_mem_copy(";
  if (i == 1)
    return "int32_t core_mem_placeholder(void) {";
  if (i == 2)
    return "int32_t core_mem_align_of_i32(void) {";
  return NULL;
}
int labi_fs_gen_provides_std_heap_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_provides_std_heap_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "uint8_t * std_heap_libc_heap_alloc_c(size_t size) {";
  if (i == 1)
    return "void std_heap_libc_heap_free_c(uint8_t * ptr) {";
  if (i == 2)
    return "std_heap_libc_heap_alloc_c(size_t size) {";
  return NULL;
}
int link_abi_generated_c_provides_core_mem(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_provides_core_mem_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_provides_core_mem_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_provides_std_heap(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_provides_std_heap_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_provides_std_heap_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* wave141: Win32 / WSA generated_c needs pure (cold twin). */
int labi_fs_gen_win32_needle_count(void) {
  return 9;
}
const char *labi_fs_gen_win32_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "GetStdHandle";
  if (i == 1)
    return "WriteFile";
  if (i == 2)
    return "CreateFileA";
  if (i == 3)
    return "ReadFile";
  if (i == 4)
    return "CloseHandle";
  if (i == 5)
    return "ExitProcess";
  if (i == 6)
    return "win32_write";
  if (i == 7)
    return "win32_read_file_into";
  if (i == 8)
    return "win32_exit_process";
  return NULL;
}
int labi_fs_gen_win32_wsa_needle_count(void) {
  return 3;
}
const char *labi_fs_gen_win32_wsa_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "WSAStartup";
  if (i == 1)
    return "WSACleanup";
  if (i == 2)
    return "win32_net_available";
  return NULL;
}
int link_abi_generated_c_needs_win32(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_win32_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_win32_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}
int link_abi_generated_c_needs_win32_wsa(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_win32_wsa_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_win32_wsa_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* wave142: G-01 stub0 — never hard-link core/builtin or core/mem from C-path scan.
 * Pure orch lives in labi_freestanding_list.x under hybrid; cold twin here.
 * PLATFORM: SHARED
 */
int link_abi_generated_c_needs_core_builtin(const char *c_path) {
  (void)c_path;
  return 0;
}
int link_abi_generated_c_needs_core_mem(const char *c_path) {
  (void)c_path;
  return 0;
}

/* wave143: generated-C async scheduler needs pure (cold twin).
 * Nine substr needles ≡ historical mega xlang_generated_c_needs_async_scheduler.
 * Cap residual: link_abi_generated_c_contains_substr. PLATFORM: SHARED
 */
int labi_fs_gen_async_scheduler_needle_count(void) {
  return 9;
}
const char *labi_fs_gen_async_scheduler_needle_at(int i) {
  if (i < 0)
    return NULL;
  if (i == 0)
    return "xlang_async_run_i32";
  if (i == 1)
    return "xlang_async_cps_suspend";
  if (i == 2)
    return "xlang_async_task_submit";
  if (i == 3)
    return "xlang_async_run_seed_";
  if (i == 4)
    return "xlang_async_coop_pingpong_jmp";
  if (i == 5)
    return "xlang_async_coop_pingpong";
  if (i == 6)
    return "xlang_async_run_drain_until_idle";
  if (i == 7)
    return "xlang_async_queue_reset";
  if (i == 8)
    return "xlang_async_bind_context_c";
  return NULL;
}
int xlang_generated_c_needs_async_scheduler(const char *c_path) {
  int n, i;
  if (!c_path || !c_path[0])
    return 0;
  n = labi_fs_gen_async_scheduler_needle_count();
  for (i = 0; i < n; i++) {
    const char *needle = labi_fs_gen_async_scheduler_needle_at(i);
    if (needle && needle[0] && link_abi_generated_c_contains_substr(c_path, needle) != 0)
      return 1;
  }
  return 0;
}

/* wave144: freestanding user.o needs_io / needs_panic pure (cold twin).
 * Tables labi_fs_io_sym_* / labi_fs_panic_sym already pure above.
 * Cap residual: xlang_link_obj_needs_undef_sym. PLATFORM: SHARED
 */
int xlang_freestanding_user_o_needs_io(const char *user_o) {
  int n;
  int i;
  if (!user_o || !user_o[0])
    return 0;
  n = labi_fs_io_sym_count();
  for (i = 0; i < n; i++) {
    const char *s = labi_fs_io_sym_at(i);
    if (s && s[0] && xlang_link_obj_needs_undef_sym(user_o, s))
      return 1;
  }
  return 0;
}

int xlang_freestanding_user_o_needs_panic(const char *user_o) {
  const char *s;
  if (!user_o || !user_o[0])
    return 0;
  s = labi_fs_panic_sym();
  if (!s || !s[0])
    return 0;
  return xlang_link_obj_needs_undef_sym(user_o, s);
}

/* wave159: freestanding_enabled pure orch (cold twin ≡ .x).
 * Peer host_is_linux + pure env name; Cap residual link_abi_getenv (wave223 G.7).
 * PLATFORM: SHARED orch / LINUX consumers.
 */
int xlang_link_freestanding_enabled(int driver_freestanding) {
  char *e;
  if (xlang_host_is_linux() == 0)
    return 0;
  if (driver_freestanding != 0)
    return 1;
  e = (char *)link_abi_getenv(labi_fs_env_freestanding());
  if (e == NULL)
    return 0;
  if (e[0] == 0)
    return 0;
  if (e[0] == 48) /* '0' */
    return 0;
  return 1;
}

/* wave167: ensure_crt0_user_o pure orch (cold twin ≡ .x).
 * Peer freestanding_enabled + pure tables; Cap residual resolve/access/cc/stat.
 * Pure byte join (no snprintf). PLATFORM: SHARED orch / LINUX freestanding consumers.
 */
int xlang_ensure_crt0_user_o(const char *argv0, int driver_freestanding) {
  char comp[4096];
  char out_o[4096];
  char src_s[4096];
  const char *out_base = labi_fs_crt0_out_base();
  const char *src_rel = labi_fs_crt0_src_rel();
  const char *stem = labi_fs_ensure_stem(0);
  const char *leaf_o;
  const char *leaf_s;
  const char *o_path;
  const char *have;
  int dn, ln_o, ln_s, i, k, rc, crc;
  if (xlang_link_freestanding_enabled(driver_freestanding) == 0)
    return 0;
  o_path = xlang_crt0_user_o_path(argv0);
  have = asm_link_obj_skip_missing(o_path);
  if (have != NULL)
    return 0;
  rc = xlang_resolve_compiler_dir(argv0, comp, sizeof comp);
  if (rc != 0) {
    link_diag_runtime_obj_resolve_fail(out_base ? out_base : "crt0_user.o", NULL);
    return -1;
  }
  leaf_o = out_base ? out_base : "crt0_user.o";
  leaf_s = src_rel ? src_rel : "src/asm/crt0_user_x86_64.s";
  dn = 0;
  while (comp[dn] != 0)
    dn++;
  ln_o = 0;
  while (leaf_o[ln_o] != 0)
    ln_o++;
  if (dn + 1 + ln_o >= 4096)
    return -1;
  for (i = 0; i < dn; i++)
    out_o[i] = comp[i];
  out_o[dn] = '/';
  for (k = 0; k <= ln_o; k++)
    out_o[dn + 1 + k] = leaf_o[k];
  ln_s = 0;
  while (leaf_s[ln_s] != 0)
    ln_s++;
  if (dn + 1 + ln_s >= 4096)
    return -1;
  for (i = 0; i < dn; i++)
    src_s[i] = comp[i];
  src_s[dn] = '/';
  for (k = 0; k <= ln_s; k++)
    src_s[dn + 1 + k] = leaf_s[k];
  if (link_abi_path_readable(src_s) == 0) {
    link_diag_runtime_source_missing(stem ? stem : "crt0_user", src_s);
    return -1;
  }
  crc = xlang_cc_compile_sync(src_s, out_o, NULL, NULL, NULL, 1);
  if (crc != 0) {
    link_diag_runtime_obj_build_status(leaf_o, crc);
    return -1;
  }
  o_path = xlang_crt0_user_o_path(argv0);
  have = asm_link_obj_skip_missing(o_path);
  if (have == NULL) {
    link_diag_runtime_obj_missing(leaf_o, out_o);
    return -1;
  }
  return 0;
}

/* wave168: ensure_freestanding_io_o pure orch (cold twin ≡ .x).
 * Peer freestanding_enabled + pure io tables; Cap residual resolve/access/cc/stat.
 * Pure byte join (no snprintf). PLATFORM: SHARED orch / LINUX freestanding consumers.
 */
int xlang_ensure_freestanding_io_o(const char *argv0, int driver_freestanding) {
  char comp[4096];
  char out_o[4096];
  char src_s[4096];
  const char *out_base = labi_fs_io_out_base();
  const char *src_rel = labi_fs_io_src_rel();
  const char *stem = labi_fs_ensure_stem(1);
  const char *leaf_o;
  const char *leaf_s;
  const char *o_path;
  const char *have;
  int dn, ln_o, ln_s, i, k, rc, crc;
  if (xlang_link_freestanding_enabled(driver_freestanding) == 0)
    return 0;
  o_path = xlang_freestanding_io_o_path(argv0);
  have = asm_link_obj_skip_missing(o_path);
  if (have != NULL)
    return 0;
  rc = xlang_resolve_compiler_dir(argv0, comp, sizeof comp);
  if (rc != 0) {
    link_diag_runtime_obj_resolve_fail(out_base ? out_base : "freestanding_io.o", NULL);
    return -1;
  }
  leaf_o = out_base ? out_base : "freestanding_io.o";
  leaf_s = src_rel ? src_rel : "src/asm/freestanding_io_x86_64.s";
  dn = 0;
  while (comp[dn] != 0)
    dn++;
  ln_o = 0;
  while (leaf_o[ln_o] != 0)
    ln_o++;
  if (dn + 1 + ln_o >= 4096)
    return -1;
  for (i = 0; i < dn; i++)
    out_o[i] = comp[i];
  out_o[dn] = '/';
  for (k = 0; k <= ln_o; k++)
    out_o[dn + 1 + k] = leaf_o[k];
  ln_s = 0;
  while (leaf_s[ln_s] != 0)
    ln_s++;
  if (dn + 1 + ln_s >= 4096)
    return -1;
  for (i = 0; i < dn; i++)
    src_s[i] = comp[i];
  src_s[dn] = '/';
  for (k = 0; k <= ln_s; k++)
    src_s[dn + 1 + k] = leaf_s[k];
  if (link_abi_path_readable(src_s) == 0) {
    link_diag_runtime_source_missing(stem ? stem : "freestanding_io", src_s);
    return -1;
  }
  crc = xlang_cc_compile_sync(src_s, out_o, NULL, NULL, NULL, 1);
  if (crc != 0) {
    link_diag_runtime_obj_build_status(leaf_o, crc);
    return -1;
  }
  o_path = xlang_freestanding_io_o_path(argv0);
  have = asm_link_obj_skip_missing(o_path);
  if (have == NULL) {
    link_diag_runtime_obj_missing(leaf_o, out_o);
    return -1;
  }
  return 0;
}


#else
const char *labi_fs_env_freestanding(void);
int labi_fs_io_sym_count(void);
const char *labi_fs_io_sym_at(int i);
const char *labi_fs_panic_sym(void);
int labi_fs_ensure_catalog_count(void);
int labi_fs_ensure_catalog_step_at(int i, const char **stem_out, const char **out_base_out,
                                   const char **src_rel_out);
const char *labi_fs_ensure_out_base(int i);
const char *labi_fs_ensure_src_rel(int i);
const char *labi_fs_ensure_stem(int i);
const char *labi_fs_crt0_out_base(void);
const char *labi_fs_crt0_src_rel(void);
const char *labi_fs_io_out_base(void);
const char *labi_fs_io_src_rel(void);
int labi_fs_heap_c_needle_count(void);
const char *labi_fs_heap_c_needle_at(int i);
int labi_fs_heap_o_sym_count(void);
const char *labi_fs_heap_o_sym_at(int i);
int labi_fs_memcpy_face_sym_count(void);
const char *labi_fs_memcpy_face_sym_at(int i);
int link_abi_generated_c_needs_libc_heap(const char *c_path);
int link_abi_user_o_needs_libc_heap(const char *user_o);
int link_abi_user_o_needs_freestanding_nostdlib_face(const char *user_o);
/* wave136: C-path PRIMARY OS/fs generated_c needs pure (L7). */
int labi_fs_gen_fs_needle_count(void);
const char *labi_fs_gen_fs_needle_at(int i);
int labi_fs_gen_random_needle_count(void);
const char *labi_fs_gen_random_needle_at(int i);
int labi_fs_gen_time_needle_count(void);
const char *labi_fs_gen_time_needle_at(int i);
int labi_fs_gen_runtime_needle_count(void);
const char *labi_fs_gen_runtime_needle_at(int i);
int link_abi_generated_c_needs_fs(const char *c_path);
int link_abi_generated_c_needs_random(const char *c_path);
int link_abi_generated_c_needs_time(const char *c_path);
int link_abi_generated_c_needs_runtime(const char *c_path);
/* wave137: compress lib generated_c needs pure (L7). */
int labi_fs_gen_zlib_needle_count(void);
const char *labi_fs_gen_zlib_needle_at(int i);
int labi_fs_gen_zstd_needle_count(void);
const char *labi_fs_gen_zstd_needle_at(int i);
int labi_fs_gen_brotli_needle_count(void);
const char *labi_fs_gen_brotli_needle_at(int i);
int link_abi_generated_c_needs_zlib(const char *c_path);
int link_abi_generated_c_needs_zstd(const char *c_path);
int link_abi_generated_c_needs_brotli(const char *c_path);
/* wave138: core.slice / std.db.kv / std.db.arrow generated_c needs pure (L7). */
int labi_fs_gen_core_slice_needle_count(void);
const char *labi_fs_gen_core_slice_needle_at(int i);
int labi_fs_gen_db_kv_needle_count(void);
const char *labi_fs_gen_db_kv_needle_at(int i);
int labi_fs_gen_db_arrow_needle_count(void);
const char *labi_fs_gen_db_arrow_needle_at(int i);
int link_abi_generated_c_needs_core_slice(const char *c_path);
int link_abi_generated_c_needs_db_kv(const char *c_path);
int link_abi_generated_c_needs_db_arrow(const char *c_path);
/* wave139: co-emit provides_* pure (L7). */
int labi_fs_gen_provides_core_mem_needle_count(void);
const char *labi_fs_gen_provides_core_mem_needle_at(int i);
int labi_fs_gen_provides_std_heap_needle_count(void);
const char *labi_fs_gen_provides_std_heap_needle_at(int i);
int link_abi_generated_c_provides_core_mem(const char *c_path);
int link_abi_generated_c_provides_std_heap(const char *c_path);
/* wave141: Win32 / WSA generated_c needs pure (L7). */
int labi_fs_gen_win32_needle_count(void);
const char *labi_fs_gen_win32_needle_at(int i);
int labi_fs_gen_win32_wsa_needle_count(void);
const char *labi_fs_gen_win32_wsa_needle_at(int i);
int link_abi_generated_c_needs_win32(const char *c_path);
int link_abi_generated_c_needs_win32_wsa(const char *c_path);
/* wave142: core_builtin / core_mem stub0 pure (L7). */
int link_abi_generated_c_needs_core_builtin(const char *c_path);
int link_abi_generated_c_needs_core_mem(const char *c_path);
/* wave143: async scheduler generated_c needs pure (L7). */
int labi_fs_gen_async_scheduler_needle_count(void);
const char *labi_fs_gen_async_scheduler_needle_at(int i);
int xlang_generated_c_needs_async_scheduler(const char *c_path);
/* wave144: freestanding user.o needs_io / needs_panic pure (L7). */
int xlang_freestanding_user_o_needs_io(const char *user_o);
int xlang_freestanding_user_o_needs_panic(const char *user_o);
/* wave159: freestanding_enabled pure orch (L7). */
int xlang_link_freestanding_enabled(int driver_freestanding);
/* wave167: ensure_crt0_user_o pure orch (L7). */
int xlang_ensure_crt0_user_o(const char *argv0, int driver_freestanding);
/* wave168: ensure_freestanding_io_o pure orch (L7). */
int xlang_ensure_freestanding_io_o(const char *argv0, int driver_freestanding);
/* wave175: contains_substr pure orch (L7). */
int link_abi_generated_c_contains_substr(const char *c_path, const char *needle);
/* wave176: contains_substr_use_line pure orch (L7). */
int link_abi_generated_c_contains_substr_use_line(const char *c_path, const char *needle);
/* wave177: any_substr_use_line pure orch (L7). */
int link_abi_generated_c_contains_any_substr_use_line(const char *c_path, const char **needles,
                                                     int n_needles);
/* wave178: any_substr pure orch (L7). */
int link_abi_generated_c_contains_any_substr(const char *c_path, const char **needles,
                                            int n_needles);
#endif

int labi_freestanding_list_slice_marker(void) {
  return 1;
}