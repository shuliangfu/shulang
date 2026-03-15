/**
 * std/unicode/unicode.c — Unicode 分类、大小写、空白、ASCII（P4 可选；对标 Zig std.unicode、Rust char）
 *
 * 【文件职责】category、to_lower/to_upper、is_whitespace、is_ascii；ASCII 用表驱动，非 ASCII 占位/恒等。
 * 【所属模块/组件】标准库 std.unicode；依赖 std.encoding；与 std/unicode/mod.su 同属一模块。
 */

#include <stdint.h>
#include <ctype.h>

/* ASCII 分类表：0 未知，1 Letter，2 Number，3 Whitespace；一次查表避免分支 */
#define U_CAT_LETTER    1
#define U_CAT_NUMBER    2
#define U_CAT_WHITESPACE 3
static const uint8_t ascii_category_table[128] = {
  [0 ... 8] = 0,
  [9] = U_CAT_WHITESPACE,   /* \\t */
  [10 ... 13] = U_CAT_WHITESPACE, /* \\n \\v \\f \\r */
  [14 ... 31] = 0,
  [32] = U_CAT_WHITESPACE,  /* space */
  [33 ... 47] = 0,
  ['0'] = U_CAT_NUMBER,
  ['1'] = U_CAT_NUMBER,
  ['2'] = U_CAT_NUMBER,
  ['3'] = U_CAT_NUMBER,
  ['4'] = U_CAT_NUMBER,
  ['5'] = U_CAT_NUMBER,
  ['6'] = U_CAT_NUMBER,
  ['7'] = U_CAT_NUMBER,
  ['8'] = U_CAT_NUMBER,
  ['9'] = U_CAT_NUMBER,
  [58 ... 64] = 0,
  ['A'] = U_CAT_LETTER,
  ['B'] = U_CAT_LETTER,
  ['C'] = U_CAT_LETTER,
  ['D'] = U_CAT_LETTER,
  ['E'] = U_CAT_LETTER,
  ['F'] = U_CAT_LETTER,
  ['G'] = U_CAT_LETTER,
  ['H'] = U_CAT_LETTER,
  ['I'] = U_CAT_LETTER,
  ['J'] = U_CAT_LETTER,
  ['K'] = U_CAT_LETTER,
  ['L'] = U_CAT_LETTER,
  ['M'] = U_CAT_LETTER,
  ['N'] = U_CAT_LETTER,
  ['O'] = U_CAT_LETTER,
  ['P'] = U_CAT_LETTER,
  ['Q'] = U_CAT_LETTER,
  ['R'] = U_CAT_LETTER,
  ['S'] = U_CAT_LETTER,
  ['T'] = U_CAT_LETTER,
  ['U'] = U_CAT_LETTER,
  ['V'] = U_CAT_LETTER,
  ['W'] = U_CAT_LETTER,
  ['X'] = U_CAT_LETTER,
  ['Y'] = U_CAT_LETTER,
  ['Z'] = U_CAT_LETTER,
  [91 ... 96] = 0,
  ['a'] = U_CAT_LETTER,
  ['b'] = U_CAT_LETTER,
  ['c'] = U_CAT_LETTER,
  ['d'] = U_CAT_LETTER,
  ['e'] = U_CAT_LETTER,
  ['f'] = U_CAT_LETTER,
  ['g'] = U_CAT_LETTER,
  ['h'] = U_CAT_LETTER,
  ['i'] = U_CAT_LETTER,
  ['j'] = U_CAT_LETTER,
  ['k'] = U_CAT_LETTER,
  ['l'] = U_CAT_LETTER,
  ['m'] = U_CAT_LETTER,
  ['n'] = U_CAT_LETTER,
  ['o'] = U_CAT_LETTER,
  ['p'] = U_CAT_LETTER,
  ['q'] = U_CAT_LETTER,
  ['r'] = U_CAT_LETTER,
  ['s'] = U_CAT_LETTER,
  ['t'] = U_CAT_LETTER,
  ['u'] = U_CAT_LETTER,
  ['v'] = U_CAT_LETTER,
  ['w'] = U_CAT_LETTER,
  ['x'] = U_CAT_LETTER,
  ['y'] = U_CAT_LETTER,
  ['z'] = U_CAT_LETTER,
  [123 ... 127] = 0,
};

/** Unicode 分类（简化）：0 未知，1 Letter，2 Number，3 Whitespace。ASCII 查表，非 ASCII 返回 0。 */
int32_t unicode_category_c(uint32_t rune) {
  if (rune < 128u) return (int32_t)ascii_category_table[rune];
  return 0;
}

/** 是否为空白（\\t \\n \\v \\f \\r 空格）。对标 Zig unicode.isWhitespace、Rust char::is_whitespace。 */
int32_t unicode_is_whitespace_c(uint32_t rune) {
  if (rune < 128u) return ascii_category_table[rune] == U_CAT_WHITESPACE ? 1 : 0;
  return 0;
}

/** 是否为 ASCII（rune <= 127）。对标 Rust char::is_ascii。 */
int32_t unicode_is_ascii_c(uint32_t rune) {
  return rune <= 127u ? 1 : 0;
}

/** rune 转小写；非 ASCII 暂返回原 rune。 */
uint32_t unicode_to_lower_c(uint32_t rune) {
  if (rune <= 127u) return (uint32_t)(unsigned char)tolower((int)(rune & 0xff));
  return rune;
}

/** rune 转大写；非 ASCII 暂返回原 rune。 */
uint32_t unicode_to_upper_c(uint32_t rune) {
  if (rune <= 127u) return (uint32_t)(unsigned char)toupper((int)(rune & 0xff));
  return rune;
}
