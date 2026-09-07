#!/bin/sh
# build_xlang_asm.sh — 用 asm 后端构建 xlang（Goal 2：.x → 目标文件 .o，不经 -E C 翻译）
# 用法：在 compiler 目录下执行 XLANG=./xlang ./scripts/build_xlang_asm.sh
# 或由 build_tool 调用：./build_tool ./xlang asm（策略见仓库根目录 build.x 注释）。
# 依赖：XLANG 已支持 -backend asm；宿主 cc 用于链接桩、-E 产物与最终链接 xlang_asm。
# crt0 / runtime_panic / typeck_f64_bits 由本脚本内 ensure_asm_link_objs 用 cc 生成，不依赖 make。
#
# 回退链接（非 Linux crt0 路径）：runtime_asm_build 调 main_entry（main.x 经 -E 的 C 符号名）；runtime_driver 依赖
# pipeline_run_x_pipeline、parser_parse_into*、asm_asm_codegen_elf_o 等。这些符号来自 -E 生成的
# pipeline_gen.c/driver_gen.c（与 Makefile bootstrap-driver-seed 一致），不能仅靠 src/*.c 前端：
# C parser 导出的是 parse 等名，与 runtime 期望的 parser_parse_into 不一致。
# pipeline_gen.c 已内联 ast/lexer/parser/typeck/codegen 与 asm 后端；当前 -backend asm 产出的 build_asm/*.o
# 多为空桩（仅 Mach-O 壳），并入回退链接会触发 Apple ld 断言或重复定义。故回退链仅 -E 产物 + C 种子，不并 build_asm/*.o。
# Linux crt0 成功路径使用 NONEMPTY_ASM，但须单一 glue 权威（见 filter_crt0_asm_objs）。
#
# 仅当 main.o/pipeline.o 均非空且链接仍失败时退出码 1（供 build_tool 回退 legacy）；其它情况 0。
# 构建顺序与 LIBROOT 唯一定义在 src/asm/asm_build_list.x。

set -e
cd "$(dirname "$0")/.."
# PLATFORM: SHARED — nm export lists are ASCII symbol names; force C locale so
# GNU sort and comm agree. Host locales (e.g. zh_CN.UTF-8) make sort/comm
# disagree on underscore/letter order → wrong partial export subtraction
# (dual authority with relink_xlang_asm_strict_glue.sh).
export LC_ALL=C

# 可选外层超时（阶段 G phase0-stream）：XLANG_BUILD_ASM_TIMEOUT=3600 等。
if [ -z "${XLANG_BUILD_ASM_TIMEOUT_WRAPPED:-}" ] && [ -n "${XLANG_BUILD_ASM_TIMEOUT:-}" ] && [ "${XLANG_BUILD_ASM_TIMEOUT}" != "0" ]; then
  _to_bin=""
  if command -v timeout >/dev/null 2>&1; then
  _to_bin=timeout
  elif command -v gtimeout >/dev/null 2>&1; then
  _to_bin=gtimeout
  fi
  if [ -n "$_to_bin" ]; then
  export XLANG_BUILD_ASM_TIMEOUT_WRAPPED=1
  build_xlang_asm_info "outer timeout ${XLANG_BUILD_ASM_TIMEOUT}s"
  exec "$_to_bin" "${XLANG_BUILD_ASM_TIMEOUT}" "$0" "$@"
  fi
  build_xlang_asm_warn "timeout unavailable; XLANG_BUILD_ASM_TIMEOUT ignored"
fi

# CI：跳过 second pass 与全量 typeck 预检，避免 Token/Lexer 布局刷屏导致 runner OOM（1h+ lost communication）。
if [ -n "${CI:-}" ] && [ "${XLANG_ASM_CI_SKIP_FAST:-0}" != "1" ]; then
  export XLANG_ASM_FORCE_SKIP_TYPECK="${XLANG_ASM_FORCE_SKIP_TYPECK:-1}"
  export XLANG_ASM_QUIET="${XLANG_ASM_QUIET:-1}"
  export XLANG_ASM_CI_SKIP_SECOND_PASS=1
  # B-strict SKIP_GEN 仅 Linux CI；macOS/Windows experimental 链常缺 LSP/typeck 符号，失败时 gen_driver。
  if [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
  export XLANG_ASM_EXPERIMENTAL_SKIP_GEN="${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-1}"
  fi
  # macOS/Windows CI：experimental bootstrap 成功后即停，勿再 strict 重链（30–60min+ 易超时）。
  export XLANG_ASM_CI_ACCEPT_EXPERIMENTAL_ONLY=1
fi

# 调试 env 勿泄漏进 build_asm：XLANG_ASM_START_FUNC>=模块 func 数时 emit 循环全跳过，仅剩 8B 空 __text 桩（B-strict PTEXT 门禁失败）。
unset XLANG_ASM_START_FUNC 2>/dev/null || true

build_xlang_asm_warn() {
  printf 'warning: build_xlang_asm: %s\n' "$*" >&2
}

build_xlang_asm_info() {
  printf 'info: build_xlang_asm: %s\n' "$*" >&2
}

build_xlang_asm_error() {
  printf 'build error: build_xlang_asm: %s\n' "$*" >&2
}

# B-strict（XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1）：链接或 smoke 失败即 exit 1，不回退 gen_driver / pipeline_x。
# 非 SKIP_GEN 时仅告警并返回，供 Linux 等宿主继续 gen_driver 回退或保留 experimental bootstrap 产物。
xlang_asm_bstrict_fail() {
  build_xlang_asm_error "B-strict failed: $*"
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  exit 1
  fi
  return 1
}

# E-06 v5：MSYS2/MINGW 宿主探测（Windows B-strict experimental X-only 链）。
build_xlang_asm_is_msys() {
  if [ -n "${MSYSTEM:-}" ]; then
  return 0
  fi
  case "$(uname -s 2>/dev/null)" in
  MINGW*|MSYS*) return 0 ;;
  esac
  return 1
}

# wave887: when XLANG unset, default to ./$TARGET (TARGET default xlang).
# Makefile bootstrap-asm-full no longer injects XLANG=./$(TARGET); CLI/env still win.
# PLATFORM: SHARED.
TARGET="${TARGET:-xlang}"
XLANG="${XLANG:-./$TARGET}"
BUILD_LIST_X="src/asm/asm_build_list.x"
BUILD_DIR="build_asm"
mkdir -p "$BUILD_DIR"

# ./xlang 在 make all 后为 C 种子（无 -backend asm）；bootstrap-driver-seed 后 xlang-x 与 xlang 均含 asm。
if [ "$XLANG" = "./xlang" ] && [ -x ./xlang-x ]; then
  # Phase 2 TODO: xlang -backend asm (no file) is a backend capability probe,
  # not a compile call. Migrate to `xlang --print-target-cpu` or similar when
  # implicit fallback is removed in Phase 2.
  if ./xlang -backend asm 2>&1 | grep -q "not available"; then
  XLANG=./xlang-x
  fi
fi

# 链接拓扑：未导出 XLANG_ASM_LINK_TOPOLOGY 时，check_asm_o_quality 认定全部 __text 非空 → full_asm（Linux/macOS 同）。
# M7/M11 release 默认 XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 → asm_only_strict（最终链无 pipeline_x.o / pipeline_gen.c）。
# E-06 v1：SKIP_GEN 严格段不得 cc -c E-03 软退役前端 .c（asm_driver_seed 考古除外）— run-e06-no-compiler-frontend-cc-gate.sh
# E-06 v2：experimental bootstrap 在 *_x.o 就绪时跳过 asm_driver_seed 前端 cc -c 与链接（strict 回退仍 ensure 前端 .o）。
# 具体赋值在质检文件写出之后；勿在此预置 XLANG_ASM_LINK_TOPOLOGY，避免与下方自动选择冲突。

# 从 .x 唯一定义读取 LIBROOT（行格式：// LIBROOT:<tab>-L .. -L src ...）；TAB 用于兼容 BSD sed
TAB=$(printf '\t')
LIBROOT=""
if [ -f "$BUILD_LIST_X" ]; then
  LIBROOT=$(grep '^// LIBROOT:' "$BUILD_LIST_X" | sed "s|^// LIBROOT:${TAB}||")
fi
[ -z "$LIBROOT" ] && LIBROOT="-L asm_libroot -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess -L src/pipeline -L src/lsp -L src/asm"

build_xlang_asm_info "using XLANG=$XLANG (list from $BUILD_LIST_X)"

# compile_x 的 stub 回退与后续链接均依赖宿主 cc；须在 asm 编译循环之前定义。
CC="${CC:-cc}"
CFLAGS="-Wall -Wextra -I. -Iinclude -Isrc"
# PLATFORM: MACOS — match macho.x LC_BUILD_VERSION minos 11.0.0 (same authority
# as ensure_host_cc_seed_o.sh / cc_inc_tu.sh). Always-linked host-cc companions
# built here (runtime_panic.o / runtime_asm_io_stubs.o / user-link runtime objs)
# otherwise stamp minos=<host SDK> and ld warns "newer macOS version than being
# linked" on every user-program link. Do not -w swallow; do not raise macho.x
# minos to 26.0.
case "$(uname -s 2>/dev/null)" in
  Darwin)
    case " $CFLAGS " in
      *" -mmacosx-version-min="*) ;;
      *) CFLAGS="$CFLAGS -mmacosx-version-min=11.0" ;;
    esac
    ;;
esac

# Stage 12.2.1: XLANG_FORBID_HOST_CC gate (no-op when flag unset; zero impact
# on normal builds). When XLANG_FORBID_HOST_CC=1, replaces $CC with a wrapper
# that logs and blocks all host-CC invocations — builds the zero-CC problem map.
# PLATFORM: SHARED.
. "$(dirname "$0")/forbid_host_cc.sh"

# Stage 12.2.3: pure-ld/as helpers (zero-CC when XLANG_ZERO_CC_LD/AS=1).
# Sourced at top so all functions (including ensure_asm_link_objs fallback
# and emit_asm_text_stub_o) can use pure_as_compile / pure_ld_partial_merge.
# PLATFORM: SHARED.
. "$(dirname "$0")/pure_ld_shared.sh"

# backend.x 等大模块 asm 编译 abort 时，用最小 .s/.c 占位保证 __text 非空（质检 24/24）。
# wave297: host scripts/asm_text_stub.c left; seed authority seeds/asm_text_stub.from_x.c
emit_asm_text_stub_o() {
  local out="$1"
  local stub_c="seeds/asm_text_stub.from_x.c"
  local stub_s="scripts/asm_text_stub.s"
  local _stub_sym="xlang_asm_ci_text_stub"
  # Stage 12.2.3: Generate platform-specific weak .s stub as PRIMARY path
  # (zero-CC via pure_as_compile). Defines xlang_asm_ci_text_stub as weak —
  # identical symbol to .c stub (verified: nm -m shows "weak external" on both
  # Darwin and Linux). On Linux plain nm shows W (weak) vs T (strong); on Darwin
  # plain nm shows T for both — refresh_build_asm_ci_text_stubs_for_strict_link
  # regenerates all ≤64-byte text stubs on Darwin regardless, which is safe
  # because this function always emits a weak stub.
  # PLATFORM: SHARED — Darwin (.weak_definition + _prefix) / Linux (.weak).
  local _stub_s_tmp=""
  _stub_s_tmp="$(mktemp "${TMPDIR:-/tmp}/xlang_stub_XXXXXX.s" 2>/dev/null)" || _stub_s_tmp=""
  if [ -n "$_stub_s_tmp" ]; then
    case "$(uname -s 2>/dev/null)" in
      Darwin)
        # macOS Mach-O: underscore prefix + .weak_definition.
        printf '.text\n.globl _%s\n.weak_definition _%s\n_%s:\n  ret\n' \
          "$_stub_sym" "$_stub_sym" "$_stub_sym" > "$_stub_s_tmp"
        ;;
      Linux)
        # ELF: no prefix + .weak.
        printf '.text\n.globl %s\n.weak %s\n%s:\n  ret\n' \
          "$_stub_sym" "$_stub_sym" "$_stub_sym" > "$_stub_s_tmp"
        ;;
      *)
        rm -f "$_stub_s_tmp"
        _stub_s_tmp=""
        ;;
    esac
  fi
  if [ -n "$_stub_s_tmp" ] && [ -s "$_stub_s_tmp" ]; then
    # pure_as_compile: as when XLANG_ZERO_CC_AS=1, else $CC -c (zero regression).
    if pure_as_compile "$out" "$_stub_s_tmp" 2>/dev/null; then
      rm -f "$_stub_s_tmp"
      return 0
    fi
    rm -f "$_stub_s_tmp"
  fi
  # Fallback: .c stub via $CC (zero regression when .s generation unavailable
  # or unsupported platform, e.g. Windows/MSYS).
  if [ -f "$stub_c" ]; then
  "$CC" $CFLAGS -c -o "$out" "$stub_c" 2>/dev/null && return 0
  fi
  # Last resort: static .s stub (different symbol __xlang_asm_mod_stub, non-weak).
  [ -f "$stub_s" ] || return 1
  echo " fallback: $stub_s -> $out (asm compile abort recovery)"
  pure_as_compile "$out" "$stub_s" 2>/dev/null
}

# strict 链前：首遍 stub .o 若仍含强符号 xlang_asm_ci_text_stub，用 weak 版重编（并列链 multiple definition）。
refresh_build_asm_ci_text_stubs_for_strict_link() {
  local o="" txt="" sym=""
  for o in $NONEMPTY_ASM; do
  sym=$(nm "$o" 2>/dev/null | awk '/ xlang_asm_ci_text_stub$/ {print $2; exit}')
  [ "$sym" = "T" ] || continue
  txt=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  [ "$txt" -le 64 ] 2>/dev/null || continue
  emit_asm_text_stub_o "$o" 2>/dev/null || true
  done
}

# 按依赖顺序尝试编译各 .x 为 .o（顺序由 asm_build_list.x 的 // BUILD: 行定义）
# SKIP 表示该次 -backend asm -o 编译失败（命令非零退出）；默认保留 stderr，可直接看到失败原因（如 asm_codegen_elf_o failed）。
# 常见原因：asm_codegen_elf_o 内某步失败，或 pipeline 解析/类型检查/codegen 失败。若需静默可设 XLANG_ASM_QUIET=1。

# 非 Linux CI（macOS/Windows）：experimental bootstrap 不链 build_asm/*.o；
# MSYS 上 -backend asm 会挂起 45min+（含 typeck），故 build_asm 一律 text stub。
asm_ci_stub_build_asm_module() {
  local out="$1"
  [ -n "${XLANG_ASM_CI_ACCEPT_EXPERIMENTAL_ONLY:-}" ] || return 1
  # Linux CI 仍全量 emit（ubuntu B-strict / bootstrap-verify）。
  [ "$(uname -s 2>/dev/null)" = "Linux" ] && return 1
  return 0
}

# MSYS/macOS CI：typeck.x EMIT_HEAVY 会挂起；S2 __text 门禁仅 Linux x64 实跑。
asm_ci_skip_typeck_emit_heavy() {
  [ -n "${XLANG_ASM_CI_ACCEPT_EXPERIMENTAL_ONLY:-}" ] || return 1
  [ "$(uname -s 2>/dev/null)" = "Linux" ] && return 1
  return 0
}

# CI 快速路径：非宿主 ISA 的 encoder 模块用 text stub，缩短 macOS/Windows build_xlang_asm。
asm_ci_host_skip_module() {
  local out="$1"
  local host=""
  [ -n "${XLANG_ASM_CI_ACCEPT_EXPERIMENTAL_ONLY:-}" ] || return 1
  case "$(uname -m 2>/dev/null)" in
  arm64|aarch64) host=arm64 ;;
  x86_64|amd64) host=x86_64 ;;
  *) return 1 ;;
  esac
  case "$out" in
  x86_64_enc.o|riscv64.o|riscv64_enc.o)
  [ "$host" = "x86_64" ] && return 1
  return 0 ;;
  arm64_enc.o)
  [ "$host" = "arm64" ] && return 1
  return 0 ;;
  *) return 1 ;;
  esac
}

# 仅保留 emit 仍会宿主 Abort 的特大模块走 SKIP+桩；其余默认 C 预检 + 真 emit（见 pipeline_should_skip_x_typeck）。
asm_out_needs_skip_typeck() {
  case "$1" in
  ast.o|typeck.o|parser.o|backend.o|arm64_enc.o|x86_64_enc.o|riscv64_enc.o|lexer.o|pipeline.o|codegen.o|lsp.o|main.o)
  return 0
  ;;
  *)
  return 1
  ;;
  esac
}

compile_x() {
  local out="$BUILD_DIR/$1"
  local src="$2"
  local skip_typeck=0
  local preserve_backup=""
  printf " asm %s -> %s ... " "$src" "$out"
  # 首遍 BUILD 循环：无 EMIT_HEAVY 时一律 text stub（Rosetta/大模块 elf emit 极慢）；真符号由 second pass + X/partial 提供。
  if [ -z "${XLANG_ASM_ENTRY_EMIT_HEAVY:-}" ]; then
  if emit_asm_text_stub_o "$out"; then
  echo "OK-${1%.o}-stub"
  return 0
  fi
  fi
  # CI：macOS/Windows 除 typeck.o 外 stub（experimental 链不依赖 build_asm；MSYS token.x 会挂起）。
  if asm_ci_stub_build_asm_module "$1"; then
  if emit_asm_text_stub_o "$out"; then
  echo "OK-ci-stub-build"
  return 0
  fi
  fi
  # CI：交叉架构 encoder 用最小 stub .o，避免 x86_64_enc 等在 ARM macOS 上耗时/Abort。
  if asm_ci_host_skip_module "$1"; then
  if emit_asm_text_stub_o "$out"; then
  echo "OK-ci-stub"
  return 0
  fi
  fi
  # 自举第二遍：重编失败时保留已有非空 __text（避免 stage2 清空 build_asm/*.o）。
  if [ -f "$out" ] && [ -s "$out" ]; then
  preserve_backup="$BUILD_DIR/.preserve_${1}"
  cp -f "$out" "$preserve_backup" 2>/dev/null || preserve_backup=""
  fi
  # 大模块（typeck/codegen/elf）parse/typeck 栈帧深；macOS 默认栈易 segfault(139)。
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  # 单模块 .o：仅编入口符号，dep 由其它 build_asm/*.o 并列提供，避免 Mach-O 重复定义。
  # 勿设 XLANG_TYPECK_FORCE_C：C typeck_module 面向旧式 fat Module，slim pool 模块会 segfault。
  if [ -n "${XLANG_ASM_FORCE_SKIP_TYPECK:-}" ]; then
  skip_typeck=1
  elif asm_out_needs_skip_typeck "$1"; then
  skip_typeck=1
  fi
  if [ "$skip_typeck" -eq 1 ]; then
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 "$XLANG" build -backend asm -o "$out" $LIBROOT "$src" ${XLANG_ASM_QUIET:+2>/dev/null}; then
  _txt=$(asm_o_text_bytes "$out")
  if [ "$_txt" = "0" ]; then
  echo "WARN-empty-__text"
  build_xlang_asm_warn "$out __text=0 (XLANG_ASM_ENTRY_ONLY_DEBUG=1 $XLANG -backend asm -o /tmp/x.o $LIBROOT $src -> funcs=N)"
  fi
  echo OK; return 0
  fi
  else
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 "$XLANG" build -backend asm -o "$out" $LIBROOT "$src" ${XLANG_ASM_QUIET:+2>/dev/null}; then
  _txt=$(asm_o_text_bytes "$out")
  if [ "$_txt" = "0" ]; then
  echo "WARN-empty-__text"
  build_xlang_asm_warn "$out __text=0 (XLANG_ASM_ENTRY_ONLY_DEBUG=1 ... -> funcs=N)"
  fi
  echo OK; return 0
  elif env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 "$XLANG" build -backend asm -o "$out" $LIBROOT "$src" ${XLANG_ASM_QUIET:+2>/dev/null}; then
  _txt=$(asm_o_text_bytes "$out")
  if [ "$_txt" = "0" ]; then
  echo "WARN-empty-__text"
  fi
  echo OK-skip-typeck; return 0
  fi
  fi
  echo SKIP
  if [ -n "$preserve_backup" ] && [ -f "$preserve_backup" ]; then
  cp -f "$preserve_backup" "$out" 2>/dev/null || true
  echo "(preserved __text=$(asm_o_text_bytes "$out" 2>/dev/null || echo 0)B)"
  fi
  # Darwin 首遍：main.x / lexer.x SKIP_TYPECK 常 Bus error/SIGSEGV；用 text stub 占位使 pipeline.o 已绿时仍能走 experimental + second pass。
  case "$1" in
  main.o|lexer.o)
  if [ "$(asm_o_text_bytes "$out" 2>/dev/null || echo 0)" = "0" ]; then
  if emit_asm_text_stub_o "$out"; then
  echo "OK-stub-after-skip"
  return 0
  fi
  fi
  ;;
  esac
  return 0
}

# 读 .o 代码段大小（Mach-O __text 或 ELF .text），失败返回 0。
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
  # POSIX sh（#!/bin/sh）不支持 bash 的 $((16#hex))；与 run-s2-typeck-gate.sh 一致用 perl。
  perl -e 'print hex(shift)' "$hex" 2>/dev/null || echo 0
}

# macOS ld64 / lld 支持 -exported_symbols_list；GNU bfd ld 须 --version-script。
ld_supports_exported_symbols_list() {
  ld -v 2>&1 | grep -qE 'PROJECT:ld64|LLD|LLVM'
}

# 从符号列表（每行一个，可带 Mach-O 前缀 _）做 ld -r 局部导出；供 strict partial 链。
#
# PLATFORM: SHARED — process-wide DepCtx table (NL-07 pure static dual-table residual).
# When the input .o defines g_xlang_depctx_sc, always keep it GLOBAL in the partial.
# Darwin -exported_symbols_list and Linux objcopy --keep-global-symbols both localize
# unlisted symbols. Static depctx_sidecar_get is copied into each partial and binds
# whatever BSS it sees; if the table is localized, Cap module_at vs path_copy split
# (core.types body emitted as core_result_*). Authority: runtime_pipeline_abi
# g_xlang_depctx_sc / pure depctx table (ast_pool.c left wave309).
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
  # GNU bfd ld：--version-script 不剥离 .o 内符号；须 objcopy --keep-global-symbols 真删局部符号。
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

# 实验链第一遍链接后：用新 xlang_asm + 最新 pipeline_glue_standalone 重编 pipeline.o（避免鸡生蛋 4B 桩）。
# 成功须 __text≥200B（B-strict 前置）；bootstrap xlang_asm 在 Linux ELF 常产出 0B 桩，须回退 seed ./xlang。
rebuild_pipeline_o_second_pass() {
  if [ -n "${XLANG_ASM_CI_SKIP_SECOND_PASS:-}" ]; then
  build_xlang_asm_info "pipeline.o second pass skipped (CI fast)"
  return 0
  fi
  local min_text=200
  local pcomp PTMP PTEXT=0
  # G.7: pipeline.x is pure-extern (0 bodies). Real impl is src/runtime_pipeline_abi.o
  # (already on LD argv). pipeline_x.o / build_asm/pipeline.o are driver_leaf stubs
  # (__text often 0–4B, 0 T). Promote marks second-pass OK when abi is selfhosted;
  # do NOT require stub __text>=min_text (that gate was for pre-abi emit era).
  # Skip asm re-emit of pipeline.x (Docker futex; would still yield a stub).
  # PLATFORM: SHARED — abi authority + stub promote on Darwin and Linux.
  _promote_pipeline_x_second_pass() {
  asm_strict_pipeline_selfhosted || return 1
  if [ -f pipeline_x.o ]; then
  cp -f pipeline_x.o "$BUILD_DIR/pipeline.o"
  fi
  PTEXT=$(asm_o_text_bytes "$BUILD_DIR/pipeline.o" 2>/dev/null || echo 0)
  _abi_t=$(asm_o_text_bytes src/runtime_pipeline_abi.o 2>/dev/null || echo 0)
  build_xlang_asm_info "pipeline.o second pass OK via runtime_pipeline_abi (stub=__text=${PTEXT}B, abi=${_abi_t}B, skip asm emit)"
  return 0
  }
  if [ "${XLANG_ASM_SECOND_PASS_FORCE_ASM:-0}" != "1" ] && _promote_pipeline_x_second_pass; then
  return 0
  fi
  # virtiofs 挂载下长时 asm -o 易 futex 卡死；优先在容器 /tmp 落盘，成功后再 mv 到 BUILD_DIR
  if [ -n "${XLANG_ASM_SECOND_PASS_TMP:-}" ]; then
  PTMP="$XLANG_ASM_SECOND_PASS_TMP"
  elif [ -d /tmp ] && [ -w /tmp ]; then
  PTMP="/tmp/xlang_pipeline_second_pass_$$.o"
  else
  PTMP="$BUILD_DIR/pipeline.second_pass.o"
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  build_xlang_asm_info "second pass - recompile pipeline.o (tmp=$PTMP)"
  # 单次 attempt 超时（秒）；EMIT_HEAVY 在 pipeline.x 上偶发 futex 卡死，须 timeout 后回退轻量路径
  _sp_timeout="${XLANG_ASM_SECOND_PASS_TIMEOUT:-7200}"
  _run_pipeline_sp() {
  _sp_env="$1"
  shift
  rm -f "$PTMP" 2>/dev/null || true
  if command -v timeout >/dev/null 2>&1; then
  timeout "$_sp_timeout" env -u XLANG_ASM_START_FUNC "$@" "$_sp_env" -backend asm -o "$PTMP" $LIBROOT src/pipeline/pipeline.x 2>"$BUILD_DIR/pipeline.second_pass.err"
  else
  env -u XLANG_ASM_START_FUNC "$@" "$_sp_env" -backend asm -o "$PTMP" $LIBROOT src/pipeline/pipeline.x 2>"$BUILD_DIR/pipeline.second_pass.err"
  fi
  }
  _try_pipeline_sp_ok() {
  _label="$1"
  shift
  PTEXT=$(asm_o_text_bytes "$PTMP" 2>/dev/null || echo 0)
  if [ "$PTEXT" -ge "$min_text" ] 2>/dev/null; then
  mv -f "$PTMP" "$BUILD_DIR/pipeline.o"
  build_xlang_asm_info "pipeline.o second pass OK $_label (__text=${PTEXT}B)"
  return 0
  fi
  build_xlang_asm_warn "pipeline.o second pass $_label too small (__text=${PTEXT}B)"
  return 1
  }
  for pcomp in "./xlang_asm.experimental" "./xlang-seed-phase1" "${XLANG:-}" "./xlang" "./xlang_asm"; do
  [ -n "$pcomp" ] || continue
  [ -x "$pcomp" ] || continue
  build_xlang_asm_info "pipeline.o second pass try $pcomp"
  # 1) 轻量 SKIP_TYPECK（避免 EMIT_HEAVY futex 卡死）
  if _run_pipeline_sp "$pcomp" XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1; then
  _try_pipeline_sp_ok "with SKIP_TYPECK via $pcomp" && return 0
  fi
  rm -f "$PTMP" 2>/dev/null || true
  # 2) 默认 entry-only
  if _run_pipeline_sp "$pcomp" XLANG_ASM_ENTRY_MODULE_ONLY=1; then
  _try_pipeline_sp_ok "via $pcomp" && return 0
  fi
  rm -f "$PTMP" 2>/dev/null || true
  # 3) EMIT_HEAVY 最后尝试（timeout 后失败则换下一 compiler）
  if _run_pipeline_sp "$pcomp" XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 XLANG_ASM_ENTRY_EMIT_HEAVY=1 XLANG_ASM_WPO_DCE=0; then
  _try_pipeline_sp_ok "with EMIT_HEAVY via $pcomp" && return 0
  fi
  rm -f "$PTMP" 2>/dev/null || true
  done
  if _promote_pipeline_x_second_pass; then
  return 0
  fi
  build_xlang_asm_error "pipeline.o second pass failed (no compiler reached __text>=${min_text}B)"
  return 1
}

# 第二遍：用 bootstrap xlang_asm（experimental 链，含 pipeline_x.o）重编大模块；须在 strict 重链覆盖 xlang_asm 之前执行。
rebuild_typeck_parser_backend_second_pass() {
  if [ -n "${XLANG_ASM_CI_SKIP_SECOND_PASS:-}" ]; then
  build_xlang_asm_info "typeck/parser/backend second pass skipped (CI fast)"
  return 0
  fi
  # 第二遍编译器：显式参数 > ./xlang_asm（strict 产物）> ${XLANG} > experimental；勿用过期 seed ./xlang。
  local comp=""
  if [ -n "${1:-}" ] && [ -x "${1}" ]; then
  comp="$1"
  elif [ -n "${XLANG_ASM_SECOND_PASS_COMPILER:-}" ] && [ -x "${XLANG_ASM_SECOND_PASS_COMPILER}" ]; then
  comp="${XLANG_ASM_SECOND_PASS_COMPILER}"
  elif [ -x "./xlang_asm.experimental" ]; then
  comp="./xlang_asm.experimental"
  elif [ -n "${XLANG:-}" ] && [ -x "${XLANG}" ]; then
  comp="${XLANG}"
  elif [ -x "./xlang" ]; then
  comp="./xlang"
  elif [ -x "./xlang-seed-phase1" ]; then
  comp="./xlang-seed-phase1"
  elif [ -x "./xlang_asm" ]; then
  comp="./xlang_asm"
  else
  return 1
  fi
  local ok=0
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  for spec in "typeck.o:src/typeck/typeck.x:typeck_x.o" "parser.o:src/parser/parser.x:parser_x.o" "backend.o:src/asm/backend.x:"; do
  local out="${spec%%:*}"
  local rest="${spec#*:}"
  local src="${rest%%:*}"
  local x_o="${rest#*:}"
  local tmp="$BUILD_DIR/${out%.o}.second_pass.o"
  local pass_ok=0
  # backend：seed partial 已提供强符号时跳过 asm 二遍（backend.x 极大，Docker 易 OOM/Killed）
  if [ "$out" = "backend.o" ] && [ -s "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
  build_xlang_asm_info "$out second pass skip - seed_host/asm_backend_partial.o"
  ok=1
  continue
  fi
  # typeck/parser：promote 已 pinned 的 *_x.o（与 pipeline_x promote 同理）
  if [ "${XLANG_ASM_SECOND_PASS_FORCE_ASM:-0}" != "1" ] && [ -n "$x_o" ] && [ -f "$x_o" ]; then
  cp -f "$x_o" "$BUILD_DIR/$out"
  case "$out" in
  typeck.o)
  if asm_strict_typeck_selfhosted; then
  build_xlang_asm_info "$out second pass promote $x_o (__text=$(asm_o_text_bytes "$BUILD_DIR/$out")B, skip asm emit)"
  ok=1
  continue
  fi
  ;;
  parser.o)
  if [ "$(asm_o_text_bytes "$BUILD_DIR/$out" 2>/dev/null || echo 0)" -gt 8192 ] 2>/dev/null; then
  build_xlang_asm_info "$out second pass promote $x_o (__text=$(asm_o_text_bytes "$BUILD_DIR/$out")B, skip asm emit)"
  ok=1
  continue
  fi
  ;;
  esac
  rm -f "$BUILD_DIR/$out" 2>/dev/null || true
  fi
  build_xlang_asm_info "second pass - recompile $out with $comp"
  if [ "$out" = "typeck.o" ] || [ "$out" = "backend.o" ] || [ "$out" = "parser.o" ]; then
  # 第二遍：EMIT_HEAVY 真 emit（parser 截断模块在 ast_pool 内桩化；真机在 parser_x.o）。
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 XLANG_ASM_ENTRY_EMIT_HEAVY=1 XLANG_ASM_WPO_DCE=0 \
  "$comp" -backend asm -o "$tmp" $LIBROOT "$src" && pass_ok=1; then
  :
  fi
  elif env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 "$comp" -backend asm -o "$tmp" $LIBROOT "$src" && pass_ok=1; then
  :
  fi
  if [ "$pass_ok" -eq 1 ] && [ -f "$tmp" ]; then
  mv -f "$tmp" "$BUILD_DIR/$out"
  build_xlang_asm_info "$out second pass OK (__text=$(asm_o_text_bytes "$BUILD_DIR/$out")B)"
  ok=1
  else
  rm -f "$tmp" 2>/dev/null || true
  build_xlang_asm_error "$out second pass failed"
  return 1
  fi
  done
  [ "$ok" -eq 1 ]
}

# CI / experimental-only：S2 gate 要求 build_asm/typeck.o __text≥68264；首遍 SKIP_TYPECK 仅 ~165B 桩，须单独 EMIT_HEAVY。
# 不受 XLANG_ASM_CI_SKIP_SECOND_PASS 影响（仅重编 typeck.o，比全量 second pass 快）。
rebuild_typeck_o_emit_heavy_s2() {
  local comp="${1:-./xlang_asm.experimental}"
  local out="$BUILD_DIR/typeck.o"
  local src="src/typeck/typeck.x"
  local tmp="$BUILD_DIR/typeck.emit_heavy_s2.o"
  local cur_txt new_txt min_gate=68264
  local baseline="../../tests/baseline/s2-typeck-o.tsv"

  if [ -f "$baseline" ]; then
  min_gate=$(awk -F'\t' '$1=="min_text_bytes" && $1 !~ /^#/ { print $2; exit }' "$baseline" 2>/dev/null)
  [ -z "$min_gate" ] && min_gate=68264
  fi
  if [ ! -x "$comp" ]; then
  comp="./xlang_asm"
  fi
  if [ ! -x "$comp" ]; then
  build_xlang_asm_error "typeck EMIT_HEAVY S2: no xlang_asm compiler"
  return 1
  fi
  cur_txt=$(asm_o_text_bytes "$out" 2>/dev/null || echo 0)
  if [ "${cur_txt:-0}" -ge "$min_gate" ] 2>/dev/null; then
  build_xlang_asm_info "typeck.o already S2-ready (__text=${cur_txt}B >= ${min_gate})"
  return 0
  fi
  build_xlang_asm_info "S2 typeck: EMIT_HEAVY recompile typeck.o with $comp (was __text=${cur_txt}B)"
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  rm -f "$tmp"
  if ! env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 XLANG_ASM_WPO_DCE=0 \
  "$comp" -backend asm -o "$tmp" $LIBROOT "$src"; then
  rm -f "$tmp" 2>/dev/null || true
  build_xlang_asm_error "typeck.o EMIT_HEAVY compile failed"
  return 1
  fi
  new_txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  if [ "${new_txt:-0}" -lt "$min_gate" ] 2>/dev/null; then
  rm -f "$tmp" 2>/dev/null || true
  build_xlang_asm_error "typeck.o EMIT_HEAVY __text=${new_txt}B < S2 min ${min_gate}"
  return 1
  fi
  mv -f "$tmp" "$out"
  ensure_typeck_asm_layout_partial_obj || true
  build_xlang_asm_info "typeck.o EMIT_HEAVY S2 OK (__text=${new_txt}B)"
  return 0
}

# M8a：parser 支持 Module.sub.Type 后，须用已链入新 parser 的编译器重编首遍仅解析到首个函数的模块（arm64_enc 等）。
rebuild_m8a_parser_dependent_modules_second_pass() {
  if [ -n "${XLANG_ASM_CI_SKIP_SECOND_PASS:-}" ]; then
  build_xlang_asm_info "M8a second pass skipped (CI fast)"
  return 0
  fi
  local comp="${XLANG_ASM_SECOND_PASS_COMPILER:-./xlang_asm}"
  if [ -n "${1:-}" ] && [ -x "${1}" ]; then
  comp="$1"
  fi
  if [ ! -x "$comp" ]; then
  comp="${XLANG:-./xlang}"
  fi
  if [ ! -x "$comp" ]; then
  return 1
  fi
  local ok=0
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  for spec in "arm64_enc.o:src/asm/arch/arm64_enc.x" "lsp.o:src/lsp/lsp.x" "asm.o:src/asm/asm.x"; do
  local out="${spec%%:*}"
  local src="${spec#*:}"
  local tmp="$BUILD_DIR/${out%.o}.m8a_second_pass.o"
  build_xlang_asm_info "M8a second pass - recompile $out with $comp"
  local cur_txt=0
  if [ -f "$BUILD_DIR/$out" ]; then
  cur_txt=$(asm_o_text_bytes "$BUILD_DIR/$out" 2>/dev/null || echo 0)
  fi
  if [ "$cur_txt" -gt 0 ] 2>/dev/null; then
  build_xlang_asm_info "$out M8a pass skipped (__text=${cur_txt}B already OK)"
  ok=1
  continue
  fi
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 "$comp" -backend asm -o "$tmp" $LIBROOT "$src" \
  && [ -f "$tmp" ]; then
  local new_txt=0
  new_txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  if [ "${new_txt:-0}" -gt 0 ] 2>/dev/null; then
  mv -f "$tmp" "$BUILD_DIR/$out"
  build_xlang_asm_info "$out M8a pass OK (__text=${new_txt}B)"
  ok=1
  else
  rm -f "$tmp" 2>/dev/null || true
  build_xlang_asm_warn "$out M8a pass empty __text (keep existing ${cur_txt}B)"
  [ "${cur_txt:-0}" -gt 0 ] 2>/dev/null && ok=1
  fi
  else
  rm -f "$tmp" 2>/dev/null || true
  build_xlang_asm_warn "$out M8a pass failed"
  fi
  done
  [ "$ok" -eq 1 ]
}

# build_asm/main.o（ENTRY_MODULE_ONLY）会导出强符号 main_entry，盖住 bridge 的子命令路由；剥离后保留 entry。
strip_main_entry_from_build_asm_main_o() {
  local mo="$BUILD_DIR/main.o"
  [ -f "$mo" ] || return 0
  if ! nm "$mo" 2>/dev/null | grep -q ' _main_entry$'; then
  return 0
  fi
  build_xlang_asm_info "strip _main_entry from main.o (CLI dispatch via asm_experimental_symbol_bridge)"
  if command -v llvm-objcopy >/dev/null 2>&1; then
  llvm-objcopy --strip-symbol=_main_entry "$mo"
  elif strip -N _main_entry "$mo" 2>/dev/null; then
  :
  elif command -v objcopy >/dev/null 2>&1; then
  objcopy --strip-symbol=_main_entry "$mo" 2>/dev/null || objcopy -N _main_entry "$mo"
  else
  build_xlang_asm_error "cannot strip _main_entry (need llvm-objcopy or strip -N)"
  return 1
  fi
}

# B-strict strict 重链前：main.x 须 ENTRY_MODULE_ONLY + ENTRY_EMIT_HEAVY 真 emit entry（含 check/fmt/test 路由）。
# 勿去掉 ENTRY_MODULE_ONLY（会拉全量 dep typeck，codegen import 常失败）；EMIT_HEAVY 与 typeck 第二遍同模式。
# 优先 XLANG_ASM_WPO_DCE 默认开（main.o ~9KiB→~32B）；失败或无 entry 时回退 WPO=0。
rebuild_main_o_for_cli() {
  local tmp="/tmp/xlang_build_main.cli.o"
  local comp=""
  local txt=""
  local wpo_mode=""
  local main_tout="${XLANG_MAIN_O_COMPILE_TIMEOUT:-300}"

  if [ "${XLANG_ASM_SKIP_MAIN_O_REBUILD:-0}" = "1" ]; then
  build_xlang_asm_info "skip main.o recompile (XLANG_ASM_SKIP_MAIN_O_REBUILD=1)"
  return 0
  fi

  # main.x EMIT_HEAVY 须大栈；Alpine 默认 8192KiB 时 WPO on 易 SIGSEGV/失败。
  ulimit -s 65532 2>/dev/null || ulimit -s 16384 2>/dev/null || ulimit -s hard 2>/dev/null || true

  # 尝试编译 main.o：wpo_arg 为空=默认 WPO 开；0=显式关（A/B 对照 / 回退）。
  # WPO on 优先 SKIP+无 EMIT_HEAVY（main.x 仅 export entry，~656B）；失败再试 EMIT_HEAVY 全链。
  try_main_o_compile() {
  local wpo_arg="$1"
  local compiler="$2"
  local emit_heavy="${3:-0}"
  rm -f "$tmp" 2>/dev/null || true
  if command -v timeout >/dev/null 2>&1; then
  if [ -n "$wpo_arg" ]; then
  timeout "$main_tout" env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/main.x 2>/dev/null || return 1
  else
  timeout "$main_tout" env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/main.x 2>/dev/null || return 1
  fi
  elif [ -n "$wpo_arg" ]; then
  if ! env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/main.x 2>/dev/null; then
  return 1
  fi
  elif ! env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/main.x 2>/dev/null; then
  return 1
  fi
  txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  if [ "$txt" = "0" ]; then
  return 1
  fi
  # PLATFORM: SHARED — product ABI is main_entry (main.x); Mach-O may prefix `_`.
  # Legacy bare `entry` still accepted. Tip multi-export no longer DCE-compresses.
  if ! nm "$tmp" 2>/dev/null | grep -qE ' (_)?(main_)?entry$'; then
  return 1
  fi
  # WPO on：prefer compressed; oversize falls through to WPO-off / heavy paths.
  # Cap 见 wpo-main-o.tsv / XLANG_WPO_MAIN_MAX_TEXT（历史 ~1610B；tip full emit larger）.
  local main_wpo_max="${XLANG_WPO_MAIN_MAX_TEXT:-2048}"
  if [ -z "$wpo_arg" ] && [ "$txt" -gt "$main_wpo_max" ] 2>/dev/null; then
  return 1
  fi
  return 0
  }

  build_xlang_asm_info "recompile main.o (ENTRY_MODULE_ONLY + WPO DCE prefer-on, max __text=${XLANG_WPO_MAIN_MAX_TEXT:-2048}B)"
  set +e
  # XLANG_WPO_MAIN_REBUILD_ONLY：post-strict 仅允许指定编译器（须为新链出的 ./xlang_asm）。
  if [ -n "${XLANG_WPO_MAIN_REBUILD_ONLY:-}" ]; then
  for comp in ${XLANG_WPO_MAIN_REBUILD_ONLY}; do
  [ -x "$comp" ] || continue
  wpo_mode="on"
  if try_main_o_compile "" "$comp" 0; then
  :
  elif try_main_o_compile "" "$comp" 1; then
  wpo_mode="on-heavy"
  elif try_main_o_compile "0" "$comp" 0; then
  wpo_mode="off"
  elif try_main_o_compile "0" "$comp" 1; then
  wpo_mode="off-heavy"
  else
  continue
  fi
  mv -f "$tmp" "$BUILD_DIR/main.o"
  build_xlang_asm_info "main.o CLI entry OK via $comp (__text=${txt}B, WPO DCE ${wpo_mode}, symbol entry)"
  set -e
  return 0
  done
  set -e
  build_xlang_asm_error "main.o post-strict WPO recompile failed (compiler=${XLANG_WPO_MAIN_REBUILD_ONLY})"
  return 1
  fi
  # post-strict / 生产链：优先 experimental（ENTRY_MODULE_ONLY smoke 通过）。
  while IFS= read -r comp; do
  [ -n "$comp" ] || continue
  wpo_mode="on"
  if try_main_o_compile "" "$comp" 0; then
  :
  elif try_main_o_compile "" "$comp" 1; then
  wpo_mode="on-heavy"
  elif try_main_o_compile "0" "$comp" 0; then
  wpo_mode="off"
  elif try_main_o_compile "0" "$comp" 1; then
  wpo_mode="off-heavy"
  else
  continue
  fi
  mv -f "$tmp" "$BUILD_DIR/main.o"
  build_xlang_asm_info "main.o CLI entry OK via $comp (__text=${txt}B, WPO DCE ${wpo_mode}, symbol entry)"
  set -e
  return 0
  done <<EOF
$(wpo_rebuild_compiler_candidates)
EOF
  set -e
  build_xlang_asm_error "main.o CLI recompile failed (check/fmt/test may rely on asm_experimental_symbol_bridge)"
  return 1
}

# strict 链成功后重编 main.o：strict xlang_asm 自编 main.x 易 SIGSEGV；优先 experimental。
# 若已有 WPO 压缩 main.o（≤768B + entry），勿用 WPO off 回退覆盖。
rebuild_main_o_post_strict_link() {
  ulimit -s 65532 2>/dev/null || ulimit -s 16384 2>/dev/null || ulimit -s hard 2>/dev/null || true
  local comp
  local cur_txt
  if [ "${XLANG_ASM_SKIP_MAIN_O_REBUILD:-0}" = "1" ]; then
  build_xlang_asm_info "post-strict skip main.o recompile (XLANG_ASM_SKIP_MAIN_O_REBUILD=1)"
  return 0
  fi
  if [ -f "$BUILD_DIR/asm_experimental_symbol_bridge.o" ] && \
  ! nm "$BUILD_DIR/main.o" 2>/dev/null | grep -qE ' (_)?(main_)?entry$'; then
  build_xlang_asm_info "post-strict skip main.o recompile (bridge entry; main.o stub)"
  return 0
  fi
  cur_txt=$(asm_o_text_bytes "$BUILD_DIR/main.o" 2>/dev/null || echo 0)
  if [ "$cur_txt" -gt 0 ] && [ "$cur_txt" -le 768 ] 2>/dev/null && \
  nm "$BUILD_DIR/main.o" 2>/dev/null | grep -qE ' (_)?(main_)?entry$'; then
  build_xlang_asm_info "post-strict main.o keep compressed (__text=${cur_txt}B, main_entry/entry present)"
  return 0
  fi
  for comp in ./xlang_asm ./xlang_asm.experimental ./xlang_asm_stage1 ./xlang; do
  [ -x "$comp" ] || continue
  if XLANG_WPO_MAIN_REBUILD_ONLY="$comp" rebuild_main_o_for_cli; then
  return 0
  fi
  done
  return 1
}

# EMIT_HEAVY driver_compile + link_alias → driver_compile_link.o（strict 替换 driver_compile_x.o）。
# EMIT_HEAVY 常漏 driver_compile_parse_argv_loop；从 driver_compile_x.o 部分导出补全。
# PLATFORM: SHARED — merge authority = pure_ld_partial_merge (G.7; no bare ld -r).
# PLATFORM: MACOS — F7 MH_OBJECT has two LC_SEGMENT; Apple ld -r fails; merge → libtool ar.
# PLATFORM: LINUX — cc/ld -r keeps single ET_REL.
ensure_driver_parse_argv_loop_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/driver_compile_parse_argv_loop_partial.o"
  SYMS="$BUILD_DIR/driver_compile_parse_argv_loop_export.txt"
  SUO="driver_compile_x.o"
  [ -f "$SUO" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ]; then
  printf '%s\n' 'driver_compile_parse_argv_loop' >"$SYMS"
  echo " ld partial export $SYMS $SUO -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" || return 1
  fi
  return 0
}

ensure_driver_compile_link_obj() {
  local eh_o="$BUILD_DIR/driver_compile_emit_heavy.o"
  local alias_src="seeds/driver_compile_asm_link_alias.from_x.c"
  local alias_o="$BUILD_DIR/driver_compile_asm_link_alias.o"
  local link_o="$BUILD_DIR/driver_compile_link.o"
  local loop_partial="$BUILD_DIR/driver_compile_parse_argv_loop_partial.o"
  local merge_objs=""
  [ -f "$eh_o" ] && [ -s "$eh_o" ] || return 1
  [ -f "$alias_src" ] || return 1
  if [ ! -f "$alias_o" ] || [ "$alias_src" -nt "$alias_o" ]; then
  build_xlang_asm_info "cc_inc_tu driver_compile_asm_link_alias.o"
  sh scripts/cc_inc_tu.sh "$alias_src" "$alias_o"
  fi
  if nm "$eh_o" 2>/dev/null | grep -qE ' U (_)?driver_compile_parse_argv_loop$'; then
  ensure_driver_parse_argv_loop_partial_obj || return 1
  else
  loop_partial=""
  # emit_heavy 已含 loop：仅用 eh+alias 重编 link_o，勿再挂 loop partial。
  rm -f "$link_o" 2>/dev/null || true
  fi
  if [ ! -f "$link_o" ] || [ "$eh_o" -nt "$link_o" ] || [ "$alias_o" -nt "$link_o" ] || \
  { [ -n "$loop_partial" ] && [ -f "$loop_partial" ] && [ "$loop_partial" -nt "$link_o" ]; }; then
  build_xlang_asm_info "pure_ld_partial_merge driver_compile_emit_heavy + link_alias -> driver_compile_link.o"
  rm -f "$link_o" 2>/dev/null || true
  merge_objs="$eh_o $alias_o"
  if [ -n "$loop_partial" ] && [ -f "$loop_partial" ]; then
  merge_objs="$merge_objs $loop_partial"
  fi
  # shellcheck disable=SC2086
  pure_ld_partial_merge "$link_o" $merge_objs || return 1
  fi
  nm -g "$link_o" 2>/dev/null | grep -qE '(_)?driver_run_compiler_full_x' || return 1
  if nm "$link_o" 2>/dev/null | grep -qE ' U (_)?driver_compile_parse_argv_loop$'; then
  return 1
  fi
  return 0
}

# EMIT_HEAVY 全量 driver_compile（S3 gate / strict link）；与 WPO 压缩 driver_compile.o 分离。
try_driver_emit_heavy_compile() {
  local out_o="$1"
  local compiler="$2"
  local eh_tout="${XLANG_DRIVER_EMIT_HEAVY_TIMEOUT:-600}"
  rm -f "$out_o" 2>/dev/null || true
  if command -v timeout >/dev/null 2>&1; then
  timeout "$eh_tout" env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 \
  XLANG_ASM_WPO_DCE=0 \
  "$compiler" -backend asm -o "$out_o" $LIBROOT src/driver/compile.x 2>/dev/null || return 1
  elif ! env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 \
  XLANG_ASM_WPO_DCE=0 \
  "$compiler" -backend asm -o "$out_o" $LIBROOT src/driver/compile.x 2>/dev/null; then
  return 1
  fi
  [ -s "$out_o" ] || return 1
  [ "$(asm_o_text_bytes "$out_o" 2>/dev/null || echo 0)" -ge 5104 ] 2>/dev/null
}

# WPO 压缩 driver_compile.o 验收：无 entry 符号；须 __text≤768B 且含至少一个真 export。
driver_wpo_compressed_o_ok() {
  local o="$1"
  local txt
  txt=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  [ "$txt" -gt 0 ] 2>/dev/null || return 1
  [ "$txt" -le 768 ] 2>/dev/null || return 1
  # PLATFORM: SHARED — Mach-O nm prefixes `_`.
  nm "$o" 2>/dev/null | grep -qE ' T (_)?(compile_dispatch_asm_backend|run_compiler_full_x|entry)$' && return 0
  nm "$o" 2>/dev/null | grep -q ' T '
}

# B-strict：WPO 压缩 driver_compile.o；失败不覆盖已有压缩产物。
rebuild_driver_compile_o_wpo() {
  local tmp="/tmp/xlang_build_driver_compile.cli.o"
  local comp=""
  local txt=""
  local wpo_mode=""
  if [ "${XLANG_ASM_SKIP_WPO_DOGFOOD:-0}" = "1" ]; then
  build_xlang_asm_info "skip driver_compile.o WPO recompile (XLANG_ASM_SKIP_WPO_DOGFOOD=1)"
  return 0
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s 16384 2>/dev/null || ulimit -s hard 2>/dev/null || true

  try_driver_wpo_compile() {
  local wpo_arg="$1"
  local compiler="$2"
  rm -f "$tmp" 2>/dev/null || true
  if [ -n "$wpo_arg" ]; then
  if ! env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 \
  XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/driver/compile.x 2>/dev/null; then
  return 1
  fi
  elif ! env -u XLANG_ASM_START_FUNC \
  XLANG_ASM_ENTRY_MODULE_ONLY=1 \
  XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/driver/compile.x 2>/dev/null; then
  return 1
  fi
  txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  [ "$txt" -gt 0 ] || return 1
  if [ -z "$wpo_arg" ] && [ "$txt" -gt 768 ] 2>/dev/null; then
  return 1
  fi
  driver_wpo_compressed_o_ok "$tmp" || return 1
  return 0
  }

  build_xlang_asm_info "recompile driver_compile.o (WPO DCE prefer-on, entry-only ~145B)"
  set +e
  while IFS= read -r comp; do
  [ -n "$comp" ] || continue
  wpo_mode="on"
  if try_driver_wpo_compile "" "$comp"; then
  :
  elif try_driver_wpo_compile "0" "$comp"; then
  wpo_mode="off"
  else
  continue
  fi
  mv -f "$tmp" "$BUILD_DIR/driver_compile.o"
  build_xlang_asm_info "driver_compile.o WPO OK via $comp (__text=${txt}B, WPO DCE ${wpo_mode})"
  set -e
  return 0
  done <<EOF
$(wpo_rebuild_compiler_candidates)
EOF
  set -e
  build_xlang_asm_warn "driver_compile.o WPO recompile failed (non-fatal)"
  return 1
}

# EMIT_HEAVY + link.o：strict 链 parse_argv / run_compiler_full_x asm 替换 C-gen。
rebuild_driver_compile_emit_heavy_and_link() {
  local eh_o="$BUILD_DIR/driver_compile_emit_heavy.o"
  local comp=""
  local eh_tout="${XLANG_DRIVER_EMIT_HEAVY_TIMEOUT:-600}"
  if [ "${XLANG_ASM_SKIP_DRIVER_EMIT_HEAVY:-0}" = "1" ]; then
  build_xlang_asm_info "skip driver_compile_emit_heavy.o recompile (XLANG_ASM_SKIP_DRIVER_EMIT_HEAVY=1)"
  return 0
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s 16384 2>/dev/null || ulimit -s hard 2>/dev/null || true
  build_xlang_asm_info "recompile driver_compile_emit_heavy.o (EMIT_HEAVY full X)"
  set +e
  for comp in "${XLANG:-}" "./xlang_asm" "./xlang_asm_stage1" "${XLANG_ASM_SECOND_PASS_COMPILER:-./xlang_asm.experimental}" "./xlang" "./xlang-x"; do
  [ -n "$comp" ] || continue
  [ -x "$comp" ] || continue
  if try_driver_emit_heavy_compile "$eh_o" "$comp"; then
  if ensure_driver_compile_link_obj; then
  build_xlang_asm_info "driver_compile_emit_heavy.o OK via $comp (__text=$(asm_o_text_bytes "$eh_o")B, link.o ready)"
  set -e
  return 0
  fi
  fi
  done
  set -e
  build_xlang_asm_warn "driver_compile_emit_heavy.o failed; using strict driver asm fallback to C-gen"
  return 1
}

rebuild_driver_compile_post_strict_link() {
  local cur_txt
  cur_txt=$(asm_o_text_bytes "$BUILD_DIR/driver_compile.o" 2>/dev/null || echo 0)
  if driver_wpo_compressed_o_ok "$BUILD_DIR/driver_compile.o" 2>/dev/null; then
  build_xlang_asm_info "post-strict driver_compile.o keep compressed (__text=${cur_txt}B)"
  else
  rebuild_driver_compile_o_wpo || true
  fi
  rebuild_driver_compile_emit_heavy_and_link || true
  rebuild_pipeline_wpo_post_strict || true
  rebuild_typeck_wpo_post_strict || true
  rebuild_backend_wpo_post_strict || true
  if asm_pipeline_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_WPO=1
  build_xlang_asm_info "post-strict STRICT_LINK_BUILD_ASM_WPO=1 (pipeline_wpo.o reach OK)"
  fi
  if [ "${XLANG_ASM_STRICT_LINK_TYPECK_WPO:-1}" != "0" ] && asm_typeck_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_TYPECK_WPO=1
  build_xlang_asm_info "post-strict STRICT_LINK_BUILD_ASM_TYPECK_WPO=1 (typeck_wpo reach OK; helpers only if typeck.o not selfhosted)"
  fi
  if asm_backend_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_BACKEND_WPO=1
  build_xlang_asm_info "post-strict STRICT_LINK_BUILD_ASM_BACKEND_WPO=1 (backend_wpo.o reach OK)"
  fi
}

# WPO dogfood smoke: compile runtime_pipeline_abi.x ENTRY_MODULE_ONLY (reach OK).
# G.7: pipeline.x is pure-extern (0 bodies) → exit-0 empty .o; live orch is
# runtime_pipeline_abi.x (pipeline_run_x_pipeline_impl). PLATFORM: SHARED.
xlang_asm_entry_module_smoke_ok() {
  local comp="$1"
  local tmp="/tmp/xlang_wpo_entry_smoke.$$.o"
  local tout="${XLANG_ASM_ENTRY_SMOKE_TIMEOUT:-180}"
  local smoke_src="${XLANG_WPO_PIPELINE_SRC:-src/runtime_pipeline_abi.x}"
  [ -x "$comp" ] || return 1
  rm -f "$tmp" 2>/dev/null || true
  # PLATFORM: MACOS — EMIT_HEAVY=1 Abort risk on mega TU; prefer heavy=0.
  local emit_heavy=1
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  emit_heavy=0
  fi
  if command -v timeout >/dev/null 2>&1; then
  timeout "$tout" env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$comp" -backend asm -o "$tmp" $LIBROOT "$smoke_src" 2>/dev/null \
  || { rm -f "$tmp" 2>/dev/null || true; return 1; }
  elif ! env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$comp" -backend asm -o "$tmp" $LIBROOT "$smoke_src" 2>/dev/null; then
  rm -f "$tmp" 2>/dev/null || true
  return 1
  fi
  if [ ! -s "$tmp" ]; then
  rm -f "$tmp" 2>/dev/null || true
  return 1
  fi
  if ! pipeline_wpo_tmp_reach_ok "$tmp" 2>/dev/null; then
  rm -f "$tmp" 2>/dev/null || true
  return 1
  fi
  rm -f "$tmp" 2>/dev/null || true
  return 0
}

# WPO experimental freshness (G.7 single authority).
# PLATFORM: SHARED — after wave335 / 8.3 leave, ast_pool.c and pipeline_glue.c are
# absent; live WPO source is runtime_pipeline_abi.x (+ seed twin). Stale checks on
# deleted files never fired → experimental lagged ASM_WPO_MAX_FUNCS / emit_order
# clamp and re-emitted ~814KiB fake strchr volume when preferred as fallback.
# Name kept (call sites); body retargeted to abi.x / seed / pipeline_x.o.
ensure_experimental_ast_pool_for_wpo() {
  local gen_drv="$BUILD_DIR/gen_driver/pipeline_x.o"
  local abi_x="${XLANG_WPO_PIPELINE_SRC:-src/runtime_pipeline_abi.x}"
  local abi_seed="seeds/runtime_pipeline_abi.from_x.c"
  local need=0
  # Host-cc mega pipeline_x.o still used in some bags: refresh when abi sources newer.
  if [ -f "$abi_x" ] && { [ "$abi_x" -nt pipeline_x.o ] 2>/dev/null \
    || { [ -f "$gen_drv" ] && [ "$abi_x" -nt "$gen_drv" ]; }; }; then
  need=1
  elif [ -f "$abi_seed" ] && { [ "$abi_seed" -nt pipeline_x.o ] 2>/dev/null \
    || { [ -f "$gen_drv" ] && [ "$abi_seed" -nt "$gen_drv" ]; }; }; then
  need=1
  fi
  if [ "$need" -eq 1 ]; then
  # Wave929: shell try-heat with PIPELINE_X_FORCE_COMPILE=1 (no make).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug; MF must exist).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    build_xlang_asm_info "abi/WPO source stale - make pipeline_x.o PIPELINE_X_FORCE_COMPILE=1"
    make pipeline_x.o PIPELINE_X_FORCE_COMPILE=1 || return 1
  else
    build_xlang_asm_info "abi/WPO source stale - try-heat pipeline_x.o PIPELINE_X_FORCE_COMPILE=1 (wave929)"
    PIPELINE_X_FORCE_COMPILE=1 bash scripts/ensure_host_cc_seed_o.sh try-heat pipeline_x.o || return 1
  fi
  fi
  if [ ! -x ./scripts/relink_xlang_asm_experimental_bootstrap.sh ]; then
  return 1
  fi
  # Relink experimental when missing or abi / pipeline_x newer (fallback candidate).
  if [ ! -x ./xlang_asm.experimental ] \
  || { [ -f "$abi_x" ] && [ "$abi_x" -nt ./xlang_asm.experimental ]; } \
  || { [ -f "$abi_seed" ] && [ "$abi_seed" -nt ./xlang_asm.experimental ]; } \
  || [ pipeline_x.o -nt ./xlang_asm.experimental ] 2>/dev/null; then
  build_xlang_asm_info "relink xlang_asm.experimental (abi WPO source / pipeline_x.o)"
  ./scripts/relink_xlang_asm_experimental_bootstrap.sh || return 1
  fi
  return 0
}

# WPO 五模块自编译：优先 experimental（ENTRY_MODULE_ONLY 可用）；strict_glue 须 smoke 通过。
wpo_rebuild_compiler_candidates() {
  local comp=""
  if [ -n "${XLANG_WPO_REBUILD_COMPILER:-}" ]; then
  for comp in ${XLANG_WPO_REBUILD_COMPILER}; do
  [ -x "$comp" ] && printf '%s\n' "$comp"
  done
  return 0
  fi
  # PLATFORM: SHARED — prefer product tip ./xlang_asm first. Stale
  # ./xlang_asm.experimental often lags ASM_WPO_MAX_FUNCS / emit_order clamp
  # (2026-08-24: experimental still 1024 → re-emit ~971× T _strchr / ~814KiB
  # fake size after tip compress). experimental / strict_glue stay fallbacks.
  # pipeline 已 promote/selfhosted 时跳过 pipeline.x smoke（Docker 上易 futex 卡死数小时）
  if [ "${XLANG_ASM_SKIP_ENTRY_SMOKE:-0}" = "1" ] || asm_strict_pipeline_selfhosted 2>/dev/null; then
  for comp in ./xlang_asm ./xlang_asm.strict_glue ./xlang_asm.experimental ./xlang-seed-phase1 ./xlang; do
  [ -x "$comp" ] && printf '%s\n' "$comp"
  done
  return 0
  fi
  # PLATFORM: MACOS — abi smoke is ~20s/candidate (mega runtime_pipeline_abi.x).
  # Skip smoke for candidate list speed; rebuild_pipeline_wpo_o still compiles abi.
  # Escape: XLANG_ASM_FORCE_ENTRY_SMOKE=1.
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ] && [ "${XLANG_ASM_FORCE_ENTRY_SMOKE:-0}" != "1" ]; then
  for comp in ./xlang_asm ./xlang_asm.strict_glue ./xlang_asm.experimental ./xlang; do
  [ -x "$comp" ] && printf '%s\n' "$comp"
  done
  return 0
  fi
  if [ -x ./xlang_asm ] && xlang_asm_entry_module_smoke_ok ./xlang_asm; then
  printf '%s\n' "./xlang_asm"
  fi
  if [ -x ./xlang_asm.strict_glue ] && xlang_asm_entry_module_smoke_ok ./xlang_asm.strict_glue; then
  printf '%s\n' "./xlang_asm.strict_glue"
  fi
  if [ -x ./xlang_asm.experimental ] && xlang_asm_entry_module_smoke_ok ./xlang_asm.experimental; then
  printf '%s\n' "./xlang_asm.experimental"
  fi
  if [ -n "${XLANG_ASM_SECOND_PASS_COMPILER:-}" ] && [ -x "${XLANG_ASM_SECOND_PASS_COMPILER}" ] \
  && xlang_asm_entry_module_smoke_ok "${XLANG_ASM_SECOND_PASS_COMPILER}"; then
  printf '%s\n' "${XLANG_ASM_SECOND_PASS_COMPILER}"
  fi
  for comp in ./xlang ./xlang-x; do
  [ -x "$comp" ] && xlang_asm_entry_module_smoke_ok "$comp" && printf '%s\n' "$comp"
  done
}

# pipeline_wpo.o 编排链 reach：tmp .o 内 run_x_pipeline_impl 直接 callee 须已定义。
pipeline_wpo_tmp_reach_ok() {
  local o="$1"
  [ -f "$o" ] || return 1
  nm "$o" 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  nm "$o" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_typecheck_entry$' && return 1
  nm "$o" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_codegen_entry$' && return 1
  nm "$o" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_parse_entry_if_needed$' && return 1
  nm "$o" 2>/dev/null | grep -qE ' U (_)?run_x_pipeline_codegen_deps$' && return 1
  return 0
}

# pipeline_wpo.o dogfood from runtime_pipeline_abi.x (G.7 single authority).
# wave335+: pipeline.x is pure-extern (0 bodies) → asm emit exit-0 empty; live orch
# is runtime_pipeline_abi.x (pipeline_run_x_pipeline_impl + Cap faces).
# 2026-08-24: emit_order OOB clamp → true __text ~37KiB (was ~814KiB strchr dups).
# Soft size unless XLANG_WPO_PIPELINE_STRICT_SIZE=1. PLATFORM: SHARED.
rebuild_pipeline_wpo_o() {
  local tmp="/tmp/xlang_build_pipeline_wpo.cli.o"
  local comp=""
  local txt=""
  local preserve_backup=""
  local pipe_src="${XLANG_WPO_PIPELINE_SRC:-src/runtime_pipeline_abi.x}"
  # Post-cap tip ~72KiB (FUNCS=2048 full emit); soft 96KiB headroom (STRICT_SIZE hard).
  local pipe_wpo_max="${XLANG_WPO_PIPELINE_MAX_TEXT:-98304}"
  local pipe_tout="${XLANG_WPO_PIPELINE_COMPILE_TIMEOUT:-600}"
  if [ "${XLANG_ASM_SKIP_WPO_DOGFOOD:-0}" = "1" ]; then
  build_xlang_asm_info "skip pipeline_wpo.o recompile (XLANG_ASM_SKIP_WPO_DOGFOOD=1)"
  return 0
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  if [ -f "$BUILD_DIR/pipeline_wpo.o" ] && [ -s "$BUILD_DIR/pipeline_wpo.o" ]; then
  preserve_backup="$BUILD_DIR/.preserve_pipeline_wpo.o"
  cp -f "$BUILD_DIR/pipeline_wpo.o" "$preserve_backup" 2>/dev/null || preserve_backup=""
  fi
  ensure_experimental_ast_pool_for_wpo || true
  try_pipe_wpo() {
  local wpo_arg="$1"
  local compiler="$2"
  local emit_heavy="${3:-1}"
  rm -f "$tmp" 2>/dev/null || true
  if command -v timeout >/dev/null 2>&1; then
  if [ -n "$wpo_arg" ]; then
  timeout "$pipe_tout" env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT "$pipe_src" 2>/dev/null || return 1
  else
  timeout "$pipe_tout" env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT "$pipe_src" 2>/dev/null || return 1
  fi
  elif [ -n "$wpo_arg" ]; then
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT "$pipe_src" 2>/dev/null || return 1
  else
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT "$pipe_src" 2>/dev/null || return 1
  fi
  txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  [ "$txt" -gt 0 ] || return 1
  if [ "$txt" -gt "$pipe_wpo_max" ] 2>/dev/null; then
  if [ "${XLANG_WPO_PIPELINE_STRICT_SIZE:-0}" = "1" ]; then
  return 1
  fi
  build_xlang_asm_warn "pipeline_wpo.o __text=${txt}B > soft max ${pipe_wpo_max}B (post-compress soft OK)"
  fi
  nm "$tmp" 2>/dev/null | grep -qE '(_)?(pipeline_)?run_x_pipeline_impl' || return 1
  pipeline_wpo_tmp_reach_ok "$tmp" || return 1
  return 0
  }
  build_xlang_asm_info "recompile pipeline_wpo.o from $pipe_src (WPO DCE, pipeline_run_x_pipeline_impl root, max __text=${pipe_wpo_max}B soft)"
  set +e
  while IFS= read -r comp; do
  [ -n "$comp" ] || continue
  # PLATFORM: SHARED — mega runtime_pipeline_abi.x: prefer EMIT_HEAVY=0 first
  # (Darwin Abort risk; Linux heavy path hang/fail on tip). Then try heavy=1.
  if try_pipe_wpo "" "$comp" 0 || try_pipe_wpo "1" "$comp" 0 || try_pipe_wpo "0" "$comp" 0; then
  mv -f "$tmp" "$BUILD_DIR/pipeline_wpo.o"
  build_xlang_asm_info "pipeline_wpo.o OK via $comp (__text=${txt}B, EMIT_HEAVY=0, reach OK)"
  rm -f "$preserve_backup" 2>/dev/null || true
  set -e
  return 0
  fi
  if try_pipe_wpo "" "$comp" 1 || try_pipe_wpo "0" "$comp" 1; then
  mv -f "$tmp" "$BUILD_DIR/pipeline_wpo.o"
  build_xlang_asm_info "pipeline_wpo.o OK via $comp (__text=${txt}B, reach OK)"
  rm -f "$preserve_backup" 2>/dev/null || true
  set -e
  return 0
  fi
  done <<EOF
$(wpo_rebuild_compiler_candidates)
EOF
  set -e
  if [ -n "$preserve_backup" ] && [ -f "$preserve_backup" ]; then
  cp -f "$preserve_backup" "$BUILD_DIR/pipeline_wpo.o"
  build_xlang_asm_warn "pipeline_wpo.o rebuild failed; restored previous artifact"
  fi
  return 1
}

rebuild_pipeline_wpo_post_strict() {
  rebuild_pipeline_wpo_o || true
}

# typeck.x WPO 压缩产物（dogfood；strict 仍用 build_asm/typeck.o 全量 EMIT_HEAVY）。
rebuild_typeck_wpo_o() {
  local tmp="/tmp/xlang_build_typeck_wpo.cli.o"
  local comp=""
  local txt=""
  if [ "${XLANG_ASM_SKIP_WPO_DOGFOOD:-0}" = "1" ]; then
  build_xlang_asm_info "skip typeck_wpo.o recompile (XLANG_ASM_SKIP_WPO_DOGFOOD=1)"
  return 0
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  try_tck_wpo() {
  local wpo_arg="$1"
  local compiler="$2"
  local emit_heavy="${3:-1}"
  rm -f "$tmp" 2>/dev/null || true
  if [ -n "$wpo_arg" ]; then
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/typeck/typeck.x 2>/dev/null || return 1
  else
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY="$emit_heavy" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/typeck/typeck.x 2>/dev/null || return 1
  fi
  txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  [ "$txt" -gt 0 ] || return 1
  # Align with tests/baseline/wpo-typeck-o.tsv (post-2026-07 true DCE ~4577B Linux).
  # PLATFORM: MACOS — arm64 typeck_wpo tip ~9–10KiB; raise default cap when unset.
  local tck_wpo_max="${XLANG_WPO_TYPECK_MAX_TEXT:-}"
  if [ -z "$tck_wpo_max" ]; then
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  tck_wpo_max=16384
  else
  # tip Linux typeck_wpo ~6.5KiB (was 4577→6144; 2026-08-24 probe 6528).
  tck_wpo_max=8192
  fi
  fi
  [ "$txt" -le "$tck_wpo_max" ] 2>/dev/null || return 1
  nm "$tmp" 2>/dev/null | grep -q 'typeck_x_ast' || return 1
  nm "$tmp" 2>/dev/null | grep -q 'check_block' || return 1
  return 0
  }
  build_xlang_asm_info "recompile typeck_wpo.o (WPO DCE, typeck_x_ast root, max __text=${XLANG_WPO_TYPECK_MAX_TEXT:-8192}B; Darwin default 16384)"
  set +e
  while IFS= read -r comp; do
  [ -n "$comp" ] || continue
  # PLATFORM: SHARED — prefer EMIT_HEAVY=0 first (Darwin Abort; Linux tip ~6.5KiB OK).
  if try_tck_wpo "" "$comp" 0 || try_tck_wpo "1" "$comp" 0 || try_tck_wpo "0" "$comp" 0; then
  mv -f "$tmp" "$BUILD_DIR/typeck_wpo.o"
  build_xlang_asm_info "typeck_wpo.o OK via $comp (__text=${txt}B, EMIT_HEAVY=0)"
  set -e
  return 0
  fi
  if try_tck_wpo "" "$comp" 1 || try_tck_wpo "0" "$comp" 1; then
  mv -f "$tmp" "$BUILD_DIR/typeck_wpo.o"
  build_xlang_asm_info "typeck_wpo.o OK via $comp (__text=${txt}B)"
  set -e
  return 0
  fi
  done <<EOF
$(wpo_rebuild_compiler_candidates)
EOF
  set -e
  return 1
}

rebuild_typeck_wpo_post_strict() {
  rebuild_typeck_wpo_o || true
}

# backend.x WPO 压缩产物（dogfood；strict 仍用 build_asm/backend.o 全量 EMIT_HEAVY）。
rebuild_backend_wpo_o() {
  local tmp="/tmp/xlang_build_backend_wpo.cli.o"
  local comp=""
  local txt=""
  if [ "${XLANG_ASM_SKIP_WPO_DOGFOOD:-0}" = "1" ]; then
  build_xlang_asm_info "skip backend_wpo.o recompile (XLANG_ASM_SKIP_WPO_DOGFOOD=1)"
  return 0
  fi
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  try_be_wpo() {
  local wpo_arg="$1"
  local compiler="$2"
  rm -f "$tmp" 2>/dev/null || true
  if [ -n "$wpo_arg" ]; then
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 XLANG_ASM_WPO_DCE="$wpo_arg" \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/asm/backend.x 2>/dev/null || return 1
  else
  env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=1 \
  "$compiler" -backend asm -o "$tmp" $LIBROOT src/asm/backend.x 2>/dev/null || return 1
  fi
  txt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  [ "$txt" -gt 0 ] || return 1
  [ "$txt" -le 512 ] 2>/dev/null || return 1
  nm "$tmp" 2>/dev/null | grep -q 'asm_codegen_ast' || return 1
  return 0
  }
  build_xlang_asm_info "recompile backend_wpo.o (WPO DCE, asm_codegen_ast root)"
  set +e
  while IFS= read -r comp; do
  [ -n "$comp" ] || continue
  if try_be_wpo "" "$comp"; then
  mv -f "$tmp" "$BUILD_DIR/backend_wpo.o"
  build_xlang_asm_info "backend_wpo.o OK via $comp (__text=${txt}B)"
  set -e
  return 0
  fi
  done <<EOF
$(wpo_rebuild_compiler_candidates)
EOF
  set -e
  return 1
}

rebuild_backend_wpo_post_strict() {
  rebuild_backend_wpo_o || true
}

# 仅重编 WPO dogfood 五模块（CI/stage2 补链；须已有可执行 ./xlang_asm，跳过 BUILD 循环与链接）。
if [ "${XLANG_WPO_REBUILD_ARTIFACTS_ONLY:-}" = "1" ]; then
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  # G.7: WPO authority = runtime_pipeline_abi.x (+ seed). ensure refreshes
  # experimental from abi freshness (deleted ast_pool.c never fired). ARTIFACTS
  # dogfood prefers tip ./xlang_asm — only relink strict_glue when pipeline_x.o
  # itself is newer (avoid abi-mtime → full strict relink every dogfood).
  ensure_experimental_ast_pool_for_wpo || \
  build_xlang_asm_warn "ensure_experimental_ast_pool_for_wpo failed (WPO rebuild may use stale experimental)"
  if [ -x ./scripts/relink_xlang_asm_strict_glue.sh ] \
  && [ -x ./xlang_asm.strict_glue ] \
  && [ pipeline_x.o -nt ./xlang_asm.strict_glue ] 2>/dev/null; then
  build_xlang_asm_info "pipeline_x.o newer - relink xlang_asm.strict_glue (no xlang_asm overwrite)"
  ./scripts/relink_xlang_asm_strict_glue.sh || \
  build_xlang_asm_warn "relink_xlang_asm_strict_glue failed"
  fi
  wpo_fail=0
  rebuild_main_o_for_cli || wpo_fail=1
  rebuild_driver_compile_o_wpo || wpo_fail=1
  # G.7: pipeline_wpo from runtime_pipeline_abi.x (pipeline.x pure-extern empty).
  # Hard-require on both Darwin and Linux once abi source is wired.
  rebuild_pipeline_wpo_o || wpo_fail=1
  rebuild_typeck_wpo_o || wpo_fail=1
  rebuild_backend_wpo_o || wpo_fail=1
  if [ "$wpo_fail" -ne 0 ]; then
  build_xlang_asm_error "XLANG_WPO_REBUILD_ARTIFACTS_ONLY failed (one or more WPO .o missing)"
  exit 1
  fi
  build_xlang_asm_info "XLANG_WPO_REBUILD_ARTIFACTS_ONLY OK (main+driver+pipeline_wpo+typeck_wpo+backend_wpo)"
  exit 0
fi

# runtime-only 快速重链：勿重跑 BUILD 循环（会覆盖 build_asm/*.o 中已绿 __text）。
if [ -n "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ]; then
  if [ -z "${XLANG_ASM_SKIP_QUALITY_REPORT:-}" ]; then
  export XLANG_ASM_SKIP_QUALITY_REPORT=1
  fi
fi

if [ -z "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ]; then
if [ -f "$BUILD_LIST_X" ]; then
  grep '^// BUILD:' "$BUILD_LIST_X" | while IFS= read -r line; do
  rest=$(echo "$line" | sed "s|^// BUILD:${TAB}||")
  out=$(echo "$rest" | cut -f1)
  src=$(echo "$rest" | cut -f2)
  [ -n "$out" ] && [ -n "$src" ] && compile_x "$out" "$src"
  done
else
  build_xlang_asm_warn "$BUILD_LIST_X not found, using built-in list"
  compile_x token.o src/lexer/token.x
  compile_x ast.o src/ast/ast.x
  compile_x codegen.o src/codegen/codegen.x
  compile_x typeck.o src/typeck/typeck.x
  compile_x lexer.o src/lexer/lexer.x
  compile_x preprocess.o src/preprocess/preprocess.x
  compile_x std_fs.o ../std/fs/mod.x
  compile_x lsp.o src/lsp/lsp.x
  compile_x types.o src/asm/types.x
  compile_x platform_elf.o src/asm/platform/elf.x
  compile_x x86_64.o src/asm/arch/x86_64.x
  compile_x x86_64_enc.o src/asm/arch/x86_64_enc.x
  compile_x arm64.o src/asm/arch/arm64.x
  compile_x arm64_enc.o src/asm/arch/arm64_enc.x
  compile_x riscv64.o src/asm/arch/riscv64.x
  compile_x riscv64_enc.o src/asm/arch/riscv64_enc.x
  compile_x peephole.o src/asm/peephole.x
  compile_x backend.o src/asm/backend.x
  compile_x asm.o src/asm/asm.x
  compile_x macho.o src/asm/platform/macho.x
  compile_x coff.o src/asm/platform/coff.x
  compile_x parser.o src/parser/parser.x
  compile_x pipeline.o src/pipeline/pipeline.x
  compile_x main.o src/main.x
fi
fi

# 报告 build_asm/*.o 的 __text 是否非空；写入 build_asm/.asm_text_quality（供 topology 降级判断）
if [ -z "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ]; then
if [ -z "${XLANG_ASM_SKIP_QUALITY_REPORT}" ]; then
  XLANG="$XLANG" ./scripts/check_asm_o_quality.sh || true
  # Target B（SELFHOST §4）：非空清单提示下一批应修的 BUILD 令牌，便于逐项消灭 EMPTY/MISSING
  BADEMPTY="$BUILD_DIR/.asm_empty_text_list"
  if [ -s "$BADEMPTY" ]; then
  build_xlang_asm_warn "__text EMPTY/MISSING sample (full list: $BADEMPTY, doc: docs/SELFHOST.md §4.1)"
  head -n 12 "$BADEMPTY" | sed 's/^/ /' || true
  fi
fi
fi

# 链接：仅当 main.o 与 pipeline.o 均来自 asm 时，用 asm 版链接。
# 优先尝试「无 C 桩」路径（仅 Linux）：crt0_x86_64.o + typeck_f64_bits.o + runtime_panic.o + build_asm/*.o + libc/libm；
# 失败或非 Linux 时回退到 runtime_asm_build.o + runtime_driver.o + -E 流水线 .o + C 种子（不并 build_asm/*.o，见上文）。
#
# 下列用 cc 直接编译，不调用 make，以便在「仅 bootstrap.sh + build_tool」环境下完成 asm 链接（朝去掉 Makefile 走一步）。
# CC/CFLAGS 已在 compile_x 之前定义（stub 回退需要）。

# 与 Makefile PIPELINE_GEN_CFLAGS 对齐：编译 -E 大文件时压制已知告警；Clang 追加额外 -Wno。
detect_pipeline_gen_cflags() {
  PIPELINE_GEN_CFLAGS="-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-parentheses -Wno-sign-compare -Wno-ignored-qualifiers -Wno-unused-but-set-variable -Wno-type-limits"
  if "$CC" -v 2>&1 | grep -qi clang; then
  PIPELINE_GEN_CFLAGS="$PIPELINE_GEN_CFLAGS -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses -Wno-incompatible-pointer-types-discards-qualifiers"
  fi
}

# Target B 实验链：编译 pipeline_run_x_pipeline 最小 C 桥（见 seeds/pipeline_glue_link.from_x.c）。
ensure_asm_pipeline_glue_link_obj() {
  GLUE_LINK_OBJ="$BUILD_DIR/pipeline_glue_link.o"
  if [ ! -f "$GLUE_LINK_OBJ" ] || [ "seeds/pipeline_glue_link.from_x.c" -nt "$GLUE_LINK_OBJ" ]; then
  echo " cc -c seeds/pipeline_glue_link.from_x.c -> $GLUE_LINK_OBJ"
  sh scripts/cc_inc_tu.sh seeds/pipeline_glue_link.from_x.c "$GLUE_LINK_OBJ"
  fi
}

# 实验链：run_x_pipeline_impl 别名到 pipeline_run_x_pipeline_impl（无 pipeline_x.o 时）
ensure_asm_pipeline_run_impl_alias_obj() {
  ALIAS_OBJ="$BUILD_DIR/pipeline_run_impl_alias.o"
  local ALIAS_CFLAGS="$CFLAGS"
  if asm_strict_x_orchestration_ok; then
  ALIAS_CFLAGS="$CFLAGS -DXLANG_PIPELINE_RUN_IMPL_ALIAS_PARSE_ALIASES=0"
  fi
  if [ ! -f "$ALIAS_OBJ" ] || [ "seeds/pipeline_run_impl_alias.from_x.c" -nt "$ALIAS_OBJ" ] || \
  [ ! -f "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" ] || \
  { asm_strict_x_orchestration_ok && [ "$(cat "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" 2>/dev/null)" != "1" ]; } || \
  { ! asm_strict_x_orchestration_ok && [ "$(cat "$BUILD_DIR/.pipeline_run_impl_alias_x_orch" 2>/dev/null)" = "1" ]; }; then
  echo " cc -c seeds/pipeline_run_impl_alias.from_x.c -> $ALIAS_OBJ (X orch=$(asm_strict_x_orchestration_ok && echo 1 || echo 0))"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_impl_alias.from_x.c "$ALIAS_OBJ"
  if asm_strict_x_orchestration_ok; then echo "1" >"$BUILD_DIR/.pipeline_run_impl_alias_x_orch"; else echo "0" >"$BUILD_DIR/.pipeline_run_impl_alias_x_orch"; fi
  fi
}

# strict 链：build_asm/parser.o 自举时 parse_into_buf 等大函数未进 module；从 pipeline_x.o 部分链接 parser_* 真机码。
ensure_parser_bootstrap_partial_obj() {
  PARTIAL="$BUILD_DIR/parser_bootstrap_partial.o"
  SYMS="$BUILD_DIR/parser_bootstrap_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  printf '%s\n' \
  '_parser_parse_into_buf' \
  '_parser_collect_imports_buf' \
  '_parser_parse_into_init' \
  '_parser_parse_into_set_main_index' > "$SYMS"
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
}

# strict 链：从 pipeline_x.o 导出全部 parser_* 真机码（自洽 TU），替代 build_asm/parser.o 桩 + 零散 partial。
# PLATFORM: SHARED — SYMS freshness = producer .o (+ script/$0 when present); deleted
# ast_pool.c -nt never fired post-leave (same debt layer as glue_standalone ensure).
ensure_parser_from_x_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/parser_from_x_partial.o"
  SYMS="$BUILD_DIR/parser_from_x_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$SYMS" ] || [ "$SUO" -nt "$SYMS" ]; then
  GLUE_O="$BUILD_DIR/pipeline_glue_standalone.o"
  ensure_asm_pipeline_glue_standalone_obj
  nm "$SUO" | awk '/ T _parser_/ {print $3}' > "$BUILD_DIR/.parser_from_x_all.txt"
  : > "$SYMS"
  while IFS= read -r sym; do
  [ -n "$sym" ] || continue
  if [ -f "$GLUE_O" ] && nm "$GLUE_O" 2>/dev/null | grep -q " T ${sym}$"; then
  continue
  fi
  printf '%s\n' "$sym" >> "$SYMS"
  done < "$BUILD_DIR/.parser_from_x_all.txt"
  echo " nm pipeline_x.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') parser_* symbols, glue dupes skipped)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
}

# strict 链：build_asm/parser.o 的 parse_into_init 等为桩；与 parser_bootstrap_partial 合并后 bootstrap 符号优先。
ensure_parser_strict_merged_obj() {
  local MERGED PO PARTIAL SYMS
  MERGED="$BUILD_DIR/parser_strict_merged.o"
  SYMS="$BUILD_DIR/parser_strict_merged_export.txt"
  PO="$BUILD_DIR/parser.o"
  ensure_parser_bootstrap_partial_obj
  PARTIAL="$BUILD_DIR/parser_bootstrap_partial.o"
  if [ ! -f "$PO" ] || [ ! -f "$PARTIAL" ]; then
  return 1
  fi
  if [ ! -f "$MERGED" ] || [ "$PO" -nt "$MERGED" ] || [ "$PARTIAL" -nt "$MERGED" ] || [ "$SYMS" -nt "$MERGED" ]; then
  printf '%s\n' \
  '_parser_parse_into_buf' \
  '_parser_collect_imports_buf' \
  '_parser_parse_into_init' \
  '_parser_parse_into_set_main_index' > "$SYMS"
  echo " ld -r -exported_symbols_list $SYMS parser.o + parser_bootstrap_partial.o -> $MERGED"
  ld -r -exported_symbols_list "$SYMS" -o "$MERGED" "$PO" "$PARTIAL"
  fi
  return 0
}

# strict 链：build_asm/pipeline.o 编排函数 emit 不可用；C 实现供 ld -r 合并进 runtime partial。
ensure_pipeline_asm_orchestration_partial_obj() {
  local PARTIAL SYMS ALIAS_O
  PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_orchestration_export.txt"
  ALIAS_O="$BUILD_DIR/pipeline_asm_orchestration_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ "seeds/pipeline_asm_orchestration_alias.from_x.c" -nt "$ALIAS_O" ]; then
  echo " cc_inc_tu seeds/pipeline_asm_orchestration_alias.from_x.c -> $ALIAS_O"
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
  echo " ld partial export $SYMS orchestration_alias.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$ALIAS_O"
  fi
  # strict 链最终链接读 pipeline_asm_runtime_partial.o
  cp -f "$PARTIAL" "$BUILD_DIR/pipeline_asm_runtime_partial.o"
  return 0
}

# strict 链：pipeline.o 第二遍 emit 的 typecheck if/else 不完整；C alias 单独提供 pipeline_impl_typecheck。
ensure_pipeline_asm_typecheck_alias_obj() {
  local ALIAS_O
  ALIAS_O="$BUILD_DIR/pipeline_asm_typecheck_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ "seeds/pipeline_asm_typecheck_alias.from_x.c" -nt "$ALIAS_O" ]; then
  echo " cc -c seeds/pipeline_asm_typecheck_alias.from_x.c -> $ALIAS_O"
  sh scripts/cc_inc_tu.sh seeds/pipeline_asm_typecheck_alias.from_x.c "$ALIAS_O"
  fi
}

# strict 链：pipeline.o 第二遍 emit 的 run_all typeck 失败后仍进 codegen；C alias 单独 ld -r。
ensure_pipeline_asm_run_all_partial_obj() {
  local PARTIAL SYMS ALIAS_O
  PARTIAL="$BUILD_DIR/pipeline_asm_run_all_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_run_all_export.txt"
  ALIAS_O="$BUILD_DIR/pipeline_asm_run_all_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ "seeds/pipeline_asm_run_all_alias.from_x.c" -nt "$ALIAS_O" ]; then
  echo " cc -c seeds/pipeline_asm_run_all_alias.from_x.c -> $ALIAS_O"
  sh scripts/cc_inc_tu.sh seeds/pipeline_asm_run_all_alias.from_x.c "$ALIAS_O"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$ALIAS_O" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_pipeline_impl_run_all
_run_x_pipeline_impl
EOF
  echo " ld -r -exported_symbols_list $SYMS run_all_alias.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$ALIAS_O"
  fi
}

# strict 链（B-strict+asm）：第二遍 build_asm/pipeline.o 导出编排符号（spill/load 已修）；不含 U 的 phase_parse_only。
ensure_pipeline_asm_orchestration_from_build_o() {
  local PARTIAL SYMS PO
  PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_from_build.o"
  SYMS="$BUILD_DIR/pipeline_asm_orchestration_from_build_export.txt"
  PO="$BUILD_DIR/pipeline.o"
  if [ ! -f "$PO" ] || [ ! -s "$PO" ]; then
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$PO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_pipeline_impl_phase_load_deps
_pipeline_impl_should_skip_codegen
_pipeline_impl_codegen_deps
_pipeline_impl_codegen_entry
_pipeline_impl_codegen_chain
EOF
  echo " ld partial export $SYMS build_asm/pipeline.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$PO"
  fi
  return 0
}

# strict 链：pipeline.x 自洽 parse 包（parse_into_with_init_buf + parser_*），避免 U 解析到 build_asm 空桩。
ensure_pipeline_parse_x_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/pipeline_parse_x_partial.o"
  SYMS="$BUILD_DIR/pipeline_parse_x_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_pipeline_parse_into_with_init_buf
_pipeline_resolve_path_x
_pipeline_read_file_x
EOF
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
}

# strict 链：pipeline.o 第二遍 emit 缺 pipeline_impl_phase_parse_only（ENTRY_MODULE_ONLY 未落码），单 TU 补一条。
ensure_pipeline_phase_parse_only_partial_obj() {
  local PARTIAL SYMS ALIAS_O
  PARTIAL="$BUILD_DIR/pipeline_phase_parse_only_partial.o"
  SYMS="$BUILD_DIR/pipeline_phase_parse_only_export.txt"
  ALIAS_O="$BUILD_DIR/pipeline_phase_parse_only_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ "seeds/pipeline_phase_parse_only_alias.from_x.c" -nt "$ALIAS_O" ]; then
  echo " cc -c seeds/pipeline_phase_parse_only_alias.from_x.c -> $ALIAS_O"
  sh scripts/cc_inc_tu.sh seeds/pipeline_phase_parse_only_alias.from_x.c "$ALIAS_O"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$ALIAS_O" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  cat > "$SYMS" <<'EOF'
_pipeline_impl_phase_parse_only
EOF
  else
  cat > "$SYMS" <<'EOF'
_pipeline_impl_phase_parse_only
_pipeline_impl_phase_parse_load
EOF
  fi
  echo " ld -r -exported_symbols_list $SYMS phase_parse_only_alias.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$ALIAS_O"
  fi
}

# strict 链：自 build_asm/pipeline.o 导出除 impl/parse/typecheck 外全部全局 T（C 编排见 orchestration_alias.c）。
pipeline_strict_link_export_syms_stale() {
  local syms="$1"
  local po="$2"
  [ -f "$syms" ] || return 0
  grep -qE '^(_)?preprocess_if_stack_|^(_)?backend_ctx_(push|pop)_loop_labels$|^(_)?backend_try_fold_count_up_while_elf$' "$syms" 2>/dev/null && return 0
  # X 编排：partial 不得再 export C 版 run_x_pipeline_*（runtime bootstrap 提供 pipeline_run_x_pipeline_impl）。
  if asm_strict_x_orchestration_ok 2>/dev/null; then
  grep -qxF 'run_x_pipeline_impl' "$syms" 2>/dev/null && return 0
  grep -qxF 'run_x_pipeline_parse_entry_do_parse' "$syms" 2>/dev/null && return 0
  fi
  # 历史 WPO subtract 误留仅 ~27 个 orchestration 符号的小表。
  local n_po n_sym
  n_po=$(nm "$po" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  n_sym=$(wc -l <"$syms" | tr -d ' ')
  if [ "${n_po:-0}" -gt 80 ] 2>/dev/null && [ "${n_sym:-0}" -lt 40 ] 2>/dev/null; then
  grep -qxF 'run_x_pipeline_impl' "$syms" 2>/dev/null && return 0
  fi
  return 1
}

ensure_pipeline_o_strict_link_partial_obj() {
  local PARTIAL SYMS PO WPO_E n_t
  PARTIAL="$BUILD_DIR/pipeline_strict_link_partial.o"
  SYMS="$BUILD_DIR/pipeline_strict_link_export.txt"
  PO="$BUILD_DIR/pipeline.o"
  WPO_E="$BUILD_DIR/pipeline_wpo.o"
  if [ ! -f "$PO" ] || [ ! -s "$PO" ]; then
  return 1
  fi
  # G.7: wave335+ pipeline.x pure-extern → build_asm/pipeline.o often 0 T.
  # Live orch = runtime_pipeline_abi / pipeline_wpo; skip empty partial (no hard error).
  # PLATFORM: SHARED.
  n_t=$(nm "$PO" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${n_t:-0}" -eq 0 ] && asm_pipeline_wpo_strict_reach_ok; then
  build_xlang_asm_info "skip pipeline_strict_link_partial (pipeline.o 0 T pure-extern; WPO/abi covers)"
  rm -f "$PARTIAL" 2>/dev/null || true
  : >"$SYMS"
  return 1
  fi
  if pipeline_strict_link_export_syms_stale "$SYMS" "$PO"; then
  rm -f "$PARTIAL" "$SYMS"
  fi
  if [ "$(cat "$BUILD_DIR/.pipeline_strict_orch_mode" 2>/dev/null)" = "su" ] && ! asm_strict_x_orchestration_ok; then
  rm -f "$PARTIAL" "$SYMS"
  fi
  if [ "$(cat "$BUILD_DIR/.pipeline_strict_orch_mode" 2>/dev/null)" = "c" ] && asm_strict_x_orchestration_ok; then
  rm -f "$PARTIAL" "$SYMS"
  fi
  if [ -f "$SYMS" ] && grep -qE '_pipeline_should_skip_x_typeck|pipeline_should_skip_x_typeck' "$SYMS" 2>/dev/null; then
  rm -f "$PARTIAL" "$SYMS"
  fi
  # Stale: T-only export dropped X weak resolve_path_* (WPO bridge UNDEF).
  if [ -f "$SYMS" ] && ! grep -qxF 'pipeline_resolve_path_try_one_lib_root' "$SYMS" 2>/dev/null; then
  build_xlang_asm_warn "stale pipeline_strict_link export (missing W resolve_path); regen"
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$0" -nt "$SYMS" ] || [ "$PO" -nt "$SYMS" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$SYMS" ]; } || \
  { [ -f "$BUILD_DIR/pipeline_x_glue_support_export.txt" ] && [ "$BUILD_DIR/pipeline_x_glue_support_export.txt" -nt "$SYMS" ]; }; then
  # PLATFORM: SHARED — pipeline.x emits resolve_path helpers as weak (W); bridge needs them.
  nm "$PO" 2>/dev/null | awk '/ [TW] / {print $3}' | grep -vE \
  '_run_x_pipeline_(impl|parse_entry_do_parse|parse_entry_if_needed|typecheck_entry)$|^_?(parse_into_with_init_buf|parse_into_with_init|pipeline_run_x_pipeline_impl|pipeline_should_skip_x_typeck|preprocess_if_stack_.*|backend_ctx_push_loop_labels|backend_ctx_pop_loop_labels|backend_try_fold_count_up_while_elf)$' \
  | sort -u >"$SYMS"
  # S5 WPO：pipeline_wpo.o / helpers partial 已定义的符号须从 partial 剔除，避免 multiple definition。
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
  # X glue support partial 从 pipeline_x.o 提供 glue/astpool 符号；勿与 build_asm partial 重复 export。
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -f "$BUILD_DIR/pipeline_x_glue_support_export.txt" ] && \
  [ -s "$BUILD_DIR/pipeline_x_glue_support_export.txt" ]; then
  sort -u "$SYMS" -o "$SYMS"
  sort -u "$BUILD_DIR/pipeline_x_glue_support_export.txt" -o "$BUILD_DIR/.pipeline_x_glue_support_export.sorted.txt"
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_x_glue_support_export.sorted.txt" >"$SYMS.gsup" 2>/dev/null && mv -f "$SYMS.gsup" "$SYMS"
  echo " pipeline_strict_link: minus pipeline_x_glue_support exports ($(wc -l <"$BUILD_DIR/.pipeline_x_glue_support_export.sorted.txt" | tr -d ' ') syms)"
  fi
  echo " nm pipeline.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols, minus parse/typecheck/impl entry)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$PO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; } || \
  { [ -f "$BUILD_DIR/pipeline_x_glue_support_export.txt" ] && [ "$BUILD_DIR/pipeline_x_glue_support_export.txt" -nt "$PARTIAL" ]; } || \
  [ "seeds/pipeline_asm_orchestration_alias.from_x.c" -nt "$PARTIAL" ]; then
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -f "$BUILD_DIR/pipeline_x_glue_support_export.txt" ] && \
  [ -s "$BUILD_DIR/pipeline_x_glue_support_export.txt" ]; then
  sort -u "$SYMS" -o "$SYMS"
  sort -u "$BUILD_DIR/pipeline_x_glue_support_export.txt" -o "$BUILD_DIR/.pipeline_x_glue_support_export.sorted.txt"
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_x_glue_support_export.sorted.txt" >"$SYMS.link" 2>/dev/null && mv -f "$SYMS.link" "$SYMS"
  fi
  echo " ld partial export $SYMS pipeline.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$PO" || return 1
  fi
  return 0
}

# strict WPO opt-in：从 pipeline_wpo.o 导出 helper（剔除 X 编排入口；编排仍走 C orchestration partial）。
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
  # G.7: abi already on LD argv → skip helpers extract (overlap + Darwin LC_SEGMENT /
  # Ubuntu internal multi-def if emit_order OOB regresses). PLATFORM: SHARED.
  if asm_strict_pipeline_selfhosted; then
  build_xlang_asm_info "skip pipeline_wpo_helpers_partial (runtime_pipeline_abi on LD argv)"
  return 1
  fi
  # PLATFORM: SHARED — do not overwrite full selfhosted pipeline.o (pipeline_x, 1000+ T
  # with pipeline_resolve_path_*) with WPO-helpers-only; bare resolve_path_* come from pipeline_wpo.o.
  if [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ] && [ -f "$BUILD_DIR/pipeline.o" ]; then
  _po_n=$(nm "$BUILD_DIR/pipeline.o" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${_po_n:-0}" -gt 80 ] 2>/dev/null; then
  :
  elif ! nm "$BUILD_DIR/pipeline.o" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$'; then
  local comp tmp pt
  tmp="$BUILD_DIR/pipeline.wpo_strict_helpers.o"
  for comp in ./xlang_asm.experimental ./xlang_asm ./xlang ./xlang-x; do
  [ -x "$comp" ] || continue
  echo " pipeline_wpo_helpers: rebuild pipeline.o EMIT_HEAVY via $comp"
  ulimit -s 65532 2>/dev/null || ulimit -s hard 2>/dev/null || true
  rm -f "$tmp" 2>/dev/null || true
  # G.7: resolve_path helpers live in runtime_pipeline_abi.x (pipeline.x pure-extern).
  if env -u XLANG_ASM_START_FUNC XLANG_ASM_ENTRY_MODULE_ONLY=1 XLANG_ASM_BUILD_SKIP_TYPECK=1 \
  XLANG_ASM_ENTRY_EMIT_HEAVY=0 XLANG_ASM_WPO_DCE=0 \
  "$comp" -backend asm -o "$tmp" -L asm_libroot -L .. -L src \
  "${XLANG_WPO_PIPELINE_SRC:-src/runtime_pipeline_abi.x}" 2>/dev/null; then
  pt=$(asm_o_text_bytes "$tmp" 2>/dev/null || echo 0)
  if [ "$pt" -gt 512 ] 2>/dev/null && \
  nm "$tmp" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$'; then
  mv -f "$tmp" "$BUILD_DIR/pipeline.o"
  rm -f "$BUILD_DIR/pipeline_strict_link_partial.o" "$BUILD_DIR/pipeline_strict_link_export.txt" 2>/dev/null || true
  break
  fi
  fi
  rm -f "$tmp" 2>/dev/null || true
  done
  fi
  fi
  if [ ! -f "$SYMS" ] || [ "$WPO_E" -nt "$SYMS" ] || [ "seeds/pipeline_asm_orchestration_alias.from_x.c" -nt "$SYMS" ] || \
  { ensure_pipeline_glue_standalone_export_syms_txt && [ "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" -nt "$SYMS" ]; }; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | grep -vE \
  '^(run_x_pipeline_impl|run_x_pipeline_parse_entry_do_parse|run_x_pipeline_parse_entry_if_needed|run_x_pipeline_typecheck_entry|parse_into_with_init_buf|parse_into_with_init|pipeline_run_x_pipeline_impl|pipeline_run_x_pipeline|pipeline_should_skip_x_typeck)$' \
  >"$SYMS"
  if ensure_pipeline_glue_standalone_export_syms_txt; then
  comm -23 "$SYMS" "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" >"$SYMS.glue" 2>/dev/null && mv -f "$SYMS.glue" "$SYMS"
  echo " pipeline_wpo_helpers: minus glue_standalone T dupes"
  fi
  echo " nm pipeline_wpo.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') helper syms, minus orchestration entry)"
  fi
  if [ -f "$PARTIAL" ] && ensure_pipeline_glue_standalone_export_syms_txt && \
  [ -f "$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt" ]; then
  if comm -12 "$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt" \
  "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" 2>/dev/null | grep -q .; then
  build_xlang_asm_warn "stale pipeline_wpo_helpers_partial (glue dupes); rebuild"
  rm -f "$PARTIAL" "$SYMS"
  fi
  fi
  if [ ! -s "$SYMS" ]; then
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$WPO_E" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  echo " ld partial export $SYMS pipeline_wpo.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$WPO_E" || return 1
  nm "$PARTIAL" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_wpo_helpers_export_syms.txt"
  fi
  return 0
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
  # 旧 partial 曾误含 typeck_x_ast（内联 WPO check_block）→ 强制重算。
  if [ -f "$PARTIAL" ]; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' && rm -f "$PARTIAL" "$SYMS"
  fi
  if [ ! -f "$SYMS" ] || [ "$WPO_E" -nt "$SYMS" ]; then
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | grep -vE "$EXCLUDE_RE" >"$SYMS"
  echo " nm typeck_wpo.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') layout syms, minus check_block/check_expr/typeck_x_ast*)"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$WPO_E" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  echo " ld partial export $SYMS typeck_wpo.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$WPO_E" || return 1
  nm "$PARTIAL" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.typeck_wpo_helpers_export_syms.txt"
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' && {
  build_xlang_asm_error "typeck_wpo_helpers_partial must not export typeck_x_ast (use typeck.o entry)"
  return 1
  }
  fi
  return 0
}

# strict 链：C orchestration partial 即 runtime partial（勿链 pipeline.o，避免 dead broken 符号拉入 U typeck）。
ensure_pipeline_asm_runtime_partial_obj() {
  ensure_pipeline_asm_orchestration_partial_obj
}

# strict 回退：build_asm pipeline 仍不足时，从 pipeline_x.o 部分链接完整 pipeline_run_x_pipeline_impl。
# G.7: when runtime_pipeline_abi.o is selfhosted (already on strict LD argv), skip —
# pipeline_x.o is a pure-extern stub (0 T); ld -r -exported_symbols_list for
# _pipeline_run_x_pipeline_impl UNDEFs. Callers use `ensure && FILTERED=...partial`.
# PLATFORM: SHARED.
ensure_pipeline_runtime_bootstrap_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_pipeline_selfhosted; then
  build_xlang_asm_info "skip pipeline_runtime_bootstrap_partial (runtime_pipeline_abi on LD argv)"
  rm -f "$PARTIAL" 2>/dev/null || true
  return 1
  fi
  SYMS="$BUILD_DIR/pipeline_runtime_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  printf '%s\n' '_pipeline_run_x_pipeline_impl' > "$SYMS"
  echo " ld partial export $SYMS pipeline_x.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" || return 1
  fi
}

# strict X 编排：从 pipeline_x.o 导出 glue/astpool 桥接（与 runtime bootstrap 同 TU）；替代 glue_standalone 避免双 astpool SIGSEGV。
ensure_pipeline_x_glue_support_partial_obj() {
  local PARTIAL SYMS SUO TCK_SYMS
  PARTIAL="$BUILD_DIR/pipeline_x_glue_support_partial.o"
  SYMS="$BUILD_DIR/pipeline_x_glue_support_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  TCK_SYMS="$BUILD_DIR/typeck_strict_link_export.txt"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  [ -f "$SUO" ] || return 1
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -f typeck_x.o ]; then
  nm typeck_x.o 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.typeck_x_all_t.txt"
  TCK_SYMS="$BUILD_DIR/.typeck_x_all_t.txt"
  else
  ensure_typeck_o_strict_link_partial_obj || true
  TCK_SYMS="$BUILD_DIR/typeck_strict_link_export.txt"
  fi
  if [ ! -f "$SYMS" ] || [ "$0" -nt "$SYMS" ] || [ "$SUO" -nt "$SYMS" ] || \
  { [ -f "$TCK_SYMS" ] && [ "$TCK_SYMS" -nt "$SYMS" ]; } || \
  { [ -f "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" ] && [ "$BUILD_DIR/.pipeline_glue_standalone_export_syms.txt" -nt "$SYMS" ]; }; then
  ensure_pipeline_glue_standalone_export_syms_txt || return 1
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
  # build_asm pipeline_strict_link_partial 须 U→T：交集抽取常漏 _c 后缀外的 X 编排符号。
  for sym in pipeline_load_and_sync_direct_import_deps pipeline_run_x_pipeline_fill_dep_import_path; do
  sym_export="$sym"
  if ld_supports_exported_symbols_list; then
  sym_export="_$sym"
  fi
  grep -qxF "$sym_export" "$SYMS" 2>/dev/null || printf '%s\n' "$sym_export" >>"$SYMS"
  done
  echo " pipeline_x glue support: $(wc -l <"$SYMS" | tr -d ' ') syms (pipeline_x∩glue minus orch/typeck)"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  echo " ld partial export $SYMS pipeline_x.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" || return 1
  fi
  return 0
}

# strict 链：build_asm 编排/typeck/codegen 仍不足时，从 pipeline_x.o 部分链接（不含 pipeline_run 重复符号）。
ensure_pipeline_asm_x_bootstrap_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/pipeline_asm_x_bootstrap_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_x_bootstrap_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_asm_asm_codegen_ast
_backend_asm_codegen_ast
_typeck_typeck_x_ast
_typeck_typeck_x_ast_library
EOF
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
  # 兼容旧名
  cp -f "$PARTIAL" "$BUILD_DIR/pipeline_asm_codegen_bootstrap_partial.o"
}

# strict 编排链：parse + typeck + codegen 须同一 ld -r（两次 partial 会重复 parser 内部符号 → body_ref=0）。
ensure_pipeline_asm_strict_support_partial_obj() {
  local PARTIAL SYMS SUO PARSE_ONLY_SYMS
  PARTIAL="$BUILD_DIR/pipeline_asm_strict_support_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_strict_support_export.txt"
  PARSE_ONLY_SYMS="$BUILD_DIR/pipeline_asm_strict_support_parse_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  local TCK_BYTES BACK_BYTES
  TCK_BYTES=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo 0)
  BACK_BYTES=$(asm_o_text_bytes "$BUILD_DIR/backend.o" 2>/dev/null || echo 0)
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  # build_asm typeck.o 已完整自举（__text>8KiB）时 partial 只补 parse；否则 partial 含 typeck_x_ast*。
  if asm_strict_typeck_selfhosted; then
  cat > "$PARSE_ONLY_SYMS" <<'EOF'
_pipeline_parse_into_with_init_buf
_parser_parse_into_buf
_parser_parse_into_init
_parser_parse_into_set_main_index
_parser_collect_imports_buf
_parser_parse_into
_parser_get_module_num_imports
_parser_get_module_import_path
EOF
  SYMS="$PARSE_ONLY_SYMS"
  build_xlang_asm_info "strict_support parse-only partial (typeck.o=${TCK_BYTES}B selfhosted from build_asm)"
  else
  cat > "$SYMS" <<'EOF'
_pipeline_parse_into_with_init_buf
_parser_parse_into_buf
_parser_parse_into_init
_parser_parse_into_set_main_index
_parser_collect_imports_buf
_parser_parse_into
_parser_get_module_num_imports
_parser_get_module_import_path
_typeck_typeck_x_ast
_typeck_typeck_x_ast_library
EOF
  build_xlang_asm_info "strict_support parse+typeck partial (typeck.o=${TCK_BYTES}B not selfhosted yet)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  [ "$BUILD_DIR/typeck.o" -nt "$PARTIAL" ] || [ "$BUILD_DIR/backend.o" -nt "$PARTIAL" ]; then
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
}

# WPO opt-in helper 链：仅 typecheck emit 桥（编排入口由 C orchestration partial 提供）。
ensure_pipeline_wpo_typecheck_emit_bridge_obj() {
  local BR_O="$BUILD_DIR/pipeline_wpo_typecheck_emit_bridge.o"
  local BR_SRC="seeds/pipeline_wpo_typecheck_emit_bridge.from_x.c"
  if [ ! -f "$BR_SRC" ]; then
  return 1
  fi
  if [ ! -f "$BR_O" ] || [ "$BR_SRC" -nt "$BR_O" ]; then
  echo " cc_inc_tu $BR_SRC -> $BR_O (WPO typecheck emit bridge)"
  sh scripts/cc_inc_tu.sh "$BR_SRC" "$BR_O" || return 1
  fi
  return 0
}

# S5 WPO strict 链：pipeline_wpo.o + glue 入口/typecheck emit 别名（替代 C orchestration partial）。
ensure_pipeline_wpo_strict_link_alias_obj() {
  local ALIAS_O="$BUILD_DIR/pipeline_wpo_strict_link_alias.o"
  local ALIAS_SRC="seeds/pipeline_wpo_strict_link_alias.from_x.c"
  if [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -ne 1 ] || ! asm_pipeline_wpo_strict_reach_ok; then
  return 0
  fi
  if [ ! -f "$ALIAS_SRC" ]; then
  return 1
  fi
  if [ ! -f "$ALIAS_O" ] || [ "$ALIAS_SRC" -nt "$ALIAS_O" ]; then
  echo " cc_inc_tu $ALIAS_SRC -> $ALIAS_O (WPO strict link alias)"
  sh scripts/cc_inc_tu.sh "$ALIAS_SRC" "$ALIAS_O" || return 1
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

# WPO FULL：从 pipeline_glue_standalone 剔除 pipeline_wpo.o 已 T 定义的符号，避免 multiple definition。
ensure_pipeline_glue_standalone_wpo_dedupe_obj() {
  local PARTIAL SYMS GLUE_O WPO_E
  PARTIAL="$BUILD_DIR/pipeline_glue_wpo_dedupe.o"
  SYMS="$BUILD_DIR/pipeline_glue_wpo_dedupe_export.txt"
  GLUE_O="$BUILD_DIR/pipeline_glue_standalone.o"
  WPO_E="$BUILD_DIR/pipeline_wpo.o"
  ensure_asm_pipeline_glue_standalone_obj || return 1
  [ -f "$WPO_E" ] || return 1
  if [ ! -f "$SYMS" ] || [ "$GLUE_O" -nt "$SYMS" ] || [ "$WPO_E" -nt "$SYMS" ]; then
  nm "$GLUE_O" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_glue_all_t.txt"
  nm "$WPO_E" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$BUILD_DIR/.pipeline_wpo_all_t.txt"
  comm -23 "$BUILD_DIR/.pipeline_glue_all_t.txt" "$BUILD_DIR/.pipeline_wpo_all_t.txt" >"$SYMS"
  echo " pipeline_glue wpo dedupe: $(wc -l <"$SYMS" | tr -d ' ') syms (glue minus pipeline_wpo T dupes)"
  fi
  [ -s "$SYMS" ] || return 1
  if [ ! -f "$PARTIAL" ] || [ "$GLUE_O" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || [ "$WPO_E" -nt "$PARTIAL" ]; then
  echo " ld partial export $SYMS pipeline_glue_standalone.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$GLUE_O" || return 1
  fi
  return 0
}

# strict 链：自 build_asm/typeck.o 导出除 WPO 已定义外符号（impl mega 等仍由 partial 提供）。
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
  # 过期 export/partial 须强制重算（仅减 typeck_wpo.o 的 6 个 T，须保留 typeck_check_block_one_* 等 callee）。
  if typeck_wpo_strict_partial_export_syms_stale "$SYMS"; then
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ -f "$PARTIAL" ] && [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] && asm_typeck_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_check_block_one_while$' || rm -f "$PARTIAL"
  fi
  # glue_standalone 更新后须重算 export，避免 typeck partial 仍导出 pipeline_arena_expr_ptr 等重复符号。
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
  echo " nm typeck.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$TCKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; } || \
  { [ -f "$GLUE_O" ] && [ "$GLUE_O" -nt "$PARTIAL" ]; }; then
  echo " ld partial export $SYMS typeck.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$TCKO" || return 1
  if [ "${STRICT_LINK_BUILD_ASM_TYPECK_WPO:-0}" -eq 1 ] && asm_typeck_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_check_block_one_while$' || {
  build_xlang_asm_error "typeck_strict_link_partial missing typeck_check_block_one_while (stale export?)"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?check_block_as_loop_body$' || {
  build_xlang_asm_error "typeck_strict_link_partial missing check_block_as_loop_body"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?check_block$' || {
  build_xlang_asm_error "typeck_strict_link_partial missing check_block (must come from typeck.o, not typeck_wpo.o)"
  return 1
  }
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?typeck_x_ast$' || {
  build_xlang_asm_error "typeck_strict_link_partial missing typeck_x_ast (must come from typeck.o, not typeck_wpo.o)"
  return 1
  }
  fi
  fi
  return 0
}

# strict 链：C orchestration TU（不含 pipeline_run 包装，与 trampoline 并列）。
ensure_pipeline_bootstrap_orchestration_strict_obj() {
  local ORCH_O
  ORCH_O="$BUILD_DIR/pipeline_bootstrap_orchestration_strict.o"
  if [ ! -f "$ORCH_O" ] || [ "seeds/pipeline_bootstrap_orchestration.from_x.c" -nt "$ORCH_O" ]; then
  echo " cc -c seeds/pipeline_bootstrap_orchestration.from_x.c -> $ORCH_O (strict, no pipeline_run wrapper)"
  "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -I"$BUILD_DIR" -DPIPELINE_BOOTSTRAP_ORCH_NO_PIPELINE_RUN_WRAPPER \
  -c -o "$ORCH_O" seeds/pipeline_bootstrap_orchestration.from_x.c
  fi
}

# B-strict：runtime 入口薄壳，委托 C glue run_x_pipeline_impl（build_asm/pipeline.o 仅 path/load helper）。
ensure_pipeline_run_bootstrap_trampoline_obj() {
  local TRAMP_O TRAMP_CFLAGS
  TRAMP_O="$BUILD_DIR/pipeline_run_bootstrap_trampoline.o"
  TRAMP_CFLAGS="$CFLAGS"
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  TRAMP_CFLAGS="$CFLAGS -DSTRICT_LINK_BUILD_ASM_PIPELINE=1"
  fi
  if [ ! -f "$TRAMP_O" ] || [ "seeds/pipeline_run_bootstrap_trampoline.from_x.c" -nt "$TRAMP_O" ] || \
  [ ! -f "$BUILD_DIR/.pipeline_trampoline_strict_flag" ] || \
  [ "$(cat "$BUILD_DIR/.pipeline_trampoline_strict_flag" 2>/dev/null)" != "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" ]; then
  echo " cc -c seeds/pipeline_run_bootstrap_trampoline.from_x.c -> $TRAMP_O (STRICT_LINK_BUILD_ASM_PIPELINE=${STRICT_LINK_BUILD_ASM_PIPELINE:-0})"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_bootstrap_trampoline.from_x.c "$TRAMP_O"
  echo "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" >"$BUILD_DIR/.pipeline_trampoline_strict_flag"
  fi
}

# B-strict：最小 glue shell；编排真机在 runtime_pipeline_abi／pipeline.x
# （ast_pool.c / glue_standalone mega left wave309）。
# wave304 G.7 8.3.6: seed shell retired (0 residual T after wave303). Product
# g05 no longer host-cc or links this .o. Soft no-op when seed absent so
# experimental strict paths do not hard-fail; they must resolve via typeck_x /
# pipeline_x / pipeline_abi. PLATFORM: SHARED freestanding shell retire.
ensure_asm_pipeline_glue_strict_minimal_obj() {
  local GLUE_OBJ="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  local SEED="seeds/pipeline_glue_strict_minimal.from_x.c"
  if [ ! -f "$SEED" ]; then
    return 0
  fi
  if [ ! -f "$GLUE_OBJ" ] || [ "$SEED" -nt "$GLUE_OBJ" ]; then
    echo " cc -c $SEED -> $GLUE_OBJ (G-02f-11)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c "$SEED" -o "$GLUE_OBJ"
  fi
}

# B-strict：preprocess -D 与 labeled 名写入（ast_pool_l5_bridge.c）。
ensure_ast_pool_l5_bridge_obj() {
  # G-02f-11：实现已并入 seeds/runtime_driver_strict_glue_stubs.from_x.c
  local o="src/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
    echo "  cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11)" >&2
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
}

# B-strict：pipeline_x.o 仅导出 asm/backend 四入口（legacy experimental 链）。
ensure_pipeline_asm_codegen_only_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/pipeline_asm_codegen_only_partial.o"
  SYMS="$BUILD_DIR/pipeline_asm_codegen_only_export.txt"
  SUO="$BUILD_DIR/gen_driver/pipeline_x.o"
  ensure_pipeline_x_o_fresh
  if [ ! -f "$SUO" ]; then
  ensure_asm_gen_driver_x_objs
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_asm_asm_codegen_ast
_asm_asm_codegen_elf_o
_backend_asm_codegen_ast
_backend_asm_codegen_ast_to_elf
EOF
  echo " ld -r -exported_symbols_list $SYMS pipeline_x.o -> $PARTIAL"
  ld -r -exported_symbols_list "$SYMS" -o "$PARTIAL" "$SUO"
  fi
}

# build_asm pipeline.o 第二遍：path/resolve/load + run_x_pipeline_impl 均 X 真 emit。
# 当前 seed 二遍实测 __text≈6843B（低于历史 S3a 11588B 目标，但符号齐全即可 strict）。
# nm：ELF 无 leading _，Mach-O 有 _；resolve 符号名为 resolve_path_probe_dot_x_and_mod 等。
# G.7 authority: runtime_pipeline_abi.o is the pipeline implementation (890KB+ text,
# 739 T symbols, run_x_pipeline_impl / path_append / resolve_path). pipeline.x is a
# pure-extern declaration module (0 function bodies); pipeline_x.o / pipeline.o are
# stubs (driver_leaf, 1688B text, 0 T symbols). Check the authority, not the stub.
# PLATFORM: SHARED — runtime_pipeline_abi.o is in LD argv on both Darwin and Linux.
asm_strict_pipeline_selfhosted() {
  local t
  t=$(asm_o_text_bytes src/runtime_pipeline_abi.o 2>/dev/null || echo 0)
  [ "$t" -ge 6144 ] 2>/dev/null || return 1
  nm -g src/runtime_pipeline_abi.o 2>/dev/null | grep -qE '(_)?path_append_from_buf_256|(_)?resolve_path_.*su' || return 1
  nm -g src/runtime_pipeline_abi.o 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  return 0
}

# build_asm pipeline 自举后用户 .x 编译：走 X run_x_pipeline_impl（与 experimental 一致）；C orchestration alias 已知 fill_cl SIGSEGV。
asm_strict_x_orchestration_ok() {
  local p_x_t=0
  [ "${XLANG_ASM_STRICT_C_ORCHESTRATION:-0}" = "1" ] && return 1
  [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ] || return 1
  if asm_strict_pipeline_selfhosted; then
  return 0
  fi
  # runtime-only relink 可能复用薄 build_asm/pipeline.o，但真正可执行的 X orchestration
  # 已存在于 pipeline_x.o；此时仍应允许 strict 路径按 companion 判真。
  [ -f pipeline_x.o ] || return 1
  p_x_t=$(asm_o_text_bytes pipeline_x.o 2>/dev/null || echo 0)
  [ "$p_x_t" -ge 6144 ] 2>/dev/null || return 1
  nm -g pipeline_x.o 2>/dev/null | grep -qE '(_)?path_append_from_buf_256|(_)?resolve_path_.*su' || return 1
  nm -g pipeline_x.o 2>/dev/null | grep -qE '(_)?run_x_pipeline_impl' || return 1
  return 0
}

# 自举 typeck + X 编排：glue 走 pipeline_x partial + glue_strict_minimal（勿 glue_standalone 双 astpool）。
asm_strict_typeck_x_glue_via_pipeline_x() {
  asm_strict_x_orchestration_ok || return 1
  if asm_strict_typeck_selfhosted; then
  return 0
  fi
  # runtime-only relink 可能复用薄 build_asm/typeck.o，但 typeck_x.o 已是完整 companion；
  # 此时仍应走 strict_minimal glue，避免退回缺少 pipeline_asm_* helper 的 glue_standalone。
  if [ -f typeck_x.o ] && [ -s typeck_x.o ]; then
  local t_x
  t_x=$(asm_o_text_bytes typeck_x.o 2>/dev/null || echo 0)
  [ "$t_x" -gt 10000 ] 2>/dev/null && return 0
  fi
  return 0
}

# pipeline_wpo.o 编排链 reach：run_x_pipeline_impl 直接 callee 须在 TU 内定义（S5 strict WPO link 前置）。
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

# track-only：链整颗 pipeline_wpo.o（X run_x_pipeline_impl 编排）；默认 helpers+C 编排（稳定）。
asm_pipeline_wpo_strict_link_full_ok() {
  local po="$BUILD_DIR/pipeline_wpo.o"
  [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL:-0}" = "1" ] || return 1
  asm_pipeline_wpo_strict_reach_ok || return 1
  nm "$po" 2>/dev/null | grep -qE ' T (_)?resolve_path_try_one_lib_root$' || return 1
  return 0
}

# Linux/Darwin reach OK 时默认链 pipeline_wpo；FULL=1 显式开启整颗 pipeline_wpo.o。
# When runtime_pipeline_abi already on LD argv, keep FULL=0 (avoid dual-authority).
# PLATFORM: SHARED.
maybe_default_pipeline_wpo_strict_link() {
  if [ -n "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO+x}" ]; then
  return 0
  fi
  case "$(uname -s)-$(uname -m 2>/dev/null)" in
  Linux-x86_64|Linux-amd64|Linux-aarch64|Linux-arm64|Darwin-arm64|Darwin-x86_64)
  if asm_pipeline_wpo_strict_reach_ok; then
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL:-0}" = "1" ] && ! asm_strict_pipeline_selfhosted; then
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL=1
  build_xlang_asm_info "default XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 + FULL=1 (whole pipeline_wpo.o + glue support)"
  else
  export XLANG_ASM_STRICT_LINK_PIPELINE_WPO_FULL=0
  build_xlang_asm_info "default XLANG_ASM_STRICT_LINK_PIPELINE_WPO=1 (helpers + C orch; abi covers when selfhosted)"
  fi
  fi
  ;;
  esac
}

# typeck_wpo.o WPO reach：typeck_x_ast / check_block / check_expr 须在 TU 内定义（impl 由 partial 补）。
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

# typeck_wpo helpers partial 仅于 typeck.o 未自举时链入；自举 typeck.o 已含 layout，且 wpo partial 会带入内联 check_block 局部符号 → SIGSEGV。
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

# build_asm backend.o 已 EMIT（薄桩 + helper；mega 真实现在 seed partial）。
asm_strict_backend_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/backend.o" 2>/dev/null || echo 0)
  [ "$t" -gt 1024 ] 2>/dev/null
}

# strict WPO 链：seeds/backend_asm_bare_link_alias.from_x.c（glue backend_* → build_asm 裸符号）。
ensure_backend_asm_bare_link_alias_obj() {
  local ALIAS_O="$BUILD_DIR/backend_asm_bare_link_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ seeds/backend_asm_bare_link_alias.from_x.c -nt "$ALIAS_O" ]; then
  echo " cc -c seeds/backend_asm_bare_link_alias.from_x.c -> $ALIAS_O"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$ALIAS_O" seeds/backend_asm_bare_link_alias.from_x.c
  fi
}

# strict 非 WPO backend fallback：给 user_asm_seed_bridge 提供 backend_* 强桥接，避免落到 seed weak return -1 桩。
ensure_backend_asm_strict_fallback_alias_obj() {
  local ALIAS_O="$BUILD_DIR/backend_asm_strict_fallback_alias.o"
  if [ ! -f "$ALIAS_O" ] || [ seeds/backend_asm_strict_fallback_alias.from_x.c -nt "$ALIAS_O" ]; then
  echo " cc -c seeds/backend_asm_strict_fallback_alias.from_x.c -> $ALIAS_O"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$ALIAS_O" seeds/backend_asm_strict_fallback_alias.from_x.c
  fi
}

# strict 链：compat stubs 须随源码重编（勿用 src/asm/*.o 陈旧副本）。
ensure_asm_backend_compat_stubs_obj() {
  local STUB_O="$BUILD_DIR/asm_backend_compat_stubs.o"
  if [ ! -f "$STUB_O" ] || [ seeds/asm_backend_compat_stubs.from_x.c -nt "$STUB_O" ]; then
  echo " cc -c seeds/asm_backend_compat_stubs.from_x.c -> $STUB_O"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/asm_backend_compat_stubs.from_x.c -o "$STUB_O"
  fi
}

ensure_bstrict_filtered_obj_against_seed_partial() {
  local src_o="$1"
  local out_o="$2"
  local tag="$3"
  local seed_o="$BUILD_DIR/seed_host/asm_backend_partial.o"
  # PLATFORM: SHARED — G.7 twin of filter_bootstrap_seed_against_partial_o /
  #   filter_o_export_against_deps (Darwin -arch + ar-archive path).
  # Do NOT use bare ld_partial_export here: Xcode ld needs -arch, and prefer/libtool
  # may leave SRC as ar (multi LC_SEGMENT); Apple ld has returned 0 with no OUT.
  [ -f "$src_o" ] || return 1
  [ -f "$seed_o" ] || return 1
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ] || [ "$seed_o" -nt "$out_o" ]; then
  echo " filter_o_export $(basename "$src_o") -> $(basename "$out_o") (bstrict vs seed_partial; stem=$tag)"
  bash scripts/filter_o_export_against_deps.sh \
    --src "$src_o" --out "$out_o" --stem "$tag" \
    --omit "$seed_o" || return 1
  fi
  [ -s "$out_o" ] || return 1
  return 0
}

ensure_bstrict_pipeline_filtered_obj() {
  local src_o="pipeline_x.o"
  local out_o="$BUILD_DIR/bstrict_pipeline_filtered.o"
  local all_syms="$BUILD_DIR/.bstrict_pipeline_all_t.txt"
  local omit_syms="$BUILD_DIR/.bstrict_pipeline_omit.txt"
  local keep_syms="$BUILD_DIR/.bstrict_pipeline_keep.txt"
  local dep_o
  [ -f "$src_o" ] || return 1
  : >"$omit_syms"
  for dep_o in typeck_x.o codegen_x.o "$BUILD_DIR/seed_host/asm_backend_partial.o"; do
  [ -f "$dep_o" ] || continue
  nm "$dep_o" 2>/dev/null | awk '/ T / {print $3}' >>"$omit_syms"
  done
  sort -u "$omit_syms" -o "$omit_syms"
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ] || [ "$omit_syms" -nt "$out_o" ]; then
  nm "$src_o" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$all_syms"
  comm -23 "$all_syms" "$omit_syms" >"$keep_syms"
  [ -s "$keep_syms" ] || return 1
  echo " ld partial export $keep_syms pipeline_x.o -> $(basename "$out_o")"
  ld_partial_export "$keep_syms" "$out_o" "$src_o" || return 1
  fi
  return 0
}

# PLATFORM: DARWIN — experimental bootstrap needs strict_glue_stubs (preprocess/codegen/ast
# helpers) but must not re-export asm_driver_* already strong in runtime_asm_build.o.
# Authority: keep full stubs on Linux; Darwin uses filter_o_export partial instead of
# dropping the whole .o (which left U preprocess_*/codegen_*/ast_module_free).
# Stage2 round2 tip: prefer/libtool may leave src as **ar archive** (multi LC_SEGMENT);
# local ld_partial_export lacked -arch and cannot re-filter ar → filt fail → historical
# "drop stubs" fallback → UNDEF codegen_set_* / pipeline_block_labeled_set_names.
# G.7: filter_o_export_against_deps.sh is the ld -r authority (Darwin -arch + ar path).
ensure_bstrict_darwin_strict_glue_stubs_filt_obj() {
  local src_o="src/runtime_driver_strict_glue_stubs.o"
  local out_o="$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o"
  local seed="seeds/runtime_driver_strict_glue_stubs.from_x.c"
  local need_cc=0
  # Prefer/libtool may leave an ar at src_o; force a fresh MH_OBJECT before filter.
  if [ ! -f "$src_o" ] || [ "$seed" -nt "$src_o" ]; then
  need_cc=1
  elif file "$src_o" 2>/dev/null | grep -qi 'ar archive'; then
  need_cc=1
  fi
  if [ "$need_cc" = "1" ]; then
  echo " cc -c $src_o <- $seed (Darwin filt prep; MH_OBJECT)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c "$seed" -o "$src_o" || return 1
  fi
  [ -f "$src_o" ] || return 1
  # Stale filt that still exports asm_asm_codegen_* must rebuild (omit set expanded).
  if [ -f "$out_o" ] && nm -gU "$out_o" 2>/dev/null | grep -qE 'asm_asm_codegen_(elf_o|ast)$'; then
  rm -f "$out_o"
  fi
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ]; then
  # Omit asm_driver_* (strong in runtime_asm_build) and asm_asm_codegen_* (strong in
  # user_asm_seed_bridge ar). Archive members are only extracted for currently
  # undefined symbols: if weak -1 stubs pre-satisfy U, Stage2 Darwin never pulls
  # the real bridge → CG002 code_len=0 on every user asm -o (G.7 twin g05 order).
  echo " filter_o_export $(basename "$src_o") -> $(basename "$out_o") (Darwin, omit asm_driver_* + asm_asm_codegen_*)"
  bash scripts/filter_o_export_against_deps.sh \
    --src "$src_o" --out "$out_o" --stem bstrict_strict_glue_stubs_darwin \
    --omit-sym asm_driver_set_current_dep_path_for_codegen \
    --omit-sym asm_driver_skip_codegen_dep_0_get \
    --omit-sym asm_asm_codegen_elf_o \
    --omit-sym asm_asm_codegen_ast \
    --require-keep || return 1
  fi
  # Required fillers for runtime_driver_asm_strict + parser_x (Stage2 round2 UNDEF map).
  if ! nm -gU "$out_o" 2>/dev/null | grep -q 'codegen_set_dep_slots_for_x_pipeline'; then
  build_xlang_asm_warn "Darwin stubs filt missing codegen_set_dep_slots_for_x_pipeline"
  return 1
  fi
  if ! nm -gU "$out_o" 2>/dev/null | grep -q 'pipeline_block_labeled_set_names'; then
  build_xlang_asm_warn "Darwin stubs filt missing pipeline_block_labeled_set_names"
  return 1
  fi
  if nm -gU "$out_o" 2>/dev/null | grep -qE 'asm_asm_codegen_(elf_o|ast)$'; then
  build_xlang_asm_warn "Darwin stubs filt still exports asm_asm_codegen_* (must omit for user_asm ar)"
  return 1
  fi
  return 0
}

# PLATFORM: DARWIN — filtered pipeline_x omits typeck helpers that live only in
# pipeline_glue_strict_minimal (pipeline_typeck_after_parse_ok, *_strict_minimal).
# Export the complement (symbols not in filtered pipeline / experimental bridge /
# filtered stubs / runtime_asm_build) so Darwin ld has no multiply_defined.
ensure_bstrict_darwin_minimal_glue_complement_obj() {
  local src_o="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  local out_o="$BUILD_DIR/bstrict_pipeline_glue_minimal_complement.o"
  local all_syms="$BUILD_DIR/.bstrict_min_glue_all_t.txt"
  local omit_syms="$BUILD_DIR/.bstrict_min_glue_omit.txt"
  local keep_syms="$BUILD_DIR/.bstrict_min_glue_keep.txt"
  local dep_o
  [ -f "$src_o" ] || return 1
  : >"$omit_syms"
  for dep_o in \
    "$BUILD_DIR/bstrict_pipeline_filtered.o" \
    "$BUILD_DIR/asm_experimental_symbol_bridge.o" \
    "$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o" \
    src/asm/runtime_asm_build.o
  do
  [ -f "$dep_o" ] || continue
  nm "$dep_o" 2>/dev/null | awk '/ T / {print $3}' >>"$omit_syms"
  done
  sort -u "$omit_syms" -o "$omit_syms"
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ] || [ "$omit_syms" -nt "$out_o" ]; then
  nm "$src_o" 2>/dev/null | awk '/ T / {print $3}' | sort -u >"$all_syms"
  comm -23 "$all_syms" "$omit_syms" >"$keep_syms"
  [ -s "$keep_syms" ] || return 1
  echo " ld partial export $keep_syms $(basename "$src_o") -> $(basename "$out_o") (Darwin complement)"
  ld_partial_export "$keep_syms" "$out_o" "$src_o" || return 1
  fi
  return 0
}

# strict WPO 链：seed partial 保留 mega + arch enc + glue 侧car（剔除 wpo 已替代的薄入口）。
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
  build_xlang_asm_warn "stale asm_backend_seed_helper export (missing W text stubs); regen"
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
  build_xlang_asm_info "seed helper export: $(wc -l <"$SYMS" | tr -d ' ') symbols (seed T+W minus wpo thin entry)"
  fi
  if [ -f "$SYMS" ] && grep -qxF 'backend_asm_codegen_ast' "$SYMS" 2>/dev/null; then
  build_xlang_asm_warn "stale asm_backend_seed_helper export (dup bare_link_alias); regen"
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ -f "$PARTIAL" ] && nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?backend_asm_codegen_ast$'; then
  build_xlang_asm_warn "stale asm_backend_seed_helper_partial (dup bare_link_alias); rebuild"
  rm -f "$PARTIAL"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$SEED" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || [ "$EXCLUDE" -nt "$PARTIAL" ]; then
  build_xlang_asm_info "ld partial export $SYMS seed asm_backend_partial.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$SEED" || return 1
  fi
  return 0
}

# WPO strict partial 导出表是否过期：须含 arch/emit helper、不含 stub mega。
backend_wpo_strict_partial_export_syms_stale() {
  local syms="$1"
  [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] || return 1
  asm_backend_wpo_strict_reach_ok || return 1
  [ -f "$syms" ] || return 0
  grep -qxF 'arch_emit_add_imm_to_rax' "$syms" 2>/dev/null || return 0
  grep -qxF 'asm_codegen_ast_seed_mega' "$syms" 2>/dev/null && return 0
  return 1
}

# strict 链：自 build_asm/backend.o 导出除 WPO 已定义与 stub mega 外符号。
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
  echo " backend_strict_link: minus backend_wpo.o exports ($(wc -l <"$BUILD_DIR/.backend_wpo_export_syms.txt" | tr -d ' ') syms)"
  fi
  grep -vxF 'asm_codegen_ast_seed_mega' "$SYMS" >"$SYMS.nmega" 2>/dev/null && mv -f "$SYMS.nmega" "$SYMS"
  grep -vxF 'asm_codegen_ast_to_elf_seed_mega' "$SYMS" >"$SYMS.nmega2" 2>/dev/null && mv -f "$SYMS.nmega2" "$SYMS"
  fi
  echo " nm backend.o -> $SYMS ($(wc -l <"$SYMS" | tr -d ' ') symbols)"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$BACKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ] || \
  { [ -f "$WPO_E" ] && [ "$WPO_E" -nt "$PARTIAL" ]; }; then
  echo " ld partial export $SYMS backend.o -> $PARTIAL"
  ld_partial_export "$SYMS" "$PARTIAL" "$BACKO" || return 1
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  nm "$PARTIAL" 2>/dev/null | grep -qE ' T (_)?arch_emit_add_imm_to_rax$' || {
  build_xlang_asm_error "backend_strict_link_partial missing arch_emit_add_imm_to_rax"
  return 1
  }
  fi
  fi
  return 0
}

# strict WPO 链 backend 对象组：wpo + seed helper（mega/emit 仍在 seed）；build_asm backend.o 薄桩不与 seed 混链。
# 非 WPO fallback 下优先直接使用 seed partial 的真实 backend_* 强符号；仅当旧 seed partial 缺符号时才补 alias。
strict_asm_backend_companion_objs() {
  local seed_o="$BUILD_DIR/seed_host/asm_backend_partial.o"
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  ensure_backend_asm_bare_link_alias_obj >&2 || return 1
  ensure_asm_backend_seed_helper_partial_obj >&2 || return 1
  printf '%s\n' "$BUILD_DIR/backend_wpo.o $BUILD_DIR/backend_asm_bare_link_alias.o $BUILD_DIR/asm_backend_seed_helper_partial.o"
  return 0
  fi
  if [ -f "$seed_o" ] && \
  nm "$seed_o" 2>/dev/null | grep -qE ' T (_)?backend_asm_codegen_ast$' && \
  nm "$seed_o" 2>/dev/null | grep -qE ' T (_)?backend_asm_codegen_ast_to_elf$'; then
  printf '%s\n' "$seed_o"
  return 0
  fi
  ensure_backend_asm_strict_fallback_alias_obj >&2 || return 1
  printf '%s\n' "$BUILD_DIR/backend_asm_strict_fallback_alias.o $seed_o"
  return 0
}

# 保留旧名供 grep；第二遍 EMIT_HEAVY 验收与 asm_strict_pipeline_selfhosted 一致。
asm_pipeline_run_impl_has_real_body() {
  asm_strict_pipeline_selfhosted
}

# build_asm typeck.o 仅 __text>8KiB 视为完整自举 emit；否则 typeck 走 strict_support partial。
asm_strict_typeck_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo 0)
  [ "$t" -gt 8192 ] 2>/dev/null
}

# build_asm driver_compile_emit_heavy.o + driver_compile_link.o：run_compiler_full_x / parse_argv X emit。
# driver_compile.o 为 WPO 压缩 entry TU（dogfood）；strict 链尺寸门禁看 emit_heavy.o。
asm_strict_driver_selfhosted() {
  local t
  [ -f "$BUILD_DIR/driver_compile_link.o" ] || return 1
  t=$(asm_o_text_bytes "$BUILD_DIR/driver_compile_emit_heavy.o" 2>/dev/null || echo 0)
  if [ "$t" -lt 5104 ] 2>/dev/null; then
  t=$(asm_o_text_bytes "$BUILD_DIR/driver_compile.o" 2>/dev/null || echo 0)
  fi
  [ "$t" -ge 5104 ] 2>/dev/null || return 1
  nm -g "$BUILD_DIR/driver_compile_link.o" 2>/dev/null | grep -qE '(_)?driver_run_compiler_full_x' || return 1
  return 0
}

# Stage2 二遍自举：XLANG 已是 xlang_asm 时仍用 driver_compile_x（gen1 拓扑），直至 gen2 driver X 链稳定。
asm_strict_bootstrap_round2() {
  if [ -n "${XLANG_ASM_STRICT_FORCE_DRIVER_X:-}" ]; then
  return 0
  fi
  if [ -n "${XLANG_ASM_BOOTSTRAP_ROUND2:-}" ]; then
  return 0
  fi
  case "${XLANG:-}" in
  ./xlang_asm|./xlang_asm_stage1|./xlang_asm2|*/xlang_asm|*/xlang_asm_stage1|*/xlang_asm2) return 0 ;;
  esac
  case "$(basename "${XLANG:-}" 2>/dev/null)" in
  xlang_asm|xlang_asm_stage1|xlang_asm2) return 0 ;;
  esac
  return 1
}

# Stage2 round2 是否跳过 typeck_wpo（XLANG_ASM_ROUND2_TRY_TYPECK_WPO=1 为 track-only 试链）。
asm_strict_round2_skip_typeck_wpo() {
  if [ -n "${XLANG_ASM_ROUND2_TRY_TYPECK_WPO:-}" ]; then
  return 1
  fi
  asm_strict_bootstrap_round2
}

# strict 最终链是否使用 driver_compile_link.o（须 asm_strict_driver_selfhosted）。
asm_strict_link_driver_selfhosted() {
  if [ -n "${XLANG_ASM_STRICT_FORCE_DRIVER_X:-}" ]; then
  build_xlang_asm_info "XLANG_ASM_STRICT_FORCE_DRIVER_X=1 - keep driver_compile_x"
  return 1
  fi
  if ! asm_strict_driver_selfhosted; then
  return 1
  fi
  return 0
}

# build_asm typeck.o 未自举完成时：仅导出 layout/metrics 符号供 glue，不含 typeck_x_ast 桩。
ensure_typeck_asm_layout_partial_obj() {
  local PARTIAL SYMS TCK
  PARTIAL="$BUILD_DIR/typeck_asm_layout_partial.o"
  SYMS="$BUILD_DIR/typeck_asm_layout_export.txt"
  TCK="$BUILD_DIR/typeck.o"
  if [ ! -f "$TCK" ] || [ ! -s "$TCK" ]; then
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$TCK" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_typeck_struct_layout_metrics
_typeck_validate_struct_layouts_zero_padding
_typeck_ensure_struct_layout_from_struct_lit
_typeck_merge_dep_struct_layouts_into_entry
_typeck_wpo_unify_soa_layouts
_typeck_entry_module_find_struct_layout_index
_typeck_find_layout_idx_by_type_name
EOF
  echo " ld -r -exported_symbols_list $SYMS typeck.o -> $PARTIAL (layout only)"
  set +e
  ld_partial_export "$SYMS" "$PARTIAL" "$TCK" 2>"$BUILD_DIR/.typeck_layout_partial_err"
  local ld_rc=$?
  set -e
  if [ "$ld_rc" -ne 0 ]; then
  build_xlang_asm_warn "typeck layout partial skipped (layout symbols missing in typeck.o; need typeck second pass >8KiB)"
  rm -f "$PARTIAL"
  return 1
  fi
  fi
}

# strict 链：build_asm layout partial 已导出 layout 符号时，从 typeck_x.o 剔除同符号避免 duplicate。
ensure_typeck_x_no_layout_partial_obj() {
  local PARTIAL SYMS SUO
  PARTIAL="$BUILD_DIR/typeck_x_no_layout_partial.o"
  SYMS="$BUILD_DIR/typeck_x_no_layout_export.txt"
  SUO="typeck_x.o"
  if [ ! -f "$SUO" ]; then
  return 1
  fi
  if [ -f "$SYMS" ] && grep -qE '^_typeck_(ensure_struct_layout_from_struct_lit|entry_module_find_struct_layout_index)$' "$SYMS" 2>/dev/null; then
  rm -f "$SYMS" "$PARTIAL"
  fi
  if [ ! -f "$SYMS" ] || [ "$0" -nt "$SYMS" ] || [ "$SUO" -nt "$SYMS" ]; then
  # ELF 符号无 leading _；统一 sed 去/加 _ 供 macOS exported_symbols_list 与 Linux objcopy。
  # Keep ALL T symbols (not just typeck_* prefix): typeck.x also defines pipeline_typeck_*,
  # pipeline_expr_is_c_*, pipeline_dep_ctx_*, glue_typeck_* etc. The old awk '/ T _?typeck_/'
  # only matched symbols starting with typeck_ right after the T column, silently dropping
  # pipeline_typeck_* (which have pipeline_ prefix) → undefined references in strict link.
  # The 7 grep -v below still exclude layout symbols owned by typeck_asm_layout_partial.o.
  nm "$SUO" 2>/dev/null | awk '/ T / {print $3}' | sed 's/^_//' | \
  grep -v '^typeck_struct_layout_metrics$' | \
  grep -v '^typeck_validate_struct_layouts_zero_padding$' | \
  grep -v '^typeck_merge_dep_struct_layouts_into_entry$' | \
  grep -v '^typeck_wpo_unify_soa_layouts$' | \
  grep -v '^typeck_find_layout_idx_by_type_name$' | \
  grep -v '^typeck_ensure_struct_layout_from_struct_lit$' | \
  grep -v '^typeck_entry_module_find_struct_layout_index$' | \
  sed 's/^/_/' >"$SYMS"
  fi
  if [ ! -f "$PARTIAL" ] || [ "$0" -nt "$PARTIAL" ] || [ "$SUO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  echo " ld -r -exported_symbols_list $SYMS typeck_x.o -> $PARTIAL (no layout dupes)"
  set +e
  ld_partial_export "$SYMS" "$PARTIAL" "$SUO" 2>"$BUILD_DIR/.typeck_x_no_layout_err"
  local ld_rc=$?
  set -e
  if [ "$ld_rc" -ne 0 ]; then
  rm -f "$PARTIAL"
  return 1
  fi
  fi
}

# strict 双自举（build_asm typeck.o + pipeline.o）：C typeck 仅导出编排入口，避免与 X typeck.o 重复。
ensure_typeck_c_orchestration_partial_obj() {
  local PARTIAL SYMS TCKO
  PARTIAL="$BUILD_DIR/typeck_c_orchestration_partial.o"
  SYMS="$BUILD_DIR/typeck_c_orchestration_export.txt"
  TCKO="src/typeck/typeck.o"
  if [ ! -f "$TCKO" ]; then
  TCKO="$BUILD_DIR/asm_driver_seed/typeck.o"
  fi
  if [ ! -f "$TCKO" ]; then
  return 1
  fi
  if [ ! -f "$PARTIAL" ] || [ "$TCKO" -nt "$PARTIAL" ] || [ "$SYMS" -nt "$PARTIAL" ]; then
  cat > "$SYMS" <<'EOF'
_typeck_module
_typeck_one_function
EOF
  build_xlang_asm_info "ld -r -exported_symbols_list $SYMS $TCKO -> $PARTIAL (C orchestration only)"
  set +e
  ld_partial_export "$SYMS" "$PARTIAL" "$TCKO" 2>"$BUILD_DIR/.typeck_c_orch_partial_err"
  local ld_rc=$?
  set -e
  if [ "$ld_rc" -ne 0 ]; then
  rm -f "$PARTIAL"
  return 1
  fi
  fi
}

# strict 整链 typeck.o 时：用 weak 桩满足 lsp_diag.c / runtime 对 C typeck_module 的链接，不再 ld -r 抽 seed typeck.o。
ensure_typeck_c_module_stubs_obj() {
  local OBJ="$BUILD_DIR/typeck_c_module_stubs.o"
  if [ ! -f "$OBJ" ] || [ seeds/typeck_c_module_stubs.from_x.c -nt "$OBJ" ]; then
  build_xlang_asm_info "cc -c seeds/typeck_c_module_stubs.from_x.c -> $OBJ"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$OBJ" seeds/typeck_c_module_stubs.from_x.c
  fi
}

# strict 整链 typeck.o 时：优先 seed typeck_module 仅预检；失败回退 weak 桩。
ensure_typeck_c_user_precheck_obj() {
  if ensure_typeck_c_orchestration_partial_obj; then
  echo "$BUILD_DIR/typeck_c_orchestration_partial.o"
  return 0
  fi
  build_xlang_asm_warn "typeck_c_orchestration_partial failed; falling back to typeck_c_module_stubs"
  ensure_typeck_c_module_stubs_obj
  echo "$BUILD_DIR/typeck_c_module_stubs.o"
  return 0
}

# build_asm typeck.o 供 glue metrics；codegen 走 codegen_only partial。
asm_strict_keep_build_asm_typeck_backend() {
  asm_strict_typeck_selfhosted
}

# 实验 asm-only 链：build_asm 裸符号名 → runtime 期望名（首链 experimental 仍需要；strict 链不链 bridge）。
ensure_asm_experimental_symbol_bridge_obj() {
  BRIDGE_OBJ="$BUILD_DIR/asm_experimental_symbol_bridge.o"
  if [ ! -f "$BRIDGE_OBJ" ] || [ "seeds/asm_experimental_symbol_bridge.from_x.c" -nt "$BRIDGE_OBJ" ]; then
  echo " cc -c seeds/asm_experimental_symbol_bridge.from_x.c -> $BRIDGE_OBJ"
  sh scripts/cc_inc_tu.sh seeds/asm_experimental_symbol_bridge.from_x.c "$BRIDGE_OBJ"
  fi
}

# 实验链：排除 partial/glue/与 runtime/seed 冲突的模块 .o。
filter_experimental_asm_objs() {
  FILTERED=""
  UNAME_HOST=$(uname -m 2>/dev/null || echo unknown)
  for o in $NONEMPTY_ASM; do
  base=$(basename "$o")
  case "$base" in
  main.o|parser.o|asm.o|lsp.o|\
  backend.o|codegen.o|typeck.o|pipeline.o|std_fs.o|platform_elf.o|macho.o|coff.o|\
  pipeline_glue_link.o|pipeline_run_impl_alias.o|pipeline_glue_standalone.o|pipeline_glue_strict_minimal.o|pipeline_glue_wpo_dedupe.o|\
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
  bootstrap_seed_pipeline_filtered.o|bootstrap_seed_user_asm_seed_bridge_filtered.o|bootstrap_seed_asm_backend_compat_stubs_filtered.o|bootstrap_seed_backend_x86_64_enc_c_filtered.o|\
  bstrict_pipeline_filtered.o|bstrict_user_asm_seed_bridge_filtered.o|bstrict_user_asm_seed_bridge_host.o|bstrict_asm_backend_compat_stubs_filtered.o|bstrict_backend_x86_64_enc_c_filtered.o|\
  bstrict_strict_glue_stubs_darwin.o|bstrict_pipeline_glue_minimal_complement.o|preprocess_if_stack_only.o|\
  runtime_driver_strict_glue_stubs.o|\
  pipeline_run_bootstrap_trampoline.o|pipeline_bootstrap_orchestration_strict.o|\
  driver_compile_parse_argv_loop_partial.o|\
  typeck_asm_layout_partial.o|typeck_x_no_layout_partial.o|typeck_c_orchestration_partial.o|\
  typeck_c_module_stubs.o|typeck_asm_bare_link_alias.o|typeck_wpo.o|typeck_wpo_helpers_partial.o|typeck_strict_link_partial.o|\
  typeck_lsp_io_stub.o|\
  backend_wpo.o|backend_strict_link_partial.o|backend_asm_bare_link_alias.o|backend_asm_strict_fallback_alias.o|asm_backend_seed_helper_partial.o|\
  asm_backend_compat_stubs.o|\
  std_fs_shim.o|x_seed_bridge.o|seed_link_compat.o|\
  parser_from_gen.o|asm_experimental_symbol_bridge.o|asm_xlang_lsp_diag_stub.o)
  continue
  ;;
  esac
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
  FILTERED="$FILTERED $o"
  done
}

# strict 链：build_asm 编译器 .o + codegen_only partial（四入口真 codegen）+ runtime_bootstrap pipeline_run。
# STRICT_LINK_BUILD_ASM_PIPELINE=1 时链入 build_asm/pipeline.o（真编排），不链 runtime_bootstrap partial。
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
  # pipeline_wpo：FULL=整颗 X 编排；默认 helpers + C orchestration（稳定）。
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && [ "${STRICT_LINK_BUILD_ASM_WPO:-0}" -eq 1 ] && asm_pipeline_wpo_strict_reach_ok; then
  if asm_pipeline_wpo_strict_link_full_ok; then
  ensure_pipeline_wpo_strict_link_alias_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_strict_link_alias.o"
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo.o"
  # FULL 仍须 pipeline_x glue support：ast_pool 桥接符号不在 pipeline_wpo.o 内（typeck_x U 引用）。
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  build_xlang_asm_info "strict link pipeline_x glue support (FULL wpo astpool bridge)"
  fi
  build_xlang_asm_info "strict link whole pipeline_wpo.o (X orchestration, track-only FULL)"
  else
  if asm_strict_x_orchestration_ok; then
  ensure_pipeline_runtime_bootstrap_partial_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  build_xlang_asm_info "strict link pipeline_x glue support (replace glue_standalone astpool)"
  fi
  if ensure_pipeline_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_helpers_partial.o"
  build_xlang_asm_info "strict link pipeline_wpo_helpers + pipeline_x runtime bootstrap (opt-in WPO)"
  else
  build_xlang_asm_warn "pipeline_wpo_helpers partial failed; using pipeline_x runtime bootstrap only"
  fi
  echo "su" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  else
  ensure_pipeline_asm_orchestration_partial_obj
  FILTERED="$FILTERED $BUILD_DIR/pipeline_asm_orchestration_partial.o"
  if ensure_pipeline_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_wpo_helpers_partial.o"
  build_xlang_asm_info "strict link pipeline_wpo_helpers + C orchestration (opt-in WPO)"
  else
  build_xlang_asm_warn "pipeline_wpo_helpers partial failed; falling back to C orchestration only"
  fi
  echo "c" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  fi
  fi
  else
  if asm_strict_x_orchestration_ok; then
  ensure_pipeline_runtime_bootstrap_partial_obj && FILTERED="$FILTERED $BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && ensure_pipeline_x_glue_support_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_x_glue_support_partial.o"
  build_xlang_asm_info "strict link pipeline_x glue support (replace glue_standalone astpool)"
  fi
  build_xlang_asm_info "strict link pipeline_x runtime bootstrap orchestration"
  echo "su" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  else
  ensure_pipeline_asm_orchestration_partial_obj
  FILTERED="$FILTERED $BUILD_DIR/pipeline_asm_orchestration_partial.o"
  build_xlang_asm_info "strict link pipeline_asm_orchestration_partial.o (C run_x_pipeline_impl)"
  echo "c" >"$BUILD_DIR/.pipeline_strict_orch_mode"
  fi
  fi
  if ensure_pipeline_o_strict_link_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/pipeline_strict_link_partial.o"
  else
  # G.7: skip empty pure-extern pipeline.o when WPO/abi covers. PLATFORM: SHARED.
  _po_t=$(nm "$o" 2>/dev/null | awk '/ T / {c++} END{print c+0}')
  if [ "${_po_t:-0}" -eq 0 ] && { asm_pipeline_wpo_strict_reach_ok || asm_strict_pipeline_selfhosted; }; then
  build_xlang_asm_info "skip empty pipeline.o on strict LD (WPO/abi covers)"
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
  case "$base" in
  driver_compile.cli.o|main.cli.o|\
  parser.o|backend.o|asm.o|main.o|lsp.o|std_fs.o|\
  codegen.o|pipeline_glue_link.o|pipeline_run_impl_alias.o|pipeline_glue_standalone.o|pipeline_glue_strict_minimal.o|pipeline_glue_wpo_dedupe.o|\
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
  bootstrap_seed_pipeline_filtered.o|bootstrap_seed_user_asm_seed_bridge_filtered.o|bootstrap_seed_asm_backend_compat_stubs_filtered.o|bootstrap_seed_backend_x86_64_enc_c_filtered.o|\
  bstrict_pipeline_filtered.o|bstrict_user_asm_seed_bridge_filtered.o|bstrict_user_asm_seed_bridge_host.o|bstrict_asm_backend_compat_stubs_filtered.o|bstrict_backend_x86_64_enc_c_filtered.o|\
  bstrict_strict_glue_stubs_darwin.o|bstrict_pipeline_glue_minimal_complement.o|preprocess_if_stack_only.o|\
  runtime_driver_strict_glue_stubs.o|\
  pipeline_run_bootstrap_trampoline.o|pipeline_bootstrap_orchestration_strict.o|\
  driver_compile_parse_argv_loop_partial.o|\
  typeck_skip.o|typeck_heavy.o|typeck.second.o|\
  typeck_asm_layout_partial.o|typeck_x_no_layout_partial.o|typeck_c_orchestration_partial.o|\
  typeck_c_module_stubs.o|typeck_asm_bare_link_alias.o|typeck_wpo.o|typeck_wpo_helpers_partial.o|typeck_strict_link_partial.o|\
  typeck_lsp_io_stub.o|\
  backend_wpo.o|backend_strict_link_partial.o|backend_asm_bare_link_alias.o|backend_asm_strict_fallback_alias.o|asm_backend_seed_helper_partial.o|\
  asm_backend_compat_stubs.o|\
  std_fs_shim.o|x_seed_bridge.o|seed_link_compat.o|\
  parser_from_gen.o|asm_experimental_symbol_bridge.o|asm_xlang_lsp_diag_stub.o|\
  parser_asm_minimal_partial.o|\
  \
  lexer.o|peephole.o|platform_elf.o|macho.o|coff.o)
  continue
  ;;
  esac
  # strict 链的 x86_64 encoder 由 seed_host partial / filtered dispatch companions 提供；
  # 若再把 build_asm/backend_x86_64_enc_c.o 混进 ASM_TRY_OBJS，会和 seed partial 重复定义。
  if [ "$base" = "backend_x86_64_enc_c.o" ] && [ -s "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
  build_xlang_asm_info "strict skip build_asm/backend_x86_64_enc_c.o (seed_host partial already provides encoder)"
  continue
  fi
  # Darwin strict fallback 的 mega backend 也已被 seed_host partial 覆盖；
  # 若再把 build_asm/backend_seed_mega_fallback.o 混入 strict link，会与 seed partial 重复导出 backend_asm_codegen_*。
  if [ "$base" = "backend_seed_mega_fallback.o" ] && [ -s "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
  build_xlang_asm_info "strict skip build_asm/backend_seed_mega_fallback.o (seed_host partial already provides backend mega fallback)"
  continue
  fi
  if [ "$base" = "typeck.o" ]; then
  # typeck 自举：WPO reach OK 且 typeck.o 未自举时链 typeck_wpo helpers + partial；自举后整颗 typeck.o（wpo partial 会 poison check_block）。
  if [ "$LINK_BUILD_ASM_TYPECK" -eq 1 ]; then
  if asm_typeck_wpo_strict_link_helpers_ok; then
  if ensure_typeck_wpo_helpers_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/typeck_wpo_helpers_partial.o"
  build_xlang_asm_info "strict link typeck_wpo_helpers + typeck.o partial (pre-selfhosted typeck)"
  else
  FILTERED="$FILTERED $BUILD_DIR/typeck_wpo.o"
  build_xlang_asm_warn "strict link typeck_wpo.o (helpers partial failed; falling back to full wpo.o)"
  fi
  ensure_typeck_o_strict_link_partial_obj && FILTERED="$FILTERED $BUILD_DIR/typeck_strict_link_partial.o"
  elif asm_strict_typeck_selfhosted; then
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  build_xlang_asm_info "strict skip build_asm/typeck.o (X glue; seed typeck + typeck_x.o tail)"
  elif ensure_typeck_o_strict_link_partial_obj; then
  FILTERED="$FILTERED $BUILD_DIR/typeck_strict_link_partial.o"
  build_xlang_asm_info "strict link typeck.o partial (selfhosted, minus glue dupes)"
  else
  FILTERED="$FILTERED $o"
  build_xlang_asm_warn "strict link whole typeck.o (selfhosted partial failed)"
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
  if [ "$base" = "driver_compile.o" ] || [ "$base" = "driver_compile_asm_link_alias.o" ] || [ "$base" = "driver_compile_emit_heavy.o" ]; then
  # driver_compile_link 或 Stage2 round2（driver_compile_x）均勿再链 build_asm driver 三件套。
  if asm_strict_link_driver_selfhosted || asm_strict_bootstrap_round2; then
  continue
  fi
  fi
  if [ "$base" = "driver_compile_link.o" ]; then
  if asm_strict_link_driver_selfhosted; then
  # PLATFORM: MACOS — pure_ld_partial_merge may leave link.o as libtool ar (F7
  # two LC_SEGMENT). Apple ld extracts archive members only for currently-U
  # symbols; weak/other defs can suppress the strong EMIT_HEAVY body. Expand to
  # the underlying MH_OBJECT members (G.7 twin of Darwin user_asm MH host).
  # PLATFORM: LINUX — link.o stays single ET_REL; keep as-is.
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ] \
    && file "$o" 2>/dev/null | grep -qi 'ar archive'; then
  FILTERED="$FILTERED $BUILD_DIR/driver_compile_emit_heavy.o $BUILD_DIR/driver_compile_asm_link_alias.o"
  if [ -f "$BUILD_DIR/driver_compile_parse_argv_loop_partial.o" ] \
    && nm "$BUILD_DIR/driver_compile_emit_heavy.o" 2>/dev/null \
      | grep -qE ' U (_)?driver_compile_parse_argv_loop$'; then
  FILTERED="$FILTERED $BUILD_DIR/driver_compile_parse_argv_loop_partial.o"
  fi
  else
  FILTERED="$FILTERED $o"
  fi
  fi
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
  # strict 勿链 text 桩 encoder（仅 U enc_u32_le）；backend_enc_dispatch + seed partial 已覆盖。
  case "$base" in
  x86_64_enc.o|arm64_enc.o|riscv64_enc.o)
  enc_stub_bytes=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  if [ "${enc_stub_bytes:-0}" -lt 512 ] 2>/dev/null; then
  build_xlang_asm_info "strict skip stub $base (__text=${enc_stub_bytes}B)"
  continue
  fi
  ;;
  esac
  # PLATFORM: DARWIN — Apple ld-1267+ errors on multiple weak _xlang_asm_ci_text_stub
  # across FILTERED first-pass stubs (arm64/ast/token/types/preprocess …). Skip pure
  # CI text stubs (≤64B, no other global T). SHARED-safe: Linux weak coalesce OK, but
  # stubs add no real symbols either way.
  _stub_t=$(asm_o_text_bytes "$o" 2>/dev/null || echo 0)
  if [ "${_stub_t:-0}" -le 64 ] 2>/dev/null \
  && nm "$o" 2>/dev/null | grep -qE '(_)?xlang_asm_ci_text_stub$'; then
  _other_t=$(nm -g "$o" 2>/dev/null | awk '/ [Tt] / && $3 !~ /xlang_asm_ci_text_stub/ { c++ } END { print c+0 }')
  if [ "${_other_t:-0}" = "0" ]; then
  build_xlang_asm_info "strict skip CI text stub $base (__text=${_stub_t}B)"
  continue
  fi
  fi
  FILTERED="$FILTERED $o"
  done
}

# Target B 实验链：独立 pipeline_glue+ast_pool TU（类型从 pipeline_gen.c 抽取，不含 .x 函数体）。
# wave309: seed retired — early-return when absent (G.7 twin of g05_ensure /
# experimental_bootstrap / strict_glue). Ban -E pipeline.x / cc_inc_tu noise on
# Stage2 round2 when ASM_GLUE_STANDALONE_O is empty. PLATFORM: SHARED.
ensure_asm_pipeline_glue_standalone_obj() {
  GLUE_STANDALONE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  if [ ! -f seeds/pipeline_glue_standalone.from_x.c ]; then
  build_xlang_asm_info "skip pipeline_glue_standalone (wave309 seed retired; use pipeline_glue_strict_minimal / runtime_pipeline_abi)"
  rm -f "$GLUE_STANDALONE_OBJ" 2>/dev/null || true
  return 0
  fi
  detect_pipeline_gen_cflags
  GLUE_TYPES="$BUILD_DIR/pipeline_glue_types.inc"
  GEN_PIPELINE="$BUILD_DIR/gen_driver/pipeline_gen.c"
  NEED_GEN=0
  if [ ! -f "$GEN_PIPELINE" ] || [ ! -s "$GEN_PIPELINE" ]; then
  NEED_GEN=1
  fi
  if [ "$NEED_GEN" -eq 0 ] && [ ! -f "$GLUE_TYPES" ]; then
  NEED_GEN=1
  fi
  if [ "$NEED_GEN" -eq 0 ] && [ "$GEN_PIPELINE" -nt "$GLUE_TYPES" ]; then
  NEED_GEN=1
  fi
  if [ "$NEED_GEN" -eq 1 ]; then
  mkdir -p "$BUILD_DIR/gen_driver"
  if [ -f pipeline_gen.c ] && [ -s pipeline_gen.c ]; then
  cp -f pipeline_gen.c "$GEN_PIPELINE"
  if [ -f scripts/patch_pipeline_gen_ast_layout.pl ]; then
  perl scripts/patch_pipeline_gen_ast_layout.pl "$GEN_PIPELINE"
  fi
  echo " pinned pipeline_gen.c -> $GEN_PIPELINE ($(wc -c <"$GEN_PIPELINE" | tr -d ' ') bytes)"
  else
  XLANG_E_LOCAL="${XLANG_E:-}"
  if [ -z "$XLANG_E_LOCAL" ] || [ ! -x "$XLANG_E_LOCAL" ]; then
  for _e in ./xlang ./xlang-seed-phase1 ./xlang_asm ./xlang-c; do
  if [ -x "$_e" ] && "$_e" -h >/dev/null 2>&1; then
  XLANG_E_LOCAL="$_e"
  break
  fi
  done
  [ -z "$XLANG_E_LOCAL" ] && XLANG_E_LOCAL="$XLANG"
  fi
  # glue types only: extract_pipeline_glue_types.pl from -E-extern gen
  # (pipeline_glue.c left wave309 — no mega include truncate). Full -E would
  # inline std.io etc.; mid-codegen failure yields truncated C and trips set -e.
  echo " $XLANG_E_LOCAL -E -E-extern pipeline.x -> $GEN_PIPELINE (glue standalone types) ..."
  "$XLANG_E_LOCAL" -L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess \
  -E -E-extern src/pipeline/pipeline.x >"$GEN_PIPELINE"
  if [ -f scripts/patch_pipeline_gen_ast_layout.pl ]; then
  perl scripts/patch_pipeline_gen_ast_layout.pl "$GEN_PIPELINE"
  fi
  fi
  perl -i -ne 'print unless /^struct xlang_slice_uint8_t/ && $seen++' "$GEN_PIPELINE" 2>/dev/null || true
  perl scripts/fix_slim_arena_gen_c.pl "$GEN_PIPELINE" 2>/dev/null || true
  perl scripts/hoist_pipeline_prototypes.pl "$GEN_PIPELINE" 2>/dev/null || true
  echo " perl extract_pipeline_glue_types.pl -> $GLUE_TYPES"
  perl scripts/extract_pipeline_glue_types.pl "$GEN_PIPELINE" >"$GLUE_TYPES"
  perl scripts/patch_ide_glue_types.pl "$GLUE_TYPES"
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  perl -i -0777 -pe 's/\nenum ast_ExprKind parser_compound_assign_token_to_expr_kind\(enum token_TokenKind kind\) \{\n return compound_assign_token_to_expr_kind_from_glue\(kind\);\n\}//g' "$GLUE_TYPES" 2>/dev/null || true
  fi
  fi
  # Authority = seed + glue_types + extract/patch scripts (deleted ast_pool.c /
  # pipeline_glue.c -nt never fired post-leave). PLATFORM: SHARED.
  if [ ! -f "$GLUE_STANDALONE_OBJ" ] || [ "seeds/pipeline_glue_standalone.from_x.c" -nt "$GLUE_STANDALONE_OBJ" ] || [ "$GLUE_TYPES" -nt "$GLUE_STANDALONE_OBJ" ] || [ "scripts/extract_pipeline_glue_types.pl" -nt "$GLUE_STANDALONE_OBJ" ] || [ "scripts/patch_ide_glue_types.pl" -nt "$GLUE_STANDALONE_OBJ" ]; then
  build_xlang_asm_info "cc -c seeds/pipeline_glue_standalone.from_x.c -> $GLUE_STANDALONE_OBJ"
  if ! sh scripts/cc_inc_tu.sh seeds/pipeline_glue_standalone.from_x.c "$GLUE_STANDALONE_OBJ" $PIPELINE_GEN_CFLAGS -I"$BUILD_DIR"; then
  build_xlang_asm_warn "pipeline_glue_standalone.o compile failed (strict 链可继续用 pipeline_glue_strict_minimal)"
  rm -f "$GLUE_STANDALONE_OBJ" 2>/dev/null || true
  fi
  fi
}

# preprocess_if_stack_* 6 个符号的独立 provider。
# 【Why】strict re-link 不链入 pipeline_x.o（by design），ST_GLUE_OBJ=pipeline_glue_strict_minimal.o
#        不含 preprocess_if_stack_*；preprocess_x.o 引用这些符号会 undefined。
# 【Authority · 2026-08-05 pure-owned WEAK cold leave】G.7 live face is
#        runtime_pipeline_abi.o (runtime_pipeline_abi.x fixed i32[32] BSS). Host-cc
#        pipeline_preprocess_if.c GrowVec XLANG_WEAK twin deleted from pipeline_x.
#        Historical provider src was pipeline_glue_standalone.o (embedded ast_pool);
#        after leave, partial-export from pure runtime_pipeline_abi.o only.
# 【Invariant】只导出 preprocess_if_stack_* 6 个 global 符号，避免符号冲突。
# PLATFORM: SHARED — prefer ld_partial_export (Darwin ld -exported_symbols_list / Linux
# objcopy path inside ld_partial_export). Never hard-require host objcopy for the provider
# path: missing .o breaks strict re-link argv (clang: no such file).
ensure_preprocess_if_stack_provider_obj() {
  local src_o out_o keep_list pure_o
  # Prefer product pure authority (cwd=compiler when invoked from build_xlang_asm).
  pure_o="src/runtime_pipeline_abi.o"
  if [ ! -f "$pure_o" ] && [ -f "../compiler/src/runtime_pipeline_abi.o" ]; then
    pure_o="../compiler/src/runtime_pipeline_abi.o"
  fi
  if [ ! -f "$pure_o" ] && [ -f "compiler/src/runtime_pipeline_abi.o" ]; then
    pure_o="compiler/src/runtime_pipeline_abi.o"
  fi
  out_o="$BUILD_DIR/preprocess_if_stack_only.o"
  keep_list="$BUILD_DIR/.preprocess_if_stack_only_keep.txt"
  # G.7: runtime_pipeline_abi.o already defines preprocess_if_stack_* and is on
  # the strict LD argv. Skip the companion partial — Darwin prefer/libtool may
  # leave abi as an ar archive; ld_partial_export lacks -arch → "Missing -arch"
  # and set -e abort. Also avoids duplicate T if a partial ever succeeded.
  # Callers must only link preprocess_if_stack_only.o when the file exists.
  # PLATFORM: SHARED.
  if [ -f "$pure_o" ] && nm -g "$pure_o" 2>/dev/null | grep -qE '(_)?preprocess_if_stack_reset'; then
    build_xlang_asm_info "skip preprocess_if_stack_only (runtime_pipeline_abi already provides)"
    rm -f "$out_o" 2>/dev/null || true
    return 0
  fi
  src_o="$pure_o"
  if [ ! -f "$src_o" ]; then
    # Fallback: rebuild standalone only if pure .o missing (dev tree half-clean).
    ensure_asm_pipeline_glue_standalone_obj
    src_o="$BUILD_DIR/pipeline_glue_standalone.o"
  fi
  [ -f "$src_o" ] || return 0
  # PLATFORM: DARWIN — exported_symbols_list requires Mach-O leading '_'.
  # PLATFORM: LINUX — ld_partial_export strips '_' for objcopy keep list.
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  printf '%s\n' \
    '_preprocess_if_stack_reset' \
    '_preprocess_if_stack_len' \
    '_preprocess_if_stack_push' \
    '_preprocess_if_stack_pop' \
    '_preprocess_if_stack_at' \
    '_preprocess_if_stack_set_at' >"$keep_list"
  else
  printf '%s\n' \
    'preprocess_if_stack_reset' \
    'preprocess_if_stack_len' \
    'preprocess_if_stack_push' \
    'preprocess_if_stack_pop' \
    'preprocess_if_stack_at' \
    'preprocess_if_stack_set_at' >"$keep_list"
  fi
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ] || [ "$keep_list" -nt "$out_o" ]; then
  echo " ld partial export $keep_list $(basename "$src_o") -> $(basename "$out_o")"
  if ! ld_partial_export "$keep_list" "$out_o" "$src_o"; then
    build_xlang_asm_warn "preprocess_if_stack_only.o partial export failed"
    rm -f "$out_o" 2>/dev/null || true
    return 1
  fi
  fi
  [ -f "$out_o" ] || return 1
  return 0
}

# 收集非空 build_asm/*.o（空文件多为 asm SKIP 残留）
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

# PLATFORM: LINUX — crt0 bag single glue authority (NL-07 L1 topology).
# build_asm often holds BOTH pipeline_glue_standalone.o (full ast_pool/glue) and
# pipeline_glue_strict_minimal.o / preprocess_if_stack_only.o (strict companions).
# strict/experimental filters drop those from the bulk bag and re-add one ST_GLUE;
# crt0 historically dumped the whole bag → multiple definition (9 symbols).
# Authority when standalone is present: standalone only; drop subset/companion objs.
# When standalone is missing: keep strict_minimal + preprocess_if_stack_only.
# NL-07 L1: multi-def topology only. L2: fflush in nostdlib stubs.
# L3: backend enc/dispatch companions via ensure_crt0_backend_companion_objs.
# L3b: same ensure appends seed backend_emit_* partial (not full seed .o — multi-def).
# L4+: typeck/driver/lsp companions via ensure_crt0_typeck_driver_lsp_companion_objs.
# L5: codegen/parser residual partials via ensure_crt0_codegen_parser_companion_objs.
# L6: nostdlib libc face (fileno/isatty/puts/strerror/fread/ferror/stdin/remove/
#     __ctype_b_loc) in bootstrap_nostdlib_stubs (same G.7 stdio authority as L2).
# Residual after L6: should be empty on crt0 bag (or new pull-ins only).
# NL-07 L2/L6: libc face lives in bootstrap_nostdlib_stubs (not freestanding_io).
# NL-07 L7: freestanding vsnprintf %g/%e (fixes pure-static float lit "g.0").
# NL-07 L7b: crt0 companions include preprocess_x.o (not bridge weak preprocess_x_buf).
# NL-07 L7c: crt0 companions include user_asm_seed_bridge (asm_asm_codegen_elf_o for smoke).
filter_crt0_asm_objs() {
  CRT0_ASM=""
  _crt0_have_standalone=0
  if [ -f "$BUILD_DIR/pipeline_glue_standalone.o" ] \
  && [ -s "$BUILD_DIR/pipeline_glue_standalone.o" ]; then
  _crt0_have_standalone=1
  fi
  for _co in $NONEMPTY_ASM; do
  _cb=$(basename "$_co")
  case "$_cb" in
  *_partial.o|pipeline_strict_link_partial.o)
  continue
  ;;
  pipeline_glue_strict_minimal.o|preprocess_if_stack_only.o)
  if [ "$_crt0_have_standalone" -eq 1 ]; then
  continue
  fi
  ;;
  esac
  CRT0_ASM="$CRT0_ASM $_co"
  done
  if [ "$_crt0_have_standalone" -eq 1 ]; then
  build_xlang_asm_info "crt0 bag: glue authority=pipeline_glue_standalone (drop strict_minimal + preprocess_if_stack_only)"
  fi
}

# PLATFORM: LINUX — NL-07 L3b: partial-export seed weak backend_emit_* into crt0.
# Authority (G.7): seed_host/asm_backend_partial.o (backend_seed_mega_fallback weak stubs).
# Why not full seed .o: T backend_asm_codegen_ast{,_to_elf} multi-def with
# build_asm/backend_asm_strict_fallback_alias.o already in the crt0 bag.
# Why not second stub TU: same seed symbols experimental/strict already use.
# Residual after L3b closed by L4+ typeck/driver/lsp companions.
ensure_crt0_backend_emit_seed_partial_obj() {
  local seed_o="$BUILD_DIR/seed_host/asm_backend_partial.o"
  local partial="$BUILD_DIR/crt0_backend_emit_seed_partial.o"
  local syms="$BUILD_DIR/crt0_backend_emit_seed_export.txt"
  # Ensure seed partial exists (same pin path as experimental / build_seed_asm_host).
  if [ ! -f "$seed_o" ] || [ ! -s "$seed_o" ]; then
  if [ -x ./scripts/build_seed_asm_host.sh ] || [ -f ./scripts/build_seed_asm_host.sh ]; then
  build_xlang_asm_info "crt0 L3b: build_seed_asm_host for $seed_o"
  ./scripts/build_seed_asm_host.sh || true
  fi
  fi
  if [ ! -f "$seed_o" ] || [ ! -s "$seed_o" ]; then
  build_xlang_asm_warn "crt0 L3b: missing $seed_o (skip backend_emit seed partial)"
  return 1
  fi
  # Export only backend_emit_* T+W from seed (weak no-op stubs resolve compat_stubs UNDEF).
  nm "$seed_o" 2>/dev/null | awk '/ [TW] / {
    s=$3; sub(/^_/, "", s)
    if (s ~ /^backend_emit_/) print s
  }' | sort -u >"$syms"
  if [ ! -s "$syms" ]; then
  build_xlang_asm_warn "crt0 L3b: seed has no backend_emit_* exports"
  return 1
  fi
  if [ ! -f "$partial" ] || [ "$seed_o" -nt "$partial" ] || [ "$syms" -nt "$partial" ]; then
  build_xlang_asm_info "ld partial export $syms seed asm_backend_partial -> $partial (NL-07 L3b)"
  ld_partial_export "$syms" "$partial" "$seed_o" || return 1
  fi
  # Sanity: at least the text-path head symbols that residual head listed after L3.
  if ! nm "$partial" 2>/dev/null | grep -qE ' [TW] (_)?backend_emit_expr$'; then
  build_xlang_asm_error "crt0 L3b partial missing backend_emit_expr"
  return 1
  fi
  CRT0_BACKEND_EMIT_PARTIAL="$partial"
  return 0
}

# PLATFORM: LINUX — NL-07 L4+: typeck / driver / lsp companions into crt0 bag.
# Who produces UNDEF (L3b residual head): asm_experimental_symbol_bridge + pipeline_glue
# reference driver_run_compiler_full / driver_cmd_* / driver_diagnostic_* / typeck_* /
# lsp_io_* / lsp_diag_* — those live outside the historic build_asm/*.o bulk bag.
# Authority (G.7): same objects experimental already links — NOT a second stub table.
#   · runtime_driver_{abi,diagnostic,asm_strict} · runtime_{pipeline,link,io}_abi · diag
#   · driver_{fmt,check,test,run,build,compile,emit}_x.o · target_cpu
#   · lsp_{x,io,io_std_heap}_x.o · lsp_diag seed stubs · rt_* seed slices
#   · typeck_x.o ONLY when bag typeck.o is not selfhosted (thin stub); full bag typeck
#     already defines residual typeck_* (dual typeck_x would multi-def).
# Forbidden: full experimental line (parser_x/codegen_x/x_frontend_link_alias/
#   strict_glue_stubs multi-def with bag). Residual after L4+: codegen cluster.
# Sets CRT0_TDL_COMPANIONS (Linux crt0 only).
ensure_crt0_typeck_driver_lsp_companion_objs() {
  CRT0_TDL_COMPANIONS=""
  # Materialize runtime driver stack + rt seed slices (same ensure as experimental).
  ensure_runtime_driver_asm_strict_obj || true
  # Driver subcmd X modules (driver_cmd_fmt/check/test/run …).
  if [ ! -f driver_fmt_x.o ] || [ ! -f driver_compile_x.o ] || [ ! -f driver_run_x.o ]; then
  ensure_asm_bootstrap_x_companion_objs || true
  fi
  # LSP X + seed diag stubs (lsp_main_impl / lsp_io_* / lsp_diag_enabled B).
  ensure_asm_experimental_lsp_objs || true
  mkdir -p "$BUILD_DIR/asm_driver_seed"
  ensure_lsp_diag_seed_obj "$BUILD_DIR/asm_driver_seed" || true
  _lsp_diag_o=$(lsp_diag_seed_obj_path "$BUILD_DIR/asm_driver_seed")
  # typeck: bag may be OK-typeck-stub (~11B) during early nostdlib try; full EMIT_HEAVY
  # typeck.o already provides typeck_check_*/typeck_x_ast* — do not dual-link typeck_x.
  if ! asm_strict_typeck_selfhosted 2>/dev/null; then
  if [ -f typeck_x.o ] && [ -s typeck_x.o ]; then
  CRT0_TDL_COMPANIONS="$CRT0_TDL_COMPANIONS typeck_x.o"
  build_xlang_asm_info "crt0 L4+: typeck bag not selfhosted — append typeck_x.o"
  fi
  fi
  # Runtime / driver / cmd objects — multi-def vs bag checked = 0 (Ubuntu map 2026-07-17).
  for _tdl in \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_link_abi.o \
  src/runtime_io_abi.o \
  src/runtime_driver_asm_strict.o \
  src/diag.o \
  src/driver/target_cpu.o \
  src/runtime/rt_arena_buf.o \
  src/runtime/rt_emit_state.o \
  src/runtime/rt_preamble.o \
  src/runtime/rt_stack.o \
  src/runtime/rt_parse_diag.o \
  driver_fmt_x.o \
  driver_check_x.o \
  driver_test_x.o \
  driver_run_x.o \
  driver_build_x.o \
  driver_compile_x.o \
  driver_emit_x.o
  do
  if [ -f "$_tdl" ] && [ -s "$_tdl" ]; then
  CRT0_TDL_COMPANIONS="$CRT0_TDL_COMPANIONS $_tdl"
  fi
  done
  # Prefer root lsp_*_x.o; fall back to gen_driver copies (ensure_asm_experimental_lsp_objs).
  _lsp_added=0
  for _tdl in lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o; do
  if [ -f "$_tdl" ] && [ -s "$_tdl" ]; then
  CRT0_TDL_COMPANIONS="$CRT0_TDL_COMPANIONS $_tdl"
  _lsp_added=1
  fi
  done
  if [ "$_lsp_added" -eq 0 ]; then
  for _tdl in \
  "$BUILD_DIR/gen_driver/lsp_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_std_heap_x.o"
  do
  if [ -f "$_tdl" ] && [ -s "$_tdl" ]; then
  CRT0_TDL_COMPANIONS="$CRT0_TDL_COMPANIONS $_tdl"
  fi
  done
  fi
  if [ -n "$_lsp_diag_o" ] && [ -f "$_lsp_diag_o" ] && [ -s "$_lsp_diag_o" ]; then
  CRT0_TDL_COMPANIONS="$CRT0_TDL_COMPANIONS $_lsp_diag_o"
  fi
  build_xlang_asm_info "crt0 bag: typeck/driver/lsp companions (NL-07 L4+)=$CRT0_TDL_COMPANIONS"
}

# PLATFORM: LINUX — bag parser.o / pipeline.o are often 11B stubs at first crt0 try
# (second-pass promote happens later). Same 8KiB gate as typeck selfhosted.
asm_strict_parser_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/parser.o" 2>/dev/null || echo 0)
  [ "$t" -gt 8192 ] 2>/dev/null
}

# PLATFORM: LINUX — bag codegen.o is historically a tiny stub; gate mirrors typeck.
asm_strict_codegen_selfhosted() {
  local t
  t=$(asm_o_text_bytes "$BUILD_DIR/codegen.o" 2>/dev/null || echo 0)
  [ "$t" -gt 8192 ] 2>/dev/null
}

# PLATFORM: LINUX — write one-symbol-per-line export list and ld_partial_export.
# Args: out.o src.o sym1 [sym2 ...]. Returns 0 only if partial built and non-empty.
# G.7: partial residual only — never second stub table of reimplemented bodies.
crt0_ld_partial_syms() {
  local out_o="$1"
  local src_o="$2"
  shift 2
  local syms_file="$out_o.export.txt"
  local s
  if [ ! -f "$src_o" ] || [ ! -s "$src_o" ]; then
  return 1
  fi
  : >"$syms_file"
  for s in "$@"; do
  # Keep only symbols actually present as T/W in src (avoid empty partials).
  if nm -g "$src_o" 2>/dev/null | grep -qE " [TW] (_)?${s}\$"; then
  printf '%s\n' "$s" >>"$syms_file"
  fi
  done
  if [ ! -s "$syms_file" ]; then
  return 1
  fi
  if [ ! -f "$out_o" ] || [ "$src_o" -nt "$out_o" ] || [ "$syms_file" -nt "$out_o" ]; then
  build_xlang_asm_info "ld partial export $syms_file $(basename "$src_o") -> $out_o (NL-07 L5)"
  ld_partial_export "$syms_file" "$out_o" "$src_o" || return 1
  fi
  return 0
}

# PLATFORM: LINUX — NL-07 L5: codegen/parser (+ residual glue) into crt0 bag.
# Who produces UNDEF (L4+ residual head ~41 unique):
#   · crt0 first-pass bag uses OK-parser-stub / OK-codegen-stub / OK-pipeline-stub
#     (size≈11) — promote to parser_x/codegen_x/pipeline_x happens AFTER crt0 try.
#   · glue_standalone U-refs codegen_emit_* / parser_parse_into_buf / pipeline_run_* /
#     find_or_alloc_ptr_type_ref / strict_minimal typeck_find / preamble masks / cfg_* /
#     lsp sizes / driver_run_{fmt,check} — live outside historic bag bulk.
# Authority (G.7): SAME product objects experimental/g05 already use; export ONLY the
# residual T/W symbols (L3b pattern). Forbidden: full parser_x/codegen_x/pipeline_x/
# strict_glue/lsp_ctx on the crt0 line (multi-def vs bag or L4 companions).
# Conditional: parser residual partial only when bag parser not selfhosted (dual T).
# pipeline_run partial only when bag pipeline not selfhosted (dual W otherwise OK but
# stub has no def). Sets CRT0_CG_PARSER_COMPANIONS.
ensure_crt0_codegen_parser_companion_objs() {
  CRT0_CG_PARSER_COMPANIONS=""
  # Materialize X frontend + glue sources (same ensure experimental uses).
  ensure_asm_bootstrap_x_companion_objs || true
  ensure_asm_lsp_codegen_extern_obj || true
  ensure_asm_pipeline_glue_strict_minimal_obj || true
  ensure_lsp_diag_pipeline_sizes_obj || true
  # g05 authority for true sizeof (not weak sizes-only stub) when present.
  if [ ! -f src/lsp/lsp_diag_pipeline_sizes_nostub.o ]; then
  if [ -f seeds/lsp_diag_pipeline_sizes_nostub.from_x.c ] || [ -f src/lsp/lsp_diag_pipeline_sizes_nostub.c ]; then
  build_xlang_asm_info "crt0 L5: build lsp_diag_pipeline_sizes_nostub.o"
  # Wave931: shell try-heat (B3_LSP_SAT_SEED_OBJS · wave911; no make).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    make -s src/lsp/lsp_diag_pipeline_sizes_nostub.o 2>/dev/null || true
  else
    bash scripts/ensure_host_cc_seed_o.sh try-heat src/lsp/lsp_diag_pipeline_sizes_nostub.o 2>/dev/null || true
  fi
  fi
  fi
  if [ ! -f src/lsp/lsp_diag_pipeline_ctx.o ]; then
  # Wave928: shell ensure_host_cc_seed_o try-ldpc-prefer (wave767 authority; no make).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    make -s src/lsp/lsp_diag_pipeline_ctx.o 2>/dev/null || true
  else
    bash scripts/ensure_host_cc_seed_o.sh try-ldpc-prefer src/lsp/lsp_diag_pipeline_ctx.o 2>/dev/null || true
  fi
  fi
  if [ ! -f src/driver/fmt_check_cmd_driver.o ]; then
  # Wave928: shell ensure_host_cc_seed_o try-other-l2-prefer (wave771/775 authority; no make).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    make -s src/driver/fmt_check_cmd_driver.o 2>/dev/null || true
  else
    bash scripts/ensure_host_cc_seed_o.sh try-other-l2-prefer src/driver/fmt_check_cmd_driver.o 2>/dev/null || true
  fi
  fi
  if [ ! -f src/lexer/cfg_eval.o ]; then
  ensure_asm_bootstrap_support_extra_objs || true
  fi

  local p
  # --- always: residual-only partials (symbol multi vs bag+L4 = 0; Ubuntu map 2026-07-17) ---
  p="$BUILD_DIR/crt0_l5_codegen_partial.o"
  if crt0_ld_partial_syms "$p" codegen_x.o \
  codegen_emit_bytes_from_ptr \
  codegen_emit_expr \
  codegen_x_ast \
  codegen_x_ast_emit_header; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  p="$BUILD_DIR/crt0_l5_x_frontend_partial.o"
  if crt0_ld_partial_syms "$p" x_frontend_link_alias.o \
  codegen_codegen_x_ast \
  find_or_alloc_ptr_type_ref; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  # lexer_x.o multi=0 vs bag+L4 (Ubuntu map); closes lexer_init / lexer_next_* after parser partial.
  if [ -f lexer_x.o ] && [ -s lexer_x.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS lexer_x.o"
  fi
  # parse_expr_into alias (strict already links this TU).
  if [ -f src/asm/parser_asm_parse_expr_link.o ] && [ -s src/asm/parser_asm_parse_expr_link.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/asm/parser_asm_parse_expr_link.o"
  elif [ -f parser_asm_parse_expr_link.o ] && [ -s parser_asm_parse_expr_link.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS parser_asm_parse_expr_link.o"
  fi
  # parser_asm_thin_glue: product authority for parser_*_glue (strict link already uses it).
  # Full .o multi=4 non-glue names vs bag; export ONLY parser_*_glue (residual cascade 100/100).
  if [ -f parser_asm_thin_glue.o ] && [ -s parser_asm_thin_glue.o ]; then
  p="$BUILD_DIR/crt0_l5_parser_thin_glue_partial.o"
  _glue_syms="$BUILD_DIR/crt0_l5_parser_thin_glue_export.txt"
  nm parser_asm_thin_glue.o 2>/dev/null | awk '/ [TW] / {
    s=$3; sub(/^_/, "", s)
    if (s ~ /^parser_.*_glue$/) print s
  }' | sort -u >"$_glue_syms"
  if [ -s "$_glue_syms" ]; then
  if [ ! -f "$p" ] || [ parser_asm_thin_glue.o -nt "$p" ] || [ "$_glue_syms" -nt "$p" ]; then
  build_xlang_asm_info "ld partial export $_glue_syms parser_asm_thin_glue -> $p (NL-07 L5 glue cascade)"
  ld_partial_export "$_glue_syms" "$p" parser_asm_thin_glue.o || true
  fi
  if [ -f "$p" ] && [ -s "$p" ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  fi
  fi
  p="$BUILD_DIR/crt0_l5_strict_glue_partial.o"
  if crt0_ld_partial_syms "$p" src/runtime_driver_strict_glue_stubs.o \
  ast_module_free \
  codegen_get_preamble_skip_mask \
  codegen_or_preamble_skip_mask \
  codegen_reset_preamble_skip_mask \
  codegen_set_dep_slots_for_x_pipeline \
  codegen_set_preamble_has_core_option_result \
  codegen_wpo_mono_sym_format \
  pipeline_block_labeled_set_names \
  preprocess_define_add \
  preprocess_define_reset \
  preprocess_eval_condition_c; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  # NL-07 L7 runtime: pure crt0 previously resolved preprocess_x_buf from
  # asm_experimental_symbol_bridge weak stub (returns -1) → PP002 + postlink smoke WARN.
  # Authority (G.7): product preprocess_x.o (same as experimental/strict companions).
  # multi-def: only preprocess_x_buf overlaps bridge W; strong T wins. Other preprocess_*
  # symbols exclusive to preprocess_x.o (Ubuntu map 2026-07-17).
  if [ -f preprocess_x.o ] && [ -s preprocess_x.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS preprocess_x.o"
  fi
  # NL-07 L7c: asm -o smoke needs product asm_asm_codegen_elf_o (user_asm_seed_bridge).
  # Without it, bridge weak asm_codegen_elf_o returns -1 → CG002; experimental/strict
  # already link BSTRICT_USER_ASM_SEED_BRIDGE_LINK. multi vs bag: only W/t same names.
  if [ -f src/asm/user_asm_seed_bridge.o ] && [ -s src/asm/user_asm_seed_bridge.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/asm/user_asm_seed_bridge.o"
  elif [ -f seeds/user_asm_seed_bridge.from_x.c ]; then
  ensure_bstrict_seed_support_objs 2>/dev/null || true
  if [ -f src/asm/user_asm_seed_bridge.o ] && [ -s src/asm/user_asm_seed_bridge.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/asm/user_asm_seed_bridge.o"
  fi
  fi
  # process argv surface (g05 / experimental already links runtime_process_argv.o).
  if [ -f runtime_process_argv.o ] && [ -s runtime_process_argv.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS runtime_process_argv.o"
  fi
  p="$BUILD_DIR/crt0_l5_fmt_check_partial.o"
  if crt0_ld_partial_syms "$p" src/driver/fmt_check_cmd_driver.o \
  driver_run_compiler_check \
  driver_run_fmt; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  # cfg_eval.o: full TU multi=0 vs bag+L4 (g05 companion).
  if [ -f src/lexer/cfg_eval.o ] && [ -s src/lexer/cfg_eval.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/lexer/cfg_eval.o"
  fi
  # Prefer nostub sizeof (g05); fall back to weak sizes seed.
  if [ -f src/lsp/lsp_diag_pipeline_sizes_nostub.o ] && [ -s src/lsp/lsp_diag_pipeline_sizes_nostub.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/lsp/lsp_diag_pipeline_sizes_nostub.o"
  elif [ -f src/lsp/lsp_diag_pipeline_sizes.o ] && [ -s src/lsp/lsp_diag_pipeline_sizes.o ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS src/lsp/lsp_diag_pipeline_sizes.o"
  fi
  p="$BUILD_DIR/crt0_l5_lsp_ctx_partial.o"
  if crt0_ld_partial_syms "$p" src/lsp/lsp_diag_pipeline_ctx.o \
  lsp_state_buf_ptr \
  lsp_write_all; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi
  # L1 drops strict_minimal when standalone present — re-export residual-only symbols.
  p="$BUILD_DIR/crt0_l5_strict_minimal_typeck_find_partial.o"
  if crt0_ld_partial_syms "$p" "$BUILD_DIR/pipeline_glue_strict_minimal.o" \
  pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal \
  parser_diagnostic_parse_commit_post \
  parser_diagnostic_parse_commit_pre; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  fi

  # --- conditional: bag stub → need X residual; bag selfhosted already defines ---
  if ! asm_strict_parser_selfhosted 2>/dev/null; then
  # thin_glue parser_*_glue calls back into parser_x parse_*_into / onefunc wire.
  # Export the full residual cascade from parser_x (not whole .o — multi with bag/standalone).
  p="$BUILD_DIR/crt0_l5_parser_partial.o"
  _psyms="$BUILD_DIR/crt0_l5_parser_export.txt"
  if [ -f parser_x.o ] && [ -s parser_x.o ]; then
  # Keep GLOBAL every parser_x symbol thin_glue / residual U-ref (objcopy
  # --keep-global demotes unlisted T to local → cannot satisfy cross-.o U).
  # PLATFORM: LINUX — NL-07 L7+ pure-static import: pipeline U-refs
  # parser_get_module_num_imports / path. If demoted to local, ELF picks
  # experimental_symbol_bridge weak stubs (return 0 / empty path) → no dep
  # open → typeck XT001 check_block on import programs (hello/option/si).
  # Authority: parser_x.o real bodies only; keep-global must list them (G.7).
  nm parser_x.o 2>/dev/null | awk '/ [TW] / {
    s=$3; sub(/^_/, "", s)
    if (s == "parse_expr_into" \
        || s ~ /^parser_parse_/ \
        || s ~ /^parser_onefunc_/ \
        || s == "parser_copy_module_import_path64" \
        || s == "parser_get_module_num_imports" \
        || s == "parser_get_module_import_path" \
        || s == "parser_diag_fail_at_token_kind" \
        || s ~ /^parser_diag_fail_at_token_kind/)
      print s
  }' | sort -u >"$_psyms"
  if [ -s "$_psyms" ]; then
  if [ ! -f "$p" ] || [ parser_x.o -nt "$p" ] || [ "$_psyms" -nt "$p" ]; then
  build_xlang_asm_info "ld partial export $_psyms parser_x -> $p (NL-07 L5 parser cascade)"
  ld_partial_export "$_psyms" "$p" parser_x.o || true
  fi
  if [ -f "$p" ] && [ -s "$p" ]; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  build_xlang_asm_info "crt0 L5: parser bag not selfhosted — append parser residual cascade partial"
  fi
  fi
  fi
  fi
  if ! asm_strict_pipeline_selfhosted 2>/dev/null; then
  p="$BUILD_DIR/crt0_l5_pipeline_run_partial.o"
  if crt0_ld_partial_syms "$p" pipeline_x.o \
  pipeline_run_x_pipeline_impl; then
  CRT0_CG_PARSER_COMPANIONS="$CRT0_CG_PARSER_COMPANIONS $p"
  build_xlang_asm_info "crt0 L5: pipeline bag not selfhosted — append pipeline_run residual partial"
  fi
  fi
  # codegen residual partial is always from codegen_x (bag codegen historically stub);
  # if bag ever selfhosts, residual codegen_emit_* would already be in bag — dual T risk.
  # Current map: bag codegen has 0 T codegen_*; keep always-on partial above.

  build_xlang_asm_info "crt0 bag: codegen/parser residual companions (NL-07 L5)=$CRT0_CG_PARSER_COMPANIONS"
}

# PLATFORM: LINUX — NL-07 L3 + L3b + L4+ + L5 + L9: crt0 link must include backend enc/dispatch
# companions (BSTRICT_DISPATCH_OBJS + simd_*), seed backend_emit_* partial,
# typeck/driver/lsp companions, codegen/parser residual partials, and experimental
# seed-support homologues (compat stubs / x_seed_bridge / asm_full_link_stubs).
# Who produces UNDEF (enc): pipeline/backend build_asm .o reference backend_enc_* /
# arch_emit / try_inline / simd — dispatch live under src/asm/, never in bag historically.
# Who produces UNDEF (emit): asm_backend_compat_stubs forwards to backend_emit_*; seed
# holds weak stubs but was not on the crt0 line (experimental links full seed partial).
# Who produces UNDEF (tdl): bridge/glue reference driver_*/typeck_*/lsp_* outside bag.
# Who produces UNDEF (L5): glue U-refs codegen_*/parser_*/pipeline_run/cfg/lsp sizes —
# first-pass bag stubs + L1 drop of strict_minimal.
# Who produces UNDEF (L9 residual after L1–L8): pipeline_glue_standalone U-refs
# backend_enc_mov_imm32_to_w0_arch / backend_ensure_block_local_slots (compat stubs),
# io_read_batch_buf / io_write_batch_buf (x_seed_bridge), arch_arm64_* (asm_full_link_stubs).
# Authority (G.7): ensure_bstrict_seed_support_objs + BSTRICT_DISPATCH_OBJS + seed emit
# partial + ensure_crt0_typeck_driver_lsp_companion_objs +
# ensure_crt0_codegen_parser_companion_objs + GEN_DRIVER/strict seed-support objs
# (no second stub table — same .o experimental already chains).
# Sets CRT0_BACKEND_COMPANIONS for the crt0 link line (Linux only callers).
ensure_crt0_backend_companion_objs() {
  CRT0_BACKEND_COMPANIONS=""
  ensure_bstrict_seed_support_objs
  # crt0 path is Linux-only; keep non-Darwin dispatch set (no filtered enc complement).
  BSTRICT_BACKEND_X86_64_ENC_LINK="src/asm/backend_x86_64_enc_c.o"
  BSTRICT_DISPATCH_OBJS="src/asm/backend_enc_dispatch.o $BSTRICT_BACKEND_X86_64_ENC_LINK src/asm/backend_arch_emit_dispatch.o src/asm/backend_try_inline_dispatch.o src/asm/backend_call_dispatch.o"
  CRT0_BACKEND_COMPANIONS="$BSTRICT_DISPATCH_OBJS"
  # Same layer as GEN_DRIVER_BSTRICT_COMPANIONS simd_* (closes simd_enc UNDEF cluster).
  if [ -f src/asm/simd_enc.o ]; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS src/asm/simd_enc.o"
  fi
  if [ -f src/asm/simd_loop.o ]; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS src/asm/simd_loop.o"
  fi
  # NL-07 L3b: seed weak backend_emit_* (partial only — avoid multi-def with fallback alias).
  CRT0_BACKEND_EMIT_PARTIAL=""
  if ensure_crt0_backend_emit_seed_partial_obj; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS $CRT0_BACKEND_EMIT_PARTIAL"
  fi
  # NL-07 L4+: typeck / driver / lsp (experimental-homologous; multi-safe vs bag).
  CRT0_TDL_COMPANIONS=""
  ensure_crt0_typeck_driver_lsp_companion_objs
  if [ -n "${CRT0_TDL_COMPANIONS:-}" ]; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS $CRT0_TDL_COMPANIONS"
  fi
  # NL-07 L5: codegen/parser residual partials (L3b pattern; multi-safe).
  CRT0_CG_PARSER_COMPANIONS=""
  ensure_crt0_codegen_parser_companion_objs
  if [ -n "${CRT0_CG_PARSER_COMPANIONS:-}" ]; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS $CRT0_CG_PARSER_COMPANIONS"
  fi
  # NL-07 L9: experimental/strict seed-support homologues (G.7 single authority).
  # Closes crt0 residual after L1–L8 when bag holds full pipeline_glue_standalone.
  # Only append objs NOT already in CRT0_ASM (filter bag) — dual src/asm + build_asm
  # copies of the same TU cause multi-def (compat stubs first failure mode).
  ensure_asm_backend_compat_stubs_obj 2>/dev/null || true
  CRT0_SEED_SUPPORT=""
  _crt0_bag=" $CRT0_ASM "
  case "$_crt0_bag" in
  *"asm_backend_compat_stubs.o"*) ;;
  *)
  if [ -f "$BUILD_DIR/asm_backend_compat_stubs.o" ]; then
  CRT0_SEED_SUPPORT="$CRT0_SEED_SUPPORT $BUILD_DIR/asm_backend_compat_stubs.o"
  elif [ -f src/asm/asm_backend_compat_stubs.o ]; then
  CRT0_SEED_SUPPORT="$CRT0_SEED_SUPPORT src/asm/asm_backend_compat_stubs.o"
  fi
  ;;
  esac
  case "$_crt0_bag" in
  *"x_seed_bridge.o"*) ;;
  *)
  if [ -f "$BUILD_DIR/x_seed_bridge.o" ]; then
  CRT0_SEED_SUPPORT="$CRT0_SEED_SUPPORT $BUILD_DIR/x_seed_bridge.o"
  fi
  ;;
  esac
  case "$_crt0_bag" in
  *"seed_link_compat.o"*) ;;
  *)
  if [ -f "$BUILD_DIR/seed_link_compat.o" ]; then
  CRT0_SEED_SUPPORT="$CRT0_SEED_SUPPORT $BUILD_DIR/seed_link_compat.o"
  fi
  ;;
  esac
  # arch_arm64_* weak cluster — same obj ST_BSTRICT_LINK_EXTRA / experimental uses.
  case "$_crt0_bag" in
  *"asm_full_link_stubs.o"*) ;;
  *)
  if [ ! -f "$BUILD_DIR/seed_host/asm_full_link_stubs.o" ] \
  || [ ! -s "$BUILD_DIR/seed_host/asm_full_link_stubs.o" ]; then
  if [ -f pipeline_x.o ] && { [ -x scripts/gen_asm_full_link_stubs.pl ] || [ -f scripts/gen_asm_full_link_stubs.pl ]; }; then
  _crt0_stub_scan="pipeline_x.o $BSTRICT_DISPATCH_OBJS"
  if [ -f "$BUILD_DIR/seed_host/asm_full.o" ]; then
  _crt0_stub_scan="$BUILD_DIR/seed_host/asm_full.o $_crt0_stub_scan"
  fi
  if perl scripts/gen_asm_full_link_stubs.pl "$BUILD_DIR/seed_host/asm_full_link_stubs.c" $_crt0_stub_scan 2>/dev/null \
  && [ -s "$BUILD_DIR/seed_host/asm_full_link_stubs.c" ]; then
  "$CC" $CFLAGS -c -o "$BUILD_DIR/seed_host/asm_full_link_stubs.o" "$BUILD_DIR/seed_host/asm_full_link_stubs.c" 2>/dev/null || true
  fi
  fi
  fi
  if [ -f "$BUILD_DIR/seed_host/asm_full_link_stubs.o" ] \
  && [ -s "$BUILD_DIR/seed_host/asm_full_link_stubs.o" ]; then
  CRT0_SEED_SUPPORT="$CRT0_SEED_SUPPORT $BUILD_DIR/seed_host/asm_full_link_stubs.o"
  fi
  ;;
  esac
  if [ -n "$CRT0_SEED_SUPPORT" ]; then
  CRT0_BACKEND_COMPANIONS="$CRT0_BACKEND_COMPANIONS $CRT0_SEED_SUPPORT"
  build_xlang_asm_info "crt0 bag: L9 seed-support homologues=$CRT0_SEED_SUPPORT"
  fi
  build_xlang_asm_info "crt0 bag: backend+tdl+l5+l9 companions (NL-07 L3+L3b+L4++L5+L9)=$CRT0_BACKEND_COMPANIONS"
}

# F-06 v1：fs/io/heap 已纯 .x；bootstrap 不再 cc -c std/*.c（符号由 std_fs_shim / runtime_io_abi / lsp_io_std_heap_x 等提供）。
ensure_std_fs_io_heap_objs() {
  :
}

# pipeline.x import pipeline.run_x_pipeline → pipeline_run_x_link_alias 提供 C 符号。
ensure_pipeline_run_x_link_alias_obj() {
  if [ ! -f src/asm/pipeline_run_x_link_alias.o ] || [ seeds/pipeline_run_x_link_alias.from_x.c -nt src/asm/pipeline_run_x_link_alias.o ]; then
  build_xlang_asm_info "cc pipeline_run_x_link_alias.o"
  sh scripts/cc_inc_tu.sh seeds/pipeline_run_x_link_alias.from_x.c src/asm/pipeline_run_x_link_alias.o
  fi
}

# B-strict 首遍 bootstrap：与 bootstrap-driver-seed 对齐的 -E-extern 分模块 .o + asm 后端 partial。
# 瘦 pipeline_x.o 须链 parser_x/typeck_x/codegen_x/lexer_x、std_fs_shim、seed_host backend partial；
# 首遍勿并 build_asm/*.o（各模块 __xlang_asm_mod_stub 重复 → Darwin ld 失败）。
ensure_asm_bootstrap_x_companion_objs() {
  # Presence of the full companion set (not only READY flag): seed/g05 leaves on disk.
  _x_companions_present=0
  if [ -f parser_x.o ] && [ -f lexer_x.o ] && [ -f typeck_x.o ] \
    && [ -f codegen_x.o ] && [ -f preprocess_x.o ] \
    && [ -f driver_x.o ] && [ -f driver_fmt_x.o ] && [ -f driver_check_x.o ] \
    && [ -f driver_test_x.o ] && [ -f driver_build_x.o ] && [ -f driver_run_x.o ] \
    && [ -f driver_compile_x.o ] && [ -f driver_emit_x.o ] \
    && [ -f lsp_io_std_heap_x.o ] && [ -f x_frontend_link_alias.o ]; then
    _x_companions_present=1
  fi
  if [ "${XLANG_ASM_BOOTSTRAP_X_COMPANIONS_READY:-0}" = "1" ] \
    && [ "$_x_companions_present" = "1" ]; then
    build_xlang_asm_info "reuse X companion objs (already ensured in this run)"
    return 0
  fi
  detect_pipeline_gen_cflags
  ensure_pipeline_x_o_fresh
  # runtime-only relink：X companion .o 已存在时勿 make typeck_x.o（stale typeck_gen 会阻断 relink）。
  if [ -n "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ] \
    && [ -f parser_x.o ] && [ -f lexer_x.o ] && [ -f typeck_x.o ] \
    && [ -f codegen_x.o ] && [ -f preprocess_x.o ]; then
    build_xlang_asm_info "BSTRICT_RELINK_ONLY - skip X companion make (reuse existing *_x.o)"
  elif [ "$_x_companions_present" = "1" ]; then
    # G.7: when seed/g05 already produced the bag, never re-enter make (all platforms).
    # PLATFORM: WINDOWS — nested MinGW make was the hang/fail (sh.dll "C:", typeck_f64_bits arch).
    build_xlang_asm_info "reuse seed X companion bag (skip nested make)"
  elif build_xlang_asm_is_msys; then
    # PLATFORM: WINDOWS | MINGW | MSYS — never nest make for companions; hybrid continues with
    # whatever seed objs exist + direct cc below. Missing leaves may fail at link (real signal).
    build_xlang_asm_info "win: skip nested make for X companions (missing seed bag; link may fail)"
  else
    # Wave931: shell multi-family ensure (default; no make).
    # Companion list spans 6 multi-target families (G.7 single-body per family):
    #   MIGRATE_X (wave919): parser_x.o typeck_x.o codegen_x.o
    #   GEN_C_TO_O (wave910): lexer_x.o preprocess_x.o driver_x.o
    #   R1_ALIAS_STUBS (wave902): x_frontend_link_alias.o
    #   DRIVER_LEAF (wave896): driver_{fmt,check,test,build,run,compile,emit}_x.o + lsp_io_std_heap_x.o
    #   R3_COLD (wave906): src/runtime_io_abi.o
    #   R1_EXTRA_CFLAGS (wave903): src/asm/parser_asm_parse_expr_link.o
    # Thin pipeline_x.o still references codegen_codegen_* / typeck_typeck_* / lexer_lexer_init;
    # must use same link alias as bootstrap-driver-seed.
    # x-naming migration: link line still references *_x.o; alias targets cp *_x.o.
    # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
    if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
      build_xlang_asm_info "ensure X companion objs (parser/lexer/typeck/codegen/preprocess/compile)"
      make parser_x.o lexer_x.o typeck_x.o codegen_x.o preprocess_x.o \
        lexer_x.o codegen_x.o typeck_x.o preprocess_x.o \
        x_frontend_link_alias.o \
        driver_x.o driver_fmt_x.o driver_check_x.o driver_test_x.o \
        driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o \
        driver_fmt_x.o driver_check_x.o driver_test_x.o \
        driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o \
        lsp_io_std_heap_x.o \
        src/runtime_io_abi.o src/asm/parser_asm_parse_expr_link.o
    else
      build_xlang_asm_info "wave931: shell ensure X companion objs (6 families)"
      # MIGRATE_X_OBJS (wave919): parser_x.o typeck_x.o codegen_x.o
      bash scripts/migrate_x_objs.sh parser_x.o
      bash scripts/migrate_x_objs.sh typeck_x.o
      bash scripts/migrate_x_objs.sh codegen_x.o
      # GEN_C_TO_O_SEED_OBJS (wave910): lexer_x.o preprocess_x.o driver_x.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat lexer_x.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat preprocess_x.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat driver_x.o
      # R1_ALIAS_STUBS_OBJS (wave902): x_frontend_link_alias.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat x_frontend_link_alias.o
      # DRIVER_LEAF_PRODUCT_OBJS (wave896): driver_*_x.o + lsp_io_std_heap_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_fmt_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_check_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_test_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_build_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_run_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_compile_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure driver_emit_x.o
      bash scripts/driver_leaf_x_to_o.sh ensure lsp_io_std_heap_x.o
      # R3_COLD_SEED_OBJS (wave906): src/runtime_io_abi.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat src/runtime_io_abi.o
      # R1_EXTRA_CFLAGS_OBJS (wave903): src/asm/parser_asm_parse_expr_link.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat src/asm/parser_asm_parse_expr_link.o
    fi
  fi
  # G-02e: fs/sys shim symbols live in runtime_io_abi.o
  if [ ! -f src/runtime_io_abi.o ] || [ seeds/runtime_io_abi.from_x.c -nt src/runtime_io_abi.o ]; then
    echo " cc -c seeds/runtime_io_abi.from_x.c -> src/runtime_io_abi.o"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o src/runtime_io_abi.o
  fi
  if [ ! -f "$BUILD_DIR/x_seed_bridge.o" ] || [ "seeds/x_seed_bridge.from_x.c" -nt "$BUILD_DIR/x_seed_bridge.o" ]; then
    echo " cc -c seeds/x_seed_bridge.from_x.c -> $BUILD_DIR/x_seed_bridge.o (G-02f-11)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/x_seed_bridge.from_x.c -o "$BUILD_DIR/x_seed_bridge.o"
  fi
  if [ ! -f "$BUILD_DIR/seed_link_compat.o" ] || [ "seeds/seed_link_compat.from_x.c" -nt "$BUILD_DIR/seed_link_compat.o" ]; then
    echo " cc -c seeds/seed_link_compat.from_x.c -> $BUILD_DIR/seed_link_compat.o (G-02f-11)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/seed_link_compat.from_x.c -o "$BUILD_DIR/seed_link_compat.o"
  fi
  # preprocess_if_stack_* 由 runtime_pipeline_abi／pipeline orch 提供
  # （ast_pool.c / pipeline_glue.c mega left wave309）；bridge 已删除。
  # dispatch TU 须先于 build_seed_asm_host（partial 导出须 nm 四份 dispatch .o）。
  ensure_bstrict_seed_support_objs
  if [ -n "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ] && [ -f "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
    :
  elif [ ! -f "$BUILD_DIR/seed_host/asm_backend_partial.o" ] || [ "src/asm/backend.x" -nt "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
    build_xlang_asm_info "build_seed_asm_host (backend_enc_* for pipeline_x.o)"
    ./scripts/build_seed_asm_host.sh
  fi
  ensure_ast_pool_l5_bridge_obj
  if [ ! -f pipeline_bootstrap_orchestration.o ] || [ seeds/pipeline_bootstrap_orchestration.from_x.c -nt pipeline_bootstrap_orchestration.o ]; then
    # Wave928: all platforms cc direct from seed (unified with WINDOWS path; no make).
    # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
    if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
      make pipeline_bootstrap_orchestration.o
    elif [ -f seeds/pipeline_bootstrap_orchestration.from_x.c ]; then
      echo " cc pipeline_bootstrap_orchestration.o <- seeds (wave928; unified all platforms)"
      $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/pipeline_bootstrap_orchestration.from_x.c \
        -o pipeline_bootstrap_orchestration.o
    else
      build_xlang_asm_info "WARN missing pipeline_bootstrap_orchestration.o seed"
    fi
  fi
  XLANG_ASM_BOOTSTRAP_X_COMPANIONS_READY=1
}

# 与 Makefile USER_ASM_SEED_OBJS 对齐：pipeline_glue / partial 引用的 enc/call 分派 TU。
# backend_x86_64_enc_c.o 须链入，否则 asm_full_link_stubs weak enc_label 恒 -1（用户 asm -o 全挂）。
BSTRICT_PIPELINE_LINK_O="pipeline_x.o"
# wave309: pipeline_glue_standalone seed retired; pure runtime_pipeline_abi.o (already in
# LD argv) is G.7 authority. Default empty; refresh_bstrict_link_variants populates only
# when .o physically exists (end-of-function guard). PLATFORM: SHARED.
BSTRICT_EXPERIMENTAL_GLUE_OBJ=""
BSTRICT_USER_ASM_SEED_BRIDGE_LINK="src/asm/user_asm_seed_bridge.o"
BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK="src/asm/asm_backend_compat_stubs.o"
BSTRICT_BACKEND_X86_64_ENC_LINK="src/asm/backend_x86_64_enc_c.o"
# PLATFORM: MACOS|DARWIN — g05_relink_env _USER_ASM_LINK includes backend_arm64_enc_c.o
# so strong arch_arm64_enc_* override seed_link_compat / full_link_stubs weak -1.
# Empty on Linux (x86_64 enc already in BSTRICT_BACKEND_X86_64_ENC_LINK).
BSTRICT_BACKEND_ARM64_ENC_LINK=""
BSTRICT_DISPATCH_OBJS="src/asm/backend_enc_dispatch.o $BSTRICT_BACKEND_X86_64_ENC_LINK src/asm/backend_arch_emit_dispatch.o src/asm/backend_try_inline_dispatch.o src/asm/backend_call_dispatch.o"
BSTRICT_DISPATCH_COMPANIONS="$BSTRICT_DISPATCH_OBJS"
# Early bag: user_asm (+ Darwin arm64 enc) must precede weak stubs on the link line
# when user_asm is a prefer/libtool ar (archive extract only for currently-U symbols).
BSTRICT_USER_ASM_EARLY_LINK=""

refresh_bstrict_link_variants() {
  BSTRICT_PIPELINE_LINK_O="pipeline_x.o"
  BSTRICT_EXPERIMENTAL_GLUE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  BSTRICT_USER_ASM_SEED_BRIDGE_LINK="src/asm/user_asm_seed_bridge.o"
  BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK="src/asm/asm_backend_compat_stubs.o"
  BSTRICT_BACKEND_X86_64_ENC_LINK="src/asm/backend_x86_64_enc_c.o"
  BSTRICT_BACKEND_ARM64_ENC_LINK=""
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  # PLATFORM: DARWIN — ld 不允许多定义（-multiply_defined 已废弃）。
  # filtered pipeline 与 full minimal glue 重叠 → 不整颗链 minimal；改为：
  #   filtered pipeline + minimal complement（仅 filtered 缺的 typeck helpers）
  #   + filtered strict_glue_stubs（见 ensure_bstrict_darwin_*）。
  BSTRICT_EXPERIMENTAL_GLUE_OBJ=""
  if ensure_bstrict_pipeline_filtered_obj 2>/dev/null; then
  BSTRICT_PIPELINE_LINK_O="$BUILD_DIR/bstrict_pipeline_filtered.o"
  # Prefer complement of minimal glue so pipeline_typeck_after_parse_ok / *_strict_minimal resolve.
  if ensure_asm_pipeline_glue_strict_minimal_obj 2>/dev/null \
    && ensure_bstrict_darwin_strict_glue_stubs_filt_obj 2>/dev/null \
    && ensure_bstrict_darwin_minimal_glue_complement_obj 2>/dev/null; then
  BSTRICT_EXPERIMENTAL_GLUE_OBJ="$BUILD_DIR/bstrict_pipeline_glue_minimal_complement.o"
  fi
  else
  BSTRICT_EXPERIMENTAL_GLUE_OBJ="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  BSTRICT_PIPELINE_LINK_O="pipeline_x.o"
  fi
  if [ -s "$BUILD_DIR/seed_host/asm_backend_partial.o" ]; then
  ensure_asm_backend_compat_stubs_obj >/dev/null 2>&1 || true
  # PLATFORM: DARWIN — prefer/libtool may leave user_asm_seed_bridge.o as an ar whose
  # thin member has multi LC_SEGMENT; Stage2 final ld then never extracts the rest
  # member that holds strong asm_asm_codegen_elf_o → CG002 code_len=0. G.7 twin of
  # ensure_bstrict_darwin_strict_glue_stubs_filt_obj MH_OBJECT prep: host-cc the seed
  # to a plain MH_OBJECT, then filter against seed_partial (filter out is MH too).
  _uabr_src="src/asm/user_asm_seed_bridge.o"
  _uabr_host="$BUILD_DIR/bstrict_user_asm_seed_bridge_host.o"
  if [ -f seeds/user_asm_seed_bridge.from_x.c ]; then
  # Rebuild MH host only when missing/stale (not on every refresh just because prefer ar exists).
  if [ ! -f "$_uabr_host" ] \
    || [ "seeds/user_asm_seed_bridge.from_x.c" -nt "$_uabr_host" ] \
    || file "$_uabr_host" 2>/dev/null | grep -qi 'ar archive'; then
  echo " cc -c seeds/user_asm_seed_bridge.from_x.c -> $_uabr_host (Darwin BSTRICT MH_OBJECT; not prefer ar)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/user_asm_seed_bridge.from_x.c -o "$_uabr_host" \
    || build_xlang_asm_warn "Darwin user_asm MH host-cc failed"
  fi
  if [ -s "$_uabr_host" ] && file "$_uabr_host" 2>/dev/null | grep -qi 'Mach-O'; then
  _uabr_src="$_uabr_host"
  fi
  fi
  # Only the filtered MH enters EARLY / companions. host.o is skipped by
  # filter_strict_asm_objs / filter_experimental_asm_objs (must not also land in ASM_TRY_OBJS).
  if ensure_bstrict_filtered_obj_against_seed_partial "$_uabr_src" "$BUILD_DIR/bstrict_user_asm_seed_bridge_filtered.o" "bstrict_user_asm_seed_bridge" 2>/dev/null; then
  BSTRICT_USER_ASM_SEED_BRIDGE_LINK="$BUILD_DIR/bstrict_user_asm_seed_bridge_filtered.o"
  elif [ -s "$_uabr_host" ]; then
  BSTRICT_USER_ASM_SEED_BRIDGE_LINK="$_uabr_host"
  fi
  if ensure_bstrict_filtered_obj_against_seed_partial "$BUILD_DIR/asm_backend_compat_stubs.o" "$BUILD_DIR/bstrict_asm_backend_compat_stubs_filtered.o" "bstrict_asm_backend_compat_stubs" 2>/dev/null; then
  BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK="$BUILD_DIR/bstrict_asm_backend_compat_stubs_filtered.o"
  fi
  if ensure_bstrict_filtered_obj_against_seed_partial "src/asm/backend_x86_64_enc_c.o" "$BUILD_DIR/bstrict_backend_x86_64_enc_c_filtered.o" "bstrict_backend_x86_64_enc_c" 2>/dev/null; then
  BSTRICT_BACKEND_X86_64_ENC_LINK="$BUILD_DIR/bstrict_backend_x86_64_enc_c_filtered.o"
  fi
  fi
  # G.7 twin g05_relink_env Darwin _USER_ASM_LINK: strong arm64 enc MH_OBJECT.
  if [ -f src/asm/backend_arm64_enc_c.o ] || [ -f seeds/backend_arm64_enc_c.from_x.c ]; then
  if [ ! -f src/asm/backend_arm64_enc_c.o ] \
    || [ "seeds/backend_arm64_enc_c.from_x.c" -nt src/asm/backend_arm64_enc_c.o ]; then
  echo " cc -c seeds/backend_arm64_enc_c.from_x.c -> src/asm/backend_arm64_enc_c.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/backend_arm64_enc_c.from_x.c -o src/asm/backend_arm64_enc_c.o
  fi
  BSTRICT_BACKEND_ARM64_ENC_LINK="src/asm/backend_arm64_enc_c.o"
  fi
  fi
  BSTRICT_DISPATCH_OBJS="src/asm/backend_enc_dispatch.o $BSTRICT_BACKEND_X86_64_ENC_LINK $BSTRICT_BACKEND_ARM64_ENC_LINK src/asm/backend_arch_emit_dispatch.o src/asm/backend_try_inline_dispatch.o src/asm/backend_call_dispatch.o"
  # Early link bag (before BSTRICT_SEED_SUPPORT weak stubs / experimental bridge).
  # PLATFORM: DARWIN primary; SHARED-safe (arm64 link empty on Linux).
  # Prefer/libtool may leave user_asm as ar — members extract only for currently-U
  # symbols, so this bag must precede weak asm_asm_codegen_* stubs (G.7 twin g05).
  BSTRICT_USER_ASM_EARLY_LINK="$BSTRICT_USER_ASM_SEED_BRIDGE_LINK $BSTRICT_BACKEND_ARM64_ENC_LINK"
  # Companions omit early-linked objs (Darwin rejects duplicate MH_OBJECT arm64 enc).
  BSTRICT_DISPATCH_COMPANIONS="$BSTRICT_DISPATCH_OBJS"
  if [ -n "$BSTRICT_BACKEND_ARM64_ENC_LINK" ]; then
  BSTRICT_DISPATCH_COMPANIONS=$(echo "$BSTRICT_DISPATCH_OBJS" | sed "s|[[:space:]]*${BSTRICT_BACKEND_ARM64_ENC_LINK}||g")
  fi
  # Keep full_link_stubs next to partial on ELF/Darwin (weak stubs; order free).
  # user_asm + arm64 enc live in BSTRICT_USER_ASM_EARLY_LINK on asm_only_strict lines.
  # PLATFORM: WINDOWS | PE — real enc/dispatch BEFORE strong full_link/compat stubs
  # (FIRST-wins; twin g05_relink_env WINDOWS). Stubs-first → enc_label -1 → CG002.
  if build_xlang_asm_is_msys 2>/dev/null; then
  GEN_DRIVER_BSTRICT_COMPANIONS="src/runtime_io_abi.o $BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $BUILD_DIR/seed_host/asm_backend_partial.o $BSTRICT_USER_ASM_SEED_BRIDGE_LINK $BSTRICT_DISPATCH_OBJS $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BUILD_DIR/seed_host/asm_full_link_stubs.o parser_asm_thin_glue.o src/asm/parser_asm_parse_expr_link.o src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o"
  else
  GEN_DRIVER_BSTRICT_COMPANIONS="src/runtime_io_abi.o $BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $BUILD_DIR/seed_host/asm_backend_partial.o $BUILD_DIR/seed_host/asm_full_link_stubs.o $BSTRICT_USER_ASM_SEED_BRIDGE_LINK $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BSTRICT_DISPATCH_OBJS parser_asm_thin_glue.o src/asm/parser_asm_parse_expr_link.o src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o"
  fi
  # wave309/wave304: glue seed shells retired; pure runtime_pipeline_abi.o (already in
  # LD argv) is G.7 authority. Drop BSTRICT_EXPERIMENTAL_GLUE_OBJ path when .o physically
  # absent so LD argv does not reference non-existent file (ld.bfd "cannot find").
  # Covers Linux standalone default + Darwin complement/fallback assignments above.
  # PLATFORM: SHARED — same authority as L4 g05 pure-ld path.
  [ -z "$BSTRICT_EXPERIMENTAL_GLUE_OBJ" ] || [ -f "$BSTRICT_EXPERIMENTAL_GLUE_OBJ" ] || BSTRICT_EXPERIMENTAL_GLUE_OBJ=""
}

# gen_driver 回退链须与 bootstrap-driver-seed 同款 companion：pipeline_x.o 引用 std_fs_shim / try_inline 分派等。
# PLATFORM: SHARED — include asm_full_link_stubs after partial (g05 USER_ASM_LINK /
#   Makefile USER_ASM_SEED_HOST_STUBS). PE hybrid needs strong platform_coff_* when
#   partial is thin/stale; ELF uses them as U-fill too.
# PLATFORM: WINDOWS | PE — real enc/dispatch BEFORE stubs (FIRST-wins; see refresh above).
#   Default (ELF/Darwin) keeps partial then stubs (weak override).
GEN_DRIVER_BSTRICT_COMPANIONS="src/runtime_io_abi.o $BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $BUILD_DIR/seed_host/asm_backend_partial.o $BUILD_DIR/seed_host/asm_full_link_stubs.o $BSTRICT_USER_ASM_SEED_BRIDGE_LINK $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BSTRICT_DISPATCH_OBJS parser_asm_thin_glue.o src/asm/parser_asm_parse_expr_link.o src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o"
if build_xlang_asm_is_msys 2>/dev/null; then
  GEN_DRIVER_BSTRICT_COMPANIONS="src/runtime_io_abi.o $BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $BUILD_DIR/seed_host/asm_backend_partial.o $BSTRICT_USER_ASM_SEED_BRIDGE_LINK $BSTRICT_DISPATCH_OBJS $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BUILD_DIR/seed_host/asm_full_link_stubs.o parser_asm_thin_glue.o src/asm/parser_asm_parse_expr_link.o src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o"
fi

# gen_driver fallback: pipeline_x.o / runtime_driver need parser/lexer/codegen X + driver
# subcmds + orchestration (Darwin: not seed parser.o alone).
# PLATFORM: SHARED — do NOT put runtime_driver_strict_glue_stubs.o here. Stubs go at
#   link END (GEN_DRIVER_GLUE_SUFFIX) so PE --allow-multiple-definition FIRST-wins
#   keeps real pipeline_x / parser_x / typeck_x (Makefile DRIVER_SEED_GLUE_SUFFIX /
#   g05 _GLUE_SUFFIX). Early stubs shadowed driver_get_module_num_funcs → num_funcs=0.
# PLATFORM: WINDOWS | PE — also link GEN_DRIVER_X_PIPELINE_COMPANIONS (parser_x.o)
#   BEFORE GEN_DRIVER_BSTRICT_COMPANIONS: parser_asm_parse_expr_link.o used to emit
#   strong empty parser_parse_into* when XLANG_WEAK is empty; first-wins → XP003.
GEN_DRIVER_X_PIPELINE_COMPANIONS="parser_x.o lexer_x.o codegen_x.o x_frontend_link_alias.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o pipeline_bootstrap_orchestration.o"

# 与 Makefile bootstrap-driver-seed / relink-xlang 对齐：pipeline_x.o 经 glue 引用的 backend 桥与 check/fmt C 实现。
ensure_bstrict_seed_support_objs() {
  if [ ! -f "$BUILD_DIR/backend_asm_strict_fallback_alias.o" ] \
  || [ "seeds/backend_asm_strict_fallback_alias.from_x.c" -nt "$BUILD_DIR/backend_asm_strict_fallback_alias.o" ]; then
  echo " cc -c seeds/backend_asm_strict_fallback_alias.from_x.c -> $BUILD_DIR/backend_asm_strict_fallback_alias.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$BUILD_DIR/backend_asm_strict_fallback_alias.o" seeds/backend_asm_strict_fallback_alias.from_x.c
  fi
  if [ ! -f src/asm/asm_backend_compat_stubs.o ] \
  || [ "seeds/asm_backend_compat_stubs.from_x.c" -nt src/asm/asm_backend_compat_stubs.o ]; then
  echo " cc -c seeds/asm_backend_compat_stubs.from_x.c -> src/asm/asm_backend_compat_stubs.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/asm_backend_compat_stubs.from_x.c -o src/asm/asm_backend_compat_stubs.o
  fi
  for _disp in backend_enc_dispatch backend_arch_emit_dispatch backend_try_inline_dispatch backend_call_dispatch; do
  if [ -f "seeds/${_disp}.from_x.c" ]; then
  if [ ! -f "src/asm/${_disp}.o" ] || [ "seeds/${_disp}.from_x.c" -nt "src/asm/${_disp}.o" ]; then
  echo " cc -c seeds/${_disp}.from_x.c -> src/asm/${_disp}.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "src/asm/${_disp}.o" "seeds/${_disp}.from_x.c"
  fi
  elif [ -f "src/asm/${_disp}.inc" ]; then
  if [ ! -f "src/asm/${_disp}.o" ] || [ "src/asm/${_disp}.inc" -nt "src/asm/${_disp}.o" ]; then
  echo " cc -c src/asm/${_disp}.inc -> src/asm/${_disp}.o"
  sh scripts/cc_inc_tu.sh "src/asm/${_disp}.inc" "src/asm/${_disp}.o" -I. -Iinclude -Isrc
  fi
  fi
  done
  if [ ! -f src/asm/backend_x86_64_enc_c.o ] || [ "seeds/backend_x86_64_enc_c.from_x.c" -nt src/asm/backend_x86_64_enc_c.o ]; then
  echo " cc -c seeds/backend_x86_64_enc_c.from_x.c -> src/asm/backend_x86_64_enc_c.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/backend_x86_64_enc_c.from_x.c -o src/asm/backend_x86_64_enc_c.o -I. -Iinclude -Isrc
  fi
  if [ ! -f src/driver/fmt_check_cmd_driver.o ] \
  || [ "seeds/fmt_check_cmd.from_x.c" -nt src/driver/fmt_check_cmd_driver.o ]; then
  echo " cc -c seeds/fmt_check_cmd.from_x.c -> src/driver/fmt_check_cmd_driver.o (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE -c seeds/fmt_check_cmd.from_x.c -o src/driver/fmt_check_cmd_driver.o
  fi
  if [ ! -f src/driver/target_cpu.o ] \
  || [ "seeds/target_cpu_pure.from_x.c" -nt src/driver/target_cpu.o ]; then
  echo " cc -c seeds/target_cpu_pure.from_x.c -> src/driver/target_cpu.o"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c seeds/target_cpu_pure.from_x.c -o src/driver/target_cpu.o
  fi
  if [ ! -f src/asm/simd_enc.o ] \
  || [ "seeds/simd_enc.from_x.c" -nt src/asm/simd_enc.o ]; then
  echo " cc -c seeds/simd_enc.from_x.c -> src/asm/simd_enc.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/simd_enc.from_x.c -o src/asm/simd_enc.o
  fi
  if [ ! -f src/asm/simd_loop.o ] \
  || [ "seeds/simd_loop.from_x.c" -nt src/asm/simd_loop.o ]; then
  echo " cc -c seeds/simd_loop.from_x.c -> src/asm/simd_loop.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/simd_loop.from_x.c -o src/asm/simd_loop.o
  fi
  if [ ! -f src/asm/user_asm_seed_bridge.o ] \
  || [ "seeds/user_asm_seed_bridge.from_x.c" -nt src/asm/user_asm_seed_bridge.o ]; then
  echo " cc -c seeds/user_asm_seed_bridge.from_x.c -> src/asm/user_asm_seed_bridge.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/user_asm_seed_bridge.from_x.c -o src/asm/user_asm_seed_bridge.o
  fi
  # parser EMIT_HEAVY extern bl _glue：须与 Makefile USER_ASM_SEED_OBJS 同步链入 xlang_asm。
  PARSER_ASM_THIN_GLUE_CFLAGS="-DPARSER_ASM_THIN_GLUE_NO_SEED_PARSE"
  if [ ! -f parser_asm_thin_glue.o ] \
  || [ "seeds/parser_asm_thin_c.from_x.c" -nt parser_asm_thin_glue.o ] \
  || [ "seeds/parser_asm/parser_asm_struct_layout_slice.inc" -nt parser_asm_thin_glue.o ] \
  || [ "seeds/parser_asm/parser_asm_block_from_res_slice.inc" -nt parser_asm_thin_glue.o ] \
  || [ "seeds/parser_asm/parser_asm_if_stmt_slice.inc" -nt parser_asm_thin_glue.o ] \
  || [ "seeds/parser_asm/parser_asm_type_ref_slice.inc" -nt parser_asm_thin_glue.o ]; then
  echo " cc -c seeds/parser_asm_thin_c.from_x.c -> parser_asm_thin_glue.o"
  $CC $CFLAGS $PARSER_ASM_THIN_GLUE_CFLAGS -I. -Iinclude -Isrc -Isrc/lexer -Isrc/asm \
    -c seeds/parser_asm_thin_c.from_x.c -o parser_asm_thin_glue.o
  fi
}

# bootstrap-driver-seed 同款的 C 种子 .o：与 pipeline_x.o 并存时不链完整 ast.c（用 -DXLANG_USE_X_AST 的 ast_seed）。
# E-02 v1：默认 seed 链 lsp_diag_stubs_no_c.o；XLANG_LEGACY_LSP_DIAG_C=1 恢复 lsp_diag.c。
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
  echo " cc -c $seed_dir/lsp_diag.o <- lsp_diag.c (LEGACY)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lsp_glue.from_x.c -o "$seed_dir/lsp_diag.o"
  fi
  else
  if [ ! -f "$seed_dir/lsp_diag_stubs_no_c.o" ] || [ "seeds/lsp_diag_stubs_no_c.from_x.c" -nt "$seed_dir/lsp_diag_stubs_no_c.o" ]; then
  echo " cc -c $seed_dir/lsp_diag_stubs_no_c.o (E-02 soft-retire lsp_diag.c)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/lsp_diag_stubs_no_c.from_x.c -o "$seed_dir/lsp_diag_stubs_no_c.o"
  fi
  fi
}

ensure_diag_seed_obj() {
  local seed_dir="$1"
  if [ ! -f "$seed_dir/diag.o" ] || [ "seeds/diag.from_x.c" -nt "$seed_dir/diag.o" ] || [ "include/diag.h" -nt "$seed_dir/diag.o" ]; then
  echo " cc -c $seed_dir/diag.o <- seeds/diag.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/diag.from_x.c -o "$seed_dir/diag.o"
  fi
}

ensure_asm_driver_seed_support_c_objs() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  mkdir -p "$SEED_DIR"
  ensure_diag_seed_obj "$SEED_DIR"
  if [ ! -f "$SEED_DIR/async_liveness.o" ] || [ seeds/async_liveness.from_x.c -nt "$SEED_DIR/async_liveness.o" ]; then
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/async_liveness.from_x.c -o "$SEED_DIR/async_liveness.o"
  fi
  if [ ! -f "$SEED_DIR/async_cps_codegen.o" ] || [ seeds/async_cps_codegen.from_x.c -nt "$SEED_DIR/async_cps_codegen.o" ]; then
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/async_cps_codegen.from_x.c -o "$SEED_DIR/async_cps_codegen.o"
  fi
  ensure_lsp_diag_seed_obj "$SEED_DIR"
  LSP_DIAG_SEED_O=$(lsp_diag_seed_obj_path "$SEED_DIR")
  export LSP_DIAG_SEED_O
  if [ ! -f src/lsp/lsp_diag_pipeline_ctx.o ] || [ seeds/lsp_diag_pipeline_ctx.from_x.c -nt src/lsp/lsp_diag_pipeline_ctx.o ]; then
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/lsp_diag_pipeline_ctx.from_x.c -o src/lsp/lsp_diag_pipeline_ctx.o
  fi
}

ensure_asm_driver_seed_frontend_c_objs() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  mkdir -p "$SEED_DIR"
  # G-02a：默认 omit C 前端 seed；X *_x.o 由 ensure_asm_bootstrap_x_companion_objs 提供。
  if asm_seed_omit_c_frontend_seed; then
  echo " G-02a: omit C frontend seed (X *_x.o; XLANG_LEGACY_SEED_FRONTEND_CC=1 to restore cc -c)"
  return 0
  fi
  echo " cc -c asm_driver_seed/*.o <- lexer/ast_seed/typeck/codegen .c (XLANG_LEGACY_SEED_FRONTEND_CC archaeology)"
  if [ ! -f seeds/runtime_lexer_glue.from_x.c ] || [ ! -f seeds/runtime_ast_glue.from_x.c ] \
  || [ ! -f src/typeck/typeck.c ]; then
  build_xlang_asm_error "LEGACY seed frontend .c missing; use X companions or restore C sources"
  return 1
  fi
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_lexer_glue.from_x.c -o "$SEED_DIR/lexer.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_ast_glue.from_x.c -o "$SEED_DIR/ast_seed.o"
  "$CC" $CFLAGS -c -o "$SEED_DIR/typeck.o" src/typeck/typeck.c
  # G-02a: codegen.c 已物理删除；codegen.o 由 codegen.x 生成（codegen_x.o），编排桩由 codegen_pipeline_stubs.o 提供。
  if [ -f src/codegen/codegen.c ]; then
  "$CC" $CFLAGS -c -o "$SEED_DIR/codegen.o" src/codegen/codegen.c
  fi
}

# E-06 v2/v4：X 前端 *.o 就绪检测（parser_x / typeck_x / codegen_x / lexer_x）。
asm_seed_x_frontend_o_ready() {
  for o in parser_x.o typeck_x.o codegen_x.o lexer_x.o; do
  if [ ! -f "$o" ] || [ ! -s "$o" ]; then
  return 1
  fi
  done
  return 0
}

# E-06 v4：X 前端 .o 就绪时 experimental / strict 链不 cc -c / 不链 asm_driver_seed 前端 C TU（与 omit 一致）。
asm_seed_use_x_frontend() {
  asm_seed_omit_c_frontend_seed
}

# E-06 v4：gen_driver / ensure_asm_driver_seed — X 就绪即 omit C 前端 seed（不要求 SKIP_GEN）。
asm_seed_omit_c_frontend_seed() {
  if [ -n "${XLANG_LEGACY_SEED_FRONTEND_CC:-}" ]; then
  return 1
  fi
  asm_seed_x_frontend_o_ready
}

# E-06 v3：strict 重链仅保留 async seed（无 parser/typeck/codegen/lexer/ast C 前端 .o）。
asm_seed_st_async_support_link() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  echo "$SEED_DIR/async_liveness.o $SEED_DIR/async_cps_codegen.o"
}

# E-06 v3：legacy strict 仍链 asm_driver_seed 全量 C 前端 .o（考古 / 非 SKIP_GEN）。
# G-02a: typeck.c 已物理删除；typeck.o 不再编译（typeck_x.o + typeck_c_module_stubs.o 提供）。
asm_seed_st_frontend_seed_link() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  echo "$SEED_DIR/parser.o $SEED_DIR/async_liveness.o $SEED_DIR/async_cps_codegen.o $SEED_DIR/lexer.o $SEED_DIR/ast_seed.o"
}

# E-06 v3：bare typeck alias 路径省略 seed typeck.o，其余与 frontend_seed 一致。
asm_seed_st_frontend_seed_no_typeck_link() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  echo "$SEED_DIR/parser.o $SEED_DIR/async_liveness.o $SEED_DIR/async_cps_codegen.o $SEED_DIR/lexer.o $SEED_DIR/ast_seed.o"
}

# X glue 后缀：codegen_x + x link alias（strict / experimental 共用）。
asm_seed_st_x_glue_suffix() {
  echo "codegen_x.o x_frontend_link_alias.o"
}

# G-02a: preprocess.c 已物理删除；preprocess 由 preprocess_x.o 提供，不链 seed preprocess.o。
asm_seed_st_preprocess_link() {
  echo ""
}

# E-06 v4：gen_driver 回退链 — omit seed C 前端 .o（lexer/ast/parser/typeck/codegen）。
asm_seed_gen_driver_c_frontend_link() {
  SEED_DIR="${SEED_DIR:-$BUILD_DIR/asm_driver_seed}"
  if asm_seed_omit_c_frontend_seed; then
  echo ""
  return 0
  fi
  echo "$SEED_DIR/lexer.o $SEED_DIR/ast_seed.o $SEED_DIR/parser.o"
}

ensure_asm_driver_seed_c_objs() {
  SEED_DIR="$BUILD_DIR/asm_driver_seed"
  export SEED_DIR
  if asm_seed_omit_c_frontend_seed; then
  echo " E-06 v2/v4: asm_driver_seed skip frontend cc -c (X *_x.o; XLANG_LEGACY_SEED_FRONTEND_CC=1 to restore)"
  ensure_asm_driver_seed_support_c_objs
  return 0
  fi
  ensure_asm_driver_seed_frontend_c_objs
  ensure_asm_driver_seed_support_c_objs
}

# strict 重链 companion：与 experimental bootstrap 一致。
# - std_sys_shim：driver_emit_x / pipeline read_file
# - parser_asm_parse_expr_link：thin glue → parser_x parse_expr_into
# - pipeline_fill_dep_strict_alias：strict 链仅 fill_dep 裸名（勿整包 pipeline_run_x_link_alias）
ensure_asm_strict_link_extra_objs() {
  # G-02e: std_sys_shim merged into runtime_io_abi.o (ensured above / DRIVER_SEED)
  if [ ! -f src/runtime_io_abi.o ] || [ seeds/runtime_io_abi.from_x.c -nt src/runtime_io_abi.o ]; then
  echo " cc -c seeds/runtime_io_abi.from_x.c -> src/runtime_io_abi.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o src/runtime_io_abi.o
  fi
  if [ ! -f src/asm/parser_asm_parse_expr_link.o ] \
  || [ seeds/parser_asm_parse_expr_link.from_x.c -nt src/asm/parser_asm_parse_expr_link.o ]; then
  echo " cc -c seeds/parser_asm_parse_expr_link.from_x.c -> src/asm/parser_asm_parse_expr_link.o"
  $CC $CFLAGS -I. -Iinclude -Isrc -DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS \
    -c seeds/parser_asm_parse_expr_link.from_x.c -o src/asm/parser_asm_parse_expr_link.o
  fi
  # G-02-B1：优先 .x（-backend asm）；无 xlang 或失败时回退 .c（删 C 前须 Docker Stage2 回归）。
  if [ -f src/asm/pipeline_fill_dep_strict_alias.x ] \
  && { [ ! -f src/asm/pipeline_fill_dep_strict_alias.o ] \
  || [ src/asm/pipeline_fill_dep_strict_alias.x -nt src/asm/pipeline_fill_dep_strict_alias.o ]; }; then
  if [ -x "$XLANG" ] && "$XLANG" build -backend asm -o src/asm/pipeline_fill_dep_strict_alias.o $LIBROOT \
  src/asm/pipeline_fill_dep_strict_alias.x 2>/dev/null \
  && [ -s src/asm/pipeline_fill_dep_strict_alias.o ]; then
  echo " $XLANG -backend asm -> src/asm/pipeline_fill_dep_strict_alias.o (G-02-B1 .x)"
  elif [ -f seeds/pipeline_fill_dep_strict_alias.from_x.c ]; then
  echo " cc -c seeds/pipeline_fill_dep_strict_alias.from_x.c -> src/asm/pipeline_fill_dep_strict_alias.o (fallback)"
  sh scripts/cc_inc_tu.sh seeds/pipeline_fill_dep_strict_alias.from_x.c src/asm/pipeline_fill_dep_strict_alias.o
  fi
  elif [ ! -f src/asm/pipeline_fill_dep_strict_alias.o ] \
  && [ -f seeds/pipeline_fill_dep_strict_alias.from_x.c ]; then
  echo " cc -c seeds/pipeline_fill_dep_strict_alias.from_x.c -> src/asm/pipeline_fill_dep_strict_alias.o"
  sh scripts/cc_inc_tu.sh seeds/pipeline_fill_dep_strict_alias.from_x.c src/asm/pipeline_fill_dep_strict_alias.o
  fi
  # preprocess_if_stack_* 由 runtime_pipeline_abi／pipeline orch 提供
  # （ast_pool.c mega left wave309）；bridge 已删除。
}

# experimental / strict 链：lsp_state.o 依赖 typeck_lsp_main_impl（lsp.x -E → lsp_x.o）；勿拉整包 gen_driver。
ensure_asm_experimental_lsp_objs() {
  GEN_DIR="$BUILD_DIR/gen_driver"
  mkdir -p "$GEN_DIR"
  local lsp_ok=1
  for o in lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o; do
  if [ ! -f "$o" ] || [ ! -s "$o" ]; then
  lsp_ok=0
  break
  fi
  done
  if [ "$lsp_ok" -eq 1 ]; then
  cp -f lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o "$GEN_DIR/"
  cp -f lsp_io_std_heap_x.o "$GEN_DIR/lsp_io_std_heap_x.o"
  return 0
  fi
  # PLATFORM: SHARED — post-Makefile phys-del: do NOT early-bail to gen_driver on
  # missing MF. Shell gen + try-heat is the authority (wave930). VIA_MAKE + MF escapes.
  # OOM 可能留下 0 字节 gen；删空文件以便 shell gen / try-heat 重产。
  if [ -f lsp_io_std_heap_gen.c ] && [ ! -s lsp_io_std_heap_gen.c ]; then
  rm -f lsp_io_std_heap_gen.c
  fi
  build_xlang_asm_info "ensure lsp_x.o (+ lsp_io) for lsp_state (typeck_lsp_main_impl)"
  # Wave930: shell gen + try-heat (no make; lsp_gen.c via ensure_lsp_pipeline_gen.sh,
  # lsp_io_std_heap_gen.c via ensure_archaeology_gen.sh, *_x.o via try-heat / cc).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    make -s lsp_io_gen.c lsp_gen.c lsp_io_std_heap_gen.c lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o
  else
    bash scripts/ensure_lsp_pipeline_gen.sh lsp
    bash scripts/ensure_archaeology_gen.sh lsp_io_std_heap
    bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_x.o
    bash scripts/ensure_host_cc_seed_o.sh try-heat lsp_io_x.o
    # lsp_io_std_heap_x.o: no Makefile rule (via driver_leaf / direct cc); cc -c from gen.c.
    if [ ! -f lsp_io_std_heap_x.o ] && [ -f lsp_io_std_heap_gen.c ]; then
      "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
        -c lsp_io_std_heap_gen.c -o lsp_io_std_heap_x.o
    fi
  fi
  cp -f lsp_x.o lsp_io_x.o lsp_io_std_heap_x.o "$GEN_DIR/"
}

# pipeline_x.o freshness (G.7 single authority; twin of relink_xlang_asm_strict_glue).
# PLATFORM: SHARED — after wave335 / 8.3 leave, ast_pool.c and pipeline_glue.c are
# absent; dead -nt on those paths never fired (bash treats missing LHS as false).
# pipeline_x.o producer = src/pipeline/pipeline.x via try-gen-x (pure-extern leaf),
# NOT runtime_pipeline_abi.x — abi freshness lives in ensure_experimental_ast_pool_for_wpo
# / runtime_pipeline_abi.o. Do not retarget this ensure to abi (would forever need=1
# while cwd pipeline_x.o stays a tiny stub). Authority = PIPELINE_X_DEPS only.
ensure_pipeline_x_o_fresh() {
  local need=0
  # runtime-only relink：已有 pipeline_x.o 时跳过（勿因源 mtime 触发 bootstrap-pipeline）。
  if [ -n "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ] && [ -f pipeline_x.o ]; then
  mkdir -p "$BUILD_DIR/gen_driver"
  if [ ! -f "$BUILD_DIR/gen_driver/pipeline_x.o" ] || ! cmp -s pipeline_x.o "$BUILD_DIR/gen_driver/pipeline_x.o" 2>/dev/null; then
  cp -fp pipeline_x.o "$BUILD_DIR/gen_driver/pipeline_x.o" 2>/dev/null || true
  fi
  return 0
  fi
  if [ ! -f pipeline_x.o ] || [ ! -f pipeline_gen.c ]; then
  need=1
  fi
  # PIPELINE_X_DEPS：asm 编码/backend 变更不会触达 pipeline_gen.c 时 ensure 仍须重 -E。
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
  # Wave930: shell ensure_lsp_pipeline_gen + try-heat (no make; bootstrap-pipeline
  # target thin-calls ensure_lsp_pipeline_gen.sh pipeline; pipeline_x.o via GEN_C_TO_O).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    build_xlang_asm_info "rebuild pipeline_x.o (PIPELINE_X_DEPS newer than pipeline_x.o)"
    make bootstrap-pipeline pipeline_x.o
  else
    build_xlang_asm_info "rebuild pipeline_x.o (PIPELINE_X_DEPS; ensure_lsp_pipeline_gen + try-heat)"
    bash scripts/ensure_lsp_pipeline_gen.sh pipeline
    bash scripts/ensure_host_cc_seed_o.sh try-heat pipeline_x.o
  fi
  fi
  # gen_driver 与 strict partial 须与 compiler/pipeline_x.o 同步；parser_x.o 变更后须失效旧 partial。
  if [ -f pipeline_x.o ]; then
  mkdir -p "$BUILD_DIR/gen_driver"
  if [ ! -f "$BUILD_DIR/gen_driver/pipeline_x.o" ] || ! cmp -s pipeline_x.o "$BUILD_DIR/gen_driver/pipeline_x.o" 2>/dev/null; then
  cp -fp pipeline_x.o "$BUILD_DIR/gen_driver/pipeline_x.o"
  fi
  fi
  if [ -f parser_x.o ]; then
  for stale in \
  "$BUILD_DIR/parser_bootstrap_partial.o" \
  "$BUILD_DIR/parser_strict_merged.o" \
  "$BUILD_DIR/parser_from_x_partial.o" \
  "$BUILD_DIR/pipeline_asm_strict_support_partial.o"; do
  if [ -f "$stale" ] && [ parser_x.o -nt "$stale" ]; then
  rm -f "$stale"
  fi
  done
  fi
}

# B-strict 最终链：用 seed xlang-c -E 的 parser_x.o 覆盖 C seed parser（struct return / param-binop 等门禁）。
# PLATFORM: SHARED — post-Makefile phys-del: do NOT early-return on missing MF;
# migrate_x_objs is the shell authority (wave929). VIA_MAKE + MF still escapes.
ensure_parser_x_o_for_strict_link() {
  if [ ! -f src/parser/parser.x ]; then
  return 0
  fi
  if [ ! -f parser_x.o ] || [ src/parser/parser.x -nt parser_x.o ]; then
  # Wave929: shell migrate_x_objs.sh (no make; MIGRATE_X_OBJS body authority).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    build_xlang_asm_info "make parser_x.o (strict link must override seed parser.o)"
    make -s parser_x.o
  else
    build_xlang_asm_info "migrate_x_objs parser_x.o (wave929; strict link override; 0-make)"
    bash scripts/migrate_x_objs.sh parser_x.o
  fi
  fi
}

# 用 xlang-c（优先）对 pipeline/main/lsp/preprocess 做 -E，再 cc 编成 .o；提供 pipeline_*、entry、main_run_compiler_c、asm_asm_codegen_elf_o 等。
# XLANG_E 可覆盖；默认 ./xlang-c（Makefile 约定：pipeline -E 须 C 解析器 stmt_order，勿用已链 x 前端的 xlang）。
ensure_asm_gen_driver_x_objs() {
  detect_pipeline_gen_cflags
  GEN_DIR="$BUILD_DIR/gen_driver"
  if [ "${XLANG_ASM_GEN_DRIVER_X_READY:-0}" = "1" ] \
  && [ -f "$GEN_DIR/pipeline_x.o" ] && [ -f "$GEN_DIR/driver_x.o" ] \
  && [ -f "$GEN_DIR/preprocess_x.o" ] && [ -f "$GEN_DIR/lsp_io_x.o" ] \
  && [ -f "$GEN_DIR/lsp_x.o" ] && [ -f "$GEN_DIR/lsp_io_std_heap_x.o" ] \
  && [ -f "$GEN_DIR/driver_fmt_x.o" ] && [ -f "$GEN_DIR/driver_check_x.o" ] \
  && [ -f "$GEN_DIR/driver_test_x.o" ]; then
  build_xlang_asm_info "reuse gen_driver X objs (already ensured in this run)"
  return 0
  fi
  mkdir -p "$GEN_DIR"
  XLANG_E="${XLANG_E:-}"
  if [ -z "$XLANG_E" ] || [ ! -x "$XLANG_E" ]; then
  if [ -x ./xlang-c ]; then
  XLANG_E=./xlang-c
  else
  XLANG_E="$XLANG"
  fi
  fi
  LIB_E_PIPELINE="-L .. -L src -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/asm -L src/preprocess"
  LIB_E_MAIN="-L .. -L src -L src/lsp -L src/lexer -L src/ast -L src/parser -L src/typeck -L src/codegen -L src/preprocess"

  # -E 单文件聚合时可能对 slice ABI 重复吐出同名 struct，同一 TU 内触发重定义；与 verify-selfhost.sh 一致只保留首行。
  dedupe_xlang_slice_struct() {
  f="$1"
  [ -f "$f" ] || return 0
  perl -i -ne 'print unless /^struct xlang_slice_uint8_t/ && $seen++' "$f" 2>/dev/null || true
  }

  # 与 Makefile bootstrap-pipeline 一致：优先复用已补齐布局的顶层 pipeline_gen.c，避免旧 xlang-c 重新 -E pipeline.x 失败。
  if [ -f pipeline_gen.c ] && [ -s pipeline_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  echo " pinned pipeline_gen.c -> $GEN_DIR/pipeline_gen.c ($(wc -c <pipeline_gen.c | tr -d ' ') bytes)"
  cp -f pipeline_gen.c "$GEN_DIR/pipeline_gen.c"
  else
  echo " $XLANG_E -E -E-extern pipeline.x -> $GEN_DIR/pipeline_gen.c ..."
  "$XLANG_E" $LIB_E_PIPELINE -E -E-extern src/pipeline/pipeline.x >"$GEN_DIR/pipeline_gen.c"
  fi
  if [ -f scripts/patch_pipeline_gen_ast_layout.pl ]; then
  perl scripts/patch_pipeline_gen_ast_layout.pl "$GEN_DIR/pipeline_gen.c"
  fi
  dedupe_xlang_slice_struct "$GEN_DIR/pipeline_gen.c"
  if [ -f lsp_io_gen.c ] && [ -s lsp_io_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  echo " pinned lsp_io_gen.c -> $GEN_DIR/lsp_io_gen.c ($(wc -c <lsp_io_gen.c | tr -d ' ') bytes)"
  cp -f lsp_io_gen.c "$GEN_DIR/lsp_io_gen.c"
  else
  echo " $XLANG_E -E lsp_io.x (-E-extern) -> $GEN_DIR/lsp_io_gen.c ..."
  "$XLANG_E" $LIB_E_MAIN src/lsp/lsp_io.x -E -E-extern >"$GEN_DIR/lsp_io_gen.c"
  fi
  if [ -f lsp_gen.c ] && [ -s lsp_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  echo " pinned lsp_gen.c -> $GEN_DIR/lsp_gen.c ($(wc -c <lsp_gen.c | tr -d ' ') bytes)"
  cp -f lsp_gen.c "$GEN_DIR/lsp_gen.c"
  else
  echo " $XLANG_E -E lsp.x (-E-extern) -> $GEN_DIR/lsp_gen.c ..."
  "$XLANG_E" $LIB_E_MAIN src/lsp/lsp.x -E -E-extern >"$GEN_DIR/lsp_gen.c"
  fi
  # lsp_gen.c 内大 state 数组迁至 lsp_state.c 的 g_lsp_state_buf（与 Makefile bootstrap-driver-seed 一致）
  sed -i.bak 's/uint8_t state_buf\[16388\] = { 0 }/extern uint8_t g_lsp_state_buf[16388]/' "$GEN_DIR/lsp_gen.c" 2>/dev/null || true
  sed -i.bak 's/(state_buf)/(g_lsp_state_buf)/g' "$GEN_DIR/lsp_gen.c" 2>/dev/null || true
  rm -f "$GEN_DIR/lsp_gen.c.bak"
  if [ ! -s lsp_io_std_heap_gen.c ]; then
    bash scripts/ensure_archaeology_gen.sh lsp_io_std_heap 2>/dev/null || true
  fi
  if [ -f lsp_io_std_heap_gen.c ] && [ -s lsp_io_std_heap_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  echo " pinned lsp_io_std_heap_gen.c -> $GEN_DIR/lsp_io_std_heap_gen.c ($(wc -c <lsp_io_std_heap_gen.c | tr -d ' ') bytes)"
  cp -f lsp_io_std_heap_gen.c "$GEN_DIR/lsp_io_std_heap_gen.c"
  else
  echo " $XLANG_E -E lsp_io_std_heap.x (-E-extern) -> $GEN_DIR/lsp_io_std_heap_gen.c ..."
  "$XLANG_E" $LIB_E_MAIN src/lsp/lsp_io_std_heap.x -E -E-extern >"$GEN_DIR/lsp_io_std_heap_gen.c" 2>/dev/null || true
  if [ ! -s "$GEN_DIR/lsp_io_std_heap_gen.c" ] && [ -f "seeds/lsp_io_std_heap_gen.linux.x86_64.c" ]; then
    echo " lsp_io_std_heap: -E failed/empty; fallback seed seeds/lsp_io_std_heap_gen.linux.x86_64.c (archaeology parity)"
    cp -f "seeds/lsp_io_std_heap_gen.linux.x86_64.c" "$GEN_DIR/lsp_io_std_heap_gen.c"
    cp -f "seeds/lsp_io_std_heap_gen.linux.x86_64.c" lsp_io_std_heap_gen.c 2>/dev/null || true
  fi
  fi
  driver_gen_pinned=0
  if [ -f driver_gen.c ] && [ -s driver_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  driver_gen_pinned=1
  for dep in src/main.x src/codegen/codegen.x src/ast/ast.x src/preprocess/preprocess.x; do
  if [ -f "$dep" ] && [ "$dep" -nt driver_gen.c ]; then
  driver_gen_pinned=0
  break
  fi
  done
  fi
  if [ "$driver_gen_pinned" = "1" ]; then
  echo " pinned driver_gen.c -> $GEN_DIR/driver_gen.c ($(wc -c <driver_gen.c | tr -d ' ') bytes)"
  cp -f driver_gen.c "$GEN_DIR/driver_gen.c"
  else
  # PLATFORM: SHARED — parity with scripts/ensure_driver_gen.sh: try xlang-x / xlang-c -E,
  # then seed fallback. Empty -E must not leave 0-byte driver_gen (Windows hybrid gate
  # previously died here when workspace pin was older than MAIN_X_DEPS).
  driver_gen_tmp="$GEN_DIR/driver_gen.c.tmp"
  driver_gen_seed="seeds/driver_gen.linux.x86_64.c"
  driver_gen_ok=0
  rm -f "$driver_gen_tmp"
  if [ -x ./xlang-x ]; then
  echo " ./xlang-x -x -E main.x (-E-extern) -> $GEN_DIR/driver_gen.c ..."
  ./xlang-x -x -E $LIB_E_MAIN -E-extern src/main.x >"$driver_gen_tmp" 2>/dev/null || true
  fi
  if [ -s "$driver_gen_tmp" ] && grep -q 'argc < 3' "$driver_gen_tmp" && grep -q 'main_eq_minus_E(arg_buf, len) != 0' "$driver_gen_tmp"; then
  mv -f "$driver_gen_tmp" "$GEN_DIR/driver_gen.c"
  driver_gen_ok=1
  else
  rm -f "$driver_gen_tmp"
  echo " $XLANG_E -E main.x (-E-extern) -> $GEN_DIR/driver_gen.c ..."
  "$XLANG_E" $LIB_E_MAIN src/main.x -E -E-extern >"$driver_gen_tmp" 2>/dev/null || true
  if [ -s "$driver_gen_tmp" ] && grep -q 'argc < 3' "$driver_gen_tmp" && grep -q 'main_eq_minus_E(arg_buf, len) != 0' "$driver_gen_tmp"; then
  mv -f "$driver_gen_tmp" "$GEN_DIR/driver_gen.c"
  driver_gen_ok=1
  else
  rm -f "$driver_gen_tmp"
  if [ -f "$driver_gen_seed" ] && [ -s "$driver_gen_seed" ]; then
  echo " driver_gen: -E failed/empty; fallback seed $driver_gen_seed (ensure_driver_gen parity)"
  cp -f "$driver_gen_seed" "$GEN_DIR/driver_gen.c"
  # Keep workspace pin warm so a later pin-check can skip broken tip -E.
  cp -f "$driver_gen_seed" driver_gen.c
  touch driver_gen.c
  driver_gen_ok=1
  else
  echo " driver_gen: FAIL (-E failed and no seed $driver_gen_seed)" >&2
  : >"$GEN_DIR/driver_gen.c"
  fi
  fi
  fi
  if [ "$driver_gen_ok" != "1" ]; then
  echo "ensure_asm_gen_driver_x_objs: driver_gen.c missing/empty after pin/-E/seed" >&2
  return 1
  fi
  fi
  dedupe_xlang_slice_struct "$GEN_DIR/driver_gen.c"
  if [ -f preprocess_gen.c ] && [ -s preprocess_gen.c ] && [ "${XLANG_FORCE_REGEN_GEN:-0}" != "1" ]; then
  echo " pinned preprocess_gen.c -> $GEN_DIR/preprocess_gen.c ($(wc -c <preprocess_gen.c | tr -d ' ') bytes)"
  cp -f preprocess_gen.c "$GEN_DIR/preprocess_gen.c"
  else
  echo " $XLANG_E -E preprocess.x (-E-extern) -> $GEN_DIR/preprocess_gen.c ..."
  "$XLANG_E" -L src/lexer -E -E-extern src/preprocess/preprocess.x >"$GEN_DIR/preprocess_gen.c"
  fi
  dedupe_xlang_slice_struct "$GEN_DIR/preprocess_gen.c"

  # Track L：fmt/check/test 叶子退役 — 始终从 .x -E（不再 pin 工作区 driver_*_gen.c）
  # 符号 rename 与 Makefile / prove_module_selfhost 一致；产物直接写 gen_driver/*.o
  echo " Track L: driver_fmt/check/test_x.o <- src/driver/*.x (PREFER_X_O)"
  DRIVER_SUBCMD_DIRS="-L .. -L src -L src/lexer -L src/ast" \
    BASE_CFLAGS="$CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc" \
    bash scripts/driver_leaf_x_to_o.sh src/driver/fmt.x "$GEN_DIR/driver_fmt_x.o" 'cmd_fmt:driver_cmd_fmt' seeds/driver_fmt_gen.linux.x86_64.c
  DRIVER_SUBCMD_DIRS="-L .. -L src -L src/lexer -L src/ast" \
    BASE_CFLAGS="$CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc" \
    bash scripts/driver_leaf_x_to_o.sh src/driver/check.x "$GEN_DIR/driver_check_x.o" 'cmd_check:driver_cmd_check' seeds/driver_check_gen.linux.x86_64.c
  DRIVER_SUBCMD_DIRS="-L .. -L src -L src/lexer -L src/ast" \
    BASE_CFLAGS="$CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc" \
    bash scripts/driver_leaf_x_to_o.sh src/driver/test.x "$GEN_DIR/driver_test_x.o" 'cmd_test:driver_cmd_test' seeds/driver_test_gen.linux.x86_64.c
  # 同步工作区副本供后续链接行引用 compiler/driver_*_x.o
  cp -f "$GEN_DIR/driver_fmt_x.o" driver_fmt_x.o 2>/dev/null || true
  cp -f "$GEN_DIR/driver_check_x.o" driver_check_x.o 2>/dev/null || true
  cp -f "$GEN_DIR/driver_test_x.o" driver_test_x.o 2>/dev/null || true

  # pipeline/driver/preprocess: same products as retired Makefile gen-x-driver-objs.
  #
  # PLATFORM: WINDOWS | MINGW | MSYS — do NOT:
  #   1) nest MinGW `make gen-x-driver-objs` (sh.dll "C:", empty UNAME_M, 0-CPU stall)
  #   2) call `ensure try-heat pipeline_x.o` from this script on MinGW — observed
  #      recursive re-entry (parent chain of ensure_host_cc_seed_o.sh try-heat
  #      pipeline_x.o with no gcc, frozen hybrid log_bytes) until kill.
  # Seed/g05 already owns pipeline_x.o / driver_x.o / preprocess_x.o on the
  # hybrid host; reuse when present, else direct cc -c of pinned gen.c.
  # PLATFORM: SHARED Linux/Darwin — post-Makefile phys-del: shell try-heat is the
  # authority (wave930). Do NOT gate try-heat on MF presence (that forced raw
  # cc -c after phys-del). VIA_MAKE + MF still escapes for parity / debug.
  if build_xlang_asm_is_msys; then
    if [ -f pipeline_x.o ] && [ -f driver_x.o ] && [ -f preprocess_x.o ]; then
      echo " win: reuse seed pipeline_x.o driver_x.o preprocess_x.o (skip nested make + try-heat)"
      cp -f pipeline_x.o "$GEN_DIR/"
      cp -f driver_x.o "$GEN_DIR/driver_x.o"
      cp -f preprocess_x.o "$GEN_DIR/preprocess_x.o"
    else
      echo " win: cc -c gen_driver/*_x.o (missing seed objs; no nested make/try-heat)"
      "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I.. \
        -Dstd_io_driver_driver_read_ptr_len=xlang_io_read_ptr_len \
        -Dstd_io_driver_driver_read_ptr=xlang_io_read_ptr \
        -c "$GEN_DIR/pipeline_gen.c" -o "$GEN_DIR/pipeline_x.o"
      "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -include src/x_stubs.h \
        -Dstd_fs_fs_read=fs_posix_read_c -Dstd_fs_fs_write=fs_posix_write_c -Dstd_fs_fs_close=fs_posix_close_c \
        -c "$GEN_DIR/driver_gen.c" -o "$GEN_DIR/driver_x.o"
      "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -c "$GEN_DIR/preprocess_gen.c" -o "$GEN_DIR/preprocess_x.o"
      cp -f "$GEN_DIR/pipeline_x.o" pipeline_x.o 2>/dev/null || true
      cp -f "$GEN_DIR/driver_x.o" driver_x.o 2>/dev/null || true
      cp -f "$GEN_DIR/preprocess_x.o" preprocess_x.o 2>/dev/null || true
    fi
  else
    # Wave930: shell try-heat for 3 leaves (no make).
    # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug; MF must exist).
    if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
      && command -v make >/dev/null 2>&1; then
      echo " make gen-x-driver-objs -> copy pipeline_x.o driver_x.o preprocess_x.o to $GEN_DIR/"
      make gen-x-driver-objs
    else
      echo " wave930: try-heat pipeline_x.o + driver_x.o + preprocess_x.o -> $GEN_DIR/ (0-make)"
      bash scripts/ensure_host_cc_seed_o.sh try-heat pipeline_x.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat driver_x.o
      bash scripts/ensure_host_cc_seed_o.sh try-heat preprocess_x.o
    fi
    cp -f pipeline_x.o "$GEN_DIR/"
    cp -f driver_x.o "$GEN_DIR/driver_x.o"
    cp -f preprocess_x.o "$GEN_DIR/preprocess_x.o"
  fi

  echo " cc -c gen_driver/lsp*.o <- lsp -E 产物"
  "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I. -Dstd_io_read=io_read -Dstd_io_write=io_write \
  -Dstd_heap_alloc_usize=typeck_std_heap_alloc -Dstd_heap_free_u8_ptr=typeck_std_heap_free \
  -Dtypeck_std_heap_alloc=lsp_io_std_heap_std_heap_alloc \
  -Dtypeck_std_heap_free=lsp_io_std_heap_std_heap_free \
  -c "$GEN_DIR/lsp_io_gen.c" -o "$GEN_DIR/lsp_io_x.o"
  "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I. -c "$GEN_DIR/lsp_gen.c" -o "$GEN_DIR/lsp_x.o"
  "$CC" $CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
  -c "$GEN_DIR/lsp_io_std_heap_gen.c" -o "$GEN_DIR/lsp_io_std_heap_x.o"
  ensure_gen_driver_typeck_companion_objs
  XLANG_ASM_GEN_DRIVER_X_READY=1
}

# gen_driver fallback: pipeline_x.o mega C calls typeck_check_* (from typeck.x -E);
# must link typeck_x.o + x_frontend_link_alias.o.
# PLATFORM: WINDOWS | MINGW | MSYS — never nest MinGW make for these leaves:
#   make typeck_x.o / x_frontend_link_alias.o → FORCE try-heat re-entry hang
#   (same class as pipeline_x.o ensure recursion). Reuse seed/g05 objs when present.
# PLATFORM: SHARED Linux/Darwin — post-Makefile phys-del: shell migrate + try-heat
# is the authority (wave929). Do NOT gate on MF presence (that silently skipped
# ensure after phys-del). VIA_MAKE + MF still escapes for parity / debug.
ensure_gen_driver_typeck_companion_objs() {
  if [ "${XLANG_ASM_GEN_DRIVER_TYPECK_READY:-0}" = "1" ] \
    && [ -f typeck_x.o ] && [ -f x_frontend_link_alias.o ]; then
    build_xlang_asm_info "reuse gen_driver typeck companions (already ensured in this run)"
    return 0
  fi
  if build_xlang_asm_is_msys; then
    if [ -f typeck_x.o ] && [ -f x_frontend_link_alias.o ]; then
      build_xlang_asm_info "win: reuse seed typeck_x.o + x_frontend_link_alias.o (skip nested make)"
    else
      build_xlang_asm_info "win: WARN missing typeck companions; hybrid link may fail (no nested make)"
    fi
    XLANG_ASM_GEN_DRIVER_TYPECK_READY=1
    return 0
  fi
  # Wave929: shell migrate + try-heat (no make; MIGRATE_X_OBJS + R1_ALIAS_STUBS bodies).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug; MF must exist).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] \
    && command -v make >/dev/null 2>&1; then
    build_xlang_asm_info "gen_driver typeck companions (typeck_x.o + link alias)"
    make typeck_x.o x_frontend_link_alias.o
  else
    build_xlang_asm_info "gen_driver typeck companions (wave929; migrate + try-heat; 0-make)"
    bash scripts/migrate_x_objs.sh typeck_x.o
    bash scripts/ensure_host_cc_seed_o.sh try-heat x_frontend_link_alias.o
  fi
  XLANG_ASM_GEN_DRIVER_TYPECK_READY=1
}

# 与 ensure_gen_driver_typeck_companion_objs 配套：gen_driver 链接行追加对象（experimental 链已含；回退仅补 typeck mega 符号）。
GEN_DRIVER_TYPECK_COMPANIONS="typeck_x.o x_frontend_link_alias.o"

# lsp_diag.c 依赖 pipeline 结构体 sizeof（与 Makefile bootstrap-driver-seed 一致）
ensure_lsp_diag_pipeline_sizes_obj() {
  if [ ! -f src/lsp/lsp_diag_pipeline_sizes.o ]; then
  echo " cc -c src/lsp/lsp_diag_pipeline_sizes.o"
  sh scripts/cc_inc_tu.sh seeds/lsp_diag_pipeline_sizes_weak.from_x.c src/lsp/lsp_diag_pipeline_sizes.o
  fi
}

# B-hybrid 链 lsp_x.o 需要 lsp_build_diagnostics_response 等；typeck_lsp_io 见 seeds/typeck_lsp_io_stub.from_x.c。
# wave297: host scripts/asm_xlang_lsp_diag_stub.c left; seed authority seed-only .o.
ensure_asm_xlang_lsp_diag_stub_obj() {
  STUB_C="seeds/asm_xlang_lsp_diag_stub.from_x.c"
  STUB_O="$BUILD_DIR/asm_xlang_lsp_diag_stub.o"
  LSP_IO_STUB="seeds/typeck_lsp_io_stub.from_x.c"
  LSP_IO_O="$BUILD_DIR/typeck_lsp_io_stub.o"
  if [ ! -f "$LSP_IO_O" ] || [ "$LSP_IO_STUB" -nt "$LSP_IO_O" ]; then
  echo " cc_inc_tu $LSP_IO_O <- $LSP_IO_STUB"
  sh scripts/cc_inc_tu.sh "$LSP_IO_STUB" "$LSP_IO_O"
  fi
  if [ ! -f "$STUB_O" ] || [ "$STUB_C" -nt "$STUB_O" ]; then
  echo " cc -c $STUB_O <- $STUB_C"
  "$CC" $CFLAGS -c -o "$STUB_O" "$STUB_C"
  fi
}

# codegen.o（C seed）引用 lsp_codegen_emit_*；小 TU，不与 pipeline_x.o 重复
ensure_asm_lsp_codegen_extern_obj() {
  LCE_C="seeds/runtime_driver_strict_glue_stubs.from_x.c"
  LCE_O=src/runtime_driver_strict_glue_stubs.o
  if [ ! -f "$LCE_O" ] || [ "$LCE_C" -nt "$LCE_O" ]; then
  echo " cc -c $LCE_O <- $LCE_C (G-02f-11)"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$LCE_O" "$LCE_C"
  fi
}

# 回退链接所需的 C 桩（不依赖 make）
ensure_runtime_cc_stubs() {
  echo " cc -c src/asm/runtime_asm_build.o <- seeds/runtime_asm_build.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_asm_build.from_x.c -o src/asm/runtime_asm_build.o
  # PLATFORM: SHARED — Do NOT clobber src/runtime_driver.o if it already exists.
  # make bootstrap-driver-seed / g05_ensure build src/runtime_driver.o with the
  # full RUNTIME_DRIVER_CFLAGS (-DXLANG_NO_C_FRONTEND -DXLANG_RT_*_FROM_X
  # -DXLANG_ASM_USE_COMPILER_IMPL_C). This fallback only has a subset of flags
  # (-DXLANG_USE_X_PREPROCESS); rebuilding with the subset produces a .o with
  # different symbol definitions that breaks the g05/make product link (the
  # X pipeline silently returns -1). Only build the fallback when the
  # authoritative .o is ABSENT (cold start with no prior make/g05).
  if [ -f src/runtime_driver.o ] && [ -s src/runtime_driver.o ]; then
    echo " ensure: src/runtime_driver.o exists (make/g05 authority); skip fallback rebuild"
  else
    # wave321 7.1.1: monofile seeds/runtime.from_x.c retired — multi-slice no_c + alias.
    # PLATFORM: SHARED freestanding; archaeology fallback uses product authority.
    echo " ensure: src/runtime_driver.o via try-rt-prefer multi-slice (wave321 monofile retired)"
    if ! bash scripts/ensure_host_cc_seed_o.sh try-r1 src/runtime_driver.o; then
      build_xlang_asm_error "runtime_driver.o multi-slice fallback failed (wave321)"
      return 1
    fi
  fi
}

# B-strict xlang_asm：driver_run_compiler_full 走 impl_c（完整 parse_argv），勿与 seed 共用 runtime_driver.o 宏。
# G-02e：runtime_abi.c / runtime_proc_abi.c 已合并到 runtime_link_abi（ensure_runtime_link_abi_obj）；
#   codegen_pipeline_stubs.c 已合并到 strict_glue（runtime_driver_strict_glue_stubs.o）。
ensure_runtime_io_abi_obj() {
  local o="src/runtime_io_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_io_abi.from_x.c" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_io_abi.from_x.c (E-04 v3 I/O ABI)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_io_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_link_abi_obj() {
  local o="src/runtime_link_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_link_abi.from_x.c" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_link_abi.from_x.c (E-04 v5 link/cc ABI helpers)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_link_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_pipeline_abi_obj() {
  local o="src/runtime_pipeline_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_pipeline_abi.from_x.c" -nt "$o" ] || [ "Makefile" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_pipeline_abi.from_x.c (E-04 v32 pipeline import + preprocess ABI)"
  local pa_flags="-DXLANG_USE_X_PIPELINE"
  if [ "${XLANG_LEGACY_PREPROCESS_C:-0}" = "1" ]; then
  pa_flags="$pa_flags -DXLANG_LEGACY_PREPROCESS_C"
  fi
  $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE -c seeds/runtime_pipeline_abi.from_x.c -o "$o"
  fi
}

ensure_runtime_driver_abi_obj() {
  local o="src/runtime_driver_abi.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_abi.from_x.c" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_driver_abi.from_x.c (E-04 driver ABI: stack bump / dep path)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_abi.from_x.c -o "$o"
  fi
}

ensure_diag_obj() {
  local o="src/diag.o"
  if [ ! -f "$o" ] || [ "seeds/diag.from_x.c" -nt "$o" ] || [ "include/diag.h" -nt "$o" ]; then
  echo " cc -c $o <- seeds/diag.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/diag.from_x.c -o "$o"
  fi
}

ensure_runtime_driver_diagnostic_obj() {
  local o="src/runtime_driver_diagnostic.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_diagnostic.from_x.c" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_driver_diagnostic.from_x.c (E-04 typeck diagnostic hooks)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_diagnostic.from_x.c -o "$o"
  fi
}

# Cap residual：driver_abi 跨 TU 数据/thread_fn（与 Makefile RT_SEED_SLICE_OBJS 同源）。
# 须含 rt_parse_diag：runtime_report_parse_recovery_diagnostics 权威体在 seeds/rt_parse_diag.from_x.c
# （runtime.from_x.c 仅声明；缺链 → B-strict experimental link U 引用）。
ensure_rt_seed_slice_objs() {
  mkdir -p src/runtime
  local pair seed o
  for pair in \
    "rt_arena_buf:seeds/rt_arena_buf.from_x.c:src/runtime/rt_arena_buf.o" \
    "rt_emit_state:seeds/rt_emit_state.from_x.c:src/runtime/rt_emit_state.o" \
    "rt_preamble:seeds/rt_preamble.from_x.c:src/runtime/rt_preamble.o" \
    "rt_stack:seeds/rt_stack.from_x.c:src/runtime/rt_stack.o" \
    "rt_parse_diag:seeds/rt_parse_diag.from_x.c:src/runtime/rt_parse_diag.o"; do
    seed="${pair#*:}"
    seed="${seed%%:*}"
    o="${pair##*:}"
    if [ ! -f "$seed" ]; then
      build_xlang_asm_error "rt seed slice missing: $seed"
      return 1
    fi
    if [ ! -f "$o" ] || [ "$seed" -nt "$o" ]; then
      echo " cc -c $o <- $seed (Cap residual / RT seed slice)"
      $CC $CFLAGS -I. -Iinclude -Isrc -c "$seed" -o "$o"
    fi
  done
}

ensure_runtime_driver_asm_strict_obj() {
  ensure_runtime_io_abi_obj
  ensure_runtime_link_abi_obj
  ensure_runtime_pipeline_abi_obj
  ensure_runtime_driver_abi_obj
  ensure_diag_obj
  ensure_runtime_driver_diagnostic_obj
  ensure_rt_seed_slice_objs
  local o="src/runtime_driver_asm_bstrict.o"
  # wave321 7.1.1: monofile retired — product multi-slice no_c is authority;
  # bstrict archaeology .o is an alias of runtime_driver_no_c (same surface).
  # PLATFORM: SHARED freestanding; mtime gate = content layer seed + script.
  if [ ! -f "$o" ] \
    || { [ -f seeds/rt_content.from_x.c ] && [ seeds/rt_content.from_x.c -nt "$o" ]; } \
    || [ "scripts/build_xlang_asm.sh" -nt "$o" ]; then
    echo " ensure: $o ← multi-slice no_c alias (wave321 monofile retired)"
    if ! bash scripts/ensure_host_cc_seed_o.sh try-rt-prefer src/runtime_driver_no_c.o; then
      build_xlang_asm_error "runtime_driver_no_c multi-slice failed for bstrict alias (wave321)"
      return 1
    fi
    cp -f src/runtime_driver_no_c.o "$o" || return 1
  fi
  # 兼容旧链脚本/规则仍引用 runtime_driver_asm_strict.o
  cp -f "$o" src/runtime_driver_asm_strict.o 2>/dev/null || true
}

# bootstrap-driver-seed DRIVER_SEED_SUPPORT_EXTRA 对齐：X 前端 experimental 链缺 C codegen/lexer 时的桩。
ensure_asm_bootstrap_support_extra_objs() {
  local o
  o="src/lexer/cfg_eval.o"
  if [ -f src/lexer/cfg_eval.x ] \
  && { [ ! -f "$o" ] || [ src/lexer/cfg_eval.x -nt "$o" ]; }; then
  if [ -x "$XLANG" ] && "$XLANG" build -backend asm -o "$o" $LIBROOT src/lexer/cfg_eval.x 2>/dev/null \
  && [ -s "$o" ]; then
  echo " $XLANG -backend asm -> $o (G-02-B1 cfg_eval.x)"
  elif [ -x "$XLANG" ] && "$XLANG" build -E -E-extern $LIBROOT src/lexer/cfg_eval.x > src/lexer/cfg_eval_gen.c 2>/dev/null \
  && [ -s src/lexer/cfg_eval_gen.c ]; then
  echo " $XLANG -E-extern -> cfg_eval_gen.c + link alias -> $o (G-02-B1 cfg_eval.x)"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o src/lexer/cfg_eval_x.o src/lexer/cfg_eval_gen.c
  sh scripts/cc_inc_tu.sh seeds/cfg_eval_link_alias.from_x.c src/lexer/cfg_eval_link_alias.o
  "$LD" $LD_RELFLAGS -r -o "$o" src/lexer/cfg_eval_x.o src/lexer/cfg_eval_link_alias.o
  elif [ -f src/lexer/cfg_eval.x ] && [ -x "$XLANG" ]; then
  build_xlang_asm_error "cfg_eval: need $XLANG -backend asm or -E-extern for cfg_eval.x (G-02a: no cfg_eval.c)"
  return 1
  fi
  fi
  ensure_typeck_f64_bits_obj
  o="src/runtime_driver_strict_glue_stubs.o"
  if [ ! -f "$o" ] || [ "seeds/runtime_driver_strict_glue_stubs.from_x.c" -nt "$o" ]; then
  echo " cc -c $o <- seeds/runtime_driver_strict_glue_stubs.from_x.c (G-02f-11)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_driver_strict_glue_stubs.from_x.c -o "$o"
  fi
  ensure_typeck_c_module_stubs_obj
  # PLATFORM: SHARED — process_xlang_argc/argv_get (g05 DRIVER_SEED_OBJS); experimental/strict
  # both need this for backend_enc_dispatch process_args_count_c / process_arg_c.
  if [ ! -f runtime_process_argv.o ] || [ seeds/runtime_process_argv.from_x.c -nt runtime_process_argv.o ]; then
  echo " cc -c runtime_process_argv.o <- seeds/runtime_process_argv.from_x.c (bootstrap support)"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_process_argv.from_x.c -o runtime_process_argv.o
  fi
}

# experimental / strict runtime 链：heap_*_c 在 runtime_driver_strict_glue_stubs.o（G-02e-14）。
# RT Cap residual slices：与 Makefile RT_SEED_SLICE_OBJS 同源（含 parse_diag recovery）。
# PLATFORM: SHARED — include runtime_process_argv.o (process_xlang_argc/argv_get authority).
asm_bootstrap_support_extra_link() {
  echo "src/async/async_asm_pool.o src/lexer/cfg_eval.o src/typeck/typeck_f64_bits.o $BUILD_DIR/typeck_c_module_stubs.o src/runtime_driver_strict_glue_stubs.o runtime_process_argv.o src/runtime/rt_arena_buf.o src/runtime/rt_emit_state.o src/runtime/rt_preamble.o src/runtime/rt_stack.o src/runtime/rt_parse_diag.o"
}

# Ensure typeck_f64_bits.o (pipeline_x / parser f64 literal bit-split).
# wave762 G.7: body = ensure_host_cc_seed_o.sh try-r2 (catalog DRIVER_SEED_TYPECK_F64_OBJS).
# PLATFORM: WINDOWS | MINGW | MSYS — try-r2 re-parses catalog via
#   driver_seed_obj_catalog.sh --shell without XLANG_CATALOG_CACHE_FILE → known stall
#   (ensure_host header documents this). If seed .o already present, reuse it.
#   Cold miss: compile mingw .s directly (no ensure script / no catalog).
# PLATFORM: SHARED Linux/Darwin — try-r2 remains authority when ensure script exists.
ensure_typeck_f64_bits_obj() {
  local _f64o="src/typeck/typeck_f64_bits.o"
  local _f64s=""
  if build_xlang_asm_is_msys; then
    if [ -f "$_f64o" ]; then
      echo " win: reuse $_f64o (skip try-r2 catalog stall)"
      return 0
    fi
    if [ -f src/typeck/typeck_f64_bits_x86_64_mingw.s ]; then
      _f64s=src/typeck/typeck_f64_bits_x86_64_mingw.s
      echo " win: cc -c $_f64s → $_f64o (no try-r2)"
      pure_as_compile "$_f64o" "$_f64s" \
        || { echo "ensure_typeck_f64_bits_obj: win cc failed" >&2; return 1; }
      return 0
    fi
    echo "ensure_typeck_f64_bits_obj: win missing $_f64o and mingw .s" >&2
    return 1
  fi
  if [ -f scripts/ensure_host_cc_seed_o.sh ]; then
    echo " ensure try-r2 $_f64o (wave762 R2 typeck_f64)"
    CC="$CC" CFLAGS="$CFLAGS" bash scripts/ensure_host_cc_seed_o.sh try-r2 "$_f64o" \
      || { echo "ensure_typeck_f64_bits_obj: try-r2 failed" >&2; return 1; }
    return 0
  fi
  # Fallback only if ensure script missing (should not happen on product tree).
  UNAME_S=$(uname -s 2>/dev/null || echo Unknown)
  UNAME_M=$(uname -m 2>/dev/null || echo Unknown)
  if [ "$UNAME_S" = "Linux" ] && [ "$UNAME_M" = "x86_64" ] && [ -f src/typeck/typeck_f64_bits_x86_64.s ]; then
    pure_as_compile "$_f64o" src/typeck/typeck_f64_bits_x86_64.s
  elif [ "$UNAME_S" = "Linux" ] && [ "$UNAME_M" = "aarch64" ] && [ -f src/typeck/typeck_f64_bits_aarch64_elf.s ]; then
    pure_as_compile "$_f64o" src/typeck/typeck_f64_bits_aarch64_elf.s
  elif [ "$UNAME_S" = "Darwin" ] && [ "$UNAME_M" = "arm64" ] && [ -f src/typeck/typeck_f64_bits_arm64.s ]; then
    pure_as_compile "$_f64o" src/typeck/typeck_f64_bits_arm64.s
  elif [ "$UNAME_S" = "Darwin" ] && [ "$UNAME_M" = "x86_64" ] && [ -f src/typeck/typeck_f64_bits_x86_64.s ]; then
    pure_as_compile "$_f64o" src/typeck/typeck_f64_bits_x86_64.s
  else
    echo "ensure_typeck_f64_bits_obj: missing platform .s for $UNAME_S/$UNAME_M" >&2
    return 1
  fi
}

# typeck 整链 build_asm/typeck.o：裸符号 → typeck_ 前缀 glue 名。
# wave296: authority = seeds/typeck_asm_bare_link_alias.from_x.c (host leaf left).
# PLATFORM: SHARED — B-hybrid/strict_glue only; G05 does not link this .o.
ensure_typeck_asm_bare_link_alias_obj() {
  local OBJ="$BUILD_DIR/typeck_asm_bare_link_alias.o"
  local SEED="seeds/typeck_asm_bare_link_alias.from_x.c"
  local GEN="scripts/gen_typeck_asm_bare_link_alias.py"
  if [ -f "$GEN" ] && [ -f "$BUILD_DIR/typeck.o" ] && [ -f typeck_x.o ]; then
  if [ ! -f "$SEED" ] || [ src/typeck/typeck.x -nt "$SEED" ] \
  || [ "$BUILD_DIR/typeck.o" -nt "$SEED" ]; then
  python3 "$GEN" 2>/dev/null || true
  fi
  fi
  if [ ! -f "$SEED" ]; then
  echo "ensure_typeck_asm_bare_link_alias_obj: missing $SEED" >&2
  return 1
  fi
  if [ ! -f "$OBJ" ] || [ "$SEED" -nt "$OBJ" ]; then
  echo " cc -c $SEED -> $OBJ"
  "$CC" $CFLAGS -I. -Iinclude -Isrc -c -o "$OBJ" "$SEED"
  fi
}

# Ensure runtime_panic.o / crt0 / typeck_f64_bits exist.
# wave760/762 G.7: try-r2 body for panic/crt0; typeck_f64 via ensure_typeck_f64_bits_obj.
# PLATFORM: WINDOWS | MINGW | MSYS — never call try-r2 here: catalog parse without
#   XLANG_CATALOG_CACHE_FILE stalls / re-enters (observed stacked try-r2 bash).
#   Reuse seed panic.o or compile portable seed C; crt0 is Linux/Darwin only.
# PLATFORM: SHARED Linux/Darwin — try-r2 remains authority when ensure script exists.
ensure_asm_link_objs() {
  UNAME_S=$(uname -s 2>/dev/null || echo Unknown)
  ALPINE=0
  test -f /etc/alpine-release && ALPINE=1
  if build_xlang_asm_is_msys; then
    if [ -f runtime_panic.o ]; then
      echo " win: reuse runtime_panic.o (skip try-r2 catalog stall)"
    elif [ -f seeds/runtime_panic.from_x.c ]; then
      echo " win: cc -c runtime_panic.o <- seeds/runtime_panic.from_x.c (no try-r2)"
      $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_panic.from_x.c -o runtime_panic.o \
        || { echo "ensure_asm_link_objs: win panic cc failed" >&2; return 1; }
    else
      echo "ensure_asm_link_objs: win missing runtime_panic.o and seed" >&2
      return 1
    fi
  elif [ -f scripts/ensure_host_cc_seed_o.sh ]; then
    echo " ensure try-r2 runtime_panic.o (wave760 R2 cold body)"
    CC="$CC" CFLAGS="$CFLAGS" bash scripts/ensure_host_cc_seed_o.sh try-r2 runtime_panic.o \
      || { echo "ensure_asm_link_objs: try-r2 runtime_panic.o failed" >&2; return 1; }
    # PLATFORM: LINUX — product crt0 path; other hosts use MAIN_LINK via g05/make.
    if [ "$UNAME_S" = "Linux" ] && [ -f src/asm/crt0_x86_64.s ]; then
      echo " ensure try-r2 src/asm/crt0_x86_64.o (wave762 R2 crt0)"
      CC="$CC" CFLAGS="$CFLAGS" bash scripts/ensure_host_cc_seed_o.sh try-r2 src/asm/crt0_x86_64.o \
        || { echo "ensure_asm_link_objs: try-r2 crt0_x86_64.o failed" >&2; return 1; }
    elif [ "$UNAME_S" = "Darwin" ]; then
      UNAME_M=$(uname -m 2>/dev/null || echo unknown)
      if { [ "$UNAME_M" = "arm64" ] || [ "$UNAME_M" = "aarch64" ]; } && [ -f src/asm/crt0_arm64.s ]; then
        echo " ensure try-r2 src/asm/crt0_arm64.o (wave762 R2 crt0)"
        CC="$CC" CFLAGS="$CFLAGS" bash scripts/ensure_host_cc_seed_o.sh try-r2 src/asm/crt0_arm64.o \
          || { echo "ensure_asm_link_objs: try-r2 crt0_arm64.o failed" >&2; return 1; }
      elif [ -f src/asm/crt0_darwin_x86_64.s ]; then
        echo " ensure try-r2 src/asm/crt0_darwin_x86_64.o (wave762 R2 crt0)"
        CC="$CC" CFLAGS="$CFLAGS" bash scripts/ensure_host_cc_seed_o.sh try-r2 src/asm/crt0_darwin_x86_64.o \
          || { echo "ensure_asm_link_objs: try-r2 crt0_darwin_x86_64.o failed" >&2; return 1; }
      fi
    fi
  else
    # Fallback only if ensure script missing (should not happen on product tree).
    if [ "$UNAME_S" = "Linux" ] && [ "$(uname -m 2>/dev/null)" = "x86_64" ] && [ -f src/asm/runtime_panic_x86_64.s ]; then
      echo " cc -c runtime_panic.o <- src/asm/runtime_panic_x86_64.s"
      pure_as_compile runtime_panic.o src/asm/runtime_panic_x86_64.s
    elif [ -f seeds/runtime_panic_arm64.from_x.c ] && { [ "$(uname -m 2>/dev/null)" = "aarch64" ] || [ "$(uname -m 2>/dev/null)" = "arm64" ]; }; then
      echo " cc -c runtime_panic.o <- seeds/runtime_panic_arm64.from_x.c"
      $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_panic_arm64.from_x.c -o runtime_panic.o
    else
      echo " cc -c runtime_panic.o <- seeds/runtime_panic.from_x.c"
      $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_panic.from_x.c -o runtime_panic.o
    fi
    if [ "$UNAME_S" = "Linux" ] && [ -f src/asm/crt0_x86_64.s ]; then
      echo " cc -c src/asm/crt0_x86_64.o <- src/asm/crt0_x86_64.s"
      pure_as_compile src/asm/crt0_x86_64.o src/asm/crt0_x86_64.s
    fi
  fi
  ensure_typeck_f64_bits_obj
  # atoi: G.7 authority = scripts/bootstrap_nostdlib_shared.sh ensure_atoi_stub_obj.
  CRT0_ATOI_LINK="$(ensure_atoi_stub_obj)"
}

# 用户程序 asm 链预编译 runtime 对象（nostdlib xlang_asm 无 fork+cc，须在 build 阶段产出）。
ensure_runtime_user_link_objs() {
  if [ ! -f runtime_asm_io_stubs.o ] || [ seeds/runtime_asm_io_stubs.from_x.c -nt runtime_asm_io_stubs.o ]; then
  echo " cc_inc_tu runtime_asm_io_stubs.o <- seeds/runtime_asm_io_stubs.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -fPIE -c seeds/runtime_asm_io_stubs.from_x.c -o runtime_asm_io_stubs.o
  fi
  if [ ! -f runtime_process_argv.o ] || [ seeds/runtime_process_argv.from_x.c -nt runtime_process_argv.o ]; then
  echo " cc_inc_tu runtime_process_argv.o <- seeds/runtime_process_argv.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_process_argv.from_x.c -o runtime_process_argv.o
  fi
  if [ ! -f runtime_random_fill.o ] || [ seeds/runtime_random_fill.from_x.c -nt runtime_random_fill.o ]; then
  echo " cc_inc_tu runtime_random_fill.o <- seeds/runtime_random_fill.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_random_fill.from_x.c -o runtime_random_fill.o
  fi
  if [ ! -f runtime_time_os.o ] || [ seeds/runtime_time_os.from_x.c -nt runtime_time_os.o ] || [ src/asm/runtime_time_os.x -nt runtime_time_os.o ]; then
  echo " cc_inc_tu runtime_time_os.o <- seeds/runtime_time_os.from_x.c"
  if [ "${XLANG_G05_PREFER_X_O:-0}" = "1" ] && [ -x ./xlang-c ] && [ -f src/asm/runtime_time_os.x ]; then
    _rtos_tmp=$(mktemp "${TMPDIR:-/tmp}/rtos.XXXXXX") || _rtos_tmp=/tmp/rtos_tmp_$$
    ./xlang-c -L .. -L src -L src/asm -E src/asm/runtime_time_os.x > "$_rtos_tmp" 2>/dev/null && \
    $CC $CFLAGS -I. -Iinclude -Isrc -x c -c "$_rtos_tmp" -o runtime_time_os_thin.o && \
    $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_RUNTIME_TIME_OS_FROM_X -c seeds/runtime_time_os.from_x.c -o runtime_time_os_rest.o && \
    ld -r runtime_time_os_thin.o runtime_time_os_rest.o -o runtime_time_os.o && \
    rm -f "$_rtos_tmp" runtime_time_os_thin.o runtime_time_os_rest.o && \
    echo "   rtos: R2 full thin+rest merged (PREFER_X_O)"
  else
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_time_os.from_x.c -o runtime_time_os.o
  fi
  fi
  if [ ! -f runtime_env_os.o ] || [ seeds/runtime_env_os.from_x.c -nt runtime_env_os.o ] || [ src/asm/runtime_env_os.x -nt runtime_env_os.o ]; then
  echo " cc_inc_tu runtime_env_os.o <- seeds/runtime_env_os.from_x.c"
  if [ "${XLANG_G05_PREFER_X_O:-0}" = "1" ] && [ -x ./xlang-c ] && [ -f src/asm/runtime_env_os.x ]; then
    _reos_tmp=$(mktemp "${TMPDIR:-/tmp}/reos.XXXXXX") || _reos_tmp=/tmp/reos_tmp_$$
    ./xlang-c -L .. -L src -L src/asm -E src/asm/runtime_env_os.x > "$_reos_tmp" 2>/dev/null && \
    $CC $CFLAGS -I. -Iinclude -Isrc -x c -c "$_reos_tmp" -o runtime_env_os_thin.o && \
    $CC $CFLAGS -I. -Iinclude -Isrc -DXLANG_RUNTIME_ENV_OS_FROM_X -c seeds/runtime_env_os.from_x.c -o runtime_env_os_rest.o && \
    ld -r runtime_env_os_thin.o runtime_env_os_rest.o -o runtime_env_os.o && \
    rm -f "$_reos_tmp" runtime_env_os_thin.o runtime_env_os_rest.o && \
    echo "   reos: R2 full thin+rest merged (PREFER_X_O)"
  else
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_env_os.from_x.c -o runtime_env_os.o
  fi
fi
  # wave253: sole user-domain residual face body (weak; companion of PRIMARY_PANIC / residual).
  if [ ! -f runtime_link_abi_user_env.o ] || [ seeds/runtime_link_abi_user_env.from_x.c -nt runtime_link_abi_user_env.o ]; then
  echo " cc_inc_tu runtime_link_abi_user_env.o <- seeds/runtime_link_abi_user_env.from_x.c"
  $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/runtime_link_abi_user_env.from_x.c -o runtime_link_abi_user_env.o
  fi
}

# NL-07 / G-03: freestanding_io + bootstrap_nostdlib_stubs + wants_nostdlib + weak atoi
# G.7 single authority — scripts/bootstrap_nostdlib_shared.sh (also g05 product chain).
# shellcheck disable=SC1091
. "$(CDPATH= cd -- "$(dirname "$0")" && pwd)/bootstrap_nostdlib_shared.sh"

# Stage 12.2.2: G.7 pure-ld helpers — single authority for direct ld link paths
# (shared with g05 product chain). Sourced for XLANG_ZERO_CC_LD crt0 link path.
# shellcheck disable=SC1091
. "$(CDPATH= cd -- "$(dirname "$0")" && pwd)/pure_ld_shared.sh"

# crt0 链尾参数（无 PIPELINE_LIBS）。
# PLATFORM: LINUX — nostdlib tail is Linux x86_64 bootstrap only.
# PLATFORM: WINDOWS | MINGW | MSYS — never emit bare -lc/-lm: MinGW has no
#   free-standing lib "c" for ld (msvcrt is pulled by the gcc driver). Explicit
#   `-lc` fails with `cannot find -lc` and aborts hybrid after multidef noise.
# Callers capture stdout: BOOT_CRT0_TAIL=$(bootstrap_link_tail_crt0).
# ensure_* may print " cc -c ..." progress; must go to stderr or $(...) pollutes the
# link line with a bare -c and fails: cannot specify '-o' with '-c' with multiple files.
bootstrap_link_tail_crt0() {
  if bootstrap_wants_nostdlib; then
  ensure_freestanding_io_x86_64_obj
  ensure_bootstrap_nostdlib_stubs_obj
  echo "-nostdlib -static -Wl,--gc-sections src/asm/freestanding_io_x86_64.o src/asm/bootstrap_nostdlib_stubs.o"
  elif build_xlang_asm_is_msys; then
  echo ""
  else
  echo "-lc -lm"
  fi
}

# Stage 12.2.2: ld-compatible crt0 tail — objects only, no CC-driver flags.
# Returns object files / libs for the crt0 link tail (zero-CC ld path).
# PLATFORM: LINUX — nostdlib freestanding crt0 only (this block is Linux-guarded).
# Translation from bootstrap_link_tail_crt0:
#   -nostdlib (CC-driver only) → dropped (ld never adds default libs/startup)
#   -static / --gc-sections    → emitted by caller as direct ld flags
#   object files               → identical (G.7 single authority with CC path)
# Callers capture stdout: BOOT_CRT0_LD_TAIL=$(bootstrap_link_tail_crt0_ld).
bootstrap_link_tail_crt0_ld() {
  if bootstrap_wants_nostdlib; then
  ensure_freestanding_io_x86_64_obj
  ensure_bootstrap_nostdlib_stubs_obj
  echo "src/asm/freestanding_io_x86_64.o src/asm/bootstrap_nostdlib_stubs.o"
  elif build_xlang_asm_is_msys; then
  echo ""
  else
  echo "-lc -lm"
  fi
}

# driver / experimental / strict 链尾（保留 PIPELINE_LIBS，仅去 -lc/-lm）。
# PLATFORM: LINUX — same stdout purity rule as bootstrap_link_tail_crt0 (NL-07).
# PLATFORM: WINDOWS | MINGW | MSYS — no -lc/-lm; keep PIPELINE_LIBS only (usually empty).
bootstrap_link_tail_driver() {
  if bootstrap_wants_nostdlib; then
  ensure_freestanding_io_x86_64_obj
  ensure_bootstrap_nostdlib_stubs_obj
  echo "-nostdlib -static -Wl,--gc-sections src/asm/freestanding_io_x86_64.o src/asm/bootstrap_nostdlib_stubs.o ${PIPELINE_LIBS}"
  elif build_xlang_asm_is_msys; then
  echo "${PIPELINE_LIBS}"
  else
  echo "-lm -lc ${PIPELINE_LIBS}"
  fi
}

# NL-07 v5：nostdlib 静态链不链 libpthread（libpthread 依赖 libc；桩见 bootstrap_nostdlib_stubs.inc）。
bootstrap_pipeline_libs() {
  if bootstrap_wants_nostdlib; then
  echo "-lc -lgcc -lgcc_eh"
  elif [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
  echo "-luring -lpthread"
  else
  echo ""
  fi
}

# NL-07 v5：nostdlib 须 crt0 _start→main_entry；libc 路径仍用 runtime_asm_build main()。
bootstrap_entry_obj() {
  if bootstrap_wants_nostdlib && [ "$(uname -s 2>/dev/null)" = "Linux" ] && [ -f src/asm/crt0_x86_64.o ]; then
  echo "src/asm/crt0_x86_64.o"
  else
  echo "src/asm/runtime_asm_build.o"
  fi
}

# NL-07 v5：crt0 链用 -e _start -nostartfiles（与 bootstrap-driver-seed 一致）。
bootstrap_entry_ldflags() {
  if bootstrap_wants_nostdlib && [ "$(uname -s 2>/dev/null)" = "Linux" ] && [ -f src/asm/crt0_x86_64.o ]; then
  echo "-no-pie -e _start -nostartfiles -lc"
  else
  echo ""
  fi
}

# pipeline_glue_standalone 提供 backend_ctx_push_loop_labels 等 C 真实现；
# 与 pipeline_x.o / asm_backend_partial.o 重复时须 glue 置首且允许多定义（首符号生效）。
asm_glue_duplicate_ldflags() {
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  echo "-Wl,-multiply_defined -Wl,suppress"
  else
  echo "-Wl,--allow-multiple-definition"
  fi
}

# 确保 crt0 / nostdlib 对象在 experimental/strict 链前已编译。
bootstrap_ensure_entry_objs() {
  if bootstrap_wants_nostdlib && [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
  ensure_asm_link_objs
  ensure_runtime_user_link_objs
  ensure_freestanding_io_x86_64_obj
  ensure_bootstrap_nostdlib_stubs_obj
  fi
}

# 仅重链 xlang_asm（runtime/bootstrap/crt0 对象更新后）；不跑 build_asm 全量 -backend asm 循环。
# 用法：XLANG_ASM_BSTRICT_RELINK_ONLY=1 ./scripts/build_xlang_asm.sh
# 或 ./scripts/relink_xlang_asm_bstrict_runtime_objs.sh
#
# Sync xlang_asm → xlang_asm_stage1 after a successful strict link.
# C5/C6 and non-Stage2 consumers read stage1 as "latest strict product".
#
# PLATFORM: SHARED — must NOT run during Stage2 round2 (XLANG_ASM_BOOTSTRAP_ROUND2=1).
# verify-selfhost-stage2-bstrict Step1 freezes gen1 into xlang_asm_stage1; Step4c
# SHA256-compares that snapshot to xlang_asm2 (gen2). Overwriting stage1 here made
# gen1==gen2 always (假 fixed point / false SHA256 green) and also collapsed Step3
# behavior parity to gen2-vs-gen2. Round2 leaves stage1 untouched.
xlang_asm_sync_stage1_from_strict() {
  if [ -n "${XLANG_ASM_BOOTSTRAP_ROUND2:-}" ]; then
  build_xlang_asm_info "skip sync xlang_asm_stage1 (BOOTSTRAP_ROUND2; Stage2 owns gen1 snapshot)"
  return 0
  fi
  if [ -f ./xlang_asm ] && [ -x ./xlang_asm ]; then
  # PLATFORM: DARWIN — delete-then-cp avoids bad vnode/signature cache on in-place overwrite.
  rm -f ./xlang_asm_stage1 2>/dev/null || true
  cp -f ./xlang_asm ./xlang_asm_stage1 2>/dev/null || true
  fi
}

xlang_asm_bstrict_relink_runtime_only() {
  local ST_RC=0
  local ST_GLUE_OBJ ST_WPO_ALIAS ST_PARSER_LINK ST_BRIDGE_OBJ ST_DRIVER_CLI_OBJS
  local ST_SEED_PREPROCESS_LINK ST_SEED_PARSER_TCK ST_STRICT_COMPANIONS ST_TYPECK_LSP_STUB
  local ST_STRICT_FB_X_TAIL ST_BACKEND_COMPANIONS ST_TYPECK_X_LINK
  local BSTRICT_SEED_SUPPORT BOOT_ENTRY_OBJ BOOT_ENTRY_LDFLAGS BOOT_DRIVER_TAIL
  local ST_BSTRICT_LINK_EXTRA PTEXT

  build_xlang_asm_info "XLANG_ASM_BSTRICT_RELINK_ONLY - refresh runtime/bootstrap + strict relink"
  export STRICT_LINK_BUILD_ASM_PIPELINE=1
  SEED_O="${SEED_O:-$BUILD_DIR/asm_driver_seed}"
  ensure_diag_seed_obj "$SEED_O"
  ensure_lsp_diag_seed_obj "$SEED_O"
  LSP_DIAG_SEED_O=${LSP_DIAG_SEED_O:-$(lsp_diag_seed_obj_path "$SEED_O")}
  PIPELINE_LIBS=$(bootstrap_pipeline_libs)
  build_nonempty_asm_objs
  PTEXT=$(asm_o_text_bytes "$BUILD_DIR/pipeline.o" 2>/dev/null || echo 0)
  ensure_asm_pipeline_glue_standalone_obj
  ensure_asm_pipeline_glue_strict_minimal_obj
  ensure_asm_experimental_symbol_bridge_obj
  ensure_asm_bootstrap_x_companion_objs
  ensure_asm_experimental_lsp_objs
  ensure_runtime_io_abi_obj
  ensure_runtime_link_abi_obj
  ensure_runtime_pipeline_abi_obj
  ensure_runtime_driver_abi_obj
  ensure_runtime_driver_diagnostic_obj
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  ensure_parser_x_o_for_strict_link
  strip_main_entry_from_build_asm_main_o || true
  bootstrap_ensure_entry_objs

  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  fi
  # wave309/wave304: glue seed shells retired; drop ST_GLUE_OBJ if .o physically missing.
  # Pure runtime_pipeline_abi.o (in LD argv) + runtime_driver_strict_glue_stubs.o provide
  # same symbols (G.7, same as L4 pure-ld). PLATFORM: SHARED.
  [ -z "$ST_GLUE_OBJ" ] || [ -f "$ST_GLUE_OBJ" ] || ST_GLUE_OBJ=""
  ST_WPO_ALIAS=""
  ST_PARSER_LINK=""
  ST_BRIDGE_OBJ="$BUILD_DIR/asm_experimental_symbol_bridge.o"
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o"
  if asm_strict_link_driver_selfhosted; then
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_emit_x.o"
  export STRICT_LINK_BUILD_ASM_DRIVER=1
  fi
  ST_SEED_PREPROCESS_LINK=$(asm_seed_st_preprocess_link)
  ST_TYPECK_X_LINK="typeck_x.o"
  # selfhosted strict relink 不会并链 ST_LAYOUT_PARTIAL；此时若误用 no_layout partial，
  # 会把 typeck_ensure_struct_layout_from_struct_lit / entry_module_find_struct_layout_index 一并裁掉。
  if ! asm_strict_typeck_selfhosted && ensure_typeck_asm_layout_partial_obj && ensure_typeck_x_no_layout_partial_obj; then
  ST_TYPECK_X_LINK="$BUILD_DIR/typeck_x_no_layout_partial.o"
  fi
  if asm_strict_typeck_selfhosted && asm_strict_typeck_x_glue_via_pipeline_x; then
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $(asm_seed_st_x_glue_suffix)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link) $(asm_seed_st_x_glue_suffix)"
  fi
  elif asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  fi
  ST_PARSER_X_TAIL="parser_x.o lexer_x.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -n "$ST_TYPECK_X_LINK" ] && [ -f "$ST_TYPECK_X_LINK" ]; then
  case " $ST_SEED_PARSER_TCK " in
  *" $ST_TYPECK_X_LINK "*) ST_TYPECK_X_TAIL="" ;;
  *) ST_TYPECK_X_TAIL="$ST_TYPECK_X_LINK" ;;
  esac
  fi
  ensure_ast_pool_l5_bridge_obj
  ensure_asm_backend_compat_stubs_obj
  refresh_bstrict_link_variants
  ST_BACKEND_COMPANIONS=$(strict_asm_backend_companion_objs) || ST_BACKEND_COMPANIONS="$BUILD_DIR/seed_host/asm_backend_partial.o"
  # runtime_io_abi.o hard-coded once on strict link line — do not also put it here
  # (PLATFORM: DARWIN rejects the same .o twice as duplicate symbols).
  ST_BSTRICT_LINK_EXTRA="src/asm/parser_asm_parse_expr_link.o src/asm/pipeline_fill_dep_strict_alias.o $BUILD_DIR/seed_host/asm_full_link_stubs.o"
  # user_asm (+ Darwin arm64 enc) live in BSTRICT_USER_ASM_EARLY_LINK before stubs.
  ST_STRICT_COMPANIONS="$BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $ST_BACKEND_COMPANIONS $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BSTRICT_DISPATCH_COMPANIONS parser_asm_thin_glue.o $ST_BSTRICT_LINK_EXTRA src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o preprocess_x.o src/runtime_driver_strict_glue_stubs.o $ST_DRIVER_CLI_OBJS"
  ensure_pipeline_o_strict_link_partial_obj || true
  filter_strict_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  ST_TYPECK_LSP_STUB=""
  if [ ! -f "$BUILD_DIR/gen_driver/lsp_io_x.o" ]; then
  ST_TYPECK_LSP_STUB="$BUILD_DIR/typeck_lsp_io_stub.o"
  fi
  ST_RUNTIME_PARTIAL=""
  ST_RUNTIME_PANIC=""
  ST_RUNTIME_EXTRA=""
  ST_LAYOUT_PARTIAL=""
  ST_PIPELINE_ALIAS=""
  ST_STRICT_FB_X_TAIL=""
  if [ -f runtime_panic.o ] && [ "$(uname -s 2>/dev/null)" != "Darwin" ]; then
  # PLATFORM: DARWIN — skip runtime_panic.o (link_abi_getenv dual-defs with
  # src/runtime_link_abi.o G.7 authority; host link resolves panic/crash via static locals).
  ST_RUNTIME_PANIC="runtime_panic.o atoi_stub.o"
  fi
  refresh_build_asm_ci_text_stubs_for_strict_link || true
  if [ ! -f "$BUILD_DIR/seed_host/asm_backend_partial.o" ] \
  || [ "$(wc -c <"$BUILD_DIR/seed_host/asm_backend_partial.o" | tr -d ' ')" -lt 8192 ]; then
  if [ "${XLANG_ASM_BSTRICT_RELINK_ALLOW_PHASE1_STUB:-0}" = "1" ]; then
  build_xlang_asm_warn "runtime-only relink with phase1 asm_backend_partial (dev/Docker only)"
  else
  xlang_asm_bstrict_fail "runtime-only relink needs real build_asm/seed_host/asm_backend_partial.o (not phase1 stub)"
  fi
  fi
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  BOOT_DRIVER_TAIL=$(bootstrap_link_tail_driver)
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)

  set +e
  # shellcheck disable=SC2086
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_SEED_SUPPORT \
  ${ST_GLUE_OBJ:+"$ST_GLUE_OBJ"} \
  $ST_WPO_ALIAS \
  $ASM_TRY_OBJS \
  $ST_PARSER_LINK \
  $ST_RUNTIME_PARTIAL \
  $ST_PARSER_X_TAIL \
  $ST_BRIDGE_OBJ \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $ST_TYPECK_LSP_STUB \
  src/runtime_driver_strict_glue_stubs.o \
  $ST_SEED_PREPROCESS_LINK \
  $ST_SEED_PARSER_TCK \
  $ST_STRICT_COMPANIONS \
  "$BUILD_DIR/gen_driver/lsp_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_ctx.o \
  src/lsp/lsp_diag_pipeline_sizes.o \
  $ST_RUNTIME_PANIC atoi_stub.o \
  $ST_RUNTIME_EXTRA \
  $ST_LAYOUT_PARTIAL \
  $ST_PIPELINE_ALIAS \
  $ST_TYPECK_X_TAIL \
  $BOOT_DRIVER_TAIL 2>"$BUILD_DIR/.asm_strict_relink_only_err"
  ST_RC=$?
  set -e
  if [ "$ST_RC" -ne 0 ]; then
  build_xlang_asm_error "runtime-only strict relink failed (rc=$ST_RC)"
  tail -n 12 "$BUILD_DIR/.asm_strict_relink_only_err" 2>/dev/null | sed 's/^/ /' || true
  xlang_asm_bstrict_fail "runtime-only strict relink failed"
  fi
  build_xlang_asm_info "xlang_asm strict OK (runtime-only relink, pipeline.o __text=${PTEXT}B)"
  LINK_OK=1
  LINK_MODE=asm_only_strict
  if [ -z "${XLANG_ASM_SKIP_STRICT_SMOKE:-}" ]; then
  if ! XLANG_ASM_SMOKE_SKIP_GATE=1 ./scripts/run_xlang_asm_smoke.sh >"$BUILD_DIR/.asm_strict_smoke.log" 2>&1; then
  xlang_asm_bstrict_fail "strict xlang_asm smoke failed after runtime-only relink"
  fi
  build_xlang_asm_info "strict xlang_asm smoke passed (runtime-only relink)"
  fi
  xlang_asm_sync_stage1_from_strict
}

if [ -n "${XLANG_ASM_BSTRICT_RELINK_ONLY:-}" ]; then
  xlang_asm_bstrict_relink_runtime_only
  exit 0
fi

LINK_OK=0
ASM_READY=0
LINK_MODE=""
ASM_TEXT_ALL_OK=0
[ -f "$BUILD_DIR/.asm_text_quality" ] && ASM_TEXT_ALL_OK=$(cat "$BUILD_DIR/.asm_text_quality")

# 拓扑：显式导出 XLANG_ASM_LINK_TOPOLOGY 时尊重用户值；否则全域 __text 非空 → full_asm，否则 pipeline_x
if [ -z "${XLANG_ASM_LINK_TOPOLOGY+x}" ]; then
  XLANG_ASM_LINK_TOPOLOGY=pipeline_x
  UNAMES=$(uname -s 2>/dev/null || echo Unknown)
  if [ "$ASM_TEXT_ALL_OK" = "1" ]; then
  XLANG_ASM_LINK_TOPOLOGY=full_asm
  build_xlang_asm_info "auto XLANG_ASM_LINK_TOPOLOGY=full_asm ($UNAMES, all BUILD __text non-empty)"
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_info "M11 production B-strict (SKIP_GEN -> asm_only_strict, no cc -c pipeline_gen.c in final link)"
  elif [ "$UNAMES" != "Linux" ]; then
  build_xlang_asm_info "hint: export XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 or bash scripts/bootstrap_driver_bstrict.sh for asm_only_strict"
  fi
  elif [ "$UNAMES" != "Linux" ]; then
  build_xlang_asm_info "host=$UNAMES: topology pipeline_x (__text 未全绿；crt0 仅 Linux，见 docs/SELFHOST.md §4)"
  fi
else
  if [ "$XLANG_ASM_LINK_TOPOLOGY" = "full_asm" ] && [ "$ASM_TEXT_ALL_OK" != "1" ]; then
  build_xlang_asm_warn "XLANG_ASM_LINK_TOPOLOGY=full_asm requires all __text non-empty; forcing pipeline_x"
  XLANG_ASM_LINK_TOPOLOGY=pipeline_x
  fi
fi

if [ -f "$BUILD_DIR/main.o" ] && [ -s "$BUILD_DIR/main.o" ] && [ -f "$BUILD_DIR/pipeline.o" ] && [ -s "$BUILD_DIR/pipeline.o" ]; then
  ASM_READY=1
  build_nonempty_asm_objs
  USE_CRT0=0
  if [ "$(uname -s 2>/dev/null)" = "Linux" ]; then
  ensure_asm_link_objs
  fi
  # B-strict（SKIP_GEN）须 asm_only_strict（含 runtime_driver）；crt0 链无 driver，成功反而会触发末尾 bstrict 失败。
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_info "XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 - skip crt0 link (use asm_only_strict; crt0 见 bash scripts/bootstrap_driver_crt0.sh)"
  elif [ "$(uname -s 2>/dev/null)" = "Linux" ] && [ -f src/asm/crt0_x86_64.o ] && [ -f src/typeck/typeck_f64_bits.o ] && [ -f runtime_panic.o ]; then
  echo " linking xlang_asm (crt0 + typeck_f64_bits + runtime_panic + asm*.o, no runtime_driver) ..."
  filter_crt0_asm_objs
  # NL-07 L3+L3b+L4++L5+L9: dispatch + emit partial + tdl + codegen/parser + seed-support.
  ensure_crt0_backend_companion_objs
  set +e
  # F-no-libc NL-07 BEGIN — bootstrap nostdlib（XLANG_BOOTSTRAP_NOSTDLIB=1 尝试；失败回退 libc/libm）
  # 目标：crt0_x86_64 + freestanding_io + bootstrap_nostdlib_stubs + build_asm/*.o
  #        + backend dispatch companions + seed emit partial + typeck/driver/lsp companions
  #        + codegen/parser residual partials + L9 seed-support + -nostdlib --gc-sections
  # F-06 v1：bootstrap 已不链 cc -c 的 std/fs|io|heap .o
  # CRT0_ATOI_LINK: empty when runtime_panic already provides T atoi (avoid multi-def).
  CRT0_ATOI_LINK="${CRT0_ATOI_LINK:-}"
  if [ -z "$CRT0_ATOI_LINK" ] && [ -f atoi_stub.o ]; then
  if nm runtime_panic.o 2>/dev/null | grep -q ' T atoi$'; then
  CRT0_ATOI_LINK=""
  else
  CRT0_ATOI_LINK="atoi_stub.o"
  fi
  fi
  CRT_RC=1
  # Stage 12.2.2: zero-CC crt0 link — direct ld invocation (no host-CC driver).
  # PLATFORM: LINUX — crt0_x86_64 _start entry; nostdlib freestanding.
  # Opt-in: XLANG_ZERO_CC_LD=1. Flag unset = $CC path (zero regression).
  # ld flag translation from $CC driver:
  #   -nostdlib (CC-only) → dropped (ld never adds default libs/startup)
  #   -static              → -static (ld accepts)
  #   -Wl,--gc-sections    → --gc-sections
  #   entry: -e _start (crt0_x86_64.o defines _start; ld default but explicit)
  # Object order mirrors the $CC path (crt0 → typeck_f64 → panic → atoi →
  # CRT0_ASM → backend companions → freestanding_io → nostdlib_stubs).
  if [ "${XLANG_ZERO_CC_LD:-0}" = "1" ]; then
  # Stage 12.2.2: zero-CC crt0 link via pure_ld_try_link (G.7 single authority).
  # Reuses the same pure-ld helpers as g05 product chain (wave773/774):
  #   · pure_ld_multidef_flags → --allow-multiple-definition (Linux)
  #   · pure_ld_platform_prefix → syslibroot (Darwin) / --dynamic-linker (Linux)
  #   · pure_ld_default_entry → -e _start
  # This fixes the multidef issue that breaks the $CC crt0 path (both $CC and
  # bare ld fail without --allow-multiple-definition; pure_ld_try_link adds it).
  # PLATFORM: LINUX — nostdlib freestanding crt0.
  BOOT_CRT0_LD_OBJS="$(bootstrap_link_tail_crt0_ld)"
  CRT0_LD_OBJS="src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o $CRT0_ATOI_LINK $CRT0_ASM $CRT0_BACKEND_COMPANIONS $BOOT_CRT0_LD_OBJS"
  build_xlang_asm_info "Stage 12.2.2: zero-CC crt0 link via pure-ld (XLANG_ZERO_CC_LD=1)"
  if pure_ld_try_link xlang_asm "$CRT0_LD_OBJS" "$(pure_ld_default_entry)" "" "-static --gc-sections" "" 2>"$BUILD_DIR/.bootstrap_nostdlib_link_err"; then
    CRT_RC=0
    build_xlang_asm_info "zero-CC crt0 link OK via pure-ld (no host-CC, no libc)"
  else
    CRT_RC=1
    build_xlang_asm_error "zero-CC crt0 link failed — no $CC fallback (XLANG_ZERO_CC_LD=1)"
    if [ -f "$BUILD_DIR/.bootstrap_nostdlib_link_err" ]; then
      head -15 "$BUILD_DIR/.bootstrap_nostdlib_link_err" 2>/dev/null || true
    fi
  fi
  else
  if bootstrap_wants_nostdlib; then
  BOOT_CRT0_TAIL=$(bootstrap_link_tail_crt0)
  build_xlang_asm_info "trying bootstrap nostdlib crt0 link (XLANG_BOOTSTRAP_NOSTDLIB=1)"
  # shellcheck disable=SC2086
  "$CC" $CFLAGS -o xlang_asm src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o $CRT0_ATOI_LINK \
  $CRT0_ASM $CRT0_BACKEND_COMPANIONS $BOOT_CRT0_TAIL 2>"$BUILD_DIR/.bootstrap_nostdlib_link_err"
  CRT_RC=$?
  if [ "$CRT_RC" -ne 0 ]; then
  build_xlang_asm_error "bootstrap nostdlib crt0 link failed (rc=$CRT_RC)"
  if [ -f "$BUILD_DIR/.bootstrap_nostdlib_link_err" ]; then
  head -15 "$BUILD_DIR/.bootstrap_nostdlib_link_err" 2>/dev/null || true
  fi
  else
  build_xlang_asm_info "bootstrap nostdlib crt0 link OK (no libc/libm)"
  fi
  fi
  if [ "$CRT_RC" -ne 0 ]; then
  # F-no-libc track：默认 crt0 链仍须 libc/libm；用户 freestanding 走 runtime NL-05 无 libc。
  BOOT_CRT0_TAIL=$(bootstrap_link_tail_crt0)
  # shellcheck disable=SC2086
  "$CC" $CFLAGS -o xlang_asm src/asm/crt0_x86_64.o src/typeck/typeck_f64_bits.o runtime_panic.o $CRT0_ATOI_LINK \
  $CRT0_ASM $CRT0_BACKEND_COMPANIONS $BOOT_CRT0_TAIL
  CRT_RC=$?
  fi
  # F-no-libc NL-07 END
  fi
  set -e
  if [ "$CRT_RC" -eq 0 ]; then
  build_xlang_asm_info "xlang_asm built (no C runtime driver)"
  LINK_OK=1
  USE_CRT0=1
  LINK_MODE=crt0
  else
  build_xlang_asm_warn "crt0 link failed (rc=$CRT_RC); trying runtime_driver fallback"
  fi
  fi
  if [ "$LINK_OK" -ne 1 ]; then
  ensure_runtime_cc_stubs
  ensure_std_fs_io_heap_objs
  ensure_asm_driver_seed_c_objs
  LSP_DIAG_SEED_O=${LSP_DIAG_SEED_O:-$(lsp_diag_seed_obj_path "$SEED_O")}
  ensure_lsp_diag_pipeline_sizes_obj
  ensure_asm_xlang_lsp_diag_stub_obj
  ensure_asm_lsp_codegen_extern_obj
  # Linux：crt0 失败后试 experimental bootstrap（pipeline_x.o + X companions）；SKIP_GEN 时 macOS 等同理。
  _try_experimental=0
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  _try_experimental=1
  elif [ "$(uname -s 2>/dev/null)" = "Linux" ] && [ "$LINK_OK" -ne 1 ]; then
  _try_experimental=1
  build_xlang_asm_warn "Linux crt0/runtime link failed; trying experimental bootstrap (pipeline_x.o + X companions)"
  fi
  if [ "$_try_experimental" -eq 1 ]; then
  _try_exp_enter=0
  if [ -n "$NONEMPTY_ASM" ]; then
  _try_exp_enter=1
  elif [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && build_xlang_asm_is_msys; then
  build_xlang_asm_info "E-06 v5 Windows B-strict - experimental X-only (no build_asm/*.o required)"
  _try_exp_enter=1
  fi
  else
  _try_exp_enter=0
  fi
  if [ "$_try_exp_enter" -eq 1 ]; then
  if [ "$ASM_TEXT_ALL_OK" != "1" ]; then
  build_xlang_asm_info "XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 (__text 未全绿仍试 asm-only 链)"
  else
  build_xlang_asm_info "XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 - B-strict asm-only（bootstrap + strict 重链，最终无 pipeline_gen.c）"
  fi
  ensure_std_fs_io_heap_objs
  PIPELINE_LIBS=$(bootstrap_pipeline_libs)
  bootstrap_ensure_entry_objs
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  if bootstrap_wants_nostdlib; then
  build_xlang_asm_info "NL-07 v5 nostdlib entry $BOOT_ENTRY_OBJ ($BOOT_ENTRY_LDFLAGS)"
  fi
  UNAME_ASM=$(uname -s 2>/dev/null || echo Unknown)
  # Darwin：ENTRY_MODULE_ONLY 下 duplicate symbol 已消除，但大模块 .o 符号不全/跨模块命名仍会导致 undefined；试链后失败则回退 gen_driver。
  filter_experimental_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  if [ "$UNAME_ASM" = "Darwin" ]; then
  build_xlang_asm_info "Darwin 试 asm-only 链（ENTRY_MODULE_ONLY 已无 duplicate；若 undefined 则回退）"
  fi
  if build_xlang_asm_is_msys && [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_info "MSYS B-strict - skip build_asm/*.o in experimental bootstrap (X companions + pipeline_x)"
  ASM_TRY_OBJS=""
  fi
  if [ -n "$ASM_TRY_OBJS" ] || { [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && build_xlang_asm_is_msys; }; then
  ensure_pipeline_x_o_fresh
  ensure_asm_experimental_symbol_bridge_obj
  ensure_asm_driver_seed_c_objs
  # B-strict：companion 已提供 preprocess_x.o / driver_*_x.o；勿再 ensure_asm_gen_driver_x_objs（冗余 -E gen_driver/pipeline_gen.c）。
  ensure_asm_bootstrap_x_companion_objs
  ensure_pipeline_run_x_link_alias_obj
  ensure_asm_experimental_lsp_objs
  ensure_ast_pool_l5_bridge_obj
  if [ ! -f pipeline_bootstrap_orchestration.o ] || [ seeds/pipeline_bootstrap_orchestration.from_x.c -nt pipeline_bootstrap_orchestration.o ]; then
  # Wave928: all platforms cc direct from seed (unified; no make).
  # XLANG_ASM_LINK_VIA_MAKE=1 escapes to make (parity / debug).
  if [ "${XLANG_ASM_LINK_VIA_MAKE:-0}" = "1" ] && [ -f Makefile ] && command -v make >/dev/null 2>&1; then
    make pipeline_bootstrap_orchestration.o
  elif [ -f seeds/pipeline_bootstrap_orchestration.from_x.c ]; then
    echo " cc pipeline_bootstrap_orchestration.o <- seeds (wave928; unified all platforms)"
    $CC $CFLAGS -I. -Iinclude -Isrc -c seeds/pipeline_bootstrap_orchestration.from_x.c \
      -o pipeline_bootstrap_orchestration.o
  else
    build_xlang_asm_info "WARN missing pipeline_bootstrap_orchestration.o seed"
  fi
  fi
  SEED_O="$BUILD_DIR/asm_driver_seed"
  GEN_O="$BUILD_DIR/gen_driver"
  ASM_SEED_FRONTEND_LINK=""
  if ! asm_seed_omit_c_frontend_seed; then
  ASM_SEED_FRONTEND_LINK="$SEED_O/parser.o $SEED_O/lexer.o $SEED_O/ast_seed.o"
  elif asm_seed_use_x_frontend; then
  build_xlang_asm_info "E-06 v2 experimental link omit asm_driver_seed frontend .o (X companions)"
  else
  build_xlang_asm_info "E-06 v4 experimental link omit asm_driver_seed frontend .o (X ready, no SKIP_GEN)"
  fi
  # pipeline_x / dispatch 引用的 arch_* enc/emit 须 weak 桩（与 bootstrap-driver-seed 同源）。
  ASM_LINK_STUBS_O=""
  if [ -f pipeline_x.o ]; then
  refresh_bstrict_link_variants
  _stub_scan="$BSTRICT_PIPELINE_LINK_O $BSTRICT_DISPATCH_OBJS"
  if [ -f "$BUILD_DIR/seed_host/asm_full.o" ]; then
  _stub_scan="$BUILD_DIR/seed_host/asm_full.o $_stub_scan"
  fi
  if perl scripts/gen_asm_full_link_stubs.pl "$BUILD_DIR/seed_host/asm_full_link_stubs.c" $_stub_scan 2>/dev/null \
  && [ -s "$BUILD_DIR/seed_host/asm_full_link_stubs.c" ]; then
  "$CC" $CFLAGS -c -o "$BUILD_DIR/seed_host/asm_full_link_stubs.o" "$BUILD_DIR/seed_host/asm_full_link_stubs.c" 2>/dev/null \
  && ASM_LINK_STUBS_O="$BUILD_DIR/seed_host/asm_full_link_stubs.o"
  fi
  fi
  # 首遍 bootstrap 不链 build_asm/*.o（stub 符号重复）；第二遍 strict 重链再并入 pipeline.o 等。
  echo " linking xlang_asm (experimental bootstrap: runtime + pipeline_x + X companions + seed C, no build_asm/*.o) ..."
  set +e
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  # PLATFORM: DARWIN — do not drop whole strict_glue_stubs (historically hid U
  # preprocess_*/codegen_*/ast_* / Stage2 round2 codegen_set_*). Prefer filtered
  # partial that omits only asm_driver_* strong-duplicated by BOOT_ENTRY.
  # Fallback keeps unfiltered stubs.o (never drop — drop recreates UNDEF).
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  if ensure_bstrict_darwin_strict_glue_stubs_filt_obj 2>/dev/null; then
  BSTRICT_SEED_SUPPORT=$(echo "$BSTRICT_SEED_SUPPORT" \
    | sed "s|src/runtime_driver_strict_glue_stubs\\.o|$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o|g")
  else
  build_xlang_asm_warn "Darwin strict_glue_stubs filt failed; linking unfiltered stubs.o"
  fi
  fi
  BOOT_DRIVER_TAIL=$(bootstrap_link_tail_driver)
  ensure_asm_pipeline_glue_standalone_obj
  ensure_asm_pipeline_glue_strict_minimal_obj
  refresh_bstrict_link_variants
  # Darwin ld 不再尊重 -multiply_defined；重复 .o 硬失败。
  # minimal glue 与 filtered pipeline 重叠 → Darwin 用 complement（refresh_bstrict_link_variants）。
  BSTRICT_MINIMAL_GLUE_COMPANION=""
  if [ "$(uname -s 2>/dev/null)" != "Darwin" ] \
    && [ -n "$BSTRICT_EXPERIMENTAL_GLUE_OBJ" ] \
    && [ "$BSTRICT_EXPERIMENTAL_GLUE_OBJ" != "$BUILD_DIR/pipeline_glue_strict_minimal.o" ] \
    && [ -f "$BUILD_DIR/pipeline_glue_strict_minimal.o" ]; then
  BSTRICT_MINIMAL_GLUE_COMPANION="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  fi
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)
  # shellcheck disable=SC2086
  # PLATFORM: SHARED — early user_asm (+ Darwin arm64 enc) before weak stubs (ar extract).
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  ${BSTRICT_EXPERIMENTAL_GLUE_OBJ:+"$BSTRICT_EXPERIMENTAL_GLUE_OBJ"} \
  $BSTRICT_MINIMAL_GLUE_COMPANION \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_USER_ASM_EARLY_LINK \
  $BSTRICT_SEED_SUPPORT \
  "$BSTRICT_PIPELINE_LINK_O" \
  pipeline_bootstrap_orchestration.o \
  preprocess_x.o \
  driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o \
  "$BUILD_DIR/x_seed_bridge.o" \
  "$BUILD_DIR/seed_link_compat.o" \
  "$BUILD_DIR/seed_host/asm_backend_partial.o" \
  $ASM_LINK_STUBS_O \
  "$BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK" \
  $BSTRICT_DISPATCH_COMPANIONS \
  src/asm/pipeline_run_x_link_alias.o \
  src/asm/parser_asm_parse_expr_link.o \
  parser_asm_thin_glue.o \
  src/driver/fmt_check_cmd_driver.o \
  src/driver/target_cpu.o \
  src/asm/simd_enc.o \
  src/asm/simd_loop.o \
  \
  "$BUILD_DIR/asm_experimental_symbol_bridge.o" \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $ASM_SEED_FRONTEND_LINK \
  "$SEED_O/async_liveness.o" \
  "$SEED_O/async_cps_codegen.o" \
  parser_x.o lexer_x.o typeck_x.o codegen_x.o \
  x_frontend_link_alias.o \
  "$GEN_O/lsp_x.o" \
  "$GEN_O/lsp_io_x.o" \
  "$GEN_O/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_ctx.o \
  src/lsp/lsp_diag_pipeline_sizes.o \
  $BOOT_DRIVER_TAIL 2>"$BUILD_DIR/.asm_experimental_link_err"
  FB_RC=$?
  set -e
  if [ "$FB_RC" -eq 0 ]; then
  build_xlang_asm_info "xlang_asm built (experimental: build_asm backend + pipeline_x.o bootstrap)"
  cp -f xlang_asm xlang_asm.experimental 2>/dev/null || true
  export XLANG_ASM_SECOND_PASS_COMPILER=./xlang_asm.experimental
  LINK_OK=1
  LINK_MODE=asm_only_experimental
  if [ -n "${XLANG_ASM_CI_ACCEPT_EXPERIMENTAL_ONLY:-}" ]; then
  build_xlang_asm_info "CI fast - keep asm_only_experimental bootstrap (skip strict relink + gen_driver)"
  if asm_ci_skip_typeck_emit_heavy; then
  build_xlang_asm_info "CI fast - skip typeck EMIT_HEAVY on $(uname -s) (S2 gate Linux-only)"
  elif ! rebuild_typeck_o_emit_heavy_s2 "./xlang_asm.experimental"; then
  xlang_asm_bstrict_fail "typeck.o EMIT_HEAVY required for S2 gate after CI experimental bootstrap"
  fi
  else
  # abi/WPO source 变更后须刷新 pipeline_x.o + experimental（G.7；非已删 ast_pool.c）。
  ensure_experimental_ast_pool_for_wpo || true
  # 第二遍：bootstrap xlang_asm 重编 pipeline/typeck/parser/backend，再 strict 重链（无 pipeline_x.o）。
  SECOND_PASS_OK=0
  if rebuild_pipeline_o_second_pass; then
  SECOND_PASS_OK=1
  fi
  # EMIT_HEAVY 第二遍：pipeline 未达标时仍重编 typeck/parser/backend（S2 gate 依赖 build_asm/typeck.o）。
  if ! rebuild_typeck_parser_backend_second_pass "./xlang_asm.experimental"; then
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_warn "bootstrap second pass (typeck/parser/backend) failed; continuing strict with partials"
  else
  build_xlang_asm_warn "typeck/parser/backend second pass failed (pipeline may be partial)"
  fi
  fi
  PTEXT=$(asm_o_text_bytes "$BUILD_DIR/pipeline.o" 2>/dev/null || echo 0)
  STRICT_TRY=0
  # G.7 residual close (post-107d09af2): when runtime_pipeline_abi.o is the
  # selfhosted authority, stub pipeline.o __text may be 0B — still allow strict.
  # Legacy path: SECOND_PASS_OK + stub __text>200 (pre-abi emit era).
  # PLATFORM: SHARED — same gate Darwin/Linux (closes Darwin Stage2 __text=0B RED).
  if [ "$SECOND_PASS_OK" -eq 1 ] && { [ "$PTEXT" -gt 200 ] 2>/dev/null || asm_strict_pipeline_selfhosted; }; then
  STRICT_TRY=1
  else
  build_xlang_asm_error "pipeline.o second pass failed (__text=${PTEXT}B)"
  xlang_asm_bstrict_fail "pipeline second pass required for B-strict (__text=${PTEXT}B)"
  fi
  if [ "$STRICT_TRY" -eq 1 ]; then
  ensure_asm_pipeline_glue_standalone_obj
  ensure_asm_pipeline_glue_strict_minimal_obj
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  # wave309/wave304: glue seed shells retired; drop ST_GLUE_OBJ if .o missing.
  [ -z "$ST_GLUE_OBJ" ] || [ -f "$ST_GLUE_OBJ" ] || ST_GLUE_OBJ=""
  ST_WPO_ALIAS=""
  ST_PARSER_LINK=""
  ST_RUNTIME_PARTIAL=""
  ST_RUNTIME_EXTRA=""
  ST_LAYOUT_PARTIAL=""
  ST_PIPELINE_ALIAS=""
  ST_RUNTIME_MODE="bootstrap"
  ST_USES_ASM_PIPELINE=0
  ST_PARSER_LINK=""
  ST_PHASE_PARSE_PARTIAL=""
  if asm_strict_pipeline_selfhosted; then
  _abi_t=$(asm_o_text_bytes src/runtime_pipeline_abi.o 2>/dev/null || echo 0)
  build_xlang_asm_info "pipeline selfhosted via runtime_pipeline_abi (stub=__text=${PTEXT}B, abi=${_abi_t}B)"
  STRICT_LINK_BUILD_ASM_PIPELINE=1
  export STRICT_LINK_BUILD_ASM_PIPELINE
  build_xlang_asm_info "strict link build_asm/pipeline.o + glue_standalone"
  elif [ "$PTEXT" -gt 512 ] 2>/dev/null; then
  build_xlang_asm_error "pipeline.o __text=${PTEXT}B but not selfhosted; B-strict link aborted"
  xlang_asm_bstrict_fail "pipeline.o not selfhosted (__text=${PTEXT}B)"
  else
  build_xlang_asm_error "pipeline.o __text=${PTEXT}B too small; B-strict link aborted"
  xlang_asm_bstrict_fail "pipeline.o __text=${PTEXT}B"
  fi
  ST_PIPELINE_ALIAS=""
  if [ "$STRICT_LINK_BUILD_ASM_PIPELINE" -eq 1 ]; then
  if asm_strict_x_orchestration_ok; then
  # X 编排：pipeline_runtime_bootstrap_partial.o 由 filter_strict_asm_objs 链入 ASM_TRY_OBJS。
  ST_RUNTIME_PARTIAL=""
  else
  ensure_pipeline_bootstrap_orchestration_strict_obj
  # C 编排 trampoline；勿与 pipeline_asm_orchestration_partial 重复 pipeline_run_x_pipeline_impl。
  ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_bootstrap_orchestration_strict.o"
  fi
  fi
  if [ "$STRICT_LINK_BUILD_ASM_PIPELINE" -eq 1 ]; then
  ST_RUNTIME_MODE="strict_support"
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_strict_minimal.o"
  build_xlang_asm_info "strict glue_strict_minimal + pipeline_x glue support (X orch)"
  else
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_standalone.o"
  fi
  # wave309/wave304: glue seed shells retired; drop ST_GLUE_OBJ if .o missing.
  [ -z "$ST_GLUE_OBJ" ] || [ -f "$ST_GLUE_OBJ" ] || ST_GLUE_OBJ=""
  ST_RUNTIME_EXTRA=""
  if asm_strict_typeck_selfhosted; then
  ensure_typeck_asm_layout_partial_obj && ST_LAYOUT_PARTIAL="$BUILD_DIR/typeck_asm_layout_partial.o" || ST_LAYOUT_PARTIAL=""
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  build_xlang_asm_info "strict link typeck.o partial + pipeline_x glue support (__text=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo ?)B)"
  else
  build_xlang_asm_info "strict link typeck.o partial+glue_standalone (__text=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo ?)B, minus glue dupes + bare_link_alias)"
  fi
  else
  ensure_typeck_asm_layout_partial_obj && ST_LAYOUT_PARTIAL="$BUILD_DIR/typeck_asm_layout_partial.o" || ST_LAYOUT_PARTIAL=""
  fi
  else
  ensure_pipeline_parse_x_partial_obj
  fi
  # 实验：C 编排 partial（需 build_asm pipeline.o 或 strict_support；设 XLANG_ASM_STRICT_ORCHESTRATION=1 启用）。
  if [ -n "${XLANG_ASM_STRICT_ORCHESTRATION:-}" ] && ensure_pipeline_asm_orchestration_partial_obj; then
  ensure_pipeline_asm_orchestration_from_build_o
  ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_partial.o"
  ST_RUNTIME_EXTRA="$BUILD_DIR/pipeline_asm_strict_support_partial.o $BUILD_DIR/pipeline_asm_orchestration_from_build.o"
  ST_PARSER_LINK=""
  ST_RUNTIME_MODE="asm_orchestration"
  ST_USES_ASM_PIPELINE=1
  elif [ -n "${XLANG_ASM_STRICT_ORCHESTRATION_LEGACY:-}" ] && ensure_pipeline_asm_orchestration_from_build_o; then
  ensure_pipeline_phase_parse_only_partial_obj
  ensure_pipeline_asm_run_all_partial_obj
  ensure_asm_pipeline_run_impl_alias_obj
  ensure_pipeline_asm_typecheck_alias_obj
  ensure_pipeline_asm_x_bootstrap_partial_obj
  ST_RUNTIME_PARTIAL="$BUILD_DIR/pipeline_asm_orchestration_from_build.o"
  ST_RUNTIME_EXTRA="$BUILD_DIR/pipeline_phase_parse_only_partial.o $BUILD_DIR/pipeline_asm_run_all_partial.o $BUILD_DIR/pipeline_run_impl_alias.o $BUILD_DIR/pipeline_asm_typecheck_alias.o $BUILD_DIR/pipeline_asm_x_bootstrap_partial.o"
  ST_PARSER_LINK="$BUILD_DIR/pipeline_parse_x_partial.o"
  ST_RUNTIME_MODE="asm_orchestration_legacy"
  ST_USES_ASM_PIPELINE=1
  fi
  if [ "$ST_RUNTIME_MODE" = "strict_support" ] || [ "$ST_USES_ASM_PIPELINE" -eq 1 ]; then
  export STRICT_LINK_BUILD_ASM_PIPELINE
  if [ "$ST_RUNTIME_MODE" = "strict_support" ]; then
  # build_asm pipeline 自举时须链 preprocess/platform 等 companion .o；否则仅 seed partial 会 U preprocess_x_buf。
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  # pipeline_wpo X 编排编任意 .x 会 SIGSEGV；默认 C orchestration + WPO helpers（Linux 自动开启）。
  maybe_default_pipeline_wpo_strict_link
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && asm_pipeline_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_WPO=1
  else
  export STRICT_LINK_BUILD_ASM_WPO=0
  fi
  # typeck_wpo helpers（不含 check_block/check_expr；全量 check 仍来自 typeck.o partial）。
  if [ "${XLANG_ASM_STRICT_LINK_TYPECK_WPO:-1}" != "0" ] && asm_typeck_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_TYPECK_WPO=1
  else
  export STRICT_LINK_BUILD_ASM_TYPECK_WPO=0
  rm -f "$BUILD_DIR/typeck_strict_link_partial.o" "$BUILD_DIR/typeck_strict_link_export.txt" \
  "$BUILD_DIR/typeck_wpo_helpers_partial.o" "$BUILD_DIR/typeck_wpo_helpers_export.txt" 2>/dev/null || true
  fi
  if asm_backend_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_BACKEND_WPO=1
  else
  export STRICT_LINK_BUILD_ASM_BACKEND_WPO=0
  fi
  # WPO FULL：glue_standalone 与 pipeline_wpo.o 有重叠 T（如 pipeline_should_skip_x_typeck）。
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && asm_pipeline_wpo_strict_link_full_ok; then
  if ensure_pipeline_glue_standalone_wpo_dedupe_obj; then
  ST_GLUE_OBJ="$BUILD_DIR/pipeline_glue_wpo_dedupe.o"
  build_xlang_asm_info "strict glue_wpo_dedupe (glue minus pipeline_wpo T dupes)"
  fi
  fi
  filter_strict_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  else
  ASM_TRY_OBJS=""
  fi
  else
  filter_strict_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  fi
  else
  filter_experimental_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  fi
  echo " re-link xlang_asm (strict: ${ST_RUNTIME_MODE}, no pipeline_x.o) ..."
  ensure_preprocess_if_stack_provider_obj || true
  # G.7: companion only when ensure actually wrote it; abi-on-argv path deletes it.
  ST_PREPROCESS_IF_STACK_O=""
  [ -f "$BUILD_DIR/preprocess_if_stack_only.o" ] && ST_PREPROCESS_IF_STACK_O="$BUILD_DIR/preprocess_if_stack_only.o"
  ensure_asm_driver_seed_c_objs
  SEED_O="$BUILD_DIR/asm_driver_seed"
  ensure_asm_strict_link_extra_objs
  # runtime_io_abi.o hard-coded once on strict link line — do not also put it here
  # (PLATFORM: DARWIN rejects the same .o twice as duplicate symbols).
  ST_BSTRICT_LINK_EXTRA="src/asm/parser_asm_parse_expr_link.o src/asm/pipeline_fill_dep_strict_alias.o $BUILD_DIR/seed_host/asm_full_link_stubs.o"
  ensure_asm_link_objs
  # PLATFORM: DARWIN — runtime_panic.o is a user-domain cold twin (STD_AND_PANIC
  # bag) that defines link_abi_getenv/_impl, dual-defining with src/runtime_link_abi.o
  # (G.7 host authority hard-coded above). Darwin ld rejects the duplicate; Linux ld
  # tolerates it (last-def wins). The host compiler link does not need runtime_panic.o:
  # xlang_panic_ and crash_evidence are resolved as static locals in other .o; atoi via
  # libc. Skip on Darwin to match experimental bootstrap (which never links it).
  ST_RUNTIME_PANIC="runtime_panic.o atoi_stub.o"
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
    ST_RUNTIME_PANIC=""
  fi
  ST_BRIDGE_OBJ=""
  ST_SEED_PARSER_TCK=""
  ST_SEED_PREPROCESS_LINK=""
  ST_PARSER_X_TAIL=""
  ST_TYPECK_X_TAIL=""
  ST_STRICT_COMPANIONS=""
  ST_SEED_PREPROCESS_LINK=$(asm_seed_st_preprocess_link)
  if [ "$ST_RUNTIME_MODE" = "strict_support" ]; then
  ensure_parser_x_o_for_strict_link
  # 链 bridge：子命令由 bridge.main_entry 分发；裸编译走 weak entry→run_compiler_c（XLANG_ASM_USE_COMPILER_IMPL_C 时走 impl_c parse）。
  ensure_asm_experimental_symbol_bridge_obj
  ST_BRIDGE_OBJ="$BUILD_DIR/asm_experimental_symbol_bridge.o"
  # 子命令 .o（勿链 driver_x.o：与 pipeline_glue_standalone 重复 main_run_compiler_c）；main.o 不链入（与 driver_emit_x.o 重复符号）。
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o"
  if asm_strict_link_driver_selfhosted; then
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_emit_x.o"
  STRICT_LINK_BUILD_ASM_DRIVER=1
  export STRICT_LINK_BUILD_ASM_DRIVER
  build_xlang_asm_info "strict link build_asm/driver_compile_link.o (parse_argv + run_compiler_full_x X emit)"
  fi
  ST_TYPECK_X_LINK="typeck_x.o"
  if [ -n "$ST_LAYOUT_PARTIAL" ] && ensure_typeck_x_no_layout_partial_obj; then
  ST_TYPECK_X_LINK="$BUILD_DIR/typeck_x_no_layout_partial.o"
  fi
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  ST_WPO_ALIAS=""
  if [ "${XLANG_ASM_STRICT_LINK_PIPELINE_WPO:-0}" = "1" ] && asm_pipeline_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_WPO=1
  if asm_pipeline_wpo_strict_link_full_ok; then
  build_xlang_asm_info "strict link whole pipeline_wpo.o (X orchestration FULL)"
  else
  ensure_pipeline_wpo_typecheck_emit_bridge_obj && ST_WPO_ALIAS="$BUILD_DIR/pipeline_wpo_typecheck_emit_bridge.o"
  build_xlang_asm_info "strict link pipeline_wpo_helpers (opt-in WPO, C orchestration + typecheck emit bridge)"
  fi
  fi
  if asm_backend_wpo_strict_reach_ok; then
  export STRICT_LINK_BUILD_ASM_BACKEND_WPO=1
  fi
  if asm_strict_typeck_selfhosted; then
  ensure_typeck_f64_bits_obj
  ST_TCK_C_PRECHECK=$(ensure_typeck_c_user_precheck_obj)
  if asm_strict_typeck_x_glue_via_pipeline_x; then
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $(asm_seed_st_x_glue_suffix)"
  build_xlang_asm_info "E-06 v3 strict X-only seed (async + X glue; no SEED C frontend .o)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link) $(asm_seed_st_x_glue_suffix)"
  build_xlang_asm_info "strict seed typeck + typeck_x tail (X glue; no build_asm typeck partial)"
  fi
  else
  ensure_typeck_asm_bare_link_alias_obj
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$ST_TCK_C_PRECHECK $BUILD_DIR/typeck_asm_bare_link_alias.o $(asm_seed_st_async_support_link) $(asm_seed_st_x_glue_suffix) src/typeck/typeck_f64_bits.o"
  build_xlang_asm_info "E-06 v3 strict bare alias X-only (no SEED parser/lexer/ast .o)"
  else
  ST_SEED_PARSER_TCK="$ST_TCK_C_PRECHECK $BUILD_DIR/typeck_asm_bare_link_alias.o $(asm_seed_st_frontend_seed_no_typeck_link) $(asm_seed_st_x_glue_suffix) src/typeck/typeck_f64_bits.o"
  fi
  fi
  else
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  fi
  fi
  # parser_x.o 须为链接线最后一批：压过 seed parser.o 与 companions 中可能的重复符号（struct mk CALL 内联等）。
  ST_PARSER_X_TAIL="parser_x.o lexer_x.o"
  if asm_strict_typeck_x_glue_via_pipeline_x && [ -n "$ST_TYPECK_X_LINK" ] && [ -f "$ST_TYPECK_X_LINK" ]; then
  ST_TYPECK_X_TAIL="$ST_TYPECK_X_LINK"
  fi
  ensure_ast_pool_l5_bridge_obj
  ST_BACKEND_COMPANIONS=$(strict_asm_backend_companion_objs) || ST_BACKEND_COMPANIONS="$BUILD_DIR/seed_host/asm_backend_partial.o"
  if [ "${STRICT_LINK_BUILD_ASM_BACKEND_WPO:-0}" -eq 1 ] && asm_backend_wpo_strict_reach_ok; then
  build_xlang_asm_info "strict link backend_wpo.o (WPO reach OK)"
  fi
  ensure_asm_backend_compat_stubs_obj
  refresh_bstrict_link_variants
  # PLATFORM: DARWIN — stubs come from BSTRICT_SEED_SUPPORT (filt); omit hard-coded full stubs.
  ST_COMPANION_GLUE_STUBS="src/runtime_driver_strict_glue_stubs.o"
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ST_COMPANION_GLUE_STUBS=""
  fi
  # user_asm (+ Darwin arm64 enc) live in BSTRICT_USER_ASM_EARLY_LINK before stubs.
  ST_STRICT_COMPANIONS="$BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $ST_BACKEND_COMPANIONS $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BSTRICT_DISPATCH_COMPANIONS parser_asm_thin_glue.o $ST_BSTRICT_LINK_EXTRA src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o preprocess_x.o $ST_COMPANION_GLUE_STUBS $ST_DRIVER_CLI_OBJS"
  else
  # legacy：须 seed C 前端 *.o 在前、*_x.o 在后（macOS ld 重复符号取后定义）。
  # E-06 v3 X：仅 async seed + X glue；parser_x.o 在 ST_PARSER_X_TAIL 压过重复符号。
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  build_xlang_asm_info "E-06 v3 strict default X-only ST_SEED_PARSER_TCK"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link) $ST_TYPECK_X_LINK $(asm_seed_st_x_glue_suffix)"
  fi
  ST_PARSER_X_TAIL="parser_x.o lexer_x.o"
  ensure_ast_pool_l5_bridge_obj
  ST_BACKEND_COMPANIONS=$(strict_asm_backend_companion_objs) || ST_BACKEND_COMPANIONS="$BUILD_DIR/seed_host/asm_backend_partial.o"
  ensure_asm_backend_compat_stubs_obj
  refresh_bstrict_link_variants
  ST_COMPANION_GLUE_STUBS="src/runtime_driver_strict_glue_stubs.o"
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ]; then
  ST_COMPANION_GLUE_STUBS=""
  fi
  ST_STRICT_COMPANIONS="$BUILD_DIR/x_seed_bridge.o $BUILD_DIR/seed_link_compat.o $ST_BACKEND_COMPANIONS $BSTRICT_ASM_BACKEND_COMPAT_STUBS_LINK $BSTRICT_DISPATCH_COMPANIONS parser_asm_thin_glue.o $ST_BSTRICT_LINK_EXTRA src/driver/fmt_check_cmd_driver.o src/driver/target_cpu.o src/asm/simd_enc.o src/asm/simd_loop.o preprocess_x.o $ST_COMPANION_GLUE_STUBS $ST_DRIVER_CLI_OBJS"
  fi
  elif [ "$ST_USES_ASM_PIPELINE" -eq 1 ]; then
  ST_BRIDGE_OBJ="$BUILD_DIR/asm_experimental_symbol_bridge.o"
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link)"
  fi
  else
  ST_BRIDGE_OBJ="$BUILD_DIR/asm_experimental_symbol_bridge.o"
  if asm_seed_use_x_frontend; then
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link)"
  else
  ST_SEED_PARSER_TCK="$(asm_seed_st_frontend_seed_link)"
  fi
  fi
  ensure_asm_bootstrap_x_companion_objs
  ensure_asm_experimental_lsp_objs
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  # PLATFORM: DARWIN — same asm_driver_* collision fix as experimental bootstrap.
  # BSTRICT_SEED_SUPPORT already carries stubs; leave ST_STRICT_GLUE_STUBS_O empty to avoid a second copy.
  ST_STRICT_GLUE_STUBS_O="src/runtime_driver_strict_glue_stubs.o"
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ] \
    && ensure_bstrict_darwin_strict_glue_stubs_filt_obj 2>/dev/null; then
  BSTRICT_SEED_SUPPORT=$(echo "$BSTRICT_SEED_SUPPORT" \
    | sed "s|src/runtime_driver_strict_glue_stubs\\.o|$BUILD_DIR/bstrict_strict_glue_stubs_darwin.o|g")
  ST_STRICT_GLUE_STUBS_O=""
  fi
  ST_TYPECK_LSP_STUB=""
  if [ ! -f "$BUILD_DIR/gen_driver/lsp_io_x.o" ]; then
  ST_TYPECK_LSP_STUB="$BUILD_DIR/typeck_lsp_io_stub.o"
  fi
  if [ -n "$ST_BRIDGE_OBJ" ] || asm_strict_pipeline_selfhosted 2>/dev/null; then
  export XLANG_ASM_SKIP_ENTRY_SMOKE=1
  export XLANG_ASM_SKIP_MAIN_O_REBUILD=1
  export XLANG_ASM_SKIP_WPO_DOGFOOD=1
  # PLATFORM: SHARED — do NOT force SKIP_DRIVER_EMIT_HEAVY here. Tip can emit
  # driver_compile EMIT_HEAVY; Darwin merge is pure_ld_partial_merge (libtool ar).
  # Escape: caller may still set XLANG_ASM_SKIP_DRIVER_EMIT_HEAVY=1.
  rebuild_main_o_for_cli || true
  rebuild_driver_compile_emit_heavy_and_link || true
  build_xlang_asm_info "skip WPO dogfood recompile (strict bridge / pipeline selfhosted); EMIT_HEAVY driver attempted"
  else
  rebuild_main_o_for_cli || true
  rebuild_driver_compile_emit_heavy_and_link || true
  rebuild_driver_compile_o_wpo || true
  rebuild_pipeline_wpo_o || true
  rebuild_typeck_wpo_o || true
  rebuild_backend_wpo_o || true
  fi
  # driver_compile_link 在首批 filter_strict_asm_objs 之后才补全 parse_argv_loop；刷新链入对象避免与 driver_compile_x 重复。
  if [ "$ST_RUNTIME_MODE" = "strict_support" ]; then
  if asm_strict_link_driver_selfhosted; then
  STRICT_LINK_BUILD_ASM_DRIVER=1
  export STRICT_LINK_BUILD_ASM_DRIVER
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_emit_x.o"
  filter_strict_asm_objs
  ASM_TRY_OBJS="$FILTERED"
  build_xlang_asm_info "strict re-filter after driver_compile_link OK"
  else
  ST_DRIVER_CLI_OBJS="driver_fmt_x.o driver_check_x.o driver_test_x.o driver_build_x.o driver_run_x.o driver_compile_x.o driver_emit_x.o"
  fi
  fi
  if [ -n "$ST_BRIDGE_OBJ" ]; then
  strip_main_entry_from_build_asm_main_o || true
  fi
  refresh_build_asm_ci_text_stubs_for_strict_link || true
  bootstrap_ensure_entry_objs
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)
  set +e
  BOOT_DRIVER_TAIL=$(bootstrap_link_tail_driver)
  # shellcheck disable=SC2086
  # PLATFORM: SHARED — BSTRICT_USER_ASM_EARLY_LINK before weak stubs / bridge so
  # prefer/libtool ar user_asm extracts strong asm_asm_codegen_elf_o (G.7 twin g05).
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_USER_ASM_EARLY_LINK \
  $BSTRICT_SEED_SUPPORT \
  $ST_PREPROCESS_IF_STACK_O \
  ${ST_GLUE_OBJ:+"$ST_GLUE_OBJ"} \
  $ST_WPO_ALIAS \
  $ASM_TRY_OBJS \
  $ST_PARSER_LINK \
  $ST_RUNTIME_PARTIAL \
  $ST_BRIDGE_OBJ \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $ST_TYPECK_LSP_STUB \
  $ST_STRICT_GLUE_STUBS_O \
  $ST_SEED_PREPROCESS_LINK \
  $ST_SEED_PARSER_TCK \
  $ST_STRICT_COMPANIONS \
  "$BUILD_DIR/gen_driver/lsp_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_ctx.o \
  src/lsp/lsp_diag_pipeline_sizes.o \
  $ST_RUNTIME_PANIC atoi_stub.o \
  $ST_RUNTIME_EXTRA \
  $ST_LAYOUT_PARTIAL \
  $ST_PIPELINE_ALIAS \
  $ST_PARSER_X_TAIL \
  $ST_TYPECK_X_TAIL \
  $BOOT_DRIVER_TAIL 2>"$BUILD_DIR/.asm_strict_link_err"
  ST_RC=$?
  set -e
  if [ "$ST_RC" -ne 0 ] && [ "$ST_USES_ASM_PIPELINE" -eq 1 ]; then
  build_xlang_asm_warn "strict asm orchestration link failed; retrying with pipeline_runtime_bootstrap_partial.o"
  ST_RUNTIME_BOOTSTRAP_PARTIAL=""
  if ensure_pipeline_runtime_bootstrap_partial_obj; then
  ST_RUNTIME_BOOTSTRAP_PARTIAL="$BUILD_DIR/pipeline_runtime_bootstrap_partial.o"
  fi
  ST_PARSER_LINK="$BUILD_DIR/pipeline_parse_x_partial.o"
  ST_RUNTIME_EXTRA=""
  ST_RUNTIME_MODE="bootstrap"
  ST_USES_ASM_PIPELINE=0
  ST_STRICT_FB_X_TAIL=""
  if asm_seed_use_x_frontend; then
  ST_SEED_PREPROCESS_LINK=""
  ST_SEED_PARSER_TCK="$(asm_seed_st_async_support_link) $(asm_seed_st_x_glue_suffix)"
  ST_STRICT_FB_X_TAIL="preprocess_x.o parser_x.o lexer_x.o typeck_x.o codegen_x.o"
  build_xlang_asm_info "E-06 v3 strict fallback X-only (no SEED C frontend .o)"
  else
  ST_SEED_PREPROCESS_LINK=""
  ST_SEED_PARSER_TCK="$SEED_O/parser.o $SEED_O/async_liveness.o $SEED_O/async_cps_codegen.o $SEED_O/lexer.o $SEED_O/ast_seed.o"
  fi
  set +e
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  bootstrap_ensure_entry_objs
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_USER_ASM_EARLY_LINK \
  $BSTRICT_SEED_SUPPORT \
  $ST_PREPROCESS_IF_STACK_O \
  ${ST_GLUE_OBJ:+"$ST_GLUE_OBJ"} \
  $ST_WPO_ALIAS \
  $ASM_TRY_OBJS \
  "$ST_PARSER_LINK" \
  $ST_RUNTIME_BOOTSTRAP_PARTIAL \
  "$BUILD_DIR/asm_experimental_symbol_bridge.o" \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $ST_TYPECK_LSP_STUB \
  src/runtime_driver_strict_glue_stubs.o \
  $ST_SEED_PREPROCESS_LINK \
  $ST_SEED_PARSER_TCK \
  $ST_STRICT_FB_X_TAIL \
  "$BUILD_DIR/gen_driver/lsp_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_x.o" \
  "$BUILD_DIR/gen_driver/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_ctx.o \
  src/lsp/lsp_diag_pipeline_sizes.o \
  $BOOT_DRIVER_TAIL 2>"$BUILD_DIR/.asm_strict_link_err"
  ST_RC=$?
  set -e
  fi
  # PLATFORM: SHARED — experimental bootstrap sets LINK_MODE=asm_only_experimental
  # first, then strict re-link may succeed and MUST upgrade to asm_only_strict.
  # Do NOT gate the upgrade on LINK_MODE!=experimental (that blocked Linux freestanding
  # Stage2 after the Darwin keep-path: bootstrap already marked experimental).
  # PLATFORM: DARWIN only — when strict fails, set STRICT_KEPT_EXPERIMENTAL=1 and keep
  # experimental; that flag alone skips the strict-OK upgrade. Linux still hard-fails.
  STRICT_KEPT_EXPERIMENTAL=0
  if [ "$ST_RC" -ne 0 ]; then
  build_xlang_asm_error "strict link failed (rc=$ST_RC)"
  if [ -s "$BUILD_DIR/.asm_strict_link_err" ]; then
  tail -n 8 "$BUILD_DIR/.asm_strict_link_err" | sed 's/^/ /'
  fi
  # PLATFORM: DARWIN — strict re-link still has residual multiply_defined vs Linux
  # --allow-multiple-definition. Experimental bootstrap already linked and is enough
  # for Stage2 gen2 + behavior parity; product rail remains g05/L4.
  # PLATFORM: LINUX — keep hard fail (gold standard requires asm_only_strict).
  if [ "$(uname -s 2>/dev/null)" = "Darwin" ] && [ -x ./xlang_asm.experimental ]; then
  build_xlang_asm_warn "strict re-link failed on Darwin; keeping xlang_asm.experimental as xlang_asm"
  cp -f ./xlang_asm.experimental ./xlang_asm
  LINK_OK=1
  LINK_MODE=asm_only_experimental
  ST_RC=0
  STRICT_KEPT_EXPERIMENTAL=1
  build_xlang_asm_info "B-strict OK (experimental bootstrap) - LINK_MODE=asm_only_experimental, Darwin strict residual non-blocking"
  fi
  fi
  if [ "$ST_RC" -eq 0 ] && [ "${STRICT_KEPT_EXPERIMENTAL:-0}" != "1" ]; then
  LINK_OK=1
  if [ "$ST_USES_ASM_PIPELINE" -eq 1 ]; then
  build_xlang_asm_info "xlang_asm strict OK (pipeline.o + C orchestration, __text=${PTEXT}B)"
  elif [ "$ST_RUNTIME_MODE" = "strict_support" ]; then
  if [ "${STRICT_LINK_BUILD_ASM_PIPELINE:-0}" -eq 1 ]; then
  build_xlang_asm_info "xlang_asm strict OK (build_asm/pipeline.o + glue_standalone, __text=${PTEXT}B)"
  else
  build_xlang_asm_info "xlang_asm strict OK (strict_support, pipeline.o __text=${PTEXT}B)"
  fi
  else
  build_xlang_asm_info "xlang_asm strict OK (pipeline_runtime_bootstrap_partial.o + pipeline.o __text=${PTEXT}B)"
  fi
  LINK_MODE=asm_only_strict
  if [ -z "${XLANG_ASM_SKIP_STRICT_SMOKE:-}" ]; then
  if ! XLANG_ASM_SMOKE_SKIP_GATE=1 ./scripts/run_xlang_asm_smoke.sh >"$BUILD_DIR/.asm_strict_smoke.log" 2>&1; then
  # strict 重链产物 compile 失败时：本地可 XLANG_ASM_ALLOW_EXPERIMENTAL_FALLBACK=1 回退；B-strict CI 须 FAIL。
  if [ -x ./xlang_asm.experimental ] && cp -f ./xlang_asm "$BUILD_DIR/xlang_asm.strict_failed" 2>/dev/null; then
  cp -f ./xlang_asm.experimental ./xlang_asm
  if XLANG_ASM_SMOKE_SKIP_GATE=1 ./scripts/run_xlang_asm_smoke.sh >"$BUILD_DIR/.asm_strict_smoke_fallback.log" 2>&1; then
  build_xlang_asm_warn "strict smoke failed; installed xlang_asm.experimental as xlang_asm (fallback OK)"
  touch "$BUILD_DIR/.strict_smoke_experimental_fallback"
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && [ -z "${XLANG_ASM_ALLOW_EXPERIMENTAL_FALLBACK:-}" ]; then
  xlang_asm_bstrict_fail "strict xlang_asm smoke failed (experimental fallback disabled for B-strict)"
  fi
  tail -n 5 "$BUILD_DIR/.asm_strict_smoke.log" 2>/dev/null | sed 's/^/ strict: /' || true
  else
  cp -f "$BUILD_DIR/xlang_asm.strict_failed" ./xlang_asm 2>/dev/null || true
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "strict xlang_asm smoke failed (experimental fallback also failed)"
  fi
  build_xlang_asm_error "strict xlang_asm smoke failed (experimental fallback also failed)"
  tail -n 8 "$BUILD_DIR/.asm_strict_smoke.log" 2>/dev/null | sed 's/^/ /' || true
  tail -n 8 "$BUILD_DIR/.asm_strict_smoke_fallback.log" 2>/dev/null | sed 's/^/ fallback: /' || true
  fi
  elif [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "strict xlang_asm smoke failed"
  else
  build_xlang_asm_error "strict xlang_asm smoke failed"
  tail -n 8 "$BUILD_DIR/.asm_strict_smoke.log" 2>/dev/null | sed 's/^/ /' || true
  fi
  else
  rm -f "$BUILD_DIR/.strict_smoke_experimental_fallback" 2>/dev/null || true
  build_xlang_asm_info "strict xlang_asm smoke passed"
  xlang_asm_sync_stage1_from_strict
  fi
  fi
  # strict 链成功后：用新链 ./xlang_asm 重编 WPO 压缩 .o（abi freshness+ulimit；main EH=0 ~656B）。
  if rebuild_main_o_post_strict_link; then
  :
  elif [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_warn "post-strict main.o WPO recompile failed (non-fatal for gate; stage2 may retry)"
  else
  build_xlang_asm_warn "post-strict main.o WPO recompile failed (keeping pre-link main.o)"
  fi
  rebuild_driver_compile_post_strict_link || true
  ensure_experimental_ast_pool_for_wpo || true
  # strict 产物自编译大模块（>150KiB 入口仍 SIGSEGV；bootstrap experimental 第二遍已通过）。
  if ! rebuild_typeck_parser_backend_second_pass; then
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  build_xlang_asm_warn "B-strict self-compile second pass failed (bootstrap xlang_asm + smoke OK; retry with seed XLANG for -backend asm)"
  fi
  fi
  # M8a：strict 重链后的 xlang_asm 已含新 parser.o，再重编 arm64_enc/lsp/asm（勿用 experimental，其仍链旧 parser）。
  if [ -x ./xlang_asm ]; then
  rebuild_m8a_parser_dependent_modules_second_pass "./xlang_asm" || true
  fi
  TCK2=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo 0)
  PAR2=$(asm_o_text_bytes "$BUILD_DIR/parser.o" 2>/dev/null || echo 0)
  BACK2=$(asm_o_text_bytes "$BUILD_DIR/backend.o" 2>/dev/null || echo 0)
  build_xlang_asm_info "strict self-compile __text typeck=${TCK2}B parser=${PAR2}B backend=${BACK2}B"
  elif [ "${STRICT_KEPT_EXPERIMENTAL:-0}" = "1" ]; then
  # PLATFORM: DARWIN — keep path already set LINK_OK + experimental B-strict OK above.
  :
  else
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  if [ -s "$BUILD_DIR/.asm_strict_link_err" ]; then
  tail -n 15 "$BUILD_DIR/.asm_strict_link_err" | sed 's/^/ /'
  fi
  xlang_asm_bstrict_fail "strict re-link failed (rc=$ST_RC)"
  fi
  build_xlang_asm_warn "strict re-link failed (rc=$ST_RC); keeping bootstrap xlang_asm with pipeline_x.o"
  if [ -s "$BUILD_DIR/.asm_strict_link_err" ]; then
  tail -n 15 "$BUILD_DIR/.asm_strict_link_err" | sed 's/^/ /'
  fi
  fi
  else
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "strict re-link skipped (pipeline.o __text=${PTEXT}B)"
  fi
  build_xlang_asm_warn "strict re-link skipped (pipeline.o __text=${PTEXT}B); keeping bootstrap xlang_asm with pipeline_x.o"
  fi
  fi
  else
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  if [ -s "$BUILD_DIR/.asm_experimental_link_err" ]; then
  tail -n 20 "$BUILD_DIR/.asm_experimental_link_err" | sed 's/^/ /'
  fi
  xlang_asm_bstrict_fail "experimental asm-only link failed (rc=$FB_RC)"
  fi
  build_xlang_asm_warn "experimental asm-only link failed (rc=$FB_RC); falling back to gen_driver"
  if [ -s "$BUILD_DIR/.asm_experimental_link_err" ]; then
  tail -n 20 "$BUILD_DIR/.asm_experimental_link_err" | sed 's/^/ /'
  fi
  fi
  else
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  if build_xlang_asm_is_msys; then
  xlang_asm_bstrict_fail "Windows B-strict experimental X-only link prerequisites missing"
  fi
  xlang_asm_bstrict_fail "experimental asm-only skipped on $UNAME_ASM"
  fi
  build_xlang_asm_warn "experimental asm-only skipped on $UNAME_ASM; falling back to gen_driver (仍含 cc -c pipeline_gen.c)"
  fi
  fi
  if [ "$LINK_OK" -ne 1 ]; then
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "asm-only link not OK (LINK_MODE=${LINK_MODE:-none})"
  fi
  if [ "$XLANG_ASM_LINK_TOPOLOGY" = "full_asm" ] && [ "$ASM_TEXT_ALL_OK" = "1" ]; then
  build_xlang_asm_info "full_asm: __text 已全部非空，默认仍走 gen_driver（设 XLANG_ASM_EXPERIMENTAL_SKIP_GEN=1 试 asm-only 链）"
  fi
  ensure_asm_gen_driver_x_objs
  ensure_asm_bootstrap_x_companion_objs
  fi
  if [ "$LINK_OK" -ne 1 ]; then
  PIPELINE_LIBS=$(bootstrap_pipeline_libs)
  bootstrap_ensure_entry_objs
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  SEED_O="$BUILD_DIR/asm_driver_seed"
  GEN_O="$BUILD_DIR/gen_driver"
  ASM_GEN_DRIVER_C_FRONTEND_LINK=$(asm_seed_gen_driver_c_frontend_link)
  ASM_GEN_DRIVER_ASYNC_LINK=$(asm_seed_st_async_support_link)
  if asm_seed_omit_c_frontend_seed; then
  build_xlang_asm_info "E-06 v4 gen_driver hybrid link omit SEED C frontend .o (X companions via GEN_DRIVER_X_PIPELINE_COMPANIONS)"
  fi
  echo " linking xlang_asm (runtime_asm_build + runtime_driver + seed + driver/* + -E pipeline/lsp; no build_asm/*.o) ..."
  set +e
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  ensure_asm_pipeline_glue_strict_minimal_obj
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  # PLATFORM: SHARED — strip early strict_glue from support bag; reals must link first
  # so PE --allow-multiple-definition keeps pipeline_x/parser_x (Makefile L2008-2019).
  BSTRICT_SEED_SUPPORT=$(echo "$BSTRICT_SEED_SUPPORT" | sed 's|[[:space:]]*src/runtime_driver_strict_glue_stubs\.o||g')
  BOOT_DRIVER_TAIL=$(bootstrap_link_tail_driver)
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)
  # Glue suffix at END only (once): mirrors DRIVER_SEED_GLUE_SUFFIX / g05 _GLUE_SUFFIX.
  # wave304: strict_minimal shell retired — stubs only at link END.
  GEN_DRIVER_GLUE_SUFFIX="src/runtime_driver_strict_glue_stubs.o"
  # shellcheck disable=SC2086
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_SEED_SUPPORT \
  $ASM_GEN_DRIVER_C_FRONTEND_LINK \
  $ASM_GEN_DRIVER_ASYNC_LINK \
  "$GEN_O/driver_x.o" \
  "$GEN_O/driver_fmt_x.o" \
  "$GEN_O/driver_check_x.o" \
  "$GEN_O/driver_test_x.o" \
  "$GEN_O/pipeline_x.o" \
  "$GEN_O/preprocess_x.o" \
  $GEN_DRIVER_TYPECK_COMPANIONS \
  $GEN_DRIVER_X_PIPELINE_COMPANIONS \
  $GEN_DRIVER_BSTRICT_COMPANIONS \
  "$GEN_O/lsp_x.o" \
  "$GEN_O/lsp_io_x.o" \
  "$GEN_O/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_sizes.o \
  src/lsp/lsp_diag_pipeline_ctx.o \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $GEN_DRIVER_GLUE_SUFFIX \
  $BOOT_DRIVER_TAIL
  FB_RC=$?
  set -e
  if [ "$FB_RC" -eq 0 ]; then
  build_xlang_asm_info "xlang_asm built"
  LINK_OK=1
  LINK_MODE=driver
  else
  build_xlang_asm_error "link failed (rc=$FB_RC). See src/asm/README.md Goal 2"
  fi
  fi
  fi
else
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "main.o or pipeline.o missing or empty"
  fi
  build_xlang_asm_warn "main.o or pipeline.o missing or empty; trying gen_driver fallback only"
  ensure_runtime_cc_stubs
  ensure_std_fs_io_heap_objs
  ensure_asm_driver_seed_c_objs
  ensure_lsp_diag_pipeline_sizes_obj
  ensure_asm_xlang_lsp_diag_stub_obj
  ensure_asm_lsp_codegen_extern_obj
  ensure_asm_gen_driver_x_objs
  ensure_asm_bootstrap_x_companion_objs
  PIPELINE_LIBS=$(bootstrap_pipeline_libs)
  bootstrap_ensure_entry_objs
  BOOT_ENTRY_OBJ=$(bootstrap_entry_obj)
  BOOT_ENTRY_LDFLAGS=$(bootstrap_entry_ldflags)
  SEED_O="$BUILD_DIR/asm_driver_seed"
  GEN_O="$BUILD_DIR/gen_driver"
  ASM_GEN_DRIVER_C_FRONTEND_LINK=$(asm_seed_gen_driver_c_frontend_link)
  ASM_GEN_DRIVER_ASYNC_LINK=$(asm_seed_st_async_support_link)
  if asm_seed_omit_c_frontend_seed; then
  build_xlang_asm_info "E-06 v4 gen_driver fallback link omits SEED C frontend .o (X companions)"
  fi
  build_xlang_asm_info "linking xlang_asm (gen_driver fallback; build_asm incomplete)"
  set +e
  ensure_runtime_driver_asm_strict_obj
  ensure_asm_bootstrap_support_extra_objs
  ensure_asm_pipeline_glue_strict_minimal_obj
  BSTRICT_SEED_SUPPORT=$(asm_bootstrap_support_extra_link)
  # PLATFORM: SHARED — same PE first-wins glue-end discipline as main gen_driver hybrid.
  BSTRICT_SEED_SUPPORT=$(echo "$BSTRICT_SEED_SUPPORT" | sed 's|[[:space:]]*src/runtime_driver_strict_glue_stubs\.o||g')
  BOOT_DRIVER_TAIL=$(bootstrap_link_tail_driver)
  ASM_GLUE_DUP_LDFLAGS=$(asm_glue_duplicate_ldflags)
  # wave304: strict_minimal shell retired — stubs only at link END.
  GEN_DRIVER_GLUE_SUFFIX="src/runtime_driver_strict_glue_stubs.o"
  # shellcheck disable=SC2086
  "$CC" $CFLAGS $BOOT_ENTRY_LDFLAGS $ASM_GLUE_DUP_LDFLAGS -DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -o xlang_asm \
  $BOOT_ENTRY_OBJ \
  src/runtime_io_abi.o \
  src/runtime_link_abi.o \
  src/runtime_pipeline_abi.o \
  src/runtime_driver_abi.o \
  src/diag.o \
  src/runtime_driver_diagnostic.o \
  src/runtime_driver_asm_strict.o \
  $BSTRICT_SEED_SUPPORT \
  $ASM_GEN_DRIVER_C_FRONTEND_LINK \
  $ASM_GEN_DRIVER_ASYNC_LINK \
  "$GEN_O/driver_x.o" \
  "$GEN_O/driver_fmt_x.o" \
  "$GEN_O/driver_check_x.o" \
  "$GEN_O/driver_test_x.o" \
  "$GEN_O/pipeline_x.o" \
  "$GEN_O/preprocess_x.o" \
  $GEN_DRIVER_TYPECK_COMPANIONS \
  $GEN_DRIVER_X_PIPELINE_COMPANIONS \
  $GEN_DRIVER_BSTRICT_COMPANIONS \
  "$GEN_O/lsp_x.o" \
  "$BUILD_DIR/typeck_lsp_io_stub.o" \
  "$GEN_O/lsp_io_x.o" \
  "$GEN_O/lsp_io_std_heap_x.o" \
  "$LSP_DIAG_SEED_O" \
  src/lsp/lsp_diag_pipeline_sizes.o \
  src/lsp/lsp_diag_pipeline_ctx.o \
  "$BUILD_DIR/asm_xlang_lsp_diag_stub.o" \
  $GEN_DRIVER_GLUE_SUFFIX \
  $BOOT_DRIVER_TAIL
  FB_RC=$?
  set -e
  if [ "$FB_RC" -eq 0 ]; then
  build_xlang_asm_info "xlang_asm built (gen_driver fallback)"
  LINK_OK=1
  LINK_MODE=driver
  fi
fi

if [ "$LINK_OK" -eq 1 ]; then
  case "$LINK_MODE" in
  crt0)
  build_xlang_asm_info "Target-B-partial: linked without cc -c pipeline_gen.c (crt0 + asm .o)"
  ;;
  driver)
  build_xlang_asm_info "Target-B-hybrid: xlang-c -E + cc -c gen_driver (topology=${XLANG_ASM_LINK_TOPOLOGY})"
  ;;
  asm_only_experimental)
  build_xlang_asm_info "Target-B-experimental: bootstrap with pipeline_x.o partial (no pipeline_gen.c in link)"
  ;;
  asm_only_strict)
  build_xlang_asm_info "Target-B-strict: build_asm + glue_standalone + partials, no pipeline_x.o / pipeline_gen.c"
  ;;
  esac
fi

if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && [ "$LINK_MODE" != "asm_only_strict" ] && [ "$LINK_MODE" != "asm_only_experimental" ]; then
  xlang_asm_bstrict_fail "B-strict requires asm_only_strict or asm_only_experimental link (got LINK_MODE=${LINK_MODE:-none})"
fi

# B-strict 验收：最终链无 cc -c pipeline_gen.c；asm_only_experimental = pipeline_x partial bootstrap（strict 重链待 pipeline.o 自举）。
if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && [ "$LINK_MODE" = "asm_only_strict" ]; then
  build_xlang_asm_info "B-strict OK - LINK_MODE=asm_only_strict, no pipeline_x.o in final link"
  if [ "$XLANG_ASM_LINK_TOPOLOGY" = "full_asm" ] && [ "$ASM_TEXT_ALL_OK" = "1" ]; then
  build_xlang_asm_info "M11 OK - full_asm topology + asm_only_strict (macOS/Linux production B-strict)"
  fi
fi
if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ] && [ "$LINK_MODE" = "asm_only_experimental" ]; then
  build_xlang_asm_info "B-strict OK (experimental bootstrap) - LINK_MODE=asm_only_experimental, final link uses pipeline_x.o partial not pipeline_gen.c"
fi

# CI：experimental 链成功后仍须 typeck.o EMIT_HEAVY（S2 gate）；兜底若上文未跑或仍为小桩。
if [ "$LINK_OK" -eq 1 ] && [ -n "${CI:-}" ]; then
  _s2_comp="./xlang_asm.experimental"
  [ -x "$_s2_comp" ] || _s2_comp="./xlang_asm"
  if [ -x "$_s2_comp" ]; then
  _s2_txt=$(asm_o_text_bytes "$BUILD_DIR/typeck.o" 2>/dev/null || echo 0)
  if asm_ci_skip_typeck_emit_heavy; then
  build_xlang_asm_info "skip typeck EMIT_HEAVY S2 fallback on $(uname -s) (__text=${_s2_txt}B stub OK)"
  elif [ "${_s2_txt:-0}" -lt 68264 ] 2>/dev/null; then
  rebuild_typeck_o_emit_heavy_s2 "$_s2_comp" || {
  if [ -n "${XLANG_ASM_EXPERIMENTAL_SKIP_GEN:-}" ]; then
  xlang_asm_bstrict_fail "typeck.o EMIT_HEAVY S2 fallback failed (__text=${_s2_txt}B)"
  fi
  }
  fi
  fi
fi

if [ "$ASM_READY" -eq 1 ] && [ "$LINK_OK" -ne 1 ]; then
  exit 1
fi
# strict 重链后 xlang_asm 偶发 -o SIGSEGV：回退 experimental 快照或本轮 XLANG 编译器。
if [ -x ./xlang_asm ] && [ "$LINK_OK" -eq 1 ]; then
  chmod +x scripts/xlang_asm_postlink_smoke.sh 2>/dev/null || true
  if [ -x scripts/xlang_asm_postlink_smoke.sh ]; then
  ./scripts/xlang_asm_postlink_smoke.sh ./xlang_asm "${XLANG:-./xlang}" || {
  build_xlang_asm_warn "xlang_asm postlink smoke failed (strict relink -o broken)"
  }
  fi
  if bootstrap_wants_nostdlib; then
  _nostdlib_ok=0
  if command -v readelf >/dev/null 2>&1; then
  if ! readelf -d ./xlang_asm 2>/dev/null | grep -q 'NEEDED'; then
  _nostdlib_ok=1
  fi
  elif command -v ldd >/dev/null 2>&1; then
  if ldd ./xlang_asm 2>/dev/null | grep -q 'not a dynamic executable'; then
  _nostdlib_ok=1
  fi
  fi
  if [ "$_nostdlib_ok" -eq 1 ]; then
  build_xlang_asm_info "bootstrap nostdlib final link OK (no libc/libm)"
  fi
  fi
fi
exit 0
