// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// G-02f-301/310/456 / P2 runtime R10 entry → R2 full。
// Runtime entry helpers (explain/smoke/fmt/build); G.9 English; body authoritative.
//   fmt_report_no_files / run_compiler_c / build_build_x。
// Runtime entry helpers (explain/smoke/fmt/build); G.9 English; body authoritative.
// Runtime entry helpers (explain/smoke/fmt/build); G.9 English; body authoritative.
// Runtime entry helpers (explain/smoke/fmt/build); G.9 English; body authoritative.

export extern "C" function diag_json_enabled(): i32;
/* wave227 G.7: env lookup via public pure thin link_abi_getenv (wave222 → _impl host getenv);
 * not raw libc getenv. Cap residual host getenv stays only link_abi_getenv_impl. */
export extern "C" function link_abi_getenv(name: *u8): *u8;
/* wave226 G.7: shell make via public pure thin link_abi_system (wave224 → _impl host system);
 * not raw libc system. Cap residual host system stays only link_abi_system_impl. */
export extern "C" function link_abi_system(cmd: *u8): i32;
export extern "C" function strcmp(a: *u8, b: *u8): i32;
/** Cap residual 9.1.8: raw write via Cap abstraction xlang_sys_write.
 * @param fd i32 file descriptor
 * @param buf *u8 buffer pointer
 * @param n usize bytes to write
 * @return isize bytes written or negative on error
 */
export extern "C" function xlang_sys_write(fd: i32, buf: *u8, n: usize): isize;
export extern "C" function driver_get_argv_i(argc: i32, argv: **u8, i: i32, buf: *u8, max: i32): i32;
export extern "C" function diag_report_with_code(
  file: *u8, line: i32, col: i32, kind: *u8, code: *u8, msg: *u8, detail: *u8): void;
export extern "C" function diag_code_is_known(code: *u8): i32;
export extern "C" function diag_code_suggest(code: *u8, buf: *u8, cap: usize): *u8;
export extern "C" function diag_print_code_table(out: *u8): void;
export extern "C" function diag_print_code_explain(out: *u8, code: *u8): void;
export extern "C" function diag_print_known_codes(out: *u8): void;
export extern "C" function driver_run_fmt(argc: i32, argv: **u8): i32;
export extern "C" function main_run_compiler_c(argc: i32, argv: *u8): i32;
export extern "C" function driver_stdio_stdout(): *u8;
export extern "C" function driver_stdio_stderr(): *u8;
export extern "C" function driver_entry_ab_slot(): *u8;
export extern "C" function driver_entry_code_slot(): *u8;
export extern "C" function driver_entry_suggest_slot(): *u8;
export extern "C" function driver_entry_msg_slot(): *u8;
export extern "C" function driver_entry_tmp_slot(): *u8;
export extern "C" function driver_entry_tmp2_slot(): *u8;
export extern "C" function driver_entry_fmt_argv_slot(): **u8;

/** Internal function `rt_entry_strlen`.
 * Implements `rt_entry_strlen`.
 * @param s *u8
 * @return i32
 */
function rt_entry_strlen(s: *u8): i32 {
  let i: i32 = 0;
  if (s == 0 as *u8) {
    return 0;
  }
  while (i < 4096) {
    if (s[i] == 0) {
      return i;
    }
    i = i + 1;
  }
  return i;
}

/** Internal function `rt_entry_append`.
 * Implements `rt_entry_append`.
 * @param dst *u8
 * @param cap i32
 * @param src *u8
 * @return void
 */
function rt_entry_append(dst: *u8, cap: i32, src: *u8): void {
  let n: i32 = 0;
  let i: i32 = 0;
  let c: u8 = 0;
  if (dst == 0 as *u8) {
    return;
  }
  if (cap <= 0) {
    return;
  }
  if (src == 0 as *u8) {
    return;
  }
  n = rt_entry_strlen(dst);
  while (n + 1 < cap) {
    c = src[i];
    if (c == 0) {
      break;
    }
    dst[n] = c;
    n = n + 1;
    i = i + 1;
  }
  if (n < cap) {
    dst[n] = 0;
  } else {
    dst[cap - 1] = 0;
  }
}

/** Internal function `rt_entry_append_i32`.
 * Implements `rt_entry_append_i32`.
 * @param dst *u8
 * @param cap i32
 * @param v i32
 * @return void
 */
function rt_entry_append_i32(dst: *u8, cap: i32, v: i32): void {
  let dig: *u8 = 0 as *u8;
  let n: i32 = v;
  let i: i32 = 0;
  let j: i32 = 0;
  let neg: i32 = 0;
  let a: u8 = 0;
  /* See signature and body for contracts. */
  unsafe {
    dig = driver_entry_tmp2_slot();
  }
  if (dig == 0 as *u8) {
    return;
  }
  if (n == 0) {
    dig[0] = 48;
    dig[1] = 0;
    rt_entry_append(dst, cap, dig);
    return;
  }
  if (n < 0) {
    neg = 1;
    n = 0 - n;
  }
  while (n > 0) {
    if (i >= 15) {
      break;
    }
    dig[i] = (48 + (n - (n / 10) * 10)) as u8;
    n = n / 10;
    i = i + 1;
  }
  if (neg != 0) {
    if (i < 15) {
      dig[i] = 45;
      i = i + 1;
    }
  }
  j = 0;
  while (j < i / 2) {
    a = dig[j];
    dig[j] = dig[i - 1 - j];
    dig[i - 1 - j] = a;
    j = j + 1;
  }
  dig[i] = 0;
  rt_entry_append(dst, cap, dig);
}

/** Internal function `rt_entry_write_str`.
 * Write path helper `rt_entry_write_str`.
 * @param fd i32
 * @param s *u8
 * @return void
 */
function rt_entry_write_str(fd: i32, s: *u8): void {
  let n: i32 = 0;
  if (s == 0 as *u8) {
    return;
  }
  n = rt_entry_strlen(s);
  if (n <= 0) {
    return;
  }
  unsafe {
    xlang_sys_write(fd, s, n as usize);
  }
}

/** Internal function `rt_entry_write_nl`.
 * Write path helper `rt_entry_write_nl`.
 * @param fd i32
 * @return void
 */
function rt_entry_write_nl(fd: i32): void {
  let tmp: *u8 = 0 as *u8;
  unsafe {
    tmp = driver_entry_tmp_slot();
  }
  if (tmp == 0 as *u8) {
    return;
  }
  tmp[0] = 10;
  tmp[1] = 0;
  rt_entry_write_str(fd, tmp);
}

/** Internal function `rt_entry_write_i32`.
 * Write path helper `rt_entry_write_i32`.
 * @param fd i32
 * @param v i32
 * @return void
 */
function rt_entry_write_i32(fd: i32, v: i32): void {
  let tmp: *u8 = 0 as *u8;
  unsafe {
    tmp = driver_entry_tmp_slot();
  }
  if (tmp == 0 as *u8) {
    return;
  }
  tmp[0] = 0;
  rt_entry_append_i32(tmp, 16, v);
  rt_entry_write_str(fd, tmp);
}

/** Internal function `rt_entry_is_explain_eq`.
 * Implements `rt_entry_is_explain_eq`.
 * @param s *u8
 * @return i32
 */
function rt_entry_is_explain_eq(s: *u8): i32 {
  if (s == 0 as *u8) {
    return 0;
  }
  if (s[0] != 45) {
    return 0;
  }
  if (s[1] != 45) {
    return 0;
  }
  if (s[2] != 101) {
    return 0;
  }
  if (s[3] != 120) {
    return 0;
  }
  if (s[4] != 112) {
    return 0;
  }
  if (s[5] != 108) {
    return 0;
  }
  if (s[6] != 97) {
    return 0;
  }
  if (s[7] != 105) {
    return 0;
  }
  if (s[8] != 110) {
    return 0;
  }
  if (s[9] != 61) {
    return 0;
  }
  if (s[10] == 0) {
    return 0;
  }
  return 1;
}

/** Internal function `rt_entry_explain_mode`.
 * Implements `rt_entry_explain_mode`.
 * @param ab *u8
 * @return i32
 */
function rt_entry_explain_mode(ab: *u8): i32 {
  if (ab == 0 as *u8) {
    return 0;
  }
  unsafe {
    if (strcmp(ab, "explain") == 0) {
      return 1;
    }
  }
  unsafe {
    if (strcmp(ab, "--explain") == 0) {
      return 1;
    }
  }
  if (rt_entry_is_explain_eq(ab) != 0) {
    return 2;
  }
  return 0;
}

/** Internal function `rt_entry_explain_usage_err`.
 * Implements `rt_entry_explain_usage_err`.
 * @return i32
 */
function rt_entry_explain_usage_err(): i32 {
  let msg: *u8 = 0 as *u8;
  let kind: *u8 = 0 as *u8;
  let dcode: *u8 = 0 as *u8;
  unsafe {
    msg = driver_entry_msg_slot();
  }
  if (msg == 0 as *u8) {
    return 1;
  }
  kind = "usage error";
  dcode = "ARG001";
  msg[0] = 0;
  rt_entry_append(msg, 256, "--explain requires a diagnostic code (example: xlang --explain P001; use --list to see all)");
  unsafe {
    diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
  }
  return 1;
}

/** Internal function `rt_entry_explain_list`.
 * Implements `rt_entry_explain_list`.
 * @return i32
 */
function rt_entry_explain_list(): i32 {
  let out: *u8 = 0 as *u8;
  unsafe {
    out = driver_stdio_stdout();
    if (out != 0 as *u8) {
      diag_print_code_table(out);
    }
  }
  return 0;
}

/** Internal function `rt_entry_explain_unknown`.
 * Implements `rt_entry_explain_unknown`.
 * @param code *u8
 * @return i32
 */
function rt_entry_explain_unknown(code: *u8): i32 {
  let msg: *u8 = 0 as *u8;
  let sug_buf: *u8 = 0 as *u8;
  let sug: *u8 = 0 as *u8;
  let err: *u8 = 0 as *u8;
  let kind: *u8 = 0 as *u8;
  let dcode: *u8 = 0 as *u8;
  unsafe {
    msg = driver_entry_msg_slot();
    sug_buf = driver_entry_suggest_slot();
  }
  if (msg == 0 as *u8) {
    return 1;
  }
  kind = "argument error";
  dcode = "ARG002";
  msg[0] = 0;
  rt_entry_append(msg, 256, "unknown diagnostic code '");
  rt_entry_append(msg, 256, code);
  rt_entry_append(msg, 256, "'");
  unsafe {
    diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
  }
  if (sug_buf != 0 as *u8) {
    unsafe {
      sug = diag_code_suggest(code, sug_buf, 16 as usize);
    }
  }
  if (sug != 0 as *u8) {
    msg[0] = 0;
    rt_entry_append(msg, 256, "did you mean '");
    rt_entry_append(msg, 256, sug);
    rt_entry_append(msg, 256, "'?");
    kind = "help";
    unsafe {
      diag_report_with_code(0 as *u8, 0, 0, kind, 0 as *u8, msg, 0 as *u8);
    }
  }
  msg[0] = 0;
  rt_entry_append(msg, 256, "use `xlang --explain P001` or `xlang explain P001`; use `--list` to see all codes");
  kind = "note";
  unsafe {
    diag_report_with_code(0 as *u8, 0, 0, kind, 0 as *u8, msg, 0 as *u8);
  }
  rt_entry_write_str(2, "note: ");
  unsafe {
    err = driver_stdio_stderr();
    if (err != 0 as *u8) {
      diag_print_known_codes(err);
    }
  }
  return 1;
}

/** Internal function `rt_entry_explain_known`.
 * Implements `rt_entry_explain_known`.
 * @param code *u8
 * @return i32
 */
function rt_entry_explain_known(code: *u8): i32 {
  let out: *u8 = 0 as *u8;
  unsafe {
    out = driver_stdio_stdout();
    if (out != 0 as *u8) {
      diag_print_code_explain(out, code);
    }
  }
  return 0;
}

/** Exported function `runtime_try_handle_explain_cli`.
 * Implements `runtime_try_handle_explain_cli`.
 * @param argc i32
 * @param argv **u8
 * @return i32
 */
#[no_mangle]
export function runtime_try_handle_explain_cli(argc: i32, argv: **u8): i32 {
  let ab: *u8 = 0 as *u8;
  let code_buf: *u8 = 0 as *u8;
  let code: *u8 = 0 as *u8;
  let ln: i32 = 0;
  let mode: i32 = 0;
  let known: i32 = 0;
  let is_list: i32 = 0;
  if (argc < 2) {
    return 0 - 1;
  }
  /* See signature and body for contracts. */
  if ((argv as *u8) == 0 as *u8) {
    return 0 - 1;
  }
  unsafe {
    ab = driver_entry_ab_slot();
    code_buf = driver_entry_code_slot();
  }
  if (ab == 0 as *u8) {
    return 0 - 1;
  }
  unsafe {
    ln = driver_get_argv_i(argc, argv, 1, ab, 256);
  }
  if (ln < 0) {
    return 0 - 1;
  }
  mode = rt_entry_explain_mode(ab);
  if (mode == 0) {
    return 0 - 1;
  }
  code = 0 as *u8;
  if (mode == 2) {
    code = &ab[10];
  } else {
    if (argc >= 3) {
      if (code_buf != 0 as *u8) {
        unsafe {
          ln = driver_get_argv_i(argc, argv, 2, code_buf, 256);
        }
        if (ln > 0) {
          code = code_buf;
        }
      }
    }
  }
  if (code == 0 as *u8) {
    return rt_entry_explain_usage_err();
  }
  if (code[0] == 0) {
    return rt_entry_explain_usage_err();
  }
  is_list = 0;
  unsafe {
    if (strcmp(code, "list") == 0) {
      is_list = 1;
    }
  }
  if (is_list == 0) {
    unsafe {
      if (strcmp(code, "--list") == 0) {
        is_list = 1;
      }
    }
  }
  if (is_list != 0) {
    return rt_entry_explain_list();
  }
  known = 0;
  unsafe {
    known = diag_code_is_known(code);
  }
  if (known == 0) {
    return rt_entry_explain_unknown(code);
  }
  return rt_entry_explain_known(code);
}

/**
 * Whether smoke diagnostic emission is enabled.
 * True when diag JSON mode is on, or XLANG_SMOKE_DIAG is set to a non-empty value
 * other than ASCII "0".
 * @return i32 — 1 enabled, 0 disabled
 * wave227 G.7: env via public pure thin link_abi_getenv (not raw libc getenv).
 * PLATFORM: SHARED — process env; host residual only link_abi_getenv_impl.
 */
#[no_mangle]
export function xlang_smoke_diag_enabled(): i32 {
  let e: *u8 = 0 as *u8;
  unsafe {
    if (diag_json_enabled() != 0) {
      return 1;
    }
    e = link_abi_getenv("XLANG_SMOKE_DIAG");
  }
  if (e == 0 as *u8) {
    return 0;
  }
  if (e[0] == 0) {
    return 0;
  }
  if (e[0] == 48) {
    return 0;
  }
  return 1;
}

/** Internal function `rt_entry_smoke_write_body`.
 * Write path helper `rt_entry_smoke_write_body`.
 * @param name *u8
 * @param main_final_lit i32
 * @param has_main_body i32
 * @return void
 */
function rt_entry_smoke_write_body(name: *u8, main_final_lit: i32, has_main_body: i32): void {
  if (has_main_body != 0) {
    if (main_final_lit >= 0) {
      rt_entry_write_str(1, "parse OK: ");
      rt_entry_write_str(1, name);
      rt_entry_write_str(1, "(): i32 { ");
      rt_entry_write_i32(1, main_final_lit);
      rt_entry_write_str(1, " }");
      rt_entry_write_nl(1);
    } else {
      rt_entry_write_str(1, "parse OK: ");
      rt_entry_write_str(1, name);
      rt_entry_write_str(1, "(): i32 { expr }");
      rt_entry_write_nl(1);
    }
  } else {
    rt_entry_write_str(1, "parse OK (library module)");
    rt_entry_write_nl(1);
  }
  rt_entry_write_str(1, "typeck OK");
  rt_entry_write_nl(1);
}

/** Internal function `rt_entry_smoke_diag_body`.
 * Implements `rt_entry_smoke_diag_body`.
 * @param name *u8
 * @param main_final_lit i32
 * @param has_main_body i32
 * @return void
 */
function rt_entry_smoke_diag_body(name: *u8, main_final_lit: i32, has_main_body: i32): void {
  let msg: *u8 = 0 as *u8;
  let kind: *u8 = 0 as *u8;
  let dcode: *u8 = 0 as *u8;
  unsafe {
    msg = driver_entry_msg_slot();
  }
  if (msg == 0 as *u8) {
    return;
  }
  kind = "info";
  dcode = "SMOKE001";
  if (has_main_body != 0) {
    if (main_final_lit >= 0) {
      msg[0] = 0;
      rt_entry_append(msg, 256, "parse OK: ");
      rt_entry_append(msg, 256, name);
      rt_entry_append(msg, 256, "(): i32 { ");
      rt_entry_append_i32(msg, 256, main_final_lit);
      rt_entry_append(msg, 256, " }");
      unsafe {
        diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
      }
    } else {
      msg[0] = 0;
      rt_entry_append(msg, 256, "parse OK: ");
      rt_entry_append(msg, 256, name);
      rt_entry_append(msg, 256, "(): i32 { expr }");
      unsafe {
        diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
      }
    }
  } else {
    msg[0] = 0;
    rt_entry_append(msg, 256, "parse OK (library module)");
    unsafe {
      diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
    }
  }
  dcode = "SMOKE002";
  msg[0] = 0;
  rt_entry_append(msg, 256, "typeck OK");
  unsafe {
    diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
  }
}

/* See signature and body for contracts. */
#[no_mangle]
export function driver_emit_legacy_smoke_summary_stdout(
  main_name: *u8, main_final_lit: i32, has_main_body: i32
): void {
  let name: *u8 = 0 as *u8;
  if (main_name != 0 as *u8) {
    name = main_name;
  } else {
    name = "?";
  }
  rt_entry_smoke_write_body(name, main_final_lit, has_main_body);
  if (xlang_smoke_diag_enabled() == 0) {
    return;
  }
  rt_entry_smoke_diag_body(name, main_final_lit, has_main_body);
}

/** Exported function `driver_fmt_report_no_files`.
 * Implements `driver_fmt_report_no_files`.
 * @return i32
 */
#[no_mangle]
export function driver_fmt_report_no_files(): i32 {
  /* See signature and body for contracts. */
  unsafe {
    return driver_run_fmt(2, driver_entry_fmt_argv_slot());
  }
  return 1;
}

/** Exported function `run_compiler_c`.
 * Implements `run_compiler_c`.
 * @param argc i32
 * @param argv **u8
 * @return i32
 */
#[no_mangle]
export function run_compiler_c(argc: i32, argv: **u8): i32 {
  unsafe {
    return main_run_compiler_c(argc, argv as *u8);
  }
  return 1;
}

/**
 * See signature and body for params/returns/contracts.
 * See signature and body for params/returns/contracts.
 */
#[no_mangle]
export function driver_build_build_x(): i32 {
  let rc: i32 = 0;
  let msg: *u8 = 0 as *u8;
  let kind: *u8 = 0 as *u8;
  let dcode: *u8 = 0 as *u8;
  unsafe {
    msg = driver_entry_msg_slot();
    // wave226 G.7: public pure thin link_abi_system (not raw libc system).
    rc = link_abi_system("cd compiler && make -s build-tool 2>&1");
  }
  if (rc != 0) {
    kind = "build error";
    dcode = "BLD001";
    if (msg != 0 as *u8) {
      msg[0] = 0;
      rt_entry_append(msg, 256, "make build-tool failed (exit ");
      rt_entry_append_i32(msg, 256, rc);
      rt_entry_append(msg, 256, ")");
      unsafe {
        diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
      }
    }
    return 1;
  }
  unsafe {
    // wave226 G.7: public pure thin link_abi_system (not raw libc system).
    rc = link_abi_system("cd compiler && ./build_tool ./xlang 2>&1");
  }
  if (rc != 0) {
    kind = "build error";
    dcode = "BLD001";
    if (msg != 0 as *u8) {
      msg[0] = 0;
      rt_entry_append(msg, 256, "build_tool failed (exit ");
      rt_entry_append_i32(msg, 256, rc);
      rt_entry_append(msg, 256, ")");
      unsafe {
        diag_report_with_code(0 as *u8, 0, 0, kind, dcode, msg, 0 as *u8);
      }
    }
    return 1;
  }
  return 0;
}
