#!/usr/bin/env bash
# PLATFORM: SHARED — link-order probe for bridge 4-arg weak asm_codegen_ast.
# Bridge.o first, then a weak provider that returns 42. After deleting the
# bridge -1 stub, both orders must run as direct=42 alias=42.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
CC="${CC:-cc}"
INC="$ROOT/compiler/include"
SEED="$ROOT/compiler/seeds/asm_experimental_symbol_bridge.from_x.c"
WORKDIR="${TMPDIR:-/tmp}/xlang_bridge_asm_codegen_ast_$$"
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

# After the -1 stub is gone, bridge.o must not DEFINE asm_codegen_ast.
if nm "$WORKDIR/bridge.o" 2>/dev/null | grep -E ' [TWw] (_)?asm_codegen_ast$'; then
  echo "FAIL: bridge.o still defines asm_codegen_ast" >&2
  exit 1
fi
if ! nm "$WORKDIR/bridge.o" 2>/dev/null | grep -E ' [Uu] (_)?asm_codegen_ast$'; then
  echo "FAIL: bridge.o missing U asm_codegen_ast (prefix aliases should ref it)" >&2
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
echo "bridge_asm_codegen_ast probe OK"
