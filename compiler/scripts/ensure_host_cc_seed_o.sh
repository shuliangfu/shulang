#!/usr/bin/env bash
# ensure_host_cc_seed_o.sh — R1 host-cc seed/from_x → .o single body
#   wave748: first family RT_SEED_SLICE
#   wave749: second family R1_CORE_SEED (diag / link_abi / c_import / bridge / seed_link_compat)
#   wave750: third family R1_FRONTEND_GLUE (lexer/ast/lsp basename-mismatch map)
#   wave751: fourth family R1_MAIN_RUNTIME (main/runtime multi-flag variants)
#   wave752: fifth family R1_ALIAS_STUBS (link alias / bare / compat stubs)
#   wave753: sixth family R1_EXTRA_CFLAGS (pipeline_abi / -fPIE / sqlite multi-flag /
#            parser link-alias extras)
#   wave754: seventh family R1_MISC_BASENAME (misc pure basename host-cc:
#            channel/kv/scheduler glue, backend enc, lsp ctx, pipeline_glue
#            strict_minimal, runtime_asm_build, link_abi_user_env)
#   wave755: eighth family R1_SEED_MAP (basename-mismatch + orch -D:
#            target_cpu_pure → target_cpu.o, runtime_ast_glue → ast_seed.o,
#            pipeline_bootstrap_orchestration + -Ibuild_asm -D)
#   wave756: R4 pure-R1 body helper — `try-r1 OUT` resolves OUT against the
#            eight catalog KEY memberships (G.7 lists stay mk) and runs the
#            same ensure_one body. Used by rebuild_leaves so pure R1 leaves
#            leave the make pattern graph; non-members exit 3 (caller make).
#   wave757: R3 cold-else body helper — `try-r3-cold OUT` resolves OUT against
#            catalog R3_COLD_SEED_OBJS (thin+rest leaves whose cold path is
#            pure basename host-cc). Same ensure_one body; exit 3 if not member.
#            rebuild_leaves residual uses this before make.
#   wave763: R3 PREFER thin+rest product path — `try-r3-prefer OUT` (same catalog
#            R3_COLD_SEED_OBJS; G.7 有则补全, no new list). When
#            XLANG_G05_PREFER_X_O=1 and xlang-c works: thin.x via
#            rt_prefer_try_x_to_o (wave190: single -E prologue; no bare -E|cc)
#            + seed rest (-D FROM_X) → ld -r. Else / fail → ensure_one cold seed
#            (same body as try-r3-cold). Product leaves thin-call this helper
#            via try-heat / g05 r3-prefer-family. simd_enc/loop keep nm symbol
#            gates.
#   wave764: G.7 g05 dual-hybrid swallow — same try-r3-prefer body owns product
#            daily path for R3_COLD nine (g05_ensure thin-calls r3-prefer-family).
#            Leaf map gains optional full.x first ladder (simd/backend R2 full
#            surface H=0; fail → thin; fail → cold).
#   wave765: G.7 g05 labi multi-slice swallow — `try-labi-prefer OUT` for
#            src/runtime_link_abi.o (L0..L9+L8b+L8c + rest FROM_X → cc -r).
#            g05_ensure + Makefile thin-call (no dual hybrid body).
#   wave766: G.7 g05 rt multi-slice swallow — `try-rt-prefer OUT` for
#            src/runtime_driver_no_c.o (content..dispatch + rest FROM_X → cc -r;
#            RT_SEED_SLICE external). g05_ensure + Makefile thin-call.
#   wave318: G.7 runtime mega full seed host-cc leave (prefer path) —
#            when all hybrid non-default RT_* slices are ok, monofile rest under
#            full XLANG_RT_*_FROM_X is T=0 (empty mega). Omit host-cc of
#            seeds/runtime.from_x.c and merge slices only (parser f-330 analogue).
#   wave319: G.7 runtime cold multi-slice leave (PREFER=0) —
#            multi-slice path no longer gated on PREFER=1; PREFER=0 uses cold
#            layer seeds only (no .x try). When full non-default set ok → same
#            omit empty mega rest as wave318 (no monofile host-cc). Monofile
#            seeds/runtime.from_x.c remains last-resort only (partial/fail).
#            Not M4 pin-off (7.1 still ⬜ — monofile seed still in tree).
#   wave320: G.7 product no_c refuse monofile (7.1.2 step) —
#            multi-slice gated on content layer seed (not monofile presence);
#            partial rest + last-resort monofile host-cc **refused** by default
#            (fail hard). Escape: XLANG_RT_ALLOW_MONOFILE_LAST_RESORT=1
#            (archaeology only; requires monofile file if still present).
#   wave321: G.7 R1 monofile physical retire (7.1.1) —
#            seeds/runtime.from_x.c **removed**. R1 main-runtime runtime*.o
#            cold maps → multi-slice product object (content layer seeds only).
#            runtime.o / runtime_x.o / runtime_driver.o become aliases of
#            multi-slice no_c (monofile flag variants retired; LEGACY monofile
#            host-cc gone). Escape monofile last-resort fails without seed.
#   wave767: G.7 g05 pipeline_abi + ldpc PREFER swallow —
#            `try-pipeline-abi-prefer OUT` (full .x WEAK + rest FROM_X → cc -r)
#            · `try-ldpc-prefer OUT` (thin .x WEAK + rest L2_LSP_CTX → cc -r).
#            g05_ensure + Makefile thin-call.
#   wave768: G.7 g05 target_cpu PREFER swallow —
#            `try-target-cpu-prefer OUT` (flags.x + rest pure FROM_X → cc -r).
#            g05_ensure + Makefile thin-call.
#   wave769: G.7 g05 L2 asm three thin+rest PREFER swallow —
#            `try-l2-asm-prefer OUT` for user_asm_seed_bridge /
#            backend_x86_64_enc_c / asm_backend_compat_stubs (table-driven;
#            thin .x + rest FROM_X → $CC -r; cold ensure_one).
#   wave770: G.7 g05 async three thin+rest PREFER swallow —
#            `try-async-prefer OUT` for async_liveness / async_cps_codegen /
#            async_asm_pool (table-driven; full .x + rest FROM_X → $CC -r;
#            cold ensure_one).
#   wave771: G.7 g05 other L2 four thin+rest PREFER swallow —
#            `try-other-l2-prefer OUT` for seed_link_compat / strict_glue_stubs /
#            fmt_check_cmd_driver / lsp_diag (table-driven; thin/full .x + rest
#            FROM_X → $CC -r; slc named-weak via G05_X_O_WEAK_FUNCS; cold
#            ensure_one + fmt USE_X_PIPELINE).
#   wave775: G.7 fmt_check_cmd.o Makefile dual → try-other-l2-prefer (有则补全) —
#            same table; leaf_kind=fmt_core (no -DXLANG_USE_X_PIPELINE; OBJS_CORE /
#            PIPELINE_X satellite path). Residual: physical delete · panic PREFER.
#   wave776: G.7 R2 panic PREFER thin+rest → `try-r2-prefer OUT` (有则补全) —
#            membership = catalog DRIVER_SEED_PANIC_OBJS; PREFER=1 thin.x + seed
#            rest FROM_X → ld -r (host pick mirrors Makefile ifeq tree); fail /
#            PREFER≠1 / pure-asm host → ensure_r2_panic_one cold (try-r2 twin).
#            Makefile runtime_panic.o thin-call; dual hybrid deleted.
#   wave779: G.7 B1 runtime_* OS/glue dual hybrid → `try-runtime-os-prefer OUT`
#            (有则补全; table-driven 23 leaves; reuses rt_prefer_try_x_to_o).
#            Makefile thin-call only (NOT physical delete). Special leaf_kinds:
#            http (-Iseeds/http), ed25519 (-Isrc/asm), tls (mbedtls -I fallback),
#            net_udp (Linux-only PREFER). Residual: B2–B5 · physical delete.
#   wave780: G.7 B2 std/core product hybrid → `try-std-core-prefer OUT`
#            (有则补全; 5 leaves: process/path/runtime/net + core/slice).
#            leaf_kind: direct (path/runtime/slice R2 DIRECT xlang-c -lib-name),
#            process_merge (args seed + argv + os_glue ld -r), net_merge
#            (sub .x + net_*_fast PREFER + final ld -r). Makefile thin-call only.
#            Residual: B3–B5 · physical delete.
#   wave781: G.7 B3 LSP satellite hybrid → `try-lsp-sat-prefer OUT`
#            (有则补全; dedicated table — shapes differ from try-other-l2-prefer /
#            try-ldpc: sizes_nostub = xlang-c -E → cc -c direct; stubs_no_c =
#            xlang-c -E thin + seed rest FROM_X → ld -r multidef). Makefile
#            thin-call only (NOT physical delete). Residual: B4–B5 · physical delete.
#   wave782: G.7 B4 gen.c → .o bootstrap → `try-gen-c-to-o OUT`
#            (有则补全; body = ensure_gen_x_o.sh maps for lexer_x / ast_gen2 /
#            driver_x / preprocess_x — outside try-gen-x catalog).
#            wave295 B′: _x_stubs2 host left (dead dual; not g05/stage2 link).
#            Makefile thin-call only (NOT physical delete). Residual: B5 · physical delete.
#   wave783: G.7 B5 cfg_eval multi-ladder → `try-cfg-eval-ladder OUT`
#            (有则补全; single leaf src/lexer/cfg_eval.o; rungs: -E-extern±L →
#            linux pin gen + link_alias ld -r → bootstrap stub). Makefile
#            thin-call only (NOT physical delete). Residual: B6 R5 · physical delete.
#   wave950: cfg-eval soft missing xlang-c → scripts/ensure_xlang_c.sh (0-make;
#            was make-target xlang-c; post-delete residual; soft || true pin/stub OK).
#   wave789: B7A heat shell auto-dispatch — `try-heat OUT` (有则补全; NOT physical
#            delete). Ladder existing try-* membership helpers (prefer before
#            pure R1/R2/gen) so heat can rebuild ensure-owned leaves without
#            knowing which Makefile recipe owns them. Makefile thin-call edges
#            remain residual (make dep graph); this is shell-primary heat body
#            dispatch only. Residual: Makefile edges · Windows gate physical del.
#   wave790: B7A heat Makefile thin-call unify — all ensure *recipes* call
#            `try-heat $@` only (115 leaves; G.7 single heat entry). Historical
#            try-*/one mode names stay in Makefile comments for archaeology.
#            Dependency edges still residual (NOT physical delete).
#   wave791: B7A heat dep-edge thin — pure runtime_* (seed+.x) Makefile prereqs
#            collapse to FORCE + ensure script; try-heat owns seed/.x mtime.
#            NOT physical delete; hdr/c/asm/stamp leaves keep full edges.
#   wave792: B7A heat dep-edge thin — pure seed+.x residual (R1/async/rt/alias/L2/
#            lsp/strict_minimal; +31 → 59 FORCE) same FORCE+ensure pattern.
#            Exclude hdr/twin (scheduler·strict_glue_stubs)/cfg_eval multi/asm/gen.
#   wave793: B7A heat dep-edge thin — pure seed+.x+.h residual → FORCE (+19 → 78).
#            ensure_one + prefer skip paths own project-header mtime via
#            seed_project_hdrs_newer (quoted/angle #include under .|include|src,
#            depth-capped BFS). NOT physical delete; residual twin/c multi/asm/gen.
#   wave794: B7A heat dep-edge thin — twin · Makefile-flags · pure leftover → FORCE
#            (+8 → 86). scheduler_glue (async_net_fs #include) · strict_glue_stubs
#            (heap_user #include + thin.x prefer) · glue_standalone multi-c ·
#            slice pure seed+.x · main_driver/runtime_driver{,_no_c}/pipeline_abi
#            (Makefile macro flags via force_thin_makefile_flags_newer).
#            Residual: cfg_eval multi · asm/gen · stamp · std merge · gen_x.
#            NOT physical delete.
#   wave795: B7A heat dep-edge thin — cfg_eval multi · pure asm · std direct/process
#            → FORCE (+15 → 101). cfg_eval multi-seed · crt0/freestanding/typeck_f64
#            · path/runtime/process. Host ifeq for crt0/typeck kept. crt0_mingw
#            Makefile flags via force_thin_makefile_flags_newer. Residual: net
#            multi-merge · panic stamp · gen_x · orch. NOT physical delete.
#   wave796: B7A heat dep-edge thin net multi-merge · panic stamp · gen_x/B4
#            residual (+11 → 112 FORCE). Shell owns: net_merge multi .x/seed
#            mtime; panic platform stamp + host pick (already try-r2); gen_x
#            via try-heat → try-gen-x / try-gen-c-to-o (PIPELINE_X_DEPS env).
#            Residual: orch / physical delete after Windows. NOT physical delete.
#   wave797: B7A heat dep-edge thin orch residual (+1 → 113 FORCE).
#            Shell owns: orch seed/.x + pipeline_gen.c + pipeline_glue_types.inc.
#            Residual: physical delete after Windows only. NOT physical delete.
#   wave758: R4 residual pure host-cc thin_glue → R1 seed-map (G.7 有则补全):
#            parser_asm_thin_glue.o ← seeds/parser_asm_thin_c.from_x.c +
#            -DPARSER_ASM_THIN_GLUE_NO_SEED_PARSE -Isrc/lexer -Isrc/asm -Iseeds/parser_asm;
#            ensure_one also refreshes on seeds/parser_asm/*.inc (Makefile prereq twin).
#   wave759: R4 residual glue standalone → R1 seed-map (G.7 有则补全):
#            build_asm/pipeline_glue_standalone.o ← seeds/pipeline_glue_standalone.from_x.c
#            + -Wno-error=return-type -Ibuild_asm. wave309 seed retired; ensure_one
#            early-exits when seed absent. Freshness residual (archaeology path):
#            build_asm/pipeline_glue_types.inc only — deleted pipeline_glue.c /
#            ast_pool.c -nt never fire (same debt layer as SYMS／glue ensure).
#   wave760: R2 panic cold body — `try-r2 OUT` resolves OUT against catalog
#            DRIVER_SEED_PANIC_OBJS (lists = mk). Cold path selects source by
#            host uname (Linux x86_64 → runtime_panic_x86_64.s when present;
#            arm64/aarch64 → runtime_panic_arm64.from_x.c; else
#            runtime_panic.from_x.c), touches platform stamp
#            build_asm/runtime_panic.$(uname -s).$(uname -m).stamp, then
#            ensure_one (seed) or plain cc -c (.s). PREFER thin+rest stays
#            Makefile. rebuild_leaves residual uses try-r2 before make.
#   wave762: R2 typeck_f64 + crt0 — extend try-r2 membership to catalog
#            DRIVER_SEED_TYPECK_F64_OBJS + DRIVER_SEED_CRT0_OBJS (lists = mk).
#            typeck_f64_bits.o: host picks platform .s (Linux/Darwin/Windows).
#            crt0*.o / freestanding_io_x86_64.o: fixed o→.s map; crt0_mingw.o
#            uses seeds/crt0_mingw.from_x.c via cc_inc_tu (+ WIN32_O_CFLAGS).
#            G.7 有则补全 on try-r2 (no second helper name).
#
# Authority (G.7):
#   Single shell *recipe body* for pure host-cc compile of seeds/*.from_x.c → .o.
#   Object *lists* stay in Makefile / mk (catalog export keys).
#   This script never hardcodes a second product .o inventory as authority.
#   Seed / flag path conventions (not .o lists):
#     basename match:  <dir>/<leaf>.o  ←  seeds/<leaf>.from_x.c
#     frontend-glue:   fixed o→seed map (leaf stem ≠ seed stem)
#     main-runtime:    o→seed map (main_* ← main; runtime_* ← runtime) +
#                      o→extra -D flags (thin Makefile passes expanded make vars)
#     alias-stubs:     basename match (same as core-seed / rt-slice)
#     extra-cflags:    o→seed map (sqlite_stub shares sqlite seed) +
#                      o→extra flags (-D / -fPIE; thin passes make vars)
#     misc-basename:   basename match (same as alias-stubs / core-seed)
#     seed-map:        o→seed map (stem ≠ seed stem) + optional orch extras
#
# Families (list authority = catalog KEY):
#   RT_SEED_SLICE_OBJS     — five Cap residual slices under src/runtime/
#   R1_CORE_SEED_OBJS      — diag + runtime_link_abi + runtime_c_import +
#                            x_seed_bridge + seed_link_compat
#   R1_FRONTEND_GLUE_OBJS  — lexer.o / ast.o / lsp_diag.o (runtime_*_glue seeds)
#   R1_MAIN_RUNTIME_OBJS   — main / main_x / main_driver / runtime / runtime_x /
#                            runtime_driver / runtime_driver_no_c
#   R1_ALIAS_STUBS_OBJS    — x_frontend_link_alias + bare aliases + typeck stubs +
#                            user_asm_seed_bridge + asm_backend_compat_stubs +
#                            runtime_driver_strict_glue_stubs
#   R1_EXTRA_CFLAGS_OBJS   — runtime_pipeline_abi + runtime_asm_io_stubs (-fPIE) +
#                            runtime_sqlite_glue[+_stub] + parser_asm_parse_expr_link
#   R1_MISC_BASENAME_OBJS  — pure basename host-cc without special -D/-f extras
#                            (glue/enc/ctx/pipeline_glue_strict_minimal/asm_build/…)
#   R1_SEED_MAP_OBJS       — basename-mismatch + bootstrap orch extras + thin_glue
#                            + glue standalone (target_cpu / ast_seed / orch /
#                            parser_asm_thin_glue · pipeline_glue_standalone · wave758/759)
#   R3_COLD_SEED_OBJS      — thin+rest cold-else pure host-cc (wave757)
#   wave761: R4 residual gen *_x + pipeline_x — `try-gen-x OUT`
#            membership = catalog LSP_X / PIPELINE_X keys;
#            body = scripts/ensure_gen_x_o.sh (G.7 有则补全).
#            rebuild_leaves try-r2 then try-gen-x then residual make.

# Not in scope (honest residual):
#   - ~~R3 Makefile PREFER thin for R3_COLD nine~~ wave763 try-r3-prefer
#   - ~~g05 R3_COLD nine dual hybrid~~ wave764 → r3-prefer-family
#   - ~~g05 labi multi-slice~~ wave765 try-labi-prefer
#   - ~~g05 rt multi-slice~~ wave766 try-rt-prefer
#   - ~~g05 pipeline_abi / ldpc PREFER~~ wave767 try-pipeline-abi-prefer / try-ldpc-prefer
#   - ~~g05 target_cpu PREFER~~ wave768 try-target-cpu-prefer
#   - ~~g05 L2 asm three (uasb/bxec/abcs)~~ wave769 try-l2-asm-prefer
#   - ~~g05 async three (liveness/cps/asm_pool)~~ wave770 try-async-prefer
#   - ~~g05 other L2 four (slc/strict_glue/fmt_check/lsp_diag)~~ wave771
#     try-other-l2-prefer
#   - ~~fmt_check_cmd.o Makefile dual~~ wave775 → try-other-l2-prefer fmt_core
#   - ~~panic PREFER thin~~ wave776 → try-r2-prefer
#   - ~~B1 runtime_* OS/glue dual hybrid~~ wave779 → try-runtime-os-prefer
#   - ~~B2 std/core product hybrid~~ wave780 → try-std-core-prefer
#   - ~~B3 LSP satellite hybrid~~ wave781 → try-lsp-sat-prefer
#   - ~~B4 gen_c_to_o bootstrap~~ wave782 → try-gen-c-to-o
#   - ~~B5 cfg_eval multi-ladder~~ wave783 → try-cfg-eval-ladder
#   - R5 CI all · B6 · pure-ld residual
#   - pure-ld (11.1.4) · physical Makefile delete (11.3.1)
#   - bootstrap_nostdlib_stubs.o (cc_inc_tu residual)
#   - ~~crt0_user.o / freestanding_io.o / ast_x.o cp wrappers~~ wave836 → ensure_cp_alias_o
#
# Usage (cwd = compiler/):
#   bash scripts/ensure_host_cc_seed_o.sh one <out.o> <seed.from_x.c> [extra cflags...]
#   bash scripts/ensure_host_cc_seed_o.sh try-r1 <out.o>   # wave756 R4 pure-R1 helper
#   bash scripts/ensure_host_cc_seed_o.sh try-r3-cold <out.o>
#   bash scripts/ensure_host_cc_seed_o.sh try-r3-prefer <out.o> # wave763 PREFER thin+rest
#   bash scripts/ensure_host_cc_seed_o.sh try-labi-prefer <out.o> # wave765 labi multi-slice
#   bash scripts/ensure_host_cc_seed_o.sh try-rt-prefer <out.o>   # wave766 rt multi-slice
#   bash scripts/ensure_host_cc_seed_o.sh try-pipeline-abi-prefer <out.o> # wave767 pipeline_abi
#   bash scripts/ensure_host_cc_seed_o.sh try-ldpc-prefer <out.o>  # wave767 ldpc thin+rest
#   bash scripts/ensure_host_cc_seed_o.sh try-target-cpu-prefer <out.o> # wave768 target_cpu
#   bash scripts/ensure_host_cc_seed_o.sh try-l2-asm-prefer <out.o> # wave769 L2 asm three
#   bash scripts/ensure_host_cc_seed_o.sh try-async-prefer <out.o> # wave770 async three
#   bash scripts/ensure_host_cc_seed_o.sh try-other-l2-prefer <out.o> # wave771 other L2 four
#   bash scripts/ensure_host_cc_seed_o.sh try-r2-prefer <out.o> # wave776 R2 panic PREFER thin
#   bash scripts/ensure_host_cc_seed_o.sh try-runtime-os-prefer <out.o> # wave779 B1 runtime OS 23
#   bash scripts/ensure_host_cc_seed_o.sh try-std-core-prefer <out.o> # wave780 B2 std/core 5
#   bash scripts/ensure_host_cc_seed_o.sh try-lsp-sat-prefer <out.o> # wave781 B3 LSP satellite 2
#   bash scripts/ensure_host_cc_seed_o.sh try-gen-c-to-o <out.o> # wave782 B4 gen.c→.o bootstrap 5
#   bash scripts/ensure_host_cc_seed_o.sh try-cfg-eval-ladder <out.o> # wave783 B5 cfg_eval multi-ladder 1
#   bash scripts/ensure_host_cc_seed_o.sh try-heat <out.o>  # wave789 B7A heat auto-dispatch ladder
#   bash scripts/ensure_host_cc_seed_o.sh try-r2 <out.o>   # wave760/762 R2 UNAME leaves
#   bash scripts/ensure_host_cc_seed_o.sh try-gen-x <out.o> # wave761 gen *_x / pipeline_x
#   bash scripts/ensure_host_cc_seed_o.sh r2-panic         # DRIVER_SEED_PANIC family
#   bash scripts/ensure_host_cc_seed_o.sh r2-typeck-f64    # DRIVER_SEED_TYPECK_F64 family
#   bash scripts/ensure_host_cc_seed_o.sh r2-crt0          # DRIVER_SEED_CRT0 family
#   bash scripts/ensure_host_cc_seed_o.sh rt-slice          # RT_SEED_SLICE family
#   bash scripts/ensure_host_cc_seed_o.sh core-seed         # R1_CORE_SEED family
#   bash scripts/ensure_host_cc_seed_o.sh frontend-glue     # R1_FRONTEND_GLUE family
#   bash scripts/ensure_host_cc_seed_o.sh main-runtime      # R1_MAIN_RUNTIME family
#   bash scripts/ensure_host_cc_seed_o.sh alias-stubs       # R1_ALIAS_STUBS family
#   bash scripts/ensure_host_cc_seed_o.sh extra-cflags      # R1_EXTRA_CFLAGS family
#   bash scripts/ensure_host_cc_seed_o.sh misc-basename     # R1_MISC_BASENAME family
#   bash scripts/ensure_host_cc_seed_o.sh seed-map          # R1_SEED_MAP family
#   bash scripts/ensure_host_cc_seed_o.sh all               # all swallowed families
#   bash scripts/ensure_host_cc_seed_o.sh --check
#   bash scripts/ensure_host_cc_seed_o.sh seed-map --force
#   ./xbuild host-cc-seed | … | misc-basename | seed-map | r2-panic
#
#   wave964: --check post_ship when Makefile absent (wave941 phys-del).
#            Catalog + shell seed maps / try-heat ladder remain the authority;
#            MF thin-call residual inventory is N/A (no dual "missing Makefile" fail).
#            PLATFORM: SHARED — 0-make structural honesty; dual-end L2 safe.
#
# Env:
#   CC — host compiler (default: resolve_host_cc.sh — `cc` if present else `gcc`;
#        PLATFORM: WINDOWS/MinGW often has only gcc, no `cc` binary name)
#   CFLAGS — base flags (default: load via make export-try-heat-cflags when unset
#        — wave862; fallback -Wall -Wextra -I. -Iinclude -Isrc)
#   PIPELINE_GEN_CFLAGS — silence flags (default: load via export-try-heat-cflags
#        when unset — wave862; needs make ifeq for CC_IS_CLANG)
#   RUNTIME_DRIVER_CFLAGS / RUNTIME_DRIVER_NO_C_CFLAGS — multi-flag variants
#   RUNTIME_PIPELINE_ABI_CFLAGS / PARSER_ASM_LINK_ALIAS_CFLAGS — extra-cflags family
#     (Makefile thin expands make vars; family mode uses env or defaults below)
#   XLANG_HOST_CC_SEED_FORCE=1 — force recompile (same as --force)
#   MAKE — catalog list expansion + wave862 CFLAGS export leaf (default: make)
#   XLANG_G05_PREFER_X_O — prefer thin .x path when 1 (default per family helper
#        :-0 or :-1). wave881: Makefile try-heat drops PREFER recipe inject;
#        set via make CLI / env (GNU make auto-exports CLI+env vars). Cold seed:
#        `make XLANG_G05_PREFER_X_O=0 …` still forces seed path without inject.
#
# PLATFORM: SHARED — shell orchestration; seed pins host-portable C.
#   R2 panic body: PLATFORM LINUX|x86_64 (.s) / MACOS|arm64 + LINUX|aarch64
#   (arm64 seed) / else (from_x seed). PREFER thin = try-r2-prefer (wave776).
#   R2 typeck_f64 / crt0: PLATFORM per host .s / mingw seed (wave762).
# Wave: 748–763 Track MG · 11.3.1 R1 families + R4 pure-R1 + R3 cold-else +
#       R3 PREFER thin (try-r3-prefer) + thin_glue/glue-standalone seed-map +
#       R2 panic/typeck_f64/crt0 (not physical delete · not pure-ld).

set -euo pipefail
_ENSURE_HOST_CC_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
cd "$_ENSURE_HOST_CC_DIR/.."

# G.7: single default-CC policy (scripts/resolve_host_cc.sh). Do not hardcode
# CC=cc — MinGW ships gcc without a `cc` alias (Windows hybrid min-gate).
# shellcheck source=resolve_host_cc.sh
. "$_ENSURE_HOST_CC_DIR/resolve_host_cc.sh"

# Stage 12.2.1: XLANG_FORBID_HOST_CC gate (no-op when flag unset; zero impact
# on normal builds). When XLANG_FORBID_HOST_CC=1, replaces $CC with a wrapper
# that logs and blocks all host-CC invocations — builds the zero-CC problem map.
# PLATFORM: SHARED.
. "$_ENSURE_HOST_CC_DIR/forbid_host_cc.sh"

# Stage 12.2.3: pure-ld partial-merge helper (replaces $CC -r -nostdlib in
# prefer hybrid merges; zero-CC when XLANG_ZERO_CC_LD=1, else $CC -r zero
# regression). PLATFORM: SHARED.
. "$_ENSURE_HOST_CC_DIR/pure_ld_shared.sh"

# Stage 12.0.5: strip ambient tree PREFER_ASM_O unless ALLOW_TREE (G.7).
# Prefer families re-scope PREFER inside pure_asm subshells. PLATFORM: SHARED.
xlang_strip_tree_prefer_asm_unless_allowed

MAKE="${MAKE:-make}"
FORCE="${XLANG_HOST_CC_SEED_FORCE:-0}"

# wave862 · B7B try-heat CFLAGS bulk shell-load (G.7 有则补全 on wave860 export-leaf).
# Product CFLAGS / PIPELINE_GEN_CFLAGS need make expansion (OPT += -O2; clang
# silence ifeq). Makefile try-heat recipes drop multi-token CFLAGS= env; shell
# loads export-try-heat-cflags when either var is unset. Fallback matches
# historic shell defaults when make export is unavailable.
# wave881 · B7B try-heat PREFER inject hygiene: product try-heat drops PREFER
# inject (no XLANG_G05_PREFER_X_O= / XLANG= recipe inject). Prefer policy is
# env/CLI + shell defaults (G.7 single body).
# wave884 · B7B residual CC= inject hygiene: product try-heat is env-free thin
# @bash only — CC from resolve_host_cc when unset; make CLI/env auto-export.
# wave885 · B7B residual G05_SYNC inject hygiene: relink-xlang / xlang_asm drop
# G05_SYNC_ASM= recipe inject; shell --no-sync + default sync own policy.
# wave886 · B7B residual LD + pipeline bag inject hygiene: cfg_eval drops
# LD=/LD_RELFLAGS=; pipeline_x drops PIPELINE_X_* / XLANG_FORCE_REGEN_GEN inject.
# Shell owns LD defaults + PIPELINE_X_DEPS mk-load when unset.
# Residual: thin edges · B2 · mk lists · physical delete.
# wave942: catalog-primary CFLAGS/PIPELINE_GEN_CFLAGS load (was make
# export-try-heat-cflags). Makefile physically deleted in wave941; catalog is
# the single authority for mk-derived KEY=VALUE (CC, CFLAGS, PIPELINE_GEN_CFLAGS
# all sourced from mk/*.mk via driver_seed_obj_catalog.sh --shell).
# XLANG_CATALOG_CACHE_FILE lets the parent bootstrap pass a pre-warmed cache
# so this script does not re-parse all mk files (Windows MinGW: ~3min/call).
# PLATFORM: SHARED — same KEY=VALUE semantics on Darwin/Linux/Windows MSYS2.
_load_try_heat_cflags_via_catalog() {
  local _val
  if [ -z "${CFLAGS+x}" ]; then
    if [ -n "${XLANG_CATALOG_CACHE_FILE:-}" ] && [ -s "${XLANG_CATALOG_CACHE_FILE:-}" ]; then
      _val=$(sed -n "s|^CFLAGS=||p" "${XLANG_CATALOG_CACHE_FILE}" | tail -n 1)
    else
      _val=$(bash scripts/driver_seed_obj_catalog.sh --shell 2>/dev/null \
        | sed -n "s|^CFLAGS=||p" | tail -n 1)
    fi
    [ -n "$_val" ] && CFLAGS="$_val"
  fi
  if [ -z "${PIPELINE_GEN_CFLAGS+x}" ]; then
    if [ -n "${XLANG_CATALOG_CACHE_FILE:-}" ] && [ -s "${XLANG_CATALOG_CACHE_FILE:-}" ]; then
      _val=$(sed -n "s|^PIPELINE_GEN_CFLAGS=||p" "${XLANG_CATALOG_CACHE_FILE}" | tail -n 1)
    else
      _val=$(bash scripts/driver_seed_obj_catalog.sh --shell 2>/dev/null \
        | sed -n "s|^PIPELINE_GEN_CFLAGS=||p" | tail -n 1)
    fi
    [ -n "$_val" ] && PIPELINE_GEN_CFLAGS="$_val"
  fi
  return 0
}

if [ -z "${CFLAGS+x}" ] || [ -z "${PIPELINE_GEN_CFLAGS+x}" ]; then
  _load_try_heat_cflags_via_catalog || true
fi
# Match g05 / Makefile product includes; PIPELINE_GEN_CFLAGS optional when empty.
BASE_CFLAGS="${CFLAGS:--Wall -Wextra -I. -Iinclude -Isrc}"
# PLATFORM: MACOS — match macho.x LC_BUILD_VERSION minos 11.0.0.
# Catalog CFLAGS already completes this when unset; keep the flag if env CFLAGS
# omitted it so always-linked companions (stubs/panic/user_env) match product-asm.
# Do not -w swallow; do not raise macho.x minos to 26.0.
case "$(uname -s 2>/dev/null)" in
  Darwin)
    case " $BASE_CFLAGS " in
      *" -mmacosx-version-min="*) ;;
      *) BASE_CFLAGS="$BASE_CFLAGS -mmacosx-version-min=11.0" ;;
    esac
    ;;
esac
PIPELINE_GEN_CFLAGS="${PIPELINE_GEN_CFLAGS:-}"

# Default multi-flag mirrors for family mode when env empty.
# PLATFORM: SHARED — must stay aligned with Makefile RUNTIME_DRIVER_*_CFLAGS
# (without optional XLANG_LEGACY_PREPROCESS_C; LEGACY path dead after preprocess.c
# physical delete). wave864: product thin leaves no longer inject make-expanded
# RUNTIME_*/PARSER_* bags — shell defaults are the authority when env unset.
_DEFAULT_RT_SLICE_CFLAGS="-DXLANG_RT_ARENA_BUF_FROM_X -DXLANG_RT_EMIT_STATE_FROM_X -DXLANG_RT_PREAMBLE_FROM_X -DXLANG_RT_STACK_FROM_X -DXLANG_RT_PARSE_DIAG_FROM_X"
_DEFAULT_RUNTIME_DRIVER_CFLAGS="-DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS -DXLANG_NO_C_FRONTEND -DXLANG_ASM_USE_COMPILER_IMPL_C ${_DEFAULT_RT_SLICE_CFLAGS}"
_DEFAULT_RUNTIME_DRIVER_NO_C_CFLAGS="-DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE -DXLANG_USE_X_PREPROCESS -DXLANG_USE_X_TYPECK -DXLANG_USE_X_CODEGEN -DXLANG_NO_C_FRONTEND -DXLANG_ASM_USE_COMPILER_IMPL_C ${_DEFAULT_RT_SLICE_CFLAGS}"
# PLATFORM: SHARED — defaults aligned with Makefile (without optional LEGACY).
_DEFAULT_RUNTIME_PIPELINE_ABI_CFLAGS="-DXLANG_USE_X_PIPELINE"
_DEFAULT_PARSER_ASM_LINK_ALIAS_CFLAGS="-DPARSER_ASM_LINK_ALIAS_SKIP_X_SYMBOLS"
# PLATFORM: SHARED — aligned with Makefile PARSER_ASM_THIN_GLUE_CFLAGS + -I paths.
_DEFAULT_PARSER_ASM_THIN_GLUE_CFLAGS="-DPARSER_ASM_THIN_GLUE_NO_SEED_PARSE -Isrc/lexer -Isrc/asm -Iseeds/parser_asm"

# wave326: M4 7.3.1 link_abi mega pin close — prefer 12× labi_*.x slices by default.
# Product authority: L0..L9 + L8b + L8c labi_*.x prefer → per-slice .o →
#   $CC -r -nostdlib merge → src/runtime_link_abi.o; -D XLANG_LABI_*_FROM_X only
#   on slices that preferred .x (rest compiled from mega seed with those gates).
# Pin seed (seeds/runtime_link_abi.from_x.c + seeds/labi_*.from_x.c) is
#   archaeology egg only (true cold / no product xlang binary).
# PLATFORM: SHARED — cold start (R1_CORE_SEED direct call) + g05 daily path
#   now aligned (no more "g05 PREFER=1 vs direct call PREFER=0" dual policy).
# Aligned with wave322 typeck / wave323 codegen / wave325 parser FROM_X defaults.
XLANG_LINK_ABI_FROM_X="${XLANG_LINK_ABI_FROM_X:-1}"
XLANG_LINK_ABI_ALLOW_PIN="${XLANG_LINK_ABI_ALLOW_PIN:-1}"

MODE="${1:-}"
if [ -z "$MODE" ]; then
  echo "ensure_host_cc_seed_o: usage: one|try-r1|try-r3-cold|try-r3-prefer|try-labi-prefer|try-rt-prefer|try-pipeline-abi-prefer|try-ldpc-prefer|try-target-cpu-prefer|try-l2-asm-prefer|try-async-prefer|try-other-l2-prefer|try-r2-prefer|try-runtime-os-prefer|try-std-core-prefer|try-lsp-sat-prefer|try-gen-c-to-o|try-cfg-eval-ladder|try-x-to-o|try-heat|try-r2|try-gen-x|rt-slice|core-seed|frontend-glue|main-runtime|alias-stubs|extra-cflags|misc-basename|seed-map|r3-cold-seed|r2-panic|r2-typeck-f64|r2-crt0|gen-x|all|--check  (see header)" >&2
  exit 2
fi
shift || true

# Parse trailing --force on any mode
for arg in "$@"; do
  case "$arg" in
    --force|-f|force) FORCE=1 ;;
  esac
done

log() { echo "ensure-host-cc-seed: $*" >&2; }


# ---------------------------------------------------------------------------
# wave793: project-header freshness (G.7 single body for FORCE thin).
#
# Mirror Makefile .h prereqs without dual lists: scan seed #include "..." / <...>
# and resolve under dirname(seed), include/, src/, and .  Depth-capped BFS so
# transitive project headers (e.g. lexer.h → token.h) refresh the .o.
# System headers (not found under project paths) are ignored.
# First-hop also catches twin seed embeds (#include "seeds/async_net_fs.from_x.c",
# runtime_heap_user.from_x.c) — wave794 twin FORCE thin relies on this.
# Exit 0 if any resolved project header is newer than OUT; else 1.
# PLATFORM: SHARED — portable shell; no make graph.
# ---------------------------------------------------------------------------
seed_project_hdrs_newer() {
  local seed="$1"
  local out="$2"
  local f inc cand resolved dir n=0 max_n=64
  local queue="" seen=" "
  if [ -z "$seed" ] || [ -z "$out" ] || [ ! -f "$seed" ] || [ ! -f "$out" ]; then
    return 1
  fi
  queue="$seed"
  seen=" $seed "
  while [ -n "$queue" ] && [ "$n" -lt "$max_n" ]; do
    f="${queue%% *}"
    if [ "$queue" = "$f" ]; then
      queue=""
    else
      queue="${queue#* }"
    fi
    n=$((n + 1))
    [ -f "$f" ] || continue
    dir="$(dirname "$f")"
    # shellcheck disable=SC2016
    while IFS= read -r inc || [ -n "$inc" ]; do
      [ -z "$inc" ] && continue
      # Skip obvious libc / system basenames when not present in project tree.
      resolved=""
      for cand in "$dir/$inc" "include/$inc" "src/$inc" "$inc"; do
        if [ -f "$cand" ]; then
          resolved="$cand"
          break
        fi
      done
      [ -z "$resolved" ] && continue
      if [ "$resolved" -nt "$out" ]; then
        return 0
      fi
      case "$seen" in
        *" $resolved "*) ;;
        *)
          seen="$seen$resolved "
          case "$resolved" in
            *.h|*.hpp|*.inc)
              if [ -z "$queue" ]; then
                queue="$resolved"
              else
                queue="$queue $resolved"
              fi
              ;;
          esac
          ;;
      esac
    done <<EOF
$(sed -n 's/^[[:space:]]*#[[:space:]]*include[[:space:]]*[<"]\([^>"]*\)[>"].*/\1/p' "$f" 2>/dev/null || true)
EOF
  done
  return 1
}

# ---------------------------------------------------------------------------
# wave794: Makefile mtime for flag-sensitive FORCE-thin leaves (G.7 single body).
#
# These leaves historically listed Makefile as a make prereq so CFLAGS / -D
# Historic FORCE-thin edge: Makefile mtime drove macro-flag rebuilds
# (USE_X_PIPELINE / USE_X_DRIVER / NO_C / …). wave941 deleted Makefile —
# dead `[ Makefile -nt OUT ]` never fires (bash missing -nt → false).
# Authority now = FORCE / catalog / seed+.x (ensure_one); this helper stays
# as a named no-op so callers keep a single G.7 hook.
# Exit 0 if flags source is newer than OUT; else 1 (always 1 post-MG).
# PLATFORM: SHARED — portable shell; no make graph.
# ---------------------------------------------------------------------------
force_thin_makefile_flags_newer() {
  local out="$1"
  case "$out" in
    # wave794: main/runtime/pipeline macro flags · wave795: crt0_mingw WIN32_O_CFLAGS
    # wave941: Makefile absent — never refresh via deleted make graph.
    src/main_driver.o|src/runtime_driver.o|src/runtime_driver_no_c.o|src/runtime_pipeline_abi.o|src/asm/crt0_mingw.o)
      return 1
      ;;
  esac
  return 1
}

# ---------------------------------------------------------------------------
# one OUT SEED [extra cflags...]
# PLATFORM: SHARED — pure host-cc body; no make graph.
# ---------------------------------------------------------------------------
ensure_one() {
  local out="$1"
  local seed="$2"
  shift 2
  # Drop --force tokens if present as extra args
  local extras=()
  local a
  for a in "$@"; do
    case "$a" in
      --force|-f|force) continue ;;
      *) extras+=("$a") ;;
    esac
  done

  if [ -z "$out" ] || [ -z "$seed" ]; then
    echo "ensure_host_cc_seed_o one: need <out.o> <seed.from_x.c>" >&2
    exit 2
  fi
  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o: missing seed $seed" >&2
    exit 1
  fi

  mkdir -p "$(dirname "$out")"

  if [ "$FORCE" != "1" ] && [ -f "$out" ] && [ ! "$seed" -nt "$out" ]; then
    # Sibling .x deps: out path stem, seed-stem under src/asm or src/,
    # and main_c_entry.x for main family (Makefile dep name).
    local need=0
    local xsrc stem cand inc
    xsrc="${out%.o}.x"
    if [ -f "$xsrc" ] && [ "$xsrc" -nt "$out" ]; then
      need=1
    fi
    stem="$(basename "$seed" .from_x.c)"
    for cand in "src/asm/${stem}.x" "src/${stem}.x" "src/main_c_entry.x"; do
      if [ -f "$cand" ] && [ "$cand" -nt "$out" ]; then
        need=1
        break
      fi
    done
    # wave758: parser_asm_thin_glue monothin includes many seeds/parser_asm/*.inc;
    # Makefile lists them as prereqs — mirror freshness here (G.7 single body).
    if [ "$need" -eq 0 ] && [ "$stem" = "parser_asm_thin_c" ]; then
      for inc in seeds/parser_asm/*.inc; do
        if [ -f "$inc" ] && [ "$inc" -nt "$out" ]; then
          need=1
          break
        fi
      done
    fi
    # wave759→wave309: glue_standalone seed retired; deleted pipeline_glue.c /
    # ast_pool.c -nt never fire. Residual freshness = types.inc only when the
    # archaeology seed path is still invoked (G.7 single body). PLATFORM: SHARED.
    if [ "$need" -eq 0 ] && [ "$stem" = "pipeline_glue_standalone" ]; then
      for cand in build_asm/pipeline_glue_types.inc; do
        if [ -f "$cand" ] && [ "$cand" -nt "$out" ]; then
          need=1
          break
        fi
      done
    fi
    # wave797: pipeline_bootstrap_orchestration historically rebuilt when pipeline_gen.c
    # or build_asm/pipeline_glue_types.inc changed (Makefile prereq twin). Mirror here
    # so FORCE + try-heat can drop source prereqs (G.7 single body; not physical delete).
    if [ "$need" -eq 0 ] && [ "$stem" = "pipeline_bootstrap_orchestration" ]; then
      for cand in pipeline_gen.c build_asm/pipeline_glue_types.inc; do
        if [ -f "$cand" ] && [ "$cand" -nt "$out" ]; then
          need=1
          break
        fi
      done
    fi
    # wave793: project headers (Makefile .h prereqs) — single body for FORCE thin.
    if [ "$need" -eq 0 ] && seed_project_hdrs_newer "$seed" "$out"; then
      need=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$need" -eq 0 ] && force_thin_makefile_flags_newer "$out"; then
      need=1
    fi
    if [ "$need" -eq 0 ]; then
      log "skip $out (up-to-date vs $seed)"
      return 0
    fi
  fi

  # wave940: pipeline_glue_standalone.o embeds build_asm/pipeline_glue_types.inc
  # via #include. On cold start (build_asm/ cleared) the .inc is missing and
  # cc fails with "fatal error: pipeline_glue_types.inc: No such file or
  # directory". Root-cause fix (G.7 single body): ensure .inc before cc -c.
  # PLATFORM: SHARED — same extract on Darwin/Linux/Windows MSYS2.
  # Before wave940 this was a symptom-level fix (manual cc -Ibuild_asm); now
  # the seed-map body owns the .inc prerequisite just like Makefile prereq.
  if [ "$out" = "build_asm/pipeline_glue_standalone.o" ] \
    && [ ! -s build_asm/pipeline_glue_types.inc ] \
    && [ -f scripts/ensure_pipeline_glue_types.sh ]; then
    log "ensure build_asm/pipeline_glue_types.inc (cold-start prereq for $out)"
    bash scripts/ensure_pipeline_glue_types.sh >&2 || {
      echo "ensure_host_cc_seed_o: ensure_pipeline_glue_types.sh failed for $out" >&2
      return 1
    }
  fi

  log "cc -c $seed → $out"
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS "${extras[@]+"${extras[@]}"}" -c -o "$out" "$seed"; then
    echo "ensure_host_cc_seed_o: cc failed for $out (seed=$seed)" >&2
    return 1
  fi
}

# ---------------------------------------------------------------------------
# Catalog list expansion (G.7: KEY only; no hardcoded .o inventory in shell)
# ---------------------------------------------------------------------------
# Process + optional file cache (wave MG Windows):
#   try-heat is invoked as a *new bash* per Makefile FORCE leaf. Without a
#   shared cache, each of ~50 ensure goals re-runs driver_seed_obj_catalog.sh
#   (full mk parse). On MinGW/Git Bash that multi-minute stalls look like a
#   hung make with no gcc. catalog_blob already memoizes in-process; also honor
#   XLANG_CATALOG_CACHE_FILE so ensure_prereqs / rebuild can warm once.
# PLATFORM: SHARED — cache is optional; unset = prior in-process-only behavior.
catalog_blob() {
  # Prefer shared file cache (cross-process for one ensure/make/bootstrap wave).
  # Parent (bootstrap_driver_seed / ensure_prereqs / rebuild_leaves) should set
  # XLANG_CATALOG_CACHE_FILE; without it each try-* re-parses mk (Windows stall).
  if [ -n "${XLANG_CATALOG_CACHE_FILE:-}" ] && [ -s "${XLANG_CATALOG_CACHE_FILE}" ]; then
    cat "${XLANG_CATALOG_CACHE_FILE}"
    return 0
  fi
  if [ -z "${_catalog_blob_cache:-}" ]; then
    if [ ! -f scripts/driver_seed_obj_catalog.sh ]; then
      echo "ensure_host_cc_seed_o: missing scripts/driver_seed_obj_catalog.sh" >&2
      exit 1
    fi
    # --shell: never route catalog through MAKE wrap (Windows gate MAKE is a
    # logging wrapper; export-via-make is LEGACY only). PLATFORM: SHARED.
    _catalog_blob_cache="$(bash scripts/driver_seed_obj_catalog.sh --shell)"
    if [ -n "${XLANG_CATALOG_CACHE_FILE:-}" ]; then
      # Best-effort warm for sibling try-heat processes in the same ensure wave.
      printf '%s\n' "$_catalog_blob_cache" >"${XLANG_CATALOG_CACHE_FILE}" 2>/dev/null || true
    fi
  fi
  printf '%s\n' "$_catalog_blob_cache"
}

catalog_key_list() {
  # $1 = catalog KEY name (e.g. RT_SEED_SLICE_OBJS)
  local key="$1"
  local key_line
  if [ -z "$key" ]; then
    echo "ensure_host_cc_seed_o: catalog_key_list needs KEY" >&2
    exit 2
  fi
  key_line="$(catalog_blob | sed -n "s/^${key}=//p" | head -1)"
  if [ -z "${key_line// /}" ]; then
    echo "ensure_host_cc_seed_o: empty $key from catalog (export missing?)" >&2
    exit 1
  fi
  printf '%s\n' "$key_line"
}

# seed convention (basename match): basename of .o → seeds/<basename>.from_x.c
seed_for_o() {
  local o="$1"
  local base
  base="$(basename "$o" .o)"
  printf 'seeds/%s.from_x.c\n' "$base"
}

# seed convention (frontend-glue basename mismatch): o path → seed path.
# PLATFORM: SHARED — map is path convention only; list authority = catalog KEY.
# Not a second .o inventory: unknown catalog members fail closed.
seed_for_frontend_glue() {
  local o="$1"
  case "$o" in
    src/lexer/lexer.o)   printf 'seeds/runtime_lexer_glue.from_x.c\n' ;;
    src/ast/ast.o)       printf 'seeds/runtime_ast_glue.from_x.c\n' ;;
    src/lsp/lsp_diag.o)  printf 'seeds/runtime_lsp_glue.from_x.c\n' ;;
    *)
      echo "ensure_host_cc_seed_o: no frontend-glue seed map for $o" >&2
      exit 1
      ;;
  esac
}

# seed convention (main-runtime multi-out from shared seeds).
# PLATFORM: SHARED — map is path convention only; list authority = catalog KEY.
# wave321: runtime* monofile retired — map reports content layer gate seed
# (check / inventory); body builds via ensure_runtime_multi_slice_leaf.
seed_for_main_runtime() {
  local o="$1"
  case "$o" in
    src/main.o|src/main_x.o|src/main_driver.o)
      printf 'seeds/main.from_x.c\n'
      ;;
    src/runtime.o|src/runtime_x.o|src/runtime_driver.o|src/runtime_driver_no_c.o)
      # wave321 7.1.1: monofile seeds/runtime.from_x.c physically retired.
      # Content layer seed is the product multi-slice gate (wave320).
      printf 'seeds/rt_content.from_x.c\n'
      ;;
    *)
      echo "ensure_host_cc_seed_o: no main-runtime seed map for $o" >&2
      exit 1
      ;;
  esac
}

# wave321: R1 runtime*.o leaves — multi-slice only (no monofile host-cc).
# PLATFORM: SHARED freestanding product no_c multi-slice is the sole authority.
is_runtime_multi_slice_leaf() {
  case "$1" in
    src/runtime.o|src/runtime_x.o|src/runtime_driver.o|src/runtime_driver_no_c.o)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

# Build product multi-slice into runtime_driver_no_c.o; optional alias copy for
# archaeology catalog members that historically used monofile + different -D.
# G.7: single body = ensure_rt_prefer_one; no second monofile compile path.
ensure_runtime_multi_slice_leaf() {
  local o="$1"
  local no_c="src/runtime_driver_no_c.o"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o: ensure_runtime_multi_slice_leaf needs <out.o>" >&2
    return 2
  fi
  if ! is_runtime_multi_slice_leaf "$o"; then
    echo "ensure_host_cc_seed_o: $o is not a runtime multi-slice leaf" >&2
    return 1
  fi
  # Product authority always lands on no_c first.
  ensure_rt_prefer_one "$no_c" || return 1
  if [ "$o" != "$no_c" ]; then
    # wave321: monofile flag variants (plain / USE_X_PIPELINE / DRIVER_CFLAGS)
    # retired with physical monofile rm. Catalog still lists these .o for R1
    # inventory; content = multi-slice no_c product object (alias copy).
    mkdir -p "$(dirname "$o")"
    cp -f "$no_c" "$o" || return 1
    log "main-runtime: $o ← multi-slice no_c alias (wave321 monofile retired)"
  fi
  return 0
}

# Extra -D flags for main-runtime family (stdout, space-separated; may be empty).
# wave864: product try-heat thin-call is CC= only; env override still honored when
# set; else shell defaults (authority). Makefile may still define flag bags for
# force_thin_makefile_flags_newer / docs — not recipe inject.
# Family mode: use env when set, else defaults aligned with Makefile base flags.
extras_for_main_runtime() {
  local o="$1"
  case "$o" in
    src/main.o|src/runtime.o)
      ;;
    src/main_x.o|src/runtime_x.o)
      printf '%s' '-DXLANG_USE_X_PIPELINE'
      ;;
    src/main_driver.o)
      printf '%s' '-DXLANG_USE_X_DRIVER -DXLANG_USE_X_PIPELINE'
      ;;
    src/runtime_driver.o)
      if [ -n "${RUNTIME_DRIVER_CFLAGS:-}" ]; then
        printf '%s' "$RUNTIME_DRIVER_CFLAGS"
      else
        printf '%s' "$_DEFAULT_RUNTIME_DRIVER_CFLAGS"
      fi
      ;;
    src/runtime_driver_no_c.o)
      if [ -n "${RUNTIME_DRIVER_NO_C_CFLAGS:-}" ]; then
        printf '%s' "$RUNTIME_DRIVER_NO_C_CFLAGS"
      else
        printf '%s' "$_DEFAULT_RUNTIME_DRIVER_NO_C_CFLAGS"
      fi
      ;;
    *)
      echo "ensure_host_cc_seed_o: no main-runtime extras map for $o" >&2
      exit 1
      ;;
  esac
}

# seed convention (extra-cflags: basename + multi-out sqlite stub).
# PLATFORM: SHARED — map is path convention only; list authority = catalog KEY.
seed_for_extra_cflags() {
  local o="$1"
  case "$o" in
    runtime_sqlite_glue_stub.o)
      printf 'seeds/runtime_sqlite_glue.from_x.c\n'
      ;;
    src/runtime_pipeline_abi.o|runtime_asm_io_stubs.o|runtime_sqlite_glue.o|src/asm/parser_asm_parse_expr_link.o)
      seed_for_o "$o"
      ;;
    *)
      echo "ensure_host_cc_seed_o: no extra-cflags seed map for $o" >&2
      exit 1
      ;;
  esac
}

# Extra flags for extra-cflags family (stdout, space-separated; may be empty).
# wave864: pipeline_abi product thin-call is CC= only; env override still honored;
# else _DEFAULT_RUNTIME_PIPELINE_ABI_CFLAGS. Other leaves use fixed -fPIE/-D bags.
# Family mode: use env when set, else defaults aligned with Makefile base flags.
extras_for_extra_cflags() {
  local o="$1"
  case "$o" in
    src/runtime_pipeline_abi.o)
      if [ -n "${RUNTIME_PIPELINE_ABI_CFLAGS:-}" ]; then
        printf '%s' "$RUNTIME_PIPELINE_ABI_CFLAGS"
      else
        printf '%s' "$_DEFAULT_RUNTIME_PIPELINE_ABI_CFLAGS"
      fi
      ;;
    runtime_asm_io_stubs.o)
      printf '%s' '-fPIE'
      ;;
    runtime_sqlite_glue.o)
      # PLATFORM: SHARED — seed has #ifdef XLANG_DB_USE_SQLITE3 / stub #else.
      # Always defining it makes cc -c require sqlite3.h (Ubuntu gold may not
      # ship libsqlite3). Probe the header; omit the define so stub T
      # xlang_db_use_sqlite3_c still lands. G.7 complete extra-cflags; product
      # -o must not hard-fail on missing sqlite3.h (cookbook sqlite_available).
      if echo '#include <sqlite3.h>' | ${CC:-cc} -E - >/dev/null 2>&1; then
        printf '%s' '-DXLANG_DB_USE_SQLITE3'
      fi
      ;;
    runtime_sqlite_glue_stub.o)
      ;;
    src/asm/parser_asm_parse_expr_link.o)
      if [ -n "${PARSER_ASM_LINK_ALIAS_CFLAGS:-}" ]; then
        printf '%s' "$PARSER_ASM_LINK_ALIAS_CFLAGS"
      else
        printf '%s' "$_DEFAULT_PARSER_ASM_LINK_ALIAS_CFLAGS"
      fi
      ;;
    *)
      echo "ensure_host_cc_seed_o: no extra-cflags extras map for $o" >&2
      exit 1
      ;;
  esac
}


# seed convention (seed-map: basename mismatch + orch basename).
# PLATFORM: SHARED — map is path convention only; list authority = catalog KEY.
# Not a second .o inventory: unknown catalog members fail closed.
seed_for_seed_map() {
  local o="$1"
  case "$o" in
    src/driver/target_cpu.o)
      printf 'seeds/target_cpu_pure.from_x.c\n'
      ;;
    src/ast/ast_seed.o)
      printf 'seeds/runtime_ast_glue.from_x.c\n'
      ;;
    pipeline_bootstrap_orchestration.o)
      printf 'seeds/pipeline_bootstrap_orchestration.from_x.c\n'
      ;;
    # wave758: R4 residual pure host-cc monothin (basename mismatch).
    parser_asm_thin_glue.o)
      printf 'seeds/parser_asm_thin_c.from_x.c\n'
      ;;
    # wave759: R4 residual glue standalone (build_asm/ path; basename seed).
    build_asm/pipeline_glue_standalone.o)
      printf 'seeds/pipeline_glue_standalone.from_x.c\n'
      ;;
    *)
      echo "ensure_host_cc_seed_o: no seed-map seed map for $o" >&2
      exit 1
      ;;
  esac
}

# Extra flags for seed-map family (stdout, space-separated; may be empty).
# wave864: parser_asm_thin_glue product thin-call is CC= only; env override still
# honored; else _DEFAULT_PARSER_ASM_THIN_GLUE_CFLAGS (-D + monothin -I).
# Family mode: orch needs -Ibuild_asm + -D; thin_glue needs NO_SEED_PARSE + -I;
# glue standalone needs -Wno-error=return-type -Ibuild_asm; target_cpu/ast_seed pure.
extras_for_seed_map() {
  local o="$1"
  case "$o" in
    src/driver/target_cpu.o|src/ast/ast_seed.o)
      ;;
    pipeline_bootstrap_orchestration.o)
      printf '%s' '-Ibuild_asm -DPIPELINE_BOOTSTRAP_ORCH_NO_PIPELINE_RUN_WRAPPER'
      ;;
    parser_asm_thin_glue.o)
      if [ -n "${PARSER_ASM_THIN_GLUE_CFLAGS:-}" ]; then
        # Makefile thin may export only -D; always append monothin -I paths.
        printf '%s %s' "$PARSER_ASM_THIN_GLUE_CFLAGS" "-Isrc/lexer -Isrc/asm -Iseeds/parser_asm"
      else
        printf '%s' "$_DEFAULT_PARSER_ASM_THIN_GLUE_CFLAGS"
      fi
      ;;
    # wave759: match Makefile/g05 cc_inc_tu extras (types.inc under build_asm/).
    build_asm/pipeline_glue_standalone.o)
      printf '%s' '-Wno-error=return-type -Ibuild_asm'
      ;;
    *)
      echo "ensure_host_cc_seed_o: no seed-map extras map for $o" >&2
      exit 1
      ;;
  esac
}

# Ensure every .o in catalog KEY via pure host-cc body.
# $1=KEY $2=label $3=seed_mode (basename|frontend-glue|main-runtime|extra-cflags|seed-map)
ensure_catalog_family() {
  local key="$1"
  local label="$2"
  local seed_mode="${3:-basename}"
  local list n=0 o seed extras_str
  list="$(catalog_key_list "$key")"
  # Word-split intentionally (space-separated make expansion).
  # shellcheck disable=SC2086
  for o in $list; do
    [ -z "$o" ] && continue
    # wave321: runtime* R1 leaves never host-cc monofile (multi-slice only).
    if [ "$seed_mode" = "main-runtime" ] && is_runtime_multi_slice_leaf "$o"; then
      ensure_runtime_multi_slice_leaf "$o" || exit 1
      n=$((n + 1))
      continue
    fi
    case "$seed_mode" in
      basename) seed="$(seed_for_o "$o")" ;;
      frontend-glue) seed="$(seed_for_frontend_glue "$o")" ;;
      main-runtime) seed="$(seed_for_main_runtime "$o")" ;;
      extra-cflags) seed="$(seed_for_extra_cflags "$o")" ;;
      seed-map) seed="$(seed_for_seed_map "$o")" ;;
      *)
        echo "ensure_host_cc_seed_o: unknown seed_mode $seed_mode" >&2
        exit 2
        ;;
    esac
    extras_str=""
    case "$seed_mode" in
      main-runtime) extras_str="$(extras_for_main_runtime "$o")" ;;
      extra-cflags) extras_str="$(extras_for_extra_cflags "$o")" ;;
      seed-map) extras_str="$(extras_for_seed_map "$o")" ;;
    esac
    if [ -n "$extras_str" ]; then
      # shellcheck disable=SC2086
      ensure_one "$o" "$seed" $extras_str
    else
      ensure_one "$o" "$seed"
    fi
    n=$((n + 1))
  done
  log "$label OK ($n objs via catalog $key)"
}

ensure_rt_slice() {
  ensure_catalog_family "RT_SEED_SLICE_OBJS" "rt-slice" "basename"
}

ensure_core_seed() {
  ensure_catalog_family "R1_CORE_SEED_OBJS" "core-seed" "basename"
}

ensure_frontend_glue() {
  ensure_catalog_family "R1_FRONTEND_GLUE_OBJS" "frontend-glue" "frontend-glue"
}

ensure_main_runtime() {
  ensure_catalog_family "R1_MAIN_RUNTIME_OBJS" "main-runtime" "main-runtime"
}

ensure_alias_stubs() {
  # Basename convention — same seed_mode as core-seed / rt-slice.
  ensure_catalog_family "R1_ALIAS_STUBS_OBJS" "alias-stubs" "basename"
}

ensure_extra_cflags() {
  # Multi-flag / multi-out pure host-cc (pipeline_abi, -fPIE, sqlite, parser link).
  ensure_catalog_family "R1_EXTRA_CFLAGS_OBJS" "extra-cflags" "extra-cflags"
}

ensure_misc_basename() {
  # Pure basename host-cc without special extras (glue / enc / ctx / pipeline_glue / …).
  ensure_catalog_family "R1_MISC_BASENAME_OBJS" "misc-basename" "basename"
}

ensure_seed_map() {
  # Basename-mismatch + orch -D pure host-cc (target_cpu / ast_seed / orch).
  ensure_catalog_family "R1_SEED_MAP_OBJS" "seed-map" "seed-map"
}

ensure_all_swallowed() {
  ensure_rt_slice
  ensure_core_seed
  ensure_frontend_glue
  ensure_main_runtime
  ensure_alias_stubs
  ensure_extra_cflags
  ensure_misc_basename
  ensure_seed_map
  log "all swallowed R1 families OK (rt-slice + core-seed + frontend-glue + main-runtime + alias-stubs + extra-cflags + misc-basename + seed-map)"
}

# ---------------------------------------------------------------------------
# wave756: try-r1 OUT — pure R1 body for R4 rebuild without hardcoding .o lists.
#
# Resolve OUT by *membership* in catalog KEY families (lists = mk only).
# Exit codes:
#   0 — OUT is pure R1; ensure_one ran (or skipped up-to-date)
#   3 — OUT not in any R1 catalog family (caller should use make residual)
#   1 — membership found but ensure failed / catalog error
# PLATFORM: SHARED — same host-cc body as family modes; no dual recipe.
# Catalog expansion: catalog_blob / catalog_key_list (above; shared file cache).
# ---------------------------------------------------------------------------
catalog_key_words() {
  # $1 = KEY — print space-separated words from cached catalog blob
  local key="$1"
  local line
  line="$(catalog_blob | sed -n "s/^${key}=//p" | head -1)"
  printf '%s\n' "$line"
}

list_has_word() {
  # $1=needle $2=space-separated list
  local needle="$1"
  local list="$2"
  local w
  # shellcheck disable=SC2086
  for w in $list; do
    [ "$w" = "$needle" ] && return 0
  done
  return 1
}

# Print seed_mode for OUT if member of any pure R1 family; else return 1.
# Order: specific maps first (seed-map / frontend-glue / main-runtime / extra-cflags),
# then basename families. KEY membership only — no second .o inventory.
r1_seed_mode_for_o() {
  local o="$1"
  local list
  list="$(catalog_key_words "R1_SEED_MAP_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "seed-map"
    return 0
  fi
  list="$(catalog_key_words "R1_FRONTEND_GLUE_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "frontend-glue"
    return 0
  fi
  list="$(catalog_key_words "R1_MAIN_RUNTIME_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "main-runtime"
    return 0
  fi
  list="$(catalog_key_words "R1_EXTRA_CFLAGS_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "extra-cflags"
    return 0
  fi
  list="$(catalog_key_words "RT_SEED_SLICE_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "basename"
    return 0
  fi
  list="$(catalog_key_words "R1_CORE_SEED_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "basename"
    return 0
  fi
  list="$(catalog_key_words "R1_ALIAS_STUBS_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "basename"
    return 0
  fi
  list="$(catalog_key_words "R1_MISC_BASENAME_OBJS")"
  if list_has_word "$o" "$list"; then
    printf '%s\n' "basename"
    return 0
  fi
  return 1
}

try_ensure_r1_one() {
  local o="$1"
  local seed_mode seed extras_str
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r1: need <out.o>" >&2
    exit 2
  fi
  # sat -B + XLANG_G05_PREFER_X_O=0 used to cold-cc the mega seed
  # (seeds/runtime_link_abi.from_x.c `#ifndef FROM_X`) and wipe prefer
  # labi_*.x slices. Route like pipeline_abi: single body
  # ensure_labi_prefer_one (FROM_X default 1 still hybrids). Do **not**
  # gate on G05_PREFER=1. G.7: no second labi builder.
  # PLATFORM: SHARED — sat try-r1 + g05 try-labi-prefer share one body.
  if [ "$o" = "src/runtime_link_abi.o" ]; then
    ensure_labi_prefer_one "$o" || return 1
    return 0
  fi
  # wave176 / L4: pipeline_abi always routes through ensure_pipeline_abi_prefer_one
  # (hybrid when egg exists; cold seed last resort). Do **not** gate on PREFER=1 —
  # sat rebuild sets PREFER=0 and would otherwise cold-cc the broken full seed and
  # wipe a good hybrid .o. G.7: single body wave767.
  # PLATFORM: SHARED · pin egg required for true-cold hybrid.
  if [ "$o" = "src/runtime_pipeline_abi.o" ]; then
    ensure_pipeline_abi_prefer_one "$o" || return 1
    return 0
  fi
  # wave321 7.1.1: runtime monofile retired — multi-slice product body only.
  if is_runtime_multi_slice_leaf "$o"; then
    ensure_runtime_multi_slice_leaf "$o" || return 1
    return 0
  fi
  if ! seed_mode="$(r1_seed_mode_for_o "$o")"; then
    # Not pure R1 — honest residual for R2/R3/gen/etc.
    return 3
  fi
  case "$seed_mode" in
    basename) seed="$(seed_for_o "$o")" ;;
    frontend-glue) seed="$(seed_for_frontend_glue "$o")" ;;
    main-runtime) seed="$(seed_for_main_runtime "$o")" ;;
    extra-cflags) seed="$(seed_for_extra_cflags "$o")" ;;
    seed-map) seed="$(seed_for_seed_map "$o")" ;;
    *)
      echo "ensure_host_cc_seed_o try-r1: unknown seed_mode $seed_mode for $o" >&2
      exit 1
      ;;
  esac
  extras_str=""
  case "$seed_mode" in
    main-runtime) extras_str="$(extras_for_main_runtime "$o")" ;;
    extra-cflags) extras_str="$(extras_for_extra_cflags "$o")" ;;
    seed-map) extras_str="$(extras_for_seed_map "$o")" ;;
  esac
  if [ -n "$extras_str" ]; then
    # shellcheck disable=SC2086
    ensure_one "$o" "$seed" $extras_str
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

# ---------------------------------------------------------------------------
# wave757: try-r3-cold OUT — R3 cold-else pure host-cc without dual .o lists.
#
# Membership = catalog R3_COLD_SEED_OBJS only (lists = mk).
# Seed = basename convention (seeds/<leaf>.from_x.c); same ensure_one as R1.
# Exit codes:
#   0 — OUT is R3 cold-seed member; ensure_one ran (or skipped up-to-date)
#   3 — OUT not in R3_COLD_SEED_OBJS (caller residual make)
#   1 — membership found but ensure failed / catalog error
# PLATFORM: SHARED — cold path body only; PREFER thin+rest remains Makefile.
# ---------------------------------------------------------------------------
try_ensure_r3_cold_one() {
  local o="$1"
  local list seed
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r3-cold: need <out.o>" >&2
    exit 2
  fi
  list="$(catalog_key_words "R3_COLD_SEED_OBJS")"
  if ! list_has_word "$o" "$list"; then
    return 3
  fi
  seed="$(seed_for_o "$o")"
  ensure_one "$o" "$seed"
  return 0
}

ensure_r3_cold_seed() {
  ensure_catalog_family "R3_COLD_SEED_OBJS" "r3-cold-seed" "basename"
}

# ---------------------------------------------------------------------------
# wave763/764: try-r3-prefer OUT — R3 PREFER thin+rest product path (single body).
# Stage 12.0.5 pure-asm hybrid (opt-in PREFER_ASM_O; not product-default):
#   thin via rt_prefer_try_x_to_o → pure_asm_x_to_o first. Freestanding reject
#   covers U xlang_driver_*_opaque (rdabi fallthrough -E). ptr+int ADD uses
#   scale1 64-bit (glue_try_emit_ptr_arith_scaled) — closes pure-asm rio IO001.
#   Dual-end R3 hybrid 9/9 pure-ld + matrix 5/5 @ tip after fix.

#
# Membership = catalog R3_COLD_SEED_OBJS only (lists = mk; same KEY as cold).
# When XLANG_G05_PREFER_X_O=1 and ./xlang-c is executable:
#   wave764 ladder (per leaf map):
#     1) optional full.x + full rest -D (R2 full surface; simd/backend)
#     2) thin.x (or primary .x) + thin rest -D
#     3) ld -r prefer.o rest.o → OUT (Darwin arch + multidef; ELF/PE allow-multidef)
#     4) optional nm symbol gate (simd_enc / simd_loop) — fail → next ladder step
# Prefer fail / PREFER≠1 / no xlang-c → ensure_one cold seed (try-r3-cold twin).
# Callers: Makefile nine leaves (wave763) · g05 r3-prefer-family (wave764).
# Exit codes:
#   0 — OUT is R3_COLD member; prefer or cold body produced OUT
#   3 — OUT not in R3_COLD_SEED_OBJS
#   1 — membership found but both prefer and cold failed
# PLATFORM: SHARED shell body · Darwin ld -r arch/multidef · cold chain PREFER=0.
# G.7: no second .o list; per-leaf x/rest-defs/nm/full are seed-path conventions.
# ---------------------------------------------------------------------------

# R3 prefer leaf map — NOT an .o inventory (membership = catalog only).
# stdout fields (pipe-separated):
#   thin_x | thin_rest_defs | nm_sym | full_x_or_- | full_rest_defs_or_-
# rest_defs = comma-joined -D tokens without -D prefix.
# PLATFORM: SHARED — Makefile phase4 thin + former g05 full ladder (wave764).
r3_prefer_leaf_spec() {
  local o="$1"
  case "$o" in
    src/runtime_io_abi.o)
      # Primary surface is full .x (not *_thin.x); dual rest -D historical.
      printf '%s\n' "src/runtime_io_abi.x|XLANG_L2_RIO_THIN_FROM_X,XLANG_RUNTIME_IO_ABI_FROM_X|-|-|-"
      ;;
    src/runtime_driver_abi.o)
      printf '%s\n' "src/runtime_driver_abi_thin.x|XLANG_L2_RDABI_THIN_FROM_X|-|-|-"
      ;;
    src/runtime_driver_diagnostic.o)
      printf '%s\n' "src/runtime_driver_diagnostic_thin.x|XLANG_L2_RDD_THIN_FROM_X|-|-|-"
      ;;
    src/asm/simd_enc.o)
      # wave764: full.x first (R2 H=0), then thin L2; nm gate on both.
      printf '%s\n' "src/asm/simd_enc_thin.x|XLANG_L2_SIMD_ENC_THIN_FROM_X|simd_rbp_disp32|src/asm/simd_enc.x|XLANG_SIMD_ENC_FROM_X"
      ;;
    src/asm/simd_loop.o)
      printf '%s\n' "src/asm/simd_loop_thin.x|XLANG_L2_SIMD_LOOP_THIN_FROM_X|glue_simd_loop_pick_lanes_c|src/asm/simd_loop.x|XLANG_SIMD_LOOP_FROM_X"
      ;;
    src/asm/backend_enc_dispatch.o)
      # nm gate: full.x / thin.x still miss Cap residual f64 enc (addsd/divsd/…);
      # hybrid under FROM_X empties rest bodies → L4 pure-ld UNDEF from
      # runtime_pipeline_abi. Gate fails prefer → cold full seed (has symbols).
      # PLATFORM: SHARED · remove gate when .x exports backend_enc_addsd_rax_rbx_arch.
      printf '%s\n' "src/asm/backend_enc_dispatch_thin.x|XLANG_L2_ENC_DISPATCH_THIN_FROM_X|backend_enc_addsd_rax_rbx_arch|src/asm/backend_enc_dispatch.x|XLANG_BACKEND_ENC_DISPATCH_FROM_X"
      ;;
    src/asm/backend_arch_emit_dispatch.o)
      printf '%s\n' "src/asm/backend_arch_emit_dispatch_thin.x|XLANG_L2_ARCH_EMIT_THIN_FROM_X|-|src/asm/backend_arch_emit_dispatch.x|XLANG_BACKEND_ARCH_EMIT_DISPATCH_FROM_X"
      ;;
    src/asm/backend_try_inline_dispatch.o)
      printf '%s\n' "src/asm/backend_try_inline_dispatch_thin.x|XLANG_L2_TRY_INLINE_THIN_FROM_X|-|src/asm/backend_try_inline_dispatch.x|XLANG_BACKEND_TRY_INLINE_DISPATCH_FROM_X"
      ;;
    src/asm/backend_call_dispatch.o)
      printf '%s\n' "src/asm/backend_call_dispatch_thin.x|XLANG_L2_CALL_DISPATCH_THIN_FROM_X|-|src/asm/backend_call_dispatch.x|XLANG_BACKEND_CALL_DISPATCH_FROM_X"
      ;;
    *)
      return 1
      ;;
  esac
}

r3_prefer_ld_r_flags() {
  # stdout: ld args for partial link (no -o / inputs). PLATFORM: SHARED.
  local uname_s uname_m
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  if [ "$uname_s" = "Darwin" ]; then
    case "$uname_m" in
      arm64|aarch64) printf '%s\n' "-arch arm64 -r -multiply_defined suppress" ;;
      x86_64|amd64)  printf '%s\n' "-arch x86_64 -r -multiply_defined suppress" ;;
      *)             printf '%s\n' "-r -multiply_defined suppress" ;;
    esac
  else
    # PLATFORM: LINUX|WINDOWS (ELF/PE) — GNU ld multidef for thin+rest merge.
    printf '%s\n' "-r --allow-multiple-definition"
  fi
}

r3_prefer_nm_has_sym() {
  # $1=out.o $2=symbol (unadorned). Accepts Darwin leading underscore.
  local o="$1" sym="$2"
  [ -z "$sym" ] || [ "$sym" = "-" ] && return 0
  nm -gU "$o" 2>/dev/null | awk -v s="$sym" '
    $0 ~ (" " s "$") || $0 ~ (" _" s "$") { found=1 }
    END { exit !found }
  '
}

# Try one prefer step: thin.x → .o (rt_prefer prologue) + seed rest -D → ld -r OUT.
# $1=out.o $2=x_src $3=rest_csv $4=nm_sym $5=seed $6=xlang_bin
# Returns 0 on success (OUT written + nm ok).
#
# G.7 / wave190: thin compile MUST reuse rt_prefer_try_x_to_o (single -E prologue
# authority). Bare `xlang -E | cc` left U xlang_driver_* on pure
# runtime_driver_abi_thin (stdout_ptr / fputs_opaque / … are static inline only
# inside that harness). PLATFORM: SHARED.
r3_prefer_try_step() {
  local o="$1" x_src="$2" rest_csv="$3" nm_sym="$4" seed="$5" xlang_bin="$6"
  local thin_o rest_o ld_flags d_args=() d
  local label="${x_src##*/}"

  [ -n "$x_src" ] && [ "$x_src" != "-" ] && [ -f "$x_src" ] || return 1
  [ -f "$seed" ] || return 1
  [ -x "$xlang_bin" ] || return 1

  thin_o="${o%.o}_prefer_step.o"
  rest_o="${o%.o}_prefer_rest.o"
  mkdir -p "$(dirname "$o")"
  # Thin surface: same prologue as try-pipeline-abi / g05 (xlang_driver_* inlines).
  if ! rt_prefer_try_x_to_o "$x_src" "$thin_o"; then
    rm -f "$thin_o" "$rest_o"
    return 1
  fi
  d_args=()
  if [ -n "$rest_csv" ] && [ "$rest_csv" != "-" ]; then
    IFS=',' read -r -a _defs <<< "$rest_csv"
    for d in "${_defs[@]}"; do
      [ -n "$d" ] && d_args+=("-D$d")
    done
  fi
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
    "${d_args[@]}" -c "$seed" -o "$rest_o" 2>/dev/null; then
    rm -f "$thin_o" "$rest_o"
    return 1
  fi
  ld_flags="$(r3_prefer_ld_r_flags)"
  # shellcheck disable=SC2086
  if ld $ld_flags -o "$o" "$thin_o" "$rest_o" 2>/dev/null \
    && r3_prefer_nm_has_sym "$o" "$nm_sym"; then
    log "prefer thin+rest $o <- $x_src + $seed ($label; try-r3-prefer)"
    rm -f "$thin_o" "$rest_o"
    return 0
  fi
  rm -f "$thin_o" "$rest_o"
  return 1
}

ensure_r3_prefer_one() {
  # Prefer ladder (full→thin) or cold seed for one R3_COLD member (no membership check).
  local o="$1"
  local spec x_src rest_csv nm_sym full_x full_rest seed
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local xlang_bin="./xlang-c"
  local ok=0
  local stale=0

  seed="$(seed_for_o "$o")"
  if ! spec="$(r3_prefer_leaf_spec "$o")"; then
    echo "ensure_host_cc_seed_o try-r3-prefer: no leaf spec for $o" >&2
    return 1
  fi
  x_src="$(printf '%s' "$spec" | cut -d'|' -f1)"
  rest_csv="$(printf '%s' "$spec" | cut -d'|' -f2)"
  nm_sym="$(printf '%s' "$spec" | cut -d'|' -f3)"
  full_x="$(printf '%s' "$spec" | cut -d'|' -f4)"
  full_rest="$(printf '%s' "$spec" | cut -d'|' -f5)"
  [ -z "$full_x" ] && full_x="-"
  [ -z "$full_rest" ] && full_rest="-"

  # Up-to-date skip (make / g05 already gated; shell direct calls benefit).
  # wave764: also consider full.x mtime when present.
  if [ "$FORCE" != "1" ] && [ -f "$o" ] && [ -f "$seed" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    if [ -n "$full_x" ] && [ "$full_x" != "-" ] && [ -f "$full_x" ] && [ "$full_x" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (r3-prefer)"
      return 0
    fi
  fi

  # PLATFORM: SHARED cold-chain — only PREFER=1 may thin (Darwin history: thin
  # with PREFER=0 left UNDEFs in phase1). wave763 unified PREFER=1 for all nine;
  # wave764 full→thin ladder for g05 R2 full surface (simd/backend).
  if [ "$prefer" = "1" ] && [ -x "$xlang_bin" ] && [ -f "$seed" ]; then
    # 1) optional full.x first
    if [ -n "$full_x" ] && [ "$full_x" != "-" ] && [ -f "$full_x" ]; then
      if r3_prefer_try_step "$o" "$full_x" "$full_rest" "$nm_sym" "$seed" "$xlang_bin"; then
        ok=1
      fi
    fi
    # 2) thin / primary .x
    if [ "$ok" != "1" ] && [ -f "$x_src" ]; then
      if r3_prefer_try_step "$o" "$x_src" "$rest_csv" "$nm_sym" "$seed" "$xlang_bin"; then
        ok=1
      fi
    fi
  fi

  if [ "$ok" = "1" ]; then
    return 0
  fi

  # Cold fallback — same ensure_one as try-r3-cold.
  # Force when prefer path may have left a partial/bad OUT (e.g. nm gate fail).
  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-r3-prefer: missing seed $seed for $o" >&2
    return 1
  fi
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    # Prefer attempted: never keep a thin that failed nm / ld semantics.
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_r3_prefer_one() {
  local o="$1"
  local list
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r3-prefer: need <out.o>" >&2
    exit 2
  fi
  list="$(catalog_key_words "R3_COLD_SEED_OBJS")"
  if ! list_has_word "$o" "$list"; then
    return 3
  fi
  ensure_r3_prefer_one "$o"
  return 0
}

ensure_r3_prefer() {
  # Family mode: all R3_COLD members via prefer-or-cold body.
  local list o
  list="$(catalog_key_words "R3_COLD_SEED_OBJS")"
  if [ -z "$list" ]; then
    echo "ensure_host_cc_seed_o r3-prefer: empty R3_COLD_SEED_OBJS" >&2
    exit 1
  fi
  for o in $list; do
    ensure_r3_prefer_one "$o" || return 1
  done
}


# ---------------------------------------------------------------------------
# wave765: try-labi-prefer OUT — g05 labi multi-slice product PREFER (single body).
#
# Single leaf: src/runtime_link_abi.o (in R1_CORE_SEED_OBJS; cold twin = ensure_one).
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   L0..L9 + L8b(+L8c capacity split) prefer .x → .o (else cold layer seed)
#   rest = seeds/runtime_link_abi.from_x.c with XLANG_LABI_*_FROM_X for ok layers
#   merge: $CC -r -nostdlib slices + rest → OUT
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold full seed (same as core-seed).
# Callers: g05_ensure (wave765) · Makefile src/runtime_link_abi.o (unified)
#   · sat try-r1 (same body; no mega `#ifndef` wipe).
# Exit codes:
#   0 — OUT is runtime_link_abi.o; prefer or cold body produced OUT
#   3 — OUT is not src/runtime_link_abi.o
#   1 — membership found but cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# G.7: no second .o list; layer table is seed-path convention (not product inventory).
# Residual after: rt multi-slice · pipeline_abi · ldpc · target_cpu · pure-ld · physical delete.
# ---------------------------------------------------------------------------

# True when this host's product -E binary is a leftover Windows PE that cannot
# compile tip .x sources (e.g. pipeline_abi mega 92k LOC or labi multi-slice).
# PLATFORM: WINDOWS — 2026-07-31 leftover PE is present for Track L / can_run
# egg pick, but attempting -E with it hangs or corrupts stdout.
windows_leftover_pe_cannot_e() {
  case "$(uname -s 2>/dev/null)" in
    MINGW*|MSYS*|CYGWIN*) return 0 ;;
  esac
  return 1
}

labi_prefer_pick_xlang() {
  # PLATFORM: WINDOWS — leftover PE cannot -E tip slices; fallback to cold seed.
  if windows_leftover_pe_cannot_e; then
    return 1
  fi
  # stdout: first executable product binary.
  local b
  for b in ./xlang ./xlang-c ./bootstrap_xlangc; do
    if [ -x "$b" ]; then
      printf '%s\n' "$b"
      return 0
    fi
  done
  return 1
}

# Prefer one layer .x → .o (simple -E harness; fail → caller seed).
# $1=x_src $2=out.o  Returns 0 on success.
# Stage 12.0.5 labi-only pure-asm product default (authorized 2026-08-12):
#   · XLANG_PREFER_ASM_O_LABI defaults to 1 → scoped XLANG_PREFER_ASM_O=1 for
#     pure_asm_x_to_o only (subshell; does NOT leak tree-level PREFER_ASM_O).
#   · pure_asm reject (panic/__error/CG002/ONLY miss) → fall through -E+$CC.
#   · Escape hatch: XLANG_PREFER_ASM_O_LABI=0 → historic -E+$CC. Ambient tree
#     PREFER_ASM_O does NOT re-enable pure-asm unless
#     XLANG_ALLOW_TREE_PREFER_ASM=1 (product entry also strips tree PREFER).
# Peer defaults (same-day auth wave): XLANG_PREFER_ASM_O_RT (rt_prefer harness
# families: rt/async/R3/l2-asm/B1–B3/…) and XLANG_PREFER_ASM_O_G05 (g05_try).
#   · pipeline_abi mega pure-asm: product open (opaque WEAK on driver_abi bag;
#     hang wall closed typeck slim dual-end <90s emit).
# PLATFORM: SHARED — retry -E then -backend c -E (Ubuntu SIGSEGV history).
# G.7: single pure_asm_x_to_o authority; no second pure-asm helper.
labi_prefer_try_x_to_o() {
  local x_src="$1" x_out="$2" xlang_bin tmp e_ok e_try
  [ -f "$x_src" ] || return 1
  mkdir -p "$(dirname "$x_out")"
  # Labi-only pure-asm default: scope PREFER_ASM_O=1 inside subshell so
  # pure_asm_x_to_o (G.7) runs without flipping tree-level product defaults.
  # When LABI=0: unset ambient PREFER unless ALLOW_TREE (close tree leak).
  # PLATFORM: SHARED.
  if (
    if [ "${XLANG_PREFER_ASM_O_LABI:-1}" = "1" ]; then
      export XLANG_PREFER_ASM_O=1
    elif [ "${XLANG_ALLOW_TREE_PREFER_ASM:-0}" != "1" ]; then
      unset XLANG_PREFER_ASM_O
    fi
    pure_asm_x_to_o "$x_out" "$x_src"
  ); then
    return 0
  fi
  xlang_bin="$(labi_prefer_pick_xlang)" || return 1
  tmp="$(mktemp "${TMPDIR:-/tmp}/labipref.XXXXXX")"
  e_ok=0
  for e_try in 1 2 3 4 5; do
    if "$xlang_bin" -E "$x_src" >"$tmp" 2>/dev/null && [ -s "$tmp" ]; then
      e_ok=1
      break
    fi
    : >"$tmp"
    if "$xlang_bin" -backend c -E "$x_src" >"$tmp" 2>/dev/null && [ -s "$tmp" ]; then
      e_ok=1
      break
    fi
    : >"$tmp"
  done
  if [ "$e_ok" != "1" ]; then
    rm -f "$tmp"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS -I. -Iinclude -Isrc -x c -c -o "$x_out" "$tmp" 2>/dev/null; then
    rm -f "$tmp"
    return 1
  fi
  rm -f "$tmp"
  return 0
}

# Compile one layer: prefer .x else seed → tmp .o. Sets ok via nameref-ish stdout.
# $1=label $2=x $3=seed $4=out_tmp  → 0 if layer .o ready.
labi_prefer_layer() {
  local label="$1" x_src="$2" seed="$3" out_tmp="$4"
  # wave326: XLANG_LINK_ABI_FROM_X is the new pin-close default;
  # XLANG_G05_PREFER_X_O remains as legacy g05-wide escape hatch.
  local prefer="${XLANG_LINK_ABI_FROM_X:-${XLANG_G05_PREFER_X_O:-0}}"
  if [ "$prefer" = "1" ] && [ -f "$x_src" ]; then
    if labi_prefer_try_x_to_o "$x_src" "$out_tmp"; then
      log "labi $label ← $x_src (prefer .x)"
      return 0
    fi
  fi
  if [ -f "$seed" ]; then
    # shellcheck disable=SC2086
    if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$out_tmp" "$seed" 2>/dev/null; then
      log "labi $label ← $seed (cold seed slice)"
      return 0
    fi
  fi
  return 1
}

ensure_labi_prefer_one() {
  # Prefer multi-slice or cold full seed for src/runtime_link_abi.o (no membership check).
  local o="$1"
  local seed="seeds/runtime_link_abi.from_x.c"
  # wave326: XLANG_LINK_ABI_FROM_X is the pin-close default (1 = labi_*.x authoritative);
  # XLANG_G05_PREFER_X_O remains as legacy g05-wide escape. ALLOW_PIN=1 keeps
  # true-cold egg path: if no xlang binary → compile full seed as archaeology fallback.
  local prefer="${XLANG_LINK_ABI_FROM_X:-${XLANG_G05_PREFER_X_O:-0}}"
  local stale=0 done=0
  local l0_o l1_o l2_o l3_o l4_o l5_o l6_o l7_o l8_o l8b_o l8c_o l9_o rest_o
  local l0_ok=0 l1_ok=0 l2_ok=0 l3_ok=0 l4_ok=0 l5_ok=0 l6_ok=0 l7_ok=0
  local l8_ok=0 l8b_ok=0 l8c_ok=0 l9_ok=0
  local l8b_x_ok=0 l8c_x_ok=0
  local rest_defs link_objs
  # Layer paths (seed-path convention; not a product .o list).
  local l0_x=src/runtime/labi_path_pure.x l0_seed=seeds/labi_path_pure.from_x.c
  local l1_x=src/runtime/labi_diag_pure.x l1_seed=seeds/labi_diag_pure.from_x.c
  local l2_x=src/runtime/labi_host_lit.x l2_seed=seeds/labi_host_lit.from_x.c
  local l3_x=src/runtime/labi_path_io.x l3_seed=seeds/labi_path_io.from_x.c
  local l4_x=src/runtime/labi_ensure_list.x l4_seed=seeds/labi_ensure_list.from_x.c
  local l5_x=src/runtime/labi_invoke_cc_list.x l5_seed=seeds/labi_invoke_cc_list.from_x.c
  local l6_x=src/runtime/labi_invoke_ld_list.x l6_seed=seeds/labi_invoke_ld_list.from_x.c
  local l7_x=src/runtime/labi_freestanding_list.x l7_seed=seeds/labi_freestanding_list.from_x.c
  local l8_x=src/runtime/labi_std_list.x l8_seed=seeds/labi_std_list.from_x.c
  local l8b_x=src/runtime/labi_ondemand_list.x l8b_seed=seeds/labi_ondemand_list.from_x.c
  local l8c_x=src/runtime/labi_ondemand_heavy.x
  local l9_x=src/runtime/labi_gates.x l9_seed=seeds/labi_gates.from_x.c

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-labi-prefer: missing seed $seed" >&2
    return 1
  fi

  # Up-to-date skip: seed + any layer .x / layer seed newer → rebuild.
  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    for f in \
      "$l0_x" "$l0_seed" "$l1_x" "$l1_seed" "$l2_x" "$l2_seed" \
      "$l3_x" "$l3_seed" "$l4_x" "$l4_seed" "$l5_x" "$l5_seed" \
      "$l6_x" "$l6_seed" "$l7_x" "$l7_seed" "$l8_x" "$l8_seed" \
      "$l8b_x" "$l8b_seed" "$l8c_x" "$l9_x" "$l9_seed"
    do
      if [ -f "$f" ] && [ "$f" -nt "$o" ]; then
        stale=1
        break
      fi
    done
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (labi-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # Multi-slice prefer only when PREFER=1 (Darwin cold-chain safety twin of R3).
  if [ "$prefer" = "1" ] && labi_prefer_pick_xlang >/dev/null 2>&1; then
    l0_o="$(mktemp "${TMPDIR:-/tmp}/labi_l0.XXXXXX")"
    l1_o="$(mktemp "${TMPDIR:-/tmp}/labi_l1.XXXXXX")"
    l2_o="$(mktemp "${TMPDIR:-/tmp}/labi_l2.XXXXXX")"
    l3_o="$(mktemp "${TMPDIR:-/tmp}/labi_l3.XXXXXX")"
    l4_o="$(mktemp "${TMPDIR:-/tmp}/labi_l4.XXXXXX")"
    l5_o="$(mktemp "${TMPDIR:-/tmp}/labi_l5.XXXXXX")"
    l6_o="$(mktemp "${TMPDIR:-/tmp}/labi_l6.XXXXXX")"
    l7_o="$(mktemp "${TMPDIR:-/tmp}/labi_l7.XXXXXX")"
    l8_o="$(mktemp "${TMPDIR:-/tmp}/labi_l8.XXXXXX")"
    l8b_o="$(mktemp "${TMPDIR:-/tmp}/labi_l8b.XXXXXX")"
    l8c_o="$(mktemp "${TMPDIR:-/tmp}/labi_l8c.XXXXXX")"
    l9_o="$(mktemp "${TMPDIR:-/tmp}/labi_l9.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/labi_rest.XXXXXX")"

    labi_prefer_layer L0 "$l0_x" "$l0_seed" "$l0_o" && l0_ok=1
    labi_prefer_layer L1 "$l1_x" "$l1_seed" "$l1_o" && l1_ok=1
    labi_prefer_layer L2 "$l2_x" "$l2_seed" "$l2_o" && l2_ok=1
    labi_prefer_layer L3 "$l3_x" "$l3_seed" "$l3_o" && l3_ok=1
    labi_prefer_layer L4 "$l4_x" "$l4_seed" "$l4_o" && l4_ok=1
    labi_prefer_layer L5 "$l5_x" "$l5_seed" "$l5_o" && l5_ok=1
    labi_prefer_layer L6 "$l6_x" "$l6_seed" "$l6_o" && l6_ok=1
    labi_prefer_layer L7 "$l7_x" "$l7_seed" "$l7_o" && l7_ok=1
    labi_prefer_layer L8 "$l8_x" "$l8_seed" "$l8_o" && l8_ok=1
    labi_prefer_layer L9 "$l9_x" "$l9_seed" "$l9_o" && l9_ok=1

    # wave263: L8b early + L8c heavy must BOTH prefer .x, else full L8b seed covers both.
    if [ "$prefer" = "1" ] && [ -f "$l8b_x" ] && labi_prefer_try_x_to_o "$l8b_x" "$l8b_o"; then
      l8b_x_ok=1
    fi
    if [ "$prefer" = "1" ] && [ -f "$l8c_x" ] && labi_prefer_try_x_to_o "$l8c_x" "$l8c_o"; then
      l8c_x_ok=1
    fi
    if [ "$l8b_x_ok" = "1" ] && [ "$l8c_x_ok" = "1" ]; then
      l8b_ok=1
      l8c_ok=1
      log "labi L8b+L8c ← $l8b_x + $l8c_x (capacity split)"
    elif [ -f "$l8b_seed" ]; then
      # shellcheck disable=SC2086
      if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$l8b_o" "$l8b_seed" 2>/dev/null; then
        l8b_ok=1
        l8c_ok=0
        log "labi L8b ← $l8b_seed (full seed; L8c unused)"
      fi
    fi

    # Rest FROM_X flags (L0 always required for hybrid path).
    rest_defs="-DXLANG_LABI_PATH_PURE_FROM_X"
    [ "$l1_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_DIAG_PURE_FROM_X"
    [ "$l2_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_HOST_LIT_FROM_X"
    [ "$l3_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_PATH_IO_FROM_X"
    [ "$l4_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_ENSURE_LIST_FROM_X"
    [ "$l5_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_INVOKE_CC_LIST_FROM_X"
    [ "$l6_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_INVOKE_LD_LIST_FROM_X"
    [ "$l7_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_FREESTANDING_LIST_FROM_X"
    [ "$l8_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_STD_LIST_FROM_X"
    [ "$l8b_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_ONDEMAND_LIST_FROM_X"
    [ "$l9_ok" = "1" ] && rest_defs="$rest_defs -DXLANG_LABI_GATES_FROM_X"

    if [ "$l0_ok" = "1" ]; then
      # shellcheck disable=SC2086
      if $CC $BASE_CFLAGS -I. -Iinclude -Isrc $rest_defs -c -o "$rest_o" "$seed" 2>/dev/null; then
        link_objs="$l0_o"
        [ "$l1_ok" = "1" ] && link_objs="$link_objs $l1_o"
        [ "$l2_ok" = "1" ] && link_objs="$link_objs $l2_o"
        [ "$l3_ok" = "1" ] && link_objs="$link_objs $l3_o"
        [ "$l4_ok" = "1" ] && link_objs="$link_objs $l4_o"
        [ "$l5_ok" = "1" ] && link_objs="$link_objs $l5_o"
        [ "$l6_ok" = "1" ] && link_objs="$link_objs $l6_o"
        [ "$l7_ok" = "1" ] && link_objs="$link_objs $l7_o"
        [ "$l8_ok" = "1" ] && link_objs="$link_objs $l8_o"
        [ "$l8b_ok" = "1" ] && link_objs="$link_objs $l8b_o"
        [ "$l8c_ok" = "1" ] && link_objs="$link_objs $l8c_o"
        [ "$l9_ok" = "1" ] && link_objs="$link_objs $l9_o"
        # shellcheck disable=SC2086
        # PLATFORM: SHARED — historic g05 used $CC -r -nostdlib (not ld Darwin flags).
        if pure_ld_partial_merge "$o" $link_objs "$rest_o" 2>/dev/null; then
          log "prefer multi-slice $o <- L0..L9+L8b+L8c + link_abi rest (try-labi-prefer)"
          done=1
        fi
      fi
    fi
    rm -f "$l0_o" "$l1_o" "$l2_o" "$l3_o" "$l4_o" "$l5_o" "$l6_o" \
      "$l7_o" "$l8_o" "$l8b_o" "$l8c_o" "$l9_o" "$rest_o"
    if [ "$done" = "0" ]; then
      log "labi multi-slice hybrid failed; fallback full seed"
    fi
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full seed (ensure_one twin / PREFER=0).
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_labi_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-labi-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ "$o" != "src/runtime_link_abi.o" ]; then
    return 3
  fi
  ensure_labi_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave766: try-rt-prefer OUT — g05 rt multi-slice product PREFER (single body).
#
# Single leaf: src/runtime_driver_no_c.o (R1_MAIN_RUNTIME; cold twin = ensure_one
# with RUNTIME_DRIVER_NO_C_CFLAGS).
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   content + util + argv + emit_flags + compile + run + asm + entry + diag +
#   elf_diag + lib_root + fs + fmt + dispatch* + run_*  prefer thin/full .x
#   → slice .o (else cold layer seed); rest = seeds/runtime.from_x.c under
#   XLANG_RT_*_FROM_X for ok layers; merge $CC -r -nostdlib slices + rest → OUT.
# PLATFORM: SHARED — do NOT merge RT_SEED_SLICE permanent .o into no_c
#   (arena/emit_state/preamble/stack/parse_diag stay external; FROM_X on rest
#   leaves them U in no_c — historic Darwin 22× multidef fix).
# Prefer fail / partial slices → **refuse** monofile by default (wave320);
#   set XLANG_RT_ALLOW_MONOFILE_LAST_RESORT=1 to restore monofile + NO_C last resort.
# wave319: PREFER=0 still multi-slices from cold layer seeds; omit empty mega when full.
# wave320: gate on content layer seed; product path never host-cc monofile unless escape.
# Callers: g05_ensure (wave766) · heat / try-rt-prefer product leaf.
# Exit codes:
#   0 — OUT is runtime_driver_no_c.o; multi-slice (or allow-escape monofile) produced OUT
#   3 — OUT is not src/runtime_driver_no_c.o
#   1 — multi-slice incomplete / monofile refused / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0 multi-slice.
# G.7: no second .o list; layer table is seed-path convention (not product inventory).
# Residual after wave321 monofile rm: typeck 7.4.1 · LEGACY monofile flag variants.
# ---------------------------------------------------------------------------

rt_prefer_no_c_cflags() {
  # stdout: NO_C product flags (Makefile/env or default).
  if [ -n "${RUNTIME_DRIVER_NO_C_CFLAGS:-}" ]; then
    printf '%s' "$RUNTIME_DRIVER_NO_C_CFLAGS"
  else
    printf '%s' "$_DEFAULT_RUNTIME_DRIVER_NO_C_CFLAGS"
  fi
}

rt_prefer_try_x_to_o() {
  _xsrc="$1"
  _xout="$2"
  shift 2
  _xxlang=""
  if [ -x ./xlang ]; then
    _xxlang=./xlang
  elif [ -x ./xlang-c ]; then
    _xxlang=./xlang-c
  elif [ -x ./bootstrap_xlangc ]; then
    _xxlang=./bootstrap_xlangc
  else
    return 1
  fi
  if [ ! -f "$_xsrc" ]; then
    return 1
  fi
  mkdir -p "$(dirname "$_xout")"
  # Stage 12.0.5 prefer-family pure-asm product default (authorized 2026-08-12):
  #   · XLANG_PREFER_ASM_O_RT defaults to 1 → scoped XLANG_PREFER_ASM_O=1 for
  #     pure_asm_x_to_o only (subshell; does NOT leak tree-level PREFER_ASM_O).
  #   · Covers every prefer family that reuses this harness: try-rt-prefer,
  #     try-r3-prefer, try-async-prefer, try-l2-asm-prefer, try-target-cpu /
  #     try-ldpc / try-other-l2, B1 runtime-os / B2 std-core / B3 lsp-sat, etc.
  #   · pure_asm reject (panic/__error/CG002/ONLY miss/WEAK polish fail) →
  #     fall through -E+$CC (same as labi default path).
  #   · Escape hatch: XLANG_PREFER_ASM_O_RT=0 → historic -E+$CC. Ambient tree
  #     PREFER does NOT re-enable pure-asm unless XLANG_ALLOW_TREE_PREFER_ASM=1.
  #   · Ban: tree-level PREFER_ASM_O=1 as product default (hard strip + family=0).
  #     pipeline_abi mega product pure-asm skip (Cap residual; opaque WEAK closed).
  # PLATFORM: SHARED harness · G.7 single pure_asm_x_to_o authority.
  # Labi keeps its own XLANG_PREFER_ASM_O_LABI gate in labi_prefer_try_x_to_o.
  if (
    if [ "${XLANG_PREFER_ASM_O_RT:-1}" = "1" ]; then
      export XLANG_PREFER_ASM_O=1
    elif [ "${XLANG_ALLOW_TREE_PREFER_ASM:-0}" != "1" ]; then
      unset XLANG_PREFER_ASM_O
    fi
    pure_asm_x_to_o "$_xout" "$_xsrc"
  ); then
    return 0
  fi
  # Historic product path: -E → prologue → $CC -c.
  # BSD/macOS mktemp 要求 X 串在模板末尾；勿用 XXXXXX.c
  _xtmp=$(mktemp "${TMPDIR:-/tmp}/rtpref_x.XXXXXX") || return 1
  # F1-2026-08-18: XLANG_PREGEN_E_C=<path> reuses a pre-generated -E dump instead
  # of running the (OOM-prone) -E step here. Use case: mega runtime_pipeline_abi.x
  # -E peaks 22-40GB RSS (fat AST nodes x GrowVec doubling) and dev-box jetsam
  # kills it ~24GB; a big-RAM host (Ubuntu gold, 61GB) runs the bare -E and the
  # artifact is transferred back. Downstream post-processing (weak rename,
  # prologue, cc flags) stays in THIS function — single authority, G.7.
  # PLATFORM: SHARED harness
  if [ -n "${XLANG_PREGEN_E_C:-}" ]; then
    if [ -s "$XLANG_PREGEN_E_C" ]; then
      cat "$XLANG_PREGEN_E_C" > "$_xtmp"
    else
      echo "rt_prefer_try_x_to_o: XLANG_PREGEN_E_C set but empty/missing: $XLANG_PREGEN_E_C" >&2
      rm -f "$_xtmp"
      return 1
    fi
  else
  # 优先默认 -E（Linux 上 -backend c -E 可能 SIGSEGV）；再回退 -backend c -E。
  # Ubuntu 主机偶发 -E SIGSEGV：最多 5 次重试（对齐 prove harness b12bf000）。
  # PLATFORM: SHARED harness
  # shellcheck disable=SC2086
  _e_ok=0
  for _e_try in 1 2 3 4 5; do
    if "$_xxlang" -E "$_xsrc" >"$_xtmp" 2>/dev/null && [ -s "$_xtmp" ]; then
      _e_ok=1
      break
    fi
    : >"$_xtmp"
    if "$_xxlang" -backend c -E "$_xsrc" >"$_xtmp" 2>/dev/null && [ -s "$_xtmp" ]; then
      _e_ok=1
      break
    fi
    : >"$_xtmp"
  done
  if [ "$_e_ok" != "1" ]; then
    rm -f "$_xtmp"
    return 1
  fi
  fi
  if [ -n "${G05_X_O_WEAK_FUNCS:-}" ]; then
    # Named weak only (G.7 有则补全 on rt_prefer harness).
    # wave771 seed_link_compat: 6 stubs must stay weak so lsp_diag_x /
    # lsp_diag_pipeline_ctx strong defs win; do NOT weak every export.
    # Format: G05_X_O_WEAK_FUNCS="name1,name2,..." (bare C identifiers).
    # PLATFORM: SHARED — matches historic g05 sed on ^int32_t name(
    _old_ifs_w="$IFS"
    IFS=','
    for _wfn in $G05_X_O_WEAK_FUNCS; do
      _wfn="$(printf '%s' "$_wfn" | tr -d '[:space:]')"
      [ -z "$_wfn" ] && continue
      perl -i -pe "s/^(int32_t)\\s+${_wfn}\\s*\\(/XLANG_WEAK \$1 ${_wfn}(/" "$_xtmp" || true
    done
    IFS="$_old_ifs_w"
  elif [ "${G05_X_O_WEAK:-0}" = "1" ]; then
    # 仅改非 static 的简单返回类型函数定义行（-E 产物形态）
    # G-02f-335/336：含 uint8_t * / char * / int64_t 返回（diag_color_prefix / get_source_len 等）
    perl -i -pe 's/^((?:void|int64_t|int32_t|int|size_t|uint32_t|uint64_t|uint8_t \*|uint8_t|const char \*|char \*))\s+(\w+)\s*\(/XLANG_WEAK $1 $2(/' "$_xtmp" || true
  fi
  # F1-2026-08-18 chunked -E: -E renders .x file-level `let g_*` as C `static`
  # globals. In a monolithic file all functions share one storage; split chunks
  # would each get a PRIVATE copy (semantic divergence). G05_X_O_GLOBALS_WEAK=1
  # drops `static` and marks them XLANG_WEAK so ld -r first-wins restores the
  # single shared storage across merged chunks. Default 0 = zero regression.
  # PLATFORM: SHARED harness (chunked runtime_pipeline_abi thin builder).
  if [ "${G05_X_O_GLOBALS_WEAK:-0}" = "1" ]; then
    perl -i -pe 's/^static ((?:(?:const|volatile)\s+)?\w[\w\s]*?\*?\s*g_\w+)/XLANG_WEAK $1/' "$_xtmp" || true
  fi
  # G-02f-458: 前端 *_gen.c .o 的符号重命名
  # 格式：G05_X_O_SYM_RENAME="old1:new1,old2:new2,..."
  # 将 -E 输出中的 .x 函数名重命名为 gen.c 期望的符号名（模块前缀+函数名）
  if [ -n "${G05_X_O_SYM_RENAME:-}" ]; then
    _old_ifs="$IFS"
    IFS=','
    for _pair in $G05_X_O_SYM_RENAME; do
      _old_name="${_pair%%:*}"
      _new_name="${_pair#*:}"
      if [ -n "$_old_name" ] && [ -n "$_new_name" ] && [ "$_old_name" != "$_new_name" ]; then
        perl -i -pe "s/\\b${_old_name}\\b/${_new_name}/g" "$_xtmp" || true
      fi
    done
    IFS="$_old_ifs"
  fi
  # G-02f-332/334：-E 缺 ssize_t / open 原型；前置 POSIX 头，并删掉 -E 里冲突的 libc extern
  {
    echo '/* rt_prefer_try_x_to_o prologue (G-02f-332/334 + uio/poll) */'
    echo '#include <stddef.h>'
    echo '#include <stdint.h>'
    echo '#include "xlang_weak.h"'
    echo '#include <sys/types.h>'
    echo '#include <stdlib.h>'
    echo '#include <string.h>'
    echo '#include <stdio.h>'
    echo '#ifdef _WIN32'
    # PLATFORM: WINDOWS — -E dumps call POSIX read/write/rmdir; MinGW CRT is
    # _read/_write/_rmdir. win32_compat.h is the alias authority (access too).
    echo '#include "win32_compat.h"'
    echo '#else'
    echo '#include <unistd.h>'
    echo '#include <fcntl.h>'
    echo '#include <errno.h>'
    # PLATFORM: POSIX — -E preamble 内联 xlang_sys_readv/writev/poll 需原型；
    # 下方 sed 会删掉 -E 自带 #include <poll.h> 等，故在 prologue 补齐。
    echo '#include <sys/uio.h>'
    echo '#include <poll.h>'
    # Cap residual 9.1.10: fmt walk *u8 wrappers via xlang_dir_cap.h (no libc opendir).
    echo '#include <xlang_dir_cap.h>'
    echo 'static inline uint8_t *xlang_fmt_opendir(uint8_t *name) {'
    echo '  return name ? (uint8_t *)xlang_dir_open((const char *)(void *)name) : (uint8_t *)0;'
    echo '}'
    echo 'static inline int32_t xlang_fmt_closedir(uint8_t *dirp) {'
    echo '  return dirp ? (int32_t)xlang_dir_close((void *)dirp) : (int32_t)-1;'
    echo '}'
    echo 'static inline int32_t xlang_fmt_access(uint8_t *path, int32_t mode) {'
    echo '  return path ? (int32_t)access((const char *)path, (int)mode) : (int32_t)-1;'
    echo '}'
    echo 'static inline uint8_t *xlang_fmt_readdir_name(uint8_t *dirp) {'
    echo '  char *n;'
    echo '  if (!dirp) return (uint8_t *)0;'
    echo '  n = xlang_dir_readdir_name((void *)dirp);'
    echo '  return (uint8_t *)(void *)n;'
    echo '}'
    echo '#endif'
    # PLATFORM: SHARED — wave22 Cap residual: opaque *u8 → FILE* fputs cast.
    # .x cannot name FILE*; direct fputs(*u8,*u8) trips -Werror=incompatible-pointer-types.
    # Pure driver_preamble_fputs (runtime_driver_abi_thin.x) calls this harness helper.
    # Outside _WIN32 guard: stdio fputs is available on Windows host-cc too.
    echo 'static inline int32_t xlang_driver_fputs_opaque(uint8_t *s, uint8_t *stream) {'
    echo '  return (int32_t)fputs((const char *)(void *)s, (FILE *)(void *)stream);'
    echo '}'
    # PLATFORM: SHARED — wave26 Cap residual: stdout identity + fclose/fwrite for pure
    # driver_parsed_fclose / fclose_rc / write_out (runtime_driver_abi_thin.x).
    # .x cannot name FILE* or compare to stdout without these harness casts.
    echo 'static inline uint8_t *xlang_driver_stdout_ptr(void) {'
    echo '  return (uint8_t *)(void *)stdout;'
    echo '}'
    echo 'static inline int32_t xlang_driver_fclose_opaque(uint8_t *stream) {'
    echo '  if (!stream) return 0;'
    echo '  return fclose((FILE *)(void *)stream) == 0 ? 0 : 1;'
    echo '}'
    echo 'static inline int32_t xlang_driver_fwrite_opaque(uint8_t *data, int32_t len, uint8_t *stream) {'
    echo '  size_t n;'
    echo '  if (!data || len < 0 || !stream) return 1;'
    echo '  if (len == 0) return 0;'
    echo '  n = fwrite((const void *)(void *)data, 1, (size_t)len, (FILE *)(void *)stream);'
    echo '  return n == (size_t)len ? 0 : 1;'
    echo '}'
    # PLATFORM: SHARED — wave27 Cap residual: fopen(path,"w") as opaque *u8 for pure
    # driver_parsed_open_out_file (runtime_driver_abi_thin.x). .x cannot name FILE*.
    echo 'static inline uint8_t *xlang_driver_fopen_write_opaque(uint8_t *path) {'
    echo '  if (!path) return (uint8_t *)0;'
    echo '  return (uint8_t *)(void *)fopen((const char *)(void *)path, "w");'
    echo '}'
    # PLATFORM: SHARED — wave40 Cap residual: stderr identity + fflush(stdout) + fopen "wb"
    # for pure driver_stdio_stderr / driver_asm_fflush_stdout / driver_asm_fopen_wb
    # (runtime_driver_abi_thin.x). "wb" is intentionally not "w" (binary metric/asm out;
    # G.7: separate surface from fopen_write_opaque text "w").
    echo 'static inline uint8_t *xlang_driver_stderr_ptr(void) {'
    echo '  return (uint8_t *)(void *)stderr;'
    echo '}'
    echo 'static inline void xlang_driver_fflush_stdout(void) {'
    echo '  (void)fflush(stdout);'
    echo '}'
    echo 'static inline uint8_t *xlang_driver_fopen_wb_opaque(uint8_t *path) {'
    echo '  if (!path) return (uint8_t *)0;'
    echo '  return (uint8_t *)(void *)fopen((const char *)(void *)path, "wb");'
    echo '}'
    # PLATFORM: SHARED — wave41 Cap residual: fdopen(fd,"wb") as opaque *u8 for pure
    # driver_asm_mkstemp_fdopen (runtime_driver_abi_thin.x). .x cannot name FILE*.
    echo 'static inline uint8_t *xlang_driver_fdopen_wb_opaque(int32_t fd) {'
    echo '  FILE *fp;'
    echo '  if (fd < 0) return (uint8_t *)0;'
    echo '  fp = fdopen((int)fd, "wb");'
    echo '  return (uint8_t *)(void *)fp;'
    echo '}'
    # PLATFORM: SHARED — wave79 Cap residual: libc realpath as opaque *u8 for pure
    # xlang_path_try_realpath_inplace (runtime_pipeline_abi.x). .x must not name char*
    # realpath (labi_path_io clash note); non-POSIX returns null → pure leaves path.
    # POSIX/APPLE: realpath from unistd/stdlib (prologue includes them above).
    echo '#if defined(_POSIX_VERSION) || defined(__APPLE__)'
    echo 'static inline uint8_t *xlang_driver_realpath_opaque(uint8_t *path, uint8_t *resolved) {'
    echo '  char *r;'
    echo '  if (!path || !resolved) return (uint8_t *)0;'
    echo '  r = realpath((const char *)(void *)path, (char *)(void *)resolved);'
    echo '  return (uint8_t *)(void *)r;'
    echo '}'
    echo '#else'
    echo 'static inline uint8_t *xlang_driver_realpath_opaque(uint8_t *path, uint8_t *resolved) {'
    echo '  (void)path; (void)resolved;'
    echo '  return (uint8_t *)0;'
    echo '}'
    echo '#endif'
    # PLATFORM: SHARED — wave84 Cap residual: function address as *u8 for pure
    # pipeline_run_x_thread_fn_ptr / xlang_asm_codegen_elf_o_thread_fn_ptr
    # (runtime_pipeline_abi.x). .x cannot form function-pointer constants (&fn);
    # pure thin surface owns the product names; cast residual stays in this harness
    # (same pattern as stdout_ptr / realpath_opaque). Cold twin under seed #ifndef FROM_X.
    # Match pure .x export: *u8 arg / *u8 return (not void* — gcc conflicts with pure body).
    echo 'extern uint8_t *pipeline_run_x_thread_fn(uint8_t *);'
    echo 'extern uint8_t *xlang_asm_codegen_elf_o_thread_fn(uint8_t *);'
    echo 'static inline uint8_t *xlang_driver_pipeline_run_x_thread_fn_ptr(void) {'
    echo '  return (uint8_t *)(void *)pipeline_run_x_thread_fn;'
    echo '}'
    echo 'static inline uint8_t *xlang_driver_asm_elf_o_thread_fn_ptr(void) {'
    echo '  return (uint8_t *)(void *)xlang_asm_codegen_elf_o_thread_fn;'
    echo '}'
    # Strip -E #include + libc redecls that clash with prologue headers.
    # PLATFORM: SHARED harness — G.7 product authority for libc skip is
    # codegen_is_libc_conflicting_extern_name (codegen.x + seed). After wave30,
    # mkstemp/rename are in that predicate; sed lines below stay as defense for
    # cold/old xlang -E, opendir opaque (intentionally NOT in product skip), and
    # xlang_fmt_*/xlang_driver_* harness helpers defined as static inline above.
    sed -e '/^#include /d' \
        -e '/^extern ssize_t read(/d' \
        -e '/^extern ssize_t write(/d' \
        -e '/^extern int32_t open(/d' \
        -e '/^extern int open(/d' \
        -e '/^extern int32_t fcntl(/d' \
        -e '/^extern int fcntl(/d' \
        -e '/^extern int32_t close(/d' \
        -e '/^extern int close(/d' \
        -e '/^extern uint8_t \* calloc(/d' \
        -e '/^extern uint8_t \* malloc(/d' \
        -e '/^extern void free(/d' \
        -e '/^extern uint8_t \* memcpy(/d' \
        -e '/^extern void \* memcpy(/d' \
        -e '/^extern int32_t memcmp(/d' \
        -e '/^extern int memcmp(/d' \
        -e '/^extern char \* getenv(/d' \
        -e '/^extern uint8_t \* getenv(/d' \
        -e '/^extern char \* getcwd(/d' \
        -e '/^extern uint8_t \* getcwd(/d' \
        -e '/^extern int32_t unlink(/d' \
        -e '/^extern int unlink(/d' \
        -e '/^extern size_t strlen(/d' \
        -e '/^extern int32_t strcmp(/d' \
        -e '/^extern int strcmp(/d' \
        -e '/^extern int32_t strncmp(/d' \
        -e '/^extern int strncmp(/d' \
        -e '/^extern uint8_t \* strstr(/d' \
        -e '/^extern char \* strstr(/d' \
        -e '/^extern uint8_t \* memset(/d' \
        -e '/^extern void \* memset(/d' \
        -e '/^extern int32_t setenv(/d' \
        -e '/^extern int setenv(/d' \
        -e '/^extern uint8_t \* strerror(/d' \
        -e '/^extern char \* strerror(/d' \
        -e '/^extern int32_t system(/d' \
        -e '/^extern int system(/d' \
        -e '/^extern int32_t fputs(/d' \
        -e '/^extern int fputs(/d' \
        -e '/^extern uint8_t \* opendir(/d' \
        -e '/^extern void \* opendir(/d' \
        -e '/^extern DIR \* opendir(/d' \
        -e '/^extern int32_t closedir(/d' \
        -e '/^extern int closedir(/d' \
        -e '/^extern int32_t access(/d' \
        -e '/^extern int access(/d' \
        -e '/^extern uint8_t \* xlang_fmt_opendir(/d' \
        -e '/^extern int32_t xlang_fmt_closedir(/d' \
        -e '/^extern int32_t xlang_fmt_access(/d' \
        -e '/^extern uint8_t \* xlang_fmt_readdir_name(/d' \
        -e '/^extern int32_t xlang_driver_fputs_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_stdout_ptr(/d' \
        -e '/^extern int32_t xlang_driver_fclose_opaque(/d' \
        -e '/^extern int32_t xlang_driver_fwrite_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_fopen_write_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_stderr_ptr(/d' \
        -e '/^extern void xlang_driver_fflush_stdout(/d' \
        -e '/^extern uint8_t \* xlang_driver_fopen_wb_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_fdopen_wb_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_realpath_opaque(/d' \
        -e '/^extern uint8_t \* xlang_driver_pipeline_run_x_thread_fn_ptr(/d' \
        -e '/^extern uint8_t \* xlang_driver_asm_elf_o_thread_fn_ptr(/d' \
        -e '/^extern int32_t mkstemp(/d' \
        -e '/^extern int mkstemp(/d' \
        -e '/^extern int32_t rename(/d' \
        -e '/^extern int rename(/d' \
        "$_xtmp"
  } >"${_xtmp}.full" && mv "${_xtmp}.full" "$_xtmp"
  # shellcheck disable=SC2086
  # -x c：mktemp 无扩展名时 clang 否则不当作 C 源
  if ! $CC $BASE_CFLAGS "$@" -x c -c -o "$_xout" "$_xtmp"; then
    rm -f "$_xtmp"
    return 1
  fi
  rm -f "$_xtmp"
  return 0
}

ensure_rt_prefer_one() {
  # Prefer multi-slice (or cold multi-slice); monofile last-resort only with escape.
  # PLATFORM: SHARED freestanding — wave318/319 omit empty mega; wave320 refuse monofile.
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local allow_monofile="${XLANG_RT_ALLOW_MONOFILE_LAST_RESORT:-0}"
  local RUNTIME_DRIVER_NO_C_CFLAGS
  RUNTIME_DRIVER_NO_C_CFLAGS="$(rt_prefer_no_c_cflags)"
  export RUNTIME_DRIVER_NO_C_CFLAGS
  # Historic g05 block (paths + hybrid/cold multi-slice; monofile opt-in only).
    # G-02f-14 / G-02f-261～265 / G-02f-291～297：runtime_driver_no_c.o
    # PREFER_X_O=1：R2..parsed 切片 hybrid（.x+seed）→ omit empty mega rest (wave318)
    # PREFER_X_O=0：同层 cold seed 切片 only → omit empty mega rest (wave319)
    # wave320：默认 **拒** monofile last-resort（7.1.2）；escape=XLANG_RT_ALLOW_MONOFILE_LAST_RESORT=1
    # 注：RFC R4 DCE 在 !XLANG_USE_X_DRIVER 下，不进产品 .o；R7 spawn 仍 rest
    _rt=seeds/runtime.from_x.c
    _rt_content_x=src/runtime/rt_content.x
    _rt_content_seed=seeds/rt_content.from_x.c
    _rt_util_seed=seeds/rt_util.from_x.c
    _rt_util_x=src/runtime/rt_util.x
    _rt_argv_seed=seeds/rt_argv.from_x.c
    _rt_argv_x=src/runtime/rt_argv.x
    _rt_ef_seed=seeds/rt_emit_flags.from_x.c
    _rt_ef_x=src/runtime/rt_emit_flags.x
    _rt_pre_seed=seeds/rt_preamble.from_x.c
    _rt_pre_x=src/runtime/rt_preamble.x
    _rt_compile_seed=seeds/rt_compile.from_x.c
    _rt_compile_x=src/runtime/rt_compile.x
    _rt_run_seed=seeds/rt_run_exec.from_x.c
    _rt_run_exec_x=src/runtime/rt_run_exec.x
    _rt_asm_seed=seeds/rt_asm_stub.from_x.c
    _rt_asm_stub_x=src/runtime/rt_asm_stub.x
    _rt_entry_seed=seeds/rt_entry.from_x.c
    _rt_entry_x=src/runtime/rt_entry.x
    _rt_diag_seed=seeds/rt_diag_errno.from_x.c
    _rt_diag_x=src/runtime/rt_diag_errno.x
    _rt_emit_st_seed=seeds/rt_emit_state.from_x.c
    _rt_emit_st_x=src/runtime/rt_emit_state.x
    _rt_elf_diag_seed=seeds/rt_pipeline_elf_diag.from_x.c
    _rt_elf_diag_x=src/runtime/rt_pipeline_elf_diag.x
    _rt_lib_root_seed=seeds/rt_lib_root.from_x.c
    _rt_lib_root_x=src/runtime/rt_lib_root.x
    _rt_parse_diag_seed=seeds/rt_parse_diag.from_x.c
    _rt_parse_diag_x=src/runtime/rt_parse_diag.x
    _rt_fs_open_seed=seeds/rt_fs_open.from_x.c
    _rt_fs_open_x=src/runtime/rt_fs_open.x
    _rt_arena_buf_seed=seeds/rt_arena_buf.from_x.c
    _rt_arena_buf_x=src/runtime/rt_arena_buf.x
    _rt_fmt_one_seed=seeds/rt_fmt_one.from_x.c
    _rt_fmt_one_x=src/runtime/rt_fmt_one.x
    _rt_dispatch_thin_seed=seeds/rt_dispatch_thin.from_x.c
    _rt_dispatch_thin_x=src/runtime/rt_dispatch_thin.x
    _rt_dispatch_impl_seed=seeds/rt_dispatch_impl.from_x.c
    _rt_dispatch_impl_x=src/runtime/rt_dispatch_impl.x
    _rt_run_x_emit_seed=seeds/rt_run_x_emit.from_x.c
    _rt_run_x_emit_x=src/runtime/rt_run_x_emit.x
    _rt_run_asm_backend_seed=seeds/rt_run_asm_backend.from_x.c
    _rt_run_asm_backend_x=src/runtime/rt_run_asm_backend.x
    _rt_run_compiler_parsed_seed=seeds/rt_run_compiler_parsed.from_x.c
    _rt_run_compiler_parsed_x=src/runtime/rt_run_compiler_parsed.x
    _rt_stack_seed=seeds/rt_stack.from_x.c
    _rt_stack_x=src/runtime/rt_stack.x
    _rt_o="$1"
    # wave320: product multi-slice gated on content layer seed (not monofile presence).
    # Monofile may be absent after future 7.1.1 physical retire; escape still uses _rt.
    # PLATFORM: SHARED freestanding runtime product no_c.
    if [ -f "$_rt_content_seed" ] || [ -f "$_rt" ]; then
      if [ ! -f "$_rt_o" ] \
        || { [ -f "$_rt" ] && [ "$_rt" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_content_seed" ] && [ "$_rt_content_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_util_seed" ] && [ "$_rt_util_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_util_x" ] && [ "$_rt_util_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_argv_seed" ] && [ "$_rt_argv_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_argv_x" ] && [ "$_rt_argv_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_ef_seed" ] && [ "$_rt_ef_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_ef_x" ] && [ "$_rt_ef_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_pre_seed" ] && [ "$_rt_pre_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_pre_x" ] && [ "$_rt_pre_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_compile_seed" ] && [ "$_rt_compile_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_compile_x" ] && [ "$_rt_compile_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_seed" ] && [ "$_rt_run_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_exec_x" ] && [ "$_rt_run_exec_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_asm_seed" ] && [ "$_rt_asm_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_asm_stub_x" ] && [ "$_rt_asm_stub_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_entry_seed" ] && [ "$_rt_entry_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_entry_x" ] && [ "$_rt_entry_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_diag_seed" ] && [ "$_rt_diag_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_diag_x" ] && [ "$_rt_diag_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_emit_st_seed" ] && [ "$_rt_emit_st_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_emit_st_x" ] && [ "$_rt_emit_st_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_elf_diag_seed" ] && [ "$_rt_elf_diag_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_elf_diag_x" ] && [ "$_rt_elf_diag_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_lib_root_seed" ] && [ "$_rt_lib_root_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_lib_root_x" ] && [ "$_rt_lib_root_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_parse_diag_seed" ] && [ "$_rt_parse_diag_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_parse_diag_x" ] && [ "$_rt_parse_diag_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_fs_open_seed" ] && [ "$_rt_fs_open_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_fs_open_x" ] && [ "$_rt_fs_open_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_arena_buf_seed" ] && [ "$_rt_arena_buf_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_arena_buf_x" ] && [ "$_rt_arena_buf_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_fmt_one_seed" ] && [ "$_rt_fmt_one_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_fmt_one_x" ] && [ "$_rt_fmt_one_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_dispatch_thin_seed" ] && [ "$_rt_dispatch_thin_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_dispatch_thin_x" ] && [ "$_rt_dispatch_thin_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_dispatch_impl_seed" ] && [ "$_rt_dispatch_impl_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_dispatch_impl_x" ] && [ "$_rt_dispatch_impl_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_x_emit_seed" ] && [ "$_rt_run_x_emit_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_x_emit_x" ] && [ "$_rt_run_x_emit_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_asm_backend_seed" ] && [ "$_rt_run_asm_backend_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_asm_backend_x" ] && [ "$_rt_run_asm_backend_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_compiler_parsed_seed" ] && [ "$_rt_run_compiler_parsed_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_run_compiler_parsed_x" ] && [ "$_rt_run_compiler_parsed_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_stack_seed" ] && [ "$_rt_stack_seed" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_stack_x" ] && [ "$_rt_stack_x" -nt "$_rt_o" ]; } \
        || { [ -f "$_rt_content_x" ] && [ "$_rt_content_x" -nt "$_rt_o" ]; }; then
        _rt_done=0
        # wave319: multi-slice whenever content cold seed exists (not only PREFER=1).
        # Per-slice still tries .x only when PREFER=1; PREFER=0 uses cold seed bodies.
        # PLATFORM: SHARED freestanding runtime mega cold multi-slice omit empty rest.
        if [ -f "$_rt_content_seed" ]; then
          _rt_c_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_content.XXXXXX") || true
          _rt_u_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_util.XXXXXX") || true
          _rt_a_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_argv.XXXXXX") || true
          _rt_e_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_eflags.XXXXXX") || true
          _rt_p_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_pre.XXXXXX") || true
          _rt_cmp_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_compile.XXXXXX") || true
          _rt_run_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run.XXXXXX") || true
          _rt_asm_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_asm.XXXXXX") || true
          _rt_ent_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_entry.XXXXXX") || true
          _rt_diag_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_diag.XXXXXX") || true
          _rt_est_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_emit_st.XXXXXX") || true
          _rt_elfd_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_elf_diag.XXXXXX") || true
          _rt_lr_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_lib_root.XXXXXX") || true
          _rt_pd_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_parse_diag.XXXXXX") || true
          _rt_fs_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fs_open.XXXXXX") || true
          _rt_ab_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_arena_buf.XXXXXX") || true
          _rt_fo_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fmt_one.XXXXXX") || true
          _rt_dt_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_thin.XXXXXX") || true
          _rt_di_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_impl.XXXXXX") || true
          _rt_xe_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_x_emit.XXXXXX") || true
          _rt_abk_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_asm_backend.XXXXXX") || true
          _rt_rcp_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_compiler_parsed.XXXXXX") || true
          _rt_st_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_stack.XXXXXX") || true
          _rt_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_rest.XXXXXX") || true
          _rt_content_ok=0
          _rt_util_ok=0
          _rt_argv_ok=0
          _rt_ef_ok=0
          _rt_pre_ok=0
          _rt_compile_ok=0
          _rt_run_ok=0
          _rt_asm_ok=0
          _rt_entry_ok=0
          _rt_diag_ok=0
          _rt_est_ok=0
          _rt_elfd_ok=0
          _rt_lr_ok=0
          _rt_pd_ok=0
          _rt_fs_ok=0
          _rt_ab_ok=0
          _rt_fo_ok=0
          _rt_dt_ok=0
          _rt_di_ok=0
          _rt_xe_ok=0
          _rt_abk_ok=0
          _rt_rcp_ok=0
          _rt_st_ok=0
          if [ -n "$_rt_c_o" ]; then
            # G-02f-436：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_content_x" ]; then
              _rt_content_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_content_thin.XXXXXX") || true
              _rt_content_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_content_rest.XXXXXX") || true
              if [ -n "$_rt_content_thin_o" ] && [ -n "$_rt_content_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_content_x" "$_rt_content_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_CONTENT_FROM_X \
                     -c -o "$_rt_content_rest_o" "$_rt_content_seed" \
                && pure_ld_partial_merge "$_rt_c_o" "$_rt_content_thin_o" "$_rt_content_rest_o" 2>/dev/null; then
                _rt_content_ok=1
                echo "rt-prefer: R2 content ← full .x + rest H=0 (path wrappers in .x)"
              fi
              rm -f "$_rt_content_thin_o" "$_rt_content_rest_o"
            fi
            if [ "$_rt_content_ok" = "0" ] && [ -f "$_rt_content_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_c_o" "$_rt_content_seed"; then
                _rt_content_ok=1
                echo "rt-prefer: R2 content ← $_rt_content_seed (G-02f-261/306 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_u_o" ]; then
            # G-02f-435：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_util_x" ]; then
              _rt_util_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_util_thin.XXXXXX") || true
              _rt_util_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_util_rest.XXXXXX") || true
              if [ -n "$_rt_util_thin_o" ] && [ -n "$_rt_util_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_util_x" "$_rt_util_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_UTIL_FROM_X \
                     -c -o "$_rt_util_rest_o" "$_rt_util_seed" \
                && pure_ld_partial_merge "$_rt_u_o" "$_rt_util_thin_o" "$_rt_util_rest_o" 2>/dev/null; then
                _rt_util_ok=1
                echo "rt-prefer: R0 util ← thin .x + rest (G-02f-435 L2 prefer .x)"
              fi
              rm -f "$_rt_util_thin_o" "$_rt_util_rest_o"
            fi
            if [ "$_rt_util_ok" = "0" ] && [ -f "$_rt_util_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_u_o" "$_rt_util_seed"; then
                _rt_util_ok=1
                echo "rt-prefer: R0 util ← $_rt_util_seed (G-02f-262 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_a_o" ]; then
            # R2 full：PREFER_X_O=1 时 full .x + rest seed (-D FROM_X 业务 H=0) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_argv_x" ]; then
              _rt_argv_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_argv_thin.XXXXXX") || true
              _rt_argv_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_argv_rest.XXXXXX") || true
              if [ -n "$_rt_argv_thin_o" ] && [ -n "$_rt_argv_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_argv_x" "$_rt_argv_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_ARGV_FROM_X \
                     -c -o "$_rt_argv_rest_o" "$_rt_argv_seed" \
                && pure_ld_partial_merge "$_rt_a_o" "$_rt_argv_thin_o" "$_rt_argv_rest_o" 2>/dev/null; then
                _rt_argv_ok=1
                echo "rt-prefer: R1 argv ← full .x + rest (R2 full H=0; G-02f-431 PREFER_X_O)"
              fi
              rm -f "$_rt_argv_thin_o" "$_rt_argv_rest_o"
            fi
            if [ "$_rt_argv_ok" = "0" ] && [ -f "$_rt_argv_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_a_o" "$_rt_argv_seed"; then
                _rt_argv_ok=1
                echo "rt-prefer: R1 argv ← $_rt_argv_seed (G-02f-263 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_e_o" ] && [ -f "$_rt_ef_seed" ]; then
            # G-02f-451：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_ef_x" ]; then
              _rt_ef_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_emit_flags_thin.XXXXXX") || true
              _rt_ef_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_emit_flags_rest.XXXXXX") || true
              if [ -n "$_rt_ef_thin_o" ] && [ -n "$_rt_ef_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_ef_x" "$_rt_ef_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_EMIT_FLAGS_FROM_X \
                     -c -o "$_rt_ef_rest_o" "$_rt_ef_seed" \
                && pure_ld_partial_merge "$_rt_e_o" "$_rt_ef_thin_o" "$_rt_ef_rest_o" 2>/dev/null; then
                _rt_ef_ok=1
                echo "rt-prefer: R2 emit_flags ← full .x + rest (G-02f R2 prefer .x; FROM_X rest H=0)"
              fi
              rm -f "$_rt_ef_thin_o" "$_rt_ef_rest_o"
            fi
            if [ "$_rt_ef_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_e_o" "$_rt_ef_seed"; then
                _rt_ef_ok=1
                echo "rt-prefer: R5-lite emit_flags ← $_rt_ef_seed (G-02f-264 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_p_o" ] && [ -f "$_rt_pre_seed" ]; then
            # R2 full：PREFER_X_O=1 时 full .x + rest seed（表+marker）→ cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_pre_x" ]; then
              _rt_p_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_pre_thin.XXXXXX") || true
              _rt_p_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_pre_rest.XXXXXX") || true
              if [ -n "$_rt_p_thin_o" ] && [ -n "$_rt_p_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_pre_x" "$_rt_p_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_PREAMBLE_FROM_X \
                     -c -o "$_rt_p_rest_o" "$_rt_pre_seed" \
                && pure_ld_partial_merge "$_rt_p_o" "$_rt_p_thin_o" "$_rt_p_rest_o" 2>/dev/null; then
                _rt_pre_ok=1
                echo "rt-prefer: R3 preamble ← full .x + rest tables/marker (R2 full H=0)"
              fi
              rm -f "$_rt_p_thin_o" "$_rt_p_rest_o"
            fi
            if [ "$_rt_pre_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_p_o" "$_rt_pre_seed"; then
                _rt_pre_ok=1
                echo "rt-prefer: R3 preamble ← $_rt_pre_seed (G-02f-265 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_cmp_o" ] && [ -f "$_rt_compile_seed" ]; then
            # G-02f-454：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            # 门闩：.x -E 可能「假成功」缺关键 T 符号；FROM_X rest 仅前向声明 → 最终 link U。
            # 合并后必须有 seed 权威入口，否则回退完整 seed 冷编。
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_compile_x" ]; then
              _rt_cmp_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_compile_thin.XXXXXX") || true
              _rt_cmp_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_compile_rest.XXXXXX") || true
              if [ -n "$_rt_cmp_thin_o" ] && [ -n "$_rt_cmp_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_compile_x" "$_rt_cmp_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_COMPILE_FROM_X \
                     -c -o "$_rt_cmp_rest_o" "$_rt_compile_seed" \
                && pure_ld_partial_merge "$_rt_cmp_o" "$_rt_cmp_thin_o" "$_rt_cmp_rest_o" 2>/dev/null \
                && nm "$_rt_cmp_o" 2>/dev/null | grep -q " T driver_compile_state_alloc_c$" \
                && nm "$_rt_cmp_o" 2>/dev/null | grep -q " T driver_deps_are_std_core_closure_only$" \
                && nm "$_rt_cmp_o" 2>/dev/null | grep -q " T driver_compile_parse_argv_impl_c$"; then
                _rt_compile_ok=1
                echo "rt-prefer: R6 compile ← full .x + rest marker (R2 full H=0)"
              else
                echo "rt-prefer: R6 compile .x hybrid incomplete (missing T exports) → seed fallback" >&2
              fi
              rm -f "$_rt_cmp_thin_o" "$_rt_cmp_rest_o"
            fi
            if [ "$_rt_compile_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_cmp_o" "$_rt_compile_seed"; then
                _rt_compile_ok=1
                echo "rt-prefer: R6 compile pure ← $_rt_compile_seed (G-02f-291~296 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_run_o" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            # 门闩：.x -E 假成功缺 driver_run_test 时不得标 FROM_X（否则 driver_test_x 链 U）。
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_run_exec_x" ]; then
              _rt_run_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_thin.XXXXXX") || true
              _rt_run_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_rest.XXXXXX") || true
              if [ -n "$_rt_run_thin_o" ] && [ -n "$_rt_run_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_run_exec_x" "$_rt_run_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_RUN_EXEC_FROM_X \
                     -c -o "$_rt_run_rest_o" "$_rt_run_seed" \
                && pure_ld_partial_merge "$_rt_run_o" "$_rt_run_thin_o" "$_rt_run_rest_o" 2>/dev/null \
                && nm "$_rt_run_o" 2>/dev/null | grep -q " T driver_run_test$"; then
                _rt_run_ok=1
                echo "rt-prefer: R7 run/exec ← full .x + rest marker (R2 full H=0)"
              else
                echo "rt-prefer: R7 run/exec .x hybrid incomplete (missing driver_run_test) → seed fallback" >&2
              fi
              rm -f "$_rt_run_thin_o" "$_rt_run_rest_o"
            fi
            if [ "$_rt_run_ok" = "0" ] && [ -f "$_rt_run_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_run_o" "$_rt_run_seed"; then
                _rt_run_ok=1
                echo "rt-prefer: R7 run/exec ← $_rt_run_seed (G-02f-297~299/311 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_asm_o" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_asm_stub_x" ]; then
              _rt_asm_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_asm_thin.XXXXXX") || true
              _rt_asm_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_asm_rest.XXXXXX") || true
              if [ -n "$_rt_asm_thin_o" ] && [ -n "$_rt_asm_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_asm_stub_x" "$_rt_asm_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_ASM_STUB_FROM_X \
                     -c -o "$_rt_asm_rest_o" "$_rt_asm_seed" \
                && pure_ld_partial_merge "$_rt_asm_o" "$_rt_asm_thin_o" "$_rt_asm_rest_o" 2>/dev/null; then
                _rt_asm_ok=1
                echo "rt-prefer: R9 asm stub ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_asm_thin_o" "$_rt_asm_rest_o"
            fi
            if [ "$_rt_asm_ok" = "0" ] && [ -f "$_rt_asm_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_asm_o" "$_rt_asm_seed"; then
                _rt_asm_ok=1
                echo "rt-prefer: R9 asm stub ← $_rt_asm_seed (G-02f-300 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_ent_o" ] && [ -f "$_rt_entry_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_entry_x" ]; then
              _rt_ent_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_entry_thin.XXXXXX") || true
              _rt_ent_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_entry_rest.XXXXXX") || true
              if [ -n "$_rt_ent_thin_o" ] && [ -n "$_rt_ent_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_entry_x" "$_rt_ent_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_ENTRY_FROM_X \
                     -c -o "$_rt_ent_rest_o" "$_rt_entry_seed" \
                && pure_ld_partial_merge "$_rt_ent_o" "$_rt_ent_thin_o" "$_rt_ent_rest_o" 2>/dev/null; then
                _rt_entry_ok=1
                echo "rt-prefer: R10 entry ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_ent_thin_o" "$_rt_ent_rest_o"
            fi
            if [ "$_rt_entry_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_ent_o" "$_rt_entry_seed"; then
                _rt_entry_ok=1
                echo "rt-prefer: R10 entry gates ← $_rt_entry_seed (G-02f-301/310 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_diag_o" ] && [ -f "$_rt_diag_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_diag_x" ]; then
              _rt_diag_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_diag_thin.XXXXXX") || true
              _rt_diag_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_diag_rest.XXXXXX") || true
              if [ -n "$_rt_diag_thin_o" ] && [ -n "$_rt_diag_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_diag_x" "$_rt_diag_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_DIAG_ERRNO_FROM_X \
                     -c -o "$_rt_diag_rest_o" "$_rt_diag_seed" \
                && pure_ld_partial_merge "$_rt_diag_o" "$_rt_diag_thin_o" "$_rt_diag_rest_o" 2>/dev/null; then
                _rt_diag_ok=1
                echo "rt-prefer: rest diag_errno ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_diag_thin_o" "$_rt_diag_rest_o"
            fi
            if [ "$_rt_diag_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_diag_o" "$_rt_diag_seed"; then
                _rt_diag_ok=1
                echo "rt-prefer: rest diag errno ← $_rt_diag_seed (G-02f-302 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_est_o" ] && [ -f "$_rt_emit_st_seed" ]; then
            # G-02f-455：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_emit_st_x" ]; then
              _rt_est_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_emit_st_thin.XXXXXX") || true
              _rt_est_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_emit_st_rest.XXXXXX") || true
              if [ -n "$_rt_est_thin_o" ] && [ -n "$_rt_est_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_emit_st_x" "$_rt_est_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_EMIT_STATE_FROM_X \
                     -c -o "$_rt_est_rest_o" "$_rt_emit_st_seed" \
                && pure_ld_partial_merge "$_rt_est_o" "$_rt_est_thin_o" "$_rt_est_rest_o" 2>/dev/null; then
                _rt_est_ok=1
                echo "rt-prefer: rest emit state ← full .x + rest BSS+marker (R2 full H=0)"
              fi
              rm -f "$_rt_est_thin_o" "$_rt_est_rest_o"
            fi
            if [ "$_rt_est_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_est_o" "$_rt_emit_st_seed"; then
                _rt_est_ok=1
                echo "rt-prefer: rest emit state+argv ← $_rt_emit_st_seed (G-02f-303/304 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_elfd_o" ] && [ -f "$_rt_elf_diag_seed" ]; then
            # G-02f-445：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_elf_diag_x" ]; then
              _rt_elfd_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_elf_diag_thin.XXXXXX") || true
              _rt_elfd_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_elf_diag_rest.XXXXXX") || true
              if [ -n "$_rt_elfd_thin_o" ] && [ -n "$_rt_elfd_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_elf_diag_x" "$_rt_elfd_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_PIPELINE_ELF_DIAG_FROM_X \
                     -c -o "$_rt_elfd_rest_o" "$_rt_elf_diag_seed" \
                && pure_ld_partial_merge "$_rt_elfd_o" "$_rt_elfd_thin_o" "$_rt_elfd_rest_o" 2>/dev/null; then
                _rt_elfd_ok=1
                echo "rt-prefer: rest pipeline elf diag ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_elfd_thin_o" "$_rt_elfd_rest_o"
            fi
            if [ "$_rt_elfd_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_elfd_o" "$_rt_elf_diag_seed"; then
                _rt_elfd_ok=1
                echo "rt-prefer: rest pipeline elf diag ← $_rt_elf_diag_seed (G-02f-304 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_lr_o" ]; then
            # G-02f-432：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_lib_root_x" ]; then
              _rt_lr_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_lr_thin.XXXXXX") || true
              _rt_lr_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_lr_rest.XXXXXX") || true
              if [ -n "$_rt_lr_thin_o" ] && [ -n "$_rt_lr_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_lib_root_x" "$_rt_lr_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_LIB_ROOT_FROM_X \
                     -c -o "$_rt_lr_rest_o" "$_rt_lib_root_seed" \
                && pure_ld_partial_merge "$_rt_lr_o" "$_rt_lr_thin_o" "$_rt_lr_rest_o" 2>/dev/null; then
                _rt_lr_ok=1
                echo "rt-prefer: rest lib_root ← thin .x + rest (G-02f-432 L2 prefer .x)"
              fi
              rm -f "$_rt_lr_thin_o" "$_rt_lr_rest_o"
            fi
            if [ "$_rt_lr_ok" = "0" ] && [ -f "$_rt_lib_root_seed" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_lr_o" "$_rt_lib_root_seed"; then
                _rt_lr_ok=1
                echo "rt-prefer: rest lib_root ← $_rt_lib_root_seed (G-02f-305 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_pd_o" ] && [ -f "$_rt_parse_diag_seed" ]; then
            # G-02f-448：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_parse_diag_x" ]; then
              _rt_pd_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_parse_diag_thin.XXXXXX") || true
              _rt_pd_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_parse_diag_rest.XXXXXX") || true
              if [ -n "$_rt_pd_thin_o" ] && [ -n "$_rt_pd_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_parse_diag_x" "$_rt_pd_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc \
                     -DXLANG_RT_PARSE_DIAG_FROM_X -DXLANG_RT_PARSE_DIAG_PRECISE_BRIDGE \
                     -c -o "$_rt_pd_rest_o" "$_rt_parse_diag_seed" \
                && pure_ld_partial_merge "$_rt_pd_o" "$_rt_pd_thin_o" "$_rt_pd_rest_o" 2>/dev/null; then
                _rt_pd_ok=1
                echo "rt-prefer: rest parse_diag ← thin .x + rest (R2 full H=0; G-02f-448 PREFER_X_O)"
              fi
              rm -f "$_rt_pd_thin_o" "$_rt_pd_rest_o"
            fi
            if [ "$_rt_pd_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_pd_o" "$_rt_parse_diag_seed"; then
                _rt_pd_ok=1
                echo "rt-prefer: rest parse diag ← $_rt_parse_diag_seed (G-02f-307 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_fs_o" ] && [ -f "$_rt_fs_open_seed" ]; then
            # G-02f-452：PREFER_X_O=1 时 thin .x + rest seed (-D) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_fs_open_x" ]; then
              _rt_fs_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fs_open_thin.XXXXXX") || true
              _rt_fs_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fs_open_rest.XXXXXX") || true
              if [ -n "$_rt_fs_thin_o" ] && [ -n "$_rt_fs_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_fs_open_x" "$_rt_fs_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_FS_OPEN_FROM_X \
                     -c -o "$_rt_fs_rest_o" "$_rt_fs_open_seed" \
                && pure_ld_partial_merge "$_rt_fs_o" "$_rt_fs_thin_o" "$_rt_fs_rest_o" 2>/dev/null; then
                _rt_fs_ok=1
                echo "rt-prefer: rest fs open ← thin .x + rest (R2 full H=0; G-02f-452 PREFER_X_O)"
              fi
              rm -f "$_rt_fs_thin_o" "$_rt_fs_rest_o"
            fi
            if [ "$_rt_fs_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_fs_o" "$_rt_fs_open_seed"; then
                _rt_fs_ok=1
                echo "rt-prefer: rest fs open ← $_rt_fs_open_seed (G-02f-308 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_ab_o" ] && [ -f "$_rt_arena_buf_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，BSS+marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_arena_buf_x" ]; then
              _rt_ab_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_arena_thin.XXXXXX") || true
              _rt_ab_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_arena_rest.XXXXXX") || true
              if [ -n "$_rt_ab_thin_o" ] && [ -n "$_rt_ab_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_arena_buf_x" "$_rt_ab_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_ARENA_BUF_FROM_X \
                     -c -o "$_rt_ab_rest_o" "$_rt_arena_buf_seed" \
                && pure_ld_partial_merge "$_rt_ab_o" "$_rt_ab_thin_o" "$_rt_ab_rest_o" 2>/dev/null; then
                _rt_ab_ok=1
                echo "rt-prefer: rest arena_buf ← full .x + rest BSS+marker (R2 full H=0)"
              fi
              rm -f "$_rt_ab_thin_o" "$_rt_ab_rest_o"
            fi
            if [ "$_rt_ab_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_ab_o" "$_rt_arena_buf_seed"; then
                _rt_ab_ok=1
                echo "rt-prefer: rest arena_buf ← $_rt_arena_buf_seed (G-02f-309 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_fo_o" ] && [ -f "$_rt_fmt_one_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_fmt_one_x" ]; then
              _rt_fo_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fmt_one_thin.XXXXXX") || true
              _rt_fo_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_fmt_one_rest.XXXXXX") || true
              if [ -n "$_rt_fo_thin_o" ] && [ -n "$_rt_fo_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_fmt_one_x" "$_rt_fo_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_FMT_ONE_FROM_X \
                     -c -o "$_rt_fo_rest_o" "$_rt_fmt_one_seed" \
                && pure_ld_partial_merge "$_rt_fo_o" "$_rt_fo_thin_o" "$_rt_fo_rest_o" 2>/dev/null; then
                _rt_fo_ok=1
                echo "rt-prefer: rest fmt_one ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_fo_thin_o" "$_rt_fo_rest_o"
            fi
            if [ "$_rt_fo_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_fo_o" "$_rt_fmt_one_seed"; then
                _rt_fo_ok=1
                echo "rt-prefer: rest fmt_one ← $_rt_fmt_one_seed (G-02f-311 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_dt_o" ] && [ -f "$_rt_dispatch_thin_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_dispatch_thin_x" ]; then
              _rt_dt_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_thin_thin.XXXXXX") || true
              _rt_dt_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_thin_rest.XXXXXX") || true
              if [ -n "$_rt_dt_thin_o" ] && [ -n "$_rt_dt_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_dispatch_thin_x" "$_rt_dt_thin_o" \
                && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_DISPATCH_THIN_FROM_X \
                     -c -o "$_rt_dt_rest_o" "$_rt_dispatch_thin_seed" \
                && pure_ld_partial_merge "$_rt_dt_o" "$_rt_dt_thin_o" "$_rt_dt_rest_o" 2>/dev/null; then
                _rt_dt_ok=1
                echo "rt-prefer: rest dispatch_thin ← full .x + rest marker (R2 H=0)"
              fi
              rm -f "$_rt_dt_thin_o" "$_rt_dt_rest_o"
            fi
            if [ "$_rt_dt_ok" = "0" ]; then
              # shellcheck disable=SC2086
              # cold / no PREFER：全 C 体；product 冷路径仍带 ASM_USE_COMPILER_IMPL_C 选 full 分派
              if $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_ASM_USE_COMPILER_IMPL_C -c -o "$_rt_dt_o" "$_rt_dispatch_thin_seed"; then
                _rt_dt_ok=1
                echo "rt-prefer: rest dispatch_thin ← $_rt_dispatch_thin_seed (G-02f-312 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_di_o" ] && [ -f "$_rt_dispatch_impl_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_dispatch_impl_x" ]; then
              _rt_di_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_impl_thin.XXXXXX") || true
              _rt_di_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_dispatch_impl_rest.XXXXXX") || true
              if [ -n "$_rt_di_thin_o" ] && [ -n "$_rt_di_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_dispatch_impl_x" "$_rt_di_thin_o" \
                && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_DISPATCH_IMPL_FROM_X \
                     -c -o "$_rt_di_rest_o" "$_rt_dispatch_impl_seed" \
                && pure_ld_partial_merge "$_rt_di_o" "$_rt_di_thin_o" "$_rt_di_rest_o" 2>/dev/null; then
                _rt_di_ok=1
                echo "rt-prefer: rest dispatch_impl ← full .x + rest marker (R2 H=0)"
              fi
              rm -f "$_rt_di_thin_o" "$_rt_di_rest_o"
            fi
            if [ "$_rt_di_ok" = "0" ]; then
              # shellcheck disable=SC2086
              # same product NO_C / pipeline / impl flags as runtime rest
              if $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_di_o" "$_rt_dispatch_impl_seed"; then
                _rt_di_ok=1
                echo "rt-prefer: rest dispatch_impl ← $_rt_dispatch_impl_seed (G-02f-313 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_xe_o" ] && [ -f "$_rt_run_x_emit_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_run_x_emit_x" ]; then
              _rt_xe_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_x_emit_thin.XXXXXX") || true
              _rt_xe_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_run_x_emit_rest.XXXXXX") || true
              if [ -n "$_rt_xe_thin_o" ] && [ -n "$_rt_xe_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_run_x_emit_x" "$_rt_xe_thin_o" \
                && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_RUN_X_EMIT_FROM_X \
                     -c -o "$_rt_xe_rest_o" "$_rt_run_x_emit_seed" \
                && pure_ld_partial_merge "$_rt_xe_o" "$_rt_xe_thin_o" "$_rt_xe_rest_o" 2>/dev/null; then
                _rt_xe_ok=1
                echo "rt-prefer: R2 run_x_emit ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_xe_thin_o" "$_rt_xe_rest_o"
            fi
            if [ "$_rt_xe_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_xe_o" "$_rt_run_x_emit_seed"; then
                _rt_xe_ok=1
                echo "rt-prefer: rest run_x_emit ← $_rt_run_x_emit_seed (G-02f-314 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_abk_o" ] && [ -f "$_rt_run_asm_backend_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_run_asm_backend_x" ]; then
              _rt_abk_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_abk_thin.XXXXXX") || true
              _rt_abk_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_abk_rest.XXXXXX") || true
              if [ -n "$_rt_abk_thin_o" ] && [ -n "$_rt_abk_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_run_asm_backend_x" "$_rt_abk_thin_o" \
                && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_RUN_ASM_BACKEND_FROM_X \
                     -c -o "$_rt_abk_rest_o" "$_rt_run_asm_backend_seed" \
                && pure_ld_partial_merge "$_rt_abk_o" "$_rt_abk_thin_o" "$_rt_abk_rest_o" 2>/dev/null; then
                _rt_abk_ok=1
                echo "rt-prefer: R2 run_asm_backend ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_abk_thin_o" "$_rt_abk_rest_o"
            fi
            if [ "$_rt_abk_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_abk_o" "$_rt_run_asm_backend_seed"; then
                _rt_abk_ok=1
                echo "rt-prefer: rest run_asm_backend ← $_rt_run_asm_backend_seed (G-02f-315 seed slice)"
              fi
            fi
          fi
          if [ -n "$_rt_rcp_o" ] && [ -f "$_rt_run_compiler_parsed_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_run_compiler_parsed_x" ]; then
              _rt_rcp_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_rcp_thin.XXXXXX") || true
              _rt_rcp_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_rcp_rest.XXXXXX") || true
              if [ -n "$_rt_rcp_thin_o" ] && [ -n "$_rt_rcp_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_run_compiler_parsed_x" "$_rt_rcp_thin_o" \
                && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_RUN_COMPILER_PARSED_FROM_X \
                     -c -o "$_rt_rcp_rest_o" "$_rt_run_compiler_parsed_seed" \
                && pure_ld_partial_merge "$_rt_rcp_o" "$_rt_rcp_thin_o" "$_rt_rcp_rest_o" 2>/dev/null; then
                _rt_rcp_ok=1
                echo "rt-prefer: R2 run_compiler_parsed ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_rcp_thin_o" "$_rt_rcp_rest_o"
            fi
            if [ "$_rt_rcp_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_rcp_o" "$_rt_run_compiler_parsed_seed"; then
                _rt_rcp_ok=1
                echo "rt-prefer: rest run_compiler_parsed ← $_rt_run_compiler_parsed_seed (G-02f-316 seed slice cold)"
              fi
            fi
          fi
          if [ -n "$_rt_st_o" ] && [ -f "$_rt_stack_seed" ]; then
            # R2 full H=0：PREFER_X_O=1 时 full .x + rest seed (-D，仅 marker) → cc -r 合并
            if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ] && [ -f "$_rt_stack_x" ]; then
              _rt_st_thin_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_stack_thin.XXXXXX") || true
              _rt_st_rest_o=$(mktemp "${TMPDIR:-/tmp}/rtpref_stack_rest.XXXXXX") || true
              if [ -n "$_rt_st_thin_o" ] && [ -n "$_rt_st_rest_o" ] \
                && rt_prefer_try_x_to_o "$_rt_stack_x" "$_rt_st_thin_o" \
                && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -DXLANG_RT_STACK_FROM_X \
                     -c -o "$_rt_st_rest_o" "$_rt_stack_seed" \
                && pure_ld_partial_merge "$_rt_st_o" "$_rt_st_thin_o" "$_rt_st_rest_o" 2>/dev/null; then
                _rt_st_ok=1
                echo "rt-prefer: rest stack esc ← full .x + rest marker (R2 full H=0)"
              fi
              rm -f "$_rt_st_thin_o" "$_rt_st_rest_o"
            fi
            if [ "$_rt_st_ok" = "0" ]; then
              # shellcheck disable=SC2086
              if $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_st_o" "$_rt_stack_seed"; then
                _rt_st_ok=1
                echo "rt-prefer: rest stack esc ← $_rt_stack_seed (G-02f-317 seed slice cold)"
              fi
            fi
          fi
          _rt_rest_defs="-DXLANG_RT_CONTENT_FROM_X"
          if [ "$_rt_util_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_UTIL_FROM_X"
          fi
          if [ "$_rt_argv_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_ARGV_FROM_X"
          fi
          if [ "$_rt_ef_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_EMIT_FLAGS_FROM_X"
          fi
          if [ "$_rt_pre_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_PREAMBLE_FROM_X"
          fi
          if [ "$_rt_compile_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_COMPILE_FROM_X"
          fi
          if [ "$_rt_run_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_RUN_EXEC_FROM_X"
          fi
          if [ "$_rt_asm_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_ASM_STUB_FROM_X"
          fi
          if [ "$_rt_entry_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_ENTRY_FROM_X"
          fi
          if [ "$_rt_diag_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_DIAG_ERRNO_FROM_X"
          fi
          if [ "$_rt_est_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_EMIT_STATE_FROM_X"
          fi
          if [ "$_rt_elfd_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_PIPELINE_ELF_DIAG_FROM_X"
          fi
          if [ "$_rt_lr_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_LIB_ROOT_FROM_X"
          fi
          if [ "$_rt_pd_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_PARSE_DIAG_FROM_X"
          fi
          if [ "$_rt_fs_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_FS_OPEN_FROM_X"
          fi
          if [ "$_rt_ab_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_ARENA_BUF_FROM_X"
          fi
          if [ "$_rt_fo_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_FMT_ONE_FROM_X"
          fi
          if [ "$_rt_dt_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_DISPATCH_THIN_FROM_X"
          fi
          if [ "$_rt_di_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_DISPATCH_IMPL_FROM_X"
          fi
          if [ "$_rt_xe_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_RUN_X_EMIT_FROM_X"
          fi
          if [ "$_rt_abk_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_RUN_ASM_BACKEND_FROM_X"
          fi
          if [ "$_rt_rcp_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_RUN_COMPILER_PARSED_FROM_X"
          fi
          if [ "$_rt_st_ok" = "1" ]; then
            _rt_rest_defs="$_rt_rest_defs -DXLANG_RT_STACK_FROM_X"
          fi
          # wave318: full non-default hybrid set ⇒ monofile rest T=0 under all
          # XLANG_RT_*_FROM_X (NO_C already carries 5 RT_SEED_SLICE FROM_X).
          # PLATFORM: SHARED freestanding — omit empty mega rest host-cc.
          _rt_full_slices_ok=0
          if [ "$_rt_content_ok" = "1" ] \
            && [ "$_rt_util_ok" = "1" ] && [ "$_rt_argv_ok" = "1" ] \
            && [ "$_rt_ef_ok" = "1" ] && [ "$_rt_compile_ok" = "1" ] \
            && [ "$_rt_run_ok" = "1" ] && [ "$_rt_asm_ok" = "1" ] \
            && [ "$_rt_entry_ok" = "1" ] && [ "$_rt_diag_ok" = "1" ] \
            && [ "$_rt_elfd_ok" = "1" ] && [ "$_rt_lr_ok" = "1" ] \
            && [ "$_rt_fs_ok" = "1" ] && [ "$_rt_fo_ok" = "1" ] \
            && [ "$_rt_dt_ok" = "1" ] && [ "$_rt_di_ok" = "1" ] \
            && [ "$_rt_xe_ok" = "1" ] && [ "$_rt_abk_ok" = "1" ] \
            && [ "$_rt_rcp_ok" = "1" ]; then
            _rt_full_slices_ok=1
          fi
          if [ "$_rt_content_ok" = "1" ]; then
            _rt_link_objs="$_rt_c_o"
            if [ "$_rt_util_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_u_o"
            fi
            if [ "$_rt_argv_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_a_o"
            fi
            if [ "$_rt_ef_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_e_o"
            fi
            # PLATFORM: SHARED — do NOT merge RT_SEED_SLICE objs into no_c.
            # g05_relink_env always links:
            #   rt_arena_buf / rt_emit_state / rt_preamble / rt_stack / rt_parse_diag
            # as separate .o. Merging them here caused Darwin 22× duplicate symbols
            # (parse_diag recovery + arena/emit/preamble/stack). Keep FROM_X on rest
            # (above) so no_c leaves those symbols U; permanent slice .o provide them.
            # Still merge non-slice hybrid pieces (content/util/argv/…/fs/fmt/dispatch…).
            if [ "$_rt_compile_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_cmp_o"
            fi
            if [ "$_rt_run_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_run_o"
            fi
            if [ "$_rt_asm_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_asm_o"
            fi
            if [ "$_rt_entry_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_ent_o"
            fi
            if [ "$_rt_diag_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_diag_o"
            fi
            if [ "$_rt_elfd_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_elfd_o"
            fi
            if [ "$_rt_lr_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_lr_o"
            fi
            if [ "$_rt_fs_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_fs_o"
            fi
            if [ "$_rt_fo_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_fo_o"
            fi
            if [ "$_rt_dt_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_dt_o"
            fi
            if [ "$_rt_di_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_di_o"
            fi
            if [ "$_rt_xe_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_xe_o"
            fi
            if [ "$_rt_abk_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_abk_o"
            fi
            if [ "$_rt_rcp_ok" = "1" ]; then
              _rt_link_objs="$_rt_link_objs $_rt_rcp_o"
            fi
            # Do NOT cp hybrid temps over permanent RT_SEED_SLICE .o (Makefile/seed
            # path owns those). Hybrid thin+rest can be incomplete and would
            # poison product asm codegen (CG002 code_len=0 on Darwin).
            # shellcheck disable=SC2086
            if [ "$_rt_full_slices_ok" = "1" ]; then
              # wave318/319: all non-default slices present → empty mega rest;
              # no host-cc of seeds/runtime.from_x.c (prefer hybrid or cold seeds).
              if pure_ld_partial_merge "$_rt_o" $_rt_link_objs 2>/dev/null; then
                if [ "${XLANG_G05_PREFER_X_O:-1}" = "1" ]; then
                  echo "rt-prefer: $_rt_o ← hybrid slices only; omit empty mega rest (wave318)"
                else
                  echo "rt-prefer: $_rt_o ← cold slices only; omit empty mega rest (wave319)"
                fi
                _rt_done=1
              fi
            elif [ "$allow_monofile" = "1" ] && [ -f "$_rt" ] && [ -n "$_rt_rest_o" ] \
              && $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc \
                   $_rt_rest_defs -c -o "$_rt_rest_o" "$_rt" \
              && pure_ld_partial_merge "$_rt_o" $_rt_link_objs "$_rt_rest_o" 2>/dev/null; then
              # wave320: partial monofile rest only with explicit archaeology escape.
              echo "rt-prefer: $_rt_o ← R2..R10/diag/…/parsed + monofile rest (ALLOW_MONOFILE_LAST_RESORT=1)"
              _rt_done=1
            elif [ "$_rt_full_slices_ok" != "1" ]; then
              echo "rt-prefer: partial multi-slice; refuse monofile rest (wave320; set XLANG_RT_ALLOW_MONOFILE_LAST_RESORT=1)" >&2
            fi
          fi
          if [ "$_rt_done" = "0" ]; then
            echo "rt-prefer: L2 multi-slice runtime incomplete (wave320)" >&2
          fi
          rm -f "$_rt_c_o" "$_rt_u_o" "$_rt_a_o" "$_rt_e_o" "$_rt_p_o" "$_rt_cmp_o" "$_rt_run_o" "$_rt_asm_o" "$_rt_ent_o" "$_rt_diag_o" "$_rt_est_o" "$_rt_elfd_o" "$_rt_lr_o" "$_rt_pd_o" "$_rt_fs_o" "$_rt_ab_o" "$_rt_fo_o" "$_rt_dt_o" "$_rt_di_o" "$_rt_xe_o" "$_rt_abk_o" "$_rt_rcp_o" "$_rt_st_o" "$_rt_rest_o"
        fi
        if [ "$_rt_done" = "0" ]; then
          # wave320: product default refuses monofile full-seed last-resort (7.1.2).
          # multi-error recovery 权威在 seeds/rt_parse_diag.from_x.c → 单独链 rt_parse_diag.o
          # （g05_relink_env RT_SEED_SLICE）；NO_C 已带 XLANG_RT_PARSE_DIAG_FROM_X，禁止再 merge。
          if [ "$allow_monofile" = "1" ] && [ -f "$_rt" ]; then
            # wave321: monofile seed physically retired; this branch only if a
            # local archaeology copy is reintroduced outside the tree.
            echo "rt-prefer: runtime_driver_no_c.o ← monofile seed + NO_C (ALLOW_MONOFILE_LAST_RESORT=1)"
            # shellcheck disable=SC2086
            if ! $CC $BASE_CFLAGS $RUNTIME_DRIVER_NO_C_CFLAGS -I. -Iinclude -Isrc -c -o "$_rt_o" "$_rt"; then
              echo "rt-prefer: monofile host-cc failed" >&2
              return 1
            fi
            _rt_done=1
          else
            echo "rt-prefer: refuse monofile last-resort for $_rt_o (wave321 monofile retired; need full multi-slice)" >&2
            return 1
          fi
        fi
      fi
    else
      echo "rt-prefer: missing content layer seed ($_rt_content_seed) (wave321 monofile retired)" >&2
      return 1
    fi
  return 0
}

try_ensure_rt_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-rt-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ "$o" != "src/runtime_driver_no_c.o" ]; then
    return 3
  fi
  # wave320: propagate multi-slice fail / monofile refuse (exit 1).
  ensure_rt_prefer_one "$o"
}

# ---------------------------------------------------------------------------
# wave767: try-pipeline-abi-prefer OUT — g05 pipeline_abi product PREFER (single body).
#
# Single leaf: src/runtime_pipeline_abi.o (R1_EXTRA_CFLAGS; cold twin = ensure_one
# with RUNTIME_PIPELINE_ABI_CFLAGS / -DXLANG_USE_X_PIPELINE).
# When an xlang binary works (always hybrid for this leaf; not gated on PREFER=1):
#   full .x → .o via rt_prefer_try_x_to_o with G05_X_O_WEAK=1 (Darwin ld -r
#     pure-dup tolerance; same harness as wave766 — Cap residual realpath /
#     thread_fn_ptr prologue required by runtime_pipeline_abi.x)
#   rest = seeds/runtime_pipeline_abi.from_x.c under
#     -DXLANG_USE_X_PIPELINE -DXLANG_RUNTIME_PIPELINE_ABI_FROM_X
#   merge: pure_ld_partial_merge thin + rest → OUT
# Prefer fail / no xlang → ensure_one cold + pipeline ABI cflags (or keep OUT).
#
# Stage 12.0.5 COMPILE residual (pipeline_abi mega pure-asm product skip):
#   · typeck wall slim ✅ dual-end emit mac ~45–60s / Ubuntu ~75s (hang closed).
#   · opaque freestanding surface ✅ XLANG_WEAK in runtime_driver_abi.from_x.c
#     (pure-asm may U those faces; pure-ld resolves vs driver_abi bag).
#   · product pure-asm install residual: Cap residual only in seed rest
#     (pure monofile incomplete; basename skip + call-site PREFER_ASM_O_RT=0).
#
# Callers: g05_ensure (wave767) · product ensure_one route for pipeline_abi.
# Exit codes:
#   0 — OUT is runtime_pipeline_abi.o; prefer or cold body produced OUT
#   3 — OUT is not src/runtime_pipeline_abi.o
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · product cold path = egg hybrid (not cold full seed).
# G.7: reuses rt_prefer_try_x_to_o harness (有则补全; no second -E prologue).
# Residual after: ~~target_cpu~~(wave768) · other L2 · pure-ld · physical delete.
# ---------------------------------------------------------------------------

pipeline_abi_prefer_cflags() {
  # stdout: cold seed flags (Makefile/env or default -DXLANG_USE_X_PIPELINE).
  if [ -n "${RUNTIME_PIPELINE_ABI_CFLAGS:-}" ]; then
    printf '%s' "$RUNTIME_PIPELINE_ABI_CFLAGS"
  else
    printf '%s' "$_DEFAULT_RUNTIME_PIPELINE_ABI_CFLAGS"
  fi
}

ensure_pipeline_abi_prefer_one() {
  local o="$1"
  local seed="seeds/runtime_pipeline_abi.from_x.c"
  local x_src="src/runtime_pipeline_abi.x"
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o cold_flags

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-pipeline-abi-prefer: missing seed $seed" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    # Incomplete Darwin libtool archive masquerading as .o → always rebuild.
    # PLATFORM: MACOS Cap residual (10.3.2); LINUX never matches.
    if pipeline_abi_o_is_libtool_archive "$o"; then
      local arch_sz
      arch_sz=$(wc -c <"$o" | tr -d ' ')
      if [ -z "$arch_sz" ] || [ "$arch_sz" -lt 1000000 ]; then
        log "pipeline_abi prefer: incomplete libtool archive $o (${arch_sz:-0}B) → force rebuild"
        stale=1
      fi
    fi
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi.h ] && [ src/runtime_pipeline_abi.h -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi_param_ptr_slot_thin.x ] \
      && [ src/runtime_pipeline_abi_param_ptr_slot_thin.x -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi_slot_bytes_thin.x ] \
      && [ src/runtime_pipeline_abi_slot_bytes_thin.x -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi_fnptr_as_thin.x ] \
      && [ src/runtime_pipeline_abi_fnptr_as_thin.x -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi_asm_expr_thin.x ] \
      && [ src/runtime_pipeline_abi_asm_expr_thin.x -nt "$o" ]; then
      stale=1
    fi
    if [ -f src/runtime_pipeline_abi_fnptr_array_esz_thin.x ] \
      && [ src/runtime_pipeline_abi_fnptr_array_esz_thin.x -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (pipeline-abi-prefer)"
      # Still inject thin leaves (small -E) when present.
      pipeline_abi_inject_reent_deep_copy_thin "$o" || true
      pipeline_abi_inject_fixed_array_copy_thin "$o" || true
      pipeline_abi_inject_slot_bytes_thin "$o" || true
      pipeline_abi_inject_field_load_sz_thin "$o" || true
      pipeline_abi_inject_unused_hints_thin "$o" || true
      pipeline_abi_inject_wpo_dump_thin "$o" || true
      pipeline_abi_inject_fnptr_as_thin "$o" || true
      pipeline_abi_inject_asm_expr_thin "$o" || true
      pipeline_abi_inject_fnptr_array_esz_thin "$o" || true
      pipeline_abi_inject_assign_thin "$o" || true
      # ttc-thin only when seed/x is newer (inject-only below). Re-injecting
      # on every up-to-date g05 stacks static inner copies.
      return 0
    fi
    # Thin inject: mega .x prefer -E is hang-prone (92k LOC). When a hybrid
    # OUT already exists, inject-only instead of full hybrid rebuild.
    # FORCE=1 / XLANG_HOST_CC_SEED_FORCE=1 still does full thin+rest prefer
    # on POSIX gold. PLATFORM: SHARED shell · LINUX gold + MACOS.
    # PLATFORM: WINDOWS — leftover PE cannot -E mega; FORCE skip is below.
    if [ -s "$o" ] && ! pipeline_abi_o_is_libtool_archive "$o" \
      && { [ -f src/runtime_pipeline_abi_reent_deep_copy_thin.x ] \
      || [ -f src/runtime_pipeline_abi_fixed_array_copy_thin.x ]; }; then
      log "pipeline_abi prefer: inject-only thins (skip full mega -E; HOST_CC_SEED_FORCE=1 for hybrid)"
      pipeline_abi_inject_reent_deep_copy_thin "$o" || true
      pipeline_abi_inject_fixed_array_copy_thin "$o" || true
      pipeline_abi_inject_slot_bytes_thin "$o" || true
      pipeline_abi_inject_field_load_sz_thin "$o" || true
      pipeline_abi_inject_unused_hints_thin "$o" || true
      pipeline_abi_inject_wpo_dump_thin "$o" || true
      # ttc-thin merge-fail is pre-existing (already-strong dup); do not
      # abort before blkpeel (same as arrcopy || true before ttc).
      pipeline_abi_inject_type_to_c_repr_thin "$o" || true
      # blkpeel merge-fail is pre-existing on Ubuntu leftover (already-strong
      # dup). Do not abort before ptrslot (this leaf).
      pipeline_abi_inject_binop_block_peel_thin "$o" || true
      pipeline_abi_inject_param_ptr_slot_thin "$o" || return 1
      pipeline_abi_inject_fnptr_as_thin "$o" || return 1
      pipeline_abi_inject_asm_expr_thin "$o" || return 1
      pipeline_abi_inject_fnptr_array_esz_thin "$o" || return 1
      pipeline_abi_inject_assign_thin "$o" || true
      return 0
    fi
  fi

  # PLATFORM: WINDOWS — leftover PE (Track L / can_run egg) is executable so
  # hybrid rt_prefer_try_x_to_o would launch ./xlang -E of mega
  # runtime_pipeline_abi.x (92k LOC; hang / multi-GB RSS, stderr discarded).
  # SAT rebuild sets XLANG_HOST_CC_SEED_FORCE=1 which skips the inject-only
  # keep above. Do NOT keep leftover hybrid $o: Windows leftover pabi is tens
  # of KiB (FROM_X rest without thin) vs ~1.4MiB POSIX hybrid, and omits
  # pipeline_type_* / pipeline_asm_* / ast_pool_* that tip glue UNDEF at phase1.
  # Cold full seed (no FROM_X) hits 251 void*/struct* dual-decls in
  # seeds/runtime_pipeline_abi.from_x.c — not a viable identity path (wave176).
  # G.7 有则补全 of the POSIX hybrid rest CC line + pure_ld_partial_merge:
  #   rest = host-cc seed under -DXLANG_RUNTIME_PIPELINE_ABI_FROM_X (3s, 220KiB)
  #          plus WIN_LEFTOVER_GROW_VEC so leftover-PE rest compiles seed
  #          ifndef-FROM_X cold twins POSIX .x thin -E would provide T:
  #          grow_vec/sidecar + wave123 glue_arm64_mov_*/lea + wave125
  #          pipeline_asm_ctx_layout + wave133 glue_enc_sxt/zxt (closed out
  #          of wave132 so WIN rest does not take ty_ref / append_bytes
  #          dual-decl) + wave273 F7 data-section (emit_data_len /
  #          append_data_u32_le / set_shndx_override; BSS moved before first
  #          use; rest of wave273 stays closed — append_bytes dual-decl) +
  #          wave74 driver_dep_* + wave77 typeck_ndep/sidecar + wave73
  #          pipeline_diag_* + path wrappers (import_path_to_file_path /
  #          get_entry_dir / cstr_ends_with_dot_x / import_path_is_file_path /
  #          path_try_realpath_inplace / resolve_file_import_path /
  #          resolve_import_file_path_multi; _impl already always compiled) +
  #          wave67 path_bufs_reset / copy_entry_dir / fill_ctx_path_buffers /
  #          pctx_seed_dep_slots / pctx_seed_dep_import_paths_only /
  #          pctx_update_dep_slots_no_reset / set_use_asm_backend +
  #          wave68/70 entry_dir BSS+set/get + dep arena/module slots
  #          (set_dep_slots / get_dep_arena_slot; independent ifndefs) +
  #          is_object/_magic + fclose_asm_out cluster (fp_is_stdout /
  #          fclose_file; independent ifndefs) + user_std_net/skip_typeck
  #          cluster (std_dep_skip_x_typeck / std_net_dep_path /
  #          std_io_driver_dep_path / dep_parse_skip_typeck_path;
  #          independent ifndefs; wrappers call always-extern pipeline.x
  #          faces; leftover standalone defines 0 of remaining unique) +
  #          dep_prerun_entry_dir + _pick (independent ifndefs; entry_dir
  #          calls _pick; leftover standalone defines 0 of remaining unique) +
  #          merge_deps_path_already_out + _scan + merge_direct_then_transitive
  #          deps / dep_paths (independent ifndefs; wrappers call always-
  #          compiled _impl; _impl already calls already_out; leftover
  #          standalone defines 0 of remaining unique) +
  #          one_ctx_for_dep_prerun + map_impl + find_loaded_import_index +
  #          _scan (independent ifndefs; wrapper calls always-compiled _impl;
  #          _impl already calls map_impl; map_impl calls find_loaded_import_index
  #          which calls _scan; leftover standalone defines 0 of remaining unique) +
  #          load_direct_imports_for_asm_layout + _impl + module_num_imports +
  #          load_one_direct_resolve_read_preprocess + load_one_direct_import_at +
  #          load_direct_fail_cleanup + preprocess_raw_to_malloc / _impl
  #          (independent ifndefs; unlike merge/one_ctx, _impl is still ifndef —
  #          convert it with the wrapper; resolve_read calls already-OR'd path
  #          wrappers / pipeline_diag plus preprocess_raw_to_malloc; leftover
  #          standalone defines 0 of remaining unique) +
  #          public xlang_preprocess / with_path / quiet (one independent
  #          ifndef; wrappers call already-T _impl; leftover rest compiles
  #          with XLANG_USE_X_PIPELINE so LEGACY preprocess_c_fallback #else
  #          is not parsed; unique lists preprocess + with_path; leftover
  #          standalone defines 0 of remaining unique) +
  #          xlang_lsp_free_loaded_imports (independent ifndef; wrapper
  #          calls already-T _impl with void**; header struct ast_Module **
  #          @304 is prototype+definition, not a dual-decl; leftover
  #          standalone defines 0 of remaining unique; do not convert
  #          neighboring xlang_lsp_ptr_slot_clear — not unique) +
  #          collect leftover cluster (12 independent ifndefs: strdup /
  #          to_load_has / seed_to_load / enqueue_module_imports /
  #          tmp_parse_and_enqueue / deps_process_one / deps_transitive_impl /
  #          deps_transitive / paths_tmp_resolve_parse_enqueue /
  #          paths_process_one / dep_paths_transitive_impl /
  #          dep_paths_transitive; unlike merge/one_ctx, _impl is still
  #          ifndef — convert with the wrapper; wrappers call _impl;
  #          _impl calls seed_to_load + process_one; process_one calls
  #          already-OR'd load_one_direct_import_at + find_loaded_import_index
  #          + tmp_parse; unique lists deps_transitive + dep_paths_transitive;
  #          leftover standalone defines 0 of remaining unique; do not
  #          convert neighboring xlang_driver_asm_prepare_entry_elf_emit —
  #          it calls closed debug_trace) +
  #          dep_prerun leftover cluster (6 independent ifndefs: thread_fn
  #          impl+wrapper / large_stack impl+wrapper / parse_skip
  #          impl+wrapper / typeck_only impl+wrapper / parse_only
  #          impl+wrapper / for_asm_module_o; unlike merge/one_ctx, _impl
  #          is still ifndef — convert with the wrapper; parse_skip_impl
  #          calls large_stack; large_stack_impl calls thread_fn;
  #          thread_fn_impl calls always-extern pipeline_run_x_pipeline;
  #          unique lists thread_fn + large_stack + four dep_prerun
  #          wrappers; leftover standalone defines 0 of remaining unique;
  #          do not convert neighboring pipeline_run_x_thread_fn_ptr —
  #          not unique — or xlang_asm_codegen_elf_o_product_emit /
  #          thread_fn_ptr — not unique; elf_o leftover cluster converts
  #          thread_fn+large_stack only — or
  #          xlang_driver_asm_prepare_entry_elf_emit — calls closed
  #          debug_trace; pipeline_run_x_pipeline_impl is a separate
  #          leftover cluster after closing enclosing wave101) +
  #          elf_o leftover cluster (2 independent ifndefs: thread_fn
  #          impl+wrapper / large_stack impl+wrapper; unlike merge/one_ctx,
  #          _impl is still ifndef — convert with the wrapper; thread_fn_impl
  #          calls always-extern asm_asm_codegen_elf_o; large_stack_impl
  #          calls thread_fn + driver_run_thread_on_large_stack; unique
  #          lists thread_fn + large_stack; leftover standalone defines 0
  #          of remaining unique; do not convert neighboring
  #          xlang_asm_codegen_elf_o_product_emit / thread_fn_ptr — not
  #          unique — or xlang_driver_asm_prepare_entry_elf_emit — calls
  #          closed debug_trace) +
  #          glue_type leftover cluster (surgical extract at start of
  #          independent wave154 ifndef: size_simple + align_simple +
  #          helpers empty_struct / layout_metrics / w154_layout_name_eq;
  #          unique lists size_simple + align_simple; leftover standalone
  #          defines 0 of remaining unique; glue_vector_type_lanes_esz_c
  #          stays closed — not unique — leftover rest externs it; do not
  #          convert neighboring typeck_typeck_struct_layout_metrics — not
  #          unique — or glue_type_named_layout_size_any_module_elf_c —
  #          nested in wave178) +
  #          rec leftover cluster (surgical extract of inner wave152
  #          ifndef after closing enclosing wave149: rec + lit_i32 /
  #          match_subject_field / emit_expr_elf_c wrapper / emit_expr_elf_fast;
  #          rec calls fast — convert together; unique lists rec; leftover
  #          standalone defines 0 of remaining unique; wave149 binop helpers
  #          stay closed; wave153 block_body stays its own ifndef) +
  #          append_reloc leftover cluster (surgical extract of nested
  #          wave273 after closing enclosing wave154/wave178/wave273
  #          reopen-after-F7: pipeline_elf_ctx_append_reloc_absolute64
  #          only; unique lists absolute64; leftover standalone defines 0
  #          of remaining unique; callee append_reloc_typed stays closed —
  #          not unique — leftover rest U it; SAT / leftover standalone
  #          provide T; do not convert neighboring append_reloc / typed —
  #          not unique — or reloc_sym_name_ptr — not unique — or
  #          glue_type_named_layout_size_any_module_elf_c — nested in
  #          wave178 stub) +
  #          sret leftover cluster (surgical extract of nested wave223
  #          after closing enclosing wave154 reopen-after-glue_type +
  #          wave178: three sret setters + getters sharing BSS cells;
  #          unique lists the three setters; leftover standalone defines
  #          0 of remaining unique; getters not unique — SAT / leftover
  #          standalone provide T; convert together so setters have a
  #          cell; do not convert neighboring wave222 module/dep_pipe —
  #          not unique — or named_layout — seed body is a stub — or
  #          pipeline_module_*_storage_* — nested wave178 sidecar) +
  #          pipeline_run_x_pipeline_impl leftover cluster (surgical
  #          extract after closing enclosing wave101: impl only; unique
  #          lists impl; leftover standalone defines 0 of remaining unique;
  #          callees parse_entry/load_deps/typecheck/codegen wrappers not
  #          unique — SAT / leftover standalone provide T; do not convert
  #          neighboring driver_emit_lib_root_release — nested wave101
  #          sidecar BSS) +
  #          modlet leftover cluster (surgical extract of nested wave139
  #          after closing enclosing wave136: four unique prepare/seed/
  #          register/lit_inits faces + BSS g_pipeline_asm_modlet_cold +
  #          helpers name_is_shared/load/store; unique lists the four;
  #          leftover standalone defines 0 of remaining unique; name_is_shared
  #          / load / store not unique — SAT / leftover standalone provide T;
  #          convert together so unique faces have a cell; do not convert
  #          neighboring wave140 index — not unique) +
  #          array_lit leftover cluster (surgical extract of nested wave143
  #          unique after closing enclosing remaining wave136:
  #          pipeline_asm_array_lit_elem_byte_sz_c + helper
  #          pipeline_asm_array_lit_elem_type_ref; unique lists
  #          elem_byte_sz_c; leftover standalone defines 0 of remaining
  #          unique; elem_type_ref not unique — SAT / leftover standalone
  #          provide T; convert together so unique has a helper; do not
  #          convert neighboring wave140 index — not unique — or remaining
  #          wave143 emit/empty/force_esz — not unique) +
  #          stack_off leftover unique (surgical extract of nested wave148
  #          unique after closing enclosing remaining wave136:
  #          glue_asm_local_var_stack_off_scoped; unique lists this face;
  #          leftover standalone defines 0 of remaining unique; callees
  #          var_name_len/into leftover rest already T; find_offset_scoped
  #          leftover rest already T uint8_t*; find_offset leftover rest U —
  #          SAT / leftover standalone provide T; do not convert neighboring
  #          remaining wave143 emit/empty/force_esz — not unique — or
  #          remaining wave148 vector-lane emit — not unique) +
  #          glue_func_return leftover unique (surgical extract of nested
  #          wave192 unique after closing enclosing wave154 reopen-after-
  #          glue_type + wave178 INDEX-peel: glue_func_return_byte_size_c;
  #          unique lists this face; leftover standalone defines 0 of
  #          remaining unique; seed body was a stub return 0 — port the
  #          real .x body instead of OR'ing the stub; callees size_simple
  #          leftover rest already T; kind_ord leftover rest already extern
  #          void*; num_funcs always-compiled void* — do not re-extern;
  #          func_return_type_at leftover rest T later so extract carries
  #          a void* extern; leftover rest U num_funcs — SAT / leftover
  #          standalone provide T; do not convert neighboring dual_gp /
  #          param_home_width — not unique) +
  #          named_layout leftover unique (surgical extract of nested
  #          wave191 unique after closing enclosing wave154 reopen-after-
  #          glue_type + wave178 INDEX-peel: glue_type_named_layout_size_any_module_elf_c;
  #          unique lists this face; leftover standalone defines 0 of
  #          remaining unique; seed body was a stub return 0 — port the
  #          real .x body instead of OR'ing the stub; callees leftover rest
  #          already T/extern from glue_type + array_lit clusters; ndep
  #          always-compiled struct* — do not re-extern; leftover rest U
  #          emit_module_ref_c / emit_dep_pipe_c defs — SAT / leftover
  #          standalone provide T; do not convert neighboring pass_addr /
  #          dual_gp / param_home_width — not unique) +
  #          glue_call_return leftover unique (surgical extract of nested
  #          wave194 unique after closing enclosing wave154 reopen-after-
  #          glue_type + wave178 INDEX-peel: glue_call_return_byte_size_c;
  #          unique lists this face; leftover standalone defines 0 of
  #          remaining unique; seed body was a stub return -1 — port the
  #          real .x body instead of OR'ing the stub; callees size_simple
  #          leftover rest already T; kind_ord / func_return_type_at /
  #          emit_dep_pipe / emit_module_ref leftover rest already extern;
  #          extract carries resolve + get_dep_return_type void* externs;
  #          leftover rest U glue_asm_resolve — SAT / leftover standalone
  #          provide T; do not convert neighboring param_agg / load_var /
  #          wave195–199 — not unique — or glue_asm_resolve — seed stub) +
  #          type_alias leftover unique (surgical extract of nested
  #          wave262 unique after closing enclosing wave154 reopen-after-
  #          sret + wave178 INDEX-peel: pipeline_module_type_alias_storage_reset
  #          / storage_release; unique lists these two faces; leftover
  #          standalone defines 0 of remaining unique; seed bodies are
  #          real — convert unique + BSS + find_slot together so leftover
  #          rest WAVE279 ast_pool_module_reset/release has a cell;
  #          remaining wave262 alloc/set/getters stay closed on leftover
  #          rest — not unique; SAT / leftover standalone provide T; do
  #          not convert neighboring wave224 / wave261 — not unique) +
  #          enum leftover unique (surgical extract of nested wave264
  #          unique after closing enclosing wave154 reopen-after-
  #          type_alias + wave178 INDEX-peel: pipeline_module_enum_storage_reset
  #          / storage_release; unique lists these two faces; leftover
  #          standalone defines 0 of remaining unique; seed bodies are
  #          real — convert unique + BSS + find_slot + header_n/set_header_n
  #          together so leftover rest WAVE279 ast_pool_module_reset/release
  #          has a cell; remaining wave264 alloc/set/getters stay closed
  #          on leftover rest — not unique; SAT / leftover standalone
  #          provide T; do not convert neighboring wave263 import — not
  #          unique — or remaining tl/sl unique — own extracts) +
  #          top_level_let leftover unique (surgical extract of nested
  #          wave265 unique after closing enclosing wave154 reopen-after-
  #          enum + wave178 INDEX-peel: pipeline_module_top_level_let_storage_reset
  #          / storage_release; unique lists these two faces; leftover
  #          standalone defines 0 of remaining unique; seed bodies are
  #          real — convert unique + BSS + find_slot + header_n/set_header_n
  #          together so leftover rest WAVE279 ast_pool_module_reset/release
  #          has a cell; remaining wave265 alloc/set/getters stay closed
  #          on leftover rest — not unique; SAT / leftover standalone
  #          provide T; do not convert neighboring remaining wave264
  #          alloc/set — not unique — or remaining sl unique — own extract) +
  #          struct_layout leftover unique (surgical extract of nested
  #          wave266 unique after closing enclosing wave154 reopen-after-
  #          tl + wave178 INDEX-peel: pipeline_module_struct_layout_storage_reset
  #          / storage_release; unique lists these two faces; leftover
  #          standalone defines 0 of remaining unique; seed bodies are
  #          real — convert unique + BSS + find_slot + header_n/set_header_n
  #          together so leftover rest WAVE279 ast_pool_module_reset/release
  #          has a cell; remaining wave266 alloc/set/getters stay closed
  #          on leftover rest — not unique; SAT / leftover standalone
  #          provide T; do not convert neighboring remaining wave265
  #          alloc/set — not unique) +
  #          block_diverged leftover unique (independent ifndef after
  #          lsp_free; no seed twin in wave213 cluster: glue_asm_block_diverged_set
  #          + getter + BSS together so leftover rest SET/GET share leftover
  #          rest BSS; unique lists setter only — leftover standalone already
  #          T getter; leftover standalone defines 0 of remaining unique;
  #          port from .x @77841/@77856; do not add faces to wave213 cluster
  #          — cold full seed compiles this OR; a second def would dual-def
  #          in the same TU) +
  #          driver_emit leftover unique (surgical extract of nested
  #          wave104 emit sidecar after closing enclosing wave101:
  #          driver_emit_lib_root_release + reset/append/count/len/copy +
  #          BSS + find together so leftover rest SET/GET/release share
  #          leftover rest BSS; unique lists release only — leftover
  #          standalone already T reset/append; leftover standalone
  #          defines 0 of remaining unique; seed bodies are real; do not
  #          convert neighboring asm_qual_sym_layer_* — not unique,
  #          separate BSS family) +
  #          debug_trace leftover unique (independent ifndefs: match +
  #          impl + wrapper together so leftover rest wrapper calls
  #          leftover rest impl; unique lists wrapper only; leftover
  #          standalone defines 0 of remaining unique; leftover rest
  #          FROM_X proto @49851 is void* — the struct* extern @18600
  #          is inside FALSE #ifndef FROM_X wave144/145 nest, not a
  #          leftover-rest dual-decl; do not convert neighboring
  #          pipeline_asm_debug_enabled / mega_pre_reset wrappers —
  #          not unique) +
  #          prepare_entry leftover unique (independent ifndef: unique
  #          lists xlang_driver_asm_prepare_entry_elf_emit; leftover
  #          standalone defines 0 of remaining unique; header @292
  #          prototype+definition; calls leftover rest T debug_trace;
  #          do not convert neighboring product_emit / thread_fn_ptr —
  #          not unique; pabi leftover unique coding is exhausted
  #          after this extract).
  #          pipeline_resolve_path / read_file stay closed this wave.
  #          FROM_X rest otherwise only externs them.
  #   thin = leftover build_asm/pipeline_glue_standalone.o (7/31 archaeology;
  #          ASM_GLUE_STANDALONE_O is empty on product; this file is the only
  #          on-disk provider of pipeline_type_* / ast_pool_* ifndef-FROM_X
  #          twins when PE cannot -E; it does NOT define grow_vec/sidecar)
  # Merge rest-first so tip FROM_X wins overlaps; leftover fills missing twins.
  # POSIX (Linux gold / Darwin): FORCE hybrid -E stays the product path.
  if pipeline_abi_windows_leftover_pe_cannot_e; then
    local win_rest win_thin win_sz
    win_thin="build_asm/pipeline_glue_standalone.o"
    mkdir -p "$(dirname "$o")"
    if [ ! -s "$win_thin" ]; then
      echo "ensure_host_cc_seed_o: Windows leftover PE cannot -E; missing $win_thin (cold twins)" >&2
      return 1
    fi
    win_rest="$(mktemp "${TMPDIR:-/tmp}/pabi_win_rest.XXXXXX")"
    log "pipeline_abi prefer: leftover PE cannot -E mega; host-cc FROM_X rest + grow_vec/sidecar twins + leftover standalone thin"
    # shellcheck disable=SC2086
    if ! $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE \
         -DXLANG_RUNTIME_PIPELINE_ABI_FROM_X \
         -DXLANG_RUNTIME_PIPELINE_ABI_WIN_LEFTOVER_GROW_VEC \
         -c -o "$win_rest" "$seed"; then
      echo "ensure_host_cc_seed_o: Windows FROM_X rest cc failed for $o" >&2
      rm -f "$win_rest"
      return 1
    fi
    if ! pure_ld_partial_merge "$o" "$win_rest" "$win_thin"; then
      echo "ensure_host_cc_seed_o: Windows rest+standalone merge failed for $o" >&2
      rm -f "$win_rest"
      return 1
    fi
    rm -f "$win_rest"
    # PLATFORM: WINDOWS — thin mega / thin wrapper keep relative calls to thin
    # twins (PE first-wins does not rewrite intra-object). Rest WIN_LEFTOVER:
    # get_return/nso/body_ref + WAVE290 mega_body void-main mov-imm-0.
    # G.7: one post-merge redirect script (proved by return-42 / void-main).
    if ! bash scripts/win_pe_pabi_redirect_return_helpers.sh "$o"; then
      echo "ensure_host_cc_seed_o: Windows thin→rest return-helper redirect failed for $o" >&2
      return 1
    fi
    win_sz=$(wc -c <"$o" | tr -d ' ')
    log "prefer Windows leftover-PE hybrid $o <- FROM_X rest + grow_vec/sidecar + $win_thin (${win_sz:-0}B) + return-helper redirect"
    return 0
  fi

  mkdir -p "$(dirname "$o")"

  # Hybrid thin+rest whenever a pin/product egg exists.
  # PLATFORM: SHARED — L4 root fix: sat rebuild forces XLANG_G05_PREFER_X_O=0
  # (-B). Historical gate only hybrid-ed when PREFER=1, so sat re-entered cold
  # full seed (void*/struct* dual decls) and **wiped** a good hybrid .o from
  # ensure_prereqs → pure-ld phase1 missing src/runtime_pipeline_abi.o.
  # Cold full seed is not a viable identity path until seed dual-decls are
  # cleaned; egg hybrid is the single working product cold path for this leaf.
  # PLATFORM: WINDOWS — leftover PE cannot -E; skip this block (predicate).
  if [ -f "$x_src" ] \
    && ! pipeline_abi_windows_leftover_pe_cannot_e \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/pabi_rest.XXXXXX")"
    # WEAK pure thin: Darwin ld -r tolerates residual pure-dup still in rest.
    # Stage 12.0.5: force XLANG_PREFER_ASM_O_RT=0 — opaque freestanding surface
    # closed (WEAK on driver_abi bag) but mega pure monofile still incomplete
    # (Cap residual only in seed rest). Basename ban + RT=0 keep product -E hybrid.
    # PLATFORM: SHARED · G.7 call-site + pure_asm_x_to_o basename skip.
    # shellcheck disable=SC2086
    if XLANG_PREFER_ASM_O_RT=0 G05_X_O_WEAK=1 rt_prefer_try_x_to_o "$x_src" "$thin_o" \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_USE_X_PIPELINE \
           -DXLANG_RUNTIME_PIPELINE_ABI_FROM_X \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      # PLATFORM: MACOS — libtool -static fallback yields ar named .o; Cap LEA
      # and product force_load need a complete hybrid or cold MH_OBJECT, not a
      # thin+rest archive leftover. Discard and fall through to cold seed.
      if pipeline_abi_o_is_libtool_archive "$o"; then
        # Accept complete Darwin prefer archives (thin+rest); discard tiny leftovers.
        # Incomplete Cap residual was ~260KiB (fnptr_thin + pabi_rest_try only).
        local hyb_sz
        hyb_sz=$(wc -c <"$o" | tr -d ' ')
        if [ -n "$hyb_sz" ] && [ "$hyb_sz" -ge 1000000 ]; then
          log "prefer thin+rest $o <- $x_src + seed-rest (Darwin libtool archive ≥1MiB; prefer=${prefer})"
          done=1
        else
          log "pipeline_abi hybrid produced incomplete libtool archive (${hyb_sz:-0}B); discard → cold/seed"
          rm -f "$o"
          done=0
        fi
      else
        log "prefer thin+rest $o <- $x_src + seed-rest (try-pipeline-abi-prefer; prefer=${prefer}; pure-asm skip Cap-residual RT=0)"
        done=1
      fi
    else
      log "pipeline_abi hybrid failed; fallback full seed (prefer=${prefer})"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    # 4.2.7: inject nested reent deep-copy esz fix without full mega -E.
    # Full runtime_pipeline_abi.x prefer -E is multi-minute / hang-prone (92k LOC);
    # thin leaf re-emits only glue_slice_let_reent_deep_copy_after_dual_gp_elf_c
    # (same body as mega pure leave) and first-wins ld -r over weak pure.
    pipeline_abi_inject_reent_deep_copy_thin "$o" || true
    pipeline_abi_inject_fixed_array_copy_thin "$o" || true
    pipeline_abi_inject_slot_bytes_thin "$o" || true
    pipeline_abi_inject_field_load_sz_thin "$o" || true
    pipeline_abi_inject_unused_hints_thin "$o" || true
      pipeline_abi_inject_wpo_dump_thin "$o" || true
    pipeline_abi_inject_type_to_c_repr_thin "$o" || true
    pipeline_abi_inject_binop_block_peel_thin "$o" || true
    pipeline_abi_inject_param_ptr_slot_thin "$o" || true
    pipeline_abi_inject_fnptr_as_thin "$o" || true
    pipeline_abi_inject_asm_expr_thin "$o" || true
    pipeline_abi_inject_fnptr_array_esz_thin "$o" || true
    pipeline_abi_inject_assign_thin "$o" || true
    return 0
  fi

  # Cold full seed (ensure_one twin) with XLANG_USE_X_PIPELINE — last resort only.
  # wave176: cold full seed currently fails type conflicts (void* vs struct*
  # dual decls in from_x). If hybrid failed but OUT still exists, keep it.
  # PLATFORM: SHARED freestanding product / sat rebuild safety.
  # Hard-fail when OUT is still missing — never return 0 with no leaf (L4 pure-ld).
  cold_flags="$(pipeline_abi_prefer_cflags)"
  # shellcheck disable=SC2086
  if [ -s "$o" ]; then
    # Cap residual (10.3.2): never "keep" an incomplete Darwin libtool archive.
    if pipeline_abi_o_is_libtool_archive "$o"; then
      local keep_sz
      keep_sz=$(wc -c <"$o" | tr -d ' ')
      if [ -z "$keep_sz" ] || [ "$keep_sz" -lt 1000000 ]; then
        log "pipeline_abi discard incomplete libtool archive $o (${keep_sz:-0}B); try cold seed (10.3.2)"
        rm -f "$o"
      else
        log "pipeline_abi keep Darwin libtool archive $o (${keep_sz}B ≥1MiB)"
        pipeline_abi_inject_reent_deep_copy_thin "$o" || true
        pipeline_abi_inject_fixed_array_copy_thin "$o" || true
        pipeline_abi_inject_slot_bytes_thin "$o" || true
        pipeline_abi_inject_field_load_sz_thin "$o" || true
        pipeline_abi_inject_unused_hints_thin "$o" || true
          pipeline_abi_inject_wpo_dump_thin "$o" || true
        pipeline_abi_inject_type_to_c_repr_thin "$o" || true
        pipeline_abi_inject_binop_block_peel_thin "$o" || true
        pipeline_abi_inject_param_ptr_slot_thin "$o" || true
        pipeline_abi_inject_fnptr_as_thin "$o" || true
        pipeline_abi_inject_asm_expr_thin "$o" || true
        pipeline_abi_inject_fnptr_array_esz_thin "$o" || true
        pipeline_abi_inject_assign_thin "$o" || true
        return 0
      fi
    else
      log "pipeline_abi skip cold wipe; keep existing $o (wave176; cold seed type conflicts)"
      pipeline_abi_inject_reent_deep_copy_thin "$o" || true
      pipeline_abi_inject_fixed_array_copy_thin "$o" || true
      pipeline_abi_inject_slot_bytes_thin "$o" || true
      pipeline_abi_inject_field_load_sz_thin "$o" || true
      pipeline_abi_inject_unused_hints_thin "$o" || true
        pipeline_abi_inject_wpo_dump_thin "$o" || true
      pipeline_abi_inject_type_to_c_repr_thin "$o" || true
      pipeline_abi_inject_binop_block_peel_thin "$o" || true
      pipeline_abi_inject_param_ptr_slot_thin "$o" || true
      pipeline_abi_inject_fnptr_as_thin "$o" || true
      pipeline_abi_inject_asm_expr_thin "$o" || true
      pipeline_abi_inject_fnptr_array_esz_thin "$o" || true
      pipeline_abi_inject_assign_thin "$o" || true
      return 0
    fi
  fi
  if ! ensure_one "$o" "$seed" $cold_flags; then
    echo "ensure_host_cc_seed_o: pipeline_abi cold seed failed and no hybrid $o" >&2
    echo "  need: pin egg (./xbuild bootstrap-driver-seed installs select_bootstrap)" >&2
    return 1
  fi
  if [ ! -s "$o" ]; then
    echo "ensure_host_cc_seed_o: pipeline_abi ensure finished without $o" >&2
    return 1
  fi
  pipeline_abi_inject_reent_deep_copy_thin "$o" || true
  pipeline_abi_inject_fixed_array_copy_thin "$o" || true
  pipeline_abi_inject_slot_bytes_thin "$o" || true
  pipeline_abi_inject_field_load_sz_thin "$o" || true
  pipeline_abi_inject_unused_hints_thin "$o" || true
      pipeline_abi_inject_wpo_dump_thin "$o" || true
  pipeline_abi_inject_type_to_c_repr_thin "$o" || true
  pipeline_abi_inject_binop_block_peel_thin "$o" || true
  pipeline_abi_inject_param_ptr_slot_thin "$o" || true
  pipeline_abi_inject_fnptr_as_thin "$o" || true
  pipeline_abi_inject_asm_expr_thin "$o" || true
  pipeline_abi_inject_fnptr_array_esz_thin "$o" || true
  pipeline_abi_inject_assign_thin "$o" || true
  return 0
}

# Generic first-wins thin inject into src/runtime_pipeline_abi.o (PLATFORM: SHARED).
# Thin .x body MUST match the same-named export in runtime_pipeline_abi.x;
# regenerate the thin when that function changes. First-wins ld -r: thin.o then pabi.o.
# G.7: one helper; 4.2.7 nested SLICE esz + dest-ARRAY [K][N]T memcpy both reuse it.
# True if PATH is a Darwin libtool/ar archive (magic "!<arch>"), not MH_OBJECT.
# PLATFORM: MACOS — prefer/inject ld -r fallback uses libtool -static; a later
# inject into that archive can leave a tiny incomplete .o (Cap LEA missing).
# LINUX ELF never matches. G.7 single gate for pabi recover / inject refuse.
pipeline_abi_o_is_libtool_archive() {
  local p="$1"
  local mag
  [ -f "$p" ] || return 1
  # PLATFORM: MACOS — magic "!<arch>" (7 bytes). Avoid tr on binary (Darwin LC_CTYPE).
  mag="$(head -c 7 "$p" 2>/dev/null || true)"
  [ "$mag" = '!<arch>' ]
}

# True when this host's product -E binary is a leftover Windows PE that cannot
# compile tip pipeline_abi sources (mega hang; thin -E fail).
# PLATFORM: WINDOWS — 2026-07-31 leftover PE is present for Track L / can_run
# so the "no xlang binary" skip does not fire. POSIX gold xlang_asm CAN -E.
# G.7: one predicate; prefer FORCE hybrid + thin inject both consult it
# BEFORE launching leftover PE -E (post-fail keep is not enough: mega hangs).
pipeline_abi_windows_leftover_pe_cannot_e() {
  windows_leftover_pe_cannot_e
}

# Return 0 if every global text symbol in THIN is already a global T in BASE.
# PLATFORM: SHARED nm (Darwin leading underscore accepted as-is).
pipeline_abi_thin_already_defined() {
  local base="$1"
  local thin="$2"
  local sym
  local thin_syms
  [ -f "$base" ] && [ -f "$thin" ] || return 1
  thin_syms="$(nm -gU "$thin" 2>/dev/null | awk '/ [Tt] / { print $NF }')"
  [ -n "$thin_syms" ] || return 1
  while IFS= read -r sym; do
    [ -n "$sym" ] || continue
    nm -gU "$base" 2>/dev/null | awk -v s="$sym" '
      ($2 == "T" || $2 == "t") && $NF == s { found=1 }
      END { exit !found }
    ' || return 1
  done <<EOF
$thin_syms
EOF
  return 0
}

pipeline_abi_inject_thin_leaf() {
  local o="$1"
  local thin_x="$2"
  local tag="$3"
  local xlang_bin=""
  local gen_c thin_o base_o
  if [ ! -s "$o" ] || [ ! -f "$thin_x" ]; then
    return 0
  fi
  # Cap residual (10.3.2 Darwin): do not inject into a libtool archive named .o.
  # Caller (prefer) must rebuild MH_OBJECT / ELF first. PLATFORM: MACOS.
  if pipeline_abi_o_is_libtool_archive "$o"; then
    log "pipeline_abi ${tag} inject skip: $o is libtool archive (rebuild pabi first)"
    return 1
  fi
  # PLATFORM: WINDOWS — leftover PE cannot -E tip thins (fail or hang).
  # Do not launch; keep existing hybrid $o (same as no-binary skip).
  # POSIX (Linux gold / Darwin): continue with product -E.
  if pipeline_abi_windows_leftover_pe_cannot_e; then
    log "pipeline_abi ${tag} inject skip: Windows leftover PE cannot -E tip thins; keep $o"
    return 0
  fi
  if [ -x ./xlang_asm ]; then
    xlang_bin=./xlang_asm
  elif [ -x ./xlang ]; then
    xlang_bin=./xlang
  elif [ -x ./xlang-c ]; then
    xlang_bin=./xlang-c
  else
    log "pipeline_abi ${tag} inject skip: no xlang binary"
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_thin.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_thin.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_thin_base.XXXXXX.o")"
  if ! "$xlang_bin" -E "$thin_x" >"$gen_c" 2>/dev/null || [ ! -s "$gen_c" ]; then
    log "pipeline_abi ${tag} inject: -E failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi ${tag} inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # PLATFORM: MACOS — g05 re-injects after bootstrap already overlaid this leaf.
  # Second strong overlay cannot Darwin ld -r (two LC_SEGMENT / two T); libtool
  # -static then keeps both members. Final -force_load of a ≤2-member archive
  # pulls both → duplicate `_glue_slice_let_reent_deep_copy_after_dual_gp_elf_c`
  # (L4 @7f2754d80). Skip when thin's global T symbols are already T in $o.
  if pipeline_abi_thin_already_defined "$o" "$thin_o"; then
    log "pipeline_abi ${tag} inject skip: already defined in $o"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$o" "$base_o"
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    # PLATFORM: MACOS — ld -r may fall back to libtool -static. Accept only if
    # the archive still contains the full base (≥ base size). Tiny incomplete
    # archives (Cap residual 10.3.2: thin+rest_try leftover) are refused.
    if pipeline_abi_o_is_libtool_archive "$o"; then
      local base_sz out_sz
      base_sz=$(wc -c <"$base_o" | tr -d ' ')
      out_sz=$(wc -c <"$o" | tr -d ' ')
      if [ -z "$base_sz" ] || [ -z "$out_sz" ] || [ "$out_sz" -lt "$base_sz" ]; then
        cp -f "$base_o" "$o"
        log "pipeline_abi ${tag} inject: incomplete libtool archive; restored base"
        rm -f "$gen_c" "$thin_o" "$base_o"
        return 1
      fi
      log "pipeline_abi ${tag} inject OK (Darwin libtool archive ≥ base; force_load)"
    else
      log "pipeline_abi ${tag} inject OK (first-wins over weak pure)"
    fi
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi ${tag} inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

# 4.2.7 nested TYPE_SLICE reent deep-copy inject.
pipeline_abi_inject_reent_deep_copy_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_reent_deep_copy_thin.x" "reent-thin"
}

# dest-ARRAY [K][N]T memcpy / return Path B0 row stride inject.
pipeline_abi_inject_fixed_array_copy_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_fixed_array_copy_thin.x" "arrcopy-thin"
}

# NL-04: asm_local_slot_bytes dep-max (import PageMmapHeap thin lit vs dep 24B).
# G.7: thin body matches runtime_pipeline_abi.x; first-wins over weak pure.
# Keeps thin-first hybrid (seed-first dropped Ubuntu driver_diag).
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_slot_bytes_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_slot_bytes_thin.x" "slotbytes-thin"
}

# CORE-016: FIELD_ACCESS load width — prefer typeck mono scalar stamp over
# generic-layout free TYPE_NAMED T/U (which glue maps to 8 → ldr x0 garbage).
# G.7: thin body matches runtime_pipeline_abi.x pipeline_expr_field_access_load_byte_sz.
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_field_load_sz_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_field_load_sz_thin.x" "fieldloadsz-thin"
}

# L6 unused-binding hints (XLANG_UNUSED_HINT=1). G.7: thin body matches
# runtime_pipeline_abi.x pipeline_typeck_unused_binding_hints.
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_unused_hints_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_unused_hints_thin.x" "unusedhints-thin"
}

# Cap-fn-ptr (10.3.2 slice0): EXPR_AS same-module #[no_mangle] fn as *u8 → LEA.
# G.7: thin body matches pipeline_asm_emit_as_elf_impl / _c in mega .x.
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_fnptr_as_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_fnptr_as_thin.x" "fnptr-as-thin"
}

# Stage10 10.2.1: EXPR_ASM emit_expr_elf_rec override (ko==60 → try_emit).
# G.7: thin body matches seed/mega emit_expr_elf_rec asm branch.
pipeline_abi_inject_asm_expr_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_asm_expr_thin.x" "asm-expr-thin"
}

# 10.3.1 slice13: TYPE_FN array-lit esz / fixed-array temp bytes.
# Seed rest holds strong glue_array_lit_force_esz_from_elem_type_c /
# glue_fixed_array_temp_bytes — weaken then first-wins thin (no mega -E).
# G.7: thin body matches runtime_pipeline_abi.x. PLATFORM: SHARED shell ·
# LINUX gold + MACOS.
pipeline_abi_inject_fnptr_array_esz_thin() {
  local o="$1"
  local thin_x="src/runtime_pipeline_abi_fnptr_array_esz_thin.x"
  local xlang_bin=""
  local gen_c thin_o base_o oc
  if [ ! -s "$o" ] || [ ! -f "$thin_x" ]; then
    return 0
  fi
  if pipeline_abi_o_is_libtool_archive "$o"; then
    log "pipeline_abi fnptr-arr-esz inject skip: $o is libtool archive"
    return 1
  fi
  # PLATFORM: WINDOWS — leftover PE cannot -E tip thins; keep existing hybrid.
  if pipeline_abi_windows_leftover_pe_cannot_e; then
    log "pipeline_abi fnptr-arr-esz inject skip: Windows leftover PE cannot -E; keep $o"
    return 0
  fi
  if [ -x ./xlang_asm ]; then
    xlang_bin=./xlang_asm
  elif [ -x ./xlang ]; then
    xlang_bin=./xlang
  elif [ -x ./xlang-c ]; then
    xlang_bin=./xlang-c
  else
    log "pipeline_abi fnptr-arr-esz inject skip: no xlang binary"
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_fnarr.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_fnarr.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_fnarr_base.XXXXXX.o")"
  if ! "$xlang_bin" -E "$thin_x" >"$gen_c" 2>/dev/null || [ ! -s "$gen_c" ]; then
    log "pipeline_abi fnptr-arr-esz inject: -E failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi fnptr-arr-esz inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  cp -f "$o" "$base_o"
  oc=""
  if [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
    oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
  elif command -v llvm-objcopy >/dev/null 2>&1; then
    oc=llvm-objcopy
  elif command -v objcopy >/dev/null 2>&1; then
    oc=objcopy
  fi
  if [ -n "$oc" ]; then
    # Seed rest holds strong defs; weaken so thin first-wins. ELF + Mach-O.
    "$oc" --weaken-symbol=glue_array_lit_force_esz_from_elem_type_c "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=_glue_array_lit_force_esz_from_elem_type_c "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=glue_fixed_array_temp_bytes "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=_glue_fixed_array_temp_bytes "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=pipeline_asm_array_lit_elem_byte_sz_c "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=_pipeline_asm_array_lit_elem_byte_sz_c "$base_o" 2>/dev/null || true
  fi
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    log "pipeline_abi fnptr-arr-esz inject OK (first-wins over weakened leftover)"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi fnptr-arr-esz inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

# WPO_DUMP_CALLGRAPH (XLANG_WPO_DUMP_CALLGRAPH). G.7: thin body matches
# runtime_pipeline_abi.x pipeline_typeck_wpo_dump_callgraph.
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_wpo_dump_thin() {
  pipeline_abi_inject_thin_leaf "$1" "src/runtime_pipeline_abi_wpo_dump_thin.x" "wpodump-thin"
}


# *T formal home vs by-value NAMED self (w189 fill_param_slots walk).
# Mega leftover may hold a strong/weak glue_local_var_slot_needs_ptr_load_elf_c
# (hybrid thin+rest). Weaken then first-wins ld -r of the small .x thin so
# product need not full mega -E (Darwin 22-40GB RSS). G.7: thin body matches
# runtime_pipeline_abi.x. PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_param_ptr_slot_thin() {
  local o="$1"
  local thin_x="src/runtime_pipeline_abi_param_ptr_slot_thin.x"
  local xlang_bin=""
  local gen_c thin_o base_o oc
  if [ ! -s "$o" ] || [ ! -f "$thin_x" ]; then
    return 0
  fi
  # PLATFORM: WINDOWS — leftover PE cannot -E tip thins; keep existing hybrid.
  if pipeline_abi_windows_leftover_pe_cannot_e; then
    log "pipeline_abi ptrslot-thin inject skip: Windows leftover PE cannot -E; keep $o"
    return 0
  fi
  if [ -x ./xlang_asm ]; then
    xlang_bin=./xlang_asm
  elif [ -x ./xlang ]; then
    xlang_bin=./xlang
  elif [ -x ./xlang-c ]; then
    xlang_bin=./xlang-c
  else
    log "pipeline_abi ptrslot-thin inject skip: no xlang binary"
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_ptrslot.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_ptrslot.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_ptrslot_base.XXXXXX.o")"
  if ! "$xlang_bin" -E "$thin_x" >"$gen_c" 2>/dev/null || [ ! -s "$gen_c" ]; then
    log "pipeline_abi ptrslot-thin inject: -E failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! $CC $BASE_CFLAGS -I. -Iinclude -Isrc -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi ptrslot-thin inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  if pipeline_abi_thin_already_defined "$o" "$thin_o"; then
    log "pipeline_abi ptrslot-thin inject skip: already defined in $o"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$o" "$base_o"
  oc=""
  if [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
    oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
  elif command -v llvm-objcopy >/dev/null 2>&1; then
    oc=llvm-objcopy
  elif command -v objcopy >/dev/null 2>&1; then
    oc=objcopy
  fi
  if [ -n "$oc" ]; then
    # Try both ELF (no prefix) and Mach-O (_ prefix). Do not short-circuit:
    # GNU objcopy may exit 0 on a missing Darwin-prefixed name.
    "$oc" --weaken-symbol=glue_local_var_slot_needs_ptr_load_elf_c "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=_glue_local_var_slot_needs_ptr_load_elf_c "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=w189_stack_off_is_emit_param_ptr_slot "$base_o" 2>/dev/null || true
    "$oc" --weaken-symbol=_w189_stack_off_is_emit_param_ptr_slot "$base_o" 2>/dev/null || true
  fi
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    log "pipeline_abi ptrslot-thin inject OK (first-wins over weakened leftover)"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi ptrslot-thin inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

# host-C type_to_c_repr SLICE `*`→`_p` sanitizer. Product hybrid keeps this
# symbol in the mega leftover (seed body is #ifndef FROM_X). inject-only
# skips full mega -E, so extract the marked seed body, weaken the existing
# strong symbol, first-wins ld -r. G.7: one C body (markers in from_x.c).
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_type_to_c_repr_thin() {
  local o="$1"
  local seed="seeds/runtime_pipeline_abi.from_x.c"
  local xlang_bin=""
  local gen_c thin_o base_o oc
  if [ ! -s "$o" ] || [ ! -f "$seed" ]; then
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_ttc.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_ttc.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_ttc_base.XXXXXX.o")"
  if ! awk '
    /XLANG_PABI_TYPE_TO_C_REPR_THIN_BEGIN/ {p=1; next}
    /XLANG_PABI_TYPE_TO_C_REPR_THIN_END/ {p=0; next}
    p {print}
  ' "$seed" >"$gen_c" || [ ! -s "$gen_c" ]; then
    log "pipeline_abi ttc-thin inject: extract failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! ${CC:-cc} ${BASE_CFLAGS:--Wall -I. -Iinclude -Isrc} -Wno-unused -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi ttc-thin inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  cp -f "$o" "$base_o"
  oc=""
  if [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
    oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
  elif command -v llvm-objcopy >/dev/null 2>&1; then
    oc=llvm-objcopy
  elif command -v objcopy >/dev/null 2>&1; then
    oc=objcopy
  fi
  if [ -n "$oc" ]; then
    "$oc" --weaken-symbol=_pipeline_codegen_type_to_c_repr "$base_o" 2>/dev/null \
      || "$oc" --weaken-symbol=pipeline_codegen_type_to_c_repr "$base_o" 2>/dev/null \
      || true
  fi
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    log "pipeline_abi ttc-thin inject OK (first-wins over weakened leftover)"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi ttc-thin inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

# binop dual-slot peel of transparent EXPR_BLOCK (`unsafe { e }`).
# Product hybrid keeps load_operand in the leftover (seed body is
# #ifndef FROM_X). inject-only skips full mega -E, so extract the
# marked seed bodies, weaken the existing strong symbols, first-wins
# ld -r. G.7: one C body (markers in from_x.c).
# PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_binop_block_peel_thin() {
  local o="$1"
  local seed="seeds/runtime_pipeline_abi.from_x.c"
  local gen_c thin_o base_o oc
  if [ ! -s "$o" ] || [ ! -f "$seed" ]; then
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_blkpeel.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_blkpeel.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_blkpeel_base.XXXXXX.o")"
  if ! awk '
    /XLANG_PABI_BINOP_BLOCK_PEEL_THIN_BEGIN/ {p=1; next}
    /XLANG_PABI_BINOP_BLOCK_PEEL_THIN_END/ {p=0; next}
    p {print}
  ' "$seed" >"$gen_c" || [ ! -s "$gen_c" ]; then
    log "pipeline_abi blkpeel-thin inject: extract failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! ${CC:-cc} ${BASE_CFLAGS:--Wall -I. -Iinclude -Isrc} -Wno-unused -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi blkpeel-thin inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  cp -f "$o" "$base_o"
  oc=""
  if [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
    oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
  elif command -v llvm-objcopy >/dev/null 2>&1; then
    oc=llvm-objcopy
  elif command -v objcopy >/dev/null 2>&1; then
    oc=objcopy
  fi
  if [ -n "$oc" ]; then
    for s in \
      glue_try_binop_load_operand_elf_c \
      glue_binop_operand_index_addr_clobbers_rbx_elf_c \
      glue_binop_operand_load_to_rbx_clobbers_rax_elf_c \
      glue_expr_emit_may_clobber_rbx_elf_c \
      glue_expr_block_transparent_value_ref_at
    do
      "$oc" --weaken-symbol="_$s" "$base_o" 2>/dev/null \
        || "$oc" --weaken-symbol="$s" "$base_o" 2>/dev/null \
        || true
    done
  fi
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    log "pipeline_abi blkpeel-thin inject OK (first-wins over weakened leftover)"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi blkpeel-thin inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

# wave142 dest-in-rbx assign thin inject.
# Seed rest holds strong assign cluster in leftover; weaken then first-wins.
# G.7: one C body (markers in from_x.c). PLATFORM: SHARED shell · LINUX gold + MACOS.
pipeline_abi_inject_assign_thin() {
  local o="$1"
  local seed="seeds/runtime_pipeline_abi.from_x.c"
  local gen_c thin_o base_o oc
  if [ ! -s "$o" ] || [ ! -f "$seed" ]; then
    return 0
  fi
  gen_c="$(mktemp "${TMPDIR:-/tmp}/pabi_asg.XXXXXX.c")"
  thin_o="$(mktemp "${TMPDIR:-/tmp}/pabi_asg.XXXXXX.o")"
  base_o="$(mktemp "${TMPDIR:-/tmp}/pabi_asg_base.XXXXXX.o")"
  if ! awk '
    /XLANG_PABI_ASSIGN_THIN_BEGIN/ {p=1; next}
    /XLANG_PABI_ASSIGN_THIN_END/ {p=0; next}
    p {print}
  ' "$seed" >"$gen_c" || [ ! -s "$gen_c" ]; then
    log "pipeline_abi asg-thin inject: extract failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  # shellcheck disable=SC2086
  if ! ${CC:-cc} ${BASE_CFLAGS:--Wall -I. -Iinclude -Isrc} -Wno-implicit-function-declaration -Wno-int-conversion -Wno-unused -c -o "$thin_o" "$gen_c" 2>/dev/null; then
    log "pipeline_abi asg-thin inject: cc thin failed"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 1
  fi
  cp -f "$o" "$base_o"
  oc=""
  if [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
    oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
  elif command -v llvm-objcopy >/dev/null 2>&1; then
    oc=llvm-objcopy
  elif command -v objcopy >/dev/null 2>&1; then
    oc=objcopy
  fi
  if [ -n "$oc" ]; then
    for s in \
      glue_assign_lhs_f32_type_ref_elf_c \
      glue_emit_assign_rhs_elf_c \
      glue_emit_assign_rhs_to_rax_elf_c \
      pipeline_asm_emit_assign_elf_c \
      glue_field_assign_pair_base_ref_c \
      glue_body_expr_stmt_at_c
    do
      "$oc" --weaken-symbol="_$s" "$base_o" 2>/dev/null \
        || "$oc" --weaken-symbol="$s" "$base_o" 2>/dev/null \
        || true
    done
  fi
  if pure_ld_partial_merge "$o" "$thin_o" "$base_o" 2>/dev/null; then
    log "pipeline_abi asg-thin inject OK (first-wins over weakened leftover)"
    rm -f "$gen_c" "$thin_o" "$base_o"
    return 0
  fi
  cp -f "$base_o" "$o"
  log "pipeline_abi asg-thin inject: merge failed; restored base"
  rm -f "$gen_c" "$thin_o" "$base_o"
  return 1
}

try_ensure_pipeline_abi_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-pipeline-abi-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ "$o" != "src/runtime_pipeline_abi.o" ]; then
    return 3
  fi
  ensure_pipeline_abi_prefer_one "$o" || return 1
  return 0
}

# ---------------------------------------------------------------------------
# wave767: try-ldpc-prefer OUT — g05 lsp_diag_pipeline_ctx product PREFER.
#
# Single leaf: src/lsp/lsp_diag_pipeline_ctx.o (R1_MISC_BASENAME; cold twin =
# ensure_one plain seed).
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   thin .x → .o via rt_prefer_try_x_to_o with G05_X_O_WEAK=1 (alias weak vs
#     bootstrap/filtered strong symbols; G-02f-331)
#   rest = seeds/lsp_diag_pipeline_ctx.from_x.c under
#     -DXLANG_L2_LSP_CTX_THIN_FROM_X
#   merge: $CC -r -nostdlib thin + rest → OUT
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold plain seed.
# Stage 12.0.5 pure-asm hybrid (opt-in PREFER_ASM_O; not product-default):
#   G05_X_O_WEAK=1 still required vs lsp_diag_x strong defs of
#   lsp_diag_{hover,definition,references}_at. pure_asm_x_to_o now applies
#   objcopy --weaken polish after freestanding emit (G.7 有则补全; nmedit
#   cannot weak pure-asm objects). Missing objcopy → fall through -E+$CC.
# Callers: g05_ensure (wave767) · Makefile src/lsp/lsp_diag_pipeline_ctx.o.
# Exit codes:
#   0 — OUT is lsp_diag_pipeline_ctx.o; prefer or cold body produced OUT
#   3 — OUT is not src/lsp/lsp_diag_pipeline_ctx.o
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# G.7: reuses rt_prefer_try_x_to_o harness (有则补全).
# Residual after: ~~target_cpu~~(wave768) · other L2 · pure-ld · physical delete.
# ---------------------------------------------------------------------------

ensure_ldpc_prefer_one() {
  local o="$1"
  local seed="seeds/lsp_diag_pipeline_ctx.from_x.c"
  local x_src="src/lsp/lsp_diag_pipeline_ctx.x"
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-ldpc-prefer: missing seed $seed" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (ldpc-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  if [ "$prefer" = "1" ] && [ -f "$x_src" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/ldpc_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/ldpc_rest.XXXXXX")"
    # thin 别名 weak，避免与 bootstrap/filtered 强符号冲突（对齐 strict_glue / g05）
    # shellcheck disable=SC2086
    if G05_X_O_WEAK=1 rt_prefer_try_x_to_o "$x_src" "$thin_o" \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_L2_LSP_CTX_THIN_FROM_X \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer thin+rest $o <- $x_src + seed-rest (try-ldpc-prefer)"
      done=1
    else
      log "ldpc hybrid failed; fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_ldpc_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-ldpc-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ "$o" != "src/lsp/lsp_diag_pipeline_ctx.o" ]; then
    return 3
  fi
  ensure_ldpc_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave768: try-target-cpu-prefer OUT — g05 target_cpu product PREFER (single body).
#
# Single leaf: src/driver/target_cpu.o (R1_SEED_MAP; cold twin = ensure_one pure
# seed seeds/target_cpu_pure.from_x.c).
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   flags.x (pending/tolower/eq5/eq6) → .o via rt_prefer_try_x_to_o
#     (G.7 有则补全: same harness as pipeline_abi/ldpc/rt; no WEAK — historic
#     g05 flags helpers are strong and rest omits them under FROM_X)
#   rest = seeds/target_cpu_pure.from_x.c under -DXLANG_L2_TARGET_CPU_FLAGS_FROM_X
#   merge: $CC -r -nostdlib flags + rest → OUT (g05 historic)
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold pure seed (full TU).
# Callers: g05_ensure (wave768) · Makefile src/driver/target_cpu.o (unified).
# Exit codes:
#   0 — OUT is target_cpu.o; prefer or cold body produced OUT
#   3 — OUT is not src/driver/target_cpu.o
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# G.7: reuses rt_prefer_try_x_to_o harness (有则补全; no second -E prologue).
# Residual after: other L2 hybrid · pure-ld · physical delete.
# ---------------------------------------------------------------------------

ensure_target_cpu_prefer_one() {
  local o="$1"
  local seed="seeds/target_cpu_pure.from_x.c"
  local flags_x="src/driver/target_cpu_flags.x"
  local pure_x="src/driver/target_cpu_pure.x"
  local hdr="include/target_cpu.h"
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-target-cpu-prefer: missing seed $seed" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$flags_x" ] && [ "$flags_x" -nt "$o" ]; then
      stale=1
    fi
    if [ -f "$pure_x" ] && [ "$pure_x" -nt "$o" ]; then
      stale=1
    fi
    if [ -f "$hdr" ] && [ "$hdr" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (target-cpu-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # PREFER flags.x + seed-rest only when PREFER=1 (Darwin cold-chain safety twin).
  if [ "$prefer" = "1" ] && [ -f "$flags_x" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/tcpu_flags.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/tcpu_rest.XXXXXX")"
    # shellcheck disable=SC2086
    if rt_prefer_try_x_to_o "$flags_x" "$thin_o" \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -DXLANG_L2_TARGET_CPU_FLAGS_FROM_X \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer thin+rest $o <- $flags_x + seed-rest (try-target-cpu-prefer)"
      done=1
    else
      log "target_cpu hybrid failed; fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full pure seed (ensure_one twin / PREFER=0).
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_target_cpu_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-target-cpu-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ "$o" != "src/driver/target_cpu.o" ]; then
    return 3
  fi
  ensure_target_cpu_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave769: try-l2-asm-prefer OUT — g05 L2 asm three thin+rest product PREFER.
#
# Table-driven single body (G.7 有则补全; no second -E prologue; reuses
# rt_prefer_try_x_to_o). Leaves (historic g05 G-02f-439/441/442 dual hybrid):
#   src/asm/user_asm_seed_bridge.o
#     x=src/asm/user_asm_seed_bridge.x
#     seed=seeds/user_asm_seed_bridge.from_x.c
#     rest -D=XLANG_USER_ASM_SEED_BRIDGE_FROM_X
#     rest -I=default
#   src/asm/backend_x86_64_enc_c.o
#     x=src/asm/backend_x86_64_enc_c.x
#     seed=seeds/backend_x86_64_enc_c.from_x.c
#     rest -D=XLANG_BACKEND_X86_64_ENC_C_FROM_X
#     rest -I=default
#   src/asm/asm_backend_compat_stubs.o
#     x=src/asm/asm_backend_compat_stubs.x
#     seed=seeds/asm_backend_compat_stubs.from_x.c
#     rest -D=XLANG_ASM_BACKEND_COMPAT_STUBS_FROM_X
#     rest -I=default + -Isrc/asm -Isrc/lexer
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   thin .x → .o via rt_prefer_try_x_to_o (no WEAK — historic g05 strong thin)
#   rest = seed under FROM_X -D (+ optional -I)
#   merge: $CC -r -nostdlib thin + rest → OUT
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold plain seed.
# Callers: g05_ensure (wave769) · Makefile three leaves (was ensure one cold).
# Exit codes:
#   0 — OUT is a table member; prefer or cold body produced OUT
#   3 — OUT is not in the L2 asm prefer table
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# Residual after: ~~async three~~ (wave770) · other L2 (seed_link_compat /
#   strict_glue / fmt_check / lsp_diag…) · pure-ld · physical delete.
# ---------------------------------------------------------------------------

# Resolve OUT → seed|x_src|from_x_def|rest_extra_incs (pipe-separated).
# Empty string means non-member.
l2_asm_prefer_spec_for_out() {
  case "$1" in
    src/asm/user_asm_seed_bridge.o)
      printf '%s' "seeds/user_asm_seed_bridge.from_x.c|src/asm/user_asm_seed_bridge.x|XLANG_USER_ASM_SEED_BRIDGE_FROM_X|"
      ;;
    src/asm/backend_x86_64_enc_c.o)
      printf '%s' "seeds/backend_x86_64_enc_c.from_x.c|src/asm/backend_x86_64_enc_c.x|XLANG_BACKEND_X86_64_ENC_C_FROM_X|"
      ;;
    src/asm/asm_backend_compat_stubs.o)
      printf '%s' "seeds/asm_backend_compat_stubs.from_x.c|src/asm/asm_backend_compat_stubs.x|XLANG_ASM_BACKEND_COMPAT_STUBS_FROM_X|-Isrc/asm -Isrc/lexer"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

ensure_l2_asm_prefer_one() {
  local o="$1"
  local spec seed x_src from_x_def rest_extra rest
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o

  spec="$(l2_asm_prefer_spec_for_out "$o")"
  if [ -z "$spec" ]; then
    return 3
  fi
  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  rest="${rest#*|}"
  from_x_def="${rest%%|*}"
  rest_extra="${rest#*|}"

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-l2-asm-prefer: missing seed $seed for $o" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (l2-asm-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # PREFER thin.x + seed-rest only when PREFER=1 (Darwin cold-chain safety twin).
  if [ "$prefer" = "1" ] && [ -f "$x_src" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/l2asm_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/l2asm_rest.XXXXXX")"
    # shellcheck disable=SC2086
    if rt_prefer_try_x_to_o "$x_src" "$thin_o" \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc $rest_extra -D"$from_x_def" \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer thin+rest $o <- $x_src + seed-rest (try-l2-asm-prefer)"
      done=1
    else
      log "l2-asm hybrid failed for $o; fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full seed (ensure_one twin / PREFER=0).
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_l2_asm_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-l2-asm-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(l2_asm_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_l2_asm_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave770: try-async-prefer OUT — g05 async three full.x+rest product PREFER.
#
# Table-driven single body (G.7 有则补全; no second -E prologue; reuses
# rt_prefer_try_x_to_o). Leaves (historic g05 R2 dual hybrid / glue unbundle):
#   src/async/async_liveness.o
#     x=src/async/async_liveness.x
#     seed=seeds/async_liveness.from_x.c
#     rest -D=XLANG_ASYNC_LIVENESS_FROM_X
#   src/async/async_cps_codegen.o
#     x=src/async/async_cps_codegen.x
#     seed=seeds/async_cps_codegen.from_x.c
#     rest -D=XLANG_ASYNC_CPS_CODEGEN_FROM_X
#   src/async/async_asm_pool.o
#     x=src/asm/async_asm_pool.x
#     seed=seeds/async_asm_pool.from_x.c
#     rest -D=XLANG_ASYNC_ASM_POOL_FROM_X
# When XLANG_G05_PREFER_X_O=1 and an xlang binary works:
#   full .x → .o via rt_prefer_try_x_to_o (no WEAK — historic g05 strong thin)
#   rest = seed under FROM_X -D (slice_marker only)
#   merge: $CC -r -nostdlib thin + rest → OUT
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold plain seed.
# Stage 12.0.5 pure-asm hybrid (opt-in PREFER_ASM_O; not product-default):
#   pure_asm standalone 3/3 (div0 FAIL_ABI residual closed) · FORCE try-async-prefer
#   pure-asm thin+rest · soft g05 pure-ld · matrix 5/5 · restore -E 5/5
#   dual-end @ tip 190ab4eb3 (mac + Ubuntu gold). No WEAK polish needed.
# Callers: g05_ensure (wave770) · Makefile three leaves (was dual hybrid).
# Exit codes:
#   0 — OUT is a table member; prefer or cold body produced OUT
#   3 — OUT is not in the async prefer table
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# Residual after: other L2 (seed_link_compat / strict_glue / fmt_check /
#   lsp_diag…) · pure-ld · physical delete.
# ---------------------------------------------------------------------------

# Resolve OUT → seed|x_src|from_x_def (pipe-separated). Empty = non-member.
async_prefer_spec_for_out() {
  case "$1" in
    src/async/async_liveness.o)
      printf '%s' "seeds/async_liveness.from_x.c|src/async/async_liveness.x|XLANG_ASYNC_LIVENESS_FROM_X"
      ;;
    src/async/async_cps_codegen.o)
      printf '%s' "seeds/async_cps_codegen.from_x.c|src/async/async_cps_codegen.x|XLANG_ASYNC_CPS_CODEGEN_FROM_X"
      ;;
    src/async/async_asm_pool.o)
      printf '%s' "seeds/async_asm_pool.from_x.c|src/asm/async_asm_pool.x|XLANG_ASYNC_ASM_POOL_FROM_X"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

ensure_async_prefer_one() {
  local o="$1"
  local spec seed x_src from_x_def rest
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o

  spec="$(async_prefer_spec_for_out "$o")"
  if [ -z "$spec" ]; then
    return 3
  fi
  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  from_x_def="${rest#*|}"

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-async-prefer: missing seed $seed for $o" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (async-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # PREFER full .x + seed-rest only when PREFER=1 (Darwin cold-chain safety twin).
  if [ "$prefer" = "1" ] && [ -f "$x_src" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/async_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/async_rest.XXXXXX")"
    # shellcheck disable=SC2086
    if rt_prefer_try_x_to_o "$x_src" "$thin_o" \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc -D"$from_x_def" \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer full.x+rest $o <- $x_src + seed-rest (try-async-prefer)"
      done=1
    else
      log "async hybrid failed for $o; fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full seed (ensure_one twin / PREFER=0).
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_async_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-async-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(async_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_async_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave771 + wave775: try-other-l2-prefer OUT — other L2 thin+rest PREFER table.
#
# Table-driven single body (G.7 有则补全; reuses rt_prefer_try_x_to_o).
# Leaves (historic dual hybrid; special prologues/weak sed):
#   src/seed_link_compat.o
#     x=src/seed_link_compat.x  seed=seeds/seed_link_compat.from_x.c
#     rest -D=XLANG_SEED_LINK_COMPAT_FROM_X + -Isrc/asm -Isrc/lexer
#     thin: G05_X_O_WEAK_FUNCS=6 lsp/typeck stubs (not WEAK=all)
#   src/runtime_driver_strict_glue_stubs.o
#     x=src/runtime_driver_strict_glue_thin.x
#     seed=seeds/runtime_driver_strict_glue_stubs.from_x.c
#     rest -D=XLANG_L2_STRICT_GLUE_THIN_FROM_X
#     thin: G05_X_O_WEAK=1; stale also on seeds/runtime_heap_user.from_x.c
#   src/driver/fmt_check_cmd_driver.o
#     x=src/driver/fmt_check_cmd_thin.x  seed=seeds/fmt_check_cmd.from_x.c
#     rest -D=XLANG_L2_FMT_CHECK_THIN_FROM_X -DXLANG_USE_X_PIPELINE
#     thin: G05_X_O_WEAK=1; cold seed also -DXLANG_USE_X_PIPELINE
#   src/driver/fmt_check_cmd.o  (wave775 · non-driver OBJS_CORE / PIPELINE_X)
#     same thin.x + seed; rest -D=XLANG_L2_FMT_CHECK_THIN_FROM_X only
#     leaf_kind=fmt_core — NO -DXLANG_USE_X_PIPELINE (runtime_x lacks USE_X_DRIVER;
#     fmt/check must stay on run_compiler_c stubs)
#   src/lsp/lsp_diag.o
#     x=src/asm/runtime_lsp_glue.x  seed=seeds/runtime_lsp_glue.from_x.c
#     rest -D=XLANG_L2_LSP_GLUE_FULL_FROM_X
#     thin: G05_X_O_WEAK=1
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold (fmt keeps USE_X_PIPELINE).
# Callers: g05_ensure (wave771 four) · Makefile five leaves (wave775 adds fmt.o).
# Exit codes:
#   0 — OUT is a table member; prefer or cold body produced OUT
#   3 — OUT is not in the other-L2 prefer table
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# Residual after: physical delete · panic PREFER (if any).
# ---------------------------------------------------------------------------

# Resolve OUT → seed|x_src|from_x_def|weak_mode|leaf_kind (pipe-separated).
# weak_mode: slc6 | weak
# leaf_kind: slc | strict | fmt | fmt_core | lsp  (rest/cold extras + extra stale)
other_l2_prefer_spec_for_out() {
  case "$1" in
    src/seed_link_compat.o)
      printf '%s' "seeds/seed_link_compat.from_x.c|src/seed_link_compat.x|XLANG_SEED_LINK_COMPAT_FROM_X|slc6|slc"
      ;;
    src/runtime_driver_strict_glue_stubs.o)
      printf '%s' "seeds/runtime_driver_strict_glue_stubs.from_x.c|src/runtime_driver_strict_glue_thin.x|XLANG_L2_STRICT_GLUE_THIN_FROM_X|weak|strict"
      ;;
    src/driver/fmt_check_cmd_driver.o)
      printf '%s' "seeds/fmt_check_cmd.from_x.c|src/driver/fmt_check_cmd_thin.x|XLANG_L2_FMT_CHECK_THIN_FROM_X|weak|fmt"
      ;;
    src/driver/fmt_check_cmd.o)
      # wave775: non-driver dual → same prefer body; no USE_X_PIPELINE.
      printf '%s' "seeds/fmt_check_cmd.from_x.c|src/driver/fmt_check_cmd_thin.x|XLANG_L2_FMT_CHECK_THIN_FROM_X|weak|fmt_core"
      ;;
    src/lsp/lsp_diag.o)
      printf '%s' "seeds/runtime_lsp_glue.from_x.c|src/asm/runtime_lsp_glue.x|XLANG_L2_LSP_GLUE_FULL_FROM_X|weak|lsp"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Historic G-02f-440: six weak stubs overridden by lsp_diag_x / pipeline_ctx.
# slc6 historic lsp/typeck stubs + std_sys_read_file_into (seed from_x.c already
# XLANG_WEAK; prefer thin .x must match). Without weak, strong dual vs driver_x
# monomorphized std.sys fails Darwin pure-ld (ld64 multidef obsolete).
# PLATFORM: SHARED — G.7 seed face weak; product mono in driver_x wins.
_OTHER_L2_SLC_WEAK_FUNCS="lsp_diag_lsp_build_diagnostics_response,lsp_diag_lsp_build_semantic_tokens_response,lsp_diag_hover_at,lsp_diag_references_at,lsp_diag_definition_at,typeck_lsp_main_impl,std_sys_read_file_into"

ensure_other_l2_prefer_one() {
  local o="$1"
  local spec seed x_src from_x_def weak_mode leaf_kind rest
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o
  local rest_extra="" cold_extra=()

  spec="$(other_l2_prefer_spec_for_out "$o")"
  if [ -z "$spec" ]; then
    return 3
  fi
  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  rest="${rest#*|}"
  from_x_def="${rest%%|*}"
  rest="${rest#*|}"
  weak_mode="${rest%%|*}"
  leaf_kind="${rest#*|}"

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-other-l2-prefer: missing seed $seed for $o" >&2
    return 1
  fi

  case "$leaf_kind" in
    slc) rest_extra="-Isrc/asm -Isrc/lexer" ;;
    fmt)
      # driver leaf: rest + cold need -DXLANG_USE_X_PIPELINE (product pipeline).
      rest_extra="-DXLANG_USE_X_PIPELINE"
      cold_extra=(-DXLANG_USE_X_PIPELINE)
      ;;
    fmt_core)
      # wave775 non-driver: OBJS_CORE / PIPELINE_X satellite — seed/thin only;
      # no USE_X_PIPELINE (avoids missing driver_run_compiler_full on runtime_x).
      ;;
    strict|lsp) ;;
    *)
      echo "ensure_host_cc_seed_o try-other-l2-prefer: unknown leaf_kind $leaf_kind" >&2
      return 1
      ;;
  esac

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # strict_glue seed #includes runtime_heap_user — refresh when heap seed newer.
    if [ "$leaf_kind" = "strict" ] \
      && [ -f seeds/runtime_heap_user.from_x.c ] \
      && [ seeds/runtime_heap_user.from_x.c -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (other-l2-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # PREFER thin/full .x + seed-rest only when PREFER=1 (Darwin cold-chain twin).
  if [ "$prefer" = "1" ] && [ -f "$x_src" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/ol2_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/ol2_rest.XXXXXX")"
    _thin_ok=0
    case "$weak_mode" in
      slc6)
        if G05_X_O_WEAK_FUNCS="$_OTHER_L2_SLC_WEAK_FUNCS" \
          rt_prefer_try_x_to_o "$x_src" "$thin_o"; then
          _thin_ok=1
        fi
        ;;
      weak)
        if G05_X_O_WEAK=1 rt_prefer_try_x_to_o "$x_src" "$thin_o"; then
          _thin_ok=1
        fi
        ;;
      *)
        if rt_prefer_try_x_to_o "$x_src" "$thin_o"; then
          _thin_ok=1
        fi
        ;;
    esac
    # shellcheck disable=SC2086
    if [ "$_thin_ok" = "1" ] \
      && $CC $BASE_CFLAGS -I. -Iinclude -Isrc $rest_extra -D"$from_x_def" \
           -c -o "$rest_o" "$seed" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer thin.x+rest $o <- $x_src + seed-rest (try-other-l2-prefer/$leaf_kind)"
      done=1
    else
      log "other-l2 hybrid failed for $o ($leaf_kind); fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full seed (ensure_one twin / PREFER=0). fmt keeps USE_X_PIPELINE.
  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed" "${cold_extra[@]+"${cold_extra[@]}"}"
    FORCE=0
  else
    ensure_one "$o" "$seed" "${cold_extra[@]+"${cold_extra[@]}"}"
  fi
  return 0
}

try_ensure_other_l2_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-other-l2-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(other_l2_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_other_l2_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave779: try-runtime-os-prefer OUT — B1 runtime_* OS/glue dual hybrid table.
#
# Table-driven single body (G.7 有则补全; reuses rt_prefer_try_x_to_o).
# 23 top-level runtime_*.o leaves that still had Makefile thin+rest PREFER dual
# (test_fn_invoke … process_os_glue). NOT physical delete — Makefile keeps
# thin-call edges + prereqs.
#
# Spec: seed|x_src|from_x_def|leaf_kind
# leaf_kind:
#   std          — default -I. -Iinclude -Isrc only
#   http         — rest/cold + -Iseeds/http; x under src/asm/http/
#   ed25519      — rest/cold + -Isrc/asm
#   tls          — rest/cold try homebrew mbedtls -I then plain (PLATFORM: MACOS
#                  homebrew path optional; LINUX often plain)
#   net_udp      — PLATFORM: LINUX only PREFER; non-Linux always cold seed
# Prefer fail / PREFER≠1 / no xlang → ensure_one cold (with leaf extras).
# Callers: Makefile 23 leaves (wave779).
# Exit codes:
#   0 — OUT is a table member; prefer or cold body produced OUT
#   3 — OUT is not in the runtime-os prefer table
#   1 — cold seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# Residual after: B2–B5 · physical delete · R5.
# ---------------------------------------------------------------------------

# Resolve OUT → seed|x_src|from_x_def|leaf_kind (pipe-separated).
runtime_os_prefer_spec_for_out() {
  case "$1" in
    runtime_test_fn_invoke.o)
      printf '%s' "seeds/runtime_test_fn_invoke.from_x.c|src/asm/runtime_test_fn_invoke.x|XLANG_RUNTIME_TEST_FN_INVOKE_FROM_X|std"
      ;;
    runtime_random_fill.o)
      printf '%s' "seeds/runtime_random_fill.from_x.c|src/asm/runtime_random_fill.x|XLANG_RUNTIME_RANDOM_FILL_FROM_X|std"
      ;;
    runtime_compress_zlib_glue.o)
      printf '%s' "seeds/runtime_compress_zlib_glue.from_x.c|src/asm/runtime_compress_zlib_glue.x|XLANG_RUNTIME_COMPRESS_ZLIB_GLUE_FROM_X|std"
      ;;
    runtime_time_os.o)
      printf '%s' "seeds/runtime_time_os.from_x.c|src/asm/runtime_time_os.x|XLANG_RUNTIME_TIME_OS_FROM_X|std"
      ;;
    runtime_queue_contention.o)
      printf '%s' "seeds/runtime_queue_contention.from_x.c|src/asm/runtime_queue_contention.x|XLANG_RUNTIME_QUEUE_CONTENTION_FROM_X|std"
      ;;
    runtime_dynlib_os.o)
      printf '%s' "seeds/runtime_dynlib_os.from_x.c|src/asm/runtime_dynlib_os.x|XLANG_RUNTIME_DYNLIB_OS_FROM_X|std"
      ;;
    runtime_env_os.o)
      printf '%s' "seeds/runtime_env_os.from_x.c|src/asm/runtime_env_os.x|XLANG_RUNTIME_ENV_OS_FROM_X|std"
      ;;
    runtime_backtrace_platform.o)
      printf '%s' "seeds/runtime_backtrace_platform.from_x.c|src/asm/runtime_backtrace_platform.x|XLANG_RUNTIME_BACKTRACE_PLATFORM_FROM_X|std"
      ;;
    runtime_log_os.o)
      printf '%s' "seeds/runtime_log_os.from_x.c|src/asm/runtime_log_os.x|XLANG_RUNTIME_LOG_OS_FROM_X|std"
      ;;
    runtime_math_libm.o)
      printf '%s' "seeds/runtime_math_libm.from_x.c|src/asm/runtime_math_libm.x|XLANG_RUNTIME_MATH_LIBM_FROM_X|std"
      ;;
    runtime_atomic_glue.o)
      printf '%s' "seeds/runtime_atomic_glue.from_x.c|src/asm/runtime_atomic_glue.x|XLANG_RUNTIME_ATOMIC_GLUE_FROM_X|std"
      ;;
    runtime_net_udp_batch.o)
      # PLATFORM: LINUX — PREFER gated in ensure body; macOS cold = empty TU.
      printf '%s' "seeds/runtime_net_udp_batch.from_x.c|src/asm/runtime_net_udp_batch.x|XLANG_RUNTIME_NET_UDP_BATCH_FROM_X|net_udp"
      ;;
    runtime_net_workers.o)
      printf '%s' "seeds/runtime_net_workers.from_x.c|src/asm/runtime_net_workers.x|XLANG_RUNTIME_NET_WORKERS_FROM_X|std"
      ;;
    runtime_sync_os.o)
      printf '%s' "seeds/runtime_sync_os.from_x.c|src/asm/runtime_sync_os.x|XLANG_RUNTIME_SYNC_OS_FROM_X|std"
      ;;
    runtime_sync_lock_diag_tls.o)
      printf '%s' "seeds/runtime_sync_lock_diag_tls.from_x.c|src/asm/runtime_sync_lock_diag_tls.x|XLANG_RUNTIME_SYNC_LOCK_DIAG_TLS_FROM_X|std"
      ;;
    runtime_thread_glue.o)
      printf '%s' "seeds/runtime_thread_glue.from_x.c|src/asm/runtime_thread_glue.x|XLANG_RUNTIME_THREAD_GLUE_FROM_X|std"
      ;;
    runtime_http_glue.o)
      printf '%s' "seeds/runtime_http_glue.from_x.c|src/asm/http/runtime_http_glue.x|XLANG_RUNTIME_HTTP_GLUE_FROM_X|http"
      ;;
    runtime_tls_mbedtls_bio.o)
      # PLATFORM: MACOS homebrew mbedtls -I optional; LINUX often plain.
      printf '%s' "seeds/runtime_tls_mbedtls_bio.from_x.c|src/asm/runtime_tls_mbedtls_bio.x|XLANG_RUNTIME_TLS_MBEDTLS_BIO_FROM_X|tls"
      ;;
    runtime_arrow_simd_glue.o)
      printf '%s' "seeds/runtime_arrow_simd_glue.from_x.c|src/asm/runtime_arrow_simd_glue.x|XLANG_RUNTIME_ARROW_SIMD_GLUE_FROM_X|std"
      ;;
    runtime_crypto_inc_glue.o)
      printf '%s' "seeds/runtime_crypto_inc_glue.from_x.c|src/asm/runtime_crypto_inc_glue.x|XLANG_RUNTIME_CRYPTO_INC_GLUE_FROM_X|std"
      ;;
    runtime_ed25519_ref10_glue.o)
      printf '%s' "seeds/runtime_ed25519_ref10_glue.from_x.c|src/asm/runtime_ed25519_ref10_glue.x|XLANG_RUNTIME_ED25519_REF10_GLUE_FROM_X|ed25519"
      ;;
    runtime_process_argv.o)
      printf '%s' "seeds/runtime_process_argv.from_x.c|src/asm/runtime_process_argv.x|XLANG_RUNTIME_PROCESS_ARGV_FROM_X|std"
      ;;
    runtime_process_os_glue.o)
      printf '%s' "seeds/runtime_process_os_glue.from_x.c|src/asm/runtime_process_os_glue.x|XLANG_RUNTIME_PROCESS_OS_GLUE_FROM_X|std"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Compile rest/cold seed with leaf extras. stdout unused; sets rest_o/out via args.
# $1=out_o  $2=seed  $3=from_x_def_or_empty  $4=leaf_kind
# from_x_def empty → cold path (no FROM_X).
_runtime_os_cc_seed() {
  local out_o="$1" seed="$2" from_x_def="$3" leaf_kind="$4"
  local def_flag=() rest_extra=()
  if [ -n "$from_x_def" ]; then
    def_flag=(-D"$from_x_def")
  fi
  case "$leaf_kind" in
    http) rest_extra=(-Iseeds/http) ;;
    ed25519) rest_extra=(-Isrc/asm) ;;
    tls)
      # PLATFORM: MACOS — try homebrew mbedtls include first; fall back plain.
      # shellcheck disable=SC2086
      if $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
           -I/opt/homebrew/opt/mbedtls/include \
           "${def_flag[@]+"${def_flag[@]}"}" \
           -c -o "$out_o" "$seed" 2>/dev/null; then
        return 0
      fi
      # shellcheck disable=SC2086
      $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
        "${def_flag[@]+"${def_flag[@]}"}" \
        -c -o "$out_o" "$seed"
      return $?
      ;;
    std|net_udp) ;;
    *)
      echo "ensure_host_cc_seed_o try-runtime-os-prefer: unknown leaf_kind $leaf_kind" >&2
      return 1
      ;;
  esac
  # shellcheck disable=SC2086
  $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
    "${rest_extra[@]+"${rest_extra[@]}"}" \
    "${def_flag[@]+"${def_flag[@]}"}" \
    -c -o "$out_o" "$seed"
}

ensure_runtime_os_prefer_one() {
  local o="$1"
  local spec seed x_src from_x_def leaf_kind rest
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0 done=0
  local thin_o rest_o uname_s

  spec="$(runtime_os_prefer_spec_for_out "$o")"
  if [ -z "$spec" ]; then
    return 3
  fi
  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  rest="${rest#*|}"
  from_x_def="${rest%%|*}"
  leaf_kind="${rest#*|}"

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-runtime-os-prefer: missing seed $seed for $o" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (runtime-os-prefer)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # PLATFORM: LINUX — net_udp PREFER only on Linux (macOS cold = empty .o).
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  _do_prefer=0
  if [ "$prefer" = "1" ] && [ -f "$x_src" ] \
    && { [ -x ./xlang ] || [ -x ./xlang-c ] || [ -x ./bootstrap_xlangc ]; }; then
    if [ "$leaf_kind" = "net_udp" ] && [ "$uname_s" != "Linux" ]; then
      _do_prefer=0
    else
      _do_prefer=1
    fi
  fi

  if [ "$_do_prefer" = "1" ]; then
    thin_o="$(mktemp "${TMPDIR:-/tmp}/rtos_thin.XXXXXX")"
    rest_o="$(mktemp "${TMPDIR:-/tmp}/rtos_rest.XXXXXX")"
    if rt_prefer_try_x_to_o "$x_src" "$thin_o" \
      && _runtime_os_cc_seed "$rest_o" "$seed" "$from_x_def" "$leaf_kind" \
      && pure_ld_partial_merge "$o" "$thin_o" "$rest_o" 2>/dev/null; then
      log "prefer thin.x+rest $o <- $x_src + seed-rest (try-runtime-os-prefer/$leaf_kind)"
      done=1
    else
      log "runtime-os hybrid failed for $o ($leaf_kind); fallback full seed"
    fi
    rm -f "$thin_o" "$rest_o"
  fi

  if [ "$done" = "1" ]; then
    return 0
  fi

  # Cold full seed (ensure_one twin / PREFER=0 / net_udp non-Linux).
  # tls needs mbedtls fallback — use _runtime_os_cc_seed for cold too.
  if [ "$leaf_kind" = "tls" ] || [ "$leaf_kind" = "http" ] || [ "$leaf_kind" = "ed25519" ]; then
    if [ -f "$o" ] && [ "$prefer" = "1" ]; then
      FORCE=1
    fi
    if [ "$FORCE" = "1" ] || [ ! -f "$o" ] || [ "$seed" -nt "$o" ] \
      || { [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; }; then
      _runtime_os_cc_seed "$o" "$seed" "" "$leaf_kind" || return 1
      log "cold seed $o <- $seed (try-runtime-os-prefer/$leaf_kind)"
    else
      log "skip up-to-date $o (runtime-os-prefer cold)"
    fi
    FORCE="${XLANG_HOST_CC_SEED_FORCE:-0}"
    return 0
  fi

  if [ -f "$o" ] && [ "$prefer" = "1" ]; then
    FORCE=1
    ensure_one "$o" "$seed"
    FORCE=0
  else
    ensure_one "$o" "$seed"
  fi
  return 0
}

try_ensure_runtime_os_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-runtime-os-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(runtime_os_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_runtime_os_prefer_one "$o"
  return 0
}



# ---------------------------------------------------------------------------
# wave780: try-std-core-prefer OUT — B2 std/core product hybrid table.
#
# Table-driven single body (G.7 有则补全). Five product leaves that still had
# Makefile inline host-cc / PREFER hybrid (process · path · runtime · net ·
# core/slice glue). NOT physical delete — Makefile keeps thin-call edges + prereqs.
#
# leaf_kind:
#   direct        — R2 DIRECT: PREFER=1 + xlang-c → -lib-name "" -o OUT from .x;
#                   else / fail → cold seed (path / runtime / slice)
#   process_merge — cold only: cc args_thin seed + ld -r with runtime_process_argv.o
#                   + runtime_process_os_glue.o (B1 already try-runtime-os-prefer)
#   net_merge     — multi sub .x + net_*_fast PREFER thin+rest + final ld -r
#                   PLATFORM: MACOS force xlang-c for net submodules (dead_strip UNDEF)
# Prefer fail / PREFER≠1 / no xlang → cold seed (direct) or process/net cold path.
# Callers: Makefile 5 leaves (wave780).
# Exit codes:
#   0 — OUT is a table member; body produced OUT
#   3 — OUT is not in the std-core prefer table
#   1 — seed missing / compile failed
# PLATFORM: SHARED shell body · g05 historic PREFER=1 · cold chain PREFER=0.
# Residual after: B3–B5 · physical delete · R5.
# ---------------------------------------------------------------------------

# Normalize OUT path variants to a canonical key used by the table.
# Accepts: ../std/path/path.o | std/path/path.o | absolute …/std/path/path.o
std_core_prefer_key_for_out() {
  local o="$1"
  case "$o" in
    ../std/process/process.o|std/process/process.o|*std/process/process.o)
      printf '%s' "std/process/process.o" ;;
    ../std/path/path.o|std/path/path.o|*std/path/path.o)
      printf '%s' "std/path/path.o" ;;
    ../std/runtime/runtime.o|std/runtime/runtime.o|*std/runtime/runtime.o)
      printf '%s' "std/runtime/runtime.o" ;;
    ../std/net/net.o|std/net/net.o|*std/net/net.o)
      printf '%s' "std/net/net.o" ;;
    ../core/slice/slice.o|core/slice/slice.o|*core/slice/slice.o)
      printf '%s' "core/slice/slice.o" ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Spec: seed|x_src|leaf_kind
std_core_prefer_spec_for_out() {
  local key
  key="$(std_core_prefer_key_for_out "$1")"
  case "$key" in
    std/path/path.o)
      printf '%s' "seeds/runtime_path_fast.from_x.c|src/asm/runtime_path_fast.x|direct"
      ;;
    std/runtime/runtime.o)
      printf '%s' "seeds/runtime_std_runtime_fast.from_x.c|src/asm/runtime_std_runtime_fast.x|direct"
      ;;
    core/slice/slice.o)
      printf '%s' "seeds/runtime_slice_glue.from_x.c|src/asm/runtime_slice_glue.x|direct"
      ;;
    std/process/process.o)
      printf '%s' "seeds/runtime_process_args_thin.from_x.c||process_merge"
      ;;
    std/net/net.o)
      printf '%s' "||net_merge"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Prefer: historic Makefile used xlang-c -lib-name "" (R2 DIRECT), not -E rest.
_std_core_try_xlang_c_direct() {
  local x_src="$1" out_o="$2"
  local xx=""
  if [ -x ./xlang-c ]; then
    xx=./xlang-c
  elif [ -x ./xlang ]; then
    xx=./xlang
  elif [ -x ./bootstrap_xlangc ]; then
    xx=./bootstrap_xlangc
  else
    return 1
  fi
  [ -f "$x_src" ] || return 1
  mkdir -p "$(dirname "$out_o")"
  # PLATFORM: SHARED — R2 DIRECT pure-compute / thin wrappers via -lib-name "".
  XLANG_KEEP_C=1 "$xx" -L .. -L src -L src/asm -lib-name "" -o "$out_o" "$x_src"
}

# Relocatable multi-obj merge for std/core prefer (process_merge / net_merge / fast).
#
# G.7: single authority = `pure_ld_partial_merge` (already sourced above).
# Do NOT keep a second body with bare `ld -r -multiply_defined suppress`:
#   - `-multiply_defined` is obsolete on current Apple ld
#   - no Darwin libtool fallback → when an input is a prefer **libtool archive
#     named `.o`** (e.g. `runtime_process_argv.o` thin+rest after F7 two-segment
#     `ld -r` failure), Apple `ld -r` errors
#     "more than one LC_SEGMENT found in object file" and process_merge fails →
#     no `std/process/process.o` → product `-o` UNDEF `std_process_*` (tip L4
#     run-process BLD001 after CG002 force_load wave left process_argv as archive)
#
# PLATFORM: SHARED — pure_ld_partial_merge owns Linux ELF -r + Darwin libtool
#           -static fallback; callers (process_merge / net_merge) unchanged.
_std_core_ld_r() {
  local out="$1"
  shift
  pure_ld_partial_merge "$out" "$@"
}

# PLATFORM: SHARED — after ld -r product .o, keep only export faces as global T.
# formal_mod co-emits foreign std_io_*/core_result_*/xlang_io_*/ctx_*/process_*
# bodies as global T; product monofile also emits them → multi-def (L4
# run-std-net-context-gate: 221 dups). Localize non-export T so monofile owns
# foreign faces; this .o only exports its API. G.7 single post-merge authority.
# $1=out.o  remaining args = bare prefixes without leading _ (e.g. std_net_ net_)
# Darwin: nmedit -s keep_list. Linux: objcopy/llvm-objcopy --localize-symbol.
_std_core_keep_global_prefixes() {
  local out="$1"
  shift
  [ -f "$out" ] || return 0
  command -v nm >/dev/null 2>&1 || return 0
  local uname_s keep_re keep_list sym bare p
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  keep_re=""
  for p in "$@"; do
    [ -n "$p" ] || continue
    if [ -n "$keep_re" ]; then
      keep_re="${keep_re}|${p}"
    else
      keep_re="${p}"
    fi
  done
  [ -n "$keep_re" ] || return 0
  keep_list=$(mktemp "${TMPDIR:-/tmp}/xlang_keep_glob.XXXXXX") || return 0
  # nm -gU: defined global only. Match bare name against keep prefixes (optional _).
  nm -gU "$out" 2>/dev/null | awk '{print $NF}' | while IFS= read -r sym; do
    [ -n "$sym" ] || continue
    bare="$sym"
    case "$sym" in
      _*) bare="${sym#_}" ;;
    esac
    if printf '%s' "$bare" | grep -Eq "^(${keep_re})"; then
      printf '%s\n' "$sym"
    fi
  done >"$keep_list" 2>/dev/null || true
  if [ ! -s "$keep_list" ]; then
    rm -f "$keep_list"
    return 0
  fi
  if [ "$uname_s" = "Darwin" ] && command -v nmedit >/dev/null 2>&1; then
    # nmedit: globals NOT in list become local. Export list = keep.
    nmedit -s "$keep_list" "$out" 2>/dev/null || true
  else
    # Linux / objcopy path: localize every global T not in keep_list.
    local oc=""
    if command -v objcopy >/dev/null 2>&1; then
      oc=objcopy
    elif command -v llvm-objcopy >/dev/null 2>&1; then
      oc=llvm-objcopy
    elif [ -x /opt/homebrew/opt/llvm/bin/llvm-objcopy ]; then
      oc=/opt/homebrew/opt/llvm/bin/llvm-objcopy
    fi
    if [ -n "$oc" ]; then
      nm -gU "$out" 2>/dev/null | awk '{print $NF}' | while IFS= read -r sym; do
        [ -n "$sym" ] || continue
        if ! grep -Fxq "$sym" "$keep_list" 2>/dev/null; then
          "$oc" --localize-symbol="$sym" "$out" 2>/dev/null || true
        fi
      done
    fi
  fi
  rm -f "$keep_list"
  return 0
}

# One net_*_fast PREFER or cold seed piece.
# $1=fast_o $2=seed $3=x_src $4=from_x_def $5=mode (thin_rest|direct) $6=xlang_bin
_std_core_net_fast_one() {
  local fast_o="$1" seed="$2" x_src="$3" from_x_def="$4" mode="$5" xbin="${6:-}"
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local thin_o rest_o dir
  dir="$(dirname "$fast_o")"
  mkdir -p "$dir"
  if [ "$prefer" = "1" ] && [ -f "$x_src" ] && [ -n "$xbin" ] && [ -x "$xbin" ]; then
    if [ "$mode" = "direct" ]; then
      if XLANG_KEEP_C=1 "$xbin" -L .. -L src -L src/asm -lib-name "" -o "$fast_o" "$x_src" 2>/dev/null; then
        return 0
      fi
    else
      thin_o="${fast_o%.o}_thin.o"
      rest_o="${fast_o%.o}_rest.o"
      # shellcheck disable=SC2086
      if XLANG_KEEP_C=1 "$xbin" -L .. -L src -L src/asm -lib-name "" -o "$thin_o" "$x_src" 2>/dev/null \
        && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -D"$from_x_def" -c "$seed" -o "$rest_o" 2>/dev/null \
        && _std_core_ld_r "$fast_o" "$thin_o" "$rest_o"; then
        rm -f "$thin_o" "$rest_o"
        return 0
      fi
      rm -f "$thin_o" "$rest_o"
    fi
  fi
  # shellcheck disable=SC2086
  $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c "$seed" -o "$fast_o"
}

ensure_std_core_prefer_one() {
  local o="$1"
  local key spec seed x_src leaf_kind rest
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local stale=0
  local uname_s xlang net_sub_xlang objs x
  local tmp_args

  key="$(std_core_prefer_key_for_out "$o")"
  spec="$(std_core_prefer_spec_for_out "$o")"
  if [ -z "$spec" ] || [ -z "$key" ]; then
    return 3
  fi
  # Force canonical OUT under compiler/ parent layout (../std|core/...).
  case "$key" in
    std/*|core/*) o="../$key" ;;
  esac

  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  leaf_kind="${rest#*|}"

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    if [ -n "$seed" ] && [ -f "$seed" ] && [ "$seed" -nt "$o" ]; then
      stale=1
    fi
    if [ -n "$x_src" ] && [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    if [ "$leaf_kind" = "process_merge" ]; then
      if [ -f runtime_process_argv.o ] && [ runtime_process_argv.o -nt "$o" ]; then
        stale=1
      fi
      if [ -f runtime_process_os_glue.o ] && [ runtime_process_os_glue.o -nt "$o" ]; then
        stale=1
      fi
      # PLATFORM: SHARED — import_alias carries std_process_* product face.
      if [ -f seeds/runtime_process_import_alias.from_x.c ] &&
         [ seeds/runtime_process_import_alias.from_x.c -nt "$o" ]; then
        stale=1
      fi
    fi
    # wave796: net multi-merge source mtime (FORCE thin; G.7 single body).
    # Mirrors historic Makefile prereqs + net_merge body inputs.
    if [ "$stale" = "0" ] && [ "$leaf_kind" = "net_merge" ]; then
      local _net_dep
      for _net_dep in \
        ../std/net/mod.x ../std/net/alpn.x ../std/net/dns.x \
        ../std/net/io_batch.x ../std/net/addr.x ../std/net/ipv6.x \
        ../std/net/sock.x ../std/net/udp.x ../std/net/tcp.x \
        ../std/net/udp_batch.x ../std/net/workers.x ../std/net/tcp_pool.x \
        seeds/runtime_net_dns_fast.from_x.c \
        seeds/runtime_net_io_batch_fast.from_x.c \
        seeds/runtime_net_addr_fast.from_x.c \
        seeds/runtime_net_ipv6_fast.from_x.c \
        seeds/runtime_net_sock_fast.from_x.c \
        src/asm/runtime_net_dns_fast.x \
        src/asm/runtime_net_io_batch_fast.x \
        src/asm/runtime_net_addr_fast.x \
        src/asm/runtime_net_ipv6_fast.x \
        src/asm/runtime_net_sock_fast.x
      do
        if [ -f "$_net_dep" ] && [ "$_net_dep" -nt "$o" ]; then
          stale=1
          break
        fi
      done
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && [ -n "$seed" ] && [ -f "$seed" ]       && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (std-core-prefer/$leaf_kind)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  case "$leaf_kind" in
    direct)
      if [ ! -f "$seed" ]; then
        echo "ensure_host_cc_seed_o try-std-core-prefer: missing seed $seed for $o" >&2
        return 1
      fi
      if [ "$prefer" = "1" ] && [ -f "$x_src" ]; then
        if _std_core_try_xlang_c_direct "$x_src" "$o"; then
          log "prefer direct.x $o <- $x_src (try-std-core-prefer/direct)"
          return 0
        fi
        log "std-core direct prefer failed for $o; fallback full seed"
      fi
      if [ -f "$o" ] && [ "$prefer" = "1" ]; then
        FORCE=1
        ensure_one "$o" "$seed"
        FORCE=0
      else
        ensure_one "$o" "$seed"
      fi
      return 0
      ;;

    process_merge)
      # PLATFORM: SHARED — process.o = args_thin + argv + os_glue + import_alias.
      # import_alias exports std_process_* for pure-asm import METHOD (G.7 complete
      # process_merge; C-path co-emit of mod.x is not used on pure-asm product).
      if [ ! -f "$seed" ]; then
        echo "ensure_host_cc_seed_o try-std-core-prefer: missing seed $seed for $o" >&2
        return 1
      fi
      if [ ! -f runtime_process_argv.o ]; then
        try_ensure_runtime_os_prefer_one runtime_process_argv.o \
          || ensure_one runtime_process_argv.o seeds/runtime_process_argv.from_x.c \
          || return 1
      fi
      if [ ! -f runtime_process_os_glue.o ]; then
        try_ensure_runtime_os_prefer_one runtime_process_os_glue.o \
          || ensure_one runtime_process_os_glue.o seeds/runtime_process_os_glue.from_x.c \
          || return 1
      fi
      _proc_alias_c="seeds/runtime_process_import_alias.from_x.c"
      if [ ! -f "$_proc_alias_c" ]; then
        echo "ensure_host_cc_seed_o try-std-core-prefer: missing $_proc_alias_c for $o" >&2
        return 1
      fi
      tmp_args="$(mktemp "${TMPDIR:-/tmp}/proc_args.XXXXXX")"
      tmp_alias="$(mktemp "${TMPDIR:-/tmp}/proc_alias.XXXXXX")"
      # shellcheck disable=SC2086
      if ! $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c "$seed" -o "$tmp_args"; then
        rm -f "$tmp_args" "$tmp_alias"
        return 1
      fi
      # shellcheck disable=SC2086
      if ! $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c "$_proc_alias_c" -o "$tmp_alias"; then
        rm -f "$tmp_args" "$tmp_alias"
        return 1
      fi
      if ! _std_core_ld_r "$o" "$tmp_args" runtime_process_argv.o runtime_process_os_glue.o "$tmp_alias"; then
        rm -f "$tmp_args" "$tmp_alias"
        return 1
      fi
      rm -f "$tmp_args" "$tmp_alias"
      log "process_merge $o <- $seed + argv + os_glue + import_alias (try-std-core-prefer)"
      return 0
      ;;

    net_merge)
      # PLATFORM: SHARED net.o — mod.x + alpn/udp/tcp/udp_batch/workers/tls_stub/tcp_pool
      # + five fast pieces. PLATFORM: MACOS — force xlang-c for net submodules
      # (post-wave102 pure-asm arm64 left tls_stub UNDEFs under product -dead_strip).
      # F-04 tcp_pool.x must be in this merge: before this leaf, only weak
      # std_net_tcp_pool_net_tcp_pool_*_c stubs (return 0) were merged, so
      # cookbook net_tcp_pool built but create handle was always 0 (run=1).
      # G.7: complete net_merge with real tcp_pool.o + strong import aliases
      # (≡ tls_stub); do not keep a second weak body. PLATFORM: SHARED.
      xlang="${XLANG:-}"
      if [ -z "$xlang" ] || [ ! -x "$xlang" ]; then
        if [ -x ./xlang_asm ]; then xlang=./xlang_asm
        elif [ -x ./xlang ]; then xlang=./xlang
        elif [ -x ./xlang-c ]; then xlang=./xlang-c
        else xlang=; fi
      fi
      if [ -z "$xlang" ]; then
        echo "net.o: need xlang-c to merge net_*.x" >&2
        # Historic Makefile exited 0 here (soft). Keep soft for cold trees.
        return 0
      fi
      net_sub_xlang="$xlang"
      uname_s="$(uname -s 2>/dev/null || echo Unknown)"
      case "$uname_s" in
        Darwin)
          if [ -x ./xlang-c ]; then net_sub_xlang=./xlang-c
          elif [ -x ./xlang ]; then net_sub_xlang=./xlang; fi
          ;;
      esac
      objs=""
      # PLATFORM: SHARED — include tls_stub + tcp_pool (mod.x import both).
      # OpenSSL/mbedTLS variants remain separate product overlays.
      for x in alpn udp tcp udp_batch workers tls_stub tcp_pool; do
        sh scripts/xlang_compile_std_x.sh "$net_sub_xlang" "../std/net/$x.x" "../std/net/$x.o" || return 1
        objs="$objs ../std/net/$x.o"
      done
      # Import-binding face: bare net_tls_*_c → std_net_tls_stub_net_tls_*_c
      # and bare net_tcp_pool_*_c → std_net_tcp_pool_net_tcp_pool_*_c.
      # xlang_compile_std_x emits bare C symbols; mod.x import path prefixes both
      # leaf and name. G.7: single alias .o after stub/pool compile (no second body).
      if [ -f ../std/net/tls_stub.o ] || [ -f ../std/net/tcp_pool.o ]; then
        # Keep alias .o under std/net/ (not TMPDIR) so ld -r sees a stable path.
        _tls_alias_c="../std/net/tls_stub_import_alias.c"
        _tls_alias_o="../std/net/tls_stub_import_alias.o"
        {
          echo '/* net_merge: import-binding aliases for std.net.tls_stub + tcp_pool */'
          echo '#include <stdint.h>'
          echo '#include <stddef.h>'
          cat <<'TEOF'
extern int32_t net_tls_is_available_c(void);
extern uint8_t *net_tls_backend_name_c(void);
extern int32_t net_tls_connect_client_c(int32_t fd, uint8_t *sni);
extern int32_t net_tls_connect_client_alpn_c(int32_t fd, uint8_t *sni, uint8_t *alpn, int32_t alpn_len);
extern int32_t net_tls_close_c(int64_t h);
extern int32_t net_tls_read_c(int64_t h, uint8_t *buf, int32_t cap);
extern int32_t net_tls_write_c(int64_t h, uint8_t *buf, int32_t len);
extern int32_t net_tls_last_error_c(void);
extern int32_t net_tls_alpn_selected_c(int64_t h, uint8_t *out, int32_t out_cap);
extern int32_t net_tls_alpn_is_h2_c(int64_t h);
int32_t std_net_tls_stub_net_tls_is_available_c(void) { return net_tls_is_available_c(); }
uint8_t *std_net_tls_stub_net_tls_backend_name_c(void) { return net_tls_backend_name_c(); }
int32_t std_net_tls_stub_net_tls_connect_client_c(int32_t fd, uint8_t *sni) { return net_tls_connect_client_c(fd, sni); }
int32_t std_net_tls_stub_net_tls_connect_client_alpn_c(int32_t fd, uint8_t *sni, uint8_t *alpn, int32_t alpn_len) { return net_tls_connect_client_alpn_c(fd, sni, alpn, alpn_len); }
int32_t std_net_tls_stub_net_tls_close_c(int64_t h) { return net_tls_close_c(h); }
int32_t std_net_tls_stub_net_tls_read_c(int64_t h, uint8_t *buf, int32_t cap) { return net_tls_read_c(h, buf, cap); }
int32_t std_net_tls_stub_net_tls_write_c(int64_t h, uint8_t *buf, int32_t len) { return net_tls_write_c(h, buf, len); }
int32_t std_net_tls_stub_net_tls_last_error_c(void) { return net_tls_last_error_c(); }
int32_t std_net_tls_stub_net_tls_alpn_selected_c(int64_t h, uint8_t *out, int32_t out_cap) { return net_tls_alpn_selected_c(h, out, out_cap); }
int32_t std_net_tls_stub_net_tls_alpn_is_h2_c(int64_t h) { return net_tls_alpn_is_h2_c(h); }
/* Residual io faces when product only needs connect_ctx.
 * Weak so real io .o can override when linked. PLATFORM: SHARED. */
__attribute__((weak)) int32_t std_io_read_fixed_fd(int32_t a, uint32_t b, size_t c, size_t d, uint32_t e) {
  (void)a;(void)b;(void)c;(void)d;(void)e; return -1;
}
__attribute__((weak)) int32_t std_io_write_fixed_fd(int32_t a, uint32_t b, size_t c, size_t d, uint32_t e) {
  (void)a;(void)b;(void)c;(void)d;(void)e; return -1;
}
__attribute__((weak)) uint8_t *xlang_io_read_ptr_len(size_t h, size_t *out_len) {
  (void)h; if (out_len) *out_len = 0; return (uint8_t *)0;
}
/* Strong import aliases for std.net.tcp_pool (≡ tls_stub). Bare bodies live in
 * tcp_pool.o from tcp_pool.x. Do NOT weaken these — weak return-0 stubs were the
 * net_tcp_pool cookbook run=1 root cause. PLATFORM: SHARED. */
extern int64_t net_tcp_pool_create_c(uint32_t a, uint32_t b, int32_t c);
extern int32_t net_tcp_pool_acquire_c(int64_t h, uint32_t t);
extern int32_t net_tcp_pool_release_c(int64_t h, int32_t fd);
extern void net_tcp_pool_drain_c(int64_t h);
extern void net_tcp_pool_destroy_c(int64_t h);
extern int32_t net_tcp_pool_connect_count_c(int64_t h);
extern int32_t net_tcp_pool_idle_count_c(int64_t h);
extern int32_t net_tcp_pool_smoke_c(void);
int64_t std_net_tcp_pool_net_tcp_pool_create_c(uint32_t a, uint32_t b, int32_t c) {
  return net_tcp_pool_create_c(a, b, c);
}
int32_t std_net_tcp_pool_net_tcp_pool_acquire_c(int64_t h, uint32_t t) {
  return net_tcp_pool_acquire_c(h, t);
}
int32_t std_net_tcp_pool_net_tcp_pool_release_c(int64_t h, int32_t fd) {
  return net_tcp_pool_release_c(h, fd);
}
void std_net_tcp_pool_net_tcp_pool_drain_c(int64_t h) { net_tcp_pool_drain_c(h); }
void std_net_tcp_pool_net_tcp_pool_destroy_c(int64_t h) { net_tcp_pool_destroy_c(h); }
int32_t std_net_tcp_pool_net_tcp_pool_connect_count_c(int64_t h) {
  return net_tcp_pool_connect_count_c(h);
}
int32_t std_net_tcp_pool_net_tcp_pool_idle_count_c(int64_t h) {
  return net_tcp_pool_idle_count_c(h);
}
int32_t std_net_tcp_pool_net_tcp_pool_smoke_c(void) { return net_tcp_pool_smoke_c(); }
/* Fast-path addr helpers sometimes only on asm leaves; weak for pure host-C net.o. */
__attribute__((weak)) int64_t net_tcp_local_addr_c(int32_t fd) { (void)fd; return 0; }
__attribute__((weak)) int64_t net_tcp_peer_addr_c(int32_t fd) { (void)fd; return 0; }
__attribute__((weak)) void net_tcp_set_addr_port_buf_c(uint8_t *b, uint32_t a, uint32_t p) {
  (void)b;(void)a;(void)p;
}
__attribute__((weak)) void net_udp_set_addr_port_buf_c(uint8_t *b, uint32_t a, uint32_t p) {
  (void)b;(void)a;(void)p;
}
TEOF
        } >"$_tls_alias_c"
        if cc -std=c11 -c -o "$_tls_alias_o" "$_tls_alias_c" 2>/dev/null; then
          objs="$objs $_tls_alias_o"
        fi
        rm -f "$_tls_alias_c"
      fi
      sh scripts/xlang_compile_std_module.sh ../std/net/mod.o ../std/net/mod.x || return 1
      objs="$objs ../std/net/mod.o"
      _std_core_net_fast_one ../std/net/net_dns_fast.o \
        seeds/runtime_net_dns_fast.from_x.c src/asm/runtime_net_dns_fast.x \
        XLANG_RUNTIME_NET_DNS_FAST_FROM_X thin_rest "$net_sub_xlang" || return 1
      _std_core_net_fast_one ../std/net/net_io_batch_fast.o \
        seeds/runtime_net_io_batch_fast.from_x.c src/asm/runtime_net_io_batch_fast.x \
        XLANG_RUNTIME_NET_IO_BATCH_FAST_FROM_X thin_rest "$net_sub_xlang" || return 1
      _std_core_net_fast_one ../std/net/net_addr_fast.o \
        seeds/runtime_net_addr_fast.from_x.c src/asm/runtime_net_addr_fast.x \
        XLANG_RUNTIME_NET_ADDR_FAST_FROM_X direct "$net_sub_xlang" || return 1
      _std_core_net_fast_one ../std/net/net_ipv6_fast.o \
        seeds/runtime_net_ipv6_fast.from_x.c src/asm/runtime_net_ipv6_fast.x \
        XLANG_RUNTIME_NET_IPV6_FAST_FROM_X thin_rest "$net_sub_xlang" || return 1
      _std_core_net_fast_one ../std/net/net_sock_fast.o \
        seeds/runtime_net_sock_fast.from_x.c src/asm/runtime_net_sock_fast.x \
        XLANG_RUNTIME_NET_SOCK_FAST_FROM_X thin_rest "$net_sub_xlang" || return 1
      # shellcheck disable=SC2086
      if ! _std_core_ld_r "$o" $objs \
        ../std/net/net_dns_fast.o ../std/net/net_io_batch_fast.o \
        ../std/net/net_addr_fast.o ../std/net/net_ipv6_fast.o \
        ../std/net/net_sock_fast.o; then
        return 1
      fi
      rm -f ../std/net/mod.o ../std/net/net_dns_fast.o ../std/net/net_io_batch_fast.o \
        ../std/net/net_addr_fast.o ../std/net/net_ipv6_fast.o ../std/net/net_sock_fast.o
      # Keep only net product faces global. formal_mod co-emits std_io_*/core_result_*
      # etc. as T; monofile also defines them → multi-def on product -o (L4 STD-092).
      # PLATFORM: SHARED — nmedit (Darwin) / objcopy localize (Linux).
      _std_core_keep_global_prefixes "$o" "std_net_" "net_"
      log "net_merge $o <- sub.x + mod + five fast (try-std-core-prefer)"
      return 0
      ;;

    *)
      echo "ensure_host_cc_seed_o try-std-core-prefer: unknown leaf_kind $leaf_kind" >&2
      return 1
      ;;
  esac
}

try_ensure_std_core_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-std-core-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(std_core_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_std_core_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave781: try-lsp-sat-prefer OUT — B3 LSP satellite hybrid table.
#
# Table-driven single body (G.7 有则补全). Two Makefile product hybrids that
# sit *outside* try-other-l2-prefer (lsp_diag.o glue) and try-ldpc-prefer
# (pipeline_ctx). Shapes differ enough that extending other-l2 would fork
# authority — dedicated table is the single body for these two leaves.
#
# leaf_kind:
#   direct_e   — PREFER: xlang-c -E .x → host-cc -x c -c → OUT (no rest merge).
#                cold: seeds/lsp_diag_pipeline_sizes.from_x.c
#                Historic Makefile: prefer when ./xlang-c exists (no PREFER env).
#   thin_rest_e — PREFER: xlang-c -E .x → thin.o + seed rest
#                 -DXLANG_LSP_DIAG_STUBS_NO_C_FROM_X → ld -r multidef.
#                 cold: seeds/lsp_diag_stubs_no_c.from_x.c
# Prefer fail / no xlang-c → cold seed. NOT physical delete — Makefile thin-call.
# Callers: Makefile 2 leaves (wave781).
# Exit codes:
#   0 — OUT is a table member; body produced OUT
#   3 — OUT is not in the lsp-sat prefer table
#   1 — seed missing / compile failed
# PLATFORM: SHARED shell body · product dual hybrid historic (xlang-c when present).
# Residual after: ~~B4~~ (wave782) · B5 · physical delete · R5.
# ---------------------------------------------------------------------------

# Spec: seed|x_src|from_x_def|leaf_kind
# from_x_def empty for direct_e; XLANG_LSP_DIAG_STUBS_NO_C_FROM_X for thin_rest_e.
lsp_sat_prefer_spec_for_out() {
  case "$1" in
    src/lsp/lsp_diag_pipeline_sizes_nostub.o)
      printf '%s' "seeds/lsp_diag_pipeline_sizes.from_x.c|src/lsp/lsp_diag_pipeline_sizes.x||direct_e"
      ;;
    src/lsp/lsp_diag_stubs_no_c.o)
      printf '%s' "seeds/lsp_diag_stubs_no_c.from_x.c|src/lsp/lsp_diag_stubs_no_c.x|XLANG_LSP_DIAG_STUBS_NO_C_FROM_X|thin_rest_e"
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Historic Makefile xlang-c -E for LSP satellites (stubs uses module -L paths).
_lsp_sat_xlang_c_e() {
  local x_src="$1" tmp_c="$2" mode="$3"
  if [ ! -x ./xlang-c ]; then
    return 1
  fi
  [ -f "$x_src" ] || return 1
  case "$mode" in
    direct_e)
      ./xlang-c -E "$x_src" >"$tmp_c" 2>/dev/null
      ;;
    thin_rest_e)
      ./xlang-c -L .. -L src -L src/asm -L src/ast -L src/parser \
        -L src/typeck -L src/preprocess -L src/codegen -L src/pipeline \
        -E "$x_src" >"$tmp_c" 2>/dev/null
      ;;
    *)
      return 1
      ;;
  esac
  [ -s "$tmp_c" ]
}

ensure_lsp_sat_prefer_one() {
  local o="$1"
  local spec seed x_src from_x_def leaf_kind rest
  local stale=0
  local tmp_c thin_o rest_o

  spec="$(lsp_sat_prefer_spec_for_out "$o")"
  if [ -z "$spec" ]; then
    return 3
  fi
  seed="${spec%%|*}"
  rest="${spec#*|}"
  x_src="${rest%%|*}"
  rest="${rest#*|}"
  from_x_def="${rest%%|*}"
  leaf_kind="${rest#*|}"

  if [ ! -f "$seed" ]; then
    echo "ensure_host_cc_seed_o try-lsp-sat-prefer: missing seed $seed for $o" >&2
    return 1
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    [ "$seed" -nt "$o" ] && stale=1
    if [ -f "$x_src" ] && [ "$x_src" -nt "$o" ]; then
      stale=1
    fi
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    if [ "$stale" = "0" ] && seed_project_hdrs_newer "$seed" "$o"; then
      stale=1
    fi
    # wave794: Makefile flag-sensitive FORCE thin (main/runtime/pipeline_abi).
    if [ "$stale" = "0" ] && force_thin_makefile_flags_newer "$o"; then
      stale=1
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (lsp-sat-prefer/$leaf_kind)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  case "$leaf_kind" in
    direct_e)
      # PLATFORM: SHARED — PREFER xlang-c -E → host-cc; cold seed (Makefile twin).
      if [ -f "$x_src" ] && [ -x ./xlang-c ]; then
        tmp_c="$(mktemp "${TMPDIR:-/tmp}/lsp_sizes.XXXXXX")"
        # shellcheck disable=SC2086
        if _lsp_sat_xlang_c_e "$x_src" "$tmp_c" direct_e \
          && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
               -x c -c "$tmp_c" -o "$o"; then
          rm -f "$tmp_c"
          log "prefer direct_e $o <- $x_src (try-lsp-sat-prefer/direct_e)"
          return 0
        fi
        rm -f "$tmp_c"
        log "lsp-sat direct_e prefer failed for $o; fallback full seed"
      fi
      if [ -f "$o" ]; then
        FORCE=1
        ensure_one "$o" "$seed"
        FORCE=0
      else
        ensure_one "$o" "$seed"
      fi
      return 0
      ;;

    thin_rest_e)
      # PLATFORM: SHARED — PREFER thin -E .x + seed rest FROM_X → ld -r multidef.
      if [ -f "$x_src" ] && [ -x ./xlang-c ] && [ -n "$from_x_def" ]; then
        tmp_c="$(mktemp "${TMPDIR:-/tmp}/ldsn.XXXXXX")"
        thin_o="$(mktemp "${TMPDIR:-/tmp}/ldsn_thin.XXXXXX")"
        rest_o="$(mktemp "${TMPDIR:-/tmp}/ldsn_rest.XXXXXX")"
        # shellcheck disable=SC2086
        if _lsp_sat_xlang_c_e "$x_src" "$tmp_c" thin_rest_e \
          && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
               -x c -c "$tmp_c" -o "$thin_o" \
          && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
               -D"$from_x_def" -c "$seed" -o "$rest_o" \
          && _std_core_ld_r "$o" "$thin_o" "$rest_o"; then
          rm -f "$tmp_c" "$thin_o" "$rest_o"
          log "prefer thin_rest_e $o <- $x_src + seed-rest (try-lsp-sat-prefer/thin_rest_e)"
          return 0
        fi
        rm -f "$tmp_c" "$thin_o" "$rest_o"
        log "lsp-sat thin_rest_e prefer failed for $o; fallback full seed"
      fi
      if [ -f "$o" ]; then
        FORCE=1
        ensure_one "$o" "$seed"
        FORCE=0
      else
        ensure_one "$o" "$seed"
      fi
      return 0
      ;;

    *)
      echo "ensure_host_cc_seed_o try-lsp-sat-prefer: unknown leaf_kind $leaf_kind" >&2
      return 1
      ;;
  esac
}

try_ensure_lsp_sat_prefer_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-lsp-sat-prefer: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(lsp_sat_prefer_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_lsp_sat_prefer_one "$o"
  return 0
}

# ---------------------------------------------------------------------------
# wave782: try-gen-c-to-o OUT — B4 gen.c → .o bootstrap.
#
# Table-driven membership (G.7 有则补全). Four Makefile pure host-cc leaves
# outside try-gen-x catalog (lsp trio + pipeline_x are try-gen-x). Body =
# ensure_gen_x_o.sh one OUT (same authority as wave761 gen maps; extended for B4).
#
# Leaves: lexer_x.o · ast_gen2.o · driver_x.o · preprocess_x.o
# wave295 B′: _x_stubs2.o host left (dead dual; product g05 / stage2 never linked).
# Prefer fail N/A — cold gen.c only (historic Makefile).
# Callers: Makefile 4 leaves (wave782/295). NOT physical delete.
# Exit codes:
#   0 — OUT is a B4 table member; body produced OUT (or skip up-to-date)
#   3 — OUT is not in the gen-c-to-o table
#   1 — gen missing / compile failed
# PLATFORM: SHARED shell body.
# Residual after: B5 · physical delete · R5.
# ---------------------------------------------------------------------------

gen_c_to_o_spec_for_out() {
  # stdout non-empty iff B4 member (value = gen source path for --check).
  case "$1" in
    lexer_x.o) printf '%s' "lexer_gen.c" ;;
    ast_gen2.o) printf '%s' "ast_gen2.c" ;;
    driver_x.o) printf '%s' "driver_gen.c" ;;
    preprocess_x.o) printf '%s' "preprocess_gen.c" ;;
    *) printf '%s' "" ;;
  esac
}

try_ensure_gen_c_to_o_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-gen-c-to-o: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(gen_c_to_o_spec_for_out "$o")" ]; then
    return 3
  fi
  if [ ! -f scripts/ensure_gen_x_o.sh ]; then
    echo "ensure_host_cc_seed_o try-gen-c-to-o: missing scripts/ensure_gen_x_o.sh (wave782)" >&2
    return 1
  fi
  if [ "$FORCE" = "1" ]; then
    XLANG_GEN_X_FORCE=1 XLANG_HOST_CC_SEED_FORCE=1 \
      bash scripts/ensure_gen_x_o.sh one "$o" || return 1
  else
    bash scripts/ensure_gen_x_o.sh one "$o" || return 1
  fi
  return 0
}

# ---------------------------------------------------------------------------
# wave783: try-cfg-eval-ladder OUT — B5 cfg_eval multi-ladder (single leaf).
#
# Authority for src/lexer/cfg_eval.o product body (G.7 有则补全). Historic
# Makefile multi-ladder: live -E-extern (+/- -L) → cc with PIPELINE_GEN_CFLAGS
# + link_alias ld -r; else linux pin gen + alias; else bootstrap stub copy.
# Dead rung dropped: `if false &&` default-pipeline asm path (was permanently
# disabled). Cold may soft-ensure xlang-c via ensure_xlang_c.sh (wave950;
# was make-target xlang-c); pin/stub rungs do not require it.
#
# Exit codes:
#   0 — OUT is B5 member; ladder produced OUT (or skip up-to-date)
#   3 — OUT is not src/lexer/cfg_eval.o
#   1 — all rungs failed
# PLATFORM: SHARED shell body · pin = Ubuntu gold seed; Darwin may fall to stub
# when -E emits illegal dual host-lit C (historic Makefile twin).
# Callers: g05 / rebuild_leaves / historic Makefile thin-call (wave783).
# wave950: missing xlang-c → ensure_xlang_c.sh (0-make post-delete).
# ---------------------------------------------------------------------------

cfg_eval_ladder_spec_for_out() {
  # stdout non-empty iff B5 member.
  case "$1" in
    src/lexer/cfg_eval.o) printf '%s' "cfg_eval_multi_ladder" ;;
    *) printf '%s' "" ;;
  esac
}

# wave886: default LD_RELFLAGS when unset (mirror Makefile UNAME ifeq).
# PLATFORM: MACOS — ld -r needs explicit -arch; LINUX/WINDOWS leave empty.
# G.7 single body — CLI/env LD_RELFLAGS still wins when set.
_cfg_eval_default_ld_relflags() {
  local uname_s uname_m
  uname_s=$(uname -s 2>/dev/null || echo unknown)
  uname_m=$(uname -m 2>/dev/null || echo unknown)
  case "$uname_s" in
    Darwin)
      case "$uname_m" in
        arm64|aarch64) printf '%s' "-arch arm64" ;;
        x86_64|amd64) printf '%s' "-arch x86_64" ;;
        *) printf '%s' "" ;;
      esac
      ;;
    *)
      printf '%s' ""
      ;;
  esac
}

# Link cfg_eval_x.o + link_alias → OUT (historic Makefile $(LD) -r twin).
# PLATFORM: SHARED — LD/LD_RELFLAGS from env when set; shell defaults otherwise
# (wave886: no Makefile recipe inject).
_cfg_eval_link_x_plus_alias() {
  local out="$1" x_o="$2"
  local ld_bin="${LD:-ld}"
  local ld_rel="${LD_RELFLAGS-}"
  if [ -z "${LD_RELFLAGS+x}" ]; then
    ld_rel="$(_cfg_eval_default_ld_relflags)"
  fi
  if [ ! -f scripts/cc_inc_tu.sh ]; then
    echo "ensure_host_cc_seed_o try-cfg-eval-ladder: missing scripts/cc_inc_tu.sh" >&2
    return 1
  fi
  if [ ! -f seeds/cfg_eval_link_alias.from_x.c ]; then
    echo "ensure_host_cc_seed_o try-cfg-eval-ladder: missing seeds/cfg_eval_link_alias.from_x.c" >&2
    return 1
  fi
  sh scripts/cc_inc_tu.sh seeds/cfg_eval_link_alias.from_x.c src/lexer/cfg_eval_link_alias.o || return 1
  # shellcheck disable=SC2086
  $ld_bin $ld_rel -r -o "$out" "$x_o" src/lexer/cfg_eval_link_alias.o
}

ensure_cfg_eval_ladder_one() {
  local o="$1"
  local x_src="src/lexer/cfg_eval.x"
  local pin="seeds/cfg_eval_gen.linux.x86_64.c"
  local alias_seed="seeds/cfg_eval_link_alias.from_x.c"
  local stub_seed="seeds/cfg_eval_bootstrap_stub.from_x.c"
  local host_lit="seeds/cfg_eval_host_lit.from_x.c"
  local x_o="src/lexer/cfg_eval_x.o"
  local gen_c="src/lexer/cfg_eval_gen.c"
  local xlang_c="./xlang-c"
  local stale=0
  local d

  if [ -z "$(cfg_eval_ladder_spec_for_out "$o")" ]; then
    return 3
  fi

  if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
    stale=0
    for d in "$x_src" "$alias_seed" "$pin" "$host_lit" "$stub_seed"; do
      if [ -f "$d" ] && [ "$d" -nt "$o" ]; then
        stale=1
        break
      fi
    done
    # wave793: project-header mtime (FORCE thin; G.7 single body).
    # cfg-eval multi-seed: scan pin + alias + stub for #include freshness.
    if [ "$stale" = "0" ]; then
      if seed_project_hdrs_newer "$pin" "$o"         || seed_project_hdrs_newer "$alias_seed" "$o"         || seed_project_hdrs_newer "$stub_seed" "$o"; then
        stale=1
      fi
    fi
    if [ "$stale" = "0" ]; then
      log "skip up-to-date $o (cfg-eval-ladder)"
      return 0
    fi
  fi

  mkdir -p "$(dirname "$o")"

  # Soft ensure xlang-c for live -E rungs. wave950: ensure_xlang_c.sh (0-make;
  # Makefile deleted wave941). Soft-continue so pin/stub cold paths still work
  # when bootstrap_xlangc / SRC is not ready (L2 residual rebuild).
  # PLATFORM: SHARED — G.7 single authority for default xlang-c alias.
  if [ ! -x "$xlang_c" ]; then
    log "cfg-eval-ladder: xlang-c missing; soft ensure via ensure_xlang_c.sh (pin/stub fallback if fail)"
    bash scripts/ensure_xlang_c.sh ensure xlang-c 2>/dev/null || true
  fi
  # (do not reintroduce bare make-target xlang-c here)

  rm -f "$x_o"

  # Rung 1: live -E -E-extern -L .. + PIPELINE_GEN_CFLAGS + alias
  # PLATFORM: SHARED — prefer live gen; wave98: bare -E forbidden (dangling BSS).
  if [ -x "$xlang_c" ] && [ -f "$x_src" ]; then
    # shellcheck disable=SC2086
    if "$xlang_c" -E -E-extern -L .. "$x_src" >"$gen_c" 2>/dev/null \
      && [ -s "$gen_c" ] \
      && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c -o "$x_o" "$gen_c" 2>/dev/null \
      && _cfg_eval_link_x_plus_alias "$o" "$x_o"; then
      log "cfg_eval.o from cfg_eval.x (-E-extern + alias)"
      return 0
    fi
    # Rung 2: -E -E-extern without -L (module path residual)
    # shellcheck disable=SC2086
    if "$xlang_c" -E -E-extern "$x_src" >"$gen_c" 2>/dev/null \
      && [ -s "$gen_c" ] \
      && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c -o "$x_o" "$gen_c" 2>/dev/null \
      && _cfg_eval_link_x_plus_alias "$o" "$x_o"; then
      log "cfg_eval.o from cfg_eval.x (-E-extern no -L + alias)"
      return 0
    fi
  fi

  # Rung 3: linux pin gen + alias (Ubuntu gold seed; same as typeck pin style)
  # PLATFORM: LINUX pin source · SHARED host-cc of pin on all platforms.
  # shellcheck disable=SC2086
  if [ -s "$pin" ] \
    && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc -c -o "$x_o" "$pin" 2>/dev/null \
    && _cfg_eval_link_x_plus_alias "$o" "$x_o"; then
    log "cfg_eval.o from cfg_eval.x (linux pin gen + alias)"
    return 0
  fi

  # Rung 4: bootstrap stub (cold when .x path unusable / -E illegal C)
  if [ -f "$stub_seed" ] && [ -f scripts/cc_inc_tu.sh ]; then
    if sh scripts/cc_inc_tu.sh "$stub_seed" src/lexer/cfg_eval_bootstrap_stub.o \
      && cp -f src/lexer/cfg_eval_bootstrap_stub.o "$o"; then
      log "cfg_eval.o from bootstrap stub (cfg_eval.x unavailable at cold start)"
      return 0
    fi
  fi

  echo "ensure_host_cc_seed_o try-cfg-eval-ladder: all rungs failed for $o" >&2
  return 1
}

try_ensure_cfg_eval_ladder_one() {
  local o="$1"
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-cfg-eval-ladder: need <out.o>" >&2
    exit 2
  fi
  if [ -z "$(cfg_eval_ladder_spec_for_out "$o")" ]; then
    return 3
  fi
  ensure_cfg_eval_ladder_one "$o"
  return $?
}

# ---------------------------------------------------------------------------
# wave760: try-r2 OUT — R2 platform-stamp panic cold body (UNAME leaf).
#
# Membership = catalog DRIVER_SEED_PANIC_OBJS only (lists = mk; currently
# runtime_panic.o). Cold source selection mirrors Makefile / build_xlang_asm:
#   PLATFORM: LINUX|x86_64 — cc -c src/asm/runtime_panic_x86_64.s when present
#   PLATFORM: MACOS|arm64 / LINUX|aarch64 — seeds/runtime_panic_arm64.from_x.c
#   else — seeds/runtime_panic.from_x.c
# Platform stamp: build_asm/runtime_panic.$(uname -s).$(uname -m).stamp
# (create if missing; force rebuild when stamp was missing so platform switch
# cannot leave a stale .o without a matching stamp).
# Exit codes:
#   0 — OUT is panic catalog member; cold body ran (or skipped up-to-date)
#   3 — OUT not in DRIVER_SEED_PANIC_OBJS (caller residual make)
#   1 — membership found but compile failed / missing source
# PLATFORM: SHARED shell body · per-host source pick tagged above.
# PREFER_X_O=1 thin+rest → try-r2-prefer (wave776; not this cold helper).
# ---------------------------------------------------------------------------
r2_panic_host_pick_src() {
  # stdout: "asm|seed <path>" — host cold source for runtime_panic.o
  # PLATFORM: LINUX|x86_64 prefer pure-syscall .s; arm64/aarch64 arm64 seed;
  #           else portable from_x seed (incl. Darwin x86_64 / Windows).
  local uname_s uname_m
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  if [ "$uname_s" = "Linux" ] && [ "$uname_m" = "x86_64" ] \
    && [ -f src/asm/runtime_panic_x86_64.s ]; then
    printf '%s\n' "asm src/asm/runtime_panic_x86_64.s"
    return 0
  fi
  case "$uname_m" in
    arm64|aarch64)
      if [ -f seeds/runtime_panic_arm64.from_x.c ]; then
        printf '%s\n' "seed seeds/runtime_panic_arm64.from_x.c"
        return 0
      fi
      ;;
  esac
  if [ -f seeds/runtime_panic.from_x.c ]; then
    printf '%s\n' "seed seeds/runtime_panic.from_x.c"
    return 0
  fi
  echo "ensure_host_cc_seed_o r2-panic: no runtime_panic cold source for $uname_s/$uname_m" >&2
  return 1
}

ensure_r2_panic_one() {
  # Cold body for a DRIVER_SEED_PANIC_OBJS member (no membership check).
  local o="$1"
  local pick kind src stamp uname_s uname_m need=0 cand
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  stamp="build_asm/runtime_panic.${uname_s}.${uname_m}.stamp"
  mkdir -p build_asm
  if [ ! -f "$stamp" ]; then
    touch "$stamp"
    need=1
  fi
  pick="$(r2_panic_host_pick_src)" || return 1
  kind="${pick%% *}"
  src="${pick#* }"
  if [ ! -f "$src" ]; then
    echo "ensure_host_cc_seed_o r2-panic: missing source $src" >&2
    return 1
  fi
  case "$kind" in
    seed)
      # Sibling .x freshness is inside ensure_one; stamp-missing forces compile.
      # FORCE is script-global (read at ensure_one); temporarily raise when stamp was new.
      if [ "$need" = "1" ] && [ "$FORCE" != "1" ]; then
        FORCE=1
        ensure_one "$o" "$src"
        FORCE=0
      else
        ensure_one "$o" "$src"
      fi
      ;;
    asm)
      # PLATFORM: LINUX|x86_64 — plain cc -c .s (no PIPELINE_GEN_CFLAGS).
      if [ "$FORCE" != "1" ] && [ "$need" = "0" ] && [ -f "$o" ] \
        && [ ! "$src" -nt "$o" ]; then
        log "skip $o (up-to-date vs $src)"
        return 0
      fi
      log "cc -c $src → $o"
      # Stage 12.2.3: pure_as_compile (as when XLANG_ZERO_CC_AS=1, else $CC -c).
      pure_as_compile "$o" "$src"
      ;;
    *)
      echo "ensure_host_cc_seed_o r2-panic: unknown kind $kind" >&2
      return 1
      ;;
  esac
  # Keep stamp mtime after successful compile so make prereq stays satisfied.
  touch "$stamp"
  return 0
}

try_ensure_r2_one() {
  # wave760 panic + wave762 typeck_f64/crt0 — single try-r2 entry (G.7 有则补全).
  local o="$1"
  local list
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r2: need <out.o>" >&2
    exit 2
  fi
  # 1) panic catalog
  list="$(catalog_key_words "DRIVER_SEED_PANIC_OBJS")"
  if list_has_word "$o" "$list"; then
    case "$o" in
      runtime_panic.o) ensure_r2_panic_one "$o"; return 0 ;;
      *)
        echo "ensure_host_cc_seed_o try-r2: no cold map for panic member $o" >&2
        return 1
        ;;
    esac
  fi
  # 2) typeck_f64 catalog
  list="$(catalog_key_words "DRIVER_SEED_TYPECK_F64_OBJS")"
  if list_has_word "$o" "$list"; then
    case "$o" in
      src/typeck/typeck_f64_bits.o) ensure_r2_typeck_f64_one "$o"; return 0 ;;
      *)
        echo "ensure_host_cc_seed_o try-r2: no cold map for typeck_f64 member $o" >&2
        return 1
        ;;
    esac
  fi
  # 3) crt0 catalog
  list="$(catalog_key_words "DRIVER_SEED_CRT0_OBJS")"
  if list_has_word "$o" "$list"; then
    ensure_r2_crt0_one "$o" || return 1
    return 0
  fi
  return 3
}

ensure_r2_panic() {
  local list n=0 o
  list="$(catalog_key_words "DRIVER_SEED_PANIC_OBJS")"
  if [ -z "${list// /}" ]; then
    echo "ensure_host_cc_seed_o: empty DRIVER_SEED_PANIC_OBJS" >&2
    exit 1
  fi
  # shellcheck disable=SC2086
  for o in $list; do
    [ -z "$o" ] && continue
    ensure_r2_panic_one "$o" || exit 1
    n=$((n + 1))
  done
  log "r2-panic OK ($n objs; catalog DRIVER_SEED_PANIC_OBJS)"
}

# ---------------------------------------------------------------------------
# wave776: try-r2-prefer OUT — R2 panic PREFER thin+rest product path.
#
# Membership = catalog DRIVER_SEED_PANIC_OBJS (lists = mk; currently
# runtime_panic.o only). G.7 有则补全 on R2 family (parallel try-r3-prefer;
# not a second list / second cold body).
#
# PREFER host pick mirrors historic Makefile ifeq tree (NOT cold pick):
#   PLATFORM: LINUX|x86_64 + runtime_panic_x86_64.s present
#     → no PREFER (pure syscall .s; cold only)
#   PLATFORM: LINUX|arm64|aarch64
#     → thin src/asm/runtime_panic_arm64.x
#       + rest seeds/runtime_panic_arm64.from_x.c -DXLANG_RUNTIME_PANIC_ARM64_FROM_X
#   PLATFORM: LINUX (other, incl. x86_64 without .s) + non-Linux (MACOS/…)
#     → thin src/asm/runtime_panic.x
#       + rest seeds/runtime_panic.from_x.c -DXLANG_RUNTIME_PANIC_FROM_X
#       (Darwin arm64 historic PREFER uses portable panic.x, not arm64.x)
#
# When XLANG_G05_PREFER_X_O=1 and xlang-c works and prefer spec non-empty:
#   thin via historic xlang-c -o (same -L / -lib-name as Makefile dual)
#   rest = $CC seed -D FROM_X
#   merge = ld $(r3_prefer_ld_r_flags) thin + rest → OUT
# Prefer fail / PREFER≠1 / pure-asm host / no xlang-c → ensure_r2_panic_one cold.
#
# Callers: Makefile runtime_panic.o (all UNAME branches; was dual hybrid).
# Exit codes:
#   0 — OUT is panic catalog member; prefer or cold body produced OUT
#   3 — OUT not in DRIVER_SEED_PANIC_OBJS
#   1 — cold compile failed / missing source
# PLATFORM: SHARED shell body · per-host PREFER pick tagged above.
# Residual after: R5 CI · physical delete · FORCE_CC named residual.
# ---------------------------------------------------------------------------

# stdout: "x_src|seed|from_x_def" or empty when PREFER not applicable (pure asm).
r2_panic_prefer_spec() {
  local uname_s uname_m
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  # PLATFORM: LINUX|x86_64 pure-syscall .s — Makefile has no PREFER dual.
  if [ "$uname_s" = "Linux" ] && [ "$uname_m" = "x86_64" ] \
    && [ -f src/asm/runtime_panic_x86_64.s ]; then
    printf '%s' ""
    return 0
  fi
  if [ "$uname_s" = "Linux" ]; then
    case "$uname_m" in
      arm64|aarch64)
        # PLATFORM: LINUX|aarch64 — arm64 thin + arm64 seed rest.
        if [ -f src/asm/runtime_panic_arm64.x ] \
          && [ -f seeds/runtime_panic_arm64.from_x.c ]; then
          printf '%s' "src/asm/runtime_panic_arm64.x|seeds/runtime_panic_arm64.from_x.c|XLANG_RUNTIME_PANIC_ARM64_FROM_X"
          return 0
        fi
        ;;
    esac
    # PLATFORM: LINUX other (or aarch64 fallback) — portable panic.x + from_x.
    if [ -f src/asm/runtime_panic.x ] && [ -f seeds/runtime_panic.from_x.c ]; then
      printf '%s' "src/asm/runtime_panic.x|seeds/runtime_panic.from_x.c|XLANG_RUNTIME_PANIC_FROM_X"
      return 0
    fi
  else
    # PLATFORM: MACOS / non-Linux — historic PREFER pair (panic.x + from_x)
    # even when cold pick uses arm64 seed on Darwin arm64.
    if [ -f src/asm/runtime_panic.x ] && [ -f seeds/runtime_panic.from_x.c ]; then
      printf '%s' "src/asm/runtime_panic.x|seeds/runtime_panic.from_x.c|XLANG_RUNTIME_PANIC_FROM_X"
      return 0
    fi
  fi
  printf '%s' ""
  return 0
}

ensure_r2_prefer_one() {
  # PREFER thin+rest or cold for one DRIVER_SEED_PANIC member (no membership check).
  local o="$1"
  local prefer="${XLANG_G05_PREFER_X_O:-0}"
  local spec x_src seed from_x_def rest
  local thin_o rest_o ld_flags done=0 stale=0

  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r2-prefer: need <out.o>" >&2
    return 2
  fi

  # PREFER thin+rest only when PREFER=1 (Darwin cold-chain safety twin of R3).
  if [ "$prefer" = "1" ]; then
    spec="$(r2_panic_prefer_spec)"
    if [ -n "$spec" ]; then
      x_src="${spec%%|*}"
      rest="${spec#*|}"
      seed="${rest%%|*}"
      from_x_def="${rest#*|}"
      if [ -f "$x_src" ] && [ -f "$seed" ] && [ -x ./xlang-c ]; then
        if [ "$FORCE" != "1" ] && [ -f "$o" ]; then
          stale=0
          [ "$seed" -nt "$o" ] && stale=1
          [ "$x_src" -nt "$o" ] && stale=1
          # wave793: project-header mtime (FORCE thin; G.7 single body).
          if [ "$stale" = "0" ] && [ -n "$seed" ] && [ -f "$seed" ]             && seed_project_hdrs_newer "$seed" "$o"; then
            stale=1
          fi
          if [ "$stale" = "0" ]; then
            log "skip up-to-date $o (r2-prefer)"
            return 0
          fi
        fi
        thin_o="$(mktemp "${TMPDIR:-/tmp}/r2pref_thin.XXXXXX")"
        rest_o="$(mktemp "${TMPDIR:-/tmp}/r2pref_rest.XXXXXX")"
        ld_flags="$(r3_prefer_ld_r_flags)"
        # Historic Makefile: XLANG_KEEP_C=1 ./xlang-c -L … -lib-name "" -o thin .x
        # PLATFORM: SHARED product PREFER path (not -E harness; keep dual fidelity).
        # shellcheck disable=SC2086
        if XLANG_KEEP_C=1 ./xlang-c -L .. -L src -L src/asm -lib-name "" \
             -o "$thin_o" "$x_src" 2>/dev/null \
          && $CC $BASE_CFLAGS $PIPELINE_GEN_CFLAGS -I. -Iinclude -Isrc \
               -D"$from_x_def" -c -o "$rest_o" "$seed" 2>/dev/null \
          && ld $ld_flags -o "$o" "$thin_o" "$rest_o" 2>/dev/null; then
          log "prefer thin.x+rest $o <- $x_src + $seed (try-r2-prefer)"
          done=1
        else
          log "r2-prefer hybrid failed for $o; fallback cold try-r2"
        fi
        rm -f "$thin_o" "$rest_o"
      fi
    fi
  fi

  if [ "$done" = "1" ]; then
    # Keep platform stamp fresh (same as cold body).
    local uname_s uname_m stamp
    uname_s="$(uname -s 2>/dev/null || echo Unknown)"
    uname_m="$(uname -m 2>/dev/null || echo unknown)"
    stamp="build_asm/runtime_panic.${uname_s}.${uname_m}.stamp"
    mkdir -p build_asm
    touch "$stamp"
    return 0
  fi

  # Cold path = try-r2 / ensure_r2_panic_one (G.7 single cold body).
  # After failed PREFER, force recompile so a partial thin.o is not left green.
  if [ "$prefer" = "1" ] && [ -f "$o" ]; then
    FORCE=1
    ensure_r2_panic_one "$o" || return 1
    FORCE=0
  else
    ensure_r2_panic_one "$o" || return 1
  fi
  return 0
}

try_ensure_r2_prefer_one() {
  local o="$1"
  local list
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-r2-prefer: need <out.o>" >&2
    exit 2
  fi
  list="$(catalog_key_words "DRIVER_SEED_PANIC_OBJS")"
  if ! list_has_word "$o" "$list"; then
    return 3
  fi
  case "$o" in
    runtime_panic.o) ensure_r2_prefer_one "$o"; return 0 ;;
    *)
      echo "ensure_host_cc_seed_o try-r2-prefer: no prefer map for panic member $o" >&2
      return 1
      ;;
  esac
}

# ---------------------------------------------------------------------------
# wave762: R2 typeck_f64_bits — host picks platform pure-.s source.
# Membership = catalog DRIVER_SEED_TYPECK_F64_OBJS (lists = mk).
# PLATFORM: LINUX|x86_64 / LINUX|aarch64 / DARWIN|arm64 / DARWIN|x86_64 /
#           WINDOWS|x86_64 mingw .s. Mirrors g05_ensure + Makefile (G.7 one body).
# ---------------------------------------------------------------------------
r2_typeck_f64_host_pick_src() {
  # stdout: path to .s for typeck_f64_bits.o on this host
  local uname_s uname_m
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  # PLATFORM: WINDOWS — MSYS/MinGW uname often MINGW64_NT-* / MSYS_NT-*.
  case "$uname_s" in
    MINGW*|MSYS*|CYGWIN*)
      if [ -f src/typeck/typeck_f64_bits_x86_64_mingw.s ]; then
        printf '%s\n' "src/typeck/typeck_f64_bits_x86_64_mingw.s"
        return 0
      fi
      ;;
  esac
  if [ "${XLANG_IS_WIN_HOST:-0}" = "1" ]; then
    if [ -f src/typeck/typeck_f64_bits_x86_64_mingw.s ]; then
      printf '%s\n' "src/typeck/typeck_f64_bits_x86_64_mingw.s"
      return 0
    fi
  fi
  case "${uname_s}/${uname_m}" in
    Linux/x86_64)
      printf '%s\n' "src/typeck/typeck_f64_bits_x86_64.s" ;;
    Linux/aarch64)
      printf '%s\n' "src/typeck/typeck_f64_bits_aarch64_elf.s" ;;
    Darwin/arm64|Darwin/aarch64)
      printf '%s\n' "src/typeck/typeck_f64_bits_arm64.s" ;;
    Darwin/x86_64|Darwin/amd64)
      printf '%s\n' "src/typeck/typeck_f64_bits_x86_64.s" ;;
    *)
      echo "ensure_host_cc_seed_o r2-typeck-f64: unsupported host $uname_s/$uname_m" >&2
      return 1
      ;;
  esac
  return 0
}

ensure_r2_typeck_f64_one() {
  local o="$1"
  local src
  src="$(r2_typeck_f64_host_pick_src)" || return 1
  if [ ! -f "$src" ]; then
    echo "ensure_host_cc_seed_o r2-typeck-f64: missing $src" >&2
    return 1
  fi
  mkdir -p "$(dirname "$o")"
  if [ "$FORCE" != "1" ] && [ -f "$o" ] && [ ! "$src" -nt "$o" ]; then
    log "skip $o (up-to-date vs $src)"
    return 0
  fi
  log "cc -c $src → $o"
  # Stage 12.2.3: pure_as_compile (as when XLANG_ZERO_CC_AS=1, else $CC -c).
  pure_as_compile "$o" "$src"
}

ensure_r2_typeck_f64() {
  local list n=0 o
  list="$(catalog_key_words "DRIVER_SEED_TYPECK_F64_OBJS")"
  if [ -z "${list// /}" ]; then
    echo "ensure_host_cc_seed_o: empty DRIVER_SEED_TYPECK_F64_OBJS" >&2
    exit 1
  fi
  # shellcheck disable=SC2086
  for o in $list; do
    [ -z "$o" ] && continue
    ensure_r2_typeck_f64_one "$o" || exit 1
    n=$((n + 1))
  done
  log "r2-typeck-f64 OK ($n objs; catalog DRIVER_SEED_TYPECK_F64_OBJS)"
}

# ---------------------------------------------------------------------------
# wave762: R2 crt0 / freestanding platform leaves — fixed o→src map.
# Membership = catalog DRIVER_SEED_CRT0_OBJS. Most are plain .s; mingw is seed
# via cc_inc_tu (+ WIN32_O_CFLAGS from env/make).
# PLATFORM: LINUX crt0_x86_64 + freestanding · MACOS arm64/darwin_x86_64 ·
#           WINDOWS crt0_mingw seed.
# ---------------------------------------------------------------------------
r2_crt0_src_for_out() {
  # stdout: "asm|seed|cc_inc_tu <path>" for OUT; fail closed if unknown.
  local o="$1"
  case "$o" in
    src/asm/crt0_x86_64.o)
      printf '%s\n' "asm src/asm/crt0_x86_64.s" ;;
    src/asm/crt0_arm64.o)
      printf '%s\n' "asm src/asm/crt0_arm64.s" ;;
    src/asm/crt0_darwin_x86_64.o)
      printf '%s\n' "asm src/asm/crt0_darwin_x86_64.s" ;;
    src/asm/crt0_user_x86_64.o)
      printf '%s\n' "asm src/asm/crt0_user_x86_64.s" ;;
    src/asm/freestanding_io_x86_64.o)
      printf '%s\n' "asm src/asm/freestanding_io_x86_64.s" ;;
    src/asm/crt0_mingw.o)
      # PLATFORM: WINDOWS — seed via cc_inc_tu (Makefile twin).
      printf '%s\n' "cc_inc_tu seeds/crt0_mingw.from_x.c" ;;
    *)
      echo "ensure_host_cc_seed_o r2-crt0: no source map for $o" >&2
      return 1
      ;;
  esac
  return 0
}

ensure_r2_crt0_one() {
  local o="$1"
  local pick kind src
  pick="$(r2_crt0_src_for_out "$o")" || return 1
  kind="${pick%% *}"
  src="${pick#* }"
  if [ ! -f "$src" ]; then
    echo "ensure_host_cc_seed_o r2-crt0: missing $src" >&2
    return 1
  fi
  mkdir -p "$(dirname "$o")"
  case "$kind" in
    asm)
      if [ "$FORCE" != "1" ] && [ -f "$o" ] && [ ! "$src" -nt "$o" ] \
        && ! force_thin_makefile_flags_newer "$o"; then
        log "skip $o (up-to-date vs $src)"
        return 0
      fi
      log "cc -c $src → $o"
      # Stage 12.2.3: pure_as_compile (as when XLANG_ZERO_CC_AS=1, else $CC -c).
      pure_as_compile "$o" "$src"
      ;;
    cc_inc_tu)
      # PLATFORM: WINDOWS — WIN32_O_CFLAGS from env when set by caller (wave866:
      # Makefile drops WIN32_O_CFLAGS= inject; shell ${WIN32_O_CFLAGS:-} empty default).
      # wave795: Makefile mtime for flag-sensitive rebuild (force_thin_makefile_flags_newer).
      if [ "$FORCE" != "1" ] && [ -f "$o" ] && [ ! "$src" -nt "$o" ] \
        && ! force_thin_makefile_flags_newer "$o"; then
        log "skip $o (up-to-date vs $src)"
        return 0
      fi
      if [ ! -f scripts/cc_inc_tu.sh ]; then
        echo "ensure_host_cc_seed_o r2-crt0: missing scripts/cc_inc_tu.sh" >&2
        return 1
      fi
      log "cc_inc_tu $src → $o"
      # shellcheck disable=SC2086
      sh scripts/cc_inc_tu.sh "$src" "$o" ${WIN32_O_CFLAGS:-}
      ;;
    *)
      echo "ensure_host_cc_seed_o r2-crt0: unknown kind $kind" >&2
      return 1
      ;;
  esac
  return 0
}

r2_crt0_host_relevant() {
  # Family-mode filter: catalog lists all platforms, but .s for other OS/ISA
  # live in-tree and must not be assembled by the host toolchain.
  # try-r2 OUT still runs ensure_r2_crt0_one for any member (Makefile only
  # requests the host MAIN_LINK / freestanding leaf).
  # PLATFORM: per-leaf gate below.
  local o="$1" uname_s uname_m
  uname_s="$(uname -s 2>/dev/null || echo Unknown)"
  uname_m="$(uname -m 2>/dev/null || echo unknown)"
  case "$o" in
    src/asm/crt0_x86_64.o|src/asm/crt0_user_x86_64.o|src/asm/freestanding_io_x86_64.o)
      [ "$uname_s" = "Linux" ] && [ "$uname_m" = "x86_64" ]
      ;;
    src/asm/crt0_arm64.o)
      [ "$uname_s" = "Darwin" ] && { [ "$uname_m" = "arm64" ] || [ "$uname_m" = "aarch64" ]; }
      ;;
    src/asm/crt0_darwin_x86_64.o)
      [ "$uname_s" = "Darwin" ] && { [ "$uname_m" = "x86_64" ] || [ "$uname_m" = "amd64" ]; }
      ;;
    src/asm/crt0_mingw.o)
      case "$uname_s" in
        MINGW*|MSYS*|CYGWIN*) return 0 ;;
      esac
      [ "${XLANG_IS_WIN_HOST:-0}" = "1" ]
      ;;
    *)
      return 1
      ;;
  esac
}

ensure_r2_crt0() {
  # Family runner: only host-relevant leaves (source present + host gate).
  local list n=0 o pick src
  list="$(catalog_key_words "DRIVER_SEED_CRT0_OBJS")"
  if [ -z "${list// /}" ]; then
    echo "ensure_host_cc_seed_o: empty DRIVER_SEED_CRT0_OBJS" >&2
    exit 1
  fi
  # shellcheck disable=SC2086
  for o in $list; do
    [ -z "$o" ] && continue
    if ! r2_crt0_host_relevant "$o"; then
      log "r2-crt0 skip $o (not host MAIN_LINK/freestanding leaf)"
      continue
    fi
    pick="$(r2_crt0_src_for_out "$o")" || continue
    src="${pick#* }"
    if [ ! -f "$src" ]; then
      log "r2-crt0 skip $o (source $src missing)"
      continue
    fi
    ensure_r2_crt0_one "$o" || exit 1
    n=$((n + 1))
  done
  log "r2-crt0 OK ($n host-relevant objs; catalog DRIVER_SEED_CRT0_OBJS)"
}


# ---------------------------------------------------------------------------
# wave761: try-gen-x OUT — residual gen *_x.o + pipeline_x.o (R4 pattern body).
#
# Membership (catalog only; G.7 no dual .o list):
#   lsp_io_x.o | lsp_x.o | lsp_diag_x.o ∈ DRIVER_SEED_LSP_X_OBJS
#   pipeline_x.o ∈ DRIVER_SEED_PIPELINE_X_OBJS
# Body: scripts/ensure_gen_x_o.sh one OUT (compile map + gen_driver STALE).
# Exit codes:
#   0 — OUT is gen residual member; body ran (or skipped up-to-date)
#   3 — OUT not in gen residual map / catalog
#   1 — membership found but compile failed
# PLATFORM: SHARED shell · PIPELINE_X_DEPS / FORCE from env (Makefile expands).
# ---------------------------------------------------------------------------
try_ensure_gen_x_one() {
  local o="$1"
  local list
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-gen-x: need <out.o>" >&2
    exit 2
  fi
  case "$o" in
    lsp_io_x.o|lsp_x.o|lsp_diag_x.o)
      list="$(catalog_key_words "DRIVER_SEED_LSP_X_OBJS")"
      if ! list_has_word "$o" "$list"; then
        return 3
      fi
      ;;
    pipeline_x.o)
      list="$(catalog_key_words "DRIVER_SEED_PIPELINE_X_OBJS")"
      if ! list_has_word "$o" "$list"; then
        return 3
      fi
      ;;
    *)
      return 3
      ;;
  esac
  if [ ! -f scripts/ensure_gen_x_o.sh ]; then
    echo "ensure_host_cc_seed_o try-gen-x: missing scripts/ensure_gen_x_o.sh (wave761)" >&2
    return 1
  fi
  # Propagate FORCE into gen body (same global FORCE used by ensure_one).
  if [ "$FORCE" = "1" ]; then
    XLANG_GEN_X_FORCE=1 XLANG_HOST_CC_SEED_FORCE=1 \
      bash scripts/ensure_gen_x_o.sh one "$o" || return 1
  else
    bash scripts/ensure_gen_x_o.sh one "$o" || return 1
  fi
  return 0
}

ensure_gen_x_residual() {
  # Family runner: all gen residual maps (lsp trio + pipeline).
  bash scripts/ensure_gen_x_o.sh residual-all
}

# ---------------------------------------------------------------------------
# --check: wiring + catalog keys + convention (no full compile required)
# ---------------------------------------------------------------------------
check_family() {
  # $1=KEY $2=min_count $3=label $4=seed_mode $5=optional path prefix pattern
  local key="$1"
  local min_n="$2"
  local label="$3"
  local seed_mode="${4:-basename}"
  local path_pfx="${5:-}"
  local list n=0 o seed
  if ! list="$(catalog_key_list "$key" 2>/dev/null)"; then
    bad "catalog cannot expand $key (add export key)"
    return
  fi
  # shellcheck disable=SC2086
  for o in $list; do
    [ -z "$o" ] && continue
    n=$((n + 1))
    case "$seed_mode" in
      basename) seed="$(seed_for_o "$o")" ;;
      frontend-glue)
        if ! seed="$(seed_for_frontend_glue "$o" 2>/dev/null)"; then
          bad "frontend-glue map missing for catalog member $o"
          continue
        fi
        ;;
      main-runtime)
        if ! seed="$(seed_for_main_runtime "$o" 2>/dev/null)"; then
          bad "main-runtime map missing for catalog member $o"
          continue
        fi
        # extras map must also resolve (fail closed)
        if ! extras_for_main_runtime "$o" >/dev/null 2>&1; then
          bad "main-runtime extras map missing for catalog member $o"
        fi
        ;;
      extra-cflags)
        if ! seed="$(seed_for_extra_cflags "$o" 2>/dev/null)"; then
          bad "extra-cflags map missing for catalog member $o"
          continue
        fi
        if ! extras_for_extra_cflags "$o" >/dev/null 2>&1; then
          bad "extra-cflags extras map missing for catalog member $o"
        fi
        ;;
      seed-map)
        if ! seed="$(seed_for_seed_map "$o" 2>/dev/null)"; then
          bad "seed-map map missing for catalog member $o"
          continue
        fi
        if ! extras_for_seed_map "$o" >/dev/null 2>&1; then
          bad "seed-map extras map missing for catalog member $o"
        fi
        ;;
      *) bad "unknown seed_mode $seed_mode for $label"; continue ;;
    esac
    if [ ! -f "$seed" ]; then
      bad "missing seed for $o → $seed ($label)"
    fi
    if [ -n "$path_pfx" ]; then
      case "$o" in
        ${path_pfx}*) ;;
        *) bad "$label .o not under $path_pfx: $o" ;;
      esac
    fi
  done
  if [ "$n" -lt "$min_n" ]; then
    bad "$key count $n < $min_n ($label)"
  else
    note "catalog $key n=$n ($label)"
  fi
}

run_check() {
  local fail=0
  note() { echo "ensure_host_cc_seed_o: $*" >&2; }
  bad() { echo "ensure_host_cc_seed_o: FAIL: $*" >&2; fail=1; }

  # -------------------------------------------------------------------------
  # wave964 post_ship: Makefile physically deleted (wave941). Catalog + shell
  # own host-cc seed/.o; MF thin-call residual inventory is N/A.
  # PLATFORM: SHARED — structural honesty only (no product compile); dual-end L2.
  # -------------------------------------------------------------------------
  if [ ! -f Makefile ]; then
    local _ps_key _ps_keys _ps_cache
    if [ ! -f scripts/driver_seed_obj_catalog.sh ]; then
      bad "missing driver_seed_obj_catalog.sh (wave964 post_ship)"
    else
      note "catalog script present (wave964 post_ship)"
    fi
    if [ ! -f mk/driver_seed_r_lists.mk ]; then
      bad "missing mk/driver_seed_r_lists.mk (wave964; R* list authority)"
    fi
    # Warm file cache once: catalog_key_list uses `catalog_blob | sed` (pipe
    # subshell loses in-process _catalog_blob_cache). Without a file cache,
    # each family re-parses mk (~9s × N) and --check looks hung.
    # PLATFORM: SHARED — same cache contract as bootstrap/ensure_prereqs.
    _ps_cache="${TMPDIR:-/tmp}/xlang_ensure_host_cc_check_$$.catalog"
    if bash scripts/driver_seed_obj_catalog.sh --shell >"$_ps_cache" 2>/dev/null \
      && [ -s "$_ps_cache" ]; then
      export XLANG_CATALOG_CACHE_FILE="$_ps_cache"
      note "catalog cache warm for --check (wave964 post_ship)"
    else
      rm -f "$_ps_cache" 2>/dev/null || true
      note "catalog cache warm skipped; in-process only (wave964)"
    fi
    # List authority lives in mk/*.mk (catalog re-exports). Not Makefile.
    _ps_keys="RT_SEED_SLICE_OBJS R1_CORE_SEED_OBJS R1_FRONTEND_GLUE_OBJS R1_MAIN_RUNTIME_OBJS \
R1_ALIAS_STUBS_OBJS R1_EXTRA_CFLAGS_OBJS R1_MISC_BASENAME_OBJS R1_SEED_MAP_OBJS \
R3_COLD_SEED_OBJS DRIVER_SEED_PANIC_OBJS DRIVER_SEED_TYPECK_F64_OBJS DRIVER_SEED_CRT0_OBJS"
    # shellcheck disable=SC2086
    for _ps_key in $_ps_keys; do
      if ! grep -q "$_ps_key" mk/*.mk 2>/dev/null; then
        bad "$_ps_key not defined in mk/*.mk (wave964 post_ship)"
      fi
    done
    # Catalog expand + seed map resolve (G.7 lists stay mk; shell owns seed paths).
    check_family "RT_SEED_SLICE_OBJS" 5 "rt-slice" "basename" "src/runtime/"
    check_family "R1_CORE_SEED_OBJS" 5 "core-seed" "basename" "src/"
    check_family "R1_FRONTEND_GLUE_OBJS" 3 "frontend-glue" "frontend-glue" "src/"
    check_family "R1_MAIN_RUNTIME_OBJS" 7 "main-runtime" "main-runtime" "src/"
    check_family "R1_ALIAS_STUBS_OBJS" 8 "alias-stubs" "basename" ""
    check_family "R1_EXTRA_CFLAGS_OBJS" 5 "extra-cflags" "extra-cflags" ""
    # Floors track mk/driver_seed_r_lists.mk (post_ship; was misc=9 seed-map=5).
    check_family "R1_MISC_BASENAME_OBJS" 8 "misc-basename" "basename" ""
    check_family "R1_SEED_MAP_OBJS" 4 "seed-map" "seed-map" ""
    check_family "R3_COLD_SEED_OBJS" 9 "r3-cold-seed" "basename" ""
    {
      local panic_list panic_n=0 po pick
      if ! panic_list="$(catalog_key_list "DRIVER_SEED_PANIC_OBJS" 2>/dev/null)"; then
        bad "catalog cannot expand DRIVER_SEED_PANIC_OBJS (wave964 post_ship)"
      else
        # shellcheck disable=SC2086
        for po in $panic_list; do
          [ -z "$po" ] && continue
          panic_n=$((panic_n + 1))
        done
        if [ "$panic_n" -lt 1 ]; then
          bad "DRIVER_SEED_PANIC_OBJS empty (wave964 post_ship)"
        else
          note "catalog DRIVER_SEED_PANIC_OBJS n=$panic_n (r2-panic)"
        fi
        if ! pick="$(r2_panic_host_pick_src 2>/dev/null)"; then
          bad "r2_panic_host_pick_src failed on this host (wave964 post_ship)"
        else
          note "r2-panic host pick: $pick"
        fi
      fi
    }
    {
      local f64_list f64_n=0 fo f64_src crt0_list crt0_n=0 co
      if ! f64_list="$(catalog_key_list "DRIVER_SEED_TYPECK_F64_OBJS" 2>/dev/null)"; then
        bad "catalog cannot expand DRIVER_SEED_TYPECK_F64_OBJS (wave964 post_ship)"
      else
        # shellcheck disable=SC2086
        for fo in $f64_list; do
          [ -z "$fo" ] && continue
          f64_n=$((f64_n + 1))
        done
        if [ "$f64_n" -lt 1 ]; then
          bad "DRIVER_SEED_TYPECK_F64_OBJS empty (wave964 post_ship)"
        else
          note "catalog DRIVER_SEED_TYPECK_F64_OBJS n=$f64_n (r2-typeck-f64)"
        fi
        if ! f64_src="$(r2_typeck_f64_host_pick_src 2>/dev/null)"; then
          bad "r2_typeck_f64_host_pick_src failed on this host (wave964 post_ship)"
        else
          note "r2-typeck-f64 host pick: $f64_src"
        fi
      fi
      if ! crt0_list="$(catalog_key_list "DRIVER_SEED_CRT0_OBJS" 2>/dev/null)"; then
        bad "catalog cannot expand DRIVER_SEED_CRT0_OBJS (wave964 post_ship)"
      else
        # shellcheck disable=SC2086
        for co in $crt0_list; do
          [ -z "$co" ] && continue
          crt0_n=$((crt0_n + 1))
        done
        if [ "$crt0_n" -lt 1 ]; then
          bad "DRIVER_SEED_CRT0_OBJS empty (wave964 post_ship)"
        else
          note "catalog DRIVER_SEED_CRT0_OBJS n=$crt0_n (r2-crt0)"
        fi
      fi
    }
    # G.7: list authority is catalog/mk only — no hardcoded assignment of product lists.
    if grep -nE '^(export )?RT_SEED_SLICE_OBJS=' "$0" 2>/dev/null \
      | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
      bad "must not hardcode RT_SEED_SLICE_OBJS= in shell body"
    fi
    if grep -nE '^(export )?R1_CORE_SEED_OBJS=' "$0" 2>/dev/null \
      | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
      bad "must not hardcode R1_CORE_SEED_OBJS= in shell body"
    fi
    if grep -nE '^(export )?DRIVER_SEED_PANIC_OBJS=' "$0" 2>/dev/null \
      | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
      bad "must not hardcode DRIVER_SEED_PANIC_OBJS= in shell body"
    fi
    # Shell ladder / bodies still required after MF delete.
    if ! grep -q 'try_ensure_r1_one\|try-r1' "$0"; then
      bad "try-r1 / try_ensure_r1_one missing (wave756/964)"
    else
      note "try-r1 pure-R1 helper present (wave964 post_ship)"
    fi
    if ! grep -q 'try_ensure_r3_cold_one\|try-r3-cold' "$0"; then
      bad "try-r3-cold missing (wave757/964)"
    else
      note "try-r3-cold helper present (wave964 post_ship)"
    fi
    if ! grep -q 'try_ensure_r2_one\|try-r2' "$0"; then
      bad "try-r2 / try_ensure_r2_one missing (wave760/762/964)"
    else
      note "try-r2 R2 UNAME helper present (wave964 post_ship)"
    fi
    if ! grep -q 'try_heat_one\|try-heat' "$0"; then
      bad "try-heat / try_heat_one missing (wave789/964 B7A heat)"
    else
      note "try-heat B7A heat auto-dispatch present (wave964 post_ship)"
    fi
    if ! grep -q '_load_try_heat_cflags_via_catalog\|export-try-heat-cflags' "$0"; then
      bad "shell must load try-heat CFLAGS via catalog (wave862/942/964)"
    else
      note "try-heat CFLAGS catalog-load present (wave964 post_ship)"
    fi
    if ! grep -q 'try_ensure_gen_x_one\|try-gen-x' "$0"; then
      bad "try-gen-x / try_ensure_gen_x_one missing (wave761/964)"
    else
      note "try-gen-x gen residual helper present (wave964 post_ship)"
    fi
    if [ ! -f scripts/ensure_gen_x_o.sh ]; then
      bad "scripts/ensure_gen_x_o.sh missing (wave761/964)"
    else
      note "ensure_gen_x_o.sh present (wave964 post_ship)"
    fi
    # wave950: cfg-eval soft missing xlang-c → ensure_xlang_c.sh (0-make).
    if grep -E '^[[:space:]]+\$MAKE[[:space:]]+xlang-c' "$0" 2>/dev/null | grep -q .; then
      bad "cfg-eval ladder must not residual bare make xlang-c (wave950/964; ensure_xlang_c.sh)"
    fi
    if ! grep -q 'ensure_xlang_c\.sh ensure' "$0" 2>/dev/null; then
      bad "cfg-eval ladder must soft-call ensure_xlang_c.sh for missing xlang-c (wave950/964)"
    else
      note "cfg-eval soft xlang-c → ensure_xlang_c.sh (wave964 post_ship; 0-make)"
    fi
    if ! grep -q 'seed_project_hdrs_newer' "$0"; then
      bad "seed_project_hdrs_newer missing (wave793/964)"
    else
      note "seed_project_hdrs_newer present (wave964 post_ship)"
    fi
    if ! grep -q 'force_thin_makefile_flags_newer' "$0"; then
      bad "force_thin_makefile_flags_newer missing (wave794/964)"
    else
      note "force_thin_makefile_flags_newer present (wave964 post_ship)"
    fi
    if ! grep -q 'udp_batch.x' "$0" || ! grep -q 'runtime_net_sock_fast.from_x.c' "$0"; then
      bad "net_merge multi-source mtime missing (wave796/964)"
    else
      note "net_merge multi-source mtime present (wave964 post_ship)"
    fi
    # B4 gen-c-to-o table (shell owns map; MF multi-target gone).
    if ! grep -q 'gen_c_to_o_spec_for_out\|try_ensure_gen_c_to_o_one' "$0"; then
      bad "gen-c-to-o table/body missing (wave782/964)"
    else
      note "gen-c-to-o table present (wave964 post_ship)"
    fi
    _b4_n=0
    for _b4_leaf in lexer_x.o ast_gen2.o driver_x.o preprocess_x.o; do
      if [ -n "$(gen_c_to_o_spec_for_out "$_b4_leaf" 2>/dev/null || true)" ]; then
        _b4_n=$((_b4_n + 1))
      else
        bad "gen_c_to_o_spec_for_out missing $_b4_leaf (wave782/964/295)"
      fi
    done
    if [ "$_b4_n" -ne 4 ]; then
      bad "gen-c-to-o table size $_b4_n != 4 (wave782/964/295 B4 heat)"
    else
      note "gen-c-to-o table has 4 members (wave295 post_ship; stubs2 left)"
    fi
    # B5 cfg-eval ladder table.
    if ! grep -q 'cfg_eval_ladder_spec_for_out\|ensure_cfg_eval_ladder_one\|try-cfg-eval-ladder' "$0"; then
      bad "cfg-eval ladder table/body missing (wave783/964)"
    else
      note "cfg-eval ladder present (wave964 post_ship)"
    fi
    if [ -n "$(cfg_eval_ladder_spec_for_out "src/lexer/cfg_eval.o" 2>/dev/null || true)" ]; then
      note "cfg_eval_ladder_spec_for_out has src/lexer/cfg_eval.o (wave964 post_ship)"
    else
      bad "cfg_eval_ladder_spec_for_out missing src/lexer/cfg_eval.o (wave783/964)"
    fi
    # Prefer helpers still present (product path via try-heat ladder).
    if ! grep -q 'try_ensure_runtime_os_prefer_one' "$0" \
      || ! grep -q 'try_ensure_r1_one' "$0" \
      || ! grep -q 'try_ensure_gen_x_one' "$0"; then
      bad "try-heat ladder requires existing try-* helpers (wave789/964)"
    else
      note "try-heat ladder deps present (prefer/R1/gen; wave964 post_ship)"
    fi
    if [ -n "${_ps_cache:-}" ]; then
      rm -f "$_ps_cache" 2>/dev/null || true
    fi
    if [ "$fail" -ne 0 ]; then
      echo "ensure_host_cc_seed_o: --check FAILED (wave964 post_ship)" >&2
      exit 1
    fi
    echo "ensure_host_cc_seed_o: CHECK OK (wave964 post_ship; catalog+shell R1/R3/R2/gen-x/try-heat; MF thin residual N/A after wave941 phys-del; 0-make)" >&2
    exit 0
  fi

  # wave907–915 G.7: multi-target FORCE try-heat covers many historical per-leaf prefer
  # checks (R1/R3/ASYNC/B1 / GEN_X / GEN_C_TO_O / B3_LSP_SAT / FMT_CHECK / R2 CRT0 / TYPECK_F64 / PANIC).
  # Accept per-leaf OR membership in a multi-target list whose recipe thin-calls ensure
  # try-heat (prefer / gen-x / gen-c-to-o / lsp-sat / other-l2 / try-r2 ladder lives in shell).
  # Archaeology: this block runs only when Makefile is present (pre_ship / restored MF).
  makefile_leaf_try_heat_ok() {
    local leaf="$1"
    local prefer_re="${2:-try-heat}"
    if awk -v leaf="$leaf" -v pre="$prefer_re" '
      $0 ~ ("^" leaf ":") {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ pre) exit 0
        exit 1
      }
    ' Makefile; then
      return 0
    fi
    local mk="mk/driver_seed_r_lists.mk"
    local var
    for var in \
      RT_SEED_SLICE_OBJS R1_CORE_SEED_OBJS R1_FRONTEND_GLUE_OBJS R1_MAIN_RUNTIME_OBJS \
      R1_ALIAS_STUBS_OBJS R1_EXTRA_CFLAGS_OBJS R1_MISC_BASENAME_OBJS R1_SEED_MAP_OBJS \
      R3_COLD_SEED_OBJS ASYNC_THREE_SEED_OBJS B1_RUNTIME_OS_SEED_OBJS GEN_X_SEED_OBJS \
      GEN_C_TO_O_SEED_OBJS B3_LSP_SAT_SEED_OBJS FMT_CHECK_SEED_OBJS DRIVER_SEED_CRT0_OBJS DRIVER_SEED_TYPECK_F64_OBJS DRIVER_SEED_PANIC_OBJS DRIVER_SEED_CFG_EVAL_OBJS; do
      if [ ! -f "$mk" ]; then
        continue
      fi
      if ! awk -v var="$var" -v leaf="$leaf" '
        /^[[:space:]]*#/ { next }
        $0 ~ ("^" var "[[:space:]]*=") {
          line=$0
          sub(/#.*/,"",line)
          n=split(line, a, /[[:space:]\\]+/)
          for (i=1;i<=n;i++) if (a[i]==leaf) { found=1; exit 0 }
        }
        END { exit found ? 0 : 1 }
      ' "$mk"; then
        continue
      fi
      if grep -qE "\\$\\(${var}\\):[[:space:]]*FORCE" Makefile 2>/dev/null \
        && awk -v var="$var" '
          $0 ~ ("\\$\\(" var "\\):") { hit=1; next }
          hit && /^[^#[:space:]\t]/ { exit 1 }
          hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
          END { exit found ? 0 : 1 }
        ' Makefile; then
        return 0
      fi
    done
    # B2 std_core hybrid multi-target (separate mk)
    local b2mk="mk/std_core_hybrid_product_objs.mk"
    if [ -f "$b2mk" ] \
      && awk -v leaf="$leaf" '
        /^[[:space:]]*#/ { next }
        /STD_CORE_HYBRID_PRODUCT_OBJS/ {
          line=$0
          sub(/#.*/,"",line)
          n=split(line, a, /[[:space:]\\]+/)
          for (i=1;i<=n;i++) if (a[i]==leaf) { found=1; exit 0 }
        }
        END { exit found ? 0 : 1 }
      ' "$b2mk" \
      && grep -qE '\$\(STD_CORE_HYBRID_PRODUCT_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
      && awk '
        /\$\(STD_CORE_HYBRID_PRODUCT_OBJS\):/ { hit=1; next }
        hit && /^[^#[:space:]\t]/ { exit 1 }
        hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
        END { exit found ? 0 : 1 }
      ' Makefile; then
      return 0
    fi
    return 1
  }

  if [ ! -f scripts/driver_seed_obj_catalog.sh ]; then
    bad "missing driver_seed_obj_catalog.sh"
  fi
  if ! grep -q 'RT_SEED_SLICE_OBJS' Makefile \
    && ! grep -q 'RT_SEED_SLICE_OBJS' mk/*.mk 2>/dev/null; then
    bad "RT_SEED_SLICE_OBJS not defined in Makefile/mk"
  fi
  if ! grep -q 'R1_CORE_SEED_OBJS' Makefile \
    && ! grep -q 'R1_CORE_SEED_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_CORE_SEED_OBJS not defined in Makefile/mk (wave749)"
  fi
  if ! grep -q 'R1_FRONTEND_GLUE_OBJS' Makefile \
    && ! grep -q 'R1_FRONTEND_GLUE_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_FRONTEND_GLUE_OBJS not defined in Makefile/mk (wave750)"
  fi
  if ! grep -q 'R1_MAIN_RUNTIME_OBJS' Makefile \
    && ! grep -q 'R1_MAIN_RUNTIME_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_MAIN_RUNTIME_OBJS not defined in Makefile/mk (wave751)"
  fi
  if ! grep -q 'R1_ALIAS_STUBS_OBJS' Makefile \
    && ! grep -q 'R1_ALIAS_STUBS_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_ALIAS_STUBS_OBJS not defined in Makefile/mk (wave752)"
  fi
  if ! grep -q 'R1_EXTRA_CFLAGS_OBJS' Makefile \
    && ! grep -q 'R1_EXTRA_CFLAGS_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_EXTRA_CFLAGS_OBJS not defined in Makefile/mk (wave753)"
  fi
  if ! grep -q 'R1_MISC_BASENAME_OBJS' Makefile \
    && ! grep -q 'R1_MISC_BASENAME_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_MISC_BASENAME_OBJS not defined in Makefile/mk (wave754)"
  fi
  if ! grep -q 'R1_SEED_MAP_OBJS' Makefile \
    && ! grep -q 'R1_SEED_MAP_OBJS' mk/*.mk 2>/dev/null; then
    bad "R1_SEED_MAP_OBJS not defined in Makefile/mk (wave755)"
  fi
  if ! grep -q 'R3_COLD_SEED_OBJS' Makefile \
    && ! grep -q 'R3_COLD_SEED_OBJS' mk/*.mk 2>/dev/null; then
    bad "R3_COLD_SEED_OBJS not defined in Makefile/mk (wave757)"
  fi
  if ! grep -q 'DRIVER_SEED_PANIC_OBJS' Makefile \
    && ! grep -q 'DRIVER_SEED_PANIC_OBJS' mk/*.mk 2>/dev/null; then
    bad "DRIVER_SEED_PANIC_OBJS not defined in Makefile/mk (wave760 R2 panic list)"
  fi

  check_family "RT_SEED_SLICE_OBJS" 5 "rt-slice" "basename" "src/runtime/"
  check_family "R1_CORE_SEED_OBJS" 5 "core-seed" "basename" "src/"
  check_family "R1_FRONTEND_GLUE_OBJS" 3 "frontend-glue" "frontend-glue" "src/"
  check_family "R1_MAIN_RUNTIME_OBJS" 7 "main-runtime" "main-runtime" "src/"
  # alias-stubs: mixed cwd-root and src/ paths; no single path prefix.
  check_family "R1_ALIAS_STUBS_OBJS" 8 "alias-stubs" "basename" ""
  # extra-cflags: mixed paths; multi-flag map.
  check_family "R1_EXTRA_CFLAGS_OBJS" 5 "extra-cflags" "extra-cflags" ""
  # misc-basename: mixed cwd-root / src/ / build_asm/ paths; pure basename.
  # Floor tracks mk (post_ship; was 9).
  check_family "R1_MISC_BASENAME_OBJS" 8 "misc-basename" "basename" ""
  # seed-map: mismatch stems + orch extras + thin_glue (wave758).
  # Floor tracks mk (post_ship; was 5).
  check_family "R1_SEED_MAP_OBJS" 4 "seed-map" "seed-map" ""
  # R3 cold-else: thin+rest leaves cold path = pure basename host-cc.
  check_family "R3_COLD_SEED_OBJS" 9 "r3-cold-seed" "basename" ""
  # R2 panic: catalog list must resolve; seed/asm pick must work on this host.
  {
    local panic_list panic_n=0 po pick
    if ! panic_list="$(catalog_key_list "DRIVER_SEED_PANIC_OBJS" 2>/dev/null)"; then
      bad "catalog cannot expand DRIVER_SEED_PANIC_OBJS (wave760)"
    else
      # shellcheck disable=SC2086
      for po in $panic_list; do
        [ -z "$po" ] && continue
        panic_n=$((panic_n + 1))
      done
      if [ "$panic_n" -lt 1 ]; then
        bad "DRIVER_SEED_PANIC_OBJS empty (wave760)"
      else
        note "catalog DRIVER_SEED_PANIC_OBJS n=$panic_n (r2-panic)"
      fi
      if ! pick="$(r2_panic_host_pick_src 2>/dev/null)"; then
        bad "r2_panic_host_pick_src failed on this host (wave760)"
      else
        note "r2-panic host pick: $pick"
      fi
    fi
  }
  # wave762: typeck_f64 + crt0 catalogs + host pick / map
  {
    local f64_list f64_n=0 fo f64_src crt0_list crt0_n=0 co
    if ! f64_list="$(catalog_key_list "DRIVER_SEED_TYPECK_F64_OBJS" 2>/dev/null)"; then
      bad "catalog cannot expand DRIVER_SEED_TYPECK_F64_OBJS (wave762)"
    else
      # shellcheck disable=SC2086
      for fo in $f64_list; do
        [ -z "$fo" ] && continue
        f64_n=$((f64_n + 1))
      done
      if [ "$f64_n" -lt 1 ]; then
        bad "DRIVER_SEED_TYPECK_F64_OBJS empty (wave762)"
      else
        note "catalog DRIVER_SEED_TYPECK_F64_OBJS n=$f64_n (r2-typeck-f64)"
      fi
      if ! f64_src="$(r2_typeck_f64_host_pick_src 2>/dev/null)"; then
        bad "r2_typeck_f64_host_pick_src failed on this host (wave762)"
      else
        note "r2-typeck-f64 host pick: $f64_src"
      fi
    fi
    if ! crt0_list="$(catalog_key_list "DRIVER_SEED_CRT0_OBJS" 2>/dev/null)"; then
      bad "catalog cannot expand DRIVER_SEED_CRT0_OBJS (wave762)"
    else
      # shellcheck disable=SC2086
      for co in $crt0_list; do
        [ -z "$co" ] && continue
        crt0_n=$((crt0_n + 1))
      done
      if [ "$crt0_n" -lt 1 ]; then
        bad "DRIVER_SEED_CRT0_OBJS empty (wave762)"
      else
        note "catalog DRIVER_SEED_CRT0_OBJS n=$crt0_n (r2-crt0)"
      fi
    fi
  }

  # Makefile thin: recipes must call this script (not inline $(CC) -c for swallowed leaves)
  if ! grep -q 'ensure_host_cc_seed_o\.sh' Makefile; then
    bad "Makefile must thin-call ensure_host_cc_seed_o.sh for R1 families"
  else
    note "Makefile thin-call present"
  fi
  # Core-seed leaves must not keep inline $(CC) -c recipes (thin only).
  if grep -A1 -E '^(src/diag\.o|src/runtime_link_abi\.o|src/runtime_c_import\.o|src/x_seed_bridge\.o|src/seed_link_compat\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile core-seed leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile core-seed leaves thin (no inline \$(CC) -c)"
  fi
  # Frontend-glue leaves must not keep inline $(CC) -c recipes.
  if grep -A1 -E '^(src/lexer/lexer\.o|src/ast/ast\.o|src/lsp/lsp_diag\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile frontend-glue leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile frontend-glue leaves thin (no inline \$(CC) -c)"
  fi
  # Main-runtime leaves must not keep inline $(CC) -c recipes.
  if grep -A1 -E '^(src/main\.o|src/main_x\.o|src/main_driver\.o|src/runtime\.o|src/runtime_x\.o|src/runtime_driver\.o|src/runtime_driver_no_c\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile main-runtime leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile main-runtime leaves thin (no inline \$(CC) -c)"
  fi
  # Alias-stubs leaves must not keep inline $(CC) -c recipes.
  if grep -A1 -E '^(x_frontend_link_alias\.o|ast_asm_bare_link_alias\.o|backend_asm_bare_link_alias\.o|backend_asm_strict_fallback_alias\.o|typeck_c_module_stubs\.o|src/asm/user_asm_seed_bridge\.o|src/asm/asm_backend_compat_stubs\.o|src/runtime_driver_strict_glue_stubs\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile alias-stubs leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile alias-stubs leaves thin (no inline \$(CC) -c)"
  fi
  # Extra-cflags leaves must not keep inline $(CC) -c recipes.
  if grep -A1 -E '^(src/runtime_pipeline_abi\.o|runtime_asm_io_stubs\.o|runtime_sqlite_glue\.o|runtime_sqlite_glue_stub\.o|src/asm/parser_asm_parse_expr_link\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile extra-cflags leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile extra-cflags leaves thin (no inline \$(CC) -c)"
  fi
  # Misc-basename leaves must not keep inline $(CC) -c recipes.
  if grep -A2 -E '^(runtime_link_abi_user_env\.o|runtime_channel_glue\.o|runtime_scheduler_glue\.o|runtime_kv_mmap_glue\.o|src/asm/backend_x86_64_enc_c\.o|src/asm/backend_arm64_enc_c\.o|src/lsp/lsp_diag_pipeline_ctx\.o|build_asm/pipeline_glue_strict_minimal\.o|src/asm/runtime_asm_build\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile misc-basename leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile misc-basename leaves thin (no inline \$(CC) -c)"
  fi
  # Seed-map leaves must not keep inline $(CC) -c recipes (incl. thin_glue wave758).
  if grep -A2 -E '^(src/driver/target_cpu\.o|src/ast/ast_seed\.o|pipeline_bootstrap_orchestration\.o|parser_asm_thin_glue\.o):' Makefile \
    | grep -qE '\$\(CC\).*-c seeds/'; then
    bad "Makefile seed-map leaves still have inline \$(CC) -c (must thin-call ensure)"
  else
    note "Makefile seed-map leaves thin (no inline \$(CC) -c; wave758 thin_glue)"
  fi
  # wave759: glue standalone target is $(ASM_GLUE_STANDALONE_O) — recipe must call ensure,
  # not residual cc_inc_tu (G.7 single body via ensure_one).
  # wave905: leaf joined multi-target $(R1_SEED_MAP_OBJS): FORCE try-heat (no per-leaf line).
  if awk '
    /^\$\(ASM_GLUE_STANDALONE_O\):|^build_asm\/pipeline_glue_standalone\.o:/ { in_t=1; next }
    in_t && /^[^[:space:]#]/ { in_t=0 }
    in_t { body = body $0 "\n" }
    END {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body !~ /cc_inc_tu\.sh/) exit 0
      exit 1
    }
  ' Makefile; then
    note "Makefile glue standalone thin (ensure; no cc_inc_tu; wave759)"
  elif grep -qE '\$\(R1_SEED_MAP_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && grep -qF 'build_asm/pipeline_glue_standalone.o' mk/driver_seed_r_lists.mk 2>/dev/null \
    && awk '
      /\$\(R1_SEED_MAP_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile glue standalone via multi-target R1_SEED_MAP try-heat (wave905)"
  else
    bad "Makefile ASM_GLUE_STANDALONE / pipeline_glue_standalone must thin-call ensure (wave759/905; no cc_inc_tu)"
  fi

  # G.7: list authority is catalog only — no hardcoded assignment of product lists.
  if grep -nE '^(export )?RT_SEED_SLICE_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode RT_SEED_SLICE_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_CORE_SEED_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_CORE_SEED_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_FRONTEND_GLUE_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_FRONTEND_GLUE_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_MAIN_RUNTIME_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_MAIN_RUNTIME_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_ALIAS_STUBS_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_ALIAS_STUBS_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_EXTRA_CFLAGS_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_EXTRA_CFLAGS_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_MISC_BASENAME_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_MISC_BASENAME_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R1_SEED_MAP_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R1_SEED_MAP_OBJS= in shell body"
  fi
  if grep -nE '^(export )?R3_COLD_SEED_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode R3_COLD_SEED_OBJS= in shell body"
  fi
  if grep -nE '^(export )?DRIVER_SEED_PANIC_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode DRIVER_SEED_PANIC_OBJS= in shell body (wave760)"
  fi
  if grep -nE '^(export )?DRIVER_SEED_TYPECK_F64_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode DRIVER_SEED_TYPECK_F64_OBJS= in shell body (wave762)"
  fi
  if grep -nE '^(export )?DRIVER_SEED_CRT0_OBJS=' "$0" 2>/dev/null \
    | grep -vqE '^\s*#|:[0-9]+:\s*#'; then
    bad "must not hardcode DRIVER_SEED_CRT0_OBJS= in shell body (wave762)"
  fi

  # wave760 + wave776 + wave915: Makefile panic must thin-call try-heat|try-r2-prefer|try-r2.
  # wave915: multi-target $(DRIVER_SEED_PANIC_OBJS): FORCE try-heat (list in r_lists).
  if grep -qE '\$\(DRIVER_SEED_PANIC_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_PANIC_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-r2-prefer|try-r2/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile R2 PANIC multi-target FORCE thin try-heat (wave915)"
  elif awk '
    /^runtime_panic\.o:/ { in_t=1; next }
    in_t && /^[^[:space:]#]/ { in_t=0 }
    in_t { body = body $0 "\n" }
    END {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-r2-prefer|try-r2|r2-panic|try_r2/) exit 0
      exit 1
    }
  ' Makefile; then
    note "Makefile runtime_panic thin-calls ensure try-r2-prefer/try-r2 (wave760/776)"
  else
    bad "Makefile runtime_panic.o must thin-call ensure try-heat|try-r2-prefer or try-r2 (wave776/915 multi-target)"
  fi
  # wave776: ban dual hybrid (inline xlang-c thin + seed rest + ld -r).
  # wave915: multi-target recipe body must also stay thin (no dual hybrid).
  if grep -qE '\$\(DRIVER_SEED_PANIC_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_PANIC_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 0 }
      hit {
        body = body $0 "\n"
      }
      END {
        if (body ~ /runtime_panic\.thin\.o/ && body ~ /runtime_panic\.rest\.o/) exit 1
        if (body ~ /XLANG_RUNTIME_PANIC_FROM_X/ && body ~ /ld -r/) exit 1
        if (body ~ /\.\/xlang-c/ && body ~ /runtime_panic/ && body ~ /ld -r/) exit 1
        exit 0
      }
    ' Makefile; then
    note "Makefile runtime_panic multi-target has no dual hybrid body (wave776/915)"
  elif awk '
    /^runtime_panic\.o:/ { in_t=1; next }
    in_t && /^[^[:space:]#]/ { in_t=0 }
    in_t { body = body $0 "\n" }
    END {
      if (body ~ /runtime_panic\.thin\.o/ && body ~ /runtime_panic\.rest\.o/) exit 1
      if (body ~ /XLANG_RUNTIME_PANIC_FROM_X/ && body ~ /ld -r/) exit 1
      if (body ~ /\.\/xlang-c/ && body ~ /runtime_panic/ && body ~ /ld -r/) exit 1
      exit 0
    }
  ' Makefile; then
    note "Makefile runtime_panic has no dual hybrid body (wave776)"
  else
    bad "Makefile runtime_panic.o still has dual hybrid PREFER body (wave776)"
  fi
  if ! grep -q 'try_ensure_r2_prefer_one\|try-r2-prefer' "$0"; then
    bad "try-r2-prefer / try_ensure_r2_prefer_one missing (wave776)"
  else
    note "try-r2-prefer helper present (wave776)"
  fi

  # wave762/914: typeck_f64 must thin-call try-heat|try-r2 (no inline $(CC) -c).
  # wave914: multi-target $(DRIVER_SEED_TYPECK_F64_OBJS): FORCE try-heat (UNAME gates dropped).
  if grep -qE '\$\(DRIVER_SEED_TYPECK_F64_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_TYPECK_F64_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-r2/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile R2 TYPECK_F64 multi-target FORCE thin try-heat (wave914)"
  elif awk '
    /^src\/typeck\/typeck_f64_bits\.o:/ { in_t=1; next }
    in_t && /^[^[:space:]#]/ { in_t=0 }
    in_t { body = body $0 "\n" }
    END {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-r2/) exit 0
      exit 1
    }
  ' Makefile; then
    note "Makefile typeck_f64_bits thin-calls ensure try-r2 (wave762)"
  else
    bad "Makefile typeck_f64_bits.o must thin-call ensure try-heat|try-r2 (wave762/914 multi-target)"
  fi
  # Host MAIN_LINK crt0 (Darwin arm64 / Linux x86_64 / …) — per-leaf or wave913 multi-target.
  # wave913: multi-target $(DRIVER_SEED_CRT0_OBJS): FORCE try-heat covers all six catalog leaves
  # (no per-leaf dual). Accept multi-target OR historical per-leaf try-heat|try-r2.
  if grep -qE '\$\(DRIVER_SEED_CRT0_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_CRT0_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-r2/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile R2 CRT0 multi-target FORCE thin try-heat (wave913; covers six)"
  elif awk '
    /^src\/asm\/crt0_[a-z0-9_]+\.o:/ { in_t=1; body=""; next }
    in_t && /^[^[:space:]#]/ {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-r2/) found=1
      in_t=0
    }
    in_t { body = body $0 "\n" }
    END { if (found) exit 0; exit 1 }
  ' Makefile; then
    note "Makefile crt0 leaves thin-call ensure try-r2 (wave762)"
  else
    bad "Makefile crt0_*.o recipes must thin-call ensure try-heat|try-r2 (wave762/913 multi-target)"
  fi

  if [ "$fail" -ne 0 ]; then
    echo "ensure_host_cc_seed_o: --check FAILED" >&2
    exit 1
  fi
  # wave756: try-r1 entry must exist (R4 pure-R1 body helper)
  if ! grep -q 'try_ensure_r1_one\|try-r1' "$0"; then
    bad "try-r1 / try_ensure_r1_one missing (wave756 R4 pure-R1)"
  else
    note "try-r1 pure-R1 helper present (wave756)"
  fi
  # wave757: try-r3-cold entry must exist (R3 cold-else body helper)
  if ! grep -q 'try_ensure_r3_cold_one\|try-r3-cold' "$0"; then
    bad "try-r3-cold / try_ensure_r3_cold_one missing (wave757 R3 cold-else)"
  else
    note "try-r3-cold R3 cold-else helper present (wave757)"
  fi
  # wave763: try-r3-prefer PREFER thin+rest product path
  if ! grep -q 'try_ensure_r3_prefer_one\|try-r3-prefer' "$0"; then
    bad "try-r3-prefer / try_ensure_r3_prefer_one missing (wave763 R3 PREFER thin)"
  else
    note "try-r3-prefer R3 PREFER thin helper present (wave763)"
  fi
  if ! grep -q 'r3_prefer_leaf_spec\|ensure_r3_prefer_one' "$0"; then
    bad "r3 prefer body missing (wave763)"
  else
    note "r3-prefer leaf map + body present (wave763)"
  fi
  # Makefile R3_COLD nine must thin-call try-heat|try-r3-prefer (no inline thin+rest).
  # wave906: multi-target $(R3_COLD_SEED_OBJS): FORCE + try-heat covers all nine
  # (G.7 有则补全 list; no per-leaf dual). Accept multi-target OR historical per-leaf.
  _r3c_multi=0
  if grep -qE '\$\(R3_COLD_SEED_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(R3_COLD_SEED_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-r3-prefer/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    _r3c_multi=1
    note "Makefile R3_COLD multi-target FORCE thin try-heat (wave906; covers nine)"
  fi
  for leaf in \
    src/runtime_io_abi.o \
    src/runtime_driver_abi.o \
    src/runtime_driver_diagnostic.o \
    src/asm/simd_enc.o \
    src/asm/simd_loop.o \
    src/asm/backend_enc_dispatch.o \
    src/asm/backend_arch_emit_dispatch.o \
    src/asm/backend_try_inline_dispatch.o \
    src/asm/backend_call_dispatch.o
  do
    if [ "$_r3c_multi" -eq 1 ]; then
      # Multi-target owns thin-call; still ban per-leaf dual recipe if present.
      if grep -qE "^${leaf}:" Makefile 2>/dev/null; then
        bad "Makefile $leaf still has per-leaf target under R3_COLD multi-target (wave906)"
      fi
      continue
    fi
    if awk -v t="$leaf" '
      $0 ~ "^" t ":" {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-r3-prefer/) exit 0
        exit 1
      }
    ' Makefile; then
      note "Makefile $leaf thin-calls ensure try-r3-prefer (wave763)"
    else
      bad "Makefile $leaf must thin-call ensure try-heat|try-r3-prefer (wave763/906)"
    fi
    # No residual inline ld -r thin+rest in the leaf recipe body.
    if awk -v t="$leaf" '
      $0 ~ "^" t ":" {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /ld -r/ && body ~ /_rest\.o/) exit 1
        exit 0
      }
    ' Makefile; then
      :
    else
      bad "Makefile $leaf still has inline ld -r thin+rest (wave763)"
    fi
  done
  # wave764: g05 product daily path must thin-call r3-prefer-family (no dual hybrid
  # for R3_COLD nine: rio / rdabi / rdd / simd_* / backend_*).
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'r3-prefer-family\|r3_prefer_family' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure r3-prefer-family (wave764)"
    else
      bad "g05_ensure must thin-call ensure r3-prefer-family for R3_COLD (wave764)"
    fi
    # Dual body residual: g05 must not re-open inline hybrid for R3_COLD leaves.
    if grep -qE 'g05_rio_thin|g05_rdabi_thin|g05_rdd_thin|g05_simd_enc_thin|g05_bed_thin|G-02f-334：runtime_io_abi' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has R3_COLD dual hybrid body (wave764)"
    else
      note "g05_ensure R3_COLD dual hybrid body removed (wave764)"
    fi
    # wave764 full ladder in leaf map (simd/backend full.x field present).
    if grep -q 'XLANG_SIMD_ENC_FROM_X' "$0" \
      && grep -q 'r3_prefer_try_step' "$0"; then
      note "try-r3-prefer full→thin ladder present (wave764)"
    else
      bad "try-r3-prefer must gain full→thin ladder (wave764)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave764 g05 gate)"
  fi
  # wave765: try-labi-prefer labi multi-slice (g05 + Makefile thin-call; no dual hybrid)
  if ! grep -q 'try_ensure_labi_prefer_one\|try-labi-prefer' "$0"; then
    bad "try-labi-prefer / try_ensure_labi_prefer_one missing (wave765 labi multi-slice)"
  else
    note "try-labi-prefer labi multi-slice helper present (wave765)"
  fi
  if ! grep -q 'ensure_labi_prefer_one\|labi_prefer_try_x_to_o' "$0"; then
    bad "labi prefer body missing (wave765)"
  else
    note "labi-prefer multi-slice body present (wave765)"
  fi
  if makefile_leaf_try_heat_ok "src/runtime_link_abi.o" 'try-heat|try-labi-prefer'; then
    note "Makefile src/runtime_link_abi.o thin-calls ensure try-labi-prefer (wave765/899 multi)"
  else
    bad "Makefile src/runtime_link_abi.o must thin-call ensure try-heat|try-labi-prefer (wave765/899)"
  fi
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-labi-prefer\|labi-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-labi-prefer (wave765)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-labi-prefer for labi (wave765)"
    fi
    if grep -qE 'g05_labi_l0\.|_labi_l0_seed=seeds/labi_path_pure|_labi_rest_defs=.*LABI_PATH_PURE' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has labi multi-slice dual hybrid body (wave765)"
    else
      note "g05_ensure labi multi-slice dual hybrid body removed (wave765)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave765 g05 gate)"
  fi
  # wave766: try-rt-prefer rt multi-slice (g05 + Makefile thin-call; no dual hybrid)
  if ! grep -q 'try_ensure_rt_prefer_one\|try-rt-prefer' "$0"; then
    bad "try-rt-prefer / try_ensure_rt_prefer_one missing (wave766 rt multi-slice)"
  else
    note "try-rt-prefer rt multi-slice helper present (wave766)"
  fi
  if ! grep -q 'ensure_rt_prefer_one\|rt_prefer_try_x_to_o' "$0"; then
    bad "rt prefer body missing (wave766)"
  else
    note "rt-prefer multi-slice body present (wave766)"
  fi
  if makefile_leaf_try_heat_ok "src/runtime_driver_no_c.o" 'try-heat|try-rt-prefer'; then
    note "Makefile src/runtime_driver_no_c.o thin-calls ensure try-rt-prefer (wave766/901 multi)"
  else
    bad "Makefile src/runtime_driver_no_c.o must thin-call ensure try-heat|try-rt-prefer (wave766/901)"
  fi
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-rt-prefer\|rt-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-rt-prefer (wave766)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-rt-prefer for rt multi-slice (wave766)"
    fi
    # Dual body residual: g05 must not re-open inline rt multi-slice hybrid.
    if grep -qE '_rt_content_seed=seeds/rt_content|_rt_rest_defs=.*RT_CONTENT_FROM_X|g05_rt_content\.XXXXXX' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has rt multi-slice dual hybrid body (wave766)"
    else
      note "g05_ensure rt multi-slice dual hybrid body removed (wave766)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave766 g05 gate)"
  fi
  # wave767: try-pipeline-abi-prefer + try-ldpc-prefer (g05 + Makefile thin-call)
  if ! grep -q 'try_ensure_pipeline_abi_prefer_one\|try-pipeline-abi-prefer' "$0"; then
    bad "try-pipeline-abi-prefer / try_ensure_pipeline_abi_prefer_one missing (wave767)"
  else
    note "try-pipeline-abi-prefer helper present (wave767)"
  fi
  if ! grep -q 'ensure_pipeline_abi_prefer_one' "$0"; then
    bad "pipeline_abi prefer body missing (wave767)"
  else
    note "pipeline-abi-prefer body present (wave767)"
  fi
  if ! grep -q 'try_ensure_ldpc_prefer_one\|try-ldpc-prefer' "$0"; then
    bad "try-ldpc-prefer / try_ensure_ldpc_prefer_one missing (wave767)"
  else
    note "try-ldpc-prefer helper present (wave767)"
  fi
  if ! grep -q 'ensure_ldpc_prefer_one' "$0"; then
    bad "ldpc prefer body missing (wave767)"
  else
    note "ldpc-prefer body present (wave767)"
  fi
  if makefile_leaf_try_heat_ok "src/runtime_pipeline_abi.o" 'try-heat|try-pipeline-abi-prefer'; then
    note "Makefile src/runtime_pipeline_abi.o thin-calls ensure try-pipeline-abi-prefer (wave767/903 multi)"
  else
    bad "Makefile src/runtime_pipeline_abi.o must thin-call ensure try-heat|try-pipeline-abi-prefer (wave767/903)"
  fi
  if makefile_leaf_try_heat_ok "src/lsp/lsp_diag_pipeline_ctx.o" 'try-heat|try-ldpc-prefer'; then
    note "Makefile src/lsp/lsp_diag_pipeline_ctx.o thin-calls ensure try-ldpc-prefer (wave767/904 multi)"
  else
    bad "Makefile src/lsp/lsp_diag_pipeline_ctx.o must thin-call ensure try-heat|try-ldpc-prefer (wave767/904)"
  fi
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-pipeline-abi-prefer\|pipeline-abi-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'try-ldpc-prefer\|ldpc-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-pipeline-abi-prefer + try-ldpc-prefer (wave767)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-pipeline-abi-prefer and try-ldpc-prefer (wave767)"
    fi
    # Dual body residual: g05 must not re-open inline pipeline_abi / ldpc hybrid.
    if grep -qE '_rpabi=seeds/runtime_pipeline_abi\.from_x\.c|_ldpc=seeds/lsp_diag_pipeline_ctx\.from_x\.c' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has pipeline_abi/ldpc dual hybrid body (wave767)"
    else
      note "g05_ensure pipeline_abi/ldpc dual hybrid body removed (wave767)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave767 g05 gate)"
  fi
  # wave768: try-target-cpu-prefer (g05 + Makefile thin-call)
  if ! grep -q 'try_ensure_target_cpu_prefer_one\|try-target-cpu-prefer' "$0"; then
    bad "try-target-cpu-prefer / try_ensure_target_cpu_prefer_one missing (wave768)"
  else
    note "try-target-cpu-prefer helper present (wave768)"
  fi
  if ! grep -q 'ensure_target_cpu_prefer_one' "$0"; then
    bad "target_cpu prefer body missing (wave768)"
  else
    note "target-cpu-prefer body present (wave768)"
  fi
  if makefile_leaf_try_heat_ok "src/driver/target_cpu.o" 'try-heat|try-target-cpu-prefer'; then
    note "Makefile src/driver/target_cpu.o thin-calls ensure try-target-cpu-prefer (wave768/905 multi)"
  else
    bad "Makefile src/driver/target_cpu.o must thin-call ensure try-heat|try-target-cpu-prefer (wave768/905)"
  fi
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-target-cpu-prefer\|target-cpu-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-target-cpu-prefer (wave768)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-target-cpu-prefer (wave768)"
    fi
    # Dual body residual: g05 must not re-open inline target_cpu flags hybrid.
    if grep -qE '_tcflags_x=src/driver/target_cpu_flags\.x|_tcpure=seeds/target_cpu_pure\.from_x\.c' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has target_cpu dual hybrid body (wave768)"
    else
      note "g05_ensure target_cpu dual hybrid body removed (wave768)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave768 g05 gate)"
  fi
  # wave769: try-l2-asm-prefer (g05 + Makefile thin-call; three L2 asm leaves)
  if ! grep -q 'try_ensure_l2_asm_prefer_one\|try-l2-asm-prefer' "$0"; then
    bad "try-l2-asm-prefer / try_ensure_l2_asm_prefer_one missing (wave769)"
  else
    note "try-l2-asm-prefer helper present (wave769)"
  fi
  if ! grep -q 'ensure_l2_asm_prefer_one\|l2_asm_prefer_spec_for_out' "$0"; then
    bad "l2-asm prefer body/table missing (wave769)"
  else
    note "l2-asm-prefer table body present (wave769)"
  fi
  for _l2_leaf in \
    src/asm/user_asm_seed_bridge.o \
    src/asm/backend_x86_64_enc_c.o \
    src/asm/asm_backend_compat_stubs.o; do
    if makefile_leaf_try_heat_ok "$_l2_leaf" 'try-heat|try-l2-asm-prefer'; then
      note "Makefile $_l2_leaf thin-calls ensure try-l2-asm-prefer (wave769/multi)"
    else
      bad "Makefile $_l2_leaf must thin-call ensure try-heat|try-l2-asm-prefer (wave769/multi)"
    fi
  done
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-l2-asm-prefer\|l2-asm-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-l2-asm-prefer (wave769)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-l2-asm-prefer for L2 asm three (wave769)"
    fi
    # Dual body residual: g05 must not re-open inline uasb/bxec/abcs hybrid.
    if grep -qE '_uasb_seed=|_bxec_seed=|_abcs_seed=|user_asm_seed_bridge ← thin|_bxec_thin_o=|_abcs_thin_o=' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has L2 asm dual hybrid body (wave769)"
    else
      note "g05_ensure L2 asm dual hybrid body removed (wave769)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave769 g05 gate)"
  fi
  # wave770: try-async-prefer (g05 + Makefile thin-call; three async leaves)
  if ! grep -q 'try_ensure_async_prefer_one\|try-async-prefer' "$0"; then
    bad "try-async-prefer / try_ensure_async_prefer_one missing (wave770)"
  else
    note "try-async-prefer helper present (wave770)"
  fi
  if ! grep -q 'ensure_async_prefer_one\|async_prefer_spec_for_out' "$0"; then
    bad "async prefer body/table missing (wave770)"
  else
    note "async-prefer table body present (wave770)"
  fi
  for _async_leaf in \
    src/async/async_liveness.o \
    src/async/async_cps_codegen.o \
    src/async/async_asm_pool.o; do
    if makefile_leaf_try_heat_ok "$_async_leaf" 'try-heat|try-async-prefer'; then
      note "Makefile $_async_leaf thin-calls ensure try-async-prefer (wave770/907 multi)"
    else
      bad "Makefile $_async_leaf must thin-call ensure try-heat|try-async-prefer (wave770/907)"
    fi
  done
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-async-prefer\|async-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-async-prefer (wave770)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-async-prefer for async three (wave770)"
    fi
    # Dual body residual: g05 must not re-open inline async hybrid.
    if grep -qE '_aliv_seed=|_acps_seed=|_aap_seed=|async_liveness PREFER|_aliv_x_o=|_acps_x_o=|_aap_x_o=' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has async dual hybrid body (wave770)"
    else
      note "g05_ensure async dual hybrid body removed (wave770)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave770 g05 gate)"
  fi
  # wave771 + wave775: try-other-l2-prefer (g05 four + Makefile five incl. fmt_core)
  if ! grep -q 'try_ensure_other_l2_prefer_one\|try-other-l2-prefer' "$0"; then
    bad "try-other-l2-prefer / try_ensure_other_l2_prefer_one missing (wave771)"
  else
    note "try-other-l2-prefer helper present (wave771/775)"
  fi
  if ! grep -q 'ensure_other_l2_prefer_one\|other_l2_prefer_spec_for_out' "$0"; then
    bad "other-l2 prefer body/table missing (wave771)"
  else
    note "other-l2-prefer table body present (wave771/775)"
  fi
  if ! grep -q 'fmt_core' "$0"; then
    bad "fmt_core leaf_kind missing (wave775 fmt_check_cmd.o)"
  else
    note "fmt_core leaf_kind present (wave775)"
  fi
  if ! grep -q 'G05_X_O_WEAK_FUNCS' "$0"; then
    bad "G05_X_O_WEAK_FUNCS named-weak missing in rt_prefer (wave771 slc)"
  else
    note "G05_X_O_WEAK_FUNCS named-weak present (wave771)"
  fi
  for _ol2_leaf in \
    src/seed_link_compat.o \
    src/runtime_driver_strict_glue_stubs.o \
    src/driver/fmt_check_cmd_driver.o \
    src/driver/fmt_check_cmd.o \
    src/lsp/lsp_diag.o; do
    if makefile_leaf_try_heat_ok "$_ol2_leaf" 'try-heat|try-other-l2-prefer'; then
      note "Makefile $_ol2_leaf thin-calls ensure try-other-l2-prefer (wave771/775/multi)"
    else
      bad "Makefile $_ol2_leaf must thin-call ensure try-heat|try-other-l2-prefer (wave771/775/multi)"
    fi
  done
  # wave775: ban re-opened Makefile dual hybrid body for non-driver fmt.o
  if awk '
    $0 ~ /^src\/driver\/fmt_check_cmd\.o:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab {body = body $0 "\n"}
    END {
      if (body ~ /mktemp/ && body ~ /fmt_check_cmd_thin\.o/) exit 0
      exit 1
    }
  ' Makefile; then
    bad "Makefile fmt_check_cmd.o still has dual hybrid body (wave775)"
  else
    note "Makefile fmt_check_cmd.o dual hybrid body removed (wave775)"
  fi
  if [ -f scripts/g05_ensure_relink_prereqs.sh ]; then
    if grep -q 'try-other-l2-prefer\|other-l2-prefer' scripts/g05_ensure_relink_prereqs.sh \
      && grep -q 'ensure_host_cc_seed_o.sh' scripts/g05_ensure_relink_prereqs.sh; then
      note "g05_ensure thin-calls ensure try-other-l2-prefer (wave771)"
    else
      bad "g05_ensure must thin-call ensure try-heat|try-other-l2-prefer for other L2 four (wave771)"
    fi
    # Dual body residual: g05 must not re-open inline slc/strict/fmt/lsp hybrid.
    if grep -qE '_slc_o=|_slc_seed=|_rdss=|_rdss_thin_x=|_fcc=|_fcc_thin_x=|_lspg=|_lspg_thin_x=' \
      scripts/g05_ensure_relink_prereqs.sh; then
      bad "g05_ensure still has other L2 dual hybrid body (wave771)"
    else
      note "g05_ensure other L2 dual hybrid body removed (wave771)"
    fi
  else
    bad "scripts/g05_ensure_relink_prereqs.sh missing (wave771 g05 gate)"
  fi
  # wave779: try-runtime-os-prefer B1 23 runtime_* OS/glue dual hybrid
  if ! grep -q 'try_ensure_runtime_os_prefer_one\|try-runtime-os-prefer' "$0"; then
    bad "try-runtime-os-prefer / try_ensure_runtime_os_prefer_one missing (wave779)"
  else
    note "try-runtime-os-prefer helper present (wave779)"
  fi
  if ! grep -q 'runtime_os_prefer_spec_for_out\|ensure_runtime_os_prefer_one' "$0"; then
    bad "runtime-os prefer body/table missing (wave779)"
  else
    note "runtime-os-prefer table body present (wave779)"
  fi
  # Count table members (must stay 23 — heat inventory wave777 B1).
  _rtos_n=0
  for _rtos_leaf in \
    runtime_test_fn_invoke.o \
    runtime_random_fill.o \
    runtime_compress_zlib_glue.o \
    runtime_time_os.o \
    runtime_queue_contention.o \
    runtime_dynlib_os.o \
    runtime_env_os.o \
    runtime_backtrace_platform.o \
    runtime_log_os.o \
    runtime_math_libm.o \
    runtime_atomic_glue.o \
    runtime_net_udp_batch.o \
    runtime_net_workers.o \
    runtime_sync_os.o \
    runtime_sync_lock_diag_tls.o \
    runtime_thread_glue.o \
    runtime_http_glue.o \
    runtime_tls_mbedtls_bio.o \
    runtime_arrow_simd_glue.o \
    runtime_crypto_inc_glue.o \
    runtime_ed25519_ref10_glue.o \
    runtime_process_argv.o \
    runtime_process_os_glue.o; do
    if [ -n "$(runtime_os_prefer_spec_for_out "$_rtos_leaf")" ]; then
      _rtos_n=$((_rtos_n + 1))
    else
      bad "runtime_os_prefer_spec_for_out missing $_rtos_leaf (wave779)"
    fi
    # wave908: multi-target $(B1_RUNTIME_OS_SEED_OBJS): FORCE try-heat OR per-leaf
    if makefile_leaf_try_heat_ok "$_rtos_leaf" 'try-heat|try-runtime-os-prefer'; then
      note "Makefile $_rtos_leaf thin-calls ensure try-heat|try-runtime-os-prefer (wave779/908)"
    else
      bad "Makefile $_rtos_leaf must thin-call ensure try-heat|try-runtime-os-prefer (wave779/908)"
    fi
    # Ban re-opened dual hybrid body (mktemp + thin.o / rest.o inline).
    if awk -v leaf="$_rtos_leaf" '
      $0 ~ ("^" leaf ":") {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /mktemp/ && body ~ /(thin\.o|_thin\.o|rest\.o|_rest\.o)/) exit 0
        if (body ~ /XLANG_KEEP_C=1/ && body ~ /xlang-c/) exit 0
        exit 1
      }
    ' Makefile; then
      bad "Makefile $_rtos_leaf still has dual hybrid body (wave779)"
    fi
  done
  if [ "$_rtos_n" -ne 23 ]; then
    bad "runtime-os prefer table size $_rtos_n != 23 (wave779 B1 heat)"
  else
    note "runtime-os prefer table has 23 members (wave779 B1)"
  fi
  # wave780: try-std-core-prefer B2 5 std/core product hybrid
  if ! grep -q 'try_ensure_std_core_prefer_one\|try-std-core-prefer' "$0"; then
    bad "try-std-core-prefer / try_ensure_std_core_prefer_one missing (wave780)"
  else
    note "try-std-core-prefer helper present (wave780)"
  fi
  if ! grep -q 'std_core_prefer_spec_for_out\|ensure_std_core_prefer_one' "$0"; then
    bad "std-core prefer body/table missing (wave780)"
  else
    note "std-core-prefer table body present (wave780)"
  fi
  # wave897: multi-target $(STD_CORE_HYBRID_PRODUCT_OBJS) + mk list (no per-leaf target line).
  # Accept A) legacy per-leaf `^OUT:` FORCE+try-heat, or B) OUT in mk list + multi-target rule.
  _SC_MK="mk/std_core_hybrid_product_objs.mk"
  [ -f "$_SC_MK" ] || _SC_MK="compiler/mk/std_core_hybrid_product_objs.mk"
  _sc_n=0
  _sc_multi=0
  if [ -f "$_SC_MK" ] && grep -qE '\$\(STD_CORE_HYBRID_PRODUCT_OBJS\):[[:space:]]*FORCE' Makefile; then
    if awk '
      /\$\(STD_CORE_HYBRID_PRODUCT_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-std-core-prefer/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
      _sc_multi=1
      note "Makefile multi-target STD_CORE_HYBRID_PRODUCT_OBJS FORCE+try-heat (wave897)"
    fi
  fi
  for _sc_leaf in \
    ../std/process/process.o \
    ../std/path/path.o \
    ../std/runtime/runtime.o \
    ../std/net/net.o \
    ../core/slice/slice.o; do
    if [ -n "$(std_core_prefer_spec_for_out "$_sc_leaf")" ]; then
      _sc_n=$((_sc_n + 1))
    else
      bad "std_core_prefer_spec_for_out missing $_sc_leaf (wave780)"
    fi
    _ok_t=0
    if awk -v leaf="$_sc_leaf" '
      $0 ~ ("^" leaf ":") {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-std-core-prefer/) exit 0
        exit 1
      }
    ' Makefile; then
      _ok_t=1
    elif [ "$_sc_multi" -eq 1 ] && grep -qF "$_sc_leaf" "$_SC_MK" 2>/dev/null; then
      _ok_t=1
    fi
    if [ "$_ok_t" -eq 1 ]; then
      note "Makefile $_sc_leaf thin-calls ensure try-heat|try-std-core-prefer (wave780/897)"
    else
      bad "Makefile $_sc_leaf must thin-call ensure try-heat|try-std-core-prefer (wave780/897)"
    fi
    # Ban re-opened hybrid: only scan recipe lines (leading tab), not following
    # comment blocks (those often mention historic xlang-c / PREFER).
    # wave897 multi-target path: no per-leaf body — skip dual-hybrid scan when covered by mk.
    if [ "$_sc_multi" -eq 1 ] && grep -qF "$_sc_leaf" "$_SC_MK" 2>/dev/null \
      && ! grep -qE "^${_sc_leaf}:" Makefile 2>/dev/null; then
      :
    elif awk -v leaf="$_sc_leaf" '
      $0 ~ ("^" leaf ":") {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab && /^\t/ {body = body $0 "\n"}
      END {
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-std-core-prefer/ && body !~ /xlang_compile_std_x\.sh/ && body !~ /\$\(CC\)/) exit 1
        if (body ~ /XLANG_KEEP_C=1/ && body ~ /xlang-c/ && body !~ /ensure_host_cc_seed_o/) exit 0
        if (body ~ /\$\(CC\)/ && body ~ /-c seeds\//) exit 0
        if (body ~ /xlang_compile_std_x\.sh/ && body ~ /net_dns_fast/) exit 0
        exit 1
      }
    ' Makefile; then
      bad "Makefile $_sc_leaf still has dual hybrid body (wave780)"
    fi
  done
  if [ "$_sc_n" -ne 5 ]; then
    bad "std-core prefer table size $_sc_n != 5 (wave780 B2 heat)"
  else
    note "std-core prefer table has 5 members (wave780 B2; wave897 multi-target)"
  fi
  # wave781: try-lsp-sat-prefer B3 2 LSP satellite hybrid
  if ! grep -q 'try_ensure_lsp_sat_prefer_one\|try-lsp-sat-prefer' "$0"; then
    bad "try-lsp-sat-prefer / try_ensure_lsp_sat_prefer_one missing (wave781)"
  else
    note "try-lsp-sat-prefer helper present (wave781)"
  fi
  if ! grep -q 'lsp_sat_prefer_spec_for_out\|ensure_lsp_sat_prefer_one' "$0"; then
    bad "lsp-sat prefer body/table missing (wave781)"
  else
    note "lsp-sat-prefer table body present (wave781)"
  fi
  _ls_n=0
  # wave911: multi-target $(B3_LSP_SAT_SEED_OBJS): FORCE try-heat covers both
  # (no per-leaf dual). Accept multi-target OR historical per-leaf.
  if grep -qE '\$\(B3_LSP_SAT_SEED_OBJS\):[[:space:]]*FORCE' Makefile \
    && awk '
      /\$\(B3_LSP_SAT_SEED_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile B3_LSP_SAT multi-target FORCE thin try-heat (wave911; covers two)"
  fi
  for _ls_leaf in \
    src/lsp/lsp_diag_pipeline_sizes_nostub.o \
    src/lsp/lsp_diag_stubs_no_c.o; do
    if [ -n "$(lsp_sat_prefer_spec_for_out "$_ls_leaf")" ]; then
      _ls_n=$((_ls_n + 1))
    else
      bad "lsp_sat_prefer_spec_for_out missing $_ls_leaf (wave781)"
    fi
    if makefile_leaf_try_heat_ok "$_ls_leaf" 'try-heat|try-lsp-sat-prefer'; then
      note "Makefile $_ls_leaf thin-calls try-heat|try-lsp-sat-prefer (wave781/911)"
    else
      bad "Makefile $_ls_leaf must thin-call ensure try-heat|try-lsp-sat-prefer (wave781/911)"
    fi
    # Ban re-opened hybrid: only scan tab-prefixed recipe lines (not # comments).
    # Multi-target: no per-leaf body — skip dual-body scan when leaf only via list.
    if grep -qE "^${_ls_leaf}:" Makefile 2>/dev/null; then
      if awk -v leaf="$_ls_leaf" '
        $0 ~ ("^" leaf ":") {grab=1; next}
        grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
        grab && /^\t/ {body = body $0 "\n"}
        END {
          if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-lsp-sat-prefer/ && body !~ /\$\(CC\)/ && body !~ /xlang-c/) exit 1
          if (body ~ /xlang-c/ && body !~ /ensure_host_cc_seed_o/) exit 0
          if (body ~ /\$\(CC\)/ && body ~ /-c seeds\//) exit 0
          if (body ~ /mktemp/ && body ~ /(thin\.o|_thin\.o|rest\.o|_rest\.o)/) exit 0
          exit 1
        }
      ' Makefile; then
        bad "Makefile $_ls_leaf still has dual hybrid body (wave781)"
      fi
    fi
  done
  if [ "$_ls_n" -ne 2 ]; then
    bad "lsp-sat prefer table size $_ls_n != 2 (wave781 B3 heat)"
  else
    note "lsp-sat prefer table has 2 members (wave781 B3; wave911 multi-target)"
  fi
  # wave782: try-gen-c-to-o B4 5 gen.c → .o bootstrap
  if ! grep -q 'try_ensure_gen_c_to_o_one\|try-gen-c-to-o' "$0"; then
    bad "try-gen-c-to-o / try_ensure_gen_c_to_o_one missing (wave782)"
  else
    note "try-gen-c-to-o helper present (wave782)"
  fi
  if ! grep -q 'gen_c_to_o_spec_for_out' "$0"; then
    bad "gen_c_to_o table missing (wave782)"
  else
    note "gen-c-to-o table present (wave782)"
  fi
  if ! grep -q 'build_lexer_x\|lexer_x.o' scripts/ensure_gen_x_o.sh; then
    bad "ensure_gen_x_o.sh missing B4 lexer_x map (wave782)"
  else
    note "ensure_gen_x_o B4 maps present (wave782)"
  fi
  _b4_n=0
  # wave910/295: multi-target $(GEN_C_TO_O_SEED_OBJS): FORCE try-heat covers all four
  # (no per-leaf dual; stubs2 left). Accept multi-target OR historical per-leaf.
  if grep -qE '\$\(GEN_C_TO_O_SEED_OBJS\):[[:space:]]*FORCE' Makefile \
    && awk '
      /\$\(GEN_C_TO_O_SEED_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile GEN_C_TO_O multi-target FORCE thin try-heat (wave910/295; covers four)"
  fi
  for _b4_leaf in lexer_x.o ast_gen2.o driver_x.o preprocess_x.o; do
    if [ -n "$(gen_c_to_o_spec_for_out "$_b4_leaf")" ]; then
      _b4_n=$((_b4_n + 1))
    else
      bad "gen_c_to_o_spec_for_out missing $_b4_leaf (wave782/295)"
    fi
    if makefile_leaf_try_heat_ok "$_b4_leaf" 'try-heat|try-gen-c-to-o'; then
      note "Makefile $_b4_leaf thin-calls try-heat|try-gen-c-to-o (wave782/796/910/295)"
    else
      bad "Makefile $_b4_leaf must thin-call ensure try-heat|try-gen-c-to-o (wave782/910/295)"
    fi
    # Ban re-opened inline $(CC) -c body on recipe lines (comments OK).
    # wave910: multi-target has no per-leaf recipe — only check if per-leaf line exists.
    if grep -qE "^${_b4_leaf}:" Makefile 2>/dev/null; then
      if awk -v leaf="$_b4_leaf" '
        $0 ~ ("^" leaf ":") {grab=1; next}
        grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
        grab && /^\t/ {body = body $0 "\n"}
        END {
          if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-gen-c-to-o/ && body !~ /\$\(CC\)/) exit 1
          if (body ~ /\$\(CC\)/ && body ~ /-c /) exit 0
          if (body ~ /sync_lexer_gen_token_enum/ && body !~ /ensure_host_cc_seed_o/) exit 0
          exit 1
        }
      ' Makefile; then
        bad "Makefile $_b4_leaf still has inline host-cc body (wave782)"
      fi
    fi
  done
  if [ "$_b4_n" -ne 4 ]; then
    bad "gen-c-to-o table size $_b4_n != 4 (wave782/295 B4 heat)"
  else
    note "gen-c-to-o table has 4 members (wave295 B4; stubs2 left)"
  fi
  # wave783: try-cfg-eval-ladder B5 multi-ladder (1 leaf)
  if ! grep -q 'try_ensure_cfg_eval_ladder_one\|try-cfg-eval-ladder' "$0"; then
    bad "try-cfg-eval-ladder / try_ensure_cfg_eval_ladder_one missing (wave783)"
  else
    note "try-cfg-eval-ladder helper present (wave783)"
  fi
  if ! grep -q 'cfg_eval_ladder_spec_for_out\|ensure_cfg_eval_ladder_one' "$0"; then
    bad "cfg_eval ladder table/body missing (wave783)"
  else
    note "cfg-eval ladder table present (wave783)"
  fi
  if [ -n "$(cfg_eval_ladder_spec_for_out "src/lexer/cfg_eval.o")" ]; then
    note "cfg_eval_ladder_spec_for_out has src/lexer/cfg_eval.o (wave783 B5)"
  else
    bad "cfg_eval_ladder_spec_for_out missing src/lexer/cfg_eval.o (wave783)"
  fi
  if [ -z "$(cfg_eval_ladder_spec_for_out "not_a_cfg_eval.o")" ]; then
    note "cfg_eval_ladder non-member empty (wave783)"
  else
    bad "cfg_eval_ladder_spec_for_out must reject non-members (wave783)"
  fi
  # wave950: cfg-eval soft missing xlang-c → ensure_xlang_c.sh (0-make).
  # PLATFORM: SHARED — post_ship honesty after Makefile physical delete.
  # Match only active recipe lines (leading spaces + $MAKE), not comments/strings.
  if grep -E '^[[:space:]]+\$MAKE[[:space:]]+xlang-c' "$0" 2>/dev/null | grep -q .; then
    bad "cfg-eval ladder must not residual bare make xlang-c (wave950; ensure_xlang_c.sh)"
  fi
  if ! grep -q 'ensure_xlang_c\.sh ensure' "$0" 2>/dev/null; then
    bad "cfg-eval ladder must soft-call ensure_xlang_c.sh for missing xlang-c (wave950)"
  else
    note "cfg-eval soft xlang-c → ensure_xlang_c.sh (wave950; 0-make)"
  fi
  # wave783 + wave916: cfg_eval must thin-call try-heat|try-cfg-eval-ladder.
  # wave916: multi-target $(DRIVER_SEED_CFG_EVAL_OBJS): FORCE try-heat (list in r_lists).
  if grep -qE '\$\(DRIVER_SEED_CFG_EVAL_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_CFG_EVAL_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat|try-cfg-eval-ladder/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile B5 CFG_EVAL multi-target FORCE thin try-heat (wave916)"
  elif awk '
    $0 ~ /^src\/lexer\/cfg_eval\.o:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab {body = body $0 "\n"}
    END {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-cfg-eval-ladder/) exit 0
      exit 1
    }
  ' Makefile; then
    note "Makefile src/lexer/cfg_eval.o thin-calls ensure try-cfg-eval-ladder (wave783)"
  else
    bad "Makefile cfg_eval must thin-call ensure try-heat|try-cfg-eval-ladder (wave783/916 multi-target)"
  fi
  # Ban re-opened multi-ladder: no inline $(CC)/xlang-c/-E-extern on recipe lines.
  # wave916: multi-target recipe body must also stay thin (no inline multi-ladder).
  if grep -qE '\$\(DRIVER_SEED_CFG_EVAL_OBJS\):[[:space:]]*FORCE' Makefile 2>/dev/null \
    && awk '
      /\$\(DRIVER_SEED_CFG_EVAL_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 0 }
      hit && /^\t/ {body = body $0 "\n"}
      END {
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-cfg-eval-ladder/ \
            && body !~ /\$\(CC\)/ && body !~ /xlang-c/ && body !~ /-E-extern/) exit 1
        if (body ~ /\$\(CC\)/ && body ~ /-c /) exit 0
        if (body ~ /-E-extern/ && body !~ /ensure_host_cc_seed_o/) exit 0
        if (body ~ /cfg_eval_bootstrap_stub/ && body !~ /ensure_host_cc_seed_o/) exit 0
        exit 1
      }
    ' Makefile; then
    bad "Makefile B5 CFG_EVAL multi-target still has multi-ladder body (wave783/916)"
  elif awk '
    $0 ~ /^src\/lexer\/cfg_eval\.o:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab && /^\t/ {body = body $0 "\n"}
    END {
      if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat|try-cfg-eval-ladder/ \
          && body !~ /\$\(CC\)/ && body !~ /xlang-c/ && body !~ /-E-extern/) exit 1
      if (body ~ /\$\(CC\)/ && body ~ /-c /) exit 0
      if (body ~ /-E-extern/ && body !~ /ensure_host_cc_seed_o/) exit 0
      if (body ~ /cfg_eval_bootstrap_stub/ && body !~ /ensure_host_cc_seed_o/) exit 0
      exit 1
    }
  ' Makefile; then
    bad "Makefile src/lexer/cfg_eval.o still has multi-ladder body (wave783)"
  fi
  # wave760/762: try-r2 R2 UNAME leaves (panic + typeck_f64 + crt0)
  if ! grep -q 'try_ensure_r2_one\|try-r2' "$0"; then
    bad "try-r2 / try_ensure_r2_one missing (wave760/762 R2 UNAME)"
  else
    note "try-r2 R2 UNAME helper present (wave760 panic + wave762 typeck_f64/crt0)"
  fi
  if ! grep -q 'ensure_r2_typeck_f64_one\|r2_typeck_f64_host_pick' "$0"; then
    bad "r2 typeck_f64 body missing (wave762)"
  else
    note "r2-typeck-f64 body present (wave762)"
  fi
  if ! grep -q 'ensure_r2_crt0_one\|r2_crt0_src_for_out' "$0"; then
    bad "r2 crt0 body missing (wave762)"
  else
    note "r2-crt0 body present (wave762)"
  fi
  # wave761: try-gen-x gen residual helper
  if ! grep -q 'try_ensure_gen_x_one\|try-gen-x' "$0"; then
    bad "try-gen-x / try_ensure_gen_x_one missing (wave761 gen residual)"
  else
    note "try-gen-x gen residual helper present (wave761)"
  fi
  if [ ! -f scripts/ensure_gen_x_o.sh ]; then
    bad "scripts/ensure_gen_x_o.sh missing (wave761)"
  else
    note "ensure_gen_x_o.sh present (wave761)"
  fi
  # Makefile gen residual: wave761 ensure_gen_x_o · wave796 FORCE + try-heat
  # (try-heat → try-gen-x → ensure_gen_x_o body; G.7 single body).
  # wave909: multi-target $(GEN_X_SEED_OBJS): FORCE try-heat covers all four
  # (no per-leaf dual). Accept multi-target OR historical per-leaf.
  if grep -qE '\$\(GEN_X_SEED_OBJS\):[[:space:]]*FORCE' Makefile \
    && awk '
      /\$\(GEN_X_SEED_OBJS\):/ { hit=1; next }
      hit && /^[^#[:space:]\t]/ { exit 1 }
      hit && /ensure_host_cc_seed_o\.sh/ && /try-heat/ { found=1; exit 0 }
      END { exit found ? 0 : 1 }
    ' Makefile; then
    note "Makefile GEN_X multi-target FORCE thin try-heat (wave909; covers four)"
  fi
  for leaf in lsp_io_x.o lsp_x.o lsp_diag_x.o pipeline_x.o; do
    if makefile_leaf_try_heat_ok "$leaf" 'try-heat|try-gen-x'; then
      note "Makefile $leaf thin-calls try-heat|try-gen-x (wave761/796/909)"
    elif awk -v t="$leaf" '
      $0 ~ "^" t ":" {grab=1; next}
      grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
      grab {body = body $0 "\n"}
      END {
        if (body ~ /ensure_gen_x_o\.sh/) exit 0
        if (body ~ /ensure_host_cc_seed_o\.sh/ && body ~ /try-heat/) exit 0
        exit 1
      }
    ' Makefile; then
      note "Makefile $leaf thin-calls try-heat|ensure_gen_x_o (wave761/796)"
    else
      bad "Makefile $leaf must thin-call try-heat or ensure_gen_x_o.sh (wave761/796/909)"
    fi
  done

  # wave789: B7A heat auto-dispatch entry must exist (shell ladder; no second body).
  if ! grep -q 'try_heat_one\|try-heat' "$0"; then
    bad "try-heat / try_heat_one missing (wave789 B7A heat shell dispatch)"
  else
    note "try-heat B7A heat auto-dispatch present (wave789)"
  fi
  # wave862: try-heat CFLAGS bulk shell-load via export-try-heat-cflags (G.7).
  # Makefile try-heat recipes must not re-inject CFLAGS=/PIPELINE_GEN_CFLAGS=.
  # wave942: catalog-primary CFLAGS load (was make export-try-heat-cflags).
  # Makefile physically deleted in wave941; catalog is the single authority.
  if ! grep -q '_load_try_heat_cflags_via_catalog\|export-try-heat-cflags' "$0"; then
    bad "shell must load try-heat CFLAGS via catalog (wave862/942)"
  else
    note "try-heat CFLAGS catalog-load present (wave862/942)"
  fi
  _th_cflags_n=$(awk '
    $0 ~ /ensure_host_cc_seed_o\.sh try-heat/ { grab=1 }
    grab {
      body = body $0 "\n"
      if ($0 ~ /try-heat \$\@/) {
        if (body ~ /CFLAGS="\$\(CFLAGS\)"/ || body ~ /PIPELINE_GEN_CFLAGS="\$\(PIPELINE_GEN_CFLAGS\)"/) n++
        body=""; grab=0
      }
    }
    END { print n+0 }
  ' Makefile)
  if [ "${_th_cflags_n:-0}" -ne 0 ]; then
    bad "Makefile try-heat recipes still inject CFLAGS=/PIPELINE_GEN_CFLAGS= (wave862; got ${_th_cflags_n})"
  else
    note "Makefile try-heat recipes drop CFLAGS/PIPELINE_GEN inject (wave862)"
  fi
  if ! grep -q 'seed_project_hdrs_newer' "$0"; then
    bad "seed_project_hdrs_newer missing (wave793 B7A hdr mtime for FORCE thin)"
  else
    note "seed_project_hdrs_newer present (wave793 project-header freshness)"
  fi
  if ! grep -q 'force_thin_makefile_flags_newer' "$0"; then
    bad "force_thin_makefile_flags_newer missing (wave794 Makefile-flags FORCE thin)"
  else
    note "force_thin_makefile_flags_newer present (wave794 flag-sensitive leaves)"
  fi
  if ! grep -q 'try_ensure_runtime_os_prefer_one' "$0" \
    || ! grep -q 'try_ensure_r1_one' "$0" \
    || ! grep -q 'try_ensure_gen_x_one' "$0"; then
    bad "try-heat ladder requires existing try-* helpers (wave789 G.7 有则补全)"
  else
    note "try-heat ladder deps present (prefer/R1/gen; wave789)"
  fi

  if [ "$fail" -ne 0 ]; then
    echo "ensure_host_cc_seed_o: --check FAILED" >&2
    exit 1
  fi
  # wave796: net multi-merge FORCE thin requires multi .x/seed mtime loop.
  if ! grep -q 'udp_batch.x' "$0" || ! grep -q 'runtime_net_sock_fast.from_x.c' "$0"; then
    bad "net_merge multi-source mtime missing (wave796 B7A FORCE thin)"
  else
    note "net_merge multi-source mtime present (wave796 FORCE thin)"
  fi
  # wave866: crt0_mingw must not inject multi-token WIN32_O_CFLAGS= (G.7 hygiene).
  # Shell uses ${WIN32_O_CFLAGS:-}; no Makefile ?= composition for this bag.
  # wave913: mingw is multi-target member — also scan multi-target body if no per-leaf line.
  _win_rec=$(awk '
    $0 ~ /^src\/asm\/crt0_mingw\.o:/ {grab=1; next}
    grab && /^[^\t#]/ && $0 !~ /^$/ {exit}
    grab {print}
  ' Makefile 2>/dev/null || true)
  if [ -z "${_win_rec:-}" ]; then
    _win_rec=$(awk '
      /\$\(DRIVER_SEED_CRT0_OBJS\):/ { grab=1; next }
      grab && /^[^#[:space:]\t]/ { exit }
      grab { print }
    ' Makefile 2>/dev/null || true)
  fi
  if grep -qE 'WIN32_O_CFLAGS=' <<<"${_win_rec:-}"; then
    bad "Makefile crt0_mingw still injects WIN32_O_CFLAGS= (wave866/913)"
  else
    note "Makefile crt0_mingw drops WIN32_O_CFLAGS inject (wave866/913 multi-target)"
  fi
  echo "ensure_host_cc_seed_o: CHECK OK (R1 families + try-r1 + R3 cold-else + R3 PREFER thin + R2 panic/typeck_f64/crt0 + gen-x residual + try-heat + CFLAGS shell-load wave862 + WIN32_O drop wave866 + hdr/Makefile-flags + net multi-merge mtime · wave748–866)" >&2
}

# ---------------------------------------------------------------------------
# wave789: try-heat OUT — B7A heat shell auto-dispatch (G.7 有则补全).
#
# Single heat entry that ladders *existing* membership helpers only.
# Prefer/hybrid product modes run before pure R1/R2/gen so heat matches
# Makefile product thin-call semantics (labi/rt/pipeline_abi/… before R1).
# Exit codes:
#   0 — some mode claimed OUT and ensure body ran (or skipped up-to-date)
#   3 — no ensure mode claims OUT (caller residual make / non-ensure leaf)
#   1/2 — matching mode hard-failed
# PLATFORM: SHARED — orchestration only; no second recipe body / no .o list.
# NOT physical delete: Makefile thin-call edges remain for make dep graph.
# wave791–794: FORCE-thin leaves (pure seed+.x(+.h) + twin + Makefile-flags +
# pure leftover) still use this ladder for seed/.x/project-hdr/Makefile-flags
# (and prefer-table) freshness — cheap skip when up-to-date
# (seed_project_hdrs_newer · force_thin_makefile_flags_newer).
# ---------------------------------------------------------------------------
try_heat_one() {
  local o="$1"
  local rc
  if [ -z "$o" ]; then
    echo "ensure_host_cc_seed_o try-heat: need <out.o>" >&2
    exit 2
  fi
  # Prefer / hybrid first (heat product path), then pure R1, R2 UNAME, gen-x.
  # Each helper exits 3 when OUT is not a member — cheap membership only.
  set +e
  try_ensure_runtime_os_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_std_core_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_lsp_sat_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_gen_c_to_o_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_cfg_eval_ladder_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_r3_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_labi_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_rt_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_pipeline_abi_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_ldpc_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_target_cpu_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_l2_asm_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_async_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_other_l2_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_r2_prefer_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_r1_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_r2_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  set +e
  try_ensure_gen_x_one "$o"; rc=$?; set -e
  [ "$rc" -eq 0 ] && return 0
  [ "$rc" -ne 3 ] && return "$rc"
  # Honest residual: not an ensure-owned leaf (make graph / non-catalog).
  return 3
}

case "$MODE" in
  try-x-to-o|x-to-o)
    # F1-2026-08-18 chunked -E builder: generic rt_prefer harness entry for
    # arbitrary (SRC.x, OUT.o) pairs. Purpose: split OOM-prone mega modules
    # (runtime_pipeline_abi.x -E peaks 22-40GB RSS) into line-balanced chunks,
    # each small enough for dev-box jetsam limits; caller merges chunk .o's
    # via pure_ld_partial_merge (first-wins). Env passthrough (single
    # authority stays rt_prefer_try_x_to_o — no second build path, G.7):
    #   XLANG_PREFER_ASM_O_RT=0  → historic -E+$CC (chunk path default)
    #   G05_X_O_WEAK=1           → weakify function defs (first-wins merge)
    #   G05_X_O_GLOBALS_WEAK=1   → un-static + weakify g_* globals (shared
    #                              storage across chunks; see weakify block)
    # PLATFORM: SHARED harness.
    if [ "$#" -lt 2 ]; then
      echo "ensure_host_cc_seed_o try-x-to-o: need <src.x> <out.o>" >&2
      exit 2
    fi
    set +e
    rt_prefer_try_x_to_o "$1" "$2"
    _xrc=$?
    set -e
    exit "$_xrc"
    ;;
  one)
    if [ "$#" -lt 2 ]; then
      echo "ensure_host_cc_seed_o one: need <out.o> <seed.from_x.c> [extra...]" >&2
      exit 2
    fi
    ensure_one "$@"
    ;;
  try-r1|try_r1|one-r1|r1-one)
    # wave756: R4 pure-R1 helper — exit 3 if not pure R1 catalog member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-r1: need <out.o>" >&2
      exit 2
    fi
    # Drop trailing --force tokens already handled via FORCE global.
    _try_out="$1"
    set +e
    try_ensure_r1_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-r3-cold|try_r3_cold|r3-cold|r3-cold-one)
    # wave757: R3 cold-else helper — exit 3 if not R3_COLD_SEED_OBJS member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-r3-cold: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_r3_cold_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-r3-prefer|try_r3_prefer|r3-prefer|r3-prefer-one|prefer-thin|try-prefer-thin)
    # wave763: R3 PREFER thin+rest helper — exit 3 if not R3_COLD_SEED_OBJS member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-r3-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_r3_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  r3-prefer-family|r3_prefer_family|prefer-thin-family|family=r3_prefer)
    ensure_r3_prefer
    ;;
  try-labi-prefer|try_labi_prefer|labi-prefer|labi-prefer-one|try-labi)
    # wave765: labi multi-slice PREFER helper — exit 3 if not src/runtime_link_abi.o.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-labi-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_labi_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-rt-prefer|try_rt_prefer|rt-prefer|rt-prefer-one|try-rt)
    # wave766: rt multi-slice PREFER helper — exit 3 if not src/runtime_driver_no_c.o.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-rt-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_rt_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-pipeline-abi-prefer|try_pipeline_abi_prefer|pipeline-abi-prefer|pipeline-abi|try-pabi)
    # wave767: pipeline_abi PREFER helper — exit 3 if not src/runtime_pipeline_abi.o.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-pipeline-abi-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_pipeline_abi_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-ldpc-prefer|try_ldpc_prefer|ldpc-prefer|ldpc-prefer-one|try-ldpc)
    # wave767: ldpc PREFER helper — exit 3 if not src/lsp/lsp_diag_pipeline_ctx.o.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-ldpc-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_ldpc_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-target-cpu-prefer|try_target_cpu_prefer|target-cpu-prefer|tcpu-prefer|try-tcpu)
    # wave768: target_cpu PREFER helper — exit 3 if not src/driver/target_cpu.o.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-target-cpu-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_target_cpu_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-l2-asm-prefer|try_l2_asm_prefer|l2-asm-prefer|l2-asm|try-l2-asm)
    # wave769: L2 asm three PREFER helper — exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-l2-asm-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_l2_asm_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-async-prefer|try_async_prefer|async-prefer|async|try-async)
    # wave770: async three PREFER helper — exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-async-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_async_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-other-l2-prefer|try_other_l2_prefer|other-l2-prefer|other-l2|try-other-l2|ol2-prefer)
    # wave771: other L2 four PREFER helper — exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-other-l2-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_other_l2_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-r2-prefer|try_r2_prefer|r2-prefer|panic-prefer|try-r2-prefer-panic)
    # wave776: R2 panic PREFER thin+rest; exit 3 if not DRIVER_SEED_PANIC member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-r2-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_r2_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-runtime-os-prefer|try_runtime_os_prefer|runtime-os-prefer|rtos-prefer|try-runtime-os|b1-prefer)
    # wave779: B1 runtime_* OS/glue PREFER table; exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-runtime-os-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_runtime_os_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-std-core-prefer|try_std_core_prefer|std-core-prefer|stdcore-prefer|try-std-core|b2-prefer)
    # wave780: B2 std/core product hybrid table; exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-std-core-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_std_core_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-lsp-sat-prefer|try_lsp_sat_prefer|lsp-sat-prefer|lspsat-prefer|try-lsp-sat|b3-prefer)
    # wave781: B3 LSP satellite hybrid table; exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-lsp-sat-prefer: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_lsp_sat_prefer_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-gen-c-to-o|try_gen_c_to_o|gen-c-to-o|genc2o|try-gen-c|b4-gen|b4-prefer)
    # wave782: B4 gen.c → .o bootstrap table; exit 3 if not table member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-gen-c-to-o: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_gen_c_to_o_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-cfg-eval-ladder|try_cfg_eval_ladder|cfg-eval-ladder|cfgeval-ladder|try-cfg-eval|b5-cfg|b5-ladder)
    # wave783: B5 cfg_eval multi-ladder; exit 3 if not member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-cfg-eval-ladder: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_cfg_eval_ladder_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-heat|try_heat|heat|heat-one|try-auto|auto|b7a-heat)
    # wave789: B7A heat shell auto-dispatch; exit 3 if no ensure mode claims OUT.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-heat: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_heat_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-r2|try_r2|try-r2-panic|r2-one|r2-panic-one)
    # wave760/762: R2 UNAME helper — panic | typeck_f64 | crt0; exit 3 if not member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-r2: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_r2_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  try-gen-x|try_gen_x|try-gen|gen-x-one|r4-gen-one)
    # wave761: gen residual helper — exit 3 if not gen map + catalog member.
    if [ "$#" -lt 1 ]; then
      echo "ensure_host_cc_seed_o try-gen-x: need <out.o>" >&2
      exit 2
    fi
    _try_out="$1"
    set +e
    try_ensure_gen_x_one "$_try_out"
    _try_rc=$?
    set -e
    exit "$_try_rc"
    ;;
  r3-cold-seed|r3_cold_seed|cold-seed|family=r3_cold_seed)
    ensure_r3_cold_seed
    ;;
  r2-panic|r2_panic|panic-cold|family=r2_panic|family=driver_seed_panic)
    ensure_r2_panic
    ;;
  r2-typeck-f64|r2_typeck_f64|typeck-f64|typeck_f64|family=r2_typeck_f64|family=driver_seed_typeck_f64)
    ensure_r2_typeck_f64
    ;;
  r2-crt0|r2_crt0|crt0|family=r2_crt0|family=driver_seed_crt0)
    ensure_r2_crt0
    ;;
  gen-x|gen_x|residual-gen|family=gen_x|family=r4_gen_x)
    ensure_gen_x_residual
    ;;
  rt-slice|rt_slice|rt-seed-slice|family=rt_seed_slice)
    ensure_rt_slice
    ;;
  core-seed|core_seed|core|r1-core|r1-core-seed|family=r1_core_seed)
    ensure_core_seed
    ;;
  frontend-glue|frontend_glue|glue|r1-frontend-glue|r1-glue|family=r1_frontend_glue)
    ensure_frontend_glue
    ;;
  main-runtime|main_runtime|r1-main-runtime|r1-main|family=r1_main_runtime)
    ensure_main_runtime
    ;;
  alias-stubs|alias_stubs|r1-alias-stubs|r1-alias|family=r1_alias_stubs)
    ensure_alias_stubs
    ;;
  extra-cflags|extra_cflags|r1-extra-cflags|r1-extra|pipeline-abi|family=r1_extra_cflags)
    ensure_extra_cflags
    ;;
  misc-basename|misc_basename|misc|r1-misc-basename|r1-misc|family=r1_misc_basename)
    ensure_misc_basename
    ;;
  seed-map|seed_map|r1-seed-map|r1-mismatch|mismatch|family=r1_seed_map)
    ensure_seed_map
    ;;
  all|family|families|swallowed)
    # Umbrella: all swallowed pure R1 families on this body.
    ensure_all_swallowed
    ;;
  --check|check|-c)
    run_check
    ;;
  help|-h|--help)
    sed -n '2,75p' "$0" | sed 's/^# \{0,1\}//'
    exit 0
    ;;
  *)
    echo "ensure_host_cc_seed_o: unknown mode '$MODE' (one|try-r1|try-r3-cold|try-r3-prefer|try-labi-prefer|try-rt-prefer|try-pipeline-abi-prefer|try-ldpc-prefer|try-target-cpu-prefer|try-r2-prefer|try-heat|try-r2|try-gen-x|try-x-to-o|rt-slice|core-seed|frontend-glue|main-runtime|alias-stubs|extra-cflags|misc-basename|seed-map|r3-cold-seed|r2-panic|r2-typeck-f64|r2-crt0|gen-x|all|--check)" >&2
    exit 2
    ;;
esac
