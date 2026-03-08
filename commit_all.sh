#!/usr/bin/env bash
# 按单文件提交：根据该文件的 diff 内容生成 commit message，说明具体做了哪些修改（Conventional Commits + 英文）
set -e
cd "$(dirname "$0")"

# 从 diff 的新增行中提取关键改动描述（用于已修改文件）
# 输出一行简短英文，如 "add ASSIGN expr and for-step; extend match enum"
summarize_diff() {
  local f="$1"
  local diff=$(git diff --no-color "$f" 2>/dev/null)
  [ -z "$diff" ] && echo "no change" && return

  local added=$(echo "$diff" | grep '^+' | grep -v '^+++' | sed 's/^+//')
  [ -z "$added" ] && echo "remove or whitespace" && return

  local hints=""
  echo "$added" | grep -qE 'AST_EXPR_ASSIGN|AST_EXPR_[A-Z]+' && hints="${hints}ASSIGN/expr kind; "
  echo "$added" | grep -qE 'TOKEN_[A-Z]+' && hints="${hints}token; "
  echo "$added" | grep -qE 'parse_assign|parse_ternary|parse_for|parse_expr' && hints="${hints}parser expr/assign/for; "
  echo "$added" | grep -qE 'parse_one_enum|parse_one_struct|parse_import' && hints="${hints}parser struct/enum/import; "
  echo "$added" | grep -qE 'typeck_expr|typeck_module|compute_struct_layouts' && hints="${hints}typeck; "
  echo "$added" | grep -qE 'codegen_expr|codegen_emit|shulang_panic_' && hints="${hints}codegen; "
  echo "$added" | grep -qE 'invoke_cc|opt_level|strip|-O' && hints="${hints}driver -O/strip/cc; "
  echo "$added" | grep -qE 'function\s+\w+|return\s+|panic\s*' && hints="${hints}function/return/panic; "
  echo "$added" | grep -qE 'struct\s+\w+|enum\s+\w+|trait\s+\w+|impl\s+' && hints="${hints}struct/enum/trait/impl; "
  echo "$added" | grep -qE 'let\s+\w+:|const\s+\w+' && hints="${hints}let/const; "
  echo "$added" | grep -qE 'import\s+core\.|import\s+std\.' && hints="${hints}import; "
  echo "$added" | grep -qE 'for\s*\(|while\s+|match\s+\w+' && hints="${hints}for/while/match; "
  echo "$added" | grep -qE 'defer\s*\{|goto\s+' && hints="${hints}defer/goto; "
  echo "$diff" | grep -c '^+' | grep -qE '[1-9]' && [ -z "$hints" ] && hints="code or comment change; "
  echo "$added" | grep -qE 'README|说明|文档' && hints="${hints}docs/README; "
  echo "$added" | grep -qE 'size_baseline|perf.baseline|run-' && hints="${hints}baseline script; "

  hints=$(echo "$hints" | sed 's/; $//')
  [ -z "$hints" ] && hints="update"
  echo "$hints"
}

# 根据路径确定 type 前缀：refactor/feat/test/docs/chore
type_prefix() {
  local f="$1"
  [[ "$f" == compiler/* ]] && echo "refactor(compiler)" && return
  [[ "$f" == core/*.su ]] && echo "feat(core)" && return
  [[ "$f" == std/*.su ]] && echo "feat(std)" && return
  [[ "$f" == docs/* ]] && echo "docs" && return
  [[ "$f" == tests/README.md ]] && echo "docs(tests)" && return
  [[ "$f" == tests/* ]] && echo "test" && return
  [[ "$f" == examples/* ]] && echo "chore(examples)" && return
  echo "chore"
}

# 生成 commit message：$1=文件路径 $2=add|update
msg_for() {
  local f="$1"
  local mode="$2"
  local base=$(basename "$f")
  local dir=$(dirname "$f")
  local prefix=$(type_prefix "$f")
  local summary=""

  if [[ "$mode" == add ]]; then
    # 新文件：用路径和文件名描述
    if [[ "$f" == core/*.su ]]; then summary="add $(basename ${f%.su}) module"; fi
    if [[ "$f" == std/*.su ]]; then summary="add $(basename ${f%.su}) module"; fi
    if [[ "$f" == tests/run-*.sh ]]; then summary="add runner script $(basename ${f%.sh})"; fi
    if [[ "$f" == tests/*/*.su ]]; then summary="add $dir test case $(basename ${f%.su})"; fi
    if [[ "$f" == tests/*.su ]]; then summary="add test $base"; fi
    [ -z "$summary" ] && summary="add $f"
    echo "$prefix: $summary"
    return
  fi

  # 已修改文件：根据 diff 概括具体改动
  summary=$(summarize_diff "$f")
  if [[ "$f" == tests/README.md ]]; then
    summary="update tests README"
  fi
  echo "$prefix: $summary"
}

# 先提交所有已修改文件
while IFS= read -r f; do
  [ -z "$f" ] && continue
  [ ! -f "$f" ] && continue
  msg=$(msg_for "$f" update)
  # 截断过长（保留约 72 字符）
  msg=$(echo "$msg" | cut -c1-72)
  git add "$f" && git commit -m "$msg"
done < <(git diff --name-only)

# 再提交所有未跟踪文件
while IFS= read -r f; do
  [ -z "$f" ] && continue
  [ ! -f "$f" ] && continue
  msg=$(msg_for "$f" add)
  msg=$(echo "$msg" | cut -c1-72)
  git add "$f" && git commit -m "$msg"
done < <(git ls-files --others --exclude-standard)

echo "Done."
