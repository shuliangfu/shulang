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
// - libz：deflateInit2/inflateInit2、deflate/inflate、deflateEnd/inflateEnd
// - core.mem：mem_zero
// See implementation.

const mem = import("core.mem");
const types = import("core.types");

/** Exported function `gzip_stream_state_bytes`.
 * Implements `gzip_stream_state_bytes`.
 * @return i32
 */
export function gzip_stream_state_bytes(): i32 {
  /* See implementation. */
  return 128;
}

/** Exported function `gzip_stream_hdr_bytes`.
 * Implements `gzip_stream_hdr_bytes`.
 * @return i32
 */
export function gzip_stream_hdr_bytes(): i32 {
  return 16;
}

/* See implementation. */
export const XLANG_GZIP_STREAM_MAGIC: u32 = 0x475a5354;

/* See implementation. */
export const GZIP_WBITS: i32 = 31;

/* See implementation. */
export const Z_OK: i32 = 0;
/* See implementation. */
export const Z_STREAM_END: i32 = 1;
/* See implementation. */
export const Z_NO_FLUSH: i32 = 0;
/* See implementation. */
export const Z_FINISH: i32 = 4;
/* See implementation. */
export const Z_DEFLATED: i32 = 8;
/* See implementation. */
export const Z_DEFAULT_COMPRESSION: i32 = -1;
/* See implementation. */
export const Z_DEFAULT_STRATEGY: i32 = 0;
/* See implementation. */
export const Z_BUF_ERROR: i32 = -5;

/* See implementation. */
allow(padding) struct GzipStreamHdr {
  magic: u32;
  mode: i32;
  ended: i32;
  inited: i32;
}

/* See implementation. */
allow(padding) struct ZStream {
  next_in: *u8;
  avail_in: u32;
  total_in: u64;
  next_out: *u8;
  avail_out: u32;
  total_out: u64;
  msg: *u8;
  state: *u8;
  zalloc: usize;
  zfree: usize;
  opaque: *u8;
  data_type: i32;
  adler: u64;
  reserved: u64;
}

/* See implementation. */
allow(padding) struct GzipStream {
  hdr: GzipStreamHdr;
  strm: ZStream;
}

/* See implementation. */
extern function deflateInit2(strm: *ZStream, level: i32, method: i32, windowBits: i32, memLevel: i32, strategy: i32): i32;
/* See implementation. */
extern function deflate(strm: *ZStream, flush: i32): i32;
/* See implementation. */
extern function deflateEnd(strm: *ZStream): i32;
/* See implementation. */
extern function inflateInit2(strm: *ZStream, windowBits: i32): i32;
/* See implementation. */
extern function inflate(strm: *ZStream, flush: i32): i32;
/* See implementation. */
extern function inflateEnd(strm: *ZStream): i32;

/**
 * See implementation.
 */
export function gzip_zstream_clear_alloc(strm: *ZStream): void {
  strm.zalloc = 0;
  strm.zfree = 0;
  strm.opaque = 0 as *u8;
}

/**
 * See implementation.
 */
export function xlang_gzip_stream_cast(state: *u8, state_cap: i32): *GzipStream {
  let need: i32 = gzip_stream_state_bytes();
  if (state == 0 || state_cap < need) {
    return 0 as *GzipStream;
  }
  let s: *GzipStream = state as *GzipStream;
  if (s.hdr.magic != XLANG_GZIP_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0 as *GzipStream;
  }
  return s;
}

/**
 * See implementation.
 */
export function compress_gzip_compress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let strm: ZStream;
  gzip_zstream_clear_alloc(&strm);
  let init_ret: i32 = 0;
  // Level -1 is Z_DEFAULT_COMPRESSION. Use 0-1 (not the named const):
  // x86_64 product emit of export const -1 as a call arg leaves an unread
  // stack slot (Ubuntu Init2 then Z_STREAM_ERROR). compress2 already passes
  // a -1 literal; match that. Named const stays for the public API.
  // PLATFORM: SHARED — Darwin AAPCS64 folds the named const; Linux x86_64 does not.
  unsafe { init_ret = deflateInit2(&strm, 0 - 1, Z_DEFLATED, GZIP_WBITS, 8, Z_DEFAULT_STRATEGY); }
  if (init_ret != Z_OK) {
    return -1;
  }
  strm.avail_in = in_len as u32;
  strm.next_in = in;
  strm.avail_out = out_cap as u32;
  strm.next_out = out;
  let deflate_ret: i32 = 0;
  unsafe { deflate_ret = deflate(&strm, Z_FINISH); }
  if (deflate_ret != Z_STREAM_END) {
    unsafe { deflateEnd(&strm); }
    return -1;
  }
  let written: i32 = out_cap - (strm.avail_out as i32);
  unsafe { deflateEnd(&strm); }
  return written;
}

/**
 * See implementation.
 */
export function compress_gzip_decompress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let strm: ZStream;
  gzip_zstream_clear_alloc(&strm);
  strm.avail_in = in_len as u32;
  strm.next_in = in;
  let init_ret: i32 = 0;
  unsafe { init_ret = inflateInit2(&strm, GZIP_WBITS); }
  if (init_ret != Z_OK) {
    return -1;
  }
  strm.avail_out = out_cap as u32;
  strm.next_out = out;
  let ret: i32 = 0;
  unsafe { ret = inflate(&strm, Z_FINISH); }
  let written: i32 = -1;
  if (ret == Z_STREAM_END) {
    written = out_cap - (strm.avail_out as i32);
  }
  unsafe { inflateEnd(&strm); }
  return written;
}

/**
 * See implementation.
 */
export function compress_gzip_stream_state_bytes_c(): i32 {
  return gzip_stream_state_bytes();
}

/**
 * See implementation.
 */
export function compress_gzip_stream_init_compress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = gzip_stream_state_bytes();
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *GzipStream = state as *GzipStream;
  s.hdr.magic = XLANG_GZIP_STREAM_MAGIC;
  s.hdr.mode = 0;
  gzip_zstream_clear_alloc(&s.strm);
  let init_ret: i32 = 0;
  // Same 0-1 as compress_gzip_compress_c (x86_64 named-const -1 call-arg).
  // PLATFORM: SHARED
  unsafe { init_ret = deflateInit2(&s.strm, 0 - 1, Z_DEFLATED, GZIP_WBITS, 8, Z_DEFAULT_STRATEGY); }
  if (init_ret != Z_OK) {
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_gzip_stream_init_decompress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = gzip_stream_state_bytes();
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *GzipStream = state as *GzipStream;
  s.hdr.magic = XLANG_GZIP_STREAM_MAGIC;
  s.hdr.mode = 1;
  gzip_zstream_clear_alloc(&s.strm);
  let init_ret: i32 = 0;
  unsafe { init_ret = inflateInit2(&s.strm, GZIP_WBITS); }
  if (init_ret != Z_OK) {
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_gzip_stream_compress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, is_last: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *GzipStream = xlang_gzip_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 0 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let in_before: i32 = in_len;
  if (in_len > 0) {
    s.strm.avail_in = in_len as u32;
    s.strm.next_in = in;
  } else {
    s.strm.avail_in = 0;
    s.strm.next_in = 0 as *u8;
  }
  s.strm.avail_out = out_cap as u32;
  s.strm.next_out = out;
  let flush: i32 = Z_NO_FLUSH;
  if (is_last != 0) {
    flush = Z_FINISH;
  }
  let ret: i32 = 0;
  unsafe { ret = deflate(&s.strm, flush); }
  let written: i32 = out_cap - (s.strm.avail_out as i32);
  if (in_consumed != 0) {
    in_consumed[0] = in_before - (s.strm.avail_in as i32);
  }
  if (ret == Z_STREAM_END) {
    s.hdr.ended = 1;
    return written;
  }
  if (ret == Z_OK) {
    return written;
  }
  if (ret == Z_BUF_ERROR && written > 0) {
    return written;
  }
  return -1;
}

/**
 * See implementation.
 */
export function compress_gzip_stream_decompress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *GzipStream = xlang_gzip_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 1 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let in_before: i32 = in_len;
  if (in_len > 0) {
    s.strm.avail_in = in_len as u32;
    s.strm.next_in = in;
  } else {
    s.strm.avail_in = 0;
    s.strm.next_in = 0 as *u8;
  }
  s.strm.avail_out = out_cap as u32;
  s.strm.next_out = out;
  let ret: i32 = 0;
  unsafe { ret = inflate(&s.strm, Z_NO_FLUSH); }
  let written: i32 = out_cap - (s.strm.avail_out as i32);
  if (in_consumed != 0) {
    in_consumed[0] = in_before - (s.strm.avail_in as i32);
  }
  if (ret == Z_STREAM_END) {
    s.hdr.ended = 1;
    return written;
  }
  if (ret == Z_OK) {
    return written;
  }
  if (ret == Z_BUF_ERROR && (written > 0 || (s.strm.avail_in as i32) < in_before)) {
    return written;
  }
  return -1;
}

/**
 * See implementation.
 */
export function compress_gzip_stream_end_c(state: *u8, state_cap: i32): i32 {
  let hdr_need: i32 = gzip_stream_hdr_bytes();
  if (state == 0 || state_cap < hdr_need) {
    return 0;
  }
  let s: *GzipStream = state as *GzipStream;
  if (s.hdr.magic != XLANG_GZIP_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0;
  }
  if (s.hdr.mode == 0) {
    unsafe { deflateEnd(&s.strm); }
  } else {
    unsafe { inflateEnd(&s.strm); }
  }
  s.hdr.inited = 0;
  return 0;
}
