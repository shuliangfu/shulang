/* Generated from src/x_seed_bridge.x (G-02f-27 true .x + C tail).
 * G-02f-332：PREFER_X_O hybrid thin 由 .x→-E；rest 用 XLANG_L2_X_SEED_BRIDGE_THIN_FROM_X。
 * Regen: ./xlang-c -E -L .. src/x_seed_bridge.x > /tmp/xsb.c
 *         then re-apply C tail (match-module / ast_expr / io_read-write / buffer / weak).
 * .x covers: typeck_preprocess_x_buf, std_heap_*, io register/read_ptr stubs.
 */
#include <xlang_weak.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
/* Why: io_read (L200) and io_write (L209) call POSIX read()/write(), which
 *      require <unistd.h> declarations. The historical `#ifndef _WIN32`
 *      guard assumed Windows lacked <unistd.h>, but the project's
 *      include/unistd.h shim now provides read/write/close/lseek/open wrappers
 *      on MinGW (calling _read/_write/_close/_lseek/_open). Removing the
 *      guard lets Windows MSYS/MinGW resolve read/write via the shim.
 * Invariant: include/unistd.h shim is in -Iinclude search path (CFLAGS L14);
 *            on macOS/Linux it delegates to system <unistd.h> via
 *            #include_next (no behavior change).
 * PLATFORM: SHARED (include always; was Windows-skipped before). */
#include <unistd.h>
#include <xlang_io_cap.h>
#include <stdio.h>
/* sys/types for ssize_t if not from unistd */
#include <sys/types.h>

extern int32_t preprocess_x_buf(uint8_t * src, ssize_t src_len, uint8_t * out_buf, int32_t out_cap);
extern uint8_t * typeck_std_heap_alloc(size_t size);
#ifndef XLANG_L2_X_SEED_BRIDGE_THIN_FROM_X
int32_t typeck_preprocess_x_buf(uint8_t * src, ssize_t src_len, uint8_t * out_buf, int32_t out_cap) {
  (void)(({   {
    int32_t r = preprocess_x_buf(src, src_len, out_buf, out_cap);
    return r;
  }
 }));
  return 0;
}
uint8_t * std_heap_alloc_zeroed(size_t size) {
  (void)(({   {
    uint8_t * r = calloc(1, size);
    return r;
  }
 }));
  return ((uint8_t *)(0));
}
uint8_t * std_heap_alloc_zero(size_t size) {
  return std_heap_alloc_zeroed(size);
}
void std_heap_free(uint8_t * ptr) {
  (void)(({   {
    (void)(free(ptr));
  }
 }));
}
uint8_t * std_heap_alloc(size_t size) {
  (void)(({   {
    uint8_t * r = typeck_std_heap_alloc(size);
    return r;
  }
 }));
  return ((uint8_t *)(0));
}
uint8_t * io_read_ptr(uint32_t handle, uint32_t timeout_ms) {
  return ((uint8_t *)(0));
}
int32_t io_read_ptr_len(void) {
  return 0;
}
int32_t io_register_buffer(uint8_t * ptr, size_t len) {
  return 0;
}
void io_unregister_buffers(void) {
  (void)(0);
}
int32_t io_wait_readable(int32_t * fds, int32_t n, uint32_t timeout_ms) {
  return 0;
}
int32_t io_register_buffers_4(uint8_t * p0, size_t l0, uint8_t * p1, size_t l1, uint8_t * p2, size_t l2, uint8_t * p3, size_t l3, uint32_t nr) {
  return 0;
}
int32_t io_register_buffers_buf(uint8_t * bufs, int32_t nr) {
  return 0;
}
int32_t io_register_buffers_buf_i32(ssize_t bufs, int32_t nr) {
  return io_register_buffers_buf(((uint8_t *)(0)), nr);
}
int32_t xlang_io_register(uint8_t * ptr, size_t len, size_t handle) {
  return io_register_buffer(ptr, len);
}

#else
/* G-02f-332：thin 由 src/x_seed_bridge.x（-E）提供 */
extern int32_t typeck_preprocess_x_buf(uint8_t *src, ssize_t src_len, uint8_t *out_buf, int32_t out_cap);
extern uint8_t *std_heap_alloc_zeroed(size_t size);
extern uint8_t *std_heap_alloc_zero(size_t size);
extern void std_heap_free(uint8_t *ptr);
extern uint8_t *std_heap_alloc(size_t size);
extern uint8_t *io_read_ptr(uint32_t handle, uint32_t timeout_ms);
extern int32_t io_read_ptr_len(void);
extern int32_t io_register_buffer(uint8_t *ptr, size_t len);
extern void io_unregister_buffers(void);
extern int32_t io_wait_readable(int32_t *fds, int32_t n, uint32_t timeout_ms);
extern int32_t io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, uint32_t nr);
extern int32_t io_register_buffers_buf(uint8_t *bufs, int32_t nr);
extern int32_t io_register_buffers_buf_i32(ssize_t bufs, int32_t nr);
extern int32_t xlang_io_register(uint8_t *ptr, size_t len, size_t handle);
#endif

/* ---- C tail (G-02f-27): static global / struct field / ssize io / weak ---- */

/** 与 -E-extern 生成体一致的扁平 ASTExpr（勿 include ast.h 的 ASTExpr，布局不同）。 */
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

struct ast_ASTArena;
struct ast_Module;

/** parser.x parse_match 查 enum tag 时的当前 Module（parse_into 入口设置）。 */
static struct ast_Module *g_parser_match_module_x;

void pipeline_parser_set_match_module(struct ast_Module *m) {
  g_parser_match_module_x = m;
}

struct ast_Module *pipeline_parser_get_match_module(void) {
  return g_parser_match_module_x;
}

extern struct ast_Expr ast_arena_expr_get(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);

/** parser.x 生成体引用；初始化 match 相关字段。verify-selfhost-stage2 链 ast_x2.o 时由 ast.x 导出，勿重复定义。 */
#ifndef X_VERIFY_STAGE2
void ast_expr_init_match_enum(struct ast_Expr *e) {
  if (!e)
    return;
  e->match_matched_ref = 0;
  e->match_arm_base = 0;
  e->match_num_arms = 0;
}
#endif

/** typeck/codegen 生成体引用；重置 call resolve 字段。Stage2 由 ast_x2.o 提供。 */
#ifndef X_VERIFY_STAGE2
void ast_expr_init_call_resolve(struct ast_ASTArena *arena, int32_t expr_ref) {
  struct ast_Expr e;
  if (!arena || expr_ref <= 0)
    return;
  e = ast_arena_expr_get(arena, expr_ref);
  e.call_resolved_func_index = -1;
  e.call_resolved_dep_index = -1;
  ast_arena_expr_set(arena, expr_ref, e);
}
#endif

/** lsp_io.x / pipeline 引用 libc 风格 IO 符号；seed 链 read/write 转发。 */
ptrdiff_t io_read(int fd, uint8_t *buf, size_t count, unsigned timeout_ms) {
  ssize_t n;
  (void)timeout_ms;
  if (!buf || count == 0)
    return 0;
  n = (ssize_t)xlang_io_read(fd, buf, count);
  return n >= 0 ? (ptrdiff_t)n : -1;
}

ptrdiff_t io_write(int fd, uint8_t *buf, size_t count, unsigned timeout_ms) {
  ssize_t n;
  (void)timeout_ms;
  if (!buf || count == 0)
    return 0;
  n = (ssize_t)xlang_io_write(fd, buf, count);
  return n >= 0 ? (ptrdiff_t)n : -1;
}

ptrdiff_t io_read_batch_buf(int fd, const void *bufs, int n, unsigned timeout_ms) {
  (void)fd;
  (void)bufs;
  (void)n;
  (void)timeout_ms;
  return -1;
}

ptrdiff_t io_write_batch_buf(int fd, const void *bufs, int n, unsigned timeout_ms) {
  (void)fd;
  (void)bufs;
  (void)n;
  (void)timeout_ms;
  return -1;
}

ptrdiff_t io_read_fixed(int32_t fd, uint32_t buf_index, size_t offset, size_t len, unsigned timeout_ms) {
  (void)buf_index;
  (void)offset;
  return io_read(fd, NULL, len, timeout_ms);
}

ptrdiff_t io_write_fixed(int32_t fd, uint32_t buf_index, size_t offset, size_t len, unsigned timeout_ms) {
  (void)buf_index;
  (void)offset;
  return io_write(fd, NULL, len, timeout_ms);
}

ptrdiff_t io_read_batch(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2,
                        uint8_t *p3, size_t l3, int32_t n, unsigned timeout_ms) {
  (void)p1;
  (void)l1;
  (void)p2;
  (void)l2;
  (void)p3;
  (void)l3;
  (void)n;
  return io_read(fd, p0, l0, timeout_ms);
}

ptrdiff_t io_write_batch(int32_t fd, uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2,
                         uint8_t *p3, size_t l3, int32_t n, unsigned timeout_ms) {
  (void)p1;
  (void)l1;
  (void)p2;
  (void)l2;
  (void)p3;
  (void)l3;
  (void)n;
  return io_write(fd, p0, l0, timeout_ms);
}

typedef struct {
  uint8_t *ptr;
  size_t length;
  size_t handle;
} xlang_buffer_abi_t;

int32_t xlang_io_register_buf(intptr_t buf) {
  const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf;
  if (!b)
    return -1;
  return xlang_io_register(b->ptr, b->length, b->handle);
}

int32_t xlang_io_submit_read(uint8_t *ptr, size_t len, size_t handle, unsigned timeout_ms) {
  int32_t fd = (int32_t)handle;
  ptrdiff_t r = io_read(fd, ptr, len, timeout_ms);
  if (r < 0)
    return -1;
  return (int32_t)r;
}

int32_t xlang_io_submit_read_buf(intptr_t buf, int32_t timeout_ms) {
  const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf;
  if (!b)
    return -1;
  return xlang_io_submit_read(b->ptr, b->length, b->handle, (unsigned)timeout_ms);
}

int32_t xlang_io_submit_write(uint8_t *ptr, size_t len, size_t handle, unsigned timeout_ms) {
  int32_t fd = (int32_t)handle;
  ptrdiff_t r = io_write(fd, ptr, len, timeout_ms);
  if (r < 0)
    return -1;
  return (int32_t)r;
}

int32_t xlang_io_submit_write_buf(intptr_t buf, int32_t timeout_ms) {
  const xlang_buffer_abi_t *b = (const xlang_buffer_abi_t *)(uintptr_t)buf;
  if (!b)
    return -1;
  return xlang_io_submit_write(b->ptr, b->length, b->handle, (unsigned)timeout_ms);
}

/** lsp_gen 引用 driver_read_ptr*；真 partial 无 phase1 弱桩时兜底。 */
XLANG_WEAK uint8_t *std_io_driver_driver_read_ptr(size_t handle, unsigned timeout_ms) {
  (void)handle;
  (void)timeout_ms;
  return NULL;
}

XLANG_WEAK int32_t std_io_driver_driver_read_ptr_len(void) {
  return 0;
}
