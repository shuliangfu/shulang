#!/usr/bin/env bash
# Cap 10.7.1 language slice7–18: va_* → Cap (-E/host-cc) + product -backend c -o + default asm -o.
# slice7–10: Cap rewrite/arity/host-cc/preamble; slice11: invoke_cc Cap -I;
# slice12: asm Cap va_start/end/va_arg_i32; slice13: asm Cap va_arg_i64/ptr;
# slice14: typed turbofish va_arg<T>(ap); slice15: aarch64 asm Cap cross-emit;
# slice16: va_arg<f32>/va_arg<f64> (XMM/NEON + C float→double promote).
# slice17: GP stack extras beyond 6 SysV GP (11/22 in r8/r9, 33/44 at [rbp+16]).
# slice18: mixed GP+FP overflow on the shared stack (asm -o + host-C of mixed).
# PLATFORM: SHARED — L2 probe; Ubuntu gold. Does not run xlang check.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
XLANG="${XLANG:-$ROOT/compiler/xlang}"
SRC="$ROOT/tests/sys/lang_va_cap_builtins_smoke.x"
OUT_C="/tmp/xlang_lang_va_cap_builtins_$$.c"
OUT_BIN="/tmp/xlang_lang_va_cap_builtins_$$"
OUT_PROD="/tmp/xlang_lang_va_cap_builtins_prod_$$"
trap 'rm -f "$OUT_C" "$OUT_BIN" "$OUT_PROD"' EXIT

if [[ ! -x "$XLANG" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=1 reason=no_xlang" >&2
  exit 1
fi

if ! "$XLANG" -E "$SRC" >"$OUT_C" 2>/tmp/xlang_lang_va_cap_builtins_err.$$; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=emit" >&2
  tail -40 /tmp/xlang_lang_va_cap_builtins_err.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_builtins_err.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_builtins_err.$$

# Cap header must appear in -E prologue.
if ! grep -F '#include <xlang_va_cap.h>' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_cap_header" >&2
  head -40 "$OUT_C" >&2 || true
  exit 1
fi

# VaList local → xlang_va_list spelling.
if ! grep -E 'xlang_va_list[[:space:]]+ap' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_valist" >&2
  grep -n 'ap\|VaList\|va_list' "$OUT_C" | head -30 >&2 || true
  exit 1
fi

# Builtin rewrites (must not leave bare va_start( as a C call to undeclared fn).
if ! grep -F 'xlang_va_start(' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_start" >&2
  grep -n 'va_start\|xlang_va_' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
if ! grep -F 'xlang_va_arg(' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_arg" >&2
  grep -n 'va_arg\|xlang_va_' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
if ! grep -F 'xlang_va_end(' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_end" >&2
  grep -n 'va_end\|xlang_va_' "$OUT_C" | head -30 >&2 || true
  exit 1
fi

# Call site must emit trailing variadic args (slice8 arity + slice13 i64/ptr + slice17 stack extras).
if ! grep -E 'lang_va_cap_probe\([^)]*42' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_variadic_call" >&2
  grep -n 'lang_va_cap_probe' "$OUT_C" | head -20 >&2 || true
  exit 1
fi
# slice17: stack extras 33/44 must appear at the call site (host-C and asm).
# Do not use [^)]* — host-C emits &(m) which contains ')' before 33.
if ! grep -E 'lang_va_cap_probe\(.*33' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_stack_extra" >&2
  grep -n 'lang_va_cap_probe' "$OUT_C" | head -20 >&2 || true
  exit 1
fi
# slice13–14: typed va_arg<T> / helpers must rewrite to Cap macros (not bare va_arg calls).
if ! grep -F 'int64_t)(xlang_va_arg(ap, int64_t)' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_arg_i64" >&2
  grep -n 'va_arg\|xlang_va_arg' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
if ! grep -F 'uint8_t *)(xlang_va_arg(ap, uint8_t *)' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_arg_ptr" >&2
  grep -n 'va_arg\|xlang_va_arg' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
# slice16: f32 uses C default promotion (va_arg double, cast float); f64 is double.
if ! grep -F 'float)(xlang_va_arg(ap, double)' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_arg_f32" >&2
  grep -n 'va_arg\|xlang_va_arg' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
if ! grep -F 'double)(xlang_va_arg(ap, double)' "$OUT_C" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_va_arg_f64" >&2
  grep -n 'va_arg\|xlang_va_arg' "$OUT_C" | head -30 >&2 || true
  exit 1
fi
# Five va_arg<i32> in one TU must share one host-C definition (combo dedup).
n_va_i32="$(grep -c 'int32_t va_arg__VaList_i32(' "$OUT_C" || true)"
if [[ "${n_va_i32}" -ne 1 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=dup_va_arg_i32 n=${n_va_i32} want=1" >&2
  grep -n 'va_arg__VaList_i32' "$OUT_C" | head -20 >&2 || true
  exit 1
fi

# Cap 10.7.1 slice9: host-cc + run — Cap macros must be real (expect exit 42).
CC_BIN="${CC:-cc}"
if ! "$CC_BIN" -std=gnu11 -O0 -Wall -I"$ROOT/compiler/include" -o "$OUT_BIN" "$OUT_C" \
  2>/tmp/xlang_lang_va_cap_builtins_cc.$$; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=host_cc" >&2
  cat /tmp/xlang_lang_va_cap_builtins_cc.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_builtins_cc.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_builtins_cc.$$
if [[ ! -x "$OUT_BIN" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_exe" >&2
  exit 1
fi
set +e
"$OUT_BIN"
rc=$?
set -e
if [[ "$rc" -ne 42 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=run_rc rc=$rc want=42" >&2
  exit 1
fi

# Cap 10.7.1 slice10: product -o preamble must fold Cap va header (N=224 slot).
if ! grep -F 'xlang_va_cap.h' "$ROOT/compiler/seeds/rt_preamble.from_x.c" >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=no_preamble_cap" >&2
  exit 1
fi

# Cap 10.7.1 slice11: product opt-in host-C -o must resolve Cap headers via invoke_cc -I.
# PC: C is opt-in (ALLOW_HOST_CC + -backend c); default asm Cap va remains residual.
rm -f "$OUT_PROD"
set +e
XLANG_ALLOW_HOST_CC=1 "$XLANG" build -backend c -o "$OUT_PROD" "$SRC" \
  >/tmp/xlang_lang_va_cap_builtins_prod.$$ 2>&1
prod_rc=$?
set -e
if [[ "$prod_rc" -ne 0 ]] || [[ ! -x "$OUT_PROD" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=product_c_o" >&2
  cat /tmp/xlang_lang_va_cap_builtins_prod.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_builtins_prod.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_builtins_prod.$$
set +e
"$OUT_PROD"
prod_run=$?
set -e
if [[ "$prod_run" -ne 42 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=product_run_rc rc=$prod_run want=42" >&2
  exit 1
fi

# Cap 10.7.1 slice12–14: default product asm -o (no ALLOW_HOST_CC) must exit 42.
# slice14: no UNDEF for va_arg / va_arg_i64 / va_arg_ptr either.
OUT_ASM="/tmp/xlang_lang_va_cap_builtins_asm_$$"
trap 'rm -f "$OUT_C" "$OUT_BIN" "$OUT_PROD" "$OUT_ASM"' EXIT
rm -f "$OUT_ASM"
set +e
"$XLANG" -o "$OUT_ASM" "$SRC" >/tmp/xlang_lang_va_cap_builtins_asm.$$ 2>&1
asm_rc=$?
set -e
if [[ "$asm_rc" -ne 0 ]] || [[ ! -x "$OUT_ASM" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=product_asm_o" >&2
  cat /tmp/xlang_lang_va_cap_builtins_asm.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_builtins_asm.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_builtins_asm.$$
if nm -u "$OUT_ASM" 2>/dev/null | grep -E 'U (va_start|va_end|va_arg_i32|va_arg_i64|va_arg_ptr|va_arg)$' >/dev/null 2>&1; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=asm_undef_va" >&2
  nm -u "$OUT_ASM" 2>/dev/null | grep -E 'va_' >&2 || true
  exit 1
fi
set +e
"$OUT_ASM"
asm_run=$?
set -e
if [[ "$asm_run" -ne 42 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=asm_run_rc rc=$asm_run want=42" >&2
  exit 1
fi

# Cap 10.7.1 slice15: aarch64 Cap va cross-emit (Ubuntu x86 gold = opcode scan, no qemu).
# Distinctive LE: ldr x0,[x3]=f9400060; str x0,[x3]=f9000060; sub x0,x0,#8=d1002000.
OUT_A64="/tmp/xlang_lang_va_cap_builtins_a64_$$.o"
trap 'rm -f "$OUT_C" "$OUT_BIN" "$OUT_PROD" "$OUT_ASM" "$OUT_A64"' EXIT
rm -f "$OUT_A64"
set +e
"$XLANG" -target aarch64-linux-gnu -o "$OUT_A64" "$SRC" >/tmp/xlang_lang_va_cap_builtins_a64.$$ 2>&1
a64_rc=$?
set -e
if [[ "$a64_rc" -ne 0 ]] || [[ ! -f "$OUT_A64" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=aarch64_emit" >&2
  cat /tmp/xlang_lang_va_cap_builtins_a64.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_builtins_a64.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_builtins_a64.$$
a64_ok=0
if grep -a -q $'\x60\x00\x40\xf9' "$OUT_A64" 2>/dev/null; then a64_ok=1; fi
if grep -a -q $'\x60\x00\x00\xf9' "$OUT_A64" 2>/dev/null; then a64_ok=$((a64_ok + 1)); fi
if grep -a -q $'\x00\x20\x00\xd1' "$OUT_A64" 2>/dev/null; then a64_ok=$((a64_ok + 1)); fi
if [[ "$a64_ok" -lt 2 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=aarch64_no_cap_opcodes a64_ok=$a64_ok" >&2
  xxd "$OUT_A64" 2>/dev/null | head -20 >&2 || true
  exit 1
fi

# Cap 10.7.1 slice18: mixed GP+FP overflow — product asm -o + host-C of two
# va_arg<f64> (one va_arg__VaList_f64; combo dedup).
SRC_MIX="$ROOT/tests/sys/lang_va_cap_mixed_overflow_smoke.x"
OUT_MIX="/tmp/xlang_lang_va_cap_mixed_$$"
OUT_MIX_C="/tmp/xlang_lang_va_cap_mixed_$$.c"
OUT_MIX_HOST="/tmp/xlang_lang_va_cap_mixed_host_$$"
trap 'rm -f "$OUT_C" "$OUT_BIN" "$OUT_PROD" "$OUT_ASM" "$OUT_A64" "$OUT_MIX" "$OUT_MIX_C" "$OUT_MIX_HOST"' EXIT
rm -f "$OUT_MIX"
set +e
"$XLANG" -o "$OUT_MIX" "$SRC_MIX" >/tmp/xlang_lang_va_cap_mixed.$$ 2>&1
mix_rc=$?
set -e
if [[ "$mix_rc" -ne 0 ]] || [[ ! -x "$OUT_MIX" ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=mixed_asm_o" >&2
  cat /tmp/xlang_lang_va_cap_mixed.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_mixed.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_mixed.$$
set +e
"$OUT_MIX"
mix_run=$?
set -e
if [[ "$mix_run" -ne 42 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=mixed_run_rc rc=$mix_run want=42" >&2
  exit 1
fi
if ! "$XLANG" -E "$SRC_MIX" >"$OUT_MIX_C" 2>/tmp/xlang_lang_va_cap_mixed_e.$$; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=mixed_emit" >&2
  tail -40 /tmp/xlang_lang_va_cap_mixed_e.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_mixed_e.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_mixed_e.$$
n_va_f64="$(grep -c 'double va_arg__VaList_f64(' "$OUT_MIX_C" || true)"
if [[ "${n_va_f64}" -ne 1 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=dup_va_arg_f64 n=${n_va_f64} want=1" >&2
  grep -n 'va_arg__VaList_f64' "$OUT_MIX_C" | head -20 >&2 || true
  exit 1
fi
if ! "$CC_BIN" -std=gnu11 -O0 -Wall -I"$ROOT/compiler/include" -o "$OUT_MIX_HOST" "$OUT_MIX_C" \
  2>/tmp/xlang_lang_va_cap_mixed_cc.$$; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=mixed_host_cc" >&2
  cat /tmp/xlang_lang_va_cap_mixed_cc.$$ >&2 || true
  rm -f /tmp/xlang_lang_va_cap_mixed_cc.$$
  exit 1
fi
rm -f /tmp/xlang_lang_va_cap_mixed_cc.$$
set +e
"$OUT_MIX_HOST"
mix_host_run=$?
set -e
if [[ "$mix_host_run" -ne 42 ]]; then
  echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=fail run=0 obs=0 skip=0 reason=mixed_host_run_rc rc=$mix_host_run want=42" >&2
  exit 1
fi

host="$(uname -s 2>/dev/null || echo unknown)/$(uname -m 2>/dev/null || echo unknown)"
echo "xlang: [XLANG_LANG_VA_CAP_BUILTINS] status=ok run=1 obs=0 skip=0 host=$host"
