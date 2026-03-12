#!/usr/bin/env python3
# fix_pipeline_gen.py — 修正 -E 生成 pipeline_gen.c 中的声明顺序与命名冲突
# 1. parser: zero_u8_p 使用在声明之前 → 改为 zero_u8
# 2. platform_elf_elf_resolve_patches: delta/next_insn 在使用前未声明 → 先 while(l) 再算 delta，再 e_machine 块
# 3. write_elf_o_to_buf: rela 与 extern read 冲突 → 改为 rela_buf 并声明

import re
import sys

def main():
    path = "pipeline_gen.c" if len(sys.argv) < 2 else sys.argv[1]
    with open(path, "r") as f:
        content = f.read()

    # 1. zero_u8_p: 使用处改为 zero_u8；删掉循环后多余的 "uint8_t zero_u8_p = 0;"
    content = content.replace(
        "(((param).name)[pk] = zero_u8_p, 0)",
        "(((param).name)[pk] = zero_u8, 0)",
    )
    content = re.sub(
        r"\n      uint8_t zero_u8_p = 0;\n    \}\n    \(void\)\(\(\(f\)\.return_type_ref",
        "\n    }\n    (void)(((f).return_type_ref",
        content,
    )

    # 2. rela → rela_buf，避免与 extern read 冲突（含数组下标与 elf_append 调用）
    content = content.replace("(rela)[", "(rela_buf)[")
    content = content.replace("out, rela, 24)", "out, rela_buf, 24)")
    if "rela_buf[24]" not in content:
        content = re.sub(
            r"(  while \(r < \(ctx\)->num_relocs\) \{\s*\n)(    int32_t sym_idx = 0;)",
            r"\1    uint8_t rela_buf[24] = {0};\n\2",
            content,
            count=1,
        )

    # 2.5 parser 死循环根因：parse_into/parse_into_buf 的 while 循环必须在每次成功解析一个函数后用 res.next_lex 更新 lex，
    # 否则下一轮仍用旧 lex，词法位置不前进导致死循环。此处一律在 num_funcs 自增后插入该行（已存在则多一行重复赋值，无害）。
    _num_funcs_inc = "(void)(((module)->num_funcs = (module)->num_funcs + 1));"
    _lex_next = "(void)((lex = (res).next_lex));"
    if _num_funcs_inc in content:
        idx = 0
        while True:
            pos = content.find(_num_funcs_inc, idx)
            if pos == -1:
                break
            after = pos + len(_num_funcs_inc)
            line_end = content.find("\n", after)
            if line_end == -1:
                break
            insert_at = line_end + 1
            content = content[:insert_at] + "    " + _lex_next + "\n" + content[insert_at:]
            idx = insert_at + len(_lex_next) + 2

    # 2.6/2.7/2.8 诊断已关闭：不再注入 parse_into/collect_imports/lexer_next 的 stderr 调试输出
    # 2.9 根因：codegen 将 skip_whitespace 中「//」与「#」分支的 continue 提到 while 前，导致 l 未更新即回到循环 → 死循环。把 continue 移到 while 体后。
    # 行注释：") == 47) {   continue;\n  while" → ") == 47) {\n  while" 且 "  }\n } else" → "  }\n  continue;\n } else"
    content = content.replace(
        ") == 47) {   continue;\n  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {\n    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));\n  }\n } else (__tmp = 0) ; __tmp; }));",
        ") == 47) {\n  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {\n    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));\n  }\n  continue;\n } else (__tmp = 0) ; __tmp; }));",
        1,
    )
    # 预处理器 #（skip_whitespace_and_comments）：先 while 再 continue
    content = content.replace(
        " (void)(({ int32_t __tmp = 0; if (c == 35) {   continue;\n  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {\n    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));\n  }\n } else (__tmp = 0) ; __tmp; }));\n    return l;",
        " (void)(({ int32_t __tmp = 0; if (c == 35) {\n  while ((l).pos < (data)->length && ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]) != 10) {\n    (void)((l = lexer_advance_one(l, ((l).pos < 0 || (size_t)((l).pos) >= (data)->length ? (shulang_panic_(1, 0), (data)->data[0]) : (data)->data[(l).pos]))));\n  }\n  continue;\n } else (__tmp = 0) ; __tmp; }));\n    return l;",
        1,
    )
    # skip_whitespace_and_comments_buf：// 分支，先 while 再 continue
    content = content.replace(
        "(c == 47 && (l).pos + 1 < len_u && (data)[(l).pos + 1] == 47) {   continue;\n  while ((l).pos < len_u && (data)[(l).pos] != 10) {\n    (void)((l = lexer_advance_one(l, (data)[(l).pos])));\n  }\n } else (__tmp = 0) ; __tmp; }));",
        "(c == 47 && (l).pos + 1 < len_u && (data)[(l).pos + 1] == 47) {\n  while ((l).pos < len_u && (data)[(l).pos] != 10) {\n    (void)((l = lexer_advance_one(l, (data)[(l).pos])));\n  }\n  continue;\n } else (__tmp = 0) ; __tmp; }));",
        1,
    )
    # skip_whitespace_and_comments_buf：# 分支，先 while 再 continue
    content = content.replace(
        "(void)(({ int32_t __tmp = 0; if (c == 35) {   continue;\n  while ((l).pos < len_u && (data)[(l).pos] != 10) {\n    (void)((l = lexer_advance_one(l, (data)[(l).pos])));\n  }\n } else (__tmp = 0) ; __tmp; }));\n    return l;",
        "(void)(({ int32_t __tmp = 0; if (c == 35) {\n  while ((l).pos < len_u && (data)[(l).pos] != 10) {\n    (void)((l = lexer_advance_one(l, (data)[(l).pos])));\n  }\n  continue;\n } else (__tmp = 0) ; __tmp; }));\n    return l;",
        1,
    )

    # 3. platform_elf_elf_resolve_patches: 重排 while(p) 体为 [声明+while(l)+赋值] + [原 BLOCK1 + p++]
    fn = "platform_elf_elf_resolve_patches"
    start = content.find(f"int32_t {fn}(struct platform_elf_ElfCodegenCtx * ctx)")
    if start == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (no resolve_patches reorder)", path)
        return

    # 从 while (p < (ctx)->num_patches) { 到对应的 } 的整块
    wp_start = content.find("while (p < (ctx)->num_patches) {", start)
    if wp_start == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (while p not found)", path)
        return

    body_start = content.find("\n", wp_start) + 1
    # 找 BLOCK1 的起止：从 "    (void)(({ int32_t __tmp = 0; if (target_offset < 0)" 到 "} ; __tmp; })) ; __tmp; }));"
    block1_start = content.find("    (void)(({ int32_t __tmp = 0; if (target_offset < 0)", body_start)
    if block1_start == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (block1 not found)", path)
        return

    # BLOCK1 结束于 "} ; __tmp; })) ; __tmp; }));" 后跟 "    (void)((p = p + 1));"
    block1_end_marker = "} ; __tmp; })) ; __tmp; }));"
    idx = block1_start
    depth = 0
    in_block = False
    block1_end = -1
    for i in range(len(content) - 20):
        if content[i:i+len(block1_end_marker)] == block1_end_marker:
            block1_end = i + len(block1_end_marker)
            break
    if block1_end == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (block1_end not found)", path)
        return

    # p++ 行
    p_inc = content.find("    (void)((p = p + 1));", block1_end)
    if p_inc == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (p_inc not found)", path)
        return
    after_p_inc = content.find("\n", p_inc) + 1

    # while (l < (ctx)->num_labels) { ... } 整块
    while_l_start = content.find("    while (l < (ctx)->num_labels) {", after_p_inc)
    if while_l_start == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (while_l not found)", path)
        return
    # 匹配闭合括号
    wl = while_l_start + len("    while (l < (ctx)->num_labels) {")
    depth = 1
    while_l_end = wl
    while depth and wl < len(content):
        if content[wl] == "{": depth += 1
        elif content[wl] == "}": depth -= 1
        wl += 1
    while_l_end = wl
    # next_insn delta 两行
    next_delta_start = content.find("    int32_t next_insn = rel32_offset + 4;", while_l_end)
    if next_delta_start == -1:
        with open(path, "w") as f:
            f.write(content)
        print("fix_pipeline_gen.py: applied fixes (next_insn not found)", path)
        return
    next_delta_end = content.find("\n  }", next_delta_start)  # while(p) 的闭合
    if next_delta_end == -1:
        next_delta_end = content.find("\n}", next_delta_start)
    next_delta_end = content.find("\n", next_delta_start)
    next_delta_end = content.find("\n", next_delta_end + 1)  # 两行

    before = content[:body_start]
    after_loop = content[next_delta_end + 1:]  # "  }\n  return 0;\n}"

    part1 = content[body_start:block1_start]  # rel32_offset, target_offset, l = 0
    block1_and_p = content[block1_start:after_p_inc]  # BLOCK1 + p++
    between = content[after_p_inc:while_l_start]  # 空白? 实际是 "    while (l..."
    while_l_block = content[while_l_start:while_l_end]
    next_delta = content[next_delta_start:next_delta_end + 1]

    # 在 part1 末尾加 next_insn/delta 声明；然后放 while_l_block、next_delta 赋值、再 BLOCK1 和 p++
    new_part1 = part1.rstrip()
    if "int32_t next_insn;" not in new_part1:
        new_part1 += "\n    int32_t next_insn;\n    int32_t delta;"
    new_body = (
        new_part1 + "\n"
        + while_l_block + "\n"
        + "    next_insn = rel32_offset + 4; delta = target_offset - next_insn;\n"
        + block1_and_p
    )
    content = before + new_body + after_loop

    # 4. peephole_run: line_len/next_start/remove_len 声明在 while(i) 末尾，使用在开头 → 移到 while 体开头
    if "int32_t line_end = i;" in content and "int32_t line_len = line_end - i;" in content:
        content = content.replace(
            "    (void)(({ int32_t __tmp = 0; if (line_end >= (out)->len) {   break;\n } else (__tmp = 0) ; __tmp; }));\n    (void)(({ int32_t __tmp = 0; if (line_len == 10 && next_start",
            "    (void)(({ int32_t __tmp = 0; if (line_end >= (out)->len) {   break;\n } else (__tmp = 0) ; __tmp; }));\n    int32_t line_len = line_end - i;\n    int32_t next_start = line_end + 1;\n    int32_t remove_len = 0;\n    (void)(({ int32_t __tmp = 0; if (line_len == 10 && next_start",
            1,
        )
        content = re.sub(
            r"    \(void\)\(\(line_end = line_end \+ 1\)\);\n    \}\n    int32_t line_len = line_end - i;\n    int32_t next_start = line_end \+ 1;\n    int32_t remove_len = 0;\n  \}",
            "    (void)((line_end = line_end + 1));\n    }\n  }",
            content,
            count=1,
        )

    # 5. platform_macho: ri 声明在 while(r) 体末尾 → 移到 while(r) 体开头
    if "(ri)[0]" in content and "uint8_t ri[8]" in content:
        content = re.sub(
            r"(  while \(r < \(ctx\)->num_relocs\) \{\s*\n)(    int32_t sym_idx = 0;\s*\n    int32_t m = 0;\s*\n\s*\(void\)\(\(\(ri\))",
            r"\1    uint8_t ri[8] = {0};\n\2",
            content,
            count=1,
        )
        # 删除 while(r) 体末尾重复的 ri 声明（保留开头已插入的）
        content = re.sub(
            r"\n    uint8_t ri\[8\] = \{ 0 \};\n  \}\n  \(void\)\(\(\(out\)->len = 0\)\);",
            "\n  }\n  (void)(((out)->len = 0));",
            content,
            count=1,
        )

    # 6. platform_coff: rel 声明在 while(r) 体末尾 → 移到 while(r) 体开头
    if "(rel)[0]" in content and "uint8_t rel[10]" in content:
        content = re.sub(
            r"(  while \(r < num_relocs\) \{\s*\n)(    int32_t sym_idx = 0;\s*\n    int32_t m = 0;\s*\n\s*\(void\)\(\(\(rel\))",
            r"\1    uint8_t rel[10] = {0};\n\2",
            content,
            count=1,
        )
        content = re.sub(
            r"\n    uint8_t rel\[10\] = \{ 0 \};\n  \}\n  while \(s < num_syms\)",
            "\n  }\n  while (s < num_syms)",
            content,
            count=1,
        )

    # 7. 诊断已关闭：不再注入 pipeline impl/typeck/codegen 的 stderr 调试输出

    with open(path, "w") as f:
        f.write(content)
    print("fix_pipeline_gen.py: applied fixes to", path)

if __name__ == "__main__":
    main()
