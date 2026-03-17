# Shulang Language

在 VS Code / Cursor 中为 `.su`（Shulang）提供语法高亮、语言配置和 LSP。

## 功能

- **语法高亮**：关键字、类型、字面量、注释、字符串、运算符
- **语言配置**：行/块注释、括号配对与自动闭合、折叠、单词边界
- **文件图标**：`.su` 在编辑器和文件树中显示专用图标；可在「文件图标主题」中选择 **Shulang (.su)** 以在资源管理器中为 .su 使用该图标
- **LSP**：诊断（问题面板）、转到定义、查找引用、悬停显示类型、**文档格式化**

LSP 需要本机已安装 **shu**（Shulang 编译器），扩展会通过 `shu --lsp` 启动语言服务。

## 安装

1. 按 **Ctrl+Shift+P**（Mac：**Cmd+Shift+P**），输入 **Install from VSIX**，选 **Extensions: Install from VSIX...**
2. 选择本扩展的 `.vsix` 文件
3. 按提示重载窗口

或在 **扩展** 视图右上角 **⋯** 里选 **从 VSIX 安装...**，再选 `.vsix` 文件。

## 配置

| 设置 | 说明 | 默认 |
|------|------|------|
| `shulang.serverPath` | shu 可执行文件路径 | `shu`（从 PATH 查找） |

shu 不在 PATH 时，在设置里搜 **Shulang**，把 **Shulang: Server Path** 设为 shu 的路径（绝对路径或相对工作区根，如 `compiler/shu`）。

### 代码格式化

对 `.su` 文件可使用 **格式化文档**（右键 → 格式化文档，或快捷键）。扩展已为 `[su]` 设置默认格式化器；如需保存时自动格式化，在设置中为 `[su]` 开启 `editor.formatOnSave`。

格式化选项通过 LSP 的 `textDocument/formatting` 请求的 `params.options` 传入，可由支持传递 FormattingOptions 的客户端使用。支持的选项如下：

| 选项 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `tabSize` | 数字 | `2` | 每级缩进宽度（1–16），仅当 `insertSpaces` 为 true 时有效 |
| `insertSpaces` | 布尔 | `true` | 使用空格缩进；为 false 时使用 Tab |
| `maxLineLength` | 数字 | `100` | 每行最大字符数（20–512），超长时在空格处折行 |
| `insertFinalNewline` | 布尔 | `true` | 为 true 时保证文件末尾有且仅有一个换行；为 false 时去掉末尾换行 |
| `trimTrailingWhitespace` | 布尔 | `true` | 为 true 时去掉每行行尾空格/制表符；为 false 时保留 |
| `trimFinalNewlines` | 布尔 | `true` | 为 true 时将文件末尾多余空行压成至多一个换行；为 false 时保留 |

在 VS Code 中，`editor.tabSize`、`editor.insertSpaces` 等会由语言客户端传给 LSP；若需自定义行宽等，可在扩展或客户端侧在请求里附带上述 `options`。

## 要求

- VS Code 或 Cursor（引擎 ^1.75.0）
- 使用 LSP 时需本机可运行 shu
