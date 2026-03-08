/**
 * codegen.c — 代码生成实现（AST → C）
 *
 * 文件职责：实现 codegen.h 声明的 codegen_module_to_c 与 codegen_library_module_to_c，将 AST 转为 C 源码供系统 cc 编译。
 * 所属模块：编译器后端 codegen，compiler/src/codegen/；实现 codegen.h。
 * 与其它文件的关系：依赖 include/ast.h；被 main 在 typeck 通过后调用；输出到 main 提供的临时文件流。
 * 重要约定：入口模块仅支持 main；生成 Hello World 的 printf，且 return 使用 main 体整数字面量的值（阶段 4 方案 B 扩展）；库模块仅输出注释（阶段 7.3 多文件占位）。
 */

#include "codegen/codegen.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

/** 用于生成唯一 match 临时变量名，避免嵌套 match 时冲突 */
static int codegen_match_id;

/**
 * 将 AST 类型写入 buf，用于递归拼指针类型（*T、**T 等）。
 * 参数：ty 类型节点；buf 输出缓冲区；size 缓冲区大小。副作用：写入 buf。
 */
static void c_type_to_buf(const struct ASTType *ty, char *buf, size_t size) {
    if (!ty || size == 0) return;
    if (ty->kind == AST_TYPE_PTR && ty->elem_type) {
        static char inner_buf[256];
        c_type_to_buf(ty->elem_type, inner_buf, sizeof(inner_buf));
        snprintf(buf, size, "%s *", inner_buf);
        return;
    }
    /* 数组类型 [N]T：声明时用 elem_type name[N]，此处只写元素类型（文档 §6.2） */
    if (ty->kind == AST_TYPE_ARRAY && ty->elem_type) {
        c_type_to_buf(ty->elem_type, buf, size);
        return;
    }
    /* 切片 []T：C 侧为 struct shulang_slice_<elem> { elem* data; size_t len; }（文档 §6.3） */
    if (ty->kind == AST_TYPE_SLICE && ty->elem_type) {
        static char elem_buf[128];
        c_type_to_buf(ty->elem_type, elem_buf, sizeof(elem_buf));
        snprintf(buf, size, "struct shulang_slice_%s", elem_buf);
        return;
    }
    const char *s = "int";
    switch (ty->kind) {
        case AST_TYPE_I32:   s = "int32_t"; break;
        case AST_TYPE_BOOL:  s = "int"; break;
        case AST_TYPE_U8:    s = "uint8_t"; break;
        case AST_TYPE_U32:   s = "uint32_t"; break;
        case AST_TYPE_U64:   s = "uint64_t"; break;
        case AST_TYPE_I64:   s = "int64_t"; break;
        case AST_TYPE_USIZE: s = "size_t"; break;
        case AST_TYPE_ISIZE: s = "ptrdiff_t"; break;
        case AST_TYPE_NAMED: s = ty->name ? ty->name : "int"; break;
        default: break;
    }
    snprintf(buf, size, "%s", s);
}

/**
 * 将 AST 类型映射为 C 类型字符串；用于 const/let 声明。支持裸指针 *T（文档 §5.1）。
 * 参数：ty 类型节点，不可为 NULL。返回值：C 类型名（静态缓冲区，非线程安全）。
 */
static const char *c_type_str(const struct ASTType *ty) {
    if (!ty) return "int";
    static char buf[256];
    c_type_to_buf(ty, buf, sizeof(buf));
    return buf;
}

/** 已输出的切片结构体 elem 类型 key，避免重复定义；最多 16 种 */
#define MAX_SLICE_STRUCTS 16
static const char *codegen_slice_emitted[MAX_SLICE_STRUCTS];
static int codegen_slice_emitted_n;

/**
 * 若 ty 为切片类型，则向 out 输出一次 struct shulang_slice_<elem> { elem* data; size_t len; }（文档 §6.3）。
 * 同一 elem 类型只输出一次。无返回值。
 */
static void ensure_slice_struct(const struct ASTType *ty, FILE *out) {
    if (!ty || ty->kind != AST_TYPE_SLICE || !ty->elem_type || !out) return;
    const char *key = c_type_str(ty->elem_type);
    for (int i = 0; i < codegen_slice_emitted_n; i++)
        if (codegen_slice_emitted[i] && strcmp(codegen_slice_emitted[i], key) == 0) return;
    if (codegen_slice_emitted_n >= MAX_SLICE_STRUCTS) return;
    codegen_slice_emitted[codegen_slice_emitted_n++] = key;
    fprintf(out, "struct shulang_slice_%s { %s *data; size_t len; };\n", key, key);
}

/** 前向声明，供 codegen_init 使用 */
static int codegen_expr(const struct ASTExpr *e, FILE *out);

/**
 * 输出 const/let 的初始化表达式。block 用于“切片从数组”时查数组长度；可为 NULL（则不解析数组→切片）。
 * 当类型为数组且初值为字面量 0 时输出 {0}；当类型为切片且初值为数组变量时输出 { .data = name, .len = N }。
 */
static int codegen_init(const struct ASTType *ty, const struct ASTExpr *init, FILE *out, const struct ASTBlock *block) {
    if (ty && ty->kind == AST_TYPE_ARRAY && init && init->kind == AST_EXPR_LIT && init->value.int_val == 0) {
        fprintf(out, "{0}");
        return 0;
    }
    if (ty && ty->kind == AST_TYPE_SLICE && init && init->kind == AST_EXPR_VAR && block) {
        const char *name = init->value.var.name;
        for (int i = 0; i < block->num_consts; i++)
            if (block->const_decls[i].name && name && strcmp(block->const_decls[i].name, name) == 0 &&
                block->const_decls[i].type && block->const_decls[i].type->kind == AST_TYPE_ARRAY) {
                fprintf(out, "{ .data = %s, .len = %d }", name ? name : "", block->const_decls[i].type->array_size);
                return 0;
            }
        for (int i = 0; i < block->num_lets; i++)
            if (block->let_decls[i].name && name && strcmp(block->let_decls[i].name, name) == 0 &&
                block->let_decls[i].type && block->let_decls[i].type->kind == AST_TYPE_ARRAY) {
                fprintf(out, "{ .data = %s, .len = %d }", name ? name : "", block->let_decls[i].type->array_size);
                return 0;
            }
    }
    return codegen_expr(init, out);
}

/**
 * 将单棵表达式生成 C 表达式写入 out（LIT 输出整数字面量，ADD/SUB 递归输出左 op 右）。
 * 参数：e 表达式根节点，不可为 NULL；out 输出流。返回值：0 成功，-1 不支持的节点类型。副作用：仅写 out。
 */
static int codegen_expr(const struct ASTExpr *e, FILE *out) {
    if (!e || !out) return -1;
    switch (e->kind) {
        case AST_EXPR_LIT:
            fprintf(out, "%d", e->value.int_val);
            return 0;
        case AST_EXPR_BOOL_LIT:
            fprintf(out, "%d", e->value.int_val ? 1 : 0);
            return 0;
        case AST_EXPR_VAR:
            fprintf(out, "%s", e->value.var.name ? e->value.var.name : "");
            return 0;
        case AST_EXPR_ADD: {
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR);
            int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " + ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_SUB: {
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind >= AST_EXPR_EQ && l->kind <= AST_EXPR_LOGOR);
            int need_r = (r->kind >= AST_EXPR_EQ && r->kind <= AST_EXPR_LOGOR);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " - ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_MUL: {
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
            int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " * ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_DIV: {
            const struct ASTExpr *l = e->value.binop.left, *r = e->value.binop.right;
            int need_l = (l->kind == AST_EXPR_ADD || l->kind == AST_EXPR_SUB);
            int need_r = (r->kind == AST_EXPR_ADD || r->kind == AST_EXPR_SUB);
            if (need_l) fprintf(out, "(");
            if (codegen_expr(l, out) != 0) return -1;
            if (need_l) fprintf(out, ")");
            fprintf(out, " / ");
            if (need_r) fprintf(out, "(");
            if (codegen_expr(r, out) != 0) return -1;
            if (need_r) fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_MOD:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " %% ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_SHL:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " << ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_SHR:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >> ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITAND:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " & ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITOR:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " | ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_BITXOR:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " ^ ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_EQ:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " == ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_NE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " != ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LT:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " < ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " <= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_GT:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " > ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_GE:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " >= ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LOGAND:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " && ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_LOGOR:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " || ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_NEG:
            fprintf(out, "(-");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_BITNOT:
            fprintf(out, "(~");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_LOGNOT:
            fprintf(out, "(!");
            if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
            fprintf(out, ")");
            return 0;
        case AST_EXPR_IF: {
            /* 若 then 分支为 panic，条件用 __builtin_expect(!!(cond),0) 包裹，使热点路径线性取指（控制流清单 §8.3） */
            const struct ASTExpr *then_e = e->value.if_expr.then_expr;
            int then_is_panic = (then_e && then_e->kind == AST_EXPR_PANIC);
            fprintf(out, "(");
            if (then_is_panic) {
                fprintf(out, "__builtin_expect(!!(");
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, "), 0) ? ");
            } else {
                if (codegen_expr(e->value.if_expr.cond, out) != 0) return -1;
                fprintf(out, " ? ");
            }
            if (codegen_expr(then_e, out) != 0) return -1;
            fprintf(out, " : ");
            if (e->value.if_expr.else_expr) {
                if (codegen_expr(e->value.if_expr.else_expr, out) != 0) return -1;
            } else {
                fprintf(out, "0");
            }
            fprintf(out, ")");
            return 0;
        }
        case AST_EXPR_PANIC:
            /* 冷路径：通过辅助函数标记 noreturn+cold，避免污染 ICache（控制流清单 §8.3、§8.4） */
            if (e->value.unary.operand) {
                fprintf(out, "shulang_panic_(1, ");
                if (codegen_expr(e->value.unary.operand, out) != 0) return -1;
                fprintf(out, ")");
            } else {
                fprintf(out, "shulang_panic_(0, 0)");
            }
            return 0;
        case AST_EXPR_FIELD_ACCESS:
            /* 字段访问 base.field，基表达式加括号以保证 a+b.x 为 (a+b).x */
            fprintf(out, "(");
            if (codegen_expr(e->value.field_access.base, out) != 0) return -1;
            fprintf(out, ").%s", e->value.field_access.field_name ? e->value.field_access.field_name : "");
            return 0;
        case AST_EXPR_STRUCT_LIT: {
            /* 结构体字面量 TypeName { f: expr, ... } → (struct Name){ .f = expr, ... }（C99 指定初始化） */
            fprintf(out, "(struct %s){ ", e->value.struct_lit.struct_name ? e->value.struct_lit.struct_name : "");
            for (int i = 0; i < e->value.struct_lit.num_fields; i++) {
                if (i) fprintf(out, ", ");
                fprintf(out, ".%s = ", e->value.struct_lit.field_names[i] ? e->value.struct_lit.field_names[i] : "");
                if (codegen_expr(e->value.struct_lit.inits[i], out) != 0) return -1;
            }
            fprintf(out, " }");
            return 0;
        }
        case AST_EXPR_ARRAY_LIT: {
            /* 数组字面量 [e1, e2, ...] → C 的 { e1, e2, ... }（文档 §6.2） */
            fprintf(out, "{ ");
            for (int i = 0; i < e->value.array_lit.num_elems; i++) {
                if (i) fprintf(out, ", ");
                if (codegen_expr(e->value.array_lit.elems[i], out) != 0) return -1;
            }
            fprintf(out, " }");
            return 0;
        }
        case AST_EXPR_INDEX: {
            /* 数组 base[i] → (base)[i]；切片 base[i] → (base).data[i]（文档 §6.3） */
            fprintf(out, "(");
            if (codegen_expr(e->value.index.base, out) != 0) return -1;
            if (e->value.index.base_is_slice)
                fprintf(out, ").data[");
            else
                fprintf(out, ")[");
            if (codegen_expr(e->value.index.index_expr, out) != 0) return -1;
            fprintf(out, "]");
            return 0;
        }
        case AST_EXPR_MATCH: {
            /* 按控制流清单 §8.6：密度 > 0.7 时生成 switch 促生跳转表 O(1)，否则保持三元链 */
            const struct ASTExpr *me = e->value.match_expr.matched_expr;
            const struct ASTMatchArm *arms = e->value.match_expr.arms;
            int num_arms = e->value.match_expr.num_arms;
            int value_min = INT_MAX, value_max = INT_MIN, lit_count = 0;
            for (int i = 0; i < num_arms; i++) {
                if (arms[i].is_wildcard) continue;
                lit_count++;
                if (arms[i].lit_val < value_min) value_min = arms[i].lit_val;
                if (arms[i].lit_val > value_max) value_max = arms[i].lit_val;
            }
            int range = (value_max >= value_min) ? (value_max - value_min + 1) : 0;
            double density = (range > 0 && lit_count > 0) ? (double)lit_count / (double)range : 0.0;
            int use_switch = (density > 0.7 && lit_count > 0);

            if (use_switch) {
                int id = codegen_match_id++;
                fprintf(out, "({ int _su_m%d = (", id);
                if (codegen_expr(me, out) != 0) return -1;
                fprintf(out, "); int _su_r; switch (_su_m%d) { ", id);
                for (int i = 0; i < num_arms; i++) {
                    if (arms[i].is_wildcard) {
                        fprintf(out, "default: _su_r = (");
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        fprintf(out, "); break; ");
                        break;
                    }
                    fprintf(out, "case %d: _su_r = (", arms[i].lit_val);
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                    fprintf(out, "); break; ");
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, "default: _su_r = 0; break; ");
                fprintf(out, "} _su_r; })");
            } else {
                fprintf(out, "(");
                for (int i = 0; i < num_arms; i++) {
                    if (i) fprintf(out, " : ");
                    if (arms[i].is_wildcard) {
                        if (codegen_expr(arms[i].result, out) != 0) return -1;
                        break;
                    }
                    fprintf(out, "(");
                    if (codegen_expr(me, out) != 0) return -1;
                    fprintf(out, ") == %d ? ", arms[i].lit_val);
                    if (codegen_expr(arms[i].result, out) != 0) return -1;
                }
                if (num_arms && !arms[num_arms - 1].is_wildcard)
                    fprintf(out, " : 0");
                fprintf(out, ")");
            }
            return 0;
        }
        default:
            return -1;
    }
}

/** 前向声明：codegen_block_body 与 codegen_run_defers 互相依赖 */
static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out);

/**
 * 按逆序生成执行本块所有 defer 块的 C 代码（块退出时执行）。
 * 参数：out 输出流；b 当前块（含 defer_blocks）；indent 缩进（2 或 4）。
 */
static int codegen_run_defers(FILE *out, const struct ASTBlock *b, int indent) {
    if (!b || !out || !b->defer_blocks) return 0;
    for (int i = b->num_defers - 1; i >= 0; i--) {
        if (codegen_block_body(b->defer_blocks[i], indent, out) != 0) return -1;
    }
    return 0;
}

/**
 * 将块体生成到 out：const/let 声明（带 indent 空格缩进），再 labeled_stmts（label/goto/return）、run_defers，再 final_expr。
 * 若 final_expr 为 break/continue/return/panic 则生成对应语句，否则 (void)(final_expr);。
 * 用于 main 块或 while 体；indent 为每行前空格数（如 2 或 4）。
 */
static int codegen_block_body(const struct ASTBlock *b, int indent, FILE *out) {
    if (!b || !out) return -1;
    const char *pad = (indent == 2) ? "  " : (indent == 4) ? "    " : "      ";
    for (int i = 0; i < b->num_consts; i++) {
        const struct ASTType *ty = b->const_decls[i].type;
        const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
        if (ty && ty->kind == AST_TYPE_NAMED && ty->name)
            fprintf(out, "%sconst struct %s %s = ", pad, ty->name, name);
        else if (ty && ty->kind == AST_TYPE_ARRAY && ty->elem_type) {
            const char *cty = c_type_str(ty->elem_type);
            fprintf(out, "%sconst %s %s[%d] = ", pad, cty, name, ty->array_size);
        } else if (ty && ty->kind == AST_TYPE_SLICE && ty->elem_type) {
            ensure_slice_struct(ty, out);
            fprintf(out, "%sconst %s %s = ", pad, c_type_str(ty), name);
        } else {
            const char *cty = ty ? c_type_str(ty) : "int32_t";
            fprintf(out, "%sconst %s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, b->const_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_lets; i++) {
        const struct ASTType *ty = b->let_decls[i].type;
        const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
        if (ty && ty->kind == AST_TYPE_NAMED && ty->name)
            fprintf(out, "%sstruct %s %s = ", pad, ty->name, name);
        else if (ty && ty->kind == AST_TYPE_ARRAY && ty->elem_type) {
            const char *cty = c_type_str(ty->elem_type);
            fprintf(out, "%s%s %s[%d] = ", pad, cty, name, ty->array_size);
        } else if (ty && ty->kind == AST_TYPE_SLICE && ty->elem_type) {
            ensure_slice_struct(ty, out);
            fprintf(out, "%s%s %s = ", pad, c_type_str(ty), name);
        } else {
            const char *cty = ty ? c_type_str(ty) : "int32_t";
            fprintf(out, "%s%s %s = ", pad, cty, name);
        }
        if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label)
            fprintf(out, "%s%s:\n", pad, b->labeled_stmts[i].label);
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
            if (codegen_run_defers(out, b, indent) != 0) return -1;
            fprintf(out, "%sgoto %s;\n", pad, b->labeled_stmts[i].u.goto_target);
        } else {
            if (codegen_run_defers(out, b, indent) != 0) return -1;
            fprintf(out, "%sreturn ", pad);
            if (codegen_expr(b->labeled_stmts[i].u.return_expr, out) != 0) return -1;
            fprintf(out, ";\n");
        }
    }
    if (codegen_run_defers(out, b, indent) != 0) return -1;
    if (!b->final_expr) return 0;  /* 块以 return/goto 结尾，无需 final_expr */
    if (b->final_expr->kind == AST_EXPR_BREAK) {
        fprintf(out, "%sbreak;\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_CONTINUE) {
        fprintf(out, "%scontinue;\n", pad);
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_RETURN) {
        fprintf(out, "%sreturn ", pad);
        if (codegen_expr(b->final_expr->value.unary.operand, out) != 0) return -1;
        fprintf(out, ";\n");
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "%s", pad);
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        return 0;
    }
    fprintf(out, "%s(void)(", pad);
    if (codegen_expr(b->final_expr, out) != 0) return -1;
    fprintf(out, ");\n");
    return 0;
}

/**
 * 将入口模块生成 C；功能、参数、返回值见 codegen.h 声明处注释。
 * body 为块：先生成 const/let 声明，再各 while 循环，最后 return final_expr。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out) {
    if (!m || !out) return -1;
    if (!m->main_func || !m->main_func->body) return -1;

    if (strcmp(m->main_func->name, "main") != 0) return -1;

    const struct ASTBlock *b = m->main_func->body;
    codegen_slice_emitted_n = 0;
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include <stdlib.h>\n");
    fprintf(out, "#include <stdint.h>\n");
    fprintf(out, "#include <stddef.h>\n");
    /* 顶层结构体定义 → C struct（变量类型与类型系统设计 §6.1） */
    for (int i = 0; i < m->num_structs && m->struct_defs; i++) {
        const struct ASTStructDef *sd = m->struct_defs[i];
        if (!sd || !sd->name) continue;
        fprintf(out, "struct %s { ", sd->name);
        for (int j = 0; j < sd->num_fields; j++) {
            const struct ASTType *fty = sd->fields[j].type;
            const char *fname = sd->fields[j].name ? sd->fields[j].name : "";
            if (fty && fty->kind == AST_TYPE_ARRAY && fty->elem_type)
                fprintf(out, "%s %s[%d]; ", c_type_str(fty->elem_type), fname, fty->array_size);
            else {
                const char *cty = fty ? c_type_str(fty) : "int32_t";
                fprintf(out, "%s %s; ", cty, fname);
            }
        }
        fprintf(out, "};\n");
    }
    /* 冷路径辅助：panic 分支标记 noreturn+cold，利于 ICache 与分支预测（控制流清单 §8.3） */
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));\n");
    fprintf(out, "static void shulang_panic_(int has_msg, int msg_val) {\n");
    fprintf(out, "  if (has_msg) (void)fprintf(stderr, \"%%d\\n\", msg_val);\n");
    fprintf(out, "  abort();\n");
    fprintf(out, "}\n");
    /* 为本块中使用的切片类型生成 struct shulang_slice_<elem> 定义（§6.3） */
    for (int i = 0; i < b->num_consts; i++)
        if (b->const_decls[i].type && b->const_decls[i].type->kind == AST_TYPE_SLICE)
            ensure_slice_struct(b->const_decls[i].type, out);
    for (int i = 0; i < b->num_lets; i++)
        if (b->let_decls[i].type && b->let_decls[i].type->kind == AST_TYPE_SLICE)
            ensure_slice_struct(b->let_decls[i].type, out);
    fprintf(out, "int main(void) {\n");
    fprintf(out, "  printf(\"Hello World\\n\");\n");
    for (int i = 0; i < b->num_consts; i++) {
        const struct ASTType *ty = b->const_decls[i].type;
        const char *name = b->const_decls[i].name ? b->const_decls[i].name : "";
        if (ty && ty->kind == AST_TYPE_NAMED && ty->name)
            fprintf(out, "  const struct %s %s = ", ty->name, name);
        else if (ty && ty->kind == AST_TYPE_ARRAY && ty->elem_type)
            fprintf(out, "  const %s %s[%d] = ", c_type_str(ty->elem_type), name, ty->array_size);
        else if (ty && ty->kind == AST_TYPE_SLICE && ty->elem_type) {
            ensure_slice_struct(ty, out);
            fprintf(out, "  const %s %s = ", c_type_str(ty), name);
        } else {
            const char *cty = ty ? c_type_str(ty) : "int32_t";
            fprintf(out, "  const %s %s = ", cty, name);
        }
        if (codegen_init(ty, b->const_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_lets; i++) {
        const struct ASTType *ty = b->let_decls[i].type;
        const char *name = b->let_decls[i].name ? b->let_decls[i].name : "";
        if (ty && ty->kind == AST_TYPE_NAMED && ty->name)
            fprintf(out, "  struct %s %s = ", ty->name, name);
        else if (ty && ty->kind == AST_TYPE_ARRAY && ty->elem_type)
            fprintf(out, "  %s %s[%d] = ", c_type_str(ty->elem_type), name, ty->array_size);
        else if (ty && ty->kind == AST_TYPE_SLICE && ty->elem_type) {
            ensure_slice_struct(ty, out);
            fprintf(out, "  %s %s = ", c_type_str(ty), name);
        } else {
            const char *cty = ty ? c_type_str(ty) : "int32_t";
            fprintf(out, "  %s %s = ", cty, name);
        }
        if (codegen_init(ty, b->let_decls[i].init, out, b) != 0) return -1;
        fprintf(out, ";\n");
    }
    for (int i = 0; i < b->num_loops; i++) {
        fprintf(out, "  while (");
        if (codegen_expr(b->loops[i].cond, out) != 0) return -1;
        fprintf(out, ") {\n");
        if (codegen_block_body(b->loops[i].body, 4, out) != 0) return -1;
        fprintf(out, "  }\n");
    }
    for (int i = 0; i < b->num_for_loops; i++) {
        fprintf(out, "  for (");
        if (b->for_loops[i].init) {
            if (codegen_expr(b->for_loops[i].init, out) != 0) return -1;
        }
        fprintf(out, "; ");
        if (b->for_loops[i].cond) {
            if (codegen_expr(b->for_loops[i].cond, out) != 0) return -1;
        } else {
            fprintf(out, "1");  /* cond 空表示恒真 */
        }
        fprintf(out, "; ");
        if (b->for_loops[i].step) {
            if (codegen_expr(b->for_loops[i].step, out) != 0) return -1;
        }
        fprintf(out, ") {\n");
        if (codegen_block_body(b->for_loops[i].body, 4, out) != 0) return -1;
        fprintf(out, "  }\n");
    }
    for (int i = 0; i < b->num_labeled_stmts; i++) {
        if (b->labeled_stmts[i].label)
            fprintf(out, "  %s:\n", b->labeled_stmts[i].label);
        if (b->labeled_stmts[i].kind == AST_STMT_GOTO) {
            if (codegen_run_defers(out, b, 2) != 0) return -1;
            fprintf(out, "  goto %s;\n", b->labeled_stmts[i].u.goto_target);
        } else {
            if (codegen_run_defers(out, b, 2) != 0) return -1;
            fprintf(out, "  return ");
            if (codegen_expr(b->labeled_stmts[i].u.return_expr, out) != 0) return -1;
            fprintf(out, ";\n");
        }
    }
    if (codegen_run_defers(out, b, 2) != 0) return -1;
    if (!b->final_expr) {
        /* 块以 return/goto 结尾，labeled_stmts 已输出，无需 final_expr */
        fprintf(out, "}\n");
        return 0;
    }
    if (b->final_expr->kind == AST_EXPR_PANIC) {
        fprintf(out, "  ");
        if (codegen_expr(b->final_expr, out) != 0) return -1;
        fprintf(out, ";\n");
        fprintf(out, "  return 0;\n");
    } else {
        fprintf(out, "  return ");
        if (b->final_expr->kind == AST_EXPR_RETURN) {
            if (codegen_expr(b->final_expr->value.unary.operand, out) != 0) return -1;
        } else {
            if (codegen_expr(b->final_expr, out) != 0) return -1;
        }
        fprintf(out, ";\n");
    }
    fprintf(out, "}\n");
    return 0;
}

/**
 * 将库模块生成占位 C；功能、参数、返回值见 codegen.h 声明处注释。
 */
int codegen_library_module_to_c(struct ASTModule *m, const char *import_path, FILE *out) {
    (void)m;
    if (!out) return -1;
    /* 占位：避免空翻译单元警告；多文件链接时每个 import 对应一个 .c */
    fprintf(out, "/* generated from %s */\n", import_path ? import_path : "");
    return 0;
}
