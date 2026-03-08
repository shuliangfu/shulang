/**
 * main.c — Shulang 编译器入口（Driver）
 *
 * 文件职责：解析命令行（-L、-target、-o、输入文件），串联 lexer→parser→typeck→codegen，并调用系统 cc 生成可执行文件；无 -o 时打印 Token 与 parse/typeck 结果供测试。
 * 所属模块：编译器 driver，compiler/src/；作为 shuc 可执行文件的主入口，依赖 lexer、parser、typeck、codegen、ast。
 * 与其它文件的关系：调用 lexer_new/lexer_next/lexer_free、parse、typeck_module、codegen_module_to_c/codegen_library_module_to_c、ast_module_free；通过 read_file 读入 .su，通过 invoke_cc 调用外部 cc。
 * 重要约定：源码缓冲区在整条链路中由 main 持有并 free；import 的模块在 resolve_imports 与 -o 分支中会重复解析（先 typeck 再 codegen 时再解析），临时 .c 文件均在 /tmp 下创建并在调用 cc 后 unlink。多文件时 C 文件数不超过 MAX_C_FILES。
 */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "typeck/typeck.h"
#include "codegen/codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * 读入整个文件为 NUL 结尾的堆分配字符串。
 * 功能说明：用于读入 .su 源码或 import 的模块文件，供 Lexer/Parser 使用。
 * 参数：path 文件系统路径，只读；须可访问且为普通文件。
 * 返回值：成功返回 malloc 的缓冲区（含结尾 NUL），调用方须 free；失败（无法打开、seek/read 错误）返回 NULL。
 * 错误与边界：空文件返回非 NULL 且 buf[0]='\0'；path 为 NULL 或不可打开时返回 NULL。
 * 副作用与约定：分配内存，无静态状态；不修改 path。
 */
static char *read_file(const char *path);

/**
 * 将 import 路径字符串转为库根下的 .su 文件路径。
 * 功能说明：例如 "core.types" 在 lib_root 为 "." 时得到 "./core/types.su"，供 read_file 打开。
 * 参数：lib_root 标准库根目录，若为 NULL 或空则视为 "."；import_path 如 "core.types"；path 输出缓冲区；path_size 缓冲区字节数，建议至少 512。
 * 返回值：无；结果写入 path，保证 NUL 结尾（若 path_size>0）。
 * 错误与边界：path_size 过小可能导致截断；import_path 中的 '.' 均替换为 '/'。
 * 副作用与约定：仅写 path，不分配内存；不修改 lib_root、import_path。
 */
static void import_path_to_file_path(const char *lib_root, const char *import_path, char *path, size_t path_size) {
    const char *r = lib_root && lib_root[0] ? lib_root : ".";
    size_t off = (size_t)snprintf(path, path_size, "%s/", r);
    for (const char *s = import_path; *s && off + 1 < path_size; s++) {
        if (*s == '.')
            path[off++] = '/';
        else
            path[off++] = *s;
    }
    if (off + 4 <= path_size)
        snprintf(path + off, path_size - off, ".su");
}

/**
 * 解析并类型检查模块的所有 import 依赖。
 * 功能说明：按 mod->import_paths 依次解析对应 .su 文件并执行 typeck，确保依赖模块存在且合法；不保留依赖 AST，仅做存在性与类型检查。
 * 参数：mod 已解析的入口模块，其 import_paths 与 num_imports 已填充；lib_root 标准库根目录，用于 import_path_to_file_path。
 * 返回值：0 表示全部 import 解析与 typeck 通过；-1 表示某 import 打开失败、解析失败或 typeck 失败，且已向 stderr 输出信息。
 * 错误与边界：mod 为 NULL 或 num_imports 为 0 时直接返回 0；任一依赖失败即返回 -1，不继续后续 import。
 * 副作用与约定：每个依赖会临时分配 Lexer 与 AST 并在本函数内 ast_module_free，不修改 mod；会向 stderr 打印错误信息。
 */
static int resolve_imports(ASTModule *mod, const char *lib_root) {
    char path[512];
    for (int i = 0; i < mod->num_imports; i++) {
        import_path_to_file_path(lib_root, mod->import_paths[i], path, sizeof(path));
        char *src = read_file(path);
        if (!src) {
            fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", mod->import_paths[i], path);
            return -1;
        }
        Lexer *lex = lexer_new(src);
        ASTModule *dep = NULL;
        int pr = parse(lex, &dep);
        lexer_free(lex);
        free(src);
        if (pr != 0 || !dep) {
            fprintf(stderr, "shuc: failed to parse import '%s'\n", mod->import_paths[i]);
            return -1;
        }
        if (typeck_module(dep) != 0) {
            fprintf(stderr, "shuc: typeck failed for import '%s'\n", mod->import_paths[i]);
            ast_module_free(dep);
            return -1;
        }
        ast_module_free(dep);
    }
    return 0;
}

/**
 * 将 Token 类型枚举转为可读字符串，用于控制台打印。
 * 功能说明：供无 -o 时打印 Token 序列使用，返回如 "FN"、"IDENT"、"INT" 等。
 * 参数：k 当前 Token 的 kind。
 * 返回值：指向静态字符串的指针，只读；未知 kind 返回 "?"。
 * 错误与边界：无；不分配内存。
 * 副作用与约定：无副作用；返回值不得被 free。
 */
static const char *token_kind_str(TokenKind k) {
    switch (k) {
        case TOKEN_EOF:     return "EOF";
        case TOKEN_FUNCTION: return "FUNCTION";
        case TOKEN_LET:     return "LET";
        case TOKEN_CONST:   return "CONST";
        case TOKEN_IF:      return "IF";
        case TOKEN_ELSE:    return "ELSE";
        case TOKEN_WHILE:   return "WHILE";
        case TOKEN_LOOP:    return "LOOP";
        case TOKEN_FOR:     return "FOR";
        case TOKEN_BREAK:   return "BREAK";
        case TOKEN_CONTINUE: return "CONTINUE";
        case TOKEN_RETURN:   return "RETURN";
        case TOKEN_PANIC:   return "PANIC";
        case TOKEN_DEFER:   return "DEFER";
        case TOKEN_MATCH:   return "MATCH";
        case TOKEN_STRUCT:  return "STRUCT";
        case TOKEN_GOTO:    return "GOTO";
        case TOKEN_UNDERSCORE: return "UNDERSCORE";
        case TOKEN_IDENT:   return "IDENT";
        case TOKEN_I32:     return "I32";
        case TOKEN_BOOL:    return "BOOL";
        case TOKEN_U8:      return "U8";
        case TOKEN_U32:     return "U32";
        case TOKEN_U64:     return "U64";
        case TOKEN_I64:     return "I64";
        case TOKEN_USIZE:   return "USIZE";
        case TOKEN_ISIZE:   return "ISIZE";
        case TOKEN_TRUE:    return "TRUE";
        case TOKEN_FALSE:   return "FALSE";
        case TOKEN_INT:     return "INT";
        case TOKEN_LPAREN:  return "LPAREN";
        case TOKEN_RPAREN:  return "RPAREN";
        case TOKEN_LBRACE:  return "LBRACE";
        case TOKEN_RBRACE:  return "RBRACE";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_ARROW:   return "ARROW";
        case TOKEN_FATARROW: return "FATARROW";
        case TOKEN_COMMA:   return "COMMA";
        case TOKEN_COLON:   return "COLON";
        case TOKEN_IMPORT:  return "IMPORT";
        case TOKEN_DOT:     return "DOT";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_PLUS:   return "PLUS";
        case TOKEN_MINUS:  return "MINUS";
        case TOKEN_STAR:   return "STAR";
        case TOKEN_SLASH:  return "SLASH";
        case TOKEN_PERCENT: return "PERCENT";
        case TOKEN_AMP:    return "AMP";
        case TOKEN_PIPE:   return "PIPE";
        case TOKEN_CARET:  return "CARET";
        case TOKEN_LSHIFT: return "LSHIFT";
        case TOKEN_RSHIFT: return "RSHIFT";
        case TOKEN_TILDE:  return "TILDE";
        case TOKEN_EQ:     return "EQ";
        case TOKEN_NE:     return "NE";
        case TOKEN_LT:     return "LT";
        case TOKEN_GT:     return "GT";
        case TOKEN_LE:     return "LE";
        case TOKEN_GE:     return "GE";
        case TOKEN_AMPAMP: return "AMPAMP";
        case TOKEN_PIPEPIPE: return "PIPEPIPE";
        case TOKEN_BANG:   return "BANG";
        case TOKEN_ASSIGN: return "ASSIGN";
        default:            return "?";
    }
}

/* read_file 实现：见上方声明处注释 */
static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long size = ftell(f);
    if (size < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)size, f);
    fclose(f);
    if (n != (size_t)size) { free(buf); return NULL; }
    buf[n] = '\0';
    return buf;
}

/** 多文件编译时 C 文件数量上限（入口 + import 闭包） */
#define MAX_C_FILES 33

/**
 * 调用系统 cc 将多个 C 文件编译链接为可执行文件。
 * 功能说明：阶段 7.3 多文件；fork 子进程 execvp("cc", ...)，将 c_paths 中所有 .c 与 -o out_path、可选 -target 一并传入 cc。
 * 参数：c_paths 生成的 .c 文件路径数组，元素不可为 NULL；n 文件个数，至少 1，且 n 与 c_paths 实际数量一致；out_path 输出可执行文件路径；target 可选目标三元组（如 x86_64-apple-darwin），NULL 或空表示本机。
 * 返回值：0 表示 cc 执行成功且退出码为 0；-1 表示参数非法、fork/exec 失败或 cc 非零退出，且已向 stderr 输出信息。
 * 错误与边界：c_paths 为 NULL 或 n<1 时直接返回 -1；子进程内 execvp 失败会 _exit(127)。
 * 副作用与约定：阻塞等待子进程结束；不修改 c_paths、out_path、target；依赖 PATH 中的 cc（通常为 clang/gcc）。
 */
static int invoke_cc(const char **c_paths, int n, const char *out_path, const char *target) {
    if (!c_paths || n < 1) return -1;
    pid_t pid = fork();
    if (pid < 0) {
        perror("shuc: fork");
        return -1;
    }
    if (pid == 0) {
        char *argv[MAX_C_FILES + 8];
        int i = 0;
        argv[i++] = (char *)"cc";
        if (target && target[0]) {
            argv[i++] = (char *)"-target";
            argv[i++] = (char *)target;
        }
        argv[i++] = (char *)"-o";
        argv[i++] = (char *)out_path;
        for (int j = 0; j < n && i < MAX_C_FILES + 6; j++)
            argv[i++] = (char *)c_paths[j];
        argv[i++] = NULL;
        execvp("cc", argv);
        perror("shuc: cc");
        _exit(127);
    }
    int status;
    if (waitpid(pid, &status, 0) != pid) {
        perror("shuc: waitpid");
        return -1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "shuc: cc failed (exit %d)\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
        return -1;
    }
    return 0;
}

/**
 * 编译器主入口：解析命令行，执行 lexer→parser→typeck，可选 codegen→cc 产出可执行文件。
 * 功能说明：支持 -L、-target、-o；无 -o 时打印 Token 与 parse/typeck OK（供测试）；有 -o 时生成 C（含 import 占位）、调用 cc 链接。
 * 参数：argc、argv 为标准 C 程序参数；argv[0] 为程序名，后续为可选 -L/-target/-o 及其参数与一个输入 .su 路径。
 * 返回值：0 表示成功（含无参数时打印用法）；1 表示读文件失败、解析/typeck 失败、codegen 或 cc 失败。
 * 错误与边界：无输入文件时打印用法并返回 0；-o 指定但无 main 时返回 1；import 数量超过 32 时仅处理前 32 个。
 * 副作用与约定：可能创建/删除 /tmp 下临时文件；依赖 getenv("SHULANG_LIB")；多文件时可能多次解析同一 import 的 .su。
 */
int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *out_path = NULL;
    const char *lib_root = NULL;
    const char *target = NULL;
    int emit_c_only = 0;  /* -E：仅生成 C 到 stdout，不调用 cc */

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-E") == 0) {
            emit_c_only = 1;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            out_path = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            lib_root = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-target") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
                return 1;
            }
            target = argv[i + 1];
            i++;
        } else if (!input_path) {
            input_path = argv[i];
        }
    }
    if (!lib_root) lib_root = getenv("SHULANG_LIB");
    if (!lib_root) lib_root = ".";

    if (!input_path) {
        fprintf(stderr, "Usage: %s [ -L <lib> ] [ -target <triple> ] <file.su> [ -o <out> ]\n", argv[0] ? argv[0] : "shuc");
        return 0;
    }

    char *src = read_file(input_path);
    if (!src) {
        fprintf(stderr, "Error: cannot read file '%s'\n", input_path);
        return 1;
    }

    Lexer *lex = lexer_new(src);
    ASTModule *mod = NULL;
    int pr = parse(lex, &mod);
    lexer_free(lex);

    if (pr != 0 || !mod) {
        if (mod) ast_module_free(mod);
        free(src);
        return 1;
    }
    if (mod->num_imports > 0 && resolve_imports(mod, lib_root) != 0) {
        ast_module_free(mod);
        free(src);
        return 1;
    }
    if (typeck_module(mod) != 0) {
        ast_module_free(mod);
        free(src);
        return 1;
    }

    /* -E：仅将入口模块生成 C 到 stdout 后退出（便于调试） */
    if (emit_c_only) {
        if (!mod->main_func || !mod->main_func->body) {
            fprintf(stderr, "shuc: no main function (cannot emit C)\n");
            ast_module_free(mod);
            free(src);
            return 1;
        }
        int ec = codegen_module_to_c(mod, stdout);
        ast_module_free(mod);
        free(src);
        return ec != 0 ? 1 : 0;
    }

    /* 若指定 -o：需有 main，生成 C（含 import 闭包占位 .c）→ 调用 cc 链接 → 产出可执行文件；阶段 7.3 多文件 */
    if (out_path) {
        if (!mod->main_func || !mod->main_func->body) {
            fprintf(stderr, "shuc: no main function (cannot emit executable)\n");
            ast_module_free(mod);
            free(src);
            return 1;
        }
        const char *c_paths[MAX_C_FILES];
        int n_c = 0;
        char tmp_c[256];
        char dep_c_paths[32][256];
        int ndep = 0;

        /* 入口模块 → 临时 .c */
        char tmp[] = "/tmp/shuc_XXXXXX";
        int fd = mkstemp(tmp);
        if (fd < 0) {
            perror("shuc: mkstemp");
            ast_module_free(mod);
            free(src);
            return 1;
        }
        FILE *cf = fdopen(fd, "w");
        if (!cf) {
            close(fd);
            unlink(tmp);
            ast_module_free(mod);
            free(src);
            return 1;
        }
        if (codegen_module_to_c(mod, cf) != 0) {
            fclose(cf);
            unlink(tmp);
            ast_module_free(mod);
            free(src);
            return 1;
        }
        fclose(cf);
        snprintf(tmp_c, sizeof(tmp_c), "%s.c", tmp);
        if (rename(tmp, tmp_c) != 0) {
            perror("shuc: rename");
            unlink(tmp);
            ast_module_free(mod);
            free(src);
            return 1;
        }
        c_paths[n_c++] = tmp_c;

        /* 每个 import 生成占位 .c，参与链接 */
        for (int i = 0; i < mod->num_imports && ndep < 32; i++) {
            char path[512];
            import_path_to_file_path(lib_root, mod->import_paths[i], path, sizeof(path));
            char *dep_src = read_file(path);
            if (!dep_src) {
                fprintf(stderr, "shuc: cannot open import '%s' (tried %s)\n", mod->import_paths[i], path);
                while (ndep--) unlink(dep_c_paths[ndep]);
                unlink(tmp_c);
                ast_module_free(mod);
                free(src);
                return 1;
            }
            Lexer *dlex = lexer_new(dep_src);
            ASTModule *dep = NULL;
            int dpr = parse(dlex, &dep);
            lexer_free(dlex);
            free(dep_src);
            if (dpr != 0 || !dep) {
                fprintf(stderr, "shuc: failed to parse import '%s'\n", mod->import_paths[i]);
                while (ndep--) unlink(dep_c_paths[ndep]);
                unlink(tmp_c);
                ast_module_free(mod);
                free(src);
                return 1;
            }
            char tmpd[] = "/tmp/shuc_XXXXXX";
            int fdd = mkstemp(tmpd);
            if (fdd < 0) {
                ast_module_free(dep);
                while (ndep--) unlink(dep_c_paths[ndep]);
                unlink(tmp_c);
                ast_module_free(mod);
                free(src);
                return 1;
            }
            FILE *dcf = fdopen(fdd, "w");
            if (!dcf || codegen_library_module_to_c(dep, mod->import_paths[i], dcf) != 0) {
                if (dcf) fclose(dcf);
                else close(fdd);
                unlink(tmpd);
                ast_module_free(dep);
                while (ndep--) unlink(dep_c_paths[ndep]);
                unlink(tmp_c);
                ast_module_free(mod);
                free(src);
                return 1;
            }
            fclose(dcf);
            snprintf(dep_c_paths[ndep], sizeof(dep_c_paths[0]), "%s.c", tmpd);
            if (rename(tmpd, dep_c_paths[ndep]) != 0) {
                unlink(tmpd);
                ast_module_free(dep);
                while (ndep--) unlink(dep_c_paths[ndep]);
                unlink(tmp_c);
                ast_module_free(mod);
                free(src);
                return 1;
            }
            c_paths[n_c++] = dep_c_paths[ndep];
            ndep++;
            ast_module_free(dep);
        }

        int cc_ok = invoke_cc(c_paths, n_c, out_path, target);
        while (ndep--) unlink(dep_c_paths[ndep]);
        unlink(tmp_c);
        ast_module_free(mod);
        free(src);
        return cc_ok == 0 ? 0 : 1;
    }

    /* 无 -o：保留原有行为：打印 Token，再解析并打印 parse/typeck OK（供测试） */
    Lexer *lex2 = lexer_new(src);
    Token tok;
    for (;;) {
        lexer_next(lex2, &tok);
        if (tok.kind == TOKEN_EOF) {
            printf("%s\n", token_kind_str(tok.kind));
            break;
        }
        printf("%s", token_kind_str(tok.kind));
        if (tok.kind == TOKEN_INT)
            printf(" %d", tok.value.int_val);
        else if ((tok.kind == TOKEN_IDENT || tok.kind == TOKEN_I32 || tok.kind == TOKEN_BOOL
                  || tok.kind == TOKEN_U8 || tok.kind == TOKEN_U32 || tok.kind == TOKEN_U64
                  || tok.kind == TOKEN_I64 || tok.kind == TOKEN_USIZE || tok.kind == TOKEN_ISIZE)
                 && tok.value.ident && tok.ident_len > 0)
            printf(" %.*s", tok.ident_len, tok.value.ident);
        printf(" @%d:%d\n", tok.line, tok.col);
    }
    lexer_free(lex2);

    if (mod->main_func && mod->main_func->body) {
        const struct ASTBlock *blk = mod->main_func->body;
        const struct ASTExpr *e = blk->final_expr;
        if (e && e->kind == AST_EXPR_LIT)
            printf("parse OK: %s() -> i32 { %d }\n",
                   mod->main_func->name,
                   e->value.int_val);
        else
            printf("parse OK: %s() -> i32 { expr }\n",
                   mod->main_func->name);
    } else
        printf("parse OK (library module)\n");
    printf("typeck OK\n");
    ast_module_free(mod);
    free(src);
    return 0;
}
