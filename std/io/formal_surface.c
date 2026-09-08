/* PLATFORM: SHARED — pure-asm formal vehicle for std.io context-timeout faces.
 *
 * Why C face: pure-asm monofile skips whole std.io emit (pipeline/bridge); product
 * user.o CALLs std_io_timeout_from_ctx / read_ctx / write_ctx as U. Always-linked
 * runtime_asm_io_stubs.o cannot host these: they U-import std.context / std.error
 * and would break plain run-io when --gc-sections is weak.
 *
 * Authority body ≡ std/io/mod.x (IO_CTX_MS_CANCELLED=-1, EXPIRED=-2;
 * cancelled/expired → std_error_io_err_*). Context ABI = single i64 handle.
 * Forwards live I/O to std_io_read / std_io_write (stubs always on product plan).
 *
 * G.7: single formal vehicle std/io/io.o (formal_mod kind=c_face).
 * formal_mod kind=c_face.
 */
#include <stdint.h>
#include <stddef.h>

typedef struct std_context_Context {
  int64_t handle;
} std_context_Context;

extern int32_t std_context_is_cancelled(std_context_Context ctx);
extern int64_t std_context_remaining_ns(std_context_Context ctx);
extern int64_t std_context_deadline_ns(std_context_Context ctx);
extern int32_t std_error_io_err_cancelled(void);
extern int32_t std_error_io_err_timeout(void);
extern int32_t std_io_read(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);
extern int32_t std_io_write(size_t handle, uint8_t *ptr, size_t len, uint32_t timeout_ms);

enum {
  STD_IO_CTX_MS_CANCELLED = -1,
  STD_IO_CTX_MS_EXPIRED = -2
};

int32_t std_io_timeout_from_ctx(std_context_Context ctx) {
  int64_t rem;
  int64_t dl;
  int64_t ms;
  if (std_context_is_cancelled(ctx) != 0)
    return (int32_t)STD_IO_CTX_MS_CANCELLED;
  rem = std_context_remaining_ns(ctx);
  dl = std_context_deadline_ns(ctx);
  if (dl > 0 && rem <= 0)
    return (int32_t)STD_IO_CTX_MS_EXPIRED;
  if (rem <= 0)
    return 0;
  ms = rem / 1000000;
  if (ms <= 0)
    return 1;
  if (ms > 2147483647)
    return 2147483647;
  return (int32_t)ms;
}

int32_t std_io_read_ctx(size_t handle, uint8_t *ptr, size_t len, std_context_Context ctx) {
  int32_t tm = std_io_timeout_from_ctx(ctx);
  if (tm == (int32_t)STD_IO_CTX_MS_CANCELLED)
    return std_error_io_err_cancelled();
  if (tm == (int32_t)STD_IO_CTX_MS_EXPIRED)
    return std_error_io_err_timeout();
  return std_io_read(handle, ptr, len, (uint32_t)tm);
}

int32_t std_io_write_ctx(size_t handle, uint8_t *ptr, size_t len, std_context_Context ctx) {
  int32_t tm = std_io_timeout_from_ctx(ctx);
  if (tm == (int32_t)STD_IO_CTX_MS_CANCELLED)
    return std_error_io_err_cancelled();
  if (tm == (int32_t)STD_IO_CTX_MS_EXPIRED)
    return std_error_io_err_timeout();
  return std_io_write(handle, ptr, len, (uint32_t)tm);
}
