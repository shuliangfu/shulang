#!/usr/bin/env perl
# 【已废弃，构建未调用】原兜底脚本：将 "int __tmp = 0; ... } else (__tmp = (struct X){0})" 改为 "struct X __tmp = (struct X){0}; ..."
# 当前构建无补丁，if-expr __tmp 类型由 codegen/typeck 从根源产出，本脚本仅保留作历史参考。
use strict;
use warnings;
my $f = $ARGV[0];
open my $fh, '<', $f or die $!;
my @lines = <$fh>;
close $fh;
# 从文件末尾向前处理：这样先处理嵌套的 "} else (struct X){0}" 会先改掉更外层的 __tmp，内层再处理时该行已是 struct 不再匹配，避免把内层 if 的 __tmp 改成 struct
# 规则：从本行向上回溯时，仅当“先遇到 } else、再遇到声明”时才替换（即用更外层的声明）
for (my $i = $#lines; $i >= 0; $i--) {
    next unless $lines[$i] =~ m/\} else \(__tmp = \(struct (ast_\w+)\)\{0\}\)/;
    my $st = $1;
    my $seen_else = 0;
    for (my $j = $i - 1; $j >= 0; $j--) {
        $seen_else = 1 if $lines[$j] =~ m/\} else/;
        if ($lines[$j] =~ m/(\s)(int32_t|int)(\s+__tmp = 0;)/) {
            if ($seen_else) {
                $lines[$j] =~ s/(\s)(int32_t|int)(\s+__tmp = 0;)/$1struct $st$3/;
                $lines[$j] =~ s/__tmp = 0;/__tmp = (struct $st){0};/;
                last;
            }
        }
    }
}
open $fh, '>', $f or die $!;
print $fh $_ for @lines;
close $fh;
