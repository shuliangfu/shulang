// Stage 10 (10.1.4) slice2: bare `extern "C"` dlsym → Cap → Cap CALL.
// No std.dynlib; proves raw FFI + 10.3 Cap compose.
// RTLD_DEFAULT (null handle): resolve already-linked libc `atoi`.
// PLATFORM: SHARED (emit) / POSIX (dlfcn).

/**
 * POSIX dlsym — C ABI import (libdl / libc).
 * @param handle *u8 — library handle, or null for RTLD_DEFAULT
 * @param symbol *u8 — NUL-terminated symbol name
 * @return *u8 — Cap fn-ptr, or null on failure
 */
extern "C" function dlsym(handle: *u8, symbol: *u8): *u8;

/**
 * libc atoi via Cap CALL after dlsym(RTLD_DEFAULT, "atoi").
 * Opaque Cap→TYPE_FN only via `as function` (slice16).
 * @return i32 — 42 on success; 2 = dlsym null; 3 = wrong atoi
 * PLATFORM: SHARED / POSIX
 */
function main(): i32 {
  let name: u8[8] = [97, 116, 111, 105, 0, 0, 0, 0]; /* "atoi" */
  let digits: u8[4] = [52, 50, 0, 0]; /* "42" */
  let sym: *u8 = 0 as *u8;
  let v: i32 = 0;
  unsafe {
    sym = dlsym(0 as *u8, &name[0]);
    if (sym == 0 as *u8) {
      /* Darwin / macOS RTLD_DEFAULT is ((void*)-2) */
      sym = dlsym((0 - 2) as *u8, &name[0]);
    }
  }
  if (sym == 0 as *u8) {
    return 2;
  }
  let f: function(*u8): i32 = sym as function(*u8): i32;
  unsafe {
    v = f(&digits[0]);
  }
  if (v != 42) {
    return 3;
  }
  return 42;
}
