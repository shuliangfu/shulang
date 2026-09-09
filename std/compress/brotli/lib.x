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

/** Exported function `brotli_stream_state_bytes`.
 * Implements `brotli_stream_state_bytes`.
 * @return i32
 */
export function brotli_stream_state_bytes(): i32 {
  /* See implementation. */
  return 32;
}

/** Exported function `brotli_stream_hdr_bytes`.
 * Implements `brotli_stream_hdr_bytes`.
 * @return i32
 */
export function brotli_stream_hdr_bytes(): i32 {
  return 16;
}

/* See implementation. */
export const XLANG_BROTLI_STREAM_MAGIC: u32 = 0x42525354;

/* See implementation. */
export const BROTLI_DEFAULT_QUALITY: i32 = 11;
export const BROTLI_DEFAULT_WINDOW: i32 = 22;
export const BROTLI_DEFAULT_MODE: i32 = 0;

/* See implementation. */
export const BROTLI_DECODER_RESULT_SUCCESS: i32 = 1;
export const BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT: i32 = 2;
export const BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT: i32 = 3;

/* See implementation. */
export const BROTLI_OPERATION_PROCESS: i32 = 0;
export const BROTLI_OPERATION_FINISH: i32 = 2;

/* See implementation. */
export const BROTLI_TRUE: i32 = 1;

/* See implementation. */
allow(padding) struct BrotliStreamHdr {
  magic: u32;
  mode: i32;
  ended: i32;
  inited: i32;
}

/* See implementation. */
allow(padding) struct BrotliStream {
  hdr: BrotliStreamHdr;
  enc: *u8;
  dec: *u8;
}

/* See implementation. */
extern function BrotliEncoderCompress(quality: i32, lgwin: i32, mode: i32, input_size: usize,
  input_buffer: *u8, encoded_size: *usize, encoded_buffer: *u8): i32;

/* See implementation. */
extern function BrotliDecoderDecompress(encoded_size: usize, encoded_buffer: *u8,
  decoded_size: *usize, decoded_buffer: *u8): i32;

/* See implementation. */
extern function BrotliEncoderCreateInstance(a: *u8, b: *u8, c: *u8): *u8;
extern function BrotliEncoderDestroyInstance(state: *u8): void;

/* See implementation. */
extern function BrotliDecoderCreateInstance(a: *u8, b: *u8, c: *u8): *u8;
extern function BrotliDecoderDestroyInstance(state: *u8): void;

/* See implementation. */
extern function BrotliEncoderCompressStream(state: *u8, op: i32, available_in: *usize,
  next_in: * *u8, available_out: *usize, next_out: * *u8, total_out: *usize): i32;

/* See implementation. */
extern function BrotliEncoderIsFinished(state: *u8): i32;

/* See implementation. */
extern function BrotliDecoderDecompressStream(state: *u8, available_in: *usize, next_in: * *u8,
  available_out: *usize, next_out: * *u8, total_out: *usize): i32;

/* See implementation. */
let xlang_compress_brotli_marker: u8 = 1;

/**
 * See implementation.
 */
export function xlang_brotli_stream_cast(state: *u8, state_cap: i32): *BrotliStream {
  // PLATFORM: SHARED — cap is 32; do not call brotli_stream_state_bytes()
  // (co-emitted short name aliases std.compress facade → recurse).
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return 0 as *BrotliStream;
  }
  let s: *BrotliStream = state as *BrotliStream;
  if (s.hdr.magic != XLANG_BROTLI_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0 as *BrotliStream;
  }
  return s;
}

/**
 * See implementation.
 */
export function compress_brotli_compress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let encoded_size: usize = out_cap as usize;
  let ok: i32 = 0;
  unsafe {
    ok = BrotliEncoderCompress(BROTLI_DEFAULT_QUALITY, BROTLI_DEFAULT_WINDOW, BROTLI_DEFAULT_MODE,
      in_len, in, &encoded_size, out);
  }
  if (ok == 0) {
    return -1;
  }
  return encoded_size as i32;
}

/**
 * See implementation.
 */
export function compress_brotli_decompress_c(in: *u8, in_len: i32, out: *u8, out_cap: i32): i32 {
  if (in == 0 || out == 0 || in_len < 0 || out_cap <= 0) {
    return -1;
  }
  let decoded_size: usize = out_cap as usize;
  let r: i32 = 0;
  unsafe { r = BrotliDecoderDecompress(in_len as usize, in, &decoded_size, out); }
  if (r != BROTLI_DECODER_RESULT_SUCCESS) {
    return -1;
  }
  return decoded_size as i32;
}

/**
 * See implementation.
 */
export function compress_brotli_available_c(): i32 {
  return 1;
}

/**
 * See implementation.
 */
export function compress_brotli_smoke_c(): i32 {
  let inp: u8[5] = [104, 101, 108, 108, 111];
  let out: u8[64] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let dec: u8[64] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  let n: i32 = compress_brotli_compress_c(&inp[0], 5, &out[0], 64);
  if (n <= 0) {
    return 1;
  }
  let m: i32 = compress_brotli_decompress_c(&out[0], n, &dec[0], 64);
  if (m != 5) {
    return 2;
  }
  if (mem.mem_compare(&dec[0], &inp[0], 5) != 0) {
    return 2;
  }
  return 0;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_state_bytes_c(): i32 {
  // PLATFORM: SHARED — literal cap (same as brotli_stream_state_bytes). Co-emitted
  // short-name call aliases the facade and recurses (Ubuntu xlang build).
  return 32;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_init_compress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *BrotliStream = state as *BrotliStream;
  s.hdr.magic = XLANG_BROTLI_STREAM_MAGIC;
  s.hdr.mode = 0;
  unsafe { s.enc = BrotliEncoderCreateInstance(0 as *u8, 0 as *u8, 0 as *u8); }
  if (s.enc == 0) {
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_init_decompress_c(state: *u8, state_cap: i32): i32 {
  let need: i32 = 32;
  if (state == 0 || state_cap < need) {
    return -1;
  }
  mem.mem_zero(state, need);
  let s: *BrotliStream = state as *BrotliStream;
  s.hdr.magic = XLANG_BROTLI_STREAM_MAGIC;
  s.hdr.mode = 1;
  unsafe { s.dec = BrotliDecoderCreateInstance(0 as *u8, 0 as *u8, 0 as *u8); }
  if (s.dec == 0) {
    return -1;
  }
  s.hdr.inited = 1;
  return 0;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_compress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, is_last: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *BrotliStream = xlang_brotli_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 0 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let op: i32 = BROTLI_OPERATION_PROCESS;
  if (is_last != 0) {
    op = BROTLI_OPERATION_FINISH;
  }
  let avail_in: usize = 0;
  let next_in: *u8 = 0 as *u8;
  let avail_out: usize = out_cap as usize;
  let next_out: *u8 = out;
  let total_out: usize = 0;
  if (in_len > 0) {
    avail_in = in_len as usize;
    next_in = in;
  }
  let ret_ok: i32 = 0;
  unsafe { ret_ok = BrotliEncoderCompressStream(s.enc, op, &avail_in, &next_in, &avail_out, &next_out, &total_out); }
  if (ret_ok != BROTLI_TRUE) {
    return -1;
  }
  let written: i32 = out_cap - (avail_out as i32);
  if (in_consumed != 0) {
    in_consumed[0] = in_len - (avail_in as i32);
  }
  let finished: i32 = 0;
  unsafe { finished = BrotliEncoderIsFinished(s.enc); }
  if (is_last != 0 && finished != 0) {
    s.hdr.ended = 1;
  }
  return written;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_decompress_c(state: *u8, state_cap: i32, in: *u8, in_len: i32,
  out: *u8, out_cap: i32, in_consumed: *i32): i32 {
  if (in_consumed != 0) {
    in_consumed[0] = 0;
  }
  let s: *BrotliStream = xlang_brotli_stream_cast(state, state_cap);
  if (s == 0 || s.hdr.mode != 1 || out == 0 || out_cap <= 0) {
    return -1;
  }
  if (in_len > 0 && in == 0) {
    return -1;
  }
  let avail_in: usize = 0;
  let next_in: *u8 = 0 as *u8;
  let avail_out: usize = out_cap as usize;
  let next_out: *u8 = out;
  let total_out: usize = 0;
  if (in_len > 0) {
    avail_in = in_len as usize;
    next_in = in;
  }
  let r: i32 = 0;
  unsafe { r = BrotliDecoderDecompressStream(s.dec, &avail_in, &next_in, &avail_out, &next_out, &total_out); }
  let written: i32 = out_cap - (avail_out as i32);
  if (in_consumed != 0) {
    in_consumed[0] = in_len - (avail_in as i32);
  }
  if (r == BROTLI_DECODER_RESULT_SUCCESS) {
    s.hdr.ended = 1;
    return written;
  }
  if (r == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT && written > 0) {
    return written;
  }
  if (r == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT && written > 0) {
    return written;
  }
  if (r == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT || r == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    return written;
  }
  return -1;
}

/**
 * See implementation.
 */
export function compress_brotli_stream_end_c(state: *u8, state_cap: i32): i32 {
  // PLATFORM: SHARED — hdr cap is 16; avoid co-emit short-name alias.
  let hdr_need: i32 = 16;
  if (state == 0 || state_cap < hdr_need) {
    return 0;
  }
  let s: *BrotliStream = state as *BrotliStream;
  if (s.hdr.magic != XLANG_BROTLI_STREAM_MAGIC || s.hdr.inited == 0) {
    return 0;
  }
  if (s.hdr.mode == 0 && s.enc != 0) {
    unsafe { BrotliEncoderDestroyInstance(s.enc); }
  }
  if (s.hdr.mode == 1 && s.dec != 0) {
    unsafe { BrotliDecoderDestroyInstance(s.dec); }
  }
  s.enc = 0 as *u8;
  s.dec = 0 as *u8;
  s.hdr.inited = 0;
  return 0;
}
