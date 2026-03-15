/**
 * std/runtime/runtime.c — 运行时：panic/abort 对接编译器生成的 shulang_panic_
 *
 * 【文件职责】
 * 提供 runtime_panic()、runtime_abort()，供 std.runtime 的 panic()/abort() 调用；
 * 内部调 shulang_panic_(0, 0)，该符号由 compiler 链接时提供的 runtime_panic.o 提供。
 *
 * 【对标】Zig @panic、Rust panic!、Go runtime.Goexit/panic；我们显式提供 panic/abort 供用户与断言使用。
 */

extern void shulang_panic_(int has_msg, int msg_val);

/** 无参 panic：终止程序（noreturn）。对标 Rust panic!()、Zig @panic。 */
void runtime_panic(void) {
  shulang_panic_(0, 0);
}

/** 终止程序（noreturn）；与 panic 同义，对标 C abort()、Rust std::process::abort。 */
void runtime_abort(void) {
  shulang_panic_(0, 0);
}
