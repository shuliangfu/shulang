/**
 * preprocess.h — .su 条件编译预处理（#if / #else / #endif）
 *
 * 文件职责：声明预处理接口，供 main 在将源码交给 lexer 前按「已定义符号」过滤 #if 块，实现标准库按 OS 选实现。
 * 约定：支持 #if SYMBOL、#elseif SYMBOL、#else、#endif；SYMBOL 为单个标识符（字母数字下划线）；无 #ifdef 或表达式。
 */

#ifndef SHUC_PREPROCESS_H
#define SHUC_PREPROCESS_H

/**
 * 对源码做条件编译预处理，保留「条件成立」分支的代码，被跳过行以空行占位以保持行号一致。
 * 参数：source 为 NUL 结尾的完整源码；defines 为已定义符号数组（如 "OS_LINUX"）；ndefines 为数组长度。
 * 返回值：成功返回 malloc 的字符串（调用方须 free）；ndefines==0 时返回 strdup(source)；失败返回 NULL 并可能写 stderr。
 */
char *preprocess(const char *source, const char **defines, int ndefines);

#endif /* SHUC_PREPROCESS_H */
