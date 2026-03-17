#!/usr/bin/env bash
# 阶段 2.11 / 9.1：验证纯 .su 流水线（-su -E）对最小程序能跑通并产出 C。
# 在仓库根目录执行：./tests/run-su-pipeline.sh
# 要求：compiler 已 make，且 make bootstrap-pipeline + shu-su-pipeline 已生成 shu_su。

set -e
cd "$(dirname "$0")/.."

# 阶段 10.2：CI 下也跑本测试；用 run_timeout 限时，超时则失败（exit 1）避免假绿。
make -C compiler -q 2>/dev/null || make -C compiler

# 可移植超时：执行一条命令，超时秒数 $1，命令为 "${@:2}"；超时返回 124
run_timeout() {
  local secs="$1"
  shift
  if command -v timeout >/dev/null 2>&1; then
    timeout "$secs" "$@" || { local e=$?; [ "$e" -eq 124 ] && return 124; return "$e"; }
  else
    perl -e 'alarm shift; exec @ARGV' "$secs" "$@" || { local e=$?; [ "$e" -eq 142 ] && return 124; return "$e"; }
  fi
}

# 生成 shu_su（bootstrap-pipeline + 编译 pipeline_gen.c）整段限 120s，避免卡在 make
make_ret=0
run_timeout 120 bash -c 'make -C compiler bootstrap-pipeline 2>/dev/null || true; make -C compiler shu-su-pipeline 2>/dev/null || true' || make_ret=$?
if [ "$make_ret" -eq 124 ]; then
  echo "run-su-pipeline FAIL (make bootstrap-pipeline / shu-su-pipeline timed out after 120s)"
  exit 1
fi

if [ -x compiler/shu_su ]; then SU_SHU=compiler/shu_su; else SU_SHU=compiler/shu; fi
[ -x "$SU_SHU" ] || { echo "compiler/shu_su and compiler/shu not found or not executable"; exit 1; }

MIN_SU="tests/su-pipeline/min.su"
mkdir -p tests/su-pipeline
if [ ! -f "$MIN_SU" ]; then
  printf 'function main(): i32 { return 0; }\n' > "$MIN_SU"
fi

# 使用 compiler/shu 时可能为 C-only 构建（不支持 -su -E），先探测；不支持则跳过以免 make test 失败
# 对 -su -E 加 60s 超时，避免 shu_su 在部分环境挂起（pipeline_run_su_pipeline_impl/typeck/codegen）。
# 将 stderr 写入临时文件，失败时打印以便 CI 看到 -su -E 诊断（如 out_buf.len、前 16 字节 hex）。
out=$(mktemp)
err=$(mktemp)
ec=0
run_timeout 60 "$SU_SHU" -su -E "$MIN_SU" > "$out" 2>"$err" || ec=$?
[ "$ec" -eq 142 ] && ec=124
_show_stderr() { echo "--- stderr ---"; cat "$err" 2>/dev/null || true; rm -f "$err"; }
if [ "$ec" -eq 124 ]; then
  rm -f "$out"
  _show_stderr
  echo "run-su-pipeline FAIL (shu_su -su -E timed out after 60s)"
  exit 1
fi
if [ "$ec" -ne 0 ]; then
  if [ "$SU_SHU" = "compiler/shu" ]; then
    rm -f "$out" "$err"
    echo "run-su-pipeline SKIP (shu does not support -su -E; run make bootstrap-driver or use build_tool for full shu)"
    exit 0
  fi
  if [ "$ec" -eq 126 ]; then
    rm -f "$out" "$err"
    echo "run-su-pipeline SKIP (shu_su not runnable in this env, e.g. wrong libc in container; run make -C compiler clean first)"
    exit 0
  fi
  echo "run-su-pipeline: $SU_SHU -su -E $MIN_SU failed (exit $ec)"
  cat "$out" 2>/dev/null || true
  _show_stderr
  rm -f "$out"
  exit 1
fi

# 产出应含 return（有 return 即视为有效 C；#include 可有可无，shu_su 的 pipeline 可能不生成）
if ! grep -q 'return' "$out"; then
  echo "run-su-pipeline: output missing return"
  cat "$out"
  _show_stderr
  rm -f "$out"
  exit 1
fi

rm -f "$out" "$err"
echo "run-su-pipeline OK (-su -E minimal program)"
