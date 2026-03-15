# std.fs + std.io 性能评估：是否已压榨到极致？能否超越三平台？

## 一、当前已实现（按平台）

### Linux

| 能力 | 状态 | 说明 |
|------|------|------|
| **io_uring** | ✅ | 每线程一 ring(512 条目)；SQPOLL + fixed files 尝试，失败回退普通 ring；单次 read/write、batch readv/writev 均走 uring |
| **O_DIRECT** | ✅ | fs_open_read_direct，buf/offset 对齐 fs_direct_align() |
| **mmap + madvise** | ✅ | fs_mmap_ro/rw，MADV_SEQUENTIAL；≥2MB 时 MADV_HUGEPAGE |
| **fadvise** | ✅ | fs_fadvise_sequential / fs_fadvise_willneed |
| **零拷贝** | ✅ | copy_file_range（文件→文件）、sendfile（文件→socket） |
| **分散/集中 I/O** | ✅ | fs_readv2/fs_writev2；std.io read_batch_fd/write_batch_fd 走 readv/writev 或多 SQE |
| **范围刷盘 / 预分配** | ✅ | fs_sync_range、fs_fallocate |
| **与 std.io 联合** | ✅ | fd → read_fd/write_fd/read_batch_fd/write_batch_fd，走 io_uring |

### macOS

| 能力 | 状态 | 说明 |
|------|------|------|
| **kqueue** | ✅ | std.io 每线程 kqueue，fd≥3 时 kevent 再 read |
| **mmap** | ✅ | fs_mmap_ro/rw（无 fadvise，平台无 POSIX_FADV_*） |
| **pread/pwrite** | ✅ | 同 Linux |
| **readv/writev** | ✅ | fs_readv2/fs_writev2、std.io batch |
| **无缓存读（F_NOCACHE）** | ✅ | fs_open_read_direct 用 fcntl(F_NOCACHE)；fs_direct_align 返回 4096 |
| **copy_file_range** | ✅ | 读+写循环回退（无内核 copy_file_range） |
| **sendfile/fallocate/sync_range** | ❌ | 平台无或 API 不同，no-op/桩 |

### Windows

| 能力 | 状态 | 说明 |
|------|------|------|
| **IOCP + Overlapped** | ✅ | std.io 用 CreateIoCompletionPort + ReadFile/WriteFile + GetOverlappedResult；batch 有 OVERLAPPED 池(8) |
| **std.fs 内存映射** | ✅ | fs_mmap_ro/rw：CreateFileMapping + MapViewOfFile；fs_munmap：UnmapViewOfFile |
| **无缓冲打开** | ✅ | fs_open_read_direct：CreateFile + FILE_FLAG_NO_BUFFERING，_open_osfhandle 得 CRT fd；fs_direct_align 用 GetSystemInfo 页大小 |
| **copy_file_range** | ✅ | ReadFile/WriteFile 循环（256KB 缓冲），两 fd 当前偏移前进 |
| **readv2/writev2** | ✅ | 两段 ReadFile / 两段 WriteFile |
| **TransmitFile** | ✅ | fs_sendfile：TransmitFile(socket, file, count)；需链 ws2_32 + mswsock |
| **fallocate** | ✅ | SetFilePointerEx + SetEndOfFile，仅扩展不收缩 |
| **sync_range** | ⚪ | 当前 no-op（Windows 无等价范围刷盘 API），返回 0 以兼容 |

---

## 二、是否已经压榨到极致？

- **Linux**：**已非常接近**。已用 io_uring、O_DIRECT、mmap、fadvise、madvise、copy_file_range、sendfile、readv/writev、sync_range、fallocate，与手写 C 用同一套内核能力，可视为「同一水平」。尚未用尽的可压榨点见下节。
- **macOS**：**未到极致**。无 io_uring 级 API，已用 kqueue + readv/writev 已算合理；可再考虑 Dispatch I/O、真正异步、更大 batch。
- **Windows**：**已补全**。std.fs 已实现内存映射、无缓冲打开、copy_file_range、readv2/writev2、TransmitFile、fallocate；仅 sync_range 为 no-op。与 std.io 的 IOCP 联合即可达到系统级高性能。

---

## 三、还能继续压榨的方向

### 通用

- **真正异步**：当前 std.io 为「submit + 等一次完成」的同步风格；可暴露 submit 与 wait 分离、多请求 in-flight，重叠 I/O 与计算。
- **批量段数**：read_batch_fd/write_batch_fd 目前最多 4 段；io.c 内部已有 8 段路径，可对 .su API 开放 8 段或更多。
- **固定 buffer 池**：Linux 下 io_uring_register_buffers 已预留；可对高频路径使用 fixed buffer，减少拷贝/注册开销。

### Linux

- **ring 扩大**：IO_URING_RING_ENTRIES 从 512 提高到 2K/4K，高并发时减少 submit 轮次。
- **SQPOLL / polled 模式**：已尝试 SQPOLL + fixed files；可继续优化失败回退路径与 fd 注册策略。
- **IORING_SETUP_DEFER_TASKRUN / SINGLE_ISSUER**：已用；可结合批量化进一步减少系统调用次数。

### macOS

- **Dispatch I/O**：可用 GCD 的 dispatch_read/dispatch_write 做大块、异步、分片 I/O，与 kqueue 互补。
- **fcntl(F_NOCACHE)**：类似 O_DIRECT 的绕过页缓存（部分场景），可按需支持。

### Windows

- **std.fs 已补全**：CreateFileMapping/MapViewOfFile、FILE_FLAG_NO_BUFFERING、ReadFile/WriteFile 实现 copy_file_range 与 readv2/writev2、TransmitFile、SetEndOfFile 实现 fallocate。
- **可继续压榨**：打开文件时用 CreateFile + FILE_FLAG_OVERLAPPED，同一 handle 走 std.io IOCP 批量 Overlapped；SetFileCompletionNotificationModes(SKIP) 已用，可扩展更多 handle 缓存。

---

## 四、能否「超越」Linux / macOS / Windows 的高性能 I/O？

- **Linux**：**不能超越内核能力**。当前实现已与「手写 C + io_uring + O_DIRECT + mmap」用同一套内核接口，性能在同一量级；可优化的是批大小、ring 大小、异步模型等，属于同一水平上的微调，而非超越内核。
- **macOS**：**与系统能力持平**。无 io_uring，我们已用 kqueue + readv；在系统提供的 API 范围内已算压榨到位，谈不上超越系统。
- **Windows**：**已补全**。std.fs 已实现内存映射、无缓冲 I/O、TransmitFile、fallocate 等，与 std.io 的 IOCP 联合可达到「原生 C + IOCP + 内存映射」同一水平，无法超越系统 API。

**结论**：在 **Linux** 上已可与手写 C 的高性能 I/O 比肩；在 **macOS** 上已合理利用 kqueue + readv；在 **Windows** 上 std.fs 已补全，与 std.io 联合可达到三平台「都达到各自系统级高性能」的目标。真正「超越」三平台原生 I/O 不现实，因为上限由内核/OS 提供；我们的目标是**在每平台上把系统提供的能力用满、用对**。

---

## 五、与 Zig 的 std.fs / std.io 对比：能否比肩？能否超越？

### 5.1 Zig 现状（简要）

- **std.fs**：File 的 read/write/seek、createFile/openFile；复制用 copy_file_range（Linux）、fcopyfile（Darwin）、sendfile（BSD），有 copyRange 与 offset；mmap 通过 std.posix.mmap（传统上 Windows 不提供，新 API 在演进）。
- **std.io**：Reader/Writer 抽象、通用流接口；**标准库本身不内置 io_uring/kqueue/IOCP**，高性能事件循环依赖社区库（如 libxev、zig-aio）提供 io_uring/kqueue/IOCP 后端。
- **特点**：API 清晰、零分配设计、跨平台；高性能 IO 需额外依赖或自研。

### 5.2 Shu 与 Zig 对比

| 维度 | Zig | Shu（std.fs + std.io） |
|------|-----|------------------------|
| **高性能 IO 后端** | 标准库无，需 libxev/zig-aio 等 | **标准库内置** io_uring（Linux）、kqueue（macOS）、IOCP（Windows），统一 Buffer + submit + completion |
| **mmap 三平台** | posix.mmap，Windows 支持在演进 | **已支持** Linux/macOS/Windows（含 CreateFileMapping/MapViewOfFile） |
| **无缓冲/O_DIRECT** | 需手写或平台 API | **已提供** fs_open_read_direct + fs_direct_align（Linux O_DIRECT、macOS F_NOCACHE、Windows FILE_FLAG_NO_BUFFERING） |
| **零拷贝复制** | copy_file_range/fcopyfile/sendfile，有 copyRange | **有** fs_copy_file_range（Linux 零拷贝；macOS/Windows 读+写回退）、fs_sendfile |
| **分散/集中 I/O** | 需手写 readv/writev 或等价 | **已提供** fs_readv2/fs_writev4、read_batch_fd/write_batch_fd（最多 4 段） |
| **fadvise/fallocate/sync_range** | 部分在 posix 或需自行封装 | **已提供** fadvise（Linux）、fallocate（Linux/Windows）、sync_range（Linux） |
| **错误码** | 通过 Result 或 error 类型 | **已提供** fs_last_error() 统一取 errno/GetLastError |
| **打开模式** | createFile/openFile 配 flags | **已提供** fs_open_append、fs_open_create |

### 5.3 能否比肩？能否超越？

- **比肩**：**可以**。在「三平台、大文件、高性能、零拷贝与批量化」维度上，Shu 的 std.fs + std.io 已覆盖 Zig std 已提供或常用的能力，并在「标准库内建 io_uring/kqueue/IOCP」「mmap/无缓冲/readv4 三平台」「错误码与打开模式」等点上与 Zig 相当或更齐全（Zig 需依赖社区库才能达到同等后端）。
- **超越**：**在「开箱即用」与「标准库内高性能后端」意义上可以认为超越**。Zig 标准库不包含 io_uring/kqueue/IOCP，用户需选型并集成 libxev、zig-aio 等；Shu 标准库直接提供三平台高性能后端与统一 API，无需额外依赖即可达到与 Zig+libxev 同级的 IO 路径。在「语言表现力、生态、工具链成熟度」上 Zig 仍更成熟，此处仅就 **std.fs / std.io 的能力与内置高性能后端** 论。

**结论**：Shu 的 io/fs 在**能力与内置高性能后端**上可与 Zig 比肩，在**开箱即用的高性能 IO（无需第三方事件循环）**上可视为超越 Zig 标准库；与「Zig + libxev/zig-aio」相比属同一水平，各有取舍。
