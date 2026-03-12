# platform/ — 目标文件格式（按平台）

与 **arch/** 按 CPU 架构分派类似，本目录按**宿主/目标平台**组织可重定位 .o 的格式与写出逻辑。

## 模块

| 文件 | 格式 | 说明 |
|------|------|------|
| **elf.su** | ELF64 | Linux / *BSD 等可重定位 .o；符号、重定位、patch 回填；`write_elf_o_to_buf`。 |
| **macho.su** | Mach-O 64 位 | macOS 可重定位 MH_OBJECT；复用 `ElfCodegenCtx`，`write_macho_o_to_buf`。 |
| **coff.su** | PE/COFF | Windows 可重定位 .obj（x86_64）；复用 `ElfCodegenCtx`，`write_coff_o_to_buf`。 |

## 使用

- **backend**、**asm.su**、**arch/*_enc.su** 通过 `import platform.elf`（及可选的 `platform.macho`、`platform.coff`）引用。
- 出 .o 时由 asm.su 根据 `ctx.use_coff_o`、`ctx.use_macho_o` 选择 `platform.coff.write_coff_o_to_buf`、`platform.macho.write_macho_o_to_buf` 或 `platform.elf.write_elf_o_to_buf`。
