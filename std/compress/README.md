# std.compress

压缩封装（P4 可选；对标 Zig std.compress、Rust flate2）。提供 **zlib**、**gzip**（.gz）、**Brotli**（.br），各格式可选编译。

**实现**：启用对应库时，上述 API 均为**真实压缩/解压**（zlib 用 `compress2`/`uncompress` 与 deflate/inflate 流；Brotli 用 `BrotliEncoderCompress`/`BrotliDecoderDecompress`）。未启用时为占位，返回 -1。`tests/compress/main.su` 与 `run-compress.sh` 对 gzip、brotli 做压缩→解压往返校验。

## 格式说明

- **zlib**：2 字节头 + deflate 流 + 4 字节 Adler-32，常用于 HTTP 等协议。API：`deflate` / `inflate`。
- **gzip**：.gz 文件格式，含 gzip 头、deflate 流、8 字节尾。API：`gzip_compress` / `gzip_decompress`。
- **Brotli（.br）**：压缩率通常优于 gzip（尤其文本），HTTP Content-Encoding: br。API：`brotli_compress` / `brotli_decompress`。

## 平台与系统支持

- **不启用任何库**：所有系统均支持，对应 API 为占位（返回 -1），无额外依赖。
- **zlib / gzip**：Linux、macOS、BSD 上 zlib 多为系统自带或包管理可装（如 `libz-dev` / `zlib-devel`）；Windows 需自行提供 zlib（如 vcpkg、MSYS2 或自带头库）。
- **Brotli**：各系统均需额外安装（如 Linux `libbrotli-dev`、macOS `brew install brotli`、Windows vcpkg 等），非默认自带。

## 编译与链接

- **不定义**：对应格式为占位，返回 -1，无额外依赖。
- **zlib**：编译 `-DSHU_USE_ZLIB`，链接 `-lz`。
- **Brotli**：编译 `-DSHU_USE_BROTLI`，链接 `-lbrotlienc -lbrotlidec`（或部分系统 `-lbrotli`）。例如：
  - 编译：`cc -DSHU_USE_BROTLI -I/usr/include -c -o std/compress/compress.o std/compress/compress.c`
  - 链接：在 cc 参数中加 `-lbrotlienc -lbrotlidec`。

## API

- **deflate(in, in_len, out, out_cap): i32** — 压缩为 zlib 格式，返回写入字节数，失败 -1。
- **inflate(in, in_len, out, out_cap): i32** — 解压 zlib 流，返回写入字节数，失败 -1。
- **gzip_compress(in, in_len, out, out_cap): i32** — 压缩为 gzip 格式（.gz），返回写入字节数，失败 -1。
- **gzip_decompress(in, in_len, out, out_cap): i32** — 解压 gzip 流，返回写入字节数，失败 -1。
- **brotli_compress(in, in_len, out, out_cap): i32** — 压缩为 Brotli 格式（.br），返回写入字节数，失败 -1。
- **brotli_decompress(in, in_len, out, out_cap): i32** — 解压 Brotli 流，返回写入字节数，失败 -1。
