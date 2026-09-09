#!/usr/bin/env bash
# Strict re-link xlang_asm: refresh partials / glue companions / EMIT_HEAVY without
# full build_xlang_asm. wave309: pipeline_glue_standalone seed + ast_pool.c retired;
# product authority = runtime_pipeline_abi.o (+ strict_minimal when present).
# Usage: cd compiler && ./scripts/relink_xlang_asm_strict_glue.sh
set -e
cd "$(dirname "$0")/.."
BUILD_DIR="build_asm"
CC=${CC:-cc}
CFLAGS="-Wall -Wextra -I. -Iinclude -Isrc"
SEED_O="$BUILD_DIR/asm_driver_seed"
export STRICT_LINK_BUILD_ASM_PIPELINE=1
# PLATFORM: SHARED — nm export lists are ASCII symbol names; force C locale so
# GNU sort and comm agree. Host locales (e.g. zh_CN.UTF-8) make sort/comm
# disagree on underscore/letter order → "file is not in sorted order" noise and
# wrong set subtraction for WPO partial export (dual authority with build_xlang_asm).
export LC_ALL=C
# Stage 12.2.3: source pure_ld_shared.sh for pure_as_compile (zero-CC .s assembly).
# PLATFORM: SHARED — used for runtime_panic .s compilation on Linux x86_64.
. scripts/pure_ld_shared.sh

# #region debug-point A:dbg-helpers
DBG_ENV_FILE="../.dbg/relink-strict-glue-hang.env"
DBG_RUN_ID="${DBG_RUN_ID:-pre-$$}"
DBG_HEARTBEAT_SEC="${DBG_HEARTBEAT_SEC:-10}"
dbg_load_env() {
  if [ -f "$DBG_ENV_FILE" ]; then
  # shellcheck disable=SC1090
  . "$DBG_ENV_FILE" 2>/dev/null || true
  fi
}
dbg_event() {
  local hypothesis_id="$1"
  local msg="$2"
  local esc
  esc="${msg//\\/\\\\}"
  esc="${esc//\"/\\\"}"
  esc="${esc//$'\n'/\\n}"
  dbg_load_env
  [ -n "${DEBUG_SERVER_URL:-}" ] || return 0
  command -v curl >/dev/null 2>&1 || return 0
  curl -sS -m 1 -X POST "$DEBUG_SERVER_URL" \
  -H 'Content-Type: application/json' \
  -d "{\"sessionId\":\"${DEBUG_SESSION_ID:-relink-strict-glue-hang}\",\"runId\":\"$DBG_RUN_ID\",\"hypothesisId\":\"$hypothesis_id\",\"location\":\"relink_xlang_asm_strict_glue.sh\",\"msg\":\"[DEBUG] $esc\"}" \
  >/dev/null 2>&1 || true
}
dbg_watch_pid() {
  local pid="$1"
  local what="$2"
  local start_s="$3"
  local now_s
  while kill -0 "$pid" 2>/dev/null; do
  now_s=$(date +%s 2>/dev/null || echo 0)
  dbg_event H4 "$what still running pid=$pid elapsed=$((now_s - start_s))s"
  sleep "$DBG_HEARTBEAT_SEC" 2>/dev/null || sleep 10
  done
}
trap 'rc=$?; dbg_event D "exit rc=$rc"' EXIT
dbg_event A "script start (cwd=$(pwd))"
# #endregion

strict_glue_warn() {
  printf 'warning: relink_xlang_asm_strict_glue: %s\n' "$*" >&2
}

strict_glue_info() {
  printf 'info: relink_xlang_asm_strict_glue: %s\n' "$*" >&2
}

strict_glue_error() {
  printf 'build error: relink_xlang_asm_strict_glue: %s\n' "$*" >&2
}

asm_seed_x_frontend_o_ready() {
  local o
  for o in parser_x.o typeck_x.o codegen_x.o lexer_x.o; do
  if [ ! -f "$o" ] || [ ! -s "$o" ]; then
  return 1
  fi
  done
  return 0
}

asm_seed_omit_c_frontend_seed() {
  if [ -n "${XLANG_LEGACY_SEED_FRONTEND_CC:-}" ]; then
  return 1
  fi
  asm_seed_x_frontend_o_ready
}

asm_seed_st_async_support_link() {
  echo "$SEED_O/async_liveness.o $SEED_O/async_cps_codegen.o"
}

asm_seed_st_preprocess_link() {
  # G-02a: preprocess.c 已物理删除；preprocess 由 preprocess_x.o 提供。
  echo ""
}

have_link_liburing() {
  printf 'int main(void){return 0;}\n' | "$CC" -x c - -o /dev/null -luring >/dev/null 2>&1
}

# codegen.c 引用 async_liveness / async_cps_codegen（与 Makefile OBJS_CORE、build_xlang_asm 一致）。
ensure_async_cps_seed_objs() {
  local src out
  for src_pair in \
  "seeds/async_liveness.from_x.c:$SEED_O/async_liveness.o" \
  "seeds/async_cps_codegen.from_x.c:$SEED_O/async_cps_codegen.o"; do
  src="${src_pair%%:*}"
  out="${src_pair##*:}"
  if [ ! -f "$out" ] || [ "$src" -nt "$out" ]; then
  strict_glue_info "cc -c $src -> $out"
  mkdir -p "$(dirname "$out")"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$out" "$src"
  fi
  done
}

# 与 build_xlang_asm.sh 一致：判断 build_asm/typeck.o 是否已 EMIT_HEAVY 自举（__text>8192）。
asm_o_text_bytes() {
  local o="$1"
  local hex
  hex=$(objdump -h "$o" 2>/dev/null | awk '$2 == "__text" { print $3; exit }')
  if [ -z "$hex" ]; then
  hex=$(objdump -h "$o" 2>/dev/null | awk '$2 == ".text" { print $3; exit }')
  fi
  if [ -z "$hex" ]; then
  echo 0
  return
  fi
  echo $((16#$hex))
}

asm_strict_typeck_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo 0)
  [ "$t" -gt 8192 ] 2>/dev/null
}

# macOS ld64 / lld 支持 -exported_symbols_list；GNU bfd ld 须 objcopy --keep-global-symbols。
ld_supports_exported_symbols_list() {
  ld -v 2>&1 | grep -qE 'PROJECT:ld64|LLD|LLVM'
}

# 从符号列表（每行一个，可带 Mach-O 前缀 _）做 ld -r 局部导出；与 build_xlang_asm.sh 一致。
# PLATFORM: SHARED — keep g_xlang_depctx_sc global when present (NL-07 pure static; see
# build_xlang_asm.sh ld_partial_export + runtime_pipeline_abi depctx table;
# ast_pool.c left wave309). Must stay in lockstep with that helper.
ld_partial_export() {
  local syms_file="$1"
  local out_o="$2"
  shift 2
  local in_o="$1"
  local export_list="$syms_file"
  local tmp_export=""
  if nm "$in_o" 2>/dev/null | grep -qE ' [A-Za-z] (_)?g_xlang_depctx_sc$'; then
  tmp_export="${out_o}.export_with_depctx.txt"
  cp "$syms_file" "$tmp_export"
  if ! grep -qE '^_?g_xlang_depctx_sc$' "$tmp_export" 2>/dev/null; then
  if nm "$in_o" 2>/dev/null | grep -qE ' _g_xlang_depctx_sc$'; then
  printf '%s\n' '_g_xlang_depctx_sc' >>"$tmp_export"
  else
  printf '%s\n' 'g_xlang_depctx_sc' >>"$tmp_export"
  fi
  fi
  export_list="$tmp_export"
  fi
  if ld_supports_exported_symbols_list; then
  ld -r -exported_symbols_list "$export_list" -o "$out_o" "$in_o"
  return $?
  fi
  local keep="$out_o.keep_syms"
  : > "$keep"
  while IFS= read -r sym || [ -n "$sym" ]; do
  [ -z "$sym" ] && continue
  case "$sym" in \#*) continue ;; esac
  sym="${sym#_}"
  echo "$sym" >> "$keep"
  done < "$export_list"
  ld -r -o "$out_o" "$in_o" || return 1
  objcopy --keep-global-symbols="$keep" "$out_o" "$out_o"
}

ensure_typeck_c_orchestration_partial_obj() {
  local PARTIAL="$BUILD_DIR/typeck_c_orchestration_partial.o"
  local SYMS="$BUILD_DIR/typeck_c_orchestration_export.txt"
  local TCKO="src/typeck/typeck.o"
  [ -f "$TCKO" ] || TCKO="$SEED_O/typeck.o"
  [ -f "$TCKO" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$TCKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  printf '%s\n' _typeck_module _typeck_one_function > "$SYMS"
  strict_glue_info "ld -r -exported_symbols_list $SYMS $TCKO -> $PARTIAL (C orchestration only)"
  ld_partial_export "$SYMS" "$PARTIAL" "$TCKO" 2>"$BUILD_DIR/.typeck_c_orch_partial_err" || return 1
  fi
  return 0
}

ensure_typeck_c_user_precheck_obj() {
  if ensure_typeck_c_orchestration_partial_obj; then
  echo "$BUILD_DIR/typeck_c_orchestration_partial.o"
  return 0
  fi
  # Fallback stubs are a valid precheck object; must return 0 so set -e callers
  # (ST_TYPECK_C_STUBS=$(ensure_...)) do not abort the strict_glue relink.
  # PLATFORM: SHARED.
  strict_glue_warn "typeck_c_orchestration_partial failed; using fallback stubs"
  if [ ! -f "$BUILD_DIR/typeck_c_module_stubs.o" ] || [ seeds/typeck_c_module_stubs.from_x.c -nt "$BUILD_DIR/typeck_c_module_stubs.o" ]; then
  strict_glue_info "cc -c seeds/typeck_c_module_stubs.from_x.c -> $BUILD_DIR/typeck_c_module_stubs.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$BUILD_DIR/typeck_c_module_stubs.o" seeds/typeck_c_module_stubs.from_x.c
  fi
  echo "$BUILD_DIR/typeck_c_module_stubs.o"
  return 0
}

# strict 链：C 编排 partial（run_x_pipeline_impl 等），与 build_xlang_asm.sh 一致。
ensure_pipeline_asm_orchestration_partial_obj() {
  local PARTIAL SYMS ALIAS_O
  PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_orchestration_export.txt"
  ALIAS_O="$BUILD_DIR/pipeline_asm_orchestration_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ "seeds/pipeline_asm_orchestration_alias.from_x.c" -nt "$ALIAS_O" ]; then
  strict_glue_info "cc_inc_tu seeds/pipeline_asm_orchestration_alias.from_x.c -> $ALIAS_O"
  sh scripts/cc_inc_tu.sh seeds/pipeline_asm_orchestration_alias.from_x.c "$ALIAS_O"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$ALIAS_O" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_pipeline_run_x_pipeline_impl
_run_x_pipeline_impl
_run_x_pipeline_parse_entry_do_parse
_run_x_pipeline_parse_entry_if_needed
_parse_into_with_init_buf
EOF
  strict_glue_info "ld partial export $SYMS orchestration_alias.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$ALIAS_O"
  fi
  cp -f "$PARTIAL" "$BUILD_DIR/pipeline_asm_runtime_partial.o"
  return 0
}

# strict WPO opt-in：pipeline_wpo.o helper 子集（编排入口仍走 C orchestration partial）。
ensure_pipeline_wpo_helpers_partial_obj() {
  local PARTIAL SYMS WPO_E
  PARTIAL="$BUILD_DIR/pipeline_wpo_helpers_partial.o"
  SYMS="$BUILD_DIR/pipeline_wpo_helpers_export.txt"
  WPO_E="$BUILD_DIR/pipeline_wpo.o"
  if [ ! -f "$WPO_E" ] || [ ! -s "$WPO_E" ]; then
  return 1
  fi
  if ! asm_pipeline_wpo_strict_reach_ok; then
  return 1
  fi
  # G.7: when runtime_pipeline_abi is already on strict LD argv, helpers extract from
  # pipeline_wpo overlaps (~1k T stubs) and Darwin ld -r rejects multi-LC_SEGMENT /
  # Ubuntu may hit internal multi-def. Soft-skip; abi covers orch (reach gate still
  # validates pipeline_wpo.o). strchr OOB dup emit fixed 2026-08-24. PLATFORM: SHARED.
  if asm_strict_pipeline_selfhosted; then
  strict_glue_info "skip pipeline_wpo_helpers_partial (runtime_pipeline_abi on LD argv; avoid dual/WPO ld -r)"
  return 1
  fi
  if [ ! -f "$SYMS" ] || [ "$WPO_E" -nt "$SYMS" ]; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | grep -vE \
  '^(run_x_pipeline_impl|run_x_pipeline_parse_entry_do_parse|run_x_pipeline_parse_entry_if_needed|run_x_pipeline_typecheck_entry|parse_into_with_init_buf|parse_into_with_init|pipeline_run_x_pipeline_impl|pipeline_run_x_pipeline)$' \
  >"$SYMS"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$WPO_E" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export pipeline_wpo helpers -> $PARTIAL"
  if ! ld_partial_export "$SYMS" "$PARTIAL" "$WPO_E"; then
  strict_glue_warn "pipeline_wpo_helpers ld -r failed (Darwin LC_SEGMENT / internal multi-def); soft-skip"
  rm -f "$PARTIAL" 2>/dev/null || true
  return 1
  fi
  nm "$PARTIAL" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt"
  fi
  return 0
}

# WPO opt-in：typecheck emit 桥（helper 内 X typecheck_entry thin bl 依赖）。
ensure_pipeline_wpo_typecheck_emit_bridge_obj() {
  local BR_O="$BUILD_DIR/pipeline_wpo_typecheck_emit_bridge.o"
  local BR_SRC="seeds/pipeline_wpo_typecheck_emit_bridge.from_x.c"
  [ -f "$BR_SRC" ] || return 1
  if [ ! -f "$BR_O" ] || [ "$BR_SRC" -nt "$BR_O" ]; then
  strict_glue_info "cc_inc_tu $BR_SRC -> $BR_O"
  sh scripts/cc_inc_tu.sh "$BR_SRC" "$BR_O" || return 1
  fi
  return 0
}

# B-hybrid / strict_glue：lsp_x.o 缺的 LSP 响应桩；typeck_lsp_io 见 seeds/typeck_lsp_io_stub.from_x.c。
# strict 链：ast.x 裸名 → pipeline_glue ast_ast_*（typeck_strict_link_partial 去重后缺 ast_block_if_*）。
ensure_ast_asm_bare_link_alias_obj() {
  local ALIAS_O="$BUILD_DIR/ast_asm_bare_link_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ seeds/ast_asm_bare_link_alias.from_x.c -nt "$ALIAS_O" ]; then
  strict_glue_info "cc ast_asm_bare_link_alias.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -I"$BUILD_DIR" -c -o "$ALIAS_O" seeds/ast_asm_bare_link_alias.from_x.c
  fi
}

# wave297: host scripts/asm_xlang_lsp_diag_stub.c left; seed authority seed-only .o.
ensure_asm_xlang_lsp_diag_stub_obj() {
  local STUB_C="seeds/asm_xlang_lsp_diag_stub.from_x.c"
  local STUB_O="$BUILD_DIR/asm_xlang_lsp_diag_stub.o"
  local LSP_IO_STUB="seeds/typeck_lsp_io_stub.from_x.c"
  local LSP_IO_O="$BUILD_DIR/typeck_lsp_io_stub.o"
  if [ ! -f "$LSP_IO_O" ] || [ "$LSP_IO_STUB" -nt "$LSP_IO_O" ]; then
  strict_glue_info "cc_inc_tu $LSP_IO_O <- $LSP_IO_STUB"
  sh scripts/cc_inc_tu.sh "$LSP_IO_STUB" "$LSP_IO_O"
  fi
  if [ ! -f "$STUB_O" ] || [ "$STUB_C" -nt "$STUB_O" ]; then
  strict_glue_info "cc -c $STUB_O <- $STUB_C"
  "$CC" $CFLAGS -c -o "$STUB_O" "$STUB_C"
  fi
}

# E-02：默认 seed 链 lsp_diag_stubs_no_c.o（与 build_xlang_asm.sh 一致）。
lsp_diag_seed_obj_path() {
  local seed_dir="$1"
  if [ "${XLANG_LEGACY_LSP_DIAG_C:-0}" = "1" ]; then
  echo "$seed_dir/lsp_diag.o"
  else
  echo "$seed_dir/lsp_diag_stubs_no_c.o"
  fi
}

ensure_lsp_diag_seed_obj() {
  local seed_dir="$1"
  if [ "${XLANG_LEGACY_LSP_DIAG_C:-0}" = "1" ]; then
  if [ ! -f "$seed_dir/lsp_diag.o" ] || [ "seeds/runtime_lsp_glue.from_x.c" -nt "$seed_dir/lsp_diag.o" ]; then
  strict_glue_info "cc -c $seed_dir/lsp_diag.o <- lsp_diag.c (LEGACY)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lsp_glue.from_x.c -o "$seed_dir/lsp_diag.o"
  fi
  else
  if [ ! -f "$seed_dir/lsp_diag_stubs_no_c.o" ] || [ "seeds/lsp_diag_stubs_no_c.from_x.c" -nt "$seed_dir/lsp_diag_stubs_no_c.o" ]; then
  strict_glue_info "cc -c $seed_dir/lsp_diag_stubs_no_c.o (E-02 soft-retire lsp_diag.c)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/lsp_diag_stubs_no_c.from_x.c -o "$seed_dir/lsp_diag_stubs_no_c.o"
  fi
  fi
}

ensure_diag_seed_obj() {
  local seed_dir="$1"
  if [ ! -f "$seed_dir/diag.o" ] || [ "seeds/diag.from_x.c" -nt "$seed_dir/diag.o" ] || [ "include/diag.h" -nt "$seed_dir/diag.o" ]; then
  strict_glue_info "cc -c $seed_dir/diag.o <- seeds/diag.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/diag.from_x.c -o "$seed_dir/diag.o"
  fi
}

# strict 链：自 build_asm/pipeline.o 导出除 impl/parse/typecheck 外符号，避免与 orchestration partial 重复。
ensure_pipeline_o_strict_link_partial_obj() {
  local PARTIAL SYMS PO WPO_E n_t
  PARTIAL="$BUILD_DIR/pipeline_strict_link_partial.o"
  SYMS="$BUILD_DIR/pipeline_strict_link_export.txt"
  PO="$BUILD_DIR/pipeline.o"
  WPO_E="$BUILD_DIR/pipeline_wpo.o"
  if [ ! -f "$PO" ] || [ ! -s "$PO" ]; then
  return 1
  fi
  # G.7: wave335+ pipeline.x is pure-extern (0 bodies). Live orch is
  # runtime_pipeline_abi (.o already on strict LD argv; pipeline_wpo dogfood).
  # Empty stub has 0 T → partial export is meaningless; do not hard-error.
  # PLATFORM: SHARED — Darwin and Linux tip both carry empty build_asm/pipeline.o.
  n_t=$(nm "$PO" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${n_t:-0}" -eq 0 ] && asm_pipeline_wpo_strict_reach_ok; then
  strict_glue_info "skip pipeline_strict_link_partial (pipeline.o 0 T pure-extern; WPO/abi covers)"
  rm -f "$PARTIAL" 2>/dev/null || true
  : >"$SYMS"
  return 1
  fi
  # X 编排：partial 不得再 export C 版 run_x_pipeline_*（runtime bootstrap 提供 pipeline_run_x_pipeline_impl）。
  pipeline_strict_link_export_syms_stale() {
  local syms="$1"
  local po="$2"
  [ -f "$syms" ] || return 0
  grep -qE '^(_)?preprocess_if_stack_|^(_)?backend_ctx_(push|pop)_loop_labels$|^(_)?backend_try_fold_count_up_while_elf$' "$syms" 2>/dev/null && return 0
  if asm_strict_x_orchestration_ok 2>/dev/null; then
  grep -qxF 'run_x_pipeline_impl' "$syms" 2>/dev/null && return 0
  grep -qxF 'run_x_pipeline_parse_entry_do_parse' "$syms" 2>/dev/null && return 0
  fi
  local n_po n_sym
  n_po=$(nm "$po" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  n_sym=$(wc -l <"$syms" | tr -d ' ')
  if [ "${n_po:-0}" -gt 80 ] 2>/dev/null && [ "${n_sym:-0}" -lt 40 ] 2>/dev/null; then
  grep -qxF 'run_x_pipeline_impl' "$syms" 2>/dev/null && return 0
  fi
  return 1
  }
  if pipeline_strict_link_export_syms_stale "$SYMS" "$PO"; then
  rm -f "$PARTIAL" "$SYMS"
  fi
  rebuild_pipeline_o_wpo_strict_helpers_if_needed || true
  # Stale: T-only export dropped X weak resolve_path_* (WPO bridge UNDEF).
  if [ -f "$SYMS" ] && ! grep -qxF 'pipeline_resolve_path_try_one_lib_root' "$SYMS" 2>/dev/null; then
  strict_glue_warn "stale pipeline_strict_link export (missing W resolve_path); regen"
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$0" -nt "$SYMS" ] || [ "$PO" -nt "$SYMS" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$SYMS" ]; } || \
  { [ -f "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" ] && [ "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" -nt "$SYMS" ]; }; then
  # PLATFORM: SHARED — pipeline.x emits resolve_path helpers as weak (W); bridge needs them.
  # T-only export dropped pipeline_resolve_path_try_one_lib_root → UNDEF from typecheck emit bridge.
  nm "$PO" 2>/dev/null | awk '/ [TW] / {print $3}' | grep -vE \
  '^(_)?(run_x_pipeline_(impl|parse_entry_do_parse|parse_entry_if_needed|typecheck_entry)|parse_into_with_init_buf|parse_into_with_init|pipeline_run_x_pipeline_impl|preprocess_if_stack_.*|backend_ctx_push_loop_labels|backend_ctx_pop_loop_labels|backend_try_fold_count_up_while_elf)$' \
  | sort -u >"$SYMS"
  if [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ] && asm_pipeline_wpo_strict_reach_ok; then
  if asm_pipeline_wpo_strict_link_full_ok; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_wpo_export_syms.txt"
  echo " pipeline_strict_link: minus full pipeline_wpo exports ($(wc -l <"$BUILD_DIR/.pipeline_wpo_export_syms.txt" | tr -d ' ') syms)"
  elif [ -f "$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt" ] && [ -s "$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt" ]; then
  cp -f "$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt" "$BUILD_DIR/.pipeline_wpo_export_syms.txt"
  elif [ -f "$WPO_E" ]; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_wpo_export_syms.txt"
  fi
  if [ -s "$BUILD_DIR/.pipeline_wpo_export_syms.txt" ]; then
  sort -u "$BUILD_DIR/.pipeline_wpo_export_syms.txt" -o "$BUILD_DIR/.pipeline_wpo_export_syms.txt"
  sort -u "$SYMS" -o "$SYMS"
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_wpo_export_syms.txt" >"$SYMS.wpo" 2>/dev/null && mv -f "$SYMS.wpo" "$SYMS"
  echo " pipeline_strict_link: minus pipeline_wpo exports ($(wc -l <"$BUILD_DIR/.pipeline_wpo_export_syms.txt" | tr -d ' ') syms)"
  fi
  fi
  if ensure_pipeline_glue_strict_minimal_export_syms_txt; then
  sort -u "$SYMS" -o "$SYMS"
  sort -u "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" -o "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt"
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" >"$SYMS.strict_minimal" 2>/dev/null \
  && mv -f "$SYMS.strict_minimal" "$SYMS"
  fi
  strict_glue_info "nm pipeline.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols T+W, minus parse/typecheck/impl entry)"
  fi
  if [ ! -s "$SYMS" ]; then
  # G.7: empty after WPO subtract is expected when pipeline.o is pure-extern stub
  # (or full overlap with pipeline_wpo). Soft-skip; abi/WPO covers orch.
  # PLATFORM: SHARED — was a hard error that aborted Darwin/Ubuntu tip dogfood.
  if asm_pipeline_wpo_strict_reach_ok || asm_strict_pipeline_selfhosted; then
  strict_glue_info "pipeline_strict_link 0 symbols after WPO subtract (pure-extern/overlap); skip partial"
  return 1
  fi
  strict_glue_error "pipeline_strict_link has 0 symbols after WPO subtract; cannot build partial"
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$PO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; } || \
  [ "seeds/pipeline_asm_orchestration_alias.from_x.c" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export $SYMS pipeline.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$PO" || return 1
  fi
  if [ -f "$PARTIAL" ] && [ -f "$BUILD_DIR/pipeline_wpo_helpers_partial.o" ] && \
  comm -12 <(nm "$PARTIAL" 2>/dev/null | awk '/ T / {print $3}' | sort -u) \
  <(nm "$BUILD_DIR/pipeline_wpo_helpers_partial.o" 2>/dev/null | awk '/ T / {print $3}' | sort -u) | grep -q .; then
  strict_glue_warn "pipeline_strict_link partial overlaps WPO helpers; rebuilding once"
  rm -f "$PARTIAL"
  strict_glue_info "ld partial export $SYMS pipeline.o -> $PARTIAL (retry)"
  ld_partial_export "$SYMS" "$PARTIAL" "$PO" || return 1
  fi
  return 0
}

# pipeline_wpo.o 编排链 reach：run_x_pipeline_impl 直接 callee 须已定义（与 build_xlang_asm.sh 一致）。
asm_pipeline_wpo_strict_reach_ok() {
  local po="$BUILD_DIR/pipeline_wpo.o"
  [ -f "$po" ] || return 1
  nm "$po" 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  nm "$po" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_typecheck_entry$' && return 1
  nm "$po" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_codegen_entry$' && return 1
  nm "$po" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_parse_entry_if_needed$' && return 1
  nm "$po" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_codegen_deps$' && return 1
  return 0
}

# track-only：链整颗 pipeline_wpo.o（X 编排）；默认 helpers + C orchestration。
asm_pipeline_wpo_strict_link_full_ok() {
  local po="$BUILD_DIR/pipeline_wpo.o"
  [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL:-0}" = "1" ] || return 1
  asm_pipeline_wpo_strict_reach_ok || return 1
  nm "$po" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$' || return 1
  return 0
}

# G.7 authority: runtime_pipeline_abi.o is the pipeline implementation (already on
# strict LD argv). pipeline.x is pure-extern; build_asm/pipeline.o is a 0-T stub.
# Must match build_xlang_asm.sh twin — checking the stub was a false residual.
# PLATFORM: SHARED.
asm_strict_pipeline_selfhosted() {
  local t
  t=$(asm_o_text_bytes src/runtime_pipeline_abi.o 2>/dev/null || echo 0)
  [ "$t" -ge 6144 ] 2>/dev/null || return 1
  nm -g src/runtime_pipeline_abi.o 2>/dev/null | grep -qE '(_)?path_append_from_buf_256|(_)?resolve_path_.*su' || return 1
  nm -g src/runtime_pipeline_abi.o 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  return 0
}

# X 编排（abi / pipeline_wpo）替代 C orchestration alias；与 build_xlang_asm.sh 对齐。
asm_strict_x_orchestration_ok() {
  local p_x_t=0
  [ "${XLANG_ASM_STRICT_C_ORCHESTRATION:-0}" = "1" ] && return 1
  [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ] || return 1
  if asm_strict_pipeline_selfhosted; then
  return 0
  fi
  # Fallback: pipeline_x.o companion when abi not yet selfhosted.
  [ -f pipeline_x.o ] || return 1
  p_x_t=$(asm_o_text_bytes pipeline_x.o 2>/dev/null || echo 0)
  [ "$p_x_t" -ge 6144 ] 2>/dev/null || return 1
  nm -g pipeline_x.o 2>/dev/null | grep -qE '(_)?path_append_from_buf_256|(_)?resolve_path_.*su' || return 1
  nm -g pipeline_x.o 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  return 0
}

# 自举 typeck + X 编排：glue 走 pipeline_x partial + glue_strict_minimal（勿 glue_standalone 双 astpool）。
asm_strict_typeck_x_glue_via_pipeline_x() {
  asm_strict_typeck_selfhosted || return 1
  asm_strict_x_orchestration_ok || return 1
  return 0
}

# pipeline_x.o freshness (G.7 single authority; twin of build_xlang_asm.sh).
# PLATFORM: SHARED — after wave335 / 8.3 leave, ast_pool.c and pipeline_glue.c are
# absent; dead -nt on those paths never fired. pipeline_x.o producer =
# src/pipeline/pipeline.x via try-gen-x — NOT runtime_pipeline_abi.x (abi freshness
# is ensure_experimental_ast_pool_for_wpo / runtime_pipeline_abi.o). Authority =
# PIPELINE_X_DEPS only; do not retarget to abi (forever need=1 on stub .o).
ensure_pipeline_x_o_fresh() {
  local need=0
  if [ ! -f pipeline_x.o ] || [ ! -f pipeline_gen.c ]; then
  need=1
  fi
  # (Deleted ast_pool.c / pipeline_glue.c -nt removed — never fired post-leave.)
  for dep in \
  src/pipeline/pipeline.x src/codegen/codegen.x src/typeck/typeck.x src/parser/parser.x \
  src/ast/ast.x src/lexer/lexer.x src/preprocess/preprocess.x src/asm/asm.x \
  src/asm/backend.x src/asm/platform/elf.x src/asm/arch/arm64.x src/asm/arch/arm64_enc.x; do
  if [ -f "$dep" ] && [ "$dep" -nt "pipeline_x.o" ]; then
  need=1
  break
  fi
  done
  if [ "$need" -eq 1 ]; then
  # PLATFORM: SHARED — post-Makefile phys-del: rebuild pipeline_x.o via try-heat
  # (twin of build_xlang_asm wave929 / xlang_x_pipeline wave947). Ban bare make.
  # Escape: XLANG_STRICT_GLUE_VIA_MAKE=1 + Makefile → historic bootstrap-pipeline.
  strict_glue_info "rebuild pipeline_x.o (PIPELINE_X_DEPS newer; 0-make try-heat)"
  if [ "${XLANG_STRICT_GLUE_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ]; then
    make bootstrap-pipeline pipeline_x.o || return 1
  else
    PIPELINE_X_FORCE_COMPILE=1 bash scripts/ensure_host_cc_seed_o.sh try-heat pipeline_x.o \
      || { strict_glue_error "try-heat pipeline_x.o failed (ensure_pipeline_x_o_fresh)"; return 1; }
  fi
  fi
  if [ -f pipeline_x.o ]; then
  # PLATFORM: SHARED — re-promote when pipeline.o missing, older, or reduced to WPO-helpers-only
  # (few T / bare resolve_path_*) after a prior dogfood overwrite of full pipeline_x.
  _need_promote=0
  if [ ! -f "$BUILD_DIR/pipeline.o" ] || [ "pipeline_x.o" -nt "$BUILD_DIR/pipeline.o" ]; then
  _need_promote=1
  else
  _po_t=$(nm "$BUILD_DIR/pipeline.o" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  _px_t=$(nm pipeline_x.o 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${_px_t:-0}" -gt 80 ] 2>/dev/null && [ "${_po_t:-0}" -lt 80 ] 2>/dev/null; then
  _need_promote=1
  fi
  fi
  if [ "$_need_promote" -eq 1 ]; then
  strict_glue_info "promote pipeline_x.o -> $BUILD_DIR/pipeline.o"
  cp -f pipeline_x.o "$BUILD_DIR/pipeline.o"
  rm -f "$BUILD_DIR/pipeline_strict_link_partial.o" "$BUILD_DIR/pipeline_strict_link_export.txt" 2>/dev/null || true
  fi
  mkdir -p "$BUILD_DIR/gen_driver"
  cp -f pipeline_x.o "$BUILD_DIR/gen_driver/pipeline_x.o"
  fi
}

# strict 回退：从 pipeline_x.o 部分链接 pipeline_run_x_pipeline_impl（与 experimental X 编排一致）。
# G.7: when runtime_pipeline_abi.o is selfhosted (already on strict LD argv), skip —
# pipeline_x.o is a pure-extern stub (0 T); ld -r for _pipeline_run_x_pipeline_impl UNDEFs.
# PLATFORM: SHARED — twin of build_xlang_asm.sh.
ensure_pipeline_runtime_bootstrap_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_pipeline_selfhosted; then
  strict_glue_info "skip pipeline_runtime_bootstrap_partial (runtime_pipeline_abi on LD argv)"
  rm -f "$PARTIAL" 2>/dev/null || true
  return 1
  fi
  SYMS="$BUILD_DIR/pipeline_runtime_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  strict_glue_error "missing $SUO; run build_xlang_asm once"
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  printf '%s\n' '_pipeline_run_x_pipeline_impl' > "$SYMS"
  strict_glue_info "ld partial export $SYMS pipeline_x.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" || return 1
  fi
  return 0
}

# strict X 编排：从 pipeline_x.o 导出 glue/astpool 桥接；替代 glue_standalone 避免双 astpool SIGSEGV。
ensure_pipeline_x_glue_support_partial_obj() {
  local PARTIAL SYMS SUO TCK_SYMS
  PARTIAL="$BUILD_DIR/pipeline_x_glue_support_partial.o"
  SYMS="$BUILD_DIR/pipeline_x_glue_support_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  TCK_SYMS="$BUILD_DIR/typeck_strict_link_export.txt"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  strict_glue_error "missing $SUO; run build_xlang_asm once"
  return 1
  fi
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -f typeck_x.o ]; then
  nm typeck_x.o 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.typeck_x_all_t.txt"
  TCK_SYMS="$BUILD_DIR/.typeck_x_all_t.txt"
  else
  ensure_typeck_o_strict_link_partial_obj || true
  TCK_SYMS="$BUILD_DIR/typeck_strict_link_export.txt"
  fi
  if [ ! -f "$SYMS" ] || [ "$0" -nt "$SYMS" ] || [ "$SUO" -nt "$SYMS" ] || \
  { [ -f "$TCK_SYMS" ] && [ "$TCK_SYMS" -nt "$SYMS" ]; } || \
  { [ -f "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" ] && [ "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" -nt "$SYMS" ]; } || \
  { [ -f "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" ] && [ "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" -nt "$SYMS" ]; }; then
  ensure_pipeline_glue_standalone_export_syms_txt || return 1
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  ensure_pipeline_glue_strict_minimal_export_syms_txt || true
  fi
  nm "$SUO" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_x_all_t.txt"
  comm -12 "$BUILD_DIR/.pipeline_x_all_t.txt" "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" \
  >"$BUILD_DIR/.pipeline_x_glue_common.txt" 2>/dev/null || return 1
  : >"$SYMS"
  while IFS= read -r sym || [ -n "$sym" ]; do
  [ -z "$sym" ] && continue
  case "$sym" in
  _pipeline_run_x_pipeline_impl|pipeline_run_x_pipeline_impl|_run_x_pipeline_impl|run_x_pipeline_impl)
  continue
  ;;
  _preprocess_if_stack_*|preprocess_if_stack_*|_backend_ctx_push_loop_labels|backend_ctx_push_loop_labels|_backend_ctx_pop_loop_labels|backend_ctx_pop_loop_labels|_backend_try_fold_count_up_while_elf|backend_try_fold_count_up_while_elf)
  continue
  ;;
  _typeck_x_ast|typeck_x_ast|_typeck_x_ast_library|typeck_x_ast_library|_check_block|check_block|_check_expr|check_expr|_check_block_*|check_block_*|_check_expr_*|check_expr_*|_typeck_check_*|typeck_check_*)
  continue
  ;;
  esac
  if [ -f "$TCK_SYMS" ] && grep -qxF "$sym" "$TCK_SYMS" 2>/dev/null; then
  continue
  fi
  PIPE_SYMS="$BUILD_DIR/pipeline_strict_link_export.txt"
  if [ -f "$PIPE_SYMS" ] && grep -qxF "$sym" "$PIPE_SYMS" 2>/dev/null; then
  continue
  fi
  printf '%s\n' "$sym" >>"$SYMS"
  done <"$BUILD_DIR/.pipeline_x_glue_common.txt"
  sort -u "$SYMS" -o "$SYMS"
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -s "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" ]; then
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt" >"$SYMS.strict_minimal" 2>/dev/null \
  && mv -f "$SYMS.strict_minimal" "$SYMS"
  fi
  for sym in _pipeline_load_and_sync_direct_import_deps _pipeline_run_x_pipeline_fill_dep_import_path; do
  if [ -f "$PIPE_SYMS" ] && grep -qxF "$sym" "$PIPE_SYMS" 2>/dev/null; then
  continue
  fi
  grep -qxF "$sym" "$SYMS" 2>/dev/null || printf '%s\n' "$sym" >>"$SYMS"
  done
  strict_glue_info "pipeline_x glue support: $(wc -l <"$SYMS" | tr -d ' ') syms"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export $SYMS pipeline_x.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" || return 1
  fi
  return 0
}

ensure_asm_pipeline_run_impl_alias_obj() {
  local ALIAS_OBJ="$BUILD_DIR/pipeline_run_impl_alias.o"
  local ALIAS_CFLAGS="$CFLAGS"
  if asm_strict_x_orchestration_ok; then
  ALIAS_CFLAGS="$CFLAGS -DXLANG_PIPELINE_RUN_IMPL_ALIAS_PARSE_ALIASES=0"
  fi
  if [ ! -f "$ALIAS_OBJ" ] || [ "seeds/pipeline_run_impl_alias.from_x.c" -nt "$ALIAS_OBJ" ] || \
  [ ! -f "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" ] || \
  { asm_strict_x_orchestration_ok && [ "$(cat "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" 2>/dev/null)" != "1" ]; } || \
  { ! asm_strict_x_orchestration_ok && [ "$(cat "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" 2>/dev/null)" = "1" ]; }; then
  strict_glue_info "cc -c seeds/pipeline_run_impl_alias.from_x.c -> $ALIAS_OBJ (X orch=$(asm_strict_x_orchestration_ok && echo 1 || echo 0))"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_impl_alias.from_x.c "$ALIAS_OBJ"
  if asm_strict_x_orchestration_ok; then echo "1" >"$BUILD_DIR/.pipeline_run_impl_alias_x_orch"; else echo "0" >"$BUILD_DIR/.pipeline_run_impl_alias_x_orch"; fi
  fi
}

# WPO helpers 导出排除表：mega entry + check_* 须由 typeck.o 全量提供（WPO 版内联压缩 check_block 会 SIGSEGV）。
typeck_wpo_helpers_export_exclude_re() {
  echo '^(check_block|check_expr|typeck_x_ast|typeck_x_ast_library)$'
}

# strict WPO：从 typeck_wpo.o 仅导出 layout/unify helper；entry/check_* 仍由 typeck.o 全量提供。
ensure_typeck_wpo_helpers_partial_obj() {
  local PARTIAL SYMS WPO_E EXCLUDE_RE
  PARTIAL="$BUILD_DIR/typeck_wpo_helpers_partial.o"
  SYMS="$BUILD_DIR/typeck_wpo_helpers_export.txt"
  WPO_E="$BUILD_DIR/typeck_wpo.o"
  EXCLUDE_RE=$(typeck_wpo_helpers_export_exclude_re)
  if [ ! -f "$WPO_E" ] || [ ! -s "$WPO_E" ]; then
  return 1
  fi
  if ! asm_typeck_wpo_strict_reach_ok; then
  return 1
  fi
  if [ -f "$PARTIAL" ]; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' && rm -f "$PARTIAL" "$SYMS"
  fi
  if [ ! -f "$SYMS" ] || [ "$WPO_E" -nt "$SYMS" ]; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | grep -vE "$EXCLUDE_RE" >"$SYMS"
  strict_glue_info "nm typeck_wpo.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') layout syms, minus check_block/check_expr/typeck_x_ast*)"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$WPO_E" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export $SYMS typeck_wpo.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$WPO_E" || return 1
  nm "$PARTIAL" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt"
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' && {
  strict_glue_error "typeck_wpo_helpers_partial must not export typeck_x_ast"
  return 1
  }
  fi
  return 0
}

# WPO strict partial 导出表是否过期：旧缓存曾误删 check_block callee 或误含 WPO typeck_x_ast。
typeck_wpo_strict_partial_export_syms_stale() {
  local syms="$1"
  [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] || return 1
  asm_typeck_wpo_strict_reach_ok || return 1
  [ -f "$syms" ] || return 0
  grep -qxF 'typeck_check_block_one_while' "$syms" 2>/dev/null || return 0
  grep -qxF 'check_block_as_loop_body' "$syms" 2>/dev/null || return 0
  grep -qxF 'typeck_x_ast' "$syms" 2>/dev/null && return 0
  if [ -f "$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt" ] && \
  grep -qxF 'typeck_x_ast' "$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt" 2>/dev/null; then
  return 0
  fi
  return 1
}

# pipeline_glue_standalone.o 全局 T 导出表：与 build_asm/typeck.o 并列链时会 duplicate ast_pool/glue → fill_cl SIGSEGV。
# PLATFORM: SHARED — freshness authority = GLUE_O only (deleted pipeline_glue.c -nt never fired).
ensure_pipeline_glue_standalone_export_syms_txt() {
  local GLUE_O="$BUILD_DIR/pipeline_glue_standalone.o"
  local OUT="$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt"
  [ -f "$GLUE_O" ] || return 1
  if [ ! -f "$OUT" ] || [ "$GLUE_O" -nt "$OUT" ]; then
  nm "$GLUE_O" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$OUT"
  fi
  [ -s "$OUT" ] || return 1
  return 0
}

ensure_pipeline_glue_strict_minimal_export_syms_txt() {
  local GLUE_O="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  local OUT="$BUILD_DIR/.pipeline_glue_strict_minimal_export_syms.txt"
  [ -f "$GLUE_O" ] || return 1
  if [ ! -f "$OUT" ] || [ "$GLUE_O" -nt "$OUT" ] || [ "seeds/pipeline_glue_strict_minimal.from_x.c" -nt "$OUT" ]; then
  nm "$GLUE_O" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$OUT"
  fi
  [ -s "$OUT" ] || return 1
  return 0
}

# strict 链：自 build_asm/typeck.o 导出除 WPO 已定义外符号。
ensure_typeck_o_strict_link_partial_obj() {
  local PARTIAL SYMS TCKO WPO_E GLUE_O
  PARTIAL="$BUILD_DIR/typeck_strict_link_partial.o"
  SYMS="$BUILD_DIR/typeck_strict_link_export.txt"
  TCKO="$BUILD_DIR/typeck.o"
  WPO_E="$BUILD_DIR/typeck_wpo.o"
  GLUE_O="$BUILD_DIR/pipeline_glue_standalone.o"
  if [ ! -f "$TCKO" ] || [ ! -s "$TCKO" ]; then
  return 1
  fi
  if typeck_wpo_strict_partial_export_syms_stale "$SYMS"; then
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ -f "$PARTIAL" ] && [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] && asm_typeck_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_check_block_one_while$' || rm -f "$PARTIAL"
  fi
  if [ -f "$PARTIAL" ] && [ -f "$GLUE_O" ] && [ "$GLUE_O" -nt "$PARTIAL" ]; then
  rm -f "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$TCKO" -nt "$SYMS" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$SYMS" ]; } || \
  { [ -f "$GLUE_O" ] && [ "$GLUE_O" -nt "$SYMS" ]; }; then
  nm "$TCKO" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$SYMS"
  if [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] && [ -f "$WPO_E" ] && asm_typeck_wpo_strict_reach_ok && asm_typeck_wpo_strict_link_helpers_ok; then
  if [ -f "$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt" ] && [ -s "$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt" ]; then
  cp -f "$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt" "$BUILD_DIR/.typeck_wpo_export_syms.txt"
  else
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | grep -vE "$(typeck_wpo_helpers_export_exclude_re)" | sort -u >"$BUILD_DIR/.typeck_wpo_export_syms.txt"
  fi
  if [ -s "$BUILD_DIR/.typeck_wpo_export_syms.txt" ]; then
  sort -u "$BUILD_DIR/.typeck_wpo_export_syms.txt" -o "$BUILD_DIR/.typeck_wpo_export_syms.txt"
  comm -23 "$SYMS" "$BUILD_DIR/.typeck_wpo_export_syms.txt" >"$SYMS.wpo" 2>/dev/null && mv -f "$SYMS.wpo" "$SYMS"
  echo " typeck_strict_link: minus typeck_wpo layout exports ($(wc -l <"$BUILD_DIR/.typeck_wpo_export_syms.txt" | tr -d ' ') syms, keep check_block/typeck_x_ast from typeck.o)"
  fi
  fi
  if ensure_pipeline_glue_standalone_export_syms_txt; then
  sort -u "$SYMS" -o "$SYMS"
  comm -12 "$SYMS" "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" >"$BUILD_DIR/.typeck_glue_dup_syms.txt" 2>/dev/null || true
  if [ -s "$BUILD_DIR/.typeck_glue_dup_syms.txt" ]; then
  comm -23 "$SYMS" "$BUILD_DIR/.typeck_glue_dup_syms.txt" >"$SYMS.glue" 2>/dev/null && mv -f "$SYMS.glue" "$SYMS"
  echo " typeck_strict_link: minus typeck∩glue duplicate exports ($(wc -l <"$BUILD_DIR/.typeck_glue_dup_syms.txt" | tr -d ' ') syms, glue_standalone owns ast_pool)"
  fi
  fi
  strict_glue_info "nm typeck.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$TCKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; } || \
  { [ -f "$GLUE_O" ] && [ "$GLUE_O" -nt "$PARTIAL" ]; }; then
  strict_glue_info "ld partial export $SYMS typeck.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$TCKO" || return 1
  if [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] && asm_typeck_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_check_block_one_while$' || {
  strict_glue_error "typeck_strict_link_partial missing typeck_check_block_one_while"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?check_block_as_loop_body$' || {
  strict_glue_error "typeck_strict_link_partial missing check_block_as_loop_body"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?check_block$' || {
  strict_glue_error "typeck_strict_link_partial missing check_block"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' || {
  strict_glue_error "typeck_strict_link_partial missing typeck_x_ast"
  return 1
  }
  fi
  fi
  return 0
}

# typeck_wpo.o WPO reach：typeck_x_ast / check_block / check_expr 须在 TU 内定义。
asm_typeck_wpo_strict_reach_ok() {
  local to="$BUILD_DIR/typeck_wpo.o"
  [ -f "$to" ] || return 1
  nm "$to" 2>/dev/null | grep -qE '(_)?typeck_x_ast' || return 1
  nm "$to" 2>/dev/null | grep -qE ' U (_)?typeck_x_ast$' && return 1
  nm "$to" 2>/dev/null | grep -qE ' U (_)?check_block$' && return 1
  nm "$to" 2>/dev/null | grep -qE ' U (_)?check_expr$' && return 1
  nm "$to" 2>/dev/null | grep -qE ' T (_)?check_block' || return 1
  nm "$to" 2>/dev/null | grep -qE ' T (_)?check_expr' || return 1
  return 0
}

# typeck_wpo helpers partial 仅于 typeck.o 未自举时链入；自举后 wpo partial 会带入内联 check_block 局部符号。
asm_typeck_wpo_strict_link_helpers_ok() {
  [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] || return 1
  asm_typeck_wpo_strict_reach_ok || return 1
  asm_strict_typeck_selfhosted && return 1
  return 0
}

# backend_wpo.o WPO reach：asm_codegen_ast / emit_expr_elf / emit_block_body_elf 须在 TU 内定义。
asm_backend_wpo_strict_reach_ok() {
  local bo="$BUILD_DIR/backend_wpo.o"
  [ -f "$bo" ] || return 1
  nm "$bo" 2>/dev/null | grep -qE ' T (_)?asm_codegen_ast$' || return 1
  nm "$bo" 2>/dev/null | grep -qE ' U (_)?asm_codegen_ast$' && return 1
  nm "$bo" 2>/dev/null | grep -qE ' T (_)?emit_expr_elf' || return 1
  nm "$bo" 2>/dev/null | grep -qE ' T (_)?emit_block_body_elf' || return 1
  return 0
}

asm_strict_backend_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/backend.o" 2>/dev/null || echo 0)
  [ "$t" -gt 1024 ] 2>/dev/null
}

ensure_backend_asm_bare_link_alias_obj() {
  local ALIAS_O="$BUILD_DIR/backend_asm_bare_link_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ seeds/backend_asm_bare_link_alias.from_x.c -nt "$ALIAS_O" ]; then
  strict_glue_info "cc -c seeds/backend_asm_bare_link_alias.from_x.c -> $ALIAS_O"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$ALIAS_O" seeds/backend_asm_bare_link_alias.from_x.c
  fi
}

ensure_asm_backend_seed_helper_partial_obj() {
  local PARTIAL SYMS SEED EXCLUDE
  PARTIAL="$BUILD_DIR/asm_backend_seed_helper_partial.o"
  SYMS="$BUILD_DIR/asm_backend_seed_helper_export.txt"
  EXCLUDE="$BUILD_DIR/asm_backend_seed_helper_exclude.txt"
  SEED="$BUILD_DIR/seed_host/asm_backend_partial.o"
  if [ ! -f "$SEED" ] || [ ! -s "$SEED" ]; then
  return 1
  fi
  # Stale: older helper exports were T-only and dropped seed W text stubs
  # (backend_emit_expr / loop_body / if_then) → strict WPO final link UNDEF.
  if [ -f "$SYMS" ] && ! grep -qxF 'backend_emit_expr' "$SYMS" 2>/dev/null; then
  strict_glue_warn "stale asm_backend_seed_helper export (missing W text stubs); regen"
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$SEED" -nt "$SYMS" ] || [ ! -f "$EXCLUDE" ] || [ "$EXCLUDE" -nt "$SYMS" ]; then
  cat >"$EXCLUDE" <<'EOF'
backend_asm_codegen_ast
backend_asm_codegen_ast_to_elf
backend_emit_expr_elf
backend_emit_block_body_elf
EOF
  # PLATFORM: SHARED — seed pin keeps text-path emit helpers as weak (W) stubs;
  # WPO path replaces only thin T entrypoints. Must export T+W or compat_stubs
  # UNDEFs backend_emit_expr / loop_body / if_then under STRICT_LINK_BUILD_ASM_BACKEND_WPO.
  nm "$SEED" 2>/dev/null | awk '/ [TW] / {print $3}' | sort -u >"$SYMS.all"
  sort -u "$EXCLUDE" -o "$EXCLUDE"
  comm -23 "$SYMS.all" "$EXCLUDE" >"$SYMS"
  rm -f "$SYMS.all"
  strict_glue_info "seed helper export: $(wc -l <"$SYMS" | tr -d ' ') symbols (seed T+W minus wpo thin entry)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SEED" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export $SYMS seed asm_backend_partial.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SEED" || return 1
  fi
  return 0
}

ensure_asm_backend_platform_writer_partial_obj() {
  local PARTIAL SYMS SEED
  PARTIAL="$BUILD_DIR/asm_backend_platform_writer_partial.o"
  SYMS="$BUILD_DIR/asm_backend_platform_writer_export.txt"
  SEED="$BUILD_DIR/seed_host/asm_backend_partial.o"
  if [ ! -f "$SEED" ] || [ ! -s "$SEED" ]; then
  return 1
  fi
  if [ ! -f "$SYMS" ] || [ "$SEED" -nt "$SYMS" ]; then
  : >"$SYMS"
  case "$(uname -s 2>/dev/null)" in
  Darwin)
  printf '%s\n' "_platform_macho_write_macho_o_to_buf" >>"$SYMS"
  ;;
  MINGW*|MSYS*|CYGWIN*|Windows_NT)
  printf '%s\n' "_platform_coff_write_coff_o_to_buf" >>"$SYMS"
  ;;
  esac
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$SEED" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  strict_glue_info "ld partial export $SYMS seed asm_backend_partial.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SEED" || return 1
  fi
  return 0
}

backend_wpo_strict_partial_export_syms_stale() {
  local syms="$1"
  [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] || return 1
  asm_backend_wpo_strict_reach_ok || return 1
  [ -f "$syms" ] || return 0
  grep -qxF 'arch_emit_add_imm_to_rax' "$syms" 2>/dev/null || return 0
  grep -qxF 'asm_codegen_ast_seed_mega' "$syms" 2>/dev/null && return 0
  return 1
}

ensure_backend_o_strict_link_partial_obj() {
  local PARTIAL SYMS BACKO WPO_E
  PARTIAL="$BUILD_DIR/backend_strict_link_partial.o"
  SYMS="$BUILD_DIR/backend_strict_link_export.txt"
  BACKO="$BUILD_DIR/backend.o"
  WPO_E="$BUILD_DIR/backend_wpo.o"
  if [ ! -f "$BACKO" ] || [ ! -s "$BACKO" ]; then
  return 1
  fi
  if backend_wpo_strict_partial_export_syms_stale "$SYMS"; then
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ -f "$PARTIAL" ] && [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?arch_emit_add_imm_to_rax$' || rm -f "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$BACKO" -nt "$SYMS" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$SYMS" ]; }; then
  nm "$BACKO" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$SYMS"
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && [ -f "$WPO_E" ] && asm_backend_wpo_strict_reach_ok; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.backend_wpo_export_syms.txt"
  if [ -s "$BUILD_DIR/.backend_wpo_export_syms.txt" ]; then
  sort -u "$BUILD_DIR/.backend_wpo_export_syms.txt" -o "$BUILD_DIR/.backend_wpo_export_syms.txt"
  comm -23 "$SYMS" "$BUILD_DIR/.backend_wpo_export_syms.txt" >"$SYMS.wpo" 2>/dev/null && mv -f "$SYMS.wpo" "$SYMS"
  strict_glue_info "backend_strict_link: minus backend_wpo.o exports ($(wc -l <"$BUILD_DIR/.backend_wpo_export_syms.txt" | tr -d ' ') syms)"
  fi
  grep -vxF 'asm_codegen_ast_seed_mega' "$SYMS" >"$SYMS.nmega" 2>/dev/null && mv -f "$SYMS.nmega" "$SYMS"
  grep -vxF 'asm_codegen_ast_to_elf_seed_mega' "$SYMS" >"$SYMS.nmega2" 2>/dev/null && mv -f "$SYMS.nmega2" "$SYMS"
  fi
  strict_glue_info "nm backend.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$BACKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; }; then
  strict_glue_info "ld partial export $SYMS backend.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$BACKO" || return 1
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?arch_emit_add_imm_to_rax$' || {
  strict_glue_error "backend_strict_link_partial missing arch_emit_add_imm_to_rax"
  return 1
  }
  fi
  fi
  return 0
}

ensure_asm_backend_compat_stubs_obj() {
  local STUB_O="$BUILD_DIR/asm_backend_compat_stubs.o"
  if [ ! -f "$STUB_O" ] || [ seeds/asm_backend_compat_stubs.from_x.c -nt "$STUB_O" ]; then
  strict_glue_info "cc -c seeds/asm_backend_compat_stubs.from_x.c -> $STUB_O"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/asm_backend_compat_stubs.from_x.c -o "$STUB_O"
  fi
}

# 与 build_xlang_asm.sh 一致：pipeline_glue_standalone 引用 simd_enc / simd_loop / target_cpu。
# PLATFORM: SHARED — G-02e: f32 xmm ABI folded into backend_call_dispatch (no pipeline_abi_f32_xmm.c).
ensure_simd_glue_link_objs() {
  if [ ! -f src/asm/backend_call_dispatch.o ] || [ seeds/backend_call_dispatch.from_x.c -nt src/asm/backend_call_dispatch.o ]; then
  strict_glue_info "cc -c seeds/backend_call_dispatch.from_x.c -> src/asm/backend_call_dispatch.o (G-02e f32 xmm)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/backend_call_dispatch.from_x.c -o src/asm/backend_call_dispatch.o
  fi
  if [ ! -f src/driver/target_cpu.o ] || [ seeds/target_cpu_pure.from_x.c -nt src/driver/target_cpu.o ]; then
  strict_glue_info "cc -c seeds/target_cpu_pure.from_x.c -> src/driver/target_cpu.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/target_cpu_pure.from_x.c -o src/driver/target_cpu.o
  fi
  if [ ! -f src/asm/simd_enc.o ] || [ seeds/simd_enc.from_x.c -nt src/asm/simd_enc.o ]; then
  strict_glue_info "cc -c seeds/simd_enc.from_x.c -> src/asm/simd_enc.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/simd_enc.from_x.c -o src/asm/simd_enc.o
  fi
  if [ ! -f src/asm/simd_loop.o ] || [ seeds/simd_loop.from_x.c -nt src/asm/simd_loop.o ]; then
  strict_glue_info "cc -c seeds/simd_loop.from_x.c -> src/asm/simd_loop.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/simd_loop.from_x.c -o src/asm/simd_loop.o
  fi
}

strict_asm_backend_companion_objs() {
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  ensure_backend_asm_bare_link_alias_obj >&2 || return 1
  ensure_asm_backend_seed_helper_partial_obj >&2 || return 1
  printf '%s\n' "$BUILD_DIR/backend_wpo.o $BUILD_DIR/backend_asm_bare_link_alias.o $BUILD_DIR/asm_backend_seed_helper_partial.o"
  return 0
  fi
  printf '%s\n' "$BUILD_DIR/seed_host/asm_backend_partial.o"
  return 0
}

# Linux reach OK 时默认链 pipeline_wpo FULL；显式 XLANG_ASM_STRICT_LINK_PIPELINE_WPO=0 关闭。
# Darwin：亦默认开 WPO；FULL 默认 0（abi 已在 LD argv，整颗 pipeline_wpo 与 abi 双权威重叠；
# helpers ld -r 在 Darwin multi-LC_SEGMENT / Ubuntu 内部 strchr multi-def 上仍软残 → abi 覆盖）。
# PLATFORM: SHARED default enable; MACOS soft FULL=0 residual documented.
maybe_default_pipeline_wpo_strict_link() {
  if [ -n "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO+x}" ]; then
  return 0
  fi
  case "$(uname -s)-$(uname -m 2>/dev/null)" in
  Linux-x86_64|Linux-amd64|Linux-aarch64|Linux-arm64|Darwin-arm64|Darwin-x86_64)
  if asm_pipeline_wpo_strict_reach_ok; then
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL:-1}" = "0" ]; then
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL=0
  strict_glue_info "default XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 (helpers; abi covers orch)"
  else
  # Prefer helpers when abi already selfhosted (avoid dual-authority FULL+abi).
  if asm_strict_pipeline_selfhosted; then
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL=0
  strict_glue_info "default XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 helpers (abi on LD argv; skip FULL dual)"
  else
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL=1
  strict_glue_info "default XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 + FULL=1"
  fi
  fi
  fi
  ;;
  esac
}

# 默认 C orchestration；XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 且 reach OK 才链 pipeline_wpo helpers。
maybe_default_pipeline_wpo_strict_link
if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && [ "${STRICT_LINK_BUILD_ASM_WPO:-}" != "0" ] && asm_pipeline_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_WPO=1
  strict_glue_info "STRICT_LINK_BUILD_ASM_WPO=1 (pipeline_wpo.o opt-in)"
else
  export STRICT_LINK_BUILD_ASM_WPO=0
fi
if [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-}" != "0" ] && asm_typeck_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_TYPECK_WPO=1
  strict_glue_info "STRICT_LINK_BUILD_ASM_TYPECK_WPO=1 (typeck_wpo reach OK; helpers only if typeck.o not selfhosted)"
else
  export STRICT_LINK_BUILD_ASM_TYPECK_WPO=0
fi
if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-}" != "0" ] && asm_backend_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_BACKEND_WPO=1
  strict_glue_info "STRICT_LINK_BUILD_ASM_BACKEND_WPO=1 (backend_wpo.o reach OK)"
fi

# WPO strict 链：pipeline_wpo.o 依赖 resolve_path_* 等 helper；CI 跳过 pipeline second pass 时 build_asm/pipeline.o 与 wpo 符号重叠、partial 为空。
# PLATFORM: SHARED — do NOT overwrite a full selfhosted pipeline.o (pipeline_x promote, often 1000+ T
# symbols with pipeline_resolve_path_* names) with a WPO-helpers-only object. Bare resolve_path_* live
# in pipeline_wpo.o / helpers partial; overwriting full pipeline.o made strict_link residual 0 after
# WPO subtract (Stage2 WPO 2h tip L4 residual after Cap pure).
# G.7: live orch source is runtime_pipeline_abi.x (pipeline.x pure-extern). Prefer EMIT_HEAVY=0.
rebuild_pipeline_o_wpo_strict_helpers_if_needed() {
  local po="$BUILD_DIR/pipeline.o"
  local comp tmp pt n_t src heavy
  [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ] || return 0
  asm_pipeline_wpo_strict_reach_ok || return 0
  [ -f "$po" ] || return 1
  n_t=$(nm "$po" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${n_t:-0}" -gt 80 ] 2>/dev/null; then
  strict_glue_info "pipeline.o already full (T=${n_t}); WPO helpers from pipeline_wpo.o only"
  return 0
  fi
  if nm "$po" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$'; then
  return 0
  fi
  # Empty pure-extern stub + pipeline_wpo already has resolve → nothing to rebuild.
  if [ "${n_t:-0}" -eq 0 ] && \
  nm "$BUILD_DIR/pipeline_wpo.o" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$'; then
  strict_glue_info "skip pipeline.o rebuild (0 T stub; pipeline_wpo has resolve_path)"
  return 0
  fi
  src="${XLANG_WPO_PIPELINE_SRC:-src/runtime_pipeline_abi.x}"
  tmp="$BUILD_DIR/pipeline.wpo_strict_helpers.o"
  for heavy in 0 1; do
  for comp in ./xlang_asm.experimental ./xlang_asm ./xlang ./xlang-x; do
  [ -x "$comp" ] || continue
  strict_glue_info "rebuild pipeline.o from $src (EMIT_HEAVY=$heavy) via $comp"
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  rm -f "$tmp" 2>/dev/null || true
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$heavy" XLANG_ASM_WPO_DCE=0 \
  "$comp" -backend asm -o "$tmp" -L asm_libroot -L .. -L src \
  "$src" 2>/dev/null; then
  pt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  if [ "$pt" -gt 512 ] 2>/dev/null \
  && nm "$tmp" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$'; then
  mv -f "$tmp" "$po"
  rm -f "$BUILD_DIR/pipeline_strict_link_partial.o" "$BUILD_DIR/pipeline_strict_link_export.txt" 2>/dev/null || true
  strict_glue_info "pipeline.o WPO helpers OK (__text=${pt}B, src=$(basename "$src"), heavy=$heavy)"
  return 0
  fi
  fi
  rm -f "$tmp" 2>/dev/null || true
  done
  done
  strict_glue_warn "pipeline.o WPO helper rebuild failed"
  return 1
}

# S5 WPO strict 链：pipeline_wpo.o + glue 入口/typecheck emit 别名（替代 C orchestration partial）。
ensure_pipeline_wpo_strict_link_alias_obj() {
  local ALIAS_O="$BUILD_DIR/pipeline_wpo_strict_link_alias.o"
  local ALIAS_SRC="seeds/pipeline_wpo_strict_link_alias.from_x.c"
  if [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -ne 1 ] || ! asm_pipeline_wpo_strict_reach_ok; then
  return 0
  fi
  # 7.2.1 seventh knife: .x authority via cc_inc_tu --auto prefer lane.
  if [ -x ./xlang_asm ] || [ -x ./xlang ] || [ -x ./xlang-c ]; then
    if [ ! -f "$ALIAS_O" ] || [ src/pipeline_wpo_strict_link_alias.x -nt "$ALIAS_O" ] \
       || { [ -f "$ALIAS_SRC" ] && [ "$ALIAS_SRC" -nt "$ALIAS_O" ]; }; then
      strict_glue_info "cc_inc_tu --auto (src/pipeline_wpo_strict_link_alias.x) -> $ALIAS_O"
      sh scripts/cc_inc_tu.sh --auto "$ALIAS_O" || return 1
    fi
    return 0
  fi
  if [ ! -f "$ALIAS_SRC" ]; then
  return 1
  fi
  if [ ! -f "$ALIAS_O" ] || [ "$ALIAS_SRC" -nt "$ALIAS_O" ]; then
  strict_glue_info "cc_inc_tu $ALIAS_SRC -> $ALIAS_O (WPO strict link alias)"
  sh scripts/cc_inc_tu.sh "$ALIAS_SRC" "$ALIAS_O" || return 1
  fi
  return 0
}

# Glue companion detect + optional archaeology standalone (seed retired wave309).
detect_gen() {
  PIPELINE_GEN_CFLAGS="-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-parentheses -Wno-sign-compare -Wno-ignored-qualifiers -Wno-unused-but-set-variable -Wno-type-limits"
  case "$(uname -s)" in
  Darwin) PIPELINE_GEN_CFLAGS="$PIPELINE_GEN_CFLAGS -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses -Wno-incompatible-pointer-types-discards-qualifiers" ;;
  esac
}
detect_gen
GLUE_TYPES="$BUILD_DIR/pipeline_glue_types.inc"
if [ ! -f "$GLUE_TYPES" ]; then
  strict_glue_error "missing $GLUE_TYPES; run build_xlang_asm once"
  exit 1
fi
PARSER_ASM_THIN_GLUE_CFLAGS="-DPARSER_ASM_THIN_GLUE_NO_SEED_PARSE"
PARSER_ASM_LINK_ALIAS_CFLAGS="-DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS"
PARSER_ASM_THIN_C="parser_asm_thin_glue.o"
if [ ! -f "$PARSER_ASM_THIN_C" ] || [ "seeds/parser_asm_thin_c.from_x.c" -nt "$PARSER_ASM_THIN_C" ] \
  || [ "seeds/parser_asm/parser_asm_if_stmt_slice.inc" -nt "$PARSER_ASM_THIN_C" ]; then
  strict_glue_info "cc seeds/parser_asm_thin_c.from_x.c → parser_asm_thin_glue.o (G-02f-10)"
  $CC $CFLAGS $PARSER_ASM_THIN_GLUE_CFLAGS -I. -Iinclude -Isrc -Isrc/lexer -Isrc/asm \
    -c seeds/parser_asm_thin_c.from_x.c -o "$PARSER_ASM_THIN_C"
fi
# wave304: pipeline_glue_strict_minimal.from_x.c seed retired; pure runtime_pipeline_abi.o
# (in LD argv) is G.7 authority. Skip compilation when seed absent; ST_GLUE_OBJ guard
# below drops the path so LD argv does not reference non-existent .o. PLATFORM: SHARED.
if [ -f seeds/pipeline_glue_strict_minimal.from_x.c ] && { [ ! -f "$BUILD_DIR/pipeline_glue_strict_minimal.o" ] || [ "seeds/pipeline_glue_strict_minimal.from_x.c" -nt "$BUILD_DIR/pipeline_glue_strict_minimal.o" ]; }; then
  strict_glue_info "cc seeds/pipeline_glue_strict_minimal.from_x.c → pipeline_glue_strict_minimal.o (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/pipeline_glue_strict_minimal.from_x.c -o "$BUILD_DIR/pipeline_glue_strict_minimal.o"
fi
ST_MINIMAL_GLUE_COMPANION=""
if asm_strict_typeck_x_glue_via_pipeline_x; then
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  strict_glue_info "ST_GLUE glue_strict_minimal + pipeline_x glue support (X orch)"
else
  # wave309: standalone seed + ast_pool.c retired; skip when seed absent.
  # Authority = runtime_pipeline_abi.o (LD argv); do not claim ast_pool producer.
  if [ -f seeds/pipeline_glue_standalone.from_x.c ]; then
  strict_glue_info "cc pipeline_glue_standalone.o <- seeds/pipeline_glue_standalone.from_x.c (archaeology)"
  sh scripts/cc_inc_tu.sh seeds/pipeline_glue_standalone.from_x.c "$BUILD_DIR/pipeline_glue_standalone.o" $PIPELINE_GEN_CFLAGS -I"$BUILD_DIR"
  else
  strict_glue_info "skip pipeline_glue_standalone (wave309 seed retired; abi authority)"
  fi
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  # PLATFORM: SHARED — match build_xlang_asm BSTRICT_MINIMAL_GLUE_COMPANION (Linux).
  # typeck_x.o (non-selfhosted path) UNDEFs pipeline_typeck_*_strict_minimal; standalone
  # does not define them. Darwin skips companion (multiply_defined / filtered complement).
  if [ "$(uname -s 2>/dev/null)" != "Darwin" ] && [ -f "$BUILD_DIR/pipeline_glue_strict_minimal.o" ]; then
  ST_MINIMAL_GLUE_COMPANION="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  strict_glue_info "companion pipeline_glue_strict_minimal.o (typeck_x *_strict_minimal)"
  fi
fi
# wave309/wave304: glue seed shells retired; drop ST_GLUE_OBJ if .o physically missing.
# Pure runtime_pipeline_abi.o (in LD argv) provides same symbols (G.7, same as L4 pure-ld).
# When ST_GLUE_OBJ is empty, pipeline_x.o tail is auto-included (line ~1449 guard).
# PLATFORM: SHARED.
[ -z "$ST_GLUE_OBJ" ] || [ -f "$ST_GLUE_OBJ" ] || ST_GLUE_OBJ=""

# 收集非空 build_asm/*.o 并经 filter_strict_asm_objs 筛选（与 build_xlang_asm strict 链一致）。
build_nonempty_asm_objs() {
  NONEMPTY_ASM=""
  for o in "$BUILD_DIR"/*.o; do
  [ -f "$o" ] || continue
  base=$(basename "$o")
  case "$base" in
  typeck_skip.o|typeck_heavy.o|typeck.second.o)
  continue
  ;;
  esac
  if [ -s "$o" ]; then
  NONEMPTY_ASM="$NONEMPTY_ASM $o"
  fi
  done
}

filter_strict_asm_objs() {
  FILTERED=""
  UNAME_HOST=$(uname -m 2>/dev/null || echo unknown)
  local LINK_BUILD_ASM_TYPECK=0
  local LINK_BUILD_ASM_PIPELINE=0
  if asm_strict_typeck_selfhosted; then
  LINK_BUILD_ASM_TYPECK=1
  fi
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  LINK_BUILD_ASM_PIPELINE=1
  fi
  for o in $NONEMPTY_ASM; do
  base=$(basename "$o")
  if [ "$base" = "pipeline.o" ]; then
  if [ "$LINK_BUILD_ASM_PIPELINE" -eq 1 ]; then
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ] && asm_pipeline_wpo_strict_reach_ok; then
  if asm_pipeline_wpo_strict_link_full_ok; then
  ensure_pipeline_wpo_strict_link_alias_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_strict_link_alias.o"
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo.o"
  # FULL 仍须 pipeline_x glue support：ast_pool 桥接（typeck_x 依赖 ast_ref_is_null 等）不在 pipeline_wpo.o 内。
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  strict_glue_info "link pipeline_x glue support (FULL wpo astpool bridge)"
  fi
  strict_glue_info "link whole pipeline_wpo.o (X orchestration, FULL)"
  else
  if asm_strict_x_orchestration_ok; then
  ensure_pipeline_runtime_bootstrap_partial_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  strict_glue_info "link pipeline_x glue support (replace glue_standalone astpool)"
  fi
  if ensure_pipeline_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_helpers_partial.o"
  strict_glue_info "link pipeline_wpo_helpers + pipeline_x runtime bootstrap (opt-in WPO)"
  else
  strict_glue_warn "pipeline_wpo_helpers partial failed; using pipeline_x runtime bootstrap only"
  fi
  echo "su" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  else
  ensure_pipeline_asm_orchestration_partial_obj
  FILTERED="$FILTERED $BUILD_DIR/pipeline_asm_orchestration_partial.o"
  if ensure_pipeline_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_helpers_partial.o"
  strict_glue_info "link pipeline_wpo_helpers + C orchestration (opt-in WPO)"
  fi
  echo "c" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  fi
  fi
  else
  if asm_strict_x_orchestration_ok; then
  ensure_pipeline_runtime_bootstrap_partial_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  strict_glue_info "link pipeline_x glue support (replace glue_standalone astpool)"
  fi
  strict_glue_info "link pipeline_x runtime bootstrap orchestration"
  echo "su" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  else
  ensure_pipeline_asm_orchestration_partial_obj
  FILTERED="$FILTERED $BUILD_DIR/pipeline_asm_orchestration_partial.o"
  strict_glue_info "link pipeline_asm_orchestration_partial.o (C run_x_pipeline_impl)"
  echo "c" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  fi
  fi
  if ensure_pipeline_o_strict_link_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_strict_link_partial.o"
  else
  # G.7: empty pure-extern stub — do not drag 0-T pipeline.o onto LD argv when
  # WPO/abi already covers orch. PLATFORM: SHARED.
  _po_t=$(nm "$o" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${_po_t:-0}" -eq 0 ] && { asm_pipeline_wpo_strict_reach_ok || asm_strict_pipeline_selfhosted; }; then
  strict_glue_info "skip empty pipeline.o on strict LD (WPO/abi covers)"
  else
  FILTERED="$FILTERED $o"
  fi
  fi
  fi
  continue
  fi
  if [ "$base" = "parser.o" ]; then
  continue
  fi
  # PLATFORM: SHARED — keep skip list twin of build_xlang_asm.sh filter_strict_asm_objs /
  # filter_experimental_asm_objs. Darwin filt / complement / host MH objects are linked
  # via dedicated ST_* vars (or Darwin-only stubs slot); never re-admit via build_asm glob
  # or they multiply_define against the explicit stubs / runtime_asm_build authority.
  case "$base" in
  bootstrap_seed_pipeline_filtered.o|bootstrap_seed_user_asm_seed_bridge_filtered.o|bootstrap_seed_asm_backend_compat_stubs_filtered.o|bootstrap_seed_backend_x86_64_enc_c_filtered.o|\
  bstrict_pipeline_filtered.o|bstrict_user_asm_seed_bridge_filtered.o|bstrict_user_asm_seed_bridge_host.o|bstrict_asm_backend_compat_stubs_filtered.o|bstrict_backend_x86_64_enc_c_filtered.o|\
  bstrict_strict_glue_stubs_darwin.o|bstrict_pipeline_glue_minimal_complement.o|preprocess_if_stack_only.o|\
  runtime_driver_strict_glue_stubs.o|\
  parser.o|backend.o|asm.o|main.o|lsp.o|std_fs.o|backend_x86_64_enc_c.o|\
  codegen.o|pipeline_glue_link.o|pipeline_run_impl_alias.o|pipeline_glue_standalone.o|pipeline_glue_strict_minimal.o|\
  parser_bootstrap_partial.o|parser_from_x_partial.o|parser_strict_merged.o|\
  pipeline_parse_x_partial.o|pipeline_runtime_bootstrap_partial.o|pipeline_x_glue_support_partial.o|\
  pipeline_asm_x_bootstrap_partial.o|pipeline_asm_codegen_bootstrap_partial.o|\
  pipeline_asm_runtime_partial.o|pipeline_asm_orchestration_partial.o|\
  pipeline_asm_orchestration_from_build.o|pipeline_phase_parse_only_partial.o|\
  pipeline_phase_parse_only_alias.o|pipeline_asm_run_all_partial.o|\
  pipeline_asm_run_all_alias.o|pipeline_asm_typecheck_alias.o|\
  pipeline_asm_helpers_partial.o|pipeline_asm_orchestration_alias.o|\
  pipeline_strict_link_partial.o|pipeline_wpo.o|pipeline_wpo_helpers_partial.o|pipeline_wpo_typecheck_emit_bridge.o|pipeline_wpo_strict_link_alias.o|\
  pipeline_asm_strict_support_partial.o|pipeline_asm_codegen_only_partial.o|\
  pipeline_asm_strict_core_partial.o|\
  pipeline_run_bootstrap_trampoline.o|pipeline_bootstrap_orchestration_strict.o|\
  asm_backend_platform_writer_partial.o|\
  typeck_skip.o|typeck_heavy.o|typeck.second.o|\
  typeck_asm_layout_partial.o|typeck_x_no_layout_partial.o|typeck_c_orchestration_partial.o|\
  typeck_c_module_stubs.o|typeck_asm_bare_link_alias.o|typeck_wpo.o|typeck_wpo_helpers_partial.o|typeck_strict_link_partial.o|\
  typeck_lsp_io_stub.o|\
  backend_wpo.o|backend_strict_link_partial.o|backend_asm_bare_link_alias.o|backend_asm_strict_fallback_alias.o|asm_backend_seed_helper_partial.o|backend_seed_mega_fallback.o|\
  asm_backend_compat_stubs.o|\
  std_fs_shim.o|x_seed_bridge.o|seed_link_compat.o|\
  parser_from_gen.o|asm_experimental_symbol_bridge.o|asm_xlang_lsp_diag_stub.o|\
  \
  lexer.o|peephole.o|platform_elf.o|macho.o|coff.o|\
  parser_asm_minimal_partial.o|parser_asm_thin_c.o|\
  driver_compile.o|driver_compile_asm_link_alias.o|driver_compile_emit_heavy.o|driver_compile_link.o)
  continue
  ;;
  esac
  if [ "$base" = "typeck.o" ]; then
  if [ "$LINK_BUILD_ASM_TYPECK" -eq 1 ]; then
  if asm_typeck_wpo_strict_link_helpers_ok; then
  if ensure_typeck_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/typeck_wpo_helpers_partial.o"
  strict_glue_info "link typeck_wpo_helpers + typeck.o partial"
  else
  FILTERED="$FILTERED $BUILD_DIR/typeck_wpo.o"
  fi
  ensure_typeck_o_strict_link_partial_obj && FILTERED="$FILTERED $BUILD_DIR/typeck_strict_link_partial.o"
  elif asm_strict_typeck_selfhosted; then
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  strict_glue_info "skip build_asm/typeck.o (X glue; seed typeck + typeck_x.o tail)"
  elif ensure_typeck_o_strict_link_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/typeck_strict_link_partial.o"
  strict_glue_info "link typeck.o partial (selfhosted, minus glue dupes)"
  else
  FILTERED="$FILTERED $o"
  strict_glue_info "link whole typeck.o (selfhosted partial failed)"
  fi
  else
  FILTERED="$FILTERED $o"
  fi
  fi
  continue
  fi
  if [ "$base" = "typeck_asm_layout_partial.o" ] && [ "$LINK_BUILD_ASM_TYPECK" -eq 1 ]; then
  continue
  fi
  case "$UNAME_HOST" in
  arm64|aarch64)
  case "$base" in
  x86_64.o|x86_64_enc.o|riscv64.o|riscv64_enc.o) continue ;;
  esac
  ;;
  x86_64|amd64)
  case "$base" in
  arm64.o|arm64_enc.o|riscv64.o|riscv64_enc.o) continue ;;
  esac
  ;;
  esac
  # G.7 twin of build_xlang_asm filter_strict_asm_objs: skip tiny enc stubs.
  case "$base" in
  x86_64_enc.o|arm64_enc.o|riscv64_enc.o)
  enc_stub_bytes=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  if [ "${enc_stub_bytes:-0}" -lt 512 ] 2>/dev/null; then
  strict_glue_info "strict skip stub $base (__text=${enc_stub_bytes}B)"
  continue
  fi
  ;;
  esac
  # PLATFORM: DARWIN — Apple ld rejects multiple _xlang_asm_ci_text_stub across
  # first-pass CI placeholders (arm64/ast/token/types/preprocess …). Skip pure
  # CI text stubs (≤64B, no other global T). Twin of build_xlang_asm.sh.
  _stub_t=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  if [ "${_stub_t:-0}" -le 64 ] 2>/dev/null \
    && nm "$o" 2>/dev/null | grep -qE '(_)?xlang_asm_ci_text_stub$'; then
  _other_t=$(nm -g "$o" 2>/dev/null | awk '/ [Tt] / && $3 !~ /xlang_asm_ci_text_stub/ { c++ } END { print c+0 }')
  if [ "${_other_t:-0}" = "0" ]; then
  strict_glue_info "strict skip CI text stub $base (__text=${_stub_t}B)"
  continue
  fi
  fi
  FILTERED="$FILTERED $o"
  done
}

build_nonempty_asm_objs
filter_strict_asm_objs
ASM_TRY_OBJS="$FILTERED"
if echo " $ASM_TRY_OBJS " | grep -q 'pipeline_strict_link_partial.o' \
  && echo " $ASM_TRY_OBJS " | grep -q 'pipeline_x_glue_support_partial.o'; then
  ASM_TRY_OBJS=$(
  for o in $ASM_TRY_OBJS; do
  [ "$o" = "$BUILD_DIR/pipeline_x_glue_support_partial.o" ] && continue
  printf '%s\n' "$o"
  done | paste -sd' ' -
  )
  strict_glue_info "omit pipeline_x_glue_support_partial (strict pipeline partial already owns promoted glue)"
fi

# build_asm/parser.o 仅导出 parser_x/glue 缺的符号（勿链整颗 parser.o，会与 seed parser 重复）。
ensure_parser_asm_minimal_partial_obj() {
  local PARTIAL SYMS PO
  PARTIAL="$BUILD_DIR/parser_asm_minimal_partial.o"
  SYMS="$BUILD_DIR/parser_asm_minimal_export.txt"
  PO="$BUILD_DIR/parser.o"
  if [ ! -f "$PO" ] || [ ! -s "$PO" ]; then
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$PO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_parser_parse_expr_into
_parser_copy_module_import_path64
_parser_parse_one_function_ok_for_pipeline
EOF
  strict_glue_info "ld -r parser_asm_minimal_partial.o <- parser.o (3 symbols)"
  ld_partial_export "$SYMS" "$PARTIAL" "$PO" || return 1
  fi
  return 0
}

PARSER_ASM_PARTIAL=""
if [ ! -f parser_x.o ] && ensure_parser_asm_minimal_partial_obj; then
  PARSER_ASM_PARTIAL="$BUILD_DIR/parser_asm_minimal_partial.o"
fi

PARSER_EXPR_LINK_O="src/asm/parser_asm_parse_expr_link.o"
if [ ! -f "$PARSER_EXPR_LINK_O" ] || [ "seeds/parser_asm_parse_expr_link.from_x.c" -nt "$PARSER_EXPR_LINK_O" ]; then
  strict_glue_info "cc seeds/parser_asm_parse_expr_link.from_x.c → parse_expr_link.o (G-02f-10)"
  $CC $CFLAGS $PARSER_ASM_LINK_ALIAS_CFLAGS -I. -Iinclude -Isrc \
    -c seeds/parser_asm_parse_expr_link.from_x.c -o "$PARSER_EXPR_LINK_O"
fi

ST_LAYOUT_PARTIAL=""
if [ -f "$BUILD_DIR/typeck_asm_layout_partial.o" ] && ! asm_strict_typeck_selfhosted; then
  ST_LAYOUT_PARTIAL="$BUILD_DIR/typeck_asm_layout_partial.o"
fi

ST_TYPECK_X_LINK="typeck_x.o"
if ! asm_strict_typeck_selfhosted && [ -f "$BUILD_DIR/typeck_asm_layout_partial.o" ] && [ -f "$BUILD_DIR/typeck_x_no_layout_partial.o" ]; then
  ST_TYPECK_X_LINK="$BUILD_DIR/typeck_x_no_layout_partial.o"
fi

ensure_async_cps_seed_objs
ST_ASYNC_CPS_SEED=$(asm_seed_st_async_support_link)
ST_PREPROCESS_SEED=$(asm_seed_st_preprocess_link)

# strict 自举链须 typeck_x.o（与 experimental 一致；缺则 X typeck 桥接不全）。
# PLATFORM: SHARED — post-Makefile phys-del: migrate_x_objs (G.7 twin of
# build_xlang_asm wave929). Escape: XLANG_STRICT_GLUE_VIA_MAKE=1 + MF.
ensure_typeck_x_o_for_strict_link() {
  if [ -f typeck_x.o ]; then
    return 0
  fi
  if [ "${XLANG_STRICT_GLUE_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    strict_glue_info "make typeck_x.o"
    make -s typeck_x.o
  else
    strict_glue_info "migrate_x_objs typeck_x.o (0-make)"
    bash scripts/migrate_x_objs.sh typeck_x.o || true
  fi
  [ -f typeck_x.o ] || return 1
  return 0
}
ensure_typeck_x_o_for_strict_link || strict_glue_warn "missing typeck_x.o"

ST_TYPECK_C_STUBS=""
ST_TYPECK_BARE_ALIAS=""
if asm_strict_typeck_selfhosted; then
  ST_TYPECK_C_STUBS=$(ensure_typeck_c_user_precheck_obj)
  if asm_seed_omit_c_frontend_seed; then
  ensure_typeck_x_o_for_strict_link || true
  ST_SEED_PARSER_TCK="$ST_ASYNC_CPS_SEED codegen_x.o x_frontend_link_alias.o"
  strict_glue_info "omit asm_driver_seed frontend C objs (X companions ready)"
  elif asm_strict_typeck_x_glue_via_pipeline_x; then
  ensure_typeck_x_o_for_strict_link || true
  ST_SEED_PARSER_TCK="$SEED_O/parser.o $ST_ASYNC_CPS_SEED $SEED_O/lexer.o $SEED_O/ast_seed.o codegen_x.o x_frontend_link_alias.o"
  strict_glue_info "seed typeck + typeck_x tail (X glue; no build_asm typeck partial/bare_link)"
  else
  # wave296: seed-only authority (host typeck_asm_bare_link_alias.c left).
  _tba_seed=seeds/typeck_asm_bare_link_alias.from_x.c
  if [ ! -f "$_tba_seed" ]; then
  strict_glue_info "missing $_tba_seed (wave296 seed authority)"
  return 1
  fi
  if [ ! -f "$BUILD_DIR/typeck_asm_bare_link_alias.o" ] || [ "$_tba_seed" -nt "$BUILD_DIR/typeck_asm_bare_link_alias.o" ]; then
  strict_glue_info "cc -c $_tba_seed -> $BUILD_DIR/typeck_asm_bare_link_alias.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$BUILD_DIR/typeck_asm_bare_link_alias.o" "$_tba_seed"
  fi
  ST_TYPECK_BARE_ALIAS="$BUILD_DIR/typeck_asm_bare_link_alias.o"
  ST_SEED_PARSER_TCK="$ST_TYPECK_C_STUBS $ST_TYPECK_BARE_ALIAS $SEED_O/parser.o $ST_ASYNC_CPS_SEED $SEED_O/lexer.o $SEED_O/ast_seed.o codegen_x.o x_frontend_link_alias.o"
  if [ -f src/typeck/typeck_f64_bits.o ]; then
  ST_SEED_PARSER_TCK="$ST_SEED_PARSER_TCK src/typeck/typeck_f64_bits.o"
  fi
  strict_glue_info "typeck partial + bare_link_alias (__text=$(asm_o_text_bytes "$BUILD_DIR/typeck.o")B)"
  fi
elif asm_seed_omit_c_frontend_seed; then
  ST_SEED_PARSER_TCK="$ST_ASYNC_CPS_SEED $ST_TYPECK_X_LINK codegen_x.o x_frontend_link_alias.o"
  strict_glue_info "typeck not selfhosted; omit asm_driver_seed frontend C objs"
else
  ST_SEED_PARSER_TCK="$SEED_O/parser.o $ST_ASYNC_CPS_SEED $SEED_O/lexer.o $SEED_O/ast_seed.o $ST_TYPECK_X_LINK codegen_x.o x_frontend_link_alias.o"
  strict_glue_info "typeck not selfhosted yet (__text=$(asm_o_text_bytes "$BUILD_DIR/typeck.o")B)"
fi

# PLATFORM: SHARED — G-02e: f32 xmm lives in backend_call_dispatch; match build_xlang_asm BSTRICT_DISPATCH_OBJS.
BSTRICT_DISPATCH="src/asm/backend_enc_dispatch.o src/asm/backend_arch_emit_dispatch.o src/asm/backend_try_inline_dispatch.o src/asm/backend_call_dispatch.o"
ST_DRIVER_COMPILE_O="driver_compile_x.o"
# asm driver 替换须 STRICT_LINK_BUILD_ASM_DRIVER=1；默认仍用 C-gen（link.o 链入后 strict check 仍待修 arm64 对齐/ABI）。
if [ "${STRICT_LINK_BUILD_ASM_DRIVER:-0}" -eq 1 ] && [ -f "$BUILD_DIR/driver_compile_link.o" ]; then
  dc_sz=$(asm_o_text_bytes "$BUILD_DIR/driver_compile_emit_heavy.o" 2>/dev/null || echo 0)
  if [ "$dc_sz" -lt 5120 ] 2>/dev/null; then
  dc_sz=$(asm_o_text_bytes "$BUILD_DIR/driver_compile.o" 2>/dev/null || echo 0)
  fi
  if [ "$dc_sz" -ge 5120 ] 2>/dev/null; then
  # PLATFORM: MACOS — link.o may be libtool ar (F7 two LC_SEGMENT via
  # pure_ld_partial_merge). Expand to MH_OBJECT members for Apple ld (G.7 twin
  # build_xlang_asm filter_strict_asm_objs). PLATFORM: LINUX — keep ET_REL link.o.
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ] \
    && file "$BUILD_DIR/driver_compile_link.o" 2>/dev/null | grep -qi 'ar archive'; then
  ST_DRIVER_COMPILE_O="$BUILD_DIR/driver_compile_emit_heavy.o $BUILD_DIR/driver_compile_asm_link_alias.o"
  if [ -f "$BUILD_DIR/driver_compile_parse_argv_loop_partial.o" ] \
    && nm "$BUILD_DIR/driver_compile_emit_heavy.o" 2>/dev/null \
      | grep -qE ' U (_)?driver_compile_parse_argv_loop$'; then
  ST_DRIVER_COMPILE_O="$ST_DRIVER_COMPILE_O $BUILD_DIR/driver_compile_parse_argv_loop_partial.o"
  fi
  strict_glue_info "driver selfhosted (__text=${dc_sz}B, Darwin eh+alias MH, STRICT_LINK_BUILD_ASM_DRIVER=1)"
  else
  ST_DRIVER_COMPILE_O="$BUILD_DIR/driver_compile_link.o"
  strict_glue_info "driver selfhosted (__text=${dc_sz}B, link.o, STRICT_LINK_BUILD_ASM_DRIVER=1)"
  fi
  fi
fi
# orchestration partial 已含 pipeline_run_x_pipeline_impl；勿再链 trampoline（与 build_xlang_asm strict_support 一致）。
ensure_pipeline_run_bootstrap_trampoline_obj() {
  local TRAMP_O TRAMP_CFLAGS
  TRAMP_O="$BUILD_DIR/pipeline_run_bootstrap_trampoline.o"
  TRAMP_CFLAGS="$CFLAGS"
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  if echo " $ASM_TRY_OBJS $ST_RUNTIME_PARTIAL $ST_STRICT_ORCH_ALIAS " | grep -qE 'pipeline\.o|orchestration|runtime_bootstrap|wpo_strict_link_alias'; then
  TRAMP_CFLAGS="$CFLAGS -DSTRICT_LINK_BUILD_ASM_PIPELINE=1"
  fi
  fi
  if [ ! -f "$TRAMP_O" ] || [ "seeds/pipeline_run_bootstrap_trampoline.from_x.c" -nt "$TRAMP_O" ]; then
  strict_glue_info "cc pipeline_run_bootstrap_trampoline.o"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_bootstrap_trampoline.from_x.c "$TRAMP_O"
  fi
}
ST_WPO_ALIAS=""
# pipeline_strict_link_partial 内 run_x_pipeline_typecheck_entry 会 thin bl→run_x_pipeline_typecheck_entry_emit。
if echo " $ASM_TRY_OBJS " | grep -q 'pipeline_strict_link_partial.o'; then
  if echo " $ASM_TRY_OBJS " | grep -q 'pipeline_wpo_strict_link_alias.o'; then
  : # strict_link_alias 已提供 emit
  else
  ensure_pipeline_wpo_typecheck_emit_bridge_obj && ST_WPO_ALIAS="$BUILD_DIR/pipeline_wpo_typecheck_emit_bridge.o"
  strict_glue_info "link pipeline_wpo_typecheck_emit_bridge (strict_link_partial typecheck_entry)"
  fi
elif [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ]; then
  if asm_pipeline_wpo_strict_link_full_ok; then
  : # alias/bridge 已在 ASM_TRY_OBJS
  else
  ensure_pipeline_wpo_typecheck_emit_bridge_obj && ST_WPO_ALIAS="$BUILD_DIR/pipeline_wpo_typecheck_emit_bridge.o"
  fi
fi
# pipeline.x + C 编排 alias（须在 trampoline 编译前判定 STRICT_LINK_BUILD_ASM_PIPELINE）。
ensure_pipeline_x_o_fresh || true
ST_PIPELINE_X_TAIL=""
if [ -f pipeline_x.o ] && [ "$ST_GLUE_OBJ" != "$BUILD_DIR/pipeline_glue_standalone.o" ]; then
  if echo " $ASM_TRY_OBJS " | grep -q 'pipeline_strict_link_partial.o'; then
  strict_glue_info "omit pipeline_x.o tail (strict pipeline partial already linked)"
  else
  ST_PIPELINE_X_TAIL="pipeline_x.o"
  fi
fi
ST_STRICT_ORCH_ALIAS=""
if [ "$ST_GLUE_OBJ" = "$BUILD_DIR/pipeline_glue_standalone.o" ]; then
  if ! echo " $ASM_TRY_OBJS " | grep -qE 'pipeline_asm_orchestration|pipeline_runtime_bootstrap|pipeline_wpo_strict_link_alias'; then
  strict_glue_info "glue_standalone uses orchestration partial (not full alias TU)"
  fi
fi
ST_RUNTIME_PARTIAL=""
if asm_pipeline_wpo_strict_link_full_ok; then
  ST_RUNTIME_PARTIAL=""
elif [ -n "$ST_WPO_ALIAS" ]; then
  ST_RUNTIME_PARTIAL=""
elif echo " $ASM_TRY_OBJS " | grep -q 'pipeline_runtime_bootstrap_partial.o'; then
  ST_RUNTIME_PARTIAL=""
elif echo " $ASM_TRY_OBJS " | grep -q 'pipeline_asm_orchestration_partial.o'; then
  ST_RUNTIME_PARTIAL=""
elif echo " $ASM_TRY_OBJS " | grep -q 'pipeline_strict_link_partial.o'; then
  ST_RUNTIME_PARTIAL=""
elif [ "$ST_GLUE_OBJ" = "$BUILD_DIR/pipeline_glue_standalone.o" ] && \
  ! echo " $ASM_TRY_OBJS " | grep -qE 'pipeline_asm_orchestration|pipeline_runtime_bootstrap|pipeline_wpo_strict_link_alias|pipeline_strict_link_partial'; then
  ensure_pipeline_asm_orchestration_partial_obj && ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_partial.o"
elif [ -f "$BUILD_DIR/pipeline_bootstrap_orchestration_strict.o" ] && ! asm_strict_x_orchestration_ok; then
  ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_bootstrap_orchestration_strict.o"
else
  ensure_pipeline_run_bootstrap_trampoline_obj
  ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_run_bootstrap_trampoline.o"
fi
ensure_asm_backend_compat_stubs_obj
# lsp_state.o 依赖 typeck_lsp_main_impl（lsp.x -E → lsp_x.o）；与 build_xlang_asm ensure_asm_experimental_lsp_objs 一致。
# wave937: shell-primary (was make -s lsp_io_gen.c lsp_gen.c ...). Mirrors
# build_xlang_asm.sh ensure_asm_experimental_lsp_objs shell path (wave930).
ensure_strict_glue_lsp_objs() {
  GEN_DIR="$BUILD_DIR/gen_driver"
  mkdir -p "$GEN_DIR"
  strict_glue_info "ensure lsp_x.o (+ lsp_io) for lsp_state (typeck_lsp_main_impl)"
  # LSP pipeline gen sources + .o via shell (G.7 single body; no Makefile).
  bash scripts/ensure_lsp_pipeline_gen.sh lsp
  bash scripts/ensure_archaeology_gen.sh lsp_io_std_heap
  bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_x.o
  bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_io_x.o
  # lsp_io_std_heap_x.o: driver_leaf product obj (via driver_leaf_x_to_o.sh ensure).
  if [ ! -f lsp_io_std_heap_x.o ]; then
    bash scripts/driver_leaf_x_to_o.sh ensure lsp_io_std_heap_x.o
  fi
  cp -f lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o "$GEN_DIR/"
}
ensure_strict_glue_lsp_objs || true
ensure_asm_xlang_lsp_diag_stub_obj
ensure_lsp_diag_seed_obj "$SEED_O"
ensure_diag_seed_obj "$SEED_O"
LSP_DIAG_SEED_O=$(lsp_diag_seed_obj_path "$SEED_O")
# G-02-B1：优先 pipeline_fill_dep_strict_alias.x（-backend asm）；失败回退 .c。
XLANG_REL="${XLANG:-./xlang_asm}"
[ -x "$XLANG_REL" ] || XLANG_REL=./xlang
LIBROOT_REL=""
if [ -f src/asm/asm_build_list.x ]; then
  LIBROOT_REL=$(sed -n 's|^// LIBROOT:[[:space:]]*||p' src/asm/asm_build_list.x | head -1)
fi
if [ -f src/asm/pipeline_fill_dep_strict_alias.x ] \
  && { [ ! -f src/asm/pipeline_fill_dep_strict_alias.o ] \
  || [ src/asm/pipeline_fill_dep_strict_alias.x -nt src/asm/pipeline_fill_dep_strict_alias.o ]; }; then
  if [ -x "$XLANG_REL" ] && "$XLANG_REL" -backend asm -o src/asm/pipeline_fill_dep_strict_alias.o $LIBROOT_REL \
  src/asm/pipeline_fill_dep_strict_alias.x 2>/dev/null; then
  strict_glue_info "$XLANG_REL -backend asm pipeline_fill_dep_strict_alias.x"
  elif [ -f seeds/pipeline_fill_dep_strict_alias.from_x.c ]; then
  strict_glue_info "cc -c seeds/pipeline_fill_dep_strict_alias.from_x.c (fallback)"
  sh scripts/cc_inc_tu.sh seeds/pipeline_fill_dep_strict_alias.from_x.c src/asm/pipeline_fill_dep_strict_alias.o
  fi
elif [ ! -f src/asm/pipeline_fill_dep_strict_alias.o ] \
  && [ -f seeds/pipeline_fill_dep_strict_alias.from_x.c ]; then
  strict_glue_info "cc -c seeds/pipeline_fill_dep_strict_alias.from_x.c"
  sh scripts/cc_inc_tu.sh seeds/pipeline_fill_dep_strict_alias.from_x.c src/asm/pipeline_fill_dep_strict_alias.o
fi
# PLATFORM: SHARED — G-02e: std_sys_shim folded into runtime_io_abi (match build_xlang_asm ST_BSTRICT_LINK_EXTRA).
ST_BSTRICT_LINK_EXTRA="src/asm/parser_asm_parse_expr_link.o src/asm/pipeline_fill_dep_strict_alias.o"
ensure_ast_asm_bare_link_alias_obj
ST_AST_BARE_ALIAS=""
if ! echo " $ASM_TRY_OBJS " | grep -q 'ast_asm_bare_link_alias.o'; then
  ST_AST_BARE_ALIAS="$BUILD_DIR/ast_asm_bare_link_alias.o"
fi
ST_LSP_X_OBJS=""
if [ -f "$BUILD_DIR/gen_driver/lsp_x.o" ]; then
  ST_LSP_X_OBJS="$BUILD_DIR/gen_driver/lsp_x.o $BUILD_DIR/gen_driver/lsp_io_x.o $BUILD_DIR/gen_driver/lsp_io_std_heap_x.o"
fi
ST_TYPECK_LSP_STUB=""
if [ -z "$ST_LSP_X_OBJS" ]; then
  ST_TYPECK_LSP_STUB="$BUILD_DIR/typeck_lsp_io_stub.o"
fi
ensure_simd_glue_link_objs
dbg_event A "before strict_asm_backend_companion_objs"
ST_BACKEND_COMPANIONS=$(strict_asm_backend_companion_objs) || ST_BACKEND_COMPANIONS="$BUILD_DIR/seed_host/asm_backend_partial.o"
dbg_event A "after strict_asm_backend_companion_objs"
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ST_BACKEND_COMPANIONS=""
  ensure_asm_backend_platform_writer_partial_obj && ST_BACKEND_COMPANIONS="$BUILD_DIR/asm_backend_platform_writer_partial.o"
  dbg_event A "darwin: keep only narrow platform writer companion to avoid duplicate symbols"
fi
if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  strict_glue_info "link backend_wpo.o (WPO reach OK)"
fi
if [ ! -f "$BUILD_DIR/seed_link_compat.o" ] || [ "seeds/seed_link_compat.from_x.c" -nt "$BUILD_DIR/seed_link_compat.o" ]; then
  strict_glue_info "cc -c $BUILD_DIR/seed_link_compat.o <- seeds/seed_link_compat.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/seed_link_compat.from_x.c -o "$BUILD_DIR/seed_link_compat.o"
fi
ST_STRICT_COMPANIONS="src/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $ST_BACKEND_COMPANIONS src/asm/user_asm_seed_bridge.o $BUILD_DIR/asm_backend_compat_stubs.o $BSTRICT_DISPATCH src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o preprocess_x.o driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o $ST_DRIVER_COMPILE_O driver_emit_x.o $ST_BSTRICT_LINK_EXTRA"
# G-02e: codegen_pipeline_stubs folded into runtime_driver_strict_glue_stubs (linked separately).
ST_STRICT_COMPANIONS="$ST_STRICT_COMPANIONS src/typeck/typeck_f64_bits.o src/lexer/cfg_eval.o"
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ST_STRICT_COMPANIONS="$ST_STRICT_COMPANIONS $BUILD_DIR/backend_seed_mega_fallback.o"
fi

ST_PARSER_X_TAIL=""
if [ -f parser_x.o ]; then
  ST_PARSER_X_TAIL="parser_x.o"
  if [ -f lexer_x.o ]; then
  ST_PARSER_X_TAIL="$ST_PARSER_X_TAIL lexer_x.o"
  else
  strict_glue_warn "missing lexer_x.o (ensure try-gen-x / migrate); strict link may have undefined symbols"
  fi
  # parser_x.o 已导出 parse_expr_into / parser_copy_module_import_path64 等；勿再链 partial。
  # 弱 parse 桩 / parse_expr 桥在 src/asm/parser_asm_parse_expr_link.o（ST_BSTRICT_LINK_EXTRA）。
  PARSER_ASM_PARTIAL=""
fi

ST_TYPECK_X_TAIL=""
if asm_strict_typeck_x_glue_via_pipeline_x && [ -f "$ST_TYPECK_X_LINK" ]; then
  ST_TYPECK_X_TAIL="$ST_TYPECK_X_LINK"
fi

ensure_runtime_driver_diagnostic_obj() {
  local o="src/runtime_driver_diagnostic.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_diagnostic.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_driver_diagnostic.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_diagnostic.from_x.c -o "$o"
  fi
}

ensure_diag_obj() {
  local o="src/diag.o"
  if [ ! -f "$o" ] || [ "seeds/diag.from_x.c" -nt "$o" ] || [ "include/diag.h" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/diag.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/diag.from_x.c -o "$o"
  fi
}

# 与 build_xlang_asm.sh 一致：pipeline_x/typeck_x 引用 driver_typeck_skip_large_entry / pipeline_get_dep_arena_slot。
ensure_runtime_driver_abi_obj() {
  local o="src/runtime_driver_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_abi.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_driver_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_pipeline_abi_obj() {
  local o="src/runtime_pipeline_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_pipeline_abi.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_pipeline_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE -c seeds/runtime_pipeline_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_driver_diagnostic_obj
ensure_diag_obj
ensure_runtime_driver_abi_obj
ensure_runtime_pipeline_abi_obj

# 与 build_xlang_asm.sh strict 链一致：driver_get_argv_i / xlang_read_file_into_path / invoke_ld。
# PLATFORM: SHARED — G-02e: runtime_abi.c / runtime_proc_abi.c merged into runtime_link_abi;
#   std_fs_shim / std_sys_shim merged into runtime_io_abi. Authority matches build_xlang_asm.sh.
ensure_runtime_io_abi_obj() {
  local o="src/runtime_io_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_io_abi.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_io_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o "$o"
  fi
}
ensure_runtime_link_abi_obj() {
  local o="src/runtime_link_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_link_abi.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_link_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_link_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_pipeline_abi_obj() {
  local o="src/runtime_pipeline_abi.o"
  local cf="$CFLAGS -DXLANG_USE_X_PIPELINE"
  if [ "${XLANG_LEGACY_PREPROCESS_C:-0}" = "1" ]; then
  cf="$cf -DXLANG_LEGACY_PREPROCESS_C"
  fi
  # PLATFORM: SHARED — freshness authority = seed only (wave941 Makefile deleted;
  # dead Makefile -nt never fired; same debt layer as ast_pool/glue SYMS ensure).
  if [ ! -f "$o" ] || [ "seeds/runtime_pipeline_abi.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_pipeline_abi.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE -c seeds/runtime_pipeline_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_driver_obj() {
  local o="src/runtime_driver.o"
  # wave321 7.1.1: monofile seeds/runtime.from_x.c retired — multi-slice no_c alias.
  # PLATFORM: SHARED freestanding; archaeology strict-glue uses product authority.
  if [ ! -f "$o" ] \
    || { [ -f seeds/rt_content.from_x.c ] && [ seeds/rt_content.from_x.c -nt "$o" ]; }; then
    strict_glue_info "ensure $o via multi-slice no_c alias (wave321 monofile retired)"
    bash scripts/ensure_host_cc_seed_o.sh try-r1 "$o" || return 1
  fi
}

ensure_ast_obj() {
  local o="src/ast/ast.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_ast_glue.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_ast_glue.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_ast_glue.from_x.c -o "$o"
  fi
}

ensure_lexer_obj() {
  local o="src/lexer/lexer.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_lexer_glue.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc_inc_tu $o <- seeds/runtime_lexer_glue.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lexer_glue.from_x.c -o "$o"
  fi
}

# G-02a: typeck.c 已物理删除；ensure_typeck_obj 已移除（typeck_x.o + typeck_c_module_stubs.o 提供）。

# G-02a: codegen.c 已物理删除；ensure_codegen_obj 已移除（codegen_x.o + runtime_driver_strict_glue_stubs）。
# G-02e: codegen_pipeline_stubs.c 已并入 runtime_driver_strict_glue_stubs.from_x.c。

ensure_runtime_c_import_obj() {
  local o="src/runtime_c_import.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_c_import.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_c_import.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_c_import.from_x.c -o "$o"
  fi
}

ensure_runtime_pipeline_abi_xlang_c_stubs_obj() {
  # G-02e-12：实现已并入 runtime_driver_strict_glue_stubs.inc
  local o="src/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
    strict_glue_info "cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11) (former pipeline_abi_xlang_c_stubs)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
}
# G-02e: codegen_pipeline_stubs / std_fs_shim deleted — use ensure_runtime_driver_strict_glue_stubs_obj
# and ensure_runtime_io_abi_obj (authority in build_xlang_asm.sh).

ensure_runtime_driver_strict_glue_stubs_obj() {
  local o="$BUILD_DIR/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
}

# PLATFORM: DARWIN — G.7 twin of build_xlang_asm ensure_bstrict_darwin_strict_glue_stubs_filt_obj.
# Full stubs.o exports strong asm_driver_* / asm_asm_codegen_* that collide with
# runtime_asm_build / user_asm bridge (Darwin ld rejects multiply_defined; Linux
# --allow-multiple-definition papers it over). Authority = filtered MH_OBJECT that
# omits those symbols. Prefer/libtool may leave src stubs as ar → force MH_OBJECT.
ensure_strict_glue_darwin_stubs_filt_obj() {
  local src_o="src/runtime_driver_strict_glue_stubs.o"
  local out_o="$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o"
  local seed="seeds/runtime_driver_strict_glue_stubs.from_x.c"
  local need_cc=0
  if [ ! -f "$src_o" ] || [ "$seed" -nt "$src_o" ]; then
  need_cc=1
  elif file "$src_o" 2>/dev/null | grep -qi 'ar archive'; then
  need_cc=1
  fi
  if [ "$need_cc" = "1" ]; then
  strict_glue_info "cc -c $src_o <- $seed (Darwin filt prep; MH_OBJECT)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$seed" -o "$src_o" || return 1
  fi
  [ -f "$src_o" ] || return 1
  if [ -f "$out_o" ] && nm -gU "$out_o" 2>/dev/null | grep -qE 'asm_asm_codegen_(elf_o|ast)$'; then
  rm -f "$out_o"
  fi
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ]; then
  strict_glue_info "filter_o_export $(basename "$src_o") -> $(basename "$out_o") (Darwin, omit asm_driver_* + asm_asm_codegen_*)"
  bash scripts/filter_o_export_against_deps.sh \
    --src "$src_o" --out "$out_o" --stem bstrict_strict_glue_stubs_darwin \
    --omit-sym asm_driver_set_current_dep_path_for_codegen \
    --omit-sym asm_driver_skip_codegen_dep_0_get \
    --omit-sym asm_asm_codegen_elf_o \
    --omit-sym asm_asm_codegen_ast \
    --require-keep || return 1
  fi
  if ! nm -gU "$out_o" 2>/dev/null | grep -q 'codegen_set_dep_slots_for_x_pipeline'; then
  strict_glue_warn "Darwin stubs filt missing codegen_set_dep_slots_for_x_pipeline"
  return 1
  fi
  if ! nm -gU "$out_o" 2>/dev/null | grep -q 'pipeline_block_labeled_set_names'; then
  strict_glue_warn "Darwin stubs filt missing pipeline_block_labeled_set_names"
  return 1
  fi
  if nm -gU "$out_o" 2>/dev/null | grep -qE 'asm_asm_codegen_(elf_o|ast)$'; then
  strict_glue_warn "Darwin stubs filt still exports asm_asm_codegen_*"
  return 1
  fi
  return 0
}
ensure_runtime_asm_build_obj() {
  local o="src/asm/runtime_asm_build.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_asm_build.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/runtime_asm_build.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_asm_build.from_x.c -o "$o"
  fi
}

ensure_x_seed_bridge_obj() {
  local o="src/x_seed_bridge.o"
  if [ ! -f "$o" ] || [ "seeds/x_seed_bridge.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/x_seed_bridge.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/x_seed_bridge.from_x.c -o "$o"
  fi
}

ensure_ast_pool_l5_bridge_obj() {
  # G-02e-13：实现已并入 runtime_driver_strict_glue_stubs.inc
  local o="src/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
    echo "  cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11) (former ast_pool_l5_bridge)" >&2
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
}

ensure_asm_experimental_symbol_bridge_obj() {
  local o="src/asm/asm_experimental_symbol_bridge.o"
  if [ ! -f "$o" ] || [ "seeds/asm_experimental_symbol_bridge.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- seeds/asm_experimental_symbol_bridge.from_x.c"
  sh scripts/cc_inc_tu.sh seeds/asm_experimental_symbol_bridge.from_x.c "$o"
  fi
}

ensure_lsp_codegen_extern_obj() {
  # G-02e-11：实现已并入 runtime_driver_strict_glue_stubs.inc
  local o="src/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
    strict_glue_info "cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11) (former lsp_codegen_extern)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
}

ensure_lsp_pipeline_ctx_obj() {
  local o="src/lsp/lsp_diag_pipeline_ctx.o"
  if [ ! -f "$o" ] || [ "seeds/lsp_diag_pipeline_ctx.from_x.c" -nt "$o" ]; then
    strict_glue_info "cc -c $o <- seeds/lsp_diag_pipeline_ctx.from_x.c"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/lsp_diag_pipeline_ctx.from_x.c -o "$o"
  fi
}
ensure_backend_seed_mega_fallback_obj() {
  local o="$BUILD_DIR/backend_seed_mega_fallback.o"
  local src="seeds/backend_seed_mega_fallback.from_x.c"
  if [ ! -f "$o" ] || [ "$src" -nt "$o" ]; then
  strict_glue_info "cc_inc_tu $o <- $src (weak backend stubs)"
  sh scripts/cc_inc_tu.sh "$src" "$o"
  fi
}
ensure_backend_x86_64_enc_c_obj() {
  local o="$BUILD_DIR/backend_x86_64_enc_c.o"
  local src="seeds/backend_x86_64_enc_c.from_x.c"
  if [ ! -f "$o" ] || [ "$src" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- $src (G-02f-15 x86_64 enc)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$src" -o "$o"
  fi
}
ensure_typeck_f64_bits_obj() {
  local uname_s uname_m src
  uname_s=$(uname -s 2>/dev/null || echo Unknown)
  uname_m=$(uname -m 2>/dev/null || echo Unknown)
  src=""
  if [ "$uname_s" = "Linux" ] && [ "$uname_m" = "x86_64" ]; then
  src="src/typeck/typeck_f64_bits_x86_64.s"
  elif [ "$uname_s" = "Linux" ] && [ "$uname_m" = "aarch64" ]; then
  src="src/typeck/typeck_f64_bits_aarch64_elf.s"
  elif [ "$uname_s" = "Darwin" ] && [ "$uname_m" = "arm64" ]; then
  src="src/typeck/typeck_f64_bits_arm64.s"
  elif [ "$uname_s" = "Darwin" ] && [ "$uname_m" = "x86_64" ]; then
  src="src/typeck/typeck_f64_bits_x86_64.s"
  fi
  if [ -z "$src" ] || [ ! -f "$src" ]; then
  strict_glue_info "ensure_typeck_f64_bits_obj: missing .s for $uname_s/$uname_m"
  return 1
  fi
  if [ ! -f src/typeck/typeck_f64_bits.o ] || [ "$src" -nt src/typeck/typeck_f64_bits.o ]; then
  strict_glue_info "cc -c src/typeck/typeck_f64_bits.o <- $src"
  "$CC" -c -o src/typeck/typeck_f64_bits.o "$src"
  fi
}
ensure_cfg_eval_obj() {
  local o="src/lexer/cfg_eval.o"
  local ld_cmd="${LD:-ld}"
  if [ ! -f "$o" ] || [ "src/lexer/cfg_eval_gen.c" -nt "$o" ] || [ "seeds/cfg_eval_link_alias.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc/ld src/lexer/cfg_eval.o <- cfg_eval_gen.c + cfg_eval_link_alias.from_x.c"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o src/lexer/cfg_eval_x.o src/lexer/cfg_eval_gen.c
  sh scripts/cc_inc_tu.sh seeds/cfg_eval_link_alias.from_x.c src/lexer/cfg_eval_link_alias.o
  "$ld_cmd" $LD_RELFLAGS -r -o "$o" src/lexer/cfg_eval_x.o src/lexer/cfg_eval_link_alias.o
  fi
}
ensure_runtime_io_abi_obj
ensure_runtime_link_abi_obj
ensure_runtime_pipeline_abi_obj
ensure_runtime_driver_obj
ensure_runtime_driver_strict_glue_stubs_obj
ensure_runtime_asm_build_obj
ensure_x_seed_bridge_obj
ensure_ast_pool_l5_bridge_obj
ensure_asm_experimental_symbol_bridge_obj
ensure_lsp_codegen_extern_obj
ensure_lsp_pipeline_ctx_obj
# PLATFORM: SHARED — match build_xlang_asm ensure_lsp_diag_pipeline_sizes_obj (seed weak sizes).
ensure_lsp_diag_pipeline_sizes_obj() {
  local o="src/lsp/lsp_diag_pipeline_sizes.o"
  if [ ! -f "$o" ] || [ "seeds/lsp_diag_pipeline_sizes_weak.from_x.c" -nt "$o" ]; then
  strict_glue_info "cc_inc_tu seeds/lsp_diag_pipeline_sizes_weak.from_x.c -> $o"
  sh scripts/cc_inc_tu.sh seeds/lsp_diag_pipeline_sizes_weak.from_x.c "$o" -I. -Iinclude -Isrc
  fi
}
ensure_lsp_diag_pipeline_sizes_obj
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ensure_backend_seed_mega_fallback_obj
fi
ensure_typeck_f64_bits_obj
ensure_cfg_eval_obj

ST_X86_64_ENC_FALLBACK=""
ensure_backend_x86_64_enc_c_obj
if [ -f "$BUILD_DIR/backend_x86_64_enc_c.o" ]; then
  ST_X86_64_ENC_FALLBACK="$BUILD_DIR/backend_x86_64_enc_c.o"
fi
ST_STRICT_COMPANIONS="$ST_STRICT_COMPANIONS $ST_X86_64_ENC_FALLBACK"

# G.7: match product g05_relink_env — async_asm_pool (abi CPS layout) + Darwin
# backend_arm64_enc_c (strong arch_arm64_enc_* overriding weak -1 stubs).
# Missing these left strict_glue final link UNDEF after 0-symbol lift.
# PLATFORM: SHARED async; MACOS arm64 enc required on Darwin product path.
ensure_async_asm_pool_obj() {
  local o="src/async/async_asm_pool.o"
  local src="seeds/async_asm_pool.from_x.c"
  if [ ! -f "$o" ] || [ "$src" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- $src (product DRIVER_SEED_SUPPORT twin)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$src" -o "$o" || return 1
  fi
  return 0
}
ensure_backend_arm64_enc_c_obj() {
  local o="src/asm/backend_arm64_enc_c.o"
  local src="seeds/backend_arm64_enc_c.from_x.c"
  [ -f "$src" ] || return 1
  if [ ! -f "$o" ] || [ "$src" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- $src (Darwin arch_arm64_enc_* strong)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$src" -o "$o" || return 1
  fi
  return 0
}
ensure_async_asm_pool_obj
ST_STRICT_COMPANIONS="$ST_STRICT_COMPANIONS src/async/async_asm_pool.o"
case "$(uname -s)-$(uname -m 2>/dev/null)" in
Darwin-arm64|Darwin-aarch64)
  if ensure_backend_arm64_enc_c_obj; then
  ST_STRICT_COMPANIONS="$ST_STRICT_COMPANIONS src/asm/backend_arm64_enc_c.o"
  fi
  ;;
esac

# PLATFORM: SHARED — RT Cap residual slices (Makefile RT_SEED_SLICE_OBJS); product
# g05/build_xlang_asm links them via asm_bootstrap_support_extra_link. runtime_driver_abi
# needs driver_preamble_fs_path_lines{,_n} from rt_preamble.o.
ensure_rt_seed_slice_objs() {
  local pair src o
  for pair in \
    "seeds/rt_arena_buf.from_x.c:src/runtime/rt_arena_buf.o" \
    "seeds/rt_emit_state.from_x.c:src/runtime/rt_emit_state.o" \
    "seeds/rt_preamble.from_x.c:src/runtime/rt_preamble.o" \
    "seeds/rt_stack.from_x.c:src/runtime/rt_stack.o" \
    "seeds/rt_parse_diag.from_x.c:src/runtime/rt_parse_diag.o"; do
  src="${pair%%:*}"
  o="${pair##*:}"
  if [ ! -f "$o" ] || [ "$src" -nt "$o" ]; then
  strict_glue_info "cc -c $o <- $src (RT seed slice)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$src" -o "$o"
  fi
  done
}
ensure_rt_seed_slice_objs
ST_RT_SEED_SLICES="src/runtime/rt_arena_buf.o src/runtime/rt_emit_state.o src/runtime/rt_preamble.o src/runtime/rt_stack.o src/runtime/rt_parse_diag.o"
# PLATFORM: SHARED — process_xlang_argc/argv_get authority (product asm_bootstrap_support_extra_link).
if [ ! -f runtime_process_argv.o ] || [ seeds/runtime_process_argv.from_x.c -nt runtime_process_argv.o ]; then
  strict_glue_info "cc -c runtime_process_argv.o <- seeds/runtime_process_argv.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_process_argv.from_x.c -o runtime_process_argv.o
fi
ST_RT_SEED_SLICES="$ST_RT_SEED_SLICES runtime_process_argv.o"

strict_glue_info "linking xlang_asm.strict_glue (glue_standalone + build_asm pipeline.o ...)"
dbg_event C "begin link-phase setup"
# Linux strict 链：runtime_panic + liburing（与 build_xlang_asm PIPELINE_LIBS 一致）。
# NL-07 L10: when bootstrap_wants_nostdlib, drop -lpthread/-lm/-lc (G.7 shared policy).
ST_RUNTIME_PANIC=""
ST_PIPELINE_LIBS="-lm -lc"
if [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
  _arch="$(uname -m 2>/dev/null)"
  _panic_src=""
  if [ "$_arch" = "x86_64" ] && [ -f src/asm/runtime_panic_x86_64.s ]; then
  _panic_src="src/asm/runtime_panic_x86_64.s"
  elif { [ "$_arch" = "aarch64" ] || [ "$_arch" = "arm64" ]; } && [ -f seeds/runtime_panic_arm64.from_x.c ]; then
  _panic_src="seeds/runtime_panic_arm64.from_x.c"
  elif [ -f seeds/runtime_panic.from_x.c ]; then
  _panic_src="seeds/runtime_panic.from_x.c"
  fi
  if [ -n "$_panic_src" ] && { [ ! -f runtime_panic.o ] || [ "$_panic_src" -nt runtime_panic.o ]; }; then
  strict_glue_info "cc runtime_panic.o <- $_panic_src"
  if [ "${_panic_src##*.}" = "s" ]; then
  pure_as_compile runtime_panic.o "$_panic_src"
  else
  sh scripts/cc_inc_tu.sh "$_panic_src" runtime_panic.o
  fi
  fi
  [ -f runtime_panic.o ] && ST_RUNTIME_PANIC="runtime_panic.o"
  # shellcheck disable=SC1091
  . scripts/bootstrap_nostdlib_shared.sh
  if bootstrap_wants_nostdlib; then
  # PLATFORM: LINUX — product nostdlib tail (same freestanding/stubs/atoi as g05/crt0).
  strict_glue_info "NL-07 L10 strict: nostdlib tail (no -lc/-lpthread)"
  ST_PIPELINE_LIBS="$(bootstrap_nostdlib_link_flags) $(bootstrap_nostdlib_extra_objs)"
  else
  ST_PIPELINE_LIBS="-lpthread -lm -lc"
  if have_link_liburing; then
  ST_PIPELINE_LIBS="-luring $ST_PIPELINE_LIBS"
  else
  strict_glue_warn "liburing unavailable; linking without -luring"
  fi
  fi
fi
set +e
ST_ALLOW_MULTIDEF="-Wl,--allow-multiple-definition"
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ST_ALLOW_MULTIDEF="-Wl,-multiply_defined -Wl,suppress"
fi
# PLATFORM: DARWIN — single stubs authority = filtered darwin.o (omit asm_driver_*).
# Linux keeps full build_asm stubs (GNU ld --allow-multiple-definition). Never link
# both full stubs.o and bstrict_strict_glue_stubs_darwin.o (G.7 dual-authority ban).
ST_STRICT_GLUE_STUBS_O="$BUILD_DIR/runtime_driver_strict_glue_stubs.o"
if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  if ensure_strict_glue_darwin_stubs_filt_obj; then
  ST_STRICT_GLUE_STUBS_O="$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o"
  strict_glue_info "Darwin final link: stubs = bstrict_strict_glue_stubs_darwin.o (filt; omit asm_driver_*)"
  else
  strict_glue_warn "Darwin stubs filt failed; linking unfiltered build_asm stubs.o (may multiply_define)"
  fi
fi
dbg_event B "invoke final link"
LINK_START_S=$(date +%s 2>/dev/null || echo 0)
# PLATFORM: SHARED — G-02e link line: no runtime_abi/proc_abi/std_fs_shim .o (see build_xlang_asm.sh).
"$CC" ${CFLAGS} $ST_ALLOW_MULTIDEF -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm.strict_glue \
  src/asm/runtime_asm_build.o \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_driver.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_abi.o \
  src/runtime_pipeline_abi.o \
  "$ST_STRICT_GLUE_STUBS_O" \
  $ST_RUNTIME_PANIC \
  ${ST_GLUE_OBJ:+"$ST_GLUE_OBJ"} \
  $ST_MINIMAL_GLUE_COMPANION \
  $ST_RT_SEED_SLICES \
  $ASM_TRY_OBJS \
  $PARSER_ASM_PARTIAL \
  "$PARSER_ASM_THIN_C" \
  $ST_AST_BARE_ALIAS \
  $ST_WPO_ALIAS \
  $ST_RUNTIME_PARTIAL \
  src/asm/asm_experimental_symbol_bridge.o \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $ST_TYPECK_LSP_STUB \
  \
  $ST_PREPROCESS_SEED \
  $ST_SEED_PARSER_TCK \
  $ST_STRICT_COMPANIONS \
  "$LSP_DIAG_SEED_O" \
  $ST_LSP_X_OBJS \
  \
  src/lsp/lsp_diag_pipeline_ctx.o \
  src/lsp/lsp_diag_pipeline_sizes.o \
  $ST_LAYOUT_PARTIAL \
  $ST_PARSER_X_TAIL \
  $ST_PIPELINE_X_TAIL \
  $ST_TYPECK_X_TAIL \
  $ST_PIPELINE_LIBS 2>"$BUILD_DIR/.relink_strict_glue_err" &
LINK_PID=$!
dbg_event B "final link pid=$LINK_PID"
dbg_watch_pid "$LINK_PID" "final link" "$LINK_START_S" &
WATCH_PID=$!
wait "$LINK_PID"
RC=$?
kill "$WATCH_PID" >/dev/null 2>&1 || true
wait "$WATCH_PID" >/dev/null 2>&1 || true
dbg_event B "final link returned rc=$RC"
set -e
if [ "$RC" -ne 0 ]; then
  strict_glue_error "final link failed (rc=$RC)"
  tail -n 12 "$BUILD_DIR/.relink_strict_glue_err" 2>/dev/null | sed 's/^/ /' || true
  exit "$RC"
fi
strict_glue_info "OK -> xlang_asm.strict_glue ($(nm xlang_asm.strict_glue 2>/dev/null | grep -c ' T .*asm_skip_heavy_module_func_body' || echo 0) asm_skip_heavy)"
strict_glue_info "验证: XLANG_S2_EMIT_HEAVY_COMPILER=./xlang_asm.strict_glue ./tests/run-s2-typeck-emit-heavy.sh"
strict_glue_info "WPO dogfood 编 build_asm/*.x 优先 ./xlang_asm.experimental（含 pipeline_x.o）；用户 -o 用 strict_glue"
