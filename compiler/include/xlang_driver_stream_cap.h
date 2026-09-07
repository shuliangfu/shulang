/**
 * xlang_driver_stream_cap.h — Cap residual 9.7.1: opaque stream face → fd-handle.
 *
 * File role: single authority for the fd-handle encoding shared by every
 * producer/consumer of the opaque `uint8_t *` stream face
 * (xlang_driver_{fputs,fclose,fwrite,fopen_write,fopen_wb,fdopen_wb,stdout_ptr,
 * stderr_ptr,fflush_stdout}_opaque and the diag micro-ABI diag_stderr/diag_io_*).
 *
 * Background: the face used to wrap libc FILE* (opaque pointer to stdio state),
 * which forced every provider to keep fprintf/fwrite/fclose residuals. 9.7.1
 * converts the face INTERNALLY to raw fd I/O (Cap authorities in
 * xlang_io_cap.h / xlang_proc_cap.h). The face signatures stay `uint8_t *`
 * pointers, so .x consumers (which cannot name FILE*) are source-compatible.
 *
 * Encoding: handle = (uint8_t *)(intptr_t)(fd + 1); NULL is invalid.
 *   - +1 offset keeps NULL distinct from fd 0 (stdin).
 *   - Encoding is injective, so pointer identity checks in .x consumers
 *     (e.g. driver_asm_fp_is_stdout comparing against xlang_driver_stdout_ptr)
 *     keep working unchanged.
 *   - std fds: 0 = stdin, 1 = stdout, 2 = stderr. Handles for fd <= 2 MUST NOT
 *     be closed (see xlang_driver_handle_close); producers of stdout/stderr
 *     identity return the encoded handle instead of a libc FILE*.
 *
 * Consumers: compiler seeds (runtime_driver_abi.from_x.c, diag.from_x.c,
 * rt_preamble.from_x.c, runtime_driver_strict_glue_stubs.from_x.c, rt_run_*)
 * and the host-cc prologue emitters (scripts/ensure_host_cc_seed_o.sh,
 * scripts/g05_ensure_relink_prereqs.sh) which embed the face bodies into
 * generated C. Keep all copies semantically identical (G.7: one authority,
 * twins allowed only as build-phase mirrors of THIS header's semantics).
 *
 * PLATFORM: SHARED — encoding is platform-independent; the underlying
 * write/open/close go through the xlang_io_cap.h / xlang_proc_cap.h authorities.
 */

#ifndef XLANG_DRIVER_STREAM_CAP_H
#define XLANG_DRIVER_STREAM_CAP_H

#include <stdint.h>

#include "xlang_io_cap.h"
#include "xlang_proc_cap.h"

/**
 * Encode a raw fd into an opaque stream handle.
 * @param fd non-negative file descriptor (0/1/2 = std streams)
 * @return opaque handle, never NULL for fd >= 0
 * PLATFORM: SHARED
 */
static inline uint8_t *xlang_driver_handle_from_fd(int fd) {
  return (uint8_t *)(intptr_t)(fd + 1);
}

/**
 * Decode an opaque stream handle into its raw fd.
 * @param handle handle previously produced by xlang_driver_handle_from_fd
 *               (or any NULL — invalid)
 * @return file descriptor, or -1 when handle is NULL
 * PLATFORM: SHARED
 */
static inline int xlang_driver_handle_to_fd(uint8_t *handle) {
  return handle ? (int)(intptr_t)handle - 1 : -1;
}

/**
 * Close a stream handle via the Cap close authority.
 * std fds (0/1/2) are intentionally NOT closed: the face never closes the
 * process std streams (callers guard stdout explicitly, e.g.
 * driver_asm_fclose_asm_out / driver_parsed_fclose), and a stray close of
 * fd 1/2 would kill all later compiler output.
 * @param handle opaque stream handle (NULL allowed)
 * @return 0 on success or skipped std handle, 1 on close failure
 * PLATFORM: SHARED
 */
static inline int xlang_driver_handle_close(uint8_t *handle) {
  int fd = xlang_driver_handle_to_fd(handle);
  if (fd <= 2)
    return 0;
  return xlang_proc_close_fd(fd) == 0 ? 0 : 1;
}

#endif /* XLANG_DRIVER_STREAM_CAP_H */
