# Shulang 下一步开发清单

> 根目录清单：按顺序推进，每完成一项将 ⬜ 改为 ✅ 并保存。详细背景见 `analysis/下一步开发分析.md`、`analysis/接下来做什么-性能压榨与新std.md`。

---

## 一、高优先级

| 状态 | 项 | 验收 |
|------|----|------|
| ✅ | 修 -su -E 平台差异（Linux/Windows/Debian 上 -su -E 只出 "0" 的问题） | runtime.c：-su -E 时 setvbuf(stdout, _IONBF) 避免缓冲截断；全平台通过需结合 CI 日志再查 |
| ✅ | 提交 import 两种方式测试（const_binding / const_select + run-import.sh） | 已提交并纳入 CI，run-import 覆盖三种 import |

---

## 二、标准库（新 std，小步快跑）

| 状态 | 项 | 验收 |
|------|----|------|
| ⬜ | std.time：最小 API（单调时间、墙上时钟、sleep_ms） | 有模块、测试、文档，按需链接 |
| ⬜ | std.random：最小 API（fill_bytes、u32） | 有模块、测试、文档，按需链接 |
| ⬜ | std.env（或扩 std.process）：getenv 等独立/扩展 | 与现有 process 不重复，文档清晰 |

---

## 三、自举与 .su 迁移

| 状态 | 项 | 验收 |
|------|----|------|
| ⬜ | 放宽单函数 let 上限（避免 parser.su 做 while/for 时「too many let」） | 配置或前端放宽，bootstrap-parser 可继续扩展 |
| ⬜ | 修 bootstrap-parser / codegen（OneFuncResult、数组初始化等） | make bootstrap-parser 通过 |
| ⬜ | parser.su：补全 while/for、完整表达式解析 | 自举开发时序表 2.6、2.7、2.8、2.9、2.10 全部 ✅ |
| ⬜ | 更多 typeck/codegen 逻辑迁入 .su（10.4.2） | 自举仍过，.su 覆盖度提高 |

---

## 四、可选与收尾

| 状态 | 项 | 验收 |
|------|----|------|
| ⬜ | CI 可选跑 asm（bootstrap-driver + run-asm/run-without-c） | 文档与 CI 一致，按需跑且通过 |
| ⬜ | 测试与语言缺口：FFI 回归、return 类型断言、packed 等 | 按 tests/README §5.2 补脚本或启用断言 |
| ⬜ | 自举前基建：FFI 规范、UB 清单、Result 寄存器化、io.driver 占位 | 见 analysis/自举前-目标与缺口分析.md |

---

## 使用说明

- **顺序**：建议先做「一」再做「二」，三、四可按需穿插。
- **打勾**：完成一项后，把该项的 `⬜` 改成 `✅` 并保存本文件。
- **更新**：若某条验收标准变更，直接改表中「验收」列即可。
