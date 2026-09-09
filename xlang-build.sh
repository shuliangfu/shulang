#!/usr/bin/env bash
# xlang-build.sh — 仓库根统一构建入口体（G-05 · G.7 权威实现）
# wave784: shebang bash — body uses arrays (`_hcs_args=()`); xbuild execs bash.
#
# 对外首选名：./xbuild（薄转调本脚本；禁止在 xbuild 再写目标体）。
#
# 分层：
#   1) 日常编译器：build.x + compiler/build_tool
#      → scripts/g05_build_xlang_asm.sh → g05 relink（产品 0-make）
#   2) 测试 / 内核 / gate：委托 compiler/scripts 或 tests/*.sh
#   3) compiler/Makefile：已物理删除（wave942）；叶图 → shell catalog + tests/lib/compiler-make.sh
#   4) 根 Makefile：已删除；统一入口 ./xbuild
#
# 产品入口 0× make -C（build-tool/clean/test*/bootstrap-* 均 shell 权威）。
#
# 用法: ./xbuild <target>   或   ./xlang-build.sh <target>
# 例:   ./xbuild build
#       ./xbuild xlang-asm
#       XLANG_BUILD_TOOL_FULL=1 ./xbuild full

set -e
cd "$(dirname "$0")"

TARGET="${1:-all}"

# G.7: scripts/build_tool.sh is the only build_tool body (Makefile thin leaf).
# wave866 fix: bash (not sh/dash) — script uses bash features + export-try-heat-cflags.
run_build_tool_host() {
  (cd compiler && bash scripts/build_tool.sh)
}

ensure_build_tool() {
  if [ ! -x compiler/build_tool ]; then
    echo "xlang-build: compiler/build_tool missing → scripts/build_tool.sh"
    run_build_tool_host
  fi
}

# G.7: build_via_tool.sh is the only "run build_tool → product" body
# (Makefile build-via-tool thin leaf; wave874). Optional subcmd: asm | legacy.
run_build_tool() {
  ensure_build_tool
  (cd compiler && TARGET=xlang bash scripts/build_via_tool.sh ${1:+"$1"})
}

# Residual make hub for CI / cold-start / leaf .o (wave730 · wave733 G.7).
# Outer workflows/docker must call ./xbuild — never raw `make -C compiler`.
# G.7 single body: tests/lib/compiler-make.sh (same as tests xlang_compiler_make).
# Dependency graph: shell catalog + compiler-make hub (Makefile deleted).
# PLATFORM: SHARED
run_compiler_make() {
  bash tests/lib/compiler-make.sh "$@"
}

# g05 product chain — direct shell (wave733 · 11.1.6 first slice).
# No Makefile: prepare/ensure/env/link already live under compiler/scripts/g05_*.sh.
# PLATFORM: SHARED
run_g05_ensure() {
  (cd compiler && sh scripts/g05_ensure_relink_prereqs.sh)
}
run_g05_link_env() {
  (cd compiler && sh scripts/g05_relink_env.sh)
}
run_g05_prepare_and_relink() {
  # $1 = G05_SYNC_ASM (0 = xlang only; 1 = also sync xlang_asm)
  (cd compiler && G05_SYNC_ASM="${1:-1}" sh scripts/g05_prepare_and_relink.sh)
}
# P0 asm gate: migrate shell + g05 relink + overlay xlang_asm (wave734/735).
run_refresh_xlang_asm_gate() {
  (cd compiler && sh scripts/refresh_xlang_asm_gate.sh)
}
# migrate companions: parser_x.o typeck_x.o codegen_x.o (wave735 · 11.1.6).
# G.7 body = scripts/migrate_x_objs.sh; *_gen.c via ensure_migrate_gen.sh (wave736).
run_migrate_x_objs() {
  (cd compiler && sh scripts/migrate_x_objs.sh all)
}
# product frontend *_gen.c pin/seed/-E (wave736 migrate trio · wave737 +lexer).
# G.7 body = scripts/ensure_migrate_gen.sh (parser/typeck/codegen; lexer via mode).
run_ensure_migrate_gen() {
  (cd compiler && bash scripts/ensure_migrate_gen.sh all)
}
run_ensure_lexer_gen() {
  (cd compiler && bash scripts/ensure_migrate_gen.sh lexer)
}
# product driver/preprocess *_gen.c pin/seed/-E (wave738).
# G.7 body = scripts/ensure_driver_gen.sh
run_ensure_driver_gen() {
  (cd compiler && bash scripts/ensure_driver_gen.sh all)
}
# product LSP + pipeline *_gen.c pin/seed/-E (wave739).
# G.7 body = scripts/ensure_lsp_pipeline_gen.sh
run_ensure_lsp_pipeline_gen() {
  (cd compiler && bash scripts/ensure_lsp_pipeline_gen.sh all)
}
# Track L archaeology *_gen.c pin/seed/-E (wave740; product link does not use).
# G.7 body = scripts/ensure_archaeology_gen.sh
run_ensure_archaeology_gen() {
  (cd compiler && bash scripts/ensure_archaeology_gen.sh all)
}
case "$TARGET" in
  # === 编译器（G-05 日常）===
  all|build|xlang)
    # 默认路径：build_tool → g05 relink；见 build_tool_libc_bridge
    # NOTE: product `all` ≠ Makefile `all`. CI host-cc/seed path = compiler-all.
    run_build_tool
    ;;
  xlang-asm|asm)
    # 显式 asm 子命令（与 ./build_tool ./xlang asm 相同）
    run_build_tool asm
    ;;
  full|bstrict)
    # 全量 B-strict（脚本 + refresh）；较慢；FULL 仍可能 make bstrict（非日常）
    ensure_build_tool
    (cd compiler && XLANG_BUILD_TOOL_FULL=1 ./build_tool ./xlang asm)
    ;;
  legacy)
    # 逐步 -E 路径（依赖现有 *_x.o / seed；非默认）
    run_build_tool legacy
    ;;
  build-tool)
    run_build_tool_host
    ;;
  first-time|bootstrap)
    # pinned seeds → build_tool shell，再日常 relink
    run_build_tool_host
    run_build_tool
    ;;
  clean)
    # G.7: scripts/clean_compiler.sh（Makefile clean 同调）
    (cd compiler && sh scripts/clean_compiler.sh)
    ;;

  # === g05 产品链一等目标（wave733 · 11.1.6；零 make）===
  ensure|g05-ensure|g05-ensure-relink-prereqs)
    run_g05_ensure
    ;;
  link-env|g05-export|g05-export-relink)
    run_g05_link_env
    ;;
  link-product|relink|relink-xlang)
    # Like `make relink-xlang`: final link only (no xlang_asm sync)
    run_g05_prepare_and_relink 0
    ;;
  link-product-asm|prepare-and-relink)
    # Like `make xlang_asm`: ensure+link+sync xlang_asm (no build_tool rebuild)
    run_g05_prepare_and_relink 1
    ;;
  refresh-gate|refresh-xlang-asm-gate)
    # P0: migrate-x-objs (shell) + g05 relink + cp xlang → xlang_asm
    # Wave734/735 · 11.1.6; body = scripts/refresh_xlang_asm_gate.sh (G.7)
    run_refresh_xlang_asm_gate
    ;;
  migrate|migrate-x-objs)
    # Wave735 · 11.1.6: parser/typeck/codegen _x.o via migrate_x_objs.sh
    # (wave736: gen ensure is shell; no residual make for *_gen.c body)
    run_migrate_x_objs
    ;;
  migrate-gen|ensure-migrate-gen|parser-gen|typeck-gen|codegen-gen|lexer-gen|ensure-lexer-gen)
    # Wave736/737 · 11.1.6: frontend *_gen.c via ensure_migrate_gen.sh
    # Optional sub-mode: ./xbuild migrate-gen parser|typeck|codegen|lexer
    # ./xbuild lexer-gen | all-frontend
    _gen_mode="all"
    if [ "${2:-}" = "parser" ] || [ "${2:-}" = "typeck" ] || [ "${2:-}" = "codegen" ] \
      || [ "${2:-}" = "lexer" ] || [ "${2:-}" = "all-frontend" ] || [ "${2:-}" = "frontend" ]; then
      _gen_mode="$2"
    fi
    case "$TARGET" in
      parser-gen) _gen_mode=parser ;;
      typeck-gen) _gen_mode=typeck ;;
      codegen-gen) _gen_mode=codegen ;;
      lexer-gen|ensure-lexer-gen) _gen_mode=lexer ;;
    esac
    (cd compiler && bash scripts/ensure_migrate_gen.sh "$_gen_mode")
    ;;
  drift-gate|pin-drift-gate|pin-gen-drift-gate)
    # 7.4.4 v1: pin↔gen T-symbol freshness gate. Catches "pin edited in git,
    # worktree gen stale" (2026-09-10 driver_gen trap). G.7 body =
    # compiler/scripts/pin_gen_drift_gate.sh. Optional: ./xbuild drift-gate -v
    # PLATFORM: SHARED — cc/nm only.
    (cd compiler && bash scripts/pin_gen_drift_gate.sh "${2:-}")
    ;;
  driver-gen|ensure-driver-gen|preprocess-gen|ensure-preprocess-gen)
    # Wave738 · 11.1.6: driver_gen.c + preprocess_gen.c via ensure_driver_gen.sh
    # Optional: ./xbuild driver-gen driver|preprocess    _dgen_mode="all"
    if [ "${2:-}" = "driver" ] || [ "${2:-}" = "preprocess" ] || [ "${2:-}" = "all" ]; then
      _dgen_mode="$2"
    fi
    case "$TARGET" in
      preprocess-gen|ensure-preprocess-gen) _dgen_mode=preprocess ;;
      driver-gen|ensure-driver-gen)
        if [ -z "${2:-}" ]; then _dgen_mode=all; fi
        ;;
    esac
    (cd compiler && bash scripts/ensure_driver_gen.sh "$_dgen_mode")
    ;;
  lsp-gen|ensure-lsp-gen|pipeline-gen|ensure-pipeline-gen|lsp-pipeline-gen|ensure-lsp-pipeline-gen)
    # Wave739 · 11.1.6: lsp_*_gen.c + pipeline_gen.c via ensure_lsp_pipeline_gen.sh
    # Optional: ./xbuild lsp-gen lsp|lsp_diag|lsp_io|lsp_gen|pipeline
    _lp_mode="all"
    if [ "${2:-}" = "lsp" ] || [ "${2:-}" = "lsp-all" ] || [ "${2:-}" = "lsp_diag" ] \
      || [ "${2:-}" = "lsp_io" ] || [ "${2:-}" = "lsp_gen" ] || [ "${2:-}" = "pipeline" ] \
      || [ "${2:-}" = "all" ]; then
      _lp_mode="$2"
    fi
    case "$TARGET" in
      pipeline-gen|ensure-pipeline-gen) _lp_mode=pipeline ;;
      lsp-gen|ensure-lsp-gen)
        if [ -z "${2:-}" ]; then _lp_mode=lsp; fi
        ;;
      lsp-pipeline-gen|ensure-lsp-pipeline-gen)
        if [ -z "${2:-}" ]; then _lp_mode=all; fi
        ;;
    esac
    (cd compiler && bash scripts/ensure_lsp_pipeline_gen.sh "$_lp_mode")
    ;;
  archaeology-gen|ensure-archaeology-gen|driver-subcmd-gen|ensure-driver-subcmd-gen)
    # Wave740 · 11.1.6: Track L archaeology driver_*_gen + lsp_io_std_heap_gen
    # Product link does not consume these (PREFER_X_O). Optional sub-mode:
    #   ./xbuild archaeology-gen all|driver-all|fmt|check|…|emit|lsp_io_std_heap
    _arch_mode="all"
    if [ -n "${2:-}" ]; then
      case "$2" in
        all|driver-all|driver_all|subcmd-all|subcmds|fmt|check|test|compile|build|run|emit|lsp_io_std_heap|std_heap|heap)
          _arch_mode="$2"
          ;;
      esac
    fi
    case "$TARGET" in
      driver-subcmd-gen|ensure-driver-subcmd-gen)
        if [ -z "${2:-}" ]; then _arch_mode=driver-all; fi
        ;;
    esac
    (cd compiler && bash scripts/ensure_archaeology_gen.sh "$_arch_mode")
    ;;

  # === 11.1.1 inventory + 11.1.2 schedule (wave742/743 · not full .x import graph) ===
  product-dag|build-dag|cold-dag|ensure-product-dag|dag-run|dag-dry-run)
    # Dump / check / dry-run / run orchestration schedules.
    # Usage:
    #   ./xbuild product-dag
    #   ./xbuild product-dag --check
    #   ./xbuild product-dag --dry-run [product|refresh|cold]
    #   ./xbuild product-dag --run product|refresh|cold
    # Body: compiler/scripts/product_build_dag.sh · map: compiler/docs/BUILD_DAG.md
    # G.7: no second .o list; run only invokes existing body scripts.
    _dag_mode="dump"
    _dag_profile="product"
    case "${1}" in
      dag-dry-run) _dag_mode="dry-run"; _dag_profile="${2:-product}" ;;
      dag-run) _dag_mode="run"; _dag_profile="${2:-product}" ;;
      *)
        if [ "${2:-}" = "--check" ] || [ "${2:-}" = "check" ] || [ "${2:-}" = "-c" ]; then
          _dag_mode="check"
        elif [ "${2:-}" = "--dry-run" ] || [ "${2:-}" = "dry-run" ]; then
          _dag_mode="dry-run"
          _dag_profile="${3:-product}"
        elif [ "${2:-}" = "--run" ] || [ "${2:-}" = "run" ]; then
          _dag_mode="run"
          _dag_profile="${3:-product}"
        fi
        ;;
    esac
    if [ "$_dag_mode" = "dry-run" ] || [ "$_dag_mode" = "run" ]; then
      bash compiler/scripts/product_build_dag.sh "$_dag_mode" "$_dag_profile"
    else
      bash compiler/scripts/product_build_dag.sh "$_dag_mode"
    fi
    ;;

  # === wave744 · 11.3 residual: DRIVER_SEED_PREREQS edge satisfaction (shell) ===
  driver-seed-prereqs|ensure-driver-seed-prereqs|seed-prereqs)
    # Expand catalog DRIVER_SEED_PREREQS (+ glue companion); dry-run/check/run.
    # List authority: compiler/mk/*.mk via driver_seed_obj_catalog.sh (G.7).
    # Usage: ./xbuild driver-seed-prereqs [--dry-run|--check|--run]
    _prereq_mode="${2:---dry-run}"
    case "$_prereq_mode" in
      --dry-run|dry-run|dryrun|--check|check|-c|--run|run|ensure) ;;
      *) _prereq_mode="--dry-run" ;;
    esac
    (cd compiler && bash scripts/driver_seed_ensure_prereqs.sh "$_prereq_mode")
    ;;

  # === wave745 · 11.1.3 platform + 11.1.4 linker policy (shell inventory) ===
  host-platform|platform-host|platform|linker-policy|host-linker|ld-policy)
    # Host OS/arch facts + named residual CC -o inventory (G.7 no dual link path).
    # Map: compiler/docs/PLATFORM_LINKER.md
    # Usage:
    #   ./xbuild host-platform              # dump platform KEY=value
    #   ./xbuild host-platform --export     # shell-sourceable exports
    #   ./xbuild host-platform --check
    #   ./xbuild linker-policy              # residual + preferred ld inventory
    #   ./xbuild linker-policy --check
    _pl_mode="dump"
    case "${1}" in
      host-platform|platform-host|platform)
        _pl_mode="platform"
        if [ "${2:-}" = "--export" ] || [ "${2:-}" = "export" ] || [ "${2:-}" = "-e" ]; then
          _pl_mode="export"
        elif [ "${2:-}" = "--check" ] || [ "${2:-}" = "check" ] || [ "${2:-}" = "-c" ]; then
          _pl_mode="check"
        elif [ "${2:-}" = "--dump" ] || [ "${2:-}" = "dump" ]; then
          _pl_mode="dump"
        fi
        ;;
      linker-policy|host-linker|ld-policy)
        _pl_mode="linker"
        if [ "${2:-}" = "--check" ] || [ "${2:-}" = "check" ] || [ "${2:-}" = "-c" ]; then
          _pl_mode="check"
        elif [ "${2:-}" = "--dump" ] || [ "${2:-}" = "dump" ]; then
          _pl_mode="dump"
        fi
        ;;
    esac
    bash compiler/scripts/host_platform_linker.sh "$_pl_mode"
    ;;

  # === wave746 · 11.3.1 path · leaf .o pattern residual inventory ===
  leaf-patterns|leaf-residual|pattern-residual|leaf-pattern)
    # Named residual classes for Makefile leaf host-cc / pattern rules (G.7 no dual .o).
    # Map: compiler/docs/LEAF_PATTERN_RESIDUAL.md
    # Usage:
    #   ./xbuild leaf-patterns              # dump class inventory + live metrics
    #   ./xbuild leaf-patterns --check
    #   ./xbuild leaf-residual classes
    _lp_mode="dump"
    if [ "${2:-}" = "--check" ] || [ "${2:-}" = "check" ] || [ "${2:-}" = "-c" ]; then
      _lp_mode="check"
    elif [ "${2:-}" = "classes" ] || [ "${2:-}" = "class" ] || [ "${2:-}" = "--classes" ]; then
      _lp_mode="classes"
    elif [ "${2:-}" = "--dump" ] || [ "${2:-}" = "dump" ]; then
      _lp_mode="dump"
    fi
    bash compiler/scripts/leaf_pattern_residual.sh "$_lp_mode"
    ;;

  # === wave963 · BC track open · stage 8.3 product residual C inventory ===
  bc-inventory|bc-host-cc|bc-host-cc-inventory|bc-residual)
    # G.7 single body: compiler/scripts/bc_host_cc_product_inventory.sh
    # Freezes product residual C that still need host-cc (pipeline_glue/ast_pool/…).
    # Map: analysis/C迁移追踪.md §8.3 · does NOT compile · not pin lift.
    # Usage:
    #   ./xbuild bc-inventory
    #   ./xbuild bc-inventory --check
    #   ./xbuild bc-host-cc --check
    _bc_mode="dump"
    if [ "${2:-}" = "--check" ] || [ "${2:-}" = "check" ] || [ "${2:-}" = "-c" ]; then
      _bc_mode="check"
    elif [ "${2:-}" = "--dump" ] || [ "${2:-}" = "dump" ]; then
      _bc_mode="dump"
    fi
    bash compiler/scripts/bc_host_cc_product_inventory.sh "$_bc_mode"
    ;;

  # === wave299 · G.7 daily L2 product matrix (root fix: set -e + rv exit 42) ===
  l2-matrix|product-matrix|product-l2-matrix|matrix-l2)
    # G.7 single body: compiler/scripts/product_l2_matrix.sh
    # Captures expected non-zero run codes (rv=42, opt=102) without aborting mid-matrix.
    # Usage:
    #   ./xbuild l2-matrix
    #   XLANG=./compiler/xlang_asm ./xbuild product-matrix
    #   ./xbuild l2-matrix --xlang ./compiler/xlang_asm
    # PLATFORM: SHARED — dual-end for SHARED product work.
    shift
    bash compiler/scripts/product_l2_matrix.sh "$@"
    ;;

  # === wave341 · G.7 L4 true-cold product gate (single entry next to l2-matrix) ===
  l4|l4-cold|true-cold|true-cold-l4|product-l4|l4-true-cold)
    # G.7 single body: compiler/scripts/product_l4_true_cold.sh
    # Full wipe .o + product binaries → seed pin → bootstrap-driver-seed → g05
    # → product_l2_matrix → run-all-bstrict (SKIP_BUILD=1). Does NOT run check.
    # Usage:
    #   ./xbuild l4
    #   ./xbuild l4-cold
    #   ./xbuild l4 --no-bstrict      # rebuild + matrix only
    #   ./xbuild l4 --rebuild-only    # purge + seed + g05 only
    # PLATFORM: SHARED — dual-end for SHARED / bootstrap cut-over (Ubuntu gold).
    shift
    bash compiler/scripts/product_l4_true_cold.sh "$@"
    ;;

  # === wave799 · 11.3.1 · physical-delete execute gate (NOT delete; NOT Windows green) ===
  phys-del-gate|phys-del|physical-delete-gate|makefile-delete-gate)
    # G.7 single body: compiler/scripts/phys_del_makefile_gate.sh
    # Hard-refuses rm of compiler/Makefile until Windows min-gate re-proven + ENDGAME=1.
    # wave800: --run-windows-gate writes proof stamp; --verify-windows-proof checks tip.
    # wave801: --status-flip-preview proof-gated plan only (NOT flip; NOT delete).
    # wave802: --status-flip-apply proof+confirm leaf STATUS edit (NOT delete; ENDGAME=0).
    # wave803: --status-flip-commit-honesty inventory + post-apply contract (NOT edit; NOT delete).
    # wave805: --endgame-preview STATUS-gated ENDGAME=1 plan only (NOT arm; NOT delete).
    # wave806: --endgame-arm-apply STATUS+confirm leaf ENDGAME edit (NOT delete; TREE_ARMED=0).
    # wave807: --endgame-arm-commit-honesty pre_arm/post_arm contract (NOT edit; NOT delete).
    # wave808: TREE_ARMED arm on leaf (ENDGAME=1 TREE_ARMED=1; NOT physical delete).
    # wave809: --delete-body-preview TREE_ARMED-gated plan only (NOT ship body; NOT rm).
    # wave810: --delete-body-commit-honesty pre_ship inventory (NOT edit; NOT rm).
    # Usage:
    #   ./xbuild phys-del-gate
    #   ./xbuild phys-del-gate --check
    #   ./xbuild phys-del-gate --dry-run-delete
    #   ./xbuild phys-del-gate --run-windows-gate          # MSYS2 only; writes proof
    #   ./xbuild phys-del-gate --verify-windows-proof [p]  # tip SHA match (scp'd stamp)
    #   ./xbuild phys-del-gate --status-flip-preview [p]   # plan only after proof (wave801)
    #   ./xbuild phys-del-gate --status-flip-apply [p]     # confirm-gated apply (wave802)
    #   ./xbuild phys-del-gate --status-flip-commit-honesty # commit checklist (wave803)
    #   ./xbuild phys-del-gate --endgame-preview           # ENDGAME arm plan (wave805)
    #   ./xbuild phys-del-gate --endgame-arm-apply         # confirm-gated ENDGAME arm (wave806)
    #   ./xbuild phys-del-gate --endgame-arm-commit-honesty # arm commit checklist (wave807)
    #   ./xbuild phys-del-gate --delete-body-preview       # delete body plan (wave809; NOT rm)
    #   ./xbuild phys-del-gate --delete-body-commit-honesty # delete body commit checklist (wave810; NOT rm)
    # PLATFORM: SHARED shell; Windows gate body only on MSYS2
    shift
    bash compiler/scripts/phys_del_makefile_gate.sh "$@"
    ;;

  # === wave748–757 · 11.3.1 · R1 host-cc seed body + R3 cold-else ===
  heat-o|try-heat|heat|b7a-heat)
    # wave789: B7A heat shell auto-dispatch (G.7 有则补全; NOT physical delete).
    #   ./xbuild heat-o src/diag.o
    #   ./xbuild try-heat src/runtime_link_abi.o
    # Ladder prefer→R1→R2→gen via ensure try-heat; exit 3 = not ensure-owned.
    if [ "$#" -lt 2 ]; then
      echo "xbuild heat-o: need <out.o>  (e.g. ./xbuild heat-o src/diag.o)" >&2
      exit 2
    fi
    shift
    _heat_out="$1"
    shift || true
    _heat_args=()
    while [ "$#" -gt 0 ]; do
      _heat_args+=("$1")
      shift || true
    done
    (
      cd compiler
      bash scripts/ensure_host_cc_seed_o.sh try-heat "$_heat_out" "${_heat_args[@]}"
    )
    ;;

  host-cc-seed|rt-seed-slice|rt-slice|host-cc-seed-o|core-seed|core_seed|r1-core|r1-core-seed|frontend-glue|frontend_glue|r1-frontend-glue|r1-glue|main-runtime|main_runtime|r1-main-runtime|r1-main|alias-stubs|alias_stubs|r1-alias-stubs|r1-alias|extra-cflags|extra_cflags|r1-extra-cflags|r1-extra|pipeline-abi|misc-basename|misc_basename|misc|r1-misc-basename|r1-misc|seed-map|seed_map|r1-seed-map|r1-mismatch|mismatch|r3-cold-seed|r3_cold_seed|cold-seed|r3-cold)
    # Pure host-cc seed → .o single body (G.7). Lists = catalog keys only.
    #   host-cc-seed     → all swallowed R1 families
    #   rt-seed-slice    → RT_SEED_SLICE_OBJS only
    #   core-seed        → R1_CORE_SEED_OBJS only (wave749)
    #   frontend-glue    → R1_FRONTEND_GLUE_OBJS only (wave750; basename-mismatch map)
    #   main-runtime     → R1_MAIN_RUNTIME_OBJS only (wave751; multi-flag map)
    #   alias-stubs      → R1_ALIAS_STUBS_OBJS only (wave752; pure basename)
    #   extra-cflags     → R1_EXTRA_CFLAGS_OBJS only (wave753; pipeline_abi/-fPIE/sqlite/parser)
    #   misc-basename    → R1_MISC_BASENAME_OBJS only (wave754; glue/enc/ctx/pipeline_glue/…)
    #   seed-map         → R1_SEED_MAP_OBJS only (wave755/758; target_cpu/ast_seed/orch/thin_glue)
    #   r3-cold-seed     → R3_COLD_SEED_OBJS only (wave757; thin+rest cold-else)
    # Map: compiler/docs/LEAF_PATTERN_RESIDUAL.md
    # Usage:
    #   ./xbuild host-cc-seed              # all swallowed R1 families
    #   ./xbuild host-cc-seed --check
    #   ./xbuild host-cc-seed --force
    #   ./xbuild rt-seed-slice | … | seed-map | r3-cold-seed
    #   ./xbuild heat-o OUT.o              # wave789 B7A heat try-heat (separate case)
    _hcs_cmd="$1"
    _hcs_args=()
    case "$_hcs_cmd" in
      rt-seed-slice|rt-slice) _hcs_mode="rt-slice" ;;
      core-seed|core_seed|r1-core|r1-core-seed) _hcs_mode="core-seed" ;;
      frontend-glue|frontend_glue|r1-frontend-glue|r1-glue) _hcs_mode="frontend-glue" ;;
      main-runtime|main_runtime|r1-main-runtime|r1-main) _hcs_mode="main-runtime" ;;
      alias-stubs|alias_stubs|r1-alias-stubs|r1-alias) _hcs_mode="alias-stubs" ;;
      extra-cflags|extra_cflags|r1-extra-cflags|r1-extra|pipeline-abi) _hcs_mode="extra-cflags" ;;
      misc-basename|misc_basename|misc|r1-misc-basename|r1-misc) _hcs_mode="misc-basename" ;;
      seed-map|seed_map|r1-seed-map|r1-mismatch|mismatch) _hcs_mode="seed-map" ;;
      r3-cold-seed|r3_cold_seed|cold-seed|r3-cold) _hcs_mode="r3-cold-seed" ;;
      *) _hcs_mode="all" ;;  # host-cc-seed umbrella
    esac
    shift || true
    while [ "$#" -gt 0 ]; do
      case "$1" in
        --check|check|-c)
          _hcs_mode="--check"
          ;;
        --force|-f|force)
          _hcs_args+=(--force)
          ;;
        rt-slice|rt-seed-slice)
          _hcs_mode="rt-slice"
          ;;
        core-seed|core|core_seed|r1-core)
          _hcs_mode="core-seed"
          ;;
        frontend-glue|frontend_glue|glue|r1-frontend-glue|r1-glue)
          _hcs_mode="frontend-glue"
          ;;
        main-runtime|main_runtime|r1-main-runtime|r1-main)
          _hcs_mode="main-runtime"
          ;;
        alias-stubs|alias_stubs|r1-alias-stubs|r1-alias)
          _hcs_mode="alias-stubs"
          ;;
        extra-cflags|extra_cflags|r1-extra-cflags|r1-extra|pipeline-abi)
          _hcs_mode="extra-cflags"
          ;;
        misc-basename|misc_basename|misc|r1-misc-basename|r1-misc)
          _hcs_mode="misc-basename"
          ;;
        seed-map|seed_map|r1-seed-map|r1-mismatch|mismatch)
          _hcs_mode="seed-map"
          ;;
        r3-cold-seed|r3_cold_seed|cold-seed|r3-cold)
          _hcs_mode="r3-cold-seed"
          ;;
        all|families)
          _hcs_mode="all"
          ;;
        one)
          # Passthrough: ./xbuild host-cc-seed one OUT SEED [flags...]
          _hcs_mode="one"
          shift
          _hcs_args+=("$@")
          set --
          break
          ;;
        *)
          _hcs_args+=("$1")
          ;;
      esac
      shift || true
    done
    (
      cd compiler
      if [ "$_hcs_mode" = "--check" ]; then
        bash scripts/ensure_host_cc_seed_o.sh --check
      elif [ "$_hcs_mode" = "one" ]; then
        bash scripts/ensure_host_cc_seed_o.sh one "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "core-seed" ]; then
        bash scripts/ensure_host_cc_seed_o.sh core-seed "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "frontend-glue" ]; then
        bash scripts/ensure_host_cc_seed_o.sh frontend-glue "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "main-runtime" ]; then
        bash scripts/ensure_host_cc_seed_o.sh main-runtime "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "alias-stubs" ]; then
        bash scripts/ensure_host_cc_seed_o.sh alias-stubs "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "extra-cflags" ]; then
        bash scripts/ensure_host_cc_seed_o.sh extra-cflags "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "misc-basename" ]; then
        bash scripts/ensure_host_cc_seed_o.sh misc-basename "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "seed-map" ]; then
        bash scripts/ensure_host_cc_seed_o.sh seed-map "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "r3-cold-seed" ]; then
        bash scripts/ensure_host_cc_seed_o.sh r3-cold-seed "${_hcs_args[@]}"
      elif [ "$_hcs_mode" = "rt-slice" ]; then
        bash scripts/ensure_host_cc_seed_o.sh rt-slice "${_hcs_args[@]}"
      else
        bash scripts/ensure_host_cc_seed_o.sh all "${_hcs_args[@]}"
      fi
    )
    ;;

  # === CI / 冷启动 / 叶 .o（wave730：外层 0× make -C；叶 pattern residual 至 11.3）===
  compiler-all|ci-all)
    # wave784 B6: R5 CI host-cc body = scripts/compiler_all_ci.sh (G.7 single body).
    # Historical: `make -C compiler OPT=1 all` (xlang + xlang-c / seed).
    # Distinct from product `./xbuild all` (g05 relink). OPT defaults to 1.
    # Residual: leaf .o graph still make (B7); NOT physical delete of Makefile.
    # PLATFORM: SHARED
    if [ -z "${OPT+set}" ]; then OPT=1; fi
    export OPT
    (cd compiler && bash scripts/compiler_all_ci.sh)
    ;;
  bootstrap-driver-seed)
    # Cold-start: direct shell → bootstrap_driver_seed.sh (wave941).
    # wave744: shell ensure_prereqs then §5b sequence; lists via catalog.
    # wave935/936: all mk calls migrated to direct shell (0 make in --run path).
    # wave941: drop make entry — bootstrap_driver_seed.sh is 100% shell-primary
    # (catalog cache + ensure_prereqs + rebuild_leaves + link all shell).
    # The only make re-entry was XLANG_SKIP_SUBSCRIPT_MAKE (line 66-71) which
    # only fires when TARGET missing under SKIP; normal cold start is shell.
    # PLATFORM: SHARED — same shell path on Darwin/Linux/Windows MSYS2.
    (cd compiler && bash scripts/bootstrap_driver_seed.sh)
    ;;
  compiler-make)
    # Passthrough for residual leaves: std .o, CFLAGS=…, ASan rebuild, etc.
    # Usage: ./xbuild compiler-make <make-args...>
    shift
    if [ "$#" -eq 0 ]; then
      echo "Usage: ./xbuild compiler-make <make-args...>" >&2
      echo "  e.g. ./xbuild compiler-make ../std/io/io.o" >&2
      echo "       ./xbuild compiler-make all CFLAGS='-O0 -g'" >&2
      exit 1
    fi
    run_compiler_make "$@"
    ;;

  # === 编译器测试（wave720：test* / bootstrap-verify 全 shell；无 make -C）===
  test)
    (cd compiler && sh scripts/run_compiler_tests.sh all)
    ;;
  test_c)
    (cd compiler && sh scripts/run_compiler_tests.sh c)
    ;;
  test_x)
    (cd compiler && sh scripts/run_compiler_tests.sh x)
    ;;
  bootstrap-lexer)
    (cd compiler && sh scripts/bootstrap_token_lexer_smoke.sh lexer)
    ;;
  bootstrap-token)
    (cd compiler && sh scripts/bootstrap_token_lexer_smoke.sh token)
    ;;
  # wave844: parser smokes shell-primary (G.7; same family as token/lexer wave719)
  bootstrap-parser)
    (cd compiler && sh scripts/bootstrap_parser_smoke.sh parser)
    ;;
  bootstrap-parse-file)
    (cd compiler && sh scripts/bootstrap_parser_smoke.sh parse-file)
    ;;
  # wave845: xlang-x-pipeline shell-primary (G.7). wave946: post-delete honesty —
  # full archaeology link is the same shell body (catalog bags; no make -C).
  xlang-x-pipeline|xlang_x_pipeline)
    (cd compiler && sh scripts/xlang_x_pipeline.sh --check)
    echo "xbuild xlang-x-pipeline: structural --check only; full link: cd compiler && bash scripts/xlang_x_pipeline.sh" >&2
    ;;
  bootstrap-verify)
    (cd compiler && sh scripts/bootstrap_verify_bstrict.sh)
    ;;
  bootstrap-driver-bstrict)
    (cd compiler && sh scripts/bootstrap_driver_bstrict.sh)
    ;;

  # === 内核 QEMU 测试 ===
  kernel)
    sh tests/kernel/run-kernel-gate.sh
    ;;
  kernel-build)
    : "${X:?Usage: xlang-build.sh kernel-build X=file.x [ELF=out.elf]}"
    : "${ELF:=kernel.elf}"
    sh tests/kernel/build-kernel.sh "$X" "$ELF"
    ;;
  kernel-check)
    sh tests/kernel/static-check-gate.sh
    ;;
  kernel64-check)
    sh tests/kernel/kernel64-gate.sh
    ;;
  kernel-longmode)
    sh tests/kernel/longmode-gate.sh
    ;;
  kernel-multiboot2)
    sh tests/kernel/multiboot2-gate.sh
    ;;
  kernel-uefi-app)
    sh tests/kernel/uefi-app-gate.sh
    ;;
  kernel-ist)
    sh tests/kernel/ist-gate.sh
    ;;
  kernel-smp)
    sh tests/kernel/smp-gate.sh
    ;;
  kernel-send-sync)
    sh tests/kernel/send_sync_gate.sh
    ;;
  kernel-cross-arch)
    sh tests/kernel/cross-arch-gate.sh
    ;;
  kernel-uefi)
    sh tests/kernel/uefi-gate.sh
    ;;
  kernel-host-test)
    sh tests/kernel/host-test-gate.sh
    ;;
  kernel-stack-check)
    sh tests/kernel/stack-check-gate.sh
    ;;
  kernel-repro)
    sh tests/kernel/reproducible-gate.sh
    ;;

  # === 自举前 gate ===
  checklist)
    XLANG=./compiler/xlang bash tests/run-codegen-semantic-debt-gate.sh
    ;;
  struct-layout)
    sh tests/run-struct-layout-assert-gate.sh
    ;;
  ffi-deep)
    sh tests/run-ffi-deep-recursion-gate.sh
    ;;
  compiler-rt-audit)
    sh tests/run-compiler-rt-audit-gate.sh
    ;;
  c08)
    sh tests/run-c08-build-x-gate.sh
    ;;

  help|--help|-h)
    cat <<'EOF'
xbuild / xlang-build.sh — 统一构建入口（G-05 · G.7 同体）

推荐: ./xbuild <target>   （根 Makefile 仅 help→本入口）
别名: ./build.sh [target]  （wave731 · 11.4.1 薄转发本入口；默认 build）

编译器（推荐日常）:
  all / build / xlang   增量构建（build_tool → g05 relink 金标准）
  xlang-asm / asm       同上，显式 asm 子命令
  full / bstrict       全量 B-strict（XLANG_BUILD_TOOL_FULL=1）
  legacy               build_tool legacy 逐步路径
  build-tool           scripts/build_tool.sh（pinned seeds；无 make）
  first-time           build_tool.sh + 日常构建
  clean                scripts/clean_compiler.sh（无 make）

g05 产品链（wave733–735 · 11.1.6；产品 link 零 make）:
  ensure / g05-ensure           g05_ensure_relink_prereqs.sh
  link-env / g05-export         g05_relink_env.sh（打印/导出链接清单）
  link-product / relink         g05_prepare_and_relink（G05_SYNC_ASM=0）
  link-product-asm              g05_prepare_and_relink（G05_SYNC_ASM=1 → xlang_asm）
  migrate / migrate-x-objs      migrate_x_objs.sh（parser/typeck/codegen _x.o）
  migrate-gen                   ensure_migrate_gen.sh（parser/typeck/codegen _gen.c）
  lexer-gen                     ensure_migrate_gen.sh lexer（wave737）
  driver-gen                    ensure_driver_gen.sh（driver+preprocess _gen.c · wave738）
  preprocess-gen                ensure_driver_gen.sh preprocess
  lsp-gen                       ensure_lsp_pipeline_gen.sh（lsp trio · wave739）
  pipeline-gen                  ensure_lsp_pipeline_gen.sh pipeline
  lsp-pipeline-gen              ensure_lsp_pipeline_gen.sh all
  archaeology-gen               ensure_archaeology_gen.sh（Track L 考古 gen · wave740）
  driver-subcmd-gen             ensure_archaeology_gen.sh driver-all
  refresh-gate                  migrate shell + g05 relink + overlay xlang_asm
                                （体 refresh_xlang_asm_gate.sh；product *_gen 已 shell）

11.1.1/11.1.2 编排 DAG（wave742 库存 · wave743 调度 · wave744 prereq edges）:
  product-dag / build-dag / cold-dag   product_build_dag.sh dump
  product-dag --check                  校验节点体 + schedule + dry-run 三 profile
  product-dag --dry-run [product|refresh|cold]
  product-dag --run product|refresh|cold
  dag-dry-run / dag-run                同上简写
                                       （G.7 禁第二套 .o；run 只调既有 shell 体）
  driver-seed-prereqs                  DRIVER_SEED_PREREQS 边 dry-run/check/run
                                       （wave744 shell ensure；列表仍 mk catalog）

11.1.3/11.1.4 平台 + 链接策略（wave745 · 非 pure-ld 终局）:
  host-platform / platform             host OS/arch KEY=value
  host-platform --export               shell-sourceable exports
  host-platform --check                校验 doc + dump + 接线
  linker-policy                        命名 residual CC -o + preferred ld 库存
  linker-policy --check                同上机检
                                       体 = host_platform_linker.sh
                                       图 = compiler/docs/PLATFORM_LINKER.md
                                       （G.7 禁双 .o；禁第二套链接实现）
  leaf-patterns / leaf-residual        叶 .o pattern residual 库存（11.3.1 路径）
  leaf-patterns --check                校验 doc + class dump + 接线
  bc-inventory / bc-host-cc            BC 轨 · 阶段 8.3 产品 residual C 库存（wave963）
  bc-inventory --check                 冻结 glue/ast_pool/桩面；8.3.9 孤儿须 absent
                                       体 = bc_host_cc_product_inventory.sh
                                       图 = analysis/C迁移追踪.md §8.3
  l2-matrix / product-matrix           日常 L2 产品矩阵（wave299 · G.7 单权威）
                                       rv42／opt102／hello0／si0／f32；**捕获**预期非 0
                                       （return-value=42 是绿，禁 set -e 中途打断）
                                       体 = product_l2_matrix.sh
  l4 / l4-cold / true-cold             L4 真冷全测（wave341 · G.7 单权威）
                                       全擦 .o + 重链 seed/g05 + L2 矩阵 + 全量 bstrict
                                       （SKIP_BUILD=1；**不跑** xlang check）
                                       ./xbuild l4 --no-bstrict | --rebuild-only
                                       体 = product_l4_true_cold.sh
  phys-del-gate / phys-del             物理删 Makefile 执行闸门（wave799–810；非物理删）
  phys-del-gate --check                硬拒删 + preflight 诚实 + proof + flip + endgame + delete-body-preview + commit-honesty
  phys-del-gate --dry-run-delete       仅列将删面
  phys-del-gate --run-windows-gate     MSYS2 上跑 hybrid min-gate 并写 proof stamp
  phys-del-gate --verify-windows-proof 校验 proof tip 与 HEAD（非 STATUS 翻转）
  phys-del-gate --status-flip-preview  有 proof 后打印 STATUS 翻转计划（wave801；不改 leaf）
  phys-del-gate --status-flip-apply    proof+confirm 改 leaf STATUS（wave802；非物理删）
  phys-del-gate --endgame-preview      STATUS 绿后打印 ENDGAME=1 计划（wave805；不 arm）
  phys-del-gate --endgame-arm-apply    STATUS+confirm 改 leaf ENDGAME（wave806；非物理删）
  phys-del-gate --endgame-arm-commit-honesty  树 arm commit 清单/契约（wave807；不改 leaf）
  phys-del-gate --delete-body-preview  TREE_ARMED 后删体计划（wave809；不 rm）
  phys-del-gate --delete-body-commit-honesty  删体 commit 清单/契约（wave810；不 rm）
                                       体 = phys_del_makefile_gate.sh
  host-cc-seed / rt-seed-slice / core-seed / frontend-glue / main-runtime / alias-stubs / extra-cflags / misc-basename / seed-map / r3-cold-seed
                                       R1 host-cc 体（wave748–752 五族）
  host-cc-seed --check                 校验 catalog + thin Makefile + 八族
  host-cc-seed --force                 强制重编已吞 R1 族
  heat-o / try-heat OUT.o              B7A heat shell 自动分发（wave789；非物理删）
                                       体 = leaf_pattern_residual.sh
                                       图 = compiler/docs/LEAF_PATTERN_RESIDUAL.md
                                       （非物理删 make；G.7 禁双 .o 清单）

CI / 冷启动（外层 0× make；Makefile 已删 wave941）:
  compiler-all / ci-all      scripts/compiler_all_ci.sh（CI host-cc；≠ 产品 all；wave784）
  bootstrap-driver-seed      冷启动（shell ensure_prereqs → §5b 编排）
  compiler-make <args…>      叶 .o / archaeology phony 分发（std .o / stub / ASan）
                             体 = tests/lib/compiler-make.sh（G.7 单 hub · 0-make）

测试 / 自举:
  test / test_c / test_x     scripts/run_compiler_tests.sh
  bootstrap-token / lexer    scripts/bootstrap_token_lexer_smoke.sh
  bootstrap-parser / parse-file  scripts/bootstrap_parser_smoke.sh (wave844)
  xlang-x-pipeline               scripts/xlang_x_pipeline.sh --check (wave845; full=same shell)
  bootstrap-driver-bstrict   scripts/bootstrap_driver_bstrict.sh
  bootstrap-verify           scripts/bootstrap_verify_bstrict.sh

内核 (QEMU):
  kernel               全部内核 gate
  kernel-build X=      构建单个内核 ELF
  …（kernel-* 与 tests/kernel 一致）

其它 gate:
  checklist / struct-layout / ffi-deep / compiler-rt-audit / c08

环境:
  XLANG_BUILD_TOOL_FULL=1   full 目标走 bootstrap-driver-bstrict
  XLANG_G05_LEGACY_SMOKE=1  c08 gate 额外跑 ./build_tool ./xlang legacy（默认跳过）

实现层（用户勿直接依赖）:
  tests/lib/compiler-make.sh               — 叶分发 hub（0-make；tests + xbuild）
  compiler/scripts/g05_build_xlang_asm.sh  — build_tool 唯一 asm 出口
  compiler/scripts/g05_prepare_and_relink.sh — ensure+env+link 编排
  compiler/scripts/refresh_xlang_asm_gate.sh — P0 refresh 门禁体（wave734）
  compiler/scripts/driver_seed_obj_catalog.sh — mk/*.mk 单权威列表/CFLAGS
  compiler/Makefile / 根 Makefile          — 已物理删除（wave941）；勿再新建

日常优先:
  ./xbuild build
  cd compiler && ./build_tool ./xlang
EOF
    ;;
  *)
    echo "Unknown target: $TARGET (try: ./xbuild help)" >&2
    exit 1
    ;;
esac
