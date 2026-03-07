# 阶段 7：泛型与 Trait 设计

> 本文档定义泛型、trait 的**语法形态**与**实现顺序**，与 `analysis/语法与类型设计-高性能与内存安全.md` 一致：尽量简单、易读、易维护；显式语义、少未定义。

---

## 一、泛型（7.1）

### 1.1 目标

- 支持**泛型函数**与**泛型结构体**；类型检查时做**单态化**（monomorphization），codegen 产出具体类型实例，零成本抽象。
- 不引入高阶类型、不追求类型论复杂；与 C++ 模板单态化思路类似，但语法更简洁。

### 1.2 语法形态（建议）

- **泛型函数**：`fn name<T>(x: T) -> T { x }`，或先支持单参 `fn name<T>(...)`。
- **泛型结构体**：`struct Vec<T> { ... }`，后续可扩展。
- **类型参数**：仅类型形参（无 const 泛型等），满足自举前必须即可。
- **约束**：先无约束或仅「trait 约束」（见下）；无约束时按「可复制/可比较」等最小能力推断，或显式约束后补。

### 1.3 实现顺序

1. **Parser**：识别 `fn ident < ident > ( ... )` 与 `struct ident < ident > { ... }`，在 AST 中增加 `generic_params`（如 `char **names, int count`）。
2. **Typeck**：对调用点做类型推导，确定具体类型后生成单态化实例（或插入实例化请求）。
3. **IR/Codegen**：每个用到的实例生成一份代码（或由后端根据实例集生成），无运行时泛型。

### 1.4 与当前代码的衔接

- `ast.h` 中 `ASTFunc` 预留：`char **generic_param_names; int num_generic_params;`（阶段 7 实现时添加）。
- Lexer 需增加 `<`、`>` 的 Token（如 `TOKEN_LANGLE`、`TOKEN_RANGLE`），注意与比较运算符区分（泛型上下文用尖括号）。

---

## 二、Trait/接口（7.2）

### 2.1 目标

- 支持**接口抽象**（trait）与**实现**（impl），满足「自举前必须」的语法与类型需求；可与泛型结合（如 `fn f<T: Display>(x: T)`）。

### 2.2 语法形态（建议）

- **Trait 定义**：`trait Name { fn method(self) -> i32; }`，仅方法签名。
- **实现**：`impl Name for Type { fn method(self) -> i32 { ... } }`。
- **约束**：泛型参数可带 `T: Trait`；多 trait 用 `+` 连接（可选，后续）。

### 2.3 实现顺序

1. **Parser**：`trait`、`impl`、`for` 关键字与对应 AST 节点（TraitDecl、ImplBlock）。
2. **Typeck**：解析 impl 与 trait 的对应关系；检查方法签名一致；对泛型约束做满足性检查。
3. **Codegen**：单态化后 trait 方法解析为静态分发（直接调具体 impl 的方法），无 vtable 或按需再引入。

### 2.4 与当前代码的衔接

- 新增 AST 节点类型：`ASTTrait`、`ASTImpl`（阶段 7 实现时在 ast.h 中扩展）。
- Lexer 需增加关键字：`trait`、`impl`、`for`（及可能的 `self`）。

---

## 三、模块系统（7.3）

### 3.1 当前状态

- **import** 已实现：顶层 `import path;`，路径解析为 `lib_root/path/to/module.su`。
- **多文件编译（已实现）**：指定 `-o` 时，driver 对入口生成含 main 的 .c，对每个 import 的模块生成占位 .c（`codegen_library_module_to_c`），将所有 .c 一并传给 cc 链接，产出单一可执行文件。

### 3.2 阶段 7 目标

- **多文件编译**：入口文件 + 其 import 树内所有 .su 参与同一编译单元或同一链接单元；driver 对每个被 import 的模块产出代码并链接。
- **可见性**：可引入 `pub`/`export` 等最小可见性规则，使「仅导出」的符号可被 import 方使用；内部细节不导出。具体语法可与现有 import 对齐后补文档。

### 3.3 实现顺序

1. Driver：收集入口文件的 import 闭包，对每个模块生成 C（或 IR），再统一调用 cc 链接。
2. 符号表：typeck 或单独 pass 建立「模块 → 导出符号」表，供 codegen 与链接使用。
3. 可见性：在 AST/parser 中增加 `pub fn`/`pub struct` 等（可选，可放在 7.3 后期）。

---

## 四、标准库扩展（7.4）

- **core**：在现有 core.types、core.mem 占位基础上，扩展为自举前必须的**类型与函数声明 + 最小实现**（如 size_of、align_of、Option、Result、slice、fmt 最小、builtin、debug）。
- **std**：在现有 std 占位（io、fs、path、process、heap、string、vec、map、error 等）基础上，增加**最小实现**与**文档「自举前必须的库」清单**；与 7.1–7.3 的泛型、trait、多文件配合，使标准库可被 import 并在用户程序中调用。

标准库扩展的**具体 API 清单**见 `std/README.md` 阶段 7 节与 `core/README.md`。

---

## 五、与开发时序的对应

| 开发时序条目 | 本文档对应 |
|--------------|------------|
| 7.1 泛型     | 一、1.1–1.4：语法形态与实现顺序 |
| 7.2 Trait    | 二、2.1–2.4：语法形态与实现顺序 |
| 7.3 模块系统 | 三、3.1–3.3：多文件与可见性 |
| 7.4 标准库扩展 | 四 + std/README、core/README 清单 |

实现时按 **7.1 → 7.2 → 7.3 → 7.4** 或 **7.3（多文件）→ 7.1 → 7.2 → 7.4** 的顺序均可，视「先能链多文件」还是「先能写泛型 API」的需求而定。
