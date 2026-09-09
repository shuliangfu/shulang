// Copyright (C) 2026 ShuLiangfu <admin@shuliangfu.com>
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// Full text: LICENSE.Apache-2.0

// See implementation.
//
// See implementation.
// See implementation.
//
// See implementation.
// See implementation.
// - core.mem：mem_zero、mem_compare
// See implementation.

const mem = import("core.mem");
const types = import("core.types");

/** Exported function `zstd_stream_state_bytes`.
 * Implements `zstd_stream_state_bytes`.
 * @return i32
 */
export function zstd_stream_state_bytes(): i32 {
  /* See implementation. */
  return 32;
}

/** Exported function `zstd_stream_hdr_bytes`.
 * Implements `zstd_stream_hdr_bytes`.
 * @return i32
 */
export function zstd_stream_hdr_bytes(): i32 {
  return 16;
}

/* See implementation. */
export const XLANG_ZSTD_STREAM_MAGIC: u32 = 0x5a535452;

/* See implementation. */
export const ZSTD_CLEVEL_DEFAULT: i32 = 3;

/* See implementation. */
export const ZSTD_c_compressionLevel: i32 = 100;

/* See implementation. */
export const ZSTD_e_continue: i32 = 0;
export const ZSTD_e_end: i32 = 2;

/* See implementation. */
allow(padding) struct ZstdStreamHdr {
  magic: u32;
  mode: i32;
  ended: i32;
  inited: i32;
}

/* See implementation. */
allow(padding) struct ZstdStream {
  hdr: ZstdStreamHdr;
  cctx: *u8;
  dctx: *u8;
}

/* See implementation. */
allow(padding) struct ZstdInBuffer {
  src: *u8;
  size: usize;
  pos: usize;
}

/* See implementation. */
allow(padding) struct ZstdOutBuffer {
  dst: *u8;
  size: usize;
  pos: usize;
}

/* See implementation. */
extern function ZSTD_compress(dst: *u8, dstCapacity: usize, src: *u8, srcSize: usize, compressionLevel: i32): usize;

/* See implementation. */
extern function ZSTD_decompress(dst: *u8, dstCapacity: usize, src: *u8, compressedSize: usize): usize;

/* See implementation. */
extern function ZSTD_isError(code: usize): u32;

/* See implementation. */
extern function ZSTD_createCCtx(): *u8;
extern function ZSTD_freeCCtx(cctx: *u8): usize;
extern function ZSTD_createDCtx(): *u8;
extern function ZSTD_freeDCtx(dctx: *u8): usize;

/* See implementation. */
extern function ZSTD_CCtx_setParameter(cctx: *u8, param: i32, value: i32): usize;

/* See implementation. */
extern function ZSTD_compressStream2(cctx: *u8, output: *ZstdOutBuffer, input: *ZstdInBuffer, endOp: i32): usize;

/* See implementation. */
extern function ZSTD_decompressStream(dctx: *u8, output: *ZstdOutBuffer, input: *ZstdInBuffer): usize;

/* See implementation. */
let xlang_compress_zstd_marker: u8 = 1;

/**
 * See implementation.
 */
export function xlang_zstd_stream_cast(state: *u8, state_cap: i32): *ZstdStream {
  // PLATFORM: SHARED — cap is 32; do not call zstd_stream_state_bytes()
  // (co-emitted short name aliases std.compress facade → recurse).
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return 0 as *ZstdStream;
  }
  let s: *ZstdStream = state as *ZstdStream;
  if (s.hdr.magic != XLANG_ZSTD_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0 as *ZstdStream;
  }
  return s;
}

/**
 * See implementation.
 */
export function compress_zstd_compress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let n: usize = 0;
  unsafe { n = ZSTD_compress(out, out_cap, in, in_len, ZSTD_CLEVEL_DEFAULT); }
  let is_err: u32 = 0;
  unsafe { is_err = ZSTD_isError(n); }
  if (is_err != 0) {
    return -1;
  }
  return n as i32;
}

/**
 * See implementation.
 */
export function compress_zstd_decompress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let n: usize = 0;
  unsafe { n = ZSTD_decompress(out, out_cap, in, in_len); }
  let is_err: u32 = 0;
  unsafe { is_err = ZSTD_isError(n); }
  if (is_err != 0) {
    return -1;
  }
  return n as i32;
}

/**
 * See implementation.
 */
export function compress_zstd_available_c(): i32 {
  return 1;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_state_bytes_c(): i32 {
  // PLATFORM: SHARED — literal cap (same as zstd_stream_state_bytes). Co-emitted
  // short-name call aliases the facade and recurses (Ubuntu xlang build).
  return 32;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_init_compress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *ZstdStream = state as *ZstdStream;
  s.hdr.magic = XLANG_ZSTD_STREAM_MAGIC;
  s.hdr.mode = 0;
  unsafe { s.cctx = ZSTD_createCCtx(); }
  if (s.cctx == 0) {
    return -1;
  }
  let set_ret: usize = 0;
  unsafe { set_ret = ZSTD_CCtx_setParameter(s.cctx, ZSTD_c_compressionLevel, ZSTD_CLEVEL_DEFAULT); }
  let is_err: u32 = 0;
  unsafe { is_err = ZSTD_isError(set_ret); }
  if (is_err != 0) {
    unsafe { ZSTD_freeCCtx(s.cctx); }
    s.cctx = 0 as *u8;
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_init_decompress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *ZstdStream = state as *ZstdStream;
  s.hdr.magic = XLANG_ZSTD_STREAM_MAGIC;
  s.hdr.mode = 1;
  unsafe { s.dctx = ZSTD_createDCtx(); }
  if (s.dctx == 0) {
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_compress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, is_last: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *ZstdStream = xlang_zstd_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 0 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let inbuf: ZstdInBuffer;
  let outbuf: ZstdOutBuffer;
  inbuf.src = in;
  if (in_len > 0) {
    inbuf.size = in_len as usize;
  } else {
    inbuf.size = 0;
  }
  inbuf.pos = 0;
  outbuf.dst = out;
  outbuf.size = out_cap as usize;
  outbuf.pos = 0;
  let mode: i32 = ZSTD_e_continue;
  if (is_last != 0) {
    mode = ZSTD_e_end;
  }
  let remaining: usize = 0;
  unsafe { remaining = ZSTD_compressStream2(s.cctx, &outbuf, &inbuf, mode); }
  let is_err: u32 = 0;
  unsafe { is_err = ZSTD_isError(remaining); }
  if (is_err != 0) {
    return -1;
  }
  if (in_consumed != 0) {
    in_consumed[0] = inbuf.pos as i32;
  }
  if (mode == ZSTD_e_end && remaining == 0) {
    s.hdr.ended = 1;
  }
  return outbuf.pos as i32;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_decompress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *ZstdStream = xlang_zstd_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 1 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let inbuf: ZstdInBuffer;
  let outbuf: ZstdOutBuffer;
  inbuf.src = in;
  if (in_len > 0) {
    inbuf.size = in_len as usize;
  } else {
    inbuf.size = 0;
  }
  inbuf.pos = 0;
  outbuf.dst = out;
  outbuf.size = out_cap as usize;
  outbuf.pos = 0;
  let ret: usize = 0;
  unsafe { ret = ZSTD_decompressStream(s.dctx, &outbuf, &inbuf); }
  let is_err: u32 = 0;
  unsafe { is_err = ZSTD_isError(ret); }
  if (is_err != 0) {
    return -1;
  }
  if (in_consumed != 0) {
    in_consumed[0] = inbuf.pos as i32;
  }
  if (ret == 0) {
    s.hdr.ended = 1;
  }
  return outbuf.pos as i32;
}

/**
 * See implementation.
 */
export function compress_zstd_stream_end_c(state: *u8, state_cap: i32): i32 {
  // PLATFORM: SHARED — hdr cap is 16; avoid co-emit short-name alias.
  let hdr_need: i32 = 16;
  if (state == 0 || state_cap < hdr_need) {
    return 0;
  }
  let s: *ZstdStream = state as *ZstdStream;
  if (s.hdr.magic != XLANG_ZSTD_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0;
  }
  if (s.cctx != 0) {
    unsafe { ZSTD_freeCCtx(s.cctx); }
    s.cctx = 0 as *u8;
  }
  if (s.dctx != 0) {
    unsafe { ZSTD_freeDCtx(s.dctx); }
    s.dctx = 0 as *u8;
  }
  s.hdr.inited = 0;
  return 0;
}

/**
 * See implementation.
 */
export function compress_zstd_smoke_c(): i32 {
  let inp: u8[5] = [104, 101, 108, 108, 111];
  let out: u8[64] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let dec: u8[64] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let st_c: u8[512] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let st_d: u8[512] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let cap_c: i32 = 0;
  let cap_d: i32 = 0;
  let n: i32 = 0;
  let m: i32 = 0;
  let consumed: i32 = 0;
  if (compress_zstd_available_c() == 0) {
    return 0;
  }
  n = compress_zstd_compress_c(&inp[0], 5, &out[0], 64);
  if (n <= 0) {
    return 1;
  }
  m = compress_zstd_decompress_c(&out[0], n, &dec[0], 64);
  if (m != 5 || mem.mem_compare(&dec[0], &inp[0], 5) != 0) {
    return 2;
  }
  cap_c = compress_zstd_stream_state_bytes_c();
  cap_d = compress_zstd_stream_state_bytes_c();
  if (compress_zstd_stream_init_compress_c(&st_c[0], cap_c) != 0) {
    return 3;
  }
  consumed = 0;
  n = compress_zstd_stream_compress_c(&st_c[0], cap_c, &inp[0], 5, &out[0], 64, 1, &consumed);
  if (n <= 0) {
    compress_zstd_stream_end_c(&st_c[0], cap_c);
    return 4;
  }
  compress_zstd_stream_end_c(&st_c[0], cap_c);
  if (compress_zstd_stream_init_decompress_c(&st_d[0], cap_d) != 0) {
    return 5;
  }
  consumed = 0;
  m = compress_zstd_stream_decompress_c(&st_d[0], cap_d, &out[0], n, &dec[0], 64, &consumed);
  compress_zstd_stream_end_c(&st_d[0], cap_d);
  if (m != 5 || mem.mem_compare(&dec[0], &inp[0], 5) != 0) {
    return 6;
  }
  return 0;
}
