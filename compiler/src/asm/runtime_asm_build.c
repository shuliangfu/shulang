/**
 * runtime_asm_build.c — Goal 2 用 asm 后端构建 shuc 时的最小 C 桩
 *
 * 仅提供 main()，转调 main.su 编译为 asm/.o 后的入口符号 entry。
 * 与 main.c 等价：main.c 调 main_entry（来自 -E 展开的 driver_gen.c），
 * 本文件在「全 .su 用 asm 产出 .o」时调 entry（main.su 的 function entry）。
 *
 * 链接时需：本 .o + main.su 的 .o（含 entry）+ 其它 .su 的 .o + runtime_driver.o（或提供 run_compiler_c_impl 等）+ -lc。
 */
extern int entry(int argc, char **argv);

int main(int argc, char **argv) {
    return entry(argc, argv);
}
