/**
 * lsp_diag.h — LSP 诊断收集器接口
 *
 * 供 parser/typeck 在 LSP 模式下将错误写入收集器而非 stderr；
 * LSP 层调用 lsp_diagnostics_collect 对当前文档跑解析并取 Diagnostic[] JSON。
 */

#ifndef SHU_LSP_DIAG_H
#define SHU_LSP_DIAG_H

#include <stdint.h>

/** 非零时 parser/typeck 应调用 lsp_diag_add 而非写 stderr（由 lsp_diagnostics_collect 置 1，结束后置 0）。 */
extern int lsp_diag_enabled;

/** 清空当前收集的诊断条数。 */
void lsp_diag_clear(void);

/** 文档变更时由 lsp_io 调用，使模块与诊断缓存失效，避免旧模块指向已释放的文档缓冲。 */
void lsp_diag_invalidate_cache(void);

/** 追加一条诊断：line/col 为 1-based；severity 1=Error 2=Warning；msg 以 NUL 结尾。 */
void lsp_diag_add(int line, int col, int severity, const char *msg);

/** typeck 统一报错入口：line/col 为 1-based；LSP 模式下写入收集器，否则 fprintf stderr + " at line:col\n"。 */
void lsp_diag_report_typeck(int line, int col, const char *fmt, ...);

/**
 * 对 source[0..source_len-1] 跑 C parser，收集诊断，并构建完整 JSON-RPC 响应正文：
 * {"jsonrpc":"2.0","id":<id_val>,"result":<Diagnostic[] 的 JSON>}。
 * 写入 out_buf，返回长度，失败或越界返回 -1。
 * 高性能：仅在此处跑一次解析，不在 didChange 时跑。
 */
int lsp_build_diagnostics_response(int id_val, const uint8_t *source, int source_len,
                                   uint8_t *out_buf, int out_cap);

/**
 * 在 source 上按 (line_0, col_0)（LSP 0-based）查“定义”；找到则 out_line/out_col 为 1-based 定义位置，返回 1，否则返回 0。
 */
int lsp_definition_at(const uint8_t *source, int source_len, int line_0, int col_0, int *out_line, int *out_col);

/**
 * 在 source 上按 (line_0, col_0) 确定目标函数，收集其所有引用位置（1-based），写入 out_lines/out_cols，返回个数，最多 max_refs。
 */
int lsp_references_at(const uint8_t *source, int source_len, int line_0, int col_0,
                      int *out_lines, int *out_cols, int max_refs);

/**
 * 在 source 上按 (line_0, col_0) 找表达式类型，格式化为字符串写入 out_buf，返回长度；无类型返回 0。
 */
int lsp_hover_at(const uint8_t *source, int source_len, int line_0, int col_0, char *out_buf, int out_cap);

#endif /* SHU_LSP_DIAG_H */
