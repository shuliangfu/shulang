/**
 * Regression: if-cond grouped binop + following assignment must not hang.
 * Minimal g5 from analysis/当前问题分析.md §3.4.
 * Expect: parse+typeck+run rc=0.
 * PLATFORM: SHARED
 */
function main(): i32 {
  let m: i32 = 3;
  if (m + 1) == 1 {
    m = 0;
  }
  m = m / 2;
  return 0;
}
