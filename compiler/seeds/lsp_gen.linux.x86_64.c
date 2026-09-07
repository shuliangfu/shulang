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

static int32_t lsp_LSP_BODY_CAP = 1048576;
static int32_t lsp_LSP_STATE_SIZE = 4 + 8192 * 2;
static int32_t lsp_LSP_DIAG_RESP_CAP = 32768;
static int32_t lsp_LSP_REF_RESP_CAP = 8192;
static int32_t lsp_LSP_FORMAT_RESP_CAP = 262144;
extern uint8_t * typeck_lsp_alloc(size_t size);
static inline uint8_t * lsp_io_lsp_alloc(size_t size) {
  return typeck_lsp_alloc(size);
}
extern ptrdiff_t typeck_read_message(int32_t fd, uint8_t * body_out, int32_t body_cap, uint8_t * state_buf);
static inline ptrdiff_t lsp_io_read_message(int32_t fd, uint8_t * body_out, int32_t body_cap, uint8_t * state_buf) {
  return typeck_read_message(fd, body_out, body_cap, state_buf);
}
extern int32_t typeck_lsp_is_null(uint8_t * ptr);
static inline int32_t lsp_io_lsp_is_null(uint8_t * ptr) {
  return typeck_lsp_is_null(ptr);
}
extern void typeck_lsp_free(uint8_t * ptr);
static inline void lsp_io_lsp_free(uint8_t * ptr) {
  return typeck_lsp_free(ptr);
}
extern void lsp_io_lsp_diag_invalidate_cache();
extern uint8_t * lsp_state_buf_ptr();
extern int32_t lsp_write_all(int32_t fd, uint8_t * ptr, int32_t len);
extern int32_t lsp_build_initialize_result(int32_t id_val, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_diagnostics_response(int32_t id_val, uint8_t * source, int32_t source_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_definition_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_references_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_hover_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_formatting_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_completion_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_document_symbol_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_semantic_tokens_response(int32_t id_val, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern int32_t lsp_build_rename_response(int32_t id_val, uint8_t * body, int32_t body_len, uint8_t * doc_buf, int32_t doc_len, uint8_t * out_buf, int32_t out_cap);
extern void lsp_diag_invalidate_cache();
extern int32_t lsp_build_response_with_result(int32_t id_val, uint8_t * result_ptr, int32_t result_len, uint8_t * out_buf, int32_t out_cap);
extern void lsp_set_document_from_body(uint8_t * body, int32_t body_len);
extern uint8_t * lsp_get_document_ptr();
extern int32_t lsp_get_document_len();
int32_t lsp_body_contains_initialize(uint8_t * body, int32_t len);
int32_t lsp_body_contains_initialized(uint8_t * body, int32_t len);
int32_t lsp_body_contains_shutdown(uint8_t * body, int32_t len);
int32_t lsp_body_contains_did_open(uint8_t * body, int32_t len);
int32_t lsp_body_contains_did_change(uint8_t * body, int32_t len);
int32_t lsp_body_contains_did_save(uint8_t * body, int32_t len);
int32_t lsp_body_contains_diagnostic(uint8_t * body, int32_t len);
int32_t lsp_body_contains_completion(uint8_t * body, int32_t len);
int32_t lsp_body_contains_document_symbol(uint8_t * body, int32_t len);
int32_t lsp_body_contains_semantic_tokens(uint8_t * body, int32_t len);
int32_t lsp_body_contains_rename(uint8_t * body, int32_t len);
int32_t lsp_body_contains_did_close(uint8_t * body, int32_t len);
int32_t lsp_body_contains_cancel(uint8_t * body, int32_t len);
int32_t lsp_body_contains_did_change_config(uint8_t * body, int32_t len);
int32_t lsp_body_contains_definition(uint8_t * body, int32_t len);
int32_t lsp_body_contains_references(uint8_t * body, int32_t len);
int32_t lsp_body_contains_hover(uint8_t * body, int32_t len);
int32_t lsp_body_contains_formatting(uint8_t * body, int32_t len);
int32_t lsp_body_contains_exit(uint8_t * body, int32_t len);
int32_t lsp_parse_id(uint8_t * body, int32_t len, uint8_t * id_buf, int32_t id_buf_len);
int32_t lsp_send_response(int32_t fd, uint8_t * body, int32_t body_len);
int32_t lsp_main_impl();
int32_t lsp_body_contains_initialize(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 10 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 105 && (body)[i + 1] == 110 && (body)[i + 2] == 105 && (body)[i + 3] == 116 && (body)[i + 4] == 105 && (body)[i + 5] == 97 && (body)[i + 6] == 108 && (body)[i + 7] == 105 && (body)[i + 8] == 122 && (body)[i + 9] == 101) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_initialized(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 11 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 105 && (body)[i + 1] == 110 && (body)[i + 2] == 105 && (body)[i + 3] == 116 && (body)[i + 4] == 105 && (body)[i + 5] == 97 && (body)[i + 6] == 108 && (body)[i + 7] == 105 && (body)[i + 8] == 122 && (body)[i + 9] == 101 && (body)[i + 10] == 100) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_shutdown(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 8 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 115 && (body)[i + 1] == 104 && (body)[i + 2] == 117 && (body)[i + 3] == 116 && (body)[i + 4] == 100 && (body)[i + 5] == 111 && (body)[i + 6] == 119 && (body)[i + 7] == 110) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_did_open(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 19 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 105 && (body)[i + 15] == 100 && (body)[i + 16] == 79 && (body)[i + 17] == 112 && (body)[i + 18] == 101 && (body)[i + 19] == 110) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_did_change(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 21 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 105 && (body)[i + 15] == 100 && (body)[i + 16] == 67 && (body)[i + 17] == 104 && (body)[i + 18] == 97 && (body)[i + 19] == 110 && (body)[i + 20] == 103 && (body)[i + 21] == 101) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_did_save(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 19 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 105 && (body)[i + 15] == 100 && (body)[i + 16] == 83 && (body)[i + 17] == 97 && (body)[i + 18] == 118 && (body)[i + 19] == 101) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_diagnostic(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 23 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 105 && (body)[i + 15] == 97 && (body)[i + 16] == 103 && (body)[i + 17] == 110 && (body)[i + 18] == 111 && (body)[i + 19] == 115 && (body)[i + 20] == 116 && (body)[i + 21] == 105 && (body)[i + 22] == 99) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_completion(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 23 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 99 && (body)[i + 14] == 111 && (body)[i + 15] == 109 && (body)[i + 16] == 112 && (body)[i + 17] == 108 && (body)[i + 18] == 101 && (body)[i + 19] == 116 && (body)[i + 20] == 105 && (body)[i + 21] == 111 && (body)[i + 22] == 110) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_document_symbol(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 27 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 111 && (body)[i + 15] == 99 && (body)[i + 16] == 117 && (body)[i + 17] == 109 && (body)[i + 18] == 101 && (body)[i + 19] == 110 && (body)[i + 20] == 116 && (body)[i + 21] == 83 && (body)[i + 22] == 121 && (body)[i + 23] == 109 && (body)[i + 24] == 98 && (body)[i + 25] == 111 && (body)[i + 26] == 108) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_semantic_tokens(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 28 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 115 && (body)[i + 14] == 101 && (body)[i + 15] == 109 && (body)[i + 16] == 97 && (body)[i + 17] == 110 && (body)[i + 18] == 116 && (body)[i + 19] == 105 && (body)[i + 20] == 99 && (body)[i + 21] == 84 && (body)[i + 22] == 111 && (body)[i + 23] == 107 && (body)[i + 24] == 101 && (body)[i + 25] == 110 && (body)[i + 26] == 115) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_rename(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 20 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 114 && (body)[i + 14] == 101 && (body)[i + 15] == 110 && (body)[i + 16] == 97 && (body)[i + 17] == 109 && (body)[i + 18] == 101) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_did_close(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 20 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 105 && (body)[i + 15] == 100 && (body)[i + 16] == 67 && (body)[i + 17] == 108 && (body)[i + 18] == 111 && (body)[i + 19] == 115 && (body)[i + 20] == 101) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_cancel(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 14 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 36 && (body)[i + 1] == 47 && (body)[i + 2] == 99 && (body)[i + 3] == 97 && (body)[i + 4] == 110 && (body)[i + 5] == 99 && (body)[i + 6] == 101 && (body)[i + 7] == 108 && (body)[i + 8] == 82 && (body)[i + 9] == 101 && (body)[i + 10] == 113 && (body)[i + 11] == 117 && (body)[i + 12] == 101 && (body)[i + 13] == 115 && (body)[i + 14] == 116) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_did_change_config(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 35 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 119 && (body)[i + 1] == 111 && (body)[i + 2] == 114 && (body)[i + 3] == 107 && (body)[i + 4] == 115 && (body)[i + 5] == 112 && (body)[i + 6] == 97 && (body)[i + 7] == 99 && (body)[i + 8] == 101 && (body)[i + 9] == 47 && (body)[i + 10] == 100 && (body)[i + 11] == 105 && (body)[i + 12] == 100 && (body)[i + 13] == 67 && (body)[i + 14] == 104 && (body)[i + 15] == 97 && (body)[i + 16] == 110 && (body)[i + 17] == 103 && (body)[i + 18] == 101 && (body)[i + 19] == 67 && (body)[i + 20] == 111 && (body)[i + 21] == 110 && (body)[i + 22] == 102 && (body)[i + 23] == 105 && (body)[i + 24] == 103 && (body)[i + 25] == 117 && (body)[i + 26] == 114 && (body)[i + 27] == 97 && (body)[i + 28] == 116 && (body)[i + 29] == 105 && (body)[i + 30] == 111 && (body)[i + 31] == 110) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_definition(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 22 < len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 100 && (body)[i + 14] == 101 && (body)[i + 15] == 102 && (body)[i + 16] == 105 && (body)[i + 17] == 110 && (body)[i + 18] == 105 && (body)[i + 19] == 116 && (body)[i + 20] == 105 && (body)[i + 21] == 111 && (body)[i + 22] == 110) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_references(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 23 < len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 114 && (body)[i + 14] == 101 && (body)[i + 15] == 102 && (body)[i + 16] == 101 && (body)[i + 17] == 114 && (body)[i + 18] == 101 && (body)[i + 19] == 110 && (body)[i + 20] == 99 && (body)[i + 21] == 101 && (body)[i + 22] == 115 && (body)[i + 23] == 115) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_hover(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 17 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 104 && (body)[i + 14] == 111 && (body)[i + 15] == 118 && (body)[i + 16] == 101 && (body)[i + 17] == 114) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_formatting(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 23 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 116 && (body)[i + 1] == 101 && (body)[i + 2] == 120 && (body)[i + 3] == 116 && (body)[i + 4] == 68 && (body)[i + 5] == 111 && (body)[i + 6] == 99 && (body)[i + 7] == 117 && (body)[i + 8] == 109 && (body)[i + 9] == 101 && (body)[i + 10] == 110 && (body)[i + 11] == 116 && (body)[i + 12] == 47 && (body)[i + 13] == 102 && (body)[i + 14] == 111 && (body)[i + 15] == 114 && (body)[i + 16] == 109 && (body)[i + 17] == 97 && (body)[i + 18] == 116 && (body)[i + 19] == 116 && (body)[i + 20] == 105 && (body)[i + 21] == 110 && (body)[i + 22] == 103) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_body_contains_exit(uint8_t * body, int32_t len) {
  int32_t i = 0;
  while (i + 4 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 101 && (body)[i + 1] == 120 && (body)[i + 2] == 105 && (body)[i + 3] == 116) {   return 1;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return 0;
}
int32_t lsp_parse_id(uint8_t * body, int32_t len, uint8_t * id_buf, int32_t id_buf_len) {
  int32_t i = 0;
  while (i + 6 <= len) {
    (void)(({ int32_t __tmp = 0; if ((body)[i] == 34 && (body)[i + 1] == 105 && (body)[i + 2] == 100 && (body)[i + 3] == 34 && (body)[i + 4] == 58) {   i += 5;
  while (i < len && (body)[i] == 32 || (body)[i] == 9) {
    ++i;
  }
  (void)(({ int32_t __tmp = 0; if (i >= len) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  int32_t val = 0;
  int32_t j = 0;
  while (i < len && j < id_buf_len - 1) {
    uint8_t c = (body)[i];
    (void)(({ int32_t __tmp = 0; if (c >= 48 && c <= 57) {   (val = ((val * 10 + ((int32_t)(c))) - 48));
  ((id_buf)[j] = (c));
  ++j;
  ++i;
 } else {   break;
 } ; __tmp; }));
  }
  ((id_buf)[j] = (0));
  return val;
 } else (__tmp = 0) ; __tmp; }));
    ++i;
  }
  return (-1);
}
int32_t lsp_send_response(int32_t fd, uint8_t * body, int32_t body_len) {
  uint8_t header[128] = { 0 };
  ((header)[0] = (67));
  ((1 < 0 || (1) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[1] = 111, 0)));
  ((2 < 0 || (2) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[2] = 110, 0)));
  ((3 < 0 || (3) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[3] = 116, 0)));
  ((4 < 0 || (4) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[4] = 101, 0)));
  ((5 < 0 || (5) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[5] = 110, 0)));
  ((6 < 0 || (6) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[6] = 116, 0)));
  ((7 < 0 || (7) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[7] = 45, 0)));
  ((8 < 0 || (8) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[8] = 76, 0)));
  ((9 < 0 || (9) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[9] = 101, 0)));
  ((10 < 0 || (10) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[10] = 110, 0)));
  ((11 < 0 || (11) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[11] = 103, 0)));
  ((12 < 0 || (12) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[12] = 116, 0)));
  ((13 < 0 || (13) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[13] = 104, 0)));
  ((14 < 0 || (14) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[14] = 58, 0)));
  ((15 < 0 || (15) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[15] = 32, 0)));
  int32_t n = body_len;
  int32_t k = 16;
  (void)(({ int32_t __tmp = 0; if (n == 0) {   ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = 48, 0)));
  ++k;
 } else {   int32_t digits[12] = { 0 };
  int32_t d = 0;
  int32_t n2 = n;
  while (n2 > 0) {
    ((d < 0 || (d) >= 12 ? (xlang_panic_(1, 0), 0) : ((digits)[d] = (10 == 0 ? (xlang_panic_(1, 0), n2) : (n2 % 10)), 0)));
    (n2 = ((10 == 0 ? (xlang_panic_(1, 0), n2) : (n2 / 10))));
    ++d;
  }
  int32_t idx = d - 1;
  while (idx >= 0) {
    ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = ((uint8_t)((idx < 0 || (idx) >= 12 ? (xlang_panic_(1, 0), (digits)[0]) : (digits)[idx]) + 48)), 0)));
    ++k;
    (idx = (idx - 1));
  }
 } ; __tmp; }));
  ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = 13, 0)));
  ++k;
  ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = 10, 0)));
  ++k;
  ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = 13, 0)));
  ++k;
  ((k < 0 || (k) >= 64 ? (xlang_panic_(1, 0), 0) : ((header)[k] = 10, 0)));
  ++k;
  int32_t w = lsp_write_all(fd, header, k);
  (void)(({ int32_t __tmp = 0; if (w != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (body_len > 0) {   int32_t w2 = lsp_write_all(fd, body, body_len);
  __tmp = ({ int32_t __tmp = 0; if (w2 != 0) {   return (-1);
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
  return 0;
}
int32_t lsp_main_impl() {
  int32_t stdin_fd = 0;
  int32_t stdout_fd = 1;
  uint8_t out_buf[4096] = { 0 };
  int32_t shutdown_requested = 0;
  uint8_t id_buf[32] = { 0 };
  uint8_t * state_ptr = lsp_state_buf_ptr();
  uint8_t * diag_ptr = lsp_io_lsp_alloc(((size_t)(lsp_LSP_DIAG_RESP_CAP)));
  uint8_t * ref_ptr = lsp_io_lsp_alloc(((size_t)(lsp_LSP_REF_RESP_CAP)));
  uint8_t * format_ptr = lsp_io_lsp_alloc(((size_t)(lsp_LSP_FORMAT_RESP_CAP)));
  (void)(({ int32_t __tmp = 0; if (lsp_io_lsp_is_null(state_ptr) != 0 || lsp_io_lsp_is_null(diag_ptr) != 0 || lsp_io_lsp_is_null(ref_ptr) != 0 || lsp_io_lsp_is_null(format_ptr) != 0) {   (void)(({ int32_t __tmp = 0; if (lsp_io_lsp_is_null(diag_ptr) == 0) {   (void)(lsp_io_lsp_free(diag_ptr));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_io_lsp_is_null(ref_ptr) == 0) {   (void)(lsp_io_lsp_free(ref_ptr));
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_io_lsp_is_null(format_ptr) == 0) {   (void)(lsp_io_lsp_free(format_ptr));
 } else (__tmp = 0) ; __tmp; }));
  return (-1);
 } else (__tmp = 0) ; __tmp; }));
  while (1) {
    uint8_t * body_ptr = lsp_io_lsp_alloc(((size_t)(lsp_LSP_BODY_CAP)));
    (void)(({ int32_t __tmp = 0; if (lsp_io_lsp_is_null(body_ptr) != 0) {   continue;
 } else (__tmp = 0) ; __tmp; }));
    ptrdiff_t msg_len = lsp_io_read_message(stdin_fd, body_ptr, lsp_LSP_BODY_CAP, state_ptr);
    (void)(({ int32_t __tmp = 0; if (msg_len < 0) {   (void)(lsp_io_lsp_free(body_ptr));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (msg_len == 0) {   (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    int32_t content_len = ((int32_t)(msg_len));
    (void)(({ int32_t __tmp = 0; if (content_len > lsp_LSP_BODY_CAP) {   (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_did_open(body_ptr, content_len) != 0) {   (void)(lsp_set_document_from_body(body_ptr, content_len));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_did_change(body_ptr, content_len) != 0) {   (void)(lsp_set_document_from_body(body_ptr, content_len));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_did_save(body_ptr, content_len) != 0) {   (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_did_close(body_ptr, content_len) != 0) {   (void)(lsp_diag_invalidate_cache());
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_cancel(body_ptr, content_len) != 0) {   (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_did_change_config(body_ptr, content_len) != 0) {   (void)(lsp_diag_invalidate_cache());
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_exit(body_ptr, content_len) != 0 && shutdown_requested != 0) {   (void)(lsp_io_lsp_free(body_ptr));
  break;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_shutdown(body_ptr, content_len) != 0) {   (shutdown_requested = (1));
  int32_t sid = lsp_parse_id(body_ptr, content_len, id_buf, 32);
  (void)(({ int32_t __tmp = 0; if (sid < 0) {   (sid = (1));
 } else (__tmp = 0) ; __tmp; }));
  uint8_t null_val[4] = { 110, 117, 108, 108 };
  int32_t resp_len = lsp_build_response_with_result(sid, null_val, 4, out_buf, 4096);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, resp_len));
 } else (__tmp = 0) ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_initialized(body_ptr, content_len) != 0) {   (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    (void)(({ int32_t __tmp = 0; if (lsp_body_contains_initialize(body_ptr, content_len) != 0) {   int32_t sid = lsp_parse_id(body_ptr, content_len, id_buf, 32);
  (void)(({ int32_t __tmp = 0; if (sid < 0) {   (sid = (1));
 } else (__tmp = 0) ; __tmp; }));
  int32_t out_len = lsp_build_initialize_result(sid, diag_ptr, lsp_LSP_DIAG_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (out_len > 0) {   (void)(lsp_send_response(stdout_fd, diag_ptr, out_len));
 } else (__tmp = 0) ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
    int32_t req_id = lsp_parse_id(body_ptr, content_len, id_buf, 32);
    uint8_t * doc_ptr = lsp_get_document_ptr();
    int32_t doc_len = lsp_get_document_len();
    (void)(({ int32_t __tmp = 0; if (req_id >= 0) {   uint8_t empty_arr[2] = { 91, 93 };
  uint8_t null_val[4] = { 110, 117, 108, 108 };
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_diagnostic(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_diagnostics_response(req_id, doc_ptr, doc_len, diag_ptr, lsp_LSP_DIAG_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, diag_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_definition(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_definition_response(req_id, body_ptr, content_len, doc_ptr, doc_len, out_buf, 4096);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, null_val, 4, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_references(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_references_response(req_id, body_ptr, content_len, doc_ptr, doc_len, ref_ptr, lsp_LSP_REF_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, ref_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_hover(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_hover_response(req_id, body_ptr, content_len, doc_ptr, doc_len, out_buf, 4096);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, null_val, 4, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_formatting(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_formatting_response(req_id, body_ptr, content_len, doc_ptr, doc_len, format_ptr, lsp_LSP_FORMAT_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, format_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_completion(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_completion_response(req_id, body_ptr, content_len, doc_ptr, doc_len, format_ptr, lsp_LSP_FORMAT_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, format_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_document_symbol(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_document_symbol_response(req_id, body_ptr, content_len, doc_ptr, doc_len, format_ptr, lsp_LSP_FORMAT_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, format_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  (void)(({ int32_t __tmp = 0; if (lsp_body_contains_semantic_tokens(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_semantic_tokens_response(req_id, doc_ptr, doc_len, format_ptr, lsp_LSP_FORMAT_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, format_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, empty_arr, 2, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; }));
  __tmp = ({ int32_t __tmp = 0; if (lsp_body_contains_rename(body_ptr, content_len) != 0) {   int32_t resp_len = lsp_build_rename_response(req_id, body_ptr, content_len, doc_ptr, doc_len, format_ptr, lsp_LSP_FORMAT_RESP_CAP);
  (void)(({ int32_t __tmp = 0; if (resp_len > 0) {   (void)(lsp_send_response(stdout_fd, format_ptr, resp_len));
 } else {   int32_t fallback_len = lsp_build_response_with_result(req_id, null_val, 4, out_buf, 4096);
  __tmp = ({ int32_t __tmp = 0; if (fallback_len > 0) {   (void)(lsp_send_response(stdout_fd, out_buf, fallback_len));
 } else (__tmp = 0) ; __tmp; });
 } ; __tmp; }));
  (void)(lsp_io_lsp_free(body_ptr));
  continue;
 } else (__tmp = 0) ; __tmp; });
 } else (__tmp = 0) ; __tmp; }));
    (void)(lsp_io_lsp_free(body_ptr));
  }
  (void)(lsp_io_lsp_free(diag_ptr));
  (void)(lsp_io_lsp_free(ref_ptr));
  (void)(lsp_io_lsp_free(format_ptr));
  return 0;
}
