#!/usr/bin/env bash
#
# 【文件职责】std.process 模块的全量回归测试脚本；按顺序编译并运行 tests/process/*.su，校验退出码。
# 【测试目的】覆盖 exit、args_count/arg/getenv、setenv/unsetenv、getpid、getppid、getcwd、chdir、self_exe_path、spawn_simple+waitpid、exec_simple 失败路径，确保 API 行为符合预期。
# 【覆盖用例】
#   1. main.su     — exit(99)，校验进程退出码 99
#   2. args.su     — args_count、arg(0)、getenv("PATH")
#   3. setenv_unsetenv.su — setenv、getenv、unsetenv 全流程
#   4. getpid.su   — getpid()>0
#   5. getppid.su  — getppid() 可调用
#   6. getcwd.su   — getcwd 成功且 buf 有效
#   7. chdir.su    — chdir(".")、getcwd 前后一致
#   8. self_exe_path.su — self_exe_path 成功且 buf 有效
#   8b. zerocopy.su — getcwd_ptr/getcwd_cached_len、self_exe_path_ptr/self_exe_path_cached_len 零拷贝
#   9. spawn_wait.su — spawn_simple("/bin/true")、waitpid(pid)==0（Windows 无此路径则 SKIP；Alpine 仅有 /bin/true）
#  10. exec_fail.su — exec_simple("/nonexistent") 返回 -1
# 【运行方式】在仓库根目录执行 ./tests/run-process.sh；可选环境变量 SHUC 指定编译器路径。
# 【约定】编译使用 compiler/shuc -L .；失败时打印用例名与原因并 exit 1；spawn_wait 在 Windows 上失败时仅打印 SKIP 不失败整脚本。
#
set -e
cd "$(dirname "$0")/.."
make -C compiler -q 2>/dev/null || make -C compiler

SHUC="${SHUC:-./compiler/shuc}"
run_one() {
  local name="$1"
  local src="$2"
  local exe="/tmp/shuc_process_$$_${name}"
  if ! $SHUC -L . "$src" -o "$exe" 2>&1; then
    echo "process test $name: compile failed"
    return 1
  fi
  local exitcode=0
  $exe >/dev/null 2>&1 || exitcode=$?
  rm -f "$exe"
  if [ "$exitcode" -ne 0 ]; then
    echo "process test $name: expected exit 0, got $exitcode"
    return 1
  fi
  return 0
}

# 1. exit(99)
$SHUC -L . tests/process/main.su -o /tmp/shuc_process_exit 2>&1
exitcode=0; /tmp/shuc_process_exit >/dev/null 2>&1 || exitcode=$?
[ "$exitcode" -ne 99 ] && { echo "process test exit: expected 99, got $exitcode"; exit 1; }
rm -f /tmp/shuc_process_exit

# 2. args_count、arg(0)、getenv("PATH")
run_one "args" "tests/process/args.su" || exit 1

# 3. setenv、getenv、unsetenv
run_one "setenv_unsetenv" "tests/process/setenv_unsetenv.su" || exit 1

# 4. getpid
run_one "getpid" "tests/process/getpid.su" || exit 1

# 5. getppid
run_one "getppid" "tests/process/getppid.su" || exit 1

# 6. getcwd
run_one "getcwd" "tests/process/getcwd.su" || exit 1

# 7. chdir
run_one "chdir" "tests/process/chdir.su" || exit 1

# 8. self_exe_path
run_one "self_exe_path" "tests/process/self_exe_path.su" || exit 1

# 8b. 零拷贝 getcwd_ptr / self_exe_path_ptr
run_one "zerocopy" "tests/process/zerocopy.su" || exit 1

# 9. spawn_simple + waitpid（/bin/true；Windows 无此路径则跳过）
if run_one "spawn_wait" "tests/process/spawn_wait.su"; then
  :
else
  case "$(uname -s 2>/dev/null)" in
    MINGW*|MSYS*|CYGWIN*|*Windows*) echo "process test spawn_wait: SKIP (no /bin/true on Windows)"; ;;
    *) echo "process test spawn_wait: FAIL"; exit 1; ;;
  esac
fi

# 10. exec_simple 失败路径
run_one "exec_fail" "tests/process/exec_fail.su" || exit 1

echo "process test OK (all)"
rm -f /tmp/shuc_process_$$_*
