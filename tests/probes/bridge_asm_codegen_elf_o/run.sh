#!/usr/bin/env bash
# PLATFORM: SHARED — link-order probe for bridge 5-arg weak asm_codegen_elf_o.
# Product consume is PREFIX asm_asm_codegen_elf_o (user_asm_seed_bridge).
# After deleting the -1 stub AND the weak prefix alias that forwarded
# into it, bridge.o must not define either name; both link orders
# must run as direct=42 alias=42 from the provider.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
INC="$ROOT/compiler/include"
SEED="$ROOT/compiler/seeds/asm_experimental_symbol_bridge.from_x.c"
WORKDIR="${TMPDIR:-/tmp}/xlang_bridge_asm_codegen_elf_o_$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

# Function-sections so unused bridge faces (and their UNDEFs) can be GC'd.
# Darwin cc emits .subsections_via_symbols; -dead_strip is enough there.
uname_s="$(uname -s)"
cflags=(-c -I"$INC" -I"$ROOT/compiler")
ldflags=()
if [ "$uname_s" = "Darwin" ]; then
  ldflags+=(-Wl,-dead_strip)
else
  cflags+=(-ffunction-sections -fdata-sections)
  ldflags+=(-Wl,--gc-sections)
fi
"$CC" "${cflags[@]}" "$SEED" -o "$WORKDIR/bridge.o"
"$CC" "${cflags[@]}" "$(dirname "$0")/provider.c" -o "$WORKDIR/provider.o"
"$CC" "${cflags[@]}" "$(dirname "$0")/caller.c" -o "$WORKDIR/caller.o"

# After the -1 stub and its prefix alias are gone, bridge.o must not
# DEFINE either name (and must not U-ref the unprefixed name — that
# U is what UNDEFd Darwin product g05 when the alias was kept).
for name in asm_codegen_elf_o asm_asm_codegen_elf_o; do
  if nm "$WORKDIR/bridge.o" 2>/dev/null | grep -E " [TWw] (_)?${name}$"; then
    echo "FAIL: bridge.o still defines $name" >&2
    exit 1
  fi
done
if nm "$WORKDIR/bridge.o" 2>/dev/null | grep -E ' [Uu] (_)?asm_codegen_elf_o$'; then
  echo "FAIL: bridge.o still U-refs asm_codegen_elf_o (alias leftover)" >&2
  exit 1
fi

# Same-class PREFIX -1 leftovers (this knife): strict_glue (product
# g05 _GLUE_SUFFIX), x_stubs (experimental xlang_x), verify-selfhost
# generated _x_stubs.c. G.7 complete this probe — do not add a second
# scanner. A definition of PREFIX asm_asm_codegen_elf_o in any of
# these is the first-wins / archive-presatisfy hazard.
leftover_re='^(XLANG_WEAK[[:space:]]+)?int(32_t)?[[:space:]]+asm_asm_codegen_elf_o[[:space:]]*\('
leftover_n=0
for src in \
  "$ROOT/compiler/seeds/runtime_driver_strict_glue_stubs.from_x.c" \
  "$ROOT/compiler/seeds/x_stubs.from_x.c" \
  "$ROOT/compiler/verify-selfhost.sh"
do
  if grep -nE "$leftover_re" "$src"; then
    echo "FAIL: $src still defines PREFIX asm_asm_codegen_elf_o" >&2
    leftover_n=$((leftover_n + 1))
  fi
done
if [ "$leftover_n" -ne 0 ]; then
  exit 1
fi

link_run() {
  local tag="$1"
  shift
  "$CC" "${ldflags[@]}" -o "$WORKDIR/$tag" "$@"
  local out rc
  set +e
  out="$("$WORKDIR/$tag")"
  rc=$?
  set -e
  echo "$tag: $out rc=$rc"
  if [ "$out" != "direct=42 alias=42" ] || [ "$rc" -ne 0 ]; then
    echo "FAIL $tag (want direct=42 alias=42 rc=0)" >&2
    exit 1
  fi
}

# Hazard order: bridge before provider (ELF/Mach-O first weak used to win).
link_run bridge_first "$WORKDIR/bridge.o" "$WORKDIR/provider.o" "$WORKDIR/caller.o"
link_run provider_first "$WORKDIR/provider.o" "$WORKDIR/bridge.o" "$WORKDIR/caller.o"
echo "bridge_asm_codegen_elf_o probe OK leftover_prefix=0"
