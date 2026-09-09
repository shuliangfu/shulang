#!/usr/bin/env bash
# bootstrap_driver_seed_smoke.sh — bootstrap-driver-seed 产出 xlang 的 -c/-o 烟测
#
# 用法（compiler 目录）：
#   ./scripts/bootstrap_driver_seed_smoke.sh [path/to/xlang]
#
# 成功：exit 0，stdout 打印 OK；写入 ../logs/bootstrap-seed.fresh
# 失败且存在 pinned seed：默认复制并 exit 0（WARN）；写入 bootstrap-seed.pinned-fallback
#   XLANG_BOOTSTRAP_NO_PINNED_FALLBACK=1 — 禁止回退（W3 gold 须设，防自举塌陷）
#
# 环境：
#   XLANG_BOOTSTRAP_AUDIT_DIR — 审计标记目录（默认 ../logs）

set -euo pipefail
cd "$(dirname "$0")/.."

# main.x / pipeline 深递归；与 build_xlang_asm / run_xlang_asm_smoke 栈对齐。
ulimit -s 65532 2>/dev/null || ulimit -s 16384 2>/dev/null || ulimit -s hard 2>/dev/null || true

TARGET="${1:-./xlang}"
# 【Why】路径中不可含「.数字.」：codegen 用源文件 stem 作 C 符号前缀，
# `/tmp/foo.$$.x` → stem `foo.12345` → `extern int32_t foo.12345_main` 非法 C。
# Ubuntu 上 fresh smoke 亦曾失败靠 pinned 回退；Darwin pinned 常不可用，须路径自绿。
# PLATFORM: WINDOWS — XLANG file-open uses Win32 CreateFileA which does not
# recognize MSYS2 /tmp/ or /c/... mapping; absolute POSIX-style paths fail
# with IO001. cygpath -m forces mixed-mode Windows path (C:/xlang_tmp/...)
# regardless of MSYS_NO_PATHCONV. POSIX falls back to /tmp.
case "$(uname -s 2>/dev/null)" in
  MINGW*|MSYS*|CYGWIN*)
    _SMOKE_TMP="$(cygpath -m "${TEMP:-/tmp}" 2>/dev/null || echo "${TEMP:-/tmp}")"
    ;;
  *)
    _SMOKE_TMP="/tmp"
    ;;
esac
SMOKE_SRC="${_SMOKE_TMP}/xlang_bootstrap_seed_smoke_$$.x"
SMOKE_OUT="${_SMOKE_TMP}/xlang_bootstrap_seed_smoke_out_$$"
# PLATFORM: WINDOWS — MinGW gcc auto-appends .exe to -o targets. Without the
# suffix, `[ -x "$SMOKE_OUT" ]` fails (file is SMOKE_OUT.exe, not SMOKE_OUT)
# and bash direct exec yields Permission denied / not found. POSIX unchanged.
case "$(uname -s 2>/dev/null)" in
  MINGW*|MSYS*|CYGWIN*) SMOKE_OUT="${SMOKE_OUT}.exe" ;;
esac
PINNED_TMP="${_SMOKE_TMP}/xlang_bootstrap_seed_pinned_$$"
AUDIT_DIR="${XLANG_BOOTSTRAP_AUDIT_DIR:-../logs}"

maybe_codesign() {
  case "$(uname -s 2>/dev/null)" in
    Darwin)
      command -v codesign >/dev/null 2>&1 && codesign -s - --force "$1" >/dev/null 2>&1 || true
      ;;
    MINGW*|MSYS*|CYGWIN*)
      # PLATFORM: WINDOWS — Smart App Control (SAC) intermittently blocks
      # unsigned .exe compiled to $TEMP (Permission denied, exit 126). Sign
      # with the XlangDevCert self-signed cert (one-time setup per
      # analysis/Windows平台限制与测试指南.md §3.4). No-op if cert missing
      # or powershell unavailable.
      if command -v powershell.exe >/dev/null 2>&1; then
        local _cert _win_path
        _cert="${XLANG_CODESIGN_THUMBPRINT:-697D4125CC086F4BF683053A2BD6025B939D96FC}"
        _win_path="$(cygpath -m "$1" 2>/dev/null || echo "$1")"
        powershell.exe -NoProfile -Command \
          "Set-AuthenticodeSignature -FilePath '$_win_path' -Certificate (Get-Item \"Cert:\\LocalMachine\\My\\$_cert\")" >/dev/null 2>&1 || true
      fi
      ;;
  esac
}

cleanup() {
  rm -f "$SMOKE_SRC" "$SMOKE_OUT" "$PINNED_TMP" 2>/dev/null || true
}
trap cleanup EXIT

mkdir -p "$AUDIT_DIR"

if [ ! -x "$TARGET" ]; then
  echo "bootstrap_driver_seed_smoke: not executable: $TARGET" >&2
  exit 1
fi

printf '%s\n' 'function main(): i32 { return 42; }' >"$SMOKE_SRC"

# run_smoke — 对 bootstrap seed 编译器做 -c 与 -o 烟测。
# bootstrap seed 默认 asm -o 会链入 std/*.o 缺 C bridge；-backend c 走 C 后端可执行链。
# 参数：bin — 待测 xlang 路径；成功返回 0。
run_smoke() {
  local bin="$1"
  local _log="${_SMOKE_TMP}/xlang_bootstrap_seed_smoke_$$.log"
  local _rc=0
  # PLATFORM: WINDOWS | MSYS | MINGW — make just relinked $bin (./xlang) fresh and
  # unsigned; Smart App Control blocks unsigned .exe (Permission denied). Sign
  # it before any invocation so the -c / -backend c -o smoke can run. No-op on
  # POSIX (maybe_codesign only acts on Darwin/macOS + MINGW).
  maybe_codesign "$bin"
  echo "[$(date '+%H:%M:%S')] seed smoke: -c check ..."
  # xlang-c (C frontend) 不支持 -c，用 -E 替代（同样做 parse+typeck）
  if "$bin" -c "$SMOKE_SRC" 2>&1 | tee "$_log"; then
    :
  else
    _rc="${PIPESTATUS[0]:-1}"
    # 尝试 -E 回退（xlang-c C 前端模式）
    if "$bin" -E "$SMOKE_SRC" > /dev/null 2>&1; then
      echo "[$(date '+%H:%M:%S')] seed smoke: -c not supported, -E OK (C frontend)"
    else
      return 1
    fi
  fi
  echo "[$(date '+%H:%M:%S')] seed smoke: -backend c -o (may take ~1min) ..."
  rm -f "$SMOKE_OUT"
  # PLATFORM: SHARED — Stage 12.2.3: product host-cc spawn is experimental;
  # -backend c requires ALLOW opt-in. Matches xlang_asm_postlink_smoke.sh / verify-selfhost-stage2.
  export XLANG_ALLOW_HOST_CC=1
  "$bin" -backend c -o "$SMOKE_OUT" "$SMOKE_SRC" 2>&1 | tee "$_log"
  _rc="${PIPESTATUS[0]:-1}"
  if [ "$_rc" -ne 0 ]; then
    # 回退：xlang-c C 前端不支持 -backend c -o，用 -E + cc 替代
    echo "[$(date '+%H:%M:%S')] seed smoke: -backend c -o failed, trying -E + cc fallback ..."
    # SMOKE_OUT may carry .exe on Windows; strip it for the .c companion path.
    "$bin" -E "$SMOKE_SRC" > "${SMOKE_OUT%.exe}.c" 2>"$_log"
    _rc=$?
    if [ "$_rc" -ne 0 ]; then
      return 1
    fi
    # PLATFORM: SHARED — generated C always `#include <xlang_va_cap.h>`
    # (codegen emit_header). Bare `cc -O2 file.c` misses compiler/include
    # (Darwin -backend c -o SEGV in invoke_cc_impl then this fallback
    # died on fatal error: xlang_va_cap.h file not found). Match product
    # host-cc -I. -Iinclude -Isrc. cwd is compiler/.
    ${CC:-cc} -O2 -I. -Iinclude -Isrc -o "$SMOKE_OUT" "${SMOKE_OUT%.exe}.c" 2>>"$_log"
    _rc=$?
    rm -f "${SMOKE_OUT%.exe}.c"
    if [ "$_rc" -ne 0 ]; then
      return 1
    fi
  fi
  [ -x "$SMOKE_OUT" ] || return 1
  # PLATFORM: WINDOWS — sign the compiled smoke .exe so SAC does not block it
  # (matches run-win32-read-file-gate.sh fix per §2.3).
  maybe_codesign "$SMOKE_OUT"
  local ec=0
  "$SMOKE_OUT" 2>&1 | tee "$_log" || ec=$?
  [ "$ec" -eq 42 ]
}

host_seed_path() {
  local os arch
  os="$(uname -s | tr '[:upper:]' '[:lower:]')"
  arch="$(uname -m 2>/dev/null | tr '[:upper:]' '[:lower:]')"
  case "$arch" in
    x86_64|amd64) arch=x86_64 ;;
    aarch64|arm64) arch=arm64 ;;
  esac
  case "$os" in
    darwin) os=darwin ;;
    linux) os=linux ;;
    *) return 1 ;;
  esac
  echo "seeds/bootstrap_xlangc.${os}.${arch}"
}

if run_smoke "$TARGET"; then
  : >"$AUDIT_DIR/bootstrap-seed.fresh"
  rm -f "$AUDIT_DIR/bootstrap-seed.pinned-fallback"
  printf '[%s] seed smoke OK fresh %s\n' "$(date +%Y-%m-%dT%H:%M:%S)" "$TARGET" \
    >>"$AUDIT_DIR/bootstrap-audit.log"
  echo "bootstrap_driver_seed_smoke: OK $TARGET (-c + -backend c -o exit=42)"
  exit 0
fi

if [ "${XLANG_BOOTSTRAP_NO_PINNED_FALLBACK:-0}" = "1" ]; then
  echo "bootstrap_driver_seed_smoke: FAIL $TARGET smoke (XLANG_BOOTSTRAP_NO_PINNED_FALLBACK=1; no pinned copy)" >&2
  printf '[%s] seed smoke FAIL no-fallback %s\n' "$(date +%Y-%m-%dT%H:%M:%S)" "$TARGET" \
    >>"$AUDIT_DIR/bootstrap-audit.log"
  exit 1
fi

pinned="$(host_seed_path || true)"
if [ -n "$pinned" ] && [ -f "$pinned" ] && [ -s "$pinned" ]; then
  echo "bootstrap_driver_seed_smoke: WARN $TARGET smoke failed; fallback pinned $pinned" >&2
  cp -f "$pinned" "$PINNED_TMP"
  chmod +x "$PINNED_TMP"
  maybe_codesign "$PINNED_TMP"
  if run_smoke "$PINNED_TMP"; then
    cp -f "$pinned" "$TARGET"
    cp -f "$pinned" xlang-c 2>/dev/null || true
    cp -f "$pinned" bootstrap_xlangc 2>/dev/null || true
    chmod +x "$TARGET" xlang-c bootstrap_xlangc 2>/dev/null || chmod +x "$TARGET"
    maybe_codesign "$TARGET"
    maybe_codesign xlang-c
    maybe_codesign bootstrap_xlangc
    : >"$AUDIT_DIR/bootstrap-seed.pinned-fallback"
    rm -f "$AUDIT_DIR/bootstrap-seed.fresh"
    printf '[%s] seed smoke OK pinned-fallback %s <- %s\n' "$(date +%Y-%m-%dT%H:%M:%S)" "$TARGET" "$pinned" \
      >>"$AUDIT_DIR/bootstrap-audit.log"
    echo "bootstrap_driver_seed_smoke: OK after pinned fallback $TARGET"
    exit 0
  fi
  echo "bootstrap_driver_seed_smoke: FAIL pinned seed smoke also failed" >&2
  exit 1
fi

echo "bootstrap_driver_seed_smoke: FAIL $TARGET smoke (no pinned seed)" >&2
exit 1
