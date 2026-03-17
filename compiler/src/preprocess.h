/**
 * preprocess.h — .su 条件编译预处理（#if / #else / #endif）
 *
 * 文件职责：声明预处理接口，供 main 在将源码交给 lexer 前按「已定义符号」过滤 #if 块，实现标准库按 OS 选实现。
 * 约定：支持 #if SYMBOL、#elseif SYMBOL、#else、#endif；SYMBOL 为单个标识符（字母数字下划线）；无 #ifdef 或表达式。
 */

#ifndef SHU_PREPROCESS_H
#define SHU_PREPROCESS_H

#include <stddef.h>

/**
 * 对源码做条件编译预处理，保留「条件成立」分支的代码，被跳过行以空行占位以保持行号一致。
 * 参数：source 为源码指针；source_len 为源码字节数（若为 0 则按 NUL 结尾用 strlen 取长，仅兼容旧调用）；
 *       defines 为已定义符号数组；ndefines 为数组长度；
 *       out_length 若非 NULL，返回输出缓冲区有效字节数（不含结尾 NUL），供 slice 使用。
 * 约定：按 source_len 字节扫描，不依赖 source 内 NUL，避免嵌入 NUL 导致截断（bar→ba、main→mai）。
 * 返回值：成功返回 malloc 的字符串（调用方须 free）；失败返回 NULL 并可能写 stderr。
 */
char *preprocess(const char *source, size_t source_len, const char **defines, int ndefines, size_t *out_length);

/** C 实现：供 runtime.c 在 ndefines>0 或 .su 不可用时调用；6.4 迁 .su 后由 preprocess_su 处理 ndefines==0。 */
char *preprocess_c_fallback(const char *source, size_t source_len, const char **defines, int ndefines, size_t *out_length);

#endif /* SHU_PREPROCESS_H */
