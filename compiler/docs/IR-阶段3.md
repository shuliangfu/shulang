# 阶段 3 IR 形态说明

阶段 3–4 采用**由带类型 AST 直接生成 C** 的路线，IR 极简。

## 当前约定（阶段 3）

- **IR 形态**：暂不引入独立 IR 数据结构；类型检查（Typeck）直接对 AST 做校验，Codegen 阶段由 **AST → C 源码** 一步到位。
- **后续**：若引入优化或多后端，再在 `compiler/src/ir/` 定义 SSA 或线性 IR，由 Typeck 产出 IR、Codegen 消费 IR。

## 与开发时序的对应

- **阶段 3.1**：本文档确定「直接 AST → C」的形态，`compiler/src/ir/` 仅占位，无必写 IR 代码。
- **阶段 4**：Codegen 读 AST（经 Typeck 校验通过），输出 C 或调用系统 `cc` 生成可执行文件。
