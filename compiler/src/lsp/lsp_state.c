/**
 * lsp_state.c — LSP read_message 的 state 缓冲区，单独编译单元避免被同单元内大数组/栈覆盖。
 * 供 lsp_gen.c 通过 extern 使用（生成代码里 state_buf 被 sed 替换为 g_lsp_state_buf）。
 */
#include <stdint.h>

uint8_t g_lsp_state_buf[16388];
