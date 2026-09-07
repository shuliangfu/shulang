// wave942 (9.4.2 carrier) · true void*(*)(void*) C-ABI loop: xlang fn
//   address -> thread_create_c (pthread_create) -> pthread invokes it ->
//   join -> verify side effect on the caller's stack.
// Expected: exit 42 (payload == 91).
// PLATFORM: SHARED — macOS dev box + Ubuntu gold.
function tbody(arg: *u8): *u8 {
  let p: *i32 = arg as *i32;
  unsafe { *p = 91; }
  return arg;
}
extern function thread_create_c(entry: *u8, arg: *u8): i64;
extern function thread_join_c(thread_id: i64): i32;
function main(): i32 {
  let payload: i32 = 0;
  let tid: i64 = 0;
  unsafe { tid = thread_create_c(tbody as *u8, &payload as *u8); }
  if (tid == 0) { return 5; }
  let jr: i32 = 0;
  unsafe { jr = thread_join_c(tid); }
  if (jr != 0) { return 6; }
  if (payload != 91) { return 7; }
  return 42;
}
