// See implementation.
// 9.3.3: bare decimal literal #if 0 must be false.
#if 0
/** Internal function `main`.
 * Program/test entry point.
 * @return i32
 */
function main(): i32 { return 11; }
#else
/** Internal function `main`.
 * Program/test entry point.
 * @return i32
 */
function main(): i32 { return 22; }
#endif
