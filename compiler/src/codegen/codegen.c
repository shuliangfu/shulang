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
        case AST_EXPR_ADD:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " + ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        case AST_EXPR_SUB:
            if (codegen_expr(e->value.binop.left, out) != 0) return -1;
            fprintf(out, " - ");
            if (codegen_expr(e->value.binop.right, out) != 0) return -1;
            return 0;
        default:
            return -1;
    }
}

/**
 * 将入口模块生成 C；功能、参数、返回值见 codegen.h 声明处注释。
 * 使用 main_func->body 表达式生成 return 语句（整数字面量或加减表达式），使退出码与 .su 语义一致。
 */
int codegen_module_to_c(struct ASTModule *m, FILE *out) {
    if (!m || !out) return -1;
    if (!m->main_func || !m->main_func->body) return -1;

    /* 仅支持 main；return 使用 body 的 C 表达式 */
    if (strcmp(m->main_func->name, "main") != 0) return -1;

    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "int main(void) {\n");
    fprintf(out, "  printf(\"Hello World\\n\");\n");
    fprintf(out, "  return ");
    if (codegen_expr(m->main_func->body, out) != 0) return -1;
    fprintf(out, ";\n");
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
