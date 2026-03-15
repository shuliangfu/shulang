# std/ — 标准库 std（依赖 OS）

**标准库的 std 层**：依赖操作系统或运行时（进程、文件、网络等），在 core 之上提供统一 API。

- **用途**：用户通过 `import std.xxx` 引用；编译器解析到本目录下对应模块（如 `std/io/mod.su`）。
- **内容**：按模块单文件或子目录（runtime、process、io、fs、path、string、fmt、vec、map、thread、sync、time、net 等）。
- **原则**：内部按目标平台条件编译，**用户只写一套 API**；按需链接，未用模块不进入二进制。嵌入式可用最小 std 子集或仅 core。

详细清单与优先级见 `analysis/std标准库全量清单与优先级.md`。下文按**实现状态**分类。

---

## 一、已完善（功能完整、可用）

以下模块具备完整或对标 Zig/Rust 的 API，已实现并可使用（含测试或文档）。

| 模块 | 路径 | 说明 |
|------|------|------|
| **std.runtime** | std/runtime/ | 运行时、panic/abort 钩子 |
| **std.io** | std/io/ | IO core/driver、Reader/Writer、批读批写、print_str |
| **std.mem** | std/mem/ | Buffer、register_buffer、copy/set/compare |
| **std.fs** | std/fs/ | open/read/write/close、mmap、readv/writev |
| **std.process** | std/process/ | exit、args、getenv（spawn/exec/管道为 P3 扩展，未做） |
| **std.path** | std/path/ | 路径拼接、分解、规范化 |
| **std.heap** | std/heap/ | alloc/free/realloc、alloc_i32/alloc_u8 等 |
| **std.string** | std/string/ | String、StrView、eq/compare/find/trim/替换 |
| **std.vec** | std/vec/ | Vec_i32/Vec_u8、append_slice/truncate/reserve |
| **std.map** | std/map/ | Map_i32_i32、get/insert/remove/contains |
| **std.error** | std/error/ | Error 类型、is_ok/is_err |
| **std.net** | std/net/ | TcpStream、listen/connect/accept、UDP、批 IO |
| **std.thread** | std/thread/ | spawn/join/self、affinity、stack、qos |
| **std.time** | std/time/ | 单调/墙钟 now_*_ns/us/ms/sec、sleep_*、duration |
| **std.random** | std/random/ | fill_bytes、u32/u64、range_u32、bool（CSPRNG） |
| **std.env** | std/env/ | getenv、getenv_exists、setenv、unsetenv、temp_dir |
| **std.fmt** | std/fmt/ | 重导出 core.fmt、print/println、多参数 format |
| **std.sync** | std/sync/ | Mutex（mutex_new/lock/unlock 等） |
| **std.encoding** | std/encoding/ | UTF-8 valid/len/decode/encode、ASCII |
| **std.base64** | std/base64/ | encode_standard/decode_standard、encode_url/decode_url |
| **std.crypto** | std/crypto/ | mem_eq、sha256/sha512、hmac_sha256 |
| **std.log** | std/log/ | set_min_level、log(level, ptr, len) |
| **std.test** | std/test/ | expect、expect_eq_*、test_run |
| **std.set** | std/set/ | Set_i32/Set_u64、insert/remove/contains |
| **std.queue** | std/queue/ | 双端队列 push_back/pop_front 等 |
| **std.atomic** | std/atomic/ | load/store、compare_exchange、fetch_add 等 |
| **std.channel** | std/channel/ | 有界 channel、send/recv/try_recv |
| **std.backtrace** | std/backtrace/ | capture、symbolicate（平台相关） |
| **std.hash** | std/hash/ | SipHash、hash_start/hash_u32/u64/bytes/hash_finish |
| **std.math** | std/math/ | 常量、floor/ceil/round、sin/cos/sqrt/pow 等 |
| **std.sort** | std/sort/ | sort_slice、特化 sort_i32/sort_u8 等 |
| **std.ffi** | std/ffi/ | CStr/CString 风格，C 互操作 |
| **std.json** | std/json/ | parse number/null/bool/string，append number/null/bool，escape |
| **std.csv** | std/csv/ | next_field（RFC 4180 引号字段）、escape、unescape |
| **std.compress** | std/compress/ | zlib(deflate/inflate)、gzip、Brotli（.br）；可选 -lz / Brotli 库 |
| **std.unicode** | std/unicode/ | category、to_lower/to_upper、is_whitespace、is_ascii（ASCII 表驱动） |
| **std.dynlib** | std/dynlib/ | open/sym/close（Linux -ldl） |
| **std.http** | std/http/ | 最小 GET（解析 URL、getaddrinfo + socket + send/recv） |
| **std.tar** | std/tar/ | UStar 512 字节头 read_header/write_header |

---

## 二、部分完善（核心可用，缺部分能力或平台）

| 模块 | 路径 | 说明 |
|------|------|------|
| **std.regex** | std/regex/ | Linux 使用 POSIX regex.h（compile/match/free）；Windows 为占位，返回失败。 |
| **std.process 扩展** | std/process/ | 当前仅有 exit/args/getenv；spawn/exec/管道等为 P3 规划，未实现。 |

---

## 三、占位（仅声明或空实现）

以下模块仅有 mod.su 声明或 C 层返回 -1/空，待语言或工具链支持后再实现。

| 模块 | 路径 | 说明 |
|------|------|------|
| **std.elf** | std/elf/ | 仅占位；ELF 解析依赖工具链/用途，按需再做。 |
| **std.async** | std/async/ | 仅占位；异步运行时与语言阶段一致后再做。 |
| **std.simd** | std/simd/ | 仅占位；向量类型/SIMD 与语言/目标架构一致后再做。 |

---

## 四、测试覆盖情况

**结论**：已完善模块并非全部都有**全面覆盖 + 边界测试**；多数仅有**最小 smoke 测试**（单条路径、单次调用），边界与异常路径普遍欠缺。

### 4.1 有独立回归测试且已纳入 run-all.sh 的模块

以下模块在 `tests/` 下有对应 `tests/xxx/main.su` 与 `run-xxx.sh`，且已在 `tests/run-all.sh` 中执行：

runtime、io、io-driver、mem、fs、process、path、heap、string、vec、map、error、net、time、env、fmt、fmt-std、sync、encoding、base64、crypto、log、stdtest、set、queue、atomic、channel、backtrace、hash、math、sort、ffi、json、csv、unicode、dynlib、compress、thread、random、core-types、builtin、debug 等（具体以 `tests/run-all.sh` 中 run run-*.sh 为准）。

### 4.2 已纳入 run-all.sh 的 thread / random

- **std.thread**：`tests/thread/main.su`、`run-thread.sh`，已加入 run-all.sh。
- **std.random**：`tests/random/main.su`、`run-random.sh`（含 range_u32 边界 100..100），已加入 run-all.sh。

### 4.3 已完善但暂无独立测试的模块

- **std.http**：无 `tests/http/`、无 `run-http.sh`；建议补最小 GET 往返或 mock 测试。
- **std.tar**：无 `tests/tar/`、无 `run-tar.sh`；建议补 read_header/write_header 往返与校验和边界。

### 4.4 测试深度说明

- **当前**：多数测试为「单用例、单路径」smoke，仅保证 API 可调、不崩溃、返回值符合预期（如 json 测 parse_null/parse_bool/append_number；csv 测一次 next_field 与 escape；string 仅测 string_empty）。
- **欠缺**：  
  - **全面覆盖**：未系统覆盖各 API 的每种参数组合与返回值。  
  - **边界测试**：空输入、长度为 0、缓冲区刚够/不足、非法输入、最大长度、整数溢出等。  
  - ** round-trip 与一致性**：如 base64 编解码往返、compress 解压后与原数据一致等（compress 已有；json/csv/base64 可加强）。

后续建议：对每个已完善模块逐步补充「API 全覆盖 + 边界与异常用例」，并保持 run-all.sh 与文档同步。

---

## 五、参考

- 优先级与全量清单：`analysis/std标准库全量清单与优先级.md`（P0～P4、对标 Zig/Rust）。
- 各子目录下的 `README.md`（若有）描述该模块 API、编译与平台说明。
