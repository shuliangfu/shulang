# std.path — 路径拼接、分解、规范化

与 **Rust** `std::path::Path`、**Go** `path/filepath`、**Zig** `std.fs.path` 对标，提供路径的 (ptr, len) 处理，不依赖结尾 NUL。

---

## API 一览

| API | 说明 | 对标 |
|-----|------|------|
| `path_sep(): u8` | 当前平台路径分隔符（POSIX 为 47 `'/'`） | Zig `sep`、Go `Separator` |
| `path_empty_len(): i32` | 空路径长度 0，与 path_join 等配合 | — |
| `path_join(out, out_max, a, a_len, b, b_len): i32` | 将 a 与 b 拼接，中间按需加 `/`，写入 out；溢出 -1 | Rust `join`、Go `Join`、Zig `join` |
| `path_dirname(path, path_len, out, out_max): i32` | 目录部分（最后一个 `/` 之前），写入 out | Rust `parent`、Go `Dir`、Zig `dirname` |
| `path_basename(path, path_len, out, out_max): i32` | 最后一段（文件名），写入 out | Rust `file_name`、Go `Base`、Zig `basename` |
| `path_extension(path, path_len, out, out_max): i32` | 扩展名（含点，如 `.txt`）；无或隐藏文件返回 0 | Rust `extension`、Go `Ext`、Zig `extension` |
| `path_stem(path, path_len, out, out_max): i32` | 最后一段去掉扩展名 | Rust `file_stem`、Zig 同语义 |
| `path_is_absolute(path, path_len): i32` | 是否绝对路径（POSIX：首字节 `'/'` 为 1） | Rust `is_absolute`、Go `IsAbs`、Zig `isAbsolute` |
| `path_clean(path, path_len, out, out_max): i32` | 规范化：合并 `/`、去掉 `.` 段、`..` 消前段；溢出 -1 | Go `Clean`、Zig 类似 |
| `path_extension_and_stem(path, path_len, ext_out, ext_max, stem_out, stem_max): i32` | 一次扫描同时写 extension 与 stem；返回 `(stem_len<<16)\|ext_len` 或 -1 | 性能：避免两次 last_slash+last_dot |

内部辅助（不对外承诺稳定）：`path_last_slash`、`path_last_dot`。

---

## 性能

- **O(1)**：`path_sep`、`path_is_absolute`（仅看首字节）。
- **单次扫描 + 一次拷贝**：`path_join`、`path_dirname`、`path_basename`；路径通常很短，已接近最优。
- **同时要 extension 与 stem**：用 `path_extension_and_stem` 可少一次 `path_last_slash` 与一次 `path_last_dot`（由两次扫描降为一次）。
- **path_clean**：单遍扫描，栈上 64 个 i32 记录段起始；超长路径可考虑分段或限制段数。

---

## 约定

- 路径均按 **`(ptr, len)`** 处理，**不写 NUL**；调用方在需要时自设 `out[ret]=0`。
- **POSIX**：分隔符 `'/'`（47）；Windows 可后续扩展 `path_sep` 与 `path_is_absolute`。
- **extension**：含点（如 `.txt`）；仅最后一个 `.` 后为扩展；无扩展或隐藏文件（如 `.gitignore`）返回长度 0。
- **clean**：根 `/` 保留；空或仅 `.` 写出 0 长度；最多 64 段。

---

## 测试

- `tests/path/main.su` — path_empty_len
- `tests/path/join_basename.su` — path_join、path_basename、path_dirname
- `tests/path/extension_stem_abs_clean.su` — path_extension、path_stem、path_is_absolute、path_sep、path_clean

运行：`./tests/run-path.sh`
