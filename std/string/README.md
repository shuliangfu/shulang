# std.string — 字符串类型与基本操作

与 **Rust** `str`/`String`、**Go** `strings`、**Zig** `[]const u8` + `std.mem` 对标，提供固定缓冲 **256 字节**的 `String` 及构造、比较、查找、子串、trim、单字节替换、追加与拷贝。

---

## 对标 Zig / Rust / Go 简表

| 能力 | Rust | Go | Zig |
|------|------|-----|-----|
| 长度/空 | len, is_empty | len(s) | .len |
| 比较 | eq, cmp | Compare | std.mem.eql |
| 包含子串 | contains | Contains | indexOf != null |
| 子串首次位置 | find | Index | std.mem.indexOf |
| 单字节首次 | find | IndexByte | indexOfScalar |
| 单字节最后 | rfind | LastIndexByte | lastIndexOfScalar |
| 前后缀 | starts_with, ends_with | HasPrefix, HasSuffix | startsWith, endsWith |
| 去首尾空格 | trim | TrimSpace | 手动或 std.mem.trim |
| 单字节替换 | replace | Replace | 手动循环 |
| 追加 | push, push_str | + / WriteString | append 等 |

当前实现为**字节语义**，无 UTF-8/Unicode；上述 API 均按字节操作。

---

## 吸收 Zig / Rust / Go 的优化与取舍

我们**已吸收**且与项目宗旨（无 GC、轻量、性能）一致的部分：

| 思路 | Zig / Rust / Go 做法 | 我们的做法 |
|------|----------------------|------------|
| **字符串即切片/视图** | Go `string`、Zig `[]const u8`、Rust `&str` 都是 (ptr, len)，不限制长度。 | **StrView** = (ptr, len)，零拷贝、不限制长度；大块数据一律用 StrView，不拷入 String。 |
| **长串用 libc 快路径** | 比较/查找用 memcmp、memchr、strstr 等。 | 长 StrView（≥32 或 needle≥8）走 **memcmp / memmem**（std/string/string.c），短串保留 .su 循环并做 4 字节展开与超短串特判。 |
| **零拷贝传参** | 函数普遍接受 `&str` / `string` / `[]const u8`，不强制拷贝。 | API 接受 **StrView** 或 (ptr, len)；输出用 **string_data_ptr + string_len**，避免 string_copy_to。 |
| **只读与可变分离** | Rust String vs &str；Go string 只读。 | **StrView** 只读；**String** 可原地修改，但固定 256 字节。 |

我们**有意不做**、以保持轻量级与无 GC 的部分：

| 他们的做法 | 为何我们暂不采用 |
|------------|------------------|
| **Rust String 堆分配、可无限增长** | 会引入堆与释放责任，与「无 GC、一切要小」冲突；若未来有 std.heap，可再提供可选「堆上可增长字符串」类型。 |
| **语言内置“无长度上限”的 string** | 不分配堆的前提下，要么固定容量（当前 String 256），要么只用视图（StrView）；我们两者都有，文档约定「短用 String，长用 StrView」。 |

**推荐用法（对齐三语言习惯）**：  
- 函数参数能接受「只读字符串」时，优先用 **StrView** 或 (ptr, len)，避免拷贝（类似 Go/Zig 传 string/slice、Rust 传 `&str`）。  
- 只在需要**短、可变、栈上持有**时用 **String**（≤256 字节）。

---

## 零拷贝与性能

- **零拷贝输入**：已有 `(ptr, len)` 时不必拷入 `String`。使用 **StrView**：`string_view(ptr, len)` 得到只读视图，再用 `string_view_*`（len、eq、compare、find_char、starts_with、ends_with、contains、find_slice）操作，无任何拷贝。
- **零拷贝输出**：需要把 `String` 当 `(ptr, len)` 传给 std.fs/std.path 时，用 `string_data_ptr(&s)` + `string_len(s)` 即可，无需 `string_copy_to`。调用方在 `s` 未被修改前使用该指针。
- **性能**：拷贝类（from_slice/append_slice/copy_to/copy_to_ptr/trim）≥**8** 字节走 C **memcpy**；比较与查找（eq/compare/find_char/find_slice/rfind_char、view 同）≥**32** 字节走 C **memcmp/memchr/memmem**；**starts_with/ends_with** 在 prefix/suffix≥**8** 时走 **memcmp**；热路径用字面量 8/32 并 **string_*_ptr** 避免阈值调用与 260 字节按值传递；eq/view_eq 对长度 1～4 做特判、其余短循环做 **4 字节展开**；find_slice 在 needle 长度为 1 时 C 端走 **memchr**。

## 「大块」指多大？几 MB 的文本可以吗？

- **String 固定缓冲**：最大 **256 字节**（`string_capacity()`），适合短路径、文件名、短句等；超过 256 字节的数据**不能**塞进 String；`string_from_slice` 超长会截断到 256，`string_append_slice` 超出会返回 -1。所以「大块」= **大于 256 字节** 时请用 StrView / Buffer。
- **几 MB 的文本完全可以**：做法是**不要**把整块拷进 String，而是：
  1. 用 std.fs 读入到**缓冲区**（如 `fs_read` 大块、或 mmap 得到 `(ptr, len)`）；
  2. 用 **StrView** 包装该缓冲区：`v = string_view(ptr, len)`，len 可以是几 M；
  3. 用 `string_view_*`（eq、compare、find_slice、contains、starts_with、ends_with 等）对整块做只读操作，**零拷贝**。
- StrView 本身**不限制长度**（只受地址空间限制），所以「直接读取一个几 M 大小的文本」是**支持**的：读进 buffer，再用 StrView 操作即可。

## 长 StrView 性能（已优化）

- **块拷贝**：from_slice/append_slice/copy_to/copy_to_ptr/trim 在长度 ≥ **8** 时走 C **memcpy**，否则 4 字节展开逐字节拷贝。
- **比较与查找**：eq/compare/find_char/find_slice/rfind_char 在长度 ≥ **32** 时走 C **memcmp/memchr/memmem**；eq/view_eq 对长度 1～4 特判、5～31 做 4 字节展开；find_slice 在 needle 长度为 1 时 C 端用 **memchr**。
- **starts_with/ends_with**（String 与 View）在 prefix/suffix ≥ **8** 时走 **memcmp**。需链接 `std/string/string.o`。
- **热路径 _ptr**：`string_len_ptr`、`string_is_empty_ptr`、`string_eq_ptr`、`string_compare_ptr`、`string_copy_to_ptr` 接受 `*String`，避免 260 字节按值传递；热路径内用字面量 8/32 避免阈值函数调用。

---

## 类型

| 类型 | 说明 |
|------|------|
| `String` | `{ data: [256]u8, len: i32 }`，不分配堆，最大 256 字节。 |
| `StrView` | `{ ptr: *u8, len: i32 }`，只读视图，零拷贝包装 (ptr, len)。 |

---

## API 一览

| API | 说明 | 对标 |
|-----|------|------|
| `string_empty(): i32` | 空长度常量 0。 | — |
| `string_capacity(): i32` | 最大字节数 256。 | Rust capacity |
| `string_new(): String` | 新建空字符串。 | Rust String::new |
| `string_len(s: String): i32` | 当前字节数。 | Rust len、Go len(s) |
| `string_is_empty(s: String): i32` | 是否为空，1 是 0 否。 | Rust is_empty、Go len(s)==0 |
| `string_is_empty_ptr(s: *String): i32` | 指针版 is_empty，热路径减拷贝。 | — |
| `string_from_char(c: u8): String` | 单字符构造。 | — |
| `string_from_slice(ptr, len): String` | 从 (ptr, len) 拷贝构造，超长截断至 256。 | Rust from_utf8 等 |
| `string_get(s, i): u8` | 取第 i 字节（越界未定义）。 | Rust as_bytes()[i] |
| `string_eq(a, b): i32` | 相等比较，1 相等 0 不等；长串 memcmp。 | Rust eq、Go Compare |
| `string_eq_ptr(a, b: *String): i32` | 指针版相等，热路径少拷贝；长串 memcmp。 | — |
| `string_compare(a, b): i32` | 字典序，<0 / 0 / >0；长串 memcmp。 | Rust cmp、Go Compare |
| `string_compare_ptr(a, b: *String): i32` | 指针版字典序，热路径少拷贝；长串 memcmp。 | — |
| `string_clear(s: *String): i32` | 清空 len。 | Rust clear |
| `string_append_char(s: *String, c: u8): i32` | 追加一字节，0 成功 -1 溢出。 | Rust push |
| `string_append_slice(s: *String, ptr, len): i32` | 追加 (ptr,len)，0 成功 -1 溢出。 | Rust push_str |
| `string_copy_to(s, out, out_max): i32` | 拷贝到 out，返回长度或 -1；长块 memcpy。 | 与 (ptr,len) API 对接 |
| `string_copy_to_ptr(s, out, out_max): i32` | 指针版 copy_to，热路径减拷贝；长块 memcpy。 | — |
| `string_find_char(s, c): i32` | 首次出现 c 的下标，-1 表示不存在。 | Rust find、Go IndexByte |
| `string_starts_with(s, prefix, prefix_len): i32` | 是否以 prefix 开头，1 是 0 否；长 prefix 走 memcmp。 | Rust starts_with、Go HasPrefix |
| `string_ends_with(s, suffix, suffix_len): i32` | 是否以 suffix 结尾，1 是 0 否；长 suffix 走 memcmp。 | Rust ends_with、Go HasSuffix |
| `string_contains(s, sub, sub_len): i32` | 是否包含子串，1 是 0 否。 | Rust contains、Go Contains |
| `string_find_slice(s, sub, sub_len): i32` | 子串首次下标，-1 表示不存在。 | Rust find、Go Index |
| `string_rfind_char(s, c): i32` | 字节 c 最后出现下标，-1 表示不存在。 | Rust rfind、Go LastIndexByte |
| `string_trim_space(s, out, out_max): i32` | 去首尾空格写入 out，返回长度或 -1。 | Rust trim、Go TrimSpace |
| `string_replace_char(s, from, to): i32` | 原地把 from 换成 to，返回替换次数。 | Rust replace、Go Replace |

**StrView（零拷贝只读）**：`string_view(ptr, len)`、`string_view_len`、`string_view_is_empty`、`string_view_get`、`string_view_eq`、`string_view_eq_slice`、`string_view_compare`、`string_view_find_char`、`string_view_starts_with`、`string_view_ends_with`、`string_view_find_slice`、`string_view_contains`。

---

## 约定

- **不分配堆**：最大长度 256；`string_from_slice` 超长截断，`string_append_slice` 无法全部追加时返回 -1。
- **与 (ptr, len) 互转**：`string_from_slice` 从裸指针构造；零拷贝时用 `string_view` + `string_view_*` 只读、或 `string_data_ptr` + `string_len` 写出；需拷贝时用 `string_copy_to`。
- **修改**：`string_clear`、`string_append_char`、`string_append_slice`、`string_replace_char` 接受 `*String`，原地修改。

---

## 测试

- `tests/string/main.su` — string_empty
- `tests/string/from_slice_eq.su` — from_slice、len、is_empty、eq
- `tests/string/compare_append_find.su` — compare、append、find_char、starts_with、ends_with、copy_to
- `tests/string/contains_trim_replace.su` — contains、find_slice、rfind_char、trim_space、replace_char
- `tests/string/view_zerocopy.su` — StrView、string_view_*、string_data_ptr、string_eq_view

运行：`./tests/run-string.sh`
