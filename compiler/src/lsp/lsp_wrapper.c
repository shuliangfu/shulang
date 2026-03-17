/**
 * lsp_wrapper.c — LSP 入口包装
 *
 * driver_gen.c 期望符号 lsp_lsp_main，而 lsp.su -E 生成的 lsp_gen.c 可能以 typeck_ 为前缀导出。
 * 本文件提供 lsp_lsp_main 转调 typeck_lsp_main，保证链接通过。
 */
extern int typeck_lsp_main(void);

int lsp_lsp_main(void) {
    return typeck_lsp_main();
}
