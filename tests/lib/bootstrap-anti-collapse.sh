#!/usr/bin/env bash
# bootstrap-anti-collapse.sh — 自举塌陷检测（防鸡生蛋链静默断裂）
#
# 塌陷定义：表面 A-09 hash 绿 / gate EXIT=0，但中间某步用 pinned seed 或旧编译器
# 复制冒充 fresh 产物，导致 Stage0→1→2 循环实际未发生。
#
# 典型塌陷路径：
#   1. make bootstrap-driver-seed 烟测失败 → cp seeds/bootstrap_xlangc.* 覆盖 ./xlang
#   2. build_xlang_asm postlink 失败 → cp ./xlang / xlang_asm.experimental 覆盖 ./xlang_asm
#   3. stage1==stage2==pinned 同 SHA256 → 哈希金标准绿但无真二遍编译
#
# 用法（仓库根，source 后调用）：
#   source tests/lib/bootstrap-anti-collapse.sh
#   bootstrap_anti_collapse_reset_audit
#   bootstrap_anti_collapse_check compiler/xlang_asm_stage1 compiler/xlang_asm2

# 审计标记目录（compiler 内脚本写 ../logs；gate 在仓库根用 logs/）。
bootstrap_anti_collapse_audit_dir() {
  if [ -n "${XLANG_BOOTSTRAP_AUDIT_DIR:-}" ]; then
    echo "$XLANG_BOOTSTRAP_AUDIT_DIR"
    return 0
  fi
  local root
  root="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/../.." && pwd)"
  echo "$root/logs"
}

# bootstrap_audit_log — 追加一行带时间戳的审计日志。
# 参数：msg — 日志正文。
bootstrap_audit_log() {
  local dir msg
  dir="$(bootstrap_anti_collapse_audit_dir)"
  msg="$1"
  mkdir -p "$dir"
  printf '[%s] %s\n' "$(date +%Y-%m-%dT%H:%M:%S)" "$msg" >>"$dir/bootstrap-audit.log"
}

# bootstrap_anti_collapse_reset_audit — 新一次 gold 跑前清空本轮审计标记。
bootstrap_anti_collapse_reset_audit() {
  local dir
  dir="$(bootstrap_anti_collapse_audit_dir)"
  mkdir -p "$dir"
  rm -f \
    "$dir/bootstrap-seed.fresh" \
    "$dir/bootstrap-seed.pinned-fallback" \
    "$dir/bootstrap-postlink.fresh" \
    "$dir/bootstrap-postlink.experimental-fallback" \
    "$dir/bootstrap-postlink.compiler-fallback"
  : >"$dir/bootstrap-audit.log" 2>/dev/null || true
  bootstrap_audit_log "audit reset"
}

# bootstrap_hash_file — 计算文件 SHA256（sha256sum / shasum 兼容）。
# 参数：path — 文件路径；stdout 输出 hex digest。
bootstrap_hash_file() {
  local f="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$f" | awk '{print $1}'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$f" | awk '{print $1}'
  else
    echo "bootstrap-anti-collapse: no sha256sum/shasum" >&2
    return 1
  fi
}

# bootstrap_host_pinned_seed — 按宿主 OS/arch 返回 seeds/bootstrap_xlangc 路径。
bootstrap_host_pinned_seed() {
  local os arch root
  root="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/../.." && pwd)"
  os="$(uname -s | tr '[:upper:]' '[:lower:]')"
  arch="$(uname -m 2>/dev/null | tr '[:upper:]' '[:lower:]')"
  case "$arch" in
    x86_64|amd64) arch=x86_64 ;;
    aarch64|arm64) arch=arm64 ;;
  esac
  case "$os" in
    darwin) os=darwin ;;
    linux) os=linux ;;
    freebsd) os=freebsd ;;
    *) return 1 ;;
  esac
  echo "$root/compiler/seeds/bootstrap_xlangc.${os}.${arch}"
}

# bootstrap_anti_collapse_check — 在 gen1/gen2 后断言无塌陷；失败 exit 1。
# 参数：
#   stage1 — gen1 产物路径（默认 compiler/xlang_asm_stage1）
#   stage2 — gen2 产物路径（默认 compiler/xlang_asm2）
#   seed   — Stage0 ./xlang 路径（默认 compiler/xlang）
# 环境：
#   XLANG_BOOTSTRAP_ANTI_COLLAPSE_FAIL=1 — 硬失败（W3 gold 默认）
#   XLANG_BOOTSTRAP_ALLOW_PINNED_FALLBACK=1 — 允许 seed 回退 pinned（本地调试）
#   XLANG_BOOTSTRAP_ALLOW_POSTLINK_FALLBACK=1 — 允许 postlink 回退（本地调试）。
#     Same flag is the produce-point gate for compiler-fallback copy in
#     xlang_asm_postlink_smoke.sh (G.7 complete; default no overwrite).
bootstrap_anti_collapse_check() {
  local stage1="${1:-compiler/xlang_asm_stage1}"
  local stage2="${2:-compiler/xlang_asm2}"
  local seed="${3:-compiler/xlang}"
  local dir pinned h1 h2 hs hp fail=0

  dir="$(bootstrap_anti_collapse_audit_dir)"

  if [ ! -f "$stage1" ] || [ ! -f "$stage2" ]; then
    echo "bootstrap-anti-collapse FAIL: missing stage binary" >&2
    return 1
  fi

  # --- 审计标记：本轮是否发生 silent fallback ---
  if [ -f "$dir/bootstrap-seed.pinned-fallback" ] \
    && [ "${XLANG_BOOTSTRAP_ALLOW_PINNED_FALLBACK:-0}" != "1" ] \
    && [ "${XLANG_BOOTSTRAP_COLD_START_PINNED:-0}" != "1" ]; then
    echo "bootstrap-anti-collapse FAIL: seed smoke used pinned fallback (鸡生蛋链断裂风险)" >&2
    echo "  hint: 若 intentional 冷启动，设 XLANG_BOOTSTRAP_COLD_START_PINNED=1 并确保 gen1!=pinned" >&2
    bootstrap_audit_log "FAIL seed pinned fallback"
    fail=1
  fi

  if [ -f "$dir/bootstrap-seed.pinned-fallback" ] \
    && [ "${XLANG_BOOTSTRAP_COLD_START_PINNED:-0}" = "1" ]; then
    echo "bootstrap-anti-collapse: explicit cold-start pinned seed (须 gen1!=pinned 证真编译)"
    bootstrap_audit_log "INFO cold-start pinned allowed"
  fi

  if [ -f "$dir/bootstrap-postlink.compiler-fallback" ] \
    && [ "${XLANG_BOOTSTRAP_ALLOW_POSTLINK_FALLBACK:-0}" != "1" ]; then
    echo "bootstrap-anti-collapse FAIL: postlink copied compiler over xlang_asm" >&2
    bootstrap_audit_log "FAIL postlink compiler fallback"
    fail=1
  fi

  if [ -f "$dir/bootstrap-postlink.experimental-fallback" ] \
    && [ "${XLANG_BOOTSTRAP_ALLOW_POSTLINK_FALLBACK:-0}" != "1" ]; then
    echo "bootstrap-anti-collapse FAIL: postlink used experimental snapshot (非 strict 链产物)" >&2
    bootstrap_audit_log "FAIL postlink experimental fallback"
    fail=1
  fi

  h1="$(bootstrap_hash_file "$stage1")"
  h2="$(bootstrap_hash_file "$stage2")"
  hs="$(bootstrap_hash_file "$seed")"
  pinned="$(bootstrap_host_pinned_seed 2>/dev/null || true)"
  hp=""
  if [ -n "$pinned" ] && [ -f "$pinned" ]; then
    hp="$(bootstrap_hash_file "$pinned")"
  fi

  echo "bootstrap-anti-collapse: stage1 sha256=$h1 bytes=$(wc -c <"$stage1" | tr -d ' ')"
  echo "bootstrap-anti-collapse: stage2 sha256=$h2 bytes=$(wc -c <"$stage2" | tr -d ' ')"
  echo "bootstrap-anti-collapse: seed   sha256=$hs bytes=$(wc -c <"$seed" | tr -d ' ')"

  # stage1 必须与 seed 不同：gen1 须真正编译出新一代二进制。
  if [ "$h1" = "$hs" ]; then
    echo "bootstrap-anti-collapse FAIL: stage1==seed (gen1 未产出新编译器，可能 postlink 复制)" >&2
    bootstrap_audit_log "FAIL stage1==seed"
    fail=1
  fi

  # 三者同体 = 纯 pinned 复制假闭环。
  if [ -n "$hp" ] && [ "$h1" = "$hp" ] && [ "$h1" = "$hs" ]; then
    echo "bootstrap-anti-collapse FAIL: stage1==seed==pinned (假自举 fixed point)" >&2
    bootstrap_audit_log "FAIL triple equal pinned"
    fail=1
  fi

  # A-09 须一致（与 run-stage2-hash-gate 对齐）。
  if [ "$h1" != "$h2" ]; then
    echo "bootstrap-anti-collapse FAIL: stage1!=stage2 SHA256 (非 fixed point)" >&2
    bootstrap_audit_log "FAIL stage1!=stage2"
    fail=1
  fi

  if [ "$fail" -ne 0 ]; then
    if [ "${XLANG_BOOTSTRAP_ANTI_COLLAPSE_FAIL:-1}" = "1" ]; then
      return 1
    fi
    echo "bootstrap-anti-collapse WARN (XLANG_BOOTSTRAP_ANTI_COLLAPSE_FAIL=0)" >&2
    return 0
  fi

  if [ -f "$dir/bootstrap-seed.fresh" ]; then
    echo "bootstrap-anti-collapse: seed built fresh (no pinned fallback)"
  else
    echo "bootstrap-anti-collapse WARN: no bootstrap-seed.fresh marker (seed may pre-exist)" >&2
  fi

  echo "bootstrap-anti-collapse OK (no collapse detected; SHA256 fixed point)"
  bootstrap_audit_log "OK stage1=$h1"
  return 0
}
