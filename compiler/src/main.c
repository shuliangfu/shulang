/**
 * main.c — 6.4 极简入口：仅调 main.su 的 main_entry，驱动逻辑在 runtime.c
 *
 * 程序入口为 main()；实际驱动由 main_entry 实现（main.su 提供，或 runtime.c 的弱符号桩转调 run_compiler_c）。
 * 构建/文档标明：入口逻辑在 main.su，C 侧运行时在 runtime.c。
 */
#include <stdlib.h>

extern int main_entry(int argc, char **argv);

int main(int argc, char **argv) {
    return main_entry(argc, argv);
}
