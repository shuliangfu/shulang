# std.tar

tar 归档读/写（P4 可选）。当前 read_header/write_header 为占位，返回 -1。后续可基于 std.fs、std.io 实现。

## API

- **read_header(buf, len, name_out, name_cap, size_out): i32** — 占位，返回 -1
- **write_header(buf, buf_cap, name, name_len, file_size): i32** — 占位，返回 -1
