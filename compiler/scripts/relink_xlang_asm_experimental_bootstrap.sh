#!/usr/bin/env bash
# experimental bootstrap 重链：pipeline_x.o + X companions + seed C（与 build_xlang_asm.sh 首链一致）。
# pipeline.x newer → rebuild pipeline_x.o (try-gen-x); abi/WPO freshness is
# ensure_experimental_ast_pool_for_wpo (not this script). Deleted ast_pool.c -nt retired.
# 用法：cd compiler && ./scripts/relink_xlang_asm_experimental_bootstrap.sh
#   (companions via migrate/try-heat/driver_leaf — 0-make post phys-del; twin of build_xlang_asm wave931)
# Escape: XLANG_EXPERIMENTAL_BOOTSTRAP_VIA_MAKE=1 + Makefile → historic make leaves.
# PLATFORM: SHARED — product of this script is xlang_asm.experimental only.
# Product xlang_asm is owned by g05 / build_xlang_asm strict / L4.
# Escape: XLANG_EXPERIMENTAL_PROMOTE_TO_PRODUCT=1 copies onto xlang_asm
# (explicit promote; WPO ARTIFACTS_ONLY / ensure_experimental MUST NOT set this).
set -e
cd "$(dirname "$0")/.."
BUILD_DIR="build_asm"
CC=${CC:-cc}
CFLAGS="-Wall -Wextra -I. -Iinclude -Isrc"
SEED_O="$BUILD_DIR/asm_driver_seed"
BSTRICT_DISPATCH="src/asm/backend_enc_dispatch.o src/asm/backend_x86_64_enc_c.o src/asm/backend_arch_emit_dispatch.o src/asm/backend_try_inline_dispatch.o src/asm/backend_call_dispatch.o"
PARSER_EXPR_LINK_O="src/asm/parser_asm_parse_expr_link.o"
PARSER_ASM_PARTIAL="$BUILD_DIR/parser_asm_minimal_partial.o"

experimental_bootstrap_info() {
  printf 'info: relink_experimental_bootstrap: %s\n' "$*" >&2
}

experimental_bootstrap_warn() {
  printf 'warning: relink_experimental_bootstrap: %s\n' "$*" >&2
}

experimental_bootstrap_error() {
  printf 'build error: relink_experimental_bootstrap: %s\n' "$*" >&2
}

# codegen.c 引用 async_liveness / async_cps_codegen（与 Makefile OBJS_CORE、build_xlang_asm 一致）。
ensure_async_cps_seed_objs() {
  local src out src_pair
  for src_pair in \
  "seeds/async_liveness.from_x.c:$SEED_O/async_liveness.o" \
  "seeds/async_cps_codegen.from_x.c:$SEED_O/async_cps_codegen.o"; do
  src="${src_pair%%:*}"
  out="${src_pair##*:}"
  if [ ! -f "$out" ] || [ "$src" -nt "$out" ]; then
  experimental_bootstrap_info "cc $src -> $out"
  mkdir -p "$(dirname "$out")"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$out" "$src"
  fi
  done
}
ensure_async_cps_seed_objs

# bootstrap-driver-seed 同款 C 种子 .o（experimental 链须 parser/typeck 等；缺则 ld 失败）。
ensure_asm_driver_seed_c_objs() {
  mkdir -p "$SEED_O"
  if [ ! -f "$SEED_O/lexer.o" ] || [ "seeds/runtime_lexer_glue.from_x.c" -nt "$SEED_O/lexer.o" ]; then
  experimental_bootstrap_info "cc_inc_tu $SEED_O/lexer.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lexer_glue.from_x.c -o "$SEED_O/lexer.o"
  fi
  if [ ! -f "$SEED_O/ast_seed.o" ] || [ "seeds/runtime_ast_glue.from_x.c" -nt "$SEED_O/ast_seed.o" ]; then
  experimental_bootstrap_info "cc $SEED_O/ast_seed.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_ast_glue.from_x.c -o "$SEED_O/ast_seed.o"
  fi
  # G-02a: typeck.c 已物理删除；typeck.o 由 typeck.x 生成（typeck_x.o），编排桩由 typeck_c_module_stubs.o 提供。
  # G-02a: codegen.c 已物理删除；codegen.o 由 codegen.x 生成（codegen_x.o），编排桩由 codegen_pipeline_stubs.o 提供。
  if [ ! -f "$SEED_O/lsp_diag.o" ] || [ "seeds/runtime_lsp_glue.from_x.c" -nt "$SEED_O/lsp_diag.o" ]; then
  experimental_bootstrap_info "cc $SEED_O/lsp_diag.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lsp_glue.from_x.c -o "$SEED_O/lsp_diag.o"
  fi
  if [ ! -f src/lsp/lsp_diag_pipeline_ctx.o ] || [ "seeds/lsp_diag_pipeline_ctx.from_x.c" -nt src/lsp/lsp_diag_pipeline_ctx.o ]; then
  experimental_bootstrap_info "cc src/lsp/lsp_diag_pipeline_ctx.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/lsp_diag_pipeline_ctx.from_x.c -o src/lsp/lsp_diag_pipeline_ctx.o
  fi
}
ensure_asm_driver_seed_c_objs

# pipeline_x.o freshness for experimental bootstrap (G.7; twin of
# ensure_pipeline_x_o_fresh in build_xlang_asm / strict_glue).
# PLATFORM: SHARED — after wave335 / 8.3 leave, ast_pool.c and pipeline_glue.c are
# absent; dead -nt on those paths never fired. pipeline_x.o producer =
# src/pipeline/pipeline.x via try-gen-x. Abi/WPO freshness is
# ensure_experimental_ast_pool_for_wpo (build_xlang_asm) — do not retarget this
# helper to abi.x (would forever need=1 on stub pipeline_x.o). Name kept.
rebuild_pipeline_x_force() {
  if [ "${XLANG_EXPERIMENTAL_BOOTSTRAP_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    make -s pipeline_x.o PIPELINE_X_FORCE_COMPILE=1 || return 1
  else
    PIPELINE_X_FORCE_COMPILE=1 bash scripts/ensure_host_cc_seed_o.sh try-heat pipeline_x.o || return 1
  fi
  return 0
}

ensure_pipeline_x_fresh_for_ast_pool() {
  local need=0
  local pipe_x="src/pipeline/pipeline.x"
  if [ ! -f pipeline_x.o ]; then
  need=1
  elif [ -f "$pipe_x" ] && [ "$pipe_x" -nt pipeline_x.o ]; then
  need=1
  fi
  if [ "$need" -eq 1 ]; then
  experimental_bootstrap_info "pipeline.x newer than pipeline_x.o - rebuild (0-make try-heat)"
  rebuild_pipeline_x_force || {
  experimental_bootstrap_warn "pipeline_x.o rebuild failed"
  return 1
  }
  fi
  return 0
}
ensure_pipeline_x_fresh_for_ast_pool || true

# experimental 链符号桥（缺则 ld 失败）。
if [ ! -f "$BUILD_DIR/asm_experimental_symbol_bridge.o" ] || [ "seeds/asm_experimental_symbol_bridge.from_x.c" -nt "$BUILD_DIR/asm_experimental_symbol_bridge.o" ]; then
  experimental_bootstrap_info "cc asm_experimental_symbol_bridge.o"
  sh scripts/cc_inc_tu.sh seeds/asm_experimental_symbol_bridge.from_x.c "$BUILD_DIR/asm_experimental_symbol_bridge.o"
fi

# runtime_asm_build.o（首链 bootstrap-asm 产物；缺则 ld 失败）。
if [ ! -f src/asm/runtime_asm_build.o ] || [ "seeds/runtime_asm_build.from_x.c" -nt src/asm/runtime_asm_build.o ]; then
  experimental_bootstrap_info "cc runtime_asm_build.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_asm_build.from_x.c -o src/asm/runtime_asm_build.o
fi

# B-strict xlang_asm：driver_run_compiler_full 走 impl_c（与 build_xlang_asm.sh 一致）。
# PLATFORM: SHARED — G-02e: runtime_abi.c / runtime_proc_abi.c merged into runtime_link_abi.
ensure_runtime_io_abi_obj() {
  local o="src/runtime_io_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_io_abi.from_x.c" -nt "$o" ]; then
  experimental_bootstrap_info "cc $o <- seeds/runtime_io_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o "$o"
  fi
}
ensure_runtime_link_abi_obj() {
  local o="src/runtime_link_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_link_abi.from_x.c" -nt "$o" ]; then
  experimental_bootstrap_info "cc $o <- seeds/runtime_link_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_link_abi.from_x.c -o "$o"
  fi
}
ensure_runtime_driver_asm_strict_obj() {
  ensure_runtime_io_abi_obj
  ensure_runtime_link_abi_obj
  local o="src/runtime_driver_asm_strict.o"
  # wave321 7.1.1: monofile retired — alias multi-slice product no_c.
  # PLATFORM: SHARED freestanding experimental bootstrap archaeology path.
  if [ ! -f "$o" ] \
    || { [ -f seeds/rt_content.from_x.c ] && [ seeds/rt_content.from_x.c -nt "$o" ]; }; then
    experimental_bootstrap_info "ensure $o ← multi-slice no_c alias (wave321 monofile retired)"
    bash scripts/ensure_host_cc_seed_o.sh try-rt-prefer src/runtime_driver_no_c.o || return 1
    cp -f src/runtime_driver_no_c.o "$o" || return 1
  fi
}
ensure_runtime_driver_asm_strict_obj

# pipeline_glue / pipeline_x 引用 target_cpu / simd_enc / simd_loop（SIMD-S1–S4）。
ensure_simd_glue_link_objs() {
  # G-02e: f32 xmm ABI 并入 backend_call_dispatch.o（无独立 pipeline_abi_f32_xmm.o）
  if [ ! -f src/asm/backend_call_dispatch.o ] || [ seeds/backend_call_dispatch.from_x.c -nt src/asm/backend_call_dispatch.o ]; then
  experimental_bootstrap_info "cc seeds/backend_call_dispatch.from_x.c → src/asm/backend_call_dispatch.o"
  $CC $CFLAGS -c seeds/backend_call_dispatch.from_x.c -o src/asm/backend_call_dispatch.o
  fi
  if [ ! -f src/driver/target_cpu.o ] || [ seeds/target_cpu_pure.from_x.c -nt src/driver/target_cpu.o ]; then
  experimental_bootstrap_info "cc src/driver/target_cpu.o"
  sh scripts/cc_inc_tu.sh seeds/target_cpu_pure.from_x.c src/driver/target_cpu.o -I. -Iinclude -Isrc
  fi
  if [ ! -f src/asm/simd_enc.o ] || [ seeds/simd_enc.from_x.c -nt src/asm/simd_enc.o ]; then
  experimental_bootstrap_info "cc seeds/simd_enc.from_x.c → src/asm/simd_enc.o"
  $CC $CFLAGS -c seeds/simd_enc.from_x.c -o src/asm/simd_enc.o
  fi
  if [ ! -f src/asm/simd_loop.o ] || [ seeds/simd_loop.from_x.c -nt src/asm/simd_loop.o ]; then
  experimental_bootstrap_info "cc seeds/simd_loop.from_x.c → src/asm/simd_loop.o"
  $CC $CFLAGS -c seeds/simd_loop.from_x.c -o src/asm/simd_loop.o
  fi
}
ensure_simd_glue_link_objs

# build_asm 伴生 .o（experimental 链与 build_xlang_asm ensure_asm_bootstrap_x_companion_objs 对齐）。
# PLATFORM: SHARED — post-Makefile phys-del: shell multi-family ensure (twin of
# build_xlang_asm wave931). VIA_MAKE + MF escapes to historic make list.
ensure_experimental_companion_objs() {
  mkdir -p "$BUILD_DIR" "$BUILD_DIR/seed_host"
  if [ "${XLANG_EXPERIMENTAL_BOOTSTRAP_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    experimental_bootstrap_info "VIA_MAKE ensure X companion objs"
    make -s parser_x.o lexer_x.o typeck_x.o codegen_x.o preprocess_x.o \
      x_frontend_link_alias.o \
      driver_x.o driver_fmt_x.o driver_check_x.o driver_test_x.o \
      driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o \
      pipeline_bootstrap_orchestration.o 2>/dev/null || true
  else
    experimental_bootstrap_info "0-make ensure X companion objs (migrate/try-heat/driver_leaf)"
    bash scripts/migrate_x_objs.sh parser_x.o || true
    bash scripts/migrate_x_objs.sh typeck_x.o || true
    bash scripts/migrate_x_objs.sh codegen_x.o || true
    bash scripts/ensure_host_cc_seed_o.sh try-heat lexer_x.o || true
    bash scripts/ensure_host_cc_seed_o.sh try-heat preprocess_x.o || true
    bash scripts/ensure_host_cc_seed_o.sh try-heat driver_x.o || true
    bash scripts/ensure_host_cc_seed_o.sh try-heat x_frontend_link_alias.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_fmt_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_check_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_test_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_build_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_run_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_compile_x.o || true
    bash scripts/driver_leaf_x_to_o.sh ensure driver_emit_x.o || true
    if [ ! -f pipeline_bootstrap_orchestration.o ] \
      || [ seeds/pipeline_bootstrap_orchestration.from_x.c -nt pipeline_bootstrap_orchestration.o ]; then
      if [ -f seeds/pipeline_bootstrap_orchestration.from_x.c ]; then
        experimental_bootstrap_info "cc pipeline_bootstrap_orchestration.o <- seeds"
        $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/pipeline_bootstrap_orchestration.from_x.c \
          -o pipeline_bootstrap_orchestration.o || true
      fi
    fi
  fi
  if [ ! -f src/runtime_io_abi.o ] || [ seeds/runtime_io_abi.from_x.c -nt src/runtime_io_abi.o ]; then
  experimental_bootstrap_info "cc runtime_io_abi.o (incl. fs/sys shim)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o src/runtime_io_abi.o
  fi
  if [ ! -f "$BUILD_DIR/x_seed_bridge.o" ] || [ "seeds/x_seed_bridge.from_x.c" -nt "$BUILD_DIR/x_seed_bridge.o" ]; then
  experimental_bootstrap_info "cc x_seed_bridge.o (G-02f-11 seed)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/x_seed_bridge.from_x.c -o "$BUILD_DIR/x_seed_bridge.o"
  fi
  if [ ! -f src/runtime_driver_strict_glue_stubs.o ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt src/runtime_driver_strict_glue_stubs.o ]; then
    experimental_bootstrap_info "cc runtime_driver_strict_glue_stubs.o (G-02f-11 seed)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o src/runtime_driver_strict_glue_stubs.o
  fi
  if [ ! -f "$BUILD_DIR/seed_host/asm_backend_partial.o" ] || [ "src/asm/backend.x" -nt "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
  experimental_bootstrap_info "build_seed_asm_host (asm_backend_partial.o)"
  ./scripts/build_seed_asm_host.sh
  fi
  if [ ! -f src/asm/asm_backend_compat_stubs.o ] || [ "seeds/asm_backend_compat_stubs.from_x.c" -nt src/asm/asm_backend_compat_stubs.o ]; then
  experimental_bootstrap_info "cc asm_backend_compat_stubs.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/asm_backend_compat_stubs.from_x.c -o src/asm/asm_backend_compat_stubs.o
  fi
  if [ ! -f src/asm/user_asm_seed_bridge.o ] || [ "seeds/user_asm_seed_bridge.from_x.c" -nt src/asm/user_asm_seed_bridge.o ]; then
  experimental_bootstrap_info "cc user_asm_seed_bridge.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/user_asm_seed_bridge.from_x.c -o src/asm/user_asm_seed_bridge.o
  fi
}
ensure_experimental_companion_objs

# parser thin C glue（EMIT_HEAVY 第二遍 bl→parser_*_glue 符号）。
PARSER_ASM_THIN_GLUE_CFLAGS="-DPARSER_ASM_THIN_GLUE_NO_SEED_PARSE"
PARSER_ASM_LINK_ALIAS_CFLAGS="-DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS"
PARSER_ASM_THIN_C="parser_asm_thin_glue.o"
if [ ! -f "$PARSER_ASM_THIN_C" ] || [ "seeds/parser_asm_thin_c.from_x.c" -nt "$PARSER_ASM_THIN_C" ] \
  || [ "seeds/parser_asm/parser_asm_struct_layout_slice.inc" -nt "$PARSER_ASM_THIN_C" ] \
  || [ "seeds/parser_asm/parser_asm_block_from_res_slice.inc" -nt "$PARSER_ASM_THIN_C" ] \
  || [ "seeds/parser_asm/parser_asm_if_stmt_slice.inc" -nt "$PARSER_ASM_THIN_C" ]; then
  experimental_bootstrap_info "cc parser_asm_thin_glue.o"
  sh scripts/cc_inc_tu.sh seeds/parser_asm_thin_c.from_x.c "$PARSER_ASM_THIN_C" $PARSER_ASM_THIN_GLUE_CFLAGS -I. -Iinclude -Isrc -Isrc/lexer
fi

# parse_expr_into 桥 + pipeline 弱 parse 桩（G-02e-7：原 parser_asm_link_alias 并入）
if [ ! -f "$PARSER_EXPR_LINK_O" ] || [ "seeds/parser_asm_parse_expr_link.from_x.c" -nt "$PARSER_EXPR_LINK_O" ]; then
  experimental_bootstrap_info "cc parser_asm_parse_expr_link.o"
  sh scripts/cc_inc_tu.sh seeds/parser_asm_parse_expr_link.from_x.c "$PARSER_EXPR_LINK_O" $PARSER_ASM_LINK_ALIAS_CFLAGS
fi
if [ ! -f "$PARSER_ASM_PARTIAL" ] && [ -f "$BUILD_DIR/parser.o" ]; then
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  cat > "$BUILD_DIR/parser_asm_minimal_export.txt" <<'EOF'
_parse_expr_into
_copy_module_import_path64
_parse_one_function_ok_for_pipeline
EOF
  ld -r -exported_symbols_list "$BUILD_DIR/parser_asm_minimal_export.txt" -o "$PARSER_ASM_PARTIAL" "$BUILD_DIR/parser.o"
  else
  # Linux：ld -exported_symbols_list 为 Mach-O 语法；bootstrap 链不依赖 partial，跳过即可。
  cp -f "$BUILD_DIR/parser.o" "$PARSER_ASM_PARTIAL"
  fi
fi

# parser_x.o：Makefile 要求 parser_copy_module_import_path64 在 gen 内；experimental 链由 link_alias+thin_glue 提供。
# PLATFORM: SHARED — post-Makefile phys-del: migrate_x_objs (G.7 twin of build_xlang_asm wave929).
ensure_parser_x_obj() {
  if [ -f parser_x.o ]; then
  return 0
  fi
  if [ "${XLANG_EXPERIMENTAL_BOOTSTRAP_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    make -s parser_x.o 2>/dev/null || true
  else
    experimental_bootstrap_info "migrate_x_objs parser_x.o (0-make)"
    bash scripts/migrate_x_objs.sh parser_x.o || true
  fi
  if [ ! -f parser_x.o ] && [ -f parser_gen.c ]; then
  experimental_bootstrap_info "cc parser_gen.c -> parser_x.o (link_alias supplies parser_* pipeline symbols)"
  # Catalog owns PIPELINE_GEN_CFLAGS post phys-del (no make print-*).
  _pgc=""
  if [ -f scripts/driver_seed_obj_catalog.sh ]; then
    _pgc=$(bash scripts/driver_seed_obj_catalog.sh --cflags-export 2>/dev/null \
      | sed -n 's/^PIPELINE_GEN_CFLAGS=//p' | tail -n 1)
  fi
  "$CC" $CFLAGS ${_pgc} \
  -I. -Iinclude -Isrc \
  -Dstd_io_driver_driver_read_ptr_len=xlang_io_read_ptr_len \
  -Dstd_io_driver_driver_read_ptr=xlang_io_read_ptr \
  -c parser_gen.c -o parser_x.o
  fi
  if [ ! -f parser_x.o ]; then
  experimental_bootstrap_error "missing parser_x.o (migrate_x_objs / restore parser_gen.c)"
  exit 1
  fi
}
ensure_parser_x_obj

# 瘦 parser_x.o 无 parse_into_buf：默认 cc seed slice TU；X PARSE_BOOTSTRAP_EMIT 仍 139，仅 opt-in 探测。
ensure_parser_parse_bootstrap_asm_obj() {
  PARSER_PARSE_BOOT_O="$BUILD_DIR/parser_parse_bootstrap.o"
  PBOOT_C_SRC="seeds/parser_asm/parser_asm_parse_bootstrap_obj.inc"
  PBOOT_SEED_SLICE="seeds/parser_asm/parser_asm_seed_parse_into_buf_slice.inc"
  mkdir -p "$BUILD_DIR"

  compile_parser_parse_bootstrap_cc_obj() {
  experimental_bootstrap_info "cc parser_asm_parse_bootstrap_obj.inc -> $PARSER_PARSE_BOOT_O"
  # PLATFORM: SHARED — match parser_asm_thin_c: -Isrc/asm for parser_asm_stretch_audit_gate.h
  # (default cc_inc_tu only has -I. -Iinclude -Isrc; bare #include "parser_asm_stretch_audit_gate.h" fails).
  if ! sh scripts/cc_inc_tu.sh "$PBOOT_C_SRC" "$PARSER_PARSE_BOOT_O" -Isrc/lexer -Isrc/asm; then
  experimental_bootstrap_warn "cc parser_parse_bootstrap.o failed"
  rm -f "$PARSER_PARSE_BOOT_O"
  return 1
  fi
  if ! nm -g "$PARSER_PARSE_BOOT_O" 2>/dev/null | grep -qE '[[:space:]]parse_into_buf$'; then
  experimental_bootstrap_warn "parser_parse_bootstrap.o missing parse_into_buf"
  rm -f "$PARSER_PARSE_BOOT_O"
  return 1
  fi
  return 0
  }

  try_parser_parse_bootstrap_x_emit() {
  XLANG_SEED="./xlang"
  PBOOT_LIBROOT="-L asm_libroot -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess -L src/pipeline -L src/lsp -L src/asm"
  if [ -x ./xlang_asm2_refreshed ] && file ./xlang_asm2_refreshed 2>/dev/null | grep -q "ELF.*x86-64"; then
  _min="/tmp/xlang_seed_parse_probe.$$.x"
  printf 'function main(): i32 { return 0; }\n' > "$_min"
  if ! env XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 ./xlang build -backend asm -o /tmp/xlang_seed_probe.$$.o \
  $PBOOT_LIBROOT "$_min" 2>/dev/null || [ ! -s /tmp/xlang_seed_probe.$$.o ]; then
  XLANG_SEED="./xlang_asm2_refreshed"
  experimental_bootstrap_warn "./xlang parse probe failed - bootstrap seed=$XLANG_SEED"
  fi
  rm -f "$_min" /tmp/xlang_seed_probe.$$.o 2>/dev/null || true
  fi
  if [ ! -x "$XLANG_SEED" ]; then
  return 1
  fi
  # G.7: pipeline_x.o producer = pipeline.x (deleted ast_pool.c never fires).
  _pipe_x="src/pipeline/pipeline.x"
  if { [ ! -f pipeline_x.o ] \
    || { [ -f "$_pipe_x" ] && [ "$_pipe_x" -nt pipeline_x.o ]; }; }; then
  experimental_bootstrap_info "pipeline.x newer - rebuild pipeline_x.o for parse bootstrap (0-make try-heat)"
  rebuild_pipeline_x_force || true
  fi
  if [ -f pipeline_x.o ] && [ pipeline_x.o -nt "$XLANG_SEED" ] 2>/dev/null; then
  experimental_bootstrap_info "refresh ./xlang (pipeline_x.o for parse bootstrap emit; 0-make g05)"
  if [ "${XLANG_EXPERIMENTAL_BOOTSTRAP_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    make -s relink-xlang 2>/dev/null || true
  else
    # g05 --no-sync = historic relink-xlang (xlang only; no xlang_asm sync).
    bash scripts/g05_prepare_and_relink.sh --no-sync 2>/dev/null || true
  fi
  fi
  experimental_bootstrap_info "$XLANG_SEED asm parser parse bootstrap (XLANG_ASM_PARSER_PARSE_BOOTSTRAP_EMIT opt-in)"
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  if ! env -u XLANG_ASM_START_FUNC XLANG_ASM_PARSER_PARSE_BOOTSTRAP_EMIT=1 \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 XLANG_ASM_WPO_DCE=0 \
  "$XLANG_SEED" -backend asm -o "$PARSER_PARSE_BOOT_O" $PBOOT_LIBROOT src/parser/parser.x \
  2>"$BUILD_DIR/.parser_parse_bootstrap_err"; then
  experimental_bootstrap_warn "parser parse bootstrap X emit failed"
  tail -8 "$BUILD_DIR/.parser_parse_bootstrap_err" 2>/dev/null | sed 's/^/ /' || true
  rm -f "$PARSER_PARSE_BOOT_O"
  return 1
  fi
  if ! nm -g "$PARSER_PARSE_BOOT_O" 2>/dev/null | grep -qE '[[:space:]]parse_into_buf$'; then
  experimental_bootstrap_warn "X bootstrap .o missing parse_into_buf"
  rm -f "$PARSER_PARSE_BOOT_O"
  return 1
  fi
  return 0
  }

  need_rebuild=0
  if [ ! -f "$PARSER_PARSE_BOOT_O" ]; then
  need_rebuild=1
  elif [ "$PBOOT_C_SRC" -nt "$PARSER_PARSE_BOOT_O" ] || [ "$PBOOT_SEED_SLICE" -nt "$PARSER_PARSE_BOOT_O" ]; then
  need_rebuild=1
  fi

  if [ "$need_rebuild" = "1" ]; then
  if [ "${XLANG_ASM_PARSER_PARSE_BOOTSTRAP_X_EMIT:-0}" = "1" ]; then
  try_parser_parse_bootstrap_x_emit || compile_parser_parse_bootstrap_cc_obj || true
  else
  compile_parser_parse_bootstrap_cc_obj || true
  fi
  fi

  if [ ! -f "$PARSER_PARSE_BOOT_O" ]; then
  PARSER_PARSE_BOOT_O=""
  fi
  # parser_x.o 已真 emit parse_into* 时勿再链 bootstrap .o（否则 ld multiple definition）。
  if [ -f parser_x.o ] && nm parser_x.o 2>/dev/null | grep -qE '[[:space:]]T parser_parse_into_buf$'; then
  PARSER_PARSE_BOOT_O=""
  fi
}
ensure_parser_parse_bootstrap_asm_obj

for o in pipeline_x.o pipeline_bootstrap_orchestration.o preprocess_x.o lexer_x.o typeck_x.o codegen_x.o \
  x_frontend_link_alias.o \
  driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o; do
  if [ ! -f "$o" ]; then
  experimental_bootstrap_error "missing $o (migrate/try-heat/driver_leaf ensure)"
  exit 1
  fi
done

PIPELINE_RUN_X_ALIAS_O="src/asm/pipeline_run_x_link_alias.o"
if [ ! -f "$PIPELINE_RUN_X_ALIAS_O" ] || [ "seeds/pipeline_run_x_link_alias.from_x.c" -nt "$PIPELINE_RUN_X_ALIAS_O" ]; then
  experimental_bootstrap_info "cc pipeline_run_x_link_alias.o"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_x_link_alias.from_x.c "$PIPELINE_RUN_X_ALIAS_O"
fi

# Linux：std/io io_uring 须 -luring（与 build_xlang_asm.sh PIPELINE_LIBS 一致）。
# NL-07 L10: nostdlib drops -luring/-lpthread/-lc (G.7 shared policy).
# shellcheck disable=SC1091
. scripts/bootstrap_nostdlib_shared.sh
# Stage 12.2.3: pure-ld helpers (zero-CC when XLANG_ZERO_CC_LD=1).
# PLATFORM: SHARED.
# shellcheck disable=SC1091
. scripts/pure_ld_shared.sh
PIPELINE_LIBS=""
EXP_LINK_TAIL="-lm -lc"
if bootstrap_wants_nostdlib; then
  # PLATFORM: LINUX — same freestanding/stubs/atoi tail as g05/crt0.
  experimental_bootstrap_info "NL-07 L10 experimental: nostdlib tail (no -lc/-lpthread)"
  EXP_LINK_TAIL="$(bootstrap_nostdlib_link_flags) $(bootstrap_nostdlib_extra_objs)"
elif [ "$(uname -s)" = "Linux" ]; then
  PIPELINE_LIBS="-luring -lpthread"
fi

experimental_bootstrap_info "linking xlang_asm.experimental"
# seed parser/typeck/codegen/lexer 供 runtime/lsp_diag 链接；parser_x/typeck_x 须链在末尾压过重复 glue（build_xlang_asm ST_PARSER_X_TAIL）。
# lsp_state.o 依赖 typeck_lsp_main_impl（与 strict_glue ensure_strict_glue_lsp_objs 一致）。
ensure_experimental_lsp_objs() {
  GEN_DIR="$BUILD_DIR/gen_driver"
  mkdir -p "$GEN_DIR"
  # wave937: shell-primary (was make -s lsp_io_gen.c lsp_gen.c ...). Mirrors
  # build_xlang_asm.sh ensure_asm_experimental_lsp_objs shell path (wave930).
  experimental_bootstrap_warn "ensure lsp_x.o (+ lsp_io + lsp_diag) via shell"
  bash scripts/ensure_lsp_pipeline_gen.sh lsp
  bash scripts/ensure_lsp_pipeline_gen.sh lsp_diag
  bash scripts/ensure_archaeology_gen.sh lsp_io_std_heap
  bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_x.o
  bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_io_x.o
  bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_diag_x.o
  if [ ! -f lsp_io_std_heap_x.o ]; then
    bash scripts/driver_leaf_x_to_o.sh ensure lsp_io_std_heap_x.o
  fi
  cp -f lsp_x.o lsp_io_x.o lsp_diag_x.o lsp_io_std_heap_x.o "$GEN_DIR/"
}
ensure_experimental_lsp_objs || true
ST_LSP_X=""
if [ -f "$BUILD_DIR/gen_driver/lsp_x.o" ]; then
  ST_LSP_X="$BUILD_DIR/gen_driver/lsp_x.o $BUILD_DIR/gen_driver/lsp_io_x.o $BUILD_DIR/gen_driver/lsp_io_std_heap_x.o $BUILD_DIR/gen_driver/lsp_diag_x.o"
fi
# wave297: host scripts/asm_xlang_lsp_diag_stub.c left; seed authority seed-only .o.
if [ ! -f "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" ] || [ "seeds/asm_xlang_lsp_diag_stub.from_x.c" -nt "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" ]; then
  "$CC" $CFLAGS -c -o "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" seeds/asm_xlang_lsp_diag_stub.from_x.c
fi
ST_LSP_DIAG_STUB="$BUILD_DIR/asm_xlang_lsp_diag_stub.o"
GLUE_O="$BUILD_DIR/pipeline_glue_standalone.o"
PIPELINE_GEN_CFLAGS="-O2 -g -fno-strict-aliasing -DPIPELINE_GEN_STANDALONE"
# wave309: pipeline_glue_standalone.from_x.c seed retired; pure runtime_pipeline_abi.o
# is G.7 authority. Skip compilation when seed absent (non-fatal; experimental link
# resolves via runtime_pipeline_abi.o). Deleted ast_pool.c / pipeline_glue.c -nt never
# fired post-leave — freshness = seed only when present. PLATFORM: SHARED.
if [ -f seeds/pipeline_glue_standalone.from_x.c ] && \
  { [ ! -f "$GLUE_O" ] || [ "seeds/pipeline_glue_standalone.from_x.c" -nt "$GLUE_O" ]; }; then
  experimental_bootstrap_info "cc pipeline_glue_standalone.o"
  mkdir -p "$BUILD_DIR"
  sh scripts/cc_inc_tu.sh seeds/pipeline_glue_standalone.from_x.c "$GLUE_O" $PIPELINE_GEN_CFLAGS -I"$BUILD_DIR"
fi
# wave309: glue seed shell retired; drop GLUE_O if .o physically missing so LD argv
# does not reference non-existent file. Pure runtime_pipeline_abi.o / pipeline_x.o
# provide pipeline symbols (G.7). PLATFORM: SHARED.
[ -z "$GLUE_O" ] || [ -f "$GLUE_O" ] || GLUE_O=""
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  # -multiply_defined is obsolete on new macOS ld (causes link error: "file
  # cannot be open()ed, path=suppress"). G.7 single authority (parser_x.o
  # excludes parser.o) handles duplicates without linker flags.
  # PLATFORM: MACOS.
  EXP_ALLOW_MULTIDEF=""
else
  # PLATFORM: LINUX — --allow-multiple-definition is still supported by GNU ld.
  EXP_ALLOW_MULTIDEF="-Wl,--allow-multiple-definition"
fi
# parse_diag：与 Makefile RT_SEED_SLICE / g05 同源；runtime 仅声明 recovery 诊断。
if [ ! -f src/runtime/rt_parse_diag.o ] || [ seeds/rt_parse_diag.from_x.c -nt src/runtime/rt_parse_diag.o ]; then
  mkdir -p src/runtime
  experimental_bootstrap_info "cc src/runtime/rt_parse_diag.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/rt_parse_diag.from_x.c -o src/runtime/rt_parse_diag.o
fi
# RT_SEED_SLICE companions: same source as build_xlang_asm.sh line 4738-4741 and
# g05_relink_env (linked as separate .o to avoid Darwin duplicate symbols per
# ensure_host_cc_seed_o.sh comment). rt_emit_state.o provides driver_x_emit_c_path
# global; rt_arena_buf/rt_preamble/rt_stack provide other runtime globals referenced
# by driver/pipeline code paths. Without these, the experimental binary crashes at
# runtime (dyld: symbol not found in flat namespace).
# PLATFORM: SHARED.
for _exp_rt_pair in \
  "rt_arena_buf:src/runtime/rt_arena_buf.o" \
  "rt_emit_state:src/runtime/rt_emit_state.o" \
  "rt_preamble:src/runtime/rt_preamble.o" \
  "rt_stack:src/runtime/rt_stack.o"; do
  _exp_rt_name="${_exp_rt_pair%%:*}"
  _exp_rt_out="${_exp_rt_pair##*:}"
  if [ ! -f "$_exp_rt_out" ] || [ "seeds/${_exp_rt_name}.from_x.c" -nt "$_exp_rt_out" ]; then
    mkdir -p src/runtime
    experimental_bootstrap_info "cc $_exp_rt_out <- seeds/${_exp_rt_name}.from_x.c"
    $CC $CFLAGS -I. -Iinclude -Isrc -c "seeds/${_exp_rt_name}.from_x.c" -o "$_exp_rt_out"
  fi
done
# PLATFORM: SHARED — G-02e: no runtime_abi/proc_abi .o; link runtime_link_abi instead.
# Build OBJS string (shared between CC and pure-ld paths; G.7 single authority
# for the experimental bootstrap object inventory).
EXP_LINK_OBJS="src/asm/runtime_asm_build.o"
[ -z "$GLUE_O" ] || EXP_LINK_OBJS="$EXP_LINK_OBJS $GLUE_O"
EXP_LINK_OBJS="$EXP_LINK_OBJS src/runtime_pipeline_abi.o src/runtime_io_abi.o src/runtime_link_abi.o src/runtime_driver_asm_strict.o src/runtime/rt_parse_diag.o src/runtime/rt_arena_buf.o src/runtime/rt_emit_state.o src/runtime/rt_preamble.o src/runtime/rt_stack.o pipeline_x.o pipeline_bootstrap_orchestration.o preprocess_x.o src/runtime_driver_strict_glue_stubs.o driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o $BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_host/asm_backend_partial.o src/asm/user_asm_seed_bridge.o src/asm/asm_backend_compat_stubs.o src/asm/pipeline_run_x_link_alias.o $BSTRICT_DISPATCH src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o $BUILD_DIR/asm_experimental_symbol_bridge.o"
[ -z "$PARSER_PARSE_BOOT_O" ] || EXP_LINK_OBJS="$EXP_LINK_OBJS $PARSER_PARSE_BOOT_O"
[ -z "$ST_LSP_DIAG_STUB" ] || EXP_LINK_OBJS="$EXP_LINK_OBJS $ST_LSP_DIAG_STUB"
EXP_LINK_OBJS="$EXP_LINK_OBJS $SEED_O/async_liveness.o $SEED_O/async_cps_codegen.o $SEED_O/ast_seed.o $SEED_O/lexer.o $SEED_O/lsp_diag.o"
# G.7: parser_x.o is the Track L authority (covers all parser.o symbols).
# Skip seed parser.o when parser_x.o exists to avoid duplicate symbols
# (-multiply_defined suppress is obsolete on new macOS ld; G.7 single
# authority requires only one parser provider in the link).
# PLATFORM: SHARED.
[ -f parser_x.o ] || EXP_LINK_OBJS="$EXP_LINK_OBJS $SEED_O/parser.o"
[ -z "$ST_LSP_X" ] || EXP_LINK_OBJS="$EXP_LINK_OBJS $ST_LSP_X"
EXP_LINK_OBJS="$EXP_LINK_OBJS src/lsp/lsp_diag_pipeline_ctx.o src/lsp/lsp_diag_pipeline_sizes.o $PARSER_ASM_THIN_C $PARSER_EXPR_LINK_O parser_x.o lexer_x.o typeck_x.o codegen_x.o x_frontend_link_alias.o"
# Stage 12.2.3: Add objects to close pre-existing undefined symbol gap between
# experimental chain and g05 product chain (symbols present in g05 but missing
# from experimental link). Objects identified by diffing g05 G05_OBJS against
# EXP_LINK_OBJS — G.7 single authority (g05_relink_env.sh is the production
# truth; experimental link must converge to same object set modulo bootstrap
# specific runtime_asm_build.o / asm_experimental_symbol_bridge.o).
#
# Key fix 1: use src/lexer/cfg_eval.o (full partial merge: cfg_eval_x.o +
# cfg_eval_link_alias.o via ld -r) instead of bare cfg_eval_link_alias.o.
# The link_alias alone CONSUMES lexer_cfg_* symbols (U in nm); cfg_eval.o
# PROVIDES them (T in nm). This matches g05 _DRIVER_SEED_SUPPORT in no_c
# default mode. Without this fix the link fails with 4 lexer_cfg_* U refs.
#
# Key fix 2: add src/asm/backend_arm64_enc_c.o (arm64 instruction encoder).
# Without it, asm_codegen on Darwin arm64 produces code_len=0 (CG002) because
# arch_arm64_enc_enc_mov_imm32_to_w0 (needed for `return N` → `mov w0, #N`)
# is undefined. g05 _USER_ASM_LINK includes both x86_64_enc_c.o AND
# arm64_enc_c.o for cross-target support; experimental BSTRICT_DISPATCH
# only had x86_64. PLATFORM: SHARED — arm64 encoder needed on Darwin arm64;
# x86_64 encoder needed on Linux x86_64; both included for cross-target.
#
# Key fix 3: add driver_x.o (main entry + command dispatch). The experimental
# chain had individual driver_*_x.o subcommand objects but NOT driver_x.o
# itself, which provides _main_run_compiler_c_impl and _main_* helpers.
# Without it, `xlang_asm build` subcommand fails (rc=255, no output) though
# default `xlang_asm -o out src.x` works via a different main path.
#
# Key fix 4: add runtime_process_argv.o (process_xlang_argc_get /
# process_xlang_argv_get / xlang_process_argv_bind_from_crt). g05
# _DRIVER_SEED_OBJS includes this explicitly; experimental had only
# process_args_count_c from runtime_driver_asm_strict.o.
#
# NOTE: LSP objects (lsp_x.o, lsp_diag_x.o, lsp_io_x.o, lsp_io_std_heap_x.o,
# src/lsp/lsp_diag.o) are NOT added here because the experimental chain
# already includes them via $SEED_O/lsp_diag.o and $ST_LSP_X variables
# (lines 465-473). Adding them again causes 145 duplicate symbols.
#
# PLATFORM: SHARED — all objects exist on both macOS and Ubuntu after g05
# ensure. arm64_enc_c.o is needed on arm64; x86_64_enc_c.o on x86_64;
# both included for cross-target codegen (matches g05).
EXP_LINK_OBJS="$EXP_LINK_OBJS src/seed_link_compat.o build_asm/seed_host/asm_full_link_stubs.o src/runtime_driver_diagnostic.o src/runtime_driver_abi.o src/diag.o src/async/async_asm_pool.o src/lexer/cfg_eval.o src/typeck/typeck_f64_bits.o"
EXP_LINK_OBJS="$EXP_LINK_OBJS src/asm/backend_arm64_enc_c.o driver_x.o runtime_process_argv.o"

# Stage 12.2.3: zero-CC experimental bootstrap link via pure_ld_try_link
# (G.7 single authority). When XLANG_ZERO_CC_LD=1 and host is freestanding-eligible,
# use `ld` directly instead of `$CC -o`. When unset or host ineligible, original
# `$CC` path (zero regression).
#
# Hosted (non-nostdlib): include system crt1.o (provides _start → main, same
#   entry chain as $CC's automatic crt1). Entry = pure_ld_default_entry (-e _start).
# Nostdlib (Linux x86_64): no crt1 (nostdlib = no standard crt); entry = -e main
#   (direct kernel → main, matching the $CC -nostdlib behavior where main is the
#   effective entry). Extra = -static --gc-sections. nostdlib_extra_objs are .o
#   files and go into OBJS, not tail.
#
# PLATFORM: SHARED — Darwin (hosted crt1) + Linux x86_64 (hosted crt1 or nostdlib).
if [ "${XLANG_ZERO_CC_LD:-0}" = "1" ] && pure_ld_freestanding_ok; then
  if bootstrap_wants_nostdlib; then
    # PLATFORM: LINUX — nostdlib freestanding (no crt1; direct main entry).
    EXP_NOSTDLIB_EXTRA="$(bootstrap_nostdlib_extra_objs)"
    EXP_LD_ENTRY="-e main"
    EXP_LD_TAIL=""
    EXP_LD_EXTRA="-static --gc-sections"
    EXP_LD_OBJS="$EXP_LINK_OBJS $EXP_NOSTDLIB_EXTRA"
  else
    # Hosted: no crt1.o needed on modern Darwin (LC_MAIN auto-detection) or
    # Linux (ld defaults to _start or accepts -e main). $CC auto-includes
    # crt1.o, but pure-ld relies on LC_MAIN (Darwin) or -e main (Linux) to
    # bypass crt1 entirely. This matches $CC's LC_MAIN behavior on modern macOS.
    EXP_LD_TAIL="-lm $(pure_ld_default_libc_tail)"
    if [ "$(uname -s)" = "Linux" ]; then
      EXP_LD_TAIL="$EXP_LD_TAIL -luring -lpthread"
      # Linux: -e main sets entry to main (no crt1 needed; matches $CC -nostdlib
      # behavior where main is the effective entry).
      EXP_LD_ENTRY="-e main"
      EXP_LD_EXTRA=""
    else
      # Darwin: empty entry → ld auto-detects main → LC_MAIN (same as $CC).
      # -undefined dynamic_lookup: $CC default for dynamic links; experimental
      # binary has lazy-resolved xlang_* symbols never called at runtime.
      EXP_LD_ENTRY=""
      EXP_LD_EXTRA="-undefined dynamic_lookup"
    fi
    EXP_LD_OBJS="$EXP_LINK_OBJS"
  fi
  experimental_bootstrap_info "pure-ld → xlang_asm.experimental ($(printf '%s' "$EXP_LD_OBJS" | wc -w | tr -d ' ') objs)"
  if ! pure_ld_try_link xlang_asm.experimental "$EXP_LD_OBJS" "$EXP_LD_ENTRY" "$EXP_LD_TAIL" "$EXP_LD_EXTRA" "" 2>"$BUILD_DIR/.relink_experimental_bootstrap_err"; then
    experimental_bootstrap_error "pure-ld link failed (no silent CC fallback; unset XLANG_ZERO_CC_LD for CC path)"
    tail -n 12 "$BUILD_DIR/.relink_experimental_bootstrap_err" 2>/dev/null | sed 's/^/ /' || true
    exit 1
  fi
else
  # Original $CC path (zero regression when flag unset or host ineligible).
  # shellcheck disable=SC2086
  "$CC" $CFLAGS $EXP_ALLOW_MULTIDEF -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm.experimental \
    $EXP_LINK_OBJS \
    $EXP_LINK_TAIL $PIPELINE_LIBS 2>"$BUILD_DIR/.relink_experimental_bootstrap_err"
  if [ ! -x xlang_asm.experimental ]; then
    experimental_bootstrap_error "link failed"
    tail -n 12 "$BUILD_DIR/.relink_experimental_bootstrap_err" 2>/dev/null | sed 's/^/ /' || true
    exit 1
  fi
fi

# PLATFORM: SHARED — do not silently promote experimental onto product xlang_asm.
# Produce-point of "experimental promote 链污染": WPO ensure /
# ensure_experimental_ast_pool_for_wpo called this script and the copy
# overwrote Ubuntu gold xlang_asm. G.7: complete this existing relink;
# do not invent a second WPO/promote path. Darwin strict-fail keep /
# smoke fallback / postlink experimental fallback consult the same flag
# (not a second promote path).
if [ "${XLANG_EXPERIMENTAL_PROMOTE_TO_PRODUCT:-0}" = "1" ]; then
  cp -f xlang_asm.experimental xlang_asm
  experimental_bootstrap_info "OK (promoted to xlang_asm; XLANG_EXPERIMENTAL_PROMOTE_TO_PRODUCT=1)"
else
  experimental_bootstrap_info "OK (xlang_asm.experimental only; product xlang_asm untouched)"
fi
experimental_bootstrap_info "verify: XLANG_S2_FAIL_ON_EMIT_HEAVY=1 ../tests/run-s2-typeck-emit-heavy.sh"
