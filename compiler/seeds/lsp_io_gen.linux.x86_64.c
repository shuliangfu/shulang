/* generated (single-file with deps) */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <xlang_fmt_cap.h> /* Cap residual 10.7.2: CRASH_EVIDENCE path → Cap snprintf */
/* G.7: Cap after stdio for compiler-only gen seed pin crash evidence. */
#undef snprintf
#define snprintf xlang_snprintf
#include <xlang_io_cap.h>   /* Cap residual 9.5.3: xlang_io_write / xlang_io_open_write */
#include <xlang_proc_cap.h> /* Cap residual 9.5.3: xlang_proc_close_fd (single close authority) */
#include <string.h>
#include <math.h>
/* wave245 G.7: env via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl.
 * PLATFORM: SHARED orch / host getenv residual via single face.
 * Compiler-only gen seed pin (CRASH_EVIDENCE inline) — not user program template
 * (runtime.from_x.c fprintf CRASH_EVIDENCE user C templates use link_abi_getenv since wave254). */
extern char *link_abi_getenv(const char *name);
extern int getpid(void);
static inline void xlang_crash_evidence_collect_inline(int has_msg, int msg_val) {
  const char *_ev = link_abi_getenv("XLANG_CRASH_EVIDENCE");
  char _note[192];
  if (!_ev || _ev[0] != '1') return;
  int _pid = (int)getpid();
  { int _n = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] panic=%d msg=%d frames=0 pid=%d\n", has_msg, msg_val, _pid);
    if (_n > 0) (void)xlang_io_write(2, _note, (size_t)_n); }
  { const char *_dir = link_abi_getenv("XLANG_CRASH_EVIDENCE_DIR");
    if (_dir && _dir[0]) { char _p[1024]; snprintf(_p, sizeof _p, "%s/xlang-crash-%d.txt", _dir, _pid);
      { int _fd = xlang_io_open_write(_p);
        if (_fd >= 0) { char _body[160];
          int _bl = snprintf(_body, sizeof _body, "panic_has_msg=%d\npanic_msg=%d\nframes=0\npid=%d\n", has_msg, msg_val, _pid);
          if (_bl > 0) (void)xlang_io_write(_fd, _body, (size_t)_bl);
          (void)xlang_proc_close_fd(_fd);
          { int _bn = snprintf(_note, sizeof _note, "xlang: [XLANG_CRASH_EVIDENCE] bundle=%s\n", _p);
            if (_bn > 0) (void)xlang_io_write(2, _note, (size_t)_bn); } } } } }
}
static inline void xlang_panic_(int has_msg, int msg_val) __attribute__((noreturn, cold));
static inline void xlang_panic_(int has_msg, int msg_val) {
  xlang_crash_evidence_collect_inline(has_msg, msg_val);
  if (has_msg) { char _mb[32]; int _mn = snprintf(_mb, sizeof _mb, "%d\n", msg_val);
    if (_mn > 0) (void)xlang_io_write(2, _mb, (size_t)_mn); }
  abort();
}
struct std_io_sync_Iovec { uint8_t * base; size_t length; };
struct std_io_sync_PollFd { int32_t fd; int16_t events; int16_t revents; };
struct std_io_sync_IoBatchBuf { uint8_t * ptr; size_t length; size_t handle; };
struct std_io_read_ptr_XlangSliceU8 { uint8_t * data; size_t length; };
struct std_io_backend_IoBatchBuf { uint8_t * ptr; size_t length; size_t handle; };
struct std_io_backend_XlangSliceU8 { uint8_t * data; size_t length; };
enum std_io_driver_IO_Result { std_io_driver_IO_Result_Ok, std_io_driver_IO_Result_Err, std_io_driver_IO_Result_Timeout, std_io_driver_IO_Result_Cancelled };
struct std_io_driver_Buffer { uint8_t * ptr; size_t length; size_t handle; };
struct std_io_driver_Completion { int32_t tag; };
struct std_io_driver_AsyncContext { uint32_t flags; };
struct std_context_Context { int64_t handle; };
struct core_result_Result_i32 { int32_t value; int32_t _pad1; int32_t err; int32_t _pad2; };
struct core_result_Result_u8 { uint8_t value; uint8_t _pad1; uint8_t _pad2; uint8_t _pad3; int32_t err; int32_t _pad4; };
struct std_error_Error { int32_t code; };
struct std_error_ErrorChain { int32_t depth; int32_t c0; int32_t c1; int32_t c2; int32_t c3; };
struct xlang_slice_uint8_t { uint8_t *data; size_t length; };
struct std_io_ReadOnlySlice { struct xlang_slice_uint8_t data; };
struct std_io_WriteOnlySlice { struct xlang_slice_uint8_t data; };
struct std_io_ReadPtrView { uint8_t * ptr; int32_t length; uint64_t gen; };
struct std_heap_libc_Arena64 { uint8_t * chunk; size_t cap; size_t off; };
struct std_heap_page_mmap_PageMmapHeap { uint8_t * base; size_t cap; size_t off; };
struct std_heap_Arena64 { uint8_t * chunk; size_t cap; size_t off; };
struct std_heap_HeapTraceStats { uint64_t alloc_count; uint64_t free_count; uint64_t realloc_count; uint64_t bytes_allocated; };
struct std_heap_Allocator { int32_t kind; struct std_heap_Arena64 * arena; };
/* slim arena grow pool glue (C-04 codegen; linked from pipeline/runtime) */
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena *a, int32_t ref);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena *a, int32_t ref);
extern void ast_arena_expr_set(struct ast_ASTArena *a, int32_t ref, struct ast_Expr e);
extern void ast_arena_block_set(struct ast_ASTArena *a, int32_t ref, struct ast_Block b);
extern void ast_arena_type_set(struct ast_ASTArena *a, int32_t ref, struct ast_Type t);
extern void ast_arena_func_set(struct ast_ASTArena *a, int32_t ref, struct ast_Func f);


/* lsp_codegen_extern: std.heap typeck 链接别名（C-04 v0；std_io extern 由 codegen 自动生成） */
extern uint8_t *typeck_std_heap_alloc(size_t size);
extern void typeck_std_heap_free(uint8_t *ptr);
#define std_heap_alloc typeck_std_heap_alloc
#define std_heap_free typeck_std_heap_free
static int32_t lsp_io_LSP_BODY_SAFETY_CAP = 1048576;
static int32_t lsp_io_LSP_STATE_LEFTOVER_OFF = 0;
static int32_t lsp_io_LSP_STATE_LEFTOVER_MAX = 8192 * 2;
static int32_t lsp_io_LSP_STATE_LEN_OFF = 8192 * 2;
extern int32_t std_io_read_usize_u8_ptr_usize_u32(size_t handle, uint8_t * ptr, size_t len, uint32_t timeout_ms);
extern int32_t std_io_write_usize_u8_ptr_usize_u32(size_t handle, uint8_t * ptr, size_t len, uint32_t timeout_ms);
extern void lsp_diag_invalidate_cache();
extern void lsp_debug_u32(uint32_t n);
extern void lsp_debug_ptr(uint8_t * p);
ptrdiff_t lsp_io_read_message(int32_t fd, uint8_t * body_out, int32_t body_cap, uint8_t * state_buf);
int32_t lsp_io_parse_content_length_in_buf(uint8_t * state_buf, int32_t off, int32_t header_end);
ptrdiff_t lsp_io_write_fd(int32_t fd, uint8_t * ptr, size_t count);
int32_t lsp_io_extract_document_text(uint8_t * body, int32_t body_len, uint8_t * out_buf, int32_t out_cap);
uint8_t * lsp_io_lsp_alloc(size_t size);
void lsp_io_lsp_free(uint8_t * ptr);
int32_t lsp_io_lsp_is_null(uint8_t * ptr);
ptrdiff_t lsp_io_read_message(int32_t fd, uint8_t * body_out, int32_t body_cap, uint8_t * state_buf) {
  size_t h = ((size_t)(0));
  (void)(({ int32_t __tmp = 0; if (fd != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t b0 = (state_buf)[lsp_io_LSP_STATE_LEN_OFF];
  uint8_t b1 = (state_buf)[lsp_io_LSP_STATE_LEN_OFF + 1];
  uint8_t b2 = (state_buf)[lsp_io_LSP_STATE_LEN_OFF + 2];
  uint8_t b3 = (state_buf)[lsp_io_LSP_STATE_LEN_OFF + 3];
  int32_t n0 = ((int32_t)(b0));
  int32_t n1 = ((int32_t)(b1)) << 8;
  int32_t n2 = ((int32_t)(b2)) << 16;
  int32_t n3 = ((int32_t)(b3)) << 24;
  int32_t n = ((n0 + n1) + n2) + n3;
  (void)(({ int32_t __tmp = 0; if (n < 0 || n > lsp_io_LSP_STATE_LEFTOVER_MAX) {   (n = (0));
 } else (__tmp = 0) ; __tmp; }));
  (void)(lsp_debug_ptr(state_buf));
  (void)(({ int32_t __tmp = 0; if (n > 0) {   (void)(lsp_debug_u32(((uint32_t)(n))));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n < lsp_io_LSP_STATE_LEFTOVER_MAX) {   while (n < lsp_io_LSP_STATE_LEFTOVER_MAX) {
    int32_t got = std_io_read_usize_u8_ptr_usize_u32(h, (&((state_buf)[n])), ((size_t)(lsp_io_LSP_STATE_LEFTOVER_MAX - n)), ((uint32_t)(0)));
    (void)(({ int32_t __tmp = 0; if (got > 0) {   (n = (n + got));
 } else {   break;
 } ; __tmp; }));
  }
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (n <= 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t i = 0;
  while (i + 4 <= n) {
    (void)(({ int32_t __tmp = 0; if ((state_buf)[i] == 13 && (state_buf)[i + 1] == 10 && (state_buf)[i + 2] == 13 && (state_buf)[i + 3] == 10) {   break;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  (void)(({ int32_t __tmp = 0; if (i + 4 > n) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t header_end = i + 4;
  int32_t content_len = lsp_io_parse_content_length_in_buf(state_buf, 0, header_end);
  (void)(({ int32_t __tmp = 0; if (content_len <= 0 || content_len > body_cap || content_len > lsp_io_LSP_BODY_SAFETY_CAP) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t body_in_buf = n - header_end;
  int32_t to_copy = ({ int32_t __tmp = 0; if (body_in_buf > content_len) {   __tmp = content_len;
 } else {   __tmp = body_in_buf;
 } ; __tmp; });
  int32_t j = 0;
  while (j < to_copy) {
    ((body_out)[j] = ((state_buf)[header_end + j]));
    ++j;
  }
  (void)(({ int32_t __tmp = 0; if (content_len > to_copy) {   int32_t remain = content_len - to_copy;
  int32_t r = std_io_read_usize_u8_ptr_usize_u32(h, (&((body_out)[to_copy])), ((size_t)(remain)), ((uint32_t)(0)));
  __tmp = ({ int32_t __tmp = 0; if (r != remain) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  int32_t consumed = header_end + content_len;
  int32_t new_n = n - consumed;
  (void)(({ int32_t __tmp = 0; if (new_n > 0) {   int32_t k = 0;
  while (k < new_n) {
    ((state_buf)[k] = ((state_buf)[consumed + k]));
    ++k;
  }
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF] = (((uint8_t)(new_n & 255))));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 1] = (((uint8_t)(new_n >> 8 & 255))));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 2] = (((uint8_t)(new_n >> 16 & 255))));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 3] = (((uint8_t)(new_n >> 24 & 255))));
  (void)(lsp_debug_u32(((uint32_t)(new_n))));
 } else {   ((state_buf)[lsp_io_LSP_STATE_LEN_OFF] = (0));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 1] = (0));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 2] = (0));
  ((state_buf)[lsp_io_LSP_STATE_LEN_OFF + 3] = (0));
 } ; __tmp; }));
  return ((ptrdiff_t)(content_len));
}
int32_t lsp_io_parse_content_length_in_buf(uint8_t * state_buf, int32_t off, int32_t header_end) {
  (void)(({ int32_t __tmp = 0; if (header_end < 16) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  uint8_t key[16] = { 67, 111, 110, 116, 101, 110, 116, 45, 76, 101, 110, 103, 116, 104, 58, 32 };
  int32_t ki = 0;
  while (ki < 16) {
    (void)(({ int32_t __tmp = 0; if ((state_buf)[off + ki] != (key)[ki]) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
    ++ki;
  }
  int32_t val = 0;
  int32_t i = 16;
  while (i < header_end) {
    uint8_t c0 = (state_buf)[off + i];
    (void)(({ int32_t __tmp = 0; if (c0 != 32 && c0 != 9) {   break;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  while (i < header_end) {
    uint8_t c = (state_buf)[off + i];
    (void)(({ int32_t __tmp = 0; if (c >= 48 && c <= 57) {   (val = ((val * 10 + ((int32_t)(c))) - 48));
  ++i;
 } else {   break;
 } ; __tmp; }));
  }
  return val;
}
ptrdiff_t lsp_io_write_fd(int32_t fd, uint8_t * ptr, size_t count) {
  size_t h = ((size_t)(1));
  (void)(({ ptrdiff_t __tmp = 0; if (fd != 1) {   return ((ptrdiff_t)((-1)));
 } else (__tmp = 0) ; __tmp; }));
  size_t off = ((size_t)(0));
  while (off < count) {
    int32_t r = std_io_write_usize_u8_ptr_usize_u32(h, (&((ptr)[off])), count - off, ((uint32_t)(0)));
    (void)(({ ptrdiff_t __tmp = 0; if (r <= 0) {   return ((ptrdiff_t)((-1)));
 } else (__tmp = 0) ; __tmp; }));
    (off = (off + ((size_t)(r))));
  }
  return ((ptrdiff_t)(count));
}
int32_t lsp_io_extract_document_text(uint8_t * body, int32_t body_len, uint8_t * out_buf, int32_t out_cap) {
  int32_t key_len = 8;
  uint8_t key[8] = { 34, 116, 101, 120, 116, 34, 58, 34 };
  int32_t i = 0;
  while (i + key_len <= body_len) {
    int32_t is_match = 1;
    int32_t k = 0;
    while (k < key_len) {
      (void)(({ int32_t __tmp = 0; if ((body)[i + k] != (k < 0 || (k) >= 8 ? (xlang_panic_(1, 0), (key)[0]) : (key)[k])) {   (is_match = (0));
  break;
 } else (__tmp = 0) ; __tmp; }));
      ++k;
    }
    (void)(({ int32_t __tmp = 0; if (is_match != 0) {   int32_t start = i + key_len;
  int32_t out_len = 0;
  while (start < body_len && out_len < out_cap - 1) {
    uint8_t c = (body)[start];
    (void)(({ int32_t __tmp = 0; if (c == 34) {   break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (c == 92 && start + 1 < body_len) {   ++start;
  uint8_t next = (body)[start];
  (void)(({ int32_t __tmp = 0; if (next == 110) {   ((out_buf)[out_len] = (10));
  ++out_len;
  ++start;
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (next == 114) {   ((out_buf)[out_len] = (13));
  ++out_len;
  ++start;
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (next == 116) {   ((out_buf)[out_len] = (9));
  ++out_len;
  ++start;
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (next == 34 || next == 92) {   ((out_buf)[out_len] = (next));
  ++out_len;
  ++start;
  continue;
 } else (__tmp = 0) ; __tmp; }));
  ((out_buf)[out_len] = (next));
  ++out_len;
  ++start;
  continue;
 } else (__tmp = 0) ; __tmp; }));
    ((out_buf)[out_len] = (c));
    ++out_len;
    ++start;
  }
  ((out_buf)[out_len] = (0));
  return out_len;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return (-1);
}
uint8_t * lsp_io_lsp_alloc(size_t size) {
  (void)(({ uint8_t * __tmp = 0; if (size == 0 || size > ((size_t)(lsp_io_LSP_BODY_SAFETY_CAP))) {   return ((uint8_t *)(0));
 } else (__tmp = 0) ; __tmp; }));
  return std_heap_alloc_usize(size);
}
void lsp_io_lsp_free(uint8_t * ptr) {
  (void)(std_heap_free_u8_ptr(ptr));
}
int32_t lsp_io_lsp_is_null(uint8_t * ptr) {
  (void)(({ int32_t __tmp = 0; if (ptr == ((uint8_t *)(0))) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
