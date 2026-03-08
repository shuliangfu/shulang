# UB 收窄测试（除零、越界）

与 `analysis/UB与未定义行为.md` 对应：编译器对整数除零、取模零及数组/切片越界插入运行时检查，触发时 `shulang_panic_`（abort），将 UB 收窄为定义行为。

- **div_zero.su**：`42 / x`，x=0 → panic
- **bounds_array.su**：`a[3]`，a 长度为 2 → panic
- **bounds_slice.su**：`s[2]`，s.len=2 → panic
- **div_ok.su**：正常除法/取模，返回 3

运行：从仓库根目录执行 `sh tests/run-ub.sh`。
