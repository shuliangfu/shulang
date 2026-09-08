/* seeds/labi_ondemand_list_surface.from_x.c
 * G-02f labi_ondemand_list R2 L8b surface — isomorphic with src/runtime/labi_ondemand_list.x
 * wave263: late heavy pure moved to labi_ondemand_heavy_surface.from_x.c (L8c)
 * PLATFORM: SHARED
 */
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
extern int32_t xlang_link_obj_needs_undef_sym(uint8_t * user_o, uint8_t * sym);
extern int32_t xlang_link_obj_has_defined_sym(uint8_t * o_path, uint8_t * sym);
extern int32_t link_abi_obj_exports_marker(uint8_t * obj_o, uint8_t * marker);
extern int32_t link_abi_obj_has_undef_sym(uint8_t * obj_o, uint8_t * sym);
extern int32_t labi_od_simple_group_count(void);
extern int32_t labi_od_simple_group_sym_count(int32_t g);
extern uint8_t * labi_od_simple_group_sym_at(int32_t g, int32_t i);
extern uint8_t * labi_od_simple_group_rel(int32_t g);
extern int32_t labi_od_kv_sym_count(void);
extern uint8_t * labi_od_kv_sym_at(int32_t i);
extern uint8_t * labi_od_kv_rel(void);
extern uint8_t * labi_od_kv_glue_rel(void);
extern int32_t labi_od_arrow_sym_count(void);
extern uint8_t * labi_od_arrow_sym_at(int32_t i);
extern uint8_t * labi_od_arrow_rel(void);
extern uint8_t * labi_od_arrow_glue_rel(void);
extern int32_t labi_od_time_sym_count(void);
extern uint8_t * labi_od_time_sym_at(int32_t i);
extern uint8_t * labi_od_time_rel(void);
extern uint8_t * labi_od_time_os_rel(void);
extern int32_t labi_od_queue_sym_count(void);
extern uint8_t * labi_od_queue_sym_at(int32_t i);
extern uint8_t * labi_od_queue_rel(void);
extern uint8_t * labi_od_queue_contention_rel(void);
extern int32_t labi_od_net_sym_count(void);
extern uint8_t * labi_od_net_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_net(uint8_t * user_o);
extern int32_t labi_od_set_sym_count(void);
extern uint8_t * labi_od_set_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_set(uint8_t * user_o);
extern int32_t labi_od_map_sym_count(void);
extern uint8_t * labi_od_map_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_map(uint8_t * user_o);
extern int32_t labi_od_queue_api_sym_count(void);
extern uint8_t * labi_od_queue_api_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_queue(uint8_t * user_o);
extern int32_t labi_od_test_sym_count(void);
extern uint8_t * labi_od_test_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_test(uint8_t * user_o);
extern int32_t labi_od_core_mem_sym_count(void);
extern uint8_t * labi_od_core_mem_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_core_mem(uint8_t * user_o);
extern int32_t labi_od_core_slice_sym_count(void);
extern uint8_t * labi_od_core_slice_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_core_slice(uint8_t * user_o);
extern int32_t labi_od_page_mmap_sym_count(void);
extern uint8_t * labi_od_page_mmap_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_heap_page_mmap(uint8_t * user_o);
extern int32_t labi_od_sys_linux_sym_count(void);
extern uint8_t * labi_od_sys_linux_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_sys_linux(uint8_t * user_o);
extern int32_t labi_od_sys_sym_count(void);
extern uint8_t * labi_od_sys_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_sys(uint8_t * user_o);
extern int32_t labi_od_heap_api_sym_count(void);
extern uint8_t * labi_od_heap_api_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_std_heap_api(uint8_t * user_o);
extern int32_t labi_od_heap_user_sym_count(void);
extern uint8_t * labi_od_heap_user_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_heap_user_syms(uint8_t * user_o);
extern int32_t labi_od_async_scheduler_sym_count(void);
extern uint8_t * labi_od_async_scheduler_sym_at(int32_t i);
extern int32_t link_abi_user_o_needs_async_scheduler(uint8_t * user_o);
extern int32_t labi_od_zlib_undef_sym_count(void);
extern uint8_t * labi_od_zlib_undef_sym_at(int32_t i);
extern uint8_t * labi_od_compress_zlib_marker(void);
extern int32_t labi_od_zstd_undef_sym_count(void);
extern uint8_t * labi_od_zstd_undef_sym_at(int32_t i);
extern uint8_t * labi_od_compress_zstd_marker(void);
extern int32_t labi_od_brotli_undef_sym_count(void);
extern uint8_t * labi_od_brotli_undef_sym_at(int32_t i);
extern uint8_t * labi_od_compress_brotli_marker(void);
extern int32_t link_abi_obj_needs_zlib(uint8_t * obj_o);
extern int32_t link_abi_obj_needs_zstd(uint8_t * obj_o);
extern int32_t link_abi_obj_needs_brotli(uint8_t * obj_o);
extern int32_t link_abi_user_o_needs_compress_libs(uint8_t * user_o);
extern int32_t labi_od_runtime_time_os_sym_count(void);
extern uint8_t * labi_od_runtime_time_os_sym_at(int32_t i);
extern int32_t labi_user_needs_runtime_time_os(uint8_t * user_o);
extern int32_t labi_od_runtime_random_fill_sym_count(void);
extern uint8_t * labi_od_runtime_random_fill_sym_at(int32_t i);
extern int32_t labi_user_needs_runtime_random_fill(uint8_t * user_o);
extern int32_t labi_od_runtime_env_os_sym_count(void);
extern uint8_t * labi_od_runtime_env_os_sym_at(int32_t i);
extern int32_t labi_user_needs_runtime_env_os(uint8_t * user_o);
extern int32_t labi_od_runtime_process_argv_sym_count(void);
extern uint8_t * labi_od_runtime_process_argv_sym_at(int32_t i);
extern int32_t labi_user_needs_runtime_process_argv(uint8_t * user_o);
extern int32_t xlang_link_obj_needs_undef_sym_impl(uint8_t * user_o, uint8_t * sym);
int32_t xlang_link_obj_needs_undef_sym(uint8_t * user_o, uint8_t * sym) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  if ((sym ==0)) {
    return 0;
  }
  if (((sym)[0] ==0)) {
    return 0;
  }
  return xlang_link_obj_needs_undef_sym_impl(user_o, sym);
  return 0;
}
extern int32_t link_abi_ld_argv_entry_is_obj(uint8_t * s);
extern int32_t xlang_link_obj_has_defined_sym_impl(uint8_t * o_path, uint8_t * sym);
int32_t xlang_link_obj_has_defined_sym(uint8_t * o_path, uint8_t * sym) {
  if ((o_path ==0)) {
    return 0;
  }
  if (((o_path)[0] ==0)) {
    return 0;
  }
  if ((sym ==0)) {
    return 0;
  }
  if (((sym)[0] ==0)) {
    return 0;
  }
  return xlang_link_obj_has_defined_sym_impl(o_path, sym);
  return 0;
}
extern int32_t link_abi_obj_exports_marker_impl(uint8_t * obj_o, uint8_t * marker);
int32_t link_abi_obj_exports_marker(uint8_t * obj_o, uint8_t * marker) {
  if ((obj_o ==0)) {
    return 0;
  }
  if (((obj_o)[0] ==0)) {
    return 0;
  }
  if ((marker ==0)) {
    return 0;
  }
  if (((marker)[0] ==0)) {
    return 0;
  }
  return link_abi_obj_exports_marker_impl(obj_o, marker);
  return 0;
}
extern int32_t link_abi_obj_has_undef_sym_impl(uint8_t * obj_o, uint8_t * sym);
int32_t link_abi_obj_has_undef_sym(uint8_t * obj_o, uint8_t * sym) {
  if ((obj_o ==0)) {
    return 0;
  }
  if (((obj_o)[0] ==0)) {
    return 0;
  }
  if ((sym ==0)) {
    return 0;
  }
  if (((sym)[0] ==0)) {
    return 0;
  }
  return link_abi_obj_has_undef_sym_impl(obj_o, sym);
  return 0;
}
extern int32_t link_abi_asm_ld_push_obj(uint8_t * primary, uint8_t * link_argv0, uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, int32_t * flag_out);
extern void link_abi_asm_ld_argv_push_stable(uint8_t * bank, uint8_t * * argv, int32_t * la, int32_t max_la, uint8_t * p);
extern uint8_t * xlang_asm_ld_try_under_lib_roots(uint8_t * rel, uint8_t * * lib_roots, int32_t n_lib_roots, uint8_t * bank);
extern uint8_t * asm_link_obj_skip_missing(uint8_t * path);
extern uint8_t * xlang_rel_o_path_from_argv0(uint8_t * argv0, uint8_t * rel);
extern uint8_t * xlang_repo_root_from_argv0(uint8_t * argv0);
extern int32_t xlang_ensure_formal_std_make_o(uint8_t * repo_root, uint8_t * rel_from_repo, uint8_t * make_target);
extern int32_t driver_freestanding_get(void);
extern int32_t xlang_ensure_runtime_thread_glue_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_thread_glue_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_net_udp_batch_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_net_udp_batch_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_net_workers_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_net_workers_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_test_fn_invoke_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_test_fn_invoke_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_heap_user_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_heap_user_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_process_argv_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_process_argv_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_time_os_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_time_os_o_path(uint8_t * argv0);
extern int32_t xlang_ensure_runtime_queue_contention_o(uint8_t * argv0);
extern uint8_t * xlang_runtime_queue_contention_o_path(uint8_t * argv0);
extern uint8_t * xlang_std_async_scheduler_o_path(uint8_t * argv0);
extern uint8_t * xlang_runtime_scheduler_glue_o_path(uint8_t * argv0);
extern uint8_t * xlang_runtime_kv_mmap_glue_o_path(uint8_t * argv0);
extern uint8_t * xlang_runtime_arrow_simd_glue_o_path(uint8_t * argv0);
int32_t labi_od_simple_group_count(void) {
  /* PLATFORM: SHARED — ≡ pure labi_ondemand_list.x g0..g19 (G.7 cold twin). */
  return 20;
}
int32_t labi_od_simple_group_sym_count(int32_t g) {
  if ((g < 0)) {
    return 0;
  }
  if ((g ==0)) {
    return 9;
  }
  if ((g ==1)) {
    return 2;
  }
  if ((g ==2)) {
    return 6;
  }
  if ((g ==3)) {
    return 4;
  }
  if ((g ==4)) {
    return 5;
  }
  if ((g ==5)) {
    return 3;
  }
  if ((g ==6)) {
    return 4;
  }
  if ((g ==7)) {
    return 4;
  }
  if ((g ==8)) {
    return 6;
  }
  if ((g ==9)) {
    return 10;
  }
  /* PLATFORM: SHARED — core.builtin formal (pure-asm residual; C G-01 __builtin_*). */
  if ((g ==10)) {
    return 14;
  }
  /* PLATFORM: SHARED — std.ffi formal (pure-asm run-ffi residual). */
  if ((g ==11)) {
    return 8;
  }
  if ((g ==12)) {
    return 5;
  }
  if ((g ==13)) {
    return 6;
  }
  if ((g ==14)) {
    return 8;
  }
  if ((g ==15)) {
    return 24;
  }
  if ((g ==16)) {
    return 4;
  }
  if ((g ==17)) {
    return 3;
  }
  if ((g ==18)) {
    return 23; /* std.simd VECTOR mid + binop/dot/fma + scalar faces + select_lane */
  }
  if ((g ==19)) {
    return 3; /* std.io ctx-timeout */
  }
  return 0;
}
uint8_t * labi_od_simple_group_sym_at(int32_t g, int32_t i) {
  if ((g < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((g ==0)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x63\x6f\x70\x79\x5f\x63");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6d\x65\x6d\x63\x6d\x70\x5f\x63");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6d\x65\x6d\x63\x68\x72\x5f\x63");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6d\x65\x6d\x6d\x65\x6d\x5f\x63");
      return p;
    }
    if ((i ==4)) {
      uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6d\x65\x6d\x72\x63\x68\x72\x5f\x63");
      return p;
    }
    if ((i ==5)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6e\x65\x77");
      return p;
    }
    if ((i ==6)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x66\x72\x6f\x6d\x5f\x73\x6c\x69\x63\x65");
      return p;
    }
    if ((i ==7)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x76\x69\x65\x77");
      return p;
    }
    if ((i ==8)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x74\x72\x69\x6e\x67\x5f\x73\x74\x72\x69\x6e\x67\x5f\x6c\x65\x6e");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==1)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x74\x79\x70\x65\x73\x5f\x73\x69\x7a\x65\x5f\x6f\x66\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x74\x79\x70\x65\x73\x5f\x70\x6c\x61\x63\x65\x68\x6f\x6c\x64\x65\x72");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==2)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x75\x74\x66\x38\x5f\x76\x61\x6c\x69\x64\x5f\x63");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x68\x65\x78\x5f\x65\x6e\x63\x6f\x64\x65\x5f\x63");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x61\x73\x63\x69\x69\x5f\x69\x73\x5f\x61\x6c\x70\x68\x61\x5f\x63");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x75\x74\x66\x38\x5f\x76\x61\x6c\x69\x64");
      return p;
    }
    if ((i ==4)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x75\x74\x66\x38\x5f\x64\x65\x63\x6f\x64\x65\x5f\x72\x75\x6e\x65");
      return p;
    }
    if ((i ==5)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x63\x6f\x64\x69\x6e\x67\x5f\x61\x73\x63\x69\x69\x5f\x69\x73\x5f\x61\x6c\x70\x68\x61");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==3)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x62\x61\x73\x65\x36\x34\x5f\x65\x6e\x63\x6f\x64\x65\x5f\x73\x74\x61\x6e\x64\x61\x72\x64\x5f\x63");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x62\x61\x73\x65\x36\x34\x5f\x65\x6e\x63\x6f\x64\x65\x5f\x73\x74\x61\x6e\x64\x61\x72\x64");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x62\x61\x73\x65\x36\x34\x5f\x64\x65\x63\x6f\x64\x65\x5f\x73\x74\x61\x6e\x64\x61\x72\x64");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x62\x61\x73\x65\x36\x34\x5f\x65\x6e\x63\x6f\x64\x65\x5f\x75\x72\x6c");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==4)) {
    /* PLATFORM: SHARED — exact UNDEF needles for std/csv/csv.o (g==4). */
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x63\x73\x76\x5f\x6e\x65\x78\x74\x5f\x66\x69\x65\x6c\x64");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x63\x73\x76\x5f\x65\x73\x63\x61\x70\x65");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x63\x73\x76\x5f\x63\x73\x76\x5f\x74\x65\x73\x74\x5f\x71\x75\x6f\x74\x65\x64\x5f\x66\x69\x72\x73\x74");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"std_csv_parse_row");
      return p;
    }
    if ((i ==4)) {
      uint8_t * p = ((uint8_t *)"std_csv_write_row");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==5)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x73\x63\x68\x65\x6d\x61\x5f\x63\x72\x65\x61\x74\x65\x5f\x63");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x73\x63\x68\x65\x6d\x61\x5f\x64\x65\x63\x6f\x64\x65\x5f\x6a\x73\x6f\x6e\x5f\x63");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x73\x63\x68\x65\x6d\x61\x5f\x73\x6d\x6f\x6b\x65\x5f\x63");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==6)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6f\x70\x74\x69\x6f\x6e\x5f\x73\x6f\x6d\x65\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6f\x70\x74\x69\x6f\x6e\x5f\x75\x6e\x77\x72\x61\x70\x5f\x6f\x72\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6f\x70\x74\x69\x6f\x6e\x5f\x6e\x6f\x6e\x65\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6f\x70\x74\x69\x6f\x6e\x5f\x69\x73\x5f\x73\x6f\x6d\x65\x5f\x69\x33\x32");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==7)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x72\x65\x73\x75\x6c\x74\x5f\x6f\x6b\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x72\x65\x73\x75\x6c\x74\x5f\x69\x73\x5f\x6f\x6b\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x72\x65\x73\x75\x6c\x74\x5f\x65\x72\x72\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x72\x65\x73\x75\x6c\x74\x5f\x6f\x6b");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==8)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74\x5f\x65\x71\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74\x5f\x65\x71\x5f\x75\x33\x32");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74\x5f\x65\x71\x5f\x75\x36\x34");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74\x5f\x6e\x65\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==4)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74");
      return p;
    }
    if ((i ==5)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x64\x65\x62\x75\x67\x5f\x64\x65\x62\x75\x67\x5f\x61\x73\x73\x65\x72\x74");
      return p;
    }
    return ((uint8_t *)(0));
  }
  if ((g ==9)) {
    if ((i ==0)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x6c\x65\x6e\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==1)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x67\x65\x74\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==2)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x67\x65\x74\x5f\x69\x33\x32\x5f\x75\x6e\x63\x68\x65\x63\x6b\x65\x64");
      return p;
    }
    if ((i ==3)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x6c\x65\x6e\x5f\x75\x38");
      return p;
    }
    if ((i ==4)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x67\x65\x74\x5f\x75\x38");
      return p;
    }
    if ((i ==5)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x67\x65\x74\x5f\x75\x38\x5f\x75\x6e\x63\x68\x65\x63\x6b\x65\x64");
      return p;
    }
    if ((i ==6)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x73\x75\x62\x73\x6c\x69\x63\x65\x5f\x69\x33\x32");
      return p;
    }
    if ((i ==7)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x73\x75\x62\x73\x6c\x69\x63\x65\x5f\x75\x38");
      return p;
    }
    if ((i ==8)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x6c\x65\x6e\x5f\x75\x36\x34");
      return p;
    }
    if ((i ==9)) {
      uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x67\x65\x74\x5f\x75\x36\x34");
      return p;
    }
    return ((uint8_t *)(0));
  }
  /* PLATFORM: SHARED — core.builtin formal surface (G.7 twin of pure labi_ondemand_list.x). */
  if ((g ==10)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"core_builtin_placeholder"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"core_builtin_copy"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"core_builtin_min_i32"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"core_builtin_max_i32"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"core_builtin_min_u32"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"core_builtin_max_u32"); return p; }
    if ((i ==6)) { uint8_t * p = ((uint8_t *)"core_builtin_clz_u32"); return p; }
    if ((i ==7)) { uint8_t * p = ((uint8_t *)"core_builtin_ctz_u32"); return p; }
    if ((i ==8)) { uint8_t * p = ((uint8_t *)"core_builtin_popcount_u32"); return p; }
    if ((i ==9)) { uint8_t * p = ((uint8_t *)"core_builtin_bswap_u32"); return p; }
    if ((i ==10)) { uint8_t * p = ((uint8_t *)"core_builtin_rotl_u32"); return p; }
    if ((i ==11)) { uint8_t * p = ((uint8_t *)"core_builtin_rotr_u32"); return p; }
    if ((i ==12)) { uint8_t * p = ((uint8_t *)"core_builtin_unreachable"); return p; }
    if ((i ==13)) { uint8_t * p = ((uint8_t *)"core_builtin_abort"); return p; }
    return ((uint8_t *)(0));
  }
  /* PLATFORM: SHARED — std.ffi formal surface (G.7 twin of pure labi_ondemand_list.x). */
  if ((g ==11)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_ffi_cstr_len"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_ffi_cstring_new"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_ffi_cstring_free"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_ffi_cstring_try_new"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"std_ffi_cstring_destroy"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"ffi_cstr_len_c"); return p; }
    if ((i ==6)) { uint8_t * p = ((uint8_t *)"ffi_cstring_new_c"); return p; }
    if ((i ==7)) { uint8_t * p = ((uint8_t *)"ffi_cstring_free_c"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==12)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_test_expect"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_test_expect_eq_i32"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_test_expect_ne_i32"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_test_assert"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"std_test_runner_case"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==13)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"core_assert_assert"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"core_assert_assert_eq_i32"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"core_assert_assert_ne_i32"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"core_assert_debug_assert"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"core_assert_assert_eq_u32"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"core_assert_assert_eq_bool"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==14)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_fmt_format_i32"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_fmt_to_buf_u8_ptr_i32_i32"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_fmt_to_buf_u8_ptr_i32_u32"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_fmt_to_buf_u8_ptr_i32_i64"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"std_fmt_to_buf_u8_ptr_i32_u64"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"std_fmt_hex_to_buf_u8_ptr_i32_u32"); return p; }
    if ((i ==6)) { uint8_t * p = ((uint8_t *)"std_fmt_append_to_buf_u8_ptr_i32_i32_i32"); return p; }
    if ((i ==7)) { uint8_t * p = ((uint8_t *)"std_fmt_format_u8_ptr_i32_i32_i32"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==15)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_compress_gzip_compress"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_compress_gzip_decompress"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_compress_brotli_compress"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_compress_brotli_decompress"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"std_compress_zstd_compress"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"std_compress_zstd_decompress"); return p; }
    if ((i ==6)) { uint8_t * p = ((uint8_t *)"std_compress_compress_state_bytes_for"); return p; }
    if ((i ==7)) { uint8_t * p = ((uint8_t *)"std_compress_compress_init"); return p; }
    if ((i ==8)) { uint8_t * p = ((uint8_t *)"std_compress_compress_process"); return p; }
    if ((i ==9)) { uint8_t * p = ((uint8_t *)"std_compress_compress_end"); return p; }
    if ((i ==10)) { uint8_t * p = ((uint8_t *)"std_compress_format_brotli"); return p; }
    if ((i ==11)) { uint8_t * p = ((uint8_t *)"std_compress_format_zstd"); return p; }
    if ((i ==12)) { uint8_t * p = ((uint8_t *)"std_compress_mode_compress"); return p; }
    if ((i ==13)) { uint8_t * p = ((uint8_t *)"std_compress_mode_decompress"); return p; }
    if ((i ==14)) { uint8_t * p = ((uint8_t *)"std_compress_zlib_deflate"); return p; }
    if ((i ==15)) { uint8_t * p = ((uint8_t *)"std_compress_zlib_inflate"); return p; }
    if ((i ==16)) { uint8_t * p = ((uint8_t *)"std_compress_gzip_gzip_compress"); return p; }
    if ((i ==17)) { uint8_t * p = ((uint8_t *)"std_compress_gzip_gzip_decompress"); return p; }
    if ((i ==18)) { uint8_t * p = ((uint8_t *)"std_compress_deflate"); return p; }
    if ((i ==19)) { uint8_t * p = ((uint8_t *)"std_compress_inflate"); return p; }
    if ((i ==20)) { uint8_t * p = ((uint8_t *)"compress_deflate_c"); return p; }
    if ((i ==21)) { uint8_t * p = ((uint8_t *)"compress_inflate_c"); return p; }
    if ((i ==22)) { uint8_t * p = ((uint8_t *)"compress_gzip_compress_c"); return p; }
    if ((i ==23)) { uint8_t * p = ((uint8_t *)"compress_gzip_decompress_c"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==16)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_io_driver_register"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_io_driver_submit_read"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_io_driver_submit_write"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_io_driver_submit_register_fixed_buffers_buf"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==17)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_debug_assert"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_debug_println_u8_ptr_i32"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_debug_print_u8_ptr_i32"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==18)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_simd_shuffle_f32x4_i32_a4"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_simd_shuffle_i32x8_i32_a8"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_simd_select_f32x4_f32x4_f32x4"); return p; }
    if ((i ==3)) { uint8_t * p = ((uint8_t *)"std_simd_select_i32x8_i32x8_i32x8"); return p; }
    if ((i ==4)) { uint8_t * p = ((uint8_t *)"std_simd_splat_i32"); return p; }
    if ((i ==5)) { uint8_t * p = ((uint8_t *)"std_simd_splat_f32"); return p; }
    if ((i ==6)) { uint8_t * p = ((uint8_t *)"std_simd_mul_f32x4_f32x4"); return p; }
    if ((i ==7)) { uint8_t * p = ((uint8_t *)"std_simd_mul_i32x8_i32x8"); return p; }
    if ((i ==8)) { uint8_t * p = ((uint8_t *)"std_simd_sub_i32x8_i32x8"); return p; }
    if ((i ==9)) { uint8_t * p = ((uint8_t *)"std_simd_sub_f32x4_f32x4"); return p; }
    if ((i ==10)) { uint8_t * p = ((uint8_t *)"std_simd_add_f32x4_f32x4"); return p; }
    if ((i ==11)) { uint8_t * p = ((uint8_t *)"std_simd_add_i32x8_i32x8"); return p; }
    if ((i ==12)) { uint8_t * p = ((uint8_t *)"std_simd_dot"); return p; }
    if ((i ==13)) { uint8_t * p = ((uint8_t *)"std_simd_madd"); return p; }
    if ((i ==14)) { uint8_t * p = ((uint8_t *)"std_simd_fma"); return p; }
    if ((i ==15)) { uint8_t * p = ((uint8_t *)"std_simd_hsum"); return p; }
    if ((i ==16)) { uint8_t * p = ((uint8_t *)"std_simd_placeholder"); return p; }
    if ((i ==17)) { uint8_t * p = ((uint8_t *)"std_simd_hw_available"); return p; }
    if ((i ==18)) { uint8_t * p = ((uint8_t *)"std_simd_recommend_path"); return p; }
    if ((i ==19)) { uint8_t * p = ((uint8_t *)"std_simd_SIMD_PATH_SCALAR"); return p; }
    if ((i ==20)) { uint8_t * p = ((uint8_t *)"std_simd_SIMD_PATH_HW"); return p; }
    if ((i ==21)) { uint8_t * p = ((uint8_t *)"std_simd_select_lane_i32_i32_i32"); return p; }
    if ((i ==22)) { uint8_t * p = ((uint8_t *)"std_simd_select_lane_f32_f32_f32"); return p; }
    return ((uint8_t *)(0));
  }
  if ((g ==19)) {
    if ((i ==0)) { uint8_t * p = ((uint8_t *)"std_io_timeout_from_ctx"); return p; }
    if ((i ==1)) { uint8_t * p = ((uint8_t *)"std_io_read_ctx"); return p; }
    if ((i ==2)) { uint8_t * p = ((uint8_t *)"std_io_write_ctx"); return p; }
    return ((uint8_t *)(0));
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_simple_group_rel(int32_t g) {
  if ((g < 0)) {
    return ((uint8_t *)(0));
  }
  if ((g ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x73\x74\x72\x69\x6e\x67\x2f\x73\x74\x72\x69\x6e\x67\x2e\x6f");
    return p;
  }
  if ((g ==1)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x2f\x74\x79\x70\x65\x73\x2f\x74\x79\x70\x65\x73\x2e\x6f");
    return p;
  }
  if ((g ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x65\x6e\x63\x6f\x64\x69\x6e\x67\x2f\x65\x6e\x63\x6f\x64\x69\x6e\x67\x2e\x6f");
    return p;
  }
  if ((g ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x62\x61\x73\x65\x36\x34\x2f\x62\x61\x73\x65\x36\x34\x2e\x6f");
    return p;
  }
  if ((g ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x63\x73\x76\x2f\x63\x73\x76\x2e\x6f");
    return p;
  }
  if ((g ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x73\x63\x68\x65\x6d\x61\x2f\x73\x63\x68\x65\x6d\x61\x2e\x6f");
    return p;
  }
  if ((g ==6)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x2f\x6f\x70\x74\x69\x6f\x6e\x2f\x6f\x70\x74\x69\x6f\x6e\x2e\x6f");
    return p;
  }
  if ((g ==7)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x2f\x72\x65\x73\x75\x6c\x74\x2f\x72\x65\x73\x75\x6c\x74\x2e\x6f");
    return p;
  }
  if ((g ==8)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x2f\x64\x65\x62\x75\x67\x2f\x64\x65\x62\x75\x67\x2e\x6f");
    return p;
  }
  if ((g ==9)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x2f\x73\x6c\x69\x63\x65\x2f\x6d\x6f\x64\x2e\x6f");
    return p;
  }
  if ((g ==10)) {
    uint8_t * p = ((uint8_t *)"core/builtin/builtin.o");
    return p;
  }
  if ((g ==11)) {
    uint8_t * p = ((uint8_t *)"std/ffi/ffi.o");
    return p;
  }
  if ((g ==12)) {
    uint8_t * p = ((uint8_t *)"std/test/test.o");
    return p;
  }
  if ((g ==13)) {
    uint8_t * p = ((uint8_t *)"core/assert/assert.o");
    return p;
  }
  if ((g ==14)) {
    uint8_t * p = ((uint8_t *)"std/fmt/fmt.o");
    return p;
  }
  if ((g ==15)) {
    uint8_t * p = ((uint8_t *)"std/compress/compress.o");
    return p;
  }
  if ((g ==16)) {
    uint8_t * p = ((uint8_t *)"std/io/driver.o");
    return p;
  }
  if ((g ==17)) {
    uint8_t * p = ((uint8_t *)"std/debug/debug.o");
    return p;
  }
  if ((g ==18)) {
    uint8_t * p = ((uint8_t *)"std/simd/simd.o");
    return p;
  }
  if ((g ==19)) {
    uint8_t * p = ((uint8_t *)"std/io/io.o");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t labi_od_kv_sym_count(void) {
  return 2;
}
uint8_t * labi_od_kv_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x64\x62\x5f\x6b\x76\x5f\x6f\x70\x65\x6e\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x64\x62\x5f\x6b\x76\x5f\x67\x65\x74\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_kv_rel(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x64\x62\x2f\x6b\x76\x2f\x6b\x76\x2e\x6f");
  return p;
}
uint8_t * labi_od_kv_glue_rel(void) {
  uint8_t * p = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x6b\x76\x5f\x6d\x6d\x61\x70\x5f\x67\x6c\x75\x65\x2e\x6f");
  return p;
}
int32_t labi_od_arrow_sym_count(void) {
  return 2;
}
uint8_t * labi_od_arrow_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x61\x72\x72\x6f\x77\x5f\x63\x6f\x6c\x75\x6d\x6e\x5f\x69\x33\x32\x5f\x63\x72\x65\x61\x74\x65\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x61\x72\x72\x6f\x77\x5f\x63\x6f\x6c\x75\x6d\x6e\x5f\x61\x64\x6f\x70\x74\x5f\x66\x33\x32\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_arrow_rel(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x64\x62\x2f\x61\x72\x72\x6f\x77\x2f\x61\x72\x72\x6f\x77\x2e\x6f");
  return p;
}
uint8_t * labi_od_arrow_glue_rel(void) {
  uint8_t * p = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x61\x72\x72\x6f\x77\x5f\x73\x69\x6d\x64\x5f\x67\x6c\x75\x65\x2e\x6f");
  return p;
}
int32_t labi_od_time_sym_count(void) {
  return 4;
}
uint8_t * labi_od_time_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x6d\x6f\x6e\x6f\x74\x6f\x6e\x69\x63\x5f\x6e\x73");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x73\x6c\x65\x65\x70\x5f\x6d\x73");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x74\x69\x6d\x65\x72\x5f\x73\x74\x61\x72\x74");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x6d\x6f\x6e\x6f\x74\x6f\x6e\x69\x63\x5f\x6e\x73\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_time_rel(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x74\x69\x6d\x65\x2f\x74\x69\x6d\x65\x2e\x6f");
  return p;
}
uint8_t * labi_od_time_os_rel(void) {
  uint8_t * p = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x74\x69\x6d\x65\x5f\x6f\x73\x2e\x6f");
  return p;
}
int32_t labi_od_queue_sym_count(void) {
  return 3;
}
uint8_t * labi_od_queue_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x79\x6e\x63\x5f\x71\x75\x65\x75\x65\x5f\x63\x6f\x6e\x74\x65\x6e\x74\x69\x6f\x6e\x5f\x73\x6d\x6f\x6b\x65\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x71\x75\x65\x75\x65\x5f\x6f\x73\x5f\x72\x75\x6e\x5f\x74\x77\x6f\x5f\x77\x6f\x72\x6b\x65\x72\x73\x5f\x63");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x71\x75\x65\x75\x65\x5f\x63\x6f\x6e\x74\x65\x6e\x74\x69\x6f\x6e\x5f\x77\x6f\x72\x6b\x65\x72\x5f\x70\x75\x73\x68\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_queue_rel(void) {
  uint8_t * p = ((uint8_t *)"\x73\x74\x64\x2f\x71\x75\x65\x75\x65\x2f\x71\x75\x65\x75\x65\x2e\x6f");
  return p;
}
uint8_t * labi_od_queue_contention_rel(void) {
  uint8_t * p = ((uint8_t *)"\x63\x6f\x6d\x70\x69\x6c\x65\x72\x2f\x72\x75\x6e\x74\x69\x6d\x65\x5f\x71\x75\x65\x75\x65\x5f\x63\x6f\x6e\x74\x65\x6e\x74\x69\x6f\x6e\x2e\x6f");
  return p;
}
int32_t labi_od_net_sym_count(void) {
  return 17;
}
uint8_t * labi_od_net_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x6c\x69\x73\x74\x65\x6e");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x63\x6f\x6e\x6e\x65\x63\x74");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x75\x64\x70\x5f\x62\x69\x6e\x64");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x75\x64\x70\x5f\x72\x65\x63\x76\x5f\x6d\x61\x6e\x79\x5f\x62\x75\x66");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x75\x64\x70\x5f\x73\x65\x6e\x64\x5f\x6d\x61\x6e\x79\x5f\x62\x75\x66");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x61\x64\x64\x72\x5f\x74\x6f\x5f\x75\x33\x32");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6e\x65\x74\x5f\x63\x6c\x6f\x73\x65\x5f\x75\x64\x70");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x73\x74\x72\x65\x61\x6d\x5f\x77\x72\x69\x74\x65\x5f\x62\x61\x74\x63\x68\x5f\x63");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x74\x63\x70\x5f\x63\x6f\x6e\x6e\x65\x63\x74\x5f\x63");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x74\x63\x70\x5f\x6c\x69\x73\x74\x65\x6e\x5f\x63");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x75\x64\x70\x5f\x62\x69\x6e\x64\x5f\x63");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x75\x64\x70\x5f\x72\x65\x63\x76\x5f\x6d\x61\x6e\x79\x5f\x62\x75\x66\x5f\x63");
    return p;
  }
  if ((i ==12)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x75\x64\x70\x5f\x73\x65\x6e\x64\x5f\x6d\x61\x6e\x79\x5f\x62\x75\x66\x5f\x63");
    return p;
  }
  if ((i ==13)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x63\x6c\x6f\x73\x65\x5f\x73\x6f\x63\x6b\x65\x74\x5f\x63");
    return p;
  }
  if ((i ==14)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x75\x64\x70\x5f\x73\x65\x6e\x64\x5f\x63");
    return p;
  }
  if ((i ==15)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x64\x6e\x73\x5f\x72\x65\x73\x6f\x6c\x76\x65\x5f\x63");
    return p;
  }
  if ((i ==16)) {
    uint8_t * p = ((uint8_t *)"\x6e\x65\x74\x5f\x73\x6f\x63\x6b\x5f\x63\x72\x65\x61\x74\x65\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_net(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_net_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_net_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_set_sym_count(void) {
  return 20;
}
uint8_t * labi_od_set_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x6e\x65\x77\x5f\x69\x33\x32\x5f\x72\x65\x74\x53\x65\x74\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x6e\x65\x77\x5f\x69\x33\x32\x5f\x72\x65\x74\x53\x65\x74\x5f\x75\x36\x34");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x77\x69\x74\x68\x5f\x63\x61\x70\x61\x63\x69\x74\x79\x5f\x53\x65\x74\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x69\x6e\x73\x65\x72\x74\x5f\x53\x65\x74\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x69\x6e\x73\x65\x72\x74\x5f\x53\x65\x74\x5f\x75\x36\x34\x5f\x70\x74\x72\x5f\x75\x36\x34");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x63\x6f\x6e\x74\x61\x69\x6e\x73\x5f\x6b\x65\x79\x5f\x53\x65\x74\x5f\x69\x33\x32\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x63\x6f\x6e\x74\x61\x69\x6e\x73\x5f\x6b\x65\x79\x5f\x53\x65\x74\x5f\x75\x36\x34\x5f\x75\x36\x34");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x72\x65\x6d\x6f\x76\x65\x5f\x53\x65\x74\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x72\x65\x6d\x6f\x76\x65\x5f\x53\x65\x74\x5f\x75\x36\x34\x5f\x70\x74\x72\x5f\x75\x36\x34");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x6c\x65\x6e\x5f\x53\x65\x74\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x6c\x65\x6e\x5f\x53\x65\x74\x5f\x75\x36\x34");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x64\x65\x69\x6e\x69\x74\x5f\x53\x65\x74\x5f\x69\x33\x32\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==12)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x64\x65\x69\x6e\x69\x74\x5f\x53\x65\x74\x5f\x75\x36\x34\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==13)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x74\x72\x5f\x6e\x65\x77");
    return p;
  }
  if ((i ==14)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x74\x72\x5f\x69\x6e\x73\x65\x72\x74");
    return p;
  }
  if ((i ==15)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x65\x74\x5f\x69\x33\x32\x5f\x69\x6e\x73\x65\x72\x74");
    return p;
  }
  if ((i ==16)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x65\x74\x5f\x69\x33\x32\x5f\x63\x6f\x6e\x74\x61\x69\x6e\x73");
    return p;
  }
  if ((i ==17)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x65\x74\x5f\x69\x33\x32\x5f\x72\x65\x6d\x6f\x76\x65");
    return p;
  }
  if ((i ==18)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x65\x74\x5f\x69\x33\x32\x5f\x6c\x65\x6e");
    return p;
  }
  if ((i ==19)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x65\x74\x5f\x73\x65\x74\x5f\x69\x33\x32\x5f\x64\x65\x69\x6e\x69\x74");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_set(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_set_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_set_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_map_sym_count(void) {
  return 9;
}
uint8_t * labi_od_map_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x65\x6d\x70\x74\x79\x5f\x73\x69\x7a\x65");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x6e\x65\x77\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x77\x69\x74\x68\x5f\x63\x61\x70\x61\x63\x69\x74\x79\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x69\x6e\x73\x65\x72\x74\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x67\x65\x74\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x66\x69\x6e\x64\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x64\x65\x69\x6e\x69\x74\x5f\x4d\x61\x70\x5f\x69\x33\x32\x5f\x69\x33\x32\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x73\x74\x72\x5f\x6e\x65\x77");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x6d\x61\x70\x5f\x73\x74\x72\x5f\x69\x6e\x73\x65\x72\x74");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_map(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_map_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_map_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_queue_api_sym_count(void) {
  return 12;
}
uint8_t * labi_od_queue_api_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x6e\x65\x77\x5f\x72\x65\x74\x51\x75\x65\x75\x65\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x6e\x65\x77\x5f\x72\x65\x74\x51\x75\x65\x75\x65\x5f\x75\x38");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x70\x75\x73\x68\x5f\x62\x61\x63\x6b\x5f\x51\x75\x65\x75\x65\x5f\x69\x33\x32\x5f\x70\x74\x72\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x70\x75\x73\x68\x5f\x62\x61\x63\x6b\x5f\x51\x75\x65\x75\x65\x5f\x75\x38\x5f\x70\x74\x72\x5f\x75\x38");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x70\x75\x73\x68\x5f\x66\x72\x6f\x6e\x74");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x70\x6f\x70\x5f\x66\x72\x6f\x6e\x74\x5f\x51\x75\x65\x75\x65\x5f\x69\x33\x32\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x70\x6f\x70\x5f\x62\x61\x63\x6b");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x67\x65\x74");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x6c\x65\x6e\x5f\x51\x75\x65\x75\x65\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x69\x73\x5f\x65\x6d\x70\x74\x79\x5f\x51\x75\x65\x75\x65\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x64\x65\x69\x6e\x69\x74\x5f\x51\x75\x65\x75\x65\x5f\x69\x33\x32\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x71\x75\x65\x75\x65\x5f\x77\x69\x74\x68\x5f\x63\x61\x70\x61\x63\x69\x74\x79");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_queue(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_queue_api_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_queue_api_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_test_sym_count(void) {
  return 12;
}
uint8_t * labi_od_test_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x63\x61\x6c\x6c\x5f\x69\x33\x32\x5f\x76\x6f\x69\x64\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x72\x75\x6e\x6e\x65\x72\x5f");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x65\x78\x70\x65\x63\x74\x5f");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x62\x65\x6e\x63\x68\x5f");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x66\x5f\x74\x65\x73\x74\x5f");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x69\x6f\x5f");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x74\x65\x73\x74\x5f\x66\x75\x7a\x7a\x5f");
    return p;
  }
  if ((i ==7)) { uint8_t * p = ((uint8_t *)"std_test_expect"); return p; }
  if ((i ==8)) { uint8_t * p = ((uint8_t *)"std_test_expect_eq_i32"); return p; }
  if ((i ==9)) { uint8_t * p = ((uint8_t *)"std_test_expect_ne_i32"); return p; }
  if ((i ==10)) { uint8_t * p = ((uint8_t *)"std_test_assert"); return p; }
  if ((i ==11)) { uint8_t * p = ((uint8_t *)"std_test_runner_case"); return p; }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_test(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_test_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_test_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_core_mem_sym_count(void) {
  return 7;
}
uint8_t * labi_od_core_mem_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x61\x6c\x69\x67\x6e\x5f\x75\x70");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x61\x6c\x69\x67\x6e\x5f\x64\x6f\x77\x6e");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x6d\x65\x6d\x5f\x63\x6f\x70\x79");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x6d\x65\x6d\x5f\x73\x65\x74");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x6d\x65\x6d\x5f\x7a\x65\x72\x6f");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x6d\x65\x6d\x5f\x6d\x6f\x76\x65");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x6d\x65\x6d\x5f\x6d\x65\x6d\x5f\x63\x6f\x6d\x70\x61\x72\x65");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_core_mem(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_core_mem_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_core_mem_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_core_slice_sym_count(void) {
  return 6;
}
uint8_t * labi_od_core_slice_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x69\x33\x32\x5f\x66\x72\x6f\x6d\x5f\x70\x74\x72\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x75\x62\x73\x6c\x69\x63\x65\x5f\x69\x33\x32\x5f\x63");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x75\x38\x5f\x66\x72\x6f\x6d\x5f\x70\x74\x72\x5f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x75\x62\x73\x6c\x69\x63\x65\x5f\x75\x38\x5f\x63");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x6c\x69\x63\x65\x5f\x75\x36\x34\x5f\x66\x72\x6f\x6d\x5f\x70\x74\x72\x5f\x63");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x63\x6f\x72\x65\x5f\x73\x75\x62\x73\x6c\x69\x63\x65\x5f\x75\x36\x34\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_core_slice(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_core_slice_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_core_slice_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_page_mmap_sym_count(void) {
  return 5;
}
uint8_t * labi_od_page_mmap_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x68\x65\x61\x70\x5f\x61\x76\x61\x69\x6c\x61\x62\x6c\x65");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x68\x65\x61\x70\x5f\x69\x6e\x69\x74");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x68\x65\x61\x70\x5f\x64\x65\x69\x6e\x69\x74");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x70\x61\x67\x65\x5f\x6d\x6d\x61\x70\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_heap_page_mmap(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_page_mmap_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_page_mmap_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_sys_linux_sym_count(void) {
  return 7;
}
uint8_t * labi_od_sys_linux_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x69\x6e\x76\x6f\x6b\x65\x5f\x61\x76\x61\x69\x6c\x61\x62\x6c\x65");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x61\x6e\x6f\x6e\x79\x6d\x6f\x75\x73\x5f\x6d\x6d\x61\x70");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x6d\x75\x6e\x6d\x61\x70");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x72\x65\x61\x64");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x77\x72\x69\x74\x65");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x63\x6c\x6f\x73\x65");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x65\x78\x69\x74");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_sys_linux(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_sys_linux_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_sys_linux_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_sys_sym_count(void) {
  return 8;
}
uint8_t * labi_od_sys_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x77\x72\x69\x74\x65\x5f\x73\x74\x64\x6f\x75\x74");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x77\x72\x69\x74\x65\x5f\x73\x74\x64\x65\x72\x72");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x77\x72\x69\x74\x65");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x72\x65\x61\x64");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x63\x6c\x6f\x73\x65");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x65\x78\x69\x74");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x66\x72\x65\x65\x73\x74\x61\x6e\x64\x69\x6e\x67\x5f\x77\x72\x69\x74\x65\x5f\x61\x76\x61\x69\x6c\x61\x62\x6c\x65");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x73\x79\x73\x5f\x6c\x69\x6e\x75\x78\x5f\x73\x79\x73\x63\x61\x6c\x6c\x5f\x74\x61\x62\x6c\x65\x5f\x61\x76\x61\x69\x6c\x61\x62\x6c\x65");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_sys(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_sys_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_sys_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_heap_api_sym_count(void) {
  return 25;
}
uint8_t * labi_od_heap_api_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x75\x38");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x75\x38");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x73\x69\x7a\x65\x5f\x7a\x65\x72\x6f");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x75\x73\x69\x7a\x65");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x75\x38\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x64\x65\x66\x61\x75\x6c\x74\x5f\x61\x6c\x6c\x6f\x63");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6b\x69\x6e\x64\x5f\x61\x72\x65\x6e\x61");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x41\x6c\x6c\x6f\x63\x61\x74\x6f\x72\x5f\x75\x73\x69\x7a\x65");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x72\x65\x61\x6c\x6c\x6f\x63\x5f\x41\x6c\x6c\x6f\x63\x61\x74\x6f\x72\x5f\x75\x38\x5f\x70\x74\x72\x5f\x75\x73\x69\x7a\x65");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x41\x6c\x6c\x6f\x63\x61\x74\x6f\x72\x5f\x75\x38\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==12)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x36\x34\x5f\x61\x6c\x6c\x6f\x63");
    return p;
  }
  if ((i ==13)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x36\x34\x5f\x61\x6c\x6c\x6f\x63\x5f\x63");
    return p;
  }
  if ((i ==14)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x63");
    return p;
  }
  if ((i ==15)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x63");
    return p;
  }
  if ((i ==16)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x61\x6c\x69\x67\x6e\x65\x64\x5f\x63");
    return p;
  }
  if ((i ==17)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x69\x33\x32\x5f\x63");
    return p;
  }
  if ((i ==18)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x75\x38\x5f\x63");
    return p;
  }
  if ((i ==19)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x75\x36\x34\x5f\x63");
    return p;
  }
  if ((i ==20)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x69\x33\x32\x5f\x63");
    return p;
  }
  if ((i ==21)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x75\x38\x5f\x63");
    return p;
  }
  if ((i ==22)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x75\x36\x34\x5f\x63");
    return p;
  }
  if ((i ==23)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6d\x61\x70\x5f\x66\x69\x6e\x64");
    return p;
  }
  if ((i ==24)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x68\x65\x61\x70\x5f\x6c\x69\x62\x63\x5f\x68\x65\x61\x70\x5f\x63\x6f\x70\x79\x5f\x75\x38\x5f\x61\x74\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_std_heap_api(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_heap_api_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_heap_api_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_heap_user_sym_count(void) {
  return 7;
}
uint8_t * labi_od_heap_user_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x61\x6c\x6c\x6f\x63\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x66\x72\x65\x65\x5f\x63");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x72\x65\x61\x6c\x6c\x6f\x63\x5f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x36\x34\x5f\x61\x6c\x6c\x6f\x63\x5f\x63");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x5f\x69\x6e\x69\x74\x5f\x63");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x36\x34\x5f\x64\x65\x69\x6e\x69\x74\x5f\x63");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x68\x65\x61\x70\x5f\x61\x72\x65\x6e\x61\x36\x34\x5f\x69\x6e\x69\x74\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_heap_user_syms(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_heap_user_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_heap_user_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_async_scheduler_sym_count(void) {
  return 35;
}
uint8_t * labi_od_async_scheduler_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x63\x6f\x6f\x70\x5f\x70\x69\x6e\x67\x70\x6f\x6e\x67");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x63\x6f\x6f\x70\x5f\x70\x69\x6e\x67\x70\x6f\x6e\x67\x5f\x6a\x6d\x70");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x63\x70\x73\x5f\x73\x75\x73\x70\x65\x6e\x64");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x61\x73\x6d\x5f\x66\x72\x61\x6d\x65\x5f\x70\x68\x61\x73\x65\x5f\x62\x79\x5f\x69\x64");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x61\x73\x6d\x5f\x66\x72\x61\x6d\x65\x5f\x73\x74\x6f\x72\x65\x5f\x66\x72\x6f\x6d\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x61\x73\x6d\x5f\x66\x72\x61\x6d\x65\x5f\x6c\x6f\x61\x64\x5f\x74\x6f\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x61\x73\x6d\x5f\x66\x72\x61\x6d\x65\x5f\x72\x65\x73\x65\x74\x5f\x62\x79\x5f\x69\x64");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x63\x70\x73\x5f\x73\x75\x73\x70\x65\x6e\x64\x5f\x69\x6f");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x74\x61\x73\x6b\x5f\x73\x75\x62\x6d\x69\x74");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x74\x61\x73\x6b\x5f\x73\x75\x62\x6d\x69\x74\x5f\x74\x6f");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x73\x63\x68\x65\x64\x75\x6c\x65\x72\x5f\x64\x72\x61\x69\x6e");
    return p;
  }
  if ((i ==12)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x77\x6f\x72\x6b\x65\x72\x5f\x64\x72\x61\x69\x6e");
    return p;
  }
  if ((i ==13)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x77\x6f\x72\x6b\x65\x72\x5f\x63\x6f\x75\x6e\x74");
    return p;
  }
  if ((i ==14)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x77\x6f\x72\x6b\x65\x72\x5f\x70\x65\x6e\x64\x69\x6e\x67");
    return p;
  }
  if ((i ==15)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x71\x75\x65\x75\x65\x5f\x72\x65\x73\x65\x74");
    return p;
  }
  if ((i ==16)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x73\x63\x68\x65\x64\x75\x6c\x65\x72\x5f\x70\x65\x6e\x64\x69\x6e\x67");
    return p;
  }
  if ((i ==17)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x69\x6f\x5f\x77\x61\x6b\x65\x5f\x61\x6c\x6c");
    return p;
  }
  if ((i ==18)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x69\x6f\x5f\x77\x61\x69\x74\x65\x72\x73\x5f\x70\x65\x6e\x64\x69\x6e\x67");
    return p;
  }
  if ((i ==19)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x69\x6f\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x69\x6f\x6e\x73\x5f\x72\x65\x61\x64\x79");
    return p;
  }
  if ((i ==20)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x73\x65\x74\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==21)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x72\x65\x73\x65\x74");
    return p;
  }
  if ((i ==22)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x70\x75\x73\x68\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==23)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x70\x75\x73\x68\x5f\x75\x33\x32");
    return p;
  }
  if ((i ==24)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x70\x75\x73\x68\x5f\x69\x36\x34");
    return p;
  }
  if ((i ==25)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x76\x61\x6c\x69\x64");
    return p;
  }
  if ((i ==26)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x74\x61\x6b\x65\x5f\x69\x33\x32");
    return p;
  }
  if ((i ==27)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x74\x61\x6b\x65\x5f\x75\x33\x32");
    return p;
  }
  if ((i ==28)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x61\x73\x79\x6e\x63\x5f\x72\x75\x6e\x5f\x73\x65\x65\x64\x5f\x74\x61\x6b\x65\x5f\x69\x36\x34");
    return p;
  }
  if ((i ==29)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x73\x75\x62\x6d\x69\x74\x5f\x72\x65\x61\x64\x5f\x61\x73\x79\x6e\x63");
    return p;
  }
  if ((i ==30)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x5f\x72\x65\x61\x64\x5f\x61\x73\x79\x6e\x63");
    return p;
  }
  if ((i ==31)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x5f\x72\x65\x61\x64\x5f\x61\x73\x79\x6e\x63\x5f\x73\x6c\x6f\x74");
    return p;
  }
  if ((i ==32)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x73\x75\x62\x6d\x69\x74\x5f\x77\x72\x69\x74\x65\x5f\x61\x73\x79\x6e\x63");
    return p;
  }
  if ((i ==33)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x5f\x77\x72\x69\x74\x65\x5f\x61\x73\x79\x6e\x63");
    return p;
  }
  if ((i ==34)) {
    uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x63\x6f\x6d\x70\x6c\x65\x74\x65\x5f\x77\x72\x69\x74\x65\x5f\x61\x73\x79\x6e\x63\x5f\x73\x6c\x6f\x74");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t link_abi_user_o_needs_async_scheduler(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 0;
  }
  if (((user_o)[0] ==0)) {
    return 0;
  }
  int32_t n = labi_od_async_scheduler_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_async_scheduler_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_zlib_undef_sym_count(void) {
  return 8;
}
uint8_t * labi_od_zlib_undef_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x5f\x63\x6f\x6d\x70\x72\x65\x73\x73\x32");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x5f\x64\x65\x66\x6c\x61\x74\x65");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x5f\x69\x6e\x66\x6c\x61\x74\x65");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x5f\x75\x6e\x63\x6f\x6d\x70\x72\x65\x73\x73");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"compress2");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"deflate");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"inflate");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"uncompress");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_compress_zlib_marker(void) {
  uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x63\x6f\x6d\x70\x72\x65\x73\x73\x5f\x7a\x6c\x69\x62\x5f\x6d\x61\x72\x6b\x65\x72");
  return p;
}
int32_t labi_od_zstd_undef_sym_count(void) {
  return 2;
}
uint8_t * labi_od_zstd_undef_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x5a\x53\x54\x44\x5f");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x5f\x5a\x53\x54\x44");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_compress_zstd_marker(void) {
  uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x63\x6f\x6d\x70\x72\x65\x73\x73\x5f\x7a\x73\x74\x64\x5f\x6d\x61\x72\x6b\x65\x72");
  return p;
}
int32_t labi_od_brotli_undef_sym_count(void) {
  return 2;
}
uint8_t * labi_od_brotli_undef_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x42\x72\x6f\x74\x6c\x69\x45\x6e\x63\x6f\x64\x65\x72\x43\x6f\x6d\x70\x72\x65\x73\x73");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x42\x72\x6f\x74\x6c\x69\x44\x65\x63\x6f\x64\x65\x72\x44\x65\x63\x6f\x6d\x70\x72\x65\x73\x73");
    return p;
  }
  return ((uint8_t *)(0));
}
uint8_t * labi_od_compress_brotli_marker(void) {
  uint8_t * p = ((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x63\x6f\x6d\x70\x72\x65\x73\x73\x5f\x62\x72\x6f\x74\x6c\x69\x5f\x6d\x61\x72\x6b\x65\x72");
  return p;
}
int32_t link_abi_obj_needs_zlib(uint8_t * obj_o) {
  if ((obj_o ==0)) {
    return 0;
  }
  if (((obj_o)[0] ==0)) {
    return 0;
  }
  uint8_t * marker = labi_od_compress_zlib_marker();
  if ((marker !=0)) {
    if (((marker)[0] !=0)) {
      int32_t mhit = 0;
      (void)((mhit = link_abi_obj_exports_marker(obj_o, marker)));
      if ((mhit !=0)) {
        return 1;
      }
    }
  }
  int32_t n = labi_od_zlib_undef_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_zlib_undef_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = link_abi_obj_has_undef_sym(obj_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t link_abi_obj_needs_zstd(uint8_t * obj_o) {
  if ((obj_o ==0)) {
    return 0;
  }
  if (((obj_o)[0] ==0)) {
    return 0;
  }
  uint8_t * marker = labi_od_compress_zstd_marker();
  if ((marker !=0)) {
    if (((marker)[0] !=0)) {
      int32_t mhit = 0;
      (void)((mhit = link_abi_obj_exports_marker(obj_o, marker)));
      if ((mhit !=0)) {
        return 1;
      }
    }
  }
  int32_t n = labi_od_zstd_undef_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_zstd_undef_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = link_abi_obj_has_undef_sym(obj_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t link_abi_obj_needs_brotli(uint8_t * obj_o) {
  if ((obj_o ==0)) {
    return 0;
  }
  if (((obj_o)[0] ==0)) {
    return 0;
  }
  uint8_t * marker = labi_od_compress_brotli_marker();
  if ((marker !=0)) {
    if (((marker)[0] !=0)) {
      int32_t mhit = 0;
      (void)((mhit = link_abi_obj_exports_marker(obj_o, marker)));
      if ((mhit !=0)) {
        return 1;
      }
    }
  }
  int32_t n = labi_od_brotli_undef_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_brotli_undef_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = link_abi_obj_has_undef_sym(obj_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t link_abi_user_o_needs_compress_libs(uint8_t * user_o) {
  if ((link_abi_obj_needs_zlib(user_o) !=0)) {
    return 1;
  }
  if ((link_abi_obj_needs_zstd(user_o) !=0)) {
    return 1;
  }
  if ((link_abi_obj_needs_brotli(user_o) !=0)) {
    return 1;
  }
  return 0;
}
int32_t labi_od_runtime_time_os_sym_count(void) {
  return 10;
}
uint8_t * labi_od_runtime_time_os_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x6d\x6f\x6e\x6f\x74\x6f\x6e\x69\x63\x5f\x6e\x73\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x77\x61\x6c\x6c\x5f\x6e\x73\x5f\x63");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x73\x6c\x65\x65\x70\x5f\x6e\x73\x5f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x66\x6f\x72\x6d\x61\x74\x5f\x77\x61\x6c\x6c\x5f\x72\x66\x63\x33\x33\x33\x39\x5f\x63");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x74\x69\x6d\x65\x5f\x77\x61\x6c\x6c\x5f\x6c\x6f\x63\x61\x6c\x5f\x6f\x66\x66\x73\x65\x74\x5f\x6d\x69\x6e\x5f\x63");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x6d\x6f\x6e\x6f\x74\x6f\x6e\x69\x63\x5f\x6e\x73");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x6e\x6f\x77\x5f\x77\x61\x6c\x6c\x5f\x6e\x73");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x73\x6c\x65\x65\x70\x5f\x6d\x73");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x74\x69\x6d\x65\x72\x5f\x73\x74\x61\x72\x74");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x74\x69\x6d\x65\x5f\x64\x75\x72\x61\x74\x69\x6f\x6e\x5f\x6e\x73");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t labi_user_needs_runtime_time_os(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 1;
  }
  if (((user_o)[0] ==0)) {
    return 1;
  }
  int32_t n = labi_od_runtime_time_os_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_runtime_time_os_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_runtime_random_fill_sym_count(void) {
  return 12;
}
uint8_t * labi_od_runtime_random_fill_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x69\x6c\x6c\x5f\x62\x79\x74\x65\x73\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x69\x6c\x6c\x5f\x62\x79\x74\x65\x73");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x69\x6c\x6c");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x6e\x65\x78\x74");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x72\x61\x6e\x67\x65\x5f\x75\x33\x32\x5f\x75\x33\x32");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x67\x65\x6e");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x66\x6c\x69\x70");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x72\x6e\x67\x5f\x73\x6d\x6f\x6b\x65");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x72\x61\x6e\x64\x6f\x6d\x5f\x73\x65\x65\x64");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x72\x61\x6e\x64\x6f\x6d\x5f\x75\x33\x32\x5f\x63");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x72\x61\x6e\x64\x6f\x6d\x5f\x75\x36\x34\x5f\x63");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x72\x61\x6e\x64\x6f\x6d\x5f\x72\x6e\x67\x5f\x73\x6d\x6f\x6b\x65\x5f\x63");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t labi_user_needs_runtime_random_fill(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 1;
  }
  if (((user_o)[0] ==0)) {
    return 1;
  }
  int32_t n = labi_od_runtime_random_fill_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_runtime_random_fill_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_runtime_env_os_sym_count(void) {
  return 19;
}
uint8_t * labi_od_runtime_env_os_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x63");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x65\x78\x69\x73\x74\x73\x5f\x63");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x7a\x5f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x70\x74\x72\x5f\x63");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x73\x65\x74\x65\x6e\x76\x5f\x63");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x75\x6e\x73\x65\x74\x65\x6e\x76\x5f\x63");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x74\x65\x6d\x70\x5f\x64\x69\x72\x5f\x63");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x69\x74\x65\x72\x5f\x63\x6f\x75\x6e\x74\x5f\x63");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x65\x6e\x76\x5f\x69\x74\x65\x72\x5f\x61\x74\x5f\x63");
    return p;
  }
  if ((i ==9)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76");
    return p;
  }
  if ((i ==10)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x65\x78\x69\x73\x74\x73");
    return p;
  }
  if ((i ==11)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x7a");
    return p;
  }
  if ((i ==12)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x67\x65\x74\x65\x6e\x76\x5f\x70\x74\x72");
    return p;
  }
  if ((i ==13)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x73\x65\x74\x65\x6e\x76");
    return p;
  }
  if ((i ==14)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x75\x6e\x73\x65\x74\x65\x6e\x76");
    return p;
  }
  if ((i ==15)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x74\x65\x6d\x70\x5f\x64\x69\x72");
    return p;
  }
  if ((i ==16)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x69\x74\x65\x72");
    return p;
  }
  if ((i ==17)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x69\x74\x65\x72\x5f\x63\x6f\x75\x6e\x74");
    return p;
  }
  if ((i ==18)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x61\x72\x67\x73\x5f\x69\x74\x65\x72");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t labi_user_needs_runtime_env_os(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 1;
  }
  if (((user_o)[0] ==0)) {
    return 1;
  }
  int32_t n = labi_od_runtime_env_os_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_runtime_env_os_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t labi_od_runtime_process_argv_sym_count(void) {
  return 9;
}
uint8_t * labi_od_runtime_process_argv_sym_at(int32_t i) {
  if ((i < 0)) {
    return ((uint8_t *)(0));
  }
  if ((i ==0)) {
    uint8_t * p = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x5f\x78\x6c\x61\x6e\x67\x5f\x61\x72\x67\x63\x5f\x67\x65\x74");
    return p;
  }
  if ((i ==1)) {
    uint8_t * p = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x5f\x78\x6c\x61\x6e\x67\x5f\x61\x72\x67\x76\x5f\x67\x65\x74");
    return p;
  }
  if ((i ==2)) {
    uint8_t * p = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x5f\x63");
    return p;
  }
  if ((i ==3)) {
    uint8_t * p = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x73\x5f\x63\x6f\x75\x6e\x74\x5f\x63");
    return p;
  }
  if ((i ==4)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x73");
    return p;
  }
  if ((i ==5)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67");
    return p;
  }
  if ((i ==6)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x63");
    return p;
  }
  if ((i ==7)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x61\x72\x67\x76");
    return p;
  }
  if ((i ==8)) {
    uint8_t * p = ((uint8_t *)"\x73\x74\x64\x5f\x65\x6e\x76\x5f\x61\x72\x67\x73\x5f\x69\x74\x65\x72");
    return p;
  }
  return ((uint8_t *)(0));
}
int32_t labi_user_needs_runtime_process_argv(uint8_t * user_o) {
  if ((user_o ==0)) {
    return 1;
  }
  if (((user_o)[0] ==0)) {
    return 1;
  }
  int32_t n = labi_od_runtime_process_argv_sym_count();
  int32_t i = 0;
  while ((i < n)) {
    uint8_t * sym = labi_od_runtime_process_argv_sym_at(i);
    if ((sym !=0)) {
      if (((sym)[0] !=0)) {
        int32_t hit = 0;
        (void)((hit = xlang_link_obj_needs_undef_sym(user_o, sym)));
        if ((hit !=0)) {
          return 1;
        }
      }
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
