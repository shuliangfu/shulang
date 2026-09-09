#!/usr/bin/env bash
# PLATFORM: SHARED — hygiene probe for retired mega esc_gate wrappers.
# src/runtime.x + runtime_surface.from_x.c used to export
# driver_stack_esc_gate_{thread_fn,large_stack} as thin forwards to
# never-defined *_impl. Product authority is rt_stack.x.
# After retirement: mega surface must not define those names; rt_stack
# cold seed and product xlang_asm must still provide the 4-symbol face.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
XLANG="${XLANG:-$ROOT/compiler/xlang_asm}"
WORKDIR="${TMPDIR:-/tmp}/xlang_mega_stale_esc_gate_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

# -w: surface is -E codegen (parentheses-equality noise); nm is the gate.
cflags=(-c -w -I"$ROOT/compiler" -I"$ROOT/compiler/include" -I"$ROOT/compiler/src")
"$CC" "${cflags[@]}" "$ROOT/compiler/seeds/runtime_surface.from_x.c" -o "$WORKDIR/surface.o"
"$CC" "${cflags[@]}" "$ROOT/compiler/seeds/rt_stack.from_x.c" -o "$WORKDIR/rt_stack.o"

nm_has() {
  local obj="$1"
  local kind="$2" # TWw or Uu
  local name="$3"
  nm "$obj" 2>/dev/null | grep -E " [$kind] (_)?${name}$" >/dev/null
}

# Mega surface must not mention the retired names (no T/W and no U _impl).
for name in \
  driver_stack_esc_gate_thread_fn \
  driver_stack_esc_gate_large_stack \
  driver_stack_esc_gate_thread_fn_impl \
  driver_stack_esc_gate_large_stack_impl
do
  if nm_has "$WORKDIR/surface.o" 'TWwUu' "$name"; then
    echo "FAIL: runtime_surface.o still has $name" >&2
    nm "$WORKDIR/surface.o" | grep -E "esc_gate" >&2 || true
    exit 1
  fi
done

# rt_stack cold seed is the real body.
for name in driver_stack_esc_gate_thread_fn driver_stack_esc_gate_large_stack; do
  if ! nm_has "$WORKDIR/rt_stack.o" 'TWw' "$name"; then
    echo "FAIL: rt_stack.o missing T $name" >&2
    nm "$WORKDIR/rt_stack.o" | grep -E "esc_gate" >&2 || true
    exit 1
  fi
done

# Product 4/4 face (rt_stack + driver_abi orch / fn-ptr residual).
if [ ! -x "$XLANG" ]; then
  echo "FAIL: missing product $XLANG" >&2
  exit 1
fi
for name in \
  driver_run_stack_esc_gate_on_large_stack \
  driver_stack_esc_gate_large_stack \
  driver_stack_esc_gate_thread_fn \
  driver_stack_esc_gate_thread_fn_ptr
do
  if ! nm_has "$XLANG" 'TWw' "$name"; then
    echo "FAIL: product xlang_asm missing T $name" >&2
    nm "$XLANG" | grep -E "esc_gate" >&2 || true
    exit 1
  fi
done

echo "mega_stale_esc_gate probe OK surface=0 rt_stack=2 product=4"
