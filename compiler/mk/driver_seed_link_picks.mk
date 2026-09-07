# driver_seed_link_picks.mk — wave819 · 11.3.1 B7B · wave924 link-export
#
# Single-authority seed *link picks* for bootstrap-driver-seed / composites / relink:
#   PREPROCESS_LINK_O / DRIVER_SEED_PREPROCESS_REBUILD
#   AST_POOL_L5_BRIDGE_O
#   RELINK_XLANG_GLUE_SUFFIX / DRIVER_SEED_GLUE_PREFIX / DRIVER_SEED_GLUE_SUFFIX
#   LSP_DIAG_LINK_O
#   LEXER_LINK_O / AST_LINK_O
#   MAIN_LINK_O / MAIN_LINK_REBUILD / MAIN_LINK_FLAGS
#   LD_R_MULTIDEF_FLAGS / ASM_GLUE_DUP_LDFLAGS  (wave924: moved from Makefile inline)
#   SEED_LINK_PURE_OK / SEED_LINK_ENTRY / SEED_LINK_LD_TAIL  (wave924: moved from Makefile)
#
# Used by:
#   - compiler/Makefile seed link / relink / xlang-x / no-c frontend recipes
#   - mk/driver_seed_composites.mk (DRIVER_SEED_OBJS / PREREQS expand MAIN/LEXER/AST)
#   - driver_seed_obj_catalog.sh shell parse (0-make; G.7)
#   - driver_seed_obj_catalog.sh --link-export phase1|final (wave924: SEED_LINK_* dump)
#
# G.7: Definitions live only here. Makefile must include, not re-assign the
# product inventory. Shell host-defaults must not hardcode a second
# MAIN_LINK_O / LEXER_LINK_O / LSP_DIAG_LINK_O list (parse this mk instead).
#
# wave819: moved out of compiler/Makefile inline ifeq body (list residual of
# b7b_lists_in_mk). NOT physical delete — thin edges + other mk lists +
# std_core product graph + OBJS_CORE archaeology list still residual.
#
# PLATFORM: SHARED — leaf basenames portable; branch picks use UNAME / WIN host.
# catalog_parse_mk supports only ifeq/else/endif (not "else ifeq", not $(filter)).
# Nested ifeq mirrors historical Makefile order:
#   LEGACY_MAIN_C → Linux → Darwin → XLANG_IS_WIN_HOST → main_driver fallback.
# Linux crt0 only on UNAME_M=x86_64 (historical; amd64 falls to main_driver).
# Darwin arm64/aarch64 → crt0_arm64; x86_64/amd64 → crt0_darwin_x86_64.
#
# Stubs note (Windows-critical, kept for archaeology):
#   runtime_driver_strict_glue_stubs.o lives in GLUE_SUFFIX (link END), not
#   SUPPORT_EXTRA (wave818). PLATFORM: SHARED — PE first-wins multidef.

# G-02a: preprocess.c deleted; preprocess path is preprocess.x (preprocess_x.o).
PREPROCESS_LINK_O =
DRIVER_SEED_PREPROCESS_REBUILD =

# parser labeled-name write path (parser_x.o / bridge depend on stubs).
AST_POOL_L5_BRIDGE_O = src/runtime_driver_strict_glue_stubs.o

# Glue suffix at link END (real impls first; stubs fill missing C frontend).
# ASM_GLUE_STANDALONE_O comes from mk/driver_seed_r_lists.mk (include earlier).
# wave304 G.7 8.3.6: strict_minimal seed shell retired (0 T; product unlinked).
# PLATFORM: SHARED freestanding 8.3.6 shell retire.
RELINK_XLANG_GLUE_SUFFIX = src/runtime_driver_strict_glue_stubs.o
DRIVER_SEED_GLUE_PREFIX =
# wave304/309: stubs only (strict_minimal + standalone shells retired).
DRIVER_SEED_GLUE_SUFFIX = src/runtime_driver_strict_glue_stubs.o

# LSP_DIAG_LINK_O: fmt needs real xlang_format_x_document (not stubs_no_c).
LSP_DIAG_LINK_O = src/lsp/lsp_diag.o

# E-03 v2 lexer/ast: LEGACY C frontend or LEGACY_SEED_LEXER_AST → C objs;
# product default and XLANG_NO_C_SEED_LINK=1 both leave empty (X pipeline).
ifeq ($(XLANG_LEGACY_C_FRONTEND),1)
LEXER_LINK_O = src/lexer/lexer.o
AST_LINK_O = src/ast/ast_seed.o
else
ifeq ($(XLANG_LEGACY_SEED_LEXER_AST),1)
LEXER_LINK_O = src/lexer/lexer.o
AST_LINK_O = src/ast/ast_seed.o
else
LEXER_LINK_O =
AST_LINK_O =
endif
endif

# E-04: platform crt0 replaces main_driver.o when driver_x.o exports main_entry.
# PLATFORM: LINUX x86_64 · MACOS arm64/x86_64 · WINDOWS mingw · else main_driver.
ifeq ($(XLANG_LEGACY_MAIN_C),1)
MAIN_LINK_O = src/main_driver.o
MAIN_LINK_REBUILD = src/main_driver.o
MAIN_LINK_FLAGS =
else
ifeq ($(UNAME_S),Linux)
ifeq ($(UNAME_M),x86_64)
# PLATFORM: LINUX x86_64 — freestanding pure-ld seed/product face.
# crt0 provides _start; freestanding_io provides xlang_sys_* (write/read/open/mmap/…).
# driver_x (std.sys leaf) UNDEFs those symbols; pure-ld with only -lc cannot resolve
# them (libc has write, not xlang_sys_write). L4 wipe + cold bootstrap-driver-seed
# phase1 pure-ld fails without freestanding in the bag; soft L2 can hide this when
# old product bins survive. G.7: companion lives on MAIN_LINK (same face as crt0),
# so DRIVER_SEED_OBJS / PREREQS / PHASE1 / FINAL expand it once — not a second bag.
# freestanding_io_x86_64.o is also in DRIVER_SEED_CRT0_OBJS (try-r2 rebuild).
MAIN_LINK_O = src/asm/crt0_x86_64.o src/asm/freestanding_io_x86_64.o
MAIN_LINK_REBUILD = src/asm/crt0_x86_64.o src/asm/freestanding_io_x86_64.o
# Match build_xlang_asm.sh bootstrap_entry_ldflags: -no-pie required with crt0.
MAIN_LINK_FLAGS = -no-pie -e _start -nostartfiles
else
MAIN_LINK_O = src/main_driver.o
MAIN_LINK_REBUILD = src/main_driver.o
MAIN_LINK_FLAGS =
endif
else
ifeq ($(UNAME_S),Darwin)
# PLATFORM: MACOS — runtime_asm_io_stubs.o (XLANG_WEAK io twin bag) provides
# xlang_sys_write/read/writev for src/runtime_driver_no_c.o: rt_entry.x is
# SHARED and since Cap 9.1.8 declares `export extern xlang_sys_write` (raw
# write leaf). freestanding_io strong twin is Linux-x86_64-only asm, so the
# Darwin seed phase1/final pure-ld fails U _xlang_sys_write from
# _rt_entry_strlen without this slot. G.7: same face as the Linux
# MAIN_LINK_O freestanding_io slot above and as the g05_relink_env.sh
# Darwin MAIN_LINK_O slot (weak twin loses to any strong twin when both
# are linked).
ifeq ($(UNAME_M),arm64)
MAIN_LINK_O = src/asm/crt0_arm64.o runtime_asm_io_stubs.o
MAIN_LINK_REBUILD = src/asm/crt0_arm64.o runtime_asm_io_stubs.o
MAIN_LINK_FLAGS = -e _start -nostartfiles
else
ifeq ($(UNAME_M),aarch64)
MAIN_LINK_O = src/asm/crt0_arm64.o runtime_asm_io_stubs.o
MAIN_LINK_REBUILD = src/asm/crt0_arm64.o runtime_asm_io_stubs.o
MAIN_LINK_FLAGS = -e _start -nostartfiles
else
ifeq ($(UNAME_M),x86_64)
MAIN_LINK_O = src/asm/crt0_darwin_x86_64.o runtime_asm_io_stubs.o
MAIN_LINK_REBUILD = src/asm/crt0_darwin_x86_64.o runtime_asm_io_stubs.o
MAIN_LINK_FLAGS = -e _start -nostartfiles
else
ifeq ($(UNAME_M),amd64)
MAIN_LINK_O = src/asm/crt0_darwin_x86_64.o runtime_asm_io_stubs.o
MAIN_LINK_REBUILD = src/asm/crt0_darwin_x86_64.o runtime_asm_io_stubs.o
MAIN_LINK_FLAGS = -e _start -nostartfiles
else
MAIN_LINK_O = src/main_driver.o
MAIN_LINK_REBUILD = src/main_driver.o
MAIN_LINK_FLAGS =
endif
endif
endif
endif
else
ifeq ($(XLANG_IS_WIN_HOST),1)
MAIN_LINK_O = src/asm/crt0_mingw.o
MAIN_LINK_REBUILD = src/asm/crt0_mingw.o
# PLATFORM: WINDOWS — PE stack reserve 256MiB (matches pthread path stack_sz).
# MSYS default main stack ~2MiB; PE --stack reserves VA, OS commits on demand.
MAIN_LINK_FLAGS = -Wl,--stack,268435456
else
MAIN_LINK_O = src/main_driver.o
MAIN_LINK_REBUILD = src/main_driver.o
MAIN_LINK_FLAGS =
endif
endif
endif
endif

# ---------------------------------------------------------------------------
# wave924: platform multidef + pure-ld eligibility flags moved from Makefile
# inline ifeq (G.7 single authority; catalog_parse_mk owns them now).
# Converted from Makefile `else ifeq` to nested ifeq/else/endif so the shell
# catalog parser (no `else ifeq` support) can resolve them.
# ---------------------------------------------------------------------------

# PLATFORM: SHARED — Darwin uses -multiply_defined suppress; ELF/PE uses
# --allow-multiple-definition. Both are no-ops when no duplicate exists.
# Invariant: applied to every `ld -r` rule that merges 2+ .o inputs.
ifeq ($(UNAME_S),Darwin)
LD_R_MULTIDEF_FLAGS = -multiply_defined suppress
ASM_GLUE_DUP_LDFLAGS = -Wl,-multiply_defined,suppress
else
LD_R_MULTIDEF_FLAGS = --allow-multiple-definition
ASM_GLUE_DUP_LDFLAGS = -Wl,--allow-multiple-definition
endif

# pure-ld eligibility: freestanding crt0 + -e _start (not main_driver / not PE).
# PLATFORM: LINUX x86_64 · MACOS arm64/x86_64 — pure ld + tail libs.
# PLATFORM: WINDOWS · LEGACY_MAIN_C · non-x86_64 Linux · non-Darwin → CC residual.
# Mirrors MAIN_LINK_O platform branches: LEGACY_MAIN_C wins first; then Linux
# x86_64; then Darwin (any arch); else PURE_OK=0 (Windows / fallback main_driver).
ifeq ($(XLANG_LEGACY_MAIN_C),1)
SEED_LINK_PURE_OK = 0
SEED_LINK_ENTRY =
SEED_LINK_LD_TAIL =
else
ifeq ($(UNAME_S),Linux)
ifeq ($(UNAME_M),x86_64)
SEED_LINK_PURE_OK = 1
SEED_LINK_ENTRY = -e _start
# nostartfiles-style cold seed still pulls libc via former CC driver; pure-ld needs -lc.
SEED_LINK_LD_TAIL = -lc
else
SEED_LINK_PURE_OK = 0
SEED_LINK_ENTRY =
SEED_LINK_LD_TAIL =
endif
else
ifeq ($(UNAME_S),Darwin)
SEED_LINK_PURE_OK = 1
SEED_LINK_ENTRY = -e _start
# PLATFORM: MACOS — syslibroot/arch/platform_version composed in bootstrap_driver_seed_link.sh
SEED_LINK_LD_TAIL = -lSystem
else
SEED_LINK_PURE_OK = 0
SEED_LINK_ENTRY =
SEED_LINK_LD_TAIL =
endif
endif
endif
