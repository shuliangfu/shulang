/* seeds/runtime_pipeline_abi_surface.from_x.c
 * G-02f runtime_pipeline_abi R2 full surface - isomorphic with src/runtime_pipeline_abi.x
 * Product PREFER_X_O: xlang_asm -E(.x) -> thin.o + ld -r with rest (seeds/runtime_pipeline_abi.from_x.c)
 * Prove: full.x vs this surface -> nm IDENTICAL (237 #[no_mangle] · 270 nm T)
 * Mode: full DIRECT compute (pipeline import/load/sync/parse/typeck orch + module import storage)
 * Cap residual: extern bridges (parser_*, asm_*, pipeline_*, typeck_*, cfg_eval_*, driver_*, xlang_*)
 * No doc_anchor.
 * Regen: xlang_asm -E src/runtime_pipeline_abi.x | filter DBG + polish prologue
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/uio.h>
#include <poll.h>
#include <dirent.h>
#endif
extern void parser_parse_into_init(uint8_t * module, uint8_t * arena);
extern void xlang_module_collect_imports_from_buf(uint8_t * module, uint8_t * data, int64_t len);
extern int32_t parser_get_module_num_imports(uint8_t * module);
extern void parser_get_module_import_path(uint8_t * module, int32_t idx, uint8_t * path_buf);
extern int32_t parser_copy_module_import_path64(uint8_t * module, int32_t i, uint8_t * out);
extern void asm_skip_heavy_set_pipeline_ctx(uint8_t * ctx);
extern void pipeline_fill_array_lit_types_for_skipped_typeck(uint8_t * m, uint8_t * a);
extern void pipeline_fill_soa_field_access_for_asm_emit(uint8_t * m, uint8_t * a);
extern void pipeline_module_fixup_with_arena_stmt_orders(uint8_t * m, uint8_t * a);
extern int32_t xlang_asm_codegen_elf_o_product_emit(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf);
extern int32_t pipeline_parse_set_main_from_buf_c(uint8_t * m, uint8_t * a, uint8_t * d, int32_t len);
extern void pipeline_diag_emitted_reset(void);
extern void pipeline_diag_emitted_note(void);
extern int32_t pipeline_diag_emitted_get(void);
extern int32_t get_ndep(void);
extern void pipeline_set_ndep(int32_t n);
extern int32_t driver_dep_seeded_get(int32_t i);
extern void driver_dep_seeded_set(int32_t i, int32_t v);
extern int32_t typeck_driver_dep_seeded_get(int32_t i);
extern uint8_t * get_dep_module(int32_t i);
extern uint8_t * get_dep_arena(int32_t i);
extern uint8_t * typeck_get_dep_module(int32_t i);
extern uint8_t * typeck_get_dep_arena(int32_t i);
extern void pipeline_set_dep(int32_t i, uint8_t * mod, uint8_t * arena);
extern void driver_dep_publish_slot(int32_t i, uint8_t * arena, uint8_t * module, uint8_t * import_path);
extern uint8_t * typeck_driver_dep_module_buf(int32_t i);
extern uint8_t * typeck_driver_dep_arena_buf(int32_t i);
extern int32_t xlang_cstr_ends_with_dot_x(uint8_t * s);
extern int32_t xlang_asm_out_buf_is_object_magic(uint8_t * data);
extern int32_t xlang_import_path_is_file_path(uint8_t * import_path);
extern int32_t xlang_asm_user_std_dep_skip_x_typeck(uint8_t * dep_path);
extern int32_t xlang_asm_user_std_net_dep_path(uint8_t * dep_path);
extern int32_t xlang_asm_user_std_io_driver_dep_path(uint8_t * dep_path);
extern int32_t xlang_asm_user_dep_parse_skip_typeck_path(uint8_t * dep_path);
extern int32_t xlang_asm_out_buf_is_object(uint8_t * data, int64_t len);
extern uint8_t * xlang_dep_prerun_entry_dir(uint8_t * main_entry_dir, uint8_t * lib_roots, int32_t n_lib_roots);
extern int32_t xlang_find_loaded_import_index(uint8_t * import_path, uint8_t * all_paths, int32_t n_all);
extern int32_t xlang_merge_deps_path_already_out(uint8_t * path, uint8_t * out_paths, int32_t n_out);
extern void xlang_fputs_stdout(uint8_t * s);
extern void xlang_emit_pipeline_glue_include(void);
extern int32_t xlang_import_dep_dir_from_path(uint8_t * path, uint8_t * dep_dir, int64_t dep_dir_size);
extern void pipeline_debug_trace_body_x_mega_pre_reset(uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_body_x_mega_post_reset(uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_body_x_mega_post_params(uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_body_x_mega_post_frame(uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_body_x_mega_post_locals(uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_body_x_mega_pre_emit(uint8_t * module, uint8_t * arena);
extern void driver_typeck_dep_sidecar_clear(void);
extern void driver_dep_seeded_clear_slots(void);
extern void driver_dep_seeded_clear_all(void);
extern void xlang_get_entry_dir(uint8_t * input_path, uint8_t * entry_dir, int64_t size);
extern int32_t driver_asm_fp_is_stdout(uint8_t * fp);
extern void driver_asm_fclose_file(uint8_t * fp);
extern void driver_asm_fclose_asm_out(uint8_t * fp);
extern void xlang_import_path_to_file_path(uint8_t * lib_root, uint8_t * import_path, uint8_t * path, int64_t path_size);
extern void pipe_cstr_join_slash(uint8_t * dst, int32_t cap, uint8_t * a, uint8_t * b);
extern void xlang_path_try_realpath_inplace(uint8_t * path, int64_t path_size);
extern void xlang_resolve_file_import_path(uint8_t * entry_dir, uint8_t * import_path, uint8_t * path, int64_t path_size);
extern int32_t driver_dep_slot_for_path_scan(uint8_t * path);
extern int32_t driver_dep_slot_for_path(uint8_t * path);
extern int32_t xlang_preprocess_raw_to_malloc_impl(uint8_t * raw, int64_t raw_len, uint8_t * out_src, uint8_t * out_src_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines, int32_t emit_diag);
extern int32_t xlang_preprocess_raw_to_malloc(uint8_t * raw, int64_t raw_len, uint8_t * out_src, uint8_t * out_src_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines);
extern uint8_t * xlang_preprocess_with_path(uint8_t * source, size_t source_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines, uint8_t * out_length);
extern uint8_t * xlang_preprocess_quiet(uint8_t * source, size_t source_len, uint8_t * defines, int32_t ndefines, uint8_t * out_length);
extern uint8_t * xlang_preprocess(uint8_t * source, size_t source_len, uint8_t * defines, int32_t ndefines, uint8_t * out_length);
extern void driver_dep_seed_slots(uint8_t * arenas, uint8_t * modules, int32_t n);
extern int32_t pipe_cstr_contains(uint8_t * hay, uint8_t * needle);
extern uint8_t * xlang_entry_lib_name_from_path(uint8_t * input_path);
extern uint8_t * pipeline_get_dep_arena_slot(int32_t i);
extern uint8_t * pipeline_get_dep_module_slot(int32_t i);
extern void pipe_cstr_copy(uint8_t * dst, int32_t cap, uint8_t * src);
extern void pipeline_diag_import_open_fail_once(uint8_t * import_path, uint8_t * resolved_path);
extern void pipeline_resolve_path_into_static(uint8_t * path_c);
extern int32_t pipeline_resolve_path(uint8_t * path_ptr, int32_t path_len);
extern int32_t pipeline_read_file_stage_prep(void);
extern int32_t pipeline_read_file_commit_prep(void);
extern int32_t pipeline_read_file(void);
extern int32_t pipeline_parse_into_bytes(uint8_t * arena, uint8_t * module, uint8_t * data, int64_t len);
extern int32_t pipeline_parse_into_loaded_import(uint8_t * arena, uint8_t * module);
extern int32_t xlang_pipeline_run_x_pipeline_large_stack(uint8_t * module, uint8_t * arena, uint8_t * source_data, int64_t source_len, uint8_t * out_buf, uint8_t * ctx);
extern int32_t xlang_pipeline_dep_prerun_parse_skip_typeck_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx);
extern int32_t xlang_pipeline_dep_prerun_parse_skip_typeck(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx);
extern int32_t xlang_pipeline_dep_prerun_parse_only_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len);
extern int32_t xlang_pipeline_dep_prerun_parse_only(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len);
extern int32_t xlang_pipeline_dep_prerun_typeck_only_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx);
extern int32_t pipeline_typeck_dep_prerun_module_c(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern int32_t pipeline_typeck_validate_struct_layouts_zero_padding_c(uint8_t * module, uint8_t * arena);
extern void pipeline_typeck_patch_all_body_parent_links_c(uint8_t * module, uint8_t * arena);
extern void pipeline_bind_import_dep_buffers(uint8_t * ctx, int32_t import_idx);
extern int32_t pipeline_sync_one_dep_slot(uint8_t * module, uint8_t * ctx, int32_t dep_i);
extern int32_t pipeline_sync_dep_slots_from_driver_c(uint8_t * module, uint8_t * ctx);
extern int32_t pipeline_load_import_from_disk_c(uint8_t * module, uint8_t * arena, uint8_t * ctx, int32_t import_idx);
extern int32_t pipeline_try_bind_seeded_import(uint8_t * ctx, int32_t import_idx, int32_t global_slot);
extern void pipeline_dep_ctx_realign_ndep_for_entry_c(uint8_t * module, uint8_t * ctx);
extern int32_t pipeline_load_and_sync_direct_import_deps_c(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern int32_t xlang_pipeline_dep_prerun_typeck_only(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx);
extern int32_t xlang_pipeline_dep_prerun_for_asm_module_o(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx);
extern int32_t pipe_path_readable(uint8_t * path);
extern int32_t pipe_cstr_has_char(uint8_t * s, uint8_t ch);
extern void pipe_write_nested_name_x(uint8_t * dst, int32_t cap, uint8_t * root, uint8_t * name);
extern int32_t pipe_write_root_dotted_imp(uint8_t * dst, int32_t cap, uint8_t * root, uint8_t * imp);
extern void pipe_append_suffix(uint8_t * dst, int32_t cap, int32_t off, uint8_t * suf);
extern uint8_t * xlang_cstr_offset(uint8_t * s, int32_t off);
extern uint8_t * pipe_dir_tail(uint8_t * entry_dir);
extern uint8_t * pipe_strip_prefix_seg(uint8_t * import_path, uint8_t * dir_tail);
extern void xlang_resolve_import_file_path_multi(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_path, uint8_t * path, int64_t path_size);
extern int32_t pipe_pctx_off_entry_dir_buf(void);
extern int32_t pipe_pctx_off_entry_dir_len(void);
extern int32_t pipe_pctx_off_num_lib_roots(void);
extern int32_t pipe_pctx_off_loaded_len(void);
extern int32_t pipe_pctx_off_preprocess_len(void);
extern void pipe_store_i32_le(uint8_t * base, int32_t off, int32_t v);
extern int32_t pipe_load_i32_le(uint8_t * base, int32_t off);
extern void pipe_store_i64_zero(uint8_t * base, int32_t off);
extern void pipeline_dep_ctx_path_bufs_reset(uint8_t * ctx);
extern int32_t pipeline_resolve_path_x(uint8_t * ctx, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_read_file_x(uint8_t * ctx);
extern int32_t pipeline_preprocess_loaded_into_ctx(uint8_t * ctx);
extern int32_t pipeline_parse_into_buf(uint8_t * arena, uint8_t * module, uint8_t * buf, int32_t buf_len);
extern void pipeline_dep_ctx_copy_entry_dir(uint8_t * ctx, uint8_t * entry_dir);
extern void pipeline_dep_ctx_set_use_asm_backend(uint8_t * ctx, int32_t v);
extern void pipeline_typeck_diag_soft_suppress_set(int32_t v);
extern int32_t pipeline_typeck_diag_soft_suppress_get(void);
extern void pipeline_typeck_set_dep_ctx(uint8_t * ctx);
extern uint8_t * pipeline_typeck_get_dep_ctx(void);
extern void preprocess_define_reset(void);
extern void preprocess_define_add(uint8_t * name);
extern int32_t preprocess_define_has(uint8_t * sym, int32_t sym_len);
extern int32_t preprocess_eval_condition_c(uint8_t * cond, int32_t cond_len);
extern void preprocess_if_stack_reset(void);
extern int32_t preprocess_if_stack_len(void);
extern int32_t preprocess_if_stack_push(int32_t v);
extern void preprocess_if_stack_pop(void);
extern int32_t preprocess_if_stack_at(int32_t i);
extern void preprocess_if_stack_set_at(int32_t i, int32_t v);
extern int32_t * typeck_ndep_slot(void);
extern void typeck_ndep_store_impl(int32_t n);
extern uint8_t * typeck_dep_module_get(int32_t i);
extern uint8_t * typeck_dep_arena_get(int32_t i);
extern void typeck_dep_module_set_impl(int32_t i, uint8_t * mod);
extern void typeck_dep_arena_set_impl(int32_t i, uint8_t * arena);
extern uint8_t * typeck_dep_module_ptrs_base(void);
extern uint8_t * xlang_cstr_typeck_lit(void);
extern uint8_t * xlang_entry_lib_keyword_lit(int32_t k);
extern uint8_t * xlang_entry_lib_name_from_path_impl(uint8_t * input_path);
extern int32_t * pipeline_diag_emitted_flag_slot(void);
extern int32_t * driver_dep_seeded_slot(int32_t i);
extern void driver_dep_arena_ptr_set_impl(int32_t i, uint8_t * arena);
extern void driver_dep_module_ptr_set_impl(int32_t i, uint8_t * module);
extern void driver_dep_path_registry_set(int32_t i, uint8_t * path);
extern uint8_t * driver_dep_path_registry_at(int32_t i);
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_module(void);
extern uint8_t * driver_dep_arena_buf(int32_t i);
extern uint8_t * driver_dep_module_buf(int32_t i);
extern void pipeline_rf_stage_prep_clear(void);
extern void pipeline_rf_stage_prep_set(uint8_t * prep, int64_t prep_len);
extern int32_t pipeline_rf_stage_prep_take(uint8_t * out_prep, uint8_t * out_len);
extern int32_t pipeline_loaded_import_commit_from_owned(uint8_t * prep, int64_t prep_len);
extern uint8_t * pipeline_loaded_import_data(void);
extern int64_t pipeline_loaded_import_len_get(void);
extern uint8_t * pipeline_resolved_path_buf_slot(void);
extern void pipeline_dep_arena_slot_set(int32_t i, uint8_t * p);
extern void pipeline_dep_module_slot_set(int32_t i, uint8_t * p);
extern uint8_t * pipeline_dep_arena_slot_at(int32_t i);
extern uint8_t * pipeline_dep_module_slot_at(int32_t i);
extern void pipeline_entry_dir_copy(uint8_t * path);
extern void pipeline_entry_dir_set_dot(void);
extern uint8_t * pipeline_entry_dir_get(void);
extern void pipeline_set_entry_dir(uint8_t * path);
extern void pipeline_set_dep_slots(uint8_t * arenas, uint8_t * modules);
extern void xlang_pipeline_fill_ctx_path_buffers(uint8_t * ctx, uint8_t * entry_dir, uint8_t * lib_roots, int32_t n_lib_roots);
extern int32_t pipe_cstr_len(uint8_t * s);
extern void xlang_pipeline_pctx_seed_dep_slots(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ar, uint8_t * import_paths, int32_t n);
extern void xlang_pipeline_pctx_seed_dep_import_paths_only(uint8_t * ctx, uint8_t * import_paths, int32_t n);
extern void xlang_pipeline_one_ctx_for_dep_prerun_map_impl(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * dep_paths, int32_t ndep, uint8_t * dep_src, int64_t dep_src_len);
extern void xlang_pipeline_one_ctx_for_dep_prerun(uint8_t * ctx, int32_t j, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * dep_paths, int32_t ndep, uint8_t * dep_src, int64_t dep_src_len);
extern void xlang_driver_asm_prepare_entry_elf_emit(uint8_t * module, uint8_t * arena, uint8_t * pctx);
extern int32_t xlang_asm_codegen_elf_o_large_stack(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf);
extern void xlang_load_direct_fail_cleanup(uint8_t * dep_sources, uint8_t * dep_paths, int32_t mi);
extern int32_t xlang_load_one_direct_resolve_read_preprocess(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_key, uint8_t * defines, int32_t ndefines, uint8_t * out_prep, uint8_t * out_prep_len);
extern int32_t xlang_load_one_direct_import_at(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_key, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t mi);
extern int32_t xlang_load_direct_imports_for_asm_layout(uint8_t * module, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * out_n);
extern int32_t xlang_merge_direct_then_transitive_dep_paths(uint8_t * module, int32_t n_imports, uint8_t * cpaths, int32_t n_closure, uint8_t * out_paths, int32_t * out_n);
extern int32_t xlang_merge_direct_then_transitive_deps(uint8_t * module, int32_t n_imports, uint8_t * cls, uint8_t * clens, uint8_t * cpaths, int32_t n_closure, uint8_t * out_src, uint8_t * out_lens, uint8_t * out_paths, int32_t * out_n);
extern int32_t xlang_collect_deps_transitive(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n_deps);
extern int32_t xlang_collect_dep_paths_transitive(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n_deps);
extern int32_t pipe_diag_msg_append_cstr(uint8_t * dst, int32_t cap, int32_t at, uint8_t * src);
extern int32_t pipe_diag_msg_append_i32(uint8_t * dst, int32_t cap, int32_t at, int32_t val);
extern int32_t pipe_diag_msg_append_name(uint8_t * dst, int32_t cap, int32_t at, uint8_t * name, int32_t name_len);
extern void pipeline_debug_trace_named_func_bodies_impl(uint8_t * phase, uint8_t * module, uint8_t * arena);
extern void pipeline_debug_trace_named_func_bodies(uint8_t * phase, uint8_t * module, uint8_t * arena);
extern int32_t typeck_module_entry_only(uint8_t * module);
extern int32_t typeck_module_with_sidecar(uint8_t * module);
extern int32_t pipeline_typeck_module_for_ctx_impl(uint8_t * module, uint8_t * arena, uint8_t * ctx_void);
extern int32_t pipeline_typeck_module_for_ctx(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern void xlang_lsp_ptr_slot_clear(uint8_t * arr, int32_t i);
extern void xlang_lsp_free_loaded_imports(uint8_t * all_dep_mods, uint8_t * all_dep_paths, int32_t n_all);
extern void pipeline_diag_preprocess_unclosed_if(uint8_t * path_diag);
extern void pipeline_diag_preprocess_fail(uint8_t * path_diag);
extern void pipeline_diag_import_preprocess_fail(uint8_t * import_path, uint8_t * resolved_path);
extern void pipeline_diag_preprocess_alloc_fail(uint8_t * path_diag, uint8_t * what);
extern void pipeline_diag_merge_dep_missing(uint8_t * import_path);
extern void typeck_ndep_store(int32_t n);
extern void typeck_dep_module_set(int32_t i, uint8_t * mod);
extern void typeck_dep_arena_set(int32_t i, uint8_t * arena);
extern void driver_dep_arena_ptr_set(int32_t i, uint8_t * arena);
extern void driver_dep_module_ptr_set(int32_t i, uint8_t * module);
extern int32_t pipe_cstr_eq(uint8_t * a, uint8_t * b);
extern uint8_t * pipe_load_ptr_slot(uint8_t * base, int32_t i);
extern void pipe_store_ptr_slot(uint8_t * base, int32_t i, uint8_t * val);
extern int64_t xlang_size_slot_get(uint8_t * arr, int32_t i);
extern void xlang_size_slot_set(uint8_t * arr, int32_t i, int64_t v);
extern void xlang_ptr_slot_set(uint8_t * arr, int32_t i, uint8_t * p);
extern uint8_t * xlang_ptr_slot_get(uint8_t * arr, int32_t i);
extern void xlang_i32_store(int32_t * p, int32_t v);
extern int32_t xlang_module_num_imports(uint8_t * module);
extern void xlang_module_import_path_cstr(uint8_t * module, int32_t idx, uint8_t * buf, int32_t cap);
extern int32_t xlang_collect_to_load_has(uint8_t * to_load, int32_t to_load_n, uint8_t * path);
extern uint8_t * xlang_collect_strdup(uint8_t * s);
extern int32_t xlang_collect_seed_to_load(uint8_t * module, uint8_t * to_load, int32_t * to_load_n);
extern void xlang_collect_tmp_parse_and_enqueue(uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz, uint8_t * prep, int64_t prep_len, uint8_t * debug_path, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded);
extern int32_t xlang_collect_paths_tmp_resolve_parse_enqueue(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded);
extern int32_t xlang_collect_deps_process_one(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n, uint8_t * to_load, int32_t * to_load_n, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz);
extern int32_t xlang_collect_paths_process_one(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n, uint8_t * to_load, int32_t * to_load_n, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz);
extern int32_t xlang_collect_deps_transitive_impl(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n_deps);
extern int32_t xlang_collect_dep_paths_transitive_impl(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n_deps);
extern void xlang_collect_enqueue_module_imports(uint8_t * tmp_module, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded);
extern void pipeline_diag_preprocess_directive_code(uint8_t * path_diag, int32_t code);
extern uint8_t * xlang_dep_prerun_entry_dir_pick(uint8_t * main_entry_dir, uint8_t * lib_roots, int32_t n_lib_roots);
extern int32_t xlang_find_loaded_import_index_scan(uint8_t * path, uint8_t * all_paths, int32_t n_all);
extern int32_t xlang_merge_deps_path_already_out_scan(uint8_t * path, uint8_t * out_paths, int32_t n_out);
extern void xlang_pipeline_pctx_update_dep_slots_no_reset(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * import_paths, int32_t n);
extern uint8_t * pipeline_run_x_thread_fn_impl(uint8_t * arg);
extern uint8_t * pipeline_run_x_thread_fn(uint8_t * arg);
extern uint8_t * pipeline_run_x_thread_fn_ptr(void);
extern int32_t xlang_pipeline_run_x_pipeline_large_stack_impl(uint8_t * module, uint8_t * arena, uint8_t * source_data, int64_t source_len, uint8_t * out_buf, uint8_t * ctx);
extern uint8_t * xlang_asm_codegen_elf_o_thread_fn(uint8_t * arg);
extern uint8_t * xlang_asm_codegen_elf_o_thread_fn_ptr(void);
extern uint8_t * xlang_asm_codegen_elf_o_thread_fn_impl(uint8_t * arg);
extern int32_t xlang_asm_codegen_elf_o_large_stack_impl(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf);
extern int32_t pipeline_asm_debug_enabled(void);
extern int32_t pipeline_debug_body_func_match(uint8_t * filter, uint8_t * name);
extern int32_t pipe_imp_entry_size(void);
extern int32_t pipe_imp_off_num_imports(void);
extern void pipe_imp_set_header_n(uint8_t * module, int32_t n);
extern int32_t pipe_imp_get_header_n(uint8_t * module);
extern int32_t pipe_imp_find_slot(uint8_t * module);
extern void pipe_imp_soft_sync(uint8_t * module);
extern int32_t pipe_imp_find_or_create(uint8_t * module);
extern int32_t pipe_imp_ensure_entries(int32_t slot, int32_t need);
extern int32_t pipe_imp_ensure_select(int32_t slot, int32_t need);
extern uint8_t * pipe_imp_entry_at(int32_t slot, int32_t idx);
extern int32_t pipe_imp_entry_off(int32_t idx);
extern void pipeline_module_import_storage_release(uint8_t * module);
extern int32_t pipeline_module_import_alloc(uint8_t * module);
extern void pipeline_module_import_set_path(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_path_len(uint8_t * module, int32_t idx);
extern void pipeline_module_import_path_copy(uint8_t * module, int32_t idx, uint8_t * dst, int32_t dst_cap);
extern uint8_t pipeline_module_import_path_byte_at(uint8_t * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_kind(uint8_t * module, int32_t idx, int32_t kind);
extern int32_t pipeline_module_import_kind_at(uint8_t * module, int32_t idx);
extern void pipeline_module_import_set_binding_name(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_binding_name_len(uint8_t * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(uint8_t * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_select_count(uint8_t * module, int32_t idx, int32_t n);
extern int32_t pipeline_module_import_append_select_name(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_count_at(uint8_t * module, int32_t idx);
extern void pipeline_module_import_set_select_name(uint8_t * module, int32_t idx, int32_t sel, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_name_len(uint8_t * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(uint8_t * module, int32_t idx, int32_t sel, int32_t off);
#undef g_import_open_valid
static int32_t g_import_open_valid = 0;
#undef g_import_open_import
static uint8_t g_import_open_import[65];
#undef g_import_open_resolved
static uint8_t g_import_open_resolved[512];
#undef g_pipe_entry_dir_buf
static uint8_t g_pipe_entry_dir_buf[512];
#undef g_pipe_entry_dir_dot
static uint8_t g_pipe_entry_dir_dot[2];
#undef g_pipe_entry_dir_is_dot
static int32_t g_pipe_entry_dir_is_dot = 1;
#undef g_pipe_resolved_path_buf
static uint8_t g_pipe_resolved_path_buf[512];
#undef g_pipe_dep_arena_slots
static uint8_t g_pipe_dep_arena_slots[256];
#undef g_pipe_dep_module_slots
static uint8_t g_pipe_dep_module_slots[256];
#undef g_pipe_rf_stage_prep
static uint8_t g_pipe_rf_stage_prep[8];
#undef g_pipe_rf_stage_prep_len
static uint8_t g_pipe_rf_stage_prep_len[8];
#undef g_pipe_loaded_import_buf
static uint8_t g_pipe_loaded_import_buf[8];
#undef g_pipe_loaded_import_len
static uint8_t g_pipe_loaded_import_len[8];
#undef g_pipe_loaded_import_cap
static uint8_t g_pipe_loaded_import_cap[8];
#undef g_pipe_diag_emitted_flag
static int32_t g_pipe_diag_emitted_flag = 0;
#undef g_pipe_driver_dep_arena
static uint8_t g_pipe_driver_dep_arena[256];
#undef g_pipe_driver_dep_module
static uint8_t g_pipe_driver_dep_module[256];
#undef g_pipe_driver_dep_path_registry
static uint8_t g_pipe_driver_dep_path_registry[256];
#undef g_pipe_driver_dep_seeded
static int32_t g_pipe_driver_dep_seeded[32];
#undef g_pipe_typeck_ndep
static int32_t g_pipe_typeck_ndep = 0;
#undef g_pipe_typeck_dep_module_ptrs
static uint8_t g_pipe_typeck_dep_module_ptrs[256];
#undef g_pipe_typeck_dep_arena_ptrs
static uint8_t g_pipe_typeck_dep_arena_ptrs[256];
#undef g_pipe_pp_defines
static uint8_t g_pipe_pp_defines[8192];
#undef g_pipe_pp_ndefines
static int32_t g_pipe_pp_ndefines = 0;
#undef g_pipe_pp_if_stack
static int32_t g_pipe_pp_if_stack[32];
#undef g_pipe_pp_if_n
static int32_t g_pipe_pp_if_n = 0;
#undef g_pipe_typeck_diag_soft_suppress
static int32_t g_pipe_typeck_diag_soft_suppress = 0;
#undef g_pipe_typeck_dep_ctx
static uint8_t g_pipe_typeck_dep_ctx[8];
#undef g_pipe_cstr_typeck_lit
static uint8_t g_pipe_cstr_typeck_lit[7] = {116, 121, 112, 101, 99, 107, 0};
#undef g_pipe_entry_lib_kw0
static uint8_t g_pipe_entry_lib_kw0[5] = {109, 97, 105, 110, 0};
#undef g_pipe_entry_lib_kw1
static uint8_t g_pipe_entry_lib_kw1[6] = {98, 117, 105, 108, 100, 0};
#undef g_pipe_entry_lib_kw2
static uint8_t g_pipe_entry_lib_kw2[9] = {112, 105, 112, 101, 108, 105, 110, 101, 0};
#undef g_pipe_entry_lib_kw3
static uint8_t g_pipe_entry_lib_kw3[7] = {100, 114, 105, 118, 101, 114, 0};
#undef g_pipe_entry_lib_kw4
static uint8_t g_pipe_entry_lib_kw4[8] = {99, 111, 100, 101, 103, 101, 110, 0};
#undef g_pipe_entry_lib_kw5
static uint8_t g_pipe_entry_lib_kw5[7] = {116, 121, 112, 101, 99, 107, 0};
#undef g_pipe_entry_lib_kw6
static uint8_t g_pipe_entry_lib_kw6[7] = {112, 97, 114, 115, 101, 114, 0};
#undef g_pipe_entry_lib_kw7
static uint8_t g_pipe_entry_lib_kw7[6] = {116, 111, 107, 101, 110, 0};
#undef g_pipe_entry_lib_kw8
static uint8_t g_pipe_entry_lib_kw8[6] = {108, 101, 120, 101, 114, 0};
#undef g_pipe_entry_lib_kw9
static uint8_t g_pipe_entry_lib_kw9[4] = {97, 115, 116, 0};
#undef g_pipe_entry_lib_stem_buf
static uint8_t g_pipe_entry_lib_stem_buf[128];
#undef g_pipe_imp_mod
static uint8_t g_pipe_imp_mod[1024];
#undef g_pipe_imp_n
static int32_t g_pipe_imp_n[128];
#undef g_pipe_imp_cap
static int32_t g_pipe_imp_cap[128];
#undef g_pipe_imp_entries
static uint8_t g_pipe_imp_entries[1024];
#undef g_pipe_imp_sel_n
static int32_t g_pipe_imp_sel_n[128];
#undef g_pipe_imp_sel_cap
static int32_t g_pipe_imp_sel_cap[128];
#undef g_pipe_imp_sel_rows
static uint8_t g_pipe_imp_sel_rows[1024];
#undef g_pipe_imp_sel_lens
static uint8_t g_pipe_imp_sel_lens[1024];
static void init_globals(void) {
  g_import_open_valid = 0;
  g_pipe_entry_dir_is_dot = 1;
  g_pipe_diag_emitted_flag = 0;
  g_pipe_typeck_ndep = 0;
  g_pipe_pp_ndefines = 0;
  g_pipe_pp_if_n = 0;
  g_pipe_typeck_diag_soft_suppress = 0;
}
extern int32_t cfg_eval_expr_c(uint8_t * start, int32_t len);
extern int32_t pipeline_asm_user_dep_skip_x_typeck(uint8_t * path);
extern int32_t pipeline_asm_user_std_net_dep_path(uint8_t * path);
extern int32_t pipeline_codegen_path_is_std_io_driver_bytes(uint8_t * path);
extern int32_t typeck_x_ast(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern int32_t typeck_x_ast_library(uint8_t * module, uint8_t * arena, uint8_t * ctx);
extern int32_t typeck_validate_struct_layouts_zero_padding(uint8_t * module, uint8_t * arena);
extern void typeck_patch_all_body_parent_links(uint8_t * module, uint8_t * arena);
extern int32_t ast_pipeline_dep_ctx_ndep(uint8_t * ctx);
extern uint8_t * ast_pipeline_dep_ctx_module_at(uint8_t * ctx, int32_t idx);
extern int32_t pipeline_loop_should_continue_lib_root_c(uint8_t * ctx, int32_t idx);
extern int32_t pipeline_resolve_path_try_one_lib_root(uint8_t * ctx, int32_t lib_idx, uint8_t * import_path, int32_t path_len);
extern int32_t pipeline_resolve_path_try_entry_dir(uint8_t * ctx, uint8_t * import_path, int32_t path_len);
extern uint8_t * pipeline_dep_ctx_path_buf_ptr(uint8_t * ctx);
extern uint8_t * pipeline_dep_ctx_loaded_buf_ptr(uint8_t * ctx);
extern void pipeline_dep_ctx_set_loaded_len(uint8_t * ctx, int64_t n);
extern int32_t xlang_read_file_into_path(uint8_t * path, uint8_t * buf, int64_t cap);
extern uint8_t * pipeline_dep_ctx_arena_at(uint8_t * ctx, int32_t idx);
extern uint8_t * pipeline_dep_ctx_preprocess_buf_ptr(uint8_t * ctx);
extern int32_t pipeline_dep_ctx_preprocess_len_get(uint8_t * ctx);
extern void typeck_merge_dep_struct_layouts_into_entry(uint8_t * mod, uint8_t * arena, uint8_t * ctx);
extern void typeck_wpo_unify_soa_layouts(uint8_t * entry, uint8_t * ctx);
extern int32_t pipeline_module_main_func_index(uint8_t * module);
extern int32_t runtime_read_file_view(uint8_t * path, uint8_t * out);
extern void runtime_release_file_view(uint8_t * view);
extern void ast_module_free(uint8_t * mod);
extern void ast_pipeline_dep_ctx_reset(uint8_t * ctx);
extern void ast_pipeline_dep_ctx_set_module(uint8_t * ctx, int32_t idx, uint8_t * m);
extern void ast_pipeline_dep_ctx_set_arena(uint8_t * ctx, int32_t idx, uint8_t * a);
extern void ast_pipeline_dep_ctx_set_import_path(uint8_t * ctx, int32_t idx, uint8_t * bytes, int32_t len);
extern void ast_pipeline_dep_ctx_set_ndep(uint8_t * ctx, int32_t n);
extern int32_t asm_asm_codegen_elf_o(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf);
extern void driver_set_pipeline_entry_source_len(int64_t len);
extern int32_t pipeline_run_x_pipeline(uint8_t * module, uint8_t * arena, uint8_t * source_data, int64_t source_len, uint8_t * out_buf, uint8_t * ctx);
extern void driver_run_thread_on_large_stack(uint8_t * fn, uint8_t * arg);
extern int32_t xlang_driver_fputs_opaque(uint8_t * s, uint8_t * stream);
extern uint8_t * xlang_driver_stdout_ptr(void);
extern int32_t xlang_driver_fclose_opaque(uint8_t * stream);
extern uint8_t * xlang_driver_realpath_opaque(uint8_t * path, uint8_t * resolved);
extern void driver_asm_fflush_stdout(void);
extern void driver_pipeline_dep_ctx_set_use_asm(uint8_t * ctx, int32_t v);
extern int32_t ast_pipeline_ctx_append_lib_root(uint8_t * ctx, uint8_t * path, int32_t len);
extern int32_t preprocess_x_buf(uint8_t * src, int64_t src_len, uint8_t * out_buf, int32_t out_cap);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern void diag_report(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * msg, uint8_t * detail);
extern int32_t driver_check_only_get(void);
extern void driver_check_only_set(int32_t v);
extern void driver_x_pipeline_skip_typeck_set(int32_t v);
extern void driver_x_pipeline_skip_codegen_set(int32_t v);
extern int32_t driver_pipeline_dep_ctx_get_asm_entry_module_only(uint8_t * ctx);
extern void driver_pipeline_dep_ctx_set_asm_entry_module_only(uint8_t * ctx, int32_t v);
extern int32_t driver_parse_into_buf_rc(uint8_t * arena, uint8_t * module, uint8_t * data, int32_t len, int32_t * out_main_idx);
extern int32_t pipeline_module_num_funcs(uint8_t * module);
extern int32_t pipeline_module_func_name_len_at(uint8_t * module, int32_t fi);
extern void pipeline_module_func_name_copy64(uint8_t * module, int32_t fi, uint8_t * dst);
extern int32_t pipeline_module_func_body_ref_at(uint8_t * module, int32_t fi);
extern int32_t ast_ast_block_num_consts(uint8_t * arena, int32_t block_ref);
extern int32_t ast_ast_block_num_lets(uint8_t * arena, int32_t block_ref);
extern int32_t ast_ast_block_num_if_stmts(uint8_t * arena, int32_t block_ref);
extern int32_t ast_ast_block_num_regions(uint8_t * arena, int32_t block_ref);
extern int32_t ast_ast_block_num_stmt_order(uint8_t * arena, int32_t block_ref);
extern int32_t ast_ast_block_final_expr_ref(uint8_t * arena, int32_t block_ref);
extern uint8_t * link_abi_getenv(uint8_t * name);
void parser_parse_into_init(uint8_t * module, uint8_t * arena) {
}
int32_t parser_get_module_num_imports(uint8_t * module) {
  return 0;
}
void parser_get_module_import_path(uint8_t * module, int32_t idx, uint8_t * path_buf) {
  if ((path_buf ==0)) {
    return;
  }
  (void)(((path_buf)[0] = 0));
}
int32_t parser_copy_module_import_path64(uint8_t * module, int32_t i, uint8_t * out) {
  if ((out ==0)) {
    return 0;
  }
  if ((module ==0)) {
    (void)(((out)[0] = 0));
    return 0;
  }
  (void)(pipeline_module_import_path_copy(module, i, out, 64));
  int32_t path_len = 0;
  while ((path_len < 64)) {
    uint8_t ch = 0;
    (void)((ch = (out)[path_len]));
    if ((ch ==0)) {
      break;
    }
    (void)((path_len = (path_len + 1)));
  }
  return path_len;
}
void asm_skip_heavy_set_pipeline_ctx(uint8_t * ctx) {
}
void pipeline_fill_array_lit_types_for_skipped_typeck(uint8_t * m, uint8_t * a) {
}
/* 8.3.3 host-cc leave: thin surface → typeck.x authority (typeck_x.o). */
extern void typeck_soa_fill_field_access_for_asm_emit(uint8_t * m, uint8_t * a);
void pipeline_fill_soa_field_access_for_asm_emit(uint8_t * m, uint8_t * a) {
  typeck_soa_fill_field_access_for_asm_emit(m, a);
}
void pipeline_module_fixup_with_arena_stmt_orders(uint8_t * m, uint8_t * a) {
}
int32_t xlang_asm_codegen_elf_o_product_emit(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf) {
  return asm_asm_codegen_elf_o(module, arena, ctx, elf_ctx, out_buf);
  return -1;
}
int32_t pipeline_parse_set_main_from_buf_c(uint8_t * m, uint8_t * a, uint8_t * d, int32_t len) {
  return 0;
}
void pipeline_diag_emitted_reset(void) {
  {
    int32_t * p = pipeline_diag_emitted_flag_slot();
    (void)(((p)[0] = 0));
  }
}
void pipeline_diag_emitted_note(void) {
  {
    int32_t * p = pipeline_diag_emitted_flag_slot();
    (void)(((p)[0] = 1));
  }
}
int32_t pipeline_diag_emitted_get(void) {
  {
    int32_t * p = pipeline_diag_emitted_flag_slot();
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
int32_t get_ndep(void) {
  {
    int32_t * p = typeck_ndep_slot();
    int32_t r = (p)[0];
    return r;
  }
  return 0;
}
void pipeline_set_ndep(int32_t n) {
  (void)(typeck_ndep_store(n));
}
int32_t driver_dep_seeded_get(int32_t i) {
  if ((i < 0)) {
    return 0;
  }
  if ((i >=32)) {
    return 0;
  }
  {
    int32_t * p = driver_dep_seeded_slot(i);
    if (((p)[0] !=0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}
void driver_dep_seeded_set(int32_t i, int32_t v) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  {
    int32_t * p = driver_dep_seeded_slot(i);
    (void)(((p)[0] = v));
  }
}
int32_t typeck_driver_dep_seeded_get(int32_t i) {
  return driver_dep_seeded_get(i);
}
uint8_t * get_dep_module(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  {
    int32_t n = get_ndep();
    if ((i >=n)) {
      return ((uint8_t *)(0));
    }
    uint8_t * r = typeck_dep_module_get(i);
    return r;
  }
  return ((uint8_t *)(0));
}
uint8_t * get_dep_arena(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  {
    int32_t n = get_ndep();
    if ((i >=n)) {
      return ((uint8_t *)(0));
    }
    uint8_t * r = typeck_dep_arena_get(i);
    return r;
  }
  return ((uint8_t *)(0));
}
uint8_t * typeck_get_dep_module(int32_t i) {
  return get_dep_module(i);
}
uint8_t * typeck_get_dep_arena(int32_t i) {
  return get_dep_arena(i);
}
void pipeline_set_dep(int32_t i, uint8_t * mod, uint8_t * arena) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(typeck_dep_module_set_impl(i, mod));
  (void)(typeck_dep_arena_set_impl(i, arena));
}
void driver_dep_publish_slot(int32_t i, uint8_t * arena, uint8_t * module, uint8_t * import_path) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(driver_dep_arena_ptr_set_impl(i, arena));
  (void)(driver_dep_module_ptr_set_impl(i, module));
  (void)(driver_dep_seeded_set(i, 1));
  (void)(driver_dep_path_registry_set(i, import_path));
}
uint8_t * typeck_driver_dep_module_buf(int32_t i) {
  {
    uint8_t * r = driver_dep_module_buf(i);
    return r;
  }
  return ((uint8_t *)(0));
}
uint8_t * typeck_driver_dep_arena_buf(int32_t i) {
  {
    uint8_t * r = driver_dep_arena_buf(i);
    return r;
  }
  return ((uint8_t *)(0));
}
int32_t xlang_cstr_ends_with_dot_x(uint8_t * s) {
  if ((s ==0)) {
    return 0;
  }
  {
    int64_t n = 0;
    while (((s)[n] !=0)) {
      (void)((n = (n + 1)));
    }
    if ((n < 2)) {
      return 0;
    }
    if (((s)[(n - 2)] !=46)) {
      return 0;
    }
    if (((s)[(n - 1)] !=120)) {
      return 0;
    }
    return 1;
  }
  return 0;
}
int32_t xlang_asm_out_buf_is_object_magic(uint8_t * data) {
  if ((data ==0)) {
    return 0;
  }
  {
    uint8_t b0 = (data)[0];
    uint8_t b1 = (data)[1];
    uint8_t b2 = (data)[2];
    uint8_t b3 = (data)[3];
    if ((b0 ==207)) {
      if ((b1 ==250)) {
        if ((b2 ==237)) {
          if ((b3 ==254)) {
            return 1;
          }
        }
      }
    }
    if ((b0 ==254)) {
      if ((b1 ==237)) {
        if ((b2 ==250)) {
          if ((b3 ==207)) {
            return 1;
          }
        }
      }
    }
    if ((b0 ==127)) {
      if ((b1 ==69)) {
        if ((b2 ==76)) {
          if ((b3 ==70)) {
            return 1;
          }
        }
      }
    }
    return 0;
  }
  return 0;
}
int32_t xlang_import_path_is_file_path(uint8_t * import_path) {
  if ((import_path ==0)) {
    return 0;
  }
  if (((import_path)[0] ==0)) {
    return 0;
  }
  if (((import_path)[0] ==47)) {
    return 1;
  }
  if (((import_path)[0] ==46)) {
    return 1;
  }
  if ((strchr(import_path, 47) !=0)) {
    return 1;
  }
  if ((xlang_cstr_ends_with_dot_x(import_path) !=0)) {
    return 1;
  }
  return 0;
  return 0;
}
int32_t xlang_asm_user_std_dep_skip_x_typeck(uint8_t * dep_path) {
  if ((dep_path ==0)) {
    return 0;
  }
  if (((dep_path)[0] ==0)) {
    return 0;
  }
  if ((pipeline_asm_user_dep_skip_x_typeck(dep_path) !=0)) {
    return 1;
  }
  return 0;
  return 0;
}
int32_t xlang_asm_user_std_net_dep_path(uint8_t * dep_path) {
  if ((dep_path ==0)) {
    return 0;
  }
  if (((dep_path)[0] ==0)) {
    return 0;
  }
  if ((pipeline_asm_user_std_net_dep_path(dep_path) !=0)) {
    return 1;
  }
  return 0;
  return 0;
}
int32_t xlang_asm_user_std_io_driver_dep_path(uint8_t * dep_path) {
  if ((dep_path ==0)) {
    return 0;
  }
  if (((dep_path)[0] ==0)) {
    return 0;
  }
  if ((pipeline_codegen_path_is_std_io_driver_bytes(dep_path) !=0)) {
    return 1;
  }
  return 0;
  return 0;
}
int32_t xlang_asm_user_dep_parse_skip_typeck_path(uint8_t * dep_path) {
  if ((xlang_asm_user_std_net_dep_path(dep_path) !=0)) {
    return 1;
  }
  if ((xlang_asm_user_std_io_driver_dep_path(dep_path) !=0)) {
    return 1;
  }
  return 0;
  return 0;
}
int32_t xlang_asm_out_buf_is_object(uint8_t * data, int64_t len) {
  if ((data ==0)) {
    return 0;
  }
  if ((len < 4)) {
    return 0;
  }
  return xlang_asm_out_buf_is_object_magic(data);
  return 0;
}
uint8_t * xlang_dep_prerun_entry_dir(uint8_t * main_entry_dir, uint8_t * lib_roots, int32_t n_lib_roots) {
  if ((n_lib_roots <=0)) {
    return main_entry_dir;
  }
  return xlang_dep_prerun_entry_dir_pick(main_entry_dir, lib_roots, n_lib_roots);
  return main_entry_dir;
}
int32_t xlang_find_loaded_import_index(uint8_t * import_path, uint8_t * all_paths, int32_t n_all) {
  if ((import_path ==0)) {
    return -1;
  }
  if ((all_paths ==0)) {
    return -1;
  }
  if ((n_all <=0)) {
    return -1;
  }
  return xlang_find_loaded_import_index_scan(import_path, all_paths, n_all);
}
int32_t xlang_merge_deps_path_already_out(uint8_t * path, uint8_t * out_paths, int32_t n_out) {
  if ((path ==0)) {
    return 0;
  }
  if ((out_paths ==0)) {
    return 0;
  }
  if ((n_out <=0)) {
    return 0;
  }
  return xlang_merge_deps_path_already_out_scan(path, out_paths, n_out);
}
void xlang_fputs_stdout(uint8_t * s) {
  if ((s ==0)) {
    return;
  }
  {
    uint8_t * so = xlang_driver_stdout_ptr();
    if ((so !=0)) {
      (void)(xlang_driver_fputs_opaque(s, so));
    }
  }
}
/* wave309: no-op — product glue shell retired; do not emit #include pipeline_glue.c. */
void xlang_emit_pipeline_glue_include(void) {
  return;
}
int32_t xlang_import_dep_dir_from_path(uint8_t * path, uint8_t * dep_dir, int64_t dep_dir_size) {
  if ((path ==0)) {
    return -1;
  }
  if ((dep_dir ==0)) {
    return -1;
  }
  if ((dep_dir_size ==0)) {
    return -1;
  }
  {
    int64_t n = 0;
    while ((n < 4096)) {
      if (((path)[n] ==0)) {
        break;
      }
      (void)((n = (n + 1)));
    }
    int64_t last_slash = -1;
    int64_t i = 0;
    while ((i < n)) {
      if (((path)[i] ==47)) {
        (void)((last_slash = i));
      }
      (void)((i = (i + 1)));
    }
    if ((last_slash < 0)) {
      if ((dep_dir_size < 2)) {
        return -1;
      }
      (void)(((dep_dir)[0] = 46));
      (void)(((dep_dir)[1] = 0));
      return 0;
    }
    int64_t dlen = last_slash;
    if ((dlen >=dep_dir_size)) {
      return -1;
    }
    int64_t j = 0;
    while ((j < dlen)) {
      (void)(((dep_dir)[j] = (path)[j]));
      (void)((j = (j + 1)));
    }
    (void)(((dep_dir)[dlen] = 0));
    return 0;
  }
  return -1;
}
void pipeline_debug_trace_body_x_mega_pre_reset(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x72\x65\x5f\x72\x65\x73\x65\x74"), module, arena));
}
void pipeline_debug_trace_body_x_mega_post_reset(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x6f\x73\x74\x5f\x72\x65\x73\x65\x74"), module, arena));
}
void pipeline_debug_trace_body_x_mega_post_params(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x6f\x73\x74\x5f\x70\x61\x72\x61\x6d\x73"), module, arena));
}
void pipeline_debug_trace_body_x_mega_post_frame(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x6f\x73\x74\x5f\x66\x72\x61\x6d\x65"), module, arena));
}
void pipeline_debug_trace_body_x_mega_post_locals(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x6f\x73\x74\x5f\x6c\x6f\x63\x61\x6c\x73"), module, arena));
}
void pipeline_debug_trace_body_x_mega_pre_emit(uint8_t * module, uint8_t * arena) {
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x78\x5f\x6d\x65\x67\x61\x5f\x70\x72\x65\x5f\x65\x6d\x69\x74"), module, arena));
}
void driver_typeck_dep_sidecar_clear(void) {
  (void)(typeck_ndep_store(0));
  int32_t i = 0;
  while ((i < 32)) {
    (void)(typeck_dep_module_set(i, 0));
    (void)(typeck_dep_arena_set(i, 0));
    (void)((i = (i + 1)));
  }
}
void driver_dep_seeded_clear_slots(void) {
  int32_t i = 0;
  while ((i < 32)) {
    (void)(driver_dep_seeded_set(i, 0));
    (void)(driver_dep_path_registry_set(i, 0));
    (void)(driver_dep_arena_ptr_set(i, 0));
    (void)(driver_dep_module_ptr_set(i, 0));
    (void)((i = (i + 1)));
  }
}
void driver_dep_seeded_clear_all(void) {
  (void)(driver_dep_seeded_clear_slots());
  (void)(driver_typeck_dep_sidecar_clear());
}
void xlang_get_entry_dir(uint8_t * input_path, uint8_t * entry_dir, int64_t size) {
  if ((entry_dir ==0)) {
    return;
  }
  if ((size ==0)) {
    return;
  }
  if ((input_path ==0)) {
    (void)(((entry_dir)[0] = 0));
    return;
  }
  {
    int32_t last = -1;
    int32_t i = 0;
    while ((i < 65536)) {
      if (((input_path)[i] ==0)) {
        break;
      }
      if (((input_path)[i] ==47)) {
        (void)((last = i));
      }
      (void)((i = (i + 1)));
    }
    if ((last < 0)) {
      if ((size >=2)) {
        (void)(((entry_dir)[0] = 46));
        (void)(((entry_dir)[1] = 0));
      } else {
        (void)(((entry_dir)[0] = 0));
      }
      return;
    }
    int32_t len = last;
    int32_t cap = ((int32_t)(size));
    if ((cap <=0)) {
      return;
    }
    if ((len >=cap)) {
      (void)((len = (cap - 1)));
    }
    int32_t k = 0;
    while ((k < len)) {
      (void)(((entry_dir)[k] = (input_path)[k]));
      (void)((k = (k + 1)));
    }
    (void)(((entry_dir)[len] = 0));
  }
}
int32_t driver_asm_fp_is_stdout(uint8_t * fp) {
  if ((fp ==0)) {
    return 0;
  }
  {
    uint8_t * so = xlang_driver_stdout_ptr();
    if ((fp ==so)) {
      return 1;
    }
  }
  return 0;
}
void driver_asm_fclose_file(uint8_t * fp) {
  if ((fp ==0)) {
    return;
  }
  (void)(xlang_driver_fclose_opaque(fp));
}
void driver_asm_fclose_asm_out(uint8_t * fp) {
  if ((fp ==0)) {
    (void)(driver_asm_fflush_stdout());
    return;
  }
  if ((driver_asm_fp_is_stdout(fp) !=0)) {
    (void)(driver_asm_fflush_stdout());
    return;
  }
  (void)(driver_asm_fclose_file(fp));
}
void xlang_import_path_to_file_path(uint8_t * lib_root, uint8_t * import_path, uint8_t * path, int64_t path_size) {
  if ((path ==0)) {
    return;
  }
  if ((path_size ==0)) {
    return;
  }
  {
    int32_t cap = ((int32_t)(path_size));
    if ((cap <=0)) {
      return;
    }
    uint8_t * r = lib_root;
    if ((r ==0)) {
      (void)((r = ((uint8_t *)(0))));
    } else {
      if (((r)[0] ==0)) {
        (void)((r = ((uint8_t *)(0))));
      }
    }
    int32_t off = 0;
    if ((r ==0)) {
      if (((off + 1) < cap)) {
        (void)(((path)[off] = 46));
        (void)((off = (off + 1)));
      }
    } else {
      int32_t ri = 0;
      while ((ri < 4096)) {
        if (((r)[ri] ==0)) {
          break;
        }
        if (((off + 1) >=cap)) {
          break;
        }
        (void)(((path)[off] = (r)[ri]));
        (void)((off = (off + 1)));
        (void)((ri = (ri + 1)));
      }
    }
    if (((off + 1) < cap)) {
      (void)(((path)[off] = 47));
      (void)((off = (off + 1)));
    }
    if ((import_path !=0)) {
      int32_t s = 0;
      while ((s < 4096)) {
        if (((import_path)[s] ==0)) {
          break;
        }
        if (((off + 1) >=cap)) {
          break;
        }
        uint8_t ch = (import_path)[s];
        if ((ch ==46)) {
          (void)(((path)[off] = 47));
        } else {
          (void)(((path)[off] = ch));
        }
        (void)((off = (off + 1)));
        (void)((s = (s + 1)));
      }
    }
    if (((off + 2) < cap)) {
      (void)(((path)[off] = 46));
      (void)(((path)[(off + 1)] = 120));
      (void)(((path)[(off + 2)] = 0));
    } else {
      if ((off < cap)) {
        (void)(((path)[off] = 0));
      } else {
        if ((cap > 0)) {
          (void)(((path)[(cap - 1)] = 0));
        }
      }
    }
  }
}
void pipe_cstr_join_slash(uint8_t * dst, int32_t cap, uint8_t * a, uint8_t * b) {
  if ((dst ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  int32_t off = 0;
  if ((a !=0)) {
    int32_t i = 0;
    while ((i < 4096)) {
      if (((a)[i] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (a)[i]));
      (void)((off = (off + 1)));
      (void)((i = (i + 1)));
    }
  }
  if (((off + 1) < cap)) {
    (void)(((dst)[off] = 47));
    (void)((off = (off + 1)));
  }
  if ((b !=0)) {
    int32_t j = 0;
    while ((j < 4096)) {
      if (((b)[j] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (b)[j]));
      (void)((off = (off + 1)));
      (void)((j = (j + 1)));
    }
  }
  if ((off < cap)) {
    (void)(((dst)[off] = 0));
  } else {
    (void)(((dst)[(cap - 1)] = 0));
  }
}
void xlang_path_try_realpath_inplace(uint8_t * path, int64_t path_size) {
  if ((path ==0)) {
    return;
  }
  if ((path_size ==0)) {
    return;
  }
  {
    uint8_t resolved[1024] = {};
    uint8_t * r = xlang_driver_realpath_opaque(path, &((resolved)[0]));
    if ((r !=0)) {
      int32_t cap = ((int32_t)(path_size));
      if ((cap > 0)) {
        (void)(pipe_cstr_copy(path, cap, r));
      }
    }
  }
}
void xlang_resolve_file_import_path(uint8_t * entry_dir, uint8_t * import_path, uint8_t * path, int64_t path_size) {
  if ((path ==0)) {
    return;
  }
  if ((path_size ==0)) {
    return;
  }
  if ((import_path ==0)) {
    (void)(((path)[0] = 0));
    return;
  }
  int32_t cap = ((int32_t)(path_size));
  if ((cap <=0)) {
    return;
  }
  if (((import_path)[0] ==47)) {
    (void)(pipe_cstr_copy(path, cap, import_path));
  } else {
    if ((entry_dir !=0)) {
      if (((entry_dir)[0] !=0)) {
        (void)(pipe_cstr_join_slash(path, cap, entry_dir, import_path));
      } else {
        (void)(pipe_cstr_copy(path, cap, import_path));
      }
    } else {
      (void)(pipe_cstr_copy(path, cap, import_path));
    }
  }
  (void)(xlang_path_try_realpath_inplace(path, path_size));
}
int32_t driver_dep_slot_for_path_scan(uint8_t * path) {
  if ((path ==0)) {
    return -1;
  }
  {
    int32_t i = 0;
    while ((i < 32)) {
      uint8_t * reg = driver_dep_path_registry_at(i);
      if ((reg !=0)) {
        if ((pipe_cstr_eq(reg, path) !=0)) {
          return i;
        }
      }
      (void)((i = (i + 1)));
    }
  }
  return -1;
}
int32_t driver_dep_slot_for_path(uint8_t * path) {
  if ((path ==0)) {
    return -1;
  }
  return driver_dep_slot_for_path_scan(path);
}
int32_t xlang_preprocess_raw_to_malloc_impl(uint8_t * raw, int64_t raw_len, uint8_t * out_src, uint8_t * out_src_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines, int32_t emit_diag) {
  if ((out_src !=0)) {
    (void)(xlang_ptr_slot_set(out_src, 0, 0));
  }
  if ((out_src_len !=0)) {
    (void)(xlang_size_slot_set(out_src_len, 0, 0));
  }
  int32_t buf_cap = 4194304;
  int64_t buf_cap_i64 = ((int64_t)(buf_cap));
  if ((raw_len > buf_cap_i64)) {
    if ((emit_diag !=0)) {
      (void)(pipeline_diag_preprocess_fail(path_diag));
    }
    return -1;
  }
  uint8_t * scratch = 0;
  (void)((scratch = malloc(((size_t)(buf_cap)))));
  if ((scratch ==0)) {
    if ((emit_diag !=0)) {
      uint8_t what[16] = {};
      (void)(((what)[0] = 115));
      (void)(((what)[1] = 99));
      (void)(((what)[2] = 114));
      (void)(((what)[3] = 97));
      (void)(((what)[4] = 116));
      (void)(((what)[5] = 99));
      (void)(((what)[6] = 104));
      (void)(((what)[7] = 32));
      (void)(((what)[8] = 98));
      (void)(((what)[9] = 117));
      (void)(((what)[10] = 102));
      (void)(((what)[11] = 102));
      (void)(((what)[12] = 101));
      (void)(((what)[13] = 114));
      (void)(((what)[14] = 0));
      (void)(pipeline_diag_preprocess_alloc_fail(path_diag, &((what)[0])));
    }
    return -1;
  }
  (void)(preprocess_define_reset());
  int32_t di = 0;
  while ((di < ndefines)) {
    if ((defines !=0)) {
      uint8_t * dname = xlang_ptr_slot_get(defines, di);
      if ((dname !=0)) {
        (void)(preprocess_define_add(dname));
      }
    }
    (void)((di = (di + 1)));
  }
  int32_t n = 0;
  (void)((n = preprocess_x_buf(raw, raw_len, scratch, buf_cap)));
  if ((n < 0)) {
    (void)(free(scratch));
    if ((emit_diag !=0)) {
      if ((n <=-2)) {
        (void)(pipeline_diag_preprocess_directive_code(path_diag, n));
      } else {
        int32_t stack_n = 0;
        (void)((stack_n = preprocess_if_stack_len()));
        if ((stack_n !=0)) {
          (void)(pipeline_diag_preprocess_unclosed_if(path_diag));
        } else {
          (void)(pipeline_diag_preprocess_fail(path_diag));
        }
      }
    }
    return -1;
  }
  int32_t stack_after = 0;
  (void)((stack_after = preprocess_if_stack_len()));
  if ((stack_after !=0)) {
    (void)(free(scratch));
    if ((emit_diag !=0)) {
      (void)(pipeline_diag_preprocess_unclosed_if(path_diag));
    }
    return -1;
  }
  uint8_t * dup = 0;
  (void)((dup = malloc(((size_t)((n + 1))))));
  if ((dup ==0)) {
    (void)(free(scratch));
    if ((emit_diag !=0)) {
      uint8_t what2[16] = {};
      (void)(((what2)[0] = 111));
      (void)(((what2)[1] = 117));
      (void)(((what2)[2] = 116));
      (void)(((what2)[3] = 112));
      (void)(((what2)[4] = 117));
      (void)(((what2)[5] = 116));
      (void)(((what2)[6] = 32));
      (void)(((what2)[7] = 98));
      (void)(((what2)[8] = 117));
      (void)(((what2)[9] = 102));
      (void)(((what2)[10] = 102));
      (void)(((what2)[11] = 101));
      (void)(((what2)[12] = 114));
      (void)(((what2)[13] = 0));
      (void)(pipeline_diag_preprocess_alloc_fail(path_diag, &((what2)[0])));
    }
    return -1;
  }
  int32_t i = 0;
  while ((i < n)) {
    (void)(((dup)[i] = (scratch)[i]));
    (void)((i = (i + 1)));
  }
  (void)(((dup)[n] = 0));
  (void)(free(scratch));
  if ((out_src !=0)) {
    (void)(xlang_ptr_slot_set(out_src, 0, dup));
  }
  if ((out_src_len !=0)) {
    (void)(xlang_size_slot_set(out_src_len, 0, ((int64_t)(n))));
  }
  return 0;
}
int32_t xlang_preprocess_raw_to_malloc(uint8_t * raw, int64_t raw_len, uint8_t * out_src, uint8_t * out_src_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines) {
  if ((raw_len < 0)) {
    return -1;
  }
  if ((raw ==0)) {
    if ((raw_len > 0)) {
      return -1;
    }
  }
  if ((ndefines < 0)) {
    return -1;
  }
  return xlang_preprocess_raw_to_malloc_impl(raw, raw_len, out_src, out_src_len, path_diag, defines, ndefines, 1);
  return -1;
}
uint8_t * xlang_preprocess_with_path(uint8_t * source, size_t source_len, uint8_t * path_diag, uint8_t * defines, int32_t ndefines, uint8_t * out_length) {
  if ((out_length !=0)) {
    (void)(xlang_size_slot_set(out_length, 0, 0));
  }
  if ((source ==0)) {
    return ((uint8_t *)(0));
  }
  int64_t slen = ((int64_t)(source_len));
  if ((slen ==0)) {
    (void)((slen = ((int64_t)(pipe_cstr_len(source)))));
  }
  uint8_t out_prep[8] = {};
  uint8_t out_len[8] = {};
  (void)(pipe_store_ptr_slot(&((out_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((out_len)[0]), 0, 0));
  uint8_t * def_arg = 0;
  if ((ndefines > 0)) {
    (void)((def_arg = defines));
  }
  int32_t rc = 0;
  (void)((rc = xlang_preprocess_raw_to_malloc_impl(source, slen, &((out_prep)[0]), &((out_len)[0]), path_diag, def_arg, ndefines, 1)));
  if ((rc !=0)) {
    return ((uint8_t *)(0));
  }
  uint8_t * prep = pipe_load_ptr_slot(&((out_prep)[0]), 0);
  int64_t olen = xlang_size_slot_get(&((out_len)[0]), 0);
  if ((out_length !=0)) {
    (void)(xlang_size_slot_set(out_length, 0, olen));
  }
  return prep;
}
uint8_t * xlang_preprocess_quiet(uint8_t * source, size_t source_len, uint8_t * defines, int32_t ndefines, uint8_t * out_length) {
  if ((out_length !=0)) {
    (void)(xlang_size_slot_set(out_length, 0, 0));
  }
  if ((source ==0)) {
    return ((uint8_t *)(0));
  }
  int64_t slen = ((int64_t)(source_len));
  if ((slen ==0)) {
    (void)((slen = ((int64_t)(pipe_cstr_len(source)))));
  }
  uint8_t out_prep[8] = {};
  uint8_t out_len[8] = {};
  (void)(pipe_store_ptr_slot(&((out_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((out_len)[0]), 0, 0));
  uint8_t * def_arg = 0;
  if ((ndefines > 0)) {
    (void)((def_arg = defines));
  }
  int32_t rc = 0;
  (void)((rc = xlang_preprocess_raw_to_malloc_impl(source, slen, &((out_prep)[0]), &((out_len)[0]), 0, def_arg, ndefines, 0)));
  if ((rc !=0)) {
    return ((uint8_t *)(0));
  }
  uint8_t * prep = pipe_load_ptr_slot(&((out_prep)[0]), 0);
  int64_t olen = xlang_size_slot_get(&((out_len)[0]), 0);
  if ((out_length !=0)) {
    (void)(xlang_size_slot_set(out_length, 0, olen));
  }
  return prep;
}
uint8_t * xlang_preprocess(uint8_t * source, size_t source_len, uint8_t * defines, int32_t ndefines, uint8_t * out_length) {
  return xlang_preprocess_quiet(source, source_len, defines, ndefines, out_length);
}
void driver_dep_seed_slots(uint8_t * arenas, uint8_t * modules, int32_t n) {
  int32_t j = 0;
  while ((j < 32)) {
    if ((j < n)) {
      {
        uint8_t * a = 0;
        uint8_t * m = 0;
        if ((arenas !=0)) {
          (void)((a = pipe_load_ptr_slot(arenas, j)));
        }
        if ((modules !=0)) {
          (void)((m = pipe_load_ptr_slot(modules, j)));
        }
        (void)(driver_dep_arena_ptr_set(j, a));
        (void)(driver_dep_module_ptr_set(j, m));
        (void)(driver_dep_seeded_set(j, 1));
      }
    } else {
      (void)(driver_dep_seeded_set(j, 0));
    }
    (void)((j = (j + 1)));
  }
}
int32_t pipe_cstr_contains(uint8_t * hay, uint8_t * needle) {
  if ((hay ==0)) {
    return 0;
  }
  if ((needle ==0)) {
    return 0;
  }
  if (((needle)[0] ==0)) {
    return 1;
  }
  {
    int32_t hi = 0;
    while ((hi < 4096)) {
      if (((hay)[hi] ==0)) {
        return 0;
      }
      int32_t j = 0;
      int32_t ok = 1;
      while ((ok !=0)) {
        if (((needle)[j] ==0)) {
          return 1;
        }
        if (((hay)[(hi + j)] ==0)) {
          (void)((ok = 0));
        } else {
          if (((hay)[(hi + j)] !=(needle)[j])) {
            (void)((ok = 0));
          } else {
            (void)((j = (j + 1)));
          }
        }
      }
      (void)((hi = (hi + 1)));
    }
  }
  return 0;
}
uint8_t * xlang_entry_lib_name_from_path(uint8_t * input_path) {
  if ((input_path ==0)) {
    return xlang_cstr_typeck_lit();
  }
  return xlang_entry_lib_name_from_path_impl(input_path);
}
uint8_t * pipeline_get_dep_arena_slot(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return pipeline_dep_arena_slot_at(i);
  return ((uint8_t *)(0));
}
uint8_t * pipeline_get_dep_module_slot(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return pipeline_dep_module_slot_at(i);
  return ((uint8_t *)(0));
}
void pipe_cstr_copy(uint8_t * dst, int32_t cap, uint8_t * src) {
  int32_t i = 0;
  if ((dst ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  if ((src ==0)) {
    (void)(((dst)[0] = 0));
    return;
  }
  while ((i < (cap - 1))) {
    uint8_t c = (src)[i];
    (void)(((dst)[i] = c));
    if ((c ==0)) {
      return;
    }
    (void)((i = (i + 1)));
  }
  (void)(((dst)[(cap - 1)] = 0));
}
void pipeline_diag_import_open_fail_once(uint8_t * import_path, uint8_t * resolved_path) {
  uint8_t q[2] = {};
  (void)(((q)[0] = 63));
  (void)(((q)[1] = 0));
  uint8_t * import_key = import_path;
  uint8_t * resolved_key = resolved_path;
  if ((import_key ==0)) {
    (void)((import_key = &((q)[0])));
  }
  if ((resolved_key ==0)) {
    (void)((resolved_key = &((q)[0])));
  }
  {
    if ((g_import_open_valid !=0)) {
      if ((pipe_cstr_eq(&((g_import_open_import)[0]), import_key) !=0)) {
        if ((pipe_cstr_eq(&((g_import_open_resolved)[0]), resolved_key) !=0)) {
          (void)(pipeline_diag_emitted_note());
          return;
        }
      }
    }
    (void)(pipe_cstr_copy(&((g_import_open_import)[0]), 65, import_key));
    (void)(pipe_cstr_copy(&((g_import_open_resolved)[0]), 512, resolved_key));
    (void)((g_import_open_valid = 1));
    (void)(pipeline_diag_emitted_note());
    uint8_t kind[16] = {};
    uint8_t code[8] = {};
    uint8_t msg[32] = {};
    (void)(((kind)[0] = 105));
    (void)(((kind)[1] = 109));
    (void)(((kind)[2] = 112));
    (void)(((kind)[3] = 111));
    (void)(((kind)[4] = 114));
    (void)(((kind)[5] = 116));
    (void)(((kind)[6] = 32));
    (void)(((kind)[7] = 101));
    (void)(((kind)[8] = 114));
    (void)(((kind)[9] = 114));
    (void)(((kind)[10] = 111));
    (void)(((kind)[11] = 114));
    (void)(((kind)[12] = 0));
    (void)(((code)[0] = 73));
    (void)(((code)[1] = 77));
    (void)(((code)[2] = 80));
    (void)(((code)[3] = 48));
    (void)(((code)[4] = 48));
    (void)(((code)[5] = 49));
    (void)(((code)[6] = 0));
    (void)(((msg)[0] = 99));
    (void)(((msg)[1] = 97));
    (void)(((msg)[2] = 110));
    (void)(((msg)[3] = 110));
    (void)(((msg)[4] = 111));
    (void)(((msg)[5] = 116));
    (void)(((msg)[6] = 32));
    (void)(((msg)[7] = 111));
    (void)(((msg)[8] = 112));
    (void)(((msg)[9] = 101));
    (void)(((msg)[10] = 110));
    (void)(((msg)[11] = 32));
    (void)(((msg)[12] = 105));
    (void)(((msg)[13] = 109));
    (void)(((msg)[14] = 112));
    (void)(((msg)[15] = 111));
    (void)(((msg)[16] = 114));
    (void)(((msg)[17] = 116));
    (void)(((msg)[18] = 0));
    uint8_t * file = resolved_path;
    if ((file ==0)) {
      (void)((file = import_path));
    }
    (void)(diag_report_with_code(file, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), 0));
  }
}
void pipeline_resolve_path_into_static(uint8_t * path_c) {
  if ((path_c ==0)) {
    return;
  }
  uint8_t dot[2] = {};
  (void)(((dot)[0] = 46));
  (void)(((dot)[1] = 0));
  uint8_t roots[8] = {};
  {
    (void)(xlang_ptr_slot_set(&((roots)[0]), 0, &((dot)[0])));
    uint8_t * entry = pipeline_entry_dir_get();
    uint8_t * rbuf = pipeline_resolved_path_buf_slot();
    (void)(xlang_resolve_import_file_path_multi(&((roots)[0]), 1, entry, path_c, rbuf, 512));
  }
}
int32_t pipeline_resolve_path(uint8_t * path_ptr, int32_t path_len) {
  if ((path_ptr ==0)) {
    return -1;
  }
  int32_t plen = path_len;
  if ((plen <=0)) {
    (void)((plen = 64));
  }
  if ((plen > 64)) {
    (void)((plen = 64));
  }
  uint8_t path_c[65] = {};
  int32_t k = 0;
  while ((k < plen)) {
    if (((path_ptr)[k] ==0)) {
      break;
    }
    (void)(((path_c)[k] = (path_ptr)[k]));
    (void)((k = (k + 1)));
  }
  (void)(((path_c)[k] = 0));
  (void)(pipeline_resolve_path_into_static(&((path_c)[0])));
  return 0;
}
int32_t pipeline_read_file_stage_prep(void) {
  (void)(pipeline_rf_stage_prep_clear());
  uint8_t * path = 0;
  (void)((path = pipeline_resolved_path_buf_slot()));
  uint8_t view[32] = {};
  int32_t z = 0;
  while ((z < 32)) {
    (void)(((view)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t view_rc = 0;
  (void)((view_rc = runtime_read_file_view(path, &((view)[0]))));
  if ((view_rc !=0)) {
    (void)(pipeline_diag_import_open_fail_once(0, path));
    return -1;
  }
  uint8_t * raw_data = xlang_ptr_slot_get(&((view)[0]), 0);
  int64_t raw_len = xlang_size_slot_get(&((view)[0]), 1);
  uint8_t out_prep[8] = {};
  uint8_t out_len[8] = {};
  (void)(pipe_store_ptr_slot(&((out_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((out_len)[0]), 0, 0));
  int32_t prep_rc = 0;
  (void)((prep_rc = xlang_preprocess_raw_to_malloc(raw_data, raw_len, &((out_prep)[0]), &((out_len)[0]), path, 0, 0)));
  (void)(runtime_release_file_view(&((view)[0])));
  if ((prep_rc !=0)) {
    return -1;
  }
  uint8_t * prep = pipe_load_ptr_slot(&((out_prep)[0]), 0);
  int64_t prep_len = xlang_size_slot_get(&((out_len)[0]), 0);
  if ((prep ==0)) {
    (void)(pipeline_diag_import_preprocess_fail(0, path));
    return -1;
  }
  (void)(pipeline_rf_stage_prep_set(prep, prep_len));
  return 0;
}
int32_t pipeline_read_file_commit_prep(void) {
  uint8_t out_prep[8] = {};
  uint8_t out_len[8] = {};
  (void)(pipe_store_ptr_slot(&((out_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((out_len)[0]), 0, 0));
  int32_t take_rc = 0;
  (void)((take_rc = pipeline_rf_stage_prep_take(&((out_prep)[0]), &((out_len)[0]))));
  if ((take_rc !=0)) {
    return -1;
  }
  uint8_t * prep = pipe_load_ptr_slot(&((out_prep)[0]), 0);
  int64_t prep_len = xlang_size_slot_get(&((out_len)[0]), 0);
  if ((prep ==0)) {
    return -1;
  }
  return pipeline_loaded_import_commit_from_owned(prep, prep_len);
  return -1;
}
int32_t pipeline_read_file(void) {
  if ((pipeline_read_file_stage_prep() !=0)) {
    return -1;
  }
  if ((pipeline_read_file_commit_prep() !=0)) {
    return -1;
  }
  return 0;
}
int32_t pipeline_parse_into_bytes(uint8_t * arena, uint8_t * module, uint8_t * data, int64_t len) {
  if ((arena ==0)) {
    return -1;
  }
  if ((module ==0)) {
    return -1;
  }
  if ((data ==0)) {
    return -1;
  }
  int64_t imax = 2147483647;
  if ((len < 0)) {
    return -1;
  }
  if ((len > imax)) {
    return -1;
  }
  int32_t len_i32 = ((int32_t)(len));
  {
    (void)(parser_parse_into_init(module, arena));
    int32_t pr_ok = driver_parse_into_buf_rc(arena, module, data, len_i32, 0);
    if ((pr_ok ==0)) {
      return 0;
    }
    return -1;
  }
  return -1;
}
int32_t pipeline_parse_into_loaded_import(uint8_t * arena, uint8_t * module) {
  if ((arena ==0)) {
    return -1;
  }
  if ((module ==0)) {
    return -1;
  }
  {
    uint8_t * data = pipeline_loaded_import_data();
    if ((data ==0)) {
      return -1;
    }
    int64_t len = pipeline_loaded_import_len_get();
    return pipeline_parse_into_bytes(arena, module, data, len);
  }
  return -1;
}
int32_t xlang_pipeline_run_x_pipeline_large_stack(uint8_t * module, uint8_t * arena, uint8_t * source_data, int64_t source_len, uint8_t * out_buf, uint8_t * ctx) {
  if ((module ==0)) {
    return -1;
  }
  if ((arena ==0)) {
    return -1;
  }
  if ((source_data ==0)) {
    return -1;
  }
  if ((source_len <=0)) {
    return -1;
  }
  return xlang_pipeline_run_x_pipeline_large_stack_impl(module, arena, source_data, source_len, out_buf, ctx);
  return -1;
}
int32_t xlang_pipeline_dep_prerun_parse_skip_typeck_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx) {
  {
    int32_t saved = driver_check_only_get();
    int32_t saved_entry_only = 0;
    (void)(driver_check_only_set(1));
    if ((one_ctx !=0)) {
      (void)((saved_entry_only = driver_pipeline_dep_ctx_get_asm_entry_module_only(one_ctx)));
      (void)(driver_pipeline_dep_ctx_set_asm_entry_module_only(one_ctx, 1));
    }
    (void)(driver_x_pipeline_skip_typeck_set(1));
    (void)(driver_x_pipeline_skip_codegen_set(1));
    int32_t ec = xlang_pipeline_run_x_pipeline_large_stack(dep_mod, dep_arena, src, len, dep_out, one_ctx);
    (void)(driver_x_pipeline_skip_codegen_set(0));
    (void)(driver_x_pipeline_skip_typeck_set(0));
    if ((one_ctx !=0)) {
      (void)(driver_pipeline_dep_ctx_set_asm_entry_module_only(one_ctx, saved_entry_only));
    }
    if ((saved !=0)) {
      (void)(driver_check_only_set(1));
    } else {
      (void)(driver_check_only_set(0));
    }
    return ec;
  }
  return -1;
}
int32_t xlang_pipeline_dep_prerun_parse_skip_typeck(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx) {
  if ((dep_mod ==0)) {
    return -1;
  }
  if ((dep_arena ==0)) {
    return -1;
  }
  if ((src ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  return xlang_pipeline_dep_prerun_parse_skip_typeck_impl(dep_mod, dep_arena, src, len, dep_out, one_ctx);
  return -1;
}
int32_t xlang_pipeline_dep_prerun_parse_only_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len) {
  if ((dep_mod ==0)) {
    return -1;
  }
  if ((dep_arena ==0)) {
    return -1;
  }
  if ((src ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  int64_t imax = 2147483647;
  if ((len > imax)) {
    return -1;
  }
  {
    int32_t len_i32 = ((int32_t)(len));
    (void)(parser_parse_into_init(dep_mod, dep_arena));
    int32_t parse_rc = pipeline_parse_set_main_from_buf_c(dep_mod, dep_arena, src, len_i32);
    if ((parse_rc ==0)) {
      return 0;
    }
    return -1;
  }
  return -1;
}
int32_t xlang_pipeline_dep_prerun_parse_only(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len) {
  if ((dep_mod ==0)) {
    return -1;
  }
  if ((dep_arena ==0)) {
    return -1;
  }
  if ((src ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  return xlang_pipeline_dep_prerun_parse_only_impl(dep_mod, dep_arena, src, len);
  return -1;
}
int32_t xlang_pipeline_dep_prerun_typeck_only_impl(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx) {
  if ((dep_mod ==0)) {
    return -1;
  }
  if ((dep_arena ==0)) {
    return -1;
  }
  if ((src ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  if ((one_ctx ==0)) {
    return -1;
  }
  int64_t imax = 2147483647;
  if ((len > imax)) {
    return -1;
  }
  {
    int32_t len_i32 = ((int32_t)(len));
    int32_t parse_rc = pipeline_parse_set_main_from_buf_c(dep_mod, dep_arena, src, len_i32);
    if ((parse_rc !=0)) {
      return -2;
    }
    int32_t load_rc = pipeline_load_and_sync_direct_import_deps_c(dep_mod, dep_arena, one_ctx);
    if ((load_rc !=0)) {
      return load_rc;
    }
    int32_t tc_rc = pipeline_typeck_dep_prerun_module_c(dep_mod, dep_arena, one_ctx);
    return tc_rc;
  }
  return -1;
}
int32_t pipeline_typeck_dep_prerun_module_c(uint8_t * module, uint8_t * arena, uint8_t * ctx) {
  if ((module ==0)) {
    return -5;
  }
  if ((arena ==0)) {
    return -5;
  }
  if ((ctx ==0)) {
    return -5;
  }
  int32_t tc = 0;
  (void)(pipeline_typeck_set_dep_ctx(ctx));
  (void)(pipeline_typeck_diag_soft_suppress_set(1));
  (void)((tc = typeck_x_ast_library(module, arena, ctx)));
  (void)(pipeline_typeck_diag_soft_suppress_set(0));
  if ((tc ==0)) {
    return 0;
  }
  int32_t vrc = 0;
  (void)((vrc = pipeline_typeck_validate_struct_layouts_zero_padding_c(module, arena)));
  if ((vrc !=0)) {
    return -7;
  }
  (void)(pipeline_typeck_patch_all_body_parent_links_c(module, arena));
  return 0;
}
int32_t pipeline_typeck_validate_struct_layouts_zero_padding_c(uint8_t * module, uint8_t * arena) {
  if ((module ==0)) {
    return -1;
  }
  if ((arena ==0)) {
    return -1;
  }
  int32_t rc = 0;
  (void)((rc = typeck_validate_struct_layouts_zero_padding(module, arena)));
  return rc;
}
void pipeline_typeck_patch_all_body_parent_links_c(uint8_t * module, uint8_t * arena) {
  if ((module ==0)) {
    return;
  }
  if ((arena ==0)) {
    return;
  }
  (void)(typeck_patch_all_body_parent_links(module, arena));
}
void pipeline_bind_import_dep_buffers(uint8_t * ctx, int32_t import_idx) {
  if ((ctx ==0)) {
    return;
  }
  if ((import_idx < 0)) {
    return;
  }
  {
    uint8_t * a = driver_dep_arena_buf(import_idx);
    uint8_t * m = driver_dep_module_buf(import_idx);
    (void)(ast_pipeline_dep_ctx_set_arena(ctx, import_idx, a));
    (void)(ast_pipeline_dep_ctx_set_module(ctx, import_idx, m));
  }
}
int32_t pipeline_sync_one_dep_slot(uint8_t * module, uint8_t * ctx, int32_t dep_i) {
  if ((module ==0)) {
    return -1;
  }
  if ((ctx ==0)) {
    return -1;
  }
  if ((dep_i < 0)) {
    return -1;
  }
  uint8_t sync_path[128] = {};
  {
    (void)(memset(&((sync_path)[0]), 0, 64));
    int32_t _pl = parser_copy_module_import_path64(module, dep_i, &((sync_path)[0]));
  }
  int32_t sync_slot = 0;
  (void)((sync_slot = driver_dep_slot_for_path(&((sync_path)[0]))));
  if ((sync_slot < 0)) {
    (void)((sync_slot = dep_i));
  }
  int32_t pl = 0;
  while ((pl < 64)) {
    uint8_t b = 0;
    (void)((b = (sync_path)[pl]));
    if ((b ==0)) {
      break;
    }
    (void)((pl = (pl + 1)));
  }
  if ((pl > 0)) {
    (void)(ast_pipeline_dep_ctx_set_import_path(ctx, dep_i, &((sync_path)[0]), pl));
  }
  {
    uint8_t * m = driver_dep_module_buf(sync_slot);
    uint8_t * a = driver_dep_arena_buf(sync_slot);
    (void)(ast_pipeline_dep_ctx_set_module(ctx, dep_i, m));
    (void)(ast_pipeline_dep_ctx_set_arena(ctx, dep_i, a));
  }
  return 0;
}
int32_t pipeline_sync_dep_slots_from_driver_c(uint8_t * module, uint8_t * ctx) {
  if ((module ==0)) {
    return -1;
  }
  if ((ctx ==0)) {
    return -1;
  }
  int32_t dep_sync_nd = 0;
  int32_t n_entry_imports = 0;
  (void)((dep_sync_nd = ast_pipeline_dep_ctx_ndep(ctx)));
  (void)((n_entry_imports = parser_get_module_num_imports(module)));
  if ((n_entry_imports >=0)) {
    if ((n_entry_imports < dep_sync_nd)) {
      return 0;
    }
  }
  int32_t dep_sync_i = 0;
  while ((dep_sync_i < dep_sync_nd)) {
    int32_t sync_rc = 0;
    (void)((sync_rc = pipeline_sync_one_dep_slot(module, ctx, dep_sync_i)));
    if ((sync_rc !=0)) {
      return sync_rc;
    }
    (void)((dep_sync_i = (dep_sync_i + 1)));
  }
  return 0;
}
int32_t pipeline_load_import_from_disk_c(uint8_t * module, uint8_t * arena, uint8_t * ctx, int32_t import_idx) {
  if ((module ==0)) {
    return -1;
  }
  if ((arena ==0)) {
    return -1;
  }
  if ((ctx ==0)) {
    return -1;
  }
  if ((import_idx < 0)) {
    return -1;
  }
  uint8_t path_buf[128] = {};
  int32_t path_len = 0;
  (void)(memset(&((path_buf)[0]), 0, 64));
  (void)((path_len = parser_copy_module_import_path64(module, import_idx, &((path_buf)[0]))));
  int32_t rr = 0;
  (void)((rr = pipeline_resolve_path_x(ctx, &((path_buf)[0]), path_len)));
  if ((rr !=0)) {
    return -7;
  }
  (void)((rr = pipeline_read_file_x(ctx)));
  if ((rr !=0)) {
    return -8;
  }
  (void)((rr = pipeline_preprocess_loaded_into_ctx(ctx)));
  if ((rr !=0)) {
    return -9;
  }
  if ((path_len > 0)) {
    (void)(ast_pipeline_dep_ctx_set_import_path(ctx, import_idx, &((path_buf)[0]), path_len));
  }
  (void)(pipeline_bind_import_dep_buffers(ctx, import_idx));
  uint8_t * dep_arena = 0;
  uint8_t * dep_module = 0;
  uint8_t * prep_buf = 0;
  int32_t prep_len = 0;
  (void)((dep_arena = pipeline_dep_ctx_arena_at(ctx, import_idx)));
  (void)((dep_module = ast_pipeline_dep_ctx_module_at(ctx, import_idx)));
  (void)((prep_buf = pipeline_dep_ctx_preprocess_buf_ptr(ctx)));
  (void)((prep_len = pipeline_dep_ctx_preprocess_len_get(ctx)));
  (void)((rr = pipeline_parse_into_buf(dep_arena, dep_module, prep_buf, prep_len)));
  if ((rr !=0)) {
    return -10;
  }
  return 0;
}
int32_t pipeline_try_bind_seeded_import(uint8_t * ctx, int32_t import_idx, int32_t global_slot) {
  if ((ctx ==0)) {
    return 0;
  }
  if ((import_idx < 0)) {
    return 0;
  }
  if ((global_slot >=0)) {
    if ((driver_dep_seeded_get(global_slot) !=0)) {
      {
        uint8_t * a = driver_dep_arena_buf(global_slot);
        uint8_t * m = driver_dep_module_buf(global_slot);
        (void)(ast_pipeline_dep_ctx_set_arena(ctx, import_idx, a));
        (void)(ast_pipeline_dep_ctx_set_module(ctx, import_idx, m));
      }
      return 1;
    }
  }
  if ((driver_dep_seeded_get(import_idx) !=0)) {
    {
      uint8_t * a2 = driver_dep_arena_buf(import_idx);
      uint8_t * m2 = driver_dep_module_buf(import_idx);
      (void)(ast_pipeline_dep_ctx_set_arena(ctx, import_idx, a2));
      (void)(ast_pipeline_dep_ctx_set_module(ctx, import_idx, m2));
    }
    return 1;
  }
  return 0;
}
void pipeline_dep_ctx_realign_ndep_for_entry_c(uint8_t * module, uint8_t * ctx) {
  if ((module ==0)) {
    return;
  }
  if ((ctx ==0)) {
    return;
  }
  int32_t n_imp = 0;
  int32_t ndep = 0;
  (void)((n_imp = parser_get_module_num_imports(module)));
  (void)((ndep = ast_pipeline_dep_ctx_ndep(ctx)));
  if ((ndep ==n_imp)) {
    return;
  }
  if ((ndep > n_imp)) {
    return;
  }
  (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
}
int32_t pipeline_load_and_sync_direct_import_deps_c(uint8_t * module, uint8_t * arena, uint8_t * ctx) {
  if ((module ==0)) {
    return -1;
  }
  if ((arena ==0)) {
    return -1;
  }
  if ((ctx ==0)) {
    return -1;
  }
  int32_t n_imports = 0;
  (void)((n_imports = parser_get_module_num_imports(module)));
  (void)(pipeline_dep_ctx_realign_ndep_for_entry_c(module, ctx));
  int32_t ndep0 = 0;
  (void)((ndep0 = ast_pipeline_dep_ctx_ndep(ctx)));
  uint8_t path_buf[128] = {};
  int32_t i = 0;
  int32_t rc = 0;
  if ((ndep0 ==0)) {
    if ((n_imports > 0)) {
      (void)((i = 0));
      while ((i < n_imports)) {
        {
          (void)(memset(&((path_buf)[0]), 0, 64));
          int32_t _pl0 = parser_copy_module_import_path64(module, i, &((path_buf)[0]));
        }
        int32_t pl = 0;
        while ((pl < 64)) {
          uint8_t b = 0;
          (void)((b = (path_buf)[pl]));
          if ((b ==0)) {
            break;
          }
          (void)((pl = (pl + 1)));
        }
        if ((pl > 0)) {
          (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, &((path_buf)[0]), pl));
        }
        int32_t gs = 0;
        (void)((gs = driver_dep_slot_for_path(&((path_buf)[0]))));
        int32_t bound = 0;
        (void)((bound = pipeline_try_bind_seeded_import(ctx, i, gs)));
        if ((bound ==0)) {
          (void)((rc = pipeline_load_import_from_disk_c(module, arena, ctx, i)));
          if ((rc !=0)) {
            return rc;
          }
        }
        (void)((i = (i + 1)));
      }
      (void)(ast_pipeline_dep_ctx_set_ndep(ctx, n_imports));
    }
  } else {
    if ((n_imports > 0)) {
      int32_t cur_ndep = ndep0;
      if ((cur_ndep > n_imports)) {
        (void)((i = 0));
        while ((i < cur_ndep)) {
          int32_t seeded = 0;
          (void)((seeded = driver_dep_seeded_get(i)));
          if ((seeded !=0)) {
            {
              uint8_t * m = driver_dep_module_buf(i);
              uint8_t * a = driver_dep_arena_buf(i);
              (void)(ast_pipeline_dep_ctx_set_module(ctx, i, m));
              (void)(ast_pipeline_dep_ctx_set_arena(ctx, i, a));
              uint8_t * reg_path = driver_dep_path_registry_at(i);
              if ((reg_path !=0)) {
                int32_t rpl = pipe_cstr_len(reg_path);
                if ((rpl > 63)) {
                  (void)((rpl = 63));
                }
                if ((rpl > 0)) {
                  (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, reg_path, rpl));
                }
              }
            }
          }
          (void)((i = (i + 1)));
        }
      } else {
        (void)((i = 0));
        while ((i < n_imports)) {
          {
            (void)(memset(&((path_buf)[0]), 0, 64));
            int32_t _pl1 = parser_copy_module_import_path64(module, i, &((path_buf)[0]));
          }
          int32_t pl2 = 0;
          while ((pl2 < 64)) {
            uint8_t b2 = 0;
            (void)((b2 = (path_buf)[pl2]));
            if ((b2 ==0)) {
              break;
            }
            (void)((pl2 = (pl2 + 1)));
          }
          if ((pl2 > 0)) {
            (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, &((path_buf)[0]), pl2));
          }
          int32_t gs2 = 0;
          (void)((gs2 = driver_dep_slot_for_path(&((path_buf)[0]))));
          int32_t bound2 = 0;
          (void)((bound2 = pipeline_try_bind_seeded_import(ctx, i, gs2)));
          if ((bound2 ==0)) {
            uint8_t * cur_m = 0;
            (void)((cur_m = ast_pipeline_dep_ctx_module_at(ctx, i)));
            if ((cur_m ==0)) {
              (void)((rc = pipeline_load_import_from_disk_c(module, arena, ctx, i)));
              if ((rc !=0)) {
                return rc;
              }
            }
          }
          (void)((i = (i + 1)));
        }
        int32_t nd_now = 0;
        (void)((nd_now = ast_pipeline_dep_ctx_ndep(ctx)));
        if ((nd_now < n_imports)) {
          (void)(ast_pipeline_dep_ctx_set_ndep(ctx, n_imports));
        }
      }
    }
  }
  int32_t sync_rc = 0;
  (void)((sync_rc = pipeline_sync_dep_slots_from_driver_c(module, ctx)));
  if ((sync_rc !=0)) {
    return sync_rc;
  }
  int32_t all_seeded = 0;
  if ((n_imports > 0)) {
    (void)((all_seeded = 1));
  }
  (void)((i = 0));
  while ((i < n_imports)) {
    {
      (void)(memset(&((path_buf)[0]), 0, 64));
      int32_t _pl2 = parser_copy_module_import_path64(module, i, &((path_buf)[0]));
    }
    int32_t gs3 = 0;
    (void)((gs3 = driver_dep_slot_for_path(&((path_buf)[0]))));
    int32_t seed_gs = 0;
    int32_t seed_i = 0;
    if ((gs3 >=0)) {
      (void)((seed_gs = driver_dep_seeded_get(gs3)));
    }
    (void)((seed_i = driver_dep_seeded_get(i)));
    if ((gs3 < 0)) {
      if ((seed_i ==0)) {
        (void)((all_seeded = 0));
        break;
      }
    } else {
      if ((seed_gs ==0)) {
        if ((seed_i ==0)) {
          (void)((all_seeded = 0));
          break;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  if ((all_seeded ==0)) {
    (void)(typeck_merge_dep_struct_layouts_into_entry(module, arena, ctx));
    (void)(typeck_wpo_unify_soa_layouts(module, ctx));
  }
  return 0;
}
int32_t xlang_pipeline_dep_prerun_typeck_only(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx) {
  if ((dep_mod ==0)) {
    return -1;
  }
  if ((dep_arena ==0)) {
    return -1;
  }
  if ((src ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  if ((one_ctx ==0)) {
    return -1;
  }
  return xlang_pipeline_dep_prerun_typeck_only_impl(dep_mod, dep_arena, src, len, dep_out, one_ctx);
  return -1;
}
int32_t xlang_pipeline_dep_prerun_for_asm_module_o(uint8_t * dep_mod, uint8_t * dep_arena, uint8_t * src, int64_t len, uint8_t * dep_out, uint8_t * one_ctx) {
  return xlang_pipeline_dep_prerun_typeck_only(dep_mod, dep_arena, src, len, dep_out, one_ctx);
}
int32_t pipe_path_readable(uint8_t * path) {
  if ((path ==0)) {
    return 0;
  }
  if ((access(path, 4) ==0)) {
    return 1;
  }
  return 0;
}
int32_t pipe_cstr_has_char(uint8_t * s, uint8_t ch) {
  if ((s ==0)) {
    return 0;
  }
  int32_t i = 0;
  while ((i < 4096)) {
    if (((s)[i] ==0)) {
      return 0;
    }
    if (((s)[i] ==ch)) {
      return 1;
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
void pipe_write_nested_name_x(uint8_t * dst, int32_t cap, uint8_t * root, uint8_t * name) {
  if ((dst ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  int32_t off = 0;
  if ((root !=0)) {
    int32_t i = 0;
    while ((i < 4096)) {
      if (((root)[i] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (root)[i]));
      (void)((off = (off + 1)));
      (void)((i = (i + 1)));
    }
  }
  if (((off + 1) < cap)) {
    (void)(((dst)[off] = 47));
    (void)((off = (off + 1)));
  }
  if ((name !=0)) {
    int32_t j = 0;
    while ((j < 4096)) {
      if (((name)[j] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (name)[j]));
      (void)((off = (off + 1)));
      (void)((j = (j + 1)));
    }
  }
  if (((off + 1) < cap)) {
    (void)(((dst)[off] = 47));
    (void)((off = (off + 1)));
  }
  if ((name !=0)) {
    int32_t k = 0;
    while ((k < 4096)) {
      if (((name)[k] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (name)[k]));
      (void)((off = (off + 1)));
      (void)((k = (k + 1)));
    }
  }
  if (((off + 2) < cap)) {
    (void)(((dst)[off] = 46));
    (void)(((dst)[(off + 1)] = 120));
    (void)(((dst)[(off + 2)] = 0));
  } else {
    if ((off < cap)) {
      (void)(((dst)[off] = 0));
    } else {
      (void)(((dst)[(cap - 1)] = 0));
    }
  }
}
int32_t pipe_write_root_dotted_imp(uint8_t * dst, int32_t cap, uint8_t * root, uint8_t * imp) {
  if ((dst ==0)) {
    return 0;
  }
  if ((cap <=0)) {
    return 0;
  }
  int32_t off = 0;
  if ((root !=0)) {
    int32_t i = 0;
    while ((i < 4096)) {
      if (((root)[i] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      (void)(((dst)[off] = (root)[i]));
      (void)((off = (off + 1)));
      (void)((i = (i + 1)));
    }
  }
  if (((off + 1) < cap)) {
    (void)(((dst)[off] = 47));
    (void)((off = (off + 1)));
  }
  if ((imp !=0)) {
    int32_t j = 0;
    while ((j < 4096)) {
      if (((imp)[j] ==0)) {
        break;
      }
      if (((off + 1) >=cap)) {
        break;
      }
      uint8_t ch = (imp)[j];
      if ((ch ==46)) {
        (void)(((dst)[off] = 47));
      } else {
        (void)(((dst)[off] = ch));
      }
      (void)((off = (off + 1)));
      (void)((j = (j + 1)));
    }
  }
  if ((off < cap)) {
    (void)(((dst)[off] = 0));
  } else {
    (void)(((dst)[(cap - 1)] = 0));
  }
  return off;
}
void pipe_append_suffix(uint8_t * dst, int32_t cap, int32_t off, uint8_t * suf) {
  if ((dst ==0)) {
    return;
  }
  if ((suf ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  int32_t o = off;
  int32_t si = 0;
  while ((si < 16)) {
    if (((suf)[si] ==0)) {
      break;
    }
    if (((o + 1) >=cap)) {
      break;
    }
    (void)(((dst)[o] = (suf)[si]));
    (void)((o = (o + 1)));
    (void)((si = (si + 1)));
  }
  if ((o < cap)) {
    (void)(((dst)[o] = 0));
  } else {
    (void)(((dst)[(cap - 1)] = 0));
  }
}
uint8_t * xlang_cstr_offset(uint8_t * s, int32_t off) {
  if ((s ==0)) {
    return ((uint8_t *)(0));
  }
  if ((off < 0)) {
    return s;
  }
  return &((s)[off]);
  return s;
}
uint8_t * pipe_dir_tail(uint8_t * entry_dir) {
  if ((entry_dir ==0)) {
    return ((uint8_t *)(0));
  }
  int32_t last = -1;
  int32_t i = 0;
  while ((i < 4096)) {
    if (((entry_dir)[i] ==0)) {
      break;
    }
    if (((entry_dir)[i] ==47)) {
      (void)((last = i));
    }
    (void)((i = (i + 1)));
  }
  if ((last < 0)) {
    return entry_dir;
  }
  return xlang_cstr_offset(entry_dir, (last + 1));
  return entry_dir;
}
uint8_t * pipe_strip_prefix_seg(uint8_t * import_path, uint8_t * dir_tail) {
  if ((import_path ==0)) {
    return import_path;
  }
  if ((dir_tail ==0)) {
    return import_path;
  }
  {
    int32_t tl = pipe_cstr_len(dir_tail);
    int32_t i = 0;
    while ((i < tl)) {
      if (((import_path)[i] ==0)) {
        return import_path;
      }
      if (((import_path)[i] !=(dir_tail)[i])) {
        return import_path;
      }
      (void)((i = (i + 1)));
    }
    if (((import_path)[tl] ==46)) {
      return xlang_cstr_offset(import_path, (tl + 1));
    }
  }
  return import_path;
}
void xlang_resolve_import_file_path_multi(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_path, uint8_t * path, int64_t path_size) {
  if ((path ==0)) {
    return;
  }
  if ((path_size ==0)) {
    return;
  }
  if ((import_path ==0)) {
    (void)(((path)[0] = 0));
    return;
  }
  int32_t cap = ((int32_t)(path_size));
  if ((cap <=0)) {
    return;
  }
  if ((xlang_import_path_is_file_path(import_path) !=0)) {
    (void)(xlang_resolve_file_import_path(entry_dir, import_path, path, path_size));
    if ((pipe_path_readable(path) !=0)) {
      return;
    }
    if (((import_path)[0] !=47)) {
      (void)(pipe_cstr_copy(path, cap, import_path));
      if ((pipe_path_readable(path) !=0)) {
        return;
      }
    }
  }
  int32_t r = 0;
  while ((r < n_lib_roots)) {
    uint8_t * lib_root = 0;
    if ((lib_roots !=0)) {
      (void)((lib_root = pipe_load_ptr_slot(lib_roots, r)));
    }
    uint8_t * use_root = lib_root;
    uint8_t dot[2] = {};
    (void)(((dot)[0] = 46));
    (void)(((dot)[1] = 0));
    if ((use_root ==0)) {
      (void)((use_root = &((dot)[0])));
    } else {
      if (((use_root)[0] ==0)) {
        (void)((use_root = &((dot)[0])));
      }
    }
    (void)(xlang_import_path_to_file_path(use_root, import_path, path, path_size));
    if ((pipe_path_readable(path) !=0)) {
      return;
    }
    if ((pipe_cstr_has_char(import_path, 46) ==0)) {
      if ((path_size >=16)) {
        int32_t n = pipe_cstr_len(import_path);
        if ((n > 0)) {
          if ((n < 64)) {
            (void)(pipe_write_nested_name_x(path, cap, use_root, import_path));
            if ((pipe_path_readable(path) !=0)) {
              return;
            }
          }
        }
      }
    } else {
      if ((path_size >=16)) {
        int32_t off = pipe_write_root_dotted_imp(path, cap, use_root, import_path);
        uint8_t modx[8] = {};
        (void)(((modx)[0] = 47));
        (void)(((modx)[1] = 109));
        (void)(((modx)[2] = 111));
        (void)(((modx)[3] = 100));
        (void)(((modx)[4] = 46));
        (void)(((modx)[5] = 120));
        (void)(((modx)[6] = 0));
        if (((off + 8) <=cap)) {
          (void)(pipe_append_suffix(path, cap, off, &((modx)[0])));
          if ((pipe_path_readable(path) !=0)) {
            return;
          }
        }
        (void)(xlang_import_path_to_file_path(use_root, import_path, path, path_size));
        if ((pipe_path_readable(path) !=0)) {
          return;
        }
      }
    }
    (void)((r = (r + 1)));
  }
  if ((entry_dir !=0)) {
    if (((entry_dir)[0] !=0)) {
      if ((pipe_cstr_has_char(import_path, 46) ==0)) {
        int32_t off2 = pipe_write_root_dotted_imp(path, cap, entry_dir, import_path);
        uint8_t dx[4] = {};
        (void)(((dx)[0] = 46));
        (void)(((dx)[1] = 120));
        (void)(((dx)[2] = 0));
        (void)(pipe_append_suffix(path, cap, off2, &((dx)[0])));
        if ((pipe_path_readable(path) !=0)) {
          return;
        }
      } else {
        if ((path_size >=16)) {
          uint8_t * tail = pipe_dir_tail(entry_dir);
          uint8_t * eff = pipe_strip_prefix_seg(import_path, tail);
          int32_t off3 = pipe_write_root_dotted_imp(path, cap, entry_dir, eff);
          uint8_t dx2[4] = {};
          (void)(((dx2)[0] = 46));
          (void)(((dx2)[1] = 120));
          (void)(((dx2)[2] = 0));
          if (((off3 + 3) <=cap)) {
            (void)(pipe_append_suffix(path, cap, off3, &((dx2)[0])));
            if ((pipe_path_readable(path) !=0)) {
              return;
            }
          }
          uint8_t modx2[8] = {};
          (void)(((modx2)[0] = 47));
          (void)(((modx2)[1] = 109));
          (void)(((modx2)[2] = 111));
          (void)(((modx2)[3] = 100));
          (void)(((modx2)[4] = 46));
          (void)(((modx2)[5] = 120));
          (void)(((modx2)[6] = 0));
          if (((off3 + 8) <=cap)) {
            (void)(pipe_append_suffix(path, cap, off3, &((modx2)[0])));
            if ((pipe_path_readable(path) !=0)) {
              return;
            }
          }
        }
      }
    }
  }
}
int32_t pipe_pctx_off_entry_dir_buf(void) {
  return 4;
}
int32_t pipe_pctx_off_entry_dir_len(void) {
  return 516;
}
int32_t pipe_pctx_off_num_lib_roots(void) {
  return 520;
}
int32_t pipe_pctx_off_loaded_len(void) {
  return 4195344;
}
int32_t pipe_pctx_off_preprocess_len(void) {
  return 8389656;
}
void pipe_store_i32_le(uint8_t * base, int32_t off, int32_t v) {
  if ((base ==0)) {
    return;
  }
  if ((off < 0)) {
    return;
  }
  {
    uint32_t u = ((uint32_t)(v));
    (void)(((base)[off] = ((uint8_t)((u & 255)))));
    (void)(((base)[(off + 1)] = ((uint8_t)(((u / 256) & 255)))));
    (void)(((base)[(off + 2)] = ((uint8_t)(((u / 65536) & 255)))));
    (void)(((base)[(off + 3)] = ((uint8_t)(((u / 16777216) & 255)))));
  }
}
int32_t pipe_load_i32_le(uint8_t * base, int32_t off) {
  if ((base ==0)) {
    return 0;
  }
  if ((off < 0)) {
    return 0;
  }
  uint32_t b0 = 0;
  uint32_t b1 = 0;
  uint32_t b2 = 0;
  uint32_t b3 = 0;
  (void)((b0 = ((uint32_t)((base)[off]))));
  (void)((b1 = ((uint32_t)((base)[(off + 1)]))));
  (void)((b2 = ((uint32_t)((base)[(off + 2)]))));
  (void)((b3 = ((uint32_t)((base)[(off + 3)]))));
  uint32_t u = (((b0 + (b1 * 256)) + (b2 * 65536)) + (b3 * 16777216));
  return ((int32_t)(u));
}
void pipe_store_i64_zero(uint8_t * base, int32_t off) {
  if ((base ==0)) {
    return;
  }
  if ((off < 0)) {
    return;
  }
  (void)(pipe_store_i32_le(base, off, 0));
  (void)(pipe_store_i32_le(base, (off + 4), 0));
}
void pipeline_dep_ctx_path_bufs_reset(uint8_t * ctx) {
  if ((ctx ==0)) {
    return;
  }
  (void)(pipe_store_i64_zero(ctx, pipe_pctx_off_loaded_len()));
  (void)(pipe_store_i32_le(ctx, pipe_pctx_off_preprocess_len(), 0));
  (void)(pipe_store_i32_le(ctx, pipe_pctx_off_entry_dir_len(), 0));
  (void)(pipe_store_i32_le(ctx, pipe_pctx_off_num_lib_roots(), 0));
}
int32_t pipeline_resolve_path_x(uint8_t * ctx, uint8_t * import_path, int32_t path_len) {
  if ((ctx ==0)) {
    return -1;
  }
  if ((import_path ==0)) {
    return -1;
  }
  if ((path_len <=0)) {
    return -1;
  }
  int32_t lib_i = 0;
  while (1) {
    int32_t cont = 0;
    (void)((cont = pipeline_loop_should_continue_lib_root_c(ctx, lib_i)));
    if ((cont ==0)) {
      break;
    }
    int32_t try_rc = 0;
    (void)((try_rc = pipeline_resolve_path_try_one_lib_root(ctx, lib_i, import_path, path_len)));
    if ((try_rc ==0)) {
      return 0;
    }
    (void)((lib_i = (lib_i + 1)));
  }
  int32_t entry_rc = 0;
  (void)((entry_rc = pipeline_resolve_path_try_entry_dir(ctx, import_path, path_len)));
  if ((entry_rc ==0)) {
    return 0;
  }
  return -1;
}
int32_t pipeline_read_file_x(uint8_t * ctx) {
  if ((ctx ==0)) {
    return -1;
  }
  uint8_t * path = 0;
  uint8_t * buf = 0;
  (void)((path = pipeline_dep_ctx_path_buf_ptr(ctx)));
  (void)((buf = pipeline_dep_ctx_loaded_buf_ptr(ctx)));
  if ((path ==0)) {
    return -1;
  }
  if ((buf ==0)) {
    return -1;
  }
  int64_t cap = 4194304;
  int32_t n = 0;
  (void)((n = xlang_read_file_into_path(path, buf, cap)));
  if ((n < 0)) {
    return -1;
  }
  (void)(pipeline_dep_ctx_set_loaded_len(ctx, ((int64_t)(n))));
  return 0;
}
int32_t pipeline_preprocess_loaded_into_ctx(uint8_t * ctx) {
  if ((ctx ==0)) {
    return -1;
  }
  uint8_t * loaded = 0;
  uint8_t * prep = 0;
  (void)((loaded = pipeline_dep_ctx_loaded_buf_ptr(ctx)));
  (void)((prep = pipeline_dep_ctx_preprocess_buf_ptr(ctx)));
  if ((loaded ==0)) {
    return -1;
  }
  if ((prep ==0)) {
    return -1;
  }
  int64_t loaded_len = 0;
  (void)((loaded_len = xlang_size_slot_get(ctx, 524418)));
  int32_t out_cap = 4194304;
  int32_t out_len = 0;
  (void)((out_len = preprocess_x_buf(loaded, loaded_len, prep, out_cap)));
  if ((out_len < 0)) {
    return -9;
  }
  (void)(pipe_store_i32_le(ctx, pipe_pctx_off_preprocess_len(), out_len));
  return 0;
}
int32_t pipeline_parse_into_buf(uint8_t * arena, uint8_t * module, uint8_t * buf, int32_t buf_len) {
  if ((arena ==0)) {
    return -1;
  }
  if ((module ==0)) {
    return -1;
  }
  if ((buf ==0)) {
    return -1;
  }
  if ((buf_len <=0)) {
    return -1;
  }
  {
    (void)(parser_parse_into_init(module, arena));
    int32_t pr_ok = driver_parse_into_buf_rc(arena, module, buf, buf_len, 0);
    if ((pr_ok ==0)) {
      (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x70\x61\x72\x73\x65\x5f\x70\x6f\x73\x74"), module, arena));
      (void)(pipeline_module_fixup_with_arena_stmt_orders(module, arena));
      (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x70\x61\x72\x73\x65\x5f\x70\x6f\x73\x74\x5f\x66\x69\x78\x75\x70"), module, arena));
      return 0;
    }
    return -1;
  }
  return -1;
}
void pipeline_dep_ctx_copy_entry_dir(uint8_t * ctx, uint8_t * entry_dir) {
  if ((ctx ==0)) {
    return;
  }
  if ((entry_dir ==0)) {
    return;
  }
  int32_t el = 0;
  while ((el < 511)) {
    uint8_t c = (entry_dir)[el];
    if ((c ==0)) {
      break;
    }
    (void)((el = (el + 1)));
  }
  int32_t base_off = pipe_pctx_off_entry_dir_buf();
  int32_t k = 0;
  while ((k < el)) {
    (void)(((ctx)[(base_off + k)] = (entry_dir)[k]));
    (void)((k = (k + 1)));
  }
  (void)(((ctx)[(base_off + el)] = 0));
  (void)(pipe_store_i32_le(ctx, pipe_pctx_off_entry_dir_len(), el));
}
void pipeline_dep_ctx_set_use_asm_backend(uint8_t * ctx, int32_t v) {
  (void)(driver_pipeline_dep_ctx_set_use_asm(ctx, v));
}
void pipeline_typeck_diag_soft_suppress_set(int32_t v) {
  if ((v !=0)) {
    (void)((g_pipe_typeck_diag_soft_suppress = 1));
  } else {
    (void)((g_pipe_typeck_diag_soft_suppress = 0));
  }
}
int32_t pipeline_typeck_diag_soft_suppress_get(void) {
  if ((g_pipe_typeck_diag_soft_suppress !=0)) {
    return 1;
  }
  return 0;
}
void pipeline_typeck_set_dep_ctx(uint8_t * ctx) {
  (void)(xlang_ptr_slot_set(&((g_pipe_typeck_dep_ctx)[0]), 0, ctx));
}
uint8_t * pipeline_typeck_get_dep_ctx(void) {
  return xlang_ptr_slot_get(&((g_pipe_typeck_dep_ctx)[0]), 0);
}
void preprocess_define_reset(void) {
  (void)((g_pipe_pp_ndefines = 0));
}
void preprocess_define_add(uint8_t * name) {
  if ((name ==0)) {
    return;
  }
  if ((g_pipe_pp_ndefines >=128)) {
    return;
  }
  int32_t n = 0;
  while ((n < 64)) {
    if (((name)[n] ==0)) {
      break;
    }
    (void)((n = (n + 1)));
  }
  if ((n ==0)) {
    return;
  }
  if ((n >=64)) {
    return;
  }
  int32_t base = (g_pipe_pp_ndefines * 64);
  int32_t k = 0;
  while ((k < n)) {
    (void)(((g_pipe_pp_defines)[(base + k)] = (name)[k]));
    (void)((k = (k + 1)));
  }
  (void)(((g_pipe_pp_defines)[(base + n)] = 0));
  (void)((g_pipe_pp_ndefines = (g_pipe_pp_ndefines + 1)));
}
int32_t preprocess_define_has(uint8_t * sym, int32_t sym_len) {
  if ((sym ==0)) {
    return 0;
  }
  if ((sym_len <=0)) {
    return 0;
  }
  int32_t i = 0;
  while ((i < g_pipe_pp_ndefines)) {
    int32_t base = (i * 64);
    int32_t k = 0;
    int32_t ok = 1;
    while ((k < sym_len)) {
      {
        uint8_t tb = (g_pipe_pp_defines)[(base + k)];
        if ((tb !=(sym)[k])) {
          (void)((ok = 0));
          break;
        }
        if ((tb ==0)) {
          (void)((ok = 0));
          break;
        }
      }
      (void)((k = (k + 1)));
    }
    if ((ok !=0)) {
      if (((g_pipe_pp_defines)[(base + sym_len)] ==0)) {
        return 1;
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t preprocess_eval_condition_c(uint8_t * cond, int32_t cond_len) {
  if ((cond ==0)) {
    return 0;
  }
  if ((cond_len <=0)) {
    return 0;
  }
  uint8_t * base = cond;
  int32_t n = cond_len;
  while ((n > 0)) {
    uint8_t lead = 0;
    (void)((lead = (base)[0]));
    if ((lead !=32)) {
      if ((lead !=9)) {
        break;
      }
    }
    (void)((base = xlang_cstr_offset(base, 1)));
    (void)((n = (n - 1)));
  }
  while ((n > 0)) {
    uint8_t trail = 0;
    (void)((trail = (base)[(n - 1)]));
    if ((trail !=32)) {
      if ((trail !=9)) {
        break;
      }
    }
    (void)((n = (n - 1)));
  }
  if ((n <=0)) {
    return 0;
  }
  int32_t k = 0;
  int32_t complex = 0;
  while ((k < n)) {
    uint8_t c = 0;
    (void)((c = (base)[k]));
    if ((c ==32)) {
      (void)((complex = 1));
      break;
    }
    if ((c ==9)) {
      (void)((complex = 1));
      break;
    }
    if ((c ==61)) {
      (void)((complex = 1));
      break;
    }
    if ((c ==33)) {
      (void)((complex = 1));
      break;
    }
    if ((c ==40)) {
      (void)((complex = 1));
      break;
    }
    if ((c ==41)) {
      (void)((complex = 1));
      break;
    }
    (void)((k = (k + 1)));
  }
  if ((complex !=0)) {
    int32_t er = 0;
    (void)((er = cfg_eval_expr_c(base, n)));
    if ((er !=0)) {
      return 1;
    }
    return 0;
  }
  /* 9.3.3: bare decimal literal — nonzero true, "0" false (mirror of .x
   * authority; digit tokens never exist in the -D table). */
  k = 0;
  int32_t all_digits = 1;
  int32_t lit_true = 0;
  while ((k < n)) {
    uint8_t d = 0;
    (void)((d = (base)[k]));
    if ((d < 48)) {
      (void)((all_digits = 0));
      break;
    }
    if ((d > 57)) {
      (void)((all_digits = 0));
      break;
    }
    if ((d != 48)) {
      (void)((lit_true = 1));
    }
    (void)((k = (k + 1)));
  }
  if ((all_digits != 0)) {
    return lit_true;
  }
  return preprocess_define_has(base, n);
}
void preprocess_if_stack_reset(void) {
  (void)((g_pipe_pp_if_n = 0));
}
int32_t preprocess_if_stack_len(void) {
  return g_pipe_pp_if_n;
}
int32_t preprocess_if_stack_push(int32_t v) {
  if ((g_pipe_pp_if_n >=32)) {
    return -1;
  }
  {
    int32_t * p = &((g_pipe_pp_if_stack)[g_pipe_pp_if_n]);
    (void)(((p)[0] = v));
  }
  (void)((g_pipe_pp_if_n = (g_pipe_pp_if_n + 1)));
  return 0;
}
void preprocess_if_stack_pop(void) {
  if ((g_pipe_pp_if_n > 0)) {
    (void)((g_pipe_pp_if_n = (g_pipe_pp_if_n - 1)));
  }
}
int32_t preprocess_if_stack_at(int32_t i) {
  if ((i < 0)) {
    return 0;
  }
  if ((i >=g_pipe_pp_if_n)) {
    return 0;
  }
  {
    int32_t * p = &((g_pipe_pp_if_stack)[i]);
    return (p)[0];
  }
  return 0;
}
void preprocess_if_stack_set_at(int32_t i, int32_t v) {
  if ((i < 0)) {
    return;
  }
  if ((i >=g_pipe_pp_if_n)) {
    return;
  }
  {
    int32_t * p = &((g_pipe_pp_if_stack)[i]);
    (void)(((p)[0] = v));
  }
}
int32_t * typeck_ndep_slot(void) {
  return &(g_pipe_typeck_ndep);
}
void typeck_ndep_store_impl(int32_t n) {
  (void)((g_pipe_typeck_ndep = n));
}
uint8_t * typeck_dep_module_get(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return xlang_ptr_slot_get(&((g_pipe_typeck_dep_module_ptrs)[0]), i);
}
uint8_t * typeck_dep_arena_get(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return xlang_ptr_slot_get(&((g_pipe_typeck_dep_arena_ptrs)[0]), i);
}
void typeck_dep_module_set_impl(int32_t i, uint8_t * mod) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_typeck_dep_module_ptrs)[0]), i, mod));
}
void typeck_dep_arena_set_impl(int32_t i, uint8_t * arena) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_typeck_dep_arena_ptrs)[0]), i, arena));
}
uint8_t * typeck_dep_module_ptrs_base(void) {
  return &((g_pipe_typeck_dep_module_ptrs)[0]);
}
uint8_t * xlang_cstr_typeck_lit(void) {
  return &((g_pipe_cstr_typeck_lit)[0]);
}
uint8_t * xlang_entry_lib_keyword_lit(int32_t k) {
  if ((k ==0)) {
    return &((g_pipe_entry_lib_kw0)[0]);
  }
  if ((k ==1)) {
    return &((g_pipe_entry_lib_kw1)[0]);
  }
  if ((k ==2)) {
    return &((g_pipe_entry_lib_kw2)[0]);
  }
  if ((k ==3)) {
    return &((g_pipe_entry_lib_kw3)[0]);
  }
  if ((k ==4)) {
    return &((g_pipe_entry_lib_kw4)[0]);
  }
  if ((k ==5)) {
    return &((g_pipe_entry_lib_kw5)[0]);
  }
  if ((k ==6)) {
    return &((g_pipe_entry_lib_kw6)[0]);
  }
  if ((k ==7)) {
    return &((g_pipe_entry_lib_kw7)[0]);
  }
  if ((k ==8)) {
    return &((g_pipe_entry_lib_kw8)[0]);
  }
  if ((k ==9)) {
    return &((g_pipe_entry_lib_kw9)[0]);
  }
  return &((g_pipe_cstr_typeck_lit)[0]);
}
uint8_t * xlang_entry_lib_name_from_path_impl(uint8_t * input_path) {
  if ((input_path ==0)) {
    return xlang_cstr_typeck_lit();
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw0)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(0);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw1)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(1);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw2)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(2);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw3)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(3);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw4)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(4);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw5)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(5);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw6)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(6);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw7)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(7);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw8)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(8);
  }
  if ((pipe_cstr_contains(input_path, &((g_pipe_entry_lib_kw9)[0])) !=0)) {
    return xlang_entry_lib_keyword_lit(9);
  }
  int32_t std_after = -1;
  int32_t si = 0;
  while ((si < 4096)) {
    if (((input_path)[si] ==0)) {
      break;
    }
    int32_t at_bound = 0;
    if ((si ==0)) {
      (void)((at_bound = 1));
    } else {
      if (((input_path)[(si - 1)] ==47)) {
        (void)((at_bound = 1));
      }
      if (((input_path)[(si - 1)] ==92)) {
        (void)((at_bound = 1));
      }
    }
    if ((at_bound !=0)) {
      if ((((((input_path)[si] ==115) && ((input_path)[(si + 1)] ==116)) && ((input_path)[(si + 2)] ==100)) && ((input_path)[(si + 3)] ==47))) {
        (void)((std_after = (si + 4)));
        break;
      }
    }
    (void)((si = (si + 1)));
  }
  if ((std_after >=0)) {
    (void)(((g_pipe_entry_lib_stem_buf)[0] = 115));
    (void)(((g_pipe_entry_lib_stem_buf)[1] = 116));
    (void)(((g_pipe_entry_lib_stem_buf)[2] = 100));
    (void)(((g_pipe_entry_lib_stem_buf)[3] = 95));
    int32_t off = 4;
    int32_t p = std_after;
    while ((((input_path)[p] !=0) && ((off + 2) < 128))) {
      int32_t seg_start = p;
      while (((((input_path)[p] !=0) && ((input_path)[p] !=47)) && ((input_path)[p] !=92))) {
        (void)((p = (p + 1)));
      }
      int32_t seg_len = (p - seg_start);
      if ((seg_len >=3)) {
        if (((((input_path)[((seg_start + seg_len) - 3)] ==46) && ((input_path)[((seg_start + seg_len) - 2)] ==115)) && ((input_path)[((seg_start + seg_len) - 1)] ==117))) {
          (void)((seg_len = (seg_len - 3)));
        }
      }
      if ((seg_len >=2)) {
        if ((((input_path)[((seg_start + seg_len) - 2)] ==46) && ((input_path)[((seg_start + seg_len) - 1)] ==120))) {
          (void)((seg_len = (seg_len - 2)));
        }
      }
      int32_t is_mod = 0;
      if ((seg_len ==3)) {
        if (((((input_path)[seg_start] ==109) && ((input_path)[(seg_start + 1)] ==111)) && ((input_path)[(seg_start + 2)] ==100))) {
          (void)((is_mod = 1));
        }
      }
      if (((is_mod ==0) && (seg_len > 0))) {
        if (((off > 4) && (((off + seg_len) + 1) < 128))) {
          (void)(((g_pipe_entry_lib_stem_buf)[off] = 95));
          (void)((off = (off + 1)));
        }
        if (((off + seg_len) < 128)) {
          int32_t k = 0;
          while ((k < seg_len)) {
            (void)(((g_pipe_entry_lib_stem_buf)[(off + k)] = (input_path)[(seg_start + k)]));
            (void)((k = (k + 1)));
          }
          (void)((off = (off + seg_len)));
        }
      }
      if (((input_path)[p] !=0)) {
        (void)((p = (p + 1)));
      }
    }
    if ((off > 4)) {
      (void)(((g_pipe_entry_lib_stem_buf)[off] = 0));
      return &((g_pipe_entry_lib_stem_buf)[0]);
    }
  }
  int32_t core_after = -1;
  int32_t ci = 0;
  while ((ci < 4096)) {
    if (((input_path)[ci] ==0)) {
      break;
    }
    int32_t at_bound2 = 0;
    if ((ci ==0)) {
      (void)((at_bound2 = 1));
    } else {
      if (((input_path)[(ci - 1)] ==47)) {
        (void)((at_bound2 = 1));
      }
      if (((input_path)[(ci - 1)] ==92)) {
        (void)((at_bound2 = 1));
      }
    }
    if ((at_bound2 !=0)) {
      if (((((((input_path)[ci] ==99) && ((input_path)[(ci + 1)] ==111)) && ((input_path)[(ci + 2)] ==114)) && ((input_path)[(ci + 3)] ==101)) && ((input_path)[(ci + 4)] ==47))) {
        (void)((core_after = (ci + 5)));
        break;
      }
    }
    (void)((ci = (ci + 1)));
  }
  if ((core_after >=0)) {
    (void)(((g_pipe_entry_lib_stem_buf)[0] = 99));
    (void)(((g_pipe_entry_lib_stem_buf)[1] = 111));
    (void)(((g_pipe_entry_lib_stem_buf)[2] = 114));
    (void)(((g_pipe_entry_lib_stem_buf)[3] = 101));
    (void)(((g_pipe_entry_lib_stem_buf)[4] = 95));
    int32_t off2 = 5;
    int32_t p2 = core_after;
    while ((((input_path)[p2] !=0) && ((off2 + 2) < 128))) {
      int32_t seg_start2 = p2;
      while (((((input_path)[p2] !=0) && ((input_path)[p2] !=47)) && ((input_path)[p2] !=92))) {
        (void)((p2 = (p2 + 1)));
      }
      int32_t seg_len2 = (p2 - seg_start2);
      if ((seg_len2 >=3)) {
        if (((((input_path)[((seg_start2 + seg_len2) - 3)] ==46) && ((input_path)[((seg_start2 + seg_len2) - 2)] ==115)) && ((input_path)[((seg_start2 + seg_len2) - 1)] ==117))) {
          (void)((seg_len2 = (seg_len2 - 3)));
        }
      }
      if ((seg_len2 >=2)) {
        if ((((input_path)[((seg_start2 + seg_len2) - 2)] ==46) && ((input_path)[((seg_start2 + seg_len2) - 1)] ==120))) {
          (void)((seg_len2 = (seg_len2 - 2)));
        }
      }
      int32_t is_mod2 = 0;
      if ((seg_len2 ==3)) {
        if (((((input_path)[seg_start2] ==109) && ((input_path)[(seg_start2 + 1)] ==111)) && ((input_path)[(seg_start2 + 2)] ==100))) {
          (void)((is_mod2 = 1));
        }
      }
      if (((is_mod2 ==0) && (seg_len2 > 0))) {
        if (((off2 > 5) && (((off2 + seg_len2) + 1) < 128))) {
          (void)(((g_pipe_entry_lib_stem_buf)[off2] = 95));
          (void)((off2 = (off2 + 1)));
        }
        if (((off2 + seg_len2) < 128)) {
          int32_t k2 = 0;
          while ((k2 < seg_len2)) {
            (void)(((g_pipe_entry_lib_stem_buf)[(off2 + k2)] = (input_path)[(seg_start2 + k2)]));
            (void)((k2 = (k2 + 1)));
          }
          (void)((off2 = (off2 + seg_len2)));
        }
      }
      if (((input_path)[p2] !=0)) {
        (void)((p2 = (p2 + 1)));
      }
    }
    if ((off2 > 5)) {
      (void)(((g_pipe_entry_lib_stem_buf)[off2] = 0));
      return &((g_pipe_entry_lib_stem_buf)[0]);
    }
  }
  int32_t last_slash = -1;
  int32_t bi = 0;
  while ((bi < 4096)) {
    if (((input_path)[bi] ==0)) {
      break;
    }
    if ((((input_path)[bi] ==47) || ((input_path)[bi] ==92))) {
      (void)((last_slash = bi));
    }
    (void)((bi = (bi + 1)));
  }
  int32_t base = 0;
  if ((last_slash >=0)) {
    (void)((base = (last_slash + 1)));
  }
  int32_t last_dot = -1;
  int32_t di = base;
  while ((di < 4096)) {
    if (((input_path)[di] ==0)) {
      break;
    }
    if (((input_path)[di] ==46)) {
      (void)((last_dot = di));
    }
    (void)((di = (di + 1)));
  }
  if ((last_dot > base)) {
    int32_t is_x = 0;
    if (((((input_path)[last_dot] ==46) && ((input_path)[(last_dot + 1)] ==120)) && ((input_path)[(last_dot + 2)] ==0))) {
      (void)((is_x = 1));
    }
    if ((((((input_path)[last_dot] ==46) && ((input_path)[(last_dot + 1)] ==115)) && ((input_path)[(last_dot + 2)] ==117)) && ((input_path)[(last_dot + 3)] ==0))) {
      (void)((is_x = 1));
    }
    if ((is_x !=0)) {
      int32_t stem_len = (last_dot - base);
      if (((stem_len > 0) && (stem_len < 128))) {
        int32_t k3 = 0;
        while ((k3 < stem_len)) {
          (void)(((g_pipe_entry_lib_stem_buf)[k3] = (input_path)[(base + k3)]));
          (void)((k3 = (k3 + 1)));
        }
        (void)(((g_pipe_entry_lib_stem_buf)[stem_len] = 0));
        return &((g_pipe_entry_lib_stem_buf)[0]);
      }
    }
  }
  return xlang_cstr_typeck_lit();
}
int32_t * pipeline_diag_emitted_flag_slot(void) {
  return &(g_pipe_diag_emitted_flag);
}
int32_t * driver_dep_seeded_slot(int32_t i) {
  int32_t idx = i;
  if ((idx < 0)) {
    (void)((idx = 0));
  }
  if ((idx >=32)) {
    (void)((idx = 31));
  }
  return &((g_pipe_driver_dep_seeded)[idx]);
}
void driver_dep_arena_ptr_set_impl(int32_t i, uint8_t * arena) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_driver_dep_arena)[0]), i, arena));
}
void driver_dep_module_ptr_set_impl(int32_t i, uint8_t * module) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_driver_dep_module)[0]), i, module));
}
void driver_dep_path_registry_set(int32_t i, uint8_t * path) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_driver_dep_path_registry)[0]), i, path));
}
uint8_t * driver_dep_path_registry_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return xlang_ptr_slot_get(&((g_pipe_driver_dep_path_registry)[0]), i);
}
size_t pipeline_sizeof_arena(void) {
  return ((size_t)(16));
}
size_t pipeline_sizeof_module(void) {
  return ((size_t)(68));
}
uint8_t * driver_dep_arena_buf(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  uint8_t * p = xlang_ptr_slot_get(&((g_pipe_driver_dep_arena)[0]), i);
  if ((p !=0)) {
    return p;
  }
  size_t sz = 0;
  (void)((sz = pipeline_sizeof_arena()));
  (void)((p = malloc(sz)));
  if ((p ==0)) {
    return ((uint8_t *)(0));
  }
  (void)(memset(p, 0, sz));
  (void)(xlang_ptr_slot_set(&((g_pipe_driver_dep_arena)[0]), i, p));
  return p;
}
uint8_t * driver_dep_module_buf(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  uint8_t * p = xlang_ptr_slot_get(&((g_pipe_driver_dep_module)[0]), i);
  if ((p !=0)) {
    return p;
  }
  size_t sz = 0;
  (void)((sz = pipeline_sizeof_module()));
  (void)((p = malloc(sz)));
  if ((p ==0)) {
    return ((uint8_t *)(0));
  }
  (void)(memset(p, 0, sz));
  (void)(xlang_ptr_slot_set(&((g_pipe_driver_dep_module)[0]), i, p));
  return p;
}
void pipeline_rf_stage_prep_clear(void) {
  uint8_t * p = xlang_ptr_slot_get(&((g_pipe_rf_stage_prep)[0]), 0);
  if ((p !=0)) {
    (void)(free(p));
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_rf_stage_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((g_pipe_rf_stage_prep_len)[0]), 0, 0));
}
void pipeline_rf_stage_prep_set(uint8_t * prep, int64_t prep_len) {
  (void)(xlang_ptr_slot_set(&((g_pipe_rf_stage_prep)[0]), 0, prep));
  if ((prep ==0)) {
    (void)(xlang_size_slot_set(&((g_pipe_rf_stage_prep_len)[0]), 0, 0));
    return;
  }
  (void)(xlang_size_slot_set(&((g_pipe_rf_stage_prep_len)[0]), 0, prep_len));
}
int32_t pipeline_rf_stage_prep_take(uint8_t * out_prep, uint8_t * out_len) {
  uint8_t * prep = xlang_ptr_slot_get(&((g_pipe_rf_stage_prep)[0]), 0);
  int64_t prep_len = xlang_size_slot_get(&((g_pipe_rf_stage_prep_len)[0]), 0);
  (void)(xlang_ptr_slot_set(&((g_pipe_rf_stage_prep)[0]), 0, 0));
  (void)(xlang_size_slot_set(&((g_pipe_rf_stage_prep_len)[0]), 0, 0));
  if ((out_prep !=0)) {
    (void)(xlang_ptr_slot_set(out_prep, 0, prep));
  }
  if ((out_len !=0)) {
    if ((prep ==0)) {
      (void)(xlang_size_slot_set(out_len, 0, 0));
    } else {
      (void)(xlang_size_slot_set(out_len, 0, prep_len));
    }
  }
  if ((prep ==0)) {
    return -1;
  }
  return 0;
}
int32_t pipeline_loaded_import_commit_from_owned(uint8_t * prep, int64_t prep_len) {
  if ((prep ==0)) {
    return -1;
  }
  uint8_t * buf = xlang_ptr_slot_get(&((g_pipe_loaded_import_buf)[0]), 0);
  int64_t cap = xlang_size_slot_get(&((g_pipe_loaded_import_cap)[0]), 0);
  if (((prep_len > cap) || (buf ==0))) {
    (void)(free(buf));
    int64_t floor_cap = 4194304;
    int64_t new_cap = floor_cap;
    if ((prep_len >=floor_cap)) {
      (void)((new_cap = (prep_len + 65536)));
    }
    (void)(xlang_size_slot_set(&((g_pipe_loaded_import_cap)[0]), 0, new_cap));
    uint8_t * fresh = 0;
    (void)((fresh = malloc(((size_t)(new_cap)))));
    if ((fresh ==0)) {
      (void)(xlang_ptr_slot_set(&((g_pipe_loaded_import_buf)[0]), 0, 0));
      (void)(free(prep));
      return -1;
    }
    (void)(xlang_ptr_slot_set(&((g_pipe_loaded_import_buf)[0]), 0, fresh));
    (void)((buf = fresh));
  }
  (void)(memcpy(buf, prep, ((size_t)(prep_len))));
  (void)(free(prep));
  (void)(xlang_size_slot_set(&((g_pipe_loaded_import_len)[0]), 0, prep_len));
  return 0;
}
uint8_t * pipeline_loaded_import_data(void) {
  return xlang_ptr_slot_get(&((g_pipe_loaded_import_buf)[0]), 0);
}
int64_t pipeline_loaded_import_len_get(void) {
  return xlang_size_slot_get(&((g_pipe_loaded_import_len)[0]), 0);
}
uint8_t * pipeline_resolved_path_buf_slot(void) {
  return &((g_pipe_resolved_path_buf)[0]);
}
void pipeline_dep_arena_slot_set(int32_t i, uint8_t * p) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_dep_arena_slots)[0]), i, p));
}
void pipeline_dep_module_slot_set(int32_t i, uint8_t * p) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_dep_module_slots)[0]), i, p));
}
uint8_t * pipeline_dep_arena_slot_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return xlang_ptr_slot_get(&((g_pipe_dep_arena_slots)[0]), i);
}
uint8_t * pipeline_dep_module_slot_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i >=32)) {
    return ((uint8_t *)(0));
  }
  return xlang_ptr_slot_get(&((g_pipe_dep_module_slots)[0]), i);
}
void pipeline_entry_dir_copy(uint8_t * path) {
  if ((path ==0)) {
    return;
  }
  int32_t i = 0;
  while ((i < 511)) {
    uint8_t c = (path)[i];
    (void)(((g_pipe_entry_dir_buf)[i] = c));
    if ((c ==0)) {
      (void)((g_pipe_entry_dir_is_dot = 0));
      return;
    }
    (void)((i = (i + 1)));
  }
  (void)(((g_pipe_entry_dir_buf)[511] = 0));
  (void)((g_pipe_entry_dir_is_dot = 0));
}
void pipeline_entry_dir_set_dot(void) {
  (void)((g_pipe_entry_dir_is_dot = 1));
  (void)(((g_pipe_entry_dir_dot)[0] = 46));
  (void)(((g_pipe_entry_dir_dot)[1] = 0));
}
uint8_t * pipeline_entry_dir_get(void) {
  if ((g_pipe_entry_dir_is_dot !=0)) {
    (void)(((g_pipe_entry_dir_dot)[0] = 46));
    (void)(((g_pipe_entry_dir_dot)[1] = 0));
    return &((g_pipe_entry_dir_dot)[0]);
  }
  return &((g_pipe_entry_dir_buf)[0]);
}
void pipeline_set_entry_dir(uint8_t * path) {
  if ((path ==0)) {
    (void)(pipeline_entry_dir_set_dot());
    return;
  }
  if (((path)[0] ==0)) {
    (void)(pipeline_entry_dir_set_dot());
    return;
  }
  (void)(pipeline_entry_dir_copy(path));
}
void pipeline_set_dep_slots(uint8_t * arenas, uint8_t * modules) {
  int32_t i = 0;
  while ((i < 32)) {
    {
      uint8_t * a = 0;
      uint8_t * m = 0;
      if ((arenas !=0)) {
        (void)((a = pipe_load_ptr_slot(arenas, i)));
      }
      if ((modules !=0)) {
        (void)((m = pipe_load_ptr_slot(modules, i)));
      }
      (void)(pipeline_dep_arena_slot_set(i, a));
      (void)(pipeline_dep_module_slot_set(i, m));
    }
    (void)((i = (i + 1)));
  }
}
void xlang_pipeline_fill_ctx_path_buffers(uint8_t * ctx, uint8_t * entry_dir, uint8_t * lib_roots, int32_t n_lib_roots) {
  if ((ctx ==0)) {
    return;
  }
  (void)(pipeline_dep_ctx_path_bufs_reset(ctx));
  if ((entry_dir !=0)) {
    (void)(pipeline_dep_ctx_copy_entry_dir(ctx, entry_dir));
  }
  if ((lib_roots ==0)) {
    return;
  }
  if ((n_lib_roots <=0)) {
    return;
  }
  int32_t i = 0;
  while ((i < n_lib_roots)) {
    {
      uint8_t * p = pipe_load_ptr_slot(lib_roots, i);
      if ((p !=0)) {
        int32_t ll = pipe_cstr_len(p);
        if ((ll > 255)) {
          (void)((ll = 255));
        }
        if ((ll > 0)) {
          int32_t _r = ast_pipeline_ctx_append_lib_root(ctx, p, ll);
        }
      }
    }
    (void)((i = (i + 1)));
  }
}

/* wave1225: release sidecars before free — see runtime_pipeline_abi.x pipe_release_tmp. */
extern void ast_pool_arena_release(void *a);
extern void ast_pool_module_release(void *m);
static void pipe_release_tmp_arena_module(void *arena, void *module) {
  if (arena) { ast_pool_arena_release(arena); free(arena); }
  if (module) { ast_pool_module_release(module); free(module); }
}
int32_t pipe_cstr_len(uint8_t * s) {
  if ((s ==0)) {
    return 0;
  }
  int32_t i = 0;
  while ((i < 65536)) {
    if (((s)[i] ==0)) {
      return i;
    }
    (void)((i = (i + 1)));
  }
  return i;
}
void xlang_pipeline_pctx_seed_dep_slots(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ar, uint8_t * import_paths, int32_t n) {
  if ((ctx ==0)) {
    return;
  }
  (void)(ast_pipeline_dep_ctx_reset(ctx));
  int32_t i = 0;
  while ((i < n)) {
    {
      uint8_t * m = 0;
      uint8_t * a = 0;
      if ((dep_mods !=0)) {
        (void)((m = pipe_load_ptr_slot(dep_mods, i)));
      }
      if ((dep_ar !=0)) {
        (void)((a = pipe_load_ptr_slot(dep_ar, i)));
      }
      (void)(ast_pipeline_dep_ctx_set_module(ctx, i, m));
      (void)(ast_pipeline_dep_ctx_set_arena(ctx, i, a));
      if ((import_paths !=0)) {
        uint8_t * p = pipe_load_ptr_slot(import_paths, i);
        if ((p !=0)) {
          int32_t pl = pipe_cstr_len(p);
          (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, p, pl));
        }
      }
    }
    (void)((i = (i + 1)));
  }
  (void)(ast_pipeline_dep_ctx_set_ndep(ctx, n));
}
void xlang_pipeline_pctx_seed_dep_import_paths_only(uint8_t * ctx, uint8_t * import_paths, int32_t n) {
  if ((ctx ==0)) {
    return;
  }
  (void)(ast_pipeline_dep_ctx_reset(ctx));
  int32_t i = 0;
  while ((i < n)) {
    if ((import_paths !=0)) {
      {
        uint8_t * p = pipe_load_ptr_slot(import_paths, i);
        if ((p !=0)) {
          int32_t pl = pipe_cstr_len(p);
          (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, p, pl));
        }
      }
    }
    (void)((i = (i + 1)));
  }
}
void xlang_pipeline_one_ctx_for_dep_prerun_map_impl(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * dep_paths, int32_t ndep, uint8_t * dep_src, int64_t dep_src_len) {
  if ((ctx ==0)) {
    return;
  }
  size_t asz = 0;
  size_t msz = 0;
  (void)((asz = pipeline_sizeof_arena()));
  (void)((msz = pipeline_sizeof_module()));
  uint8_t * tmp_arena = 0;
  uint8_t * tmp_module = 0;
  (void)((tmp_arena = malloc(asz)));
  (void)((tmp_module = malloc(msz)));
  if ((tmp_arena ==0)) {
    if ((tmp_module !=0)) {
      (void)(pipe_release_tmp_arena_module(NULL, tmp_module));
    }
    (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
    return;
  }
  if ((tmp_module ==0)) {
    (void)(pipe_release_tmp_arena_module(tmp_arena, NULL));
    (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
    return;
  }
  (void)(memset(tmp_arena, 0, asz));
  (void)(memset(tmp_module, 0, msz));
  (void)(parser_parse_into_init(tmp_module, tmp_arena));
  int32_t len_i32 = ((int32_t)(dep_src_len));
  int32_t pr_ok = 0;
  (void)((pr_ok = driver_parse_into_buf_rc(tmp_arena, tmp_module, dep_src, len_i32, 0)));
  if ((pr_ok !=0)) {
    if ((pr_ok !=-2)) {
      (void)(pipe_release_tmp_arena_module(tmp_arena, tmp_module));
      (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
      return;
    }
  }
  int32_t n_imp = xlang_module_num_imports(tmp_module);
  if ((n_imp <=0)) {
    (void)(pipe_release_tmp_arena_module(tmp_arena, tmp_module));
    (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
    return;
  }
  int32_t mapped = 0;
  int32_t ii = 0;
  while ((ii < n_imp)) {
    uint8_t path_c[65] = {};
    (void)(xlang_module_import_path_cstr(tmp_module, ii, &((path_c)[0]), 65));
    int32_t g = xlang_find_loaded_import_index(&((path_c)[0]), dep_paths, ndep);
    if ((g < 0)) {
      (void)((ii = (ii + 1)));
      continue;
    }
    {
      uint8_t * m = pipe_load_ptr_slot(dep_mods, g);
      uint8_t * a = pipe_load_ptr_slot(dep_ars, g);
      (void)(ast_pipeline_dep_ctx_set_module(ctx, mapped, m));
      (void)(ast_pipeline_dep_ctx_set_arena(ctx, mapped, a));
      uint8_t * p = pipe_load_ptr_slot(dep_paths, g);
      if ((p !=0)) {
        int32_t pl = pipe_cstr_len(p);
        (void)(ast_pipeline_dep_ctx_set_import_path(ctx, mapped, p, pl));
      }
    }
    (void)((mapped = (mapped + 1)));
    (void)((ii = (ii + 1)));
  }
  (void)(pipe_release_tmp_arena_module(tmp_arena, tmp_module));
  (void)(ast_pipeline_dep_ctx_set_ndep(ctx, mapped));
}
void xlang_pipeline_one_ctx_for_dep_prerun(uint8_t * ctx, int32_t j, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * dep_paths, int32_t ndep, uint8_t * dep_src, int64_t dep_src_len) {
  if ((ctx ==0)) {
    return;
  }
  int32_t _j = j;
  (void)(pipeline_dep_ctx_set_use_asm_backend(ctx, 0));
  if ((dep_mods ==0)) {
    (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
    return;
  }
  if ((dep_ars ==0)) {
    (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
    return;
  }
  if ((dep_paths ==0)) {
    (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
    return;
  }
  if ((ndep <=0)) {
    (void)(ast_pipeline_dep_ctx_set_ndep(ctx, 0));
    return;
  }
  if ((dep_src ==0)) {
    (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
    return;
  }
  if ((dep_src_len <=0)) {
    (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
    return;
  }
  int64_t imax = 2147483647;
  if ((dep_src_len > imax)) {
    (void)(xlang_pipeline_pctx_update_dep_slots_no_reset(ctx, dep_mods, dep_ars, dep_paths, ndep));
    return;
  }
  (void)(xlang_pipeline_one_ctx_for_dep_prerun_map_impl(ctx, dep_mods, dep_ars, dep_paths, ndep, dep_src, dep_src_len));
}
void xlang_driver_asm_prepare_entry_elf_emit(uint8_t * module, uint8_t * arena, uint8_t * pctx) {
  if ((module ==0)) {
    return;
  }
  if ((arena ==0)) {
    return;
  }
  /* fill_array + soa_fill: backend after dep merge only (mega emit wall). */
  (void)(asm_skip_heavy_set_pipeline_ctx(pctx));
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x65\x6d\x69\x74\x5f\x70\x72\x65\x70\x61\x72\x65\x5f\x70\x72\x65\x5f\x66\x69\x78\x75\x70"), module, arena));
  (void)(pipeline_module_fixup_with_arena_stmt_orders(module, arena));
  (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x65\x6d\x69\x74\x5f\x70\x72\x65\x70\x61\x72\x65\x5f\x70\x6f\x73\x74\x5f\x66\x69\x78\x75\x70"), module, arena));
}
int32_t xlang_asm_codegen_elf_o_large_stack(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf) {
  if ((module ==0)) {
    return -1;
  }
  if ((arena ==0)) {
    return -1;
  }
  if ((out_buf ==0)) {
    return -1;
  }
  return xlang_asm_codegen_elf_o_large_stack_impl(module, arena, ctx, elf_ctx, out_buf);
  return -1;
}
void xlang_load_direct_fail_cleanup(uint8_t * dep_sources, uint8_t * dep_paths, int32_t mi) {
  int32_t i = mi;
  while ((i > 0)) {
    (void)((i = (i - 1)));
    if ((dep_sources !=0)) {
      uint8_t * s = pipe_load_ptr_slot(dep_sources, i);
      if ((s !=0)) {
        (void)(free(s));
        (void)(pipe_store_ptr_slot(dep_sources, i, 0));
      }
    }
    if ((dep_paths !=0)) {
      uint8_t * p = pipe_load_ptr_slot(dep_paths, i);
      if ((p !=0)) {
        (void)(free(p));
        (void)(pipe_store_ptr_slot(dep_paths, i, 0));
      }
    }
  }
}
int32_t xlang_load_one_direct_resolve_read_preprocess(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_key, uint8_t * defines, int32_t ndefines, uint8_t * out_prep, uint8_t * out_prep_len) {
  if ((import_key ==0)) {
    return 1;
  }
  if ((out_prep ==0)) {
    return 1;
  }
  if ((out_prep_len ==0)) {
    return 1;
  }
  (void)(pipe_store_ptr_slot(out_prep, 0, 0));
  (void)(xlang_size_slot_set(out_prep_len, 0, 0));
  uint8_t resolved[4096] = {};
  int32_t zi = 0;
  while ((zi < 4096)) {
    (void)(((resolved)[zi] = 0));
    (void)((zi = (zi + 1)));
  }
  (void)(xlang_resolve_import_file_path_multi(lib_roots, n_lib_roots, entry_dir, import_key, &((resolved)[0]), 4096));
  uint8_t view[32] = {};
  int32_t z = 0;
  while ((z < 32)) {
    (void)(((view)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t view_rc = 0;
  (void)((view_rc = runtime_read_file_view(&((resolved)[0]), &((view)[0]))));
  if ((view_rc !=0)) {
    (void)(pipeline_diag_import_open_fail_once(import_key, &((resolved)[0])));
    return 1;
  }
  uint8_t * raw_data = xlang_ptr_slot_get(&((view)[0]), 0);
  int64_t raw_len = xlang_size_slot_get(&((view)[0]), 1);
  uint8_t * def_arg = 0;
  if ((ndefines > 0)) {
    (void)((def_arg = defines));
  }
  int32_t prep_rc = 0;
  (void)((prep_rc = xlang_preprocess_raw_to_malloc(raw_data, raw_len, out_prep, out_prep_len, &((resolved)[0]), def_arg, ndefines)));
  (void)(runtime_release_file_view(&((view)[0])));
  if ((prep_rc !=0)) {
    (void)(pipe_store_ptr_slot(out_prep, 0, 0));
    (void)(xlang_size_slot_set(out_prep_len, 0, 0));
    return 1;
  }
  uint8_t * prep = pipe_load_ptr_slot(out_prep, 0);
  if ((prep ==0)) {
    (void)(pipeline_diag_import_preprocess_fail(import_key, &((resolved)[0])));
    (void)(xlang_size_slot_set(out_prep_len, 0, 0));
    return 1;
  }
  return 0;
}
int32_t xlang_load_one_direct_import_at(uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * import_key, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t mi) {
  if ((import_key ==0)) {
    return 1;
  }
  if ((mi < 0)) {
    return 1;
  }
  uint8_t prep_cell[8] = {};
  uint8_t prep_len_cell[8] = {};
  int32_t rc = 0;
  (void)((rc = xlang_load_one_direct_resolve_read_preprocess(lib_roots, n_lib_roots, entry_dir, import_key, defines, ndefines, &((prep_cell)[0]), &((prep_len_cell)[0]))));
  if ((rc !=0)) {
    return 1;
  }
  uint8_t * prep = pipe_load_ptr_slot(&((prep_cell)[0]), 0);
  int64_t prep_len = xlang_size_slot_get(&((prep_len_cell)[0]), 0);
  if ((prep ==0)) {
    return 1;
  }
  if ((dep_sources !=0)) {
    (void)(pipe_store_ptr_slot(dep_sources, mi, prep));
  }
  if ((dep_lens !=0)) {
    (void)(xlang_size_slot_set(dep_lens, mi, prep_len));
  }
  if ((dep_paths !=0)) {
    uint8_t * key = 0;
    (void)((key = xlang_collect_strdup(import_key)));
    if ((key ==0)) {
      (void)(free(prep));
      if ((dep_sources !=0)) {
        (void)(pipe_store_ptr_slot(dep_sources, mi, 0));
      }
      return 1;
    }
    (void)(pipe_store_ptr_slot(dep_paths, mi, key));
  }
  return 0;
}
int32_t xlang_load_direct_imports_for_asm_layout(uint8_t * module, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * out_n) {
  if ((module ==0)) {
    return -1;
  }
  if ((out_n ==0)) {
    return -1;
  }
  (void)(xlang_i32_store(out_n, 0));
  int32_t n_imports = 0;
  (void)((n_imports = xlang_module_num_imports(module)));
  if ((n_imports <=0)) {
    return 0;
  }
  int32_t mi = 0;
  int32_t i = 0;
  while ((i < n_imports)) {
    if ((i >=32)) {
      break;
    }
    if ((mi >=32)) {
      break;
    }
    uint8_t path_c[65] = {};
    (void)(xlang_module_import_path_cstr(module, i, &((path_c)[0]), 65));
    int32_t rc = 0;
    (void)((rc = xlang_load_one_direct_import_at(lib_roots, n_lib_roots, entry_dir, &((path_c)[0]), defines, ndefines, dep_sources, dep_lens, dep_paths, mi)));
    if ((rc !=0)) {
      (void)(xlang_load_direct_fail_cleanup(dep_sources, dep_paths, mi));
      (void)(xlang_i32_store(out_n, 0));
      return 1;
    }
    (void)((mi = (mi + 1)));
    (void)((i = (i + 1)));
  }
  (void)(xlang_i32_store(out_n, mi));
  return 0;
}
int32_t xlang_merge_direct_then_transitive_dep_paths(uint8_t * module, int32_t n_imports, uint8_t * cpaths, int32_t n_closure, uint8_t * out_paths, int32_t * out_n) {
  if ((module ==0)) {
    return -1;
  }
  if ((out_n ==0)) {
    return -1;
  }
  if ((out_paths ==0)) {
    return -1;
  }
  uint8_t used[32] = {};
  int32_t ui = 0;
  while ((ui < 32)) {
    (void)(((used)[ui] = 0));
    (void)((ui = (ui + 1)));
  }
  int32_t mi = 0;
  int32_t i = 0;
  while ((i < n_imports)) {
    if ((i >=32)) {
      break;
    }
    if ((mi >=32)) {
      break;
    }
    uint8_t path_c[65] = {};
    (void)(xlang_module_import_path_cstr(module, i, &((path_c)[0]), 65));
    int32_t found = -1;
    int32_t kk = 0;
    while ((kk < n_closure)) {
      {
        uint8_t * cp = 0;
        if ((cpaths !=0)) {
          (void)((cp = pipe_load_ptr_slot(cpaths, kk)));
        }
        if ((cp !=0)) {
          if ((pipe_cstr_eq(cp, &((path_c)[0])) !=0)) {
            (void)((found = kk));
          }
        }
      }
      if ((found >=0)) {
        break;
      }
      (void)((kk = (kk + 1)));
    }
    if ((found < 0)) {
      (void)(pipeline_diag_merge_dep_missing(&((path_c)[0])));
      return 1;
    }
    {
      uint8_t * pfound = pipe_load_ptr_slot(cpaths, found);
      (void)(xlang_ptr_slot_set(out_paths, mi, pfound));
    }
    if ((found < 32)) {
      (void)(((used)[found] = 1));
    }
    (void)((mi = (mi + 1)));
    (void)((i = (i + 1)));
  }
  int32_t kj = 0;
  while ((kj < n_closure)) {
    if ((mi >=32)) {
      break;
    }
    if ((kj < 32)) {
      if (((used)[kj] ==0)) {
        {
          uint8_t * cp2 = 0;
          if ((cpaths !=0)) {
            (void)((cp2 = pipe_load_ptr_slot(cpaths, kj)));
          }
          if ((cp2 !=0)) {
            if ((xlang_merge_deps_path_already_out(cp2, out_paths, mi) !=0)) {
              (void)(((used)[kj] = 1));
            } else {
              (void)(xlang_ptr_slot_set(out_paths, mi, cp2));
              (void)((mi = (mi + 1)));
            }
          } else {
            (void)(xlang_ptr_slot_set(out_paths, mi, cp2));
            (void)((mi = (mi + 1)));
          }
        }
      }
    }
    (void)((kj = (kj + 1)));
  }
  (void)(xlang_i32_store(out_n, mi));
  return 0;
}
int32_t xlang_merge_direct_then_transitive_deps(uint8_t * module, int32_t n_imports, uint8_t * cls, uint8_t * clens, uint8_t * cpaths, int32_t n_closure, uint8_t * out_src, uint8_t * out_lens, uint8_t * out_paths, int32_t * out_n) {
  if ((module ==0)) {
    return -1;
  }
  if ((out_n ==0)) {
    return -1;
  }
  if ((out_paths ==0)) {
    return -1;
  }
  uint8_t used[32] = {};
  int32_t ui = 0;
  while ((ui < 32)) {
    (void)(((used)[ui] = 0));
    (void)((ui = (ui + 1)));
  }
  int32_t mi = 0;
  int32_t i = 0;
  while ((i < n_imports)) {
    if ((i >=32)) {
      break;
    }
    if ((mi >=32)) {
      break;
    }
    uint8_t path_c[65] = {};
    (void)(xlang_module_import_path_cstr(module, i, &((path_c)[0]), 65));
    int32_t found = -1;
    int32_t kk = 0;
    while ((kk < n_closure)) {
      {
        uint8_t * cp = 0;
        if ((cpaths !=0)) {
          (void)((cp = pipe_load_ptr_slot(cpaths, kk)));
        }
        if ((cp !=0)) {
          if ((pipe_cstr_eq(cp, &((path_c)[0])) !=0)) {
            (void)((found = kk));
          }
        }
      }
      if ((found >=0)) {
        break;
      }
      (void)((kk = (kk + 1)));
    }
    if ((found < 0)) {
      (void)(pipeline_diag_merge_dep_missing(&((path_c)[0])));
      return 1;
    }
    {
      uint8_t * pfound = 0;
      uint8_t * sfound = 0;
      int64_t lfound = 0;
      if ((cpaths !=0)) {
        (void)((pfound = pipe_load_ptr_slot(cpaths, found)));
      }
      if ((cls !=0)) {
        (void)((sfound = pipe_load_ptr_slot(cls, found)));
      }
      if ((clens !=0)) {
        (void)((lfound = xlang_size_slot_get(clens, found)));
      }
      if ((out_src !=0)) {
        (void)(xlang_ptr_slot_set(out_src, mi, sfound));
      }
      if ((out_lens !=0)) {
        (void)(xlang_size_slot_set(out_lens, mi, lfound));
      }
      (void)(xlang_ptr_slot_set(out_paths, mi, pfound));
    }
    if ((found < 32)) {
      (void)(((used)[found] = 1));
    }
    (void)((mi = (mi + 1)));
    (void)((i = (i + 1)));
  }
  int32_t kj = 0;
  while ((kj < n_closure)) {
    if ((mi >=32)) {
      break;
    }
    if ((kj < 32)) {
      if (((used)[kj] ==0)) {
        {
          uint8_t * cp2 = 0;
          if ((cpaths !=0)) {
            (void)((cp2 = pipe_load_ptr_slot(cpaths, kj)));
          }
          if ((cp2 !=0)) {
            if ((xlang_merge_deps_path_already_out(cp2, out_paths, mi) !=0)) {
              (void)(((used)[kj] = 1));
            } else {
              uint8_t * s2 = 0;
              int64_t l2 = 0;
              if ((cls !=0)) {
                (void)((s2 = pipe_load_ptr_slot(cls, kj)));
              }
              if ((clens !=0)) {
                (void)((l2 = xlang_size_slot_get(clens, kj)));
              }
              if ((out_src !=0)) {
                (void)(xlang_ptr_slot_set(out_src, mi, s2));
              }
              if ((out_lens !=0)) {
                (void)(xlang_size_slot_set(out_lens, mi, l2));
              }
              (void)(xlang_ptr_slot_set(out_paths, mi, cp2));
              (void)((mi = (mi + 1)));
            }
          } else {
            uint8_t * s3 = 0;
            int64_t l3 = 0;
            if ((cls !=0)) {
              (void)((s3 = pipe_load_ptr_slot(cls, kj)));
            }
            if ((clens !=0)) {
              (void)((l3 = xlang_size_slot_get(clens, kj)));
            }
            if ((out_src !=0)) {
              (void)(xlang_ptr_slot_set(out_src, mi, s3));
            }
            if ((out_lens !=0)) {
              (void)(xlang_size_slot_set(out_lens, mi, l3));
            }
            (void)(xlang_ptr_slot_set(out_paths, mi, cp2));
            (void)((mi = (mi + 1)));
          }
        }
      }
    }
    (void)((kj = (kj + 1)));
  }
  (void)(xlang_i32_store(out_n, mi));
  return 0;
}
int32_t xlang_collect_deps_transitive(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n_deps) {
  if ((module ==0)) {
    return -1;
  }
  if ((n_deps ==0)) {
    return -1;
  }
  int32_t nimp = 0;
  (void)((nimp = xlang_module_num_imports(module)));
  if ((nimp <=0)) {
    (void)(xlang_i32_store(n_deps, 0));
    return 0;
  }
  return xlang_collect_deps_transitive_impl(module, arena_sz, module_sz, lib_roots, n_lib_roots, entry_dir, defines, ndefines, dep_sources, dep_lens, dep_paths, n_deps);
  return -1;
}
int32_t xlang_collect_dep_paths_transitive(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n_deps) {
  if ((module ==0)) {
    return -1;
  }
  if ((n_deps ==0)) {
    return -1;
  }
  int32_t nimp = 0;
  (void)((nimp = xlang_module_num_imports(module)));
  if ((nimp <=0)) {
    (void)(xlang_i32_store(n_deps, 0));
    return 0;
  }
  return xlang_collect_dep_paths_transitive_impl(module, arena_sz, module_sz, lib_roots, n_lib_roots, entry_dir, defines, ndefines, dep_paths, n_deps);
  return -1;
}
int32_t pipe_diag_msg_append_cstr(uint8_t * dst, int32_t cap, int32_t at, uint8_t * src) {
  if ((dst ==0)) {
    return at;
  }
  if ((src ==0)) {
    return at;
  }
  int32_t j = at;
  int32_t i = 0;
  while (((j + 1) < cap)) {
    uint8_t c = (src)[i];
    if ((c ==0)) {
      break;
    }
    (void)(((dst)[j] = c));
    (void)((j = (j + 1)));
    (void)((i = (i + 1)));
  }
  if ((j < cap)) {
    (void)(((dst)[j] = 0));
  }
  return j;
}
int32_t pipe_diag_msg_append_i32(uint8_t * dst, int32_t cap, int32_t at, int32_t val) {
  if ((dst ==0)) {
    return at;
  }
  if (((at + 1) >=cap)) {
    return at;
  }
  int32_t v = val;
  {
    if ((v < 0)) {
      (void)(((dst)[at] = 45));
      (void)((at = (at + 1)));
      (void)((v = (0 - v)));
    }
    int32_t d0 = 0;
    int32_t d1 = 0;
    int32_t d2 = 0;
    int32_t d3 = 0;
    int32_t d4 = 0;
    int32_t d5 = 0;
    int32_t d6 = 0;
    int32_t d7 = 0;
    int32_t d8 = 0;
    int32_t d9 = 0;
    int32_t dn = 0;
    if ((v ==0)) {
      (void)((d0 = 0));
      (void)((dn = 1));
    } else {
      int32_t t = v;
      while ((t > 0)) {
        if ((dn >=10)) {
          break;
        }
        int32_t dig = (t % 10);
        if ((dn ==0)) {
          (void)((d0 = dig));
        }
        if ((dn ==1)) {
          (void)((d1 = dig));
        }
        if ((dn ==2)) {
          (void)((d2 = dig));
        }
        if ((dn ==3)) {
          (void)((d3 = dig));
        }
        if ((dn ==4)) {
          (void)((d4 = dig));
        }
        if ((dn ==5)) {
          (void)((d5 = dig));
        }
        if ((dn ==6)) {
          (void)((d6 = dig));
        }
        if ((dn ==7)) {
          (void)((d7 = dig));
        }
        if ((dn ==8)) {
          (void)((d8 = dig));
        }
        if ((dn ==9)) {
          (void)((d9 = dig));
        }
        (void)((dn = (dn + 1)));
        (void)((t = (t / 10)));
      }
    }
    int32_t k = dn;
    while ((k > 0)) {
      if (((at + 1) >=cap)) {
        break;
      }
      (void)((k = (k - 1)));
      int32_t dig = 0;
      if ((k ==0)) {
        (void)((dig = d0));
      }
      if ((k ==1)) {
        (void)((dig = d1));
      }
      if ((k ==2)) {
        (void)((dig = d2));
      }
      if ((k ==3)) {
        (void)((dig = d3));
      }
      if ((k ==4)) {
        (void)((dig = d4));
      }
      if ((k ==5)) {
        (void)((dig = d5));
      }
      if ((k ==6)) {
        (void)((dig = d6));
      }
      if ((k ==7)) {
        (void)((dig = d7));
      }
      if ((k ==8)) {
        (void)((dig = d8));
      }
      if ((k ==9)) {
        (void)((dig = d9));
      }
      (void)(((dst)[at] = ((uint8_t)((48 + dig)))));
      (void)((at = (at + 1)));
    }
    if ((at < cap)) {
      (void)(((dst)[at] = 0));
    }
  }
  return at;
}
int32_t pipe_diag_msg_append_name(uint8_t * dst, int32_t cap, int32_t at, uint8_t * name, int32_t name_len) {
  if ((dst ==0)) {
    return at;
  }
  if ((name ==0)) {
    return at;
  }
  if ((name_len <=0)) {
    return at;
  }
  int32_t n = 0;
  while ((n < name_len)) {
    if (((at + 1) >=cap)) {
      break;
    }
    (void)(((dst)[at] = (name)[n]));
    (void)((at = (at + 1)));
    (void)((n = (n + 1)));
  }
  if ((at < cap)) {
    (void)(((dst)[at] = 0));
  }
  return at;
}
void pipeline_debug_trace_named_func_bodies_impl(uint8_t * phase, uint8_t * module, uint8_t * arena) {
  if ((module ==0)) {
    return;
  }
  if ((arena ==0)) {
    return;
  }
  {
    uint8_t key[24] = {};
    (void)(((key)[0] = 83));
    (void)(((key)[1] = 72));
    (void)(((key)[2] = 85));
    (void)(((key)[3] = 88));
    (void)(((key)[4] = 95));
    (void)(((key)[5] = 68));
    (void)(((key)[6] = 69));
    (void)(((key)[7] = 66));
    (void)(((key)[8] = 85));
    (void)(((key)[9] = 71));
    (void)(((key)[10] = 95));
    (void)(((key)[11] = 66));
    (void)(((key)[12] = 79));
    (void)(((key)[13] = 68));
    (void)(((key)[14] = 89));
    (void)(((key)[15] = 95));
    (void)(((key)[16] = 70));
    (void)(((key)[17] = 85));
    (void)(((key)[18] = 78));
    (void)(((key)[19] = 67));
    (void)(((key)[20] = 0));
    uint8_t * filter = link_abi_getenv(&((key)[0]));
    if ((filter ==0)) {
      return;
    }
    if (((filter)[0] ==0)) {
      return;
    }
    if (((filter)[0] ==48)) {
      return;
    }
    int32_t nf = pipeline_module_num_funcs(module);
    int32_t fi = 0;
    while ((fi < nf)) {
      uint8_t raw_name[128] = {};
      uint8_t name[65] = {};
      int32_t ni = 0;
      while ((ni < 64)) {
        (void)(((raw_name)[ni] = 0));
        (void)((ni = (ni + 1)));
      }
      (void)((ni = 0));
      while ((ni < 65)) {
        (void)(((name)[ni] = 0));
        (void)((ni = (ni + 1)));
      }
      int32_t name_len = pipeline_module_func_name_len_at(module, fi);
      if ((name_len > 0)) {
        if ((name_len <=64)) {
          (void)(pipeline_module_func_name_copy64(module, fi, &((raw_name)[0])));
          int32_t ci = 0;
          while ((ci < name_len)) {
            (void)(((name)[ci] = (raw_name)[ci]));
            (void)((ci = (ci + 1)));
          }
          (void)(((name)[name_len] = 0));
          if ((pipeline_debug_body_func_match(filter, &((name)[0])) !=0)) {
            int32_t body_ref = pipeline_module_func_body_ref_at(module, fi);
            int32_t c_n = -1;
            int32_t l_n = -1;
            int32_t if_n = -1;
            int32_t reg_n = -1;
            int32_t so_n = -1;
            int32_t fin_n = -1;
            if ((body_ref > 0)) {
              (void)((c_n = ast_ast_block_num_consts(arena, body_ref)));
              (void)((l_n = ast_ast_block_num_lets(arena, body_ref)));
              (void)((if_n = ast_ast_block_num_if_stmts(arena, body_ref)));
              (void)((reg_n = ast_ast_block_num_regions(arena, body_ref)));
              (void)((so_n = ast_ast_block_num_stmt_order(arena, body_ref)));
              (void)((fin_n = ast_ast_block_final_expr_ref(arena, body_ref)));
            }
            uint8_t msg[320] = {};
            int32_t at = 0;
            int32_t cap = 320;
            uint8_t lit[32] = {};
            (void)(((lit)[0] = 98));
            (void)(((lit)[1] = 111));
            (void)(((lit)[2] = 100));
            (void)(((lit)[3] = 121));
            (void)(((lit)[4] = 32));
            (void)(((lit)[5] = 116));
            (void)(((lit)[6] = 114));
            (void)(((lit)[7] = 97));
            (void)(((lit)[8] = 99));
            (void)(((lit)[9] = 101));
            (void)(((lit)[10] = 58));
            (void)(((lit)[11] = 32));
            (void)(((lit)[12] = 112));
            (void)(((lit)[13] = 104));
            (void)(((lit)[14] = 97));
            (void)(((lit)[15] = 115));
            (void)(((lit)[16] = 101));
            (void)(((lit)[17] = 61));
            (void)(((lit)[18] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            if ((phase !=0)) {
              if (((phase)[0] !=0)) {
                (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, phase)));
              } else {
                (void)(((lit)[0] = 63));
                (void)(((lit)[1] = 0));
                (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
              }
            } else {
              (void)(((lit)[0] = 63));
              (void)(((lit)[1] = 0));
              (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            }
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 102));
            (void)(((lit)[2] = 105));
            (void)(((lit)[3] = 61));
            (void)(((lit)[4] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, fi)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 98));
            (void)(((lit)[2] = 111));
            (void)(((lit)[3] = 100));
            (void)(((lit)[4] = 121));
            (void)(((lit)[5] = 95));
            (void)(((lit)[6] = 114));
            (void)(((lit)[7] = 101));
            (void)(((lit)[8] = 102));
            (void)(((lit)[9] = 61));
            (void)(((lit)[10] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, body_ref)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 110));
            (void)(((lit)[2] = 97));
            (void)(((lit)[3] = 109));
            (void)(((lit)[4] = 101));
            (void)(((lit)[5] = 61));
            (void)(((lit)[6] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_name(&((msg)[0]), cap, at, &((name)[0]), name_len)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 98));
            (void)(((lit)[2] = 108));
            (void)(((lit)[3] = 111));
            (void)(((lit)[4] = 99));
            (void)(((lit)[5] = 107));
            (void)(((lit)[6] = 40));
            (void)(((lit)[7] = 99));
            (void)(((lit)[8] = 61));
            (void)(((lit)[9] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, c_n)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 108));
            (void)(((lit)[2] = 61));
            (void)(((lit)[3] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, l_n)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 105));
            (void)(((lit)[2] = 102));
            (void)(((lit)[3] = 61));
            (void)(((lit)[4] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, if_n)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 114));
            (void)(((lit)[2] = 101));
            (void)(((lit)[3] = 103));
            (void)(((lit)[4] = 61));
            (void)(((lit)[5] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, reg_n)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 115));
            (void)(((lit)[2] = 111));
            (void)(((lit)[3] = 61));
            (void)(((lit)[4] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, so_n)));
            (void)(((lit)[0] = 32));
            (void)(((lit)[1] = 102));
            (void)(((lit)[2] = 105));
            (void)(((lit)[3] = 110));
            (void)(((lit)[4] = 61));
            (void)(((lit)[5] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            (void)((at = pipe_diag_msg_append_i32(&((msg)[0]), cap, at, fin_n)));
            (void)(((lit)[0] = 41));
            (void)(((lit)[1] = 0));
            (void)((at = pipe_diag_msg_append_cstr(&((msg)[0]), cap, at, &((lit)[0]))));
            uint8_t note_k[8] = {};
            (void)(((note_k)[0] = 110));
            (void)(((note_k)[1] = 111));
            (void)(((note_k)[2] = 116));
            (void)(((note_k)[3] = 101));
            (void)(((note_k)[4] = 0));
            (void)(diag_report(((uint8_t *)(0)), 0, 0, &((note_k)[0]), &((msg)[0]), ((uint8_t *)(0))));
          }
        }
      }
      (void)((fi = (fi + 1)));
    }
  }
}
void pipeline_debug_trace_named_func_bodies(uint8_t * phase, uint8_t * module, uint8_t * arena) {
  if ((module ==0)) {
    return;
  }
  if ((arena ==0)) {
    return;
  }
  (void)(pipeline_debug_trace_named_func_bodies_impl(phase, module, arena));
}
int32_t typeck_module_entry_only(uint8_t * module) {
  if ((module ==0)) {
    return -1;
  }
  return -1;
}
int32_t typeck_module_with_sidecar(uint8_t * module) {
  if ((module ==0)) {
    return -1;
  }
  return -1;
}
int32_t pipeline_typeck_module_for_ctx_impl(uint8_t * module, uint8_t * arena, uint8_t * ctx_void) {
  if ((module ==0)) {
    return -1;
  }
  if (((arena ==0) || (ctx_void ==0))) {
    return -1;
  }
  int32_t mi = 0;
  (void)((mi = pipeline_module_main_func_index(module)));
  int32_t rc = 0;
  if ((mi < 0)) {
    (void)((rc = typeck_x_ast_library(module, arena, ctx_void)));
  } else {
    (void)((rc = typeck_x_ast(module, arena, ctx_void)));
  }
  if ((rc !=0)) {
    return -1;
  }
  return 0;
}
int32_t pipeline_typeck_module_for_ctx(uint8_t * module, uint8_t * arena, uint8_t * ctx) {
  if ((module ==0)) {
    return -1;
  }
  return pipeline_typeck_module_for_ctx_impl(module, arena, ctx);
}
void xlang_lsp_ptr_slot_clear(uint8_t * arr, int32_t i) {
  if ((arr ==0)) {
    return;
  }
  if ((i < 0)) {
    return;
  }
  (void)(xlang_ptr_slot_set(arr, i, 0));
}
void xlang_lsp_free_loaded_imports(uint8_t * all_dep_mods, uint8_t * all_dep_paths, int32_t n_all) {
  if ((all_dep_mods ==0)) {
    return;
  }
  if ((all_dep_paths ==0)) {
    return;
  }
  if ((n_all <=0)) {
    return;
  }
  int32_t i = 0;
  while ((i < n_all)) {
    {
      uint8_t * p = pipe_load_ptr_slot(all_dep_paths, i);
      if ((p !=0)) {
        (void)(free(p));
        (void)(xlang_lsp_ptr_slot_clear(all_dep_paths, i));
      }
      uint8_t * m = pipe_load_ptr_slot(all_dep_mods, i);
      if ((m !=0)) {
        (void)(ast_module_free(m));
        (void)(xlang_lsp_ptr_slot_clear(all_dep_mods, i));
      }
    }
    (void)((i = (i + 1)));
  }
}
void pipeline_diag_preprocess_unclosed_if(uint8_t * path_diag) {
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[24] = {};
  uint8_t code[8] = {};
  uint8_t msg[16] = {};
  (void)(((kind)[0] = 112));
  (void)(((kind)[1] = 114));
  (void)(((kind)[2] = 101));
  (void)(((kind)[3] = 112));
  (void)(((kind)[4] = 114));
  (void)(((kind)[5] = 111));
  (void)(((kind)[6] = 99));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 115));
  (void)(((kind)[9] = 115));
  (void)(((kind)[10] = 32));
  (void)(((kind)[11] = 101));
  (void)(((kind)[12] = 114));
  (void)(((kind)[13] = 114));
  (void)(((kind)[14] = 111));
  (void)(((kind)[15] = 114));
  (void)(((kind)[16] = 0));
  (void)(((code)[0] = 80));
  (void)(((code)[1] = 80));
  (void)(((code)[2] = 48));
  (void)(((code)[3] = 48));
  (void)(((code)[4] = 49));
  (void)(((code)[5] = 0));
  (void)(((msg)[0] = 117));
  (void)(((msg)[1] = 110));
  (void)(((msg)[2] = 99));
  (void)(((msg)[3] = 108));
  (void)(((msg)[4] = 111));
  (void)(((msg)[5] = 115));
  (void)(((msg)[6] = 101));
  (void)(((msg)[7] = 100));
  (void)(((msg)[8] = 32));
  (void)(((msg)[9] = 35));
  (void)(((msg)[10] = 105));
  (void)(((msg)[11] = 102));
  (void)(((msg)[12] = 0));
  (void)(diag_report_with_code(path_diag, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), 0));
}
void pipeline_diag_preprocess_fail(uint8_t * path_diag) {
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[24] = {};
  uint8_t code[8] = {};
  uint8_t msg[40] = {};
  (void)(((kind)[0] = 112));
  (void)(((kind)[1] = 114));
  (void)(((kind)[2] = 101));
  (void)(((kind)[3] = 112));
  (void)(((kind)[4] = 114));
  (void)(((kind)[5] = 111));
  (void)(((kind)[6] = 99));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 115));
  (void)(((kind)[9] = 115));
  (void)(((kind)[10] = 32));
  (void)(((kind)[11] = 101));
  (void)(((kind)[12] = 114));
  (void)(((kind)[13] = 114));
  (void)(((kind)[14] = 111));
  (void)(((kind)[15] = 114));
  (void)(((kind)[16] = 0));
  (void)(((code)[0] = 80));
  (void)(((code)[1] = 80));
  (void)(((code)[2] = 48));
  (void)(((code)[3] = 48));
  (void)(((code)[4] = 50));
  (void)(((code)[5] = 0));
  (void)(((msg)[0] = 46));
  (void)(((msg)[1] = 120));
  (void)(((msg)[2] = 32));
  (void)(((msg)[3] = 112));
  (void)(((msg)[4] = 114));
  (void)(((msg)[5] = 101));
  (void)(((msg)[6] = 112));
  (void)(((msg)[7] = 114));
  (void)(((msg)[8] = 111));
  (void)(((msg)[9] = 99));
  (void)(((msg)[10] = 101));
  (void)(((msg)[11] = 115));
  (void)(((msg)[12] = 115));
  (void)(((msg)[13] = 32));
  (void)(((msg)[14] = 102));
  (void)(((msg)[15] = 97));
  (void)(((msg)[16] = 105));
  (void)(((msg)[17] = 108));
  (void)(((msg)[18] = 101));
  (void)(((msg)[19] = 100));
  (void)(((msg)[20] = 0));
  (void)(diag_report_with_code(path_diag, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), 0));
}
void pipeline_diag_import_preprocess_fail(uint8_t * import_path, uint8_t * resolved_path) {
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[24] = {};
  uint8_t code[8] = {};
  uint8_t msg[40] = {};
  (void)(((kind)[0] = 112));
  (void)(((kind)[1] = 114));
  (void)(((kind)[2] = 101));
  (void)(((kind)[3] = 112));
  (void)(((kind)[4] = 114));
  (void)(((kind)[5] = 111));
  (void)(((kind)[6] = 99));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 115));
  (void)(((kind)[9] = 115));
  (void)(((kind)[10] = 32));
  (void)(((kind)[11] = 101));
  (void)(((kind)[12] = 114));
  (void)(((kind)[13] = 114));
  (void)(((kind)[14] = 111));
  (void)(((kind)[15] = 114));
  (void)(((kind)[16] = 0));
  (void)(((code)[0] = 73));
  (void)(((code)[1] = 77));
  (void)(((code)[2] = 80));
  (void)(((code)[3] = 48));
  (void)(((code)[4] = 48));
  (void)(((code)[5] = 50));
  (void)(((code)[6] = 0));
  (void)(((msg)[0] = 105));
  (void)(((msg)[1] = 109));
  (void)(((msg)[2] = 112));
  (void)(((msg)[3] = 111));
  (void)(((msg)[4] = 114));
  (void)(((msg)[5] = 116));
  (void)(((msg)[6] = 32));
  (void)(((msg)[7] = 112));
  (void)(((msg)[8] = 114));
  (void)(((msg)[9] = 101));
  (void)(((msg)[10] = 112));
  (void)(((msg)[11] = 114));
  (void)(((msg)[12] = 111));
  (void)(((msg)[13] = 99));
  (void)(((msg)[14] = 101));
  (void)(((msg)[15] = 115));
  (void)(((msg)[16] = 115));
  (void)(((msg)[17] = 32));
  (void)(((msg)[18] = 102));
  (void)(((msg)[19] = 97));
  (void)(((msg)[20] = 105));
  (void)(((msg)[21] = 108));
  (void)(((msg)[22] = 101));
  (void)(((msg)[23] = 100));
  (void)(((msg)[24] = 0));
  uint8_t * file = resolved_path;
  if ((file ==0)) {
    (void)((file = import_path));
  }
  (void)(diag_report_with_code(file, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), 0));
}
void pipeline_diag_preprocess_alloc_fail(uint8_t * path_diag, uint8_t * what) {
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[24] = {};
  uint8_t code[8] = {};
  uint8_t msg[48] = {};
  (void)(((kind)[0] = 112));
  (void)(((kind)[1] = 105));
  (void)(((kind)[2] = 112));
  (void)(((kind)[3] = 101));
  (void)(((kind)[4] = 108));
  (void)(((kind)[5] = 105));
  (void)(((kind)[6] = 110));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 32));
  (void)(((kind)[9] = 101));
  (void)(((kind)[10] = 114));
  (void)(((kind)[11] = 114));
  (void)(((kind)[12] = 111));
  (void)(((kind)[13] = 114));
  (void)(((kind)[14] = 0));
  (void)(((code)[0] = 88));
  (void)(((code)[1] = 80));
  (void)(((code)[2] = 48));
  (void)(((code)[3] = 48));
  (void)(((code)[4] = 53));
  (void)(((code)[5] = 0));
  (void)(((msg)[0] = 97));
  (void)(((msg)[1] = 108));
  (void)(((msg)[2] = 108));
  (void)(((msg)[3] = 111));
  (void)(((msg)[4] = 99));
  (void)(((msg)[5] = 97));
  (void)(((msg)[6] = 116));
  (void)(((msg)[7] = 105));
  (void)(((msg)[8] = 111));
  (void)(((msg)[9] = 110));
  (void)(((msg)[10] = 32));
  (void)(((msg)[11] = 102));
  (void)(((msg)[12] = 97));
  (void)(((msg)[13] = 105));
  (void)(((msg)[14] = 108));
  (void)(((msg)[15] = 101));
  (void)(((msg)[16] = 100));
  (void)(((msg)[17] = 32));
  (void)(((msg)[18] = 100));
  (void)(((msg)[19] = 117));
  (void)(((msg)[20] = 114));
  (void)(((msg)[21] = 105));
  (void)(((msg)[22] = 110));
  (void)(((msg)[23] = 103));
  (void)(((msg)[24] = 32));
  (void)(((msg)[25] = 112));
  (void)(((msg)[26] = 114));
  (void)(((msg)[27] = 101));
  (void)(((msg)[28] = 112));
  (void)(((msg)[29] = 114));
  (void)(((msg)[30] = 111));
  (void)(((msg)[31] = 99));
  (void)(((msg)[32] = 101));
  (void)(((msg)[33] = 115));
  (void)(((msg)[34] = 115));
  (void)(((msg)[35] = 0));
  uint8_t * _w = what;
  (void)(diag_report_with_code(path_diag, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), 0));
}
void pipeline_diag_merge_dep_missing(uint8_t * import_path) {
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[16] = {};
  uint8_t code[8] = {};
  uint8_t msg[48] = {};
  uint8_t note_k[8] = {};
  uint8_t note_m[128] = {};
  (void)(((kind)[0] = 105));
  (void)(((kind)[1] = 109));
  (void)(((kind)[2] = 112));
  (void)(((kind)[3] = 111));
  (void)(((kind)[4] = 114));
  (void)(((kind)[5] = 116));
  (void)(((kind)[6] = 32));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 114));
  (void)(((kind)[9] = 114));
  (void)(((kind)[10] = 111));
  (void)(((kind)[11] = 114));
  (void)(((kind)[12] = 0));
  (void)(((code)[0] = 73));
  (void)(((code)[1] = 77));
  (void)(((code)[2] = 80));
  (void)(((code)[3] = 48));
  (void)(((code)[4] = 48));
  (void)(((code)[5] = 52));
  (void)(((code)[6] = 0));
  (void)(((msg)[0] = 100));
  (void)(((msg)[1] = 105));
  (void)(((msg)[2] = 114));
  (void)(((msg)[3] = 101));
  (void)(((msg)[4] = 99));
  (void)(((msg)[5] = 116));
  (void)(((msg)[6] = 32));
  (void)(((msg)[7] = 105));
  (void)(((msg)[8] = 109));
  (void)(((msg)[9] = 112));
  (void)(((msg)[10] = 111));
  (void)(((msg)[11] = 114));
  (void)(((msg)[12] = 116));
  (void)(((msg)[13] = 32));
  (void)(((msg)[14] = 109));
  (void)(((msg)[15] = 105));
  (void)(((msg)[16] = 115));
  (void)(((msg)[17] = 115));
  (void)(((msg)[18] = 105));
  (void)(((msg)[19] = 110));
  (void)(((msg)[20] = 103));
  (void)(((msg)[21] = 32));
  (void)(((msg)[22] = 102));
  (void)(((msg)[23] = 114));
  (void)(((msg)[24] = 111));
  (void)(((msg)[25] = 109));
  (void)(((msg)[26] = 32));
  (void)(((msg)[27] = 100));
  (void)(((msg)[28] = 101));
  (void)(((msg)[29] = 112));
  (void)(((msg)[30] = 32));
  (void)(((msg)[31] = 99));
  (void)(((msg)[32] = 108));
  (void)(((msg)[33] = 111));
  (void)(((msg)[34] = 115));
  (void)(((msg)[35] = 117));
  (void)(((msg)[36] = 114));
  (void)(((msg)[37] = 101));
  (void)(((msg)[38] = 0));
  (void)(((note_k)[0] = 110));
  (void)(((note_k)[1] = 111));
  (void)(((note_k)[2] = 116));
  (void)(((note_k)[3] = 101));
  (void)(((note_k)[4] = 0));
  (void)(((note_m)[0] = 100));
  (void)(((note_m)[1] = 101));
  (void)(((note_m)[2] = 112));
  (void)(((note_m)[3] = 101));
  (void)(((note_m)[4] = 110));
  (void)(((note_m)[5] = 100));
  (void)(((note_m)[6] = 101));
  (void)(((note_m)[7] = 110));
  (void)(((note_m)[8] = 99));
  (void)(((note_m)[9] = 121));
  (void)(((note_m)[10] = 32));
  (void)(((note_m)[11] = 99));
  (void)(((note_m)[12] = 108));
  (void)(((note_m)[13] = 111));
  (void)(((note_m)[14] = 115));
  (void)(((note_m)[15] = 117));
  (void)(((note_m)[16] = 114));
  (void)(((note_m)[17] = 101));
  (void)(((note_m)[18] = 32));
  (void)(((note_m)[19] = 99));
  (void)(((note_m)[20] = 111));
  (void)(((note_m)[21] = 110));
  (void)(((note_m)[22] = 115));
  (void)(((note_m)[23] = 116));
  (void)(((note_m)[24] = 114));
  (void)(((note_m)[25] = 117));
  (void)(((note_m)[26] = 99));
  (void)(((note_m)[27] = 116));
  (void)(((note_m)[28] = 105));
  (void)(((note_m)[29] = 111));
  (void)(((note_m)[30] = 110));
  (void)(((note_m)[31] = 32));
  (void)(((note_m)[32] = 102));
  (void)(((note_m)[33] = 97));
  (void)(((note_m)[34] = 105));
  (void)(((note_m)[35] = 108));
  (void)(((note_m)[36] = 101));
  (void)(((note_m)[37] = 100));
  (void)(((note_m)[38] = 0));
  (void)(diag_report_with_code(import_path, 0, 0, &((kind)[0]), &((code)[0]), &((msg)[0]), ((uint8_t *)(0))));
  (void)(diag_report(((uint8_t *)(0)), 0, 0, &((note_k)[0]), &((note_m)[0]), ((uint8_t *)(0))));
}
void typeck_ndep_store(int32_t n) {
  int32_t v = n;
  if ((v > 32)) {
    (void)((v = 32));
  }
  if ((v < 0)) {
    (void)((v = 0));
  }
  (void)(typeck_ndep_store_impl(v));
}
void typeck_dep_module_set(int32_t i, uint8_t * mod) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(typeck_dep_module_set_impl(i, mod));
}
void typeck_dep_arena_set(int32_t i, uint8_t * arena) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(typeck_dep_arena_set_impl(i, arena));
}
void driver_dep_arena_ptr_set(int32_t i, uint8_t * arena) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(driver_dep_arena_ptr_set_impl(i, arena));
}
void driver_dep_module_ptr_set(int32_t i, uint8_t * module) {
  if ((i < 0)) {
    return;
  }
  if ((i >=32)) {
    return;
  }
  (void)(driver_dep_module_ptr_set_impl(i, module));
}
int32_t pipe_cstr_eq(uint8_t * a, uint8_t * b) {
  if ((a ==0)) {
    return 0;
  }
  if ((b ==0)) {
    return 0;
  }
  int32_t i = 0;
  while ((i < 4096)) {
    if (((a)[i] !=(b)[i])) {
      return 0;
    }
    if (((a)[i] ==0)) {
      return 1;
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
uint8_t * pipe_load_ptr_slot(uint8_t * base, int32_t i) {
  if ((base ==0)) {
    return ((uint8_t *)(0));
  }
  int32_t off = (i * 8);
  size_t m = 256;
  size_t m2 = (m * m);
  size_t m4 = (m2 * m2);
  size_t a = ((size_t)((base)[off]));
  (void)((a = (a + (((size_t)((base)[(off + 1)])) * m))));
  (void)((a = (a + (((size_t)((base)[(off + 2)])) * m2))));
  (void)((a = (a + (((size_t)((base)[(off + 3)])) * (m2 * m)))));
  (void)((a = (a + (((size_t)((base)[(off + 4)])) * m4))));
  (void)((a = (a + (((size_t)((base)[(off + 5)])) * (m4 * m)))));
  (void)((a = (a + (((size_t)((base)[(off + 6)])) * (m4 * m2)))));
  (void)((a = (a + (((size_t)((base)[(off + 7)])) * ((m4 * m2) * m)))));
  return ((uint8_t *)(a));
}
void pipe_store_ptr_slot(uint8_t * base, int32_t i, uint8_t * val) {
  if ((base ==0)) {
    return;
  }
  if ((i < 0)) {
    return;
  }
  int32_t off = (i * 8);
  {
    size_t m = 256;
    size_t b255 = 255;
    size_t u0 = ((size_t)(val));
    (void)(((base)[off] = ((uint8_t)((u0 & b255)))));
    size_t u1 = (u0 / m);
    (void)(((base)[(off + 1)] = ((uint8_t)((u1 & b255)))));
    size_t u2 = (u1 / m);
    (void)(((base)[(off + 2)] = ((uint8_t)((u2 & b255)))));
    size_t u3 = (u2 / m);
    (void)(((base)[(off + 3)] = ((uint8_t)((u3 & b255)))));
    size_t u4 = (u3 / m);
    (void)(((base)[(off + 4)] = ((uint8_t)((u4 & b255)))));
    size_t u5 = (u4 / m);
    (void)(((base)[(off + 5)] = ((uint8_t)((u5 & b255)))));
    size_t u6 = (u5 / m);
    (void)(((base)[(off + 6)] = ((uint8_t)((u6 & b255)))));
    size_t u7 = (u6 / m);
    (void)(((base)[(off + 7)] = ((uint8_t)((u7 & b255)))));
  }
}
int64_t xlang_size_slot_get(uint8_t * arr, int32_t i) {
  if ((arr ==0)) {
    return 0;
  }
  if ((i < 0)) {
    return 0;
  }
  uint8_t * p = pipe_load_ptr_slot(arr, i);
  return ((int64_t)(p));
}
void xlang_size_slot_set(uint8_t * arr, int32_t i, int64_t v) {
  if ((arr ==0)) {
    return;
  }
  if ((i < 0)) {
    return;
  }
  (void)(pipe_store_ptr_slot(arr, i, ((uint8_t *)(v))));
}
void xlang_ptr_slot_set(uint8_t * arr, int32_t i, uint8_t * p) {
  (void)(pipe_store_ptr_slot(arr, i, p));
}
uint8_t * xlang_ptr_slot_get(uint8_t * arr, int32_t i) {
  if ((arr ==0)) {
    return ((uint8_t *)(0));
  }
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  return pipe_load_ptr_slot(arr, i);
}
void xlang_i32_store(int32_t * p, int32_t v) {
  if ((p ==0)) {
    return;
  }
  (void)(((p)[0] = v));
}
int32_t xlang_module_num_imports(uint8_t * module) {
  if ((module ==0)) {
    return 0;
  }
  return parser_get_module_num_imports(module);
}
void xlang_module_import_path_cstr(uint8_t * module, int32_t idx, uint8_t * buf, int32_t cap) {
  if ((buf ==0)) {
    return;
  }
  if ((cap <=0)) {
    return;
  }
  (void)(((buf)[0] = 0));
  if ((module ==0)) {
    return;
  }
  uint8_t path_buf[128] = {};
  (void)(parser_get_module_import_path(module, idx, &((path_buf)[0])));
  int32_t k = 0;
  while ((k < 64)) {
    uint8_t ch = 0;
    (void)((ch = (path_buf)[k]));
    if ((ch ==0)) {
      break;
    }
    if (((k + 1) >=cap)) {
      break;
    }
    (void)(((buf)[k] = ch));
    (void)((k = (k + 1)));
  }
  (void)(((buf)[k] = 0));
}
int32_t xlang_collect_to_load_has(uint8_t * to_load, int32_t to_load_n, uint8_t * path) {
  if ((to_load ==0)) {
    return 0;
  }
  if ((path ==0)) {
    return 0;
  }
  if ((to_load_n <=0)) {
    return 0;
  }
  int32_t t = 0;
  while ((t < to_load_n)) {
    uint8_t * p = pipe_load_ptr_slot(to_load, t);
    if ((p !=0)) {
      if ((pipe_cstr_eq(p, path) !=0)) {
        return 1;
      }
    }
    (void)((t = (t + 1)));
  }
  return 0;
}
uint8_t * xlang_collect_strdup(uint8_t * s) {
  if ((s ==0)) {
    return ((uint8_t *)(0));
  }
  int32_t n = 0;
  while (((s)[n] !=0)) {
    (void)((n = (n + 1)));
  }
  uint8_t * out = 0;
  (void)((out = malloc(((size_t)((n + 1))))));
  if ((out ==0)) {
    return ((uint8_t *)(0));
  }
  int32_t i = 0;
  while ((i < n)) {
    (void)(((out)[i] = (s)[i]));
    (void)((i = (i + 1)));
  }
  (void)(((out)[n] = 0));
  return out;
}
int32_t xlang_collect_seed_to_load(uint8_t * module, uint8_t * to_load, int32_t * to_load_n) {
  if ((to_load ==0)) {
    return 1;
  }
  if ((to_load_n ==0)) {
    return 1;
  }
  (void)(((to_load_n)[0] = 0));
  if ((module ==0)) {
    return 0;
  }
  int32_t slot_max = 32;
  int32_t n_imports = xlang_module_num_imports(module);
  int32_t j = 0;
  while ((j < n_imports)) {
    if ((j >=slot_max)) {
      break;
    }
    int32_t n = 0;
    (void)((n = (to_load_n)[0]));
    if ((n >=slot_max)) {
      break;
    }
    uint8_t path_c[65] = {};
    (void)(xlang_module_import_path_cstr(module, j, &((path_c)[0]), 65));
    uint8_t * owned = 0;
    (void)((owned = xlang_collect_strdup(&((path_c)[0]))));
    if ((owned ==0)) {
      while ((n > 0)) {
        (void)((n = (n - 1)));
        uint8_t * p = pipe_load_ptr_slot(to_load, n);
        if ((p !=0)) {
          (void)(free(p));
        }
        (void)(pipe_store_ptr_slot(to_load, n, 0));
      }
      (void)(((to_load_n)[0] = 0));
      return 1;
    }
    (void)(pipe_store_ptr_slot(to_load, n, owned));
    (void)(((to_load_n)[0] = (n + 1)));
    (void)((j = (j + 1)));
  }
  return 0;
}
void xlang_collect_tmp_parse_and_enqueue(uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz, uint8_t * prep, int64_t prep_len, uint8_t * debug_path, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded) {
  if ((tmp_arena ==0)) {
    return;
  }
  if ((tmp_module ==0)) {
    return;
  }
  if ((prep ==0)) {
    return;
  }
  if ((debug_path ==0)) {
  }
  uint8_t * ta = pipe_load_ptr_slot(tmp_arena, 0);
  uint8_t * tm = pipe_load_ptr_slot(tmp_module, 0);
  if ((ta ==0)) {
    (void)((ta = malloc(((size_t)(arena_sz)))));
    (void)((tm = malloc(((size_t)(module_sz)))));
    (void)(pipe_store_ptr_slot(tmp_arena, 0, ta));
    (void)(pipe_store_ptr_slot(tmp_module, 0, tm));
  }
  if ((ta ==0)) {
    return;
  }
  if ((tm ==0)) {
    return;
  }
  (void)(memset(ta, 0, ((size_t)(arena_sz))));
  (void)(memset(tm, 0, ((size_t)(module_sz))));
  (void)(parser_parse_into_init(tm, ta));
  (void)(xlang_module_collect_imports_from_buf(tm, prep, prep_len));
  (void)(xlang_collect_enqueue_module_imports(tm, to_load, to_load_n, dep_paths, n_loaded));
}
int32_t xlang_collect_paths_tmp_resolve_parse_enqueue(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded) {
  if ((path_c ==0)) {
    return 1;
  }
  if ((tmp_arena ==0)) {
    return 1;
  }
  if ((tmp_module ==0)) {
    return 1;
  }
  uint8_t * ta = pipe_load_ptr_slot(tmp_arena, 0);
  if ((ta ==0)) {
    uint8_t * tm_new = 0;
    (void)((ta = malloc(((size_t)(arena_sz)))));
    (void)((tm_new = malloc(((size_t)(module_sz)))));
    (void)(pipe_store_ptr_slot(tmp_arena, 0, ta));
    (void)(pipe_store_ptr_slot(tmp_module, 0, tm_new));
  }
  (void)((ta = pipe_load_ptr_slot(tmp_arena, 0)));
  uint8_t * tm = pipe_load_ptr_slot(tmp_module, 0);
  if ((ta ==0)) {
    return 0;
  }
  if ((tm ==0)) {
    return 0;
  }
  uint8_t prep_cell[8] = {};
  uint8_t prep_len_cell[8] = {};
  int32_t rc = 0;
  (void)((rc = xlang_load_one_direct_resolve_read_preprocess(lib_roots, n_lib_roots, entry_dir, path_c, defines, ndefines, &((prep_cell)[0]), &((prep_len_cell)[0]))));
  if ((rc !=0)) {
    return 1;
  }
  uint8_t * prep = pipe_load_ptr_slot(&((prep_cell)[0]), 0);
  int64_t prep_len = xlang_size_slot_get(&((prep_len_cell)[0]), 0);
  (void)(xlang_collect_tmp_parse_and_enqueue(tmp_arena, tmp_module, arena_sz, module_sz, prep, prep_len, path_c, to_load, to_load_n, dep_paths, n_loaded));
  if ((prep !=0)) {
    (void)(free(prep));
  }
  return 0;
}
int32_t xlang_collect_deps_process_one(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n, uint8_t * to_load, int32_t * to_load_n, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz) {
  if ((path_c ==0)) {
    return 1;
  }
  if ((n ==0)) {
    return 1;
  }
  if ((to_load ==0)) {
    return 1;
  }
  if ((to_load_n ==0)) {
    return 1;
  }
  if ((tmp_arena ==0)) {
    return 1;
  }
  if ((tmp_module ==0)) {
    return 1;
  }
  int32_t mi = 0;
  (void)((mi = (n)[0]));
  if ((xlang_find_loaded_import_index(path_c, dep_paths, mi) >=0)) {
    (void)(free(path_c));
    return 0;
  }
  int32_t rc = 0;
  (void)((rc = xlang_load_one_direct_import_at(lib_roots, n_lib_roots, entry_dir, path_c, defines, ndefines, dep_sources, dep_lens, dep_paths, mi)));
  (void)(free(path_c));
  if ((rc !=0)) {
    return 1;
  }
  uint8_t * key = pipe_load_ptr_slot(dep_paths, mi);
  if ((key ==0)) {
    return 1;
  }
  (void)(((n)[0] = (mi + 1)));
  uint8_t * prep = pipe_load_ptr_slot(dep_sources, mi);
  int64_t prep_len = xlang_size_slot_get(dep_lens, mi);
  int32_t n_loaded = (mi + 1);
  (void)(xlang_collect_tmp_parse_and_enqueue(tmp_arena, tmp_module, arena_sz, module_sz, prep, prep_len, key, to_load, to_load_n, dep_paths, n_loaded));
  return 0;
}
int32_t xlang_collect_paths_process_one(uint8_t * path_c, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n, uint8_t * to_load, int32_t * to_load_n, uint8_t * tmp_arena, uint8_t * tmp_module, int64_t arena_sz, int64_t module_sz) {
  if ((path_c ==0)) {
    return 1;
  }
  if ((n ==0)) {
    return 1;
  }
  if ((to_load ==0)) {
    return 1;
  }
  if ((to_load_n ==0)) {
    return 1;
  }
  if ((tmp_arena ==0)) {
    return 1;
  }
  if ((tmp_module ==0)) {
    return 1;
  }
  int32_t mi = 0;
  (void)((mi = (n)[0]));
  if ((xlang_find_loaded_import_index(path_c, dep_paths, mi) >=0)) {
    (void)(free(path_c));
    return 0;
  }
  uint8_t * key = 0;
  (void)((key = xlang_collect_strdup(path_c)));
  if ((key ==0)) {
    (void)(free(path_c));
    return 1;
  }
  (void)(pipe_store_ptr_slot(dep_paths, mi, key));
  (void)(((n)[0] = (mi + 1)));
  int32_t n_loaded = (mi + 1);
  int32_t rc = 0;
  (void)((rc = xlang_collect_paths_tmp_resolve_parse_enqueue(path_c, lib_roots, n_lib_roots, entry_dir, defines, ndefines, tmp_arena, tmp_module, arena_sz, module_sz, to_load, to_load_n, dep_paths, n_loaded)));
  (void)(free(path_c));
  return rc;
}
int32_t xlang_collect_deps_transitive_impl(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_sources, uint8_t * dep_lens, uint8_t * dep_paths, int32_t * n_deps) {
  if ((n_deps ==0)) {
    return 1;
  }
  uint8_t to_load[256] = {};
  int32_t z = 0;
  while ((z < 256)) {
    (void)(((to_load)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t to_load_n = 0;
  uint8_t tmp_cells[16] = {};
  (void)((z = 0));
  while ((z < 16)) {
    (void)(((tmp_cells)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t n = 0;
  int32_t slot_max = 32;
  if ((xlang_collect_seed_to_load(module, &((to_load)[0]), &(to_load_n)) !=0)) {
    while ((to_load_n > 0)) {
      (void)((to_load_n = (to_load_n - 1)));
      uint8_t * p = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
      if ((p !=0)) {
        (void)(free(p));
      }
      (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
    }
    return 1;
  }
  while ((to_load_n > 0)) {
    if ((n >=slot_max)) {
      break;
    }
    (void)((to_load_n = (to_load_n - 1)));
    uint8_t * path_c = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
    (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
    int32_t rc = 0;
    (void)((rc = xlang_collect_deps_process_one(path_c, lib_roots, n_lib_roots, entry_dir, defines, ndefines, dep_sources, dep_lens, dep_paths, &(n), &((to_load)[0]), &(to_load_n), &((tmp_cells)[0]), &((tmp_cells)[8]), arena_sz, module_sz)));
    if ((rc !=0)) {
      while ((to_load_n > 0)) {
        (void)((to_load_n = (to_load_n - 1)));
        uint8_t * p2 = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
        if ((p2 !=0)) {
          (void)(free(p2));
        }
        (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
      }
      uint8_t * ta = pipe_load_ptr_slot(&((tmp_cells)[0]), 0);
      uint8_t * tm = pipe_load_ptr_slot(&((tmp_cells)[0]), 1);
      if ((ta !=0)) {
        (void)(free(ta));
      }
      if ((tm !=0)) {
        (void)(free(tm));
      }
      while ((n > 0)) {
        (void)((n = (n - 1)));
        uint8_t * s = pipe_load_ptr_slot(dep_sources, n);
        uint8_t * k = pipe_load_ptr_slot(dep_paths, n);
        if ((s !=0)) {
          (void)(free(s));
        }
        if ((k !=0)) {
          (void)(free(k));
        }
        (void)(pipe_store_ptr_slot(dep_sources, n, 0));
        (void)(pipe_store_ptr_slot(dep_paths, n, 0));
      }
      return 1;
    }
  }
  while ((to_load_n > 0)) {
    (void)((to_load_n = (to_load_n - 1)));
    uint8_t * p3 = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
    if ((p3 !=0)) {
      (void)(free(p3));
    }
    (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
  }
  uint8_t * ta_ok = pipe_load_ptr_slot(&((tmp_cells)[0]), 0);
  uint8_t * tm_ok = pipe_load_ptr_slot(&((tmp_cells)[0]), 1);
  if ((ta_ok !=0)) {
    (void)(free(ta_ok));
  }
  if ((tm_ok !=0)) {
    (void)(free(tm_ok));
  }
  (void)(xlang_i32_store(n_deps, n));
  return 0;
}
int32_t xlang_collect_dep_paths_transitive_impl(uint8_t * module, int64_t arena_sz, int64_t module_sz, uint8_t * lib_roots, int32_t n_lib_roots, uint8_t * entry_dir, uint8_t * defines, int32_t ndefines, uint8_t * dep_paths, int32_t * n_deps) {
  if ((n_deps ==0)) {
    return 1;
  }
  uint8_t to_load[256] = {};
  int32_t z = 0;
  while ((z < 256)) {
    (void)(((to_load)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t to_load_n = 0;
  uint8_t tmp_cells[16] = {};
  (void)((z = 0));
  while ((z < 16)) {
    (void)(((tmp_cells)[z] = 0));
    (void)((z = (z + 1)));
  }
  int32_t n = 0;
  int32_t slot_max = 32;
  if ((xlang_collect_seed_to_load(module, &((to_load)[0]), &(to_load_n)) !=0)) {
    while ((to_load_n > 0)) {
      (void)((to_load_n = (to_load_n - 1)));
      uint8_t * p = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
      if ((p !=0)) {
        (void)(free(p));
      }
      (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
    }
    return 1;
  }
  while ((to_load_n > 0)) {
    if ((n >=slot_max)) {
      break;
    }
    (void)((to_load_n = (to_load_n - 1)));
    uint8_t * path_c = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
    (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
    int32_t rc = 0;
    (void)((rc = xlang_collect_paths_process_one(path_c, lib_roots, n_lib_roots, entry_dir, defines, ndefines, dep_paths, &(n), &((to_load)[0]), &(to_load_n), &((tmp_cells)[0]), &((tmp_cells)[8]), arena_sz, module_sz)));
    if ((rc !=0)) {
      while ((to_load_n > 0)) {
        (void)((to_load_n = (to_load_n - 1)));
        uint8_t * p2 = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
        if ((p2 !=0)) {
          (void)(free(p2));
        }
        (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
      }
      uint8_t * ta = pipe_load_ptr_slot(&((tmp_cells)[0]), 0);
      uint8_t * tm = pipe_load_ptr_slot(&((tmp_cells)[0]), 1);
      if ((ta !=0)) {
        (void)(free(ta));
      }
      if ((tm !=0)) {
        (void)(free(tm));
      }
      while ((n > 0)) {
        (void)((n = (n - 1)));
        uint8_t * k = pipe_load_ptr_slot(dep_paths, n);
        if ((k !=0)) {
          (void)(free(k));
        }
        (void)(pipe_store_ptr_slot(dep_paths, n, 0));
      }
      return 1;
    }
  }
  while ((to_load_n > 0)) {
    (void)((to_load_n = (to_load_n - 1)));
    uint8_t * p3 = pipe_load_ptr_slot(&((to_load)[0]), to_load_n);
    if ((p3 !=0)) {
      (void)(free(p3));
    }
    (void)(pipe_store_ptr_slot(&((to_load)[0]), to_load_n, 0));
  }
  uint8_t * ta_ok = pipe_load_ptr_slot(&((tmp_cells)[0]), 0);
  uint8_t * tm_ok = pipe_load_ptr_slot(&((tmp_cells)[0]), 1);
  if ((ta_ok !=0)) {
    (void)(free(ta_ok));
  }
  if ((tm_ok !=0)) {
    (void)(free(tm_ok));
  }
  (void)(xlang_i32_store(n_deps, n));
  return 0;
}
void xlang_collect_enqueue_module_imports(uint8_t * tmp_module, uint8_t * to_load, int32_t * to_load_n, uint8_t * dep_paths, int32_t n_loaded) {
  if ((tmp_module ==0)) {
    return;
  }
  if ((to_load ==0)) {
    return;
  }
  if ((to_load_n ==0)) {
    return;
  }
  int32_t slot_max = 32;
  int32_t n_imp = 0;
  (void)((n_imp = parser_get_module_num_imports(tmp_module)));
  if ((n_imp <=0)) {
    return;
  }
  int32_t jj = 0;
  while ((jj < n_imp)) {
    if ((jj >=slot_max)) {
      break;
    }
    int32_t n = 0;
    (void)((n = (to_load_n)[0]));
    if ((n >=slot_max)) {
      break;
    }
    uint8_t sub_c[65] = {};
    (void)(xlang_module_import_path_cstr(tmp_module, jj, &((sub_c)[0]), 65));
    if ((xlang_find_loaded_import_index(&((sub_c)[0]), dep_paths, n_loaded) >=0)) {
      (void)((jj = (jj + 1)));
      continue;
    }
    if ((xlang_collect_to_load_has(to_load, n, &((sub_c)[0])) !=0)) {
      (void)((jj = (jj + 1)));
      continue;
    }
    uint8_t * owned = 0;
    (void)((owned = xlang_collect_strdup(&((sub_c)[0]))));
    if ((owned ==0)) {
      (void)((jj = (jj + 1)));
      continue;
    }
    (void)(pipe_store_ptr_slot(to_load, n, owned));
    (void)(((to_load_n)[0] = (n + 1)));
    (void)((jj = (jj + 1)));
  }
}
void pipeline_diag_preprocess_directive_code(uint8_t * path_diag, int32_t code) {
  if ((code !=-2)) {
    if ((code !=-3)) {
      if ((code !=-4)) {
        if ((code !=-5)) {
          if ((code !=-6)) {
            if ((code !=-7)) {
              (void)(pipeline_diag_preprocess_fail(path_diag));
              return;
            }
          }
        }
      }
    }
  }
  (void)(pipeline_diag_emitted_note());
  uint8_t kind[24] = {};
  uint8_t dcode[8] = {};
  (void)(((kind)[0] = 112));
  (void)(((kind)[1] = 114));
  (void)(((kind)[2] = 101));
  (void)(((kind)[3] = 112));
  (void)(((kind)[4] = 114));
  (void)(((kind)[5] = 111));
  (void)(((kind)[6] = 99));
  (void)(((kind)[7] = 101));
  (void)(((kind)[8] = 115));
  (void)(((kind)[9] = 115));
  (void)(((kind)[10] = 32));
  (void)(((kind)[11] = 101));
  (void)(((kind)[12] = 114));
  (void)(((kind)[13] = 114));
  (void)(((kind)[14] = 111));
  (void)(((kind)[15] = 114));
  (void)(((kind)[16] = 0));
  (void)(((dcode)[0] = 80));
  (void)(((dcode)[1] = 80));
  (void)(((dcode)[2] = 48));
  (void)(((dcode)[3] = 48));
  (void)(((dcode)[4] = 50));
  (void)(((dcode)[5] = 0));
  uint8_t msg[32] = {};
  if ((code ==-2)) {
    (void)(((msg)[0] = 35));
    (void)(((msg)[1] = 101));
    (void)(((msg)[2] = 108));
    (void)(((msg)[3] = 115));
    (void)(((msg)[4] = 101));
    (void)(((msg)[5] = 32));
    (void)(((msg)[6] = 119));
    (void)(((msg)[7] = 105));
    (void)(((msg)[8] = 116));
    (void)(((msg)[9] = 104));
    (void)(((msg)[10] = 111));
    (void)(((msg)[11] = 117));
    (void)(((msg)[12] = 116));
    (void)(((msg)[13] = 32));
    (void)(((msg)[14] = 35));
    (void)(((msg)[15] = 105));
    (void)(((msg)[16] = 102));
    (void)(((msg)[17] = 0));
  } else {
    if ((code ==-3)) {
      (void)(((msg)[0] = 35));
      (void)(((msg)[1] = 101));
      (void)(((msg)[2] = 110));
      (void)(((msg)[3] = 100));
      (void)(((msg)[4] = 105));
      (void)(((msg)[5] = 102));
      (void)(((msg)[6] = 32));
      (void)(((msg)[7] = 119));
      (void)(((msg)[8] = 105));
      (void)(((msg)[9] = 116));
      (void)(((msg)[10] = 104));
      (void)(((msg)[11] = 111));
      (void)(((msg)[12] = 117));
      (void)(((msg)[13] = 116));
      (void)(((msg)[14] = 32));
      (void)(((msg)[15] = 35));
      (void)(((msg)[16] = 105));
      (void)(((msg)[17] = 102));
      (void)(((msg)[18] = 0));
    } else {
      if ((code ==-4)) {
        (void)(((msg)[0] = 35));
        (void)(((msg)[1] = 101));
        (void)(((msg)[2] = 108));
        (void)(((msg)[3] = 115));
        (void)(((msg)[4] = 101));
        (void)(((msg)[5] = 105));
        (void)(((msg)[6] = 102));
        (void)(((msg)[7] = 32));
        (void)(((msg)[8] = 119));
        (void)(((msg)[9] = 105));
        (void)(((msg)[10] = 116));
        (void)(((msg)[11] = 104));
        (void)(((msg)[12] = 111));
        (void)(((msg)[13] = 117));
        (void)(((msg)[14] = 116));
        (void)(((msg)[15] = 32));
        (void)(((msg)[16] = 35));
        (void)(((msg)[17] = 105));
        (void)(((msg)[18] = 102));
        (void)(((msg)[19] = 0));
      } else {
        if ((code ==-5)) {
          (void)(((msg)[0] = 35));
          (void)(((msg)[1] = 101));
          (void)(((msg)[2] = 108));
          (void)(((msg)[3] = 115));
          (void)(((msg)[4] = 101));
          (void)(((msg)[5] = 105));
          (void)(((msg)[6] = 102));
          (void)(((msg)[7] = 32));
          (void)(((msg)[8] = 97));
          (void)(((msg)[9] = 102));
          (void)(((msg)[10] = 116));
          (void)(((msg)[11] = 101));
          (void)(((msg)[12] = 114));
          (void)(((msg)[13] = 32));
          (void)(((msg)[14] = 35));
          (void)(((msg)[15] = 101));
          (void)(((msg)[16] = 108));
          (void)(((msg)[17] = 115));
          (void)(((msg)[18] = 101));
          (void)(((msg)[19] = 0));
        } else {
          if ((code ==-6)) {
            (void)(((msg)[0] = 100));
            (void)(((msg)[1] = 117));
            (void)(((msg)[2] = 112));
            (void)(((msg)[3] = 108));
            (void)(((msg)[4] = 105));
            (void)(((msg)[5] = 99));
            (void)(((msg)[6] = 97));
            (void)(((msg)[7] = 116));
            (void)(((msg)[8] = 101));
            (void)(((msg)[9] = 32));
            (void)(((msg)[10] = 35));
            (void)(((msg)[11] = 101));
            (void)(((msg)[12] = 108));
            (void)(((msg)[13] = 115));
            (void)(((msg)[14] = 101));
            (void)(((msg)[15] = 0));
          } else {
            (void)(((msg)[0] = 35));
            (void)(((msg)[1] = 105));
            (void)(((msg)[2] = 102));
            (void)(((msg)[3] = 32));
            (void)(((msg)[4] = 110));
            (void)(((msg)[5] = 101));
            (void)(((msg)[6] = 115));
            (void)(((msg)[7] = 116));
            (void)(((msg)[8] = 105));
            (void)(((msg)[9] = 110));
            (void)(((msg)[10] = 103));
            (void)(((msg)[11] = 32));
            (void)(((msg)[12] = 116));
            (void)(((msg)[13] = 111));
            (void)(((msg)[14] = 111));
            (void)(((msg)[15] = 32));
            (void)(((msg)[16] = 100));
            (void)(((msg)[17] = 101));
            (void)(((msg)[18] = 101));
            (void)(((msg)[19] = 112));
            (void)(((msg)[20] = 0));
          }
        }
      }
    }
  }
  (void)(diag_report_with_code(path_diag, 0, 0, &((kind)[0]), &((dcode)[0]), &((msg)[0]), 0));
}
uint8_t * xlang_dep_prerun_entry_dir_pick(uint8_t * main_entry_dir, uint8_t * lib_roots, int32_t n_lib_roots) {
  if ((lib_roots ==0)) {
    return main_entry_dir;
  }
  if ((n_lib_roots <=0)) {
    return main_entry_dir;
  }
  {
    uint8_t * r0 = pipe_load_ptr_slot(lib_roots, 0);
    if ((r0 !=0)) {
      if (((r0)[0] !=0)) {
        return r0;
      }
    }
  }
  return main_entry_dir;
}
int32_t xlang_find_loaded_import_index_scan(uint8_t * path, uint8_t * all_paths, int32_t n_all) {
  if ((path ==0)) {
    return -1;
  }
  if ((all_paths ==0)) {
    return -1;
  }
  if ((n_all <=0)) {
    return -1;
  }
  int32_t i = 0;
  while ((i < n_all)) {
    uint8_t * p = pipe_load_ptr_slot(all_paths, i);
    if ((p !=0)) {
      if ((pipe_cstr_eq(p, path) !=0)) {
        return i;
      }
    }
    (void)((i = (i + 1)));
  }
  return -1;
}
int32_t xlang_merge_deps_path_already_out_scan(uint8_t * path, uint8_t * out_paths, int32_t n_out) {
  if ((path ==0)) {
    return 0;
  }
  if ((out_paths ==0)) {
    return 0;
  }
  if ((n_out <=0)) {
    return 0;
  }
  int32_t j = 0;
  while ((j < n_out)) {
    uint8_t * p = pipe_load_ptr_slot(out_paths, j);
    if ((p !=0)) {
      if ((pipe_cstr_eq(p, path) !=0)) {
        return 1;
      }
    }
    (void)((j = (j + 1)));
  }
  return 0;
}
void xlang_pipeline_pctx_update_dep_slots_no_reset(uint8_t * ctx, uint8_t * dep_mods, uint8_t * dep_ars, uint8_t * import_paths, int32_t n) {
  if ((ctx ==0)) {
    return;
  }
  int32_t i = 0;
  while ((i < n)) {
    {
      uint8_t * m = 0;
      uint8_t * a = 0;
      if ((dep_mods !=0)) {
        (void)((m = pipe_load_ptr_slot(dep_mods, i)));
      }
      if ((dep_ars !=0)) {
        (void)((a = pipe_load_ptr_slot(dep_ars, i)));
      }
      (void)(ast_pipeline_dep_ctx_set_module(ctx, i, m));
      (void)(ast_pipeline_dep_ctx_set_arena(ctx, i, a));
      if ((import_paths !=0)) {
        uint8_t * p = pipe_load_ptr_slot(import_paths, i);
        if ((p !=0)) {
          int32_t pl = pipe_cstr_len(p);
          (void)(ast_pipeline_dep_ctx_set_import_path(ctx, i, p, pl));
        }
      }
    }
    (void)((i = (i + 1)));
  }
  (void)(ast_pipeline_dep_ctx_set_ndep(ctx, n));
}
uint8_t * pipeline_run_x_thread_fn_impl(uint8_t * arg) {
  if ((arg ==0)) {
    return ((uint8_t *)(0));
  }
  uint8_t * module = pipe_load_ptr_slot(arg, 0);
  uint8_t * arena = pipe_load_ptr_slot(arg, 1);
  uint8_t * source_data = pipe_load_ptr_slot(arg, 2);
  int64_t source_len = xlang_size_slot_get(arg, 3);
  uint8_t * out_buf = pipe_load_ptr_slot(arg, 4);
  uint8_t * ctx = pipe_load_ptr_slot(arg, 5);
  (void)(driver_set_pipeline_entry_source_len(source_len));
  int32_t ec = 0;
  (void)((ec = pipeline_run_x_pipeline(module, arena, source_data, source_len, out_buf, ctx)));
  (void)(xlang_size_slot_set(arg, 6, ((int64_t)(ec))));
  return ((uint8_t *)(0));
}
uint8_t * pipeline_run_x_thread_fn(uint8_t * arg) {
  if ((arg ==0)) {
    return ((uint8_t *)(0));
  }
  return pipeline_run_x_thread_fn_impl(arg);
  return ((uint8_t *)(0));
}
uint8_t * pipeline_run_x_thread_fn_ptr(void) {
  return ((uint8_t *)(pipeline_run_x_thread_fn));
}
int32_t xlang_pipeline_run_x_pipeline_large_stack_impl(uint8_t * module, uint8_t * arena, uint8_t * source_data, int64_t source_len, uint8_t * out_buf, uint8_t * ctx) {
  uint8_t args[56] = {};
  int32_t zi = 0;
  while ((zi < 56)) {
    (void)(((args)[zi] = 0));
    (void)((zi = (zi + 1)));
  }
  (void)(driver_set_pipeline_entry_source_len(source_len));
  (void)(pipe_store_ptr_slot(&((args)[0]), 0, module));
  (void)(pipe_store_ptr_slot(&((args)[0]), 1, arena));
  (void)(pipe_store_ptr_slot(&((args)[0]), 2, source_data));
  (void)(xlang_size_slot_set(&((args)[0]), 3, source_len));
  (void)(pipe_store_ptr_slot(&((args)[0]), 4, out_buf));
  (void)(pipe_store_ptr_slot(&((args)[0]), 5, ctx));
  (void)(xlang_size_slot_set(&((args)[0]), 6, -99));
  uint8_t * fn = 0;
  (void)((fn = pipeline_run_x_thread_fn_ptr()));
  if ((fn !=0)) {
    (void)(driver_run_thread_on_large_stack(fn, &((args)[0])));
  }
  int64_t result = xlang_size_slot_get(&((args)[0]), 6);
  if ((result ==-99)) {
    return pipeline_run_x_pipeline(module, arena, source_data, source_len, out_buf, ctx);
  }
  return ((int32_t)(result));
}
uint8_t * xlang_asm_codegen_elf_o_thread_fn(uint8_t * arg) {
  if ((arg ==0)) {
    return ((uint8_t *)(0));
  }
  return xlang_asm_codegen_elf_o_thread_fn_impl(arg);
  return ((uint8_t *)(0));
}
uint8_t * xlang_asm_codegen_elf_o_thread_fn_ptr(void) {
  return ((uint8_t *)(xlang_asm_codegen_elf_o_thread_fn));
}
uint8_t * xlang_asm_codegen_elf_o_thread_fn_impl(uint8_t * arg) {
  if ((arg ==0)) {
    return ((uint8_t *)(0));
  }
  uint8_t * module = pipe_load_ptr_slot(arg, 0);
  uint8_t * arena = pipe_load_ptr_slot(arg, 1);
  uint8_t * ctx = pipe_load_ptr_slot(arg, 2);
  uint8_t * elf_ctx = pipe_load_ptr_slot(arg, 3);
  uint8_t * out_buf = pipe_load_ptr_slot(arg, 4);
  int32_t ec = 0;
  (void)((ec = xlang_asm_codegen_elf_o_product_emit(module, arena, ctx, elf_ctx, out_buf)));
  (void)(xlang_size_slot_set(arg, 5, ((int64_t)(ec))));
  return ((uint8_t *)(0));
}
int32_t xlang_asm_codegen_elf_o_large_stack_impl(uint8_t * module, uint8_t * arena, uint8_t * ctx, uint8_t * elf_ctx, uint8_t * out_buf) {
  uint8_t args[48] = {};
  int32_t zi = 0;
  while ((zi < 48)) {
    (void)(((args)[zi] = 0));
    (void)((zi = (zi + 1)));
  }
  (void)(pipe_store_ptr_slot(&((args)[0]), 0, module));
  (void)(pipe_store_ptr_slot(&((args)[0]), 1, arena));
  (void)(pipe_store_ptr_slot(&((args)[0]), 2, ctx));
  (void)(pipe_store_ptr_slot(&((args)[0]), 3, elf_ctx));
  (void)(pipe_store_ptr_slot(&((args)[0]), 4, out_buf));
  (void)(xlang_size_slot_set(&((args)[0]), 5, -99));
  uint8_t * fn = 0;
  (void)((fn = xlang_asm_codegen_elf_o_thread_fn_ptr()));
  if ((fn !=0)) {
    (void)(driver_run_thread_on_large_stack(fn, &((args)[0])));
  }
  int64_t result = xlang_size_slot_get(&((args)[0]), 5);
  if ((result ==-99)) {
    return xlang_asm_codegen_elf_o_product_emit(module, arena, ctx, elf_ctx, out_buf);
  }
  return ((int32_t)(result));
}
int32_t pipeline_asm_debug_enabled(void) {
  {
    uint8_t * e = link_abi_getenv(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x41\x53\x4d\x5f\x44\x45\x42\x55\x47"));
    if ((e !=0)) {
      return 1;
    }
  }
  return 0;
}
int32_t pipeline_debug_body_func_match(uint8_t * filter, uint8_t * name) {
  if ((filter ==0)) {
    return 0;
  }
  if (((filter)[0] ==0)) {
    return 0;
  }
  if (((filter)[0] ==48)) {
    return 0;
  }
  if ((name ==0)) {
    return 0;
  }
  if (((name)[0] ==0)) {
    return 0;
  }
  int32_t name_len = 0;
  while ((name_len < 512)) {
    if (((name)[name_len] ==0)) {
      break;
    }
    (void)((name_len = (name_len + 1)));
  }
  int32_t p = 0;
  while ((p < 4096)) {
    uint8_t c = (filter)[p];
    if ((c ==0)) {
      break;
    }
    while ((p < 4096)) {
      (void)((c = (filter)[p]));
      if ((c ==0)) {
        break;
      }
      if ((c ==32)) {
        (void)((p = (p + 1)));
        continue;
      }
      if ((c ==9)) {
        (void)((p = (p + 1)));
        continue;
      }
      if ((c ==44)) {
        (void)((p = (p + 1)));
        continue;
      }
      break;
    }
    (void)((c = (filter)[p]));
    if ((c ==0)) {
      break;
    }
    int32_t start = p;
    while ((p < 4096)) {
      (void)((c = (filter)[p]));
      if ((c ==0)) {
        break;
      }
      if ((c ==44)) {
        break;
      }
      (void)((p = (p + 1)));
    }
    int32_t end = p;
    while ((end > start)) {
      uint8_t pc = (filter)[(end - 1)];
      if ((pc ==32)) {
        (void)((end = (end - 1)));
        continue;
      }
      if ((pc ==9)) {
        (void)((end = (end - 1)));
        continue;
      }
      break;
    }
    int32_t tok_len = (end - start);
    if ((tok_len > 0)) {
      if ((tok_len ==name_len)) {
        int32_t k = 0;
        int32_t eq = 1;
        while ((k < tok_len)) {
          if (((filter)[(start + k)] !=(name)[k])) {
            (void)((eq = 0));
            break;
          }
          (void)((k = (k + 1)));
        }
        if ((eq !=0)) {
          return 1;
        }
      }
    }
  }
  return 0;
}
int32_t pipe_imp_entry_size(void) {
  return 340;
}
int32_t pipe_imp_off_num_imports(void) {
  return 8;
}
void pipe_imp_set_header_n(uint8_t * module, int32_t n) {
  if ((module ==0)) {
    return;
  }
  (void)(pipe_store_i32_le(module, pipe_imp_off_num_imports(), n));
}
int32_t pipe_imp_get_header_n(uint8_t * module) {
  if ((module ==0)) {
    return 0;
  }
  return pipe_load_i32_le(module, pipe_imp_off_num_imports());
}
int32_t pipe_imp_find_slot(uint8_t * module) {
  if ((module ==0)) {
    return -1;
  }
  int32_t i = 0;
  while ((i < 128)) {
    uint8_t * k = xlang_ptr_slot_get(&((g_pipe_imp_mod)[0]), i);
    if ((k ==module)) {
      return i;
    }
    (void)((i = (i + 1)));
  }
  return -1;
}
void pipe_imp_soft_sync(uint8_t * module) {
  if ((module ==0)) {
    return;
  }
  if ((pipe_imp_get_header_n(module) !=0)) {
    return;
  }
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  (void)(((g_pipe_imp_n)[s] = 0));
  (void)(((g_pipe_imp_sel_n)[s] = 0));
}
int32_t pipe_imp_find_or_create(uint8_t * module) {
  if ((module ==0)) {
    return -1;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t found = pipe_imp_find_slot(module);
  if ((found >=0)) {
    return found;
  }
  int32_t i = 0;
  while ((i < 128)) {
    uint8_t * k = xlang_ptr_slot_get(&((g_pipe_imp_mod)[0]), i);
    if ((k ==0)) {
      (void)(xlang_ptr_slot_set(&((g_pipe_imp_mod)[0]), i, module));
      (void)(((g_pipe_imp_n)[i] = 0));
      (void)(((g_pipe_imp_cap)[i] = 0));
      (void)(((g_pipe_imp_sel_n)[i] = 0));
      (void)(((g_pipe_imp_sel_cap)[i] = 0));
      (void)(xlang_ptr_slot_set(&((g_pipe_imp_entries)[0]), i, 0));
      (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_rows)[0]), i, 0));
      (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_lens)[0]), i, 0));
      return i;
    }
    (void)((i = (i + 1)));
  }
  return -1;
}
int32_t pipe_imp_ensure_entries(int32_t slot, int32_t need) {
  if ((slot < 0)) {
    return 0;
  }
  if ((slot >=128)) {
    return 0;
  }
  if ((need <=0)) {
    return 1;
  }
  int32_t cap = (g_pipe_imp_cap)[slot];
  if ((cap >=need)) {
    return 1;
  }
  int32_t new_cap = cap;
  if ((new_cap < 8)) {
    (void)((new_cap = 8));
  }
  while ((new_cap < need)) {
    (void)((new_cap = (new_cap * 2)));
  }
  int32_t esz = pipe_imp_entry_size();
  size_t nbytes = ((size_t)((new_cap * esz)));
  uint8_t * np = 0;
  (void)((np = malloc(nbytes)));
  if ((np ==0)) {
    return 0;
  }
  (void)(memset(np, 0, nbytes));
  uint8_t * old = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), slot);
  int32_t old_n = (g_pipe_imp_n)[slot];
  if ((old !=0)) {
    if ((old_n > 0)) {
      size_t old_bytes = ((size_t)((old_n * esz)));
      (void)(memcpy(np, old, old_bytes));
    }
    (void)(free(old));
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_entries)[0]), slot, np));
  (void)(((g_pipe_imp_cap)[slot] = new_cap));
  return 1;
}
int32_t pipe_imp_ensure_select(int32_t slot, int32_t need) {
  if ((slot < 0)) {
    return 0;
  }
  if ((slot >=128)) {
    return 0;
  }
  if ((need <=0)) {
    return 1;
  }
  int32_t cap = (g_pipe_imp_sel_cap)[slot];
  if ((cap >=need)) {
    return 1;
  }
  int32_t new_cap = cap;
  if ((new_cap < 8)) {
    (void)((new_cap = 8));
  }
  while ((new_cap < need)) {
    (void)((new_cap = (new_cap * 2)));
  }
  size_t row_bytes = ((size_t)((new_cap * 64)));
  size_t lens_bytes = ((size_t)((new_cap * 4)));
  uint8_t * nrows = 0;
  uint8_t * nlens = 0;
  (void)((nrows = malloc(row_bytes)));
  (void)((nlens = malloc(lens_bytes)));
  if ((nrows ==0)) {
    if ((nlens !=0)) {
      (void)(free(nlens));
    }
    return 0;
  }
  if ((nlens ==0)) {
    (void)(free(nrows));
    return 0;
  }
  (void)(memset(nrows, 0, row_bytes));
  (void)(memset(nlens, 0, lens_bytes));
  uint8_t * old_rows = xlang_ptr_slot_get(&((g_pipe_imp_sel_rows)[0]), slot);
  uint8_t * old_lens = xlang_ptr_slot_get(&((g_pipe_imp_sel_lens)[0]), slot);
  int32_t old_n = (g_pipe_imp_sel_n)[slot];
  if ((old_rows !=0)) {
    if ((old_n > 0)) {
      (void)(memcpy(nrows, old_rows, ((size_t)((old_n * 64)))));
    }
    (void)(free(old_rows));
  }
  if ((old_lens !=0)) {
    if ((old_n > 0)) {
      (void)(memcpy(nlens, old_lens, ((size_t)((old_n * 4)))));
    }
    (void)(free(old_lens));
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_rows)[0]), slot, nrows));
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_lens)[0]), slot, nlens));
  (void)(((g_pipe_imp_sel_cap)[slot] = new_cap));
  return 1;
}
uint8_t * pipe_imp_entry_at(int32_t slot, int32_t idx) {
  if ((slot < 0)) {
    return ((uint8_t *)(0));
  }
  if ((idx < 0)) {
    return ((uint8_t *)(0));
  }
  if ((idx >=(g_pipe_imp_n)[slot])) {
    return ((uint8_t *)(0));
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), slot);
  if ((base ==0)) {
    return ((uint8_t *)(0));
  }
  int32_t off = (idx * pipe_imp_entry_size());
  return base;
}
int32_t pipe_imp_entry_off(int32_t idx) {
  return (idx * pipe_imp_entry_size());
}
void pipeline_module_import_storage_release(uint8_t * module) {
  if ((module ==0)) {
    return;
  }
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  uint8_t * e = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((e !=0)) {
    (void)(free(e));
  }
  uint8_t * r = xlang_ptr_slot_get(&((g_pipe_imp_sel_rows)[0]), s);
  if ((r !=0)) {
    (void)(free(r));
  }
  uint8_t * l = xlang_ptr_slot_get(&((g_pipe_imp_sel_lens)[0]), s);
  if ((l !=0)) {
    (void)(free(l));
  }
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_mod)[0]), s, 0));
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_entries)[0]), s, 0));
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_rows)[0]), s, 0));
  (void)(xlang_ptr_slot_set(&((g_pipe_imp_sel_lens)[0]), s, 0));
  (void)(((g_pipe_imp_n)[s] = 0));
  (void)(((g_pipe_imp_cap)[s] = 0));
  (void)(((g_pipe_imp_sel_n)[s] = 0));
  (void)(((g_pipe_imp_sel_cap)[s] = 0));
}
int32_t pipeline_module_import_alloc(uint8_t * module) {
  if ((module ==0)) {
    return -1;
  }
  int32_t s = pipe_imp_find_or_create(module);
  if ((s < 0)) {
    return -1;
  }
  int32_t n = (g_pipe_imp_n)[s];
  if ((pipe_imp_ensure_entries(s, (n + 1)) ==0)) {
    return -1;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return -1;
  }
  int32_t off = pipe_imp_entry_off(n);
  int32_t k = 0;
  while ((k < 340)) {
    (void)(((base)[(off + k)] = 0));
    (void)((k = (k + 1)));
  }
  (void)(((g_pipe_imp_n)[s] = (n + 1)));
  (void)(pipe_imp_set_header_n(module, (n + 1)));
  return n;
}
void pipeline_module_import_set_path(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len) {
  if ((module ==0)) {
    return;
  }
  if ((bytes ==0)) {
    return;
  }
  if ((len <=0)) {
    return;
  }
  if ((len > 255)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  int32_t off = pipe_imp_entry_off(idx);
  int32_t z = 0;
  while ((z < 256)) {
    (void)(((base)[(off + z)] = 0));
    (void)((z = (z + 1)));
  }
  int32_t i = 0;
  while ((i < len)) {
    (void)(((base)[(off + i)] = (bytes)[i]));
    (void)((i = (i + 1)));
  }
  (void)(pipe_store_i32_le(base, (off + 256), len));
}
int32_t pipeline_module_import_path_len(uint8_t * module, int32_t idx) {
  if ((module ==0)) {
    return 0;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return 0;
  }
  if ((idx < 0)) {
    return 0;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return 0;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return 0;
  }
  return pipe_load_i32_le(base, (pipe_imp_entry_off(idx) + 256));
}
void pipeline_module_import_path_copy(uint8_t * module, int32_t idx, uint8_t * dst, int32_t dst_cap) {
  if ((dst ==0)) {
    return;
  }
  if ((dst_cap <=0)) {
    return;
  }
  (void)(((dst)[0] = 0));
  if ((module ==0)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  int32_t off = pipe_imp_entry_off(idx);
  int32_t n = pipe_load_i32_le(base, (off + 256));
  if ((n >=dst_cap)) {
    (void)((n = (dst_cap - 1)));
  }
  int32_t i = 0;
  while ((i < n)) {
    (void)(((dst)[i] = (base)[(off + i)]));
    (void)((i = (i + 1)));
  }
  (void)(((dst)[n] = 0));
}
uint8_t pipeline_module_import_path_byte_at(uint8_t * module, int32_t idx, int32_t off) {
  if ((module ==0)) {
    return ((uint8_t)(0));
  }
  if ((off < 0)) {
    return ((uint8_t)(0));
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return ((uint8_t)(0));
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return ((uint8_t)(0));
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t plen = pipe_load_i32_le(base, (eoff + 256));
  if ((off >=plen)) {
    return ((uint8_t)(0));
  }
  if ((off >=256)) {
    return ((uint8_t)(0));
  }
  uint8_t b = 0;
  (void)((b = (base)[(eoff + off)]));
  return b;
}
void pipeline_module_import_set_kind(uint8_t * module, int32_t idx, int32_t kind) {
  if ((module ==0)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  (void)(pipe_store_i32_le(base, (pipe_imp_entry_off(idx) + 260), kind));
}
int32_t pipeline_module_import_kind_at(uint8_t * module, int32_t idx) {
  if ((module ==0)) {
    return 0;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return 0;
  }
  if ((idx < 0)) {
    return 0;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return 0;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return 0;
  }
  return pipe_load_i32_le(base, (pipe_imp_entry_off(idx) + 260));
}
void pipeline_module_import_set_binding_name(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len) {
  if ((module ==0)) {
    return;
  }
  if ((bytes ==0)) {
    return;
  }
  if ((len <=0)) {
    return;
  }
  if ((len > 64)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t z = 0;
  while ((z < 64)) {
    (void)(((base)[((eoff + 264) + z)] = 0));
    (void)((z = (z + 1)));
  }
  int32_t i = 0;
  while ((i < len)) {
    (void)(((base)[((eoff + 264) + i)] = (bytes)[i]));
    (void)((i = (i + 1)));
  }
  (void)(pipe_store_i32_le(base, (eoff + 328), len));
}
int32_t pipeline_module_import_binding_name_len(uint8_t * module, int32_t idx) {
  if ((module ==0)) {
    return 0;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return 0;
  }
  if ((idx < 0)) {
    return 0;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return 0;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return 0;
  }
  return pipe_load_i32_le(base, (pipe_imp_entry_off(idx) + 328));
}
uint8_t pipeline_module_import_binding_name_byte_at(uint8_t * module, int32_t idx, int32_t off) {
  if ((module ==0)) {
    return ((uint8_t)(0));
  }
  if ((off < 0)) {
    return ((uint8_t)(0));
  }
  if ((off >=64)) {
    return ((uint8_t)(0));
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return ((uint8_t)(0));
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return ((uint8_t)(0));
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t bl = pipe_load_i32_le(base, (eoff + 328));
  if ((off >=bl)) {
    return ((uint8_t)(0));
  }
  uint8_t b = 0;
  (void)((b = (base)[((eoff + 264) + off)]));
  return b;
}
void pipeline_module_import_set_select_count(uint8_t * module, int32_t idx, int32_t n) {
  if ((module ==0)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  (void)(pipe_store_i32_le(base, (pipe_imp_entry_off(idx) + 336), n));
}
int32_t pipeline_module_import_append_select_name(uint8_t * module, int32_t idx, uint8_t * bytes, int32_t len) {
  if ((module ==0)) {
    return -1;
  }
  if ((bytes ==0)) {
    return -1;
  }
  if ((len <=0)) {
    return -1;
  }
  if ((idx < 0)) {
    return -1;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_or_create(module);
  if ((s < 0)) {
    return -1;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return -1;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return -1;
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t scount = pipe_load_i32_le(base, (eoff + 336));
  if ((scount ==0)) {
    (void)(pipe_store_i32_le(base, (eoff + 332), (g_pipe_imp_sel_n)[s]));
  }
  int32_t vi = (g_pipe_imp_sel_n)[s];
  if ((pipe_imp_ensure_select(s, (vi + 1)) ==0)) {
    return -1;
  }
  uint8_t * rows = xlang_ptr_slot_get(&((g_pipe_imp_sel_rows)[0]), s);
  uint8_t * lens = xlang_ptr_slot_get(&((g_pipe_imp_sel_lens)[0]), s);
  if ((rows ==0)) {
    return -1;
  }
  if ((lens ==0)) {
    return -1;
  }
  int32_t row_off = (vi * 64);
  int32_t z = 0;
  while ((z < 64)) {
    (void)(((rows)[(row_off + z)] = 0));
    (void)((z = (z + 1)));
  }
  int32_t n = len;
  if ((n > 63)) {
    (void)((n = 63));
  }
  int32_t i = 0;
  while ((i < n)) {
    (void)(((rows)[(row_off + i)] = (bytes)[i]));
    (void)((i = (i + 1)));
  }
  (void)(pipe_store_i32_le(lens, (vi * 4), n));
  (void)(((g_pipe_imp_sel_n)[s] = (vi + 1)));
  (void)(pipe_store_i32_le(base, (eoff + 336), (scount + 1)));
  return scount;
}
int32_t pipeline_module_import_select_count_at(uint8_t * module, int32_t idx) {
  if ((module ==0)) {
    return 0;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return 0;
  }
  if ((idx < 0)) {
    return 0;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return 0;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return 0;
  }
  return pipe_load_i32_le(base, (pipe_imp_entry_off(idx) + 336));
}
void pipeline_module_import_set_select_name(uint8_t * module, int32_t idx, int32_t sel, uint8_t * bytes, int32_t len) {
  if ((module ==0)) {
    return;
  }
  if ((bytes ==0)) {
    return;
  }
  if ((len <=0)) {
    return;
  }
  if ((sel < 0)) {
    return;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_or_create(module);
  if ((s < 0)) {
    return;
  }
  if ((idx < 0)) {
    return;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return;
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  while (1) {
    int32_t scount = pipe_load_i32_le(base, (eoff + 336));
    if ((scount > sel)) {
      break;
    }
    int32_t ap = pipeline_module_import_append_select_name(module, idx, bytes, len);
    if ((ap < 0)) {
      return;
    }
    (void)((scount = pipe_load_i32_le(base, (eoff + 336))));
    if ((sel < (scount - 1))) {
      return;
    }
  }
  int32_t sbase = pipe_load_i32_le(base, (eoff + 332));
  int32_t abs = (sbase + sel);
  uint8_t * rows = xlang_ptr_slot_get(&((g_pipe_imp_sel_rows)[0]), s);
  uint8_t * lens = xlang_ptr_slot_get(&((g_pipe_imp_sel_lens)[0]), s);
  if ((rows ==0)) {
    return;
  }
  if ((lens ==0)) {
    return;
  }
  if ((abs < 0)) {
    return;
  }
  if ((abs >=(g_pipe_imp_sel_n)[s])) {
    return;
  }
  int32_t row_off = (abs * 64);
  int32_t z = 0;
  while ((z < 64)) {
    (void)(((rows)[(row_off + z)] = 0));
    (void)((z = (z + 1)));
  }
  int32_t n = len;
  if ((n > 63)) {
    (void)((n = 63));
  }
  int32_t i = 0;
  while ((i < n)) {
    (void)(((rows)[(row_off + i)] = (bytes)[i]));
    (void)((i = (i + 1)));
  }
  (void)(pipe_store_i32_le(lens, (abs * 4), n));
}
int32_t pipeline_module_import_select_name_len(uint8_t * module, int32_t idx, int32_t sel) {
  if ((module ==0)) {
    return 0;
  }
  if ((sel < 0)) {
    return 0;
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return 0;
  }
  if ((idx < 0)) {
    return 0;
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return 0;
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return 0;
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t scount = pipe_load_i32_le(base, (eoff + 336));
  if ((sel >=scount)) {
    return 0;
  }
  int32_t sbase = pipe_load_i32_le(base, (eoff + 332));
  int32_t abs = (sbase + sel);
  if ((abs < 0)) {
    return 0;
  }
  if ((abs >=(g_pipe_imp_sel_n)[s])) {
    return 0;
  }
  uint8_t * lens = xlang_ptr_slot_get(&((g_pipe_imp_sel_lens)[0]), s);
  if ((lens ==0)) {
    return 0;
  }
  return pipe_load_i32_le(lens, (abs * 4));
}
uint8_t pipeline_module_import_select_name_byte_at(uint8_t * module, int32_t idx, int32_t sel, int32_t off) {
  if ((module ==0)) {
    return ((uint8_t)(0));
  }
  if ((sel < 0)) {
    return ((uint8_t)(0));
  }
  if ((off < 0)) {
    return ((uint8_t)(0));
  }
  (void)(pipe_imp_soft_sync(module));
  int32_t s = pipe_imp_find_slot(module);
  if ((s < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx < 0)) {
    return ((uint8_t)(0));
  }
  if ((idx >=(g_pipe_imp_n)[s])) {
    return ((uint8_t)(0));
  }
  uint8_t * base = xlang_ptr_slot_get(&((g_pipe_imp_entries)[0]), s);
  if ((base ==0)) {
    return ((uint8_t)(0));
  }
  int32_t eoff = pipe_imp_entry_off(idx);
  int32_t scount = pipe_load_i32_le(base, (eoff + 336));
  if ((sel >=scount)) {
    return ((uint8_t)(0));
  }
  int32_t sbase = pipe_load_i32_le(base, (eoff + 332));
  int32_t abs = (sbase + sel);
  if ((abs < 0)) {
    return ((uint8_t)(0));
  }
  if ((abs >=(g_pipe_imp_sel_n)[s])) {
    return ((uint8_t)(0));
  }
  int32_t nlen = pipeline_module_import_select_name_len(module, idx, sel);
  if ((off >=nlen)) {
    return ((uint8_t)(0));
  }
  if ((off >=64)) {
    return ((uint8_t)(0));
  }
  uint8_t * rows = xlang_ptr_slot_get(&((g_pipe_imp_sel_rows)[0]), s);
  if ((rows ==0)) {
    return ((uint8_t)(0));
  }
  uint8_t b = 0;
  (void)((b = (rows)[((abs * 64) + off)]));
  return b;
}
