#!/usr/bin/env bash
# prove_module_selfhost.sh — 单模块自举验证（.o 符号差分）
#
# 自举方法 P0 工具：验证某模块的 .x → .o 与 seed gen.c → .o 符号一致
# 这是比 C 源码 diff 更准确的差分验证（符号层面 = 功能层面等价）
#
# 用法：bash tests/prove_module_selfhost.sh [模块名...]
#   不传参数 = 验证所有已配置模块
#   传模块名 = 只验证指定模块（如：fmt check test build run diagnostic）
#
# 输出：每个模块的 xlang-E / cc-c / nm-diff 状态
#
# 模式（第 5 字段，可选）：
#   （空）  IDENTICAL — 已定义符号完全一致 → 可退役 seed（计入 N）
#   core:a,b,c  CORE — x 定义符号 ⊆ seed，允许 x 独有辅助符号 a,b,c
#               （hybrid thin/C-tail seed 的中间门禁；不计 N 退役）

set -u
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT/compiler" || exit 1

# 模块配置（模块名|.x路径|seed路径|符号重命名|模式）
# 符号重命名映射格式：old1:new1,old2:new2,...
# 模式：空 | core:x_only_sym1,x_only_sym2
MODULES=(
  "fmt|src/driver/fmt.x|driver_fmt_gen.c|cmd_fmt:driver_cmd_fmt|"
  "check|src/driver/check.x|driver_check_gen.c|cmd_check:driver_cmd_check|"
  "test|src/driver/test.x|driver_test_gen.c|cmd_test:driver_cmd_test|"
  "build|src/driver/build.x|driver_build_gen.c|cmd_build:build_cmd_build|"
  "run|src/driver/run.x|driver_run_gen.c|cmd_run:driver_cmd_run,run_eq_word:driver_run_eq_word|"
  "compile|src/driver/compile.x|driver_compile_gen.c|compile_dispatch_asm_backend:driver_compile_dispatch_asm_backend,compile_dispatch_emit_c_path:driver_compile_dispatch_emit_c_path,eq_minus_o:driver_eq_minus_o,eq_minus_L:driver_eq_minus_L,eq_minus_backend:driver_eq_minus_backend,eq_minus_target:driver_eq_minus_target,eq_minus_target_cpu:driver_eq_minus_target_cpu,eq_print_target_cpu:driver_eq_print_target_cpu,eq_minus_O:driver_eq_minus_O,eq_flto:driver_eq_flto,eq_minus_freestanding:driver_eq_minus_freestanding,eq_legacy_f32_abi:driver_eq_legacy_f32_abi,eq_fsanitize_address:driver_eq_fsanitize_address,eq_asm_word:driver_eq_asm_word,eq_c_word:driver_eq_c_word,path_ends_x:driver_path_ends_x,target_has_arm:driver_target_has_arm,run_compiler_full_x_post_parse:driver_run_compiler_full_x_post_parse,run_compiler_full_x:driver_run_compiler_full_x|"
  "emit|src/driver/emit.x|driver_emit_gen.c|emit_copy_lib_roots_to_ctx:driver_emit_copy_lib_roots_to_ctx,run_x_emit_x:driver_run_x_emit_x,dispatch_x_emit_to_c:driver_dispatch_x_emit_to_c,emit_state_key:driver_emit_state_key,pipeline_dep_ctx_fill_for_emit:driver_pipeline_dep_ctx_fill_for_emit|"
  # lsp_io_std_heap：Track L 退役叶子；prove 锁 nm vs 入库 seed pin（禁工作区 gitignore 的 *_gen.c）
  # PLATFORM: SHARED — seed 不可再声明 uint8_t* malloc 与 stdlib void* 冲突（Ubuntu seed cc）
  "lsp_io_std_heap|src/lsp/lsp_io_std_heap.x|seeds/lsp_io_std_heap_gen.linux.x86_64.c|std_heap_alloc:lsp_io_std_heap_std_heap_alloc,std_heap_alloc_zeroed:lsp_io_std_heap_std_heap_alloc_zeroed,std_heap_free:lsp_io_std_heap_std_heap_free|"
  # token：enum+Token+token_is_eof；产品链仍用 include/token.h（C 头），本条锁 nm 面 / 扩 N
  "token|src/lexer/token.x|token_gen.c||"
  # lsp_diag_pipeline_sizes：三枚 sizeof 门闩；产品 sizes_nostub PREFER_X_O；本条锁 nm / 扩 N
  "lsp_diag_pipeline_sizes|src/lsp/lsp_diag_pipeline_sizes.x|seeds/lsp_diag_pipeline_sizes.from_x.c||"
  # labi_path_pure R2 full：.x 吃满公共门闩 + count（wave116 try_under + wave146–151 + wave160 compiler_o_path_copy + wave162 repo_root + wave163–166 path ladders + wave180 scheduler_o_for_task_link + wave181 bootstrap_nostdlib_stubs_o_path + wave183 29× thin runtime_*_o_path BSS + wave184 empty_cstr/std_io/compress/effective_link + wave185 rel_o_path） + wave189 set/clear user_o_files + wave253/258 user_env path + push_minimal companion + wave262 private helper short names (no_mangle)；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：Windows #if sep 在 mega 冷路径；bank_push/rel/skip Cap；resolve Cap（wave160/184）；resolve+rel Cap（wave162）；realpath+getcwd+skip Cap（wave163）
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_path_pure.from_x.c 全 C 体
  "labi_path_pure|src/runtime/labi_path_pure.x|seeds/labi_path_pure_surface.from_x.c||"
  # labi_gates R2 full：.x 吃满 6 thin gates + count（*u8 透传 _impl）；
  # mega rest 在 FROM_X 下业务 H=0；Cap residual：*_impl 主体在 mega rest
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_gates.from_x.c 全 C 体
  "labi_gates|src/runtime/labi_gates.x|seeds/labi_gates_surface.from_x.c||"
  # labi_invoke_cc_list R2 full：.x 吃满 harden/skip-native/icc rel 纯表 + wave155 harden orch + wave198 early_needs + wave199 std need scan + wave200 ensure-push front + wave201 ensure-push mid + wave202 ensure-push heavy_a + wave203 ensure-push heavy_b
  # + wave260 g05 L5 default PREFER full .x（历史 cold-seed-only STRING_LIT leave-off 闭）
  # + wave204 heap F-06 + wave205 fork-exec + wave206 argv head + wave207 argv tail + wave208 MINIMAL_CC_LINK tail
  # + wave155 xlang_append_linux_link_harden_impl pure orch；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：getenv 🔒 + mega invoke_cc_impl
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_invoke_cc_list.from_x.c 全 C 体
  "labi_invoke_cc_list|src/runtime/labi_invoke_cc_list.x|seeds/labi_invoke_cc_list_surface.from_x.c||"
  # labi_invoke_ld_list R2 full：.x 吃满 brew/compress/tail/driver/entry 纯表 + wave152 brew orch
  # + wave153 asm_ld_append_compress_libs pure orch + wave154 invoke_cc_append_compress_ld pure orch
  # + wave156 xlang_asm_ld_append_mach_tail_libs_impl pure orch
  # + wave157 xlang_asm_ld_append_unix_gcc_tail_libs_impl pure orch
  # + wave158 invoke_cc_append_net_tls_ld pure orch（exports_marker/realpath/rel_o Cap）
  # + wave179 invoke_cc_argv_push_existing pure orch（Cap residual resolve pool）
  # + wave187 ensure_std_net_o_auto_tls pure orch（Cap residual getenv+system+realpath+exports_marker）；
  # + wave188 xlang_ensure_formal_std_make_o pure orch（Cap residual getenv+access+realpath+system+skip_missing）；
  # + wave191 labi_std_append_formal_ensure_for_rel pure orch（Cap residual repo_root + ensure_runtime_* + peer push_obj；append_std formal companions）；
  # + wave192 labi_std_append_glue_for_op pure orch（Cap residual ensure_runtime_*_glue + peer path + push_obj；append_std OP_GLUE_*）；
  # + wave193 labi_std_append_primary_for_op + process_argv_if pure orch（Cap residual needs_* + ensure/path + process_argv；append_std PRIMARY/IO_STUBS + complement）；
  # + wave253/259 PRIMARY_PANIC companion user_env ensure+push（surface re-pin ≡ .x/cold）；
  # + wave194 labi_std_append_task_special pure orch（Cap residual skip/path/bank + formal ensure；append_std TASK_SPECIAL task+scheduler+glue）；
  # + wave195 labi_std_append_op_std pure orch（fk→flag_out map + fk0/fk1–13 gate + formal ensure + push_obj；append_std OP_STD）；
  # + wave196 xlang_asm_ld_append_std_objs_for_user plan shell pure orch（flags/local_have init + plan loop + dispatch wave190–195 leaves + process_argv complement）；
  # + wave215/255 invoke_cc_argv_resolve_existing_path pure（null/empty+skip_missing；_impl realpath pool only）；
  # + wave262 private helper short names（labi_std_glue_push_if / op_std_flag_out / glue_have_for_op / need_process_argv no_mangle）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：host_is_apple + needs+ensure+path + resolve_existing_path_impl (pool only wave255) + exports_marker/realpath/rel_o + spawn/ld/cc IO mega + getenv/system shell make
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_invoke_ld_list.from_x.c 全 C 体
  "labi_invoke_ld_list|src/runtime/labi_invoke_ld_list.x|seeds/labi_invoke_ld_list_surface.from_x.c||"
  # labi_freestanding_list R2 full：.x 吃满 env/io_sym/panic/ensure + wave117 heap/nostdlib + wave136 gen needs + wave137 compress + wave138 core_slice/db + wave139 provides_core_mem/std_heap + wave141 needs_win32/wsa + wave142 needs_core_builtin/mem stub0 + wave143 needs_async_scheduler + wave144 freestanding needs_io/panic + wave159 freestanding_enabled + wave167 ensure_crt0_user_o + wave168 ensure_freestanding_io_o + wave175 contains_substr + wave176 contains_substr_use_line + wave177 any_substr_use_line + wave178 any_substr 纯表+orch；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：buf scan/use_line + undef_sym + resolve/access/cc/stat（ensure 叶）
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_freestanding_list.from_x.c 全 C 体
  "labi_freestanding_list|src/runtime/labi_freestanding_list.x|seeds/labi_freestanding_list_surface.from_x.c||"
  # labi_std_list R2 full：.x 吃满 58 步 plan + default_std_rel 纯表；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：IO/ensure/push 在 mega append_std_objs
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_std_list.from_x.c 全 C 体
  "labi_std_list|src/runtime/labi_std_list.x|seeds/labi_std_list_surface.from_x.c||"
  # labi_ondemand_list R2 full：.x 吃满 simple/kv/arrow/time/queue + rel_* + wave118–135 needs_std_net/set/map/queue/test + needs_core_mem/slice + needs_std_heap_page_mmap + needs_std_sys_linux + needs_std_sys + needs_std_heap_api + needs_heap_user_syms + needs_async_scheduler + compress family + labi_user_needs_runtime time_os/random_fill/env_os/process_argv + labi_user_needs_std_task + labi_std_fk0_user_needs_rel + wave140 user_o_provides_core_mem/std_heap 纯表+orch + wave145 link_needs_heap_user_c/std_heap_import 聚合 pure orch + wave190 labi_std_fk_gate_sym_* + labi_std_fk_user_needs (fk1–13 plan gates) + wave197 xlang_asm_ld_append_on_demand_user_objs pure orch（on_demand 产品壳）+ wave210 has_undef_sym pure thin orch + wave211 exports_marker pure thin orch + wave212 needs_undef_sym pure thin orch + wave213 has_defined_sym pure thin orch；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：nm/push/ensure + has_undef_impl / needs_undef_impl / exports_marker_impl / has_defined_impl
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_ondemand_list.from_x.c 全 C 体
  # wave263: L8b early pure + L8c heavy capacity split (parse-skip of 14 late exports closed)
  "labi_ondemand_list|src/runtime/labi_ondemand_list.x|seeds/labi_ondemand_list_surface.from_x.c||"
  "labi_ondemand_heavy|src/runtime/labi_ondemand_heavy.x|seeds/labi_ondemand_heavy_surface.from_x.c||"
  # labi_ensure_list R2 full：.x 吃满 ensure catalog 纯表（27 条目 stem/out/seed/flags/step_at；wave253 user_env）
  #   + wave173 ensure_from_catalog + wave174 catalog thin + wave169–172/182 special ensure
  #   + wave186 prepare_for_exe_link pure orch
  #   + wave173 link_abi_ensure_from_catalog pure orch
  #   + wave174 catalog thin ensure wraps pure（27× xlang_ensure_runtime_*_o incl. link_abi_user_env）
  #   + wave169 ensure_runtime_panic_o + wave170 ensure_runtime_heap_user_o
  #   + wave171 ensure_runtime_test_fn_invoke_o + wave172 ensure_runtime_tls_mbedtls_bio_o pure orch
  #   + wave182 ensure_bootstrap_nostdlib_stubs_o pure orch（-fno-builtin one_extra；peer path wave181）；
  #   + wave253/256: xlang_ensure_runtime_link_abi_user_env_o + prepare companion；surface re-pin gate 27；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：resolve/access/cc/stat (+ one_extra catalog flags)；
  #   panic ensure resolve/access/cc/stat + host linux_x86_64/posix_aarch64；heap_user has_defined_sym + unlink stub；
  #   tls_mbedtls_bio ensure resolve/access/cc_one_extra/stat（homebrew -I）；thin wrap path peers *_o_path
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_ensure_list.from_x.c 全 C 体
  "labi_ensure_list|src/runtime/labi_ensure_list.x|seeds/labi_ensure_list_surface.from_x.c||"
  # labi_path_io R2 full：.x 吃满 6 公共门闩 + count（wave209 path_readable + wave218 realpath_cap + wave221 path_executable）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：stat/realpath_if/access R_OK+X_OK/realpath_cap _impl 在 mega rest
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_path_io.from_x.c 全 C 体
  "labi_path_io|src/runtime/labi_path_io.x|seeds/labi_path_io_surface.from_x.c||"
  # labi_host_lit R2 full：.x 吃满 2 公共门闩 + count；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：#if host _impl 在 mega rest
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_host_lit.from_x.c 全 C 体
  "labi_host_lit|src/runtime/labi_host_lit.x|seeds/labi_host_lit_surface.from_x.c||"
  # labi_diag_pure R2 full：.x 吃满 code_for_kind + 7 report 消息体 + count；
  # + wave216 waitpid pure thin + wave217 strerror/wait decode pure thin
  # + wave219 spawn_sync pure thin（null/empty gates；Cap residual fork/exec/_spawnvp _impl）
  # + wave220 strip_out_x pure thin（null/empty gates；Cap residual argv pack+spawn _impl）
  # + wave222 link_abi_getenv pure thin（null/empty name gates；Cap residual host getenv _impl）
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：ld_debug_argv + wait/strerror/spawn/strip/getenv _impl 在 mega rest
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/labi_diag_pure.from_x.c 全 C 体
  "labi_diag_pure|src/runtime/labi_diag_pure.x|seeds/labi_diag_pure_surface.from_x.c||"
  # diagnostic R2 thin + Cap residual pure deep-migrate: thin.x gates + fixed-msg/pipe orch + assemble pure + getenv
  # + report_prefixed/pipe_note + debug_log/parser_diag_* + typeck_block/fn/var + scratch BSS
  # + parse_fail/codegen_fail/typeck_func_fail/ptr_field/ret_fail pure (append+note/code; rest T 28→23)
  # + parse_skip/commit_fail XP002/func_generic/onefunc_param/import_const/warn_pad/warn_hot/hint_unused
  #   pure (append; rest T 23→15)
  # + binop/commit_shape(+parser alias) pure (append; rest T 15→12)
  # + after_entry_parse_module/codegen_emit_func_fail pure (pipeline API+append; rest T 12→10);
  # + asm BSS store/set/trace/print/var/fail pure (module BSS+append; rest T 10→4);
  # + wave6: slice_marker pure; lsp_get G.7 → runtime_lsp_glue; FROM_X drops dead va_list report → rest T=0
  # rest FROM_X no pure-dup _impl for pure set; prove locks thin surface IDENTICAL
  # cold/no PREFER still full C seeds/runtime_driver_diagnostic.from_x.c
  "diagnostic|src/runtime_driver_diagnostic_thin.x|seeds/runtime_driver_diagnostic_thin_surface.from_x.c||"
  # driver_abi R2 thin + pure 深迁：thin.x 门闩 + pure 真体（scan/has/argv/target_os/fail/smoke/peek/
  # entry_i32/large_stack orch + getenv 门闩 + 数值 env stack_limit_want/parse_u32/phase_timing_enabled）；
  # + wave1 Cap residual pure：9× flag-slot BSS 进 thin；+ wave2 path/len BSS pure（dep path ·
  #   entry_source_len · path_last_preprocess_len）；+ wave3 format print pure（check_ok/fail/smoke
  #   append+diag_report*）；+ wave4 defines_set_at（xlang_ptr_slot_set）+ os_define_lit pure；
  #   + wave5 phase timing BSS + begin/end pure；
  #   + wave6 phase_timing_flush pure（whole-ms append+diag_report；no reportf floats）；
  #   + wave7 compile_phase_now_sec pure（→ xlang_driver_wall_clock_sec OS surface）；
  #   + wave8 call_fn pure orch（→ xlang_driver_call_fn_void_arg OS surface；.x 无间接调用）；
  #   + wave9 bump_stack_limit pure orch（→ xlang_driver_bump_stack_limit setrlimit OS surface）；
  #   + wave10 uname host defines pure orch（→ xlang_driver_argv_append_uname OS surface；no utsname in .x）；
  #   + wave11 path-read pure orch（→ xlang_driver_path_read_preprocess_malloc OS surface；no file-view in .x）；
  #   + wave12 pthread pure orch（→ xlang_driver_run_thread_on_large_stack_pthread OS surface；no pthread_attr in .x）；
  #   + wave13 entry_source_len load debug note pure（XLANG_DEBUG_PIPE truthy → append_*+diag_report；no reportf）；
  #   rest FROM_X 无 pure-dup flag_slot/path-len/format/set_at/os_lit/begin/end/flush/now_sec/call_fn/setrlimit/uname/path_read/pthread/load_debug _impl；
  # Cap residual pure leaf closed for driver_abi debug_pipe note（OS Cap rest _impl=0）
  # prove 锁 thin surface IDENTICAL；冷/无 PREFER 仍可走 seeds/runtime_driver_abi.from_x.c 全 C 体
  "driver_abi|src/runtime_driver_abi_thin.x|seeds/runtime_driver_abi_thin_surface.from_x.c||"
  # runtime_io_abi R2 full：.x 吃满 19 公共门闩 + 5 _impl 真迁（read/malloc/memcpy）；
  # rest 在 XLANG_L2_RIO_THIN_FROM_X+FROM_X 下无 thin/impl 公共体；Cap residual：4 平台 _impl（mmap/fstat/O_*）
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/runtime_io_abi.from_x.c 全 C 体
  "runtime_io_abi|src/runtime_io_abi.x|seeds/runtime_io_abi_surface.from_x.c||"
  # runtime_time_os R2 thin+rest：.x 吃满 5 public API 薄壳（monotonic/wall/sleep/rfc3339/local_offset）；
  # rest 在 XLANG_RUNTIME_TIME_OS_FROM_X 下仅 5 _impl OS 桥（clock_gettime/nanosleep/gmtime_r/QPC/Sleep 等 Cap residual）；
  # prove 锁 thin surface IDENTICAL；冷/无 PREFER 仍可走 seeds/runtime_time_os.from_x.c 全 C 体
  "runtime_time_os|src/asm/runtime_time_os.x|seeds/runtime_time_os_surface.from_x.c||"
  # runtime_path_fast R2 full DIRECT：.x 吃满 16 path helpers（sep/is_sep/last_sep/last_dot/empty_len/
  # join/dirname/basename/is_absolute/is_sep/extension/stem/extension_and_stem/clean/resolve）纯计算无 OS 依赖；
  # DIRECT 模式（无 thin+rest ld -r）；prove 锁 full surface IDENTICAL；
  # 冷/无 PREFER 仍可走 seeds/runtime_path_fast.from_x.c 全 C 体
  "runtime_path_fast|src/asm/runtime_path_fast.x|seeds/runtime_path_fast_surface.from_x.c||"
  # runtime_dynlib_os R2 thin+rest：.x 吃满 7 public API（normalize_path pure compute +
  # 6 _impl 委托：load_library/copy_last_error/open/sym/close/win_path_smoke）；
  # rest 在 XLANG_RUNTIME_DYNLIB_OS_FROM_X 下仅 6 _impl OS 桥（LoadLibraryW/dlopen/dlsym/
  # dlclose/dlerror/FormatMessage 等 Cap residual）；prove 锁 thin surface IDENTICAL；
  # 冷/无 PREFER 仍可走 seeds/runtime_dynlib_os.from_x.c 全 C 体
  "runtime_dynlib_os|src/asm/runtime_dynlib_os.x|seeds/runtime_dynlib_os_surface.from_x.c||"
  # runtime_panic R2 thin+rest：.x 1 public API (xlang_crash_evidence_minimal) + 1 _impl 桥；
  # rest 在 XLANG_RUNTIME_PANIC_FROM_X 下仅 1 _impl OS 桥（crash evidence minimal）；
  # prove 锁 thin surface IDENTICAL；x86_64 变体（与 arm64 互斥）
  "runtime_panic|src/asm/runtime_panic.x|seeds/runtime_panic_surface.from_x.c||"
  # runtime_panic_arm64 R2 thin+rest：arm64 变体，结构与 runtime_panic 相同；
  # prove 锁 thin surface IDENTICAL；arm64 变体（与 x86_64 互斥）
  "runtime_panic_arm64|src/asm/runtime_panic_arm64.x|seeds/runtime_panic_arm64_surface.from_x.c||"
  # runtime_process_argv R2 thin+rest：.x 1 public API (xlang_process_argv_bind_from_crt) + 1 _impl 桥；
  # rest 在 XLANG_RUNTIME_PROCESS_ARGV_FROM_X 下仅 1 _impl OS 桥（macOS _NSGetArgc / Linux /proc/self/cmdline）；
  # prove 锁 thin surface IDENTICAL
  "runtime_process_argv|src/asm/runtime_process_argv.x|seeds/runtime_process_argv_surface.from_x.c||"
  # runtime_test_fn_invoke R2 thin+rest：.x 1 public API (test_call_i32_void_c) + 1 _impl 桥；
  # rest 在 XLANG_RUNTIME_TEST_FN_INVOKE_FROM_X 下仅 1 _impl 桥（uintptr_t → fnptr cast + indirect call）；
  # Xlang 无法表达 C fnptr cast，故 indirect call 留 rest；prove 锁 thin surface IDENTICAL
  "runtime_test_fn_invoke|src/asm/runtime_test_fn_invoke.x|seeds/runtime_test_fn_invoke_surface.from_x.c||"
  # runtime_net_workers R2 thin+rest：.x 2 public API (thread_set_affinity_self_c weak default +
  #   xlang_net_worker_accept_entry_ptr_c fnptr return) + 1 _impl 桥；
  # rest 在 XLANG_RUNTIME_NET_WORKERS_FROM_X 下仅 _impl 桥（void*(*)(void*) C ABI 无法 .x 表达）；
  # prove 锁 thin surface IDENTICAL
  "runtime_net_workers|src/asm/runtime_net_workers.x|seeds/runtime_net_workers_surface.from_x.c||"
  # runtime_compress_zlib_glue R2 thin+rest：.x 2 public API (deflateInit2 + inflateInit2 宏 wrapper)
  #   + 2 _impl 桥；rest #include <zlib.h> + #undef macros + call real deflateInit2_/inflateInit2_；
  # #[no_mangle] 确保符号名匹配 libz.x extern 声明（无 _c 后缀）；prove 锁 thin surface IDENTICAL
  "runtime_compress_zlib_glue|src/asm/runtime_compress_zlib_glue.x|seeds/runtime_compress_zlib_glue_surface.from_x.c||"
  # runtime_arrow_simd_glue R2 thin+rest：.x 4 public API (arrow_f32_sum/dot/i32_sum_valid/f32_sum_valid_kernel)
  #   + 4 _impl 桥；rest 含 SIMD intrinsics（需 C compiler target attributes）；prove 锁 thin surface IDENTICAL
  "runtime_arrow_simd_glue|src/asm/runtime_arrow_simd_glue.x|seeds/runtime_arrow_simd_glue_surface.from_x.c||"
  # runtime_random_fill R2 thin+rest (wave544)：.x 2 public API (random_get_alg + random_fill_bytes_c)
  #   + 2 _impl 桥；rest 含 OS CSPRNG 调用（Windows BCryptGenRandom / Linux getrandom / macOS getentropy）；
  #   #[no_mangle] 确保符号名匹配 std/crypto/random.x extern 声明（无 _c 后缀）；prove 锁 thin surface IDENTICAL
  "runtime_random_fill|src/asm/runtime_random_fill.x|seeds/runtime_random_fill_surface.from_x.c||"
  # runtime_tls_mbedtls_bio R2 thin+rest (wave544)：.x 2 public API (xlang_mbedtls_bio_send + _recv)
  #   + 2 _impl 桥；rest 调用 mbedtls BIO send/recv（需 mbedtls 头）；prove 锁 thin surface IDENTICAL
  "runtime_tls_mbedtls_bio|src/asm/runtime_tls_mbedtls_bio.x|seeds/runtime_tls_mbedtls_bio_surface.from_x.c||"
  # runtime_ed25519_ref10_glue R2 thin+rest (wave544)：.x 3 public API (ed25519_ref10_create_keypair + _sign + _verify)
  #   + 3 _impl_c 桥；rest #include 8 个 .inc 文件（sha512/fe/ge/sc/keypair/sign/verify + fixedint.h）经宏重命名发射
  #   _impl_c 实现；#[no_mangle] 确保符号名匹配 std/crypto/ed25519.x extern 声明（无 _c 后缀）；prove 锁 thin surface IDENTICAL
  "runtime_ed25519_ref10_glue|src/asm/runtime_ed25519_ref10_glue.x|seeds/runtime_ed25519_ref10_glue_surface.from_x.c||"
  # runtime_net_udp_batch R2 thin+rest (wave545)：.x 2 public API (xlang_udp_batch_set_addr_port + _poll_readable)
  #   + 2 _impl 桥；rest 含 sockaddr_in pack + poll/WSAPoll OS 调用；prove 锁 thin surface IDENTICAL
  "runtime_net_udp_batch|src/asm/runtime_net_udp_batch.x|seeds/runtime_net_udp_batch_surface.from_x.c||"
  # runtime_net_sock_fast R2 thin+rest (wave545)：.x 2 public API (net_ensure_wsa + net_wsa_ctor)
  #   + 2 _impl_c 桥；rest 含 Windows WSAStartup + constructor（POSIX no-op stub）；wave545 根修 .x extern
  #   _impl → _impl_c 匹配 seed；prove 锁 thin surface IDENTICAL
  "runtime_net_sock_fast|src/asm/runtime_net_sock_fast.x|seeds/runtime_net_sock_fast_surface.from_x.c||"
  # runtime_net_dns_fast R2 thin+rest (wave545)：.x 3 public API (net_dns_ai_addconfig_c + _map_gai_error_c + _ensure_wsa_c)
  #   + 3 _impl_c 桥；rest 含 getaddrinfo hints + gai error map + WSA init；wave545 根修 .x extern
  #   _impl → _impl_c 匹配 seed；prove 锁 thin surface IDENTICAL
  "runtime_net_dns_fast|src/asm/runtime_net_dns_fast.x|seeds/runtime_net_dns_fast_surface.from_x.c||"
  # runtime_net_ipv6_fast R2 thin+rest (wave545)：.x 5 public API (net_ipv6_ensure_wsa_c + _close_socket_c +
  #   _set_nonblock_c + _poll_writable_c + _connect_retry_ok_c) + 5 _impl_c 桥；rest 含 IPv6 socket OS 调用
  #   (close/fcntl/poll/connect)；wave545 根修 .x extern _impl → _impl_c 匹配 seed；prove 锁 thin surface IDENTICAL
  "runtime_net_ipv6_fast|src/asm/runtime_net_ipv6_fast.x|seeds/runtime_net_ipv6_fast_surface.from_x.c||"
  # runtime_net_addr_fast R2 thin+rest (wave546)：.x 1 public API (net_sockaddr_in_pack_addr_port_c)
  #   thin+rest — .x 1 thin 函数（手动字节解析无 libc）；seed 4 rest 函数（getsockname/getpeername +
  #   htonl/htons — asm codegen u16 store bug workaround）；ast_ 前缀适配（net_ #[no_mangle] 触发）
  "runtime_net_addr_fast|src/asm/runtime_net_addr_fast.x|seeds/runtime_net_addr_fast_surface.from_x.c||"
  # runtime_slice_glue R2 DIRECT (wave546)：.x 6 public API (3 core_slice_*_from_ptr_c + 3 core_subslice_*_c)
  #   DIRECT — 纯 .x 实现（无 extern 桥，无 OS 调用，纯寄存器运算）；seed 全守卫 #ifndef
  #   XLANG_RUNTIME_SLICE_GLUE_FROM_X；无 Cap residual；prove 锁 thin surface IDENTICAL
  "runtime_slice_glue|src/asm/runtime_slice_glue.x|seeds/runtime_slice_glue_surface.from_x.c||"
  # runtime_crypto_inc_glue R2 thin+rest (wave547)：.x 6 public API (xlang_sha256_block + _rotr32 + _ch + _maj +
  #   crypto_i32_sub_c + crypto_rotl32_c) + 6 _impl 桥；rest 含 sha256 block/rotr/ch/maj + crypto_i32_sub/rotl32
  #   纯 C 算术（无 OS 调用）；xlang_/crypto_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL
  "runtime_crypto_inc_glue|src/asm/runtime_crypto_inc_glue.x|seeds/runtime_crypto_inc_glue_surface.from_x.c||"
  # runtime_sync_lock_diag_tls R2 mixed (wave547)：.x 5 public API (sync_lock_diag_find_meta_idx + get_order +
  #   append_byte + append_lit + append_i32) — 2 thin+rest (find_meta_idx + get_order _impl 桥) +
  #   3 DIRECT (append_byte/lit/i32 纯计算)；rest 含 pthread_mutexattr protocol lookup；
  #   sync_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL
  "runtime_sync_lock_diag_tls|src/asm/runtime_sync_lock_diag_tls.x|seeds/runtime_sync_lock_diag_tls_surface.from_x.c||"
  # runtime_std_runtime_fast R2 DIRECT (wave548)：.x 6 public API (std_runtime_crash_evidence_collect +
  #   runtime_crash_evidence_collect_c + std_runtime_runtime_panic + runtime_panic + std_runtime_runtime_abort +
  #   runtime_abort) DIRECT — 纯转发到 xlang_panic_/_crash_evidence_collect_c extern 桥；seed 全守卫；
  #   无 doc_anchor 函数（.x 未定义）；prove 锁 6 #[no_mangle] IDENTICAL
  "runtime_std_runtime_fast|src/asm/runtime_std_runtime_fast.x|seeds/runtime_std_runtime_fast_surface.from_x.c||"
  # runtime_atomic_glue R2 thin+rest (wave548)：.x 30 public API (atomic_load/store/cas/fetch_add/fetch_sub ×
  #   i16/u16/i32/u32/i64/u64 + 3 fence) + 30 _impl 桥；rest 含 C11 stdatomic/GCC __atomic intrinsics；
  #   atomic_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL
  "runtime_atomic_glue|src/asm/runtime_atomic_glue.x|seeds/runtime_atomic_glue_surface.from_x.c||"
  # runtime_asm_build R2 thin(extern) (wave549)：.x 2 public API (asm_driver_skip_codegen_dep_0_get +
  #   asm_driver_set_current_dep_path_for_codegen) thin(extern) — 纯转发到 driver_abi extern C 桥；
  #   seed 全守卫；cap residual: main()（.x 无法表达 char** argv）；无 doc_anchor 函数；
  #   asm_ 前缀不触发 ast_；prove 锁 2 #[no_mangle] IDENTICAL
  "runtime_asm_build|src/asm/runtime_asm_build.x|seeds/runtime_asm_build_surface.from_x.c||"
  # runtime_asm_io_stubs R2 thin+rest (wave549)：.x 3 public API (seed_io_syscall_write +
  #   seed_io_syscall_read + seed_io_write_fd1) + 3 _impl 桥；rest 含 Linux x86_64 inline asm syscall
  #   + POSIX write/read；doc_anchor runtime_asm_io_stubs_x_doc_anchor；seed_ 前缀不触发 ast_；
  #   prove 锁 thin surface IDENTICAL (3 #[no_mangle] + 1 doc_anchor)
  "runtime_asm_io_stubs|src/asm/runtime_asm_io_stubs.x|seeds/runtime_asm_io_stubs_surface.from_x.c||"
  # runtime_string_fast R2 DIRECT (wave549)：.x 8 public API (xlang_string_memrchr/memchr/
  #   portable_memmem/memmem/ptr_at/memcmp/memcmp_at/copy_c) DIRECT — 纯计算 + libc memcmp/memcpy
  #   extern 桥；seed 全守卫；doc_anchor ast_runtime_string_fast_x_doc_anchor（非 #[no_mangle]
  #   export function，xlang-c 自动加 ast_ 前缀，同 path_fast/net_sock_fast 规律）；
  #   prove 锁 8 #[no_mangle] + 1 ast_ doc_anchor IDENTICAL
  "runtime_string_fast|src/asm/runtime_string_fast.x|seeds/runtime_string_fast_surface.from_x.c||"
  # runtime_net_io_batch_fast R2 thin+rest (wave550)：.x 8 public API (3 weak io_* defaults +
  #   3 net_stream_*_batch_c + 2 net_udp_*_many_buf_c) + 2 _impl 桥；rest 含 Linux
  #   recvmmsg/sendmmsg syscall；doc_anchor ast_runtime_net_io_batch_fast_x_doc_anchor（触发 ast_）；
  #   net_/io_ 前缀不触发 ast_（仅 doc_anchor 触发）；prove 锁 thin surface IDENTICAL
  "runtime_net_io_batch_fast|src/asm/runtime_net_io_batch_fast.x|seeds/runtime_net_io_batch_fast_surface.from_x.c||"
  # runtime_env_os R2 thin+rest (wave550)：.x 10 public API (1 DIRECT env_build_key + 9 thin+rest
  #   forwards) + 9 _impl 桥；rest 含 POSIX getenv/setenv/unsetenv/environ + Windows
  #   GetEnvironmentVariableA/_putenv；doc_anchor runtime_env_os_x_doc_anchor（无 ast_）；
  #   env_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL
  "runtime_env_os|src/asm/runtime_env_os.x|seeds/runtime_env_os_surface.from_x.c||"
  # runtime_http_glue R2 mixed (wave551)：.x 12 public API (11 thin+rest forwards + 1 DIRECT
  #   http_method_has_body) + 11 _impl 桥；rest 含 POSIX socket + Win32 winsock + TLS bridge；
  #   doc_anchor runtime_http_glue_x_doc_anchor（无 ast_）；http_/xlang_http_ 前缀不触发 ast_；
  #   .x 在 asm/http/ 子目录；prove 锁 thin surface IDENTICAL (12 #[no_mangle] + 1 doc_anchor)
  "runtime_http_glue|src/asm/http/runtime_http_glue.x|seeds/runtime_http_glue_surface.from_x.c||"
  # runtime_queue_contention R2 mixed (wave551)：.x 13 public API (5 thin+rest queue_os_*_c + 8 DIRECT
  #   queue_smoke_*/worker/trampoline/smoke_c) + 5 _impl 桥；rest 含 POSIX pthread_mutex_t +
  #   pthread_create / Windows CRITICAL_SECTION + _beginthreadex；QueueSmokeState struct 5 fields；
  #   doc_anchor runtime_queue_contention_x_doc_anchor（无 ast_）；queue_ 前缀不触发 ast_；
  #   prove 锁 thin surface IDENTICAL (13 #[no_mangle] + 1 doc_anchor)
  "runtime_queue_contention|src/asm/runtime_queue_contention.x|seeds/runtime_queue_contention_surface.from_x.c||"
  # runtime_backtrace_platform R2 thin+rest (wave552)：.x 15 public API (14 backtrace_*_c forwards +
  #   1 name_has_gold_anchor DIRECT forward) + 13 _impl 桥；rest 含 execinfo/dladdr/DbgHelp/
  #   CaptureStackBackTrace；doc_anchor runtime_backtrace_platform_x_doc_anchor（无 ast_）；
  #   backtrace_/xlang_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL (15 #[no_mangle] + 1 doc_anchor)
  "runtime_backtrace_platform|src/asm/runtime_backtrace_platform.x|seeds/runtime_backtrace_platform_surface.from_x.c||"
  # runtime_sync_os R2 thin+rest (wave552)：.x 16 public API (5 sync_mutex_*_c + 6 sync_rwlock_*_c +
  #   5 sync_condvar_*_c) + 16 _impl 桥；rest 含 pthread_mutex_t/pthread_rwlock_t/pthread_cond_t
  #   (POSIX) + CRITICAL_SECTION/SRWLOCK/CONDITION_VARIABLE (Windows)；doc_anchor
  #   runtime_sync_os_x_doc_anchor（无 ast_）；sync_ 前缀不触发 ast_；
  #   prove 锁 thin surface IDENTICAL (16 #[no_mangle] + 1 doc_anchor)
  "runtime_sync_os|src/asm/runtime_sync_os.x|seeds/runtime_sync_os_surface.from_x.c||"
  # runtime_channel_glue R2 thin+rest (wave553)：.x 17 public API (8 channel_sync_*/lock/unlock/
  #   signal/broadcast + 4 channel_wait_*/timedwait_* + 1 channel_unbounded_grow + 4 channel_select_*)
  #   + 17 _impl 桥；rest 含 pthread_mutex_t/pthread_cond_t (POSIX) + CRITICAL_SECTION/
  #   CONDITION_VARIABLE (Windows)；doc_anchor runtime_channel_glue_x_doc_anchor（无 ast_）；
  #   channel_ 前缀不触发 ast_；prove 锁 thin surface IDENTICAL (17 #[no_mangle] + 1 doc_anchor)
  "runtime_channel_glue|src/asm/runtime_channel_glue.x|seeds/runtime_channel_glue_surface.from_x.c||"
  # runtime_log_os R2 mixed (wave553)：.x 16 public API (7 thin+rest log_apply_env_once/do_rotate/
  #   write_file_sync/write_sync/async_enqueue/emit_bytes/write_fd + 9 mixed _c bridges:
  #   log_apply_env_once_c/get_min_level_c + 7 _c thin+rest forwards) + 14 _impl 桥；
  #   rest 含 _write (Windows)/write (POSIX) + C static state；doc_anchor runtime_log_os_x_doc_anchor
  #   （无 ast_）；log_ 前缀不触发 ast_；log_emit_bytes_c 用 `null or` 语法被 xlang_asm 静默丢弃
  #   （编译器 bug，待修）；prove 锁 mixed surface IDENTICAL (16 #[no_mangle] + 1 doc_anchor)
  "runtime_log_os|src/asm/runtime_log_os.x|seeds/runtime_log_os_surface.from_x.c||"
  # runtime_scheduler_glue R2 mixed (wave554)：.x 17 public API (10 thin+rest xlang_async_*/coop_*
  #   + 7 DIRECT: xlang_async_q_occupancy pure compute + 6 env gate using link_abi_getenv) +
  #   11 _impl 桥 + link_abi_getenv (env bridge)；rest 含 worker/coop frame OS logic；
  #   env_parse_u32_default export 无 #[no_mangle]，surface 用 static helper 匹配 .x linkage；
  #   doc_anchor runtime_scheduler_glue_x_doc_anchor（无 ast_）；xlang_ 前缀不触发 ast_；
  #   prove 锁 mixed surface IDENTICAL (17 #[no_mangle] + 1 doc_anchor)
  "runtime_scheduler_glue|src/asm/runtime_scheduler_glue.x|seeds/runtime_scheduler_glue_surface.from_x.c||"
  # runtime_process_os_glue R2 thin+rest (wave554)：.x 22 public API (process_getenv/setenv/
  #   unsetenv/getpid/getppid/getcwd/getcwd_ptr/getcwd_cached_len/chdir/self_exe_path/
  #   self_exe_path_ptr/self_exe_path_cached_len/nop_sigchld/spawn/exec/waitpid/spawn_simple/
  #   exec_simple/dup_stdio_posix/spawn_io/pipe _c) + 22 _impl 桥；rest 含 POSIX getpid/getcwd/
  #   chdir/execve/waitpid/pipe + Windows _wpgmptr/GetModuleFileName/CreateProcess；
  #   doc_anchor runtime_process_os_glue_x_doc_anchor（无 ast_）；process_ 前缀不触发 ast_；
  #   prove 锁 thin surface IDENTICAL (22 #[no_mangle] + 1 doc_anchor)
  "runtime_process_os_glue|src/asm/runtime_process_os_glue.x|seeds/runtime_process_os_glue_surface.from_x.c||"
  # asm_backend_compat_stubs R2 DIRECT (wave555)：.x 3 public API (xlang_format_u32_to_buf pure compute +
  #   xlang_elf_ctx_append_u32_le + xlang_arm64_mov_imm32_to_w0_c via pipeline_elf_ctx_append_bytes extern bridge);
  #   seed 全守卫 #ifndef XLANG_ASM_BACKEND_COMPAT_STUBS_FROM_X;
  #   doc_anchor asm_backend_compat_stubs_x_doc_anchor（无 ast_）；xlang_ 前缀不触发 ast_；
  #   prove 锁 DIRECT surface IDENTICAL (3 #[no_mangle] + 1 doc_anchor)
  "asm_backend_compat_stubs|src/asm/asm_backend_compat_stubs.x|seeds/asm_backend_compat_stubs_surface.from_x.c||"
  # runtime_thread_glue R2 thin+rest (wave555)：.x 24 public API (16 thin+rest forwards to _impl:
  #   2 xlang_cpu_ star + 14 thread_ star + 8 DIRECT std_thread_ star forwards to thread_ star _c);
  #   rest 含 16 _impl OS bridges (pthread_ star / CreateThread / SetThreadAffinityMask / qos_class);
  #   doc_anchor runtime_thread_glue_x_doc_anchor（无 ast_）；thread_/std_thread_/xlang_ 前缀不触发 ast_；
  #   prove 锁 thin surface IDENTICAL (24 #[no_mangle] + 1 doc_anchor)
  "runtime_thread_glue|src/asm/runtime_thread_glue.x|seeds/runtime_thread_glue_surface.from_x.c||"
  # bootstrap_nostdlib_stubs R2 mixed (wave556)：.x 6 #[no_mangle] public API
  #   (5 thin+rest forwards to _impl: heap_grow/syscall3/syscall4/format_double/vfprintf_fd
  #    + 1 DIRECT pure compute: align16);
  #   rest 含 5 _impl bridges (bump heap mmap / Linux x86_64 syscall / vsnprintf+write);
  #   doc_anchor bootstrap_nostdlib_stubs_x_doc_anchor（无 ast_）；bootstrap_ 前缀不触发 ast_；
  #   prove 锁 mixed surface IDENTICAL (6 #[no_mangle] + 1 doc_anchor)
  "bootstrap_nostdlib_stubs|src/asm/bootstrap_nostdlib_stubs.x|seeds/bootstrap_nostdlib_stubs_surface.from_x.c||"
  # backend_seed_mega_fallback R2 DIRECT (wave556)：.x 2 #[no_mangle] public API
  #   (pipeline_seed_mega_ctx_reset + pipeline_dep_ctx_target_arch_local)
  #   + 3 non-no_mangle helpers (mega_load_i32_le + mega_store_i32_le + mega_store_ptr_le);
  #   seed 全守卫 #ifndef XLANG_BACKEND_SEED_MEGA_FALLBACK_FROM_X;
  #   doc_anchor backend_seed_mega_fallback_x_doc_anchor（无 ast_）；mega_/pipeline_ 前缀不触发 ast_；
  #   prove 锁 DIRECT surface IDENTICAL (2 #[no_mangle] + 3 helper + 1 doc_anchor)
  "backend_seed_mega_fallback|src/asm/backend_seed_mega_fallback.x|seeds/backend_seed_mega_fallback_surface.from_x.c||"
  # parser_asm_parse_expr_link R2 thin+rest (wave557)：.x 1 #[no_mangle] public API
  #   (parser_asm_parse_expr_debug_enabled thin forward to link_abi_getenv extern bridge);
  #   rest 含 link_abi_getenv _impl (host getenv);
  #   prove 锁 thin+rest surface IDENTICAL (1 #[no_mangle] + 1 doc_anchor)
  "parser_asm_parse_expr_link|src/asm/parser_asm_parse_expr_link.x|seeds/parser_asm_parse_expr_link_surface.from_x.c||"
  # lsp_diag_stubs_no_c R2 DIRECT (wave557)：.x 4 #[no_mangle] public API
  #   (lsp_diag_copy_text_impl + json_escape_str_impl + lsp_diag_copy_text + json_escape_str);
  #   lsp_diag_copy_text/json_escape_str forward to _impl (same module #[no_mangle]);
  #   prove 锁 DIRECT surface IDENTICAL (4 #[no_mangle] + 1 doc_anchor)
  "lsp_diag_stubs_no_c|src/lsp/lsp_diag_stubs_no_c.x|seeds/lsp_diag_stubs_no_c_surface.from_x.c||"
  # build_runtime R2 thin+rest (wave558)：.x 5 #[no_mangle] public API
  #   (5 thin forwards to _impl: build_runtime_info/warn + build_patch_pipeline_gen_c/driver_gen_c + build_run_legacy_steps);
  #   rest 含 5 _impl bridges;
  #   prove 锁 thin+rest surface IDENTICAL (5 #[no_mangle] + 1 doc_anchor)
  "build_runtime|src/build_runtime.x|seeds/build_runtime_surface.from_x.c||"
  # user_asm_seed_bridge R2 mixed (wave558)：.x 7 #[no_mangle] public API
  #   (4 thin+rest forwards to _impl: seed_elf_ctx_set_macho_leading_underscore + seed_asm_reject_empty_elf_text
  #    + seed_platform_macho_write_macho_o_to_buf + seed_platform_coff_write_coff_o_to_buf
  #    + 2 DIRECT env gates: seed_asm_debug_enabled + seed_asm_emit_trace_enabled via link_abi_getenv
  #    + 1 DIRECT pure compute: seed_elf_ctx_code_len);
  #   rest 含 4 _impl bridges + link_abi_getenv _impl;
  #   prove 锁 mixed surface IDENTICAL (7 #[no_mangle] + 1 doc_anchor)
  "user_asm_seed_bridge|src/asm/user_asm_seed_bridge.x|seeds/user_asm_seed_bridge_surface.from_x.c||"
  # runtime_heap_user R2 DIRECT (wave559)：.x 7 #[no_mangle] public API
  #   (heap_alloc_c + heap_free_c + heap_realloc_c + heap_alloc_zeroed_c
  #    + heap_arena_init_c + heap_arena64_alloc_c + heap_arena64_deinit_c);
  #   DIRECT via extern bridges: malloc/free/realloc/calloc/heap_alloc_aligned_c;
  #   prove 锁 DIRECT surface IDENTICAL (7 #[no_mangle] + 1 doc_anchor)
  "runtime_heap_user|src/runtime_heap_user.x|seeds/runtime_heap_user_surface.from_x.c||"
  # target_cpu_flags R2 DIRECT (wave559)：.x 5 #[no_mangle] public API
  #   (driver_set/get_pending_target_cpu_features + tcp_tolower + tcp_eq5 + tcp_eq6);
  #   pure compute + static BSS, no extern bridges;
  #   prove 锁 DIRECT surface IDENTICAL (5 #[no_mangle] · no doc_anchor)
  "target_cpu_flags|src/driver/target_cpu_flags.x|seeds/target_cpu_flags_surface.from_x.c||"
  # parser_asm_thin_c R2 mixed (wave560)：.x 11 #[no_mangle] public API
  #   (10 thin+rest forwards to _impl: copy_token_bytes_to_buf64 + extern_parse_set_fail_c
  #    + skip_trait_impl_block_raw_c + skip_one_top_level_let/const_into_slice_c
  #    + cfg_skip_pending_top_level_into_slice_c + try_skip_const_import_stmt
  #    + collect_imports_consume_path + write_try_skip_allow_result + lex_from_lr_next_c
  #    + 1 DIRECT pure compute: is_fn_sig_scalar_type_token_c);
  #   rest 含 10 _impl bridges;
  #   prove 锁 mixed surface IDENTICAL (11 #[no_mangle] + 1 doc_anchor)
  "parser_asm_thin_c|src/asm/parser_asm_thin_c.x|seeds/parser_asm_thin_c_surface.from_x.c||"
  # runtime_driver_strict_glue_stubs R2 mixed (wave560)：.x 12 #[no_mangle] public API
  #   (3 thin+rest forwards to driver_*: asm_driver_skip_codegen_dep_0_get
  #    + asm_driver_set_current_dep_path_for_codegen + typeck_driver_diagnostic_pipe_marker
  #    + 8 DIRECT via typeck_*_slot extern bridges: typeck_i32_ptr_store/read
  #    + typeck_layout_metrics_init_slot/init_depth/al_read_depth/sz_read_depth
  #    + typeck_call_resolve_dep_idx_peek + typeck_call_resolve_func_idx_peek
  #    + 1 thin+rest forward to append_text_to_codegen_buf_impl);
  #   rest 含 10 extern bridges;
  #   prove 锁 mixed surface IDENTICAL (12 #[no_mangle] · no doc_anchor)
  "runtime_driver_strict_glue_stubs|src/runtime_driver_strict_glue_stubs.x|seeds/runtime_driver_strict_glue_stubs_surface.from_x.c||"
  # rt_dispatch_thin R2 thin+rest (wave561)：.x 4 #[no_mangle] public API
  #   (4 thin forwards to _impl: driver_run_asm_backend_c + driver_run_emit_c_path_c
  #    + driver_run_compiler_full + driver_try_compile_via_shu_c_sibling);
  #   rest 含 4 _impl bridges;
  #   prove 锁 thin+rest surface IDENTICAL (4 #[no_mangle] · no doc_anchor)
  "rt_dispatch_thin|src/runtime/rt_dispatch_thin.x|seeds/rt_dispatch_thin_surface.from_x.c||"
  # lsp_diag_pipeline_ctx R2 thin+rest (wave561)：.x 14 #[no_mangle] public API
  #   (14 thin forwards to extern bridges: lsp_diag_x_alloc_dep_ctx_size
  #    + lsp_build_diagnostics_response + lsp_diag_hover_at + lsp_diag_references_at
  #    + lsp_hover_at + lsp_references_at + lsp_diag_definition_at
  #    + lsp_build_semantic_tokens_response + lsp_io_lsp_diag_invalidate_cache
  #    + lsp_diag_pipeline_ctx_fill_paths + typeck_lsp_main + lsp_write_all
  #    + lsp_debug_report_sqpoll_env + lsp_apply_default_io_policy);
  #   rest 含 12 extern bridges (typeck_lsp_* shared by 2 wrappers each);
  #   prove 锁 thin+rest surface IDENTICAL (14 #[no_mangle] · no doc_anchor)
  "lsp_diag_pipeline_ctx|src/lsp/lsp_diag_pipeline_ctx.x|seeds/lsp_diag_pipeline_ctx_surface.from_x.c||"
  # x_seed_bridge R2 mixed (wave562)：.x 14 #[no_mangle] public API
  #   (5 thin+rest forwards: typeck_preprocess_x_buf + std_heap_alloc_zeroed/zero/free/alloc
  #    + 9 DIRECT: 8 io_* stubs + 1 forward chain io_register_buffers_buf_i32/xlang_io_register);
  #   rest 含 4 extern bridges (preprocess_x_buf + typeck_std_heap_alloc + calloc + free);
  #   prove 锁 mixed surface IDENTICAL (14 #[no_mangle] · no doc_anchor)
  "x_seed_bridge|src/x_seed_bridge.x|seeds/x_seed_bridge_surface.from_x.c||"
  # seed_link_compat R2 mixed (wave562)：.x 19 #[no_mangle] public API
  #   (11 thin+rest forwards: typeck_lsp_alloc/free/is_null/main_impl + typeck_std_heap_alloc/alloc_zeroed/free
  #    + std_sys_read_file_into + std_heap_free_u8_ptr + ast_pipeline_module_struct_layout_set_packed
  #    + backend_asm_ctx_slot_offset
  #    + 5 DIRECT stubs returning -1: lsp_diag_lsp_build_diagnostics/semantic_tokens + lsp_diag_hover/references/definition_at
  #    + 3 DIRECT compute: xlang_expr_is_func_param_at + xlang_expr_is_param0_field_access + xlang_module_func_index_by_name);
  #   rest 含 20 extern bridges;
  #   prove 锁 mixed surface IDENTICAL (19 #[no_mangle] · no doc_anchor)
  "seed_link_compat|src/seed_link_compat.x|seeds/seed_link_compat_surface.from_x.c||"
  # simd_loop_thin R2 mixed (wave563)：.x 22 #[no_mangle] public API
  #   (5 DIRECT compute: glue_f32_slot_rbp_disp32 + glue_soa_f32_col_rbp_disp32
  #    + glue_simd_loop_pick_lanes_c + glue_var_array_i32_size_c + glue_var_is_array_i32_n_c
  #    + 17 thin+rest forwards to _impl);
  #   rest 含 22 extern bridges (5 pipeline_* + 17 *_impl);
  #   prove 锁 mixed surface IDENTICAL (22 #[no_mangle] · no doc_anchor)
  "simd_loop_thin|src/asm/simd_loop_thin.x|seeds/simd_loop_thin_surface.from_x.c||"
  # runtime_math_libm R2 mixed (wave564)：.x 34 #[no_mangle] public API
  #   (2 DIRECT compute: math_signum_c + math_special_near
  #    + 32 thin+rest forwards to math_*_impl);
  #   rest 含 32 extern bridges (math_*_impl);
  #   prove 锁 mixed surface IDENTICAL (34 #[no_mangle] · no doc_anchor)
  "runtime_math_libm|src/asm/runtime_math_libm.x|seeds/runtime_math_libm_surface.from_x.c||"
  # fmt_check_cmd R2 mixed (wave565)：.x 25 #[no_mangle] public API
  #   (DIRECT compute + thin+rest forwards to _impl);
  #   rest 含 30 extern bridges (driver_/path_/fmt_/file_/check_/walk_/collect_/parse_);
  #   prove 锁 mixed surface IDENTICAL (25 #[no_mangle] · no doc_anchor)
  "fmt_check_cmd|src/driver/fmt_check_cmd.x|seeds/fmt_check_cmd_surface.from_x.c||"
  # runtime_lsp_glue R2 mixed (wave566)：.x 54 nm T symbols (46 #[no_mangle] + 8 non-mangle global)
  #   (37 DIRECT compute + 17 thin+rest forwards to _impl);
  #   rest 含 23 extern bridges (17 *_impl + 6 lsp_entry_*/lsp_json_key_*);
  #   prove 锁 mixed surface IDENTICAL (54 nm T · has doc_anchor runtime_lsp_glue_x_doc_anchor)
  "runtime_lsp_glue|src/asm/runtime_lsp_glue.x|seeds/runtime_lsp_glue_surface.from_x.c||"
  # backend_try_inline_dispatch_thin R2 mixed (wave566)：.x 50 nm T symbols
  #   (8 DIRECT compute + 42 thin+rest forwards to _impl);
  #   rest 含 42 extern bridges (37 *_impl + 5 pipeline_/asm_ctx_/backend_);
  #   prove 锁 mixed surface IDENTICAL (50 nm T · no doc_anchor)
  "backend_try_inline_dispatch_thin|src/asm/backend_try_inline_dispatch_thin.x|seeds/backend_try_inline_dispatch_thin_surface.from_x.c||"
  # backend_call_dispatch_thin R2 mixed (wave567)：.x 44 nm T symbols
  #   (6 DIRECT compute + 1 thin forward + 37 thin+rest forwards to _impl);
  #   rest 含 40 extern bridges (36 *_impl + 4 pipeline_);
  #   prove 锁 mixed surface IDENTICAL (44 nm T · no doc_anchor)
  "backend_call_dispatch_thin|src/asm/backend_call_dispatch_thin.x|seeds/backend_call_dispatch_thin_surface.from_x.c||"
  # backend_arch_emit_dispatch_thin R2 mixed (wave567)：.x 47 nm T symbols
  #   (43 pure dispatch by ta + 4 dispatch with DIRECT return 0 fallback);
  #   rest 含 135 extern bridges (45 arch_arm64_* + 45 arch_riscv64_* + 45 arch_x86_64_*);
  #   prove 锁 mixed surface IDENTICAL (47 nm T · no doc_anchor)
  "backend_arch_emit_dispatch_thin|src/asm/backend_arch_emit_dispatch_thin.x|seeds/backend_arch_emit_dispatch_thin_surface.from_x.c||"
  # runtime_driver_strict_glue_thin R2 mixed (wave568)：.x 11 nm T symbols
  #   (8 DIRECT compute + 3 thin+rest forwards to driver_*);
  #   rest 含 9 extern bridges (3 driver_* + 6 typeck_*_slot/slot_depth);
  #   prove 锁 mixed surface IDENTICAL (11 nm T · no doc_anchor)
  "runtime_driver_strict_glue_thin|src/runtime_driver_strict_glue_thin.x|seeds/runtime_driver_strict_glue_thin_surface.from_x.c||"
  # simd_enc_thin R2 mixed (wave568)：.x 74 nm T symbols
  #   (3 DIRECT compute + 71 thin+rest forwards to _impl);
  #   rest 含 71 extern bridges (*_impl);
  #   prove 锁 mixed surface IDENTICAL (74 nm T · no doc_anchor)
  "simd_enc_thin|src/asm/simd_enc_thin.x|seeds/simd_enc_thin_surface.from_x.c||"
  # diag_thin R2 mixed (wave569)：.x 78 nm T symbols
  #   (19 DIRECT compute + 59 thin+rest forwards to _impl);
  #   rest 含 53 extern bridges (*_impl);
  #   prove 锁 mixed surface IDENTICAL (78 nm T · no doc_anchor)
  #   注：diag_thin.x ≠ diag.x（diag.x 有 Cap residual 已排除，diag_thin.x 的 -E 成功）
  "diag_thin|src/diag_thin.x|seeds/diag_thin_surface.from_x.c||"
  # runtime_driver_abi R2 mixed (wave569)：.x 61 nm T symbols
  #   (54 DIRECT compute + 7 thin+rest forwards to _impl);
  #   rest 含 39 extern bridges (driver_*_flag_slot + getenv + *_impl);
  #   prove 锁 mixed surface IDENTICAL (61 nm T · no doc_anchor)
  #   注：full 变体，thin 已注册为 driver_abi 模块
  "runtime_driver_abi|src/runtime_driver_abi.x|seeds/runtime_driver_abi_surface.from_x.c||"
  # backend_x86_64_enc_c R2 mixed (wave570)：.x 104 nm T symbols
  #   (104 DIRECT compute · 0 thin+rest);
  #   rest 含 9 extern bridges (pipeline_elf_ctx_*);
  #   prove 锁 mixed surface IDENTICAL (104 nm T · has doc_anchor backend_x86_64_enc_c_x_doc_anchor)
  "backend_x86_64_enc_c|src/asm/backend_x86_64_enc_c.x|seeds/backend_x86_64_enc_c_surface.from_x.c||"
  # diag R2 mixed (wave571)：.x 42 nm T symbols
  #   (35 DIRECT compute + 7 thin+rest forwards to diag_ctx_*/diag_code_table_*/diag_entry_*/link_abi_getenv);
  #   rest 含 39 extern bridges (diag_io_* + diag_ctx_* + diag_code_table_* + diag_entry_* + link_abi_getenv);
  #   prove 锁 mixed surface IDENTICAL (42 nm T · no doc_anchor)
  #   注：wave571 修复 diag_io_fputc 参数顺序 bug (c,o)→(o,c)，-E + cc -c 全绿，L2 真测通过
  "diag|src/diag.x|seeds/diag_surface.from_x.c||"
  # runtime R2 mixed (wave572)：.x 99 nm T symbols
  #   (30 DIRECT compute + 69 thin+rest forwards to _impl;
  #    9.7.6 residual retired mega esc_gate wrappers → rt_stack authority;
  #    9.7.6 residual 2 retired mega smoke_lex_dump / c_typeck_entry_* →
  #    pipeline_typeck_entry_module authority;
  #    9.7.6 residual 3 retired mega c_frontend_smoke / check_only_c_typeck →
  #    pipeline_typeck_entry_module authority;
  #    9.7.6 residual 4 retired rt_run_* leftover !XLANG_NO_C_FRONTEND
  #    consume sites → driver_asm_try_c_* + pipeline_typeck_entry_module;
  #    9.7.6 residual 5 retired rt_run_compiler_parsed leftover generic
  #    lexer/parse + import-downgrade !XLANG_NO_C_FRONTEND blocks →
  #    rt_cp_step_try_c / driver_parsed_try_c_after_pp always -2;
  #    9.7.6 residual 6 retired rt_dispatch_impl leftover
  #    !XLANG_NO_C_FRONTEND driver_try_compile_via_shu_c_sibling consume
  #    site → driver_dispatch_run_compiler_parsed (spawn body stays in
  #    rt_dispatch_thin; HAS a real fork/exec body, different class);
  #    9.7.6 residual 7 retired rt_run_x_emit leftover
  #    !XLANG_NO_C_FRONTEND -E-extern cparser consume site →
  #    driver_x_emit_try_extern_via_cparser always BLD001;
  #    9.7.6 residual 8 retired mega via_cparser wrapper → never-defined
  #    _impl (T 101→100); product -E-extern still try_extern BLD001;
  #    9.7.6 residual 9 retired mega sibling wrapper → never-defined
  #    _impl (T 100→99); product sibling still T from rt_dispatch_thin);
  #   rest 含 84 extern bridges (*_impl) + 7 helper externs (link_abi_getenv + diag_json_enabled + ...);
  #   prove 锁 mixed surface IDENTICAL (99 nm T · no doc_anchor)
  "runtime|src/runtime.x|seeds/runtime_surface.from_x.c||"
  # runtime_link_abi R2 mixed (wave573)：.x 145 nm T symbols
  #   (75 DIRECT compute + 70 thin+rest forwards to _impl);
  #   rest 含 91 extern bridges (*_impl) + 7 helper externs;
  #   prove 锁 mixed surface IDENTICAL (145 nm T · no doc_anchor)
  "runtime_link_abi|src/runtime_link_abi.x|seeds/runtime_link_abi_surface.from_x.c||"
  # backend_enc_dispatch_thin R2 thin full (wave574)：.x 133 nm T symbols
  #   (arm64/riscv64/x86_64 enc dispatch + arch_*_enc_* forwards to _impl +
  #    DIRECT compute: arm64_add/sub_sp_imm12/str_x0/load_store_w0/call 等);
  #   rest 含 arch_*_enc_* extern bridges (per-arch enc helpers) + *_impl externs;
  #   prove 锁 thin full surface IDENTICAL (133 nm T · no doc_anchor)
  "backend_enc_dispatch_thin|src/asm/backend_enc_dispatch_thin.x|seeds/backend_enc_dispatch_thin_surface.from_x.c||"
  # runtime_pipeline_abi R2 full (wave575 lock; 2026-09-09 surface regen)：.x 2044 nm T
  #   (DIRECT compute: pipeline import/load/sync/parse/typeck orch + module import storage +
  #    debug_trace + diag_emitted + dep_seeded + ndep + cfg_eval complex ops);
  #   rest 含 extern bridges (parser_*/asm_*/pipeline_*/typeck_*/cfg_eval_*/driver_*/xlang_*);
  #   Ubuntu xlang_asm -E 给非 #[no_mangle] 的 pipe_* export function 加 pipeline_ 前缀；
  #   Darwin 同前缀。sym_rename 在 .x-E 上将 pipeline_pipe_* → pipe_* 匹配 surface
  #   prove 锁 full surface IDENTICAL (2044 nm T · no doc_anchor)
  "runtime_pipeline_abi|src/runtime_pipeline_abi.x|seeds/runtime_pipeline_abi_surface.from_x.c|pipeline_pipe_append_suffix:pipe_append_suffix,pipeline_pipe_cstr_contains:pipe_cstr_contains,pipeline_pipe_cstr_copy:pipe_cstr_copy,pipeline_pipe_cstr_eq:pipe_cstr_eq,pipeline_pipe_cstr_has_char:pipe_cstr_has_char,pipeline_pipe_cstr_join_slash:pipe_cstr_join_slash,pipeline_pipe_cstr_len:pipe_cstr_len,pipeline_pipe_dir_tail:pipe_dir_tail,pipeline_pipe_imp_ensure_entries:pipe_imp_ensure_entries,pipeline_pipe_imp_ensure_select:pipe_imp_ensure_select,pipeline_pipe_imp_entry_at:pipe_imp_entry_at,pipeline_pipe_imp_entry_off:pipe_imp_entry_off,pipeline_pipe_imp_entry_size:pipe_imp_entry_size,pipeline_pipe_imp_find_or_create:pipe_imp_find_or_create,pipeline_pipe_imp_find_slot:pipe_imp_find_slot,pipeline_pipe_imp_get_header_n:pipe_imp_get_header_n,pipeline_pipe_imp_off_num_imports:pipe_imp_off_num_imports,pipeline_pipe_imp_set_header_n:pipe_imp_set_header_n,pipeline_pipe_imp_soft_sync:pipe_imp_soft_sync,pipeline_pipe_load_i32_le:pipe_load_i32_le,pipeline_pipe_load_ptr_slot:pipe_load_ptr_slot,pipeline_pipe_path_readable:pipe_path_readable,pipeline_pipe_pctx_off_entry_dir_buf:pipe_pctx_off_entry_dir_buf,pipeline_pipe_pctx_off_entry_dir_len:pipe_pctx_off_entry_dir_len,pipeline_pipe_pctx_off_loaded_len:pipe_pctx_off_loaded_len,pipeline_pipe_pctx_off_num_lib_roots:pipe_pctx_off_num_lib_roots,pipeline_pipe_pctx_off_preprocess_len:pipe_pctx_off_preprocess_len,pipeline_pipe_store_i32_le:pipe_store_i32_le,pipeline_pipe_store_i64_zero:pipe_store_i64_zero,pipeline_pipe_store_ptr_slot:pipe_store_ptr_slot,pipeline_pipe_strip_prefix_seg:pipe_strip_prefix_seg,pipeline_pipe_write_nested_name_x:pipe_write_nested_name_x,pipeline_pipe_write_root_dotted_imp:pipe_write_root_dotted_imp|"
  # fmt_check R2 thin + Cap residual pure 深迁（含 append_repo + missing_diag +
  #  collect_mode/user_passed_L BSS + init + file_list/ignore/lib_bufs n + ignore path slots +
  #  lib path slots + full try_append + full argv_append + file_list path slots/store/clear +
  #  driver_run_compiler_check full orch + driver_run_fmt full orch + check_one_file body +
  #  path_stat pure + walk_dir_collect pure + path_bss_slot pure）：
  # thin.x 吃满 lit/entry + pure 真体（path_should_ignore / .x 后缀 / lint / file_list_push /
  #  process_child / collect_paths / default_dirs / check_one_file full body / try_append 全 pure /
  #  argv_append 全 pure / parse_ignore 全量 / invoke_compile·dep_clear / set_current_file /
  #  print_collected / cwd_fallback / try_walk / path_resolve_abs / append_repo / missing_diag /
  #  collect_mode / user_passed_L / init / file_list_n / user_ignore_count / lib_bufs_n /
  #  user_ignore_at / lib_buf_at/store / file_list_at/store/clear / run_compiler_check / run_fmt /
  #  path_stat opendir+access / walk_dir_collect opendir+readdir_name+path_stat /
  #  path_bss_slot 2×512 flat BSS）；
  # rest FROM_X 无 pure-dup _impl；hybrid rest T=0（path_bss leaf closed）
  # prove 锁 thin surface IDENTICAL；冷/无 PREFER 仍可走 seeds/fmt_check_cmd.from_x.c 全 C 体
  "fmt_check|src/driver/fmt_check_cmd_thin.x|seeds/fmt_check_cmd_thin_surface.from_x.c||"
  # simd_loop R2 full：.x 吃满 peel/parse/emit 公共业务；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/simd_loop.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "simd_loop|src/asm/simd_loop.x|seeds/simd_loop_surface.from_x.c||"
  # simd_enc R2 full：.x 吃满 pure/insn/try_hw 公共业务（74 公共面 + anchor）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/simd_enc.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "simd_enc|src/asm/simd_enc.x|seeds/simd_enc_surface.from_x.c||"
  # backend_enc_dispatch R2 full：.x 吃满 enc/ta 公共业务；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/backend_enc_dispatch.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "backend_enc_dispatch|src/asm/backend_enc_dispatch.x|seeds/backend_enc_dispatch_surface.from_x.c||"
  # backend_arch_emit_dispatch R2 full：.x 吃满 47 ta 分派壳公共业务；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/backend_arch_emit_dispatch.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "backend_arch_emit_dispatch|src/asm/backend_arch_emit_dispatch.x|seeds/backend_arch_emit_dispatch_surface.from_x.c||"
  # backend_try_inline_dispatch R2 full：.x 吃满 try_inline/glue 公共业务；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/backend_try_inline_dispatch.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "backend_try_inline_dispatch|src/asm/backend_try_inline_dispatch.x|seeds/backend_try_inline_dispatch_surface.from_x.c||"
  # backend_call_dispatch R2 full：.x 吃满 CALL/emit/import 公共业务；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/backend_call_dispatch.from_x.c 全 C 体
  # prove 锁 full surface IDENTICAL；L2 thin seed 仅作 g05 full.x 失败回退
  "backend_call_dispatch|src/asm/backend_call_dispatch.x|seeds/backend_call_dispatch_surface.from_x.c||"
  # rt_dispatch R2 full：.x 吃满 asm/emit 薄门闩 + run_compiler_full + sibling；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：sibling spawn 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_dispatch_thin.from_x.c 全 C 体
  "rt_dispatch|src/runtime/rt_dispatch_thin.x|seeds/rt_dispatch_thin_surface.from_x.c||"
  # rt_dispatch_impl R2 full：.x 吃满 asm/emit/post_parse/full_x/x_emit_from_state 5 公共；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：lib_roots 槽 + Parsed 填表在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_dispatch_impl.from_x.c 全 C 体
  "rt_dispatch_impl|src/runtime/rt_dispatch_impl.x|seeds/rt_dispatch_impl_surface.from_x.c||"
  # rt_asm_stub R2 full：.x 吃满 want_exe + asm_codegen_ast（GAS main→42 循环）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：GAS 行表 + OutBuf append 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_asm_stub.from_x.c 全 C 体
  "rt_asm_stub|src/runtime/rt_asm_stub.x|seeds/rt_asm_stub_surface.from_x.c||"
  # rt_fmt_one L2 thin 公共面：与产品 PREFER_X_O 同源（thin.x + hybrid rest seed）；prove 锁 thin 面 IDENTICAL
  # 产品 hybrid rest 仍见 seeds/rt_fmt_one.from_x.c（read/format/write body）；入 runtime_driver_no_c.o
  # rt_fmt_one R2 full：.x 吃满 driver_fmt_one_file；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL（driver_fmt_one_file + path helpers）；冷/无 PREFER 仍可走 seeds/rt_fmt_one.from_x.c 全 C 体
  "rt_fmt_one|src/runtime/rt_fmt_one.x|seeds/rt_fmt_one_surface.from_x.c||"
  # rt_pipeline_elf_diag R2 full：.x 吃满 runtime_pipeline_elf_ctx_diag_note（字节偏移读表 + diag_report_with_code）；
  # 产品 rest 在 FROM_X 下业务符号 H=0（仅 marker）；prove 锁 full surface IDENTICAL
  # 冷/无 PREFER 仍可走 seeds/rt_pipeline_elf_diag.from_x.c 全 C 体
  "rt_pipeline_elf_diag|src/runtime/rt_pipeline_elf_diag.x|seeds/rt_pipeline_elf_diag_surface.from_x.c||"
  # rt_run_x_emit R2 full：.x 吃满 driver_run_x_emit_c（step 拆分 + work 槽）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual 在 driver_abi（OutBuf/stdout/work 槽）
  # 冷/无 PREFER 仍可走 seeds/rt_run_x_emit.from_x.c 全 C 体
  # 9.7.6 residual 7: leftover !XLANG_NO_C_FRONTEND -E-extern cparser
  # consume site retired; cold seed now also refuses via
  # driver_x_emit_try_extern_via_cparser (always BLD001)
  # 9.7.6 residual 8: mega via_cparser → _impl wrapper retired (T 101→100)
  # 9.7.6 residual 9: mega sibling → _impl wrapper retired (T 100→99);
  # spawn body stays in rt_dispatch_thin (HAS a real fork/exec body)
  "rt_run_x_emit|src/runtime/rt_run_x_emit.x|seeds/rt_run_x_emit_surface.from_x.c||"
  # rt_parse_diag R2 full：.x 吃满 precise parse failure P001；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL（1 公共符号）；冷/无 PREFER 仍可走 seeds/rt_parse_diag.from_x.c 全 C 体
  "rt_parse_diag|src/runtime/rt_parse_diag.x|seeds/rt_parse_diag_surface.from_x.c||"
  # rt_diag_errno R2 full：.x 吃满 code_for_kind + errno{,_path,_path_pair} + cli_usage_note；产品 rest 在 FROM_X 下业务 H=0
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_diag_errno.from_x.c 全 C 体
  "rt_diag_errno|src/runtime/rt_diag_errno.x|seeds/rt_diag_errno_surface.from_x.c||"
  # rt_fs_open R2 full：.x 吃满 path_copy + open_read + open_write；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL（3 公共符号）；冷/无 PREFER 仍可走 seeds/rt_fs_open.from_x.c 全 C 体
  "rt_fs_open|src/runtime/rt_fs_open.x|seeds/rt_fs_open_surface.from_x.c||"
  # rt_arena_buf R2 full：.x 吃满 arena_buf + module_buf；产品 rest 在 FROM_X 下业务 H=0（marker+BSS）
  # Cap-global-bss residual：槽 API 在 driver_abi；prove 锁 full surface IDENTICAL
  # 冷/无 PREFER 仍可走 seeds/rt_arena_buf.from_x.c 全 C 体
  "rt_arena_buf|src/runtime/rt_arena_buf.x|seeds/rt_arena_buf_surface.from_x.c||"
  # rt_preamble R2 full：.x 吃满 write_io_net + write_fs_path_map_error（skip+fputs）；
  # 产品 rest 在 FROM_X 下业务 H=0（marker+巨型字串表数据）；Cap-giant-string residual 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_preamble.from_x.c 全 C 体
  "rt_preamble|src/runtime/rt_preamble.x|seeds/rt_preamble_surface.from_x.c||"
  # rt_stack R2 full：.x 吃满 thread_fn + large_stack；产品 rest 在 FROM_X 下业务符号 H=0（仅 marker）
  # Cap-fn-ptr residual：driver_run_stack_esc_gate_on_large_stack 在 driver_abi（平台层）
  # prove 锁 full surface IDENTICAL（2 公共符号）；冷/无 PREFER 仍可走 seeds/rt_stack.from_x.c 全 C 体
  "rt_stack|src/runtime/rt_stack.x|seeds/rt_stack_surface.from_x.c||"
  # rt_lib_root R2 full：.x 吃满 ptr_usable + default + roots_from_key；产品 rest 在 FROM_X 下业务符号 H=0（仅 marker）
  # prove 锁 full surface IDENTICAL（3 公共符号）；冷/无 PREFER 仍可走 seeds/rt_lib_root.from_x.c 全 C 体
  "rt_lib_root|src/runtime/rt_lib_root.x|seeds/rt_lib_root_surface.from_x.c||"
  # rt_emit_flags R2 full：.x 吃满 has_emit + set_use_lto + set_print_target_cpu；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL（3 公共符号）；冷/无 PREFER 仍可走 seeds/rt_emit_flags.from_x.c 全 C 体
  "rt_emit_flags|src/runtime/rt_emit_flags.x|seeds/rt_emit_flags_surface.from_x.c||"
  # rt_emit_state R2 full：.x 吃满 set_path/set_lib/set_n/set_extern + argv_parse；产品 rest FROM_X 业务 T=0（仅 marker+BSS）
  # Cap-global-bss residual：槽/绑定 API 在 driver_abi；共享 path_buf/lib_roots 数据在 rest seed
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_emit_state.from_x.c 全 C 体
  "rt_emit_state|src/runtime/rt_emit_state.x|seeds/rt_emit_state_surface.from_x.c||"
  # rt_content R2 full：.x 吃满 content_has_* + driver_source_has_* path wrappers；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_content.from_x.c 全 C 体
  "rt_content|src/runtime/rt_content.x|seeds/rt_content_surface.from_x.c||"
  # rt_util R2 full：.x 吃满 unlink + argv0_basename；产品 rest 在 FROM_X 下业务符号 H=0
  # prove 锁 full surface IDENTICAL（2 公共符号）；冷/无 PREFER 仍可走 seeds/rt_util.from_x.c 全 C 体
  "rt_util|src/runtime/rt_util.x|seeds/rt_util_surface.from_x.c||"
  # rt_argv R2 full：.x 吃满 15 公共 drv_eq_* / path_ends_x / target_has_arm；产品 rest 在 FROM_X 下业务 H=0
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_argv.from_x.c 全 C 体
  "rt_argv|src/runtime/rt_argv.x|seeds/rt_argv_surface.from_x.c||"
  # rt_entry R2 full：.x 吃满 explain_cli / smoke_diag / smoke_summary /
  #   fmt_report_no_files / run_compiler_c / build_build_x；产品 rest 在 FROM_X 下业务 H=0
  # Cap residual：driver_stdio_* + driver_entry_*_slot 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_entry.from_x.c 全 C 体
  "rt_entry|src/runtime/rt_entry.x|seeds/rt_entry_surface.from_x.c||"
  # rt_compile R2 full：.x 吃满 deps/asm_dep/apply/init/scan/impl/alloc 等 25 公共；产品 rest 在 FROM_X 下业务 H=0
  # （禁 let **u8 / 局部 u8[N]；malloc 扫描缓冲；strstr/strncmp；diag_report_with_code）
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_compile.from_x.c 全 C 体
  "rt_compile|src/runtime/rt_compile.x|seeds/rt_compile_surface.from_x.c||"
  # rt_run_exec R2 full：.x 吃满 want_asm/print_usage/test_status/print_cpu/scan/path/exec/run_test 8 公共；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：usage_write + compiled_body 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_run_exec.from_x.c 全 C 体
  "rt_run_exec|src/runtime/rt_run_exec.x|seeds/rt_run_exec_surface.from_x.c||"
  # rt_run_asm_backend R2 full：.x 吃满 driver_run_asm_backend（step 拆分 + work 槽）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual 在 driver_abi（FILE/pctx/host/defines/work）
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_run_asm_backend.from_x.c 全 C 体
  "rt_run_asm_backend|src/runtime/rt_run_asm_backend.x|seeds/rt_run_asm_backend_surface.from_x.c||"
  # rt_run_compiler_parsed R2 full：.x 吃满 driver_run_compiler_parsed（step 拆分 + work 槽）；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：Parsed/FILE/invoke_cc/work 在 driver_abi
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/rt_run_compiler_parsed.from_x.c 全 C 体
  "rt_run_compiler_parsed|src/runtime/rt_run_compiler_parsed.x|seeds/rt_run_compiler_parsed_surface.from_x.c||"
  # target_cpu_pure R2 full：.x 吃满 12 公共业务（pending/tolower/eq_at/set_u32/parse_named/resolve/
  #   eq5/eq6/simd_spelling/simd_lanes/append_feat/flags_has_token）+ BSS；
  # 产品 rest 在 FROM_X 下业务 H=0（仅 marker）；Cap residual：xlang_target_cpu_print (FILE/fprintf) +
  #   OS detect (sysctl/proc/#if) 在 mega rest
  # prove 锁 full surface IDENTICAL；冷/无 PREFER 仍可走 seeds/target_cpu_pure.from_x.c 全 C 体
  "target_cpu_pure|src/driver/target_cpu_pure.x|seeds/target_cpu_pure_surface.from_x.c||"
  # async_asm_pool R2 full：.x 吃满 helpers + build_layout；
  # FROM_X rest 业务 H=0（仅 slice_marker）；冷/无 PREFER 仍可走 seeds/async_asm_pool.from_x.c 全 C 体
  # 产品 pipeline_glue 仍 #include 冷 seed（无宏）直至 glue unbundle；prove 锁 full surface IDENTICAL
  "async_asm_pool|src/asm/async_asm_pool.x|seeds/async_asm_pool_surface.from_x.c||"
  # async_liveness R2 pure surface + Cap residual pure：.x 吃满 await walk / live frame / mangle/tag
  #   + lookup/type/size/layout/has_await/needs_cps/analyze/module_struct
  #   + FILE* emit_* typedef/local/codegen_comment（shared driver_preamble_fputs）；
  # FROM_X 省略 pure C 体（slice_marker）；Cap residual fputs：G.7 = driver_preamble_fputs
  # 冷/无 PREFER 仍可走 seeds/async_liveness.from_x.c 全 C 体；prove 锁 pure surface IDENTICAL
  # Stack：analyze_block_linear malloc(4096)；layout temps malloc(4196)（Ubuntu -E 稳）
  "async_liveness|src/async/async_liveness.x|seeds/async_liveness_surface.from_x.c||"
  # async_cps_codegen R2 pure + Cap residual pure wave1–5：
  #   .x 吃满 name gates + thin walk/hoist + expr_is_* + module/sched + void_entry + walk _impl
  #   + FILE* emit end/phase_reset/after_await(_io)/sched_wrapper（shared driver_preamble_fputs）；
  # FROM_X 省略 pure C 体（含 walk _impl + wave4–5 emit；slice_marker）；
  # Cap residual fputs：G.7 = driver_preamble_fputs（no module-local async_cps_fputs）
  # 冷/无 PREFER 仍可走 seeds/async_cps_codegen.from_x.c 全 C 体；prove 锁 pure surface IDENTICAL
  # Thin ABI：(e,target)/(b,target) 与 C 公共面一致
  "async_cps_codegen|src/async/async_cps_codegen.x|seeds/async_cps_codegen_surface.from_x.c||"
)

# 找 xlang 二进制：优先 $XLANG（文档/进度验收），再 xlang_asm / xlang / xlang-c
# 注意：本脚本已 cd 到 compiler/，故 $XLANG=./compiler/xlang_asm 需映射到 $REPO_ROOT
XLANG_BIN=""
if [ -n "${XLANG:-}" ]; then
  _xlang_cand="$XLANG"
  case "$_xlang_cand" in
    /*) ;;
    ./*|../*) _xlang_cand="$REPO_ROOT/${_xlang_cand#./}" ;;
    *)
      if [ -x "$_xlang_cand" ]; then
        :
      elif [ -x "$REPO_ROOT/$_xlang_cand" ]; then
        _xlang_cand="$REPO_ROOT/$_xlang_cand"
      elif [ -x "./$_xlang_cand" ]; then
        _xlang_cand="./$_xlang_cand"
      fi
      ;;
  esac
  if [ -x "$_xlang_cand" ]; then
    XLANG_BIN="$_xlang_cand"
  fi
  unset _xlang_cand
fi
if [ -z "$XLANG_BIN" ]; then
  for bin in ./xlang_asm ./xlang ./xlang-c ./bootstrap_xlangc; do
    if [ -x "$bin" ]; then
      XLANG_BIN="$bin"
      break
    fi
  done
fi
if [ -z "$XLANG_BIN" ]; then
  echo "prove: no xlang_asm/xlang/xlang-c found in compiler/ (set XLANG=...)" >&2
  exit 127
fi
echo "prove: XLANG_BIN=$XLANG_BIN" >&2

CC="${CC:-cc}"
BASE_CFLAGS="-Wall -Wextra -I. -Iinclude -Isrc"
TMP_DIR="${TMPDIR:-/tmp}/xlang_prove_$$"
mkdir -p "$TMP_DIR"

XLANG_LIB_PATHS="-L .. -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/lsp -L src/driver -L src/preprocess"

# 最近一次 gen_x_o 失败原因（供主循环打印；勿 2>/dev/null 吞掉）
GEN_X_O_LAST_ERR=""

# 生成 .x 版 .o（模拟 g05_try_x_to_o 逻辑；prologue 须与 g05 同源）
gen_x_o() {
  local xsrc="$1"
  local xout="$2"
  local sym_rename="$3"

  local tmp="$TMP_DIR/$(basename "$xsrc" .x)_x.c"
  local e_err="$TMP_DIR/$(basename "$xsrc" .x)_E.err"
  GEN_X_O_LAST_ERR=""

  # xlang -E（超时 45s 防死循环）；stderr 落盘。
  # PLATFORM: SHARED harness — Ubuntu x86_64 host xlang -E occasionally SIGSEGV
  # (nondeterministic; also seen on small modules). Retry a few times; IDENTICAL
  # nm gate still hard-fails on real symbol mismatch. Not a product soft-skip.
  # shellcheck disable=SC2086
  local e_try=0 e_ok=0
  while [ "$e_try" -lt 5 ]; do
    e_try=$((e_try + 1))
    rm -f "$tmp" "$e_err"
    if perl -e 'alarm 45; exec @ARGV' "$XLANG_BIN" -E $XLANG_LIB_PATHS "$xsrc" >"$tmp" 2>"$e_err" \
      && [ -s "$tmp" ]; then
      e_ok=1
      break
    fi
    sleep 0.3
  done
  if [ "$e_ok" -ne 1 ]; then
    GEN_X_O_LAST_ERR="xlang -E fail (after ${e_try} tries): $(tr '\n' ' ' <"$e_err" 2>/dev/null | head -c 160)"
    return 1
  fi

  # 过滤 DBG- 调试行
  grep -v '^DBG-' "$tmp" >"${tmp}.clean" && mv "${tmp}.clean" "$tmp"

  # 符号重命名（与 g05 G05_X_O_SYM_RENAME 一致）
  if [ -n "$sym_rename" ]; then
    local old_ifs="$IFS"
    IFS=','
    for pair in $sym_rename; do
      old_name="${pair%%:*}"
      new_name="${pair#*:}"
      if [ -n "$old_name" ] && [ -n "$new_name" ] && [ "$old_name" != "$new_name" ]; then
        perl -i -pe "s/\\b${old_name}\\b/${new_name}/g" "$tmp" || true
      fi
    done
    IFS="$old_ifs"
  fi

  # POSIX prologue + 删 -E 自带 #include 和 libc extern（与 g05_try_x_to_o 一致）
  {
    echo '/* prove prologue (g05_try_x_to_o aligned + uio/poll) */'
    echo '#include <stddef.h>'
    echo '#include <stdint.h>'
    echo '#include <sys/types.h>'
    echo '#include <stdlib.h>'
    echo '#include <string.h>'
    echo '#include <stdio.h>'
    echo '#ifndef _WIN32'
    echo '#include <unistd.h>'
    echo '#include <fcntl.h>'
    echo '#include <errno.h>'
    # PLATFORM: POSIX — -E preamble 内联 xlang_sys_readv/writev/poll；
    # sed 会删 -E 自带 #include，故在此补齐（权威：g05_try_x_to_o）。
    echo '#include <sys/uio.h>'
    echo '#include <poll.h>'
    # PLATFORM: POSIX — fmt_check walk/path_stat pure *u8 wrappers (DIR* cast safe).
    echo '#include <dirent.h>'
    echo 'static inline uint8_t *xlang_fmt_opendir(uint8_t *name) {'
    echo '  return (uint8_t *)opendir((const char *)name);'
    echo '}'
    echo 'static inline int32_t xlang_fmt_closedir(uint8_t *dirp) {'
    echo '  return dirp ? (int32_t)closedir((DIR *)(void *)dirp) : (int32_t)-1;'
    echo '}'
    echo 'static inline int32_t xlang_fmt_access(uint8_t *path, int32_t mode) {'
    echo '  return path ? (int32_t)access((const char *)path, (int)mode) : (int32_t)-1;'
    echo '}'
    echo 'static inline uint8_t *xlang_fmt_readdir_name(uint8_t *dirp) {'
    echo '  struct dirent *ent;'
    echo '  if (!dirp) return (uint8_t *)0;'
    echo '  ent = readdir((DIR *)(void *)dirp);'
    echo '  return ent ? (uint8_t *)ent->d_name : (uint8_t *)0;'
    echo '}'
    echo '#endif'
    sed -e '/^#include /d' \
        -e '/^extern ssize_t read(/d' \
        -e '/^extern ssize_t write(/d' \
        -e '/^extern int32_t open(/d' \
        -e '/^extern int open(/d' \
        -e '/^extern int32_t fcntl(/d' \
        -e '/^extern int fcntl(/d' \
        -e '/^extern int32_t close(/d' \
        -e '/^extern int close(/d' \
        -e '/^extern uint8_t \* calloc(/d' \
        -e '/^extern uint8_t \* malloc(/d' \
        -e '/^extern void free(/d' \
        -e '/^extern uint8_t \* memcpy(/d' \
        -e '/^extern void \* memcpy(/d' \
        -e '/^extern int32_t memcmp(/d' \
        -e '/^extern int memcmp(/d' \
        -e '/^extern char \* getenv(/d' \
        -e '/^extern uint8_t \* getenv(/d' \
        -e '/^extern char \* getcwd(/d' \
        -e '/^extern uint8_t \* getcwd(/d' \
        -e '/^extern int32_t unlink(/d' \
        -e '/^extern int unlink(/d' \
        -e '/^extern size_t strlen(/d' \
        -e '/^extern int32_t strcmp(/d' \
        -e '/^extern int strcmp(/d' \
        -e '/^extern int32_t strncmp(/d' \
        -e '/^extern int strncmp(/d' \
        -e '/^extern uint8_t \* strstr(/d' \
        -e '/^extern char \* strstr(/d' \
        -e '/^extern uint8_t \* memset(/d' \
        -e '/^extern void \* memset(/d' \
        -e '/^extern int32_t setenv(/d' \
        -e '/^extern int setenv(/d' \
        -e '/^extern uint8_t \* strerror(/d' \
        -e '/^extern char \* strerror(/d' \
        -e '/^extern int32_t system(/d' \
        -e '/^extern int system(/d' \
        -e '/^extern int32_t fputs(/d' \
        -e '/^extern int fputs(/d' \
        -e '/^extern uint8_t \* opendir(/d' \
        -e '/^extern void \* opendir(/d' \
        -e '/^extern DIR \* opendir(/d' \
        -e '/^extern int32_t closedir(/d' \
        -e '/^extern int closedir(/d' \
        -e '/^extern int32_t access(/d' \
        -e '/^extern int access(/d' \
        -e '/^extern ptrdiff_t io_read_batch(/d' \
        -e '/^extern ptrdiff_t io_write_batch(/d' \
        -e '/^extern .*io_read_ptr(/d' \
        -e '/^extern .*io_read_ptr_len(/d' \
        -e '/^extern .*io_register_buffer(/d' \
        -e '/^extern .*io_unregister_buffers(/d' \
        -e '/^extern .*io_wait_readable(/d' \
        -e '/^extern .*io_register_buffers_4(/d' \
        -e '/^extern .*io_register_buffers_buf(/d' \
        -e '/^extern .*io_register_buffers_buf_i32(/d' \
        -e '/^#define io_register_buffers_buf(/d' \
        -e '/^#define std_io_driver_io_register_buffers_buf(/d' \
        -e '/^#define std_io_core_xlang_io_register_buffers_buf/d' \
        -e '/^__attribute__((weak)).* io_register_buffers_buf_c(/d' \
        -e '/^__attribute__((weak)).* io_register_buffers_4(/,/^}/d' \
        -e '/^__attribute__((weak)).* io_wait_readable(/,/^}/d' \
        -e '/^__attribute__((weak)).* io_read_batch_buf(/,/^}/d' \
        -e '/^__attribute__((weak)).* io_write_batch_buf(/,/^}/d' \
        -e '/^static inline .*io_register_buffers_buf_i32(/d' \
        -e '/^extern uint8_t \* xlang_fmt_opendir(/d' \
        -e '/^extern int32_t xlang_fmt_closedir(/d' \
        -e '/^extern int32_t xlang_fmt_access(/d' \
        -e '/^extern uint8_t \* xlang_fmt_readdir_name(/d' \
        "$tmp"
  } >"${tmp}.full" && mv "${tmp}.full" "$tmp"

  # cc -c
  if ! $CC $BASE_CFLAGS -x c -c -o "$xout" "$tmp" 2>"${TMP_DIR}/cc_err.txt"; then
    GEN_X_O_LAST_ERR="cc -c fail: $(tr '\n' ' ' <"${TMP_DIR}/cc_err.txt" | head -c 160)"
    return 1
  fi
  return 0
}

# 生成 seed 版 .o
gen_seed_o() {
  local seed="$1"
  local out="$2"
  $CC $BASE_CFLAGS -I. -c -o "$out" "$seed" 2>"${TMP_DIR}/cc_err.txt"
}

# 已定义**强全局**业务符号裸名（去 Mach-O 前导 _），一行一个
#
# PLATFORM: SHARED — IDENTICAL 只比「强定义」API 面：
#   · Linux ELF：nm 类型 T/D/B/R/S/C（排除 U / W weak / V）
#   · macOS Mach-O：nm -m「external」且非 weak（Darwin 上 weak 常显示为 T，
#     若用 plain nm 会把 -E preamble 的 weak 桩算进 x 面 → N 全红假象）
# 忽略：局部 t/d/s、ltmp、l_ 字符串池。preamble 弱桩（args_iter_*/ctx_*/io_*…）
# 不参与退役判据——与 g05 PREFER 入链语义一致（weak 可重叠）。
defined_sym_names() {
  local obj="$1"
  # LC_ALL=C：comm 要求字节序排序；locale sort 在 Ubuntu 会触发 “not in sorted order”
  if nm -m "$obj" >/dev/null 2>&1; then
    # PLATFORM: MACOS — nm -m 可区分 weak external vs external
    nm -m "$obj" 2>/dev/null | awk '
      /undefined/ { next }
      / non-external / { next }
      / weak / { next }
      / external / {
        s = $NF
        if (s ~ /^_/) s = substr(s, 2)
        if (s ~ /^l_/) next
        if (s ~ /^\./) next
        if (s ~ /^L\./) next
        if (s ~ /^ltmp/) next
        print s
      }' | LC_ALL=C sort -u
  else
    # PLATFORM: LINUX — 强定义字母类；W/V = weak，不计入 N
    nm "$obj" 2>/dev/null | awk '
      $2 ~ /^[TDBRSC]$/ {
        s = $3
        if (s ~ /^_/) s = substr(s, 2)
        if (s ~ /^l_/) next
        if (s ~ /^\./) next
        if (s ~ /^L\./) next
        if (s ~ /^ltmp/) next
        print s
      }' | LC_ALL=C sort -u
  fi
}

# nm 比较符号 — IDENTICAL 模式：全局业务符号集合相等（可退役 seed）
compare_symbols() {
  local o1="$1"
  local o2="$2"
  local sym1="$TMP_DIR/sym1.txt"
  local sym2="$TMP_DIR/sym2.txt"
  defined_sym_names "$o1" >"$sym1"
  defined_sym_names "$o2" >"$sym2"
  diff "$sym1" "$sym2"
}

# CORE 模式：x 定义符号（除 allowlist）必须 ⊆ seed；seed 可多 thin/impl/C-tail
# 输出：空=通过；否则列出缺失符号
compare_core_surface() {
  local x_o="$1"
  local seed_o="$2"
  local allow_csv="$3"
  local x_syms="$TMP_DIR/core_x.txt"
  local seed_syms="$TMP_DIR/core_seed.txt"
  local allow_file="$TMP_DIR/core_allow.txt"
  local missing="$TMP_DIR/core_missing.txt"

  defined_sym_names "$x_o" >"$x_syms"
  defined_sym_names "$seed_o" >"$seed_syms"
  : >"$allow_file"
  if [ -n "$allow_csv" ]; then
    local old_ifs="$IFS"
    IFS=','
    for a in $allow_csv; do
      a="${a#_}"
      [ -n "$a" ] && echo "$a" >>"$allow_file"
    done
    IFS="$old_ifs"
    LC_ALL=C sort -u "$allow_file" -o "$allow_file"
  fi

  # x \ seed \ allow
  comm -23 "$x_syms" "$seed_syms" >"${missing}.raw"
  if [ -s "$allow_file" ]; then
    comm -23 "${missing}.raw" "$allow_file" >"$missing"
  else
    mv "${missing}.raw" "$missing"
  fi

  if [ -s "$missing" ]; then
    echo "CORE missing from seed:"
    cat "$missing"
    return 1
  fi
  # 备注：seed 多 / x 仅 allowlist 不 fail
  local seed_only x_only
  seed_only=$(comm -13 "$x_syms" "$seed_syms" | wc -l | tr -d ' ')
  x_only=$(comm -23 "$x_syms" "$seed_syms" | wc -l | tr -d ' ')
  echo "seed+${seed_only} x_allow+${x_only}"
  return 0
}

# 主逻辑
printf "%-18s | %-8s | %-8s | %-10s | %s\n" "模块" "xlang-E" "cc-c" "nm-diff" "备注"
printf "%-18s-+-%-8s-+-%-8s-+-%-10s-+-%s\n" "$(printf '%0.s-' {1..18})" "$(printf '%0.s-' {1..8})" "$(printf '%0.s-' {1..8})" "$(printf '%0.s-' {1..10})" "$(printf '%0.s-' {1..30})"

PASS=0
CORE_PASS=0
FAIL=0
SKIP=0

# 过滤模块（如果传了参数）
SELECTED="${*:-}"
for entry in "${MODULES[@]}"; do
  IFS='|' read -r name xsrc seed sym_rename mode <<< "$entry"

  # 如果传了参数，只验证指定的模块
  if [ -n "$SELECTED" ]; then
    found=0
    for sel in $SELECTED; do
      [ "$sel" = "$name" ] && found=1 && break
    done
    [ "$found" = "0" ] && continue
  fi

  # 检查 .x 和 seed 是否存在
  if [ ! -f "$xsrc" ]; then
    printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "NOSRC" "-" "-" ".x 不存在"
    SKIP=$((SKIP + 1))
    continue
  fi
  seed_path=""
  # Track L：工作区 *_gen.c 已非构建硬依赖；冷启动对照用 seeds/*_gen.linux.x86_64.c
  _seed_base="${seed%.c}"
  for s in "$seed" "seeds/$seed" "seeds/${_seed_base}.linux.x86_64.c" "seeds/${seed}"; do
    if [ -f "$s" ]; then
      seed_path="$s"
      break
    fi
  done
  if [ -z "$seed_path" ]; then
    printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "NOSEED" "-" "-" "seed=$seed 不存在"
    SKIP=$((SKIP + 1))
    continue
  fi

  x_o="$TMP_DIR/${name}_x.o"
  seed_o="$TMP_DIR/${name}_seed.o"

  # 生成 .x 版 .o
  if ! gen_x_o "$xsrc" "$x_o" "$sym_rename"; then
    printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "FAIL" "-" "-" "${GEN_X_O_LAST_ERR:-xlang -E 或 cc -c 失败}"
    FAIL=$((FAIL + 1))
    continue
  fi

  # 生成 seed 版 .o
  if ! gen_seed_o "$seed_path" "$seed_o"; then
    printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "OK" "FAIL" "-" "seed cc -c 失败"
    FAIL=$((FAIL + 1))
    continue
  fi

  # nm 比较
  if [[ "$mode" == core:* ]]; then
    allow_csv="${mode#core:}"
    core_out=$(compare_core_surface "$x_o" "$seed_o" "$allow_csv")
    core_rc=$?
    if [ "$core_rc" -eq 0 ]; then
      printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "OK" "OK" "CORE_OK" "$core_out; hybrid 非退役"
      CORE_PASS=$((CORE_PASS + 1))
    else
      printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "OK" "OK" "CORE_FAIL" "x 公共面缺失于 seed"
      echo "$core_out" | head -8 | sed 's/^/    /'
      FAIL=$((FAIL + 1))
    fi
  else
    diff_out=$(compare_symbols "$x_o" "$seed_o")
    if [ -z "$diff_out" ]; then
      printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "OK" "OK" "IDENTICAL" "可退役 seed"
      PASS=$((PASS + 1))
    else
      diff_lines=$(echo "$diff_out" | wc -l | tr -d ' ')
      printf "%-18s | %-8s | %-8s | %-10s | %s\n" "$name" "OK" "OK" "${diff_lines}行" "符号差异"
      # 显示前 5 行差异
      echo "$diff_out" | head -5 | sed 's/^/    /'
      FAIL=$((FAIL + 1))
    fi
  fi
done

echo ""
echo "=== 自举验证结果 ==="
echo "总计：$((PASS + CORE_PASS + FAIL + SKIP))"
echo "  符号一致（可退役 seed / KPI N）：$PASS"
echo "  核心面 OK（hybrid CORE，不计 N）：$CORE_PASS"
echo "  符号差异 / CORE 失败：$FAIL"
echo "  跳过：$SKIP"
echo ""
echo "IDENTICAL = .x→.o 与 seed→.o 已定义符号完全相同（可退役）"
echo "CORE_OK   = x 公共符号 ⊆ seed（允许 seed 多 thin/C-tail；x 独有列于 core: allowlist）"

# 清理
rm -rf "$TMP_DIR"

# 有 FAIL 则非零退出（CI / 门禁）
if [ "$FAIL" -gt 0 ]; then
  exit 1
fi
exit 0
