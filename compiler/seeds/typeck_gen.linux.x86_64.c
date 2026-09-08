/* wave322 typeck M4 cold assemble from .x (7.4.1):
 *   base = tip xlang -E src/typeck/typeck.x
 *   module-prefix rename: bare export faces → typeck_*
 *   layer-3 short-face #defines = seeds/typeck_short_face_alias.from_x.c (inject early)
 *   layer-1 Cap residual append = seeds/typeck_cap_residual.from_x.c
 *   layer-2 mangle alias append = seeds/typeck_mangle_link_alias.from_x.c
 * G.7: product authority = typeck.x + companions; pin seed archaeology only.
 * PLATFORM: SHARED freestanding typeck cold assemble.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#ifndef XLANG_DYN_OBJ
#define XLANG_DYN_OBJ

/* seeds/typeck_short_face_alias.from_x.c — wave317 typeck M4 layer-3 (partial)
 * Bare ast_block_* / ast_expr_* / ast_arena_* short names → ast_ast_* product faces.
 * Tip typeck.x -E emits bare calls; product/pool export ast_ast_* (and pipeline_*).
 * G.7: define-only aliases (zero bodies). Inject early in typeck_gen (before bodies).
 * PLATFORM: SHARED freestanding typeck tip re-pin companion.
 * MUST stay outside #if defined(__APPLE__) when merged into typeck_gen pin:
 * Linux cold Track-L otherwise leaves U bare ast_block_* → phase1 pure-ld UNDEF.
 */
#ifndef XLANG_TYPECK_SHORT_FACE_ALIAS_H
#define XLANG_TYPECK_SHORT_FACE_ALIAS_H
#define ast_block_final_expr_ref ast_ast_block_final_expr_ref
#define ast_block_num_consts ast_ast_block_num_consts
#define ast_block_num_lets ast_ast_block_num_lets
#define ast_block_num_loops ast_ast_block_num_loops
#define ast_block_num_for_loops ast_ast_block_num_for_loops
#define ast_block_num_if_stmts ast_ast_block_num_if_stmts
#define ast_block_num_regions ast_ast_block_num_regions
#define ast_block_num_labeled_stmts ast_ast_block_num_labeled_stmts
#define ast_block_region_body_ref ast_ast_block_region_body_ref
#define ast_block_num_expr_stmts ast_ast_block_num_expr_stmts
#define ast_block_num_stmt_order ast_ast_block_num_stmt_order
#define ast_block_stmt_order_kind ast_ast_block_stmt_order_kind
#define ast_block_stmt_order_idx ast_ast_block_stmt_order_idx
#define ast_block_const_init_ref ast_ast_block_const_init_ref
#define ast_block_const_type_ref ast_ast_block_const_type_ref
#define ast_block_let_init_ref ast_ast_block_let_init_ref
#define ast_block_let_type_ref ast_ast_block_let_type_ref
#define ast_block_expr_stmt_ref ast_ast_block_expr_stmt_ref
#define ast_block_while_cond_ref ast_ast_block_while_cond_ref
#define ast_block_while_body_ref ast_ast_block_while_body_ref
#define ast_block_for_init_ref ast_ast_block_for_init_ref
#define ast_block_for_cond_ref ast_ast_block_for_cond_ref
#define ast_block_for_step_ref ast_ast_block_for_step_ref
#define ast_block_for_body_ref ast_ast_block_for_body_ref
#define ast_block_if_cond_ref ast_ast_block_if_cond_ref
#define ast_block_if_then_body_ref ast_ast_block_if_then_body_ref
#define ast_block_if_else_body_ref ast_ast_block_if_else_body_ref
#define ast_block_resolve_var_to_type_ref ast_ast_block_resolve_var_to_type_ref
#define ast_expr_apply_call_resolve ast_ast_expr_apply_call_resolve
#define ast_expr_disallows_implicit_tail ast_ast_expr_disallows_implicit_tail
#define ast_expr_layout_prime_call_resolved ast_ast_expr_layout_prime_call_resolved
#define ast_arena_init ast_ast_arena_init
#define ast_arena_type_alloc ast_ast_arena_type_alloc
#define ast_arena_expr_alloc ast_ast_arena_expr_alloc
#define ast_arena_block_alloc ast_ast_arena_block_alloc
#define ast_arena_type_get ast_ast_arena_type_get
#define ast_arena_type_set ast_ast_arena_type_set
#define ast_arena_expr_get ast_ast_arena_expr_get
#define ast_arena_expr_set ast_ast_arena_expr_set
#define ast_arena_block_get ast_ast_arena_block_get
#define ast_arena_block_set ast_ast_arena_block_set
#define ast_arena_func_alloc ast_ast_arena_func_alloc
#define ast_arena_func_get ast_ast_arena_func_get
#define ast_arena_func_set ast_ast_arena_func_set
#define ast_arena_patch_block_parent_links ast_ast_arena_patch_block_parent_links
#endif /* XLANG_TYPECK_SHORT_FACE_ALIAS_H */

struct xlang_dyn_obj { void *data; void *vtable; };
#endif
#ifndef XLANG_SLICE_LAYOUTS
#define XLANG_SLICE_LAYOUTS
struct xlang_slice_uint8_t { uint8_t *data; size_t length; };
struct xlang_slice_int8_t { int8_t *data; size_t length; };
struct xlang_slice_int16_t { int16_t *data; size_t length; };
struct xlang_slice_uint16_t { uint16_t *data; size_t length; };
struct xlang_slice_int { int *data; size_t length; };
struct xlang_slice_int32_t { int32_t *data; size_t length; };
struct xlang_slice_uint32_t { uint32_t *data; size_t length; };
struct xlang_slice_int64_t { int64_t *data; size_t length; };
struct xlang_slice_uint64_t { uint64_t *data; size_t length; };
struct xlang_slice_size_t { size_t *data; size_t length; };
struct xlang_slice_ssize_t { ssize_t *data; size_t length; };
struct xlang_slice_float { float *data; size_t length; };
struct xlang_slice_double { double *data; size_t length; };
struct xlang_slice_xlang_slice_uint8_t { struct xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_int8_t { struct xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_int16_t { struct xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_uint16_t { struct xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_int { struct xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_int32_t { struct xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_uint32_t { struct xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_int64_t { struct xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_uint64_t { struct xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_size_t { struct xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_ssize_t { struct xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_float { struct xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_double { struct xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int8_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint16_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint32_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_int64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_uint64_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_size_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ssize_t *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_float *data; size_t length; };
struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_double *data; size_t length; };
#endif
enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID, ast_TypeKind_TYPE_DYN, ast_TypeKind_TYPE_FN };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE, ast_ExprKind_EXPR_STRING_LIT };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type {
  int32_t kind;
  uint8_t name[128];
  int32_t name_len;
  int32_t elem_type_ref;
  int32_t array_size;
  uint8_t region_label[128];
  int32_t region_label_len;
};

struct xlang_slice_ast_Type { struct ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Type { struct xlang_slice_ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Type { struct xlang_slice_xlang_slice_ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type { struct xlang_slice_xlang_slice_xlang_slice_ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Type *data; size_t length; };

struct ast_Expr {
  int32_t kind;
  int32_t resolved_type_ref;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t var_name[128];
  int32_t var_name_len;
  int32_t binop_left_ref;
  int32_t binop_right_ref;
  int32_t unary_operand_ref;
  int32_t if_cond_ref;
  int32_t if_then_ref;
  int32_t if_else_ref;
  int32_t block_ref;
  int32_t match_matched_ref;
  int32_t match_arm_base;
  int32_t match_num_arms;
  int32_t field_access_base_ref;
  uint8_t field_access_field_name[128];
  int32_t field_access_field_len;
  int32_t field_access_is_enum_variant;
  int32_t field_access_offset;
  int32_t field_access_soa_stride;
  int32_t index_base_ref;
  int32_t index_index_ref;
  int32_t index_base_is_slice;
  int32_t call_callee_ref;
  int32_t call_arg_base;
  int32_t call_num_args;
  int32_t call_num_type_args;
  int32_t method_call_base_ref;
  uint8_t method_call_name[128];
  int32_t method_call_name_len;
  int32_t method_call_arg_base;
  int32_t method_call_num_args;
  int32_t const_folded_val;
  int32_t const_folded_valid;
  int32_t index_proven_in_bounds;
  uint8_t struct_lit_struct_name[128];
  int32_t struct_lit_struct_name_len;
  int32_t struct_lit_field_base;
  int32_t struct_lit_num_fields;
  int32_t array_lit_elem_base;
  int32_t array_lit_num_elems;
  int32_t float_bits_lo;
  int32_t float_bits_hi;
  int32_t enum_variant_tag;
  int32_t as_operand_ref;
  int32_t as_target_type_ref;
  int32_t call_resolved_func_index;
  int32_t call_resolved_dep_index;
};

struct xlang_slice_ast_Expr { struct ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_xlang_slice_ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_xlang_slice_xlang_slice_ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Expr *data; size_t length; };

struct ast_ConstDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct xlang_slice_ast_ConstDecl { struct ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_xlang_slice_ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ConstDecl *data; size_t length; };

struct ast_LetDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct xlang_slice_ast_LetDecl { struct ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_xlang_slice_ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_xlang_slice_xlang_slice_ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LetDecl *data; size_t length; };

struct ast_WhileLoop {
  int32_t cond_ref;
  int32_t body_ref;
};

struct xlang_slice_ast_WhileLoop { struct ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_xlang_slice_ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_WhileLoop *data; size_t length; };

struct ast_ForLoop {
  int32_t init_ref;
  int32_t cond_ref;
  int32_t step_ref;
  int32_t body_ref;
};

struct xlang_slice_ast_ForLoop { struct ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_xlang_slice_ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_xlang_slice_xlang_slice_ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ForLoop *data; size_t length; };

struct ast_IfStmt {
  int32_t cond_ref;
  int32_t then_body_ref;
  int32_t else_body_ref;
};

struct xlang_slice_ast_IfStmt { struct ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_xlang_slice_ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_xlang_slice_xlang_slice_ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_IfStmt *data; size_t length; };

struct ast_StmtOrderItem {
  uint8_t kind;
  int32_t idx;
};

struct xlang_slice_ast_StmtOrderItem { struct ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StmtOrderItem *data; size_t length; };

struct ast_LabeledStmt {
  uint8_t label[128];
  int32_t label_len;
  int32_t is_goto;
  uint8_t goto_target[128];
  int32_t goto_target_len;
  int32_t return_expr_ref;
};

struct xlang_slice_ast_LabeledStmt { struct ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_xlang_slice_ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_LabeledStmt *data; size_t length; };

struct ast_Block {
  int32_t const_base;
  int32_t num_consts;
  int32_t let_base;
  int32_t num_lets;
  int32_t num_early_lets;
  int32_t loop_base;
  int32_t num_loops;
  int32_t for_loop_base;
  int32_t num_for_loops;
  int32_t if_base;
  int32_t num_if_stmts;
  int32_t region_base;
  int32_t num_regions;
  int32_t defer_base;
  int32_t num_defers;
  int32_t labeled_base;
  int32_t num_labeled_stmts;
  int32_t expr_stmt_base;
  int32_t num_expr_stmts;
  int32_t final_expr_ref;
  int32_t stmt_order_base;
  int32_t num_stmt_order;
  int32_t parent_block_ref;
};

struct xlang_slice_ast_Block { struct ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Block { struct xlang_slice_ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Block { struct xlang_slice_xlang_slice_ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block { struct xlang_slice_xlang_slice_xlang_slice_ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Block *data; size_t length; };

struct ast_Param {
  uint8_t name[32];
  int32_t name_len;
  int32_t type_ref;
};

struct xlang_slice_ast_Param { struct ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Param { struct xlang_slice_ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Param { struct xlang_slice_xlang_slice_ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param { struct xlang_slice_xlang_slice_xlang_slice_ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Param *data; size_t length; };

struct ast_Func {
  uint8_t name[128];
  int32_t name_len;
  int32_t param_base;
  int32_t num_params;
  int32_t num_generic_params;
  int32_t return_type_ref;
  int32_t body_ref;
  int32_t body_expr_ref;
  int32_t is_extern;
  int32_t is_async;
  int32_t is_used;
  int32_t is_naked;
  int32_t is_entry;
  int32_t is_no_mangle;
  int32_t is_interrupt;
  int32_t abi_kind;
  int32_t is_variadic;
  int32_t is_export;
};

struct xlang_slice_ast_Func { struct ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Func { struct xlang_slice_ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Func { struct xlang_slice_xlang_slice_ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func { struct xlang_slice_xlang_slice_xlang_slice_ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Func *data; size_t length; };

struct ast_StructLayout {
  uint8_t name[128];
  int32_t name_len;
  int32_t field_base;
  int32_t num_fields;
  int32_t allow_padding;
  int32_t soa;
  int32_t packed;
  int32_t repr_compatible;
  int32_t is_export;
};

struct xlang_slice_ast_StructLayout { struct ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_xlang_slice_ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_xlang_slice_xlang_slice_ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_StructLayout *data; size_t length; };

struct ast_Module {
  int32_t num_funcs;
  int32_t main_func_index;
  int32_t num_imports;
  int32_t num_top_level_lets;
  int32_t num_struct_layouts;
  int32_t pending_allow_padding;
  int32_t pending_soa_struct;
  int32_t pending_cfg_skip;
  int32_t pending_repr_c_struct;
  int32_t pending_repr_compatible_struct;
  int32_t pending_used;
  int32_t pending_naked;
  int32_t pending_entry;
  int32_t pending_no_mangle;
  int32_t pending_interrupt;
  int32_t pending_export;
  int32_t num_module_enums;
};

struct xlang_slice_ast_Module { struct ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_ast_Module { struct xlang_slice_ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_Module { struct xlang_slice_xlang_slice_ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module { struct xlang_slice_xlang_slice_xlang_slice_ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_Module *data; size_t length; };

struct ast_ASTArena {
  int32_t num_types;
  int32_t num_exprs;
  int32_t num_blocks;
  int32_t num_funcs;
};

/* pipeline call aliases (ast_pipeline_* extern, pipeline_* call) */
#define pipeline_block_expr_stmt_ref ast_pipeline_block_expr_stmt_ref
#define ast_arena_init ast_ast_arena_init
#define ast_arena_type_alloc ast_ast_arena_type_alloc
#define ast_arena_expr_alloc ast_ast_arena_expr_alloc
#define ast_arena_block_alloc ast_ast_arena_block_alloc
#define ast_arena_type_get ast_ast_arena_type_get
#define ast_arena_type_set ast_ast_arena_type_set
#define ast_arena_expr_get ast_ast_arena_expr_get
#define ast_arena_expr_set ast_ast_arena_expr_set
#define ast_arena_block_get ast_ast_arena_block_get
#define ast_arena_patch_block_parent_links ast_ast_arena_patch_block_parent_links
#define ast_arena_block_set ast_ast_arena_block_set
#define ast_arena_func_alloc ast_ast_arena_func_alloc
#define ast_arena_func_get ast_ast_arena_func_get
#define ast_arena_func_set ast_ast_arena_func_set
#define typeck_typeck_type_kind_ordinal typeck_type_kind_ordinal
#define typeck_typeck_name_equal typeck_name_equal
#define typeck_typeck_resolve_type_alias_ref_local typeck_resolve_type_alias_ref_local
#define typeck_typeck_resolve_type_alias_ref typeck_resolve_type_alias_ref
#define typeck_typeck_canonicalize_named_inst_if_present typeck_canonicalize_named_inst_if_present
#define typeck_typeck_named_type_matches_name_or_alias typeck_named_type_matches_name_or_alias
#define typeck_typeck_layout_name_equal typeck_layout_name_equal
#define typeck_typeck_layout_field_name_equal typeck_layout_field_name_equal
#define typeck_typeck_layout_name_into typeck_layout_name_into
#define typeck_typeck_layout_field_name_into typeck_layout_field_name_into
#define typeck_typeck_import_path_slice_equal typeck_import_path_slice_equal
#define typeck_typeck_import_binding_name_equal typeck_import_binding_name_equal
#define typeck_typeck_module_num_imports typeck_module_num_imports
#define typeck_typeck_var_is_import_visible_name typeck_var_is_import_visible_name
#define typeck_typeck_import_select_name_equal typeck_import_select_name_equal
#define typeck_typeck_top_level_let_name_equal typeck_top_level_let_name_equal
#define typeck_typeck_dep_module_const_idx_named typeck_dep_module_const_idx_named
#define typeck_typeck_find_import_const_dep_index typeck_find_import_const_dep_index
#define typeck_typeck_import_last_segment_into typeck_import_last_segment_into
#define typeck_typeck_resolve_dep_index_for_import typeck_resolve_dep_index_for_import
#define typeck_typeck_import_const_binding_hint_at typeck_import_const_binding_hint_at
#define typeck_typeck_reject_bare_import_const typeck_reject_bare_import_const
#define typeck_typeck_find_layout_idx_by_type_name typeck_find_layout_idx_by_type_name
#define typeck_typeck_x_named_builtin_align typeck_x_named_builtin_align
#define typeck_typeck_x_named_builtin_size typeck_x_named_builtin_size
#define typeck_typeck_x_type_align typeck_x_type_align
#define typeck_typeck_type_is_empty_struct typeck_type_is_empty_struct
#define typeck_typeck_x_type_size typeck_x_type_size
#define typeck_typeck_soa_find_layout_idx_by_name typeck_soa_find_layout_idx_by_name
#define typeck_typeck_soa_find_layout_module_and_idx typeck_soa_find_layout_module_and_idx
#define typeck_typeck_soa_col_base_for_field typeck_soa_col_base_for_field
#define typeck_typeck_soa_field_soa_index typeck_soa_field_soa_index
#define typeck_typeck_soa_array_storage_size_glue typeck_soa_array_storage_size_glue
#define typeck_typeck_struct_layout_metrics typeck_struct_layout_metrics
#define typeck_typeck_validate_struct_layouts_zero_padding typeck_validate_struct_layouts_zero_padding
#define typeck_typeck_get_field_offset_from_layout typeck_get_field_offset_from_layout
#define typeck_typeck_get_field_type_ref_from_layout typeck_get_field_type_ref_from_layout
#define typeck_typeck_get_field_offset_from_layout_deps typeck_get_field_offset_from_layout_deps
#define typeck_typeck_ensure_struct_layout_from_struct_lit typeck_ensure_struct_layout_from_struct_lit
#define typeck_typeck_field_known_ptr typeck_field_known_ptr
#define typeck_typeck_dep_top_level_const_match typeck_dep_top_level_const_match
#define typeck_typeck_field_import_try_dep_enum_type typeck_field_import_try_dep_enum_type
#define typeck_typeck_field_import_binding typeck_field_import_binding
#define typeck_typeck_field_import_const_is_const typeck_field_import_const_is_const
#define typeck_typeck_field_reverse_infer_base_type typeck_field_reverse_infer_base_type
#define typeck_typeck_named_last_segment_off typeck_named_last_segment_off
#define typeck_typeck_named_spelling_eq typeck_named_spelling_eq
#define typeck_typeck_named_is_module_concrete typeck_named_is_module_concrete
#define typeck_typeck_mono_field_type_from_base typeck_mono_field_type_from_base
#define typeck_typeck_field_unknown_hard_fail typeck_field_unknown_hard_fail
#define typeck_typeck_field_layout_named typeck_field_layout_named
#define typeck_typeck_expr_var_name_equal_func typeck_expr_var_name_equal_func
#define typeck_typeck_find_or_alloc_named_type_ref typeck_find_or_alloc_named_type_ref
#define typeck_typeck_field_access_lexer_wrapper_fallback typeck_field_access_lexer_wrapper_fallback
#define typeck_typeck_ensure_primitive_by_kind_ord typeck_ensure_primitive_by_kind_ord
#define typeck_typeck_ensure_i32_type_ref typeck_ensure_i32_type_ref
#define typeck_typeck_ensure_u8_type_ref typeck_ensure_u8_type_ref
#define typeck_typeck_ensure_bool_type_ref typeck_ensure_bool_type_ref
#define typeck_typeck_ensure_f32_type_ref typeck_ensure_f32_type_ref
#define typeck_typeck_ensure_f64_type_ref typeck_ensure_f64_type_ref
#define typeck_typeck_ensure_usize_type_ref typeck_ensure_usize_type_ref
#define typeck_typeck_ensure_void_type_ref typeck_ensure_void_type_ref
#define typeck_typeck_map_import_binding_named_to_caller typeck_map_import_binding_named_to_caller
#define typeck_typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32 typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32
#define typeck_typeck_ensure_i64_type_ref typeck_ensure_i64_type_ref
#define typeck_typeck_find_or_alloc_compound_type_ref typeck_find_or_alloc_compound_type_ref
#define typeck_typeck_find_or_alloc_array_type_ref typeck_find_or_alloc_array_type_ref
#define typeck_typeck_ensure_array_type_ref_named_elem typeck_ensure_array_type_ref_named_elem
#define typeck_typeck_ensure_kind_only_type_ref typeck_ensure_kind_only_type_ref
#define typeck_typeck_find_or_alloc_ptr_type_ref typeck_find_or_alloc_ptr_type_ref
#define typeck_typeck_find_or_alloc_slice_type_ref typeck_find_or_alloc_slice_type_ref
#define typeck_typeck_find_or_alloc_linear_type_ref typeck_find_or_alloc_linear_type_ref
#define typeck_typeck_find_or_alloc_vector_type_ref typeck_find_or_alloc_vector_type_ref
#define typeck_typeck_dep_return_type_to_caller_arena typeck_dep_return_type_to_caller_arena
#define typeck_typeck_expr_field_access_fallback_scalar_type_ref typeck_expr_field_access_fallback_scalar_type_ref
#define typeck_typeck_get_field_type_ref_from_layout_deps typeck_get_field_type_ref_from_layout_deps
#define typeck_typeck_inline_u8_64_array_field_type_ref typeck_inline_u8_64_array_field_type_ref
#define typeck_typeck_expr_inline_array_field_type_ref typeck_expr_inline_array_field_type_ref
#define typeck_typeck_entry_module_find_struct_layout_index typeck_entry_module_find_struct_layout_index
#define typeck_typeck_resolve_scan_dep_with_apply typeck_resolve_scan_dep_with_apply
#define typeck_typeck_find_func_return_type_in_module typeck_find_func_return_type_in_module
#define typeck_typeck_find_func_return_type_in_module_by_name typeck_find_func_return_type_in_module_by_name
#define typeck_typeck_overload_arg_param_score typeck_overload_arg_param_score
#define typeck_typeck_find_func_return_type_in_module_by_name_overload typeck_find_func_return_type_in_module_by_name_overload
#define typeck_typeck_find_func_return_type_in_module_overload typeck_find_func_return_type_in_module_overload
#define typeck_typeck_import_path_segment_count typeck_import_path_segment_count
#define typeck_typeck_import_segment_at typeck_import_segment_at
#define typeck_typeck_resolve_whole_import_qualified_call_return_type typeck_resolve_whole_import_qualified_call_return_type
#define typeck_typeck_resolve_call_binding_import_return_type typeck_resolve_call_binding_import_return_type
#define typeck_typeck_resolve_method_call_binding_import_return_type typeck_resolve_method_call_binding_import_return_type
#define typeck_typeck_resolve_call_select_import_return_type typeck_resolve_call_select_import_return_type
#define typeck_typeck_resolve_call_callee_try_whole_import typeck_resolve_call_callee_try_whole_import
#define typeck_typeck_resolve_call_callee_try_binding_import typeck_resolve_call_callee_try_binding_import
#define typeck_typeck_resolve_call_callee_local_module typeck_resolve_call_callee_local_module
#define typeck_typeck_resolve_call_callee_scan_dep typeck_resolve_call_callee_scan_dep
#define typeck_typeck_resolve_call_callee_return_type typeck_resolve_call_callee_return_type
#define typeck_typeck_expr_type_ref typeck_expr_type_ref
#define typeck_typeck_type_ref_is_bool_impl typeck_type_ref_is_bool_impl
#define typeck_typeck_type_ref_is_bool typeck_type_ref_is_bool
#define typeck_typeck_named_unqual_start typeck_named_unqual_start
#define typeck_typeck_type_ref_mangle_suffix typeck_type_ref_mangle_suffix
#define typeck_typeck_named_inst_mangle_into typeck_named_inst_mangle_into
#define typeck_typeck_type_refs_equal_named typeck_type_refs_equal_named
#define typeck_typeck_type_refs_equal_same_kind typeck_type_refs_equal_same_kind
#define typeck_typeck_type_refs_equal_impl typeck_type_refs_equal_impl
#define typeck_typeck_type_refs_equal typeck_type_refs_equal
#define typeck_typeck_integer_widen_ok typeck_integer_widen_ok
#define typeck_typeck_int_family_id typeck_int_family_id
#define typeck_typeck_integer_widen_ok_refs typeck_integer_widen_ok_refs
#define typeck_typeck_float_widen_ok typeck_float_widen_ok
#define typeck_typeck_dyn_rhs_is_null_sentinel typeck_dyn_rhs_is_null_sentinel
#define typeck_typeck_array_to_slice_ok typeck_array_to_slice_ok
#define typeck_typeck_return_operand_matches typeck_return_operand_matches
#define typeck_typeck_expr_is_null_keyword typeck_expr_is_null_keyword
#define typeck_typeck_coerce_init_lit_to_decl typeck_coerce_init_lit_to_decl
#define typeck_typeck_coerce_init_float_lit_to_decl typeck_coerce_init_float_lit_to_decl
#define typeck_typeck_coerce_init_enum_field_to_decl typeck_coerce_init_enum_field_to_decl
#define typeck_typeck_coerce_init_named_call_to_decl typeck_coerce_init_named_call_to_decl
#define typeck_typeck_coerce_init_resolved_alias_to_decl typeck_coerce_init_resolved_alias_to_decl
#define typeck_typeck_coerce_array_lit_elem_types_to_decl typeck_coerce_array_lit_elem_types_to_decl
#define typeck_typeck_vector_lanes_of_type typeck_vector_lanes_of_type
#define typeck_typeck_coerce_init_array_vector_lit_to_decl typeck_coerce_init_array_vector_lit_to_decl
#define typeck_typeck_coerce_init_vector_binop_to_decl typeck_coerce_init_vector_binop_to_decl
#define typeck_typeck_coerce_init_int_binop_to_decl typeck_coerce_init_int_binop_to_decl
#define typeck_typeck_coerce_init_bool_to_int_decl typeck_coerce_init_bool_to_int_decl
#define typeck_typeck_coerce_init_array_lit_to_len_int_decl typeck_coerce_init_array_lit_to_len_int_decl
#define typeck_typeck_coerce_init_slice_from_array typeck_coerce_init_slice_from_array
#define typeck_typeck_coerce_array_lit_struct_elems_to_decl typeck_coerce_array_lit_struct_elems_to_decl
#define typeck_typeck_coerce_init_expr_to_decl typeck_coerce_init_expr_to_decl
#define typeck_typeck_coerce_init_struct_lit_to_decl typeck_coerce_init_struct_lit_to_decl
#define typeck_typeck_diag_append_lit typeck_diag_append_lit
#define typeck_typeck_diag_append_u32_dec typeck_diag_append_u32_dec
#define typeck_typeck_diag_fmt_type_at typeck_diag_fmt_type_at
#define typeck_typeck_diag_fmt_type_into typeck_diag_fmt_type_into
#define typeck_typeck_diag_fmt_type_or_question typeck_diag_fmt_type_or_question
#define typeck_typeck_return_breadcrumb_into typeck_return_breadcrumb_into
#define typeck_typeck_check_expr_float_lit typeck_check_expr_float_lit
#define typeck_typeck_check_expr_int_lit typeck_check_expr_int_lit
#define typeck_typeck_check_expr_bool_lit typeck_check_expr_bool_lit
#define typeck_typeck_check_expr_string_lit typeck_check_expr_string_lit
#define typeck_typeck_check_expr_break_continue typeck_check_expr_break_continue
#define typeck_typeck_check_expr_enum_variant typeck_check_expr_enum_variant
#define typeck_typeck_check_expr_if_ternary typeck_check_expr_if_ternary
#define typeck_typeck_block_expr_value_ref typeck_block_expr_value_ref
#define typeck_typeck_check_expr_block typeck_check_expr_block
#define typeck_typeck_check_expr_assign typeck_check_expr_assign
#define typeck_typeck_check_expr_return typeck_check_expr_return
#define typeck_typeck_check_expr_panic typeck_check_expr_panic
#define typeck_typeck_check_expr_match_arm typeck_check_expr_match_arm
#define typeck_typeck_check_expr_match typeck_check_expr_match
#define typeck_typeck_check_expr_try_propagate typeck_check_expr_try_propagate
#define typeck_typeck_check_expr_call_arg typeck_check_expr_call_arg
#define typeck_typeck_check_expr_call_resolve typeck_check_expr_call_resolve
#define typeck_typeck_call_arity_compatible typeck_call_arity_compatible
#define typeck_typeck_check_call_arity typeck_check_call_arity
#define typeck_typeck_named_is_module_type typeck_named_is_module_type
#define typeck_typeck_type_is_free_type_param typeck_type_is_free_type_param
#define typeck_typeck_type_tree_has_free_type_param typeck_type_tree_has_free_type_param
#define typeck_typeck_generic_formal_matches_arg_type typeck_generic_formal_matches_arg_type
#define typeck_typeck_call_is_fmt_debug_print_any typeck_call_is_fmt_debug_print_any
#define typeck_typeck_check_call_arg_types typeck_check_call_arg_types
#define typeck_typeck_match_subject_field_type typeck_match_subject_field_type
#define typeck_typeck_call_arg_repr_compatible_ok typeck_call_arg_repr_compatible_ok
#define typeck_typeck_is_cap_va_builtin_name typeck_is_cap_va_builtin_name
#define typeck_typeck_check_extern_call_unsafe_boundary typeck_check_extern_call_unsafe_boundary
#define typeck_typeck_slice_region_escape typeck_slice_region_escape
#define typeck_typeck_slice_region_conflict typeck_slice_region_conflict
#define typeck_typeck_check_slice_region_assign typeck_check_slice_region_assign
#define typeck_typeck_check_return_slice_region typeck_check_return_slice_region
#define typeck_typeck_ptr_has_stack_local_label typeck_ptr_has_stack_local_label
#define typeck_typeck_block_tree_has_var typeck_block_tree_has_var
#define typeck_typeck_var_is_block_local typeck_var_is_block_local
#define typeck_typeck_expr_is_addr_of_block_local typeck_expr_is_addr_of_block_local
#define typeck_typeck_lval_is_param_ptr_field typeck_lval_is_param_ptr_field
#define typeck_typeck_block_is_strict_ancestor typeck_block_is_strict_ancestor
#define typeck_typeck_expr_lval_root_var typeck_expr_lval_root_var
#define typeck_typeck_check_struct_stack_escape_assign typeck_check_struct_stack_escape_assign
#define typeck_typeck_check_scope_borrow_assign typeck_check_scope_borrow_assign
#define typeck_typeck_check_scope_borrow_return typeck_check_scope_borrow_return
#define typeck_typeck_type_is_allocator_struct typeck_type_is_allocator_struct
#define typeck_typeck_check_allocator_region_assign typeck_check_allocator_region_assign
#define typeck_typeck_check_allocator_region_return typeck_check_allocator_region_return
#define typeck_typeck_check_call_ptr_struct_compat typeck_check_call_ptr_struct_compat
#define typeck_typeck_check_call_slice_region typeck_check_call_slice_region
#define typeck_typeck_check_expr_call typeck_check_expr_call
#define typeck_typeck_type_is_aggregate_cmp_operand typeck_type_is_aggregate_cmp_operand
#define typeck_typeck_check_expr_binop_cmp typeck_check_expr_binop_cmp
#define typeck_typeck_check_expr_binop_arith typeck_check_expr_binop_arith
#define typeck_typeck_check_expr_binop typeck_check_expr_binop
#define typeck_typeck_check_expr_field_access typeck_check_expr_field_access
#define typeck_typeck_check_expr_unary typeck_check_expr_unary
#define typeck_typeck_check_expr_addr_of typeck_check_expr_addr_of
#define typeck_typeck_check_expr_deref typeck_check_expr_deref
#define typeck_typeck_check_expr_var_top_level typeck_check_expr_var_top_level
#define typeck_typeck_check_expr_var typeck_check_expr_var
#define typeck_typeck_check_expr_method_call_arg typeck_check_expr_method_call_arg
#define typeck_typeck_method_call_resolve_generic_bound typeck_method_call_resolve_generic_bound
#define typeck_typeck_check_expr_method_call typeck_check_expr_method_call
#define typeck_typeck_as_cast_type_class_ok typeck_as_cast_type_class_ok
#define typeck_typeck_as_cast_allowed typeck_as_cast_allowed
#define typeck_typeck_check_expr_as typeck_check_expr_as
#define typeck_typeck_check_expr_struct_lit_field typeck_check_expr_struct_lit_field
#define typeck_typeck_coerce_struct_lit_field_inits_to_layout typeck_coerce_struct_lit_field_inits_to_layout
#define typeck_typeck_check_expr_struct_lit typeck_check_expr_struct_lit
#define typeck_typeck_vector_elem_type_ref typeck_vector_elem_type_ref
#define typeck_typeck_type_is_valid_subscript_index typeck_type_is_valid_subscript_index
#define typeck_typeck_check_expr_index typeck_check_expr_index
#define typeck_typeck_expr_is_any_assign_kind typeck_expr_is_any_assign_kind
#define typeck_typeck_check_expr_array_lit typeck_check_expr_array_lit
#define typeck_typeck_check_expr_impl_mega typeck_check_expr_impl_mega
#define typeck_typeck_check_expr_impl typeck_check_expr_impl
#define typeck_typeck_check_expr typeck_check_expr
#define typeck_typeck_func_body_tail_expr_ref_for_implicit_rule typeck_func_body_tail_expr_ref_for_implicit_rule
#define typeck_typeck_func_body_has_implicit_return_tail typeck_func_body_has_implicit_return_tail
#define typeck_typeck_loop_depth_push typeck_loop_depth_push
#define typeck_typeck_check_block_as_loop_body typeck_check_block_as_loop_body
#define typeck_typeck_check_block_one_const typeck_check_block_one_const
#define typeck_typeck_check_block_one_let typeck_check_block_one_let
#define typeck_typeck_check_block_one_while typeck_check_block_one_while
#define typeck_typeck_check_block_one_for typeck_check_block_one_for
#define typeck_typeck_check_block_one_if typeck_check_block_one_if
#define typeck_typeck_void_reject_value_expr typeck_void_reject_value_expr
#define typeck_typeck_check_block_final typeck_check_block_final
#define typeck_typeck_check_block_one_region typeck_check_block_one_region
#define typeck_typeck_check_block_stmt_order_one typeck_check_block_stmt_order_one
#define typeck_typeck_check_block_legacy_consts typeck_check_block_legacy_consts
#define typeck_typeck_check_block_legacy_lets typeck_check_block_legacy_lets
#define typeck_typeck_check_block_legacy_whiles typeck_check_block_legacy_whiles
#define typeck_typeck_check_block_legacy_fors typeck_check_block_legacy_fors
#define typeck_typeck_check_block_legacy_ifs typeck_check_block_legacy_ifs
#define typeck_typeck_check_block_legacy_expr_stmts typeck_check_block_legacy_expr_stmts
#define typeck_typeck_check_block_impl typeck_check_block_impl
#define typeck_typeck_check_block typeck_check_block
#define typeck_typeck_x_ast_check_one_func typeck_x_ast_check_one_func
#define typeck_typeck_x_ast_check_all_funcs_loop typeck_x_ast_check_all_funcs_loop
#define typeck_typeck_x_ast_check_one_top_level_let typeck_x_ast_check_one_top_level_let
#define typeck_typeck_x_ast_check_top_level_lets typeck_x_ast_check_top_level_lets
#define typeck_typeck_x_ast_impl typeck_x_ast_impl
#define typeck_typeck_x_ast_library typeck_x_ast_library
#define typeck_typeck_x_ast typeck_x_ast
#define typeck_typeck_scan_expr_stack_escape_c typeck_scan_expr_stack_escape_c
#define typeck_typeck_scan_block_stack_escape_c typeck_scan_block_stack_escape_c
#define typeck_typeck_module_func_overload_count typeck_module_func_overload_count
#define typeck_typeck_pick_overload_func_index_for_call typeck_pick_overload_func_index_for_call
#define typeck_typeck_resolve_call_func_index_for_emit typeck_resolve_call_func_index_for_emit
#define typeck_typeck_call_arg_effective_type typeck_call_arg_effective_type
#define typeck_typeck_try_infer_generic_call_from_args typeck_try_infer_generic_call_from_args
#define typeck_typeck_check_inferred_generic_bounds typeck_check_inferred_generic_bounds
#define typeck_typeck_check_call_generic_type_args typeck_check_call_generic_type_args
#define typeck_typeck_mono_map_lookup typeck_mono_map_lookup
#define typeck_typeck_mono_map_bind typeck_mono_map_bind
#define typeck_typeck_named_num_type_args_ASTArena_ptr_i32_reti32 typeck_named_num_type_args_ASTArena_ptr_i32_reti32
#define typeck_typeck_alloc_named_with_type_args_flat typeck_alloc_named_with_type_args_flat
#define typeck_typeck_pattern_unify_bind typeck_pattern_unify_bind
#define typeck_typeck_build_value_formal_mono_map typeck_build_value_formal_mono_map
#define typeck_typeck_subst_type_ref typeck_subst_type_ref
#define typeck_typeck_generic_call_subst_ret_from_formal_map typeck_generic_call_subst_ret_from_formal_map
#define typeck_typeck_method_call_generic_ufcs typeck_method_call_generic_ufcs
#define typeck_typeck_generic_call_fixup_resolved_type typeck_generic_call_fixup_resolved_type
#define typeck_typeck_linear_name_already_moved typeck_linear_name_already_moved
#define typeck_typeck_call_resolve_dep_idx_peek typeck_call_resolve_dep_idx_peek
#define typeck_typeck_call_resolve_func_idx_peek typeck_call_resolve_func_idx_peek
#define typeck_typeck_overload_expected_ret_peek typeck_overload_expected_ret_peek
#define typeck_typeck_expr_is_c_static_const_init typeck_expr_is_c_static_const_init
#define typeck_typeck_expr_is_const_with_module_consts typeck_expr_is_const_with_module_consts
#define typeck_typeck_block_const_init_is_const typeck_block_const_init_is_const
#define ast_expr_apply_call_resolve ast_ast_expr_apply_call_resolve
#define ast_block_final_expr_ref ast_ast_block_final_expr_ref
#define ast_expr_disallows_implicit_tail ast_ast_expr_disallows_implicit_tail
#define ast_block_num_consts ast_ast_block_num_consts
#define ast_block_num_lets ast_ast_block_num_lets
#define ast_block_num_loops ast_ast_block_num_loops
#define ast_block_num_for_loops ast_ast_block_num_for_loops
#define ast_block_num_if_stmts ast_ast_block_num_if_stmts
#define ast_block_num_regions ast_ast_block_num_regions
#define ast_block_num_labeled_stmts ast_ast_block_num_labeled_stmts
#define ast_block_region_body_ref ast_ast_block_region_body_ref
#define ast_block_num_expr_stmts ast_ast_block_num_expr_stmts
#define ast_block_num_stmt_order ast_ast_block_num_stmt_order
#define ast_block_stmt_order_kind ast_ast_block_stmt_order_kind
#define ast_block_stmt_order_idx ast_ast_block_stmt_order_idx
#define ast_block_const_init_ref ast_ast_block_const_init_ref
#define ast_block_const_type_ref ast_ast_block_const_type_ref
#define ast_block_let_init_ref ast_ast_block_let_init_ref
#define ast_block_let_type_ref ast_ast_block_let_type_ref
#define ast_block_expr_stmt_ref ast_ast_block_expr_stmt_ref
#define ast_block_while_cond_ref ast_ast_block_while_cond_ref
#define ast_block_while_body_ref ast_ast_block_while_body_ref
#define ast_block_for_init_ref ast_ast_block_for_init_ref
#define ast_block_for_cond_ref ast_ast_block_for_cond_ref
#define ast_block_for_step_ref ast_ast_block_for_step_ref
#define ast_block_for_body_ref ast_ast_block_for_body_ref
#define ast_block_if_cond_ref ast_ast_block_if_cond_ref
#define ast_block_if_then_body_ref ast_ast_block_if_then_body_ref
#define ast_block_if_else_body_ref ast_ast_block_if_else_body_ref
#define ast_block_resolve_var_to_type_ref ast_ast_block_resolve_var_to_type_ref
#define ast_expr_layout_prime_call_resolved ast_ast_expr_layout_prime_call_resolved
#define ast_arena_expr_set ast_ast_arena_expr_set
#define ast_arena_block_set ast_ast_arena_block_set
#define ast_arena_type_set ast_ast_arena_type_set
#define ast_arena_func_set ast_ast_arena_func_set

/* pipeline reverse aliases (call ast_pipeline_* → pipeline_* extern) */
#define ast_pipeline_arena_expr_get_copy pipeline_arena_expr_get_copy
#define ast_pipeline_arena_block_get_copy pipeline_arena_block_get_copy
#define ast_pipeline_arena_type_get_copy pipeline_arena_type_get_copy
#define ast_pipeline_arena_func_get_copy pipeline_arena_func_get_copy
#define ast_pipeline_arena_type_alloc pipeline_arena_type_alloc
#define ast_pipeline_arena_expr_alloc pipeline_arena_expr_alloc
#define ast_pipeline_arena_block_alloc pipeline_arena_block_alloc
#define ast_pipeline_arena_func_alloc pipeline_arena_func_alloc
#define ast_pipeline_arena_type_set_copy pipeline_arena_type_set_copy
#define ast_pipeline_arena_expr_set_copy pipeline_arena_expr_set_copy
#define ast_pipeline_arena_block_set_copy pipeline_arena_block_set_copy
#define ast_pipeline_arena_func_set_copy pipeline_arena_func_set_copy
#define ast_pipeline_arena_type_cap pipeline_arena_type_cap
#define ast_pipeline_arena_expr_cap pipeline_arena_expr_cap
#define ast_pipeline_arena_block_cap pipeline_arena_block_cap
#define ast_pipeline_arena_func_cap pipeline_arena_func_cap
#define ast_pipeline_module_import_alloc pipeline_module_import_alloc
#define ast_pipeline_module_import_set_path pipeline_module_import_set_path
#define ast_pipeline_module_import_path_len pipeline_module_import_path_len
#define ast_pipeline_module_import_path_copy pipeline_module_import_path_copy
#define ast_pipeline_module_import_path_byte_at pipeline_module_import_path_byte_at
#define ast_pipeline_module_import_set_kind pipeline_module_import_set_kind
#define ast_pipeline_module_import_kind_at pipeline_module_import_kind_at
#define ast_pipeline_module_import_set_binding_name pipeline_module_import_set_binding_name
#define ast_pipeline_module_import_binding_name_len pipeline_module_import_binding_name_len
#define ast_pipeline_module_import_binding_name_byte_at pipeline_module_import_binding_name_byte_at
#define ast_pipeline_module_import_set_select_count pipeline_module_import_set_select_count
#define ast_pipeline_module_import_append_select_name pipeline_module_import_append_select_name
#define ast_pipeline_module_import_select_count_at pipeline_module_import_select_count_at
#define ast_pipeline_module_import_set_select_name pipeline_module_import_set_select_name
#define ast_pipeline_module_import_select_name_len pipeline_module_import_select_name_len
#define ast_pipeline_module_import_select_name_byte_at pipeline_module_import_select_name_byte_at
#define ast_pipeline_module_struct_layout_alloc pipeline_module_struct_layout_alloc
#define ast_pipeline_module_struct_layout_reset_slot pipeline_module_struct_layout_reset_slot
#define ast_pipeline_module_struct_layout_set_name pipeline_module_struct_layout_set_name
#define ast_pipeline_module_struct_layout_set_field pipeline_module_struct_layout_set_field
#define ast_pipeline_module_struct_layout_name_len pipeline_module_struct_layout_name_len
#define ast_pipeline_module_struct_layout_name_into pipeline_module_struct_layout_name_into
#define ast_pipeline_module_struct_layout_field_name_into pipeline_module_struct_layout_field_name_into
#define ast_pipeline_module_struct_layout_num_fields pipeline_module_struct_layout_num_fields
#define ast_pipeline_module_struct_layout_set_num_fields pipeline_module_struct_layout_set_num_fields
#define ast_pipeline_module_struct_layout_field_type_ref pipeline_module_struct_layout_field_type_ref
#define ast_pipeline_module_struct_layout_field_name_len pipeline_module_struct_layout_field_name_len
#define ast_pipeline_module_top_level_let_alloc pipeline_module_top_level_let_alloc
#define ast_pipeline_module_top_level_let_set pipeline_module_top_level_let_set
#define ast_pipeline_module_top_level_let_name_len pipeline_module_top_level_let_name_len
#define ast_pipeline_module_top_level_let_name_byte_at pipeline_module_top_level_let_name_byte_at
#define ast_pipeline_module_top_level_let_type_ref pipeline_module_top_level_let_type_ref
#define ast_pipeline_module_top_level_let_init_ref pipeline_module_top_level_let_init_ref
#define ast_pipeline_module_top_level_let_is_const pipeline_module_top_level_let_is_const
#define ast_pipeline_module_enum_alloc pipeline_module_enum_alloc
#define ast_pipeline_module_enum_set_name pipeline_module_enum_set_name
#define ast_pipeline_module_enum_name_len pipeline_module_enum_name_len
#define ast_pipeline_module_enum_name_byte_at pipeline_module_enum_name_byte_at
#define ast_pipeline_module_struct_layout_name_byte_at pipeline_module_struct_layout_name_byte_at
#define ast_pipeline_module_struct_layout_set_allow_padding pipeline_module_struct_layout_set_allow_padding
#define ast_pipeline_module_struct_layout_allow_padding_at pipeline_module_struct_layout_allow_padding_at
#define ast_pipeline_module_struct_layout_set_soa pipeline_module_struct_layout_set_soa
#define ast_pipeline_module_struct_layout_set_packed pipeline_module_struct_layout_set_packed
#define ast_pipeline_module_struct_layout_packed_at pipeline_module_struct_layout_packed_at
#define ast_pipeline_module_struct_layout_soa_at pipeline_module_struct_layout_soa_at
#define ast_pipeline_module_struct_layout_field_offset_at pipeline_module_struct_layout_field_offset_at
#define ast_pipeline_module_struct_layout_set_field_offset pipeline_module_struct_layout_set_field_offset
#define ast_pipeline_onefunc_append_const_name pipeline_onefunc_append_const_name
#define ast_pipeline_onefunc_const_name_len pipeline_onefunc_const_name_len
#define ast_pipeline_onefunc_const_name_byte_at pipeline_onefunc_const_name_byte_at
#define ast_pipeline_onefunc_const_init_val pipeline_onefunc_const_init_val
#define ast_pipeline_onefunc_num_consts pipeline_onefunc_num_consts
#define ast_pipeline_onefunc_append_let pipeline_onefunc_append_let
#define ast_pipeline_onefunc_let_name_len pipeline_onefunc_let_name_len
#define ast_pipeline_onefunc_let_name_byte_at pipeline_onefunc_let_name_byte_at
#define ast_pipeline_onefunc_let_init_val pipeline_onefunc_let_init_val
#define ast_pipeline_onefunc_let_init_ref pipeline_onefunc_let_init_ref
#define ast_pipeline_onefunc_let_type_ref pipeline_onefunc_let_type_ref
#define ast_pipeline_onefunc_num_lets pipeline_onefunc_num_lets
#define ast_pipeline_onefunc_const_name_copy64 pipeline_onefunc_const_name_copy64
#define ast_pipeline_onefunc_let_name_copy64 pipeline_onefunc_let_name_copy64
#define ast_pipeline_onefunc_copy_sidecar pipeline_onefunc_copy_sidecar
#define ast_pipeline_block_append_const pipeline_block_append_const
#define ast_pipeline_block_append_let pipeline_block_append_let
#define ast_pipeline_block_append_if pipeline_block_append_if
#define ast_pipeline_block_append_region pipeline_block_append_region
#define ast_pipeline_block_append_unsafe pipeline_block_append_unsafe
#define ast_pipeline_block_region_body_ref pipeline_block_region_body_ref
#define ast_pipeline_block_append_expr_stmt pipeline_block_append_expr_stmt
#define ast_pipeline_block_append_stmt_order pipeline_block_append_stmt_order
#define ast_pipeline_block_const_init_ref pipeline_block_const_init_ref
#define ast_pipeline_block_const_type_ref pipeline_block_const_type_ref
#define ast_pipeline_block_const_name_len pipeline_block_const_name_len
#define ast_pipeline_block_const_name_copy64 pipeline_block_const_name_copy64
#define ast_pipeline_block_let_init_ref pipeline_block_let_init_ref
#define ast_pipeline_block_let_type_ref pipeline_block_let_type_ref
#define ast_pipeline_block_let_name_len pipeline_block_let_name_len
#define ast_pipeline_block_let_name_copy64 pipeline_block_let_name_copy64
#define ast_pipeline_block_stmt_order_kind pipeline_block_stmt_order_kind
#define ast_pipeline_block_stmt_order_idx pipeline_block_stmt_order_idx
#define ast_pipeline_block_if_cond_ref pipeline_block_if_cond_ref
#define ast_pipeline_block_if_then_body_ref pipeline_block_if_then_body_ref
#define ast_pipeline_block_if_else_body_ref pipeline_block_if_else_body_ref
#define ast_pipeline_block_resolve_var_type_ref pipeline_block_resolve_var_type_ref
#define ast_pipeline_block_fill_ifs_from_onefunc pipeline_block_fill_ifs_from_onefunc
#define ast_pipeline_block_fill_stmt_order_from_onefunc pipeline_block_fill_stmt_order_from_onefunc
#define ast_pipeline_block_fill_expr_stmts_from_onefunc pipeline_block_fill_expr_stmts_from_onefunc
#define ast_pipeline_block_append_while pipeline_block_append_while
#define ast_pipeline_block_append_for pipeline_block_append_for
#define ast_pipeline_block_while_cond_ref pipeline_block_while_cond_ref
#define ast_pipeline_block_while_body_ref pipeline_block_while_body_ref
#define ast_pipeline_block_for_init_ref pipeline_block_for_init_ref
#define ast_pipeline_block_for_cond_ref pipeline_block_for_cond_ref
#define ast_pipeline_block_for_step_ref pipeline_block_for_step_ref
#define ast_pipeline_block_for_body_ref pipeline_block_for_body_ref
#define ast_pipeline_block_fill_whiles_from_onefunc pipeline_block_fill_whiles_from_onefunc
#define ast_pipeline_block_fill_fors_from_onefunc pipeline_block_fill_fors_from_onefunc
#define ast_pipeline_block_append_labeled pipeline_block_append_labeled
#define ast_pipeline_block_labeled_return_expr_ref pipeline_block_labeled_return_expr_ref
#define ast_pipeline_onefunc_append_while pipeline_onefunc_append_while
#define ast_pipeline_onefunc_while_cond_ref pipeline_onefunc_while_cond_ref
#define ast_pipeline_onefunc_while_body_ref pipeline_onefunc_while_body_ref
#define ast_pipeline_onefunc_num_whiles pipeline_onefunc_num_whiles
#define ast_pipeline_onefunc_append_for pipeline_onefunc_append_for
#define ast_pipeline_onefunc_for_init_ref pipeline_onefunc_for_init_ref
#define ast_pipeline_onefunc_for_cond_ref pipeline_onefunc_for_cond_ref
#define ast_pipeline_onefunc_for_step_ref pipeline_onefunc_for_step_ref
#define ast_pipeline_onefunc_for_body_ref pipeline_onefunc_for_body_ref
#define ast_pipeline_onefunc_num_fors pipeline_onefunc_num_fors
#define ast_pipeline_dep_ctx_set_module pipeline_dep_ctx_set_module
#define ast_pipeline_dep_ctx_set_arena pipeline_dep_ctx_set_arena
#define ast_pipeline_dep_ctx_module_at pipeline_dep_ctx_module_at
#define ast_pipeline_dep_ctx_arena_at pipeline_dep_ctx_arena_at
#define ast_pipeline_dep_ctx_set_import_path pipeline_dep_ctx_set_import_path
#define ast_pipeline_dep_ctx_import_path_len pipeline_dep_ctx_import_path_len
#define ast_pipeline_dep_ctx_import_path_byte_at pipeline_dep_ctx_import_path_byte_at
#define ast_pipeline_dep_ctx_import_path_copy64 pipeline_dep_ctx_import_path_copy64
#define ast_pipeline_dep_ctx_ndep pipeline_dep_ctx_ndep
#define ast_pipeline_dep_ctx_set_ndep pipeline_dep_ctx_set_ndep
#define ast_pipeline_ctx_append_lib_root pipeline_ctx_append_lib_root
#define ast_pipeline_ctx_lib_root_count pipeline_ctx_lib_root_count
#define ast_pipeline_ctx_lib_root_len pipeline_ctx_lib_root_len
#define ast_pipeline_ctx_lib_root_copy pipeline_ctx_lib_root_copy
#define ast_pipeline_module_func_alloc_slot pipeline_module_func_alloc_slot
#define ast_pipeline_module_func_ref_at pipeline_module_func_ref_at
#define ast_pipeline_module_func_ref_set pipeline_module_func_ref_set
#define ast_pipeline_module_func_set_return_type pipeline_module_func_set_return_type
#define ast_pipeline_module_func_set_body_ref pipeline_module_func_set_body_ref
#define ast_pipeline_module_func_set_body_expr_ref pipeline_module_func_set_body_expr_ref
#define ast_pipeline_module_func_set_is_extern pipeline_module_func_set_is_extern
#define ast_pipeline_module_func_set_is_variadic pipeline_module_func_set_is_variadic
#define ast_pipeline_module_func_is_variadic_at pipeline_module_func_is_variadic_at
#define ast_pipeline_module_func_set_num_params pipeline_module_func_set_num_params
#define ast_pipeline_module_func_set_num_generic_params pipeline_module_func_set_num_generic_params
#define ast_pipeline_module_func_return_type_at pipeline_module_func_return_type_at
#define ast_pipeline_module_func_num_generic_params_at pipeline_module_func_num_generic_params_at
#define ast_pipeline_module_func_name_equal_at pipeline_module_func_name_equal_at
#define ast_pipeline_module_func_name_byte_at pipeline_module_func_name_byte_at
#define ast_pipeline_module_func_body_expr_ref_at pipeline_module_func_body_expr_ref_at
#define ast_pipeline_expr_append_call_arg pipeline_expr_append_call_arg
#define ast_pipeline_expr_call_arg_ref pipeline_expr_call_arg_ref
#define ast_pipeline_expr_call_num_args_at pipeline_expr_call_num_args_at
#define ast_pipeline_expr_call_num_type_args_at pipeline_expr_call_num_type_args_at
#define ast_pipeline_expr_append_method_call_arg pipeline_expr_append_method_call_arg
#define ast_pipeline_expr_method_call_arg_ref pipeline_expr_method_call_arg_ref
#define ast_pipeline_expr_append_match_arm pipeline_expr_append_match_arm
#define ast_pipeline_expr_match_num_arms_at pipeline_expr_match_num_arms_at
#define ast_pipeline_expr_match_arm_result_ref pipeline_expr_match_arm_result_ref
#define ast_pipeline_expr_match_arm_is_wildcard pipeline_expr_match_arm_is_wildcard
#define ast_pipeline_expr_match_arm_lit_val pipeline_expr_match_arm_lit_val
#define ast_pipeline_expr_match_arm_is_enum_variant pipeline_expr_match_arm_is_enum_variant
#define ast_pipeline_expr_match_arm_variant_index pipeline_expr_match_arm_variant_index
#define ast_pipeline_expr_match_arm_set_wildcard pipeline_expr_match_arm_set_wildcard
#define ast_pipeline_expr_match_arm_set_lit_val pipeline_expr_match_arm_set_lit_val
#define ast_pipeline_expr_match_arm_set_enum_variant pipeline_expr_match_arm_set_enum_variant
#define ast_pipeline_expr_append_struct_lit_field pipeline_expr_append_struct_lit_field
#define ast_pipeline_expr_append_array_lit_elem pipeline_expr_append_array_lit_elem
#define ast_pipeline_expr_array_lit_elem_ref pipeline_expr_array_lit_elem_ref
#define ast_pipeline_expr_array_lit_num_elems_at pipeline_expr_array_lit_num_elems_at
#define ast_pipeline_expr_init_call_resolve_at_ref pipeline_expr_init_call_resolve_at_ref
#define ast_pipeline_expr_apply_call_resolve pipeline_expr_apply_call_resolve
#define ast_pipeline_typeck_field_import_binding_resolve_c pipeline_typeck_field_import_binding_resolve_c
#define ast_pipeline_typeck_field_layout_named_c pipeline_typeck_field_layout_named_c
#define ast_pipeline_typeck_field_unknown_hard_fail_c pipeline_typeck_field_unknown_hard_fail_c
#define ast_pipeline_typeck_named_is_module_concrete_c pipeline_typeck_named_is_module_concrete_c
#define ast_pipeline_typeck_with_arena_scope_n_at pipeline_typeck_with_arena_scope_n_at
#define ast_pipeline_typeck_with_arena_current_body_ref_c pipeline_typeck_with_arena_current_body_ref_c
#define ast_pipeline_typeck_with_arena_scope_push_c pipeline_typeck_with_arena_scope_push_c
#define ast_pipeline_typeck_with_arena_scope_pop_c pipeline_typeck_with_arena_scope_pop_c
#define ast_pipeline_typeck_with_arena_scope_reset_c pipeline_typeck_with_arena_scope_reset_c
#define ast_pipeline_dep_ctx_scope_region_push_c pipeline_dep_ctx_scope_region_push_c
#define ast_pipeline_dep_ctx_scope_region_pop_c pipeline_dep_ctx_scope_region_pop_c
#define ast_pipeline_dep_ctx_scope_region_len_at pipeline_dep_ctx_scope_region_len_at
#define ast_pipeline_typeck_region_scope_reset_c pipeline_typeck_region_scope_reset_c
#define ast_pipeline_typeck_scan_module_struct_stack_escape_c pipeline_typeck_scan_module_struct_stack_escape_c
#define ast_pipeline_typeck_is_read_ptr_slice_callee_c pipeline_typeck_is_read_ptr_slice_callee_c
#define ast_pipeline_typeck_is_simd_comptime_callee_c pipeline_typeck_is_simd_comptime_callee_c
#define ast_pipeline_typeck_read_ptr_slice_return_ref_c pipeline_typeck_read_ptr_slice_return_ref_c
#define ast_pipeline_type_stamp_block_let_region_c pipeline_type_stamp_block_let_region_c
#define ast_pipeline_typeck_check_block_one_region_c pipeline_typeck_check_block_one_region_c
#define ast_pipeline_typeck_check_call_struct_stack_escape_c pipeline_typeck_check_call_struct_stack_escape_c
#define ast_pipeline_typeck_ptr_for_addr_of_operand_c pipeline_typeck_ptr_for_addr_of_operand_c
#define ast_pipeline_typeck_check_return_slice_region_in_scope_c pipeline_typeck_check_return_slice_region_in_scope_c
#define ast_pipeline_typeck_resolve_call_callee_return_type_c pipeline_typeck_resolve_call_callee_return_type_c
#define ast_pipeline_typeck_pick_overload_func_index_for_call_c pipeline_typeck_pick_overload_func_index_for_call_c
#define ast_pipeline_typeck_resolve_call_func_index_for_emit_c pipeline_typeck_resolve_call_func_index_for_emit_c
#define ast_pipeline_typeck_named_is_module_type_c pipeline_typeck_named_is_module_type_c
#define ast_pipeline_typeck_call_arg_effective_type_c pipeline_typeck_call_arg_effective_type_c
#define ast_pipeline_typeck_check_call_generic_type_args_c pipeline_typeck_check_call_generic_type_args_c
#define ast_pipeline_typeck_method_call_generic_ufcs_c pipeline_typeck_method_call_generic_ufcs_c
#define ast_pipeline_typeck_set_entry_module_for_dep_map_c pipeline_typeck_set_entry_module_for_dep_map_c
#define ast_pipeline_typeck_get_dep_return_type_in_caller_arena_c pipeline_typeck_get_dep_return_type_in_caller_arena_c
#define ast_pipeline_typeck_dep_return_type_to_caller_arena_c pipeline_typeck_dep_return_type_to_caller_arena_c
#define ast_pipeline_typeck_expr_var_name_equal_func_c pipeline_typeck_expr_var_name_equal_func_c
#define ast_pipeline_typeck_find_func_return_type_in_module_by_name_c pipeline_typeck_find_func_return_type_in_module_by_name_c
#define ast_pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal
#define ast_pipeline_typeck_find_func_return_type_in_module_by_name_strict_minimal pipeline_typeck_find_func_return_type_in_module_by_name_strict_minimal
#define ast_pipeline_typeck_find_func_return_type_in_module_c pipeline_typeck_find_func_return_type_in_module_c
#define ast_pipeline_typeck_block_const_init_is_const_c pipeline_typeck_block_const_init_is_const_c
#define ast_pipeline_typeck_const_init_not_constant_c pipeline_typeck_const_init_not_constant_c
#define ast_pipeline_typeck_fold_expr_c pipeline_typeck_fold_expr_c
#define ast_pipeline_typeck_fold_block_const_init_c pipeline_typeck_fold_block_const_init_c
#define ast_pipeline_typeck_fold_expr_in_block_c pipeline_typeck_fold_expr_in_block_c
#define ast_pipeline_expr_is_c_static_const_init pipeline_expr_is_c_static_const_init
#define ast_pipeline_typeck_check_expr_assign_c pipeline_typeck_check_expr_assign_c
#define ast_pipeline_typeck_diag_append_lit_c pipeline_typeck_diag_append_lit_c
#define ast_pipeline_typeck_diag_append_u32_dec_c pipeline_typeck_diag_append_u32_dec_c
#define ast_pipeline_typeck_diag_fmt_type_at_c pipeline_typeck_diag_fmt_type_at_c
#define ast_pipeline_typeck_diag_fmt_type_into_c pipeline_typeck_diag_fmt_type_into_c
#define ast_pipeline_typeck_diag_fmt_type_or_question_c pipeline_typeck_diag_fmt_type_or_question_c
#define ast_pipeline_typeck_check_slice_region_assign_c pipeline_typeck_check_slice_region_assign_c
#define ast_pipeline_typeck_check_struct_stack_escape_assign_c pipeline_typeck_check_struct_stack_escape_assign_c
#define ast_pipeline_typeck_check_scope_borrow_assign_c pipeline_typeck_check_scope_borrow_assign_c
#define ast_pipeline_typeck_check_scope_borrow_return_c pipeline_typeck_check_scope_borrow_return_c
#define ast_pipeline_typeck_check_allocator_region_assign_c pipeline_typeck_check_allocator_region_assign_c
#define ast_pipeline_typeck_check_allocator_region_return_c pipeline_typeck_check_allocator_region_return_c
#define ast_pipeline_typeck_check_return_slice_region_c pipeline_typeck_check_return_slice_region_c
#define ast_pipeline_typeck_check_call_slice_region_c pipeline_typeck_check_call_slice_region_c
#define ast_pipeline_typeck_coerce_init_lit_to_decl_c pipeline_typeck_coerce_init_lit_to_decl_c
#define ast_pipeline_typeck_coerce_init_float_lit_to_decl_c pipeline_typeck_coerce_init_float_lit_to_decl_c
#define ast_pipeline_typeck_coerce_init_enum_field_to_decl_c pipeline_typeck_coerce_init_enum_field_to_decl_c
#define ast_pipeline_typeck_coerce_init_named_call_to_decl_c pipeline_typeck_coerce_init_named_call_to_decl_c
#define ast_pipeline_typeck_coerce_init_array_vector_lit_to_decl_c pipeline_typeck_coerce_init_array_vector_lit_to_decl_c
#define ast_pipeline_typeck_coerce_init_vector_binop_to_decl_c pipeline_typeck_coerce_init_vector_binop_to_decl_c
#define ast_pipeline_typeck_coerce_init_int_binop_to_decl_c pipeline_typeck_coerce_init_int_binop_to_decl_c
#define ast_pipeline_typeck_coerce_init_struct_lit_to_decl_c pipeline_typeck_coerce_init_struct_lit_to_decl_c
#define ast_pipeline_typeck_coerce_init_slice_from_array_c pipeline_typeck_coerce_init_slice_from_array_c
#define ast_pipeline_typeck_coerce_init_expr_to_decl_c pipeline_typeck_coerce_init_expr_to_decl_c
#define ast_pipeline_typeck_float_widen_ok_c pipeline_typeck_float_widen_ok_c
#define ast_pipeline_typeck_integer_widen_ok_c pipeline_typeck_integer_widen_ok_c
#define ast_pipeline_typeck_integer_widen_ok_refs_c pipeline_typeck_integer_widen_ok_refs_c
#define ast_pipeline_typeck_type_refs_equal_named_c pipeline_typeck_type_refs_equal_named_c
#define ast_pipeline_typeck_resolve_type_alias_ref_c pipeline_typeck_resolve_type_alias_ref_c
#define ast_pipeline_typeck_type_refs_equal_impl_c pipeline_typeck_type_refs_equal_impl_c
#define ast_pipeline_typeck_type_refs_equal_c pipeline_typeck_type_refs_equal_c
#define ast_pipeline_typeck_type_refs_equal_same_kind_c pipeline_typeck_type_refs_equal_same_kind_c
#define ast_pipeline_typeck_type_ref_is_bool_impl_c pipeline_typeck_type_ref_is_bool_impl_c
#define ast_pipeline_typeck_type_ref_is_bool_c pipeline_typeck_type_ref_is_bool_c
#define ast_pipeline_typeck_expr_type_ref_impl_c pipeline_typeck_expr_type_ref_impl_c
#define ast_pipeline_typeck_expr_type_ref_c pipeline_typeck_expr_type_ref_c
#define ast_pipeline_typeck_return_operand_matches_c pipeline_typeck_return_operand_matches_c
#define ast_pipeline_typeck_ret_coerce_integral_to_expect_i32_c pipeline_typeck_ret_coerce_integral_to_expect_i32_c
#define ast_pipeline_typeck_ret_coerce_integral_widen_c pipeline_typeck_ret_coerce_integral_widen_c
#define ast_pipeline_typeck_check_expr_int_lit_c pipeline_typeck_check_expr_int_lit_c
#define ast_pipeline_typeck_expr_is_any_assign_kind_c pipeline_typeck_expr_is_any_assign_kind_c
#define ast_pipeline_typeck_block_impl_bind_ctx_c pipeline_typeck_block_impl_bind_ctx_c
#define ast_pipeline_typeck_block_impl_restore_ctx_c pipeline_typeck_block_impl_restore_ctx_c
#define ast_pipeline_typeck_block_impl_touch_ctx_block_c pipeline_typeck_block_impl_touch_ctx_block_c
#define ast_pipeline_typeck_loop_depth_push_c pipeline_typeck_loop_depth_push_c
#define ast_pipeline_typeck_loop_depth_pop_c pipeline_typeck_loop_depth_pop_c
#define ast_pipeline_dep_ctx_typeck_unsafe_depth_at pipeline_dep_ctx_typeck_unsafe_depth_at
#define ast_pipeline_typeck_unsafe_depth_push_c pipeline_typeck_unsafe_depth_push_c
#define ast_pipeline_typeck_unsafe_depth_pop_c pipeline_typeck_unsafe_depth_pop_c
#define ast_pipeline_typeck_loop_depth_set_c pipeline_typeck_loop_depth_set_c
#define ast_pipeline_typeck_check_block_impl_c pipeline_typeck_check_block_impl_c
#define ast_pipeline_typeck_check_block_c pipeline_typeck_check_block_c
#define ast_pipeline_typeck_check_block_as_loop_body_c pipeline_typeck_check_block_as_loop_body_c
#define ast_pipeline_typeck_set_active_ctx_c pipeline_typeck_set_active_ctx_c
#define ast_pipeline_typeck_active_ctx_c pipeline_typeck_active_ctx_c
#define ast_pipeline_typeck_linear_reset_c pipeline_typeck_linear_reset_c
#define ast_pipeline_typeck_linear_use_var_c pipeline_typeck_linear_use_var_c
#define ast_pipeline_typeck_linear_accepts_init_c pipeline_typeck_linear_accepts_init_c
#define ast_pipeline_typeck_reject_addr_of_linear_c pipeline_typeck_reject_addr_of_linear_c
#define ast_pipeline_typeck_func_body_tail_expr_ref_for_implicit_rule_c pipeline_typeck_func_body_tail_expr_ref_for_implicit_rule_c
#define ast_pipeline_typeck_func_body_has_implicit_return_tail_c pipeline_typeck_func_body_has_implicit_return_tail_c
#define ast_pipeline_typeck_check_expr_method_call_c pipeline_typeck_check_expr_method_call_c
#define ast_pipeline_typeck_expr_apply_call_resolve_c pipeline_typeck_expr_apply_call_resolve_c
#define ast_pipeline_typeck_import_segment_at_c pipeline_typeck_import_segment_at_c
#define ast_pipeline_typeck_resolve_dep_index_for_import_c pipeline_typeck_resolve_dep_index_for_import_c
#define ast_pipeline_typeck_resolve_whole_import_call_ret_c pipeline_typeck_resolve_whole_import_call_ret_c
#define ast_pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32 pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32
#define ast_pipeline_dep_ctx_set_current_func_index pipeline_dep_ctx_set_current_func_index
#define ast_pipeline_typeck_check_expr_impl_c pipeline_typeck_check_expr_impl_c
#define ast_pipeline_typeck_check_expr_impl_mega_c pipeline_typeck_check_expr_impl_mega_c
#define ast_pipeline_typeck_check_expr_method_call_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_expr_method_call_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_expr_apply_call_resolve_c_ASTArena_ptr_i32_i32_i32 pipeline_typeck_expr_apply_call_resolve_c_ASTArena_ptr_i32_i32_i32
#define ast_pipeline_typeck_import_segment_at_c_Module_ptr_i32_i32_i32_ptr_i32_ptr_reti32 pipeline_typeck_import_segment_at_c_Module_ptr_i32_i32_i32_ptr_i32_ptr_reti32
#define ast_pipeline_typeck_resolve_dep_index_for_import_c_Module_ptr_PipelineDepCtx_ptr_i32_reti32 pipeline_typeck_resolve_dep_index_for_import_c_Module_ptr_PipelineDepCtx_ptr_i32_reti32
#define ast_pipeline_typeck_resolve_whole_import_call_ret_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_ptr_i32_ptr_reti32 pipeline_typeck_resolve_whole_import_call_ret_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_ptr_i32_ptr_reti32
#define ast_pipeline_typeck_check_expr_try_propagate_c pipeline_typeck_check_expr_try_propagate_c
#define ast_pipeline_typeck_check_expr_match_c pipeline_typeck_check_expr_match_c
#define ast_pipeline_typeck_match_set_subject_c pipeline_typeck_match_set_subject_c
#define ast_pipeline_typeck_match_clear_subject_c pipeline_typeck_match_clear_subject_c
#define ast_pipeline_typeck_match_subject_ty_get_c pipeline_typeck_match_subject_ty_get_c
#define ast_pipeline_typeck_match_subject_mod_get_c pipeline_typeck_match_subject_mod_get_c
#define ast_pipeline_module_struct_layout_repr_compatible_at pipeline_module_struct_layout_repr_compatible_at
#define ast_pipeline_typeck_check_expr_c pipeline_typeck_check_expr_c
#define ast_pipeline_module_struct_layout_num_type_params_at pipeline_module_struct_layout_num_type_params_at
#define ast_pipeline_module_struct_layout_type_param_name_len pipeline_module_struct_layout_type_param_name_len
#define ast_pipeline_module_struct_layout_type_param_name_into pipeline_module_struct_layout_type_param_name_into
#define ast_pipeline_type_named_name_into pipeline_type_named_name_into
#define ast_pipeline_type_kind_ord_at pipeline_type_kind_ord_at
#define ast_pipeline_type_array_size_at pipeline_type_array_size_at
#define ast_pipeline_type_elem_ref_at pipeline_type_elem_ref_at
#define ast_pipeline_type_type_arg_ref_at pipeline_type_type_arg_ref_at
#define ast_pipeline_type_append_type_arg pipeline_type_append_type_arg
#define ast_pipeline_type_set_elem_array_size_at pipeline_type_set_elem_array_size_at
#define ast_pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32 pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32
#define ast_pipeline_typeck_call_arg_repr_compatible_ok_c pipeline_typeck_call_arg_repr_compatible_ok_c
#define ast_pipeline_typeck_check_extern_call_unsafe_boundary_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_extern_call_unsafe_boundary_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_match_subject_field_type_c pipeline_typeck_match_subject_field_type_c
#define ast_pipeline_typeck_active_module_c pipeline_typeck_active_module_c
#define ast_pipeline_module_num_type_aliases_at pipeline_module_num_type_aliases_at
#define ast_pipeline_module_type_alias_name_len pipeline_module_type_alias_name_len
#define ast_pipeline_module_type_alias_name_byte_at pipeline_module_type_alias_name_byte_at
#define ast_pipeline_module_type_alias_target_ref pipeline_module_type_alias_target_ref
#define ast_pipeline_typeck_func_body_has_implicit_return_tail_c_ASTArena_ptr_i32_reti32 pipeline_typeck_func_body_has_implicit_return_tail_c_ASTArena_ptr_i32_reti32
#define ast_pipeline_expr_binop_left_ref_at pipeline_expr_binop_left_ref_at
#define ast_pipeline_expr_binop_right_ref_at pipeline_expr_binop_right_ref_at
#define ast_pipeline_block_name_binding_kind pipeline_block_name_binding_kind
#define ast_pipeline_module_top_level_name_is_const pipeline_module_top_level_name_is_const
#define ast_pipeline_block_local_name_redecl_c pipeline_block_local_name_redecl_c
#define ast_pipeline_patch_block_parent_links pipeline_patch_block_parent_links
#define ast_pipeline_asm_emit_dep_pipe_c pipeline_asm_emit_dep_pipe_c
#define ast_pipeline_asm_emit_func_index_c pipeline_asm_emit_func_index_c
#define ast_pipeline_asm_emit_set_func_index pipeline_asm_emit_set_func_index
#define ast_pipeline_expr_set_field_access_soa_stride pipeline_expr_set_field_access_soa_stride
#define ast_pipeline_expr_field_access_soa_stride pipeline_expr_field_access_soa_stride
#define ast_pipeline_debug_trace_named_func_bodies pipeline_debug_trace_named_func_bodies
#define ast_pipeline_get_dep_arena_slot pipeline_get_dep_arena_slot
#define ast_pipeline_module_func_param_type_ref_for_name pipeline_module_func_param_type_ref_for_name
#define ast_pipeline_module_num_funcs pipeline_module_num_funcs
#define ast_pipeline_module_main_func_index pipeline_module_main_func_index
#define ast_pipeline_module_func_is_extern_at pipeline_module_func_is_extern_at
#define ast_pipeline_module_func_body_ref_at pipeline_module_func_body_ref_at
#define ast_pipeline_module_func_name_len_at pipeline_module_func_name_len_at
#define ast_pipeline_module_func_name_copy64 pipeline_module_func_name_copy64
#define ast_pipeline_struct_layout_next_field_offset pipeline_struct_layout_next_field_offset
#define ast_pipeline_expr_struct_lit_num_fields pipeline_expr_struct_lit_num_fields
#define ast_pipeline_expr_struct_lit_type_name_len pipeline_expr_struct_lit_type_name_len
#define ast_pipeline_expr_struct_lit_type_name_into pipeline_expr_struct_lit_type_name_into
#define ast_pipeline_expr_struct_lit_type_name_set pipeline_expr_struct_lit_type_name_set
#define ast_pipeline_expr_struct_lit_field_name_len pipeline_expr_struct_lit_field_name_len
#define ast_pipeline_expr_struct_lit_field_name_into pipeline_expr_struct_lit_field_name_into
#define ast_pipeline_expr_struct_lit_init_ref pipeline_expr_struct_lit_init_ref
#define ast_pipeline_expr_resolved_type_ref pipeline_expr_resolved_type_ref
#define ast_pipeline_expr_set_resolved_type_ref pipeline_expr_set_resolved_type_ref
#define ast_pipeline_expr_typeck_set_float_bits_from_val pipeline_expr_typeck_set_float_bits_from_val
#define ast_pipeline_expr_line_at pipeline_expr_line_at
#define ast_pipeline_expr_col_at pipeline_expr_col_at
#define ast_pipeline_dep_ctx_typeck_loop_depth_at pipeline_dep_ctx_typeck_loop_depth_at
#define ast_pipeline_dep_ctx_current_block_ref_at pipeline_dep_ctx_current_block_ref_at
#define ast_pipeline_dep_ctx_current_func_index pipeline_dep_ctx_current_func_index
#define ast_pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32 pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_block_impl_bind_ctx_c_PipelineDepCtx_ptr_i32_reti32 pipeline_typeck_block_impl_bind_ctx_c_PipelineDepCtx_ptr_i32_reti32
#define ast_pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32 pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32
#define ast_pipeline_typeck_block_impl_touch_ctx_block_c_PipelineDepCtx_ptr_i32 pipeline_typeck_block_impl_touch_ctx_block_c_PipelineDepCtx_ptr_i32
#define ast_pipeline_expr_int_val_at pipeline_expr_int_val_at
#define ast_pipeline_expr_field_access_is_enum_variant pipeline_expr_field_access_is_enum_variant
#define ast_pipeline_expr_set_field_access_enum_variant pipeline_expr_set_field_access_enum_variant
#define ast_pipeline_expr_match_arm_guard_ref pipeline_expr_match_arm_guard_ref
#define ast_pipeline_expr_match_matched_ref_at pipeline_expr_match_matched_ref_at
#define ast_pipeline_module_enum_variant_tag_for_names pipeline_module_enum_variant_tag_for_names
#define ast_pipeline_type_init_primitive_kind_at pipeline_type_init_primitive_kind_at
#define ast_pipeline_type_init_named_at pipeline_type_init_named_at
#define ast_pipeline_type_init_compound_kind_at pipeline_type_init_compound_kind_at
#define ast_pipeline_type_ensure_by_kind_ord pipeline_type_ensure_by_kind_ord
#define ast_pipeline_type_find_or_alloc_named pipeline_type_find_or_alloc_named
#define ast_pipeline_type_find_or_alloc_compound pipeline_type_find_or_alloc_compound
#define ast_pipeline_type_region_label_into pipeline_type_region_label_into
#define ast_pipeline_type_region_label_len_at pipeline_type_region_label_len_at
#define ast_pipeline_type_set_region_label_at pipeline_type_set_region_label_at
#define ast_pipeline_type_find_or_alloc_slice pipeline_type_find_or_alloc_slice
#define ast_pipeline_type_find_or_alloc_ptr pipeline_type_find_or_alloc_ptr
#define ast_pipeline_typeck_check_slice_region_assign_c_ASTArena_ptr_i32_i32_i32_reti32 pipeline_typeck_check_slice_region_assign_c_ASTArena_ptr_i32_i32_i32_reti32
#define ast_pipeline_typeck_check_return_slice_region_c_ASTArena_ptr_i32_i32_i32_reti32 pipeline_typeck_check_return_slice_region_c_ASTArena_ptr_i32_i32_i32_reti32
#define ast_pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_call_slice_region_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_call_slice_region_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32 pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32
#define ast_pipeline_typeck_pick_overload_func_index_for_call_c_Module_ptr_ASTArena_ptr_i32_reti32 pipeline_typeck_pick_overload_func_index_for_call_c_Module_ptr_ASTArena_ptr_i32_reti32
#define ast_pipeline_typeck_check_call_generic_type_args_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32 pipeline_typeck_check_call_generic_type_args_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32
#define ast_pipeline_typeck_method_call_generic_ufcs_c_Module_ptr_ASTArena_ptr_i32_i32_u8_ptr_i32_i32_reti32 pipeline_typeck_method_call_generic_ufcs_c_Module_ptr_ASTArena_ptr_i32_i32_u8_ptr_i32_i32_reti32
#define ast_pipeline_expr_call_type_arg_ref_at pipeline_expr_call_type_arg_ref_at
#define ast_pipeline_typeck_resolve_call_callee_return_type_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_resolve_call_callee_return_type_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_type_stamp_block_let_region_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_type_stamp_block_let_region_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32 pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32
#define ast_pipeline_typeck_read_ptr_slice_return_ref_c_ASTArena_ptr_reti32 pipeline_typeck_read_ptr_slice_return_ref_c_ASTArena_ptr_reti32
#define ast_pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32 pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32
#define ast_pipeline_block_set_let_type_ref pipeline_block_set_let_type_ref
#define ast_pipeline_typeck_check_block_one_region_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_block_one_region_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_call_struct_stack_escape_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_call_struct_stack_escape_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_block_region_is_unsafe pipeline_block_region_is_unsafe
#define ast_pipeline_block_region_with_arena_cap_ref pipeline_block_region_with_arena_cap_ref
#define ast_pipeline_block_region_label_len pipeline_block_region_label_len
#define ast_pipeline_block_region_label_copy64 pipeline_block_region_label_copy64
#define ast_pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32 pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32 pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32
#define ast_pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32 pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32
#define ast_pipeline_typeck_linear_accepts_init_c_ASTArena_ptr_i32_i32_reti32 pipeline_typeck_linear_accepts_init_c_ASTArena_ptr_i32_i32_reti32
#define ast_pipeline_typeck_reject_addr_of_linear_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32 pipeline_typeck_reject_addr_of_linear_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_ptr_for_addr_of_operand_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32 pipeline_typeck_ptr_for_addr_of_operand_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_struct_stack_escape_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_struct_stack_escape_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_scope_borrow_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_scope_borrow_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_scope_borrow_return_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_scope_borrow_return_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_allocator_region_assign_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32 pipeline_typeck_check_allocator_region_assign_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32
#define ast_pipeline_typeck_check_allocator_region_return_c_ASTArena_ptr_i32_i32_reti32 pipeline_typeck_check_allocator_region_return_c_ASTArena_ptr_i32_i32_reti32
#define ast_pipeline_block_parent_block_ref_at pipeline_block_parent_block_ref_at
#define ast_pipeline_block_find_var_decl_block_ref pipeline_block_find_var_decl_block_ref
#define ast_pipeline_module_func_param_type_ref_at pipeline_module_func_param_type_ref_at
#define ast_pipeline_module_func_num_params_at pipeline_module_func_num_params_at
#define ast_pipeline_expr_call_resolved_func_index_at pipeline_expr_call_resolved_func_index_at
#define ast_pipeline_expr_call_resolved_dep_index_at pipeline_expr_call_resolved_dep_index_at
#define ast_pipeline_expr_kind_ord_at pipeline_expr_kind_ord_at
#define ast_pipeline_block_set_const_type_ref pipeline_block_set_const_type_ref
#define ast_pipeline_module_top_level_let_set_type_ref pipeline_module_top_level_let_set_type_ref
#define ast_pipeline_expr_if_cond_ref_at pipeline_expr_if_cond_ref_at
#define ast_pipeline_expr_if_then_ref_at pipeline_expr_if_then_ref_at
#define ast_pipeline_expr_if_else_ref_at pipeline_expr_if_else_ref_at
#define ast_pipeline_expr_block_ref_at pipeline_expr_block_ref_at
#define ast_pipeline_asm_block_final_expr_ref_at pipeline_asm_block_final_expr_ref_at
#define ast_pipeline_block_set_parent_if_zero pipeline_block_set_parent_if_zero
#define ast_pipeline_expr_unary_operand_ref_at pipeline_expr_unary_operand_ref_at
#define ast_pipeline_expr_call_callee_ref_at pipeline_expr_call_callee_ref_at
#define ast_pipeline_expr_index_base_ref pipeline_expr_index_base_ref
#define ast_pipeline_expr_index_index_ref pipeline_expr_index_index_ref
#define ast_pipeline_expr_set_index_base_is_slice pipeline_expr_set_index_base_is_slice
#define ast_pipeline_expr_set_index_proven_in_bounds pipeline_expr_set_index_proven_in_bounds
#define ast_pipeline_expr_as_operand_ref_at pipeline_expr_as_operand_ref_at
#define ast_pipeline_expr_as_target_type_ref_at pipeline_expr_as_target_type_ref_at
#define ast_pipeline_expr_field_access_name_into pipeline_expr_field_access_name_into
#define ast_pipeline_expr_field_access_name_len pipeline_expr_field_access_name_len
#define ast_pipeline_expr_field_access_base_ref pipeline_expr_field_access_base_ref
#define ast_pipeline_expr_set_field_access_offset pipeline_expr_set_field_access_offset
#define ast_pipeline_expr_var_name_into pipeline_expr_var_name_into
#define ast_pipeline_expr_var_name_len pipeline_expr_var_name_len
#define ast_pipeline_expr_method_call_base_ref_at pipeline_expr_method_call_base_ref_at
#define ast_pipeline_expr_method_call_num_args_at pipeline_expr_method_call_num_args_at
#define ast_pipeline_expr_method_call_name_len pipeline_expr_method_call_name_len
#define ast_pipeline_expr_method_call_name_into pipeline_expr_method_call_name_into
#define ast_pipeline_module_num_struct_layouts_at pipeline_module_num_struct_layouts_at
#define ast_pipeline_module_struct_layout_field_align_at pipeline_module_struct_layout_field_align_at
#define ast_pipeline_module_struct_layout_set_field_align pipeline_module_struct_layout_set_field_align
#define ast_pipeline_struct_layout_next_field_offset_ex pipeline_struct_layout_next_field_offset_ex
#define ast_pipeline_typeck_pad_fields_warn_layout pipeline_typeck_pad_fields_warn_layout
#define ast_pipeline_typeck_hot_reorder_warn_layout pipeline_typeck_hot_reorder_warn_layout
#define ast_pipeline_typeck_unused_binding_hints pipeline_typeck_unused_binding_hints
#define ast_pipeline_typeck_wpo_dump_callgraph pipeline_typeck_wpo_dump_callgraph
#define ast_pipeline_visibility_allow_func pipeline_visibility_allow_func
#define ast_pipeline_expr_is_null_keyword_c pipeline_expr_is_null_keyword_c
#define ast_pipeline_typeck_active_module_set_c pipeline_typeck_active_module_set_c
#define ast_pipeline_expr_enum_variant_tag_at pipeline_expr_enum_variant_tag_at
#define ast_pipeline_expr_try_mark_enum_field_access pipeline_expr_try_mark_enum_field_access
#define ast_pipeline_expr_const_folded_valid_at pipeline_expr_const_folded_valid_at
#define ast_pipeline_expr_const_folded_val_at pipeline_expr_const_folded_val_at

/* slim arena grow pool glue (linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);


struct xlang_slice_ast_ASTArena { struct ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_xlang_slice_ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_xlang_slice_xlang_slice_ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_ASTArena *data; size_t length; };

struct ast_PipelineDepCtx {
  int32_t ndep;
  uint8_t entry_dir_buf[512];
  int32_t entry_dir_len;
  int32_t num_lib_roots;
  uint8_t path_buf[512];
  uint8_t loaded_buf[4194304];
  ssize_t loaded_len;
  uint8_t preprocess_buf[4194304];
  int32_t preprocess_len;
  int32_t use_asm_backend;
  int32_t target_arch;
  int32_t target_cpu_features;
  int32_t use_macho_o;
  int32_t use_coff_o;
  int32_t current_block_ref;
  int32_t typeck_loop_depth;
  int32_t current_func_index;
  int32_t skip_codegen_dep_0;
  int32_t entry_already_parsed;
  int32_t current_func_single_empty_param_index;
  int32_t current_func_empty_param_count;
  int32_t current_emit_empty_var_next_index;
  int32_t emit_expr_as_callee;
  struct ast_Module * current_codegen_module;
  struct ast_ASTArena * current_codegen_arena;
  int32_t current_codegen_dep_index;
  uint8_t current_codegen_prefix_mirror[128];
  int32_t current_codegen_prefix_len;
  int32_t asm_entry_module_only;
  uint8_t entry_module_import_path_mirror[128];
  int32_t entry_module_import_path_len;
  int32_t typeck_scope_region_len;
  uint8_t typeck_scope_region_label[128];
  int32_t mono_active;
  int32_t mono_num_types;
  int32_t mono_generic_type_refs[8];
  int32_t mono_concrete_type_refs[8];
};

struct xlang_slice_ast_PipelineDepCtx { struct ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx { struct xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_xlang_slice_ast_PipelineDepCtx *data; size_t length; };

struct ast_Type;
struct ast_Expr;
struct ast_ConstDecl;
struct ast_LetDecl;
struct ast_WhileLoop;
struct ast_ForLoop;
struct ast_IfStmt;
struct ast_StmtOrderItem;
struct ast_LabeledStmt;
struct ast_Block;
struct ast_Param;
struct ast_Func;
struct ast_StructLayout;
struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;
struct ast_Type;
struct ast_Expr;
struct ast_ConstDecl;
struct ast_LetDecl;
struct ast_WhileLoop;
struct ast_ForLoop;
struct ast_IfStmt;
struct ast_StmtOrderItem;
struct ast_LabeledStmt;
struct ast_Block;
struct ast_Param;
struct ast_Func;
struct ast_StructLayout;
struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;
extern void ast_ast_pool_block_on_alloc(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_block_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_type_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_expr_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_block_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_func_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern int32_t pipeline_arena_type_cap(void);
extern int32_t pipeline_arena_expr_cap(void);
extern int32_t pipeline_arena_block_cap(void);
extern int32_t pipeline_arena_func_cap(void);
extern int32_t pipeline_module_import_alloc(struct ast_Module * module);
extern void pipeline_module_import_set_path(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_path_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_path_copy(struct ast_Module * module, int32_t idx, uint8_t * dst, int32_t dst_cap);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_kind(struct ast_Module * module, int32_t idx, int32_t kind);
extern int32_t pipeline_module_import_kind_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_binding_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_select_count(struct ast_Module * module, int32_t idx, int32_t n);
extern int32_t pipeline_module_import_append_select_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_count_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_select_name(struct ast_Module * module, int32_t idx, int32_t sel, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_name_len(struct ast_Module * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(struct ast_Module * module, int32_t idx, int32_t sel, int32_t off);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t li, int32_t j, uint8_t * fname_bytes, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_name_into(struct ast_Module * module, int32_t idx, uint8_t * out64);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module * module, int32_t li, int32_t j, uint8_t * out64);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t idx, int32_t nf);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_top_level_let_alloc(struct ast_Module * module);
extern void pipeline_module_top_level_let_set(struct ast_Module * module, int32_t idx, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref, int32_t is_const);
extern int32_t pipeline_module_top_level_let_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_top_level_let_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_top_level_let_type_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_init_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_is_const(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_enum_alloc(struct ast_Module * module);
extern void pipeline_module_enum_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_enum_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_allow_padding_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern void pipeline_module_struct_layout_set_packed(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_packed_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_soa_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_offset(struct ast_Module * module, int32_t li, int32_t j, int32_t foff);
extern int32_t pipeline_onefunc_append_const_name(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val);
extern int32_t pipeline_onefunc_const_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_const_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_const_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_consts(uint8_t * out);
extern int32_t pipeline_onefunc_append_let(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t pipeline_onefunc_let_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_let_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_let_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_type_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_lets(uint8_t * out);
extern void pipeline_onefunc_const_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_let_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_copy_sidecar(uint8_t * dst, uint8_t * src);
extern void ast_ast_pool_onefunc_reset(uint8_t * out);
extern int32_t pipeline_block_append_const(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_let(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_if(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_block_append_region(struct ast_ASTArena * arena, int32_t br, uint8_t * label, int32_t label_len, int32_t body_ref);
extern int32_t pipeline_block_append_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t body_ref);
extern int32_t pipeline_block_region_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern int32_t pipeline_block_append_expr_stmt(struct ast_ASTArena * arena, int32_t br, int32_t expr_ref);
extern int32_t pipeline_block_append_stmt_order(struct ast_ASTArena * arena, int32_t br, uint8_t kind, int32_t idx);
extern int32_t pipeline_block_const_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_name_len(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern void pipeline_block_const_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t ci, uint8_t * dst);
extern int32_t pipeline_block_let_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_name_len(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern void pipeline_block_let_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t li, uint8_t * dst);
extern int32_t pipeline_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t br, int32_t ei);
extern uint8_t pipeline_block_stmt_order_kind(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_stmt_order_idx(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_if_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_then_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_else_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void pipeline_block_fill_ifs_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_stmt_order_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_expr_stmts_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_while(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_block_append_for(struct ast_ASTArena * arena, int32_t br, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_block_while_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_while_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_for_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_step_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern void pipeline_block_fill_whiles_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_fors_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_labeled(struct ast_ASTArena * arena, int32_t br, int32_t label_len, int32_t is_goto, int32_t goto_target_len, int32_t return_expr_ref);
extern int32_t pipeline_block_labeled_return_expr_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_onefunc_append_while(uint8_t * out, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_while_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_while_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_whiles(uint8_t * out);
extern int32_t pipeline_onefunc_append_for(uint8_t * out, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_for_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_step_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_fors(uint8_t * out);
extern void pipeline_dep_ctx_set_module(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_Module * m);
extern void pipeline_dep_ctx_set_arena(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_ASTArena * a);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern uint8_t pipeline_dep_ctx_import_path_byte_at(struct ast_PipelineDepCtx * ctx, int32_t idx, int32_t off);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_set_ndep(struct ast_PipelineDepCtx * ctx, int32_t n);
extern int32_t pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx * ctx, uint8_t * path, int32_t len);
extern int32_t pipeline_ctx_lib_root_count(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_ctx_lib_root_len(struct ast_PipelineDepCtx * ctx, int32_t i);
extern void pipeline_ctx_lib_root_copy(struct ast_PipelineDepCtx * ctx, int32_t i, uint8_t * dst, int32_t cap);
extern int32_t pipeline_module_func_alloc_slot(struct ast_Module * module);
extern int32_t pipeline_module_func_ref_at(struct ast_Module * module, int32_t func_index);
extern void pipeline_module_func_ref_set(struct ast_Module * module, int32_t func_index, int32_t func_ref);
extern void pipeline_module_func_set_return_type(struct ast_Module * module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(struct ast_Module * module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(struct ast_Module * module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(struct ast_Module * module, int32_t fi, int32_t is_extern);
extern void pipeline_module_func_set_is_variadic(struct ast_Module * module, int32_t fi, int32_t is_variadic);
extern int32_t pipeline_module_func_is_variadic_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_set_num_params(struct ast_Module * module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_num_generic_params(struct ast_Module * module, int32_t fi, int32_t n);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_num_generic_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern void pipeline_module_func_set_is_used(struct ast_Module * module, int32_t fi, int32_t is_used);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern int ast_ref_is_null(int32_t ref);
extern int32_t ast_ast_placeholder(void);
extern void ast_expr_layout_prime_call_resolved(void);
extern void ast_func_layout_prime_generic_params(void);
extern void ast_ast_arena_init(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern void ast_expr_init_match_enum(struct ast_Expr * e);
extern int32_t pipeline_expr_append_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_type_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_append_method_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_append_match_arm(struct ast_ASTArena * arena, int32_t expr_ref, int32_t result_ref, int32_t is_wildcard, int32_t lit_val, int32_t is_enum_variant, int32_t variant_index);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern void pipeline_expr_match_arm_set_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t is_var, int32_t variant_index);
extern int32_t pipeline_expr_append_struct_lit_field(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * name_bytes, int32_t name_len, int32_t init_ref);
extern int32_t pipeline_expr_append_array_lit_elem(struct ast_ASTArena * arena, int32_t expr_ref, int32_t elem_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_init_call_resolve_at_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern void ast_expr_init_call_resolve(struct ast_ASTArena * arena, int32_t expr_ref);
extern void ast_ast_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
extern int ast_ast_name_bytes_equal(uint8_t * a_nm, int32_t a_len, uint8_t * b_nm, int32_t b_len);
extern int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena * a, int32_t body_ref);
extern int implicit_tail_expr_disallowed_by_glue(struct ast_ASTArena * a, int32_t expr_ref);
extern int ast_ast_expr_disallows_implicit_tail(struct ast_ASTArena * a, int32_t expr_ref);
extern int32_t ast_ast_block_num_consts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_lets(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_for_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_regions(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_labeled_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_region_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ri);
extern int32_t ast_ast_block_num_expr_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena * a, int32_t br);
extern uint8_t ast_ast_block_stmt_order_kind(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_stmt_order_idx(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_const_init_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_const_type_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_let_init_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_let_type_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_expr_stmt_ref(struct ast_ASTArena * a, int32_t br, int32_t ei);
extern int32_t ast_ast_block_while_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_while_body_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_for_init_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_step_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_body_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_if_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_then_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_else_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_resolve_var_to_type_ref(struct ast_ASTArena * a, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void ast_ast_arena_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern int32_t ast_ast_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern int32_t typeck_type_kind_ordinal(enum ast_TypeKind k);
extern int typeck_name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len);
extern int32_t typeck_resolve_type_alias_ref_local(struct ast_Module * module, struct ast_ASTArena * arena, int32_t type_ref, int32_t depth);
extern int32_t typeck_resolve_type_alias_ref(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_canonicalize_named_inst_if_present(struct ast_ASTArena * arena, int32_t ty);
extern int typeck_named_type_matches_name_or_alias(struct ast_Module * module, struct ast_ASTArena * arena, int32_t decl_ty_ref, uint8_t * lit_name, int32_t lit_name_len, int32_t depth);
extern int typeck_layout_name_equal(struct ast_Module * module, int32_t k, uint8_t * nm, int32_t nlen);
extern int typeck_layout_field_name_equal(struct ast_Module * module, int32_t k, int32_t j, uint8_t * nm, int32_t nlen);
extern int32_t typeck_layout_name_into(struct ast_Module * module, int32_t k, uint8_t * buf);
extern int32_t typeck_layout_field_name_into(struct ast_Module * module, int32_t k, int32_t j, uint8_t * buf);
extern int typeck_import_path_slice_equal(struct ast_Module * module, int32_t imp_ix, int32_t off, int32_t seg_len, uint8_t * nm, int32_t nm_len);
extern int typeck_import_binding_name_equal(struct ast_Module * module, int32_t imp_ix, uint8_t * nm, int32_t nm_len);
extern int32_t typeck_module_num_imports(struct ast_Module * module);
extern int typeck_var_is_import_visible_name(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int typeck_import_select_name_equal(struct ast_Module * module, int32_t imp_ix, int32_t sel, uint8_t * nm, int32_t nm_len);
extern int typeck_top_level_let_name_equal(struct ast_Module * module, int32_t tl_ix, uint8_t * nm, int32_t nm_len);
extern int32_t typeck_dep_module_const_idx_named(struct ast_Module * module, uint8_t * nm, int32_t nlen, int32_t tl_ix);
extern int32_t typeck_find_import_const_dep_index(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * nm, int32_t nlen, int32_t dep_ix);
extern int32_t typeck_import_last_segment_into(struct ast_Module * module, int32_t imp_ix, uint8_t * out);
extern int32_t typeck_resolve_dep_index_for_import(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix);
extern int32_t typeck_import_const_binding_hint_at(struct ast_Module * module, int32_t dep_ix, uint8_t * out);
extern int32_t typeck_reject_bare_import_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, uint8_t * vbuf, int32_t vnlen);
extern int32_t typeck_find_layout_idx_by_type_name(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_named_builtin_align(uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_named_builtin_size(uint8_t * nm, int32_t nlen);
extern int32_t typeck_x_type_align(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_type_is_empty_struct(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_x_type_size(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_soa_find_layout_idx_by_name(struct ast_Module * module, uint8_t * name, int32_t name_len);
extern int32_t typeck_soa_find_layout_module_and_idx(struct ast_Module * module, uint8_t * name, int32_t name_len, struct ast_Module * * out_layout_mod);
extern int32_t typeck_soa_col_base_for_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t field_idx, int32_t array_len, int32_t depth);
extern int32_t typeck_soa_field_soa_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref);
extern int32_t typeck_soa_array_storage_size_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t elem_type_ref, int32_t array_len, int32_t depth);
extern int32_t typeck_struct_layout_metrics(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth, int32_t check_pad, int32_t * out_sz, int32_t * out_al);
extern int32_t typeck_validate_struct_layouts_zero_padding(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t typeck_get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_get_field_type_ref_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_get_field_offset_from_layout_deps(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref);
extern void typeck_soa_fill_field_access_for_asm_emit(struct ast_Module * module, struct ast_ASTArena * arena);
extern void typeck_field_prebind(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_field_known_ptr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, int32_t num_struct_layouts);
extern int32_t typeck_dep_top_level_const_match(struct ast_Module * dep_mod, uint8_t * name, int32_t name_len, int32_t * out_type_ref);
extern int32_t typeck_field_import_try_dep_enum_type(struct ast_Module * dep_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, uint8_t * base_name, int32_t base_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_field_import_binding(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_field_import_const_is_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_field_reverse_infer_base_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t outer_expected);
extern int32_t typeck_named_last_segment_off(uint8_t * name, int32_t name_len);
extern int32_t typeck_named_spelling_eq(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len);
extern int32_t typeck_named_is_module_concrete(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * name, int32_t name_len);
extern int32_t typeck_mono_field_type_from_base(struct ast_Module * module, struct ast_ASTArena * arena, int32_t field_ty, int32_t base_ty);
extern int32_t typeck_field_unknown_hard_fail(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern void typeck_field_apply_mono_type_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty);
extern void typeck_field_apply_ambient_for_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t ambient_ty, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_field_layout_named(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern void typeck_field_slice(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref);
extern void typeck_field_name_fallback(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref);
extern void typeck_field_lexer_fallback(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern int typeck_expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index);
extern int32_t typeck_find_or_alloc_named_type_ref(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t typeck_field_access_lexer_wrapper_fallback(struct ast_ASTArena * arena, int32_t base_type_ref, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_ensure_primitive_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord);
extern int32_t typeck_ensure_i32_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_u8_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_bool_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_f32_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_f64_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_usize_type_ref(struct ast_ASTArena * arena);
extern int32_t typeck_ensure_void_type_ref(struct ast_ASTArena * a);
extern int32_t typeck_map_import_binding_named_to_caller(struct ast_Module * entry_mod, int32_t dep_ix, struct ast_ASTArena * caller_arena, uint8_t * nm, int32_t nlen);
extern int32_t typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_ensure_i64_type_ref(struct ast_ASTArena * caller_arena);
extern int32_t typeck_find_or_alloc_compound_type_ref(struct ast_ASTArena * a, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t typeck_find_or_alloc_array_type_ref(struct ast_ASTArena * a, int32_t elem_ref, int32_t array_size);
extern int32_t typeck_ensure_array_type_ref_named_elem(struct ast_ASTArena * a, uint8_t * elem_nm, int32_t elem_nm_len, int32_t array_size);
extern int32_t typeck_ensure_kind_only_type_ref(struct ast_ASTArena * w, enum ast_TypeKind kind);
extern int32_t typeck_find_or_alloc_ptr_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t typeck_find_or_alloc_slice_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t typeck_find_or_alloc_linear_type_ref(struct ast_ASTArena * w, int32_t elem_ref);
extern int32_t typeck_find_or_alloc_vector_type_ref(struct ast_ASTArena * w, int32_t elem_ref, int32_t array_size);
extern int32_t typeck_dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena);
extern int32_t typeck_expr_field_access_fallback_scalar_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_get_field_type_ref_from_layout_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_inline_u8_64_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_expr_inline_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len);
extern int32_t typeck_entry_module_find_struct_layout_index(struct ast_Module * mod, uint8_t * nm, int32_t nlen);
extern void typeck_merge_dep_struct_layouts_into_entry(struct ast_Module * mod, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern void typeck_wpo_unify_soa_layouts(struct ast_Module * entry, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_resolve_scan_dep_with_apply(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax, int32_t want_apply);
extern int32_t typeck_find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_find_func_return_type_in_module_by_name(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_overload_arg_param_score(struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t arg_i, int32_t param_ty_raw, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_find_func_return_type_in_module_by_name_overload(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_find_func_return_type_in_module_overload(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_import_path_segment_count(uint8_t * path, int32_t path_len);
extern int typeck_import_segment_at(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen);
extern int32_t typeck_resolve_whole_import_qualified_call_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t typeck_resolve_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t typeck_resolve_method_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern int32_t typeck_resolve_call_select_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t typeck_resolve_call_callee_try_whole_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord);
extern int32_t typeck_resolve_call_callee_try_binding_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord);
extern int32_t typeck_resolve_call_callee_local_module(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_resolve_call_callee_scan_dep(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax);
extern int32_t typeck_resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern int typeck_type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref);
extern int typeck_type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_named_unqual_start(uint8_t * buf, int32_t len);
extern int32_t typeck_type_ref_mangle_suffix(struct ast_ASTArena * arena, int32_t type_ref, uint8_t * buf, int32_t buf_cap);
extern int32_t typeck_named_inst_mangle_into(struct ast_ASTArena * arena, int32_t ty, uint8_t * out, int32_t out_cap);
extern int typeck_type_refs_equal_named(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int typeck_type_refs_equal_same_kind(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord);
extern int typeck_type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int typeck_type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int typeck_integer_widen_ok(int32_t dest_kind, int32_t src_kind);
extern int32_t typeck_int_family_id(struct ast_ASTArena * arena, int32_t type_ref);
extern int typeck_integer_widen_ok_refs(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref);
extern int typeck_float_widen_ok(int32_t dest_kind, int32_t src_kind);
extern int32_t typeck_is_fnptr_surface(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_fn_type_sig_equal(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t typeck_module_func_matches_type_fn(struct ast_Module * module, struct ast_ASTArena * arena, int32_t fi, int32_t expect_fn);
extern int32_t typeck_fnptr_surface_compat(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expect_ty, int32_t got_ty, int32_t got_expr, int32_t allow_opaque);
extern int32_t typeck_method_call_field_fnptr_ty(struct ast_Module * module, struct ast_ASTArena * arena,
    struct ast_PipelineDepCtx * ctx, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen);
extern int32_t typeck_dyn_rhs_is_null_sentinel(struct ast_ASTArena * arena, int32_t rhs_type_ref, int32_t rhs_expr_ref);
extern int32_t typeck_array_to_slice_ok(struct ast_ASTArena * arena, int32_t src_ty, int32_t dest_ty);
extern int typeck_return_operand_matches(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern int32_t typeck_expr_is_null_keyword(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_coerce_init_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_float_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern void typeck_stamp_resolved_args_float_lit(struct ast_ASTArena * arena, int32_t expr_ref, struct ast_Module * callee_mod, int32_t func_ix, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t param_base);
extern int32_t typeck_coerce_init_enum_field_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_named_call_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_resolved_alias_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t typeck_coerce_array_lit_elem_types_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_vector_lanes_of_type(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_coerce_init_array_vector_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_vector_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_int_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_bool_to_int_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t typeck_coerce_init_array_lit_to_len_int_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t typeck_coerce_init_slice_from_array(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t typeck_coerce_array_lit_struct_elems_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_coerce_init_expr_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_coerce_init_struct_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t typeck_diag_append_lit(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len);
extern int32_t typeck_diag_append_u32_dec(uint8_t * out, int32_t pos, int32_t cap, int32_t v);
extern int32_t typeck_diag_fmt_type_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap);
extern int32_t typeck_diag_fmt_type_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap);
extern int32_t typeck_diag_fmt_type_or_question(struct ast_ASTArena * arena, int32_t ref, uint8_t * out);
extern void typeck_ret_coerce_integral_to_expect_i32(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_coerce_integral_widen(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_coerce_null_lit_to_expect(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void typeck_ret_fixup_unresolved_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_return_breadcrumb_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern void typeck_emit_return_subexpr_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col);
extern void typeck_emit_return_unresolved_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col);
extern int32_t typeck_check_expr_float_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_int_lit(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref);
extern int32_t typeck_check_expr_bool_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_string_lit(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_break_continue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_check_expr_if_ternary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_block_expr_value_ref(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t typeck_check_expr_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_panic(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_match_arm(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arm_i, int32_t num_arms, int32_t line, int32_t col);
extern int32_t typeck_check_expr_match(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_try_propagate(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args);
extern int32_t typeck_check_expr_call_resolve(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_call_arity_compatible(struct ast_Module * module, int32_t fi, int32_t num_args);
extern int32_t typeck_check_call_arity(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_named_is_module_type(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t typeck_type_is_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_type_tree_has_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth);
extern int32_t typeck_generic_formal_matches_arg_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t formal_ty, int32_t arg_ty, int32_t depth);
extern int32_t typeck_call_is_fmt_debug_print_any(struct ast_Module * mod, int32_t fi, int32_t dep, struct ast_PipelineDepCtx * ctx, int32_t num_args);
extern int32_t typeck_check_call_arg_types(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_match_subject_field_type(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t typeck_call_arg_repr_compatible_ok(struct ast_Module * module, struct ast_ASTArena * arena, int32_t param_ref, int32_t arg_ref);
extern int32_t typeck_is_cap_va_builtin_name(uint8_t * name, int32_t name_len);
extern int32_t typeck_check_extern_call_unsafe_boundary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern void typeck_expr_diag_line_col(struct ast_ASTArena * arena, int32_t expr_ref, int32_t * line_out, int32_t * col_out);
extern int32_t typeck_slice_region_escape(struct ast_ASTArena * arena, int32_t expect_ref, int32_t src_ref);
extern int32_t typeck_slice_region_conflict(struct ast_ASTArena * arena, int32_t expect_ref, int32_t src_ref);
extern int32_t typeck_check_slice_region_assign(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref);
extern int32_t typeck_check_return_slice_region(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref);
extern int32_t typeck_ptr_has_stack_local_label(struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_block_tree_has_var(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern int32_t typeck_var_is_block_local(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t expr_ref);
extern int32_t typeck_expr_is_addr_of_block_local(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t expr_ref);
extern int32_t typeck_lval_is_param_ptr_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t func_ix, int32_t left_ref, int32_t dst_pi);
extern int32_t typeck_block_is_strict_ancestor(struct ast_ASTArena * arena, int32_t ancestor, int32_t descendant);
extern int32_t typeck_expr_lval_root_var(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out, int32_t * out_len);
extern int32_t typeck_check_struct_stack_escape_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_scope_borrow_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_scope_borrow_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t op_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_type_is_allocator_struct(struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_check_allocator_region_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_allocator_region_return(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref);
extern int32_t typeck_check_call_ptr_struct_compat(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t param_ref, int32_t arg_ref);
extern int32_t typeck_check_call_slice_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_type_is_aggregate_cmp_operand(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_check_expr_binop_cmp(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_binop_arith(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_binop(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_field_access(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_unary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_addr_of(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_deref(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_var_top_level(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * vbuf, int32_t vnlen, int32_t tl);
extern int32_t typeck_check_expr_var(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_method_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args);
extern int32_t typeck_method_call_resolve_generic_bound(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args);
extern int32_t typeck_check_expr_method_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_as_cast_type_class_ok(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_as_cast_allowed(struct ast_Module * module, struct ast_ASTArena * arena, int32_t src_ty, int32_t tgt_ty);
extern int32_t typeck_check_expr_as(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_struct_lit_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t field_i, int32_t num_fields);
extern int32_t typeck_coerce_struct_lit_field_inits_to_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty);
extern int32_t typeck_check_expr_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_vector_elem_type_ref(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t typeck_type_is_valid_subscript_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref);
extern int32_t typeck_check_expr_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int typeck_expr_is_any_assign_kind(int32_t kind_ord);
extern int32_t typeck_check_expr_array_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_impl_mega(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_func_body_tail_expr_ref_for_implicit_rule(struct ast_ASTArena * arena, int32_t body_ref);
extern int typeck_func_body_has_implicit_return_tail(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t typeck_loop_depth_push(struct ast_PipelineDepCtx * ctx);
extern void typeck_loop_depth_pop(struct ast_PipelineDepCtx * ctx, int32_t saved);
extern int32_t typeck_check_block_as_loop_body(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_block_one_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_let(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_while(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_for(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_one_if(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_void_reject_value_expr(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref);
extern int32_t typeck_check_block_final(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t fin0);
extern int32_t typeck_check_block_one_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t typeck_check_block_stmt_order_one(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t si, int32_t nso, int32_t nc, int32_t nl, int32_t nes, int32_t nlp, int32_t nfp, int32_t nif, int32_t nreg);
extern int32_t typeck_check_block_legacy_consts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nc);
extern int32_t typeck_check_block_legacy_lets(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nl);
extern int32_t typeck_check_block_legacy_whiles(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nlp);
extern int32_t typeck_check_block_legacy_fors(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nfp);
extern int32_t typeck_check_block_legacy_ifs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nif);
extern int32_t typeck_check_block_legacy_expr_stmts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nes);
extern int32_t typeck_check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast_check_one_func(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_idx);
extern int32_t typeck_x_ast_check_all_funcs_loop(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_i, int32_t num_funcs);
extern void typeck_patch_all_body_parent_links(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t typeck_x_ast_check_one_top_level_let(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t tl);
extern int32_t typeck_x_ast_check_top_level_lets(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast_library(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_x_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_field_import_binding_resolve_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_field_layout_named_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_field_unknown_hard_fail_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_named_is_module_concrete_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_with_arena_scope_n_at(void);
extern int32_t pipeline_typeck_with_arena_current_body_ref_c(void);
extern void pipeline_typeck_with_arena_scope_push_c(int32_t body_ref);
extern void pipeline_typeck_with_arena_scope_pop_c(void);
extern void pipeline_typeck_with_arena_scope_reset_c(void);
extern int32_t pipeline_dep_ctx_scope_region_push_c(struct ast_PipelineDepCtx * ctx, uint8_t * label, int32_t label_len);
extern void pipeline_dep_ctx_scope_region_pop_c(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_scope_region_len_at(struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_region_scope_reset_c(void);
extern int32_t typeck_scan_expr_stack_escape_c(struct ast_Module * m, struct ast_ASTArena * a, struct ast_PipelineDepCtx * ctx, int32_t func_ix, int32_t expr_ref);
extern int32_t typeck_scan_block_stack_escape_c(struct ast_Module * m, struct ast_ASTArena * a, struct ast_PipelineDepCtx * ctx, int32_t func_ix, int32_t block_ref);
extern int32_t pipeline_typeck_scan_module_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_is_read_ptr_slice_callee_c(uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_is_simd_comptime_callee_c(uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_read_ptr_slice_return_ref_c(struct ast_ASTArena * arena);
extern int32_t pipeline_type_stamp_block_let_region_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_block_one_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_call_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_ptr_for_addr_of_operand_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_return_slice_region_in_scope_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_resolve_call_callee_return_type_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t typeck_module_func_overload_count(struct ast_Module * m, uint8_t * name, int32_t name_len);
extern int32_t typeck_pick_overload_func_index_for_call(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref);
extern int32_t typeck_resolve_call_func_index_for_emit(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref);
extern int32_t pipeline_typeck_pick_overload_func_index_for_call_c(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref);
extern int32_t pipeline_typeck_resolve_call_func_index_for_emit_c(uint8_t * m, uint8_t * a, int32_t call_expr_ref);
extern int32_t typeck_call_arg_effective_type(struct ast_ASTArena * arena, int32_t arg_ref);
extern int32_t pipeline_typeck_named_is_module_type_c(struct ast_Module * m, struct ast_ASTArena * a, uint8_t * nm, int32_t nlen);
extern int32_t pipeline_typeck_call_arg_effective_type_c(struct ast_ASTArena * a, int32_t arg_ref);
extern int32_t glue_typeck_type_tree_has_free_param_c(struct ast_Module * mod, struct ast_ASTArena * arena, int32_t ty, int32_t depth);
extern int32_t typeck_try_infer_generic_call_from_args(struct ast_Module * callee_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t func_ix, int32_t expected_ret);
extern int32_t typeck_check_inferred_generic_bounds(struct ast_Module * callee_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t func_ix, uint8_t * fn_name, int32_t fn_name_len, int32_t line, int32_t col, int32_t expected_ret);
extern int32_t typeck_check_call_generic_type_args(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern int32_t pipeline_typeck_check_call_generic_type_args_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern int32_t typeck_mono_map_lookup(uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, uint8_t * nm, int32_t nlen);
extern int32_t typeck_mono_map_bind(uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, uint8_t * nm, int32_t nlen, int32_t concrete_ty, struct ast_ASTArena * caller_arena);
extern int32_t typeck_named_num_type_args_ASTArena_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t ty);
extern int32_t typeck_alloc_named_with_type_args_flat(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len, int32_t * arg_refs, int32_t n_args);
extern int32_t typeck_pattern_unify_bind(struct ast_Module * mod, struct ast_ASTArena * formal_arena, int32_t formal_ty, struct ast_ASTArena * arg_arena, int32_t arg_ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, int32_t depth);
extern int32_t typeck_build_value_formal_mono_map(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t max_map);
extern int32_t typeck_subst_type_ref(struct ast_Module * mod, struct ast_ASTArena * src_arena, struct ast_ASTArena * dst_arena, int32_t ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, int32_t depth);
extern int32_t glue_typeck_pattern_unify_bind_c(struct ast_Module * mod, struct ast_ASTArena * formal_arena, int32_t formal_ty, struct ast_ASTArena * arg_arena, int32_t arg_ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, int32_t depth);
extern int32_t glue_typeck_subst_type_ref_c(struct ast_Module * mod, struct ast_ASTArena * src_arena, struct ast_ASTArena * dst_arena, int32_t ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, int32_t depth);
extern int32_t glue_typeck_build_value_formal_mono_map_c(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t max_map);
extern int32_t typeck_generic_call_subst_ret_from_formal_map(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, int32_t ret_ty);
extern int32_t typeck_method_call_generic_ufcs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args);
extern int32_t typeck_generic_call_fixup_resolved_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern int32_t pipeline_typeck_method_call_generic_ufcs_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args);
extern int32_t glue_generic_call_fixup_resolved_type_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern void pipeline_typeck_set_entry_module_for_dep_map_c(struct ast_Module * module);
extern int32_t pipeline_typeck_get_dep_return_type_in_caller_arena_c(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_dep_return_type_to_caller_arena_c(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena);
extern int32_t pipeline_typeck_expr_var_name_equal_func_c(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index);
extern int32_t pipeline_typeck_find_func_return_type_in_module_by_name_c(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, int32_t want_arity, int32_t call_expr_ref, int32_t is_method, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t pipeline_typeck_find_func_return_type_in_module_by_name_strict_minimal(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, int32_t want_arity, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t pipeline_typeck_find_func_return_type_in_module_c(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out);
extern int32_t pipeline_typeck_block_const_init_is_const_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx);
extern void pipeline_typeck_const_init_not_constant_c(int32_t line, int32_t col);
extern void pipeline_typeck_fold_expr_c(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_typeck_fold_block_const_init_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx);
extern void pipeline_typeck_fold_expr_in_block_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t expr_ref);
extern int32_t pipeline_expr_is_c_static_const_init(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_check_expr_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_diag_append_lit_c(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len);
extern int32_t pipeline_typeck_diag_append_u32_dec_c(uint8_t * out, int32_t pos, int32_t cap, int32_t v);
extern int32_t pipeline_typeck_diag_fmt_type_at_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap);
extern int32_t pipeline_typeck_diag_fmt_type_into_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap);
extern int32_t pipeline_typeck_diag_fmt_type_or_question_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out);
extern int32_t pipeline_typeck_check_slice_region_assign_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref);
extern int32_t pipeline_typeck_check_struct_stack_escape_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_scope_borrow_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_scope_borrow_return_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t op_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_allocator_region_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_allocator_region_return_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref);
extern int32_t pipeline_typeck_check_return_slice_region_c(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref);
extern int32_t pipeline_typeck_check_call_slice_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_coerce_init_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_float_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_enum_field_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_named_call_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_array_vector_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_vector_binop_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_int_binop_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind);
extern int32_t pipeline_typeck_coerce_init_struct_lit_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t pipeline_typeck_coerce_init_slice_from_array_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind);
extern int32_t pipeline_typeck_coerce_init_expr_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref);
extern int32_t pipeline_typeck_float_widen_ok_c(int32_t dest_kind, int32_t src_kind);
extern int32_t pipeline_typeck_integer_widen_ok_c(int32_t dest_kind, int32_t src_kind);
extern int32_t pipeline_typeck_integer_widen_ok_refs_c(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref);
extern int32_t pipeline_typeck_type_refs_equal_named_c(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t pipeline_typeck_resolve_type_alias_ref_c(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_typeck_type_refs_equal_impl_c(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t pipeline_typeck_type_refs_equal_c(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t pipeline_typeck_type_refs_equal_same_kind_c(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord);
extern int32_t pipeline_typeck_type_ref_is_bool_impl_c(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_typeck_type_ref_is_bool_c(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_typeck_expr_type_ref_impl_c(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_expr_type_ref_c(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_return_operand_matches_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void pipeline_typeck_ret_coerce_integral_to_expect_i32_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern void pipeline_typeck_ret_coerce_integral_widen_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref);
extern int32_t pipeline_typeck_check_expr_int_lit_c(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_expr_is_any_assign_kind_c(int32_t kind_ord);
extern int32_t pipeline_typeck_block_impl_bind_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern void pipeline_typeck_block_impl_restore_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref);
extern void pipeline_typeck_block_impl_touch_ctx_block_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern int32_t pipeline_typeck_loop_depth_push_c(struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_loop_depth_pop_c(struct ast_PipelineDepCtx * ctx, int32_t saved_loop_depth);
extern int32_t pipeline_dep_ctx_typeck_unsafe_depth_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_unsafe_depth_push_c(struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_unsafe_depth_pop_c(struct ast_PipelineDepCtx * ctx, int32_t saved_unsafe_depth);
extern void pipeline_typeck_loop_depth_set_c(struct ast_PipelineDepCtx * ctx, int32_t depth);
extern int32_t pipeline_typeck_check_block_impl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_block_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_block_as_loop_body_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_set_active_ctx_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern struct ast_PipelineDepCtx * pipeline_typeck_active_ctx_c(void);
extern void pipeline_typeck_linear_reset_c(void);
extern int32_t typeck_linear_name_already_moved(uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_linear_use_var_c(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_linear_accepts_init_c(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref);
extern int32_t pipeline_typeck_reject_addr_of_linear_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_func_body_tail_expr_ref_for_implicit_rule_c(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t pipeline_typeck_func_body_has_implicit_return_tail_c(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t pipeline_typeck_check_expr_method_call_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_expr_apply_call_resolve_c(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern int32_t pipeline_typeck_import_segment_at_c(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen);
extern int32_t pipeline_typeck_resolve_dep_index_for_import_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix);
extern int32_t pipeline_typeck_resolve_whole_import_call_ret_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
/* XLANG_ALLOW_LEGACY_EXTERN: pin twin of patch_typeck_gen_lang007.py
 * ALLOW_LEGACY_HELPERS (G.7 same semantics). The assemble path injects
 * these bodies into host-local typeck_gen.c after -E; Track L compiles
 * this pin directly. The marker keeps the archaeology patcher idempotent
 * (7.4.7: missing marker → double insert → g05 redefinition).
 * Default allow=0 keeps LANG-007 S0 enforcement via glue boundary. */
static int g_typeck_allow_legacy_extern_calls = 0;
int typeck_set_allow_legacy_extern_calls(int allow) {
  int old = g_typeck_allow_legacy_extern_calls;
  g_typeck_allow_legacy_extern_calls = allow ? 1 : 0;
  return old;
}
int typeck_get_allow_legacy_extern_calls(void) {
  return g_typeck_allow_legacy_extern_calls;
}
#undef g_typeck_prim_arena
static uint8_t * g_typeck_prim_arena = 0;
#undef g_typeck_prim_ref
static int32_t g_typeck_prim_ref[18];
#undef g_typeck_entry_module_for_dep_map
static struct ast_Module * g_typeck_entry_module_for_dep_map = 0;
#undef g_typeck_with_arena_body_stack
static int32_t g_typeck_with_arena_body_stack[8];
#undef g_typeck_with_arena_scope_n
static int32_t g_typeck_with_arena_scope_n = 0;
#undef g_typeck_region_saved_len
static int32_t g_typeck_region_saved_len[8];
#undef g_typeck_region_saved_label
static uint8_t g_typeck_region_saved_label[1024];
#undef g_typeck_region_scope_n
static int32_t g_typeck_region_scope_n = 0;
#undef g_typeck_unsafe_depth
static int32_t g_typeck_unsafe_depth = 0;
#undef g_typeck_linear_moved_n
static int32_t g_typeck_linear_moved_n = 0;
#undef g_typeck_linear_moved_names
static uint8_t g_typeck_linear_moved_names[16384];
#undef g_typeck_linear_moved_lens
static int32_t g_typeck_linear_moved_lens[128];
#undef g_typeck_active_ctx
static struct ast_PipelineDepCtx * g_typeck_active_ctx = 0;
static void init_globals(void) {
  g_typeck_prim_arena = 0;
  g_typeck_entry_module_for_dep_map = 0;
  g_typeck_with_arena_scope_n = 0;
  g_typeck_region_scope_n = 0;
  g_typeck_unsafe_depth = 0;
  g_typeck_linear_moved_n = 0;
  g_typeck_active_ctx = 0;
}
extern int32_t typeck_float64_bits_lo(double d);
extern int32_t typeck_float64_bits_hi(double d);
extern int32_t xlang_skip_impl_concrete_implements_trait_c(void * arena, int32_t concrete_ty_ref, uint8_t * trait_nm, int32_t trait_nlen);
extern int32_t xlang_skip_trait_method_slot_c(uint8_t * trait_nm, int32_t trait_nlen, uint8_t * method_nm, int32_t method_nlen);
extern int32_t xlang_skip_trait_method_count_c(uint8_t * trait_nm, int32_t trait_nlen);
extern int32_t xlang_skip_trait_method_name_into_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, uint8_t * out64);
extern int32_t xlang_skip_trait_method_ret_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_elem_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_array_size_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_array_ndims_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_array_dim_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t dim_ix);
extern int32_t xlang_skip_trait_method_ret_elem_elem_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_elem_array_ndims_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot);
extern int32_t xlang_skip_trait_method_ret_elem_array_dim_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t dim_ix);
extern int32_t xlang_skip_trait_method_ret_name_into_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, uint8_t * out64);
extern int32_t xlang_skip_trait_method_param_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix);
extern int32_t xlang_skip_trait_method_param_elem_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix);
extern int32_t xlang_skip_trait_method_param_name_into_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix, uint8_t * out64);
extern int32_t xlang_skip_trait_method_param_array_ndims_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix);
extern int32_t xlang_skip_trait_method_param_array_dim_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix, int32_t dim_ix);
extern int32_t xlang_skip_trait_method_param_elem_elem_kind_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix);
extern int32_t xlang_skip_trait_method_param_elem_array_ndims_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix);
extern int32_t xlang_skip_trait_method_param_elem_array_dim_c(uint8_t * trait_nm, int32_t trait_nlen, int32_t slot, int32_t param_ix, int32_t dim_ix);
extern void driver_diagnostic_typeck_func_fail(int32_t func_idx, uint8_t * name, int32_t name_len, int32_t kind);
extern void pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t depth);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t parser_get_module_num_imports(struct ast_Module * module);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_current_func_index(struct ast_PipelineDepCtx * ctx, int32_t ix);
extern int32_t pipeline_typeck_check_expr_impl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_impl_mega_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_method_call_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_expr_apply_call_resolve_c_ASTArena_ptr_i32_i32_i32(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern int32_t pipeline_typeck_import_segment_at_c_Module_ptr_i32_i32_i32_ptr_i32_ptr_reti32(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen);
extern int32_t pipeline_typeck_resolve_dep_index_for_import_c_Module_ptr_PipelineDepCtx_ptr_i32_reti32(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix);
extern int32_t pipeline_typeck_resolve_whole_import_call_ret_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_ptr_i32_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out);
extern void pipeline_expr_init_call_resolve_at_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_typeck_check_expr_try_propagate_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_expr_match_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_match_set_subject_c(struct ast_Module * module, int32_t ty);
extern void pipeline_typeck_match_clear_subject_c(void);
extern int32_t pipeline_typeck_match_subject_ty_get_c(void);
extern struct ast_Module * pipeline_typeck_match_subject_mod_get_c(void);
extern int32_t typeck_type_is_named_struct_c(uint8_t * m, uint8_t * a, int32_t ty_ref);
extern int32_t typeck_layout_index_for_named_type_c(uint8_t * m, uint8_t * a, int32_t ty_ref);
extern int32_t typeck_struct_layouts_same_shape_c(uint8_t * m, uint8_t * a, int32_t la, int32_t lb);
extern int32_t pipeline_module_struct_layout_repr_compatible_at(struct ast_Module * module, int32_t idx);
extern int32_t glue_module_func_index_by_name_c(uint8_t * mod, uint8_t * name, int32_t name_len);
extern int32_t typeck_get_allow_legacy_extern_calls(void);
extern void driver_diagnostic_typeck_extern_call_outside_unsafe(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_try_propagate_bad_enclosing(int32_t line, int32_t col);
extern int32_t pipeline_typeck_check_expr_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_module_struct_layout_num_type_params_at(struct ast_Module * module, int32_t li);
extern int32_t pipeline_module_struct_layout_type_param_name_len(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_type_param_name_into(struct ast_Module * module, int32_t li, int32_t j, uint8_t * out);
extern void lsp_diag_report_typeck(int32_t line, int32_t col, uint8_t * msg);
extern int32_t pipeline_module_enum_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void driver_diagnostic_typeck_ptr_field(int32_t bt_kind, int32_t inner_kind, int32_t inner_nlen, int32_t base_resolved_ref, int32_t num_struct_layouts);
extern int32_t pipeline_type_named_name_into(struct ast_ASTArena * arena, int32_t type_ref, uint8_t * out);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_type_array_size_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_type_elem_ref_at(struct ast_ASTArena * arena, int32_t type_ref);
extern int32_t pipeline_type_type_arg_ref_at(struct ast_ASTArena * arena, int32_t type_ref, int32_t idx);
extern int32_t pipeline_type_append_type_arg(struct ast_ASTArena * arena, int32_t type_ref, int32_t arg_ref);
extern int32_t pipeline_type_set_elem_array_size_at(struct ast_ASTArena * arena, int32_t type_ref, int32_t elem_ref, int32_t array_size);
extern int32_t pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(struct ast_ASTArena * arena, int32_t a, int32_t b);
extern int32_t typeck_named_num_type_args_ASTArena_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t ty);
extern int32_t pipeline_typeck_call_arg_repr_compatible_ok_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t param_ref, int32_t arg_ref);
extern int32_t pipeline_typeck_check_extern_call_unsafe_boundary_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_match_subject_field_type_c(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern struct ast_Module * pipeline_typeck_active_module_c(void);
extern int32_t pipeline_module_num_type_aliases_at(struct ast_Module * module);
extern int32_t pipeline_module_type_alias_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_type_alias_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_type_alias_target_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_typeck_func_body_has_implicit_return_tail_c_ASTArena_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t body_ref);
extern int32_t pipeline_expr_binop_left_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_binop_right_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void driver_diagnostic_typeck_block_enter(int32_t func_idx, int32_t block_ref, int32_t n_const, int32_t n_let, int32_t n_loop, int32_t n_for, int32_t n_expr, int32_t final_ref);
extern void driver_diagnostic_typeck_fn_enter(int32_t func_idx, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_ret_fail(int32_t stage, int32_t op_expr_ref, int32_t expect_ty_ref, int32_t got_ty_ref);
extern void driver_diagnostic_typeck_binop_operands(int32_t expr_ref, int32_t left_ref, int32_t right_ref, int32_t left_kind, int32_t right_kind, int32_t left_block_ref, int32_t right_block_ref, int32_t left_ty_ref, int32_t right_ty_ref, uint8_t * left_ty, int32_t left_ty_len, uint8_t * right_ty, int32_t right_ty_len);
extern void driver_diagnostic_typeck_return_mismatch(int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_return_unresolved(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_return_subexpr(int32_t line, int32_t col, uint8_t * expr_buf, int32_t expr_len);
extern void driver_diagnostic_typeck_assign_mismatch(int32_t is_compound, int32_t line, int32_t col, uint8_t * expect_buf, int32_t expect_len, uint8_t * found_buf, int32_t found_len);
extern void driver_diagnostic_typeck_import_const_must_be_qualified(int32_t line, int32_t col, uint8_t * name, int32_t name_len, uint8_t * binding, int32_t binding_len);
extern void driver_diagnostic_typeck_subscript_base(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_break_continue_outside(int32_t line, int32_t col, int32_t is_break);
extern void driver_diagnostic_typeck_invalid_ptr_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_float_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_aggregate_cmp(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_as_cast(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_arity_mismatch(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_arg_type_mismatch(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_unresolved(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_call_not_generic(int32_t line, int32_t col, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_call_requires_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len);
extern void driver_diagnostic_typeck_call_wrong_num_type_args(int32_t line, int32_t col, uint8_t * name, int32_t name_len, int32_t expect_n, int32_t got_n);
extern int32_t xlang_generic_bound_check_type_args_c(uint8_t * fn_name, int32_t fn_name_len, uint8_t * type_args, int32_t * type_arg_lens, int32_t nargs, int32_t line, int32_t col);
extern int32_t pipeline_expr_call_num_type_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void driver_diagnostic_typeck_subscript_index(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_logical_operand_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_comparison_type_mismatch(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_void_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_invalid_bool_binop(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_assign_to_const(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_duplicate_local(int32_t line, int32_t col);
extern int32_t pipeline_block_name_binding_kind(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern int32_t pipeline_module_top_level_name_is_const(struct ast_Module * module, uint8_t * vname, int32_t vlen);
extern int32_t pipeline_block_local_name_redecl_c(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen, int32_t kind, int32_t idx, struct ast_Module * module, int32_t func_index);
extern int32_t pipeline_block_let_name_len(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern void pipeline_block_let_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t li, uint8_t * dst);
extern int32_t pipeline_block_const_name_len(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern void pipeline_block_const_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t ci, uint8_t * dst);
extern void typeck_driver_diagnostic_pipe_marker(int32_t id);
extern void driver_diagnostic_typeck_if_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_while_condition_not_bool(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_for_condition_not_bool(int32_t line, int32_t col);
extern uint8_t * driver_typeck_diag_scratch_expect(void);
extern uint8_t * driver_typeck_diag_scratch_found(void);
extern uint8_t * typeck_scratch64_slot(int32_t slot);
extern int32_t * typeck_layout_metrics_sz_slot(void);
extern int32_t * typeck_layout_metrics_al_slot(void);
extern int32_t * typeck_layout_metrics_sz_slot_depth(int32_t depth);
extern int32_t * typeck_layout_metrics_al_slot_depth(int32_t depth);
extern void typeck_i32_ptr_store(int32_t * p, int32_t v);
extern int32_t typeck_i32_ptr_read(int32_t * p);
extern int32_t * typeck_call_resolve_dep_idx_slot(void);
extern int32_t * typeck_call_resolve_func_idx_slot(void);
extern int32_t * typeck_overload_expected_ret_slot(void);
extern int32_t typeck_overload_expected_ret_peek(void);
extern int32_t typeck_call_resolve_dep_idx_peek(void);
extern int32_t typeck_call_resolve_func_idx_peek(void);
extern void typeck_binop_arith_infer_type_c(struct ast_ASTArena * arena, int32_t expr_ref, int32_t bop_l, int32_t bop_r, int32_t expr_kind);
extern void pipeline_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern void typeck_layout_metrics_init_depth(int32_t depth);
extern int32_t typeck_layout_metrics_al_read_depth(int32_t depth);
extern int32_t typeck_layout_metrics_sz_read_depth(int32_t depth);
extern void typeck_layout_metrics_init_slot(void);
extern int32_t typeck_x_type_align_from_layout_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth);
extern int32_t typeck_x_type_size_from_layout_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth);
extern struct ast_PipelineDepCtx * pipeline_asm_emit_dep_pipe_c(void);
extern int32_t pipeline_asm_emit_func_index_c(void);
extern void pipeline_asm_emit_set_func_index(int32_t func_index);
extern void pipeline_expr_set_field_access_soa_stride(struct ast_ASTArena * arena, int32_t expr_ref, int32_t stride);
extern int32_t pipeline_expr_field_access_soa_stride(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_debug_trace_named_func_bodies(uint8_t * phase, struct ast_Module * module, struct ast_ASTArena * arena);
extern void glue_sync_struct_layout_field_offsets_c(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t glue_struct_layout_field_offset_by_name_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, uint8_t * field_name, int32_t flen);
extern void glue_fill_var_types_from_lets_in_block(struct ast_ASTArena * arena, int32_t block_ref);
extern void glue_fill_var_types_from_params_for_func(struct ast_Module * module, struct ast_ASTArena * arena, int32_t func_index);
extern int32_t glue_field_layout_offset_for_base_field(struct ast_ASTArena * arena, struct ast_Module * module, int32_t base_ref, uint8_t * field_name, int32_t flen);
extern struct ast_ASTArena * pipeline_get_dep_arena_slot(int32_t ix);
extern int32_t pipeline_module_func_param_type_ref_for_name(struct ast_Module * module, int32_t func_index, uint8_t * vname, int32_t vname_len);
extern int32_t pipeline_module_num_funcs(struct ast_Module * module);
extern int32_t pipeline_module_main_func_index(struct ast_Module * module);
extern int32_t pipeline_module_func_is_extern_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_body_ref_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_len_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_name_copy64(struct ast_Module * module, int32_t fi, uint8_t * dst);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern void pipeline_module_func_set_is_used(struct ast_Module * module, int32_t fi, int32_t is_used);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t layout_idx, int32_t j, uint8_t * fname, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_struct_layout_next_field_offset(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module * module, int32_t layout_idx, int32_t j, uint8_t * out);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t layout_idx, int32_t j);
extern void pipeline_module_struct_layout_name_into(struct ast_Module * module, int32_t idx, uint8_t * out);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t layout_idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t layout_idx, int32_t nf);
extern int32_t pipeline_expr_struct_lit_num_fields(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_struct_lit_type_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_struct_lit_type_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern void pipeline_expr_struct_lit_type_name_set(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_expr_struct_lit_field_name_len(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j);
extern void pipeline_expr_struct_lit_field_name_into(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j, uint8_t * out);
extern int32_t pipeline_expr_struct_lit_init_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t j);
extern int32_t pipeline_expr_resolved_type_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_resolved_type_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t type_ref);
extern void pipeline_expr_typeck_set_float_bits_from_val(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_line_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_col_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_dep_ctx_typeck_loop_depth_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_current_block_ref_at(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_current_func_index(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_block_impl_bind_ctx_c_PipelineDepCtx_ptr_i32_reti32(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern void pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref);
extern void pipeline_typeck_block_impl_touch_ctx_block_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
extern int32_t pipeline_expr_int_val_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int64_t pipeline_expr_int64_val_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_field_access_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t tag);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_guard_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_matched_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_module_enum_variant_tag_for_names(struct ast_Module * m, uint8_t * enum_name, int32_t enum_len, uint8_t * variant_name, int32_t variant_len);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern void driver_diagnostic_typeck_enum_no_variant(int32_t line, int32_t col);
extern void driver_diagnostic_typeck_var_resolution(int32_t expr_ref, uint8_t * name, int32_t name_len, int32_t func_idx, int32_t block_ref, int32_t source, int32_t type_ref);
extern int32_t pipeline_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_type_init_primitive_kind_at(struct ast_ASTArena * arena, int32_t ref, int32_t kind_ord);
extern int32_t pipeline_type_init_named_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_type_init_compound_kind_at(struct ast_ASTArena * arena, int32_t ref, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t pipeline_type_ensure_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord);
extern int32_t pipeline_type_find_or_alloc_named(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len);
extern int32_t pipeline_type_find_or_alloc_compound(struct ast_ASTArena * arena, int32_t kind_ord, int32_t elem_ref, int32_t array_size);
extern int32_t pipeline_type_region_label_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out64);
extern int32_t pipeline_type_region_label_len_at(struct ast_ASTArena * arena, int32_t ref);
extern int32_t pipeline_type_set_region_label_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * label, int32_t label_len);
extern int32_t pipeline_type_find_or_alloc_slice(struct ast_ASTArena * arena, int32_t elem_ref, uint8_t * reg_label, int32_t reg_label_len);
extern int32_t pipeline_type_find_or_alloc_ptr(struct ast_ASTArena * arena, int32_t elem_ref, uint8_t * reg_label, int32_t reg_label_len);
extern int32_t pipeline_typeck_check_slice_region_assign_c_ASTArena_ptr_i32_i32_i32_reti32(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref);
extern int32_t pipeline_typeck_check_return_slice_region_c_ASTArena_ptr_i32_i32_i32_reti32(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref);
extern int32_t pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t glue_expr_kind_is_assign_like_ord(int32_t ko);
extern int32_t pipeline_typeck_check_extern_call_unsafe_boundary_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx);
extern void driver_diagnostic_typeck_deref_outside_unsafe(int32_t line, int32_t col);
extern int32_t pipeline_typeck_check_call_slice_region_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32(uint8_t * m, uint8_t * a, int32_t call_expr_ref);
extern int32_t pipeline_typeck_pick_overload_func_index_for_call_c_Module_ptr_ASTArena_ptr_i32_reti32(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref);
extern uint8_t * link_abi_getenv(uint8_t * name);
extern int32_t pipeline_typeck_check_call_generic_type_args_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern int32_t glue_generic_call_fixup_resolved_type_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
extern int32_t pipeline_typeck_method_call_generic_ufcs_c_Module_ptr_ASTArena_ptr_i32_i32_u8_ptr_i32_i32_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args);
extern void pipeline_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern int32_t pipeline_expr_call_type_arg_ref_at(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t xlang_generic_func_type_param_index_c(uint8_t * fn_name, int32_t fn_name_len, uint8_t * tp_name, int32_t tp_name_len);
extern int32_t xlang_generic_bound_method_on_param_c(uint8_t * fn_name, int32_t fn_name_len, uint8_t * tp_name, int32_t tp_name_len, uint8_t * method_name, int32_t method_name_len, int32_t num_args, int32_t * out_ret_kind, uint8_t * out_ret_name, int32_t * out_ret_name_len);
extern int32_t pipeline_typeck_resolve_call_callee_return_type_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_type_stamp_block_let_region_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32(uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_read_ptr_slice_return_ref_c_ASTArena_ptr_reti32(struct ast_ASTArena * arena);
extern int32_t pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32(uint8_t * name, int32_t name_len);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_set_let_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t li, int32_t type_ref);
extern int32_t pipeline_typeck_check_block_one_region_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_call_struct_stack_escape_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_block_region_is_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern int32_t pipeline_block_region_with_arena_cap_ref(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern int32_t pipeline_block_region_label_len(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern void pipeline_block_region_label_copy64(struct ast_ASTArena * arena, int32_t br, int32_t ri, uint8_t * dst);
extern int32_t pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32(struct ast_PipelineDepCtx * ctx);
extern void pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t saved);
extern int32_t pipeline_module_func_num_generic_params_at(struct ast_Module * module, int32_t fi);
extern void pipeline_typeck_linear_reset_c(void);
extern int32_t pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len);
extern int32_t pipeline_typeck_linear_accepts_init_c_ASTArena_ptr_i32_i32_reti32(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref);
extern int32_t pipeline_typeck_reject_addr_of_linear_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern void driver_diagnostic_typeck_linear_addr_of(int32_t line, int32_t col);
extern int32_t pipeline_typeck_ptr_for_addr_of_operand_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_struct_stack_escape_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_scope_borrow_assign_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_scope_borrow_return_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t op_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_allocator_region_assign_c_Module_ptr_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_typeck_check_allocator_region_return_c_ASTArena_ptr_i32_i32_reti32(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref);
extern int32_t pipeline_block_parent_block_ref_at(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_block_find_var_decl_block_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern int32_t glue_expr_is_func_param_at_c(struct ast_ASTArena * arena, struct ast_Module * mod, int32_t func_idx, int32_t expr_ref, int32_t param_ix);
extern int32_t pipeline_module_func_param_type_ref_at(struct ast_Module * module, int32_t fi, int32_t pi);
extern int32_t pipeline_module_func_num_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_expr_call_resolved_func_index_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_resolved_dep_index_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_block_set_const_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci, int32_t type_ref);
extern void pipeline_module_top_level_let_set_type_ref(struct ast_Module * module, int32_t idx, int32_t type_ref);
extern int32_t pipeline_module_top_level_let_init_ref(struct ast_Module * module, int32_t idx);
extern void typeck_fold_expr(struct ast_ASTArena * arena, int32_t expr_ref);
extern void typeck_fold_block_const_init(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx);
extern void typeck_fold_expr_in_block(struct ast_ASTArena * arena, int32_t block_ref, int32_t expr_ref);
extern int32_t typeck_block_const_init_is_const(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx);
extern void typeck_const_init_not_constant(int32_t line, int32_t col);
extern int32_t typeck_expr_is_c_static_const_init(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t typeck_expr_is_const_with_module_consts(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_if_cond_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_if_then_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_if_else_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_block_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_asm_block_final_expr_ref_at(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t block_ref, int32_t ei);
extern int32_t pipeline_block_set_parent_if_zero(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern int32_t pipeline_expr_unary_operand_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_callee_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_index_base_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_index_index_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_index_base_is_slice(struct ast_ASTArena * arena, int32_t expr_ref, int32_t v);
extern void pipeline_expr_set_index_proven_in_bounds(struct ast_ASTArena * arena, int32_t expr_ref, int32_t v);
extern int32_t pipeline_expr_as_operand_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_as_target_type_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_field_access_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern int32_t pipeline_expr_field_access_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_field_access_base_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_set_field_access_offset(struct ast_ASTArena * arena, int32_t expr_ref, int32_t offset);
extern void pipeline_expr_var_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern int32_t pipeline_expr_method_call_base_ref_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_method_call_name_len(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_method_call_name_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out64);
extern void asm_qual_sym_layer_reset(void);
extern int32_t asm_qual_sym_layer_push(uint8_t * bytes, int32_t len);
extern int32_t asm_qual_sym_layer_count(void);
extern int32_t asm_qual_sym_layer_len(int32_t i);
extern void asm_qual_sym_layer_copy(int32_t i, uint8_t * dst, int32_t cap);
extern void driver_diagnostic_typeck_struct_padding_before(uint8_t * sname, int32_t sname_len, int32_t gap, uint8_t * fname, int32_t fname_len);
extern void driver_diagnostic_typeck_struct_padding_trailing(uint8_t * sname, int32_t sname_len, int32_t gap);
extern void driver_diagnostic_typeck_struct_field_bad_size(uint8_t * sname, int32_t sname_len, uint8_t * fname, int32_t fname_len);
extern int32_t pipeline_module_num_struct_layouts_at(struct ast_Module * module);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t layout_idx, int32_t j);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_align_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_align(struct ast_Module * module, int32_t li, int32_t j, int32_t al);
extern int32_t pipeline_struct_layout_next_field_offset_ex(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref, int32_t field_align_req);
extern void pipeline_typeck_pad_fields_warn_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li);
extern void pipeline_typeck_hot_reorder_warn_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li);
extern int32_t pipeline_typeck_unused_binding_hints(struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t pipeline_typeck_wpo_dump_callgraph(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_struct_layout_allow_padding_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_packed_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_soa_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_import_path_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_import_kind_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_import_select_count_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_import_select_name_len(struct ast_Module * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(struct ast_Module * module, int32_t idx, int32_t sel, int32_t off);
extern int32_t pipeline_module_top_level_let_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_top_level_let_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_top_level_let_type_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_is_const(struct ast_Module * module, int32_t idx);
int32_t typeck_type_kind_ordinal(enum ast_TypeKind k) {
  int32_t o = ((int32_t)(k));
  int32_t lo = 0;
  int32_t hi = 18;
  if ((o < lo)) {
    return -1;
  }
  if ((o > hi)) {
    return -1;
  }
  return o;
}
int typeck_name_equal(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len) {
  if (((a_len !=b_len) || (a_len <=0))) {
    return 0;
  }
  int32_t i = 0;
  while ((i < a_len)) {
    if (((a)[i] !=(b)[i])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t typeck_resolve_type_alias_ref_local(struct ast_Module * module, struct ast_ASTArena * arena, int32_t type_ref, int32_t depth) {
  {
    uint8_t type_name[128] = {};
    int32_t alias_count = 0;
    int32_t alias_i = 0;
    int32_t type_name_len = 0;
    int32_t alias_name_len = 0;
    int32_t alias_off = 0;
    int32_t ord_named = 8;
    int32_t alias_target_ref = 0;
    int32_t max_depth = 32;
    if (((((module ==0) || (arena ==0)) || ast_ref_is_null(type_ref)) || (depth > max_depth))) {
      return type_ref;
    }
    if ((pipeline_type_kind_ord_at(arena, type_ref) !=ord_named)) {
      return type_ref;
    }
    (void)((type_name_len = pipeline_type_named_name_into(arena, type_ref, &((type_name)[0]))));
    if ((type_name_len <=0)) {
      return type_ref;
    }
    (void)((alias_count = pipeline_module_num_type_aliases_at(module)));
    while ((alias_i < alias_count)) {
      (void)((alias_name_len = pipeline_module_type_alias_name_len(module, alias_i)));
      if ((((alias_name_len ==type_name_len) && (alias_name_len > 0)) && (alias_name_len <=127))) {
        (void)((alias_off = 0));
        while ((alias_off < alias_name_len)) {
          if ((pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off) !=(type_name)[alias_off])) {
            break;
          }
          (void)((alias_off = (alias_off + 1)));
        }
        ((alias_off ==alias_name_len) ? ({   (void)((alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i)));
  if (ast_ref_is_null(alias_target_ref)) {
    return type_ref;
  }
  return typeck_resolve_type_alias_ref_local(module, arena, alias_target_ref, (depth + 1));
 }) : 0);
      }
      (void)((alias_i = (alias_i + 1)));
    }
    return type_ref;
  }
}
int32_t typeck_resolve_type_alias_ref(struct ast_ASTArena * arena, int32_t type_ref) {
  {
    struct ast_Module * mod = pipeline_typeck_active_module_c();
    int32_t peeled = typeck_resolve_type_alias_ref_local(mod, arena, type_ref, 0);
    return typeck_canonicalize_named_inst_if_present(arena, peeled);
  }
}
int32_t typeck_canonicalize_named_inst_if_present(struct ast_ASTArena * arena, int32_t ty) {
  {
    uint8_t mangled[128] = {};
    int32_t ml = 0;
    int32_t k = 0;
    int32_t ko = 0;
    int32_t exist_len = 0;
    uint8_t * nm_scr = typeck_scratch64_slot(13);
    int32_t uq = 0;
    int32_t ul = 0;
    int32_t i = 0;
    int32_t ord_named = 8;
    int32_t fam = 0;
    if (((arena ==0) || (ty <=0))) {
      return ty;
    }
    if ((pipeline_type_kind_ord_at(arena, ty) !=ord_named)) {
      return ty;
    }
    if ((typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, ty) <=0)) {
      return ty;
    }
    (void)((ml = typeck_named_inst_mangle_into(arena, ty, &((mangled)[0]), 128)));
    if ((ml <=0)) {
      return ty;
    }
    (void)((k = 1));
    while ((k <=((arena)->num_types))) {
      (void)((ko = pipeline_type_kind_ord_at(arena, k)));
      if (((ko ==ord_named) && (typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, k) ==0))) {
        (void)((exist_len = pipeline_type_named_name_into(arena, k, nm_scr)));
        if (((exist_len ==ml) && typeck_name_equal(nm_scr, exist_len, &((mangled)[0]), ml))) {
          return k;
        }
        (void)((uq = typeck_named_unqual_start(nm_scr, exist_len)));
        (void)((ul = (exist_len - uq)));
        (((ul ==ml) && (ul > 0)) ? ({   (void)((i = 0));
  while ((i < ml)) {
    if (((nm_scr)[(uq + i)] !=(mangled)[i])) {
      break;
    }
    (void)((i = (i + 1)));
  }
  ((i ==ml) ? ({   return k;
 }) : 0);
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    (void)((fam = typeck_find_or_alloc_named_type_ref(arena, &((mangled)[0]), ml)));
    if ((fam > 0)) {
      return fam;
    }
    return ty;
  }
}
int typeck_named_type_matches_name_or_alias(struct ast_Module * module, struct ast_ASTArena * arena, int32_t decl_ty_ref, uint8_t * lit_name, int32_t lit_name_len, int32_t depth) {
  {
    uint8_t decl_name[128] = {};
    uint8_t alias_name[128] = {};
    int32_t resolved_decl = 0;
    int32_t decl_name_len = 0;
    int32_t alias_count = 0;
    int32_t alias_i = 0;
    int32_t alias_name_len = 0;
    int32_t alias_off = 0;
    int32_t alias_target_ref = 0;
    int32_t ord_named = 8;
    int32_t max_depth = 32;
    if (((((((module ==0) || (arena ==0)) || ast_ref_is_null(decl_ty_ref)) || (lit_name ==0)) || (lit_name_len <=0)) || (depth > max_depth))) {
      return 0;
    }
    (void)((resolved_decl = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0)));
    if ((!(ast_ref_is_null(resolved_decl)) && (pipeline_type_kind_ord_at(arena, resolved_decl) ==ord_named))) {
      (void)((decl_name_len = pipeline_type_named_name_into(arena, resolved_decl, &((decl_name)[0]))));
      (typeck_name_equal(&((decl_name)[0]), decl_name_len, lit_name, lit_name_len) ? ({   return 1;
 }) : 0);
    }
    if ((pipeline_type_kind_ord_at(arena, decl_ty_ref) !=ord_named)) {
      return 0;
    }
    (void)((decl_name_len = pipeline_type_named_name_into(arena, decl_ty_ref, &((decl_name)[0]))));
    if (typeck_name_equal(&((decl_name)[0]), decl_name_len, lit_name, lit_name_len)) {
      return 1;
    }
    (void)((alias_count = pipeline_module_num_type_aliases_at(module)));
    while ((alias_i < alias_count)) {
      (void)((alias_name_len = pipeline_module_type_alias_name_len(module, alias_i)));
      if ((((alias_name_len ==decl_name_len) && (alias_name_len > 0)) && (alias_name_len <=127))) {
        (void)((alias_off = 0));
        while ((alias_off < alias_name_len)) {
          (void)(((alias_name)[alias_off] = pipeline_module_type_alias_name_byte_at(module, alias_i, alias_off)));
          (void)((alias_off = (alias_off + 1)));
        }
        (typeck_name_equal(&((alias_name)[0]), alias_name_len, &((decl_name)[0]), decl_name_len) ? ({   (void)((alias_target_ref = pipeline_module_type_alias_target_ref(module, alias_i)));
  return typeck_named_type_matches_name_or_alias(module, arena, alias_target_ref, lit_name, lit_name_len, (depth + 1));
 }) : 0);
      }
      (void)((alias_i = (alias_i + 1)));
    }
    return 0;
  }
}
int typeck_layout_name_equal(struct ast_Module * module, int32_t k, uint8_t * nm, int32_t nlen) {
  {
    uint8_t * buf = typeck_scratch64_slot(0);
    int32_t slen = pipeline_module_struct_layout_name_len(module, k);
    if (((slen !=nlen) || (nlen <=0))) {
      return 0;
    }
    (void)(pipeline_module_struct_layout_name_into(module, k, buf));
    return typeck_name_equal(buf, slen, nm, nlen);
  }
}
int typeck_layout_field_name_equal(struct ast_Module * module, int32_t k, int32_t j, uint8_t * nm, int32_t nlen) {
  {
    uint8_t * buf = typeck_scratch64_slot(1);
    int32_t fl = pipeline_module_struct_layout_field_name_len(module, k, j);
    if (((fl !=nlen) || (nlen <=0))) {
      return 0;
    }
    (void)(pipeline_module_struct_layout_field_name_into(module, k, j, buf));
    return typeck_name_equal(buf, fl, nm, nlen);
  }
}
int32_t typeck_layout_name_into(struct ast_Module * module, int32_t k, uint8_t * buf) {
  (void)(pipeline_module_struct_layout_name_into(module, k, buf));
  return pipeline_module_struct_layout_name_len(module, k);
}
int32_t typeck_layout_field_name_into(struct ast_Module * module, int32_t k, int32_t j, uint8_t * buf) {
  (void)(pipeline_module_struct_layout_field_name_into(module, k, j, buf));
  return pipeline_module_struct_layout_field_name_len(module, k, j);
}
int typeck_import_path_slice_equal(struct ast_Module * module, int32_t imp_ix, int32_t off, int32_t seg_len, uint8_t * nm, int32_t nm_len) {
  {
    if (((seg_len !=nm_len) || (seg_len <=0))) {
      return 0;
    }
    int32_t i = 0;
    while ((i < seg_len)) {
      if ((pipeline_module_import_path_byte_at(module, imp_ix, (off + i)) !=(nm)[i])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int typeck_import_binding_name_equal(struct ast_Module * module, int32_t imp_ix, uint8_t * nm, int32_t nm_len) {
  {
    int32_t bl = pipeline_module_import_binding_name_len(module, imp_ix);
    if (((bl !=nm_len) || (nm_len <=0))) {
      return 0;
    }
    int32_t i = 0;
    while ((i < nm_len)) {
      if ((pipeline_module_import_binding_name_byte_at(module, imp_ix, i) !=(nm)[i])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int32_t typeck_module_num_imports(struct ast_Module * module) {
  {
    if ((module ==0)) {
      return 0;
    }
    int32_t n_imp = parser_get_module_num_imports(module);
    if ((n_imp > 0)) {
      return n_imp;
    }
    return ((module)->num_imports);
  }
}
int typeck_var_is_import_visible_name(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  {
    int32_t ii = 0;
    int32_t import_kind = 0;
    int32_t seg_rel = 0;
    int32_t seg_len = 0;
    if ((((module ==0) || (nm ==0)) || (nlen <=0))) {
      return 0;
    }
    int32_t n_imp = typeck_module_num_imports(module);
    while ((ii < n_imp)) {
      (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
      if (((import_kind ==1) && typeck_import_binding_name_equal(module, ii, nm, nlen))) {
        return 1;
      }
      if ((typeck_import_segment_at(module, ii, 0, &(seg_rel), &(seg_len)) && typeck_import_path_slice_equal(module, ii, seg_rel, seg_len, nm, nlen))) {
        return 1;
      }
      (void)((ii = (ii + 1)));
    }
    return 0;
  }
}
int typeck_import_select_name_equal(struct ast_Module * module, int32_t imp_ix, int32_t sel, uint8_t * nm, int32_t nm_len) {
  {
    int32_t sl = pipeline_module_import_select_name_len(module, imp_ix, sel);
    if (((sl !=nm_len) || (nm_len <=0))) {
      return 0;
    }
    int32_t i = 0;
    while ((i < nm_len)) {
      if ((pipeline_module_import_select_name_byte_at(module, imp_ix, sel, i) !=(nm)[i])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int typeck_top_level_let_name_equal(struct ast_Module * module, int32_t tl_ix, uint8_t * nm, int32_t nm_len) {
  {
    int32_t tll = pipeline_module_top_level_let_name_len(module, tl_ix);
    if (((tll !=nm_len) || (nm_len <=0))) {
      return 0;
    }
    int32_t i = 0;
    while ((i < nm_len)) {
      if ((pipeline_module_top_level_let_name_byte_at(module, tl_ix, i) !=(nm)[i])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int32_t typeck_dep_module_const_idx_named(struct ast_Module * module, uint8_t * nm, int32_t nlen, int32_t tl_ix) {
  if ((((module ==0) || (nm ==0)) || (nlen <=0))) {
    return -1;
  }
  if ((tl_ix >=((module)->num_top_level_lets))) {
    return -1;
  }
  if (((pipeline_module_top_level_let_is_const(module, tl_ix) !=0) && typeck_top_level_let_name_equal(module, tl_ix, nm, nlen))) {
    return tl_ix;
  }
  return typeck_dep_module_const_idx_named(module, nm, nlen, (tl_ix + 1));
}
int32_t typeck_find_import_const_dep_index(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * nm, int32_t nlen, int32_t dep_ix) {
  {
    struct ast_Module * dm = 0;
    if (((((module ==0) || (ctx ==0)) || (nm ==0)) || (nlen <=0))) {
      return -1;
    }
    if ((dep_ix >=typeck_module_num_imports(module))) {
      return -1;
    }
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_ix)));
    if (((dm !=0) && (typeck_dep_module_const_idx_named(dm, nm, nlen, 0) >=0))) {
      return dep_ix;
    }
    return typeck_find_import_const_dep_index(module, ctx, nm, nlen, (dep_ix + 1));
  }
}
int32_t typeck_import_last_segment_into(struct ast_Module * module, int32_t imp_ix, uint8_t * out) {
  {
    int32_t pl = 0;
    int32_t start = 0;
    int32_t i = 0;
    int32_t seg_len = 0;
    if (((((module ==0) || (out ==0)) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
      return 0;
    }
    (void)((pl = pipeline_module_import_path_len(module, imp_ix)));
    if (((pl <=0) || (pl > 127))) {
      return 0;
    }
    while ((i < pl)) {
      if ((pipeline_module_import_path_byte_at(module, imp_ix, i) ==46)) {
        (void)((start = (i + 1)));
      }
      (void)((i = (i + 1)));
    }
    (void)((seg_len = (pl - start)));
    if (((seg_len <=0) || (seg_len > 127))) {
      return 0;
    }
    (void)((i = 0));
    while ((i < seg_len)) {
      (void)(((out)[i] = pipeline_module_import_path_byte_at(module, imp_ix, (start + i))));
      (void)((i = (i + 1)));
    }
    return seg_len;
  }
}
int32_t typeck_resolve_dep_index_for_import(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix) {
  {
    int32_t plen = 0;
    int32_t dep_i = 0;
    int32_t nd = 0;
    uint8_t path_buf[128] = {};
    if (((((module ==0) || (ctx ==0)) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
      return -1;
    }
    (void)((plen = pipeline_module_import_path_len(module, imp_ix)));
    if (((plen <=0) || (plen > 127))) {
      return -1;
    }
    while ((dep_i < plen)) {
      (void)(((path_buf)[dep_i] = pipeline_module_import_path_byte_at(module, imp_ix, dep_i)));
      (void)((dep_i = (dep_i + 1)));
    }
    (void)((nd = pipeline_dep_ctx_ndep(ctx)));
    (void)((dep_i = 0));
    while ((dep_i < nd)) {
      int32_t dep_plen = pipeline_dep_ctx_import_path_len(ctx, dep_i);
      if ((dep_plen ==plen)) {
        uint8_t dep_buf[128] = {};
        int eq = 1;
        int32_t k = 0;
        (void)(pipeline_dep_ctx_import_path_copy64(ctx, dep_i, &((dep_buf)[0])));
        while ((k < plen)) {
          if (((dep_buf)[k] !=(path_buf)[k])) {
            (void)((eq = 0));
            break;
          }
          (void)((k = (k + 1)));
        }
        (eq ? ({   return dep_i;
 }) : 0);
      }
      (void)((dep_i = (dep_i + 1)));
    }
    return -1;
  }
}
int32_t typeck_import_const_binding_hint_at(struct ast_Module * module, int32_t dep_ix, uint8_t * out) {
  {
    int32_t import_kind = 0;
    int32_t bl = 0;
    int32_t i = 0;
    if (((((module ==0) || (out ==0)) || (dep_ix < 0)) || (dep_ix >=typeck_module_num_imports(module)))) {
      return 0;
    }
    (void)((import_kind = pipeline_module_import_kind_at(module, dep_ix)));
    if ((import_kind ==1)) {
      (void)((bl = pipeline_module_import_binding_name_len(module, dep_ix)));
      (((bl > 0) && (bl <=127)) ? ({   while ((i < bl)) {
    (void)(((out)[i] = pipeline_module_import_binding_name_byte_at(module, dep_ix, i)));
    (void)((i = (i + 1)));
  }
  return bl;
 }) : 0);
    }
    return typeck_import_last_segment_into(module, dep_ix, out);
  }
}
int32_t typeck_reject_bare_import_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, uint8_t * vbuf, int32_t vnlen) {
  {
    int32_t const_dep_ix = -1;
    uint8_t hint_buf[128] = {};
    int32_t hint_len = 0;
    int32_t line = 0;
    int32_t col = 0;
    if (((((((module ==0) || (arena ==0)) || (ctx ==0)) || (vbuf ==0)) || (vnlen <=0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((const_dep_ix = typeck_find_import_const_dep_index(module, ctx, vbuf, vnlen, 0)));
    if ((const_dep_ix < 0)) {
      return 0;
    }
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)((hint_len = typeck_import_const_binding_hint_at(module, const_dep_ix, &((hint_buf)[0]))));
    (void)(driver_diagnostic_typeck_import_const_must_be_qualified(line, col, vbuf, vnlen, &((hint_buf)[0]), hint_len));
    return 1;
  }
}
int32_t typeck_find_layout_idx_by_type_name(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  int32_t k = 0;
  while ((k < ((module)->num_struct_layouts))) {
    if (typeck_layout_name_equal(module, k, nm, nlen)) {
      return k;
    }
    (void)((k = (k + 1)));
  }
  return -1;
}
int32_t typeck_x_named_builtin_align(uint8_t * nm, int32_t nlen) {
  if (((nm ==0) || (nlen <=0))) {
    return 0;
  }
  if (((((nlen ==3) && ((nm)[0] ==105)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if (((((nlen ==3) && ((nm)[0] ==117)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if ((((((nlen ==4) && ((nm)[0] ==98)) && ((nm)[1] ==111)) && ((nm)[2] ==111)) && ((nm)[3] ==108))) {
    return 4;
  }
  if ((((nlen ==2) && ((nm)[0] ==117)) && ((nm)[1] ==56))) {
    return 1;
  }
  if (((((nlen ==3) && ((nm)[0] ==105)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  if (((((nlen ==3) && ((nm)[0] ==117)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  if (((((((nlen ==5) && ((nm)[0] ==117)) && ((nm)[1] ==115)) && ((nm)[2] ==105)) && ((nm)[3] ==122)) && ((nm)[4] ==101))) {
    return 8;
  }
  if (((((((nlen ==5) && ((nm)[0] ==105)) && ((nm)[1] ==115)) && ((nm)[2] ==105)) && ((nm)[3] ==122)) && ((nm)[4] ==101))) {
    return 8;
  }
  if (((((nlen ==3) && ((nm)[0] ==102)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
    return 4;
  }
  if (((((nlen ==3) && ((nm)[0] ==102)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
    return 8;
  }
  return 0;
}
int32_t typeck_x_named_builtin_size(uint8_t * nm, int32_t nlen) {
  int32_t a = typeck_x_named_builtin_align(nm, nlen);
  if (((((a ==1) && (nlen ==2)) && ((nm)[0] ==117)) && ((nm)[1] ==56))) {
    return 1;
  }
  if ((a ==4)) {
    return 4;
  }
  if ((a ==8)) {
    return 8;
  }
  return 0;
}
int32_t typeck_x_type_align(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  {
    int32_t ko = 0;
    int32_t er = 0;
    int32_t nm_len = 0;
    int32_t li = 0;
    int32_t ba = 0;
    uint8_t * nm_buf = typeck_scratch64_slot(4);
    if ((((ast_ref_is_null(ty_ref) || (ty_ref <=0)) || (ty_ref > ((arena)->num_types))) || (depth > 64))) {
      return 1;
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
    if ((ko ==2)) {
      return 1;
    }
    if (((((ko ==0) || (ko ==3)) || (ko ==1)) || (ko ==14))) {
      return 4;
    }
    if (((((((ko ==5) || (ko ==4)) || (ko ==6)) || (ko ==7)) || (ko ==15)) || (ko ==9)) || (ko ==18)) {
      return 8;
    }
    if ((ko ==11)) {
      return 8;
    }
    if ((((ko ==10) || (ko ==12)) || (ko ==13))) {
      (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
      if (ast_ref_is_null(er)) {
        return 1;
      }
      return typeck_x_type_align(module, arena, er, (depth + 1));
    }
    if ((ko ==8)) {
      (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf)));
      (void)((li = typeck_find_layout_idx_by_type_name(module, nm_buf, nm_len)));
      if ((li >=0)) {
        return typeck_x_type_align_from_layout_glue(module, arena, li, (depth + 1));
      }
      (void)((ba = typeck_x_named_builtin_align(nm_buf, nm_len)));
      if ((ba > 0)) {
        return ba;
      }
      return 4;
    }
    return 1;
  }
}
int32_t typeck_type_is_empty_struct(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  {
    int32_t ko = 0;
    int32_t nm_len = 0;
    int32_t li = 0;
    int32_t nf = 0;
    int32_t j = 0;
    int32_t ftr = 0;
    uint8_t * nm = typeck_scratch64_slot(4);
    if ((((module ==0) || (arena ==0)) || (ty_ref <=0))) {
      return 0;
    }
    if (((ty_ref > ((arena)->num_types)) || (depth > 64))) {
      return 0;
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
    if ((ko !=8)) {
      return 0;
    }
    (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm)));
    if ((nm_len <=0)) {
      return 0;
    }
    (void)((li = typeck_find_layout_idx_by_type_name(module, nm, nm_len)));
    if ((li < 0)) {
      return 0;
    }
    (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
    if ((nf ==0)) {
      return 1;
    }
    (void)((j = 0));
    while ((j < nf)) {
      (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
      if ((typeck_type_is_empty_struct(module, arena, ftr, (depth + 1)) ==0)) {
        return 0;
      }
      (void)((j = (j + 1)));
    }
    return 1;
  }
}
int32_t typeck_x_type_size(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  {
    int32_t ko = 0;
    int32_t er = 0;
    int32_t asz = 0;
    int32_t es = 0;
    int32_t nm_len = 0;
    int32_t li2 = 0;
    int32_t bsz = 0;
    uint8_t * nm_buf_sz = typeck_scratch64_slot(4);
    if ((((ast_ref_is_null(ty_ref) || (ty_ref <=0)) || (ty_ref > ((arena)->num_types))) || (depth > 64))) {
      return 0;
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, ty_ref)));
    if ((ko ==16)) {
      return 0;
    }
    if ((ko ==2)) {
      return 1;
    }
    if (((((ko ==0) || (ko ==3)) || (ko ==1)) || (ko ==14))) {
      return 4;
    }
    if (((((((ko ==5) || (ko ==4)) || (ko ==6)) || (ko ==7)) || (ko ==15)) || (ko ==9)) || (ko ==18)) {
      return 8;
    }
    if ((ko ==11)) {
      return 16;
    }
    if ((ko ==12)) {
      (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
      if (ast_ref_is_null(er)) {
        return 0;
      }
      return typeck_x_type_size(module, arena, er, (depth + 1));
    }
    if (((ko ==10) || (ko ==13))) {
      (void)((er = pipeline_type_elem_ref_at(arena, ty_ref)));
      (void)((asz = pipeline_type_array_size_at(arena, ty_ref)));
      if ((ast_ref_is_null(er) || (asz <=0))) {
        return 0;
      }
      int32_t soa_sz = typeck_soa_array_storage_size_glue(module, arena, er, asz, (depth + 1));
      if ((soa_sz > 0)) {
        return soa_sz;
      }
      (void)((es = typeck_x_type_size(module, arena, er, (depth + 1))));
      if ((es <=0)) {
        return 0;
      }
      return (asz * es);
    }
    if ((ko ==8)) {
      (void)((nm_len = pipeline_type_named_name_into(arena, ty_ref, nm_buf_sz)));
      (void)((li2 = typeck_find_layout_idx_by_type_name(module, nm_buf_sz, nm_len)));
      if ((li2 >=0)) {
        return typeck_x_type_size_from_layout_glue(module, arena, li2, (depth + 1));
      }
      (void)((bsz = typeck_x_named_builtin_size(nm_buf_sz, nm_len)));
      if ((bsz > 0)) {
        return bsz;
      }
      return 4;
    }
    return 0;
  }
}
int32_t typeck_soa_find_layout_idx_by_name(struct ast_Module * module, uint8_t * name, int32_t name_len) {
  {
    int32_t k = 0;
    int32_t j = 0;
    int32_t ln = 0;
    int32_t eq = 0;
    if (((((module ==0) || (name ==0)) || (name_len <=0)) || (name_len > 127))) {
      return -1;
    }
    (void)((k = 0));
    while ((k < pipeline_module_num_struct_layouts_at(module))) {
      (void)((ln = pipeline_module_struct_layout_name_len(module, k)));
      if ((ln ==name_len)) {
        (void)((j = 0));
        (void)((eq = 1));
        while ((j < name_len)) {
          if ((pipeline_module_struct_layout_name_byte_at(module, k, j) !=(name)[j])) {
            (void)((eq = 0));
            break;
          }
          (void)((j = (j + 1)));
        }
        ((eq !=0) ? ({   return k;
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    return -1;
  }
}
int32_t typeck_soa_find_layout_module_and_idx(struct ast_Module * module, uint8_t * name, int32_t name_len, struct ast_Module * * out_layout_mod) {
  {
    int32_t li = 0;
    struct ast_PipelineDepCtx * pipe = 0;
    int32_t nd = 0;
    int32_t di = 0;
    struct ast_Module * dm = 0;
    uint8_t * om_bytes = ((uint8_t *)(out_layout_mod));
    if ((om_bytes !=0)) {
      (void)(((out_layout_mod)[0] = module));
    }
    if ((((module ==0) || (name ==0)) || (name_len <=0))) {
      return -1;
    }
    (void)((li = typeck_soa_find_layout_idx_by_name(module, name, name_len)));
    if ((li >=0)) {
      return li;
    }
    (void)((pipe = pipeline_asm_emit_dep_pipe_c()));
    if ((pipe ==0)) {
      return -1;
    }
    (void)((nd = pipeline_dep_ctx_ndep(pipe)));
    (void)((di = 0));
    while ((di < nd)) {
      (void)((dm = pipeline_dep_ctx_module_at(pipe, di)));
      if ((dm !=0)) {
        (void)((li = typeck_soa_find_layout_idx_by_name(dm, name, name_len)));
        ((li >=0) ? ({   if ((om_bytes !=0)) {
    (void)(((out_layout_mod)[0] = dm));
  }
  return li;
 }) : 0);
      }
      (void)((di = (di + 1)));
    }
    return -1;
  }
}
int32_t typeck_soa_col_base_for_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t field_idx, int32_t array_len, int32_t depth) {
  {
    int32_t col = 0;
    int32_t j = 0;
    int32_t nf = 0;
    int32_t ftr = 0;
    int32_t A = 0;
    int32_t fsize = 0;
    int32_t rem = 0;
    int32_t gap = 0;
    if (((((((module ==0) || (arena ==0)) || (li < 0)) || (field_idx < 0)) || (array_len <=0)) || (depth > 64))) {
      return 0;
    }
    (void)((col = 0));
    (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
    (void)((j = 0));
    while (((j < nf) && (j < field_idx))) {
      (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
      if ((ftr > 0)) {
        (void)((A = typeck_x_type_align(module, arena, ftr, depth)));
        (void)((fsize = typeck_x_type_size(module, arena, ftr, depth)));
        if ((A <=0)) {
          (void)((A = 1));
        }
        if ((fsize <=0)) {
          (void)((fsize = 4));
        }
        (void)((rem = (col % A)));
        (void)((gap = (A - rem)));
        (void)((gap = (gap % A)));
        (void)((col = ((col + gap) + (array_len * fsize))));
      }
      (void)((j = (j + 1)));
    }
    return col;
  }
}
int32_t typeck_soa_field_soa_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref) {
  {
    int32_t ix_base_ref = 0;
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t elem_ty = 0;
    int32_t array_sz = 0;
    uint8_t elem_nm[128] = {};
    int32_t elem_nlen = 0;
    int32_t li = 0;
    int32_t fl = 0;
    uint8_t fn_buf[128] = {};
    int32_t j = 0;
    int32_t fnlen = 0;
    int32_t ftr = 0;
    int32_t col_base = 0;
    int32_t stride = 0;
    struct ast_Module * layout_mod = module;
    int32_t fi = 0;
    uint8_t vname[128] = {};
    int32_t vlen = 0;
    int32_t nfuncs = 0;
    int32_t feq = 0;
    int32_t bi = 0;
    uint8_t fb[128] = {};
    if (((((module ==0) || (arena ==0)) || (expr_ref <=0)) || (base_ref <=0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=47)) {
      return 0;
    }
    (void)((ix_base_ref = pipeline_expr_index_base_ref(arena, base_ref)));
    if ((ix_base_ref <=0)) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, ix_base_ref)));
    if (((base_ty <=0) && (pipeline_expr_kind_ord_at(arena, ix_base_ref) ==3))) {
      (void)((vlen = pipeline_expr_var_name_len(arena, ix_base_ref)));
      (((vlen > 0) && (vlen <=127)) ? ({   (void)(pipeline_expr_var_name_into(arena, ix_base_ref, &((vname)[0])));
  (void)((nfuncs = pipeline_module_num_funcs(module)));
  (void)((fi = pipeline_asm_emit_func_index_c()));
  if (((fi >=0) && (fi < nfuncs))) {
    (void)((base_ty = pipeline_module_func_param_type_ref_for_name(module, fi, &((vname)[0]), vlen)));
  }
  if ((base_ty <=0)) {
    (void)((fi = 0));
    while ((fi < nfuncs)) {
      (void)((base_ty = pipeline_module_func_param_type_ref_for_name(module, fi, &((vname)[0]), vlen)));
      if ((base_ty > 0)) {
        break;
      }
      (void)((fi = (fi + 1)));
    }
  }
  ((base_ty > 0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, ix_base_ref, base_ty));
 }) : 0);
 }) : 0);
    }
    if (((base_ty <=0) || (base_ty > ((arena)->num_types)))) {
      return 0;
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    if (((bt_kind !=10) && (bt_kind !=13))) {
      return 0;
    }
    (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
    (void)((array_sz = pipeline_type_array_size_at(arena, base_ty)));
    if (((elem_ty <=0) || (array_sz <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, elem_ty) !=8)) {
      return 0;
    }
    (void)((elem_nlen = pipeline_type_named_name_into(arena, elem_ty, &((elem_nm)[0]))));
    if (((elem_nlen <=0) || (elem_nlen > 127))) {
      return 0;
    }
    (void)((li = typeck_soa_find_layout_module_and_idx(module, &((elem_nm)[0]), elem_nlen, &(layout_mod))));
    if ((((li < 0) || (layout_mod ==0)) || (pipeline_module_struct_layout_soa_at(layout_mod, li) ==0))) {
      return 0;
    }
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    (void)((ftr = 0));
    (void)((stride = 0));
    (void)((col_base = 0));
    (void)((j = 0));
    while ((j < pipeline_module_struct_layout_num_fields(layout_mod, li))) {
      (void)((fnlen = pipeline_module_struct_layout_field_name_len(layout_mod, li, j)));
      if ((fnlen ==fl)) {
        (void)(pipeline_module_struct_layout_field_name_into(layout_mod, li, j, &((fb)[0])));
        (void)((feq = 1));
        (void)((bi = 0));
        while ((bi < fnlen)) {
          if (((fb)[bi] !=(fn_buf)[bi])) {
            (void)((feq = 0));
            break;
          }
          (void)((bi = (bi + 1)));
        }
        ((feq !=0) ? ({   (void)((ftr = pipeline_module_struct_layout_field_type_ref(layout_mod, li, j)));
  (void)((stride = typeck_x_type_size(layout_mod, arena, ftr, 0)));
  if ((stride <=0)) {
    (void)((stride = 4));
  }
  (void)((col_base = typeck_soa_col_base_for_field(layout_mod, arena, li, j, array_sz, 0)));
  break;
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    if ((ftr <=0)) {
      return 0;
    }
    (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, col_base));
    (void)(pipeline_expr_set_field_access_soa_stride(arena, expr_ref, stride));
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ftr));
    return 1;
  }
}
int32_t typeck_soa_array_storage_size_glue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t elem_type_ref, int32_t array_len, int32_t depth) {
  {
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    int32_t li = 0;
    int32_t nf = 0;
    int32_t col = 0;
    int32_t max_al = 0;
    int32_t j = 0;
    int32_t ftr = 0;
    int32_t A = 0;
    if ((((((module ==0) || (arena ==0)) || (elem_type_ref <=0)) || (array_len <=0)) || (depth > 64))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, elem_type_ref) !=8)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, elem_type_ref, &((nm)[0]))));
    if (((nlen <=0) || (nlen > 127))) {
      return 0;
    }
    (void)((li = typeck_soa_find_layout_idx_by_name(module, &((nm)[0]), nlen)));
    if (((li < 0) || (pipeline_module_struct_layout_soa_at(module, li) ==0))) {
      return 0;
    }
    (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
    (void)((col = typeck_soa_col_base_for_field(module, arena, li, nf, array_len, (depth + 1))));
    (void)((max_al = 1));
    (void)((j = 0));
    while ((j < nf)) {
      (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
      if ((ftr > 0)) {
        (void)((A = typeck_x_type_align(module, arena, ftr, (depth + 1))));
        ((A > max_al) ? ({   (void)((max_al = A));
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    if (((max_al > 1) && ((col % max_al) !=0))) {
      (void)((col = (col + (max_al - (col % max_al)))));
    }
    if ((col > 0)) {
      return col;
    }
    return 0;
  }
}
int32_t typeck_struct_layout_metrics(struct ast_Module * module, struct ast_ASTArena * arena, int32_t li, int32_t depth, int32_t check_pad, int32_t * out_sz, int32_t * out_al) {
  {
    int32_t nf = 0;
    int32_t allow = 0;
    int32_t layout_nlen = 0;
    int32_t current = 0;
    int32_t max_align = 1;
    int32_t j = 0;
    int32_t ftr = 0;
    int32_t flen = 0;
    int32_t A = 0;
    int32_t rem = 0;
    int32_t gap = 0;
    int32_t fsize = 0;
    int32_t end_pad = 0;
    int32_t fa = 0;
    uint8_t * layout_nm = typeck_scratch64_slot(2);
    uint8_t * field_nm = typeck_scratch64_slot(3);
    if (((((module ==0) || (arena ==0)) || (out_sz ==0)) || (out_al ==0))) {
      return -1;
    }
    if ((((li < 0) || (li >=pipeline_module_num_struct_layouts_at(module))) || (depth > 64))) {
      return -1;
    }
    (void)((nf = pipeline_module_struct_layout_num_fields(module, li)));
    (void)((allow = pipeline_module_struct_layout_allow_padding_at(module, li)));
    (void)(typeck_layout_name_into(module, li, layout_nm));
    (void)((layout_nlen = pipeline_module_struct_layout_name_len(module, li)));
    (void)((current = 0));
    (void)((max_align = 1));
    if ((pipeline_module_struct_layout_packed_at(module, li) !=0)) {
      (void)((j = 0));
      while ((j < nf)) {
        (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
        (void)((fsize = typeck_x_type_size(module, arena, ftr, depth)));
        if (((fsize < 0) || ((fsize ==0) && (typeck_type_is_empty_struct(module, arena, ftr, depth) ==0)))) {
          if ((check_pad !=0)) {
            (void)(typeck_layout_field_name_into(module, li, j, field_nm));
            (void)((flen = pipeline_module_struct_layout_field_name_len(module, li, j)));
            (void)(driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen));
          }
          return -1;
        }
        (void)((current = (current + fsize)));
        (void)((j = (j + 1)));
      }
      (void)(typeck_i32_ptr_store(out_sz, current));
      (void)(typeck_i32_ptr_store(out_al, 1));
      return 0;
    }
    (void)((j = 0));
    while ((j < nf)) {
      (void)((ftr = pipeline_module_struct_layout_field_type_ref(module, li, j)));
      (void)(typeck_layout_field_name_into(module, li, j, field_nm));
      (void)((flen = pipeline_module_struct_layout_field_name_len(module, li, j)));
      (void)((fa = pipeline_module_struct_layout_field_align_at(module, li, j)));
      (void)((A = typeck_x_type_align(module, arena, ftr, depth)));
      if ((A <=0)) {
        (void)((A = 1));
      }
      if ((fa > A)) {
        (void)((A = fa));
      }
      (void)((rem = (current % A)));
      (void)((gap = (A - rem)));
      (void)((gap = (gap % A)));
      if ((((check_pad !=0) && (gap > 0)) && (allow ==0))) {
        (void)(driver_diagnostic_typeck_struct_padding_before(layout_nm, layout_nlen, gap, field_nm, flen));
        return -1;
      }
      (void)((current = (current + gap)));
      (void)((fsize = typeck_x_type_size(module, arena, ftr, depth)));
      if (((fsize < 0) || ((fsize ==0) && (typeck_type_is_empty_struct(module, arena, ftr, depth) ==0)))) {
        if ((check_pad !=0)) {
          (void)(driver_diagnostic_typeck_struct_field_bad_size(layout_nm, layout_nlen, field_nm, flen));
        }
        return -1;
      }
      (void)((current = (current + fsize)));
      if ((A > max_align)) {
        (void)((max_align = A));
      }
      (void)((j = (j + 1)));
    }
    if (((max_align > 0) && ((current % max_align) !=0))) {
      (void)((end_pad = (max_align - (current % max_align))));
      if ((((check_pad !=0) && (end_pad > 0)) && (allow ==0))) {
        (void)(driver_diagnostic_typeck_struct_padding_trailing(layout_nm, layout_nlen, end_pad));
        return -1;
      }
      (void)((current = (current + end_pad)));
    }
    (void)(typeck_i32_ptr_store(out_sz, current));
    (void)(typeck_i32_ptr_store(out_al, max_align));
    return 0;
  }
}
int32_t typeck_validate_struct_layouts_zero_padding(struct ast_Module * module, struct ast_ASTArena * arena) {
  {
    int32_t li = 0;
    int32_t nsl = pipeline_module_num_struct_layouts_at(module);
    int32_t * sz_out = typeck_layout_metrics_sz_slot();
    int32_t * al_out = typeck_layout_metrics_al_slot();
    while ((li < nsl)) {
      (void)(typeck_layout_metrics_init_slot());
      if ((typeck_struct_layout_metrics(module, arena, li, 0, 1, sz_out, al_out) !=0)) {
        return -1;
      }
      (void)(pipeline_typeck_pad_fields_warn_layout(module, arena, li));
      (void)(pipeline_typeck_hot_reorder_warn_layout(module, arena, li));
      (void)((li = (li + 1)));
    }
    return 0;
  }
}
int32_t typeck_get_field_offset_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  {
    int32_t k = 0;
    while ((k < ((module)->num_struct_layouts))) {
      if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
        int32_t j = 0;
        while ((j < pipeline_module_struct_layout_num_fields(module, k))) {
          if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
            int32_t stored = pipeline_module_struct_layout_field_offset_at(module, k, j);
            if ((stored != 0)) {
              return stored;
            }
            if ((j == 0)) {
              return 0;
            }
            return -1;
          }
          (void)((j = (j + 1)));
        }
      }
      (void)((k = (k + 1)));
    }
    return -1;
  }
}
int32_t typeck_get_field_type_ref_from_layout(struct ast_Module * module, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  {
    int32_t k = 0;
    while ((k < ((module)->num_struct_layouts))) {
      if (typeck_layout_name_equal(module, k, type_name, type_name_len)) {
        int32_t j = 0;
        while ((j < pipeline_module_struct_layout_num_fields(module, k))) {
          if (typeck_layout_field_name_equal(module, k, j, field_name, field_name_len)) {
            return pipeline_module_struct_layout_field_type_ref(module, k, j);
          }
          (void)((j = (j + 1)));
        }
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
}
int32_t typeck_get_field_offset_from_layout_deps(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  {
    int32_t r = typeck_get_field_offset_from_layout(module, type_name, type_name_len, field_name, field_name_len);
    if ((r >=0)) {
      return r;
    }
    if ((ctx ==0)) {
      return -1;
    }
    int32_t nd = pipeline_dep_ctx_ndep(ctx);
    int32_t di = 0;
    while ((di < nd)) {
      struct ast_Module * dm = pipeline_dep_ctx_module_at(ctx, di);
      if ((dm !=0)) {
        (void)((r = typeck_get_field_offset_from_layout(dm, type_name, type_name_len, field_name, field_name_len)));
        ((r >=0) ? ({   return r;
 }) : 0);
        struct ast_ASTArena * darena = pipeline_dep_ctx_arena_at(ctx, di);
        if ((darena !=0)) {
          int32_t lk = 0;
          int32_t nsl = pipeline_module_num_struct_layouts_at(dm);
          while ((lk < nsl)) {
            if (typeck_layout_name_equal(dm, lk, type_name, type_name_len)) {
              (void)((r = glue_struct_layout_field_offset_by_name_c(dm, darena, lk, field_name, field_name_len)));
              if ((r >=0)) {
                return r;
              }
            }
            (void)((lk = (lk + 1)));
          }
        }
      }
      (void)((di = (di + 1)));
    }
    return -1;
  }
}
int32_t typeck_ensure_struct_layout_from_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    int32_t num_fields = 0;
    int32_t name_len = 0;
    int32_t k = 0;
    int32_t found_idx = -1;
    int32_t idx_m = 0;
    int32_t jm = 0;
    int32_t fnlen_m = 0;
    int32_t exists_m = 0;
    int32_t tm = 0;
    int32_t nf_layout = 0;
    int32_t flen_tm = 0;
    int32_t nf_m = 0;
    int32_t ftr_m = 0;
    int32_t init_rm = 0;
    int32_t fr_m = 0;
    int32_t idx = 0;
    int32_t j = 0;
    int32_t fnlen_j = 0;
    int32_t ftr = 0;
    int32_t init_r = 0;
    int32_t fr = 0;
    int32_t foff_m = 0;
    int32_t foff_j = 0;
    int32_t nsl = 0;
    int32_t sname_len = 0;
    uint8_t * lit_nm = typeck_scratch64_slot(4);
    uint8_t * layout_nm = typeck_scratch64_slot(5);
    uint8_t * field_nm = typeck_scratch64_slot(6);
    uint8_t * exist_nm = typeck_scratch64_slot(7);
    if (((expr_ref <=0) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref)));
    if (((num_fields <=0) || (num_fields > 8))) {
      return 0;
    }
    (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
    if (((name_len <=0) || (name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, lit_nm));
    (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
    (void)((k = 0));
    (void)((found_idx = -1));
    while ((k < nsl)) {
      (void)(pipeline_module_struct_layout_name_into(module, k, layout_nm));
      (void)((sname_len = pipeline_module_struct_layout_name_len(module, k)));
      if (typeck_name_equal(layout_nm, sname_len, lit_nm, name_len)) {
        (void)((found_idx = k));
        break;
      }
      (void)((k = (k + 1)));
    }
    if ((found_idx >=0)) {
      (void)((idx_m = found_idx));
      (void)((jm = 0));
      while ((jm < num_fields)) {
        (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm));
        (void)((fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm)));
        (void)((exists_m = 0));
        (void)((tm = 0));
        (void)((nf_layout = pipeline_module_struct_layout_num_fields(module, idx_m)));
        if ((nf_layout >=num_fields)) {
          return 0;
        }
        while ((tm < nf_layout)) {
          (void)(pipeline_module_struct_layout_field_name_into(module, idx_m, tm, exist_nm));
          (void)((flen_tm = pipeline_module_struct_layout_field_name_len(module, idx_m, tm)));
          if (typeck_name_equal(exist_nm, flen_tm, field_nm, fnlen_m)) {
            (void)((exists_m = 1));
          }
          (void)((tm = (tm + 1)));
        }
        if ((exists_m ==0)) {
          (void)((nf_m = nf_layout));
          (void)((ftr_m = 0));
          (void)((init_rm = pipeline_expr_struct_lit_init_ref(arena, expr_ref, jm)));
          if (((!(ast_ref_is_null(init_rm)) && (init_rm > 0)) && (init_rm <=((arena)->num_exprs)))) {
            (void)((fr_m = typeck_expr_type_ref(arena, init_rm)));
            (!(ast_ref_is_null(fr_m)) ? ({   (void)((ftr_m = fr_m));
 }) : 0);
          }
          (void)((foff_m = pipeline_struct_layout_next_field_offset(module, arena, idx_m, ftr_m)));
          (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, jm, field_nm));
          (void)((fnlen_m = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, jm)));
          (void)(pipeline_module_struct_layout_set_field(module, idx_m, nf_m, field_nm, fnlen_m, ftr_m, foff_m));
          (void)(pipeline_module_struct_layout_set_num_fields(module, idx_m, (nf_m + 1)));
        }
        (void)((jm = (jm + 1)));
      }
      return 0;
    }
    (void)((idx = pipeline_module_struct_layout_alloc(module)));
    if ((idx < 0)) {
      return -1;
    }
    (void)(pipeline_module_struct_layout_reset_slot(module, idx));
    (void)(pipeline_module_struct_layout_set_name(module, idx, lit_nm, name_len));
    (void)(pipeline_module_struct_layout_set_num_fields(module, idx, num_fields));
    (void)((j = 0));
    while ((j < num_fields)) {
      (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_nm));
      (void)((fnlen_j = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j)));
      (void)((ftr = 0));
      (void)((init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j)));
      if (((!(ast_ref_is_null(init_r)) && (init_r > 0)) && (init_r <=((arena)->num_exprs)))) {
        (void)((fr = typeck_expr_type_ref(arena, init_r)));
        (!(ast_ref_is_null(fr)) ? ({   (void)((ftr = fr));
 }) : 0);
      }
      (void)((foff_j = pipeline_struct_layout_next_field_offset(module, arena, idx, ftr)));
      (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_nm));
      (void)((fnlen_j = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j)));
      (void)(pipeline_module_struct_layout_set_field(module, idx, j, field_nm, fnlen_j, ftr, foff_j));
      (void)((j = (j + 1)));
    }
    return 0;
  }
}
void typeck_soa_fill_field_access_for_asm_emit(struct ast_Module * module, struct ast_ASTArena * arena) {
  {
    int32_t fi = 0;
    int32_t ei = 0;
    int32_t saved_fi = 0;
    int32_t li = 0;
    int32_t nf2 = 0;
    int32_t j = 0;
    int32_t fa0 = 0;
    int32_t br = 0;
    int32_t base_ref = 0;
    int32_t flen = 0;
    uint8_t fname[128] = {};
    int32_t layout_off = 0;
    int32_t nfuncs = 0;
    int32_t nlayouts = 0;
    int32_t nexprs = 0;
    int32_t ens_rc = 0;
    int32_t soa_rc = 0;
    if (((module ==0) || (arena ==0))) {
      return;
    }
    (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x66\x69\x6c\x6c\x5f\x63\x6c\x5f\x70\x72\x65"), module, arena));
    (void)((nexprs = ((arena)->num_exprs)));
    (void)((ei = 1));
    while ((ei <=nexprs)) {
      if ((pipeline_expr_kind_ord_at(arena, ei) ==45)) {
        (void)((ens_rc = typeck_ensure_struct_layout_from_struct_lit(module, arena, ei)));
        ((ens_rc !=0) ? ({  }) : 0);
      }
      (void)((ei = (ei + 1)));
    }
    (void)((nlayouts = pipeline_module_num_struct_layouts_at(module)));
    (void)((li = 0));
    while ((li < nlayouts)) {
      (void)((nf2 = pipeline_module_struct_layout_num_fields(module, li)));
      (void)((j = 0));
      while (((j + 1) < nf2)) {
        (void)((fa0 = pipeline_module_struct_layout_field_align_at(module, li, j)));
        if (((fa0 >=64) && (pipeline_module_struct_layout_field_align_at(module, li, (j + 1)) ==0))) {
          (void)(pipeline_module_struct_layout_set_field_align(module, li, (j + 1), fa0));
        }
        (void)((j = (j + 1)));
      }
      (void)((li = (li + 1)));
    }
    (void)(glue_sync_struct_layout_field_offsets_c(module, arena));
    (void)((saved_fi = pipeline_asm_emit_func_index_c()));
    (void)((nfuncs = pipeline_module_num_funcs(module)));
    (void)((fi = 0));
    while ((fi < nfuncs)) {
      if ((pipeline_module_func_is_extern_at(module, fi) !=0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((br = pipeline_module_func_body_ref_at(module, fi)));
      if ((br <=0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)(pipeline_asm_emit_set_func_index(fi));
      (void)(glue_fill_var_types_from_lets_in_block(arena, br));
      (void)(glue_fill_var_types_from_params_for_func(module, arena, fi));
      (void)((fi = (fi + 1)));
    }
    (void)((ei = 1));
    while ((ei <=nexprs)) {
      if ((pipeline_expr_kind_ord_at(arena, ei) !=44)) {
        (void)((ei = (ei + 1)));
        continue;
      }
      (void)((base_ref = pipeline_expr_field_access_base_ref(arena, ei)));
      if ((base_ref <=0)) {
        (void)((ei = (ei + 1)));
        continue;
      }
      if ((pipeline_expr_kind_ord_at(arena, base_ref) ==47)) {
        (void)((soa_rc = typeck_soa_field_soa_index(module, arena, ei, base_ref)));
        ((soa_rc !=0) ? ({  }) : 0);
      }
      (void)((flen = pipeline_expr_field_access_name_len(arena, ei)));
      if (((flen <=0) || (flen > 127))) {
        (void)((ei = (ei + 1)));
        continue;
      }
      (void)(pipeline_expr_field_access_name_into(arena, ei, &((fname)[0])));
      if ((pipeline_expr_field_access_soa_stride(arena, ei) > 0)) {
        (void)((ei = (ei + 1)));
        continue;
      }
      (void)((layout_off = glue_field_layout_offset_for_base_field(arena, module, base_ref, &((fname)[0]), flen)));
      if ((layout_off >=0)) {
        (void)(pipeline_expr_set_field_access_offset(arena, ei, layout_off));
      }
      (void)((ei = (ei + 1)));
    }
    (void)(pipeline_asm_emit_set_func_index(saved_fi));
    (void)(pipeline_debug_trace_named_func_bodies(((uint8_t *)"\x66\x69\x6c\x6c\x5f\x63\x6c\x5f\x70\x6f\x73\x74"), module, arena));
  }
}
void typeck_field_prebind(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t base_ref = 0;
    int32_t vnlen = 0;
    uint8_t vbuf[128] = {};
    int32_t param_pre = 0;
    int32_t nt_pre = 0;
    int32_t fi = 0;
    if (((arena ==0) || (module ==0))) {
      return;
    }
    (void)((base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref)));
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=3)) {
      return;
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref)))) {
      return;
    }
    (void)((vnlen = pipeline_expr_var_name_len(arena, base_ref)));
    if (((vnlen <=0) || (vnlen > 127))) {
      return;
    }
    (void)(pipeline_expr_var_name_into(arena, base_ref, &((vbuf)[0])));
    if ((ctx !=0)) {
      (void)((fi = pipeline_dep_ctx_current_func_index(ctx)));
      (((fi >=0) && (fi < ((module)->num_funcs))) ? ({   (void)((param_pre = pipeline_module_func_param_type_ref_for_name(module, fi, &((vbuf)[0]), vnlen)));
  (!(ast_ref_is_null(param_pre)) ? ({   return;
 }) : 0);
 }) : 0);
    }
    (void)((nt_pre = typeck_find_or_alloc_named_type_ref(arena, &((vbuf)[0]), vnlen)));
    ((nt_pre !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, base_ref, nt_pre));
 }) : 0);
  }
}
int32_t typeck_field_known_ptr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, int32_t num_struct_layouts) {
  {
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t elem_ty = 0;
    uint8_t inner_nm_buf[128] = {};
    int32_t inner_nm_len = 0;
    int32_t inner_ord = 0;
    int32_t fl = 0;
    uint8_t fn_buf[128] = {};
    uint8_t nm_astarena[8] = {65, 83, 84, 65, 114, 101, 110, 97};
    uint8_t nm_types[5] = {116, 121, 112, 101, 115};
    uint8_t nm_num_types[9] = {110, 117, 109, 95, 116, 121, 112, 101, 115};
    uint8_t nm_exprs[5] = {101, 120, 112, 114, 115};
    uint8_t nm_num_exprs[9] = {110, 117, 109, 95, 101, 120, 112, 114, 115};
    uint8_t nm_blocks[6] = {98, 108, 111, 99, 107, 115};
    uint8_t nm_num_blocks[10] = {110, 117, 109, 95, 98, 108, 111, 99, 107, 115};
    uint8_t nm_funcs[5] = {102, 117, 110, 99, 115};
    uint8_t nm_num_funcs[9] = {110, 117, 109, 95, 102, 117, 110, 99, 115};
    uint8_t nm_ty[4] = {84, 121, 112, 101};
    uint8_t nm_ex[4] = {69, 120, 112, 114};
    uint8_t nm_bl[5] = {66, 108, 111, 99, 107};
    uint8_t nm_fu[4] = {70, 117, 110, 99};
    uint8_t nm_module[6] = {77, 111, 100, 117, 108, 101};
    uint8_t nm_struct_layouts_m[14] = {115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
    uint8_t nm_num_struct_layouts_m[18] = {110, 117, 109, 95, 115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
    uint8_t nm_sl_m[12] = {83, 116, 114, 117, 99, 116, 76, 97, 121, 111, 117, 116};
    int32_t i32r_at = 0;
    int32_t i32r_mod = 0;
    int32_t matched = 0;
    int32_t arr_ty = 0;
    if ((arena ==0)) {
      return 0;
    }
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((ast_ref_is_null(base_ty) || (base_ty <=0)) || (base_ty > ((arena)->num_types)))) {
      return 0;
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    if ((bt_kind !=9)) {
      return 0;
    }
    (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
    if (ast_ref_is_null(elem_ty)) {
      return 0;
    }
    (void)((inner_nm_len = pipeline_type_named_name_into(arena, elem_ty, &((inner_nm_buf)[0]))));
    (void)((inner_ord = pipeline_type_kind_ord_at(arena, elem_ty)));
    (void)(driver_diagnostic_typeck_ptr_field(9, inner_ord, inner_nm_len, base_ty, num_struct_layouts));
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    (void)((i32r_at = typeck_ensure_i32_type_ref(arena)));
    (void)((i32r_mod = typeck_ensure_i32_type_ref(arena)));
    (void)((matched = 0));
    if ((((inner_ord ==8) && (inner_nm_len ==8)) && typeck_name_equal(&((inner_nm_buf)[0]), inner_nm_len, &((nm_astarena)[0]), 8))) {
      if (((fl ==5) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_types)[0]), 5))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 0));
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_ty)[0]), 4, 512)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==9)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_types)[0]), 9))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 40960));
        ((i32r_at !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==5)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_exprs)[0]), 5))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 40968));
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_ex)[0]), 4, 32768)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==9)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_exprs)[0]), 9))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 6234120));
        ((i32r_at !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==6)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_blocks)[0]), 6))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 6234124));
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_bl)[0]), 5, 8192)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==10)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_blocks)[0]), 10))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 17184780));
        ((i32r_at !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==5)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_funcs)[0]), 5))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 17184784));
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_fu)[0]), 4, 256)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==9)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_funcs)[0]), 9))) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 17371152));
        ((i32r_at !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_at));
  (void)((matched = 1));
 }) : 0);
      }
      ((matched !=0) ? ({   return 1;
 }) : 0);
    }
    if ((((inner_ord ==8) && (inner_nm_len ==6)) && typeck_name_equal(&((inner_nm_buf)[0]), inner_nm_len, &((nm_module)[0]), 6))) {
      (void)((matched = 0));
      if (((fl ==5) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_funcs)[0]), 5))) {
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_fu)[0]), 4, 256)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==14)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_struct_layouts_m)[0]), 14))) {
        (void)((arr_ty = typeck_ensure_array_type_ref_named_elem(arena, &((nm_sl_m)[0]), 12, 32)));
        ((arr_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
  (void)((matched = 1));
 }) : 0);
      }
      if ((((matched ==0) && (fl ==9)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_funcs)[0]), 9))) {
        ((i32r_mod !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_mod));
  (void)((matched = 1));
 }) : 0);
      }
      ((((matched ==0) && (fl ==18)) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_num_struct_layouts_m)[0]), 18)) ? ({   ((i32r_mod !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_mod));
  (void)((matched = 1));
 }) : 0);
 }) : 0);
    }
    if ((matched !=0)) {
      return 1;
    }
    return 0;
  }
}
int32_t typeck_dep_top_level_const_match(struct ast_Module * dep_mod, uint8_t * name, int32_t name_len, int32_t * out_type_ref) {
  {
    int32_t tl = 0;
    int32_t ntl = 0;
    int32_t tr = 0;
    if (((((dep_mod ==0) || (name ==0)) || (name_len <=0)) || (out_type_ref ==0))) {
      return 0;
    }
    (void)((ntl = ((dep_mod)->num_top_level_lets)));
    while ((tl < ntl)) {
      if ((pipeline_module_top_level_let_is_const(dep_mod, tl) !=0)) {
        (typeck_top_level_let_name_equal(dep_mod, tl, name, name_len) ? ({   (void)((tr = pipeline_module_top_level_let_type_ref(dep_mod, tl)));
  (void)((*(out_type_ref) = tr));
  return 1;
 }) : 0);
      }
      (void)((tl = (tl + 1)));
    }
    return 0;
  }
}
int32_t typeck_field_import_try_dep_enum_type(struct ast_Module * dep_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, uint8_t * base_name, int32_t base_name_len, uint8_t * field_name, int32_t field_name_len) {
  {
    int32_t ne = 0;
    int32_t ek = 0;
    int32_t el = 0;
    int32_t bi = 0;
    int32_t enum_ty = 0;
    int32_t nt = 0;
    if (((((dep_mod ==0) || (arena ==0)) || (field_name ==0)) || (field_name_len <=0))) {
      return 0;
    }
    (void)((ne = ((dep_mod)->num_module_enums)));
    while ((ek < ne)) {
      (void)((el = pipeline_module_enum_name_len(dep_mod, ek)));
      if (((el ==field_name_len) && (el > 0))) {
        (void)((bi = 0));
        while ((bi < el)) {
          if ((pipeline_module_enum_name_byte_at(dep_mod, ek, bi) !=(field_name)[bi])) {
            break;
          }
          (void)((bi = (bi + 1)));
        }
        ((bi ==el) ? ({   (void)((enum_ty = typeck_find_or_alloc_named_type_ref(arena, field_name, field_name_len)));
  if ((enum_ty !=0)) {
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, enum_ty));
  }
  if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
    (((base_name !=0) && (base_name_len > 0)) ? ({   (void)((nt = typeck_find_or_alloc_named_type_ref(arena, base_name, base_name_len)));
  ((nt !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, base_ref, nt));
 }) : 0);
 }) : 0);
  }
  return 1;
 }) : 0);
      }
      (void)((ek = (ek + 1)));
    }
    return 0;
  }
}
extern int32_t typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx);
int32_t typeck_field_import_binding(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  {
    uint8_t base_name[128] = {};
    int32_t base_name_len = 0;
    uint8_t field_name[128] = {};
    int32_t field_name_len = 0;
    int32_t i = 0;
    int32_t n_imp = 0;
    struct ast_Module * dep_mod = 0;
    int32_t j = 0;
    int32_t nf = 0;
    int32_t nd = 0;
    int32_t ret_ty = 0;
    int32_t const_ty = 0;
    int32_t nt = 0;
    int32_t ntl = 0;
    int32_t tl = 0;
    int32_t di = 0;
    if (((((module ==0) || (arena ==0)) || (base_ref <=0)) || (ctx ==0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=3)) {
      return 0;
    }
    (void)((base_name_len = pipeline_expr_var_name_len(arena, base_ref)));
    if (((base_name_len <=0) || (base_name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, base_ref, &((base_name)[0])));
    (void)((field_name_len = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((field_name_len <=0) || (field_name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((field_name)[0])));
    (void)((n_imp = ((module)->num_imports)));
    while ((i < n_imp)) {
      if (typeck_import_binding_name_equal(module, i, &((base_name)[0]), base_name_len)) {
        (void)((dep_mod = 0));
        (void)((nd = pipeline_dep_ctx_ndep(ctx)));
        if ((i < nd)) {
          (void)((dep_mod = pipeline_dep_ctx_module_at(ctx, i)));
        }
        ((dep_mod !=0) ? ({   (void)((nf = pipeline_module_num_funcs(dep_mod)));
  (void)((j = 0));
  while ((j < nf)) {
    if ((pipeline_module_func_name_equal_at(dep_mod, j, &((field_name)[0]), field_name_len) !=0)) {
      (void)((ret_ty = pipeline_module_func_return_type_at(dep_mod, j)));
      if ((ret_ty > 0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
      }
      if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
        (void)((nt = typeck_find_or_alloc_named_type_ref(arena, &((base_name)[0]), base_name_len)));
        ((nt !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, base_ref, nt));
 }) : 0);
      }
      return 1;
    }
    (void)((j = (j + 1)));
  }
  (void)((const_ty = 0));
  if ((typeck_dep_top_level_const_match(dep_mod, &((field_name)[0]), field_name_len, &(const_ty)) !=0)) {
    if ((const_ty <=0)) {
      (void)((const_ty = typeck_ensure_i32_type_ref(arena)));
    } else {
      (void)((const_ty = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(i, const_ty, arena, ctx)));
    }
    if ((const_ty > 0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, const_ty));
    }
    if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
      (void)((nt = typeck_find_or_alloc_named_type_ref(arena, &((base_name)[0]), base_name_len)));
      ((nt !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, base_ref, nt));
 }) : 0);
    }
    return 1;
  }
  ((typeck_field_import_try_dep_enum_type(dep_mod, arena, expr_ref, base_ref, &((base_name)[0]), base_name_len, &((field_name)[0]), field_name_len) !=0) ? ({   return 1;
 }) : 0);
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
    (void)((ntl = ((module)->num_top_level_lets)));
    (void)((tl = 0));
    while ((tl < ntl)) {
      if ((pipeline_module_top_level_let_is_const(module, tl) !=0)) {
        (typeck_top_level_let_name_equal(module, tl, &((base_name)[0]), base_name_len) ? ({   (void)((nd = pipeline_dep_ctx_ndep(ctx)));
  (void)((di = 0));
  while ((di < nd)) {
    (void)((dep_mod = pipeline_dep_ctx_module_at(ctx, di)));
    if ((dep_mod !=0)) {
      (void)((const_ty = 0));
      if ((typeck_dep_top_level_const_match(dep_mod, &((field_name)[0]), field_name_len, &(const_ty)) !=0)) {
        if ((const_ty <=0)) {
          (void)((const_ty = typeck_ensure_i32_type_ref(arena)));
        } else {
          (void)((const_ty = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(di, const_ty, arena, ctx)));
        }
        if ((const_ty > 0)) {
          (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, const_ty));
        }
        if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, base_ref))) {
          (void)((nt = typeck_find_or_alloc_named_type_ref(arena, &((base_name)[0]), base_name_len)));
          ((nt !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, base_ref, nt));
 }) : 0);
        }
        return 1;
      }
      ((typeck_field_import_try_dep_enum_type(dep_mod, arena, expr_ref, base_ref, &((base_name)[0]), base_name_len, &((field_name)[0]), field_name_len) !=0) ? ({   return 1;
 }) : 0);
    }
    (void)((di = (di + 1)));
  }
 }) : 0);
      }
      (void)((tl = (tl + 1)));
    }
    return 0;
  }
}
int32_t typeck_field_import_const_is_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t base_ref = 0;
    uint8_t base_name[128] = {};
    int32_t base_name_len = 0;
    uint8_t field_name[128] = {};
    int32_t field_name_len = 0;
    int32_t i = 0;
    int32_t n_imp = 0;
    struct ast_Module * dep_mod = 0;
    int32_t nd = 0;
    int32_t const_ty = 0;
    int32_t ntl = 0;
    int32_t tl = 0;
    int32_t di = 0;
    if (((((module ==0) || (arena ==0)) || (expr_ref <=0)) || (ctx ==0))) {
      return 0;
    }
    (void)((base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref)));
    if ((base_ref <=0)) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=3)) {
      return 0;
    }
    (void)((base_name_len = pipeline_expr_var_name_len(arena, base_ref)));
    if (((base_name_len <=0) || (base_name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, base_ref, &((base_name)[0])));
    (void)((field_name_len = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((field_name_len <=0) || (field_name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((field_name)[0])));
    (void)((n_imp = ((module)->num_imports)));
    while ((i < n_imp)) {
      if (typeck_import_binding_name_equal(module, i, &((base_name)[0]), base_name_len)) {
        (void)((nd = pipeline_dep_ctx_ndep(ctx)));
        (void)((dep_mod = 0));
        if ((i < nd)) {
          (void)((dep_mod = pipeline_dep_ctx_module_at(ctx, i)));
        }
        ((dep_mod !=0) ? ({   (void)((const_ty = 0));
  ((typeck_dep_top_level_const_match(dep_mod, &((field_name)[0]), field_name_len, &(const_ty)) !=0) ? ({   return 1;
 }) : 0);
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
    (void)((ntl = ((module)->num_top_level_lets)));
    (void)((tl = 0));
    while ((tl < ntl)) {
      if ((pipeline_module_top_level_let_is_const(module, tl) !=0)) {
        (typeck_top_level_let_name_equal(module, tl, &((base_name)[0]), base_name_len) ? ({   (void)((nd = pipeline_dep_ctx_ndep(ctx)));
  (void)((di = 0));
  while ((di < nd)) {
    (void)((dep_mod = pipeline_dep_ctx_module_at(ctx, di)));
    if ((dep_mod !=0)) {
      (void)((const_ty = 0));
      ((typeck_dep_top_level_const_match(dep_mod, &((field_name)[0]), field_name_len, &(const_ty)) !=0) ? ({   return 1;
 }) : 0);
    }
    (void)((di = (di + 1)));
  }
 }) : 0);
      }
      (void)((tl = (tl + 1)));
    }
    return 0;
  }
}
int32_t typeck_field_reverse_infer_base_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t outer_expected) {
  {
    uint8_t fn_buf[128] = {};
    int32_t fl = 0;
    int32_t nsl = 0;
    int32_t k = 0;
    int32_t hits = 0;
    int32_t unique_ty = 0;
    int32_t nf = 0;
    int32_t j = 0;
    int32_t fjl = 0;
    uint8_t fjn[128] = {};
    int32_t bi = 0;
    int32_t match_f = 0;
    uint8_t lnm[128] = {};
    int32_t lnl = 0;
    int32_t nty = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
    if ((nsl <=0)) {
      return 0;
    }
    (void)((hits = 0));
    (void)((unique_ty = 0));
    (void)((k = 0));
    while ((k < nsl)) {
      (void)((nf = pipeline_module_struct_layout_num_fields(module, k)));
      (void)((j = 0));
      while ((j < nf)) {
        (void)((fjl = pipeline_module_struct_layout_field_name_len(module, k, j)));
        if ((fjl ==fl)) {
          (void)(pipeline_module_struct_layout_field_name_into(module, k, j, &((fjn)[0])));
          (void)((match_f = 1));
          (void)((bi = 0));
          while ((bi < fl)) {
            if (((fjn)[bi] !=(fn_buf)[bi])) {
              (void)((match_f = 0));
              break;
            }
            (void)((bi = (bi + 1)));
          }
          ((match_f !=0) ? ({   (void)((lnl = pipeline_module_struct_layout_name_len(module, k)));
  (((lnl > 0) && (lnl <=127)) ? ({   (void)(pipeline_module_struct_layout_name_into(module, k, &((lnm)[0])));
  (void)((nty = typeck_find_or_alloc_named_type_ref(arena, &((lnm)[0]), lnl)));
  ((nty > 0) ? ({   (!(((hits ==1) && (unique_ty ==nty))) ? ({   (void)((hits = (hits + 1)));
  (void)((unique_ty = nty));
  ((hits > 1) ? ({   return 0;
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
        }
        (void)((j = (j + 1)));
      }
      (void)((k = (k + 1)));
    }
    if ((hits ==1)) {
      return unique_ty;
    }
    return 0;
  }
}
int32_t typeck_named_last_segment_off(uint8_t * name, int32_t name_len) {
  int32_t i = 0;
  int32_t off = 0;
  if (((name ==0) || (name_len <=0))) {
    return 0;
  }
  while ((i < name_len)) {
    if (((name)[i] ==46)) {
      (void)((off = (i + 1)));
    }
    (void)((i = (i + 1)));
  }
  return off;
}
int32_t typeck_named_spelling_eq(uint8_t * a, int32_t a_len, uint8_t * b, int32_t b_len) {
  int32_t ao = 0;
  int32_t bo = 0;
  int32_t n = 0;
  int32_t i = 0;
  if (((((a ==0) || (b ==0)) || (a_len <=0)) || (b_len <=0))) {
    return 0;
  }
  if (typeck_name_equal(a, a_len, b, b_len)) {
    return 1;
  }
  (void)((ao = typeck_named_last_segment_off(a, a_len)));
  (void)((bo = typeck_named_last_segment_off(b, b_len)));
  (void)((n = (a_len - ao)));
  if (((n <=0) || (n !=(b_len - bo)))) {
    return 0;
  }
  while ((i < n)) {
    if (((a)[(ao + i)] !=(b)[(bo + i)])) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
}
int32_t typeck_named_is_module_concrete(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * name, int32_t name_len) {
  {
    int32_t k = 0;
    int32_t nsl = 0;
    int32_t ne = 0;
    int32_t sl = 0;
    int32_t el = 0;
    int32_t bi = 0;
    uint8_t snm[128] = {};
    int32_t nd = 0;
    int32_t di = 0;
    struct ast_Module * dm = 0;
    if (((((module ==0) || (name ==0)) || (name_len <=0)) || (name_len > 127))) {
      return 0;
    }
    (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
    (void)((k = 0));
    while ((k < nsl)) {
      (void)((sl = pipeline_module_struct_layout_name_len(module, k)));
      if (((sl > 0) && (sl <=127))) {
        (void)(pipeline_module_struct_layout_name_into(module, k, &((snm)[0])));
        ((typeck_named_spelling_eq(name, name_len, &((snm)[0]), sl) !=0) ? ({   return 1;
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    (void)((ne = ((module)->num_module_enums)));
    (void)((k = 0));
    while ((k < ne)) {
      (void)((el = pipeline_module_enum_name_len(module, k)));
      if (((el > 0) && (el <=127))) {
        (void)((bi = 0));
        while ((bi < el)) {
          (void)(((snm)[bi] = pipeline_module_enum_name_byte_at(module, k, bi)));
          (void)((bi = (bi + 1)));
        }
        ((typeck_named_spelling_eq(name, name_len, &((snm)[0]), el) !=0) ? ({   return 1;
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    if ((ctx !=0)) {
      (void)((nd = pipeline_dep_ctx_ndep(ctx)));
      (void)((di = 0));
      while ((di < nd)) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, di)));
        if (((dm !=0) && (dm !=module))) {
          (void)((nsl = pipeline_module_num_struct_layouts_at(dm)));
          (void)((k = 0));
          while ((k < nsl)) {
            (void)((sl = pipeline_module_struct_layout_name_len(dm, k)));
            if (((sl > 0) && (sl <=127))) {
              (void)(pipeline_module_struct_layout_name_into(dm, k, &((snm)[0])));
              ((typeck_named_spelling_eq(name, name_len, &((snm)[0]), sl) !=0) ? ({   return 1;
 }) : 0);
            }
            (void)((k = (k + 1)));
          }
          (void)((ne = ((dm)->num_module_enums)));
          (void)((k = 0));
          while ((k < ne)) {
            (void)((el = pipeline_module_enum_name_len(dm, k)));
            if (((el > 0) && (el <=127))) {
              (void)((bi = 0));
              while ((bi < el)) {
                (void)(((snm)[bi] = pipeline_module_enum_name_byte_at(dm, k, bi)));
                (void)((bi = (bi + 1)));
              }
              ((typeck_named_spelling_eq(name, name_len, &((snm)[0]), el) !=0) ? ({   return 1;
 }) : 0);
            }
            (void)((k = (k + 1)));
          }
        }
        (void)((di = (di + 1)));
      }
    }
    return 0;
  }
}
int32_t typeck_mono_field_type_from_base(struct ast_Module * module, struct ast_ASTArena * arena, int32_t field_ty, int32_t base_ty) {
  {
    int32_t mono_ty = 0;
    int32_t bt_kind = 0;
    uint8_t gnm[128] = {};
    int32_t gnl = 0;
    uint8_t bnm[128] = {};
    int32_t bnl = 0;
    int32_t sk = 0;
    int32_t tp_slot = 0;
    int32_t elem = 0;
    int32_t nsl = 0;
    int32_t sl = 0;
    uint8_t snm[128] = {};
    int32_t bi = 0;
    int32_t match_b = 0;
    int32_t ntp = 0;
    int32_t tj = 0;
    int32_t tpl = 0;
    uint8_t tpn[128] = {};
    int32_t pi = 0;
    int32_t peq = 0;
    int32_t ord_type_ptr = 9;
    int32_t ord_type_named = 8;
    if (((module ==0) || (arena ==0))) {
      return 0;
    }
    if (((field_ty <=0) || (field_ty > ((arena)->num_types)))) {
      return 0;
    }
    if (((base_ty <=0) || (base_ty > ((arena)->num_types)))) {
      return 0;
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    if ((bt_kind ==ord_type_ptr)) {
      (void)((elem = pipeline_type_elem_ref_at(arena, base_ty)));
      ((((elem > 0) && (elem <=((arena)->num_types))) && (pipeline_type_kind_ord_at(arena, elem) ==ord_type_named)) ? ({   (void)((base_ty = elem));
 }) : ({   return 0;
 }));
    } else {
      if ((bt_kind !=ord_type_named)) {
        return 0;
      }
    }
    if ((pipeline_type_kind_ord_at(arena, field_ty) !=ord_type_named)) {
      return 0;
    }
    (void)((gnl = pipeline_type_named_name_into(arena, field_ty, &((gnm)[0]))));
    if (((gnl <=0) || (gnl > 127))) {
      return 0;
    }
    if ((typeck_named_is_module_concrete(module, 0, &((gnm)[0]), gnl) !=0)) {
      return 0;
    }
    (void)((bnl = pipeline_type_named_name_into(arena, base_ty, &((bnm)[0]))));
    (void)((tp_slot = 0));
    if ((bnl > 0)) {
      (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
      (void)((sk = 0));
      while ((sk < nsl)) {
        (void)((sl = pipeline_module_struct_layout_name_len(module, sk)));
        if ((sl ==bnl)) {
          (void)(pipeline_module_struct_layout_name_into(module, sk, &((snm)[0])));
          (void)((match_b = 1));
          (void)((bi = 0));
          while ((bi < bnl)) {
            if (((snm)[bi] !=(bnm)[bi])) {
              (void)((match_b = 0));
              break;
            }
            (void)((bi = (bi + 1)));
          }
          ((match_b !=0) ? ({   (void)((ntp = pipeline_module_struct_layout_num_type_params_at(module, sk)));
  if ((ntp > 0)) {
    (void)((tp_slot = -1));
    (void)((tj = 0));
    while ((tj < ntp)) {
      (void)((tpl = pipeline_module_struct_layout_type_param_name_len(module, sk, tj)));
      if ((tpl ==gnl)) {
        (void)(pipeline_module_struct_layout_type_param_name_into(module, sk, tj, &((tpn)[0])));
        (void)((peq = 1));
        (void)((pi = 0));
        while ((pi < gnl)) {
          if (((tpn)[pi] !=(gnm)[pi])) {
            (void)((peq = 0));
            break;
          }
          (void)((pi = (pi + 1)));
        }
        ((peq !=0) ? ({   (void)((tp_slot = tj));
  break;
 }) : 0);
      }
      (void)((tj = (tj + 1)));
    }
    ((tp_slot < 0) ? ({   return 0;
 }) : 0);
  }
  break;
 }) : 0);
        }
        (void)((sk = (sk + 1)));
      }
    }
    (void)((mono_ty = pipeline_type_type_arg_ref_at(arena, base_ty, tp_slot)));
    if (((mono_ty <=0) && (tp_slot ==0))) {
      (void)((mono_ty = pipeline_type_elem_ref_at(arena, base_ty)));
    }
    if (((mono_ty <=0) || (mono_ty > ((arena)->num_types)))) {
      return 0;
    }
    return mono_ty;
  }
}
int32_t typeck_field_unknown_hard_fail(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t got_ty = 0;
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t check_ty = 0;
    int32_t elem_ty = 0;
    int32_t line_f = 0;
    int32_t col_f = 0;
    int32_t nlen = 0;
    uint8_t nbuf[128] = {};
    int32_t has_struct = 0;
    int32_t has_enum = 0;
    int32_t di = 0;
    int32_t nd = 0;
    struct ast_Module * dm = 0;
    int32_t k = 0;
    int32_t nsl = 0;
    int32_t ne = 0;
    int32_t sl = 0;
    int32_t el = 0;
    int32_t bi = 0;
    uint8_t snm[128] = {};
    int32_t peeled = 0;
    int32_t peeled_e = 0;
    int32_t ord_type_ptr = 9;
    int32_t ord_type_named = 8;
    int32_t ord_type_array = 10;
    int32_t ord_type_slice = 11;
    int32_t ord_type_vector = 13;
    if (((((module ==0) || (arena ==0)) || (expr_ref <=0)) || (base_ref <=0))) {
      return 0;
    }
    (void)((got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if (((!(ast_ref_is_null(got_ty)) && (got_ty > 0)) && (got_ty <=((arena)->num_types)))) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((ast_ref_is_null(base_ty) || (base_ty <=0)) || (base_ty > ((arena)->num_types)))) {
      return 0;
    }
    (void)((peeled = typeck_resolve_type_alias_ref_local(module, arena, base_ty, 0)));
    if (((!(ast_ref_is_null(peeled)) && (peeled > 0)) && (peeled <=((arena)->num_types)))) {
      (void)((base_ty = peeled));
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    (void)((check_ty = base_ty));
    if ((bt_kind ==ord_type_ptr)) {
      (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
      if (((ast_ref_is_null(elem_ty) || (elem_ty <=0)) || (elem_ty > ((arena)->num_types)))) {
        (void)((line_f = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_f = pipeline_expr_col_at(arena, expr_ref)));
        (void)(lsp_diag_report_typeck(line_f, col_f, ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x69\x65\x6c\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x74\x79\x70\x65")));
        return -1;
      }
      (void)((peeled_e = typeck_resolve_type_alias_ref_local(module, arena, elem_ty, 0)));
      if (((!(ast_ref_is_null(peeled_e)) && (peeled_e > 0)) && (peeled_e <=((arena)->num_types)))) {
        (void)((elem_ty = peeled_e));
      }
      (void)((check_ty = elem_ty));
      (void)((bt_kind = pipeline_type_kind_ord_at(arena, check_ty)));
    }
    if ((((bt_kind ==ord_type_slice) || (bt_kind ==ord_type_array)) || (bt_kind ==ord_type_vector))) {
      (void)((line_f = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_f = pipeline_expr_col_at(arena, expr_ref)));
      (void)(lsp_diag_report_typeck(line_f, col_f, ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x69\x65\x6c\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x74\x79\x70\x65")));
      return -1;
    }
    if ((bt_kind ==ord_type_named)) {
      (void)((nlen = pipeline_type_named_name_into(arena, check_ty, &((nbuf)[0]))));
      if (((nlen <=0) || (nlen > 127))) {
        return 0;
      }
      (void)((has_struct = 0));
      (void)((has_enum = 0));
      (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
      (void)((ne = ((module)->num_module_enums)));
      (void)((k = 0));
      while ((k < nsl)) {
        (void)((sl = pipeline_module_struct_layout_name_len(module, k)));
        if ((sl ==nlen)) {
          (void)(pipeline_module_struct_layout_name_into(module, k, &((snm)[0])));
          (void)((bi = 0));
          while ((bi < sl)) {
            if (((snm)[bi] !=(nbuf)[bi])) {
              break;
            }
            (void)((bi = (bi + 1)));
          }
          ((bi ==sl) ? ({   (void)((has_struct = 1));
  break;
 }) : 0);
        }
        (void)((k = (k + 1)));
      }
      (void)((k = 0));
      while ((k < ne)) {
        (void)((el = pipeline_module_enum_name_len(module, k)));
        if ((el ==nlen)) {
          (void)((bi = 0));
          while ((bi < el)) {
            if ((pipeline_module_enum_name_byte_at(module, k, bi) !=(nbuf)[bi])) {
              break;
            }
            (void)((bi = (bi + 1)));
          }
          ((bi ==el) ? ({   (void)((has_enum = 1));
  break;
 }) : 0);
        }
        (void)((k = (k + 1)));
      }
      if ((((has_struct ==0) || (has_enum ==0)) && (ctx !=0))) {
        (void)((nd = pipeline_dep_ctx_ndep(ctx)));
        (void)((di = 0));
        while ((di < nd)) {
          (void)((dm = pipeline_dep_ctx_module_at(ctx, di)));
          if ((dm !=0)) {
            if ((has_struct ==0)) {
              (void)((nsl = pipeline_module_num_struct_layouts_at(dm)));
              (void)((k = 0));
              while ((k < nsl)) {
                (void)((sl = pipeline_module_struct_layout_name_len(dm, k)));
                if ((sl ==nlen)) {
                  (void)(pipeline_module_struct_layout_name_into(dm, k, &((snm)[0])));
                  (void)((bi = 0));
                  while ((bi < sl)) {
                    if (((snm)[bi] !=(nbuf)[bi])) {
                      break;
                    }
                    (void)((bi = (bi + 1)));
                  }
                  ((bi ==sl) ? ({   (void)((has_struct = 1));
  break;
 }) : 0);
                }
                (void)((k = (k + 1)));
              }
            }
            if ((has_enum ==0)) {
              (void)((ne = ((dm)->num_module_enums)));
              (void)((k = 0));
              while ((k < ne)) {
                (void)((el = pipeline_module_enum_name_len(dm, k)));
                if ((el ==nlen)) {
                  (void)((bi = 0));
                  while ((bi < el)) {
                    if ((pipeline_module_enum_name_byte_at(dm, k, bi) !=(nbuf)[bi])) {
                      break;
                    }
                    (void)((bi = (bi + 1)));
                  }
                  ((bi ==el) ? ({   (void)((has_enum = 1));
  break;
 }) : 0);
                }
                (void)((k = (k + 1)));
              }
            }
            (((has_struct !=0) && (has_enum !=0)) ? ({   break;
 }) : 0);
          }
          (void)((di = (di + 1)));
        }
      }
      if (((has_struct ==0) && (has_enum ==0))) {
        (void)((line_f = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_f = pipeline_expr_col_at(arena, expr_ref)));
        (void)(lsp_diag_report_typeck(line_f, col_f, ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x69\x65\x6c\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x74\x79\x70\x65")));
        return -1;
      }
      (void)((line_f = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_f = pipeline_expr_col_at(arena, expr_ref)));
      if (((has_enum !=0) && (has_struct ==0))) {
        (void)(driver_diagnostic_typeck_enum_no_variant(line_f, col_f));
        return -1;
      }
      (void)(lsp_diag_report_typeck(line_f, col_f, ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x69\x65\x6c\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x74\x79\x70\x65")));
      return -1;
    }
    (void)((line_f = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col_f = pipeline_expr_col_at(arena, expr_ref)));
    (void)(lsp_diag_report_typeck(line_f, col_f, ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x66\x69\x65\x6c\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x74\x79\x70\x65")));
    return -1;
  }
}
void typeck_field_apply_mono_type_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty) {
  {
    int32_t got_ty = 0;
    int32_t mono_ty = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return;
    }
    (void)((got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if (((ast_ref_is_null(got_ty) || (got_ty <=0)) || (got_ty > ((arena)->num_types)))) {
      return;
    }
    (void)((mono_ty = typeck_mono_field_type_from_base(module, arena, got_ty, base_ty)));
    if (((mono_ty <=0) || (mono_ty ==got_ty))) {
      return;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, mono_ty));
  }
}
void typeck_field_apply_ambient_for_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t ambient_ty, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t got_ty = 0;
    int32_t use_ambient = 0;
    uint8_t gnm[128] = {};
    int32_t gnl = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return;
    }
    if (((ambient_ty <=0) || (ambient_ty > ((arena)->num_types)))) {
      return;
    }
    (void)((got_ty = pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if (((ast_ref_is_null(got_ty) || (got_ty <=0)) || (got_ty > ((arena)->num_types)))) {
      return;
    }
    if ((typeck_vector_lanes_of_type(arena, got_ty) > 0)) {
      return;
    }
    if ((pipeline_type_kind_ord_at(arena, got_ty) ==8)) {
      (void)((gnl = pipeline_type_named_name_into(arena, got_ty, &((gnm)[0]))));
      (((gnl > 0) && (gnl <=127)) ? ({   ((typeck_named_is_module_concrete(module, ctx, &((gnm)[0]), gnl) ==0) ? ({   (void)((use_ambient = 1));
 }) : 0);
 }) : 0);
    }
    ((use_ambient !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ambient_ty));
 }) : 0);
  }
}
int32_t typeck_field_layout_named(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t layout_named_ref = 0;
    uint8_t layout_nm_buf[128] = {};
    int32_t layout_nm_len = 0;
    uint8_t fn_buf[128] = {};
    int32_t fl2 = 0;
    int32_t user_ev_tag = 0;
    uint8_t nm_type_kind_ty[8] = {84, 121, 112, 101, 75, 105, 110, 100};
    int32_t skip_layout_for_type_kind = 0;
    int32_t vv = 0;
    int32_t off = 0;
    int32_t ftr = 0;
    int32_t i32r_tk = 0;
    int32_t i32r_eof = 0;
    uint8_t nm_tok_kind_ty[9] = {84, 111, 107, 101, 110, 75, 105, 110, 100};
    uint8_t nm_eof_variant[9] = {84, 79, 75, 69, 78, 95, 69, 79, 70};
    int32_t elem_ty = 0;
    int32_t peeled = 0;
    int32_t peeled_e = 0;
    int32_t dot_pos = 0;
    int32_t si = 0;
    int32_t suffix_len = 0;
    uint8_t s_i32[8] = {84, 121, 112, 101, 95, 73, 51, 50};
    uint8_t s_bool[9] = {84, 121, 112, 101, 95, 66, 79, 79, 76};
    uint8_t s_u8[7] = {84, 121, 112, 101, 95, 85, 56};
    uint8_t s_u32[8] = {84, 121, 112, 101, 95, 85, 51, 50};
    uint8_t s_u64[8] = {84, 121, 112, 101, 95, 85, 54, 52};
    uint8_t s_i64[8] = {84, 121, 112, 101, 95, 73, 54, 52};
    uint8_t s_usize[10] = {84, 121, 112, 101, 95, 85, 83, 73, 90, 69};
    uint8_t s_isize[10] = {84, 121, 112, 101, 95, 73, 83, 73, 90, 69};
    uint8_t s_named[10] = {84, 121, 112, 101, 95, 78, 65, 77, 69, 68};
    uint8_t s_ptr[8] = {84, 121, 112, 101, 95, 80, 84, 82};
    uint8_t s_arr[10] = {84, 121, 112, 101, 95, 65, 82, 82, 65, 89};
    uint8_t s_sli[10] = {84, 121, 112, 101, 95, 83, 76, 73, 67, 69};
    uint8_t s_vec[11] = {84, 121, 112, 101, 95, 86, 69, 67, 84, 79, 82};
    uint8_t s_f32[8] = {84, 121, 112, 101, 95, 70, 51, 50};
    uint8_t s_f64[8] = {84, 121, 112, 101, 95, 70, 54, 52};
    uint8_t s_void[9] = {84, 121, 112, 101, 95, 86, 79, 73, 68};
    if (((arena ==0) || (module ==0))) {
      return 0;
    }
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((ast_ref_is_null(base_ty) || (base_ty <=0)) || (base_ty > ((arena)->num_types)))) {
      return 0;
    }
    (void)((peeled = typeck_resolve_type_alias_ref_local(module, arena, base_ty, 0)));
    if (((!(ast_ref_is_null(peeled)) && (peeled > 0)) && (peeled <=((arena)->num_types)))) {
      (void)((base_ty = peeled));
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    (void)((layout_named_ref = 0));
    if ((bt_kind ==9)) {
      (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
      if ((!(ast_ref_is_null(elem_ty)) && (elem_ty > 0))) {
        (void)((peeled_e = typeck_resolve_type_alias_ref_local(module, arena, elem_ty, 0)));
        (((!(ast_ref_is_null(peeled_e)) && (peeled_e > 0)) && (peeled_e <=((arena)->num_types))) ? ({   (void)((elem_ty = peeled_e));
 }) : 0);
      }
      ((!(ast_ref_is_null(elem_ty)) && (pipeline_type_kind_ord_at(arena, elem_ty) ==8)) ? ({   (void)((layout_named_ref = elem_ty));
 }) : 0);
    } else {
      if ((bt_kind ==8)) {
        (void)((layout_named_ref = base_ty));
      }
    }
    if ((layout_named_ref ==0)) {
      return 0;
    }
    (void)((layout_nm_len = pipeline_type_named_name_into(arena, layout_named_ref, &((layout_nm_buf)[0]))));
    if (((layout_nm_len <=0) || (pipeline_type_kind_ord_at(arena, layout_named_ref) !=8))) {
      return 0;
    }
    (void)((fl2 = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl2 <=0) || (fl2 > 127))) {
      return 0;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    (void)((user_ev_tag = pipeline_module_enum_variant_tag_for_names(module, &((layout_nm_buf)[0]), layout_nm_len, &((fn_buf)[0]), fl2)));
    if ((user_ev_tag >=0)) {
      (void)(pipeline_expr_set_field_access_enum_variant(arena, expr_ref, user_ev_tag));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, layout_named_ref));
      return 2;
    }
    (void)((vv = -1));
    (void)((skip_layout_for_type_kind = 0));
    if (((layout_nm_len ==8) && typeck_name_equal(&((layout_nm_buf)[0]), layout_nm_len, &((nm_type_kind_ty)[0]), 8))) {
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_i32)[0]), 8))) {
        (void)((vv = 0));
      }
      if ((((vv < 0) && (fl2 ==9)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_bool)[0]), 9))) {
        (void)((vv = 1));
      }
      if ((((vv < 0) && (fl2 ==7)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_u8)[0]), 7))) {
        (void)((vv = 2));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_u32)[0]), 8))) {
        (void)((vv = 3));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_u64)[0]), 8))) {
        (void)((vv = 4));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_i64)[0]), 8))) {
        (void)((vv = 5));
      }
      if ((((vv < 0) && (fl2 ==10)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_usize)[0]), 10))) {
        (void)((vv = 6));
      }
      if ((((vv < 0) && (fl2 ==10)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_isize)[0]), 10))) {
        (void)((vv = 7));
      }
      if ((((vv < 0) && (fl2 ==10)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_named)[0]), 10))) {
        (void)((vv = 8));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_ptr)[0]), 8))) {
        (void)((vv = 9));
      }
      if ((((vv < 0) && (fl2 ==10)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_arr)[0]), 10))) {
        (void)((vv = 10));
      }
      if ((((vv < 0) && (fl2 ==10)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_sli)[0]), 10))) {
        (void)((vv = 11));
      }
      if ((((vv < 0) && (fl2 ==11)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_vec)[0]), 11))) {
        (void)((vv = 12));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_f32)[0]), 8))) {
        (void)((vv = 13));
      }
      if ((((vv < 0) && (fl2 ==8)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_f64)[0]), 8))) {
        (void)((vv = 14));
      }
      if ((((vv < 0) && (fl2 ==9)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((s_void)[0]), 9))) {
        (void)((vv = 15));
      }
      ((vv >=0) ? ({   (void)((i32r_tk = typeck_ensure_i32_type_ref(arena)));
  if ((i32r_tk !=0)) {
    (void)(pipeline_expr_set_field_access_enum_variant(arena, expr_ref, vv));
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_tk));
  }
  (void)((skip_layout_for_type_kind = 1));
 }) : 0);
    }
    (void)((off = -1));
    (void)((ftr = 0));
    if ((skip_layout_for_type_kind ==0)) {
      (void)((dot_pos = -1));
      (void)((si = 0));
      while ((si < layout_nm_len)) {
        if (((layout_nm_buf)[si] ==46)) {
          (void)((dot_pos = si));
        }
        (void)((si = (si + 1)));
      }
      if (((dot_pos >=0) && ((dot_pos + 1) < layout_nm_len))) {
        (void)((suffix_len = (layout_nm_len - (dot_pos + 1))));
        (void)((si = 0));
        while ((si < suffix_len)) {
          (void)(((layout_nm_buf)[si] = (layout_nm_buf)[((dot_pos + 1) + si)]));
          (void)((si = (si + 1)));
        }
        (void)(((layout_nm_buf)[suffix_len] = 0));
        (void)((layout_nm_len = suffix_len));
      }
      (void)((off = typeck_get_field_offset_from_layout_deps(module, ctx, &((layout_nm_buf)[0]), layout_nm_len, &((fn_buf)[0]), fl2)));
      if ((off >=0)) {
        (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, off));
      }
      (void)((ftr = typeck_get_field_type_ref_from_layout_deps(module, arena, ctx, &((layout_nm_buf)[0]), layout_nm_len, &((fn_buf)[0]), fl2)));
      ((ftr !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ftr));
 }) : 0);
    }
    if (((((((off < 0) && (ftr ==0)) && (layout_nm_len ==9)) && typeck_name_equal(&((layout_nm_buf)[0]), layout_nm_len, &((nm_tok_kind_ty)[0]), 9)) && (fl2 ==9)) && typeck_name_equal(&((fn_buf)[0]), fl2, &((nm_eof_variant)[0]), 9))) {
      (void)((i32r_eof = typeck_ensure_i32_type_ref(arena)));
      ((i32r_eof !=0) ? ({   (void)(pipeline_expr_set_field_access_enum_variant(arena, expr_ref, 0));
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, i32r_eof));
 }) : 0);
    }
    return 0;
  }
}
void typeck_field_slice(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref) {
  {
    int32_t base_ty = 0;
    int32_t elem_ty = 0;
    int32_t fl = 0;
    int32_t bt_kind = 0;
    uint8_t fn_buf[128] = {};
    uint8_t len_nm[6] = {108, 101, 110, 103, 116, 104};
    uint8_t dat_nm[4] = {100, 97, 116, 97};
    int32_t ut = 0;
    int32_t ptr_ref = 0;
    if ((((arena ==0) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((base_ty <=0) || (base_ty > ((arena)->num_types)))) {
      return;
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    if (((((bt_kind ==10) || (bt_kind ==13)) && (fl ==6)) && typeck_name_equal(&((fn_buf)[0]), fl, &((len_nm)[0]), 6))) {
      if ((pipeline_type_array_size_at(arena, base_ty) <=0)) {
        return;
      }
      (void)((ut = typeck_ensure_usize_type_ref(arena)));
      if ((ut !=0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ut));
      }
      return;
    }
    if ((bt_kind !=11)) {
      return;
    }
    (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
    if ((elem_ty <=0)) {
      return;
    }
    if (((fl ==6) && typeck_name_equal(&((fn_buf)[0]), fl, &((len_nm)[0]), 6))) {
      (void)((ut = typeck_ensure_usize_type_ref(arena)));
      if ((ut !=0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ut));
      }
      (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 8));
      return;
    }
    (((fl ==4) && typeck_name_equal(&((fn_buf)[0]), fl, &((dat_nm)[0]), 4)) ? ({   (void)(pipeline_expr_set_field_access_offset(arena, expr_ref, 0));
  (void)((ptr_ref = typeck_find_or_alloc_ptr_type_ref(arena, elem_ty)));
  ((ptr_ref !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_ref));
 }) : 0);
 }) : 0);
  }
}
void typeck_field_name_fallback(struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref) {
  {
    int32_t fl = 0;
    uint8_t fn_buf[128] = {};
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t named_ref = 0;
    uint8_t cob_nm[128] = {};
    int32_t cob_len = 0;
    uint8_t nm_dat[4] = {100, 97, 116, 97};
    uint8_t nm_cob[13] = {67, 111, 100, 101, 103, 101, 110, 79, 117, 116, 66, 117, 102};
    int32_t u8r_cob = 0;
    int32_t arr_cob = 0;
    int32_t u8_fb = 0;
    int32_t arr_fb = 0;
    int32_t scalar_fb = 0;
    int32_t elem_r = 0;
    if ((arena ==0)) {
      return;
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref)))) {
      return;
    }
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    if (((((fl ==4) && !(ast_ref_is_null(base_ref))) && (base_ref > 0)) && (base_ref <=((arena)->num_exprs)))) {
      (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
      (((!(ast_ref_is_null(base_ty)) && (base_ty > 0)) && (base_ty <=((arena)->num_types))) ? ({   (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
  (void)((named_ref = 0));
  if ((bt_kind ==9)) {
    (void)((elem_r = pipeline_type_elem_ref_at(arena, base_ty)));
    ((!(ast_ref_is_null(elem_r)) && (pipeline_type_kind_ord_at(arena, elem_r) ==8)) ? ({   (void)((named_ref = elem_r));
 }) : 0);
  } else {
    if ((bt_kind ==8)) {
      (void)((named_ref = base_ty));
    }
  }
  (((named_ref !=0) && typeck_name_equal(&((fn_buf)[0]), fl, &((nm_dat)[0]), 4)) ? ({   (void)((cob_len = pipeline_type_named_name_into(arena, named_ref, &((cob_nm)[0]))));
  (((cob_len ==13) && typeck_name_equal(&((cob_nm)[0]), cob_len, &((nm_cob)[0]), 13)) ? ({   (void)((u8r_cob = typeck_ensure_u8_type_ref(arena)));
  ((u8r_cob !=0) ? ({   (void)((arr_cob = typeck_find_or_alloc_array_type_ref(arena, u8r_cob, 8388608)));
  ((arr_cob !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_cob));
  return;
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref)))) {
      return;
    }
    (void)((u8_fb = typeck_inline_u8_64_array_field_type_ref(arena, &((fn_buf)[0]), fl)));
    if ((u8_fb !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, u8_fb));
      return;
    }
    (void)((arr_fb = typeck_expr_inline_array_field_type_ref(arena, &((fn_buf)[0]), fl)));
    if ((arr_fb !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_fb));
      return;
    }
    (void)((scalar_fb = typeck_expr_field_access_fallback_scalar_type_ref(arena, &((fn_buf)[0]), fl)));
    ((scalar_fb !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, scalar_fb));
 }) : 0);
  }
}
void typeck_field_lexer_fallback(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t base_ty = 0;
    int32_t elem_ty = 0;
    int32_t fl = 0;
    uint8_t fn_buf[128] = {};
    uint8_t vbuf[128] = {};
    int32_t vnlen = 0;
    int32_t pr_fb = 0;
    int32_t lx_fb = 0;
    int32_t fi = 0;
    if (((arena ==0) || (module ==0))) {
      return;
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref)))) {
      return;
    }
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return;
    }
    (void)((fl = pipeline_expr_field_access_name_len(arena, expr_ref)));
    if (((fl <=0) || (fl > 127))) {
      return;
    }
    (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((fn_buf)[0])));
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((!(ast_ref_is_null(base_ty)) && (base_ty > 0)) && (base_ty <=((arena)->num_types)))) {
      (void)((lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, base_ty, &((fn_buf)[0]), fl)));
      if ((lx_fb !=0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb));
        return;
      }
      ((pipeline_type_kind_ord_at(arena, base_ty) ==9) ? ({   (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
  (!(ast_ref_is_null(elem_ty)) ? ({   (void)((lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, elem_ty, &((fn_buf)[0]), fl)));
  ((lx_fb !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb));
  return;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref)))) {
      return;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=3)) {
      return;
    }
    (void)((vnlen = pipeline_expr_var_name_len(arena, base_ref)));
    if (((vnlen <=0) || (vnlen > 127))) {
      return;
    }
    if ((ctx ==0)) {
      return;
    }
    (void)((fi = pipeline_dep_ctx_current_func_index(ctx)));
    if (((fi < 0) || (fi >=((module)->num_funcs)))) {
      return;
    }
    (void)(pipeline_expr_var_name_into(arena, base_ref, &((vbuf)[0])));
    (void)((pr_fb = pipeline_module_func_param_type_ref_for_name(module, fi, &((vbuf)[0]), vnlen)));
    if (ast_ref_is_null(pr_fb)) {
      return;
    }
    (void)((lx_fb = typeck_field_access_lexer_wrapper_fallback(arena, pr_fb, &((fn_buf)[0]), fl)));
    ((lx_fb !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, lx_fb));
 }) : 0);
  }
}
int typeck_expr_var_name_equal_func(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index) {
  {
    uint8_t * vbuf = typeck_scratch64_slot(8);
    int32_t b_len = 0;
    int32_t a_len = 0;
    int32_t i = 0;
    if (((callee_expr_ref <=0) || (callee_expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=3)) {
      return 0;
    }
    (void)((b_len = pipeline_expr_var_name_len(arena, callee_expr_ref)));
    if (((func_index < 0) || (func_index >=((mod)->num_funcs)))) {
      return 0;
    }
    (void)((a_len = pipeline_module_func_name_len_at(mod, func_index)));
    if ((((a_len !=b_len) || (a_len <=0)) || (a_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, callee_expr_ref, vbuf));
    while ((i < a_len)) {
      if ((pipeline_module_func_name_byte_at(mod, func_index, i) !=(vbuf)[i])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int32_t typeck_find_or_alloc_named_type_ref(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len) {
  {
    int32_t k = 0;
    int32_t ko = 0;
    int32_t exist_len = 0;
    int32_t ord_named = 8;
    uint8_t * nm_scr = typeck_scratch64_slot(12);
    if (((((arena ==0) || (name ==0)) || (name_len <=0)) || (name_len > 127))) {
      return 0;
    }
    (void)((k = 1));
    while ((k <=((arena)->num_types))) {
      (void)((ko = pipeline_type_kind_ord_at(arena, k)));
      if ((ko ==ord_named)) {
        (void)((exist_len = pipeline_type_named_name_into(arena, k, nm_scr)));
        (((exist_len ==name_len) && typeck_name_equal(nm_scr, exist_len, name, name_len)) ? ({   return k;
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    (void)((k = pipeline_arena_type_alloc(arena)));
    if ((k <=0)) {
      return 0;
    }
    if ((pipeline_type_init_named_at(arena, k, name, name_len) ==0)) {
      return 0;
    }
    return k;
  }
}
int32_t typeck_field_access_lexer_wrapper_fallback(struct ast_ASTArena * arena, int32_t base_type_ref, uint8_t * field_name, int32_t field_name_len) {
  {
    if (((ast_ref_is_null(base_type_ref) || (base_type_ref <=0)) || (base_type_ref > ((arena)->num_types)))) {
      return 0;
    }
    uint8_t bn[128] = {};
    int32_t bn_len = pipeline_type_named_name_into(arena, base_type_ref, &((bn)[0]));
    if (((bn_len <=0) || (bn_len > 127))) {
      return 0;
    }
    uint8_t nm_lexer[5] = {76, 101, 120, 101, 114};
    uint8_t nm_next_lex[8] = {110, 101, 120, 95, 108, 101, 120};
    uint8_t nm_token_start[11] = {116, 111, 107, 101, 110, 95, 115, 116, 97, 114, 116};
    uint8_t nm_lex[3] = {108, 101, 120};
    uint8_t nm_pos[3] = {112, 111, 115};
    uint8_t nm_line[4] = {108, 105, 110, 101};
    uint8_t nm_col[3] = {99, 111, 108};
    uint8_t nm_lres[11] = {76, 101, 120, 101, 114, 82, 101, 115, 117, 108, 116};
    uint8_t nm_cir[21] = {67, 111, 108, 108, 101, 99, 116, 73, 109, 112, 111, 114, 116, 115, 82, 101, 115, 117, 108, 116};
    uint8_t nm_tsar[18] = {84, 114, 121, 83, 107, 105, 112, 65, 108, 108, 111, 119, 82, 101, 115, 117, 108, 116};
    uint8_t nm_lpr[19] = {76, 105, 98, 114, 97, 114, 121, 80, 97, 114, 115, 101, 82, 101, 115, 117, 108, 116};
    uint8_t nm_per[15] = {80, 97, 114, 115, 101, 69, 120, 112, 114, 82, 101, 115, 117, 108, 116};
    uint8_t nm_pbr[16] = {80, 97, 114, 115, 101, 66, 108, 111, 99, 107, 82, 101, 115, 117, 108, 116};
    uint8_t nm_tlr[17] = {84, 111, 112, 76, 101, 118, 101, 108, 76, 101, 116, 82, 101, 115, 117, 108, 116};
    int32_t lex_tr = typeck_find_or_alloc_named_type_ref(arena, &((nm_lexer)[0]), 5);
    if ((lex_tr ==0)) {
      return 0;
    }
    if (((field_name_len ==8) && typeck_name_equal(field_name, field_name_len, &((nm_next_lex)[0]), 8))) {
      if (((bn_len ==11) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_lres)[0]), 11))) {
        return lex_tr;
      }
      if (((bn_len ==19) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_lpr)[0]), 19))) {
        return lex_tr;
      }
      if (((bn_len ==15) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_per)[0]), 15))) {
        return lex_tr;
      }
      if (((bn_len ==16) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_pbr)[0]), 16))) {
        return lex_tr;
      }
      (((bn_len ==17) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_tlr)[0]), 17)) ? ({   return lex_tr;
 }) : 0);
    }
    if (((field_name_len ==11) && typeck_name_equal(field_name, field_name_len, &((nm_token_start)[0]), 11))) {
      (((bn_len ==11) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_lres)[0]), 11)) ? ({   return typeck_ensure_usize_type_ref(arena);
 }) : 0);
    }
    if (((field_name_len ==3) && typeck_name_equal(field_name, field_name_len, &((nm_lex)[0]), 3))) {
      if (((bn_len ==21) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_cir)[0]), 21))) {
        return lex_tr;
      }
      (((bn_len ==18) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_tsar)[0]), 18)) ? ({   return lex_tr;
 }) : 0);
    }
    if (((bn_len ==5) && typeck_name_equal(&((bn)[0]), bn_len, &((nm_lexer)[0]), 5))) {
      if (((field_name_len ==3) && typeck_name_equal(field_name, field_name_len, &((nm_pos)[0]), 3))) {
        return typeck_ensure_usize_type_ref(arena);
      }
      if (((field_name_len ==4) && typeck_name_equal(field_name, field_name_len, &((nm_line)[0]), 4))) {
        return typeck_ensure_i32_type_ref(arena);
      }
      (((field_name_len ==3) && typeck_name_equal(field_name, field_name_len, &((nm_col)[0]), 3)) ? ({   return typeck_ensure_i32_type_ref(arena);
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_ensure_primitive_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord) {
  {
    int32_t k = 0;
    int32_t ko = 0;
    int32_t er = 0;
    int32_t asz = 0;
    uint8_t * a_u8 = 0;
    int32_t ci = 0;
    if ((((arena ==0) || (kind_ord < 0)) || (kind_ord > 17))) {
      return 0;
    }
    (void)((a_u8 = ((uint8_t *)(arena))));
    if ((g_typeck_prim_arena !=a_u8)) {
      (void)((g_typeck_prim_arena = a_u8));
      (void)((ci = 0));
      while ((ci <=17)) {
        (void)(((g_typeck_prim_ref)[ci] = 0));
        (void)((ci = (ci + 1)));
      }
    }
    if (((g_typeck_prim_ref)[kind_ord] > 0)) {
      return (g_typeck_prim_ref)[kind_ord];
    }
    (void)((k = 1));
    while ((k <=((arena)->num_types))) {
      (void)((ko = pipeline_type_kind_ord_at(arena, k)));
      if ((ko ==kind_ord)) {
        (void)((er = pipeline_type_elem_ref_at(arena, k)));
        (void)((asz = pipeline_type_array_size_at(arena, k)));
        (((er ==0) && (asz ==0)) ? ({   (void)(((g_typeck_prim_ref)[kind_ord] = k));
  return k;
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    (void)((k = pipeline_arena_type_alloc(arena)));
    if ((k <=0)) {
      return 0;
    }
    if ((pipeline_type_init_primitive_kind_at(arena, k, kind_ord) ==0)) {
      return 0;
    }
    (void)(((g_typeck_prim_ref)[kind_ord] = k));
    return k;
  }
}
int32_t typeck_ensure_i32_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 0);
}
int32_t typeck_ensure_u8_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 2);
}
int32_t typeck_ensure_bool_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 1);
}
int32_t typeck_ensure_f32_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 14);
}
int32_t typeck_ensure_f64_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 15);
}
int32_t typeck_ensure_usize_type_ref(struct ast_ASTArena * arena) {
  return typeck_ensure_primitive_by_kind_ord(arena, 6);
}
int32_t typeck_ensure_void_type_ref(struct ast_ASTArena * a) {
  return typeck_ensure_primitive_by_kind_ord(a, 16);
}
int32_t typeck_map_import_binding_named_to_caller(struct ast_Module * entry_mod, int32_t dep_ix, struct ast_ASTArena * caller_arena, uint8_t * nm, int32_t nlen) {
  {
    int32_t bl = 0;
    int32_t qlen = 0;
    int32_t i = 0;
    uint8_t * qnm = typeck_scratch64_slot(15);
    if ((((caller_arena ==0) || (nm ==0)) || (nlen <=0))) {
      return 0;
    }
    if ((((entry_mod ==0) || (dep_ix < 0)) || (dep_ix >=((entry_mod)->num_imports)))) {
      return typeck_find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    if ((pipeline_module_import_kind_at(entry_mod, dep_ix) !=1)) {
      return typeck_find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    (void)((bl = pipeline_module_import_binding_name_len(entry_mod, dep_ix)));
    if (((bl <=0) || (((bl + 1) + nlen) > 127))) {
      return typeck_find_or_alloc_named_type_ref(caller_arena, nm, nlen);
    }
    while ((i < bl)) {
      (void)(((qnm)[i] = pipeline_module_import_binding_name_byte_at(entry_mod, dep_ix, i)));
      (void)((i = (i + 1)));
    }
    (void)(((qnm)[bl] = 46));
    (void)((i = 0));
    while ((i < nlen)) {
      (void)(((qnm)[((bl + 1) + i)] = (nm)[i]));
      (void)((i = (i + 1)));
    }
    (void)((qlen = ((bl + 1) + nlen)));
    return typeck_find_or_alloc_named_type_ref(caller_arena, qnm, qlen);
  }
}
int32_t typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx) {
  {
    struct ast_ASTArena * dep_arena = 0;
    int32_t kind = 0;
    int32_t nlen = 0;
    uint8_t * nm_buf = typeck_scratch64_slot(0);
    int32_t ord_named = 8;
    if (((from_dep_index < 0) || (ctx ==0))) {
      return 0;
    }
    (void)((dep_arena = pipeline_dep_ctx_arena_at(ctx, from_dep_index)));
    if ((dep_arena ==0)) {
      (void)((dep_arena = pipeline_get_dep_arena_slot(from_dep_index)));
      ((dep_arena ==0) ? ({   return 0;
 }) : 0);
    }
    if ((from_dep_index >=pipeline_dep_ctx_ndep(ctx))) {
      ((pipeline_dep_ctx_module_at(ctx, from_dep_index) ==0) ? ({   return 0;
 }) : 0);
    }
    if (((g_typeck_entry_module_for_dep_map !=0) && (dep_return_type_ref > 0))) {
      ((dep_return_type_ref <=((dep_arena)->num_types)) ? ({   (void)((kind = pipeline_type_kind_ord_at(dep_arena, dep_return_type_ref)));
  ((kind ==ord_named) ? ({   (void)((nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf)));
  ((nlen > 0) ? ({   return typeck_map_import_binding_named_to_caller(g_typeck_entry_module_for_dep_map, from_dep_index, caller_arena, nm_buf, nlen);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    return typeck_dep_return_type_to_caller_arena(dep_arena, dep_return_type_ref, caller_arena);
  }
}
int32_t typeck_ensure_i64_type_ref(struct ast_ASTArena * caller_arena) {
  return typeck_ensure_primitive_by_kind_ord(caller_arena, 5);
}
int32_t typeck_find_or_alloc_compound_type_ref(struct ast_ASTArena * a, int32_t kind_ord, int32_t elem_ref, int32_t array_size) {
  if ((((a ==0) || (kind_ord < 0)) || (kind_ord > 15))) {
    return 0;
  }
  return pipeline_type_find_or_alloc_compound(a, kind_ord, elem_ref, array_size);
}
int32_t typeck_find_or_alloc_array_type_ref(struct ast_ASTArena * a, int32_t elem_ref, int32_t array_size) {
  if ((elem_ref ==0)) {
    return 0;
  }
  return typeck_find_or_alloc_compound_type_ref(a, 10, elem_ref, array_size);
}
int32_t typeck_ensure_array_type_ref_named_elem(struct ast_ASTArena * a, uint8_t * elem_nm, int32_t elem_nm_len, int32_t array_size) {
  int32_t elem_ref = typeck_find_or_alloc_named_type_ref(a, elem_nm, elem_nm_len);
  if ((elem_ref ==0)) {
    return 0;
  }
  return typeck_find_or_alloc_array_type_ref(a, elem_ref, array_size);
}
int32_t typeck_ensure_kind_only_type_ref(struct ast_ASTArena * w, enum ast_TypeKind kind) {
  return typeck_ensure_primitive_by_kind_ord(w, ((int32_t)(kind)));
}
int32_t typeck_find_or_alloc_ptr_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return typeck_find_or_alloc_compound_type_ref(w, 9, elem_ref, 0);
}
int32_t typeck_find_or_alloc_slice_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return pipeline_type_find_or_alloc_slice(w, elem_ref, 0, 0);
}
int32_t typeck_find_or_alloc_linear_type_ref(struct ast_ASTArena * w, int32_t elem_ref) {
  return typeck_find_or_alloc_compound_type_ref(w, 12, elem_ref, 0);
}
int32_t typeck_find_or_alloc_vector_type_ref(struct ast_ASTArena * w, int32_t elem_ref, int32_t array_size) {
  return typeck_find_or_alloc_compound_type_ref(w, 13, elem_ref, array_size);
}
int32_t typeck_dep_return_type_to_caller_arena(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena) {
  {
    int32_t kind = 0;
    int32_t inner_mapped = 0;
    int32_t elem_ref = 0;
    int32_t array_size = 0;
    int32_t nlen = 0;
    uint8_t * nm_buf = typeck_scratch64_slot(0);
    int32_t ord_i32 = 0;
    int32_t ord_bool = 1;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_linear = 12;
    int32_t ord_vector = 13;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_usize = 6;
    int32_t ord_void = 16;
    if ((dep_return_type_ref <=0)) {
      return 0;
    }
    (void)((kind = pipeline_type_kind_ord_at(dep_arena, dep_return_type_ref)));
    if ((kind < 0)) {
      return 0;
    }
    if ((((((((((((kind ==ord_i32) || (kind ==ord_i64)) || (kind ==ord_bool)) || (kind ==ord_f64)) || (kind ==ord_u8)) || (kind ==ord_u32)) || (kind ==ord_u64)) || (kind ==ord_isize)) || (kind ==ord_f32)) || (kind ==ord_usize)) || (kind ==ord_void))) {
      return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
    }
    if ((kind ==ord_named)) {
      (void)((nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf)));
      if ((nlen <=0)) {
        return 0;
      }
      return typeck_find_or_alloc_named_type_ref(caller_arena, nm_buf, nlen);
    }
    (void)((elem_ref = pipeline_type_elem_ref_at(dep_arena, dep_return_type_ref)));
    (void)((inner_mapped = 0));
    if (!(ast_ref_is_null(elem_ref))) {
      (void)((inner_mapped = typeck_dep_return_type_to_caller_arena(dep_arena, elem_ref, caller_arena)));
      ((inner_mapped ==0) ? ({   return 0;
 }) : 0);
    }
    (void)((array_size = pipeline_type_array_size_at(dep_arena, dep_return_type_ref)));
    if ((kind ==ord_slice)) {
      int32_t rlen = pipeline_type_region_label_len_at(dep_arena, dep_return_type_ref);
      uint8_t * rbuf = typeck_scratch64_slot(14);
      if ((rlen > 0)) {
        (void)(pipeline_type_region_label_into(dep_arena, dep_return_type_ref, rbuf));
      }
      return pipeline_type_find_or_alloc_slice(caller_arena, inner_mapped, rbuf, rlen);
    }
    if ((kind ==ord_ptr)) {
      return typeck_find_or_alloc_ptr_type_ref(caller_arena, inner_mapped);
    }
    if ((kind ==ord_linear)) {
      return typeck_find_or_alloc_linear_type_ref(caller_arena, inner_mapped);
    }
    if ((kind ==ord_vector)) {
      return typeck_find_or_alloc_vector_type_ref(caller_arena, inner_mapped, array_size);
    }
    if ((kind ==ord_array)) {
      if ((ast_ref_is_null(elem_ref) || (array_size <=0))) {
        return 0;
      }
      return typeck_find_or_alloc_array_type_ref(caller_arena, inner_mapped, array_size);
    }
    if ((!(ast_ref_is_null(elem_ref)) || (array_size !=0))) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(dep_arena, dep_return_type_ref, nm_buf)));
    if ((nlen !=0)) {
      return 0;
    }
    return typeck_ensure_primitive_by_kind_ord(caller_arena, kind);
  }
}
int32_t typeck_expr_field_access_fallback_scalar_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  if ((field_name_len >=4)) {
    int32_t br = (field_name_len - 4);
    ((((((field_name)[br] ==95) && ((field_name)[(br + 1)] ==114)) && ((field_name)[(br + 2)] ==101)) && ((field_name)[(br + 3)] ==102)) ? ({   return typeck_ensure_i32_type_ref(arena);
 }) : 0);
  }
  uint8_t nm_match_num_arms[14] = {109, 97, 116, 99, 104, 95, 110, 117, 109, 95, 97, 114, 109, 115};
  uint8_t nm_field_access_is_enum_variant[28] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 105, 115, 95, 101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116};
  uint8_t nm_field_access_field_len[22] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 108, 101, 110};
  uint8_t nm_field_access_offset[19] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 111, 102, 102, 115, 101, 116};
  uint8_t nm_index_base_is_slice[19] = {105, 110, 100, 101, 120, 95, 98, 97, 115, 101, 95, 105, 115, 95, 115, 108, 105, 99, 101};
  uint8_t nm_call_num_args[13] = {99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115};
  uint8_t nm_method_call_name_len[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101, 95, 108, 101, 110};
  uint8_t nm_method_call_num_args[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 117, 109, 95, 97, 114, 103, 115};
  uint8_t nm_const_folded_val[16] = {99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95, 118, 97, 108};
  uint8_t nm_const_folded_valid[18] = {99, 111, 110, 115, 116, 95, 102, 111, 108, 100, 101, 100, 95, 118, 97, 108, 105, 100};
  uint8_t nm_index_proven_in_bounds[22] = {105, 110, 100, 101, 120, 95, 112, 114, 111, 118, 101, 110, 95, 105, 110, 95, 98, 111, 117, 110, 100, 115};
  uint8_t nm_call_resolved_func_index[24] = {99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 102, 117, 110, 99, 95, 105, 110, 100, 101, 120};
  uint8_t nm_call_resolved_dep_index[22] = {99, 97, 108, 108, 95, 114, 101, 115, 111, 108, 118, 101, 100, 95, 100, 101, 112, 95, 105, 110, 100, 101, 120};
  uint8_t nm_enum_variant_tag[16] = {101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 116, 97, 103};
  if (((field_name_len ==14) && typeck_name_equal(field_name, field_name_len, &((nm_match_num_arms)[0]), 14))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==28) && typeck_name_equal(field_name, field_name_len, &((nm_field_access_is_enum_variant)[0]), 28))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && typeck_name_equal(field_name, field_name_len, &((nm_field_access_field_len)[0]), 22))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==19) && typeck_name_equal(field_name, field_name_len, &((nm_field_access_offset)[0]), 19))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==19) && typeck_name_equal(field_name, field_name_len, &((nm_index_base_is_slice)[0]), 19))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==13) && typeck_name_equal(field_name, field_name_len, &((nm_call_num_args)[0]), 13))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==20) && typeck_name_equal(field_name, field_name_len, &((nm_method_call_name_len)[0]), 20))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==20) && typeck_name_equal(field_name, field_name_len, &((nm_method_call_num_args)[0]), 20))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==16) && typeck_name_equal(field_name, field_name_len, &((nm_const_folded_val)[0]), 16))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==18) && typeck_name_equal(field_name, field_name_len, &((nm_const_folded_valid)[0]), 18))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && typeck_name_equal(field_name, field_name_len, &((nm_index_proven_in_bounds)[0]), 22))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==24) && typeck_name_equal(field_name, field_name_len, &((nm_call_resolved_func_index)[0]), 24))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==22) && typeck_name_equal(field_name, field_name_len, &((nm_call_resolved_dep_index)[0]), 22))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  if (((field_name_len ==16) && typeck_name_equal(field_name, field_name_len, &((nm_enum_variant_tag)[0]), 16))) {
    return typeck_ensure_i32_type_ref(arena);
  }
  return 0;
}
int32_t typeck_get_field_type_ref_from_layout_deps(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, uint8_t * type_name, int32_t type_name_len, uint8_t * field_name, int32_t field_name_len) {
  {
    uint8_t nm_funcs_pool[5] = {102, 117, 110, 99, 115};
    uint8_t nm_func_elem[4] = {70, 117, 110, 99};
    if (((field_name_len ==5) && typeck_name_equal(field_name, field_name_len, &((nm_funcs_pool)[0]), 5))) {
      int32_t arr_funcs_pool = typeck_ensure_array_type_ref_named_elem(arena, &((nm_func_elem)[0]), 4, 256);
      ((arr_funcs_pool !=0) ? ({   return arr_funcs_pool;
 }) : 0);
    }
    uint8_t nm_struct_layouts_pool[14] = {115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
    uint8_t nm_sl_elem[12] = {83, 116, 114, 117, 99, 116, 76, 97, 121, 111, 117, 116};
    if (((field_name_len ==14) && typeck_name_equal(field_name, field_name_len, &((nm_struct_layouts_pool)[0]), 14))) {
      int32_t arr_sl_pool = typeck_ensure_array_type_ref_named_elem(arena, &((nm_sl_elem)[0]), 12, 32);
      ((arr_sl_pool !=0) ? ({   return arr_sl_pool;
 }) : 0);
    }
    uint8_t nm_num_struct_layouts_pool[18] = {110, 117, 109, 95, 115, 116, 114, 117, 99, 116, 95, 108, 97, 121, 111, 117, 116, 115};
    if (((field_name_len ==18) && typeck_name_equal(field_name, field_name_len, &((nm_num_struct_layouts_pool)[0]), 18))) {
      return typeck_ensure_i32_type_ref(arena);
    }
    int32_t u8_inline = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
    if ((u8_inline !=0)) {
      return u8_inline;
    }
    int32_t i32_arr_inline = typeck_expr_inline_array_field_type_ref(arena, field_name, field_name_len);
    if ((i32_arr_inline !=0)) {
      return i32_arr_inline;
    }
    int32_t r = typeck_get_field_type_ref_from_layout(module, type_name, type_name_len, field_name, field_name_len);
    if ((r !=0)) {
      return r;
    }
    if ((ctx ==0)) {
      return 0;
    }
    int32_t nd2 = pipeline_dep_ctx_ndep(ctx);
    int32_t di = 0;
    while ((di < nd2)) {
      struct ast_Module * dm = pipeline_dep_ctx_module_at(ctx, di);
      if ((dm !=0)) {
        (void)((r = typeck_get_field_type_ref_from_layout(dm, type_name, type_name_len, field_name, field_name_len)));
        ((r !=0) ? ({   struct ast_ASTArena * da = pipeline_dep_ctx_arena_at(ctx, di);
  if ((da !=0)) {
    return typeck_dep_return_type_to_caller_arena(da, r, arena);
  }
  return r;
 }) : 0);
      }
      (void)((di = (di + 1)));
    }
    if ((((((type_name_len ==4) && ((type_name)[0] ==69)) && ((type_name)[1] ==120)) && ((type_name)[2] ==112)) && ((type_name)[3] ==114))) {
      int32_t u8_fb = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      if ((u8_fb !=0)) {
        return u8_fb;
      }
      int32_t arr_fb = typeck_expr_inline_array_field_type_ref(arena, field_name, field_name_len);
      if ((arr_fb !=0)) {
        return arr_fb;
      }
      int32_t fb = typeck_expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
      ((fb !=0) ? ({   return fb;
 }) : 0);
    }
    if ((((((type_name_len ==4) && ((type_name)[0] ==84)) && ((type_name)[1] ==121)) && ((type_name)[2] ==112)) && ((type_name)[3] ==101))) {
      int32_t u8_ty = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      ((u8_ty !=0) ? ({   return u8_ty;
 }) : 0);
    }
    if ((((((type_name_len ==4) && ((type_name)[0] ==70)) && ((type_name)[1] ==117)) && ((type_name)[2] ==110)) && ((type_name)[3] ==99))) {
      int32_t u8_fn = typeck_inline_u8_64_array_field_type_ref(arena, field_name, field_name_len);
      if ((u8_fn !=0)) {
        return u8_fn;
      }
      uint8_t nm_params[6] = {112, 97, 114, 97, 109, 115};
      uint8_t nm_pa[5] = {80, 97, 114, 97, 109};
      if (((field_name_len ==6) && typeck_name_equal(field_name, field_name_len, &((nm_params)[0]), 6))) {
        return typeck_ensure_array_type_ref_named_elem(arena, &((nm_pa)[0]), 5, 16);
      }
      int32_t fb_fn = typeck_expr_field_access_fallback_scalar_type_ref(arena, field_name, field_name_len);
      ((fb_fn !=0) ? ({   return fb_fn;
 }) : 0);
    }
    if (((((((type_name_len ==5) && ((type_name)[0] ==80)) && ((type_name)[1] ==97)) && ((type_name)[2] ==114)) && ((type_name)[3] ==97)) && ((type_name)[4] ==109))) {
      uint8_t nm_pname[4] = {110, 97, 109, 101};
      (((field_name_len ==4) && typeck_name_equal(field_name, field_name_len, &((nm_pname)[0]), 4)) ? ({   int32_t u8r_p = typeck_ensure_u8_type_ref(arena);
  ((u8r_p !=0) ? ({   return typeck_find_or_alloc_array_type_ref(arena, u8r_p, 32);
 }) : 0);
 }) : 0);
    }
    if ((((((((((((((type_name_len ==12) && ((type_name)[0] ==83)) && ((type_name)[1] ==116)) && ((type_name)[2] ==114)) && ((type_name)[3] ==117)) && ((type_name)[4] ==99)) && ((type_name)[5] ==116)) && ((type_name)[6] ==76)) && ((type_name)[7] ==97)) && ((type_name)[8] ==121)) && ((type_name)[9] ==111)) && ((type_name)[10] ==117)) && ((type_name)[11] ==116))) {
      int32_t u8r_sl = typeck_ensure_u8_type_ref(arena);
      int32_t i32r_sl = typeck_ensure_i32_type_ref(arena);
      uint8_t nm_sl_name[4] = {110, 97, 109, 101};
      uint8_t nm_sl_field_names[11] = {102, 105, 101, 108, 100, 95, 110, 97, 109, 101, 115};
      uint8_t nm_sl_field_lens[11] = {102, 105, 101, 108, 100, 95, 108, 101, 110, 115};
      uint8_t nm_sl_field_offsets[13] = {102, 105, 101, 108, 100, 95, 111, 102, 102, 115, 101, 116, 115};
      uint8_t nm_sl_field_type_refs[15] = {102, 105, 101, 108, 100, 95, 116, 121, 112, 101, 95, 114, 101, 102, 115};
      uint8_t nm_sl_num_fields[10] = {110, 117, 109, 95, 102, 105, 101, 108, 100, 115};
      uint8_t nm_sl_allow_padding[14] = {97, 108, 108, 111, 119, 95, 112, 97, 100, 100, 105, 110, 103};
      if ((((field_name_len ==4) && typeck_name_equal(field_name, field_name_len, &((nm_sl_name)[0]), 4)) && (u8r_sl !=0))) {
        return typeck_find_or_alloc_array_type_ref(arena, u8r_sl, 64);
      }
      if ((((field_name_len ==11) && typeck_name_equal(field_name, field_name_len, &((nm_sl_field_names)[0]), 11)) && (u8r_sl !=0))) {
        int32_t row_u8 = typeck_find_or_alloc_array_type_ref(arena, u8r_sl, 64);
        ((row_u8 !=0) ? ({   return typeck_find_or_alloc_array_type_ref(arena, row_u8, 64);
 }) : 0);
      }
      if ((((field_name_len ==11) && typeck_name_equal(field_name, field_name_len, &((nm_sl_field_lens)[0]), 11)) && (i32r_sl !=0))) {
        return typeck_find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if ((((field_name_len ==13) && typeck_name_equal(field_name, field_name_len, &((nm_sl_field_offsets)[0]), 13)) && (i32r_sl !=0))) {
        return typeck_find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if ((((field_name_len ==15) && typeck_name_equal(field_name, field_name_len, &((nm_sl_field_type_refs)[0]), 15)) && (i32r_sl !=0))) {
        return typeck_find_or_alloc_array_type_ref(arena, i32r_sl, 64);
      }
      if (((field_name_len ==10) && typeck_name_equal(field_name, field_name_len, &((nm_sl_num_fields)[0]), 10))) {
        return i32r_sl;
      }
      if (((field_name_len ==14) && typeck_name_equal(field_name, field_name_len, &((nm_sl_allow_padding)[0]), 14))) {
        return i32r_sl;
      }
      ((((((((((field_name_len ==8) && ((field_name)[0] ==110)) && ((field_name)[1] ==97)) && ((field_name)[2] ==109)) && ((field_name)[3] ==101)) && ((field_name)[4] ==95)) && ((field_name)[5] ==108)) && ((field_name)[6] ==101)) && ((field_name)[7] ==110)) ? ({   return i32r_sl;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_inline_u8_64_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  int32_t u8r = typeck_ensure_u8_type_ref(arena);
  if ((u8r ==0)) {
    return 0;
  }
  uint8_t nm_name[4] = {110, 97, 109, 101};
  uint8_t nm_var_name[8] = {118, 97, 114, 95, 110, 97, 109, 101};
  uint8_t nm_field_access_field_name[22] = {102, 105, 101, 108, 100, 95, 97, 99, 99, 101, 115, 115, 95, 102, 105, 101, 108, 100, 95, 110, 97, 109, 101};
  uint8_t nm_method_call_name[16] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 110, 97, 109, 101};
  uint8_t nm_struct_lit_struct_name[22] = {115, 116, 114, 117, 99, 116, 95, 108, 105, 116, 95, 115, 116, 114, 117, 99, 116, 95, 110, 97, 109, 101};
  if (((field_name_len ==4) && typeck_name_equal(field_name, field_name_len, &((nm_name)[0]), 4))) {
    return typeck_find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==8) && typeck_name_equal(field_name, field_name_len, &((nm_var_name)[0]), 8))) {
    return typeck_find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==22) && typeck_name_equal(field_name, field_name_len, &((nm_field_access_field_name)[0]), 22))) {
    return typeck_find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==16) && typeck_name_equal(field_name, field_name_len, &((nm_method_call_name)[0]), 16))) {
    return typeck_find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  if (((field_name_len ==22) && typeck_name_equal(field_name, field_name_len, &((nm_struct_lit_struct_name)[0]), 22))) {
    return typeck_find_or_alloc_array_type_ref(arena, u8r, 64);
  }
  return 0;
}
int32_t typeck_expr_inline_array_field_type_ref(struct ast_ASTArena * arena, uint8_t * field_name, int32_t field_name_len) {
  int32_t i32r = typeck_ensure_i32_type_ref(arena);
  if ((i32r ==0)) {
    return 0;
  }
  uint8_t nm_call_arg_refs[13] = {99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115};
  uint8_t nm_method_call_arg_refs[20] = {109, 101, 116, 104, 111, 100, 95, 99, 97, 108, 108, 95, 97, 114, 103, 95, 114, 101, 102, 115};
  uint8_t nm_match_arm_result_refs[21] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 114, 101, 115, 117, 108, 116, 95, 114, 101, 102, 115};
  uint8_t nm_array_lit_elem_refs[19] = {97, 114, 114, 97, 121, 95, 108, 105, 116, 95, 101, 108, 101, 109, 95, 114, 101, 102, 115};
  uint8_t nm_match_arm_is_wildcard[21] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 119, 105, 108, 100, 99, 97, 114, 100};
  uint8_t nm_match_arm_lit_val[17] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 108, 105, 116, 95, 118, 97, 108};
  uint8_t nm_match_arm_is_enum_variant[25] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 105, 115, 95, 101, 110, 117, 109, 95, 118, 97, 114, 105, 97, 110, 116};
  uint8_t nm_match_arm_variant_index[23] = {109, 97, 116, 99, 104, 95, 97, 114, 109, 95, 118, 97, 114, 105, 97, 110, 116, 95, 105, 110, 100, 101, 120};
  if (((field_name_len ==13) && typeck_name_equal(field_name, field_name_len, &((nm_call_arg_refs)[0]), 13))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==20) && typeck_name_equal(field_name, field_name_len, &((nm_method_call_arg_refs)[0]), 20))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==21) && typeck_name_equal(field_name, field_name_len, &((nm_match_arm_result_refs)[0]), 21))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==19) && typeck_name_equal(field_name, field_name_len, &((nm_array_lit_elem_refs)[0]), 19))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==21) && typeck_name_equal(field_name, field_name_len, &((nm_match_arm_is_wildcard)[0]), 21))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==17) && typeck_name_equal(field_name, field_name_len, &((nm_match_arm_lit_val)[0]), 17))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==25) && typeck_name_equal(field_name, field_name_len, &((nm_match_arm_is_enum_variant)[0]), 25))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  if (((field_name_len ==23) && typeck_name_equal(field_name, field_name_len, &((nm_match_arm_variant_index)[0]), 23))) {
    return typeck_find_or_alloc_array_type_ref(arena, i32r, 16);
  }
  return 0;
}
int32_t typeck_entry_module_find_struct_layout_index(struct ast_Module * mod, uint8_t * nm, int32_t nlen) {
  return typeck_find_layout_idx_by_type_name(mod, nm, nlen);
}
void typeck_merge_dep_struct_layouts_into_entry(struct ast_Module * mod, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t nd_merge = 0;
    int32_t di = 0;
    struct ast_Module * dm = 0;
    struct ast_ASTArena * darena = 0;
    int32_t k = 0;
    int32_t nl = 0;
    int32_t nf_dep = 0;
    int32_t ex = 0;
    int32_t need = 0;
    int weak_entry = 0;
    int is_expr_nm = 0;
    int32_t ni = 0;
    int32_t j = 0;
    int32_t raw_fr = 0;
    int32_t mapped = 0;
    int32_t fnlen = 0;
    int32_t foff = 0;
    int32_t ndm_sl = 0;
    uint8_t * dep_nm_buf = typeck_scratch64_slot(9);
    uint8_t * fn_buf = typeck_scratch64_slot(10);
    if ((ctx ==0)) {
      return;
    }
    (void)((nd_merge = pipeline_dep_ctx_ndep(ctx)));
    (void)((di = 0));
    while ((di < nd_merge)) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, di)));
      (void)((darena = pipeline_dep_ctx_arena_at(ctx, di)));
      if (((dm ==0) || (darena ==0))) {
        (void)((di = (di + 1)));
        continue;
      }
      /* Sync dep offsets against the dep arena BEFORE copy. PLATFORM: SHARED. */
      glue_sync_struct_layout_field_offsets_c(dm, darena);
      (void)((ndm_sl = pipeline_module_num_struct_layouts_at(dm)));
      (void)((k = 0));
      while ((k < ndm_sl)) {
        (void)((nl = pipeline_module_struct_layout_name_len(dm, k)));
        if (((nl > 0) && (nl <=127))) {
          (void)((nf_dep = pipeline_module_struct_layout_num_fields(dm, k)));
          if ((nf_dep > 64)) {
            (void)((nf_dep = 64));
          }
          (void)(pipeline_module_struct_layout_name_into(dm, k, dep_nm_buf));
          (void)((ex = typeck_entry_module_find_struct_layout_index(mod, dep_nm_buf, nl)));
          (void)((need = 0));
          if ((ex < 0)) {
            (void)((need = 1));
          } else {
            (void)((weak_entry = 0));
            if (((pipeline_module_struct_layout_num_fields(mod, ex) >=2) && (pipeline_module_struct_layout_field_type_ref(mod, ex, 1) ==0))) {
              (void)((weak_entry = 1));
            }
            (void)((is_expr_nm = 0));
            if ((nl ==4)) {
              (((((pipeline_module_struct_layout_name_byte_at(dm, k, 0) ==69) && (pipeline_module_struct_layout_name_byte_at(dm, k, 1) ==120)) && (pipeline_module_struct_layout_name_byte_at(dm, k, 2) ==112)) && (pipeline_module_struct_layout_name_byte_at(dm, k, 3) ==114)) ? ({   (void)((is_expr_nm = 1));
 }) : 0);
            }
            if ((((nf_dep > pipeline_module_struct_layout_num_fields(mod, ex)) || weak_entry) || is_expr_nm)) {
              (void)((need = 1));
            }
            if ((((nf_dep > 0) && (nf_dep >=pipeline_module_struct_layout_num_fields(mod, ex))) && (pipeline_module_struct_layout_num_fields(mod, ex) > 0))) {
              (void)((need = 1));
            }
            (((pipeline_module_struct_layout_soa_at(dm, k) !=0) && (pipeline_module_struct_layout_soa_at(mod, ex) ==0)) ? ({   (void)((need = 1));
 }) : 0);
          }
          ((need !=0) ? ({   (void)((ni = ex));
  if ((ex < 0)) {
    (void)((ni = pipeline_module_struct_layout_alloc(mod)));
    ((ni < 0) ? ({   (void)((k = (k + 1)));
  continue;
 }) : 0);
  }
  (void)(pipeline_module_struct_layout_reset_slot(mod, ni));
  (void)(pipeline_module_struct_layout_set_name(mod, ni, dep_nm_buf, nl));
  (void)((j = 0));
  while ((j < nf_dep)) {
    (void)((raw_fr = pipeline_module_struct_layout_field_type_ref(dm, k, j)));
    (void)((mapped = 0));
    if ((raw_fr !=0)) {
      (void)((mapped = typeck_dep_return_type_to_caller_arena(darena, raw_fr, arena)));
    }
    (void)((fnlen = pipeline_module_struct_layout_field_name_len(dm, k, j)));
    (void)(pipeline_module_struct_layout_field_name_into(dm, k, j, fn_buf));
    (void)((foff = pipeline_module_struct_layout_field_offset_at(dm, k, j)));
    (void)(pipeline_module_struct_layout_set_field(mod, ni, j, fn_buf, fnlen, mapped, foff));
    (void)(pipeline_module_struct_layout_set_field_align(mod, ni, j, pipeline_module_struct_layout_field_align_at(dm, k, j)));
    (void)((j = (j + 1)));
  }
  (void)(pipeline_module_struct_layout_set_num_fields(mod, ni, nf_dep));
  (void)(pipeline_module_struct_layout_set_allow_padding(mod, ni, pipeline_module_struct_layout_allow_padding_at(dm, k)));
  (void)(pipeline_module_struct_layout_set_soa(mod, ni, pipeline_module_struct_layout_soa_at(dm, k)));
  (void)(pipeline_module_struct_layout_set_packed(mod, ni, pipeline_module_struct_layout_packed_at(dm, k)));
 }) : 0);
        }
        (void)((k = (k + 1)));
      }
      (void)((di = (di + 1)));
    }
  }
}
void typeck_wpo_unify_soa_layouts(struct ast_Module * entry, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t nd = 0;
    int32_t mi = 0;
    struct ast_Module * dm = 0;
    int32_t nsl = 0;
    int32_t k = 0;
    int32_t nl = 0;
    int32_t any_soa = 0;
    int32_t mj = 0;
    struct ast_Module * dm2 = 0;
    int32_t nsl2 = 0;
    int32_t k2 = 0;
    int32_t nl2 = 0;
    int32_t li = 0;
    uint8_t * nm_buf = typeck_scratch64_slot(11);
    uint8_t * nm2 = typeck_scratch64_slot(12);
    if (((entry ==0) || (ctx ==0))) {
      return;
    }
    (void)((nd = pipeline_dep_ctx_ndep(ctx)));
    (void)((mi = -1));
    while ((mi < nd)) {
      (void)((dm = entry));
      if ((mi >=0)) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, mi)));
      }
      if ((dm ==0)) {
        (void)((mi = (mi + 1)));
        continue;
      }
      (void)((nsl = pipeline_module_num_struct_layouts_at(dm)));
      (void)((k = 0));
      while ((k < nsl)) {
        (void)((nl = pipeline_module_struct_layout_name_len(dm, k)));
        if (((nl > 0) && (nl <=127))) {
          (void)(pipeline_module_struct_layout_name_into(dm, k, nm_buf));
          (void)((any_soa = pipeline_module_struct_layout_soa_at(dm, k)));
          (void)((mj = -1));
          while (((mj < nd) && (any_soa ==0))) {
            (void)((dm2 = entry));
            if ((mj >=0)) {
              (void)((dm2 = pipeline_dep_ctx_module_at(ctx, mj)));
            }
            if ((dm2 !=0)) {
              (void)((nsl2 = pipeline_module_num_struct_layouts_at(dm2)));
              (void)((k2 = 0));
              while (((k2 < nsl2) && (any_soa ==0))) {
                (void)((nl2 = pipeline_module_struct_layout_name_len(dm2, k2)));
                if ((nl2 ==nl)) {
                  (void)(pipeline_module_struct_layout_name_into(dm2, k2, nm2));
                  ((typeck_name_equal(nm_buf, nl, nm2, nl2) && (pipeline_module_struct_layout_soa_at(dm2, k2) !=0)) ? ({   (void)((any_soa = 1));
 }) : 0);
                }
                (void)((k2 = (k2 + 1)));
              }
            }
            (void)((mj = (mj + 1)));
          }
          ((any_soa !=0) ? ({   (void)((mj = -1));
  while ((mj < nd)) {
    (void)((dm2 = entry));
    if ((mj >=0)) {
      (void)((dm2 = pipeline_dep_ctx_module_at(ctx, mj)));
    }
    if ((dm2 !=0)) {
      (void)((li = typeck_find_layout_idx_by_type_name(dm2, nm_buf, nl)));
      (((li >=0) && (pipeline_module_struct_layout_soa_at(dm2, li) ==0)) ? ({   (void)(pipeline_module_struct_layout_set_soa(dm2, li, 1));
 }) : 0);
    }
    (void)((mj = (mj + 1)));
  }
 }) : 0);
        }
        (void)((k = (k + 1)));
      }
      (void)((mi = (mi + 1)));
    }
  }
}
int32_t typeck_resolve_scan_dep_with_apply(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax, int32_t want_apply) {
  {
    struct ast_Module * dm = 0;
    int32_t ret = 0;
    int32_t * fn_slot = typeck_call_resolve_func_idx_slot();
    if ((dep_i >=imax)) {
      return 0;
    }
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_i)));
    if ((dm !=0)) {
      (void)(typeck_i32_ptr_store(fn_slot, 0));
      (void)((ret = typeck_find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx, fn_slot)));
      if ((ret !=0)) {
        if ((want_apply !=0)) {
          (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek()));
        }
        return ret;
      }
      ((dep_i < typeck_module_num_imports(module)) ? ({   (void)((ret = typeck_resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord, dep_i, ctx, fn_slot)));
  ((ret !=0) ? ({   if ((want_apply !=0)) {
    (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, dep_i, typeck_call_resolve_func_idx_peek()));
  }
  return ret;
 }) : 0);
 }) : 0);
    }
    return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord, call_expr_ref, ctx, (dep_i + 1), imax, want_apply);
  }
}
int32_t typeck_find_func_return_type_in_module(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    int32_t j = 0;
    while ((j < ((mod)->num_funcs))) {
      if (typeck_expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
        if ((func_index_out !=0)) {
          (void)(((func_index_out)[0] = j));
        }
        int32_t ret_dep = pipeline_module_func_return_type_at(mod, j);
        if ((from_dep_index < 0)) {
          return ret_dep;
        }
        return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, ret_dep, caller_arena, ctx);
      }
      (void)((j = (j + 1)));
    }
    return 0;
  }
}
extern int32_t pipeline_visibility_allow_func(struct ast_Module * mod, int32_t fi, int32_t cross_module);
int32_t typeck_find_func_return_type_in_module_by_name(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    if (((name_len <=0) || (name_len > 127))) {
      return 0;
    }
    int32_t j = 0;
    while ((j < ((mod)->num_funcs))) {
      if ((pipeline_module_func_name_equal_at(mod, j, name, name_len) !=0)) {
        if (((from_dep_index >=0) && (pipeline_visibility_allow_func(mod, j, 1) ==0))) {
          (void)((j = (j + 1)));
          continue;
        }
        if ((func_index_out !=0)) {
          (void)(((func_index_out)[0] = j));
        }
        int32_t rtr = pipeline_module_func_return_type_at(mod, j);
        if ((from_dep_index < 0)) {
          return rtr;
        }
        int32_t mapped = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, rtr, caller_arena, ctx);
        if ((mapped !=0)) {
          return mapped;
        }
        struct ast_ASTArena * da = pipeline_dep_ctx_arena_at(ctx, from_dep_index);
        if (((da !=0) && (rtr !=0))) {
          return typeck_dep_return_type_to_caller_arena(da, rtr, caller_arena);
        }
        return 0;
      }
      (void)((j = (j + 1)));
    }
    return 0;
  }
}
int32_t typeck_overload_arg_param_score(struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t arg_i, int32_t param_ty_raw, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t arg_ref = 0;
    int32_t arg_ty = 0;
    int32_t param_ty = 0;
    int32_t ord_as = 54;
    int32_t ord_method_call = 49;
    int32_t as_tgt = 0;
    int32_t call_kind = 0;
    if ((((caller_arena ==0) || (call_expr_ref <=0)) || (arg_i < 0))) {
      return -1;
    }
    (void)((call_kind = pipeline_expr_kind_ord_at(caller_arena, call_expr_ref)));
    if ((call_kind ==ord_method_call)) {
      (void)((arg_ref = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, arg_i)));
    } else {
      (void)((arg_ref = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, arg_i)));
    }
    if ((arg_ref <=0)) {
      return -1;
    }
    (void)((param_ty = param_ty_raw));
    if ((from_dep_index >=0)) {
      (void)((param_ty = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, param_ty_raw, caller_arena, ctx)));
      ((param_ty ==0) ? ({   return -1;
 }) : 0);
    }
    if ((param_ty <=0)) {
      return -1;
    }
    (void)((arg_ty = pipeline_expr_resolved_type_ref(caller_arena, arg_ref)));
    if (((arg_ty > 0) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, arg_ty, param_ty) !=0))) {
      return 1000;
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, arg_ref) ==ord_as)) {
      (void)((as_tgt = pipeline_expr_as_target_type_ref_at(caller_arena, arg_ref)));
      (((as_tgt > 0) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, as_tgt, param_ty) !=0)) ? ({   return 1000;
 }) : 0);
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, arg_ref) ==59)) {
      int32_t pk_sl = pipeline_type_kind_ord_at(caller_arena, param_ty);
      int32_t pe_sl = 0;
      int32_t u8_ord = 2;
      (((pk_sl ==9) || (pk_sl ==11)) ? ({   (void)((pe_sl = pipeline_type_elem_ref_at(caller_arena, param_ty)));
  (((pe_sl > 0) && (pipeline_type_kind_ord_at(caller_arena, pe_sl) ==u8_ord)) ? ({   return 1000;
 }) : 0);
 }) : 0);
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, arg_ref) ==0)) {
      int32_t pk_lit = pipeline_type_kind_ord_at(caller_arena, param_ty);
      if ((typeck_expr_is_null_keyword(caller_arena, arg_ref) !=0)) {
        if ((pk_lit ==9)) {
          return 100;
        }
        return -1;
      }
      if ((((((((pk_lit ==0) || (pk_lit ==2)) || (pk_lit ==3)) || (pk_lit ==4)) || (pk_lit ==5)) || (pk_lit ==6)) || (pk_lit ==7))) {
        return 100;
      }
      (((pk_lit ==9) && (pipeline_expr_int_val_at(caller_arena, arg_ref) ==0)) ? ({   return 100;
 }) : 0);
    }
    int32_t arg_ko_fl = pipeline_expr_kind_ord_at(caller_arena, arg_ref);
    int32_t fl_inner = arg_ref;
    if ((arg_ko_fl ==22)) {
      (void)((fl_inner = pipeline_expr_unary_operand_ref_at(caller_arena, arg_ref)));
      ((fl_inner > 0) ? ({   (void)((arg_ko_fl = pipeline_expr_kind_ord_at(caller_arena, fl_inner)));
 }) : 0);
    }
    if ((arg_ko_fl ==1)) {
      int32_t pk_fl = pipeline_type_kind_ord_at(caller_arena, param_ty);
      if (((pk_fl ==14) || (pk_fl ==15))) {
        return 100;
      }
      return -1;
    }
    if ((arg_ty > 0)) {
      int32_t ak = pipeline_type_kind_ord_at(caller_arena, arg_ty);
      int32_t pk = pipeline_type_kind_ord_at(caller_arena, param_ty);
      if (typeck_integer_widen_ok_refs(caller_arena, param_ty, arg_ty)) {
        return 100;
      }
      if (typeck_float_widen_ok(pk, ak)) {
        return 100;
      }
      /* 10.3.3: TYPE_FN ↔ Cap *u8 opaque ABI cross-kind (≡ typeck.x score). */
      if ((((ak != pk) && (typeck_is_fnptr_surface(caller_arena, param_ty) !=0)) && (typeck_is_fnptr_surface(caller_arena, arg_ty) !=0))) {
        return 100;
      }
      if (((ak ==10) && (pk ==9))) {
        int32_t ae = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        int32_t pe = pipeline_type_elem_ref_at(caller_arena, param_ty);
        ((((ae > 0) && (pe > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, ae, pe) !=0)) ? ({   return 1000;
 }) : 0);
      }
      if (((ak ==9) && (pk ==9))) {
        int32_t ae2 = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        int32_t pe2 = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if ((((ae2 > 0) && (pe2 > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, ae2, pe2) !=0))) {
          return 1000;
        }
        return -1;
      }
      if (((ak ==10) && (pk ==10))) {
        int32_t ae_a = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        int32_t pe_a = pipeline_type_elem_ref_at(caller_arena, param_ty);
        int32_t asz = pipeline_type_array_size_at(caller_arena, arg_ty);
        int32_t psz = pipeline_type_array_size_at(caller_arena, param_ty);
        if (((((ae_a > 0) && (pe_a > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, ae_a, pe_a) !=0)) && (((asz <=0) || (psz <=0)) || (asz ==psz)))) {
          return 1000;
        }
        return -1;
      }
      if (((ak ==11) && (pk ==11))) {
        int32_t ae_s = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        int32_t pe_s = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if ((((ae_s > 0) && (pe_s > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, ae_s, pe_s) !=0))) {
          return 1000;
        }
        return -1;
      }
      if (((ak ==10) && (pk ==11))) {
        int32_t ae_as = pipeline_type_elem_ref_at(caller_arena, arg_ty);
        int32_t pe_as = pipeline_type_elem_ref_at(caller_arena, param_ty);
        if ((((ae_as > 0) && (pe_as > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, ae_as, pe_as) !=0))) {
          return 100;
        }
        return -1;
      }
      if (((ak ==pk) && (ak !=0))) {
        return 1;
      }
      return -1;
    }
    return -1;
  }
}
int32_t typeck_find_func_return_type_in_module_by_name_overload(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    int32_t j = 0;
    int32_t num_args = 0;
    int32_t best_idx = -1;
    int32_t best_score = -1;
    int32_t best_expect_match = -1;
    int32_t best_ret = 0;
    int32_t first_idx = -1;
    int32_t first_ret = 0;
    int32_t expect_ty = 0;
    if ((((name_len <=0) || (name_len > 127)) || (mod ==0))) {
      return 0;
    }
    if ((((call_expr_ref <=0) || (caller_arena ==0)) || (call_expr_ref > ((caller_arena)->num_exprs)))) {
      return typeck_find_func_return_type_in_module_by_name(mod, caller_arena, name, name_len, from_dep_index, ctx, func_index_out);
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) ==49)) {
      (void)((num_args = pipeline_expr_method_call_num_args_at(caller_arena, call_expr_ref)));
    } else {
      (void)((num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref)));
    }
    (void)((expect_ty = typeck_overload_expected_ret_peek()));
    while ((j < ((mod)->num_funcs))) {
      if ((pipeline_module_func_name_equal_at(mod, j, name, name_len) !=0)) {
        int32_t rtr = pipeline_module_func_return_type_at(mod, j);
        if ((first_idx < 0)) {
          (void)((first_idx = j));
          (void)((first_ret = rtr));
        }
        int32_t nparams = pipeline_module_func_num_params_at(mod, j);
        /* Cap 10.7.1 slice8 */ ((typeck_call_arity_compatible(mod, j, num_args) !=0) ? ({   int32_t ai = 0;
  int32_t score = 0;
  int32_t matched = 1;
  int32_t expect_match = 0;
  while ((ai < nparams)) {
    int32_t param_raw = pipeline_module_func_param_type_ref_at(mod, j, ai);
    int32_t pty = param_raw;
    int32_t aref = 0;
    if ((from_dep_index >=0)) {
      (void)((pty = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, param_raw, caller_arena, ctx)));
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) ==49)) {
      (void)((aref = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, ai)));
    } else {
      (void)((aref = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, ai)));
    }
    if (((aref > 0) && (pty > 0))) {
      (void)(typeck_coerce_init_array_vector_lit_to_decl(mod, caller_arena, aref, pty, pipeline_type_kind_ord_at(caller_arena, pty), pipeline_expr_kind_ord_at(caller_arena, aref)));
    }
    int32_t sc = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw, from_dep_index, ctx);
    if ((sc < 0)) {
      (void)((matched = 0));
      break;
    }
    (void)((score = (score + sc)));
    (void)((ai = (ai + 1)));
  }
  if ((((matched !=0) && (expect_ty > 0)) && (rtr > 0))) {
    int32_t mapped_ret = rtr;
    if ((from_dep_index >=0)) {
      (void)((mapped_ret = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, rtr, caller_arena, ctx)));
    }
    ((mapped_ret > 0) ? ({   ((pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, mapped_ret, expect_ty) !=0) ? ({   (void)((expect_match = 1));
 }) : ({   uint8_t na[128] = {};
  uint8_t nb[128] = {};
  int32_t la = pipeline_type_named_name_into(caller_arena, mapped_ret, &((na)[0]));
  int32_t lb = pipeline_type_named_name_into(caller_arena, expect_ty, &((nb)[0]));
  (((la > 0) && (lb > 0)) ? ({   int32_t sa = 0;
  int32_t sb = 0;
  int32_t ii = 0;
  while ((ii < la)) {
    if (((na)[ii] ==46)) {
      (void)((sa = (ii + 1)));
    }
    (void)((ii = (ii + 1)));
  }
  (void)((ii = 0));
  while ((ii < lb)) {
    if (((nb)[ii] ==46)) {
      (void)((sb = (ii + 1)));
    }
    (void)((ii = (ii + 1)));
  }
  ((((la - sa) ==(lb - sb)) && ((la - sa) > 0)) ? ({   int32_t eq = 1;
  (void)((ii = 0));
  while ((ii < (la - sa))) {
    if (((na)[(sa + ii)] !=(nb)[(sb + ii)])) {
      (void)((eq = 0));
      break;
    }
    (void)((ii = (ii + 1)));
  }
  ((eq !=0) ? ({   (void)((expect_match = 1));
 }) : 0);
 }) : 0);
 }) : 0);
 }));
 }) : 0);
  }
  (((matched !=0) && ((score > best_score) || ((score ==best_score) && (expect_match > best_expect_match)))) ? ({   (void)((best_score = score));
  (void)((best_expect_match = expect_match));
  (void)((best_idx = j));
  (void)((best_ret = rtr));
 }) : 0);
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    if ((best_idx >=0)) {
      if ((func_index_out !=0)) {
        (void)(((func_index_out)[0] = best_idx));
      }
      if ((from_dep_index < 0)) {
        return best_ret;
      }
      return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, best_ret, caller_arena, ctx);
    }
    if ((first_idx >=0)) {
      int32_t any_arity = 0;
      int32_t j2 = 0;
      while ((j2 < ((mod)->num_funcs))) {
        if ((pipeline_module_func_name_equal_at(mod, j2, name, name_len) !=0)) {
          /* Cap 10.7.1 slice8 */ ((typeck_call_arity_compatible(mod, j2, num_args) !=0) ? ({   (void)((any_arity = 1));
  break;
 }) : 0);
        }
        (void)((j2 = (j2 + 1)));
      }
      if ((any_arity ==0)) {
        return 0;
      }
      if ((func_index_out !=0)) {
        (void)(((func_index_out)[0] = first_idx));
      }
      if ((from_dep_index < 0)) {
        return first_ret;
      }
      return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, first_ret, caller_arena, ctx);
    }
    return 0;
  }
}
int32_t typeck_find_func_return_type_in_module_overload(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t call_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    int32_t j = 0;
    int32_t first_idx = -1;
    int32_t first_ret = 0;
    int32_t num_args = 0;
    int32_t has_call_info = 0;
    int32_t best_idx = -1;
    int32_t best_score = -1;
    int32_t best_ret = 0;
    int32_t expect_ty = 0;
    if (((call_expr_ref > 0) && (call_expr_ref <=((caller_arena)->num_exprs)))) {
      if ((pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) ==49)) {
        (void)((num_args = pipeline_expr_method_call_num_args_at(caller_arena, call_expr_ref)));
      } else {
        (void)((num_args = pipeline_expr_call_num_args_at(caller_arena, call_expr_ref)));
      }
      (void)((has_call_info = 1));
    }
    (void)((expect_ty = typeck_overload_expected_ret_peek()));
    int32_t best_expect_match2 = -1;
    while ((j < ((mod)->num_funcs))) {
      if (typeck_expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j)) {
        if ((first_idx < 0)) {
          (void)((first_idx = j));
          (void)((first_ret = pipeline_module_func_return_type_at(mod, j)));
        }
        ((has_call_info !=0) ? ({   int32_t nparams = pipeline_module_func_num_params_at(mod, j);
  /* Cap 10.7.1 slice8 */ ((typeck_call_arity_compatible(mod, j, num_args) !=0) ? ({   int32_t ai = 0;
  int32_t score = 0;
  int32_t matched = 1;
  int32_t expect_match2 = 0;
  int32_t rtr_cand = pipeline_module_func_return_type_at(mod, j);
  while ((ai < nparams)) {
    int32_t param_raw = pipeline_module_func_param_type_ref_at(mod, j, ai);
    int32_t pty2 = param_raw;
    int32_t aref2 = 0;
    if ((from_dep_index >=0)) {
      (void)((pty2 = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, param_raw, caller_arena, ctx)));
    }
    if ((pipeline_expr_kind_ord_at(caller_arena, call_expr_ref) ==49)) {
      (void)((aref2 = pipeline_expr_method_call_arg_ref(caller_arena, call_expr_ref, ai)));
    } else {
      (void)((aref2 = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, ai)));
    }
    if (((aref2 > 0) && (pty2 > 0))) {
      (void)(typeck_coerce_init_array_vector_lit_to_decl(mod, caller_arena, aref2, pty2, pipeline_type_kind_ord_at(caller_arena, pty2), pipeline_expr_kind_ord_at(caller_arena, aref2)));
    }
    int32_t sc = typeck_overload_arg_param_score(caller_arena, call_expr_ref, ai, param_raw, from_dep_index, ctx);
    if ((sc < 0)) {
      (void)((matched = 0));
      break;
    }
    (void)((score = (score + sc)));
    (void)((ai = (ai + 1)));
  }
  if ((((matched !=0) && (expect_ty > 0)) && (rtr_cand > 0))) {
    int32_t mapped_ret2 = rtr_cand;
    if ((from_dep_index >=0)) {
      (void)((mapped_ret2 = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, rtr_cand, caller_arena, ctx)));
    }
    (((mapped_ret2 > 0) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, mapped_ret2, expect_ty) !=0)) ? ({   (void)((expect_match2 = 1));
 }) : 0);
  }
  (((matched !=0) && ((score > best_score) || ((score ==best_score) && (expect_match2 > best_expect_match2)))) ? ({   (void)((best_score = score));
  (void)((best_expect_match2 = expect_match2));
  (void)((best_idx = j));
  (void)((best_ret = rtr_cand));
 }) : 0);
 }) : 0);
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    if ((best_idx >=0)) {
      if ((func_index_out !=0)) {
        (void)(((func_index_out)[0] = best_idx));
      }
      if ((from_dep_index < 0)) {
        return best_ret;
      }
      return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, best_ret, caller_arena, ctx);
    }
    if ((first_idx >=0)) {
      if ((has_call_info !=0)) {
        int32_t any_arity2 = 0;
        int32_t j3 = 0;
        while ((j3 < ((mod)->num_funcs))) {
          if (typeck_expr_var_name_equal_func(callee_arena, callee_expr_ref, mod, j3)) {
            /* Cap 10.7.1 slice8 */ ((typeck_call_arity_compatible(mod, j3, num_args) !=0) ? ({   (void)((any_arity2 = 1));
  break;
 }) : 0);
          }
          (void)((j3 = (j3 + 1)));
        }
        ((any_arity2 ==0) ? ({   return 0;
 }) : 0);
      }
      if ((func_index_out !=0)) {
        (void)(((func_index_out)[0] = first_idx));
      }
      if ((from_dep_index < 0)) {
        return first_ret;
      }
      return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, first_ret, caller_arena, ctx);
    }
    return 0;
  }
}
int32_t typeck_import_path_segment_count(uint8_t * path, int32_t path_len) {
  if (((path_len <=0) || (path ==0))) {
    return 0;
  }
  int32_t n = 1;
  int32_t ii = 0;
  while ((ii < path_len)) {
    uint8_t ch_u8 = (path)[ii];
    if ((ch_u8 ==46)) {
      (void)((n = (n + 1)));
    }
    (void)((ii = (ii + 1)));
  }
  return n;
}
int typeck_import_segment_at(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen) {
  {
    if ((((module ==0) || (imp_ix < 0)) || (imp_ix >=typeck_module_num_imports(module)))) {
      return 0;
    }
    int32_t pl = pipeline_module_import_path_len(module, imp_ix);
    if (((pl <=0) || (pl > 127))) {
      return 0;
    }
    int32_t ci = 0;
    int32_t ss = 0;
    int32_t k = 0;
    while ((k <=pl)) {
      int at_end_p = (k ==pl);
      int dot_p = 0;
      if ((!(at_end_p) && (k < pl))) {
        (void)((dot_p = (pipeline_module_import_path_byte_at(module, imp_ix, k) ==46)));
      }
      if ((at_end_p || dot_p)) {
        int32_t seg_len_here = (k - ss);
        if ((seg_len_here <=0)) {
          return 0;
        }
        if ((ci ==want_seg)) {
          (void)(((ostr)[0] = ss));
          (void)(((olen)[0] = seg_len_here));
          return 1;
        }
        if (dot_p) {
          (void)((ss = (k + 1)));
        }
        (void)((ci = (ci + 1)));
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
}
int32_t typeck_resolve_whole_import_qualified_call_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  {
    int32_t ord_field = 44;
    int32_t ord_var = 3;
    if ((ctx ==0)) {
      return 0;
    }
    if ((((callee_expr_ref <=0) || (callee_expr_ref > ((arena)->num_exprs))) || (module ==0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=ord_field)) {
      return 0;
    }
    uint8_t layer_buf[128] = {};
    (void)(asm_qual_sym_layer_reset());
    int32_t nstack = 0;
    int32_t cur_ref = callee_expr_ref;
    while (1) {
      if (((cur_ref <=0) || (cur_ref > ((arena)->num_exprs)))) {
        return 0;
      }
      int32_t falen = pipeline_expr_field_access_name_len(arena, cur_ref);
      if ((((pipeline_expr_kind_ord_at(arena, cur_ref) !=ord_field) || (falen <=0)) || (falen > 127))) {
        break;
      }
      (void)(pipeline_expr_field_access_name_into(arena, cur_ref, &((layer_buf)[0])));
      if ((asm_qual_sym_layer_push(&((layer_buf)[0]), falen) < 0)) {
        return 0;
      }
      (void)((nstack = (nstack + 1)));
      (void)((cur_ref = pipeline_expr_field_access_base_ref(arena, cur_ref)));
    }
    (void)((nstack = asm_qual_sym_layer_count()));
    if (((cur_ref <=0) || (cur_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    int32_t vnlen = pipeline_expr_var_name_len(arena, cur_ref);
    if ((((pipeline_expr_kind_ord_at(arena, cur_ref) !=ord_var) || (vnlen <=0)) || (vnlen > 127))) {
      return 0;
    }
    uint8_t vname_buf[128] = {};
    (void)(pipeline_expr_var_name_into(arena, cur_ref, &((vname_buf)[0])));
    int32_t dep_j = 0;
    int32_t n_imp = typeck_module_num_imports(module);
    while ((dep_j < n_imp)) {
      int32_t plen = pipeline_module_import_path_len(module, dep_j);
      if (((plen <=0) || (plen > 127))) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      uint8_t path_cnt_buf[128] = {};
      int32_t pci = 0;
      while (((pci < plen) && (pci < 127))) {
        (void)(((path_cnt_buf)[pci] = pipeline_module_import_path_byte_at(module, dep_j, pci)));
        (void)((pci = (pci + 1)));
      }
      int32_t Pseg = typeck_import_path_segment_count(&((path_cnt_buf)[0]), plen);
      if (((Pseg <=0) || (nstack !=Pseg))) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      int32_t s0_rel = 0;
      int32_t s0_ln = 0;
      if (!(typeck_import_segment_at(module, dep_j, 0, &(s0_rel), &(s0_ln)))) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      if (!(typeck_import_path_slice_equal(module, dep_j, s0_rel, s0_ln, &((vname_buf)[0]), vnlen))) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      int bad_mid = 0;
      int32_t sm = 1;
      while ((sm <=(Pseg - 1))) {
        int32_t srv = 0;
        int32_t slv = 0;
        if (!(typeck_import_segment_at(module, dep_j, sm, &(srv), &(slv)))) {
          (void)((bad_mid = 1));
        } else {
          int32_t lay_ix = (Pseg - sm);
          (void)(asm_qual_sym_layer_copy(lay_ix, &((layer_buf)[0]), 64));
          (!(typeck_import_path_slice_equal(module, dep_j, srv, slv, &((layer_buf)[0]), asm_qual_sym_layer_len(lay_ix))) ? ({   (void)((bad_mid = 1));
 }) : 0);
        }
        if (bad_mid) {
          break;
        }
        (void)((sm = (sm + 1)));
      }
      if (bad_mid) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, dep_j);
      struct ast_Module * dm = 0;
      if ((dep_slot < 0)) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
      if ((dm ==0)) {
        (void)((dep_j = (dep_j + 1)));
        continue;
      }
      (void)(asm_qual_sym_layer_copy(0, &((layer_buf)[0]), 64));
      int32_t ret_fn = typeck_find_func_return_type_in_module_by_name(dm, arena, &((layer_buf)[0]), asm_qual_sym_layer_len(0), dep_slot, ctx, func_index_out);
      if ((ret_fn !=0)) {
        ((dep_index_out !=0) ? ({   (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
 }) : 0);
      }
      return ret_fn;
    }
    return 0;
  }
}
int32_t typeck_resolve_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  {
    int32_t ord_field = 44;
    int32_t ord_var = 3;
    int32_t ord_import_binding = 1;
    int32_t base_bind_ref = 0;
    int32_t base_bind_len = 0;
    int32_t field_len = 0;
    int32_t ii = 0;
    int32_t ret_b = 0;
    struct ast_Module * dm = 0;
    int32_t import_kind = 0;
    uint8_t base_bind_nm[128] = {};
    uint8_t field_nm[128] = {};
    if (((((callee_expr_ref <=0) || (callee_expr_ref > ((arena)->num_exprs))) || (module ==0)) || (ctx ==0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, callee_expr_ref) !=ord_field)) {
      return 0;
    }
    (void)((base_bind_ref = pipeline_expr_field_access_base_ref(arena, callee_expr_ref)));
    if (((base_bind_ref <=0) || (base_bind_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_bind_ref) !=ord_var)) {
      return 0;
    }
    (void)((base_bind_len = pipeline_expr_var_name_len(arena, base_bind_ref)));
    if (((base_bind_len <=0) || (base_bind_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, base_bind_ref, &((base_bind_nm)[0])));
    (void)((field_len = pipeline_expr_field_access_name_len(arena, callee_expr_ref)));
    (void)(pipeline_expr_field_access_name_into(arena, callee_expr_ref, &((field_nm)[0])));
    (void)((ii = 0));
    int32_t n_imp = typeck_module_num_imports(module);
    while ((ii < n_imp)) {
      (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
      if (((import_kind ==ord_import_binding) && typeck_import_binding_name_equal(module, ii, &((base_bind_nm)[0]), base_bind_len))) {
        int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii);
        if ((dep_slot < 0)) {
          break;
        }
        (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
        if ((dm !=0)) {
          (void)((ret_b = typeck_find_func_return_type_in_module_by_name_overload(dm, arena, &((field_nm)[0]), field_len, call_expr_ref, dep_slot, ctx, func_index_out)));
          ((ret_b !=0) ? ({   if ((dep_index_out !=0)) {
    (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
  }
  return ret_b;
 }) : 0);
        }
        break;
      }
      (void)((ii = (ii + 1)));
    }
    return 0;
  }
}
int32_t typeck_resolve_method_call_binding_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  {
    int32_t ord_var = 3;
    int32_t ord_import_binding = 1;
    int32_t base_ref = 0;
    int32_t base_len = 0;
    int32_t method_len = 0;
    int32_t ii = 0;
    int32_t ret_b = 0;
    struct ast_Module * dm = 0;
    int32_t import_kind = 0;
    uint8_t base_nm[128] = {};
    uint8_t method_nm[128] = {};
    if (((((expr_ref <=0) || (expr_ref > ((arena)->num_exprs))) || (module ==0)) || (ctx ==0))) {
      return 0;
    }
    (void)((base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref)));
    if (((base_ref <=0) || (base_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, base_ref) !=ord_var)) {
      return 0;
    }
    (void)((base_len = pipeline_expr_var_name_len(arena, base_ref)));
    (void)((method_len = pipeline_expr_method_call_name_len(arena, expr_ref)));
    if (((((base_len <=0) || (base_len > 127)) || (method_len <=0)) || (method_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, base_ref, &((base_nm)[0])));
    (void)(pipeline_expr_method_call_name_into(arena, expr_ref, &((method_nm)[0])));
    int32_t n_imp = typeck_module_num_imports(module);
    while ((ii < n_imp)) {
      (void)((import_kind = pipeline_module_import_kind_at(module, ii)));
      if (((import_kind ==ord_import_binding) && typeck_import_binding_name_equal(module, ii, &((base_nm)[0]), base_len))) {
        int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii);
        if ((dep_slot < 0)) {
          break;
        }
        (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
        if ((dm !=0)) {
          (void)((ret_b = typeck_find_func_return_type_in_module_by_name(dm, arena, &((method_nm)[0]), method_len, dep_slot, ctx, func_index_out)));
          ((ret_b !=0) ? ({   if ((dep_index_out !=0)) {
    (void)(typeck_i32_ptr_store(dep_index_out, dep_slot));
  }
  return ret_b;
 }) : 0);
        }
        break;
      }
      (void)((ii = (ii + 1)));
    }
    return 0;
  }
}
int32_t typeck_resolve_call_select_import_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    int32_t ord_var = 3;
    int32_t ord_import_select = 2;
    int32_t cv_len = 0;
    int32_t k = 0;
    int32_t sel_cnt = 0;
    int32_t import_kind = 0;
    struct ast_Module * dm = 0;
    uint8_t cv_nm[128] = {};
    if (((module ==0) || (ctx ==0))) {
      return 0;
    }
    if ((((dep_ix < 0) || (dep_ix >=typeck_module_num_imports(module))) || (callee_ord !=ord_var))) {
      return 0;
    }
    (void)((import_kind = pipeline_module_import_kind_at(module, dep_ix)));
    if ((import_kind !=ord_import_select)) {
      return 0;
    }
    (void)((cv_len = pipeline_expr_var_name_len(arena, callee_expr_ref)));
    if ((cv_len <=0)) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, callee_expr_ref, &((cv_nm)[0])));
    int32_t dep_slot = typeck_resolve_dep_index_for_import(module, ctx, dep_ix);
    if ((dep_slot < 0)) {
      return 0;
    }
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
    if ((dm ==0)) {
      return 0;
    }
    (void)((sel_cnt = pipeline_module_import_select_count_at(module, dep_ix)));
    (void)((k = 0));
    while ((k < sel_cnt)) {
      if (typeck_import_select_name_equal(module, dep_ix, k, &((cv_nm)[0]), cv_len)) {
        return typeck_find_func_return_type_in_module_by_name(dm, arena, &((cv_nm)[0]), cv_len, dep_slot, ctx, func_index_out);
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
}
int32_t typeck_resolve_call_callee_try_whole_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord) {
  int32_t ord_field = 44;
  int32_t * null_po = 0;
  if ((callee_ord !=ord_field)) {
    return 0;
  }
  return typeck_resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx, null_po, null_po);
}
int32_t typeck_resolve_call_callee_try_binding_import(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t callee_ord) {
  int32_t ord_field = 44;
  int32_t * null_po = 0;
  if ((callee_ord !=ord_field)) {
    return 0;
  }
  return typeck_resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx, null_po, null_po);
}
int32_t typeck_resolve_call_callee_local_module(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t minus_one = -1;
  return typeck_find_func_return_type_in_module(module, arena, arena, arena, callee_expr_ref, minus_one, ctx, 0);
}
int32_t typeck_resolve_call_callee_scan_dep(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t callee_ord, struct ast_PipelineDepCtx * ctx, int32_t dep_i, int32_t imax) {
  {
    struct ast_Module * dm = 0;
    int32_t ret = 0;
    int32_t * null_po = 0;
    if ((dep_i >=imax)) {
      return 0;
    }
    (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_i)));
    if ((dm !=0)) {
      (void)((ret = typeck_find_func_return_type_in_module(dm, arena, arena, arena, callee_expr_ref, dep_i, ctx, null_po)));
      if ((ret !=0)) {
        return ret;
      }
      ((dep_i < typeck_module_num_imports(module)) ? ({   (void)((ret = typeck_resolve_call_select_import_return_type(module, arena, callee_expr_ref, callee_ord, dep_i, ctx, null_po)));
  ((ret !=0) ? ({   return ret;
 }) : 0);
 }) : 0);
    }
    return typeck_resolve_call_callee_scan_dep(module, arena, callee_expr_ref, callee_ord, ctx, (dep_i + 1), imax);
  }
}
int32_t typeck_resolve_call_callee_return_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t want_apply = 0;
    int32_t callee_ord = 0;
    int32_t ret = 0;
    int32_t imax = 0;
    int32_t nd_scan = 0;
    if (((callee_expr_ref <=0) || (callee_expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if (((call_expr_ref > 0) && (call_expr_ref <=((arena)->num_exprs)))) {
      (void)((want_apply = 1));
    }
    (void)((callee_ord = pipeline_expr_kind_ord_at(arena, callee_expr_ref)));
    (void)((ret = typeck_resolve_call_callee_try_whole_import(module, arena, callee_expr_ref, ctx, callee_ord)));
    if ((ret !=0)) {
      if ((want_apply !=0)) {
        (void)(typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0));
        (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
        (void)(typeck_resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx, typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot()));
        (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(), typeck_call_resolve_func_idx_peek()));
      }
      return ret;
    }
    (void)((ret = typeck_resolve_call_callee_try_binding_import(module, arena, callee_expr_ref, call_expr_ref, ctx, callee_ord)));
    if ((ret !=0)) {
      if ((want_apply !=0)) {
        (void)(typeck_i32_ptr_store(typeck_call_resolve_dep_idx_slot(), 0));
        (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
        (void)((ret = typeck_resolve_call_binding_import_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx, typeck_call_resolve_dep_idx_slot(), typeck_call_resolve_func_idx_slot())));
        (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, typeck_call_resolve_dep_idx_peek(), typeck_call_resolve_func_idx_peek()));
      }
      return ret;
    }
    (void)((ret = typeck_resolve_call_callee_local_module(module, arena, callee_expr_ref, ctx)));
    if ((ret !=0)) {
      if ((want_apply !=0)) {
        int32_t minus_one_lm = -1;
        (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
        (void)((ret = typeck_find_func_return_type_in_module_overload(module, arena, arena, arena, callee_expr_ref, call_expr_ref, minus_one_lm, ctx, typeck_call_resolve_func_idx_slot())));
        (void)(ast_ast_expr_apply_call_resolve(arena, call_expr_ref, minus_one_lm, typeck_call_resolve_func_idx_peek()));
      }
      return ret;
    }
    (void)((imax = typeck_module_num_imports(module)));
    (void)((nd_scan = pipeline_dep_ctx_ndep(ctx)));
    if ((nd_scan > imax)) {
      (void)((imax = nd_scan));
    }
    return typeck_resolve_scan_dep_with_apply(module, arena, callee_expr_ref, callee_ord, call_expr_ref, ctx, 0, imax, want_apply);
  }
}
int32_t typeck_expr_type_ref(struct ast_ASTArena * arena, int32_t expr_ref) {
  if (ast_ref_is_null(expr_ref)) {
    return 0;
  }
  if (((expr_ref <=0) || (expr_ref > ((arena)->num_exprs)))) {
    return 0;
  }
  return pipeline_expr_resolved_type_ref(arena, expr_ref);
}
int typeck_type_ref_is_bool_impl(struct ast_ASTArena * arena, int32_t type_ref) {
  {
    int32_t ord_bool = 1;
    return (pipeline_type_kind_ord_at(arena, type_ref) ==ord_bool);
  }
}
int typeck_type_ref_is_bool(struct ast_ASTArena * arena, int32_t type_ref) {
  if (ast_ref_is_null(type_ref)) {
    return 0;
  }
  if (((type_ref <=0) || (type_ref > ((arena)->num_types)))) {
    return 0;
  }
  return typeck_type_ref_is_bool_impl(arena, type_ref);
}
int32_t typeck_named_unqual_start(uint8_t * buf, int32_t len) {
  int32_t i = (len - 1);
  while ((i > 0)) {
    if (((buf)[i] ==46)) {
      return (i + 1);
    }
    (void)((i = (i - 1)));
  }
  return 0;
}
int32_t typeck_type_ref_mangle_suffix(struct ast_ASTArena * arena, int32_t type_ref, uint8_t * buf, int32_t buf_cap) {
  {
    int32_t tk = 0;
    int32_t n = 0;
    int32_t elem = 0;
    if (((((arena ==0) || (type_ref <=0)) || (buf ==0)) || (buf_cap <=0))) {
      return 0;
    }
    (void)((tk = pipeline_type_kind_ord_at(arena, type_ref)));
    if ((tk ==9)) {
      (void)((elem = pipeline_type_elem_ref_at(arena, type_ref)));
      (void)((n = typeck_type_ref_mangle_suffix(arena, elem, buf, buf_cap)));
      if (((n > 0) && ((n + 4) < buf_cap))) {
        (void)(((buf)[n] = 95));
        (void)(((buf)[(n + 1)] = 112));
        (void)(((buf)[(n + 2)] = 116));
        (void)(((buf)[(n + 3)] = 114));
        return (n + 4);
      }
      return n;
    }
    if ((tk ==8)) {
      (void)((n = pipeline_type_named_name_into(arena, type_ref, buf)));
      if (((n <=0) || (n >=buf_cap))) {
        return 0;
      }
      return n;
    }
    if ((tk ==0)) {
      if ((buf_cap < 3)) {
        return 0;
      }
      (void)(((buf)[0] = 105));
      (void)(((buf)[1] = 51));
      (void)(((buf)[2] = 50));
      return 3;
    }
    if ((tk ==5)) {
      if ((buf_cap < 3)) {
        return 0;
      }
      (void)(((buf)[0] = 105));
      (void)(((buf)[1] = 54));
      (void)(((buf)[2] = 52));
      return 3;
    }
    if ((tk ==2)) {
      if ((buf_cap < 2)) {
        return 0;
      }
      (void)(((buf)[0] = 117));
      (void)(((buf)[1] = 56));
      return 2;
    }
    if ((tk ==3)) {
      if ((buf_cap < 3)) {
        return 0;
      }
      (void)(((buf)[0] = 117));
      (void)(((buf)[1] = 51));
      (void)(((buf)[2] = 50));
      return 3;
    }
    if ((tk ==4)) {
      if ((buf_cap < 3)) {
        return 0;
      }
      (void)(((buf)[0] = 117));
      (void)(((buf)[1] = 54));
      (void)(((buf)[2] = 52));
      return 3;
    }
    if ((tk ==1)) {
      if ((buf_cap < 4)) {
        return 0;
      }
      (void)(((buf)[0] = 98));
      (void)(((buf)[1] = 111));
      (void)(((buf)[2] = 111));
      (void)(((buf)[3] = 108));
      return 4;
    }
    if ((tk ==6)) {
      if ((buf_cap < 5)) {
        return 0;
      }
      (void)(((buf)[0] = 117));
      (void)(((buf)[1] = 115));
      (void)(((buf)[2] = 105));
      (void)(((buf)[3] = 122));
      (void)(((buf)[4] = 101));
      return 5;
    }
    if ((tk ==7)) {
      if ((buf_cap < 5)) {
        return 0;
      }
      (void)(((buf)[0] = 105));
      (void)(((buf)[1] = 115));
      (void)(((buf)[2] = 105));
      (void)(((buf)[3] = 122));
      (void)(((buf)[4] = 101));
      return 5;
    }
    return 0;
  }
}
int32_t typeck_named_inst_mangle_into(struct ast_ASTArena * arena, int32_t ty, uint8_t * out, int32_t out_cap) {
  {
    uint8_t base[128] = {};
    int32_t base_len = 0;
    int32_t n_args = 0;
    int32_t pos = 0;
    int32_t ai = 0;
    int32_t is_result = 0;
    int32_t e_is_i32 = 0;
    int32_t arg = 0;
    uint8_t suf[64] = {};
    int32_t sl = 0;
    int32_t sj = 0;
    if (((((arena ==0) || (ty <=0)) || (out ==0)) || (out_cap <=0))) {
      return 0;
    }
    (void)((n_args = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, ty)));
    if ((n_args <=0)) {
      return 0;
    }
    (void)((base_len = pipeline_type_named_name_into(arena, ty, &((base)[0]))));
    if (((base_len <=0) || (base_len >=out_cap))) {
      return 0;
    }
    (void)((pos = 0));
    while ((pos < base_len)) {
      (void)(((out)[pos] = (base)[pos]));
      (void)((pos = (pos + 1)));
    }
    if ((((((((base_len ==6) && ((base)[0] ==82)) && ((base)[1] ==101)) && ((base)[2] ==115)) && ((base)[3] ==117)) && ((base)[4] ==108)) && ((base)[5] ==116))) {
      (void)((is_result = 1));
    }
    if (((is_result !=0) && (n_args >=2))) {
      (void)((arg = pipeline_type_type_arg_ref_at(arena, ty, 1)));
      (((arg > 0) && (pipeline_type_kind_ord_at(arena, arg) ==0)) ? ({   (void)((e_is_i32 = 1));
 }) : 0);
    }
    (void)((ai = 0));
    while (((ai < n_args) && (ai < 8))) {
      ((((is_result !=0) && (e_is_i32 !=0)) && (ai ==1)) ? ({   (void)((ai = (ai + 1)));
 }) : ({   (void)((arg = pipeline_type_type_arg_ref_at(arena, ty, ai)));
  if ((arg <=0)) {
    return 0;
  }
  (void)((sl = typeck_type_ref_mangle_suffix(arena, arg, &((suf)[0]), 64)));
  if (((sl <=0) || (((pos + 1) + sl) >=out_cap))) {
    return 0;
  }
  (void)(((out)[pos] = 95));
  (void)((pos = (pos + 1)));
  (void)((sj = 0));
  while ((sj < sl)) {
    (void)(((out)[pos] = (suf)[sj]));
    (void)((pos = (pos + 1)));
    (void)((sj = (sj + 1)));
  }
  (void)((ai = (ai + 1)));
 }));
    }
    if ((pos <=base_len)) {
      return 0;
    }
    return pos;
  }
}
int typeck_type_refs_equal_named(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  {
    uint8_t * buf_a = typeck_scratch64_slot(0);
    uint8_t * buf_b = typeck_scratch64_slot(1);
    int32_t na = pipeline_type_named_name_into(arena, a, buf_a);
    int32_t nb = pipeline_type_named_name_into(arena, b, buf_b);
    int32_t i = 0;
    int32_t ta = 0;
    int32_t tb = 0;
    int32_t ua = 0;
    int32_t ub = 0;
    uint8_t mangled[128] = {};
    int32_t ml = 0;
    int32_t na_args = 0;
    int32_t nb_args = 0;
    if (((na <=0) || (nb <=0))) {
      return 0;
    }
    if ((na ==nb)) {
      (void)((i = 0));
      while ((i < na)) {
        if (((buf_a)[i] !=(buf_b)[i])) {
          break;
        }
        (void)((i = (i + 1)));
      }
      ((i ==na) ? ({   (void)((na_args = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, a)));
  (void)((nb_args = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, b)));
  if (((na_args ==0) && (nb_args ==0))) {
    return 1;
  }
  ((((na_args > 0) && (nb_args > 0)) && (na_args ==nb_args)) ? ({   (void)((i = 0));
  while ((i < na_args)) {
    if (!(typeck_type_refs_equal(arena, pipeline_type_type_arg_ref_at(arena, a, i), pipeline_type_type_arg_ref_at(arena, b, i)))) {
      return 0;
    }
    (void)((i = (i + 1)));
  }
  return 1;
 }) : 0);
 }) : 0);
    }
    (void)((na_args = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, a)));
    (void)((nb_args = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arena, b)));
    if (((na_args > 0) && (nb_args ==0))) {
      (void)((ml = typeck_named_inst_mangle_into(arena, a, &((mangled)[0]), 128)));
      ((ml > 0) ? ({   if ((ml ==nb)) {
    (void)((i = 0));
    while ((i < ml)) {
      if (((mangled)[i] !=(buf_b)[i])) {
        break;
      }
      (void)((i = (i + 1)));
    }
    ((i ==ml) ? ({   return 1;
 }) : 0);
  }
  (void)((tb = typeck_named_unqual_start(buf_b, nb)));
  (void)((ub = (nb - tb)));
  (((ml ==ub) && (ub > 0)) ? ({   (void)((i = 0));
  while ((i < ml)) {
    if (((mangled)[i] !=(buf_b)[(tb + i)])) {
      break;
    }
    (void)((i = (i + 1)));
  }
  ((i ==ml) ? ({   return 1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (((nb_args > 0) && (na_args ==0))) {
      (void)((ml = typeck_named_inst_mangle_into(arena, b, &((mangled)[0]), 128)));
      ((ml > 0) ? ({   if ((ml ==na)) {
    (void)((i = 0));
    while ((i < ml)) {
      if (((mangled)[i] !=(buf_a)[i])) {
        break;
      }
      (void)((i = (i + 1)));
    }
    ((i ==ml) ? ({   return 1;
 }) : 0);
  }
  (void)((ta = typeck_named_unqual_start(buf_a, na)));
  (void)((ua = (na - ta)));
  (((ml ==ua) && (ua > 0)) ? ({   (void)((i = 0));
  while ((i < ml)) {
    if (((mangled)[i] !=(buf_a)[(ta + i)])) {
      break;
    }
    (void)((i = (i + 1)));
  }
  ((i ==ml) ? ({   return 1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    (void)((ta = typeck_named_unqual_start(buf_a, na)));
    (void)((tb = typeck_named_unqual_start(buf_b, nb)));
    (void)((ua = (na - ta)));
    (void)((ub = (nb - tb)));
    if (((ua !=ub) || (ua <=0))) {
      return 0;
    }
    (void)((i = 0));
    while ((i < ua)) {
      if (((buf_a)[(ta + i)] !=(buf_b)[(tb + i)])) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    return 1;
  }
}
int typeck_type_refs_equal_same_kind(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord) {
  {
    int32_t ea = 0;
    int32_t eb = 0;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_linear = 12;
    int32_t ord_vector = 13;
    int32_t ord_fn = 18;
    if ((kind_ord ==ord_named)) {
      return typeck_type_refs_equal_named(arena, a, b);
    }
    if ((((kind_ord ==ord_ptr) || (kind_ord ==ord_slice)) || (kind_ord ==ord_linear))) {
      (void)((ea = pipeline_type_elem_ref_at(arena, a)));
      (void)((eb = pipeline_type_elem_ref_at(arena, b)));
      return typeck_type_refs_equal(arena, ea, eb);
    }
    if (((kind_ord ==ord_array) || (kind_ord ==ord_vector))) {
      if ((pipeline_type_array_size_at(arena, a) !=pipeline_type_array_size_at(arena, b))) {
        return 0;
      }
      (void)((ea = pipeline_type_elem_ref_at(arena, a)));
      (void)((eb = pipeline_type_elem_ref_at(arena, b)));
      return typeck_type_refs_equal(arena, ea, eb);
    }
    if ((kind_ord == ord_fn)) {
      return (typeck_fn_type_sig_equal(arena, a, b) != 0);
    }
    return 1;
  }
}
int typeck_type_refs_equal_impl(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  {
    int32_t ka = pipeline_type_kind_ord_at(arena, a);
    int32_t kb = pipeline_type_kind_ord_at(arena, b);
    if ((ka !=kb)) {
      return 0;
    }
    return typeck_type_refs_equal_same_kind(arena, a, b, ka);
  }
}
int typeck_type_refs_equal(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  if ((ast_ref_is_null(a) || ast_ref_is_null(b))) {
    return (a ==b);
  }
  (void)((a = typeck_resolve_type_alias_ref(arena, a)));
  (void)((b = typeck_resolve_type_alias_ref(arena, b)));
  if ((a ==b)) {
    return 1;
  }
  return typeck_type_refs_equal_impl(arena, a, b);
}
int typeck_integer_widen_ok(int32_t dest_kind, int32_t src_kind) {
  int32_t ord_i32 = 0;
  int32_t ord_u8 = 2;
  int32_t ord_u32 = 3;
  int32_t ord_u64 = 4;
  int32_t ord_i64 = 5;
  int32_t ord_usize = 6;
  int32_t ord_isize = 7;
  if ((dest_kind ==src_kind)) {
    if ((((((((dest_kind ==ord_i32) || (dest_kind ==ord_i64)) || (dest_kind ==ord_u8)) || (dest_kind ==ord_u32)) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize))) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_u8)) {
    if (((((((dest_kind ==ord_u32) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_i32)) || (dest_kind ==ord_i64)) || (dest_kind ==ord_isize))) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_i32)) {
    if (((((((dest_kind ==ord_i64) || (dest_kind ==ord_u32)) || (dest_kind ==ord_u64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize)) || (dest_kind ==ord_u8))) {
      return 1;
    }
    return 0;
  }
  if ((src_kind ==ord_u32)) {
    if (((((dest_kind ==ord_u64) || (dest_kind ==ord_i64)) || (dest_kind ==ord_usize)) || (dest_kind ==ord_isize))) {
      return 1;
    }
    return 0;
  }
  if (((src_kind ==ord_usize) && (dest_kind ==ord_u64))) {
    return 1;
  }
  if (((src_kind ==ord_u64) && (dest_kind ==ord_usize))) {
    return 1;
  }
  if (((src_kind ==ord_isize) && (dest_kind ==ord_i64))) {
    return 1;
  }
  if (((src_kind ==ord_i64) && (dest_kind ==ord_isize))) {
    return 1;
  }
  return 0;
}
int32_t typeck_int_family_id(struct ast_ASTArena * arena, int32_t type_ref) {
  {
    int32_t k = 0;
    int32_t nlen = 0;
    uint8_t * buf = typeck_scratch64_slot(15);
    if ((ast_ref_is_null(type_ref) || (type_ref <=0))) {
      return -1;
    }
    (void)((k = pipeline_type_kind_ord_at(arena, type_ref)));
    if ((((((((k ==0) || (k ==2)) || (k ==3)) || (k ==4)) || (k ==5)) || (k ==6)) || (k ==7))) {
      return k;
    }
    if ((k !=8)) {
      return -1;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, type_ref, buf)));
    if ((((nlen ==2) && ((buf)[0] ==105)) && ((buf)[1] ==56))) {
      return 10;
    }
    if (((((nlen ==3) && ((buf)[0] ==105)) && ((buf)[1] ==49)) && ((buf)[2] ==54))) {
      return 11;
    }
    if (((((nlen ==3) && ((buf)[0] ==117)) && ((buf)[1] ==49)) && ((buf)[2] ==54))) {
      return 12;
    }
    return -1;
  }
}
int typeck_integer_widen_ok_refs(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref) {
  {
    int32_t dest_f = 0;
    int32_t src_f = 0;
    if ((ast_ref_is_null(dest_ref) || ast_ref_is_null(src_ref))) {
      return 0;
    }
    (void)((dest_f = typeck_int_family_id(arena, dest_ref)));
    (void)((src_f = typeck_int_family_id(arena, src_ref)));
    if (((dest_f < 0) || (src_f < 0))) {
      return 0;
    }
    if ((dest_f ==src_f)) {
      return 1;
    }
    if (((dest_f <=7) && (src_f <=7))) {
      (typeck_integer_widen_ok(dest_f, src_f) ? ({   return 1;
 }) : 0);
    }
    if ((src_f ==10)) {
      if ((((((((((dest_f ==11) || (dest_f ==12)) || (dest_f ==2)) || (dest_f ==0)) || (dest_f ==3)) || (dest_f ==4)) || (dest_f ==5)) || (dest_f ==6)) || (dest_f ==7))) {
        return 1;
      }
      return 0;
    }
    if ((src_f ==11)) {
      if (((((((((dest_f ==12) || (dest_f ==2)) || (dest_f ==0)) || (dest_f ==3)) || (dest_f ==4)) || (dest_f ==5)) || (dest_f ==6)) || (dest_f ==7))) {
        return 1;
      }
      return 0;
    }
    if ((src_f ==12)) {
      if ((((((((dest_f ==2) || (dest_f ==0)) || (dest_f ==3)) || (dest_f ==4)) || (dest_f ==5)) || (dest_f ==6)) || (dest_f ==7))) {
        return 1;
      }
      return 0;
    }
    if ((dest_f ==10)) {
      if (((((src_f ==2) || (src_f ==0)) || (src_f ==11)) || (src_f ==12))) {
        return 1;
      }
      return 0;
    }
    if ((dest_f ==11)) {
      if (((((src_f ==2) || (src_f ==0)) || (src_f ==12)) || (src_f ==3))) {
        return 1;
      }
      return 0;
    }
    if ((dest_f ==12)) {
      if (((((src_f ==2) || (src_f ==0)) || (src_f ==11)) || (src_f ==3))) {
        return 1;
      }
      return 0;
    }
    return 0;
  }
}
int typeck_float_widen_ok(int32_t dest_kind, int32_t src_kind) {
  int32_t ord_f32 = 14;
  int32_t ord_f64 = 15;
  if ((dest_kind ==src_kind)) {
    if (((dest_kind ==ord_f32) || (dest_kind ==ord_f64))) {
      return 1;
    }
    return 0;
  }
  if (((src_kind ==ord_f32) && (dest_kind ==ord_f64))) {
    return 1;
  }
  return 0;
}
/* 10.3.1/10.3.2: TYPE_FN(18) or Cap *u8 — twin of typeck.x. PLATFORM: SHARED. */
int32_t typeck_is_fnptr_surface(struct ast_ASTArena * arena, int32_t type_ref) {
  int32_t ko = 0;
  int32_t er = 0;
  int32_t eko = 0;
  if (((arena ==0) || (type_ref <=0))) {
    return 0;
  }
  (void)((ko = pipeline_type_kind_ord_at(arena, type_ref)));
  if ((ko ==18)) {
    return 1;
  }
  if ((ko ==9)) {
    (void)((er = pipeline_type_elem_ref_at(arena, type_ref)));
    if ((er > 0)) {
      (void)((eko = pipeline_type_kind_ord_at(arena, er)));
      if ((eko ==2)) {
        return 1;
      }
    }
  }
  return 0;
}
/* 10.3.1: TYPE_FN structural signature equality (twin of typeck.x). PLATFORM: SHARED. */
int32_t typeck_fn_type_sig_equal(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  int32_t na = 0;
  int32_t nb = 0;
  int32_t i = 0;
  int32_t ra = 0;
  int32_t rb = 0;
  int32_t pa = 0;
  int32_t pb = 0;
  if (((arena == 0) || (a <= 0) || (b <= 0))) {
    return 0;
  }
  if (((pipeline_type_kind_ord_at(arena, a) != 18) || (pipeline_type_kind_ord_at(arena, b) != 18))) {
    return 0;
  }
  na = pipeline_type_array_size_at(arena, a);
  nb = pipeline_type_array_size_at(arena, b);
  if (((na != nb) || (na < 0))) {
    return 0;
  }
  ra = pipeline_type_elem_ref_at(arena, a);
  rb = pipeline_type_elem_ref_at(arena, b);
  if (!(typeck_type_refs_equal(arena, ra, rb))) {
    return 0;
  }
  i = 0;
  while ((i < na)) {
    pa = pipeline_type_type_arg_ref_at(arena, a, i);
    pb = pipeline_type_type_arg_ref_at(arena, b, i);
    if (((pa <= 0) || (pb <= 0) || !(typeck_type_refs_equal(arena, pa, pb)))) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}
/* 10.3.1: module func vs TYPE_FN expect (twin of typeck.x). PLATFORM: SHARED. */
int32_t typeck_module_func_matches_type_fn(struct ast_Module * module, struct ast_ASTArena * arena,
    int32_t fi, int32_t expect_fn) {
  int32_t np = 0;
  int32_t n_expect = 0;
  int32_t i = 0;
  int32_t pret = 0;
  int32_t eret = 0;
  int32_t ppar = 0;
  int32_t epar = 0;
  if (((module == 0) || (arena == 0) || (fi < 0) || (expect_fn <= 0))) {
    return 0;
  }
  if ((pipeline_type_kind_ord_at(arena, expect_fn) != 18)) {
    return 0;
  }
  np = pipeline_module_func_num_params_at(module, fi);
  n_expect = pipeline_type_array_size_at(arena, expect_fn);
  if (((np != n_expect) || (np < 0))) {
    return 0;
  }
  pret = pipeline_module_func_return_type_at(module, fi);
  eret = pipeline_type_elem_ref_at(arena, expect_fn);
  if (!(typeck_type_refs_equal(arena, pret, eret))) {
    return 0;
  }
  i = 0;
  while ((i < np)) {
    ppar = pipeline_module_func_param_type_ref_at(module, fi, i);
    epar = pipeline_type_type_arg_ref_at(arena, expect_fn, i);
    if (((ppar <= 0) || (epar <= 0) || !(typeck_type_refs_equal(arena, ppar, epar)))) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}
/* 10.3.1: same-block let init by name (Cap provenance). Twin typeck.x. */
int32_t typeck_block_let_init_by_name(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * name,
    int32_t name_len) {
  int32_t nl = 0;
  int32_t i = 0;
  int32_t ln = 0;
  uint8_t nbuf[128];
  int32_t j = 0;
  int32_t eq = 0;
  if (((arena == 0) || (block_ref <= 0) || (name == 0) || (name_len <= 0) || (name_len > 127))) {
    return 0;
  }
  nl = ast_ast_block_num_lets(arena, block_ref);
  i = 0;
  while ((i < nl)) {
    ln = pipeline_block_let_name_len(arena, block_ref, i);
    if ((ln == name_len)) {
      pipeline_block_let_name_copy64(arena, block_ref, i, &((nbuf)[0]));
      eq = 1;
      j = 0;
      while ((j < name_len)) {
        if (((nbuf)[j] != (name)[j])) {
          eq = 0;
          break;
        }
        j = j + 1;
      }
      if ((eq != 0)) {
        return pipeline_block_let_init_ref(arena, block_ref, i);
      }
    }
    i = i + 1;
  }
  return 0;
}
/* 10.3.1: recover module fn from Cap/AS provenance. Twin typeck.x. */
int32_t typeck_recover_fn_fi_from_cap_expr(struct ast_Module * module, struct ast_ASTArena * arena,
    int32_t expr, int32_t depth) {
  int32_t ko = 0;
  int32_t ord_var = 3;
  int32_t ord_as = 54;
  int32_t vnlen = 0;
  uint8_t vbuf[128];
  int32_t fi = 0;
  int32_t nfuncs = 0;
  int32_t op = 0;
  int32_t init_r = 0;
  struct ast_PipelineDepCtx * ctx = 0;
  int32_t br = 0;
  if (((module == 0) || (arena == 0) || (expr <= 0) || (depth > 8))) {
    return (0 - 1);
  }
  ko = pipeline_expr_kind_ord_at(arena, expr);
  if ((ko == ord_as)) {
    op = pipeline_expr_as_operand_ref_at(arena, expr);
    return typeck_recover_fn_fi_from_cap_expr(module, arena, op, (depth + 1));
  }
  if ((ko == ord_var)) {
    vnlen = pipeline_expr_var_name_len(arena, expr);
    if (((vnlen > 0) && (vnlen <= 127))) {
      pipeline_expr_var_name_into(arena, expr, &((vbuf)[0]));
      nfuncs = (module)->num_funcs;
      fi = 0;
      while ((fi < nfuncs)) {
        if ((pipeline_module_func_name_equal_at(module, fi, &((vbuf)[0]), vnlen) != 0)) {
          return fi;
        }
        fi = fi + 1;
      }
      ctx = pipeline_typeck_active_ctx_c();
      if ((ctx != 0)) {
        br = pipeline_dep_ctx_current_block_ref_at(ctx);
        if ((br > 0)) {
          init_r = typeck_block_let_init_by_name(arena, br, &((vbuf)[0]), vnlen);
          if ((init_r > 0)) {
            return typeck_recover_fn_fi_from_cap_expr(module, arena, init_r, (depth + 1));
          }
        }
      }
    }
  }
  return (0 - 1);
}
/* 10.3.1: Cap/TYPE_FN surface compat + signature + Cap provenance (twin of typeck.x). PLATFORM: SHARED. */
int32_t typeck_fnptr_surface_compat(struct ast_Module * module, struct ast_ASTArena * arena,
    int32_t expect_ty, int32_t got_ty, int32_t got_expr, int32_t allow_opaque) {
  int32_t ek = 0;
  int32_t gk = 0;
  struct ast_Module * mod = module;
  int32_t vnlen = 0;
  uint8_t vbuf[128];
  int32_t fi = 0;
  int32_t nfuncs = 0;
  int32_t ord_var = 3;
  int32_t recovered = 0;
  if (((arena == 0) || (expect_ty <= 0) || (got_ty <= 0))) {
    return 0;
  }
  if (((typeck_is_fnptr_surface(arena, expect_ty) == 0) || (typeck_is_fnptr_surface(arena, got_ty) == 0))) {
    return 0;
  }
  ek = pipeline_type_kind_ord_at(arena, expect_ty);
  gk = pipeline_type_kind_ord_at(arena, got_ty);
  if (((ek == 18) && (gk == 18))) {
    return typeck_fn_type_sig_equal(arena, expect_ty, got_ty);
  }
  if (((ek == 18) && (gk == 9))) {
    if ((mod == 0)) {
      mod = pipeline_typeck_active_module_c();
    }
    if (((mod != 0) && (got_expr > 0))) {
      if ((pipeline_expr_kind_ord_at(arena, got_expr) == ord_var)) {
        vnlen = pipeline_expr_var_name_len(arena, got_expr);
        if (((vnlen > 0) && (vnlen <= 127))) {
          pipeline_expr_var_name_into(arena, got_expr, &((vbuf)[0]));
          nfuncs = (mod)->num_funcs;
          fi = 0;
          while ((fi < nfuncs)) {
            if ((pipeline_module_func_name_equal_at(mod, fi, &((vbuf)[0]), vnlen) != 0)) {
              return typeck_module_func_matches_type_fn(mod, arena, fi, expect_ty);
            }
            fi = fi + 1;
          }
        }
      }
      recovered = typeck_recover_fn_fi_from_cap_expr(mod, arena, got_expr, 0);
      if ((recovered >= 0)) {
        return typeck_module_func_matches_type_fn(mod, arena, recovered, expect_ty);
      }
    }
    /* 10.3.1 slice16: opaque Cap→TYPE_FN hard reject unless allow_opaque (as). */
    if ((allow_opaque != 0)) {
      return 1;
    }
    return 0;
  }
  return 1;
}
/* 10.3.3 slice3: METHOD_CALL name → Cap/TYPE_FN field type (twin of typeck.x). */
int32_t typeck_method_call_field_fnptr_ty(struct ast_Module * module, struct ast_ASTArena * arena,
    struct ast_PipelineDepCtx * ctx, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen) {
  int32_t ty = 0;
  int32_t ko = 0;
  int32_t er = 0;
  int32_t nlen = 0;
  int32_t ftr = 0;
  uint8_t nm[128];
  if (((module == 0) || (arena == 0) || (base_ty <= 0) || (method_nm == 0) || (method_nlen <= 0)
      || (method_nlen > 127))) {
    return 0;
  }
  ty = base_ty;
  ko = pipeline_type_kind_ord_at(arena, ty);
  if ((ko == 9)) {
    er = pipeline_type_elem_ref_at(arena, ty);
    if ((er <= 0)) {
      return 0;
    }
    ty = er;
    ko = pipeline_type_kind_ord_at(arena, ty);
  }
  if ((ko != 8)) {
    return 0;
  }
  nlen = pipeline_type_named_name_into(arena, ty, &((nm)[0]));
  if (((nlen <= 0) || (nlen > 127))) {
    return 0;
  }
  ftr = typeck_get_field_type_ref_from_layout_deps(module, arena, ctx, &((nm)[0]), nlen, method_nm,
      method_nlen);
  if ((ftr <= 0)) {
    return 0;
  }
  if ((typeck_is_fnptr_surface(arena, ftr) != 0)) {
    return ftr;
  }
  return 0;
}
int32_t typeck_dyn_rhs_is_null_sentinel(struct ast_ASTArena * arena, int32_t rhs_type_ref, int32_t rhs_expr_ref) {
  {
    int32_t ord_lit = 0;
    if (ast_ref_is_null(rhs_expr_ref)) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, rhs_expr_ref) !=ord_lit)) {
      return 0;
    }
    if ((pipeline_expr_int_val_at(arena, rhs_expr_ref) !=0)) {
      return 0;
    }
    return 1;
  }
}
int32_t typeck_array_to_slice_ok(struct ast_ASTArena * arena, int32_t src_ty, int32_t dest_ty) {
  {
    int32_t se = 0;
    int32_t de = 0;
    if ((ast_ref_is_null(src_ty) || ast_ref_is_null(dest_ty))) {
      return 0;
    }
    if (((src_ty <=0) || (dest_ty <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, dest_ty) !=11)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, src_ty) !=10)) {
      return 0;
    }
    (void)((se = pipeline_type_elem_ref_at(arena, src_ty)));
    (void)((de = pipeline_type_elem_ref_at(arena, dest_ty)));
    if ((ast_ref_is_null(se) || ast_ref_is_null(de))) {
      return 0;
    }
    if (!(typeck_type_refs_equal(arena, se, de))) {
      return 0;
    }
    return 1;
  }
}
int typeck_return_operand_matches(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  {
    int32_t got = typeck_expr_type_ref(arena, op_ref);
    int32_t expect_kind = 0;
    int32_t got_kind = 0;
    if ((ast_ref_is_null(op_ref) || ast_ref_is_null(expect_ref))) {
      return 1;
    }
    if (ast_ref_is_null(got)) {
      int32_t ord_lit = 0;
      int32_t ord_ptr = 9;
      int32_t kop = pipeline_expr_kind_ord_at(arena, op_ref);
      (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
      if ((((kop ==ord_lit) && (expect_kind ==ord_ptr)) && (pipeline_expr_int_val_at(arena, op_ref) ==0))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
        return 1;
      }
      return 0;
    }
    if (typeck_type_refs_equal(arena, got, expect_ref)) {
      return 1;
    }
    (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
    (void)((got_kind = pipeline_type_kind_ord_at(arena, got)));
    if (typeck_integer_widen_ok_refs(arena, expect_ref, got)) {
      return 1;
    }
    if (typeck_float_widen_ok(expect_kind, got_kind)) {
      return 1;
    }
    if ((typeck_array_to_slice_ok(arena, got, expect_ref) !=0)) {
      return 1;
    }
    /* 10.3.1: Cap/TYPE_FN surface + signature (≡ typeck.x). Pass live module;
     * leftover-PE pipeline_typeck_active_module_c BSS may be NULL. */
    if ((typeck_fnptr_surface_compat(module, arena, expect_ref, got, op_ref, 0) != 0)) {
      return 1;
    }
    int32_t ord_linear = 12;
    if ((pipeline_type_kind_ord_at(arena, got) ==ord_linear)) {
      int32_t elem = pipeline_type_elem_ref_at(arena, got);
      ((!(ast_ref_is_null(elem)) && typeck_type_refs_equal(arena, elem, expect_ref)) ? ({   return 1;
 }) : 0);
    }
    return 0;
  }
}
extern int32_t pipeline_expr_is_null_keyword_c(struct ast_ASTArena * arena, int32_t expr_ref);
int32_t typeck_expr_is_null_keyword(struct ast_ASTArena * arena, int32_t expr_ref) {
  if (((arena ==0) || (expr_ref <=0))) {
    return 0;
  }
  return pipeline_expr_is_null_keyword_c(arena, expr_ref);
}
int32_t typeck_coerce_init_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int64_t int_val = 0;
    int32_t ord_expr_lit = 0;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_vector = 13;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    if ((init_kind !=ord_expr_lit)) {
      return 0;
    }
    (void)((int_val = pipeline_expr_int64_val_at(arena, init_ref)));
    if ((typeck_expr_is_null_keyword(arena, init_ref) !=0)) {
      if ((decl_kind ==ord_ptr)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
        return 1;
      }
      return 0;
    }
    if (((decl_kind ==ord_ptr) && (int_val ==0))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if (((decl_kind ==ord_array) && (int_val ==0))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((((decl_kind ==ord_u8) && (int_val >=0)) && (int_val <=255))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((decl_kind ==ord_i64)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((decl_kind ==ord_isize)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((decl_kind ==ord_u32)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if (((decl_kind ==ord_usize) || (decl_kind ==ord_u64))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((decl_kind ==ord_named)) {
      uint8_t nm16[128] = {};
      int32_t nlen16 = pipeline_type_named_name_into(arena, decl_ty_ref, &((nm16)[0]));
      if (((((((nlen16 ==3) && ((nm16)[0] ==117)) && ((nm16)[1] ==49)) && ((nm16)[2] ==54)) && (int_val >=0)) && (int_val <=65535))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
        return 1;
      }
      (((((((nlen16 ==3) && ((nm16)[0] ==105)) && ((nm16)[1] ==49)) && ((nm16)[2] ==54)) && ((int_val + 32768) >=0)) && (int_val <=32767)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
    }
    if (((decl_kind ==ord_f32) || (decl_kind ==ord_f64))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if (((int_val ==0) && ((decl_kind ==ord_named) || (decl_kind ==ord_vector)))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    return 0;
  }
}
int32_t typeck_coerce_init_float_lit_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t ord_expr_float = 1;
    int32_t ord_neg = 22;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t op_ref = 0;
    if (((decl_kind !=ord_f32) && (decl_kind !=ord_f64))) {
      return 0;
    }
    if ((init_kind ==ord_expr_float)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    if ((init_kind ==ord_neg)) {
      (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, init_ref)));
      (((!(ast_ref_is_null(op_ref)) && (op_ref > 0)) && (op_ref <=((arena)->num_exprs))) ? ({   ((pipeline_expr_kind_ord_at(arena, op_ref) ==ord_expr_float) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, decl_ty_ref));
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
 }) : 0);
    }
    return 0;
  }
}
void typeck_stamp_resolved_args_float_lit(struct ast_ASTArena * arena, int32_t expr_ref, struct ast_Module * callee_mod, int32_t func_ix, int32_t dep_ix, struct ast_PipelineDepCtx * ctx, int32_t param_base) {
  {
    int32_t ord_method = 49;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t call_kind = 0;
    int32_t i = 0;
    int32_t n = 0;
    int32_t arg_ref = 0;
    int32_t param_raw = 0;
    int32_t arg_kind = 0;
    int32_t pk = 0;
    int32_t caller_ty = 0;
    struct ast_ASTArena * da = 0;
    if (((((arena ==0) || (callee_mod ==0)) || (expr_ref <=0)) || (func_ix < 0))) {
      return;
    }
    if ((param_base < 0)) {
      (void)((param_base = 0));
    }
    (void)((call_kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((call_kind ==ord_method)) {
      (void)((n = pipeline_expr_method_call_num_args_at(arena, expr_ref)));
    } else {
      (void)((n = pipeline_expr_call_num_args_at(arena, expr_ref)));
    }
    if (((dep_ix >=0) && (ctx !=0))) {
      (void)((da = pipeline_dep_ctx_arena_at(ctx, dep_ix)));
      ((da ==0) ? ({   (void)((da = pipeline_get_dep_arena_slot(dep_ix)));
 }) : 0);
    }
    while ((i < n)) {
      if ((call_kind ==ord_method)) {
        (void)((arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, i)));
      } else {
        (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i)));
      }
      (void)((param_raw = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, (i + param_base))));
      (void)((pk = 0));
      if ((param_raw > 0)) {
        ((da !=0) ? ({   (void)((pk = pipeline_type_kind_ord_at(da, param_raw)));
 }) : ({   (void)((pk = pipeline_type_kind_ord_at(arena, param_raw)));
 }));
      }
      if (((arg_ref > 0) && ((pk ==ord_f32) || (pk ==ord_f64)))) {
        (void)((caller_ty = pipeline_type_ensure_by_kind_ord(arena, pk)));
        ((caller_ty > 0) ? ({   (void)((arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref)));
  (void)(typeck_coerce_init_float_lit_to_decl(arena, arg_ref, caller_ty, pk, arg_kind));
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
  }
}
int32_t typeck_coerce_init_enum_field_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t base_ix = 0;
    int32_t ord_named = 8;
    int32_t ord_expr_var = 3;
    int32_t ord_field_access = 44;
    if (((decl_kind !=ord_named) || (init_kind !=ord_field_access))) {
      return 0;
    }
    (void)((base_ix = pipeline_expr_field_access_base_ref(arena, init_ref)));
    if (((!(ast_ref_is_null(base_ix)) && (base_ix > 0)) && (base_ix <=((arena)->num_exprs)))) {
      uint8_t * decl_buf = typeck_scratch64_slot(0);
      uint8_t * vbuf = typeck_scratch64_slot(1);
      uint8_t * field_buf = typeck_scratch64_slot(2);
      int32_t decl_nlen = pipeline_type_named_name_into(arena, decl_ty_ref, decl_buf);
      int32_t vnlen = pipeline_expr_var_name_len(arena, base_ix);
      int32_t i_nm = 0;
      int eq_nm = 1;
      ((((pipeline_expr_kind_ord_at(arena, base_ix) ==ord_expr_var) && (decl_nlen ==vnlen)) && (decl_nlen > 0)) ? ({   (void)(pipeline_expr_var_name_into(arena, base_ix, vbuf));
  while ((i_nm < decl_nlen)) {
    if (((decl_buf)[i_nm] !=(vbuf)[i_nm])) {
      (void)((eq_nm = 0));
    }
    (void)((i_nm = (i_nm + 1)));
  }
  (eq_nm ? ({   int32_t field_nlen = pipeline_expr_field_access_name_len(arena, init_ref);
  (void)(pipeline_expr_field_access_name_into(arena, init_ref, field_buf));
  int32_t ev_tag = pipeline_module_enum_variant_tag_for_names(module, decl_buf, decl_nlen, field_buf, field_nlen);
  ((ev_tag >=0) ? ({   (void)(pipeline_expr_set_field_access_enum_variant(arena, init_ref, ev_tag));
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if ((pipeline_expr_field_access_is_enum_variant(arena, init_ref) !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    return 0;
  }
}
int32_t typeck_coerce_init_named_call_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t ord_type_named = 8;
    int32_t ord_expr_call = 48;
    if ((((decl_kind ==ord_type_named) && (init_kind ==ord_expr_call)) && ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, init_ref)))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    return 0;
  }
}
int32_t typeck_coerce_init_resolved_alias_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  {
    int32_t ord_type_named = 8;
    int32_t init_resolved = 0;
    int32_t decl_resolved = 0;
    if ((decl_kind !=ord_type_named)) {
      return 0;
    }
    (void)((init_resolved = pipeline_expr_resolved_type_ref(arena, init_ref)));
    if (ast_ref_is_null(init_resolved)) {
      return 0;
    }
    (void)((decl_resolved = typeck_resolve_type_alias_ref_local(module, arena, decl_ty_ref, 0)));
    if (ast_ref_is_null(decl_resolved)) {
      return 0;
    }
    if (!(typeck_type_refs_equal(arena, decl_resolved, init_resolved))) {
      return 0;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_coerce_array_lit_elem_types_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  {
    int32_t ord_type_array = 10;
    int32_t ord_type_slice = 11;
    int32_t ord_expr_array_lit = 46;
    int32_t decl_kind_here = 0;
    int32_t elem_decl_ref = 0;
    int32_t elem_decl_kind = 0;
    int32_t num_elems = 0;
    int32_t i = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    int32_t err_line = 0;
    int32_t err_col = 0;
    if ((ast_ref_is_null(init_ref) || ast_ref_is_null(decl_ty_ref))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, init_ref) !=ord_expr_array_lit)) {
      return 0;
    }
    (void)((decl_kind_here = pipeline_type_kind_ord_at(arena, decl_ty_ref)));
    if (((decl_kind_here !=ord_type_array) && (decl_kind_here !=ord_type_slice))) {
      return 0;
    }
    (void)((elem_decl_ref = pipeline_type_elem_ref_at(arena, decl_ty_ref)));
    if (ast_ref_is_null(elem_decl_ref)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      return 1;
    }
    (void)((elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl_ref)));
    (void)((num_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref)));
    while ((i < num_elems)) {
      int32_t elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, i);
      int32_t elem_kind = 0;
      int32_t elem_ty = 0;
      int32_t got_kind = 0;
      if (ast_ref_is_null(elem_ref)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((elem_kind = pipeline_expr_kind_ord_at(arena, elem_ref)));
      if (((elem_kind ==ord_expr_array_lit) && ((elem_decl_kind ==ord_type_array) || (elem_decl_kind ==ord_type_slice)))) {
        ((typeck_coerce_array_lit_elem_types_to_decl(module, arena, elem_ref, elem_decl_ref) < 0) ? ({   return -1;
 }) : 0);
      } else {
        (void)(typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl_ref, elem_decl_kind, elem_kind));
        (void)(typeck_coerce_init_float_lit_to_decl(arena, elem_ref, elem_decl_ref, elem_decl_kind, elem_kind));
        (void)(typeck_coerce_init_slice_from_array(arena, elem_ref, elem_decl_ref, elem_decl_kind));
        (void)((elem_ty = typeck_expr_type_ref(arena, elem_ref)));
        ((!(ast_ref_is_null(elem_ty)) && (elem_ty > 0)) ? ({   (void)((got_kind = pipeline_type_kind_ord_at(arena, elem_ty)));
  /* Twin living/typeck.x 10.3.1 slice12: TYPE_FN←Cap via fnptr_surface_compat. */
  ((((typeck_type_refs_equal(arena, elem_ty, elem_decl_ref) || typeck_integer_widen_ok_refs(arena, elem_decl_ref, elem_ty)) || typeck_float_widen_ok(elem_decl_kind, got_kind)) || (typeck_fnptr_surface_compat(module, arena, elem_decl_ref, elem_ty, elem_ref, 0) != 0)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl_ref));
 }) : ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, elem_decl_ref, eb, 96)));
  (void)((gl = typeck_diag_fmt_type_into(arena, elem_ty, gb, 96)));
  (void)((err_line = pipeline_expr_line_at(arena, elem_ref)));
  (void)((err_col = pipeline_expr_col_at(arena, elem_ref)));
  (void)(driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl));
  return -1;
 }));
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_vector_lanes_of_type(struct ast_ASTArena * arena, int32_t type_ref) {
  {
    int32_t ord_type_vector = 13;
    int32_t ord_type_named = 8;
    int32_t tk = 0;
    int32_t asz = 0;
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    int32_t i = 0;
    int32_t lanes = 0;
    if ((ast_ref_is_null(type_ref) || (type_ref <=0))) {
      return 0;
    }
    (void)((tk = pipeline_type_kind_ord_at(arena, type_ref)));
    if ((tk ==ord_type_vector)) {
      (void)((asz = pipeline_type_array_size_at(arena, type_ref)));
      if ((asz > 0)) {
        return asz;
      }
      return 0;
    }
    if ((tk !=ord_type_named)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, type_ref, &((nm)[0]))));
    (void)((i = 0));
    while ((i < nlen)) {
      if (((nm)[i] ==120)) {
        (void)((i = (i + 1)));
        (void)((lanes = 0));
        while ((((i < nlen) && ((nm)[i] >=48)) && ((nm)[i] <=57))) {
          (void)((lanes = ((lanes * 10) + (((int32_t)((nm)[i])) - 48))));
          (void)((i = (i + 1)));
        }
        if ((((lanes ==4) || (lanes ==8)) || (lanes ==16))) {
          return lanes;
        }
        return 0;
      }
      (void)((i = (i + 1)));
    }
    if (((((((nlen ==5) && ((nm)[0] ==86)) && ((nm)[1] ==101)) && ((nm)[2] ==99)) && ((nm)[3] ==52)) && ((nm)[4] ==102))) {
      return 4;
    }
    if (((((((nlen ==5) && ((nm)[0] ==86)) && ((nm)[1] ==101)) && ((nm)[2] ==99)) && ((nm)[3] ==56)) && ((nm)[4] ==105))) {
      return 8;
    }
    return 0;
  }
}
int32_t typeck_coerce_init_array_vector_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t ord_type_array = 10;
    int32_t ord_type_slice = 11;
    int32_t ord_type_vector = 13;
    int32_t ord_expr_array_lit = 46;
    int32_t lanes = 0;
    int32_t n_elems = 0;
    int32_t elem_decl = 0;
    int32_t elem_decl_kind = 0;
    int32_t i = 0;
    int32_t elem_ref = 0;
    int32_t ek = 0;
    int32_t elem_ty = 0;
    int32_t got_kind = 0;
    if ((((decl_kind ==ord_type_array) || (decl_kind ==ord_type_slice)) && (init_kind ==ord_expr_array_lit))) {
      return typeck_coerce_array_lit_elem_types_to_decl(module, arena, init_ref, decl_ty_ref);
    }
    if ((init_kind ==ord_expr_array_lit)) {
      (void)((n_elems = pipeline_expr_array_lit_num_elems_at(arena, init_ref)));
      (void)((lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref)));
      if (((lanes <=0) && (decl_kind ==ord_type_vector))) {
        (void)((lanes = pipeline_type_array_size_at(arena, decl_ty_ref)));
      }
      (((lanes > 0) && (n_elems ==lanes)) ? ({   (void)((elem_decl = typeck_vector_elem_type_ref(arena, decl_ty_ref)));
  if ((!(ast_ref_is_null(elem_decl)) && (elem_decl > 0))) {
    (void)((elem_decl_kind = pipeline_type_kind_ord_at(arena, elem_decl)));
    (void)((i = 0));
    while ((i < n_elems)) {
      (void)((elem_ref = pipeline_expr_array_lit_elem_ref(arena, init_ref, i)));
      if ((!(ast_ref_is_null(elem_ref)) && (elem_ref > 0))) {
        (void)((ek = pipeline_expr_kind_ord_at(arena, elem_ref)));
        (void)(typeck_coerce_init_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek));
        (void)(typeck_coerce_init_float_lit_to_decl(arena, elem_ref, elem_decl, elem_decl_kind, ek));
        (void)((elem_ty = typeck_expr_type_ref(arena, elem_ref)));
        ((!(ast_ref_is_null(elem_ty)) && (elem_ty > 0)) ? ({   (void)((got_kind = pipeline_type_kind_ord_at(arena, elem_ty)));
  (((typeck_type_refs_equal(arena, elem_ty, elem_decl) || typeck_integer_widen_ok_refs(arena, elem_decl, elem_ty)) || typeck_float_widen_ok(elem_decl_kind, got_kind)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, elem_ref, elem_decl));
 }) : ({   return 0;
 }));
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_coerce_init_vector_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t lref_c = 0;
    int32_t rref_c = 0;
    int32_t ord_type_vector = 13;
    int32_t ord_add = 4;
    int32_t ord_sub = 5;
    int32_t ord_mul = 6;
    int32_t ord_div = 7;
    int32_t ord_expr_array_lit = 46;
    int32_t lanes = 0;
    (void)((lanes = typeck_vector_lanes_of_type(arena, decl_ty_ref)));
    if (((lanes <=0) && (decl_kind !=ord_type_vector))) {
      return 0;
    }
    if ((lanes <=0)) {
      (void)((lanes = pipeline_type_array_size_at(arena, decl_ty_ref)));
    }
    if ((lanes <=0)) {
      return 0;
    }
    if (((((init_kind !=ord_add) && (init_kind !=ord_sub)) && (init_kind !=ord_mul)) && (init_kind !=ord_div))) {
      return 0;
    }
    (void)((lref_c = pipeline_expr_binop_left_ref_at(arena, init_ref)));
    (void)((rref_c = pipeline_expr_binop_right_ref_at(arena, init_ref)));
    if ((!(ast_ref_is_null(lref_c)) && !(ast_ref_is_null(rref_c)))) {
      int32_t lt_c = typeck_expr_type_ref(arena, lref_c);
      int32_t rt_c = typeck_expr_type_ref(arena, rref_c);
      int32_t lk_e = pipeline_expr_kind_ord_at(arena, lref_c);
      int32_t rk_e = pipeline_expr_kind_ord_at(arena, rref_c);
      if (((((lk_e ==ord_expr_array_lit) && (rk_e ==ord_expr_array_lit)) && (pipeline_expr_array_lit_num_elems_at(arena, lref_c) ==lanes)) && (pipeline_expr_array_lit_num_elems_at(arena, rref_c) ==lanes))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, lref_c, decl_ty_ref));
        (void)(pipeline_expr_set_resolved_type_ref(arena, rref_c, decl_ty_ref));
        (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
        return 1;
      }
      (((((!(ast_ref_is_null(lt_c)) && !(ast_ref_is_null(rt_c))) && (typeck_vector_lanes_of_type(arena, lt_c) ==lanes)) && (typeck_vector_lanes_of_type(arena, rt_c) ==lanes)) && typeck_type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_c), pipeline_type_elem_ref_at(arena, rt_c))) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_coerce_init_int_binop_to_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_add = 4;
    int32_t ord_sub = 5;
    int32_t ord_mul = 6;
    int32_t ord_div = 7;
    int32_t ord_neg = 22;
    int32_t ord_lit = 0;
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    int32_t op_ref = 0;
    if ((((arena ==0) || (init_ref <=0)) || (init_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if (((((((((((decl_kind !=ord_i32) && (decl_kind !=ord_i64)) && (decl_kind !=ord_u8)) && (decl_kind !=ord_u32)) && (decl_kind !=ord_u64)) && (decl_kind !=ord_usize)) && (decl_kind !=ord_isize)) && (decl_kind !=ord_f32)) && (decl_kind !=ord_f64)) && (decl_kind !=ord_named))) {
      return 0;
    }
    if ((decl_kind ==ord_named)) {
      (void)((nlen = pipeline_type_named_name_into(arena, decl_ty_ref, &((nm)[0]))));
      (!((((((nlen ==2) && ((nm)[0] ==105)) && ((nm)[1] ==56)) || ((((nlen ==3) && ((nm)[0] ==105)) && ((nm)[1] ==49)) && ((nm)[2] ==54))) || ((((nlen ==3) && ((nm)[0] ==117)) && ((nm)[1] ==49)) && ((nm)[2] ==54)))) ? ({   return 0;
 }) : 0);
    }
    if ((((((init_kind !=ord_add) && (init_kind !=ord_sub)) && (init_kind !=ord_mul)) && (init_kind !=ord_div)) && (init_kind !=ord_neg))) {
      return 0;
    }
    if ((((decl_kind ==ord_f32) || (decl_kind ==ord_f64)) && (init_kind ==ord_neg))) {
      (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, init_ref)));
      ((((!(ast_ref_is_null(op_ref)) && (op_ref > 0)) && (op_ref <=((arena)->num_exprs))) && (pipeline_expr_kind_ord_at(arena, op_ref) ==ord_lit)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, decl_ty_ref));
 }) : 0);
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_coerce_init_bool_to_int_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  {
    int32_t ord_bool = 1;
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t init_res = 0;
    int32_t init_tk = 0;
    if ((((((((decl_kind !=ord_i32) && (decl_kind !=ord_u8)) && (decl_kind !=ord_u32)) && (decl_kind !=ord_u64)) && (decl_kind !=ord_i64)) && (decl_kind !=ord_usize)) && (decl_kind !=ord_isize))) {
      return 0;
    }
    (void)((init_res = pipeline_expr_resolved_type_ref(arena, init_ref)));
    if (ast_ref_is_null(init_res)) {
      return 0;
    }
    (void)((init_tk = pipeline_type_kind_ord_at(arena, init_res)));
    if ((init_tk !=ord_bool)) {
      return 0;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_coerce_init_array_lit_to_len_int_decl(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  {
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_expr_array_lit = 46;
    if ((init_kind !=ord_expr_array_lit)) {
      return 0;
    }
    if ((((((((decl_kind !=ord_i32) && (decl_kind !=ord_u8)) && (decl_kind !=ord_u32)) && (decl_kind !=ord_u64)) && (decl_kind !=ord_i64)) && (decl_kind !=ord_usize)) && (decl_kind !=ord_isize))) {
      return 0;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_coerce_init_slice_from_array(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  {
    int32_t init_res = 0;
    if ((decl_kind !=11)) {
      return 0;
    }
    (void)((init_res = pipeline_expr_resolved_type_ref(arena, init_ref)));
    if ((typeck_array_to_slice_ok(arena, init_res, decl_ty_ref) ==0)) {
      return 0;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
    return 1;
  }
}
int32_t typeck_coerce_array_lit_struct_elems_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  {
    int32_t dk = 0;
    int32_t ik = 0;
    int32_t ed = 0;
    int32_t n = 0;
    int32_t k = 0;
    int32_t er = 0;
    int32_t ek = 0;
    if ((((((arena ==0) || (init_ref <=0)) || (init_ref > ((arena)->num_exprs))) || (decl_ty_ref <=0)) || (decl_ty_ref > ((arena)->num_types)))) {
      return 0;
    }
    (void)((ik = pipeline_expr_kind_ord_at(arena, init_ref)));
    (void)((dk = pipeline_type_kind_ord_at(arena, decl_ty_ref)));
    if ((ik !=46)) {
      return 0;
    }
    if ((dk !=10)) {
      ((dk !=11) ? ({   return 0;
 }) : 0);
    }
    (void)((ed = pipeline_type_elem_ref_at(arena, decl_ty_ref)));
    if ((ed <=0)) {
      return 0;
    }
    (void)((n = pipeline_expr_array_lit_num_elems_at(arena, init_ref)));
    (void)((k = 0));
    while ((k < n)) {
      (void)((er = pipeline_expr_array_lit_elem_ref(arena, init_ref, k)));
      if (((er > 0) && (er <=((arena)->num_exprs)))) {
        (void)((ek = pipeline_expr_kind_ord_at(arena, er)));
        if ((ek ==45)) {
          (void)(typeck_coerce_init_struct_lit_to_decl(module, arena, er, ed));
        }
        ((ek ==46) ? ({   (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, er, ed));
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    return 1;
  }
}
int32_t typeck_coerce_init_expr_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  {
    int32_t decl_kind = 0;
    int32_t init_kind = 0;
    if ((ast_ref_is_null(init_ref) || ast_ref_is_null(decl_ty_ref))) {
      return 0;
    }
    if (((((init_ref <=0) || (init_ref > ((arena)->num_exprs))) || (decl_ty_ref <=0)) || (decl_ty_ref > ((arena)->num_types)))) {
      return 0;
    }
    (void)((decl_kind = pipeline_type_kind_ord_at(arena, decl_ty_ref)));
    (void)((init_kind = pipeline_expr_kind_ord_at(arena, init_ref)));
    if ((typeck_coerce_init_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_float_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_enum_field_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_named_call_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_resolved_alias_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind) !=0)) {
      return 1;
    }
    (void)(({   int32_t arr_c = typeck_coerce_init_array_vector_lit_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind);
  if ((arr_c < 0)) {
    return -1;
  }
  ((arr_c !=0) ? ({   (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_ref, decl_ty_ref));
  return 1;
 }) : 0);
 }));
    if ((typeck_coerce_init_vector_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_int_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_bool_to_int_decl(arena, init_ref, decl_ty_ref, decl_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_array_lit_to_len_int_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_slice_from_array(arena, init_ref, decl_ty_ref, decl_kind) !=0)) {
      return 1;
    }
    if ((typeck_coerce_init_struct_lit_to_decl(module, arena, init_ref, decl_ty_ref) !=0)) {
      return 1;
    }
    return 0;
  }
}
int32_t typeck_coerce_init_struct_lit_to_decl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  {
    int32_t decl_kind = 0;
    int32_t init_kind = 0;
    int32_t name_len = 0;
    uint8_t decl_nm[128] = {};
    int32_t decl_nlen = 0;
    int32_t ord_named = 8;
    int32_t ord_struct_lit = 45;
    int32_t num_fields = 0;
    int32_t j = 0;
    int32_t flen = 0;
    int32_t init_r = 0;
    int32_t ftr = 0;
    uint8_t field_buf[128] = {};
    if ((((((arena ==0) || (init_ref <=0)) || (init_ref > ((arena)->num_exprs))) || (decl_ty_ref <=0)) || (decl_ty_ref > ((arena)->num_types)))) {
      return 0;
    }
    (void)((decl_kind = pipeline_type_kind_ord_at(arena, decl_ty_ref)));
    (void)((init_kind = pipeline_expr_kind_ord_at(arena, init_ref)));
    if (((decl_kind !=ord_named) || (init_kind !=ord_struct_lit))) {
      return 0;
    }
    (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, init_ref)));
    if ((name_len <=0)) {
      (void)((decl_nlen = pipeline_type_named_name_into(arena, decl_ty_ref, &((decl_nm)[0]))));
      if (((decl_nlen <=0) || (decl_nlen > 127))) {
        return 0;
      }
      (void)(pipeline_expr_struct_lit_type_name_set(arena, init_ref, &((decl_nm)[0]), decl_nlen));
      if ((module !=0)) {
        ((typeck_ensure_struct_layout_from_struct_lit(module, arena, init_ref) !=0) ? ({   return 0;
 }) : 0);
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty_ref));
      (void)((name_len = decl_nlen));
      (void)(pipeline_expr_struct_lit_type_name_into(arena, init_ref, &((decl_nm)[0])));
    } else {
      if ((name_len > 127)) {
        return 0;
      }
      (void)(pipeline_expr_struct_lit_type_name_into(arena, init_ref, &((decl_nm)[0])));
    }
    if (((module !=0) && (name_len > 0))) {
      (void)((num_fields = pipeline_expr_struct_lit_num_fields(arena, init_ref)));
      (void)((j = 0));
      while ((j < num_fields)) {
        (void)((flen = pipeline_expr_struct_lit_field_name_len(arena, init_ref, j)));
        (void)((init_r = pipeline_expr_struct_lit_init_ref(arena, init_ref, j)));
        if (((((flen > 0) && (flen <=127)) && (init_r > 0)) && (init_r <=((arena)->num_exprs)))) {
          (void)(pipeline_expr_struct_lit_field_name_into(arena, init_ref, j, &((field_buf)[0])));
          (void)((ftr = typeck_get_field_type_ref_from_layout(module, &((decl_nm)[0]), name_len, &((field_buf)[0]), flen)));
          ((ftr > 0) ? ({   if ((pipeline_expr_kind_ord_at(arena, init_r) ==ord_struct_lit)) {
    (void)(typeck_coerce_init_struct_lit_to_decl(module, arena, init_r, ftr));
  }
  ((pipeline_expr_kind_ord_at(arena, init_r) ==46) ? ({   (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_r, ftr));
 }) : 0);
 }) : 0);
        }
        (void)((j = (j + 1)));
      }
    }
    return 1;
  }
}
int32_t typeck_diag_append_lit(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len) {
  int32_t p = pos;
  int32_t i = 0;
  while ((((i < lit_len) && (p >=0)) && (p < cap))) {
    (void)(((out)[p] = (lit)[i]));
    (void)((p = (p + 1)));
    (void)((i = (i + 1)));
  }
  return p;
}
int32_t typeck_diag_append_u32_dec(uint8_t * out, int32_t pos, int32_t cap, int32_t v) {
  int32_t p = pos;
  if ((((v < 0) || (p < 0)) || (p >=cap))) {
    return p;
  }
  if ((v ==0)) {
    uint8_t zd[1] = {48};
    return typeck_diag_append_lit(out, p, cap, &((zd)[0]), 1);
  }
  int32_t cnt = 0;
  int32_t tc = v;
  while ((tc > 0)) {
    (void)((cnt = (cnt + 1)));
    (void)((tc = (tc / 10)));
  }
  int32_t k = (cnt - 1);
  int32_t tm = v;
  while ((tm > 0)) {
    int32_t d = (tm % 10);
    (void)((tm = (tm / 10)));
    if ((((pos + k) < 0) || ((pos + k) >=cap))) {
      return p;
    }
    (void)(((out)[(pos + k)] = ((uint8_t)((d + 48)))));
    (void)((k = (k - 1)));
  }
  return (pos + cnt);
}
int32_t typeck_diag_fmt_type_at(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap) {
  {
    uint8_t qmk[1] = {63};
    uint8_t lit_i32[3] = {105, 51, 50};
    uint8_t lit_bool[4] = {98, 111, 111, 108};
    uint8_t lit_u8[2] = {117, 56};
    uint8_t lit_u32[3] = {117, 51, 50};
    uint8_t lit_u64[3] = {117, 54, 52};
    uint8_t lit_i64[3] = {105, 54, 52};
    uint8_t lit_usize[5] = {117, 115, 105, 122, 101};
    uint8_t lit_isize[5] = {105, 115, 105, 122, 101};
    uint8_t lit_f32[3] = {102, 51, 50};
    uint8_t lit_f64[3] = {102, 54, 52};
    uint8_t lit_void[4] = {118, 111, 105, 100};
    /* 10.3.1: format TYPE_FN as "function" (was bare "?"). Twin of typeck.x. */
    uint8_t lit_fn[8] = {102, 117, 110, 99, 116, 105, 111, 110};
    uint8_t star[1] = {42};
    uint8_t lbk[1] = {91};
    uint8_t rbk[1] = {93};
    uint8_t slo[2] = {91, 93};
    int32_t kind = 0;
    int32_t nlen = 0;
    int32_t elem_ref = 0;
    int32_t asz = 0;
    int32_t ord_i32 = 0;
    int32_t ord_bool = 1;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_linear = 12;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_void = 16;
    int32_t ord_fn = 18;
    uint8_t * nm_buf = typeck_scratch64_slot(0);
    if ((((cur < 0) || (cap <=0)) || (cur >=cap))) {
      return cur;
    }
    if (((ast_ref_is_null(ref) || (ref <=0)) || (ref > ((arena)->num_types)))) {
      return typeck_diag_append_lit(out, cur, cap, &((qmk)[0]), 1);
    }
    (void)((kind = pipeline_type_kind_ord_at(arena, ref)));
    if ((kind ==ord_named)) {
      (void)((nlen = pipeline_type_named_name_into(arena, ref, nm_buf)));
      ((nlen > 0) ? ({   return typeck_diag_append_lit(out, cur, cap, nm_buf, nlen);
 }) : 0);
    }
    if ((kind ==ord_i32)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_i32)[0]), 3);
    }
    if ((kind ==ord_bool)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_bool)[0]), 4);
    }
    if ((kind ==ord_u8)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_u8)[0]), 2);
    }
    if ((kind ==ord_u32)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_u32)[0]), 3);
    }
    if ((kind ==ord_u64)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_u64)[0]), 3);
    }
    if ((kind ==ord_i64)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_i64)[0]), 3);
    }
    if ((kind ==ord_usize)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_usize)[0]), 5);
    }
    if ((kind ==ord_isize)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_isize)[0]), 5);
    }
    if ((kind ==ord_f32)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_f32)[0]), 3);
    }
    if ((kind ==ord_f64)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_f64)[0]), 3);
    }
    if ((kind ==ord_void)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_void)[0]), 4);
    }
    if ((kind ==ord_fn)) {
      return typeck_diag_append_lit(out, cur, cap, &((lit_fn)[0]), 8);
    }
    if ((kind ==ord_ptr)) {
      (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
      int32_t nex = typeck_diag_append_lit(out, cur, cap, &((star)[0]), 1);
      return typeck_diag_fmt_type_at(arena, elem_ref, out, nex, cap);
    }
    if ((kind ==ord_slice)) {
      uint8_t lt_ch[1] = {60};
      uint8_t gt_ch[1] = {62};
      int32_t rlen = 0;
      uint8_t * rbuf = typeck_scratch64_slot(15);
      (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
      int32_t nex2 = typeck_diag_append_lit(out, cur, cap, &((slo)[0]), 2);
      (void)((nex2 = typeck_diag_fmt_type_at(arena, elem_ref, out, nex2, cap)));
      (void)((rlen = pipeline_type_region_label_len_at(arena, ref)));
      if (((rlen > 0) && (pipeline_type_region_label_into(arena, ref, rbuf) ==rlen))) {
        int32_t p0 = typeck_diag_append_lit(out, nex2, cap, &((lt_ch)[0]), 1);
        int32_t p1 = typeck_diag_append_lit(out, p0, cap, rbuf, rlen);
        return typeck_diag_append_lit(out, p1, cap, &((gt_ch)[0]), 1);
      }
      return nex2;
    }
    if ((kind ==ord_linear)) {
      uint8_t lpar[7] = {76, 105, 110, 101, 97, 114, 40};
      uint8_t rpar[1] = {41};
      (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
      int32_t p0 = typeck_diag_append_lit(out, cur, cap, &((lpar)[0]), 7);
      int32_t p1 = typeck_diag_fmt_type_at(arena, elem_ref, out, p0, cap);
      return typeck_diag_append_lit(out, p1, cap, &((rpar)[0]), 1);
    }
    if ((kind ==ord_array)) {
      (void)((elem_ref = pipeline_type_elem_ref_at(arena, ref)));
      (void)((asz = pipeline_type_array_size_at(arena, ref)));
      ((!(ast_ref_is_null(elem_ref)) && (asz > 0)) ? ({   int32_t p0 = typeck_diag_append_lit(out, cur, cap, &((lbk)[0]), 1);
  int32_t p1 = typeck_diag_append_u32_dec(out, p0, cap, asz);
  int32_t p2 = typeck_diag_append_lit(out, p1, cap, &((rbk)[0]), 1);
  return typeck_diag_fmt_type_at(arena, elem_ref, out, p2, cap);
 }) : 0);
    }
    return typeck_diag_append_lit(out, cur, cap, &((qmk)[0]), 1);
  }
}
int32_t typeck_diag_fmt_type_into(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap) {
  return typeck_diag_fmt_type_at(arena, ref, out, 0, cap);
}
int32_t typeck_diag_fmt_type_or_question(struct ast_ASTArena * arena, int32_t ref, uint8_t * out) {
  uint8_t qmk[1] = {63};
  if (((ast_ref_is_null(ref) || (ref <=0)) || (ref > ((arena)->num_types)))) {
    return typeck_diag_append_lit(out, 0, 96, &((qmk)[0]), 1);
  }
  return typeck_diag_fmt_type_into(arena, ref, out, 96);
}
void typeck_ret_coerce_integral_to_expect_i32(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  {
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t ord_usize = 6;
    if ((((ast_ref_is_null(op_ref) || (op_ref <=0)) || (op_ref > ((arena)->num_exprs))) || ast_ref_is_null(expect_ref))) {
      return;
    }
    if (((expect_ref <=0) || (expect_ref > ((arena)->num_types)))) {
      return;
    }
    if ((pipeline_type_kind_ord_at(arena, expect_ref) !=ord_i32)) {
      return;
    }
    int32_t got_ref = typeck_expr_type_ref(arena, op_ref);
    if (((ast_ref_is_null(got_ref) || (got_ref <=0)) || (got_ref > ((arena)->num_types)))) {
      return;
    }
    int32_t got_kind = pipeline_type_kind_ord_at(arena, got_ref);
    if (((got_kind !=ord_u8) && (got_kind !=ord_usize))) {
      return;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
  }
}
void typeck_ret_coerce_integral_widen(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  {
    int32_t got_ref = 0;
    int32_t expect_kind = 0;
    int32_t got_kind = 0;
    if ((((ast_ref_is_null(op_ref) || (op_ref <=0)) || (op_ref > ((arena)->num_exprs))) || ast_ref_is_null(expect_ref))) {
      return;
    }
    if (((expect_ref <=0) || (expect_ref > ((arena)->num_types)))) {
      return;
    }
    (void)((got_ref = typeck_expr_type_ref(arena, op_ref)));
    if (((ast_ref_is_null(got_ref) || (got_ref <=0)) || (got_ref > ((arena)->num_types)))) {
      return;
    }
    (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
    (void)((got_kind = pipeline_type_kind_ord_at(arena, got_ref)));
    (typeck_integer_widen_ok_refs(arena, expect_ref, got_ref) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
  return;
 }) : 0);
  }
}
void typeck_ret_coerce_null_lit_to_expect(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  {
    int32_t ord_lit = 0;
    int32_t ord_ptr = 9;
    int32_t op_kind = 0;
    int32_t expect_kind = 0;
    int32_t int_val = 0;
    if ((((arena ==0) || ast_ref_is_null(op_ref)) || ast_ref_is_null(expect_ref))) {
      return;
    }
    (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
    if ((op_kind !=ord_lit)) {
      return;
    }
    (void)((expect_kind = pipeline_type_kind_ord_at(arena, expect_ref)));
    (void)((int_val = pipeline_expr_int_val_at(arena, op_ref)));
    (((expect_kind ==ord_ptr) && (int_val ==0)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, expect_ref));
 }) : 0);
  }
}
void typeck_ret_fixup_unresolved_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t op_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_call = 48;
    int32_t op_kind = 0;
    if ((((module ==0) || (arena ==0)) || ast_ref_is_null(op_ref))) {
      return;
    }
    if (!(ast_ref_is_null(typeck_expr_type_ref(arena, op_ref)))) {
      return;
    }
    (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
    if ((op_kind !=ord_call)) {
      return;
    }
    (void)(typeck_check_expr_call_resolve(module, arena, op_ref, ctx));
  }
}
int32_t typeck_return_breadcrumb_into(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out) {
  {
    int32_t ord_var = 3;
    int32_t ord_field = 44;
    int32_t ord_call = 48;
    int32_t ord_method_call = 49;
    int32_t kind = 0;
    int32_t base_ref = 0;
    int32_t callee_ref = 0;
    int32_t base_len = 0;
    int32_t field_len = 0;
    int32_t callee_len = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((kind ==ord_var)) {
      (void)((base_len = pipeline_expr_var_name_len(arena, expr_ref)));
      if (((base_len <=0) || (base_len > 60))) {
        return 0;
      }
      (void)(pipeline_expr_var_name_into(arena, expr_ref, out));
      (void)(((out)[base_len] = 0));
      return base_len;
    }
    if ((kind ==ord_field)) {
      (void)((base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref)));
      if (((base_ref <=0) || (base_ref > ((arena)->num_exprs)))) {
        return 0;
      }
      (void)((base_len = typeck_return_breadcrumb_into(arena, base_ref, out)));
      (void)((field_len = pipeline_expr_field_access_name_len(arena, expr_ref)));
      if ((((base_len <=0) || (field_len <=0)) || (((base_len + 1) + field_len) > 60))) {
        return 0;
      }
      (void)(((out)[base_len] = 46));
      (void)(pipeline_expr_field_access_name_into(arena, expr_ref, &((out)[(base_len + 1)])));
      (void)(((out)[((base_len + 1) + field_len)] = 0));
      return ((base_len + 1) + field_len);
    }
    if ((kind ==ord_call)) {
      (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
      (void)((callee_len = typeck_return_breadcrumb_into(arena, callee_ref, out)));
      if (((callee_len <=0) || ((callee_len + 2) > 60))) {
        return 0;
      }
      (void)(((out)[callee_len] = 40));
      (void)(((out)[(callee_len + 1)] = 41));
      (void)(((out)[(callee_len + 2)] = 0));
      return (callee_len + 2);
    }
    if ((kind ==ord_method_call)) {
      (void)((base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref)));
      (void)((base_len = typeck_return_breadcrumb_into(arena, base_ref, out)));
      (void)((field_len = pipeline_expr_method_call_name_len(arena, expr_ref)));
      if ((((base_len <=0) || (field_len <=0)) || (((base_len + 3) + field_len) > 60))) {
        return 0;
      }
      (void)(((out)[base_len] = 46));
      (void)(pipeline_expr_method_call_name_into(arena, expr_ref, &((out)[(base_len + 1)])));
      (void)(((out)[((base_len + 1) + field_len)] = 40));
      (void)(((out)[((base_len + 2) + field_len)] = 41));
      (void)(((out)[((base_len + 3) + field_len)] = 0));
      return ((base_len + 3) + field_len);
    }
    return 0;
  }
}
void typeck_emit_return_subexpr_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col) {
  {
    uint8_t * buf = typeck_scratch64_slot(2);
    int32_t bl = typeck_return_breadcrumb_into(arena, expr_ref, buf);
    ((bl > 0) ? ({   (void)(driver_diagnostic_typeck_return_subexpr(line, col, buf, bl));
 }) : 0);
  }
}
void typeck_emit_return_unresolved_breadcrumb(struct ast_ASTArena * arena, int32_t expr_ref, int32_t line, int32_t col) {
  {
    uint8_t * buf = typeck_scratch64_slot(2);
    int32_t bl = typeck_return_breadcrumb_into(arena, expr_ref, buf);
    ((bl > 0) ? ({   (void)(driver_diagnostic_typeck_return_unresolved(line, col, buf, bl));
 }) : 0);
  }
}
int32_t typeck_check_expr_float_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    (void)(pipeline_expr_typeck_set_float_bits_from_val(arena, expr_ref));
    int32_t ft = typeck_ensure_f64_type_ref(arena);
    if ((ft !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ft));
    }
    return 0;
  }
}
int32_t typeck_check_expr_int_lit(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref) {
  {
    int64_t v = 0;
    int32_t ty = 0;
    int32_t vlen = 0;
    uint8_t vname[8] = {};
    int64_t i32_max = 2147483647;
    int64_t i32_min = -(2147483648);
    int32_t ord_i32 = 0;
    int32_t ord_i64 = 5;
    (void)(typeck_ret_coerce_null_lit_to_expect(arena, expr_ref, return_type_ref));
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if (!(ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref)))) {
      return 0;
    }
    (void)((v = pipeline_expr_int64_val_at(arena, expr_ref)));
    (void)((vlen = pipeline_expr_var_name_len(arena, expr_ref)));
    if (((v ==0) && (vlen ==4))) {
      (void)(pipeline_expr_var_name_into(arena, expr_ref, &((vname)[0])));
      ((((((vname)[0] ==110) && ((vname)[1] ==117)) && ((vname)[2] ==108)) && ((vname)[3] ==108)) ? ({   return 0;
 }) : 0);
    }
    if (((v > i32_max) || (v < i32_min))) {
      (void)((ty = pipeline_type_ensure_by_kind_ord(arena, ord_i64)));
    } else {
      (void)((ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32)));
    }
    if ((ty !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty));
    }
    return 0;
  }
}
int32_t typeck_check_expr_bool_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    int32_t bt = typeck_ensure_bool_type_ref(arena);
    if ((bt !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
    }
    return 0;
  }
}
int32_t typeck_check_expr_string_lit(struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    int32_t u8r = typeck_ensure_u8_type_ref(arena);
    int32_t ptr_u8 = 0;
    if (ast_ref_is_null(u8r)) {
      return -1;
    }
    (void)((ptr_u8 = typeck_find_or_alloc_ptr_type_ref(arena, u8r)));
    if (!(ast_ref_is_null(ptr_u8))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_u8));
    }
    return 0;
  }
}
int32_t typeck_check_expr_break_continue(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_break = 39;
    int32_t ord_continue = 40;
    int32_t line = 0;
    int32_t col = 0;
    int32_t kind = 0;
    int32_t is_break = 1;
    if ((pipeline_dep_ctx_typeck_loop_depth_at(ctx) > 0)) {
      return 0;
    }
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((kind ==ord_continue)) {
      (void)((is_break = 0));
    }
    (void)(driver_diagnostic_typeck_break_continue_outside(line, col, is_break));
    return -1;
  }
}
int32_t typeck_check_expr_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref) {
  {
    int32_t it = typeck_ensure_i32_type_ref(arena);
    if ((it !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, it));
    }
    return 0;
  }
}
int32_t typeck_check_expr_if_ternary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_ternary = 27;
    int32_t ord_named = 8;
    int32_t ord_lit = 0;
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    int32_t cond_ref = pipeline_expr_if_cond_ref_at(arena, expr_ref);
    int32_t then_ref = pipeline_expr_if_then_ref_at(arena, expr_ref);
    int32_t else_ref = pipeline_expr_if_else_ref_at(arena, expr_ref);
    int32_t ty_t = 0;
    int32_t ty_e = 0;
    int t_named = 0;
    int e_named = 0;
    int32_t resolved = 0;
    int32_t cond_ty = 0;
    int32_t expect_kind = 0;
    int32_t got_kind = 0;
    int32_t then_k = 0;
    int32_t else_k = 0;
    int32_t tv = 0;
    int32_t ev = 0;
    if ((typeck_check_expr(module, arena, cond_ref, 0, ctx) !=0)) {
      return -1;
    }
    if (!(ast_ref_is_null(cond_ref))) {
      (void)((cond_ty = typeck_expr_type_ref(arena, cond_ref)));
      (!(typeck_type_ref_is_bool(arena, cond_ty)) ? ({   return -1;
 }) : 0);
    }
    if ((typeck_check_expr(module, arena, then_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if (!(ast_ref_is_null(else_ref))) {
      ((typeck_check_expr(module, arena, else_ref, return_type_ref, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)((ty_t = typeck_expr_type_ref(arena, then_ref)));
    (void)((ty_e = typeck_expr_type_ref(arena, else_ref)));
    if ((!(ast_ref_is_null(ty_t)) && (ty_t > 0))) {
      (void)((t_named = (pipeline_type_kind_ord_at(arena, ty_t) ==ord_named)));
    }
    if ((!(ast_ref_is_null(ty_e)) && (ty_e > 0))) {
      (void)((e_named = (pipeline_type_kind_ord_at(arena, ty_e) ==ord_named)));
    }
    if ((expr_kind ==ord_ternary)) {
      if (ast_ref_is_null(ty_t)) {
        return -1;
      }
      if (ast_ref_is_null(ty_e)) {
        return -1;
      }
      if (!(typeck_type_refs_equal(arena, ty_t, ty_e))) {
        return -1;
      }
      (void)((resolved = ty_t));
      if (((!(ast_ref_is_null(return_type_ref)) && (return_type_ref > 0)) && (return_type_ref <=((arena)->num_types)))) {
        (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
        (void)((got_kind = pipeline_type_kind_ord_at(arena, ty_t)));
        (typeck_integer_widen_ok_refs(arena, return_type_ref, ty_t) ? ({   (void)((resolved = return_type_ref));
 }) : (typeck_float_widen_ok(expect_kind, got_kind) ? ({   (void)((resolved = return_type_ref));
 }) : (((expect_kind ==ord_u8) && (got_kind ==ord_i32)) ? ({   (void)((then_k = pipeline_expr_kind_ord_at(arena, then_ref)));
  (void)((else_k = pipeline_expr_kind_ord_at(arena, else_ref)));
  (((then_k ==ord_lit) && (else_k ==ord_lit)) ? ({   (void)((tv = pipeline_expr_int_val_at(arena, then_ref)));
  (void)((ev = pipeline_expr_int_val_at(arena, else_ref)));
  (((((tv >=0) && (tv <=255)) && (ev >=0)) && (ev <=255)) ? ({   (void)((resolved = return_type_ref));
  (void)(pipeline_expr_set_resolved_type_ref(arena, then_ref, return_type_ref));
  (void)(pipeline_expr_set_resolved_type_ref(arena, else_ref, return_type_ref));
 }) : 0);
 }) : 0);
 }) : 0)));
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved));
      return 0;
    }
    if ((((!(ast_ref_is_null(ty_t)) && !(ast_ref_is_null(ty_e))) && t_named) && e_named)) {
      (!(typeck_type_refs_equal(arena, ty_t, ty_e)) ? ({   return -1;
 }) : 0);
    }
    if ((!(ast_ref_is_null(ty_t)) && !(ast_ref_is_null(ty_e)))) {
      ((e_named && !(t_named)) ? ({   (void)((resolved = ty_e));
 }) : ({   (void)((resolved = ty_t));
 }));
    } else {
      if (!(ast_ref_is_null(ty_t))) {
        (void)((resolved = ty_t));
      } else {
        if (!(ast_ref_is_null(ty_e))) {
          (void)((resolved = ty_e));
        }
      }
    }
    if ((((ast_ref_is_null(resolved) && !(ast_ref_is_null(return_type_ref))) && (return_type_ref > 0)) && (return_type_ref <=((arena)->num_types)))) {
      (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      ((expect_kind ==ord_named) ? ({   (void)((resolved = return_type_ref));
 }) : 0);
    }
    if (!(ast_ref_is_null(resolved))) {
      if (((!(ast_ref_is_null(return_type_ref)) && (return_type_ref > 0)) && (return_type_ref <=((arena)->num_types)))) {
        (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
        (void)((got_kind = pipeline_type_kind_ord_at(arena, resolved)));
        (typeck_integer_widen_ok_refs(arena, return_type_ref, resolved) ? ({   (void)((resolved = return_type_ref));
 }) : (typeck_float_widen_ok(expect_kind, got_kind) ? ({   (void)((resolved = return_type_ref));
 }) : 0));
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, resolved));
    }
    return 0;
  }
}
int32_t typeck_block_expr_value_ref(struct ast_ASTArena * arena, int32_t block_ref) {
  {
    uint8_t stmt_order_kind_region_c_parser = 5;
    uint8_t stmt_order_kind_region_x_parser = 6;
    int32_t fin_ref = 0;
    int32_t nso = 0;
    uint8_t last_k = 0;
    int32_t ridx = 0;
    int32_t nreg = 0;
    int32_t inner_ref = 0;
    if (((ast_ref_is_null(block_ref) || (block_ref <=0)) || (block_ref > ((arena)->num_blocks)))) {
      return 0;
    }
    (void)((fin_ref = ast_ast_block_final_expr_ref(arena, block_ref)));
    if (!(ast_ref_is_null(fin_ref))) {
      return fin_ref;
    }
    (void)((nso = ast_ast_block_num_stmt_order(arena, block_ref)));
    if ((nso <=0)) {
      return 0;
    }
    (void)((last_k = ast_ast_block_stmt_order_kind(arena, block_ref, (nso - 1))));
    if (((last_k !=stmt_order_kind_region_c_parser) && (last_k !=stmt_order_kind_region_x_parser))) {
      return 0;
    }
    (void)((ridx = ast_ast_block_stmt_order_idx(arena, block_ref, (nso - 1))));
    (void)((nreg = ast_ast_block_num_regions(arena, block_ref)));
    if (((ridx < 0) || (ridx >=nreg))) {
      return 0;
    }
    if ((pipeline_block_region_is_unsafe(arena, block_ref, ridx) ==0)) {
      return 0;
    }
    (void)((inner_ref = ast_ast_block_region_body_ref(arena, block_ref, ridx)));
    return typeck_block_expr_value_ref(arena, inner_ref);
  }
}
int32_t typeck_check_expr_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_assign = 28;
    int32_t block_ref = pipeline_expr_block_ref_at(arena, expr_ref);
    int32_t fin_blk = 0;
    int32_t ty_fin = 0;
    int32_t nes = 0;
    int32_t fst_es = 0;
    int32_t st_kind = 0;
    int32_t rhs_ref = 0;
    int32_t ty_rhs = 0;
    if ((typeck_check_block(module, arena, block_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if ((ast_ref_is_null(block_ref) || (block_ref <=0))) {
      return 0;
    }
    (void)((fin_blk = typeck_block_expr_value_ref(arena, block_ref)));
    if (!(ast_ref_is_null(fin_blk))) {
      (void)((ty_fin = typeck_expr_type_ref(arena, fin_blk)));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_fin));
      return 0;
    }
    (void)((nes = ast_ast_block_num_expr_stmts(arena, block_ref)));
    if ((nes !=1)) {
      return 0;
    }
    (void)((fst_es = pipeline_block_expr_stmt_ref(arena, block_ref, 0)));
    if ((fst_es <=0)) {
      return 0;
    }
    (void)((st_kind = pipeline_expr_kind_ord_at(arena, fst_es)));
    if (((st_kind !=ord_assign) && ((st_kind < 29) || (st_kind > 39)))) {
      return 0;
    }
    (void)((rhs_ref = pipeline_expr_binop_right_ref_at(arena, fst_es)));
    if (ast_ref_is_null(rhs_ref)) {
      return 0;
    }
    (void)((ty_rhs = typeck_expr_type_ref(arena, rhs_ref)));
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ty_rhs));
    return 0;
  }
}
int32_t typeck_check_expr_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_assign = 28;
    int32_t ord_add_assign = 29;
    int32_t ord_sub_assign = 30;
    int32_t ord_lit = 0;
    int32_t ord_var = 3;
    int32_t ord_ternary = 27;
    int32_t ord_add = 4;
    int32_t ord_sub = 5;
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_type_array = 10;
    int32_t ord_field = 44;
    int32_t ord_index = 47;
    int32_t ord_call = 48;
    int32_t ord_expr_array_lit = 46;
    int32_t ord_string_lit = 59;
    int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    int32_t left_ref = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    int32_t right_ref = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    int32_t line = pipeline_expr_line_at(arena, expr_ref);
    int32_t col = pipeline_expr_col_at(arena, expr_ref);
    if ((typeck_check_struct_stack_escape_assign(module, arena, expr_ref, left_ref, right_ref, ctx) !=0)) {
      return -1;
    }
    if ((typeck_check_scope_borrow_assign(module, arena, expr_ref, left_ref, right_ref, ctx) !=0)) {
      return -1;
    }
    int32_t lt = 0;
    int32_t rt = 0;
    int32_t rt_after = 0;
    int32_t rhs_ctx = 0;
    int32_t compound_flag = 1;
    int32_t lt_kind = 0;
    int32_t rhs_kind = 0;
    int32_t lhs_kind = 0;
    int32_t int_val = 0;
    int32_t ev = 0;
    int32_t then_r = 0;
    int32_t else_r = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    int32_t dyn_assign_ok = 0;
    int32_t ptr_compound_offset_ok = 0;
    if ((expr_kind ==ord_assign)) {
      (void)((compound_flag = 0));
    }
    if ((typeck_check_expr(module, arena, left_ref, 0, ctx) !=0)) {
      return -1;
    }
    if ((typeck_check_allocator_region_assign(module, arena, expr_ref, left_ref, ctx) !=0)) {
      return -1;
    }
    (void)(({   int32_t lhs_kind_c = pipeline_expr_kind_ord_at(arena, left_ref);
  ((lhs_kind_c ==ord_var) ? ({   uint8_t vbuf_c[128] = {};
  int32_t vnlen_c = pipeline_expr_var_name_len(arena, left_ref);
  int32_t bind_kind = -1;
  int32_t br_c = 0;
  int32_t bi = 0;
  (((vnlen_c > 0) && (vnlen_c < 128)) ? ({   (void)(pipeline_expr_var_name_into(arena, left_ref, &((vbuf_c)[0])));
  if ((ctx !=0)) {
    (void)((br_c = pipeline_dep_ctx_current_block_ref_at(ctx)));
    ((br_c > 0) ? ({   (void)((bind_kind = pipeline_block_name_binding_kind(arena, br_c, &((vbuf_c)[0]), vnlen_c)));
 }) : 0);
  }
  if ((bind_kind < 0)) {
    (void)((bi = pipeline_module_top_level_name_is_const(module, &((vbuf_c)[0]), vnlen_c)));
    ((bi !=0) ? ({   (void)((bind_kind = 1));
 }) : 0);
  }
  ((bind_kind ==1) ? ({   (void)(driver_diagnostic_typeck_assign_to_const(line, col));
  return -1;
 }) : 0);
 }) : 0);
 }) : 0);
 }));
    (void)((lt = typeck_expr_type_ref(arena, left_ref)));
    (void)((rhs_ctx = return_type_ref));
    if (!(ast_ref_is_null(lt))) {
      (void)((rhs_ctx = lt));
    }
    if ((((compound_flag !=0) && !(ast_ref_is_null(lt))) && ((expr_kind ==ord_add_assign) || (expr_kind ==ord_sub_assign)))) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      ((lt_kind ==ord_ptr) ? ({   (void)((rhs_ctx = 0));
 }) : 0);
    }
    if ((typeck_check_expr(module, arena, right_ref, rhs_ctx, ctx) !=0)) {
      return -1;
    }
    if ((ast_ref_is_null(left_ref) || ast_ref_is_null(right_ref))) {
      return 0;
    }
    if (ast_ref_is_null(lt)) {
      (void)((lt = typeck_expr_type_ref(arena, left_ref)));
    }
    (void)((rt_after = typeck_expr_type_ref(arena, right_ref)));
    if ((!(ast_ref_is_null(lt)) && (lt > 0))) {
      (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      (void)(({   int32_t ord_type_slice = 11;
  (((rhs_kind ==ord_expr_array_lit) && ((lt_kind ==ord_type_array) || (lt_kind ==ord_type_slice))) ? ({   if ((typeck_coerce_array_lit_elem_types_to_decl(module, arena, right_ref, lt) < 0)) {
    return -1;
  }
  (void)((rt_after = typeck_expr_type_ref(arena, right_ref)));
 }) : 0);
 }));
      if (!(typeck_type_refs_equal(arena, lt, rt_after))) {
        ((rhs_kind ==ord_lit) ? ({   (void)(typeck_coerce_init_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
 }) : ({   (void)(typeck_coerce_init_float_lit_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
  (void)(typeck_coerce_init_int_binop_to_decl(arena, right_ref, lt, lt_kind, rhs_kind));
 }));
      }
      (((typeck_expr_is_null_keyword(arena, right_ref) !=0) && (lt_kind !=ord_ptr)) ? ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, lt, eb, 96)));
  (void)((gl = typeck_diag_append_lit(gb, 0, 96, ((uint8_t *)"\x6e\x75\x6c\x6c"), 4)));
  (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
  return -1;
 }) : 0);
    }
    (void)((rt = typeck_expr_type_ref(arena, right_ref)));
    if (((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt))) && !(typeck_type_refs_equal(arena, lt, rt)))) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      int32_t rt_kind_assign = pipeline_type_kind_ord_at(arena, rt);
      (typeck_integer_widen_ok_refs(arena, lt, rt) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
  (void)((rt = lt));
 }) : (typeck_float_widen_ok(lt_kind, rt_kind_assign) ? ({  }) : 0));
    }
    if (((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt))) && !(typeck_type_refs_equal(arena, lt, rt)))) {
      (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
      ((rhs_kind ==ord_ternary) ? ({   (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
  ((lt_kind ==ord_u8) ? ({   (void)((then_r = pipeline_expr_if_then_ref_at(arena, right_ref)));
  (void)((else_r = pipeline_expr_if_else_ref_at(arena, right_ref)));
  (((pipeline_expr_kind_ord_at(arena, then_r) ==ord_lit) && (pipeline_expr_kind_ord_at(arena, else_r) ==ord_lit)) ? ({   (void)((int_val = pipeline_expr_int_val_at(arena, then_r)));
  (void)((ev = pipeline_expr_int_val_at(arena, else_r)));
  (((((int_val >=0) && (int_val <=255)) && (ev >=0)) && (ev <=255)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, then_r, lt));
  (void)(pipeline_expr_set_resolved_type_ref(arena, else_r, lt));
  (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
  (void)((rt = lt));
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
      (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
      if ((rhs_kind ==ord_call)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
        (void)((rt = lt));
      }
      if ((rhs_kind ==ord_string_lit)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
        (void)((rt = lt));
      }
      ((rhs_kind ==ord_field) ? ({   (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
  ((typeck_coerce_init_enum_field_to_decl(module, arena, right_ref, lt, lt_kind, rhs_kind) !=0) ? ({   (void)((rt = typeck_expr_type_ref(arena, right_ref)));
 }) : 0);
 }) : 0);
    }
    if ((ast_ref_is_null(lt) && !(ast_ref_is_null(rt)))) {
      (void)((lhs_kind = pipeline_expr_kind_ord_at(arena, left_ref)));
      ((((lhs_kind ==ord_var) || (lhs_kind ==ord_field)) || (lhs_kind ==ord_index)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, left_ref, rt));
  (void)((lt = rt));
 }) : 0);
    }
    if (((((compound_flag !=0) && !(ast_ref_is_null(lt))) && !(ast_ref_is_null(rt))) && ((expr_kind ==ord_add_assign) || (expr_kind ==ord_sub_assign)))) {
      (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
      ((lt_kind ==ord_ptr) ? ({   int32_t rt_kind_pca = pipeline_type_kind_ord_at(arena, rt);
  ((((((((rt_kind_pca ==ord_i32) || (rt_kind_pca ==ord_usize)) || (rt_kind_pca ==ord_isize)) || (rt_kind_pca ==ord_u8)) || (rt_kind_pca ==ord_u32)) || (rt_kind_pca ==ord_u64)) || (rt_kind_pca ==ord_i64)) ? ({   (void)((ptr_compound_offset_ok = 1));
 }) : ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, lt, eb, 96)));
  (void)((gl = typeck_diag_fmt_type_into(arena, rt, gb, 96)));
  (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
  return -1;
 }));
 }) : 0);
    }
    if ((!(ast_ref_is_null(lt)) && !(ast_ref_is_null(rt)))) {
      if ((pipeline_type_kind_ord_at(arena, lt) ==17)) {
        ((typeck_dyn_rhs_is_null_sentinel(arena, rt, right_ref) !=0) ? ({   (void)((dyn_assign_ok = 1));
 }) : ({   uint8_t trait_nm_asg[64] = {};
  int32_t tnl_asg = pipeline_type_named_name_into(arena, lt, &((trait_nm_asg)[0]));
  (((tnl_asg > 0) && (xlang_skip_impl_concrete_implements_trait_c(((void *)(arena)), rt, &((trait_nm_asg)[0]), tnl_asg) !=0)) ? ({   (void)((dyn_assign_ok = 1));
 }) : 0);
 }));
      }
      /* 10.3.1: TYPE_FN LHS accepts Cap *u8 / TYPE_FN RHS. PLATFORM: SHARED. */
      if ((typeck_fnptr_surface_compat(module, arena, lt, rt, right_ref, 0) != 0)) {
        (void)((dyn_assign_ok = 1));
      }
      if (((!(typeck_type_refs_equal(arena, lt, rt)) && (ptr_compound_offset_ok ==0)) && (dyn_assign_ok ==0))) {
        (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
        int32_t rt_kind_mis = pipeline_type_kind_ord_at(arena, rt);
        ((!(typeck_float_widen_ok(lt_kind, rt_kind_mis)) && (typeck_array_to_slice_ok(arena, rt, lt) ==0)) ? ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, lt, eb, 96)));
  (void)((gl = typeck_diag_fmt_type_into(arena, rt, gb, 96)));
  (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
  return -1;
 }) : 0);
      }
      ((((ptr_compound_offset_ok ==0) && (dyn_assign_ok ==0)) && (typeck_check_slice_region_assign(arena, expr_ref, lt, rt) !=0)) ? ({   return -1;
 }) : 0);
    }
    if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
      (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
      (((rhs_kind ==ord_sub) || (rhs_kind ==ord_add)) ? ({   (void)((lt_kind = pipeline_type_kind_ord_at(arena, lt)));
  ((lt_kind ==ord_usize) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, right_ref, lt));
  (void)((rt = lt));
 }) : 0);
 }) : 0);
    }
    (void)((eb = driver_typeck_diag_scratch_expect()));
    (void)((gb = driver_typeck_diag_scratch_found()));
    if ((ast_ref_is_null(lt) && !(ast_ref_is_null(rt)))) {
      (void)((el = typeck_diag_fmt_type_or_question(arena, lt, eb)));
      (void)((gl = typeck_diag_fmt_type_or_question(arena, rt, gb)));
      (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
      return -1;
    }
    if ((!(ast_ref_is_null(lt)) && ast_ref_is_null(rt))) {
      (void)((el = typeck_diag_fmt_type_or_question(arena, lt, eb)));
      (void)((gl = typeck_diag_fmt_type_or_question(arena, rt, gb)));
      (void)(driver_diagnostic_typeck_assign_mismatch(compound_flag, line, col, eb, el, gb, gl));
      return -1;
    }
    return 0;
  }
}
int32_t typeck_check_expr_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_void = 16;
    int32_t ord_lit = 0;
    int32_t ord_as = 54;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_ptr = 9;
    int32_t op_ref = 0;
    int32_t line = 0;
    int32_t col = 0;
    int32_t rt_kind = 0;
    int32_t op_kind = 0;
    int32_t int_val = 0;
    int32_t as_tgt = 0;
    int32_t got = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    if (ast_ref_is_null(op_ref)) {
      if (!(ast_ref_is_null(return_type_ref))) {
        (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
        if ((rt_kind !=ord_void)) {
          (void)(driver_diagnostic_typeck_ret_fail(1, expr_ref, return_type_ref, 0));
          return -1;
        }
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
      }
      return 0;
    }
    if (!(ast_ref_is_null(return_type_ref))) {
      (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      ((rt_kind ==ord_void) ? ({   (void)((got = typeck_expr_type_ref(arena, op_ref)));
  (void)(driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got));
  return -1;
 }) : 0);
    }
    (void)(typeck_ret_fixup_unresolved_call(module, arena, op_ref, ctx));
    if ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      if (ast_ref_is_null(typeck_expr_type_ref(arena, op_ref))) {
        (void)(typeck_emit_return_unresolved_breadcrumb(arena, op_ref, line, col));
      } else {
        (void)(typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col));
      }
      (void)(driver_diagnostic_typeck_ret_fail(1, op_ref, return_type_ref, 0));
      return -1;
    }
    (void)(typeck_ret_coerce_null_lit_to_expect(arena, op_ref, return_type_ref));
    if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
      int32_t rk_ret = pipeline_type_kind_ord_at(arena, return_type_ref);
      int32_t ok_ret = pipeline_expr_kind_ord_at(arena, op_ref);
      (void)(typeck_coerce_init_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
      (void)(typeck_coerce_init_float_lit_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
      (void)(typeck_coerce_init_int_binop_to_decl(arena, op_ref, return_type_ref, rk_ret, ok_ret));
      if ((typeck_coerce_init_enum_field_to_decl(module, arena, op_ref, return_type_ref, rk_ret, ok_ret) !=0)) {
      }
      (((typeck_expr_is_null_keyword(arena, op_ref) !=0) && (rk_ret !=9)) ? ({   (void)((got = typeck_expr_type_ref(arena, op_ref)));
  (void)(driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got));
  return -1;
 }) : 0);
    }
    if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
      (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
      ((op_kind ==ord_lit) ? ({   (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
  ((typeck_expr_is_null_keyword(arena, op_ref) ==0) ? ({   ((rt_kind ==ord_i64) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
 }) : ({   (void)((int_val = pipeline_expr_int_val_at(arena, op_ref)));
  (((int_val ==0) && (rt_kind ==ord_ptr)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
 }) : ((int_val >=0) ? ({   ((((rt_kind ==ord_usize) || (rt_kind ==ord_u32)) || (rt_kind ==ord_u64)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
 }) : 0);
 }) : 0));
 }));
 }) : ((rt_kind ==ord_ptr) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
 }) : 0));
 }) : 0);
    }
    if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
      int32_t crc_arr = 0;
      (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
      (void)((rt_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
      (void)((crc_arr = typeck_coerce_init_array_vector_lit_to_decl(module, arena, op_ref, return_type_ref, rt_kind, op_kind)));
      ((crc_arr < 0) ? ({   return -1;
 }) : 0);
    }
    if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(return_type_ref)))) {
      (void)((op_kind = pipeline_expr_kind_ord_at(arena, op_ref)));
      ((op_kind ==ord_as) ? ({   (void)((as_tgt = pipeline_expr_as_target_type_ref_at(arena, op_ref)));
  ((!(ast_ref_is_null(as_tgt)) && typeck_type_refs_equal(arena, as_tgt, return_type_ref)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, as_tgt));
 }) : 0);
 }) : 0);
    }
    if ((!(ast_ref_is_null(return_type_ref)) && !(ast_ref_is_null(op_ref)))) {
      int32_t expect_kind = 0;
      int32_t got_kind = 0;
      if ((typeck_check_scope_borrow_return(module, arena, expr_ref, op_ref, return_type_ref, ctx) !=0)) {
        return -1;
      }
      if ((typeck_check_allocator_region_return(arena, expr_ref, return_type_ref) !=0)) {
        return -1;
      }
      if ((pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(arena, expr_ref, return_type_ref, ctx) !=0)) {
        return -1;
      }
      (void)(typeck_ret_coerce_integral_to_expect_i32(arena, op_ref, return_type_ref));
      (void)(typeck_ret_coerce_integral_widen(arena, op_ref, return_type_ref));
      (void)((got = typeck_expr_type_ref(arena, op_ref)));
      if (!(typeck_return_operand_matches(module, arena, op_ref, return_type_ref))) {
        if (((!(ast_ref_is_null(got)) && (got > 0)) && !(ast_ref_is_null(return_type_ref)))) {
          (void)((expect_kind = pipeline_type_kind_ord_at(arena, return_type_ref)));
          (void)((got_kind = pipeline_type_kind_ord_at(arena, got)));
          ((typeck_integer_widen_ok_refs(arena, return_type_ref, got) || typeck_float_widen_ok(expect_kind, got_kind)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, op_ref, return_type_ref));
  if ((typeck_check_return_slice_region(arena, expr_ref, op_ref, return_type_ref) !=0)) {
    return -1;
  }
  return 0;
 }) : 0);
        }
        (void)((eb = driver_typeck_diag_scratch_expect()));
        (void)((gb = driver_typeck_diag_scratch_found()));
        (void)((el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb)));
        (void)((gl = typeck_diag_fmt_type_or_question(arena, got, gb)));
        (void)(driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl));
        (void)(typeck_emit_return_subexpr_breadcrumb(arena, op_ref, line, col));
        (void)(driver_diagnostic_typeck_ret_fail(2, op_ref, return_type_ref, got));
        return -1;
      }
      ((typeck_check_return_slice_region(arena, expr_ref, op_ref, return_type_ref) !=0) ? ({   return -1;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_expr_panic(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t op_ref = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
    if ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if (!(ast_ref_is_null(return_type_ref))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
    }
    return 0;
  }
}
int32_t typeck_check_expr_match_arm(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arm_i, int32_t num_arms, int32_t line, int32_t col) {
  {
    int32_t is_enum = 0;
    int32_t var_ix = 0;
    int32_t arm_res = 0;
    int32_t guard_ref = 0;
    int32_t bool_ty = 0;
    if ((arm_i >=num_arms)) {
      return 0;
    }
    (void)((is_enum = pipeline_expr_match_arm_is_enum_variant(arena, expr_ref, arm_i)));
    if ((is_enum !=0)) {
      (void)((var_ix = pipeline_expr_match_arm_variant_index(arena, expr_ref, arm_i)));
      ((var_ix < 0) ? ({   (void)(driver_diagnostic_typeck_enum_no_variant(line, col));
  return -1;
 }) : 0);
    }
    (void)((guard_ref = pipeline_expr_match_arm_guard_ref(arena, expr_ref, arm_i)));
    if ((!(ast_ref_is_null(guard_ref)) && (guard_ref > 0))) {
      (void)((bool_ty = typeck_ensure_bool_type_ref(arena)));
      ((typeck_check_expr(module, arena, guard_ref, bool_ty, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)((arm_res = pipeline_expr_match_arm_result_ref(arena, expr_ref, arm_i)));
    if ((typeck_check_expr(module, arena, arm_res, return_type_ref, ctx) !=0)) {
      return -1;
    }
    return typeck_check_expr_match_arm(module, arena, expr_ref, return_type_ref, ctx, (arm_i + 1), num_arms, line, col);
  }
}
int32_t typeck_check_expr_match(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t matched_ref = 0;
    int32_t num_arms = 0;
    int32_t arm_i = 0;
    int32_t is_enum = 0;
    int32_t var_ix = 0;
    int32_t arm_res = 0;
    int32_t guard_ref = 0;
    int32_t bool_ty = 0;
    int32_t line = 0;
    int32_t col = 0;
    int32_t matched_ty = 0;
    int32_t saved_subj_ty = 0;
    struct ast_Module * saved_subj_mod = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((matched_ref = pipeline_expr_match_matched_ref_at(arena, expr_ref)));
    (void)((num_arms = pipeline_expr_match_num_arms_at(arena, expr_ref)));
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    if ((typeck_check_expr(module, arena, matched_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    (void)((matched_ty = pipeline_expr_resolved_type_ref(arena, matched_ref)));
    (void)((saved_subj_ty = pipeline_typeck_match_subject_ty_get_c()));
    (void)((saved_subj_mod = pipeline_typeck_match_subject_mod_get_c()));
    (void)(pipeline_typeck_match_set_subject_c(module, matched_ty));
    (void)((arm_i = 0));
    while ((arm_i < num_arms)) {
      (void)((is_enum = pipeline_expr_match_arm_is_enum_variant(arena, expr_ref, arm_i)));
      if ((is_enum !=0)) {
        (void)((var_ix = pipeline_expr_match_arm_variant_index(arena, expr_ref, arm_i)));
        ((var_ix < 0) ? ({   (void)(pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty));
  (void)(driver_diagnostic_typeck_enum_no_variant(line, col));
  return -1;
 }) : 0);
      }
      (void)((guard_ref = pipeline_expr_match_arm_guard_ref(arena, expr_ref, arm_i)));
      if ((!(ast_ref_is_null(guard_ref)) && (guard_ref > 0))) {
        (void)((bool_ty = typeck_ensure_bool_type_ref(arena)));
        ((typeck_check_expr(module, arena, guard_ref, bool_ty, ctx) !=0) ? ({   (void)(pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty));
  return -1;
 }) : 0);
      }
      (void)((arm_res = pipeline_expr_match_arm_result_ref(arena, expr_ref, arm_i)));
      if ((typeck_check_expr(module, arena, arm_res, return_type_ref, ctx) !=0)) {
        (void)(pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty));
        return -1;
      }
      (void)((arm_i = (arm_i + 1)));
    }
    (void)(pipeline_typeck_match_set_subject_c(saved_subj_mod, saved_subj_ty));
    if (!(ast_ref_is_null(return_type_ref))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
    }
    return 0;
  }
}
int32_t typeck_check_expr_try_propagate(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t op_ref = 0;
    int32_t op_ty = 0;
    int32_t enclosing_return_type_ref = 0;
    int32_t func_ix = 0;
    int32_t func_ret = 0;
    int32_t line = 0;
    int32_t col = 0;
    int32_t payload_ty = 0;
    uint8_t rname[128] = {};
    int32_t rlen = 0;
    int32_t si = 0;
    int32_t ord_named = 8;
    int32_t ord_i32 = 0;
    int32_t ord_u8 = 2;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    if ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    (void)((op_ty = typeck_expr_type_ref(arena, op_ref)));
    (void)((enclosing_return_type_ref = return_type_ref));
    (void)((func_ret = 0));
    (void)((func_ix = -1));
    if ((ctx !=0)) {
      (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
    }
    if (((((module !=0) && (ctx !=0)) && (func_ix >=0)) && (func_ix < pipeline_module_num_funcs(module)))) {
      (void)((func_ret = pipeline_module_func_return_type_at(module, func_ix)));
      (!(ast_ref_is_null(func_ret)) ? ({   (void)((enclosing_return_type_ref = func_ret));
 }) : 0);
    }
    if ((ast_ref_is_null(op_ty) || (pipeline_type_kind_ord_at(arena, op_ty) !=ord_named))) {
      (void)(driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col));
      return -1;
    }
    (void)((rlen = pipeline_type_named_name_into(arena, op_ty, &((rname)[0]))));
    if (((((((((rlen < 7) || ((rname)[0] !=82)) || ((rname)[1] !=101)) || ((rname)[2] !=115)) || ((rname)[3] !=117)) || ((rname)[4] !=108)) || ((rname)[5] !=116)) || ((rname)[6] !=95))) {
      (void)(driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col));
      return -1;
    }
    if ((ast_ref_is_null(enclosing_return_type_ref) || (typeck_type_refs_equal(arena, enclosing_return_type_ref, op_ty) ==0))) {
      (void)(driver_diagnostic_typeck_try_propagate_bad_enclosing(line, col));
      return -1;
    }
    (void)((payload_ty = 0));
    if (((((rlen ==10) && ((rname)[7] ==105)) && ((rname)[8] ==51)) && ((rname)[9] ==50))) {
      (void)((payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32)));
    } else {
      if ((((rlen ==9) && ((rname)[7] ==117)) && ((rname)[8] ==56))) {
        (void)((payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_u8)));
      } else {
        (void)((si = 7));
        while ((((si + 1) < rlen) && ((si + 1) < 64))) {
          if ((((((rname)[si] ==105) && ((rname)[(si + 1)] ==51)) && ((si + 2) < rlen)) && ((rname)[(si + 2)] ==50))) {
            (void)((payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32)));
            break;
          }
          if ((((rname)[si] ==117) && ((rname)[(si + 1)] ==56))) {
            (void)((payload_ty = pipeline_type_ensure_by_kind_ord(arena, ord_u8)));
            break;
          }
          (void)((si = (si + 1)));
        }
      }
    }
    if ((payload_ty !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, payload_ty));
    } else {
      if (!(ast_ref_is_null(op_ty))) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, op_ty));
      }
    }
    return 0;
  }
}
int32_t typeck_check_expr_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args) {
  {
    int32_t arg_ref = 0;
    if ((arg_i >=num_args)) {
      return 0;
    }
    (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, arg_i)));
    if ((typeck_check_expr(module, arena, arg_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    return typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, (arg_i + 1), num_args);
  }
}
int32_t typeck_check_expr_call_resolve(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_addr_of = 51;
    int32_t ord_deref = 52;
    int32_t ord_var = 3;
    /* 10.3.1 slice14: INDEX/FIELD Cap/TYPE_FN callees (twin typeck.x). */
    int32_t ord_index = 47;
    int32_t ord_field = 44;
    /* EXPR_CALL / EXPR_METHOD_CALL — TYPE_FN CALL-of-CALL `getf()()` (twin typeck.x). */
    int32_t ord_call = 48;
    int32_t ord_method = 49;
    int32_t minus_one = -1;
    int32_t callee_ref = 0;
    int32_t callee_eff = 0;
    int32_t inner_c = 0;
    int32_t ret_ty = 0;
    int32_t cnml = 0;
    int32_t peel_ko = 0;
    uint8_t cnm[128] = {};
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
    if (ast_ref_is_null(callee_ref)) {
      return 0;
    }
    (void)((callee_eff = callee_ref));
    (void)((peel_ko = pipeline_expr_kind_ord_at(arena, callee_eff)));
    /* Cap (*f)(): peel DEREF/ADDR_OF (10.3.2 slice3). */
    if (((peel_ko ==ord_addr_of) || (peel_ko ==ord_deref))) {
      (void)((inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff)));
      (!(ast_ref_is_null(inner_c)) ? ({   (void)((callee_eff = inner_c));
 }) : 0);
    }
    (void)((cnml = 0));
    if ((pipeline_expr_kind_ord_at(arena, callee_eff) ==ord_var)) {
      (void)((cnml = pipeline_expr_var_name_len(arena, callee_eff)));
      ((cnml > 0) ? ({   (void)(pipeline_expr_var_name_into(arena, callee_eff, &((cnm)[0])));
 }) : 0);
    }
    (void)((ret_ty = typeck_resolve_call_callee_return_type(module, arena, callee_eff, expr_ref, ctx)));
    if (((ret_ty ==0) && (cnml > 0))) {
      (void)(typeck_i32_ptr_store(typeck_call_resolve_func_idx_slot(), 0));
      (void)((ret_ty = typeck_find_func_return_type_in_module_by_name(module, arena, &((cnm)[0]), cnml, minus_one, ctx, typeck_call_resolve_func_idx_slot())));
      ((ret_ty !=0) ? ({   (void)(ast_ast_expr_apply_call_resolve(arena, expr_ref, minus_one, typeck_call_resolve_func_idx_peek()));
 }) : 0);
    }
    if (((cnml > 0) && (pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32(&((cnm)[0]), cnml) !=0))) {
      (void)((ret_ty = pipeline_typeck_read_ptr_slice_return_ref_c_ASTArena_ptr_reti32(arena)));
    }
    if ((((ret_ty ==0) && (cnml > 0)) && (pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32(&((cnm)[0]), cnml) !=0))) {
      int32_t arg_i = 0;
      int32_t arg_ref = 0;
      if ((cnml ==11)) {
        (void)((arg_i = 1));
      }
      ((pipeline_expr_call_num_args_at(arena, expr_ref) > arg_i) ? ({   (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, arg_i)));
  (!(ast_ref_is_null(arg_ref)) ? ({   (void)((ret_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
 }) : 0);
 }) : 0);
    }
    /* Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): stamp ret from TYPE_FN elem or expected/i32.
     * 10.3.1 slice14: also INDEX/FIELD Cap surfaces (twin typeck.x).
     * CALL-of-CALL `getf()()`: callee EXPR_CALL/METHOD_CALL typed TYPE_FN (twin typeck.x). */
    if ((ret_ty ==0)) {
      int32_t ckind = pipeline_expr_kind_ord_at(arena, callee_eff);
      if ((((((ckind ==ord_var) || (ckind ==ord_index)) || (ckind ==ord_field)) || (ckind ==ord_call)) || (ckind ==ord_method))) {
      if ((typeck_check_expr(module, arena, callee_eff, 0, ctx) ==0)) {
        int32_t ctr = pipeline_expr_resolved_type_ref(arena, callee_eff);
        int32_t cko = 0;
        int32_t eer = 0;
        int32_t eko = 0;
        int32_t expect = 0;
        if ((ctr > 0)) {
          (void)((cko = pipeline_type_kind_ord_at(arena, ctr)));
          if ((cko ==18)) {
            (void)((eer = pipeline_type_elem_ref_at(arena, ctr)));
            if ((eer > 0)) {
              (void)((ret_ty = eer));
            } else {
              (void)((expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot())));
              if ((expect > 0)) {
                (void)((ret_ty = expect));
              } else {
                (void)((ret_ty = typeck_ensure_i32_type_ref(arena)));
              }
            }
          } else if ((cko ==9)) {
            (void)((eer = pipeline_type_elem_ref_at(arena, ctr)));
            if ((eer > 0)) {
              (void)((eko = pipeline_type_kind_ord_at(arena, eer)));
              if ((eko ==2)) {
                (void)((expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot())));
                if ((expect > 0)) {
                  (void)((ret_ty = expect));
                } else {
                  (void)((ret_ty = typeck_ensure_i32_type_ref(arena)));
                }
              }
            }
          }
        }
      }
      }
    }
    if ((ret_ty !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
    }
    return 0;
  }
}

/* Cap 10.7.1 slice8: twin of typeck.x typeck_call_arity_compatible.
 * Exact match or variadic with num_args >= named params.
 * PLATFORM: SHARED. G.7 twin. */
int32_t typeck_call_arity_compatible(struct ast_Module * module, int32_t fi, int32_t num_args) {
  {
    int32_t np = 0;
    if (((module ==0) || (fi < 0))) {
      return 0;
    }
    (void)((np = pipeline_module_func_num_params_at(module, fi)));
    if ((np ==num_args)) {
      return 1;
    }
    if (((pipeline_module_func_is_variadic_at(module, fi) !=0) && (num_args >=np))) {
      return 1;
    }
    return 0;
  }
}

int32_t typeck_check_call_arity(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t num_args = 0;
    int32_t fi = 0;
    int32_t dep = 0;
    struct ast_Module * mod = 0;
    struct ast_Module * dm = 0;
    int32_t np = 0;
    int32_t line_a = 0;
    int32_t col_a = 0;
    int32_t callee_ref = 0;
    int32_t callee_eff = 0;
    int32_t ord_addr_of = 51;
    int32_t ord_deref = 52;
    int32_t ord_var = 3;
    int32_t inner_c = 0;
    int32_t peel_ko = 0;
    int32_t cnml = 0;
    uint8_t cnm[128] = {};
    int32_t j = 0;
    int32_t name_hits = 0;
    int32_t arity_hits = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((num_args = pipeline_expr_call_num_args_at(arena, expr_ref)));
    (void)((fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref)));
    (void)((dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref)));
    if ((fi >=0)) {
      (void)((mod = module));
      if (((dep >=0) && (ctx !=0))) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, dep)));
        ((dm !=0) ? ({   (void)((mod = dm));
 }) : 0);
      }
      /* Cap 10.7.1 slice8: exact or variadic. Twin typeck.x. */
      if ((typeck_call_arity_compatible(mod, fi, num_args) ==0)) {
        (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a));
        return -1;
      }
      return 0;
    }
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
    if (ast_ref_is_null(callee_ref)) {
      return 0;
    }
    (void)((callee_eff = callee_ref));
    (void)((peel_ko = pipeline_expr_kind_ord_at(arena, callee_eff)));
    /* Cap (*f)(): peel DEREF/ADDR_OF (10.3.2 slice3). */
    if (((peel_ko ==ord_addr_of) || (peel_ko ==ord_deref))) {
      (void)((inner_c = pipeline_expr_unary_operand_ref_at(arena, callee_eff)));
      (!(ast_ref_is_null(inner_c)) ? ({   (void)((callee_eff = inner_c));
 }) : 0);
    }
    /* 10.3.1 slice14: INDEX/FIELD Cap/TYPE_FN soft (twin typeck.x). */
    {
      int32_t ckind = pipeline_expr_kind_ord_at(arena, callee_eff);
      int32_t ord_index = 47;
      int32_t ord_field = 44;
      if (((ckind ==ord_index) || (ckind ==ord_field))) {
        if ((typeck_check_expr(module, arena, callee_eff, 0, ctx) !=0)) {
          return -1;
        }
        {
          int32_t ctr = pipeline_expr_resolved_type_ref(arena, callee_eff);
          if (((ctr > 0) && (typeck_is_fnptr_surface(arena, ctr) !=0))) {
            return 0;
          }
        }
        return 0;
      }
    }
    if ((pipeline_expr_kind_ord_at(arena, callee_eff) !=ord_var)) {
      return 0;
    }
    (void)((cnml = pipeline_expr_var_name_len(arena, callee_eff)));
    if (((cnml <=0) || (cnml > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, callee_eff, &((cnm)[0])));
    if ((pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32(&((cnm)[0]), cnml) !=0)) {
      return 0;
    }
    if ((pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32(&((cnm)[0]), cnml) !=0)) {
      return 0;
    }
    /* Cap-fn-ptr (10.3.2) / TYPE_FN (10.3.1): soft-skip unresolved name. */
    if ((typeck_check_expr(module, arena, callee_eff, 0, ctx) !=0)) {
      return -1;
    }
    {
      int32_t ctr = pipeline_expr_resolved_type_ref(arena, callee_eff);
      if (((ctr > 0) && (typeck_is_fnptr_surface(arena, ctr) !=0))) {
        return 0;
      }
    }
    (void)((name_hits = 0));
    (void)((arity_hits = 0));
    (void)((j = 0));
    while ((j < ((module)->num_funcs))) {
      if ((pipeline_module_func_name_equal_at(module, j, &((cnm)[0]), cnml) !=0)) {
        (void)((name_hits = (name_hits + 1)));
        /* Cap 10.7.1 slice8: exact or variadic. Twin typeck.x. */
        ((typeck_call_arity_compatible(module, j, num_args) !=0) ? ({   (void)((arity_hits = (arity_hits + 1)));
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    if (((name_hits > 0) && (arity_hits ==0))) {
      (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_call_arity_mismatch(line_a, col_a));
      return -1;
    }
    if ((name_hits ==0)) {
      (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
      (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
      (void)(driver_diagnostic_typeck_call_unresolved(line_a, col_a));
      return -1;
    }
    return 0;
  }
}
int32_t typeck_named_is_module_type(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * name, int32_t name_len) {
  {
    int32_t si = 0;
    int32_t nsl = 0;
    int32_t snlen = 0;
    uint8_t snm[128] = {};
    int32_t n_alias = 0;
    int32_t ai = 0;
    int32_t alen = 0;
    int32_t bi = 0;
    int32_t same = 0;
    if ((((module ==0) || (name ==0)) || (name_len <=0))) {
      return 0;
    }
    if ((arena ==0)) {
    }
    (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
    (void)((si = 0));
    while ((si < nsl)) {
      (void)((snlen = pipeline_module_struct_layout_name_len(module, si)));
      if (((snlen ==name_len) && (snlen > 0))) {
        (void)(pipeline_module_struct_layout_name_into(module, si, &((snm)[0])));
        (typeck_name_equal(&((snm)[0]), snlen, name, name_len) ? ({   return 1;
 }) : 0);
      }
      (void)((si = (si + 1)));
    }
    (void)((n_alias = pipeline_module_num_type_aliases_at(module)));
    (void)((ai = 0));
    while ((ai < n_alias)) {
      (void)((alen = pipeline_module_type_alias_name_len(module, ai)));
      if (((alen ==name_len) && (alen > 0))) {
        (void)((same = 1));
        (void)((bi = 0));
        while ((bi < alen)) {
          if ((pipeline_module_type_alias_name_byte_at(module, ai, bi) !=(name)[bi])) {
            (void)((same = 0));
            break;
          }
          (void)((bi = (bi + 1)));
        }
        ((same !=0) ? ({   return 1;
 }) : 0);
      }
      (void)((ai = (ai + 1)));
    }
    return 0;
  }
}
int32_t typeck_type_is_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    if ((((module ==0) || (arena ==0)) || (ty_ref <=0))) {
      return 0;
    }
    if ((typeck_vector_lanes_of_type(arena, ty_ref) > 0)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, ty_ref) !=8)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, ty_ref, &((nm)[0]))));
    if (((nlen <=0) || (nlen > 127))) {
      return 0;
    }
    if ((typeck_named_is_module_type(module, arena, &((nm)[0]), nlen) !=0)) {
      return 0;
    }
    return 1;
  }
}
int32_t typeck_type_tree_has_free_type_param(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref, int32_t depth) {
  {
    int32_t kind = 0;
    int32_t elem = 0;
    int32_t n_ta = 0;
    int32_t i = 0;
    int32_t ta = 0;
    int32_t asz = 0;
    if (((((module ==0) || (arena ==0)) || (ty_ref <=0)) || (depth > 12))) {
      return 0;
    }
    if ((typeck_type_is_free_type_param(module, arena, ty_ref) !=0)) {
      return 1;
    }
    (void)((kind = pipeline_type_kind_ord_at(arena, ty_ref)));
    if (((((kind ==9) || (kind ==10)) || (kind ==11)) || (kind ==13))) {
      (void)((elem = pipeline_type_elem_ref_at(arena, ty_ref)));
      if ((elem > 0)) {
        return typeck_type_tree_has_free_type_param(module, arena, elem, (depth + 1));
      }
      return 0;
    }
    if ((kind ==8)) {
      (void)((asz = pipeline_type_array_size_at(arena, ty_ref)));
      if (((asz > 0) && (asz <=8))) {
        (void)((n_ta = asz));
      } else {
        (void)((n_ta = 0));
        (void)((i = 0));
        while ((i < 8)) {
          (void)((ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i)));
          if ((ta <=0)) {
            break;
          }
          (void)((n_ta = (i + 1)));
          (void)((i = (i + 1)));
        }
      }
      (void)((i = 0));
      while ((i < n_ta)) {
        (void)((ta = pipeline_type_type_arg_ref_at(arena, ty_ref, i)));
        if (((ta <=0) && (i ==0))) {
          (void)((ta = pipeline_type_elem_ref_at(arena, ty_ref)));
        }
        if (((ta > 0) && (typeck_type_tree_has_free_type_param(module, arena, ta, (depth + 1)) !=0))) {
          return 1;
        }
        (void)((i = (i + 1)));
      }
    }
    return 0;
  }
}
int32_t typeck_generic_formal_matches_arg_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t formal_ty, int32_t arg_ty, int32_t depth) {
  {
    int32_t fk = 0;
    int32_t ak = 0;
    int32_t felem = 0;
    int32_t aelem = 0;
    int32_t fsz = 0;
    int32_t asz = 0;
    uint8_t fnm[128] = {};
    uint8_t anm[128] = {};
    int32_t fnlen = 0;
    int32_t anlen = 0;
    int32_t n_fta = 0;
    int32_t n_ata = 0;
    int32_t i = 0;
    int32_t fta = 0;
    int32_t ata = 0;
    if ((((((module ==0) || (arena ==0)) || (formal_ty <=0)) || (arg_ty <=0)) || (depth > 12))) {
      return 0;
    }
    if ((typeck_type_is_free_type_param(module, arena, formal_ty) !=0)) {
      return 1;
    }
    if ((pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, formal_ty, arg_ty) !=0)) {
      return 1;
    }
    (void)((fk = pipeline_type_kind_ord_at(arena, formal_ty)));
    (void)((ak = pipeline_type_kind_ord_at(arena, arg_ty)));
    if (((fk < 0) || (ak < 0))) {
      return 0;
    }
    if ((fk ==8)) {
      if ((ak !=8)) {
        return 0;
      }
      (void)((fnlen = pipeline_type_named_name_into(arena, formal_ty, &((fnm)[0]))));
      (void)((anlen = pipeline_type_named_name_into(arena, arg_ty, &((anm)[0]))));
      if ((((fnlen <=0) || (anlen <=0)) || !(typeck_name_equal(&((fnm)[0]), fnlen, &((anm)[0]), anlen)))) {
        return 0;
      }
      (void)((asz = pipeline_type_array_size_at(arena, formal_ty)));
      if (((asz > 0) && (asz <=8))) {
        (void)((n_fta = asz));
      } else {
        (void)((n_fta = 0));
        (void)((i = 0));
        while ((i < 8)) {
          if ((pipeline_type_type_arg_ref_at(arena, formal_ty, i) <=0)) {
            break;
          }
          (void)((n_fta = (i + 1)));
          (void)((i = (i + 1)));
        }
      }
      if ((n_fta <=0)) {
        return 1;
      }
      (void)((asz = pipeline_type_array_size_at(arena, arg_ty)));
      if (((asz > 0) && (asz <=8))) {
        (void)((n_ata = asz));
      } else {
        (void)((n_ata = 0));
        (void)((i = 0));
        while ((i < 8)) {
          if ((pipeline_type_type_arg_ref_at(arena, arg_ty, i) <=0)) {
            break;
          }
          (void)((n_ata = (i + 1)));
          (void)((i = (i + 1)));
        }
      }
      if ((n_ata <=0)) {
        (void)((aelem = pipeline_type_elem_ref_at(arena, arg_ty)));
        ((aelem > 0) ? ({   (void)((n_ata = 1));
 }) : 0);
      }
      if ((n_ata < n_fta)) {
        return 0;
      }
      (void)((i = 0));
      while ((i < n_fta)) {
        (void)((fta = pipeline_type_type_arg_ref_at(arena, formal_ty, i)));
        if (((fta <=0) && (i ==0))) {
          (void)((fta = pipeline_type_elem_ref_at(arena, formal_ty)));
        }
        (void)((ata = pipeline_type_type_arg_ref_at(arena, arg_ty, i)));
        if (((ata <=0) && (i ==0))) {
          (void)((ata = pipeline_type_elem_ref_at(arena, arg_ty)));
        }
        if (((fta <=0) || (ata <=0))) {
          return 0;
        }
        if ((typeck_generic_formal_matches_arg_type(module, arena, fta, ata, (depth + 1)) ==0)) {
          return 0;
        }
        (void)((i = (i + 1)));
      }
      return 1;
    }
    if (((((fk ==9) || (fk ==10)) || (fk ==11)) || (fk ==13))) {
      if ((ak !=fk)) {
        return 0;
      }
      (void)((felem = pipeline_type_elem_ref_at(arena, formal_ty)));
      (void)((aelem = pipeline_type_elem_ref_at(arena, arg_ty)));
      if (((felem <=0) || (aelem <=0))) {
        return 0;
      }
      if (((fk ==10) || (fk ==13))) {
        (void)((fsz = pipeline_type_array_size_at(arena, formal_ty)));
        (void)((asz = pipeline_type_array_size_at(arena, arg_ty)));
        ((((fsz > 0) && (asz > 0)) && (fsz !=asz)) ? ({   return 0;
 }) : 0);
      }
      return typeck_generic_formal_matches_arg_type(module, arena, felem, aelem, (depth + 1));
    }
    if ((fk ==ak)) {
      return 1;
    }
    return 0;
  }
}
/* Twin of typeck.x typeck_call_is_fmt_debug_print_any (7.4.9).
 * Product contract: 1-arg std.fmt / std.debug print/println of a composite
 * that misses scalar overloads is JSON "print any" — not T001.
 * L4 g05 compiles this pin (prefer .x hid the gap on daily L2).
 * PLATFORM: SHARED typeck pin. G.7 complete existing gate; no third scorer.
 */
int32_t typeck_call_is_fmt_debug_print_any(struct ast_Module * mod, int32_t fi, int32_t dep,
    struct ast_PipelineDepCtx * ctx, int32_t num_args) {
  int32_t nlen = 0;
  int32_t plen = 0;
  uint8_t print_nm[8];
  uint8_t println_nm[8];
  uint8_t pb[128] = {};
  if (num_args != 1) {
    return 0;
  }
  if ((mod == 0) || (fi < 0)) {
    return 0;
  }
  if ((dep < 0) || (ctx == 0)) {
    return 0;
  }
  nlen = pipeline_module_func_name_len_at(mod, fi);
  if ((nlen != 5) && (nlen != 7)) {
    return 0;
  }
  print_nm[0] = 112; print_nm[1] = 114; print_nm[2] = 105; print_nm[3] = 110; print_nm[4] = 116;
  println_nm[0] = 112; println_nm[1] = 114; println_nm[2] = 105; println_nm[3] = 110;
  println_nm[4] = 116; println_nm[5] = 108; println_nm[6] = 110;
  if (nlen == 5) {
    if (pipeline_module_func_name_equal_at(mod, fi, &(print_nm[0]), 5) == 0) {
      return 0;
    }
  } else {
    if (pipeline_module_func_name_equal_at(mod, fi, &(println_nm[0]), 7) == 0) {
      return 0;
    }
  }
  plen = pipeline_dep_ctx_import_path_len(ctx, dep);
  if ((plen != 7) && (plen != 9)) {
    return 0;
  }
  /* copy64 APIs write 128 bytes (AST name[128]); never a smaller local. */
  pipeline_dep_ctx_import_path_copy64(ctx, dep, &(pb[0]));
  if (plen == 7) {
    if (((pb[0] == 115) && (pb[1] == 116) && (pb[2] == 100) && (pb[3] == 46)
        && (pb[4] == 102) && (pb[5] == 109) && (pb[6] == 116))) {
      return 1;
    }
    return 0;
  }
  if (((pb[0] == 115) && (pb[1] == 116) && (pb[2] == 100) && (pb[3] == 46)
      && (pb[4] == 100) && (pb[5] == 101) && (pb[6] == 98) && (pb[7] == 117)
      && (pb[8] == 103))) {
    return 1;
  }
  return 0;
}
int32_t typeck_check_call_arg_types(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t num_args = 0;
    int32_t fi = 0;
    int32_t dep = 0;
    struct ast_Module * mod = 0;
    struct ast_Module * dm = 0;
    int32_t ai = 0;
    int32_t param_raw = 0;
    int32_t sc = 0;
    int32_t arg_ref = 0;
    int32_t line_a = 0;
    int32_t col_a = 0;
    int32_t n_gp = 0;
    int32_t arg_ty = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((fi = pipeline_expr_call_resolved_func_index_at(arena, expr_ref)));
    if ((fi < 0)) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, expr_ref) ==49)) {
      (void)((num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref)));
    } else {
      (void)((num_args = pipeline_expr_call_num_args_at(arena, expr_ref)));
    }
    (void)((dep = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref)));
    (void)((mod = module));
    if (((dep >=0) && (ctx !=0))) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep)));
      ((dm !=0) ? ({   (void)((mod = dm));
 }) : 0);
    }
    (void)((n_gp = pipeline_module_func_num_generic_params_at(mod, fi)));
    (void)((ai = 0));
    while ((ai < num_args)) {
      (void)((param_raw = pipeline_module_func_param_type_ref_at(mod, fi, ai)));
      if ((param_raw > 0)) {
        if ((pipeline_expr_kind_ord_at(arena, expr_ref) ==49)) {
          (void)((arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, ai)));
        } else {
          (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, ai)));
        }
        if ((((arg_ref > 0) && (typeck_expr_is_null_keyword(arena, arg_ref) !=0)) && (pipeline_type_kind_ord_at(arena, param_raw) !=9))) {
          (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
          (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
          (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
          return -1;
        }
        if (((n_gp > 0) && (typeck_type_is_free_type_param(mod, arena, param_raw) !=0))) {
          if ((arg_ref <=0)) {
            (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
            (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
            (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
            return -1;
          }
          (void)((ai = (ai + 1)));
          continue;
        }
        if (((n_gp > 0) && (arg_ref > 0))) {
          (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
          ((((arg_ty > 0) && (typeck_type_tree_has_free_type_param(mod, arena, param_raw, 0) !=0)) && (typeck_generic_formal_matches_arg_type(mod, arena, param_raw, arg_ty, 0) !=0)) ? ({   (void)((ai = (ai + 1)));
  continue;
 }) : 0);
        }
        if ((arg_ref > 0)) {
          int32_t pty_c = param_raw;
          if ((dep >=0)) {
            int32_t mapped_c = typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(dep, param_raw, arena, ctx);
            ((mapped_c > 0) ? ({   (void)((pty_c = mapped_c));
 }) : 0);
          }
          (void)(typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref, pty_c, pipeline_type_kind_ord_at(arena, pty_c), pipeline_expr_kind_ord_at(arena, arg_ref)));
          (void)(typeck_coerce_init_struct_lit_to_decl(module, arena, arg_ref, pty_c));
          (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, arg_ref, pty_c));
        }
        (void)((sc = typeck_overload_arg_param_score(arena, expr_ref, ai, param_raw, dep, ctx)));
        ((sc < 0) ? ({   if (((arg_ref > 0) && (typeck_call_arg_repr_compatible_ok(mod, arena, param_raw, arg_ref) !=0))) {
    (void)((ai = (ai + 1)));
    continue;
  }
  /* Twin of typeck.x: fmt/debug print/println(composite) JSON any — not T001.
   * PLATFORM: SHARED typeck pin. */
  if ((typeck_call_is_fmt_debug_print_any(mod, fi, dep, ctx, num_args) != 0)) {
    (void)((ai = (ai + 1)));
    continue;
  }
  (void)((line_a = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_a = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line_a, col_a));
  return -1;
 }) : 0);
      }
      (void)((ai = (ai + 1)));
    }
    return 0;
  }
}
int32_t typeck_match_subject_field_type(struct ast_Module * module, struct ast_ASTArena * arena, uint8_t * name, int32_t name_len) {
  {
    int32_t ty = 0;
    struct ast_Module * subj_mod = 0;
    uint8_t tnm[128] = {};
    int32_t tnl = 0;
    int32_t nsl = 0;
    int32_t k = 0;
    int32_t fl = 0;
    int32_t nf = 0;
    int32_t fi = 0;
    int32_t fnl = 0;
    int32_t j = 0;
    int32_t bi = 0;
    int32_t name_eq = 0;
    uint8_t fnm[128] = {};
    if (((((module ==0) || (arena ==0)) || (name ==0)) || (name_len <=0))) {
      return 0;
    }
    (void)((ty = pipeline_typeck_match_subject_ty_get_c()));
    (void)((subj_mod = pipeline_typeck_match_subject_mod_get_c()));
    if (((ty <=0) || (subj_mod !=module))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, ty) !=8)) {
      return 0;
    }
    (void)((tnl = pipeline_type_named_name_into(arena, ty, &((tnm)[0]))));
    if ((tnl <=0)) {
      return 0;
    }
    (void)((nsl = pipeline_module_num_struct_layouts_at(module)));
    (void)((k = 0));
    while ((k < nsl)) {
      (void)((fl = pipeline_module_struct_layout_name_len(module, k)));
      if ((fl ==tnl)) {
        (void)((name_eq = 1));
        (void)((bi = 0));
        while (((bi < fl) && (name_eq !=0))) {
          if ((pipeline_module_struct_layout_name_byte_at(module, k, bi) !=(tnm)[bi])) {
            (void)((name_eq = 0));
          }
          (void)((bi = (bi + 1)));
        }
        ((name_eq !=0) ? ({   (void)((nf = pipeline_module_struct_layout_num_fields(module, k)));
  (void)((fi = 0));
  while ((fi < nf)) {
    (void)((fnl = pipeline_module_struct_layout_field_name_len(module, k, fi)));
    if ((fnl ==name_len)) {
      (void)((j = 0));
      while ((j < 128)) {
        (void)(((fnm)[j] = 0));
        (void)((j = (j + 1)));
      }
      (void)(pipeline_module_struct_layout_field_name_into(module, k, fi, &((fnm)[0])));
      (void)((name_eq = 1));
      (void)((j = 0));
      while (((j < fnl) && (name_eq !=0))) {
        if (((fnm)[j] !=(name)[j])) {
          (void)((name_eq = 0));
        }
        (void)((j = (j + 1)));
      }
      ((name_eq !=0) ? ({   return pipeline_module_struct_layout_field_type_ref(module, k, fi);
 }) : 0);
    }
    (void)((fi = (fi + 1)));
  }
 }) : 0);
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
}
int32_t typeck_call_arg_repr_compatible_ok(struct ast_Module * module, struct ast_ASTArena * arena, int32_t param_ref, int32_t arg_ref) {
  {
    int32_t param_elem = 0;
    int32_t arg_elem = 0;
    int32_t arg_ty = 0;
    int32_t arg_kind = 0;
    int32_t op = 0;
    int32_t la = 0;
    int32_t lb = 0;
    uint8_t * m_u8 = 0;
    uint8_t * a_u8 = 0;
    if (((((module ==0) || (arena ==0)) || (param_ref <=0)) || (arg_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, param_ref) !=9)) {
      return 0;
    }
    (void)((param_elem = pipeline_type_elem_ref_at(arena, param_ref)));
    (void)((m_u8 = ((uint8_t *)(module))));
    (void)((a_u8 = ((uint8_t *)(arena))));
    if (((param_elem <=0) || (typeck_type_is_named_struct_c(m_u8, a_u8, param_elem) ==0))) {
      return 0;
    }
    (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
    (void)((arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref)));
    if (((arg_ty <=0) && (arg_kind ==51))) {
      (void)((op = pipeline_expr_unary_operand_ref_at(arena, arg_ref)));
      ((op > 0) ? ({   (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, op)));
 }) : 0);
    }
    if ((arg_ty <=0)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, arg_ty) ==8)) {
      (void)((arg_elem = arg_ty));
    } else {
      if ((pipeline_type_kind_ord_at(arena, arg_ty) ==9)) {
        (void)((arg_elem = pipeline_type_elem_ref_at(arena, arg_ty)));
      } else {
        return 0;
      }
    }
    if (((arg_elem <=0) || (typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) ==0))) {
      return 0;
    }
    (void)((param_elem = typeck_resolve_type_alias_ref(arena, param_elem)));
    (void)((arg_elem = typeck_resolve_type_alias_ref(arena, arg_elem)));
    if ((param_elem ==arg_elem)) {
      return 1;
    }
    (void)((la = typeck_layout_index_for_named_type_c(m_u8, a_u8, param_elem)));
    (void)((lb = typeck_layout_index_for_named_type_c(m_u8, a_u8, arg_elem)));
    if (((la < 0) || (lb < 0))) {
      return 0;
    }
    if ((la ==lb)) {
      return 1;
    }
    if ((((typeck_struct_layouts_same_shape_c(m_u8, a_u8, la, lb) !=0) && (pipeline_module_struct_layout_repr_compatible_at(module, la) !=0)) && (pipeline_module_struct_layout_repr_compatible_at(module, lb) !=0))) {
      return 1;
    }
    return 0;
  }
}

/* Cap 10.7.1 slice10: twin of typeck.x typeck_is_cap_va_builtin_name.
 * Cap va_* language faces (codegen → xlang_va_*); not libc FFI.
 * PLATFORM: SHARED. G.7 twin. */
int32_t typeck_is_cap_va_builtin_name(uint8_t * name, int32_t name_len) {
  if (((name ==0) || (name_len <=0))) {
    return 0;
  }
  if (((((((((name_len == 8) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 115)) && ((name)[4] == 116)) && ((name)[5] == 97)) && ((name)[6] == 114)) && ((name)[7] == 116)) {
    return 1;
  }
  if (((((((name_len == 6) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 101)) && ((name)[4] == 110)) && ((name)[5] == 100)) {
    return 1;
  }
  /* Cap 10.7.1 slice14: typed va_arg<T>(ap). Twin typeck.x. */
  if (((((((name_len == 6) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 97)) && ((name)[4] == 114)) && ((name)[5] == 103)) {
    return 1;
  }
  if ((((((((name_len == 7) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 99)) && ((name)[4] == 111)) && ((name)[5] == 112)) && ((name)[6] == 121)) {
    return 1;
  }
  if (((((((((((name_len == 10) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 97)) && ((name)[4] == 114)) && ((name)[5] == 103)) && ((name)[6] == 95)) && ((name)[7] == 105)) && ((name)[8] == 51)) && ((name)[9] == 50)) {
    return 1;
  }
  if (((((((((((name_len == 10) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 97)) && ((name)[4] == 114)) && ((name)[5] == 103)) && ((name)[6] == 95)) && ((name)[7] == 105)) && ((name)[8] == 54)) && ((name)[9] == 52)) {
    return 1;
  }
  if (((((((((((name_len == 10) && ((name)[0] == 118)) && ((name)[1] == 97)) && ((name)[2] == 95)) && ((name)[3] == 97)) && ((name)[4] == 114)) && ((name)[5] == 103)) && ((name)[6] == 95)) && ((name)[7] == 112)) && ((name)[8] == 116)) && ((name)[9] == 114)) {
    return 1;
  }
  return 0;
}

int32_t typeck_check_extern_call_unsafe_boundary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t callee_ref = 0;
    int32_t callee_kind = 0;
    int32_t name_len = 0;
    uint8_t name[128] = {};
    int32_t fi = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t * m_u8 = 0;
    if ((typeck_get_allow_legacy_extern_calls() !=0)) {
      return 0;
    }
    if ((pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(ctx) > 0)) {
      return 0;
    }
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
    if ((callee_ref <=0)) {
      return 0;
    }
    (void)((callee_kind = pipeline_expr_kind_ord_at(arena, callee_ref)));
    if ((callee_kind !=3)) {
      return 0;
    }
    (void)((name_len = pipeline_expr_var_name_len(arena, callee_ref)));
    if (((name_len <=0) || (name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, callee_ref, &((name)[0])));
    /* Cap 10.7.1 slice10: Cap va_* exempt. Twin typeck.x. */
    if ((typeck_is_cap_va_builtin_name(&((name)[0]), name_len) !=0)) {
      return 0;
    }
    (void)((m_u8 = ((uint8_t *)(module))));
    (void)((fi = glue_module_func_index_by_name_c(m_u8, &((name)[0]), name_len)));
    if (((fi < 0) || (pipeline_module_func_is_extern_at(module, fi) ==0))) {
      return 0;
    }
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_extern_call_outside_unsafe(line, col));
    return -1;
  }
}
void typeck_expr_diag_line_col(struct ast_ASTArena * arena, int32_t expr_ref, int32_t * line_out, int32_t * col_out) {
  {
    int32_t k = 0;
    int32_t l = 0;
    int32_t c = 0;
    int32_t child = 0;
    if (((line_out ==0) || (col_out ==0))) {
      return;
    }
    if (((arena ==0) || (expr_ref <=0))) {
      (void)((*(line_out) = 0));
      (void)((*(col_out) = 0));
      return;
    }
    (void)((l = pipeline_expr_line_at(arena, expr_ref)));
    (void)((c = pipeline_expr_col_at(arena, expr_ref)));
    (void)((*(line_out) = l));
    (void)((*(col_out) = c));
    if ((l > 0)) {
      return;
    }
    (void)((k = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((glue_expr_kind_is_assign_like_ord(k) !=0)) {
      (void)((child = pipeline_expr_binop_left_ref_at(arena, expr_ref)));
      (void)(typeck_expr_diag_line_col(arena, child, line_out, col_out));
      if ((*(line_out) > 0)) {
        return;
      }
      (void)((child = pipeline_expr_binop_right_ref_at(arena, expr_ref)));
      (void)(typeck_expr_diag_line_col(arena, child, line_out, col_out));
      return;
    }
    (((((k ==51) || (k ==41)) || (k ==22)) || (k ==24)) ? ({   (void)((child = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
  (void)(typeck_expr_diag_line_col(arena, child, line_out, col_out));
 }) : 0);
  }
}
int32_t typeck_slice_region_escape(struct ast_ASTArena * arena, int32_t expect_ref, int32_t src_ref) {
  if ((((arena ==0) || (expect_ref <=0)) || (src_ref <=0))) {
    return 0;
  }
  if ((pipeline_type_kind_ord_at(arena, expect_ref) !=11)) {
    return 0;
  }
  if ((pipeline_type_kind_ord_at(arena, src_ref) !=11)) {
    return 0;
  }
  if (((pipeline_type_region_label_len_at(arena, src_ref) > 0) && (pipeline_type_region_label_len_at(arena, expect_ref) <=0))) {
    return 1;
  }
  return 0;
}
int32_t typeck_slice_region_conflict(struct ast_ASTArena * arena, int32_t expect_ref, int32_t src_ref) {
  {
    int32_t ek = 0;
    int32_t sk = 0;
    uint8_t eb[128] = {};
    uint8_t sb[128] = {};
    if ((((arena ==0) || (expect_ref <=0)) || (src_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, expect_ref) !=11)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, src_ref) !=11)) {
      return 0;
    }
    (void)((ek = pipeline_type_region_label_len_at(arena, expect_ref)));
    (void)((sk = pipeline_type_region_label_len_at(arena, src_ref)));
    if (((ek <=0) || (sk <=0))) {
      return 0;
    }
    if ((pipeline_type_region_label_into(arena, expect_ref, &((eb)[0])) !=ek)) {
      return 0;
    }
    if ((pipeline_type_region_label_into(arena, src_ref, &((sb)[0])) !=sk)) {
      return 0;
    }
    if (typeck_name_equal(&((eb)[0]), ek, &((sb)[0]), sk)) {
      return 0;
    }
    return 1;
  }
}
int32_t typeck_check_slice_region_assign(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref) {
  {
    int32_t line = 0;
    int32_t col = 0;
    uint8_t sb[128] = {};
    uint8_t eb[128] = {};
    int32_t slen = 0;
    int32_t elen = 0;
    uint8_t msg[256] = {};
    int32_t p = 0;
    int32_t z = 0;
    if ((((arena ==0) || (expect_ref <=0)) || (src_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, expect_ref) !=11)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, src_ref) !=11)) {
      return 0;
    }
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    if ((typeck_slice_region_escape(arena, expect_ref, src_ref) !=0)) {
      (void)((slen = pipeline_type_region_label_into(arena, src_ref, &((sb)[0]))));
      if ((slen < 0)) {
        (void)((slen = 0));
      }
      if ((slen > 64)) {
        (void)((slen = 64));
      }
      (void)((z = 0));
      while ((z < 256)) {
        (void)(((msg)[z] = 0));
        (void)((z = (z + 1)));
      }
      (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x73\x6c\x69\x63\x65\x20\x72\x65\x67\x69\x6f\x6e\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x61\x73\x73\x69\x67\x6e\x20\x3c"), 36)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((sb)[0]), slen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e\x20\x73\x6c\x69\x63\x65\x20\x74\x6f\x20\x75\x6e\x62\x6f\x75\x6e\x64\x20\x54\x5b\x5d"), 22)));
      (void)(((msg)[p] = 0));
      (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
      return -1;
    }
    if ((typeck_slice_region_conflict(arena, expect_ref, src_ref) !=0)) {
      (void)((elen = pipeline_type_region_label_into(arena, expect_ref, &((eb)[0]))));
      (void)((slen = pipeline_type_region_label_into(arena, src_ref, &((sb)[0]))));
      if ((elen < 0)) {
        (void)((elen = 0));
      }
      if ((slen < 0)) {
        (void)((slen = 0));
      }
      if ((elen > 64)) {
        (void)((elen = 64));
      }
      if ((slen > 64)) {
        (void)((slen = 64));
      }
      (void)((z = 0));
      while ((z < 256)) {
        (void)(((msg)[z] = 0));
        (void)((z = (z + 1)));
      }
      (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x73\x6c\x69\x63\x65\x20\x72\x65\x67\x69\x6f\x6e\x20\x6d\x69\x73\x6d\x61\x74\x63\x68\x3a\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20\x3c"), 33)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((eb)[0]), elen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e\x2c\x20\x66\x6f\x75\x6e\x64\x20\x3c"), 10)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((sb)[0]), slen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e"), 1)));
      (void)(((msg)[p] = 0));
      (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
      return -1;
    }
    return 0;
  }
}
int32_t typeck_check_return_slice_region(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref) {
  {
    int32_t got_ref = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t sb[128] = {};
    uint8_t eb[128] = {};
    int32_t slen = 0;
    int32_t elen = 0;
    uint8_t msg[256] = {};
    int32_t p = 0;
    int32_t z = 0;
    if ((((arena ==0) || (op_ref <=0)) || (func_return_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, func_return_ref) !=11)) {
      return 0;
    }
    (void)((got_ref = pipeline_expr_resolved_type_ref(arena, op_ref)));
    if (((got_ref <=0) || (pipeline_type_kind_ord_at(arena, got_ref) !=11))) {
      return 0;
    }
    (void)((line = 0));
    (void)((col = 0));
    if ((ret_site_ref > 0)) {
      (void)((line = pipeline_expr_line_at(arena, ret_site_ref)));
      (void)((col = pipeline_expr_col_at(arena, ret_site_ref)));
    }
    if ((typeck_slice_region_escape(arena, func_return_ref, got_ref) !=0)) {
      (void)((slen = pipeline_type_region_label_into(arena, got_ref, &((sb)[0]))));
      if ((slen < 0)) {
        (void)((slen = 0));
      }
      if ((slen > 64)) {
        (void)((slen = 64));
      }
      (void)((z = 0));
      while ((z < 256)) {
        (void)(((msg)[z] = 0));
        (void)((z = (z + 1)));
      }
      (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x73\x6c\x69\x63\x65\x20\x72\x65\x67\x69\x6f\x6e\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x72\x65\x74\x75\x72\x6e\x20\x3c"), 36)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((sb)[0]), slen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e\x20\x73\x6c\x69\x63\x65\x20\x61\x73\x20\x75\x6e\x62\x6f\x75\x6e\x64\x20\x54\x5b\x5d"), 22)));
      (void)(((msg)[p] = 0));
      (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
      return -1;
    }
    if ((typeck_slice_region_conflict(arena, func_return_ref, got_ref) !=0)) {
      (void)((elen = pipeline_type_region_label_into(arena, func_return_ref, &((eb)[0]))));
      (void)((slen = pipeline_type_region_label_into(arena, got_ref, &((sb)[0]))));
      if ((elen < 0)) {
        (void)((elen = 0));
      }
      if ((slen < 0)) {
        (void)((slen = 0));
      }
      if ((elen > 64)) {
        (void)((elen = 64));
      }
      if ((slen > 64)) {
        (void)((slen = 64));
      }
      (void)((z = 0));
      while ((z < 256)) {
        (void)(((msg)[z] = 0));
        (void)((z = (z + 1)));
      }
      (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x73\x6c\x69\x63\x65\x20\x72\x65\x67\x69\x6f\x6e\x20\x6d\x69\x73\x6d\x61\x74\x63\x68\x20\x69\x6e\x20\x72\x65\x74\x75\x72\x6e\x3a\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20\x3c"), 43)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((eb)[0]), elen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e\x2c\x20\x66\x6f\x75\x6e\x64\x20\x3c"), 10)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((sb)[0]), slen)));
      (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e"), 1)));
      (void)(((msg)[p] = 0));
      (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
      return -1;
    }
    return 0;
  }
}
int32_t typeck_ptr_has_stack_local_label(struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    uint8_t lbl[64] = {};
    int32_t n = 0;
    if (((arena ==0) || (ty_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, ty_ref) !=9)) {
      return 0;
    }
    (void)((n = pipeline_type_region_label_len_at(arena, ty_ref)));
    if ((n !=11)) {
      return 0;
    }
    if ((pipeline_type_region_label_into(arena, ty_ref, &((lbl)[0])) !=11)) {
      return 0;
    }
    if (((((((lbl)[0] !=115) || ((lbl)[1] !=116)) || ((lbl)[2] !=97)) || ((lbl)[3] !=99)) || ((lbl)[4] !=107))) {
      return 0;
    }
    if ((((((((lbl)[5] !=95) || ((lbl)[6] !=108)) || ((lbl)[7] !=111)) || ((lbl)[8] !=99)) || ((lbl)[9] !=97)) || ((lbl)[10] !=108))) {
      return 0;
    }
    return 1;
  }
}
int32_t typeck_block_tree_has_var(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen) {
  {
    int32_t nso = 0;
    int32_t i = 0;
    int32_t sk = 0;
    int32_t idx = 0;
    int32_t br = 0;
    int32_t tr = 0;
    int32_t er = 0;
    if (((((arena ==0) || (block_ref <=0)) || (vname ==0)) || (vlen <=0))) {
      return 0;
    }
    if ((pipeline_block_resolve_var_type_ref(arena, block_ref, vname, vlen) > 0)) {
      return 1;
    }
    (void)((nso = ast_ast_block_num_stmt_order(arena, block_ref)));
    (void)((i = 0));
    while ((i < nso)) {
      (void)((sk = ((int32_t)(ast_ast_block_stmt_order_kind(arena, block_ref, i)))));
      (void)((idx = ast_ast_block_stmt_order_idx(arena, block_ref, i)));
      (void)((br = 0));
      if ((((sk ==3) && (idx >=0)) && (idx < ast_ast_block_num_loops(arena, block_ref)))) {
        (void)((br = ast_ast_block_while_body_ref(arena, block_ref, idx)));
      } else {
        if ((((sk ==4) && (idx >=0)) && (idx < ast_ast_block_num_for_loops(arena, block_ref)))) {
          (void)((br = ast_ast_block_for_body_ref(arena, block_ref, idx)));
        } else {
          if ((((sk ==5) && (idx >=0)) && (idx < ast_ast_block_num_if_stmts(arena, block_ref)))) {
            (void)((tr = ast_ast_block_if_then_body_ref(arena, block_ref, idx)));
            (void)((er = ast_ast_block_if_else_body_ref(arena, block_ref, idx)));
            if (((tr > 0) && (typeck_block_tree_has_var(arena, tr, vname, vlen) !=0))) {
              return 1;
            }
            if (((er > 0) && (typeck_block_tree_has_var(arena, er, vname, vlen) !=0))) {
              return 1;
            }
            (void)((i = (i + 1)));
            continue;
          } else {
            if ((((sk ==6) && (idx >=0)) && (idx < ast_ast_block_num_regions(arena, block_ref)))) {
              (void)((br = ast_ast_block_region_body_ref(arena, block_ref, idx)));
            }
          }
        }
      }
      if (((br > 0) && (typeck_block_tree_has_var(arena, br, vname, vlen) !=0))) {
        return 1;
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t typeck_var_is_block_local(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t expr_ref) {
  {
    int32_t vlen = 0;
    uint8_t vbuf[128] = {};
    int32_t func_ix = 0;
    int32_t body_ref = 0;
    int32_t br = 0;
    if (((((module ==0) || (arena ==0)) || (ctx ==0)) || (expr_ref <=0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, expr_ref) !=3)) {
      return 0;
    }
    (void)((vlen = pipeline_expr_var_name_len(arena, expr_ref)));
    if (((vlen <=0) || (vlen > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, expr_ref, &((vbuf)[0])));
    (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
    if (((func_ix >=0) && (pipeline_module_func_param_type_ref_for_name(module, func_ix, &((vbuf)[0]), vlen) > 0))) {
      return 0;
    }
    (void)((br = pipeline_dep_ctx_current_block_ref_at(ctx)));
    if (((br > 0) && (pipeline_block_resolve_var_type_ref(arena, br, &((vbuf)[0]), vlen) > 0))) {
      return 1;
    }
    if ((func_ix >=0)) {
      (void)((body_ref = pipeline_module_func_body_ref_at(module, func_ix)));
      (((body_ref > 0) && (typeck_block_tree_has_var(arena, body_ref, &((vbuf)[0]), vlen) !=0)) ? ({   return 1;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_expr_is_addr_of_block_local(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t expr_ref) {
  {
    int32_t op_ref = 0;
    int32_t ty = 0;
    if (((((module ==0) || (arena ==0)) || (ctx ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((ty = pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if ((typeck_ptr_has_stack_local_label(arena, ty) !=0)) {
      return 1;
    }
    if ((pipeline_expr_kind_ord_at(arena, expr_ref) !=51)) {
      return 0;
    }
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref)));
    if (((op_ref > 0) && (typeck_var_is_block_local(module, arena, ctx, op_ref) !=0))) {
      return 1;
    }
    return 0;
  }
}
int32_t typeck_lval_is_param_ptr_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t func_ix, int32_t left_ref, int32_t dst_pi) {
  {
    int32_t base_ref = 0;
    int32_t param_ty = 0;
    int32_t np = 0;
    int32_t pi = 0;
    if ((((((module ==0) || (arena ==0)) || (left_ref <=0)) || (func_ix < 0)) || (dst_pi < 0))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, left_ref) !=44)) {
      return 0;
    }
    (void)((base_ref = pipeline_expr_field_access_base_ref(arena, left_ref)));
    if ((glue_expr_is_func_param_at_c(arena, module, func_ix, base_ref, dst_pi) !=0)) {
      (void)((param_ty = pipeline_module_func_param_type_ref_at(module, func_ix, dst_pi)));
      if (((param_ty > 0) && (pipeline_type_kind_ord_at(arena, param_ty) ==9))) {
        return 1;
      }
      return 0;
    }
    (void)((np = pipeline_module_func_num_params_at(module, func_ix)));
    (void)((pi = 0));
    while ((pi < np)) {
      if ((glue_expr_is_func_param_at_c(arena, module, func_ix, base_ref, pi) !=0)) {
        (void)((param_ty = pipeline_module_func_param_type_ref_at(module, func_ix, pi)));
        (((param_ty > 0) && (pipeline_type_kind_ord_at(arena, param_ty) ==9)) ? ({   if ((pi ==dst_pi)) {
    return 1;
  }
  return 0;
 }) : 0);
      }
      (void)((pi = (pi + 1)));
    }
    return 0;
  }
}
int32_t typeck_block_is_strict_ancestor(struct ast_ASTArena * arena, int32_t ancestor, int32_t descendant) {
  {
    int32_t cur = 0;
    int32_t depth = 0;
    int32_t p = 0;
    if (((((arena ==0) || (ancestor <=0)) || (descendant <=0)) || (ancestor ==descendant))) {
      return 0;
    }
    (void)((cur = descendant));
    (void)((depth = 0));
    while ((((cur > 0) && (cur <=((arena)->num_blocks))) && (depth < 128))) {
      (void)((p = pipeline_block_parent_block_ref_at(arena, cur)));
      if ((p ==ancestor)) {
        return 1;
      }
      (void)((cur = p));
      (void)((depth = (depth + 1)));
    }
    return 0;
  }
}
int32_t typeck_expr_lval_root_var(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * out, int32_t * out_len) {
  {
    int32_t cur = 0;
    int32_t k = 0;
    int32_t n = 0;
    if (((((arena ==0) || (expr_ref <=0)) || (out ==0)) || (out_len ==0))) {
      return 0;
    }
    (void)((cur = expr_ref));
    while (1) {
      (void)((k = pipeline_expr_kind_ord_at(arena, cur)));
      if ((k ==3)) {
        (void)((n = pipeline_expr_var_name_len(arena, cur)));
        if (((n <=0) || (n > 127))) {
          return 0;
        }
        (void)(pipeline_expr_var_name_into(arena, cur, out));
        (void)((*(out_len) = n));
        return 1;
      }
      if ((k ==44)) {
        (void)((cur = pipeline_expr_field_access_base_ref(arena, cur)));
      } else {
        ((k ==47) ? ({   (void)((cur = pipeline_expr_index_base_ref(arena, cur)));
 }) : ({   return 0;
 }));
      }
      ((cur <=0) ? ({   return 0;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_struct_stack_escape_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t func_ix = 0;
    int32_t np = 0;
    int32_t pi = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[80] = {};
    int32_t p = 0;
    if ((((((module ==0) || (arena ==0)) || (ctx ==0)) || (left_ref <=0)) || (right_ref <=0))) {
      return 0;
    }
    if ((pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(ctx) > 0)) {
      return 0;
    }
    if ((typeck_expr_is_addr_of_block_local(module, arena, ctx, right_ref) ==0)) {
      return 0;
    }
    (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
    if ((func_ix < 0)) {
      return 0;
    }
    (void)((np = pipeline_module_func_num_params_at(module, func_ix)));
    (void)((pi = 0));
    while ((pi < np)) {
      if ((typeck_lval_is_param_ptr_field(module, arena, func_ix, left_ref, pi) !=0)) {
        (void)((line = 0));
        (void)((col = 0));
        if (((site_expr_ref > 0) && (site_expr_ref <=((arena)->num_exprs)))) {
          (void)((line = pipeline_expr_line_at(arena, site_expr_ref)));
          (void)((col = pipeline_expr_col_at(arena, site_expr_ref)));
        }
        (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 79, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x73\x74\x61\x63\x6b\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x73\x74\x6f\x72\x65\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x6c\x6f\x63\x61\x6c\x20\x73\x74\x72\x75\x63\x74\x20\x69\x6e\x20\x6f\x75\x74"), 73)));
        (void)(((msg)[p] = 0));
        (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
        return -1;
      }
      (void)((pi = (pi + 1)));
    }
    return 0;
  }
}
int32_t typeck_check_scope_borrow_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx) {
  {
    uint8_t lname[128] = {};
    uint8_t rname[128] = {};
    int32_t llen = 0;
    int32_t rlen = 0;
    int32_t op_ref = 0;
    int32_t site_block = 0;
    int32_t lblock = 0;
    int32_t rblock = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[24] = {};
    int32_t p = 0;
    int32_t cfi = 0;
    if ((((((module ==0) || (arena ==0)) || (ctx ==0)) || (left_ref <=0)) || (right_ref <=0))) {
      return 0;
    }
    if ((typeck_expr_is_addr_of_block_local(module, arena, ctx, right_ref) ==0)) {
      return 0;
    }
    if ((typeck_expr_lval_root_var(arena, left_ref, &((lname)[0]), &(llen)) ==0)) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, right_ref) !=51)) {
      return 0;
    }
    (void)((op_ref = pipeline_expr_unary_operand_ref_at(arena, right_ref)));
    if (((op_ref <=0) || (pipeline_expr_kind_ord_at(arena, op_ref) !=3))) {
      return 0;
    }
    (void)((rlen = pipeline_expr_var_name_len(arena, op_ref)));
    if (((rlen <=0) || (rlen > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, op_ref, &((rname)[0])));
    (void)((site_block = pipeline_dep_ctx_current_block_ref_at(ctx)));
    if ((site_block <=0)) {
      (void)((cfi = pipeline_dep_ctx_current_func_index(ctx)));
      ((cfi >=0) ? ({   (void)((site_block = pipeline_module_func_body_ref_at(module, cfi)));
 }) : 0);
    }
    if ((site_block <=0)) {
      return 0;
    }
    (void)((lblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &((lname)[0]), llen)));
    (void)((rblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &((rname)[0]), rlen)));
    if ((((lblock <=0) || (rblock <=0)) || (lblock ==rblock))) {
      return 0;
    }
    if ((typeck_block_is_strict_ancestor(arena, lblock, rblock) ==0)) {
      return 0;
    }
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 23, ((uint8_t *)"\x73\x63\x6f\x70\x65\x20\x62\x6f\x72\x72\x6f\x77\x20\x65\x73\x63\x61\x70\x65"), 19)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_check_scope_borrow_return(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t op_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[24] = {};
    int32_t p = 0;
    if ((((((module ==0) || (arena ==0)) || (ctx ==0)) || (site_expr_ref <=0)) || (op_ref <=0))) {
      return 0;
    }
    if (((return_type_ref <=0) || (pipeline_type_kind_ord_at(arena, return_type_ref) !=9))) {
      return 0;
    }
    if ((typeck_expr_is_addr_of_block_local(module, arena, ctx, op_ref) ==0)) {
      return 0;
    }
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 23, ((uint8_t *)"\x73\x63\x6f\x70\x65\x20\x62\x6f\x72\x72\x6f\x77\x20\x65\x73\x63\x61\x70\x65"), 19)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_type_is_allocator_struct(struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    int32_t off = 0;
    if (((arena ==0) || (ty_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, ty_ref) !=8)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, ty_ref, &((nm)[0]))));
    if (typeck_name_equal(&((nm)[0]), nlen, ((uint8_t *)(((uint8_t *)"\x41\x6c\x6c\x6f\x63\x61\x74\x6f\x72"))), 9)) {
      return 1;
    }
    if ((nlen > 10)) {
      (void)((off = (nlen - 9)));
      (((nm)[(off - 1)] ==46) ? ({   (typeck_name_equal(&((nm)[off]), 9, ((uint8_t *)(((uint8_t *)"\x41\x6c\x6c\x6f\x63\x61\x74\x6f\x72"))), 9) ? ({   return 1;
 }) : 0);
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_allocator_region_assign(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx) {
  {
    uint8_t lname[128] = {};
    int32_t llen = 0;
    int32_t wa_body = 0;
    int32_t site_block = 0;
    int32_t lblock = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[28] = {};
    int32_t p = 0;
    int32_t i = 0;
    int32_t nl = 0;
    int32_t nlen = 0;
    int32_t lhs_ty = 0;
    int32_t right_ref = 0;
    int32_t rhs_kind = 0;
    uint8_t nm[64] = {};
    if (((((module ==0) || (arena ==0)) || (ctx ==0)) || (left_ref <=0))) {
      return 0;
    }
    if ((pipeline_typeck_with_arena_scope_n_at() <=0)) {
      return 0;
    }
    if ((typeck_expr_lval_root_var(arena, left_ref, &((lname)[0]), &(llen)) ==0)) {
      return 0;
    }
    (void)((wa_body = pipeline_typeck_with_arena_current_body_ref_c()));
    if ((wa_body <=0)) {
      return 0;
    }
    (void)((site_block = pipeline_dep_ctx_current_block_ref_at(ctx)));
    if ((site_block <=0)) {
      (void)((site_block = wa_body));
    }
    (void)((lblock = pipeline_block_find_var_decl_block_ref(arena, site_block, &((lname)[0]), llen)));
    if ((lblock <=0)) {
      return 0;
    }
    if (((lblock ==wa_body) || (typeck_block_is_strict_ancestor(arena, wa_body, lblock) !=0))) {
      return 0;
    }
    if ((typeck_block_is_strict_ancestor(arena, lblock, wa_body) ==0)) {
      return 0;
    }
    (void)((right_ref = pipeline_expr_binop_right_ref_at(arena, site_expr_ref)));
    if ((right_ref > 0)) {
      (void)((rhs_kind = pipeline_expr_kind_ord_at(arena, right_ref)));
      ((rhs_kind ==0) ? ({   return 0;
 }) : 0);
    }
    (void)((lhs_ty = pipeline_expr_resolved_type_ref(arena, left_ref)));
    if ((lhs_ty <=0)) {
      (void)((nl = ast_ast_block_num_lets(arena, lblock)));
      (void)((i = 0));
      while ((i < nl)) {
        (void)((nlen = pipeline_block_let_name_len(arena, lblock, i)));
        if ((((nlen ==llen) && (nlen > 0)) && (nlen < 64))) {
          (void)(pipeline_block_let_name_copy64(arena, lblock, i, &((nm)[0])));
          (typeck_name_equal(&((nm)[0]), nlen, &((lname)[0]), llen) ? ({   (void)((lhs_ty = pipeline_block_let_type_ref(arena, lblock, i)));
  (void)((i = nl));
 }) : 0);
        }
        (void)((i = (i + 1)));
      }
    }
    if (((lhs_ty > 0) && (typeck_type_is_allocator_struct(arena, lhs_ty) ==0))) {
      return 0;
    }
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 27, ((uint8_t *)"\x61\x6c\x6c\x6f\x63\x61\x74\x6f\x72\x20\x72\x65\x67\x69\x6f\x6e\x20\x65\x73\x63\x61\x70\x65"), 24)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_check_allocator_region_return(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref) {
  {
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[28] = {};
    int32_t p = 0;
    if (((arena ==0) || (site_expr_ref <=0))) {
      return 0;
    }
    if ((pipeline_typeck_with_arena_scope_n_at() <=0)) {
      return 0;
    }
    if ((typeck_type_is_allocator_struct(arena, return_type_ref) ==0)) {
      return 0;
    }
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 27, ((uint8_t *)"\x61\x6c\x6c\x6f\x63\x61\x74\x6f\x72\x20\x72\x65\x67\x69\x6f\x6e\x20\x65\x73\x63\x61\x70\x65"), 24)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_check_call_ptr_struct_compat(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t param_ref, int32_t arg_ref) {
  {
    int32_t line = 0;
    int32_t col = 0;
    int32_t param_elem = 0;
    int32_t arg_ty = 0;
    int32_t arg_kind = 0;
    int32_t arg_elem = 0;
    int32_t op = 0;
    uint8_t * m_u8 = 0;
    uint8_t * a_u8 = 0;
    uint8_t msg[64] = {};
    int32_t p = 0;
    if (((((module ==0) || (arena ==0)) || (param_ref <=0)) || (arg_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, param_ref) !=9)) {
      return 0;
    }
    (void)((param_elem = pipeline_type_elem_ref_at(arena, param_ref)));
    (void)((m_u8 = ((uint8_t *)(module))));
    (void)((a_u8 = ((uint8_t *)(arena))));
    if (((param_elem <=0) || (typeck_type_is_named_struct_c(m_u8, a_u8, param_elem) ==0))) {
      return 0;
    }
    (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
    (void)((arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref)));
    if (((arg_ty <=0) && (arg_kind ==51))) {
      (void)((op = pipeline_expr_unary_operand_ref_at(arena, arg_ref)));
      ((op > 0) ? ({   (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, op)));
 }) : 0);
    }
    if ((arg_ty <=0)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, arg_ty) ==8)) {
      (void)((arg_elem = arg_ty));
    } else {
      if ((pipeline_type_kind_ord_at(arena, arg_ty) ==9)) {
        (void)((arg_elem = pipeline_type_elem_ref_at(arena, arg_ty)));
      } else {
        return 0;
      }
    }
    if (((arg_elem <=0) || (typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) ==0))) {
      return 0;
    }
    if ((typeck_call_arg_repr_compatible_ok(module, arena, param_ref, arg_ref) !=0)) {
      return 0;
    }
    (void)((line = pipeline_expr_line_at(arena, call_expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, call_expr_ref)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 63, ((uint8_t *)"\x6e\x6f\x20\x6d\x61\x74\x63\x68\x69\x6e\x67\x20\x6f\x76\x65\x72\x6c\x6f\x61\x64\x20\x28\x69\x6e\x63\x6f\x6d\x70\x61\x74\x69\x62\x6c\x65\x20\x73\x74\x72\x75\x63\x74\x20\x70\x6f\x69\x6e\x74\x65\x72\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x29"), 56)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_check_call_slice_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t func_ix = 0;
    int32_t dep_ix = 0;
    int32_t num_args = 0;
    int32_t np = 0;
    int32_t i = 0;
    int32_t arg_ref = 0;
    int32_t param_ref = 0;
    int32_t arg_ty = 0;
    int32_t arg_kind = 0;
    int32_t param_kind = 0;
    struct ast_Module * callee_mod = 0;
    struct ast_Module * dm = 0;
    uint8_t * m_u8 = 0;
    uint8_t * a_u8 = 0;
    uint8_t * skip_env = 0;
    int32_t src_i = 0;
    int32_t dst_j = 0;
    int32_t stack_arg = 0;
    int32_t stack_arg_ty = 0;
    int32_t stack_arg_elem = 0;
    int32_t param_ref2 = 0;
    int32_t elem_ref = 0;
    int32_t other_arg = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t msg[96] = {};
    int32_t p = 0;
    if ((((module ==0) || (arena ==0)) || (call_expr_ref <=0))) {
      return 0;
    }
    if ((typeck_check_extern_call_unsafe_boundary(module, arena, call_expr_ref, ctx) !=0)) {
      return -1;
    }
    (void)((func_ix = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref)));
    (void)((dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref)));
    if ((func_ix < 0)) {
      (void)((m_u8 = ((uint8_t *)(module))));
      (void)((a_u8 = ((uint8_t *)(arena))));
      (void)((func_ix = pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32(m_u8, a_u8, call_expr_ref)));
    }
    if ((func_ix < 0)) {
      return 0;
    }
    (void)((callee_mod = module));
    if (((dep_ix >=0) && (ctx !=0))) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_ix)));
      ((dm !=0) ? ({   (void)((callee_mod = dm));
 }) : 0);
    }
    (void)((num_args = pipeline_expr_call_num_args_at(arena, call_expr_ref)));
    (void)((np = pipeline_module_func_num_params_at(callee_mod, func_ix)));
    if ((num_args !=np)) {
      return 0;
    }
    (void)(typeck_stamp_resolved_args_float_lit(arena, call_expr_ref, callee_mod, func_ix, dep_ix, ctx, 0));
    (void)((i = 0));
    while ((i < num_args)) {
      (void)((arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, i)));
      (void)((param_ref = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i)));
      if (((arg_ref > 0) && (param_ref > 0))) {
        (void)((arg_kind = pipeline_expr_kind_ord_at(arena, arg_ref)));
        (void)((param_kind = pipeline_type_kind_ord_at(arena, param_ref)));
        (void)(typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref, param_ref, param_kind, arg_kind));
      }
      (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
      if ((typeck_check_slice_region_assign(arena, arg_ref, param_ref, arg_ty) !=0)) {
        return -1;
      }
      if ((typeck_check_call_ptr_struct_compat(module, arena, call_expr_ref, param_ref, arg_ref) !=0)) {
        return -1;
      }
      (void)((i = (i + 1)));
    }
    if (((ctx !=0) && (num_args >=2))) {
      (void)((skip_env = link_abi_getenv(((uint8_t *)(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x53\x4b\x49\x50\x5f\x53\x54\x41\x43\x4b\x5f\x45\x53\x43\x41\x50\x45"))))));
      (((skip_env ==0) && (pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(ctx) <=0)) ? ({   (void)((src_i = 0));
  while ((src_i < num_args)) {
    (void)((stack_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, src_i)));
    if ((typeck_expr_is_addr_of_block_local(module, arena, ctx, stack_arg) !=0)) {
      (void)((stack_arg_ty = pipeline_expr_resolved_type_ref(arena, stack_arg)));
      (((stack_arg_ty > 0) && (pipeline_type_kind_ord_at(arena, stack_arg_ty) ==9)) ? ({   (void)((stack_arg_elem = pipeline_type_elem_ref_at(arena, stack_arg_ty)));
  (void)((m_u8 = ((uint8_t *)(module))));
  (void)((a_u8 = ((uint8_t *)(arena))));
  (((stack_arg_elem > 0) && (typeck_type_is_named_struct_c(m_u8, a_u8, stack_arg_elem) !=0)) ? ({   (void)((dst_j = 0));
  while ((dst_j < num_args)) {
    if ((dst_j !=src_i)) {
      (void)((param_ref2 = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, dst_j)));
      (((param_ref2 > 0) && (pipeline_type_kind_ord_at(arena, param_ref2) ==9)) ? ({   (void)((elem_ref = pipeline_type_elem_ref_at(arena, param_ref2)));
  (((elem_ref > 0) && (typeck_type_is_named_struct_c(m_u8, a_u8, elem_ref) !=0)) ? ({   (void)((other_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, dst_j)));
  ((typeck_expr_is_addr_of_block_local(module, arena, ctx, other_arg) ==0) ? ({   (void)((line = pipeline_expr_line_at(arena, call_expr_ref)));
  (void)((col = pipeline_expr_col_at(arena, call_expr_ref)));
  (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 95, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x73\x74\x61\x63\x6b\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x70\x61\x73\x73\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x6c\x6f\x63\x61\x6c\x20\x73\x74\x72\x75\x63\x74\x20\x77\x69\x74\x68\x20\x6f\x75"), 78)));
  (void)(((msg)[p] = 0));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
  return -1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    (void)((dst_j = (dst_j + 1)));
  }
 }) : 0);
 }) : 0);
    }
    (void)((src_i = (src_i + 1)));
  }
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_expr_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t num_args = 0;
    int32_t expect_store = 0;
    int32_t callee_ref = 0;
    int32_t ret_ty = 0;
    if ((typeck_check_extern_call_unsafe_boundary(module, arena, expr_ref, ctx) !=0)) {
      return -1;
    }
    (void)((num_args = pipeline_expr_call_num_args_at(arena, expr_ref)));
    (void)((expect_store = 0));
    if ((!(ast_ref_is_null(return_type_ref)) && (return_type_ref > 0))) {
      (void)((expect_store = return_type_ref));
    }
    (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), expect_store));
    if ((typeck_check_expr_call_arg(module, arena, expr_ref, return_type_ref, ctx, 0, num_args) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if ((typeck_check_expr_call_resolve(module, arena, expr_ref, ctx) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if ((typeck_check_call_arity(module, arena, expr_ref, ctx) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if ((typeck_check_call_arg_types(module, arena, expr_ref, ctx) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if ((pipeline_typeck_check_call_generic_type_args_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(module, arena, expr_ref, ctx, expect_store) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if ((typeck_check_call_slice_region(module, arena, expr_ref, ctx) !=0)) {
      (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
      return -1;
    }
    if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, expr_ref)));
      (void)((ret_ty = typeck_resolve_call_callee_return_type(module, arena, callee_ref, expr_ref, ctx)));
      ((ret_ty !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
 }) : 0);
    }
    (void)(glue_generic_call_fixup_resolved_type_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(module, arena, expr_ref, ctx, expect_store));
    (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
    return 0;
  }
}
int32_t typeck_type_is_aggregate_cmp_operand(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    int32_t ord_named = 8;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_linear = 12;
    int32_t ord_vector = 13;
    int32_t ko = 0;
    int32_t rty = 0;
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    int32_t nlayouts = 0;
    int32_t k = 0;
    if ((((module ==0) || (arena ==0)) || ast_ref_is_null(ty_ref))) {
      return 0;
    }
    (void)((rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0)));
    if (ast_ref_is_null(rty)) {
      (void)((rty = ty_ref));
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, rty)));
    if (((((ko ==ord_array) || (ko ==ord_slice)) || (ko ==ord_linear)) || (ko ==ord_vector))) {
      return 1;
    }
    if ((ko !=ord_named)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, rty, &((nm)[0]))));
    if (((nlen <=0) || (nlen > 127))) {
      return 0;
    }
    (void)((nlayouts = pipeline_module_num_struct_layouts_at(module)));
    (void)((k = 0));
    while ((k < nlayouts)) {
      if (typeck_layout_name_equal(module, k, &((nm)[0]), nlen)) {
        return 1;
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
}
int32_t typeck_check_expr_binop_cmp(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t bop_l = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    int32_t bop_r = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    int32_t bt = 0;
    int32_t lt_cmp = 0;
    int32_t rt_cmp = 0;
    int32_t lko_cmp = 0;
    int32_t rko_cmp = 0;
    int32_t lk_cmp = 0;
    int32_t rk_cmp = 0;
    int32_t ord_lit = 0;
    int32_t ord_f32 = 14;
    int32_t ord_logand = 20;
    int32_t ord_logor = 21;
    int32_t expr_kind_cmp = 0;
    int32_t line_ac = 0;
    int32_t col_ac = 0;
    int32_t is_logical = 0;
    if ((typeck_check_expr(module, arena, bop_l, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if ((typeck_check_expr(module, arena, bop_r, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if (((typeck_expr_is_null_keyword(arena, bop_l) !=0) && (typeck_expr_is_null_keyword(arena, bop_r) ==0))) {
      (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
      (void)((rko_cmp = 0));
      if ((rt_cmp > 0)) {
        (void)((rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp)));
      }
      (((rt_cmp > 0) && (rko_cmp !=9)) ? ({   (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac));
  return -1;
 }) : 0);
    } else {
      if (((typeck_expr_is_null_keyword(arena, bop_r) !=0) && (typeck_expr_is_null_keyword(arena, bop_l) ==0))) {
        (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
        (void)((lko_cmp = 0));
        if ((lt_cmp > 0)) {
          (void)((lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp)));
        }
        (((lt_cmp > 0) && (lko_cmp !=9)) ? ({   (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac));
  return -1;
 }) : 0);
      }
    }
    (void)((expr_kind_cmp = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if (((expr_kind_cmp ==ord_logand) || (expr_kind_cmp ==ord_logor))) {
      (void)((is_logical = 1));
    }
    (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
    (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
    if ((is_logical !=0)) {
      if (((!(ast_ref_is_null(lt_cmp)) && (lt_cmp > 0)) && (lt_cmp <=((arena)->num_types)))) {
        (!(typeck_type_ref_is_bool(arena, lt_cmp)) ? ({   (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac));
  return -1;
 }) : 0);
      }
      if (((!(ast_ref_is_null(rt_cmp)) && (rt_cmp > 0)) && (rt_cmp <=((arena)->num_types)))) {
        (!(typeck_type_ref_is_bool(arena, rt_cmp)) ? ({   (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_ac, col_ac));
  return -1;
 }) : 0);
      }
      (void)((bt = typeck_ensure_bool_type_ref(arena)));
      if ((bt !=0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
      }
      return 0;
    }
    if ((!(ast_ref_is_null(lt_cmp)) && !(ast_ref_is_null(rt_cmp)))) {
      (void)((lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp)));
      (void)((rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp)));
      (void)((lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l)));
      (void)((rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r)));
      if ((lko_cmp ==ord_f32)) {
        (void)(typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_cmp, ord_f32, rk_cmp));
      } else {
        if ((rko_cmp ==ord_f32)) {
          (void)(typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_cmp, ord_f32, lk_cmp));
        }
      }
      if (((typeck_type_is_aggregate_cmp_operand(module, arena, lt_cmp) !=0) || (typeck_type_is_aggregate_cmp_operand(module, arena, rt_cmp) !=0))) {
        (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_ac, col_ac));
        return -1;
      }
      (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
      (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
      ((!(ast_ref_is_null(lt_cmp)) && !(ast_ref_is_null(rt_cmp))) ? ({   (void)((lko_cmp = pipeline_type_kind_ord_at(arena, lt_cmp)));
  (void)((rko_cmp = pipeline_type_kind_ord_at(arena, rt_cmp)));
  (void)((lk_cmp = pipeline_expr_kind_ord_at(arena, bop_l)));
  (void)((rk_cmp = pipeline_expr_kind_ord_at(arena, bop_r)));
  if (((rk_cmp ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_r, lt_cmp, lko_cmp, rk_cmp) !=0))) {
    (void)((rt_cmp = pipeline_expr_resolved_type_ref(arena, bop_r)));
  } else {
    if (((lk_cmp ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_l, rt_cmp, rko_cmp, lk_cmp) !=0))) {
      (void)((lt_cmp = pipeline_expr_resolved_type_ref(arena, bop_l)));
    }
  }
  (((((lt_cmp > 0) && (rt_cmp > 0)) && (lt_cmp <=((arena)->num_types))) && (rt_cmp <=((arena)->num_types))) ? ({   (!(typeck_type_refs_equal(arena, lt_cmp, rt_cmp)) ? ({   (void)((line_ac = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_ac = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_comparison_type_mismatch(line_ac, col_ac));
  return -1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    (void)((bt = typeck_ensure_bool_type_ref(arena)));
    if ((bt !=0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
    }
    return 0;
  }
}
int32_t typeck_check_expr_binop_arith(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_lit = 0;
    int32_t bop_l = pipeline_expr_binop_left_ref_at(arena, expr_ref);
    int32_t bop_r = pipeline_expr_binop_right_ref_at(arena, expr_ref);
    int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    int32_t lk_expr = 0;
    int32_t rk_expr = 0;
    int32_t lt_ar = 0;
    int32_t rt_ar = 0;
    int32_t lko = 0;
    int32_t rko = 0;
    int32_t out_ar = 0;
    int32_t allow_i32_fallback = 0;
    uint8_t * dbg_left = 0;
    uint8_t * dbg_right = 0;
    int32_t dbg_left_len = 0;
    int32_t dbg_right_len = 0;
    int32_t ord_type_vector = 13;
    int32_t ord_i64 = 5;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_void = 16;
    int32_t ord_bool = 1;
    int32_t ord_i32 = 0;
    int32_t ord_ptr = 9;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_add = 4;
    int32_t ord_sub = 5;
    int32_t ord_mod = 8;
    int32_t ord_shl = 9;
    int32_t ord_shr = 10;
    int32_t ord_bitand = 11;
    int32_t ord_bitor = 12;
    int32_t ord_bitxor = 13;
    if ((typeck_check_expr(module, arena, bop_l, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if ((typeck_check_expr(module, arena, bop_r, return_type_ref, ctx) !=0)) {
      return -1;
    }
    (void)((lt_ar = pipeline_expr_resolved_type_ref(arena, bop_l)));
    (void)((rt_ar = pipeline_expr_resolved_type_ref(arena, bop_r)));
    if ((!(ast_ref_is_null(lt_ar)) && !(ast_ref_is_null(rt_ar)))) {
      (void)((lk_expr = pipeline_expr_kind_ord_at(arena, bop_l)));
      (void)((rk_expr = pipeline_expr_kind_ord_at(arena, bop_r)));
      (void)((dbg_left = driver_typeck_diag_scratch_expect()));
      (void)((dbg_right = driver_typeck_diag_scratch_found()));
      (void)((dbg_left_len = typeck_diag_fmt_type_or_question(arena, lt_ar, dbg_left)));
      (void)((dbg_right_len = typeck_diag_fmt_type_or_question(arena, rt_ar, dbg_right)));
      (void)(driver_diagnostic_typeck_binop_operands(expr_ref, bop_l, bop_r, lk_expr, rk_expr, pipeline_expr_block_ref_at(arena, bop_l), pipeline_expr_block_ref_at(arena, bop_r), lt_ar, rt_ar, dbg_left, dbg_left_len, dbg_right, dbg_right_len));
      (void)((lko = pipeline_type_kind_ord_at(arena, lt_ar)));
      (void)((rko = pipeline_type_kind_ord_at(arena, rt_ar)));
      if (((lko ==ord_void) || (rko ==ord_void))) {
        int32_t line_vb = pipeline_expr_line_at(arena, expr_ref);
        int32_t col_vb = pipeline_expr_col_at(arena, expr_ref);
        (void)(driver_diagnostic_typeck_invalid_void_binop(line_vb, col_vb));
        return -1;
      }
      if (((lko ==ord_bool) || (rko ==ord_bool))) {
        int32_t line_bb = pipeline_expr_line_at(arena, expr_ref);
        int32_t col_bb = pipeline_expr_col_at(arena, expr_ref);
        (void)(driver_diagnostic_typeck_invalid_bool_binop(line_bb, col_bb));
        return -1;
      }
      if (((expr_kind ==ord_add) || (expr_kind ==ord_sub))) {
        (((lko ==ord_ptr) && (((rko ==ord_i32) || (rko ==ord_usize)) || (rko ==ord_isize))) ? ({   (void)((out_ar = lt_ar));
 }) : ((((expr_kind ==ord_add) && (rko ==ord_ptr)) && (((lko ==ord_i32) || (lko ==ord_usize)) || (lko ==ord_isize))) ? ({   (void)((out_ar = rt_ar));
 }) : 0));
      }
      if (((lko ==ord_ptr) || (rko ==ord_ptr))) {
        int32_t line_pb = pipeline_expr_line_at(arena, expr_ref);
        int32_t col_pb = pipeline_expr_col_at(arena, expr_ref);
        if ((expr_kind ==ord_add)) {
          if (!(ast_ref_is_null(out_ar))) {
            (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
            return 0;
          }
          (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
          return -1;
        }
        if ((expr_kind ==ord_sub)) {
          if (((lko ==ord_ptr) && (rko ==ord_ptr))) {
            (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_isize)));
            (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
            return 0;
          }
          if (!(ast_ref_is_null(out_ar))) {
            (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
            return 0;
          }
          (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
          return -1;
        }
        (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_pb, col_pb));
        return -1;
      }
      if (((((lko ==ord_f32) || (lko ==ord_f64)) || (rko ==ord_f32)) || (rko ==ord_f64))) {
        (((((((expr_kind ==ord_mod) || (expr_kind ==ord_shl)) || (expr_kind ==ord_shr)) || (expr_kind ==ord_bitand)) || (expr_kind ==ord_bitor)) || (expr_kind ==ord_bitxor)) ? ({   int32_t line_fb = pipeline_expr_line_at(arena, expr_ref);
  int32_t col_fb = pipeline_expr_col_at(arena, expr_ref);
  (void)(driver_diagnostic_typeck_invalid_float_binop(line_fb, col_fb));
  return -1;
 }) : 0);
      }
      if ((((typeck_type_is_aggregate_cmp_operand(module, arena, lt_ar) !=0) || (typeck_type_is_aggregate_cmp_operand(module, arena, rt_ar) !=0)) && !(((lko ==ord_type_vector) && (rko ==ord_type_vector))))) {
        int32_t line_aa = pipeline_expr_line_at(arena, expr_ref);
        int32_t col_aa = pipeline_expr_col_at(arena, expr_ref);
        (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_aa, col_aa));
        return -1;
      }
      if (ast_ref_is_null(out_ar)) {
        (((((((((lko ==ord_i32) || (lko ==ord_u8)) || (lko ==ord_u32)) || (lko ==ord_u64)) || (lko ==ord_i64)) || (lko ==ord_usize)) || (lko ==ord_isize)) && (((((((rko ==ord_i32) || (rko ==ord_u8)) || (rko ==ord_u32)) || (rko ==ord_u64)) || (rko ==ord_i64)) || (rko ==ord_usize)) || (rko ==ord_isize))) ? ({   (((expr_kind ==ord_shl) || (expr_kind ==ord_shr)) ? ({   (void)((out_ar = lt_ar));
 }) : (((((expr_kind ==ord_bitand) || (expr_kind ==ord_bitor)) || (expr_kind ==ord_bitxor)) || (expr_kind ==ord_mod)) ? ({   (((rk_expr ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_r, lt_ar, lko, rk_expr) !=0)) ? ({   (void)((out_ar = lt_ar));
 }) : (((lk_expr ==ord_lit) && (typeck_coerce_init_lit_to_decl(arena, bop_l, rt_ar, rko, lk_expr) !=0)) ? ({   (void)((out_ar = rt_ar));
 }) : 0));
 }) : 0));
 }) : 0);
      }
      if (ast_ref_is_null(out_ar)) {
        (((((lko ==ord_type_vector) && (rko ==ord_type_vector)) && (pipeline_type_array_size_at(arena, lt_ar) ==pipeline_type_array_size_at(arena, rt_ar))) && typeck_type_refs_equal(arena, pipeline_type_elem_ref_at(arena, lt_ar), pipeline_type_elem_ref_at(arena, rt_ar))) ? ({   (void)((out_ar = lt_ar));
 }) : (((lko ==ord_i64) || (rko ==ord_i64)) ? ({   (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i64)));
 }) : (((lko ==ord_f32) && (typeck_coerce_init_float_lit_to_decl(arena, bop_r, lt_ar, ord_f32, rk_expr) !=0)) ? ({   (void)((out_ar = lt_ar));
 }) : (((rko ==ord_f32) && (typeck_coerce_init_float_lit_to_decl(arena, bop_l, rt_ar, ord_f32, lk_expr) !=0)) ? ({   (void)((out_ar = rt_ar));
 }) : (((lko ==ord_f64) || (rko ==ord_f64)) ? ({   (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f64)));
 }) : (((lko ==ord_f32) || (rko ==ord_f32)) ? ({   (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_f32)));
 }) : (typeck_type_refs_equal(arena, lt_ar, rt_ar) ? ({   (void)((out_ar = lt_ar));
 }) : (typeck_integer_widen_ok_refs(arena, lt_ar, rt_ar) ? ({   (void)((out_ar = lt_ar));
 }) : (typeck_integer_widen_ok_refs(arena, rt_ar, lt_ar) ? ({   (void)((out_ar = rt_ar));
 }) : (((lk_expr ==ord_lit) && (rk_expr !=ord_lit)) ? ({   (void)((out_ar = rt_ar));
 }) : (((rk_expr ==ord_lit) && (lk_expr !=ord_lit)) ? ({   (void)((out_ar = lt_ar));
 }) : (!(ast_ref_is_null(lt_ar)) ? ({   (void)((out_ar = lt_ar));
 }) : (!(ast_ref_is_null(rt_ar)) ? ({   (void)((out_ar = rt_ar));
 }) : 0)))))))))))));
      }
      if (((expr_kind >=4) && (expr_kind <=13))) {
        (void)((allow_i32_fallback = 1));
      }
      if ((((ast_ref_is_null(out_ar) && (lko !=ord_type_vector)) && (rko !=ord_type_vector)) && (allow_i32_fallback !=0))) {
        (void)((out_ar = typeck_ensure_primitive_by_kind_ord(arena, ord_i32)));
      }
      (!(ast_ref_is_null(out_ar)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, out_ar));
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_expr_binop(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_eq = 14;
    int32_t ord_ne = 15;
    int32_t ord_lt = 16;
    int32_t ord_le = 17;
    int32_t ord_gt = 18;
    int32_t ord_ge = 19;
    int32_t ord_logand = 20;
    int32_t ord_logor = 21;
    int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    if (((((((((expr_kind ==ord_eq) || (expr_kind ==ord_ne)) || (expr_kind ==ord_lt)) || (expr_kind ==ord_le)) || (expr_kind ==ord_gt)) || (expr_kind ==ord_ge)) || (expr_kind ==ord_logand)) || (expr_kind ==ord_logor))) {
      return typeck_check_expr_binop_cmp(module, arena, expr_ref, return_type_ref, ctx);
    }
    return typeck_check_expr_binop_arith(module, arena, expr_ref, return_type_ref, ctx);
  }
}
int32_t typeck_check_expr_field_access(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t base_ref = 0;
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t elem_ty = 0;
    int32_t layout_rc = 0;
    int32_t base_expected = 0;
    int32_t base_kind = 0;
    int32_t ord_call = 48;
    int32_t ord_method_call = 49;
    int32_t ord_type_ptr = 9;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return -1;
    }
    (void)((base_ref = pipeline_expr_field_access_base_ref(arena, expr_ref)));
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return -1;
    }
    (void)(typeck_field_prebind(module, arena, expr_ref, ctx));
    if ((typeck_field_import_binding(module, arena, expr_ref, base_ref, ctx) !=0)) {
      return 0;
    }
    (void)((base_expected = 0));
    (void)((base_kind = pipeline_expr_kind_ord_at(arena, base_ref)));
    if ((((base_kind ==ord_call) || (base_kind ==ord_method_call)) || (base_kind ==45))) {
      (void)((base_expected = typeck_field_reverse_infer_base_type(module, arena, expr_ref, return_type_ref)));
    }
    if ((pipeline_typeck_check_expr_c(module, arena, base_ref, base_expected, ctx) !=0)) {
      return -1;
    }
    if ((typeck_soa_field_soa_index(module, arena, expr_ref, base_ref) !=0)) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((!(ast_ref_is_null(base_ty)) && (base_ty > 0)) && (base_ty <=((arena)->num_types)))) {
      (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
      if ((bt_kind ==ord_type_ptr)) {
        (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
        (!(ast_ref_is_null(elem_ty)) ? ({   (void)(typeck_field_known_ptr(module, arena, expr_ref, base_ref, pipeline_module_num_struct_layouts_at(module)));
 }) : 0);
      }
      (void)((layout_rc = typeck_field_layout_named(module, arena, expr_ref, base_ref, ctx)));
      if ((layout_rc ==2)) {
        return 0;
      }
      (void)(typeck_field_slice(arena, expr_ref, base_ref));
    }
    (void)(typeck_field_name_fallback(arena, expr_ref, base_ref));
    (void)(typeck_field_lexer_fallback(module, arena, expr_ref, base_ref, ctx));
    (void)(typeck_field_apply_mono_type_arg(module, arena, expr_ref, base_ty));
    (void)(typeck_field_apply_ambient_for_type_param(module, arena, expr_ref, return_type_ref, ctx));
    if ((typeck_field_unknown_hard_fail(module, arena, expr_ref, base_ref, ctx) !=0)) {
      return -1;
    }
    return 0;
  }
}
int32_t typeck_check_expr_unary(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_neg = 22;
    int32_t ord_bitnot = 23;
    int32_t ord_lognot = 24;
    int32_t ord_ptr = 9;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    int32_t expr_kind = pipeline_expr_kind_ord_at(arena, expr_ref);
    int32_t op_tr = 0;
    int32_t bt = 0;
    int32_t op_ko = 0;
    int32_t line_u = 0;
    int32_t col_u = 0;
    if ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    (void)((op_tr = typeck_expr_type_ref(arena, op_ref)));
    if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=((arena)->num_types)))) {
      ((typeck_type_is_aggregate_cmp_operand(module, arena, op_tr) !=0) ? ({   (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_invalid_aggregate_cmp(line_u, col_u));
  return -1;
 }) : 0);
    }
    if ((expr_kind ==ord_lognot)) {
      if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=((arena)->num_types)))) {
        (!(typeck_type_ref_is_bool(arena, op_tr)) ? ({   (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_logical_operand_not_bool(line_u, col_u));
  return -1;
 }) : 0);
      }
      (void)((bt = typeck_ensure_bool_type_ref(arena)));
      if ((bt !=0)) {
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, bt));
      }
      return 0;
    }
    if (((!(ast_ref_is_null(op_tr)) && (op_tr > 0)) && (op_tr <=((arena)->num_types)))) {
      (void)((op_ko = pipeline_type_kind_ord_at(arena, op_tr)));
      if ((((expr_kind ==ord_neg) || (expr_kind ==ord_bitnot)) && (op_ko ==16))) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_void_binop(line_u, col_u));
        return -1;
      }
      if ((((expr_kind ==ord_neg) || (expr_kind ==ord_bitnot)) && (op_ko ==1))) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_bool_binop(line_u, col_u));
        return -1;
      }
      if ((expr_kind ==ord_bitnot)) {
        if (((op_ko ==ord_f32) || (op_ko ==ord_f64))) {
          (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
          (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
          (void)(driver_diagnostic_typeck_invalid_float_binop(line_u, col_u));
          return -1;
        }
        ((op_ko ==ord_ptr) ? ({   (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u));
  return -1;
 }) : 0);
      }
      if (((expr_kind ==ord_neg) && (op_ko ==ord_ptr))) {
        (void)((line_u = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_u = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_ptr_binop(line_u, col_u));
        return -1;
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, op_tr));
    }
    return 0;
  }
}
int32_t typeck_check_expr_addr_of(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    int32_t op_ty = 0;
    int32_t pt = 0;
    if (!(ast_ref_is_null(op_ref))) {
      if ((pipeline_typeck_reject_addr_of_linear_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(arena, op_ref, expr_ref, module, ctx) !=0)) {
        return -1;
      }
      ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)((op_ty = typeck_expr_type_ref(arena, op_ref)));
    if (((ast_ref_is_null(op_ty) || (op_ty <=0)) || (op_ty > ((arena)->num_types)))) {
      return -1;
    }
    (void)((pt = pipeline_typeck_ptr_for_addr_of_operand_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(arena, op_ref, op_ty, module, ctx)));
    if ((pt ==0)) {
      (void)((pt = typeck_find_or_alloc_ptr_type_ref(arena, op_ty)));
    }
    if ((pt ==0)) {
      return -1;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, pt));
    return 0;
  }
}
int32_t typeck_check_expr_deref(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    if ((pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(ctx) <=0)) {
      int32_t line = pipeline_expr_line_at(arena, expr_ref);
      int32_t col = pipeline_expr_col_at(arena, expr_ref);
      (void)(driver_diagnostic_typeck_deref_outside_unsafe(line, col));
      return -1;
    }
    int32_t ord_ptr = 9;
    int32_t op_ref = pipeline_expr_unary_operand_ref_at(arena, expr_ref);
    int32_t op_ptr = 0;
    int32_t elem_ty = 0;
    if (!(ast_ref_is_null(op_ref))) {
      ((typeck_check_expr(module, arena, op_ref, return_type_ref, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)((op_ptr = typeck_expr_type_ref(arena, op_ref)));
    if (((ast_ref_is_null(op_ptr) || (op_ptr <=0)) || (op_ptr > ((arena)->num_types)))) {
      return -1;
    }
    if ((pipeline_type_kind_ord_at(arena, op_ptr) !=ord_ptr)) {
      return -1;
    }
    (void)((elem_ty = pipeline_type_elem_ref_at(arena, op_ptr)));
    if (ast_ref_is_null(elem_ty)) {
      return -1;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty));
    return 0;
  }
}
int32_t typeck_check_expr_var_top_level(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * vbuf, int32_t vnlen, int32_t tl) {
  {
    int32_t tl_tr = 0;
    if ((tl >=((module)->num_top_level_lets))) {
      return 0;
    }
    if (typeck_top_level_let_name_equal(module, tl, vbuf, vnlen)) {
      (void)((tl_tr = pipeline_module_top_level_let_type_ref(module, tl)));
      (!(ast_ref_is_null(tl_tr)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tl_tr));
  return 1;
 }) : 0);
    }
    return typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, (tl + 1));
  }
}
int32_t typeck_check_expr_var(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t vnlen = 0;
    uint8_t * vbuf = typeck_scratch64_slot(0);
    int32_t vd_tr = 0;
    int32_t block_ref = 0;
    int32_t func_ix = 0;
    int32_t pr = 0;
    int32_t tk_tr = 0;
    int32_t tg_tr = 0;
    uint8_t nm_tok_kind[9] = {84, 111, 107, 101, 110, 75, 105, 110, 100};
    uint8_t nm_typ_kind[8] = {84, 121, 112, 101, 75, 105, 110, 100};
    if ((((((arena ==0) || (module ==0)) || (ctx ==0)) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((vnlen = pipeline_expr_var_name_len(arena, expr_ref)));
    if (((vnlen <=0) || (vnlen > 127))) {
      return -1;
    }
    (void)(pipeline_expr_var_name_into(arena, expr_ref, vbuf));
    (void)((block_ref = pipeline_dep_ctx_current_block_ref_at(ctx)));
    (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 99, pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if (((block_ref !=0) && (block_ref <=((arena)->num_blocks)))) {
      (void)((vd_tr = pipeline_block_resolve_var_type_ref(arena, block_ref, vbuf, vnlen)));
      ((vd_tr !=0) ? ({   (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 1, vd_tr));
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, vd_tr));
  if ((pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32(arena, vd_tr, expr_ref, vbuf, vnlen) !=0)) {
    return -1;
  }
  return 0;
 }) : 0);
    }
    (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
    if (((func_ix >=0) && (func_ix < ((module)->num_funcs)))) {
      (void)((pr = pipeline_module_func_param_type_ref_for_name(module, func_ix, vbuf, vnlen)));
      ((pr !=0) ? ({   (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 2, pr));
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, pr));
  if ((pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32(arena, pr, expr_ref, vbuf, vnlen) !=0)) {
    return -1;
  }
  return 0;
 }) : 0);
    }
    (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 100, pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if ((((module)->num_top_level_lets) > 0)) {
      ((typeck_check_expr_var_top_level(module, arena, expr_ref, vbuf, vnlen, 0) !=0) ? ({   (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 101, pipeline_expr_resolved_type_ref(arena, expr_ref)));
  return 0;
 }) : 0);
    }
    (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, pipeline_dep_ctx_current_func_index(ctx), block_ref, 102, pipeline_expr_resolved_type_ref(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 104, pipeline_expr_resolved_type_ref(arena, expr_ref)));
    (void)(({   int32_t fi = 0;
  int32_t nfuncs = ((module)->num_funcs);
  while ((fi < nfuncs)) {
    if ((pipeline_module_func_name_equal_at(module, fi, vbuf, vnlen) !=0)) {
      int32_t u8r = typeck_ensure_u8_type_ref(arena);
      int32_t ptr_u8 = 0;
      if (ast_ref_is_null(u8r)) {
        return -1;
      }
      (void)((ptr_u8 = typeck_find_or_alloc_ptr_type_ref(arena, u8r)));
      if ((ast_ref_is_null(ptr_u8) || (ptr_u8 ==0))) {
        return -1;
      }
      /* Cap-fn-ptr (10.3.2): mark is_used so asm WPO keeps address-taken body. */
      (void)(pipeline_module_func_set_is_used(module, fi, 1));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ptr_u8));
      (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 105, ptr_u8));
      return 0;
    }
    (void)((fi = (fi + 1)));
  }
 }));
    if (((vnlen ==9) && typeck_name_equal(vbuf, vnlen, &((nm_tok_kind)[0]), 9))) {
      (void)((tk_tr = typeck_find_or_alloc_named_type_ref(arena, &((nm_tok_kind)[0]), 9)));
      ((tk_tr !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tk_tr));
  return 0;
 }) : 0);
    }
    if (((vnlen ==8) && typeck_name_equal(vbuf, vnlen, &((nm_typ_kind)[0]), 8))) {
      (void)((tg_tr = typeck_find_or_alloc_named_type_ref(arena, &((nm_typ_kind)[0]), 8)));
      ((tg_tr !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tg_tr));
  return 0;
 }) : 0);
    }
    if (typeck_var_is_import_visible_name(module, vbuf, vnlen)) {
      return 0;
    }
    if ((typeck_reject_bare_import_const(module, arena, expr_ref, ctx, vbuf, vnlen) !=0)) {
      return -1;
    }
    if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      int32_t ft = typeck_match_subject_field_type(module, arena, vbuf, vnlen);
      ((ft > 0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ft));
  (void)(driver_diagnostic_typeck_var_resolution(expr_ref, vbuf, vnlen, func_ix, block_ref, 106, ft));
  return 0;
 }) : 0);
    }
    if (ast_ref_is_null(pipeline_expr_resolved_type_ref(arena, expr_ref))) {
      return -1;
    }
    return 0;
  }
}
int32_t typeck_check_expr_method_call_arg(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t arg_i, int32_t num_args) {
  {
    int32_t arg_ref = 0;
    if ((arg_i >=num_args)) {
      return 0;
    }
    (void)((arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i)));
    if ((typeck_check_expr(module, arena, arg_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    return typeck_check_expr_method_call_arg(module, arena, expr_ref, return_type_ref, ctx, (arg_i + 1), num_args);
  }
}
int32_t typeck_method_call_resolve_generic_bound(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args) {
  {
    int32_t cfi = -1;
    int32_t fn_len = 0;
    int32_t tp_len = 0;
    int32_t ret_kind = -1;
    int32_t ret_nlen = 0;
    int32_t ret_ty = 0;
    int32_t hit = 0;
    int32_t i = 0;
    int32_t same = 0;
    uint8_t fn_nm[128] = {};
    uint8_t tp_nm[128] = {};
    uint8_t ret_nm[64] = {};
    if ((((((((module ==0) || (arena ==0)) || (ctx ==0)) || (expr_ref <=0)) || (base_ty <=0)) || (method_nm ==0)) || (method_nlen <=0))) {
      return 0;
    }
    if ((typeck_type_is_free_type_param(module, arena, base_ty) ==0)) {
      return 0;
    }
    (void)((cfi = pipeline_dep_ctx_current_func_index(ctx)));
    if ((cfi < 0)) {
      return 0;
    }
    if ((pipeline_module_func_num_generic_params_at(module, cfi) <=0)) {
      return 0;
    }
    (void)((fn_len = pipeline_module_func_name_len_at(module, cfi)));
    if (((fn_len <=0) || (fn_len > 127))) {
      return 0;
    }
    (void)(pipeline_module_func_name_copy64(module, cfi, &((fn_nm)[0])));
    (void)((tp_len = pipeline_type_named_name_into(arena, base_ty, &((tp_nm)[0]))));
    if (((tp_len <=0) || (tp_len > 127))) {
      return 0;
    }
    (void)((ret_kind = -1));
    (void)((ret_nlen = 0));
    (void)((hit = xlang_generic_bound_method_on_param_c(&((fn_nm)[0]), fn_len, &((tp_nm)[0]), tp_len, method_nm, method_nlen, num_args, &(ret_kind), &((ret_nm)[0]), &(ret_nlen))));
    if ((hit ==0)) {
      return 0;
    }
    if (((ret_kind ==8) && (ret_nlen > 0))) {
      (void)((same = 0));
      if ((((((ret_nlen ==4) && ((ret_nm)[0] ==83)) && ((ret_nm)[1] ==101)) && ((ret_nm)[2] ==108)) && ((ret_nm)[3] ==102))) {
        (void)((same = 1));
      }
      if (((same ==0) && (ret_nlen ==tp_len))) {
        (void)((same = 1));
        (void)((i = 0));
        while ((i < tp_len)) {
          (((ret_nm)[i] !=(tp_nm)[i]) ? ({   (void)((same = 0));
  (void)((i = tp_len));
 }) : ({   (void)((i = (i + 1)));
 }));
        }
      }
      ((same !=0) ? ({   (void)((ret_ty = base_ty));
 }) : ({   (void)((ret_ty = pipeline_type_find_or_alloc_named(arena, &((ret_nm)[0]), ret_nlen)));
 }));
    } else {
      if (((((((ret_kind >=0) && (ret_kind !=8)) && (ret_kind !=9)) && (ret_kind !=10)) && (ret_kind !=11)) && (ret_kind !=13))) {
        (void)((ret_ty = pipeline_type_ensure_by_kind_ord(arena, ret_kind)));
      } else {
        (void)((ret_ty = 0));
      }
    }
    (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, -1, -1));
    if ((ret_ty > 0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
    }
    return 1;
  }
}
int32_t typeck_check_expr_method_call(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_var = 3;
    int32_t ord_i32 = 0;
    int32_t ord_ptr = 9;
    int32_t ord_dyn = 17;
    int32_t ord_import_binding = 1;
    int32_t base_ref = 0;
    int32_t base_rc = 0;
    int32_t base_ty = 0;
    int32_t base_kind = 0;
    int32_t method_nlen = 0;
    int32_t num_args = 0;
    int32_t arg_i = 0;
    int32_t ret_ty = 0;
    int32_t dep_ix = -1;
    int32_t dep_slot = -1;
    int32_t func_ix = -1;
    int32_t import_ret_ty = 0;
    int32_t ii = 0;
    int32_t n_imp = 0;
    int32_t base_nlen = 0;
    int32_t expect_store = 0;
    uint8_t method_nm[128] = {};
    uint8_t base_nm[128] = {};
    struct ast_Module * dm = 0;
    uint8_t msg[256] = {};
    int32_t p = 0;
    int32_t z = 0;
    int32_t line = 0;
    int32_t col = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)(pipeline_expr_init_call_resolve_at_ref(arena, expr_ref));
    (void)((base_ref = pipeline_expr_method_call_base_ref_at(arena, expr_ref)));
    (void)((base_rc = typeck_check_expr(module, arena, base_ref, 0, ctx)));
    (void)((base_kind = pipeline_expr_kind_ord_at(arena, base_ref)));
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    (void)((method_nlen = pipeline_expr_method_call_name_len(arena, expr_ref)));
    if (((method_nlen <=0) || (method_nlen > 127))) {
      return -1;
    }
    (void)(pipeline_expr_method_call_name_into(arena, expr_ref, &((method_nm)[0])));
    (void)((ret_ty = 0));
    if ((((((((((base_ty > 0) && (pipeline_type_kind_ord_at(arena, base_ty) ==ord_i32)) && (method_nlen ==6)) && ((method_nm)[0] ==100)) && ((method_nm)[1] ==111)) && ((method_nm)[2] ==117)) && ((method_nm)[3] ==98)) && ((method_nm)[4] ==108)) && ((method_nm)[5] ==101))) {
      (void)((ret_ty = pipeline_type_ensure_by_kind_ord(arena, ord_i32)));
    }
    if (((base_ty > 0) && (pipeline_type_kind_ord_at(arena, base_ty) ==ord_dyn))) {
      uint8_t dyn_trait_nm[64] = {};
      int32_t dyn_trait_nlen = pipeline_type_named_name_into(arena, base_ty, &((dyn_trait_nm)[0]));
      ((dyn_trait_nlen > 0) ? ({   int32_t dyn_slot = xlang_skip_trait_method_slot_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, &((method_nm)[0]), method_nlen);
  if ((dyn_slot < 0)) {
    return -1;
  }
  (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, -2, dyn_slot));
  int32_t dyn_ret_kind = xlang_skip_trait_method_ret_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
  int32_t dyn_ret_ty = 0;
  if (((((((dyn_ret_kind >=0) && (dyn_ret_kind !=8)) && (dyn_ret_kind !=9)) && (dyn_ret_kind !=10)) && (dyn_ret_kind !=11)) && (dyn_ret_kind !=13))) {
    (void)((dyn_ret_ty = pipeline_type_ensure_by_kind_ord(arena, dyn_ret_kind)));
  }
  if (((dyn_ret_ty ==0) && (dyn_ret_kind ==11))) {
    int32_t dyn_rek = xlang_skip_trait_method_ret_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
    if (((((((dyn_rek >=0) && (dyn_rek !=8)) && (dyn_rek !=9)) && (dyn_rek !=10)) && (dyn_rek !=11)) && (dyn_rek !=13))) {
      int32_t dyn_ety = pipeline_type_ensure_by_kind_ord(arena, dyn_rek);
      ((dyn_ety > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_slice_type_ref(arena, dyn_ety)));
 }) : 0);
    }
    (((dyn_ret_ty ==0) && (dyn_rek ==8)) ? ({   uint8_t dyn_sname[64] = {};
  int32_t dyn_slen = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_sname)[0]));
  ((dyn_slen > 0) ? ({   int32_t dyn_snty = typeck_find_or_alloc_named_type_ref(arena, &((dyn_sname)[0]), dyn_slen);
  ((dyn_snty > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_slice_type_ref(arena, dyn_snty)));
 }) : 0);
 }) : 0);
 }) : 0);
  }
  if (((dyn_ret_ty ==0) && (dyn_ret_kind ==10))) {
    int32_t dyn_rek2 = xlang_skip_trait_method_ret_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
    int32_t dyn_rsz = xlang_skip_trait_method_ret_array_size_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
    int32_t dyn_rnd = xlang_skip_trait_method_ret_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
    int32_t dyn_leaf = 0;
    if (((((((dyn_rek2 >=0) && (dyn_rek2 !=8)) && (dyn_rek2 !=9)) && (dyn_rek2 !=10)) && (dyn_rek2 !=11)) && (dyn_rek2 !=13))) {
      (void)((dyn_leaf = pipeline_type_ensure_by_kind_ord(arena, dyn_rek2)));
    }
    if (((dyn_leaf ==0) && (dyn_rek2 ==8))) {
      uint8_t dyn_aname[64] = {};
      int32_t dyn_alen = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_aname)[0]));
      ((dyn_alen > 0) ? ({   (void)((dyn_leaf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_aname)[0]), dyn_alen)));
 }) : 0);
    }
    ((dyn_leaf > 0) ? ({   ((dyn_rnd >=2) ? ({   int32_t dyn_di = (dyn_rnd - 1);
  int32_t dyn_cur = dyn_leaf;
  while (((dyn_di >=0) && (dyn_cur > 0))) {
    int32_t dyn_dsz = xlang_skip_trait_method_ret_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_di);
    if ((dyn_dsz > 0)) {
      (void)((dyn_cur = typeck_find_or_alloc_array_type_ref(arena, dyn_cur, dyn_dsz)));
    } else {
      (void)((dyn_cur = 0));
    }
    (void)((dyn_di = (dyn_di - 1)));
  }
  (void)((dyn_ret_ty = dyn_cur));
 }) : ((dyn_rsz > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_array_type_ref(arena, dyn_leaf, dyn_rsz)));
 }) : 0));
 }) : 0);
  }
  if (((dyn_ret_ty ==0) && (dyn_ret_kind ==8))) {
    uint8_t dyn_rnm[64] = {};
    int32_t dyn_rnl = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_rnm)[0]));
    ((dyn_rnl > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_named_type_ref(arena, &((dyn_rnm)[0]), dyn_rnl)));
 }) : 0);
  }
  if (((dyn_ret_ty ==0) && (dyn_ret_kind ==9))) {
    int32_t dyn_rek3 = xlang_skip_trait_method_ret_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
    if (((((((dyn_rek3 >=0) && (dyn_rek3 !=8)) && (dyn_rek3 !=9)) && (dyn_rek3 !=10)) && (dyn_rek3 !=11)) && (dyn_rek3 !=13))) {
      int32_t dyn_ety3 = pipeline_type_ensure_by_kind_ord(arena, dyn_rek3);
      ((dyn_ety3 > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_ety3)));
 }) : 0);
    }
    if (((dyn_ret_ty ==0) && (dyn_rek3 ==8))) {
      uint8_t dyn_pname[64] = {};
      int32_t dyn_plen = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_pname)[0]));
      ((dyn_plen > 0) ? ({   int32_t dyn_pnty = typeck_find_or_alloc_named_type_ref(arena, &((dyn_pname)[0]), dyn_plen);
  ((dyn_pnty > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_pnty)));
 }) : 0);
 }) : 0);
    }
    if (((dyn_ret_ty ==0) && (dyn_rek3 ==10))) {
      int32_t dyn_reek = xlang_skip_trait_method_ret_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
      int32_t dyn_ralf = 0;
      if (((((((dyn_reek >=0) && (dyn_reek !=8)) && (dyn_reek !=9)) && (dyn_reek !=10)) && (dyn_reek !=11)) && (dyn_reek !=13))) {
        (void)((dyn_ralf = pipeline_type_ensure_by_kind_ord(arena, dyn_reek)));
      }
      if (((dyn_ralf ==0) && (dyn_reek ==8))) {
        uint8_t dyn_ranm[64] = {};
        int32_t dyn_ranl = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_ranm)[0]));
        ((dyn_ranl > 0) ? ({   (void)((dyn_ralf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_ranm)[0]), dyn_ranl)));
 }) : 0);
      }
      ((dyn_ralf > 0) ? ({   int32_t dyn_rend = xlang_skip_trait_method_ret_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
  int32_t dyn_rew = dyn_ralf;
  if ((dyn_rend >=1)) {
    int32_t dyn_rpx = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (dyn_rend + 1));
    if ((dyn_rpx > 0)) {
      int32_t dyn_rpi = 0;
      while (((dyn_rpi < dyn_rpx) && (dyn_rew > 0))) {
        (void)((dyn_rew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_rew)));
        (void)((dyn_rpi = (dyn_rpi + 1)));
      }
    }
    int32_t dyn_rex = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_rend);
    if ((dyn_rex > 0)) {
      int32_t dyn_rxi = 0;
      while (((dyn_rxi < dyn_rex) && (dyn_rew > 0))) {
        (void)((dyn_rew = typeck_find_or_alloc_slice_type_ref(arena, dyn_rew)));
        (void)((dyn_rxi = (dyn_rxi + 1)));
      }
    }
    int32_t dyn_rei = (dyn_rend - 1);
    while (((dyn_rei >=0) && (dyn_rew > 0))) {
      int32_t dyn_red = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_rei);
      if ((dyn_red > 0)) {
        (void)((dyn_rew = typeck_find_or_alloc_array_type_ref(arena, dyn_rew, dyn_red)));
      } else {
        (void)((dyn_rew = 0));
      }
      (void)((dyn_rei = (dyn_rei - 1)));
    }
  } else {
    (void)((dyn_rew = 0));
  }
  ((dyn_rew > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_rew)));
 }) : 0);
 }) : 0);
    }
    if (((dyn_ret_ty ==0) && (dyn_rek3 ==9))) {
      int32_t dyn_preek = xlang_skip_trait_method_ret_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
      int32_t dyn_pralf = 0;
      if (((((((dyn_preek >=0) && (dyn_preek !=8)) && (dyn_preek !=9)) && (dyn_preek !=10)) && (dyn_preek !=11)) && (dyn_preek !=13))) {
        (void)((dyn_pralf = pipeline_type_ensure_by_kind_ord(arena, dyn_preek)));
      }
      if (((dyn_pralf ==0) && (dyn_preek ==8))) {
        uint8_t dyn_pranm[64] = {};
        int32_t dyn_pranl = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_pranm)[0]));
        ((dyn_pranl > 0) ? ({   (void)((dyn_pralf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_pranm)[0]), dyn_pranl)));
 }) : 0);
      }
      ((dyn_pralf > 0) ? ({   int32_t dyn_prend = xlang_skip_trait_method_ret_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
  int32_t dyn_prew = dyn_pralf;
  if ((dyn_prend >=1)) {
    int32_t dyn_prpx = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (dyn_prend + 1));
    if ((dyn_prpx > 0)) {
      int32_t dyn_prpi = 0;
      while (((dyn_prpi < dyn_prpx) && (dyn_prew > 0))) {
        (void)((dyn_prew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_prew)));
        (void)((dyn_prpi = (dyn_prpi + 1)));
      }
    }
    int32_t dyn_prex = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_prend);
    if ((dyn_prex > 0)) {
      int32_t dyn_prxi = 0;
      while (((dyn_prxi < dyn_prex) && (dyn_prew > 0))) {
        (void)((dyn_prew = typeck_find_or_alloc_slice_type_ref(arena, dyn_prew)));
        (void)((dyn_prxi = (dyn_prxi + 1)));
      }
    }
    int32_t dyn_prei = (dyn_prend - 1);
    while (((dyn_prei >=0) && (dyn_prew > 0))) {
      int32_t dyn_pred = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_prei);
      if ((dyn_pred > 0)) {
        (void)((dyn_prew = typeck_find_or_alloc_array_type_ref(arena, dyn_prew, dyn_pred)));
      } else {
        (void)((dyn_prew = 0));
      }
      (void)((dyn_prei = (dyn_prei - 1)));
    }
  } else {
    if ((dyn_prend ==0)) {
      int32_t dyn_prpx0 = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, 1);
      if ((dyn_prpx0 > 0)) {
        int32_t dyn_prpi0 = 0;
        while (((dyn_prpi0 < dyn_prpx0) && (dyn_prew > 0))) {
          (void)((dyn_prew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_prew)));
          (void)((dyn_prpi0 = (dyn_prpi0 + 1)));
        }
      }
      int32_t dyn_prex0 = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, 0);
      ((dyn_prex0 > 0) ? ({   int32_t dyn_prxi0 = 0;
  while (((dyn_prxi0 < dyn_prex0) && (dyn_prew > 0))) {
    (void)((dyn_prew = typeck_find_or_alloc_slice_type_ref(arena, dyn_prew)));
    (void)((dyn_prxi0 = (dyn_prxi0 + 1)));
  }
 }) : 0);
    }
  }
  if ((dyn_prew > 0)) {
    (void)((dyn_prew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_prew)));
  }
  ((dyn_prew > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_prew)));
 }) : 0);
 }) : 0);
    }
    (((dyn_ret_ty ==0) && (dyn_rek3 ==11)) ? ({   int32_t dyn_sreek = xlang_skip_trait_method_ret_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
  int32_t dyn_sralf = 0;
  if (((((((dyn_sreek >=0) && (dyn_sreek !=8)) && (dyn_sreek !=9)) && (dyn_sreek !=10)) && (dyn_sreek !=11)) && (dyn_sreek !=13))) {
    (void)((dyn_sralf = pipeline_type_ensure_by_kind_ord(arena, dyn_sreek)));
  }
  if (((dyn_sralf ==0) && (dyn_sreek ==8))) {
    uint8_t dyn_sranm[64] = {};
    int32_t dyn_sranl = xlang_skip_trait_method_ret_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, &((dyn_sranm)[0]));
    ((dyn_sranl > 0) ? ({   (void)((dyn_sralf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_sranm)[0]), dyn_sranl)));
 }) : 0);
  }
  ((dyn_sralf > 0) ? ({   int32_t dyn_srend = xlang_skip_trait_method_ret_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot);
  int32_t dyn_srew = dyn_sralf;
  if ((dyn_srend ==-2)) {
    int32_t dyn_srpxm2 = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, 1);
    if ((dyn_srpxm2 > 0)) {
      int32_t dyn_srpim2 = 0;
      while (((dyn_srpim2 < dyn_srpxm2) && (dyn_srew > 0))) {
        (void)((dyn_srew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_srew)));
        (void)((dyn_srpim2 = (dyn_srpim2 + 1)));
      }
    }
    int32_t dyn_srexm2 = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, 0);
    if ((dyn_srexm2 < 1)) {
      (void)((dyn_srexm2 = 1));
    }
    int32_t dyn_srxim2 = 0;
    while (((dyn_srxim2 < dyn_srexm2) && (dyn_srew > 0))) {
      (void)((dyn_srew = typeck_find_or_alloc_slice_type_ref(arena, dyn_srew)));
      (void)((dyn_srxim2 = (dyn_srxim2 + 1)));
    }
  } else {
    if ((dyn_srend ==0)) {
      int32_t dyn_srpx0 = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, 0);
      ((dyn_srpx0 > 0) ? ({   int32_t dyn_srpi0 = 0;
  while (((dyn_srpi0 < dyn_srpx0) && (dyn_srew > 0))) {
    (void)((dyn_srew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_srew)));
    (void)((dyn_srpi0 = (dyn_srpi0 + 1)));
  }
 }) : 0);
    } else {
      if ((dyn_srend >=1)) {
        int32_t dyn_srpx = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_srend);
        if ((dyn_srpx > 0)) {
          int32_t dyn_srpi = 0;
          while (((dyn_srpi < dyn_srpx) && (dyn_srew > 0))) {
            (void)((dyn_srew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_srew)));
            (void)((dyn_srpi = (dyn_srpi + 1)));
          }
        }
        int32_t dyn_srex = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (dyn_srend + 1));
        if ((dyn_srex > 0)) {
          int32_t dyn_srxi = 0;
          while (((dyn_srxi < dyn_srex) && (dyn_srew > 0))) {
            (void)((dyn_srew = typeck_find_or_alloc_slice_type_ref(arena, dyn_srew)));
            (void)((dyn_srxi = (dyn_srxi + 1)));
          }
        }
        int32_t dyn_srei = (dyn_srend - 1);
        while (((dyn_srei >=0) && (dyn_srew > 0))) {
          int32_t dyn_sred = xlang_skip_trait_method_ret_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, dyn_srei);
          if ((dyn_sred > 0)) {
            (void)((dyn_srew = typeck_find_or_alloc_array_type_ref(arena, dyn_srew, dyn_sred)));
          } else {
            (void)((dyn_srew = 0));
          }
          (void)((dyn_srei = (dyn_srei - 1)));
        }
      }
    }
  }
  if ((dyn_srew > 0)) {
    (void)((dyn_srew = typeck_find_or_alloc_slice_type_ref(arena, dyn_srew)));
  }
  ((dyn_srew > 0) ? ({   (void)((dyn_ret_ty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_srew)));
 }) : 0);
 }) : 0);
 }) : 0);
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, dyn_ret_ty));
  (void)((num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref)));
  (void)((arg_i = 0));
  while ((arg_i < num_args)) {
    int32_t dyn_arg = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i);
    if ((typeck_check_expr(module, arena, dyn_arg, return_type_ref, ctx) !=0)) {
      return -1;
    }
    int32_t dyn_pk = xlang_skip_trait_method_param_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
    if (((dyn_arg > 0) && ((dyn_pk ==14) || (dyn_pk ==15)))) {
      int32_t dyn_fty = pipeline_type_ensure_by_kind_ord(arena, dyn_pk);
      ((dyn_fty > 0) ? ({   int32_t dyn_ak = pipeline_expr_kind_ord_at(arena, dyn_arg);
  (void)(typeck_coerce_init_float_lit_to_decl(arena, dyn_arg, dyn_fty, dyn_pk, dyn_ak));
 }) : 0);
    }
    if (((dyn_arg > 0) && (dyn_pk ==11))) {
      int32_t dyn_eek = xlang_skip_trait_method_param_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
      if (((((((dyn_eek >=0) && (dyn_eek !=8)) && (dyn_eek !=9)) && (dyn_eek !=10)) && (dyn_eek !=11)) && (dyn_eek !=13))) {
        int32_t dyn_ety = pipeline_type_ensure_by_kind_ord(arena, dyn_eek);
        ((dyn_ety > 0) ? ({   int32_t dyn_sty = typeck_find_or_alloc_slice_type_ref(arena, dyn_ety);
  ((dyn_sty > 0) ? ({   (void)(typeck_coerce_init_slice_from_array(arena, dyn_arg, dyn_sty, 11));
 }) : 0);
 }) : 0);
      }
      if ((dyn_eek ==8)) {
        uint8_t dyn_snm[64] = {};
        int32_t dyn_snl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_snm)[0]));
        ((dyn_snl > 0) ? ({   int32_t dyn_snty = typeck_find_or_alloc_named_type_ref(arena, &((dyn_snm)[0]), dyn_snl);
  ((dyn_snty > 0) ? ({   int32_t dyn_ssty = typeck_find_or_alloc_slice_type_ref(arena, dyn_snty);
  ((dyn_ssty > 0) ? ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_ssty));
 }) : 0);
 }) : 0);
 }) : 0);
      }
      if ((dyn_eek ==10)) {
        int32_t dyn_saek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
        int32_t dyn_salf = 0;
        if (((((((dyn_saek >=0) && (dyn_saek !=8)) && (dyn_saek !=9)) && (dyn_saek !=10)) && (dyn_saek !=11)) && (dyn_saek !=13))) {
          (void)((dyn_salf = pipeline_type_ensure_by_kind_ord(arena, dyn_saek)));
        }
        if (((dyn_salf ==0) && (dyn_saek ==8))) {
          uint8_t dyn_sanm[64] = {};
          int32_t dyn_sanl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_sanm)[0]));
          ((dyn_sanl > 0) ? ({   (void)((dyn_salf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_sanm)[0]), dyn_sanl)));
 }) : 0);
        }
        ((dyn_salf > 0) ? ({   int32_t dyn_sand = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_saw = dyn_salf;
  if ((dyn_sand >=1)) {
    int32_t dyn_sapx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_sand + 1));
    if ((dyn_sapx > 0)) {
      int32_t dyn_sapi = 0;
      while (((dyn_sapi < dyn_sapx) && (dyn_saw > 0))) {
        (void)((dyn_saw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_saw)));
        (void)((dyn_sapi = (dyn_sapi + 1)));
      }
    }
    int32_t dyn_saex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_sand);
    if ((dyn_saex > 0)) {
      int32_t dyn_saxi = 0;
      while (((dyn_saxi < dyn_saex) && (dyn_saw > 0))) {
        (void)((dyn_saw = typeck_find_or_alloc_slice_type_ref(arena, dyn_saw)));
        (void)((dyn_saxi = (dyn_saxi + 1)));
      }
    }
    int32_t dyn_sai = (dyn_sand - 1);
    while (((dyn_sai >=0) && (dyn_saw > 0))) {
      int32_t dyn_sad = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_sai);
      if ((dyn_sad > 0)) {
        (void)((dyn_saw = typeck_find_or_alloc_array_type_ref(arena, dyn_saw, dyn_sad)));
      } else {
        (void)((dyn_saw = 0));
      }
      (void)((dyn_sai = (dyn_sai - 1)));
    }
  } else {
    (void)((dyn_saw = 0));
  }
  ((dyn_saw > 0) ? ({   int32_t dyn_sasty = typeck_find_or_alloc_slice_type_ref(arena, dyn_saw);
  ((dyn_sasty > 0) ? ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_sasty));
 }) : 0);
 }) : 0);
 }) : 0);
      }
      if ((dyn_eek ==9)) {
        int32_t dyn_spek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
        int32_t dyn_splf = 0;
        if (((((((dyn_spek >=0) && (dyn_spek !=8)) && (dyn_spek !=9)) && (dyn_spek !=10)) && (dyn_spek !=11)) && (dyn_spek !=13))) {
          (void)((dyn_splf = pipeline_type_ensure_by_kind_ord(arena, dyn_spek)));
        }
        if (((dyn_splf ==0) && (dyn_spek ==8))) {
          uint8_t dyn_spnm[64] = {};
          int32_t dyn_spnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_spnm)[0]));
          ((dyn_spnl > 0) ? ({   (void)((dyn_splf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_spnm)[0]), dyn_spnl)));
 }) : 0);
        }
        ((dyn_splf > 0) ? ({   int32_t dyn_spand = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_spaw = dyn_splf;
  if ((dyn_spand ==-2)) {
    int32_t dyn_spex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    if ((dyn_spex < 1)) {
      (void)((dyn_spex = 1));
    }
    int32_t dyn_spi = 0;
    while (((dyn_spi < dyn_spex) && (dyn_spaw > 0))) {
      (void)((dyn_spaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_spaw)));
      (void)((dyn_spi = (dyn_spi + 1)));
    }
  } else {
    if ((dyn_spand >=1)) {
      int32_t dyn_sppx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_spand + 1));
      if ((dyn_sppx > 0)) {
        int32_t dyn_sppi = 0;
        while (((dyn_sppi < dyn_sppx) && (dyn_spaw > 0))) {
          (void)((dyn_spaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_spaw)));
          (void)((dyn_sppi = (dyn_sppi + 1)));
        }
      }
      int32_t dyn_spex2 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_spand);
      if ((dyn_spex2 > 0)) {
        int32_t dyn_spi2 = 0;
        while (((dyn_spi2 < dyn_spex2) && (dyn_spaw > 0))) {
          (void)((dyn_spaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_spaw)));
          (void)((dyn_spi2 = (dyn_spi2 + 1)));
        }
      }
      int32_t dyn_spai = (dyn_spand - 1);
      while (((dyn_spai >=0) && (dyn_spaw > 0))) {
        int32_t dyn_spad = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_spai);
        if ((dyn_spad > 0)) {
          (void)((dyn_spaw = typeck_find_or_alloc_array_type_ref(arena, dyn_spaw, dyn_spad)));
        } else {
          (void)((dyn_spaw = 0));
        }
        (void)((dyn_spai = (dyn_spai - 1)));
      }
    }
  }
  ((dyn_spaw > 0) ? ({   int32_t dyn_spty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_spaw);
  ((dyn_spty > 0) ? ({   int32_t dyn_spsty = typeck_find_or_alloc_slice_type_ref(arena, dyn_spty);
  ((dyn_spsty > 0) ? ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_spsty));
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
      }
      ((dyn_eek ==11) ? ({   int32_t dyn_ssek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_sslf = 0;
  if (((((((dyn_ssek >=0) && (dyn_ssek !=8)) && (dyn_ssek !=9)) && (dyn_ssek !=10)) && (dyn_ssek !=11)) && (dyn_ssek !=13))) {
    (void)((dyn_sslf = pipeline_type_ensure_by_kind_ord(arena, dyn_ssek)));
  }
  if (((dyn_sslf ==0) && (dyn_ssek ==8))) {
    uint8_t dyn_ssnm[64] = {};
    int32_t dyn_ssnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_ssnm)[0]));
    ((dyn_ssnl > 0) ? ({   (void)((dyn_sslf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_ssnm)[0]), dyn_ssnl)));
 }) : 0);
  }
  ((dyn_sslf > 0) ? ({   int32_t dyn_ssaw = dyn_sslf;
  int32_t dyn_ssand = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  if ((dyn_ssand ==0)) {
    int32_t dyn_sspx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    ((dyn_sspx > 0) ? ({   int32_t dyn_sspi = 0;
  while (((dyn_sspi < dyn_sspx) && (dyn_ssaw > 0))) {
    (void)((dyn_ssaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_ssaw)));
    (void)((dyn_sspi = (dyn_sspi + 1)));
  }
 }) : 0);
  }
  if ((dyn_ssand ==-2)) {
    int32_t dyn_sspx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 1);
    ((dyn_sspx > 0) ? ({   int32_t dyn_sspi = 0;
  while (((dyn_sspi < dyn_sspx) && (dyn_ssaw > 0))) {
    (void)((dyn_ssaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_ssaw)));
    (void)((dyn_sspi = (dyn_sspi + 1)));
  }
 }) : 0);
  }
  if ((dyn_ssand >=1)) {
    int32_t dyn_sspx3 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_ssand);
    ((dyn_sspx3 > 0) ? ({   int32_t dyn_sspi3 = 0;
  while (((dyn_sspi3 < dyn_sspx3) && (dyn_ssaw > 0))) {
    (void)((dyn_ssaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_ssaw)));
    (void)((dyn_sspi3 = (dyn_sspi3 + 1)));
  }
 }) : 0);
  }
  if ((dyn_ssand >=1)) {
    int32_t dyn_ssex3 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_ssand + 1));
    ((dyn_ssex3 > 0) ? ({   int32_t dyn_ssxi3 = 0;
  while (((dyn_ssxi3 < dyn_ssex3) && (dyn_ssaw > 0))) {
    (void)((dyn_ssaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_ssaw)));
    (void)((dyn_ssxi3 = (dyn_ssxi3 + 1)));
  }
 }) : 0);
  }
  if ((dyn_ssand >=1)) {
    int32_t dyn_ssai = (dyn_ssand - 1);
    while (((dyn_ssai >=0) && (dyn_ssaw > 0))) {
      int32_t dyn_ssad = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_ssai);
      if ((dyn_ssad > 0)) {
        (void)((dyn_ssaw = typeck_find_or_alloc_array_type_ref(arena, dyn_ssaw, dyn_ssad)));
      } else {
        (void)((dyn_ssaw = 0));
      }
      (void)((dyn_ssai = (dyn_ssai - 1)));
    }
  }
  int32_t dyn_ssity = typeck_find_or_alloc_slice_type_ref(arena, dyn_ssaw);
  ((dyn_ssity > 0) ? ({   int32_t dyn_ssoty = typeck_find_or_alloc_slice_type_ref(arena, dyn_ssity);
  ((dyn_ssoty > 0) ? ({   int32_t dyn_ssdest = dyn_ssoty;
  if ((dyn_ssand ==-2)) {
    int32_t dyn_ssex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    if ((dyn_ssex < 1)) {
      (void)((dyn_ssex = 1));
    }
    int32_t dyn_ssi = 0;
    while (((dyn_ssi < dyn_ssex) && (dyn_ssdest > 0))) {
      (void)((dyn_ssdest = typeck_find_or_alloc_slice_type_ref(arena, dyn_ssdest)));
      (void)((dyn_ssi = (dyn_ssi + 1)));
    }
  }
  ((dyn_ssdest > 0) ? ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_ssdest));
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (((dyn_arg > 0) && (dyn_pk ==8))) {
      uint8_t dyn_pnm[64] = {};
      int32_t dyn_pnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_pnm)[0]));
      ((dyn_pnl > 0) ? ({   int32_t dyn_nty = typeck_find_or_alloc_named_type_ref(arena, &((dyn_pnm)[0]), dyn_pnl);
  ((dyn_nty > 0) ? ({   (void)(typeck_coerce_init_struct_lit_to_decl(module, arena, dyn_arg, dyn_nty));
 }) : 0);
 }) : 0);
    }
    if (((dyn_arg > 0) && (dyn_pk ==9))) {
      int32_t dyn_pek = xlang_skip_trait_method_param_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
      ((dyn_pek ==10) ? ({   int32_t dyn_peek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_plf = 0;
  if (((((((dyn_peek >=0) && (dyn_peek !=8)) && (dyn_peek !=9)) && (dyn_peek !=10)) && (dyn_peek !=11)) && (dyn_peek !=13))) {
    (void)((dyn_plf = pipeline_type_ensure_by_kind_ord(arena, dyn_peek)));
  }
  if (((dyn_plf ==0) && (dyn_peek ==8))) {
    uint8_t dyn_pnm2[64] = {};
    int32_t dyn_pnl2 = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_pnm2)[0]));
    ((dyn_pnl2 > 0) ? ({   (void)((dyn_plf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_pnm2)[0]), dyn_pnl2)));
 }) : 0);
  }
  ((dyn_plf > 0) ? ({   int32_t dyn_pend = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_pew = dyn_plf;
  if ((dyn_pend >=1)) {
    int32_t dyn_ppx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_pend + 1));
    if ((dyn_ppx > 0)) {
      int32_t dyn_ppi = 0;
      while (((dyn_ppi < dyn_ppx) && (dyn_pew > 0))) {
        (void)((dyn_pew = typeck_find_or_alloc_ptr_type_ref(arena, dyn_pew)));
        (void)((dyn_ppi = (dyn_ppi + 1)));
      }
    }
    int32_t dyn_pex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_pend);
    if ((dyn_pex > 0)) {
      int32_t dyn_pxi = 0;
      while (((dyn_pxi < dyn_pex) && (dyn_pew > 0))) {
        (void)((dyn_pew = typeck_find_or_alloc_slice_type_ref(arena, dyn_pew)));
        (void)((dyn_pxi = (dyn_pxi + 1)));
      }
    }
    int32_t dyn_pei = (dyn_pend - 1);
    while (((dyn_pei >=0) && (dyn_pew > 0))) {
      int32_t dyn_ped = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_pei);
      if ((dyn_ped > 0)) {
        (void)((dyn_pew = typeck_find_or_alloc_array_type_ref(arena, dyn_pew, dyn_ped)));
      } else {
        (void)((dyn_pew = 0));
      }
      (void)((dyn_pei = (dyn_pei - 1)));
    }
  } else {
    (void)((dyn_pew = 0));
  }
  ((dyn_pew > 0) ? ({   int32_t dyn_pty = typeck_find_or_alloc_ptr_type_ref(arena, dyn_pew);
  ((dyn_pty > 0) ? ({   int32_t dyn_ak9 = pipeline_expr_kind_ord_at(arena, dyn_arg);
  ((dyn_ak9 ==51) ? ({   int32_t dyn_op9 = pipeline_expr_unary_operand_ref_at(arena, dyn_arg);
  if ((dyn_op9 > 0)) {
    (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_op9, dyn_pew));
  }
  (void)(pipeline_expr_set_resolved_type_ref(arena, dyn_arg, dyn_pty));
 }) : ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_pty));
 }));
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (((dyn_arg > 0) && (dyn_pk ==10))) {
      int32_t dyn_aek = xlang_skip_trait_method_param_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
      int32_t dyn_alf = 0;
      if (((((((dyn_aek >=0) && (dyn_aek !=8)) && (dyn_aek !=9)) && (dyn_aek !=10)) && (dyn_aek !=11)) && (dyn_aek !=13))) {
        (void)((dyn_alf = pipeline_type_ensure_by_kind_ord(arena, dyn_aek)));
      }
      if (((dyn_alf ==0) && (dyn_aek ==8))) {
        uint8_t dyn_apnm[64] = {};
        int32_t dyn_apnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_apnm)[0]));
        ((dyn_apnl > 0) ? ({   (void)((dyn_alf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_apnm)[0]), dyn_apnl)));
 }) : 0);
      }
      if (((dyn_alf ==0) && (dyn_aek ==11))) {
        int32_t dyn_aseek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
        int32_t dyn_aslf = 0;
        if (((((((dyn_aseek >=0) && (dyn_aseek !=8)) && (dyn_aseek !=9)) && (dyn_aseek !=10)) && (dyn_aseek !=11)) && (dyn_aseek !=13))) {
          (void)((dyn_aslf = pipeline_type_ensure_by_kind_ord(arena, dyn_aseek)));
        }
        if (((dyn_aslf ==0) && (dyn_aseek ==8))) {
          uint8_t dyn_asnm[64] = {};
          int32_t dyn_asnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_asnm)[0]));
          ((dyn_asnl > 0) ? ({   (void)((dyn_aslf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_asnm)[0]), dyn_asnl)));
 }) : 0);
        }
        ((dyn_aslf > 0) ? ({   int32_t dyn_asaw = dyn_aslf;
  int32_t dyn_asand = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  if ((dyn_asand ==0)) {
    int32_t dyn_aspx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    ((dyn_aspx > 0) ? ({   int32_t dyn_aspi = 0;
  while (((dyn_aspi < dyn_aspx) && (dyn_asaw > 0))) {
    (void)((dyn_asaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_asaw)));
    (void)((dyn_aspi = (dyn_aspi + 1)));
  }
 }) : 0);
  }
  if ((dyn_asand ==-2)) {
    int32_t dyn_aspx2 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 1);
    ((dyn_aspx2 > 0) ? ({   int32_t dyn_aspi2 = 0;
  while (((dyn_aspi2 < dyn_aspx2) && (dyn_asaw > 0))) {
    (void)((dyn_asaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_asaw)));
    (void)((dyn_aspi2 = (dyn_aspi2 + 1)));
  }
 }) : 0);
  }
  if ((dyn_asand >=1)) {
    int32_t dyn_aspx3 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_asand);
    ((dyn_aspx3 > 0) ? ({   int32_t dyn_aspi3 = 0;
  while (((dyn_aspi3 < dyn_aspx3) && (dyn_asaw > 0))) {
    (void)((dyn_asaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_asaw)));
    (void)((dyn_aspi3 = (dyn_aspi3 + 1)));
  }
 }) : 0);
  }
  if ((dyn_asand >=1)) {
    int32_t dyn_asex3 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_asand + 1));
    ((dyn_asex3 > 0) ? ({   int32_t dyn_asxi3 = 0;
  while (((dyn_asxi3 < dyn_asex3) && (dyn_asaw > 0))) {
    (void)((dyn_asaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_asaw)));
    (void)((dyn_asxi3 = (dyn_asxi3 + 1)));
  }
 }) : 0);
  }
  if ((dyn_asand >=1)) {
    int32_t dyn_asai = (dyn_asand - 1);
    while (((dyn_asai >=0) && (dyn_asaw > 0))) {
      int32_t dyn_asad = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_asai);
      if ((dyn_asad > 0)) {
        (void)((dyn_asaw = typeck_find_or_alloc_array_type_ref(arena, dyn_asaw, dyn_asad)));
      } else {
        (void)((dyn_asaw = 0));
      }
      (void)((dyn_asai = (dyn_asai - 1)));
    }
  }
  (void)((dyn_alf = typeck_find_or_alloc_slice_type_ref(arena, dyn_asaw)));
  ((dyn_alf > 0) ? ({   ((dyn_asand ==-2) ? ({   int32_t dyn_asex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
  if ((dyn_asex < 1)) {
    (void)((dyn_asex = 1));
  }
  int32_t dyn_asi = 0;
  while (((dyn_asi < dyn_asex) && (dyn_alf > 0))) {
    (void)((dyn_alf = typeck_find_or_alloc_slice_type_ref(arena, dyn_alf)));
    (void)((dyn_asi = (dyn_asi + 1)));
  }
 }) : 0);
 }) : 0);
 }) : 0);
      }
      if (((dyn_alf ==0) && (dyn_aek ==9))) {
        int32_t dyn_aeek = xlang_skip_trait_method_param_elem_elem_kind_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
        int32_t dyn_aplf = 0;
        if (((((((dyn_aeek >=0) && (dyn_aeek !=8)) && (dyn_aeek !=9)) && (dyn_aeek !=10)) && (dyn_aeek !=11)) && (dyn_aeek !=13))) {
          (void)((dyn_aplf = pipeline_type_ensure_by_kind_ord(arena, dyn_aeek)));
        }
        if (((dyn_aplf ==0) && (dyn_aeek ==8))) {
          uint8_t dyn_apnm[64] = {};
          int32_t dyn_apnl = xlang_skip_trait_method_param_name_into_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), &((dyn_apnm)[0]));
          ((dyn_apnl > 0) ? ({   (void)((dyn_aplf = typeck_find_or_alloc_named_type_ref(arena, &((dyn_apnm)[0]), dyn_apnl)));
 }) : 0);
        }
        ((dyn_aplf > 0) ? ({   int32_t dyn_aand = xlang_skip_trait_method_param_elem_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  ((dyn_aand !=0) ? ({   int32_t dyn_apaw = dyn_aplf;
  if ((dyn_aand ==-2)) {
    int32_t dyn_apex = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    if ((dyn_apex < 1)) {
      (void)((dyn_apex = 1));
    }
    int32_t dyn_api = 0;
    while (((dyn_api < dyn_apex) && (dyn_apaw > 0))) {
      (void)((dyn_apaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_apaw)));
      (void)((dyn_api = (dyn_api + 1)));
    }
  } else {
    if ((dyn_aand >=1)) {
      int32_t dyn_appx = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), (dyn_aand + 1));
      if ((dyn_appx > 0)) {
        int32_t dyn_appi = 0;
        while (((dyn_appi < dyn_appx) && (dyn_apaw > 0))) {
          (void)((dyn_apaw = typeck_find_or_alloc_ptr_type_ref(arena, dyn_apaw)));
          (void)((dyn_appi = (dyn_appi + 1)));
        }
      }
      int32_t dyn_apex2 = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_aand);
      if ((dyn_apex2 > 0)) {
        int32_t dyn_api2 = 0;
        while (((dyn_api2 < dyn_apex2) && (dyn_apaw > 0))) {
          (void)((dyn_apaw = typeck_find_or_alloc_slice_type_ref(arena, dyn_apaw)));
          (void)((dyn_api2 = (dyn_api2 + 1)));
        }
      }
      int32_t dyn_apai = (dyn_aand - 1);
      while (((dyn_apai >=0) && (dyn_apaw > 0))) {
        int32_t dyn_apad = xlang_skip_trait_method_param_elem_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_apai);
        if ((dyn_apad > 0)) {
          (void)((dyn_apaw = typeck_find_or_alloc_array_type_ref(arena, dyn_apaw, dyn_apad)));
        } else {
          (void)((dyn_apaw = 0));
        }
        (void)((dyn_apai = (dyn_apai - 1)));
      }
    }
  }
  ((dyn_apaw > 0) ? ({   (void)((dyn_alf = typeck_find_or_alloc_ptr_type_ref(arena, dyn_apaw)));
 }) : 0);
 }) : 0);
 }) : 0);
      }
      ((dyn_alf > 0) ? ({   int32_t dyn_and = xlang_skip_trait_method_param_array_ndims_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1));
  int32_t dyn_aty = 0;
  if ((dyn_and >=2)) {
    int32_t dyn_ai = (dyn_and - 1);
    int32_t dyn_aw = dyn_alf;
    while (((dyn_ai >=0) && (dyn_aw > 0))) {
      int32_t dyn_ad = xlang_skip_trait_method_param_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), dyn_ai);
      if ((dyn_ad > 0)) {
        (void)((dyn_aw = typeck_find_or_alloc_array_type_ref(arena, dyn_aw, dyn_ad)));
      } else {
        (void)((dyn_aw = 0));
      }
      (void)((dyn_ai = (dyn_ai - 1)));
    }
    (void)((dyn_aty = dyn_aw));
  } else {
    int32_t dyn_ad1 = xlang_skip_trait_method_param_array_dim_c(&((dyn_trait_nm)[0]), dyn_trait_nlen, dyn_slot, (arg_i + 1), 0);
    ((dyn_ad1 > 0) ? ({   (void)((dyn_aty = typeck_find_or_alloc_array_type_ref(arena, dyn_alf, dyn_ad1)));
 }) : 0);
  }
  ((dyn_aty > 0) ? ({   (void)(typeck_coerce_init_expr_to_decl(module, arena, dyn_arg, dyn_aty));
 }) : 0);
 }) : 0);
    }
    (void)((arg_i = (arg_i + 1)));
  }
  return 0;
 }) : 0);
    }
    (void)((num_args = pipeline_expr_method_call_num_args_at(arena, expr_ref)));
    (void)((arg_i = 0));
    while ((arg_i < num_args)) {
      int32_t arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, arg_i);
      if ((typeck_check_expr(module, arena, arg_ref, return_type_ref, ctx) !=0)) {
        return -1;
      }
      (void)((arg_i = (arg_i + 1)));
    }
    /* 10.3.3 slice3: Cap/TYPE_FN field METHOD_CALL (twin of typeck.x). */
    if (((base_ty > 0) && (method_nlen > 0))) {
      int32_t ff_ty = typeck_method_call_field_fnptr_ty(module, arena, ctx, base_ty, &((method_nm)[0]),
          method_nlen);
      if ((ff_ty > 0)) {
        int32_t ff_ret = 0;
        int32_t ff_ko = pipeline_type_kind_ord_at(arena, ff_ty);
        int32_t ff_er = 0;
        int32_t ff_expect = 0;
        if ((ff_ko == 18)) {
          ff_er = pipeline_type_elem_ref_at(arena, ff_ty);
          if ((ff_er > 0)) {
            ff_ret = ff_er;
          }
        }
        if ((ff_ret <= 0)) {
          ff_expect = typeck_i32_ptr_read(typeck_overload_expected_ret_slot());
          if (((ff_expect <= 0) && (return_type_ref > 0))) {
            ff_expect = return_type_ref;
          }
          if ((ff_expect > 0)) {
            ff_ret = ff_expect;
          } else {
            ff_ret = typeck_ensure_i32_type_ref(arena);
          }
        }
        if ((ff_ret > 0)) {
          pipeline_expr_set_resolved_type_ref(arena, expr_ref, ff_ret);
          return 0;
        }
      }
    }
    (void)((expect_store = 0));
    if ((return_type_ref > 0)) {
      (void)((expect_store = return_type_ref));
    }
    (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), expect_store));
    (void)((dep_ix = -1));
    (void)((func_ix = -1));
    (void)((import_ret_ty = 0));
    if (((ctx !=0) && (base_kind ==ord_var))) {
      (void)((base_nlen = pipeline_expr_var_name_len(arena, base_ref)));
      (((base_nlen > 0) && (base_nlen <=127)) ? ({   (void)(pipeline_expr_var_name_into(arena, base_ref, &((base_nm)[0])));
  (void)((n_imp = typeck_module_num_imports(module)));
  (void)((ii = 0));
  while ((ii < n_imp)) {
    if (((pipeline_module_import_kind_at(module, ii) ==ord_import_binding) && typeck_import_binding_name_equal(module, ii, &((base_nm)[0]), base_nlen))) {
      (void)((dep_slot = typeck_resolve_dep_index_for_import(module, ctx, ii)));
      (void)((func_ix = -1));
      if ((dep_slot >=0)) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_slot)));
        (((dm !=0) && (pipeline_module_num_funcs(dm) > 0)) ? ({   (void)((import_ret_ty = pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(dm, arena, &((method_nm)[0]), method_nlen, dep_slot, num_args, expr_ref, 1, ctx, &(func_ix))));
  ((import_ret_ty > 0) ? ({   (void)((dep_ix = dep_slot));
 }) : 0);
 }) : 0);
      }
      if ((import_ret_ty <=0)) {
        int32_t try_di = 0;
        int32_t nd = pipeline_dep_ctx_ndep(ctx);
        while (((try_di < nd) && (import_ret_ty <=0))) {
          struct ast_Module * try_dm = 0;
          int32_t try_fn = -1;
          int32_t try_ret = 0;
          if ((try_di !=dep_slot)) {
            (void)((try_dm = pipeline_dep_ctx_module_at(ctx, try_di)));
            (((try_dm !=0) && (pipeline_module_num_funcs(try_dm) > 0)) ? ({   (void)((try_ret = pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(try_dm, arena, &((method_nm)[0]), method_nlen, try_di, num_args, expr_ref, 1, ctx, &(try_fn))));
  ((try_ret > 0) ? ({   (void)((import_ret_ty = try_ret));
  (void)((dep_ix = try_di));
  (void)((func_ix = try_fn));
 }) : 0);
 }) : 0);
          }
          (void)((try_di = (try_di + 1)));
        }
      }
      break;
    }
    (void)((ii = (ii + 1)));
  }
 }) : 0);
    }
    (void)(typeck_i32_ptr_store(typeck_overload_expected_ret_slot(), 0));
    if ((import_ret_ty > 0)) {
      struct ast_Module * cm = module;
      if (((dep_ix >=0) && (ctx !=0))) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_ix)));
        ((dm !=0) ? ({   (void)((cm = dm));
 }) : 0);
      }
      (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, dep_ix, func_ix));
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, import_ret_ty));
      (void)(typeck_stamp_resolved_args_float_lit(arena, expr_ref, cm, func_ix, dep_ix, ctx, 0));
      if ((typeck_check_call_arg_types(module, arena, expr_ref, ctx) !=0)) {
        return -1;
      }
      return 0;
    }
    if (((base_ty > 0) && (method_nlen > 0))) {
      ((typeck_method_call_generic_ufcs(module, arena, expr_ref, base_ty, &((method_nm)[0]), method_nlen, num_args) !=0) ? ({   return 0;
 }) : 0);
    }
    if (((base_ty > 0) && (method_nlen > 0))) {
      int32_t uj = 0;
      int32_t uf_best = -1;
      int32_t uf_best_score = -1;
      int32_t saw_simd_mismatch = 0;
      int32_t nf = pipeline_module_num_funcs(module);
      while ((uj < nf)) {
        int32_t nparams = 0;
        int32_t score = 0;
        int32_t matched = 1;
        int32_t p0 = 0;
        int32_t sc0 = -1;
        int32_t ai = 0;
        int32_t simd_recv_refuse = 0;
        if ((pipeline_module_func_name_equal_at(module, uj, &((method_nm)[0]), method_nlen) !=0)) {
          (void)((nparams = pipeline_module_func_num_params_at(module, uj)));
          ((nparams ==(num_args + 1)) ? ({   (void)((p0 = pipeline_module_func_param_type_ref_at(module, uj, 0)));
  (void)((sc0 = -1));
  (void)((simd_recv_refuse = 0));
  if (((p0 > 0) && (base_ref > 0))) {
    int32_t crc0 = typeck_coerce_init_array_vector_lit_to_decl(module, arena, base_ref, p0, pipeline_type_kind_ord_at(arena, p0), pipeline_expr_kind_ord_at(arena, base_ref));
    int32_t bk0 = pipeline_expr_kind_ord_at(arena, base_ref);
    ((((crc0 ==0) && (bk0 ==46)) && (typeck_vector_lanes_of_type(arena, p0) > 0)) ? ({   (void)((simd_recv_refuse = 1));
  (void)((saw_simd_mismatch = 1));
 }) : ({   (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
 }));
  }
  if ((((simd_recv_refuse ==0) && (p0 > 0)) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, base_ty, p0) !=0))) {
    (void)((sc0 = 1000));
  }
  if (((((simd_recv_refuse ==0) && (sc0 < 0)) && (p0 > 0)) && (pipeline_type_kind_ord_at(arena, p0) ==ord_ptr))) {
    int32_t pe = pipeline_type_elem_ref_at(arena, p0);
    (((pe > 0) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, base_ty, pe) !=0)) ? ({   (void)((sc0 = 900));
 }) : 0);
  }
  if ((((simd_recv_refuse ==0) && (sc0 < 0)) && (p0 > 0))) {
    int32_t ak = pipeline_type_kind_ord_at(arena, base_ty);
    int32_t pk = pipeline_type_kind_ord_at(arena, p0);
    (((((((((pk ==0) || (pk ==2)) || (pk ==3)) || (pk ==4)) || (pk ==5)) || (pk ==6)) || (pk ==7)) && (((((((ak ==0) || (ak ==2)) || (ak ==3)) || (ak ==4)) || (ak ==5)) || (ak ==6)) || (ak ==7))) ? ({   ((((pk ==ak) || ((ak ==0) && (((pk ==5) || (pk ==6)) || (pk ==7)))) || ((ak ==2) && ((((pk ==0) || (pk ==3)) || (pk ==4)) || (pk ==6)))) ? ({   (void)((sc0 = 100));
 }) : 0);
 }) : 0);
  }
  ((sc0 >=0) ? ({   (void)((score = sc0));
  (void)((matched = 1));
  (void)((ai = 0));
  while ((ai < num_args)) {
    int32_t param_raw = pipeline_module_func_param_type_ref_at(module, uj, (ai + 1));
    int32_t arg_ref2 = pipeline_expr_method_call_arg_ref(arena, expr_ref, ai);
    int32_t arg_ty = 0;
    int32_t crc_a = 0;
    if (((arg_ref2 > 0) && (param_raw > 0))) {
      (void)((crc_a = typeck_coerce_init_array_vector_lit_to_decl(module, arena, arg_ref2, param_raw, pipeline_type_kind_ord_at(arena, param_raw), pipeline_expr_kind_ord_at(arena, arg_ref2))));
      if ((((crc_a ==0) && (pipeline_expr_kind_ord_at(arena, arg_ref2) ==46)) && (typeck_vector_lanes_of_type(arena, param_raw) > 0))) {
        (void)((saw_simd_mismatch = 1));
        (void)((matched = 0));
        break;
      }
      (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, arg_ref2, param_raw));
      (void)(typeck_coerce_init_struct_lit_to_decl(module, arena, arg_ref2, param_raw));
    }
    if ((arg_ref2 > 0)) {
      (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref2)));
    }
    if ((((param_raw <=0) || (arg_ty <=0)) || (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, arg_ty, param_raw) ==0))) {
      (void)((matched = 0));
      break;
    }
    (void)((score = (score + 1000)));
    (void)((ai = (ai + 1)));
  }
  (((matched !=0) && (score > uf_best_score)) ? ({   (void)((uf_best_score = score));
  (void)((uf_best = uj));
 }) : 0);
 }) : 0);
 }) : 0);
        }
        (void)((uj = (uj + 1)));
      }
      if ((uf_best >=0)) {
        int32_t uf_ret = pipeline_module_func_return_type_at(module, uf_best);
        ((uf_ret > 0) ? ({   (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, -1, uf_best));
  (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, uf_ret));
  (void)(typeck_stamp_resolved_args_float_lit(arena, expr_ref, module, uf_best, -1, ctx, 1));
  return 0;
 }) : 0);
      }
      ((saw_simd_mismatch !=0) ? ({   (void)((line = pipeline_expr_line_at(arena, expr_ref)));
  (void)((col = pipeline_expr_col_at(arena, expr_ref)));
  (void)(driver_diagnostic_typeck_call_arg_type_mismatch(line, col));
  return -1;
 }) : 0);
    }
    if (((base_ty > 0) && (method_nlen > 0))) {
      ((typeck_method_call_resolve_generic_bound(module, arena, expr_ref, ctx, base_ty, &((method_nm)[0]), method_nlen, num_args) !=0) ? ({   return 0;
 }) : 0);
    }
    if ((ret_ty > 0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, ret_ty));
      return 0;
    }
    /*
     * Associated Type.method(): receiver is a type name. check_expr(VAR) fails
     * because the name is not a value. `P.mk()` / `P.id(7)` / `P.get(p)`
     * resolve to a same-module func with nparams == num_args (no implicit self).
     * Instance `p.get()` already matched UFCS nparams == num_args+1 above.
     * PLATFORM: SHARED — G.7 complete typeck_check_expr_method_call;
     * authority twin compiler/src/typeck/typeck.x.
     */
    if (((base_kind == ord_var) && (method_nlen > 0)) && (base_rc != 0)) {
      int32_t assoc_nlen = pipeline_expr_var_name_len(arena, base_ref);
      if ((assoc_nlen > 0) && (assoc_nlen <= 127)) {
        pipeline_expr_var_name_into(arena, base_ref, &((base_nm)[0]));
        if (typeck_soa_find_layout_idx_by_name(module, &((base_nm)[0]), assoc_nlen) >= 0) {
          int32_t assoc_uj = 0;
          int32_t assoc_best = -1;
          int32_t assoc_best_score = -1;
          int32_t assoc_nf = pipeline_module_num_funcs(module);
          while (assoc_uj < assoc_nf) {
            if (pipeline_module_func_name_equal_at(module, assoc_uj, &((method_nm)[0]), method_nlen) != 0) {
              int32_t assoc_np = pipeline_module_func_num_params_at(module, assoc_uj);
              if (assoc_np == num_args) {
                int32_t assoc_matched = 1;
                int32_t assoc_score = 1;
                int32_t assoc_ai = 0;
                while (assoc_ai < num_args) {
                  int32_t assoc_param = pipeline_module_func_param_type_ref_at(module, assoc_uj, assoc_ai);
                  int32_t assoc_arg = pipeline_expr_method_call_arg_ref(arena, expr_ref, assoc_ai);
                  int32_t assoc_arg_ty = 0;
                  if ((assoc_arg > 0) && (assoc_param > 0)) {
                    (void)typeck_coerce_init_array_vector_lit_to_decl(module, arena, assoc_arg, assoc_param,
                        pipeline_type_kind_ord_at(arena, assoc_param),
                        pipeline_expr_kind_ord_at(arena, assoc_arg));
                    (void)typeck_coerce_array_lit_struct_elems_to_decl(module, arena, assoc_arg, assoc_param);
                    (void)typeck_coerce_init_struct_lit_to_decl(module, arena, assoc_arg, assoc_param);
                    assoc_arg_ty = pipeline_expr_resolved_type_ref(arena, assoc_arg);
                  }
                  if ((((assoc_param <= 0) || (assoc_arg_ty <= 0)) ||
                       (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, assoc_arg_ty, assoc_param) == 0))) {
                    assoc_matched = 0;
                    assoc_ai = num_args;
                  } else {
                    assoc_score = assoc_score + 1000;
                    assoc_ai = assoc_ai + 1;
                  }
                }
                if (assoc_matched != 0) {
                  int32_t assoc_ret = pipeline_module_func_return_type_at(module, assoc_uj);
                  if ((assoc_ret > 0) && (pipeline_type_kind_ord_at(arena, assoc_ret) == 8)) {
                    uint8_t assoc_rnm[128] = {};
                    int32_t assoc_rnlen = pipeline_type_named_name_into(arena, assoc_ret, &((assoc_rnm)[0]));
                    if ((assoc_rnlen == assoc_nlen) && (assoc_rnlen > 0)) {
                      int32_t assoc_eq = 1;
                      int32_t assoc_bi = 0;
                      while (assoc_bi < assoc_rnlen) {
                        if (assoc_rnm[assoc_bi] != base_nm[assoc_bi]) {
                          assoc_eq = 0;
                          assoc_bi = assoc_rnlen;
                        } else {
                          assoc_bi = assoc_bi + 1;
                        }
                      }
                      if (assoc_eq != 0) {
                        assoc_score = assoc_score + 100;
                      }
                    }
                  }
                  if (assoc_score > assoc_best_score) {
                    assoc_best_score = assoc_score;
                    assoc_best = assoc_uj;
                  }
                }
              }
            }
            assoc_uj = assoc_uj + 1;
          }
          if (assoc_best >= 0) {
            int32_t assoc_ok_ret = pipeline_module_func_return_type_at(module, assoc_best);
            if (assoc_ok_ret > 0) {
              (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, -1, assoc_best));
              (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, assoc_ok_ret));
              (void)(typeck_stamp_resolved_args_float_lit(arena, expr_ref, module, assoc_best, -1, ctx, 0));
              return 0;
            }
          }
        }
      }
    }
    if ((base_rc !=0)) {
      return -1;
    }
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)((z = 0));
    while ((z < 256)) {
      (void)(((msg)[z] = 0));
      (void)((z = (z + 1)));
    }
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x6e\x6f\x20\x69\x6d\x70\x6c\x20\x66\x6f\x72\x20\x74\x79\x70\x65\x20\x77\x69\x74\x68\x20\x6d\x65\x74\x68\x6f\x64\x20"), 29)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((method_nm)[0]), method_nlen)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t typeck_as_cast_type_class_ok(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    int32_t ord_bool = 1;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_void = 16;
    int32_t ko = 0;
    int32_t rty = 0;
    if ((((module ==0) || (arena ==0)) || ast_ref_is_null(ty_ref))) {
      return 0;
    }
    if ((typeck_type_is_aggregate_cmp_operand(module, arena, ty_ref) !=0)) {
      return 0;
    }
    (void)((rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0)));
    if (ast_ref_is_null(rty)) {
      (void)((rty = ty_ref));
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, rty)));
    if ((ko ==ord_void)) {
      return 0;
    }
    /* First-class ints / bool / float / ptr / TYPE_FN (opaque Cap-fn-ptr ABI). */
    if ((((((ko ==ord_bool) || (ko ==ord_ptr)) || (ko ==ord_f32)) || (ko ==ord_f64)) || (ko ==18))) {
      return 1;
    }
    if ((typeck_int_family_id(arena, rty) >=0)) {
      return 1;
    }
    if ((ko ==ord_named)) {
      return 1;
    }
    return 0;
  }
}
int32_t typeck_as_cast_allowed(struct ast_Module * module, struct ast_ASTArena * arena, int32_t src_ty, int32_t tgt_ty) {
  {
    int32_t ord_bool = 1;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t sk = 0;
    int32_t tk = 0;
    int32_t s_int = 0;
    int32_t t_int = 0;
    int32_t s_float = 0;
    int32_t t_float = 0;
    int32_t s_num = 0;
    int32_t t_num = 0;
    int32_t src_r = 0;
    int32_t tgt_r = 0;
    if (((module ==0) || (arena ==0))) {
      return 0;
    }
    if ((ast_ref_is_null(src_ty) || ast_ref_is_null(tgt_ty))) {
      return 0;
    }
    if ((typeck_array_to_slice_ok(arena, src_ty, tgt_ty) !=0)) {
      return 1;
    }
    if (typeck_type_refs_equal(arena, src_ty, tgt_ty)) {
      int32_t sk0 = pipeline_type_kind_ord_at(arena, src_ty);
      (((sk0 ==10) || (sk0 ==11)) ? ({   return 1;
 }) : 0);
    }
    /*
     * 10.3.1: Cap *u8 / TYPE_FN opaque fn-ptr surface ↔ surface (`as function(...)`).
     * Both TYPE_FN → structural sig. Cap↔TYPE_FN soft; bare recover in check_expr_as.
     * PLATFORM: SHARED.
     */
    if (((typeck_is_fnptr_surface(arena, src_ty) !=0) && (typeck_is_fnptr_surface(arena, tgt_ty) !=0))) {
      int32_t sk_fn = pipeline_type_kind_ord_at(arena, src_ty);
      int32_t tk_fn = pipeline_type_kind_ord_at(arena, tgt_ty);
      if (((sk_fn == 18) && (tk_fn == 18))) {
        return typeck_fn_type_sig_equal(arena, src_ty, tgt_ty);
      }
      return 1;
    }
    if (((typeck_as_cast_type_class_ok(module, arena, src_ty) ==0) || (typeck_as_cast_type_class_ok(module, arena, tgt_ty) ==0))) {
      return 0;
    }
    (void)((src_r = typeck_resolve_type_alias_ref_local(module, arena, src_ty, 0)));
    if (ast_ref_is_null(src_r)) {
      (void)((src_r = src_ty));
    }
    (void)((tgt_r = typeck_resolve_type_alias_ref_local(module, arena, tgt_ty, 0)));
    if (ast_ref_is_null(tgt_r)) {
      (void)((tgt_r = tgt_ty));
    }
    if (typeck_type_refs_equal(arena, src_r, tgt_r)) {
      return 1;
    }
    (void)((sk = pipeline_type_kind_ord_at(arena, src_r)));
    (void)((tk = pipeline_type_kind_ord_at(arena, tgt_r)));
    (void)((s_int = 0));
    (void)((t_int = 0));
    if ((((typeck_int_family_id(arena, src_r) >=0) || (sk ==ord_bool)) || (sk ==ord_named))) {
      (void)((s_int = 1));
    }
    if ((((typeck_int_family_id(arena, tgt_r) >=0) || (tk ==ord_bool)) || (tk ==ord_named))) {
      (void)((t_int = 1));
    }
    (void)((s_float = 0));
    (void)((t_float = 0));
    if (((sk ==ord_f32) || (sk ==ord_f64))) {
      (void)((s_float = 1));
    }
    if (((tk ==ord_f32) || (tk ==ord_f64))) {
      (void)((t_float = 1));
    }
    if ((((s_float !=0) && (tk ==ord_ptr)) || ((t_float !=0) && (sk ==ord_ptr)))) {
      return 0;
    }
    (void)((s_num = 0));
    (void)((t_num = 0));
    if (((s_int !=0) || (s_float !=0))) {
      (void)((s_num = 1));
    }
    if (((t_int !=0) || (t_float !=0))) {
      (void)((t_num = 1));
    }
    if (((s_num !=0) && (t_num !=0))) {
      return 1;
    }
    if ((((s_int !=0) && (tk ==ord_ptr)) || ((t_int !=0) && (sk ==ord_ptr)))) {
      return 1;
    }
    if (((sk ==ord_ptr) && (tk ==ord_ptr))) {
      return 1;
    }
    return 0;
  }
}
int32_t typeck_check_expr_as(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t op_ref = pipeline_expr_as_operand_ref_at(arena, expr_ref);
    int32_t tgt = pipeline_expr_as_target_type_ref_at(arena, expr_ref);
    int32_t src_ty = 0;
    int32_t line_as = 0;
    int32_t col_as = 0;
    if ((!(ast_ref_is_null(op_ref)) && (typeck_check_expr(module, arena, op_ref, 0, ctx) !=0))) {
      return -1;
    }
    if ((!(ast_ref_is_null(op_ref)) && !(ast_ref_is_null(tgt)))) {
      (void)((src_ty = pipeline_expr_resolved_type_ref(arena, op_ref)));
      if ((!(ast_ref_is_null(src_ty)) && (typeck_as_cast_allowed(module, arena, src_ty, tgt) ==0))) {
        (void)((line_as = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_as = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_as_cast(line_as, col_as));
        return -1;
      }
      /* 10.3.1: bare Cap as function(...) — recover module sig (≡ typeck.x). */
      if (((!(ast_ref_is_null(src_ty)) && (typeck_is_fnptr_surface(arena, src_ty) != 0))
          && (typeck_is_fnptr_surface(arena, tgt) != 0)
          && (typeck_fnptr_surface_compat(module, arena, tgt, src_ty, op_ref, 1) == 0))) {
        (void)((line_as = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col_as = pipeline_expr_col_at(arena, expr_ref)));
        (void)(driver_diagnostic_typeck_invalid_as_cast(line_as, col_as));
        return -1;
      }
      (((pipeline_expr_kind_ord_at(arena, op_ref) ==46) && (typeck_array_to_slice_ok(arena, src_ty, tgt) !=0)) ? ({   (void)(typeck_coerce_init_slice_from_array(arena, op_ref, tgt, 11));
 }) : 0);
    }
    if (!(ast_ref_is_null(tgt))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tgt));
    }
    return 0;
  }
}
int32_t typeck_check_expr_struct_lit_field(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t field_i, int32_t num_fields) {
  {
    int32_t init_sl = 0;
    int32_t no_expected = 0;
    if ((field_i >=num_fields)) {
      return 0;
    }
    (void)((init_sl = pipeline_expr_struct_lit_init_ref(arena, expr_ref, field_i)));
    if ((!(ast_ref_is_null(init_sl)) && (typeck_check_expr(module, arena, init_sl, no_expected, ctx) !=0))) {
      return -1;
    }
    return typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx, (field_i + 1), num_fields);
  }
}
int32_t typeck_coerce_struct_lit_field_inits_to_layout(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty) {
  {
    int32_t num_fields = 0;
    int32_t name_len = 0;
    int32_t j = 0;
    int32_t flen = 0;
    int32_t init_r = 0;
    int32_t ftr = 0;
    int32_t ftr_mono = 0;
    int32_t ftr_kind = 0;
    int32_t init_kind = 0;
    int32_t init_ty = 0;
    int32_t got_kind = 0;
    int32_t crc = 0;
    int32_t mono_base = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    int32_t err_line = 0;
    int32_t err_col = 0;
    uint8_t * name_buf = typeck_scratch64_slot(4);
    uint8_t * field_buf = typeck_scratch64_slot(5);
    if (((expr_ref <=0) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref)));
    (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
    if ((((num_fields <=0) || (name_len <=0)) || (name_len > 127))) {
      return 0;
    }
    (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, name_buf));
    (void)((mono_base = 0));
    if (((!(ast_ref_is_null(base_ty)) && (base_ty > 0)) && (base_ty <=((arena)->num_types)))) {
      (typeck_named_type_matches_name_or_alias(module, arena, base_ty, name_buf, name_len, 0) ? ({   (void)((mono_base = base_ty));
 }) : ({   int32_t peel = pipeline_type_elem_ref_at(arena, base_ty);
  (((!(ast_ref_is_null(peel)) && (peel > 0)) && typeck_named_type_matches_name_or_alias(module, arena, peel, name_buf, name_len, 0)) ? ({   (void)((mono_base = peel));
 }) : 0);
 }));
    }
    while ((j < num_fields)) {
      (void)((flen = pipeline_expr_struct_lit_field_name_len(arena, expr_ref, j)));
      if (((flen > 0) && (flen <=127))) {
        (void)(pipeline_expr_struct_lit_field_name_into(arena, expr_ref, j, field_buf));
        (void)((ftr = typeck_get_field_type_ref_from_layout(module, name_buf, name_len, field_buf, flen)));
        (void)((init_r = pipeline_expr_struct_lit_init_ref(arena, expr_ref, j)));
        (((((!(ast_ref_is_null(init_r)) && (init_r > 0)) && (init_r <=((arena)->num_exprs))) && !(ast_ref_is_null(ftr))) && (ftr > 0)) ? ({   if ((mono_base > 0)) {
    (void)((ftr_mono = typeck_mono_field_type_from_base(module, arena, ftr, mono_base)));
    ((ftr_mono > 0) ? ({   (void)((ftr = ftr_mono));
 }) : 0);
  }
  (void)((ftr_kind = pipeline_type_kind_ord_at(arena, ftr)));
  (void)((init_kind = pipeline_expr_kind_ord_at(arena, init_r)));
  (void)(typeck_coerce_init_lit_to_decl(arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_float_lit_to_decl(arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_enum_field_to_decl(module, arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_named_call_to_decl(arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_resolved_alias_to_decl(module, arena, init_r, ftr, ftr_kind));
  (void)((crc = typeck_coerce_init_array_vector_lit_to_decl(module, arena, init_r, ftr, ftr_kind, init_kind)));
  if ((crc < 0)) {
    return -1;
  }
  if ((init_kind ==46)) {
    (void)(typeck_coerce_array_lit_struct_elems_to_decl(module, arena, init_r, ftr));
  }
  (void)(typeck_coerce_init_vector_binop_to_decl(arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_int_binop_to_decl(arena, init_r, ftr, ftr_kind, init_kind));
  (void)(typeck_coerce_init_slice_from_array(arena, init_r, ftr, ftr_kind));
  (void)((crc = typeck_coerce_init_struct_lit_to_decl(module, arena, init_r, ftr)));
  (void)((init_ty = typeck_expr_type_ref(arena, init_r)));
  ((crc !=0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, init_r, ftr));
 }) : ((!(ast_ref_is_null(init_ty)) && (init_ty > 0)) ? ({   (void)((got_kind = pipeline_type_kind_ord_at(arena, init_ty)));
  (((typeck_type_refs_equal(arena, ftr, init_ty) || typeck_integer_widen_ok_refs(arena, ftr, init_ty)) || typeck_float_widen_ok(ftr_kind, got_kind) || (typeck_fnptr_surface_compat(module, arena, ftr, init_ty, init_r, 0) !=0)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, init_r, ftr));
 }) : ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, ftr, eb, 96)));
  (void)((gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96)));
  (void)((err_line = pipeline_expr_line_at(arena, init_r)));
  (void)((err_col = pipeline_expr_col_at(arena, init_r)));
  (void)(driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl));
  return -1;
 }));
 }) : 0));
 }) : 0);
      }
      (void)((j = (j + 1)));
    }
    return 0;
  }
}
int32_t typeck_check_expr_struct_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t num_fields = pipeline_expr_struct_lit_num_fields(arena, expr_ref);
    int32_t name_len = 0;
    uint8_t name_buf[128] = {};
    int32_t tr = 0;
    int32_t ord_named = 8;
    (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
    if ((typeck_check_expr_struct_lit_field(module, arena, expr_ref, return_type_ref, ctx, 0, num_fields) !=0)) {
      return -1;
    }
    if ((name_len <=0)) {
      if ((!(ast_ref_is_null(return_type_ref)) && (pipeline_type_kind_ord_at(arena, return_type_ref) ==ord_named))) {
        int32_t resolved_ref = typeck_resolve_type_alias_ref_local(module, arena, return_type_ref, 0);
        if ((!(ast_ref_is_null(resolved_ref)) && (pipeline_type_kind_ord_at(arena, resolved_ref) ==ord_named))) {
          uint8_t backfill_name[128] = {};
          int32_t backfill_len = pipeline_type_named_name_into(arena, resolved_ref, &((backfill_name)[0]));
          (((backfill_len > 0) && (backfill_len <=127)) ? ({   (void)(pipeline_expr_struct_lit_type_name_set(arena, expr_ref, &((backfill_name)[0]), backfill_len));
 }) : 0);
        }
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
      }
      (void)((name_len = pipeline_expr_struct_lit_type_name_len(arena, expr_ref)));
      if ((name_len > 0)) {
        if ((typeck_ensure_struct_layout_from_struct_lit(module, arena, expr_ref) !=0)) {
          return -1;
        }
        ((typeck_coerce_struct_lit_field_inits_to_layout(module, arena, expr_ref, return_type_ref) !=0) ? ({   return -1;
 }) : 0);
      }
      return 0;
    }
    if ((typeck_ensure_struct_layout_from_struct_lit(module, arena, expr_ref) !=0)) {
      return -1;
    }
    if ((typeck_coerce_struct_lit_field_inits_to_layout(module, arena, expr_ref, return_type_ref) !=0)) {
      return -1;
    }
    if ((name_len > 127)) {
      return 0;
    }
    (void)(pipeline_expr_struct_lit_type_name_into(arena, expr_ref, &((name_buf)[0])));
    (void)((tr = typeck_find_or_alloc_named_type_ref(arena, &((name_buf)[0]), name_len)));
    if ((tr !=0)) {
      (((!(ast_ref_is_null(return_type_ref)) && (pipeline_type_kind_ord_at(arena, return_type_ref) ==ord_named)) && typeck_named_type_matches_name_or_alias(module, arena, return_type_ref, &((name_buf)[0]), name_len, 0)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
 }) : ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, tr));
 }));
    }
    return 0;
  }
}
int32_t typeck_vector_elem_type_ref(struct ast_ASTArena * arena, int32_t type_ref) {
  {
    int32_t ord_type_vector = 13;
    int32_t ord_type_named = 8;
    int32_t tk = 0;
    int32_t er = 0;
    uint8_t nm[128] = {};
    int32_t nlen = 0;
    if ((ast_ref_is_null(type_ref) || (type_ref <=0))) {
      return 0;
    }
    if ((typeck_vector_lanes_of_type(arena, type_ref) <=0)) {
      return 0;
    }
    (void)((tk = pipeline_type_kind_ord_at(arena, type_ref)));
    (void)((er = pipeline_type_elem_ref_at(arena, type_ref)));
    if (((!(ast_ref_is_null(er)) && (er > 0)) && (er <=((arena)->num_types)))) {
      return er;
    }
    if ((tk ==ord_type_vector)) {
      return typeck_ensure_i32_type_ref(arena);
    }
    if ((tk !=ord_type_named)) {
      return 0;
    }
    (void)((nlen = pipeline_type_named_name_into(arena, type_ref, &((nm)[0]))));
    if ((nlen <=0)) {
      return typeck_ensure_i32_type_ref(arena);
    }
    if (((((nlen >=3) && ((nm)[0] ==102)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
      return typeck_ensure_f32_type_ref(arena);
    }
    if (((((nlen >=3) && ((nm)[0] ==102)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
      return typeck_ensure_f64_type_ref(arena);
    }
    if (((((((nlen ==5) && ((nm)[0] ==86)) && ((nm)[1] ==101)) && ((nm)[2] ==99)) && ((nm)[3] ==52)) && ((nm)[4] ==102))) {
      return typeck_ensure_f32_type_ref(arena);
    }
    if (((((nlen >=3) && ((nm)[0] ==105)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
      return typeck_ensure_i64_type_ref(arena);
    }
    if (((((nlen >=3) && ((nm)[0] ==117)) && ((nm)[1] ==54)) && ((nm)[2] ==52))) {
      return typeck_ensure_primitive_by_kind_ord(arena, 4);
    }
    if (((((nlen >=3) && ((nm)[0] ==117)) && ((nm)[1] ==51)) && ((nm)[2] ==50))) {
      return typeck_ensure_primitive_by_kind_ord(arena, 3);
    }
    if ((((nlen >=2) && ((nm)[0] ==117)) && ((nm)[1] ==56))) {
      return typeck_ensure_u8_type_ref(arena);
    }
    return typeck_ensure_i32_type_ref(arena);
  }
}
int32_t typeck_type_is_valid_subscript_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t ty_ref) {
  {
    int32_t ord_i32 = 0;
    int32_t ord_bool = 1;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_named = 8;
    int32_t rty = 0;
    int32_t ko = 0;
    if ((((arena ==0) || ast_ref_is_null(ty_ref)) || (ty_ref <=0))) {
      return 1;
    }
    (void)((rty = ty_ref));
    if ((module !=0)) {
      (void)((rty = typeck_resolve_type_alias_ref_local(module, arena, ty_ref, 0)));
      ((ast_ref_is_null(rty) || (rty <=0)) ? ({   (void)((rty = ty_ref));
 }) : 0);
    }
    (void)((ko = pipeline_type_kind_ord_at(arena, rty)));
    if ((((((((ko ==ord_i32) || (ko ==ord_u8)) || (ko ==ord_u32)) || (ko ==ord_u64)) || (ko ==ord_i64)) || (ko ==ord_usize)) || (ko ==ord_isize))) {
      return 1;
    }
    if ((ko ==ord_named)) {
      if ((typeck_type_is_aggregate_cmp_operand(module, arena, rty) !=0)) {
        return 0;
      }
      return 1;
    }
    if ((ko ==ord_bool)) {
      return 0;
    }
    return 0;
  }
}
int32_t typeck_check_expr_index(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_lit = 0;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_vector = 13;
    int32_t base_ref = pipeline_expr_index_base_ref(arena, expr_ref);
    int32_t index_ref = pipeline_expr_index_index_ref(arena, expr_ref);
    int32_t line = pipeline_expr_line_at(arena, expr_ref);
    int32_t col = pipeline_expr_col_at(arena, expr_ref);
    int32_t base_ty = 0;
    int32_t bt_kind = 0;
    int32_t elem_ty = 0;
    int32_t array_sz = 0;
    int32_t vec_lanes = 0;
    int32_t is_vec_base = 0;
    int32_t index_ty = 0;
    int32_t idx_ambient = typeck_ensure_i32_type_ref(arena);
    if ((typeck_check_expr(module, arena, base_ref, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if ((typeck_check_expr(module, arena, index_ref, idx_ambient, ctx) !=0)) {
      return -1;
    }
    if (((ast_ref_is_null(base_ref) || (base_ref <=0)) || (base_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((base_ty = pipeline_expr_resolved_type_ref(arena, base_ref)));
    if (((ast_ref_is_null(base_ty) || (base_ty <=0)) || (base_ty > ((arena)->num_types)))) {
      (void)(driver_diagnostic_typeck_subscript_base(line, col));
      return -1;
    }
    (void)((bt_kind = pipeline_type_kind_ord_at(arena, base_ty)));
    (void)((vec_lanes = typeck_vector_lanes_of_type(arena, base_ty)));
    (void)((is_vec_base = 0));
    if (((bt_kind ==ord_vector) || (vec_lanes > 0))) {
      (void)((is_vec_base = 1));
    }
    if (((((bt_kind !=ord_array) && (bt_kind !=ord_slice)) && (bt_kind !=ord_ptr)) && (is_vec_base ==0))) {
      (void)(driver_diagnostic_typeck_subscript_base(line, col));
      return -1;
    }
    if (((!(ast_ref_is_null(index_ref)) && (index_ref > 0)) && (index_ref <=((arena)->num_exprs)))) {
      (void)((index_ty = pipeline_expr_resolved_type_ref(arena, index_ref)));
      ((typeck_type_is_valid_subscript_index(module, arena, index_ty) ==0) ? ({   (void)(driver_diagnostic_typeck_subscript_index(line, col));
  return -1;
 }) : 0);
    }
    if ((is_vec_base !=0)) {
      (void)((elem_ty = typeck_vector_elem_type_ref(arena, base_ty)));
    } else {
      (void)((elem_ty = pipeline_type_elem_ref_at(arena, base_ty)));
    }
    if ((ast_ref_is_null(elem_ty) || (elem_ty <=0))) {
      (void)(driver_diagnostic_typeck_subscript_base(line, col));
      return -1;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, elem_ty));
    if ((bt_kind ==ord_slice)) {
      (void)(pipeline_expr_set_index_base_is_slice(arena, expr_ref, 1));
    } else {
      (void)(pipeline_expr_set_index_base_is_slice(arena, expr_ref, 0));
    }
    if (((!(ast_ref_is_null(index_ref)) && (index_ref > 0)) && (index_ref <=((arena)->num_exprs)))) {
      ((((pipeline_expr_kind_ord_at(arena, index_ref) ==ord_lit) && (pipeline_expr_int_val_at(arena, index_ref) ==0)) && ((bt_kind ==ord_array) || (is_vec_base !=0))) ? ({   (void)((array_sz = pipeline_type_array_size_at(arena, base_ty)));
  if (((array_sz < 1) && (vec_lanes > 0))) {
    (void)((array_sz = vec_lanes));
  }
  ((array_sz >=1) ? ({   (void)(pipeline_expr_set_index_proven_in_bounds(arena, expr_ref, 1));
 }) : 0);
 }) : 0);
    }
    return 0;
  }
}
int typeck_expr_is_any_assign_kind(int32_t kind_ord) {
  int32_t ord_assign = 28;
  int32_t ord_add_assign = 29;
  int32_t ord_shr_assign = 38;
  if ((kind_ord ==ord_assign)) {
    return 1;
  }
  if (((kind_ord >=ord_add_assign) && (kind_ord <=ord_shr_assign))) {
    return 1;
  }
  return 0;
}
int32_t typeck_check_expr_array_lit(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_expr_array_lit = 46;
    int32_t num_elems = 0;
    int32_t i = 0;
    int32_t elem_ref = 0;
    int32_t already = 0;
    int32_t elem_ty = 0;
    int32_t ok_inf = 1;
    int32_t j = 0;
    int32_t er = 0;
    int32_t et = 0;
    int32_t arr_ty = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, expr_ref) !=ord_expr_array_lit)) {
      return 0;
    }
    (void)((num_elems = pipeline_expr_array_lit_num_elems_at(arena, expr_ref)));
    if (((return_type_ref > 0) && (num_elems > 0))) {
      int32_t amb_lanes = typeck_vector_lanes_of_type(arena, return_type_ref);
      int32_t amb_kind = pipeline_type_kind_ord_at(arena, return_type_ref);
      if (((amb_lanes <=0) && (amb_kind ==13))) {
        (void)((amb_lanes = pipeline_type_array_size_at(arena, return_type_ref)));
      }
      (((amb_lanes > 0) && (amb_lanes ==num_elems)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, return_type_ref));
 }) : 0);
    }
    (void)(({   int32_t elem_expected = 0;
  int32_t amb_tk = 0;
  if ((return_type_ref > 0)) {
    (void)((amb_tk = pipeline_type_kind_ord_at(arena, return_type_ref)));
    (((amb_tk ==10) || (amb_tk ==11)) ? ({   (void)((elem_expected = pipeline_type_elem_ref_at(arena, return_type_ref)));
 }) : 0);
  }
  while ((i < num_elems)) {
    (void)((elem_ref = pipeline_expr_array_lit_elem_ref(arena, expr_ref, i)));
    if ((!(ast_ref_is_null(elem_ref)) && (elem_ref > 0))) {
      ((typeck_check_expr(module, arena, elem_ref, elem_expected, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)((i = (i + 1)));
  }
 }));
    (void)((already = pipeline_expr_resolved_type_ref(arena, expr_ref)));
    if (((ast_ref_is_null(already) || (already <=0)) && (num_elems > 0))) {
      (void)((elem_ref = pipeline_expr_array_lit_elem_ref(arena, expr_ref, 0)));
      (void)((elem_ty = 0));
      (void)((ok_inf = 1));
      if ((!(ast_ref_is_null(elem_ref)) && (elem_ref > 0))) {
        (void)((elem_ty = pipeline_expr_resolved_type_ref(arena, elem_ref)));
      }
      if ((ast_ref_is_null(elem_ty) || (elem_ty <=0))) {
        (void)((ok_inf = 0));
      }
      (void)((j = 1));
      while (((ok_inf !=0) && (j < num_elems))) {
        (void)((er = pipeline_expr_array_lit_elem_ref(arena, expr_ref, j)));
        (void)((et = 0));
        if ((!(ast_ref_is_null(er)) && (er > 0))) {
          (void)((et = pipeline_expr_resolved_type_ref(arena, er)));
        }
        if ((ast_ref_is_null(et) || (et <=0))) {
          (void)((ok_inf = 0));
        } else {
          if (((!(typeck_type_refs_equal(arena, et, elem_ty)) && !(typeck_integer_widen_ok_refs(arena, elem_ty, et))) && !(typeck_integer_widen_ok_refs(arena, et, elem_ty)))) {
            (void)((ok_inf = 0));
          } else {
            if ((!(typeck_type_refs_equal(arena, et, elem_ty)) && typeck_integer_widen_ok_refs(arena, et, elem_ty))) {
              (void)((elem_ty = et));
            }
          }
        }
        (void)((j = (j + 1)));
      }
      ((ok_inf !=0) ? ({   (void)((arr_ty = typeck_find_or_alloc_array_type_ref(arena, elem_ty, num_elems)));
  ((!(ast_ref_is_null(arr_ty)) && (arr_ty > 0)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, arr_ty));
 }) : 0);
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_check_expr_impl_mega(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_return = 41;
    int32_t ord_panic = 42;
    int32_t ord_match = 43;
    int32_t ord_field = 44;
    int32_t ord_struct_lit = 45;
    int32_t ord_array_lit = 46;
    int32_t ord_index = 47;
    int32_t ord_call = 48;
    int32_t ord_method_call = 49;
    int32_t ord_add = 4;
    int32_t ord_logor = 21;
    int32_t ord_neg = 22;
    int32_t ord_bitnot = 23;
    int32_t ord_lognot = 24;
    int32_t ord_addr_of = 51;
    int32_t ord_deref = 52;
    int32_t ord_var = 3;
    int32_t ord_as = 54;
    int32_t ord_try_propagate = 58;
    int32_t kind = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if (typeck_expr_is_any_assign_kind(kind)) {
      return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_return)) {
      return pipeline_typeck_check_expr_impl_mega_c(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_panic)) {
      return typeck_check_expr_panic(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_match)) {
      return typeck_check_expr_match(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_field)) {
      return typeck_check_expr_field_access(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_array_lit)) {
      return typeck_check_expr_array_lit(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_index)) {
      return typeck_check_expr_index(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_call)) {
      return typeck_check_expr_call(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_method_call)) {
      return typeck_check_expr_method_call(module, arena, expr_ref, return_type_ref, ctx);
    }
    if (((kind >=ord_add) && (kind <=ord_logor))) {
      return typeck_check_expr_binop(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((((kind ==ord_neg) || (kind ==ord_bitnot)) || (kind ==ord_lognot))) {
      return typeck_check_expr_unary(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_addr_of)) {
      return typeck_check_expr_addr_of(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_deref)) {
      return typeck_check_expr_deref(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_var)) {
      return typeck_check_expr_var(module, arena, expr_ref, ctx);
    }
    if ((kind ==ord_as)) {
      return typeck_check_expr_as(module, arena, expr_ref, ctx);
    }
    if ((kind ==ord_struct_lit)) {
      return typeck_check_expr_struct_lit(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_try_propagate)) {
      return typeck_check_expr_try_propagate(module, arena, expr_ref, return_type_ref, ctx);
    }
    return 0;
  }
}
int32_t typeck_check_expr_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ord_lit = 0;
    int32_t ord_float = 1;
    int32_t ord_bool = 2;
    int32_t ord_string_lit = 59;
    int32_t ord_if = 25;
    int32_t ord_block = 26;
    int32_t ord_ternary = 27;
    int32_t ord_break = 39;
    int32_t ord_continue = 40;
    int32_t ord_enum_var = 50;
    int32_t kind = 0;
    if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    (void)((kind = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((kind ==ord_float)) {
      return typeck_check_expr_float_lit(arena, expr_ref);
    }
    if ((kind ==ord_lit)) {
      return typeck_check_expr_int_lit(arena, expr_ref, return_type_ref);
    }
    if ((kind ==ord_bool)) {
      return typeck_check_expr_bool_lit(arena, expr_ref);
    }
    if ((kind ==ord_string_lit)) {
      return typeck_check_expr_string_lit(arena, expr_ref);
    }
    if (((kind ==ord_break) || (kind ==ord_continue))) {
      return typeck_check_expr_break_continue(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_enum_var)) {
      return typeck_check_expr_enum_variant(arena, expr_ref);
    }
    if (((kind ==ord_if) || (kind ==ord_ternary))) {
      return typeck_check_expr_if_ternary(module, arena, expr_ref, return_type_ref, ctx);
    }
    if ((kind ==ord_block)) {
      return typeck_check_expr_block(module, arena, expr_ref, return_type_ref, ctx);
    }
    return typeck_check_expr_impl_mega(module, arena, expr_ref, return_type_ref, ctx);
  }
}
int32_t typeck_check_expr(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t rc = 0;
  if (ast_ref_is_null(expr_ref)) {
    return 0;
  }
  if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
    return 0;
  }
  (void)((rc = typeck_check_expr_impl(module, arena, expr_ref, return_type_ref, ctx)));
  if ((rc ==0)) {
    (void)(typeck_fold_expr(arena, expr_ref));
  }
  return rc;
}
int32_t typeck_func_body_tail_expr_ref_for_implicit_rule(struct ast_ASTArena * arena, int32_t body_ref) {
  {
    uint8_t stmt_order_kind_expr_stmt = 2;
    uint8_t stmt_order_kind_region_c_parser = 5;
    uint8_t stmt_order_kind_region_x_parser = 6;
    int32_t ord_break = 39;
    int32_t ord_continue = 40;
    int32_t ord_return = 41;
    int32_t ord_panic = 42;
    int32_t fin_ref = ast_ast_block_final_expr_ref(arena, body_ref);
    int32_t fin_kind = 0;
    int32_t nso = ast_ast_block_num_stmt_order(arena, body_ref);
    if (!(ast_ref_is_null(fin_ref))) {
      (void)((fin_kind = pipeline_expr_kind_ord_at(arena, fin_ref)));
      (((((fin_kind ==ord_return) || (fin_kind ==ord_panic)) || (fin_kind ==ord_break)) || (fin_kind ==ord_continue)) ? ({   return fin_ref;
 }) : 0);
    }
    if ((nso > 0)) {
      uint8_t last_k = ast_ast_block_stmt_order_kind(arena, body_ref, (nso - 1));
      (((last_k ==stmt_order_kind_region_c_parser) || (last_k ==stmt_order_kind_region_x_parser)) ? ({   int32_t ridx = ast_ast_block_stmt_order_idx(arena, body_ref, (nso - 1));
  int32_t nreg = ast_ast_block_num_regions(arena, body_ref);
  (((ridx >=0) && (ridx < nreg)) ? ({   int32_t unsafe_region = pipeline_block_region_is_unsafe(arena, body_ref, ridx);
  ((unsafe_region !=0) ? ({   int32_t inner_ref = ast_ast_block_region_body_ref(arena, body_ref, ridx);
  (!(ast_ref_is_null(inner_ref)) ? ({   return typeck_func_body_tail_expr_ref_for_implicit_rule(arena, inner_ref);
 }) : 0);
 }) : 0);
 }) : 0);
 }) : 0);
    }
    if (!(ast_ref_is_null(fin_ref))) {
      return fin_ref;
    }
    if ((nso > 0)) {
      uint8_t last_k2 = ast_ast_block_stmt_order_kind(arena, body_ref, (nso - 1));
      if ((last_k2 ==stmt_order_kind_expr_stmt)) {
        int32_t idx = ast_ast_block_stmt_order_idx(arena, body_ref, (nso - 1));
        int32_t nes = ast_ast_block_num_expr_stmts(arena, body_ref);
        (((idx >=0) && (idx < nes)) ? ({   return ast_ast_block_expr_stmt_ref(arena, body_ref, idx);
 }) : 0);
      }
      return 0;
    }
    int32_t nes2 = ast_ast_block_num_expr_stmts(arena, body_ref);
    if ((nes2 > 0)) {
      return ast_ast_block_expr_stmt_ref(arena, body_ref, (nes2 - 1));
    }
    return 0;
  }
}
int typeck_func_body_has_implicit_return_tail(struct ast_ASTArena * arena, int32_t body_ref) {
  {
    int32_t tail_ref = 0;
    int32_t tail_kind = 0;
    uint8_t * dbg = 0;
    if ((((ast_ref_is_null(body_ref) || (body_ref <=0)) || (arena ==0)) || (body_ref > ((arena)->num_blocks)))) {
      return 0;
    }
    (void)((tail_ref = typeck_func_body_tail_expr_ref_for_implicit_rule(arena, body_ref)));
    if (ast_ref_is_null(tail_ref)) {
      return 0;
    }
    (void)((tail_kind = pipeline_expr_kind_ord_at(arena, tail_ref)));
    (void)((dbg = link_abi_getenv(((uint8_t *)(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x44\x45\x42\x55\x47\x5f\x50\x49\x50\x45"))))));
    if ((dbg !=0)) {
    }
    if (ast_ast_expr_disallows_implicit_tail(arena, tail_ref)) {
      return 0;
    }
    if ((tail_kind ==26)) {
      int32_t inner_block = pipeline_expr_block_ref_at(arena, tail_ref);
      (!(ast_ref_is_null(inner_block)) ? ({   return typeck_func_body_has_implicit_return_tail(arena, inner_block);
 }) : 0);
    }
    return 1;
  }
}
int32_t typeck_loop_depth_push(struct ast_PipelineDepCtx * ctx) {
  {
    int32_t saved = pipeline_dep_ctx_typeck_loop_depth_at(ctx);
    (void)(pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32(ctx, (saved + 1)));
    return saved;
  }
}
void typeck_loop_depth_pop(struct ast_PipelineDepCtx * ctx, int32_t saved) {
  (void)(pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32(ctx, saved));
}
int32_t typeck_check_block_as_loop_body(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  int32_t saved_ld = 0;
  int32_t rc = 0;
  if ((ctx ==0)) {
    return -1;
  }
  (void)((saved_ld = typeck_loop_depth_push(ctx)));
  (void)((rc = typeck_check_block(module, arena, body_ref, return_type_ref, ctx)));
  (void)(typeck_loop_depth_pop(ctx, saved_ld));
  return rc;
}
int32_t typeck_check_block_one_const(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  {
    int32_t cd_ir = ast_ast_block_const_init_ref(arena, block_ref, idx);
    int32_t cd_tr = ast_ast_block_const_type_ref(arena, block_ref, idx);
    int32_t init_ty = 0;
    int32_t init_ctx = 0;
    uint8_t cname_buf[128] = { 0 };
    int32_t cname_len = 0;
    int32_t func_ix = 0;
    (void)((cname_len = pipeline_block_const_name_len(arena, block_ref, idx)));
    if (((cname_len > 0) && (cname_len < 128))) {
      (void)(pipeline_block_const_name_copy64(arena, block_ref, idx, &((cname_buf)[0])));
      /* Twin of typeck.x: discard `const _` (name "_" len=1) must not T001. */
      if (!((cname_len == 1) && (cname_buf[0] == 95))) {
      (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
      ((pipeline_block_local_name_redecl_c(arena, block_ref, &((cname_buf)[0]), cname_len, 1, idx, module, func_ix) !=0) ? ({   int32_t err_line = 0;
  int32_t err_col = 0;
  if (!(ast_ref_is_null(cd_ir))) {
    (void)((err_line = pipeline_expr_line_at(arena, cd_ir)));
    (void)((err_col = pipeline_expr_col_at(arena, cd_ir)));
  }
  (void)(driver_diagnostic_typeck_duplicate_local(err_line, err_col));
  return -1;
 }) : 0);
      }
    }
    if (!(ast_ref_is_null(cd_ir))) {
      ((typeck_block_const_init_is_const(arena, block_ref, idx) ==0) ? ({   int32_t err_line = pipeline_expr_line_at(arena, cd_ir);
  int32_t err_col = pipeline_expr_col_at(arena, cd_ir);
  (void)(typeck_const_init_not_constant(err_line, err_col));
  return -1;
 }) : 0);
    }
    if (!(ast_ref_is_null(cd_tr))) {
      (void)((init_ctx = cd_tr));
    } else {
      (void)((init_ctx = 0));
    }
    if ((typeck_check_expr(module, arena, cd_ir, init_ctx, ctx) !=0)) {
      return -1;
    }
    if ((!(ast_ref_is_null(cd_ir)) && ast_ref_is_null(cd_tr))) {
      (void)((init_ty = typeck_expr_type_ref(arena, cd_ir)));
      if (ast_ref_is_null(init_ty)) {
        return -1;
      }
      ((pipeline_block_set_const_type_ref(arena, block_ref, idx, init_ty) !=0) ? ({   return -1;
 }) : 0);
    } else {
      if ((!(ast_ref_is_null(cd_ir)) && !(ast_ref_is_null(cd_tr)))) {
        if ((typeck_coerce_init_expr_to_decl(module, arena, cd_ir, cd_tr) < 0)) {
          return -1;
        }
        (void)((init_ty = typeck_expr_type_ref(arena, cd_ir)));
        ((!(ast_ref_is_null(init_ty)) && !(typeck_type_refs_equal(arena, cd_tr, init_ty))) ? ({   return -1;
 }) : 0);
      }
    }
    if (!(ast_ref_is_null(cd_ir))) {
      (void)(typeck_fold_block_const_init(arena, block_ref, idx));
    }
    return 0;
  }
}
int32_t typeck_check_block_one_let(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  {
    int32_t ld_ir = ast_ast_block_let_init_ref(arena, block_ref, idx);
    int32_t ld_tr = ast_ast_block_let_type_ref(arena, block_ref, idx);
    int32_t init_ty = 0;
    int32_t init_ctx = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    uint8_t lname_buf[128] = { 0 };
    int32_t lname_len = 0;
    int32_t func_ix_l = 0;
    int32_t canon_tr = 0;
    if (!(ast_ref_is_null(ld_tr))) {
      (void)((canon_tr = typeck_resolve_type_alias_ref(arena, ld_tr)));
      (((canon_tr > 0) && (canon_tr !=ld_tr)) ? ({   ((pipeline_block_set_let_type_ref(arena, block_ref, idx, canon_tr) ==0) ? ({   (void)((ld_tr = canon_tr));
 }) : 0);
 }) : 0);
    }
    (void)((lname_len = pipeline_block_let_name_len(arena, block_ref, idx)));
    if (((lname_len > 0) && (lname_len < 128))) {
      (void)(pipeline_block_let_name_copy64(arena, block_ref, idx, &((lname_buf)[0])));
      /* Twin of typeck.x: discard `let _` (name "_" len=1) must not T001.
       * L4 g05 compiles this pin (prefer .x hid the gap on daily L2).
       * PLATFORM: SHARED typeck pin. */
      if (!((lname_len == 1) && (lname_buf[0] == 95))) {
      (void)((func_ix_l = pipeline_dep_ctx_current_func_index(ctx)));
      ((pipeline_block_local_name_redecl_c(arena, block_ref, &((lname_buf)[0]), lname_len, 0, idx, module, func_ix_l) !=0) ? ({   int32_t err_line = 0;
  int32_t err_col = 0;
  if (!(ast_ref_is_null(ld_ir))) {
    (void)((err_line = pipeline_expr_line_at(arena, ld_ir)));
    (void)((err_col = pipeline_expr_col_at(arena, ld_ir)));
  }
  (void)(driver_diagnostic_typeck_duplicate_local(err_line, err_col));
  return -1;
 }) : 0);
      }
    }
    if (!(ast_ref_is_null(ld_ir))) {
      (void)((init_ctx = return_type_ref));
      if (!(ast_ref_is_null(ld_tr))) {
        (void)((init_ctx = ld_tr));
      }
      if ((!(ast_ref_is_null(ld_tr)) && (pipeline_expr_kind_ord_at(arena, ld_ir) ==3))) {
        int32_t decl_k0 = pipeline_type_kind_ord_at(arena, ld_tr);
        ((decl_k0 ==15) ? ({   (void)((init_ctx = 0));
 }) : 0);
      }
      ((typeck_check_expr(module, arena, ld_ir, init_ctx, ctx) !=0) ? ({   return -1;
 }) : 0);
    }
    (void)(pipeline_type_stamp_block_let_region_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(arena, block_ref, idx, ctx));
    (void)((ld_tr = ast_ast_block_let_type_ref(arena, block_ref, idx)));
    if ((!(ast_ref_is_null(ld_ir)) && !(ast_ref_is_null(ld_tr)))) {
      if ((typeck_coerce_init_expr_to_decl(module, arena, ld_ir, ld_tr) < 0)) {
        return -1;
      }
      (void)((init_ty = typeck_expr_type_ref(arena, ld_ir)));
      if (((typeck_expr_is_null_keyword(arena, ld_ir) !=0) && (pipeline_type_kind_ord_at(arena, ld_tr) !=9))) {
        (void)((eb = driver_typeck_diag_scratch_expect()));
        (void)((gb = driver_typeck_diag_scratch_found()));
        (void)((el = typeck_diag_fmt_type_into(arena, ld_tr, eb, 96)));
        (void)((gl = typeck_diag_append_lit(gb, 0, 96, ((uint8_t *)"\x6e\x75\x6c\x6c"), 4)));
        (void)(({   int32_t err_line = pipeline_expr_line_at(arena, ld_ir);
  int32_t err_col = pipeline_expr_col_at(arena, ld_ir);
  (void)(driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl));
 }));
        return -1;
      }
      if ((!(ast_ref_is_null(init_ty)) && !(typeck_type_refs_equal(arena, ld_tr, init_ty)))) {
        (typeck_integer_widen_ok_refs(arena, ld_tr, init_ty) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, ld_ir, ld_tr));
  (void)((init_ty = ld_tr));
 }) : 0);
      }
      if (((!(ast_ref_is_null(init_ty)) && !(typeck_type_refs_equal(arena, ld_tr, init_ty))) && (pipeline_typeck_linear_accepts_init_c_ASTArena_ptr_i32_i32_reti32(arena, ld_tr, init_ty) ==0))) {
        int32_t decl_k2 = pipeline_type_kind_ord_at(arena, ld_tr);
        int32_t init_k2 = pipeline_type_kind_ord_at(arena, init_ty);
        int32_t dyn_init_reject = 0;
        int32_t fn_init_ok = 0;
        if ((decl_k2 ==17)) {
          ((typeck_dyn_rhs_is_null_sentinel(arena, init_ty, ld_ir) ==0) ? ({   uint8_t trait_nm_let[64] = {};
  int32_t tnl_let = pipeline_type_named_name_into(arena, ld_tr, &((trait_nm_let)[0]));
  (((tnl_let ==0) || (xlang_skip_impl_concrete_implements_trait_c(((void *)(arena)), init_ty, &((trait_nm_let)[0]), tnl_let) ==0)) ? ({   (void)((dyn_init_reject = 1));
 }) : 0);
 }) : 0);
        }
        /* 10.3.1: TYPE_FN accepts Cap *u8 / TYPE_FN init. PLATFORM: SHARED. */
        if ((typeck_fnptr_surface_compat(module, arena, ld_tr, init_ty, ld_ir, 0) != 0)) {
          (void)((fn_init_ok = 1));
        }
        (((dyn_init_reject !=0) || (((decl_k2 !=17) && (fn_init_ok ==0)) && !(typeck_float_widen_ok(decl_k2, init_k2)))) ? ({   (void)((eb = driver_typeck_diag_scratch_expect()));
  (void)((gb = driver_typeck_diag_scratch_found()));
  (void)((el = typeck_diag_fmt_type_into(arena, ld_tr, eb, 96)));
  (void)((gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96)));
  int32_t err_line = pipeline_expr_line_at(arena, ld_ir);
  int32_t err_col = pipeline_expr_col_at(arena, ld_ir);
  (void)(driver_diagnostic_typeck_assign_mismatch(0, err_line, err_col, eb, el, gb, gl));
  return -1;
 }) : 0);
      }
      ((!(ast_ref_is_null(init_ty)) && (typeck_check_slice_region_assign(arena, ld_ir, ld_tr, init_ty) !=0)) ? ({   return -1;
 }) : 0);
    }
    if (!(ast_ref_is_null(ld_ir))) {
      (void)(typeck_fold_expr_in_block(arena, block_ref, ld_ir));
    }
    return 0;
  }
}
int32_t typeck_check_block_one_while(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  {
    int32_t wc = ast_ast_block_while_cond_ref(arena, block_ref, idx);
    int32_t wb = ast_ast_block_while_body_ref(arena, block_ref, idx);
    if (!(ast_ref_is_null(wc))) {
      if ((typeck_check_expr(module, arena, wc, 0, ctx) !=0)) {
        return -1;
      }
      (!(typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, wc))) ? ({   (void)(driver_diagnostic_typeck_while_condition_not_bool(pipeline_expr_line_at(arena, wc), pipeline_expr_col_at(arena, wc)));
  return -1;
 }) : 0);
    }
    return typeck_check_block_as_loop_body(module, arena, wb, return_type_ref, ctx);
  }
}
int32_t typeck_check_block_one_for(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  {
    int32_t fi_ir = ast_ast_block_for_init_ref(arena, block_ref, idx);
    int32_t fc_cr = ast_ast_block_for_cond_ref(arena, block_ref, idx);
    int32_t fs_sr = ast_ast_block_for_step_ref(arena, block_ref, idx);
    int32_t fb_br = ast_ast_block_for_body_ref(arena, block_ref, idx);
    if ((typeck_check_expr(module, arena, fi_ir, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if (!(ast_ref_is_null(fc_cr))) {
      if ((typeck_check_expr(module, arena, fc_cr, 0, ctx) !=0)) {
        return -1;
      }
      (!(typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, fc_cr))) ? ({   (void)(driver_diagnostic_typeck_for_condition_not_bool(pipeline_expr_line_at(arena, fc_cr), pipeline_expr_col_at(arena, fc_cr)));
  return -1;
 }) : 0);
    }
    if ((typeck_check_expr(module, arena, fs_sr, return_type_ref, ctx) !=0)) {
      return -1;
    }
    return typeck_check_block_as_loop_body(module, arena, fb_br, return_type_ref, ctx);
  }
}
int32_t typeck_check_block_one_if(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  {
    int32_t ic_cr = ast_ast_block_if_cond_ref(arena, block_ref, idx);
    int32_t ib_tr = ast_ast_block_if_then_body_ref(arena, block_ref, idx);
    int32_t ib_er = 0;
    if (!(ast_ref_is_null(ic_cr))) {
      if ((typeck_check_expr(module, arena, ic_cr, 0, ctx) !=0)) {
        return -1;
      }
      (!(typeck_type_ref_is_bool(arena, typeck_expr_type_ref(arena, ic_cr))) ? ({   (void)(typeck_driver_diagnostic_pipe_marker(pipeline_expr_kind_ord_at(arena, ic_cr)));
  (void)(typeck_driver_diagnostic_pipe_marker(pipeline_type_kind_ord_at(arena, typeck_expr_type_ref(arena, ic_cr))));
  (void)(driver_diagnostic_typeck_if_condition_not_bool(pipeline_expr_line_at(arena, ic_cr), pipeline_expr_col_at(arena, ic_cr)));
  return -1;
 }) : 0);
    }
    if ((typeck_check_block(module, arena, ib_tr, return_type_ref, ctx) !=0)) {
      return -1;
    }
    (void)((ib_er = ast_ast_block_if_else_body_ref(arena, block_ref, idx)));
    if (!(ast_ref_is_null(ib_er))) {
      return typeck_check_block(module, arena, ib_er, return_type_ref, ctx);
    }
    return 0;
  }
}
int32_t typeck_void_reject_value_expr(struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref) {
  {
    int32_t void_ord = 16;
    int32_t rt_k = 0;
    int32_t ek = 0;
    int32_t void_stmt_ok = 0;
    int32_t got = 0;
    int32_t got_k = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    int32_t line = 0;
    int32_t col = 0;
    if ((((arena ==0) || (expr_ref <=0)) || ast_ref_is_null(return_type_ref))) {
      return 0;
    }
    (void)((rt_k = pipeline_type_kind_ord_at(arena, return_type_ref)));
    if ((rt_k !=void_ord)) {
      return 0;
    }
    (void)((ek = pipeline_expr_kind_ord_at(arena, expr_ref)));
    if ((ek ==41)) {
      (ast_ref_is_null(pipeline_expr_unary_operand_ref_at(arena, expr_ref)) ? ({   (void)((void_stmt_ok = 1));
 }) : 0);
    } else {
      if ((((((ek ==48) || (ek ==49)) || (ek ==39)) || (ek ==40)) || (ek ==42))) {
        (void)((void_stmt_ok = 1));
      } else {
        if (((ek >=28) && (ek <=38))) {
          (void)((void_stmt_ok = 1));
        } else {
          if ((((ek ==25) || (ek ==26)) || (ek ==43))) {
            (void)((void_stmt_ok = 1));
          }
        }
      }
    }
    if ((void_stmt_ok !=0)) {
      return 0;
    }
    (void)((got = typeck_expr_type_ref(arena, expr_ref)));
    if (!(ast_ref_is_null(got))) {
      (void)((got_k = pipeline_type_kind_ord_at(arena, got)));
      ((got_k ==void_ord) ? ({   return 0;
 }) : 0);
    }
    (void)((eb = driver_typeck_diag_scratch_expect()));
    (void)((gb = driver_typeck_diag_scratch_found()));
    (void)((el = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb)));
    (void)((gl = typeck_diag_fmt_type_or_question(arena, got, gb)));
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)(driver_diagnostic_typeck_return_mismatch(line, col, eb, el, gb, gl));
    (void)(typeck_emit_return_subexpr_breadcrumb(arena, expr_ref, line, col));
    (void)(driver_diagnostic_typeck_ret_fail(2, expr_ref, return_type_ref, got));
    return -1;
  }
}
int32_t typeck_check_block_final(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t fin0) {
  {
    int skip_tail_ty_cmp = 0;
    int32_t fin_k_tail = 0;
    int32_t got = 0;
    int32_t fin_op = 0;
    int32_t fin_k_ret = 0;
    uint8_t * eb_fin = 0;
    uint8_t * gb_fin = 0;
    int32_t el_fin = 0;
    int32_t gl_fin = 0;
    if (ast_ref_is_null(fin0)) {
      return 0;
    }
    if ((typeck_check_expr(module, arena, fin0, return_type_ref, ctx) !=0)) {
      return -1;
    }
    if ((typeck_void_reject_value_expr(arena, fin0, return_type_ref) !=0)) {
      return -1;
    }
    (void)((fin_k_tail = pipeline_expr_kind_ord_at(arena, fin0)));
    if ((fin_k_tail !=41)) {
      (void)((skip_tail_ty_cmp = 1));
    } else {
      if (ast_ref_is_null(pipeline_expr_unary_operand_ref_at(arena, fin0))) {
        (void)((skip_tail_ty_cmp = 1));
      }
    }
    if ((ast_ref_is_null(return_type_ref) || skip_tail_ty_cmp)) {
      return 0;
    }
    (void)((got = typeck_expr_type_ref(arena, fin0)));
    (void)((fin_op = fin0));
    (void)((fin_k_ret = pipeline_expr_kind_ord_at(arena, fin0)));
    if ((fin_k_ret ==41)) {
      (void)((fin_op = pipeline_expr_unary_operand_ref_at(arena, fin0)));
    }
    if (((!(ast_ref_is_null(fin_op)) && (fin_op > 0)) && !(ast_ref_is_null(return_type_ref)))) {
      (void)(typeck_ret_coerce_integral_to_expect_i32(arena, fin_op, return_type_ref));
      (void)(typeck_ret_coerce_integral_widen(arena, fin_op, return_type_ref));
    }
    if (typeck_return_operand_matches(module, arena, fin_op, return_type_ref)) {
      return 0;
    }
    if (((!(ast_ref_is_null(fin_op)) && (fin_op > 0)) && !(ast_ref_is_null(return_type_ref)))) {
      int32_t fin_got = typeck_expr_type_ref(arena, fin_op);
      int32_t ek_fin = 0;
      int32_t gk_fin = 0;
      ((!(ast_ref_is_null(fin_got)) && (fin_got > 0)) ? ({   (void)((ek_fin = pipeline_type_kind_ord_at(arena, return_type_ref)));
  (void)((gk_fin = pipeline_type_kind_ord_at(arena, fin_got)));
  ((typeck_integer_widen_ok_refs(arena, return_type_ref, fin_got) || typeck_float_widen_ok(ek_fin, gk_fin)) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, fin_op, return_type_ref));
  return 0;
 }) : 0);
 }) : 0);
    }
    (void)((eb_fin = driver_typeck_diag_scratch_expect()));
    (void)((gb_fin = driver_typeck_diag_scratch_found()));
    (void)((el_fin = typeck_diag_fmt_type_or_question(arena, return_type_ref, eb_fin)));
    (void)((gl_fin = typeck_diag_fmt_type_or_question(arena, got, gb_fin)));
    int32_t err_line = pipeline_expr_line_at(arena, fin0);
    int32_t err_col = pipeline_expr_col_at(arena, fin0);
    (void)(driver_diagnostic_typeck_return_mismatch(err_line, err_col, eb_fin, el_fin, gb_fin, gl_fin));
    (void)(typeck_emit_return_subexpr_breadcrumb(arena, fin0, err_line, err_col));
    return -1;
  }
}
int32_t typeck_check_block_one_region(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t idx) {
  return pipeline_typeck_check_block_one_region_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(module, arena, block_ref, idx, return_type_ref, ctx);
}
int32_t typeck_check_block_stmt_order_one(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t si, int32_t nso, int32_t nc, int32_t nl, int32_t nes, int32_t nlp, int32_t nfp, int32_t nif, int32_t nreg) {
  {
    int32_t i = 0;
    uint8_t sk = 0;
    int32_t idx = 0;
    int32_t es_ref = 0;
    (void)((i = si));
    while ((i < nso)) {
      (void)(pipeline_typeck_block_impl_touch_ctx_block_c_PipelineDepCtx_ptr_i32(ctx, block_ref));
      (void)((sk = ast_ast_block_stmt_order_kind(arena, block_ref, i)));
      (void)((idx = ast_ast_block_stmt_order_idx(arena, block_ref, i)));
      if ((sk ==0)) {
        ((((idx >=0) && (idx < nc)) && (idx < 128)) ? ({   ((typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
      } else {
        if ((sk ==1)) {
          ((((idx >=0) && (idx < nl)) && (idx < 128)) ? ({   ((typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
        } else {
          if ((sk ==2)) {
            (((idx >=0) && (idx < nes)) ? ({   (void)((es_ref = ast_ast_block_expr_stmt_ref(arena, block_ref, idx)));
  if ((typeck_check_expr(module, arena, es_ref, return_type_ref, ctx) !=0)) {
    return -1;
  }
  ((typeck_void_reject_value_expr(arena, es_ref, return_type_ref) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
          } else {
            if ((sk ==3)) {
              (((idx >=0) && (idx < nlp)) ? ({   ((typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
            } else {
              if ((sk ==4)) {
                (((idx >=0) && (idx < nfp)) ? ({   ((typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
              } else {
                if ((sk ==5)) {
                  (((idx >=0) && (idx < nif)) ? ({   ((typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
                } else {
                  if ((sk ==6)) {
                    (((idx >=0) && (idx < nreg)) ? ({   ((typeck_check_block_one_region(module, arena, block_ref, return_type_ref, ctx, idx) !=0) ? ({   return -1;
 }) : 0);
 }) : 0);
                  }
                }
              }
            }
          }
        }
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t typeck_check_block_legacy_consts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nc) {
  if ((i >=nc)) {
    return 0;
  }
  if ((typeck_check_block_one_const(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, (i + 1), nc);
}
int32_t typeck_check_block_legacy_lets(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nl) {
  if ((i >=nl)) {
    return 0;
  }
  if ((typeck_check_block_one_let(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, (i + 1), nl);
}
int32_t typeck_check_block_legacy_whiles(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nlp) {
  if ((i >=nlp)) {
    return 0;
  }
  if ((typeck_check_block_one_while(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, (i + 1), nlp);
}
int32_t typeck_check_block_legacy_fors(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nfp) {
  if ((i >=nfp)) {
    return 0;
  }
  if ((typeck_check_block_one_for(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, (i + 1), nfp);
}
int32_t typeck_check_block_legacy_ifs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nif) {
  if ((i >=nif)) {
    return 0;
  }
  if ((typeck_check_block_one_if(module, arena, block_ref, return_type_ref, ctx, i) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, (i + 1), nif);
}
int32_t typeck_check_block_legacy_expr_stmts(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx, int32_t i, int32_t nes) {
  int32_t es_ref = 0;
  if (((i >=nes) || (i >=32))) {
    return 0;
  }
  (void)((es_ref = ast_ast_block_expr_stmt_ref(arena, block_ref, i)));
  if ((typeck_check_expr(module, arena, es_ref, return_type_ref, ctx) !=0)) {
    return -1;
  }
  if ((typeck_void_reject_value_expr(arena, es_ref, return_type_ref) !=0)) {
    return -1;
  }
  return typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, (i + 1), nes);
}
int32_t typeck_check_block_impl(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t saved_block_ref = 0;
    int32_t nc = 0;
    int32_t nl = 0;
    int32_t nlp = 0;
    int32_t nfp = 0;
    int32_t nif = 0;
    int32_t nreg = 0;
    int32_t nes = 0;
    int32_t nso = 0;
    int32_t fin0 = 0;
    int32_t func_ix = 0;
    if ((((arena ==0) || (ctx ==0)) || (block_ref <=0))) {
      return -1;
    }
    (void)((saved_block_ref = pipeline_typeck_block_impl_bind_ctx_c_PipelineDepCtx_ptr_i32_reti32(ctx, block_ref)));
    (void)(pipeline_block_set_parent_if_zero(arena, block_ref, saved_block_ref));
    (void)((nc = ast_ast_block_num_consts(arena, block_ref)));
    (void)((nl = ast_ast_block_num_lets(arena, block_ref)));
    (void)((nlp = ast_ast_block_num_loops(arena, block_ref)));
    (void)((nfp = ast_ast_block_num_for_loops(arena, block_ref)));
    (void)((nif = ast_ast_block_num_if_stmts(arena, block_ref)));
    (void)((nreg = ast_ast_block_num_regions(arena, block_ref)));
    (void)((nes = ast_ast_block_num_expr_stmts(arena, block_ref)));
    (void)((nso = ast_ast_block_num_stmt_order(arena, block_ref)));
    (void)((fin0 = ast_ast_block_final_expr_ref(arena, block_ref)));
    (void)((func_ix = pipeline_dep_ctx_current_func_index(ctx)));
    (void)(driver_diagnostic_typeck_block_enter(func_ix, block_ref, nc, nl, nlp, nfp, nes, fin0));
    if ((nso > 0)) {
      ((typeck_check_block_stmt_order_one(module, arena, block_ref, return_type_ref, ctx, 0, nso, nc, nl, nes, nlp, nfp, nif, nreg) !=0) ? ({   (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
  return -1;
 }) : 0);
    } else {
      if ((typeck_check_block_legacy_consts(module, arena, block_ref, return_type_ref, ctx, 0, nc) !=0)) {
        (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
        return -1;
      }
      if ((typeck_check_block_legacy_lets(module, arena, block_ref, return_type_ref, ctx, 0, nl) !=0)) {
        (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
        return -1;
      }
      if ((typeck_check_block_legacy_whiles(module, arena, block_ref, return_type_ref, ctx, 0, nlp) !=0)) {
        (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
        return -1;
      }
      if ((typeck_check_block_legacy_fors(module, arena, block_ref, return_type_ref, ctx, 0, nfp) !=0)) {
        (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
        return -1;
      }
      if ((typeck_check_block_legacy_ifs(module, arena, block_ref, return_type_ref, ctx, 0, nif) !=0)) {
        (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
        return -1;
      }
      ((typeck_check_block_legacy_expr_stmts(module, arena, block_ref, return_type_ref, ctx, 0, nes) !=0) ? ({   (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
  return -1;
 }) : 0);
    }
    if ((typeck_check_block_final(module, arena, block_ref, return_type_ref, ctx, fin0) !=0)) {
      (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
      return -1;
    }
    (void)(pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(ctx, saved_block_ref));
    return 0;
  }
}
int32_t typeck_check_block(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if (ast_ref_is_null(block_ref)) {
    return 0;
  }
  if ((((arena ==0) || (block_ref <=0)) || (block_ref > ((arena)->num_blocks)))) {
    return 0;
  }
  return typeck_check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}
int32_t typeck_x_ast_check_one_func(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_idx) {
  {
    int32_t body_ref = 0;
    int32_t ret_ty_ref = 0;
    int32_t fn_name_len = 0;
    int32_t num_generic_params = 0;
    int32_t ord_void = 16;
    int32_t rt_kind = 0;
    int32_t err_check_block = 5;
    int32_t err_implicit_tail = 6;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return 0;
    }
    (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
    (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
    (void)(driver_diagnostic_typeck_fn_enter(func_idx, typeck_scratch64_slot(0), fn_name_len));
    (void)(pipeline_typeck_linear_reset_c());
    (void)((num_generic_params = pipeline_module_func_num_generic_params_at(module, func_idx)));
    (void)((body_ref = pipeline_module_func_body_ref_at(module, func_idx)));
    if ((ast_ref_is_null(body_ref) || (pipeline_module_func_is_extern_at(module, func_idx) !=0))) {
      return 0;
    }
    (void)((ret_ty_ref = pipeline_module_func_return_type_at(module, func_idx)));
    if ((typeck_check_block(module, arena, body_ref, ret_ty_ref, ctx) !=0)) {
      (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
      (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
      int32_t fail_kind_cb = -5;
      (void)(driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb));
      return fail_kind_cb;
    }
    if (!(ast_ref_is_null(ret_ty_ref))) {
      (void)((rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref)));
      (((rt_kind !=ord_void) && typeck_func_body_has_implicit_return_tail(arena, body_ref)) ? ({   (void)((fn_name_len = pipeline_module_func_name_len_at(module, func_idx)));
  (void)(pipeline_module_func_name_copy64(module, func_idx, typeck_scratch64_slot(0)));
  int32_t fail_kind_tail = -6;
  (void)(driver_diagnostic_typeck_func_fail(func_idx, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail));
  return fail_kind_tail;
 }) : 0);
    }
    return 0;
  }
}
int32_t typeck_x_ast_check_all_funcs_loop(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t func_i, int32_t num_funcs) {
  {
    int32_t i = 0;
    int32_t body_ref = 0;
    int32_t ret_ty_ref = 0;
    int32_t fn_name_len = 0;
    int32_t num_generic_params = 0;
    int32_t ord_void = 16;
    int32_t rt_kind = 0;
    int32_t no_func_ix = -1;
    int32_t fail_kind_cb = -5;
    int32_t fail_kind_tail = -6;
    (void)((i = func_i));
    if ((i >=num_funcs)) {
      (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
      return 0;
    }
    if ((i ==0)) {
      (void)(pipeline_typeck_set_entry_module_for_dep_map_c(module));
    }
    while ((i < num_funcs)) {
      (void)(pipeline_dep_ctx_set_current_func_index(ctx, i));
      (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
      (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
      (void)(driver_diagnostic_typeck_fn_enter(i, typeck_scratch64_slot(0), fn_name_len));
      (void)((num_generic_params = pipeline_module_func_num_generic_params_at(module, i)));
      (void)((body_ref = pipeline_module_func_body_ref_at(module, i)));
      if ((!(ast_ref_is_null(body_ref)) && (pipeline_module_func_is_extern_at(module, i) ==0))) {
        (void)((ret_ty_ref = pipeline_module_func_return_type_at(module, i)));
        if ((typeck_check_block(module, arena, body_ref, ret_ty_ref, ctx) !=0)) {
          (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
          (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
          (void)(driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_cb));
          (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
          return fail_kind_cb;
        }
        (!(ast_ref_is_null(ret_ty_ref)) ? ({   (void)((rt_kind = pipeline_type_kind_ord_at(arena, ret_ty_ref)));
  (((rt_kind !=ord_void) && typeck_func_body_has_implicit_return_tail(arena, body_ref)) ? ({   (void)((fn_name_len = pipeline_module_func_name_len_at(module, i)));
  (void)(pipeline_module_func_name_copy64(module, i, typeck_scratch64_slot(0)));
  (void)(driver_diagnostic_typeck_func_fail(i, typeck_scratch64_slot(0), fn_name_len, fail_kind_tail));
  (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
  return fail_kind_tail;
 }) : 0);
 }) : 0);
      }
      (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
      (void)((i = (i + 1)));
    }
    (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
    return 0;
  }
}
void typeck_patch_all_body_parent_links(struct ast_Module * module, struct ast_ASTArena * arena) {
  {
    int32_t i = 0;
    int32_t num = 0;
    int32_t br = 0;
    if (((module ==0) || (arena ==0))) {
      return;
    }
    (void)((num = pipeline_module_num_funcs(module)));
    while ((i < num)) {
      (void)((br = pipeline_module_func_body_ref_at(module, i)));
      if (!(ast_ref_is_null(br))) {
        (void)(pipeline_patch_block_parent_links(arena, br, 0));
      }
      (void)((i = (i + 1)));
    }
  }
}
extern int32_t xlang_trait_check_impls_complete_c(struct ast_Module * module);
int32_t typeck_x_ast_check_one_top_level_let(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx, int32_t tl) {
  {
    int32_t init_ref = 0;
    int32_t decl_ty = 0;
    int32_t is_const = 0;
    int32_t init_ty = 0;
    int32_t init_ctx = 0;
    uint8_t * eb = 0;
    uint8_t * gb = 0;
    int32_t el = 0;
    int32_t gl = 0;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return -1;
    }
    if (((tl < 0) || (tl >=((module)->num_top_level_lets)))) {
      return -1;
    }
    (void)((init_ref = pipeline_module_top_level_let_init_ref(module, tl)));
    (void)((decl_ty = pipeline_module_top_level_let_type_ref(module, tl)));
    (void)((is_const = pipeline_module_top_level_let_is_const(module, tl)));
    if (ast_ref_is_null(init_ref)) {
      return 0;
    }
    if ((is_const !=0)) {
      ((typeck_expr_is_const_with_module_consts(arena, init_ref) ==0) ? ({   (void)(typeck_const_init_not_constant(pipeline_expr_line_at(arena, init_ref), pipeline_expr_col_at(arena, init_ref)));
  return -1;
 }) : 0);
    }
    (void)((init_ctx = 0));
    if (!(ast_ref_is_null(decl_ty))) {
      (void)((init_ctx = decl_ty));
    }
    if ((typeck_check_expr(module, arena, init_ref, init_ctx, ctx) !=0)) {
      return -1;
    }
    if (ast_ref_is_null(decl_ty)) {
      (void)((init_ty = typeck_expr_type_ref(arena, init_ref)));
      if (ast_ref_is_null(init_ty)) {
        return -1;
      }
      (void)(pipeline_module_top_level_let_set_type_ref(module, tl, init_ty));
      return 0;
    }
    if ((typeck_coerce_init_expr_to_decl(module, arena, init_ref, decl_ty) < 0)) {
      return -1;
    }
    (void)((init_ty = typeck_expr_type_ref(arena, init_ref)));
    if ((!(ast_ref_is_null(init_ty)) && !(typeck_type_refs_equal(arena, decl_ty, init_ty)))) {
      (typeck_integer_widen_ok_refs(arena, decl_ty, init_ty) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, init_ref, decl_ty));
  (void)((init_ty = decl_ty));
 }) : 0);
    }
    if ((!(ast_ref_is_null(init_ty)) && !(typeck_type_refs_equal(arena, decl_ty, init_ty)))) {
      (void)((eb = driver_typeck_diag_scratch_expect()));
      (void)((gb = driver_typeck_diag_scratch_found()));
      (void)((el = typeck_diag_fmt_type_into(arena, decl_ty, eb, 96)));
      (void)((gl = typeck_diag_fmt_type_into(arena, init_ty, gb, 96)));
      (void)(driver_diagnostic_typeck_assign_mismatch(0, pipeline_expr_line_at(arena, init_ref), pipeline_expr_col_at(arena, init_ref), eb, el, gb, gl));
      return -1;
    }
    return 0;
  }
}
int32_t typeck_x_ast_check_top_level_lets(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t i = 0;
    int32_t n = 0;
    int32_t no_func_ix = -1;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return -1;
    }
    (void)(pipeline_typeck_set_entry_module_for_dep_map_c(module));
    (void)(pipeline_dep_ctx_set_current_func_index(ctx, no_func_ix));
    (void)((((ctx)->current_block_ref) = 0));
    (void)((n = ((module)->num_top_level_lets)));
    while ((i < n)) {
      if ((typeck_x_ast_check_one_top_level_let(module, arena, ctx, i) !=0)) {
        return -1;
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t typeck_x_ast_impl(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t mi = 0;
    int32_t ret_kind = 0;
    int32_t ord_i32 = 0;
    int32_t ord_i64 = 5;
    int32_t ord_void = 16;
    int32_t main_num_generic_params = 0;
    int32_t body_ref = 0;
    int32_t body_expr_ref = 0;
    int32_t ret_ty = 0;
    int32_t num_funcs = 0;
    int32_t pipe_marker_ret_ty_ready = 301;
    int32_t pipe_marker_main_generic_checked = 302;
    int32_t pipe_marker_layout_validated = 303;
    int32_t pipe_marker_parent_links_patched = 304;
    int32_t pipe_marker_main_generic_base = 320;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return -2;
    }
    if ((xlang_trait_check_impls_complete_c(module) !=0)) {
      return -1;
    }
    (void)((mi = pipeline_module_main_func_index(module)));
    if (((pipeline_module_func_is_extern_at(module, mi) !=0) && ast_ref_is_null(pipeline_module_func_body_ref_at(module, mi)))) {
      return -1;
    }
    (void)((body_ref = pipeline_module_func_body_ref_at(module, mi)));
    (void)((body_expr_ref = pipeline_module_func_body_expr_ref_at(module, mi)));
    if ((ast_ref_is_null(body_ref) && ast_ref_is_null(body_expr_ref))) {
      return -2;
    }
    (void)((ret_ty = pipeline_module_func_return_type_at(module, mi)));
    if (ast_ref_is_null(ret_ty)) {
      return -3;
    }
    (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_ret_ty_ready));
    (void)((main_num_generic_params = pipeline_module_func_num_generic_params_at(module, mi)));
    (void)(typeck_driver_diagnostic_pipe_marker((pipe_marker_main_generic_base + main_num_generic_params)));
    if ((main_num_generic_params > 0)) {
      return -12;
    }
    (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_main_generic_checked));
    (void)((ret_kind = pipeline_type_kind_ord_at(arena, ret_ty)));
    if ((((ret_kind !=ord_i32) && (ret_kind !=ord_i64)) && (ret_kind !=ord_void))) {
      return -4;
    }
    if ((typeck_validate_struct_layouts_zero_padding(module, arena) !=0)) {
      return -7;
    }
    (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_layout_validated));
    (void)(typeck_patch_all_body_parent_links(module, arena));
    (void)(typeck_driver_diagnostic_pipe_marker(pipe_marker_parent_links_patched));
    if ((typeck_x_ast_check_top_level_lets(module, arena, ctx) !=0)) {
      return -5;
    }
    (void)((num_funcs = pipeline_module_num_funcs(module)));
    int32_t rc_funcs = typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
    if ((rc_funcs ==0)) {
      (void)(pipeline_typeck_unused_binding_hints(module, arena));
      (void)(pipeline_typeck_wpo_dump_callgraph(module, arena, ctx));
    }
    return rc_funcs;
  }
}
int32_t typeck_x_ast_library(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t num_funcs = 0;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return -5;
    }
    if ((typeck_validate_struct_layouts_zero_padding(module, arena) !=0)) {
      return -7;
    }
    (void)(typeck_patch_all_body_parent_links(module, arena));
    if ((typeck_x_ast_check_top_level_lets(module, arena, ctx) !=0)) {
      return -5;
    }
    (void)((num_funcs = pipeline_module_num_funcs(module)));
    int32_t rc_lib = typeck_x_ast_check_all_funcs_loop(module, arena, ctx, 0, num_funcs);
    if ((rc_lib ==0)) {
      (void)(pipeline_typeck_unused_binding_hints(module, arena));
      (void)(pipeline_typeck_wpo_dump_callgraph(module, arena, ctx));
    }
    return rc_lib;
  }
}
int32_t typeck_x_ast(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t mi = 0;
    int32_t num_funcs = 0;
    if ((module ==0)) {
      return -10;
    }
    (void)((mi = pipeline_module_main_func_index(module)));
    (void)((num_funcs = pipeline_module_num_funcs(module)));
    if ((mi < 0)) {
      return -10;
    }
    if ((mi >=num_funcs)) {
      return -11;
    }
    return typeck_x_ast_impl(module, arena, ctx);
  }
}
int32_t pipeline_typeck_field_import_binding_resolve_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_field_import_binding(module, arena, expr_ref, base_ref, ctx);
}
int32_t pipeline_typeck_field_layout_named_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_field_layout_named(module, arena, expr_ref, base_ref, ctx);
}
int32_t pipeline_typeck_field_unknown_hard_fail_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_field_unknown_hard_fail(module, arena, expr_ref, base_ref, ctx);
}
int32_t pipeline_typeck_named_is_module_concrete_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, uint8_t * name, int32_t name_len) {
  return typeck_named_is_module_concrete(module, ctx, name, name_len);
}
int32_t pipeline_typeck_with_arena_scope_n_at(void) {
  return g_typeck_with_arena_scope_n;
}
int32_t pipeline_typeck_with_arena_current_body_ref_c(void) {
  if ((g_typeck_with_arena_scope_n > 0)) {
    return (g_typeck_with_arena_body_stack)[(g_typeck_with_arena_scope_n - 1)];
  }
  return 0;
}
void pipeline_typeck_with_arena_scope_push_c(int32_t body_ref) {
  if ((body_ref <=0)) {
    return;
  }
  if ((g_typeck_with_arena_scope_n >=8)) {
    return;
  }
  (void)(((g_typeck_with_arena_body_stack)[g_typeck_with_arena_scope_n] = body_ref));
  (void)((g_typeck_with_arena_scope_n = (g_typeck_with_arena_scope_n + 1)));
}
void pipeline_typeck_with_arena_scope_pop_c(void) {
  if ((g_typeck_with_arena_scope_n > 0)) {
    (void)((g_typeck_with_arena_scope_n = (g_typeck_with_arena_scope_n - 1)));
  }
}
void pipeline_typeck_with_arena_scope_reset_c(void) {
  (void)((g_typeck_with_arena_scope_n = 0));
}
int32_t pipeline_dep_ctx_scope_region_push_c(struct ast_PipelineDepCtx * ctx, uint8_t * label, int32_t label_len) {
  if (((ctx ==0) || (label ==0))) {
    return -1;
  }
  if (((label_len <=0) || (label_len > 127))) {
    return -1;
  }
  if ((g_typeck_region_scope_n >=8)) {
    return -1;
  }
  int32_t slot = g_typeck_region_scope_n;
  int32_t prev_len = ((ctx)->typeck_scope_region_len);
  (void)(((g_typeck_region_saved_len)[slot] = prev_len));
  if (((prev_len > 0) && (prev_len <=63))) {
    int32_t base = (slot * 128);
    int32_t i = 0;
    while ((i < 128)) {
      (void)(((g_typeck_region_saved_label)[(base + i)] = (((ctx)->typeck_scope_region_label))[i]));
      (void)((i = (i + 1)));
    }
  }
  int32_t j = 0;
  while ((j < 128)) {
    (void)(((((ctx)->typeck_scope_region_label))[j] = 0));
    (void)((j = (j + 1)));
  }
  int32_t k = 0;
  while ((k < label_len)) {
    (void)(((((ctx)->typeck_scope_region_label))[k] = (label)[k]));
    (void)((k = (k + 1)));
  }
  (void)((((ctx)->typeck_scope_region_len) = label_len));
  (void)((g_typeck_region_scope_n = (g_typeck_region_scope_n + 1)));
  return 0;
}
void pipeline_dep_ctx_scope_region_pop_c(struct ast_PipelineDepCtx * ctx) {
  if ((ctx ==0)) {
    return;
  }
  if ((g_typeck_region_scope_n <=0)) {
    return;
  }
  (void)((g_typeck_region_scope_n = (g_typeck_region_scope_n - 1)));
  int32_t slot = g_typeck_region_scope_n;
  int32_t saved_len = (g_typeck_region_saved_len)[slot];
  (void)((((ctx)->typeck_scope_region_len) = saved_len));
  int32_t j = 0;
  while ((j < 128)) {
    (void)(((((ctx)->typeck_scope_region_label))[j] = 0));
    (void)((j = (j + 1)));
  }
  if (((saved_len > 0) && (saved_len <=127))) {
    int32_t base = (slot * 128);
    int32_t i = 0;
    while ((i < 128)) {
      (void)(((((ctx)->typeck_scope_region_label))[i] = (g_typeck_region_saved_label)[(base + i)]));
      (void)((i = (i + 1)));
    }
  }
}
int32_t pipeline_dep_ctx_scope_region_len_at(struct ast_PipelineDepCtx * ctx) {
  if ((ctx ==0)) {
    return 0;
  }
  if ((((ctx)->typeck_scope_region_len) > 0)) {
    return ((ctx)->typeck_scope_region_len);
  }
  return 0;
}
void pipeline_typeck_region_scope_reset_c(void) {
  (void)((g_typeck_region_scope_n = 0));
}
int32_t typeck_scan_expr_stack_escape_c(struct ast_Module * m, struct ast_ASTArena * a, struct ast_PipelineDepCtx * ctx, int32_t func_ix, int32_t expr_ref) {
  {
    int32_t k = 0;
    int32_t saved_ix = 0;
    int32_t saved_br = 0;
    int32_t l = 0;
    int32_t r = 0;
    int32_t op = 0;
    int32_t func_ret = 0;
    if ((((((m ==0) || (a ==0)) || (ctx ==0)) || (expr_ref <=0)) || (func_ix < 0))) {
      return 0;
    }
    (void)((saved_ix = ((ctx)->current_func_index)));
    (void)((saved_br = ((ctx)->current_block_ref)));
    (void)((((ctx)->current_func_index) = func_ix));
    (void)((k = pipeline_expr_kind_ord_at(a, expr_ref)));
    if ((glue_expr_kind_is_assign_like_ord(k) !=0)) {
      (void)((l = pipeline_expr_binop_left_ref_at(a, expr_ref)));
      (void)((r = pipeline_expr_binop_right_ref_at(a, expr_ref)));
      if ((typeck_check_struct_stack_escape_assign(m, a, expr_ref, l, r, ctx) !=0)) {
        (void)((((ctx)->current_func_index) = saved_ix));
        (void)((((ctx)->current_block_ref) = saved_br));
        return -1;
      }
      if ((typeck_check_scope_borrow_assign(m, a, expr_ref, l, r, ctx) !=0)) {
        (void)((((ctx)->current_func_index) = saved_ix));
        (void)((((ctx)->current_block_ref) = saved_br));
        return -1;
      }
      ((typeck_check_allocator_region_assign(m, a, expr_ref, l, ctx) !=0) ? ({   (void)((((ctx)->current_func_index) = saved_ix));
  (void)((((ctx)->current_block_ref) = saved_br));
  return -1;
 }) : 0);
    } else {
      if ((k ==41)) {
        (void)((op = pipeline_expr_unary_operand_ref_at(a, expr_ref)));
        (void)((func_ret = pipeline_module_func_return_type_at(m, func_ix)));
        if ((typeck_check_scope_borrow_return(m, a, expr_ref, op, func_ret, ctx) !=0)) {
          (void)((((ctx)->current_func_index) = saved_ix));
          (void)((((ctx)->current_block_ref) = saved_br));
          return -1;
        }
        if ((typeck_check_allocator_region_return(a, expr_ref, func_ret) !=0)) {
          (void)((((ctx)->current_func_index) = saved_ix));
          (void)((((ctx)->current_block_ref) = saved_br));
          return -1;
        }
        if ((pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(a, expr_ref, func_ret, ctx) !=0)) {
          (void)((((ctx)->current_func_index) = saved_ix));
          (void)((((ctx)->current_block_ref) = saved_br));
          return -1;
        }
        ((typeck_check_return_slice_region(a, expr_ref, op, func_ret) !=0) ? ({   (void)((((ctx)->current_func_index) = saved_ix));
  (void)((((ctx)->current_block_ref) = saved_br));
  return -1;
 }) : 0);
      } else {
        if ((k ==48)) {
          ((pipeline_typeck_check_call_struct_stack_escape_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(m, a, expr_ref, ctx) !=0) ? ({   (void)((((ctx)->current_func_index) = saved_ix));
  (void)((((ctx)->current_block_ref) = saved_br));
  return -1;
 }) : 0);
        }
      }
    }
    (void)((((ctx)->current_func_index) = saved_ix));
    (void)((((ctx)->current_block_ref) = saved_br));
    return 0;
  }
}
int32_t typeck_scan_block_stack_escape_c(struct ast_Module * m, struct ast_ASTArena * a, struct ast_PipelineDepCtx * ctx, int32_t func_ix, int32_t block_ref) {
  {
    int32_t nes = 0;
    int32_t ei = 0;
    int32_t fin = 0;
    int32_t nso = 0;
    int32_t i = 0;
    int32_t saved_br = 0;
    int32_t k = 0;
    int32_t idx = 0;
    int32_t er = 0;
    int32_t br = 0;
    int32_t tr = 0;
    int32_t wa_cap = 0;
    int32_t is_unsafe = 0;
    int32_t saved_ud = 0;
    int32_t llen = 0;
    uint8_t lbl[128] = {};
    if ((((((m ==0) || (a ==0)) || (ctx ==0)) || (block_ref <=0)) || (func_ix < 0))) {
      return 0;
    }
    (void)((saved_br = ((ctx)->current_block_ref)));
    (void)((((ctx)->current_block_ref) = block_ref));
    (void)((nes = ast_ast_block_num_expr_stmts(a, block_ref)));
    (void)((ei = 0));
    while ((ei < nes)) {
      (void)((er = ast_ast_block_expr_stmt_ref(a, block_ref, ei)));
      if (((er > 0) && (typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, er) !=0))) {
        (void)((((ctx)->current_block_ref) = saved_br));
        return -1;
      }
      (void)((ei = (ei + 1)));
    }
    (void)((fin = ast_ast_block_final_expr_ref(a, block_ref)));
    if (((fin > 0) && (typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, fin) !=0))) {
      (void)((((ctx)->current_block_ref) = saved_br));
      return -1;
    }
    (void)((nso = ast_ast_block_num_stmt_order(a, block_ref)));
    (void)((i = 0));
    while ((i < nso)) {
      (void)((k = ((int32_t)(ast_ast_block_stmt_order_kind(a, block_ref, i)))));
      (void)((idx = ast_ast_block_stmt_order_idx(a, block_ref, i)));
      if ((((k ==2) && (idx >=0)) && (idx < ast_ast_block_num_expr_stmts(a, block_ref)))) {
        (void)((er = ast_ast_block_expr_stmt_ref(a, block_ref, idx)));
        (((er > 0) && (typeck_scan_expr_stack_escape_c(m, a, ctx, func_ix, er) !=0)) ? ({   (void)((((ctx)->current_block_ref) = saved_br));
  return -1;
 }) : 0);
      } else {
        if ((((k ==3) && (idx >=0)) && (idx < ast_ast_block_num_loops(a, block_ref)))) {
          (void)((br = ast_ast_block_while_body_ref(a, block_ref, idx)));
          (((br > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) !=0)) ? ({   return -1;
 }) : 0);
        } else {
          if ((((k ==4) && (idx >=0)) && (idx < ast_ast_block_num_for_loops(a, block_ref)))) {
            (void)((br = ast_ast_block_for_body_ref(a, block_ref, idx)));
            (((br > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) !=0)) ? ({   return -1;
 }) : 0);
          } else {
            if ((((k ==5) && (idx >=0)) && (idx < ast_ast_block_num_if_stmts(a, block_ref)))) {
              (void)((tr = ast_ast_block_if_then_body_ref(a, block_ref, idx)));
              (void)((er = ast_ast_block_if_else_body_ref(a, block_ref, idx)));
              if (((tr > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, tr) !=0))) {
                return -1;
              }
              (((er > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, er) !=0)) ? ({   return -1;
 }) : 0);
            } else {
              if ((((k ==6) && (idx >=0)) && (idx < ast_ast_block_num_regions(a, block_ref)))) {
                (void)((wa_cap = pipeline_block_region_with_arena_cap_ref(a, block_ref, idx)));
                (void)((br = ast_ast_block_region_body_ref(a, block_ref, idx)));
                (void)((is_unsafe = pipeline_block_region_is_unsafe(a, block_ref, idx)));
                (void)((saved_ud = 0));
                if ((is_unsafe !=0)) {
                  (void)((saved_ud = pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32(ctx)));
                }
                if ((wa_cap > 0)) {
                  (void)(pipeline_typeck_with_arena_scope_push_c(br));
                  if (((br > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) !=0))) {
                    (void)(pipeline_typeck_with_arena_scope_pop_c());
                    if ((is_unsafe !=0)) {
                      (void)(pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(ctx, saved_ud));
                    }
                    (void)((((ctx)->current_block_ref) = saved_br));
                    return -1;
                  }
                  (void)(pipeline_typeck_with_arena_scope_pop_c());
                } else {
                  (void)((llen = pipeline_block_region_label_len(a, block_ref, idx)));
                  if ((llen > 0)) {
                    (void)(pipeline_block_region_label_copy64(a, block_ref, idx, &((lbl)[0])));
                    ((pipeline_dep_ctx_scope_region_push_c(ctx, &((lbl)[0]), llen) !=0) ? ({   if ((is_unsafe !=0)) {
    (void)(pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(ctx, saved_ud));
  }
  (void)((((ctx)->current_block_ref) = saved_br));
  return -1;
 }) : 0);
                  }
                  if (((br > 0) && (typeck_scan_block_stack_escape_c(m, a, ctx, func_ix, br) !=0))) {
                    if ((llen > 0)) {
                      (void)(pipeline_dep_ctx_scope_region_pop_c(ctx));
                    }
                    if ((is_unsafe !=0)) {
                      (void)(pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(ctx, saved_ud));
                    }
                    (void)((((ctx)->current_block_ref) = saved_br));
                    return -1;
                  }
                  ((llen > 0) ? ({   (void)(pipeline_dep_ctx_scope_region_pop_c(ctx));
 }) : 0);
                }
                ((is_unsafe !=0) ? ({   (void)(pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(ctx, saved_ud));
 }) : 0);
              }
            }
          }
        }
      }
      (void)((i = (i + 1)));
    }
    (void)((((ctx)->current_block_ref) = saved_br));
    return 0;
  }
}
int32_t pipeline_typeck_scan_module_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t i = 0;
    int32_t nf = 0;
    int32_t body = 0;
    int32_t num_generic_params = 0;
    int32_t j = 0;
    uint8_t * skip_env = 0;
    if ((((module ==0) || (arena ==0)) || (ctx ==0))) {
      return 0;
    }
    (void)((skip_env = link_abi_getenv(((uint8_t *)(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x53\x4b\x49\x50\x5f\x53\x54\x41\x43\x4b\x5f\x45\x53\x43\x41\x50\x45"))))));
    if ((skip_env !=0)) {
      return 0;
    }
    (void)(pipeline_typeck_with_arena_scope_reset_c());
    (void)(pipeline_typeck_region_scope_reset_c());
    (void)((((ctx)->typeck_scope_region_len) = 0));
    (void)((j = 0));
    while ((j < 128)) {
      (void)(((((ctx)->typeck_scope_region_label))[j] = 0));
      (void)((j = (j + 1)));
    }
    (void)((nf = pipeline_module_num_funcs(module)));
    (void)((i = 0));
    while ((i < nf)) {
      if ((pipeline_module_func_is_extern_at(module, i) !=0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((num_generic_params = pipeline_module_func_num_generic_params_at(module, i)));
      if ((num_generic_params > 0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((body = pipeline_module_func_body_ref_at(module, i)));
      if ((body <=0)) {
        (void)((i = (i + 1)));
        continue;
      }
      if ((typeck_scan_block_stack_escape_c(module, arena, ctx, i, body) !=0)) {
        return -1;
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t pipeline_typeck_is_read_ptr_slice_callee_c(uint8_t * name, int32_t name_len) {
  if (((name ==0) || (name_len <=0))) {
    return 0;
  }
  if (((name_len ==14) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x72\x65\x61\x64\x5f\x70\x74\x72\x5f\x73\x6c\x69\x63\x65"))), 14))) {
    return 1;
  }
  if (((name_len ==19) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x78\x6c\x61\x6e\x67\x5f\x69\x6f\x5f\x72\x65\x61\x64\x5f\x70\x74\x72\x5f\x73\x6c\x69\x63\x65"))), 19))) {
    return 1;
  }
  if (((name_len ==18) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x64\x72\x69\x76\x65\x72\x5f\x72\x65\x61\x64\x5f\x70\x74\x72\x5f\x73\x6c\x69\x63\x65"))), 18))) {
    return 1;
  }
  if (((name_len ==16) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x69\x6f\x5f\x72\x65\x61\x64\x5f\x70\x74\x72\x5f\x73\x6c\x69\x63\x65"))), 16))) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_is_simd_comptime_callee_c(uint8_t * name, int32_t name_len) {
  if (((name ==0) || (name_len <=0))) {
    return 0;
  }
  if (((name_len ==12) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x73\x69\x6d\x64\x5f\x73\x68\x75\x66\x66\x6c\x65"))), 12))) {
    return 1;
  }
  if (((name_len ==11) && typeck_name_equal(name, name_len, ((uint8_t *)(((uint8_t *)"\x73\x69\x6d\x64\x5f\x73\x65\x6c\x65\x63\x74"))), 11))) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_read_ptr_slice_return_ref_c(struct ast_ASTArena * arena) {
  {
    int32_t u8_ref = 0;
    if ((arena ==0)) {
      return 0;
    }
    (void)((u8_ref = pipeline_type_ensure_by_kind_ord(arena, 2)));
    if ((u8_ref <=0)) {
      return 0;
    }
    return pipeline_type_find_or_alloc_slice(arena, u8_ref, ((uint8_t *)(((uint8_t *)"\x69\x6f\x5f\x72\x65\x61\x64\x5f\x70\x74\x72"))), 11);
  }
}
int32_t pipeline_type_stamp_block_let_region_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t ty_ref = 0;
    int32_t rlen = 0;
    int32_t elem = 0;
    int32_t stamped = 0;
    if (((((arena ==0) || (ctx ==0)) || (block_ref <=0)) || (let_idx < 0))) {
      return 0;
    }
    (void)((rlen = pipeline_dep_ctx_scope_region_len_at(ctx)));
    if ((rlen <=0)) {
      return 0;
    }
    (void)((ty_ref = pipeline_block_let_type_ref(arena, block_ref, let_idx)));
    if (((ty_ref <=0) || (pipeline_type_kind_ord_at(arena, ty_ref) !=11))) {
      return 0;
    }
    if ((pipeline_type_region_label_len_at(arena, ty_ref) > 0)) {
      return 0;
    }
    (void)((elem = pipeline_type_elem_ref_at(arena, ty_ref)));
    if ((elem <=0)) {
      return 0;
    }
    (void)((stamped = pipeline_type_find_or_alloc_slice(arena, elem, &((((ctx)->typeck_scope_region_label))[0]), rlen)));
    if ((stamped <=0)) {
      return -1;
    }
    if ((stamped ==ty_ref)) {
      return 0;
    }
    return pipeline_block_set_let_type_ref(arena, block_ref, let_idx, stamped);
  }
}
int32_t pipeline_typeck_check_block_one_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    uint8_t label[128] = {};
    int32_t label_len = 0;
    int32_t body_ref = 0;
    int32_t wa_cap = 0;
    int32_t rc = 0;
    int32_t saved_ud = 0;
    if ((((((module ==0) || (arena ==0)) || (ctx ==0)) || (block_ref <=0)) || (region_idx < 0))) {
      return 0;
    }
    (void)((body_ref = ast_ast_block_region_body_ref(arena, block_ref, region_idx)));
    if ((body_ref <=0)) {
      return 0;
    }
    if ((pipeline_block_region_is_unsafe(arena, block_ref, region_idx) !=0)) {
      (void)((saved_ud = pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32(ctx)));
      (void)((rc = typeck_check_block(module, arena, body_ref, return_type_ref, ctx)));
      (void)(pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(ctx, saved_ud));
      return rc;
    }
    (void)((wa_cap = pipeline_block_region_with_arena_cap_ref(arena, block_ref, region_idx)));
    if ((wa_cap > 0)) {
      (void)(pipeline_typeck_with_arena_scope_push_c(body_ref));
      (void)((rc = typeck_check_block(module, arena, body_ref, return_type_ref, ctx)));
      (void)(pipeline_typeck_with_arena_scope_pop_c());
      return rc;
    }
    (void)((label_len = pipeline_block_region_label_len(arena, block_ref, region_idx)));
    if ((label_len <=0)) {
      return 0;
    }
    (void)(pipeline_block_region_label_copy64(arena, block_ref, region_idx, &((label)[0])));
    if ((pipeline_dep_ctx_scope_region_push_c(ctx, &((label)[0]), label_len) !=0)) {
      return -1;
    }
    (void)((rc = typeck_check_block(module, arena, body_ref, return_type_ref, ctx)));
    (void)(pipeline_dep_ctx_scope_region_pop_c(ctx));
    return rc;
  }
}
int32_t pipeline_typeck_check_call_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t func_ix = 0;
    int32_t num_args = 0;
    int32_t np = 0;
    int32_t src_i = 0;
    int32_t dst_j = 0;
    int32_t line = 0;
    int32_t col = 0;
    int32_t arg_ref = 0;
    int32_t arg_ty = 0;
    int32_t arg_elem = 0;
    int32_t param_ref = 0;
    int32_t elem_ref = 0;
    int32_t other_arg = 0;
    uint8_t * skip_env = 0;
    uint8_t * m_u8 = 0;
    uint8_t * a_u8 = 0;
    uint8_t msg[96] = {};
    int32_t p = 0;
    if (((((module ==0) || (arena ==0)) || (ctx ==0)) || (call_expr_ref <=0))) {
      return 0;
    }
    if ((pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(ctx) > 0)) {
      return 0;
    }
    (void)((m_u8 = ((uint8_t *)(module))));
    (void)((a_u8 = ((uint8_t *)(arena))));
    (void)((func_ix = pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32(m_u8, a_u8, call_expr_ref)));
    if ((func_ix < 0)) {
      return 0;
    }
    (void)((num_args = pipeline_expr_call_num_args_at(arena, call_expr_ref)));
    (void)((np = pipeline_module_func_num_params_at(module, func_ix)));
    if (((num_args !=np) || (num_args < 2))) {
      return 0;
    }
    (void)((skip_env = link_abi_getenv(((uint8_t *)(((uint8_t *)"\x58\x4c\x41\x4e\x47\x5f\x53\x4b\x49\x50\x5f\x53\x54\x41\x43\x4b\x5f\x45\x53\x43\x41\x50\x45"))))));
    if ((skip_env !=0)) {
      return 0;
    }
    (void)((src_i = 0));
    while ((src_i < num_args)) {
      (void)((arg_ref = pipeline_expr_call_arg_ref(arena, call_expr_ref, src_i)));
      if ((typeck_expr_is_addr_of_block_local(module, arena, ctx, arg_ref) !=0)) {
        (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
        (((arg_ty > 0) && (pipeline_type_kind_ord_at(arena, arg_ty) ==9)) ? ({   (void)((arg_elem = pipeline_type_elem_ref_at(arena, arg_ty)));
  (((arg_elem > 0) && (typeck_type_is_named_struct_c(m_u8, a_u8, arg_elem) !=0)) ? ({   (void)((dst_j = 0));
  while ((dst_j < num_args)) {
    if ((dst_j !=src_i)) {
      (void)((param_ref = pipeline_module_func_param_type_ref_at(module, func_ix, dst_j)));
      (((param_ref > 0) && (pipeline_type_kind_ord_at(arena, param_ref) ==9)) ? ({   (void)((elem_ref = pipeline_type_elem_ref_at(arena, param_ref)));
  (((elem_ref > 0) && (typeck_type_is_named_struct_c(m_u8, a_u8, elem_ref) !=0)) ? ({   (void)((other_arg = pipeline_expr_call_arg_ref(arena, call_expr_ref, dst_j)));
  ((typeck_expr_is_addr_of_block_local(module, arena, ctx, other_arg) ==0) ? ({   (void)((line = pipeline_expr_line_at(arena, call_expr_ref)));
  (void)((col = pipeline_expr_col_at(arena, call_expr_ref)));
  (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 95, ((uint8_t *)"\x73\x74\x72\x75\x63\x74\x20\x73\x74\x61\x63\x6b\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x70\x61\x73\x73\x20\x61\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x6c\x6f\x63\x61\x6c\x20\x73\x74\x72\x75\x63\x74\x20\x77\x69\x74\x68\x20\x6f\x75"), 78)));
  (void)(((msg)[p] = 0));
  (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
  return -1;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    (void)((dst_j = (dst_j + 1)));
  }
 }) : 0);
 }) : 0);
      }
      (void)((src_i = (src_i + 1)));
    }
    return 0;
  }
}
int32_t pipeline_typeck_ptr_for_addr_of_operand_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx) {
  {
    uint8_t * m_u8 = 0;
    uint8_t * a_u8 = 0;
    if ((((((arena ==0) || (module ==0)) || (ctx ==0)) || (op_ref <=0)) || (elem_ty <=0))) {
      return 0;
    }
    if ((typeck_var_is_block_local(module, arena, ctx, op_ref) ==0)) {
      return 0;
    }
    (void)((m_u8 = ((uint8_t *)(module))));
    (void)((a_u8 = ((uint8_t *)(arena))));
    if ((typeck_type_is_named_struct_c(m_u8, a_u8, elem_ty) ==0)) {
      return 0;
    }
    return pipeline_type_find_or_alloc_ptr(arena, elem_ty, ((uint8_t *)(((uint8_t *)"\x73\x74\x61\x63\x6b\x5f\x6c\x6f\x63\x61\x6c"))), 11);
  }
}
int32_t pipeline_typeck_check_return_slice_region_in_scope_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t line = 0;
    int32_t col = 0;
    int32_t rlen = 0;
    uint8_t msg[256] = {};
    int32_t p = 0;
    int32_t z = 0;
    if (((((arena ==0) || (ctx ==0)) || (site_expr_ref <=0)) || (return_type_ref <=0))) {
      return 0;
    }
    if ((pipeline_dep_ctx_scope_region_len_at(ctx) <=0)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, return_type_ref) !=11)) {
      return 0;
    }
    if ((pipeline_type_region_label_len_at(arena, return_type_ref) > 0)) {
      return 0;
    }
    (void)((line = 0));
    (void)((col = 0));
    (void)(typeck_expr_diag_line_col(arena, site_expr_ref, &(line), &(col)));
    (void)((rlen = pipeline_dep_ctx_scope_region_len_at(ctx)));
    if ((rlen < 0)) {
      (void)((rlen = 0));
    }
    if ((rlen > 64)) {
      (void)((rlen = 64));
    }
    (void)((z = 0));
    while ((z < 256)) {
      (void)(((msg)[z] = 0));
      (void)((z = (z + 1)));
    }
    (void)((p = typeck_diag_append_lit(&((msg)[0]), 0, 255, ((uint8_t *)"\x73\x6c\x69\x63\x65\x20\x72\x65\x67\x69\x6f\x6e\x20\x65\x73\x63\x61\x70\x65\x3a\x20\x63\x61\x6e\x6e\x6f\x74\x20\x72\x65\x74\x75\x72\x6e\x20\x3c"), 36)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, &((((ctx)->typeck_scope_region_label))[0]), rlen)));
    (void)((p = typeck_diag_append_lit(&((msg)[0]), p, 255, ((uint8_t *)"\x3e\x20\x73\x6c\x69\x63\x65\x20\x61\x73\x20\x75\x6e\x62\x6f\x75\x6e\x64\x20\x54\x5b\x5d"), 22)));
    (void)(((msg)[p] = 0));
    (void)(lsp_diag_report_typeck(line, col, &((msg)[0])));
    return -1;
  }
}
int32_t pipeline_typeck_resolve_call_callee_return_type_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_resolve_call_callee_return_type(module, arena, callee_expr_ref, call_expr_ref, ctx);
}
int32_t typeck_module_func_overload_count(struct ast_Module * m, uint8_t * name, int32_t name_len) {
  {
    int32_t i = 0;
    int32_t c = 0;
    if ((((m ==0) || (name ==0)) || (name_len <=0))) {
      return 0;
    }
    while ((i < ((m)->num_funcs))) {
      if ((pipeline_module_func_is_extern_at(m, i) ==0)) {
        ((pipeline_module_func_name_equal_at(m, i, name, name_len) !=0) ? ({   (void)((c = (c + 1)));
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
    return c;
  }
}
int32_t typeck_pick_overload_func_index_for_call(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref) {
  {
    int32_t callee_ref = 0;
    int32_t ord_var = 3;
    int32_t nlen = 0;
    uint8_t nm[128] = {};
    int32_t count = 0;
    int32_t fx_out = -1;
    int32_t ret = 0;
    int32_t minus_one = -1;
    if ((((m ==0) || (a ==0)) || (call_expr_ref <=0))) {
      return minus_one;
    }
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(a, call_expr_ref)));
    if ((callee_ref <=0)) {
      return minus_one;
    }
    if ((pipeline_expr_kind_ord_at(a, callee_ref) !=ord_var)) {
      return minus_one;
    }
    (void)((nlen = pipeline_expr_var_name_len(a, callee_ref)));
    if (((nlen <=0) || (nlen > 127))) {
      return minus_one;
    }
    (void)(pipeline_expr_var_name_into(a, callee_ref, &((nm)[0])));
    (void)((count = typeck_module_func_overload_count(m, &((nm)[0]), nlen)));
    if ((count <=1)) {
      return minus_one;
    }
    (void)((fx_out = minus_one));
    (void)((ret = typeck_find_func_return_type_in_module_by_name_overload(m, a, &((nm)[0]), nlen, call_expr_ref, minus_one, 0, &(fx_out))));
    if ((fx_out >=0)) {
      return fx_out;
    }
    if (((ret > 0) && (fx_out >=0))) {
      return fx_out;
    }
    return minus_one;
  }
}
int32_t typeck_resolve_call_func_index_for_emit(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref) {
  {
    int32_t callee_ref = 0;
    int32_t ord_var = 3;
    int32_t nlen = 0;
    uint8_t nm[128] = {};
    int32_t picked = 0;
    int32_t fx = 0;
    int32_t i = 0;
    int32_t minus_one = -1;
    if ((((m ==0) || (a ==0)) || (call_expr_ref <=0))) {
      return minus_one;
    }
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(a, call_expr_ref)));
    if (((callee_ref > 0) && (pipeline_expr_kind_ord_at(a, callee_ref) ==ord_var))) {
      (void)((nlen = pipeline_expr_var_name_len(a, callee_ref)));
      (((nlen > 0) && (nlen <=127)) ? ({   (void)(pipeline_expr_var_name_into(a, callee_ref, &((nm)[0])));
  ((typeck_module_func_overload_count(m, &((nm)[0]), nlen) > 1) ? ({   (void)((picked = typeck_pick_overload_func_index_for_call(m, a, call_expr_ref)));
  ((picked >=0) ? ({   (void)(ast_ast_expr_apply_call_resolve(a, call_expr_ref, minus_one, picked));
  return picked;
 }) : 0);
 }) : 0);
 }) : 0);
    }
    (void)((fx = pipeline_expr_call_resolved_func_index_at(a, call_expr_ref)));
    if ((fx >=0)) {
      return fx;
    }
    if ((callee_ref <=0)) {
      return minus_one;
    }
    if ((pipeline_expr_kind_ord_at(a, callee_ref) !=ord_var)) {
      return minus_one;
    }
    (void)((nlen = pipeline_expr_var_name_len(a, callee_ref)));
    if (((nlen <=0) || (nlen > 127))) {
      return minus_one;
    }
    (void)(pipeline_expr_var_name_into(a, callee_ref, &((nm)[0])));
    (void)((i = 0));
    while ((i < ((m)->num_funcs))) {
      if ((pipeline_module_func_name_equal_at(m, i, &((nm)[0]), nlen) !=0)) {
        return i;
      }
      (void)((i = (i + 1)));
    }
    return minus_one;
  }
}
int32_t pipeline_typeck_pick_overload_func_index_for_call_c(struct ast_Module * m, struct ast_ASTArena * a, int32_t call_expr_ref) {
  return typeck_pick_overload_func_index_for_call(m, a, call_expr_ref);
}
int32_t pipeline_typeck_resolve_call_func_index_for_emit_c(uint8_t * m, uint8_t * a, int32_t call_expr_ref) {
  return typeck_resolve_call_func_index_for_emit(((struct ast_Module *)(m)), ((struct ast_ASTArena *)(a)), call_expr_ref);
}
int32_t typeck_call_arg_effective_type(struct ast_ASTArena * arena, int32_t arg_ref) {
  {
    int32_t arg_ty = 0;
    int32_t ek = 0;
    int32_t u8t = 0;
    if (((arena ==0) || (arg_ref <=0))) {
      return 0;
    }
    (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
    if ((arg_ty > 0)) {
      return arg_ty;
    }
    (void)((ek = pipeline_expr_kind_ord_at(arena, arg_ref)));
    if ((ek ==0)) {
      if ((typeck_expr_is_null_keyword(arena, arg_ref) !=0)) {
        return 0;
      }
      return pipeline_type_ensure_by_kind_ord(arena, 0);
    }
    if ((ek ==1)) {
      return pipeline_type_ensure_by_kind_ord(arena, 15);
    }
    if ((ek ==2)) {
      return pipeline_type_ensure_by_kind_ord(arena, 1);
    }
    if ((ek ==59)) {
      (void)((u8t = pipeline_type_ensure_by_kind_ord(arena, 2)));
      if ((u8t <=0)) {
        return 0;
      }
      return pipeline_type_find_or_alloc_compound(arena, 9, u8t, 0);
    }
    return 0;
  }
}
int32_t pipeline_typeck_named_is_module_type_c(struct ast_Module * m, struct ast_ASTArena * a, uint8_t * nm, int32_t nlen) {
  return typeck_named_is_module_type(m, a, nm, nlen);
}
int32_t pipeline_typeck_call_arg_effective_type_c(struct ast_ASTArena * a, int32_t arg_ref) {
  return typeck_call_arg_effective_type(a, arg_ref);
}
int32_t glue_typeck_type_tree_has_free_param_c(struct ast_Module * mod, struct ast_ASTArena * arena, int32_t ty, int32_t depth) {
  return typeck_type_tree_has_free_type_param(mod, arena, ty, depth);
}
int32_t typeck_try_infer_generic_call_from_args(struct ast_Module * callee_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t func_ix, int32_t expected_ret) {
  {
    int32_t np = 0;
    int32_t nargs = 0;
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;
    int32_t ord_named = 8;
    int32_t n_gp = 0;
    int32_t ret_ty = 0;
    uint8_t ret_nm[128] = {};
    int32_t ret_nlen = 0;
    int32_t value_ok = 1;
    int32_t arg_ref = 0;
    int32_t arg_ty = 0;
    int32_t pi_ty = 0;
    uint8_t pi_nm[128] = {};
    int32_t pi_nlen = 0;
    int32_t ai_ty = 0;
    int32_t pj_ty = 0;
    uint8_t pj_nm[128] = {};
    int32_t pj_nlen = 0;
    int32_t aj_ty = 0;
    int32_t same_name = 0;
    if (((((callee_mod ==0) || (arena ==0)) || (expr_ref <=0)) || (func_ix < 0))) {
      return -1;
    }
    (void)((np = pipeline_module_func_num_params_at(callee_mod, func_ix)));
    (void)((nargs = pipeline_expr_call_num_args_at(arena, expr_ref)));
    if (((np > 0) && (nargs >=np))) {
      (void)((value_ok = 1));
      (void)((i = 0));
      while ((i < np)) {
        (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i)));
        if ((arg_ref <=0)) {
          (void)((value_ok = 0));
          break;
        }
        (void)((arg_ty = typeck_call_arg_effective_type(arena, arg_ref)));
        if ((arg_ty <=0)) {
          (void)((value_ok = 0));
          break;
        }
        (void)((i = (i + 1)));
      }
      ((value_ok !=0) ? ({   (void)((i = 0));
  while ((i < np)) {
    (void)((pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i)));
    if (((pi_ty <=0) || (pipeline_type_kind_ord_at(arena, pi_ty) !=ord_named))) {
      (void)((i = (i + 1)));
      continue;
    }
    (void)((pi_nlen = pipeline_type_named_name_into(arena, pi_ty, &((pi_nm)[0]))));
    if ((pi_nlen <=0)) {
      (void)((i = (i + 1)));
      continue;
    }
    if ((typeck_named_is_module_type(callee_mod, arena, &((pi_nm)[0]), pi_nlen) !=0)) {
      (void)((i = (i + 1)));
      continue;
    }
    (void)((ai_ty = typeck_call_arg_effective_type(arena, pipeline_expr_call_arg_ref(arena, expr_ref, i))));
    if ((ai_ty <=0)) {
      return -1;
    }
    (void)((j = (i + 1)));
    while ((j < np)) {
      (void)((pj_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, j)));
      if (((pj_ty <=0) || (pipeline_type_kind_ord_at(arena, pj_ty) !=ord_named))) {
        (void)((j = (j + 1)));
        continue;
      }
      (void)((pj_nlen = pipeline_type_named_name_into(arena, pj_ty, &((pj_nm)[0]))));
      if ((pj_nlen !=pi_nlen)) {
        (void)((j = (j + 1)));
        continue;
      }
      (void)((same_name = 1));
      (void)((k = 0));
      while ((k < pi_nlen)) {
        if (((pi_nm)[k] !=(pj_nm)[k])) {
          (void)((same_name = 0));
          break;
        }
        (void)((k = (k + 1)));
      }
      if ((same_name ==0)) {
        (void)((j = (j + 1)));
        continue;
      }
      (void)((aj_ty = typeck_call_arg_effective_type(arena, pipeline_expr_call_arg_ref(arena, expr_ref, j))));
      if (((aj_ty <=0) || (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, ai_ty, aj_ty) ==0))) {
        return -1;
      }
      (void)((j = (j + 1)));
    }
    (void)((i = (i + 1)));
  }
  return 0;
 }) : 0);
    }
    (void)((n_gp = pipeline_module_func_num_generic_params_at(callee_mod, func_ix)));
    if ((n_gp < 1)) {
      return -1;
    }
    if (((expected_ret > 0) && (typeck_type_tree_has_free_type_param(callee_mod, arena, expected_ret, 0) ==0))) {
      (void)((ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix)));
      (((ret_ty > 0) && (pipeline_type_kind_ord_at(arena, ret_ty) ==ord_named)) ? ({   (void)((ret_nlen = pipeline_type_named_name_into(arena, ret_ty, &((ret_nm)[0]))));
  (((ret_nlen > 0) && (typeck_named_is_module_type(callee_mod, arena, &((ret_nm)[0]), ret_nlen) ==0)) ? ({   return 0;
 }) : 0);
 }) : 0);
    }
    (void)((ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix)));
    if ((ret_ty <=0)) {
      return -1;
    }
    if ((typeck_type_tree_has_free_type_param(callee_mod, arena, ret_ty, 0) !=0)) {
      return -1;
    }
    (void)((i = 0));
    while ((i < np)) {
      (void)((pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i)));
      if (((pi_ty > 0) && (typeck_type_tree_has_free_type_param(callee_mod, arena, pi_ty, 0) !=0))) {
        return -1;
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t typeck_check_inferred_generic_bounds(struct ast_Module * callee_mod, struct ast_ASTArena * arena, int32_t expr_ref, int32_t func_ix, uint8_t * fn_name, int32_t fn_name_len, int32_t line, int32_t col, int32_t expected_ret) {
  {
    int32_t max_targs = 4;
    int32_t stride = 128;
    uint8_t type_args_flat[512] = {};
    int32_t type_arg_lens[4] = {};
    uint8_t formal_names_flat[512] = {};
    int32_t formal_name_lens[4] = {};
    int32_t n_tp = 0;
    int32_t np = 0;
    int32_t i = 0;
    int32_t k = 0;
    int32_t ord_named = 8;
    int32_t ret_ty = 0;
    uint8_t ret_nm[128] = {};
    int32_t ret_nlen = 0;
    int32_t pi_ty = 0;
    uint8_t pi_nm[128] = {};
    int32_t pi_nlen = 0;
    int32_t arg_ref = 0;
    int32_t arg_ty = 0;
    int32_t found = 0;
    int32_t slot = 0;
    int32_t conc_len = 0;
    int32_t base = 0;
    int32_t bi = 0;
    int32_t found_r = 0;
    if (((((((callee_mod ==0) || (arena ==0)) || (expr_ref <=0)) || (func_ix < 0)) || (fn_name ==0)) || (fn_name_len <=0))) {
      return 0;
    }
    (void)((np = pipeline_module_func_num_params_at(callee_mod, func_ix)));
    (void)((n_tp = 0));
    (void)((i = 0));
    while (((i < np) && (n_tp < max_targs))) {
      (void)((pi_ty = pipeline_module_func_param_type_ref_at(callee_mod, func_ix, i)));
      if (((pi_ty <=0) || (pipeline_type_kind_ord_at(arena, pi_ty) !=ord_named))) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((pi_nlen = pipeline_type_named_name_into(arena, pi_ty, &((pi_nm)[0]))));
      if ((pi_nlen <=0)) {
        (void)((i = (i + 1)));
        continue;
      }
      if ((typeck_named_is_module_type(callee_mod, arena, &((pi_nm)[0]), pi_nlen) !=0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((found = -1));
      (void)((k = 0));
      while ((k < n_tp)) {
        if (((formal_name_lens)[k] ==pi_nlen)) {
          (void)((base = (k * stride)));
          (void)((bi = 0));
          while ((bi < pi_nlen)) {
            if (((formal_names_flat)[(base + bi)] !=(pi_nm)[bi])) {
              break;
            }
            (void)((bi = (bi + 1)));
          }
          ((bi ==pi_nlen) ? ({   (void)((found = k));
  break;
 }) : 0);
        }
        (void)((k = (k + 1)));
      }
      if ((found >=0)) {
        (void)((i = (i + 1)));
        continue;
      }
      (void)((slot = n_tp));
      (void)((base = (slot * stride)));
      (void)((bi = 0));
      while ((bi < pi_nlen)) {
        (void)(((formal_names_flat)[(base + bi)] = (pi_nm)[bi]));
        (void)((bi = (bi + 1)));
      }
      (void)(((formal_name_lens)[slot] = pi_nlen));
      (void)((arg_ref = pipeline_expr_call_arg_ref(arena, expr_ref, i)));
      (void)((arg_ty = 0));
      if ((arg_ref > 0)) {
        (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_ref)));
      }
      (void)((conc_len = 0));
      if (((arg_ty > 0) && (pipeline_type_kind_ord_at(arena, arg_ty) ==ord_named))) {
        (void)((conc_len = pipeline_type_named_name_into(arena, arg_ty, &((type_args_flat)[base]))));
        if ((conc_len < 0)) {
          (void)((conc_len = 0));
        }
        ((conc_len > 127) ? ({   (void)((conc_len = 63));
 }) : 0);
      }
      (void)(((type_arg_lens)[slot] = conc_len));
      (void)((n_tp = (n_tp + 1)));
      (void)((i = (i + 1)));
    }
    (void)((ret_ty = pipeline_module_func_return_type_at(callee_mod, func_ix)));
    if ((((ret_ty > 0) && (pipeline_type_kind_ord_at(arena, ret_ty) ==ord_named)) && (n_tp < max_targs))) {
      (void)((ret_nlen = pipeline_type_named_name_into(arena, ret_ty, &((ret_nm)[0]))));
      (((ret_nlen > 0) && (typeck_named_is_module_type(callee_mod, arena, &((ret_nm)[0]), ret_nlen) ==0)) ? ({   (void)((found_r = -1));
  (void)((k = 0));
  while ((k < n_tp)) {
    if (((formal_name_lens)[k] ==ret_nlen)) {
      (void)((base = (k * stride)));
      (void)((bi = 0));
      while ((bi < ret_nlen)) {
        if (((formal_names_flat)[(base + bi)] !=(ret_nm)[bi])) {
          break;
        }
        (void)((bi = (bi + 1)));
      }
      ((bi ==ret_nlen) ? ({   (void)((found_r = k));
  break;
 }) : 0);
    }
    (void)((k = (k + 1)));
  }
  ((((found_r < 0) && (expected_ret > 0)) && (pipeline_type_kind_ord_at(arena, expected_ret) ==ord_named)) ? ({   (void)((slot = n_tp));
  (void)((base = (slot * stride)));
  (void)((bi = 0));
  while ((bi < ret_nlen)) {
    (void)(((formal_names_flat)[(base + bi)] = (ret_nm)[bi]));
    (void)((bi = (bi + 1)));
  }
  (void)(((formal_name_lens)[slot] = ret_nlen));
  (void)((conc_len = pipeline_type_named_name_into(arena, expected_ret, &((type_args_flat)[base]))));
  if ((conc_len < 0)) {
    (void)((conc_len = 0));
  }
  if ((conc_len > 127)) {
    (void)((conc_len = 63));
  }
  (void)(((type_arg_lens)[slot] = conc_len));
  (void)((n_tp = (n_tp + 1)));
 }) : 0);
 }) : 0);
    }
    return xlang_generic_bound_check_type_args_c(fn_name, fn_name_len, &((type_args_flat)[0]), &((type_arg_lens)[0]), n_tp, line, col);
  }
}
int32_t typeck_check_call_generic_type_args(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) {
  {
    struct ast_Module * callee_mod = 0;
    int32_t func_ix = 0;
    int32_t dep_ix = 0;
    int32_t num_generic_params = 0;
    int32_t num_type_args = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t name[128] = {};
    int32_t name_len = 0;
    if ((((module ==0) || (arena ==0)) || (expr_ref <=0))) {
      return 0;
    }
    (void)((func_ix = pipeline_expr_call_resolved_func_index_at(arena, expr_ref)));
    if ((func_ix < 0)) {
      return 0;
    }
    (void)((dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, expr_ref)));
    (void)((callee_mod = module));
    if ((dep_ix >=0)) {
      (void)((callee_mod = pipeline_dep_ctx_module_at(ctx, dep_ix)));
      ((callee_mod ==0) ? ({   return 0;
 }) : 0);
    }
    (void)((num_generic_params = pipeline_module_func_num_generic_params_at(callee_mod, func_ix)));
    (void)((num_type_args = pipeline_expr_call_num_type_args_at(arena, expr_ref)));
    if (((num_generic_params ==0) && (num_type_args ==0))) {
      return 0;
    }
    (void)((line = pipeline_expr_line_at(arena, expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, expr_ref)));
    (void)((name_len = pipeline_module_func_name_len_at(callee_mod, func_ix)));
    if ((name_len > 127)) {
      (void)((name_len = 63));
    }
    if ((name_len > 0)) {
      (void)(pipeline_module_func_name_copy64(callee_mod, func_ix, &((name)[0])));
    }
    if (((num_type_args > 0) && (num_generic_params ==0))) {
      (void)(driver_diagnostic_typeck_call_not_generic(line, col, &((name)[0]), name_len));
      return -1;
    }
    if (((num_generic_params > 0) && (num_type_args ==0))) {
      if ((typeck_try_infer_generic_call_from_args(callee_mod, arena, expr_ref, func_ix, expected_ret) ==0)) {
        if ((typeck_check_inferred_generic_bounds(callee_mod, arena, expr_ref, func_ix, &((name)[0]), name_len, line, col, expected_ret) !=0)) {
          return -1;
        }
        return 0;
      }
      (void)(driver_diagnostic_typeck_call_requires_type_args(line, col, &((name)[0]), name_len));
      return -1;
    }
    if ((num_generic_params !=num_type_args)) {
      (void)(driver_diagnostic_typeck_call_wrong_num_type_args(line, col, &((name)[0]), name_len, num_generic_params, num_type_args));
      return -1;
    }
    return 0;
  }
}
int32_t pipeline_typeck_check_call_generic_type_args_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) {
  return typeck_check_call_generic_type_args(module, arena, expr_ref, ctx, expected_ret);
}
int32_t typeck_mono_map_lookup(uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, uint8_t * nm, int32_t nlen) {
  {
    int32_t i = 0;
    int32_t k = 0;
    int32_t base = 0;
    int32_t stride = 128;
    if (((((((names_flat ==0) || (lens ==0)) || (conc ==0)) || (nm ==0)) || (nlen <=0)) || (n_map <=0))) {
      return 0;
    }
    (void)((i = 0));
    while ((i < n_map)) {
      if (((lens)[i] ==nlen)) {
        (void)((base = (i * stride)));
        (void)((k = 0));
        while ((k < nlen)) {
          if (((names_flat)[(base + k)] !=(nm)[k])) {
            break;
          }
          (void)((k = (k + 1)));
        }
        ((k ==nlen) ? ({   return (conc)[i];
 }) : 0);
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
}
int32_t typeck_mono_map_bind(uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, uint8_t * nm, int32_t nlen, int32_t concrete_ty, struct ast_ASTArena * caller_arena) {
  {
    int32_t prev = 0;
    int32_t n = 0;
    int32_t base = 0;
    int32_t k = 0;
    int32_t stride = 128;
    if ((((((((((names_flat ==0) || (lens ==0)) || (conc ==0)) || (n_map ==0)) || (nm ==0)) || (nlen <=0)) || (nlen > 127)) || (concrete_ty <=0)) || (max_map <=0))) {
      return -1;
    }
    (void)((n = typeck_i32_ptr_read(n_map)));
    (void)((prev = typeck_mono_map_lookup(names_flat, lens, conc, n, nm, nlen)));
    if ((prev > 0)) {
      if (((caller_arena !=0) && (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(caller_arena, prev, concrete_ty) ==0))) {
        return -1;
      }
      return 0;
    }
    if ((n >=max_map)) {
      return -1;
    }
    (void)((base = (n * stride)));
    (void)((k = 0));
    while ((k < 64)) {
      (void)(((names_flat)[(base + k)] = 0));
      (void)((k = (k + 1)));
    }
    (void)((k = 0));
    while ((k < nlen)) {
      (void)(((names_flat)[(base + k)] = (nm)[k]));
      (void)((k = (k + 1)));
    }
    (void)(((lens)[n] = nlen));
    (void)(((conc)[n] = concrete_ty));
    (void)(typeck_i32_ptr_store(n_map, (n + 1)));
    return 0;
  }
}
int32_t typeck_named_num_type_args_ASTArena_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t ty) {
  {
    int32_t n = 0;
    int32_t asz = 0;
    int32_t i = 0;
    int32_t max_targs = 8;
    if (((arena ==0) || (ty <=0))) {
      return 0;
    }
    (void)((asz = pipeline_type_array_size_at(arena, ty)));
    if (((asz > 0) && (asz <=max_targs))) {
      return asz;
    }
    (void)((n = 0));
    (void)((i = 0));
    while ((i < max_targs)) {
      if ((pipeline_type_type_arg_ref_at(arena, ty, i) <=0)) {
        break;
      }
      (void)((n = (i + 1)));
      (void)((i = (i + 1)));
    }
    return n;
  }
}
int32_t typeck_alloc_named_with_type_args_flat(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len, int32_t * arg_refs, int32_t n_args) {
  {
    int32_t tr = 0;
    int32_t i = 0;
    int32_t ar = 0;
    int32_t max_targs = 8;
    if (((((arena ==0) || (name ==0)) || (name_len <=0)) || (name_len > 127))) {
      return 0;
    }
    if ((((n_args < 0) || (n_args > max_targs)) || (arg_refs ==0))) {
      return 0;
    }
    (void)((tr = pipeline_arena_type_alloc(arena)));
    if ((tr <=0)) {
      return 0;
    }
    if ((pipeline_type_init_named_at(arena, tr, name, name_len) ==0)) {
      return 0;
    }
    (void)((i = 0));
    while ((i < n_args)) {
      (void)((ar = (arg_refs)[i]));
      if ((ar <=0)) {
        return 0;
      }
      if ((pipeline_type_append_type_arg(arena, tr, ar) !=0)) {
        return 0;
      }
      (void)((i = (i + 1)));
    }
    if ((n_args > 0)) {
      ((pipeline_type_set_elem_array_size_at(arena, tr, (arg_refs)[0], n_args) ==0) ? ({   return 0;
 }) : 0);
    }
    return tr;
  }
}
int32_t typeck_pattern_unify_bind(struct ast_Module * mod, struct ast_ASTArena * formal_arena, int32_t formal_ty, struct ast_ASTArena * arg_arena, int32_t arg_ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, int32_t depth) {
  {
    int32_t fk = 0;
    int32_t ak = 0;
    int32_t fnlen = 0;
    uint8_t fnm[128] = {};
    int32_t anlen = 0;
    uint8_t anm[128] = {};
    int32_t n_fta = 0;
    int32_t n_ata = 0;
    int32_t i = 0;
    int32_t fta = 0;
    int32_t ata = 0;
    int32_t felem = 0;
    int32_t aelem = 0;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_vector = 13;
    int32_t max_depth = 12;
    if ((((((((((mod ==0) || (formal_arena ==0)) || (arg_arena ==0)) || (names_flat ==0)) || (lens ==0)) || (conc ==0)) || (n_map ==0)) || (formal_ty <=0)) || (arg_ty <=0))) {
      return -1;
    }
    if ((depth > max_depth)) {
      return -1;
    }
    (void)((fk = pipeline_type_kind_ord_at(formal_arena, formal_ty)));
    (void)((ak = pipeline_type_kind_ord_at(arg_arena, arg_ty)));
    if (((fk < 0) || (ak < 0))) {
      return -1;
    }
    if ((fk ==ord_named)) {
      (void)((fnlen = pipeline_type_named_name_into(formal_arena, formal_ty, &((fnm)[0]))));
      if ((fnlen <=0)) {
        return -1;
      }
      if ((typeck_named_is_module_type(mod, formal_arena, &((fnm)[0]), fnlen) ==0)) {
        return typeck_mono_map_bind(names_flat, lens, conc, n_map, max_map, &((fnm)[0]), fnlen, arg_ty, arg_arena);
      }
      if ((ak !=ord_named)) {
        return -1;
      }
      (void)((anlen = pipeline_type_named_name_into(arg_arena, arg_ty, &((anm)[0]))));
      if (((anlen <=0) || !(typeck_name_equal(&((fnm)[0]), fnlen, &((anm)[0]), anlen)))) {
        return -1;
      }
      (void)((n_fta = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(formal_arena, formal_ty)));
      if ((n_fta <=0)) {
        return 0;
      }
      (void)((n_ata = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(arg_arena, arg_ty)));
      if ((n_ata <=0)) {
        (void)((aelem = pipeline_type_elem_ref_at(arg_arena, arg_ty)));
        ((aelem > 0) ? ({   (void)((n_ata = 1));
 }) : 0);
      }
      if ((n_ata < n_fta)) {
        return -1;
      }
      (void)((i = 0));
      while ((i < n_fta)) {
        (void)((fta = pipeline_type_type_arg_ref_at(formal_arena, formal_ty, i)));
        if (((fta <=0) && (i ==0))) {
          (void)((fta = pipeline_type_elem_ref_at(formal_arena, formal_ty)));
        }
        (void)((ata = pipeline_type_type_arg_ref_at(arg_arena, arg_ty, i)));
        if (((ata <=0) && (i ==0))) {
          (void)((ata = pipeline_type_elem_ref_at(arg_arena, arg_ty)));
        }
        if (((fta <=0) || (ata <=0))) {
          return -1;
        }
        if ((typeck_pattern_unify_bind(mod, formal_arena, fta, arg_arena, ata, names_flat, lens, conc, n_map, max_map, (depth + 1)) !=0)) {
          return -1;
        }
        (void)((i = (i + 1)));
      }
      return 0;
    }
    if (((((fk ==ord_ptr) || (fk ==ord_slice)) || (fk ==ord_array)) || (fk ==ord_vector))) {
      if ((ak !=fk)) {
        return -1;
      }
      (void)((felem = pipeline_type_elem_ref_at(formal_arena, formal_ty)));
      (void)((aelem = pipeline_type_elem_ref_at(arg_arena, arg_ty)));
      if (((felem <=0) || (aelem <=0))) {
        return -1;
      }
      if (((fk ==ord_array) || (fk ==ord_vector))) {
        ((pipeline_type_array_size_at(formal_arena, formal_ty) !=pipeline_type_array_size_at(arg_arena, arg_ty)) ? ({   return -1;
 }) : 0);
      }
      return typeck_pattern_unify_bind(mod, formal_arena, felem, arg_arena, aelem, names_flat, lens, conc, n_map, max_map, (depth + 1));
    }
    if ((fk ==ak)) {
      return 0;
    }
    return -1;
  }
}
int32_t typeck_build_value_formal_mono_map(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t max_map) {
  {
    int32_t n_map_local = 0;
    int32_t * n_map_ptr = 0;
    int32_t num_params = 0;
    int32_t pi = 0;
    int32_t param_ty = 0;
    int32_t arg_i = 0;
    int32_t arg_ty = 0;
    int32_t ord_named = 8;
    uint8_t param_nm[128] = {};
    int32_t param_nlen = 0;
    int32_t gi = 0;
    int32_t dup = 0;
    int32_t base = 0;
    int32_t k = 0;
    int32_t stride = 128;
    if ((((((((((search_mod ==0) || (search_arena ==0)) || (caller_arena ==0)) || (call_expr_ref <=0)) || (func_idx < 0)) || (names_flat ==0)) || (lens ==0)) || (conc ==0)) || (max_map <=0))) {
      return 0;
    }
    (void)((n_map_local = 0));
    (void)((n_map_ptr = &(n_map_local)));
    (void)((num_params = pipeline_module_func_num_params_at(search_mod, func_idx)));
    (void)((pi = 0));
    while (((pi < num_params) && (n_map_local < max_map))) {
      (void)((param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi)));
      if ((param_ty <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((arg_i = pipeline_expr_call_arg_ref(caller_arena, call_expr_ref, pi)));
      if ((arg_i <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((arg_ty = pipeline_expr_resolved_type_ref(caller_arena, arg_i)));
      if ((arg_ty <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      if ((pipeline_type_kind_ord_at(search_arena, param_ty) ==ord_named)) {
        (void)((param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &((param_nm)[0]))));
        (((param_nlen > 0) && (typeck_named_is_module_type(search_mod, search_arena, &((param_nm)[0]), param_nlen) ==0)) ? ({   (void)((dup = 0));
  (void)((gi = 0));
  while ((gi < n_map_local)) {
    if (((lens)[gi] ==param_nlen)) {
      (void)((base = (gi * stride)));
      (void)((k = 0));
      while ((k < param_nlen)) {
        if (((names_flat)[(base + k)] !=(param_nm)[k])) {
          break;
        }
        (void)((k = (k + 1)));
      }
      ((k ==param_nlen) ? ({   (void)((dup = 1));
  break;
 }) : 0);
    }
    (void)((gi = (gi + 1)));
  }
  if ((dup ==0)) {
    if ((typeck_mono_map_bind(names_flat, lens, conc, n_map_ptr, max_map, &((param_nm)[0]), param_nlen, arg_ty, caller_arena) !=0)) {
      return 0;
    }
    (void)((n_map_local = typeck_i32_ptr_read(n_map_ptr)));
  }
  (void)((pi = (pi + 1)));
  continue;
 }) : 0);
      }
      if ((typeck_type_tree_has_free_type_param(search_mod, search_arena, param_ty, 0) !=0)) {
        if ((typeck_pattern_unify_bind(search_mod, search_arena, param_ty, caller_arena, arg_ty, names_flat, lens, conc, n_map_ptr, max_map, 0) !=0)) {
          (void)((pi = (pi + 1)));
          continue;
        }
        (void)((n_map_local = typeck_i32_ptr_read(n_map_ptr)));
      }
      (void)((pi = (pi + 1)));
    }
    return n_map_local;
  }
}
int32_t typeck_subst_type_ref(struct ast_Module * mod, struct ast_ASTArena * src_arena, struct ast_ASTArena * dst_arena, int32_t ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, int32_t depth) {
  {
    int32_t kind = 0;
    int32_t nlen = 0;
    uint8_t nm[128] = {};
    int32_t n_ta = 0;
    int32_t i = 0;
    int32_t ta = 0;
    int32_t sa = 0;
    int32_t args[8] = {};
    int32_t elem = 0;
    int32_t mapped_elem = 0;
    int32_t asz = 0;
    int32_t looked = 0;
    int32_t max_depth = 12;
    int32_t ord_named = 8;
    int32_t ord_ptr = 9;
    int32_t ord_array = 10;
    int32_t ord_slice = 11;
    int32_t ord_vector = 13;
    int32_t ord_i32 = 0;
    int32_t ord_bool = 1;
    int32_t ord_u8 = 2;
    int32_t ord_u32 = 3;
    int32_t ord_u64 = 4;
    int32_t ord_i64 = 5;
    int32_t ord_usize = 6;
    int32_t ord_isize = 7;
    int32_t ord_f32 = 14;
    int32_t ord_f64 = 15;
    int32_t ord_void = 16;
    if ((((((mod ==0) || (src_arena ==0)) || (dst_arena ==0)) || (ty <=0)) || (depth > max_depth))) {
      return 0;
    }
    (void)((kind = pipeline_type_kind_ord_at(src_arena, ty)));
    if ((kind < 0)) {
      return 0;
    }
    if ((((((((((((kind ==ord_i32) || (kind ==ord_i64)) || (kind ==ord_bool)) || (kind ==ord_f64)) || (kind ==ord_u8)) || (kind ==ord_u32)) || (kind ==ord_u64)) || (kind ==ord_isize)) || (kind ==ord_f32)) || (kind ==ord_usize)) || (kind ==ord_void))) {
      return pipeline_type_ensure_by_kind_ord(dst_arena, kind);
    }
    if ((kind ==ord_named)) {
      (void)((nlen = pipeline_type_named_name_into(src_arena, ty, &((nm)[0]))));
      if ((nlen <=0)) {
        return 0;
      }
      if ((typeck_named_is_module_type(mod, src_arena, &((nm)[0]), nlen) ==0)) {
        (void)((looked = typeck_mono_map_lookup(names_flat, lens, conc, n_map, &((nm)[0]), nlen)));
        if ((looked > 0)) {
          return looked;
        }
        return 0;
      }
      (void)((n_ta = typeck_named_num_type_args_ASTArena_ptr_i32_reti32(src_arena, ty)));
      if ((n_ta <=0)) {
        return pipeline_type_find_or_alloc_named(dst_arena, &((nm)[0]), nlen);
      }
      (void)((i = 0));
      while ((i < n_ta)) {
        (void)((ta = pipeline_type_type_arg_ref_at(src_arena, ty, i)));
        if ((ta <=0)) {
          return 0;
        }
        (void)((sa = typeck_subst_type_ref(mod, src_arena, dst_arena, ta, names_flat, lens, conc, n_map, (depth + 1))));
        if ((sa <=0)) {
          return 0;
        }
        (void)(((args)[i] = sa));
        (void)((i = (i + 1)));
      }
      return typeck_alloc_named_with_type_args_flat(dst_arena, &((nm)[0]), nlen, &((args)[0]), n_ta);
    }
    (void)((elem = pipeline_type_elem_ref_at(src_arena, ty)));
    (void)((mapped_elem = 0));
    if ((elem > 0)) {
      (void)((mapped_elem = typeck_subst_type_ref(mod, src_arena, dst_arena, elem, names_flat, lens, conc, n_map, (depth + 1))));
      ((mapped_elem <=0) ? ({   return 0;
 }) : 0);
    }
    (void)((asz = pipeline_type_array_size_at(src_arena, ty)));
    if ((kind ==ord_ptr)) {
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_ptr, mapped_elem, 0);
    }
    if ((kind ==ord_vector)) {
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_vector, mapped_elem, asz);
    }
    if ((kind ==ord_array)) {
      if (((mapped_elem <=0) || (asz <=0))) {
        return 0;
      }
      return pipeline_type_find_or_alloc_compound(dst_arena, ord_array, mapped_elem, asz);
    }
    if ((kind ==ord_slice)) {
      return pipeline_type_find_or_alloc_slice(dst_arena, mapped_elem, 0, 0);
    }
    return 0;
  }
}
int32_t glue_typeck_pattern_unify_bind_c(struct ast_Module * mod, struct ast_ASTArena * formal_arena, int32_t formal_ty, struct ast_ASTArena * arg_arena, int32_t arg_ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t * n_map, int32_t max_map, int32_t depth) {
  return typeck_pattern_unify_bind(mod, formal_arena, formal_ty, arg_arena, arg_ty, names_flat, lens, conc, n_map, max_map, depth);
}
int32_t glue_typeck_subst_type_ref_c(struct ast_Module * mod, struct ast_ASTArena * src_arena, struct ast_ASTArena * dst_arena, int32_t ty, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t n_map, int32_t depth) {
  return typeck_subst_type_ref(mod, src_arena, dst_arena, ty, names_flat, lens, conc, n_map, depth);
}
int32_t glue_typeck_build_value_formal_mono_map_c(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, uint8_t * names_flat, int32_t * lens, int32_t * conc, int32_t max_map) {
  return typeck_build_value_formal_mono_map(search_mod, search_arena, caller_arena, call_expr_ref, func_idx, names_flat, lens, conc, max_map);
}
int32_t typeck_generic_call_subst_ret_from_formal_map(struct ast_Module * search_mod, struct ast_ASTArena * search_arena, struct ast_ASTArena * caller_arena, int32_t call_expr_ref, int32_t func_idx, int32_t ret_ty) {
  {
    int32_t ord_named = 8;
    int32_t n_map = 0;
    uint8_t names_flat[1024] = {};
    int32_t lens[8] = {};
    int32_t conc[8] = {};
    uint8_t ret_nm[128] = {};
    int32_t ret_nlen = 0;
    int32_t mono_ret = 0;
    int32_t max_map = 8;
    if (((((((search_mod ==0) || (search_arena ==0)) || (caller_arena ==0)) || (call_expr_ref <=0)) || (func_idx < 0)) || (ret_ty <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(search_arena, ret_ty) !=ord_named)) {
      return 0;
    }
    (void)((ret_nlen = pipeline_type_named_name_into(search_arena, ret_ty, &((ret_nm)[0]))));
    if ((ret_nlen <=0)) {
      return 0;
    }
    (void)((n_map = typeck_build_value_formal_mono_map(search_mod, search_arena, caller_arena, call_expr_ref, func_idx, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), max_map)));
    if ((n_map <=0)) {
      return 0;
    }
    if ((typeck_named_is_module_type(search_mod, search_arena, &((ret_nm)[0]), ret_nlen) ==0)) {
      (void)((mono_ret = typeck_subst_type_ref(search_mod, search_arena, caller_arena, ret_ty, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), n_map, 0)));
      if ((mono_ret > 0)) {
        return mono_ret;
      }
      return 0;
    }
    if ((typeck_type_tree_has_free_type_param(search_mod, search_arena, ret_ty, 0) ==0)) {
      return 0;
    }
    (void)((mono_ret = typeck_subst_type_ref(search_mod, search_arena, caller_arena, ret_ty, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), n_map, 0)));
    if ((mono_ret <=0)) {
      return 0;
    }
    if ((typeck_type_tree_has_free_type_param(search_mod, caller_arena, mono_ret, 0) !=0)) {
      return 0;
    }
    return mono_ret;
  }
}
int32_t typeck_method_call_generic_ufcs(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args) {
  {
    int32_t nf = 0;
    int32_t fi = 0;
    int32_t nparams = 0;
    int32_t p0 = 0;
    int32_t g_ret = 0;
    int32_t g_ai = 0;
    int32_t g_matched = 0;
    uint8_t names_flat[1024] = {};
    int32_t lens[8] = {};
    int32_t conc[8] = {};
    int32_t g_nmap = 0;
    int32_t g_param = 0;
    int32_t g_arg_ref = 0;
    int32_t g_arg_ty = 0;
    int32_t g_sub = 0;
    int32_t g_mono = 0;
    int32_t max_map = 8;
    if (((((((module ==0) || (arena ==0)) || (expr_ref <=0)) || (base_ty <=0)) || (method_nm ==0)) || (method_nlen <=0))) {
      return 0;
    }
    (void)((nf = pipeline_module_num_funcs(module)));
    (void)((fi = 0));
    while ((fi < nf)) {
      if ((pipeline_module_func_name_equal_at(module, fi, method_nm, method_nlen) ==0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((nparams = pipeline_module_func_num_params_at(module, fi)));
      if ((nparams !=(num_args + 1))) {
        (void)((fi = (fi + 1)));
        continue;
      }
      if ((pipeline_module_func_num_generic_params_at(module, fi) <=0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((p0 = pipeline_module_func_param_type_ref_at(module, fi, 0)));
      if ((p0 <=0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      if ((typeck_type_tree_has_free_type_param(module, arena, p0, 0) ==0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((g_nmap = 0));
      if (((typeck_pattern_unify_bind(module, arena, p0, arena, base_ty, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), &(g_nmap), max_map, 0) !=0) || (g_nmap <=0))) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((g_matched = 1));
      (void)((g_ai = 0));
      while ((g_ai < num_args)) {
        (void)((g_param = pipeline_module_func_param_type_ref_at(module, fi, (g_ai + 1))));
        (void)((g_arg_ref = pipeline_expr_method_call_arg_ref(arena, expr_ref, g_ai)));
        if ((g_arg_ref > 0)) {
          (void)((g_arg_ty = pipeline_expr_resolved_type_ref(arena, g_arg_ref)));
        } else {
          (void)((g_arg_ty = 0));
        }
        if (((g_param <=0) || (g_arg_ty <=0))) {
          (void)((g_matched = 0));
          break;
        }
        if ((pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, g_arg_ty, g_param) !=0)) {
          (void)((g_ai = (g_ai + 1)));
          continue;
        }
        (void)((g_sub = typeck_subst_type_ref(module, arena, arena, g_param, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), g_nmap, 0)));
        if (((g_sub <=0) || (pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(arena, g_arg_ty, g_sub) ==0))) {
          (void)((g_matched = 0));
          break;
        }
        (void)((g_ai = (g_ai + 1)));
      }
      if ((g_matched ==0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((g_ret = pipeline_module_func_return_type_at(module, fi)));
      if ((g_ret <=0)) {
        (void)((fi = (fi + 1)));
        continue;
      }
      (void)((g_mono = typeck_subst_type_ref(module, arena, arena, g_ret, &((names_flat)[0]), &((lens)[0]), &((conc)[0]), g_nmap, 0)));
      if (((g_mono > 0) && (typeck_type_tree_has_free_type_param(module, arena, g_mono, 0) ==0))) {
        (void)(pipeline_expr_apply_call_resolve(arena, expr_ref, -1, fi));
        (void)(pipeline_expr_set_resolved_type_ref(arena, expr_ref, g_mono));
        return 1;
      }
      (void)((fi = (fi + 1)));
    }
    return 0;
  }
}
int32_t typeck_generic_call_fixup_resolved_type(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) {
  {
    int32_t ord_var = 3;
    int32_t ord_field = 44;
    int32_t ord_named = 8;
    int32_t callee_ref = 0;
    int32_t callee_eff = 0;
    int32_t callee_kind = 0;
    int32_t func_idx = 0;
    int32_t ret_ty = 0;
    int32_t param_ty = 0;
    uint8_t ret_nm[128] = {};
    uint8_t param_nm[128] = {};
    int32_t ret_nlen = 0;
    int32_t param_nlen = 0;
    int32_t arg_i = 0;
    int32_t arg_ty = 0;
    int32_t num_params = 0;
    int32_t pi = 0;
    uint8_t cnm[128] = {};
    int32_t cnml = 0;
    int32_t j = 0;
    int32_t dep_ix = 0;
    struct ast_Module * search_mod = 0;
    struct ast_ASTArena * search_arena = 0;
    int32_t cur = 0;
    struct ast_Module * dm = 0;
    struct ast_ASTArena * da = 0;
    int32_t nd = 0;
    int32_t di = 0;
    int32_t n_map_c = 0;
    uint8_t map_names_c[1024] = {};
    int32_t map_lens_c[8] = {};
    int32_t map_conc_c[8] = {};
    int32_t mono_ret_c = 0;
    int32_t mono_ret = 0;
    int32_t n_gp = 0;
    int32_t n_ta = 0;
    int32_t ta_ty = 0;
    int32_t ret_is_module_type = 0;
    int32_t gnames_n = 0;
    uint8_t gnames[1024] = {};
    int32_t glens[8] = {};
    int32_t gidx = 0;
    int32_t found_gi = 0;
    int32_t is_mod = 0;
    int32_t max_map = 8;
    int32_t stride = 128;
    int32_t base = 0;
    int32_t k = 0;
    int32_t ci = 0;
    if ((((module ==0) || (arena ==0)) || (call_expr_ref <=0))) {
      return 0;
    }
    (void)((cur = pipeline_expr_resolved_type_ref(arena, call_expr_ref)));
    if (((cur > 0) && (typeck_type_tree_has_free_type_param(module, arena, cur, 0) ==0))) {
      return 0;
    }
    (void)((callee_ref = pipeline_expr_call_callee_ref_at(arena, call_expr_ref)));
    (void)((callee_eff = callee_ref));
    (void)((callee_kind = pipeline_expr_kind_ord_at(arena, callee_eff)));
    (void)((cnml = 0));
    (void)((search_mod = module));
    (void)((search_arena = arena));
    (void)((dep_ix = pipeline_expr_call_resolved_dep_index_at(arena, call_expr_ref)));
    (void)((func_idx = pipeline_expr_call_resolved_func_index_at(arena, call_expr_ref)));
    if ((callee_kind ==ord_var)) {
      (void)((cnml = pipeline_expr_var_name_len(arena, callee_eff)));
      if (((cnml <=0) || (cnml > 127))) {
        return 0;
      }
      (void)(pipeline_expr_var_name_into(arena, callee_eff, &((cnm)[0])));
    } else {
      ((callee_kind ==ord_field) ? ({   (void)((cnml = pipeline_expr_field_access_name_len(arena, callee_eff)));
  if (((cnml <=0) || (cnml > 127))) {
    return 0;
  }
  (void)(pipeline_expr_field_access_name_into(arena, callee_eff, &((cnm)[0])));
 }) : ({   return 0;
 }));
    }
    if ((((dep_ix >=0) && (ctx !=0)) && (dep_ix < pipeline_dep_ctx_ndep(ctx)))) {
      (void)((dm = pipeline_dep_ctx_module_at(ctx, dep_ix)));
      (void)((da = pipeline_dep_ctx_arena_at(ctx, dep_ix)));
      ((dm !=0) ? ({   (void)((search_mod = dm));
  ((da !=0) ? ({   (void)((search_arena = da));
 }) : 0);
 }) : 0);
    }
    if ((func_idx < 0)) {
      (void)((j = 0));
      while ((j < pipeline_module_num_funcs(search_mod))) {
        if ((pipeline_module_func_name_equal_at(search_mod, j, &((cnm)[0]), cnml) !=0)) {
          (void)((func_idx = j));
          break;
        }
        (void)((j = (j + 1)));
      }
    }
    if (((func_idx < 0) && (ctx !=0))) {
      (void)((nd = pipeline_dep_ctx_ndep(ctx)));
      (void)((di = 0));
      while (((di < nd) && (func_idx < 0))) {
        (void)((dm = pipeline_dep_ctx_module_at(ctx, di)));
        if ((dm ==0)) {
          (void)((di = (di + 1)));
          continue;
        }
        (void)((j = 0));
        while ((j < pipeline_module_num_funcs(dm))) {
          if ((pipeline_module_func_name_equal_at(dm, j, &((cnm)[0]), cnml) !=0)) {
            (void)((func_idx = j));
            (void)((search_mod = dm));
            (void)((da = pipeline_dep_ctx_arena_at(ctx, di)));
            if ((da !=0)) {
              (void)((search_arena = da));
            }
            break;
          }
          (void)((j = (j + 1)));
        }
        (void)((di = (di + 1)));
      }
    }
    if ((func_idx < 0)) {
      return 0;
    }
    (void)((ret_ty = pipeline_module_func_return_type_at(search_mod, func_idx)));
    if ((ret_ty <=0)) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(search_arena, ret_ty) !=ord_named)) {
      if ((typeck_type_tree_has_free_type_param(search_mod, search_arena, ret_ty, 0) ==0)) {
        return 0;
      }
      (void)((n_map_c = typeck_build_value_formal_mono_map(search_mod, search_arena, arena, call_expr_ref, func_idx, &((map_names_c)[0]), &((map_lens_c)[0]), &((map_conc_c)[0]), max_map)));
      if ((n_map_c <=0)) {
        return 0;
      }
      (void)((mono_ret_c = typeck_subst_type_ref(search_mod, search_arena, arena, ret_ty, &((map_names_c)[0]), &((map_lens_c)[0]), &((map_conc_c)[0]), n_map_c, 0)));
      if ((mono_ret_c <=0)) {
        return 0;
      }
      if ((typeck_type_tree_has_free_type_param(search_mod, arena, mono_ret_c, 0) !=0)) {
        return 0;
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, mono_ret_c));
      return 0;
    }
    (void)((ret_nlen = pipeline_type_named_name_into(search_arena, ret_ty, &((ret_nm)[0]))));
    if ((ret_nlen <=0)) {
      return 0;
    }
    (void)((num_params = pipeline_module_func_num_params_at(search_mod, func_idx)));
    (void)((pi = 0));
    while ((pi < num_params)) {
      (void)((param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi)));
      if (((param_ty <=0) || (pipeline_type_kind_ord_at(search_arena, param_ty) !=ord_named))) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &((param_nm)[0]))));
      if (((param_nlen <=0) || !(typeck_name_equal(&((ret_nm)[0]), ret_nlen, &((param_nm)[0]), param_nlen)))) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((arg_i = pipeline_expr_call_arg_ref(arena, call_expr_ref, pi)));
      if ((arg_i <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((arg_ty = pipeline_expr_resolved_type_ref(arena, arg_i)));
      if ((arg_ty <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, arg_ty));
      return 0;
    }
    (void)((mono_ret = typeck_generic_call_subst_ret_from_formal_map(search_mod, search_arena, arena, call_expr_ref, func_idx, ret_ty)));
    if ((mono_ret > 0)) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, mono_ret));
      return 0;
    }
    (void)((n_gp = pipeline_module_func_num_generic_params_at(search_mod, func_idx)));
    (void)((n_ta = pipeline_expr_call_num_type_args_at(arena, call_expr_ref)));
    (void)((ret_is_module_type = typeck_named_is_module_type(search_mod, search_arena, &((ret_nm)[0]), ret_nlen)));
    if ((ret_is_module_type !=0)) {
      return 0;
    }
    if (((((n_gp > 0) && (n_ta ==0)) && (expected_ret > 0)) && (typeck_type_tree_has_free_type_param(search_mod, arena, expected_ret, 0) ==0))) {
      (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, expected_ret));
      return 0;
    }
    if ((((n_gp <=0) || (n_ta <=0)) || (n_ta !=n_gp))) {
      return 0;
    }
    (void)((found_gi = xlang_generic_func_type_param_index_c(&((cnm)[0]), cnml, &((ret_nm)[0]), ret_nlen)));
    if (((found_gi >=0) && (found_gi < n_ta))) {
      (void)((ta_ty = pipeline_expr_call_type_arg_ref_at(arena, call_expr_ref, found_gi)));
      ((ta_ty > 0) ? ({   (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, ta_ty));
  return 0;
 }) : 0);
    }
    (void)((gnames_n = 0));
    (void)((pi = 0));
    while (((pi < num_params) && (gnames_n < 8))) {
      (void)((param_ty = pipeline_module_func_param_type_ref_at(search_mod, func_idx, pi)));
      if (((param_ty <=0) || (pipeline_type_kind_ord_at(search_arena, param_ty) !=ord_named))) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((param_nlen = pipeline_type_named_name_into(search_arena, param_ty, &((param_nm)[0]))));
      if ((param_nlen <=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((is_mod = typeck_named_is_module_type(search_mod, search_arena, &((param_nm)[0]), param_nlen)));
      if ((is_mod !=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((found_gi = -1));
      (void)((gidx = 0));
      while ((gidx < gnames_n)) {
        if (((glens)[gidx] ==param_nlen)) {
          (void)((base = (gidx * stride)));
          (void)((k = 0));
          while ((k < param_nlen)) {
            if (((gnames)[(base + k)] !=(param_nm)[k])) {
              break;
            }
            (void)((k = (k + 1)));
          }
          ((k ==param_nlen) ? ({   (void)((found_gi = gidx));
  break;
 }) : 0);
        }
        (void)((gidx = (gidx + 1)));
      }
      if ((found_gi >=0)) {
        (void)((pi = (pi + 1)));
        continue;
      }
      (void)((base = (gnames_n * stride)));
      (void)((k = 0));
      while ((k < 64)) {
        (void)(((gnames)[(base + k)] = 0));
        (void)((k = (k + 1)));
      }
      (void)((ci = 0));
      while (((ci < param_nlen) && (ci < 63))) {
        (void)(((gnames)[(base + ci)] = (param_nm)[ci]));
        (void)((ci = (ci + 1)));
      }
      (void)(((glens)[gnames_n] = param_nlen));
      (void)((gnames_n = (gnames_n + 1)));
      (void)((pi = (pi + 1)));
    }
    (void)((found_gi = -1));
    (void)((gidx = 0));
    while ((gidx < gnames_n)) {
      if (((glens)[gidx] ==ret_nlen)) {
        (void)((base = (gidx * stride)));
        (void)((k = 0));
        while ((k < ret_nlen)) {
          if (((gnames)[(base + k)] !=(ret_nm)[k])) {
            break;
          }
          (void)((k = (k + 1)));
        }
        ((k ==ret_nlen) ? ({   (void)((found_gi = gidx));
  break;
 }) : 0);
      }
      (void)((gidx = (gidx + 1)));
    }
    if (((found_gi < 0) && (gnames_n < 8))) {
      (void)((base = (gnames_n * stride)));
      (void)((k = 0));
      while ((k < 64)) {
        (void)(((gnames)[(base + k)] = 0));
        (void)((k = (k + 1)));
      }
      (void)((ci = 0));
      while (((ci < ret_nlen) && (ci < 63))) {
        (void)(((gnames)[(base + ci)] = (ret_nm)[ci]));
        (void)((ci = (ci + 1)));
      }
      (void)(((glens)[gnames_n] = ret_nlen));
      (void)((found_gi = gnames_n));
      (void)((gnames_n = (gnames_n + 1)));
    }
    if ((found_gi < 0)) {
      return 0;
    }
    if ((n_gp ==1)) {
      (void)((found_gi = 0));
    } else {
      (((n_gp > 1) && (gnames_n !=n_gp)) ? ({   return 0;
 }) : 0);
    }
    (void)((ta_ty = pipeline_expr_call_type_arg_ref_at(arena, call_expr_ref, found_gi)));
    if ((ta_ty <=0)) {
      return 0;
    }
    (void)(pipeline_expr_set_resolved_type_ref(arena, call_expr_ref, ta_ty));
    return 0;
  }
}
int32_t pipeline_typeck_method_call_generic_ufcs_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t base_ty, uint8_t * method_nm, int32_t method_nlen, int32_t num_args) {
  return typeck_method_call_generic_ufcs(module, arena, expr_ref, base_ty, method_nm, method_nlen, num_args);
}
int32_t glue_generic_call_fixup_resolved_type_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) {
  return typeck_generic_call_fixup_resolved_type(module, arena, call_expr_ref, ctx, expected_ret);
}
void pipeline_typeck_set_entry_module_for_dep_map_c(struct ast_Module * module) {
  (void)((g_typeck_entry_module_for_dep_map = module));
}
int32_t pipeline_typeck_get_dep_return_type_in_caller_arena_c(int32_t from_dep_index, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena, struct ast_PipelineDepCtx * ctx) {
  return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, dep_return_type_ref, caller_arena, ctx);
}
int32_t pipeline_typeck_dep_return_type_to_caller_arena_c(struct ast_ASTArena * dep_arena, int32_t dep_return_type_ref, struct ast_ASTArena * caller_arena) {
  return typeck_dep_return_type_to_caller_arena(dep_arena, dep_return_type_ref, caller_arena);
}
int32_t pipeline_typeck_expr_var_name_equal_func_c(struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_Module * mod, int32_t func_index) {
  if (typeck_expr_var_name_equal_func(arena, callee_expr_ref, mod, func_index)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_find_func_return_type_in_module_by_name_c(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  return typeck_find_func_return_type_in_module_by_name(mod, caller_arena, name, name_len, from_dep_index, ctx, func_index_out);
}
int32_t pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, int32_t want_arity, int32_t call_expr_ref, int32_t is_method, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  {
    int32_t ret = 0;
    int32_t fi = -1;
    int32_t _im = is_method;
    if ((_im < 0)) {
      (void)((_im = 0));
    }
    if ((((mod ==0) || (name ==0)) || (name_len <=0))) {
      return 0;
    }
    if (((call_expr_ref > 0) && (caller_arena !=0))) {
      (void)((ret = typeck_find_func_return_type_in_module_by_name_overload(mod, caller_arena, name, name_len, call_expr_ref, from_dep_index, ctx, func_index_out)));
      if ((((ret > 0) && (from_dep_index >=0)) && (func_index_out !=0))) {
        (void)((fi = (func_index_out)[0]));
        (((fi >=0) && (pipeline_visibility_allow_func(mod, fi, 1) ==0)) ? ({   return 0;
 }) : 0);
      }
      return ret;
    }
    (void)((fi = -1));
    (void)(({   int32_t j = 0;
  int32_t first_match = -1;
  int32_t n = pipeline_module_num_funcs(mod);
  while ((j < n)) {
    if ((pipeline_module_func_name_equal_at(mod, j, name, name_len) !=0)) {
      if ((first_match < 0)) {
        (void)((first_match = j));
      }
      ((want_arity >=0) ? ({   ((pipeline_module_func_num_params_at(mod, j) ==want_arity) ? ({   (void)((fi = j));
  break;
 }) : 0);
 }) : 0);
    }
    (void)((j = (j + 1)));
  }
  ((fi < 0) ? ({   (void)((fi = first_match));
 }) : 0);
 }));
    if ((fi < 0)) {
      return 0;
    }
    if (((from_dep_index >=0) && (pipeline_visibility_allow_func(mod, fi, 1) ==0))) {
      return 0;
    }
    if ((func_index_out !=0)) {
      (void)(((func_index_out)[0] = fi));
    }
    (void)((ret = pipeline_module_func_return_type_at(mod, fi)));
    if ((from_dep_index < 0)) {
      return ret;
    }
    return typeck_get_dep_return_type_in_caller_arena_i32_i32_ASTArena_ptr_PipelineDepCtx_ptr_reti32(from_dep_index, ret, caller_arena, ctx);
  }
  return 0;
}
int32_t pipeline_typeck_find_func_return_type_in_module_by_name_strict_minimal(struct ast_Module * mod, struct ast_ASTArena * caller_arena, uint8_t * name, int32_t name_len, int32_t from_dep_index, int32_t want_arity, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  return pipeline_typeck_find_func_return_type_in_module_by_name_call_strict_minimal(mod, caller_arena, name, name_len, from_dep_index, want_arity, 0, 0, ctx, func_index_out);
}
int32_t pipeline_typeck_find_func_return_type_in_module_c(struct ast_Module * mod, struct ast_ASTArena * mod_arena, struct ast_ASTArena * caller_arena, struct ast_ASTArena * callee_arena, int32_t callee_expr_ref, int32_t from_dep_index, struct ast_PipelineDepCtx * ctx, int32_t * func_index_out) {
  return typeck_find_func_return_type_in_module(mod, mod_arena, caller_arena, callee_arena, callee_expr_ref, from_dep_index, ctx, func_index_out);
}
int32_t pipeline_typeck_block_const_init_is_const_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx) {
  return typeck_block_const_init_is_const(arena, block_ref, const_idx);
}
void pipeline_typeck_const_init_not_constant_c(int32_t line, int32_t col) {
  (void)(typeck_const_init_not_constant(line, col));
}
void pipeline_typeck_fold_expr_c(struct ast_ASTArena * arena, int32_t expr_ref) {
  (void)(typeck_fold_expr(arena, expr_ref));
}
void pipeline_typeck_fold_block_const_init_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t const_idx) {
  (void)(typeck_fold_block_const_init(arena, block_ref, const_idx));
}
void pipeline_typeck_fold_expr_in_block_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t expr_ref) {
  (void)(typeck_fold_expr_in_block(arena, block_ref, expr_ref));
}
int32_t pipeline_expr_is_c_static_const_init(struct ast_ASTArena * arena, int32_t expr_ref) {
  return typeck_expr_is_c_static_const_init(arena, expr_ref);
}
extern void pipeline_typeck_active_module_set_c(struct ast_Module * m);
int32_t pipeline_typeck_check_expr_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if ((((arena ==0) || (expr_ref <=0)) || (expr_ref > ((arena)->num_exprs)))) {
    return 0;
  }
  (void)(pipeline_typeck_active_module_set_c(module));
  return typeck_check_expr_assign(module, arena, expr_ref, return_type_ref, ctx);
}
int32_t pipeline_typeck_diag_append_lit_c(uint8_t * out, int32_t pos, int32_t cap, uint8_t * lit, int32_t lit_len) {
  return typeck_diag_append_lit(out, pos, cap, lit, lit_len);
}
int32_t pipeline_typeck_diag_append_u32_dec_c(uint8_t * out, int32_t pos, int32_t cap, int32_t v) {
  return typeck_diag_append_u32_dec(out, pos, cap, v);
}
int32_t pipeline_typeck_diag_fmt_type_at_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cur, int32_t cap) {
  return typeck_diag_fmt_type_at(arena, ref, out, cur, cap);
}
int32_t pipeline_typeck_diag_fmt_type_into_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out, int32_t cap) {
  return typeck_diag_fmt_type_into(arena, ref, out, cap);
}
int32_t pipeline_typeck_diag_fmt_type_or_question_c(struct ast_ASTArena * arena, int32_t ref, uint8_t * out) {
  return typeck_diag_fmt_type_or_question(arena, ref, out);
}
int32_t pipeline_typeck_check_slice_region_assign_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t expect_ref, int32_t src_ref) {
  return typeck_check_slice_region_assign(arena, site_expr_ref, expect_ref, src_ref);
}
int32_t pipeline_typeck_check_struct_stack_escape_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_struct_stack_escape_assign(module, arena, site_expr_ref, left_ref, right_ref, ctx);
}
int32_t pipeline_typeck_check_scope_borrow_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, int32_t right_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_scope_borrow_assign(module, arena, site_expr_ref, left_ref, right_ref, ctx);
}
int32_t pipeline_typeck_check_scope_borrow_return_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t op_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_scope_borrow_return(module, arena, site_expr_ref, op_ref, return_type_ref, ctx);
}
int32_t pipeline_typeck_check_allocator_region_assign_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t left_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_allocator_region_assign(module, arena, site_expr_ref, left_ref, ctx);
}
int32_t pipeline_typeck_check_allocator_region_return_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref) {
  return typeck_check_allocator_region_return(arena, site_expr_ref, return_type_ref);
}
int32_t pipeline_typeck_check_return_slice_region_c(struct ast_ASTArena * arena, int32_t ret_site_ref, int32_t op_ref, int32_t func_return_ref) {
  return typeck_check_return_slice_region(arena, ret_site_ref, op_ref, func_return_ref);
}
int32_t pipeline_typeck_check_call_slice_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_call_slice_region(module, arena, call_expr_ref, ctx);
}
int32_t pipeline_typeck_coerce_init_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_float_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_float_lit_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_enum_field_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_enum_field_to_decl(module, arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_named_call_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_named_call_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_array_vector_lit_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  /* C ABI unchanged: no module param. Pass 0 → active_module fallback. */
  return typeck_coerce_init_array_vector_lit_to_decl(0, arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_vector_binop_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_vector_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_int_binop_to_decl_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind, int32_t init_kind) {
  return typeck_coerce_init_int_binop_to_decl(arena, init_ref, decl_ty_ref, decl_kind, init_kind);
}
int32_t pipeline_typeck_coerce_init_struct_lit_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  return typeck_coerce_init_struct_lit_to_decl(module, arena, init_ref, decl_ty_ref);
}
int32_t pipeline_typeck_coerce_init_slice_from_array_c(struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref, int32_t decl_kind) {
  return typeck_coerce_init_slice_from_array(arena, init_ref, decl_ty_ref, decl_kind);
}
int32_t pipeline_typeck_coerce_init_expr_to_decl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t init_ref, int32_t decl_ty_ref) {
  return typeck_coerce_init_expr_to_decl(module, arena, init_ref, decl_ty_ref);
}
int32_t pipeline_typeck_float_widen_ok_c(int32_t dest_kind, int32_t src_kind) {
  if (typeck_float_widen_ok(dest_kind, src_kind)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_integer_widen_ok_c(int32_t dest_kind, int32_t src_kind) {
  if (typeck_integer_widen_ok(dest_kind, src_kind)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_integer_widen_ok_refs_c(struct ast_ASTArena * arena, int32_t dest_ref, int32_t src_ref) {
  if (typeck_integer_widen_ok_refs(arena, dest_ref, src_ref)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_type_refs_equal_named_c(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  if (typeck_type_refs_equal_named(arena, a, b)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_resolve_type_alias_ref_c(struct ast_ASTArena * arena, int32_t type_ref) {
  return typeck_resolve_type_alias_ref(arena, type_ref);
}
int32_t pipeline_typeck_type_refs_equal_impl_c(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  if (typeck_type_refs_equal_impl(arena, a, b)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_type_refs_equal_c(struct ast_ASTArena * arena, int32_t a, int32_t b) {
  if (typeck_type_refs_equal(arena, a, b)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_type_refs_equal_same_kind_c(struct ast_ASTArena * arena, int32_t a, int32_t b, int32_t kind_ord) {
  if (typeck_type_refs_equal_same_kind(arena, a, b, kind_ord)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_type_ref_is_bool_impl_c(struct ast_ASTArena * arena, int32_t type_ref) {
  if (typeck_type_ref_is_bool_impl(arena, type_ref)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_type_ref_is_bool_c(struct ast_ASTArena * arena, int32_t type_ref) {
  if (typeck_type_ref_is_bool(arena, type_ref)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_expr_type_ref_impl_c(struct ast_ASTArena * arena, int32_t expr_ref) {
  return typeck_expr_type_ref(arena, expr_ref);
}
int32_t pipeline_typeck_expr_type_ref_c(struct ast_ASTArena * arena, int32_t expr_ref) {
  return typeck_expr_type_ref(arena, expr_ref);
}
int32_t pipeline_typeck_return_operand_matches_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  if (typeck_return_operand_matches(0, arena, op_ref, expect_ref)) {
    return 1;
  }
  return 0;
}
void pipeline_typeck_ret_coerce_integral_to_expect_i32_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  (void)(typeck_ret_coerce_integral_to_expect_i32(arena, op_ref, expect_ref));
}
void pipeline_typeck_ret_coerce_integral_widen_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t expect_ref) {
  (void)(typeck_ret_coerce_integral_widen(arena, op_ref, expect_ref));
}
int32_t pipeline_typeck_check_expr_int_lit_c(struct ast_ASTArena * arena, int32_t expr_ref) {
  return typeck_check_expr_int_lit(arena, expr_ref, 0);
}
int32_t pipeline_typeck_expr_is_any_assign_kind_c(int32_t kind_ord) {
  if (typeck_expr_is_any_assign_kind(kind_ord)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_block_impl_bind_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref) {
  int32_t saved = 0;
  if ((ctx ==0)) {
    return 0;
  }
  (void)((saved = ((ctx)->current_block_ref)));
  (void)((((ctx)->current_block_ref) = block_ref));
  return saved;
}
void pipeline_typeck_block_impl_restore_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref) {
  if ((ctx ==0)) {
    return;
  }
  (void)((((ctx)->current_block_ref) = saved_block_ref));
}
void pipeline_typeck_block_impl_touch_ctx_block_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref) {
  if ((ctx ==0)) {
    return;
  }
  (void)((((ctx)->current_block_ref) = block_ref));
}
int32_t pipeline_typeck_loop_depth_push_c(struct ast_PipelineDepCtx * ctx) {
  int32_t saved = 0;
  if ((ctx ==0)) {
    return 0;
  }
  (void)((saved = ((ctx)->typeck_loop_depth)));
  (void)((((ctx)->typeck_loop_depth) = (saved + 1)));
  return saved;
}
void pipeline_typeck_loop_depth_pop_c(struct ast_PipelineDepCtx * ctx, int32_t saved_loop_depth) {
  if ((ctx ==0)) {
    return;
  }
  (void)((((ctx)->typeck_loop_depth) = saved_loop_depth));
}
int32_t pipeline_dep_ctx_typeck_unsafe_depth_at(struct ast_PipelineDepCtx * ctx) {
  if ((ctx ==0)) {
  }
  return g_typeck_unsafe_depth;
}
int32_t pipeline_typeck_unsafe_depth_push_c(struct ast_PipelineDepCtx * ctx) {
  int32_t saved = 0;
  if ((ctx ==0)) {
  }
  (void)((saved = g_typeck_unsafe_depth));
  (void)((g_typeck_unsafe_depth = (saved + 1)));
  return saved;
}
void pipeline_typeck_unsafe_depth_pop_c(struct ast_PipelineDepCtx * ctx, int32_t saved_unsafe_depth) {
  if ((ctx ==0)) {
  }
  (void)((g_typeck_unsafe_depth = saved_unsafe_depth));
}
void pipeline_typeck_loop_depth_set_c(struct ast_PipelineDepCtx * ctx, int32_t depth) {
  if ((ctx ==0)) {
    return;
  }
  (void)((((ctx)->typeck_loop_depth) = depth));
}
int32_t pipeline_typeck_check_block_impl_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_block_impl(module, arena, block_ref, return_type_ref, ctx);
}
int32_t pipeline_typeck_check_block_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  if (ast_ref_is_null(block_ref)) {
    return 0;
  }
  if ((((block_ref <=0) || (arena ==0)) || (block_ref > ((arena)->num_blocks)))) {
    return 0;
  }
  return typeck_check_block(module, arena, block_ref, return_type_ref, ctx);
}
int32_t pipeline_typeck_check_block_as_loop_body_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t body_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_block_as_loop_body(module, arena, body_ref, return_type_ref, ctx);
}
void pipeline_typeck_set_active_ctx_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx) {
  (void)(pipeline_typeck_active_module_set_c(module));
  (void)((g_typeck_active_ctx = ctx));
}
struct ast_PipelineDepCtx * pipeline_typeck_active_ctx_c(void) {
  return g_typeck_active_ctx;
}
void pipeline_typeck_linear_reset_c(void) {
  (void)((g_typeck_linear_moved_n = 0));
}
int32_t typeck_linear_name_already_moved(uint8_t * name, int32_t name_len) {
  int32_t i = 0;
  int32_t j = 0;
  int32_t base = 0;
  if (((name ==0) || (name_len <=0))) {
    return 0;
  }
  while ((i < g_typeck_linear_moved_n)) {
    if (((g_typeck_linear_moved_lens)[i] ==name_len)) {
      (void)((base = (i * 128)));
      (void)((j = 0));
      while ((j < name_len)) {
        (((g_typeck_linear_moved_names)[(base + j)] !=(name)[j]) ? ({   (void)((j = (name_len + 1)));
 }) : ({   (void)((j = (j + 1)));
 }));
      }
      ((j ==name_len) ? ({   return 1;
 }) : 0);
    }
    (void)((i = (i + 1)));
  }
  return 0;
}
int32_t pipeline_typeck_linear_use_var_c(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len) {
  {
    int32_t line = 0;
    int32_t col = 0;
    int32_t i = 0;
    int32_t base = 0;
    int32_t ord_linear = 12;
    if (((((arena ==0) || (name_len <=0)) || (name_len > 127)) || (name ==0))) {
      return 0;
    }
    if (((type_ref <=0) || (pipeline_type_kind_ord_at(arena, type_ref) !=ord_linear))) {
      return 0;
    }
    if ((typeck_linear_name_already_moved(name, name_len) !=0)) {
      (void)((line = 0));
      (void)((col = 0));
      if (((expr_ref > 0) && (expr_ref <=((arena)->num_exprs)))) {
        (void)((line = pipeline_expr_line_at(arena, expr_ref)));
        (void)((col = pipeline_expr_col_at(arena, expr_ref)));
      }
      (void)(lsp_diag_report_typeck(line, col, ((uint8_t *)(((uint8_t *)"\x6c\x69\x6e\x65\x61\x72\x20\x76\x61\x6c\x75\x65\x20\x75\x73\x65\x64\x20\x61\x66\x74\x65\x72\x20\x6d\x6f\x76\x65")))));
      return -1;
    }
    if ((g_typeck_linear_moved_n < 128)) {
      (void)((base = (g_typeck_linear_moved_n * 128)));
      (void)((i = 0));
      while ((i < name_len)) {
        (void)(((g_typeck_linear_moved_names)[(base + i)] = (name)[i]));
        (void)((i = (i + 1)));
      }
      (void)(((g_typeck_linear_moved_lens)[g_typeck_linear_moved_n] = name_len));
      (void)((g_typeck_linear_moved_n = (g_typeck_linear_moved_n + 1)));
    }
    return 0;
  }
}
int32_t pipeline_typeck_linear_accepts_init_c(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref) {
  {
    int32_t ord_linear = 12;
    if ((((arena ==0) || (decl_ref <=0)) || (init_ref <=0))) {
      return 0;
    }
    if ((pipeline_type_kind_ord_at(arena, decl_ref) !=ord_linear)) {
      return 0;
    }
    if (typeck_type_refs_equal(arena, decl_ref, init_ref)) {
      return 1;
    }
    if (typeck_type_refs_equal(arena, pipeline_type_elem_ref_at(arena, decl_ref), init_ref)) {
      return 1;
    }
    return 0;
  }
}
int32_t pipeline_typeck_reject_addr_of_linear_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx) {
  {
    int32_t vnlen = 0;
    int32_t block_ref = 0;
    int32_t vd_tr = 0;
    int32_t func_ix = 0;
    int32_t pr = 0;
    int32_t line = 0;
    int32_t col = 0;
    uint8_t vbuf[128] = {};
    int32_t ord_linear = 12;
    int32_t ord_var = 3;
    int32_t i = 0;
    if ((((((arena ==0) || (module ==0)) || (ctx ==0)) || (op_ref <=0)) || (op_ref > ((arena)->num_exprs)))) {
      return 0;
    }
    if ((pipeline_expr_kind_ord_at(arena, op_ref) !=ord_var)) {
      return 0;
    }
    (void)((vnlen = pipeline_expr_var_name_len(arena, op_ref)));
    if (((vnlen <=0) || (vnlen > 127))) {
      return 0;
    }
    (void)(pipeline_expr_var_name_into(arena, op_ref, &((vbuf)[0])));
    (void)((block_ref = ((ctx)->current_block_ref)));
    if (((block_ref > 0) && (block_ref <=((arena)->num_blocks)))) {
      (void)((vd_tr = pipeline_block_resolve_var_type_ref(arena, block_ref, &((vbuf)[0]), vnlen)));
      (((vd_tr > 0) && (pipeline_type_kind_ord_at(arena, vd_tr) ==ord_linear)) ? ({   (void)((line = 0));
  (void)((col = 0));
  if (((addr_expr_ref > 0) && (addr_expr_ref <=((arena)->num_exprs)))) {
    (void)((line = pipeline_expr_line_at(arena, addr_expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, addr_expr_ref)));
  }
  (void)(driver_diagnostic_typeck_linear_addr_of(line, col));
  return -1;
 }) : 0);
    }
    (void)((func_ix = ((ctx)->current_func_index)));
    if (((func_ix >=0) && (func_ix < ((module)->num_funcs)))) {
      (void)((pr = pipeline_module_func_param_type_ref_for_name(module, func_ix, &((vbuf)[0]), vnlen)));
      (((pr > 0) && (pipeline_type_kind_ord_at(arena, pr) ==ord_linear)) ? ({   (void)((line = 0));
  (void)((col = 0));
  if (((addr_expr_ref > 0) && (addr_expr_ref <=((arena)->num_exprs)))) {
    (void)((line = pipeline_expr_line_at(arena, addr_expr_ref)));
    (void)((col = pipeline_expr_col_at(arena, addr_expr_ref)));
  }
  (void)(driver_diagnostic_typeck_linear_addr_of(line, col));
  return -1;
 }) : 0);
    }
    return 0;
  }
}
int32_t pipeline_typeck_func_body_tail_expr_ref_for_implicit_rule_c(struct ast_ASTArena * arena, int32_t body_ref) {
  return typeck_func_body_tail_expr_ref_for_implicit_rule(arena, body_ref);
}
int32_t pipeline_typeck_func_body_has_implicit_return_tail_c(struct ast_ASTArena * arena, int32_t body_ref) {
  if (typeck_func_body_has_implicit_return_tail(arena, body_ref)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_check_expr_method_call_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) {
  return typeck_check_expr_method_call(module, arena, expr_ref, return_type_ref, ctx);
}
void pipeline_typeck_expr_apply_call_resolve_c(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix) {
  (void)(pipeline_expr_apply_call_resolve(arena, call_expr_ref, dep_ix, func_ix));
}
int32_t pipeline_typeck_import_segment_at_c(struct ast_Module * module, int32_t imp_ix, int32_t want_seg, int32_t * ostr, int32_t * olen) {
  if (typeck_import_segment_at(module, imp_ix, want_seg, ostr, olen)) {
    return 1;
  }
  return 0;
}
int32_t pipeline_typeck_resolve_dep_index_for_import_c(struct ast_Module * module, struct ast_PipelineDepCtx * ctx, int32_t imp_ix) {
  return typeck_resolve_dep_index_for_import(module, ctx, imp_ix);
}
int32_t pipeline_typeck_resolve_whole_import_call_ret_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t callee_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t * dep_index_out, int32_t * func_index_out) {
  return typeck_resolve_whole_import_qualified_call_return_type(module, arena, callee_expr_ref, ctx, dep_index_out, func_index_out);
}

/* wave322 layer-1 Cap residual (seeds/typeck_cap_residual.from_x.c) */
/* ============================================================================
 * wave317 typeck M4 layer-1 Cap residual (BSS slots + CTFE).
 * Authority: pin typeck_gen L13097-14390 (pre-wave317). allow_legacy lives in
 * patch_typeck_gen_lang007 / product header — not duplicated here.
 * Append-only companion for tip typeck.x -E re-pin; G.7 residual TU.
 * PLATFORM: SHARED freestanding typeck Cap residual.
 * ========================================================================== */


/* ============================================================================
 * 8.3.1/8.3.2 host-cc leave: typeck scratch / call-resolve / overload /
 * layout-metrics slots — historical body in pipeline_typeck_slots.c (same-TU
 * #include into pipeline_x). Live BSS accessors only; dead binop_arith_infer /
 * try_packed C twins dropped (typeck.x owns widen/layout business).
 * PLATFORM: SHARED — lives in typeck_x.o (not pipeline_x host-cc mega-TU).
 * ============================================================================ */

/** typeck.x: named-type scratch (avoid local u8[64] under self-typecheck). */
uint8_t *typeck_named_scratch64(void) {
  static uint8_t s[128];
  return s;
}

/** typeck.x: multi-slot 128B scratch (wave577 Cap: 64->128). */
static uint8_t g_typeck_scratch64[16][128];

uint8_t *typeck_scratch64_slot(int32_t slot) {
  if (slot < 0 || slot >= 16)
    return g_typeck_scratch64[0];
  return g_typeck_scratch64[slot];
}

/** typeck.x: CALL resolve func/dep index BSS (no stack &cfi under selfhost). */
static int32_t g_typeck_call_resolve_func_idx;
static int32_t g_typeck_call_resolve_dep_idx;
/**
 * PLATFORM: SHARED — expected return type for overload pick (let/assign/return).
 * Zero-arg overloads score by this when args do not disambiguate. 0 = no hint.
 */
static int32_t g_typeck_overload_expected_ret;

int32_t *typeck_call_resolve_func_idx_slot(void) {
  return &g_typeck_call_resolve_func_idx;
}

int32_t *typeck_call_resolve_dep_idx_slot(void) {
  return &g_typeck_call_resolve_dep_idx;
}

int32_t *typeck_overload_expected_ret_slot(void) {
  return &g_typeck_overload_expected_ret;
}

int32_t typeck_call_resolve_dep_idx_peek(void) {
  return g_typeck_call_resolve_dep_idx;
}

int32_t typeck_call_resolve_func_idx_peek(void) {
  return g_typeck_call_resolve_func_idx;
}

int32_t typeck_overload_expected_ret_peek(void) {
  return g_typeck_overload_expected_ret;
}

/** typeck.x: struct_layout_metrics out_sz/out_al BSS (no stack &z/&al). */
static int32_t g_typeck_layout_metrics_sz;
static int32_t g_typeck_layout_metrics_al;

int32_t *typeck_layout_metrics_sz_slot(void) {
  return &g_typeck_layout_metrics_sz;
}

int32_t *typeck_layout_metrics_al_slot(void) {
  return &g_typeck_layout_metrics_al;
}

/** Recursive metrics: 8 depth groups avoid align/size single-slot tearing. */
static int32_t g_typeck_layout_metrics_depth_scratch[8][2];

int32_t *typeck_layout_metrics_sz_slot_depth(int32_t depth) {
  int32_t s = depth;
  if (s < 0)
    s = 0;
  return &g_typeck_layout_metrics_depth_scratch[s % 8][0];
}

int32_t *typeck_layout_metrics_al_slot_depth(int32_t depth) {
  int32_t s = depth;
  if (s < 0)
    s = 0;
  return &g_typeck_layout_metrics_depth_scratch[s % 8][1];
}

/* ==========================================================================
 * wave238 hand-sync: typeck CTFE pure leave (LANG-006 producer).
 * Authority = typeck_x.o (this file). Cap residual pipeline_typeck_ctfe.c thins
 * here. PLATFORM: SHARED freestanding typeck.
 * ========================================================================== */
extern struct ast_Expr *glue_arena_expr_at_ref(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_block_const_init_ref(struct ast_ASTArena *a, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_name_len(struct ast_ASTArena *a, int32_t br, int32_t ci);
extern void pipeline_block_const_name_copy64(struct ast_ASTArena *a, int32_t br, int32_t ci, uint8_t *dst);
extern int32_t pipeline_block_const_type_ref(struct ast_ASTArena *a, int32_t br, int32_t ci);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_struct_lit_init_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t j);
extern int32_t pipeline_type_kind_ord_at(struct ast_ASTArena *a, int32_t type_ref);
extern int32_t pipeline_expr_if_cond_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_if_then_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_if_else_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_block_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_match_matched_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_match_arm_is_wildcard(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_lit_val(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_guard_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_field_access_is_enum_variant(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_enum_variant_tag_at(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_try_mark_enum_field_access(struct ast_Module *m, struct ast_ASTArena *a, int32_t expr_ref);
extern struct ast_Module *pipeline_typeck_active_module_c(void);
extern int32_t pipeline_module_top_level_name_is_const(struct ast_Module *module, uint8_t *vname,
                                                       int32_t vlen);
extern struct ast_PipelineDepCtx *pipeline_typeck_active_ctx_c(void);
extern int32_t typeck_field_import_const_is_const(struct ast_Module *module, struct ast_ASTArena *a,
                                                 int32_t expr_ref, struct ast_PipelineDepCtx *ctx);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena *a, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_call_callee_ref_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_call_resolved_func_index_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_kind_ord_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_var_name_len(struct ast_ASTArena *a, int32_t expr_ref);
extern void pipeline_expr_var_name_into(struct ast_ASTArena *a, int32_t expr_ref, uint8_t *out);
extern int32_t pipeline_expr_const_folded_valid_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_const_folded_val_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t pipeline_expr_int_val_at(struct ast_ASTArena *a, int32_t expr_ref);
extern int32_t glue_fold_func_returns_param01_scalar_binop_c(struct ast_ASTArena *a, struct ast_Module *mod, int32_t fi, int32_t *out_ko);
extern int32_t glue_try_eval_pure_param0_scalar_func_c(struct ast_ASTArena *a, struct ast_Module *mod, int32_t fi, int32_t arg, int32_t *out);
extern int32_t glue_fold_func_returns_param0_index_const_c(struct ast_ASTArena *a, struct ast_Module *mod, int32_t fi, int32_t *out_lane);
extern int32_t glue_fold_func_returns_param01_vector_binop_ctfe_c(struct ast_ASTArena *a, struct ast_Module *mod, int32_t fi, int32_t *out_ko);
extern int32_t glue_try_array_lit_lane_const_i32_c(struct ast_ASTArena *a, int32_t arr_ref, int32_t lane, int32_t *out);
/* lsp_diag_report_typeck already declared above (uint8_t *msg). */
extern int32_t ast_ast_block_num_consts(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_lets(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_loops(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_for_loops(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_regions(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_num_expr_stmts(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena *a, int32_t br);
extern int32_t ast_pipeline_block_expr_stmt_ref(struct ast_ASTArena *a, int32_t br, int32_t i);

static int typeck_is_const_expr_ref_impl(struct ast_ASTArena *a, int32_t expr_ref, const char *const_names[], int n_const_names) {
  struct ast_Expr *e;
  int i, j, ne;
  enum ast_ExprKind kd;

  e = glue_arena_expr_at_ref(a, expr_ref);
  if (!e)
    return 0;
  kd = e->kind;
  if (kd == ast_ExprKind_EXPR_LIT || kd == ast_ExprKind_EXPR_FLOAT_LIT || kd == ast_ExprKind_EXPR_BOOL_LIT)
    return 1;
  if (kd == ast_ExprKind_EXPR_VAR) {
    for (i = 0; i < n_const_names; i++) {
      if (!const_names[i])
        continue;
      if (e->var_name_len > 0 && strcmp(const_names[i], e->var_name) == 0)
        return 1;
    }
    /**
     * PLATFORM: SHARED — a module top-level const VAR is a const-expr when
     * this check is the block-const whitelist (const_names != NULL).
     *
     * Why: `const s: []i32 = A` / `const n: i32 = A[1]` / `const x: [][]i32 = [A]`
     *      in a function, with `const A` at module scope, parse as EXPR_VAR.
     *      The whitelist only scanned prior *block* const names, so typeck
     *      emitted T001 "const init must be constant expression". Mutable
     *      module lets stay rejected (`pipeline_module_top_level_name_is_const`
     *      is const-only). Active module is set at typeck entry (same BSS
     *      as the enum FIELD pre-mark).
     *
     *      C-static-init / pure-lit fold pass const_names=NULL and must
     *      still reject VAR (want_decl_init: VAR trees stay init_globals).
     *
     * G.7: extend this whitelist. Do not add a second checker. Bare import
     *      const stays rejected (typeck_reject_bare_import_const); the
     *      product spelling is binding.CONST — FIELD arm below.
     */
    if (const_names != NULL && e->var_name_len > 0) {
      struct ast_Module *mod = pipeline_typeck_active_module_c();
      if (mod && pipeline_module_top_level_name_is_const(mod, (uint8_t *)e->var_name,
                                                        e->var_name_len) != 0)
        return 1;
    }
    return 0;
  }
  if (kd >= ast_ExprKind_EXPR_ADD && kd <= ast_ExprKind_EXPR_LOGOR)
    return typeck_is_const_expr_ref_impl(a, e->binop_left_ref, const_names, n_const_names) &&
           typeck_is_const_expr_ref_impl(a, e->binop_right_ref, const_names, n_const_names);
  if (kd == ast_ExprKind_EXPR_NEG || kd == ast_ExprKind_EXPR_BITNOT || kd == ast_ExprKind_EXPR_LOGNOT)
    return typeck_is_const_expr_ref_impl(a, e->unary_operand_ref, const_names, n_const_names);
  if (kd == ast_ExprKind_EXPR_ARRAY_LIT) {
    ne = e->array_lit_num_elems;
    for (i = 0; i < ne; i++) {
      if (!typeck_is_const_expr_ref_impl(a, pipeline_expr_array_lit_elem_ref(a, expr_ref, i), const_names, n_const_names))
        return 0;
    }
    return 1;
  }
  /**
   * C5-struct-lit: a struct literal is a const expression iff every field
   * initializer is a const expression. The struct value itself cannot fit
   * in the i32 const_folded_val field, so callers that demand a scalar
   * result (e.g. `const N: i32 = <struct lit>`) still fail at typeck; this
   * branch only enables nested folding of inner field inits such as
   * `S { x: A+1, y: B*2 }` where A,B are prior block consts. Mirrors the
   * ARRAY_LIT recursion above. PLATFORM: SHARED.
   */
  if (kd == ast_ExprKind_EXPR_STRUCT_LIT) {
    ne = e->struct_lit_num_fields;
    for (i = 0; i < ne; i++) {
      int32_t init_ref = pipeline_expr_struct_lit_init_ref(a, expr_ref, i);
      if (init_ref <= 0)
        return 0;
      if (!typeck_is_const_expr_ref_impl(a, init_ref, const_names, n_const_names))
        return 0;
    }
    return 1;
  }
  /**
   * C5-enum-variant: a TypeName.Variant FIELD_ACCESS is a const expression
   * iff the marker confirms it resolves to an enum variant tag.
   *
   * Why: This whitelist (pipeline_typeck_block_const_init_is_const_c) runs at
   *      seed typeck_gen L6839, BEFORE the typeck-time marker
   *      pipeline_typeck_try_mark_enum_field_access fires inside
   *      typeck_check_expr at L6850. So at whitelist time a fresh
   *      FIELD_ACCESS still has field_access_is_enum_variant=0, and the
   *      whitelist cannot tell Color.Red (enum variant — const-eligible)
   *      from obj.field (runtime struct access — NOT const-eligible).
   *
   *      We resolve the chicken-and-egg by pre-marking here using the
   *      global g_typeck_active_module, which is set at module typeck
   *      entry (runtime_pipeline_abi pipeline_typeck_active_module_set_c;
   *      historical ast_pool.c/pipeline_glue.c L* left wave309) before any
   *      block-level typeck runs. The marker is idempotent — early-
   *      returns if already marked — so re-marking at L6850 is a no-op.
   *
   * Invariant: For non-enum FIELD_ACCESS (obj.field / array[x].field at
   *            runtime) pipeline_expr_try_mark_enum_field_access leaves
   *            field_access_is_enum_variant=0 (tag lookup returns -1), so
   *            this branch correctly rejects them — they are NOT const.
   *            Only TypeName.Variant shapes pass.
   *
   * Asm/Perf: Enables `const X: Color = Color.Red;` to typecheck, paving
   *           the way for the fold handler in glue_typeck_fold_expr_ref to
   *           stamp X.const_folded_val=tag. Downstream `match X { ... }`
   *           then folds to a single mov w0,#imm (no runtime enum load).
   *
   * PLATFORM: SHARED — g_typeck_active_module is populated identically on
   *           macOS arm64 and Ubuntu x86_64 at module typeck entry.
   */
  if (kd == ast_ExprKind_EXPR_FIELD_ACCESS) {
    pipeline_expr_try_mark_enum_field_access(pipeline_typeck_active_module_c(), a, expr_ref);
    if (pipeline_expr_field_access_is_enum_variant(a, expr_ref) != 0)
      return 1;
    /**
     * PLATFORM: SHARED — import-module const FIELD `dep.A` is a const-expr
     * when this check is the block-const whitelist (const_names != NULL).
     *
     * Why: `const s: []i32 = dep.A` / `const n: i32 = dep.A[1]` /
     *      `const x: [][]i32 = [dep.A]` parse as FIELD, not VAR. Bare
     *      import const is rejected (must be binding.CONST). The FIELD
     *      arm only accepted enum variants, so typeck emitted T001.
     *
     *      Reuse typeck_field_import_const_is_const (Path A/B matchers
     *      from typeck_field_import_binding; const-only, no stamp).
     *      Active ctx is the same cell set at typeck entry. C-static-init
     *      / fold pass const_names=NULL and still reject non-enum FIELD.
     *
     * G.7: extend this whitelist. Do not add a second checker. Do not
     *      accept dep functions or runtime obj.field.
     */
    if (const_names != NULL) {
      struct ast_Module *mod = pipeline_typeck_active_module_c();
      struct ast_PipelineDepCtx *ctx = pipeline_typeck_active_ctx_c();
      if (mod && ctx && typeck_field_import_const_is_const(mod, a, expr_ref, ctx) != 0)
        return 1;
    }
    return 0;
  }
  /**
   * C5-ternary-if: a ternary `cond ? then : else` or if-expression
   * `if cond { then } else { else }` is a const expression iff cond, then,
   * and else are all const expressions. EXPR_IF and EXPR_TERNARY share the
   * same field layout (if_cond_ref / if_then_ref / if_else_ref, see
   * runtime_pipeline_abi.x::asm_wpo_collect_edges_from_expr;
   * historical ast_pool.c L14836-14844 left wave309), so one
   * branch covers both kinds.
   *
   * Why: Lets `const Y: i32 = (X == 2) ? 100 : 200;` and
   *      `const Y: i32 = if (X == 2) { 100 } else { 200 };` pass the
   *      const-init whitelist (pipeline_typeck_block_const_init_is_const_c
   *      at seed typeck_gen L6839). The fold handler in
   *      glue_typeck_fold_expr_ref then picks the live branch and stamps
   *      the result. Mirrors EXPR_MATCH treatment (subject + arms recursion
   *      but no top-level whitelist case; here we whitelist because both
   *      branches are statically reachable from a const POV — only one is
   *      selected at CTFE, but both must be const-eligible to type-check
   *      `const Y = cond ? a : b;` regardless of which branch fires).
   *
   * Invariant: Recurses into all three children (cond, then, else). If any
   *            child is non-const (e.g. runtime VAR or function call) the
   *            whole expression is non-const. This is stricter than the
   *            fold handler, which only needs the *selected* branch to
   *            fold — the whitelist must accept both because the typeck
   *            pass runs before CTFE picks a branch.
   *
   * Asm/Perf: Enables `const Y = cond ? a : b;` to typecheck, paving the
   *           way for the fold handler to emit `mov w0, #const` (4 bytes)
   *           instead of runtime cmp/branch + 2× value materialization
   *           (~24 bytes). Also unlocks parent binop folds.
   *
   * PLATFORM: SHARED — EXPR_IF / EXPR_TERNARY field layout is identical on
   *           macOS arm64 and Ubuntu x86_64 (runtime_pipeline_abi.x
   *           asm_wpo_collect_edges_from_expr; historical ast_pool.c
   *           L14836 left wave309).
   */
  if (kd == ast_ExprKind_EXPR_TERNARY || kd == ast_ExprKind_EXPR_IF) {
    int32_t cond_ref = pipeline_expr_if_cond_ref_at(a, expr_ref);
    int32_t then_ref = pipeline_expr_if_then_ref_at(a, expr_ref);
    int32_t else_ref = pipeline_expr_if_else_ref_at(a, expr_ref);
    if (cond_ref <= 0 || then_ref <= 0 || else_ref <= 0)
      return 0;
    return typeck_is_const_expr_ref_impl(a, cond_ref, const_names, n_const_names) &&
           typeck_is_const_expr_ref_impl(a, then_ref, const_names, n_const_names) &&
           typeck_is_const_expr_ref_impl(a, else_ref, const_names, n_const_names);
  }
  /**
   * C5-block: a single-stmt block `({ expr })` is a const expression iff the
   * block has no side-effecting statements (no const/let decls, no loops, no
   * if-statements, no regions) and exactly one expression statement whose
   * expr is const. This is required for EXPR_IF support because the
   * if-expression parser wraps each branch as EXPR_BLOCK
   * (parser_asm_if_expr_slice.inc::parser_asm_wrap_block_ref_as_expr_c);
   * recursing into then_ref/else_ref reaches EXPR_BLOCK children.
   *
   * Why: Lets `const Y: i32 = if (X==2) { 100 } else { 200 };` pass the
   *      const-init whitelist by treating the wrapped `{ 100 }` block as the
   *      inner literal's value. Multi-stmt / side-effecting blocks stay
   *      non-const (correctly: those have runtime ordering concerns that
   *      CTFE cannot model at this stage).
   *
   * Invariant: Strict side-effect scan (num_consts/lets/loops/for_loops/
   *            if_stmts/regions all zero, num_expr_stmts == 1). The fold
   *            handler mirrors this check and stamps e->const_folded_val
   *            from ast_ast_block_final_expr_ref's folded value.
   *
   * Asm/Perf: Unlocks EXPR_IF CTFE end-to-end. Combined with EXPR_TERNARY +
   *           EXPR_IF handlers, enables `const Y = cond ? a : b;` and
   *           `const Y = if (c) { a } else { b };` to emit `mov w0, #const`
   *           (4 bytes / 1 instr) instead of runtime cmp/branch + materialize.
   *
   * PLATFORM: SHARED — EXPR_BLOCK layout and Block accessors are identical
   *           on macOS arm64 and Ubuntu x86_64. Mirrored in seed
   *           pipeline_glue_strict_minimal.from_x.c (Darwin filtered pipeline
   *           localizes this strong version, so seed weak version is what
   *           Darwin calls).
   */
  if (kd == ast_ExprKind_EXPR_BLOCK) {
    int32_t block_ref = pipeline_expr_block_ref_at(a, expr_ref);
    int32_t final_expr_ref;
    int32_t n_es;
    if (block_ref <= 0)
      return 0;
    if (ast_ast_block_num_consts(a, block_ref) > 0)
      return 0;
    if (ast_ast_block_num_lets(a, block_ref) > 0)
      return 0;
    if (ast_ast_block_num_loops(a, block_ref) > 0)
      return 0;
    if (ast_ast_block_num_for_loops(a, block_ref) > 0)
      return 0;
    if (ast_ast_block_num_if_stmts(a, block_ref) > 0)
      return 0;
    if (ast_ast_block_num_regions(a, block_ref) > 0)
      return 0;
    /* Parser normalizes `{ expr }` (final_expr_ref set, num_expr_stmts=0)
     * into `expr_stmts[0] = expr; final_expr_ref = 0`. So accept either
     * form: prefer final_expr_ref when set, else fall back to the single
     * expr_stmt. Reject multi-stmt blocks (num_expr_stmts > 1). */
    n_es = ast_ast_block_num_expr_stmts(a, block_ref);
    final_expr_ref = ast_ast_block_final_expr_ref(a, block_ref);
    if (final_expr_ref <= 0) {
      if (n_es != 1)
        return 0;
      final_expr_ref = ast_pipeline_block_expr_stmt_ref(a, block_ref, 0);
    } else if (n_es != 0) {
      return 0;
    }
    if (final_expr_ref <= 0)
      return 0;
    return typeck_is_const_expr_ref_impl(a, final_expr_ref, const_names, n_const_names);
  }
  /**
   * PLATFORM: SHARED — EXPR_AS is a const expression iff the operand is.
   *
   * Why: `const n: i32 = 5 as i32` and `const s: []i32 = [10, 32] as []i32`
   *      parse as EXPR_AS wrapping a const operand. The whitelist runs
   *      before fold (wave460 already folds EXPR_AS) and had no case, so
   *      typeck emitted T001 "const init must be constant expression".
   *      Recurse into as_operand only — the target is a type_ref, not a
   *      value. Identity ascriptions (ARRAY / SLICE) stay unstamped in
   *      fold; emit peel remains authority for fat / fixed-array materialize.
   *
   * G.7: extend this whitelist (same helper as ARRAY_LIT / unary). Do not
   *      add a second const-expr checker.
   */
  if (kd == ast_ExprKind_EXPR_AS) {
    int32_t op = e->as_operand_ref;
    if (op <= 0)
      return 0;
    return typeck_is_const_expr_ref_impl(a, op, const_names, n_const_names);
  }
  /**
   * PLATFORM: SHARED — EXPR_INDEX is a const expression iff base and index are.
   *
   * Why: `const s: []i32 = a[1]` / `const r: [2]i32 = a[0]` / `const n: i32 = b[1]`
   *      parse as EXPR_INDEX (kind 47). The whitelist had no case, so typeck
   *      emitted T001 even when `a`/`b` were prior consts and the index was a
   *      lit or prior const. Recurse both children — a let-bound base stays
   *      rejected (VAR not in const_names), which is correct.
   *
   *      dest-SLICE / dest-[N]T / scalar consume stay on emit (const aggregate
   *      helpers already wrap INDEX). Fold does not stamp INDEX into i32
   *      (element may be ARRAY/SLICE).
   *
   * G.7: extend this whitelist (same helper as EXPR_AS / ARRAY_LIT). Do not
   *      add a second const-expr checker. Do not touch dest-SLICE emit.
   */
  if (kd == ast_ExprKind_EXPR_INDEX) {
    int32_t base = e->index_base_ref;
    int32_t idx = e->index_index_ref;
    if (base <= 0 || idx <= 0)
      return 0;
    return typeck_is_const_expr_ref_impl(a, base, const_names, n_const_names) &&
           typeck_is_const_expr_ref_impl(a, idx, const_names, n_const_names);
  }
  return 0;
}

/** PLATFORM: SHARED — expr is legal as a C static initializer (compile-time const, no free vars).
 * Authority: glue_is_const_expr_ref with empty const-name set (pure lit trees + ops; VAR fails).
 * Used by codegen want_decl_init for mutable top-level lets: lit sentinels (e.g. -1) stay at
 * decl-site for library .o without main; VAR-dependent inits (e.g. a+2) stay init_globals-only. */
int32_t typeck_expr_is_c_static_const_init(struct ast_ASTArena *arena, int32_t expr_ref) {
  if (!arena || expr_ref <= 0)
    return 0;
  return typeck_is_const_expr_ref_impl(arena, expr_ref, NULL, 0) ? 1 : 0;
}

/**
 * PLATFORM: SHARED — same whitelist as typeck_block_const_init_is_const, with
 * const_names != NULL so module top-level const VAR / import-const FIELD pass.
 *
 * Why: typeck_x_ast never walked Module.num_top_level_lets. Function-scope
 *      const used typeck_block_const_init_is_const (block names + module
 *      const lookup). Module `const x: i32 = foo()` / `const x: i32 = [1,2]`
 *      therefore skipped T001 (probe run=42 / BLD001 UNDEF).
 *
 *      C-static-init stays on typeck_expr_is_c_static_const_init (NULL names).
 *      This wrapper is not a second checker — it calls the same impl.
 *
 * G.7: complete the existing whitelist. Do not fold as i32. Do not accept
 *      bare import const VAR. Mutable module lets are not const-expr.
 */
int32_t typeck_expr_is_const_with_module_consts(struct ast_ASTArena *arena, int32_t expr_ref) {
  static const char *empty_names[1] = { NULL };
  if (!arena || expr_ref <= 0)
    return 0;
  return typeck_is_const_expr_ref_impl(arena, expr_ref, empty_names, 0) ? 1 : 0;
}

/** block 内第 const_idx 条 const 的 init 是否为常量表达式；是返回 1，否返回 0。 */
int32_t typeck_block_const_init_is_const(struct ast_ASTArena *arena, int32_t block_ref, int32_t const_idx) {
  const char *names[64];
  char name_bufs[64][128];
  int n = 0;
  int i;
  int32_t init_ref;

  if (!arena || const_idx < 0)
    return 0;
  for (i = 0; i < const_idx && n < 64; i++) {
    int32_t nlen = pipeline_block_const_name_len(arena, block_ref, i);
    if (nlen <= 0 || nlen >= 64)
      continue;
    pipeline_block_const_name_copy64(arena, block_ref, i, (uint8_t *)name_bufs[n]);
    name_bufs[n][nlen] = '\0';
    names[n] = name_bufs[n];
    n++;
  }
  init_ref = pipeline_block_const_init_ref(arena, block_ref, const_idx);
  if (init_ref <= 0)
    return 1;
  return typeck_is_const_expr_ref_impl(arena, init_ref, names, n) ? 1 : 0;
}

/** const 初值非常量表达式时报错（与 typeck.c TYPECK_ERR_AT 措辞一致）。 */
void typeck_const_init_not_constant(int32_t line, int32_t col) {
  static uint8_t msg[] = "const init must be constant expression";
  lsp_diag_report_typeck(line, col, msg);
}

/**
 * PLATFORM: SHARED — typeck CTFE producer (LANG-006 / residual IR authority).
 *
 * Writes `const_folded_valid` / `const_folded_val` on arena exprs. Emit only
 * *consumes* these fields (mov imm); do not grow emit-side optim folds.
 *
 * Restores the producer lost when mega typeck.c was removed (G-02a): product
 * typeck.x only validated `is_const_expr` and never folded. Pure lit trees and
 * block-const chains (const A=3; const B=A+2) are folded bottom-up.
 *
 * names/values: prior const bindings in scope (may be NULL/0 for pure lits).
 *
 * PLATFORM: SHARED — product Expr.const_folded_val is still an i32 field in
 * ast.x / seed layouts (ast.h documents i64 intent). Truncating wide i64 lits
 * (e.g. 9223372036854775807 -> -1) then folding `0 - lit - 1` -> 0 is the
 * fmt_i64_min / P0-4 silent wrong-code class. Rule:
 *   - Only set const_folded_valid when the value fits in int32_t.
 *   - Otherwise leave valid=0 so C emit uses full int_val on LIT / full binop tree.
 */
static int typeck_ctfe_fits_i32(int64_t v) {
  return v >= (int64_t)INT32_MIN && v <= (int64_t)INT32_MAX;
}

static void typeck_fold_expr_ref_impl(struct ast_ASTArena *a, int32_t expr_ref,
                                     const char *const_names[], const int64_t *const_values,
                                     int n_const_names) {
  struct ast_Expr *e;
  enum ast_ExprKind kd;
  int32_t left_ref;
  int32_t right_ref;
  int32_t op_ref;
  int i;
  int64_t l;
  int64_t r;
  int64_t o;
  int64_t out;

  e = glue_arena_expr_at_ref(a, expr_ref);
  if (!e)
    return;
  e->const_folded_valid = 0;
  kd = e->kind;

  if (kd == ast_ExprKind_EXPR_LIT || kd == ast_ExprKind_EXPR_BOOL_LIT) {
    /* P0-4: do not CTFE-truncate wide i64 literals into the i32 fold field.
     * But u32 literals (0..UINT32_MAX) must be foldable: their 32-bit bit
     * pattern fits in int32_t and two's complement arithmetic is correct
     * for both signed and unsigned 32-bit types.
     * Invariant: const_folded_val is int32_t; storing (int32_t)(uint32_t)v
     * preserves the 32-bit bit pattern. Codegen reinterprets by type.
     * For 64-bit types (ordinal >= 4), keep int32_t range to avoid
     * sign-extension truncation on emit. */
    {
      int64_t v = e->int_val;
      int fits = typeck_ctfe_fits_i32(v);
      if (!fits) {
        int32_t tr = e->resolved_type_ref;
        if (tr > 0) {
          int32_t tk = pipeline_type_kind_ord_at(a, tr);
          /* TYPE_I32=0, TYPE_BOOL=1, TYPE_U8=2, TYPE_U32=3: 32-bit types */
          if (tk >= 0 && tk <= 3 && v >= 0 && v <= (int64_t)UINT32_MAX)
            fits = 1;
        }
      }
      if (fits) {
        e->const_folded_val = (int32_t)(uint32_t)v;
        e->const_folded_valid = 1;
      }
    }
    return;
  }
  /*
   * wave287 Cap residual: do NOT CTFE-fold EXPR_FLOAT_LIT into const_folded_val.
   * Root cause: const_folded_val is i32; folding (int32_t)float_val truncated fractions
   * (1.5->1) and emit consumed fold via format_int -> soft residual wrong C (`double a = 1`
   * instead of 1.5; (1.5*2.0) as i32 -> 2). Product C emit uses pipeline_codegen_emit_float_lit_c
   * on float_val when const_folded_valid=0. PLATFORM: SHARED — single authority here.
   */
  if (kd == ast_ExprKind_EXPR_FLOAT_LIT) {
    e->const_folded_valid = 0;
    return;
  }
  if (kd == ast_ExprKind_EXPR_VAR) {
    if (!const_names || !const_values || n_const_names <= 0 || e->var_name_len <= 0)
      return;
    for (i = 0; i < n_const_names; i++) {
      if (!const_names[i])
        continue;
      if (strcmp(const_names[i], (const char *)e->var_name) == 0) {
        if (typeck_ctfe_fits_i32(const_values[i])) {
          e->const_folded_val = (int32_t)const_values[i];
          e->const_folded_valid = 1;
        }
        return;
      }
    }
    return;
  }

  if (kd >= ast_ExprKind_EXPR_ADD && kd <= ast_ExprKind_EXPR_LOGOR) {
    left_ref = e->binop_left_ref;
    right_ref = e->binop_right_ref;
    typeck_fold_expr_ref_impl(a, left_ref, const_names, const_values, n_const_names);
    typeck_fold_expr_ref_impl(a, right_ref, const_names, const_values, n_const_names);
    {
      struct ast_Expr *el = glue_arena_expr_at_ref(a, left_ref);
      struct ast_Expr *er = glue_arena_expr_at_ref(a, right_ref);
      if (!el || !er || !el->const_folded_valid || !er->const_folded_valid)
        return;
      l = (int64_t)el->const_folded_val;
      r = (int64_t)er->const_folded_val;
    }
    switch (kd) {
    case ast_ExprKind_EXPR_ADD:
      out = l + r;
      break;
    case ast_ExprKind_EXPR_SUB:
      out = l - r;
      break;
    case ast_ExprKind_EXPR_MUL:
      out = l * r;
      break;
    case ast_ExprKind_EXPR_DIV:
      if (r == 0)
        return;
      out = l / r;
      break;
    case ast_ExprKind_EXPR_MOD:
      if (r == 0)
        return;
      out = l % r;
      break;
    case ast_ExprKind_EXPR_SHL:
      out = (int64_t)((uint64_t)l << ((uint64_t)r & 63u));
      break;
    case ast_ExprKind_EXPR_SHR:
      out = (int64_t)((uint64_t)l >> ((uint64_t)r & 63u));
      break;
    case ast_ExprKind_EXPR_BITAND:
      out = l & r;
      break;
    case ast_ExprKind_EXPR_BITOR:
      out = l | r;
      break;
    case ast_ExprKind_EXPR_BITXOR:
      out = l ^ r;
      break;
    case ast_ExprKind_EXPR_EQ:
      out = (l == r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_NE:
      out = (l != r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_LT:
      out = (l < r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_LE:
      out = (l <= r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_GT:
      out = (l > r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_GE:
      out = (l >= r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_LOGAND:
      out = (l && r) ? 1 : 0;
      break;
    case ast_ExprKind_EXPR_LOGOR:
      out = (l || r) ? 1 : 0;
      break;
    default:
      return;
    }
    if (!typeck_ctfe_fits_i32(out))
      return;
    e->const_folded_val = (int32_t)out;
    e->const_folded_valid = 1;
    return;
  }

  if (kd == ast_ExprKind_EXPR_NEG || kd == ast_ExprKind_EXPR_BITNOT || kd == ast_ExprKind_EXPR_LOGNOT) {
    op_ref = e->unary_operand_ref;
    typeck_fold_expr_ref_impl(a, op_ref, const_names, const_values, n_const_names);
    {
      struct ast_Expr *eo = glue_arena_expr_at_ref(a, op_ref);
      if (!eo || !eo->const_folded_valid)
        return;
      o = (int64_t)eo->const_folded_val;
    }
    if (kd == ast_ExprKind_EXPR_NEG)
      out = -o;
    else if (kd == ast_ExprKind_EXPR_BITNOT)
      out = ~o;
    else
      out = !o ? 1 : 0;
    if (!typeck_ctfe_fits_i32(out))
      return;
    e->const_folded_val = (int32_t)out;
    e->const_folded_valid = 1;
    return;
  }

  if (kd == ast_ExprKind_EXPR_ARRAY_LIT) {
    int ne = e->array_lit_num_elems;
    int32_t tr;
    int32_t tk;
    for (i = 0; i < ne; i++)
      typeck_fold_expr_ref_impl(a, pipeline_expr_array_lit_elem_ref(a, expr_ref, i), const_names,
                                const_values, n_const_names);
    /**
     * C5-array-len: only when the lit was coerced to a scalar int type
     * (`const N: i32 = [1,2,3,4]`). Real array materialization keeps
     * const_folded_valid=0 so emit does not mov imm.
     */
    tr = e->resolved_type_ref;
    if (tr > 0) {
      tk = pipeline_type_kind_ord_at(a, tr);
      /* TYPE_I32..TYPE_ISIZE = 0..7 in product enum. */
      if (tk >= 0 && tk <= 7) {
        e->const_folded_val = (int32_t)ne;
        e->const_folded_valid = 1;
      }
    }
    return;
  }

  /**
   * PLATFORM: SHARED — C5-struct-lit field CTFE (扩全).
   * Why: Struct literals frequently carry field initializers that are pure
   *      const expressions (`S { x: A+1, y: A*3 }` where A is a prior const).
   *      Without recursion the inner binop trees stay unfolded, forcing emit
   *      to emit runtime `mov;add;mov;mul;mov` sequences instead of immediates.
   * Invariant: The struct value itself cannot fit in the i32 const_folded_val
   *            field, so this branch NEVER stamps e->const_folded_valid=1 on
   *            the STRUCT_LIT node. It only descends into each field init so
   *            that the inner Expr trees (binop/unary/lit/var/nested-call)
   *            get folded in place; emit then reads those inner stamps. This
   *            mirrors ARRAY_LIT's element recursion but skips the scalar
   *            coercion stamp (struct cannot be coerced to scalar int).
   * Asm/Perf: For `S { x: A+1, y: A*3 }` with A=2 folded prior, emit drops
   *           `mov edi,2; add edi,1; mov [..x],edi; mov edi,2; imul edi,3;`
   *           in favor of `mov DWORD[..x],3; mov DWORD[..y],6;` (constant
   *           materialization only), shrinking the hot path and removing
   *           two ALU dependencies.
   */
  if (kd == ast_ExprKind_EXPR_STRUCT_LIT) {
    int nf = e->struct_lit_num_fields;
    for (i = 0; i < nf; i++) {
      int32_t init_ref = pipeline_expr_struct_lit_init_ref(a, expr_ref, i);
      if (init_ref > 0)
        typeck_fold_expr_ref_impl(a, init_ref, const_names, const_values, n_const_names);
    }
    return;
  }

  if (kd == ast_ExprKind_EXPR_INDEX) {
    /*
     * PLATFORM: SHARED — CTFE recurse for EXPR_INDEX (const whitelist twin).
     * Fold base + index so nested lits/binops still CTFE. Never stamp the
     * INDEX node: the element may be ARRAY/SLICE (dest-SLICE `const s = a[1]`)
     * and cannot fit i32 const_folded_val. Scalar `const n = b[1]` emit loads
     * from the const array slot. G.7: same producer as ARRAY_LIT / STRUCT_LIT.
     */
    int32_t base = e->index_base_ref;
    int32_t idx = e->index_index_ref;
    if (base > 0)
      typeck_fold_expr_ref_impl(a, base, const_names, const_values, n_const_names);
    if (idx > 0)
      typeck_fold_expr_ref_impl(a, idx, const_names, const_values, n_const_names);
    return;
  }

  if (kd == ast_ExprKind_EXPR_AS) {
    /*
     * PLATFORM: SHARED — CTFE producer for EXPR_AS (wave460 Cap residual pure).
     * Always fold the operand so nested trees still CTFE. Stamp this AS node
     * only when the *target* is a scalar that host-C/asm can materialize as a
     * bare i32 immediate.
     *
     * Root (soft leave-off after wave459 compound-literal host-C emit):
     *   `let m: MultiField = 7 as MultiField` -> typeck set const_folded_valid=1
     *   from the lit operand -> emit_expr consumed fold as format_int -> host C
     *   `struct MultiField m = 7` -> BLD001. Variable operand skipped the fold
     *   stamp and correctly took wave459 `((TYPE){ (op) })`.
     *
     * Mirror STRUCT_LIT: aggregate values cannot fit in i32 const_folded_val;
     * never stamp valid=1 for TYPE_NAMED user structs / array / slice / vector /
     * linear so codegen EXPR_AS (compound literal / cast) remains authority.
     * G.7: single authority = this producer; emit only *consumes* the flags.
     */
    typeck_fold_expr_ref_impl(a, e->as_operand_ref, const_names, const_values, n_const_names);
    {
      struct ast_Expr *eo = glue_arena_expr_at_ref(a, e->as_operand_ref);
      int32_t tgt;
      int32_t tk;
      if (!eo || !eo->const_folded_valid)
        return;
      tgt = e->as_target_type_ref;
      if (tgt <= 0)
        tgt = e->resolved_type_ref;
      if (tgt > 0) {
        /* Kind check only (no alias peel): TYPE_NAMED covers user structs and
         * named aliases; skipping stamp for aliases is safe — emit still does
         * C cast/compound via EXPR_AS. Avoid calling resolve here (defined later
         * in this TU; fold stays self-contained). */
        tk = pipeline_type_kind_ord_at(a, tgt);
        if (tk == (int32_t)ast_TypeKind_TYPE_NAMED
            || tk == (int32_t)ast_TypeKind_TYPE_ARRAY
            || tk == (int32_t)ast_TypeKind_TYPE_SLICE
            || tk == (int32_t)ast_TypeKind_TYPE_LINEAR
            || tk == (int32_t)ast_TypeKind_TYPE_VECTOR)
          return; /* keep const_folded_valid=0; emit via EXPR_AS host-C path */
      }
      e->const_folded_val = eo->const_folded_val; /* int32 product field */
      e->const_folded_valid = 1;
    }
    return;
  }

  /**
   * PLATFORM: SHARED — C5-enum-variant CTFE (TypeName.Variant folds to tag).
   *
   * Why: Enum variants are statically assigned a discriminator tag at parse
   *      time via pipeline_module_enum_variant_tag_for_names
   *      (runtime_pipeline_abi.x; historical ast_pool.c L4204 left wave309).
   *      The same source feeds both:
   *        - MatchArmEntry.variant_index (pipeline_expr_append_match_arm in
   *          runtime_pipeline_abi; historical ast_pool.c L5200 left wave309)
   *          — drives arm comparison in EXPR_MATCH fold.
   *        - Expr.enum_variant_tag (set by pipeline_expr_try_mark_enum_field_access
   *          in runtime_pipeline_abi; historical ast_pool.c L4312 left wave309)
   *          — drives emit's `mov w0,#tag` fast path.
   *      Folding Color.Red into const_folded_val=tag enables two key wins:
   *        (1) `const X: Color = Color.Red;` stamps X with the tag so
   *            downstream `match X { Color.Red => ... }` folds to a single
   *            immediate via the EXPR_MATCH handler (L14131-14137).
   *        (2) Standalone `return Color.Red;` emits `mov w0,#tag` directly
   *            instead of going through runtime enum-load glue.
   *
   * Invariant: const_folded_val holds the enum_variant_tag (i32 >= 0). The
   *            marker is idempotent — re-running on an already-marked expr
   *            early-returns without rewriting the tag. For non-enum
   *            FIELD_ACCESS (obj.field) the marker leaves
   *            field_access_is_enum_variant=0, so this branch correctly
   *            skips stamping (const_folded_valid stays 0, set at L13664).
   *            The marker needs the active module — g_typeck_active_module
   *            is set at module typeck entry
   *            (runtime_pipeline_abi pipeline_typeck_active_module_set_c;
   *            historical ast_pool.c/glue L* left wave309)
   *            and remains live throughout block-level typeck.
   *
   * Asm/Perf: Replaces runtime tag-load sequence (`adrp xN, .enum_table;
   *           ldr w0, [xN, #off]`) with `mov w0, #imm` (4 bytes vs ~12).
   *           Eliminates a memory load and a relocation in the .text section.
   *           For match-on-const-enum the entire jump table collapses to one
   *           immediate materialization.
   */
  if (kd == ast_ExprKind_EXPR_FIELD_ACCESS) {
    int32_t tag;
    /* Pre-mark in case the whitelist path was bypassed (e.g. fold invoked
     * from pipeline_typeck_fold_expr_c on a standalone FIELD_ACCESS expr
     * without prior whitelist pre-mark). No-op if already marked. */
    pipeline_expr_try_mark_enum_field_access(pipeline_typeck_active_module_c(), a, expr_ref);
    if (pipeline_expr_field_access_is_enum_variant(a, expr_ref) == 0)
      return; /* Non-enum FIELD_ACCESS: runtime struct access, not const. */
    tag = pipeline_expr_enum_variant_tag_at(a, expr_ref);
    if (tag < 0)
      return; /* Defensive: marker set is_enum_variant=1 but tag readback failed. */
    e->const_folded_val = tag;
    e->const_folded_valid = 1;
    return;
  }

  /**
   * PLATFORM: SHARED — WPO-S2 / LANG-006 call-site CTFE (pre-emit authority).
   * (1) Pure local `f(c0,c1)` when f body is `return p0 binop p1`.
   * (2) Pure 1-param scalar: `id(c)` / `g(c)` where body is p0 / p0 op lit /
   *     lit op p0 / unary(p0). Enables nested `f(g(3),4)` via arg fold first.
   * (3) Pure `laneK(vec_binop([const…],[const…]))` when outer is `return p0[K]`
   *     and inner is vector `return p0 binop p1` with array-lit const lanes.
   * Emit only *consumes* const_folded_* (mov imm / C int); try_inline_* remain
   * safety nets. XLANG_WPO_MONO / NO_FOLD skip stamp so call sites stay live.
   */
  if (kd == ast_ExprKind_EXPR_CALL) {
    int32_t nargs;
    int32_t ai;
    int32_t callee_ref;
    int32_t clen;
    int32_t fi;
    int32_t binop_ko;
    int32_t arg0;
    int32_t arg1;
    int32_t av0;
    int32_t av1;
    int32_t folded;
    uint8_t cname[128];
    struct ast_Module *mod;
    struct ast_Expr *ea0;
    struct ast_Expr *ea1;

    nargs = pipeline_expr_call_num_args_at(a, expr_ref);
    for (ai = 0; ai < nargs; ai++) {
      int32_t ar = pipeline_expr_call_arg_ref(a, expr_ref, ai);
      if (ar > 0)
        typeck_fold_expr_ref_impl(a, ar, const_names, const_values, n_const_names);
    }
    /**
     * WPO-S2 harness: XLANG_WPO_MONO needs a live CALL for mono thunks;
     * XLANG_WPO_NO_FOLD needs a real call. Skip stamping CALL const_folded so
     * parent binops do not erase the site (scale(c0,c1)-K would become 0).
     */
    {
      /* PLATFORM: SHARED — tip/product face is uint8_t *; cast for gcc -Werror=incompatible-pointer-types (Ubuntu). */
      const char *wpo_mono = (const char *)link_abi_getenv((uint8_t *)"XLANG_WPO_MONO");
      const char *wpo_nofold = (const char *)link_abi_getenv((uint8_t *)"XLANG_WPO_NO_FOLD");
      if ((wpo_mono && wpo_mono[0]) || (wpo_nofold && wpo_nofold[0]))
        return;
    }
    mod = pipeline_typeck_active_module_c();
    if (!mod)
      return;
    callee_ref = pipeline_expr_call_callee_ref_at(a, expr_ref);
    if (callee_ref <= 0 || pipeline_expr_kind_ord_at(a, callee_ref) != 3)
      return;
    clen = pipeline_expr_var_name_len(a, callee_ref);
    if (clen <= 0 || clen > 127)
      return;
    pipeline_expr_var_name_into(a, callee_ref, cname);
    /* PLATFORM: SHARED — prefer typeck call_resolved_func_index for overloads.
     * Name-only lookup returns the first same-name func (e.g. pick(i32) before
     * pick(i64)) and wrongly CTFE-folds the i64 call site -> types/overload exit 2. */
    fi = pipeline_expr_call_resolved_func_index_at(a, expr_ref);
    if (fi < 0)
      fi = glue_module_func_index_by_name_c((uint8_t *)mod, cname, clen);
    if (fi < 0)
      return;

    /* (1) scalar f(c0,c1) -> const */
    if (nargs == 2) {
      if (glue_fold_func_returns_param01_scalar_binop_c(a, mod, fi, &binop_ko) == 0)
        return;
      arg0 = pipeline_expr_call_arg_ref(a, expr_ref, 0);
      arg1 = pipeline_expr_call_arg_ref(a, expr_ref, 1);
      if (arg0 <= 0 || arg1 <= 0)
        return;
      ea0 = glue_arena_expr_at_ref(a, arg0);
      ea1 = glue_arena_expr_at_ref(a, arg1);
      if (!ea0 || !ea1)
        return;
      if (ea0->const_folded_valid)
        av0 = ea0->const_folded_val;
      else if (ea0->kind == ast_ExprKind_EXPR_LIT || ea0->kind == ast_ExprKind_EXPR_BOOL_LIT)
        av0 = (int32_t)ea0->int_val;
      else
        return;
      if (ea1->const_folded_valid)
        av1 = ea1->const_folded_val;
      else if (ea1->kind == ast_ExprKind_EXPR_LIT || ea1->kind == ast_ExprKind_EXPR_BOOL_LIT)
        av1 = (int32_t)ea1->int_val;
      else
        return;
      /* Same domain as glue_const_scalar_binop_eval_i32 (ko 4..8). */
      switch (binop_ko) {
      case 4:
        folded = (int32_t)((int64_t)av0 + (int64_t)av1);
        break;
      case 5:
        folded = (int32_t)((int64_t)av0 - (int64_t)av1);
        break;
      case 6:
        folded = (int32_t)((int64_t)av0 * (int64_t)av1);
        break;
      case 7:
        if (av1 == 0)
          return;
        folded = (int32_t)((int64_t)av0 / (int64_t)av1);
        break;
      case 8:
        if (av1 == 0)
          return;
        folded = (int32_t)((int64_t)av0 % (int64_t)av1);
        break;
      default:
        return;
      }
      e->const_folded_val = folded;
      e->const_folded_valid = 1;
      return;
    }

    /* (2)/(3) 1-arg: pure scalar unary, else laneK(vec_binop(...)) */
    if (nargs == 1) {
      int32_t lane;
      int32_t inner_call_ref;
      int32_t inner_callee_ref;
      int32_t ilen;
      int32_t inner_fi;
      uint8_t iname[128];

      arg0 = pipeline_expr_call_arg_ref(a, expr_ref, 0);
      if (arg0 <= 0)
        return;
      /* (2) pure 1-param scalar (nested g(3) leaf). Prefer before vector lane. */
      {
        int32_t arg_const_ok = 0;
        if (pipeline_expr_const_folded_valid_at(a, arg0) != 0) {
          av0 = pipeline_expr_const_folded_val_at(a, arg0);
          arg_const_ok = 1;
        } else {
          int32_t ako = pipeline_expr_kind_ord_at(a, arg0);
          if (ako == 0 || ako == 2) {
            av0 = (int32_t)pipeline_expr_int_val_at(a, arg0);
            arg_const_ok = 1;
          }
        }
        if (arg_const_ok != 0 &&
            glue_try_eval_pure_param0_scalar_func_c(a, mod, fi, av0, &folded) != 0) {
          e->const_folded_val = folded;
          e->const_folded_valid = 1;
          return;
        }
      }

      /* (3) laneK(vec_binop([const…],[const…])) -> scalar const */
      if (glue_fold_func_returns_param0_index_const_c(a, mod, fi, &lane) == 0)
        return;
      inner_call_ref = arg0;
      if (pipeline_expr_kind_ord_at(a, inner_call_ref) != (int32_t)ast_ExprKind_EXPR_CALL)
        return;
      if (pipeline_expr_call_num_args_at(a, inner_call_ref) != 2)
        return;
      /* Nested CALL already folded above; still ok if not stamped (vector return). */
      inner_callee_ref = pipeline_expr_call_callee_ref_at(a, inner_call_ref);
      if (inner_callee_ref <= 0 || pipeline_expr_kind_ord_at(a, inner_callee_ref) != 3)
        return;
      ilen = pipeline_expr_var_name_len(a, inner_callee_ref);
      if (ilen <= 0 || ilen > 127)
        return;
      pipeline_expr_var_name_into(a, inner_callee_ref, iname);
      /* PLATFORM: SHARED — same overload rule as outer CALL fold above. */
      inner_fi = pipeline_expr_call_resolved_func_index_at(a, inner_call_ref);
      if (inner_fi < 0)
        inner_fi = glue_module_func_index_by_name_c((uint8_t *)mod, iname, ilen);
      if (inner_fi < 0)
        return;
      if (glue_fold_func_returns_param01_vector_binop_ctfe_c(a, mod, inner_fi, &binop_ko) == 0)
        return;
      arg0 = pipeline_expr_call_arg_ref(a, inner_call_ref, 0);
      arg1 = pipeline_expr_call_arg_ref(a, inner_call_ref, 1);
      if (arg0 <= 0 || arg1 <= 0)
        return;
      if (glue_try_array_lit_lane_const_i32_c(a, arg0, lane, &av0) == 0)
        return;
      if (glue_try_array_lit_lane_const_i32_c(a, arg1, lane, &av1) == 0)
        return;
      if (binop_ko == 51)
        binop_ko = 4;
      switch (binop_ko) {
      case 4:
        folded = (int32_t)((int64_t)av0 + (int64_t)av1);
        break;
      case 5:
        folded = (int32_t)((int64_t)av0 - (int64_t)av1);
        break;
      case 6:
        folded = (int32_t)((int64_t)av0 * (int64_t)av1);
        break;
      case 7:
        if (av1 == 0)
          return;
        folded = (int32_t)((int64_t)av0 / (int64_t)av1);
        break;
      case 8:
        if (av1 == 0)
          return;
        folded = (int32_t)((int64_t)av0 % (int64_t)av1);
        break;
      default:
        return;
      }
      e->const_folded_val = folded;
      e->const_folded_valid = 1;
      return;
    }
  }

  /**
   * PLATFORM: SHARED — EXPR_MATCH CTFE (C5).
   * Why: Pure-const match expressions (`match const_X { lit => const; ...; _ => const }`)
   *      are common in state machines / config tables; folding them at typeck time lets
   *      emit emit a single mov imm32 instead of a runtime cmp/branch dispatch.
   * Invariant: Only stamps const_folded_valid=1 when (1) subject folds to a constant and
   *            (2) the first matching arm (literal or wildcard) result also folds to a
   *            constant. Enum-variant arms compare variant_index. Const guards
   *            (`_ if 0` / `_ if false`) fold then skip (0) or take (nonzero);
   *            non-const guards leave the match unfolded.
   * Asm/Perf: Replaces `mov rbx,subj; cmp;jmp;armN;mov w0,result;done` (~30 bytes)
   *           with `mov w0, #const` (4 bytes); also enables parent binop folds.
   */
  if (kd == ast_ExprKind_EXPR_MATCH) {
    int32_t matched_ref;
    int32_t num_arms;
    int32_t i;
    int32_t cmp_val;
    int32_t arm_result_ref;
    int32_t matched_val;
    int32_t is_wild;
    int32_t guard_ref;
    struct ast_Expr *em;
    struct ast_Expr *er;
    struct ast_Expr *eg;

    matched_ref = pipeline_expr_match_matched_ref_at(a, expr_ref);
    if (matched_ref <= 0)
      return;
    typeck_fold_expr_ref_impl(a, matched_ref, const_names, const_values, n_const_names);
    em = glue_arena_expr_at_ref(a, matched_ref);
    if (!em || !em->const_folded_valid)
      return;
    matched_val = em->const_folded_val;

    num_arms = pipeline_expr_match_num_arms_at(a, expr_ref);
    if (num_arms <= 0 || num_arms > 32)
      return;

    /* First-match wins (mirrors leftover rest emit_match). A guarded
     * `_ if 0` is not an unguarded default — skip when the const guard
     * is 0, take when nonzero, leave unfolded when the guard is not const.
     * PLATFORM: SHARED — complete C5 MATCH CTFE (G.7). */
    for (i = 0; i < num_arms; i++) {
      is_wild = pipeline_expr_match_arm_is_wildcard(a, expr_ref, i);
      if (is_wild == 0) {
        if (pipeline_expr_match_arm_is_enum_variant(a, expr_ref, i) != 0)
          cmp_val = pipeline_expr_match_arm_variant_index(a, expr_ref, i);
        else
          cmp_val = pipeline_expr_match_arm_lit_val(a, expr_ref, i);
        if (cmp_val != matched_val)
          continue;
      }
      guard_ref = pipeline_expr_match_arm_guard_ref(a, expr_ref, i);
      if (guard_ref > 0) {
        typeck_fold_expr_ref_impl(a, guard_ref, const_names, const_values, n_const_names);
        eg = glue_arena_expr_at_ref(a, guard_ref);
        if (!eg || !eg->const_folded_valid)
          return;
        if (eg->const_folded_val == 0)
          continue;
      }
      arm_result_ref = pipeline_expr_match_arm_result_ref(a, expr_ref, i);
      if (arm_result_ref <= 0)
        return;
      typeck_fold_expr_ref_impl(a, arm_result_ref, const_names, const_values, n_const_names);
      er = glue_arena_expr_at_ref(a, arm_result_ref);
      if (er && er->const_folded_valid) {
        e->const_folded_val = er->const_folded_val;
        e->const_folded_valid = 1;
      }
      return;
    }
    return;
  }
  /**
   * C5-ternary-if: fold `cond ? then : else` and `if cond { then } else { else }`
   * to the selected branch's constant when cond folds. EXPR_IF and EXPR_TERNARY
   * share the if_cond_ref / if_then_ref / if_else_ref field layout (see
   * runtime_pipeline_abi.x::asm_wpo_collect_edges_from_expr;
   * historical ast_pool.c L14836-14844 left wave309), so one branch
   * covers both kinds.
   *
   * Why: Pure-const ternaries/if-exprs (`const Y = (X==2) ? 100 : 200;` or
   *      `let Y = if (X==2) { 100 } else { 200 };` with X a prior const) are
   *      common in config / lookup tables. Folding them at typeck time lets
   *      emit emit `mov w0, #const` (4 bytes) instead of runtime cmp/branch +
   *      2× value materialization (~24 bytes). Mirrors EXPR_MATCH handler
   *      (subject fold -> branch select -> result fold -> stamp), generalized
   *      to the 2-branch case.
   *
   * Invariant: Only stamps const_folded_valid=1 when (1) cond folds to a
   *            constant and (2) the selected branch (then if cond != 0,
   *            else if cond == 0) also folds to a constant. If cond does
   *            not fold (runtime value) both branches are still recursed
   *            into so nested pure subtrees can fold, but the ternary/if
   *            node itself stays valid=0 (runtime cmp/branch emit path).
   *            Asm-emit branch (cond==0/!=0) is unchanged.
   *
   * Asm/Perf: Replaces `cmp; b.eq else; mov w0, then; b done; else: mov w0,
   *           else; done:` (~24 bytes / 5 instrs) with `mov w0, #const`
   *           (4 bytes / 1 instr). Also unlocks parent binop folds.
   *
   * PLATFORM: SHARED — EXPR_IF / EXPR_TERNARY field layout and accessors
   *           (pipeline_expr_if_cond_ref_at / _then_ref_at / _else_ref_at)
   *           are identical on macOS arm64 and Ubuntu x86_64.
   */
  if (kd == ast_ExprKind_EXPR_TERNARY || kd == ast_ExprKind_EXPR_IF) {
    int32_t cond_ref = pipeline_expr_if_cond_ref_at(a, expr_ref);
    int32_t then_ref = pipeline_expr_if_then_ref_at(a, expr_ref);
    int32_t else_ref = pipeline_expr_if_else_ref_at(a, expr_ref);
    int32_t sel_ref;
    struct ast_Expr *ec;
    struct ast_Expr *es;

    if (cond_ref <= 0)
      return;
    typeck_fold_expr_ref_impl(a, cond_ref, const_names, const_values, n_const_names);
    ec = glue_arena_expr_at_ref(a, cond_ref);
    if (!ec || !ec->const_folded_valid) {
      /* Cond did not fold (runtime). Still recurse into both branches so
       * nested pure subtrees (e.g. `cond ? A+1 : B*2` where A,B are const)
       * can fold their inner binops, even though the ternary itself stays
       * runtime. Mirror the ARRAY_LIT/STRUCT_LIT treatment. */
      if (then_ref > 0)
        typeck_fold_expr_ref_impl(a, then_ref, const_names, const_values, n_const_names);
      if (else_ref > 0)
        typeck_fold_expr_ref_impl(a, else_ref, const_names, const_values, n_const_names);
      return;
    }
    /* Cond folded: pick the live branch. XLANG ternary/if treats any non-zero
     * int as true (mirrors C semantics; bool is i32 0/1 in the IR). */
    sel_ref = (ec->const_folded_val != 0) ? then_ref : else_ref;
    if (sel_ref <= 0)
      return;
    typeck_fold_expr_ref_impl(a, sel_ref, const_names, const_values, n_const_names);
    es = glue_arena_expr_at_ref(a, sel_ref);
    if (es && es->const_folded_valid) {
      e->const_folded_val = es->const_folded_val;
      e->const_folded_valid = 1;
    }
    return;
  }
  /**
   * C5-block: fold a single-stmt EXPR_BLOCK `({ expr })` by folding the
   * block's final expr_stmt and stamping the EXPR_BLOCK node with its
   * folded value. Mirrors the whitelist side-effect scan: only blocks with
   * no const/let/loop/if-stmt/region decls and exactly one expr_stmt are
   * eligible. This is the second half of EXPR_IF support — the if-expr
   * parser wraps each branch as EXPR_BLOCK, so when EXPR_IF picks a branch
   * it recurses into an EXPR_BLOCK child, which must fold through to the
   * inner literal.
   *
   * Why: Without this, `const Y = if (X==2) { 100 } else { 200 };` would
   *      pass the whitelist (EXPR_BLOCK accepted) but the EXPR_IF fold
   *      would recurse into the EXPR_BLOCK branch and find const_folded_valid=0
   *      (no handler stamped it), so the EXPR_IF wouldn't propagate the
   *      value upward. This handler closes the loop.
   *
   * Invariant: Same strict side-effect scan as whitelist. If the block has
   *            any side-effecting stmts, return without stamping (the
   *            EXPR_BLOCK stays runtime). The final expr is folded
   *            unconditionally so nested pure subtrees still get CTFE.
   *
   * Asm/Perf: Stamps const_folded_val on the EXPR_BLOCK so the parent
   *           EXPR_IF handler can propagate it to the const decl. Final
   *           emit then produces `mov w0, #const` (4 bytes / 1 instr).
   *
   * PLATFORM: SHARED — Mirrors whitelist case in glue_is_const_expr_ref
   *           above. ast_ast_block_final_expr_ref returns Block.final_expr_ref
   *           directly (runtime_pipeline_abi / Block.final_expr_ref;
   *           historical pipeline_glue.c L23405-23411 left wave309).
   */
  if (kd == ast_ExprKind_EXPR_BLOCK) {
    int32_t block_ref = pipeline_expr_block_ref_at(a, expr_ref);
    int32_t final_expr_ref;
    int32_t n_es;
    struct ast_Expr *ef;
    if (block_ref <= 0)
      return;
    if (ast_ast_block_num_consts(a, block_ref) > 0)
      return;
    if (ast_ast_block_num_lets(a, block_ref) > 0)
      return;
    if (ast_ast_block_num_loops(a, block_ref) > 0)
      return;
    if (ast_ast_block_num_for_loops(a, block_ref) > 0)
      return;
    if (ast_ast_block_num_if_stmts(a, block_ref) > 0)
      return;
    if (ast_ast_block_num_regions(a, block_ref) > 0)
      return;
    /* Parser normalizes `{ expr }` (final_expr_ref set, num_expr_stmts=0)
     * into `expr_stmts[0] = expr; final_expr_ref = 0`. Accept either form. */
    n_es = ast_ast_block_num_expr_stmts(a, block_ref);
    final_expr_ref = ast_ast_block_final_expr_ref(a, block_ref);
    if (final_expr_ref <= 0) {
      if (n_es != 1)
        return;
      final_expr_ref = ast_pipeline_block_expr_stmt_ref(a, block_ref, 0);
    } else if (n_es != 0) {
      return;
    }
    if (final_expr_ref <= 0)
      return;
    typeck_fold_expr_ref_impl(a, final_expr_ref, const_names, const_values, n_const_names);
    ef = glue_arena_expr_at_ref(a, final_expr_ref);
    if (ef && ef->const_folded_valid) {
      e->const_folded_val = ef->const_folded_val;
      e->const_folded_valid = 1;
    }
    return;
  }
}

/** Pure-lit / already-folded tree CTFE after typeck (no block const env). */
void typeck_fold_expr(struct ast_ASTArena *arena, int32_t expr_ref) {
  if (!arena || expr_ref <= 0)
    return;
  if (!typeck_is_const_expr_ref_impl(arena, expr_ref, NULL, 0)) {
    /* Still recurse so nested pure subtrees can fold. */
    struct ast_Expr *e = glue_arena_expr_at_ref(arena, expr_ref);
    if (!e)
      return;
    if (e->kind >= ast_ExprKind_EXPR_ADD && e->kind <= ast_ExprKind_EXPR_LOGOR) {
      typeck_fold_expr_ref_impl(arena, e->binop_left_ref, NULL, NULL, 0);
      typeck_fold_expr_ref_impl(arena, e->binop_right_ref, NULL, NULL, 0);
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_NEG || e->kind == ast_ExprKind_EXPR_BITNOT ||
               e->kind == ast_ExprKind_EXPR_LOGNOT) {
      typeck_fold_expr_ref_impl(arena, e->unary_operand_ref, NULL, NULL, 0);
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_LIT || e->kind == ast_ExprKind_EXPR_BOOL_LIT ||
               e->kind == ast_ExprKind_EXPR_FLOAT_LIT) {
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_CALL) {
      /* Call itself is not a pure const-expr tree; still try WPO call-site CTFE. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_MATCH) {
      /* PLATFORM: SHARED — Match is not a pure const-expr (subject may be runtime).
       * Still attempt CTFE: if the subject folds to a constant (e.g. `match 2 { ... }`
       * or `match const_X { ... }` outside a block-const env), the handler inside
       * glue_typeck_fold_expr_ref picks the matching arm and stamps the result. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_STRUCT_LIT) {
      /* PLATFORM: SHARED — Struct lit is not a pure const-expr (struct cannot
       * fit in i32 const_folded_val). Still recurse into each field init so
       * inner binop/unary/lit trees fold; struct node itself stays valid=0.
       * Mirrors EXPR_ARRAY_LIT treatment in pipeline_typeck_fold_expr_c. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_TERNARY || e->kind == ast_ExprKind_EXPR_IF) {
      /* PLATFORM: SHARED — Ternary `cond ? a : b` and if-expression
       * `if cond { a } else { b }` are not pure const-expr trees (cond may
       * be runtime). Still attempt CTFE: if cond folds to a constant
       * (e.g. `let Y = (X==2) ? 100 : 200;` with X a prior const outside a
       * block-const env), the handler inside glue_typeck_fold_expr_ref
       * picks the live branch and stamps the result. Mirrors EXPR_MATCH
       * treatment above. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_INDEX) {
      /* PLATFORM: SHARED — INDEX of a runtime base is not a const-expr.
       * Still recurse so a const index / nested lit tree can fold. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    } else if (e->kind == ast_ExprKind_EXPR_BLOCK) {
      /* PLATFORM: SHARED — Block expression `({ stmt; expr })` is not a pure
       * const-expr tree when stmt has side effects. Still attempt CTFE on
       * the final expr so single-stmt blocks (e.g. if-expression branches
       * `{ 100 }` produced by parser_asm_wrap_block_ref_as_expr_c) fold
       * when the final expr folds. Mirrors EXPR_MATCH / EXPR_TERNARY /
       * EXPR_IF treatment: attempt fold with NULL const env; the handler
       * inside glue_typeck_fold_expr_ref will skip if side-effect scan
       * fails. */
      typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
    }
    return;
  }
  typeck_fold_expr_ref_impl(arena, expr_ref, NULL, NULL, 0);
}

/**
 * Build prior-const name/value env for block consts [0, const_idx), then fold
 * the const_idx init (or fold expr_ref when const_idx < 0 using all consts).
 */
static void typeck_block_const_env_build_impl(struct ast_ASTArena *arena, int32_t block_ref, int max_const,
                                             const char *names[64], char name_bufs[64][128],
                                             int64_t values[64], int *out_n) {
  int n = 0;
  int i;
  *out_n = 0;
  if (!arena || max_const <= 0)
    return;
  for (i = 0; i < max_const && n < 64; i++) {
    int32_t nlen = pipeline_block_const_name_len(arena, block_ref, i);
    int32_t init_ref = pipeline_block_const_init_ref(arena, block_ref, i);
    if (nlen <= 0 || nlen >= 64)
      continue;
    pipeline_block_const_name_copy64(arena, block_ref, i, (uint8_t *)name_bufs[n]);
    name_bufs[n][nlen] = '\0';
    names[n] = name_bufs[n];
    values[n] = 0;
    if (init_ref > 0) {
      typeck_fold_expr_ref_impl(arena, init_ref, names, values, n);
      {
        struct ast_Expr *ie = glue_arena_expr_at_ref(arena, init_ref);
        if (ie && ie->const_folded_valid)
          values[n] = (int64_t)ie->const_folded_val;
      }
    }
    n++;
  }
  *out_n = n;
}

/** Fold block const init at const_idx with prior consts in scope. */
void typeck_fold_block_const_init(struct ast_ASTArena *arena, int32_t block_ref,
                                            int32_t const_idx) {
  const char *names[64];
  char name_bufs[64][128];
  int64_t values[64];
  int n = 0;
  int32_t init_ref;
  int32_t type_ref;
  struct ast_Expr *ie;

  if (!arena || const_idx < 0)
    return;
  typeck_block_const_env_build_impl(arena, block_ref, const_idx, names, name_bufs, values, &n);
  init_ref = pipeline_block_const_init_ref(arena, block_ref, const_idx);
  if (init_ref <= 0)
    return;
  typeck_fold_expr_ref_impl(arena, init_ref, names, values, n);
  ie = glue_arena_expr_at_ref(arena, init_ref);
  if (!ie || ie->const_folded_valid)
    return;
  /**
   * C5-array-len: `const N: i32 = [1,2,3,4]` — array lit init with scalar const
   * type folds to element count (LANG-006). Stamp resolved_type to const type
   * so emit/codegen can treat the init as a scalar imm.
   */
  type_ref = pipeline_block_const_type_ref(arena, block_ref, const_idx);
  if (type_ref > 0 && ie->kind == ast_ExprKind_EXPR_ARRAY_LIT) {
    int32_t tk = pipeline_type_kind_ord_at(arena, type_ref);
    if (tk >= 0 && tk <= 7) {
      ie->resolved_type_ref = type_ref;
      ie->const_folded_val = (int32_t)ie->array_lit_num_elems;
      ie->const_folded_valid = 1;
    }
  }
}

/** Fold expr with all block consts as env (let init / return of const names). */
void typeck_fold_expr_in_block(struct ast_ASTArena *arena, int32_t block_ref,
                                         int32_t expr_ref) {
  const char *names[64];
  char name_bufs[64][128];
  int64_t values[64];
  int n = 0;
  int nconst;

  if (!arena || expr_ref <= 0 || block_ref <= 0)
    return;
  nconst = ast_ast_block_num_consts(arena, block_ref);
  typeck_block_const_env_build_impl(arena, block_ref, nconst, names, name_bufs, values, &n);
  typeck_fold_expr_ref_impl(arena, expr_ref, names, values, n);
}



/* wave322 layer-2 mangle aliases (seeds/typeck_mangle_link_alias.from_x.c) */
/* seeds/typeck_mangle_link_alias.from_x.c — wave317 typeck M4 layer-2
 * X-mangle call sites from tip typeck.x -E → short product C faces.
 * G.7: alias-only (zero business logic); short faces on typeck_x / pipeline_abi.
 * Any #[no_mangle] Cap face that typeck.x also forward-declares as
 * `export extern` (call sites emit the mangled name; body stays short)
 * MUST have a thin alias here. Seed typeck_gen snapshot is not the assemble
 * authority — missing rows here UNDEF on the next typeck.x -E.
 * PLATFORM: SHARED freestanding typeck tip re-pin companion (ld -r or append).
 */
#include <stdint.h>

struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;

extern int32_t glue_generic_call_fixup_resolved_type_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
int32_t glue_generic_call_fixup_resolved_type_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) { return glue_generic_call_fixup_resolved_type_c(module, arena, call_expr_ref, ctx, expected_ret); }

extern int32_t pipeline_dep_ctx_typeck_unsafe_depth_at(struct ast_PipelineDepCtx * ctx);
int32_t pipeline_dep_ctx_typeck_unsafe_depth_at_PipelineDepCtx_ptr_reti32(struct ast_PipelineDepCtx * ctx) { return pipeline_dep_ctx_typeck_unsafe_depth_at(ctx); }

extern int32_t pipeline_type_stamp_block_let_region_c(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_type_stamp_block_let_region_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t block_ref, int32_t let_idx, struct ast_PipelineDepCtx * ctx) { return pipeline_type_stamp_block_let_region_c(arena, block_ref, let_idx, ctx); }

extern int32_t pipeline_typeck_block_impl_bind_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
int32_t pipeline_typeck_block_impl_bind_ctx_c_PipelineDepCtx_ptr_i32_reti32(struct ast_PipelineDepCtx * ctx, int32_t block_ref) { return pipeline_typeck_block_impl_bind_ctx_c(ctx, block_ref); }

extern void pipeline_typeck_block_impl_restore_ctx_c(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref);
void pipeline_typeck_block_impl_restore_ctx_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t saved_block_ref) { pipeline_typeck_block_impl_restore_ctx_c(ctx, saved_block_ref); }

extern void pipeline_typeck_block_impl_touch_ctx_block_c(struct ast_PipelineDepCtx * ctx, int32_t block_ref);
void pipeline_typeck_block_impl_touch_ctx_block_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t block_ref) { pipeline_typeck_block_impl_touch_ctx_block_c(ctx, block_ref); }

extern int32_t pipeline_typeck_check_block_one_region_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_check_block_one_region_c_Module_ptr_ASTArena_ptr_i32_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t block_ref, int32_t region_idx, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_check_block_one_region_c(module, arena, block_ref, region_idx, return_type_ref, ctx); }

extern int32_t pipeline_typeck_check_call_generic_type_args_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret);
int32_t pipeline_typeck_check_call_generic_type_args_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_i32_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t expr_ref, struct ast_PipelineDepCtx * ctx, int32_t expected_ret) { return pipeline_typeck_check_call_generic_type_args_c(module, arena, expr_ref, ctx, expected_ret); }

extern int32_t pipeline_typeck_check_call_struct_stack_escape_c(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_check_call_struct_stack_escape_c_Module_ptr_ASTArena_ptr_i32_PipelineDepCtx_ptr_reti32(struct ast_Module * module, struct ast_ASTArena * arena, int32_t call_expr_ref, struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_check_call_struct_stack_escape_c(module, arena, call_expr_ref, ctx); }

extern int32_t pipeline_typeck_check_return_slice_region_in_scope_c(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_check_return_slice_region_in_scope_c_ASTArena_ptr_i32_i32_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t site_expr_ref, int32_t return_type_ref, struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_check_return_slice_region_in_scope_c(arena, site_expr_ref, return_type_ref, ctx); }

extern int32_t pipeline_typeck_is_read_ptr_slice_callee_c(uint8_t * name, int32_t name_len);
int32_t pipeline_typeck_is_read_ptr_slice_callee_c_u8_ptr_i32_reti32(uint8_t * name, int32_t name_len) { return pipeline_typeck_is_read_ptr_slice_callee_c(name, name_len); }

extern int32_t pipeline_typeck_is_simd_comptime_callee_c(uint8_t * name, int32_t name_len);
int32_t pipeline_typeck_is_simd_comptime_callee_c_u8_ptr_i32_reti32(uint8_t * name, int32_t name_len) { return pipeline_typeck_is_simd_comptime_callee_c(name, name_len); }

extern int32_t pipeline_typeck_linear_accepts_init_c(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref);
int32_t pipeline_typeck_linear_accepts_init_c_ASTArena_ptr_i32_i32_reti32(struct ast_ASTArena * arena, int32_t decl_ref, int32_t init_ref) { return pipeline_typeck_linear_accepts_init_c(arena, decl_ref, init_ref); }

extern int32_t pipeline_typeck_linear_use_var_c(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len);
int32_t pipeline_typeck_linear_use_var_c_ASTArena_ptr_i32_i32_u8_ptr_i32_reti32(struct ast_ASTArena * arena, int32_t type_ref, int32_t expr_ref, uint8_t * name, int32_t name_len) { return pipeline_typeck_linear_use_var_c(arena, type_ref, expr_ref, name, name_len); }

extern void pipeline_typeck_loop_depth_set_c(struct ast_PipelineDepCtx * ctx, int32_t depth);
void pipeline_typeck_loop_depth_set_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t depth) { pipeline_typeck_loop_depth_set_c(ctx, depth); }

extern int32_t pipeline_typeck_ptr_for_addr_of_operand_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_ptr_for_addr_of_operand_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t op_ref, int32_t elem_ty, struct ast_Module * module, struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_ptr_for_addr_of_operand_c(arena, op_ref, elem_ty, module, ctx); }

extern int32_t pipeline_typeck_read_ptr_slice_return_ref_c(struct ast_ASTArena * arena);
int32_t pipeline_typeck_read_ptr_slice_return_ref_c_ASTArena_ptr_reti32(struct ast_ASTArena * arena) { return pipeline_typeck_read_ptr_slice_return_ref_c(arena); }

extern int32_t pipeline_typeck_reject_addr_of_linear_c(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_reject_addr_of_linear_c_ASTArena_ptr_i32_i32_Module_ptr_PipelineDepCtx_ptr_reti32(struct ast_ASTArena * arena, int32_t op_ref, int32_t addr_expr_ref, struct ast_Module * module, struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_reject_addr_of_linear_c(arena, op_ref, addr_expr_ref, module, ctx); }

extern int32_t pipeline_typeck_resolve_call_func_index_for_emit_c(uint8_t * m, uint8_t * a, int32_t call_expr_ref);
int32_t pipeline_typeck_resolve_call_func_index_for_emit_c_u8_ptr_u8_ptr_i32_reti32(uint8_t * m, uint8_t * a, int32_t call_expr_ref) { return pipeline_typeck_resolve_call_func_index_for_emit_c(m, a, call_expr_ref); }

extern int32_t pipeline_typeck_type_refs_equal_c(struct ast_ASTArena * arena, int32_t a, int32_t b);
int32_t pipeline_typeck_type_refs_equal_c_ASTArena_ptr_i32_i32_reti32(struct ast_ASTArena * arena, int32_t a, int32_t b) { return pipeline_typeck_type_refs_equal_c(arena, a, b); }

extern void pipeline_typeck_unsafe_depth_pop_c(struct ast_PipelineDepCtx * ctx, int32_t saved);
void pipeline_typeck_unsafe_depth_pop_c_PipelineDepCtx_ptr_i32(struct ast_PipelineDepCtx * ctx, int32_t saved) { pipeline_typeck_unsafe_depth_pop_c(ctx, saved); }

extern int32_t pipeline_typeck_unsafe_depth_push_c(struct ast_PipelineDepCtx * ctx);
int32_t pipeline_typeck_unsafe_depth_push_c_PipelineDepCtx_ptr_reti32(struct ast_PipelineDepCtx * ctx) { return pipeline_typeck_unsafe_depth_push_c(ctx); }
