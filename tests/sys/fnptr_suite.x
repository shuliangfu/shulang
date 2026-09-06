// Comprehensive test suite for stage 10 function pointers (10.3.1, 10.3.2, 10.3.3).
// PLATFORM: SHARED — verifies address-of, indirect call, passing as argument,
// returning as value, struct fields, and arrays of function pointers without #[no_mangle].
// Expected exit code: 42 on success.

function add(a: i32, b: i32): i32 {
  return a + b;
}

function sub(a: i32, b: i32): i32 {
  return a - b;
}

function mul(a: i32, b: i32): i32 {
  return a * b;
}

// Higher-order function taking a function pointer as parameter.
function apply_binary(f: function(i32, i32): i32, x: i32, y: i32): i32 {
  return f(x, y);
}

// Function returning a function pointer.
function get_operator(op_code: i32): function(i32, i32): i32 {
  if (op_code == 1) {
    return add as function(i32, i32): i32;
  }
  if (op_code == 2) {
    return sub as function(i32, i32): i32;
  }
  return mul as function(i32, i32): i32;
}

// Struct containing a function pointer callback with explicit padding.
struct OperationHandler {
  handler: function(i32, i32): i32,
  flag: i32,
  _pad: i32,
}

function main(): i32 {
  // 1. Address-of ordinary function as *u8 and direct call.
  let raw_add: *u8 = add as *u8;
  if (raw_add == (0 as *u8)) {
    return 1;
  }
  let v1: i32 = raw_add(10, 32);
  if (v1 != 42) {
    return 2;
  }

  // 2. Address-of ordinary function as typed function pointer.
  let typed_mul: function(i32, i32): i32 = mul as function(i32, i32): i32;
  let v2: i32 = typed_mul(6, 7);
  if (v2 != 42) {
    return 3;
  }

  // 3. Passing function pointer as parameter.
  let v3: i32 = apply_binary(typed_mul, 2, 21);
  if (v3 != 42) {
    return 4;
  }

  // 4. Returning function pointer.
  let op_add: function(i32, i32): i32 = get_operator(1);
  let v4: i32 = op_add(20, 22);
  if (v4 != 42) {
    return 5;
  }

  // 5. Function pointer in struct field and call.
  let handler: OperationHandler = OperationHandler {
    handler: add as function(i32, i32): i32,
    flag: 1,
    _pad: 0,
  };
  let cb: function(i32, i32): i32 = handler.handler;
  let v5a: i32 = cb(15, 27);
  if (v5a != 42) {
    return 6;
  }
  let v5b: i32 = (handler.handler)(15, 27);
  if (v5b != 42) {
    return 7;
  }

  // 6. Array of function pointers and indexed call.
  let ops: [3]function(i32, i32): i32 = [
    add as function(i32, i32): i32,
    sub as function(i32, i32): i32,
    mul as function(i32, i32): i32
  ];
  let v6: i32 = ops[0](12, 30);
  if (v6 != 42) {
    return 8;
  }
  let v7: i32 = (ops[0])(12, 30);
  if (v7 != 42) {
    return 9;
  }

  // All checks passed!
  return 42;
}
