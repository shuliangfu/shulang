/* seeds/async_asm_pool.from_x.c — G-02f-80 product cold-start TU
 * G-02f-104 helper gates.
 * Promoted from compiler/src/async/async_asm_pool.inc (stub/bridge; retired .inc).
 * Compile: cc -c seeds/async_asm_pool.from_x.c → src/async/async_asm_pool.o
 *
 * R2 full（2026-07-21）：公共业务由 full .x 提供（helpers + build_layout）：
 *   asm_pool_expr_is_await / has_await / is_var_named / refs_name / block_rest_refs_name
 *   + type_size_bytes + live_add + fn_id_from_name + func_needs_cps + build_layout
 * FROM_X 下本文件业务 H=0（仅 slice marker）。
 * Cap residual：无（build_layout 已 pure 真迁）。
 * Unbundle（2026-07-21）：不再 #include 进 pipeline_glue.c；独立 TU 入
 *   DRIVER_SEED_SUPPORT_EXTRA / g05_relink_env（所有模式）。
 * 冷启动/无 PREFER：完整 C 体 → src/async/async_asm_pool.o。
 * PREFER：src/asm/async_asm_pool.x + 本 rest (-DXLANG_ASYNC_ASM_POOL_FROM_X) ld -r。
 * PLATFORM: SHARED — pool API 跨平台一致。
 */
/**
 * async_asm_pool.c — pool AST async CPS 帧 layout 分析（WPO-S3 / asm 后端）
 *
 * 文件职责：线性扫描 stmt_order，在 await 边界收集 continuation 仍引用的 let；
 *           估算 frame data 区字段偏移，供 pipeline_glue emit save/restore。
 */
#include "async_asm_pool.h"
#include <string.h>

struct ast_ASTArena;
struct ast_Module;

extern int32_t pipeline_module_func_is_async_at(struct ast_Module *m, int32_t fi);
extern int32_t pipeline_module_func_body_ref_at(struct ast_Module *m, int32_t fi);
extern int32_t pipeline_module_func_name_len_at(struct ast_Module *m, int32_t fi);
extern void pipeline_module_func_name_copy64(struct ast_Module *m, int32_t fi, uint8_t *dst);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_unary_operand_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_as_operand_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_as_target_type_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_binop_left_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_binop_right_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_base_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_index_base_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_index_index_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_var_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out);
extern int32_t ast_ast_block_num_lets(struct ast_ASTArena *a, int32_t block_ref);
extern int32_t ast_ast_block_num_expr_stmts(struct ast_ASTArena *a, int32_t block_ref);
extern int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena *a, int32_t block_ref);
extern uint8_t ast_ast_block_stmt_order_kind(struct ast_ASTArena *a, int32_t block_ref, int32_t si);
extern int32_t ast_ast_block_stmt_order_idx(struct ast_ASTArena *a, int32_t block_ref, int32_t si);
extern int32_t pipeline_block_let_init_ref(struct ast_ASTArena *a, int32_t br, int32_t li);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena *a, int32_t br, int32_t li);
extern int32_t pipeline_block_let_name_len(struct ast_ASTArena *a, int32_t br, int32_t li);
extern void pipeline_block_let_name_copy64(struct ast_ASTArena *a, int32_t br, int32_t li, uint8_t *dst);
extern int32_t ast_pipeline_block_expr_stmt_ref(struct ast_ASTArena *a, int32_t br, int32_t ei);
extern int32_t pipeline_asm_block_final_expr_ref_at(struct ast_ASTArena *a, int32_t br);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena *a, int32_t type_ref);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena *a, int32_t type_ref, uint8_t *out);
extern int32_t typeck_x_type_size_from_layout_glue(struct ast_Module *module, struct ast_ASTArena *arena,
                                                    int32_t layout_idx, int32_t depth);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module *m, int32_t idx);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module *m, int32_t idx, int32_t bi);
extern int32_t pipeline_module_num_struct_layouts_at(struct ast_Module *m);

/** C AST_EXPR_AWAIT(54) 与 X EXPR_AS(54) 碰撞；X EXPR_AWAIT=55。 */
#define ASM_POOL_KIND_ORD54 54
#define ASM_POOL_KIND_X_AWAIT 55

/* R2 full：FROM_X 时全部业务体省略（由 src/asm/async_asm_pool.x 提供）；
 * 冷启动无宏时本文件提供完整 C 体（含 build_layout）。
 * 宏边界：XLANG_ASYNC_ASM_POOL_FROM_X
 */
#ifndef XLANG_ASYNC_ASM_POOL_FROM_X
/** X pool EXPR_AWAIT(55) 或 C parser await（序 54 且非 as cast）。 */
/* G-02f-142：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t asm_pool_expr_is_await(struct ast_ASTArena *a, int32_t er) {
    int32_t ko, uop;
    if (!a || er <= 0)
        return 0;
    ko = pipeline_expr_kind_ord_at(a, er);
    if (ko == ASM_POOL_KIND_X_AWAIT) {
        uop = pipeline_expr_unary_operand_ref_at(a, er);
        return uop > 0 ? 1 : 0;
    }
    if (ko != ASM_POOL_KIND_ORD54)
        return 0;
    if (pipeline_expr_as_target_type_ref_at(a, er) > 0 || pipeline_expr_as_operand_ref_at(a, er) > 0)
        return 0;
    uop = pipeline_expr_unary_operand_ref_at(a, er);
    return uop > 0 ? 1 : 0;
}


/** 表达式树是否含 await。 */
/* G-02f-142：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t asm_pool_expr_has_await(struct ast_ASTArena *a, int32_t er) {
    int32_t ko;
    if (!a || er <= 0)
        return 0;
    if (asm_pool_expr_is_await(a, er))
        return 1;
    ko = pipeline_expr_kind_ord_at(a, er);
    if (ko >= 4 && ko <= 21)
        return asm_pool_expr_has_await(a, pipeline_expr_binop_left_ref_at(a, er)) ||
               asm_pool_expr_has_await(a, pipeline_expr_binop_right_ref_at(a, er));
    if (ko == 22 || ko == 23 || ko == 24 || ko == ASM_POOL_KIND_ORD54 || ko == ASM_POOL_KIND_X_AWAIT ||
        ko == 51 || ko == 52)
        return asm_pool_expr_has_await(a, pipeline_expr_unary_operand_ref_at(a, er));
    if (ko == 44)
        return asm_pool_expr_has_await(a, pipeline_expr_field_access_base_ref(a, er));
    if (ko == 47)
        return asm_pool_expr_has_await(a, pipeline_expr_index_base_ref(a, er)) ||
               asm_pool_expr_has_await(a, pipeline_expr_index_index_ref(a, er));
    return 0;
}


/** VAR 是否引用给定 let 名。 */
/* G-02f-142：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t asm_pool_expr_is_var_named(struct ast_ASTArena *a, int32_t er, const uint8_t *name, int32_t nlen) {
    int32_t vlen;
    uint8_t vbuf[128];
    int32_t i;
    if (!a || er <= 0 || !name || nlen <= 0)
        return 0;
    if (pipeline_expr_kind_ord_at(a, er) != 3)
        return 0;
    vlen = pipeline_expr_var_name_len(a, er);
    if (vlen != nlen)
        return 0;
    pipeline_expr_var_name_into(a, er, vbuf);
    for (i = 0; i < nlen; i++) {
        if (vbuf[i] != name[i])
            return 0;
    }
    return 1;
}


/** 表达式是否引用变量名。 */
/* G-02f-142：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t asm_pool_expr_refs_name(struct ast_ASTArena *a, int32_t er, const uint8_t *name, int32_t nlen) {
    int32_t ko;
    if (!a || er <= 0 || !name || nlen <= 0)
        return 0;
    if (asm_pool_expr_is_var_named(a, er, name, nlen))
        return 1;
    ko = pipeline_expr_kind_ord_at(a, er);
    if (ko >= 4 && ko <= 21)
        return asm_pool_expr_refs_name(a, pipeline_expr_binop_left_ref_at(a, er), name, nlen) ||
               asm_pool_expr_refs_name(a, pipeline_expr_binop_right_ref_at(a, er), name, nlen);
    if (ko == 22 || ko == 23 || ko == 24 || ko == ASM_POOL_KIND_ORD54 || ko == ASM_POOL_KIND_X_AWAIT ||
        ko == 51 || ko == 52)
        return asm_pool_expr_refs_name(a, pipeline_expr_unary_operand_ref_at(a, er), name, nlen);
    if (ko == 44)
        return asm_pool_expr_refs_name(a, pipeline_expr_field_access_base_ref(a, er), name, nlen);
    if (ko == 47)
        return asm_pool_expr_refs_name(a, pipeline_expr_index_base_ref(a, er), name, nlen) ||
               asm_pool_expr_refs_name(a, pipeline_expr_index_index_ref(a, er), name, nlen);
    return 0;
}


/** stmt_order(from_exclusive+1..) 是否仍引用 name。 */
/* G-02f-142：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t asm_pool_block_rest_refs_name(struct ast_ASTArena *a, int32_t br, int32_t from_exclusive,
                                             const uint8_t *name, int32_t nlen) {
    int32_t nso;
    int32_t si;
    if (!a || br <= 0 || !name || nlen <= 0)
        return 0;
    nso = ast_ast_block_num_stmt_order(a, br);
    for (si = from_exclusive + 1; si < nso; si++) {
        uint8_t kind = ast_ast_block_stmt_order_kind(a, br, si);
        int32_t idx = ast_ast_block_stmt_order_idx(a, br, si);
        if (kind == 1 && idx >= 0 && idx < ast_ast_block_num_lets(a, br)) {
            int32_t init = pipeline_block_let_init_ref(a, br, idx);
            if (init > 0 && asm_pool_expr_refs_name(a, init, name, nlen))
                return 1;
        } else if (kind == 2 && idx >= 0 && idx < ast_ast_block_num_expr_stmts(a, br)) {
            int32_t ex = ast_pipeline_block_expr_stmt_ref(a, br, idx);
            if (ex > 0 && asm_pool_expr_refs_name(a, ex, name, nlen))
                return 1;
        }
    }
    {
        int32_t fin = pipeline_asm_block_final_expr_ref_at(a, br);
        if (fin > 0 && asm_pool_expr_refs_name(a, fin, name, nlen))
            return 1;
    }
    return 0;
}


/** let 类型字节数（i32/struct 等；失败时默认 8）。 */
/* G-02f-142：避免 m->num_struct_layouts（forward Module）；走 pipeline_module_num_struct_layouts_at */
int32_t asm_pool_type_size_bytes(struct ast_ASTArena *a, struct ast_Module *m, int32_t type_ref) {
    int32_t kind;
    uint8_t name[128];
    int32_t nlen;
    int32_t k;
    int32_t nlay;
    if (!a || type_ref <= 0)
        return 8;
    kind = pipeline_type_kind_ord_at(a, type_ref);
    if (kind == 0 || kind == 1)
        return 4;
    if (kind == 2)
        return 1;
    if (kind == 3 || kind == 4 || kind == 5 || kind == 6 || kind == 7 || kind == 9)
        return 8;
    if (kind == 8) {
        nlen = pipeline_type_named_name_into(a, type_ref, name);
        if (nlen <= 0 || !m)
            return 8;
        nlay = pipeline_module_num_struct_layouts_at(m);
        for (k = 0; k < nlay; k++) {
            int32_t ln = pipeline_module_struct_layout_name_len(m, k);
            int32_t j;
            int32_t eq = 1;
            if (ln != nlen)
                continue;
            for (j = 0; j < nlen; j++) {
                if (pipeline_module_struct_layout_name_byte_at(m, k, j) != name[j]) {
                    eq = 0;
                    break;
                }
            }
            if (eq) {
                int32_t sz = typeck_x_type_size_from_layout_glue(m, a, k, 0);
                return sz > 0 ? sz : 8;
            }
        }
        return 8;
    }
    return 8;
}


/** live 表去重追加。 */
/* G-02f-144：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
void asm_pool_live_add(AsyncAsmPoolLayout *lay, const uint8_t *name, int32_t nlen, int32_t sz) {
    int32_t i;
    int32_t off;
    if (!lay || !name || nlen <= 0 || nlen > 127 || lay->num_live >= ASYNC_LIVE_MAX_VARS)
        return;
    for (i = 0; i < lay->num_live; i++) {
        if (lay->live[i].name_len == nlen && memcmp(lay->live[i].name, name, (size_t)nlen) == 0)
            return;
    }
    off = 0;
    for (i = 0; i < lay->num_live; i++)
        off += lay->live[i].size_bytes;
    memcpy(lay->live[lay->num_live].name, name, (size_t)nlen);
    lay->live[lay->num_live].name[nlen] = '\0';
    lay->live[lay->num_live].name_len = nlen;
    lay->live[lay->num_live].size_bytes = sz > 0 ? sz : 4;
    lay->live[lay->num_live].frame_data_off = off;
    lay->num_live++;
}


/* G-02f-143：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
uint32_t async_asm_pool_fn_id_from_name(const uint8_t *name, int32_t name_len) {
    uint32_t h = 2166136261u;
    int32_t i;
    if (!name || name_len <= 0)
        return 1u;
    for (i = 0; i < name_len; i++)
        h = (h ^ (uint32_t)name[i]) * 16777619u;
    return h ? h : 1u;
}

/* G-02f-143：逻辑源 .x（真迁）；seed 保留同语义 C 供产品 cc */
int32_t async_asm_pool_func_needs_cps(struct ast_ASTArena *arena, struct ast_Module *mod, int32_t func_index) {
    int32_t br;
    if (!arena || !mod || func_index < 0)
        return 0;
    if (!pipeline_module_func_is_async_at(mod, func_index))
        return 0;
    br = pipeline_module_func_body_ref_at(mod, func_index);
    if (br <= 0)
        return 0;
    {
        int32_t nso = ast_ast_block_num_stmt_order(arena, br);
        int32_t si;
        for (si = 0; si < nso; si++) {
            if (ast_ast_block_stmt_order_kind(arena, br, si) == 1) {
                int32_t li = ast_ast_block_stmt_order_idx(arena, br, si);
                int32_t init = pipeline_block_let_init_ref(arena, br, li);
                if (init > 0 && asm_pool_expr_has_await(arena, init))
                    return 1;
            }
        }
    }
    return 0;
}

/* G-02f-R2：逻辑源 .x（真迁）；seed 保留同语义 C 供冷启动 / pipeline_glue #include */
int32_t async_asm_pool_build_layout(struct ast_ASTArena *arena, struct ast_Module *mod, int32_t func_index,
                                    AsyncAsmPoolLayout *out) {
    int32_t br;
    int32_t nso;
    int32_t si;
    uint8_t fname[128];
    int32_t fnlen;
    uint8_t defined_names[ASYNC_LIVE_MAX_VARS][128];
    int32_t defined_lens[ASYNC_LIVE_MAX_VARS];
    int32_t n_def;
    if (!arena || !mod || !out || func_index < 0)
        return -1;
    memset(out, 0, sizeof(*out));
    if (!async_asm_pool_func_needs_cps(arena, mod, func_index))
        return 1;
    fnlen = pipeline_module_func_name_len_at(mod, func_index);
    pipeline_module_func_name_copy64(mod, func_index, fname);
    out->fn_id = async_asm_pool_fn_id_from_name(fname, fnlen);
    out->await_stmt_idx = -1;
    br = pipeline_module_func_body_ref_at(mod, func_index);
    nso = ast_ast_block_num_stmt_order(arena, br);
    n_def = 0;
    for (si = 0; si < nso; si++) {
        uint8_t kind = ast_ast_block_stmt_order_kind(arena, br, si);
        int32_t idx = ast_ast_block_stmt_order_idx(arena, br, si);
        if (kind != 1 || idx < 0 || idx >= ast_ast_block_num_lets(arena, br))
            continue;
        {
            int32_t init = pipeline_block_let_init_ref(arena, br, idx);
            int32_t li;
            if (init > 0 && asm_pool_expr_has_await(arena, init)) {
                out->num_awaits++;
                if (out->await_stmt_idx < 0)
                    out->await_stmt_idx = si;
                for (li = 0; li < n_def; li++) {
                    if (asm_pool_block_rest_refs_name(arena, br, si, defined_names[li], defined_lens[li])) {
                        int32_t tref = 0;
                        int32_t j;
                        for (j = 0; j < ast_ast_block_num_lets(arena, br); j++) {
                            if (pipeline_block_let_name_len(arena, br, j) == defined_lens[li]) {
                                uint8_t nb[128];
                                pipeline_block_let_name_copy64(arena, br, j, nb);
                                if (memcmp(nb, defined_names[li], (size_t)defined_lens[li]) == 0) {
                                    tref = pipeline_block_let_type_ref(arena, br, j);
                                    break;
                                }
                            }
                        }
                        asm_pool_live_add(out, defined_names[li], defined_lens[li],
                                          asm_pool_type_size_bytes(arena, mod, tref));
                    }
                }
                /** await let 自身（如 mid）若后续仍引用，suspend 前须入帧（同 C static hoist）。 */
                {
                    uint8_t cur_nb[128];
                    int32_t cur_len = pipeline_block_let_name_len(arena, br, idx);
                    if (cur_len > 0 && cur_len <= 127) {
                        pipeline_block_let_name_copy64(arena, br, idx, cur_nb);
                        if (asm_pool_block_rest_refs_name(arena, br, si, cur_nb, cur_len)) {
                            int32_t tref = pipeline_block_let_type_ref(arena, br, idx);
                            asm_pool_live_add(out, cur_nb, cur_len, asm_pool_type_size_bytes(arena, mod, tref));
                        }
                    }
                }
            }
        }
        {
            uint8_t lnb[128];
            int32_t llen = pipeline_block_let_name_len(arena, br, idx);
            if (llen > 0 && llen <= 127 && n_def < ASYNC_LIVE_MAX_VARS) {
                pipeline_block_let_name_copy64(arena, br, idx, lnb);
                memcpy(defined_names[n_def], lnb, (size_t)llen);
                defined_lens[n_def] = llen;
                n_def++;
            }
        }
    }
    return out->num_awaits > 0 ? 0 : 1;
}
#else
/* FROM_X rest：业务 H=0；.x 提供全部公共符号 */
#endif /* XLANG_ASYNC_ASM_POOL_FROM_X */

/** Slice marker for hybrid/PREFER ld -r prove (always present). */
void async_asm_pool_slice_marker(void) {}
